<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Methods for solving reasoning problems in abstract argumentation – A survey.
   </title>
   <abstract>
    Within the last decade, abstract argumentation has emerged as a central field in Artificial Intelligence. Besides providing a core formalism for many advanced argumentation systems, abstract argumentation has also served to capture several non-monotonic logics and other AI related principles. Although the idea of abstract argumentation is appealingly simple, several reasoning problems in this formalism exhibit high computational complexity. This calls for advanced techniques when it comes to implementation issues, a challenge which has been recently faced from different angles. In this survey, we give an overview on different methods for solving reasoning problems in abstract argumentation and compare their particular features. Moreover, we highlight available state-of-the-art systems for abstract argumentation, which put these methods to practice.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Argumentation is a highly interdisciplinary field with links to psychology, linguistics, philosophy, legal theory, and formal logic. Since the advent of the computer age, formal models of argument have been materialized in different systems that implement — or at least support — creation, evaluation, and judgment of arguments. However, until Dung's seminal paper on abstract argumentation[1], the heterogeneity of these approaches was severely hampering a strong and joint development of a field like “computational argumentation”. In fact, Dung's idea of evaluating arguments on an abstract level by taking only their inter-relationships into account, not only has been shown to underlie many of the earlier approaches for argumentation, but also uniformly captures several non-monotonic logics. Yet this second contribution located Argumentation as a sub-discipline of Artificial Intelligence [2]. The increasing significance of argumentation as a research area of its own has also been witnessed by the biennial COMMA Conference on Computational Models of Argument,{sup:1} which from the second meeting onwards provides sessions for software demonstrations of implemented systems, the IJCAI Workshop Series on Theory and Applications of Formal Argumentation (TAFA),{sup:2} the 2010 established Journal of Argument and Computation,{sup:3} or the Textbook on Argumentation in Artificial Intelligence[3].
     </paragraph>
     <paragraph>
      One particular feature of abstract argumentation frameworks is their simple structure. In fact, abstract argumentation frameworks are just directed graphs where vertices play the role of arguments and edges indicate a certain conflict between the two connected arguments. These argumentation frameworks are usually derived during an instantiation process (see, e.g., [4], [5]), where structured arguments are investigated with respect to their ability to contradict other such arguments; the actual notion of “contradicting” can be instantiated in many different forms (see, e.g., [6]). Having generated the framework in such a way, the process of “conflict-resolution”, i.e., the search for jointly acceptable sets of arguments, is then delegated to semantics which operate on the abstract level. Thus, semantics for argumentation frameworks have also been referred to as calculi of opposition[7].
     </paragraph>
     <paragraph>
      One direction of research in abstract argumentation was devoted to develop the “right” forms of semantics (see, e.g., [8], [9], [10] where properties for argumentation semantics are proposed and evaluated). This has lead to what G. Simari has called a “plethora of argumentation semantics”.{sup:4} Today there seems to be agreement within the community that different semantics suit different applications, hence many of them are in use for a variety of application domains.{sup:5} It is clear that this situation implies that successful systems for abstract argumentation are expected to offer not only a single semantics.
     </paragraph>
     <paragraph>
      The central role of abstract argumentation frameworks also boosted research on efficient procedures for this particular formalism. However, it was soon recognized that already these simple frameworks show high complexity (see, e.g., [12], [13], [14]); due to the link to non-monotonic logic and to logic programming in particular, this came without a huge surprise. Together with the fact that many different semantics exist, general implementation methods for abstract argumentation thus require
     </paragraph>
     <list>
      <list-item label="•">
       a certain level of generality, such that not only a single semantics can be treated; and
      </list-item>
      <list-item label="•">
       a sufficient level of efficiency to face the high inherent complexity of the problems at hand.
      </list-item>
     </list>
     <section>
      <section>
       <section>
        <section-title>
         Scope of the survey
        </section-title>
        <paragraph>
         In this article, we present a selection of evaluation methods for abstract argumentation which we believe to meet these requirements. We group these methods into two categories: the reduction approach and the direct approach.
        </paragraph>
        <paragraph>
         The underlying idea of the reduction approach is to exploit existing efficient software which has originally been developed for other purposes. To this end, one has to formalize the reasoning problems within other formalisms like constraint-satisfaction problems (CSP) [15], propositional logic [16] or answer-set programming (ASP) [17]. In this approach, the resulting argumentation systems directly benefit from the high level of sophistication today's systems for SAT (satisfiability in propositional logic) or ASP have reached. The reduction approach will be presented in detail in Section 3 of this article. Hereby, we will first focus on
        </paragraph>
        <list>
         <list-item label="•">
          SAT-based argumentation systems. This direction has been advocated by Besnard and Doutre [18], and later extended by means of quantified propositional logic [19], [20]. We will first discuss the theoretical underpinnings of this approach and then continue with an introduction to the CEGARTIX system [21] and the ArgSemSAT system [22], which both rely on iterative calls to SAT solvers for argumentation semantics of high complexity (i.e., being located on the second level of the polynomial hierarchy).
         </list-item>
         <list-item label="•">
          CSP-based approach. Reductions to CSP have been addressed by Amgoud and Devred [23] and Bistarelli and Santini [24], [25], [26], [27], [28]; the latter work led to the development of the ConArg system. We introduce the formalization of argumentation frameworks in terms of CSPs, where the arguments of the given framework represent the variables of the CSP with domains of 0 and 1. The constraints then depend on the specific semantics.
         </list-item>
         <list-item label="•">
          ASP-based approach. The use of this logic-programming paradigm to solve abstract argumentation problems has been initiated by several authors (the survey article by Toni and Sergot [29] provides a good overview). We focus here on the ASPARTIX approach [30] which in contrast to the aforementioned SAT methods relies on a query-based implementation where the argumentation framework to be evaluated is provided as an input database (from this point of view, the SAT or CSP methods can be seen as a compiler-like approach to abstract argumentation, while the ASP method acts like an interpreter). A large collection of such ASP queries is provided by the ASPARTIX system. We will discuss standard ways of ASP encodings, but also some recent methods which exploit advanced ASP techniques [31].
         </list-item>
        </list>
        <paragraph>
         In the remainder of Section 3 we shall present the concepts behind other reduction-based approaches, for instance, the equational approach as introduced by Gabbay in [32] and the reductions to monadic second order logic as proposed in [33].
        </paragraph>
        <paragraph>
         In Section 4, we collect methods and algorithms which have been developed from scratch (instead of using another formalism like SAT or ASP). The obvious disadvantage of this direct approach is due to the fact that existing technology cannot be directly employed. On the other hand, such argumentation-tailored algorithms ease the incorporation of short-cuts that are specific to the argumentation domain. In detail, we will discuss the following ideas:
        </paragraph>
        <list>
         <list-item label="•">
          The labeling approach[34], [35], [36], [37], [38] gives a more fine-grained handle on the status of arguments when evaluated w.r.t. semantics and also provides a solid basis for dedicated algorithms. We present two different proposals for implementing the enumeration of preferred extensions, one along the lines of [35] and another following [34] using improvements from [36]. Furthermore, we discuss an algorithm dedicated to credulous reasoning with preferred semantics following the work of [38]. Labeling-based algorithms have been materialized in the ArguLab system as well as in Verheij's CompArg system.
         </list-item>
         <list-item label="•">
          Characterizations via Dialogue Games. Here the acceptance status of an argument is given in terms of winning strategies in certain games on the argumentation framework. Typically such games are two-player games where one player, the proponent, argues in favor of the argument in question and a second player, the opponent, argues against it. Such games can be used to design algorithms [35], [39], which are employed in systems like Dungine and Dung-O-Matic.
         </list-item>
         <list-item label="•">
          Finally, we will take a look on dynamic programming approaches[40] which operate on decompositions of frameworks. Notably, the running times in this approach are not mainly dependent on the size of the given framework, but on a structural parameter. We focus on the parameter tree-width and the concept of tree decomposition. This method was first advocated by Dunne [41] and later realized in the dynPARTIX system [42].
         </list-item>
        </list>
        <paragraph>
         As already hinted above, many of the methods we present have found their way into an available software system. Therefore, we will not only explain these methods in this survey, but shall also give the interested reader pointers to concrete systems which can be used to experiment. Section 5 contains a comparison of the systems w.r.t. their features (e.g. supported semantics and reasoning problems) and the underlying concepts. Some of the systems have been evaluated and compared w.r.t. their performance (see e.g., [31], [36], [43], [44], [45]), but no exhaustive performance comparisons have been done so far. In fact, an organized competition comparable to the ones from the areas of SAT [46] or ASP [47] is planned to take place in 2015 for the first time [48].{sup:6} Thus, we abstain here from a systematic comparison of the systems' performance.
        </paragraph>
        <paragraph>
         To summarize, our goal is to introduce a selection of methods for evaluating abstract argumentation frameworks; we shall explain the key concepts in detail for selected semantics and give pointers to the literature for the remaining semantics or when it comes to more subtle aspects like optimization. Concerning abstract argumentation itself, we give a concise introduction in Section 2. For readers not familiar with abstract argumentation, we highly recommend the recent survey article by Baroni et al. [49].
        </paragraph>
        <paragraph>
         Since the focus of this article is on the evaluation of semantics for Dung's abstract argumentation framework, advanced systems including instantiation (e.g., ASPIC [50] and Carneades [51]), assumption-based argumentation [52], or systems based on defeasible logic [53] are out of the scope of this article.{sup:7} Likewise, we will not consider the vast collection of extensions to Dung's frameworks,{sup:8} like value-based [56], bipolar [57], extended [58], constrained [59], temporal [60], practical [61], and fibring argumentation frameworks [62], as well as argumentation frameworks with recursive attacks [63], argumentation context systems [64], and abstract dialectical frameworks [65]. We also exclude abstract argumentation with uncertainty or weights here; recent articles by Hunter [66] and respectively Dunne et al. [67] introduce these variants in detail.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      In this section we introduce (abstract) argumentation frameworks [1] and recall the semantics we study in this paper (see also [10], [49], [68]).
     </paragraph>
     <paragraph label="Definition 1">
      An argumentation framework (AF) is a pair {a mathematical formula}F=(A,R) where A is a set of arguments and {a mathematical formula}R⊆A×A is the attack relation. The pair {a mathematical formula}(a,b)∈R means that a attacks b. We say that an argument {a mathematical formula}a∈A is defended (in F) by a set {a mathematical formula}S⊆A if, for each {a mathematical formula}b∈A such that {a mathematical formula}(b,a)∈R, there exists a {a mathematical formula}c∈S such that {a mathematical formula}(c,b)∈R.
     </paragraph>
     <paragraph>
      An argumentation framework can be represented as a directed graph.
     </paragraph>
     <paragraph label="Example 1">
      Let {a mathematical formula}F=(A,R) be an AF with {a mathematical formula}A={a,b,c,d,e} and {a mathematical formula}R={(a,b), {a mathematical formula}(b,c), {a mathematical formula}(c,b), {a mathematical formula}(d,c), {a mathematical formula}(d,e), {a mathematical formula}(e,e)}. The corresponding graph representation is depicted in Fig. 1.
     </paragraph>
     <paragraph>
      A semantics for argumentation frameworks is defined as a function σ which assigns to each AF {a mathematical formula}F=(A,R) a set {a mathematical formula}σ(F)⊆2A of extensions.
     </paragraph>
     <paragraph>
      We consider for σ the functions naive, stb, adm, com, grd, prf, sem and stg which stand for naive, stable, admissible, complete, grounded, preferred, semi-stable and stage extensions, respectively. Towards the definition of these semantics we introduce a few more formal concepts.
     </paragraph>
     <paragraph label="Definition 2">
      Given an AF {a mathematical formula}F=(A,R), the characteristic function{a mathematical formula}FF:2A→2A of F is defined as {a mathematical formula}FF(S)={x∈A|x is defended by S}. For a set {a mathematical formula}S⊆A and an argument {a mathematical formula}a∈A, we write {a mathematical formula}S↣Ra (resp. {a mathematical formula}a↣RS) in case there is an argument {a mathematical formula}b∈S, such that {a mathematical formula}(b,a)∈R (resp. {a mathematical formula}(a,b)∈R). Furthermore, we write {a mathematical formula}S↣̸Ra (resp. {a mathematical formula}a↣̸RS) in case there is no argument {a mathematical formula}b∈S, such that {a mathematical formula}(b,a)∈R (resp. {a mathematical formula}(a,b)∈R).Moreover, for a set {a mathematical formula}S⊆A, we denote the set of arguments attacked by (resp. attacking) S as {a mathematical formula}SR⊕={x|S↣Rx} (resp. {a mathematical formula}SR⊖={x|x↣RS}), and define the range of S as {a mathematical formula}SR+=S∪SR⊕ and the negative range of S as {a mathematical formula}SR−=S∪SR⊖.
     </paragraph>
     <paragraph>
      The next definition formally defines the semantics we will focus on in this survey. All of them are based on conflict-free sets, i.e. it is not allowed to jointly accept arguments which are adjacent in the framework. Different additional criteria are then used for the concrete definition: naive extensions are just maximal (with respect to set-inclusion) conflict-free sets, stable extensions have to attack all other arguments, admissible sets defend themselves from attackers, complete extensions in addition have to contain all defended arguments. The grounded extension is given by the subset-minimal complete extension. Preferred extensions are subset-maximal admissible sets (equivalently: subset-maximal complete extensions); finally, semi-stable and stage extensions are characterized by maximizing the concept of range.
     </paragraph>
     <paragraph label="Definition 3">
      Let {a mathematical formula}F=(A,R) be an AF. A set {a mathematical formula}S⊆A is conflict-free (in F), if there are no {a mathematical formula}a,b∈S, such that {a mathematical formula}(a,b)∈R. {a mathematical formula}cf(F) denotes the collection of conflict-free sets of F. For a conflict-free set {a mathematical formula}S∈cf(F), it holds that
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}S∈naive(F), if there is no {a mathematical formula}T∈cf(F) with {a mathematical formula}T⊃S;
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈stb(F), if {a mathematical formula}SR+=A;
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈adm(F), if {a mathematical formula}S⊆FF(S);
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈com(F), if {a mathematical formula}S=FF(S);
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈grd(F), if {a mathematical formula}S∈com(F) and there is no {a mathematical formula}T∈com(F) with {a mathematical formula}T⊂S;
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈prf(F), if {a mathematical formula}S∈adm(F) and there is no {a mathematical formula}T∈adm(F) with {a mathematical formula}S⊂T;
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈sem(F), if {a mathematical formula}S∈adm(F) and there is no {a mathematical formula}T∈adm(F) with {a mathematical formula}SR+⊂TR+;
      </list-item>
      <list-item label="•">
       {a mathematical formula}S∈stg(F), if there is no {a mathematical formula}T∈cf(F), with {a mathematical formula}SR+⊂TR+.
      </list-item>
     </list>
     <paragraph>
      We recall that for each AF F, the grounded semantics yields a unique extension, the grounded extension, which is the least fixed-point of the characteristic function {a mathematical formula}FF. Furthermore, Fig. 2 shows the relations between the aforementioned semantics. The figure is complete in the sense that if there is no arrow from semantics σ to semantics τ, then there is some AF F such that {a mathematical formula}σ(F)⊈τ(F). For all semantics σ we introduced here, except stable semantics, it holds that for any AF F we have {a mathematical formula}σ(F)≠∅.
     </paragraph>
     <paragraph label="Example 2">
      Consider the AF from Example 1. Then: {a mathematical formula}cf(F)={∅,{a},{b},{c},{d},{a,c},{a,d},{b,d}}; {a mathematical formula}naive(F)={{a,c},{a,d},{b,d}}; {a mathematical formula}adm(F)={∅,{a},{d},{a,d}}; and {a mathematical formula}stb(F)=com(F)=grd(F)=prf(F)=sem(F)=stg(F)={{a,d}}.
     </paragraph>
     <section>
      <section>
       <section>
        <section-title>
         Labeling-based semantics
        </section-title>
        <paragraph>
         So far we have considered so-called extension-based semantics. However, there are several approaches defining argumentation semantics via certain kinds of labelings instead of extensions. As an example we consider the popular approach by Caminada and Gabbay [69] and in particular their complete labelings. Basically, such a labeling is a three-valued function that assigns one of the labels in, out and undec to each argument, with the intuition behind these labels being the following. An argument is labeled with: in if it is accepted, i.e., it is defended by the in labeled arguments; out if there are strong reasons to reject it, i.e., it is attacked by an accepted argument; undec if the argument is undecided, i.e., neither accepted nor attacked by accepted arguments. We denote labeling functions {a mathematical formula}L also by triples {a mathematical formula}(Lin,Lout,Lundec), where {a mathematical formula}Lin is the set of arguments labeled by in, {a mathematical formula}Lout is the set of arguments labeled by out and {a mathematical formula}Lundec is the set of arguments labeled by undec.
        </paragraph>
        <paragraph>
         As an example, we give the definition of complete labelings from [69].
        </paragraph>
        <paragraph label="Definition 4">
         Given an AF {a mathematical formula}F=(A,R), a function {a mathematical formula}L:A→{in,out,undec} is a complete labeling iff the following conditions hold:
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}L(a)=in iff for each b with {a mathematical formula}(b,a)∈R, {a mathematical formula}L(b)=out.
         </list-item>
         <list-item label="•">
          {a mathematical formula}L(a)=out iff there exists b with {a mathematical formula}(b,a)∈R, {a mathematical formula}L(b)=in.
         </list-item>
        </list>
        <paragraph>
         There is a one-to-one mapping between complete extensions and complete labelings, such that the set of arguments labeled with in corresponds to the complete extension and the arguments labeled with out correspond to the arguments attacked by the complete extension. Having complete labelings at hand we can also characterize preferred labelings as follows:
        </paragraph>
        <paragraph label="Definition 5">
         Given an AF {a mathematical formula}F=(A,R). The preferred labelings are those complete labelings where {a mathematical formula}Lin is ⊆-maximal among all complete labelings.
        </paragraph>
        <paragraph>
         Right by the definitions, we have the same one-to-one mapping between preferred extensions and preferred labelings as for complete semantics. One can define labeling-based versions for all of our semantics (see [69]), but this is out of the scope of this survey.
        </paragraph>
       </section>
       <section>
        <section-title>
         Reasoning in argumentation frameworks
        </section-title>
        <paragraph>
         We recall the most important reasoning problems for AFs: Given an argumentation framework F and a semantics σ, {a mathematical formula}Enumσ(F) results in an enumeration of all extensions. A simpler notion is {a mathematical formula}Countσ(F), which only counts the number of extensions. Query-based problems are {a mathematical formula}Credσ(a,F) and {a mathematical formula}Skeptσ(a,F) for deciding credulous (respectively skeptical) acceptance of an argument a. The former returns yes if a is contained in at least one extension under σ, while for the latter to return yes, a must be contained in all extensions under σ. Finally, we also consider the problem {a mathematical formula}Verσ(S,F) of verifying a given extension, i.e., testing whether a given set S is a σ-extension of F. This problem typically occurs as a subroutine of a reasoning procedure.
        </paragraph>
        <paragraph label="Definition 6">
         Given an AF {a mathematical formula}F=(A,R), a semantics σ and an argument {a mathematical formula}a∈A, then
        </paragraph>
        <list>
         <list-item label="•">
          {a mathematical formula}Enumσ(F)=σ(F)
         </list-item>
         <list-item label="•">
          {a mathematical formula}Countσ(F)=|σ(F)|
         </list-item>
         <list-item label="•">
          {a mathematical formula}Credσ(a,F)={yesif a∈⋃S∈σ(F)Snootherwise
         </list-item>
         <list-item label="•">
          {a mathematical formula}Skeptσ(a,F)={yesif a∈⋂S∈σ(F)Snootherwise
         </list-item>
         <list-item label="•">
          {a mathematical formula}Verσ(S,F)={yesif S∈σ(F)nootherwise
         </list-item>
        </list>
        <paragraph label="Example 3">
         Consider the AF F given in Example 1. For naive semantics, the reasoning problems result in {a mathematical formula}Enumnaive(F)={{a,c},{a,d},{b,d}} and {a mathematical formula}Countnaive(F)=3. Furthermore, for argument a we obtain {a mathematical formula}Crednaive(a,F)=yes and {a mathematical formula}Skeptnaive(a,F)=no. For preferred semantics, F has a single extension {a mathematical formula}Enumprf(F)={{a,d}}, {a mathematical formula}Countprf(F)=1, and thus credulous and skeptical acceptance coincide (e.g., {a mathematical formula}Credprf(a,F)=Skeptprf(a,F)=yes).
        </paragraph>
        <paragraph>
         Next, let us turn to the complexity of reasoning in abstract argumentation frameworks. We assume the reader has knowledge about standard complexity classes, i.e., P, NP and L (logarithmic space). Furthermore, we briefly recapitulate the concept of oracle machines and related complexity classes. Let {a mathematical formula}C denote some complexity class. By a {a mathematical formula}C-oracle machine we mean a (polynomial time) Turing machine which can access an oracle that decides a given (sub)-problem in {a mathematical formula}C within one step. We denote such machines as {a mathematical formula}NPC if the underlying Turing machine is non-deterministic. The class {a mathematical formula}Σ2P=NPNP thus denotes the set of problems which can be decided by a non-deterministic polynomial time algorithm that has (unrestricted) access to an NP-oracle. The class {a mathematical formula}Π2P=coNPNP is defined as the complementary class of {a mathematical formula}Σ2P, i.e., {a mathematical formula}Π2P=coΣ2P. The relation between the complexity classes is as follows:{a mathematical formula}
        </paragraph>
        <paragraph>
         The computational complexity of credulous and skeptical reasoning has been studied extensively in the literature (see [70] for a starting point). Table 1 summarizes the computational complexity classifications of the defined decision problems [68], [12], [1], [13], [71], [14], [72], [73], where {a mathematical formula}C-c denotes that the corresponding problem is complete for class {a mathematical formula}C.
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Reduction-based approaches
     </section-title>
     <paragraph>
      In this section we will discuss reduction-based approaches in abstract argumentation. As implied by the name, these methods reduce or translate a reasoning problem to another, typically to another formalism. From a computational point of view, we assure that this reduction is efficiently computable, i.e., achievable in polynomial time, and that the answer for the original problem instance can be immediately obtained from the answer to the new problem instance. Such methods offer the great benefit of exploiting existing and highly sophisticated solvers for well-known and well-studied problem domains.
     </paragraph>
     <paragraph>
      Naturally, reduction-based methods can be distinguished by the target system. Many such approaches have been studied for abstract argumentation ranging from propositional logic [19], [18], [21], [20], constraint satisfaction problems (CSP) [27], [23], [26], [28] and answer-set programming (ASP) [30], [74], [75], [76] to equational systems [32], [77]. We will give an overview of these approaches and in particular focus on the first three very prominent target systems, the reductions to propositional logic, CSP and ASP.
     </paragraph>
     <section label="3.1">
      <section-title>
       Propositional-logic based approach
      </section-title>
      <paragraph>
       Propositional logic is the prototypical target system for many approaches based on reductions, as the Boolean SAT problem is well studied and moreover accompanied with many mature and efficient solvers such as MiniSat [78] and GRASP [79].
      </paragraph>
      <paragraph>
       First, we recall the necessary background of Boolean logic and quantified Boolean formulae (QBF) since they serve as our target systems.
      </paragraph>
      <paragraph>
       The basis of propositional logic is a set of propositional variables {a mathematical formula}P, to which we also refer to as atoms. Propositional formulae are built as usual from the connectives {a mathematical formula}∧,∨,→ and ¬, denoting the logical conjunction, disjunction, (material) implication and negation respectively. We use the truth constants ⊤ to denote true and ⊥ for false. In addition, we consider quantified Boolean formulae with the universal quantifier ∀ and the existential quantifier ∃ (both over atoms), that is, given a formula ϕ, then Qpϕ is a QBF, with {a mathematical formula}Q∈{∀,∃} and {a mathematical formula}p∈P. Furthermore, {a mathematical formula}Q{p1,…,pn}ϕ is a shorthand for {a mathematical formula}Qp1⋯Qpnϕ. The order of variables in consecutive quantifiers of the same type does not matter.
      </paragraph>
      <paragraph>
       A propositional variable p in a QBF ϕ is free if it does not occur within the scope of a quantifier Qp and bound otherwise. If ϕ contains no free variable, then ϕ is said to be closed and otherwise open. We will write {a mathematical formula}ϕ[p/ψ] to denote the result of uniformly substituting each free occurrence of p with ψ in formula ϕ.
      </paragraph>
      <paragraph>
       An interpretation {a mathematical formula}I⊆P defines for each propositional variable a truth assignment where {a mathematical formula}p∈I indicates that p evaluates to true while {a mathematical formula}p∉I indicates that p evaluates to false. This generalizes to arbitrary formulae in the standard way: Given a formula ϕ and an interpretation I, then ϕ evaluates to true under I (i.e., I satisfies ϕ) if one of the following holds (with {a mathematical formula}p∈P).
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ϕ=p and {a mathematical formula}p∈I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=¬p and {a mathematical formula}p∉I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=ψ1∧ψ2 and both {a mathematical formula}ψ1 and {a mathematical formula}ψ2 evaluate to true under I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=ψ1∨ψ2 and one of {a mathematical formula}ψ1 and {a mathematical formula}ψ2 evaluates to true under I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=ψ1→ψ2 and {a mathematical formula}ψ1 evaluates to false or {a mathematical formula}ψ2 evaluates to true under I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=∃pψ and one of {a mathematical formula}ψ[p/⊤] and {a mathematical formula}ψ[p/⊥] evaluates to true under I
       </list-item>
       <list-item label="•">
        {a mathematical formula}ϕ=∀pψ and both {a mathematical formula}ψ[p/⊤] and {a mathematical formula}ψ[p/⊥] evaluate to true under I.
       </list-item>
      </list>
      <paragraph>
       If an interpretation I satisfies a formula ϕ, denoted by {a mathematical formula}I⊨ϕ, we say that I is a model of ϕ.
      </paragraph>
      <paragraph>
       The approaches in Section 3.1.1 and Section 3.1.2 share the basic idea of translating a given AF, a semantics and a reasoning problem to a propositional formula, thereby reducing the problem to Boolean logic. In general this works by either inspecting the models of the resulting formula, which are in correspondence to the extensions of the AF, or deciding whether a formula is satisfiable or unsatisfiable, to solve query-based reasoning. Note that we restrict ourselves here to the semantics which we consider to be sufficient for illustrating the main concepts. In general, the approaches can be applied to many other semantics.
      </paragraph>
      <section label="3.1.1">
       <section-title>
        Reductions to propositional logic
       </section-title>
       <paragraph>
        The first reduction-based approach [18], [20] we consider here uses propositional logic formulae (without quantifiers) to encode the problem of finding admissible sets. Given an AF {a mathematical formula}F=(A,R), for each argument {a mathematical formula}a∈A a propositional variable {a mathematical formula}va is used. Then, {a mathematical formula}S⊆A is an extension under semantics σ iff {a mathematical formula}{va|a∈S}⊨ϕ, with ϕ being a propositional formula that evaluates AF F under semantics σ (below we will present in detail how to translate AFs into formulae). Formally, the correspondence between sets of extensions and models of a propositional formula can be defined as follows.
       </paragraph>
       <paragraph label="Definition 7">
        Let {a mathematical formula}S⊆2A be a collection of sets of arguments and let {a mathematical formula}I⊆2P be a collection of interpretations. We say that {a mathematical formula}S and {a mathematical formula}I correspond to each other, in symbols {a mathematical formula}S≅I, if
       </paragraph>
       <list>
        <list-item label="1.">
         for each {a mathematical formula}S∈S, there exists an {a mathematical formula}I∈I, such that {a mathematical formula}{a|va∈I,a∈A}=S;
        </list-item>
        <list-item label="2.">
         for each {a mathematical formula}I∈I, there exists an {a mathematical formula}S∈S, such that {a mathematical formula}{a|va∈I,a∈A}=S; and
        </list-item>
        <list-item label="3.">
         {a mathematical formula}|S|=|I|.
        </list-item>
       </list>
       <paragraph>
        Given an AF {a mathematical formula}F=(A,R) the following formula can be used to solve the enumeration problem of admissible semantics.{a mathematical formula}
       </paragraph>
       <paragraph>
        The models of {a mathematical formula}admA,R now correspond to the admissible sets of F, i.e., {a mathematical formula}Enumadm(F)≅{M|M⊨admA,R}. Taken into consideration that by definition a satisfiable formula has infinitely many models (thus violating item three in Definition 7), it is now possible to restrict the set of models to those containing only atoms occurring in the formula. The first conjunction in (1) ensures that the resulting set of arguments is conflict-free, that is, whenever we accept an argument a (i.e., {a mathematical formula}va evaluates to true under a model), all its attackers cannot be selected any further. The second conjunct expresses the defense of arguments by stating that, if we accept a, then for each attacker b, some defender c must be accepted as well. Note that an empty conjunction is treated as ⊤, whereas the empty disjunction is treated as ⊥.
       </paragraph>
       <paragraph label="Example 4">
        The propositional formula for admissible sets of the framework {a mathematical formula}F=(A,R) in Example 1 is given by{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Lines (2), (3), (4), (5), (6) encode the conflict-free property, while lines (7), (8), (9), (10), (11) ensure that arguments in an admissible set are defended. Note that for convenience, the conjuncts are arranged in a different order than in the definition of {a mathematical formula}admA,R. Consider for instance argument b. Line (3) specifies that if we accept b we cannot accept a and c anymore (conflict-free property). Likewise, line (8) states that b can only be accepted in case it is defended against its attackers. For the attacker c either b itself or d must be accepted. However, since attacker a is not attacked by any other argument, there is no model of {a mathematical formula}admA,R where {a mathematical formula}vb evaluates to true.
       </paragraph>
       <paragraph>
        Another interesting translation to capture semantics of AFs within propositional logic is done by Gabbay [80]. Here, a correspondence between AFs and propositional logic is shown via the Peirce–Quine dagger (“nor”) connective.
       </paragraph>
       <paragraph>
        Furthermore, several papers deal with the converse translation, i.e. translating a Boolean formula in CNF to an AF. Similar as before, for each atom in a formula a corresponding argument is constructed. Accepting such an argument, e.g. under stable semantics, is then interpreted as setting the atom to true. The result is a correspondence between extensions under a specific semantics and satisfying assignments of the formula. Usually, these translations incorporate auxiliary arguments, which are used to simulate the logical connectives. In [12], [13] and [81] such methods are studied and used to show complexity bounds or for translations between formalisms.
       </paragraph>
      </section>
      <section label="3.1.2">
       <section-title>
        Reductions to quantified Boolean formulae
       </section-title>
       <paragraph>
        Problems beyond NP require a more expressive formalism than Boolean logic. Preferred semantics, for example, is defined as subset-maximal admissible (or complete) sets. Intuitively, we can compute a preferred extension by searching for an admissible set and additionally making sure that there is no proper superset which is also admissible. In order to express subset maximality directly inside the logic, a universal (or, equivalently, a negated existential) quantifier can be used, making quantified Boolean formulae a well-suited formalism. It is possible to specify preferred semantics in QBFs either via an extension-based, or a labeling-based approach.
       </paragraph>
       <paragraph>
        First, we consider the extension-based approach from [20]. Here, we encode the maximality check with an auxiliary formula. For convenience we denote by {a mathematical formula}A′={a′|a∈A} the set of renamed arguments in A. Likewise, we define a renaming for the attack relation as {a mathematical formula}R′={(a′,b′)|(a,b)∈R}. The following defines a shorthand for comparing two sets of atoms an interpretation is defined upon with respect to the subset-relation.{a mathematical formula}
       </paragraph>
       <paragraph>
        In other words, this formula ensures that any model {a mathematical formula}M⊨(A&lt;A′) satisfies {a mathematical formula}{a∈A|va∈M}⊂{a∈A|va′∈M}. Now we can state the QBF for preferred extensions. Let the quantified variables be {a mathematical formula}Av′={va′|a′∈A′}.{a mathematical formula}
       </paragraph>
       <paragraph>
        In short, we check whether the accepted arguments form an admissible set and whether there exists a proper superset of it which is also admissible. If the former check succeeds and in the latter no such set exists, then we have found a preferred extension. For an arbitrary AF {a mathematical formula}F=(A,R), its preferred extensions are in a 1-to-1 correspondence to the models of {a mathematical formula}prfA,R, i.e., {a mathematical formula}Enumprf(F)≅{M|M⊨prfA,R}.
       </paragraph>
       <paragraph>
        The second approach is based on complete labelings (see Definition 4) instead of extensions [19].{sup:9} To this end, we employ four-valued interpretations to express more than two possible states for each argument. In addition to the truth values true and false we also add values undecided and inconsistent. The three labelings in, out and undecided correspond to the first three truth values. The whole approach can be encoded in classical two-valued QBFs. Hereby, the truth value of {a mathematical formula}p∈P is encoded via {a mathematical formula}p⊕ and {a mathematical formula}p⊖. Now every classical two-valued interpretation assigns values to these two atoms as usual. For two variables we have four different cases, which correspond to the four truth values: {a mathematical formula}{p⊕,p⊖}⊆I is interpreted as assigning inconsistent to p, true (resp. false) is assigned to p if only {a mathematical formula}p⊕ (resp. {a mathematical formula}p⊖) is in I, and undecided is assigned if neither {a mathematical formula}p⊕ nor {a mathematical formula}p⊖ is in I.
       </paragraph>
       <paragraph>
        For preferred semantics the encoding is more complex than (12), but the ideas are similar. We begin with formulae for the four truth values. Note that we slightly adapted the representation and formulae from [19] to better match the previous encodings, but the important concepts remain the same.{a mathematical formula}
       </paragraph>
       <paragraph>
        Here, {a mathematical formula}val(p,v) encodes the four possible truth values for a virtual atom p that can be referred to on a sort of meta-level. Actually, instead of p the auxiliary atoms {a mathematical formula}p⊕ and {a mathematical formula}p⊖ are present in the concrete formula. Using this concept, we can specify the labeling formula for each argument in an AF {a mathematical formula}F=(A,R).{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        These formulae reflect Definition 4: The formulae (13), (14) and (15) encode the in, out and undecided labelings, respectively. For example, (13) can be interpreted in the following way: If an argument a is set to true, then all its attackers must be false. (14) can be interpreted similarly, except that if an atom denotes that an argument is false, then one of its attackers must be true. Finally, (15) states that for any argument to which we assign undecided, it cannot be the case that all its attackers are false or that one of them is true.
       </paragraph>
       <paragraph>
        Three values are sufficient to reflect the three labelings. To avoid problems with the fourth truth value (inconsistent), we exclude it from occurring in the evaluation by the following formula.{a mathematical formula}
       </paragraph>
       <paragraph>
        Now, complete extensions are characterized by the following formula. We will use L as superscript in {a mathematical formula}comA,RL to denote that this formula handles labelings instead of extensions.{a mathematical formula}
       </paragraph>
       <paragraph>
        The formula {a mathematical formula}comA,RL expresses that all the arguments are assigned either true, false or undecided via the {a mathematical formula}3valA sub-formula. For each argument, the three conjuncts on the right of the formula encode implications which ensure that the labels are assigned as specified for complete labelings. For example, if a is true, then all its attackers must be false. By applying this, one can encode complete labelings and hence complete extensions. Preferred extensions (or labelings) are expressed as before by subset maximization.{a mathematical formula}
       </paragraph>
       <paragraph>
        Then, similar as in {a mathematical formula}prfA,R, the preferred extensions or their labelings can be encoded with a QBF as follows, with the quantified atoms {a mathematical formula}Av′={va′⊕,va′⊖|a′∈A′}.{a mathematical formula}
       </paragraph>
       <paragraph>
        For an AF {a mathematical formula}F=(A,R) the following notion of correspondence holds: Let the set of atoms evaluated to true under the four-valued interpretation be {a mathematical formula}Mt={p|p⊕∈M,p⊖∉M}, then {a mathematical formula}Enumprf(F)≅{Mt|M⊨prfA,RL}. Note that {a mathematical formula}prfA,RL differs from {a mathematical formula}prfA,R not only by using a labeling-based approach, but also by maximizing complete labelings rather than admissible sets.
       </paragraph>
       <paragraph>
        Utilizing the expressive power of quantifiers and the labeling approach, the authors of [19] also encode a range of other semantics, for instance semi-stable reasoning, where one can apply the same idea as outlined above, but instead of maximizing the arguments that are in, the arguments that are labeled undecided are minimized.
       </paragraph>
       <paragraph>
        This results in a general system for encoding many semantics, but one has to be careful with choosing the right target system. For example, grounded semantics can easily be specified in this formalism using a QBF, but computing the grounded extension can be done using an algorithm with polynomial running time. Thus, an appropriate encoding would yield a QBF from a fragment which is known to be efficiently decidable, for instance, 2-QBF (the generalization of Krom formulae to QBFs). However, we are not aware of any work which deals with such “complexity-sensitive” encodings in terms of QBFs.
       </paragraph>
      </section>
      <section label="3.1.3">
       <section-title>
        Iterative application of SAT solvers
       </section-title>
       <paragraph>
        The last propositional-logic based approach we outline here is based on the idea of iteratively searching for models of propositional formulae and has been instantiated in the systems ArgSemSAT [82], [22] and CEGARTIX [21], [83]. The idea is to use an algorithm which iteratively constructs formulae and searches for models of these formulae. A new formula is generated based on the model of the previous one (or based on the fact that the previous formula is unsatisfiable). At some point the algorithm reaches a final decision and terminates. This is in contrast to so-called monolithic encodings, which formulate the whole problem in a single formula. The encodings in previous sections are examples for such monolithic encodings. The iterative approach is suitable when the problem to be solved cannot be decided in general (under standard complexity theoretic assumptions) by the satisfiability of a single propositional formula (constructible in polynomial time) without quantifiers. This is, for instance, the case with skeptical acceptance under preferred semantics where the corresponding decision problem is {a mathematical formula}Π2P complete. Instead of reducing the problem to a single QBF formula, we delegate the solving task in the iterative scheme to an algorithm querying a SAT solver multiple times.
       </paragraph>
       <paragraph>
        The algorithms for preferred semantics work roughly as follows. To compute preferred extensions we traverse the search space of a computationally simpler semantics. For instance, we can iteratively search for admissible sets or complete extensions and iteratively extend them until we reach a maximal set, which is a preferred extension. By generating a new candidate admissible set/complete extension, which is not contained in an already visited preferred extension we can enumerate all preferred extensions in this manner. This allows answering credulous and skeptical reasoning as well.
       </paragraph>
       <paragraph>
        For deciding e.g. skeptical acceptance of an argument under preferred semantics one requires in general an exponential number of calls to the SAT solver (under standard complexity theoretic assumptions). However, the number of SAT calls in the iterative SAT scheme is dependent on the number of preferred extensions of the given AF, see [21].
       </paragraph>
       <paragraph>
        In the following, we first sketch the CEGARTIX approach from [21] for skeptical acceptance under preferred semantics and subsequently outline the PrefSat approach [82], implemented in the ArgSemSAT system, for enumerating all preferred extensions. Again, we slightly adapted the algorithms for a uniform setting and presentation.
       </paragraph>
       <paragraph>
        Algorithm 1 decides skeptical acceptance under preferred semantics of an argument a in an AF F. The idea is to proceed from one preferred extension to the next and checking whether a is in one of the extensions. This is encoded in the outer while loop, lines 2 to 11. The models of formula ϕ represent the remaining admissible sets in the current state of the algorithm. In the beginning, ϕ encodes all admissible sets of F. We start with an admissible set and iteratively extend it while making sure that a is not accepted in this admissible set. This is done in the second loop (lines 3 to 5) and by adding {a mathematical formula}¬va to the query. The formula {a mathematical formula}ψI incorporates the model I and states that a model of it must still correspond to an admissible set, but also has to be a superset of the current one, specified by I.
       </paragraph>
       <paragraph>
        If we cannot add further arguments to the admissible set, we check whether we can extend it with having a inside, in line 6. If this is the case, every preferred extension that is a superset of the current admissible set contains a. Hence, we can proceed to a different admissible set not containing a. In case we cannot add a to the admissible set, we have found a preferred extension without a, hereby refuting its skeptical acceptance in F. In the former case (I does not represent a preferred extension) we strengthen the main query ϕ by adding {a mathematical formula}γI in line 7, stating that at least one argument currently not accepted in I must be accepted from now on. This ensures that in future iterations we compute admissible sets that are not contained in previously found preferred extensions.
       </paragraph>
       <paragraph>
        The formulae are defined as follows.{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph label="Example 5">
        For the AF F from Example 1 we can check the skeptical acceptance of b. The condition of the first loop is satisfied as there exist the admissible sets ∅, {a mathematical formula}{a}, {a mathematical formula}{d} and {a mathematical formula}{a,d} in F. The algorithm now non-deterministically selects one of the admissible sets. Say we pick ∅. The second while loop then creates a subset maximal admissible set (excluding b) in two iterations, say first adding a and then d. As {a mathematical formula}{a,d} is now subset maximal, the second loop terminates. Since this set cannot be extended if we allow to also accept b, we know that we have found a preferred extension. This means we refute the skeptical acceptance of b.
       </paragraph>
       <paragraph>
        The PrefSat approach [82] is designed to enumerate all preferred extensions utilizing a similar idea. Hereby, also a simpler semantics for traversing the search space is used, but the encodings rely on the concept of labellings (see also Section 4.1). We outline the PrefSat procedure in Algorithm 2.
       </paragraph>
       <paragraph>
        PrefSat encodes labelings of an AF {a mathematical formula}F=(A,R) by generating three variables per argument, i.e., the set of variables in the constructed formula are {a mathematical formula}{Ia,Oa,Ua|a∈A}. In the final result these variables correspond naturally to a labeling. In particular, a three-valued labeling K corresponds to a model J if {a mathematical formula}K=(I,O,U) with {a mathematical formula}I={a|Ia∈J}, {a mathematical formula}O={a|Oa∈J} and {a mathematical formula}U={a|Ua∈J}. The following constraint encodes that for every argument exactly one labeling is assigned.{a mathematical formula} Furthermore, one can encode the conditions for a labeling to be complete by conjoining certain subformulae. For instance, the formula{a mathematical formula} encodes that we can accept x if each attacker is out. The remaining constraints for a labeling to be complete are encoded similarly. Several equivalent formulae for encoding complete labelings have been investigated by Cerutti et al. [82]. Let {a mathematical formula}comA,R′ be one of these choices for encoding complete labelings. The formulae for Algorithm 2 are then defined as follows.{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Algorithm 2 traverses the space of complete labelings in two while loops. The outer while loop computes candidate complete labelings, which are not smaller than previously found preferred labelings (when comparing only the arguments assigned in). The inner while loop searches for a maximal preferred labeling. If the inner while loop terminates, then the corresponding preferred labeling/extension is added to the solution set {a mathematical formula}S. In line 8 we exclude smaller complete labelings from subsequent iterations. In [82] the algorithm for enumerating all preferred extensions contains further refinements, such as restricting the search space to non-empty complete extensions.
       </paragraph>
      </section>
      <section label="3.1.4">
       <section-title>
        Reasoning problems
       </section-title>
       <paragraph>
        The first two reductions presented in Section 3.1.1 and Section 3.1.2 immediately solve problems of enumerating extensions. Deciding credulous and skeptical reasoning is typically easy to achieve. In order to decide {a mathematical formula}Credσ(a,F) one can conjoin the base formula with an atom corresponding to the acceptance of argument a. If there exists a model, a is credulously accepted. Adding the atom for a in negated form to the formula decides if a is not skeptically accepted, i.e., if there exists a model, an extension does not contain a.
       </paragraph>
       <paragraph>
        Similarly, the iterative SAT scheme of Algorithm 1 (see Section 3.1.3) can be adapted to solve credulous reasoning by adding the atom to be queried positively instead of negatively in line 3. Regarding the enumeration problem, Algorithm 2 enumerates all preferred extensions using iterative SAT.
       </paragraph>
       <paragraph>
        Counting the number of extensions cannot be easily encoded in the formulae, but the SAT solver itself may offer this feature by counting the number of models.
       </paragraph>
      </section>
     </section>
     <section label="3.2">
      <section-title>
       CSP-based approach
      </section-title>
      <paragraph>
       In this subsection we consider reductions to Constraint Satisfaction Problems (CSPs) [84], which allow solving combinatorial search problems. The approach of CSP is inherently related to propositional logic reductions as introduced in Subsection 3.1.1, see also [85] for a formal analysis of the relation between the two approaches.
      </paragraph>
      <paragraph>
       A CSP can generally be described by a triple {a mathematical formula}(X,D,C), where {a mathematical formula}X={x1,…,xn} is the set of variables, {a mathematical formula}D={D1,…,Dn} is a set of finite domains for the variables and {a mathematical formula}C={c1,…,cm} a set of constraints. Each constraint {a mathematical formula}ci is a pair {a mathematical formula}(hi,Hi) where {a mathematical formula}hi=(xi1,…,xik) is a k-tuple of variables and {a mathematical formula}Hi is a k-ary relation over D. In particular, {a mathematical formula}Hi is a subset of all possible variable values representing the allowed combinations of simultaneous values for the variables in {a mathematical formula}hi. An assignment v is a mapping that assigns to every variable {a mathematical formula}xi∈X an element {a mathematical formula}v(xi)∈Di. An assignment v satisfies a constraint {a mathematical formula}((xi1,…,xik),Hi)∈C iff {a mathematical formula}(v(xi1),…,v(xik))∈Hi. Finally, a solution is an assignment v to all variables such that all constraints are satisfied, denoted by {a mathematical formula}(v(x1),…,v(xn)).
      </paragraph>
      <paragraph>
       Finding a valid assignment of a CSP is in general NP-complete. Nevertheless, several programming libraries support constraint programming, like ECLiPSe, SWI Prolog, Gecode, JaCoP, Choco, Turtle (just to mention some of them) and allow for efficient implementations of CSPs. These constraint programming solvers make use of techniques like backtracking and local search.
      </paragraph>
      <paragraph>
       Computing argumentation semantics via constraint programming has been addressed mainly by Amgoud and Devred [23] and Bistarelli and Santini [26], [27], [28], where the latter provide the system ConArg which is able to compute a wide range of semantics for abstract argumentation frameworks.
      </paragraph>
      <section label="3.2.1">
       <section-title>
        Mappings of AFs to CSPs
       </section-title>
       <paragraph>
        Given an AF {a mathematical formula}F=(A,R), the associated CSP {a mathematical formula}(X,D,C) is specified as {a mathematical formula}X=A and for each {a mathematical formula}ai∈X, {a mathematical formula}Di={0,1}. The constraints are formulated depending on the specific semantics σ. For example, solutions that correspond to conflict-free sets can be obtained by defining a constraint for each pair of arguments a and b with {a mathematical formula}(a,b)∈R, where the two variables may not be set to 1 at the same time. Here, the constraint is of the form {a mathematical formula}((a,b),((0,0),(0,1),(1,0))) which is equivalent to the cases when the propositional formula {a mathematical formula}(a→¬b) evaluates to true.
       </paragraph>
       <paragraph>
        In the following, we will use the notation from [23], because it reflects the similarities between the CSP approach and the reductions to propositional logic as outlined above.
       </paragraph>
       <paragraph>
        For admissible semantics we get the following constraints.{a mathematical formula}
       </paragraph>
       <paragraph>
        The first part ensures conflict-free sets and the second part encodes the defense of arguments. Then, for an AF {a mathematical formula}F=(A,R) and its associated admissible CSP {a mathematical formula}(X,D,Cadm), {a mathematical formula}(v(x1),…,v(xn)) is a solution of the CSP iff the set {a mathematical formula}{xj,…,xk} s.t. {a mathematical formula}v(xi)=1 is an admissible set in F.
       </paragraph>
       <paragraph label="Example 6">
        For the AF of Example 1 on Page 30 we obtain the following admissible CSP {a mathematical formula}(X,D,Cadm). {a mathematical formula}X=A, for each {a mathematical formula}ai∈X we have {a mathematical formula}Di={0,1} and{a mathematical formula} This CSP has the following solutions: {a mathematical formula}(0,0,0,0,0), {a mathematical formula}(1,0,0,0,0), {a mathematical formula}(0,0,0,1,0), {a mathematical formula}(1,0,0,1,0) which correspond to the admissible sets of F, namely {a mathematical formula}{},{a},{d} and {a mathematical formula}{a,d}.
       </paragraph>
       <paragraph>
        Most CSP solvers do not support subset maximization. Thus, for preferred semantics, the authors in [28] propose an approach that iteratively computes admissible/complete extensions and adds constraints to exclude certain sets, such that one finally obtains the preferred extensions.
       </paragraph>
      </section>
      <section label="3.2.2">
       <section-title>
        Reasoning problems
       </section-title>
       <paragraph>
        Similarly to the reductions to propositional logic, one can decide the following reasoning problems with CSPs, namely verification, skeptical and credulous reasoning. Furthermore, enumeration is usually supported by modern CSP solvers.
       </paragraph>
      </section>
     </section>
     <section label="3.3">
      <section-title>
       ASP-based approach
      </section-title>
      <paragraph>
       Answer-set programming (ASP, for short) [86], [87], also known as A-Prolog [88], [89], is a declarative problem solving paradigm, rooted in logic programming and non-monotonic reasoning. Due to continuous refinements over the last decade, answer-set solvers (e.g., [90], [91]) nowadays not only support a rich language but also are capable of solving hard problems efficiently. Furthermore, the declarative approach of ASP results in readable and maintainable code (compared to C code, for instance), thus allowing to define the problems at hand in a natural way.
      </paragraph>
      <paragraph>
       Solving problems in abstract argumentation via ASP has been studied by several authors (see [29] for a survey), including the approach proposed by Nieves et al. [74] where the program is re-computed for every input instance, Wakaki and Nitta [76] who use labeling-based semantics and the approach by Egly et al. [30] which follows extension-based semantics. Here, we focus on the latter, since this approach is put into practice by the ASPARTIX system which supports a wide range of different semantics and additionally offers a web front-end.
      </paragraph>
      <paragraph>
       In the following, we first give a brief introduction to ASP. We then present how the computation of admissible and preferred extensions can be encoded in ASP. In order to obtain preferred extensions, it is necessary to check for subset-maximality of admissible sets. We sketch two approaches for this in ASP, one based directly on a certain saturation technique[92] (which is unfortunately hardly accessible for non-experts in ASP) and a second one which makes use of metasp encodings [93] (allowing to specify subset minimization via a single simple statement). Additionally, we discuss how reasoning problems can be specified.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Answer-set programming
       </section-title>
       <paragraph>
        We give a brief overview of the syntax and semantics of disjunctive logic programs under the answer-set semantics [94]; for further background, see [95], [91].
       </paragraph>
       <paragraph>
        We fix a countable set {a mathematical formula}U of (domain) elements, also called constants, and suppose a total order &lt; over the domain elements. An atom is an expression {a mathematical formula}p(t1,…,tn), where p is a predicate of arity {a mathematical formula}n≥0 and each {a mathematical formula}ti is either a variable or an element from {a mathematical formula}U. An atom is ground if it is free of variables. {a mathematical formula}BU denotes the set of all ground atoms over {a mathematical formula}U.
       </paragraph>
       <paragraph>
        A (disjunctive) rule r with {a mathematical formula}n≥0, {a mathematical formula}m≥k≥0, {a mathematical formula}n+m&gt;0 is of the form{a mathematical formula} where {a mathematical formula}a1,…,an,b1,…,bm are atoms, and “not” stands for default negation. An atom a is a positive literal, while nota is a default negated literal. The head of r is the set {a mathematical formula}H(r)={a1,…,an} and the body of r is {a mathematical formula}B(r)=B+(r)∪B−(r) with {a mathematical formula}B+(r)={b1,…,bk} and {a mathematical formula}B−(r)={bk+1,…,bm}. A rule r is normal if {a mathematical formula}n≤1 and a constraint if {a mathematical formula}n=0. A rule r is safe if each variable in r occurs in {a mathematical formula}B+(r). A rule r is ground if no variable occurs in r. A fact is a ground rule without disjunction and with an empty body. An (input) database is a set of facts. A program is a finite set of safe disjunctive rules. For a program π and an input database D, we often write {a mathematical formula}π(D) instead of {a mathematical formula}D∪π. If each rule in a program is normal (resp. ground), we call the program normal (resp. ground). Besides disjunctive and normal programs, we consider here the class of optimization programs, i.e., normal programs which additionally contain #minimize statements{a mathematical formula} where {a mathematical formula}li is a literal, {a mathematical formula}wi an integer weight and {a mathematical formula}Ji an integer priority level.
       </paragraph>
       <paragraph>
        For any program π, let {a mathematical formula}Uπ be the set of all constants appearing in π. {a mathematical formula}Gr(π) is the set of rules rτ obtained by applying, to each rule {a mathematical formula}r∈π, all possible substitutions τ from the variables in r to elements of {a mathematical formula}Uπ. An interpretation{a mathematical formula}I⊆BUsatisfies a ground rule r iff {a mathematical formula}H(r)∩I≠∅ whenever {a mathematical formula}B+(r)⊆I and {a mathematical formula}B−(r)∩I=∅. I satisfies a ground program π, if each {a mathematical formula}r∈π is satisfied by I. A non-ground rule r (resp., a program π) is satisfied by an interpretation I iff I satisfies all groundings of r (resp., {a mathematical formula}Gr(π)). {a mathematical formula}I⊆BU is an answer set of π iff it is a subset-minimal set satisfying the Gelfond–Lifschitz reduct{a mathematical formula}πI={H(r)←B+(r)|I∩B−(r)=∅,r∈Gr(π)}. For a program π, we denote the set of its answer sets by {a mathematical formula}AS(π).
       </paragraph>
       <paragraph>
        For semantics of optimization programs, we interpret the #minimize statement w.r.t. subset-inclusion: For any sets X and Y of atoms, we have {a mathematical formula}Y⊆JwX, if for any weighted literal {a mathematical formula}l=w@J occurring in (19), {a mathematical formula}Y⊨l implies {a mathematical formula}X⊨l. Then, M is a collection of relations of the form {a mathematical formula}⊆Jw for priority levels J and weights w. A standard answer set (i.e., not taking the minimize statements into account) Y of π dominates a standard answer set X of π w.r.t. M if there are a priority level J and a weight w such that {a mathematical formula}X⊆JwY does not hold for {a mathematical formula}⊆Jw∈M, while {a mathematical formula}Y⊆J′w′X holds for all {a mathematical formula}⊆J′w′∈M where {a mathematical formula}J′≥J. Finally, a standard answer set X is an answer set of an optimization program π w.r.t. M if there is no standard answer set Y of π that dominates X w.r.t. M[93].
       </paragraph>
      </section>
      <section label="3.3.2">
       <section-title>
        Basic encodings
       </section-title>
       <paragraph>
        We now provide fixed queries for admissible and preferred extensions in such a way that the AF F is given as an input database {a mathematical formula}Fˆ and the answer sets of the combined program {a mathematical formula}πe(Fˆ) are in a certain one-to-one correspondence with the respective extensions, where {a mathematical formula}e∈{adm,prf}. For an AF {a mathematical formula}F=(A,R), we define{a mathematical formula} We have to guess candidates for the selected type of extensions and then check whether a guessed candidate satisfies the corresponding conditions, where default negation is an appropriate concept to formulate such a guess within a query. In what follows, we use unary predicates {a mathematical formula}in(⋅) and {a mathematical formula}out(⋅) to perform a guess for a set {a mathematical formula}S⊆A, where {a mathematical formula}in(a) represents that {a mathematical formula}a∈S.
       </paragraph>
       <paragraph>
        Similar to Definition 7, we define the subsequent notion of correspondence which is relevant for our purposes.
       </paragraph>
       <paragraph label="Definition 8">
        Let {a mathematical formula}S⊆2U be a collection of sets of domain elements and let {a mathematical formula}I⊆2UB be a collection of sets of ground atoms. We say that {a mathematical formula}S and {a mathematical formula}I correspond to each other, in symbols {a mathematical formula}S≅I, iff
       </paragraph>
       <list>
        <list-item label="1.">
         for each {a mathematical formula}S∈S, there exists an {a mathematical formula}I∈I, such that {a mathematical formula}{a|in(a)∈I}=S;
        </list-item>
        <list-item label="2.">
         for each {a mathematical formula}I∈I, there exists an {a mathematical formula}S∈S, such that {a mathematical formula}{a|in(a)∈I}=S; and
        </list-item>
        <list-item label="3.">
         {a mathematical formula}|S|=|I|.
        </list-item>
       </list>
       <paragraph>
        Next, we will successively introduce the rules our queries are composed of. Let {a mathematical formula}F=(A,R) be an argumentation framework. The following program fragment guesses, when augmented by {a mathematical formula}Fˆ, any subset {a mathematical formula}S⊆A and then checks whether the guess is conflict-free in F:{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        The program module {a mathematical formula}πadm for the admissibility test is as follows:{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        For any AF {a mathematical formula}F=(A,R), the admissible sets of F correspond to the answer sets of {a mathematical formula}πadm augmented by {a mathematical formula}Fˆ, i.e. {a mathematical formula}adm(F)≅AS(πadm(Fˆ)).
       </paragraph>
       <paragraph>
        Sometimes we have to avoid the use of negation. This might either be the case for the saturation technique (described below), or if the problem can be encoded without a guess &amp; check approach (e.g. for grounded semantics). Then, encodings typically rely on a form of loops where all domain elements are visited and it is checked whether a desired property holds for all elements visited so far. We will use this technique in our saturation-based encoding. For this purpose, an order &lt; over the domain elements (usually provided by common ASP solvers) is used together with a few helper predicates defined in the program {a mathematical formula}π&lt; below; in fact, predicates {a mathematical formula}lt/2, {a mathematical formula}inf/1, {a mathematical formula}succ/2 and {a mathematical formula}sup⁡/1 denote lower than, infimum, successor and supremum of the order &lt;. The predicates {a mathematical formula}ninf/1, {a mathematical formula}nsup/1 and {a mathematical formula}nsucc/2 are used to derive that an element is not the infimum or the supremum, or respectively an element is not the successor of the other w.r.t. the order &lt;.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
      </section>
      <section label="3.3.3">
       <section-title>
        Saturation encodings
       </section-title>
       <paragraph>
        To compute the preferred extensions of an argumentation framework, we will use the saturation technique as follows: Having computed an admissible set S (characterized via predicates {a mathematical formula}in(⋅) and {a mathematical formula}out(⋅) using encoding {a mathematical formula}πadm(Fˆ)), we perform a second guess with new predicates, say {a mathematical formula}inN(⋅) and {a mathematical formula}outN(⋅), to represent a guess {a mathematical formula}T⊃S. In order to check whether the first guess characterizes a preferred extension, we have to ensure that no guess of the second form (i.e., via {a mathematical formula}inN(⋅) and {a mathematical formula}outN(⋅)) characterizes an admissible set. The saturation module {a mathematical formula}πsatpref looks as follows.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Let us for the moment also assume that predicates eq (rule (22)) and {a mathematical formula}undefeated(⋅) (rule (24)) are defined (we give the additional rules for those predicates below in the modules {a mathematical formula}πeq and {a mathematical formula}πundefeated) and provide the following information:
       </paragraph>
       <list>
        <list-item label="•">
         eq is derived if the guess S via {a mathematical formula}in(⋅) and {a mathematical formula}out(⋅) equals the second guess T via {a mathematical formula}inN(⋅) and {a mathematical formula}outN(⋅); in other words, eq is derived if {a mathematical formula}S=T;
        </list-item>
        <list-item label="•">
         {a mathematical formula}undefeated(a) is derived if argument a is not defeated in F by the second guess T.
        </list-item>
       </list>
       <paragraph>
        In the following, we discuss the functioning of {a mathematical formula}πsatpref when conjoined with the program {a mathematical formula}πadm(Fˆ) for a given AF F. First, rule (20) guesses a set {a mathematical formula}T⊆A as already discussed above. Rule (21) ensures that the new guess satisfies {a mathematical formula}S⊆T.
       </paragraph>
       <paragraph>
        The task of the rules (22), (23), (24) is to check whether the new guess T is a proper superset of S and characterizes an admissible set of the given AF F. If this is not the case, we derive the predicate fail. More specifically, we derive fail if either {a mathematical formula}S=T (rule (22)); T is not conflict-free in F (rule (23)); or T contains an argument not defended by T in F (rule (24)). In other words, we have not derived fail if {a mathematical formula}T⊃S and T is admissible in F. By definition, S then cannot be a preferred extension of F.
       </paragraph>
       <paragraph>
        The remaining rules (25), (26), (27) saturate the guess in case fail was derived, and finally ensure that fail has to be in an answer set.
       </paragraph>
       <paragraph>
        Let us illustrate now the behavior of {a mathematical formula}πsatpref for two scenarios. First, suppose the first guess S (via predicates {a mathematical formula}in(⋅) and {a mathematical formula}out(⋅)) is a preferred extension of the given AF {a mathematical formula}F=(A,R). Hence, for each {a mathematical formula}T⊃S, T is not admissible. Consequently, every new guess T (via predicates {a mathematical formula}inN(⋅) and {a mathematical formula}outN(⋅)) derives fail. Thus, we have no interpretation without predicate fail that satisfies {a mathematical formula}πsatpref. However, the saturated interpretation, which contains fail and both {a mathematical formula}inN(a) and {a mathematical formula}outN(a) for each {a mathematical formula}a∈A, does satisfy the program and also becomes an answer set of the program.
       </paragraph>
       <paragraph>
        Now, suppose the first guess S (via predicates {a mathematical formula}in(⋅) and {a mathematical formula}out(⋅)) is an admissible but not a preferred extension of the given AF F. Then, there exists a set {a mathematical formula}T⊃S, where T is admissible in F. If we consider the interpretation I characterizing T (i.e., we have {a mathematical formula}inN(a)∈I, for each {a mathematical formula}a∈T, and {a mathematical formula}outN(a)∈I, for each {a mathematical formula}a∈A∖T), then I does not contain fail and satisfies the rules (20), (21), (22), (23), (24), (25), (26). But this shows that we cannot have an answer set J which characterizes S. Due to rule (27) such an answer set J has to contain fail and by rules (25) and (26), J contains both {a mathematical formula}inN(a) and {a mathematical formula}outN(a) for each {a mathematical formula}a∈A. Note that we thus have {a mathematical formula}I⊂J (if I and J characterize the same initial guess S). Moreover, I satisfies the reduct of our program with respect to J. This can be seen by the fact that the only occurrence of default negation is in rule (27). In other words, there is an {a mathematical formula}I⊂J satisfying the reduct and thus J cannot be an answer set. This, however, is the desired outcome, since the initial guess S characterized by J is not a preferred extension.
       </paragraph>
       <paragraph>
        We still have to define the rules for the predicates eq and {a mathematical formula}undefeated(⋅). Basically, these predicates would be easy to define, but as we have seen in the discussion above, default negation plays a central role in the saturation technique (recall the functioning of {a mathematical formula}←notfail). We therefore have to find encodings which suitably define the required predicates only with a limited use of negation. In fact, we are only allowed to have stratified negation in these modules. Thus, both predicates eq and {a mathematical formula}undefeated(⋅) are computed via predicates {a mathematical formula}eq_upto(⋅) (resp., {a mathematical formula}undefeated_upto(⋅,⋅)) in the modules {a mathematical formula}πeq and {a mathematical formula}πundefeated, which are defined as follows.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        With these predicates at hand, we can now formally define the module for preferred extensions,{a mathematical formula} Then, for any AF F, the answer sets of {a mathematical formula}πprf(Fˆ) are in a one-to-one correspondence with the preferred extensions of F, i.e. {a mathematical formula}prf(F)≅AS(πprf(Fˆ)).
       </paragraph>
      </section>
      <section label="3.3.4">
       metasp encodings
       <paragraph>
        The following encodings for preferred semantics use the #minimize statement when evaluated with the subset-minimization semantics provided by metasp[93]. For our encodings we do not need prioritization and weights, therefore these are omitted (i.e., set to default) in the minimization statements. The minimization technique is realized through meta programming techniques, which themselves are answer-set programs. This operates as follows: The ASP encoding to solve is given to the grounder gringo{sup:10} which reifies the program, i.e., outputs a ground program consisting of facts, which represent the rules and facts of the original input encoding. The grounder is then again executed on this output with the meta programs that encode the optimization. Finally, claspD computes the answer sets. Note that here we use the version of clasp which supports disjunctive rules. Therefore, for a program π and an AF F we have the following program execution call.{a mathematical formula} Here, meta.lp, metaO.lp and metaD.lp are the encodings for the minimization statement. The statement optimize(incl,1,1) indicates that we use subset inclusion for the optimization technique using priority and weight 1.
       </paragraph>
       <paragraph>
        We now look at the encodings for preferred semantics which are easy to encode using the minimization statement of metasp. We only need the module {a mathematical formula}πadm and minimize the {a mathematical formula}out/1 predicate. This in turn gives us the subset-maximal admissible sets which captures the definition of preferred semantics.{a mathematical formula} As a result we get that for any AF F, the answer sets of {a mathematical formula}πprf_metasp(Fˆ) are in a one-to-one correspondence with the preferred extensions of F, i.e. {a mathematical formula}prf(F)≅AS(πprf_metasp(Fˆ)).
       </paragraph>
      </section>
      <section label="3.3.5">
       <section-title>
        Reasoning problems
       </section-title>
       <paragraph>
        As with other reduction-based approaches, the types of reasoning available depend on the ASP solver. Many of them feature enumeration of all solutions, as well as counting and also credulous and skeptical reasoning. For the metasp variant, the meta encodings can be augmented with constraints to achieve credulous and skeptical reasoning. Usually, when one uses an ASP program, like {a mathematical formula}πprf for preferred semantics, for an AF F, the ASP solver returns all answer sets of the program which correspond to all preferred extensions of F. For credulous or skeptical acceptance, one uses the respective reasoning problems of the ASP solver, which are sometimes referred to as brave or cautious reasoning. Note that the concrete usage depends on the particular solver.
       </paragraph>
       <paragraph>
        We exemplify this option for the solver dlv. To compute all arguments which are skeptically accepted under preferred semantics for a given AF F, we invoke{a mathematical formula}
       </paragraph>
      </section>
     </section>
     <section label="3.4">
      <section-title>
       Further reduction-based approaches
      </section-title>
      <paragraph>
       In the following, we summarize further approaches for reduction-based methods.
      </paragraph>
      <section label="3.4.1">
       <section-title>
        SAT extensions
       </section-title>
       <paragraph>
        Several extensions to the prototypical problem of SAT have been developed. Two interesting approaches include so-called minimal correction sets (MCSes) [96] and the backbone[97] of a Boolean formula in CNF. The former consists of a minimal subset of the clauses of an unsatisfiable formula, such that if we remove these clauses the resulting formula becomes satisfiable. A backbone of a satisfiable formula is simply the set of literals it logically entails. These concepts can be used to answer several reasoning problems for AFs and optimize existing algorithms. In [98] MCSes are applied to solve reasoning problems for semi-stable semantics by encoding the range of a set as satisfied clauses, and techniques for computing backbones are utilized to enhance the efficiency of the algorithms.
       </paragraph>
      </section>
      <section label="3.4.2">
       <section-title>
        Equational approaches
       </section-title>
       <paragraph>
        Equational approaches for abstract argumentation map the given reasoning problem at hand to a set of equations. Solutions of such equations then directly represent solutions of the original problems. One such approach was proposed by Gabbay [32], [77]. Here, one receives a system of equations where each argument is represented by a distinct variable with a domain of real numbers in the interval {a mathematical formula}[0,1]. Solutions to these systems of equations assign to each variable a number from the domain. The variable assignment corresponds to a labeling. If the variable of an argument a is mapped to 1, a is in, if it is mapped to 0 then it is out and undecided otherwise. This allows for easy identification of the labelings by inspecting the variable assignments. For instance, to compute complete labelings in this way we can consider the equation {a mathematical formula}f(a)=1−max(f(x1),…,f(xn)) where {a mathematical formula}{x1,…,xn} are the attackers of a. If all attackers of a are mapped to 0, then the value of a will be 1. If at least one of the attackers is “in”, i.e. it is mapped to 1, then {a mathematical formula}f(a)=0. Otherwise, if all attackers are undecided with {a mathematical formula}1&lt;f(xi)&lt;0 for each {a mathematical formula}1≤i≤n, then a will be undecided.
       </paragraph>
       <paragraph>
        Another work on equational approaches is by Osorio et al. [99], [100]. They encode preferred and semi-stable semantics as integer programs and then use the solver Xpress{sup:11} to compute the extensions.
       </paragraph>
      </section>
      <section label="3.4.3">
       <section-title>
        Monadic second order logic
       </section-title>
       <paragraph>
        A reduction approach going beyond pure propositional logic is to encode the reasoning problems in monadic second order logic (MSO). In this expressive predicate logic we may quantify over variables and unary predicates. Given such an MSO formula and an interpretation I, the task is to check whether I is a model of the formula. In [33] the authors encode several reasoning problems for AFs into an MSO formula φ. A given AF is then transformed into an interpretation I and one decides the reasoning problem by testing whether I is a model of φ. In this work certain building blocks for such encodings are introduced, which facilitate straightforward reductions of the different semantics to MSO. While the first MSO-encodings for abstract argumentation [101], [14] were introduced to obtain complexity-theoretic results in terms of tree-width, the advent of efficient systems for MSO [102], [103] turns MSO-encodings into an interesting alternative to implement abstract argumentation via the reduction method.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="4">
     <section-title>
      Direct approaches
     </section-title>
     <paragraph>
      In the previous section, we exhaustively discussed different reduction-based approaches for implementing abstract argumentation. But what about implementing procedures for abstract argumentation from scratch? While such an approach definitely requires more effort in implementation, it allows to access the framework directly, without having the overhead of transformation (and as a result a potential loss of structural information). Even more important, compared to the reduction approach, direct algorithms allow for an easy incorporation of short-cuts that are specific for the argumentation domain.
     </paragraph>
     <paragraph>
      In the reduction-based approach the distinction between computing all extensions and performing specific reasoning tasks is often delegated to the reasoner of the target formalism and thus can be neglected. When using direct approaches we have to take care (and advantage) of specific reasoning problems ourselves. Hence, in this section we will distinguish more explicitly between algorithms for enumerating all extensions and, for instance, algorithms that are specially tailored for computing “witnesses” for certain queries.
     </paragraph>
     <paragraph>
      Nowadays, the most successful approaches for direct algorithms can be categorized in three groups. First, there are so called labeling-based algorithms[104], [35], [38], which build on alternative characterizations for argumentation semantics using certain labeling functions of arguments. Second, we consider dialectical argument games, i.e., games played by two players alternating their arguments and where winning strategies ultimately characterize the acceptance status of an argument. Finally, there are dynamic programming algorithms, which are based on graph decompositions and results from (parameterized) complexity analysis. In the following, we present each of these approaches in detail.
     </paragraph>
     <section label="4.1">
      <section-title>
       Labeling-based algorithms
      </section-title>
      <paragraph>
       The class of labeling-based algorithms builds on the concept of argument labelings, with probably the most prominent variant being the 3-valued labelings due to Caminada and Gabbay [69]. For the formal definitions of complete and preferred labelings we refer to Section 2 (Definitions 4 &amp; 5).
      </paragraph>
      <paragraph>
       First labeling-based algorithms have been proposed in [34]; many further materializations of this concept can be found in the literature (see, e.g., [35], [38], [36]). The central observation underlying all these approaches is the following: Whenever one fixes the label of one argument this has immediate implications for the possible labels of the neighbors of this argument. For instance, if we are interested in complete labelings and label an argument a with in then all neighbors of a must be labeled out.
      </paragraph>
      <paragraph>
       In what follows, we focus on labeling-based algorithms for preferred semantics and distinguish between two classes: (i) algorithms which aim to enumerate all preferred extensions of a given AF; and (ii) algorithms that are tailored to perform specific reasoning tasks like skeptical and credulous reasoning.
      </paragraph>
      <section label="4.1.1">
       <section-title>
        Enumerating extensions
       </section-title>
       <paragraph>
        For enumerating extensions one can, in principle, simply enumerate all possible sets and check whether they are extensions. In general this is of course a quite inefficient approach. Therefore, labeling-based algorithms typically use a particular backtracking strategy to enumerate possible labelings, fixing the label of one argument in each step. In addition to the simple backtracking strategy, in each step the information of the new label is propagated to the neighbors of the argument. The different approaches to labeling-based algorithms have their own strategy for selecting the next arguments to be labeled as well as for the rules they apply for propagating labels. Algorithm 3 is an example for a labeling-based algorithm for computing preferred labelings in the spirit of [35].
       </paragraph>
       <paragraph>
        The main idea of Algorithm 3 is to start with the labeling that marks all arguments with in (the set containing all arguments) and to re-label arguments to either out or undec until the set becomes admissible. This strategy prevents the algorithm from considering all the (relatively small) admissible sets as candidates for preferred extension like other algorithms do (compare Algorithm 4).
       </paragraph>
       <paragraph>
        Let us explain Algorithm 3 in more detail. When applying the algorithm to an AF {a mathematical formula}F=(A,R), it first initializes the labeling {a mathematical formula}L such that each argument is labeled with in, i.e., {a mathematical formula}Lin=A, and the set {a mathematical formula}SL of candidate solutions only contains the labeling {a mathematical formula}(∅,∅,A), corresponding to the empty set. Then, in each step the algorithm picks an argument a which is labeled in but is not defended, i.e., there is an attacker that is not labeled out, and relabels it. We call such a relabel step a transition step. In Algorithm 3 a transition step is due to the following rules. First, the argument a is labeled to out and then all arguments {a mathematical formula}y∈{a}+ (a and all arguments attacked by a) are checked for being valid labeled out, i.e., in case y is neither labeled in nor is attacked by an argument labeled in, we change the label of y to undec. In [35] it is shown that each preferred extension can be obtained from the initial labeling that labels each argument to in by a finite sequence of such transition steps and further that each terminated sequence (which is indeed finite) corresponds to an admissible set.
       </paragraph>
       <paragraph>
        This simple algorithm has several weaknesses which have been addressed in the literature. First, consider line 5 of Algorithm 3. For each {a mathematical formula}a∈Lin s.t. {a mathematical formula}∃b∉Lout:(b,a)∈R one starts a transition and then recursively calls the procedure. This causes the branching in the search procedure and thus we want to minimize the number of arguments to be considered here. To this end, [35] introduces a notion of so-called super-illegal arguments which form a subset of the above mentioned arguments and can be relabeled first without branching in the algorithm. That is, in case there is at least one super-illegal argument the algorithm first considers all of them (in arbitrary order) before branching among the other arguments. However, even with this improvement, it can happen that several branches of the algorithm may produce the same candidate extension. For instance, consider the AF {a mathematical formula}F=({a,b,c},{(a,b),(b,a),(b,c),(c,b)}). The preferred labeling {a mathematical formula}〈{b},{a,c},∅〉 will be produced by two branches of the algorithm, by the branch choosing a in the first step (and assign out to a) and then choosing c in the second step (and assigning out as well), but also by the branch selecting c first and then a in the second step. As such duplicates are indeed a waste of computational resources, this is a weak point. Other algorithms [34], [36] avoid such duplicates as they use a different strategy to branch in the search space (see, for instance, Algorithm 4).
       </paragraph>
       <paragraph>
        Next, consider lines 16–23 in the algorithm. This part ensures the ⊆-maximality of the labelings in {a mathematical formula}SL. As the set {a mathematical formula}SL can be of exponential size (even if the number of preferred labelings is small) testing whether a new candidate is ⊆-maximal and updating the set {a mathematical formula}SL is costly. Hence, alternative approaches to deal with ⊆-maximality have been proposed. Firstly, [34] used a criterion for maximality that does not make use of the other extensions explicitly. Instead, it exploits the observation that a complete labeling {a mathematical formula}L is a preferred labeling iff there is no subset S of {a mathematical formula}Lundec such that the set {a mathematical formula}Lin∪S is admissible. In particular, for candidate labelings where all arguments are labeled either in or out, this avoids an explicit check of maximality (such labelings correspond to stable extensions). Secondly, in [36] the authors provide a smart traversal of the search space such that one can avoid deleting sets from {a mathematical formula}SL, i.e., in each step one can decide whether the current candidate is preferred or not, by only using previously computed preferred labelings (see Algorithm 4).
       </paragraph>
       <paragraph>
        Let us thus have a closer look on Algorithm 4 next. This algorithm for preferred semantics follows the work of [34] and [36]. The main difference to Algorithm 3 is the way the search space is explored. Starting with all arguments being unlabeled in each step the algorithm chooses one (unlabeled) argument and branches between the possible labels for this argument. Once a label is chosen it is never changed again and thus no labeling can be produced twice. Another apparent difference is that the algorithm uses four labels instead of just three labels. We denote such a four valued labeling {a mathematical formula}L as quadruple {a mathematical formula}〈Lin,Lout,Latt,Lundec〉.{sup:12} The intuition behind the labels in and out is the same as for three valued labelings, while arguments which attack an in labeled argument, but are not attacked by such an argument, are labeled att. Finally, arguments which are labeled undec have no conflict with in labeled arguments.
       </paragraph>
       <paragraph>
        This algorithm iterates over all admissible sets and tests whether they are ⊆-maximal. As for each argument a the algorithm first tries to add an argument to {a mathematical formula}Lin before considering the variant without a, we can be sure that supersets are always considered first. Hence, we never have to remove a labeling from the set {a mathematical formula}SL. The pitfall of Algorithm 4 is the potential exponential number of admissible labelings (even for a small number of preferred extensions) which are all considered by the algorithm.
       </paragraph>
       <paragraph>
        Let us briefly compare Algorithm 3 and Algorithm 4 on two extreme cases: (i) the AF {a mathematical formula}F1=(A,A×A) with the total attack relation and (ii) the AF {a mathematical formula}F2=(A,∅) with the empty attack relation. In {a mathematical formula}F1 the empty set is the only admissible set and thus also the only preferred extension. As there is just one admissible set, Algorithm 4 never branches and thus terminates after a linear number of steps. However Algorithm 3 has to update all arguments to undec. As this can be done in an arbitrary order we have n! many branches producing the same extension. For {a mathematical formula}F2 there is just one preferred extension but Algorithm 4 considers all {a mathematical formula}2|A| admissible sets. In contrast, Algorithm 3 terminates immediately. As different labeling-based algorithms behave good on different kind of argumentation frameworks, empirical evaluations are an important issue. A first step in that direction is done in the work of Nofal et al. [105], [36], [37] where the performance of different labeling-based algorithms for preferred semantics is compared on randomly generated AFs.
       </paragraph>
       <paragraph>
        Here we have only considered the case of preferred semantics, but for most of the semantics labeling-based algorithms have been proposed in the literature: an algorithm for grounded semantics is given in [35]; an algorithm for admissible labelings can be easily obtained from Algorithm 4 (by dropping the ⊆-maximality test in line 14); for complete semantics one can adapt Algorithm 3; for stable semantics, see [35]; algorithms for semi-stable and stage semantics can be found in [104], [106], [35]. Recently, [105] studied improved algorithms for enumerating grounded, complete, stable, semi-stable and stage semantics. Labeling-based algorithms are implemented in the ArguLab system [107] as well as in ArgTools [36] (see also Section 5.1).
       </paragraph>
      </section>
      <section label="4.1.2">
       <section-title>
        Reasoning problems
       </section-title>
       <paragraph>
        Having an algorithm for enumerating all extensions of an AF at hand, one can immediately use them to answer reasoning problems by simply testing each extension for the queried argument. However, this is probably not the most efficient way. Given that we are only interested in the acceptance of a certain argument, we might directly try to produce a witness (or counter-example) for this argument instead of computing all extensions. In this section we discuss dedicated algorithms for reasoning problems. As an example, we review the work of Verheij [38], a credulous acceptance algorithm for preferred semantics, which is implemented in the CompArg system (see Section 5.1).
       </paragraph>
       <paragraph>
        The idea behind the algorithm is that we start with the argument (or the set of arguments) for which we test credulous acceptance and iteratively add arguments to defend all arguments in our sets. The outlined Algorithm 5 starts with labeling the queried argument with in and all the other arguments with undec. Then, it iterates the following two steps. First, check whether the set {a mathematical formula}Lin is conflict-free and if so label all arguments attacking {a mathematical formula}Lin with out. Otherwise terminate the branch of the algorithm. In the second step, we pick for each argument a which is labeled out but not attacked by an argument labeled in, an undec labeled attacker b of a and label it with in. In case there are several such arguments, we start a new branch of the algorithm for each choice. If no such argument exists we terminate the branch of the algorithm. We stop a branch of the algorithm as soon as no more changes to labelings are made. In that case we have reached an admissible labeling acting as proof for the credulous acceptance of the queried argument.
       </paragraph>
       <paragraph>
        We give a few more comments for Algorithm 5. In contrast to the previous algorithm, we store several partial extensions (partial proofs) at the same time and also terminate as soon as we have found an admissible set. In line 1 of the algorithm one has to decide whether to use a queue or a stack for storing these partial proofs. The choice determines the search strategy in the space of partial proofs: The former would give a breadth-first search (as suggested in [38]) while the latter yields a depth-first search.
       </paragraph>
       <paragraph>
        Next, consider the sets {a mathematical formula}L′ in line 11. These are simply the sets where for each argument {a mathematical formula}a∈Lout∖Lin+ we pick one argument b attacking a and add b to {a mathematical formula}Lin+. However, in each step there might be exponentially many such sets {a mathematical formula}L′. In case there is no such set, we know the partial proof cannot be expanded to a proof and we can close this branch of the search tree. Moreover, it can happen that we consider the same partial proof twice, and thus it might be a good idea to store already considered partial proofs.
       </paragraph>
       <paragraph>
        Finally, let us mention that beside the work of Verheij [38], Doutre and Mengin [34] suggest to start from an enumeration algorithm similar to Algorithm 4 but employing several shortcuts for credulous and skeptical reasoning.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Dialectical proof-procedures (dialogue games)
      </section-title>
      <paragraph>
       A popular approach for obtaining proof procedures for abstract argumentation is based on so called dialogue games (see, e.g., [35], [39]). Such games are played by two players, the proponent (Pro) and the opponent (Opp), on a given argumentation framework. The proponent and opponent alternate in raising arguments of the AF attacking arguments previously raised by the other player (according to certain rules). A player loses the game if she cannot raise any argument. Typically, an argument a being accepted is equivalent to one player having a winning strategy in the dialogue game when started with a. However, in certain dialogue games it suffices that the proponent wins one of the possible dialogues starting with argument a to guarantee the acceptance of a[108]. By their nature, dialogue games are typically dedicated to a specific reasoning problem, but sometimes they can also be used to actually compute extensions.
      </paragraph>
      <paragraph>
       Such algorithms are implemented in the Dungine system [109], in the Dung-O-Matic Java library (see Section 5.1) and also are used in Visser's Epistemic and Practical Reasoner,{sup:13} a tool for argumentation with propositional languages (however, it is not a dedicated tool for abstract argumentation).
      </paragraph>
      <section label="4.2.1">
       <section-title>
        Games for grounded and preferred semantics
       </section-title>
       <paragraph>
        In the following, we consider games for grounded semantics and for credulous acceptance with preferred semantics, both borrowed from [35]. In both cases the game is started by Pro raising the argument in question, and then Pro and Opp alternately raise an argument attacking the previous argument in the dialogue. Finally, a dialogue is won by the player making the last move, i.e., the player forcing the dialogue into a situation where the other player has no legal move left. The dialogue games correspond to our reasoning problems in the sense that Pro has a winning strategy in the game iff the argument is accepted. The games for the different semantics and reasoning problems differ in the allowed moves for the players, where typically Pro and Opp have different rule sets for legal moves.
       </paragraph>
       <section>
        <section-title>
         A game for grounded semantics
        </section-title>
        <paragraph>
         First, consider a game that provides, given an AF {a mathematical formula}F=(A,R) and argument {a mathematical formula}a∈A, a proof whether a is contained in the grounded extension of F. The game is given by the following rules of allowed moves of each player.
        </paragraph>
        <paragraph>
         Legal moves:
        </paragraph>
        <list>
         <list-item label="•">
          For Pro: Any argument y that (i) attacks the last argument raised by Opp and (ii) is conflict-free with all arguments previously raised by Pro.
         </list-item>
         <list-item label="•">
          For Opp: Any argument y that attacks the last argument raised by Pro.
         </list-item>
        </list>
        <paragraph>
         One can easily show that a is in the grounded extension iff Pro has a winning strategy for the above game [35].
        </paragraph>
        <paragraph label="Example 7">
         Consider the AF from Example 1. The grounded extension is {a mathematical formula}{a,d}. Now, if Pro starts a dialogue game with raising argument a, then, as a is not attacked at all, Opp has no legal move to reply. Hence, Pro has a winning strategy which reflects the fact that a is in the grounded extension. Next, consider Pro starts a dialogue game with raising argument b (an argument not in the grounded extension). Then, Opp has two legal moves, either raising a or c. In the first case Opp wins the game as a is not attacked at all and thus Pro has no legal moves. Hence, Pro has no winning strategy when starting with b.
        </paragraph>
       </section>
       <section>
        <section-title>
         A game for credulous preferred acceptance
        </section-title>
        <paragraph>
         Now let us consider a game that allows us, given an AF {a mathematical formula}F=(A,R) and argument {a mathematical formula}a∈A, to prove whether a is contained in some preferred extension of F (or equivalently in some admissible set). The following game is quite similar to the game for grounded semantics, the only difference being that Opp is not allowed to repeat its moves. Restricting the legal moves of Opp makes it easier to have a winning strategy for Pro.
        </paragraph>
        <paragraph>
         Legal moves:
        </paragraph>
        <list>
         <list-item label="•">
          For Pro: Any argument y that (i) attacks the last argument raised by Opp and (ii) is conflict-free with all arguments previously raised by Pro.
         </list-item>
         <list-item label="•">
          For Opp: Any argument y that (i) attacks the last argument raised by Pro and (ii) was not previously used by Opp.
         </list-item>
        </list>
        <paragraph>
         It can be shown that Pro has a winning strategy for the above game iff the argument a is in an admissible set. The latter is well known to be equivalent to argument a being credulously accepted with preferred semantics [35].
        </paragraph>
        <paragraph label="Example 8">
         Consider the very simple AF {a mathematical formula}F=({a,b},{(a,b),(b,a)}) with the admissible sets {}, {a mathematical formula}{a} and {a mathematical formula}{b}. Now, let us test for the credulous acceptance of a, i.e., Pro starts the game with raising a. Then, the only option of Opp is to use b, Pro can use a again to defeat b. Now Opp has no legal move left, as it cannot use b again. Hence, Pro has a winning strategy for a. Notice that in the grounded game Pro and Opp would loop forever with raising a and b.
        </paragraph>
        <paragraph>
         The critical reader might observe that such dialogue games are indeed no algorithms. However, it is more or less straight forward to build algorithms out of such games, using search procedures in the strategy space of these games, branching along the possible moves (see [39], [110]). The resulting algorithms are indeed of a similar type as the previously discussed labeling-based algorithms.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="4.3">
      <section-title>
       Dynamic-programming based approach
      </section-title>
      <paragraph>
       As discussed in Section 2 most of the reasoning problems in abstract argumentation were shown to be computationally intractable, i.e., NP-hard or even harder. Hence, there is a lot of work on first classifying the exact (sources of) complexity of these problems and second on identifying problem classes that can be solved efficiently. Here we discuss algorithms based on ideas from parameterized complexity theory. The main observation is that binding a certain problem parameter to a fixed constant makes many of the intractable problems tractable. This property is referred to as fixed-parameter tractability (FPT) (see, e.g., [111]). The complexity class FPT consists of problems that can be computed in {a mathematical formula}f(k)⋅nO(1) where f is a function that depends on the problem parameter k, and n is the input size.
      </paragraph>
      <paragraph>
       One important parameter for graph problems is the tree-width of a graph that is defined along so-called tree decompositions. Intuitively, the tree-width measures the tree-likeliness of a graph, in particular connected graphs of tree-width 1 are exactly trees. AFs can be seen as directed graphs and therefore the parameter tree-width can be directly applied to them. Indeed, many argumentation problems have been shown to be solvable in linear time for AFs of bounded tree-width [41], [33].
      </paragraph>
      <paragraph>
       In this section we present a dynamic-programming based approach for abstract argumentation that is defined on tree decompositions. First introduced in [112], this approach especially aimed at the development of efficient algorithms that turn complexity-theoretic results into practice. The algorithms from [112] are capable of solving credulous and skeptical reasoning problems under admissible and preferred semantics. Later, this approach was extended to work with stable and complete semantics [42]. Further fixed-parameter tractability results were obtained for AFs with bounded clique-with [113] and in the work on backdoor sets for argumentation [114]. Negative results for other graph parameters like bounded cycle-rank, directed path-width, and Kelly-width can be found in [40].
      </paragraph>
      <paragraph>
       The approach presented here is put into practice in the dynPARTIX tool [42], [115] as well as in the D-FLAT system [102], [116]. While the former is a dedicated tool for argumentation (see also Section 5), the latter is a general framework that allows one to declaratively specify algorithms on tree decompositions by means of ASP.
      </paragraph>
      <paragraph>
       In the following, we first introduce tree decompositions. We then present the general idea behind the dynamic-programming algorithms and provide an example based on admissible semantics. Finally, we discuss how the basic algorithm that enumerates all admissible sets can be adapted for other reasoning problems.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Tree decompositions
       </section-title>
       <paragraph>
        A tree decomposition [117] is a mapping of a graph to a tree, defined as follows.
       </paragraph>
       <paragraph label="Definition 9">
        A tree decomposition of an undirected graph {a mathematical formula}G=(V,E) is a pair {a mathematical formula}(T,X) where {a mathematical formula}T=(VT,ET) is a tree, with vertices {a mathematical formula}VT and edges {a mathematical formula}ET, and {a mathematical formula}X:VT→2V is a function that assigns to every vertex {a mathematical formula}t∈VT of the tree a so-called bag, i.e. a set {a mathematical formula}Xt⊆V of vertices from the original graph. These sets of vertices {a mathematical formula}(Xt)t∈VT have to satisfy the following conditions:
       </paragraph>
       <list>
        <list-item label="(i)">
         {a mathematical formula}⋃t∈VTXt=V
        </list-item>
        <list-item label="(ii)">
         {a mathematical formula}(vi,vj)∈E⇒∃t∈VT:{vi,vj}⊆Xt
        </list-item>
        <list-item label="(iii)">
         {a mathematical formula}v∈Xt1∧v∈Xt2∧t3∈path(t1,t2)⇒v∈Xt3
        </list-item>
       </list>
       <paragraph>
        Conditions (i) and (ii) guarantee that no information of the original graph is lost, i.e., all vertices have to appear in at least one bag {a mathematical formula}Xt and connected vertices have to appear together in some bag. Condition (iii) is the connectedness condition, ensuring that all bags containing the same vertex are connected in {a mathematical formula}T. In general a graph may have multiple tree decompositions. The parameter tree-width is defined on the “best” tree decompositions one can get for a graph.
       </paragraph>
       <paragraph label="Definition 10">
        The width of a tree decomposition {a mathematical formula}(T,X) is defined as {a mathematical formula}max(|Xt∈Vt|)−1. The tree-width of a graph G is the minimum width of all possible tree decompositions of G.
       </paragraph>
       <paragraph>
        Here, we will only consider normalized tree decompositions, which can be easily obtained from standard tree-decompositions [118]. Normalized tree decompositions comply with Definition 9, but only consist of the following four different node types:
       </paragraph>
       <list>
        <list-item label="1.">
         JOIN node: A node t which has two children {a mathematical formula}t′ and {a mathematical formula}t″, {a mathematical formula}Xt=Xt′=Xt″.
        </list-item>
        <list-item label="2.">
         INTRODUCTION node: A node t having exactly one child {a mathematical formula}t′ s.t. {a mathematical formula}|Xt|=|Xt′|+1 and {a mathematical formula}Xt′⊂Xt.
        </list-item>
        <list-item label="3.">
         REMOVAL node: A node t having exactly one child {a mathematical formula}t′ s.t. {a mathematical formula}|Xt|=|Xt′|−1 and {a mathematical formula}Xt⊂Xt′.
        </list-item>
        <list-item label="4.">
         LEAF node: A node t that has no child nodes.
        </list-item>
       </list>
       <paragraph>
        Additionally, we assume that for root node r of the normalized tree-decomposition, we have {a mathematical formula}Xr=∅. Note that tree decompositions are defined on undirected graphs. We relate AFs (see Definition 1) to tree decompositions by defining that a tree decomposition of an AF {a mathematical formula}F=(A,R) is a tree decomposition of an undirected graph {a mathematical formula}G=(A,R′) where A are the arguments of the AF and {a mathematical formula}R′ are the edges R without orientation. In Fig. 3 one possible normalized tree decomposition of our example AF from Fig. 1 is given. The width of this tree decomposition is 2. Note that the computation of an optimal tree decomposition (w.r.t. width) is known to be an NP-complete problem [119]. However, the problem is fixed parameter tractable w.r.t. treewidth [120]. Thus, for AFs with small treewidth an optimal tree decomposition can be computed efficiently. Moreover, there exist several heuristic-based algorithms that provide “good” tree decompositions in polynomial time (see, e.g., [121], [15], [122]).
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Dynamic programming
       </section-title>
       <paragraph>
        In the following, we present a dynamic-programming algorithm for computing admissible sets (and deciding credulous acceptance of arguments) as proposed in [112]. Algorithms for other semantics and reasoning problems can be defined similarly.
       </paragraph>
       <paragraph>
        In a nutshell, the idea of dynamic programming as used here is as follows. First, a tree decomposition of the given problem instance (AF) is constructed. The tree of that decomposition is then traversed in bottom-up order. Due to the definition of tree decompositions it is possible to only work on the information that is locally available in the bags when traversing the tree. In every step we compute so-called colorings, a data structure to represent (partial) solutions for our problem. These colorings are computed based on the arguments contained in the bag of the current node as well as colorings from the child node(s). The idea of dynamic programming is hereby realized as follows: If we encounter a REMOVAL node during bottom-up traversal then we can exploit the fact that the “removed” node will never reappear in another bag later on during the traversal. We can therefore discard information for (partial) solutions in case it contains a removed argument that does not fulfill the properties of our semantics. The solutions for the whole input instance can be obtained by a final computation step in the root node.
       </paragraph>
       <section>
        <section-title>
         Sub-frameworks
        </section-title>
        <paragraph>
         Towards the dynamic programming algorithm we have to introduce some notions that underlie the approach. First, for a tree decomposition {a mathematical formula}(T,X) of an AF F, let {a mathematical formula}t∈T. For a sub-tree of {a mathematical formula}T that is rooted in t we define {a mathematical formula}X≥t as the union of all bags within this sub-tree, i.e., {a mathematical formula}X≥t contains all arguments of this sub-tree. For instance in the tree decomposition from Fig. 3 we have {a mathematical formula}X≥t3=Xt3∪Xt2∪Xt1={a,b,c}. Additionally, {a mathematical formula}X&gt;t denotes {a mathematical formula}X≥t∖Xt, i.e., all arguments from the bags in the sub-tree excluding the arguments from the bag of t (even if they appear in another bag). Regarding the example we have {a mathematical formula}X&gt;t3=(Xt2∪Xt1)∖Xt3={a}. Furthermore, for a {a mathematical formula}t∈T the sub-framework in t, denoted by {a mathematical formula}Ft, consists of all arguments {a mathematical formula}x∈Xt and the attack relations {a mathematical formula}(x1,x2) where {a mathematical formula}x1,x2∈Xt and {a mathematical formula}(x1,x2)∈R. The sub-framework induced by the sub-tree rooted in t, denoted by {a mathematical formula}F≥t, consists of all arguments {a mathematical formula}x∈X≥t and the attack relations {a mathematical formula}(x1,x2) where {a mathematical formula}x1,x2∈X≥t and {a mathematical formula}(x1,x2)∈R. Consider the tree decomposition given in Fig. 4(a). For each node t, the arguments that are contained in bag {a mathematical formula}Xt are marked with solid cycles. The sub-framework {a mathematical formula}Ft consists of the arguments in solid cycles and all solid attack arrows. In combination with the dotted parts we obtain the induced sub-frameworks {a mathematical formula}F≥t.
        </paragraph>
       </section>
       <section>
        <section-title>
         Restricted sets
        </section-title>
        <paragraph>
         The idea is now to analyze the (sub)-framework {a mathematical formula}F≥t for every node t during our traversal. {a mathematical formula}X&gt;t denotes all arguments that were already removed from the bags of the sub-tree rooted at t. Hence, these arguments are already completely processed by the algorithm and we can define {a mathematical formula}X&gt;t-restricted admissible sets. We distinguish between attacks from arguments in {a mathematical formula}X&gt;t and {a mathematical formula}Xt. While attacks from arguments {a mathematical formula}Xt might be counter attacked by arguments appearing later, i.e., somewhere above in the tree decomposition, this cannot happen for arguments in {a mathematical formula}X&gt;t. Thus, we define an {a mathematical formula}X&gt;t-restricted admissible set S for a sub-framework {a mathematical formula}F≥t such that first S has to be conflict-free and second it has to defend itself against the arguments in {a mathematical formula}X&gt;t∖S. So the {a mathematical formula}X&gt;t-restricted admissible sets for a sub-framework {a mathematical formula}F≥t are all the sets that might become admissible in a framework {a mathematical formula}F≥t′ for some node {a mathematical formula}t′ above in the tree decomposition.
        </paragraph>
       </section>
       <section>
        <section-title>
         Colorings
        </section-title>
        <paragraph>
         In order to represent the information that is computed within each node during traversal we need an appropriate data structure. We define so-called colorings that allow us to store information of relationships between arguments in {a mathematical formula}X≥t solely by assigning colors to arguments in {a mathematical formula}Xt. For admissible semantics, this is described by a function {a mathematical formula}C:Xt→{in,out,att,ud}. Intuitively, in denotes that an argument is contained in the set S of selected arguments, out describes that it is outside the set because it is attacked by S, att means that the argument attacks S but is not attacked by S and ud describes that the status is undecided (it is neither attacked nor attacks S). Notice that this definition is quite close to the definition of the labelings used in Algorithm 4. The main difference is that a labeling labels the whole set of arguments while colorings are only applied to a small part of the set of arguments, even if other parts have already been considered.{sup:14} Towards a more concise notion, for a coloring C, the set {a mathematical formula}[C]in denotes all arguments that are colored with in.
        </paragraph>
        <paragraph>
         We are in particular interested in colorings corresponding to at least one restricted admissible set, so-called valid colorings. Given a coloring C for node t, we define the extensions of C, {a mathematical formula}et(C), as the collection of {a mathematical formula}X&gt;t-restricted admissible sets S for {a mathematical formula}F≥t that satisfy the following conditions for each {a mathematical formula}a∈Xt:{a mathematical formula} If {a mathematical formula}et(C)≠∅, C is called a valid coloring for t.
        </paragraph>
       </section>
       <section>
        <section-title>
         Goal
        </section-title>
        <paragraph>
         Our overall goal is to compute admissible sets of an AF. The tree decomposition is traversed in bottom-up order. In each node we use our data structure of colorings and compute all valid colorings C for every node t. As shown in [112], there exists a one-to-one mapping between the extensions of C, {a mathematical formula}et(C), and the {a mathematical formula}X&gt;t-restricted admissible sets for {a mathematical formula}F≥t. Moreover, we assume that the root node r has an empty bag of arguments. Hence, by computing the valid colorings C for r we obtain the {a mathematical formula}X&gt;r-restricted admissible sets for {a mathematical formula}F≥r. As {a mathematical formula}X&gt;r=A these correspond to the admissible sets for our original AF instance.
        </paragraph>
       </section>
       <section>
        <section-title>
         Node operations
        </section-title>
        <paragraph>
         In order to achieve tractability we have to compute valid colorings in bottom-up order without explicit computation of the corresponding restricted admissible sets {a mathematical formula}et(C). Hence, we define operations for the computation of valid colorings which are applied recursively on the colorings computed at the child node(s). Detailed arguments for the correctness of these operations are given in [40], we shall just sketch the intuition behind them here.
        </paragraph>
        <paragraph>
         Let {a mathematical formula}t∈T be a node and {a mathematical formula}t′ and {a mathematical formula}t″ be its children, if they exist. Depending on the node type of t we apply the following operations:
        </paragraph>
        <paragraph>
         LEAF node: Here we have {a mathematical formula}Ft=F≥t and thus the restricted admissible sets are just the conflict-free sets. So we compute the conflict-free sets of {a mathematical formula}Ft and then build a coloring for each conflict-free set S as follows:{a mathematical formula}
        </paragraph>
        <paragraph label="Example 9">
         Consider the leaf node{a mathematical formula}t5 with bag {a mathematical formula}{a,b} in Fig. 4(b). The computed colorings represent the conflict-free (and ∅-restricted admissible) sets for {a mathematical formula}F≥t5. For instance, the second labeling C with {a mathematical formula}C(a)=att,C(b)=in corresponds to the ∅-restricted admissible/conflict-free set {a mathematical formula}{b}, which however is not admissible for {a mathematical formula}F≥t5. REMOVAL node: In a removal node we have {a mathematical formula}Xt=Xt′∖{a} for some node a. For each valid coloring of {a mathematical formula}t′ with {a mathematical formula}C(a)≠att we build a new coloring for node t by simply deleting the value for a and keeping all the remaining values. As we remove the argument a, by the connectedness of tree-decompositions, we know that we have already considered all neighbors of a. Now suppose C is a valid coloring for {a mathematical formula}t′, but has {a mathematical formula}C(a)=att, i.e., a must be attacked to make the set admissible. As all neighbors of a were already considered we know that the corresponding sets cannot be extended to an admissible set and thus we delete this coloring. If {a mathematical formula}C(a)≠att, then a does not cause a problem w.r.t. admissibility and as already all neighbors were considered will never do so.
        </paragraph>
        <paragraph label="Example 10">
         Node {a mathematical formula}t4 in Fig. 4(b) is a removal node with {a mathematical formula}Xt4=Xt5\{a}. According to the definition for the computation of colorings in removal nodes the colorings for {a mathematical formula}t4 are obtained from the colorings of {a mathematical formula}t5 except for the second coloring {a mathematical formula}C′ (where {a mathematical formula}C′(a)=att and {a mathematical formula}C′(b)=in). Here, argument b is not defended against the attack from a. Therefore, {a mathematical formula}{b} is not an {a mathematical formula}X&gt;t4 (or {a mathematical formula}{a})-restricted admissible set for {a mathematical formula}F≥t4. INTRODUCTION node: For an introduction node we have {a mathematical formula}Xt=Xt′∪{a}. We build two colorings {a mathematical formula}C+a and {a mathematical formula}C+˙a for t as described below. The first is always valid while the second is only valid if {a mathematical formula}[C+˙a]in is conflict-free.{a mathematical formula}{a mathematical formula}
        </paragraph>
        <paragraph>
         In an introduction node we add a new argument to the framework. So for each extension we get two new candidates, one where we leave the argument a outside the extension (case {a mathematical formula}C+a) and one where we add a to the extension (case {a mathematical formula}C+˙a). For the first coloring we just have to compute whether to color the new argument by out, att or ud while for the second coloring we first have to check that the set is still conflict-free and if so we have to update the colors of the old arguments according to their attacks with a. That is, if {a mathematical formula}(a,b)∈Ft then b is labeled out and if {a mathematical formula}(b,a)∈Ft and b is not already labeled out then it is labeled att.
        </paragraph>
        <paragraph label="Example 11">
         In node {a mathematical formula}t3 in Fig. 4(b) argument c is introduced, i.e. {a mathematical formula}t3 is an introduction node. Consider the second coloring {a mathematical formula}C′ of {a mathematical formula}t4 where {a mathematical formula}C′(b)=ud. Here we have two possibilities for adding c. If we do not add c to the set of selected arguments we obtain a coloring {a mathematical formula}C1 for {a mathematical formula}t3 where both arguments b and c are set to ud. On the other hand, by adding c to the set of selected arguments we obtain the coloring {a mathematical formula}C2 where {a mathematical formula}C2(b)=out and {a mathematical formula}C2(c)=in. Note that the color of b changes in this case from ud to out as c attacks b. Furthermore, note that this coloring coincides with the coloring obtained from {a mathematical formula}C″ of {a mathematical formula}t4 with {a mathematical formula}C″(b)=out in case c is added to the set of selected arguments. Hence, {a mathematical formula}C2 represents both {a mathematical formula}{a,c} and {a mathematical formula}{c} which are {a mathematical formula}X&gt;t3 (or {a mathematical formula}{a})-restricted admissible sets for {a mathematical formula}F≥t3. JOIN node: A JOIN node has two child nodes {a mathematical formula}t′,t″ with {a mathematical formula}Xt=Xt′=Xt″. We combine each valid coloring C of {a mathematical formula}t′ with each valid coloring D of {a mathematical formula}t″ such that {a mathematical formula}[C]in=[D]in and build a new coloring as follows: All arguments in {a mathematical formula}[C]in are colored in. An argument {a mathematical formula}x∈Xt is colored with out iff one of {a mathematical formula}C,D colors it with out. The remaining arguments are colored with att iff one of {a mathematical formula}C,D colors it with att and ud iff both {a mathematical formula}C,D color it with ud.
        </paragraph>
        <paragraph>
         The intuition behind this step is the following. The frameworks {a mathematical formula}F≥t′ and {a mathematical formula}F≥t″ are different parts of F that only intersect on {a mathematical formula}Xt. So an extension of {a mathematical formula}F≥t′ can be combined with an extension of {a mathematical formula}F≥t″ as long as they coincide on the intersection. The join rule for the colorings corresponds to the fact that an argument attacks/is attacked by the union of two sets iff it attacks/is attacked by at least one of them.
        </paragraph>
        <paragraph label="Example 12">
         In the join node{a mathematical formula}t2 in Fig. 4(b) two colorings C and D are combined in case {a mathematical formula}[C]in=[D]in, i.e., they coincide on their in-colored arguments. Consider the second coloring {a mathematical formula}C′ of {a mathematical formula}t3 where {a mathematical formula}C′(b)=out and {a mathematical formula}C′(c)=ud as well as the second coloring {a mathematical formula}D′ of {a mathematical formula}t6 where {a mathematical formula}D′(b)=ud and {a mathematical formula}D′(c)=out. Based on the definition of the join operator their combination results in a coloring C with {a mathematical formula}C(b)=out and {a mathematical formula}C(c)=out which represents one {a mathematical formula}X&gt;t2 (or {a mathematical formula}{a,d,e})-restricted admissible set for {a mathematical formula}F≥t2, namely {a mathematical formula}{a,d}.
        </paragraph>
       </section>
      </section>
      <section label="4.3.3">
       <section-title>
        Reasoning problems
       </section-title>
       <paragraph>
        The dynamic-programming based approach can be used to solve several reasoning problems.
       </paragraph>
       <section>
        <section-title>
         Enumerating extensions
        </section-title>
        <paragraph>
         In order to enumerate all extensions for a semantics σ the tree decomposition is traversed a second time in top-down order after the initial bottom-up computation. Thereby only relevant solutions (the extensions) are considered. Note that we do not compute {a mathematical formula}et(C) explicitly during the first traversal as this would destroy tractability. In particular, it is guaranteed that the second traversal only considers colorings that yield a solution. So enumerating extensions can be done with linear effort for each extension. For our running example AF F we obtain {a mathematical formula}Enumadm(F)={∅,{a},{d},{a,d}}. In Fig. 4(b) this result is represented by the column {a mathematical formula}et0(⋅) in node {a mathematical formula}t0.
        </paragraph>
       </section>
       <section>
        <section-title>
         Counting extensions
        </section-title>
        <paragraph>
         In case we are only interested in the number of extensions a second traversal of the tree decomposition is not necessary. It is sufficient to calculate the number of {a mathematical formula}X&gt;t-restricted admissible sets that are represented by the respective coloring immediately during the bottom-up traversal. The columns {a mathematical formula}Cnt in Fig. 4(b) show the number of represented sets for each coloring. Consider for example coloring C of {a mathematical formula}t3 where {a mathematical formula}C(b)=out and {a mathematical formula}C(c)=in: C represents two {a mathematical formula}X&gt;t3-restricted admissible sets as it results from the two colorings of {a mathematical formula}t4 where each represents one restricted set. At the root node we obtain {a mathematical formula}Countadm(F)=4.
        </paragraph>
       </section>
       <section>
        <section-title>
         Deciding credulous acceptance
        </section-title>
        <paragraph>
         Credulous acceptance of an argument x can be decided by storing an additional flag together with each coloring: In case {a mathematical formula}C(x) for a coloring C is set to in, C is marked. Additionally, this information is passed upwards the tree: If a coloring is constructed on basis of a marked coloring it is marked as well. Finally, in case the coloring at the root node is marked, we know that x is credulously accepted. In Fig. 4(b) this is represented by the columns {a mathematical formula}Crd where we want to decide whether a is credulously accepted. For {a mathematical formula}Credadm(a,F) we obtain yes. For skeptical acceptance, a dual approach can be employed (see [40]).
        </paragraph>
       </section>
      </section>
      <section label="4.3.4">
       <section-title>
        Problems beyond NP
       </section-title>
       <paragraph>
        So far we have only considered admissible semantics but the dynamic programming approach is in no way limited to problems that are in NP. Harder problems, however, generally need a more complicated data structure. Consider preferred semantics where, for example, deciding {a mathematical formula}Skeptprf is known to be {a mathematical formula}Π2P-complete. We only give a rough outline of the ideas to extend the above algorithm for preferred semantics, for details the interested reader is referred to [40].
       </paragraph>
       <paragraph>
        As preferred extensions are subset-maximal admissible sets in order to guarantee subset maximality one can use pairs {a mathematical formula}(C,Γ) as a data structure within a node t instead of colorings. Here, C is a coloring and Γ is a set of colorings, called certificates. The certificates characterize all {a mathematical formula}X&gt;t-admissible sets which are strictly larger than the {a mathematical formula}X&gt;t-admissible sets characterized by C. One can consider Γ as counter-examples for C representing subset-maximal {a mathematical formula}X&gt;t-admissible sets. During the traversal of the tree decomposition, the colorings and certificates are computed analogously to the colorings for admissible semantics. At the root node r, one checks for each pair {a mathematical formula}(C,Γ) whether {a mathematical formula}Γ=∅. If this is the case, C represents subset-maximal {a mathematical formula}X&gt;r-admissible sets, which correspond to preferred extensions.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      System comparison
     </section-title>
     <paragraph>
      In this section we provide an overview on systems that implement the approaches presented earlier. We focus here on a comparison of the systems w.r.t. their features (e.g. supported semantics and reasoning problems) and underlying concepts. Our goal is to provide a comprehensive study of the strengths of each tool, where the reader can look up the appropriate tool for the problem at hand. The features of the presented systems are naturally subject to change in the future. We note that the landscape of currently available software is very heterogeneous: Some tools are tailored to graphical representations of the used algorithms and results whereas others are particularly tuned towards performance. Within the argumentation community there is currently no consensus on which instances are representative for comparing different implementations w.r.t. performance. Moreover, independent benchmark suites are not available. Hence, a systematic, fair and longer-term stable comparison w.r.t. run-time performance is currently not possible, and we refer to currently ongoing developments within the community that seek for a standardized system competition of argumentation systems [48], [123], [43]. Nevertheless, where available, we give references to articles that deal with a performance comparison of particular tools.
     </paragraph>
     <paragraph>
      Table 2 summarizes systems for abstract argumentation. The URL links to the web page of the respective system, where source code and documentation or the web front-end (if available) can be found. Additionally, the table contains a reference to the section where the algorithms underlying the tool are discussed. The last column contains the reference to the main article of the tool. In case no particular article on the tool was published, we reference here the paper that presents the theoretical background of the tool.
     </paragraph>
     <paragraph>
      Table 3 lists the technical characteristics of the considered systems. The “GUI” column not only indicates the availability of a full-fledged graphical user interface but also contains information about availability of front-ends for demonstration purposes. Column “command line” denotes that the software is accessible via command line interface, and “library” specifies that the implementation can be accessed via a specified software interface.
     </paragraph>
     <paragraph>
      In Table 4 we provide an overview on the supported semantics and reasoning problems of the systems. Note that this table only contains the semantics and reasoning problems we consider throughout this work (see Section 2). Additionally, we also include implicit reasoning support in the table, denoted by the italic letters C and S. That is, we know that credulous reasoning yields the same answer for any AF and argument w.r.t. preferred, complete and admissible semantics. Similarly, skeptical reasoning for complete and grounded semantics return the same result. Since the grounded extension is unique, credulous and skeptical reasoning are equivalent for grounded semantics.
     </paragraph>
     <paragraph>
      The strengths of each tool are summarized in Section 5.1. There, we go into detail of system-specific characteristics, such as particular GUI-based features, support for additional reasoning problems or performance-relevant details. If a system is capable of computing further semantics, such as ideal [124], eager [125], cf2 [126], stage2 [127], resolution-based grounded [128] we note this in the corresponding system paragraph.
     </paragraph>
     <section label="5.1">
      <section-title>
       System properties
      </section-title>
      <section>
       <section>
        <section-title>
         ArgSemSAT
        </section-title>
        <paragraph>
         The high-performance system ArgSemSAT is built on top of modern SAT solvers in such that it incorporates an iterative SAT-procedure. In particular, it implements the PrefSat approach [82] from Section 3.1.3. The procedure relies on iteratively generating complete extensions/labelings and extending them iteratively to preferred extensions. A similar approach is taken by CEGARTIX, where skeptical acceptance of preferred semantics (among other query-based reasoning problems) is computed. The implementation of PrefSat showed good performance compared to ASPARTIX (even with its metasp approach) and ArgTools [82]. ArgSemSAT allows to choose between different SAT-solvers and processes input in the ASPARTIX input format. In future it is also supposed to include direct algorithms based on the SCC-recursive schema [22], [129].
        </paragraph>
       </section>
       <section>
        <section-title>
         ArgTools
        </section-title>
        <paragraph>
         This system aims to provide a fast implementation of a labeling-based algorithm for enumerating all preferred extensions (cf. Algorithm 4). While the main focus of the research behind this tool is directed towards efficient enumeration of preferred semantics [36] there are several other results. First, enumeration algorithms for several other semantics, i.e. those depicted in Table 4 and ideal, where developed in [105]. Second, in [36] the authors present an implementation of optimizations for credulous and skeptical reasoning with preferred semantics. This line of research compares the performance of different labeling based algorithms and in particular gives empirical evidence, by comparing the algorithms on randomly generated instances, that the newly proposed algorithms are the fastest ones. Some of the algorithms are also compared with ASPARTIX (using the DLV solver) and dynPARTIX where ArgTools again showed good performance.
        </paragraph>
       </section>
       <section>
        <section-title>
         ASPARTIX
        </section-title>
        <paragraph>
         The “Answer Set Programming Argumentation Reasoning Tool” [30] is based on reductions to ASP as discussed in Section 3.3. It consists of a collection of ASP encodings, where each encoding, augmented by a given AF in form of ASP facts, can be given as input to an ASP solver in order to compute the extensions. For most semantics, ASPARTIX provides encodings for the solver DLV as well as gringo/clasp(D). Following the reduction approach, ASPARTIX's performance scales with new versions of these solvers. Furthermore, the system is platform independent in the sense that it runs on any system supporting the ASP solvers. ASPARTIX also offers a web front-end, where any argumentation framework as well as its extensions can be inspected graphically. A particularly useful feature of this system is that it supports many semantics and solves various reasoning problems. In addition to the semantics in Table 4, ASPARTIX supports ideal, cf2, stage2 and resolution-based grounded semantics. Since ASP solvers support enumeration and credulous as well as skeptical query-based reasoning, this can directly be utilized by ASPARTIX. The system is often used as a reference system in performance comparisons [21], [82], [31], [36], [37], [83], [98], [105], [130], [45], [44], [131].
        </paragraph>
       </section>
       <section>
        <section-title>
         CEGARTIX
        </section-title>
        <paragraph>
         The “Counter-Example Guided Argumentation Reasoning Tool” [21] is built on top of modern SAT solvers, and relies on an iterative procedure of SAT-calls (see Algorithm 1). As a command-line tool, CEGARTIX is built towards performance and computes the skeptical acceptance of an argument w.r.t. preferred, semi-stable and stage semantics and for the last two also credulous acceptance. Like ArgSemSAT [82], which relies on iterative SAT calls for enumerating preferred labelings, CEGARTIX can be seen as a sort of hybrid approach between direct and reduction-based methods, since only certain sub-tasks are delegated to a SAT solver. CEGARTIX is available online as a binary. The system allows the user to configure which SAT-solver she wants to use. Being based on a reduction approach, CEGARTIX scales with newer versions of SAT solvers and the system has been shown to be competitive w.r.t. ASPARTIX [21] and also processes the ASPARTIX input format.
        </paragraph>
       </section>
       <section>
        <section-title>
         CompArg
        </section-title>
        <paragraph>
         CompArg [38] is intended for determining credulous acceptance of arguments w.r.t. preferred semantics and enumerating grounded, preferred, stable and semi-stable extensions. It implements the labeling-based approach as presented in Section 4.1 (Algorithm 4). Written in Delphi, the executable for Windows is publicly available. The system comes with many examples, which suits its main educational aim of illustration of the semantics. Due to this purpose it is not primarily built for high performance. The tool consists of a GUI that illustrates the computation of the acceptance status, either by providing proofs or refutations of arguments. Additionally, several example instances are provided. Therefore, CompArg is particularly useful when it comes to get a deeper understanding of the underlying algorithm. Besides deciding credulous acceptance, the resulting extensions can be enumerated.
        </paragraph>
       </section>
       <section>
        <section-title>
         ConArg
        </section-title>
        <paragraph>
         The system ConArg [26] follows a reduction-based approach towards CSPs as presented in Section 3.2. Internally, the tool uses sophisticated Java implementations of CSP engines (JaCoP). Its performance thus scales with newer versions of these engines, and it is platform-independent through the use of Java. It supports the enumeration of extensions for many semantics (see Table 4) and is capable of verifying whether a given set is a preferred extension. The tool features a simple and intuitive graphical user interface for inspecting the AF and the extensions at hand. It supports the ASPARTIX input format for AFs, and also allows to generate random (weighted) argumentation frameworks. ConArg is also available as a web-interface with an interactive graphical representation. Recently, the second version of ConArg with some modifications was released [131], [43], [44]. To improve the performance, ConArg2 is now based on Gecode, an efficient C++ environment for constraint-based applications. ConArg2 is available as a pre-compiled command line tool for Linux. Besides the features of ConArg, ConArg2 also allows for credulous and skeptical reasoning for admissible, stable and complete semantics. ConArg and ConArg2 showed good performance compared to ASPARTIX and Dung-O-Matic [130], [131].
        </paragraph>
       </section>
       <section>
        <section-title>
         Dung-O-Matic
        </section-title>
        <paragraph>
         Dung-O-Matic is based on dialectical proof-procedures (see Section 4.2) and includes implementations for many different semantics. Besides support for most of the semantics listed in Table 4, ideal and eager extensions for a given AF can be computed. Implemented as a Java library, it can be flexibly used across platforms. For demonstration purposes, it is accessible via the tool OVAgen.{sup:15} OVAgen is a web-based software where argumentation frameworks can be drawn graphically and the resulting extensions are visualized. A preliminary performance comparison against ASPARTIX and ConArg is published by Bistarelli et al. [130]. Although this work shows that the tool is outperformed by the other two systems when computing complete or stable extensions, one has to note that further comparisons and, in particular, real-world instances are necessary to gain a better picture of the tool's performance.
        </paragraph>
       </section>
       <section>
        <section-title>
         Dungine (part of ArgKit)
        </section-title>
        <paragraph>
         Dungine [109] implements algorithms based on dialogue games, and currently provides native support for grounded and preferred semantics. It is part of ArgKit, a Java library intended for building custom software based on argumentation. For demonstration purposes, the ArgKit package includes examples of GUI applications. Additionally, similar to Dung-O-Matic, the software is integrated in the tool OVAgen. Since the source code is made publicly available under the LGPL license, it can be integrated in other projects.
        </paragraph>
       </section>
       <section>
        <section-title>
         dynPARTIX
        </section-title>
        <paragraph>
         The concept underlying the “Dynamic Programming Argumentation Reasoning Tool” [42], [115] is based on dynamic programming, where the instance is decomposed before solving (see Section 4.3). The tool exploits the structure of the given argumentation framework, where the decomposition is constructed based on heuristics. Hence, its run-time performance is particularly good for instances with tree-like structures. The tool, implemented in C++, is currently available as Linux executable. A special characteristic that differentiates it from the other systems presented here is its ability to provide the overall number of solutions without explicit enumeration.
        </paragraph>
       </section>
       <section>
        <section-title>
         PyAAL (+ArguLab)
        </section-title>
        <paragraph>
         The “Python Abstract Argumentation Library” implements labeling-based procedures for determining the justification status of arguments and for enumerating the labelings for many semantics (see Section 4.1). In addition to the functionality summarized in Table 4, PyAAL is able to compute the ideal and eager labeling, as well as determining the corresponding justification status. ArguLab [107] is a web front-end that allows to demonstrate the capabilities of PyAAL. Within ArguLab, in a first step the argumentation framework is constructed. Next, based on the selected semantics the labelings associated with the arguments are visualized. The tool allows to interactively analyze the justification status of arguments. Note that ArguLab is designed for demonstration purposes only, but the underlying code of PyAAL can be used without restrictions (GPL licensed). Its particular strength lies in the fact that it supports a broad number of semantics and solves several reasoning problems.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Summary
      </section-title>
      <paragraph>
       The system comparison illustrates the diverse landscape of available tools for abstract argumentation: While some systems cover a wide range of different semantics (e.g., ASPARTIX, ConArg, Dung-O-Matic, and PyAAL), others are well-suited for illustration and demonstration purposes of the algorithms (e.g., CompArg and Dungine) or are tailored towards solving particular problems efficiently (e.g., ArgSemSAT, ArgTools, CEGARTIX and dynPARTIX). Also, diversity is observable when considering the supported semantics and solvable reasoning problems (see Table 4). Among the considered systems, no semantics and reasoning problem is supported by all tools. Additionally, to promote their functionality, several tools provide access to their systems via a web interface (e.g., ASPARTIX, ConArg, Dung-O-Matic, Dungine and PyAAL), which allows to test the system without the necessity to download or install software.
      </paragraph>
      <paragraph>
       The available run-time comparisons do not indicate that one system outperforms all others. However, we observed that ASPARTIX is, in most cases, used as a base line system for performance comparisons. To give a clearer picture on the performance aspects of the tools, there is a need for independently created and publicly available benchmark suites. This (and also ideas on running even a public system competition for argumentation systems) is discussed within the community (see, e.g., [132]).
      </paragraph>
      <paragraph>
       Additionally, besides run-time performance, many other aspects are important for a good system, including intuitive design, versatility, extendability, and also source code availability or ongoing support and development of the system. Each tool has its unique characteristics and advantages, therefore the choice for the right tool mainly depends on the problem at hand.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      We conclude our survey on implementation of abstract argumentation with various issues we have not touched yet. This includes methods for further semantics (Section 6.1) and complementary aspects for evaluating abstract argumentation frameworks, for instance, pre-processing (Section 6.2). In Section 6.3, we give pointers to systems which are in a certain way concerned with abstract argumentation, but have a more general aim (in fact, methods as presented in this survey could be used within such systems). We then proceed with a global summary and discuss directions which we believe are important for future developments.
     </paragraph>
     <section label="6.1">
      <section-title>
       Further semantics
      </section-title>
      <paragraph>
       In the interest of space, we have omitted a few prominent semantics in the main body of this survey. In what follows we give respective pointers to the literature and highlight systems implementing these semantics.
      </paragraph>
      <paragraph>
       As shown by Baroni et al. [126] argumentation semantics can be defined on the basis of decomposing an AF into its strongly connected components (SCCs). This not only provides alternative definitions of some of the semantics which we have already discussed in the paper, but also leads to novel semantics, for instance cf2 [126] and stage2 [127] semantics. For both semantics, ASP encodings [127], [133] as well as labeling-based algorithms [127] have been presented, the former are integrated in the ASPARTIX system.
      </paragraph>
      <paragraph>
       Moreover, there is the family of resolution-based semantics [128], with the resolution-based grounded semantics being the most popular instance. Different ASP encodings for resolution-based grounded semantics are studied in [31] and are incorporated in the ASPARTIX system, as well.
      </paragraph>
      <paragraph>
       Finally, the unique-status semantics ideal [124] and eager [125] (for a general notion of parametric ideal semantics, see [134]) have been proposed to perform a prudent form of reasoning on the set of preferred extensions and semi-stable extensions, respectively. A characterization in terms of labelings for ideal and eager semantics is given in [135] and labeling-based algorithms have been implemented in the ArguLab system. Also the Dung-O-Matic system allows for reasoning with ideal and eager semantics. In the ASP-setting a characterization for ideal semantics is given in [30] and is implemented in the ASPARTIX system. Regarding other reduction-based systems, ConArg is also capable of computing the ideal extension of an AF.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Further methods
      </section-title>
      <paragraph>
       Next, we briefly describe three concepts which can be considered to be used on top of argumentation systems as discussed in this survey. These methods can be seen as pre-processing or simplification steps before actually evaluating abstract argumentation frameworks.
      </paragraph>
      <paragraph>
       First, the idea of splitting allows to divide an argumentation framework F in (two) smaller argumentation frameworks {a mathematical formula}F1, {a mathematical formula}F2, such that there are no attacks from arguments in {a mathematical formula}F2 to arguments in {a mathematical formula}F1[136], [137]. Then one can first compute the extensions of {a mathematical formula}F1 and then for each of its extension E compute the extensions for a slightly modified version {a mathematical formula}F2E of {a mathematical formula}F2. The extensions of F can then be obtained by combining each extension E of {a mathematical formula}F1 with the extensions of the frameworks {a mathematical formula}F2E. The benefit from this splitting approach comes from the fact that both {a mathematical formula}F1 and {a mathematical formula}F2 are smaller than the original AF F and thus can be evaluated faster (however, in the worst case an exponential number of AFs {a mathematical formula}F2E has to be handled). The idea of splitting AFs has also been generalized by allowing a small number of attacks from arguments in {a mathematical formula}F2 to arguments in {a mathematical formula}F1, see [138]. In a recent paper, Liao and Huang have proposed a related method to evaluate only parts of a given framework when it comes to credulous or skeptical reasoning problems [139].
      </paragraph>
      <paragraph>
       Second, the identification of redundant patterns might be used to simplify argumentation frameworks before evaluation. The notion of strong equivalence [73], [140] provides means to identify redundant attacks without analyzing the entire framework (an example are attacks between two self-attacking arguments; such attacks can be safely removed for most of the semantics). Relaxed notions of strong equivalence might be even more beneficial for this purpose, see, e.g., [141], [142].
      </paragraph>
      <paragraph>
       Finally, we mention the concept of intertranslatability between abstract argumentation semantics [72]. Here, one is interested in translations from a semantics σ to another semantics τ, i.e., a function Tr that transforms arbitrary argumentation frameworks F such that {a mathematical formula}σ(F)=τ(Tr(F)). If this translation function Tr can be computed efficiently we can combine it with any system for semantics τ to build a system for σ. So translations between different semantics allow to expand the applicability of existing argumentation systems.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Further systems
      </section-title>
      <paragraph>
       In this work we focused on systems that implement the evaluation of semantics on Dung's abstract argumentation framework directly. However, there exists a wide range of systems that extend these capabilities, in particular by additionally supporting instantiation of argumentation frameworks.
      </paragraph>
      <paragraph>
       One approach is based on ASPIC [143], resp. {a mathematical formula}ASPIC+[50], which instantiates Dung-style frameworks. Arguments are represented as inference trees by applying strict and defeasible inference rules. TOAST (The Online Argument Structures Tool) [144] is an implementation of {a mathematical formula}ASPIC+ and is available as web front-end.{sup:16} The user-specified knowledge base, rule set, contrariness and preferences are used to construct an argumentation system which can currently be evaluated based on grounded, preferred, semi-stable and stable semantics. The ASPIC argumentation engine demo{sup:17} implements several instantiations of ASPIC and provides a web interface. Again the user can specify a knowledge base and a rule set to construct an argumentation system which then can be evaluated based on grounded and credulous preferred semantics. The Carneades Web Service{sup:18} is capable of “argument construction, storage, navigation, querying, evaluation, visualization and interchange” [145]. It is based on the {a mathematical formula}ASPIC+ model of structured argument but still preserves the features of the original version of Carneades system [51]. On the resulting Dung-style framework it applies grounded semantics. An approach based on classical logic and argument instantiation is shown in [146]. Here, arguments and possible counterarguments are constructed from a classical propositional knowledge base. Furthermore, Vispartix{sup:19} consists of a collection of ASP encodings [147] for obtaining Dung argumentation frameworks from a propositional knowledge base (and a set of predefined claims), based on the approach presented in [148]. The argumentation framework can then, for example, be evaluated by ASPARTIX. Another survey [54] summarizes systems that focus on the construction of arguments. This includes approaches based on classical [148] and defeasible logic [53] and briefly introduces the systems ASPIC and CaSAPI{sup:20} (which combines abstract and assumption-based argumentation).
      </paragraph>
      <paragraph>
       There is also recent work on translating different argumentation models. In [149], a translation between Carneades and Dung AFs is studied and implemented in the functional programming language Haskell. The benefit of such systems is that one may re-use engines for AFs to compute results for Carneades and potentially other argumentation models. Regarding different argumentation models, a reduction-based approach was implemented for recursive, probabilistic defeasible logic programming (RP-DeLP). The resulting system uses ASP for computing the results [150].
      </paragraph>
      <paragraph>
       Finally, a recent review on systems for argumentation in the Social Semantic Web [151] summarizes social web tools, and discusses how argumentation can be modeled in this context. It contains an exhaustive study of online tools that combine Web 2.0 and Semantic Web technologies. In the course of the review, it gives an comparative overview on current developments of practically applied argumentation research on the web.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Future directions
      </section-title>
      <paragraph>
       Although significant progress has been made in the last years in implementing efficient systems for abstract argumentation, there is still a wide range of open issues.
      </paragraph>
      <paragraph>
       On the one hand, several optimization methods which proved successful in other areas still have to be adapted for abstract argumentation systems. Methods including symmetry breaking, parallelization, heuristics and algorithm selection come to our mind. Likewise, the area of average-case and probabilistic algorithms has not been considered in combination with abstract argumentation yet. Even more important, benchmark suites are needed to evaluate and witness the value of such optimizations and, more generally, to compare the different approaches which are nowadays available on a broad and objective scope. To date, experiments are typically performed on some randomly generated frameworks. However, a better theoretical model for such frameworks is required in order to have a more meaningful picture when runtimes are measured. On the other hand, collections of structured instances stemming from real-world applications domains are lacking. Several ideas for establishing a benchmark library for abstract argumentation have first been collected in [152] and the upcoming first competition for argumentation systems, http://argumentationcompetition.org, will be very beneficial for the evolution of systems.
      </paragraph>
      <paragraph>
       Moreover, we have to understand particularities in the argumentation domain to tune the systems towards more practical needs, in particular when used within an instantiation-based argumentation context. First, argumentation is inherently dynamic [153], [154], [155] and thus one expects that argumentation frameworks are continuously evolving. Consequently, methods which allow for incremental evaluation of frameworks (i.e., the system “remembers” the framework it has evaluated last time and tries to build the current solving on this prior results) are an important research direction. A first valuable theoretical contribution in this direction can be found in [156]. Second, many people in the community argue that abstract argumentation is not a stand-alone formalism. Consequently, the integration of “abstract” into “real” argumentation systems is central. In particular, the specific needs of these real argumentation systems have to be taken into account when abstract argumentation systems are improved. To this end, it has to be clarified whether such integrated systems lead to abstract frameworks of certain structure (in particular, in many cases, instantiations lead to particular symmetries in the resulting frameworks). Advanced abstract argumentation systems therefore should either be optimized towards such structures or provide interfaces which allow to feed additional information from the instantiation process to the system in order to guide heuristics or to prune the search space.
      </paragraph>
      <paragraph>
       In conclusion, we believe that the challenge of implementing abstract argumentation systems is a perfect play-ground to apply and test different techniques on a set of uniform yet computationally manifold problems which are given by the different semantics for abstract argumentation. The future will show which techniques prove successful or whether completely novel methods will emerge in course of these investigations.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>