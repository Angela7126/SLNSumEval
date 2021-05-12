<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:350">
</head>
<body bgcolor="white">
<a href="#0" id="0">Learning with real robots is very time consuming if actions take several seconds to complete.</a>
<a href="#1" id="1">Therefore, learning algorithms should require as few executions as possible.</a>
<a href="#2" id="2">We addressed this problem using relational RL with demonstrations.</a>
<a href="#3" id="3">We combined the generalization capabilities of learning in relational domains, where the same type of objects have to be learned only once, with teacher demonstrations, thereby significantly reducing the number of exploration actions required, which is the longest part of the learning process.</a>
<a href="#4" id="4">In the proposed REX-D algorithm, we added demonstration requests to the relational RL algorithm REX.</a>
<a href="#5" id="5">In addition to the faster learning, demonstrations allow the algorithm to learn actions as they are required by extending generalization to different tasks, and new actions can be added if necessary.</a>
<a href="#6" id="6">Another aspect of the proposed method is the use of action rules analysis to help the teacher, which minimizes the number of demonstrations required in a task.</a>
<a href="#7" id="7">The improvements include providing guidance to the teacher so only the unknown actions need to be demonstrated, checking for valid action rule alternatives before requesting new demonstrations, and using subgoals in tasks where demonstrating new actions may require the execution of previously known actions.</a>
<a href="#8" id="8">We performed several experiments to analyze the performance of the REX-D algorithm.</a>
<a href="#9" id="9">Standard domains from the international planning competition were used to compare our approach with other relational RL methods, which demonstrated that significant improvements were obtained.</a>
<a href="#10" id="10">Further experiments were also performed using the Cranfield benchmark encoded in a VR system, which provided the user with a similar experience to a real robot.</a>
<a href="#11" id="11">In conclusion, we proposed a relational RL algorithm with demonstration requests that improves the learning time while aiming to minimize the number of teacher interactions.</a>
<a href="#12" id="12">In future research, it would be useful to adapt REX-D to partially observable domains, where the planner and the learner would have to consider uncertainty.</a>
<a href="#13" id="13">Approaches are available that learn partially observable domains instead of deterministic domains [26], but a new learning algorithm would have to be developed that covers both partially observable and stochastic actions.</a>
<a href="#14" id="14">On the planning side, any partially observable MDP solver can be used.</a>
</body>
</html>