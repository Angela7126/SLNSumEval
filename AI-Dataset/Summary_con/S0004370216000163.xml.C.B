<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:551">
</head>
<body bgcolor="white">
<a href="#0" id="0">Planning for real-world applications is difficult, primarily due to the inherent uncertainties in world models.</a>
<a href="#1" id="1">Such models often have imperfect information and thus, the models and the plans obtained using them need to be updated, when the system receives new information.</a>
<a href="#2" id="2">Moreover, even if the model is accurate, the world may change, making the earlier plans invalid.</a>
<a href="#3" id="3">Incremental search algorithms efficiently solve such repeated planning problems by effectively reusing the previous searches.</a>
<a href="#4" id="4">In addition to the inherent uncertainties, often a planning problem is so complex that finding optimal solutions becomes infeasible under reasonable resource (time/memory) constraints.</a>
<a href="#5" id="5">Anytime algorithms are suitable for such cases, as they offer the flexibility to reason about the quality-resource trade-off.</a>
<a href="#6" id="6">Combination of these requirements (incremental and anytime) makes planning for real-world tasks a challenging area of research.</a>
<a href="#7" id="7">We contribute to this research by developing three new algorithms for replanning.</a>
<a href="#8" id="8">We propose a novel method called truncation, that enables an incremental search to selectively re-expand states that can significantly impact the solution quality and reuse the previous values for other states, and thus, can improve the replanning runtime significantly when searching for solutions within a chosen suboptimality bound.</a>
<a href="#9" id="9">We describe two simple rules for truncation, and show how these can be used to convert LPA* to Truncated LPA* (TLPA*), a bounded suboptimal replanning algorithm.</a>
<a href="#10" id="10">We discuss the properties of TLPA*, proving its correctness, and experimentally demonstrate its efficacy for 2D and 3D (x, y, heading) planning.</a>
<a href="#11" id="11">In addition, we apply the truncation rules on D* Lite, to develop Truncated D* Lite (TD* Lite), a bounded suboptimal incremental search for navigation.</a>
<a href="#12" id="12">We also develop a novel anytime incremental search, Anytime Truncated D* (ATD*), that combines the inflated heuristic search with truncation in an anytime manner.</a>
<a href="#13" id="13">We explain why the truncation rules used in TLPA* cannot be directly used with inflated heuristics, and propose two new truncation rules to rectify this problem.</a>
<a href="#14" id="14">We discuss the analytical properties of ATD* and experimentally evaluate its performance in comparison with state-of-the-art anytime incremental searches.</a>
<a href="#15" id="15">The empirical evaluations presented in this paper suggest that the utility of incremental planning depends on the complexity of the problem.</a>
<a href="#16" id="16">If the planning task is complex (where planning a path from scratch requires substantial effort), effective reuse of the previous planning information can significantly improve the runtime, making incremental replanning effective.</a>
<a href="#17" id="17">In contrast, when planning is relatively easy, the overheads associated with incremental replanning can at times become prohibitive.</a>
<a href="#18" id="18">In a way, our experiments reinforce the observations described in [73].</a>
<a href="#19" id="19">Interestingly, when incremental planning is effective, truncated incremental searches can significantly improve efficiency by enhancing the scope of information reuse.</a>
<a href="#20" id="20">All the algorithms proposed in this work are reasonably simple to implement and extend, are theoretically well-founded and (to our belief) provide significant advantage over the current state-of-the-art, especially for large, complex problems.</a>
<a href="#21" id="21">Also, while we have presented the algorithms in this paper as heuristic search algorithms, the truncation methodology is generic enough to work seamlessly for uninformed searches (by setting the heuristic to zero) to compute fast bounded suboptimal shortest paths in dynamic graphs.</a>
<a href="#22" id="22">Note that, this is not possible with algorithms like GLPA* or AD*, which rely on heuristic inflation to provide bounded suboptimal solutions.</a>
<a href="#23" id="23">As such, we hope they will contribute to and motivate other researchers developing search algorithms for complex and dynamic real-world applications.</a>
</body>
</html>