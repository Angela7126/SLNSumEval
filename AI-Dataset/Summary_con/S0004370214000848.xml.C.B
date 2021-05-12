<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:420">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we introduced the concept of short-sighted probabilistic planning through depth-based short-sighted SSPs, a special case of SSPs in which every state has a nonzero probability of being reached using at most t actions.</a>
<a href="#1" id="1">Short-sighted probabilistic planning is a general technique that is used directly by the Short-Sighted Probabilistic Planner (SSiPP) algorithm.</a>
<a href="#2" id="2">We also presented how to combine short-sighted probabilistic planning with two other techniques for probabilistic planning – labeling and determinizations – resulting in two new probabilistic planners, Labeled-SSiPP and SSiPP-FF, respectively.</a>
<a href="#3" id="3">The goal of Labeled-SSiPP is to improve the convergence time of SSiPP to the ϵ-consistent solution.</a>
<a href="#4" id="4">This improvement is achieved by adding the labeling mechanism used by LRTDP.</a>
<a href="#5" id="5">Moreover, Labeled-SSiPP takes advantage of states labeled as solved to prune the generated short-sighted SSPs as an ϵ-consistent solution from these labeled states is already known.</a>
<a href="#6" id="6">For Labeled-SSiPP, we proved an upper bound on the number of iterations necessary to converge to an ϵ-consistent solution.</a>
<a href="#7" id="7">On the empirical side, we showed that Labeled-SSiPP, using LRTDP as an underlying SSP solver, outperforms SSiPP, LRTDP, and FTVI on problems from the International Probabilistic Planning Competition (IPPC) and in control problems with a low percentage of relevant states.</a>
<a href="#8" id="8">We also introduced another probabilistic planner, SSiPP-FF, which combines short-sighted probabilistic planning and determinizations to compute suboptimal solutions more efficiently.</a>
<a href="#9" id="9">The empirical results obtained show that SSiPP-FF successfully combines the behavior of SSiPP and FF-Replan through high coverage in problems without dead ends and a significant improvement the coverage of FF-Replan in problems with dead ends.</a>
<a href="#10" id="10">The results also show that SSiPP and SSiPP-FF consistently outperform the other planners in all the problems of the exploding blocks world, a probabilistic interesting domain.</a>
<a href="#11" id="11">Our empirical results also show that SSiPP and its extensions have a state-of-the-art performance when the value of t is randomly selected for each depth-based short-sighted SSP.</a>
<a href="#12" id="12">Because depth-based short-sighted SSPs can exploit the underlying structure of the problem through the parameter t, the performance of SSiPP and its extensions can be further improved by optimizing the value of t for the domain of the problem or for the problem being solved.</a>
<a href="#13" id="13">In the future, we plan to explore different methods to automatically adapt the value of t for a given problem, e.g., to model the problem of finding the best t as a multi-armed bandit problem.</a>
<a href="#14" id="14">Our ongoing research agenda also includes (i) exploring different underlying SSP solvers for SSiPP (e.g., ILAO* [12]); (ii) combining SSiPP and Robust-FF; and (iii) exploring efficient methods to prune the generated short-sighted SSPs.</a>
</body>
</html>