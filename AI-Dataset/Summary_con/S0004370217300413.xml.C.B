<html>
<head>
<meta name="TextLength" content="SENT_NUM:54, WORD_NUM:1370">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we have studied a novel game model that admits a natural characterisation in a simple, yet computationally powerful, syntactic fragment of the Reactive Modules language [2].</a>
<a href="#1" id="1">Also, the complexity of reasoning about equilibria in this model as well as of checking and synthesising temporal properties of multi-agent systems specified in such a language was investigated, both, in the linear-time and branching-time frameworks [20].</a>
<a href="#2" id="2">Several research groups are working on problems related to equilibrium checking: Fisman et al. [23] study the problem of synthesising systems so that certain desirable properties hold in equilibrium; in addition, extensive overviews of decision problems related to equilibrium checking are given in [13], [8], for a range of concurrent game models.</a>
<a href="#3" id="3">In our own work, we have investigated many issues surrounding rational verification, particularly using Boolean games[37].</a>
<a href="#4" id="4">Boolean games are essentially “one-shot” versions of iterated Boolean games, as described above, where play consists of a single round, and agent goals {a mathematical formula}γi are specified as propositional formulae.</a>
<a href="#5" id="5">A question that we have investigated at length is possible mechanisms for managing games.</a>
<a href="#6" id="6">This might be necessary, for example, if the game contains socially undesirable equilibria [73], or where a game possesses no equilibrium, and we wish to introduce one (which we call stabilisation).</a>
<a href="#7" id="7">One obvious mechanism for manipulating games is the use of taxation schemes, which provide incentives for players to avoid undesirable equilibria, or to prefer desirable equilibria [74].</a>
<a href="#8" id="8">(Related issues have recently been studied in the context of concurrent games [1].)</a>
<a href="#9" id="9">Another possibility is to try to influence players by changing their beliefs through communication.</a>
<a href="#10" id="10">For example, [26] considered a Boolean games setting where players make their choices based on beliefs about some variables in the environment, and a central authority is able to reveal certain information in order to modify these beliefs.</a>
<a href="#11" id="11">Another issue we have investigated is the extent to which we can develop a language that supports reasoning about strategies directly in the object language.</a>
<a href="#12" id="12">Strategy Logic (SL) is a variation of temporal logic, closely related to Alternating-time temporal logic [3], which includes names for strategies in the object language [14], and using SL, it is possible to reason about Nash equilibria.</a>
<a href="#13" id="13">However, SL is in general undecidable, which raises the question of whether weaker languages might be used.</a>
<a href="#14" id="14">For instance, in [30] a temporal logic containing a quantifier {a mathematical formula}[NE]φ, meaning “φ holds on all Nash equilibrium computations”, is proposed.</a>
<a href="#15" id="15">Also, in [31] it is shown that the existence of Nash equilibria can be represented, up to bisimilarity, in logic languages that are even weaker than full SL.</a>
<a href="#16" id="16">Other researchers have investigated similar concerns [11].</a>
<a href="#17" id="17">Another interesting question is the extent to which the model of interaction used in a particular setting affects the possible equilibria that may result.</a>
<a href="#18" id="18">In [35], we investigated Nash equilibria in games based on event structures [71], and were able to characterise conditions required for the existence of equilibria.</a>
<a href="#19" id="19">Another research direction is the extent to which we can go beyond the representation of preferences as simple binary formulae; one possible approach, investigated in [48], is to represent player's goals as formulae of Łukasiewicz logic, which permits a much richer class of preferences to be directly represented.</a>
<a href="#20" id="20">Many issues are being currently studied, or remain for future work.</a>
<a href="#21" id="21">Mixed (stochastic) strategies is an obvious major topic of interest, as it is the possibility of imperfect information [34], and of course solution concepts beyond Nash equilibria, such as subgame perfect equilibrium.</a>
<a href="#22" id="22">Our Eagle tool is a prototype [65], limited in its scope, and not optimised: extensions supporting LTL, incomplete information, etc., are all highly desirable.</a>
<a href="#23" id="23">Our main complexity results are summarised in Table 2 and some of them are rather surprising.</a>
<a href="#24" id="24">For instance, we showed that with respect to goals given by LTL formulae and deterministic strategies, it is equally hard to verify equilibrium properties (i.e., those studied in E-Nash and A-Nash) regardless of whether the arenas modelling the systems of interest are either explicitly specified in srml or implicitly given – as in iterated Boolean games (iBGs [29]), where the induced Kripke structures are exponential in the number of variables.</a>
<a href="#25" id="25">Recall that, in general, the srml model of any iBG is also of exponential size.</a>
<a href="#26" id="26">Less surprising is the fact that the complexity of all the key questions we studied is 2EXPTIME-hard.</a>
<a href="#27" id="27">This is high computational complexity, which presents a real challenge for practical implementations.</a>
<a href="#28" id="28">Our results show that, as for (LTL) synthesis problems, this is the best that one can do.</a>
<a href="#29" id="29">As a consequence, if practical implementations are desired, one would have to look for suitable simplifications to the main setting: for instance, games with memoryless strategies, or games with goals in simpler LTL syntactic fragments.</a>
<a href="#30" id="30">In the former case, one cannot do better than EXPTIME for general LTL goals; in the latter case, the complexity may be reduced even to PSPACE for safety goals.</a>
<a href="#31" id="31">Either way, any practical implementation will probably have to deal with an associated synthesis problem from a logical specification, which most likely will be of high complexity.</a>
<a href="#32" id="32">In fact, even though we deal with succinct system specifications, which are closer to the ones used in realistic scenarios, as clearly shown in [5], high complexities would be obtained even if explicit system representations are used, simply due to the fact that players goals are expressed using the full language of LTL.</a>
<a href="#33" id="33">An alternative is studied in [28], where Nash equilibria is studied with respect to fragments of LTL within the iBG framework.</a>
<a href="#34" id="34">Moreover, from an expressivity standpoint, RMGs are more general than iBGs.</a>
<a href="#35" id="35">Indeed, the class of induced Kripke structures induced by RMGs is strictly larger than the class of semantic structures associated with iBGs.</a>
<a href="#36" id="36">A simple example is the distributed algorithm in Section 5.3, which cannot be specified as an iBG, but has an srml representation.</a>
<a href="#37" id="37">Then, with RMGs, we have more expressive power with the same complexity.</a>
<a href="#38" id="38">A somewhat different question is the extent to which the techniques and solution concepts developed here can be used in practice, for example when designing electronic commerce systems.</a>
<a href="#39" id="39">The issue here touches on a substantial debate within game theory itself, concerning the applicability of game-theoretic concepts.</a>
<a href="#40" id="40">If we view game theory as being a descriptive theory, which aims to predict what people will actually do in strategic settings, then game-theoretic solution concepts seem to be of limited value in many cases (see, e.g., [7] for extensive discussion).</a>
<a href="#41" id="41">There are several points to make here.</a>
<a href="#42" id="42">First, one can argue that while people fail to be rational in the sense that game theory defines, when we design computer programs to make decisions, we can design them to act rationally.</a>
<a href="#43" id="43">Second, we suggest that Nash equilibrium analysis is a starting point for understanding the rational dynamics of a system, rather than an end point.</a>
<a href="#44" id="44">The Nash equilibrium computations of an RMG are a subset of the overall possible computations of the system at hand, and assuming rational action, then the actual trajectory of the system will lie with the Nash equilibrium set.</a>
<a href="#45" id="45">But the analysis of the present paper stops at this point, once we have identified the rational computations.</a>
<a href="#46" id="46">Finally, if we aim to use our techniques to understand the rational dynamics of human system, then work is needed on developing computational models of human strategic decision making.</a>
<a href="#47" id="47">This would take us into the territory of behavioural game theory, and is somewhat beyond the scope of the present paper.</a>
<a href="#48" id="48">In future work, we plan to use our specification language and games framework to implement a model checker of equilibrium properties in game-like concurrent and multi-agent systems.</a>
<a href="#49" id="49">It would be also very interesting to investigate how the complexity results we have obtained so far are affected by the adoption of other temporal logic languages and solution concepts.</a>
<a href="#50" id="50">Studying the relationship to Markov games and probabilistic model checking would also be interesting, perhaps using logics such as PCTL [43].</a>
<a href="#51" id="51">It would also be interesting to study situations in which the actions of players have unreliable effects (i.e., non-deterministic actions).</a>
<a href="#52" id="52">Finally, much work remains to be done in settings where one considers imperfect information [34] or more general payoff sets and preference relations.</a>
<a href="#53" id="53">All these issues should certainly be also investigated further.</a>
</body>
</html>