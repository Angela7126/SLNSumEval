<html>
<head>
<meta name="TextLength" content="SENT_NUM:9, WORD_NUM:225">
</head>
<body bgcolor="white">
<a href="#0" id="0">Model-based reinforcement learning is a powerful paradigm for learning tasks in robotics.</a>
<a href="#1" id="1">However, in-depth exploration is usually required and the actions have to be known in advance.</a>
<a href="#2" id="2">Thus, we propose a novel algorithm that integrates the option of requesting teacher demonstrations to learn new domains with fewer action executions and no previous knowledge.</a>
<a href="#3" id="3">Demonstrations allow new actions to be learned and they greatly reduce the amount of exploration required, but they are only requested when they are expected to yield a significant improvement because the teacher's time is considered to be more valuable than the robot's time.</a>
<a href="#4" id="4">Moreover, selecting the appropriate action to demonstrate is not an easy task, and thus some guidance is provided to the teacher.</a>
<a href="#5" id="5">The rule-based model is analyzed to determine the parts of the state that may be incomplete, and to provide the teacher with a set of possible problems for which a demonstration is needed.</a>
<a href="#6" id="6">Rule analysis is also used to find better alternative models and to complete subgoals before requesting help, thereby minimizing the number of requested demonstrations.</a>
<a href="#7" id="7">These improvements were demonstrated in a set of experiments, which included domains from the international planning competition and a robotic task.</a>
<a href="#8" id="8">Adding teacher demonstrations and rule analysis reduced the amount of exploration required by up to 60% in some domains, and improved the success ratio by 35% in other domains.</a>
</body>
</html>