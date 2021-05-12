<html>
<head>
<meta name="TextLength" content="SENT_NUM:40, WORD_NUM:847">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper discussed two search problems: bounded-cost search, and anytime search.</a>
<a href="#1" id="1">In a bounded-cost search, once a solution of cost lower than a given cost is found, the search can halt.</a>
<a href="#2" id="2">In an anytime search, the search continues, returning better and better solutions until the search is either halted by the user, or until an optimal solution has been found.</a>
<a href="#3" id="3">Both types of problems have important applications and this paper presents PTS and {a mathematical formula}APTS/ANA⁎ to solve them.</a>
<a href="#4" id="4">We showed that an efficient bounded-cost search algorithm can be easily converted to an efficient anytime search algorithm.</a>
<a href="#5" id="5">This is done by running the bounded-cost search algorithm iteratively, giving the bounded-cost search algorithm a lower cost bound in every iteration.</a>
<a href="#6" id="6">An attractive property of the resulting algorithm is that there is no need for parameter tuning, in contrast to most common anytime search algorithms.</a>
<a href="#7" id="7">The relation between bounded-cost and anytime search problems emphasizes the need for an efficient bounded-cost search algorithm.</a>
<a href="#8" id="8">In this paper we propose such an algorithm, called PTS.</a>
<a href="#9" id="9">PTS is a best–first search that expands nodes in order of their potential, which is the probability that a node will lead to a solution under the cost bound.</a>
<a href="#10" id="10">The relation between a given heuristic and the optimal cost is used to develop a cost function that can order the nodes in OPEN approximately according to their potential, without actually calculating it.</a>
<a href="#11" id="11">Both PTS and its corresponding anytime algorithm {a mathematical formula}APTS/ANA⁎ outperform competitive algorithms on a wide range of domains.</a>
<a href="#12" id="12">The heuristic {a mathematical formula}h(⋅) estimates the minimum cost of reaching a goal.</a>
<a href="#13" id="13">Recent work has shown that in domains with non-unit edge cost, {a mathematical formula}h(⋅) may not be correlated with the number of actions needed to reach a goal [39].</a>
<a href="#14" id="14">In such cases, prior work has shown that it is very beneficial to incorporate into the search algorithm an additional heuristic that estimates the minimum actions needed to reaching a goal [46].</a>
<a href="#15" id="15">Such a “distance” heuristic, commonly denoted as {a mathematical formula}d(⋅), together with an online learned inadmissible heuristic {a mathematical formula}hˆ(⋅), has been used in a new suboptimal search algorithm called EES [20], a new anytime search algorithm called AEES [63] and a new bounded-cost search algorithm called BEES [40].</a>
<a href="#16" id="16">BEES was shown to outperform PTS in domains with non-unit edge costs, including “Zenotravel” and “Elevators”, two domains from the International Planning Competition (IPC) that were solved with a domain independent planner.</a>
<a href="#17" id="17">Follow up work showed that in several other IPC benchmarks with non-unit edge cost, PTS can even be outperformed by a pure heuristic search [34].</a>
<a href="#18" id="18">Similar results appear when comparing AEES to {a mathematical formula}APTS/ANA⁎[63].</a>
<a href="#19" id="19">However, PTS is competitive with BEES in domains with unit edge costs.</a>
<a href="#20" id="20">See the results for the Tiles domain (which is the 15-puzzle) [40] and Tinybot domain [34], which were the only unit edge-cost domains they experimented with.</a>
<a href="#21" id="21">{sup:17} When PTS is as good as BEES, one would probably prefer using PTS since implementing it is much simpler: BEES requires maintaining at least two open lists as well as online learning an improved heuristic, while PTS is a simple best–first search algorithm with an easy to compute evaluation function.</a>
<a href="#22" id="22">Similar reasoning applies for comparing {a mathematical formula}APTS/ANA⁎ and AEES.</a>
<a href="#23" id="23">This emphasizes the need for PTS to consider {a mathematical formula}d(⋅) in domains with non-unit edge cost.</a>
<a href="#24" id="24">A first attempt to do so was in the BEEPS algorithm [63], which is equivalent to BEES except for using the PTS evaluation function when all nodes in OPEN are estimated to be above the bound.</a>
<a href="#25" id="25">Empirically, this combination of BEES and PTS performed almost exactly like BEES.</a>
<a href="#26" id="26">Thus, incorporating {a mathematical formula}d(⋅) into PTS in an effective manner is still an open challenge.</a>
<a href="#27" id="27">A possible direction for doing this is by considering explicitly the probabilistic relation between {a mathematical formula}h(n), {a mathematical formula}d(n) and {a mathematical formula}h⁎(n).</a>
<a href="#28" id="28">For example, one could apply machine learning techniques to learn this relation from past experience.</a>
<a href="#29" id="29">PTS aims at expanding the node with the highest probability to lead to a solution under the bound.</a>
<a href="#30" id="30">The task in a bounded-cost search is, however, to find such a solution as fast as possible.</a>
<a href="#31" id="31">Thus, we might also consider the expected effort of finding such a solution, and not just the probability that such a solution exists.</a>
<a href="#32" id="32">Estimating search effort may be done with search effort prediction formulas and algorithms [64], [65], [66].</a>
<a href="#33" id="33">Future work will investigate how to incorporate such estimates, in addition to the potential of a node.</a>
<a href="#34" id="34">For example, a node that is very close to a goal might be preferred to a node that has a slightly higher potential but is farther from a goal.</a>
<a href="#35" id="35">This paper combines results from two research groups who independently discovered {a mathematical formula}APTS/ANA⁎.</a>
<a href="#36" id="36">One group derived the anytime search algorithm APTS by studying bounded-cost search problems [7], [8].</a>
<a href="#37" id="37">The other research group derived {a mathematical formula}ANA⁎ motivated by a desire to avoid parameter tuning [9].</a>
<a href="#38" id="38">Both groups had papers under review simultaneously and subsequently published in 2011.</a>
<a href="#39" id="39">We thank Wheeler Ruml for pointing out this relationship.</a>
</body>
</html>