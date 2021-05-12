<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:525">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we provide an extensive analysis of algorithms for solving and playing zero-sum extensive-form games with perfect information and simultaneous moves.</a>
<a href="#1" id="1">We describe a collection of exact algorithms based on backward induction as well as a collection of Monte Carlo tree search algorithms including our novel algorithms {a mathematical formula}DOαβ, {a mathematical formula}BIαβ, SM-OOS and SM-MCTS with regret matching selection function.</a>
<a href="#2" id="2">We empirically compare the performance of these algorithms on six substantially different games in two different settings.</a>
<a href="#3" id="3">In the offline equilibrium computation setting, we show that our novel algorithm based on backward induction, {a mathematical formula}DOαβ, is able to prune large parts of the search space.</a>
<a href="#4" id="4">In most games, {a mathematical formula}DOαβ is several orders of magnitude faster than the classical backward induction and it is never significantly outperformed by any of its competitors.</a>
<a href="#5" id="5">The only benefit of the sampling algorithms in the offline setting is a to get a rough approximation of the equilibrium solution in a short time.</a>
<a href="#6" id="6">Their results are often inconsistent with short computation times.</a>
<a href="#7" id="7">Given enough time, the results clearly show that SM-OOS achieves the fastest convergence to a Nash equilibrium.</a>
<a href="#8" id="8">Finally, our offline experiments also explained different behavior reported in variants of SM-MCTS with UCT selection.</a>
<a href="#9" id="9">We have shown that adding randomization to tie-breaking rules can significantly improve the performance of this algorithm.</a>
<a href="#10" id="10">The success in the offline equilibrium computation is, however, not a very good indicator of the game playing performance in the online setting of head-to-head matches.</a>
<a href="#11" id="11">First of all, the sizes of the games used for online experiments are too large for exact algorithms to be applicable without a domain-specific evaluation function.</a>
<a href="#12" id="12">Performance of the representative of the exact algorithms, {a mathematical formula}DOαβ, depends heavily on the accuracy of the used evaluation function.</a>
<a href="#13" id="13">Secondly, in spite of the fastest convergence of SM-OOS among the sampling algorithms, SM-OOS does not always perform well in the online game playing.</a>
<a href="#14" id="14">This is mainly due to the large variance of the regret updates that increases significantly in these large games.</a>
<a href="#15" id="15">Among the remaining sampling algorithms, SM-MCTS based on regret matching is often very good, but sometimes it was outperformed by SM-MCTS with UCT selection, especially in games that require less randomized strategies.</a>
<a href="#16" id="16">Our work opens several interesting directions for future research.</a>
<a href="#17" id="17">After introducing a strong pruning algorithm, it is of interest to formally study the limitations of pruning for this class of games, similarly to the theory developed for games with sequential moves.</a>
<a href="#18" id="18">Future work could show if these pruning techniques can be substantially improved or if they are in some sense optimal.</a>
<a href="#19" id="19">The main prerequisite is, however, estimating the expected number of iterations of the double-oracle algorithms for single step matrix games, which still remains an open problem.</a>
<a href="#20" id="20">Furthermore, running large head-to-head tournaments for evaluating the game playing performance is time consuming, sensitive to setting correct parameters, and provides only limited insights into the performance of the algorithms.</a>
<a href="#21" id="21">Proximity to the Nash equilibrium is not always a good indicator of game playing performance; hence, it is interesting to study alternative measures of quality of the algorithms that would better predict their game-playing performance in large games.</a>
</body>
</html>