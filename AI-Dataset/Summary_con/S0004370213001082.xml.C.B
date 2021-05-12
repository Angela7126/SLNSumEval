<html>
<head>
<meta name="TextLength" content="SENT_NUM:9, WORD_NUM:295">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we assessed and advanced the state of the art in predicting the performance of algorithms for hard combinatorial problems.</a>
<a href="#1" id="1">We proposed new techniques for building predictive models, with a particular focus on improving prediction accuracy for parameterized algorithms, and also introduced a wealth of new features for three of the most widely studied NP-hard problems (SAT, MIP and TSP) that benefit all models.</a>
<a href="#2" id="2">We conducted the largest experimental study of which we are aware—predicting the performance of 11 algorithms on 35 instance distributions from SAT, MIP and TSP—comparing our new modelling approaches with a comprehensive set of methods from the literature.</a>
<a href="#3" id="3">We showed that our new approaches—chiefly those based on random forests, but also approximate Gaussian processes—offer the best performance, whether we consider predictions for previously unseen problem instances for parameterless algorithms, new parameter settings for a parameterized algorithm running on a single problem instance, or parameterized algorithms being run both with new parameter values and on previously unseen problem instances.</a>
<a href="#4" id="4">We also demonstrated in each of these settings that very accurate predictions (correlation coefficients between predicted and true runtime exceeding 0.9) are possible based on very small amounts of training data (only hundreds of runtime observations).</a>
<a href="#5" id="5">Finally, we demonstrated how our best-performing model, random forests, could be improved further by better handling data from prematurely terminated runs.</a>
<a href="#6" id="6">Overall, we showed that our methods are fast, general, and achieve good, robust performance.</a>
<a href="#7" id="7">We hope they will be useful to a wide variety of researchers who seek to model algorithm performance for algorithm analysis, scheduling, algorithm portfolio construction, automated algorithm configuration, and other applications.</a>
<a href="#8" id="8">The Matlab source code for our models, the data and source code to reproduce our experiments, and an online appendix containing additional experimental results, are available online at http://www.cs.ubc.ca/labs/beta/Projects/EPMs.</a>
</body>
</html>