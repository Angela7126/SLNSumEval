<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:230">
</head>
<body bgcolor="white">
<a href="#0" id="0">For the solvers with different versions, the best upper bound on each instance is considered.</a>
<a href="#1" id="1">At recent editions of MSE, we have seen that solvers implementing SAT-based algorithms clearly dominate on industrial instances.</a>
<a href="#2" id="2">Given the WPMS formula {a mathematical formula}φ=〈〈x1,5〉,〈x2,3〉,〈x3,3〉,〈x‾1∨x‾2,∞〉,〈x‾1∨x‾3,∞〉,〈x‾2∨x‾3,∞〉〉, we have that {a mathematical formula}cost(φ)=min⁡{6,8,11,∞}=6 and the solution {a mathematical formula}I maps {a mathematical formula}〈x1,x2,x3〉 to {a mathematical formula}〈1,0,0〉.</a>
<a href="#3" id="3">Imagine at-most constraint {a mathematical formula}〈A3,5,1〉 (root node) replaces at-most constraints {a mathematical formula}〈A1,2,1〉 and {a mathematical formula}〈A2,1,1〉 (child 1 and child 2).</a>
<a href="#4" id="4">Finally, p stands for phase saving extended to MaxSAT (see Section 7).</a>
<a href="#5" id="5">The basic MaxSAT problem can be further generalized to the Weighted Partial MaxSAT (WPMS) problem.</a>
<a href="#6" id="6">The key point is how to transform {a mathematical formula}φk into {a mathematical formula}φk+1.</a>
<a href="#7" id="7">OLL just handles the soft clause {a mathematical formula}〈o‾11,1〉 the same way as the original ones, {a mathematical formula}〈b‾4,1〉 and {a mathematical formula}〈b‾5,1〉, building the new Cardinality constraint on the current soft clauses instead of on the original ones.</a>
<a href="#8" id="8">The parameters include some options of the MaxSAT solver as well as some others of the underlying SAT solver.</a>
<a href="#9" id="9">Respect to latest advances in MaxSAT [42], [43] a deeper explanation of their efficiency could be that these algorithms implicitly preserve the order.</a>
<a href="#10" id="10">It basically prevents the algorithm to introduce weighted PB constraints instead of Cardinality constraints when the at-most constraints involved in the core have different weights.</a>
</body>
</html>