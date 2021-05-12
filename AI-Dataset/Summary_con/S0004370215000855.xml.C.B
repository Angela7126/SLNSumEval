<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:514">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we presented a generic approach to planning with incomplete information.</a>
<a href="#1" id="1">The basic idea underlying the proposed approach is that belief states can be represented using specific types of formulae and reasoning about effects of actions in presence of incomplete information can be formulated using suitable operations over formulae.</a>
<a href="#2" id="2">We defined a notion called a representation with a set of associated operations.</a>
<a href="#3" id="3">We used these operations to develop a transition function for computing the successor belief states.</a>
<a href="#4" id="4">We devised a set of abstract algorithms for computing the transition function and developing conformant planners.</a>
<a href="#5" id="5">We investigated three different representations, minimal-DNF, minimal-CNF, and prime implicates, and illustrated the general approach by defining their operations and providing a concrete implementation of these operations for each representation.</a>
<a href="#6" id="6">We discussed the heuristics used in the resulting conformant planners and evaluated their performance against state-of-the-art conformant planners using benchmarks from the literature and several variations of these benchmarks.</a>
<a href="#7" id="7">The experimental evaluation shows that our approach is competitive with state-of-the-art planning systems.</a>
<a href="#8" id="8">We related our method for belief state representation with previously developed method such as OBDD or target compilation languages.</a>
<a href="#9" id="9">We observe that the present work focuses on the problem of representation of belief states and conformant planning in deterministic domains.</a>
<a href="#10" id="10">As such, a natural extension of this work is an investigation of using representation in dealing with non-deterministic actions and sensing actions for conformant AND/OR contingency planning.</a>
<a href="#11" id="11">Some preliminary results in this direction can be found in [37].</a>
<a href="#12" id="12">Furthermore, as the three planners Dnf, Cnf, and PIP employ fairly simple heuristics, it is interesting to see whether representation dependent heuristics for conformant planning could be devised and employed in Algorithm 1.</a>
<a href="#13" id="13">Last but not least, the problem of which representation should be used given a particular problem is also a problem worth investigating.</a>
<a href="#14" id="14">This is because Dnf, Cnf, and PIP yield similar performance on the first three test suites, their efficiency and scalability are significantly different in the last one.</a>
<a href="#15" id="15">What is the reason for this difference?</a>
<a href="#16" id="16">A closer look at the theoretical size of the initial belief state of all the problems in the experiment reveals that the size of the initial μDNF-state is relatively small in the first three test suites while it is extremely large in the last one.</a>
<a href="#17" id="17">Indeed, in the fourth test suite, the size of the initial μDNF-state is exponentially in the size of the problem while the size of the initial μCNF-state or PI-state is polynomial.</a>
<a href="#18" id="18">As such, we hypothesize that the minimal-DNF representation can be a good choice on problems where the size of the initial μDNF-state is not very large; otherwise (i.e., for problems where the size of the initial μDNF-state is much larger than equivalent CNF formulae), if the size of the initial PI-state is comparable to the size of the initial μCNF-state then the prime implicate representation is a good choice.</a>
<a href="#19" id="19">If the size of the PI-states is significantly larger than the size of the initial μCNF-state then the minimal-CNF representation should be used.</a>
<a href="#20" id="20">Verifying this hypothesis is thus an interesting task for a future work.</a>
</body>
</html>