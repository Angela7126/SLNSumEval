<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:612">
</head>
<body bgcolor="white">
<a href="#0" id="0">NDP2, like the earlier NDP algorithm [30], solves nondeterministic planning problems by calling a classical planner on a sequence of deterministic planning problems, and using the classical planner's plans to construct a strong cyclic solution policy for the nondeterministic problem.</a>
<a href="#1" id="1">However, in order to avoid NDP's difficulties with unsoundness and combinatorial explosion in the presence of unsolvable states, NDP2 has a different (and provably correct) way of dealing with unsolvable states.</a>
<a href="#2" id="2">We also have provided algorithms to translate a planning problem P into two different “abstract” versions of P in which there are states that represent sets of P's states.</a>
<a href="#3" id="3">These overcome another limitation of [30], which described a similar “conjunctive abstraction” technique without providing an algorithm to compute it.</a>
<a href="#4" id="4">The well-known MBP planner uses BDDs to compute abstractions that are significantly more powerful than ours—but since our abstractions do not use BDDs, they preserve NDP2's ability to be used with any classical planner.</a>
<a href="#5" id="5">NDP2's primary advantage over MBP is that MBP uses none of the sophisticated search heuristics used in classical planners, hence can sometimes visit many more states than it needs to.</a>
<a href="#6" id="6">Since NDP2 uses a classical planner as a subroutine, the classical planner's search heuristics can sometimes help NDP2 to visit significantly fewer states than MBP.</a>
<a href="#7" id="7">This happened in the Robot Navigation domain and the Nondeterministic Blocks World, where NDP2 did much better than MBP.</a>
<a href="#8" id="8">NDP2's main disadvantage compared to MBP is that in many of the cases where MBP's BDDs can represent a set of states as a single abstract state, our abstraction algorithms cannot do so.</a>
<a href="#9" id="9">Thus there are cases where NDP2 must plan for different states separately but MBP can plan for the entire set of states at once.</a>
<a href="#10" id="10">This happened in our Hunter–Prey experiments, where MBP performed much better than NDP2.</a>
<a href="#11" id="11">Our experimental results with Exploding Blocks World, Tire World, and Lost in Space showed that NDP2's technique for avoiding unsolvable states works quite well: NDP2 completed nearly every problem that MBP completed, and many more that MBP could not complete.</a>
<a href="#12" id="12">In the Exploding Blocks World and Lost in Space domain, where both planners completed enough problems to compare speed, NDP2 completed large problems much faster than MBP.</a>
<a href="#13" id="13">Since MBP's BDD-based abstractions give it an advantage in some cases, and NDP2's access to classical search heuristics gives it an advantage in other cases, it might be possible to obtain better performance than both MBP and NDP2 by writing an NDP2-like planner that incorporates an FF-like algorithm operating over BDDs, or by finding other ways to combine BDDs and relaxed planning graphs.</a>
<a href="#14" id="14">Existing work such as [7] has already investigated ways to combine planning graphs and BDDs, but these approaches typically require complicated and potentially exponential representations due to the mutex conditions in planning graphs, which degrade the abstraction capabilities in BDDs.</a>
<a href="#15" id="15">Since FF's relaxed planning graphs do not include mutex conditions, they might be a better fit for BDDs.</a>
<a href="#16" id="16">Further improvements may also be achievable by coupling NDP2 and FF more tightly.</a>
<a href="#17" id="17">When NDP2 calls FF, it must wait until FF reaches a goal.</a>
<a href="#18" id="18">If we could intervene to stop FF as soon as it reaches a state that is already part of NDP2's current partial solution, this would provide a substantial speedup because it would prevent FF from wasting time retracing large parts of the solutions that it found during the previous times NDP2 called it.</a>
<a href="#19" id="19">We note that some MDP planning algorithms (e.g., LAO* [19]) can generate cyclic solution policies.</a>
<a href="#20" id="20">With proper modifications to these planners and their inputs, it would be interesting to compare them with NDP2 and classical planners.</a>
<a href="#21" id="21">This may provide a path toward developing an NDP2-like algorithm for MDPs.</a>
</body>
</html>