<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:321">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper presents and analyzes two new efficient local search strategies for the Boolean Satisfiability (SAT) problem.</a>
<a href="#1" id="1">We start by proposing a local search strategy called configuration checking (CC) for SAT.</a>
<a href="#2" id="2">The CC strategy results in a simple local search algorithm for SAT called Swcc, which shows promising experimental results on random 3-SAT instances, and outperforms TNM, the winner of SAT Competition 2009.</a>
<a href="#3" id="3">However, the CC strategy for SAT is still in a nascent stage, and Swcc cannot yet compete with Sparrow2011, which won SAT Competition 2011 just after Swcc had been designed.</a>
<a href="#4" id="4">The CC strategy seems too strict in that it forbids flipping those variables even with great scores, if they do not satisfy the CC criterion.</a>
<a href="#5" id="5">We improve the CC strategy by adopting an aspiration mechanism, and get a new variable selection heuristic called configuration checking with aspiration (CCA).</a>
<a href="#6" id="6">The CCA heuristic leads to an improved algorithm called Swcca, which exhibits state-of-the-art performance on random 3-SAT instances and crafted ones.</a>
<a href="#7" id="7">The third contribution concerns improving local search algorithms for random k-SAT instances with k>3.</a>
<a href="#8" id="8">Although the SAT community has made great achievements in solving random 3-SAT instances, the progress lags far behind on random k-SAT instances with k>3.</a>
<a href="#9" id="9">This work proposes a new variable property called subscore, which is utilized to break ties in the CCA heuristic when candidate variables for flipping have the same score.</a>
<a href="#10" id="10">The resulting algorithm CCAsubscore is very efficient for solving random k-SAT instances with k>3, and significantly outperforms other state-of-the-art ones.</a>
<a href="#11" id="11">Combining Swcca and CCAsubscore, we obtain a local search SAT solver called CCASat, which was ranked first in the random track of SAT Challenge 2012.</a>
<a href="#12" id="12">Additionally, we perform theoretical analyses on the CC strategy and the subscore property, and show interesting results on these two heuristics.</a>
<a href="#13" id="13">Particularly, our analysis indicates that the CC strategy is more effective for k-SAT with smaller k, while the subscore notion is not suitable for solving random 3-SAT.</a>
</body>
</html>