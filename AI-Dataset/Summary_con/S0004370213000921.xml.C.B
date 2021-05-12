<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:539">
</head>
<body bgcolor="white">
<a href="#0" id="0">This work proposed and analyzed two efficient local search heuristics for SAT, namely configuration checking (CC) and subscore, which break fresh ground from traditional SAT local search techniques.</a>
<a href="#1" id="1">These novel heuristics have led to three efficient SLS algorithms for SAT, namely Swcc, Swcca and CCAsubscore.</a>
<a href="#2" id="2">Swcc is our first endeavor to apply the idea of configuration checking (CC) to local search for SAT.</a>
<a href="#3" id="3">Swcca enhances Swcc by combining the CC strategy with an aspiration mechanism, while CCAsubscore improves Swcca by utilizing the notion of subscore.</a>
<a href="#4" id="4">Our experiments on random 3-SAT instances indicate that Swcc outperforms TNM, and Swcca does Sparrow2011.</a>
<a href="#5" id="5">Note that TNM and Sparrow2011 wins the random satisfiable category of SAT Competition 2009 and 2011 respectively.</a>
<a href="#6" id="6">Moreover, CCAsubscore significantly outperforms existing local search algorithms according to our experiments on large random 5-SAT and 7-SAT instances.</a>
<a href="#7" id="7">Notably, the SAT solver CCASat which combines Swcca and CCAsubscore, was ranked the first in the random track of SAT Challenge 2012.</a>
<a href="#8" id="8">The CC strategy for SAT remembers each variableʼs configuration (truth values of all its neighboring variables), and forbids a variable to be flipped if its configuration has not been changed since its last flip.</a>
<a href="#9" id="9">The CC strategy is further enhanced by an aspiration mechanism, resulting in a new pickVar heuristic called configuration checking with aspiration (CCA).</a>
<a href="#10" id="10">According to CCA, there are two levels with different priorities in the greedy mode.</a>
<a href="#11" id="11">Those variables whose flips can bring a big benefit have a chance to be selected on the second level, even if they do not satisfy the CC criterion.</a>
<a href="#12" id="12">The subscore property takes into account the transformations between critical clauses and steady clauses.</a>
<a href="#13" id="13">By utilizing subscore to break ties in the CCA framework, CCAsubscore achieves much better performance on random k-SAT instances with {a mathematical formula}k>3 than existing SLS solvers do.</a>
<a href="#14" id="14">The notion of subscore turns out very promising towards improving local search algorithms for random k-SAT instances with {a mathematical formula}k>3.</a>
<a href="#15" id="15">This is remarkable, as in the past two decades, very few progress has been made in this direction.</a>
<a href="#16" id="16">Finally, we performed further analyses to gain deeper understandings of the CC strategy and the subscore property.</a>
<a href="#17" id="17">We reveal the relationships of the CC strategy with the promising decreasing variable exploiting strategy and the tabu method, in terms of forbidding strength.</a>
<a href="#18" id="18">Moreover, we give insights about the size of each variableʼs neighborhood in random k-SAT instances and its impact on the effectiveness of the CC strategy.</a>
<a href="#19" id="19">We also discuss the complexity of two different implementations for the CC strategy, including the approximate one in this paper and an accurate one.</a>
<a href="#20" id="20">For the subscore property, we show that it is unsuitable for solving random 3-SAT instances.</a>
<a href="#21" id="21">As for future work, we would like to design more sophisticated variable property and scoring functions related to subscore, which we believe can further improve the state of the art in SLS algorithms for SAT, especially for random k-SAT instances with {a mathematical formula}k>3.</a>
<a href="#22" id="22">Given the promising results of Swcca on crafted instances, we also believe the CC heuristic can be helpful for solving such instances and we would like to go further in this direction by combining CC with other algorithmic techniques.</a>
<a href="#23" id="23">Also we would like to apply the CC heuristic to other combinatorial search problems.</a>
</body>
</html>