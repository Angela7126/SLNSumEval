<html>
<head>
<meta name="TextLength" content="SENT_NUM:35, WORD_NUM:702">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we deal with the multi-agent pathfinding problem (MAPF).</a>
<a href="#1" id="1">We provided a short survey on previous work on the MAPF problem, introducing a categorization that helps classify all previous work to the following classes:</a>
<a href="#2" id="2">Optimal solvers [45], [15], [42], [38], [39] Sub-optimal search-based solvers [43], [12] Sub-optimal procedure-based solvers [9], [30], [25], [37], [10] Sub-optimal hybrid solvers [52], [24], [53], [35]</a>
<a href="#3" id="3">Next, the CBS algorithm was introduced.</a>
<a href="#4" id="4">CBS is a novel optimal MAPF solver.</a>
<a href="#5" id="5">CBS is unique in that all low-level searches are performed as single-agent searches, yet it produces optimal solutions.</a>
<a href="#6" id="6">The performance of CBS depends on the structure of the problem.</a>
<a href="#7" id="7">We have demonstrated cases with bottlenecks (Fig. 1, Section 2.7) where CBS performs well, and open spaces (Fig. 6, Section 5.3.2) where CBS performs poorly.</a>
<a href="#8" id="8">We analyzed and explained these cases and how they affect CBS's performance.</a>
<a href="#9" id="9">We then turned to present the MA-CBS framework, a generalization of the CBS algorithm.</a>
<a href="#10" id="10">MA-CBS can be used on top of any MAPF solver, which will be used as a low-level solver.</a>
<a href="#11" id="11">Furthermore, MA-CBS can be viewed as a generalization of the Independence Detection (ID) framework introduced by Standley [45].</a>
<a href="#12" id="12">MA-CBS serves as a bridge between CBS and other optimal MAPF solvers, such as A*, {a mathematical formula}A*+OD[45] and EPEA* [15].</a>
<a href="#13" id="13">It starts as a regular CBS solver, where the low-level search is performed by a single agent at a time.</a>
<a href="#14" id="14">If MA-CBS identifies that a pair of agents conflicts often, it groups them together.</a>
<a href="#15" id="15">The low-level solver treats this group as one composite agent, and finds solutions for that group using the given MAPF solver (e.g., A*).</a>
<a href="#16" id="16">As a result, MA-CBS is flexible and can enjoy the complementary benefits of both CBS and traditional optimal solvers by choosing when to group agents together.</a>
<a href="#17" id="17">As a simple yet effective mechanism for deciding when to group agents, we introduced the conflict bound parameter B. The B parameter corresponds to the tendency of MA-CBS to create large groups of agents and solve them as one unit.</a>
<a href="#18" id="18">When {a mathematical formula}B=0 MA-CBS converges to ID and when {a mathematical formula}B=∞ MA-CBS is equivalent to CBS.</a>
<a href="#19" id="19">Setting {a mathematical formula}0<B<∞ gives MA-CBS flexibility, so that in cases where only few conflicts occur, MA-CBS can act like CBS, while if conflicts are common, MA-CBS can converge to a single meta-agent problem that includes all or most of the conflicting agents.</a>
<a href="#20" id="20">Experimental results in testbed map problems support our theoretical claims.</a>
<a href="#21" id="21">The domains presented have different rates of open spaces and bottlenecks.</a>
<a href="#22" id="22">MA-CBS with a high B value (100, 500) outperforms other algorithms in cases where corridors and bottlenecks are more dominant.</a>
<a href="#23" id="23">In addition, experimental results showed that MA-CBS with non-extreme values of B (i.e., neither {a mathematical formula}B=0 nor {a mathematical formula}B=∞) outperforms both CBS and other state-of-the-art MAPF algorithms.</a>
<a href="#24" id="24">The results lead to the conclusion that in the general case, it is most beneficial to group agents to a certain extent.</a>
<a href="#25" id="25">This results in a faster solving process when compared to never grouping agents, as in CBS, and to grouping all agents, as in all previous optimal solvers.</a>
<a href="#26" id="26">There are many open challenges for work on MAPF in general as well as on the CBS and MA-CBS algorithms:</a>
<a href="#27" id="27">Currently no heuristic guides the search in the high-level constraint tree.</a>
<a href="#28" id="28">Coming up with an admissible heuristic for the high level could potentially result in a significant speed up.</a>
<a href="#29" id="29">Further work could be done to understand the effect of the B parameter on MA-CBS, which might give insight into how B could be varied dynamically.</a>
<a href="#30" id="30">Using a single B parameter for merging agents is relatively simple; it is an open question whether more sophisticated merging policies could significantly improve performance.</a>
<a href="#31" id="31">For instance, merging might be based on areas of the map instead of on individual agents.</a>
<a href="#32" id="32">Following Ferner et al. [17] it would be valuable to experiment and compare different low-level solvers including ICTS [42], ODrM* [17], Boolean Satisfiability (SAT) [50], Integer Linear Programming (ILP) [55] and Answer Set Programming (ASP) [13].</a>
<a href="#33" id="33">On a larger scale, the use of constraints overlaps with work on CSP and SAT, a connection that has not been well-explored.</a>
<a href="#34" id="34">There are theoretical connections between these fields [33] that need more study.</a>
</body>
</html>