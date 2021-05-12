<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:257">
</head>
<body bgcolor="white">
<a href="#0" id="0">We also discuss how the truncation approach can be extended to work as an anytime algorithm.</a>
<a href="#1" id="1">Here, we discuss some of the important results.</a>
<a href="#2" id="2">For known dynamic graphs, TD* Lite is a better algorithm compared to D* Lite (with inflated heuristic), especially for low bounds and harder problems.</a>
<a href="#3" id="3">However, as D is already truncated, this new path information is not propagated.</a>
<a href="#4" id="4">Avoiding heap reorder: As D* Lite moves the robot along the path computed, it needs to recalculate the priorities in OPEN when a change in edge costs occurs.</a>
<a href="#5" id="5">{sup:6} Second, we observe that the run times do not always correlate with state expansions.</a>
<a href="#6" id="6">When ComputePath terminates, all states from TRUNCATED are processed through UpdateState if there is a cost change, otherwise they are added to INCONS.</a>
<a href="#7" id="7">Moreover, as the Key values of expanded states in LPA* are monotonically non-decreasing during the execution of ComputePath, the same condition ensures that expansion of any other state {a mathematical formula}s′ in OPEN cannot improve the current bound, i.e., we may terminate the current replanning iteration at this point.</a>
<a href="#8" id="8">In particular, these algorithms restart A* at the point where the current search queue differs from the previous run.</a>
<a href="#9" id="9">Search direction: D* Lite always searches from goal state to start state.</a>
<a href="#10" id="10">TLPA* uses two extra variables for each state (compared to LPA*): {a mathematical formula}gπ(s), as described earlier, and {a mathematical formula}π(s), which stores the current path (from {a mathematical formula}sstart) for a truncated state s. It also uses an additional list TRUNCATED to store the underconsistent states that are truncated.</a>
</body>
</html>