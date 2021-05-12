<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:528">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have proposed a novel approach to management of uncertainty during ranking the trial solutions due to possible creeping of noise in the fitness landscapes of a MOO problem.</a>
<a href="#1" id="1">Although most of the traditional evolutionary MOO algorithms can be extended with the principles of uncertainty management introduced herein, we realized the strategies in the DEMO algorithm for its quality performance with respect to both runtime accuracy and computational complexity.</a>
<a href="#2" id="2">The integrity of the work lies in the following: (1) adaptive selection of the sample size for the periodic fitness evaluation of a trial solution based on the fitness variance in the subpopulation surrounding it; (2) evaluation of the expected value of the fitness samples of a trial solution based on the nonuniform fitness sample distribution in the entire sample space; and (3) enhancing the robustness in selecting trial solutions from the same-rank candidate pool based on the selection probability influenced jointly by the crowding distance metric and the probability of nonoccurrence of rare (probably noisy) fitness samples.</a>
<a href="#3" id="3">The adaptive selection of the sample size for fitness reevaluation of a trial solution is significant for the efficient trade-off between runtime complexity and computational accuracy.</a>
<a href="#4" id="4">A nonlinear functional form, induced by the function {a mathematical formula}1−exp⁡(−v), is used to proficiently capture the variation of the sample size with the fitness variance v (which is an indirect implication of the extent of noise contamination) in the local neighborhood of a given trial solution.</a>
<a href="#5" id="5">The second noise handling strategy provides a unique fitness estimate of a trial solution based on the expectation of the measured noisy fitness samples.</a>
<a href="#6" id="6">It differs from the conventional averaging approach which considers equal probability of occurrence for all the fitness samples.</a>
<a href="#7" id="7">Moreover, the proposed strategy recommends a novel method of prioritizing the fitness samples in more crowded regions in the sample space, while reducing the impact of the noisy rare fitness samples, during evaluation of the expected fitness estimate.</a>
<a href="#8" id="8">The PS strategy, adopted as the third extension of the traditional DEMO algorithm, paves a way for the decisive selection of quality solutions in the next-generation population, simultaneously ensuring population diversity in the objective spaces.</a>
<a href="#9" id="9">The stratagem circumvents the dismissal of quality solutions over generations by limiting the impact of misleading individuals in the noisy environment.</a>
<a href="#10" id="10">We undertook a comparative study of the proposed DENMO algorithm with nine state-of-the-art noisy MOO algorithms.</a>
<a href="#11" id="11">The efficacy of all the contender algorithms to handle uncertainty was scrutinized with respect to the noisy version of a test suite of 23 CEC'2009 benchmark functions.</a>
<a href="#12" id="12">The performance of all the algorithms was compared on the basis of four performance metrics; IGD, Δ, ER, and HVR.</a>
<a href="#13" id="13">Statistical significance of the results was judged with the nonparametric Friedman test, the Iman-Davenport statistic, the Holm test, and Bonferroni–Dunn post hoc analysis.</a>
<a href="#14" id="14">The experimental study clearly reveals that DENMO outperforms its competitor algorithms in a statistically significant manner with respect to four standard metrics in the presence of five different stochastic noise distributions (Gaussian, Poisson, Rayleigh, exponential, and random noise of limited amplitude).</a>
<a href="#15" id="15">In addition, one more fundamental claim of this paper is that DENMO outperforms its competitors both in consistency of quality performance and in expected runtime.</a>
</body>
</html>