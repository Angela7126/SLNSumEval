<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:332">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have studied the complexity of axiom pinpointing and several related decision, counting and enumeration problems for lightweight description logics.</a>
<a href="#1" id="1">Using different reductions and novel algorithms, we were able to find tight complexity bounds for most of the problems and languages considered.</a>
<a href="#2" id="2">All these results are summarised in Table 5.</a>
<a href="#3" id="3">One important thing to consider is that our focus here is on the computational complexity classes, and not on the specific resource consumption needed to solve the problem.</a>
<a href="#4" id="4">For instance, for most of our logics, we have proven a polynomial upper bound for is-mina using the black-box method described in Algorithm 1.</a>
<a href="#5" id="5">Since entailment of Horn formulas is decidable in linear time, it is easy to see that our algorithm yields a quadratic decision procedure in this setting.</a>
<a href="#6" id="6">However, it was recently shown, using specialised techniques, that this problem is in fact decidable in linear time [68].</a>
<a href="#7" id="7">Similarly, a more fine-grained run-time analysis might be required to achieve efficient algorithms even in the tractable cases.</a>
<a href="#8" id="8">A promising approach in this direction is to exploit the ideas already developed for efficient MUS enumeration [14], [69].</a>
<a href="#9" id="9">Similarly, one should keep in mind that all the hardness results presented correspond to the worst-case behaviour of the problems.</a>
<a href="#10" id="10">Indeed, different tools have been implemented for enumerating MinAs in Horn [68], {a mathematical formula}EL[70], [71], [72], [73], [74], and even more expressive logics [7], [9], [38], [75].</a>
<a href="#11" id="11">Empirical evaluations over such systems have shown that axiom pinpointing and other related tasks are feasible in practice, for realistic ontologies.</a>
<a href="#12" id="12">As future work, we intend to close the few remaining gaps in the complexity table.</a>
<a href="#13" id="13">We are also interested in dealing with other enumeration orderings and preference relationships between the MinAs.</a>
<a href="#14" id="14">Another important path of research is to understand how the panorama changes in the presence of knowledge about individuals (known as ABoxes in the DL community) or data, and with more complex entailments such as queries.</a>
<a href="#15" id="15">In such cases, a parameterised study of the complexity may become relevant.</a>
</body>
</html>