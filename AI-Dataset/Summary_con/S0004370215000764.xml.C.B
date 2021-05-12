<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:492">
</head>
<body bgcolor="white">
<a href="#0" id="0">This article presents the texplore-vanir algorithm for intrinsically motivated learning.</a>
<a href="#1" id="1">This algorithm combines random forest based model learning with two novel intrinsic rewards.</a>
<a href="#2" id="2">One reward drives the agent to where the model is uncertain in its predictions, and the second drives the agent to acquire novel experiences that its model has not been trained on.</a>
<a href="#3" id="3">This article presents three main contributions:</a>
<a href="#4" id="4">Novel methods for obtaining intrinsic rewards from a random-forest-based model of the world.</a>
<a href="#5" id="5">The texplore-vanir algorithm for intrinsically motivated model learning, which has been released open-source as an ROS package: http://www.ros.org/wiki/rl-texplore-ros-pkg.</a>
<a href="#6" id="6">Empirical evaluations of the algorithm, both in a simulated domain and on a physical robot.</a>
<a href="#7" id="7">Experiments show empirically that texplore-vanir can learn accurate and useful models in a domain with no external rewards.</a>
<a href="#8" id="8">In addition, texplore-vanir's intrinsic rewards drive the agent to learn in a developing and curious way, progressing from learning easier to more difficult skills.</a>
<a href="#9" id="9">texplore-vanir can also combine its intrinsic rewards with external task rewards to learn a task faster than using external rewards alone.</a>
<a href="#10" id="10">One of the major use cases of this type of learning is learning on robots.</a>
<a href="#11" id="11">Robots must learn their own dynamics and environment affordances, which are then applicable to tasks the robot may want to perform in its environment.</a>
<a href="#12" id="12">We demonstrated texplore-vanir learning to move the arm of an Aldebaran Nao humanoid robot.</a>
<a href="#13" id="13">First, the agent learned solely from intrinsic motivation, exploring the state space, and then we showed that it was able to use its learned model to perform various tasks in the domain.</a>
<a href="#14" id="14">Our main interest in the pursuit of this research is to apply it to developmental learning on robots.</a>
<a href="#15" id="15">One area where texplore-vanir's performance on robots can be improved is handling continuous actions.</a>
<a href="#16" id="16">While texplore-vanir selects from a set of discrete actions, robots typically take a vector of continuous commands.</a>
<a href="#17" id="17">For example, controlling the Aldebaran Nao robot requires a continuous vector of either desired velocities or positions for each of the robot's 25 joints.</a>
<a href="#18" id="18">texplore-vanir's tree models should already be able to handle multi-dimensional continuous actions as input in making predictions about the next state and reward.</a>
<a href="#19" id="19">Thus, extending texplore-vanir to use multi-dimensional continuous actions mainly requires extensions to the uct planning algorithm for sampling and selecting from a multi-dimensional continuous action space.</a>
<a href="#20" id="20">One possible approach to this problem is to utilize recent work [37], [38] adapting the hoo algorithm for continuous bandit problems [39] to action selection at each level of the uct tree.</a>
<a href="#21" id="21">The texplore-vanir algorithm represents an important step towards fully autonomous developmental learning on robots.</a>
<a href="#22" id="22">The texplore-vanir algorithm could be utilized on robots in multiple ways.</a>
<a href="#23" id="23">It can be used without an external reward on robots to create curious robots that learn and develop.</a>
<a href="#24" id="24">It can also be combined with external rewards to speed up learning of tasks.</a>
<a href="#25" id="25">By releasing texplore-vanir as an open-source ROS package, we hope many other researchers are able to apply and extend it on their robots to improve learning.</a>
</body>
</html>