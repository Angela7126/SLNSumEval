<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Computing and restoring global inverse consistency in interactive constraint satisfaction.
   </title>
   <abstract>
    Some applications require the interactive resolution of a constraint problem by a human user. In such cases, it is highly desirable that the person who interactively solves the problem is not given the choice to select values that do not lead to solutions. We call this property global inverse consistency. Existing systems simulate this either by maintaining arc consistency after each assignment performed by the user or by compiling offline the problem as a multi-valued decision diagram. In this article, we define several questions related to global inverse consistency and analyze their complexity. Despite their theoretical intractability, we propose several algorithms for enforcing and restoring global inverse consistency and we show that the best version is efficient enough to be used in an interactive setting on several configuration and design problems.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Constraint Programming (CP) is widely used to express and solve combinatorial problems. Once a problem is modeled as a constraint network, efficient solving techniques generate a solution satisfying the constraints, if such a solution exists. However, there are situations where the user has strong opinions about the way to build good solutions to the problem but some of the desirable/undesirable combinations will become clear only once some of the variables are assigned. In this case, the constraint solver should be there to assist the user in the solution design and to ensure her choices remain in the feasible space, removing the combinatorial complexity from her shoulders. See the Synthia system for protein design as an early example of using CP to interactively solve a problem [2]. Another well known example of such an interactive solving of constraint-based models is product configuration [3], [4]. The person modeling the product as a constraint network for the company knows its technical and marketing requirements. She models the feasibility, availability and/or marketing constraints about the product. This constraint network captures the catalog of possible products, which may contain billions of solutions, but in an intentional and compact way. Nevertheless, the modeler does not know the constraints or preferences of the customer(s). This is the customer who will look for solutions, with her own constraints and preferences on the price, the color, or any other configurable feature.
     </paragraph>
     <paragraph>
      These applications refer to an interactive solving process where the user selects values for variables according to her own preferences and the system checks the constraints of the network, until all variables are assigned and satisfy all constraints of the network. This solving policy raises an important issue: the person who interactively solves the problem should not be led to a dead-end where satisfying all constraints of the network is impossible. Existing interactive solving systems address this issue either by compiling the constraint network into a multi-valued decision diagram (MDD) at the modeling phase [4], [5], [6] or by enforcing arc consistency on the network after each assignment performed by the user [2]. Compiling the constraint network as an MDD can require a significant amount of time and space. That is why compilation is performed offline (before the solving session). As a consequence, configurators based on an MDD compilation are restricted to static constraint networks: non-unary constraints can neither be added nor removed once the network is compiled. It is thus not possible for the user to perform complex requirements, e.g. she is interested in traveling to Venezia only during the carnival period. Arc and dynamic arc consistencies require a lighter computational effort but the user can be trapped in dead-ends, which is very risky from a commercial point of view. It has been shown in [7] that arc consistency (and even higher levels of local consistency) can be very bad approximations of the ideal state where all values remaining in the network can be extended to solutions.
     </paragraph>
     <paragraph>
      The message of our article is that for many of the problems that require interactive solving of the problem, and especially for real problems, it is computationally feasible to maintain the domains of the variables in a state where they only contain those values which belong to a complete solution extending the current choices of the user. Inspired by the nomenclature used in [8] and [9], we call this level of consistency global inverse consistency (GIC).
     </paragraph>
     <paragraph>
      Our contribution addresses several aspects. First, we formally characterize the questions that underlie the interactive constraint solving loop and we show that they are all NP-hard. Second, we provide several algorithms with increasing sophistication to address those tasks. Third, we experimentally show that the most efficient of our algorithms is efficient enough to be used in an interactive constraint solving loop of several non-trivial configuration and design problems.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      A (discrete) constraint network (CN) N is composed of a finite set of n variables, denoted by {a mathematical formula}vars(N), and a finite set of e constraints, denoted by {a mathematical formula}cons(N). Each variable x has a domain which is the finite set of values that can be assigned to x. The initial domain of a variable x is denoted by {a mathematical formula}dominit(x) whereas the current domain of x is denoted by {a mathematical formula}dom(x); we always have {a mathematical formula}dom(x)⊆dominit(x). Sometimes, we use {a mathematical formula}domN(x) to denote the domain of x in the context of the CN N. The maximum domain size of a variable in a given CN is denoted by d. To simplify, a variable–value pair {a mathematical formula}(x,a) such that {a mathematical formula}x∈vars(N) and {a mathematical formula}a∈domN(x) is called a value of N; we note {a mathematical formula}values(N)={(x,a)|x∈vars(N)∧a∈domN(x)}. Each constraint c involves an ordered set of variables, called the scope of c and denoted by {a mathematical formula}scp(c), and is semantically defined by a relation, denoted by {a mathematical formula}rel(c), which contains the set of tuples allowed for the variables involved in c. The arity of a constraint c is the size of {a mathematical formula}scp(c), and will usually be denoted by r.
     </paragraph>
     <paragraph>
      An instantiation I of a set {a mathematical formula}X={x1,…,xk} of variables is a set {a mathematical formula}{(x1,a1), …, {a mathematical formula}(xk,ak)} such that {a mathematical formula}∀i∈1..k,ai∈dominit(xi); X is denoted by {a mathematical formula}vars(I) and each {a mathematical formula}ai is denoted by {a mathematical formula}I[xi]. An instantiation I on a CN N is an instantiation of a set {a mathematical formula}X⊆vars(N); it is complete if {a mathematical formula}vars(I)=vars(N). I is valid on N iff {a mathematical formula}∀(x,a)∈I,a∈dom(x). I covers a constraint c iff {a mathematical formula}scp(c)⊆vars(I), and I satisfies a constraint c with {a mathematical formula}scp(c)={x1,…,xr} iff (i) I covers c and (ii) the tuple {a mathematical formula}(I[x1],…,I[xr])∈rel(c). An instantiation I on a CN N is locally consistent iff (i) I is valid on N and (ii) every constraint of N covered by I is satisfied by I. A solution of N is a complete locally consistent instantiation on N; {a mathematical formula}sols(N) denotes the set of solutions of N. A CN N is satisfiable iff {a mathematical formula}sols(N)≠∅.
     </paragraph>
     <paragraph>
      The ubiquitous example of constraint propagation is enforcement of generalized arc consistency (GAC) which removes values from domains without reducing the set of solutions of the constraint network. A value {a mathematical formula}(x,a) of a CN N is GAC on N iff for every constraint c of N involving x, there exists a valid instantiation I of {a mathematical formula}scp(c) such that I satisfies c and {a mathematical formula}I[x]=a. N is GAC iff every value of N is GAC. Enforcing GAC means removing GAC-inconsistent values from domains until the constraint network is GAC. In this article, we shall refer to MAC which is an algorithm considered to be among the most efficient generic approaches for the solution of CNs. MAC [10] explores the search space depth-first, enforces (generalized) arc consistency after each decision taken (variable assignment or value refutation) during search, and backtracks when failures happen. A past variable is a variable explicitly assigned by the search algorithm whereas a future variable is a variable not (explicitly) assigned. The set of future variables of a CN N is denoted by {a mathematical formula}varsfut(N).
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Problems raised by interactive constraint solving
     </section-title>
     <paragraph>
      In this section, we formally characterize the questions that underlie the interactive constraint solving loop and we study their theoretical complexity.
     </paragraph>
     <section label="3.1">
      <section-title>
       Formalization
      </section-title>
      <paragraph>
       We first define the level of local consistency that is desirable in any interactive solving loop involving a human, that is, the level of consistency that guarantees that all values in all domains belong to a solution. In the nomenclature introduced by Freuder in [11] it corresponds to {a mathematical formula}(1,n−1)-consistency if the constraint network contains n variables. To avoid the reference to n, Freuder has called it variable completability in [12], and Dechter has called it global consistency of values in [13]. To be consistent with the now widely accepted nomenclature introduced in [8], we decided to call it global inverse consistency.
      </paragraph>
      <paragraph label="Definition 1">
       Global Inverse ConsistencyA value {a mathematical formula}(x,a) of a CN N is globally inverse consistent (GIC) iff {a mathematical formula}∃I∈sols(N)|I[x]=a. A CN N is GIC iff every value in {a mathematical formula}values(N) is GIC. The GIC closure of a CN N is the CN obtained from N by removing all the values that do not belong to a solution of N.
      </paragraph>
      <paragraph>
       We can observe that, as usual for levels of consistency, the GIC closure of a constraint network has the same set of solutions as the original network.
      </paragraph>
      <paragraph>
       There is a close relationship between GIC and minimality of constraint networks as defined by Montanari [14]. A constraint network is minimal according to Montanari if and only if any locally consistent instantiation of length 2 can be extended to a solution. Minimal networks are only defined for binary networks, that is, when the arity of all constraints is 2. Despite similarities in the definitions of GIC and minimal networks—they are both based on the notion of extensibility to solutions, a binary constraint network can be GIC and not minimal or minimal and not GIC. Take for instance the constraint network with {a mathematical formula}dom(x1)=dom(x2)={1,2,3} and the single constraint {a mathematical formula}x1⋅x2=3. It is obviously minimal, but it is not GIC because 2 does not belong to any solution. Take now the constraint network with {a mathematical formula}dom(x1)=dom(x2)=dom(x3)={1,2,3} and the constraints {a mathematical formula}x1+x2=4, {a mathematical formula}x2+x3=4, and {a mathematical formula}|x1−x3|≤1. It is GIC, but it is not minimal because the tuple {a mathematical formula}((x1,2),(x3,1)) is accepted by the constraint {a mathematical formula}|x1−x3|≤1 and does not extend to any solution.
      </paragraph>
      <paragraph>
       The obvious problems that follow from the definition of GIC are to check whether a constraint network is GIC or not, and to enforce GIC.
      </paragraph>
      <paragraph label="Problem 1">
       Deciding GICGiven a CN N, is N GIC?
      </paragraph>
      <paragraph label="Problem 2">
       Computing GICGiven a CN N, compute the GIC closure of N.
      </paragraph>
      <paragraph>
       As we are interested in interactive solving, we define the problem of maintaining GIC after the user has performed a variable assignment or, more generally, added any arbitrary constraint.
      </paragraph>
      <paragraph label="Problem 3">
       Maintaining GICGiven a CN N that is GIC, and a constraint {a mathematical formula}cnew with {a mathematical formula}scp(cnew)⊆vars(N), recompute GIC after the addition of {a mathematical formula}cnew to {a mathematical formula}cons(N).
      </paragraph>
      <paragraph>
       We also define the problem of restoring GIC after the user has decided to discard an existing constraint.
      </paragraph>
      <paragraph label="Problem 4">
       Restoring GICGiven a CN N and its GIC closure {a mathematical formula}NGIC, given a constraint {a mathematical formula}c∈cons(N), recompute the GIC closure of N after the retraction of c from {a mathematical formula}cons(N).
      </paragraph>
      <paragraph>
       In a configuration setting, as soon as some mandatory variables have been set, the user can ask for an automatic completion of the remaining variables. Hence the definition of the following problem:
      </paragraph>
      <paragraph label="Problem 5">
       Solving a GIC networkGiven a CN N that is GIC, find a solution to N.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Complexity results
      </section-title>
      <paragraph>
       Not surprisingly, the basic questions related to GIC (Problem 1, Problem 2) are intractable.
      </paragraph>
      <paragraph label="Theorem 1">
       Problem 1Deciding whether a constraint network N is GIC is NP-complete, even if N is satisfiable.
      </paragraph>
      <paragraph label="Proof">
       We first prove membership to NP. For each value {a mathematical formula}(x,a) of N, it is sufficient to provide a solution I of N such that the projection {a mathematical formula}I[x] of I on variable x is equal to a. This certificate has size {a mathematical formula}n⋅n⋅d and can be checked in polynomial time.Completeness for NP is proved by reducing 3Col{sup:1} to the problem of deciding whether a satisfiable CN is GIC. Take any instance of the 3Col problem, that is, a graph {a mathematical formula}G=(V,E), and denote the three colors by {a mathematical formula}1,2,3. Consider the CN N where {a mathematical formula}vars(N)={xi|i∈V}, {a mathematical formula}dom(xi)={0,1,2,3},∀i∈V, and {a mathematical formula}cons(N)={(xi≠xj)∨(xi=0∧xj=0)|(i,j)∈E}. Clearly the assignment {a mathematical formula}{(xi,0)|i∈V} is a solution of N, so N is satisfiable. If N is GIC then G is 3-colorable because, by construction, N has solutions other than {a mathematical formula}{(xi,0)|i∈V} iff G is 3-colorable. If G is 3-colorable then for any variable {a mathematical formula}xi, there exists a solution of N in which {a mathematical formula}xi is assigned a value in {a mathematical formula}1,2,3. By swapping 1 with 2, 2 with 3 and 3 with 1 on all variables of this solution, we still have a solution. Similarly by swapping 1 with 3, 2 with 1 and 3 with 2 on all variables. Thus, if G is 3-colorable then N is GIC. Therefore, N is GIC iff G is 3-colorable.  □
      </paragraph>
      <paragraph>
       Our proof shows that hardness for deciding GIC holds for binary CNs (i.e., CNs only involving binary constraints). We have another proof, inspired from that used in Theorem 3 in [15], that shows that deciding GIC is still hard for Boolean domains and quaternary constraints.
      </paragraph>
      <paragraph label="Theorem 2">
       Problem 2Computing the GIC closure of a constraint network N is NP-hard and NP-easy, even if N is satisfiable.
      </paragraph>
      <paragraph label="Proof">
       We prove NP-easiness by showing that a polynomial number of calls to a NP oracle are sufficient to build the GIC closure of N. For each value {a mathematical formula}(x,a) of N, we ask the NP oracle whether N with the extra constraint {a mathematical formula}x=a is satisfiable (we call this an inverse check). Once all values have been tested, we build the GIC closure of N by removing from each {a mathematical formula}dom(x) all values a for which the oracle test returned ‘no’. Hardness is a direct corollary of Theorem 1.  □
      </paragraph>
      <paragraph>
       Notice that the two previous intractability results are still valid when the CN is satisfiable, as is the case at the beginning of an interactive resolution session.
      </paragraph>
      <paragraph>
       We finally show that Problem 3, Problem 4, Problem 5 are unfortunately not easier than checking GIC or enforcing GIC from scratch. But they are not harder.
      </paragraph>
      <paragraph label="Theorem 3">
       Problem 3Given a CN N that is GIC, and a constraint{a mathematical formula}cnewwith{a mathematical formula}scp(cnew)⊆vars(N), computing the GIC closure of the CN{a mathematical formula}N′, where{a mathematical formula}vars(N′)=vars(N)and{a mathematical formula}cons(N′)=cons(N)∪{cnew}is NP-hard and NP-easy even if{a mathematical formula}cnewis simply a variable assignment{a mathematical formula}y=b.
      </paragraph>
      <paragraph label="Proof">
       NP-easiness is proved as in the proof of Theorem 2 by showing that a polynomial number of calls to a NP oracle are sufficient to build the GIC closure of {a mathematical formula}N′. For each value {a mathematical formula}(x,a) of N we ask the NP oracle whether {a mathematical formula}N′ with the extra constraint {a mathematical formula}x=a is satisfiable. Once all values have been tested, we build the closure of {a mathematical formula}N′ by removing from {a mathematical formula}dom(y) all values {a mathematical formula}a≠b and removing from each {a mathematical formula}dom(x) all values a for which the oracle test returned ‘no’.We prove hardness by reducing 3Col to the problem of computing the GIC closure of a GIC network after a variable assignment. Take any instance of the 3Col problem, that is, a graph {a mathematical formula}G=(V,E), and denote the three colors by {a mathematical formula}1,2,3. Consider the constraint network N where {a mathematical formula}vars(N)={xi|i∈V}∪{y1,y2}, {a mathematical formula}dom(xi)={0,1,2,3},∀i, {a mathematical formula}dom(y1)=dom(y2)={0,1}. {a mathematical formula}cons(N)={c(xi,xj)|(i,j)∈E}∪{c′(xi,y1,y2)|i∈1..n}, with {a mathematical formula}c(xi,xj) satisfied iff {a mathematical formula}(xi≠xj∨xi=xj=0) and {a mathematical formula}c′(xi,y1,y2) satisfied iff at most two variables among {a mathematical formula}xi,y1 and {a mathematical formula}y2 are assigned 0. N is GIC because for any {a mathematical formula}i∈1..n, the instantiation where {a mathematical formula}xi is assigned any of its values, {a mathematical formula}xj=0,∀j≠i, and {a mathematical formula}y1 and {a mathematical formula}y2 take 0 and 1 or vice versa, is a solution.We reduce the 3Col problem to the problem of enforcing GIC on the network {a mathematical formula}N′ with {a mathematical formula}vars(N′)=vars(N) and {a mathematical formula}cons(N′)=cons(N)∪{y1=0}. Let {a mathematical formula}domGIC be the domain of the GIC closure of {a mathematical formula}N′. If G is 3-colorable then assigning all {a mathematical formula}xi's to a solution of the 3-coloring and {a mathematical formula}y2=0 is a solution of {a mathematical formula}N′. If {a mathematical formula}0∈domGIC(y2), then {a mathematical formula}y2=0 must belong to a solution, say s. {a mathematical formula}xi's cannot take value 0 in s otherwise constraints {a mathematical formula}c′(xi,y1,y2) would be violated. Thus, the restriction of s to {a mathematical formula}xi's variables is a 3-coloring. Therefore, G is 3-colorable iff {a mathematical formula}0∈domGIC(y2).  □
      </paragraph>
      <paragraph label="Theorem 4">
       Problem 4Given a CN N, its GIC closure{a mathematical formula}NGIC, and a constraint{a mathematical formula}cold∈cons(N), computing the GIC closure of the CN{a mathematical formula}N′, where{a mathematical formula}vars(N′)=vars(N)and{a mathematical formula}cons(N′)=cons(N)∖{cold}is NP-hard and NP-easy even if{a mathematical formula}coldis simply a variable assignment{a mathematical formula}y=b.
      </paragraph>
      <paragraph label="Proof">
       NP-easiness is proved as in the proof of Theorem 2. We prove hardness by reducing 3Col to the problem of taking a network N for which we know the GIC closure {a mathematical formula}NGIC, and computing the GIC closure of the network {a mathematical formula}N′ obtained from N by retracting a variable assignment. Take any instance of the 3Col problem, that is, a graph {a mathematical formula}G=(V,E). Consider the constraint network N where {a mathematical formula}vars(N)={xi|i∈V}∪{y}, {a mathematical formula}dom(xi)={0,1,2,3},∀i, {a mathematical formula}dom(y)={0,1}. {a mathematical formula}cons(N)={c1(xi,xj)|(i,j)∈E}∪{c2(xi,y)|i∈1..n}∪{y=0}, with {a mathematical formula}c1(xi,xj) satisfied iff {a mathematical formula}(xi≠xj)∨(xi=xj=0) and {a mathematical formula}c2(xi,y) satisfied iff {a mathematical formula}(xi=y=0)∨(xi≠0∧y≠0). The only solution is the assignment where every {a mathematical formula}xi is assigned 0 and y is assigned 0. Thus, {a mathematical formula}NGIC has the domain {a mathematical formula}domGIC defined by {a mathematical formula}domGIC(xi)={0},∀i, and {a mathematical formula}domGIC(y)={0}.We show that the 3Col problem can be decided polynomially if we have an oracle enforcing GIC on the network {a mathematical formula}N′ with {a mathematical formula}vars(N′)=vars(N) and {a mathematical formula}cons(N′)=cons(N)∖{y=0}. Let {a mathematical formula}domGIC′ be the domain of the GIC closure of {a mathematical formula}N′. If G is not 3-colorable then, by construction of {a mathematical formula}c1 and {a mathematical formula}c2, the only solution is the same as in N, that is, the tuple containing only 0's. If G is 3-colorable then assigning a solution of the 3-coloring to the {a mathematical formula}xi's and 1 to y is a solution of {a mathematical formula}N′. Therefore, knowing {a mathematical formula}NGIC does not help and G is 3-colorable iff {a mathematical formula}1∈domGIC(y).  □
      </paragraph>
      <paragraph label="Theorem 5">
       Problem 5Generating a solution to a GIC constraint network cannot be done in polynomial time, unless{a mathematical formula}P=NP.
      </paragraph>
      <paragraph label="Proof">
       The following proof is derived from [16]. It is also a corollary of the recent and more complex Theorem 3.1 in [17].Suppose we have an algorithm A that generates a solution to a GIC constraint network N in time bounded by a polynomial {a mathematical formula}p(|N|). Take any instance of the 3Col problem, that is, a graph {a mathematical formula}G=(V,E). Consider the CN N where {a mathematical formula}vars(N)={xi|i∈V}, {a mathematical formula}dom(xi)={1,2,3},∀i∈V, and {a mathematical formula}cons(N)={xi≠xj|(i,j)∈E}. N has a solution iff G is 3-colorable. Now, if G is 3-colorable then N is GIC because any permutation of the three colors applied to all variables remains a solution (as in the proof of Theorem 1). Thus, it is sufficient to run A during {a mathematical formula}p(|N|) steps. If it returns a solution to N, then the 3Col instance is satisfiable. Otherwise, the 3Col instance is unsatisfiable. Therefore, as 3Col is NP-complete, there cannot exist a polynomial algorithm for generating a solution to a GIC constraint network, unless {a mathematical formula}P=NP.  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Algorithms for enforcing/maintaining GIC
     </section-title>
     <paragraph>
      In this section, we introduce four algorithms to enforce global inverse consistency. These GIC algorithms use increasingly sophisticated data structures and techniques that have recently proved their worth in propagation algorithms proposed in the literature. To simplify our presentation, we assume that the CNs are satisfiable, which is the case in interactive resolution, allowing us to avoid handling domain wipe-outs in the GIC procedures. Note that these algorithms can be used to enforce GIC, but also to maintain it during a user-driven search. This is why we refer to the set {a mathematical formula}varsfut(N) of future variables in some instructions.
     </paragraph>
     <paragraph>
      The first algorithm, GIC1, is similar to an algorithm proposed in [18]. GIC1 is described in Algorithm 1. It is really basic: it will be used as our baseline during our experiments. For each value a in the domain of a future variable x, a solution for the CN N where x is assigned the value a, denoted by {a mathematical formula}N|x=a, is sought using a complete search algorithm. This search algorithm, called here searchSolutionFor, either returns the first solution that can be found, or the special value nil. Our implementation choice will be the algorithm MAC that maintains (G)AC during a backtrack search [10]. Hence, in Algorithm 1, when it is proved with searchSolutionFor that no solution exists, i.e. {a mathematical formula}I=nil, the value a can be deleted. Note that, in contrary to weaker forms of consistency, when a value is pruned there is no need for GIC to repeat the process of iterating over the values remaining in the CN.
     </paragraph>
     <paragraph>
      The second algorithm, GIC2 described in Algorithm 4 (ignoring light grey lines), uses timestamping. This is useful when GIC is maintained during a user-driven search. We use an integer variable time for counting time, and we introduce a two-dimensional array stamp that associates with each value {a mathematical formula}(x,a) of the CN the last time (value of {a mathematical formula}stamp[x][a]) a solution was found for that value (0, initially). We also assume that variables are implicitly totally ordered (for example, in lexicographic order). Then, the idea is to increment the value of the variable time whenever a new call to GIC2 is performed (see line 1) and to test time against each value {a mathematical formula}(x,a) of the CN (see line 5) to determine whether it is necessary or not to search for a solution for {a mathematical formula}(x,a). When a solution I is found, function handleSolution2/3 is called at line 10 in order to update stamps. Actually, we only update the stamps of values in I corresponding to variables that are processed after x in the loop of revisions (line 4) in Algorithm 4. These are the variables that have not been processed yet by the loop at line 4 of Algorithm 4. Finally, by further introducing a one-dimensional array nbGic that associates with each variable x of the CN the number of values in {a mathematical formula}dom(x) that have been proved to be GIC, it is possible to avoid some iterations of loop 5; see initialization at lines 2–3, testing at line 4 and update at line 4 of Algorithm 2.
     </paragraph>
     <paragraph>
      The third algorithm, GIC3, described in Algorithm 4 when considering light grey lines, can be seen as a refinement of GIC2 obtained by exploiting residues, which correspond to solutions that have been previously found. Here, we introduce a two-dimensional array residue that associates with each value {a mathematical formula}(x,a) of the CN the last solution found for this value (potentially, during another call to GIC3). Because residual solutions may not be valid anymore, for each value {a mathematical formula}(x,a) we need to test the validity of {a mathematical formula}residue[x][a] by calling the function {a mathematical formula}isValid; see instructions between lines 5 and 6. If the residue is valid, we call handleSolution2/3 to update the other data structures, and we continue with the next value in the domain of x. A validity test, Algorithm 3, only checks that all values in a given complete instantiation are still present in the current domains. Of course, when a new solution is found, we record it as a residue; see instruction after line 10.
     </paragraph>
     <paragraph>
      Our last algorithm, GIC4 described in Algorithm 6, is based on an original use of simple tabular reduction [19]. The principle is to record all solutions found during the enforcement of GIC in a table, so that an (adaptation of an) algorithm such as STR2 [20] can be applied. The current table is given by all elements of an array solutions at indices ranging from 1 to nbSolutions. As for STR2, we introduce two sets of variables called {a mathematical formula}Sval and {a mathematical formula}Ssup. The former allows us to limit validity control of solutions to the variables whose domains have changed recently (i.e., since the last execution of GIC4). This is made possible by reasoning from domain cardinalities, as performed at lines 3 and 26–27 with the array lastSize. The latter ({a mathematical formula}Ssup) contains any future variable x for which at least one value is not in the array {a mathematical formula}gicValues[x], meaning that it has still to be proved GIC. Related details can be found in [20]. After the initialization of {a mathematical formula}Sval and {a mathematical formula}Ssup (lines 1–8), each instantiation {a mathematical formula}solutions[i] of the current table is processed (lines 11–16). If it remains valid (hence, a solution), we update structures gicValues and {a mathematical formula}Ssup by calling the function handleSolution4. Otherwise, this instantiation is deleted by swapping it with the last one. The rest of the algorithm (lines 17–25) just tries to find a solution support for each value not present in gicValues. When a new solution is found, it is recorded in the current table (lines 23–24) and handleSolution4 is called (line 25).
     </paragraph>
     <paragraph label="Theorem 6">
      Algorithms GIC1, GIC2, GIC3, and GIC4 enforce GIC.
     </paragraph>
     <paragraph label="Proof">
      Soundness. Soundness is clear for all four algorithms. GIC1 (Algorithm 1) only removes a value {a mathematical formula}(x,a) in line 5, which means that line 3 has not found any solution containing {a mathematical formula}(x,a). Thus {a mathematical formula}(x,a) is not GIC. GIC2 and GIC3 (Algorithm 4) only remove a value {a mathematical formula}(x,a) in line 8, which means that line 6 has not found any solution containing {a mathematical formula}(x,a). Thus {a mathematical formula}(x,a) is not GIC. GIC4 (Algorithm 6) only removes a value {a mathematical formula}(x,a) in line 21, which means that line 19 has not found any solution containing {a mathematical formula}(x,a). Thus {a mathematical formula}(x,a) is not GIC.Completeness. Completeness of GIC1 is obvious: searchSolutionFor is called for all values (line 3), so if a value {a mathematical formula}(x,a) is not GIC, it will necessarily be removed in line 5.In GIC2 (Algorithm 4), a value {a mathematical formula}(x,a) is let in the domain without checking if it belongs to a solution when {a mathematical formula}nbGic[x]≥|dom(x)| (line 4) or {a mathematical formula}stamp[x][a]≥time (line 5). As time is incremented at each new call to GIC2 (line 1), {a mathematical formula}stamp[x][a] is (greater than or) equal to time only if line 3 of Algorithm 2 has been executed, which means that a solution containing {a mathematical formula}(x,a) has already been found, and thus {a mathematical formula}(x,a) is GIC. Lines 2 and 4 of Algorithm 2 ensure that {a mathematical formula}nbGic[x] is equal to the number of values in {a mathematical formula}dom(x) that GIC2 has already found in a solution at the current call to GIC2 ({a mathematical formula}timeth call). Hence, if {a mathematical formula}nbGic[x]≥|dom(x)|, all values of x have been proved GIC.Like GIC2, GIC3 (Algorithm 4) lets a value {a mathematical formula}(x,a) in the domain without checking if it belongs to a solution when {a mathematical formula}nbGic[x]≥|dom(x)| or {a mathematical formula}stamp[x][a]≥time. But in addition, GIC3 avoids checking if {a mathematical formula}(x,a) belongs to a solution when isValid({a mathematical formula}vars(N),{a mathematical formula}residue[x][a]) is true (grey colored line between lines 5 and 6). {a mathematical formula}residue[x][a] stores a solution containing {a mathematical formula}(x,a) found at a previous call to GIC3 (grey colored line after line 10). Function isValid checks if that solution is still valid at the current call to GIC3. If yes, {a mathematical formula}residue[x][a] is a proof of GIC for {a mathematical formula}(x,a) (and also for other values appearing in {a mathematical formula}residue[x][a]—call to handleSolution2/3 in grey colored lines between lines 5 and 6).In GIC4 (Algorithm 6) the conditions to avoid checking if a value {a mathematical formula}(x,a) belongs to a solution are {a mathematical formula}x∉Ssup (line 17) and {a mathematical formula}a∈gicValues[x] (line 18). {a mathematical formula}gicValues[x] is initialized to the empty set in line 7 and values are only added to {a mathematical formula}gicValues[x] in line 3 of Algorithm 5. To prove that these added values are GIC we have to prove that handleSolution4 is always called with valid solutions. handleSolution4 is called in lines 12 and 25 of Algorithm 6. In the call of line 25 I is obviously a valid solution as it is the result of the call to searchSolutionFor in line 19. In line 12 handleSolution4 is called with {a mathematical formula}solutions[i]. Thanks to lines 24 and 15, we know that solutions is an array that only contains instantiations that were valid solutions at the previous call to GIC4. As in line 11 isValid has checked that all values of variables with a modified domain are still in the domain, {a mathematical formula}solutions[i] is a valid solution. Thus, values in {a mathematical formula}gicValues[x] are GIC. As for the other condition ({a mathematical formula}x∉Ssup), thanks to line 8 we know that GIC4 puts all variables in {a mathematical formula}Ssup in the initialization phase. The only place where a variable is removed from {a mathematical formula}Ssup is line 5 of Algorithm 5. This line is executed only if {a mathematical formula}gicValues[x] contains all values in {a mathematical formula}dom(x) (test in line 4). Thus, by avoiding checking GIC on values of variables which are not in {a mathematical formula}Ssup we do not miss the pruning of any GIC-inconsistent value.  □
     </paragraph>
     <paragraph>
      The worst-case space complexity (for the specific data structures) of GIC1 is in {a mathematical formula}O(1). For GIC2 and GIC3, this is in {a mathematical formula}O(nd) because nbGic is in {a mathematical formula}O(n), stamp and residue are in {a mathematical formula}O(nd). For GIC4, {a mathematical formula}Sval, {a mathematical formula}Ssup and lastSize are in {a mathematical formula}O(n), gicValues is in {a mathematical formula}O(nd), and the structure solutions is in {a mathematical formula}O(n2d) because for each of the nd values, we may need to record a solution (of size n). The time complexity of the GIC algorithms can be expressed in term of the number of calls to the (oracle) searchSolutionFor. For GIC1, this is in {a mathematical formula}O(nd). For GIC2, in the best-case, only d calls are necessary, each call allowing to prove (through timestamping) that n values are GIC. For GIC3 and GIC4, still in the best-case and assuming the case of maintaining GIC (i.e., after the assignment of a variable by the user), no call to the oracle is necessary (residues and the current table are sufficient by themselves to prove that all values are GIC). This rough analysis of time complexity suggests that GIC3 and GIC4 might be the best options.
     </paragraph>
     <paragraph>
      Observe that when GIC is maintained during search, one can always enforce the weaker (and cheaper) consistency GAC before GIC. This is the approach we systematically follow when maintaining GIC during search (with any of the introduced GIC algorithms).
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      An algorithm for restoring GIC
     </section-title>
     <paragraph>
      In this section, we address the issue of restoring GIC after the user decides to discard arbitrarily a decision that has been taken during a configuration process based on GIC. So, the context is a CN N that is given initially, a sequence of p decisions {a mathematical formula}Δ=〈δ1,δ2,…,δp〉 taken on N (in that order) by the user, and GIC maintained on N.
     </paragraph>
     <paragraph>
      More formally, a configuration trace T on a CN N from a sequence of decisions {a mathematical formula}〈δ1,…,δp〉 is represented by a sequence of CNs {a mathematical formula}〈N1,…,Np〉 such that {a mathematical formula}Ni is the CN obtained from {a mathematical formula}Ni−1 (starting with {a mathematical formula}N0=N) after taking the decision {a mathematical formula}δi and running some propagation algorithm. For each decision {a mathematical formula}δi, it is easy to identify the set {a mathematical formula}deleted(δi) of values deleted due to the combined effect of {a mathematical formula}δi and constraint propagation: we have {a mathematical formula}deleted(δi)=values(Ni−1)∖values(Ni). These sets are useful for backtracking, for example with the so-called trailing mechanism (see e.g., [21]).
     </paragraph>
     <paragraph>
      Without loss of generality, we assume that N is (or has been made) initially GIC. A configuration trace {a mathematical formula}T=〈N1,…,Np〉 on N from {a mathematical formula}〈δ1,…,δp〉 is GIC-staged iff {a mathematical formula}Ni=GIC(Ni−1|δi), {a mathematical formula}∀i∈1..p. In other words, a GIC-staged configuration trace is a trace such that GIC is maintained at each step. An illustration is given by Fig. 1, where each edge represents the action of taking a decision {a mathematical formula}δi and enforcing GIC: we have {a mathematical formula}N1=GIC(N0|δ1), {a mathematical formula}N2=GIC(N1|δ2), …, {a mathematical formula}Np=GIC(Np−1|δp).
     </paragraph>
     <paragraph>
      In our work, we are interested in GIC-staged configuration traces, and our objective is to be able to rebuild GIC-staged configuration traces after discarding arbitrarily any taken decision(s). Note that it has the flavor of dynamic backtracking [22], but in the context of the very strong consistency GIC. An illustration of a GIC-staged configuration trace, {a mathematical formula}T=〈N1,…,Ni−1,Ni,Ni+1,…,Np〉, is given by Fig. 2(a): we have, {a mathematical formula}N1=GIC(N0|δ1), …, {a mathematical formula}Ni−1=GIC(Ni−2|δi−1), {a mathematical formula}Ni=GIC(Ni−1|δi), {a mathematical formula}Ni+1=GIC(Ni|δi+1), …, {a mathematical formula}Np=GIC(Np−1|δp). If ever the decision {a mathematical formula}δi is discarded by the user, then we want to compute a new GIC-staged configuration trace, {a mathematical formula}T′=〈N1,…,Ni−1,Ni′,…,Np−1′〉, as in Fig. 2(b), where {a mathematical formula}N1=GIC(N0|δ1), …, {a mathematical formula}Ni−1=GIC(Ni−2|δi−1), {a mathematical formula}Ni′=GIC(Ni−1|δi+1), …, {a mathematical formula}Np−1′=GIC(Np−2′|δp). Hence, we need to compute {a mathematical formula}p−i new CNs: {a mathematical formula}Ni′, …, {a mathematical formula}Np−1′, but as observed earlier, it suffices to identify the (new) sets of deleted values at levels i, …, {a mathematical formula}p−1. Later, in Algorithm 9, this will be the role of the data structure Knw.
     </paragraph>
     <paragraph>
      Reclassifying a deleted value of trace T means finding the level at which this value must be deleted in the new trace {a mathematical formula}T′, or proving that it is no longer deleted. It is worthwhile to analyze which values must be reclassified when a decision is discarded and a new GIC-staged configuration trace is aimed to be computed. First, at each level, i.e. after each decision δ, we can distinguish between the values that are directly removed by δ and those that are removed by propagating these initial direct deletions through the CN. For example, if x is a variable such that {a mathematical formula}dom(x)={a,b,c} and δ corresponds to the variable assignment {a mathematical formula}x=a, then the values directly removed by δ are {a mathematical formula}{b,c}. All other values removed while enforcing GIC after taking δ are said to be indirectly removed by δ. The different sets of values that are removed either directly or indirectly in a GIC-staged configuration trace are depicted in Fig. 3.
     </paragraph>
     <paragraph>
      In the following, for the sake of simplicity, we assume that all decisions correspond to variable assignments. Interestingly, once the decision {a mathematical formula}δi is discarded, computing the new GIC-staged configuration trace {a mathematical formula}T′ only requires to reclassify the deleted values that belong to the grey-colored regions of Fig. 3. The proof is as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       nothing changes for levels strictly less than i; in other words, for any integer j such that {a mathematical formula}0&lt;j&lt;i, {a mathematical formula}deleted(δj) remains the same.
      </list-item>
      <list-item label="2.">
       any value {a mathematical formula}(x,a) directly removed by a decision {a mathematical formula}δj with {a mathematical formula}j&gt;i will necessarily be again removed directly by {a mathematical formula}δj in the new trace ; in other words, {a mathematical formula}(x,a) remains in {a mathematical formula}deleted(δj).{sup:2} Indeed, the relaxation (retracted decision) does not allow us to remove {a mathematical formula}(x,a) before taking {a mathematical formula}δj in the new trace.
      </list-item>
     </list>
     <paragraph>
      All values that must be reclassified are put in a data structure called Unk and transferred progressively, while running the algorithm we propose, to a data structure called Knw that we introduce later.
     </paragraph>
     <paragraph>
      To restore GIC, Function restoreAfterDeleting(), presented in Algorithm 9, must be called. When this function is called for, it is for a GIC-staged configuration trace {a mathematical formula}T=〈N1,…,Np〉 on a CN N from a sequence of decisions {a mathematical formula}Δ=〈δ1,…,δp〉. For simplicity and because we assume that at each decision level, i.e. for each decision δ, we know {a mathematical formula}deleted(δ), only {a mathematical formula}Np is specified as a parameter (as well as the decision {a mathematical formula}δi to be discarded). General statements useful for describing our algorithm are:
     </paragraph>
     <list>
      <list-item label="•">
       take(δ) : the decision δ is added at the end of the current sequence of decisions (push operation) and {a mathematical formula}deleted(δ) initially contains the values of {a mathematical formula}dom(var(δ)) that are not compatible with δ (direct deletions).
      </list-item>
      <list-item label="•">
       backtrack() : the last taken decision δ is removed from the current sequence of decisions (pop operation) and values in {a mathematical formula}deleted(δ) are restored in domains.
      </list-item>
     </list>
     <paragraph>
      The data structures used by our function are the following:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Δreplay is the sequence {a mathematical formula}〈δi+1,δi+2,…,δp〉 of decisions to be replayed, once {a mathematical formula}δi is discarded.
      </list-item>
      <list-item label="•">
       Knw is an array of size {a mathematical formula}p−i+1, indexed from i to p, of sets of values. This is a central data structure in our algorithm, allowing us to rebuild the GIC-staged configuration trace {a mathematical formula}T′. Once the computation of this array is finished, all values are reclassified. If {a mathematical formula}(x,a)∈Knw[h] with {a mathematical formula}i≤h&lt;p, this means that {a mathematical formula}(x,a) must be deleted at level h, but if {a mathematical formula}(x,a)∈Knw[p], this means that {a mathematical formula}(x,a) will no more be deleted in the new trace (because we only kept {a mathematical formula}p−1 decisions).
      </list-item>
      <list-item label="•">
       Unk is a map that associates an integer interval {a mathematical formula}hmin..hmax, called classification interval, with each key of the form {a mathematical formula}(x,a). The meaning of an entry {a mathematical formula}((x,a),hmin..hmax) of Unk is that the value {a mathematical formula}(x,a) must be reclassified at a level ranging from {a mathematical formula}hmin to {a mathematical formula}hmax. During the execution of the algorithm, the classification interval of every entry is refined until the precise deletion level is known, i.e. until {a mathematical formula}hmin=hmax, in which case the entry is deleted and transferred to the structure Knw, described above. Notice that when the classification interval associated with a value ends up at {a mathematical formula}p..p, this actually means that the value is no more deleted by GIC. As any map, Unk supports the following operations:
      </list-item>
     </list>
     <paragraph>
      Before presenting function restoreAfterDeleting() in detail, we describe the two primitive functions increaseMin and decreaseMax that will be used to update the classification interval of a key {a mathematical formula}(x,a) in Unk and move such a key to Knw when needed. Function increaseMin({a mathematical formula}(x,a),h) (Algorithm 7) first retrieves the interval for key {a mathematical formula}(x,a) in Unk (line 1). If the new lower bound h reduces the interval to a singleton, the key {a mathematical formula}(x,a) is transferred from Unk to Knw with the right deletion level (lines 2–4). Otherwise, if the lower bound changed, the interval is updated (lines 5–6). Function decreaseMax({a mathematical formula}(x,a),h) (Algorithm 8) behaves the same way: it retrieves the interval for {a mathematical formula}(x,a), checks whether the new upper bound h reduces the interval to a singleton, and depending on the answer transfers {a mathematical formula}(x,a) to Knw or updates the upper bound.
     </paragraph>
     <paragraph>
      Function restoreAfterDeleting() works as follows. Lines 1–4 initialize the structures: the decisions to be replayed are put in {a mathematical formula}Δreplay, and structures Unk and Knw are emptied because deleted values to be reclassified are not known yet, and so, no classification has been performed yet. Line 5–14 handle all values that have been deleted from level i in the current trace T. All levels, from p down to i, are iterated over, by systematically backtracking (lines 11 and 14). The new status of any deleted value {a mathematical formula}(x,a) at a level {a mathematical formula}j&gt;i is either known (line 8), because of a direct deletion, or unknown (line 10). For the former case, the test at line 7 is sufficient because we only consider variable assignments. For the latter case, the interval {a mathematical formula}j−1..p bounds the different possibilities (the value cannot be deleted at a level less than {a mathematical formula}j−1 and possibly can remain valid at the end of the new trace). For level i (lines 12–13), as shown in Fig. 3, all deleted values must be reclassified. Line 15 attempts to refine the classification intervals of values by applying a polynomial process, such as simulating GIC by an efficient local consistency technique. We show later how to use GAC for refining the intervals. Lines 16–25 finalize classification. For each unclassified value {a mathematical formula}(x,a), we have an interval of the form {a mathematical formula}hmin..hmax. Given {a mathematical formula}(x,a), we select a value (level) s that will be used to decrease the size of the interval of {a mathematical formula}(x,a); for our experimentation, we shall select {a mathematical formula}hmax−1. In line 19, we call searchSolutionFor in the network where we force all decisions from {a mathematical formula}δi+1 to {a mathematical formula}δs+1 (that correspond to new levels i to s) plus {a mathematical formula}x=a. The purpose of this call to searchSolutionFor is to check if there exists a solution for {a mathematical formula}(x,a) at level s. If this is not the case, we can decrease the upper bound of the interval to s (since, we know that GIC is enough to prune this value at level s). Otherwise, we can increase the lower bound of all unclassified values that are present in the found solution I (see Lines 23–25). This includes of course {a mathematical formula}(x,a). Lines 26–29 build the new GIC-staged configuration trace {a mathematical formula}T′ from data in Knw.
     </paragraph>
     <paragraph>
      Reclassifying values may be expensive because for proving GIC of a value we have to run a complete search procedure (see line 19), and possibly several times. One idea is to use a cheap process, such as applying GAC, as an approximation of GIC in a preliminary stage. For example, suppose that {a mathematical formula}((x,a),10..14) is present in Unk and that MAC removes {a mathematical formula}(x,a) at level 10. We can then deduce that {a mathematical formula}(x,a) is GIC-inconsistent at level 10, and consequently directly classify {a mathematical formula}(x,a) in {a mathematical formula}T′. If MAC removes {a mathematical formula}(x,a) only at level 12, then we can replace {a mathematical formula}((x,a),10..14) by {a mathematical formula}((x,a),10..12) in Unk. To summarize, running MAC on decisions of {a mathematical formula}Δreplay allows us to refine the classification intervals at a very moderate price. This what is done by the function {a mathematical formula}refineIntervals(Unk,Knw,Δreplay) in Algorithm 10.
     </paragraph>
     <paragraph>
      In lines 1–3, GAC is maintained after each decision taken in sequence from {a mathematical formula}Δreplay. Then, in lines 4–7, we process each level in sequence from bottom to top. If {a mathematical formula}(x,a) has been deleted (at level {a mathematical formula}j−1) by GAC after decision {a mathematical formula}δj, we know that GIC will prune {a mathematical formula}(x,a) at level {a mathematical formula}j−1 at the very last. Hence, we update the interval of {a mathematical formula}(x,a) accordingly. After having processed all values of a level, we have to call the backtrack function to restore domains in the state they were before applying GAC (line 8).
     </paragraph>
     <paragraph>
      We have the guarantee that restoreAfterDeleting performs as if GIC had been maintained on N from {a mathematical formula}〈δ1,…,δi−1,δi+1,…,δp〉. The proof is based on the invariant property that Unk is sound, that is, the level of deletion of any {a mathematical formula}(x,a) present in Unk is contained in the interval stored in Unk.
     </paragraph>
     <paragraph label="Lemma 1">
      If Unk is sound before a call to refineIntervals, then it remains sound after the execution of refineIntervals as described inAlgorithm 10.
     </paragraph>
     <paragraph label="Proof">
      The interval of {a mathematical formula}(x,a) in Unk is modified in line 7 only if GAC has removed {a mathematical formula}(x,a) after decision {a mathematical formula}δj has been applied. By enforcing GIC instead of GAC, it is obvious that {a mathematical formula}(x,a) cannot be removed later. Thus, the last level at which {a mathematical formula}(x,a) can be removed is {a mathematical formula}j−1 because {a mathematical formula}δj is the {a mathematical formula}(j−1)th decision.  □
     </paragraph>
     <paragraph label="Theorem 7">
      Let{a mathematical formula}〈N1,…,Np〉be a GIC-staged configuration trace on a CN N from a sequence of decisions{a mathematical formula}〈δ1,…,δp〉. Calling restoreAfterDeleting{a mathematical formula}(Np,δi)builds the GIC-staged configuration trace on N from{a mathematical formula}〈δ1,…,δi−1,δi+1,…,δp〉.
     </paragraph>
     <paragraph label="Proof">
      Lines 11 and 14 ensure that, after line 14, all values removed in levels i to p have been restored and put either in Knw or in Unk. They will thus all be processed to find their right level of deletion.We first prove that before line 26, all values are put in Knw at their right level of deletion. After lines 1–14 are executed, all values in Knw have been put in it at line 8. They have been put at their right level because they cannot be higher (relaxation) and they are necessarily removed (line 7 tells us they belong to the instantiated variable). After lines 1–14, Unk is sound because it stores the largest possible interval for every non-reclassified value. After line 14, intervals are refined in lines 15, 21, and 25. By Lemma 1, Unk remains sound after line 15. In line 21, the {a mathematical formula}hmax of {a mathematical formula}(x,a) is decreased correctly because there were no solutions containing {a mathematical formula}(x,a) at level s. In line 25, it is also obviously correct to increase the {a mathematical formula}hmin of {a mathematical formula}(y,b) to {a mathematical formula}s+1 as we found a solution at level s. By construction of functions increaseMin and decreaseMax, we know that after line 25, Knw contains only correct levels of deletion.We then prove that the loop in lines 16–25 terminates. When we enter the loop in line 16, Unk only contains values with a non-singleton interval. By construction of increaseMin and decreaseMax, any value with an interval shrunk to singleton is moved to Knw. Thus, line 17 can only select values with non-singleton intervals, and the way s is selected in line 18 ensures that any iteration of the loop of line 17 strictly decreases the size of at least one interval in Unk. As all intervals have finite size and as Unk contains a finite number of values, the loop of line 16 terminates.The fact that after line 25 all values are put in Knw at their right level of deletion and the fact that the algorithm will eventually reach line 26 guarantees that lines 26–29 build a GIC-staged configuration trace.  □
     </paragraph>
     <paragraph>
      The algorithm restoreAfterDeleting is obviously exponential in time as it solves an NP-hard problem (see Theorem 4). Nevertheless, we can analyze the number of times it calls the NP-hard oracle searchSolutionFor.
     </paragraph>
     <paragraph label="Theorem 8">
      ComplexityLet{a mathematical formula}〈N1,…,Np〉be a GIC-staged configuration trace on a CN N from a sequence of decisions{a mathematical formula}〈δ1,…,δp〉. The number of times restoreAfterDeleting{a mathematical formula}(Np,δi)calls searchSolutionFor is in{a mathematical formula}O(nd⋅log2(p−i)).
     </paragraph>
     <paragraph label="Proof">
      Each time searchSolutionFor is called in line 19, the interval of {a mathematical formula}(x,a) is shrunk either to {a mathematical formula}[hmin,s] or to {a mathematical formula}[s+1,hmax], depending on whether line 21 or line 25 is executed. Hence, if s is selected in a dichotomic way (that is, {a mathematical formula}s=⌊hmin+hmax2⌋), each call to searchSolutionFor leads to an interval of size at most {a mathematical formula}⌈hmax−hmin+12⌉. Unk contains at most nd values and intervals cannot be larger than {a mathematical formula}p−i+1. As a result, the number of times restoreAfterDeleting can call searchSolutionFor is in {a mathematical formula}O(nd⋅log2(p−i)).  □
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      In order to show the practical interest of our approach, we have performed several experiments mainly using a computer with processors Intel(R) Core(TM) i7-2820QM CPU 2.30 GHz; however, for GIC restoration, we used a cluster of Xeon 3.0 GHz processors with 13 GB of RAM. Our main purpose was to determine whether maintaining/restoring GIC is a viable option for configuration-like problem instances (and for interactive puzzle creation), as well as to compare the relative efficiency of the four GIC algorithms described in Section 4.
     </paragraph>
     <paragraph>
      In Table 1, we show relevant features of car configuration instances, generated with the help of our industrial partner Renault. For each of the six instances currently available,{sup:3} we indicate
     </paragraph>
     <list>
      <list-item label="•">
       the number of variables (n),
      </list-item>
      <list-item label="•">
       the size of the greatest domain (d),
      </list-item>
      <list-item label="•">
       the number of constraints (e),
      </list-item>
      <list-item label="•">
       the greatest constraint arity (r),
      </list-item>
      <list-item label="•">
       the size of the greatest table (t),
      </list-item>
      <list-item label="•">
       the total number of values ({a mathematical formula}D=∑x∈vars(N)|dom(x)|),
      </list-item>
      <list-item label="•">
       and the total number of tuples ({a mathematical formula}T=∑c∈cons(N)|rel(c)|).
      </list-item>
     </list>
     <section label="6.1">
      <section-title>
       Establishing/maintaining GIC
      </section-title>
      <paragraph>
       The left part of Table 2 presents the CPU time required to establish GIC on the six Renault configuration instances. Clearly GIC1 is outperformed by the three other algorithms, which have here rather similar efficiency. The right part of Table 2 aims at simulating the behavior of a configuration software user who makes the variable choices and value selections. It presents the CPU time required to maintain GIC along a complete branch built by performing random variable assignments down to a leaf. (Random variable assignment simulates the user, who chooses the variables and the values according to her preference.) Specifically, variables and values are randomly selected in turn, and after each assignment, GIC is systematically enforced to maintain this property. Of course, no conflict (dead-end) can occur along the branch due to the strength of GIC, which is why we use the term of greedy executions. CPU times are given on average for 100 executions (different random orderings). When establishing GIC, any call to searchSolutionFor is performed with the help of the algorithm MAC (table constraints being filtered with the technique called Simple Tabular Reduction [19], [20], [23]). For all instances, GIC3 and GIC4 are maintained very fast, whereas on the biggest instances, GIC2 requires a few seconds and GIC1 around ten seconds.
      </paragraph>
      <paragraph>
       One great advantage of GIC is that it guarantees that a conflict can never occur during a configuration session. However, one may wonder whether the risk of failure(s) is really important in user-driven searches that use a weaker consistency such as GAC or a partial form of it (Forward Checking). Table 3 shows the number of conflicts (sum over 100 executions using random orderings) encountered when following a MAC or a nFC2 [24] strategy. The number of conflict situations can be very large with nFC2 (for two instances, we even report the impossibility of finding a solution within 10 minutes with some random orderings). For MAC, the number of failures is rather small but the risk is not null (for example, the risk is equal to 7% for megane).
      </paragraph>
      <paragraph>
       The encouraging results obtained on Renault configuration instances led us to test other problems, in particular to get a better picture of the relative efficiency of the various GIC algorithms. For example, on classical Crossword instances (see Table 4), GIC1 is once again clearly outperformed while the three other algorithms are quite close, where there is still a small benefit of using GIC4.
      </paragraph>
      <paragraph>
       It is worthwhile to note that GIC is a nice property that can be useful when puzzles, where hints are specified, have to be created. Typically, one looks for puzzles where only one solution exists. One way of building such puzzles is to add hints in sequence, while maintaining GIC, until all domains become singleton. For example, this is a possible approach for constructing Sudoku and Magic Square grids, with the advantage that the user can choose freely the position of the hints.{sup:4} On the left part of Table 5, we report the time to enforce GIC on empty Sudoku grids of size {a mathematical formula}9×9 and {a mathematical formula}16×16, and on empty Magic squares of size {a mathematical formula}4×4 and {a mathematical formula}5×5. On the right part we report the average time required to maintain GIC until all variables become fixed (i.e., with only singleton domains), meaning that after several hints have been randomly selected and propagated, we have the guarantee of having a one-solution puzzle. GIC4 is a clear winner, with for example, a 30% speedup over GIC2 and GIC3 on sudoku-{a mathematical formula}16×16, and more than one order of magnitude over GIC1. Overall, the results we obtain show that maintaining GIC is a practicable solution (at least for some problems) as the average time between each decision of the user is small with GIC4.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Restoring GIC
      </section-title>
      <paragraph>
       In a second set of experiments, we have focused on the issue of restoring GIC, as developed in Section 5. We have tested Algorithm 9 against all Renault car configuration instances introduced earlier. For each instance, the protocol we have used is the following. First, we have built a complete GIC-staged configuration trace T (branch), by randomly assigning each variable in turn (and subsequently maintaining GIC). Then, we have discarded arbitrarily a decision used for T, and applied our algorithm that restores GIC. Actually, we have successively collected information about GIC restoration for decisions discarded at levels i ranging respectively from 0 (first decision taken) to 80.{sup:5} After decision 80, all these instances only contain singleton domains, and so, are completely solved. In other words, we have independently tested GIC restoration on T, when a decision was discarded at level {a mathematical formula}i=0, at level {a mathematical formula}i=1, and so on until level 80. The results we present are given on average over 100 random complete GIC-staged configuration traces per level. Such traces are computed initially by randomly selecting decisions.
      </paragraph>
      <paragraph>
       We have been interested in:
      </paragraph>
      <list>
       <list-item label="•">
        the total number of values (i.e., the number of values over all variable domains), denoted by # values
       </list-item>
       <list-item label="•">
        the number of unclassified values when discarding a decision, at the point before refining classification intervals through MAC; this is denoted by “#? values before refinement”
       </list-item>
       <list-item label="•">
        the number of unclassified values when discarding a decision, at the point just after having refined classification intervals through MAC; this is denoted by “#? values after refinement”
       </list-item>
      </list>
      <paragraph>
       We have observed the same trend when testing the 6 configuration instances: i) it is only when the retracted decision belongs to the first ones taken by the user that a substantial computing effort is required, and ii) classification refinement by MAC is very useful. Figs. 4(a) and 4(b) show results for the car models Megane (a mid-size instance) and Master (a large size instance). The x-axis indicates the level at which the decision (from the complete GIC-staged configuration trace) was discarded before restoring GIC. For example, when the retraction decision level is 8, we can see for Master that the number of unclassified values after MAC refinement is around 10 (on average). The impact of classification refinement by MAC is clearly visible, as it corresponds to the gap between the two bottom curves. (Note the logarithmic scale for the y-axis.) The two curves only merge when the average number of unclassified values is around 1.
      </paragraph>
      <paragraph>
       It is also interesting to see how many calls to the procedure (oracle) searchSolutionFor are necessary to classify the remaining unclassified values after refining intervals through MAC. In Section 5, we mentioned the possibility of a dichotomic approach (see Theorem 8). However, for configuration instances, picking {a mathematical formula}s=hmax−1 at line 18 of Algorithm 9 is a relevant choice because most of the time it allows us to prove directly that the value is GIC-consistent. This is what we have observed: the proportion of successful calls (i.e., of calls returning a solution) is very high. Besides, when a solution is found, multidirectionality can be used to refine classification intervals of other values (lines 23–25 in Algorithm 9). Fig. 5 shows the average number of calls to searchSolutionFor for each instance and each retraction decision level. For the largest instances, in the worst-case (level 0), the number of calls is around 100. At level 8, less than 10 calls are required. Table 6 shows the average number of unclassified values after GAC refinement (# ? values) and the average number of calls to searchSolutionFor (# calls), computed over all retraction decision levels. The number of calls to the oracle is never more than 75% of the number of unclassified values.
      </paragraph>
      <paragraph>
       Table 7 gives the CPU time required to restore GIC. The worst-case maximum time is 1.5 seconds for megane, but note this is only 0.2 second on average. This confirms that our approach can perfectly be used in an interactive configuration context.
      </paragraph>
      <paragraph>
       Finally, Table 8 shows how the algorithm we propose for restoring GIC after discarding a decision {a mathematical formula}δi (referred to as optimized GIC restoration) behaves with respect to a simple algorithm (referred to as naive GIC restoration) that just erases all decisions from {a mathematical formula}δi to the last before replaying all of them except the discarded decision {a mathematical formula}δi, while maintaining GIC with GIC4. The results are given on average for 100 random GIC-staged configuration traces, with GIC restoration triggered after 80 decisions have been taken (32 for souffleuse) and the first of these decisions has been discarded. Note that discarding the first decision is the most adverse case (i.e., requiring the most computing effort), which is the reason for studying this particular case. We observe that during this process, the number of calls to the oracle searchSolutionFor is very limited when our optimized algorithm is used. Our algorithm is between 2 and 5 times faster than the naive one. On these instances, our algorithm never requires more than 1 second.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>