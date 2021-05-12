<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:550">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we provide the first Security Game for large environments surveillance, e.g., for fair sites protection, that can exploit an alarm system with spatially uncertain signals.</a>
<a href="#1" id="1">To monitor and protect large infrastructure such as stations, airports, and cities, a two-level paradigm is commonly adopted: a broad area surveillance phase, where an attack is detected but only approximately localized due to the spatially uncertainty of the alarm system, triggers a local investigation phase, where guards have to find and clear the attack.</a>
<a href="#2" id="2">Abstracting away from technological details, we propose a simple model of alarm systems that can be widely adopted with every specific technology and we include it in the state-of-art patrolling models, obtaining a new security game model.</a>
<a href="#3" id="3">We show that the problem of finding the best patrolling strategy to respond to a given alarm signal is {a mathematical formula}FNP-hard on trees and {a mathematical formula}APX-hard with arbitrary graphs.</a>
<a href="#4" id="4">Then, we provide two exponential-time exact algorithms to find the best patrolling strategy to respond to a given alarm signal.</a>
<a href="#5" id="5">The first algorithm performs a breath-first search by exploiting a dynamic programming approach, while the second algorithm performs a depth-first approach by exploiting a branch-and-bound approach.</a>
<a href="#6" id="6">We provide also a variation of these two algorithms to find an approximate solution.</a>
<a href="#7" id="7">We experimentally evaluate our exact and approximation algorithms both in worst-case instances, to evaluate empirically the gap between our hardness results and the theoretical guarantees of our approximation algorithms, and in one realistic instance.</a>
<a href="#8" id="8">The limit of our exact algorithms is about 16 targets with worst-case instances while we were able to compute an optimal solution for a realistic instance with ≈170 targets.</a>
<a href="#9" id="9">On the other side, our approximation algorithms provide a very effective approximation even with worst-case instances.</a>
<a href="#10" id="10">Finally, we focus on the problem of patrolling the environment, showing that if every target is alarmed and no false positives nor missed detections are present, then the best patrolling strategy prescribes that the patroller stays in a given place waiting for an alarm signal.</a>
<a href="#11" id="11">Furthermore, we show that such a strategy may be optimal even for missed detection rates up to 50%.</a>
<a href="#12" id="12">Besides the solutions we studied, a number of open problems have been posed for future research.</a>
<a href="#13" id="13">The main theoretical issue is the closure of the approximation gap of SRG-v.</a>
<a href="#14" id="14">We believe that investigating the relationship between our model and the DEADLINE–TSP could help in closing the gap.</a>
<a href="#15" id="15">Another interesting problem is the study of approximation algorithms for tree graphs.</a>
<a href="#16" id="16">Our {a mathematical formula}NP-hardness result does not exclude the existence of a PTAS (i.e., polynomial time approximation scheme), even if we conjecture that the existence is unlikely.</a>
<a href="#17" id="17">A number of extensions of our model are worth being explored, we identify two prominent ones.</a>
<a href="#18" id="18">The first is to enrich our model with false positives and missed detections, requiring patrolling even in the absence of alarm signals.</a>
<a href="#19" id="19">A second extension is to consider settings with multiple patrollers.</a>
<a href="#20" id="20">We deem that the techniques presented in this work can play a fundamental role in scaling to multi-patroller settings.</a>
<a href="#21" id="21">In [27] we give some preliminary contributions along this direction, discussing different arising subproblems, showing how some properties like the one given in Theorem 10 can be generalized, and leveraging the algorithms presented here for the resolution of multi-patroller games under different coordination assumptions.</a>
</body>
</html>