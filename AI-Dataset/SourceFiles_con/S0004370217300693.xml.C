<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    WPM3: An (in)complete algorithm for weighted partial MaxSAT.
   </title>
   <abstract>
    Maximum Satisfiability (MaxSAT) has been used to solve efficiently many combinatorial optimization problems. At recent editions of international MaxSAT Evaluation (MSE), the best performing solvers for real world (industrial) problems were those implementing SAT-based algorithms. These algorithms reformulate the MaxSAT optimization problem into a sequence of SAT decision problems where Pseudo-Boolean (PB) constraints may be introduced. In order to identify the most suitable PB constraints, some algorithms (core-guided) analyze the unsatisfiable cores retrieved from the previous SAT problems in the sequence while refining the lower bound. In this paper, we first conduct a comprehensive study on the complete core-guided algorithms Eva and OLL, that inspired the best performing solvers on industrial instances at MSE-2014. Despite of its apparently different foundations, we show how they are intimately related and identify how to improve them. In this sense, we present our complete core-guided algorithm WPM3. We show how to further exploit the analysis of unsatisfiable cores by being aware of their global structure, i.e., how the cores are interrelated. This is used to encode more efficient PB constraints and enables the algorithm to obtain assignments and refine also the upper bound. Therefore, WPM3 can also work as an incomplete algorithm. At MSE-2015, it showed a competitive performance on industrial instances. It got one out of three gold medals at the complete track and dominated at the incomplete track.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Maximum Satisfiability (MaxSAT) has been used to solve efficiently many combinatorial optimization problems that appear in real world (industrial) domains. Among these domains, we can find software package upgrade [1], debugging of hardware designs [2], [3], bioinformatics [4], [5], fault localization in C code [6], course timetabling [7], planing [8], [9], scheduling [10], routing [11], electronic markets [12], combinatorial auctions [13] and many others [14], [15].
     </paragraph>
     <paragraph>
      MaxSAT is the natural optimization variant of Satisfiability (SAT). The main idea is that sometimes not all restrictions of a problem can be satisfied, and we try to satisfy the maximum number of them. The basic MaxSAT problem can be further generalized to the Weighted Partial MaxSAT (WPMS) problem. In this case, we can divide the restrictions into two groups: the clauses that must be satisfied (hard), and the ones that may or may not be satisfied (soft). We may put different weights to the soft clauses, where the weight is the cost of falsifying the clause. The presence of soft clauses with different weights makes a MaxSAT instance Weighted and the presence of hard clauses makes it Partial. To solve the MaxSAT problem we have to find an assignment that satisfies all hard clauses and minimizes the aggregated cost of falsified soft clauses.
     </paragraph>
     <paragraph>
      Solving exactly (completely) the MaxSAT problem, i.e. finding and certifying an optimal assignment, can be NP-hard from a computational point of view. Anyway, there are many industrial problems slightly beyond the reach of state-of-the-art techniques and often the goal is not finding an optimal assignment but an assignment of a good quality in a reasonable time. For some domains, even a small gain in the quality can lead to important practical consequences. To this end, many incomplete algorithms have been developed for industrial problems. Solvers based on local search algorithms [16], [17] work good for random instances and are competitive on crafted instances. However, the experience achieved from the international MaxSAT Evaluation (MSE) [18], shows us that the best strategy for industrial instances is to improve complete algorithms and modify them so that they become also incomplete (i.e., return assignments when improved) [19], [20]. This is also the case of the WPM3 algorithm that we present in this paper.
     </paragraph>
     <paragraph>
      There are two main types of complete algorithms to solve the MaxSAT problem: (i) branch and bound [21], [22], [23], [24], [25] and (ii) SAT-based [14], [15]. At recent editions of MSE, we have seen that solvers implementing SAT-based algorithms clearly dominate on industrial instances. These algorithms proceed by reformulating the MaxSAT optimization problem into a sequence of SAT decision problems. Each SAT instance of the sequence encodes whether it exists an assignment to the MaxSAT instance with a cost less than or equal to a certain k. Those SAT instances with a k less than the optimal cost are unsatisfiable, and the others satisfiable. Therefore, when SAT-based algorithms find the phase transition point, they find the optimum.
     </paragraph>
     <paragraph>
      Among SAT-based MaxSAT algorithms, there are also two main types: (i) core-guided [26], [27], [28], [29], [30], [31], [32] and (ii) model-guided [33], [34], [35], [36]. The first ones refine (increase) the lower bound and guide the search with unsatisfiable subproblems (cores) obtained from unsatisfiable SAT instances. The second ones refine (decrease) the upper bound and guide the search with satisfying assignments (models) obtained from satisfiable SAT instances. Both have strengths and weaknesses and some hybrid approaches have been proposed [37], [38], [19], [20].
     </paragraph>
     <paragraph>
      SAT-based MaxSAT algorithms use Pseudo-Boolean (PB) constraints to create the SAT instances in the sequence. The PB constraints are used to express the arithmetic and comparison needed to only allow satisfying assignments with a cost less than or equal to the k of the instance. The size, the management and the complexity of these PB constraints are crucial for SAT-based algorithms. With respect to the size, the naive approach uses a unique PB constraint that involves all soft clauses. Fortunately, SAT-based algorithms can use a set of smaller PB constraints that do not necessarily cover all soft clauses. With respect to the management, the default option is that PB constraints are translated to SAT since SAT-based algorithms use internally a SAT solver. However, there are other options, like modeling PB constraints with the Linear Integer Arithmetic theory and using internally an SMT solver [20]. With respect to the complexity, depending on the particular SAT-based algorithm, we may only need to use a simpler form of PB constraints with all coefficients equal to 1 i.e., Cardinality constraints. In case PB constraints are managed through their translation to SAT, the best encoding that preserve arc-consistency has a quadratic size with respect to the size of the constraint [39]. For Cardinality constraints, the size of the best SAT encoding is quasilinear with respect to the size of the constraint [40].
     </paragraph>
     <paragraph>
      PB constraints are defined on auxiliary variables which express whether a particular soft clause is falsified or not. However, some SAT-based algorithms may require more than one auxiliary variable per clause introducing additional complexity. For WPMS instances in particular, the WPM1/WBO algorithm presented in [26], [27] only needed 1-Cardinality constraints (with independent term equal to 1) but it needed multiple auxiliary variables per clause. The WPM2 algorithm presented in [28] needed only a unique auxiliary variable for each clause but it needed general PB constraints.
     </paragraph>
     <paragraph>
      To our best knowledge, the OLL algorithm, presented in [41] originally for ASP (Answer Set Programming), was the first one that only needed a unique auxiliary variable per clause while using Cardinality constraints. Later, this algorithm was applied to MaxSAT and shown to be competitive in [42]. Previous to this last work, the Eva algorithm was presented and also shown to be competitive in [43]. It applies the MaxSAT resolution rule to create the next instance of the sequence. The solvers inspired by Eva and OLL were the best on industrial instances at MSE-2014. Although both algorithms were core-guided, they had apparently different foundations.
     </paragraph>
     <paragraph>
      In this paper, we demonstrate that the transformation applied by Eva at each iteration using the MaxSAT resolution rule corresponds to the incremental construction of a Cardinality constraint. In particular, it finally creates the regular encoding for 1-Cardinality constraints described in [44]. We have analyzed in detail the connections between Eva and OLL and we present a first study showing that they are in fact very similar.
     </paragraph>
     <paragraph>
      With the aim of improving the performance in MaxSAT, we have made a step forward and developed a new algorithm that takes profit of our study. The WPM3 algorithm only needs Cardinality constraints like Eva and OLL, but additionally, it is aware of the global structure of the unsatisfiable cores identified in the problem. Thus, it can exploit this structure to make encodings for the Cardinality constraints that improve the efficiency of the solvers. Moreover, WPM3 is able to exploit subproblem optimization [20] efficiently, which as subproduct provides assignments that can be used to refine the upper bound for the whole problem. In this way, WPM3 can also work as an incomplete algorithm, given limited time and memory. The assignments can be further exploited to extend to MaxSAT a very effective technique used in SAT solvers called phase saving [45].
     </paragraph>
     <paragraph>
      Finally, we have conducted an extensive experimental investigation on industrial instances showing the impact of every technique. With respect to Cardinality constraints, we show that the improvement on the performance is mostly due to the exploitation of the core structure and not only to incrementality as suggested in previous works [32]. We also analyze the results of the MSE-2015. Of the six industrial subcategories, including complete and incomplete track, WPM3 got a total of five medals. At the complete track, it got a gold (PMS) and a bronze (MS) medals. At the incomplete track, it dominated with two gold (PMS, WPMS) and a silver (MS) medals.
     </paragraph>
     <paragraph>
      This paper proceeds as follows. Section 2 introduces some preliminary concepts. Section 3 analyzes how Eva and OLL algorithms are related. Section 4 presents the WPM3 complete MaxSAT algorithm. Section 5 discusses how to encode the Cardinality constraints generated by the algorithm. Section 6 compares WPM3 with Eva and OLL. Section 7 explains how to exploit the assignments and upper bounds generated by the algorithm. Section 8 shows the experimental evaluation. Finally, Section 9 concludes.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph label="Definition 1">
      A literal l is either a Boolean variable x or its negation {a mathematical formula}x‾. A clause c is a disjunction of literals. An empty clause □ is a clause without literals. A SAT formula is a set or conjunction of clauses, i.e. a Boolean formula in Conjunctive Normal Form (CNF). We note the conversion of a Boolean formula β that is not in CNF into a SAT formula ϕ as {a mathematical formula}ϕ=CNF(β). We note the union of two SAT formulas {a mathematical formula}ϕ1 and {a mathematical formula}ϕ2 as {a mathematical formula}ϕ1∪ϕ2, e.g.:{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 2">
      A weighted clause is an ordered pair {a mathematical formula}〈c,w〉, where c is a clause and w is a natural number or infinity (indicating the cost of falsifying c, see Definition 4, Definition 8). If w is infinite the clause is hard, otherwise it is soft.
     </paragraph>
     <paragraph label="Definition 3">
      A Weighted Partial MaxSAT (WPMS) formula is an ordered multiset of weighted clauses:{a mathematical formula} The presence of soft clauses with different weights makes the formula Weighted and the presence of hard clauses makes it Partial. The ordered multiset of weights of the soft clauses in the formula is noted as {a mathematical formula}w(φ). The hard clauses are occasionally noted as {a mathematical formula}〈ϕH,∞〉,ϕH={cs+1,…,cs+h}, when their order can be ignored. The set of variables occurring in the formula is noted as {a mathematical formula}var(φ). We note the concatenation of two WPMS formulas {a mathematical formula}φ1 and {a mathematical formula}φ2 as {a mathematical formula}φ1+φ2 e.g.:{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 4">
      An assignment for a set of Boolean variables X is a function {a mathematical formula}I:X→{0,1}, that can be extended to literals, (weighted) clauses, SAT formulas and WPMS formulas as follows:{a mathematical formula} We will refer to the value returned by an assignment {a mathematical formula}I on a weighted clause or a WPMS formula as the cost of {a mathematical formula}I.
     </paragraph>
     <paragraph label="Definition 5">
      Given the WPMS formulas φ and {a mathematical formula}φ′, we say that φ is MaxSAT reducible to {a mathematical formula}φ′ if, for any assignment {a mathematical formula}I:var(φ)→{0,1}, we have that {a mathematical formula}I(φ)=min⁡{I′(φ′)|I′(x)=I(x)∀x∈var(φ)}.
     </paragraph>
     <paragraph label="Definition 6">
      Given a weighted clause {a mathematical formula}〈c,w〉 and an integer {a mathematical formula}w′≤w, the split rule replaces {a mathematical formula}〈c,w〉 by two weighted clauses as follows:{a mathematical formula} It is trivial to see MaxSat reducibility is guaranteed.
     </paragraph>
     <paragraph label="Definition 7">
      The MaxSAT resolution rule[46] replaces two premises, {a mathematical formula}〈x∨A,1〉 and {a mathematical formula}〈x‾∨B,1〉, by a set of three conclusions, as follows:{a mathematical formula} Where A and B are disjunctions of literals. The first conclusion, {a mathematical formula}〈A∨B,1〉, is the resolvant and the others the compensation clauses. The set of premises is MaxSAT reducible to the set of conclusions.It is easy to see that we can extend the MaxSAT resolution rule to the weighted case as follows:{a mathematical formula} Where A and B are disjunctions of literals and {a mathematical formula}wmin=min⁡(w1,w2).Notice that we can apply the split rule on each of the premises till we get {a mathematical formula}wmin copies of {a mathematical formula}〈x∨A,1〉 and {a mathematical formula}〈x∨B,1〉 as well as the last two conclusions {a mathematical formula}〈x∨A,w1−wmin〉 and {a mathematical formula}〈x∨B,w2−wmin〉. Then, we can apply the MaxSAT resolution rule on the {a mathematical formula}wmin pairs of premises {a mathematical formula}〈x∨A,1〉 and {a mathematical formula}〈x∨B,1〉. This will generate {a mathematical formula}wmin copies of {a mathematical formula}〈A∨B,1〉, {a mathematical formula}〈x∨A∨B‾,1〉 and {a mathematical formula}〈x‾∨A‾∨B,1〉, which can be collapsed into the first three conclusions by applying the inversion of the split rule.The second (third) conclusion is not in CNF if B (A) contains more that one literal. In [47], the version in CNF is provided. If we allow hard clauses in the conclusions, there is a simple trick by reifying {a mathematical formula}B‾ ({a mathematical formula}A‾) into a new fresh variable b. For example, {a mathematical formula}〈x∨A∨B‾,wmin〉 can be replaced by {a mathematical formula}〈x∨A∨b,wmin〉 and {a mathematical formula}〈CNF(b↔B‾),∞〉.These are special cases of the MaxSAT resolution rule:{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 8">
      We say that an assignment {a mathematical formula}I satisfies a clause or a SAT formula if the value returned by {a mathematical formula}I is equal to 1. In the case of SAT formulas, we will refer also to this assignment as a satisfying assignment or solution. Otherwise, if the value returned by {a mathematical formula}I is equal to 0, we say that {a mathematical formula}I falsifies the clause or the SAT formula.
     </paragraph>
     <paragraph label="Definition 9">
      The SAT problem for a SAT formula ϕ is the problem of finding a solution for ϕ. If a solution exists the formula is satisfiable, otherwise it is unsatisfiable.
     </paragraph>
     <paragraph label="Definition 10">
      Given an unsatisfiable SAT formula ϕ, an unsatisfiable core{a mathematical formula}ϕC is a subset of clauses {a mathematical formula}ϕC⊆ϕ that is also unsatisfiable.
     </paragraph>
     <paragraph label="Definition 11">
      A SAT algorithm for the SAT problem, takes as input a SAT formula ϕ and returns an assignment {a mathematical formula}I such that {a mathematical formula}I(ϕ)=1 if the formula is satisfiable. Otherwise, it returns an unsatisfiable core {a mathematical formula}ϕC.Given unlimited resources of time and memory, we say that a SAT algorithm is complete if it terminates for any SAT formula. Otherwise, it is incomplete.
     </paragraph>
     <paragraph label="Definition 12">
      The optimal cost (or optimum) of a WPMS formula φ is {a mathematical formula}cost(φ)=min⁡{I(φ)|I:var(φ)→{0,1}} and an optimal assignment is an assignment {a mathematical formula}I such that {a mathematical formula}I(φ)=cost(φ). We will refer to this assignment as a solution for φ if {a mathematical formula}I(φ)≠∞. Any cost above (below) {a mathematical formula}cost(φ) is called an upper (lower) bound for φ.
     </paragraph>
     <paragraph label="Example 1">
      Given the WPMS formula {a mathematical formula}φ=〈〈x1,5〉,〈x2,3〉,〈x3,3〉,〈x‾1∨x‾2,∞〉,〈x‾1∨x‾3,∞〉,〈x‾2∨x‾3,∞〉〉, we have that {a mathematical formula}cost(φ)=min⁡{6,8,11,∞}=6 and the solution {a mathematical formula}I maps {a mathematical formula}〈x1,x2,x3〉 to {a mathematical formula}〈1,0,0〉.
     </paragraph>
     <paragraph label="Definition 13">
      The Weighted Partial MaxSAT problem for a WPMS formula φ is the problem of finding a solution for φ. If a solution does not exist the formula is unsatisfiable.
     </paragraph>
     <paragraph label="Definition 14">
      A WPMS algorithm for the WPMS problem, takes as input a WPMS formula φ and returns an assignment {a mathematical formula}I, such that, {a mathematical formula}I(φ)≥cost(φ).Given unlimited resources of time and memory, we say that a WPMS algorithm is complete or exact if for any input WPMS formula φ and returned {a mathematical formula}I, {a mathematical formula}I(φ)=cost(φ). Otherwise, we say it is incomplete.
     </paragraph>
     <paragraph label="Definition 15">
      Given a WPMS formula φ such that {a mathematical formula}cost(φ)≥0, an unsatisfiable core{a mathematical formula}φC is a subset of clauses {a mathematical formula}φC⊆φ such that {a mathematical formula}cost(φC)≥0.
     </paragraph>
     <paragraph label="Definition 16">
      An integer linear Pseudo-Boolean (PB) constraint is an inequality of the form {a mathematical formula}w1x1+…+wnxnopk, where {a mathematical formula}op∈{≤,≥,=,&gt;,&lt;}, the independent term k and the coefficients {a mathematical formula}wi are integers, and the variables {a mathematical formula}xi are Boolean. A Cardinality constraint is a PB constraint where the coefficients {a mathematical formula}wi are equal to 1. A 1-Cardinality constraint is a Cardinality constraint where the independent term k is equal to 1. A PB at-most constraint is a PB constraint where op is ≤.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Comparison of Eva and OLL algorithms
     </section-title>
     <paragraph>
      In this section, we compare Eva [43] and OLL [41] MaxSAT algorithms, that inspired the best performing solvers on industrial instances at MSE-2014, {a mathematical formula}eva500a and {a mathematical formula}mscg[42] respectively. To simplify the analysis, we will only consider the non-weighted case. The analysis holds true for the weighted case since both algorithms adapt it to the non-weighted one by applying the idea described in the WPM1/WBO MaxSAT algorithms [26], [27] (i.e. by using the split rule for weighted clauses described in Definition 6). Let us recall that Eva and OLL are core-guided algorithms that iteratively solve a sequence of SAT instances until the first satisfiable instance is found. Indeed they work on a sequence of {a mathematical formula}φk MaxSAT instances such that {a mathematical formula}cost(φk)=cost(φ)−k. If {a mathematical formula}cost(φk)=0, they stop and k is the optimum. To test this, they remove the weights from {a mathematical formula}φk and check if the corresponding SAT instance {a mathematical formula}ϕk is satisfiable.
     </paragraph>
     <paragraph>
      The key point is how to transform {a mathematical formula}φk into {a mathematical formula}φk+1. After analyzing both algorithms, we have observed that the underlying idea comes from the following observation: a MaxSAT formula {a mathematical formula}φn with n soft clauses and {a mathematical formula}cost(φn)≥e, {a mathematical formula}1≤e≤n is MaxSAT reducible (Definition 5) to a formula {a mathematical formula}φn′+〈□,e〉 with {a mathematical formula}n−e soft clauses and e empty clauses:{a mathematical formula}{a mathematical formula} Where {a mathematical formula}cost(φn′)=cost(φn)−cost(〈□,e〉).
     </paragraph>
     <paragraph>
      As we will see, the Eva algorithm indirectly applies this idea by transforming the original instance through a sequence of applications of the MaxSAT resolution rule which guarantees the MaxSAT reducibility property. Notice that the SAT formula {a mathematical formula}{c1′,…, {a mathematical formula}cn−e′}∪ϕH′∪ϕH only accepts solutions such that {a mathematical formula}c‾1+…+c‾n=e. The at-least constraint {a mathematical formula}c‾1+…+c‾n≥e is implicitly encoded in the formula since {a mathematical formula}cost(φn)≥e, and the at-most constraint {a mathematical formula}c‾1+…+c‾n≤e too since we have assumed that {a mathematical formula}φn is MaxSAT reducible to {a mathematical formula}φn′+〈□,e〉 and, in particular, {a mathematical formula}cost(φn′)=cost(φn)−cost(〈□,e〉). This way, if the at-most-constraint is too restrictive (i.e., the lower bound has to be further refined), as we will see, the soft clauses involved will appear in an unsatisfiable core, and can be relaxed again.
     </paragraph>
     <paragraph>
      Back to how to transform {a mathematical formula}φk into {a mathematical formula}φk+1, Eva and OLL identify a {a mathematical formula}φn⊆φk subformula and apply the previous reduction. Then, {a mathematical formula}φk+1=(φk∖φn)∪φn′. Both algorithms use as {a mathematical formula}φn an unsatisfiable core of {a mathematical formula}φk. This guarantees that {a mathematical formula}cost(φn)≥e≥1 and hopefully n is less than the number of soft clauses in {a mathematical formula}φk. We may want n to be as small as possible, this can be achieved by minimizing the unsatisfiable core, and e as large as possible, this can be achieved by solving to optimality {a mathematical formula}φn. However, Eva and OLL only apply the transformations with {a mathematical formula}e=1 at each iteration, i.e., at each iteration they introduce a new 1-Cardinality constraint. It is interesting to see that the incremental addition of 1-Cardinality constraints end up producing k-Cardinality constraints. Therefore, if we could identify a {a mathematical formula}φn whose optimal cost is greater than 1, we could directly write the {a mathematical formula}cost(φn)-Cardinality constraint and skip all the intermediate iterations performed by Eva and OLL.
     </paragraph>
     <paragraph>
      In Section 4, we present the WPM3 algorithm, that identifies {a mathematical formula}φn with e greater than 1 and solve them to optimality. In Section 6, we provide an example of how the three algorithms build a 3-Cardinality constraint. In this section, we focus our attention on the transformation applied by Eva and OLL at each iteration. In the following, we will initially analyze the transformation applied by Eva and then explain how to adapt it such that it becomes very similar to OLL.
     </paragraph>
     <paragraph>
      In the case of Eva, the generation of {a mathematical formula}φk+1 is performed by applying the MaxSAT resolution rule (Definition 7) to {a mathematical formula}φk. The idea is to apply successively this rule to an unsatisfiable core {a mathematical formula}φn obtained from {a mathematical formula}φk and MaxSAT reduce it to {a mathematical formula}φn′+〈□,1〉. Let us see in detail how {a mathematical formula}φn′ is generated. Previous to applying the MaxSAT resolution rule, each soft clause of {a mathematical formula}φn is reified with a fresh auxiliary variable {a mathematical formula}bi. Notice that {a mathematical formula}〈〈ci,1〉〉 is MaxSAT reducible to {a mathematical formula}〈〈b‾i,1〉,〈b‾i↔ci,∞〉〉. The n hard clauses {a mathematical formula}〈b‾i↔ci,∞〉 are directly introduced into {a mathematical formula}φn′ as a part of {a mathematical formula}〈ϕH′,∞〉. The {a mathematical formula}n−1 soft clauses {a mathematical formula}〈〈c1′,1〉,…,〈cn−1′,1〉〉 are obtained by applying the MaxSAT resolution rule on the {a mathematical formula}φb formula which is composed of the n soft clauses {a mathematical formula}〈b‾i,1〉 and the hard clause {a mathematical formula}〈b1∨…∨bn,∞〉 (the core implies that at least one of the soft clauses {a mathematical formula}ci (variables {a mathematical formula}bi) must be false (true)).{a mathematical formula}
     </paragraph>
     <paragraph>
      In the first step, the MaxSAT resolution rule replaces the first soft clause and the hard clause by the resolvant clause {a mathematical formula}〈b2∨…∨bn,1〉 and the compensation clauses {a mathematical formula}〈b1∨…∨bn,∞〉 and {a mathematical formula}〈b‾1∨b2∨…∨bn‾,1〉. Then, it is applied successively to each one of the remaining original soft clauses and the resolvant clause obtained in the previous step, resulting:{a mathematical formula}
     </paragraph>
     <paragraph>
      The above formula is not in CNF. The naive translation into CNF, by reifying the negation of the disjunctions into new fresh variables (see Definition 7), generates a quadratic number of clauses with respect to n. To make it linear, while preserving the MaxSAT reducibility, the new fresh variables are reused recursively in the next reification as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      At the end, the working MaxSAT formula {a mathematical formula}φk is transformed into:{a mathematical formula}
     </paragraph>
     <paragraph>
      As a curiosity, we have observed that the transformation made to {a mathematical formula}φb using the MaxSAT resolution rule and the introduction of auxiliary variables corresponds indeed to the regular encoding of 1-Cardinality constraint in [44], as we can see in Example 2. The authors of Eva describe their transformation with the addition of auxiliary variables as a way of achieving a linear complexity in terms of the encoding size. Indeed, the regular encoding was presented as a linear SAT encoding for 1-Cardinality constraints.
     </paragraph>
     <paragraph label="Example 2">
      Applying successively the MaxSAT resolution rule like Eva to {a mathematical formula}φ=〈〈b‾1,1〉,…,〈b‾4,1〉,〈b1∨…∨b4,∞〉〉, we get the MaxSAT formula {a mathematical formula}φe:{a mathematical formula}1:b‾1∨r‾21:b‾2∨r‾31:b‾3∨r‾41:□∞:r2↔b2∨r3∞:r3↔b3∨r4∞:r4↔b4∞:b1∨b2∨b3∨b4{a mathematical formula}CNF1:b‾1∨r‾21:b‾2∨r‾31:b‾3∨r‾41:□∞:r‾2∨b2∨r3∞:b‾2∨r2∞:r‾3∨r2∞:r‾3∨b3∨r4∞:b‾3∨r3∞:r‾4∨r3∞:r‾4∨b4∞:b‾4∨r4∞:b1∨b2∨b3∨b4{a mathematical formula}(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12⁎)The regular encoding of {a mathematical formula}b1+b2+b3+b4=1 is the SAT formula {a mathematical formula}φr where {a mathematical formula}ri is true iff {a mathematical formula}(bi∨…∨bn) is true:{a mathematical formula}b1↔r‾2b2↔r2∧r‾3b3↔r3∧r‾4b4↔r4r4→r3r3→r2{a mathematical formula}CNFb‾1∨r‾2b1∨r2b‾2∨r2b‾2∨r‾3r‾2∨b2∨r3b‾3∨r3b‾3∨r‾4r‾3∨b3∨r4b‾4∨r4r‾4∨b4r‾4∨r3r‾3∨r2{a mathematical formula}(1)(12)(5)(2)(4)(8)(3)(7)(11)(10)(9)(6)Clauses 1–11 are exactly the same for {a mathematical formula}φe and {a mathematical formula}φr, and correspond to {a mathematical formula}b1+b2+b3+b4≤1. Since {a mathematical formula}r2≡(b2∨b3∨b4), from clause 12, we can get clause {a mathematical formula}12⁎, that corresponds to {a mathematical formula}b1+b2+b3+b4≥1.
     </paragraph>
     <paragraph>
      Another interesting observation comes from the fact that the regular encoding of a 1-Cardinality constraint is equivalent to the Sequential counter encoding [48] for k-Cardinality constraints when {a mathematical formula}k=1. Then, if we get a core {a mathematical formula}φn with {a mathematical formula}cost(φn)=e and apply recursively e times the Eva transformation we end up with the Sequential counter encoding for an e-Cardinality constraint.
     </paragraph>
     <paragraph>
      Back to the algorithms, we have seen the particular transformation that Eva applies to {a mathematical formula}φn to get {a mathematical formula}φn′. Actually, we can use any other transformation if we ensure that {a mathematical formula}φn is MaxSAT reducible to {a mathematical formula}φn′+〈□,1〉. For example, when we have already reified the soft clauses {a mathematical formula}〈b‾i↔ci,∞〉 and we want to derive the empty clause from {a mathematical formula}φb, we can transform it into {a mathematical formula}φo′+〈□,1〉 as follows. We can replace the n soft clauses {a mathematical formula}〈bi,1〉 with {a mathematical formula}n−1 new pairs of clauses {a mathematical formula}〈o‾k,1〉,〈o‾k→(b1+,…,+bn≤k),∞〉 for {a mathematical formula}k∈{1,…,n−1} and an empty clause {a mathematical formula}〈□,1〉. We explain in detail this transformation in Example 3.
     </paragraph>
     <paragraph label="Example 3">
      Given {a mathematical formula}φb=〈〈b‾1,1〉,…,〈b‾4,1〉,〈b1∨…∨b4,∞〉〉, let us show an alternative transformation to derive the empty clause {a mathematical formula}〈□,1〉 and guarantee MaxSAT reducibility.Let us first notice that the formula on the left, {a mathematical formula}φb, is MaxSAT reducible to the formula on the right {a mathematical formula}φo. If the assignment {a mathematical formula}I:var(φb)→{0,1} sets m{a mathematical formula}bi variables to true: (i) the cost {a mathematical formula}I(φb) will be m and (ii) the cost {a mathematical formula}I(φo) will also be m since {a mathematical formula}ok will be true for {a mathematical formula}k∈{0,…,m−1}.{a mathematical formula}1:b‾11:b‾21:b‾31:b‾4∞:b1∨b2∨b3∨b4{a mathematical formula}1:o‾31:o‾21:o‾11:o‾0∞:CNF(b1+b2+b3+b4≥1)∞:CNF(o‾3→(b1+b2+b3+b4≤3))∞:CNF(o‾2→(b1+b2+b3+b4≤2))∞:CNF(o‾1→(b1+b2+b3+b4≤1))∞:CNF(o‾0→(b1+b2+b3+b4≤0))In the case of {a mathematical formula}φo, it is trivial to see that {a mathematical formula}〈o0,∞〉 is a logical consequence of the hard clauses. Applying the MaxSAT resolution rule to {a mathematical formula}〈o0,∞〉,〈o‾0,1〉, we can replace {a mathematical formula}〈o‾0,1〉 with {a mathematical formula}〈□,1〉, resulting {a mathematical formula}φo′+〈□,1〉:{a mathematical formula}For {a mathematical formula}(b1+b2+b3+b4≥k), we could replace {a mathematical formula}〈oi,1〉|i&lt;k with {a mathematical formula}〈□,k〉.
     </paragraph>
     <paragraph>
      Applying this alternative transformation to Eva is almost what OLL does. The only difference is that when OLL converts the working formula {a mathematical formula}φo′ to SAT (removes the weights) and sends it to the SAT solver to check if {a mathematical formula}cost(φo′)=0, it does not to include the clauses {a mathematical formula}(o‾2) and {a mathematical formula}(o‾3). Notice that all assignments to {a mathematical formula}bi variables that satisfy {a mathematical formula}(o‾1) also satisfy {a mathematical formula}(o‾2) and {a mathematical formula}(o‾3). OLL only sends to the SAT solver the clause {a mathematical formula}(o‾i+1) if {a mathematical formula}(o‾i) appeared previously in a unsatisfiable core. Therefore, we can conclude that both algorithms are in fact very similar. To see how the OLL algorithm was originally described for MaxSAT check Algorithm 1 of [42].
     </paragraph>
     <paragraph>
      Finally, for the non-weighted case, Eva and OLL increase at each iteration the lower bound only by 1 (i.e. {a mathematical formula}cost(φk)=cost(φk+1)+1). We know however that there are algorithms like WPM2 that can increase at each iteration the lower bound by more than 1 by optimizing subproblems [20]. In the next section, we will present the WPM3 algorithm that is able to increase the lower bound by more than 1 at each iteration like WPM2 while preserving some of the strengths of Eva and OLL.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The WPM3 complete algorithm
     </section-title>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      In this section, we present the WPM3 complete algorithm for the MaxSAT problem. Like Eva and OLL, it is a core-guided algorithm that only handles Cardinality constraints. In addition, WPM3 is able to increase the lower bound to higher values at each iteration and obtain also upper bounds and assignments. The basic schema of WPM3 consists in, given an input WPMS formula φ, testing the satisfiability of a sequence of SAT instances {a mathematical formula}ϕk where {a mathematical formula}0≤k≤∑w(φ). Each SAT instance {a mathematical formula}ϕk encodes whether there is an assignment to φ with a cost ≤k. Notice that SAT instances with {a mathematical formula}k&lt;cost(φ) are unsatisfiable, while the others are satisfiable. WPM3 increases the lower bound by testing unsatisfiable {a mathematical formula}ϕk SAT instances.
     </paragraph>
     <paragraph>
      Roughly speaking, from every unsatisfiable SAT instance WPM3 finds and keeps an unsatisfiable core. The algorithm is designed to be aware of the global structure of theses cores. This is used both for producing more efficient Cardinality constraint encodings (see Section 5) and focus the search on subproblems of the input WPMS instance.
     </paragraph>
     <paragraph>
      The algorithm maintains a set of soft at-most Cardinality constraints AM. We note these constraints as {a mathematical formula}〈A,k,w〉, where A is an ordered multiset of indexes of the original soft clauses, k indicates at most how many clauses from A can be falsified, and w is the cost for falsifying this soft constraint. The at-most constraints are used to do not accept those assignments whose cost exceeds the current k, where {a mathematical formula}k=∑〈Aj,kj,wj〉∈AMkj⋅wj. Moreover, the algorithm guarantees that {a mathematical formula}k≤cost(φ). The idea of maintaining multiple at-most Cardinality constraints instead of a single one was originally introduced in [49] for PM2 algorithm. Notice that from the AM set the global core structure can be obtained.
     </paragraph>
     <paragraph>
      We start (line 1) by adding to AM a soft at-most constraint for each original soft clause. Then, the algorithm will iterate (line 2) till it is able to determine {a mathematical formula}cost(φ). This will happen if it detects that the set of hard clauses is unsatisfiable (line 8, {a mathematical formula}cost(φ)=∞) or when it is able to generate the first satisfiable instance (line 5, {a mathematical formula}cost(φ)=k=I(φ)). We obviate for the moment the role of {a mathematical formula}wstrat and we consider it is ∞ for the first iteration and {a mathematical formula}min({wj})wj∈w(AM),wj≠0 for the rest.
     </paragraph>
     <paragraph>
      Function sat (line 3) builds the SAT instance {a mathematical formula}ϕk at the current iteration and sends it to the SAT solver. The SAT instance {a mathematical formula}ϕk is constructed through the union of the following sets expressed as SAT clauses: (i) the set of hard clauses, (ii) the reification to variables {a mathematical formula}bi of soft clauses, (iii) the reification to variables {a mathematical formula}aj of the translation into CNF of the at-most constraints in AM, and finally (iv) the unit clauses {a mathematical formula}a‾j. The new {a mathematical formula}bi variables are true if the respective original soft clause becomes false. They are used to encode the at-most constraints which restrict the number of falsified soft clauses. The new {a mathematical formula}aj variables are true if the respective at-most constraint becomes false. The unit clauses {a mathematical formula}a‾j encode that we would like to satisfy all the at-most constraints. If this is not possible, some of them will appear into the unsatisfiable core {a mathematical formula}ϕCk.
     </paragraph>
     <paragraph label="Example 4">
      Given {a mathematical formula}φ=〈〈x1,1〉,〈x2,1〉,〈x3,1〉, {a mathematical formula}〈x‾1∨x‾2,∞〉,〈x‾1∨x‾3,∞〉,〈x‾2∨x‾3,∞〉〉 and {a mathematical formula}AM=〈〈〈1,2〉,1,1〉,〈〈3〉,0,1〉〉, then:{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Following the same idea of the transformation in Example 3 of Section 3, we can consider that WPM3 maintains in AM the information to build a WPMS formula {a mathematical formula}φk such that {a mathematical formula}cost(φ)=cost(φk+〈□,k〉). For each {a mathematical formula}〈Aj,kj,wj〉 in AM, the clause {a mathematical formula}a‾j of Example 4 corresponds to {a mathematical formula}〈o‾kj,wj〉 according to the notation of Example 3. The formula {a mathematical formula}ϕk, sent to the SAT solver to check if {a mathematical formula}cost(φk)=0, does not include the clauses {a mathematical formula}o‾i|i&gt;kj and the corresponding Cardinality constraints since they are satisfied for all assignments to {a mathematical formula}bi variables that satisfy the clauses {a mathematical formula}o‾kj (i.e. {a mathematical formula}a‾j).
     </paragraph>
     <paragraph>
      Back to the WPM3 algorithm, if function sat returns satisfiable ({a mathematical formula}st=SAT) (line 4), then we return the optimal assignment {a mathematical formula}I and its cost (line 5). Otherwise (line 7), C is the set of indexes of at-most constraints involved into the last unsatisfiable core. If the core only involves original hard clauses, we can return unsatisfiable (line 8). If there are at-most constraints involved in the core, then, we need to relax some of them since they only allow assignments with a cost strictly less than {a mathematical formula}cost(φ).
     </paragraph>
     <paragraph>
      At this stage (lines 9–12), we need to relax the set of AM constraints, but guaranteeing we do not exceed {a mathematical formula}cost(φ). Basically, we need to replace the set of at-most constraints {a mathematical formula}AMC involved in the last core with a new set of at-most constraints which allows assignments with a higher cost.
     </paragraph>
     <paragraph>
      Since we will only use Cardinality constraints, we first apply the idea described in the WPM1/WBO MaxSAT algorithms [26], [27] to deal with weighted instances (lines 9–10). It basically prevents the algorithm to introduce weighted PB constraints instead of Cardinality constraints when the at-most constraints involved in the core have different weights. In this case, we compute the minimum weight {a mathematical formula}wmin of the constraints in {a mathematical formula}AMC (line 9), and replace every soft constraint {a mathematical formula}〈Aj,kj,wj〉 by two copies with weights {a mathematical formula}wj−wmin and {a mathematical formula}wmin. The first set of copies will remain in AM (line 10) while the second will be replaced by the new at-most constraint {a mathematical formula}〈A,kA,wmin〉 (line 12). Notice we guarantee that {a mathematical formula}∑〈Aj,kj,wj〉∈AM|Aj|⋅wj=∑w(φ).
     </paragraph>
     <paragraph>
      Function optimize (line 11) allows to determine which is the new {a mathematical formula}ϕk we will test. This function, originally described for the WPM2 algorithm [28], solves exactly the subproblem that involves the new at-most constraint we will generate on the original soft clauses, and the hard clauses. When we call the sat function within the optimize function, we set to 1 both {a mathematical formula}wstrat and the weight of the only at-most constraint we are considering in the set AM. The result is the set of indexes of original soft clauses A of the new at-most constraint (notice that any index can be repeated) and the number of clauses {a mathematical formula}kA that we will at most allow to be falsified. To our best knowledge, the idea of solving a subproblem of the original optimization instance φ was originally applied for MaxSAT in WPM2 algorithm [28]. In [50] a similar approach is applied calling a MIP solver to solve the subproblem. Recently, in [19], this process is extended and named as cover optimization. The best strategy reported consists in refining iteratively the upper bound on the subproblem using the model-guided MaxSAT algorithm in [34]. We apply it within function optimize, although depending on the particular family of instances other strategies or algorithms can have better performance. At this point we have increased k by {a mathematical formula}(kA−∑〈Aj,kj,wj〉∈AMCkj)⋅wmin towards {a mathematical formula}cost(φ). Without the optimize step, we can only increase k by {a mathematical formula}1⋅wmin.
     </paragraph>
     <paragraph>
      Treating explicitly the new at-most constraint on the original soft clauses (line 12) and its relation to the constraints it replaces is fundamental, not only for function optimize, but also to encode more efficient Cardinality constraints (see Section 5). In contrast, this information (the global core structure) is not explicitly present in Eva and OLL algorithms (see Section 3) and therefore harder to be exploited efficiently (see Section 6).
     </paragraph>
     <paragraph>
      During this description, we have obviated the role of {a mathematical formula}wstrat (lines 5 and 6). It corresponds to the application of the stratified approach introduced in [51]. The stratified approach consists in sending to the SAT solver only a subset of the soft clauses, i.e., those with a weight {a mathematical formula}≥wstrat. Function decrease updates conveniently {a mathematical formula}wstrat. This can help to reduce the size of the unsatisfiable cores, produce simpler at-most constraints and progress faster to the optimum. We also apply hardening techniques like the ones described in [31], [38], [19].
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Efficient cardinality constraints for MaxSAT
     </section-title>
     <paragraph>
      In the last decade, we have seen many contributions on how to encode efficiently PB and Cardinality constraints into SAT [52], [48], [33], [53], [40]. The goal is to achieve an arc-consistent encoding (i.e., with good propagation properties) as small as possible.
     </paragraph>
     <paragraph>
      Since WPM3 only uses Cardinality constraints, let us consider the Cardinality constraint: {a mathematical formula}b1+⋯+bn≤k. From the sake of clarity, the encoder is split into two black boxes: the sum and the operator op (in our case representing ≤). The sum takes as input a list of n variables {a mathematical formula}[b1,…,bn] and returns a set of SAT clauses S and a list of {a mathematical formula}m+1 variables {a mathematical formula}[o0,…,om]. The operator takes as input the o variables and integer k and returns a set of SAT clauses OP. The encoding of the Cardinality constraint into SAT corresponds to the union {a mathematical formula}S∪OP.{a mathematical formula}
     </paragraph>
     <paragraph>
      In our case, we use the Cardinality Networks encoding in [40]. There, {a mathematical formula}m=k and the sum builds a SAT formula such that if i of the input b variables are set to true then the first i of the output o variables are set to true. Therefore, op returns the unit clause {a mathematical formula}o‾k.{sup:1}
     </paragraph>
     <paragraph>
      Our first observation is that it is crucial for the efficiency of the MaxSAT solver in which order the b variables are fed into the sum. In previous MaxSAT solvers, the order of the b variables was not taken into account. They were just added in the same order of their respective soft clauses.
     </paragraph>
     <paragraph>
      However, the b variables should be added taking into account the structure of the unsatisfiable cores. In particular, variables belonging to the same core should be as close as possible. In our algorithm the set A in an at-most constraint {a mathematical formula}〈A,k,w〉 is ordered. In line 1 of function optimize (see Section 4) when we generate the set A of the new at most constraint, we concatenate the sets of b variables of the at-most constraints that it replaces. Respect to latest advances in MaxSAT [42], [43] a deeper explanation of their efficiency could be that these algorithms implicitly preserve the order.
     </paragraph>
     <paragraph>
      Our second observation has to do again with the structure of the unsatisfiable cores we have detected so far. As we have just commented, the new at-most constraint {a mathematical formula}〈A,kA,wmin〉 (line 12 of WPM3) replaces/merges other at-most constraints. In the end, we can consider that there is a tree structure that represents how we have merged the unsatisfiable cores and where the root node is the new at-most constraint. We can store this tree structure by replacing in the new at-most constraint, the multiset A by the set C of indexes of the merged at-most constraints in AM. Going over the tree, we find in the leaf nodes exactly the same indexes we would have in A. Instead of creating a Cardinality Network for the new constraint we can reproduce this tree structure. We basically reproduce the totalizer encoding proposed originally in [52]. The leaf nodes join the at-most constraints related with a single soft clause of the input formula (i.e., with {a mathematical formula}k=0) that appeared in the same core. The leaf nodes are encoded with Cardinality Networks.
     </paragraph>
     <paragraph label="Example 5">
      Imagine at-most constraint {a mathematical formula}〈A3,5,1〉 (root node) replaces at-most constraints {a mathematical formula}〈A1,2,1〉 and {a mathematical formula}〈A2,1,1〉 (child 1 and child 2). Let us see how we start constructing the tree. Children are processed recursively in the same way{sup:2}:{a mathematical formula}{a mathematical formula}We can represent the tree structure of the constraint as follows (the big boxes represent the merge function){sup:3}:{a mathematical formula}Using the totalizer encoding, the set {a mathematical formula}S′ would be as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      The advantage of preserving this structure, in contrast to having a single Cardinality constraint, is that we can again exploit it to derive smaller encodings. In particular, we can use the lower bounds of each node to skip parts of the encoding. Moreover, we can restrict the upper bounds of the nodes using the lower bounds of their siblings. The upper bound for a non root node is set to the difference between the upper bound of its parent and the sum of the lower bounds of its siblings. We apply this in a top-down update process.
     </paragraph>
     <paragraph label="Example 6">
      At Example 5, the upper bound for the root node is 5. Child 1 (child 2) already contributes with a lower bound of 2 (1), therefore the new upper bound for child 1 (child 2) is {a mathematical formula}5−1=4 ({a mathematical formula}5−2=3){sup:4}:{a mathematical formula}{a mathematical formula}The tree structure can be represented as follows (the lower bounds are represented: by empty clauses □ at the root node for the new constraint, and, by the value false F at the intermediate nodes for the replaced constraints):{a mathematical formula}Taking into account the lower and upper bounds of all constraints, the following parts of the set S' of Example 5 can be skipped:{a mathematical formula}
     </paragraph>
     <paragraph>
      Finally, the upper bound of the root node can be initialized taking into account the information retrieved in previous calls to optimize function. In particular, the assignments that this function provides can be used to get upper bounds for the whole formula (see Section 7). The upper bound of the root node can be initialized to the cost of the best global assignment on the set of soft clauses related to it.
     </paragraph>
     <paragraph>
      In particular, the previously described encoding is applied in line 1 of the sat function where the SAT encoding of the Cardinality constraints is generated. Experiments comparing these encodings are shown in Table 1 (Section 8).
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Comparison of WPM3 with EVA and OLL
     </section-title>
     <paragraph>
      According to Sections 3 and 4, WPM3, OLL and Eva maintain a working WPMS formula {a mathematical formula}φk and transform it at each iteration. These transformations guarantee that {a mathematical formula}cost(φ)=…=cost(φki+〈□,ki〉)=cost(φki+1+〈□,ki+n⋅wmini〉)=…. Each {a mathematical formula}φk without weights is sent to a SAT solver and if it is satisfiable ({a mathematical formula}cost(φk)=0), k is the optimum. One of the advantage of WPM3 is that, unlike Eva and OLL, n can be more than 1 at each iteration. It achieves this by applying cover optimization efficiently thanks to being aware of the global structure of the cores. One of the key points is how WPM3 can explicitly build constraints on the original soft clauses like the others do implicitly. We can see this in Example 7.
     </paragraph>
     <paragraph label="Example 7">
      To illustrate how WPM3 builds explicitly Cardinality constraints on the original soft clauses like Eva and OLL do implicitly, let us compare the three iterations they make to solve the following pigeon-hole formula{sup:5}:{a mathematical formula}Each {a mathematical formula}xi ({a mathematical formula}bi) variable corresponds to a pigeon. If it is true (false), the pigeon is in a hole. According to hard clauses, there are only two holes so only two pigeons can be in a hole (at most 2 true {a mathematical formula}xi variables) and the rest must be out (at least 3 true {a mathematical formula}bi variables). Therefore, the optimum is 3.In the first iteration, the three algorithms send the input MaxSAT formula without weights to a SAT solver to check if {a mathematical formula}cost(φ)=0, and get the unsatisfiable core {a mathematical formula}{b‾1,b‾2,b‾3}∪ϕH. Then, they transform φ to derive the empty clause and generate {a mathematical formula}φ1. WPM3 and OLL replace the soft clauses of the core with two new soft clauses, {a mathematical formula}〈o‾11,1〉 and {a mathematical formula}〈o‾21,1〉, and corresponding Cardinality constraints allowing respectively 1 and 2 of the original soft clauses ({a mathematical formula}bi variables) of the core to be false (true). The soft clause {a mathematical formula}〈o‾21,1〉 and corresponding Cardinality constraint are highlighted, meaning they are not needed to check if {a mathematical formula}cost(φ1)=0 in the next iteration (({a mathematical formula}o‾21) is satisfied for all assignments to {a mathematical formula}bi variables that satisfy ({a mathematical formula}o‾11)). Eva replaces the soft clauses of the core with two new soft clauses obtained by applying successively the MaxSAT resolution rule. The three resulting {a mathematical formula}φ1 allow one pigeons to be out (1 true {a mathematical formula}bi variable):{a mathematical formula}We can see a representation of the transformations below these lines. The original soft clauses are at the bottom ({a mathematical formula}b‾i) and the new soft clauses at the top (in the case of Eva, {a mathematical formula}c11 and {a mathematical formula}c12 represent {a mathematical formula}b1‾∨(b2∨b3)‾ and {a mathematical formula}b2‾∨b3‾ respectively). The big boxes represent the Cardinality constraints (see Section 5):{a mathematical formula}In the second iteration, the three algorithms retrieve an unsatisfiable core from {a mathematical formula}φ1 and proceed to generate {a mathematical formula}φ2. WPM3 and OLL get a core containing the soft clauses {a mathematical formula}{b‾4,b‾5,o‾11} and then, the differences between them begin. WPM3 replaces the soft clauses {a mathematical formula}〈b‾4,1〉{a mathematical formula}〈b‾5,1〉 and {a mathematical formula}〈o‾11,1〉 (Cardinality constraints {a mathematical formula}〈{4},0,1〉, {a mathematical formula}〈{5},0,1〉 and {a mathematical formula}〈{1,2,3},1,1〉 using the notation of Section 4) with a new one {a mathematical formula}〈o‾22,1〉 that merges them ({a mathematical formula}〈{1,2,3,4,5},2,1〉). OLL just handles the soft clause {a mathematical formula}〈o‾11,1〉 the same way as the original ones, {a mathematical formula}〈b‾4,1〉 and {a mathematical formula}〈b‾5,1〉, building the new Cardinality constraint on the current soft clauses instead of on the original ones. This is why, when it checks if {a mathematical formula}cost(φ2)=0, it needs to take into account {a mathematical formula}〈o‾21,1〉 and the corresponding Cardinality constraint. Eva gets a core containing the soft clauses {a mathematical formula}{b‾4,b‾5,c11} and replaces them with two new ones. Notice that the three {a mathematical formula}φ2 allow two pigeons out (2 true {a mathematical formula}bi variables). However, the only algorithm that has explicitly introduced a Cardinality constraint on the original soft clauses ({a mathematical formula}bi variables) is WPM3:{a mathematical formula}In the representation of the transformations, we can see how WPM3 builds explicitly a Cardinality constraint on the original soft clauses ({a mathematical formula}bi variables). Thus, it is the only one able to apply cover optimization efficiently, find out that {a mathematical formula}〈o22,1〉 can also be replaced with {a mathematical formula}〈□,1〉, increase the lower bound by 2 and get the optimum before the third iteration. The Cardinality constraints introduced by OLL and Eva are not aware of the global structure:{a mathematical formula}In the third and last iteration, the third empty clause is derived and {a mathematical formula}φ3 is generated. Without cover optimization, WPM3 would just get a core with the soft clause {a mathematical formula}{o‾22} and replace it with an empty set. OLL and Eva, both get a core with two soft clauses and replaced them with one. After these transformations, all three {a mathematical formula}φ3 allow three pigeons out (3 true {a mathematical formula}bi variables). This is the condition imposed by the hard clauses, so we will find that {a mathematical formula}cost(φ3)=0 and know that {a mathematical formula}cost(φ)=cost(φ3+〈□,3〉)=3:{a mathematical formula}In the representation of the transformations, we can see how the Cardinality constraints {a mathematical formula}b1+…+b5≤3 is built explicitly in the case of WPM3 and implicitly in the case of the other two algorithms:{a mathematical formula}
     </paragraph>
     <paragraph>
      Example 7 shows how WPM3 builds explicitly Cardinality constraints on the original soft clauses while OLL and Eva build them implicitly. The advantage of doing this is that, by maintaining the global structure, WPM3 is able to perform cover optimization efficiently. If we look at the representations of the second iteration, we find a situation where WPM3 is able to increase the lower bound by more than 1 using cover optimization, while others are not. In the case of OLL for example, it does not fully exploit that {a mathematical formula}o‾11 is a constraint on three original soft clauses and therefore the lower bound of the new constraint can not be increased by more than 1. This example also brings some light on why cover optimization was experimentally shown to be specially effective after merging constraints in [20].
     </paragraph>
     <paragraph>
      Finally, we will show in our experimentation that building incrementally Cardinality constraints helps but preserving the structure of the cores is the key of the boost on the performance of the solvers. A version of WPM3 feeding from scratch the new Cardinality constraint at each iteration but preserving the structure of the cores is already competitive compared with OLL and EVA. By applying cover optimization, we further improve the performance. Building incrementally Cardinality constraints is just a final step to improve the performance a little bit more.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      WPM3 incomplete: upper bounds and phase saving
     </section-title>
     <paragraph>
      In Section 4, we have described the complete core-guided algorithm WPM3 that keeps increasing a lower bound towards the optimum. However, its design, in particular function optimize which implements a model-guided MaxSAT algorithm, allows to produce upper bounds during its execution. Whenever function optimize finds an assignment to the subproblem, we can just extend this assignment to the rest of the formula and check its cost, obtaining this way naturally an incomplete approach. We do this by considering that, those clauses in an undefined state under the assignment to the subproblem, are falsified.{sup:6} Function optimize keeps track of the assignment to the subproblem whose extension to the rest of the formula had the lowest cost. The cost of this assignment is an upper bound for the whole problem. We will refer to it as the best global assignment found by function optimize.
     </paragraph>
     <paragraph>
      We can further exploit the best global assignment we get from function optimize. State-of-the-art SAT solvers apply a technique called phase saving introduced in [45]. In SAT solvers, when non-chronological backtracking is applied due to a conflict, lots of variable assignments get lost and have to be revealed again during search. The idea is to avoid redoing this work by storing the phase of the variables when we find a conflict. Then, we assign to the next decision variables the stored polarity till we find a new conflict and update the polarities again. This technique has been shown to be quite effective. We can extend this idea to MaxSAT in the following way. Within function optimize we let the SAT solver apply phase saving in the regular way (line 5). Then, if the best global assignment found so far has the same cost for the subproblem as the solution found by function optimize, we store the polarity of the variables in the best global assignment. We use these polarities to guide the search of the SAT solver in line 3 of WPM3, disabling the regular phase saving that would be applied. In particular, we only store the polarities of the original variables in φ.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      Initially, we evaluated our WPM3 algorithm and the impact of each technique described in the previous sections (Subsection 8.1). Then, we submitted the best variation of WPM3 to the last editions of the international MaxSAT Evaluation (MSE-2015 and MSE-2016), both at the complete and the incomplete track (Subsection 8.2). Finally, we also explored some new configurations of our solver to further improve its performance as an incomplete solver (Subsection 8.3).
     </paragraph>
     <section label="8.1">
      <section-title>
       Experiments on MaxSAT evaluation 2014 instances
      </section-title>
      <paragraph>
       To evaluated our WPM3 algorithm, we conducted an initial experimentation on the industrial instances from the MSE-2014. We run our experiments on a cluster featured with 2.6 GHz processors and a memory limit of 3.5 GB. The instance set of MSE-2014 is divided into three categories depending on the variant of the MaxSAT problem: MaxSAT (MS), Partial MaxSAT (PMS) or Weighted Partial MaxSAT (WPMS). In each category, instances are grouped by families: 2 for MS, 22 for PMS and 8 for WPMS. Since families have different number of instances, we considered more fair to present the solvers ranked by mean family ratio of solved instances.
      </paragraph>
      <paragraph>
       We provide results for the new {a mathematical formula}wpm3 MaxSAT solver and the best solvers of the MSE-2014. We have excluded the MaxSAT solver {a mathematical formula}ISAC+[54], since it is a portfolio and our intention here is to compare ground solvers. The ground solvers with the best overall performance at MSE-2014 for industrial instances were: {a mathematical formula}eva500a[43], {a mathematical formula}mscg[42] and {a mathematical formula}open-wbo[32].
      </paragraph>
      <paragraph>
       Table 1 shows our first experiment, where we evaluate the impact of each improvement on WPM3 (with a timeout of 1800 seconds). All the variations on WPM3 are implemented on top of the glucose SAT solver (version 3.0) [55]. The different variations and corresponding implementations are named {a mathematical formula}wpm3 with different subindexes. Subindex o stands for cover optimization (see Section 4). Regarding how Cardinality constraints are encoded, t stands for core based tree, {a mathematical formula}tk stands for core based tree with refinement of the k upper bound in sub-sums (see Section 5). Finally, p stands for phase saving extended to MaxSAT (see Section 7).
      </paragraph>
      <paragraph>
       At the table, we present for each category and solver the mean ratio of solved instances per family and the total number of instances. We introduce results for {a mathematical formula}wpm1/wbo[26], [27] and {a mathematical formula}pm2 algorithms.{sup:7}{a mathematical formula}wpm3 can be considered as a hybridization of these two algorithms (see Section 4). As we can see, {a mathematical formula}wpm3 clearly outperforms {a mathematical formula}pm2. This is because, as described in Section 5, we build Cardinality constraints taking into account the order imposed by the unsatisfiable cores. If we add the cover optimization technique, see {a mathematical formula}wpm3o, then we get a version that would have ranked the first at MSE-2014 for industrial instances in terms of the total mean family ratio. The next two versions, {a mathematical formula}wpm3t and {a mathematical formula}wpm3tk, that further exploit the structure of the cores and improve the construction of the Cardinality constraint, provide a total of 13 additional solved instances for PMS and 13 for WPMS. As we can see, the cover optimization technique always improves, in particular for weighted instances at version {a mathematical formula}wpm3tko. Finally, the extension of phase saving for MaxSAT improves the average running time, and it helps to solve 7 additional instances within the timeout.
      </paragraph>
      <paragraph>
       Table 2 compares our best version {a mathematical formula}wpm3tkop with the best performing complete solvers at MSE-2014 for industrial instances. Clearly, {a mathematical formula}wpm3tkop dominates both on mean family ratio and total number of solved instances. A deeper analysis reveals that {a mathematical formula}wpm3tkop has best ratio on 30 out of the 32 families that compose the categories, while {a mathematical formula}eva500a (the second one) has best ratio on 20.
      </paragraph>
      <paragraph>
       Our last experiment is presented in Table 3. Since {a mathematical formula}wpm3tkop is able to produce upper bounds we also compared it with the best performing solvers {a mathematical formula}wpm2014 and {a mathematical formula}optimax{sup:8} for industrial instances at the incomplete track of the MSE-2014. We also compared with other MaxSAT solvers that did not take part in the incomplete track but they are able to produce upper bounds: {a mathematical formula}open-wbo[32] and qms[35]. We do not include {a mathematical formula}eva500a and {a mathematical formula}mscg since they can not produce upper bounds.
      </paragraph>
      <paragraph>
       The timeout for the incomplete track at MSE is set to 300 seconds. For a given instance, the winners are the solvers that produce the best upper bound. The best solver is the one that won on more instances. Since these results give us a partial order, it can be misleading to report an overall winner. In Table 3, we present the dominance relation between pairs of solvers on the three categories. For example, {a mathematical formula}wpm3tkop ({a mathematical formula}open-wbo) is able to obtain a better or equal upper bound than {a mathematical formula}open-wbo ({a mathematical formula}wpm3tkop) on 50 (45) ms instances, 556 (466) PMS instances and 394 (344) WPMS instances. As we can see, {a mathematical formula}wpm3tkop practically dominates the rest of the solvers. The exception is qms on PMS where qms outperforms by 9 instances {a mathematical formula}wpm3tkop. For this case, we extended the timeout to 1800 seconds. We found that {a mathematical formula}wpm3tkop outperformed qms by 5 instances. This is somehow expected since {a mathematical formula}wpm3tkop, within this timeout, solves to optimality 40 instances more than qms.
      </paragraph>
      <paragraph>
       Finally, the WPM3 variants described so far build from scratch the new Cardinality constraint at each iteration. To know the impact of building them incrementally, like Eva and OLL, we implemented the incremental WPM3 variant ({a mathematical formula}wpm3tkop⁎) as in [32]. This variant reuses as much as possible the encodings of the replaced constraints, already introduced to the SAT solver, to build the encoding of the new constraint. We show the results of {a mathematical formula}wpm3tkop⁎ in Table 4 following the same criteria of Table 1. With respect to {a mathematical formula}wpm3tkop, it increases the number (mean family ratio) of solved instances in 13 (0,7%). This increase is not as much as the 51 (3.1%) of {a mathematical formula}wpm3tkop with respect to {a mathematical formula}wpm3 in Table 1. We can conclude that what makes the difference is taking into account the structure of unsatisfiable cores to build the Cardinality constraints and apply cover optimization.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Results at the MaxSAT evaluation 2015 and 2016
      </section-title>
      <paragraph>
       We submitted the best variation of WPM3 ({a mathematical formula}wpm3tkop⁎) to the last editions of the international MaxSAT Evaluation (MSE-2015 and MSE-2016) both at the complete and the incomplete track, with the names {a mathematical formula}WPM3-2015-co and {a mathematical formula}WPM3-2015-in respectively. The results for industrial instances of all ground solvers at MSE-2015, excluding the portfolio approach {a mathematical formula}ISAC+-2015 [56] that also incorporated {a mathematical formula}WPM3-2015-co, are summarized in Table 5, Table 6. At the complete track, {a mathematical formula}WPM3-2015-co showed a good performance being first and third for PMS and MS industrial subcategories, respectively. At the incomplete track, {a mathematical formula}WPM3-2015-in won two of the three industrial subcategories, being second in the other and the best solver overall. The other best performing solvers that took part at the complete track of the evaluation were: the new versions of {a mathematical formula}mscg and {a mathematical formula}open-wbo, slightly improved with respect to those submitted to MSE-2014, {a mathematical formula}maxino, based on the core-guided algorithm described in [57], {a mathematical formula}MaxHS and {a mathematical formula}LMHS, both based on core-guided algorithm as described in [50], [58], [59], [60]. The two last solvers are interesting alternatives that do not need PB constraints and excelled in few families with a particular structure of weights. They placed in number but not in mean family ratio of solved instances. However, they do not produce upper bounds and can not work as incomplete approaches. At the incomplete track, the other best performing solvers were: {a mathematical formula}optiriss, an extension of {a mathematical formula}open-wbo, and ILP, that translated the instance into ILP and applied an ILP solver as described in [61]. Details about all the solvers and authors can be found in [62].
      </paragraph>
      <paragraph>
       {a mathematical formula}
      </paragraph>
      <paragraph>
       In Table 7, we analyze in detail the results of {a mathematical formula}WPM3-2015-in on the industrial instances at the incomplete track of MSE-2015. The rows correspond to the subcategories, with the column marked “#” specifying the total number of instances in the class. The columns correspond to solvers, being the first one the virtual best solver at the complete track (VBS-co). For VBS-co and each class, we present the number and mean family ratio of solved instances in 1800 seconds. The rest of the columns correspond to the virtual best solvers at the incomplete track (VBS-in) and the incomplete solvers that took part in the evaluation. For each incomplete solver and class, we present the number of instances where the solver reported the best upper bound in 300 seconds and the mean family ratio according to this number. For the solvers with different versions, the best upper bound on each instance is considered. The solvers {a mathematical formula}dist[16] and cc[17] are based on local search and, although overall not competitive on industrial instances with those modified from complete SAT-based solvers, they are competitive on crafted instances and better on random instances.
      </paragraph>
      <paragraph>
       The mean family ratio of solved instances in 1800 seconds for VBS-co is 85,3%. However, for some industrial domains the objective is not finding the optimum (optimal assignment) but an upper bound (assignment) of a good quality in a reasonable time. In this sense, the mean family ratio of instances where VBS-in is able to obtain an upper bounds in 300 seconds is 98,0%. To measure the quality of these upper bounds we can use the complementary of their relative distance to the optimum, i.e. an upper bound equal to the aggregated cost of all soft clauses or to the optimal cost, has a quality of 0% or 100%, respectively. For those instances with know optimums, those solved by VBS-co, the upper bound obtained by VBS-in in 300 seconds has always a quality of more than 75%. Moreover for all except a couple of instances the quality is more than 90%. For more information about the quality of optimums obtained thanks to cover optimization see [20].
      </paragraph>
      <paragraph>
       At MSE-2016, {a mathematical formula}WPM3 maintained the positions achieved at MSE-2015 in the rankings of almost all industrial subcategories, both at the complete and the incomplete track. The only exceptions were MS and PMS industrial subcategories at the incomplete track. However, {a mathematical formula}dsat-{a mathematical formula}wpm3-in-ms, the second and first best solver on the respective subcategories, has {a mathematical formula}WPM3 as an underlying solver.
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Experiments with different solver configurations
      </section-title>
      <paragraph>
       Finally, to place a solver in the first positions of the evaluation, it has to be as robust as possible across all families of a category. However, the best overall performing solvers on a category can be outperformed on some families by others that are less competitive overall. It happens the same with different parameter configurations of a given solver [56]. The parameters include some options of the MaxSAT solver as well as some others of the underlying SAT solver. For the SAT solver we experimented with:
      </paragraph>
      <list>
       <list-item label="•">
        -incremental: ‘on’ if glucose incrementality is activated, ‘off’ otherwise.
       </list-item>
       <list-item label="•">
        -rnd-init: ‘on’ if the initial activity counters are random, ‘off’ otherwise.
       </list-item>
       <list-item label="•">
        -szTrailQueue N: N is the size of glucose trail queue.
       </list-item>
       <list-item label="•">
        -szLBDQueue N: N is the size of glucose LBD queue. LBD stands for Literal Block Distance.
       </list-item>
      </list>
      <paragraph>
       For the MaxSAT solver with:
      </paragraph>
      <list>
       <list-item label="•">
        -optimize k: where {a mathematical formula}k∈{0,1,2,3} specifies when cover optimization is applied (see [20]). {a mathematical formula}k=3 means that we skip cover optimization and {a mathematical formula}k=1 that we only apply it after merging Cardinality constraints.
       </list-item>
       <list-item label="•">
        -posFReif k: where {a mathematical formula}k∈{0,1}. When reifiying a soft clause into an auxiliary variable we can apply a full or half reification. If {a mathematical formula}k=1 and the reification variable has appeared in a previous suboptimal solution assigned to true, then Full reification is applied. Otherwise, {a mathematical formula}k=0, half reification is applied.
       </list-item>
       <list-item label="•">
        -polV k: where {a mathematical formula}k∈{0,1}. If {a mathematical formula}k=1, the polarity of original variables is set according to the value in the suboptimal best interpretation obtained so far.
       </list-item>
      </list>
      <paragraph>
       In Table 9, Table 10, Table 11 we show the results (best upper bound in 300 seconds) of some variants of our solver {a mathematical formula}wpm3 that we have configured for the incomplete track. We can see that on some families and subcategories several configurations are better than the solver we submitted to MSE-2016 (e.g. {a mathematical formula}C1m, {a mathematical formula}C1p and {a mathematical formula}C3w on MS, PMS and WPMS instances respectively). For example, on trail-tr WPMS family {a mathematical formula}C10w gets the best upper bound in 300 seconds for 6 instances while {a mathematical formula}C3w only for 4 and {a mathematical formula}C1w only for 2. Developing this configuration process and implementing new features we could improve even further the performance of {a mathematical formula}wpm3 (see [56]).
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>