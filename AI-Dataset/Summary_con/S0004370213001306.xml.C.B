<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:729">
</head>
<body bgcolor="white">
<a href="#0" id="0">We contributed a representation of team performance that goes beyond the sum of single-agent capabilities; we formally introduced the weighted synergy graph model, where the inherent differences in the agentsʼ capabilities are modeled with Normally-distributed variables, and the task-based relationship is modeled as a connected weighted graph.</a>
<a href="#1" id="1">Weighted synergy graphs are applicable to many multi-agent domains, and we presented an example of a rescue task, and showed how different agents and their task-based relationships are modeled effectively.</a>
<a href="#2" id="2">To apply weighted synergy graphs on problem domains, we contributed an algorithm that learns a weighted synergy graph from observations, and two team formation algorithms that use a learned weighted synergy graph to form an effective multi-agent team.</a>
<a href="#3" id="3">These algorithms enable the weighted synergy graph model to be applied to a variety of problems, since the only input are the training observations.</a>
<a href="#4" id="4">The learning algorithm learns the structure of the weighted graph by iteratively improving the graph structure, and learns the agentsʼ capabilities by solving a system of equations derived from the observations and the graph structure.</a>
<a href="#5" id="5">Our first team formation algorithm uses branch-and-bound to find the optimal team, and our second team formation algorithm explores possible teams and approximates the optimal team.</a>
<a href="#6" id="6">Although the approximation algorithm does not have formal guarantees on the formed team, we found that the team that is formed is close to optimal while only exploring a small subset of the space.</a>
<a href="#7" id="7">The optimal team formation algorithm searches a large amount of space in order to guarantee optimality, so we believe the approximation algorithm is more applicable due to scalability issues with the optimal team formation algorithm in real problems.</a>
<a href="#8" id="8">We extensively evaluated our learning algorithm.</a>
<a href="#9" id="9">First, we created random weighted synergy graphs with representative graph structure types, and demonstrated that our learning algorithm learned weighted synergy graphs with structures similar to the types.</a>
<a href="#10" id="10">Second, we generated random weighted synergy graphs that were hidden from the learning algorithm, and showed that the log-likelihood of the learned weighted synergy graph closely matches that of the hidden ones.</a>
<a href="#11" id="11">Thus, the agent capabilities and graph structures were effectively learned using our learning algorithm.</a>
<a href="#12" id="12">Although we evaluated the learning algorithm with data derived from weighted synergy graphs, the learning algorithm is applicable to data from any source and will learn the closest weighted synergy graph that matches the data.</a>
<a href="#13" id="13">The learning algorithm does not have guaranteed bounds on the learned result but from our experiments, we believe that a small number of iterations of simulated annealing (compared to the entire space of weighted graphs) is sufficient to learn a model that matches the observed data well.</a>
<a href="#14" id="14">We applied the weighted synergy graph model to a problem domain: urban search-and-rescue.</a>
<a href="#15" id="15">Using the RoboCup Rescue simulator, we made minor modifications to six algorithms written by RoboCup participants, such that combinations of these algorithms can be run in parallel to perform the RoboCup Rescue task.</a>
<a href="#16" id="16">We treated each of these six algorithms as separate agents, and modeled their capabilities and task-based relationships when combined to form an ad hoc team.</a>
<a href="#17" id="17">We showed that the weighted synergy graph model forms a near-optimal team, outperforming the teams selected with IQ-ASyMTRe.</a>
<a href="#18" id="18">Hence, the weighted synergy graph model effectively learned and modeled the synergy of the RoboCup Rescue algorithms.</a>
<a href="#19" id="19">The weighted synergy graph effectively models agent capabilities and their task-based relationships.</a>
<a href="#20" id="20">Our algorithms only require the assumption of retrieving observations of the agentsʼ performance at the task, which makes them applicable to many multi-agent and multi-robot domains.</a>
<a href="#21" id="21">In particular, as long as problem domains can be treated as a black-box where the input is a multi-agent team, and the output is an observed performance, the weighted synergy graph model is applicable.</a>
<a href="#22" id="22">We have applied the weighted synergy graph model to multi-robot problems such as foraging [27] and configuring robots from modules [30], and we continue to apply our model to other domains.</a>
<a href="#23" id="23">Modeling and learning the synergy of multi-agent teams is a novel contribution, and we are actively pursuing this area of research.</a>
<a href="#24" id="24">We have successfully applied weighted synergy graphs on actual robots performing role assignment [27] and forming teams that are robust to failures [28], and we have introduced an algorithm to learn the synergy of a new teammate [29].</a>
<a href="#25" id="25">We are using synergy graphs on other interesting problems, such as modeling task-based relationships that are non-transitive, and modeling agents that learn to coordinate better over time.</a>
</body>
</html>