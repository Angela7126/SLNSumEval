<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:645">
</head>
<body bgcolor="white">
<a href="#0" id="0">Our work focuses on norms and norm enforcement in multi-agent systems.</a>
<a href="#1" id="1">We proposed a formal methodology that allows analysing norms and norm enforcement from a mechanism design perspective, and a programming model for implementing them.</a>
<a href="#2" id="2">Using game theoretic tools we showed that the enforcement of norms can change the behaviour of rational agents using regimentation and sanctions.</a>
<a href="#3" id="3">It is also shown that our presented programming model is aligned with the abstract model such that our developed game theoretical tools can be applied to analyse norm-based environment programs.</a>
<a href="#4" id="4">Specifically, we proposed norm-based mechanism design as a formal methodology for analysing norm-based environment programs.</a>
<a href="#5" id="5">We showed how to abstract from a particular environment specification language and how to apply methods from mechanism design to verify whether the enforcement of a set of norms on a multi-agent environment agrees with the behaviour of rational agents that the system designer expects.</a>
<a href="#6" id="6">More precisely, we introduced normative behaviour functions for representing the “ideal” behaviour of multi-agent environments with respect to different sets of agents' preferences.</a>
<a href="#7" id="7">The latter enabled us to apply concepts from game theory to identify agents' rational behaviour.</a>
<a href="#8" id="8">These formal ideas can now be used to verify whether the enforcement of a set of norms is sufficient to motivate rational agents to act in such a way that their behaviour become aligned with that described by the normative behaviour function.</a>
<a href="#9" id="9">We defined a normative system in such a way that it can modify (soft) facts of the environment states.</a>
<a href="#10" id="10">As the language used for modelling agents' preferences and the facts in normative systems are based on the same set of propositional symbols, a norm-based mechanism can steer the behaviour of each agent in flexible ways.</a>
<a href="#11" id="11">This notion of mechanism is powerful.</a>
<a href="#12" id="12">A first refinement could be to identify a subset {a mathematical formula}ΠM⊆Π of soft facts and assume that a normative system can only modify state valuations with respect to this set.</a>
<a href="#13" id="13">Such a mechanism can be much weaker but also more natural.</a>
<a href="#14" id="14">Another direction for future research is to consider robustness against group deviation.</a>
<a href="#15" id="15">Our approach can be extended such that each agent a has its “own” set {a mathematical formula}Πa of propositional symbols which is used to specify its preference.</a>
<a href="#16" id="16">If we now want that some agents are not sensitive to norms and sanctions we simply define the set {a mathematical formula}ΠNF of facts that are used in a normative system such that {a mathematical formula}ΠNF∩Πa=∅.</a>
<a href="#17" id="17">Another alternative is to take on a more game theoretic point of view in the line with [1] and [23].</a>
<a href="#18" id="18">For example, one may consider partial strategies which assume that only subgroups of agents play rationally.</a>
<a href="#19" id="19">Then, the outcome is usually not a single path any more, but rather a set of paths.</a>
<a href="#20" id="20">This gives rise to a notion of {a mathematical formula}(S,A)-implementability.</a>
<a href="#21" id="21">We investigated the problem, given a CGS {a mathematical formula}M and a set of agents' preferences {a mathematical formula}Prefs, and a normative behaviour function f, whether there is a normative system {a mathematical formula}N which {a mathematical formula}NE-implements f over {a mathematical formula}M, q and {a mathematical formula}Prefs.</a>
<a href="#22" id="22">In future work it would be interesting to identify settings in which such normative systems can be constructed efficiently.</a>
<a href="#23" id="23">We also plan to extend our analysis to other implementability notions apart from Nash equilibria in more detail, e.g. dominant strategy equilibrium implementability.</a>
<a href="#24" id="24">Finally, yet another interesting direction for future research is to investigate core properties of classical mechanism design in our norm-based setting, including budget balanced and individual rational mechanisms.</a>
<a href="#25" id="25">We note that already the interpretation of these properties in our setting is interesting.</a>
<a href="#26" id="26">For example, in the case of individual rationality it is not clear what it means for an agent “not to take part” in the mechanism/in the multi-agent systems.</a>
<a href="#27" id="27">This may require a shift to an open MAS where agents can leave an join the system.</a>
</body>
</html>