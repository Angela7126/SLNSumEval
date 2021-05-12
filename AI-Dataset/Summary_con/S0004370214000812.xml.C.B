<html>
<head>
<meta name="TextLength" content="SENT_NUM:30, WORD_NUM:679">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we studied influence and stable behavior from a new game-theoretic perspective.</a>
<a href="#1" id="1">To that end, we introduced a rich class of games, named network influence games, to capture the core strategic component of complex interactions in a network.</a>
<a href="#2" id="2">We characterized the computational complexity of computing and counting PSNE in LIGs.</a>
<a href="#3" id="3">We proposed practical, effective heuristics to compute PSNE in such games and demonstrated their effectiveness empirically.</a>
<a href="#4" id="4">Besides predicting stable behavior, we gave a framework for computing the most influential nodes and its variants (e.g., identifying a small coalition of senators that can prevent filibuster).</a>
<a href="#5" id="5">We also gave a provable approximation algorithm for the most-influential-nodes problem.</a>
<a href="#6" id="6">Although our models are inspired by decades of research by sociologists, at the heart of our whole approach is abstracting the complex dynamics of interactions using the solution concept of PSNE.</a>
<a href="#7" id="7">This allowed us to deal with richer problem instances (e.g., the ones with negative influence factors) as well as to tread into new problem settings beyond identifying the most influential nodes.</a>
<a href="#8" id="8">We conclude this paper by outlining several interesting lines of future work.</a>
<a href="#9" id="9">First, we leave several computational problems open.</a>
<a href="#10" id="10">We showed that counting the number of PSNE even in a star-type LIG is #P-complete, but does there exist an FPRAS for the counting problem?</a>
<a href="#11" id="11">The computational complexity of indiscriminant LIGs, which we conjecture to be PLS-complete, is unresolved.</a>
<a href="#12" id="12">Also, computing mixed-strategy Nash equilibria of LIGs, even for special types such as trees, remains an open question.</a>
<a href="#13" id="13">Second, we can apply our models to the general setting of “strategic interventions,” where we study the effects of changes in node thresholds, connectivity, or influence factors, usually without the possibility of having corresponding behavioral data.</a>
<a href="#14" id="14">The following is an illustrative example of it in the context of the 111th U.S.</a>
<a href="#15" id="15">Congress.</a>
<a href="#16" id="16">After the death of Ted Kennedy, who was a democratic senator from the state of Massachusetts, a republican named Scott Brown was elected in his place.</a>
<a href="#17" id="17">Not only was it Senator Brown's first appointment in the Senate, he was also the first republican from Massachusetts to be elected to Senate for a long time.</a>
<a href="#18" id="18">With no behavioral data available at that point of time, we can perform interventions using our model under various assumptions of thresholds, connectivity, and influence factors regarding Senator Brown, with the general goal of predicting stable outcomes and investigating the effects of the above interventions in various settings, such as filibuster scenarios or the setting of the most influential senators.</a>
<a href="#19" id="19">Another example of intervention, in the context of the Framingham heart study alluded in Section 1, is the following.</a>
<a href="#20" id="20">Suppose that we would like to implement a policy of targeted interventions in order to reduce smoking by some margin.</a>
<a href="#21" id="21">Using our model, we can modify the thresholds of the selected targets and predict how it could affect the overall level of smoking.</a>
<a href="#22" id="22">Besides interventions, we can also use our model to analyze past happenings, such as the role of the bipartisan “gang-of-six” senators in leading the members of the two major parties to an agreement during the U.S.</a>
<a href="#23" id="23">debt ceiling crisis.</a>
<a href="#24" id="24">{sup:17} We can use our model to find how influential the gang-of-six senators were as a group.</a>
<a href="#25" id="25">One approach to this problem would be to first find the set of stable outcomes consistent with the gang-of-six senators voting “yes” and then to analyze what fraction of these stable outcomes has 60 or more “yes” votes (signifying the passing of the corresponding bill without any possibility of a filibuster).</a>
<a href="#26" id="26">Our model of influence game can be considered as a step in the direction of modeling competitive contagion in strategic settings (see, for example, Budak et al. [12], Goyal and Kearns [30]).</a>
<a href="#27" id="27">Here, one of the main challenges would be to formulate the competitive aspects of multiple “campaigns” without having to go through the usual network dynamics.</a>
<a href="#28" id="28">In this general setting, we can ask questions such as, who are the most influential individuals with respect to achieving a certain objective that favors one “campaign” over the other?</a>
<a href="#29" id="29">Such questions, and many others, shape the long-term goal of this research.</a>
</body>
</html>