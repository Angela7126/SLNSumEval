<html>
<head>
<meta name="TextLength" content="SENT_NUM:18, WORD_NUM:608">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article we addressed the Decentralized Reinforcement Learning (DRL) of individual behaviors of those problems in which multi-dimensional action spaces are involved.</a>
<a href="#1" id="1">First, we have promoted and proposed a five-stages methodology to model and implement a DRL system in which basic concepts, definitions, and practical implementation issues were presented.</a>
<a href="#2" id="2">Second, three Multi-Agent Learning (MAL) algorithms were detailed: independent DRL scheme (DRL-Ind), which does not consider any kind of cooperation or coordination among the agents; the Cooperative Adaptive Learning Rate (DRL-CA) approach, an original contribution which adapts the global learning rate on-line based on a simple estimation of the partial quality of the policy performed by the “weakest” agent; and DRL-Lenient, in which the value function is optimistically updated whenever the last performed action increases the current utility function, or it is leniently updated if the agent has explored that action sufficiently.</a>
<a href="#3" id="3">Particularly DRL-CA and DRL-Lenient add coordination mechanisms in DRL-Ind systems.</a>
<a href="#4" id="4">The proposed DRL methodology and the three considered MAL algorithms were validated with an extensive empirical study on four different problems; two of them are well-known problems: the Three-Dimensional Mountain Car (3DMC), and a SCARA Real-Time Trajectory Generation (SCARA-RTG); and two correspond to noisy and stochastic real-world mobile robot problems: Ball-Dribbling in soccer performed with an omnidirectional biped robot, and the Ball-Pushing behavior performed with a differential robot.</a>
<a href="#5" id="5">Results for 3DMC and Ball-Pushing problems evidenced that DRL implementations show better performances and faster learning times than their CRL (centralized RL) counterparts, even with less computational resources, and non-direct coordination mechanisms.</a>
<a href="#6" id="6">On the other hand, DRL-Lenient and DRL-CA MAL algorithms showed the best final performances for the four tested problems, outperforming their DRL-Ind counterparts in all the problems.</a>
<a href="#7" id="7">Finally, note that the benefits of the proposed MAL methods were more remarkable as the problem complexity increased, such as occurs in the 3DMC ObsL and Ball-Dribbling cases, in which a CRL scheme is infeasible.</a>
<a href="#8" id="8">These results empirically demonstrate that benefits of MAS are also applicable to more complex and real world problems like robotic platforms when using a DRL modeling.</a>
<a href="#9" id="9">Furthermore, the results show DRL as a promising approach to develop applications with higher dimensional action spaces where a CRL scheme could not be easily implementable, such as behavior learning for snake robots, multi-link robotic arms, omnidirectional mobile robots, multi-rotor aerial vehicles, etc.</a>
<a href="#10" id="10">As part of our ongoing research agenda, we plan to combine the benefits of both DRL-CAdec and DRL-CAinc, in order to develop a unique and improved cooperative adaptive method.</a>
<a href="#11" id="11">As a related idea, we are interested in developing a DRL-CA version in which individual adaptive learning rates per action-state pair are available, as well as a full adaptive DRL-CA version where exploration is also dependent on that adaptive parameter.</a>
<a href="#12" id="12">There are a number of possible directions for future work.</a>
<a href="#13" id="13">For now DRL-Lenient and DRL-CA have been implemented based on temporal-difference and discrete action RL methods, and so extending these two methods to model-based and actor-critic algorithms remains an area for future work.</a>
<a href="#14" id="14">Another topic for future work is comparing partial observable MDP MAL algorithms to our DRL-CAdec and DRL-CAinc methods which have shown good results under limited observation conditions.</a>
<a href="#15" id="15">Finally, an interesting research direction is that of exploring possibilities for automated sub-task detection and decomposition.</a>
<a href="#16" id="16">Additionally, since in DRL an agent can be decomposed into several separate agents, real-time communication and observation among those individual agents is not an issue unlike many of the MAS.</a>
<a href="#17" id="17">Thus, sharing information can be the basis for a research line in the field of distributed artificial intelligence, that has not been sufficiently explored yet, in which increasingly sophisticated DRL algorithms can be developed, taking advantage of DRL systems' properties.</a>
</body>
</html>