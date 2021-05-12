<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:541">
</head>
<body bgcolor="white">
<a href="#0" id="0">Existing tools for solving optimization on graphical models are usually restricted to cost functions involving a reasonably small set of variables, often using an associated cost table.</a>
<a href="#1" id="1">But problem modeling may require to express complex conditions on a non-bounded set of variables.</a>
<a href="#2" id="2">This has been solved in Constraint Programming by using Global Constraints.</a>
<a href="#3" id="3">Our results contribute to lift this approach to the more general framework of cost function networks, allowing to express and efficiently process both global constraints and global cost functions, using dedicated soft arc consistency filtering.</a>
<a href="#4" id="4">Our contributions are four-fold.</a>
<a href="#5" id="5">First, we define the tractability of a global cost function, and study its behavior with respect to projections/extensions with different arities of cost functions.</a>
<a href="#6" id="6">We show that tractable r-projection-safety is always possible for projections/extension to/from the nullary cost function, while it is always impossible for projections/extensions to/from r-ary cost functions for {a mathematical formula}r≥2.</a>
<a href="#7" id="7">When {a mathematical formula}r=1, we show that a tractable cost function may or may not be tractable 1-projection-safe.</a>
<a href="#8" id="8">Second, we define polynomially DAG-filterable cost functions and show them to be tractable 1-projection-safe.</a>
<a href="#9" id="9">We give also a polytime dynamic programming based algorithm to compute the minimum of this class of global cost functions.</a>
<a href="#10" id="10">We also show that the cost function {a mathematical formula}W_Grammarvar is polynomially DAG-filterable and tractable 1-projection-safe.</a>
<a href="#11" id="11">The same results apply to {a mathematical formula}W_Amongvar, {a mathematical formula}W_Regularvar, and W_Max/W_Min as shown in the associated technical report [3].</a>
<a href="#12" id="12">Third, we show that dynamic programming can be emulated by soft consistencies such as DAC and VAC if a suitable network decomposition of the global cost function into a Berge-acyclic network of bounded arity cost functions exists.</a>
<a href="#13" id="13">In this case, local consistency on the decomposed network is essentially as strong as on the global cost function.</a>
<a href="#14" id="14">This approach is shown to be a specific case of the previous approach in the sense that any Berge-acyclic network-decomposable cost function is also polynomially DAG-filterable.</a>
<a href="#15" id="15">Finally, we perform experiments and compare the DAG-based and network-based approaches, in terms of run-time and search space.</a>
<a href="#16" id="16">The DAG-based approach dominates when there are several overlapping global cost functions.</a>
<a href="#17" id="17">On the contrary, the network-based approach performs better if there are few global cost functions resulting in a reasonable number of extra variables.</a>
<a href="#18" id="18">This is complexified by additional techniques such as boosting search by variable elimination [40], Weighted Degree heuristics [17], and Dead-End Elimination [33] which work better with the low-arity cost functions of the network-based approach.</a>
<a href="#19" id="19">We also compare against the flow-based approach [48] and show that our approaches are usually more competitive.</a>
<a href="#20" id="20">On Berge acyclic network-decomposable cost function just as {a mathematical formula}W_Regularvar, this is not unexpected as the dynamic programming based propagation or its emulation by T-DAC essentially solves a shortest path problem, which can easily be reduced to the more general min-cost flow problem used in [48] which can itself be reduced to LP [1].</a>
<a href="#21" id="21">As problems become more specific, algorithmic efficiency can increase.</a>
<a href="#22" id="22">An immediate possible future work is to investigate other sufficient conditions for polynomially DAG-filterable and also tractable 1-projection-safety.</a>
<a href="#23" id="23">Our results only provide a partial answer.</a>
<a href="#24" id="24">Whether there exists necessary conditions for polynomially DAG-filterable is unknown.</a>
<a href="#25" id="25">Besides polynomially DAG-filterable, we would like to investigate other form of tractable 1-projection-safety and techniques for enforcing typical consistency notions efficiently.</a>
</body>
</html>