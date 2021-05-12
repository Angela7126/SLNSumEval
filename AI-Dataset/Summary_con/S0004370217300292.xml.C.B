<html>
<head>
<meta name="TextLength" content="SENT_NUM:34, WORD_NUM:741">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we have posed and answered a long list of questions about price competition games among single-product vendors.</a>
<a href="#1" id="1">Of course, our work reveals a lot more open problems.</a>
<a href="#2" id="2">We mention a few here.</a>
<a href="#3" id="3">First, we remark that identifying broad classes of games that always admit equilibria is very interesting.</a>
<a href="#4" id="4">It is not hard to see that games with single-minded buyers, i.e., where each buyer only wishes to be assigned to a single vendor, always have pure equilibria, as essentially each vendor sets the price that maximizes its utility and the buyers either abstain or choose their preferred vendor; note that, in this setting, there is no price competition among vendors.</a>
<a href="#5" id="5">Another class of games that always admits pure equilibria is the following extension of the case in Lemma 3: let there be n buyer types, where {a mathematical formula}vij=v1j+ci, for {a mathematical formula}2≤i≤n where {a mathematical formula}ci≥0 is a constant.</a>
<a href="#6" id="6">Note that, in this setting, all buyer types agree on the same ranking of vendors and that, for fixed i, {a mathematical formula}vij−vij′ is constant for any pair of vendors {a mathematical formula}j,j′; we can adapt the proof of Lemma 3 to prove this claim.</a>
<a href="#7" id="7">However, one can show that the case, where all buyer types agree on the same ranking of vendors but {a mathematical formula}vij−vij′ may vary for different pairs j, {a mathematical formula}j′, does not always admit equilibria.</a>
<a href="#8" id="8">To see that, consider a game with two vendors of production cost 0 and two buyer types of volume 1.</a>
<a href="#9" id="9">Let {a mathematical formula}v11=6, {a mathematical formula}v12=4, {a mathematical formula}v21=5 and {a mathematical formula}v22=0, where again {a mathematical formula}vij denotes the valuation of a buyer of type i for vendor j; it is not hard to show that this game does not admit equilibria.</a>
<a href="#10" id="10">From the algorithmic point of view, observe that we have made no particular attempt to optimize the running time of our algorithms.</a>
<a href="#11" id="11">We believe that there is much room for improvement on the running time of CandidatePrice and Enumerate.</a>
<a href="#12" id="12">In particular, it would be interesting to come up with FPT algorithms (see Downey and Fellows [11]) for PriceCompetition with respect to different parameters.</a>
<a href="#13" id="13">Second, in spite of our inapproximability result (Theorem 12), we believe that it is important to design polynomial-time approximation algorithms for MinSubsidies.</a>
<a href="#14" id="14">For example, is there a logarithmic approximation algorithm?</a>
<a href="#15" id="15">What about additive approximations using an amount of subsidies that exceeds the minimum by at most {a mathematical formula}ρ⋅SW⁎ for some small {a mathematical formula}ρ>0?</a>
<a href="#16" id="16">Another set of open problems comes from introducing constraints to price competition games such as supply limitations.</a>
<a href="#17" id="17">For example, consider additional input parameters that indicate the maximum volume of buyers each vendor can support.</a>
<a href="#18" id="18">We believe that this subtle difference in the definition makes the setting even richer from the computational point of view.</a>
<a href="#19" id="19">Another question concerns mixed equilibria.</a>
<a href="#20" id="20">Do such equilibria always exist?</a>
<a href="#21" id="21">Observe that the strategy spaces of vendors have infinite size in this case.</a>
<a href="#22" id="22">Can they be computed efficiently?</a>
<a href="#23" id="23">What is their price of anarchy?</a>
<a href="#24" id="24">What about generalizations of our model that include uncertainty for buyer valuations?</a>
<a href="#25" id="25">It is our firm belief that these questions deserve investigation.</a>
<a href="#26" id="26">An alternative model for using subsidies is to reimburse the vendors so that a given buyers-to-vendors assignment x results in an equilibrium with the vendors figuring out the corresponding price vector p on their own.</a>
<a href="#27" id="27">Instead, our model reimburses the vendors so that a given pair {a mathematical formula}(x,p) is an equilibrium.</a>
<a href="#28" id="28">Apart from the requirement that the vendors compute collectively an appropriate price vector, we remark that there are cases where this variant leads to higher subsidies; the price competition game in Example 3 is such a case.</a>
<a href="#29" id="29">Finally, it makes sense to consider vendors with concave production costs (that model economies of scale), as opposed to fixed production costs per unit that we consider in the paper.</a>
<a href="#30" id="30">Clearly, all our negative results, such as the existence of price competition games with no pure Nash equilibria and the NP-completeness results, still hold but we do not know if the positive results carry over to this more general setting.</a>
<a href="#31" id="31">We remark that this modification also affects the consequences after a price change.</a>
<a href="#32" id="32">For example, a vendor may decrease its price in order to attract more buyers and, after these buyers select that vendor, the vendor can further reduce its price as now its production cost per item has decreased.</a>
<a href="#33" id="33">These model variants deserve investigation as well.</a>
</body>
</html>