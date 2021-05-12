<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:496">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work we proposed an alternative form of output for DAs called the health state.</a>
<a href="#1" id="1">A health state maps every component to a probability that it is faulty.</a>
<a href="#2" id="2">We argue that a health state is for many cases a more reasonable output than a single or k most probable diagnoses since it contains aggregated information over all the found diagnoses.</a>
<a href="#3" id="3">The health state provides an answer to a fundamental diagnostic question: which components is likely to be faulty.</a>
<a href="#4" id="4">It provides an overview of the state of the system that is readable by a human operator and can be useful for an automated troubleshooter.</a>
<a href="#5" id="5">We presented a simple and efficient method to generate a health state from an arbitrarily large set of diagnoses.</a>
<a href="#6" id="6">Two metrics were proposed to measure the quality of generated health states – Euclidean distance and the Area Under the Curve (AUC).</a>
<a href="#7" id="7">Next, we observed empirically that:</a>
<a href="#8" id="8">According to all quality metrics, a health state generated using more diagnoses is better (higher AUC, lower Euclidean distance and wasted efforts).</a>
<a href="#9" id="9">Thus, introducing an expected trade-off between the number of diagnoses used to generate a health state and its quality.</a>
<a href="#10" id="10">Empirically, the AUC metric provided a finer grained control over this trade-off, allowing easier parameter tuning.</a>
<a href="#11" id="11">For all quality metrics, the health state quality tends to converge quickly to a relatively high (i.e., good) value, where in most cases a fraction of the diagnoses are needed to obtain a health state that is almost as accurate as the one generated using all diagnoses.</a>
<a href="#12" id="12">A DAs that return diagnoses in increasing cardinality order have a tendency to converge faster while preserving high health state quality, but SAFARI [46], a stochastic DA, sometimes reaches convergence faster but resulting in a lower quality health state.</a>
<a href="#13" id="13">In many cases only a small subset of all minimal cardinality diagnoses was needed in order to reach this convergence.</a>
<a href="#14" id="14">The simple online stopping criteria we proposed for identifying when a health state with a high quality has been found and the search for more diagnoses can be halted was found to be very effective, successfully reaching a high quality health state by computing only a small subset of the diagnoses.</a>
<a href="#15" id="15">These findings highlight the usefulness of the health state as a way to consider and evaluate a set of diagnoses.</a>
<a href="#16" id="16">There are many exciting topics for future work.</a>
<a href="#17" id="17">Some were outlined in Section 7, dealing with more complex system models.</a>
<a href="#18" id="18">Another interesting future research is to use and test our health state in the context of probing and testing [15], [16].</a>
<a href="#19" id="19">Probing methods assess where the placement of probes will be most beneficial.</a>
<a href="#20" id="20">It will be interesting to examine the performance of probing and testing approaches when using upon a subset of the diagnoses given by a stopping criteria based on the health state.</a>
<a href="#21" id="21">In addition, an interesting topic for future work is to use the values in the health state as a heuristic for guiding a DA to find more diagnoses.</a>
</body>
</html>