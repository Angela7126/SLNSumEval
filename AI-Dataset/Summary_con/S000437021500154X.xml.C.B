<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:330">
</head>
<body bgcolor="white">
<a href="#0" id="0">Optimal planning and heuristic search systems solve state-space search problems by finding a least-cost path from start to goal.</a>
<a href="#1" id="1">As a byproduct of having an optimal path they also determine the optimal solution cost.</a>
<a href="#2" id="2">However, there are situations in which the optimal path is not needed – one is interested only in the optimal solution cost.</a>
<a href="#3" id="3">In this paper we presented BiSS, an efficient algorithm that accurately predicts the optimal solution cost without finding a least-cost path from start to goal.</a>
<a href="#4" id="4">BiSS is based on the ideas of bidirectional search and stratified sampling.</a>
<a href="#5" id="5">BiSS does not require preprocessing and is guaranteed to return the optimal solution cost in the limit as the number of its probes goes to infinity.</a>
<a href="#6" id="6">We showed empirically that BiSS makes very accurate predictions in several domains.</a>
<a href="#7" id="7">BiSS's predictions, with an appropriate setting of its parameters, were never worse than SCP's in our experiments and were sometimes much better.</a>
<a href="#8" id="8">BiSS scales much better than SCP.</a>
<a href="#9" id="9">Finally, we showed it could be applied to state spaces much larger than can be solved optimally in a reasonable time.</a>
<a href="#10" id="10">In this paper we also presented BiSS-h, a learning system that uses a solution cost predictor instead of a search algorithm to generate the training set required to learn heuristics.</a>
<a href="#11" id="11">BiSS-h is able to learn effective heuristics much faster than Bootstrap – a learning method that uses a search algorithm to generate the training set.</a>
<a href="#12" id="12">Our system reduces the time required by Bootstrap to learn effective heuristics from days to minutes.</a>
<a href="#13" id="13">The batch learning process of BiSS-h is even faster than Bootstrap's interleaving process for solving a single instance.</a>
<a href="#14" id="14">Speeding up the process of learning heuristic functions is just one of the applications of a solution cost predictor.</a>
<a href="#15" id="15">As two other examples, SCP has been applied for setting the w-value of Weighted IDA* and the bound for Potential Search [47]; in both applications we observed search speedups [29].</a>
<a href="#16" id="16">Exploring other applications of BiSS is an exciting direction of future research.</a>
</body>
</html>