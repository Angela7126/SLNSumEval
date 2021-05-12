<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:320">
</head>
<body bgcolor="white">
<a href="#0" id="0">Besides the considered scenario, the method is generic and can be used in other human–robot interaction scenarios.</a>
<a href="#1" id="1">The racket moves towards this hitting state and hits the ball at the end of the hitting stage.</a>
<a href="#2" id="2">In addition, we consider a naive baseline where the action is chosen only based on the most likely prediction without considering predictive uncertainty, i.e., the belief state θ is represented only by the mean of latent state and the most likely intention.</a>
<a href="#3" id="3">We do not have closed-form solutions for the decision making problem in our application due to the complexity of the human dynamics.</a>
<a href="#4" id="4">An observation {a mathematical formula}z∈Z includes perceived features of the environment, such as the position and velocity of the ball and the configuration of the opponent's racket.</a>
<a href="#5" id="5">The presented method is applicable when the intention is multi-dimensional variables, in which case MCP is a preferred tool for solving POMDPs; it is non-trivial for LSPI to model and parametrize the distribution of multi-dimensional and potentially multi-modal intention.</a>
<a href="#6" id="6">For example, a robot that navigates in an indoor environment alongside humans needs to constantly predict their trajectories in order to avoid collisions and to optimize its path [56].</a>
<a href="#7" id="7">A common way to deal with large or infinite state space is value function approximation by a linear combination of basis functions {a mathematical formula}ϕ(θ,a), given by{a mathematical formula} with parameters w. Taking into account these factors, we choose the Least-Squares Policy Iteration (LSPI) algorithm [24], a model-free reinforcement learning algorithm with the function approximation.</a>
<a href="#8" id="8">Hence, it is essential to choose the optimal action at the right time.</a>
<a href="#9" id="9">Therefore, we enforce that the robot takes a stopping action when the robot's hitting point can be reliably predicted by the vision system, which typically happens within 120 ms after the human player returns the ball [53].</a>
<a href="#10" id="10">Despite the simplification, the case study clearly showed the importance of combining anticipation and planning and the feasibility of presented methods.</a>
</body>
</html>