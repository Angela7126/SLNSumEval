<html>
<head>
<meta name="TextLength" content="SENT_NUM:35, WORD_NUM:754">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have studied approximability of finding winners under the Monroe and Chamberlin–Courant multiwinner voting rules.</a>
<a href="#1" id="1">We have shown that if we try to optimize agents' dissatisfaction, then our problems are hard to approximate up to any constant factor.</a>
<a href="#2" id="2">The same holds for the case where we focus on the satisfaction of the least satisfied agent.</a>
<a href="#3" id="3">However, for the case of optimizing the sum of agents' satisfactions, we found good approximation algorithms.</a>
<a href="#4" id="4">In particular, for the Monroe system we suggest a randomized algorithm that for the Borda score achieves an approximation ratio arbitrarily close to 0.715 (and much better ratios in many real-life settings), and ({a mathematical formula}1−1e)-approximation algorithm for arbitrary positional scoring function.</a>
<a href="#5" id="5">For the Chamberlin–Courant system, we have shown a polynomial-time approximation scheme (PTAS).</a>
<a href="#6" id="6">In Table 6 we present the summary of our (in)approximability results.</a>
<a href="#7" id="7">In Table 7 we present specific results regarding our approximation algorithms for the utilitarian satisfaction-based framework.</a>
<a href="#8" id="8">In particular, the table clearly shows that for the case of Monroe, Algorithms B and C are not much slower than Algorithm A but offer a chance of improved performance.</a>
<a href="#9" id="9">Algorithm GM is intuitively even more appealing, but achieves this at the cost of high time complexity.</a>
<a href="#10" id="10">For the case of Chamberlin–Courant rule, theoretical results suggest using Algorithm P (however, see below).</a>
<a href="#11" id="11">We have provided experimental evaluation of the algorithms for computing the winner sets both for the Monroe and Chamberlin–Courant rules.</a>
<a href="#12" id="12">While finding solutions for these rules is computationally hard in the worst case, it turned out that in practice we can obtain very high quality solutions using very simple approximation algorithms.</a>
<a href="#13" id="13">Indeed, both for the Monroe and Chamberlin–Courant rules we recommend using Algorithm C (or Algorithm A on very large Monroe elections).</a>
<a href="#14" id="14">Our experimental evaluation confirms that the algorithms work very well in the case of truncated ballots.</a>
<a href="#15" id="15">We believe that our results mean that (approximations of) the Monroe and Chamberlin–Courant rules can be used in practice.</a>
<a href="#16" id="16">Our work leads to a number of further research directions.</a>
<a href="#17" id="17">First, it would be interesting to find a better upper bound on the quality of solutions for the (satisfaction-based) Monroe and Chamberlin–Courant systems (with Borda PSF) than the simple {a mathematical formula}n(m−1) bound that we use (where n is the number of voters and m is the number of candidates).</a>
<a href="#18" id="18">We use a different approach in our randomized algorithm, but it would be much more interesting to find a deterministic algorithm that beats the approximation ratios of our algorithms.</a>
<a href="#19" id="19">One of the ways of seeking such a bound would be to consider the Monroe rule with “exponential” Borda PSF, that is, with PSF of the form, e.g., {a mathematical formula}(2m−1,2m−2,…,1).</a>
<a href="#20" id="20">For such PSF our approach in the proof of Lemma 4 would not give satisfactory results and so one would be forced to seek different attacks.</a>
<a href="#21" id="21">In a similar vein, it would be interesting to find out if there is a PTAS for the Monroe system.</a>
<a href="#22" id="22">In our work, we have focused on PSFs that are strictly increasing/decreasing.</a>
<a href="#23" id="23">It would also be interesting to study PSFs which increase/decrease but not strictly, that is, PSFs which allow some equalities.</a>
<a href="#24" id="24">We have started to work in this direction by considering agents with dichotomous preferences.</a>
<a href="#25" id="25">Formally, we consider t-approval PSF's {a mathematical formula}αt, which (in the satisfaction-based variant) are defined as follows: {a mathematical formula}αt(i)=1 if {a mathematical formula}i≤t and otherwise {a mathematical formula}αt(i)=0.</a>
<a href="#26" id="26">Results for this case for the Chamberlin–Courant rule are presented in the paper of Skowron and Faliszewski [57].</a>
<a href="#27" id="27">(As a side comment, we mention that there are also other interesting multiwinner voting rules that focus on dichotomous preferences; we point the reader to the overview of Kilgour [29] and to algorithmic studies of, for example, LeGrand et al. [31], Caragiannis et al. [12], and Aziz et al.</a>
<a href="#28" id="28">[3].)</a>
<a href="#29" id="29">On a more practical side, it would be interesting to develop our study of truncated ballots.</a>
<a href="#30" id="30">Our results show that we can obtain very high approximation ratios even when voters rank only relatively few of their top candidates.</a>
<a href="#31" id="31">For example, to achieve 90% approximation ratio for the satisfaction-based Monroe system in Polish parliamentary election ({a mathematical formula}K=460, {a mathematical formula}m=6000), each voter should rank about {a mathematical formula}8.7% of her most-preferred candidates.</a>
<a href="#32" id="32">However, this is still over 500 candidates.</a>
<a href="#33" id="33">It is unrealistic to expect that the voters would be willing to rank this many candidates.</a>
<a href="#34" id="34">Thus, the obvious question is how should one organize Monroe-based elections in practice, to balance the amount of effort required from the voters and the quality of the results?</a>
</body>
</html>