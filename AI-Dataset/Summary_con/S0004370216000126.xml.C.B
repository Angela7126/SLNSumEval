<html>
<head>
<meta name="TextLength" content="SENT_NUM:21, WORD_NUM:466">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have proposed here a methodology (called Empirical Model Learning) for merging Machine Learning and optimization by extracting decision model components from data, which may come from a simulator or from the real system.</a>
<a href="#1" id="1">Our emphasis is on defining techniques for embedding ML models in Combinatorial Optimization, which should be designed so that the optimization engine can exploit the ML model for boosting the search process.</a>
<a href="#2" id="2">We have discussed the main steps of the methodology, using as motivating and running examples two thermal-aware workload dispatching problems.</a>
<a href="#3" id="3">The ML techniques adopted are Artificial Neural Network and Decision Trees that have been encoded in Local Search, Constraint Programming, Mixed Integer Non-Linear Programming (only ANNs) and SAT Modulo Theory (only DTs).</a>
<a href="#4" id="4">Designing a good empirical model may still be a non-trivial task, but allows for better accuracy w.r.t.</a>
<a href="#5" id="5">to expert designed heuristics.</a>
<a href="#6" id="6">Experiments show the clear advantages of using a data-extracted model in terms of quality of the final solutions.</a>
<a href="#7" id="7">Constraint Programming has been shown to be particularly effective, due to the expressive modeling language and the filtering algorithms.</a>
<a href="#8" id="8">Further improvements may be obtained by increasing the accuracy of the Empirical Models: for example, using Instructions Per Clock rather than CPIs allows to better characterize computation-intensive jobs, i.e. the most critical for efficiency prediction.</a>
<a href="#9" id="9">We have tested this approach and found that it leads to significant improvements over ANN1, but not over ANN0.</a>
<a href="#10" id="10">The Empirical Model Learning approach enables the application of optimization techniques to complex real world problems that used to be either very hard or impossible to tackle.</a>
<a href="#11" id="11">As a main benefit, the approach opens up new application areas.</a>
<a href="#12" id="12">In particular, EML may be instrumental in bridging the gap between predictive and prescriptive analytics.</a>
<a href="#13" id="13">As a particular case, EML could be used to perform decision making over a controlled system.</a>
<a href="#14" id="14">In such a situation, EML allows one to use a high-level optimizer to steer the behavior of the existing controller, with no need to know its internal details and potentially without direct communication.</a>
<a href="#15" id="15">This property could be exploited to ease the integration with legacy systems, and to tackle large scale problems via multi-level optimization.</a>
<a href="#16" id="16">Active learning could be incorporated in the EML approach by periodically re-training the ML model to improve its accuracy.</a>
<a href="#17" id="17">The same approach could be employed to design self-adapting systems, capable of tracking changes in their operating conditions.</a>
<a href="#18" id="18">In principle, this could include also disruptive events, such as the addition of new system components.</a>
<a href="#19" id="19">Finally, another interesting topic for future research concerns the relation between predictive models and uncertainty: many Machine Learning models are designed to deal with uncertain data, and can provide information (e.g. probability distributions or confidence intervals) about the robustness of their predictions.</a>
<a href="#20" id="20">These capabilities could be exploited to design more robust and reliable decision making systems for real world problems.</a>
</body>
</html>