<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:622">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have investigated a range of reformulations, described algorithms to perform them, and implemented them in the system Savile Row.</a>
<a href="#1" id="1">Some of these reformulations are novel improvements on the existing work.</a>
<a href="#2" id="2">Furthermore, we have discovered sequences of reformulations that are much more effective than any single reformulation.</a>
<a href="#3" id="3">Each reformulation was evaluated on a set of 50 problem classes with 596 instances in total, in a very extensive set of experiments where reformulations were switched on one by one and their effects analysed as part of the system.</a>
<a href="#4" id="4">Throughout we reported the cost of performing a reformulation, including on instances where the model was not changed.</a>
<a href="#5" id="5">Two quite different target solvers were used in the experiments: Minion, a backtracking CP solver, and Lingeling, a state-of-the-art SAT solver with conflict learning and inprocessing.</a>
<a href="#6" id="6">Most of the reformulations prove to be effective for both target solvers, which is encouraging for the study of automated modelling techniques.</a>
<a href="#7" id="7">We have investigated four different forms of common sub-expression elimination (CSE) that are able to exploit cases where equivalent or similar expressions appear in different constraints.</a>
<a href="#8" id="8">We have introduced and described a new algorithm, X-CSE, to perform Associative–Commutative CSE (AC-CSE) as an automated modelling step for finite domain constraint satisfaction problems.</a>
<a href="#9" id="9">X-CSE is able to find common subexpressions which are particularly effective in six benchmark problems: BIBD, OPD, SONET, Killer Sudoku, Car Sequencing and Molnar's Problem.</a>
<a href="#10" id="10">Of particular importance, X-CSE interacts with other reformulations, thereby magnifying the power of those techniques and X-CSE.</a>
<a href="#11" id="11">We suggest that X-CSE is preferable to an earlier algorithm for AC-CSE, namely I-CSE, because it is able to exploit frequently occurring short common subexpressions.</a>
<a href="#12" id="12">In our experiments X-CSE outperformed I-CSE in most cases.</a>
<a href="#13" id="13">We conclude that X-CSE is a valuable addition to the armoury of automated constraint modelling techniques, both alone and in combination with other techniques.</a>
<a href="#14" id="14">We found that a wide range of reformulations are valuable, including variable unification, domain filtering and aggregation.</a>
<a href="#15" id="15">The most dramatic gains came from the X-CSE algorithm for AC-CSE, often when combined with the generation of implied sum constraints, variable unification, domain filtering and simplifiers.</a>
<a href="#16" id="16">With this combination, we saw peak speed increases of hundreds and even thousands of times.</a>
<a href="#17" id="17">The success of the CSE methods immediately suggests two avenues of future work.</a>
<a href="#18" id="18">CSE improves the formulation when two expressions overlap by more than one variable, and the types of the two expressions are appropriate.</a>
<a href="#19" id="19">For Identical and AC-CSE the types must be the same.</a>
<a href="#20" id="20">Our first avenue of future work is to examine every pair of types in the language for opportunities to exploit overlapping expressions.</a>
<a href="#21" id="21">Distinct types would necessarily require a variety of approaches to exploit the overlap.</a>
<a href="#22" id="22">In some cases a new variable may help to transfer information between the two expressions, and in others a new constraint could capture the interaction.</a>
<a href="#23" id="23">Some pairs of overlapping constraints are intractable (such as two allDifferent constraints), in which case we would investigate approximations.</a>
<a href="#24" id="24">The second avenue of future work is to improve the generation of implied constraints that feed into AC-CSE.</a>
<a href="#25" id="25">At present, only sums are created, all coefficients are 1, only allDifferent and GCC are allowed as source constraints, and the scope of the implied sum constraint is the scope of the source constraint.</a>
<a href="#26" id="26">Firstly, when a sum overlaps with a subset of the variables in a source constraint, tighter bounds may be obtained by generating the implied sums on the overlap variables only.</a>
<a href="#27" id="27">Secondly, implied sums can be generated with coefficients that match other sums in the model, enabling AC-CSE.</a>
<a href="#28" id="28">Thirdly, other AC expressions such as products could be generated when appropriate.</a>
<a href="#29" id="29">Finally, a generic algorithm could be devised to generate implied sums from any constraint with appropriate properties, for example where all variables are interchangeable.</a>
</body>
</html>