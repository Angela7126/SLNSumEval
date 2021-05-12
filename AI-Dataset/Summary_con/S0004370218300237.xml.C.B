<html>
<head>
<meta name="TextLength" content="SENT_NUM:12, WORD_NUM:223">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we propose a high-level and flexible framework namely lazy decomposition and conciliation (LDC) for parallelizing SMT solving.</a>
<a href="#1" id="1">An LDC based solver could be built upon an existing SMT solver without hacking its low-level implementation.</a>
<a href="#2" id="2">LDC is flexible for various underlying theories supporting quantifier-free interpolation.</a>
<a href="#3" id="3">We have designed a sound and complete instantiation of LDC in {a mathematical formula}TE and implemented PZ3, a parallelized version of Z3.</a>
<a href="#4" id="4">Evaluation results substantiate the potential of LDC as PZ3 outperforms the sequential solver on a variety of random and benchmark problems.</a>
<a href="#5" id="5">In particular, PZ3 generally takes an advantage on problems with sparse structures and it could achieve orders of magnitude speed-up over Z3 on these problems.</a>
<a href="#6" id="6">Our proposed framework opens some interesting directions for future research.</a>
<a href="#7" id="7">It is possible to develop a new decomposition heuristic that takes subproblem complexity into consideration for better load balancing in parallel processing.</a>
<a href="#8" id="8">Furthermore, it is worth instantiating LDC in other theories such as arithmetic, bit-vector and even theory combinations since they are relevant to many practical problems in verification and AI planning.</a>
<a href="#9" id="9">Last but not the least, the implementation of LDC could be further optimized especially for dense problems.</a>
<a href="#10" id="10">The work stealing mechanism could be integrated to improve the parallel efficiency.</a>
<a href="#11" id="11">Some refutation compression techniques [49], [50], [51], [52] are potentially helpful for a more efficient interpolant extraction.</a>
</body>
</html>