<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:456">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper extends our preliminary work [40].</a>
<a href="#1" id="1">Multi-objective evolutionary algorithms, which typically use recombination operators, have been successfully applied in many practical situations, and some theoretical results of MOEAs have been derived in recent years.</a>
<a href="#2" id="2">However, previously analyzed MOEAs rarely incorporate recombination operators.</a>
<a href="#3" id="3">This paper theoretically investigates whether recombination operators can be useful in the scenario of multi-objective optimization.</a>
<a href="#4" id="4">The Pareto front is a property of multi-objective optimization that is not involved in single-objective optimization, thus we investigate whether a recombination operator can have an effect on solving the Pareto front of multi-objective problems.</a>
<a href="#5" id="5">First, we analyze the running time of two multi-objective evolutionary algorithms with a recombination operator: {a mathematical formula}MOEArecombonebit using one-bit mutation and {a mathematical formula}MOEArecombbitwise using bit-wise mutation, on two artificial model problems Weighted LPTNO and COCZ.</a>
<a href="#6" id="6">The analytic results of {a mathematical formula}MOEArecombonebit/MOEArecombbitwise turning recombination on and off on these two problems show the helpfulness of crossover.</a>
<a href="#7" id="7">By comparing with the previously analyzed MOEAs on the LOTZ (a special case of Weighted LPTNO) and COCZ problems, we find that {a mathematical formula}MOEArecombonebit and {a mathematical formula}MOEArecombbitwise are the most efficient.</a>
<a href="#8" id="8">This supports the conclusion that recombination operators can be useful for multi-objective optimization.</a>
<a href="#9" id="9">The analysis discloses that the recombination operator works in the studied situation by accelerating the filling of the Pareto front through recombining diverse optimal solutions found-so-far.</a>
<a href="#10" id="10">Then, we further examine the effect of recombination for solving the multi-objective minimum spanning tree problem, which is an NP-hard problem.</a>
<a href="#11" id="11">We derive the expected running time of {a mathematical formula}MOEArecombbitwise with crossover probability 0.5, and by comparing with the previously analyzed {a mathematical formula}MOEAbitwise, we find that recombination can still work.</a>
<a href="#12" id="12">We observe that the use of the bit-wise mutation does not show advantages over the one-bit mutation in the studied cases, while they have been shown to have different ability [54].</a>
<a href="#13" id="13">A question that will be investigated in the future is that when the bit-wise mutation leads to a better performance than the one-bit mutation.</a>
<a href="#14" id="14">We shall analyze {a mathematical formula}MOEArecombonebit and {a mathematical formula}MOEArecombbitwise on more realistic problems with more kinds of objective functions, and we will also try to identify problem classes for which the investigated recombination operator is helpful following [41].</a>
<a href="#15" id="15">There are several possible directions to extend this work in the future: first, other types as well as other usages of recombination operators in MOEAs could be investigated; second, it is also interesting to study the effect of recombination in different stages of MOEAs as well as the effect of different initialization of MOEAs; third, the interaction between mutation, recombination and selection operators is an important aspect for a full characterization of MOEAs; and moreover, analyzing MOEAs on more than two objectives is an interesting topic.</a>
</body>
</html>