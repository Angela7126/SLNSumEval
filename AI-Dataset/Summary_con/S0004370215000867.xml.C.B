<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:335">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have shown that PDBs can be applied successfully to find optimal solutions to Sokoban and improve the current state of the art.</a>
<a href="#1" id="1">This result is not obvious, since a PDB must be build for each instance, and Sokoban has k!</a>
<a href="#2" id="2">goal states, which lead to weak lower bounds.</a>
<a href="#3" id="3">Indeed, MPDBs, a straightforward application of PDBs to Sokoban, are ineffective.</a>
<a href="#4" id="4">To be able to effectively apply PDBs to Sokoban we partition the search space into a maze and a goal zone, to obtain an explicit intermediate goal state.</a>
<a href="#5" id="5">In this way, we can apply PDBs to compute a lower bound on the distance to the intermediate goal state, and use any existing lower bound for the distance from the intermediate goal state to some final goal state.</a>
<a href="#6" id="6">We also propose a new domain-specific tie breaking rule called fill order.</a>
<a href="#7" id="7">We have shown that the lower bound can be effectively computed, dominates the state-of-the-art lower bound in 62 of the 90 instances of the standard set, and identifies four times more deadlocks in tests over random states.</a>
<a href="#8" id="8">Our experiments also show that the fill order is an effective tie breaker.</a>
<a href="#9" id="9">Applied together in an {a mathematical formula}A⁎ search, these techniques explore less nodes, and are an order of magnitude faster than other approaches.</a>
<a href="#10" id="10">In one hour our solver finds the optimal solutions of 20 instances, compared to 6 for the state-of-the-art solver {a mathematical formula}RS⁎, and 10 for EMM.</a>
<a href="#11" id="11">Although MPDBs result in weak lower bounds, they detect more deadlocks than the other approaches.</a>
<a href="#12" id="12">It remains to be studied if MPDBs can be applied effectively in Sokoban.</a>
<a href="#13" id="13">It is further possible to use instance decompositions with several, smaller maze zones.</a>
<a href="#14" id="14">PDBs for smaller maze zones have less entries which allow for larger abstractions, so we capture more interactions of stones within maze zones, but loose the interactions between maze zones.</a>
<a href="#15" id="15">The net effect of this trade-off remains to be studied.</a>
<a href="#16" id="16">It would be also interesting to apply PDBs and better tie breaking rules in non-admissible solvers.</a>
</body>
</html>