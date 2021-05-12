<html>
<head>
<meta name="TextLength" content="SENT_NUM:19, WORD_NUM:428">
</head>
<body bgcolor="white">
<a href="#0" id="0">Distributed Constraint Optimization Problems (DCOPs) can be used to model many realistic combinatorial problems that are distributed by nature.</a>
<a href="#1" id="1">The growing interest in this field has motivated intensive study in recent years on search algorithms for solving DCOPs.</a>
<a href="#2" id="2">Since DCOPs are NP-hard optimization problems, complete algorithms are useful only for small problems.</a>
<a href="#3" id="3">Larger problems like the ones studied in our experiments require incomplete methods.</a>
<a href="#4" id="4">Distributed local search algorithms were originally proposed for Distributed Constraint Satisfaction Problems and subsequently applied for DCOPs [7].</a>
<a href="#5" id="5">However, these algorithms failed to report the best state traversed by the algorithm, due to the challenge in evaluating global cost from the private, local costs of individual agents.</a>
<a href="#6" id="6">To meet this challenge, we proposed ALS_DCOP, a general framework for performing distributed local search in DCOPs that provides them with the anytime property.</a>
<a href="#7" id="7">In the proposed framework, agents use a spanning tree structure in order to accumulate the costs of a state of the system to the root agent, which compares the cost of each state with the cost of the best state found so far and propagates the step index of a new best state, once it is found, to all other agents.</a>
<a href="#8" id="8">At the end of the run the agents hold the best state that was traversed by the algorithm.</a>
<a href="#9" id="9">Apart from a small number of idle steps at the end of the run of the algorithm (twice the height of the spanning tree), the framework does not require any additional slowdown in the performance of the algorithm.</a>
<a href="#10" id="10">In contrast to complete algorithms that use a pseudo-tree, the tree used in ALS_DCOP can be a Breadth First Search (BFS) tree.</a>
<a href="#11" id="11">Thus, the height of the tree is expected to be small.</a>
<a href="#12" id="12">In terms of network load, the only messages used in the ALS_DCOP framework are the algorithm's messages (i.e., no additional messages are required by the framework).</a>
<a href="#13" id="13">Agents are required to use small (linear in the worst case) additional space.</a>
<a href="#14" id="14">Most existing local search algorithms for DCOPs are either monotonic (completely exploitive) or perform limited exploration.</a>
<a href="#15" id="15">Thus, there is a limited benefit when combining the ALS_DCOP framework with these algorithms.</a>
<a href="#16" id="16">However, we demonstrate that the framework enhances existing explorative algorithms such as DBA and Max-Sum.</a>
<a href="#17" id="17">In order to demonstrate the full potential of the framework we proposed extreme explorative methods, which are combined with existing local search algorithms (DSA and DBA), and two algorithm-independent exploration methods that can be combined with any existing incomplete DCOP algorithms.</a>
<a href="#18" id="18">Our results demonstrate the advantage of the combination of exploration and the anytime property over standard local search.</a>
</body>
</html>