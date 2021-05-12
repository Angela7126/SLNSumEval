<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:193">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have introduced relational linear programming, a simple framework combining linear and logic programming.</a>
<a href="#1" id="1">Its main building blocks are relational linear programs (RLPs).</a>
<a href="#2" id="2">They are compact LP templates defining the objective and the constraints through the logical concepts of individuals, relations, and quantified variables.</a>
<a href="#3" id="3">This contrasts with mainstream LP template languages such as AMPL, which mixes imperative and linear programming, and allows a more intuitive representation of optimization problems over relational domains where we have to reason about a varying number of objects and relations among them, without enumerating them.</a>
<a href="#4" id="4">Inference in RLPs is performed by lifted linear programming.</a>
<a href="#5" id="5">That is, symmetries within the ground linear program are employed to reduce its dimensionality, if possible, and the reduced program is solved using any off-the-shelf linear program solver.</a>
<a href="#6" id="6">This significantly extends the scope of lifted inference since it paves the way for lifted LP solvers for linear assignment, allocation and many other AI task that can be solved using LPs.</a>
<a href="#7" id="7">Empirical results on approximate inference in Markov logic networks using LP relaxations, on solving Markov decision processes, and on collective inference using relational LP support vector machines illustrated the promise of relational linear programming.</a>
</body>
</html>