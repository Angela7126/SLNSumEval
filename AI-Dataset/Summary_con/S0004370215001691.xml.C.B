<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:321">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we introduce a new problem, called Top-k SAT, defined as the problem of enumerating the Top-k models of a propositional formula.</a>
<a href="#1" id="1">A Top-k model is a model having no more than {a mathematical formula}k−1 models preferred to it with respect to the considered preference relation.</a>
<a href="#2" id="2">We also show that Top-k SAT generalizes the two well-known problems: the Partial MAX-SAT problem and the problem of computing minimal models.</a>
<a href="#3" id="3">A general algorithm for this problem is proposed and evaluated on the problem of enumerating Top-k patterns in data mining, namely, the problem of mining Top-k motifs in the transaction databases and in the sequences.</a>
<a href="#4" id="4">In the case of mining sequence data, we introduce a natural extension of the problem to deal with the sequences of itemsets.</a>
<a href="#5" id="5">Interestingly, its encoding to SAT is obtained with a slight modification of the SAT encoding of the problem dealing with the sequences of items.</a>
<a href="#6" id="6">While our new problem of computing the Top-k preferred models in Boolean satisfiability is flexible and declarative, there are a number of questions that deserve further research efforts.</a>
<a href="#7" id="7">One direction is the study of (preferred/Top-k) model enumeration algorithm so as to achieve a further speedup of the runtime.</a>
<a href="#8" id="8">This fundamental problem has not received a lot of attention in the SAT community, except some interesting works on enumerating minimal/preferred models.</a>
<a href="#9" id="9">We also plan to investigate other variants of the considered data mining problems such as sequences of sequences of items or itemsets.</a>
<a href="#10" id="10">It would be interesting to extend our encodings with constraints on the form of the enumerated patterns (restriction on the number of consecutive wildcards, regular expressions, etc.).</a>
<a href="#11" id="11">Finally, on the Boolean satisfiability side, the design of efficient model generation procedures is an important issue for SAT-based datamining framework in general and to other important application domains.</a>
<a href="#12" id="12">Finding a better approximation of the initial set of Top-k patterns to reduce the intermediary non Top-k patterns deserves to be investigated.</a>
</body>
</html>