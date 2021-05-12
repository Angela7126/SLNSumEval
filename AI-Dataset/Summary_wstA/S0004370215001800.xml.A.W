<html>
<head>
<meta name="TextLength" content="SENT_NUM:10, WORD_NUM:270">
</head>
<body bgcolor="white">
<a href="#0" id="0">Inverse reinforcement learning (IRL), analogously to RL, refers to both the problem and associated methods by which an agent passively observing another agent's actions over time, seeks to learn the latter's reward function.</a>
<a href="#1" id="1">The learning agent is typically called the learner while the observed agent is often an expert in popular applications such as in learning from demonstrations.</a>
<a href="#2" id="2">Some of the assumptions that underlie current IRL methods are impractical for many robotic applications.</a>
<a href="#3" id="3">Specifically, they assume that the learner has full observability of the expert as it performs its task; that the learner has full knowledge of the expert's dynamics; and that there is always only one expert agent in the environment.</a>
<a href="#4" id="4">For example, these assumptions are particularly restrictive in our application scenario where a subject robot is tasked with penetrating a perimeter patrol by two other robots after observing them from a vantage point.</a>
<a href="#5" id="5">In our instance of this problem, the learner can observe at most 10% of the patrol.</a>
<a href="#6" id="6">We relax these assumptions and systematically generalize a known IRL method, Maximum Entropy IRL, to enable the subject to learn the preferences of the patrolling robots, subsequently their behaviors, and predict their future positions well enough to plan a route to its goal state without being spotted.</a>
<a href="#7" id="7">Challenged by occlusion, multiple interacting robots, and partially known dynamics we demonstrate empirically that the generalization improves significantly on several baselines in its ability to inversely learn in this application setting.</a>
<a href="#8" id="8">Of note, it leads to significant improvement in the learner's overall success rate of penetrating the patrols.</a>
<a href="#9" id="9">Our methods represent significant steps towards making IRL pragmatic and applicable to real-world contexts.</a>
</body>
</html>