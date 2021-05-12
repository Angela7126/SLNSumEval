<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:347">
</head>
<body bgcolor="white">
<a href="#0" id="0">lex constraints are known to break exactly every variable symmetry retaining only a representative member of each class.</a>
<a href="#1" id="1">They are valid for all kinds of problems, independently of the nature of the domains.</a>
<a href="#2" id="2">However, the number of lex constraints is potentially factorial in the number of variables.</a>
<a href="#3" id="3">Moreover, we have shown they are impractical for numerical solvers.</a>
<a href="#4" id="4">To overcome these drawbacks, we have proposed the rlex PSBCs, a set of simple inequalities between two variables.</a>
<a href="#5" id="5">The maximum number of non-redundant constraints in rlex is linear in the number of variables.</a>
<a href="#6" id="6">Besides they are easily handled by numerical solvers, which are able to quickly propagate them.</a>
<a href="#7" id="7">They can be considered a generalization of PSBCs proposed for particular symmetry groups in some previous works.</a>
<a href="#8" id="8">We have shown that rlex are a relaxation of lex with optimal properties.</a>
<a href="#9" id="9">In fact, they enclose a space which is the closure of that enclosed by lex SBCs, and we have proved both have the same volume.</a>
<a href="#10" id="10">A detailed analysis of rlex PSBCs also shows that their filtering power is almost identical to complete SBCs in the context of numerical CSPs.</a>
<a href="#11" id="11">The experiments we have conducted on a benchmark of standard problems with various characteristics and sizes demonstrate the practical efficacy of rlex constraints: (almost) never counterproductive, they induce gains in solving time which can be factorial for problems with symmetry groups of large orders.</a>
<a href="#12" id="12">Still, the presented results also demonstrate these gains are not always directly proportional to the symmetry group order, and we have thoroughly analyzed the reasons why.</a>
<a href="#13" id="13">All the arguments we have used are also valid for continuous (constrained) optimization.</a>
<a href="#14" id="14">rlex can also be interesting in discrete domains, though Jefferson and Petrie [22] have demonstrated there exist superior PSBCs in this context.</a>
<a href="#15" id="15">Still, in discrete domains with many values for each variable, the frontier (in which reside the only symmetry classes not completely broken by rlex) will be small with respect to the domain.</a>
<a href="#16" id="16">Hence, we should also consider Mixed-Integer Nonlinear Programming and Integer Linear Programming for which some of the PSBCs we have generalized have been proposed [17], [36].</a>
</body>
</html>