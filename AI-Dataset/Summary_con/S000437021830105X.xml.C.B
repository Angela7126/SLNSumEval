<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:609">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have investigated the complexity and generality of the state of the art frameworks for learning answer set programs.</a>
<a href="#1" id="1">We have shown, for the two decision problems of verification that a hypothesis is an inductive solution of a task and deciding whether a given task is satisfiable, that brave induction ({a mathematical formula}ILPb) and induction of stable models ({a mathematical formula}ILPsm) have the same complexities, and that cautious induction ({a mathematical formula}ILPc), learning from answer sets ({a mathematical formula}ILPLAS), learning from ordered answer sets ({a mathematical formula}ILPLOAS) and context dependent learning from ordered answer sets ({a mathematical formula}ILPLOAScontext) also have the same complexities as each other, but higher than {a mathematical formula}ILPb and {a mathematical formula}ILPsm.</a>
<a href="#2" id="2">Studying the complexity of decision problems for the learning frameworks is important, as it gives a sense of the price paid for choosing a particular framework.</a>
<a href="#3" id="3">In contrast, generality is important, as it shows the advantages of choosing one framework over another, by specifying which hypotheses can be learned by each framework.</a>
<a href="#4" id="4">When using ILP in practice, a trade off must be made between the complexity and generality of the framework.</a>
<a href="#5" id="5">The generality classes presented in this paper can inform this decision, as it is likely to be influenced by the class of programs that must be learned.</a>
<a href="#6" id="6">We have introduced three new measures of generality ({a mathematical formula}D11-generality, {a mathematical formula}Dm1-generality and {a mathematical formula}Dmm-generality), and shown that, both under our own measures of generality, and by using the concept of strong reductions, there is an ordering of the generalities of the frameworks considered in this paper.</a>
<a href="#7" id="7">Although {a mathematical formula}ILPc, {a mathematical formula}ILPLAS, {a mathematical formula}ILPLOAS and {a mathematical formula}ILPLOAScontext have the same computational complexities, {a mathematical formula}ILPc is less general than {a mathematical formula}ILPLAS, which is less general than {a mathematical formula}ILPLOAS, which is less general than {a mathematical formula}ILPLOAScontext, under each measure of generality.</a>
<a href="#8" id="8">This ordering could have been seen using strong reductions, but our measures go further.</a>
<a href="#9" id="9">They allow us to reason about why one framework is more {a mathematical formula}D11-general than another, for example, by studying the class of tuples which are in one framework's distinguishability class, but not the others.</a>
<a href="#10" id="10">They also allow us to discuss the generalities of frameworks which are incomparable under strong reductions; for example, there is no strong reduction from {a mathematical formula}ILPc to {a mathematical formula}ILPb, or from {a mathematical formula}ILPb to {a mathematical formula}ILPc.</a>
<a href="#11" id="11">Our measures allow us to show, however, that {a mathematical formula}ILPb is not {a mathematical formula}D11-general enough to distinguish a hypothesis containing a constraint from the same program without the constraint, but in some cases {a mathematical formula}ILPc is {a mathematical formula}D11-general enough to do so.</a>
<a href="#12" id="12">In this paper, most of the results we have presented have addressed non-noisy learning frameworks.</a>
<a href="#13" id="13">In general our ILASP systems do support noise, by allowing examples to be labeled with a penalty.</a>
<a href="#14" id="14">In this case, ILASP searches for a hypothesis that minimises the sum {a mathematical formula}|H|+p(H,E), where {a mathematical formula}p(H,E) is the sum of all examples in a set E that are not covered by a hypothesis H. Such a hypothesis is called an optimal solution.</a>
<a href="#15" id="15">For the two decision problems of verification and satisfiability, we have shown that the complexity results are unaffected.</a>
<a href="#16" id="16">In current work we are investigating whether the complexities of the non-noisy frameworks and the noisy frameworks differ for the decision problem of verifying that a hypothesis is an optimal solution of a given task.</a>
<a href="#17" id="17">In future work, we also hope to “upgrade” the propositional complexity results presented in this paper to apply to the learning of first order answer set programs.</a>
</body>
</html>