<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:335">
</head>
<body bgcolor="white">
<a href="#0" id="0">Hierarchical clustering is an important method of analysis.</a>
<a href="#1" id="1">Most existing work focuses on heuristics to scale these methods to huge data sets which is a valid research direction if data needs to be quickly organized into any meaningful structure.</a>
<a href="#2" id="2">However, some (often scientific) data sets can take years to collect and although they are much smaller, they require more precise analysis at the expense of time.</a>
<a href="#3" id="3">In particular, a good solution is not good enough and a better solution can yield significant insights.</a>
<a href="#4" id="4">In this work we explored two such data sets: language evolution and fMRI data.</a>
<a href="#5" id="5">In the former the evolution of one language from another is discovered and in the later the organization of patients according to their fMRI scans indicates the patients most at risk.</a>
<a href="#6" id="6">Here the previously mentioned heuristic methods perform not as well, which is significant since even small improvements are worthwhile.</a>
<a href="#7" id="7">We present to the best of our knowledge the first formulation of hierarchical clustering as an integer linear programming problem with an explicit objective function that is globally optimized.</a>
<a href="#8" id="8">Our formulation has several benefits.</a>
<a href="#9" id="9">It can find accurate hierarchies because it finds the global optimum.</a>
<a href="#10" id="10">We found this to be particularly important when the distance matrix contains noise (see Fig. 8).</a>
<a href="#11" id="11">Since we formalize the dendrogram creation with an objective function that is constrained we can easily relax and add constraints.</a>
<a href="#12" id="12">We showed that relaxing the dendrogram properties/constraints can lead to novel problem settings.</a>
<a href="#13" id="13">In particular we explored relaxing transitivity to discover overlapping clustering, where an instance can appear multiple times in the hierarchy.</a>
<a href="#14" id="14">We also showed that many of the guidance-style constraints (and more) used in hierarchical clustering can be represented as linear inequalities and hence added to the ILP.</a>
<a href="#15" id="15">We believe this work will move forward hierarchical clustering from being implemented as heuristic by making it formally modeled and optimized.</a>
<a href="#16" id="16">This occurred in the 1990s to non-hierarchical clustering with the introduction of linear algebra formulations such as spectral clustering but has not occurred in hierarchical clustering.</a>
</body>
</html>