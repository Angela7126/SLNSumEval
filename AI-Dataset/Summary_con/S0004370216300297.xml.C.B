<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:351">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have studied the problem of rewriting Disjunctive Datalog programs and Description Logics ontologies into Datalog.</a>
<a href="#1" id="1">From a theoretical perspective, we have established a novel characterisation of Datalog rewritability in terms of linearisability: a Disjunctive Datalog program is Datalog rewritable if and only if it can be rewritten into a linear program.</a>
<a href="#2" id="2">Our characterisation relies on the correctness of program transposition—a novel polynomial transformation where IDB atoms are moved from head and body and vice versa while their predicates are replaced with fresh predicates of higher arity.</a>
<a href="#3" id="3">Motivated by our characterisation and the properties of transposition, we have then proposed the classes of weakly linear and markable Disjunctive Datalog programs and showed that they admit polynomial Datalog rewritings.</a>
<a href="#4" id="4">For programs that do not satisfy the WL or markability conditions, we have proposed a sound but incomplete procedure based on unfolding transformations and proved its correctness.</a>
<a href="#5" id="5">We have shown that our results for Disjunctive Datalog can be naturally applied to DL ontologies as well, and we have proposed classes of ontologies that admit polynomial and exponential rewritings, respectively.</a>
<a href="#6" id="6">Finally, we have extended all our results to conjunctive query answering and identified classes of programs and queries that admit a Datalog rewriting.</a>
<a href="#7" id="7">From a practical perspective, our techniques enable the use of scalable Datalog engines for data reasoning.</a>
<a href="#8" id="8">This is especially relevant for DL ontologies, where reasoning with large-scale datasets is a major challenge in practice.</a>
<a href="#9" id="9">Our experiments have confirmed the potential applicability of our approach.</a>
<a href="#10" id="10">We see many interesting directions for future work.</a>
<a href="#11" id="11">In particular, we are currently working on lifting transposition to programs with function symbols; preliminary results are reported in [61].</a>
<a href="#12" id="12">This would allow us to identify classes of first-order programs (and thus also expressive ontologies) that admit polynomial Datalog rewritings via transposition.</a>
<a href="#13" id="13">Additionally, it would be interesting to devise rewriting techniques that combine the benefits of resolution [2], [28] and transposition.</a>
<a href="#14" id="14">Finally, we believe that our techniques could be exploited to enhance “pay-as-you-go” query answering systems such as PAGOdA [62], where the idea is to delegate the bulk of the computational workload to a Datalog reasoner.</a>
</body>
</html>