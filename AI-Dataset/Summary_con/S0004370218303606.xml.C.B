<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:678">
</head>
<body bgcolor="white">
<a href="#0" id="0">Occlusion is often unavoidable in scenarios involving mobile robots that are observed.</a>
<a href="#1" id="1">We have shown that this cause of persistent hidden data must be accounted for when performing IRL, which otherwise severely impairs the use of common learning techniques such as expectation-maximization to learn a transition DBN.</a>
<a href="#2" id="2">Limited data from observing physical agents performing their tasks further exacerbates this problem and motivated us to relax model assumptions and generalize IRL in this article.</a>
<a href="#3" id="3">In adversarial settings such as the patrolling domain, an expert may not reveal its actions to the learner.</a>
<a href="#4" id="4">However, in robotic scenarios actions often represent movement.</a>
<a href="#5" id="5">Therefore, the patroller's chosen action is revealed by its movement.</a>
<a href="#6" id="6">For instance, the action for a given time step is inferred from the learner's machine vision readings of a patroller over that time step, i.e., constant forward movement during observations would be interpreted as a move_forward action even if the robot did not arrive at the intended next state (the next grid location in front of it).</a>
<a href="#7" id="7">Given our assumption that the intended next state is available while learning the transition function, one could hypothesize that this knowledge alone is sufficient to accurately model the patrollers' transitions.</a>
<a href="#8" id="8">However, our empirical results do not lend support to this hypothesis.</a>
<a href="#9" id="9">Notice in Fig. 15(a) the significant dip in success rates for both mIRL{sup:⁎}+Int and Known R when the probability of transitioning to the intended state is 0.95, which is very close to deterministic motion.</a>
<a href="#10" id="10">Furthermore, we varied the transition success rate of the patrollers as used in mIRL{sup:⁎}+Int in our physical robot experiments all the way to 100% (intended state results with probability 1).</a>
<a href="#11" id="11">Yet, we obtained the best performance of mIRL{sup:⁎}+Int with the physical robots when this success rate is 90%, as we mention in Section 6.3.</a>
<a href="#12" id="12">Together, our comprehensive experimentation in both simulation and with actual platforms already contains evidence that a deterministic transition model is insufficient, as one expects from robot motion, especially in the context of low-cost mobile platforms such as TurtleBots.</a>
<a href="#13" id="13">Our experiments have shown that modeling each observed robot individually and accounting for the sparse interactions between them using an interaction game significantly improves the learning ability for IRL in the presence of multiple robots.</a>
<a href="#14" id="14">Of course, the problem becomes a joint decentralized MDP [18] when interactions are pervasive and extended, and whose solution is usually highly intractable to the order of being doubly exponential in the number of time steps even for just two agents [6].</a>
<a href="#15" id="15">In comparison, modeling sparse interactions separately kept the explosion in complexity comparatively low at a level where physical experimentation was feasible.</a>
<a href="#16" id="16">The methods in this article are applicable to many real-world applications where agents each have their own separate tasks but must interact briefly with others in close proximity occasionally.</a>
<a href="#17" id="17">Finally, we presented a method for inversely learning the partial transition functions of other agents in the presence of limited observations.</a>
<a href="#18" id="18">Our model is applicable to contexts where the transitions of the agent may be attributed to independent underlying components or features that must all function properly for the agent to arrive at an intended state.</a>
<a href="#19" id="19">As the interactions are sparse, the transition probabilities of the multiple observed robots are assumed to be conditionally independent of each other; we may assume locality.</a>
<a href="#20" id="20">The locality can be relaxed by allowing joint actions in {a mathematical formula}TI and {a mathematical formula}ψI thereby mapping state and joint actions to features.</a>
<a href="#21" id="21">Robust evaluations of the methods demonstrated that the dynamics may be learned accurately.</a>
<a href="#22" id="22">In summary, this article contributes important and sophisticated methods that seek to generalize IRL to real-world pragmatics.</a>
<a href="#23" id="23">A line of future investigations may center around making more productive use of the observed data in imputing those portions of the trajectories that are occluded.</a>
<a href="#24" id="24">For example, could we form an informed expectation over the various ways in which the hidden state-action pairs may be realized?</a>
<a href="#25" id="25">Doing so has the potential to improve on the methods presented in this article although we expect a concomitant increase in the computational complexity because of the exponential combinations of hidden states and actions.</a>
</body>
</html>