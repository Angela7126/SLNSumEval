<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:470">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, the Bayesian network learning problem has been explored as an ILP problem.</a>
<a href="#1" id="1">In particular, attention has been focused on the problem of finding and adding appropriate cutting planes to speed the solution times.</a>
<a href="#2" id="2">Various aspects were studied and some found to be generally beneficial across a range of problem instances.</a>
<a href="#3" id="3">For others, impact was either modest or erratic on different instances.</a>
<a href="#4" id="4">Using cycle finding to determine cutting planes was highly effective when used in conjunction with a sub-IP approach.</a>
<a href="#5" id="5">The impact of adding constraints based on the convex hull of smaller BNs was much less evident.</a>
<a href="#6" id="6">When used in the best way, they improved performance more often than they degraded it, though for most datasets the difference in runtime was negligible.</a>
<a href="#7" id="7">The modest improvement associated with the additional classes of cut could call into question whether further work on additional cutting planes based on implied constraints truly merits attention.</a>
<a href="#8" id="8">Bartlett and Cussens [20] showed that including implied constraints based on the convex hull of a 3 node BN led to a measurable improvement, while [4] states inclusion of an implied constraint that at least one node has no parents led to a dramatic decrease in solving time.</a>
<a href="#9" id="9">On the other hand, a generalisation of cluster constraints to k-cluster constraints proposed by [3] has failed to prove to be of any notable benefit.</a>
<a href="#10" id="10">Clearly, different types of implied constraints vary vastly in their usefulness and further theoretical work is needed to understand why some are beneficial for this problem and others are not.</a>
<a href="#11" id="11">The results of the close cuts experiments are particularly interesting.</a>
<a href="#12" id="12">Close cuts could almost always provide an improvement in solving time, but only for the correct value of the α parameter, and there was no consistently good value for this parameter across datasets.</a>
<a href="#13" id="13">A similar observation could also be made for the maximum length of cycle to search for in the earlier experiment.</a>
<a href="#14" id="14">Though the technique was of clear benefit, the solution times for similar maximum lengths varied quite considerably and no value was best across the whole dataset.</a>
<a href="#15" id="15">These findings suggest that rather than fix the solver's method to some compromise ‘best’ configuration, a future approach may be to change the settings for individual problems.</a>
<a href="#16" id="16">The issue then becomes predicting appropriate solver settings for a previously unseen problem instance.</a>
<a href="#17" id="17">Malone et al. [26] provide a step in this direction.</a>
<a href="#18" id="18">Based on very simple characteristics of a problem instance they are able to determine quite accurately which of two Bayesian network learning algorithms will be quicker.</a>
<a href="#19" id="19">However, further work is clearly needed for this to be applicable here, where there are larger numbers of options from which to choose and where one might reasonably expect choosing from amongst various configurations of a single solver to be more complex than deciding between two entirely separate solvers.</a>
</body>
</html>