<html>
<head>
<meta name="TextLength" content="SENT_NUM:27, WORD_NUM:800">
</head>
<body bgcolor="white">
<a href="#0" id="0">The AI community is expressing the need to put more effort in investigating principled ways of integrating planning and acting (and hence programs) [47].</a>
<a href="#1" id="1">In this paper we have studied the notion of agent planning programs, which is much in line with this need.</a>
<a href="#2" id="2">Agent planning programs are (finite-state) programs whose atomic instructions consist of precondition-invariance-postcondition assertions.</a>
<a href="#3" id="3">These programs need to be compiled into executable ones by replacing such assertions with plans that, under the guarantee that the precondition is satisfied, maintain the invariance condition and achieve the postcondition.</a>
<a href="#4" id="4">The key point is that these plans cannot be computed in isolation, since once a goal (postcondition) has been achieved, new precondition-invariance-postcondition triples need to be fulfilled as prescribed by the program.</a>
<a href="#5" id="5">We have shown a general solution for such programs and characterized the complexity of the problem.</a>
<a href="#6" id="6">Interestingly, the general solution proposed, which is optimal from the computational complexity point of view, can be implemented directly using game-structure model-checking based synthesis tools such as the mentioned TLV, JTLV and NuGaT, but also Anzu[60] or Ratsy[10].</a>
<a href="#7" id="7">This general solution has the flavor of universal plans, but may involve more work than really needed.</a>
<a href="#8" id="8">Focusing on deterministic domains, we have developed an iterated-classical-planning technique that exploits goal preferences and plan adaptation methods to speed up the realization of transitions in cycles.</a>
<a href="#9" id="9">We have tested this technique through an array of experiments, demonstrating that the planning-based approach as a whole is an effective way to practically handle agent planning programs in deterministic domains (observe, though, that while we used some well-known domain-independent planners, the aim of such experiments was not to show the goodness of a specific planner or encoding, and other planners could have been used).</a>
<a href="#10" id="10">This is especially the case with planning domains whose state spaces have limited deadends.</a>
<a href="#11" id="11">There are several further research avenues to explore related to this mix of planning and programming that agent planning programs provide.</a>
<a href="#12" id="12">We mention here some of them at the extremes of the spectrum.</a>
<a href="#13" id="13">On the one hand, a crucial issue that we did not address in this paper is devising convenient representation formalisms for agent planning programs.</a>
<a href="#14" id="14">Indeed, we have simply used transition systems in the present work, which can be considered a general but possibly too pristine formalism for describing dynamic systems.</a>
<a href="#15" id="15">When it comes to applications, better representation formalisms—in the style of those developed in reasoning about action—are preferred.</a>
<a href="#16" id="16">For example, one could resort to variants of high-level agent programming languages like Golog/ConGolog/IndiGolog for expressing agent planning programs.</a>
<a href="#17" id="17">Notice though that, as discussed in Section 7, one cannot simply adopt their standard computational semantics, and a new sort of off-line semantics would be needed that takes into account the realization of planning programs as discussed in this paper, possibly extended to deal with first-order representation of data giving rise to infinite-state domains.</a>
<a href="#18" id="18">Pushing this line even further, one could consider allowing recursive procedure calls in the planning program, making the planning program itself infinite state (due to the need of, e.g., an unbounded stack for dealing with multiple procedure activations).</a>
<a href="#19" id="19">Recent work on decidable verification of situation calculus [30], [31], [32] and other data-aware process formalisms [7], [51] becomes very relevant for this kind of research.</a>
<a href="#20" id="20">At the other end of the spectrum, we are interested in improving and extending implementations based on planning techniques.</a>
<a href="#21" id="21">First of all, we would like to generalize the technique presented here to nondeterministic domains (possibly using conditional or conformant planners), as well as to introduce measures and techniques to compute optimized program realizations.</a>
<a href="#22" id="22">With respect to the latter, one would aim at obtaining plans that are not only good from the computational point of view, but also (or alternatively sometimes) from an engineering point of view by maximizing qualities such as understandability, robustness, and modifiability.</a>
<a href="#23" id="23">When it comes to planning programs over deterministic domains, we intend to optimize the performance of the algorithm proposed in Section 5 by including heuristics and techniques that take subsequent transitions into account more effectively (when realizing a particular transition), in order to reduce backtracking by avoiding plans that create open pairs from which a next transition cannot be realized.</a>
<a href="#24" id="24">We expect these advanced techniques will be helpful especially for programs over planning domains where our current technique can incur in a high number of backtracks.</a>
<a href="#25" id="25">We would also like to draw from the recent work on HGN-planning (and associated planning systems like GoDeL[94]), which, as mentioned above, exploits goal decomposition and landmarks to solve classical planning on a network of goals, albeit under a different semantics.</a>
<a href="#26" id="26">Finally, an interesting and challenging direction concerns addressing the realization of dynamic planning programs—programs in which states or transitions can be added or removed dynamically, and the preconditions-invariance-postconditions of the transitions can be incrementally revised—without always recomputing a new realization from scratch.</a>
</body>
</html>