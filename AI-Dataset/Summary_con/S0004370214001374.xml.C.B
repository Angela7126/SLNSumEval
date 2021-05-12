<html>
<head>
<meta name="TextLength" content="SENT_NUM:11, WORD_NUM:220">
</head>
<body bgcolor="white">
<a href="#0" id="0">We presented GPREPS, a novel model-based contextual policy search algorithm based on GP models and information-theoretic policy search.</a>
<a href="#1" id="1">We learn an upper level policy that efficiently generalizes the lower level policy parameters ω over multiple contexts.</a>
<a href="#2" id="2">GPREPS is based on REPS, an information-theoretic policy search algorithm.</a>
<a href="#3" id="3">It exploits learned probabilistic forward models of the robot and its environment to predict expected rewards of artificially generated data points.</a>
<a href="#4" id="4">For evaluating the expected reward, GPREPS samples trajectories using the learned models.</a>
<a href="#5" id="5">Unlike deterministic inference methods used in state-of-the art approaches for policy evaluation, trajectory sampling is easy to implement, easy to parallelize and does not limit the policy class or the used reward model.</a>
<a href="#6" id="6">With simulated and real robot experiments, we demonstrated that GPREPS significantly reduces the required amount of measurement data to learn high quality policies compared to state-of-the-art model free contextual policy search approaches.</a>
<a href="#7" id="7">Moreover, the GP models are able to incorporate the model uncertainty and produce accurate trajectory distributions.</a>
<a href="#8" id="8">Thus, with GPREPS we avoid the risk of learning from noisy reward samples that results in a bias in the model-free REPS formulation.</a>
<a href="#9" id="9">The increased data efficiency makes GPREPS applicable to learning contextual policies in real-robot tasks.</a>
<a href="#10" id="10">Since existing model-based policy search methods cannot be applied to the contextual setup, GPREPS allows for many new applications of model-based policy search.</a>
</body>
</html>