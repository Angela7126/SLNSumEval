<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Truncated incremental search.
   </title>
   <abstract>
    Incremental heuristic search algorithms reuse their previous search efforts whenever these are available. As a result, they can often solve a sequence of similar planning problems faster than planning from scratch. State-of-the-art incremental heuristic searches (such as LPA*, D* and D* Lite) work by propagating cost changes to all the states in the search tree whose g values (the costs of computed paths from the start state) are no longer optimal. This work is based on the observation that while a complete propagation of cost changes is essential to ensure optimality, the propagations can be stopped earlier if we are looking close-to-optimal solutions instead of the optimal one. We develop a framework called Truncated Incremental Search that builds on this observation and uses a target suboptimality bound to efficiently restrict cost propagations. We present two truncation based algorithms, Truncated LPA* (TLPA*) and Truncated D* Lite (TD* Lite), for bounded suboptimal planning and navigation in dynamic graphs. We also develop an anytime replanning algorithm, Anytime Truncated D* (ATD*), that combines the inflated heuristic search with truncation, in an anytime manner. We discuss the theoretical properties of these algorithms proving their correctness and efficiency, and present experimental results on 2D and 3D (x, y, heading) path planning domains evaluating their performance. The empirical results show that the truncated incremental searches can provide significant improvement in runtime over existing incremental search algorithms, especially when searching for close-to-optimal solutions in large, dynamic graphs.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Heuristic search is a fundamental problem solving technique in Artificial Intelligence (AI) [1], that models an optimization problem in terms of planning paths in state-space graphs. Search algorithms explore the state-space using domain specific information (heuristics), which guide the search towards solutions. Over the years, search algorithms have been used in many applications, including classical planning [2], learning [3], [4], robotics [5], [6], [7], [8], [9], [10], network design [11], [12], [13], VLSI [14], [15], [16], drug design [17], [18], bio-informatics [19], with the list growing every day.
     </paragraph>
     <paragraph>
      Planning for real-world applications involves two major problems, uncertainty and complexity. Real world is an inherently uncertain and dynamic place, which means accurate models are difficult to obtain and can quickly become out of date. Replanning becomes a necessity when such a change is perceived. The challenge here is to efficiently utilize the information gathered from earlier searches to facilitate the current planning. Incremental search algorithms are meant for such dynamic environments. They reuse previous search efforts to speed up the current search, and thus can often replan faster than planning from scratch. For complex planning problems, it is often desirable to obtain a trade-off between the solution quality and the runtime, especially when optimal planning becomes infeasible due to resource (time/memory) constraints. Anytime search algorithms target such trade-offs, providing an initial (possibly highly suboptimal) solution quickly, and then iteratively improving the solution quality depending on the deliberation time. In this work, we focus on these two classes of search algorithms, incremental and anytime, and present novel algorithms for efficiently planning/replanning bounded suboptimal paths through large, dynamic graphs.
     </paragraph>
     <paragraph>
      Lifelong planning A* (LPA*) [20] is an incremental version of A* (with a consistent heuristic function) which optimally solves a sequence of search problems in a dynamic environment. Its first iteration is the same as that of A*, but the subsequent searches are potentially faster as they reuse parts of the previous search tree that are identical to the current search tree. The rest of the tree is rebuilt by expanding states for which the g values (path cost from the start state) differ from the previous run (cost propagation). If large parts of the search tree remain unchanged over episodes, i.e., if the environments change only slightly and the changes are close to the goal, LPA* can converge significantly faster than A*. In Fig. 1, we present a simple path planning example in dynamic environment, showing how LPA* can outperform A*. The tree repair approach of LPA* has been used as a backbone for several incremental algorithms, such as D* Lite [21], Field D* [22], Anytime D* [23], that are widely used in practice, especially in robotics.
     </paragraph>
     <paragraph>
      As LPA* recomputes the optimal solution every time the environment changes, it needs to propagate the cost changes for all the states (in the search tree) whose g values are no longer optimal. This means that even for a small change in the environment, large parts of the search tree may be regenerated, especially if the changes occur close to the root. We start with the observation that while the g values may change for a large number of states, the cost difference between the previous and the current values may not be significant for a majority of such states. LPA* treats all such states equally, as it uses a binary notion of change and does not account for the impact of a particular change. In contrast, if we quantify the possible impact of the costs changes (find out how much the path cost has changed), we may improve the replanning runtime by only re-expanding the states for which the change is significant and reusing the previous paths for the other states. For example, in Fig. 1, after the first search, an obstacle pops (Fig. 1f). This (potentially) changes the g values for 202 states, and LPA* re-expands all these states (some of them twice) before it recomputes an optimal solution. However, if we only consider states for which the (potential) change in g is more than {a mathematical formula}5% or {a mathematical formula}10%, the number of states affected reduces to 78 and 41, respectively. Similarly, when the obstacle moves (Fig. 1k), the total number of states (potentially) affected is 229, whereas the number of states for which the (potential) cost change is more than {a mathematical formula}5% is 117, and the number of states with (potential) cost change more than {a mathematical formula}10% is 67.
     </paragraph>
     <paragraph>
      This observation provides an opportunity to target an effective trade-off between solution quality and replanning runtime. On one hand, we can achieve good quality solutions by propagating the cost changes for states where the changes are significant. On the other hand, we can reduce the replanning runtime by reusing the previous search values for states where the cost changes have little impact. To exploit this trade-off, we develop Truncated LPA* (TLPA*), an incremental search algorithm that speeds up replanning by using a suboptimality bound (ϵ) to limit re-expansions. TLPA* only propagates the cost changes when it is essential to ensure the suboptimality bound and reuses the previous search values for all other states (truncation). As a result, it can substantially improve the replanning runtime, and yet guarantee bounded suboptimal termination. In Fig. 1, we present an example dynamic planning scenario comparing A*, LPA*, WA* and TLPA* (the last two with suboptimality bound 1.1), highlighting the efficacy of TLPA*.
     </paragraph>
     <paragraph>
      We propose two simple rules for truncation and explain how they can be integrated with LPA* to develop TLPA*. We discuss the theoretical properties of TLPA* demonstrating its correctness and efficiency, and present experimental results for two domains, 2D and 3D (x, y, heading) path planning, highlighting its efficacy over optimal and bounded suboptimal incremental searches. In addition, we discuss how the truncation rules can be applied on top of the D* Lite algorithm, resulting in Truncated D* Lite (TD* Lite), a bounded suboptimal algorithm for navigation in dynamic graphs.
     </paragraph>
     <paragraph>
      We also discuss how the truncation approach can be extended to work as an anytime algorithm. Anytime D* (AD*) [23] is the current state-of-the-art algorithm for anytime replanning, which combines the benefits of incremental replanning (D* Lite [21]) and anytime planning (ARA* [5]). While AD* is both incremental and anytime, it actually speeds up the planning part (path computation) using inflated heuristics, whereas its replanning part (cost propagation) is exactly the same as LPA*/D* Lite. In contrast, truncation methods improve the replanning by restricting the cost propagations, whereas the planning part is essentially similar to A*. This indicates that if we can combine heuristic inflation with truncation (in an anytime fashion), the resulting algorithm may provide a more effective solution to the problem of anytime replanning by simultaneously improving planning and replanning.
     </paragraph>
     <paragraph>
      Unfortunately, these approaches cannot be combined directly, as the truncation rules used in TLPA* (and TD* Lite) cannot work with inflated heuristics to guarantee a bounded suboptimal termination. To rectify this, we propose two new truncation rules, that can work on top of inflated heuristic search, without violating the suboptimality constraints. We develop Anytime Truncated D* (ATD*), an anytime replanning algorithm that uses these new truncation rules in conjunction with heuristic inflation, and thus can simultaneously improve both planning and replanning, offering greater efficacy and flexibility for solving complex and dynamic planning problems under limited time. We describe the theoretical properties of ATD*, and present experimental results for 2D and 3D (x, y, heading) navigation evaluating its performance.
     </paragraph>
     <paragraph>
      Preliminary versions of this paper appeared in previous publications [24], [25]. In this paper we provide a complete report on the truncation approach and discuss all the truncation based algorithms in greater details with suitable examples. We also include a broader analysis of the theoretical properties of truncated incremental searches and present a more thorough evaluation of their performance.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section we discuss some of the related works in the domains of incremental and anytime heuristic search.
     </paragraph>
     <section label="2.1">
      <section-title>
       Incremental search algorithms
      </section-title>
      <paragraph>
       The incremental heuristic search algorithms found in AI literature can be broadly classified in three main categories. The first class (LPA* [20], D* [26], D* Lite [21]) reuses the g values from the previous search during the current search to correct them when necessary, which can be interpreted as transforming the A* tree from the previous run into the A* tree for the current run. The same approach has also been used for uninformed searches (DynamicSWSF-FP [27]), to compute shortest paths in dynamic graphs. These algorithms store the previous g values of the states using an extra variable (v) and only process states for which {a mathematical formula}g≠v, thus reducing replanning effort. One of the major advantages of these approaches is that they generally do not make limiting assumptions about the structure or behavior of the underlying graph, and thus, can work with any type of state-space graph as well as any type of changes (edge addition/removal, cost increase/decrease).
      </paragraph>
      <paragraph>
       The second class (Fringe Saving A* [28], Differential A* [29]) also reuses the previous search tree, but instead of repairing the tree, they identify the point till which the previous search is valid and resume searching from there. In particular, these algorithms restart A* at the point where the current search queue differs from the previous run. These algorithms often make limiting assumptions about the state-space or the dynamic behavior, which makes them inapplicable for general cases. For example, Fringe Saving A* [28] only works on 2D grids with unit cost transitions between neighboring cells. However, the assumptions made by these algorithms allow them to perform well in scenarios where they are applicable. Recently, an algorithm called Tree Restoring Weighted A* [30] was proposed, which uses the same philosophy of restoring the search queue, but can work with generic graphs as well as inflated heuristics.
      </paragraph>
      <paragraph>
       The third class (Adaptive A* [31], Generalized Adaptive A* [32]) updates the h values from the previous searches to make them more informed over iterations. As the heuristic becomes more informed, search gets better. These approaches are simple, effective and they do not require storing the entire search tree (or the search queue) across iterations (although, some of them also reuse previous path [33]/search tree [34] information in addition to the heuristic updates). However, as these algorithms alter the heuristic values between search iterations, they may have limitations or require additional processing. For example, the Adaptive A* [31] algorithm (also [33] and [34]) only works with cost increases and cannot handle cost decreases. Generalized Adaptive A* [32] does not have this limitation, but it requires an additional pass of heuristic updates to ensure consistency, which may have significant overhead. Another recent algorithm, Multipath Generalized Adaptive A* [35] improves upon Generalized Adaptive A* by reusing paths from previous searches.
      </paragraph>
      <paragraph>
       The algorithms presented in the paper belong to the first category, as they are based on the tree repairing philosophy of LPA*/D* Lite.
      </paragraph>
      <paragraph>
       Incremental search approaches have also been used in other contexts than searching in dynamic graphs. For example, incremental search algorithms (Generalized Fringe Retrieving A* [36], Moving Target D* Lite [37]) have been proposed for moving target search, where the underlying graph remains static but the search goal changes as the target moves.
      </paragraph>
      <paragraph>
       Graph search based local approaches have also been used for plan adaptation/repair in dynamic environments [38], [39]. These algorithms generally focus on improving different metrics (such as plan stability [40]) and typically they do not provide any guarantees on the quality of solutions.
      </paragraph>
      <paragraph>
       Another closely related class of search algorithms is real-time search. Real-time search algorithms (such as RTA* and LRTA* [41], RTAA* [42], etc.) interleave planning and execution. They compute a partial plan by limiting the search horizon, execute one or more of the chosen actions, and replan from the current state. The fundamental difference between incremental and real-time search is that the incremental search algorithms compute a complete plan according to the current environment (actual or perceived) and only replan when they sense a change in the environment, whereas real-time search algorithms compute partial plans, execute and replan iteratively until it reaches the goal, in a static environment. There are also search algorithms (Real-time D* [43], RTTES [44]) that are both real-time and incremental.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Anytime search algorithms
      </section-title>
      <paragraph>
       Design of anytime search algorithms has received considerable attention in the last two decades. A number of anytime algorithms are based on the Weighted A* (WA*) [45], where the actual (consistent) heuristic values are multiplied by an inflation factor ({a mathematical formula}w&gt;1.0) to give the search a depth-first flavor. Inflated heuristic searches are shown to be fast for many domains [46], [5], they also provide an implicit bound on the suboptimality, namely, the factor (w) by which the heuristic is inflated [47]. Hansen et al. [48], [49] proposed a simple technique for converting WA* into an anytime algorithm, Anytime Weighted A* (AWA*). Instead of terminating when the first solution is found, AWA* continues to search more, computing a sequence of improved solutions, updating the quality bounds whenever a new solution is discovered. Anytime Repairing A* (ARA*) [5] adopts a slightly different approach. It reduces the inflation factor every time a solution is found, iteratively targeting tighter bounds. It also reuses the previous search efforts maximally, and restricts the states expansions to one per iteration. ARA* is widely used for path planning in dense graphs, especially in robotics applications. Other algorithms, like RWA* [50] and ANA* [51] also exploit the WA* principle. RWA* proposes a restart based approach in contrast to the reuse based approach of ARA*, whereas ANA* is a non-parametric (i.e., it does not require input parameters) anytime search that greedily looks for solutions among states with the highest potential to improve upon the incumbent solution.
      </paragraph>
      <paragraph>
       There are also several anytime searches that are not based on WA*. Most of these use some constraints to restrict the search space for quick termination, or use a different metric than the conventional f values to order the state expansions. These constraints are iteratively relaxed to improve the solution quality in an anytime manner. These algorithms include variants of depth-first search (Depth-first Branch-and-Bound search [52] and Complete Anytime Beam search [53]), variants of the beam search [54] (Beam-Stack search [55], ABULB [56], [57], Anytime Pack Search [58], Anytime Column Search [59]), Anytime Window A* (AWinA*) [60], where a window of chosen depth is used to restrict the active search space, Anytime Explicit Estimation Search (AEES) [61], that uses a distance-to-go estimate (similar to the A*ϵ algorithm [62]) to determine the order of expansions. Unlike WA* based approaches, most of these algorithms do not provide any implicit bounds on their solutions. Although, some of them (BQAWinA* [60], AEES [61]) can adapt to target suboptimality bounds. On the other hand, most of these algorithms use less memory than the WA* approaches (some can run under any memory restrictions [53], [63]), and therefore, can scale better to solve large sized problems under reasonable memory/runtime limits.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Anytime and incremental search
      </section-title>
      <paragraph>
       While there are a number of heuristic search algorithms that are either incremental or anytime, algorithms that satisfy both these properties are rare. In fact, to our knowledge Anytime D* [23], which combines ARA* with D* Lite, and Anytime Tree Repairing A* [64] which combines ARA* with Tree Repairing A*, are the only two anytime algorithms that work for general dynamic graphs. Another algorithm called Incremental ARA* (I-ARA*) [65] also uses ARA* incrementally, but it is applicable for moving target search in static graphs only and not for dynamic graphs with arbitrary cost changes.
      </paragraph>
      <paragraph>
       At this point, it may be noted that while both the inflated heuristic search algorithms (ARA* [5], GLPA* [66], AD* [23], I-ARA* [65], ATRA* [64]) and truncation based searches proposed in this work produce provably guaranteed solutions within a chosen suboptimality bound, these algorithms are fundamentally different. The former speed up the search (planning) using inflated heuristics to order the state expansions, whereas truncated based algorithm use the suboptimality bound to accelerate replanning by restricting state re-expansions, with or without heuristic inflation.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Truncated LPA*
     </section-title>
     <paragraph>
      In this section we discuss the concept of truncation and demonstrate how it can be used to convert LPA* into a bounded suboptimal replanning algorithm. We start with brief description of LPA*, and then move on to explain the truncation rules.
     </paragraph>
     <paragraph label="Notation">
      In the following, S denotes the finite set of states of the domain. {a mathematical formula}sstart denotes the start state and {a mathematical formula}sgoal denotes the goal state. {a mathematical formula}c(s,s′) denotes the cost of the edge between s and {a mathematical formula}s′, if there is no such edge, then {a mathematical formula}c(s,s′)=∞. We assume {a mathematical formula}c(s,s′)≥0 and {a mathematical formula}c(s,s)=0, i.e., all the edge costs are non-negative and self-loops have zero cost. {a mathematical formula}Succ(s):={s′∈S|c(s,s′)≠∞}, denotes the set of all successors of s. Similarly, {a mathematical formula}Pred(s):={s′∈S|s∈Succ(s′)} denotes the set of predecessors of s. {a mathematical formula}c⁎(s,s′) denotes the cost of the optimal path from s to {a mathematical formula}s′, if no such path exists, then {a mathematical formula}c⁎(s,s′)=∞. {a mathematical formula}g⁎(s) denotes optimal path cost from {a mathematical formula}sstart to s. We use {a mathematical formula}π(s) to denote a path from {a mathematical formula}sstart to s. {a mathematical formula}h(s) denotes the heuristic value of s, which we assume to be consistent (and thus admissible), i.e., we assume {a mathematical formula}h(sgoal)=0 and {a mathematical formula}h(s)≤h(s′)+c(s,s′), {a mathematical formula}∀s,s′ such that {a mathematical formula}s′∈Succ(s) and {a mathematical formula}s≠sgoal. We use the symbol ∞ to denote a very large number (more than any possible value of path cost). We define the comparison operator with ∞ in the following manner, {a mathematical formula}[x&lt;∞] is true for any {a mathematical formula}x≠∞, else it is false.
     </paragraph>
     <section label="3.1">
      <section-title>
       LPA*
      </section-title>
      <paragraph>
       LPA* [20] is an incremental version of A* that uses consistent heuristics and breaks ties among states with the same f values in favor of states with smaller g values. LPA* repeatedly determines a minimum-cost path from {a mathematical formula}sstart to {a mathematical formula}sgoal in a state-space graph, while some of the edge costs change. It maintains two kinds of estimates of the cost of a path from {a mathematical formula}sstart to a state s: {a mathematical formula}g(s) and {a mathematical formula}v(s). {a mathematical formula}v(s) holds the cost of the best path found from {a mathematical formula}sstart to s during its last expansion, while {a mathematical formula}g(s) is computed from the v values of {a mathematical formula}Pred(s), and thus, is potentially better informed than {a mathematical formula}v(s). Additionally, it stores a back-pointer {a mathematical formula}bp(s) pointing to the best predecessor of s (if computed), for each s. A state s is called consistent if {a mathematical formula}v(s)=g(s), otherwise it is either overconsistent (if {a mathematical formula}v(s)&gt;g(s)) or underconsistent (if {a mathematical formula}v(s)&lt;g(s)).
      </paragraph>
      <paragraph>
       LPA* works by identifying inconsistent states (in a search tree) and systematically updating their v, g, and bp values, till an optimal path is discovered. At any intermediate point, it satisfies the following invariants,
      </paragraph>
      <list>
       <list-item label="•">
        Invariant 1:{a mathematical formula}bp(sstart)=null,g(sstart)=0 and {a mathematical formula}∀s∈S{sstart},bp(s)=argmin(s′∈Pred(s))v(s′)+c(s′,s), {a mathematical formula}g(s)=v(bp(s))+c(bp(s),s), i.e., all states update their g values using the best path information from {a mathematical formula}Pred(s), other than {a mathematical formula}sstart for which the g value is set to 0 by definition.
       </list-item>
       <list-item label="•">
        Invariant 2: The priority queue (OPEN) only contains the inconsistent states.
       </list-item>
       <list-item label="•">
        Invariant 3: The priority of a state s is given by: {a mathematical formula}Key(s)=[Key1(s),Key2(s)] where {a mathematical formula}Key1(s)=min(g(s),v(s))+h(s) and {a mathematical formula}Key2(s)=min(g(s),v(s)). Priorities are compared in lexicographic order, i.e., for two states s and {a mathematical formula}s′, {a mathematical formula}Key(s)≤Key(s′), iff either {a mathematical formula}Key1(s)&lt;Key1(s′) or ({a mathematical formula}Key1(s)=Key1(s′) and {a mathematical formula}Key2(s)≤Key2(s′)).
       </list-item>
      </list>
      <paragraph>
       It may be noted that the tie-breaking part of the Key function is important for LPA*. A* can use a tie-breaking favoring states with larger g values. The same is not true for LPA*, as in case of a tie, it needs to process an underconsistent state before an overconsistent state [20]. However, the tie-breaking in LPA* (and related algorithms) can be improved by using {a mathematical formula}Key1(s)=min(g(s),v(s))+h(s); and {a mathematical formula}Key2(s)=0 if {a mathematical formula}v(s)&lt;g(s) (i.e. if s in underconsistent), {a mathematical formula}Key2(s)=1, otherwise [66]; without violating any properties. Throughout this paper, whenever we use A*/WA*, we use tie-breaking favoring states with larger g values, and whenever we use LPA* based algorithms, we use the tie-breaking favoring underconsistent states.
      </paragraph>
      <paragraph>
       The pseudocode of a basic version of LPA* is shown in Algorithm 1. LPA* starts by initializing the states and inserting {a mathematical formula}sstart into OPEN (lines 30–32). It then calls ComputePath to obtain a minimum cost solution. ComputePath expands the inconsistent states from OPEN in increasing order of priority, maintaining Invariants 1–3, until it discovers a minimum cost path to {a mathematical formula}sgoal. If a state s is overconsistent, ComputePath makes it consistent (line 21) and propagates this information to its successors according to Invariant 1. This may make some {a mathematical formula}s′∈Succ(s) inconsistent, which are then put into OPEN ensuring Invariant 2. If s is underconsistent, ComputePath makes it overconsistent by setting {a mathematical formula}v(s)=∞ (line 25) and propagates the underconsistency information to its children, and selectively puts s and its children back to OPEN (maintaining Invariants 1–2). Note that, during the initialization, {a mathematical formula}v(s) is set to ∞, {a mathematical formula}∀s∈S (line 4). Thus, the first iteration of ComputePath is exactly the same as A*. After the first iteration, if one or more edge costs change, LPA* updates the g and bp values of the affected states (line 38), and inserts the inconsistent state in OPEN. It then calls ComputePath again to recompute an optimal path.
      </paragraph>
      <paragraph>
       In Fig. 2, we illustrate the working of LPA* on a simple example graph. To simplify the example, we assume that {a mathematical formula}h(s)=0,∀s. Fig. 2a shows the first run where each expanded state (shown in grey) has {a mathematical formula}v=g. The initial solution path is shown by the back-pointers (dashed line). After the first search, the cost of the edge from S to A changes from 1 to 6, making A an underconsistent state, with {a mathematical formula}g(A)=6 and {a mathematical formula}v(A)=1 (Fig. 2b). LPA* expands A (Fig. 2c) to propagate this inconsistency information to D, and continues to expand of D and F (Figs. 2d and 2e) before computing the optimal solution (Fig. 2f). A total of 5 states are expanded in the second iteration (A once, D and F twice).
      </paragraph>
      <paragraph>
       LPA* guarantees the following properties,
      </paragraph>
      <list>
       <list-item label="•">
        Optimality: When the ComputePath function exits, the cost of the path from {a mathematical formula}sstart to {a mathematical formula}sgoal obtained by following the back-pointers stored in every state is no larger than {a mathematical formula}g⁎(sgoal).
       </list-item>
       <list-item label="•">
        Efficiency: No state is expanded more than twice during the execution of ComputePath. Moreover, a state s is expanded in ComputePath, only if either it was inconsistent initially or made inconsistent during the current execution of ComputePath.
       </list-item>
      </list>
     </section>
     <section label="3.2">
      <section-title>
       Truncation rules
      </section-title>
      <paragraph>
       As discussed in Section 3.1, when cost changes occur, LPA* recomputes an optimal solution by propagating the cost change information through expansion of states. In this section, we present two rules, that can be used to limit such re-expansions using a target suboptimality bound.
      </paragraph>
      <paragraph>
       First, we introduce a new term called {a mathematical formula}gπ(s), to denote the cost of the path from {a mathematical formula}sstart to s computed by following the current back-pointers (bp). If no such path exists, then {a mathematical formula}gπ(s)=∞. Note that, {a mathematical formula}gπ(s) may be different from {a mathematical formula}g(s), as {a mathematical formula}g(s) holds the path cost computed directly using v values of {a mathematical formula}Pred(s) (Invariant 1), whereas {a mathematical formula}gπ(s) is computed by following the back-pointers from s to {a mathematical formula}sstart. In the truncation rules, we use the {a mathematical formula}gπ value for an inconsistent state s and a chosen suboptimality bound ϵ, to decide whether we need to expand state s to satisfy the bound. If the bounds can be guaranteed without expanding s, we truncate s (remove it from OPEN without expansion).
      </paragraph>
      <paragraph>
       TruncationRule 1  Rule 1 is applicable for underconsistent states. We observe that when we are looking for an ϵ bounded solution, we can reuse the old path cost {a mathematical formula}v(s) for an underconsistent state s (selected for expansion), as long as {a mathematical formula}gπ(s)+h(s)≤ϵ⋅(v(s)+h(s)). This stems from the fact that for an underconsistent state s selected for expansion, {a mathematical formula}v(s)+h(s) is a lower bound on the solution cost through s, as {a mathematical formula}v(s) holds previous shortest path cost (from {a mathematical formula}sstart) and {a mathematical formula}h(s) is a consistent heuristic. If the current path to s (from {a mathematical formula}sstart) satisfies the bound on {a mathematical formula}v(s)+h(s), any state {a mathematical formula}s′ that uses {a mathematical formula}v(s) to compute its {a mathematical formula}g(s′) will never underestimate the actual solution cost by more than the ϵ factor. In other words, even if we compute the new solution using the old{a mathematical formula}v(s), the obtained solution cost will be less than or equal to {a mathematical formula}ϵ⋅g⁎(sgoal), as the old paths have not deteriorated beyond the chosen bound.
      </paragraph>
      <paragraph>
       We explain this rule in Fig. 3 using the same example as shown in Fig. 2, however, unlike Fig. 2, here we search for a two bounded solution (i.e., {a mathematical formula}ϵ=2.0). The first search (same as A*/LPA*) is shown in Fig. 3a. After the first episode, the edge cost from S to A changes from 1 to 6 (Fig. 3b). Now, when A is selected for expansion, we compute {a mathematical formula}gπ(A) (Fig. 3c) to check whether {a mathematical formula}gπ(A)+h(A)≤ϵ⋅(v(A)+h(A)). For A, this condition is not true ({a mathematical formula}gπ(A)=6, {a mathematical formula}v(A)=1 and {a mathematical formula}h(A)=0). Thus, we expand A, making D underconsistent. Next, when D is selected for expansion, we find that {a mathematical formula}gπ(D)+h(D)≤ϵ⋅(v(D)+h(D)), as {a mathematical formula}gπ(D)=3 and {a mathematical formula}v(D)=2, i.e., D satisfies the truncation condition. At this point, we can truncate the cost propagation at D, as the successors of D can continue to rely on the old{a mathematical formula}v(D) ({a mathematical formula}v(D)=2) and yet guarantee that the path cost through them will be within the ϵ bound. In this example, the replanning iteration terminates at this point with a solution of cost 5, as there are no more inconsistent states to process. Note that, for this example, LPA* requires 5 re-expansions to recompute an optimal solution, whereas TLPA* provides a 2 bounded solution with 1 re-expansion only. Next, we formally state Truncation Rule 1.
      </paragraph>
      <paragraph label="Rule 1">
       An underconsistent state s having{a mathematical formula}Key(s)≤Key(u),∀u∈OPENis truncated (removed from OPEN without expansion) if{a mathematical formula}gπ(s)+h(s)≤ϵ⋅(v(s)+h(s)).
      </paragraph>
      <paragraph>
       TruncationRule 2  Rule 2 is applicable for both underconsistent and overconsistent states. The underlying principle of this rule is very simple. We observe that LPA* expands inconsistent states in an increasing order of their Key values, until the goal state has the lowest Key value in OPEN. Therefore, for any state s selected for expansion, {a mathematical formula}Key1(s)=min(g(s),v(s))+h(s) provides a lower bound on the minimum-cost solution, i.e., {a mathematical formula}Key1(s)≤g⁎(sgoal). Now, if {a mathematical formula}gπ(sgoal)≤ϵ⋅Key1(s), i.e., the cost of the solution obtained by following the back-pointers from {a mathematical formula}sgoal to {a mathematical formula}sstart is not more than {a mathematical formula}ϵ⋅Key1(s), we have {a mathematical formula}gπ(sgoal)≤ϵ⋅Key1(s)⇒gπ(sgoal)≤ϵ⋅g⁎(sgoal). In other words, the current solution is already within the ϵ bound of the optimal cost solution. Therefore, we can truncate s without violating the bound. Moreover, as the Key values of expanded states in LPA* are monotonically non-decreasing during the execution of ComputePath, the same condition ensures that expansion of any other state {a mathematical formula}s′ in OPEN cannot improve the current bound, i.e., we may terminate the current replanning iteration at this point.
      </paragraph>
      <paragraph>
       We explain this rule with Fig. 4 in comparison to LPA*. The first search is shown in Fig. 4a. After the first episode, cost of the edge from C to E changes from 2 to 1, making E overconsistent (Fig. 4b). LPA* propagates this cost change until {a mathematical formula}Key(sgoal) becomes the minimum Key value in OPEN, i.e., it expands E and H before returning the previous solution as the minimum cost solution (Fig. 4c). Now, let us consider Truncation Rule 2 with {a mathematical formula}ϵ=2.0. In Fig. 4d, when E is selected for expansion, it has {a mathematical formula}Key1(E)=2 ({a mathematical formula}g(E)=2, {a mathematical formula}v(E)=3, and {a mathematical formula}h(E)=0), and we {a mathematical formula}gπ(G)=4 (path shown in dashed arrows, Fig. 4e). As expansion of E cannot produce a solution with cost less than 2 and {a mathematical formula}gπ(G)=4, at this point, we can truncate E and return the current path as a 2 bounded solution. Thus, for this example, we can guarantee 2 bounded solution without any re-expansions. Next, we formally state Truncation Rule 2.
      </paragraph>
      <paragraph label="Rule 2">
       A state s having{a mathematical formula}Key(s)≤Key(u),∀u∈OPENis truncated if{a mathematical formula}gπ(sgoal)≤ϵ⋅Key1(s). Also, if any state s is truncated usingRule 2, all states{a mathematical formula}s′∈OPENare truncated as,{a mathematical formula}∀s′∈OPEN,Key1(s′)≥Key1(s).
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Truncated LPA* algorithm
      </section-title>
      <paragraph>
       Truncated LPA* (TLPA*) incorporates the truncation rules in LPA*. We include the pseudocode for TLPA* in Algorithm 3. TLPA* uses two extra variables for each state (compared to LPA*): {a mathematical formula}gπ(s), as described earlier, and {a mathematical formula}π(s), which stores the current path (from {a mathematical formula}sstart) for a truncated state s. It also uses an additional list TRUNCATED to store the underconsistent states that are truncated.
      </paragraph>
      <paragraph>
       TLPA* uses two auxiliary functions, namely ComputeGpi, to populate the {a mathematical formula}gπ(s) and {a mathematical formula}π(s) for a given state, and ObtainPath, to populate the solution path when ComputePath terminates. These functions are described in Algorithm 2.
      </paragraph>
      <paragraph>
       ComputePath in TLPA* uses the {a mathematical formula}gπ values to apply the truncation rules. Before each expansion, {a mathematical formula}gπ(sgoal) is computed to check whether Rule 2 can be applied. If the check at line 21 (Algorithm 3) is satisfied, ComputePath terminates with solution cost equal to {a mathematical formula}gπ(sgoal). When an underconsistent state s is selected for expansion, its {a mathematical formula}gπ(s) is used to check whether Rule 1 can be applied. If the check at line 30 is satisfied, s is truncated, otherwise it expanded in the same manner as LPA*.
      </paragraph>
      <paragraph>
       Apart from the application of the truncation rules the behavior of TLPA* is essentially the same as LPA*, other than the fact that before each call of ComputePath, TLPA* also updates the values for the truncated states in addition to the states for which the path cost has changed, and inserts all the inconsistent states in OPEN (lines 48–50).
      </paragraph>
      <paragraph>
       While the pseudocodes in Algorithm 2, Algorithm 3 describe the behavior of TLPA*, its runtime and memory can be further optimized in a few obvious ways. Some of the optimizations we use are the following,
      </paragraph>
      <list>
       <list-item label="•">
        In ComputePath, {a mathematical formula}gπ(sgoal) is computed before each expansion. We reduce the number of calls by hashing the states in current path {a mathematical formula}sstart to {a mathematical formula}sgoal and only re-computing {a mathematical formula}gπ(sgoal) if any of the state in this path is updated after the previous computation.
       </list-item>
       <list-item label="•">
        In ComputeGpi, we do not store the entire path from {a mathematical formula}sstart to s, if we encounter a truncated state {a mathematical formula}s′, we store the path up to {a mathematical formula}s′ and modify the ObtainPath to dynamically update the paths from truncated states.
       </list-item>
       <list-item label="•">
        Furthermore, while computing the {a mathematical formula}gπ for any state s other than {a mathematical formula}sgoal, we terminate the computation if the cost of the path is greater than or equal to {a mathematical formula}ϵ⋅(v(s)+h(s)) and set {a mathematical formula}gπ(s)=∞,π(s)=null, as s will not be truncated in this case.
       </list-item>
       <list-item label="•">
        Once a state s is truncated it is never re-inserted in OPEN during ComputePath. Therefore, we do not update the g and bp values of a truncated state while expanding other states.
       </list-item>
      </list>
     </section>
     <section label="3.4">
      <section-title>
       Theoretical properties of TLPA*
      </section-title>
      <paragraph>
       In [67], we prove a number of properties of TLPA*. Here, we discuss some of the important results. We start with a series of Lemmas describing the properties of expanded and truncated states. Later, we will use these properties to ascertain the correctness and efficiency of TLPA*. For the ease of the proofs, we assume a trivial initialization, that sets {a mathematical formula}g(s)=v(s)=gπ(s)=∞ and {a mathematical formula}bp(s)=null, {a mathematical formula}∀s∈S.
      </paragraph>
      <paragraph label="Lemma 1">
       In TLPA*, i) all v and g values are non-negative, ii){a mathematical formula}bp(sstart)=nulland{a mathematical formula}g(sstart)=0, and iii){a mathematical formula}∀s≠sstart,{a mathematical formula}bp(s)=argmin(s′∈Pred(s))v(s′)+c(s′,s)and{a mathematical formula}g(s)=v(bp(s))+c(bp(s),s).
      </paragraph>
      <paragraph label="Proof">
       The Lemma holds right after the trivial initialization, as all v and g values are ∞, and bp values are set to null. At the start, {a mathematical formula}g(sstart) is set to 0, and {a mathematical formula}bp(sstart) is set to null. Note that, g and bp of {a mathematical formula}sstart are never changed in UpdateState. Thus, {a mathematical formula}bp(sstart)=null and {a mathematical formula}g(sstart)=0, remains true throughout (ii).Now, for any state {a mathematical formula}v(s) is only altered if the state is expanded (line 25 or line 33), and in both the cases the UpdateState is called {a mathematical formula}∀s′∈Succ(s), which updates the g and bp values according to the Lemma statement (iii).As, {a mathematical formula}g(sstart) is 0 at the start, thus, {a mathematical formula}v(sstart) is set to 0 during the first expansion. As all the costs are non-negative, any subsequent assignment of g values (for a state s) through UpdateState ensures {a mathematical formula}g(s)≥0, and since {a mathematical formula}v(s) is either set to {a mathematical formula}g(s) or set to ∞, v values can never be negative (i).  □
      </paragraph>
      <paragraph label="Lemma 2">
       In TLPA*, i) OPEN and TRUNCATED are disjoint, ii) OPEN only contains the inconsistent states and{a mathematical formula}OPEN∪TRUNCATEDcontains all the inconsistent states, and iii) before each call ofComputePath, OPEN contains all the inconsistent states and TRUNCATED is empty.
      </paragraph>
      <paragraph label="Proof">
       All i), ii) and iii) are certainly true before the first call of ComputePath, as TRUNCATED is empty and OPEN only contains {a mathematical formula}sstart which is inconsistent ({a mathematical formula}g(sstart)=0,v(sstart)=∞).Now, during ComputePath whenever a state s is removed from OPEN, the following cases may occur,
       <list>
        {a mathematical formula}v(s)&gt;g(s): {a mathematical formula}v(s) is set to {a mathematical formula}g(s) (i.e., s becomes consistent), and UpdateState is called {a mathematical formula}∀s′∈Succ(s) which ensures that the resulting inconsistent states are inserted in OPEN if they are not in TRUNCATED.{a mathematical formula}v(s)&lt;g(s), and the state is expanded: {a mathematical formula}v(s) is set to ∞, and UpdateState is called for {a mathematical formula}s∪Succ(s) ensuring the Lemma statements.{a mathematical formula}v(s)&lt;g(s), and s is truncated: in this case, s is added to TRUNCATED and no other states g and v values are altered.When
       </list>
       <paragraph>
        ComputePath terminates, all the states from TRUNCATED and all the states for which the cost has potentially changed are processed through UpdateState, ensuring that the inconsistent states are inserted to OPEN, and TRUNCATED is made empty.  □
       </paragraph>
      </paragraph>
      <paragraph label="Lemma 3">
       If a state s is truncated ({a mathematical formula}s∈TRUNCATED),{a mathematical formula}v(s)is never altered during the execution ofComputePath.
      </paragraph>
      <paragraph label="Proof">
       The v value for a state is only altered when it is expanded. Now, if {a mathematical formula}s∈TRUNCATED, it cannot be selected for expansion, as the selections are made from OPEN, and OPEN and TRUNCATED are mutually disjoint (Lemma 2).  □
      </paragraph>
      <paragraph label="Lemma 4">
       InComputePath,{a mathematical formula}∀s∈TRUNCATED, there is a finite cost path from{a mathematical formula}sstartto s with cost{a mathematical formula}gπ(s), stored in{a mathematical formula}π(s).
      </paragraph>
      <paragraph label="Proof">
       We prove this by induction.Consider the first state s that gets truncated. First, note that {a mathematical formula}v(s)&lt;∞ (as {a mathematical formula}v(s)&lt;g(s)), which implies {a mathematical formula}gπ(s)&lt;∞. Now, as no other states have been truncated, {a mathematical formula}gπ(s) is computed by adding the action costs from {a mathematical formula}sstart to s following the bp pointers for each state in the path (check in line 9, Algorithm 2 is never true).Assume that the path is given by {a mathematical formula}π(s0=sstart,…,sk=s). For any state {a mathematical formula}si in this path, {a mathematical formula}bp(si)≠null and also, the path does not contain a cycle, because in both the cases {a mathematical formula}gπ(s) will be set to ∞ (line 5, Algorithm 2). The cost of every edge along this path is added to {a mathematical formula}gπ(s) (the states are added to {a mathematical formula}π(s)). Thus, when s is truncated, the path followed in {a mathematical formula}ComputeGpi(s) routine is a valid one, with cost {a mathematical formula}gπ(s), stored in {a mathematical formula}π(s).Now, let us assume that the Lemma statement holds for all prior truncation, and we will prove it for a current underconsistent state {a mathematical formula}s′ which is truncated. If the path followed by {a mathematical formula}ComputeGpi(s′) does not visit any truncated state then the Lemma is valid (from the earlier case). Whereas, if it encounters a state {a mathematical formula}s″∈TRUNCATED, we augment {a mathematical formula}gπ(s′) with {a mathematical formula}gπ(s″) and concatenate {a mathematical formula}π(s″) to {a mathematical formula}π(s′). As {a mathematical formula}s″∈TRUNCATED, {a mathematical formula}π(s″) is valid and has cost {a mathematical formula}gπ(s″) (from induction hypothesis), which means {a mathematical formula}π(s′) is valid and has cost {a mathematical formula}gπ(s′).  □
      </paragraph>
      <paragraph label="Proof">
       InComputePath, any state s selected for expansion/truncation (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 18) satisfies,{a mathematical formula}g(s)≤g⁎(s)if{a mathematical formula}v(s)≥g(s)and{a mathematical formula}v(s)≤g⁎(s)if{a mathematical formula}v(s)&lt;g(s).We prove this inductively using contradiction. The statement is true when OPEN contains only {a mathematical formula}sstart (as {a mathematical formula}g(sstart)=0=g⁎(sstart)). Let us assume that the Lemma is true for all selections prior to the current one, when the state s is selected.First, we consider the case where {a mathematical formula}v(s)≥g(s). Let us say, {a mathematical formula}g(s)&gt;g⁎(s) (which implies {a mathematical formula}g⁎(s)&lt;∞). Consider a least-cost path from {a mathematical formula}sstart to s, {a mathematical formula}π(s0=sstart,…,sk=s) with cost {a mathematical formula}g⁎(s). Such a path must exist, since {a mathematical formula}g⁎(s)&lt;∞. Our assumption, that {a mathematical formula}g(s)&gt;g⁎(s) means that there exists at least one {a mathematical formula}si∈π(s0=sstart,…,sk=s), namely {a mathematical formula}sk−1, whose {a mathematical formula}v(si)&gt;g⁎(si). Otherwise, from Lemma 1,{a mathematical formula} Let us now consider {a mathematical formula}si∈π(s0,…,sk−1) with the smallest index {a mathematical formula}i≥0, such that {a mathematical formula}v(si)&gt;g⁎(si). We first show that {a mathematical formula}g⁎(si)≥g(si). It is clearly so when {a mathematical formula}i=0 according to Lemma 1 which says that {a mathematical formula}g(si)=g(sstart)=0. For {a mathematical formula}i&gt;0, we use the fact that {a mathematical formula}v(si−1)≤g⁎(si−1) from the way {a mathematical formula}si was chosen. Now,{a mathematical formula} We thus have {a mathematical formula}v(si)&gt;g⁎(si)≥g(si), which also implies that {a mathematical formula}si∈OPEN (from Lemma 2). Note that, {a mathematical formula}si cannot be in TRUNCATED as that would mean {a mathematical formula}v(si)≤g⁎(si), because {a mathematical formula}si is selected prior to s for truncation (from induction hypothesis). Now, according to our assumption{a mathematical formula} Thus, we reach a contradiction that {a mathematical formula}Key(s)≤Key(u),∀u∈OPEN.The other case ({a mathematical formula}v(s)&lt;g(s)), can be proved in the exact same manner, considering that {a mathematical formula}Key(s) is {a mathematical formula}[v(s)+h(s);v(s)].  □
      </paragraph>
      <paragraph label="Lemma 6">
       InComputePath, any state s selected for expansion/truncation (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 18) satisfies,{a mathematical formula}min(g(s),v(s))+h(s)≤g⁎(sgoal).
      </paragraph>
      <paragraph label="Proof">
       We assume that the {a mathematical formula}g⁎(sgoal)&lt;∞, as otherwise the Lemma holds trivially. We first note that, {a mathematical formula}sgoal is never expanded in ComputePath, as whenever {a mathematical formula}sgoal has the minimum Key in OPEN, ComputePath terminates (i.e., always {a mathematical formula}v(sgoal)=∞). Let us now assume, {a mathematical formula}g⁎(sgoal)&lt;min(g(s),v(s))+h(s). At this point, {a mathematical formula}Key(s)≤Key(sgoal), as otherwise ComputePath will terminate before s is selected.Now, let us consider a least cost path from {a mathematical formula}sstart to {a mathematical formula}sgoal given as {a mathematical formula}π(s0=sstart,…,sk=sgoal). If all states {a mathematical formula}s′ in this path has {a mathematical formula}v(s′)≤g⁎(s′), then, {a mathematical formula}g(sgoal)≤g⁎(sgoal) (from Lemma 1), and therefore {a mathematical formula}Key(sgoal)≤[g⁎(sgoal);g⁎(sgoal)] (as {a mathematical formula}h(sgoal)=0). This combined with the fact that {a mathematical formula}Key(s)≤Key(sgoal), implies {a mathematical formula}g⁎(sgoal)≥min(g(s),v(s))+h(s).On the other hand, if there are some state(s) {a mathematical formula}s′∈π(s0=sstart,…,sk=sgoal), such that {a mathematical formula}v(s′)&gt;g⁎(s′), we pick the first state {a mathematical formula}si with {a mathematical formula}v(si)&gt;g⁎(si). Let us examine this state {a mathematical formula}si. If {a mathematical formula}i=0, we have {a mathematical formula}g(s0)=g⁎(s0)=0, and {a mathematical formula}v(s0)&gt;g⁎(s0), and if {a mathematical formula}i&gt;0, we have {a mathematical formula}g(si)≤v(si−1)+c(si−1,si)≤g⁎(si−1)+c(si−1,si)≤g⁎(si). Thus, for {a mathematical formula}si, if {a mathematical formula}v(si)&gt;g⁎(si), we have {a mathematical formula}g(si)≤g⁎(si), which implies {a mathematical formula}v(si)&gt;g(si) and thus {a mathematical formula}si∈OPEN (same as Lemma 5). Now,{a mathematical formula}Also,{a mathematical formula} Therefore, we reach a contradiction to the statement that {a mathematical formula}Key(s)≤Key(u),∀u∈OPEN.  □
      </paragraph>
      <paragraph label="Proof">
       InComputePath, for any overconsistent state s ({a mathematical formula}v(s)≥g(s)) selected for expansion (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 18), there is a finite cost path from{a mathematical formula}sstartto s with cost gc such that{a mathematical formula}gc+h(s)≤ϵ⋅(g(s)+h(s)). This path can be constructed using theObtainPathroutine if none of back-pointers change.We assume that {a mathematical formula}g(s)&lt;∞, otherwise the statement holds trivially. Suppose we start following the back-pointers starting at s. We need to show that we will reach {a mathematical formula}sstart at the cumulative cost of the transitions less than or equal to {a mathematical formula}ϵ⋅g(s)+(ϵ−1)⋅h(s).We first show that we are guaranteed not to encounter an underconsistent state or a state with {a mathematical formula}bp=null, that is not truncated. Suppose the back-pointers and the sequence of back-pointer transitions leads us through the states {a mathematical formula}{s0=s,s1,…,si} where {a mathematical formula}si is the first state that is either underconsistent or has {a mathematical formula}bp(si)=null (or both). It could not have been state s, since {a mathematical formula}v(s)≥g(s), from the assumptions of the theorem and {a mathematical formula}g(s)&lt;∞ implies {a mathematical formula}bp(s)≠null according to Lemma 1 (except when {a mathematical formula}s=sstart, in which case the Lemma holds trivially).We now show that {a mathematical formula}si cannot be underconsistent and not truncated by contradiction. Since all the states after {a mathematical formula}si are not underconsistent and have defined back-pointer values we have,{a mathematical formula} Now, considering the key values,{a mathematical formula} Thus, {a mathematical formula}si cannot be in OPEN as {a mathematical formula}Key(s) is the minimum, thus if {a mathematical formula}si is underconsistent {a mathematical formula}si∈TRUNCATED (from Lemma 2). Also, {a mathematical formula}bp(si) cannot be equal to null if {a mathematical formula}si is overconsistent. From our assumption that {a mathematical formula}g(s)&lt;∞ and the fact that {a mathematical formula}g(s)≥v(si)+c⁎(si,s) it then follows that {a mathematical formula}g(si) is finite. As a result, from Lemma 1, we have {a mathematical formula}bp(si)≠null unless {a mathematical formula}si=sstart. On the other hand, if {a mathematical formula}si is underconsistent we already have {a mathematical formula}si∈TRUNCATED.We are now ready to show that the cost of the path from {a mathematical formula}sstart to s defined by back-pointers is no larger than {a mathematical formula}ϵ⋅g(s)+(ϵ−1)⋅h(s). We consider two cases,
      </paragraph>
      <list>
       <list-item label="1.">
        There are no truncated state encountered by following the back-pointers from s to {a mathematical formula}sstart. In this case, let us denote the path (from {a mathematical formula}sstart) as: {a mathematical formula}{s0=sstart,s1,…,sk=s}. Since all states on this path are either consistent or overconsistent and their bp values are defined (except for {a mathematical formula}sstart), for any i, {a mathematical formula}k≥i&gt;0, we have {a mathematical formula}g(si)=v(si−1)+c(si−1,si)≥g(si−1)+c(si−1,si) from Lemma 1. For {a mathematical formula}i=0, {a mathematical formula}g(si)=g(sstart)=0 from the same Lemma. Thus, {a mathematical formula}g(s)=g(sk)≥g(sk−1)+c(sk−1,sk)≥g(sk−2)+c(sk−2,sk−1)+c(sk−1,sk)…≥Σj=1..kc(sj−1,sj). That is, {a mathematical formula}g(s) is at least as large as the cost of the path from {a mathematical formula}sstart to s as defined by the back-pointers, i.e., the path cost {a mathematical formula}gc=g(s).
       </list-item>
       <list-item label="2.">
        If following the path a truncated state {a mathematical formula}ss is reached, we denote the path from {a mathematical formula}ss to s as, {a mathematical formula}{s0=ss,s1,…,sk=s}, Since, all the states in this path are either consistent or overconsistent and their bp values are defined, for any {a mathematical formula}i,k≥i&gt;0, we have {a mathematical formula}g(si)=v(si−1)+c(si−1,si)≥g(si−1)+c(si−1,si) from Lemma 1. Thus, {a mathematical formula}g(s)=g(sk)≥g(sk−1)+c(sk−1,sk)≥g(sk−2)+c(sk−2,sk−1)+c(sk−1,sk)…≥Σj=1..kc(sj−1,sj)+v(ss). Now, for {a mathematical formula}ss∈TRUNCATED we have a stored path {a mathematical formula}π(ss) with cost {a mathematical formula}gπ(ss)≤ϵ⋅v(ss)+(ϵ−1)⋅h(ss) (from Lemma 3, Lemma 4 and truncation condition). Thus, for the total path cost (gc), we have{a mathematical formula}
       </list-item>
      </list>
      <paragraph label="Proof">
       InComputePath, for any state s, if the{a mathematical formula}ComputeGpi(s)routine returns a path of finite cost, i.e.,{a mathematical formula}gπ(s)&lt;∞, the same path can be constructed using theObtainPathroutine if none of the back-pointers change.The proof can be done using the same logic as Lemma 4. We consider two cases. First, when the ComputeGpi routine does not encounter any truncated states while traversing from s to {a mathematical formula}sstart using the back-pointers. As no truncated states are encountered, {a mathematical formula}gπ(sgoal) is computed by adding the action costs from {a mathematical formula}sstart to {a mathematical formula}sgoal following the bp pointer for each state in the path, and a finite {a mathematical formula}gπ indicates there is no null back-pointers or cycles. In the second case, if a state {a mathematical formula}s′∈TRUNCATED is encountered, {a mathematical formula}gπ(s) will be incremented using {a mathematical formula}gπ(s′) and {a mathematical formula}π(s′) will be used to construct the remaining path. As ObtainPath follows the same back-pointers as ComputeGpi the path returned will be unchanged if none of the back-pointers change.  □
      </paragraph>
      <paragraph>
       Using these Lemmas, we now prove the completeness and bounded suboptimality of TLPA*.
      </paragraph>
      <paragraph label="Proof">
       When theComputePathfunction exits, the path from{a mathematical formula}sstartto{a mathematical formula}sgoal, constructed using{a mathematical formula}ObtainPath(sgoal)has cost less than or equal to{a mathematical formula}ϵ⋅g⁎(sgoal)for a chosen{a mathematical formula}ϵ≥1.0.We assume {a mathematical formula}g⁎(sgoal)&lt;∞, otherwise the theorem is proved trivially.If ComputePath exits in the line 18, we have {a mathematical formula}g(sgoal)≤Key(u),∀u∈OPEN and {a mathematical formula}v(sgoal)≥g(sgoal). Now, from Lemma 5, we have {a mathematical formula}g(sgoal)≤g⁎(sgoal) and from Lemma 7, we have that {a mathematical formula}ObtainPath(sgoal) will return a path of cost {a mathematical formula}≤ϵ⋅g(sgoal) at this point (note that {a mathematical formula}h(sgoal)=0). Thus, the theorem holds.On the other hand, if ComputePath terminates using the condition in line 21, from Lemma 6 we have, {a mathematical formula}gπ(sgoal)≤ϵ⋅(min(g(s),v(s))+h(s))≤ϵ⋅g⁎(sgoal) (as {a mathematical formula}Key(s) is the minimum in OPEN), and from Lemma 8, we have that at this point {a mathematical formula}ObtainPath(sgoal) will return a path of cost {a mathematical formula}gπ(sgoal). Thus, the theorem holds.  □
      </paragraph>
      <paragraph>
       Next, we include two Theorems, which show that TLPA* retains the efficiency properties of LPA*. We do not discuss the proofs of these theorems as they can be proved in the exact same manner as LPA* [20] (detailed proofs can be found in [67]).
      </paragraph>
      <paragraph label="Theorem 3">
       InComputePath, no state is expanded more than twice.A state s is expanded byComputePathonly if either it was inconsistent initially or its v value was altered byComputePathat some point during its execution.
      </paragraph>
      <paragraph>
       It may be noted that while TLPA* improves the replanning runtime by truncating states, it does not guarantee that the number of state expansions will always be less than or equal to LPA*. TLPA* ensures that the number of underconsistent expansions will not be more than LPA*. However, in a pathological case, it may happen that some overconsistent states gets expanded in TLPA*, which would not be expanded in LPA* (as they will either be made consistent or have Key value greater than {a mathematical formula}g⁎(sgoal), if no state is truncated).
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Truncated D* Lite
     </section-title>
     <paragraph>
      D* Lite [21] is an incremental heuristic search algorithm for goal directed navigation through dynamic graphs that is widely used in real-life robotics applications. In this section, we present Truncated D* Lite (TD* Lite), a bounded suboptimal replanning algorithm for navigation in dynamic graphs, which combines the truncation rules with D* Lite.
     </paragraph>
     <section label="4.1">
      <section-title>
       D* Lite
      </section-title>
      <paragraph>
       D* Lite (Algorithm 4) repeatedly determines shortest paths between the current position of the robot and the goal state, as the edge costs of a graph change and the robot moves towards the goal state. It is directly based on LPA*, with the following three differences.
      </paragraph>
      <paragraph>
       Search direction: D* Lite always searches from goal state to start state. LPA* is a forward search algorithm and thus, its g and v values are estimates of the start distances.{sup:1} D* Lite searches backwards, from {a mathematical formula}sgoal to {a mathematical formula}sstart, so that the root of the search tree remains static when the robot moves. Therefore, in D* Lite, the g and v values are estimates of the goal distances, i.e., for a state s, {a mathematical formula}g(s) denotes the path cost from s to {a mathematical formula}sgoal. Similarly, the heuristic values in D* Lite denotes an admissible (and consistent) estimate for the distance between {a mathematical formula}sstart and s. We use the notation {a mathematical formula}h(sstart,s) instead of {a mathematical formula}h(s) to denote the heuristic for D* Lite. Also, in D* Lite, expansion of a state updates the state's predecessors and not the successors.
      </paragraph>
      <paragraph>
       Movement of the robot: After computing the shortest path for a given graph, D* Lite moves the robot along the computed path, as long as there is no change in the environment (line 39). If the edge costs change, D* Lite recomputes a shortest path using the latest position of the robot as {a mathematical formula}sstart. The navigation terminates when the robot reaches {a mathematical formula}sgoal.
      </paragraph>
      <paragraph>
       Avoiding heap reorder: As D* Lite moves the robot along the path computed, it needs to recalculate the priorities in OPEN when a change in edge costs occurs. Otherwise, Invariant 3 (as discussed in Section 3.1, page 53) will break, since the priorities are computed with respect to the previous {a mathematical formula}sstart. D* Lite avoids repeated reordering by adjusting the Key values following D* [26]. This is achieved in two steps. First, the priorities of the newly generated states are altered using a variable {a mathematical formula}km (line 2), which is set to 0 at initialization, and then incremented by {a mathematical formula}h(slast,sstart) before each call of ComputePath. This optimization ensures that D* Lite does need not to alter the Key values of states that already in OPEN (i.e., no reordering required), and also that the Key values of newly generated states maintain the lower bound on the total path cost (note that, {a mathematical formula}h(slast,sstart)≤c⁎(slast,sstart)). Second, within ComputePath, when a state (s) is selected for expansion, its Key is recomputed (line 20). If the current Key value is greater than {a mathematical formula}kold, the state is re-inserted into OPEN with the modified Key. This ensures that a state is only expanded when it's actual priority (Key) is a lower bound of the priority used for ordering ({a mathematical formula}kold), otherwise the state's position is updated according to it's actual priority.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Truncated D* lite algorithm
      </section-title>
      <paragraph>
       The first thing we note is that the truncation rules described in Section 3.2 are completely orthogonal to the optimizations used in D* Lite. Therefore, these rules can be directly applied to D* Lite. The TD* Lite algorithm (Algorithm 5){sup:2} precisely does that. It inherits all the D* Lite characteristics, namely, backward search, robot movement and avoidance of heap reorder; and augments it with the application of the truncation rules.
      </paragraph>
      <paragraph>
       The only significant change from TLPA* (other than searching backward) is the lower bound correction required for the optimization to avoid heap reorder (lines 18–21). In TD* Lite, the truncation rules are applied only when a state selected for expansion satisfies the lower bound (check at line 20), if not, the state is re-inserted in OPEN after updating its Key. This optimization is the same as used D* Lite, which ensures that we need not reorder the heap every time there is a change of cost and yet maintain the order invariants.
      </paragraph>
      <paragraph>
       While the application of truncation rules in TD* Lite is exactly the same as in TLPA*, the description of Rule 2 needs to be modified as the {a mathematical formula}Key1(s) values for TD* Lite are different from the values in TLPA*, due to the addition of {a mathematical formula}km. For TD* Lite, Truncation Rule 2 is applied if a state s selected for expansion, satisfies {a mathematical formula}gπ(sstart)≤ϵ⋅(min(g(s),v(s))+h(sstart,s)) (line 24).
      </paragraph>
      <paragraph>
       TD* Lite guarantees the same properties as TLPA*, i.e., it always returns a provably bounded suboptimal solution, and no state is expanded more than twice in ComputePath. These properties can be derived in exactly the same way as done for TLPA*.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Anytime Truncated D*
     </section-title>
     <paragraph>
      In this section, we discuss the modifications of the truncation rules required to make them work with inflated heuristics and show how these rules can be integrated with Anytime D* [23] algorithm to develop a truncation based anytime replanning algorithm. The motivation for combining AD* with truncated searches (TLPA*/TD* Lite) can be summarized from the following observations,
     </paragraph>
     <list>
      <list-item label="•">
       While both AD* and TLPA* provides bounded suboptimal solutions for replanning, algorithmically they adopt different directions, and thus can provide complimentary benefits (AD* uses heuristic inflation, whereas TLPA* uses truncation).
      </list-item>
      <list-item label="•">
       In AD*, inflated heuristics are only used for overconsistent states, while underconsistent use uninflated heuristics. At times, this results in accumulation of underconsistent states (in OPEN), causing performance deterioration [23]. Truncation is especially powerful for handling underconsistent states (Rule 1), as it can restrict cost propagations for majority of such states (if a good enough path to it has been discovered).
      </list-item>
      <list-item label="•">
       Performance of inflated heuristic searches like AD* can degrade considerably in presence of local minima [68], [69], due to its heuristic driven greediness. Truncation based algorithms do not rely on inflation, and thus do not suffer from this problem.
      </list-item>
     </list>
     <section label="5.1">
      <section-title>
       Anytime D*
      </section-title>
      <paragraph>
       Anytime D* (AD*) is anytime search algorithm for dynamic graphs that combines the ARA* [5] with LPA*/D* Lite [20], [21]. Following ARA*, AD* performs a series of searches with decreasing inflation factors, to iteratively generate solutions with improved bounds. If there is a change in the environment, AD* puts the resulting inconsistent states into OPEN and recomputes a bounded suboptimal path by propagating the cost changes, following LPA*/D* Lite.
      </paragraph>
      <paragraph>
       The pseudocode for a basic version of AD* is shown in Algorithm 6. The Main function first sets the inflation factor to a chosen {a mathematical formula}ϵ0, usually a high value, and generates an initial plan. Then, unless changes in edge costs are detected, it decreases the ϵ bound, and improves the quality of its solution by repeatedly executing ComputePath, until an optimal solution is found. This part of AD* is an exact match with ARA* [5].
      </paragraph>
      <paragraph>
       When changes in edge costs are detected, AD* updates the costs of affected states following Invariant 1 and puts the resulting inconsistent states in OPEN (Invariant 2). It then calls ComputePath to find a new solution. The state expansions and cost updates in AD* are similar to LPA*/D* Lite, however, it handles the priorities in a different way. AD* uses inflated heuristic values for overconsistent (and consistent) states (line 3) to provide a depth-first bias to the search. Whereas, for underconsistent states, it uses uninflated heuristic values (line 5), in order to ensure that underconsistent states correctly propagate their new costs to the affected successors. By incorporating this dual mechanism, AD* can handle arbitrary changes in the edge costs as well as changes to the inflation factor within a single algorithmic framework.
      </paragraph>
      <paragraph>
       In AD*, each call of ComputePath guarantees an ϵ suboptimal solution [23]. It also has the same efficiency properties as LPA*, i.e., no state is expanded more than twice within ComputePath and consistent states are not re-expanded.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Truncation rules with inflated heuristics
      </section-title>
      <paragraph>
       AD* and TLPA* use orthogonal approaches to compute bounded suboptimal solutions. In AD*, the path estimates are guaranteed to be within the chosen bound of {a mathematical formula}g⁎, while the actual path cost is guaranteed to be less than or equal to the estimate [23]. Whereas in TLPA*, the path estimates are always a lower bound on {a mathematical formula}g⁎, while the actual path costs lie within the chosen bound of this estimate (Lemma 5, Lemma 7, Lemma 8). Thus, it may seem that we can combine these two approaches seamlessly using two factors (say {a mathematical formula}ϵ1 and {a mathematical formula}ϵ2), one for heuristic inflation and another for truncation. If heuristic inflation ensures that the path estimates are always within {a mathematical formula}ϵ1 bound of the optimal path cost and the truncation rules ensure that the actual path costs are within {a mathematical formula}ϵ2 bound of the path estimates, we can guarantee that the solution cost will be within {a mathematical formula}ϵ1⋅ϵ2 of the optimal solution cost.
      </paragraph>
      <paragraph>
       Unfortunately, this only works for the truncation of overconsistent states, and not for underconsistent states. This is due to the fact that in AD*, heuristic values for overconsistent states are inflated, whereas an underconsistent state uses an uninflated heuristic. Therefore, when an overconsistent {a mathematical formula}s1 is selected for expansion (in AD*), we have {a mathematical formula}g(s1)≤ϵ1⋅g⁎(s1), but when an underconsistent state ({a mathematical formula}s2) is selected for expansion, there is no guarantee that {a mathematical formula}v(s2)≤ϵ1⋅g⁎(s2). Now, if we apply the truncation rule (say Truncation Rule 1) to a state s having {a mathematical formula}v(s)≥ϵ1⋅g⁎(s), the total path cost {a mathematical formula}C≤ϵ2⋅(v(s)+h(s)) does not ensure that {a mathematical formula}C≤ϵ1⋅ϵ2⋅(g⁎(s)+h(s)). Therefore, in such a case, we cannot guarantee bounded suboptimal termination.
      </paragraph>
      <paragraph>
       In Fig. 5, we present an example bound violation, when we simultaneously use heuristic inflation and truncation. Here, we use {a mathematical formula}ϵ1=2.0 and {a mathematical formula}ϵ2=1.25 (target bound 2.5). Fig. 5a shows the first iteration where a solution of cost 155 is obtained. After the first iteration, the cost of the edge from S to B changes from 50 to 0 and the cost of edge from A to D changes from 20 to 24, making B overconsistent and D underconsistent. Therefore, in AD*, {a mathematical formula}Key1(B)=g(B)+ϵ1⋅h(B)=0+2.0⋅60=120 and {a mathematical formula}Key1(D)=v(D)+h(D)=50+45=95, i.e., D is selected before B for expansion (as shown in Fig. 5b). Now, when D is selected for expansion, we have {a mathematical formula}gπ(D)=54 (path shown using dashed arrows in Fig. 5c). As, {a mathematical formula}gπ(D)+h(D)=54+45=99 and {a mathematical formula}v(D)+h(D)=95, we have {a mathematical formula}gπ(D)+h(D)≤1.25⋅(v(D)+h(D)), and thus, D is truncated using Rule 1 (Fig. 5c). In the next step, when B is expanded, a better path to D through B is discovered. However, as D is already truncated, this new path information is not propagated. Therefore, the second iteration ends after the expansion of B ({a mathematical formula}Key1(G) is the minimum Key in OPEN), returning the old path as the solution (shown using dashed arrows, Fig. 5d). Obviously, this solution violates the bounds as the current path cost (155) is more than 2.5 times the optimal path cost, which is 60 (path shown by grey arrows in Fig. 5d).{sup:3}
      </paragraph>
      <paragraph>
       From the example, we observe that if we combine the truncation rules from Section 3.2 with AD*, we may end up violating the bounds. To overcome this problem, we propose a two-step method for truncating underconsistent states.
      </paragraph>
      <paragraph>
       TruncationRule 1  As noted in Section 3.2, Rule 1 is applicable for underconsistent states only. TLPA* truncates the cost propagation for an underconsistent state s (selected for expansion), if {a mathematical formula}gπ(s)+h(s)≤ϵ⋅(v(s)+h(s)). In ATD*, when an underconsistent state s is selected for expansion for the first time, we compute its {a mathematical formula}gπ value and check whether {a mathematical formula}gπ(s)+h(s)≤ϵ2⋅(v(s)+h(s)), in the same manner as TLPA*. However, we do not truncate s immediately if this check is true. Instead, we mark s as a state that can be potentially truncated (by inserting it in a list called MARKED), postpone its cost propagation, and update its position in OPEN by altering its Key value from {a mathematical formula}Key(s)=[v(s)+h(s);v(s)] to {a mathematical formula}Key(s)=[v(s)+ϵ1⋅h(s);v(s)] (Step 1).
      </paragraph>
      <paragraph>
       If a state {a mathematical formula}s∈MARKED, is selected for expansion again as an underconsistent state ({a mathematical formula}v(s)&lt;g(s)), i.e., it is selected for expansion with the inflated heuristic Key, we truncate s (Step 2).
      </paragraph>
      <paragraph>
       Using this two-step policy, on one hand we ensure that we do not propagate cost changes for an underconsistent state (s) when it has already discovered a good enough path from {a mathematical formula}sstart. On the other hand, we cover for the fact that at this point {a mathematical formula}v(s) may be more than {a mathematical formula}ϵ1⋅g⁎(s). The updated {a mathematical formula}Key(s) guarantees that if s is selected again for expansion as an underconsistent state, we have {a mathematical formula}v(s)≤ϵ1⋅g⁎(s) and thus s can be truncated without violating the bounds. Otherwise, if {a mathematical formula}v(s)&gt;ϵ1⋅g⁎(s), s will be converted to an overconsistent state before it is selected for expansion again.
      </paragraph>
      <paragraph>
       In Fig. 6, we use the earlier example (Fig. 5) to show that how such a two-step truncation policy guarantees the suboptimality bounds. Similar to the earlier case, here also we set {a mathematical formula}ϵ1=2.0 and {a mathematical formula}ϵ2=1.25. After the first run, cost of the edge from S to B decreases from 50 to 0, whereas cost of the edge from S to A increases from 20 to 24 (Fig. 6a). The initial positions of B and D (in OPEN) are identical to Fig. 5b. Now, when D is selected for expansion (before B) in Fig. 6b, we compute {a mathematical formula}gπ(D) and note that it satisfies the truncation condition. However, unlike Fig. 5c, here we alter the Key of D (from 95 to 140) and reinsert it in OPEN (Fig. 6b). Next, when B expands, it propagates the new path information to D converting it to an overconsistent state (Fig. 6c). This cost change information is then propagated to F and G (through state expansions), computing the new solution (with cost 60) guaranteed to be within the 2.5 bound (Fig. 6d). Next, we formally state Truncation Rule 1 for ATD*.
      </paragraph>
      <paragraph label="ATD* Rule 1">
       An underconsistent state s having{a mathematical formula}Key(s)≤Key(u),∀u∈OPENand{a mathematical formula}s∉MARKEDis inserted in MARKED if{a mathematical formula}gπ(s)+h(s)≤ϵ2⋅(v(s)+h(s)), itsKeyis changed to{a mathematical formula}Key(s)=[v(s)+ϵ1⋅h(s);v(s)], and its position in OPEN is updated using the changedKey.An underconsistent state{a mathematical formula}s∈MARKEDwith{a mathematical formula}Key(s)≤Key(u),∀u∈OPENis truncated (removed from OPEN without expansion).
      </paragraph>
      <paragraph>
       TruncationRule 2  Truncation Rule 2 (as described in Section 3.2) is applicable for both underconsistent and overconsistent states. In ATD*, for an overconsistent state s, we apply this rule in unchanged manner, as for an overconsistent state {a mathematical formula}g(s)≤ϵ1⋅g⁎(s) is guaranteed. However, for an underconsistent state s, we apply Rule 2 only when it has earlier been marked ({a mathematical formula}s∈MARKED), i.e., it has been selected for expansion with the modified Key ({a mathematical formula}Key1(s)=v(s)+ϵ1⋅h(s)), as otherwise the bounds can be violated in a manner similar as discussed for Rule 1. For ATD*, Truncation Rule 2 is formulated in the following statement.
      </paragraph>
      <paragraph label="ATD* Rule 2">
       A state s having{a mathematical formula}Key(s)≤Key(u),∀u∈OPENis truncated if{a mathematical formula}gπ(sgoal)≤ϵ2⋅Key1(s)and if either{a mathematical formula}v(s)&gt;g(s)or{a mathematical formula}s∈MARKED.Also, if any state s is truncated usingRule 2, all states{a mathematical formula}s′∈OPENare truncated as{a mathematical formula}∀s′∈OPEN,Key1(s′)≥Key1(s).
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Anytime Truncated D* algorithm
      </section-title>
      <paragraph>
       Anytime Truncated D* (ATD*) augments the anytime replanning approach of AD* using the two truncation rules described in Section 5.2. It uses two constants, {a mathematical formula}ϵ1 to inflate the heuristics and {a mathematical formula}ϵ2 for truncation, and guarantees that ComputePath will return a solution within {a mathematical formula}ϵ1⋅ϵ2 factor of the optimal solution cost. We include the pseudocode for ATD* in Algorithm 7, Algorithm 8.
      </paragraph>
      <paragraph>
       ATD* uses an extra list MARKED to perform the two-step truncation. The auxiliary functions (ComputeGpi and ObtainPath) are the same as shown in Algorithm 2. However, the Key function and the truncation rules are different. The Key in ATD* provides different values depending on {a mathematical formula}v(s) and {a mathematical formula}g(s), for {a mathematical formula}v(s)≥g(s) it is same at AD*, whereas for {a mathematical formula}v(s)&lt;g(s), it uses heuristic inflation if {a mathematical formula}s∈MARKED, otherwise it uses an uninflated heuristic. For an underconsistent state, truncation is done in two phases (lines 43–59, Algorithm 7), whereas for an overconsistent state, it is same as TLPA*. Note that, ATD* does not re-expand an overconsistent state (i.e., a state {a mathematical formula}s∈CLOSED) within the ComputePath routine. If a better path to such a state s is discovered, s is put into INCONS instead. These states are put back to OPEN before the next call of ComputePath.
      </paragraph>
      <paragraph>
       The Main function for ATD* repeatedly calls ComputePath either to compute a new solution (for the first time, or when the edge costs change) or to improve an incumbent solution (after updating the bounds). After each call of ComputePath, it processes the states in lists MARKED, TRUNCATED and INCONS in an efficient manner to ensure minimal re-expansions. If the edge costs do not change, it reuses the stored paths for truncated states if they still satisfy the truncation rules with the new bounds (lines 22 and 26, Algorithm 8). The states that satisfy the current bounds are inserted to both MARKED and INCONS, others are only inserted in INCONS. All the states in INCONS are then merged with OPEN. If the edge costs change, the states in TRUNCATED are reevaluated, as their old estimates may no longer remain correct, and resulting inconsistent states are put into OPEN following the same invariants as TLPA*.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Theoretical properties of ATD*
      </section-title>
      <paragraph>
       In this section, we discuss some important theoretical properties of ATD*. Detailed proofs of these properties (and several others) are included in [70]. In general, the properties of ATD* are similar to that of TLPA* and AD*. Therefore, most of the following results can be proved in the same way as done for TLPA* (Section 3.4). We explain the cases where the results differ.
      </paragraph>
      <paragraph label="Lemma 9">
       In ATD*, all v and g values are non-negative,{a mathematical formula}bp(sstart)=null,{a mathematical formula}g(sstart)=0, and{a mathematical formula}∀s≠sstart,{a mathematical formula}bp(s)=argmin(s′∈Pred(s))v(s′)+c(s′,s)and{a mathematical formula}g(s)=v(bp(s))+c(bp(s),s)(same asLemma 1).
      </paragraph>
      <paragraph label="Lemma 10">
       In ATD*, OPEN, INCONS and TRUNCATED are disjoint and{a mathematical formula}OPEN∪INCONS∪TRUNCATEDcontains all the inconsistent states (i.e., CLOSED contains no inconsistent states). Also, before each call ofComputePath, OPEN contains all the inconsistent states and both TRUNCATED and INCONS are empty.
      </paragraph>
      <paragraph label="Proof">
       This can be proved in the same way as Lemma 2. At the start, OPEN contains all the inconsistent states. Later, when an overconsistent state is expanded, it is made consistent, removed from OPEN and added to CLOSED. If that state is made inconsistent again (decrease in g), it is added to INCONS. On the other hand, an underconsistent state is either expanded or truncated, satisfying the Lemma statement in both the cases. When ComputePath terminates, all states from TRUNCATED are processed through UpdateState if there is a cost change, otherwise they are added to INCONS. In both the cases, the states in INCONS are moved to OPEN.  □
      </paragraph>
      <paragraph label="Lemma 11">
       If a state s is truncated ({a mathematical formula}s∈TRUNCATED),{a mathematical formula}v(s)is never altered during the execution ofComputePath(same asLemma 3).
      </paragraph>
      <paragraph label="Lemma 12">
       InComputePath,{a mathematical formula}∀s∈TRUNCATED, there is a finite cost path from{a mathematical formula}sstartto s with cost{a mathematical formula}gπ(s), stored in{a mathematical formula}π(s)(same asLemma 4).
      </paragraph>
      <paragraph label="Proof">
       InComputePath, any state s selected for expansion/truncation (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 30,Algorithm 8) satisfies,{a mathematical formula}g(s)≤ϵ1⋅g⁎(s)if{a mathematical formula}v(s)≥g(s)and{a mathematical formula}v(s)≤ϵ1⋅g⁎(s)if{a mathematical formula}v(s)&lt;g(s)and{a mathematical formula}s∈MARKED.While this can be proved in the same manner as Lemma 5, we may note two significant differences. First, the g and v values are now within {a mathematical formula}ϵ1 bound of the optimal path cost ({a mathematical formula}g⁎). This stems from the use of inflated heuristic in ATD*. Therefore, in the proof, Equation (3) should be replaced by the following,{a mathematical formula}More importantly, the bound on v values is only true for underconsistent states in MARKED. The states that are not in MARKED use an uninflated heuristic, i.e., their Key is given by {a mathematical formula}[v(s)+h(s);v(s)], which will not satisfy the inequalities used in Equation (9). However, for a state {a mathematical formula}s∈MARKED, {a mathematical formula}Key(s) is modified to {a mathematical formula}[v(s)+ϵ1⋅h(s);v(s)] which ensures that the equation and subsequently the bound is satisfied.  □
      </paragraph>
      <paragraph label="Lemma 14">
       InComputePath, any state s selected for expansion/truncation (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 30,Algorithm 8) satisfies,{a mathematical formula}min(g(s),v(s))+ϵ1⋅h(s)≤ϵ1⋅g⁎(sgoal)if either{a mathematical formula}v(s)≥g(s)or{a mathematical formula}s∈MARKED.
      </paragraph>
      <paragraph label="Proof">
       Again, the proof is very similar to Lemma 6. However, note the extra qualification required for underconsistent states, due to the differential handling of Key values.  □
      </paragraph>
      <paragraph label="Proof">
       InComputePath, for any overconsistent state s ({a mathematical formula}v(s)≥g(s)) selected for expansion (i.e., if{a mathematical formula}Key(s)≤Key(u),∀u∈OPENat line 30,Algorithm 8), there is a finite cost path from{a mathematical formula}sstartto s with cost gc such that{a mathematical formula}gc+h(s)≤ϵ2⋅(g(s)+h(s)). This path can be constructed using theObtainPathroutine if none of back-pointers change.The proof is same as Lemma 7, other than the fact the ϵ in Lemma 7 is now replaced by {a mathematical formula}ϵ2.  □
      </paragraph>
      <paragraph label="Lemma 16">
       InComputePath, for any state s, if the{a mathematical formula}ComputeGpi(s)routine returns a path of finite cost, i.e.,{a mathematical formula}gπ(s)&lt;∞, the same path can be constructed using theObtainPathroutine if none of the back-pointers change (same asLemma 8).
      </paragraph>
      <paragraph label="Proof">
       Now, we state the correctness property of ATD*. When theComputePathfunction exits, the path from{a mathematical formula}sstartto{a mathematical formula}sgoal, constructed using{a mathematical formula}ObtainPath(sgoal)has cost{a mathematical formula}≤ϵ1⋅ϵ2⋅g⁎(sgoal).We assume {a mathematical formula}g⁎(sgoal)&lt;∞, otherwise the theorem is proved trivially. The proof is very similar to Theorem 1. If ComputePath exits in the line 30, we have {a mathematical formula}g(sgoal)≤Key(u),∀u∈OPEN and {a mathematical formula}v(sgoal)≥g(sgoal). Now, from Lemma 13, we have {a mathematical formula}g(sgoal)≤ϵ1⋅g⁎(sgoal) and from Lemma 15, we have that {a mathematical formula}ObtainPath(sgoal) will return a path of cost {a mathematical formula}≤ϵ2⋅g(sgoal). Thus, the theorem holds.On the other hand, if ComputePath terminates using the conditions in lines 36 or 45, from Lemma 14, we have, {a mathematical formula}gπ(sgoal)≤ϵ2⋅(min(g(s),v(s))+ϵ1⋅h(s))≤ϵ2⋅ϵ1⋅g⁎(sgoal) (as {a mathematical formula}Key(s) is the minimum in OPEN), and from Lemma 16, we have that at this point {a mathematical formula}ObtainPath(sgoal) will return a path of cost {a mathematical formula}gπ(sgoal). Thus, the theorem holds.  □
      </paragraph>
      <paragraph>
       The efficiency theorems (Theorem 2, Theorem 3), are also valid for ATD*, i.e., it never expands a state more than twice in ComputePath, neither does it expand a consistent state.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      We empirically evaluate the algorithms presented in this paper for two planning domains, 2D 16-connected grids for a point robot and 3D (x, y, heading) state lattices for PR2 robot base.{sup:4} For each domain, we generate two kinds of maps. Indoor maps, that are composed of randomly placed narrow hallways and large rooms with obstacles of various shapes, and outdoor maps, that have large open spaces with random convex obstacles. In each case, we compile a test suite of 100 maps of {a mathematical formula}1000×1000 size, with the start and goal states randomly chosen on the border. Note that these environments provide different levels of difficulties in planning [69]. Outdoor planning is relatively easier, due to high solution density and absence of large local minima. In contrast, for indoor maps, the presence of large halls and narrow pathways often create large local minima, which coupled with lower solution density makes planning more challenging. For 2D grids, we use Euclidean distance as a consistent heuristic, and for 3D lattices, we compute a consistent heuristic by running a 2D Dijkstra search after inflating the objects using the robot's (PR2 base) in-radius [69].
     </paragraph>
     <section label="6.1">
      <section-title>
       Planning in dynamic graphs: TLPA*
      </section-title>
      <paragraph>
       In this section, we compare TLPA* with a set of optimal (A* [72], LPA* [20], GAA* [32] and MPGAA* [35]) and bounded suboptimal (WA* [45] without re-expansion and GLPA* [66]) search algorithms, for planning in dynamic graphs.
      </paragraph>
      <paragraph>
       For the first experiment, after each planning episode, we randomly change the traversability of some of the cells in the map from blocked to unblocked and an equal number of cells from unblocked to blocked, and replan. The percentage of cells blocked/unblocked per iteration is input to the experiment (change rate). We iterate the replanning loop for 100 times for each change rate, and iterate the entire process for different change rates ranging from {a mathematical formula}1% to {a mathematical formula}10%.{sup:5} In Table 1 we include the results (in terms of average runtime and state expansions per planning iteration) comparing TLPA* ({a mathematical formula}ϵ=1.01,1.05,1.1) with A*, LPA* and GAA*.
      </paragraph>
      <paragraph>
       The results in Table 1 show some interesting trends. First, we note that the optimal incremental algorithms are good for low change rates (1%–2%). Beyond that, A* starts to outperform the incremental algorithms as the overhead of running incremental search starts to dominate.{sup:6} Second, we observe that the run times do not always correlate with state expansions. The incremental algorithms have extra overheads (for example, the state expansions in LPA*/MPGAA* are costlier than A*, GAA*/MPGAA* requires an additional procedure to make heuristics consistent), and thus, if the incremental algorithms do not reduce the state expansions by a fair margin, they end up using more time than A*. Finally, we note the efficacy of TLPA*, even for the small bounds used here (1.01–1.10), it consistently outperforms all optimal algorithms by a significant margin, with improvements ranging from 1.5X to 30X.
      </paragraph>
      <paragraph>
       It may be noted that in a way TLPA* delays the cost propagation (path correction) for states, in particular when it is not necessary to satisfy the bounds. This means that over the replanning iterations such states may accumulate, especially if the edge costs are increasing consistently. Therefore, it may happen that after a few iterations, there is an iteration where TLPA* needs to correct the paths for a large number of states, which of course increases the run time (of that iteration). To avoid such cases, we may periodically plan from scratch (so that such accumulations do not occur) or we may plan from scratch depending on the size of the TRUNCATED list (similar measures were suggested in [25]). In our experiments, we do not use any such modifications, i.e., we present the results as is.
      </paragraph>
      <paragraph>
       In the second experiment, we compare TLPA* with 2 bounded suboptimal algorithms, WA* and GLPA*, for ϵ ranging from 1.01–5.0 with change rate {a mathematical formula}1%. The results of this experiment is included in Table 2. From the results, we observe that TLPA* performs reasonably well across different bounds (ϵ) for both indoor and outdoor environments. We also observe that the inflated heuristic searches (WA*/GLPA*) behave differently for outdoor and indoor environments. For outdoor environments, both algorithms converge much faster with higher ϵ. Whereas for indoor environments, the improvement reduces quite a bit, and at times increasing ϵ results in degradation in runtime. This is due to the fact that in indoor environments, often there are large local minima and inflated heuristic searches tend to get trapped in those minima, thereby causing degradation.{sup:7} The impact is more severe in case of GLPA* due to its differential handling of underconsistent and overconsistent states. TLPA* does not use an inflated heuristic. Therefore, its performance remains more or less consistent for both kinds of maps. Overall, the results show that TLPA* is significantly better than both WA* and GLPA* for close-to-optimal bounds. For higher bounds, all the algorithms perform equally well for outdoor maps, however, for indoor maps, TLPA* remains a better choice as it is less sensitive toward the presence of local minima.
      </paragraph>
      <paragraph>
       In the third experiment, we test the dependence of TLPA* on the location of the cost changes. As noted in [20], [23], tree repairing searches (LPA*/GLPA*/AD*) are extremely sensitive to the position of the cost changes. If the cost changes occur close to the goal, these searches can reuse a large portion of the previous search tree and thus, are very efficient. Whereas if the changes occur close to root of the search tree, they need to rebuild most of the search tree, which considerably degrades their performance. To parameterize the experiments using the location of the cost changes, we confine {a mathematical formula}90% of the total cost changes within a chosen area around the goal state (governed by a closeness factor). For example, if closeness is 0.1, {a mathematical formula}90% of the total cost changes will take place within {a mathematical formula}10% of the total area of the map around the goal state, the rest of the map will contain the remaining {a mathematical formula}10% of the changes. We run LPA*, GLPA* (1.1) and TLPA* (1.1) with change rate {a mathematical formula}1%, varying the closeness from 0.1 to 0.9. In Fig. 7, we include the relative performance (in terms of state expansions) for these algorithms for 2D and 3D planning, on a combined set of indoor and outdoor maps. We plot the values as a ratio between the number of states expanded for a particular run, over the number of states expanded for the run with closeness 0.1.
      </paragraph>
      <paragraph>
       The figure clearly shows how sensitive LPA* is on closeness. As we increase the closeness factor, the number of state expansions increases significantly. GLPA* (1.1) is better than LPA*, as it uses an inflated heuristic which results in smaller search trees, however it still degrades quite a bit. TLPA* (1.1) is least sensitive on closeness (among these three algorithms), mainly due to two reasons. First, even if a change is close to the root, TLPA* can localize the cost propagations using truncation. More importantly, TLPA* uses both g and h to decide the truncation condition, which means it uses the total path information to arrive at a truncation decision, independent of the position of a cost change. In contrast, for LPA*/GLPA*, cost updates are done based on g values only. For example, after a cost change, LPA* will re-expand (at least once) all the states whose previous f-value is less than the optimal solution cost and whose g-value has increased, and the number of such states increases when the changes take place closer to the root of the tree. TLPA* can truncate a subset of such states if the current path estimate ({a mathematical formula}gπ+h) is within the chosen bound of the previous total path cost ({a mathematical formula}v+h). For states close to the root, h values should be higher, leading to more truncation. However, please note that the h value for a state is a lower bound on the remaining path cost and not the actual path cost. Thus, even for TLPA* changes close to the goal is better than changes close to the root.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Navigation in dynamic graphs (TD* Lite)
      </section-title>
      <paragraph>
       We evaluate TD* Lite comparing it with D* Lite with an inflated heuristic (so that the bounds provided by both algorithms are the same). We present results for two types of problems. One, in which the entire map is known to the robot at the start, it computes a plan and navigates towards the goal. However after every 50 steps, the map changes (i.e., some cells become blocked from unblocked and some become unblocked from blocked), so that the robot needs to replan. This procedure is iterated till the robot reaches its goal (known dynamic graph). And two, in which the robot only knows partially about the map (depending on its sensor range), and assumes the rest of the map to empty (free space). It plans according its current perception, and navigates towards the goal following the plan. While navigating, if it perceives any change in the graph, it replans (partially known static graph). For the first case, we use a change rate of {a mathematical formula}1% and for the second case we use a sensor range of 100 cells (the robot updates its map after 50 moves). The results for both these experiments with ϵ ranging from 1.01–5.0 are included in Table 3. Note that, here we report the total runtime and state expansions (average over 100 maps) over the entire navigation process, instead of per iteration values reported earlier.
      </paragraph>
      <paragraph>
       From the results in Table 3, we see two clear trends. For known dynamic graphs, TD* Lite is a better algorithm compared to D* Lite (with inflated heuristic), especially for low bounds and harder problems. For most values of ϵ, it converges earlier, although the improvement is not as much as observed with TLPA*. This is expected, as when the robot navigates, the search space gets smaller and smaller over iterations, reducing the scope of improvement. On the other hand, for navigation in partially known graphs with free space assumption, TD* Lite does not significantly outperform D* Lite. In fact in several cases, D* Lite performs better than TD* Lite (we depict the best results for this domain using bold letters, as there is no clear winner). This is mainly due to the fact that with the free space assumption, the changes take place very close to the goal, making D* Lite (with inflated heuristic) very fast, as only a small fraction of tree needs to be rebuilt. This also means that for TD* Lite, the scope of truncation gets reduced, making its performance almost similar to D* Lite. Another interesting thing to note is that for navigation in partially known domains, indoor planning is not necessarily harder, as now the local minima depends on the visible part of the graph rather than the actual graph.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Anytime navigation (ATD*)
      </section-title>
      <paragraph>
       In this section, we evaluate Anytime Truncated D* (ATD*) in comparison with ARA* [5], AD* [23] and ATRA* [64], for 2D and 3D (x, y, heading) navigation. We use the same domains as used for TD* Lite, i.e., known dynamic graphs and partially known static graphs. However, here we run the algorithms in anytime mode, where each planner starts by looking for a solution with high suboptimality bound and iteratively improves the solution quality by reducing the target bound until the time limit is reached (or the optimal solution is found). For each algorithm we start with a bound of 10 and iteratively reduce the bound by 0.2 after each episode. When the time limit is reached (or the optimal solution if found), the robot starts to navigate using the current until it needs to replan due to change in graphs (for the known dynamic case) or change in perception (for the unknown static case). This process is iterated till the goal is reached. Note that, unlike ARA*/AD*/ATRA*, which use a single suboptimality bound ϵ, ATD* uses two values ({a mathematical formula}ϵ1 and {a mathematical formula}ϵ2). For ATD*, we set {a mathematical formula}ϵ2=min(1.10,ϵ) and {a mathematical formula}ϵ1=ϵ/ϵ2, so that the target bound remains the same for all the algorithms. We use a time limit of 1 second for 2D planning and a time limit of 2 seconds for 3D planning.
      </paragraph>
      <paragraph>
       In Table 4, we include the results of this experiment. Note that, as the robot moves towards the goal, the search space gets iteratively smaller. Which means the later episodes are generally easier to solve. For this reason, here, we do not report the average bounds over all iterations. Instead, we pick the worst 5 bounds reported over all iterations and take the average of that. The results highlight the efficacy of ATD* over other algorithms. For almost all the cases, ATD* reports a better bound and achieves a better quality solution, with the difference getting more pronounced for known dynamic graphs, especially in case of indoor navigation. The primary reason for this is the fact that while all the other algorithms rely on inflated heuristics to speedup search, ATD* can use both heuristic inflation and truncation, and thus, is more robust. Another thing to note here is that for known dynamic graphs ARA* and ATRA* both perform quite well, whereas for partially known graphs AD* and ATD* consistently produce better bounds compared to WA*/ATRA*, primarily due to the localization of changes, close to the goal state. Finally, we observe that all the algorithms produce relatively high quality (close-to-optimal) solutions within the chosen time limits, which shows the utility of anytime planning.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>