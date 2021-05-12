<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    A parametric propagator for pairs of Sum constraints with a discrete convexity property.
   </title>
   <abstract>
    We introduce a propagator for pairs of Sum constraints, where the expressions in the sums respect a form of convexity. This propagator is parametric and can be instantiated for various concrete pairs, including Deviation, Spread, and the conjunction of Linear≤ and Among. We show that despite its generality, our propagator is competitive in theory and practice with state-of-the-art propagators.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Constraint programming (CP) is a set of techniques to model and solve combinatorial problems using a mix of inference and search. Each constraint of the problem is associated with a propagator that performs pruning, i.e., the removal from the search space of impossible values for the variables of the constraint.
     </paragraph>
     <paragraph>
      Many combinatorial problems involve Sum constraints, along with other constraints. It is however well-known that a propagator for a Sum constraint taken in isolation is not able to perform a lot of pruning since the estimation of the minimum or maximum of a sum does not take other constraints into account. Several authors have studied how to include other constraints (sharing some variables) in the propagator for Sum, either in particular cases (e.g., Spread[2], Deviation[3], IncreasingSum[4], and Sum with cliques [5]), or in general (e.g., ObjectiveSum[6]).
     </paragraph>
     <paragraph>
      In the present work, we focus on a parametric constraint, called TwoSums hereafter, which can be cast as{a mathematical formula}{a mathematical formula} for any {a mathematical formula}n≥1. The parameters {a mathematical formula}fi and {a mathematical formula}gi are functions from integers to integers and the {a mathematical formula}fi (respectively {a mathematical formula}gi) can differ for each i. Initially, we require {a mathematical formula}f‾, {a mathematical formula}g_, and {a mathematical formula}g‾ to be constants, but Section 7 shows how to use variables instead, along with other extensions of this constraint. As usual when describing a constraint and its propagator, we assume that all {a mathematical formula}xi are distinct variables.
     </paragraph>
     <paragraph>
      Finding a solution to the conjunction of (1) and (2) is in general NP-complete as it includes as a special case the knapsack problem (by taking {a mathematical formula}fi(v)=ai⋅v and {a mathematical formula}gi(v)=bi⋅v, where the {a mathematical formula}ai and {a mathematical formula}bi are constants). In this paper, we will discuss a large class of functions {a mathematical formula}fi and {a mathematical formula}gi for which either domain consistency, bounds{a mathematical formula}(Z) consistency, or bounds{a mathematical formula}(R) consistency [7], [8] can be achieved in polynomial time. We present a parametric propagator for this tractable class and show how to instantiate it for various functions {a mathematical formula}fi and {a mathematical formula}gi. We show that the instantiations include among others bounds{a mathematical formula}(Z)-consistent propagators for the constraints Deviation[3] and Spread[2] and a domain-consistent propagator for the conjunction of Linear≤ and Among[9].
     </paragraph>
     <paragraph>
      While the worst-case time complexity of our parametric propagator is {a mathematical formula}O(n⋅d2+n2⋅d), where d is the size of the largest domain,{sup:1} our propagator, once instantiated, matches the theoretical time complexity and practical efficiency of several previously published specialised propagators, as shown in Table 1. However, our propagator is not limited to the reproduction of existing propagators. Table 1 also lists the time complexity and consistency for several instantiations that we identified as being useful general cases but for which, to the best of our knowledge, no propagator existed. This list is not exhaustive and one can add many problem-specific instantiations: see for instance Example 3. Note that while achieving domain consistency on the knapsack problem is NP-hard, bounds{a mathematical formula}(R) consistency is achieved in polynomial time by our propagator (last line in Table 1).
     </paragraph>
     <paragraph>
      After introducing some notation and background in Section 2, we present our TwoSums propagator in Sections 3 to 5. We study its complexity in Section 6 and give some implementation notes. In Section 7, we show how the applicability of the propagator can be extended. Afterwards, we present in Section 8 several instantiations of the propagator, including a detailed case study for Deviation. Finally, Section 9 presents some experimental results showing that the genericity of our approach is not detrimental to performance. We review the related work in Section 10 before concluding in Section 11.
     </paragraph>
     <paragraph>
      This paper is an extended version of [1], expanded with new examples, proofs, and implementation notes.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Notation and background
     </section-title>
     <paragraph>
      For a function f and value v, we write {a mathematical formula}f−1(v) for the set of values having v as image: {a mathematical formula}{u|f(u)=v}. For a function f and set S, we write {a mathematical formula}f(S) for the set of images of the elements of S: {a mathematical formula}{f(u)|u∈S}. We use {a mathematical formula}xi, {a mathematical formula}vi, {a mathematical formula}fi to represent single variables, values, and functions, while x, v, f represent vectors of variables, values, and functions (e.g., {a mathematical formula}x=〈x1,x2,…,xn〉).
     </paragraph>
     <paragraph>
      Constraint programming (CP) is a set of techniques to model and solve problems defined by a set of existentially quantified variables and a set of constraints over those variables. During the solution process, each variable x is associated with a current domain, denoted {a mathematical formula}Dx, of candidate values for this variable. Each variable is given an initial domain in the model. The smallest and largest values of {a mathematical formula}Dx are denoted respectively {a mathematical formula}min⁡(Dx) and {a mathematical formula}max⁡(Dx). For a constraint c and the variables x involved in c, an assignment of values {a mathematical formula}vi∈Dxi, for all {a mathematical formula}xi∈x, is called a solution to c if the vector v of values satisfies c.
     </paragraph>
     <paragraph>
      One of the main operations in CP-style constraint solving is the filtering of the domain of a variable with respect to a constraint: values that can be proven not to belong to any solution of a constraint c (given the domains of the other variables) are removed from the domain of each variable. This is performed by an algorithm called a propagator of c.
     </paragraph>
     <paragraph>
      A propagator does not need to remove all values that do not participate in any solution, as doing so can be computationally too expensive. If a propagator removes all such values, then it is said to enforce domain consistency. If a propagator always enforces domain consistency, then it is called domain consistent. Weaker notions of consistency exist. In particular, bounds{a mathematical formula}(Z)consistency (see, e.g., [7], [8]) is achieved if, for each variable x, both {a mathematical formula}min⁡(Dx) and {a mathematical formula}max⁡(Dx) belong to a solution in which the other variables take supporting integer values within their domain bounds. If a propagator always enforces bounds{a mathematical formula}(Z) consistency, then it is called bounds{a mathematical formula}(Z)consistent. Similarly, bounds{a mathematical formula}(R)consistency (see also, e.g., [7], [8]) is achieved if, for each variable x, both {a mathematical formula}min⁡(Dx) and {a mathematical formula}max⁡(Dx) belong to a solution in which the other variables take supporting real values within their domain bounds. Bounds{a mathematical formula}(R) consistency is weaker than bounds{a mathematical formula}(Z) consistency in that it considers that supporting values need not be integers. Bounds{a mathematical formula}(R) consistency is the consistency usually considered for the implementation of propagators for Linear constraints. If a propagator always enforces bounds{a mathematical formula}(R) consistency, then it is called bounds{a mathematical formula}(R)consistent.
     </paragraph>
     <paragraph>
      In this work, we make the distinction between the Sum constraint and the Linear constraints. A Sum constraint is any constraint {a mathematical formula}∑i∈[1,n]fi(xi)#y, for any functions {a mathematical formula}fi from integers to integers, with {a mathematical formula}#∈{&lt;,≤,=,≠,≥,&gt;}, and y being an integer variable or constant. The {a mathematical formula}fi in the Sum constraint may be instantiated to give rise to many existing constraints. In particular, {a mathematical formula}Linear≤(x,a,s) holds if and only if the weighted sum of variables {a mathematical formula}xi with given integer weights {a mathematical formula}ai is at most the integer variable s, i.e., {a mathematical formula}∑i∈[1,n]ai⋅xi≤s. Similarly, {a mathematical formula}Linear=(x,a,s) holds if and only if the weighted sum of variables {a mathematical formula}xi with given integer weights {a mathematical formula}ai is equal to the integer variable s, i.e., {a mathematical formula}∑i∈[1,n]ai⋅xi=s. These constraints have been studied among others in [10] where many practical improvements of the usual {a mathematical formula}O(n) bounds{a mathematical formula}(R)-consistent propagator are introduced. In the case of Linear≤, bounds{a mathematical formula}(R) consistency coincides with domain consistency.
     </paragraph>
     <paragraph>
      The {a mathematical formula}Spread(x,μ,s) constraint [2] holds if and only if the average of the integer variables {a mathematical formula}xi is the given rational number μ and the sum of their scaled squared deviations from μ is less than or equal to the integer variable s, i.e., {a mathematical formula}∑i∈[1,n]xi=n⋅μ∧∑i∈[1,n](n⋅xi−n⋅μ)2≤s. While a generalised constraint with a variable average exists [2], we consider here only the case of a fixed average, which is used in most applications. Following [2], all values in the second inequality are scaled by n to work with integer values, as in general the average μ might not be integer but {a mathematical formula}n⋅μ surely is. An {a mathematical formula}O(n⋅log⁡n) bounds{a mathematical formula}(Z)-consistent propagator for Spread has been introduced in [11].
     </paragraph>
     <paragraph>
      Similarly, the {a mathematical formula}Deviation(x,μ,d) constraint [3] holds if and only if the average of the integer variables {a mathematical formula}xi is the given rational number μ and the sum of their scaled deviations from μ is less than or equal to the integer variable d, i.e., {a mathematical formula}∑i∈[1,n]xi=n⋅μ∧∑i∈[1,n]|n⋅xi−n⋅μ|≤d. Again, we consider only the case of a fixed average. An {a mathematical formula}O(n) bounds{a mathematical formula}(Z)-consistent propagator for Deviation has been presented in [3].
     </paragraph>
     <paragraph>
      The constraint {a mathematical formula}Lp-{a mathematical formula}Norm(x,μ,d), with {a mathematical formula}0&lt;p&lt;+∞ holds if and only if {a mathematical formula}∑i∈[1,n]xi=n⋅μ∧∑i∈[1,n]|n⋅xi−n⋅μ|p≤s. It generalises Spread (with {a mathematical formula}p=2) and Deviation (with {a mathematical formula}p=1).
     </paragraph>
     <paragraph>
      The {a mathematical formula}Among(x,V,c) constraint holds if and only if the number of integer variables {a mathematical formula}xi taking their value in the given integer set {a mathematical formula}V is equal to the integer variable c. The Among constraint can be represented using a Sum constraint as {a mathematical formula}∑i∈[1,n][xi∈V]=c, where the notation {a mathematical formula}[γ] is the Iverson bracket and is defined to be 1 if γ is true, and 0 otherwise. A domain-consistent propagator for the conjunction of a Linear≤ constraint and an Among constraint has been published in [9], with an {a mathematical formula}O(n⋅(log⁡n+d)) time complexity, where d is the size of the largest {a mathematical formula}Dxi.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Overview of the approach
     </section-title>
     <paragraph>
      Our approach for propagating the TwoSums constraint contains two parts. First (as discussed in Section 4), we compute a sharp lower bound b on the left-hand side {a mathematical formula}∑i∈[1,n]fi(xi) of constraint (1) under constraint (2), together with a support{a mathematical formula}sb, i.e., an assignment of the {a mathematical formula}xi yielding value b and satisfying constraint (2). The conjunction of (1) and (2) is feasible if and only if this lower bound, which we call the feasibility bound, is at most {a mathematical formula}f‾, the right-hand side of constraint (1). To compute this feasibility bound, we introduce new functions derived from the {a mathematical formula}fi and {a mathematical formula}gi. We show that the feasibility bound can be greedily computed if the newly introduced functions are discretely convex[12].
     </paragraph>
     <paragraph label="Example 1">
      For the conjunction of {a mathematical formula}Linear≤(x,a,s) and {a mathematical formula}Among(x,V,c)[9], the feasibility bound is computed by first taking for each variable an extreme value in its domain, and then iteratively modifying the values taken by some variables until the Among constraint is satisfied. The initial value is the largest in the domain of {a mathematical formula}xi if {a mathematical formula}ai&lt;0 and is the smallest otherwise, so that the value of the weighted sum is as small as possible. The iterative modification picks a variable such that changing its value causes the smallest increase to the bound. As the increase caused by a variable is independent of the values taken by the other variables, the iteration order can be determined beforehand by sorting. Full details are provided in [9].  □
     </paragraph>
     <paragraph>
      In the second part (discussed in Section 5) of our propagator for TwoSums, the domain of each variable {a mathematical formula}xj is filtered by computing for each value u in its domain a sharp lower bound on the left hand side {a mathematical formula}∑i∈[1,n]fi(xi) of constraint (1) under constraint (2) when {a mathematical formula}xj is assigned u. If this lower bound is larger than {a mathematical formula}f‾, then u is removed from the domain of {a mathematical formula}xj. The lower bound for each pair {a mathematical formula}(xj,u) is computed incrementally from the support {a mathematical formula}sb for the feasibility bound, thanks to the discrete convexity property, and does not need to be computed explicitly for each value. We also present an improved propagator when an additional property holds on {a mathematical formula}fj and {a mathematical formula}gj, namely a form of monotonicity.
     </paragraph>
     <paragraph label="Example 2">
      For the conjunction of {a mathematical formula}Linear≤(x,a,s) and {a mathematical formula}Among(x,V,c), the filtering for each variable {a mathematical formula}xj amounts to computing two values: the lower bound {a mathematical formula}bj∈ for the weighted sum of all the other variables when variable {a mathematical formula}xj is assigned a value in {a mathematical formula}V, and the lower bound {a mathematical formula}bj∉ when {a mathematical formula}xj is assigned a value not in {a mathematical formula}V. One of these two bounds ({a mathematical formula}bj∈ if {a mathematical formula}sjb∈V and {a mathematical formula}bj∉ otherwise) is directly computed from the feasibility bound b by subtracting the contribution of {a mathematical formula}xj. The other bound can be computed incrementally from the first bound by modifying the value of another variable than {a mathematical formula}xj so that the modification causes the smallest increase of the feasibility bound. The two new bounds are then used to remove values from the domain of {a mathematical formula}xj: the bound {a mathematical formula}bj∈ is used to remove possibly values that are in {a mathematical formula}V, and {a mathematical formula}bj∉ to remove possibly values that are not in {a mathematical formula}V. Again, details are provided in [9]. □
     </paragraph>
     <paragraph>
      Our propagator for TwoSums is parametric, depending on the {a mathematical formula}fi and {a mathematical formula}gi. The time complexity and the level of consistency achieved depend on the shape of the {a mathematical formula}fi and {a mathematical formula}gi and on the values given to the parameters (see Sections 6 and 7).
     </paragraph>
     <paragraph label="Example 3">
      Throughout the rest of the paper, we will use the following running example. Consider a workshop with n workers. The unknown daily workload in number of hours of each worker is encoded by variable {a mathematical formula}xi for each worker {a mathematical formula}i∈[1,n]. The daily total workload must be equal to a given integer t. In addition, each worker has a given nominal workload {a mathematical formula}wi, from which they can deviate but at some cost given by the following function: {a mathematical formula}fi(v)=max⁡{ri⋅(wi−v),qi⋅(v−wi)}, i.e., the cost increases linearly with a slope of {a mathematical formula}ri&gt;0 if the actual workload is below the nominal one, and with a slope of {a mathematical formula}qi&gt;0 if the actual workload is above the nominal one. The total cost must be under some given integer upper bound c. This part of the problem (a typical workshop would have additional constraints) is modelled as:{a mathematical formula} This is an instantiation of constraints (1) and (2). In subsequent examples, we will use the following values for the parameters: {a mathematical formula}n=4, {a mathematical formula}c=5, {a mathematical formula}t=10, {a mathematical formula}w=〈2,3,2,2〉, {a mathematical formula}r=〈1,1,1,2〉, and {a mathematical formula}q=〈2,2,3,3〉. We also define {a mathematical formula}Dxi=[0,5] for all {a mathematical formula}i∈[1,4]. Fig. 1 shows the functions {a mathematical formula}fi over the given domains.  □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Feasibility test
     </section-title>
     <paragraph>
      The TwoSums constraint is satisfiable if and only if the cost (i.e., the value of the objective function) of an optimal solution to the following problem is at most the value {a mathematical formula}f‾:{a mathematical formula} We gradually show in the next sub-sections how to compute greedily this cost, called the feasibility bound, together with a support, which will be used for filtering in Section 5.
     </paragraph>
     <section label="4.1">
      <section-title>
       Problem reformulation
      </section-title>
      <paragraph>
       We reformulate problem (3) into a simpler problem in two steps. The first step introduces for each i a new function {a mathematical formula}hi that captures the relation between {a mathematical formula}fi and {a mathematical formula}gi. This results in having only one function per variable instead of two. The second step splits the resulting reformulated problem into two subproblems that can be solved separately.
      </paragraph>
      <paragraph label="Example 4">
       First step  After introducing new variables {a mathematical formula}yi, so that {a mathematical formula}yi=gi(xi) for each i, we state the following new problem:{a mathematical formula} where we introduce a new function {a mathematical formula}hi:gi(Dxi)→fi(Dxi) for each i. This function is defined as {a mathematical formula}hi(v)=min⁡fi(gi−1(v))=min⁡{fi(u)|u∈Dxi∧gi(u)=v}, that is {a mathematical formula}hi(v) is the smallest value of {a mathematical formula}fi(xi) that can be attained when {a mathematical formula}gi(xi) is equal to value v. Note that the definition of {a mathematical formula}hi depends on the current domain of {a mathematical formula}xi. In Example 3, we have {a mathematical formula}gi(u)=u for all u, hence {a mathematical formula}gi−1(u)={u}. It follows that {a mathematical formula}hi(v)=fi(v), but restricted to the current domain of {a mathematical formula}xi.  □
      </paragraph>
      <paragraph label="Proof">
       We now prove that the feasibility bound can also be computed from problem (4). All optimal solutions to problems(3)and(4)have the same cost.Let v denote a vector of values for the vector y of variables. For each value {a mathematical formula}vi, we choose an arbitrary value {a mathematical formula}ui in {a mathematical formula}Dxi such that {a mathematical formula}gi(ui)=vi and {a mathematical formula}fi(ui)=hi(vi). Such a value {a mathematical formula}ui always exists, by the definition of {a mathematical formula}hi. Then the vector u is a feasible solution to problem (3) if and only if v is a feasible solution to problem (4), and they have the same cost. In addition, any other assignment {a mathematical formula}u′ such that {a mathematical formula}gi(ui′)=vi for each i has a cost larger than or equal to the cost of u and v, by the definition of {a mathematical formula}hi. Hence u is optimal if and only if v is optimal.  □
      </paragraph>
      <paragraph label="Proof">
       Second step  We define a new function, called H, from integers to integers:{a mathematical formula} That is, {a mathematical formula}H(b) is the minimum of the sum of the {a mathematical formula}hi(yi) when the sum of the {a mathematical formula}yi is equal to b. For a given integer b, we define {a mathematical formula}sb to be an assignment to y such that {a mathematical formula}b=∑i∈[1,n]sib and {a mathematical formula}H(b)=∑i∈[1,n]hi(sib). We call {a mathematical formula}sb a support for b. We propose the following new problem:{a mathematical formula} where z is a new variable. We now prove that the feasibility bound can also be computed from problem (6), as the latter has the same optimal cost as problem (4), and as problem (3) by Lemma 1. All optimal solutions to problems(4)and(6)have the same cost.This is shown by replacing {a mathematical formula}H(z) by its definition (5) in the formulation of problem (6). This gives{a mathematical formula} which is equal to{a mathematical formula} Substituting z by {a mathematical formula}∑i∈[1,n]yi leads to the formulation of problem (4).  □
      </paragraph>
      <paragraph>
       Problems (4) and (6) are more interesting than problem (3) in three respects. First, it is simpler to reason with only one function per variable (namely {a mathematical formula}hi) instead of two (namely {a mathematical formula}fi and {a mathematical formula}gi). Second, the domain {a mathematical formula}Dyi, which is equal to {a mathematical formula}gi(Dxi), might be much smaller than {a mathematical formula}Dxi (but never larger), potentially reducing a lot the number of values the algorithms must consider. Third, introducing H allows us to compute the feasibility bound in two steps: (i) construct H from the {a mathematical formula}hi, and (ii) find an optimal solution to (6). This can be done greedily, as we will show in Section 4.4, if all {a mathematical formula}hi are discretely convex, which is a concept we recall now.
      </paragraph>
      <paragraph label="Definition 1">
       [12]A function {a mathematical formula}f:A→B, where {a mathematical formula}A,B⊆Z, is discretely convex if
      </paragraph>
      <list>
       <list-item label="1.">
        A is an interval, and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}∀v∈A:(v−1)∈A∧(v+1)∈A⇒2⋅f(v)≤f(v−1)+f(v+1).
       </list-item>
      </list>
      <paragraph>
       The notion of discrete convexity is an adaptation of the usual convexity from the reals to the integers. The intuition is that a function on integers is discretely convex if its natural extension to the reals is convex. This notion has been studied in depth, for instance in [12]. It is also related to the notion of submodular functions on sets [13].
      </paragraph>
      <paragraph>
       The two conditions in Definition 1 on the {a mathematical formula}hi theoretically restrict the applicability of our approach. Those restrictions and their lifting in practice are discussed further in Section 7.1 but the next example already shows the broad applicability of our approach.
      </paragraph>
      <paragraph label="Example 5">
       Table 2 presents the functions {a mathematical formula}fi, {a mathematical formula}gi, and {a mathematical formula}hi for several pairs of constraints.
      </paragraph>
      <list>
       <list-item label="•">
        The first line shows the example of a constant {a mathematical formula}gi function, i.e., {a mathematical formula}gi(u) does not depend on the value of u, in which case the domain of {a mathematical formula}hi is a singleton and {a mathematical formula}hi is trivially discretely convex.
       </list-item>
       <list-item label="•">
        If {a mathematical formula}gi is a characteristic function, i.e., a function taking only values 0 and 1 as when defined using the Iverson bracket (e.g., Linear≤ and Among, as well as Linear≤ and Maximum), then the domain of {a mathematical formula}hi is composed of only two values and {a mathematical formula}hi is typically defined by giving a formula for each value. In those cases, {a mathematical formula}hi is always discretely convex.
       </list-item>
       <list-item label="•">
        If {a mathematical formula}gi is the identity function, as for Deviation, Spread, and {a mathematical formula}Lp-Norm, then {a mathematical formula}hi is equal to {a mathematical formula}fi. In such a case, {a mathematical formula}hi is discretely convex as long as {a mathematical formula}Dxi is relaxed to its smallest enclosing interval. As discussed in Section 7.1, this relaxation maintains the correctness of our approach but only bounds{a mathematical formula}(Z) consistency can be achieved (see Table 1).
       </list-item>
       <list-item label="•">
        If {a mathematical formula}gi is a linear function, as for Linear= alone and the conjunction of Linear≤ and Linear=, then {a mathematical formula}hi is not discretely convex because {a mathematical formula}gi(Dxi) might not be an interval even if {a mathematical formula}Dxi is an interval. However, as discussed in Section 7.1, relaxing the domain of {a mathematical formula}hi to its smallest enclosing interval maintains the correctness of our approach: as shown in Table 1, one achieves only bounds{a mathematical formula}(R) consistency.
       </list-item>
       <list-item label="•">
        The last line shows the example of a pair of constraints {a mathematical formula}fi and {a mathematical formula}gi that are very different from the previous pairs but still give rise to a discretely convex {a mathematical formula}hi when {a mathematical formula}Dxi is relaxed to its smallest enclosing interval.  □
       </list-item>
      </list>
      <paragraph>
       Before providing algorithms in Section 4.4 to compute the feasibility bound, we need to introduce some notions in Section 4.2 and characterise H in Section 4.3.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Deltas, segments, slopes, and breakpoints
      </section-title>
      <paragraph>
       Let {a mathematical formula}f:A→B be an arbitrary function with {a mathematical formula}A,B⊆Z. Given some value v in A, we call right delta (respectively left delta) the increase of f when v increases (respectively decreases) by 1. Formally: {a mathematical formula}Δ+(f,v)=f(v+1)−f(v) and {a mathematical formula}Δ−(f,v)=f(v−1)−f(v); the value of {a mathematical formula}Δ+(f,v) (respectively {a mathematical formula}Δ−(f,v)) is +∞ when {a mathematical formula}v+1 (respectively {a mathematical formula}v−1) is not in A.
      </paragraph>
      <paragraph>
       A segment of f is a maximal interval {a mathematical formula}[ℓ,u] of its domain where the right delta is constant. Formally: {a mathematical formula}Δ+(f,v)=Δ+(f,v+1) for all {a mathematical formula}v∈[ℓ,u−1], with {a mathematical formula}ℓ≤u, {a mathematical formula}Δ+(f,ℓ−1)≠Δ+(f,ℓ), and {a mathematical formula}Δ+(f,u−1)≠Δ+(f,u). The endpoints ℓ and u of a segment {a mathematical formula}[ℓ,u] of f are called breakpoints of f. The length of a segment {a mathematical formula}[ℓ,u] is {a mathematical formula}u−ℓ, that is the length of a line from ℓ to u, and not the number {a mathematical formula}u−ℓ+1 of its integer elements. The slope of a segment {a mathematical formula}[ℓ,u] is {a mathematical formula}Δ+(f,ℓ). Hence the slope of a function is constant inside any of its segments and changes at its breakpoints.
      </paragraph>
      <paragraph>
       The domain of f can be uniquely partitioned into its segments, and each value of the domain belongs to one or two segments. For a value v, the breakpoint on the right of v, denoted by {a mathematical formula}bp+(f,v), is u if v belongs to some segment {a mathematical formula}[ℓ,u] with {a mathematical formula}u≠v, and otherwise undefined, denoted by +∞. Similarly, {a mathematical formula}bp−(f,v) denotes the breakpoint on the left of v, if any, otherwise −∞.
      </paragraph>
      <paragraph>
       Let f be a discretely convex function. For any two consecutive segments, the slope of the former is smaller than the slope of the latter, hence no two segments have the same slope. Also, {a mathematical formula}Δ+(f,v)=+∞ only for the largest value v in A, because A is an interval, and {a mathematical formula}Δ−(f,v)=+∞ only for the smallest value v in A.
      </paragraph>
      <paragraph>
       Fig. 2 illustrates these notions on a discretely convex function. The points are part of the actual function, while the segments joining them are used as a visual guide to identify the segments and their slopes.
      </paragraph>
      <paragraph label="Example 6">
       Each function {a mathematical formula}hi of Example 3 is composed of two segments (see Fig. 1). For {a mathematical formula}i=1, the function {a mathematical formula}h1, defined as {a mathematical formula}h1(u)=max⁡{1⋅(2−u),2⋅(u−2)} over the interval {a mathematical formula}[0,5], is composed of the following two segments: one spans the interval {a mathematical formula}[0,2] with slope −1, the other spans the interval {a mathematical formula}[2,5] with slope 2. For {a mathematical formula}u∈[0,1], we have {a mathematical formula}Δ+(h1,u)=−1 and {a mathematical formula}bp+(h1,u)=2. For {a mathematical formula}u∈[2,4], we have {a mathematical formula}Δ+(h1,u)=2 and {a mathematical formula}bp+(h1,u)=5. Finally, {a mathematical formula}Δ+(h1,5)=+∞ and {a mathematical formula}bp+(h1,5)=+∞.  □
      </paragraph>
      <paragraph>
       The basic properties of the special values +∞ and −∞ used in our algorithms are, for any {a mathematical formula}v∈Z: {a mathematical formula}−∞&lt;v&lt;+∞, {a mathematical formula}v+(+∞)=+∞, {a mathematical formula}v+(−∞)=−∞, {a mathematical formula}v−(−∞)=+∞, {a mathematical formula}v−(+∞)=−∞, {a mathematical formula}min⁡(v,+∞)=v, and {a mathematical formula}v/+∞=0.
      </paragraph>
     </section>
     <section label="4.3">
      Characterisation of the H function
      <paragraph>
       We will show in Section 4.4 that when the {a mathematical formula}hi are discretely convex, problem (6) is easy to solve by greedy search, because H is then also discretely convex and can be calculated efficiently. In order to prove those claims, we first need to study closely the functions H and {a mathematical formula}hi, and the relationship between them and between supports. We first show how one can incrementally get a support for a value {a mathematical formula}b+1 from a support for a value b.
      </paragraph>
      <paragraph label="Proof">
       If each{a mathematical formula}hiis discretely convex, then given a support{a mathematical formula}sbfor some value b, there exists a support{a mathematical formula}sb+1for{a mathematical formula}b+1and some{a mathematical formula}j∈[1,n]such that{a mathematical formula}sib+1=sibfor all{a mathematical formula}i≠j, and{a mathematical formula}sjb+1=sjb+1(assuming b and{a mathematical formula}b+1are in the domain of H).By definition, a support {a mathematical formula}sb for any b is such that {a mathematical formula}∑i∈[1,n]sib=b and {a mathematical formula}∑i∈[1,n]hi(sib)=H(b). For any j and k with {a mathematical formula}k≠j, the sum{a mathematical formula} also equals b as we added 1 to one value and removed 1 from another one.{sup:2} Hence by definition of H (since the {a mathematical formula}sib are the values that minimise {a mathematical formula}H(b)), we have:{a mathematical formula} Rearranging and cancelling out common terms gives:{a mathematical formula} If {a mathematical formula}hj is discretely convex, then we have that:{a mathematical formula} And:{a mathematical formula} This means that adding two to any single {a mathematical formula}sjb and reducing another {a mathematical formula}skb by one to arrive at the sum {a mathematical formula}b+1 will have a higher cost than simply adding one to a single {a mathematical formula}sjb. Because each {a mathematical formula}hi is discretely convex, this is true for any increment larger than one. Hence it is possible to find a support {a mathematical formula}sb+1 for {a mathematical formula}b+1 from a support {a mathematical formula}sb for b by increasing any suitable {a mathematical formula}sib by one.  □
      </paragraph>
      <paragraph>
       Lemma 3 also shows that it is possible to find a support {a mathematical formula}sb−1 by subtracting one from any suitable {a mathematical formula}sib. We can now prove the following important result:
      </paragraph>
      <paragraph label="Proof">
       If each{a mathematical formula}hiis discretely convex, then H is discretely convex.The domain of each {a mathematical formula}hi is an interval {a mathematical formula}[si,ui], so that the domain of H is the interval {a mathematical formula}[∑i∈[1,n]si,∑i∈[1,n]ui]. We need to show that {a mathematical formula}H(b)−H(b−1)≤H(b+1)−H(b). If {a mathematical formula}sib is a support for some b then by Lemma 3 there are some k and j such that {a mathematical formula}H(b−1)=h1(s1b)+⋯+hk(skb−1)+⋯+hn(snb) and {a mathematical formula}H(b+1)=h1(s1b)+⋯+hj(sjb+1)+⋯+hn(snb). Therefore {a mathematical formula}H(b)−H(b−1)=hk(skb)−hk(skb−1) and {a mathematical formula}H(b+1)−H(b)=hj(sjb+1)−hj(sjb) and, by (7), {a mathematical formula}H(b)−H(b−1)≤H(b+1)−H(b). Hence H is discretely convex.  □
      </paragraph>
      <paragraph>
       We now show how to calculate H efficiently by giving a characterisation of its minimum and its segments. Here, for any non-empty set S and function f, the expression {a mathematical formula}argmini∈Sf(i) returns one arbitrary value {a mathematical formula}i∈S that minimises {a mathematical formula}f(i). In the following, {a mathematical formula}b⁎ represents a value minimising the value of {a mathematical formula}H(b⁎).
      </paragraph>
      <paragraph label="Proof">
       A support{a mathematical formula}sb⁎for a value{a mathematical formula}b⁎that minimises H is such that{a mathematical formula}sib⁎=argminvi∈gi(Dxi)hi(vi)for all{a mathematical formula}i∈[1,n].If {a mathematical formula}sb⁎ is a support for {a mathematical formula}b⁎, then {a mathematical formula}b⁎ is equal to {a mathematical formula}∑i∈[1,n]sib⁎ and {a mathematical formula}H(b⁎)=∑i∈[1,n]hi(sib⁎). Since each {a mathematical formula}sib⁎=argminvi∈gi(Dxi)hi(vi) corresponds to the minimum value obtainable by {a mathematical formula}hi, it is not possible to reduce the value {a mathematical formula}∑i∈[1,n]hi(sib⁎) by picking a different value for any {a mathematical formula}sib⁎.  □
      </paragraph>
      <paragraph>
       There are potentially several {a mathematical formula}sb⁎ that minimise H. The correctness of our approach does not depend on a particular choice of support.
      </paragraph>
      <paragraph label="Example 7">
       For the constraints of Example 3, there is only one value minimising {a mathematical formula}hi for each i, namely the nominal workload {a mathematical formula}wi. Hence, the unique {a mathematical formula}sb⁎ is equal to the nominal workloads {a mathematical formula}w=〈2,3,2,2〉. Then {a mathematical formula}b⁎=9=2+3+2+2 and {a mathematical formula}H(b⁎)=0 as {a mathematical formula}hi(wi)=0 for all i.  □
      </paragraph>
      <paragraph>
       We now characterise the segments of H. We first establish the relation between the slope of H at some value b and the slope of each {a mathematical formula}hi at {a mathematical formula}sib.
      </paragraph>
      <paragraph label="Proof">
       If{a mathematical formula}sbis a support for some value b, then{a mathematical formula}Δ+(hi,sib)≥Δ+(H,b)and{a mathematical formula}Δ−(hi,sib)≥Δ−(H,b)for all{a mathematical formula}i∈[1,n].If b is increased by one, then one of the {a mathematical formula}sib must be increased by one (by Lemma 3). To reach the minimum value for {a mathematical formula}b+1, one needs to increase the value of a variable {a mathematical formula}yk for which {a mathematical formula}Δ+(hk,skb) is the smallest. So the increase of H, namely {a mathematical formula}Δ+(H,b), is equal to {a mathematical formula}Δ+(hk,skb), which is smaller than or equal to {a mathematical formula}Δ+(hi,sib) for any other i. A similar argument is used for a decrease of b.  □
      </paragraph>
      <paragraph>
       The proof of Lemma 6 also shows that there is at least one i such that {a mathematical formula}Δ+(hi,sib) is equal to {a mathematical formula}Δ+(H,b). This gives us a way to define the segments of H:
      </paragraph>
      <paragraph label="Lemma 7">
       The length of each segment of H is equal to the sum of the lengths of the segments in the functions{a mathematical formula}hiwith the same slope.
      </paragraph>
      <paragraph label="Proof">
       In the proof of Lemma 6, we saw that {a mathematical formula}Δ+(H,b) is equal to a minimal {a mathematical formula}Δ+(hk,skb). If one wants to increase b by more than one, then the increase per unit stays constant as long as there is at least one variable with slope equal to {a mathematical formula}Δ+(H,b). This defines a segment of slope {a mathematical formula}Δ+(H,b), whose length is equal to the sum of the lengths of the segments of all functions {a mathematical formula}hi with the same slope.  □
      </paragraph>
      <paragraph>
       We can use Lemma 5, Lemma 7 to construct H efficiently, as shown in the following example. Section 6.1 presents several ways to implement this construction in practice.
      </paragraph>
      <paragraph label="Example 8">
       Given the domain {a mathematical formula}[0,5] for all {a mathematical formula}xi, the function H for the constraints of Example 3 can be constructed as follows (see also Fig. 3). Each {a mathematical formula}hi has two segments joining at {a mathematical formula}wi: the first spans {a mathematical formula}[0,wi] and has slope {a mathematical formula}−ri, while the second spans {a mathematical formula}[wi,5] and has slope {a mathematical formula}qi. Starting from {a mathematical formula}b⁎=9, we can define the segment of H for which {a mathematical formula}b⁎ is the left breakpoint using the second segment of each {a mathematical formula}hi with minimal {a mathematical formula}qi. There are two of them (namely for {a mathematical formula}i=1 and {a mathematical formula}i=2) with respective lengths 3 and 2, both with slope 2. This defines a segment of length 5 and slope 2 spanning the interval {a mathematical formula}[9,14]. The next segment has slope 3 and is constructed from the second segments of {a mathematical formula}hi for {a mathematical formula}i=3 and {a mathematical formula}i=4. With a length of 6, it spans the interval {a mathematical formula}[14,20]. The same reasoning for values smaller than 9 leads to two more segments: one spans {a mathematical formula}[0,2] with a slope of −2, and the other one spans {a mathematical formula}[2,9] with a slope of −1. Fig. 3 shows how H is formed of the segments of the {a mathematical formula}hi.  □
      </paragraph>
      <paragraph>
       As can be seen in the previous example, we do not compute an analytical definition of H but only its minimum and its segments. As will be made clear in Section 6, we are never interested in the value of {a mathematical formula}H(b) for an arbitrary value b but only for {a mathematical formula}b⁎ and for incremental modifications of b that can be computed using the slopes of the segments.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Computing the feasibility bound and a support
      </section-title>
      <paragraph>
       We now show that problem (6) can be solved in a greedy way.
      </paragraph>
      <paragraph label="Theorem 8">
       Problem(6)can be solved greedily if each{a mathematical formula}hiis discretely convex.
      </paragraph>
      <paragraph label="Proof">
       If each function {a mathematical formula}hi is discretely convex, then the function H is also discretely convex (by Theorem 4) and can be constructed from the {a mathematical formula}hi (by Lemma 5, Lemma 7). Finding the minimum of a discretely convex function under some bound constraints can be done greedily, as a local minimum of a discretely convex function is also a global minimum (see, e.g., Theorem 2.2 in [12]).  □
      </paragraph>
      <paragraph>
       Given the function H, problem (6) can be solved by first finding a value b minimising H (i.e., {a mathematical formula}b⁎), and then greedily increasing or decreasing b if {a mathematical formula}b⁎ is not in {a mathematical formula}[g_,g‾]. In addition, computing a support {a mathematical formula}sb is useful for the filtering (to be discussed in Section 5).
      </paragraph>
      <paragraph>
       Thanks to Lemma 6, this can be achieved by Algorithm 1.{sup:3} From now on, we write s to refer to {a mathematical formula}sb. An assignment s that minimises the value of H without considering the bounds for b is initially constructed (lines 2–4). If b is in {a mathematical formula}[g_,g‾], then the initial assignment is the final one. Otherwise the assignment is iteratively modified in order to satisfy the bounds of b. We assume {a mathematical formula}b&lt;g_ happens in line 5. Then some {a mathematical formula}si must be increased until b is equal to {a mathematical formula}g_. This is done in two steps. In lines 6–10, the segment of H where {a mathematical formula}g_ lies is found. Its slope is stored in {a mathematical formula}Δmax, and the distance between {a mathematical formula}bp−(H,g_) and {a mathematical formula}g_ is stored in {a mathematical formula}slack. Those two values allow us to modify each {a mathematical formula}si separately (lines 11–17). For each i, first {a mathematical formula}si is moved from breakpoint to breakpoint of {a mathematical formula}hi while the slope of the segment is smaller than {a mathematical formula}Δmax. Next, if the slope of the segment on the right of {a mathematical formula}si is equal to {a mathematical formula}Δmax, then {a mathematical formula}si is moved further on this segment, without exceeding the remaining slack (line 15). Lines 18–30 show the symmetrical case when {a mathematical formula}b&gt;g‾: the left deltas and left breakpoints are used, and {a mathematical formula}slack takes on negative values.
      </paragraph>
      <paragraph>
       The algorithm returns the support s (line 31), or “null” if the constraint is unsatisfiable (lines 8 and 21), which triggers propagator failure and happens if there exists no value in the domains of the {a mathematical formula}hi such that {a mathematical formula}b∈[g_,g‾].
      </paragraph>
      <paragraph>
       We now prove that Algorithm 1 is correct:
      </paragraph>
      <paragraph label="Proof">
       If the{a mathematical formula}hiare discretely convex and H is defined as in equation(5), thenAlgorithm 1returns an optimal solution to problem(4), and hence to problem(6), if one exists, and “null” otherwise.If the {a mathematical formula}hi are discretely convex, then H is also discretely convex (by Theorem 4) and lines 2–4 store its minimum in variable b (using Lemma 5). If {a mathematical formula}g_≤b≤g‾, then b is feasible and we are done. Otherwise, assume {a mathematical formula}b&lt;g_ (the other case is symmetrical), then by Theorem 2.2 in [12], the optimal solution is at {a mathematical formula}b=g_. Now, we need to find {a mathematical formula}sg_. We do this in two steps. Lines 6–7 locate the segment of H where {a mathematical formula}g_ lies. If such a segment does not exist, then {a mathematical formula}g_ is not in the domain of H and “null” is returned in line 8. Otherwise, lines 9 and 10 compute the slope {a mathematical formula}Δmax of that segment, and the distance {a mathematical formula}slack between {a mathematical formula}bp−(H,g_) and {a mathematical formula}g_. Lines 11–17 modify the value of each {a mathematical formula}wi to reach {a mathematical formula}g_: lines 12–13 position each {a mathematical formula}si at the right breakpoint of the correct segment as defined by Lemma 6, and lines 14–17 ensure that {a mathematical formula}∑i∈[1,n]si is equal to {a mathematical formula}g_.  □
      </paragraph>
      <paragraph label="Example 9">
       We now show an execution of Algorithm 1 on the problem of our running example. Important values at some steps of Algorithm 1 are given in Table 3. We have already shown in Example 7 that {a mathematical formula}b⁎=9, so we have {a mathematical formula}b=9 at line 4. As {a mathematical formula}b&lt;g_=10 on line 5, the algorithm enters the conditional branch starting at line 6 with {a mathematical formula}b=9 and {a mathematical formula}s=〈2,3,2,2〉. We have that {a mathematical formula}Δ+(H,9)=2 and {a mathematical formula}bp+(H,9)=14. As {a mathematical formula}14≮g_=10, line 7 is never executed. Lines 9 and 10 set {a mathematical formula}Δmax=2 and {a mathematical formula}slack=1. The loop of lines 11–17 is executed for each {a mathematical formula}i∈[1,4]. Here, line 13 is never executed. For {a mathematical formula}i=1, the condition of line 14 is true and lines 15–17 are executed: they set {a mathematical formula}s′=min⁡{5,2+1}=3, {a mathematical formula}slack=1−3+2=0, and {a mathematical formula}si=3. As the slack is now equal to zero, no other value will be modified for {a mathematical formula}i∈[2,4]. The final support is {a mathematical formula}s=〈3,3,2,2〉.Note that we iterate in line 11 over the indices in increasing order. If we iterated in decreasing order, then we would obtain {a mathematical formula}s=〈2,4,2,2〉. The two assignments are both correct supports for {a mathematical formula}b=10 and {a mathematical formula}H(b)=2. The conjunction of constraints in this example is feasible as the optimal value, namely 2, is at most the upper bound {a mathematical formula}f‾=5.  □
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Domain filtering
     </section-title>
     <paragraph>
      To filter the domain of a variable, we extend the reasoning presented in Section 4.1. Indeed, variable {a mathematical formula}xj can take a value {a mathematical formula}u∈Dxj if and only if the cost of an optimal solution to the following problem is smaller than or equal to {a mathematical formula}f‾:{a mathematical formula} Problem (8) resembles problem (3) but {a mathematical formula}xj is fixed to u. Hence we can use the same reformulation as in Section 4.1. We introduce the following new function:{a mathematical formula} That is, {a mathematical formula}Hj(b) is similar to {a mathematical formula}H(b) in (5) but it only uses the functions {a mathematical formula}hi for i different from j. The optimal cost of problem (8) is the optimal cost of the following new problem:{a mathematical formula} where value u is given and z is the only variable. The result of the following lemma can be used to compute {a mathematical formula}Hj.
     </paragraph>
     <paragraph label="Proof">
      The function{a mathematical formula}Hjis discretely convex if all{a mathematical formula}hiare discretely convex. The value{a mathematical formula}bj⁎that minimises{a mathematical formula}Hjis equal to the value{a mathematical formula}b⁎that minimises H minus the value{a mathematical formula}v⁎that minimises{a mathematical formula}hj. The length of each segment of{a mathematical formula}Hjis equal to the length of the linear segment of H of the same slope minus the length of the linear segment of{a mathematical formula}hjof the same slope, if any.As H and {a mathematical formula}Hj are defined identically except for the set of indices they consider, one can apply all results concerning H to {a mathematical formula}Hj. So the first statement is a consequence of Theorem 4, replacing H by {a mathematical formula}Hj. In the same way, applying Lemma 5 to {a mathematical formula}Hj, we get {a mathematical formula}sibj⁎=sib⁎ for all {a mathematical formula}i≠j. Hence {a mathematical formula}bj⁎=b⁎−sib⁎, which proves the second statement. Applying Lemma 7 to {a mathematical formula}Hj gives that the length of each segment of {a mathematical formula}Hj is equal to the sum of the lengths of the segments of the same slope of the {a mathematical formula}hi with {a mathematical formula}i≠j. Hence the only difference between the length of a segment of {a mathematical formula}Hj and the length of the segment of H of the same slope is the length of the segment of {a mathematical formula}hj with the same slope, if it exists.  □
     </paragraph>
     <paragraph label="Example 10">
      Given the functions of Example 3, {a mathematical formula}H1 is characterised as follows. Its minimum is at {a mathematical formula}9−2=7 and it has 4 segments spanning respectively the interval {a mathematical formula}[0,2] with slope −2, the interval {a mathematical formula}[2,7] with slope −1, the interval {a mathematical formula}[7,9] with slope 2, and the interval {a mathematical formula}[9,15] with slope 3. Fig. 4 on page 183 illustrates the function and its use in the forthcoming Example 11.  □
     </paragraph>
     <paragraph>
      Our filtering algorithm is given in Algorithm 2. It iterates over all variables and, for each variable {a mathematical formula}yj, filters in turn for the values larger than {a mathematical formula}sj and for the values smaller than {a mathematical formula}sj. To avoid cluttering the algorithm descriptions with numerous parameters, we consider {a mathematical formula}f,g,h,f‾,g_,g‾,H, and s to be globally available. We show hereafter two ways to use {a mathematical formula}Hj to implement ForwardFilter and BackwardFilter. The first way is applicable in general, provided {a mathematical formula}Hj is discretely convex. The second way makes use of an additional property that {a mathematical formula}fj and {a mathematical formula}gj might have.
     </paragraph>
     <section label="5.1">
      <section-title>
       Filtering in the general case
      </section-title>
      <paragraph>
       As several values u of {a mathematical formula}xj can have the same image v through {a mathematical formula}gj, the set of values in {a mathematical formula}Dxj that are consistent with constraints (1) and (2) can be partitioned as:{a mathematical formula} That is, for each v, we have the set of values u in {a mathematical formula}gj−1(v) such that the optimal cost of problem (9) is at most {a mathematical formula}f‾, hence the set of values that are feasible. The domain of {a mathematical formula}xj can be made domain consistent by filtering the following unary constraint for each value {a mathematical formula}v∈gj(Dxj):{a mathematical formula} The function {a mathematical formula}Hj being discretely convex, one can compute {a mathematical formula}ming_≤z+v≤g‾⁡Hj(z), which is independent of any particular u, incrementally from a value v to {a mathematical formula}v+1. In addition, if v is equal to {a mathematical formula}sj, which is the value of {a mathematical formula}yj in the support s computed in Section 4.4, then{a mathematical formula} This leads to Algorithm 3,{sup:4} which is used to filter the domain of {a mathematical formula}xj for values larger than {a mathematical formula}sj. This algorithm traverses the functions {a mathematical formula}hj and {a mathematical formula}Hj. The only complication is that in some cases (captured by the Boolean variable {a mathematical formula}decb defined in lines 6 and 12) reaching an optimal solution to {a mathematical formula}ming_≤z+v≤g‾⁡Hj(z) involves decrementing b, which is the current value of z (line 10). Domain filtering according to constraint (10) takes place in lines 5 and 11. We assume that the Filter procedure to filter the domain of a variable for a unary constraint is provided by the user. The semantics of Filter{a mathematical formula}(ϕ(x)) for some unary predicate ϕ is that it removes from the domain of x all values u such that {a mathematical formula}ϕ(u) does not hold. The algorithm ends when the optimal cost to problem (9) for {a mathematical formula}v+1 is larger than {a mathematical formula}f‾ (line 8), at which point values of {a mathematical formula}xj for which {a mathematical formula}gj(xj)&gt;v are filtered (line 14). The description of the procedure ComputeHj on line 2 will be given in Section 6.
      </paragraph>
      <paragraph>
       Algorithm 4 presents the complementary algorithm for values smaller than {a mathematical formula}sj. In that case, v is iteratively decreased while b is increased. Hence the Boolean {a mathematical formula}decb is replaced by {a mathematical formula}incb defined as {a mathematical formula}b+v≤g_∨Δ+(Hj,b)&lt;0. Note that line 5 is redundant with line 5 in Algorithm 3 but has been left for symmetry.
      </paragraph>
      <paragraph label="Proof">
       If each{a mathematical formula}hiis discretely convex, H is defined as in equation(5),sis the result ofAlgorithm 1, and eachFiltercall achieves domain consistency on the unary constraint given as argument, thenAlgorithm 3, Algorithm 4achieve domain consistency on{a mathematical formula}xj.First, we show that the value b used in each Filter call of lines 5 and 11 is{a mathematical formula} This is verified for the call in line 5 by equation (11) and the computed values of b and v. From now on, we only consider the case of the values v larger than {a mathematical formula}wj, i.e., Algorithm 3, the other case being symmetrical. Each iteration of the loop of lines 8–13 increments v by 1. If {a mathematical formula}b+v=g‾, then b must be decreased by 1 in order to satisfy the condition in expression (12) when v is incremented. If {a mathematical formula}Δ−(Hj,b)&lt;0, then {a mathematical formula}Hj(b−1)&lt;Hj(b). The value {a mathematical formula}b−1 is not feasible for v (as b is optimal, meaning that {a mathematical formula}b+v=g_) but is feasible for {a mathematical formula}v+1, so b must be decremented in that case. In all other cases, b stays constant. Hence, in each case, the value of b at line 11 is equal to the value of expression (12).Second, we show that the value v in line 14 is the largest feasible value in the domain of {a mathematical formula}yj. By the argument above, b is the optimal value at each iteration of the loop. Hence the test of line 8 evaluates to false if and only if {a mathematical formula}v+1 is not feasible. As {a mathematical formula}Hj is discretely convex, there is no feasible value larger than v.  □
      </paragraph>
      <paragraph>
       We note that domain consistency is usually easy to achieve for any unary constraint appearing in a Filter call.
      </paragraph>
      <paragraph>
       In Section 7.1, we will characterise the consistency level achieved by Algorithm 3, Algorithm 4 when the {a mathematical formula}hi are not discretely convex.
      </paragraph>
      <paragraph label="Example 11">
       The execution of Algorithm 3 on variable {a mathematical formula}x1 in the problem of Example 3 is as follows. Table 4 gives the values of the variables appearing in the algorithm at different moments and Fig. 4 shows how the functions {a mathematical formula}hj and {a mathematical formula}Hj are traversed. We start from the support {a mathematical formula}s=〈2,4,2,2〉 and have {a mathematical formula}f‾=5. The result of line 2, namely {a mathematical formula}Hj, was given in Example 10. Lines 3 and 4 set {a mathematical formula}b=8 and {a mathematical formula}v=2. The Filter calls at lines 5 and 11 amount, after instantiating and simplifying the formula, to “if {a mathematical formula}max⁡{2−v,2v−4}+Hj(b)&gt;5, then remove v from {a mathematical formula}Dx1”. In line 5, we have {a mathematical formula}Hj(b)=2, hence {a mathematical formula}v=2 stays in the domain. Line 6 sets {a mathematical formula}decb to true. As {a mathematical formula}g_=g‾ in this example, {a mathematical formula}decb is always true and b will be decremented at each iteration. The tested value in line 8 is equal to {a mathematical formula}0+2=2, which is smaller than 5, hence the loop is entered. Now, we have {a mathematical formula}v=3, {a mathematical formula}b=7, and {a mathematical formula}Hj(b)=0, and nothing is filtered by line 11. To start the next iteration, we have that the tested value in line 8 is {a mathematical formula}1+4=5 and the body of the loop is executed again: {a mathematical formula}v=4, {a mathematical formula}b=6, {a mathematical formula}Hj(b)=1, and nothing is filtered. Finally, the tested value in line 8 becomes {a mathematical formula}2+6=8, which is larger than 5, and the loop ends. The execution of line 14 enforces {a mathematical formula}x1≤v=4, which removes 5 from {a mathematical formula}Dx1. The domain of {a mathematical formula}x1 after the execution of Algorithm 3 is thus {a mathematical formula}[0,4].The execution of Algorithm 4 is similar and illustrated with the dotted arrows in Fig. 4. The loop ends when {a mathematical formula}v=1 and the execution of line 14 enforces {a mathematical formula}x1≥v=1, which removes 0 from {a mathematical formula}Dx1. The domain of {a mathematical formula}x1 after the execution of Algorithm 4 is thus {a mathematical formula}[1,4].  □
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Filtering in a special case
      </section-title>
      <paragraph>
       We now present a special case that allows us to avoid useless computation, namely a form of monotonicity. Let us define {a mathematical formula}kj(v)=max⁡fj(gj−1(v)), that is {a mathematical formula}kj(v) is the largest value {a mathematical formula}fj(u) for u such that {a mathematical formula}gj(u)=v. The function {a mathematical formula}kj is similar to {a mathematical formula}hj but the ‘max’ operator replaces the ‘min’ one.
      </paragraph>
      <paragraph>
       If {a mathematical formula}hj(v)≥kj(v−1) for any value v larger than {a mathematical formula}v⁎=argminu∈gj(Dxj)hj(u) and {a mathematical formula}hj(v)≥kj(v+1) for any v smaller than {a mathematical formula}v⁎, then there exists a value {a mathematical formula}vmax such that for all values {a mathematical formula}v∈gj(Dxj) smaller than {a mathematical formula}vmax (but larger than or equal to {a mathematical formula}sj) we have that all values {a mathematical formula}u∈gj−1(v) are feasible, and for all v larger than {a mathematical formula}vmax, there is no feasible u. We then need not consider all values but only find {a mathematical formula}vmax and filter according to the two constraints {a mathematical formula}gj(xj)≤vmax and {a mathematical formula}gj(xj)=vmax⇒fj(xj)≤f‾−ming_≤z+vmax≤g‾⁡Hj(z). A similar argument holds for a similarly defined {a mathematical formula}vmin.
      </paragraph>
      <paragraph>
       Finding {a mathematical formula}vmax amounts to computing the largest value v such that {a mathematical formula}hj(v)+ming_≤z+v≤g‾⁡Hj(z)≤f‾. As {a mathematical formula}hj and {a mathematical formula}Hj are both convex, this problem can be solved by incrementally increasing v until the bound is reached. Algorithm 5 presents the steps to find {a mathematical formula}vmax.{sup:5} This algorithm is very similar to Algorithm 3, but it does not need to iterate over all the values v, but only over the ones that are at a breakpoint of {a mathematical formula}hj or {a mathematical formula}Hj. The increment is stored in ℓ (lines 6, 12, and 14). For conciseness, we use if-then-else expressions inside the expressions giving the value of ℓ in lines 6, 12, and 14. The correctness of Algorithm 5 stems from the correctness of Algorithm 3 and the fact that ℓ is the largest increment such that the values of {a mathematical formula}Δ+(hj,v), {a mathematical formula}Δ−(Hj,b), and {a mathematical formula}decb are constant.
      </paragraph>
      <paragraph>
       An example of the special case is when {a mathematical formula}gj is the identity function. Then {a mathematical formula}gj is injective. Hence {a mathematical formula}hj=kj and, by convexity, {a mathematical formula}hj is non-decreasing to the right of {a mathematical formula}v⁎ and non-increasing to the left of {a mathematical formula}v⁎.
      </paragraph>
      <paragraph label="Example 12">
       The filtering of Example 11 can be rerun with Algorithm 5 since the functions {a mathematical formula}gj are the identity function. Table 5 gives the values of the variables appearing in the algorithm at different moments. Initially, we have {a mathematical formula}v=2, {a mathematical formula}b=8, and {a mathematical formula}ℓ=8−7=1, as {a mathematical formula}Hj has a breakpoint at {a mathematical formula}b=7. After one iteration, we have {a mathematical formula}v=3, {a mathematical formula}b=7, and {a mathematical formula}ℓ=5−3=2, as {a mathematical formula}hj has a breakpoint at 5. At this point, the tested value in line 8 is {a mathematical formula}2+6=8, and the loop ends. Lines 14 and 15 set {a mathematical formula}ℓ=(5−0−2)/(2+1)=1 and {a mathematical formula}v=4. As in Example 11, line 16 removes all values larger than 4 (i.e., 5) from {a mathematical formula}Dx1. Line 17 does not remove anything here. Similarly, the execution of Algorithm 6 stops after one iteration and removes value 0 from the domain of {a mathematical formula}x1.  □
      </paragraph>
      <paragraph>
       Algorithm 6 presents the complementary algorithm to find {a mathematical formula}vmin. Again, it is very similar to Algorithm 4 but, like Algorithm 5, it decreases the value of v in each step by ℓ, which is potentially larger than 1.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      A parametric propagator and its complexity
     </section-title>
     <paragraph>
      Our propagator is generic in the sense that it works correctly for any functions {a mathematical formula}fi and {a mathematical formula}gi that respect the condition of Theorem 8. However, we call it a parametric propagator, because rather than resorting to a fully generic implementation, we use hook functions and procedures that need to be provided. This often allows us to get a lower time complexity. The parameters for each instantiation are shown in Table 6: they are used in Algorithms 1 to 6. We now study the time and space complexity of our propagator, after describing some implementation strategies.
     </paragraph>
     <section label="6.1">
      Constructing H
      <paragraph>
       We represent the H function as two linked lists of segments, plus two integers for the value {a mathematical formula}b⁎ minimising {a mathematical formula}H(b⁎) and for {a mathematical formula}H(b⁎) itself. For each segment, its slope and length are stored. One linked list chains all the segments to the right of {a mathematical formula}b⁎ by increasing order of the slope value and is terminated by a dummy segment with slope +∞. The other linked list chains the segments to the left of {a mathematical formula}b⁎ by decreasing order of the slope value and is terminated by a dummy segment with slope −∞.
      </paragraph>
      <paragraph>
       Constructing the linked lists of H, i.e., line 2 in Algorithm 2, can be implemented in various ways.
      </paragraph>
      <paragraph>
       A first way is to traverse each function {a mathematical formula}hi in turn and to build H incrementally by traversing the linked lists in parallel. This takes {a mathematical formula}O(n⋅(s(h)⋅p+s(H))) time, where {a mathematical formula}s(h) is the maximum number of segments among the {a mathematical formula}hi functions, {a mathematical formula}s(H) is the number of segments of H, and p is the highest complexity of the parametric functions in Table 6.
      </paragraph>
      <paragraph>
       A second way is to collect all the segments from all the functions in a list, to sort this list, and to construct H by traversing the list. This takes {a mathematical formula}O(n⋅s(h)⋅(p+log⁡(n⋅s(h)))) time and is asymptotically better than the first way when {a mathematical formula}s(H)&gt;s(h)⋅log⁡(n⋅s(h)).
      </paragraph>
      <paragraph>
       Although it might be interesting to construct H lazily because some parts of H might never be used, preliminary experiments have shown that the construction of H takes only a very small portion of the running time so that we did not explore this direction further.
      </paragraph>
     </section>
     <section label="6.2">
      Computing {a mathematical formula}H(b), {a mathematical formula}hj(v), and {a mathematical formula}Hj(b)
      <paragraph>
       The value of {a mathematical formula}H(b) is never queried for arbitrary values of b, but only for a value {a mathematical formula}b⁎ minimising {a mathematical formula}H(b⁎) and for incrementally modified values of b, so that {a mathematical formula}H(b) can also be computed incrementally.
      </paragraph>
      <paragraph>
       The computation of {a mathematical formula}H(b), {a mathematical formula}Δ+(H,b), {a mathematical formula}Δ−(H,b), {a mathematical formula}bp+(H,b), and {a mathematical formula}bp−(H,b) can be performed as follows in constant time for all values of b used in the algorithms. Note first that in any algorithm the value of b is either only increased or only decreased, starting from {a mathematical formula}b⁎. We only discuss here the case of increasing b, the decreasing case being symmetrical. At any point in the algorithms, instead of maintaining only the value b, we also maintain a pointer to the segment s of H in which b and {a mathematical formula}b+1 lie (there is always a unique such segment), the distance ℓ between b and the right breakpoint of s, and the value of {a mathematical formula}H(b).
      </paragraph>
      <paragraph>
       Algorithm 7 shows how those quantities can be maintained upon incrementing b. If b is incremented by k with {a mathematical formula}k≤ℓ (which is ensured in all algorithms), then {a mathematical formula}H(b) is incremented by {a mathematical formula}k⋅Δ(s) and ℓ is decreased by k. If ℓ becomes equal to 0, then s is replaced by its successor in the linked list and ℓ is set to the length of the new segment. The expression {a mathematical formula}Δ+(H,b) appearing in Algorithm 1 is equal to {a mathematical formula}Δ(s) and {a mathematical formula}bp+(H,b) can be computed as {a mathematical formula}b+ℓ.
      </paragraph>
      <paragraph>
       Similarly, the value of {a mathematical formula}hj(v) is only queried for {a mathematical formula}sib⁎ and incrementally modified values of v. This is reflected by the absence of {a mathematical formula}hj(v) from the parameters in Table 6. As shown in Algorithm 8, the bookkeeping associated with {a mathematical formula}hj is simpler than the one of H: it suffices to maintain {a mathematical formula}hj(v) using the parameter function {a mathematical formula}Δ+(hj,v) whenever v is modified.
      </paragraph>
      <paragraph>
       The approach for querying the value of {a mathematical formula}Hj(b) is the same as for {a mathematical formula}H(b): the value of b is initialised to a value for which {a mathematical formula}Hj(b) is known, and then either only increased or only decreased. Hence {a mathematical formula}Hj(b) and the other related quantities can be maintained incrementally as is done for H. Using this fact and Lemma 10, we actually do not need to compute {a mathematical formula}Hj in line 2 of Algorithms 3 to 6. Instead, we only maintain the segment s of {a mathematical formula}Hj on which b and {a mathematical formula}b+1 lie (in case of increasing b). As shown in Algorithm 9, to compute the length ℓ and slope d of s, we also maintain a pointer to the segment {a mathematical formula}s′ in H from which the segment of {a mathematical formula}Hj is built and a value {a mathematical formula}v′ such that {a mathematical formula}−Δ−(hj,v′)≤Δ(s)&lt;Δ+(hj,v′). When we need to access the next segment of {a mathematical formula}Hj (because the value ℓ reached 0), we can construct it from the successor of {a mathematical formula}s′ in H and the segment on the right of {a mathematical formula}v′ in {a mathematical formula}hj. As a segment in H might be built from a single segment of only {a mathematical formula}hj, Algorithm 9 must loop while the remaining length ℓ is equal to zero.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Complexity analysis
      </section-title>
      <paragraph>
       Feasibility test  Algorithm 1 computes a support in {a mathematical formula}O(s(H)+n⋅s(h)) time, that is {a mathematical formula}O(n⋅s(h)) time, as {a mathematical formula}s(H)≤n⋅s(h). This is dominated by the prior construction of H discussed in Section 6.1.
      </paragraph>
      <paragraph>
       Filtering  We implement Algorithm 3, Algorithm 4 to run in {a mathematical formula}O(r(h)⋅(p+c)) time, where {a mathematical formula}r(h)=|gj(Dxj)|, p is the highest complexity of the parametric functions in Table 6, and c is the highest complexity of the Filter procedures in Table 6. The segments of {a mathematical formula}Hj are computed on the fly from {a mathematical formula}hj and H, as explained in Section 6.2. The sum in line 3 of Algorithm 3, Algorithm 4 is actually provided by our representation of H, so it need not be recomputed each time. Algorithm 5, Algorithm 6 take {a mathematical formula}O(s(h)⋅p+s(H)+c) time.
      </paragraph>
      <paragraph>
       The whole propagator  The time complexity of our propagator, given in Algorithm 2, is obtained by multiplying the filtering complexity by n (the number of variables) and adding the complexity of computing H. Table 7 summarises this for the different versions of the propagator. Note that {a mathematical formula}s(h)≤r(h)≤|Dx| and {a mathematical formula}s(H)≤n⋅s(h). In the worst case, one can assume that {a mathematical formula}p=c=O(d), where d is the size of the largest domain, leading to the complexity announced in Section 1 for the general case and constructing H by traversal: {a mathematical formula}O(n⋅d2+n2⋅d). However, we show in Table 1 on page 171 and in Section 8 that the time complexity for specific instantiations of the propagator is much lower.
      </paragraph>
      <paragraph>
       The space complexity of our propagator is {a mathematical formula}O(n+s(H)), as we need to store a constant amount of information for each variable (namely the value {a mathematical formula}si), as well as the whole function H (which amounts to a constant amount for each of its {a mathematical formula}s(H) segments). The functions {a mathematical formula}hi and {a mathematical formula}Hj are not stored explicitly.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Instantiating the parametric propagator
     </section-title>
     <paragraph>
      We now present a number of relaxations and extensions of the problem as covered in the previous sections. At the same time, we discuss the consistency levels that can be achieved by our propagator. Those results are used in Section 8 when instantiating the parametric propagator for particular pairs of constraints.
     </paragraph>
     <section label="7.1">
      <section-title>
       Relaxations
      </section-title>
      <paragraph>
       The required discrete convexity of the {a mathematical formula}hi functions puts a strong restriction on the shape of the {a mathematical formula}gi. Recall that {a mathematical formula}gi(Dxi) must be an interval by the first condition in Definition 1. As the discrete convexity must be respected for all{a mathematical formula}Dxi that arise during the search, the only instantiations of {a mathematical formula}gi satisfying the first condition of Definition 1 are those whose image contains only two values, which must be one unit apart. We call these characteristic functions. In such a case, the second condition of Definition 1 is always respected and the {a mathematical formula}fi can be any (integer) functions. This is for instance the case of the constraint pairs Linear≤ and Among, and Linear≤ and Maximum shown in Table 2 on page 175.
      </paragraph>
      <paragraph>
       If {a mathematical formula}Dxi is restricted to be an interval, then the class of {a mathematical formula}gi functions satisfying the first condition of Definition 1 is more general, namely all functions where{a mathematical formula} If there are holes in a domain {a mathematical formula}Dxi, then {a mathematical formula}Dxi can be relaxed to the smallest enclosing interval, but some propagation may be lost: this compromise is often acceptable for global constraints. In this case, we do not achieve domain consistency, but bounds{a mathematical formula}(Z) consistency. Among others, the identity function respects equation (13). If some {a mathematical formula}gi is the identity function, then {a mathematical formula}fi must be discretely convex, because {a mathematical formula}hi=fi.
      </paragraph>
      <paragraph>
       In general, if {a mathematical formula}hi is not discretely convex, then one can replace it by a discretely convex function {a mathematical formula}hi′:S→T that underapproximates{a mathematical formula}hi, i.e., such that {a mathematical formula}gi(Dxi)⊆S and {a mathematical formula}hi′(v)≤hi(v) for all {a mathematical formula}v∈gi(Dxi). Using {a mathematical formula}hi′, the propagator remains correct but might miss propagation.
      </paragraph>
      <paragraph>
       Even when {a mathematical formula}hi is discretely convex, it can be beneficial to replace it by an underapproximation in order to reduce the time complexity of the algorithms, at the sacrifice of a potentially weaker filtering. For example, a generally applicable relaxation is to replace all the segments of a function {a mathematical formula}hi on the right of some {a mathematical formula}sib by a single segment with slope {a mathematical formula}Δ+(hi,sib), and all segments on the left of {a mathematical formula}sib by a single segment with slope {a mathematical formula}−Δ−(hi,sib). This reduces the term {a mathematical formula}s(h) in the complexity analysis to the constant 2 but may lead to some missed filtering.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Extensions
      </section-title>
      <paragraph>
       If some {a mathematical formula}hi is a linear function, then {a mathematical formula}−hi is also discretely convex. Hence, one can put a lower bound {a mathematical formula}f_ on {a mathematical formula}∑i∈[1,n]fi(xi) and run the propagator twice, first with constraint (1) being {a mathematical formula}∑i∈[1,n]fi(xi)≤f‾, and then with constraint (1) being {a mathematical formula}−∑i∈[1,n]fi(xi)≤−f_.
      </paragraph>
      <paragraph>
       Our propagator can be extended to handle variables as the upper and lower bounds of the constraints. In such a case, the largest values in the domains of {a mathematical formula}f‾ and {a mathematical formula}g‾, as well as the smallest values in the domains of {a mathematical formula}f_ and {a mathematical formula}g_ are used in the propagator. In addition, the other bound of each variable can be constrained using the H function without changing the time complexity. Only bounds{a mathematical formula}(Z) consistency can be achieved on those variables.
      </paragraph>
      <paragraph>
       Our propagator can also be adapted to work with the {a mathematical formula}fi being functions from integers to reals. As long as the {a mathematical formula}gi are defined from integers to integers, the domains of the intermediate variables {a mathematical formula}yi and z stay subsets of the integers. However, care must be taken when implementing operations on reals using floating point numbers.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Example instantiations
     </section-title>
     <paragraph>
      We now show that many existing (pairs of) constraints fit our parametric constraint, optionally relaxed or extended as in Section 7. Table 2 on page 175 presents several instantiations of the {a mathematical formula}fi and {a mathematical formula}gi, together with the derived {a mathematical formula}hi. We discuss below some of these constraints and the time complexity of the parametric propagator in those cases, also summarised in Table 1 on page 171. The instantiated complexities are derived from the parametric complexities in Table 7 by replacing {a mathematical formula}s(h), {a mathematical formula}s(H), {a mathematical formula}r(h), p, and c by suitable values derived from the {a mathematical formula}hi.
     </paragraph>
     <paragraph>
      If {a mathematical formula}gi(u)=0 for all i, then the second constraint vanishes and we can use our propagator for a single Sum≤ constraint. In such a case, our parametric propagator achieves domain consistency in {a mathematical formula}O(n⋅(p+c)) time. For the particular case of a linear inequality (Linear≤), our parametric propagator runs in {a mathematical formula}O(n) time. Although this complexity matches the theoretical complexity of a dedicated propagator, our propagator is too general for this simple case and does not use any practical improvement such as the ones presented in [10].
     </paragraph>
     <paragraph>
      Similarly, if {a mathematical formula}fi(u)=0 for all i, then the first constraint vanishes and we can use our propagator for a single Sum= constraint, with {a mathematical formula}g_=g‾, achieving bounds{a mathematical formula}(R) consistency in {a mathematical formula}O(n⋅d) time. Again, for Linear=, we match the theoretical {a mathematical formula}O(n) complexity of dedicated propagators but without any practical improvement such as the ones presented in [10].
     </paragraph>
     <paragraph>
      The case {a mathematical formula}gi(u)=u for all i covers many interesting constraints already presented in the literature. In particular, it covers the bounds{a mathematical formula}(Z)-consistent propagators for the statistical constraints Deviation and Spread with a fixed rational average. Interestingly, it can be generalised to any {a mathematical formula}Lp-norm, with {a mathematical formula}p&gt;0, except {a mathematical formula}L+∞. One can also give a different penalty for deviations over and under the average. This may be very useful as in many practical situations it is less problematic to deviate from the average in one direction than in the other. The time complexity of our propagator is {a mathematical formula}O(n) for Deviation, which matches the best published propagator [3]. For Spread and higher norms, the time complexity of our propagator is {a mathematical formula}O(n⋅d∪), with {a mathematical formula}d∪=|∪i∈[1,n]Dxi|. This is incomparable to the {a mathematical formula}O(n⋅log⁡n) complexity of the best published propagator [2]. Note that our propagator achieves bounds{a mathematical formula}(Z) consistency, which has only been achieved recently and independently in the case of Spread[11].
     </paragraph>
     <paragraph>
      As an example, we show in Table 8 the instantiations of the parameters for Deviation (symmetric parameters are omitted): note that each {a mathematical formula}hi has (up to) three segments, joining at the breakpoints {a mathematical formula}⌊μ⌋ and {a mathematical formula}⌈μ⌉.
     </paragraph>
     <paragraph>
      If {a mathematical formula}gi is a characteristic function, then {a mathematical formula}fi can be any function. A characteristic function may be used to count, as in the case of the Count family of constraints (e.g., Among[14], [15]). But characteristic functions can also be used to represent the Maximum constraint with a fixed maximum m. Indeed, the constraint {a mathematical formula}m=maxi∈[1,n]⁡xi can be decomposed into {a mathematical formula}∀i∈[1,n]:m≥xi∧∑1∈[1,n][xi=m]≥1. Table 2 gives a definition of the functions {a mathematical formula}hi for Linear≤ and Exactly, in which case our propagator achieves domain consistency and runs in {a mathematical formula}O(n⋅(log⁡n+p+c)) time, as does the dedicated propagator presented in [9].
     </paragraph>
     <paragraph>
      Many other pairs of Sum constraints can be instantiated. Note that the functions {a mathematical formula}fi and {a mathematical formula}gi can differ for each i, i.e., one can mix in the same sum terms of different forms (e.g., some linear and some quadratic), as long as each corresponding function {a mathematical formula}hi is discretely convex.
     </paragraph>
     <paragraph label="Example 13">
      We now complete our running example. Applying Algorithm 2 achieves bounds{a mathematical formula}(Z) consistency and yields the following reduced domains: {a mathematical formula}x1∈[1,4], {a mathematical formula}x2∈[2,5], {a mathematical formula}x3∈[1,3], and {a mathematical formula}x4∈[1,3]. In total, 9 values were removed from the domains. In contrast, if the two Sum constraints were filtered separately, then the domains would be {a mathematical formula}x1∈[0,4], {a mathematical formula}x2∈[0,5], {a mathematical formula}x3∈[0,3], and {a mathematical formula}x4∈[0,3], for a total of only 5 removed values.Generalising to any number n of workers, our parametric propagator takes {a mathematical formula}O(n2) time. This is obtained by instantiating the time complexity given in Table 7 for the special case with {a mathematical formula}p=c=O(1) as all parametric functions and procedures can be implemented in constant time, {a mathematical formula}s(h)=2 as each {a mathematical formula}hi function has 2 segments, and {a mathematical formula}s(H)=2⋅n as, in the worst case, the parameters r and s are all different.  □
     </paragraph>
    </section>
    <section label="9">
     <section-title>
      Experimental evaluation
     </section-title>
     <paragraph>
      To show that the parametricity of our propagator is not detrimental not only to asymptotic complexity (as seen in Section 8) but also to efficiency, we make an experiment to compare custom propagators with instantiations of our parametric propagator. We selected the Deviation[3] and Spread[11] constraints as their bounds{a mathematical formula}(Z)-consistent propagators are freely available in the distribution of OscaR [16]. We implemented our propagator and its instantiations on top of OscaR. We performed the comparison on the 100 instances of the balanced academic curriculum problem (BACP) that were introduced in [17],{sup:6} modelled as in the OscaR distribution (we only slightly modified the search heuristic in order to make it deterministic, so that the search trees are the same for comparison purposes).
     </paragraph>
     <paragraph>
      For Deviation, we used the 44 instances that are solved to optimality in more than 1 second (to avoid measurement errors) but less than 12 hours (3 instances timed out). When using our parametric propagator, the time to solve an instance is on average only 7% longer than when using the custom propagator, with a standard deviation of 5%: see also Fig. 5, left. The numbers of nodes in the search tree and calls to the propagator are exactly the same for both propagators due to their common level of consistency and the deterministic search procedure.
     </paragraph>
     <paragraph>
      For Spread, we used the 33 instances that are solved to optimality in more than 1 second but less than 12 hours (2 instances timed out). When using our parametric propagator, the time to solve an instance is on average 28% shorter than when using the custom propagator, with a standard deviation of 10%: see also Fig. 5, right. This improvement is explained by a different algorithmic approach, which is in our favour when the domains of the variables are small, as is the case for the BACP instances. The numbers of nodes in the search tree and calls to the propagator are exactly the same for both propagators.
     </paragraph>
     <paragraph>
      Our Java implementation and the raw data for the results reported here are available at http://www.it.uu.se/research/group/astra/software#convexpairs. A package for replication is at http://recomputation.org[18].
     </paragraph>
    </section>
    <section label="10">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Our approach of first computing a feasibility bound and then incrementally adapting it is not new and has been used in the design of several propagators. Among others, this is the case for the cited propagators covered by our own propagator. However, the novelty of our work is that for the first time we abstract from the details of each constraint to focus on their common properties. This is close in spirit to what has been done with SeqBin[19], [20] for another class of constraints.
     </paragraph>
     <paragraph>
      When the {a mathematical formula}gi are characteristic functions, our conjunction of Sum constraints can also be represented using CostGCC[21]. However, this would require the explicit representation of all variable–value pairs and induce a higher time complexity than our propagator. On the other hand, CostGCC can handle more than one counting constraint in one propagator.
     </paragraph>
     <paragraph>
      To the best of our knowledge, the notion of discrete convexity has not been used before for the design of propagators. However, several researchers have exploited other forms of convexity in constraint programming, namely row convexity [22] and tree convexity [23]. Those forms of convexity are unrelated to the one considered here and the focus of the cited works is on global properties of the constraint network rather than a propagator.
     </paragraph>
     <paragraph>
      Finally, it should be noted that there are domain-consistent propagators for several constraints for which our propagator achieves bounds{a mathematical formula}(Z) consistency or bounds{a mathematical formula}(R) consistency only. In particular, Trick [24] presented a domain-consistent propagator for Linear= and Pesant [25] presented a domain-consistent propagator for {a mathematical formula}Lp-Norm (including Spread and Deviation). Those propagators are based on dynamic programming ideas and have a higher time complexity than our approach.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>