<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:430">
</head>
<body bgcolor="white">
<a href="#0" id="0">This article studies applications of the CEGAR paradigm in the context of QBF solving.</a>
<a href="#1" id="1">It introduces the algorithm RAReQS, which gradually expands the given formula into a propositional one and applies a SAT solver on it.</a>
<a href="#2" id="2">RAReQS is a recursive extension of the 2QBF algorithm AReQS, which has since its original publication inspired specialized algorithms for number of problems in the second level of polynomial hierarchy.</a>
<a href="#3" id="3">In its workings, RAReQS is close to expansion-based solvers (e.g. Quantor, Nenofex) but with the important difference that the expansion is done step-by-step, driven by counterexamples.</a>
<a href="#4" id="4">Thus, the solver builds an abstraction of the given formula by constructing a partial expansion.</a>
<a href="#5" id="5">The downside of this approach is that if in the end a full expansion is needed, then RAReQS performs the same expansion as a traditional expansion-based solver but with the overhead of intermediate tests.</a>
<a href="#6" id="6">However, the approach has important advantages.</a>
<a href="#7" id="7">Whenever there is no winning move for the partial expansion, then there is no winning move for the given formula.</a>
<a href="#8" id="8">This enables RAReQS to quickly stop for formulas with no winning moves.</a>
<a href="#9" id="9">For formulas for which there is a winning move, RAReQS only needs to build a strong-enough partial expansion whose winning moves are also likely to be winning moves for the given formula.</a>
<a href="#10" id="10">The experimental results demonstrate the ability of RAReQS to avoid the inherent memory blowup of expansion solvers, and, that careful expansion outperforms a traditional DPLL-based approach on a large number of practical instances.</a>
<a href="#11" id="11">We have shown that abstraction-refinement as used in RAReQS is also applicable within DPLL solvers as an additional learning mechanism.</a>
<a href="#12" id="12">This provides a more powerful learning technique than standard clause/cube learning, although it requires more memory.</a>
<a href="#13" id="13">Experimental evaluation indicates that this type of learning is indeed useful for DPLL-based solvers.</a>
<a href="#14" id="14">In the future we plan to further develop our DPLL solver so that it supports the full range of CEGAR learning exploited by RAReQS and to investigate how to fine-tune this learning in order to mitigate the speed penalty for the cases where the learning provides little information over the traditional learning.</a>
<a href="#15" id="15">This can not only be done by better engineering of the solver but also devising schemata that disable the learning once deemed too costly.</a>
<a href="#16" id="16">Conversely, in the future we plan to integrate learning techniques into RAReQS.</a>
<a href="#17" id="17">This is likely to be important in formulas with large number of quantification levels.</a>
<a href="#18" id="18">Techniques used in other solvers should also be considered.</a>
<a href="#19" id="19">In particular, more aggressive preprocessing as used in Quantor and techniques for finding commonalities in formulas used in Nenofex, and dependency detection as in DepQBF[37].</a>
</body>
</html>