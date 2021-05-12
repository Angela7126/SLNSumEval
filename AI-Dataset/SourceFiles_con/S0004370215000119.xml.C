<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Finding core for coalition structure utilizing dual solution.
   </title>
   <abstract>
    When forming the grand coalition is not possible or optimal, agents need to create a coalition structure. The idea of the core can be extended to such a case. In this paper, we propose an innovative exact algorithm called CoreD to check core-non-emptiness for coalition structures. A more straightforward exact algorithm based on existing techniques, which we call CoreP, first obtains the value of optimal coalition structure by solving an integer programming problem. Then, it checks whether that value can be divided without making a blocking (dissatisfied) coalition. In contrast, CoreD first finds a minimal value of the optimal coalition structure so that there exists no blocking coalition. Next, it checks whether the optimal value equals the minimal value We empirically show that when the core is empty, CoreD is by far superior to CoreP. Also, to find a second-best payoff vector when the core is empty, we propose a new solution concept called the weak ε-core+, which can utilize the approximate value of the optimal coalition structure. Based on the idea of CoreD, we further develop an algorithm for checking the non-emptiness of the weak ε-core+.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Coalition formation is an important capability in automated negotiation among self-interested agents. As a result, coalitional game theory has attracted much attention from AI and multi-agent systems (MAS) researchers [7], [12]. In a traditional model of coalitional game theory, it is assumed that all coalitions are possible and that the characteristic function is super-additive; when two coalitions are merged, the merged coalition can obtain at least the sum of the values of the two original coalitions. However, organizing a large coalition can be costly, e.g., such coordination overhead as communication costs. If time is limited, the agents may not have time to carry out the communications and the computations required to coordinate effectively within the composite coalition, and so component coalitions may be more advantageous.
     </paragraph>
     <paragraph>
      Furthermore, in many real-world applications, there can be inherent constraints on possible coalitions. For example, in many countries, antitrust laws prohibit the formation of certain coalitions of companies (cartels) that can dominate an entire market. Constraints may be placed on coalition sizes to permit or prohibit particular sizes. There can be some underlying graphical structure that determines the possible communication patterns among agents. Therefore, it is natural to assume that making a coalition is possible only when its members can communicate with each other. There exist several works that have considered such constraints on possible coalitions [41], [11], [29], [35], [31], [21].
     </paragraph>
     <paragraph>
      When the grand coalition, i.e., the coalition of all agents, is not possible or optimal, the agents should be divided into smaller coalitions; agents need to create a coalition structure to maximize the reward they can obtain [37]. Furthermore, to make a coalition structure stable, agents need to agree how to divide among themselves the reward obtained by the coalition structure. The core [13], which is a prominent solution concept in the traditional model of coalitional game theory, can be extended to such a case when the grand coalition is not possible or optimal and agents form a coalition structure [2].
     </paragraph>
     <paragraph>
      For instance, consider a coalitional form game with three agents: {a mathematical formula}A={a,b,c}. The characteristic function v represents a mapping from a coalition S (a subset of agents) to the worth or the value earned by the coalition: {a mathematical formula}v({a})=v({b})=0, {a mathematical formula}v({c})=3, {a mathematical formula}v({a,b})=12, {a mathematical formula}v({b,c})=v({c,a})=8, and {a mathematical formula}v({a,b,c})=15. A payoff vector {a mathematical formula}y=(ya,yb,yc) that belongs to the core can be computed by linear programming in such a way that for every coalition S, {a mathematical formula}v(S) does not exceed the total payoff of the agents in S and such that the total payoff equals {a mathematical formula}v(A). In this example, the core payoff vector is {a mathematical formula}y=(p,12−p,3), where {a mathematical formula}p∈[5,7]. Let us turn to a case where the grand coalition is prohibited in the above example. The concept of the core can be extended to this situation. The agents can create coalition structure {a mathematical formula}CS={{a,b},{c}} and obtain 15 reward and share it efficiently. The coalition structure {a mathematical formula}{{a,b},{c}} is optimal in the sense that the total payoff {a mathematical formula}V(CS) is maximized. The payoff vector in the core for the coalition structure is the same as in the first example.
     </paragraph>
     <paragraph>
      Checking whether the core is non-empty or not in itself is done in polynomial time in the number of allowed coalitions because it is formulated as a linear programming problem. However, Conitzer and Sandholm [8] pointed out that it requires many constraints for all the subcoalitions and the size of the representation (input) is exponential in the number of agents. Any algorithm for computing the core payoff vector requires time exponential as long as it reads all the input. If a coalition is prohibited or if its value is not explicitly specified, the algorithm may need to compute every value of such coalitions. Computing a value of a coalition is not necessarily straightforward because the agents must solve a complex collaborative planning problem.
     </paragraph>
     <paragraph>
      In general, as we noted below, computing an optimal coalition structure is known to be NP-hard and checking whether there exists a core for the (optimal) coalition structure or not is NP-complete unless its value is explicitly provided. Thus, our research goal is to develop an exact algorithm whose average runtime is much faster than traditional methods, although the worst-case complexity is doomed to be exponential in the number of explicitly given coalitions. Based on existing techniques, we can construct an algorithm to check core-non-emptiness for coalition structures, which we call CoreP. In this algorithm, the value of optimal coalition structure {a mathematical formula}V(CS⁎) is obtained by solving an integer programming (IP) problem [25]. The algorithm checks whether {a mathematical formula}V(CS⁎) can be divided without making a blocking (dissatisfied) coalition by solving a linear programming (LP) problem [8].
     </paragraph>
     <paragraph>
      In this paper, we propose an exact algorithm called CoreD, which utilizes the dual problem of the linear relaxation of the above IP problem. Experimental evaluations show that CoreD is by far superior to CoreP when the core is empty. To find a second-best payoff vector when the core is empty, we introduce a new approximate solution concept called weak ε-core{sup:+} for the weak ε-core for the optimal coalition structure. The weak ε-core is defined for a particular coalition structure that may or may not be not optimal, relaxes only the non-blocking condition with parameter ε, and efficiently distributes the rewards that the coalition structure earns. On the other hand, the weak ε-core{sup:+} does not specify a particular coalition structure beforehand. It then relaxes the efficiency condition of the weak ε-core (for the optimal coalition structure), in addition to the non-blocking condition, and efficiently distributes the reward that the dual solution provides. Thus, the sum of the elements in the payoff vector, i.e., the sum of the rewards distributed to agents, can be less than the value of the optimal coalition structure, but the difference must be at most {a mathematical formula}ε⋅n, where n is the number of agents. Based on the idea of CoreD, we also develop an algorithm for checking the non-emptiness of the weak ε-core{sup:+} called {a mathematical formula}ECore+(ε).
     </paragraph>
     <paragraph>
      This paper is organized as follows. Section 2 briefly describes the basic terms and notations and Section 3 introduces an existing technique for checking core-non-emptiness, proposes our proposed technique, and derives an associated theorem. Based on the our technique, Section 4 develops a novel solution concept, which we call weak ε-core{sup:+}. Section 5 empirically examines our proposed algorithm from some criteria. Section 6 describes four issues to our contributions, and Section 7 concludes this paper.
     </paragraph>
     <section label="1.1">
      <section-title>
       Related works
      </section-title>
      <paragraph>
       This subsection briefly explores related works. In traditional models of coalitional game theory, it is assumed that all coalitions are possible and that the characteristic function is super-additive. Forming the grand coalition is guaranteed to be optimal and the main research topic is how to divide the gain of the grand coalition among agents. The traditional theory of coalitional games provides a number of solution concepts, such as the core [13], the Shapley value [39], and the nucleolus [38].
      </paragraph>
      <paragraph>
       More recently, AI and MAS researchers have been considering the case where forming the grand coalition is not possible or not optimal. In such cases, agents should form a coalition structure to maximize the reward they can obtain. This problem is called the coalition structure generation (CSG) problem and has been an active research topic in AI and MAS.
      </paragraph>
      <paragraph>
       Sandholm et al. [37] show that the worst-case complexity of CSG problems is {a mathematical formula}O(nn) in general. Rahwan et al. [30] develop a state-of-the-art algorithm based on dynamic programming, whose complexity is {a mathematical formula}O(3n). Furthermore, in several class of games [6], [3], [15], [42], [5], the complexity of CSG problems has been examined and several tractable classes have been identified. For instance, Bachrach et al. [6] identify coalitional skill games where the complexity is polynomial for the games with a constant number of skills and a constant length of tree width. Many faster and scalable algorithms have also been designed [30], [34], [25], [22], [32], [33].
      </paragraph>
      <paragraph>
       CSG is deeply related to the winner determination (WD) problem that has been scrutinized in the literature of combinatorial auctions, see Part III [9] for an extensive survey. In combinatorial auctions, agents (bidders) are interested in buying a bundle of objects (goods) that may have some level of complementarities, i.e., an agent wants a set of objects simultaneously and submit higher bid to it than to a single object. The WD problem finds the allocation (combination of bids) that maximizes the sum of the value of the objects. Both the CSG and WD problems are essentially the set packing problem, which divides distinct objects into several non-overlapping subgroups such that the sum of the payoffs/values of the objects in each subgroup is maximized (see [23] for example). Since the seminal paper by Sandholm [36] reveals that the complexity of the WD problem is NP-hard in standard assumptions, it has been analyzed in a variety of settings of combinatorial auctions. Several tractable classes of problems are identified and some concise bidding languages (representations) are proposed that practically mitigate the complexity hurdle in the presence of the complementarities. In this context, the main idea of this paper is similar to Nisan [24].
      </paragraph>
      <paragraph>
       In most of the existing literature on CSG, there exists no restriction on possible coalitions, that is, all coalitions are allowed. There exist several works that have considered constraints on possible coalitions. From the perspective of game theory Demange [11] characterizes the core on games where arbitrary coalitions are prohibited. From the perspective of computer science, Shehory and Klaus [41] and Rahwan and Jennings [29] examine a situation where the size of possible coalitions is limited. Ramchurn et al. [35] consider spatial and temporal constraints for the coalition formation problem of emergency responders and robots. Meir et al. [21] restrict a coalition where agents are not connected on a graph. Rahwan et al. [31] propose a very general framework for constrained coalition formation and develop an algorithm for the CSG problems. This paper considers a special case called locally constrained games in their framework.
      </paragraph>
      <paragraph>
       To make a coalition structure stable, agents need to agree how to divide among themselves the reward obtained by the coalition structure. Aumann and Dreze [2] extend the core [13] when agents form a coalition structure. Assuming the number of possible coalitions is a constant, and the value of the grand coalition (or the value of an optimal coalition structure) is known, checking core-non-emptiness is easy, since the problem is reduced to a linear programming problem (see e.g., Osborne and Rubinstein [27]). However, when the value of the grand coalition (or the value of an optimal coalition structure) is not explicitly given, the problem is NP-complete{sup:1} even if we assume the number of possible coalitions is a constant [8].
      </paragraph>
      <paragraph>
       Since the core can be empty, in traditional models of coalitional game theory, several relaxed solution concepts have been proposed, e.g., strong or weak ε-core [40]. Based on the idea of the weak ε-core, we develop a new solution concept called weak ε-core{sup:+}, in which the efficiency condition is also relaxed by parameter ε. This idea is similar to the cost of stability, which is the minimal amount of money provided by an outside source to make the coalition structure stable [4]. We will discuss this point in Section 6.3.
      </paragraph>
      <paragraph>
       Another line of popular research topic in AI and MAS is compact representation schemes for a characteristic function [8], [16]. By naively representing a characteristic function as a table, we need to describe {a mathematical formula}2n entries. A compact representation scheme tries to reduce the representation size of a characteristic function. In particular, a representation scheme called Synergy Coalition Group (SCG) [8] is closely related to the constrained coalition formation we consider. We will discuss the connection with SCG in Section 6.1.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Model
     </section-title>
     <paragraph>
      We model a coalitional form game with constraints on possible coalitions according to locally constrained coalition form games [31]. Let A be a set of agents, where {a mathematical formula}|A|=n. We assume a characteristic function game, where the value of coalition {a mathematical formula}S⊆A is given by characteristic function {a mathematical formula}v:2A→R. Without loss of generality, we assume {a mathematical formula}∀S⊆A, {a mathematical formula}v(S)≥0 and {a mathematical formula}v(∅)=0. Assume a set of allowed coalitions is given as {a mathematical formula}AC⊆2A. If coalition S is not in AC, we assume the value of {a mathematical formula}v(S) is −∞ (or if all values are positive, setting {a mathematical formula}v(S) to zero works as well).
     </paragraph>
     <paragraph>
      One commonly used assumption about a characteristic function is super-additivity. We say characteristic function v is super-additive if for any two disjoint coalitions {a mathematical formula}S1 and {a mathematical formula}S2, {a mathematical formula}v(S1∪S2)≥v(S1)+v(S2) holds. However, we assume v is not necessarily super-additive. Even if we assume the original v is super-additive, considering AC, it is no longer super-additive.
     </paragraph>
     <paragraph>
      Although Rahwan et al. [31] provide more elaborated compact representations, we use this simple representation of the locally constrained game since we require that all possible allowed coalitions, i.e., AC, are explicitly represented in order to develop an efficient algorithm for checking core-non-emptiness. A similar model is used [8] to compactly represent a standard super-additive characteristic function. We assume the number of these allowed coalitions is relatively small.
     </paragraph>
     <paragraph label="Definition 1">
      Coalition structureCoalition structure {a mathematical formula}CSS of agents S is a partition of S into disjoint and exhaustive coalitions, where {a mathematical formula}CSS={S1,S2,…} satisfies the following conditions: {a mathematical formula}∀i,Si∈AC, {a mathematical formula}∀i,j(i≠j),Si∩Sj=∅, and {a mathematical formula}⋃Si∈CSSSi=S.
     </paragraph>
     <paragraph>
      We also assume every singleton coalition is allowed so that at least one {a mathematical formula}CSS, i.e., the singleton coalition structure, exists. Otherwise, no coalition structure {a mathematical formula}CSS may exist. The value of coalition structure {a mathematical formula}CSS, denoted as {a mathematical formula}V(CSS), is given by: {a mathematical formula}V(CSS)=∑Si∈CSSv(Si). The optimal coalition structure {a mathematical formula}CS⁎ is a coalition structure of all agents A satisfying the following condition: {a mathematical formula}∀CSA,V(CS⁎)≥V(CSA).
     </paragraph>
     <paragraph label="Example 1">
      Consider a coalitional game with four agents {a mathematical formula}A={a,b,c,d}. Assume that all possible coalitions are allowed. The characteristic function is given by{a mathematical formula} In this case, the optimal coalition structures {a mathematical formula}CS⁎ are {a mathematical formula}{{a,b,c},{d}}, {a mathematical formula}{{a,b,d},{c}}, and so on. The payoff {a mathematical formula}V(CS⁎) is 10.
     </paragraph>
     <paragraph>
      When agents create a coalition structure, we need to consider its stability. The concept of the core can be extended to cases where agents create an optimal coalition structure [2]. Let {a mathematical formula}y=(y1,y2,…,yn), where {a mathematical formula}yi≥0, be a payoff vector; each {a mathematical formula}yi represents the reward given to agent i. We say payoff vector y is feasible if {a mathematical formula}∑i∈Ayi≤V(CSA) holds. We also say payoff vector y is efficient if {a mathematical formula}∑i∈Ayi=V(CSA) holds. If payoff vector y is efficient, then y is feasible, but not vice versa.
     </paragraph>
     <paragraph>
      The core [13] is a prominent solution concept in coalitional game theory. Aumann and Dreze [2] extend the concept for considering coalition structures. In this paper, we extend their definition for our coalitional form game.
     </paragraph>
     <paragraph label="Definition 2">
      Core for coalition structureThe core for coalition structure {a mathematical formula}CSA of all agents A is the set of payoff vectors, where each element (denoted as y) satisfies the following two conditions:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}∀S∈AC,∑i∈Syi≥v(S) (non-blocking condition),
      </list-item>
      <list-item label="•">
       {a mathematical formula}∑i∈Ayi=V(CSA) (efficiency condition).
      </list-item>
     </list>
     <paragraph>
      The core is non-empty only for the optimal coalition structure {a mathematical formula}CS⁎ for standard coalitional games [2], i.e., AC contains all possible coalitions. Also, from the definition, there should be no monetary transfers (side payments) across different coalitions, even if such transfers are not prohibited. Thus, we concentrate on finding the core for optimal coalition structure {a mathematical formula}CS⁎.
     </paragraph>
     <paragraph label="Example 2">
      Let us consider the same example in Example 1. The core for the optimal coalition structure is non-empty. For instance, a payoff vector {a mathematical formula}y=(3,3,2,2) is in the core.
     </paragraph>
     <paragraph>
      Definition 2 requires that an efficient payoff vector should not be blocked by any coalition in AC. However, one might think that a set of agents S, which is not in AC, creates its own coalition structure {a mathematical formula}CSS. Such S can be a blocking coalition structure if {a mathematical formula}V(CSS) exceeds the sum of their payoffs. Nevertheless, Conitzer and Sandholm [8] show that this is not possible.{sup:2}
     </paragraph>
     <paragraph label="Proposition 1">
      Lemma 2 in [8]For payoff vector y, if for all{a mathematical formula}S∈AC,{a mathematical formula}∑i∈Syi≥v(S)holds, then for all{a mathematical formula}S′⊆A, where{a mathematical formula}S′∉AC,{a mathematical formula}∑i∈S′yi≥V(CSS′)also holds, where{a mathematical formula}CSS′is any coalition structure of{a mathematical formula}S′.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Core-non-emptiness
     </section-title>
     <section label="3.1">
      <section-title>
       Traditional method
      </section-title>
      <paragraph>
       We are going to present CoreP, which is based on existing techniques [8], [25]. First, it finds the value of optimal coalition structure {a mathematical formula}V(CS⁎) by solving the following IP problem. Ohta et al. [25] showed that this simple IP-based method is competitive against the state-of-the-art coalition structure generation techniques. Also, when we deal with locally constrained games, we cannot directly apply the elaborated techniques [31], since their algorithm utilizes their own complicated representation structure.
      </paragraph>
      <paragraph label="Definition 3">
       IP-PRIMAL: IP for finding the {a mathematical formula}CS⁎ value{a mathematical formula} Here, {a mathematical formula}xj is a decision variable for coalition {a mathematical formula}Sj where {a mathematical formula}j∈[1,|AC|]. If {a mathematical formula}Sj is included in {a mathematical formula}CS⁎, {a mathematical formula}xj is 1, otherwise, {a mathematical formula}xj is 0. Strictly speaking, there is a chance that the obtained coalition structure does not contain all of the agents. However, since we assume the value of a coalition is non-negative, if agent i is not included in the obtained coalition structure, we can add a coalition {a mathematical formula}{i} without reducing the value of the coalition structure. When the size of AC is large, we cannot find an optimal solution of the above IP in a reasonable amount of time even with the state-of-the-art optimization package, e.g., CPLEX.
      </paragraph>
      <paragraph>
       Second, CoreP gives a payoff vector in the core by the following LP problem [8].
      </paragraph>
      <paragraph label="Definition 4">
       LP-CNE: LP for checking core-non-emptiness{a mathematical formula}
      </paragraph>
      <paragraph>
       In summary, CoreP, which returns one payoff vector in the core if it is non-empty, is described as follows.
      </paragraph>
      <paragraph>
       AlgorithmCoreP
      </paragraph>
      <list>
       <list-item label="1.">
        Solve IP-PRIMAL to obtain the value of optimal coalition structure {a mathematical formula}V(CS⁎).
       </list-item>
       <list-item label="2.">
        Check whether there exists payoff vector y that satisfies the efficiency and non-blocking conditions by solving LP-CNE with {a mathematical formula}V(CS⁎).
       </list-item>
       <list-item label="3.">
        If such a y exists, return it as an element of the core. Otherwise, report that the core is empty.
       </list-item>
      </list>
     </section>
     <section label="3.2">
      <section-title>
       Our method
      </section-title>
      <paragraph>
       Let us consider the linear relaxation of IP-PRIMAL and its dual problem.
      </paragraph>
      <paragraph label="Definition 5">
       LP-PRIMAL: LP relaxation of IP-PRIMAL{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 6">
       LP-DUAL: Dual problem{a mathematical formula}
      </paragraph>
      <paragraph>
       Before constructing our algorithm, let us define one more decision problem called IP-EFF. Our algorithm effectively bridges solution {a mathematical formula}∑iyi denoted as {a mathematical formula}V⁎ to a decision problem that checks whether the {a mathematical formula}CS⁎ value {a mathematical formula}V(CS⁎) is equal to {a mathematical formula}V⁎.
      </paragraph>
      <paragraph label="Definition 7">
       IP-EFF: IP for checking the efficiency condition{a mathematical formula}
      </paragraph>
      <paragraph>
       Now, we are ready to construct CoreD, our newly developed algorithm, that utilizes LP-DUAL and IP-EFF. Note that a similar idea is applied for finding an approximate solution of the winner determination problem in combinatorial auctions [24].
      </paragraph>
      <paragraph>
       AlgorithmCoreD
      </paragraph>
      <list>
       <list-item label="1.">
        Solve LP-DUAL to obtain dual solution {a mathematical formula}y⁎.
       </list-item>
       <list-item label="2.">
        Check whether {a mathematical formula}y⁎ satisfies the efficiency condition by solving IP-EFF with {a mathematical formula}V⁎=∑i∈Ayi⁎.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}y⁎ satisfies it, return {a mathematical formula}y⁎ as an element of the core. Otherwise, report that the core is empty.
       </list-item>
      </list>
      <paragraph>
       When {a mathematical formula}V(CS⁎) is equal to the lower bound {a mathematical formula}V⁎ obtained from LP-DUAL, there exists an integer solution for LP-PRIMAL, that is, the optimal value of the linear relaxation happens to be identical to the original IP problem. When {a mathematical formula}V(CS⁎) is smaller than {a mathematical formula}V⁎, the core is empty. Then the difference between {a mathematical formula}V⁎ and {a mathematical formula}V(CS⁎) is called the cost of stability[4], which will be discussed in Section 6.3.
      </paragraph>
      <paragraph label="Theorem 1">
       Algorithm CoreD is correct; if it returns{a mathematical formula}y⁎,{a mathematical formula}y⁎is in the core, and if it reports that the core is empty, the core is empty.
      </paragraph>
      <paragraph label="Proof">
       If CoreD returns {a mathematical formula}y⁎, from Definition 6, {a mathematical formula}y⁎ satisfies the non-blocking condition for all {a mathematical formula}S∈AC. Also, from Definition 7, {a mathematical formula}y⁎ satisfies the efficiency condition. Thus, {a mathematical formula}y⁎ is in the core.If CoreD reports that the core is empty, IP-EFF does not have a solution. Let {a mathematical formula}x⁎=(x1⁎,x2⁎,…) be the optimal solution of LP-PRIMAL and {a mathematical formula}y⁎=(y1⁎,…,yn⁎) be the optimal solution of LP-DUAL. From the strong duality principle, the solutions of these problems must be identical, i.e., {a mathematical formula}∑Sj∈ACxj⁎⋅v(Sj)=∑i∈Ayi⁎=V⁎ holds. Since LP-PRIMAL is a linear relaxation of IP-PRIMAL, its optimal value cannot exceed {a mathematical formula}V⁎.Here, {a mathematical formula}y⁎ is a payoff vector, which satisfies the non-blocking condition, but it might not satisfy the efficiency condition, and the sum of its elements is minimized. If IP-EFF does not have a solution, then IP-PRIMAL does not have a solution whose value is better than or equal to {a mathematical formula}V⁎. Thus, there exists no payoff vector that simultaneously satisfies the efficiency and non-blocking conditions. Thus, the core is empty.  □
      </paragraph>
      <paragraph>
       CoreD first solves LP-DUAL (the optimization problem) and then solves IP-EFF (the decision problem). On the other hand, CoreP first solves IP-PRIMAL (the optimization problem) and then solves LP-CNE (the decision problem). When the core is non-empty, we expect that the performances of these algorithms are almost equivalent. However, when the core is empty, especially when {a mathematical formula}V(CS⁎) is much smaller than {a mathematical formula}V⁎, we expect that IP-PRIMAL (which finds the optimal value) becomes much harder than IP-EFF (which simply checks whether {a mathematical formula}V(CS⁎) can be equal to {a mathematical formula}V⁎). We empirically confirm these expectations in Section 5. Furthermore, for a class of games where the optimal coalition structure can be found in polynomial time [6], [3], [42], [5], we expect that the performance of CoreP and CoreD would improve as much as IP-PRIMAL and IP-EFF, which become done in polynomial time, save the runtime. Thus, the average difference of the performance does not change so much, though both algorithms improve much.
      </paragraph>
     </section>
    </section>
    <section label="4">
     Weak ε-core{sup:+}
     <paragraph>
      Since the core can be empty, in the traditional model of coalitional game theory, several solution concepts that relax the non-blocking condition are proposed based on the core. Representative solution concepts based on the core are the strong and the weak ε-core [40]. The former minimizes the total excess of each coalition, while the latter minimizes the average one. Although we can extend both concepts for a coalition structure in general,{sup:3} with our model of locally constrained games, we cannot guarantee the property similar to Proposition 1 with respect to the strong ε-core. Accordingly, we concentrate on the weak ε-core to utilize the idea of CoreD.
     </paragraph>
     <paragraph>
      Let us remark another important issue before introducing the weak ε-core and proposing our new solution concept. To define a feasible or allowed payoff vector with a coalition structure, we need to consider whether monetary transfers (side payments) across different coalitions are possible or not. We did not need to consider this issue for the core, since, from the non-blocking condition, no monetary transfers among coalitions are possible. However, if we relax the non-blocking condition, allowing monetary transfers among coalitions extends the space of the feasible payoff vectors. We thus concentrate on the case where transfers among coalitions are possible.{sup:4}
     </paragraph>
     <paragraph>
      This assumption can be considered fairer in some case. Consider the problem of assigning managers to departments and a very talented manager, who is as successful as the managers in any other department. Also, assume she is the only person who can reduce the deficit of one particular department. Then, assigning her to that department will maximize the total profit of the company. In this case, it is clearly unfair to withhold her bonus just because her department shows a deficit. That being said, the case where such transfers are not possible is more computationally challenging. We will revisit this topic in Section 6.2.
     </paragraph>
     <paragraph>
      Now we are ready to introduce average excess and the weak ε-core.
     </paragraph>
     <paragraph label="Definition 8">
      Average excessFor coalition S and payoff vector y, let {a mathematical formula}d(y,S) be the average excess of coalition S defined as follows:{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 9">
      Weak ε-coreThe weak ε-core for {a mathematical formula}CSA is the set of payoff vectors, where each element (denoted as y) satisfies the following two conditions:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}∀S∈AC,d(y,S)≤ε (relaxed non-blocking condition),
      </list-item>
      <list-item label="•">
       {a mathematical formula}∑i∈Ayi=V(CSA) (efficiency condition).
      </list-item>
     </list>
     <paragraph>
      From this definition, it is clear that if the weak ε-core is non-empty for one coalition structure {a mathematical formula}CSA, it is also non-empty for the optimal coalition structure {a mathematical formula}CS⁎. Similar to the core, we can show that there will be no blocking coalition structure, and the following theorem holds:
     </paragraph>
     <paragraph label="Theorem 2">
      If payoff vector y satisfies{a mathematical formula}d(y,S)≤εfor all{a mathematical formula}S∈AC, then{a mathematical formula}V(CSS′)−∑i∈S′yi|S′|≤εholds, for all{a mathematical formula}S′∉ACand its arbitrary coalition structure{a mathematical formula}CSS′.
     </paragraph>
     <paragraph label="Proof">
      From the definition of a coalition structure, {a mathematical formula}CSS′={S1,…,Sk}, where each {a mathematical formula}Sj∈AC is non-overlapping, {a mathematical formula}⋃Si∈CSS′Sj=S′, and {a mathematical formula}V(CSS′)=v(S1)+v(S2)+…+v(Sk) holds. Also, from the assumption,{a mathematical formula} holds for all {a mathematical formula}Sj. This means {a mathematical formula}v(Sj)−∑i∈Sjyi≤ε⋅|Sj|. Then,{a mathematical formula}  □ Intuitively, this theorem holds in conjunction with Proposition 1 because the worth of any coalition is scaled proportionally to its size by a factor ε.
     </paragraph>
     <paragraph>
      The weak ε-core for the optimal coalition structure {a mathematical formula}CS⁎ requires that the payoff vector be efficient. To find an efficient payoff vector, we need to know the exact value of {a mathematical formula}V(CS⁎). Since finding its exact value is NP-hard, it is natural to utilize an approximate, semi-optimal solution against the weak ε-core for {a mathematical formula}CS⁎. We introduce a new solution concept called the weak ε-core{sup:+}, which can be obtained by an approximate value of {a mathematical formula}V(CS⁎), and define it as follows.
     </paragraph>
     <paragraph label="Definition 10">
      Weak {a mathematical formula}ε-core+The weak ε-core{sup:+} is a set of payoff vectors, where each element (denoted as y) satisfies the following two conditions:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}∀S∈AC,d(y,S)≤ε (relaxed non-blocking condition),
      </list-item>
      <list-item label="•">
       {a mathematical formula}∑i∈Ayi≤V(CS⁎) (relaxed efficiency condition).
      </list-item>
     </list>
     <paragraph>
      We relax the efficiency condition so that {a mathematical formula}∑i∈Ayi can be less than {a mathematical formula}V(CS⁎). The condition implies that the weak ε-core{sup:+} is not directly linked with a particular coalition structure. The existing solution concepts, along with the model of Aumann and Dreze [2], require the agents to agree with a coalition structure that they form beforehand. However, the weak ε-core{sup:+} does not explicitly specify a coalition structure from the fact that computing the optimal coalition structure is NP-hard. Furthermore, this definition indicates that the difference between {a mathematical formula}V(CS⁎) and {a mathematical formula}∑i∈Ayi must be {a mathematical formula}n⋅ε at maximum by the relaxed non-blocking condition. We will discuss more when we introduce an algorithm for this approximate solution concept. It is clear that for any {a mathematical formula}ε′≤ε, the weak ε-core{sup:+} is a superset of the weak {a mathematical formula}ε′-core{sup:+} and is a superset of the weak ε-core as long as ε is non-negative (the weak ε-core{sup:+} becomes empty for {a mathematical formula}ε&lt;0). Thus, if the weak ε-core is non-empty, the weak ε-core{sup:+} is also non-empty. The converse is also true:
     </paragraph>
     <paragraph label="Theorem 3">
      If the weak ε-coreis non-empty, there exists a coalition structure{a mathematical formula}CSAwhere the weak ε-core for{a mathematical formula}CSAis non-empty.
     </paragraph>
     <paragraph label="Proof">
      It is sufficient to show that if the weak ε-core{sup:+} is non-empty, the weak ε-core for the optimal coalition structure {a mathematical formula}CS⁎ is non-empty. Assume the weak ε-core{sup:+} is non-empty. Thus, we can choose one element y in it. If {a mathematical formula}∑i∈Ayi=V(CS⁎), then y is also an element of the weak ε-core for {a mathematical formula}CS⁎. Otherwise, choose σ as {a mathematical formula}V(CS⁎)−∑i∈Ayi. Here, {a mathematical formula}σ&gt;0 holds. From y and σ, create another payoff vector {a mathematical formula}y′, such that {a mathematical formula}yi′=yi+σ/n. Then, {a mathematical formula}∑i∈Ayi′=V(CS⁎) holds. Also, for each {a mathematical formula}S∈AC, the following condition holds.{a mathematical formula} Thus, {a mathematical formula}y′ is in the weak ε-core for {a mathematical formula}CS⁎; it is non-empty.  □
     </paragraph>
     <paragraph>
      Notice that this theorem implies that there may exist a non-optimal coalition structure {a mathematical formula}CSA with {a mathematical formula}∑i∈Ayi≤V(CSA) and the weak ε-core for such a coalition structure {a mathematical formula}CSA is non-empty.
     </paragraph>
     <paragraph label="Example 3">
      Let there be three agents, a, b, and c, and let{a mathematical formula} where {a mathematical formula}v({a})=v({b})=v({c})=0, {a mathematical formula}v({a,b})=v({b,c})=v({a,c})=12. Optimal coalition structure {a mathematical formula}CS⁎ is {a mathematical formula}{{a,b},{c}}, {a mathematical formula}{{a},{b,c}}, or {a mathematical formula}{{a,c},{b}} and value {a mathematical formula}V(CS⁎) is 12. The core for the coalition structure of this game is empty because the coalition structure can not sufficiently provide enough value to make the payoff vector stable. At least one agent always has some excess as long as the coalition of the remaining two agents receives enough payoff so that it has no excess.Fig. 1 illustrates the weak 3-core{sup:+} of this game. For the given {a mathematical formula}ε=3, choose {a mathematical formula}ε′≤ε and relax the efficiency condition: {a mathematical formula}∑i∈Ayi+n⋅ε′=V(CS⁎). When {a mathematical formula}ε′=0, the weak 3-core{sup:+} becomes identical to the weak 3-core for {a mathematical formula}CS⁎. When coalition structure value {a mathematical formula}V(CS⁎)=12, the linear programming problem for the weak 3-core({sup:+}) is given by{a mathematical formula} By solving this problem, each agent obtains a payoff of at most 6, and the sum does not exceed 12: {a mathematical formula}y=(6,6,0), {a mathematical formula}y=(6,0,6), or {a mathematical formula}y=(0,6,6). Some coalitions with two agents have an average excess of at most 3. Alternatively, {a mathematical formula}y=(4,4,4) is in the weak 3-core{sup:+} and the weak 3-core for {a mathematical formula}CS⁎. The region of the payoff vector is represented by the smaller shaded triangle in the larger triangle in the leftmost of Fig. 1. Here, the height of the larger triangle is equal to {a mathematical formula}V(CS⁎). Each point therein represents an efficient payoff vector.When {a mathematical formula}ε′=2/3, the coalition structure value is reduced to 10. The weak 3-core{sup:+} is equivalent to the weak 3-core with total payoffs of 10. We compute the payoff vector with {a mathematical formula}∑i∈Ayi=V(CS⁎)−n⋅ε′=10, which is illustrated by the height of the larger triangle in the middle of Fig. 1. Each agent obtains a payoff of at most 6, and the sum does not exceed 10. Total payoff 10 is exactly shared. The region is represented by the smaller shaded triangle in the larger triangle. {a mathematical formula}y=(10/3,10/3,10/3) is in the weak 3-core{sup:+}. Here if we equally distribute the sacrificed amount of efficiency to the agents, we obtain {a mathematical formula}(4,4,4), which is in the weak 3-core.Finally, let us further relax the efficiency condition up to {a mathematical formula}ε′=1. Now we sacrifice the efficiency of 3 and the height of the larger triangle in the rightmost of Fig. 1 is 9. In this case, the payoff vector in the weak 3-core{sup:+} is uniquely determined as {a mathematical formula}(3,3,3).In summary, the weak 3-core{sup:+} is represented as a shaded triangular prism in Fig. 1. The payoff vector belongs to each cross section of the triangular prism, which corresponds to the case with {a mathematical formula}0&lt;ε′&lt;3.
     </paragraph>
     <paragraph>
      To show an algorithm that checks the weak ε-core{sup:+}-non-emptiness for any given ε, let us introduce two mathematical programming algorithms.
     </paragraph>
     <paragraph label="Definition 11">
      Dual problem with the relaxed non-blocking condition{a mathematical formula}
     </paragraph>
     <paragraph label="Definition 12">
      IP for checking the relaxed efficiency condition{a mathematical formula}
     </paragraph>
     <paragraph>
      Definition 11, Definition 12 are constructed by slightly modifying Definition 6, Definition 7. With them, we introduce the following algorithm.
     </paragraph>
     <paragraph>
      Algorithm{a mathematical formula}ECore+(ε)
     </paragraph>
     <list>
      <list-item label="1.">
       Solve the dual LP problem in Definition 11 for ε to obtain dual solution {a mathematical formula}y⁎ and {a mathematical formula}V⁎=∑i∈Ayi⁎.
      </list-item>
      <list-item label="2.">
       Check whether {a mathematical formula}y⁎ satisfies the feasibility condition ({a mathematical formula}V⁎≤V(CS⁎)) by solving the IP problem in Definition 12 for ε.
      </list-item>
      <list-item label="3.">
       If {a mathematical formula}y⁎ satisfies the relaxed efficiency condition, return {a mathematical formula}y⁎ as an element of the weak ε-core{sup:+}. Otherwise, report that the weak ε-core{sup:+} is empty.
      </list-item>
     </list>
     <paragraph>
      If the algorithm reports a payoff vector {a mathematical formula}y⁎, the IP problem in Definition 12 also returns a particular coalition structure {a mathematical formula}CSA. Notice here that {a mathematical formula}∑i∈Ayi⁎ is not always equal to the reward that {a mathematical formula}CSA provides. {a mathematical formula}V(CSA) is just guaranteed to be larger than or equal to {a mathematical formula}∑i∈Ayi⁎. Thus, the weak ε-core{sup:+} does not always choose the payoff vector which is equivalent to the weak ε-core for {a mathematical formula}CSA. A slight modification can improve the efficiency of the weak ε-core{sup:+}. More precisely, by uniformly distributing the difference between the resulting coalition structure value {a mathematical formula}V(CSA) and {a mathematical formula}∑i∈Ayi⁎ to the agents, we can obtain the weak ε-core for {a mathematical formula}CSA.
     </paragraph>
     <paragraph label="Theorem 4">
      Algorithm{a mathematical formula}ECore+(ε)is correct; if it returns{a mathematical formula}y⁎,{a mathematical formula}y⁎is in the weak ε-core, and if it reports the weak ε-coreis empty, the weak ε-coreis empty.
     </paragraph>
     <paragraph label="Proof">
      The proof is basically similar to that of Theorem 1. The only additional issue is to show that {a mathematical formula}V(CS⁎)−n⋅ε≤∑i∈Ayi holds. If the set of agents A has a unique optimal coalition structure, it implies that {a mathematical formula}A∈AC. Thus, this fact is derived from the constraint in Definition 11. Otherwise, it is done from Theorem 2.  □
     </paragraph>
     <paragraph>
      Notice that we can use a simple modification of CoreP for checking the non-emptiness of the weak ε-core{sup:+}. In this case, the algorithm first finds {a mathematical formula}V(CS⁎) and then payoff vector y that satisfies the relaxed non-blocking and efficiency conditions. However, regardless of the value of ε, it needs to find {a mathematical formula}V(CS⁎), and thus its runtime would become too long when the number of elements in AC becomes large.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Evaluation
     </section-title>
     <section label="5.1">
      <section-title>
       Settings
      </section-title>
      <paragraph>
       We experimentally evaluate our proposed algorithms. All of the tests were run on a Core i7-4770 processor with 16 GB RAM. The test machine runs Windows 7 Professional SP1 x64 Edition. We used CPLEX 12.6 for solving the linear or integer programming problem instances.
      </paragraph>
      <paragraph>
       To understand the features of our algorithms, we concentrate on three simple and typical cases that is likely to be observed in practice: (i) AC tends to include small coalitions; (ii) AC tends to include large coalitions; and (iii) there is no bias on the size of each coalition in AC. Unfortunately, there exist no widely accepted standard benchmark instances for locally constrained games. We borrowed the way to generate instances [25]. To generate problem instances, we chose one of three distributions, decay, normal, and uniform, and determine the size of each coalition in AC according to the chosen distribution.{sup:5} The instances made by using the decay distribution capture case (i). The normal distribution corresponds to case (ii), and the uniform distribution corresponds to case (iii). We believe that any of them are quite likely to occur in practical situations. Considering them is useful to deepen understanding of the features of our proposed technique, though we admit that this classification is slightly rough.
      </paragraph>
      <paragraph>
       Let us further explain how we construct the instances for each case. For case (i), using the decay distribution we create coalitions included in AC. Create a coalition with one randomly chosen agent. Then repeatedly add a new random agent with probability α until an agent is not added or the coalition includes all the agents, where {a mathematical formula}α=0.55. Then we choose value {a mathematical formula}v(S) from uniform distribution {a mathematical formula}(0,|S|×10]. For case (ii), we fix the mean and the variance of the normal distribution to 900 and 50{sup:2}. The size of a coalition {a mathematical formula}|S| is drawn from {a mathematical formula}N(μ,σ2), then we randomly add agents to a coalition so that the number of agents who belong to each coalition is equals to {a mathematical formula}|S|. For case (iii), we use the uniform distribution so that {a mathematical formula}|S| is consistent with the uniform distribution of {a mathematical formula}[1,n]. Notice that for any of the distributions, the value of each coalition is drawn from uniform distribution {a mathematical formula}(0,|S|×10]. We generate 100 problem instances and calculate the geometric average of these problem instances.
      </paragraph>
     </section>
     <section label="5.2">
      CoreD and CoreP
      <paragraph>
       Fig. 2 compares the runtime of algorithm CoreD with CoreP for each distribution. Each data point represents the geometric average of 100 problem instances (left y-axis) and also shows the ratio of instances where the core is non-empty (right y-axis). In these experiments, we set {a mathematical formula}#agents=1000 and vary the number of elements in AC, i.e., {a mathematical formula}|AC| from 1000 to 10 000 (the x-axis).
      </paragraph>
      <paragraph>
       First, in Fig. 2a the ratio decreases rapidly. In fact, when the number of elements in AC exceeds 3000, in the generated instances, the core is always empty. Let us examine the average runtimes of CoreD and CoreP for problem instances where the core is empty or non-empty for the decay distribution. When the core is empty (denoted as {a mathematical formula}CoreD(E) and {a mathematical formula}CoreP(E)), CoreD is by far superior to CoreP. CoreD can check core-non-emptiness within 10{sup:4} msec even when {a mathematical formula}|AC|=10000, while the runtime of CoreP increases very rapidly as {a mathematical formula}|AC| increases. As a result, CoreP cannot check core-non-emptiness within 10{sup:6} msec when {a mathematical formula}|AC| exceeds 5000. On the other hand, when the core is non-empty (denoted as {a mathematical formula}CoreD(N) and {a mathematical formula}CoreP(N)), the average runtimes of CoreD and CoreP are almost equivalent. For randomly generated problem instances, the core is always empty when {a mathematical formula}|AC|&gt;3000. We artificially created problem instances so that the core is non-empty for large {a mathematical formula}|AC|, and confirmed that the average runtimes of CoreD and CoreP are almost equivalent for these problem instances. Notice that we also investigate the normal distributions of {a mathematical formula}N(100,502) and {a mathematical formula}N(500,502) as similar cases to the decay distribution where the size of the coalitions in AC is relatively small. In this case, we confirm almost the same tendency as the decay distribution, except that the core is always empty and these runtimes are basically longer regardless of the number of allowed coalitions.
      </paragraph>
      <paragraph>
       Next, Figs. 2b and 2c illustrate the results for normal distribution {a mathematical formula}N(900,502) and the uniform distribution, which are substantially different from the first distribution. In the instances, the core is almost non-empty regardless of the number of allowed coalitions for both distributions and these runtimes are much larger than the decay distribution. As we see in the decay distribution when the core is non-empty, the average runtimes of CoreD are almost equivalent to those of CoreP. When {a mathematical formula}|AC|&gt;5000 for the normal distribution, CoreD is slightly worse than CoreP. This may be because the LP-DUAL part requires more time as {a mathematical formula}|AC| increases, while IP-EFF remains as hard as IP-PRIMAL. Here we are not able to extract results when the core is empty, because we have very few instances when it is empty.
      </paragraph>
      <paragraph>
       In summary, when the core is non-empty, the average runtimes of CoreD and CoreP are almost equivalent for any distribution. When the core is empty, the average runtimes of CoreD significantly outperform CoreP for the decay distribution. This suggests that when the core is empty, IP-PRIMAL, which computes the optimal solution of {a mathematical formula}V(CS⁎) in CoreP, is much harder to solve than IP-EFF, which decides whether {a mathematical formula}V(CS⁎) is equal to {a mathematical formula}V⁎ or not in CoreD.
      </paragraph>
      <paragraph>
       So far, we have illustrated the runtimes of CoreD and CoreP by varying the number of allowed coalitions and the probability distribution over their sizes. Let us next focus on the runtime relation between how “unstable” the game is and how much time is saved when moving from CoreP to CoreD. There are several ways to measure the stability level of a game instance. We consider the least core value, which is the minimal value of ε such that the (weak) ε-core is non-empty [20]. As we already confirmed, in almost all instances for the normal and uniform distributions, the core is non-empty. We focus on the decay distribution where the core is empty and compute the least core value. We obtained 440 of {a mathematical formula}100×10 instances such that we could compute the least value within 10{sup:5} msec. If the size of AC exceeds 5000, we obtain no exact solution within the time limit. Otherwise, we could successfully obtain the exact least values except when {a mathematical formula}|AC| is 1000 or 2000, for which we could solve 45/100 and 95/100 instances, respectively. Fig. 3 scatters the runtime ratios of CoreD against CoreP in the least core value. It is clear that as the least core value is larger, CoreD is significantly better. If that value exceeds 0.05, CoreD is approximately twice as fast as CoreP. In contrast, when the least value is small, the runtime fluctuates within wide ranges, i.e., for some instances CoreD still performs well, and vice versa.
      </paragraph>
     </section>
     <section label="5.3">
      {a mathematical formula}ECore+(ε)
      <paragraph>
       Next, Fig. 4 investigates the runtime for {a mathematical formula}ECore+(ε) by varying ε and examines the ratio of instances where the weak ε-core{sup:+} is non-empty. The x-axis indicates the value of ε, and the y-axis on the left and right sides shows the average runtime and the ratio of the instances, respectively. Through this experiment, we set {a mathematical formula}#agents=1000, {a mathematical formula}|AC|=10000 and vary ε from 0.01 to 10. We set the time limit to 10{sup:5} msec; if the runtime of {a mathematical formula}ECore+(ε) exceeds this time limit, we terminate the algorithm and exclude this problem instance when calculating the average runtimes and the ratios for this ε. As described below, the algorithm is terminated only when ε is slightly less than 0.1 for the decay distribution.
      </paragraph>
      <paragraph>
       In general, when the core is empty, and if we make ε sufficiently large, the weak ε-core{sup:+} will eventually become non-empty. {a mathematical formula}ECore+(ε) exhibits an easy–hard–easy transition for the runtime by increasing ε for the decay distribution in Fig. 4a and shows that the hardest region lies between 0.05 and 0.1. For the decay distribution, the runtime of {a mathematical formula}ECore+(ε) exceeds the time limit only when the values of ε are 0.05 (100%) and 0.08 (100%), where each number within the parentheses is the ratio of the instances that exceed the time limit. This is the only such case across this experiment. On the other hand, the simple modification of CoreP in the previous section cannot solve any problem instances in this setting, since we cannot obtain {a mathematical formula}V(CS⁎) within the time limit of 10{sup:5} msec for any distribution. Let us turn to the normal and uniform distributions depicted in Figs. 4b and 4c. The runtime of {a mathematical formula}ECore+(ε) hardly changes varying ε up to 1. When ε exceeds 1, the runtime gradually becomes faster and faster. Note that the weak ε-core{sup:+} is always non-empty for each ε.
      </paragraph>
      <paragraph>
       From these results, especially for the decay distribution, we expect that there exist three regions: (i) {a mathematical formula}0≤ε≤εl, where {a mathematical formula}ECore+(ε) can efficiently check that the ε-core{sup:+} is empty, (ii) {a mathematical formula}εl&lt;ε&lt;εr, where {a mathematical formula}ECore+(ε) does not terminate within a reasonable amount of time, and (iii) {a mathematical formula}εr≤ε, where {a mathematical formula}ECore+(ε) can efficiently check that the ε-core{sup:+} is non-empty. Ideally, we hope to identify value {a mathematical formula}ε⁎, s.t., the weak ε-core{sup:+} is non-empty for any {a mathematical formula}ε≥ε⁎, while for any {a mathematical formula}ε&lt;ε⁎, the weak ε-core{sup:+} is empty. However, such {a mathematical formula}ε⁎ lies in region (ii). As a result, identifying {a mathematical formula}ε⁎ is too time-consuming.
      </paragraph>
      <paragraph>
       Alternatively, we can use a standard binary search procedure to identify {a mathematical formula}εl and {a mathematical formula}εr, when {a mathematical formula}εl&lt;ε⁎&lt;εr holds. More specifically, we run {a mathematical formula}ECore+(ε) with a predefined time limit by varying ε. We keep the largest (smallest) value of ε where we found that the weak ε-core{sup:+} is empty (non-empty) as candidates of {a mathematical formula}εl ({a mathematical formula}εr). Also, we keep the smallest and largest values of ε (denoted as {a mathematical formula}cl and {a mathematical formula}cr), where {a mathematical formula}ECore+(ε) did not terminate within the predefined time limit. If the difference between {a mathematical formula}cl and the candidate of {a mathematical formula}εl (as well as the difference between {a mathematical formula}cr and the candidate of {a mathematical formula}εr) becomes smaller than δ, we terminate the procedure and return the current candidates of {a mathematical formula}εl and {a mathematical formula}εr.
      </paragraph>
      <paragraph>
       Fig. 5 shows the runtime of the binary search procedure and its obtained bound {a mathematical formula}εr−εl by varying precision δ. We set the time limit of each run of {a mathematical formula}ECore+(ε) to half a minute, i.e., 30 000 msec. The other parameter settings are identical to Fig. 4. For the decay distribution in Fig. 5a, the runtime does not increase very rapidly by decreasing δ. The obtained bound of {a mathematical formula}εr–{a mathematical formula}εl, when δ is large, becomes smaller by decreasing δ, i.e., by increasing the precision, but eventually {a mathematical formula}εr–{a mathematical formula}εl does not change by decreasing δ due to the time limit. In contrast, for the normal and uniform distributions, as we observed so far, the runtime and its bound are almost constant in Figs. 5b and 5c.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Efficiency
      </section-title>
      <paragraph>
       We have empirically shown that {a mathematical formula}ECore+(ε) effectively removed the complexity hurdle of exactly knowing {a mathematical formula}V(CS⁎). However, it must sacrifice the efficiency (social surplus) against the weak ε-core for the optimal coalition structure up to {a mathematical formula}n⋅ε in the worst case. When it is impossible to compute the exact value of the optimal coalition structure, we cannot directly investigate how far from optimal is the sum of payoffs obtained by {a mathematical formula}ECore+(ε). Nevertheless, we can derive a non-optimal coalition structure, compute its value, and obtain the weak ε-core for it. We investigate how much efficiency is achieved in the sum of payoffs obtained by {a mathematical formula}ECore+(ε) and the value of a coalition structure computed in a greedy manner.
      </paragraph>
      <paragraph>
       Let us briefly describe the greedy algorithm. We sort the allowed coalitions in decreasing order by value, check whether a coalition can be utilized one by one according to that order, and obtain a coalition structure and its worth that may not be optimal. The agents form the coalition structure and share the value efficiently so that every coalition S tolerates the excess up to {a mathematical formula}|S|ε. The greedy algorithm guarantees no lower bound with respect to efficiency, while our algorithm bounds efficiency by the difference between the optimal value and {a mathematical formula}n⋅ε. We fix the number of agents and the allowed coalitions to 1000 and {a mathematical formula}10000. In this setting, exactly knowing {a mathematical formula}V(CS⁎) is impossible. When the weak ε-core{sup:+} is non-empty, if the greedy algorithm finds a coalition structure whose value exceeds {a mathematical formula}ECore+(ε), we share the value of the coalition structure so that the payoff vector is in the weak ε-core for the obtained coalition structure. We observe the ratio of the coalition structure value obtained by the greedy algorithm to the sum of payoffs obtained by {a mathematical formula}ECore+(ε) varying with ε.
      </paragraph>
      <paragraph>
       For the decay distribution, for which the core is always empty as shown in Section 5.2. For sufficiently small ε, the weak ε-core{sup:+} chosen by {a mathematical formula}ECore+(ε) outperforms the weak ε-core for the coalition structure chosen by the greedy procedure in terms of the sum of payoffs (efficiency). In fact, when {a mathematical formula}ε=0.1, the average ratio of the greedy algorithm to {a mathematical formula}ECore+(ε) is only about 0.87. As ε increases, the efficiency ratio linearly increases and when ε reaches 1.0, it is about 0.95. For 100 instances of each ε, the weak ε-core{sup:+} is always non-empty. {a mathematical formula}ECore+(ε) significantly outperforms the greedy algorithm. However, it is a case that the coalition structure by the greedy algorithm can earn more than that by {a mathematical formula}ECore+(ε) as the number of agents or the value of ε increases. When ε exceeds one, the ratio also exceeds one. The greedy algorithm achieves better efficiency than {a mathematical formula}ECore+(ε). However, each agent must face relatively high excess.
      </paragraph>
      <paragraph>
       For the normal and uniform distributions, for which the core is always non-empty (except very few instances for the uniform distribution). Note that CoreD finds a payoff vector so that every agent has no excess. In this case, for any ε, the greedy algorithm outperforms {a mathematical formula}ECore+(ε). For the uniform distribution, when {a mathematical formula}ε=0.1, the ratio is 1.01, the ratio linearly increase, and it is 1.11 for {a mathematical formula}ε=1.0. The same trend is observed for the normal distribution. This is because the size of some coalition is relatively larger than the decay distribution. the greedy algorithm can choose some large coalitions with the higher value and can find the coalition structure whose value is larger than the value that the linear relaxation problem finds, though the degree is approximately 1.0% for sufficiently small ε.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Discussions
     </section-title>
     <section label="6.1">
      <section-title>
       Super-additive cover
      </section-title>
      <paragraph>
       Aumann and Dreze [2] presented a conceptual transformation method called super-additive cover, which transforms an original game with a non-super-additive characteristic function, into a new game with a super-additive one. More specifically, for an original characteristic function v and AC, a new super-additive one {a mathematical formula}v¯ is defined as follows.
      </paragraph>
      <list>
       <list-item label="•">
        If {a mathematical formula}S∈AC, {a mathematical formula}v¯(S) is given as {a mathematical formula}v(S).
       </list-item>
       <list-item label="•">
        Otherwise, {a mathematical formula}v¯(S) is given as {a mathematical formula}maxCSS⁡{∑Si∈CSSv(Si)}, where {a mathematical formula}CSS={S1,S2,…} is a partition of S, i.e., all {a mathematical formula}Si are disjoint and {a mathematical formula}⋃Si∈CSSSi =S, and {a mathematical formula}∀Si∈AC.
       </list-item>
      </list>
      <paragraph>
       Based on this conceptual transformation, the optimal coalition structure in the original game {a mathematical formula}CS⁎ is identical to partition {a mathematical formula}CSA, such that {a mathematical formula}v¯(A)=∑Si∈CSAv(Si) holds. Thus, {a mathematical formula}V(CS⁎)=v¯(A) holds. In summary, the problem of finding an optimal coalition structure (and the core for the coalition structure) in the original game, is equivalent to that of finding the value of the grand coalition (and the standard core) in the transformed game. Actually, Conitzer and Sandholm [8] dealt with this transformed game, where the characteristic function is explicitly given only for the elements of AC, which they call the Synergy Coalition Group. Greco et al. [15] introduce a concept called cohesive cover, in which the transformation is applied only for the grand coalition. The result presented in this subsection holds also for cohesive cover.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Monetary transfers among coalitions
      </section-title>
      <paragraph>
       When monetary transfers among coalitions are not allowed and the core is empty, forming an optimal coalition structure is not necessarily best for minimizing ε.
      </paragraph>
      <paragraph label="Example 4">
       Let there be three agents, a, b, and c, and assume {a mathematical formula}v({a,b,c})=v({a,b})=v({b,c})=v({a,c})=30, {a mathematical formula}v({c})=3, and {a mathematical formula}v({a})=v({b})=0. Here, the optimal coalition structure is {a mathematical formula}{{a,b},{c}}. Assume that transfers across coalitions are not allowed and that agents choose payoff vector {a mathematical formula}y=(15,15,3). Coalition {a mathematical formula}S={a,c} will be unsatisfied, since they can obtain 30 if they work together, i.e., {a mathematical formula}v(S)=30, but they obtain only 18. The average excess {a mathematical formula}d(y,S)=v(S)−∑i∈Syi|S| is 6. On the other hand, if the grand coalition is formed (which is not optimal), agents can choose payoff vector {a mathematical formula}y=(10,10,10). Then, any average excess is at most 5. Thus, this sub-optimal coalition structure is better for minimizing ε.
      </paragraph>
      <paragraph>
       When monetary transfers among coalitions are allowed, we can separately solve the following problems (1) finding {a mathematical formula}V(CS⁎), and (2) finding y that satisfies {a mathematical formula}∑i∈Ayi=V(CS⁎) and optimizes some criteria, e.g., minimizing an average excess. On the other hand, when monetary transfers among coalitions are not allowed, we need to find a desirable pair of a coalition structure and a payoff vector.
      </paragraph>
      <paragraph>
       In fact, the following is the mixed integer programming (MIP) formulation:
      </paragraph>
      <paragraph label="Definition 13">
       MIP where monetary transfers are not allowed{a mathematical formula}
      </paragraph>
      <paragraph>
       Given ε, this MIP finds a pair of a coalition structure {a mathematical formula}CSA and a payoff vector y that is in the weak ε-core for {a mathematical formula}CSA. The notations and constraints here are basically borrows from Definition 3, Definition 4. The fourth constraint highlights the assumption that monetary transfers among coalition are not allowed; all the value that a coalition {a mathematical formula}Sj earns must be distributed among its members.
      </paragraph>
      <paragraph>
       It is clear that the MIP in Definition 13 cannot be separated in the same manner that monetary transfers among coalition are allowed. The fourth constraint connects the first constraint that explores a coalition structure with the second and third ones that find an appropriate payoff vector. Also, the MIP must search every coalition structure, including the non-optimal ones, as Example 4 describes. Therefore, when monetary transfers are not allowed, the idea of CoreD is no longer applied. Though developing such an algorithm is admittedly our immediate future work, we need an entirely different technique from the dual solution.
      </paragraph>
      <paragraph>
       Note a case where a given instance has the core for the optimal coalition structure. For such instances, the payoff vector in the core does not change regardless whether monetary transfers among coalitions are allowed [2]. We do not need to transfer the payoffs among coalition to make the payoff vector stable, since each sub-coalition only has non-positive excess.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Cost of stability
      </section-title>
      <paragraph>
       This subsection discusses the connection between the weak ε-core{sup:+} and cost of stability (CoS), which is the minimal amount of money provided by an outside source to make the coalition structure stable [4]. CoS is defined as the difference between the lower bound {a mathematical formula}V⁎ obtained from LP-DUAL and the value {a mathematical formula}V(CS⁎) with an optimal CS. If an outside source, e.g., a government, provides {a mathematical formula}CoS=V⁎−V(CS⁎) when agents form {a mathematical formula}CS⁎, they can divide {a mathematical formula}V(CS⁎)+CoS=V⁎ so that there exists no blocking coalition.
      </paragraph>
      <paragraph label="Definition 14">
       Cost of stabilityFix characteristic function v and the optimal coalition structure {a mathematical formula}CS⁎ The cost of stability CoS is defined as the solution of the following problem:{a mathematical formula}
      </paragraph>
      <paragraph>
       When the core is non-empty, CoS is clearly zero. For the weak ε-core{sup:+} and CoS, the following theorem holds:
      </paragraph>
      <paragraph label="Theorem 5">
       If the weak ε-coreis non-empty,{a mathematical formula}CoS≤n⋅εholds.
      </paragraph>
      <paragraph label="Proof">
       Assume the weak ε-core{sup:+} is non-empty. Then we can choose one element y in the weak ε-core{sup:+}. Next, consider new payoff vector {a mathematical formula}y′ such that {a mathematical formula}yi′=yi+ε. From the definition of the weak ε-core{sup:+}, the following conditions are satisfied.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}v(S)−∑i∈Sy′≤0,∀S∈AC,
       </list-item>
       <list-item label="•">
        {a mathematical formula}V(CS⁎)≤∑i∈Ayi′≤V(CS⁎)+n⋅ε.
       </list-item>
      </list>
      <paragraph>
       We can obtain a lower-bound of ε where the weak ε-core{sup:+} is non-empty based on CoS.
      </paragraph>
      <paragraph label="Theorem 6">
       The weak ε-coreis non-empty for{a mathematical formula}ε=CoS/n.
      </paragraph>
      <paragraph label="Proof">
       From the definition of CoS, there exists y such that {a mathematical formula}∑i∈Ayi=V(CS⁎)+CoS and {a mathematical formula}∀S∈AC,∑i∈Syi≥v(S) hold. That is, y is in the core in the game with {a mathematical formula}v′. Now, consider new payoff vector {a mathematical formula}y′ such that {a mathematical formula}yi′=yi−ε where {a mathematical formula}ε=CoS/n. {a mathematical formula}y′ is in the weak ε-core{sup:+} because {a mathematical formula}∑i∈Ayi′=∑i∈Ayi−n⋅ε=V(CS⁎) and {a mathematical formula}∀S∈AC,d(y,S)≤ε hold. Thus, the weak ε-core{sup:+} is non-empty.  □
      </paragraph>
      <paragraph>
       From these two theorems, we obtain the following theorem.
      </paragraph>
      <paragraph label="Theorem 7">
       Choose{a mathematical formula}ε̲as the least value of ε, where the weak ε-coreis non-empty. Then,{a mathematical formula}ε̲is equal to{a mathematical formula}CoS/n.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Nucleolus
      </section-title>
      <paragraph>
       This subsection discusses the relation between the weak ε-core{sup:+} and the nucleolus [38]. Since the nucleolus always exists and is uniquely determined, we focus on the weak least core [20] for the optimal coalition structure and the weak least {a mathematical formula}core+, i.e., the solution concepts with the least value ε with which they are guaranteed to exist.
      </paragraph>
      <paragraph label="Lemma 1">
       The least value ε of the weak least core for the optimal coalition structure is equivalent to that of the weak least{a mathematical formula}core+.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}ε̲1 and {a mathematical formula}ε̲2 be the least values of the weak least core (for the optimal coalition structure) and the weak least {a mathematical formula}core+. First assume {a mathematical formula}ε̲1&lt;ε̲2. Consider a weak {a mathematical formula}ε′-core{sup:+} with {a mathematical formula}ε′&lt;ε̲2. Then the weak {a mathematical formula}ε′-core{sup:+} must be empty. From the assumption, the weak {a mathematical formula}ε̲1-core must be empty. However, from its definition, since the weak {a mathematical formula}ε̲1-core is a superset of the weak {a mathematical formula}ε̲1-core{sup:+}, it must be non-empty. This contradicts that the weak {a mathematical formula}ε̲1-core{sup:+} with {a mathematical formula}ε̲1&lt;ε̲2 is empty.Next, assume {a mathematical formula}ε̲1&gt;ε̲2. Consider a weak {a mathematical formula}ε′-core (not -core{sup:+}) with {a mathematical formula}ε′&lt;ε̲1. From the assumption, the weak {a mathematical formula}ε̲2-core must be empty. However, since the weak {a mathematical formula}ε̲2-core{sup:+} is non-empty, Theorem 3 derives that the weak {a mathematical formula}ε̲2-core must be non-empty. This is a contradiction. Accordingly, {a mathematical formula}ε̲1=ε̲2.  □
      </paragraph>
      <paragraph>
       From this lemma, the next theorem is derived straightforwardly.
      </paragraph>
      <paragraph label="Theorem 8">
       The weak least{a mathematical formula}core+is identical to the weak least core for the optimal coalition structure{a mathematical formula}CS⁎, i.e., any payoff vector in the weak least{a mathematical formula}core+is also in the weak least core for{a mathematical formula}CS⁎and vice versa.
      </paragraph>
      <paragraph label="Proof">
       From the definitions and Lemma 1, the weak least {a mathematical formula}core+ is a superset of the weak least core (for the optimal coalition structure {a mathematical formula}CS⁎). Assume there exists a payoff vector y such that it is not in the weak least core, but in the weak least {a mathematical formula}core+. Since the non-blocking conditions are the same across these two solution concepts, this payoff vector y must violate the efficiency condition of the weak least core. Here, let us construct another payoff vector {a mathematical formula}y′ such that{a mathematical formula} The payoff vector {a mathematical formula}y′ inevitably satisfies the efficiency condition because {a mathematical formula}y′(A)=∑i∈Ayi′=y(A)+V(CS⁎)−y(A)n×n=V(CS⁎).Let {a mathematical formula}ε⁎ be the least value of the weak least core. For any coalition S and payoff vector y,{a mathematical formula} Then, we obtain {a mathematical formula}v(S)−y′(S)|S|≤ε⁎−V(CS⁎)−y(A)n. {a mathematical formula}y′ is in the weak {a mathematical formula}ε′-core with {a mathematical formula}ε′ which is equal to {a mathematical formula}ε⁎−V(CS⁎)−y(A)n. This contradicts the fact that {a mathematical formula}ε⁎ is the least value of the weak ε-core because the weak {a mathematical formula}ε′-core with {a mathematical formula}ε′&lt;ε⁎ is non-empty. Accordingly, the weak least {a mathematical formula}core+ is identical to the weak least core for {a mathematical formula}CS⁎.  □
      </paragraph>
      <paragraph>
       This theorem shows that when ε reaches the least value, the weak ε-core{sup:+} converges to the weak ε-core for {a mathematical formula}CS⁎. That is, the dual solution {a mathematical formula}∑i∈Ayi converges to {a mathematical formula}V(CS⁎). As a result, the agents in the weak ε-core{sup:+} must form {a mathematical formula}CS⁎, otherwise, the agents do not produce enough value. As such, if {a mathematical formula}CS⁎ and its value are exactly computed, the weak ε-core{sup:+} is no longer needed. However, as long as finding {a mathematical formula}CS⁎ is hard, the least value is difficult to obtain in practice. We cannot justify how far a given ε from the (unknown) least value. Thus, the weak ε-core{sup:+} is useful as an approximate solution concept for the weak ε-core for {a mathematical formula}CS⁎.
      </paragraph>
      <paragraph>
       Next, we briefly explain the traditional nucleolus [38]. For any payoff vector and coalition, let us consider the excess of the coalition. Also, consider the vector of all the coalitions' excesses, sorted in descending order. The nucleolus chooses the payoff vector that lexicographically minimizes this vector; it first minimizes the greatest excess, then the second-greatest excess, etc. The nucleolus has some desirable properties. For a transferable utility game, it always exists, is unique (even if the core of the game is empty), is in the core if the core is non-empty. Furthermore, it is known that if the core is empty, the nucleolus is in the (strong) least core. The same property holds when we use the average excesses, i.e., if the weak core is empty, the weak nucleolus is in the weak least core (see [43] for example).
      </paragraph>
      <paragraph>
       Before formally defining the weak nucleolus for our games with constraints on the possible coalitions, let us introduce several notations. Let {a mathematical formula}θ(y) for each payoff vector y be the {a mathematical formula}|AC|-vector whose components are the corresponding average excess {a mathematical formula}d(y,S) of each allowed coalition {a mathematical formula}S∈AC, sorted in descending order: {a mathematical formula}θi(y)≥θj(y) whenever {a mathematical formula}1≤i≤j≤|AC|. i is associated with coalition S such that {a mathematical formula}θi(y)=d(y,S). The lexicographic order between such excess vectors is defined as follows. We represent {a mathematical formula}θ(y′)≺θ(y) if y is preferred to {a mathematical formula}y′, which holds if and only if there exists an integer {a mathematical formula}i⁎ such that{a mathematical formula} Also, when we write {a mathematical formula}θ(y′)⪯θ(y), it indicates that {a mathematical formula}θ(y′)≻θ(y) does not hold. Now we are ready to define the weak nucleolus.
      </paragraph>
      <paragraph label="Definition 15">
       Weak nucleolusThe weak nucleolus for coalition structure {a mathematical formula}CSA of all agents A is in the set of payoff vectors where each element y satisfies{a mathematical formula}
      </paragraph>
      <paragraph>
       This definition implies the efficiency condition by minimizing the largest average excess. If no coalition is constrained, it is of course equivalent to the original weak nucleolus. Furthermore, the weak nucleolus does minimize the largest excess of both the members and the non-members of AC. However, it does not lexicographically minimize the excess vector. Precisely, it lexicographically minimizes the excess vector for the members of AC, not for its non-members.{sup:6} Therefore, this weak nucleolus may provide a different payoff vector from the conventional one if the use of some coalition is prohibited. Nevertheless, when an optimal coalition structure is given, the weak nucleolus is guaranteed to be in the weak least core for that coalition structure.
      </paragraph>
      <paragraph label="Theorem 9">
       The weak nucleolus for the optimal coalition structure is in the weak least{a mathematical formula}core+, as well as in the weak least core for the optimal coalition structure.
      </paragraph>
      <paragraph label="Proof">
       Assume there exists a payoff vector y such that it is not in the weak least core (for the optimal coalition structure), but in the weak nucleolus (for the optimal coalition structure). Let {a mathematical formula}y′ be a payoff vector from the weak least core. From the assumption, the largest excess {a mathematical formula}θ1(y) in the excess vector of y must exceed {a mathematical formula}θ1(y′). That is, {a mathematical formula}y′ is preferred to y. This fact contradicts that y is in the weak nucleolus.  □
      </paragraph>
      <paragraph>
       Finally, let us briefly describe what happens if we relax the efficiency condition of the weak nucleolus. We can define the weak {a mathematical formula}nucleolus+ by imposing {a mathematical formula}∑i∈Ayi≤V(CS⁎). However, this does not distinguish the weak nucleolus from the weak {a mathematical formula}nucleolus+ at all because the latter automatically achieves its efficiency due to its definition which minimizes the largest excess in y.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>