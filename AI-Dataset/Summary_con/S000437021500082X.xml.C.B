<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:290">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we investigated the performance of a new class of algorithms, called L3, which uses a case base to transfer knowledge as heuristics between domains.</a>
<a href="#1" id="1">Two algorithms of this class were investigated: L3-Q, based on Q-Learning, and L3-SARSA(λ), based on the gradient descent SARSA(λ).</a>
<a href="#2" id="2">The transference of heuristics across domains makes L3 robust to negative transfers, which is the major contribution of these algorithms to the state of the art of transfer learning in reinforcement learning.</a>
<a href="#3" id="3">In order to show the generality of L3, this algorithm was applied to benchmark domains in RL whose results show that L3 outperforms Q-Learning (which is traditionally used as baseline algorithm), a Heuristically Accelerated RL algorithm and two state-of-the-art transfer learning algorithms.</a>
<a href="#4" id="4">However, L3 was not capable of mapping actions between domains in which there is a one-to-many possibility of mappings, and vice-versa.</a>
<a href="#5" id="5">This issue shall be considered in future research.</a>
<a href="#6" id="6">Future work shall also consider further possible relevance measures for case selection, other than the reward received.</a>
<a href="#7" id="7">A possible candidate for such measure could be the probability assigned to a possible case to be used.</a>
<a href="#8" id="8">In general, the more a case is used in the source domain, the more relevant it is.</a>
<a href="#9" id="9">Whether or not the use of these cases in the target domain results in a better performance than that reported in this paper is an issued to be investigated.</a>
<a href="#10" id="10">In our experiments, cases are single step: they represent a single action to be taken in a state.</a>
<a href="#11" id="11">However, we believe that this approach could easily be made more general, in the sense that sequences of actions can also be stored in the case base and used as heuristics.</a>
<a href="#12" id="12">Experiments to validate this hypothesis are a matter for future work.</a>
</body>
</html>