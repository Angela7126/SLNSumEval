<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:291">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have proposed a constraint approach to solve cyclic scheduling problems, based on modular arithmetic.</a>
<a href="#1" id="1">In particular, we have devised global constraints to model temporal dependencies (the Modular Precedence Constraint, ModPC) and resource restrictions (The Global Cyclic Cumulative Constraint, GCCC).</a>
<a href="#2" id="2">For both of them, we devised original filtering algorithms.</a>
<a href="#3" id="3">We have also described a restricted version of our solver where we rely on a specific assumption to model the resource restrictions via traditional cumulative constraints, rather than via the GCCC.</a>
<a href="#4" id="4">The general instantiation of our approach is referred to as CROSS, while its restricted version as {a mathematical formula}CROSS⁎.</a>
<a href="#5" id="5">The approach has been tested extensively on industrial as well as synthetically generated instances.</a>
<a href="#6" id="6">Our method was able to return solutions very close to the known optimum or to a lower bound in a matter of seconds (or a fraction of second), on problems of practical size.</a>
<a href="#7" id="7">Depending on the considered benchmarks, our approach either outperformed existing heuristic or unfolding-based techniques, or provided a very good compromise between solution quality and time.</a>
<a href="#8" id="8">All this makes our method one of the best available solvers for cyclic scheduling problems with cumulative resources.</a>
<a href="#9" id="9">Future research directions include improving the effectiveness of the proof of optimality, which is currently a weak point of the method.</a>
<a href="#10" id="10">A second, very interesting, research topic concerns the design of a more effective search strategy for the unrestricted CROSS approach.</a>
<a href="#11" id="11">Since the start times assigned by our Random & Restart strategy depend on the period upper bound {a mathematical formula}λ¯, they tend to lead to solutions with period quite close to {a mathematical formula}λ¯ itself, thus making the optimization process slower.</a>
<a href="#12" id="12">This could be addressed by exploiting ideas from the Precedence Constrain Posting technique [29], [34], developed for non-cyclic scheduling problems.</a>
</body>
</html>