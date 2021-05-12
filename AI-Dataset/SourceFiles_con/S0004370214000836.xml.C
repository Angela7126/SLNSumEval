<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Guarantees and limits of preprocessing in constraint satisfaction and reasoning.
   </title>
   <abstract>
    We present a first theoretical analysis of the power of polynomial-time preprocessing for important combinatorial problems from various areas in AI. We consider problems from Constraint Satisfaction, Global Constraints, Satisfiability, Nonmonotonic and Bayesian Reasoning under structural restrictions. All these problems involve two tasks: (i) identifying the structure in the input as required by the restriction, and (ii) using the identified structure to solve the reasoning task efficiently. We show that for most of the considered problems, task (i) admits a polynomial-time preprocessing to a problem kernel whose size is polynomial in a structural problem parameter of the input, in contrast to task (ii) which does not admit such a reduction to a problem kernel of polynomial size, subject to a complexity theoretic assumption. As a notable exception we show that the consistency problem for the AtMost-NValue constraint admits a polynomial kernel consisting of a quadratic number of variables and domain values. Our results provide a firm worst-case guarantees and theoretical boundaries for the performance of polynomial-time preprocessing algorithms for the considered problems.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Many important computational problems that arise in various areas of AI are intractable. Nevertheless, AI research has been very successful in developing and implementing heuristic solvers that work well on real-world instances. An important component of virtually every solver is a powerful polynomial-time preprocessing procedure that reduces the problem input. For instance, preprocessing techniques for the propositional satisfiability problem are based on Boolean Constraint Propagation (see, e.g., [27]), CSP solvers make use of various local consistency algorithms that filter the domains of variables (see, e.g., [4]); similar preprocessing methods are used by solvers for Nonmonotonic and Bayesian reasoning problems (see, e.g., [38], [13], respectively). The history of preprocessing, like applying reduction rules to simplify truth functions, can be traced back to the 1950s [56]. A natural question in this regard is how to measure the quality of preprocessing rules proposed for a specific problem.
     </paragraph>
     <paragraph>
      Until recently, no provable performance guarantees for polynomial-time preprocessing methods have been obtained, and so preprocessing was only subject of empirical studies. A possible reason for the lack of theoretical results is a certain inadequacy of the P vs NP framework for such an analysis: if we could reduce in polynomial time an instance of an NP-hard problem just by one bit, then we could solve the entire problem in polynomial time by repeating the reduction step a polynomial number of times, and {a mathematical formula}P=NP would follow.
     </paragraph>
     <paragraph>
      With the advent of parameterized complexity[24], a new theoretical framework became available that provides suitable tools to analyze the power of preprocessing. Parameterized complexity considers a problem in a two-dimensional setting, where in addition to the input size n, a problem parameter k is taken into consideration. This parameter can encode a structural aspect of the problem instance. A problem is called fixed-parameter tractable (FPT) if it can be solved in time {a mathematical formula}f(k)p(n) where f is a function of the parameter k and p is a polynomial of the input size n. Thus, for FPT problems, the combinatorial explosion can be confined to the parameter and is independent of the input size. It is known that a problem is fixed-parameter tractable if and only if every problem input can be reduced by polynomial-time preprocessing to an equivalent input whose size is bounded by a function of the parameter [25]. The reduced instance is called the problem kernel, the preprocessing is called kernelization. The power of polynomial-time preprocessing can now be benchmarked in terms of the size of the kernel. Once a small kernel is obtained, we can apply any method of choice to solve the kernel: brute-force search, heuristics, approximation, etc. [42]. Because of this flexibility a small kernel is generally preferable to a less flexible branching-based fixed-parameter algorithm. Thus, small kernels provide an additional value that goes beyond bare fixed-parameter tractability.
     </paragraph>
     <paragraph>
      Kernelization is an important algorithmic technique that has become the subject of a very active field in state-of-the-art combinatorial optimization (see, e.g., the references in [28], [42], [46], [58]). Kernelization can be seen as a preprocessing with performance guarantee that reduces a problem instance in polynomial time to an equivalent instance, the kernel, whose size is a function of the parameter [28], [32], [42], [46].
     </paragraph>
     <paragraph>
      Once a kernel is obtained, the time required to solve the instance is a function of the parameter only and therefore independent of the input size. While, in general, the time needed to solve an instance does not necessarily depend on the size of the instance alone, the kernelization view is that it preprocesses the easy parts of an instance, leaving a core instance encoding the hard parts of the problem instance. Naturally one aims at kernels that are as small as possible, in order to guarantee good worst-case running times as a function of the parameter, and the kernel size provides a performance guarantee for the preprocessing. Some NP-hard combinatorial problems such as k-Vertex Cover admit polynomially sized kernels, for others such as k-Path an exponential kernel is the best one can hope for [11].
     </paragraph>
     <paragraph>
      As an example of a polynomial kernel, consider the k-Vertex Cover problem, which, for a graph {a mathematical formula}G=(V,E) and an integer parameter k, is to decide whether there is a set S of at most k vertices such that each edge from E has at least one endpoint in S. Buss' kernelization algorithm for k-Vertex Cover (see [14]) computes the set U of vertices with degree at least {a mathematical formula}k+1 in G. If {a mathematical formula}|U|&gt;k, then reject the instance, i.e., output a trivial No-instance (e.g., the graph {a mathematical formula}K2 consisting of one edge and the parameter 0), since every vertex cover of size at most k contains each vertex from U. Otherwise, if {a mathematical formula}G∖U has more than {a mathematical formula}k(k−|U|) edges, then reject the instance, since each vertex from {a mathematical formula}G∖U covers at most k edges. Otherwise, output the instance {a mathematical formula}(G∖(U∪L),k−|U|), where L is the set of degree-0 vertices in {a mathematical formula}G∖U. This instance has {a mathematical formula}O(k2) vertices and edges. Thus, Buss' kernelization algorithm gives a quadratic kernel for k-Vertex Cover.
     </paragraph>
     <paragraph>
      In previous research several NP-hard AI problems have been shown to be fixed-parameter tractable. We list some important examples from various areas:
     </paragraph>
     <list>
      <list-item label="1.">
       Constraint satisfaction problems (CSP) over a fixed universe of values, parameterized by the induced width [41].
      </list-item>
      <list-item label="2.">
       Consistency and generalized arc consistency for intractable global constraints, parameterized by the cardinalities of certain sets of values [5].
      </list-item>
      <list-item label="3.">
       Propositional satisfiability (SAT), parameterized by the size of backdoors [51].
      </list-item>
      <list-item label="4.">
       Positive inference in Bayesian networks with variables of bounded domain size, parameterized by size of loop cutsets [53], [9].
      </list-item>
      <list-item label="5.">
       Nonmonotonic reasoning with normal logic programs, parameterized by feedback width [41].
      </list-item>
     </list>
     <paragraph>
      All these problems involve the following two tasks.
     </paragraph>
     <list>
      <list-item label="(i)">
       Structure Recognition Task: identify the structure in the input as required by the considered parameter.
      </list-item>
      <list-item label="(ii)">
       Reasoning Task: use the identified structure to solve a reasoning task efficiently.
      </list-item>
     </list>
     <paragraph>
      For most of the considered problems we observe the following pattern: the Structure Recognition Task admits a polynomial kernel, in contrast to the Reasoning Task, which does not admit a polynomial kernel, unless the Polynomial Hierarchy collapses to its third level.
     </paragraph>
     <paragraph>
      A negative exception to this pattern is the recognition problem for CSPs of small induced width, which most likely does not admit a polynomial kernel.
     </paragraph>
     <paragraph>
      A positive exception to this pattern is the AtMost-NValue global constraint, for which we obtain a polynomial kernel. As in [5], the parameter is the number of holes in the domains of the variables, measuring how close the domains are to being intervals. More specifically, we present a linear time preprocessing algorithm that reduces an AtMost-NValue constraint C with k holes to a consistency-equivalent AtMost-NValue constraint {a mathematical formula}C′ of size polynomial in k. In fact, {a mathematical formula}C′ has at most {a mathematical formula}O(k2) variables and {a mathematical formula}O(k2) domain values. We also give an improved branching algorithm checking the consistency of {a mathematical formula}C′ in time {a mathematical formula}O(1.6181k+n). The combination of kernelization and branching yields efficient algorithms for the consistency and propagation of (AtMost-)NValue constraints.
     </paragraph>
     <paragraph>
      Outline
     </paragraph>
     <paragraph>
      This article is organized as follows. Parameterized complexity and kernelization are formally introduced in Section 2. Section 3 describes the tools we use to show that certain parameterized problems do not have polynomial kernels. Sections 2 Formal background, 3 Tools for kernel lower bounds, 4 Constraint networks, 5 Satisfiability, 6 Global constraints, 7 Bayesian reasoning, 8 Nonmonotonic reasoning prove kernel lower bounds for parameterized problems in the areas of constraint networks, satisfiability, global constraints, Bayesian reasoning, and nonmonotonic reasoning. Each of these sections also gives all necessary definitions, relevant background, and related work for the considered problems. In addition, Section 6 describes a polynomial kernel for the consistency problem for the AtMost-NValue constraint parameterized by the number of holes in the variable domains, and an FPT algorithm that uses this kernel as a first step. The correctness and performance guarantees of the kernelization algorithm are only outlined in Section 6 and proved in detail in Appendix A. The conclusion, Section 9, broadly recapitulates the results and suggests the study of Turing kernels to overcome the shortcomings of (standard) kernels for many fundamental AI and Reasoning problems.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Formal background
     </section-title>
     <paragraph>
      A parameterized problem P is a subset of {a mathematical formula}Σ⁎×N for some finite alphabet Σ. For a problem instance {a mathematical formula}(x,k)∈Σ⁎×N we call x the main part and k the parameter. We assume the parameter is represented in unary. For the parameterized problems considered in this paper, the parameter is a function of the main part, i.e., {a mathematical formula}k=π(x) for a function π. We then denote the problem as {a mathematical formula}P(π), e.g., {a mathematical formula}U-CSP(width) denotes the problem U-CSP parameterized by the width of the given tree decomposition.
     </paragraph>
     <paragraph>
      A parameterized problem P is fixed-parameter tractable if there exists an algorithm that solves any input {a mathematical formula}(x,k)∈Σ⁎×N in time {a mathematical formula}O(f(k)⋅p(|x|)) where f is an arbitrary computable function of k and p is a polynomial in {a mathematical formula}|x|.
     </paragraph>
     <paragraph>
      A kernelization for a parameterized problem {a mathematical formula}P⊆Σ⁎×N is an algorithm that, given {a mathematical formula}(x,k)∈Σ⁎×N, outputs in time polynomial in {a mathematical formula}|x|+k a pair {a mathematical formula}(x′,k′)∈Σ⁎×N such that
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}(x,k)∈P if and only if {a mathematical formula}(x′,k′)∈P, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}|x′|+k′≤g(k), where g is an arbitrary computable function, called the size of the kernel.
      </list-item>
     </list>
     <paragraph>
      In particular, for constant k the kernel has constant size {a mathematical formula}g(k). If g is a polynomial then we say that P admits a polynomial kernel.
     </paragraph>
     <paragraph>
      Every fixed-parameter tractable problem admits a kernel. This can be seen by the following argument due to Downey et al. [25]. Assume we can decide instances {a mathematical formula}(x,k) of problem P in time {a mathematical formula}f(k)|x|O(1). We kernelize an instance {a mathematical formula}(x,k) as follows. If {a mathematical formula}|x|≤f(k) then we already have a kernel of size {a mathematical formula}f(k). Otherwise, if {a mathematical formula}|x|&gt;f(k), then {a mathematical formula}f(k)|x|O(1)=|x|O(1) is a polynomial; hence we can decide the instance in polynomial time and replace it with a small decision-equivalent instance {a mathematical formula}(x′,k′). Thus we always have a kernel of size at most {a mathematical formula}f(k). However, {a mathematical formula}f(k) is super-polynomial for NP-hard problems (unless {a mathematical formula}P=NP), hence this generic construction does not provide polynomial kernels.
     </paragraph>
     <paragraph>
      We understand preprocessing for an NP-hard problem as a polynomial-time procedure that transforms an instance of the problem to a (possible smaller) solution-equivalent instance of the same problem. Kernelization is such a preprocessing with a performance guarantee, i.e., we are guaranteed that the preprocessing yields a kernel whose size is bounded in terms of the parameter of the given problem instance. In the literature also different forms of preprocessing have been considered. An important one is knowledge compilation, a two-phases approach to reasoning problems where in a first phase a given knowledge base is (possibly in exponential time) preprocessed (“compiled”), such that in a second phase various queries can be answered in polynomial time [15].
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Tools for kernel lower bounds
     </section-title>
     <paragraph>
      In the sequel we will use recently developed tools to obtain kernel lower bounds. Our kernel lower bounds are subject to the widely believed complexity theoretic assumption {a mathematical formula}NP⊈coNP/poly. In other words, the tools allow us to show that a parameterized problem does not admit a polynomial kernel unless {a mathematical formula}NP⊆coNP/poly. In particular, {a mathematical formula}NP⊆coNP/poly would imply the collapse of the Polynomial Hierarchy to the third level: {a mathematical formula}PH=Σp3[52].
     </paragraph>
     <paragraph>
      A composition algorithm for a parameterized problem {a mathematical formula}P⊆Σ⁎×N is an algorithm that receives as input a sequence {a mathematical formula}(x1,k),…,(xt,k)∈Σ⁎×N, uses time polynomial in {a mathematical formula}∑i=1t|xi|+k, and outputs {a mathematical formula}(y,k′)∈Σ⁎×N with (i) {a mathematical formula}(y,k′)∈P if and only if {a mathematical formula}(xi,k)∈P for some {a mathematical formula}1≤i≤t, and (ii) {a mathematical formula}k′ is polynomial in k. A parameterized problem is compositional if it has a composition algorithm. With each parameterized problem {a mathematical formula}P⊆Σ⁎×N we associate a classical problem{a mathematical formula} where 1 denotes an arbitrary symbol from Σ and # is a new symbol not in Σ. We call {a mathematical formula}UP[P] the unparameterized version of P.
     </paragraph>
     <paragraph>
      The following result is the basis for our kernel lower bounds.
     </paragraph>
     <paragraph label="Theorem 1">
      (See[11], [34].) Let P be a parameterized problem whose unparameterized version is NP-complete. If P is compositional, then it does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}P,Q⊆Σ⁎×N be parameterized problems. We say that P is polynomial parameter reducible to Q if there exists a polynomial time computable function {a mathematical formula}K:Σ⁎×N→Σ⁎×N and a polynomial p, such that for all {a mathematical formula}(x,k)∈Σ⁎×N we have (i) {a mathematical formula}(x,k)∈P if and only if {a mathematical formula}K(x,k)=(x′,k′)∈Q, and (ii) {a mathematical formula}k′≤p(k). The function K is called a polynomial parameter transformation.
     </paragraph>
     <paragraph>
      The following theorem allows us to transform kernel lower bounds from one problem to another.
     </paragraph>
     <paragraph label="Theorem 2">
      (See[12].) Let P and Q be parameterized problems such that{a mathematical formula}UP[P]is NP-complete,{a mathematical formula}UP[Q]is in NP, and there is a polynomial parameter transformation from P to Q. If Q has a polynomial kernel, then P has a polynomial kernel.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Constraint networks
     </section-title>
     <paragraph>
      Constraint networks have proven successful in modeling everyday cognitive tasks such as vision, language comprehension, default reasoning, and abduction, as well as in applications such as scheduling, design, diagnosis, and temporal and spatial reasoning [21]. A constraint network is a triple {a mathematical formula}I=(V,U,C) where V is a finite set of variables, U is a finite universe of values, and {a mathematical formula}C={C1,…,Cm} is set of constraints. Each constraint {a mathematical formula}Ci is a pair {a mathematical formula}(Si,Ri) where {a mathematical formula}Si is a list of variables of length {a mathematical formula}ri called the constraint scope, and {a mathematical formula}Ri is an {a mathematical formula}ri-ary relation over U, called the constraint relation. The tuples of {a mathematical formula}Ri indicate the allowed combinations of simultaneous values for the variables {a mathematical formula}Si. A solution is a mapping {a mathematical formula}τ:V→U such that for each {a mathematical formula}1≤i≤m and {a mathematical formula}Si=(x1,…,xri), we have {a mathematical formula}(τ(x1),…,τ(xri))∈Ri. A constraint network is satisfiable if it has a solution.
     </paragraph>
     <paragraph>
      With a constraint network {a mathematical formula}I=(V,U,C) we associate its constraint graph{a mathematical formula}G=(V,E) where E contains an edge between two variables if and only if they occur together in the scope of a constraint. A width w tree decomposition of a graph G is a pair {a mathematical formula}(T,λ) where T is a tree and λ is a labeling of the nodes of T with sets of vertices of G such that the following properties are satisfied: (i) every vertex of G belongs to {a mathematical formula}λ(p) for some node p of T; (ii) every edge of G is contained in {a mathematical formula}λ(p) for some node p of T; (iii) for each vertex v of G the set of all tree nodes p with {a mathematical formula}v∈λ(p) induces a connected subtree of T; (iv) {a mathematical formula}|λ(p)|−1≤w holds for all tree nodes p. The treewidth of G is the smallest w such that G has a width w tree decomposition. The induced width of a constraint network is the treewidth of its constraint graph [22].
     </paragraph>
     <paragraph>
      Kernelization fits perfectly into the context of Constraint Processing where preprocessing and data reduction (e.g., in terms of local consistency algorithms, propagation, and domain filtering) are key methods [4], [43].
     </paragraph>
     <paragraph>
      Let U be a fixed universe containing at least two elements. We consider the following parameterized version of the constraint satisfaction problem (CSP).
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}U-CSP(width)
      </list-item>
      <list-item>
       Instance: A constraint network {a mathematical formula}I=(V,U,C) and a width w tree decomposition of the constraint graph of I.
      </list-item>
      <list-item>
       Parameter: The integer w.
      </list-item>
      <list-item>
       Question: Is I satisfiable?
      </list-item>
     </list>
     <paragraph>
      Associated with this problem is also the task of recognizing instances of small treewidth. We state this problem in form of the following decision problem.
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}Rec-U-CSP(width)
      </list-item>
      <list-item>
       Instance: A constraint network {a mathematical formula}I=(V,U,C) and an integer {a mathematical formula}w≥0.
      </list-item>
      <list-item>
       Parameter: The integer w.
      </list-item>
      <list-item>
       Question: Does I admit a tree decomposition of width ≤w?
      </list-item>
     </list>
     <paragraph>
      It is well known that {a mathematical formula}U-CSP(width) is fixed-parameter tractable over any fixed universe U[22], [41] (for generalizations see [62]). We contrast this classical result and show that it is unlikely that {a mathematical formula}U-CSP(width) admits a polynomial kernel, even in the simplest case where {a mathematical formula}U={0,1}.
     </paragraph>
     <paragraph label="Theorem 3">
      {a mathematical formula}{0,1}-CSP(width)does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
     </paragraph>
     <paragraph label="Proof">
      We show that {a mathematical formula}{0,1}-CSP(width) is compositional. Let {a mathematical formula}(Ii,Ti), {a mathematical formula}1≤i≤t, be a given sequence of instances of {a mathematical formula}{0,1}-CSP(width) where {a mathematical formula}Ii=(Vi,{0,1},Ci) is a constraint network and {a mathematical formula}Ti is a width w tree decomposition of the constraint graph of {a mathematical formula}Ii. We may assume, w.l.o.g., that {a mathematical formula}Vi∩Vj=∅ for {a mathematical formula}1≤i&lt;j≤t (otherwise we can simply change the names of variables). We form a new constraint network {a mathematical formula}I=(V,{0,1},C) as follows. We put {a mathematical formula}V=⋃i=1tVi∪{a1,…,at,b0,…,bt} where {a mathematical formula}ai,bi are new variables. We define the set {a mathematical formula}C of constraints in three groups.
      <list>
       For each {a mathematical formula}1≤i≤t and each constraint {a mathematical formula}C=((x1,…,xr),R)∈Ci we add to {a mathematical formula}C a new constraint {a mathematical formula}C′=((x1,…,xr,ai),R′) where {a mathematical formula}R′={(u1,…,ur,0):(u1,…,ur)∈R}∪{(1,…,1)}.We add t ternary constraints {a mathematical formula}C1⁎,…,Ct⁎ where {a mathematical formula}Ci⁎=((bi−1,bi,ai),R⁎) and {a mathematical formula}R⁎={(0,0,1),(0,1,0),(1,1,1)}.Finally, we add two unary constraints {a mathematical formula}C0=((b0),(0)) and {a mathematical formula}C1=((bt),(1)) which force the values of {a mathematical formula}b0 and {a mathematical formula}bt to 0 and 1, respectively.Let
      </list>
      <paragraph>
       {a mathematical formula}G,Gi be the constraint graphs of I and {a mathematical formula}Ii, respectively. Fig. 1 shows an illustration of G for {a mathematical formula}t=4. We observe that {a mathematical formula}a1,…,at are cut vertices of G. Removing these vertices separates G into independent parts {a mathematical formula}P,G1′,…,Gt′ where P is the path {a mathematical formula}b0,b1,…,bt, and {a mathematical formula}Gi′ is isomorphic to {a mathematical formula}Gi. By standard techniques (see, e.g., [44]), we can put the given width w tree decompositions {a mathematical formula}T1,…,Tt of {a mathematical formula}G1′,…,Gt′ and the trivial width 1 tree decomposition of P together to a width {a mathematical formula}w+1 tree decomposition T of G. Clearly {a mathematical formula}(I,T) can be obtained from {a mathematical formula}(Ii,Ti), {a mathematical formula}1≤i≤t, in polynomial time.We claim that I is satisfiable if and only if at least one of the {a mathematical formula}Ii is satisfiable. This claim can be verified by means of the following observations: The constraints in groups (2) and (3) provide that for any satisfying assignment there will be some {a mathematical formula}0≤i≤t−1 such that {a mathematical formula}b0,…,bi are all set to 0 and {a mathematical formula}bi+1,…,bt are all set to 1; consequently {a mathematical formula}ai is set to 0 and all {a mathematical formula}aj for {a mathematical formula}j≠i are set to 1. The constraints in group (1) provide that if we set {a mathematical formula}ai to 0, then we obtain from {a mathematical formula}C′ the original constraint C; if we set {a mathematical formula}ai to 1 then we obtain a constraint that can be satisfied by setting all remaining variables to 1. We conclude that {a mathematical formula}{0,1}-CSP(width) is compositional.In order to apply Theorem 1, it remains to establish that the unparameterized version of {a mathematical formula}{0,1}-CSP(width) is NP-complete. Deciding whether a constraint network I over the universe {a mathematical formula}{0,1} is satisfiable is well-known to be NP-complete (say by reducing 3-SAT). To a constraint network I on n variables we can always add a trivial width {a mathematical formula}w=n−1 tree decomposition of its constraint graph (taking a single tree node t where {a mathematical formula}λ(t) contains all variables of I). Hence {a mathematical formula}UP[{0,1}-CSP(width)] is NP-complete.  □
      </paragraph>
     </paragraph>
     <paragraph>
      Let us turn now to the recognition problem {a mathematical formula}Rec-U-CSP(width). By Bodlaender's theorem [10], the problem is fixed-parameter tractable. However, the problem is unlikely to admit a polynomial kernel. In fact, Bodlaender et al. [11] showed that the related problem of testing whether a graph has treewidth at most w does not have a polynomial kernel (taking w as the parameter), unless a certain “AND-conjecture” fails. In turn, Drucker [26] showed that a failure of the AND-conjecture implies {a mathematical formula}NP⊆coNP/poly. The combination of these two results relates directly to {a mathematical formula}Rec-U-CSP(width).
     </paragraph>
     <paragraph label="Proposition 1">
      {a mathematical formula}Rec-{0,1}-CSP(width)does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Satisfiability
     </section-title>
     <paragraph>
      The propositional satisfiability problem (SAT) was the first problem shown to be NP-hard [18]. Despite its hardness, SAT solvers are increasingly leaving their mark as a general-purpose tool in areas as diverse as software and hardware verification, automatic test pattern generation, planning, scheduling, and even challenging problems from algebra [40]. SAT solvers are capable of exploiting the hidden structure present in real-world problem instances. The concept of backdoors, introduced by Williams et al. [65], provides a means for making the vague notion of a hidden structure explicit. Backdoors are defined with respect to a “sub-solver” which is a polynomial-time algorithm that correctly decides the satisfiability for a class {a mathematical formula}C of CNF formulas. More specifically, Gomes et al. [40] define a sub-solver to be an algorithm {a mathematical formula}A that takes as input a CNF formula F and has the following properties:
     </paragraph>
     <list>
      <list-item label="1.">
       Trichotomy: {a mathematical formula}A either rejects the input F, or determines F correctly as unsatisfiable or satisfiable;
      </list-item>
      <list-item label="2.">
       Efficiency: {a mathematical formula}A runs in polynomial time;
      </list-item>
      <list-item label="3.">
       Trivial solvability: {a mathematical formula}A can determine if F is trivially satisfiable (has no clauses) or trivially unsatisfiable (contains only the empty clause);
      </list-item>
      <list-item label="4.">
       Self-reducibility: if {a mathematical formula}A determines F, then for any variable x and value {a mathematical formula}ε∈{0,1}, {a mathematical formula}A determines {a mathematical formula}F[x=ε]. {a mathematical formula}F[τ] denotes the formula obtained from F by applying the partial assignment τ, i.e., satisfied clauses are removed and false literals are removed from the remaining clauses.
      </list-item>
     </list>
     <paragraph>
      We identify a sub-solver {a mathematical formula}A with the class {a mathematical formula}CA of CNF formulas whose satisfiability can be determined by {a mathematical formula}A. A strong{a mathematical formula}A-backdoor set (or {a mathematical formula}A-backdoor, for short) of a CNF formula F is a set B of variables such that for each possible truth assignment τ to the variables in B, the satisfiability of {a mathematical formula}F[τ] can be determined by sub-solver {a mathematical formula}A in time {a mathematical formula}O(nc). The smaller the backdoor B, the more useful it is for satisfiability solving, which makes the size of the backdoor a natural parameter to consider (see [37] for a survey on the parameterized complexity of backdoor problems). If we know an {a mathematical formula}A-backdoor of size k, we can decide the satisfiability of F by running {a mathematical formula}A on {a mathematical formula}2k instances {a mathematical formula}F[τ], yielding a time bound of {a mathematical formula}O(2knc). Hence SAT decision is fixed-parameter tractable in the backdoor size k for any sub-solver {a mathematical formula}A. Hence the following problem is clearly fixed-parameter tractable for any sub-solver {a mathematical formula}A.
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}SAT(A-backdoor)
      </list-item>
      <list-item>
       Instance: A CNF formula F, and an {a mathematical formula}A-backdoor B of F of size k.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Is F satisfiable?
      </list-item>
     </list>
     <paragraph>
      We also consider for every subsolver {a mathematical formula}A the associated recognition problem.
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}Rec-SAT(A-backdoor)
      </list-item>
      <list-item>
       Instance: A CNF formula F, and an integer {a mathematical formula}k≥0.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Does F have an {a mathematical formula}A-backdoor of size at most k?
      </list-item>
     </list>
     <paragraph>
      With the problem {a mathematical formula}SAT(A-backdoor) we are concerned with the question of whether instead of trying all {a mathematical formula}2k possible partial assignments we can reduce the instance to a polynomial kernel. We will establish a very general result that applies to all possible sub-solvers.
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}SAT(A-backdoor)does not admit a polynomial kernel for any sub-solver{a mathematical formula}Aunless{a mathematical formula}NP⊆coNP/poly.We will devise polynomial parameter transformations from the following parameterized problem which is known to be compositional [34] and therefore unlikely to admit a polynomial kernel.
     </paragraph>
     <list>
      <list-item>
       SAT(vars)
      </list-item>
      <list-item>
       Instance: A propositional formula F in CNF on n variables.
      </list-item>
      <list-item>
       Parameter: The number n of variables.
      </list-item>
      <list-item>
       Question: Is F satisfiable?
      </list-item>
     </list>
     <paragraph>
      Let us denote by rCNF the class of CNF formulas where each clause has at most r literals, and by Horn the class of CNF formulas where each clause has at most one positive literal. Sub-solvers for Horn and 2CNF follow from [23] and [45], respectively.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}3SAT(π) (where π is an arbitrary parameterization) denote the problem {a mathematical formula}SAT(π) restricted to 3CNF formulas. In contrast to SAT(vars), the parameterized problem 3SAT(vars) has a trivial polynomial kernel: if we remove duplicate clauses, then any 3CNF formula on n variables contains at most {a mathematical formula}O(n3) clauses, and so is a polynomial kernel. Hence the easy proof of Theorem 4 does not carry over to {a mathematical formula}3SAT(A-backdoor). We therefore consider the cases 3SAT(Horn-backdoor) and 3SAT(2CNF-backdoor) separately, these cases are important since the detection of Horn and {a mathematical formula}2CNF-backdoors is fixed-parameter tractable [51].
     </paragraph>
     <paragraph label="Proof">
      Neither3SAT(Horn-backdoor) nor3SAT(2CNF-backdoor) admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.Let {a mathematical formula}C∈{Horn,2CNF}. We show that {a mathematical formula}3SAT(C-backdoor) is compositional. Let {a mathematical formula}(Fi,Bi), {a mathematical formula}1≤i≤t, be a given sequence of instances of {a mathematical formula}3SAT(C-backdoor) where {a mathematical formula}Fi is a 3CNF formula and {a mathematical formula}Bi is a {a mathematical formula}C-backdoor set of {a mathematical formula}Fi of size k. We distinguish two cases.Case 1: {a mathematical formula}t&gt;2k. Let {a mathematical formula}‖Fi‖:=∑C∈Fi|C| and {a mathematical formula}n:=maxi=1t⁡‖Fi‖. Whether {a mathematical formula}Fi is satisfiable or not can be decided in time {a mathematical formula}O(2kn) since the satisfiability of a Horn or 2CNF formula can be decided in linear time. We can check whether at least one of the formulas {a mathematical formula}F1,…,Ft is satisfiable in time {a mathematical formula}O(t2kn)=O(t2n) which is polynomial in {a mathematical formula}t+n. If some {a mathematical formula}Fi is satisfiable, we output {a mathematical formula}(Fi,Bi); otherwise we output {a mathematical formula}(F1,B1) ({a mathematical formula}F1 is unsatisfiable). Hence we have a composition algorithm.Case 2: {a mathematical formula}t≤2k. This case is more involved. We construct a new instance {a mathematical formula}(F,B) of {a mathematical formula}3SAT(C-backdoor) as follows.Let {a mathematical formula}s=⌈log2⁡t⌉. Since {a mathematical formula}t≤2k, {a mathematical formula}s≤k follows.Let {a mathematical formula}Vi denote the set of variables of {a mathematical formula}Fi. We may assume, w.l.o.g., that {a mathematical formula}B1=⋯=Bt and that {a mathematical formula}Vi∩Vj=B1 for all {a mathematical formula}1≤i&lt;j≤t since otherwise we can change names of variable accordingly. In a first step we obtain from every {a mathematical formula}Fi a CNF formula {a mathematical formula}Fi′ as follows. For each variable {a mathematical formula}x∈Vi∖B1 we take {a mathematical formula}s+1 new variables {a mathematical formula}x0,…,xs. We replace each positive occurrence of a variable {a mathematical formula}x∈Vi∖B1 in {a mathematical formula}Fi with the literal {a mathematical formula}x0 and each negative occurrence of x with the literal {a mathematical formula}¬xs.We add all clauses of the form {a mathematical formula}(¬xj−1∨xj) for {a mathematical formula}1≤j≤s; we call these clauses “connection clauses.” Let {a mathematical formula}Fi′ be the formula obtained from {a mathematical formula}Fi in this way. We observe that {a mathematical formula}Fi′ and {a mathematical formula}Fi are SAT-equivalent, since the connection clauses form an implication chain. Since the connection clauses are both Horn and 2CNF, {a mathematical formula}B1 is also a {a mathematical formula}C-backdoor of {a mathematical formula}Fi′.For an illustration of this construction see Example 1 below.We take a set {a mathematical formula}Y={y1,…,ys} of new variables. Let {a mathematical formula}C1,…,C2s be the sequence of all {a mathematical formula}2s possible clauses (modulo permutation of literals within a clause) containing each variable from Y either positively or negatively. Consequently we can write {a mathematical formula}Ci as {a mathematical formula}(ℓ1i∨⋯∨ℓsi) where {a mathematical formula}ℓji∈{yj,¬yj}.For {a mathematical formula}1≤i≤t we add to each connection clause {a mathematical formula}(¬xj−1∨xj) of {a mathematical formula}Fi′ the literal {a mathematical formula}ℓji∈Ci. Let {a mathematical formula}Fi″ denote the 3CNF formula obtained from {a mathematical formula}Fi′ this way.For {a mathematical formula}t&lt;i≤2s we define 3CNF formulas {a mathematical formula}Fi″ as follows. If {a mathematical formula}s≤3 then {a mathematical formula}Fi″ consists just of the clause {a mathematical formula}Ci. If {a mathematical formula}s&gt;3 then we take new variables {a mathematical formula}z2i,…,zs−2i and let {a mathematical formula}Fi″ consist of the clauses {a mathematical formula}(ℓ1i∨ℓ2i∨¬z2i), {a mathematical formula}(ℓ3i∨z2i∨¬z3i),…,(ℓs−2i∨zs−3i∨¬zs−2i), {a mathematical formula}(ℓs−1i∨ℓsi∨zs−2i). Finally, we let F be the 3CNF formula containing all the clauses from {a mathematical formula}F1″,…,F2s″. Any assignment τ to {a mathematical formula}Y∪B1 that satisfies {a mathematical formula}Ci can be extended to an assignment that satisfies {a mathematical formula}Fi″ since such assignment satisfies at least one connection clause {a mathematical formula}(xj−1∨xj∨ℓji) and so the chain of implications from {a mathematical formula}xo to {a mathematical formula}xs is broken.It is not difficult to verify the following two claims. (i) F is satisfiable if and only if at least one of the formulas {a mathematical formula}Fi is satisfiable. (ii) {a mathematical formula}B=Y∪B1 is a {a mathematical formula}C-backdoor of F. Hence we have also a composition algorithm in Case 2, and thus {a mathematical formula}3SAT(C-backdoor) is compositional. Clearly {a mathematical formula}UP[3SAT(C-backdoor)] is NP-complete, hence the result follows from Theorem 1.  □
     </paragraph>
     <paragraph label="Example 1">
      We illustrate the constructions of this proof with a running example, where we let {a mathematical formula}s=2, {a mathematical formula}t=4, {a mathematical formula}i=2, and {a mathematical formula}B1={b}.Assume that we have{a mathematical formula} From this we obtain the following formula, containing four connection clauses{a mathematical formula} Now assume {a mathematical formula}Ci=(y1∨¬y2). We add to the connection clauses literals from {a mathematical formula}Ci and we obtain{a mathematical formula} Assigning {a mathematical formula}y1 to false and {a mathematical formula}y2 to true reduces {a mathematical formula}Fi″ to {a mathematical formula}Fi′. The other three possibilities of assigning truth values to {a mathematical formula}y1,y2 break the connection clauses and make the formula trivially satisfiable. ⊣
     </paragraph>
     <paragraph>
      We now turn to the recognition problem {a mathematical formula}Rec-SAT(A-backdoor), in particular for {a mathematical formula}A∈{Horn,2CNF} for which, as mentioned above, the problem is known to be fixed-parameter tractable [51]. Here we are able to obtain positive results.
     </paragraph>
     <paragraph label="Proof">
      Both{a mathematical formula}Rec-SAT(Horn-backdoor)and{a mathematical formula}Rec-SAT(2CNF-backdoor)admit polynomial kernels, with a linear and quadratic number of variables, respectively.Let {a mathematical formula}(F,k) be the instance of Rec-SAT(Horn-backdoor). We construct a graph {a mathematical formula}G(F) whose vertices are the variables of F and which contains an edge between two variables {a mathematical formula}u,v if and only if both variables appear as positive literals together in a clause. It is well-known and easy to see that the vertex covers of {a mathematical formula}G(F) are exactly the Horn-backdoor sets of F[61]. Recall that a vertex cover of a graph is a set of vertices that contains at least one end of each edge of the graph. Now, we apply the known kernelization algorithm for vertex covers [17] to {a mathematical formula}(G(F),k) and obtain in polynomial time an equivalent instance {a mathematical formula}(G′,k′) where {a mathematical formula}G′ has at most 2k vertices. Now it only remains to consider {a mathematical formula}G′ as a CNF formula {a mathematical formula}F′ where each edge gives rise to a binary clause on two positive literals. Since evidently {a mathematical formula}G(F′)=G′, we conclude that {a mathematical formula}(F′,k′) constitutes a polynomial kernel for Rec-SAT(Horn-backdoor).For {a mathematical formula}Rec-SAT(2CNF-backdoor) we proceed similarly. Let {a mathematical formula}(F,k) be an instance of this problem. We construct a 3-uniform hypergraph {a mathematical formula}H(F) whose vertices are the variables of F and which contains a hyperedge on any three variables that appear (positively or negatively) together in a clause of F. Again, it is well-known and easy to see that the hitting sets of {a mathematical formula}H(F) are exactly the {a mathematical formula}2CNF-backdoor sets of F[61]. Recall that a hitting set of a hypergraph is a set of vertices that contains at least one vertex from each hyperedge. Now we apply a known kernelization algorithm for the hitting set problem on 3-uniform hypergraphs (3HS) [1] to {a mathematical formula}(H(F),k) and obtain in polynomial time an equivalent instance {a mathematical formula}(H′,k′) where {a mathematical formula}H′ has at most {a mathematical formula}O(k2) vertices. It remains to consider {a mathematical formula}H′ as a CNF formula {a mathematical formula}F′ where each hyperedge gives rise to a ternary clause on three positive literals. Since evidently {a mathematical formula}H(F′)=H′, we conclude that {a mathematical formula}(F′,k′) constitutes a polynomial kernel for {a mathematical formula}Rec-SAT(2CNF-backdoor).  □
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Global constraints
     </section-title>
     <paragraph>
      Constraint programming (CP) offers a powerful framework for efficient modeling and solving of a wide range of hard problems [59]. At the heart of efficient CP solvers are so-called global constraints that specify patterns that frequently occur in real-world problems. Efficient propagation algorithms for global constraints help speed up the solver significantly [43]. For instance, a frequently occurring pattern is that we require that certain variables must all take different values (e.g., activities requiring the same resource must all be assigned different times). Therefore most constraint solvers provide a global AllDifferent constraint and algorithms for its propagation. Unfortunately, for several important global constraints a complete propagation is NP-hard, and one switches therefore to incomplete propagation such as bound consistency [8].
     </paragraph>
     <paragraph>
      In their AAAI'08 paper, Bessière et al. [5] showed that a complete propagation of several intractable constraints can efficiently be done as long as certain natural problem parameters are small, i.e., the propagation is fixed-parameter tractable[24]. Among others, they showed fixed-parameter tractability of the AtLeast-NValue and Extended Global Cardinality (EGC) constraints parameterized by the number of “holes” in the domains of the variables. If there are no holes, then all domains are intervals and complete propagation is polynomial by classical results; thus the number of holes provides a way of scaling up the nice properties of constraints with interval domains.
     </paragraph>
     <paragraph>
      In the sequel we bring this approach a significant step forward, picking up a long-term research objective suggested by Bessière et al. [5] in their concluding remarks: whether intractable global constraints admit a reduction to a problem kernel or kernelization.
     </paragraph>
     <paragraph>
      More formally, a global constraint is defined for a set S of variables, each variable {a mathematical formula}x∈S ranges over a finite domain {a mathematical formula}dom(x) of values. For a set X of variables we write {a mathematical formula}dom(X)=⋃x∈Xdom(x). An instantiation is an assignment {a mathematical formula}α:S→dom(S) such that {a mathematical formula}α(x)∈dom(x) for each {a mathematical formula}x∈S. A global constraint defines which instantiations are legal and which are not. This definition is usually implicit, as opposed to classical constraints, which list all legal tuples. Examples of global constraints include:
     </paragraph>
     <list>
      <list-item label="1.">
       The global constraint NValue is defined over a set X of variables and a variable N and requires from a legal instantiation α that {a mathematical formula}|{α(x):x∈X}|=α(N);
      </list-item>
      <list-item label="2.">
       The global constraint AtMost-NValue is defined for fixed values of N over a set X of variables and requires from a legal instantiation α that {a mathematical formula}|{α(x):x∈X}|≤N;
      </list-item>
      <list-item label="3.">
       The global constraint Disjoint is specified by two sets of variables {a mathematical formula}X,Y and requires that {a mathematical formula}α(x)≠α(y) for each pair {a mathematical formula}x∈X and {a mathematical formula}y∈Y;
      </list-item>
      <list-item label="4.">
       The global constraint Uses is also specified by two sets of variables {a mathematical formula}X,Y and requires that for each {a mathematical formula}x∈X there is some {a mathematical formula}y∈Y such that {a mathematical formula}α(x)=α(y).
      </list-item>
      <list-item label="5.">
       The global constraint EGC is specified by a set of variables X, a set of values {a mathematical formula}D=dom(X), and a finite domain {a mathematical formula}dom(v)⊆N for each value {a mathematical formula}v∈D, and it requires that for each {a mathematical formula}v∈D we have {a mathematical formula}|{α(x)=v:x∈X}|∈dom(v).
      </list-item>
     </list>
     <paragraph>
      A global constraint C is consistent if there is a legal instantiation of its variables. The constraint C is hyper arc consistent (HAC) if for each variable {a mathematical formula}x∈scope(C) and each value {a mathematical formula}v∈dom(x), there is a legal instantiation α such that {a mathematical formula}α(x)=v (in that case we say that C supports v for x). In the literature, HAC is also called domain consistent or generalized arc consistent. The constraint C is bound consistent if when a variable {a mathematical formula}x∈scope(C) is assigned the minimum or maximum value of its domain, there are compatible values between the minimum and maximum domain value for all other variables in {a mathematical formula}scope(C). The main algorithmic problems for a global constraint C are the following: Consistency, to decide whether C is consistent, and Enforcing HAC, to remove from all domains the values that are not supported by the respective variable.
     </paragraph>
     <paragraph>
      It is clear that if HAC can be enforced in polynomial time for a constraint C, then the consistency of C can also be decided in polynomial time (we just need to see if any domain became empty). The reverse is true if for each {a mathematical formula}x∈scope(C) and {a mathematical formula}v∈dom(x), the consistency of {a mathematical formula}C∧(x←v), requiring x to be assigned the value v, can be decided in polynomial time (see [43, Theorem 17]). This is the case for most constraints of practical use, and in particular for all constraints considered below. The same correspondence holds with respect to fixed-parameter tractability. Hence, we will focus mainly on consistency.
     </paragraph>
     <paragraph>
      For several important types {a mathematical formula}T of global constraints, the problem of deciding whether a constraint of type {a mathematical formula}T is consistent is NP-hard. This includes the 5 global constraints NValue, AtMost-NValue, Disjoint, Uses, and EGC defined above (see [8]).
     </paragraph>
     <paragraph>
      Each global constraint of type {a mathematical formula}T and parameter par gives rise to a parameterized problem:
     </paragraph>
     <list>
      <list-item>
       {a mathematical formula}T-Cons(par)
      </list-item>
      <list-item>
       Instance: A global constraint C of type {a mathematical formula}T.
      </list-item>
      <list-item>
       Parameter: The integer par.
      </list-item>
      <list-item>
       Question: Is C consistent?
      </list-item>
     </list>
     <paragraph>
      Bessière et al. [5] considered {a mathematical formula}dx=|dom(X)| as parameter for NValue, {a mathematical formula}dxy=|dom(X)∩dom(Y)| as parameter for Disjoint, and {a mathematical formula}dy=|dom(Y)| as parameter for Uses. They showed that consistency checking is fixed-parameter tractable for the constraints under the respective parameterizations, i.e., the problems {a mathematical formula}NValue-Cons(dx), {a mathematical formula}Disjoint-Cons(dxy), and {a mathematical formula}Uses-Cons(dy) are fixed-parameter tractable.
     </paragraph>
     <paragraph>
      Bessière et al. [5] also showed that polynomial time algorithms for enforcing bounds consistency imply that the corresponding consistency problem is fixed-parameter tractable parameterized by the number of holes. This is the case for the global constraints NValue, AtMost-NValue, and EGC.
     </paragraph>
     <paragraph label="Definition 1">
      When D is totally ordered, a hole in a subset {a mathematical formula}D′⊆D is a couple {a mathematical formula}(u,w)∈D′×D′, such that there is a {a mathematical formula}v∈D∖D′ with {a mathematical formula}u&lt;v&lt;w and there is no {a mathematical formula}v′∈D′ with {a mathematical formula}u&lt;v′&lt;w.
     </paragraph>
     <paragraph>
      We denote the number of holes in the domain of a variable {a mathematical formula}x∈X by {a mathematical formula}#holes(x). The parameter of the consistency problem for AtMost-NValue constraints is {a mathematical formula}holes=∑x∈X#holes(x).
     </paragraph>
     <section label="6.1">
      <section-title>
       Kernel lower bounds
      </section-title>
      <paragraph>
       We show that it is unlikely that most of the FPT results of Bessière et al. [5] can be improved to polynomial kernels.
      </paragraph>
      <paragraph label="Theorem 6">
       The problems{a mathematical formula}NValue-Cons(dx),Disjoint-{a mathematical formula}Cons(dxy),{a mathematical formula}Uses-Cons(dy)do not admit polynomial kernels unless{a mathematical formula}NP⊆coNP/poly.
      </paragraph>
      <paragraph label="Proof">
       We devise a polynomial parameter transformation from SAT(vars). We use a construction of Bessière et al. [8]. Let {a mathematical formula}F={C1,…,Cm} be a CNF formula over variables {a mathematical formula}x1,…,xn. We consider the clauses and variables of F as the variables of a global constraint with domains {a mathematical formula}dom(xi)={−i,i}, and {a mathematical formula}dom(Cj)={i:xi∈Cj}∪{−i:¬xi∈Cj}. Now F can be encoded as an NValue constraint with {a mathematical formula}X={x1,…,xn,C1,…,Cm} and {a mathematical formula}dom(N)={n}. By the pigeonhole principle, a legal instantiation α for this constraint has {a mathematical formula}|{α(xi):1≤i≤n}|=N. Setting {a mathematical formula}α(xi)=i corresponds to setting the variable {a mathematical formula}xi of F to 1 and setting {a mathematical formula}α(xi)=−i corresponds to setting the variable {a mathematical formula}xi of F to 0. Now, for each {a mathematical formula}Cj∈F, {a mathematical formula}α(Cj)∈{α(xi):1≤i≤n} since only n values are available for α, and the literal corresponding to {a mathematical formula}α(Cj) satisfies the clause {a mathematical formula}Cj. Since {a mathematical formula}dx=2n we have a polynomial parameter reduction from SAT(vars) to {a mathematical formula}NValue-Cons(dx). Similarly, as observed by Bessière et al. [7], F can be encoded as a Disjoint constraint with {a mathematical formula}X={x1,…,xn} and {a mathematical formula}Y={C1,…,Cm} ({a mathematical formula}dxy≤2n), or as a Uses constraint with {a mathematical formula}X={C1,…,Cm} and {a mathematical formula}Y={x1,…,xn} ({a mathematical formula}dy=2n). Since the unparameterized problems are clearly NP-complete, and SAT(vars) is known to have no polynomial kernel unless {a mathematical formula}NP⊆coNP/poly (as remarked in the proof of Theorem 4), the result follows by Theorem 2.  □
      </paragraph>
      <paragraph>
       The Consistency problem for EGC constraints is NP-hard [55]. However, if all sets {a mathematical formula}dom(⋅) are intervals, then consistency can be checked in polynomial time using network flows [57]. By the result of Bessière et al. [5], the Consistency problem for EGC constraints is fixed-parameter tractable, parameterized by the number of holes in the sets {a mathematical formula}dom(⋅). Thus Régin's result generalizes to instances that are close to the interval case.
      </paragraph>
      <paragraph>
       However, it is unlikely that EGC constraints admit a polynomial kernel.
      </paragraph>
      <paragraph label="Theorem 7">
       EGC-Cons(holes) does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
      </paragraph>
      <paragraph label="Proof">
       We use the following result of Quimper et al. [55]: Given a CNF formula F on k variables, one can construct in polynomial time an EGC constraint {a mathematical formula}CF such that
       <list>
        for each value v of {a mathematical formula}CF, {a mathematical formula}dom(v)={0,iv} for an integer {a mathematical formula}iv&gt;0,{a mathematical formula}iv&gt;1 for at most 2k values v, andF is satisfiable if and only if {a mathematical formula}CF is consistent.We observe that this result provides a polynomial parameter reduction from
       </list>
       <paragraph>
        SAT(vars) to EGC-Cons(holes). As remarked in the proof of Theorem 4, SAT(vars) is known to have no polynomial kernel unless {a mathematical formula}NP⊆coNP/poly. Hence the theorem follows.  □
       </paragraph>
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       A polynomial kernel for NValue constraints
      </section-title>
      <paragraph>
       Beldiceanu [3] and Bessière et al. [6] decompose NValue constraints into two other global constraints: AtMost-NValue and AtLeast-NValue, which require that at most N or at least N values are used for the variables in X, respectively. The Consistency problem is NP-complete for NValue and AtMost-NValue constraints, and polynomial time solvable for AtLeast-NValue constraints.
      </paragraph>
      <paragraph>
       In this subsection, we will present a polynomial kernel for AtMost-NValue-Cons(holes).
      </paragraph>
      <list>
       <list-item>
        AtMost-NValue-Cons(holes)
       </list-item>
       <list-item>
        Instance: An instance {a mathematical formula}I=(X,D,dom,N), where {a mathematical formula}X={x1,…,xn} is a set of variables, D is a totally ordered set of values, {a mathematical formula}dom:X→2D is a map assigning a non-empty domain {a mathematical formula}dom(v)⊆D to each variable {a mathematical formula}x∈X, and an integer N.
       </list-item>
       <list-item>
        Parameter: The integer {a mathematical formula}k=#holes(X).
       </list-item>
       <list-item>
        Question: Is there a set {a mathematical formula}S⊆D, {a mathematical formula}|S|≤N, such that for every variable {a mathematical formula}x∈X, {a mathematical formula}dom(x)∩S≠∅?
       </list-item>
      </list>
      <paragraph label="Theorem 8">
       The problemAtMost-NValue-Cons(holes) has a polynomial kernel. In particular, anAtMost-NValueconstraint with k holes can be reduced in linear time to a consistency-equivalentAtMost-NValueconstraint with{a mathematical formula}O(k2)variables and{a mathematical formula}O(k2)domain values.
      </paragraph>
      <paragraph>
       The proof of the theorem is based on a kernelization algorithm that we will describe in the remaining part of this section.
      </paragraph>
      <paragraph>
       We say that a subset of D is an interval if it has no hole. An interval{a mathematical formula}I=[v1,v2] of a variable x is an inclusion-wise maximal hole-free subset of its domain. Its left endpoint{a mathematical formula}l(I) and right endpoint{a mathematical formula}r(I) are the values {a mathematical formula}v1 and {a mathematical formula}v2, respectively. Fig. 2 gives an example of an instance and its interval representation. We assume that instances are given by a succinct description, in which the domain of a variable is given by the left and right endpoint of each of its intervals. As the number of intervals of the instance {a mathematical formula}I=(X,D,dom,N) is {a mathematical formula}n+k, its size is {a mathematical formula}|I|=O(n+|D|+k). In case dom is given by an extensive list of the values in the domain of each variable, a succinct representation can be computed in linear time.
      </paragraph>
      <paragraph>
       Also, in a variant of AtMost-NValue-Cons(holes) where D is not part of the input, we may construct D by sorting the set of all endpoints of intervals in time {a mathematical formula}O((n+k)log⁡(n+k)). Since, w.l.o.g., a solution contains only endpoints of intervals, this step does not compromise the correctness.
      </paragraph>
      <paragraph>
       A greedy algorithm by Beldiceanu [3] checks the consistency of an AtMost-NValue constraint in linear time when all domains are intervals (i.e., {a mathematical formula}k=0). Further, Bessière et al. [5] have shown that Consistency (and Enforcing HAC) is fixed-parameter tractable, parameterized by the number of holes, for all constraints for which bound consistency can be enforced in polynomial time. A simple algorithm for checking the consistency of AtMost-NValue goes over all instances obtained from restricting the domain of each variable to one of its intervals, and executes the algorithm of [3] for each of these {a mathematical formula}2k instances. The running time of this algorithm is clearly bounded by {a mathematical formula}O(2k⋅|I|).
      </paragraph>
      <paragraph>
       Let {a mathematical formula}I=(X,D,dom,N) be an instance for the consistency problem for AtMost-NValue constraints. The algorithm is more intuitively described using the interval representation of the instance. The friends of an interval I are the other intervals of I's variable. An interval is optional if it has at least one friend, and required otherwise. For a value {a mathematical formula}v∈D, let {a mathematical formula}ivl(v) denote the set of intervals containing v.
      </paragraph>
      <paragraph>
       A solution for {a mathematical formula}I is a subset {a mathematical formula}S⊆D of at most N values such that there exists an instantiation assigning the values in S to the variables in X. The algorithm may detect for some value {a mathematical formula}v∈D, that, if the problem has a solution, then it has a solution containing v. In this case, the algorithm selects v, i.e., it removes all variables whose domain contains v, it removes v from D, and it decrements N by one. The algorithm may detect for some value {a mathematical formula}v∈D, that, if the problem has a solution, then it has a solution not containing v. In this case, the algorithm discards v, i.e., it removes v from every domain and from D. (Note that no new holes are created since D is replaced by {a mathematical formula}D∖{v}.) The algorithm may detect for some variable x, that every solution for {a mathematical formula}(X∖{x},D,dom|X∖{x},N) contains a value from {a mathematical formula}dom(x). In that case, it removes x.
      </paragraph>
      <paragraph>
       The algorithm sorts the intervals by increasing right endpoint (ties are broken arbitrarily). Then, it exhaustively applies the following three reduction rules.
      </paragraph>
      <list>
       <list-item>
        If there are two intervals {a mathematical formula}I,I′ such that {a mathematical formula}I′⊆I and {a mathematical formula}I′ is required, then remove the variable of I (and its intervals).
       </list-item>
       <list-item>
        If there are two values {a mathematical formula}v,v′∈D such that {a mathematical formula}ivl(v′)⊆ivl(v), then discard {a mathematical formula}v′.
       </list-item>
       <list-item>
        If {a mathematical formula}|dom(x)|=1 for some variable x, then select the value in {a mathematical formula}dom(x).
       </list-item>
      </list>
      <paragraph>
       In the example from Fig. 2, Red-⊆ removes the variables {a mathematical formula}x5 and {a mathematical formula}x8 because {a mathematical formula}x10⊆x5′ and {a mathematical formula}x7⊆x8, Red-Dom removes the values 1 and 5, Red-Unit selects 2, which deletes variables {a mathematical formula}x1 and {a mathematical formula}x2, and Red-Dom removes 3 from D. The resulting instance is depicted in Fig. 3.
      </paragraph>
      <paragraph>
       After none of the previous rules apply, the algorithm scans the remaining intervals from left to right (i.e., by increasing right endpoint). An interval that has already been scanned is either a leader or a follower of a subset of leaders. Informally, for a leader L, if a solution contains {a mathematical formula}r(L), then there is a solution containing {a mathematical formula}r(L) and the right endpoint of each of its followers.
      </paragraph>
      <paragraph>
       The algorithm scans the first intervals up to, and including, the first required interval. All these intervals become leaders.
      </paragraph>
      <paragraph>
       The algorithm then continues scanning intervals one by one. Let I be the interval that is currently scanned and {a mathematical formula}Ip be the last interval that was scanned. The active intervals are those that have already been scanned and intersect {a mathematical formula}Ip. A popular leader is a leader that is either active or has at least one active follower.
      </paragraph>
      <list>
       <list-item label="•">
        If I is optional, then I becomes a leader, the algorithm continues scanning intervals until scanning a required interval; all these intervals become leaders.
       </list-item>
       <list-item label="•">
        If I is required, then it becomes a follower of all popular leaders that do not intersect I and that have no follower intersecting I. If all popular leaders have at least two followers, then set {a mathematical formula}N:=N−1 and merge the second-last follower of each popular leader with the last follower of the corresponding leader; i.e., for every popular leader, the right endpoint of its second-last follower is set to the right endpoint of its last follower, and then the last follower of every popular leader is removed.
       </list-item>
      </list>
      <paragraph>
       After having scanned all the intervals, the algorithm exhaustively applies the reduction rules Red-⊆, Red-Dom, and Red-Unit again.
      </paragraph>
      <paragraph>
       In the example from Fig. 3, the interval of variable {a mathematical formula}x6 is merged with {a mathematical formula}x9's interval, and the interval of {a mathematical formula}x7 with the interval of {a mathematical formula}x10. Red-Dom then removes the values 7 and 8, resulting in the instance depicted in Fig. A.4.
      </paragraph>
      <paragraph>
       The correctness and performance guarantee of this kernelization algorithm are proved in Appendix A. In particular, for the correctness, we prove that a solution S for an instance {a mathematical formula}I can be obtained from a solution {a mathematical formula}S′ for an instance {a mathematical formula}I′ that is obtained from {a mathematical formula}I by one merge-operation by adding to {a mathematical formula}S′ one value that is common to all second-last followers of the popular leaders that were merged. We can easily bound the number of leaders by 4k and we prove that each leader has at most 4k followers. Since each interval is a leader or a follower of at least one leader, this bounds the total number of intervals by {a mathematical formula}O(k2). Using the succinct description of the domains, the size of the kernel is {a mathematical formula}O(k2). We also give some details for a linear-time implementation of the algorithm.
      </paragraph>
      <paragraph label="Remark">
       Denoting {a mathematical formula}var(v)={x∈X:v∈dom(x)}, Rule Red-Dom can be generalized to discard any {a mathematical formula}v′∈D for which there exists a {a mathematical formula}v∈D such that {a mathematical formula}var(v′)⊆var(v) at the expense of a higher running time.
      </paragraph>
      <paragraph>
       The kernel for AtMost-NValue-Cons(holes) can now be used to derive a kernel for NValue-Cons(holes).
      </paragraph>
      <paragraph label="Corollary 1">
       The problemNValue-Cons(holes) has a polynomial kernel. In particular, anNValueconstraint with k holes can be reduced in{a mathematical formula}O((|X|+|D|)ω/2)time to a consistency-equivalentNValueconstraint with{a mathematical formula}O(k2)variables and{a mathematical formula}O(k2)domain values, where{a mathematical formula}ω&lt;2.3729is the exponent of matrix multiplication.
      </paragraph>
      <paragraph label="Proof">
       As in [6], we determine the largest possible value for N if its domain were the set of all integers. This can be done in {a mathematical formula}O((|X|+|D|)ω/2) time [49], [64] by computing a maximum matching in the graph whose vertices are {a mathematical formula}X∪D with an edge between {a mathematical formula}x∈X and {a mathematical formula}v∈D iff {a mathematical formula}v∈dom(x). Suppose this largest possible value is {a mathematical formula}N+. Now, set {a mathematical formula}dom(N):={v∈dom(N):v≤N+}, giving a consistency-equivalent NValue constraint. Note that if this constraint has a legal instantiation α with {a mathematical formula}α(N)≤max⁡(dom(N)), then it has a legal instantiation {a mathematical formula}α′ with {a mathematical formula}α′(N)=max⁡(dom(N)). Therefore, it suffices to compute a kernel for AtMost-NValue-Cons(holes) with the same variables and domains and value {a mathematical formula}N=max⁡(dom(N)), and return it. □
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Improved FPT algorithm using the kernel
      </section-title>
      <paragraph>
       Using the kernel from Theorem 8 and the simple algorithm described in the beginning of this section, one arrives at an {a mathematical formula}O(2kk2+|I|) time algorithm for checking the consistency of an AtMost-NValue constraint. Borrowing ideas from the kernelization algorithm, we now reduce the exponential dependency on k in the running time. The speed-ups due to this branching algorithm and the kernelization algorithm lead to a speed-up for enforcing HAC for AtMost-NValue constraints (by Corollary 2) and for enforcing HAC for NValue constraints (by the decomposition of [6]).
      </paragraph>
      <paragraph label="Theorem 9">
       The Consistency problem forAtMost-NValueconstraints admits an{a mathematical formula}O(φkk2+|I|)time algorithm, where k is the number of holes in the domains of the input instance{a mathematical formula}I, and{a mathematical formula}φ=1+52&lt;1.6181.
      </paragraph>
      <paragraph label="Proof">
       The first step of the algorithm invokes the kernelization algorithm and obtains an equivalent instance {a mathematical formula}I′ with {a mathematical formula}O(k2) intervals in time {a mathematical formula}O(|I|).Now, we describe a branching algorithm checking the consistency of {a mathematical formula}I′. Let {a mathematical formula}I1 denote the first interval of {a mathematical formula}I′ (in the ordering by increasing right endpoint). {a mathematical formula}I1 is optional. Let {a mathematical formula}I1 denote the instance obtained from {a mathematical formula}I′ by selecting {a mathematical formula}r(I1) and exhaustively applying Reduction Rules Red-Dom and Red-Unit. Let {a mathematical formula}I2 denote the instance obtained from {a mathematical formula}I′ by removing {a mathematical formula}I1 (if {a mathematical formula}I1 had exactly one friend, this friend becomes required) and exhaustively applying Reduction Rules Red-Dom and Red-Unit. Clearly, {a mathematical formula}I′ is consistent if and only if {a mathematical formula}I1 or {a mathematical formula}I2 is consistent.Note that both {a mathematical formula}I1 and {a mathematical formula}I2 have at most {a mathematical formula}k−1 holes. If either {a mathematical formula}I1 or {a mathematical formula}I2 has at most {a mathematical formula}k−2 holes, the algorithm recursively checks whether at least one of {a mathematical formula}I1 and {a mathematical formula}I2 is consistent. If both {a mathematical formula}I1 and {a mathematical formula}I2 have exactly {a mathematical formula}k−1 holes, we note that in {a mathematical formula}I′,
       <list>
        {a mathematical formula}I1 has one friend,no other optional interval intersects {a mathematical formula}I1, andthe first interval of both {a mathematical formula}I1 and {a mathematical formula}I2 is {a mathematical formula}If, which is the third optional interval in {a mathematical formula}I′ if the second optional interval is the friend of {a mathematical formula}I1, and the second optional interval otherwise.The recursive calls of the algorithm may be represented by a search tree labeled with the number of holes of the instance. As the algorithm either branches into only one subproblem with at most
       </list>
       <paragraph>
        {a mathematical formula}k−1 holes, or two subproblems with at most {a mathematical formula}k−1 and at most {a mathematical formula}k−2 holes, respectively, the number of leaves of this search tree is {a mathematical formula}T(k)≤T(k−1)+T(k−2), with {a mathematical formula}T(0)=T(1)=1. Using standard techniques in the analysis of exponential time algorithms (see, e.g., [33, Chapter 2] and [35, Lemma 2.3]), it suffices to find a value {a mathematical formula}c&gt;1 for the base of the exponential function bounding the running time, that we will minimize, such that{a mathematical formula} or, equivalently, such that{a mathematical formula} It now suffices to find the unique positive real root of {a mathematical formula}x2−x−1, which is {a mathematical formula}φ=1+52&lt;1.6181, to determine the optimal value of c for this analysis.Since the size of the search tree is {a mathematical formula}O(φk) and the number of operations executed at each node of the search tree is {a mathematical formula}O(k2), the running time of the branching algorithm can be upper bounded by {a mathematical formula}O(φkk2).  □
       </paragraph>
      </paragraph>
      <paragraph>
       For the example of Fig. A.4, the instances {a mathematical formula}I1 and {a mathematical formula}I2 are computed by selecting the value 4, and removing the interval {a mathematical formula}x3, respectively. The reduction rules select the value 9 for {a mathematical formula}I1 and the values 6 and 10 for {a mathematical formula}I2. Both instances start with the interval {a mathematical formula}x11, and the algorithm recursively solves {a mathematical formula}I1 only, where the values 12 and 13 are selected, leading to the solution {a mathematical formula}{4,9,12,13} for the kernelized instance, which corresponds to the solution {a mathematical formula}{2,4,7,9,12,13} for the instance of Fig. 2.
      </paragraph>
      <paragraph label="Corollary 2">
       HAC for anAtMost-NValueconstraint can be enforced in time{a mathematical formula}O(φk⋅k2⋅|D|+|I|⋅|D|), where k is the number of holes in the domains of the input instance{a mathematical formula}I=(X,D,dom,N), and{a mathematical formula}φ=1+52&lt;1.6181.
      </paragraph>
      <paragraph label="Proof">
       We first remark that if a value v can be filtered from the domain of a variable x (i.e., v has no support for x), then v can be filtered from the domain of all variables, as for any legal instantiation α with {a mathematical formula}α(x′)=v, {a mathematical formula}x′∈X∖{x}, the assignment obtained from α by setting {a mathematical formula}α(x):=v is a legal instantiation as well. Also, filtering the value v creates no new holes as the set of values can be set to {a mathematical formula}D∖{v}.Now we enforce HAC by applying {a mathematical formula}O(|D|) times the algorithm from Theorem 9. Assume the instance {a mathematical formula}I=(X,D,dom,N) is consistent. If {a mathematical formula}(X,D,dom,N−1) is consistent, then no value can be filtered. Otherwise, check, for each {a mathematical formula}v∈D, whether the instance obtained from selecting v is consistent and filter v if this is not the case.  □
      </paragraph>
      <paragraph>
       Using the same reasoning as in Corollary 1, we now obtain the following corollary for NValue.
      </paragraph>
      <paragraph label="Corollary 3">
       HAC for anNValueconstraint can be enforced in time{a mathematical formula}O((φk⋅k2+(|X|+|D|)ω/2)⋅|D|), where k is the number of holes in the domains of the input instance{a mathematical formula}I=(X,D,dom,N),{a mathematical formula}φ=1+52&lt;1.6181, and{a mathematical formula}ω&lt;2.3729is the exponent of matrix multiplication.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Bayesian reasoning
     </section-title>
     <paragraph>
      Bayesian networks (BNs) have emerged as a general representation scheme for uncertain knowledge [54]. A BN models a set of stochastic variables, the independencies among these variables, and a joint probability distribution over these variables. For simplicity we consider the important special case where the stochastic variables are Boolean. The variables and independencies are modeled in the BN by a directed acyclic graph {a mathematical formula}G=(V,A), the joint probability distribution is given by a table {a mathematical formula}Tv for each node {a mathematical formula}v∈V which defines a probability {a mathematical formula}Tv|U for each possible instantiation {a mathematical formula}U=(d1,…,ds)∈{true,false}s of the parents {a mathematical formula}v1,…,vs of v in G. The probability {a mathematical formula}Pr(U) of a complete instantiation U of the variables of G is given by the product of {a mathematical formula}Tv|U over all variables v. We consider the problem Positive-BN-Inference which takes as input a Boolean BN {a mathematical formula}(G,T) and a variable v, and asks whether {a mathematical formula}Pr(v=true)&gt;0. The problem is NP-complete [19] and moves from NP to #P if we ask to compute {a mathematical formula}Pr(v=true)[60]. The problem can be solved in polynomial time if the BN is singly connected, i.e., if there is at most one undirected path between any two variables [53]. It is natural to parametrize the problem by the number of variables one must delete in order to make the BN singly connected (the deleted variables form a loop cutset). This yields the following parameterized problem.
     </paragraph>
     <list>
      <list-item>
       Positive-BN-Inference(loop cutset size)
      </list-item>
      <list-item>
       Instance: A Boolean BN {a mathematical formula}(G,T), a variable v, and a loop cutset S of size k.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Is {a mathematical formula}Pr(v=true)&gt;0?
      </list-item>
     </list>
     <paragraph>
      Again we also state a related recognition problem.
     </paragraph>
     <list>
      <list-item>
       Rec-Positive-BN-Inference(loop cutset size)
      </list-item>
      <list-item>
       Instance: A Boolean BN {a mathematical formula}(G,T) and an integer {a mathematical formula}k≥0.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Does {a mathematical formula}(G,T) has a loop cutset of size ≤k?
      </list-item>
     </list>
     <paragraph>
      Now, Positive-BN-Inference(loop cutset size) is easily seen to be fixed-parameter tractable as we can determine whether {a mathematical formula}Pr(v=true)&gt;0 by taking the maximum of {a mathematical formula}Pr(v=true|U) over all {a mathematical formula}2k possible instantiations of the k cutset variables, each of which requires processing of a singly connected network. However, although fixed-parameter tractable, it is unlikely that the problem admits a polynomial kernel.
     </paragraph>
     <paragraph label="Theorem 10">
      Positive-BN-Inference(loop cutset size) does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
     </paragraph>
     <paragraph label="Proof">
      We give a polynomial parameter transformation from SAT(vars) and apply Theorem 2. The reduction is based on the reduction from 3SAT given by Cooper [19]. Let F be a CNF formula on n variables. We construct a BN {a mathematical formula}(G,T) such that for a variable v we have {a mathematical formula}Pr(v=true)&gt;0 if and only if F is satisfiable. Cooper uses input nodes{a mathematical formula}ui for representing variables of F, clause nodes{a mathematical formula}ci for representing the clauses of F, and conjunction nodes{a mathematical formula}di for representing the conjunction of the clauses. For instance, if F has three clauses and four variables, then Cooper's reduction produces a BN {a mathematical formula}(G,T) where G has the following shape:{a mathematical formula} Clearly, the input nodes form a loop cutset of G. However, in order to get a polynomial parameter transformation from SAT(vars) we must allow in F that clauses contain an arbitrary number of literals, not just three. If we apply Cooper's reduction directly, then a single clause node {a mathematical formula}ci with many parents requires a table {a mathematical formula}Tci of exponential size. To overcome this difficulty we simply split clause nodes {a mathematical formula}ci containing more than 3 literals into several clause nodes, as indicated below, where the last one feeds into a conjunction node {a mathematical formula}di.{a mathematical formula} It remains to observe that the set of input nodes {a mathematical formula}E={u1,…,un} still form a loop cutset of the constructed BN, hence we have indeed a polynomial parameter transformation from SAT(vars) to Positive-BN-Inference(loop cutset size). The result follows by Theorem 2.  □
     </paragraph>
     <paragraph>
      Let us now turn to the recognition problem Rec-Positive-BN-Inference(loop cutset size).
     </paragraph>
     <paragraph label="Proposition 3">
      Rec-Positive-BN-Inference(loop cutset size) admits a polynomial kernel with{a mathematical formula}O(k2)nodes.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}((G,T),k) be an instance of Rec-Positive-BN-Inference(loop cutset size). We note that loop cutsets of {a mathematical formula}(G,T) are just the so-called feedback vertex sets of G. Hence we can apply a known kernelization algorithm for feedback vertex sets [16] to G and obtain a kernel {a mathematical formula}(G′,k) with at most {a mathematical formula}O(k2) many vertices. We translate this into an instance {a mathematical formula}(G′,T′,k′) of Rec-Positive-BN-Inference(loop cutset size) by taking an arbitrary table {a mathematical formula}T′.  □
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Nonmonotonic reasoning
     </section-title>
     <paragraph>
      Logic programming with negation under the stable model semantics is a well-studied form of nonmonotonic reasoning [39], [47]. A (normal) logic program P is a finite set of rules r of the form{a mathematical formula} where {a mathematical formula}h,ai,bi are atoms, where h forms the head and the {a mathematical formula}ai,bi from the body of r. We write {a mathematical formula}H(r)=h, {a mathematical formula}B+(r)={a1,…,am}, and {a mathematical formula}B−(r)={b1,…,bn}. Let I be a finite set of atoms. The GF reduct{a mathematical formula}PI of a logic program P under I is the program obtained from P by removing all rules r with {a mathematical formula}B−(r)∩I≠∅, and removing from the body of each remaining rule {a mathematical formula}r′ all literals ¬b with {a mathematical formula}b∈I. I is a stable model of P if I is a minimal model of {a mathematical formula}PI, i.e., if (i) for each rule {a mathematical formula}r∈PI with {a mathematical formula}B+(r)⊆I we have {a mathematical formula}H(r)∈I, and (ii) there is no proper subset of I with this property. The undirected dependency graph{a mathematical formula}U(P) of P is formed as follows. We take the atoms of P as vertices and add an edge {a mathematical formula}x−y between two atoms {a mathematical formula}x,y if there is a rule {a mathematical formula}r∈P with {a mathematical formula}H(r)=x and {a mathematical formula}y∈B+(r), and we add a path {a mathematical formula}x−u−y if {a mathematical formula}H(r)=x and {a mathematical formula}y∈B−(r) (u is a new vertex of degree 2). The feedback width of P is the size of a smallest set V of atoms such that every cycle of {a mathematical formula}U(P) runs through an atom in V (such a set V is called a feedback vertex set).
     </paragraph>
     <paragraph>
      A fundamental computational problems is Stable Model Existence (SME), which asks whether a given normal logic program has a stable model. The problem is well-known to be NP-complete [48]. Gottlob et al. [41] considered the following parameterization of the problem and showed fixed-parameter tractability (see [31] for generalizations).
     </paragraph>
     <list>
      <list-item>
       SME(feedback width)
      </list-item>
      <list-item>
       Instance: A logic program P and feedback vertex set V of size k.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Does P have a stable model?
      </list-item>
     </list>
     <paragraph>
      Again we also state a related recognition problem.
     </paragraph>
     <list>
      <list-item>
       Rec-SME(feedback width)
      </list-item>
      <list-item>
       Instance: A logic program P and an integer {a mathematical formula}k≥0.
      </list-item>
      <list-item>
       Parameter: The integer k.
      </list-item>
      <list-item>
       Question: Does P have a feedback vertex set of size at most k?
      </list-item>
     </list>
     <paragraph label="Theorem 11">
      We show that the result of Gottlob et al. [41] cannot be strengthened towards a polynomial kernel. SME(feedback width) does not admit a polynomial kernel unless{a mathematical formula}NP⊆coNP/poly.
     </paragraph>
     <paragraph label="Proof">
      We give a polynomial parameter transformation from SAT(vars) to {a mathematical formula}SME(feedback width) using a construction of Niemelä [50]. Given a CNF formula F on n variables, we construct a logic program P as follows. For each variable x of F we take two atoms x and {a mathematical formula}xˆ and include the rules {a mathematical formula}(xˆ←¬x) and {a mathematical formula}(x←¬xˆ); for each clause C of F we take an atom c and include for each positive literal a of C the rule {a mathematical formula}(c←a), and for each negative literal ¬a of C the rule {a mathematical formula}(c←aˆ); finally, we take two atoms s and f and include the rule {a mathematical formula}(f←¬f∧¬s) and for each clause C of F the rule {a mathematical formula}(s←¬c). The formula F is satisfiable if and only if P has a stable model [50]. It remains to observe that each cycle of {a mathematical formula}U(P) runs through a vertex in {a mathematical formula}V={x,xˆ:x∈vars(F)}, hence the feedback width of P is at most 2n. Hence we have a polynomial parameter transformation from SAT(vars) to SME(feedback width). The result follows by Theorem 2.  □
     </paragraph>
     <paragraph>
      Using a similar approach as for Proposition 3 we can establish the following result.
     </paragraph>
     <paragraph label="Proposition 4">
      Rec-SME(feedback width) admits a polynomial kernel with{a mathematical formula}O(k2)atoms.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Proof of Theorem 8
     <paragraph>
      In this appendix, we prove Theorem 8 by proving the correctness of the algorithm, upper bounding the size of the kernel, and analyzing its running time.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}I′=(X′,D′,dom′,N′) be the instance resulting from applying one operation of the kernelization algorithm to an instance {a mathematical formula}I=(X,D,dom,N). An operation is an instruction which modifies the instance: Red-⊆, Red-Dom, Red-Unit, and merge. We show that there exists a solution S for {a mathematical formula}I if and only if there exists a solution {a mathematical formula}S′ for {a mathematical formula}I′. A solution is nice if each of its elements is the right endpoint of some interval. Clearly, for every solution, a nice solution of the same size can be obtained by shifting each value to the next right endpoint of an interval. Thus, when we construct {a mathematical formula}S′ from S (or vice versa), we may assume that S is nice.
     </paragraph>
     <paragraph>
      Reduction Rule Red-⊆ is sound because a solution for {a mathematical formula}I is a solution for {a mathematical formula}I′ and vice versa, because any solution {a mathematical formula}I′ contains a value v of {a mathematical formula}I⊆I′, as I is required. Reduction Rule Red-Dom is correct because if {a mathematical formula}v′∈S, then {a mathematical formula}S′:=(S∖{v′})∪{v} is a solution for {a mathematical formula}I′ and for {a mathematical formula}I. Reduction Rule Red-Unit is obviously correct ({a mathematical formula}S=S′∪dom(x)).
     </paragraph>
     <paragraph>
      After having applied these 3 reduction rules, observe that the first interval is optional and contains only one value. Suppose the algorithm has started scanning intervals. By construction, the following properties apply to {a mathematical formula}I′.
     </paragraph>
     <paragraph label="Property 1">
      A follower does not intersect any of its leaders.
     </paragraph>
     <paragraph label="Property 2">
      If{a mathematical formula}I,I′are two distinct followers of the same leader, then I and{a mathematical formula}I′do not intersect.
     </paragraph>
     <paragraph label="Claim 1">
      Before proving the correctness of the merge operation, let us first show that the subset of leaders of a follower is not empty. Every interval that has been scanned is either a leader or a follower of at least one leader.
     </paragraph>
     <paragraph label="Proof">
      First, note that Red-Dom ensures that each domain value in D is the left endpoint of some interval and the right endpoint of some interval. We show that when an interval I is scanned it either becomes a leader or a follower of at least one leader. By induction, assume this is the case for all previously scanned intervals. Denote by {a mathematical formula}Ip the interval that was scanned prior to I. If {a mathematical formula}Ip or I is optional, then I becomes a leader. Suppose I and {a mathematical formula}Ip are required. We have that {a mathematical formula}l(I)&gt;l(Ip), otherwise I would have been removed by Red-⊆. By Rule Red-Dom, there is some interval {a mathematical formula}Iℓ with {a mathematical formula}r(Iℓ)=l(Ip). If {a mathematical formula}Iℓ is a leader, I becomes a follower of {a mathematical formula}Iℓ; otherwise I becomes a follower of {a mathematical formula}Iℓ's leader.  □
     </paragraph>
     <paragraph>
      We will now prove the correctness of the merge operation. Recall that {a mathematical formula}I′ is an instance obtained from {a mathematical formula}I by one application of the merge operation. Let I denote the interval that is scanned when the merge operation is applied. At this computation step, each popular leader has at least two followers and the algorithm merges the last two followers of each popular leader and decrements N by one. Let {a mathematical formula}F2 denote the set of all intervals that are the second-last follower of a popular leader, and {a mathematical formula}F1 the set of all intervals that are the last follower of a popular leader before merging. Let M denote the set of merged intervals. Clearly, every interval of {a mathematical formula}F1∪F2∪M is required as all followers are required.
     </paragraph>
     <paragraph label="Proof">
      Every interval in{a mathematical formula}F1intersects{a mathematical formula}l(I).Let {a mathematical formula}I1∈F1. By construction, {a mathematical formula}r(I1)∈I, as I becomes a follower of every popular leader that has no follower intersecting I, and no follower has a right endpoint larger than {a mathematical formula}r(I). Moreover, {a mathematical formula}l(I1)≤l(I) as no follower is a strict subset of I by Red-⊆ and the fact that all followers are required.  □
     </paragraph>
     <paragraph>
      The correctness of the merge operation will follow from the next two lemmas.
     </paragraph>
     <paragraph label="Lemma 2">
      If S is a nice solution for{a mathematical formula}I, then there exists a solution{a mathematical formula}S′for{a mathematical formula}I′with{a mathematical formula}S′⊆S.
     </paragraph>
     <paragraph label="Proof">
      Let {a mathematical formula}I− be the interval of {a mathematical formula}F2 with the largest right endpoint. Let L be a leader of {a mathematical formula}I−. By construction and Red-⊆, L is a leader of I as well and is therefore popular. Let {a mathematical formula}t1∈S∩I be the smallest value of S that intersects I and let {a mathematical formula}t2∈S∩I− be the largest value of S that intersects {a mathematical formula}I−. By Property 2, we have that {a mathematical formula}t2&lt;t1.The set S contains no value{a mathematical formula}t0such that{a mathematical formula}t2&lt;t0&lt;t1.For the sake of contradiction, suppose S contains a value {a mathematical formula}t0 such that {a mathematical formula}t2&lt;t0&lt;t1. Since S is nice, {a mathematical formula}t0 is the right endpoint of some interval {a mathematical formula}I0. Since {a mathematical formula}t2 is the rightmost value intersecting S and any interval in {a mathematical formula}F2, the interval {a mathematical formula}I0 is not in {a mathematical formula}F2. Since {a mathematical formula}I0 has already been scanned, and was scanned after every interval in {a mathematical formula}F2, the interval {a mathematical formula}I0 is in {a mathematical formula}F1. However, by Lemma 1, {a mathematical formula}I0 intersects {a mathematical formula}l(I). Since no scanned interval has a larger right endpoint than I, we have that {a mathematical formula}t0∈S∩I, which contradicts the fact that {a mathematical formula}t1 is the smallest value in {a mathematical formula}S∩I and that {a mathematical formula}t0&lt;t1.  □Suppose{a mathematical formula}I1∈F1and{a mathematical formula}I2∈F2are the last and second-last follower of a popular leader{a mathematical formula}L′, respectively. Let{a mathematical formula}M12∈Mdenote the interval obtained from merging{a mathematical formula}I2with{a mathematical formula}I1. If{a mathematical formula}t2∈I2, then{a mathematical formula}t1∈M12.For the sake of contradiction, assume {a mathematical formula}t2∈I2, but {a mathematical formula}t1∉M12. As {a mathematical formula}t2&lt;t1, we have that {a mathematical formula}t1&gt;r(M12)=r(I1). But then S is not a solution as {a mathematical formula}S∩I1=∅ by Claim 2 and the fact that {a mathematical formula}t2&lt;l(I1).  □If{a mathematical formula}I′is an interval with{a mathematical formula}t2∈I′, then{a mathematical formula}I′∈F2∪F1.First, suppose {a mathematical formula}I′ is a leader. As every leader has at least two followers when I is scanned, {a mathematical formula}I′ has two followers whose left endpoint is larger than {a mathematical formula}r(I′)≥t2 (by Property 1) and smaller than {a mathematical formula}l(I)≤t1 (by Red-⊆). Thus, at least one of them is included in the interval {a mathematical formula}(t2,t1) by Property 2, which contradicts S being a solution by Claim 2.Similarly, if {a mathematical formula}I′ is a follower of a popular leader, but not among the last two followers of any popular leader, Claim 2 leads to a contradiction as well.Finally, if {a mathematical formula}I′ is a follower, but has no popular leader, then it is to the left of some popular leader, and thus to the left of {a mathematical formula}t2.  □Consider the set {a mathematical formula}T2 of intervals that intersect {a mathematical formula}t2. By Claim 4, we have that {a mathematical formula}T2⊆F2∪F1. For every interval {a mathematical formula}I′∈T2∩F2, the corresponding merged interval of {a mathematical formula}I′ intersects {a mathematical formula}t1 by Claim 3. For every interval {a mathematical formula}I′∈T2∩F1, and every interval {a mathematical formula}I″∈F2 with which {a mathematical formula}I′ is merged, S contains some value {a mathematical formula}x∈I″ with {a mathematical formula}x&lt;t2. Thus, {a mathematical formula}S′:=S∖{t2} is a solution for {a mathematical formula}I′.  □
     </paragraph>
     <paragraph label="Lemma 3">
      If{a mathematical formula}S′is a nice solution for{a mathematical formula}I′, then there exists a solution S for{a mathematical formula}Iwith{a mathematical formula}S′⊆S.
     </paragraph>
     <paragraph label="Proof">
      As in the previous proof, consider the step where the kernelization algorithm applies the merge operation. Recall that the currently scanned interval is I. Let {a mathematical formula}F2 and {a mathematical formula}F1 denote the set of all intervals that are the second-last and last follower of a popular leader before merging, respectively. Let M denote the set of merged intervals.By Lemma 1, every interval of M intersects {a mathematical formula}l(I). On the other hand, every interval of {a mathematical formula}I′ whose right endpoint intersects I is in M, by construction. Thus, {a mathematical formula}S′ contains the right endpoint of some interval of M. Let {a mathematical formula}t1 denote the smallest such value, and let {a mathematical formula}I1 denote the interval of {a mathematical formula}I with {a mathematical formula}r(I1)=t1 (due to Red-⊆, there is a unique such interval). Let {a mathematical formula}I2 denote the interval of {a mathematical formula}I with the smallest right endpoint such that there is a leader L whose second-last follower is {a mathematical formula}I2 and whose last follower is {a mathematical formula}I1, and let {a mathematical formula}t2:=r(I2).Let{a mathematical formula}I1′∈F1and{a mathematical formula}I2′∈F2be two intervals from{a mathematical formula}Ithat are merged into one interval{a mathematical formula}M12′of{a mathematical formula}I′. If{a mathematical formula}t1∈M12′, then{a mathematical formula}t2∈I2′.For the sake of contradiction, suppose {a mathematical formula}t1∈M12′ but {a mathematical formula}t2∉I2′. We consider two cases. In the first case, {a mathematical formula}I2′⊆(t2,l(I1′)). But then, {a mathematical formula}I2′ would have become a follower of L, which contradicts that {a mathematical formula}I1 is the last follower of L. In the second case, {a mathematical formula}r(I2′)&lt;t2. But then, {a mathematical formula}I1 is a follower of the same leader as {a mathematical formula}I1′, as {a mathematical formula}l(I1)≤l(I1′), and thus {a mathematical formula}I1=I1′. By the definition of {a mathematical formula}I2, however, {a mathematical formula}t2=r(I2)≤r(I2′), a contradiction.  □By the previous claim, a solution S for {a mathematical formula}I is obtained from a solution {a mathematical formula}S′ for {a mathematical formula}I′ by setting {a mathematical formula}S:=S′∪{t2}.  □
     </paragraph>
     <paragraph>
      After having scanned all the intervals, Reduction Rules Red-⊆, Red-Dom, and Red-Unit are applied again, and we have already proved their correctness.
     </paragraph>
     <paragraph>
      Thus, the kernelization algorithm returns an equivalent instance. To bound the kernel size by a polynomial in k, let {a mathematical formula}I⁎=(V⁎,D⁎,dom⁎,N⁎) be the instance resulting from applying the kernelization algorithm to an instance {a mathematical formula}I=(V,D,dom,N).
     </paragraph>
     <paragraph label="Property 3">
      The instances{a mathematical formula}Iand{a mathematical formula}I⁎have at most 2k optional intervals.
     </paragraph>
     <paragraph>
      Property 3 holds for {a mathematical formula}I as every optional interval of a variable x is adjacent to at least one hole and each hole is adjacent to two optional intervals of x. It holds for {a mathematical formula}I⁎ as the kernelization algorithm introduces no holes.
     </paragraph>
     <paragraph label="Lemma 4">
      The instance{a mathematical formula}I⁎has at most 4k leaders.
     </paragraph>
     <paragraph label="Proof">
      Consider the unique step of the algorithm that creates leaders. An optional interval is scanned, the algorithm continues scanning intervals until scanning a required interval, and all these scanned intervals become leaders. As every interval is scanned only once, we have that for every optional interval there are at most 2 leaders. By Property 3, the number of leaders is thus at most 4k.  □
     </paragraph>
     <paragraph label="Lemma 5">
      Every leader has at most 4k followers.
     </paragraph>
     <paragraph label="Proof">
      Consider all steps where a newly scanned interval becomes a follower, but is not merged with another interval. In each of these steps, the popular leader {a mathematical formula}Lr with the rightmost right endpoint either
     </paragraph>
     <list>
      <list-item label="(a)">
       has no follower and intersects I, or
      </list-item>
      <list-item label="(b)">
       has no follower and does not intersect I, or
      </list-item>
      <list-item label="(c)">
       has one follower and intersects I.
      </list-item>
     </list>
     <paragraph>
      As, by Claim 1, every interval of {a mathematical formula}I⁎ is either a leader or a follower of at least one leader, Lemma 4, Lemma 5 imply that {a mathematical formula}I⁎ has {a mathematical formula}O(k2) intervals, and thus {a mathematical formula}|X⁎|=O(k2). Because of Reduction Rule Red-Dom, every value in {a mathematical formula}D⁎ is the right endpoint and the left endpoint of some interval, and thus, {a mathematical formula}|D⁎|=O(k2).
     </paragraph>
     <paragraph>
      This bounds the kernel size, and we will now show that the algorithm can be implemented to run in linear time. First, using a counting sort algorithm with satellite data (see, e.g., [20]), the initial sorting of the {a mathematical formula}n+k intervals can be done in time {a mathematical formula}O(n+|D|+k). To facilitate the application of Red-⊆, counting sort is used a second time to also sort by increasing left endpoint the sets of intervals with coinciding right endpoint. An optimized implementation applies Red-⊆, Red-Dom and Red-Unit simultaneously in one pass through the intervals, as one rule might trigger another. To guarantee a linear running time for the scan-and-merge phase of the algorithm, only the first follower of a leader stores a pointer to the leader; all other followers store a pointer to the previous follower. This proves Theorem 8.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>