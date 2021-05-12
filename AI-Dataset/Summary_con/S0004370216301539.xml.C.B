<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:269">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper addresses planning problems in which the domain models are incompletely specified.</a>
<a href="#1" id="1">We study planning situations when the domain model is annotated with possible preconditions and effects (in addition to the known preconditions and effects).</a>
<a href="#2" id="2">The solution concept for planning problems with incomplete domain models is introduced with the notion of plan robustness.</a>
<a href="#3" id="3">It is computed with the set of candidate complete models under which the plan succeeds, thus correctly captures the probability of plan success.</a>
<a href="#4" id="4">This work considers two execution semantics for plans: the Generous Execution and STRIPS Execution semantics.</a>
<a href="#5" id="5">The difference between the two semantics is how an action's failure affects plan execution.</a>
<a href="#6" id="6">The problem of assessing plan robustness is also considered and shown to be #P-complete.</a>
<a href="#7" id="7">Two approaches are considered for synthesizing robust plans—the compilation approach and the heuristic search approach.</a>
<a href="#8" id="8">While the first one is more intuitive, its performance appears to be limited to small planning instances only.</a>
<a href="#9" id="9">The heuristic approach is much more scalable, and in this work we fully develop it under the STRIPS semantics, exploiting the structures of plan correctness constraints in order to approximate robustness measures.</a>
<a href="#10" id="10">These approximations are then used during the extraction of robust relaxed plans to estimate the heuristic distance to goals.</a>
<a href="#11" id="11">The resulting planner, PISA, outperforms a state-of-the-art planner, DeFault [31], in both plan quality and planning time.</a>
<a href="#12" id="12">Finally, we also present an extension of PISA called {a mathematical formula}CPISA that is able to leverage successful plan traces to further improve robustness.</a>
<a href="#13" id="13">{a mathematical formula}CPISA also shows how such traces can be used to reduce the dependence on the domain expert for specifying possible precondition/effect annotations.</a>
</body>
</html>