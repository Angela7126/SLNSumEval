<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:470">
</head>
<body bgcolor="white">
<a href="#0" id="0">One major difference between qualitative CSPs and classical CSPs is that the domain of a qualitative CSP is always infinite, while that of a classical CSP is usually finite.</a>
<a href="#1" id="1">In this paper we proposed an extended framework for qualitative CSPs that supports finite domains.</a>
<a href="#2" id="2">In the extended framework, a spatial/temporal variable could take values from a finite domain or even a singleton.</a>
<a href="#3" id="3">This reflects demands in applications such as urban planning and spatial query processing where additional knowledge about variables may be available.</a>
<a href="#4" id="4">We believe this extension is necessary to bring QSTR closer to real-world applications.</a>
<a href="#5" id="5">We then investigated the computational complexity of solving the extended consistency problem for five very important qualitative calculi, viz.</a>
<a href="#6" id="6">PA, IA, CRA, RCC5 and RCC8.</a>
<a href="#7" id="7">The results were summarised in Table 4, where for each calculus, we determined whether each of the four variants of the consistency problem is in P or NP-complete.</a>
<a href="#8" id="8">Recall that the classical consistency problem is NP-complete for IA, CRA, RCC5 and RCC8.</a>
<a href="#9" id="9">This shows that, in general, the expressiveness of the extended framework of qualitative CSP does not incur additional cost in computational complexity for these calculi.</a>
<a href="#10" id="10">Under practical assumptions, we also provided efficient algorithms for solving basic constraints involving landmarks for all these calculi.</a>
<a href="#11" id="11">While this paper introduces landmarks in qualitative CSPs, there is a related work in classical CSPs.</a>
<a href="#12" id="12">Recently, Bulatov [5] has given a full classification of computational complexity for conservative constraint satisfaction problems with finite values, in which the set of values for each individual variable can be restricted arbitrarily.</a>
<a href="#13" id="13">The solving algorithm and the proofs given there heavily use the algebraic approach to (classical) CSP developed in [17], [6].</a>
<a href="#14" id="14">One interesting future research direction will be investigating the possibility of applying the solving algorithm given in [5], and, more generally, the algebraic approach, to solving qualitative CSPs involving landmarks.</a>
<a href="#15" id="15">We refer the reader to [2] for recent progresses of applying the algebraic approach for attacking qualitative CSPs.</a>
<a href="#16" id="16">In this paper, we have confined ourselves to the five most important qualitative calculi, which are all binary calculi.</a>
<a href="#17" id="17">The framework can be straightforwardly extended to any other qualitative calculus, binary or ternary, but the computational complexity has to be examined case by case.</a>
<a href="#18" id="18">Take the ternary calculus LR [23] as an example.</a>
<a href="#19" id="19">It has been shown that reasoning with complete basic and landmark-free LR networks is already at least NP-hard and its NP-membership is still open [46].</a>
<a href="#20" id="20">As a consequence, reasoning with complete basic LR networks involving landmarks is also NP-hard.</a>
<a href="#21" id="21">Another direction of future research will be investigating the computation complexity for other well-known calculi, individually or combined together.</a>
<a href="#22" id="22">Because most of these consistency problems are at least NP-hard, it is also necessary to develop either approximate methods or practical methods (e.g. those in [37], [18]) for solving qualitative (binary or ternary) CSPs involving landmarks.</a>
</body>
</html>