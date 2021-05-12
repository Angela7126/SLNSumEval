<html>
<head>
<meta name="TextLength" content="SENT_NUM:29, WORD_NUM:797">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have addressed the problem of designing mechanisms to fairly allocate indivisible goods to a set of agents.</a>
<a href="#1" id="1">While previously this question has been mostly investigated in the context of assignment problems, in which agents can receive at most one such good [6], the domain considered here is combinatorial: agents may receive more than one object and have preferences over the possible sets of goods that they may receive.</a>
<a href="#2" id="2">Unlike for other proposals in which payments ensuring fairness are arranged for a given efficient allocation [33], [34], the approach advocated here is distributed: agents locally implement mutually beneficial reallocations of goods (furthering the efficiency of the allocation), while the payment rule updates the payments after each deal in a way that ensures fairness at the end of the process.</a>
<a href="#3" id="3">That is, in this approach the quests for efficiency and fairness are intimately interleaved.</a>
<a href="#4" id="4">The first contribution of this paper has been to provide simple conditions under which any sequence of such reallocative steps can be guaranteed to converge to a fair outcome.</a>
<a href="#5" id="5">The fairness criteria considered are proportionality and envy-freeness.</a>
<a href="#6" id="6">As the problem is combinatorial in nature, the approach necessitates that agents can potentially agree on complex deals, and the process itself can involve a large number of steps.</a>
<a href="#7" id="7">If we assume, however, that preferences are modular (additive), then negotiation can be conducted by means of very simple deals, and the length of the process will be linearly bounded [29].</a>
<a href="#8" id="8">Note that the proposed mechanism never requires heavy central computation: only some simple redistribution of the social surplus (in terms of money) is performed at the global level.</a>
<a href="#9" id="9">Theorem 4 demonstrates that the classical Knaster procedure can be given a distributed flavour and still achieve proportional outcomes.</a>
<a href="#10" id="10">Theorem 8 shows that envy-free outcomes can be negotiated in a distributed manner, at least when the agents have supermodular preferences.</a>
<a href="#11" id="11">The discussion which follows our exposition of this last result demonstrates the limitations of the approach, by showing that the result does not generalise to a wider class of preferences (Theorem 9) or different types of payment schemes (Theorem 10).</a>
<a href="#12" id="12">Having established these results, we turned our attention to a situation of great practical relevance, namely societies of agents where the information available to agents is constrained by a social network.</a>
<a href="#13" id="13">Interestingly, we saw that, while the notion of proportionality was difficult to characterise in a meaningful manner, envy can naturally be restricted to agents that can be “seen” from an agent's position in the network.</a>
<a href="#14" id="14">Such topological constraints can be very damaging as far as efficiency is concerned, which suggests that it could potentially jeopardise also the possibility of reaching envy-free states.</a>
<a href="#15" id="15">Theorem 14 shows that this is not the case: a weaker (localised) notion of efficiency is sufficient to guarantee convergence to envy-free states on graphs.</a>
<a href="#16" id="16">While this result assumes that negotiation and envy are constrained by the same graph, an interesting lead for future research would be to relax this assumption.</a>
<a href="#17" id="17">Typically, the negotiation graph would be a subgraph of the envy graph, so convergence to fair outcomes will be more difficult to guarantee.</a>
<a href="#18" id="18">For all of our convergence results we have also provided corresponding results for the special case of agents with modular preferences.</a>
<a href="#19" id="19">In these cases, convergence can be achieved by means of individually rational deals involving only a single item at a time (Theorem 5, Theorem 11, Theorem 15).</a>
<a href="#20" id="20">By construction (and following Lemma 3), the proposed mechanisms enjoy an “anytime behaviour” as far as efficiency is concerned.</a>
<a href="#21" id="21">That is, efficiency is guaranteed to improve monotonically as negotiation progresses.</a>
<a href="#22" id="22">The situation is less clear when it comes to envy, first of all because there is no standard way of quantifying “how much” envy occurs in a society.</a>
<a href="#23" id="23">We have addressed this question by proposing a systematic typology of envy measures as well as a set of basic axioms that should be met by any such measure.</a>
<a href="#24" id="24">Equipped with these envy measures, it will be possible to investigate how envy within a society evolves over time when negotiation takes place.</a>
<a href="#25" id="25">For example, experiments reported in related work [1] suggest that envy tends to decrease, albeit not strictly monotonically.</a>
<a href="#26" id="26">More generally, these measures of envy allow us to go beyond a mere classification of a society as being either envy-free or not.</a>
<a href="#27" id="27">In particular, while some of the conditions stated in our convergence theorems are necessary to guarantee full envy-freeness in all cases, it would be interesting to investigate by how much envy can be decreased when not all of these conditions are met.</a>
<a href="#28" id="28">Finally, we have shown that the local decision problem faced by agents when they have to agree on a rational deal that reduces envy is computationally intractable (Theorem 18), albeit not harder than identifying an arbitrary rational deal.</a>
</body>
</html>