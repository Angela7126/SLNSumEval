<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    On rejected arguments and implicit conflicts: The hidden power of argumentation semantics.
   </title>
   <abstract>
    Abstract argumentation frameworks (afs) are one of the most studied formalisms in AI and are formally simple tools to model arguments and their conflicts. The evaluation of an af yields extensions (with respect to a semantics) representing alternative acceptable sets of arguments. For many of the available semantics two effects can be observed: there exist arguments in the given af that do not appear in any extension (rejected arguments); there exist pairs of arguments that do not occur jointly in any extension, albeit there is no explicit conflict between them in the given af (implicit conflicts). In this paper, we investigate the question whether these situations are only a side-effect of particular afs, or whether rejected arguments and implicit conflicts contribute to the expressiveness of the actual semantics. We do so by introducing two subclasses of afs, namely compact and analytic frameworks. The former class contains afs that do not contain rejected arguments with respect to a semantics at hand; afs from the latter class are free of implicit conflicts for a given semantics. Frameworks that are contained in both classes would be natural candidates towards normal forms for afs since they minimize the number of arguments on the one hand, and on the other hand maximize the information on conflicts, a fact that might help argumentation systems to evaluate afs more efficiently. Our main results show that under stable, preferred, semi-stable, and stage semantics neither of the classes is able to capture the full expressive power of these semantics; we thus also refute a recent conjecture by Baumann et al. on implicit conflicts. Moreover, we give a detailed complexity analysis for the problem of deciding whether an af is compact, resp. analytic. Finally, we also study the signature of these subclasses for the mentioned semantics and shed light on the question under which circumstances an arbitrary framework can be transformed into an equivalent compact, resp. analytic, af.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In recent years argumentation has emerged to become one of the major fields of research in Artificial Intelligence [34], [11]. In particular, Dung's well-studied abstract argumentation frameworks (afs) [18] are a simple, yet powerful formalism for modeling and deciding argumentation problems that are integral to many advanced argumentation systems, see e.g. [12]. The evaluation of afs in terms of finding reasonable positions with respect to a given framework is defined via so-called argumentation semantics (cf. [4] for an overview). Given an afF, an argumentation semantics σ returns acceptable sets of arguments {a mathematical formula}σ(F), the (σ-)extensions of F. Several semantics have been introduced over the years [18], [39], [13], [5] with motivations ranging from the desired treatment of specific examples to fulfilling certain abstract principles. One important line of research in abstract argumentation is thus the systematic comparison of the different semantics available. Hereby, the behavior of extensions with respect to certain properties [1] has been analyzed and the expressive power of semantics [23], [25], [28], [36] has been studied by identifying the set of extension-sets achievable under certain semantics. On the other hand, subclasses of afs  such as acyclic, symmetric, odd-cycle-free or bipartite afs, have been considered, since for some of these classes different semantics collapse [14], [19]. Beside these subclasses based on the graph structure there are also classes defined via properties of extensions. The probably most prominent such subclass is the class of coherent afs [21], i.e. afs where the stable and preferred semantics coincide. Further examples for subclasses that are defined via extensions can be found in [3], [27].
     </paragraph>
     <paragraph>
      In this work we contribute to both streams of research. We introduce two new classes, which to the best of our knowledge have not received attention in the literature. The actual definition of these two classes is motivated by typical phenomena that can be observed for several semantics. First, there exist arguments in a given af that do not appear in any extension. Since these so-called rejected arguments do not appear in the result of extension-based semantics, it is a natural question whether such arguments can be “removed” from the af at hand without changing its outcome (in a certain way, this question is similar to the problem of simplifying propositional formulas by removing “don't care” atoms). In order to have a handle for analyzing the effect of rejected arguments, we introduce the class of compactafs: an af is compact (with respect to a semantics σ), if each of its arguments appears in at least one σ-extension. Second, we are interested in the concept of implicit conflicts. An attack between two arguments represents an explicit conflict. By the nature of most argumentation semantics, conflicts can however also be implicit in the sense that some arguments do not occur together in any extension, although there is no attack between them. In order to understand the expressive power of implicit conflicts we introduce the class of analytic frameworks. Given a semantics σ, if every conflict between two arguments {a mathematical formula}a,b in an afF is explicit (i.e., for all arguments {a mathematical formula}a,b, if {a mathematical formula}{a,b}∩E≠{a,b} for all σ-extensions E, then a attacks b in F or b attacks a in F) then F is called analytic. Both compact and analytic afs thus yield a “semantic” subclass since their definitions rely on the actual extensions obtained via the chosen semantics.
     </paragraph>
     <paragraph>
      The role of rejected arguments. Although rejected arguments are natural ingredients in typical argumentation scenarios, it is of interest to understand in which ways rejected arguments contribute to the “strength” of a particular semantics. Let us first have a brief look on the naive semantics, which is defined as subset-maximal conflict-free sets: Here, it is rather easy to see that any af can be transformed into an equivalent compact af by just removing all self-attacking arguments. In other words, the same outcome (in terms of the naive extensions) can be achieved by a simplified af without rejected arguments. On the one hand, this can be seen as a general weakness of naive semantics, since any possible outcome can be equivalently achieved in the absence of rejected arguments. On the other hand, this shows that towards evaluating an af under naive semantics, the transformation into a compact af can provide a beneficial pre-processing step for computing the extensions (which afterwards should however be interpreted in terms of the original af).
     </paragraph>
     <paragraph>
      How is the situation with semantics that are considered more mature? We borrow an example from Dunne et al. [22]. Consider the af{a mathematical formula}F1 in Fig. 1, where nodes represent arguments and directed edges represent attacks.
     </paragraph>
     <paragraph>
      The stable extensions (conflict-free sets attacking all other arguments) of {a mathematical formula}F1 are given by the set {a mathematical formula}S={{a,b,c}, {a mathematical formula}{a,b′,c′}, {a mathematical formula}{a′,b,c′}, {a mathematical formula}{a′,b′,c}, {a mathematical formula}{a,b,c′}, {a mathematical formula}{a′,b,c}, {a mathematical formula}{a,b′,c}}. Observe that x is rejected, i.e. x does not appear in any stable extension of {a mathematical formula}F1. Hence, this framework is not compact for the stable semantics. Moreover, it was shown in [22] that there is no compact af (in this case an af not using argument x) that yields the same stable extensions as {a mathematical formula}F1. By the necessity of conflict-freeness any such compact af would only allow conflicts between arguments a and {a mathematical formula}a′, b and {a mathematical formula}b′, and c and {a mathematical formula}c′, respectively. Moreover, there would have to be attacks in both directions for each of these conflicts in order to ensure stability. Hence any compact af having the same stable extensions as {a mathematical formula}F1 necessarily yields {a mathematical formula}{a′,b′,c′} in addition. In other words, under the stable semantics particular outcomes (in the example the set {a mathematical formula}S of extensions) can only be achieved via afs containing at least one rejected argument. Thus, the stable semantics makes proper use of rejected arguments. As we will see, all semantics under consideration (except naive semantics) show a similar behavior.
     </paragraph>
     <paragraph>
      The role of implicit conflicts. As introduced earlier, implicit conflicts arise when two arguments are never jointly accepted although they do not attack each other. The af{a mathematical formula}F2 in Fig. 2 provides a simple example for this effect.
     </paragraph>
     <paragraph>
      It can be seen that stable semantics yields two extensions {a mathematical formula}{a,d} and {a mathematical formula}{b,c} for {a mathematical formula}F2. Since c and d do not occur together in an extension there is an implicit conflict and thus {a mathematical formula}F2 is not analytic (for stable semantics). However, the naive extensions of {a mathematical formula}F2 are given by {a mathematical formula}{a,d}, {a mathematical formula}{b,c}, {a mathematical formula}{c,d}. Thus c and d are not in an implicit conflict here, and the af is easily seen to be analytic for naive semantics. Indeed, by definition of naive semantics, two arguments occur together in a naive extension if and only if there is no attack between them and they are not self-attacking. Thus not every af is analytic for naive semantics, but it is quite easy to see that every af can be turned into an equivalent analytic one over the same arguments, by just connecting the self-attacking arguments to any other argument. Coming back to our example and to stable semantics, the question remains whether {a mathematical formula}F2 can be turned into an equivalent analytic one? This is quite an easy exercise. Just add an attack from c to d, or likewise from d to c. In fact, this addition does not change the set of extensions. However, it has been left as open question in [10] (stated as “Explicit Conflict Conjecture”) whether such a manipulation of an af is always possible. In this work, we shall negatively answer this question showing that (i) for preferred and semi-stable semantics, there exist afs such that there is no equivalent analytic af; and (ii) for stable and stage semantics, there exist afs such that there is no equivalent analytic af, unless we are allowed to add rejected arguments.
     </paragraph>
     <paragraph>
      Expressiveness of compact and analytic argumentation frameworks. Before giving an overview of the obtained results, let us further illustrate some issues that come along with the subclasses of compact and analytic argumentation frameworks. One natural question is whether any afF can be transformed to an equivalent afG, i.e. {a mathematical formula}σ(F)=σ(G) for a given semantics σ, that is compact or analytic. In case the answer is no, we can conclude that the full range of expressiveness of σ indeed relies on the concepts of rejected arguments and implicit conflicts. Knowing which sets of extensions a semantics is able to express is of central interest in approaches of extension-based revision of afs [16]. As the result of the revision may also be subject to certain syntactic constraints (e.g. a fixed set of arguments [15]) it is important to know about the role of rejected arguments and implicit conflicts. For instance, a revised AF might be required (e.g. in order to fulfill revision postulates) to have exactly the extension-set {a mathematical formula}S from above under stable semantics while consisting solely of the arguments {a mathematical formula}{a,b,c,a′,b′,c′}. As we have already observed, and we will show in a more comprehensive and general manner in the paper, such a revision is not possible since getting {a mathematical formula}S under stable semantics would require an additional, rejected argument.
     </paragraph>
     <paragraph>
      Implications for argumentation systems. An even more promising application of our results lies in the field of concrete software systems for computing semantics of abstract argumentation frameworks. A considerable number of such systems (“solvers”) exist, as has been witnessed by the First International Competition on Computational Models of Argument (ICCMA 2015) [38].{sup:1} Using instances from that competition and additional instances created according to the same graph model as the competition instances, we also performed an experimental evaluation on the theoretical phenomena we study in this paper. The results can be found in Appendix A, and demonstrate the clear computational benefit of knowing about implicit conflicts in an argumentation framework. More precisely, once all implicit conflicts of an af are made explicit, then the competition winners are able to compute the af's extensions (for stable and preferred semantics) much faster than before (without implicit conflicts made explicit). Thus it is a naturally arising research question whether information about implicit conflicts can be obtained “cheaply” in terms of computational cost, a question that we will also address in the paper. For knowing about rejected arguments, the computational gain is immediately clear, since the lower the number of arguments, the smaller is the search space a solver has to go through in order to find all extensions. Thus, preprocessing steps that remove rejected arguments might also be beneficial to solving runtime. Moreover, if an af has no rejected arguments then all of its arguments are contained in at least one extension, and so credulous as well as skeptical reasoning become easy tasks [10].
     </paragraph>
     <paragraph>
      Overall, the research question we are interested in is: how computationally costly is it to determine whether an af can be simplified along the dimensions rejected arguments and implicit conflicts? Answering this question would be crucial towards the development of clever methods for preprocessing afs before solving. However, more fundamental questions need to be addressed first. On the one hand, we analyze how hard it is to decide whether an af is compact (resp. analytic); on the other hand, we ask whether any af can be transformed into an af that is compact (resp. analytic) and equivalent under a particular semantics. Intuitively speaking, our complexity results will show that deciding whether simplification is applicable (having certain reasoning tasks in mind) is as expensive as solving the reasoning tasks themselves. Furthermore, we can even show that there are afs that cannot be exhaustively simplified. (More formally, there are afs that have “pathological” implicit conflicts that cannot be made explicit even if we allow arbitrary semantics-preserving changes in other parts of the af.) This does not make our results less applicable to implementation of reasoning systems, however. These negative results help the solver development community to delineate what can and cannot be done in improving solver performance by intelligent preprocessing. That is, by our results, we know that computing all rejected arguments and implicit conflicts are not viable candidates for simplifying given argumentation frameworks.
     </paragraph>
     <paragraph>
      Main contributions &amp; structure of the paper. The main contributions of this article are organized as follows. Recall that the semantics we mainly investigate are stable, preferred, semi-stable, stage, and naive semantics.
     </paragraph>
     <list>
      <list-item label="•">
       In Section 3 we formally introduce the subclasses of compact and analytic afs with respect to the considered semantics and investigate their relationship. For both classes the picture is similar: for instance, if an af is compact (resp. analytic) for stable it also is for semi-stable (preferred, stage, and naive); but the other direction does not hold in general.
      </list-item>
      <list-item label="•">
       Section 4 answers the question how hard it is to decide whether an af is compact (resp. analytic). As it turns out, the complexity of this problem for a given semantics σ is the same as credulous acceptance under σ. Thus, we obtain tractability for naive semantics, {a mathematical formula}NP-completeness for stable and preferred semantics, and {a mathematical formula}Σ2P-completeness for semi-stable and stage semantics.
      </list-item>
      <list-item label="•">
       In Section 5 we refute the Explicit Conflict Conjecture [10] for σ being among stable, preferred, semi-stable and stage semantics. In fact, we provide afs such that there is no af equivalent under σ that contains solely explicit conflicts. On the other hand, we identify sufficient conditions guaranteeing equivalence-preserving translations to analytic afs.
      </list-item>
      <list-item label="•">
       The final collection of results in Section 6 is concerned with signatures for compact and analytic frameworks. Signatures as introduced in [23] plainly collect all possible sets of extensions afs can deliver under a given semantics. For instance, it is shown in [23] that preferred and semi-stable semantics yield an equal signature Σ, while the signature of stage semantics is a proper subset of Σ. Compared to [23], we do not give exact characterizations of signatures for compact (resp. analytic) frameworks, but obtain a full picture of their relationship with respect to the different semantics. For instance, we show that in terms of compact afs, the signatures for semi-stable and preferred semantics become incomparable, while for analytic afs, the signature for semi-stable semantics is a proper subset of the signature for preferred semantics. Finally, we generalize some recent results on maximal numbers of extensions [8] to give some impossibility results for compact realizability.
      </list-item>
     </list>
     <paragraph>
      In this work we consider several rather complex examples of argumentation frameworks, whose evaluation is a non-trivial task. Thus, for the reader's convenience, we provide encodings in the .apx format, which can be used to evaluate the afs with systems like ASPARTIX [29].{sup:2} These encodings can be downloaded from http://www.dbai.tuwien.ac.at/proj/adf/HiddenPowerAFs.zip.
     </paragraph>
     <paragraph>
      This article is based on [10] and [32], but also contains several new results.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In what follows, we briefly recall the necessary background on abstract argumentation and computational complexity. For an excellent overview on abstract argumentation and in particular on argumentation semantics, we refer to [4].
     </paragraph>
     <section label="2.1">
      <section-title>
       Abstract argumentation
      </section-title>
      <paragraph>
       Throughout the paper we assume a countably infinite domain {a mathematical formula}A of arguments. An argumentation framework (af) is a pair {a mathematical formula}F=(A,R) where {a mathematical formula}A⊆A is a finite set of arguments and {a mathematical formula}R⊆A×A is the attack relation. The collection of all afs is given as {a mathematical formula}AFA. For an af{a mathematical formula}F=(B,S) we use {a mathematical formula}AF and {a mathematical formula}RF to refer to B and S, respectively. We write {a mathematical formula}a↣Fb for {a mathematical formula}(a,b)∈RF and {a mathematical formula}S↣Fa (resp. {a mathematical formula}a↣FS) if there exists some {a mathematical formula}s∈S such that {a mathematical formula}s↣Fa (resp. {a mathematical formula}a↣Fs). Symmetric attacks {a mathematical formula}{(a,b),(b,a)}⊆RF are occasionally denoted by {a mathematical formula}〈a,b〉∈RF. For {a mathematical formula}S⊆A, the range of S (w.r.t. F), denoted {a mathematical formula}SF+, is the set {a mathematical formula}S∪{b|S↣Fb}. Moreover, {a mathematical formula}F|S denotes the af{a mathematical formula}(AF∩S,R∩(S×S)).
      </paragraph>
      <paragraph>
       Given an afF, an argument {a mathematical formula}a∈AF is defended (in F) by {a mathematical formula}S⊆AF if for each {a mathematical formula}b∈AF, such that {a mathematical formula}b↣Fa, also {a mathematical formula}S↣Fb. A set T of arguments is defended (in F) by S if each {a mathematical formula}a∈T is defended by S (in F). A set {a mathematical formula}S⊆AF is conflict-free (in F), if there are no arguments {a mathematical formula}a,b∈S, such that {a mathematical formula}(a,b)∈RF. We denote the set of all conflict-free sets in F as {a mathematical formula}cf(F). {a mathematical formula}S∈cf(F) is called admissible (in F) if S defends itself. We denote the set of admissible sets in F as {a mathematical formula}adm(F).
      </paragraph>
      <paragraph>
       The terms semantics and extension are often used almost synonymously. Formally a semantics is a mapping, while extensions are concrete elements of its image. The semantics we study in this work are those characterized by the naive, stable, preferred, stage, and semi-stable extensions. Given an afF they are defined as subsets of {a mathematical formula}cf(F) as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}S∈nai(F), if {a mathematical formula}∄T∈cf(F) with {a mathematical formula}T⊃S;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S∈stb(F), if {a mathematical formula}SF+=AF;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S∈prf(F), if {a mathematical formula}S∈adm(F) and {a mathematical formula}∄T∈adm(F) with {a mathematical formula}T⊃S;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S∈stg(F), if {a mathematical formula}∄T∈cf(F) with {a mathematical formula}TF+⊃SF+;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S∈sem(F), if {a mathematical formula}S∈adm(F) and {a mathematical formula}∄T∈adm(F) with {a mathematical formula}TF+⊃SF+.
       </list-item>
      </list>
      <paragraph>
       The following relations between these semantics are well-known to hold for any afF:{a mathematical formula}
      </paragraph>
      <paragraph>
       Furthermore, apart from stable semantics all considered semantics guarantee the existence of at least one (possibly empty) extension as long as finite afs are considered (cf. [7] for a detailed overview including the infinite case).
      </paragraph>
      <paragraph>
       We will also make frequent use of the following concepts.
      </paragraph>
      <paragraph label="Definition 1">
       Given {a mathematical formula}S⊆2A, {a mathematical formula}ArgsS denotes {a mathematical formula}⋃S∈SS and {a mathematical formula}PairsS denotes {a mathematical formula}{(a,b)|∃S∈S:{a,b}⊆S}. {a mathematical formula}S is called an extension-set (over {a mathematical formula}A) if {a mathematical formula}ArgsS is finite.
      </paragraph>
      <paragraph>
       In words, {a mathematical formula}ArgsS stands for all arguments occurring in some element of {a mathematical formula}S and {a mathematical formula}PairsS for all pairs of arguments occurring together in some element of {a mathematical formula}S. As is easily observed, for all semantics σ, {a mathematical formula}σ(F) is an extension-set for any afF.
      </paragraph>
      <paragraph label="Example 1">
       Consider the afF depicted in Fig. 3. We have that {a mathematical formula}a′, {a mathematical formula}b′ and {a mathematical formula}f′ are self-attacking, since all semantics considered build upon conflict-freeness these three arguments can thus not be included in any extension. Similarly we may accept only one argument from a and c as these two are mutually attacking each other; the same holds for b and d and also for c and d. Naive semantics generates maximal conflict-free sets, we thus get {a mathematical formula}nai(F)={{a,b,e},{a,d,e},{b,c,e}}.Argument e is contained in each naive extension as it does not share any attacks with not self-attacking arguments. However e is attacked by f and can not defend itself against this attack. Thus the set {a mathematical formula}{a,b,e} is not admissible. Preferred semantics, as maximal admissible sets, then computes to {a mathematical formula}prf(F)={{a,b},{a,d,e},{b,c,e}}.Now for stable extensions we need conflict-freeness as well as a partition of all arguments into accepted or attacked. Naturally this means that only maximal conflict-free sets are candidates. However neither of the naive sets has full range: {a mathematical formula}{a,b,e} does not attack f, {a mathematical formula}{a,d,e} does not attack {a mathematical formula}b′ and {a mathematical formula}{b,c,e} does not attack {a mathematical formula}a′. Thus there is no stable extension, i.e. {a mathematical formula}stb(F)=∅.Stage semantics can be seen as a less restrictive form of stable semantics in that we do not need to cover all arguments in range but want extensions to be conflict-free and range-maximal. As emphasized above all naive extensions have incomparable range (missing f, {a mathematical formula}b′, or resp. {a mathematical formula}a′) and thus {a mathematical formula}stg(F)=nai(F). Similarly semi-stable extensions are those admissible sets that are range-maximal. And in this case also the preferred extensions all have incomparable range (missing f and e, {a mathematical formula}b′, or resp. {a mathematical formula}a′) and thus {a mathematical formula}sem(F)=prf(F).Now as for the concepts introduced in Definition 1 we have Args which are all the arguments occurring in any extension; in this case for all semantics {a mathematical formula}σ∈{nai,stg,sem,prf} we get {a mathematical formula}Argsσ(F)={a,b,c,d,e}. And we have Pairs, all pairs of arguments that occur together in any extension; in this case as can easily be checked again for all semantics {a mathematical formula}σ∈{naive,stg,sem,prf} we get {a mathematical formula}Pairsσ(F)={(a,b), {a mathematical formula}(b,a), {a mathematical formula}(a,e), {a mathematical formula}(e,a), {a mathematical formula}(b,e), {a mathematical formula}(e,b), {a mathematical formula}(a,d), {a mathematical formula}(d,a), {a mathematical formula}(d,e), {a mathematical formula}(e,d), {a mathematical formula}(b,c), {a mathematical formula}(c,b), {a mathematical formula}(c,e), {a mathematical formula}(e,c), {a mathematical formula}(a,a), {a mathematical formula}(b,b), {a mathematical formula}(c,c), {a mathematical formula}(d,d), {a mathematical formula}(e,e)}.   ◊
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Computational complexity
      </section-title>
      <paragraph>
       We assume the reader is familiar with standard complexity concepts, such as {a mathematical formula}P, {a mathematical formula}NP and completeness. Nevertheless we briefly recapitulate the concept of {a mathematical formula}NP-oracle machines and the related complexity class {a mathematical formula}Σ2P. By an {a mathematical formula}NP-oracle machine we mean a Turing machine that can access an oracle that decides a given sub-problem from {a mathematical formula}NP (or {a mathematical formula}coNP) within one step. The class {a mathematical formula}Σ2P (sometimes also denoted by {a mathematical formula}NPNP), contains the problems that can be decided in polynomial time by a nondeterministic {a mathematical formula}NP-oracle machine.
      </paragraph>
      <paragraph>
       The known complexity results for the argumentation semantics under consideration are summarized in Table 1[13], [17], [19], [21], [26]. Here, {a mathematical formula}Verσ refers to the problem of verifying that a given set is an extension of a given arbitrary afF w.r.t. the semantics σ; {a mathematical formula}Credσ refers to the problem of verifying that a given argument x is credulously accepted w.r.t. σ in F (there is at least one σ-extension of F containing x); and {a mathematical formula}Skeptσ refers to the problem of verifying that a given argument x is skeptically accepted w.r.t. σ in F (x is contained in each σ-extension of F). For a more detailed discussion of the complexity results the interested reader is referred to [20], [24]. We only mention that the hardness results still hold if restricted to frameworks without self-attacking arguments, which we will make use of later on.
      </paragraph>
      <paragraph>
       Later, for semantics σ, we will also need upper bounds for the problem {a mathematical formula}Credσ2 defined as follows: given afF and arguments a and b, does there exist an extension {a mathematical formula}S∈σ(F) such that {a mathematical formula}{a,b}⊆S (see e.g. [19]). For the semantics under consideration, it is rather straightforward to see that membership for {a mathematical formula}Credσ carries over to {a mathematical formula}Credσ2. For {a mathematical formula}σ∈{prf,stb,sem,stg} this is witnessed by the standard {a mathematical formula}NP-algorithm of guessing a set S containing a and b and apply an oracle for verifying whether S is a σ-extension. The complexity of the verification problem then yields the desired upper bound. Membership in {a mathematical formula}P for the naive semantics can be decided by just checking whether a, b are neither self-attacking nor attacking each other. Indeed, in this case {a mathematical formula}{a,b} is conflict-free in the given afF, and thus there must exist a naive extension of F containing both a and b.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Subclasses of argumentation frameworks
     </section-title>
     <paragraph>
      In this section, we formally introduce the two central subclasses of argumentation frameworks of this paper, namely compact and analytic frameworks. We study basic properties and relations within the classes first. At the end of the section we will compare the two classes.
     </paragraph>
     <section label="3.1">
      <section-title>
       Compact argumentation frameworks
      </section-title>
      <paragraph>
       The main idea behind compact argumentation frameworks is the absence of rejected arguments (w.r.t. a given semantics).
      </paragraph>
      <paragraph label="Definition 2">
       Given a semantics σ, an afF is called compact for σ (or σ-compact) if {a mathematical formula}Argsσ(F)=AF. The set of all compact argumentation frameworks for σ is denoted by {a mathematical formula}CAFσ.
      </paragraph>
      <paragraph label="Example 2">
       Let us consider the afF depicted in Fig. 4.{sup:3} The preferred extensions of F are {a mathematical formula}prf(F)={{z}, {a mathematical formula}{x1,a1}, {a mathematical formula}{x2,a2}, {a mathematical formula}{x3,a3}, {a mathematical formula}{y1,b1}, {a mathematical formula}{y2,b2}, {a mathematical formula}{y3,b3}}, meaning that F is prf-compact ({a mathematical formula}F∈CAFprf) since each argument occurs in at least one preferred extension. On the other hand observe that {a mathematical formula}sem(F)=prf(F)∖{{z}} and {a mathematical formula}stg(F)={{xi,ai,bj},{yi,bi,aj}|1≤i,j≤3}, i.e. z is not contained in any semi-stable or stage extension. Therefore F is neither compact for semi-stable nor compact for stage semantics (i.e. {a mathematical formula}F∉CAFsem and {a mathematical formula}F∉CAFstg).   ◊
      </paragraph>
      <paragraph>
       As indicated by Example 2, the contents of {a mathematical formula}CAFσ differ with respect to the semantics σ. Concerning relations between the classes of compact afs we start with an easy observation. In the following result, the only requirement on a semantics σ is that extensions are subsets of the arguments in the framework, i.e. {a mathematical formula}Argsσ(F)⊆AF for any afF.
      </paragraph>
      <paragraph label="Lemma 1">
       For any two semantics σ and θ such that for eachafF, for every{a mathematical formula}S∈σ(F)there is some{a mathematical formula}S′∈θ(F)with{a mathematical formula}S⊆S′, we have{a mathematical formula}CAFσ⊆CAFθ.
      </paragraph>
      <paragraph label="Proof">
       Suppose {a mathematical formula}F∈CAFσ. By definition, {a mathematical formula}Argsσ(F)=AF. Now if for each {a mathematical formula}S∈σ(F) there is some {a mathematical formula}S′∈θ(F) with {a mathematical formula}S⊆S′, we have {a mathematical formula}Argsσ(F)⊆Argsθ(F). Since {a mathematical formula}Argsθ(F)⊆AF by definition, {a mathematical formula}Argsθ(F)=AF follows. Hence, {a mathematical formula}F∈CAFθ. □
      </paragraph>
      <paragraph>
       Note that the case where {a mathematical formula}σ(F)⊆θ(F) holds for each afF is a special case of the premise of Lemma 1. The next result provides a full picture of the relations between classes of compact afs for the semantics we consider (see also Fig. 5).
      </paragraph>
      <paragraph label="Theorem 2">
       The following relations hold:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}CAFstb⊂CAFσ⊂CAFnaifor{a mathematical formula}σ∈{prf,sem,stg};
       </list-item>
       <list-item label="2.">
        {a mathematical formula}CAFsem⊂CAFprf;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}CAFstg⊈CAFθand{a mathematical formula}CAFθ⊈CAFstgfor{a mathematical formula}θ∈{prf,sem}.
       </list-item>
      </list>
      <paragraph label="Proof">
       (1) Let {a mathematical formula}σ∈{prf,sem,stg}. The ⊆-relations are due to Lemma 1 together with following facts: (a) in any afF, {a mathematical formula}stb(F)⊆σ(F); (b) each σ-extension E of an afF is conflict-free in F, thus there exists a naive extension {a mathematical formula}E′ of F with {a mathematical formula}E⊆E′.{a mathematical formula}CAFσ⊂CAFnai: The af{a mathematical formula}({a,b},{(a,b)}) is compact for naive semantics but not for σ.{a mathematical formula}CAFstb⊂CAFσ: Consider afF from Fig. 6a. We have {a mathematical formula}prf(F)=sem(F)={{x1,a1}, {a mathematical formula}{x2,a2}, {a mathematical formula}{x3,a3}, {a mathematical formula}{y1,b1}, {a mathematical formula}{y2,b2}, {a mathematical formula}{y3,b3}}, and each of these extensions can be extended to a stage extension (the former three by adding one of the arguments {a mathematical formula}b1,b2,b3 the latter three by adding one of the arguments {a mathematical formula}a1,a2,a3), but {a mathematical formula}stb(F)=∅. Thus {a mathematical formula}AF=Argsσ(F)≠Argsstb(F)=∅, meaning that {a mathematical formula}F∈CAFσ but {a mathematical formula}F∉CAFstb.(2) {a mathematical formula}CAFsem⊆CAFprf is by the fact that, in any afF, {a mathematical formula}sem(F)⊆prf(F) (cf. Lemma 1). Properness is by the af in Fig. 4, which is (as discussed in Example 2) prf-compact but not sem-compact.(3) First we show {a mathematical formula}CAFstg⊈CAFθ for {a mathematical formula}θ∈{prf,sem}. To this end, consider the simple af{a mathematical formula}F′=({a,b,c},{(a,b),(b,c),(c,a)}). We have {a mathematical formula}stg(F′)={{a},{b},{c}}, thus {a mathematical formula}F′∈CAFstg. On the other hand, {a mathematical formula}sem(F′)=prf(F′)={∅}, thus {a mathematical formula}F′∉CAFσ.{a mathematical formula}CAFprf⊈CAFstg follows by the observations in Example 2.{a mathematical formula}CAFsem⊈CAFstg: Consider the af{a mathematical formula}F″ in Fig. 6b. One can check that this af is sem-compact, but not stg-compact. In fact, argument a does not occur in any stage extension. Although {a mathematical formula}{a,u1,x5}, {a mathematical formula}{a,u2,x6}, {a mathematical formula}{a,u3,x7}∈sem(F″), the range of any conflict-free set containing a is a proper subset of the range of every stage extension of {a mathematical formula}F″: {a mathematical formula}stg(F″)={{c,ui,x4}|i∈{1,2,3}}∪{{b,ui,sj,xi+4}|i,j∈{1,2,3}}∪{{ti,uj,si,xi}|i,j∈{1,2,3}}. Hence {a mathematical formula}CAFsem⊈CAFstg. □
      </paragraph>
      <paragraph>
       Finally note that every symmetric and irreflexive (i.e. no self-attacking arguments) af is contained in {a mathematical formula}CAFstb, as already observed in [14, Proposition 6], and therefore also in each {a mathematical formula}CAFσ for all semantics σ under consideration. But already {a mathematical formula}CAFstb contains strictly more afs than the class of symmetric and irreflexive afs, which is, for instance, indicated by the af ({a mathematical formula}{a,b,c,d}, {a mathematical formula}{(a,b),(b,c),(c,d),(d,a)}), which is clearly not symmetric but compact for the stable semantics. On the other hand observe that {a mathematical formula}CAFnai⊂AFA, as every af having self-attacking arguments is not contained in {a mathematical formula}CAFnai.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Analytic argumentation frameworks
      </section-title>
      <paragraph>
       In this section we deal with afs containing no implicit conflicts, which we will call analytic. We differentiate between the concept of an attack (as a syntactical element) and the concept of a conflict (with respect to the evaluation under a given semantics).
      </paragraph>
      <paragraph label="Definition 3">
       Given some af{a mathematical formula}F=(A,R), a semantics σ and arguments {a mathematical formula}a,b∈A. If {a mathematical formula}(a,b)∉Pairsσ(F), we say that a and b are in conflict in F for σ. If {a mathematical formula}(a,b)∈R or {a mathematical formula}(b,a)∈R we say that the conflict between a and b is explicit, otherwise the conflict is called implicit (with respect to σ).
      </paragraph>
      <paragraph>
       Notice that Definition 3 does not require a and b to be different arguments. In particular, an argument that is not contained in any σ-extension is in conflict with itself. This conflict is explicit if the argument is self-attacking and implicit otherwise.
      </paragraph>
      <paragraph label="Definition 4">
       Given a semantics σ, an afF is called analytic for σ (or σ-analytic) if all conflicts of F for σ are explicit in F. The set of all analytic argumentation frameworks for σ is denoted by {a mathematical formula}XAFσ.
      </paragraph>
      <paragraph label="Example 3">
       As a simple example consider the af{a mathematical formula}F2 from the introduction, depicted in Fig. 2. For {a mathematical formula}σ∈{stb,prf,sem,stg} we have {a mathematical formula}σ(F2)={{a,d},{b,c}}. Observe that there is an implicit conflict between arguments c and d, denoted by a dashed line in Fig. 2. Hence {a mathematical formula}F2 is not σ-analytic, i.e. {a mathematical formula}F2∉XAFσ. Observe however that {a mathematical formula}nai(F2)=σ(F2)∪{{c,d}}, which means that {a mathematical formula}F2 is analytic for naive semantics.   ◊
      </paragraph>
      <paragraph>
       As indicated in Example 3 the sets of analytic afs can differ for different semantics. Again, well-known relations between the extensions of certain semantics allow us to obtain ⊆-relations between classes of analytic afs.
      </paragraph>
      <paragraph label="Lemma 3">
       For any two semantics σ and θ such that for eachafF, for every{a mathematical formula}S∈σ(F)there is some{a mathematical formula}S′∈θ(F)with{a mathematical formula}S⊆S′, we have{a mathematical formula}XAFσ⊆XAFθ.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}F∈XAFσ and let there be a conflict between arguments {a mathematical formula}a,b∈AF for θ, i.e. {a mathematical formula}(a,b)∉Pairsθ(F). Now since for every {a mathematical formula}S∈σ(F) there is some {a mathematical formula}S′∈θ(F) with {a mathematical formula}S⊆S′ it follows that {a mathematical formula}Pairsσ(F)⊆Pairsθ(F). Hence also {a mathematical formula}(a,b)∉Pairsσ(F). By the assumption that {a mathematical formula}F∈XAFσ we know that there is an attack {a mathematical formula}a↣Fb or {a mathematical formula}b↣Fa, hence also {a mathematical formula}F∈XAFθ. □
      </paragraph>
      <paragraph>
       Similarly as for compact afs, observe that every symmetric and irreflexive (i.e. no self-attacking arguments) af is contained in {a mathematical formula}XAFσ for all semantics under consideration.
      </paragraph>
      <paragraph>
       The next result provides a full picture of the relations between classes of analytic afs for the semantics we consider (see also Fig. 7). We will frequently use Lemma 3, with either the exact condition or the special case {a mathematical formula}σ(F)⊆θ(F).
      </paragraph>
      <paragraph label="Theorem 4">
       The following relations hold:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}XAFstb⊂XAFσ⊂XAFnaifor{a mathematical formula}σ∈{prf,sem,stg};
       </list-item>
       <list-item label="2.">
        {a mathematical formula}XAFsem⊂XAFprf;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}XAFstg⊈XAFθand{a mathematical formula}XAFθ⊈XAFstgfor{a mathematical formula}θ∈{prf,sem}.
       </list-item>
      </list>
      <paragraph label="Proof">
       (1) Let {a mathematical formula}σ∈{prf,sem,stg}. The ⊆-relations are due to Lemma 3 together with following facts: (a) in any afF, {a mathematical formula}stb(F)⊆σ(F); (b) each σ-extension E of an afF is conflict-free in F, thus there exists a naive extension {a mathematical formula}E′ of F with {a mathematical formula}E⊆E′.{a mathematical formula}XAFσ⊂XAFnai: The af in Fig. 2 is, as discussed in Example 3, nai-analytic but not σ-analytic.{a mathematical formula}XAFstb⊂XAFσ: Consider the afF from Fig. 8. It contains several kinds of complete subframeworks, in the sense that each member of such a subframework attacks each other member. Two complete subframeworks of nine arguments ({a mathematical formula}{ri,ui,xi|1≤i≤3} and {a mathematical formula}{si,vi,yi|1≤i≤3}) and three complete subframeworks of six arguments ({a mathematical formula}{ri,si|1≤i≤3}, {a mathematical formula}{ui,vi|1≤i≤3} and {a mathematical formula}{xi,yi|1≤i≤3}). Further there are three directed three-cycles (among {a mathematical formula}{ai|1≤i≤3}, {a mathematical formula}{bi|1≤i≤3} and {a mathematical formula}{ci|1≤i≤3}), and each argument from the complete subframeworks attacks exactly two arguments from one three-cycle, effectively activating the third one. Now observe that we have {a mathematical formula}stb(F)=∅, as at least one argument of {a mathematical formula}ai,bi,ci remains out of range due to conflict-freeness, i.e. a conflict-free set in F can have only one argument from each complete nine-component and thus leaves at least one of the three-cycles unattacked. Therefore there is an implicit conflict for stb for every pair of non-attacking arguments, hence {a mathematical formula}F∉XAFstb. On the other hand we have {a mathematical formula}prf(F)=sem(F)={{ri,vj,ai,bj},{si,uj,ai,bj}, {a mathematical formula}{ri,yj,ai,cj},{si,xj,ai,cj}, {a mathematical formula}{ui,yj,bi,cj},{vi,xj,bi,cj}|1≤i,j≤3} and {a mathematical formula}stg(F)={{ri,vj,ai,bj,ck},{si,uj,ai,bj,ck}, {a mathematical formula}{ri,yj,ai,cj,bk},{si,xj,ai,cj,bk}, {a mathematical formula}{ui,yj,bi,cj,ak},{vi,xj,bi,cj,ak}|1≤i,j,k≤3}, which allows to verify that all conflicts for σ are explicit in F, hence {a mathematical formula}F∈XAFσ.(2) By Lemma 3 we get {a mathematical formula}XAFsem⊆XAFprf. In order to obtain properness of this relation consider the afF from Fig. 9 and define a cyclic successor function s as {a mathematical formula}s(1)=2,s(2)=3,s(3)=1, and {a mathematical formula}s(4)=5,s(5)=6,s(6)=4. We have {a mathematical formula}sem(F)={{xi,yj,zs(i),zs(j)}|i∈{1,2,3},j∈{4,5,6}ori∈{4,5,6},j∈{1,2,3}}, yielding plenty of implicit conflicts, e.g. between {a mathematical formula}xi and {a mathematical formula}yi. Hence F is not analytic for semi-stable semantics. We further define {a mathematical formula}s({i})=s(i) and for {a mathematical formula}s(i)=j also {a mathematical formula}s({i,j})=s(j). Now on the other hand we have {a mathematical formula}prf(F)=sem(F)∪{{xi,yj,zs({i,j})}|i,j∈{1,2,3}ori,j∈{4,5,6}}, witnessing {a mathematical formula}F∈XAFprf.(3) {a mathematical formula}XAFstg⊈XAFσ: Consider a directed cycle of five arguments F, {a mathematical formula}AF={x1,x2,x3,x4,x5} and {a mathematical formula}RF={(x1,x2),(x2,x3),(x3,x4),(x4,x5),(x5,x1)}. Here we have {a mathematical formula}stg(F)={{x1,x3},{x1,x4},{x2,x4},{x2,x5},{x3,x5}} and thus {a mathematical formula}F∈XAFstg. On the other hand {a mathematical formula}sem(F)=prf(F)={∅}, marking all pairs of arguments as being in conflict and thus for instance the conflict between {a mathematical formula}x1 and {a mathematical formula}x3 is implicit for prf and sem (and also stb).{a mathematical formula}XAFprf⊈XAFstg: The afF in Fig. 9 is, as argued in (2), explicit for prf, but not for sem. However, it holds that {a mathematical formula}stg(F)=sem(F), hence also {a mathematical formula}F∉XAFstg.{a mathematical formula}XAFsem⊈XAFstg: As witness of {a mathematical formula}XAFsem⊈XAFstg consider the afF from Fig. 10. This af is composed of two subframeworks, {a mathematical formula}FX from Fig. 8 and {a mathematical formula}FC from Fig. 6b, and a connecting interface consisting of argument {a mathematical formula}x¯ and its counterpart set {a mathematical formula}Y={s¯i,t¯i,u¯i|i∈{1,2,3}}. There are symmetric attacks between the members {a mathematical formula}α¯ of Y and their counterparts α from {a mathematical formula}FC, between {a mathematical formula}x¯ and all members of Y, and between {a mathematical formula}x¯ and all arguments from {a mathematical formula}FX.A key ingredient to this construction is that both, {a mathematical formula}FC and {a mathematical formula}FX, on their own do not provide stable extensions and thus at least one argument remains out of range for any stage or semi-stable extension. In addition observe that {a mathematical formula}FX is compact for both semi-stable and stage, while {a mathematical formula}FC is compact only for semi-stable, where a is the argument that does not occur in any {a mathematical formula}S∈stg(FC).Considering range-maximal (conflict-free or admissible) sets for F we first distinguish between sets S in relation to the argument {a mathematical formula}x¯. In case {a mathematical formula}x¯∈S we have that all arguments from {a mathematical formula}FX are in range, Y is attacked and thus {a mathematical formula}FC needs to be evaluated on its own. In case {a mathematical formula}x¯∉S, wlog. assume {a mathematical formula}Y⊆S and {a mathematical formula}a,x5∈S, we have that all of {a mathematical formula}FC and Y are in range, {a mathematical formula}x¯ is attacked and {a mathematical formula}FX needs to be evaluated on its own. This means that either some argument from {a mathematical formula}FC or some argument from {a mathematical formula}FX remains out of range of any semi-stable or stage extension in F and thus {a mathematical formula}stb(F)=∅. On a sidenote observe that for very similar reasons F is compact for both, semi-stable and stage semantics.Recall that {a mathematical formula}FC is compact for semi-stable, but not for stage (cf. Theorem 2). This immediately means that for stage semantics there is an implicit conflict between {a mathematical formula}x¯ and {a mathematical formula}FC (argument a to be precise). This also means that for semi-stable semantics there are no implicit conflicts between {a mathematical formula}x¯ and any argument from {a mathematical formula}FC.It remains to show that F indeed is analytic for semi-stable semantics. To this end we still need to investigate possible implicit conflicts between {a mathematical formula}FX and Y, between {a mathematical formula}FC and Y, as well as between {a mathematical formula}FX and {a mathematical formula}FC, and among arguments from {a mathematical formula}FC, as well as among arguments from Y.As mentioned before the range of any semi-stable extension will cover Y and {a mathematical formula}x¯ and either all of {a mathematical formula}FC or all of {a mathematical formula}FX. We start with extensions S with {a mathematical formula}Y⊆S and thus {a mathematical formula}x¯∉S and, wlog. fix the evaluation of {a mathematical formula}FX and consider some arbitrary {a mathematical formula}SX∈sem(FX). First observe that this immediately means that Y does not contain any conflicts and, due to {a mathematical formula}FX being compact, there are also no conflicts between Y and {a mathematical formula}FX. As {a mathematical formula}Y∪SX∪{c,xi}∈sem(F) for {a mathematical formula}i∈{1,2,3,4}, and for {a mathematical formula}i∈{5,6,7} also {a mathematical formula}Y∪SX∪{a,xi}∈sem(F) as well as {a mathematical formula}Y∪SX∪{b,c,xi}∈sem(F), there are no conflicts between Y and {a mathematical formula}a,b,c,x1…x7, between c and {a mathematical formula}b,x1…x7, or between {a mathematical formula}a,b and {a mathematical formula}x5,x6,x7.We now investigate extensions {a mathematical formula}S∈sem(F) that contain gradually less arguments from Y. In the following we will omit certain {a mathematical formula}xi from extensions, due to in {a mathematical formula}FC explicit conflicts, for instance {a mathematical formula}x2 as well as {a mathematical formula}x4 attack {a mathematical formula}s1 and {a mathematical formula}t1. For {a mathematical formula}(Y∖{s¯1}∪{s1})⊆S we can have {a mathematical formula}xi∈S for {a mathematical formula}i∈{1,3}, and for {a mathematical formula}i∈{5,6,7} on the other hand {a mathematical formula}xi,a∈S or {a mathematical formula}xi,b∈S. For {a mathematical formula}(Y∖{t¯1}∪{t1})⊆S we can have {a mathematical formula}xi,c∈S for {a mathematical formula}i∈{1,3}, or for {a mathematical formula}i∈{5,6,7} on the other hand {a mathematical formula}xi,a∈S. For {a mathematical formula}(Y∖{u¯1}∪{u1})⊆S we can have {a mathematical formula}xi,a∈S or {a mathematical formula}xi,b,c∈S for {a mathematical formula}i∈{5,7}, or for {a mathematical formula}i∈{1,2,3,4} on the other hand {a mathematical formula}xi,c∈S. Hence for symmetry reasons for {a mathematical formula}i∈{1,2,3} there are no implicit conflicts between arguments {a mathematical formula}si,ti,ui on the one side and on the other side Y and arguments {a mathematical formula}a,b,c,xj for {a mathematical formula}j∈{1,2…7}. Here we can already conclude that there are no implicit but only explicit conflicts between {a mathematical formula}FC and Y in F.For {a mathematical formula}i,j,k∈{1,2,3} fixed and {a mathematical formula}SY=Y∖{s¯i,t¯j,u¯k} we have that {a mathematical formula}SX∪SY∪{si,tj,uk,xi}∈sem(F). This means that there are no conflicts between {a mathematical formula}si, {a mathematical formula}tj and {a mathematical formula}uk, and subsequently that the subframework {a mathematical formula}FC does not have any implicit conflicts in F.Now finally, as elaborated on, each argument from {a mathematical formula}FC can appear in semi-stable extensions S of F that do not contain {a mathematical formula}x¯ and thus contain some arbitrary {a mathematical formula}FX-extension {a mathematical formula}SX. This means that there are no conflicts between {a mathematical formula}FC and {a mathematical formula}FX, which closes the gaps and shows that F indeed is analytic for semi-stable semantics. □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Relations between compact and analytic frameworks
      </section-title>
      <paragraph>
       In the previous two subsections we have separately investigated relations between semantics for compact and analytic afs respectively. It looks like the relations (Theorem 2, Theorem 4) are not only similar but indeed equal. The question why we looked at the different classes of afs separately and whether the equal subset relations are based on stronger similarities must be answered two-fold.
      </paragraph>
      <paragraph>
       On the one hand the examples used for the different proofs share exploitation of similar properties for each semantics considered, and for instance Fig. 10 actually builds upon fine-tuned relations between the properties of being compact or analytic. On the other hand in fact not a single example could be used in the other subsection. The compact afs are not analytic or the analytic afs are not compact. In what follows we draw some relations between the two classes. We start with similarities as observed in self-loop free afs.
      </paragraph>
      <paragraph label="Proposition 5">
       For any{a mathematical formula}F∈XAFσthat is self-loop free,{a mathematical formula}F∈CAFσ({a mathematical formula}σ∈{nai,{a mathematical formula}stb,prf,sem,stg}).
      </paragraph>
      <paragraph label="Proof">
       Observe that in Definition 3 we allow arguments in conflict to be equal. Hence for any semantics rejected arguments are in conflict with themselves, and rejected arguments in analytic afs need to be self-attacking. If there is no self-loop in some analytic af then naturally there is no rejected argument. □
      </paragraph>
      <paragraph>
       For naive semantics we can provide even stronger observations.
      </paragraph>
      <paragraph label="Proposition 6">
       For any self-loop freeafF we have{a mathematical formula}F∈CAFnaiand{a mathematical formula}F∈XAFnai.
      </paragraph>
      <paragraph label="Proof">
       Two self-loop free arguments where none is attacking the other form a conflict-free set. Since we are dealing with finite sets only this immediately means that there is a naive extension containing both arguments. □
      </paragraph>
      <paragraph label="Proposition 7">
       {a mathematical formula}CAFnai⊂XAFnai.
      </paragraph>
      <paragraph label="Proof">
       For an af{a mathematical formula}F∈CAFnai it holds that F is self-loop free, hence {a mathematical formula}F∈XAFnai by Proposition 6. Properness is by the af{a mathematical formula}({a},{(a,a)}), which is nai-analytic, but not nai-compact. □
      </paragraph>
      <paragraph>
       However observe that still not every af is analytic for naive semantics. To see this consider the af{a mathematical formula}({a,b},{(a,a)}). Here {a mathematical formula}{b} is the only naive extension, which means that a and b share an implicit conflict.
      </paragraph>
      <paragraph>
       Finally we conclude this subsection with an observation on the missing relations. That is, we provide reasons why except for naive semantics the properties of being compact or analytic are sufficiently distinct, despite their similarities.
      </paragraph>
      <paragraph label="Proposition 8">
       For{a mathematical formula}σ∈{stb,sem,prf,stg}, we have{a mathematical formula}CAFσ⊈XAFσand{a mathematical formula}XAFσ⊈CAFσ.
      </paragraph>
      <paragraph label="Proof">
       Consider the af from Fig. 2. We have as σ-extensions {a mathematical formula}{a,d} and {a mathematical formula}{b,c}. Hence the af is compact, but not analytic as the conflict between c and d is implicit only, resulting in {a mathematical formula}CAFσ⊈XAFσ.For {a mathematical formula}XAFσ⊈CAFσ consider the af{a mathematical formula}({a,b},{(a,b),(b,b)}). This af consists of one accepted and one rejected argument only. It is analytic but not compact. □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Complexity
     </section-title>
     <paragraph>
      When aiming for the simplification of an af along the dimensions of rejected arguments and implicit conflicts the very first questions one has to face is whether there are any rejected arguments or implicit conflicts, in other words whether the af is already compact, analytic resp., or there is potential for simplifications. That is, in the following we focus on the computational complexity of the following problems for the semantics σ under consideration: (1) decide whether a given af is σ-compact or not and (2) to decide whether a given af is σ-analytic or not. Note that the first problem can also be stated as a decision problem for fairness: given an af, does each argument appear in at least one σ-extension? Further complexity issues for these two classes are mentioned at the end of the section.
     </paragraph>
     <paragraph>
      As being compact means that each argument must be credulously accepted, this question is closely related to credulous reasoning (the decision problem {a mathematical formula}Credσ is defined by the question whether, given an afF and an argument a, a is contained in at least one σ-extension of F, i.e. whether {a mathematical formula}a∈Argsσ(F) holds). Exploiting this observation we first give a generic upper bound for the computational complexity.
     </paragraph>
     <paragraph label="Theorem 9">
      For any argumentation semantics σ, with{a mathematical formula}Credσ∈Cfor a complexity class{a mathematical formula}Cclosed under conjunction,{sup:4}we have that deciding whether anafis compact for σ is in{a mathematical formula}C.
     </paragraph>
     <paragraph label="Proof">
      By definition an af{a mathematical formula}F=(A,R) is σ-compact if each {a mathematical formula}a∈A is credulously accepted w.r.t. σ. Hence to check whether F is compact we simply evaluate {a mathematical formula}⋀a∈ACred(F,a), which is only of linear size and by assumption can be evaluated in {a mathematical formula}C as well. □
     </paragraph>
     <paragraph>
      We have a similar observation for analytic frameworks, when employing complexity results for {a mathematical formula}Credσ2.
     </paragraph>
     <paragraph label="Theorem 10">
      For any argumentation semantics σ, with{a mathematical formula}Credσ2∈Cfor a complexity class{a mathematical formula}Cclosed under conjunction, we have that deciding whether anafis analytic for σ is in{a mathematical formula}C.
     </paragraph>
     <paragraph label="Proof">
      By definition an af{a mathematical formula}F=(A,R) is σ-analytic if each pair {a mathematical formula}{a,b}∈A with neither {a mathematical formula}(a,b)∈R nor {a mathematical formula}(b,a)∈R is credulously accepted w.r.t. σ. Hence to check whether F is analytic for σ we simply conjoin all these tests (only polynomially many), each of which can be done in {a mathematical formula}C. □
     </paragraph>
     <paragraph>
      As {a mathematical formula}P, {a mathematical formula}NP and {a mathematical formula}Σ2P are closed under conjunctions we obtain upper bounds for all semantics under our considerations.
     </paragraph>
     <paragraph>
      In particular, we have the following results for naive semantics.
     </paragraph>
     <paragraph label="Corollary 11">
      The following problems are in{a mathematical formula}P:
     </paragraph>
     <list>
      <list-item label="1.">
       GivenafF, deciding whether{a mathematical formula}F∈CAFnai;
      </list-item>
      <list-item label="2.">
       GivenafF, deciding whether{a mathematical formula}F∈XAFnai.
      </list-item>
     </list>
     <paragraph>
      Towards our generic hardness result we introduce the concept of SCC-splittable{sup:5} semantics. Recall that we write {a mathematical formula}F|S as shorthand for {a mathematical formula}(AF∩S,RF∩(S×S)).
     </paragraph>
     <paragraph label="Definition 5">
      A semantics σ is called SCC-splittable if there exists a function {a mathematical formula}GFσ:F×2A→2A, with {a mathematical formula}F being the set of all afs over {a mathematical formula}A, such that the following holds for every af{a mathematical formula}F=(A,R)∈F.
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}GFσ(F,A)=σ(F)
      </list-item>
      <list-item label="•">
       If {a mathematical formula}A=B∪C and R does not contain attacks from C to B then{a mathematical formula} with {a mathematical formula}UEC={c∈C∖EF+|∀a∈B:(a,c)∈R→a∈EF+}.
      </list-item>
     </list>
     <paragraph>
      Observe that the second item implies that each strongly connected component of F is either included in B or C.
     </paragraph>
     <paragraph>
      Splitting argumentation frameworks was studied in [6] where (among others) splittings for stable and preferred semantics are presented. Although the splitting theorem in [6] is not stated in terms of Definition 5 it immediately gives a function {a mathematical formula}GFσ with the desired properties. We need one more definition.
     </paragraph>
     <paragraph label="Definition 6">
      A semantics σ is called rational, if for any afF that is a clique (i.e. F is of the form {a mathematical formula}(A,{(a,b)|a,b∈A,a≠b})) it holds that {a mathematical formula}σ(F)={{a}|a∈AF}.
     </paragraph>
     <paragraph label="Proposition 12">
      Stable and preferred semantics are rational and SCC-splittable.
     </paragraph>
     <paragraph>
      Next we give the generic hardness results for semantics that are rational and SCC-splittable.
     </paragraph>
     <paragraph label="Theorem 13">
      For any rational SCC-splittable argumentation semantics σ deciding whether anafis compact for σ is as hard as{a mathematical formula}Credσwhen restricted toafs without self-attacks.
     </paragraph>
     <paragraph label="Proof">
      We reduce the problem {a mathematical formula}Credσ to deciding whether an af is compact for σ. That is given an instance {a mathematical formula}F=(A,R),x∈A of {a mathematical formula}Credσ we build the following af{a mathematical formula}F′=(A∪A′,R∪R′) with {a mathematical formula}A′={ta|a∈A} and{a mathematical formula} That is, we add a clique af{a mathematical formula}CA=(A′,{(ta,tb)|a,b∈A,a≠b}) of size {a mathematical formula}|A| and link it to the original framework as follows: The argument {a mathematical formula}tx does not attack any of the original arguments. All the other arguments {a mathematical formula}ta attack all but one of the original arguments and thus, as we discuss below, enforces that this argument is credulously accepted. The construction is illustrated in Fig. 11.To prove the claim we have to show that x is credulously accepted in F iff {a mathematical formula}F′ is σ-compact. First observe that the new arguments in {a mathematical formula}F′ form a SCC and are not attacked by arguments from outside. As σ is SCC-splittable we can evaluate {a mathematical formula}F′ as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       Compute the extensions of the clique {a mathematical formula}CA.
      </list-item>
      <list-item label="2.">
       For each such extension E of {a mathematical formula}CA build the af{a mathematical formula}F|A∖EF′+ by removing all arguments in {a mathematical formula}EF′+ from F.
      </list-item>
      <list-item label="3.">
       For each extension {a mathematical formula}E′∈GFσ(F|A∖EF′+,UEA) return {a mathematical formula}E∪E′.
      </list-item>
     </list>
     <paragraph label="Theorem 14">
      For any rational SCC-splittable argumentation semantics σ deciding whether anafis analytic for σ is as hard as deciding whether anafis compact for σ. The result even holds if one knows that theafbeing tested for being analytic is already compact.
     </paragraph>
     <paragraph label="Proof">
      We reduce the problem of deciding whether an afF is compact to deciding whether F is analytic. That is given an instance {a mathematical formula}F=(A,R) (we can assume that F has no self-attacks as otherwise it is an immediate no-instance) we build the following af{a mathematical formula}F′=(A∪A′,R∪R′) with {a mathematical formula}A′={t}∪{t{a,b}|a,b∈A,(a,b)∉R,(b,a)∉R} and{a mathematical formula} That is we add a clique afC of size at most {a mathematical formula}(|A|2+|A|)/2+1 to F with a distinguished element t and link it to the original framework as follows: The argument t does not attack any of the original arguments. All the other arguments {a mathematical formula}t{a,b} attack all original arguments in F except a and b (note that a and b are not necessarily distinct). The construction is illustrated in Fig. 12.To prove the claim we have to show that F is σ-compact iff {a mathematical formula}F′ is σ-analytic. First observe that the new arguments in {a mathematical formula}F′ form a strongly connected component (SCC) and are not attacked by arguments from outside. As σ is SCC-splittable we can evaluate {a mathematical formula}F′ as follows:
      <list>
       Compute the extensions of the clique C.For each such extension E of C build the af{a mathematical formula}F|A∖EF′+ by removing all arguments in {a mathematical formula}EF′+ from F.For each extension {a mathematical formula}E′∈GFσ(F|A∖EF′+,UEA) return {a mathematical formula}E∪E′.Finally, as for each
      </list>
      <paragraph>
       {a mathematical formula}a∈A and {a mathematical formula}t{a}=t{a,a} the set {a mathematical formula}{t{a},a} is credulously accepted the af{a mathematical formula}F′ is compact. □
      </paragraph>
     </paragraph>
     <paragraph>
      From the generic results above we immediately get the complexity characterization for stable and preferred semantics.
     </paragraph>
     <paragraph label="Corollary 15">
      The following problems are{a mathematical formula}NP-complete for{a mathematical formula}σ∈{stb,prf}.
     </paragraph>
     <list>
      <list-item label="1.">
       GivenafF, deciding whether{a mathematical formula}F∈CAFσ;
      </list-item>
      <list-item label="2.">
       GivenafF, deciding whether{a mathematical formula}F∈XAFσ; hardness already holds if the problem is restricted toafs{a mathematical formula}F∈CAFσ.
      </list-item>
     </list>
     <paragraph label="Proof">
      Recall that {a mathematical formula}Credstb and {a mathematical formula}Credprf are {a mathematical formula}NP-complete [17] and that {a mathematical formula}NP is closed under conjunction. Membership thus follows from Theorem 9, Theorem 10. Furthermore, stb and prf are SCC-splittable [6] and rational. Theorem 13, Theorem 14 thus give the matching hardness results. □
     </paragraph>
     <paragraph>
      Theorem 13, Theorem 14 do not apply to stage and semi-stable semantics (as they are not SCC-splittable). However we can extend the results to these semantics by carefully adapting the ideas from the proofs of Theorem 13, Theorem 14. The main idea is still the same: we take the original afF and add a gadget of arguments that attack certain arguments in F but whose arguments are not attacked by arguments of F. Such a gadget (replacing the clique) has to satisfy certain properties: (i) its evaluation is independent of F; (ii) all arguments of the gadget are credulously accepted; (iii) there are certain arguments selecting a single argument, resp. a pair, of the original af for acceptance, by attacking all the other arguments of the original af; (iv) the gadget for testing {a mathematical formula}F∈CAF does not affect the acceptance of the argument under question and in the gadget for testing {a mathematical formula}F∈XAF there is an argument t that maintains all extensions E of F as extensions {a mathematical formula}{t}∪E.
     </paragraph>
     <paragraph label="Theorem 16">
      GivenafF:
     </paragraph>
     <list>
      <list-item label="1.">
       Deciding whether{a mathematical formula}F∈CAFstgis{a mathematical formula}Σ2P-complete.
      </list-item>
      <list-item label="2.">
       Deciding whether{a mathematical formula}F∈CAFsemis{a mathematical formula}Σ2P-complete.
      </list-item>
     </list>
     <paragraph>
      We split the proof of Theorem 16 into several Lemmas. First, we have to show that both problems can be solved in {a mathematical formula}Σ2P.
     </paragraph>
     <paragraph label="Lemma 17">
      Membership in {a mathematical formula}Σ2PBoth deciding whether{a mathematical formula}F∈CAFstgand deciding whether{a mathematical formula}F∈CAFsemare in{a mathematical formula}Σ2P.
     </paragraph>
     <paragraph label="Proof">
      The membership in {a mathematical formula}Σ2P follows from the memberships of {a mathematical formula}Credstg and {a mathematical formula}Credsem in {a mathematical formula}Σ2P[26], [13] and Theorem 9. □
     </paragraph>
     <paragraph>
      For hardness we give a reduction that constructs an af{a mathematical formula}F′ given an afF and an argument x. Although, this reduction will be used for both hardness proofs we will apply it to different problems, i.e. {a mathematical formula}Credstg and {a mathematical formula}Credsem, to show hardness for both stg and sem.
     </paragraph>
     <paragraph label="Reduction 1">
      Given anaf{a mathematical formula}F=(A,R)and{a mathematical formula}x∈Awe build theaf{a mathematical formula}F′=(A∪A′,R∪R′)with{a mathematical formula}The construction is illustrated inFig. 13.
     </paragraph>
     <paragraph>
      For both semantics we can assume that F has no self-attacks [26] and no stable extension. To achieve the second we can add an odd length cycle to F that is not connected to any other argument. This will guarantee that there is no stable extension and does not affect credulous acceptance w.r.t. semi-stable or stage semantics.
     </paragraph>
     <paragraph label="Lemma 18">
      Given anafF without self-attacks and stable extensions then{a mathematical formula}F′∈CAFstgiff{a mathematical formula}(F,x)∈Credstg.
     </paragraph>
     <paragraph label="Proof">
      Below we will show that all arguments except x are always credulously accepted in {a mathematical formula}F′ and that x is credulously accepted in {a mathematical formula}F′ iff x is credulously accepted in F.First, we show that each stage extension E contains at least one argument from {a mathematical formula}{ta|a∈A∪{y,z}}. Suppose that not, then, as at most one of the arguments {a mathematical formula}h1,h2,h3 is contained in E, two of the sets {a mathematical formula}E∪{tx}, {a mathematical formula}E∪{ty}, {a mathematical formula}E∪{tz} are conflict-free. Hence we have a contradiction to the maximality of E. Further, as {a mathematical formula}{ta|a∈A∪{y,z}} forms a clique in F we get that each stage extension contains exactly one argument from the set.Next we show that the ranges of naive sets E containing an argument from {a mathematical formula}{ta|a∈{x,y,z}} cannot be contained in the ranges of conflict-free sets {a mathematical formula}E′ not containing any of these arguments.
      <list>
       If {a mathematical formula}tx∈E then {a mathematical formula}h1 is attacked by E and cannot be in E but is in the range of E. Now as {a mathematical formula}h2 gives the larger range than {a mathematical formula}h3 we can conclude that {a mathematical formula}h2∈E and {a mathematical formula}{h1,h2,h3}∈EF′+. By similar arguments we get that {a mathematical formula}{h1,h2,h3}⊆EF′+ if either {a mathematical formula}ty∈E or {a mathematical formula}tz∈E.If {a mathematical formula}ta∈E′ with {a mathematical formula}a∉{x,y,z} then only one of {a mathematical formula}{h1,h2,h3} can be contained in {a mathematical formula}E′ and thus at most two of them are in the range of {a mathematical formula}E′.Finally, combining the above results, we have that all arguments in
      </list>
      <paragraph>
       {a mathematical formula}A′ except x are credulously accepted in {a mathematical formula}F′ and x is credulously accepted in {a mathematical formula}F′ iff x is credulously accepted in F iff {a mathematical formula}F′ is stg-compact. □
      </paragraph>
     </paragraph>
     <paragraph>
      Now, as Reduction 1 can be performed in polynomial-time and {a mathematical formula}Credstg is {a mathematical formula}Σ2P-hard [26], Lemma 18 implies that deciding whether {a mathematical formula}F∈CAFstg is {a mathematical formula}Σ2P-hard.
     </paragraph>
     <paragraph label="Lemma 19">
      Given anafF without self-attacks and stable extensions then{a mathematical formula}F′∈CAFsemiff{a mathematical formula}(F,x)∈Credsem.
     </paragraph>
     <paragraph>
      The proof of the above lemma is very similar to the proof of Lemma 18 and thus omitted here, but provided in Appendix B. Now, as Reduction 1 can be performed in polynomial-time and {a mathematical formula}Credsem is {a mathematical formula}Σ2P-hard [26], Lemma 19 implies that deciding whether {a mathematical formula}F∈CAFstg is {a mathematical formula}Σ2P-hard. This completes the proof of Theorem 16.
     </paragraph>
     <paragraph>
      Next, starting from Theorem 16 we can show that also deciding whether an af is analytic for stage or semi-stable is {a mathematical formula}Σ2P-complete.
     </paragraph>
     <paragraph label="Theorem 20">
      GivenafF:
     </paragraph>
     <list>
      <list-item label="1.">
       Deciding whether{a mathematical formula}F∈XAFstgis{a mathematical formula}Σ2P-complete.
      </list-item>
      <list-item label="2.">
       Deciding whether{a mathematical formula}F∈XAFsemis{a mathematical formula}Σ2P-complete.
      </list-item>
     </list>
     <paragraph>
      We split the proof of Theorem 20 into several Lemmas, starting with showing that both problems can be solved in {a mathematical formula}Σ2P.
     </paragraph>
     <paragraph label="Lemma 21">
      Membership in {a mathematical formula}Σ2PBoth deciding whether{a mathematical formula}F∈XAFstgand deciding whether{a mathematical formula}F∈XAFsemare in{a mathematical formula}Σ2P.
     </paragraph>
     <paragraph label="Proof">
      The membership in {a mathematical formula}Σ2P follows from the memberships of {a mathematical formula}Credstg2, {a mathematical formula}Credsem2 in {a mathematical formula}Σ2P[26], [13] and Theorem 10. □
     </paragraph>
     <paragraph>
      For hardness we give a reduction that constructs an af{a mathematical formula}F′ given an afF. Again this reduction will be used for both stg and sem but the hardness arguments will start from different problems, i.e. from testing whether an af is in {a mathematical formula}CAFstg, in {a mathematical formula}CAFsem respectively.
     </paragraph>
     <paragraph label="Reduction 2">
      Given anaf{a mathematical formula}F=(A,R)and theaf{sup:7}{a mathematical formula}G=(AG,RG)fromFig. 8we build theaf{a mathematical formula}F′=(A∪AG∪A′,R∪RG∪R′)with{a mathematical formula}The construction is illustrated inFig. 14.
     </paragraph>
     <paragraph>
      For both semantics we can assume that F has no self-attacks and no stable extension. This is by the fact that we made the same assumptions for the hardness proofs of Theorem 16 and the fact that Reduction 1 introduces neither self-attacks nor stable extensions.
     </paragraph>
     <paragraph label="Lemma 22">
      Given anafF without self-attacks and stable extensions then{a mathematical formula}F′∈CAFstg, and{a mathematical formula}F∈CAFstgiff{a mathematical formula}F′∈XAFstg.
     </paragraph>
     <paragraph label="Proof">
      First, we show that each stage extension E contains at least one argument from {a mathematical formula}A′. Suppose that not, then {a mathematical formula}E∖AG∪{t} is a conflict-free set that has {a mathematical formula}AG in its range. Hence we have a contradiction to the range maximality of E. Further, as {a mathematical formula}A′ forms a clique in F we get that each extension contains exactly one argument from the set.Next we show that the ranges of naive sets E containing argument t cannot be contained in the ranges of conflict-free sets {a mathematical formula}E′ containing an argument {a mathematical formula}ta,b with {a mathematical formula}a,b∈A.
      <list>
       If {a mathematical formula}t∈E then all arguments in {a mathematical formula}AG are attacked by E and thus are in the range of E.If {a mathematical formula}t∉E′ at least one argument of {a mathematical formula}AG is not in the range of {a mathematical formula}E′. Otherwise, {a mathematical formula}E′∩AG would be a stable extension of G, which contradicts {a mathematical formula}stb(G)=∅.Combining the above results, we have that all non-conflicting pairs of arguments in
      </list>
      <paragraph>
       {a mathematical formula}F′ except {a mathematical formula}{t,a} with {a mathematical formula}a∈A are credulously accepted in {a mathematical formula}F′. Thus {a mathematical formula}F′ is stg-analytic iff all the pairs {a mathematical formula}{t,a} with {a mathematical formula}a∈A are credulously accepted in {a mathematical formula}F′ iff each {a mathematical formula}a∈A is credulously accepted in F iff F is stg-compact.Finally we show that {a mathematical formula}F′∈CAFstg (independent of whether {a mathematical formula}F∈CAFstg). As (i) for each {a mathematical formula}a∈A the set {a mathematical formula}{ta,a,a} is credulously accepted, and (ii) for each {a mathematical formula}g∈AG and {a mathematical formula}a,b∈A with {a mathematical formula}(a,b),(b,a)∉R the set {a mathematical formula}{ta,b,g} is credulously accepted, the af{a mathematical formula}F′ is stg-compact. □
      </paragraph>
     </paragraph>
     <paragraph>
      Now, as Reduction 2 can be performed in polynomial-time and {a mathematical formula}CAFstg is {a mathematical formula}Σ2P-hard [Theorem 16], Lemma 22 implies that deciding whether {a mathematical formula}F∈CAFstg is {a mathematical formula}Σ2P-hard.
     </paragraph>
     <paragraph label="Lemma 23">
      Given anafF without self-attacks and stable extensions then{a mathematical formula}F′∈CAFsem, and{a mathematical formula}F∈CAFsemiff{a mathematical formula}F′∈XAFsem.
     </paragraph>
     <paragraph>
      The proof of the above lemma is very similar to the proof of Lemma 22 and thus omitted here, but provided in Appendix B. Now, as Reduction 2 can be performed in polynomial-time and {a mathematical formula}CAFsem is {a mathematical formula}Σ2P-hard [Theorem 16], Lemma 23 implies that deciding whether {a mathematical formula}F∈CAFstg is {a mathematical formula}Σ2P-hard. This completes the proof of Theorem 20.  □
     </paragraph>
     <paragraph>
      In conclusion we have that for all the semantics under our considerations the complexity of testing whether an af is compact or analytic is as hard as credulous acceptance. We summarize the results of this section in Table 2.
     </paragraph>
     <paragraph>
      Complexity of further decision problems. Similar to other subclasses, compact and analytic afs decrease the complexity of certain decision problems. Let us first discuss the case of compact afs. By definition for credulous acceptance (does an argument occur in at least one extension), this problem becomes trivial for this class. For skeptical acceptance (does an argument a occur in all extensions) in compact afs the problem reduces to checking whether a is isolated. If yes, it is skeptically accepted; if no, a is connected to at least one further argument that has to be credulously accepted by the definition of compact afs. But then, it is the case for any semantics that is based on conflict-free sets that a cannot be skeptically accepted, since it will not appear together with b in an extension. For analytic afs we can distinguish between afs with self-attacks and without. In the latter case the afs are also compact (cf. Proposition 5) and thus credulous and skeptical acceptance can be solved as described above. In the former case, for credulous acceptance we only have to check whether the argument is self-attacking or not. For skeptical acceptance the behavior seems to diverge between different semantics. On the one hand, for deciding whether an argument is skeptically accepted w.r.t. stable semantics one can test if the argument is credulously accepted and all its attackers are not credulously accepted, which can be done in polynomial time. On the other hand side, for preferred and semi-stable semantics analytic afs seem to have no computational benefits. Moreover, [10] showed that in compact afs the verification problem (given afF and a set of arguments E, is E a σ-extension of F?) is still {a mathematical formula}coNP-hard for stage, semi-stable and preferred semantics. Theses results can be extended to analytic afs by the observation that the reductions used in the proofs of Theorem 14, Theorem 20 are also valid reductions for the verification problem.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Explicit conflict conjecture
     </section-title>
     <paragraph>
      In this section we take another look at the issue of implicit conflicts and the possibility of making them explicit. In Section 3.2 we identified the classes of afs where all conflicts are explicit w.r.t. a given semantics. Recall the notion of an analytic af from Definition 4. In [10] the authors conjectured that, under stable semantics, every af can be translated to an equivalent analytic af (having the same set of arguments), i.e. that all implicit conflicts can be made explicit without changing the stable extensions. We will refute this conjecture and show that the claim also does not hold for preferred, semi-stable and stage semantics.
     </paragraph>
     <paragraph label="Definition 7">
      An afF is called quasi-analytic for σ if there is an afG such that {a mathematical formula}AF=AG, {a mathematical formula}σ(F)=σ(G) and G is analytic for σ, i.e., it has only explicit conflicts for σ. On the other hand, F is called non-analytic for σ if it is not quasi-analytic for σ.
     </paragraph>
     <paragraph label="Example 4">
      Consider again the af in Fig. 2, which, as we have seen in Example 3, is not analytic for {a mathematical formula}σ∈{stb,prf,sem,stg}. However, adding the attack {a mathematical formula}c↣d (or {a mathematical formula}d↣c or both) we obtain an equivalent (under σ) af{a mathematical formula}F′, where all conflicts are explicit. Thus F is quasi-analytic.   ◊
     </paragraph>
     <paragraph>
      In other words, an af is quasi-analytic for a given semantics σ if it can be translated to another af that has the same arguments, has the same extensions under σ, and all conflicts are explicit. The conjecture from [10] says that every af containing implicit conflicts for stable semantics is quasi-analytic, in the sense that all implicit conflicts can be made explicit without adding further arguments. We repeat the conjecture from [10], just parameterized by an arbitrary semantics. In line with the following definition, [10] claimed that ECC holds for stable semantics.
     </paragraph>
     <paragraph label="Definition 8">
      We say that the Explicit Conflict Conjecture (ECC) holds for semantics σ if every af is quasi-analytic for σ.
     </paragraph>
     <paragraph>
      First note that, as discussed in the introduction, ECC holds for naive semantics. Every pair of non-self-attacking arguments occurs together in a naive extension if and only if there is no attack between them. Hence a conflict can only be implicit for naive semantics if at least one of the arguments involved is self-attacking. But letting each self-attacking argument be attacked by all other arguments does not change the naive extensions (and obviously does not change the set of arguments), hence every af is quasi-analytic.
     </paragraph>
     <paragraph>
      In the remainder of this section we will refute ECC for all semantics in {a mathematical formula}{stb,prf,sem,stg} by providing non-analytic afs.
     </paragraph>
     <paragraph label="Example 5">
      Take into account the af{a mathematical formula}F=(A,R) depicted in Fig. 15, which features an implicit conflict for stable semantics between a and b:{a mathematical formula}In the following we refer to {a mathematical formula}A1={v1}, {a mathematical formula}A2={u1}, {a mathematical formula}A3={x1,y1}, and {a mathematical formula}B1={v2}, {a mathematical formula}B2={u2}, {a mathematical formula}B3={x2,y2}. The stable extensions of F can be separated into extensions containing c and others. For {a mathematical formula}i,j∈{1,2,3} the former are given as:{a mathematical formula} If on the other hand {a mathematical formula}c∉S one of {a mathematical formula}a,b will be a member of S and thus:{a mathematical formula} For {a mathematical formula}S∈stb(F) and wlog. {a mathematical formula}a∈S take into account that a is attacked by {a mathematical formula}u1 and the only possible defenders {a mathematical formula}v1 and {a mathematical formula}y1 are explicitly in conflict with b. Thus clearly a and b share an implicit conflict, as one cannot be defended without the other being attacked. However observe that all the other conflicts implicitly defined by the extension-set {a mathematical formula}S={S1,S2,…,S6}∪{Sij|i,j∈{1,2,3}} are already given explicitly in F. Furthermore the remaining maximal conflict-free sets {a mathematical formula}Sa={a,y1,y2} and {a mathematical formula}Sb={b,x1,x2} do attack neither b nor a respectively and thus are not stable extensions of F.   ◊
     </paragraph>
     <paragraph>
      We now proceed by showing that the af depicted in Fig. 15 and discussed in Example 5 serves as a counter-example for ECC for stable semantics.
     </paragraph>
     <paragraph label="Theorem 24">
      There are non-analyticafs for stable semantics.
     </paragraph>
     <paragraph label="Proof">
      Consider the afF from Example 5 and recall its set of stable extensions {a mathematical formula}S. We will show that there is no afG with {a mathematical formula}AG=AF, {a mathematical formula}stb(G)=S and {a mathematical formula}(a,b)∈RG. (Observe that due to symmetry reasons we need not consider {a mathematical formula}(b,a)∈RG and {a mathematical formula}(a,b)∉RG.) For a contradiction take such an af as given.The extensions containing c ensure that there is no attack in G between arguments c and {a mathematical formula}αi for {a mathematical formula}α∈{x,u,v,y} and {a mathematical formula}i∈{1,2}, or between {a mathematical formula}α1 and {a mathematical formula}α2. By definition any stable extension {a mathematical formula}S∈S attacks all outside arguments, {a mathematical formula}S↣α for {a mathematical formula}α∈AG∖S. Hence from {a mathematical formula}S3={a,v1,y2} being a stable extension we conclude {a mathematical formula}a↣c and {a mathematical formula}{a,y2}↣α2 for {a mathematical formula}α∈{x,u,v}. Similarly due to {a mathematical formula}S4={a,y1,v2} we conclude that {a mathematical formula}{a,y1}↣α1 for {a mathematical formula}α∈{x,u,v}. But now by assumption {a mathematical formula}a↣b and thus for {a mathematical formula}Sa={a,y1,y2} we acquire full range, {a mathematical formula}Sa↣α for any {a mathematical formula}α∈AG∖Sa, i.e. {a mathematical formula}Sa becomes an unwanted stable extension. Therefore F is non-analytic. □
     </paragraph>
     <paragraph>
      We observe that in this counter-example for ECC for stable semantics the stable extensions coincide with semi-stable, preferred and stage extensions. With the following lemma this leads to some straightforward generalizations.
     </paragraph>
     <paragraph label="Lemma 25">
      Let F be anafwith{a mathematical formula}prf(F)=stb(F)(resp.{a mathematical formula}sem(F)=stb(F)). If F is quasi-analytic for preferred (resp. semi-stable) semantics, then it is also quasi-analytic for stable semantics.
     </paragraph>
     <paragraph label="Proof">
      By assumption, for {a mathematical formula}σ∈{prf,sem}, there is a σ-analytic afG such that {a mathematical formula}AG=AF and {a mathematical formula}σ(F)=σ(G). We want to show that {a mathematical formula}stb(G)=σ(G). Using the fact that for any afF, {a mathematical formula}stb(F)⊆σ(F) holds, it remains to show that {a mathematical formula}σ(G)⊆stb(G). To this end observe that any attack of F still represents an explicit conflict in G. Now for {a mathematical formula}S∈stb(F) we know that for all {a mathematical formula}a∈AF∖S we have {a mathematical formula}S↣Fa. Since by assumption also {a mathematical formula}S∈σ(F) this immediately implies an explicit conflict between S and a in G. Due to admissibility of σ-extensions this means that actually {a mathematical formula}S↣Ga as otherwise S would not defend itself from a in G. Therefore we have {a mathematical formula}S↣Ga for all {a mathematical formula}a∈AG∖S. Hence {a mathematical formula}S∈stb(G), resulting in {a mathematical formula}σ(G)=stb(G) and thus G being stb-analytic and also F being stb-quasi-analytic. □
     </paragraph>
     <paragraph>
      Using the afF from Example 5 and the contraposition of Lemma 25 yields the following result, refuting ECC for preferred and semi-stable semantics.
     </paragraph>
     <paragraph label="Corollary 26">
      There are non-analyticafs for preferred and semi-stable semantics, respectively.
     </paragraph>
     <paragraph>
      The next example shows that some afs prove to be non-analytic for preferred semantics while being quasi-analytic for all the other semantics under consideration.
     </paragraph>
     <paragraph label="Example 6">
      Take into account the af{a mathematical formula}F=(A,R) as depicted in Fig. 16 with{a mathematical formula} We have {a mathematical formula}prf(F)={Sa,Sb,A1,A2,A3,B1,B2,B3} and{a mathematical formula} In the following we show that F is non-analytic for preferred semantics. For a contradiction we assume that there exists an analytic afG with {a mathematical formula}AG=A and {a mathematical formula}prf(F)=prf(G). We now investigate this hypothetical afG. Observe that for {a mathematical formula}i,j∈{1,2,3} due to {a mathematical formula}Sb there is no conflict between {a mathematical formula}ui and {a mathematical formula}bj, due to {a mathematical formula}A1,A2,A3 there is no conflict between {a mathematical formula}ui and {a mathematical formula}aj, and for {a mathematical formula}i≠j there is no conflict between {a mathematical formula}xi and {a mathematical formula}uj; in other words in G the {a mathematical formula}ui can be attacked only by the {a mathematical formula}xi. Furthermore we have an implicit conflict between {a mathematical formula}a1 and {a mathematical formula}x2. Due to {a mathematical formula}Sa being admissible and G being analytic now {a mathematical formula}Sa↣Gx2. But then {a mathematical formula}Sa defends {a mathematical formula}u2 and thus can not be a preferred extension in G. For symmetry reasons it follows that the implicit conflicts {a mathematical formula}(ai,xj) of F cannot be made explicit for preferred semantics.On the other hand for stable (or stage or semi-stable) semantics we observe that {a mathematical formula}Sa is not an extension. Although the overall conflicts remain the same, this allows us to include conflicts {a mathematical formula}(xj,ai) without any harm for the other extensions. Thus for stable, semi-stable and stage semantics this af is quasi-analytic.   ◊
     </paragraph>
     <paragraph>
      We still have not answered the question whether stage semantics possesses non-analytic afs. A candidate for a non-analytic af for stage semantics would be the afF from Example 5, but it turns out to be quasi-analytic for stage semantics. In fact, the analytic afG depicted in Fig. 17 has the same stage extensions as F, {a mathematical formula}stb(F)=stg(F)=stg(G).
     </paragraph>
     <paragraph>
      However, the following slightly more involved example yields a non-analytic af for stage semantics.
     </paragraph>
     <paragraph label="Example 7">
      Take into account the af{a mathematical formula}F=(A,R) depicted in Fig. 18 with:{a mathematical formula}In the following we will refer to {a mathematical formula}Mi1={ri,vi,si},Mi2={ri,ui,si},Mi3={ri,yi},Mi4={xi,si},Mi5={xi,yi}. The stable extensions of F can be separated into extensions containing c and others. For {a mathematical formula}i,j∈{1…5} the former are given as:{a mathematical formula} If, on the other hand, {a mathematical formula}c∉S, one of {a mathematical formula}a,b will be a member of S:{a mathematical formula} Similarly to Example 5 we have that a and b share an implicit conflict for stable and thus stage semantics, as {a mathematical formula}stb(F)=stg(F)=S={S1…S6}∪{Sij|i,j∈{1…5}}. Again except for the implicit conflict between a and b all conflicts in F already are explicit, and the only other maximal conflict-free sets {a mathematical formula}Sa={a,r1,r2,y1,y2} and {a mathematical formula}Sb={b,x1,x2,s1,s2} are not stable extensions here.  ◊
     </paragraph>
     <paragraph label="Theorem 27">
      There are non-analyticafs for stage semantics.
     </paragraph>
     <paragraph label="Proof">
      Consider the af{a mathematical formula}F=(A,R) from Example 7. We first show that F is non-analytic for stable semantics by assuming a contradicting analytic afG of the same arguments and extensions. We will then use this observation to proceed similarly for stage semantics. As for any afG with {a mathematical formula}stb(G)≠∅ we have {a mathematical formula}stb(G)=stg(G), we will assume some afG which is analytic for stage semantics where {a mathematical formula}stb(G)=∅. In fact for both, stable and stage semantics, we show a slightly stronger result; for the given extension-set the conflict between a and b has to be implicit. For symmetry reasons, wlog. we assume {a mathematical formula}(a,b)∈RG. In what follows, we use the same naming schema for extensions as in Example 7.For stable semantics we need {a mathematical formula}a↣c, since e.g. {a mathematical formula}S1 has to be a stable extension. From {a mathematical formula}S33∈stb(G), {a mathematical formula}a↣b by assumption and as observed {a mathematical formula}a↣c we conclude {a mathematical formula}Sa∈stb(G), as {a mathematical formula}c∈S33 is allowed to attack only a and b. Thus if G is analytic for stable semantics then {a mathematical formula}stb(F)≠stb(G).We now turn to stage semantics and have the following observations:
     </paragraph>
     <list>
      <list-item label="•">
       For {a mathematical formula}i∈{1,2}, due to maximal conflict-freeness and the given conflicts, we need explicit conflicts between {a mathematical formula}si and {a mathematical formula}yi, {a mathematical formula}ri and {a mathematical formula}xi ({a mathematical formula}ri,si∉S55), between c and a, c and b ({a mathematical formula}a∉S33, {a mathematical formula}b∉S44), and between {a mathematical formula}ui and {a mathematical formula}vi ({a mathematical formula}vi∉S22). We will frequently make use of these necessities in the following.
      </list-item>
      <list-item label="•">
       For the explicit conflict between {a mathematical formula}s1 and {a mathematical formula}y1, we need {a mathematical formula}s1↣y1 for otherwise {a mathematical formula}S55+⊂S45+. Similarly we conclude {a mathematical formula}s2↣y2, {a mathematical formula}r1↣x1 and {a mathematical formula}r2↣x2;
      </list-item>
      <list-item label="•">
       As the conflict between c and a is explicit, furthermore necessarily {a mathematical formula}c↣a for otherwise (in case {a mathematical formula}a↣c and {a mathematical formula}c↣̸a) {a mathematical formula}S11+⊂S1+;
      </list-item>
      <list-item label="•">
       Now since {a mathematical formula}ui and {a mathematical formula}vi need to be in conflict we need {a mathematical formula}c↣̸b for otherwise at least one of {a mathematical formula}Sij for {a mathematical formula}i,j∈{1,2} becomes a stable extension. By conflict-implicitness hence {a mathematical formula}b↣c.
      </list-item>
      <list-item label="•">
       From {a mathematical formula}c↣a, {a mathematical formula}r1↣x1 and {a mathematical formula}s1↣y1 we conclude {a mathematical formula}u1↣v1 due to the danger of {a mathematical formula}S21+⊂S11+. Similarly {a mathematical formula}u2↣v2.
      </list-item>
      <list-item label="•">
       Since {a mathematical formula}c↣a and {a mathematical formula}ui↣vi furthermore we need {a mathematical formula}xi↣ri, {a mathematical formula}xi↣ui and {a mathematical formula}xi↣vi, due to range comparison of {a mathematical formula}Mi4 and {a mathematical formula}Mi2.
      </list-item>
      <list-item label="•">
       By previous range observations we have to assume {a mathematical formula}b↣̸a and {a mathematical formula}ui↣̸a, for otherwise {a mathematical formula}S2 becomes a stable extension.
      </list-item>
      <list-item label="•">
       But now {a mathematical formula}S2+⊆Sb+, i.e. either we gain the unwanted extension {a mathematical formula}Sb or we lose the desired extension {a mathematical formula}S2. □
      </list-item>
     </list>
     <paragraph>
      To conclude this section we investigate the question of conditions such that ECC holds. We have mentioned earlier that every af is quasi-analytic for naive semantics. This insight can be generalized as follows.
     </paragraph>
     <paragraph label="Proposition 28">
      Let{a mathematical formula}σ∈{stg,stb,sem,prf}. If for someafF there exists anafG such that{a mathematical formula}σ(F)=nai(G), then F is quasi-analytic for σ.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}F,G be afs with {a mathematical formula}σ(F)=nai(G). We define the afH with {a mathematical formula}AH=AF and {a mathematical formula}RH={〈a,b〉|(a,b)∈RG,a,b∈Argsσ(F)}∪{〈a,x〉,(x,x)|a∈AF,x∉Argsσ(F)}. As this afH provides the same conflicts as the afG for naive semantics, we deduce that also the maximal conflict-free sets are the same, {a mathematical formula}nai(H)=nai(G). By definition of H, for any {a mathematical formula}S∈nai(H) and {a mathematical formula}a∈AF∖S we have {a mathematical formula}S↣Ha and hence S is a stable extension of H. Finally observe that {a mathematical formula}stb(H)⊆σ(H)⊆nai(H) for any afH, hence the result follows. □
     </paragraph>
     <paragraph>
      Another property that guarantees that ECC holds relies on the existence of what we call “identifying arguments”. We say that an afF is determined for semantics σ if for every {a mathematical formula}S∈σ(F) there exists an {a mathematical formula}a∈S such that for {a mathematical formula}S′∈σ(F) we have that {a mathematical formula}a∈S′ implies {a mathematical formula}S′=S. In other words, every σ-extension contains an identifying argument in the sense that it does not occur in any other σ-extension. A simple necessary condition for an af to be determined for σ is that the number of σ-extensions does not exceed the number of arguments.
     </paragraph>
     <paragraph label="Proposition 29">
      Let{a mathematical formula}σ∈{stb,prf,sem,stg}. Then, anyafF determined for σ is quasi-analytic for σ.
     </paragraph>
     <paragraph label="Proof">
      Consider an afF determined for σ and for each {a mathematical formula}S∈σ(F) let {a mathematical formula}aS be some fixed identifying argument. Now taking into account the sets {a mathematical formula}I={aS|S∈σ(F)} and {a mathematical formula}RI={〈aS,aS′〉|S,S′∈σ(F),S≠S′}, clearly {a mathematical formula}σ((I,RI))={{aS}|S∈σ(F)}. Furthermore let {a mathematical formula}O=AF∖I be the remaining arguments of F and {a mathematical formula}RO={〈a,b〉|a,b∈O,(a,b)∉Pairsσ(F)}. We now define G as {a mathematical formula}AG=AF=O∪I and {a mathematical formula}RG=RI∪RO∪{(aS,b)|S∈σ(F),b∈(O∖S)}. Observe that I forms a clique within G, a clique that is not attacked by arguments in O. For the SCC-splittable (cf. Definition 5) stable semantics we can evaluate G as follows:
      <list>
       Compute the extensions of the clique I.For each such extension E of I build the af{a mathematical formula}G|O∖EG+.For each extension {a mathematical formula}E′∈GFstb(G|O∖EG+,UEO) return {a mathematical formula}E∪E′.Finally observe that all conflicts in
      </list>
      <paragraph>
       G for σ (among I, among O or between I and O) are explicit by definition. □
      </paragraph>
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Signatures
     </section-title>
     <paragraph>
      The last section dealt with the problem of making conflicts explicit without changing the set of arguments, or, in other words, finding an analytic af with the same arguments that is equivalent with respect to a given semantics. Abstaining from the condition that the set of arguments must be preserved, the focus is not on the given af any more but on its sets of extensions. Given an extension-set {a mathematical formula}S and a semantics σ, the question is then whether the extension-set can be analytically realized, i.e. whether there is an analytic afF having exactly {a mathematical formula}σ(F)=S, but imposing no restrictions on the arguments of F. We will deal with analytic realizability in Section 6.1. Likewise, Section 6.2 will be concerned with compact realizability where the af realizing a given extension-set needs to be compact.
     </paragraph>
     <paragraph>
      Prima facie this may seem similar to the concepts of analytic and compact argumentation frameworks studied in Section 3. However, relations between semantics from there do not carry over to realizability. For example we have seen in Theorem 2 that {a mathematical formula}CAFprf⊂CAFnai, that is, every af that is compact for preferred semantics is also compact for naive semantics and there exist afs compact for naive but not compact for preferred semantics. In terms of compact realizability we will see that these semantics are related conversely, because compact realizability under naive semantics implies compact realizability under preferred semantics, but not vice versa (cf. Theorem 34).
     </paragraph>
     <paragraph>
      Both analytic and compact realizability are restricted versions of the concept of (general) realizability studied in [23]. We first repeat the basic definitions and main results from there. Then we will for the analytic and compact scenario, respectively, first analyze the difference to general realizability and then deal with relations between the semantics under consideration.
     </paragraph>
     <paragraph label="Definition 9">
      An extension-set {a mathematical formula}S is called realizable under semantics σ if there is an afF with {a mathematical formula}σ(F)=S. The signature of a semantics σ is defined as{a mathematical formula}
     </paragraph>
     <paragraph>
      The main results from [23] include {a mathematical formula}Σnai⊂Σstg=(Σstb∖{∅})⊂Σprf=Σsem.
     </paragraph>
     <section label="6.1">
      <section-title>
       Analytic signatures
      </section-title>
      <paragraph>
       In this section we deal with the restricted form of realizability, namely without the use of implicit conflicts.
      </paragraph>
      <paragraph label="Definition 10">
       An extension-set {a mathematical formula}S is called analytically realizable under semantics σ if there is some analytic af{a mathematical formula}F∈XAFσ with {a mathematical formula}σ(F)=S. The analytic signature (x-signature){a mathematical formula}Σσx of semantics σ consists of all extension-sets that are analytically realizable under σ:{a mathematical formula}
      </paragraph>
      <paragraph>
       First of all note that every extension-set in the analytic signature of a semantics is also in the signature, i.e., {a mathematical formula}Σσx⊆Σσ. In the following we will, for each semantics under consideration, either show that the relation is strict in the sense that certain extension-sets in {a mathematical formula}Σσ are not analytically realizable or show that also {a mathematical formula}Σσx⊇Σσ holds, meaning that {a mathematical formula}Σσx and {a mathematical formula}Σσ coincide.
      </paragraph>
      <paragraph>
       First we consider the relation between the signature {a mathematical formula}Σnai and the analytic signature {a mathematical formula}Σnaix of naive semantics and formalize what we have already discussed in the introduction.
      </paragraph>
      <paragraph label="Theorem 30">
       It holds that{a mathematical formula}Σnaix=Σnai.
      </paragraph>
      <paragraph label="Proof">
       Consider some {a mathematical formula}S∈Σnai with F being the af realizing {a mathematical formula}S under naive semantics. It holds that a pair of arguments is contained in {a mathematical formula}PairsS iff there is no attack between these arguments and none of them is self-attacking. Moreover, letting each self-attacking argument be attacked by all other arguments has no effect on the naive extensions. Hence the af{a mathematical formula}F′ obtained from doing so has {a mathematical formula}nai(F′)=S and {a mathematical formula}F′∈XAFnai, therefore {a mathematical formula}Σnaix=Σnai. □
      </paragraph>
      <paragraph>
       Preferred and semi-stable semantics show strictly less expressiveness with respect to realizable extension-sets without implicit conflicts.
      </paragraph>
      <paragraph label="Theorem 31">
       For{a mathematical formula}σ∈{prf,sem}it holds that{a mathematical formula}Σσx⊂Σσ.
      </paragraph>
      <paragraph label="Proof">
       Again consider the afF in Fig. 16 and let {a mathematical formula}S=prf(F), which is given in Example 6. There we showed that there is no prf-analytic afG having {a mathematical formula}σ(G)=S and {a mathematical formula}AG=AF. Here we can abstain from the last condition. So assume there is an af{a mathematical formula}G′∈XAFprf with {a mathematical formula}σ(G′)=S. We know from Example 6 that there cannot be an attack between {a mathematical formula}Sa={a1,a2,a3}∈S and {a mathematical formula}u2 and that in order for {a mathematical formula}G′ to be analytic {a mathematical formula}a1↣Gx2. Moreover note that {a mathematical formula}x2 is the only possible attacker of {a mathematical formula}u2 among {a mathematical formula}ArgsS. Finally, every additional argument {a mathematical formula}z∉ArgsS in {a mathematical formula}G′ must be attacked by {a mathematical formula}Sa since {a mathematical formula}G′ is prf-analytic and {a mathematical formula}Sa must be admissible. This causes {a mathematical formula}Sa∪{u2} to be admissible in {a mathematical formula}G′, hence {a mathematical formula}Sa cannot be preferred in {a mathematical formula}G′. Thus any af realizing {a mathematical formula}S is non-analytic for preferred semantics or, in other words, {a mathematical formula}S∈Σprf∖Σprfx.Due to [25], [23] we know that {a mathematical formula}Σsem=Σprf, hence there is an af{a mathematical formula}F′ having {a mathematical formula}sem(F′)=S. But when trying to analytically realize {a mathematical formula}S under sem, we make the same observations as above, meaning that {a mathematical formula}Sa∪{u2} is necessarily admissible, a contradiction to {a mathematical formula}Sa being semi-stable. Hence also {a mathematical formula}S∈Σsem∖Σsemx. □
      </paragraph>
      <paragraph>
       We now turn to stable and stage semantics. In contrast to preferred and semi-stable semantics, we will see that the use of additional arguments allows us to make each implicit conflict explicit. Therefore the analytic signature coincides with the signature for stable and stage semantics.
      </paragraph>
      <paragraph>
       The following proposition shows that one additional argument allows, together with an appropriate modification of the attack relation, to make any single implicit conflict explicit.
      </paragraph>
      <paragraph label="Proposition 32">
       For stable semantics and someafF, if there is an implicit conflict between a and b, then there is anafG with{a mathematical formula}|AG|=|AF|+1,{a mathematical formula}RG⊇RF,{a mathematical formula}(a,b)∈RGand{a mathematical formula}stb(G)=stb(F)and all implicit conflicts in G are implicit conflicts in F as well.
      </paragraph>
      <paragraph label="Proof">
       Let F be an arbitrary af with an implicit conflict between two arguments a and b. We define {a mathematical formula}R′=RF∪{(a,b)}. Observe that {a mathematical formula}F′=(AF,R′) has the same and possibly more stable extensions as compared to F. By construction of {a mathematical formula}F′, any {a mathematical formula}S∈stb(F′)∖stb(F) has {a mathematical formula}a∈S and {a mathematical formula}S↣̸Fb. We collect the arguments of these unwanted extensions in {a mathematical formula}Aa=Args(stb(F′)∖stb(F)) and observe that {a mathematical formula}Aa↣̸Fb. Now define the afG with {a mathematical formula}AG=AF∪{x} and{a mathematical formula} First note that obviously {a mathematical formula}|AG|=|AF|+1, {a mathematical formula}RG⊇RF, and {a mathematical formula}(a,b)∈RG. Moreover, since the new argument x attacks or is attacked by every other argument, G does not introduce any further implicit conflicts compared to F. It remains to show that {a mathematical formula}stb(G)=stb(F). Let {a mathematical formula}S′∈stb(F) and assume that {a mathematical formula}b∈S′. As by assumption b and a do not occur together in any stable extension of F, we know that {a mathematical formula}b↣Gx and thus {a mathematical formula}S′∈stb(G). On the other hand assume that {a mathematical formula}b∉S′. Then we have some {a mathematical formula}c∈S′ with {a mathematical formula}c↣Fb. If {a mathematical formula}S′∉stb(G), then only because {a mathematical formula}S′↣̸Gx, hence {a mathematical formula}S′⊆Aa, a contradiction to {a mathematical formula}Aa↣̸Fb. Therefore {a mathematical formula}S′∈stb(G). Now assume there is some {a mathematical formula}S∈stb(G) with {a mathematical formula}S∉stb(F). By the construction of G this S must be among {a mathematical formula}stb(F′)∖stb(F). However, we then have {a mathematical formula}S↣̸Gx, a contradiction to {a mathematical formula}S∈stb(G), concluding the proof for {a mathematical formula}stb(F)=stb(G). □
      </paragraph>
      <paragraph>
       Now we can show that analytic and general signatures coincide for stable and stage semantics.
      </paragraph>
      <paragraph label="Theorem 33">
       For{a mathematical formula}σ∈{stb,stg}it holds that{a mathematical formula}Σσx=Σσ.
      </paragraph>
      <paragraph label="Proof">
       We consider as special case {a mathematical formula}stb(F)=∅ or {a mathematical formula}stg(F)={∅} where by definition the af{a mathematical formula}F=({x},{(x,x)}) serves as analytic witness. Let {a mathematical formula}S∈Σσ, i.e., there is some afF with {a mathematical formula}σ(F)=S. As by definition any afF is finite we can have at most finitely many implicit conflicts for semantics {a mathematical formula}σ∈{stb,stg}. Each of them can be removed by repeated application of Proposition 32 for {a mathematical formula}σ=stb. Hence there is an analytic af{a mathematical formula}F′ with {a mathematical formula}σ(F′)=S, meaning that {a mathematical formula}S∈Σstbx. For {a mathematical formula}σ=stg semantics we know from [25] that there is an afG with {a mathematical formula}stb(G)=stg(G)=S. Now, again, we can remove all implicit conflicts and end up with the stg-analytic af{a mathematical formula}G′ with {a mathematical formula}stg(G′)=S. Hence {a mathematical formula}S∈Σstgx. □
      </paragraph>
      <paragraph>
       So far we have compared general signatures and analytic signatures for the semantics under consideration. We have seen that preferred and semi-stable semantics can realize strictly more when allowing the use of implicit conflicts, while this is not the case for stable and stage semantics.
      </paragraph>
      <paragraph>
       In the following we relate the analytic signatures of naive, stable, preferred, stage and semi-stable semantics to each other. For general signatures it was shown in [23] that {a mathematical formula}Σnai⊂Σstg=(Σstb∖{∅})⊂Σsem=Σprf. In the analytic case preferred and semi-stable signatures do not coincide anymore.
      </paragraph>
      <paragraph label="Theorem 34">
       In accordance withFig. 19, it holds that:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Σnaix⊂Σσxfor{a mathematical formula}σ∈{stb,stg,sem,prf};
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Σstbx∖{∅}=Σstgx;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}Σstgx⊂Σsemx;
       </list-item>
       <list-item label="4.">
        {a mathematical formula}Σsemx⊂Σprfx.
       </list-item>
      </list>
      <paragraph label="Proof">
       (1) First recall from [23] that for a given {a mathematical formula}S∈Σnaix, the canonic afF where {a mathematical formula}AF=ArgsS and {a mathematical formula}RF=(AF×AF)∖PairsS gives {a mathematical formula}S=nai(F)=σ(F), and F is analytic for σ, thus {a mathematical formula}Σnaix⊆Σσx.Further consider the afF where {a mathematical formula}AF={x1,x2,x3,y1,y2,y3} and {a mathematical formula}RF={(xi,xj),(xi,yi)|i,j∈{1,2,3}}, cf. Fig. 20, the af featured in [25] to show that {a mathematical formula}σ(F)={{x1,y2,y3},{x2,y1,y3},{x3,y1,y2}} can not be realized under naive semantics. With the fact that this af is analytic for σ we obtain {a mathematical formula}Σnaix⊉Σσx, hence {a mathematical formula}Σnaix⊂Σσx.(2) Considering {a mathematical formula}Σstb∖{∅}=Σstg[23] and Theorem 33 we obtain {a mathematical formula}Σstbx∖{∅}=Σstgx.(3) For {a mathematical formula}S∈Σstgx with {a mathematical formula}S≠{∅} we know from (2) that there is an analytic afF with {a mathematical formula}stb(F)=S. Now as {a mathematical formula}S≠{∅} also {a mathematical formula}sem(F)=S, hence {a mathematical formula}S∈Σsemx. As obviously {a mathematical formula}{∅}∈Σsemx (witnessed by {a mathematical formula}({x},{(x,x)})), we get {a mathematical formula}Σstgx⊆Σsemx.For properness take a look at the afF from Fig. 8, which, as discussed in the proof of Theorem 4, is analytic for semi-stable semantics. Now consider, for instance, {a mathematical formula}S={r1,a1,v1,b1}∈sem(F). Observe that {a mathematical formula}ci∉S for {a mathematical formula}i∈{1,2,3} besides {a mathematical formula}ci not being in conflict with S. If there was an af{a mathematical formula}F′∈XAFstg with {a mathematical formula}stg(F′)=sem(F), then there can not be any attack between S and {a mathematical formula}ci in F. But then {a mathematical formula}S∪{c1} is conflict-free in {a mathematical formula}F′ and its range is strictly larger than the range of S. Thus {a mathematical formula}sem(F)∉Σstgx and therefore {a mathematical formula}Σstgx⊂Σsemx.(4) For the last part of the theorem recall that the exact translation for {a mathematical formula}sem→prf from [25] does not add any implicit conflicts between arguments from the original af. In more detail for a given (analytic) afF we add one self-attacking argument {a mathematical formula}xS for any unwanted preferred extension {a mathematical formula}S∈prf(F)∖sem(F), and further add attacks {a mathematical formula}(xS,a) for {a mathematical formula}a∈S and {a mathematical formula}(b,xS) for {a mathematical formula}b∈AF∖S. Thus the only implicit conflicts generated by this translation are conflicts between new and self-attacking arguments. However we can simply make such conflicts explicit by adding attacks between any self-attacking arguments, which does not affect preferred semantics, and hence {a mathematical formula}Σsemx⊆Σprfx.Now, for properness, consider the prf-analytic afF from Fig. 9. Define a cyclic successor functions with {a mathematical formula}s(1)=2,s(2)=3,s(3)=1 and {a mathematical formula}s(4)=5,s(5)=6,s(6)=4. We have as preferred extensions {a mathematical formula}prf(F)=S0∪S1∪S2 with{a mathematical formula}Assume that there is some {a mathematical formula}G∈XAFsem with {a mathematical formula}sem(G)=prf(F). We take a look at {a mathematical formula}S1 and more specifically {a mathematical formula}{x1,y1,z2}∈S1. Now we need an explicit conflict between {a mathematical formula}x1 and {a mathematical formula}x4, but in the selected set only {a mathematical formula}x1 can possibly defend against this attack, hence {a mathematical formula}(x1,x4)∈RG. The same argument works for {a mathematical formula}x1 and {a mathematical formula}x3 as well as {a mathematical formula}z2 and {a mathematical formula}z3, meaning that also {a mathematical formula}(x1,x3),(z2,z3)∈RG. For symmetry reasons {a mathematical formula}{(xi,xj),(xj,xi),(yi,yj),(yj,yi)|i∈{1,2,3},j∈{4,5,6}}∪{(xs(i),xi),(zi,zs(i))|i∈{1,2…6}}⊆RG.We take a look at {a mathematical formula}S2 and more specifically {a mathematical formula}{x1,y2,z3}∈S2. As there should be an explicit conflict between {a mathematical formula}x1 and {a mathematical formula}x2 with only {a mathematical formula}x1 possibly defending this extension against {a mathematical formula}x2 we need {a mathematical formula}(x1,x2)∈RG. Further as in this set only {a mathematical formula}y2 and {a mathematical formula}z3 can possibly attack {a mathematical formula}z2 we have the set {a mathematical formula}{y2,z3} attacking {a mathematical formula}z2. For symmetry reasons {a mathematical formula}{(xi,xs(i)),(yi,ys(i))|i∈{1,2…6}}⊆RG and each set {a mathematical formula}{xi,zs(i)},{yi,zs(i)} for {a mathematical formula}i∈{1,2…6} attacks {a mathematical formula}zi.Finally we take a look at {a mathematical formula}S0 and more specifically the set {a mathematical formula}S={x1,y4,z2,z5}∈S0. Since S necessarily is an admissible extension in an analytic af we have that S attacks all rejected arguments. By the above observations we now have that S even attacks all arguments not being member of S in G, which means that S is a stable extension and stable semantics and semi-stable semantics thus coincide on G. But then, with {a mathematical formula}T={x1,y1,z2}∈S1 not being in conflict with for instance {a mathematical formula}z4 we have that T can not be a stable or semi-stable extension in G. We finally conclude that indeed {a mathematical formula}prf(F)∉Σsemx and thus {a mathematical formula}Σsemx⊂Σprfx. □
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Compact signatures
      </section-title>
      <paragraph>
       We now turn to the issue of realizing extension-sets without the use of rejected arguments.
      </paragraph>
      <paragraph label="Definition 11">
       An extension-set {a mathematical formula}S is called compactly realizable under semantics σ if there is some compact af{a mathematical formula}F∈CAFσ with {a mathematical formula}σ(F)=S. The compact signature (c-signature){a mathematical formula}Σσc of semantics σ consists of all extension-sets that are compactly realizable under σ:{a mathematical formula}
      </paragraph>
      <paragraph>
       It is clear that {a mathematical formula}Σσc⊆Σσ holds for any semantics. The following theorem repeats the equality of compact and general signatures for naive semantics discussed in the introduction, and shows a ⊂-relation for all other semantics.
      </paragraph>
      <paragraph label="Proposition 35">
       It holds that
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Σnaic=Σnai, and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Σσc⊂Σσfor{a mathematical formula}σ∈{stb,stg,sem,prf}.
       </list-item>
      </list>
      <paragraph label="Proof">
       nai: Consider some {a mathematical formula}S∈Σnai with F being the af realizing {a mathematical formula}S under naive semantics. It holds that an argument is contained in {a mathematical formula}ArgsS iff it is not self-attacking. Moreover removing any self-attacking argument together with its associated attacks has no effect on the naive extensions. Hence the af{a mathematical formula}F′ obtained from removing all self-attacking arguments together with their associated attacks has {a mathematical formula}nai(F′)=S and {a mathematical formula}F′∈CAFnai, therefore {a mathematical formula}Σnaic=Σnai.By definition we have {a mathematical formula}Σσc⊆Σσ. It remains to show that {a mathematical formula}Σσc≠Σσ for {a mathematical formula}σ∈{stb,stg,sem,prf}.{a mathematical formula}stb,stg: Consider the extension-set {a mathematical formula}S={{a,b,c}, {a mathematical formula}{a,b,c′}, {a mathematical formula}{a,b′,c}, {a mathematical formula}{a,b′,c′}, {a mathematical formula}{a′,b,c}, {a mathematical formula}{a′,b,c′}, {a mathematical formula}{a′,b′,c}} from the example in the introduction. We have seen that {a mathematical formula}S is realized under stb and stg by the af{a mathematical formula}F1 from the introduction. Assume there is an af{a mathematical formula}F=(ArgsS,R) realizing {a mathematical formula}S under stb or stg. Inspecting {a mathematical formula}PairsS we infer that {a mathematical formula}R⊆{(a,a′),(a′,a),(b,b′),(b′,b),(c,c′),(c′,c)}. Note that, for any remaining choice of R, {a mathematical formula}stb(F)=stg(F). Now for {a mathematical formula}{a,b,c}∈stb(F) we need {a mathematical formula}(a,a′),(b,b′),(c,c′)∈R. On the other hand, for {a mathematical formula}{a′,b,c},{a,b′,c},{a,b,c′}∈stb(F) we need {a mathematical formula}(a′,a),(b′,b),(c′,c)∈R. But then also {a mathematical formula}{a′,b′,c′}∈stb(F). Hence {a mathematical formula}S∉Σstbc and also {a mathematical formula}S∉Σstgc, witnessing {a mathematical formula}Σstbc⊂Σstb and {a mathematical formula}Σstgc⊂Σstg.{a mathematical formula}prf,sem: Let {a mathematical formula}σ∈{prf,sem} and consider {a mathematical formula}S={{a,b}, {a mathematical formula}{a,d,e}, {a mathematical formula}{b,c,e}}. {a mathematical formula}S∈Σσ holds since Fig. 3 shows an af (with additional arguments) realizing {a mathematical formula}S as its semi-stable and preferred extensions. Now suppose there exists an af{a mathematical formula}F=(ArgsS,R) such that {a mathematical formula}σ(F)=S. Since {a mathematical formula}{a,d,e},{b,c,e}∈S, it is clear that R must not contain an edge involving e. But then, e is contained in each {a mathematical formula}E∈σ(F). It follows that {a mathematical formula}σ(F)≠S and therefore {a mathematical formula}S∉Σσc. □
      </paragraph>
      <paragraph>
       In the following we relate the compact signatures of the semantics under consideration to each other. Recall that for general signatures it holds that {a mathematical formula}Σnai⊂Σstg=(Σstb∖{∅})⊂Σsem=Σprf[23]. Similarly, but not equivalently though, we have {a mathematical formula}Σnaix⊂Σstgx=(Σstbx∖{∅})⊂Σsemx⊂Σprfx for analytic signatures (cf. Theorem 34). This picture changes when considering the relationships between compact signatures. Fig. 21 depicts the relations between compact signatures which we will show in the next theorem. The dashed areas represent particular intersections for which the question of existence of extension-sets has to be left open. Also notice that stable semantics cannot realize the empty extension set within compact afs.
      </paragraph>
      <paragraph label="Theorem 36">
       In accordance withFig. 21, it holds that:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Σnaic⊂Σσcfor{a mathematical formula}σ∈{stb,stg,sem,prf};
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Σstbc⊂Σσcfor{a mathematical formula}σ∈{stg,sem};
       </list-item>
       <list-item label="3.">
        {a mathematical formula}Σprfc∖(Σstbc∪Σsemc∪Σstgc)≠∅;
       </list-item>
       <list-item label="4.">
        {a mathematical formula}Σstgc∖(Σstbc∪Σprfc∪Σsemc)≠∅;
       </list-item>
       <list-item label="5.">
        {a mathematical formula}Σstbc∖Σprfc≠∅;
       </list-item>
       <list-item label="6.">
        {a mathematical formula}(Σprfc∩Σsemc)∖(Σstbc∪Σstgc)≠∅;
       </list-item>
       <list-item label="7.">
        {a mathematical formula}Σsemc∖(Σstbc∪Σprfc∪Σstgc)≠∅.
       </list-item>
      </list>
      <paragraph label="Proof">
       For (7) we will make use of the following lemma, which might be of interest on its own.Let{a mathematical formula}σ,τ∈{stb,prf,sem,stg}and{a mathematical formula}F,Gbe τ-compactafs such that{a mathematical formula}τ(F)∉Σσcand{a mathematical formula}AF∩AG=∅. It holds that{a mathematical formula}τ(F∪G)∉Σσc.Assume there is some compact afH such that {a mathematical formula}σ(H)=τ(F∪G). Since {a mathematical formula}AF∩AG=∅, it follows that {a mathematical formula}τ(F∪G)=τ(F)×τ(G). Due to compactness every argument {a mathematical formula}a∈AF occurs together with every argument {a mathematical formula}b∈AG in some τ-extension of {a mathematical formula}F∪G, meaning that H cannot contain any attack between a and b. Hence {a mathematical formula}σ(H)=σ(H1)×σ(H2) with {a mathematical formula}AH1=AF and {a mathematical formula}AH2=AG. Therefore it must hold that {a mathematical formula}σ(H1)=τ(F), a contradiction to the assumption that {a mathematical formula}τ(F)∉Σσc. □Now we get (7) {a mathematical formula}Σsemc∖(Σstbc∪Σprfc∪Σstgc)≠∅ as follows: Let {a mathematical formula}F=F1∪F2 where {a mathematical formula}F1 is the af in Fig. 24 and {a mathematical formula}F2 is the af in Fig. 25 (observe that for {a mathematical formula}AF1∩AF2=∅ some renaming is necessary). From {a mathematical formula}sem(F1)∉Σprfc (see Example 10) we get {a mathematical formula}sem(F)=(sem(F1)×sem(F2))∉Σprfc by Lemma 37. In the same way {a mathematical formula}sem(F)∉Σstbc∪Σstgc follows from {a mathematical formula}sem(F2)∉Σstbc∪Σstgc (see Example 11).This concludes the proof of Theorem 36.
      </paragraph>
      <paragraph>
       Comparing the insights obtained from Theorem 36 with the results on expressiveness of semantics in [23] we observe notable differences depending on whether rejected arguments are allowed or not. When allowing rejected arguments (as utilized in [23]), preferred and semi-stable semantics are equally expressive and at the same time strictly more expressive than stable and stage semantics. As we have seen, this does not carry over to the compact setting where, with the exception of {a mathematical formula}Σstbc⊂Σsemc and {a mathematical formula}Σstbc⊂Σstgc, signatures become incomparable.
      </paragraph>
      <paragraph>
       What remains an open issue is the existence of extension-sets lying in the intersection between {a mathematical formula}Σprfc (resp. {a mathematical formula}Σsemc) and {a mathematical formula}Σstgc but outside of {a mathematical formula}Σstbc (see Venn-diagram in Fig. 21). We approach this issue in the remainder of this section.
      </paragraph>
      <paragraph label="Lemma 38">
       In self-attack freeafs every stage extension that is admissible is also stable.
      </paragraph>
      <paragraph label="Proof">
       Take some af{a mathematical formula}F=(A,R), and some admissible stage extension S, {a mathematical formula}S∈stg(F), {a mathematical formula}S∈adm(F) as given. Suppose there is some argument that is not in the range of S, i.e. {a mathematical formula}a∈A∖SF+. Then by admissibility a cannot attack S, by assumption S does not attack a. Consider that any stage extension is maximal conflict-free, thus for {a mathematical formula}a∉S we in fact would need {a mathematical formula}(a,a)∈R. It follows that there is no such argument a and thus {a mathematical formula}SF+=A. Hence {a mathematical formula}S∈stb(F). □
      </paragraph>
      <paragraph label="Proposition 39">
       Let{a mathematical formula}σ∈{sem,prf}and{a mathematical formula}F,Gbe σ-compactafs such that{a mathematical formula}stg(F)=σ(G). If{a mathematical formula}stg(F)∉Σstbcthen
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}F≠G, and
       </list-item>
       <list-item label="2.">
        G is non-analytic for σ.
       </list-item>
      </list>
      <paragraph label="Proof">
       Assume that {a mathematical formula}F=G. But then, as by assumption {a mathematical formula}stg(F)=σ(F), by Lemma 38 also {a mathematical formula}σ(F)=stb(F), a contradiction to the assumption that {a mathematical formula}stg(F)∉Σstbc. Therefore {a mathematical formula}F≠G.For a contradiction, wlog. assume G to be σ-analytic (for any quasi-analytic H there is some corresponding analytic G). Observe that for stage extensions {a mathematical formula}S∈stg(F) and any argument {a mathematical formula}a∈A∖S it holds that either there is an explicit conflict between S and a in F, or a is self-attacking in F, for otherwise {a mathematical formula}SF+ would not be maximal. With {a mathematical formula}stg(F)=σ(G) and G being analytic for the admissibility based semantics σ this means that {a mathematical formula}S↣Ga, i.e. {a mathematical formula}SG+=A. With all σ-extensions becoming stb-extensions and the fact that {a mathematical formula}stb(F)⊆σ(F) for any F, we derive a contradiction to the initial statement: {a mathematical formula}stb(G)=stg(F). □
      </paragraph>
      <paragraph>
       Assume that for {a mathematical formula}σ∈{prf,stg} there exists an extension-set {a mathematical formula}S∈(Σσc∩Σstgc)∖Σstbc. Now Proposition 39 says that {a mathematical formula}S is compactly realized by different afs under σ and stg, i.e. {a mathematical formula}stg(F)=S and {a mathematical formula}σ(G)=S with {a mathematical formula}F≠G. Moreover, G is non-analytic. Recent investigations encourage us to conjecture that such extension-sets do not exist (we already know that {a mathematical formula}Σstbc⊆Σsemc∩Σstgc (cf. Theorem 36.2) and {a mathematical formula}Σstbc∖Σprfc≠∅ (cf. Theorem 36.5) hold):
      </paragraph>
      <paragraph>
       Conjecture.It holds that{a mathematical formula}Σprfc∩Σstgc⊂Σstbcand{a mathematical formula}Σsemc∩Σstgc=Σstbc.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Numbers of extensions in compact frameworks
      </section-title>
      <paragraph>
       In the previous section we have related the semantics under consideration with respect to their capabilities in compactly realizing extension-sets. The concrete problem which was tackled in [23] is deciding, given an extension-set {a mathematical formula}S, whether {a mathematical formula}S is realizable. For compact realizability this is, in general, a hard problem; that is, we have no reason to believe that we can do any better than guessing a compact af and checking whether its extension-set coincides with {a mathematical formula}S. Nevertheless, in this section we provide a number of shortcuts to detect non-compactness. By “shortcut”, we mean a property of the given extension-set {a mathematical formula}S that is easily computable (preferably in polynomial time) and lets us (sometimes) give a definitive answer to the decision problem. These shortcuts are related to numerical aspects of argumentation frameworks, some of which have been studied in graph theory.
      </paragraph>
      <paragraph>
       Among the most basic properties that are necessary for compact realizability, we find numerical aspects like possible cardinalities of σ-extension-sets.
      </paragraph>
      <paragraph label="Example 12">
       Consider the following af{a mathematical formula}F2:{a mathematical formula} Let us determine the stable extensions of {a mathematical formula}F2. Clearly, taking one {a mathematical formula}ai, one {a mathematical formula}bi and one {a mathematical formula}ci yields a conflict-free set that is also stable as long as it attacks z. Thus from the {a mathematical formula}3⋅2⋅3=18 combinations, only one (the set {a mathematical formula}{a1,b1,c2}) is not stable, whence {a mathematical formula}F2 has {a mathematical formula}18−1=17 stable extensions. We note that this af is not compact since z occurs in none of the extensions. Is there an equivalent stb-compact af? The results of this section will provide us with a negative answer.   ◊
      </paragraph>
      <paragraph label="Theorem 40">
       Baumann and Strass [8] have shown that there is a correspondence between the maximal number of stable extensions in argumentation frameworks and the maximal number of maximal independent sets in undirected graphs [33]. Recently, the result was generalized to further semantics [23, Proposition 11 and Theorem 5].{sup:8} To set the scene for the subsequent results building upon it, we recall the result below (Theorem 40). For any natural number n we define{sup:9}:{a mathematical formula}{a mathematical formula}σmax(n) returns the maximal number of σ-extensions among all AFs with n arguments. Surprisingly, there is a closed expression for {a mathematical formula}σmax. The function{a mathematical formula}σmax(n):N→Nis given by{a mathematical formula}
      </paragraph>
      <paragraph>
       What about the maximal number of σ-extensions on weakly connected{sup:10} graphs? Does this number coincide with {a mathematical formula}σmax(n)? The next theorem provides a negative answer to this question and thus gives space for impossibility results as we will see. For a natural number n define{a mathematical formula}{a mathematical formula}σmaxcon(n) returns the maximal number of σ-extensions among all connected AFs with n arguments. Again, a closed expression exists.
      </paragraph>
      <paragraph label="Theorem 41">
       The function{a mathematical formula}σmaxcon(n):N→Nis given by{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       First some notations: for an af{a mathematical formula}F=(A,R), denote its irreflexive version by{a mathematical formula} denote its symmetric version by{a mathematical formula} and its associated undirected graph by{a mathematical formula}Furthermore, for a simple and undirected graph {a mathematical formula}G=(V,E) we use {a mathematical formula}MIS(G) for the set of maximal independent sets of G. Remember, a set {a mathematical formula}S⊆V is called independent if no edge {a mathematical formula}e∈E has both its endpoints in S. Moreover, an independent set S is called maximal independent if it is ⊆-maximal among the independent sets of G. Finally, we denote its associated symmetric af by{a mathematical formula}Now for the proof. We start with showing that the number of naive extensions does not exceed the claimed value range of {a mathematical formula}σmaxcon(n). Given a connected afF. Observe that the deletion of self-loops does not reduce the number of naive extensions, i.e. {a mathematical formula}|nai(F)|≤|nai(irr(F))|. This can be seen as follows. First, for any {a mathematical formula}E∈nai(F) exists an {a mathematical formula}E′∈nai(irr(F)), such that {a mathematical formula}E⊆E′ and second, for each two {a mathematical formula}E1,E2∈nai(F) there is no {a mathematical formula}E′∈nai(irr(F)), such that {a mathematical formula}E1⊆E′ and {a mathematical formula}E2⊆E′ simultaneously. Furthermore, it is easy to see that for any irreflexive afG, {a mathematical formula}nai(G)=MIS(und(G)). Roughly speaking, this is due to the fact that first, both concepts call for ⊆-maximal sets and second, naive semantics does not distinguish between the presence of an attack {a mathematical formula}(a,b) or the presence of {a mathematical formula}(b,a) or the presence of both of them. Consequently, {a mathematical formula}|nai(F)|≤|MIS(und(irr(F)))|. Fortunately, due to Theorem 2 in [30] the maximal number of maximal independent sets in connected n-graphs are exactly given by the claimed value range of {a mathematical formula}σmaxcon(n).We proceed with arguing that the maximal number of stable extensions within the class of connected afs is at least as large as the claimed value range of {a mathematical formula}σmaxcon(n). In Figure 1 in [30] graphs realizing the maximal number of maximal independent sets for connected n-graphs are presented. These so-called extremal graphs can be used to derive afs where former maximal independent sets become stable extensions. This can be done by replacing undirected edges by symmetric directed attacks. This construction is justified by the fact that for any simple graph G, {a mathematical formula}|MIS(G)|=|nai(dir(G))| and furthermore, as shown in [14, Propositions 4 and 5] naive and stable semantics coincide on the class of irreflexive and symmetric afs. Example 13 below provides an illustration.In order to conclude the proof we use well-known subset-relations between the considered semantics (compare Section 2). Since {a mathematical formula}stb(F)⊆stg(F)⊆nai(F) for any afF, we derive that {a mathematical formula}|stb(F)|≤|stg(F)|≤|nai(F)|. Furthermore, we have already shown that first, {a mathematical formula}σmaxcon(n) does not exceed the claimed value range in case of naive semantics and second, {a mathematical formula}σmaxcon(n) is at least as great as the claimed value range in case of stable semantics. Consequently, the stated equality provides us with a tight upper bound for stable, stage and naive semantics. What about semi-stable and preferred semantics? Since the result is already shown for stable semantics and in consideration of {a mathematical formula}stb(F)⊆sem(F)⊆prf(F) for any afF, it suffices to prove that {a mathematical formula}σmaxcon(n) does not exceed the claimed value range in case of preferred semantics. This can be seen as follows. First, one may easily verify that for any afF we have, {a mathematical formula}|prf(F)|≤|prf(irr(F))| as well as {a mathematical formula}prf(F)⊆prf(sym(F)). Hence, {a mathematical formula}|prf(F)|≤|prf(sym(irr(F)))|. In [2, Corollary 1] it was already shown that preferred and stable semantics agree on irreflexive and symmetric afs, i.e. for any afF, {a mathematical formula}prf(sym(irr(F)))=stb(sym(irr(F))). In summary, for any afF we have, {a mathematical formula}|prf(F)|≤|stb(sym(irr(F)))|. Assuming the existence of an afF possessing more preferred extension than the claimed value range of {a mathematical formula}σmaxcon(n) implies the existence of an witnessing af, namely {a mathematical formula}sym(irr(F)), possessing more stable extension than the claimed value range of {a mathematical formula}σmaxcon(n) in contrast to the already shown upper bound. Hence, the stated value range of {a mathematical formula}σmaxcon(n) serves as a tight upper bound for semi-stable and preferred semantics too. □
      </paragraph>
      <paragraph>
       The following illustration provides an example how connected afs having the maximal number of σ-extensions look like.
      </paragraph>
      <paragraph label="Example 13">
       Consider the following afG:{a mathematical formula} The afG is connected and possesses 22 σ-extensions. More precisely:{a mathematical formula} This justifies {a mathematical formula}|σ(G)|=27−5=22. Furthermore, G consists of 9 arguments. Applying Theorem 41 we obtain {a mathematical formula}σmaxcon(n)=2⋅33−1+23−1=2⋅32+22=18+4=22. This means, G is an extremal af within the class of connected graphs. As an aside, in case of arbitrary frameworks, the maximal number of stable extensions given n arguments can be realized by deleting the mutual attacks between {a mathematical formula}a3 and {a mathematical formula}b3 as well as {a mathematical formula}b3 and {a mathematical formula}c3 (cf. Theorem 40). Restoring mutual attacks between one pair only yields the second largest number, which will be proven in Theorem 42.   ◊
      </paragraph>
      <paragraph>
       A further interesting question concerning arbitrary afs is whether all natural numbers less than {a mathematical formula}σmax(n) are realizable by afs possessing n arguments.{sup:11} The following theorem shows that there is a serious gap between the maximal and second largest number. For any positive natural n define{a mathematical formula}{a mathematical formula}σ2nd(n) returns the second largest number of σ-extensions among all AFs with n arguments. Graph theory provides us with an expression.
      </paragraph>
      <paragraph label="Theorem 42">
       Function{a mathematical formula}σ2nd(n):N∖{0}→Nis given by{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       At first we argue that the second largest number of σ-extensions is at least as large as the claimed value range of {a mathematical formula}σ2nd(n). For this it suffices to present witnessing afs. In [31, Theorem 2.4] graphs realizing the second largest number of maximal independent sets for n-graphs are given. These simple graphs can be used to derive afs where former maximal independent sets become σ-extensions. Replacing undirected edges by symmetric directed attacks accounts for this. This can be seen as follows. First, for any simple graph G, {a mathematical formula}|MIS(G)|=|nai(dir(G))|. Second, for any irreflexive and symmetric afF we have, {a mathematical formula}stb(F)=nai(F)[14, Propositions 4 and 5] and finally, applying well-known subset-relations, namely {a mathematical formula}stb(F)⊆sem(F)⊆prf(F) and {a mathematical formula}stb(F)⊆stg(F) (for any afF) justifies the claim for all considered semantics.We show now that the second largest number of σ-extensions does not exceed the claimed value range of {a mathematical formula}σ2nd(n). Given an afF where {a mathematical formula}|AF|=n. Observe that we have nothing to show if {a mathematical formula}n≤7 since {a mathematical formula}σ2nd(n) is given as the maximal number minus one. Let {a mathematical formula}n≥8 and suppose, towards a contradiction, that {a mathematical formula}l⋅σmax(n)&lt;σ2nd(n)=|σ(F)|&lt;σmax(n) where l depends on the remainder of n on division by 3 ({a mathematical formula}l∈{1112,89}). Similar to the proof of Theorem 41 one may easily show that for all considered semantics σ, {a mathematical formula}|σ(F)|≤|σ(sym(irr(F)))| as well as that for any symmetric and irreflexive G, {a mathematical formula}σ(F)=MIS(und(G)). This means, {a mathematical formula}l⋅σmax(n)&lt;|σ(F)|≤|MIS(und(sym(irr(F))))|≤σmax(n). We further conclude that {a mathematical formula}|MIS(und(sym(irr(F))))|=σmax(n). This equality has to hold because the term {a mathematical formula}l⋅σmax(n) as well as the value range of {a mathematical formula}σmax(n) precisely coincide with the second largest or maximal number of maximal independent sets in simple graphs [31], [33]. This means, {a mathematical formula}l⋅σmax(n)&lt;|MIS(und(sym(irr(F))))|&lt;σmax(n) would contradict the second largest number of maximal independent sets. Note that up to isomorphisms the extremal graphs are uniquely determined (cf. Theorem 1 in [30]). In the following we use {a mathematical formula}Kn to denote a complete graph on n vertices. Depending on the remainder of n on division by 3 we have {a mathematical formula}K3s for {a mathematical formula}n≡0, either one {a mathematical formula}K4 or two {a mathematical formula}K2s and the rest are {a mathematical formula}K3s in case of {a mathematical formula}n≡1 and one {a mathematical formula}K2 plus {a mathematical formula}K3s for {a mathematical formula}n≡2. Remember that we have {a mathematical formula}|σ(F)|&lt;|σ(sym(irr(F)))|=σmax(n). In particular, this means {a mathematical formula}F≠sym(irr(F)). Consequently, depending on the remainder we may thus estimate {a mathematical formula}|σ(F)|≤k⋅σmax(n) where {a mathematical formula}k∈{23,34,12}. This can be seen as follows: First, computing the σ-extensions of an af can be reduced to computing the σ-extensions of each of its component (see Lemma 46) and second, the minimal factors decreasing the number of σ-extension (through adding self-loops or deleting attacks) within a component where {a mathematical formula}3,4 or 2 arguments attack each other are {a mathematical formula}23, {a mathematical formula}34 or {a mathematical formula}12, respectively. We finally state {a mathematical formula}l⋅σmax(n)&lt;|σ(F)|≤k⋅σmax(n) where {a mathematical formula}l∈{1112,89} and {a mathematical formula}k∈{23,34,12}. This is a clear contradiction concluding the proof. □
      </paragraph>
      <paragraph>
       The attentive reader might have noticed that all maximal number functions introduced in this subsection refer to arbitrary argumentation frameworks instead of compact ones. The following theorem shows that this is not incidental since the compact versions of these functions return the same values (provided that they are defined). We first introduce the corresponding functions:{a mathematical formula}
      </paragraph>
      <paragraph label="Theorem 43">
       For any{a mathematical formula}n∈N,{a mathematical formula}σmaxc(n)=σmax(n)and{a mathematical formula}σmaxc,con(n)=σmaxcon(n). Furthermore, for any{a mathematical formula}n∈N∖{0,1},{a mathematical formula}σ2ndc(n)=σ2nd(n).
      </paragraph>
      <paragraph label="Proof">
       (sketch) Given {a mathematical formula}n∈N as claimed above.(≤) Obviously, {a mathematical formula}σmaxc(n)≤σmax(n), {a mathematical formula}σmaxc,con(n)≤σmaxcon(n) and {a mathematical formula}σ2ndc(n)≤σ2nd(n) since {a mathematical formula}CAFσ⊆AFA.(≥) Inspecting the proofs of Theorem 40, Theorem 41, Theorem 42 (respective the proofs of the mentioned references therein) reveals that the witnessing examples, i.e. the afs realizing a certain maximal number are already compact. □
      </paragraph>
      <paragraph>
       From now on we implicitly presuppose that the introduced maximal number functions restricted to compact frameworks coincide with their unrestricted versions.
      </paragraph>
      <paragraph label="Example 14">
       Recall that the (non-compact) af we discussed in Example 12 had the extension-set {a mathematical formula}S with {a mathematical formula}|S|=17 and {a mathematical formula}|ArgsS|=8. Is there a stable-compact af with the same extensions? Firstly, nothing definitive can be said by Theorem 40 since {a mathematical formula}17≤18=σmax(8). Furthermore, in accordance with Theorem 41 the set {a mathematical formula}S cannot be compactly σ-realized by a connected af since {a mathematical formula}17&gt;15=σmaxcon(8). Finally, using Theorem 42 we infer that the set {a mathematical formula}S is not compactly σ-realizable because {a mathematical formula}σ2nd(8)=16&lt;17&lt;18=σmax(8).   ◊
      </paragraph>
      <paragraph>
       The compactness property is instrumental here, since Theorem 42 has no counterpart in non-compact afs. More generally, allowing additional arguments as long as they do not occur in extensions enables us to realize any number of stable extensions up to the maximal one.
      </paragraph>
      <paragraph label="Proposition 44">
       Let n be a natural number. For each{a mathematical formula}k≤σmax(n), there is anafF with{a mathematical formula}|Argsstb(F)|=nand{a mathematical formula}|stb(F)|=k.
      </paragraph>
      <paragraph label="Proof">
       To realize k stable extensions with n arguments, we start with the construction for the maximal number from Theorem 40. We then subtract extensions as follows: We choose {a mathematical formula}σmax(n)−k arbitrary distinct stable extensions of the af realizing the maximal number. To exclude them, we use the construction of Definition 9 in [23]. □
      </paragraph>
      <paragraph label="Corollary 45">
       Let n be a natural number and σ among preferred, semi-stable and stage semantics. For each{a mathematical formula}k≤σmax(n), there is anafF with{a mathematical formula}|Argsσ(F)|=nand{a mathematical formula}σ(F)=k.
      </paragraph>
      <paragraph label="Proof">
       Follows from Lemmata 2.2 and 4.2 in [23]. □
      </paragraph>
      <paragraph>
       Now we are prepared to provide possible short cuts when deciding realizability of a given extension-set by initially simply counting the extensions. First some formal definitions.
      </paragraph>
      <paragraph label="Definition 12">
       Given an af{a mathematical formula}F=(A,R), the component-structure {a mathematical formula}K(F)={K1,…,Kn} of F is the set of sets of arguments, where each {a mathematical formula}Ki coincides with the arguments of a weakly connected component of the underlying graph; {a mathematical formula}K≥2(F)={K∈K(F)‖K|≥2}.
      </paragraph>
      <paragraph label="Example 15">
       The af{a mathematical formula}F=({a,b,c},{(a,b)}) has component-structure {a mathematical formula}K(F)={{a,b},{c}}.   ◊
      </paragraph>
      <paragraph>
       The component-structure {a mathematical formula}K(F) gives information about the number n of components of F as well as the size {a mathematical formula}|Ki| of each component. Knowing the components of an af, computing the σ-extensions can be reduced to computing the σ-extensions of each component and building the cross-product. The af resulting from restricting F to component {a mathematical formula}Ki is given by {a mathematical formula}F↓Ki=(Ki,RF∩Ki×Ki).
      </paragraph>
      <paragraph label="Lemma 46">
       Given anafF with component-structure{a mathematical formula}K(F)={K1,…,Kn}it holds that the extensions in{a mathematical formula}σ(F)and the tuples in{a mathematical formula}σ(F↓K1)×⋯×σ(F↓Kn)are in one-to-one correspondence.
      </paragraph>
      <paragraph label="Proof">
       By induction on n; the base case {a mathematical formula}n=1 is trivial. For the induction step let {a mathematical formula}K(F)={K1,…,Kn,Kn+1}.“⊆”: Let {a mathematical formula}S∈σ(F). Define {a mathematical formula}Dn+1=S∩Kn+1. By induction hypothesis, there are sets {a mathematical formula}D1,…,Dn such that each {a mathematical formula}Di is a σ-extension of {a mathematical formula}F↓Ki and {a mathematical formula}S∖Kn+1=D1∪⋯∪Dn. We have to show that {a mathematical formula}Dn+1 is a σ-extension of {a mathematical formula}F↓Kn+1. {a mathematical formula}σ=stb: Clearly {a mathematical formula}Dn+1 is conflict-free, and any {a mathematical formula}a∈Kn+1∖Dn+1 is attacked since S is stable and the attacks must come from {a mathematical formula}Dn+1 due to connectivity. {a mathematical formula}σ∈{nai,prf}: If there is a conflict-free/admissible superset of {a mathematical formula}Dn+1, then S is not naive/preferred for F. {a mathematical formula}σ∈{stg,sem}: If there is a superset of {a mathematical formula}Dn+1 with greater range, then S is not stage/semi-stable for F.“⊇”: Let {a mathematical formula}D1,…,Dn,Dn+1 such that each {a mathematical formula}Di is a σ-extension of {a mathematical formula}F↓Ki. Define {a mathematical formula}S=D1∪⋯∪Dn∪Dn+1; we show that {a mathematical formula}S∈σ(F). By induction hypothesis, {a mathematical formula}D1∪⋯∪Dn∈σ(F↓K1,…,Kn). {a mathematical formula}σ=stb: Clearly S is conflict-free since all {a mathematical formula}Di are conflict-free; since {a mathematical formula}Dn+1 is stable for {a mathematical formula}F↓Kn+1 it attacks all {a mathematical formula}a∈Kn+1∖Dn+1 and thus S is stable for F. {a mathematical formula}σ∈{nai,prf}: If S is not naive/preferred for F, there is a conflict-free/admissible superset of S in F. There is at least one additional argument, that is either in {a mathematical formula}D1∪⋯∪Dn or in {a mathematical formula}Dn+1. But the first is impossible due to induction hypothesis, and the second due to presumption. {a mathematical formula}σ∈{stg,sem}: If S is not stage/semi-stable for F, there is a conflict-free/admissible set {a mathematical formula}S′ with greater range. The range difference must manifest itself in {a mathematical formula}D1∪⋯∪Dn or {a mathematical formula}Dn+1, which leads to a contradiction with the induction hypothesis and the presumption that {a mathematical formula}Dn+1 is stage/semi-stable for {a mathematical formula}F↓Kn+1. □
      </paragraph>
      <paragraph>
       Given an extension-set {a mathematical formula}S we want to decide whether {a mathematical formula}S is realizable by a compact af under semantics σ. For an af{a mathematical formula}F=(A,R) with {a mathematical formula}σ(F)=S we know that there cannot be a conflict between any pair of arguments in {a mathematical formula}PairsS, hence {a mathematical formula}R⊆PairsS‾=(A×A)∖PairsS. The next proposition implicitly shows that for argument-pairs {a mathematical formula}(a,b)∉PairsS, although there is not necessarily a direct conflict between a and b, they are definitely in the same component. In other words, this shows that implicit conflicts cannot arise across (weakly connected) components but only within them.
      </paragraph>
      <paragraph label="Proposition 47">
       Let{a mathematical formula}Sbe an extension-set. (1) The transitive closure of{a mathematical formula}PairsS‾, the set{a mathematical formula}(PairsS‾)⁎, is an equivalence relation, that is, it is reflexive, symmetric, and transitive. (2) For eachaf{a mathematical formula}F∈CAFσthat compactly realizes{a mathematical formula}Sunder semantics σ (that is,{a mathematical formula}σ(F)=S), the component structure{a mathematical formula}K(F)of F is given by the equivalence classes of{a mathematical formula}(PairsS‾)⁎, that is,{a mathematical formula}K(F)is the quotient set of{a mathematical formula}ArgsSby{a mathematical formula}(PairsS‾)⁎.
      </paragraph>
      <paragraph label="Proof">
       Consider some extension-set {a mathematical formula}S together with an af{a mathematical formula}F∈CAFσ with {a mathematical formula}σ(F)=S. We have to show that for any pair of arguments {a mathematical formula}a,b∈ArgsS it holds that {a mathematical formula}(a,b)∈(PairsS‾)⁎ iff a and b are connected in the graph underlying F.If a and b are connected in F, this means that there is a sequence {a mathematical formula}s1,…,sn such that {a mathematical formula}a=s1, {a mathematical formula}b=sn, and {a mathematical formula}(s1,s2),…,(sn−1,sn)∉PairsS, hence {a mathematical formula}(a,b)∈(PairsS‾)⁎.If {a mathematical formula}(a,b)∈(PairsS‾)⁎ then also there is a sequence {a mathematical formula}s1,…,sn such that {a mathematical formula}a=s1, {a mathematical formula}b=sn, and {a mathematical formula}(s1,s2),…,(sn−1,sn)∈PairsS‾. Consider some {a mathematical formula}(si,si+1)∈PairsS‾ and assume, towards a contradiction, that {a mathematical formula}si occurs in another component of F than {a mathematical formula}si+1. Recall that {a mathematical formula}F∈CAFσ, so each of {a mathematical formula}si and {a mathematical formula}si+1 occur in some extension and {a mathematical formula}σ(F)≠∅. Hence, by Lemma 46, there is some σ-extension {a mathematical formula}E⊇{si,si+1} of F, meaning that {a mathematical formula}(si,si+1)∈PairsS, a contradiction. Hence all {a mathematical formula}si and {a mathematical formula}si+1 for {a mathematical formula}1≤i&lt;n occur in the same component of F, proving that also a and b do so. □
      </paragraph>
      <paragraph>
       It is particularly nice to note that the only conditions we used in the proof were compactness and conflict-freeness, which indeed shows the Proposition for all five semantics considered here.
      </paragraph>
      <paragraph>
       We will denote the component-structure induced by an extension-set {a mathematical formula}S as {a mathematical formula}K(S), i.e. {a mathematical formula}K(S) is the quotient set of {a mathematical formula}ArgsS by {a mathematical formula}(PairsS‾)⁎. Note that, by Proposition 47, {a mathematical formula}K(S) is equivalent to {a mathematical formula}K(F) for every {a mathematical formula}F∈CAFσ with {a mathematical formula}σ(F)=S. Given {a mathematical formula}S, the computation of {a mathematical formula}K(S) can be done in polynomial time. With this we can use results from graph theory together with number-theoretical considerations in order to get impossibility results for compact realizability.
      </paragraph>
      <paragraph>
       Recall that for a single connected component with n arguments the maximal number of σ-extensions is denoted by {a mathematical formula}σmaxcon(n) and its values are given by Theorem 41. In the compact setting it further holds for a connected afF with at least 2 arguments that {a mathematical formula}|σ(F)|≥2.
      </paragraph>
      <paragraph label="Proposition 48">
       Given an extension-set{a mathematical formula}Swhere{a mathematical formula}|S|is odd, it holds that if{a mathematical formula}∃K∈K(S):|K|=2then{a mathematical formula}Sis not compactly realizable under semantics σ.
      </paragraph>
      <paragraph label="Proof">
       Assume to the contrary that there is an {a mathematical formula}F∈CAFσ with {a mathematical formula}σ(F)=S. We know that {a mathematical formula}K(F)=K(S). By assumption there is a {a mathematical formula}K∈K(S) with {a mathematical formula}|K|=2, whence {a mathematical formula}|σ(K)|=2. Thus by Lemma 46 the total number of σ-extensions is even. Contradiction. □
      </paragraph>
      <paragraph label="Example 16">
       Consider the extension-set {a mathematical formula}S={{a,b,c}, {a mathematical formula}{a,b′,c′}, {a mathematical formula}{a′,b,c′}, {a mathematical formula}{a′,b′,c}, {a mathematical formula}{a,b,c′}, {a mathematical formula}{a′,b,c}, {a mathematical formula}{a,b′,c}}=stb(F1) where {a mathematical formula}F1 is the non-compact af from the proof of Proposition 35. There, it took us some effort to argue that {a mathematical formula}S is not compactly stb-realizable. Proposition 48 now gives an easier justification: {a mathematical formula}PairsS yields {a mathematical formula}K(S)={{a,a′},{b,b′},{c,c′}}. Thus {a mathematical formula}S with {a mathematical formula}|S|=7 cannot be realized.   ◊
      </paragraph>
      <paragraph>
       We denote the set of possible numbers of σ-extensions of a compact af with n arguments as {a mathematical formula}P(n); likewise we denote the set of possible numbers of σ-extensions of a compact and connectedaf with n arguments as {a mathematical formula}Pc(n). Although we know that {a mathematical formula}p∈P(n) implies {a mathematical formula}p≤σmax(n), there may be {a mathematical formula}q≤σmax(n) that are not realizable by a compact af under σ; likewise for {a mathematical formula}q∈Pc(n).
      </paragraph>
      <paragraph>
       Clearly, any {a mathematical formula}p≤n is possible by building an undirected graph with p arguments where every argument attacks all other arguments, a {a mathematical formula}Kp, and filling up with k isolated arguments (k distinct copies of {a mathematical formula}K1) such that {a mathematical formula}k+p=n. This construction obviously breaks down if we want to realize more extensions than we have arguments, that is, {a mathematical formula}p&gt;n. In this case, we have to use Lemma 46 and further graph-theoretic gadgets for addition and even a limited form of subtraction. Let us show how for {a mathematical formula}n=7 any number of extensions up to the maximal number 12 is realizable. For {a mathematical formula}12=3⋅4, Theorem 40 yields the realization, a disjoint union of a {a mathematical formula}K3 and a {a mathematical formula}K4{a mathematical formula}({an inline-figure}). For the remaining numbers, we have that {a mathematical formula}8=2⋅4⋅1 and so we can combine a {a mathematical formula}K2, a {a mathematical formula}K4 and a {a mathematical formula}K1{a mathematical formula}({an inline-figure}). Likewise, {a mathematical formula}9=3⋅3⋅1 ({an inline-figure}); {a mathematical formula}10=3⋅3+1 ({an inline-figure}) and finally {a mathematical formula}11=3⋅4−1 ({an inline-figure}). These small examples already show that {a mathematical formula}P and {a mathematical formula}Pc are closely intertwined and let us deduce some general corollaries: Firstly, {a mathematical formula}Pc(n)⊆P(n) since connected afs are a subclass of afs. Next, {a mathematical formula}P(n)⊆P(n+1) as in the step from {an inline-figure} to {an inline-figure}. We even know that {a mathematical formula}P(n)⊂P(n+1) since {a mathematical formula}σmax(n+1)∈P(n+1)∖P(n). Furthermore, whenever {a mathematical formula}p∈P(n), then {a mathematical formula}p+1∈Pc(n+1), as in the step from {an inline-figure} to {an inline-figure}. The construction that goes from 12 to 11 above obviously only works if there are two weakly connected components overall, which underlines the importance of the component structure of the realizing af. Indeed, multiplication of extension numbers of single components is our only chance to achieve overall numbers that are substantially larger than the number of arguments. This is what we will turn to next.
      </paragraph>
      <paragraph>
       Having to leave the exact contents of {a mathematical formula}P(n) and {a mathematical formula}Pc(n) open, we can still state the following result:
      </paragraph>
      <paragraph label="Proposition 49">
       Let{a mathematical formula}Sbe an extension-set that is compactly realizable under semantics σ where{a mathematical formula}K≥2(S)={K1,…,Kn}. Then for each{a mathematical formula}1≤i≤nthere is a{a mathematical formula}pi∈Pc(|Ki|)such that{a mathematical formula}|S|=∏i=1npi.
      </paragraph>
      <paragraph label="Example 17">
       Consider the extension-set {a mathematical formula}S′={{a,b,c},{a,b′,c′}, {a mathematical formula}{a′,b,c′}, {a mathematical formula}{a′,b′,c}}. (In fact there exists a (non-compact) afF with {a mathematical formula}stb(F)=S′.) We have the same component-structure {a mathematical formula}K(S′)=K(S) as in Example 16, but since now {a mathematical formula}|S′|=4 we cannot use Proposition 48 to show impossibility of realization in terms of a compact af. But with Proposition 49 at hand we can argue in the following way: {a mathematical formula}Pc(2)={2} and since {a mathematical formula}∀K∈K(S′):|K|=2 it must hold that {a mathematical formula}|S|=2⋅2⋅2=8, which is obviously not the case.   ◊
      </paragraph>
      <paragraph>
       In particular, we have a straightforward non-realizability criterion whenever {a mathematical formula}|S| is a prime number: the af (if any) must have at most one weakly connected component of size greater than two. Theorem 41 gives us the maximal number of σ-extensions in a single weakly connected component. Thus whenever the number of desired extensions is larger than that number and prime, it cannot be realized.
      </paragraph>
      <paragraph label="Corollary 50">
       Let extension-set{a mathematical formula}Swith{a mathematical formula}|ArgsS|=nbe compactly realizable under σ. If{a mathematical formula}|S|is a prime number, then{a mathematical formula}|S|≤σmaxcon(n).
      </paragraph>
      <paragraph label="Example 18">
       Let {a mathematical formula}S be an extension-set with {a mathematical formula}|ArgsS|=9 and {a mathematical formula}|S|=23. We find that {a mathematical formula}σmaxcon(9)=2⋅32+22=22&lt;23=|S| and thus {a mathematical formula}S is not compactly realizable under semantics σ.   ◊
      </paragraph>
      <paragraph>
       We can also make use of the derived component structure of an extension-set {a mathematical formula}S. Since the total number of extensions of an af is the product of these numbers for its weakly connected components (Lemma 46), each non-trivial component contributes a non-trivial amount to the total. Hence if there are more components than the factorization of {a mathematical formula}|S| has primes in it, then {a mathematical formula}S cannot be realized.
      </paragraph>
      <paragraph label="Corollary 51">
       Let extension-set{a mathematical formula}Sbe compactly realizable under σ and let{a mathematical formula}f1z1⋅…⋅fmzmbe the integer factorization of{a mathematical formula}|S|, where{a mathematical formula}f1,…,fmare prime numbers. Then,{a mathematical formula}
      </paragraph>
      <paragraph label="Example 19">
       Consider an extension-set {a mathematical formula}S containing 21 extensions and {a mathematical formula}|K≥2(S)|=3. Since {a mathematical formula}21=31⁎71 and further {a mathematical formula}1+1&lt;3, {a mathematical formula}S is not compactly realizable under semantics σ.   ◊
      </paragraph>
      <paragraph>
       We conclude this section with a partial recipe for determining compact (non-)realizability. Given an extension-set {a mathematical formula}S, compute:
      </paragraph>
      <list>
       <list-item label="•">
        the number of extensions {a mathematical formula}k=|S|,
       </list-item>
       <list-item label="•">
        the number of arguments {a mathematical formula}n=|ArgsS|,
       </list-item>
       <list-item label="•">
        the component-structure {a mathematical formula}K(S), in particular the number of non-trivial components {a mathematical formula}c=K≥2(S),
       </list-item>
       <list-item label="•">
        the integer factorization of {a mathematical formula}k=f1z1⋅…⋅fmzm
       </list-item>
      </list>
      <paragraph>
       Towards deciding compact realizability, we can use the results of this section in the following way:
      </paragraph>
      <list>
       <list-item label="1.">
        If {a mathematical formula}σmax(n)&lt;k then {a mathematical formula}S is not compactly realizable.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}σ2nd(n)&lt;k&lt;σmax(n) then {a mathematical formula}S is not compactly realizable.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}c=1 and {a mathematical formula}σmaxcon(n)&lt;k then {a mathematical formula}S is not compactly realizable.
       </list-item>
       <list-item label="4.">
        If k is prime and {a mathematical formula}σmaxcon(n)&lt;k then {a mathematical formula}S is not compactly realizable.
       </list-item>
       <list-item label="5.">
        If k is odd and there is a {a mathematical formula}K∈K(S) with {a mathematical formula}|K|=2 then {a mathematical formula}S is not compactly realizable.
       </list-item>
       <list-item label="6.">
        If {a mathematical formula}z1+…+zm&lt;c then {a mathematical formula}S is not compactly realizable.
       </list-item>
      </list>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Implicit conflicts and runtime
     </section-title>
     <paragraph>
      This appendix reports the results of experiments carried out in order to understand the impact of implicit conflicts on the efficiency of solvers. The underlying assumption is that the explication of implicit conflicts leads to a more succinct representation of an af, which in turn supports the solver by providing more information to work with. The results for extension enumeration under stable and preferred semantics confirm this hypothesis.
     </paragraph>
     <paragraph>
      The First International Competition on Computational Models of Argumentation (ICCMA, see http://argumentationcompetition.org/2015/) featured three types of benchmark graphs, each following a certain graph model. The one which turned out to be the hardest for most solvers is based on a construction that aims at having many stable (and preferred) extensions.{sup:12} As the set containing the largest instances of this type even had to be removed from the competition due to its difficulty and therefore seems most interesting to analyze, we focus on this group of instances.{sup:13} For stable and preferred semantics we analyze the correlation between the number of implicit conflicts and the runtime of solving. We focus on the particular task of extension enumeration and employ the winning solvers of the competition, that is ASPARTIX [29] for stable semantics and CEGARTIX [27] for preferred semantics. We report statistics for the instances of the competition as well as for a larger set of instances constructed with the same generator to get results which are statistically more significant.
     </paragraph>
     <paragraph>
      Instances of the considered type usually feature many rejected arguments – the ICCMA-instances have an average of {a mathematical formula}78% for stable and {a mathematical formula}76% for preferred semantics. Therefore we only take into account implicit conflicts that occur between arguments that are not rejected. Hence, in this appendix, given an afF and semantics σ, there is an implicit conflict between arguments {a mathematical formula}a,b∈AF if {a mathematical formula}(a,b)∉Pairsσ(F), {a mathematical formula}(a,b),(b,a)∉RF and {a mathematical formula}a,b∈Argsσ(F). The σ-explication of F is then {a mathematical formula}(AF,RF∪{(a,b),(b,a)|implicit conflict between a and b}). Note that, in general, the explicated af is not equivalent w.r.t. σ to the original one. However, it is not a simplification in terms of extensions, as the number of extensions of the explicated af is always greater or equal than in the original af.
     </paragraph>
     <paragraph>
      The tests have been run on a machine with two AMD Opteron 6308 processors (3.5 GHz) having 2 physical cores each; each of these cores puts at disposal 2 logical cores (per hyperthreading), 192 GB RAM {a mathematical formula}(12×16 GB) and a timeout of 600 seconds for each instance.
     </paragraph>
     <paragraph>
      The experiments show a clear tendency to shorter runtime when decreasing the number of implicit conflicts. Fig. A.26 shows the experimental results for the ICCMA instances and Fig. A.27 for the generated instances. The correlation between implicit conflicts per non-rejected argument and runtime of solving turns out to be slightly greater for preferred semantics. Explication of implicit conflicts leads to a speedup in solving for both semantics, more significantly for stable though. Table A.3 shows a few more statistics for the generated instances. While the solvers have about four times as many timeouts for the original instances than for the explicated instances for both semantics, the number of instances which are solved faster is less significantly different for preferred semantics. The explanation is that, for preferred semantics, explication only pays off if the original af is sufficiently difficult to solve.
     </paragraph>
     <paragraph>
      In this appendix we have only considered implicit conflicts among non-rejected arguments. Dropping this constraint would have the following effects on the experiments: due to the already mentioned high number of rejected arguments (i) the size of explicated afs significantly increases, and (ii) the number of implicit conflicts mostly depends on the number of rejected arguments. The effect on the runtime for extension enumeration on these explicated instances strongly differs between stable and preferred semantics. We get runtime on a constantly low level (between one and two seconds) for stable semantics and runtimes significantly higher than on the original instances for preferred instances. While the former observation is somehow in accordance with [10] as discussed at the end of Section 4, we attribute the latter to the almost quadratic increase in instance size.
     </paragraph>
    </section>
    <section label="Appendix B">
     Proofs of Section 4
     <paragraph label="Proof of Lemma 19">
      Below we will show that all arguments except x are always credulously accepted in {a mathematical formula}F′ and that x is credulously accepted in {a mathematical formula}F′ iff x is credulously accepted in F.First we show that each semi-stable extension E contains at least one argument from {a mathematical formula}{ta|a∈A∪{y,z}}. Suppose that not, then {a mathematical formula}E∪{tx} is a conflict-free set and, as {a mathematical formula}tx defends itself against all its attackers, the set {a mathematical formula}E∪{tx} is also admissible. Hence we have a contradiction to the maximality of E. Further, as {a mathematical formula}{ta|a∈A∪{y,z}} forms a clique in F we get that each extension contains exactly one argument from the set.Next we show that the ranges of preferred extensions E containing an argument from {a mathematical formula}{ta|a∈{x,y,z}} cannot be contained in the ranges of admissible sets {a mathematical formula}E′ not containing any of these arguments.
      <list>
       If {a mathematical formula}tx∈E then {a mathematical formula}h2 is defended against all its attackers, that are {a mathematical formula}ty and {a mathematical formula}h1, and thus also {a mathematical formula}h2∈E. As {a mathematical formula}h1 is attacked by {a mathematical formula}tx and {a mathematical formula}h3 is attacked by {a mathematical formula}h2 we have {a mathematical formula}{h1,h2,h3}⊆EF′+. By similar arguments we get that {a mathematical formula}{h1,h2,h3}⊆EF′+ if either {a mathematical formula}ty∈E or {a mathematical formula}tz∈E.If {a mathematical formula}ta∈E′ with {a mathematical formula}a∉{x,y,z} then none of the {a mathematical formula}h1,h2,h3 can be in the range, as they form an odd length cycle and all attacking arguments from outside are counter attacked by {a mathematical formula}E′.Finally, combining the above results, we have that all arguments in
      </list>
      <paragraph>
       {a mathematical formula}A′ except x are credulously accepted in {a mathematical formula}F′ and x is credulously accepted in F iff x is credulously accepted in {a mathematical formula}F′ iff {a mathematical formula}F′ is stg-compact. □
      </paragraph>
     </paragraph>
     <paragraph label="Proof of Lemma 23">
      First, we show that each semi-stable extension E contains at least one argument from {a mathematical formula}A′. Suppose that not, then {a mathematical formula}E∖AG∪{t} is an admissible set that has {a mathematical formula}AG in its range. Hence we have a contradiction to the range maximality of E. Further, as {a mathematical formula}A′ forms a clique in F we get that each semi-stable extension contains exactly one argument from the set.Next we show that the ranges of preferred extensions E containing argument t cannot be contained in the ranges of admissible sets {a mathematical formula}E′ containing an argument {a mathematical formula}ta,b with {a mathematical formula}a,b∈A.
      <list>
       If {a mathematical formula}t∈E then all arguments in {a mathematical formula}AG are attacked by E and thus are in the range of E.If {a mathematical formula}t∉E′ at least one argument of {a mathematical formula}AG is not in the range of {a mathematical formula}E′. Otherwise, {a mathematical formula}E′∩AG would be a stable extension of G, which contradicts {a mathematical formula}stb(G)=∅.Combining the above results, we have that all non-conflicting pairs of arguments in
      </list>
      <paragraph>
       {a mathematical formula}F′ except {a mathematical formula}{t,a} with {a mathematical formula}a∈A are credulously accepted in {a mathematical formula}F′. Thus {a mathematical formula}F′ is stg-analytic iff all the pairs {a mathematical formula}{t,a} with {a mathematical formula}a∈A are credulously accepted in {a mathematical formula}F′ iff each {a mathematical formula}a∈A is credulously accepted in F iff F is sem-compact.Finally we show that {a mathematical formula}F′∈CAFsem (independent of whether {a mathematical formula}F∈CAFsem). As (i) for each {a mathematical formula}a∈A the set {a mathematical formula}{ta,a,a} is credulously accepted, and (ii) for each {a mathematical formula}g∈AG and {a mathematical formula}a,b∈A with {a mathematical formula}(a,b),(b,a)∉R the set {a mathematical formula}{ta,b,g} is credulously accepted, the af{a mathematical formula}F′ is stg-compact. □
      </paragraph>
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Basic semantics
     </section-title>
     <paragraph>
      In the following we show how the concepts considered in the paper carry over to conflict-free, admissible and complete semantics. For that we have to introduce complete semantics first [18]:
     </paragraph>
     <paragraph label="Definition 13">
      Given {a mathematical formula}F∈AFA, {a mathematical formula}S∈com(F) if {a mathematical formula}S∈adm(F) and for each {a mathematical formula}a∈A that is defended by S it holds that {a mathematical formula}a∈S.
     </paragraph>
     <paragraph label="Proposition 52">
      It holds that{a mathematical formula}CAFcf=CAFnaiand{a mathematical formula}CAFadm=CAFcom=CAFprf.
     </paragraph>
     <paragraph label="Proof">
      Since naive (resp. preferred) extensions of any given afF are exactly the ⊆-maximal conflict-free (resp. admissible and complete) extensions it holds that {a mathematical formula}Argsnai(F)=Argscf(F) and {a mathematical formula}Argsprf(F)=Argsadm(F)=Argscom(F). Therefore {a mathematical formula}F∈CAFnai iff {a mathematical formula}F∈CAFcf and {a mathematical formula}F∈CAFprf iff {a mathematical formula}F∈CAFadm iff {a mathematical formula}F∈CAFcom. □
     </paragraph>
     <paragraph label="Proposition 53">
      It holds that{a mathematical formula}XAFcf=XAFnaiand{a mathematical formula}XAFadm=XAFcom=XAFprf.
     </paragraph>
     <paragraph label="Proof">
      Since naive (resp. preferred) extensions of any given afF are exactly the ⊆-maximal conflict-free (resp. admissible and complete) extensions it holds that {a mathematical formula}Pairsnai(F)=Pairscf(F) and {a mathematical formula}Pairsprf(F)=Pairsadm(F)=Pairscom(F). Therefore {a mathematical formula}F∈XAFnai iff {a mathematical formula}F∈XAFcf and {a mathematical formula}F∈XAFprf iff {a mathematical formula}F∈XAFadm iff {a mathematical formula}F∈XAFcom. □
     </paragraph>
     <paragraph label="Corollary 54">
      The following problems are in{a mathematical formula}P:
     </paragraph>
     <list>
      <list-item label="1.">
       GivenafF, deciding whether{a mathematical formula}F∈CAFcf;
      </list-item>
      <list-item label="2.">
       GivenafF, deciding whether{a mathematical formula}F∈XAFcf.
      </list-item>
     </list>
     <paragraph label="Proof">
      Follows from Corollary 11 and Proposition 52, Proposition 53. □
     </paragraph>
     <paragraph label="Corollary 55">
      The following problems are{a mathematical formula}NP-complete for{a mathematical formula}σ∈{adm,com}.
     </paragraph>
     <list>
      <list-item label="1.">
       GivenafF, deciding whether{a mathematical formula}F∈CAFσ;
      </list-item>
      <list-item label="2.">
       GivenafF, deciding whether{a mathematical formula}F∈XAFσ; hardness already holds if the problem is restricted toafs{a mathematical formula}F∈CAFσ.
      </list-item>
     </list>
     <paragraph label="Proof">
      Follows from Corollary 15 and Proposition 52, Proposition 53. □
     </paragraph>
     <paragraph label="Proof">
      ECC holds for cf.Consider an arbitrary afF, and observe that in order to have an implicit conflict between arguments a and b, at least one of these arguments has to be self-attacking. Hence we obtain an analytic af{a mathematical formula}F′ having {a mathematical formula}cf(F′)=cf(F) by letting each self-attacking argument be attacked by all other arguments. □
     </paragraph>
     <paragraph label="Proof">
      ECC does not hold for adm and com.Assume ECC holds for adm (resp. com) and let F be an af which is non-analytic for prf. By assumption there is an af{a mathematical formula}F′ with {a mathematical formula}AF′=AF and {a mathematical formula}adm(F′)=adm(F) (resp. {a mathematical formula}com(F′)=com(F)). But then also {a mathematical formula}prf(F′)=prf(F), a contradiction to F being non-analytic for prf. □
     </paragraph>
     <paragraph label="Proposition 58">
      It holds that
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Σcfc=Σcfand
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Σσc⊂Σσfor{a mathematical formula}σ∈{adm,com}.
      </list-item>
     </list>
     <paragraph label="Proof">
      (1) Follows directly from Proposition 35.1.(2) Let {a mathematical formula}σ∈{adm,com}, {a mathematical formula}S={∅,{a,b}} and assume there is an af{a mathematical formula}F∈CAFσ with {a mathematical formula}σ(F)=S. Since a and b are free of conflict it must hold that {a mathematical formula}F=({a,b},∅). But then we get {a mathematical formula}adm(F)={∅,{a},{b},{a,b}} and {a mathematical formula}com(F)={{a,b}}, hence {a mathematical formula}S∉Σσc. On the other hand there is the non-compact af{a mathematical formula}F′=({a,b,c,d},{(a,c),(c,c),(c,b),(b,d),(d,d),(d,a)}) having {a mathematical formula}σ(F′)=S, hence {a mathematical formula}S∈Σσ. □
     </paragraph>
     <paragraph label="Proposition 59">
      It holds that
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Σcfc⊂Σadmcand
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Σcomc⊈Σσcand{a mathematical formula}Σσc⊈Σcomcfor{a mathematical formula}σ∈{cf,adm}.
      </list-item>
     </list>
     <paragraph label="Proof">
      (1) Given an arbitrary afF it holds that {a mathematical formula}cf(F)=adm(sym(F)), where {a mathematical formula}sym(F) is the af obtained from making all attacks of F symmetric, hence {a mathematical formula}Σcfc⊆Σadmc. Properness is by the af{a mathematical formula}G=({a,b,c,d},{(a,b),(b,c),(c,d),(d,a)}), that is the directed cycle of four arguments, having {a mathematical formula}adm(G)={∅,{a,c},{b,d}}, which is an extension-set not realizable under cf. This is by the fact that if {a mathematical formula}{a,c} is conflict-free in some af then clearly also {a mathematical formula}{a} and {a mathematical formula}{c} must be conflict-free. Hence {a mathematical formula}Σcfc⊂Σadmc.(2) {a mathematical formula}Σcomc⊈Σσc: Any extension-set {a mathematical formula}S containing exactly one non-empty set of arguments S is compactly realizable under com by the af{a mathematical formula}(S,∅), but not under cf and adm since ∅ is not contained in {a mathematical formula}S. The following example shows that these trivial cases are not the only afs in {a mathematical formula}Σcomc∖Σσc. To this end consider the afF depicted in Fig. C.28. We have {a mathematical formula}com(F)={∅,{a1},{a2},{b1},{b2},{a1,b2},{a2,b1},{a1,a2,c},{b1,b2,d}}. On the one hand it is easy to see that F is compact for complete semantics, on the other hand observe that both {a mathematical formula}{a1},{a2}∈com(F), {a mathematical formula}(a1,a2)∈Pairscom(F), but {a mathematical formula}{a1,a2}∉com(F). So {a mathematical formula}com(F) violates a necessary condition for admissible and conflict-free extension-sets (cf. [23]). Hence {a mathematical formula}com(F)∉Σσ and therefore by Proposition 58 also {a mathematical formula}com(F)∉Σσc.{a mathematical formula}Σσc⊈Σcomc: Let {a mathematical formula}F=({a,b,c},{〈a,b〉,〈b,c〉}) and observe that {a mathematical formula}cf(F)=adm(F)={∅,{a},{b},{c},{a,c}}. Now assume there is an af{a mathematical formula}G∈CAFcom with {a mathematical formula}com(G)=cf(F). Clearly {a mathematical formula}AG={a,b,c} and {a mathematical formula}RG⊆{(a,b),(b,a),(b,c),(c,b)}. Now for {a mathematical formula}∅∈com(G) each argument must be attacked and, moreover, the singletons {a mathematical formula}{a}, {a mathematical formula}{b} and {a mathematical formula}{c} must defend themselves. Hence it must be that {a mathematical formula}G=F which means {a mathematical formula}com(G)={∅,{a,c},{b}}, a contradiction. □
     </paragraph>
     <paragraph label="Proposition 60">
      It holds that
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Σcfx=Σcfand
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Σσx⊂Σσfor{a mathematical formula}σ∈{adm,com}.
      </list-item>
     </list>
     <paragraph label="Proof">
      (1) Follows directly from Theorem 30.(2) Consider the af depicted in Fig. 16 which was discussed in Example 6. We show in Theorem 31 that {a mathematical formula}prf(F)∉Σprfx. Observe that F has the same implicit conflicts (namely between {a mathematical formula}a1 and {a mathematical formula}x2, {a mathematical formula}a2 and {a mathematical formula}x3, and {a mathematical formula}a3 and {a mathematical formula}x1) for preferred, admissible and complete semantics. Now assuming that {a mathematical formula}com(F)∈Σcomx (resp. {a mathematical formula}adm(F)∈Σadmx) means that there is some af{a mathematical formula}F′ which is analytic for com (resp. adm) and has {a mathematical formula}com(F′)=com(F) (resp. {a mathematical formula}adm(F′)=adm(F)). But then {a mathematical formula}F′ is also analytic for prf and has {a mathematical formula}prf(F′)=prf(F), a contradiction to {a mathematical formula}prf(F)∉Σprfx. Hence {a mathematical formula}com(F)∉Σcomx and {a mathematical formula}adm(F)∉Σadmx. □
     </paragraph>
     <paragraph label="Proposition 61">
      It holds that
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Σcfx⊂Σadmxand
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Σcomx⊈Σσxand{a mathematical formula}Σσx⊈Σcomxfor{a mathematical formula}σ∈{cf,adm}.
      </list-item>
     </list>
     <paragraph label="Proof">
      (1) The argument from in the proof of Proposition 59 applies here as well.(2) {a mathematical formula}Σcomx⊈Σσx: Consider the afF from the proof of Proposition 59 (resp. Fig. C.28) and extend it by a symmetric attack between arguments c and d as follows {a mathematical formula}F′=(AF,RF∪{〈c,d〉}). Now {a mathematical formula}com(F)=com(F′) and it is easy to verify that {a mathematical formula}F′ is analytic for complete semantics, but as discussed before {a mathematical formula}com(F)=com(F′)∉Σσ. Hence, we have a witness for {a mathematical formula}Σcomx⊈Σσx.{a mathematical formula}Σσx⊈Σcomx: Again consider the af{a mathematical formula}F=({a,b,c},{〈a,b〉,〈b,c〉}) and recall that {a mathematical formula}cf(F)=adm(F)={∅,{a},{b},{c},{a,c}}. Assume there is an af{a mathematical formula}G∈XAFx with {a mathematical formula}com(G)=cf(F). Clearly {a mathematical formula}{a,b,c}⊆AG and {a mathematical formula}RG∩(AG×AG)⊆{(a,b),(b,a),(b,c),(c,b)}. Consider arguments in {a mathematical formula}AG that are different from {a mathematical formula}a,b,c. As such arguments do not appear in any extensions they have to be self-attacking and in conflict with all the other arguments. From {a mathematical formula}{a},{b},{c}∈cf(F)=adm(F) we obtain that {a mathematical formula}a,b,c attack all arguments in {a mathematical formula}AG∖{a,b,c}. Now as {a mathematical formula}{b}∈com(G) we have that a and c must be attacked by some argument not attacked by b. Thus {a mathematical formula}(b,a)∈RG and {a mathematical formula}(b,c)∈RG and as {a mathematical formula}{a},{c}∈com(G) and have to defend themselves also {a mathematical formula}(a,b)∈RG and {a mathematical formula}(c,b)∈RG. But then we have {a mathematical formula}com(G)={∅,{a,c},{b}}, a contradiction. □
     </paragraph>
    </section>
    <section label="Appendix D">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>