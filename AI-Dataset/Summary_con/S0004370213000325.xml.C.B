<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:816">
</head>
<body bgcolor="white">
<a href="#0" id="0">As illustrated throughout the paper, increasing threshold search is highly effective in settings in which the cost of finding the agent associated with either the maximum or minimum value of any specific property needs to be minimized.</a>
<a href="#1" id="1">This problem often arises in MAS, mostly due to their distributed nature.</a>
<a href="#2" id="2">Despite its wide applicability, this method has not received adequate attention in the literature.</a>
<a href="#3" id="3">Most research of techniques utilizing expanding search extents, as discussed in Sections 1 Introduction, 4 Comparative illustration, 7 Related work, has focused on models in which the costs associated with the search are correlated with the extent of search (rather than with the number of agents applicable to the extent used, as in our case).</a>
<a href="#4" id="4">Consequently, the strategies most studied in those domains are very different from the optimal strategy to our problem, both in structure and quality of the solution obtained.</a>
<a href="#5" id="5">The paper introduces a solution to the problem in both the discrete and continuous domains.</a>
<a href="#6" id="6">While the first uses a standard dynamic programming method, the analysis of the latter domain is quite non-standard: By correlating the reservation values to the respective probabilities in the proof of Theorem 1, the essence of the optimal solution in the form of a single reservation probability is revealed, enabling a solution to the problem.</a>
<a href="#7" id="7">Furthermore, both the optimal reservation probability, from which the appropriate thresholds can be calculated, and the corresponding expected cost of search are distribution independent.</a>
<a href="#8" id="8">This means that the solution to one problem instance can be used to derive the optimal search sequence for any other instance that only differs in its distribution of values by merely applying a simple transformation.</a>
<a href="#9" id="9">It also enables making distribution-independent observations given the remaining parameters, such as the expected cost of the optimal strategy and expected number of rounds.</a>
<a href="#10" id="10">The same analysis methodology is replicated for the important and often necessary case of searching for multiple agents.</a>
<a href="#11" id="11">Here, the single reservation probability property is preserved to the extent of any number of agents already found, and all the remaining advantages of the method (e.g., distribution-independence) hold.</a>
<a href="#12" id="12">As evident in Section 6, increasing threshold search can also be useful in economic search settings where the searcher is not constrained to finding the best-valued agent.</a>
<a href="#13" id="13">This result is interesting, since increasing threshold search is by definition constrained by the need to find the best-valued agent.</a>
<a href="#14" id="14">In economic search settings, increasing threshold search can either be used as an alternative to traditional economic search methods (e.g., sequential search), possibly resulting in lower expected overall cost, or to directly augment those methods, making use of the threshold publication aspect as part of or alongside the regular search routine.</a>
<a href="#15" id="15">This has many implications in the evolving research area known also as search theory[30].</a>
<a href="#16" id="16">The paper defines and demonstrates the effectiveness of two such extensions to economic search, though many more can be considered.</a>
<a href="#17" id="17">The determination of which amongst these search strategies will result in the lowest cost is setting dependent.</a>
<a href="#18" id="18">Yet, given the probability distribution function, the search cost function, and the number of agents available, a searcher facing an economic search problem can follow the analysis given in this paper to calculate the expected cost of each method and choose accordingly.</a>
<a href="#19" id="19">Future work can consider more general assumptions regarding costs and cooperation of the different players.</a>
<a href="#20" id="20">This may require modification of the analysis.</a>
<a href="#21" id="21">In some cases, it may also impose external modeling challenges and even require the integration of buyersʼ strategic behavior.</a>
<a href="#22" id="22">For example, the values of the agents can change in time.</a>
<a href="#23" id="23">This requires external modeling of the way the distributions that characterize the agentsʼ values change over time.</a>
<a href="#24" id="24">We note that in such a case, one may find it more beneficial to use a search technique that is based on increasing and decreasing thresholds.</a>
<a href="#25" id="25">Such a strategy may be useful in cases in which agent values may actually decrease with time.</a>
<a href="#26" id="26">Another example is the possibility that agents do not know their true value and will not readily calculate their value.</a>
<a href="#27" id="27">(The current model assumes that agents know their values or are willing to calculate them—taxi drivers will always know their locations, sensors will know their readings).</a>
<a href="#28" id="28">For example, if the threshold on a call for bids is very low, some contractors may decide that it is not worth preparing a bid and hence will not know their actual value.</a>
<a href="#29" id="29">This requires modeling of the a priori value distribution of different agents, based on which their decision is made.</a>
<a href="#30" id="30">More important, the strategic behavior of the agents, in terms of willingness to prepare a bid based on the threshold they receive, should be modeled and taken into consideration.</a>
<a href="#31" id="31">Another possible extension of this work includes the investigation of competition and cooperation models for two or more searchers when operating in settings where search is costly and one or more of them is capable of using increasing threshold search.</a>
</body>
</html>