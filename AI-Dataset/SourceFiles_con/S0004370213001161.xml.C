<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Algorithms for decision problems in argument systems under preferred semantics.
   </title>
   <abstract>
    For Dungʼs model of abstract argumentation under preferred semantics, argumentation frameworks may have several distinct preferred extensions: i.e., in informal terms, sets of acceptable arguments. Thus the acceptance problem (for a specific argument) can consider deciding whether an argument is in at least one such extensions (credulously accepted) or in all such extensions (skeptically accepted). We start by presenting a new algorithm that enumerates all preferred extensions. Following this we build algorithms that decide the acceptance problem without requiring explicit enumeration of all extensions. We analyze the performance of our algorithms by comparing these to existing ones, and present experimental evidence that the new algorithms are more efficient with respect to the expected running time. Moreover, we extend our techniques to solve decision problems in a widely studied development of Dungʼs model: namely value-based argumentation frameworks (vafs). In this regard, we examine analogous notions to the problem of enumerating preferred extensions and present algorithms that decide subjective, respectively objective, acceptance.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Computational argumentation is an active research branch of artificial intelligence, see e.g. [10], [11], [55] for reviews. Abstract argumentation frameworks (afs) offer a reasoning model that is likely to be a mainstay in the study of other areas such as decision support systems (see e.g. [3]), machine learning (see e.g. [47]), and agent interaction in multi-agent systems (see e.g. [42]). Following Dung [26], an abstract argumentation framework consists of a set of arguments and a binary relation that represents the conflicting arguments. Then, a solution to an af is captured by deciding the acceptable arguments. A number of argumentation semantics have been proposed to characterize such solutions [5]. For solutions defined in set-theoretic terms (extension-based semantics) one often finds cases, such as preferred semantics (defined in Section 2), in which multiple extensions are present. Thus, focusing on preferred extensions, an argument is viewed as skeptically accepted if and only if it occurs in all preferred extensions. In a similar manner, an argument is seen as credulously accepted if and only if it occurs in at least one such extension.
     </paragraph>
     <paragraph>
      Doutre and Mengin [24] and later Modgil and Caminada [45] presented algorithms for computing preferred extensions. Informally, both algorithms build on so-called labelling based methods, under which arguments that might be included in an extension are labelled IN while arguments which might not be in the respective extension are labelled OUT and the undecided arguments are labelled UNDEC (short for undecided). Both algorithms start with some initial label for all arguments and then the labels change, through so-called transitions, until some condition holds. At this point, the arguments labelled IN make up an admissible set (defined in Section 2). These algorithms go through different sequences of transitions, and hence, they identify admissible sets in order to construct preferred extensions. The two algorithms differ in two key aspects: the argumentsʼ initial labels; and the transitions rules applied to argument labels. As we show, these issues have a significant affect on performance.
     </paragraph>
     <paragraph>
      The contribution of this work can be summarized in five points. Firstly, we introduce additional labels thereby gaining an improved label transition approach and, hence, construct preferred extensions faster than existing algorithms. Secondly, we introduce a new mechanism for pruning the search space so that transitions leading to “dead ends” are avoided at an early stage. Thirdly, we present a cost-effective heuristic rule that identifies arguments for transitions that might enable a goal state (i.e. a preferred extension) to be achieved earlier. Fourthly, by incorporating the three improvements, we design algorithms for deciding the skeptical/credulous acceptance question without explicitly enumerating all preferred extensions. Finally, we establish the usability of our algorithms in developments of Dungʼs model by investigating an instance of such: specifically the value based argumentation frameworks (vafs) of [8]. Note that some earlier results of this work were presented in [50], [51].
     </paragraph>
     <paragraph>
      In Section 3 our new algorithm that enumerates all preferred extensions is presented. In Section 4 we argue that our algorithm is faster in constructing preferred extensions than the existing approaches of Doutre and Mengin [24] and Modgil and Caminada [45] supporting these claims on the basis of empirical studies. Regarding the acceptance problems, although the skeptically/credulously accepted arguments might be simply decided by enumerating all preferred extensions, in situations where interest is confined to a single specific argument then it is more efficient to avoid such complete enumeration of preferred extensions. This is especially the case when the underlying af is dynamic (i.e. changes frequently such as in a dialog setting). Accordingly, in Section 5 we engineer algorithms that outperform, with respect to running time, the existing algorithms of Cayrol et al. [19], Thang et al. [56] and the algorithm of Verheij for the credulous acceptance problem [58]. We present relevant comparisons with existing algorithms and empirical evaluation in Section 6. In Section 7 we demonstrate how our algorithms for Dungʼs frameworks may be adapted to address analogous problems in vafs. More specifically, we address the following problems relevant to this context: preferred extension enumeration, subjective acceptance and objective acceptance. We offer further discussions and a review of related work in Section 8 and lastly we conclude the paper in Section 9.
     </paragraph>
     <paragraph>
      We first present preliminary background in Section 2.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminary background
     </section-title>
     <paragraph label="Definition 1">
      We recall the concept of argumentation framework from [26]. Dungʼs argumentation frameworksAn argumentation framework (or af) is a pair {a mathematical formula}(A,R) where A is a set of arguments and {a mathematical formula}R⊆A×A is a binary relation.
     </paragraph>
     <paragraph>
      We refer to {a mathematical formula}(x,y)∈R as x attacks y (or y is attacked by x). We denote by {a mathematical formula}{x}− respectively {a mathematical formula}{x}+ the subset of A containing those arguments that attack (resp. are attacked by) the argument x, extending this notation in the natural way to sets of arguments, so that for {a mathematical formula}S⊆A,{a mathematical formula}
     </paragraph>
     <paragraph>
      Given a subset {a mathematical formula}S⊆A, then
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}x∈A is acceptable w.r.t. S if and only if for every {a mathematical formula}(y,x)∈R, there is some {a mathematical formula}z∈S for which {a mathematical formula}(z,y)∈R.
      </list-item>
      <list-item label="•">
       S is conflict free if and only if for each {a mathematical formula}(x,y)∈S×S, {a mathematical formula}(x,y)∉R.
      </list-item>
      <list-item label="•">
       S is admissible if and only if it is conflict free and every {a mathematical formula}x∈S is acceptable w.r.t. S.
      </list-item>
      <list-item label="•">
       S is a preferred extension if and only if it is a maximal (w.r.t. ⊆) admissible set.
      </list-item>
      <list-item label="•">
       S is a stable extension if and only if it is conflict free and {a mathematical formula}S+=A∖S.
      </list-item>
      <list-item label="•">
       S is a complete extension if and only if it is an admissible set such that for each x acceptable w.r.t. S, {a mathematical formula}x∈S.
      </list-item>
      <list-item label="•">
       S is a stage extension if and only if it is conflict free and {a mathematical formula}S∪S+ is maximal (w.r.t. ⊆).
      </list-item>
      <list-item label="•">
       S is a semi-stable extension if and only if it is admissible and {a mathematical formula}S∪S+ is maximal (w.r.t. ⊆).
      </list-item>
      <list-item label="•">
       S is the ideal extension if and only if it is the maximal (w.r.t. ⊆) admissible set that is contained in every preferred extension.
      </list-item>
      <list-item label="•">
       S is the grounded extension if and only if it is the least fixed point of {a mathematical formula}F(T)={x∈A|xis acceptable w.r.t.T}.
      </list-item>
     </list>
     <paragraph>
      Preferred, complete, stable and grounded semantics are introduced in [26], whereas ideal semantics, stage semantics and semi-stable semantics are presented in [27], [57], [14] respectively. To give an example, consider the framework depicted in Fig. 1 where nodes represent arguments and edges correspond to attacks (i.e. elements of R). For this example {a mathematical formula}{b,d} is the preferred, grounded, stable, ideal, complete, semi-stable and stage extension. Note that we do not intend by this example to show differences between semantics. In the above, we introduced a selection of prevalent argumentation semantics. It is out of the scope of the present paper to explain the motivation behind every semantics or even to review all argumentation semantics proposed in the literature. In this paper we develop algorithms for decision problems under preferred semantics. This should not be construed as giving favor to preferred semantics over other semantics. From an application perspective, it has been highlighted (e.g. [5]) that it is a matter of choice as to which semantics to use for the application at hand. See the review of Baroni et al. [5] for an excellent introduction to argumentation semantics with a comprehensive discussion on explaining the motivations behind the diversity of argumentation semantics. Therefore, although this work is about building algorithms under preferred semantics, we show how these algorithms might lead to constructing algorithms for the other argumentation semantics. The bottom line is, this work has impact on implementing algorithms for argumentation semantics in general, despite the apparent focus on the preferred semantics.
     </paragraph>
     <paragraph>
      The notion of extension follows a convention of defining argumentation semantics in terms of subsets of arguments in an af, i.e. those arguments that meet particular criteria. More precisely, if {a mathematical formula}σ:2A→{⊤,⊥} is a predicate over subsets of arguments, then the σ-extensions of {a mathematical formula}(A,R) – denoted by {a mathematical formula}Eσ(A,R) – are the subsets of A which satisfy σ. A related, and often interchangeable concept characterizes argumentation semantics in terms of labelling properties. Perhaps, the most prevalent work is the labelling theory introduced by Caminada and Gabbay [17]. A central concept of this approach is to define the set of labellings that basically captures {a mathematical formula}Eσ(A,R) under a specific semantics {a mathematical formula}σ:2A→{⊤,⊥}. However, for the purpose of showing the connection of our algorithms to the theory of [17] we prescribe preferred labellings that basically correspond to preferred extensions. We refer the interested reader to [17], [5] for full presentation of the theory of Caminada and Gabbay.
     </paragraph>
     <paragraph label="Definition 2">
      Preferred labellingsLet {a mathematical formula}(A,R) be an af and {a mathematical formula}S⊆A be a preferred extension (resp. admissible set). Then, the corresponding preferred (resp. admissible) labelling {a mathematical formula}λ:A→{IN,OUT,UNDEC} for S is described by:{a mathematical formula}
     </paragraph>
     <paragraph>
      From now on we may use the terms (extension) and (labelling) interchangeably since we can obtain either if the other is given.
     </paragraph>
     <paragraph>
      Given the above context, the job of a labelling-based algorithm for listing preferred extensions can be seen as constructing all labellings within which arguments labelled IN represent a preferred extension. Both of the algorithms of [24], [45] define labelling-based procedures for enumerating preferred extensions using a total mapping {a mathematical formula}λ:A→{IN,OUT,UNDEC}. However, in [45] the IN label is the default label for all arguments of the given framework and the procedure constructs preferred labellings whose properties are specified in Definition 2, while in [24] the UNDEC label is the default label for all arguments of the input framework and the procedure captures a preferred extension S when the corresponding labelling has the following properties:{a mathematical formula}
     </paragraph>
     <paragraph>
      Thus, the algorithm of [45] adheres to the conventions of the theory of Caminada and Gabbay, whereas the algorithm of [24] does not. As we show in the paper, our algorithm for preferred extension enumeration basically constructs preferred extensions from labellings satisfying the properties of Definition 2, and so, our algorithms fit neatly into the labelling theory of Caminada and Gabbay. Nevertheless, the main concern of the present paper is to improve the efficiency of listing all preferred labellings/extensions by defining new implemented algorithms that outdo (in terms of running-time) existing algorithms. In the next section we present our new algorithm for enumerating preferred extensions.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Preferred extension enumeration: the new algorithm
     </section-title>
     <paragraph>
      One significant factor in the algorithm described in this section is in its modification of the basic labelling framework. Thus, in addition to the labels IN, OUT and UNDEC that are used by the existing algorithms of [24], [45], we introduce labels which are referred to as MUST_OUT and BLANK, so that a labelling of {a mathematical formula}H=(A,R) is now a total mapping, {a mathematical formula}μ:A→{IN,OUT,BLANK,MUST_OUT,UNDEC}. Note that we use the notation μ for such 5-value labelling schemes to distinguish from the 3-valued schemes referred to earlier.
     </paragraph>
     <paragraph>
      In what follows we explain informally how these five labels are used in our algorithm. The BLANK label is the default label for all arguments, indicating that the argument is still unprocessed. The IN label identifies arguments that might be in a preferred extension. The OUT label identifies an argument that is attacked by an IN argument. The MUST_OUT label identifies arguments that attack IN arguments. The UNDEC label designates arguments which may not be included in a preferred extension because they are not defended by any IN argument. The precise usage of these labels are introduced in Algorithm 1 for listing all preferred extensions.
     </paragraph>
     <paragraph label="Definition 3">
      Algorithm 1 is a depth-first backtracking procedure that traverses an implicit binary search tree. Algorithm 1 starts with BLANK as the initial label for all arguments, this initial state represents the root node of the search tree. Then the algorithm forks to a left (resp. right) child by picking an argument, that is BLANK, to be labelled IN (resp. UNDEC). Every time an argument, say x, is labelled IN the label of the neighbour arguments might change such that for every {a mathematical formula}y∈{x}+ the label of y becomes OUT and for every {a mathematical formula}z∈{x}−∖{x}+ the label of z becomes MUST_OUT. This process, i.e. forking to new children, continues until for every {a mathematical formula}x∈A the label of x is not BLANK. At this point, the algorithm captures {a mathematical formula}{x|the label of x is IN} as a preferred extension if and only if for every {a mathematical formula}x∈A the label of x belongs to {a mathematical formula}{IN,OUT,UNDEC} and {a mathematical formula}{x|the label of x is IN} is not a subset of a previously found preferred extension (if such exists). Then the algorithm backtracks to try to find all preferred extensions. Before giving the full specification of Algorithm 1, we define concretely the actions involved during the transition from a node of the search tree to a left (or right) child. Since expanding a left child involves labelling an argument IN, we denote such expansion by IN-TRANS (short for IN-TRANSITION). During IN-TRANS three actions are taken. Firstly, the label of a BLANK argument becomes IN. Secondly, attackers of the newly IN argument are labelled MUST_OUT. Thirdly, arguments attacked by the newly IN argument are labelled OUT. IN-TRANS transition ruleLet {a mathematical formula}(A,R) be an af, {a mathematical formula}x∈A, {a mathematical formula}μ:A→{IN,OUT,MUST_OUT,BLANK,UNDEC} be a total mapping such that {a mathematical formula}μ(x)=BLANK. Then, IN-TRANS(x) is defined by the next ordered actions:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}μ′←μ;
      </list-item>
      <list-item label="2.">
       {a mathematical formula}μ′(x)←IN;
      </list-item>
      <list-item label="3.">
       for all{a mathematical formula}y∈{x}+do{a mathematical formula}μ′(y)←OUT;
      </list-item>
      <list-item label="4.">
       for all{a mathematical formula}z∈{x}−:μ′(z)≠OUTdo{a mathematical formula}μ′(z)←MUST_OUT;
      </list-item>
      <list-item label="5.">
       return {a mathematical formula}μ′.
      </list-item>
     </list>
     <paragraph>
      Similarly we denote expanding a right child by UNDEC-TRANS, which is a process that basically involves labelling an argument UNDEC. The purpose of UNDEC-TRANS is to try to find a preferred extension excluding the newly UNDEC argument. Simply, the UNDEC-TRANS is applied by changing the label of a BLANK argument to UNDEC in accordance with the following definition.
     </paragraph>
     <paragraph label="Definition 4">
      UNDEC-TRANS transition ruleLet {a mathematical formula}(A,R) be an af, {a mathematical formula}x∈A, {a mathematical formula}μ:A→{IN,OUT,MUST_OUT,BLANK,UNDEC} be a total mapping such that {a mathematical formula}μ(x)=BLANK. Then, UNDEC-TRANS(x) is defined by the following ordered steps:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}μ′←μ;
      </list-item>
      <list-item label="2.">
       {a mathematical formula}μ′(x)←UNDEC;
      </list-item>
      <list-item label="3.">
       return {a mathematical formula}μ′.
      </list-item>
     </list>
     <paragraph>
      Fig. 2 shows how Algorithm 1 works on the af depicted in Fig. 1.
     </paragraph>
     <paragraph>
      Let us now improve the efficiency of Algorithm 1 by applying three enhancements. For the first enhancement, Algorithm 1 selects an argument labelled BLANK to use as the basis for an IN-TRANS transition arbitrarily. As we demonstrate, however, it is more productive to guide the selection via the following rule:
     </paragraph>
     <list>
      <list-item label="1.">
       Select any x with {a mathematical formula}μ(x)=BLANK and satisfying for all {a mathematical formula}y∈{x}− the condition {a mathematical formula}μ(y)∈{OUT,MUST_OUT}.
      </list-item>
      <list-item label="2.">
       Otherwise select any x with {a mathematical formula}μ(x)=BLANK and such that {a mathematical formula}|{x}+| is maximal.
      </list-item>
     </list>
     <paragraph>
      Later in this section we will explain the reason behind the first part of this selection rule. As to the second part, the intuition is that this heuristic might accelerate reaching a goal state, that is, an admissible set. Recall that the set of arguments labelled IN is admissible if and only if all arguments in the framework are labelled IN, OUT or UNDEC. Thus, the goal state of the search might be reached faster as much as we minimize the number of arguments with labels in {a mathematical formula}{BLANK,MUST_OUT} by maximizing the number of arguments labelled OUT. Conversely, as long as the first part of the selection rule failed, one might pick up an argument x for IN-TRANS such that the number of arguments that attack x is minimal. At first sight, such selection seems sensible because it produces almost a minimal number of arguments labelled MUST_OUT. However, recall that we get to a goal state (i.e. admissible set) if and only if no argument is labelled BLANK or MUST_OUT, and thus, minimizing the number of arguments labelled MUST_OUT will be unhelpful as long as the number of arguments labelled BLANK is not also minimized.
     </paragraph>
     <paragraph>
      For the second enhancement to Algorithm 1, we exploit a pruning mechanism, originally used by [24] but here we improve its effect as we explain in Section 4.1. This detects the branch of the search tree that will eventually take us to a dead end: in the sense that further expansion of the search tree – while possible – is unproductive. In particular, the pruning mechanism says that if at any state of the search there exists an argument x with {a mathematical formula}μ(x)=MUST_OUT and no argument {a mathematical formula}y∈{x}− with the label BLANK then proceeding further is fruitless and so the algorithm simply must backtrack.
     </paragraph>
     <paragraph>
      For the third enhancement, we use a further pruning tactic: we skip applying an UNDEC-TRANS transition on an argument x with the BLANK label if and only if for each {a mathematical formula}y∈{x}− the label of y belongs to {a mathematical formula}{OUT,MUST_OUT}. The enhancement simply uses the following property: if an admissible set S will be constructed while the label of such x is UNDEC then {a mathematical formula}S∪{x} is admissible and so applying the UNDEC-TRANS(x) is unnecessary.
     </paragraph>
     <paragraph>
      At this point it is convenient to give the basis for the first part of our rule when selecting an argument x labelled BLANK, i.e. to choose, if available, an {a mathematical formula}x∈A for which every {a mathematical formula}y∈{x}− is labelled OUT or MUST_OUT. Here, we note that the earlier such x is labelled IN, the greater the saving will be in terms of the part of the search tree pruned (keeping in mind the third enhancement).
     </paragraph>
     <paragraph>
      Furthermore, we modify Algorithm 1 by two minor changes. For the first change, note that UNDEC-TRANS(x) only changes the label of x: consequently there is no need to fork to a new set of labels via UNDEC-TRANS, and so, we just change the label of x to UNDEC within the current labelling. For the second change, we rewrite the IN-TRANS rule using its definition to make the algorithm self-contained. In total these lead to Algorithm 2 that reinforces Algorithm 1 by incorporating the three enhancements mentioned before alongside the two minor changes. Fig. 3 shows how Algorithm 2 computes the preferred extensions of the af of Fig. 1. We consider now the soundness and completeness of Algorithm 2.
     </paragraph>
     <paragraph label="Proposition 1">
      Let{a mathematical formula}H=(A,R)be anafand PEXT be the set of subsets of A returned byAlgorithm 2. Then{a mathematical formula}Epreferred(H)=PEXT, i.e. the algorithm reports exactly the set of preferred extensions of H.
     </paragraph>
     <paragraph label="Proof">
      We first show that every {a mathematical formula}S∈PEXT is admissible. Certainly every {a mathematical formula}S∈PEXT is conflict free: assume that there are {a mathematical formula}y,z∈S with {a mathematical formula}(y,z)∈R. If y had been labelled IN before z then z would be labelled OUT by Algorithm 2 (lines 7 and 10). On the other hand, were z to be labelled IN prior to y then y will never be labelled IN (lines 11) while z is so labelled. Both cases contradict every {a mathematical formula}x∈S being labelled IN (line 10–16). To show that for each {a mathematical formula}x∈S, x is acceptable w.r.t. S, suppose that for some {a mathematical formula}y∈S there exists {a mathematical formula}(z,y)∈R but no {a mathematical formula}w∈S with {a mathematical formula}(w,z)∈R. In this case Algorithm 2 will have modified the labelling of {a mathematical formula}μ(y)=BLANK to {a mathematical formula}μ′(y)←IN (line 24). Subsequently (line 10), z is considered together with arguments {a mathematical formula}w∈{z}− (lines 12) in the event that {a mathematical formula}μ′(z)∈{UNDEC,BLANK}. To begin, suppose (when y is labelled IN) that {a mathematical formula}μ′(z)∉{UNDEC,BLANK}. It cannot be the case that {a mathematical formula}μ′(z)=IN for, as argued earlier, y would then have been earlier labelled OUT (line 14–17). It follows, therefore, that {a mathematical formula}μ′(z)∈{OUT,MUST_OUT} is the only possibility consistent with {a mathematical formula}μ′(y)=IN, {a mathematical formula}(z,y)∈R and {a mathematical formula}μ′(z)∉{UNDEC,BLANK}. In the former case ({a mathematical formula}μ′(z)=OUT), we must have {a mathematical formula}z∈{w}+ and {a mathematical formula}μ′(w)=IN (line 11) thereby contradicting the premise that such w was unavailable. In the latter case ({a mathematical formula}μ′(z)=MUST_OUT), we have (from line 23) a contradiction to S having been reported as a potentially admissible set in PEXT: S can only be added if there is no {a mathematical formula}w∈A labelled MUST_OUT. This observation suffices to deal with the case that {a mathematical formula}μ′(z)is in {a mathematical formula}{UNDEC,BLANK} for again such z will be labelled MUST_OUT (line 11).Our analysis of the preceding paragraph establishes that every {a mathematical formula}S∈PEXT is admissible. We now show that each such set is, in fact maximal so completing the argument that {a mathematical formula}PEXT⊆Epreferred(H). In order to prove maximality (w.r.t. ⊆) let us assume that some {a mathematical formula}S∈PEXT is not maximal. From the actions of line 14 in Algorithm 2 this implies that there exists an admissible set {a mathematical formula}S′⊃S s.t. which has not been included in PEXT. Thus there is (at least one) argument, y belonging to the set {a mathematical formula}S′∖S. Algorithm 2, however, firstly labels y IN (line 25) and then later UNDEC (lines 10 and 16), and therefore, the set {a mathematical formula}S′ would be discovered in advance of the set S and thereby (line 20) added to PEXT.Finally, that {a mathematical formula}Epreferred(H)⊆PEXT follows directly from the fact that Algorithm 2 examines all subsets of A by labelling every argument that is (initially) labelled BLANK to be labelled IN (see line 25) and afterwards UNDEC (see lines 10 and 16) thereby considering all subsets including (respectively excluding) y.  □
     </paragraph>
    </section>
    <section label="4">
     Advantages of Algorithm 2 over earlier methods
     <paragraph>
      We now review the manner in which our algorithm offers potential savings over some important previous (labelling-based) techniques.
     </paragraph>
     <section label="4.1">
      <section-title>
       The algorithm of Doutre and Mengin
      </section-title>
      <paragraph>
       In [24] Doutre and Mengin present an algorithm, which we shall refer to as the DM algorithm subsequently, to enumerate all preferred extensions. The method of [24] uses a total mapping {a mathematical formula}λ:A→{IN,OUT,UNDEC}. This approach starts with every argument labelled UNDEC and then iteratively considers branches resulting via two transition rules. We can identify five differences between the DM algorithm and our approach.
      </paragraph>
      <list>
       <list-item label="DM1.">
        The DM algorithm selects an argument labelled UNDEC for transitions by heuristics in which should one rule fail to select an argument another rule is applied and so on. Three rules are given below:
       </list-item>
       <list-item label="DM2.">
        In the DM algorithm the counterpart to our IN-TRANS transition rule operates as follows:{a mathematical formula} In our approach such attackers are labelled MUST_OUT. The MUST_OUT label allows us to streamline a search pruning mechanism. In particular, the DM algorithm stops exploring a branch further and backtracks if there is some {a mathematical formula}y∈{x}− for which{a mathematical formula} A check which is performed after every transition. In contrast, Algorithm 2 backtracks as soon as an argument, y, is discovered for which{a mathematical formula} This check is performed only when applying the IN-TRANS rule which results in new MUST_OUT arguments. We observe that Algorithm 2 needs to check the condition of this pruning strategy less frequently than the algorithm of DM. Moreover, its applicability is verified on average more efficiently than the corresponding test of the DM algorithm: searching for y with {a mathematical formula}μ(y)=MUST_OUT is at worst {a mathematical formula}|A| steps; searching for x and y with {a mathematical formula}λ(y)=OUT, {a mathematical formula}λ(x)=IN, {a mathematical formula}y∈{x}− (potentially) requires {a mathematical formula}|R| steps. Typically {a mathematical formula}|R|&gt;|A|.
       </list-item>
       <list-item label="DM3.">
        The DM counterpart of UNDEC-TRANS labels the respective argument as OUT instead of UNDEC. To appreciate the benefit of UNDEC-TRANS consider the subsequent stages. Once the DM algorithm finds an admissible set the labels of all arguments are either IN or OUT, and thus, one cannot tell which of the OUT arguments attack (or are attacked by) an argument labelled IN. Comparing with our algorithm, an admissible set is reported if and only if all arguments are labelled IN, OUT or UNDEC. In this way, one easily can see that arguments labelled OUT attack (or are attacked by) an argument labelled IN while those labelled UNDEC are excluded from the respective admissible set on the grounds that they might be indefensible by the arguments labelled IN.
       </list-item>
       <list-item label="DM4.">
        In order to ensure maximality of the reported preferred extensions the DM algorithm carries out the following test:{a mathematical formula} In contrast the approach of Algorithm 2 includes a subset S in PEXT (the preferred extensions accumulated so far) if and only if a strict superset of S has not already been included in PEXT.
       </list-item>
       <list-item label="DM5.">
        Finally, we stress that our algorithm uses a new pruning mechanism that skips expanding the UNDEC-TRANS on arguments that are attacked exclusively by arguments whose labels are OUT or MUST_OUT.
       </list-item>
      </list>
     </section>
     <section label="4.2">
      <section-title>
       The algorithm of Modgil and Caminada
      </section-title>
      <paragraph>
       In [45] Modgil and Caminada present an algorithm (MC) to enumerate all preferred extensions. In common with the DM algorithm discussed above, this uses a total mapping {a mathematical formula}λ:A→{IN,OUT,UNDEC}. An important concept in the MC approach is in its introduction of the so-called “illegally” and “super-illegally” labelled arguments. We note that these are not labels per se but rather refinements of the interpretation of the labels against which they are considered. We show six differences between the MC algorithm and Algorithm 2.
      </paragraph>
      <list>
       <list-item label="MC1.">
        The MC approach starts with all arguments labelled IN while our approach starts with all arguments BLANK. Our contention (supported by the empirical studies presented in the next section) is that this is more than a simple “stylistic” issue. In particular, the choice of initial labelling may have a dramatic effect on the overall average performance: this determines the range of applicable transition rules. Transitions influence two efficiency aspects: the computational cost of applying the transition itself; the number of applicable transitions at a time, i.e. the resulting number of branches. We further examine these issues in the subsequent sections.
       </list-item>
       <list-item label="MC2.">
        In applying transitions, MC selects an argument, x, with {a mathematical formula}λ(x)=IN that is attacked by an argument, y that is “legally” labelled with one of {a mathematical formula}{IN,UNDEC}: in the terminology of [45] such x are dubbed super-illegally IN. An argument x being legally IN if and only if every {a mathematical formula}y∈{x}−, has {a mathematical formula}λ(y)=OUT. Similarly, x with {a mathematical formula}λ(x)=UNDEC, is legally UNDEC if and only if every {a mathematical formula}y∈{x}− has {a mathematical formula}λ(y)≠INand at least one such y has {a mathematical formula}λ(y)=UNDEC. If there are no super-illegally IN arguments then MC algorithm picks an illegally IN argument, i.e. an argument attacked by an argument labelled IN (or UNDEC). In contrast, Algorithm 2 selects an argument, x, labelled BLANK on the bases we have discussed earlier. Therefore, the selection process of MC may take up to {a mathematical formula}|R|2 steps while that of Algorithm 2 requires no more than {a mathematical formula}|R|.
       </list-item>
       <list-item label="MC3.">
        The MC approach defines an argument, x, with {a mathematical formula}λ(x)=OUT to be illegally OUT when there is no {a mathematical formula}y∈{x}− for which {a mathematical formula}λ(y)=IN. As a result there is a transition rule in MC which has no counterpart within the transition rules of Algorithm 2.This transition identifies an illegally IN argument, x, and changes its label to OUT. A consequence of such changes, however, is that arguments, {a mathematical formula}y∈{x}+ may become illegally OUT and so have their label changed to UNDEC. Hence, in MC the transitions need to process the attackers of a set of OUT arguments. This set not only contains the argument, y say, relabelled as OUT but also the arguments labelled OUT which are attacked by y. Comparing the two transition rules of Algorithm 2, both of these require typically less computations: UNDEC-TRANS only processes one argument while IN-TRANS processes the attackers of the argument, x, relabelled to IN together with those attacked by x.
       </list-item>
       <list-item label="MC4.">
        During its execution, MC might find, at any stage, several illegally IN arguments. Each such argument serves as the basis for applying a transition rule. Now consider the case where every argument attacks all of the other arguments: this gives rise to {a mathematical formula}|A| illegally IN arguments (from the initial labelling, since every argument is attacked by an argument labelled IN) and thus there are {a mathematical formula}|A| transitions. After processing any one of these, {a mathematical formula}|A|−1 illegally IN arguments remain and so forth. Thus, MC could involve exploring {a mathematical formula}|A|! transitions. Algorithm 2, however, (and also DM) require at most {a mathematical formula}2|A| transition possibilities since each branch generates at most two successors. We note that {a mathematical formula}n!∼2O(nlogn) so that there is potentially a significant asymptotic difference in the size of the respective search space for MC in comparison with Algorithm 2 and DM.
       </list-item>
       <list-item label="MC5.">
        In order to ensure maximality (w.r.t. ⊆) conditions are met, MC eliminates from its candidate collection of preferred extensions, those admissible sets (already identified) which are subsets of the current set of arguments labelled IN: such an operation being carried out once no illegally IN argument remains in the labelling. As argued when comparing Algorithm 2 with DM, the former reports a newly discovered admissible set as maximal if the set of IN arguments is not a subset of any member in the preferred extensions found so far, i.e. those in the set of subsets PEXT. In short, Algorithm 2 tests candidates against (known) preferred extensions whereas MC tests candidates against admissible sets. Typically (on the basis that there are at least as many admissible sets in {a mathematical formula}(A,R) as there are preferred extensions) one would anticipate the decision whether or not to add a candidate S to those already identified to be computationally less onerous.
       </list-item>
       <list-item label="MC6.">
        Finally, MC incorporates a pruning mechanism which is different from the one used in Algorithm 2. In MC the search process stops and backtracks if the set of IN arguments is a subset of a previously identified admissible set. As would appear to be supported by the experimental evaluation presented in Section 4.3, the pruning approach applied in Algorithm 2 is more powerful.
       </list-item>
      </list>
     </section>
     <section label="4.3">
      Empirical evaluation of Algorithm 2
      <paragraph>
       All algorithms, new and previous ones, were implemented in C++. We ran all experiments on a Fedora (release 13) based machine with 4 processors (Intel core i5-750 2.67 GHz) and 16 GB of memory. To compare the algorithms we tracked the average elapsed time in seconds. The elapsed time was obtained by using the time command of Linux. For all trials, we set a time limit of 60 seconds for every execution.
      </paragraph>
      <paragraph>
       Fig. 4 shows the behavior of Algorithm 2 against the existing algorithms of [24], [45] and dynPARTIX, which is an implemented system that is based on a dynamic programming algorithm [32]. Given an af, dynPARTIX basically computes a tree decomposition of the af then the extensions are enumerated based on the tree decomposition. In [32] it was showed that dynPARTIX is fixed-parameter tractable such that its time complexity depends on the tree width of the given af while it is linear in the size of the af.{sup:1} Back to Fig. 4, out of 1000 runs DM algorithm encountered 220 timeouts, dynPARTIX encountered 149 timeouts, MC encountered 899 timeouts while Algorithm 2 solves all instances within 0.04 s. For those trials that exceeded the time limit we recorded 60 s as the elapsed time.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Algorithms for deciding skeptical and credulous acceptance
     </section-title>
     <paragraph>
      In deciding acceptance, it might be desirable to produce some kind of proof (i.e. explanation) as to why an argument is credulously accepted. Thus, we might say that a credulous proof of a given argument is made up of an admissible set containing the argument in question.
     </paragraph>
     <paragraph>
      In order to define more rigorously what constitutes a proof of credulous acceptance we start by recalling some useful terminology. We say that an argument x is reachable from an argument y if and only if there is a directed path from y to x. For example, consider the af depicted in Fig. 5 where {a mathematical formula}A={b,c,d,e,f,g} and {a mathematical formula}R={(b,c),(b,e),(c,d),(d,e),(e,f),(f,g),(g,f)}. In Fig. 5f is reachable from c through the directed path {a mathematical formula}〈(c,d),(d,e),(e,f)〉 while c is not reachable from f.
     </paragraph>
     <paragraph label="Definition 5">
      Credulous proofLet {a mathematical formula}(A,R) be an af, {a mathematical formula}S⊆A be an admissible set containing x s.t. for every {a mathematical formula}z∈S, x is reachable from z. Then, S is a credulous proof for x.
     </paragraph>
     <paragraph>
      Algorithm 3 determines a credulous proof of an argument (should such exist). This algorithm is a modification of Algorithm 2 whereby instead of finding all preferred extensions we try to find only an admissible set containing the argument in question. In summary, with respect to deciding the credulous acceptability of an argument, p say, Algorithm 3 makes use of six labels: PRO (short for proponent), OPP (short for opponent), UNDEC, OUT, MUST_OUT and BLANK. An argument x is labelled PRO to indicate that x might be in an admissible set and p is reachable from x. An argument y is labelled OUT if and only if y is attacked by a PRO argument. The MUST_OUT label identifies arguments that attack PRO arguments. An argument y is labelled OPP if and only if y is attacked by a PRO argument and y attacks a PRO argument. An argument y is labelled UNDEC to signal that y cannot be in an admissible set with the current PRO arguments. The BLANK label is the default label for all arguments. The precise usage of these labels is defined in Algorithm 3.
     </paragraph>
     <paragraph>
      The basic notion of Algorithm 3 is to change argumentsʼ labels iteratively according to the labelling scheme outlined earlier until there is no argument remaining that is labelled MUST_OUT. At this point, PRO arguments make up a credulous proof for p: PRO arguments capture the admissible set containing p. Referring to the af in Fig. 5, {a mathematical formula}{b,f} is a credulous proof for f, see Fig. 6 that demonstrates how Algorithm 3 works. We establish now the soundness and completeness of Algorithm 3.
     </paragraph>
     <paragraph label="Proposition 2">
      Let{a mathematical formula}H=(A,R)be anafand{a mathematical formula}x∈A. Then:
     </paragraph>
     <list>
      <list-item label="1.">
       IfAlgorithm 3reports true given{a mathematical formula}(H,x)using{a mathematical formula}then the set T is admissible and{a mathematical formula}x∈T.
      </list-item>
      <list-item label="2.">
       If x is credulously accepted thenAlgorithm 3reports a credulous proof, i.e. a set{a mathematical formula}
      </list-item>
     </list>
     <paragraph label="Proof">
      To prove both parts, we need to show that {a mathematical formula}{y:μ(y)=PRO} which we denote by S, is admissible. To establish that S is conflict free, assume that there exist {a mathematical formula}z,y∈S with {a mathematical formula}(z,y)∈R. If z is labelled PRO prior to y, then y would be labelled OUT; similarly if y were labelled PRO before z then z would be labelled OPP. It follows that {a mathematical formula}μ(y)=μ(z)=PRO implies neither {a mathematical formula}(y,z) nor {a mathematical formula}(z,y) can be in R. To show that for all {a mathematical formula}y∈S,y is acceptable w.r.t. S, suppose we have some {a mathematical formula}y∈S and {a mathematical formula}z∈{y}− with which no {a mathematical formula}w∈S has {a mathematical formula}(w,z)∈R. Consequently, z has to be labelled MUST_OUT (lines 15 and 6). This, however, contradicts S being reported as a credulous proof for x via lines 25 and 14: this report is given if and only if there is no {a mathematical formula}w∈A for which {a mathematical formula}μ(w)=MUST_OUT.  □
     </paragraph>
     <paragraph>
      Regarding the decision problem of skeptical acceptance, recall that an argument x is skeptically accepted if and only if every preferred extension contains x. We modified Algorithm 2 to Algorithm 4 in order to decide whether an argument x is skeptically accepted. Firstly, Algorithm 4 looks for a credulously accepted argument that attacks x. If there exists such an attacker then Algorithm 4 concludes that x is not skeptically accepted. Otherwise, Algorithm 4 searches for a preferred extension, S, such that {a mathematical formula}x∉S∪S+. If such an extension is found then x is not skeptically accepted, or else x is skeptically accepted.
     </paragraph>
     <paragraph>
      Algorithm 4 is somewhat self-explanatory. See, however, Fig. 7 showing how the algorithm works in confirming the skeptically accepted status of the argument d in the af depicted in Fig. 5. Note that Fig. 7 grows from left to right. The soundness/completeness proof of Algorithm 4 would be in two parts. The first part, which directly follows, is about showing that a given argument is not skeptically accepted if the argument is attacked by a credulously accepted argument, while the second part would be identical to the proof of Algorithm 2.
     </paragraph>
    </section>
    <section label="6">
     The advantage of Algorithms 3 and 4
     <paragraph>
      As we have already done with respect to algorithms for enumerating extensions, we now compare the algorithms introduced in the preceding section with previous methods, specifically those of Cayrol et al. [19], Thang et al. [56], and Verheij [58].
     </paragraph>
     <section label="6.1">
      <section-title>
       The algorithms of Cayrol et al.
      </section-title>
      <paragraph>
       We start by highlighting the main differences between Algorithm 3 and the algorithm of Cayrol et al. [19] (abbreviated by CAYCred) for the decision problem of credulous acceptance.
      </paragraph>
      <paragraph>
       The approach adopted in CAYCred makes use of three labels: PRO, OPP and OUT. Our use of PRO &amp; OPP is similar to that of CAYCred, however, there are some differences regarding the use of the label OUT. CAYCred labels an argument x OUT on three occasions: if x is attacked by an argument labelled PRO; if x attacks an argument labelled PRO; and if x is incompatible as a member of an admissible set containing all of the arguments, currently, labelled PRO. As we demonstrate, it is more efficient to distinguish these cases via different labels. This, in effect, is what happens in Algorithm 3: the OUT label is reserved for arguments attacked by PRO labelled arguments; MUST_OUT for those attacking PRO labelled arguments; and UNDEC for the third case. To see the potential gains from our labelling scheme consider the following. The method CAYCred stops exploring further and backtracks if there exists an {a mathematical formula}x∈A which attacks an argument labelled PRO and for every attacker of x is labelled OUT. This halting condition is checked every time an argument is labelled PRO. Conversely, Algorithm 3 backtracks if an argument labelled MUST_OUT is not attacked by an argument labelled BLANK: this condition being checked every time an argument is labelled MUST_OUT. Searching for an argument attacking a PRO labelled argument in CAYCred runs in the order of {a mathematical formula}|R| while looking for a MUST_OUT labelled argument in Algorithm 3 runs in the order of {a mathematical formula}|A|. As we have previously noted, usually {a mathematical formula}|R|&gt;|A|.
      </paragraph>
      <paragraph>
       A further, significant difference is that CAYCred selects an argument to be PRO arbitrarily while Algorithm 3 uses a heuristic rule to choose which BLANK argument to expand the search structure. So, the expected running time is improved: empirical confirmation being provided by the experiments reported in Section 6.4. As to the UNDEC label, the objective is to discriminate, and then to avoid, those arguments that previously failed to be in an admissible set with the current PRO arguments. Indeed, the merit of the UNDEC label is also captured by CAYCred through the OUT label.
      </paragraph>
      <paragraph>
       Regarding the decision problem of skeptical acceptance, the idea of the algorithm from Cayrol et al. [19] (CAYSkep for short) is based on an argument x not being skeptically accepted if at least one of two conditions hold:
      </paragraph>
      <list>
       <list-item label="CAS1">
        x is attacked by a credulously accepted argument z (with the status of z decided by using CAYCred).
       </list-item>
       <list-item label="CAS2">
        There is an admissible set that does not contain x and that cannot be expanded into one that does contain it.
       </list-item>
      </list>
      <paragraph>
       Otherwise, x is skeptically accepted provided that there exists an admissible set that contains x (notice that, given the admissibility of the empty set and CAS2, it suffices to find just one admissible set containing x to ensure – CAS1 and CAS2 having reported negatively – that x is skeptically accepted).
      </paragraph>
      <paragraph>
       Regarding CAS1 we have already remarked upon the distinctions being CAYCred and Algorithm 3. With respect to CAS2, CAYSkep uses two labels IN and OUT, and so, an argument y is labelled IN to indicate that y might be in an admissible set. We have, in our discussion of CAYCred, described its use of the OUT label. To check whether or not {a mathematical formula}S⊆A is an admissible set that can be expanded into one that contains the argument in question, CAYSkep verifies that S is maximally admissible in {a mathematical formula}{y∈A|λ(y)∈{IN,OUT}}. Such verification is potentially expensive, and thus, it is avoided by Algorithm 4. Recall that Algorithm 4 decides that an admissible set is maximal if and only if the set is not a subset of any previously decided preferred extension.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       The algorithms of Thang et al.
      </section-title>
      <paragraph>
       The algorithm of Thang et al. [56] (abbreviated by THCred) for the decision problem of credulous acceptance is based on classifying arguments into four sets: P, O, SP and SO. As an initial step, the argument in question is added to SP and P while O and SO are empty. Next, the following three operations are applied iteratively s.t. in every iteration one or more tuples of the form {a mathematical formula}(P,O,SP,SO) might be generated.
      </paragraph>
      <list>
       <list-item label="ThOp1">
        If there is some {a mathematical formula}x∈P s.t. {a mathematical formula}SP∩{x}−=∅ then x is removed from P and every {a mathematical formula}y∈{x}−∖SO is added to O.
       </list-item>
       <list-item label="ThOp2">
        An argument x is added to SP and P if and only if {a mathematical formula}{x}+∩O≠∅ and {a mathematical formula}x∉O∪SO.
       </list-item>
       <list-item label="ThOp3">
        An argument y is moved from O to SO if {a mathematical formula}{y}−∩SP≠∅.
       </list-item>
      </list>
      <paragraph>
       Hence, at any time more than one tuple of {a mathematical formula}(P,O,SP,SO) may be relevant. This reflects THCred exploration of the admissibility of different subsets of A. THCred reports that the argument in question is credulously accepted if and only if there exists a tuple {a mathematical formula}(P,O,SP,SO) s.t. P and O are both empty. Otherwise, the argument is not credulously accepted. To compare with Algorithm 3, we analyze three issues.
      </paragraph>
      <list>
       <list-item label="ThCr1">
        The algorithm might reconsider an argument x to be added to SP and P although x may already have been identified as failing to be in an admissible set with the same, current arguments in SP. In contrast, Algorithm 3 avoids this possibility through its use of the UNDEC label.
       </list-item>
       <list-item label="ThCr2">
        THCred might add arguments to O despite these being attacked by arguments in SP. This, in principle, could be costly as THCred might unnecessarily test further arguments to be added to SP and P as counterarguments to those newly added to O. Again, Algorithm 3, avoids this situation through its use of the OUT label so that as soon as an argument is labelled PRO, every argument that it attacks is labelled OUT. Recall that Algorithm 3 explores arguments labelled MUST_OUT, whereas those labelled OUT are disregarded due to their being attacked by arguments labelled PRO.
       </list-item>
       <list-item label="ThCr3">
        THCred does not exploit any heuristics or pruning machinery to accelerate the search process.
       </list-item>
      </list>
      <paragraph>
       Regarding skeptical acceptance, the algorithm of Thang et al. [56] (THSkep for short) relies for its correctness on the concept of a complete base (for x). A base, {a mathematical formula}B for x being a set of admissible sets {a mathematical formula}B={S1,S2,…,Sn} each of which contains x, and such that for every preferred extension, E containing x, there is {a mathematical formula}S∈B with {a mathematical formula}S⊆E. A base {a mathematical formula}B being complete if for every preferred extension, E, there is some {a mathematical formula}S∈B for which {a mathematical formula}S⊆E. The process of verifying skeptical acceptance of x is shown to be equivalent to identifying a complete base for x. Thus the skeptical proof of x consists of such a base and the efficiency of THSkep is determined not only by the performance of THCred since THSkep depends on THCred in searching for admissible sets but also on the efficiency with which a candidate collection can be validated as a complete base: this approach is not that adopted within Algorithm 4.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       The algorithm of Verheij
      </section-title>
      <paragraph>
       Verheij [58] presented an algorithm for the credulous acceptance problem, which we denote VERCred. This classifies arguments into two sets J and D. Initially, J contains the argument in question while D is empty. Then, two functions are repeatedly executed on every pair of {a mathematical formula}(J,D). The first function is{a mathematical formula} The second function {a mathematical formula}ExtendByDefence((J,D)) is given by,{a mathematical formula} Next, if there exist {a mathematical formula}(J′,D′) and {a mathematical formula}(J,D) such that {a mathematical formula}J′=J and {a mathematical formula}D′=D then the argument in question is credulously proved by {a mathematical formula}(J′,D′). At any stage if no new pair {a mathematical formula}(J′,D′) is produced from applying the two functions on all current pairs of {a mathematical formula}(J,D) then the argument is not accepted. To evaluate the performance of Verheijʼs approach in contrast to Algorithm 3 we consider five efficiency issues.
      </paragraph>
      <list>
       <list-item label="V1.">
        The cost of finding a minimal defense set {a mathematical formula}J′ against the arguments in D, see the definition of ExtendByDefence earlier. This is not a factor in Algorithm 3.
       </list-item>
       <list-item label="V2.">
        VERCred might extend D by adding superfluous arguments already attacked by arguments in J and, in consequence, this might reduce the efficiency of computing {a mathematical formula}J′: more arguments in D could lead to more possible defense sets, thus finding a minimal defense set {a mathematical formula}J′ becomes harder. In Algorithm 3 this situation is handled by using the OUT label designating arguments that are attacked by PRO arguments, and thus no further action is needed.
       </list-item>
       <list-item label="V3.">
        VERCred might extend J by adding arguments that had already failed to form an admissible set with the current arguments in J. As noted before, Algorithm 3 use of the UNDEC label prevents this.
       </list-item>
       <list-item label="V4.">
        VERCred expands the search space on breadth-first basis, and so, the space complexity of VERCred is prohibitive. This is because VERCred should store more than one node (i.e. a pair of ({a mathematical formula}J,D)) at the same time. As Algorithm 3 is a depth-first search procedure it needs to store only one labelling at a time which means the space complexity is linear in the size of {a mathematical formula}|A|.
       </list-item>
       <list-item label="V5.">
        Again, VERCred, does not employ heuristics or pruning techniques to enhance the search progression.
       </list-item>
      </list>
     </section>
     <section label="6.4">
      Empirical evaluation: Algorithms 3 and 4
      <paragraph>
       Regarding the credulous acceptance problem, Fig. 8 shows the behavior of Algorithm 3 against the existing algorithms of [19], [56], [58]. Out of 1000 runs, VERCred algorithm [58] encountered 987 timeouts, THCred [56] encountered 980 timeouts. All these timeouts are plotted within the figure as 60 s: the time limit set for the experiments.
      </paragraph>
      <paragraph>
       Regarding the skeptical acceptance problem, Fig. 9 shows the behavior of Algorithm 4 against the existing algorithms of [19], [56]. Referring to Fig. 9, THSkep algorithm [56] could not solve any af within the 60-s time limit. Timeouts of THSkep are presented within the figure as 60 s.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Labelling algorithms for value based argument frameworks
     </section-title>
     <paragraph>
      To consider mechanisms with which to model persuasive argument in practical reasoning Bench-Capon [8] extends Dungʼs framework to accommodate the notion of arguments promoting “social values”. Bench-Caponʼs value based argumentation framework (vaf) is a 4-tuple {a mathematical formula}(A,R,V,η) where A is a set of arguments, {a mathematical formula}R⊂A×A is a binary relation, V is a non-empty set of social values, {a mathematical formula}η:A→V maps (abstract) arguments in A to values in V. A total ordering, α of V is referred to as a specific audience. Given a specific audience, α, we refer to {a mathematical formula}(vi,vj)∈α as “{a mathematical formula}vi is preferred to {a mathematical formula}vj” or “{a mathematical formula}vi≻vj”. We denote the set of all specific audiences by {a mathematical formula}U. Audiences offer a means to distinguish attacks {a mathematical formula}(x,y)∈R which do not succeed as a consequence of expressed value priorities. Formally, we say x defeats y w.r.t. the audience α if and only if {a mathematical formula}(x,y)∈R and {a mathematical formula}(η(x),η(y))∈α. An argument x is acceptable for an audience α w.r.t. {a mathematical formula}S⊆A if and only if for every y that defeats x (w.r.t. α) there is some {a mathematical formula}z∈S that defeats y w.r.t. α.
     </paragraph>
     <paragraph>
      A set {a mathematical formula}S⊆A is conflict free for the audience α if and only if for all {a mathematical formula}x,y∈S it is not the case that x defeats y w.r.t. α. Similarly, S is admissible under α if and only if it is conflict free under α and every {a mathematical formula}x∈S is acceptable for α w.r.t. S. The α-preferred extensions are the maximal (w.r.t. ⊆) admissible under α sets. An argument x is objectively accepted if and only if for every α, x is in every α-preferred extension. On the other hand, x is subjectively accepted if and only if there some α for which x is in an α-preferred extension.{sup:2} For instance, consider the vaf in Fig. 10 where {a mathematical formula}A={b,c,d}, {a mathematical formula}R={(b,c),(c,d),(d,c)}, {a mathematical formula}V={v1,v2} and {a mathematical formula}η={(b,v1),(c,v2),(d,v2)}. The nodes in Fig. 10 are labelled by argument-value identifiers. If {a mathematical formula}v1≻v2 the {a mathematical formula}(v1≻v2)-preferred extension is {a mathematical formula}{b,d} otherwise the {a mathematical formula}(v2≻v1)-preferred extensions are {a mathematical formula}{{b,c},{b,d}}. Therefore, b is objectively accepted while c and d are subjectively accepted.
     </paragraph>
     <paragraph>
      In this section we approach the problem of α-preferred extension enumeration over all specific audiences while in Appendix A we offer algorithms that decide objective/subjective acceptance without requiring enumeration of all α-preferred extensions.
     </paragraph>
     <paragraph>
      Before treating this in depth, however, it is helpful to address some questions that have been raised regarding instantiating vafs in practical settings.
     </paragraph>
     <paragraph>
      Thus, Prakken [54], [53] identifies some concerns with respect to preference-handling in the preference-based af (paf) formalism proposed by Amgoud and Cayrol [1]. It has even been claimed by Caminada and Wu [18] that there is a “consistency problem of value-based argumentation” [18, p. 64] requiring resolution. The basis for this claim being the conclusions that can, according to the authors, be drawn from the example presented as [18, Fig. 2, p. 62] by applying value-based semantics.
     </paragraph>
     <paragraph>
      Given that this example has often been raised as a potential drawback of reasoning via vafs, it is worth revisiting. In fact, we believe that the example fails to offer a sound demonstration of “inconsistency in vaf reasoning”. We will now justify our assertion by examining the example presented in [18] in more detail.
     </paragraph>
     <paragraph>
      The system considered in [18, Fig. 2] is reproduced here in Fig. 11.
     </paragraph>
     <paragraph>
      We note that, for reasons which are expanded upon subsequently, we treat this example in purely abstract terms, rather than as arising from the specific scenario proposed in [18].
     </paragraph>
     <paragraph>
      In this example, {a mathematical formula}A={A1,A2,…,A9}, the attacks involving the pairs{a mathematical formula} are symmetric and the remaining attacks in R are{a mathematical formula} Interpreted as a vaf, [18] ascribes the same value to each of {a mathematical formula}A4, {a mathematical formula}A5 and {a mathematical formula}A6. The values promoted by the remaining arguments are all distinct (so that {a mathematical formula}|V|=7). Now the base (i.e. value-free) af is described as resulting through the following set of rules in which → defines a “strict” rules and ⇝ defines a “defeasible” rule.{sup:3}{a mathematical formula} Let us first consider this framework simply in terms of the sub-structure {a mathematical formula}〈A,R〉, that is to say in terms of the standard Dung af semantics. As, correctly, stated in [18] the grounded extension is {a mathematical formula}{A1,A2,A3} and there are exactly three preferred extensions, namely the sets{a mathematical formula} In terms of the rules represented by the arguments, these correspond to three distinct sets of conclusions, i.e.{a mathematical formula} Within each, the collective conclusions are consistent.
     </paragraph>
     <paragraph>
      What happens if we now consider the influence of values and the semantics defined through specific audiences?
     </paragraph>
     <paragraph>
      According to [18], audiences which assert the primacy of {a mathematical formula}V1 (associated with {a mathematical formula}{A4,A5,A6}) all yield extensions which contain the arguments {a mathematical formula}{A1,A2,A3,A4,A5,A6} irrespective of the ordering of the other six values in V. Furthermore, depending on the relative importance attached by audiences to the (distinct) values of {a mathematical formula}A7, {a mathematical formula}A8, and {a mathematical formula}A9, this set {a mathematical formula}{A1,A2,A3,A4,A5,A6} can be extended to{sup:4}{a mathematical formula} Again, case (a) is a correct application of value-based reasoning.
     </paragraph>
     <paragraph>
      At this point in [18] it is claimed that the set of arguments {a mathematical formula}{A1,A2,A3,A4,A5,A6,A9} supports the (inconsistent) set of conclusions {a mathematical formula}{p1,p2,p3,p4,p5,p6,¬p6}as a consequence of applying the rules governing{a mathematical formula}A1 through {a mathematical formula}A9.
     </paragraph>
     <paragraph>
      This claim is fallacious: it interprets the rules governing, {a mathematical formula}A4 say, as they are originally expressed (describing conclusions that could be drawn from {a mathematical formula}A4 in the classical Dung af model), but overlooks the crucial fact that since the notion of specific audience now applies, the conclusions that can be drawn are affected. In total, the original rules, since, these do not reflect the consequences resulting by expressing value preferences require reformulation in order that such consequences are explicitly stated.
     </paragraph>
     <paragraph>
      For example, focusing on {a mathematical formula}A4: within the abstract framework this describes the defeasible rule {a mathematical formula}A1⇝p4. In the value-based setting, however, {a mathematical formula}A4 now describes:{a mathematical formula} That is to say,
     </paragraph>
     <paragraph>
      “The argument {a mathematical formula}A4 states that, if it is accepted, then it is either the case that {a mathematical formula}p4 is a (defeasible) consequence of accepting {a mathematical formula}A1 ({a mathematical formula}A1⇝p4) OR that the specific audience accepting {a mathematical formula}A4 regards the value {a mathematical formula}V1 as having greater importance than the value {a mathematical formula}V5 ({a mathematical formula}V1≻V5).”
     </paragraph>
     <paragraph>
      Now suppose we continue this rewriting process for the remaining rules. We then obtain:{a mathematical formula} For a more rigorous description, we ought to express the conclusions respecting possible value orderings as arguments in themselves. Such an approach is, of course, implicit within Modgilʼs work on extended afs from [44] and has been more directly investigated in Modgil and Bench-Caponʼs treatment of so-called Metalevel argumentation [46]. In [46] assertions that arise through expressing value preferences (such as those within this particular example), are, themselves, explicitly represented as nodes within the frameworks.
     </paragraph>
     <paragraph>
      Proceeding to consider what conclusions now follow from {a mathematical formula}{A1,A2,A3,A4,A5,A6,A9} using the reformulated rules we obtain:{a mathematical formula} This set of conclusions is consistent.
     </paragraph>
     <paragraph>
      We have expanded on this example in some detail for a number of reasons. Firstly, it should be noted that we are not claiming vaf based reasoning and semantics will always produce consistent conclusions. At best this issue, to our knowledge, remains open. It is the case, however, that one oft claimed demonstration of inconsistency (specifically [18]), is erroneous. In alleging that reasoning via vafs may raise doubts concerning whether “their collective conclusions will be consistent, or satisfy any other reasonable properties”, the example presented in [18], not only fails to take account of the interaction between topological structures and the rules by which such are generated, but also of the important fact that the structure of the rules themselves may require reformulation depending on the semantics germane to the framework. To summarize, if the ordering of values is a factor in the acceptability (or otherwise) of particular arguments then the rule basis (or other logical foundation) from which the framework was derived must embody the use of value in its specification. Finally we note that we are not dealing with some superficial dichotomy between “pure abstract argumentation” and the “logical contents of arguments”: we have considered, as noted earlier, an abstracted form of the example put forward in [18]. It is not difficult to see, however, that treating the literal scenario from [18] with respect to the required modifications to its rule-base would, again, dispel the illusion of “inconsistent conclusions”.
     </paragraph>
     <paragraph>
      We now present our methods for determining α-preferred extensions. We recall that a naive approach would enumerate all specific audiences leading to {a mathematical formula}|V|! running time. We develop a new approach that avoids forming all such audiences leading to improved expected running time. Our approach is presented by Algorithm 5, Algorithm 6, Algorithm 7, Algorithm 8.
     </paragraph>
     <paragraph label="Definition 6">
      Algorithm 5 builds total orders on V (that is, specific audiences) incrementally. For this purpose, we define {a mathematical formula}q:V→Z a mapping from social values to integers.{sup:5} Every time a social value is mapped to an integer by q (line 10), Algorithm 5 might call (line 14) Algorithm 6 and attempt to label an argument x IN: the effect of the value order encoded in q. In doing so, Algorithm 6 may then call (line 6) Algorithm 7. Algorithm 7 checks whether an argument, {a mathematical formula}y∈{x}−, labelled BLANK may be labelled OUT under q or not. That is to say whether, w.r.t. the audience described by q, y is defeated. Thus, Algorithm 7 might call (line 5) Algorithm 6 to decide whether a BLANK labelled attacker of y can be labelled IN or not. To avoid infinite recursion Algorithm 6, Algorithm 7 employ {a mathematical formula}W⊆A to hold processed arguments. In summary, every time q is incremented, Algorithm 6, Algorithm 7 together determine IN/OUT labels on BLANK arguments to reflect this change in q. Once no eligible social value is left unmapped by q (line 8 of Algorithm 5), Algorithm 5 calls (line 17) Algorithm 8 to find the α-preferred extensions under the value order (α) encoded by q. Algorithm 8 is almost identical to Algorithm 1 with one exception related to the defeat notion of vafs. This requires us to define a transition rule – IN-TRANS-vafs – for Algorithm 8 instead of IN-TRANS that is used by Algorithm 1. IN-TRANS-vafs transition ruleLet {a mathematical formula}(A,R,V,η) be a vaf, {a mathematical formula}x∈A with {a mathematical formula}μ(x) be BLANK, and {a mathematical formula}q:V→Z. The IN-TRANS-vafs({a mathematical formula}x,q) transition rule is defined by the following ordered steps:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}μ′←μ;
      </list-item>
      <list-item label="2.">
       {a mathematical formula}μ′(x)←IN;
      </list-item>
      <list-item label="3.">
       forall{a mathematical formula}y∈{x}+:q(η(x))⩽q(η(y))do{a mathematical formula}μ′(y)←OUT;
      </list-item>
      <list-item label="4.">
       forall{a mathematical formula}z∈{x}−:μ′(z)≠OUT and q(η(z))⩽q(η(x))do{a mathematical formula}μ′(z)←MUST_OUT;
      </list-item>
      <list-item label="5.">
       return {a mathematical formula}μ′.
      </list-item>
     </list>
     <paragraph>
      Fig. 12 shows how the algorithms work on the framework of Fig. 10. A benefit of {a mathematical formula}q:V→Z defined in Algorithm 5, we believe, is that building value orders on V incrementally by using q improves the efficiency of computing α-preferred extensions. To see why, notice that q does not map the social values that are promoted by OUT labelled arguments because these values are irrelevant in deciding the labels of the remaining BLANK arguments. Since the example of Fig. 12 does not show the gain of q we present Fig. 13 that shows how the algorithms work on another vaf. In this example the algorithms decide the α-preferred extensions in four stages corresponding to q as:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} In contrast, working on a pre-computed set of all specific audiences enforces 6 total orders which necessitates 6 stages. More specifically, referring to Fig. 13 the total orders: {a mathematical formula}v1≻v2≻v3 and {a mathematical formula}v1≻v3≻v2 would produce the same α-preferred extensions. Noting that as {a mathematical formula}v1 is the most preferred value then the argument c is OUT and hence the relative position of {a mathematical formula}v2 is unimportant. Thus, the value order {a mathematical formula}v1≻v2≻v3 is not critical and can be ignored. This is exactly what our approach does where Algorithm 5 does not build a function q to embody {a mathematical formula}v1≻v2≻v3. Similarly, Algorithm 5 does not develop a function q to represent the value order {a mathematical formula}v2≻v3≻v1 indicating that the order of {a mathematical formula}v3 is not critical: {a mathematical formula}v3 is associated with only OUT arguments (the argument d in this example). To confirm the benefit of q experimentally we generated instances of vafs randomly by setting attacks between arguments with a probability of 0.1 where each instance has 30 arguments. For each {a mathematical formula}|V|∈{7,8,9,10,11} we report in Table 1 the average number of processed total value orders in an execution of 100 instances. We turn now to check the soundness and completeness of our approach. To accomplish this let us first define the set of critical total value orders, denoted by {a mathematical formula}U′, which is basically a subset of the set of all specific audiences {a mathematical formula}U. In fact, {a mathematical formula}U′ is the set of total orders that Algorithm 5 investigates for enumerating preferred extensions as we will establish later.
     </paragraph>
     <paragraph label="Definition 7">
      Critical value ordersLet {a mathematical formula}H=(A,R,V,η) be a vaf and {a mathematical formula}U denote the set of all specific audiences over V. Then the set of critical total value orders, {a mathematical formula}U′, is{a mathematical formula}
     </paragraph>
     <paragraph>
      Next we verify that the set of all preferred extensions under the critical value orders {a mathematical formula}U′ correspond to the set of all preferred extensions under all specific audiences {a mathematical formula}U.
     </paragraph>
     <paragraph label="Proposition 3">
      Let{a mathematical formula}(A,R,V,η)be avaf, PREF be the set of all preferred extensions w.r.t. all specific audiences in{a mathematical formula}U,{a mathematical formula}PREF′be the set of all preferred extensions w.r.t. the set of critical total value orders{a mathematical formula}U′. Then{a mathematical formula}PREF=PREF′.
     </paragraph>
     <paragraph label="Proof">
      Assume there exists {a mathematical formula}T∈PREF:T∉PREF′. In this case{a mathematical formula} By definition of {a mathematical formula}U and {a mathematical formula}U′{a mathematical formula} Thus,{a mathematical formula} Contradiction.  □
     </paragraph>
     <paragraph>
      Now we establish the soundness and completeness of Algorithm 5. Specifically, we show that Algorithm 5 develops a mapping {a mathematical formula}q:V→Z for every critical total value order.
     </paragraph>
     <paragraph label="Proposition 4">
      Let{a mathematical formula}(A,R,V,η)be avafand{a mathematical formula}U′be the set of all critical total value orders. Then:
     </paragraph>
     <list>
      <list-item label="1.">
       for every{a mathematical formula}q:V→Zconstructed byAlgorithm 5,{a mathematical formula}∃p∈U′:∀vi,vj∈V:q(vi)⩽q(vj),(vi,vj)∈p.
      </list-item>
      <list-item label="2.">
       {a mathematical formula}∀p∈U′,Algorithm 5constructs{a mathematical formula}q:V→Zsuch that{a mathematical formula}∀vi,vj∈V:(vi,vj)∈p,q(vi)⩽q(vj).
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Assume{a mathematical formula} By Algorithm 5, lines 12 and 14{a mathematical formula} By Proposition 5 (which basically states the conditions under which an argument is labelled IN or left BLANK by Algorithm 6) and after simplification{a mathematical formula} This contradicts the definition of {a mathematical formula}U′ (Definition 7): recall that {a mathematical formula}U′ contains total value orders including those which satisfy the previous implication.
       </list-item>
       <list-item label="2.">
        Assume that{a mathematical formula} By definition of {a mathematical formula}U′{a mathematical formula} By Proposition 5, x will be labelled IN or it stays BLANK.By Algorithm 5 (lines 5, 8 and 10), there exists {a mathematical formula}q(vi)=1. Contradiction. □
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      In the following we examine the soundness and completeness of Algorithms 6 and 7. In particular, we show that if Algorithm 6 labels an argument, x, IN w.r.t. some {a mathematical formula}q:V→Z then x is in every preferred extension under the audience corresponding to q. Similarly, we demonstrate that if Algorithm 6, Algorithm 7 label an argument x OUT w.r.t. some mapping {a mathematical formula}q:V→Z then x does not belong to any preferred extension under the audience represented by q.
     </paragraph>
     <paragraph label="Proposition 5">
      Let{a mathematical formula}(A,R,V,η)be avaf,{a mathematical formula}μ(x)=BLANKand{a mathematical formula}q:V→Zformed byAlgorithm 5. Then:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}μ(x)←INunder q byAlgorithm 6if and only if{a mathematical formula}
      </list-item>
      <list-item label="2.">
       {a mathematical formula}μ(x)←OUTunder q byAlgorithm 6 (respectivelyAlgorithm 7) if and only if{a mathematical formula}
      </list-item>
      <list-item label="3.">
       If neither (1) nor (2) hold,{a mathematical formula}μ(x)=BLANK.
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Assume x is labelled IN under q by Algorithm 6 and{a mathematical formula} By Algorithm 6 lines 4, 7 and 12{a mathematical formula} Contradiction.
       </list-item>
       <list-item label="2.">
        Assume x is labelled OUT under q by Algorithm 6 (respectively Algorithm 7) and{a mathematical formula} By Algorithm 6 line 15 (respectively Algorithm 7 line 7){a mathematical formula} Contradiction.
       </list-item>
       <list-item label="3.">
        Immediate from (1) and (2). □
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      Lastly, the following proposition asserts that Algorithm 8, which enumerates α-preferred extensions, is sound and complete.
     </paragraph>
     <paragraph label="Proposition 6">
      Let{a mathematical formula}(A,R,V,η)be avaf,{a mathematical formula}q:V→Z, and let PEXT be the set of subsets returned byAlgorithm 8under q. Then,
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}∀T∈PEXT,{a mathematical formula}∃S⊆A:Sis a preferred extension under{a mathematical formula}q∧S=T, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}∀S⊆A, if S is a preferred extension under q then{a mathematical formula}∃T∈PEXT:S=T.
      </list-item>
     </list>
     <paragraph label="Proof">
      Follows from Proposition 1 and similar structure of Algorithm 8 and Algorithm 2.  □
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      We presented a new, implemented algorithm for enumerating preferred extensions in Dungʼs model of argumentation. We have shown that the new algorithm computes extensions faster than the existing algorithms presented in [24], [45]. From an applications point of view, it stands to reason that among other factors the running time performance of an agent powered by argument-based reasoning machinery is bounded to the efficiency of the implemented algorithms of the respective reasoning problems. In that sense, our main concern in this paper was to develop concrete, efficient algorithms for the decision problems related to the preferred semantics. Although the main focus in the paper was on preferred semantics, we believe that this work influences the development of algorithms for other argumentation semantics where the notions: state transition, argument selection tactics and search space pruning strategies are all relevant to other semantics. For example, if we drop line 20 (i.e. the maximality check) from Algorithm 2 then we get a procedure for listing all admissible sets. Also, if we modify the condition of line 25 (in Algorithm 2) to{a mathematical formula} then we get a procedure for listing all stable extensions. We note further evidence that developing an algorithm for an argumentation semantics might lead to building algorithms for other semantics which is the algorithms introduced by Caminada in [15], [16] for finding semi-stable, respectively stage, extensions. Indeed, these two algorithms can be viewed as a reproduction of the algorithm of Modgil and Caminada [45] for preferred extension enumeration.
     </paragraph>
     <paragraph>
      As we stated earlier, argumentation semantics can be defined by using either the labelling notion or the extension notion. However, this paper presents new algorithms that make use of labellings as an algorithmic vehicle rather than introducing new labelling-based semantics. In fact, Doutre and Mengin [24] developed their labelling-based algorithm without elaborating labelling-based semantics. On the other hand, the algorithm of Modgil and Caminada [45] complies with the labelling-based semantics of Caminada and Gabbay [17]. As it has been illustrated throughout the paper, the specification of our algorithms fit neatly into the labelling theory of Caminada and Gabbay.
     </paragraph>
     <paragraph>
      Likewise, we presented algorithms that decide the credulous and skeptical acceptance problems without explicitly enumerating all preferred extensions. An added feature of the developed algorithms is the production of proofs as to why an argument is accepted. We have shown, analytically and empirically, that our algorithms are more efficient than the existing algorithms presented in [19], [56], [58]. Some authors call the algorithms that yield proofs “dialectical proof procedures” referring to the fact that a proof of an accepted argument might be, informally speaking, defined by the arguments put forward during a dialog between two parties. In fact, argumentation semantics can be defined by using the dialog notion (see e.g. [36], [59], [30], [43], [13]). Hence, Cayrol et al. [19] describe dialogs under preferred semantics as a means for presenting their algorithms. However, Thang et al. [56] make use of so-called “dispute trees” to pave the way for introducing their algorithms, while Verheij [58] defines his algorithm by employing the notion of “labellings” rather than specifying formal dialogs. Furthermore, argument-based dialogs have been extensively studied as a backbone for interactions between agents in multi-agent systems, see e.g. [42] for an overview.
     </paragraph>
     <paragraph>
      Broadly, in the literature there are several works on computing decision problems in afs. In [60] Vreeswijk discussed algorithmically the efficiency of deciding minimally admissible sets. In [25] Doutre and Mengin specified dialectical proofs for skeptically accepted arguments under preferred semantics. Their dialog process is basically centered around the following property: given an argument x, then x is skeptically accepted if and only if{a mathematical formula} In [25] Doutre and Mengin did not give an algorithm for constructing their dialectical proof. However, adopting a naive algorithm for such proof would be prohibitive since the running time complexity in this case will be in the order of {a mathematical formula}22|A| while our algorithm for skeptical acceptance runs in the order of {a mathematical formula}2|A|.
     </paragraph>
     <paragraph>
      Reviewing further related works in the context of afs, in [39] approximating argumentation semantics was evaluated versus exact computations, whereas the experiments presented in [7] evaluated the effect of splitting an af on the computation of the preferred extensions. The work of [40] shows how to partially re-evaluate the acceptance of arguments if R changes. From a computational theoretical perspective, the decision problems of skeptical and credulous acceptance under preferred semantics are believed to be intractable, see e.g. [23], [28], [52]. Another line of research concerns encoding decision problems of afs into other formalisms and then solving them by using a respective solver, see for example [12], [48], [33], [2], [31], [20].
     </paragraph>
     <paragraph>
      Additionally, we have established the usability of our algorithms in the context of vafs. In [9] a dialog framework was developed for vafs. This dialectical framework basically extends the framework of Cayrol et al. [19]. Thus, the distinctions made in Section 6 in which we compare our algorithms with the algorithms of Cayrol et al. applies equally in showing differences between the dialog processes of [9] and our algorithms for acceptance in vafs. Recall that our algorithms for vafs use Algorithms 3 and 4 for credulous and skeptical acceptance respectively. In addition, the developments in [9] for vafs were made with the assumption that directed cycles of arguments involve at least two distinct values. As we stated earlier, we do not retain this assumption for developing the algorithms for vafs.
     </paragraph>
     <paragraph>
      We consider now an approach to rewriting a vaf into an af[44]. In general, this approach adds an argument to A for every specific audience {a mathematical formula}α∈U and thus A will grow by {a mathematical formula}|V|!. In consequence, any algorithm (e.g. Algorithm 1) working on the target af will run in the order of {a mathematical formula}2|A|+|V|! while our approach (i.e. Algorithm 5, Algorithm 6, Algorithm 7, Algorithm 8 altogether working on the original vaf) runs in the order of {a mathematical formula}|V|!2|A| which is more efficient. More importantly, recall the profit of q that might induce steps fewer than {a mathematical formula}|V|! as we illustrated earlier. The bottom line is, our approach is faster than any other mechanism that would consider every specific audience {a mathematical formula}α∈U while our algorithms only consider critical audiences {a mathematical formula}U′⊆U as stated by Proposition 4, which is a key contribution of our algorithms. Equally, our algorithms establish an efficient method for encoding total orders over V such that the space complexity is upper bounded to the number of values (i.e. {a mathematical formula}|V|) rather than to the number of all total value orders (i.e. {a mathematical formula}|V!|), which is the case if a naive approach is adopted.
     </paragraph>
     <paragraph>
      We close this section by listing some further related works in the context of vafs. The computational complexity of subjective and objective acceptance is studied in [28], [37], [38] while the algorithms of [29] and [49] decide the preferred extensions, respectively subjective/objective acceptance, under the assumption that directed cycles of arguments involve at least two distinct values. The work of [34] proposes an algorithm that translates vafs to neural networks.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Algorithms for the subjective and objective acceptance problems
     </section-title>
     <paragraph>
      Here we provide algorithms that decide subjective/objective acceptance without explicitly enumerating extensions of a vaf. Algorithm 9, Algorithm 10 (besides Algorithm 6, Algorithm 7) decide subjective acceptance while the Algorithm 11, Algorithm 12 (besides Algorithm 6, Algorithm 7) decide objective acceptance. In fact these algorithms are self-explanatory since they are alterations of Algorithm 3, Algorithm 4, Algorithm 5 as we specify in what follows. Firstly, note that Algorithm 9, Algorithm 11 are modified versions of Algorithm 5 for deciding subjective, respectively objective, acceptance. Secondly, we reform Algorithm 3 to get Algorithm 10 that works in conjunction with Algorithm 9 to decide the subjective acceptance problem. Thirdly, we change Algorithm 4 to get Algorithm 12 that works jointly with Algorithm 11 in deciding the objective acceptance problem.
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Further examples illustrating the new algorithms
     </section-title>
     <paragraph>
      This section intends to help the reader to envisage various aspects of the algorithms running on natural arguments. In particular, we present two different frameworks to give the reader a flavor of the argumentation enabled in specific domain applications: legal reasoning and moral debate.
     </paragraph>
     <paragraph label="Example 1">
      Legal reasoningThis is taken from [36], which is actually an adapted version from the original presentation in [35].Consider the following hypothetical exchange of allegations. The plaintiff (p) and the defendant (o) have both loaned money to Miller for the purchase of an oil tanker; which is the collateral for both loans. Miller has defaulted on both loans, and the practical question is which of the two lenders will first be paid from the proceeds of the sale of the ship. One subsidiary issue is whether the plaintiff perfected his security interest in the ship or not.
     </paragraph>
     <list>
      <list-item>
       p: My security interest in Millerʼs ship was perfected. A security interest in goods may be perfected by taking possession of the collateral, Uniform Commercial Code (UCC) Article 9. I have possession of Millerʼs ship.
      </list-item>
      <list-item>
       o: Ships are not goods for the purposes of Article 9.
      </list-item>
      <list-item>
       p: Ships are movable, and movable things are goods according to UCC Article 9.
      </list-item>
      <list-item>
       o: According to the Ship Mortgage Act, a security interest in a ship may only be perfected by filing a financing statement.
      </list-item>
      <list-item>
       p: The Ship Mortgage Act does not apply, since the UCC is newer and therefore has precedence.
      </list-item>
      <list-item>
       o: The Ship Mortgage Act is federal law, which has precedence over state law such as UCC.
      </list-item>
     </list>
     <paragraph>
      This discussion can be associated with the af in Fig. 14[36]. The question now is about whether the plaintiff perfected his security interest in the ship or not. In other words, is argument b of the plaintiff acceptable? (i.e. deciding the credulous acceptance of b). On the other hand, we might need to check whether the argument b can be unacceptable or not (i.e. deciding the skeptical acceptance of b). To conclude, Fig. 15, Fig. 16 show how to decide credulous (resp. skeptical) acceptance by using Algorithms 3 (resp. 4): argument b is credulously accepted while it is not skeptically accepted. Furthermore, one can get explanations as to why the argument b is acceptable (resp. unacceptable) from the arguments labeled PRO in Fig. 15 (resp. 16).
     </paragraph>
     <paragraph label="Example 2">
      Moral debateConsider the vaf in Fig. 17, which is obtained from the moral debate presented in [8] concerning the competing values of respect for life and respect for property. Before applying algorithms we present the debate as introduced in [8]. Hal, a diabetic, loses his insulin in an accident through no fault of his own. Before collapsing into a coma he rushes to the house of Carla, another diabetic. She is not at home, but Hal enters her house and uses some of her insulin. Was Hal justified, and does Carla have a right to compensation? The arguments are:
     </paragraph>
     <list>
      <list-item label="•">
       b: Hal is justified, since a person has a privilege to use the property of others to save their life.
      </list-item>
      <list-item label="•">
       c: It is wrong to infringe the property rights of another.
      </list-item>
      <list-item label="•">
       d: If, however, Hal compensates Carla, then Carlaʼs rights have not been infringed.
      </list-item>
      <list-item label="•">
       e: If Hal were too poor to compensate Carla, he should none the less be allowed to take the insulin, as no one should die because they are poor. Moreover, since Hal would not pay compensation if too poor, neither should he be obliged to do so, even if he can.
      </list-item>
      <list-item label="•">
       f: Hal is endangering Carlaʼs life.
      </list-item>
      <list-item label="•">
       g: Hal checks that Carla has abundant insulin before using it.
      </list-item>
      <list-item label="•">
       h: Carla does not have ample insulin.
      </list-item>
      <list-item label="•">
       i: Poverty is no defence for theft, that we prosecute the starving when they steal food.
      </list-item>
     </list>
     <paragraph>
      Note that fact is not literally a promoted social value but in [8] it was considered in η to emphasize that the respective argument is a fact and should always be given the highest preference (for all parties) over other arguments regardless of their associated values. Referring to Fig. 17, for the audience {a mathematical formula}fact≻life≻property, b is accepted as decided by Algorithm 10, which means Hal was justified to take insulin from Carlaʼs house because he checked that Carla has abundant insulin before using it (see argument g). Recall that c does not defeat b w.r.t. the audience {a mathematical formula}fact≻life≻property.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>