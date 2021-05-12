<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:359">
</head>
<body bgcolor="white">
<a href="#0" id="0">This work contributes to the research direction of harnessing constraint solving for developing novel types of generic data analysis techniques.</a>
<a href="#1" id="1">The focus of our study is the applicability of state-of-the-art Boolean optimization procedures to cost-optimal correlation clustering in both unconstrained and constrained settings.</a>
<a href="#2" id="2">To this end, we presented a novel MaxSAT-based framework for solving correlation clustering.</a>
<a href="#3" id="3">Our approach is based on casting the clustering problem declaratively as weighted partial maximum satisfiability, and using a generic MaxSAT solver for finding cost-optimal clusterings.</a>
<a href="#4" id="4">We studied three different encodings of correlation clustering as MaxSAT, and reported on an experimental evaluation, comparing both the time required to solve the resulting MaxSAT instances, and the quality of the clusterings obtained.</a>
<a href="#5" id="5">We compared the MaxSAT-based approach to previously proposed both exact (integer linear and quadratic programming based) and approximative (specialized local search and approximation algorithms and semi-definite programming) approaches on real-world datasets.</a>
<a href="#6" id="6">The MaxSAT approach scales better than the exact integer linear and quadratic programming approaches, and provides clusterings of significantly lower cost than the approximative algorithms, especially when the input data is sparse.</a>
<a href="#7" id="7">Due to the intrinsic computational hardness of correlation clustering, we acknowledge that a potential issue with our approach is scalability, especially scaling the MaxSAT-based approach to very large datasets (with tens of thousands of data points).</a>
<a href="#8" id="8">Nevertheless, the approach can provide cost-optimal clusterings on real-world datasets with close to a thousand points.</a>
<a href="#9" id="9">The approach is also flexible when it comes to satisfying user-specified constraints, i.e., in constrained correlation clustering.</a>
<a href="#10" id="10">The running times of the approach can notably decrease in a constrained setting, allowing for solving larger datasets faster compared to the non-constrained setting.</a>
<a href="#11" id="11">This is in stark contrast with local search algorithms which easily suffer from over-constraining in constrained settings.</a>
<a href="#12" id="12">It is conceivable that our approach can be improved also by foreseeable improvements to generic MaxSAT solvers and by developing domain-specific parallelization schemes, as well as by specialized constraint optimization techniques and heuristics for the problem domain.</a>
<a href="#13" id="13">Yet another interesting direction would be to study the applicability of Large Neighborhood Search which combine local search strategies for fixing a subspace of the search space to which to apply exact search techniques.</a>
</body>
</html>