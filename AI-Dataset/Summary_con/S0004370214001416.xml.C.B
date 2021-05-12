<html>
<head>
<meta name="TextLength" content="SENT_NUM:24, WORD_NUM:481">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work we proposed an autonomous aerial cargo delivery agent that works in environments with static obstacles to plan and create trajectories with bounded load displacements.</a>
<a href="#1" id="1">At the heart of the method is the RL policy for minimal residual oscillations trajectories.</a>
<a href="#2" id="2">Planning swing-free trajectories consists of a large action space (over 10{sup:6} actions) that deems learning impractical.</a>
<a href="#3" id="3">For that reason, we find conditions that allow us to learn the swing-free policy in an action subspace several orders of magnitude smaller.</a>
<a href="#4" id="4">In addition, the learning generalizes to an extended state space.</a>
<a href="#5" id="5">Then, we show how a RL policy learned through a single training can be adapted to perform different tasks leveraging different discretized action spaces.</a>
<a href="#6" id="6">We modified the policy by restricting the domain's action space to plan a path-following trajectory with a bounded load displacement.</a>
<a href="#7" id="7">Finally, we integrated the swing-free path-following and sampling-based path planning to solve the aerial cargo delivery task.</a>
<a href="#8" id="8">We evaluated each of the modules separately, and showed that learning converges to a single policy, and that performs minimal residual oscillation delivery task, that the policy is viable with expending state and action spaces.</a>
<a href="#9" id="9">The simulations quality is assessed through the comparison with experimental load displacement on a physical robot.</a>
<a href="#10" id="10">Then we evaluated the swing-free path-following on three reference paths for varying values of the path-following parameters.</a>
<a href="#11" id="11">The results demonstrated that the proposed method attains both good path-following and good load displacement characteristics.</a>
<a href="#12" id="12">Lastly, results of the integration with sampling-based motion planning show that the method creates collision-free trajectories with bounded load displacement for arbitrarily small bounds.</a>
<a href="#13" id="13">We experimentally demonstrated the feasibility and safety of the method by having a quadrotor deliver a cup of water to a human subject.</a>
<a href="#14" id="14">This article lays a foundation for aerial cargo delivery in environments with static obstacles.</a>
<a href="#15" id="15">In further work, trajectory smoothing can be applied to the generated trajectories to accelerate them by not stopping in the waypoints while at the same time ensuring that the trajectories remain collision-free.</a>
<a href="#16" id="16">Moving obstacles can be handled through an online trajectory tracking that adapts to dynamical changes in environment.</a>
<a href="#17" id="17">Beyond aerial cargo delivery, this article address three important question relevant to AI.</a>
<a href="#18" id="18">First, it applies reinforcement learning to a problem with very large action space.</a>
<a href="#19" id="19">To address the curse of dimensionality, it proposes learning in relevant subspaces several orders of magnitude smaller, and planning in the full action space.</a>
<a href="#20" id="20">The article contributes methods for finding the suitable subspaces.</a>
<a href="#21" id="21">Second, it shows that using the feature vectors defined on a larger domain, the learned policy generalizes well outside of the training domain.</a>
<a href="#22" id="22">Lastly, the article proposes learning constraint-balancing tasks on systems with non-linear dynamics by designing feature vectors that are linear maps over the constraints.</a>
<a href="#23" id="23">AI researchers can use the approaches and theory presented in this article to solve other constraint-balancing problems for non-linear systems using RL in continuous state and very large action spaces.</a>
</body>
</html>