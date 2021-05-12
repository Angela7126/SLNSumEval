<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:555">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article we have proved that the plan existence problem is PSPACE-complete when restricted to instances with acyclic causal graphs.</a>
<a href="#1" id="1">Our proof is largely based on one conceptually simple idea: non-deterministic choices can be replaced by enumerating all possible choices.</a>
<a href="#2" id="2">Implementing this idea in such a weak “programming language” as propositional planning is non-trivial, though, and our solution is based on making several counters to interact in complex ways.</a>
<a href="#3" id="3">It is not surprising that the planning instance constructed in the reduction has a causal graph that is complicated and difficult to characterize in graph-theoretical terms.</a>
<a href="#4" id="4">Hence, it may be worthwhile to try to obtain alternative proofs that leads to instances with different (and hopefully simpler) causal graphs.</a>
<a href="#5" id="5">An interesting question along these lines is the following: let Pe{a mathematical formula}(C) denote the plan existence problem restricted to instances such that their casual graphs are members of {a mathematical formula}C, and let {a mathematical formula}Cn denote the directed chain on n vertices.</a>
<a href="#6" id="6">Now, is it the case that Pe{a mathematical formula}({C1,C2,…}) is PSPACE-complete?</a>
<a href="#7" id="7">It is known that Pe{a mathematical formula}({C1,C2,…}) is NP-hard even if the variable domains are restricted to five elements [10] but there are no results yet indicating that this problem is indeed harder.</a>
<a href="#8" id="8">We may take this idea one step further and try to fully characterize the sets of graphs {a mathematical formula}C such that Pe{a mathematical formula}(C) is PSPACE-complete.</a>
<a href="#9" id="9">This may appear to be an overly difficult problem but it should not be deemed completely hopeless: recall that Chen and Giménez [15] have, under the complexity-theoretic assumption that nu-FPT ≠ W[1], exactly characterized the sets of graphs {a mathematical formula}C such that Pe{a mathematical formula}(C) is in P. Hence, their result may be viewed as a characterization of the problems in the “easy” end of the hardness spectrum while a characterization of the PSPACE-complete problems would be a summary of the other end of the spectrum.</a>
<a href="#10" id="10">We also note that their result leaves room for significant improvements since they only prove that sets of graphs that do not satisfy the tractability condition are not in P. In fact, there exists a set of graphs {a mathematical formula}C such that Pe{a mathematical formula}(C) is NP-intermediate, i.e. Pe{a mathematical formula}(C) is not in P and Pe{a mathematical formula}(C) is not NP-hard.</a>
<a href="#11" id="11">Clearly, a characterization of the PSPACE-complete graphs (and also of the X-complete graphs for other complexity classes X within PSPACE) would be an interesting refinement of their result, and there exists work in this direction in the literature [17].</a>
<a href="#12" id="12">We finally note that it may be much easier to study sets of acyclic graphs instead of general graphs.</a>
<a href="#13" id="13">The following could be a first step: identify the sets of acyclic graphs {a mathematical formula}C such that Pe{a mathematical formula}(C) is NP-complete without imposing any other constraints on, for instance, domain sizes?</a>
<a href="#14" id="14">Examples exist in the literature [3] but they are scarce.</a>
<a href="#15" id="15">However, recall that if we allow other side constraints (such as restricting domain sizes or otherwise put restrictions on the DTGs), then there are plenty of examples in the literature.</a>
<a href="#16" id="16">Examples include directed-path singly connected causal graphs with domain size two [6].</a>
<a href="#17" id="17">Naturally, this kind of studies can be performed with other complexity classes in mind—probably, the most interesting result would be to characterize the acyclic graphs that make Pe tractable.</a>
</body>
</html>