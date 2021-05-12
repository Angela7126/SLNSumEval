<html>
<head>
<meta name="TextLength" content="SENT_NUM:12, WORD_NUM:365">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have proposed a real-time dynamic programming algorithm that exploits the initial state of knowledge for SSP MDP-IP given in terms of a general set of constraints that can also be applied to factored SSP MDP-IP.</a>
<a href="#1" id="1">To the best of our knowledge, asynchronous algorithms for SSP MDP-IPs have not been proposed before.</a>
<a href="#2" id="2">We first defined an enumerated algorithm, called RTDP-IP, and proved that, despite the imprecision of the transition probabilities, the RTDP-IP algorithm converges for optimal values if the initial value of all the states is admissible and the sampling method does not avoid any state.</a>
<a href="#3" id="3">We have also defined the LRTDP-IP algorithm and were encouraged by the efficiency of SPUDD-IP [31], to propose two factored algorithms, named factRTDP-IP and factLRTDP-IP.</a>
<a href="#4" id="4">These factored asynchronous algorithms get the best of SPUDD-IP and enumerated RTDP-IP approaches: they efficiently represent the value function and only visit the reachable states from {a mathematical formula}s0.</a>
<a href="#5" id="5">However, in our experiments LRTDP-IP shows up to 2 times speedup in comparison to factLRTDP-IP.</a>
<a href="#6" id="6">For sparse domains such as Navigation and Triangle Tire world, LRTDP-IP and factLRTDP-IP yield up to three orders of magnitude speedup in comparison to SPUDD-IP.</a>
<a href="#7" id="7">Additionally, while SPUDD-IP is not able to return a policy for instances with more than 20 variables, LRDP-IP and factLRTDP-IP return optimal policies for instances up to 121 variables in the Navigation domain and for instances up to 80 variables in the Triangle Tire world domain.</a>
<a href="#8" id="8">Another important result for the factLRTDP-IP algorithm is that, if the maximum number of parents in the dynamic credal networks is small and the number of vertices of each credal set is small, there is no significant extra cost involved in calculating the credal set vertices and generating random points for the predefined_parameter_choice and rand_parameter_choice methods.</a>
<a href="#9" id="9">This causes no difference in time when sampling according to minimax_parameter_choice, predefined_parameter_choice or rand_parameter_choice methods.</a>
<a href="#10" id="10">As expected, in a dense domain, SPUDD-IP has a better convergence rate than our proposed asynchronous algorithms.</a>
<a href="#11" id="11">The reason for this is that for dense domains a large number of states can be reached from the initial state and, in this case, there is no advantage in exploring the state space in an asynchronous fashion.</a>
</body>
</html>