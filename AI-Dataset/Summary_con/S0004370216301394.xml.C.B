<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:174">
</head>
<body bgcolor="white">
<a href="#0" id="0">We proposed a framework for query efficient posterior estimation for expensive blackbox likelihood evaluations.</a>
<a href="#1" id="1">Our methods use GPs and are based on popular ideas in Bayesian active learning.</a>
<a href="#2" id="2">We demonstrate that our methods outperform natural alternatives in practice.</a>
<a href="#3" id="3">Note that in Machine Learning it is uncommon to treat posterior estimation in a regression setting.</a>
<a href="#4" id="4">This is probably since the estimate will depend on the intricacies of the regression algorithm.</a>
<a href="#5" id="5">Thus if likelihood evaluations are inexpensive, MCMC seems like a natural choice due to its theoretical guarantees in the large sample regime.</a>
<a href="#6" id="6">However, our work demonstrates that when likelihood evaluations are expensive, such as in scientific simulations, treating posterior estimation in an active regression framework enables us to be significantly query efficient.</a>
<a href="#7" id="7">The proposed methods do not scale very well with dimension, which is a common problem with nonparametric methods.</a>
<a href="#8" id="8">Going forward we wish to tackle active posterior estimation in several dozens of dimensions.</a>
<a href="#9" id="9">A possible avenue would be to use ideas from some recent progress on high dimensional Bayesian Optimisation using additive models [11].</a>
</body>
</html>