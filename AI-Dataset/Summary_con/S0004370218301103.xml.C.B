<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:366">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper proposed the SPR process, a sound and complete process in which it is possible to query whether a chosen plan is part of the correct hypothesis, and subsequently remove all incorrect plans from the hypothesis set.</a>
<a href="#1" id="1">It defined the SPR problem, with the goal is to minimize the number of queries to converge to the minimal hypothesis set that can be refined to the correct hypothesis.</a>
<a href="#2" id="2">We presented a number of approaches for choosing a plan to query – the plan that maximizes the expected information gain, as well as the plan that is ranked highest in terms of likelihood by the PR algorithm.</a>
<a href="#3" id="3">We evaluated these approaches on two domains from the literature, showing that both were able to converge to the correct hypothesis using significantly less queries than a random baseline, with the maximal information gain technique exhibiting a clear advantage over all approaches.</a>
<a href="#4" id="4">We also showed that using subplans, we may be able to make the querying process more efficient in some cases.</a>
<a href="#5" id="5">We presented empirical settings using different domain configuration and discussed the impact of each of them when using the SPR process.</a>
<a href="#6" id="6">We chose a simple protocol between the recognizer and observed agent (a query and a yes/no response).</a>
<a href="#7" id="7">We also assume perfect answers to a query.</a>
<a href="#8" id="8">Future work will consider richer queries, such as asking for more information from the observed agent.</a>
<a href="#9" id="9">To this end we intend to combine optimization approaches from dialogue and interruption management [59], [46], [29].</a>
<a href="#10" id="10">We also intend to consider non-uniform query costs.</a>
<a href="#11" id="11">We intend to run the SPR algorithm in online domains such as intelligently querying students about their solution strategy in the virtual labs system in a way that minimizes the disruption.</a>
<a href="#12" id="12">We also wish to develop machine learning models for predicting whether a given plan belongs to the correct hypothesis.</a>
<a href="#13" id="13">We used a plan library as the domain description for SPR.</a>
<a href="#14" id="14">We also intend to adapt our approach to other domain representations such as domain theory [44], [52].</a>
<a href="#15" id="15">Lastly, in future work we will design more sophisticated query policies that employ look ahead.</a>
<a href="#16" id="16">To this end we are working on a compact representation of a state space for using the MDP.</a>
</body>
</html>