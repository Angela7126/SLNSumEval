<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:552">
</head>
<body bgcolor="white">
<a href="#0" id="0">Our contribution is threefold.</a>
<a href="#1" id="1">First, we have proposed a new model for the selection of a collective sets of items.</a>
<a href="#2" id="2">This model appears to be very general, encompasses several known frameworks, and can be applied to various domains such as committee elections, group recommendation, and beyond.</a>
<a href="#3" id="3">Second, we have investigated the computational feasibility of the model, depending on the various assumptions that we can make about the agents' utilities and the choice of the OWA vector.</a>
<a href="#4" id="4">Table 1 in Section 4 gives a summary of our results.</a>
<a href="#5" id="5">We note that many of these results directly related to the OWA families that appear in the settings from Section 3 that were our motivating force.</a>
<a href="#6" id="6">Third, we have defined non-finicky utilities that model settings where agents are relatively “easy to please.” We believe that non-finicky utilities may find applications far beyond our framework.</a>
<a href="#7" id="7">Some of our results look negative, while some others (especially in the case of non-finicky utilities) are on the positive side.</a>
<a href="#8" id="8">However, the way the results should be interpreted depends on the application domain.</a>
<a href="#9" id="9">In political elections and other high-stake domains, it is appealing to view an approximation algorithm as a new, full-fledged voting rule, which may enjoy many desirable properties (on this point see the works of Caragiannis et al. [16], [17], Skowron et al. [55], and Elkind et al. [22]).</a>
<a href="#10" id="10">In particular, we have shown that the election system Sequential Proportional Approval Voting, SPAV, (which has been known long before the computational complexity theory was developed) is actually a greedy approximation algorithm for the Proportional Approval Voting (PAV) election rule, which is an interesting result per se.</a>
<a href="#11" id="11">(The reader may also wish to consult the paper of Aziz et al. [5] regarding the complexity of approval-based multiwinner rules.)</a>
<a href="#12" id="12">Yet, it is arguably not reasonable to use an approximation algorithm (even with a good performance guarantee) if it is viewed as nothing more than an approximation algorithm of another rule, and it is even less reasonable to use a heuristic search algorithm (when there is no good approximation algorithm); this implies that using this model for political elections is feasible when the number of candidates is small enough, but can become problematic beyond that (unless we define the approximation algorithm to be the new voting rule, as said above).</a>
<a href="#13" id="13">On the other hand, in low-stake application domains (which can include some committee elections, and of course group recommender systems), it may become perfectly reasonable, and in that case even NP-hardness and inapproximability results should not discourage us from using the model.</a>
<a href="#14" id="14">For these domains, our negative results only tell us that we may have to resort to heuristic search algorithms.</a>
<a href="#15" id="15">Developing such algorithm is one of the interesting directions for further research.</a>
<a href="#16" id="16">Our work leads to many other open problems.</a>
<a href="#17" id="17">In particular, one might want to strengthen our approximation algorithms, provide algorithms for more general cases, provide more inapproximability results.</a>
<a href="#18" id="18">Among these problems, a particularly interesting one regards the approximability of OWA-Winner for the arithmetic progression family of OWAs.</a>
<a href="#19" id="19">For this case, our set of results is very limited.</a>
<a href="#20" id="20">In particular, can one provide a PTAS for arithmetic-progression OWAs under non-finicky (in particular Borda-based) utilities?</a>
<a href="#21" id="21">Can one do so for {a mathematical formula}K2-best OWAs/{a mathematical formula}K2-median OWAs?</a>
<a href="#22" id="22">Can one do so for the harmonic OWA, used in Proportional Approval Voting?</a>
</body>
</html>