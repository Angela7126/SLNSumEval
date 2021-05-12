<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:185">
</head>
<body bgcolor="white">
<a href="#0" id="0">Bidirectional search algorithms interleave two separate searches, a normal search forward from the start state, and a search backward from the goal.</a>
<a href="#1" id="1">It is well known that adding a heuristic to unidirectional search dramatically reduces the search effort.</a>
<a href="#2" id="2">By contrast, despite decades of research, bidirectional heuristic search has not yet had a major impact.</a>
<a href="#3" id="3">Additionally, no comprehensive theory was ever devised to understand the nature of bidirectional heuristic search.</a>
<a href="#4" id="4">In this paper we aim to close this gap.</a>
<a href="#5" id="5">We first present MM, a novel bidirectional heuristic search algorithm.</a>
<a href="#6" id="6">Unlike previous bidirectional heuristic search algorithms, MM's forward and backward searches are guaranteed to “meet in the middle”, i.e. never expand a node beyond the solution midpoint.</a>
<a href="#7" id="7">Based on this unique attribute we present a novel framework for comparing MM, A*, and their brute-force variants.</a>
<a href="#8" id="8">We do this by dividing the entire state space into disjoint regions based on their distance from the start and goal.</a>
<a href="#9" id="9">This allows us to perform a comparison of these algorithms on a per region basis and identify conditions favoring each algorithm.</a>
<a href="#10" id="10">Finally, we present experimental results that support our theoretical analysis.</a>
</body>
</html>