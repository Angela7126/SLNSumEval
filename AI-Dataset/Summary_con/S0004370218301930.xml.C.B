<html>
<head>
<meta name="TextLength" content="SENT_NUM:35, WORD_NUM:836">
</head>
<body bgcolor="white">
<a href="#0" id="0">The “best-shot” public goods game (PGG) is a graphical game, where agents wish to use some good and can either purchase it (for a finite cost) or use it for free if some agent in their neighborhood obtains the good (cf.</a>
<a href="#1" id="1">[3], [4]).</a>
<a href="#2" id="2">The utility for agents who use the good without purchasing it is maximal, is lower to agents who use the good and purchase it, and is the lowest for agents who do not purchase it and have no neighbor who does.</a>
<a href="#3" id="3">For the general version of the PGG the utility of agents increases if they have several neighbors who purchase the good.</a>
<a href="#4" id="4">The general version of PGG is shown to be an ordinal potential game.</a>
<a href="#5" id="5">This implies the convergence of better-response dynamics to a stable state (a pure Nash equilibrium) [10].</a>
<a href="#6" id="6">The better-response dynamics is shown to converge in a number of steps that is bounded by {a mathematical formula}2⋅K⋅n2, where n is the number of agents and {a mathematical formula}K is the maximal number of neighbors that can increase the utility of a neighboring agent by purchasing the good.</a>
<a href="#7" id="7">Despite its ability to converge to a stable state, it is shown that better-response tends to converge to outcomes of low efficiency.</a>
<a href="#8" id="8">Therefore, an algorithm that searches for stable outcomes of high efficiency is desired.</a>
<a href="#9" id="9">An iterative distributed search algorithm for finding a stable outcome of improved efficiency in “best-shot” public goods games has been proposed.</a>
<a href="#10" id="10">The algorithm iterates among all players in the game in a fixed order and each player in its turn exchanges messages with the players that interact with it (e.g., its neighbors in the game).</a>
<a href="#11" id="11">Messages propose the selected strategy of the player and in response other players, that are affected by it, may offer transfer of funds in order to secure a desired outcome.</a>
<a href="#12" id="12">One can think of the proposed improvement procedure as an extension to the well known better-response mechanism (cf.</a>
<a href="#13" id="13">[21], [22]) that uses transfers of funds.</a>
<a href="#14" id="14">The proposed algorithm is guaranteed to converge to a state that is of higher efficiency than its initial state, for the simple version of PGG.</a>
<a href="#15" id="15">This is in contrast to standard best response that does not address efficiency at all.</a>
<a href="#16" id="16">The final state to which the algorithm converges can be stabilized by the use of transfers of funds among the players who participate in the game.</a>
<a href="#17" id="17">A transfer function that can achieve stability is computed by the players running the algorithm during its run.</a>
<a href="#18" id="18">Since the transfers that secure stability form a binding contract among all players, that is computed during the iterative search, it is natural to think of them as side-payments [13].</a>
<a href="#19" id="19">An extensive experimental evaluation shows an improvement in social welfare, and one that is significantly higher than those achieved by the better-response dynamics, for general version of the PGG.</a>
<a href="#20" id="20">These results emphasize the importance of the proposed improvement procedure despite the fact that there is no theoretical guarantee regarding the efficiency of the resulting outcomes.</a>
<a href="#21" id="21">Additionally, both better-response and the improvement procedure have a polynomial bound on the number of the improvement steps, that enables to apply them to large scale social networks.</a>
<a href="#22" id="22">It is interesting to consider the results on PGGs from the point of view of potential games.</a>
<a href="#23" id="23">It was shown in Section 3 that one can guarantee efficient stable solutions to the general version of PGGs by using the mechanism of side-payments within the framework of best response.</a>
<a href="#24" id="24">This raises the immediate question whether similar algorithms that use side-payments can converge to stable solutions of improved efficiencies also in games that are not potential games.</a>
<a href="#25" id="25">It turns out that this question can be answered in the affirmative, though with a weaker guarantee on efficiency, also in non-potential games.</a>
<a href="#26" id="26">This is the focus of a further study that is now being completed.</a>
<a href="#27" id="27">The algorithms proposed by the present study fall into the class of distributed local search (cf.</a>
<a href="#28" id="28">[23], [24], [25], [26]) and in particular for asymmetric distributed constraints problems (ADCOPs) which are equivalent to multi-agents games (cf.</a>
<a href="#29" id="29">[27], [28]).</a>
<a href="#30" id="30">It is important to note the major difference between existing distributed local search algorithms and the algorithms proposed by the present paper.</a>
<a href="#31" id="31">First and foremost, local search algorithms on either DCOPs or ADCOPs are not guaranteed to converge [23], [26].</a>
<a href="#32" id="32">Second, standard local search algorithms may converge to a stable state (e.g., a PNE) on asymmetric DCOPs but they have no guarantee on the efficiency of the resulting solution.</a>
<a href="#33" id="33">One can describe the proposed algorithms as enlarging the search space by adding transfers of funds, thereby enabling the guarantee of convergence to stable solutions of higher efficiency.</a>
<a href="#34" id="34">A last important difference between all distributed local search algorithms and the INEA algorithm is that standard local search requires cooperation among all agents in order to find a solution, while the INEA algorithm uses steps of best-response which require no cooperation among the participating agents and thereby fits well into a framework of selfish (or competitive) agents that participate in a typical PGG game.</a>
</body>
</html>