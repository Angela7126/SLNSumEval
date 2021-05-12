<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:214">
</head>
<body bgcolor="white">
<a href="#0" id="0">{a mathematical formula}∀j,F1j∈S.</a>
<a href="#1" id="1">Results and analysis</a>
<a href="#2" id="2">Before optimizing parameters for the walk engine, “getup” behaviors are learned so that if the robot falls over it is able to stand back up and start walking again.</a>
<a href="#3" id="3">For all layers of learned behaviors the CMA-ES [14] algorithm is used as the ML algorithm (M).</a>
<a href="#4" id="4">This approach to optimization is an example of sequential layered learning as the output of one learned subtask (the Walk_GoToTarget parameter set) is fed in as input to the learning of the next subtask (the learning of the Walk_Sprint parameter set).</a>
<a href="#5" id="5">It is noted above in the definition of {a mathematical formula}Fi→ that ∀j, {a mathematical formula}F1j∈S.</a>
<a href="#6" id="6">Furthermore, progressive neural networks leverage task similarities to learn successive tasks through transfer learning [34], in which they focus on learning policies for tasks that are performed in isolation from each other, where as overlapping layered learning is better suited for developing subtasks that work well together and can smoothly transition between each other.</a>
<a href="#7" id="7">The getup behavior parameters are re-optimized from their primitive behavior values through the same optimization as the getup primitives, but with the addition that right after completing a getup behavior the robot is asked to walk in different directions and is penalized if it falls over while trying to do so.</a>
</body>
</html>