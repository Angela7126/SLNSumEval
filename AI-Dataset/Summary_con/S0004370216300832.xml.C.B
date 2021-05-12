<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:229">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we proposed a number of novel ideas for local search for Partial MaxSAT, which exploit the distinction between hard and soft clauses.</a>
<a href="#1" id="1">Specifically, we proposed a clause weighting scheme that works only for hard clauses, the idea of separating hard and soft score, and a variable selection heuristic based on hard score and soft score.</a>
<a href="#2" id="2">We then used these ideas to develop a local search algorithm for PMS called Dist.</a>
<a href="#3" id="3">Experimental results show that Dist dramatically outperforms previous local search algorithms.</a>
<a href="#4" id="4">Also, Dist outperforms complete algorithms on random and crafted benchmarks, but is still worse on industrial instances.</a>
<a href="#5" id="5">Further, we proposed an initialization procedure that makes use of unit propagation and puts priority on hard unit clauses, and applied it to improve Dist on industrial instances, resulting in the DistUP solver.</a>
<a href="#6" id="6">Experimental results show that DistUP significantly improves Dist on industrial PMS and WPMS instances, yet it cannot rival state-of-the-art complete solvers.</a>
<a href="#7" id="7">This work made a breakthrough in local search for PMS, which was also confirmed by the excellent performance of Dist in the MaxSAT Evaluation 2014.</a>
<a href="#8" id="8">The strong experimental results suggested that local search based on hard and soft score is a promising direction for solving PMS and deserves further research, and we would like to extend these methods to weighted Partial MaxSAT.</a>
<a href="#9" id="9">Another interesting direction is to study the initialization methods for MaxSAT problems.</a>
</body>
</html>