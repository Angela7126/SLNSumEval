<html>
<head>
<meta name="TextLength" content="SENT_NUM:19, WORD_NUM:489">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have studied how the consistency problem for RCC8 networks is affected by the requirement that all regions need to be convex.</a>
<a href="#1" id="1">Previous results about convexity in RCC8 have been largely negative: for any fixed number of dimensions k, deciding whether a consistent RCC8 network Θ can be realized using convex regions in {a mathematical formula}Rk is computationally hard [23].</a>
<a href="#2" id="2">In contrast, we have identified a number of important sufficient conditions under which consistent RCC8 networks have convex solutions.</a>
<a href="#3" id="3">First, we have identified all restrictions on the set of base relations that guarantee that consistent atomic networks can be convexly realized in {a mathematical formula}R, {a mathematical formula}R2, {a mathematical formula}R3 and {a mathematical formula}R4.</a>
<a href="#4" id="4">Second, we have shown an upper bound which only depends on the number of regions, i.e. every consistent RCC8 network with at most {a mathematical formula}2n+1 regions can be convexly realized in {a mathematical formula}Rn ({a mathematical formula}n≥2).</a>
<a href="#5" id="5">Our main motivation in this paper was to justify the use of standard RCC8 reasoners to reason about convex regions in high-dimensional spaces, e.g. to support qualitative reasoning about conceptual spaces [9], [39].</a>
<a href="#6" id="6">While existing work on conceptual spaces is mostly based on geometric representations (e.g. corresponding to the Voronoi diagram induced by a set of prototypes [9]), in practice it can be difficult to obtain accurate region-based representations from data, especially for concepts which are relatively rare.</a>
<a href="#7" id="7">In contrast, existing lexical resources such as WordNet{sup:4} and ConcepNet{sup:5} encode several relations that can be interpreted as qualitative spatial relations between conceptual space representations.</a>
<a href="#8" id="8">For example, the hypernym/hyponym relations encoded in WordNet can be seen as PP and from ConceptNet it is sometimes possible to derive EC relations.</a>
<a href="#9" id="9">For example, ConceptNet encodes{sup:6} that “jogging is a kind of exercise similar to running” and “jogging is slower than running”, from which we may derive {a mathematical formula}joggingECrunning.</a>
<a href="#10" id="10">Similarly, natural language processing methods, e.g. based on Hearst patterns [40], can be used to learn qualitative semantic relations from natural language sentences.</a>
<a href="#11" id="11">To use such knowledge about the meaning of concepts in applications, we therefore need methods for qualitative reasoning about meaning.</a>
<a href="#12" id="12">The results we have presented in this paper provide the first step towards such applications.</a>
<a href="#13" id="13">Future work will build on these results by investigating generalizations of RCC5 and RCC8 which are tailored towards reasoning about concepts.</a>
<a href="#14" id="14">For example, Ref.</a>
<a href="#15" id="15">[18] has focused on adding a betweenness relation to RCC5, which is important for formalizing particular forms of commonsense reasoning [41].</a>
<a href="#16" id="16">In [42], a logic for concepts is introduced in which comparative distance can be expressed (i.e. “a is closer to b than to c”), which is important for formalizing categorization, but without guarantees that concepts can be realized as convex regions.</a>
<a href="#17" id="17">An interesting question would then be whether the results from this paper, viz.</a>
<a href="#18" id="18">the observation that requiring convexity does not affect consistency if the number of dimensions is sufficiently large, carries over to such more expressive settings.</a>
</body>
</html>