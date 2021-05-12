<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:465">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have developed a general framework that has enabled the understanding of several aspects of dropout with good mathematical precision.</a>
<a href="#1" id="1">Dropout is an efficient approximation to training all possible sub-models of a given architecture and taking their average.</a>
<a href="#2" id="2">While several theoretical questions regarding both the static and dynamic properties of dropout require further investigations, for instance its generalization properties, the existing framework clarifies the ensemble averaging properties of dropout, as well as its regularization properties.</a>
<a href="#3" id="3">In particular, it shows that the three standard approaches to regularizing large models and avoiding overfitting: (1) ensemble averaging; (2) adding noise; and (3) adding regularization terms (equivalent to Bayesian priors) to the error functions, are all present in dropout and thus may be viewed in a more unified manner.</a>
<a href="#4" id="4">Dropout wants to produce robust units that do not depend on the details of the activation of other individual units.</a>
<a href="#5" id="5">As a result, it seeks to produce units with activities that have small dropout variance, across dropout subnetworks.</a>
<a href="#6" id="6">This partial variance minimization is achieved by keeping the weights small and using sparse encoding, which in turn increases the accuracy of the dropout approximation and the degree of self-consistency.</a>
<a href="#7" id="7">Thus, in some sense, by using small weights and sparse coding, dropout leads to large but energy efficient networks, which could potentially have some biological relevance as it is well known that carbon-based computing is orders of magnitude more efficient than silicon-based computing.</a>
<a href="#8" id="8">It is worth to consider which other classes of models, besides, linear and non-linear feedforward networks, may benefit from dropout.</a>
<a href="#9" id="9">Some form of dropout ought to work, for instance, with Boltzmann machines or Hopfield networks.</a>
<a href="#10" id="10">Furthermore, while dropout has already been successfully applied to several real-life problems, many more remain to be tested.</a>
<a href="#11" id="11">Among these, the problem of predicting quantitative phenotypic traits, such as height, from genetic data, such as single nucleotide polymorphisms (SNPs), is worth mentioning.</a>
<a href="#12" id="12">While genomic data is growing rapidly, for many complex traits we are still in the ill-posed regime where typically the number of loci where genetic variation occurs exceeds the number of training examples.</a>
<a href="#13" id="13">Thus the best current models are typically highly (L1) regularized linear models, and these have had limited success.</a>
<a href="#14" id="14">With its strong regularization properties, dropout is a promising algorithm that could be applied to these questions, using both simple linear or logistic regression models, as well as more complex models, with the potential for also capturing epistatic interactions.</a>
<a href="#15" id="15">Finally, at first sight dropout seems like another clever hack.</a>
<a href="#16" id="16">More careful analysis, however reveals an underlying web of elegant mathematical properties.</a>
<a href="#17" id="17">This mathematical structure is unlikely to be the result of chance alone and leads one to suspect that dropout is more than a clever hack and that over time it may become an important concept for AI and machine learning.</a>
</body>
</html>