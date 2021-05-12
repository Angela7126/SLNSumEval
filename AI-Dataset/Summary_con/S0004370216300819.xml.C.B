<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:459">
</head>
<body bgcolor="white">
<a href="#0" id="0">Automated planning and reinforcement learning are two different paradigms for solving complex decision making problems.</a>
<a href="#1" id="1">Both paradigms face challenges in high-level decision making on large, unpredictable, and non-stationary domains, especially in robotics.</a>
<a href="#2" id="2">Their characteristics, however, admit an integration that can benefit from their stronger features, and overcome some of their respective weaknesses.</a>
<a href="#3" id="3">We proposed a method, DARLING, to combine automated planning and reinforcement learning, which extends the applicability of both paradigms to scenarios where each one separately would not be sufficient.</a>
<a href="#4" id="4">We analyzed the performance of DARLING in domains in which a discretization of the state space appeared natural, which allowed us to use ASP.</a>
<a href="#5" id="5">In high-dimensional continuous domains it may not be possible to find such a discretization, and a similar argument holds for the discretization of continuous actions.</a>
<a href="#6" id="6">This is a limitation we recognize in the approach as presented in this article, and significant adjustments may be necessary to DARLING, and the planning formalism employed, to deal with such domains.</a>
<a href="#7" id="7">The total number of plans computed by the ASP solver in general increases exponentially in the length of the shortest plan.</a>
<a href="#8" id="8">As a consequence, in the real-world domains the number of plans was often limited by planning time, rather than plan length.</a>
<a href="#9" id="9">The deadline gives the agent no control on which plans are included and which ones are discarded.</a>
<a href="#10" id="10">A possible interesting development is the use of a set of diverse plans[29] (also in ASP [9]) to focus the search, and on which to expand during execution.</a>
<a href="#11" id="11">Lastly, we showed in Section 4.4 how the metric used for the threshold does not have to be related with the actual cost of actions.</a>
<a href="#12" id="12">However, if plan length, which is the metric we used, does not permit to define a satisfactory threshold function, the designer will have to define an ad-hoc one, and to employ a planner that minimizes it.</a>
<a href="#13" id="13">Sampling-based planning, which in recent years has scaled up to the most challenging domains, could be employed in that case.</a>
<a href="#14" id="14">Within the range of applicability of DARLING, we showed how, on the planning side, the ability to learn lightens the reliance on the accuracy of the model, and allows the agent to adapt to the environment.</a>
<a href="#15" id="15">On the reinforcement learning side, the rationality of the automated reasoner, and the previous knowledge in the model, allow the agent to exclude certain actions without the need to try them.</a>
<a href="#16" id="16">We showed in different experiments how this integration modifies the region of the environment explored by the agent, how it allows the agent to adapt to a non-stationary environment, and how it enabled a service robot to carry out different tasks over an extended period of time, where planning would often fail and reinforcement learning could not complete any of the tasks.</a>
</body>
</html>