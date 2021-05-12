<html>
<head>
<meta name="TextLength" content="SENT_NUM:19, WORD_NUM:413">
</head>
<body bgcolor="white">
<a href="#0" id="0">MiningZinc aims at bringing the benefits of the declarative modeling + solving approach from the field of constraint programming to the field of data mining.</a>
<a href="#1" id="1">It extends the modeling language MiniZinc with a library for constraint-based itemset mining.</a>
<a href="#2" id="2">Furthermore, an execution mechanism has been designed to support a wide range of general purpose and specialized solvers and to allow for different execution strategies.</a>
<a href="#3" id="3">Its implementation incorporates many state-of-the-art constraint programming and data mining solvers, as well as specialized algorithms.</a>
<a href="#4" id="4">The resulting architecture is flexible and extensible.</a>
<a href="#5" id="5">The experiments have shown that this leads to execution strategies with state-of-the-art performance for many known as well as novel constraint-based mining tasks.</a>
<a href="#6" id="6">The benefits of the modeling + solving approach to data mining are manyfold.</a>
<a href="#7" id="7">First, it allows for the natural and declarative modeling and solving of many constraint-based data mining problems.</a>
<a href="#8" id="8">Second, it provides a uniform interface to many data mining systems.</a>
<a href="#9" id="9">It is very expressive through its use of constraint programming technology and can tackle a wide spectrum of constraint-based mining tasks.</a>
<a href="#10" id="10">This should facilitate the comparison of different algorithms as well as the re-use of software.</a>
<a href="#11" id="11">A potential benefit of the modeling + solving approach to data mining is also the possible emergence of standard languages and (integrated) systems for data mining, as in constraint programming.</a>
<a href="#12" id="12">Current limitations are that the problem must be expressed over integer and set variables (no other explicit data structures), and that search is assumed to be exhaustive (no greedy/heuristic approximations).</a>
<a href="#13" id="13">Data mining also raises new challenges for constraint programming as the solutions offered by the modeling + solving approach need to be competitive with that of standard data mining algorithms.</a>
<a href="#14" id="14">This is non-trivial because data mining algorithms are highly optimized for specific tasks and large datasets, while generic constraint solvers may struggle in particular with the size of the problems.</a>
<a href="#15" id="15">The approach taken in MiningZinc is to provide a rewrite mechanism for generating different execution plans that may involve different algorithms, each addressing part of the task.</a>
<a href="#16" id="16">Experiments have shown that the performance of different execution plans can vary greatly, which invites for automatic algorithm selection techniques.</a>
<a href="#17" id="17">However, the breadth of problems that can be formulated, different execution plans that can be produced and the sensitivity of some problems towards a single threshold raises challenges.</a>
<a href="#18" id="18">Other directions for future work include the investigation of heuristic search strategies and the extension of the framework towards more complex pattern types and other data mining tasks such as clustering [55].</a>
</body>
</html>