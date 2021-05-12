<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:530">
</head>
<body bgcolor="white">
<a href="#0" id="0">With the deployment of systems based on MAS-architectures there has been a growing interest in their verification.</a>
<a href="#1" id="1">Considerable progress has been made in model checking MAS against specifications based on temporal, epistemic, deontic and strategic properties; open-source implementations based on efficient symbolic approaches have been put forward and compared.</a>
<a href="#2" id="2">While this work has proven to be valuable, it is limited to scenarios where the number of components is known at design time.</a>
<a href="#3" id="3">This is not a realistic assumption in certain MAS where the number of components cannot be known before deployment.</a>
<a href="#4" id="4">A typical case is robotic swarms, whereby the properties of the swarm need to hold irrespective of how many robots are present in the system and should hold even if some of the robots develop a fault and leave the system.</a>
<a href="#5" id="5">In this paper we put forward a methodology to solve the parameterised model checking problem for MAS in a number of noteworthy classes of PIIS.</a>
<a href="#6" id="6">As we showed, this enabled us to give a methodology for the cutoff identification of a given parametric system.</a>
<a href="#7" id="7">When a cutoff can be determined, the parameterised model checking problem can be solved via standard model checking by verifying all system instances up to the cutoff.</a>
<a href="#8" id="8">We showed the procedure to be sound.</a>
<a href="#9" id="9">Table 2 summarises the theoretical results obtained.</a>
<a href="#10" id="10">Since the PMCP is in general undecidable, no complete results can be established in general.</a>
<a href="#11" id="11">In Section 5 we presented an incomplete technique for the {a mathematical formula}SMR class; in Section 6 we analysed an incomplete technique for the {a mathematical formula}SGS class; in Section 7 we studied a complete technique for the {a mathematical formula}SFE class.</a>
<a href="#12" id="12">Incompleteness for the {a mathematical formula}SMR and the {a mathematical formula}SGS classes follows in the absence of an agent-environment simulation between the templates since in this case the techniques cannot assess the correctness of a given specification.</a>
<a href="#13" id="13">In contrast, we can always assess the correctness of a specification on {a mathematical formula}SFE systems.</a>
<a href="#14" id="14">This level of confidence, which follows from the decidability result of Corollary 7.6, comes with considerable limitations on the range of systems that the technique can be applied to.</a>
<a href="#15" id="15">For instance, the result cannot be applied to any scenario where the agents evolve in any other way other than lock-step evolution.</a>
<a href="#16" id="16">Other systems may be modelled as {a mathematical formula}SMR or {a mathematical formula}SGS systems.</a>
<a href="#17" id="17">{a mathematical formula}SMR is suitable for scenarios requiring refined interactions between agents of different roles, whereas {a mathematical formula}SGS is suitable for simulating synchronous semantics.</a>
<a href="#18" id="18">The technique for the former class generally returns cutoffs that are larger than those for the latter class.</a>
<a href="#19" id="19">Both techniques are limited by the requirement of an agent-environment simulation between the agent and environment templates.</a>
<a href="#20" id="20">This makes it difficult to model certain applications of interest; including cache coherence protocols [67].</a>
<a href="#21" id="21">In future work we plan to explore other methodologies, including counter-abstraction [40] for obtaining cutoffs for even wider classes of systems.</a>
<a href="#22" id="22">Furthermore, we believe the technique here put forward can serve as an ideal stepping stone to verify open MAS where the agents can dynamically join or leave the system at runtime.</a>
<a href="#23" id="23">We are not aware of any formal methodologies addressing this aspect.</a>
</body>
</html>