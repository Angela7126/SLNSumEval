<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:540">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have studied the problem of scheduling a set of shared EVs in an MoD scheme and initially characterize the problem as a max flow one to determine the set of feasible tasks, given the available EVs at each location.</a>
<a href="#1" id="1">Later, we proposed an MIP formulation to solve it optimally.</a>
<a href="#2" id="2">Given that this solution scales only up to medium sized problems, we also proposed two non-optimal algorithms.</a>
<a href="#3" id="3">The first one is an incremental MIP solution, which calls the MIP incrementally for each EV.</a>
<a href="#4" id="4">The second is a greedy scheduling algorithm which scales up to thousands of tasks and EVs.</a>
<a href="#5" id="5">Finally, we developed a tabu search-based local search technique to improve the solution quality of the non-optimal algorithms.</a>
<a href="#6" id="6">In all cases, either battery swap or battery charge is used to cope with EVs' limited range.</a>
<a href="#7" id="7">In our experiments, we observe that when all EVs carry the same battery which is large enough for the longest trips, the greedy algorithm with battery swap in combination with the max flow provides the optimal solution.</a>
<a href="#8" id="8">At the same time, the variation with battery charge is close to the optimal and is further slightly improved when local search is used.</a>
<a href="#9" id="9">When some EVs do not have a large enough battery to execute some of the longest trips, the incremental MIP generates solutions slightly better than the greedy, while the optimal algorithm is the best but scales up to medium sized problems only.</a>
<a href="#10" id="10">Moreover, the online algorithm is shown to be on average at least 90% of the optimal.</a>
<a href="#11" id="11">When taken together, our algorithms and results establish the first benchmarks for the study of EVs in MoD schemes and can be used as benchmarks for future research.</a>
<a href="#12" id="12">Future work will look into possible relocation mechanisms for the EVs, in order to further improve the task completion rates.</a>
<a href="#13" id="13">Such mechanisms could be based on crowd-sourcing techniques where available drivers from the crowd could drive EVs across locations (as discussed in Section 2).</a>
<a href="#14" id="14">In a similar vein, car pooling where multiple customers will ride the same EV could also be considered.</a>
<a href="#15" id="15">In addition to these, we aim to investigate market-based techniques to incentivise customers to execute trips which improve the numbers of tasks executed.</a>
<a href="#16" id="16">Moreover, given all the vagaries of an online implementation have not been factored in, we aim to further expand the online algorithm.</a>
<a href="#17" id="17">Dealing with cancellations, predicting delays in travel, etc are issues that should be dealt with in a real-world deployment.</a>
<a href="#18" id="18">Thus, we consider to improve and extend the online algorithm in a number of ways: 1) We aim to introduce probability distributions regarding future demand, or use machine learning techniques in order to have a better forecast of future demand and increase the number of executed tasks.</a>
<a href="#19" id="19">2) We aim to investigate the use of dynamic pricing techniques in order to balance the requests across the stations [39].</a>
<a href="#20" id="20">3) We aim to introduce relocation drivers in order to cope with the case where bookings are being cancelled.</a>
<a href="#21" id="21">In this way the schedule of future tasks would remain feasible.</a>
<a href="#22" id="22">4) We aim to introduce the notion of “acceptable risk” regarding a schedule for future tasks by using chance constraints (tuning the constraints in a human-understandable way is then another research question).</a>
</body>
</html>