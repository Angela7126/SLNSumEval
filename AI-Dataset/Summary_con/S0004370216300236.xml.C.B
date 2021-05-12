<html>
<head>
<meta name="TextLength" content="SENT_NUM:32, WORD_NUM:853">
</head>
<body bgcolor="white">
<a href="#0" id="0">Much work in artificial intelligence is focused on innovative applications such as adaptive user interfaces, robotic elderly care, and automated trading agents.</a>
<a href="#1" id="1">A key technological challenge in these applications is to design an intelligent agent which can quickly learn to interact effectively with other agents whose behaviours are initially unknown.</a>
<a href="#2" id="2">Learning from scratch in such problems is not a viable solution, since time is a crucial factor and exploration via trial-and-error may not be feasible or desirable.</a>
<a href="#3" id="3">Instead, it is likely that any solution to this problem will have to draw heavily on prior experience and intuition, such as in the form of hypothesised behaviours.</a>
<a href="#4" id="4">Indeed, if we have a strong intuition regarding the behaviour of other agents, e.g. based on past experience or structural constraints of the task to be completed, then this intuition should be utilised in the interaction.</a>
<a href="#5" id="5">This is the motivation behind the type-based method studied in this work.</a>
<a href="#6" id="6">The idea in the type-based method is to hypothesise a set of possible behaviours, or types, which the other agents might have, and to plan our own actions with respect to those types which we believe are most likely, given the observed actions of the agents.</a>
<a href="#7" id="7">In this regard, we identified and addressed a spectrum of important questions, pertaining to properties of beliefs over types and the possibility of incorrect types.</a>
<a href="#8" id="8">Specifically, we formulated three alternative methods to incorporate observations into beliefs and studied the conditions under which the resulting beliefs will be correct or incorrect.</a>
<a href="#9" id="9">We then investigated the impact of prior beliefs on payoff maximisation and methods to automatically compute prior beliefs.</a>
<a href="#10" id="10">For the case in which our hypothesised types are incorrect, we analysed the conditions under which we are nevertheless able to complete our task, despite the incorrectness of types.</a>
<a href="#11" id="11">Finally, we described an automatic statistical analysis which can be used to ascertain the correctness of hypothesised types during the interaction.</a>
<a href="#12" id="12">In addition to the theoretical insights, the results presented in this article have a number of practical implications: First of all, our analysis in Section 4 shows that the standard posterior formulation, in which the likelihood is defined as a product of action probabilities, may not always be an appropriate choice.</a>
<a href="#13" id="13">Rather, one should also consider alternative formulations for posterior beliefs, such as the sum or correlated posteriors.</a>
<a href="#14" id="14">Furthermore, our empirical analysis in Section 5 shows that prior beliefs can be crucial to our ability to maximise payoffs in the long-term.</a>
<a href="#15" id="15">Indeed, we can often do better than a conservative uniform prior belief, by using automatic methods such as the ones used in this work.</a>
<a href="#16" id="16">Another important practical implication is that we can use efficient model checking methods to verify optimality of hypothesised types.</a>
<a href="#17" id="17">Specifically, in Section 6, we show a useful connection to probabilistic bisimulation checking.</a>
<a href="#18" id="18">Moreover, for the case in which a prior analysis based on bisimulation is not possible, we show that the correctness of types can still be contemplated during the interaction.</a>
<a href="#19" id="19">Our algorithm in Section 7 is simple to implement, highly efficient, and achieves high accuracy and scalability.</a>
<a href="#20" id="20">There are several potential directions for future work: Further formulations of posterior beliefs could be developed, and it would be interesting to know if the asymptotic correctness analysis in Section 4 could be complemented by useful finite-time error bounds.</a>
<a href="#21" id="21">Our empirical analysis of prior beliefs in Section 5 could be refined by a theoretical analysis, and an important question is if prior beliefs can be computed with useful error bounds (the LP-priors are a step in this direction).</a>
<a href="#22" id="22">Furthermore, the optimality analysis in Section 6 is focused on task completion and could be extended by an analysis focusing on payoff maximisation.</a>
<a href="#23" id="23">Finally, it is unclear if the concept of perfect scores in Section 7 is generally feasible or even necessary, and what impact score weights have on convergence and decision quality.</a>
<a href="#24" id="24">Two aspects which we did not address, yet which are crucial to a successful deployment of the type-based method, are the complexity of the planning step and the size of the hypothesised type spaces.</a>
<a href="#25" id="25">Regarding the former, it can be seen in Algorithm 1 (specifically (3)/(4)) that the time complexity of the planning is exponential in factors such as the number of agents, actions, and states, making it a very costly operation in complex systems.</a>
<a href="#26" id="26">A promising solution are stochastic sampling procedures such as those used in [4], [11].</a>
<a href="#27" id="27">Regarding the latter, the problem is that the number of types one may wish to hypothesise can grow dramatically with the size of the interaction problem (e.g. states, actions, agents).</a>
<a href="#28" id="28">This is problematic because the predictions of each type must be computed at each point in time, hence it is desirable to minimise the number of hypothesised types.</a>
<a href="#29" id="29">One way to do so is to develop methods which can produce small sets of reasonable types with good coverage of behaviours, in the spirit of works such as [32].</a>
<a href="#30" id="30">Another method would be to introduce learnable structure in types (i.e. parameters) such that each type covers a spectrum of behaviours.</a>
<a href="#31" id="31">However, this would require an ability to infer the parameters from the interaction history.</a>
</body>
</html>