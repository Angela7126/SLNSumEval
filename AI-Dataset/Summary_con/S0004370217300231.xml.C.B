<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:255">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have presented a novel model called Hierarchical Semi-Markov Conditional Random Field which extends the standard CRFs to incorporate hierarchical and multilevel semantics.</a>
<a href="#1" id="1">We have developed a graphical model-like dynamic representation of the HSCRF.</a>
<a href="#2" id="2">We have derived efficient algorithms for learning and inference, especially the ability to learn and inference with partially given labels.</a>
<a href="#3" id="3">We have demonstrated the capacity of the HSCRFs on home video surveillance data and the shallow parsing of English text, in which the hierarchical information inherent in the context helps to increase the recognition.</a>
<a href="#4" id="4">In future work we plan to attack the computational bottleneck in large-scale settings.</a>
<a href="#5" id="5">Although the AIO family has cubic time complexity, it is still expensive in large-scale application, especially those with long sequences.</a>
<a href="#6" id="6">It is therefore desirable to introduce approximation methods that can provide speed/quality trade-offs.</a>
<a href="#7" id="7">Our early work using Rao-Blackwellised Gibbs sampling shows promising results [37].</a>
<a href="#8" id="8">We also need to make a choice between pre-computing all the potentials prior to inference and learning, and computing them on-the-fly.</a>
<a href="#9" id="9">The first choice requires {a mathematical formula}O(DK3T2) space, which is very significant with typical real-world problems, even with today's computing power.</a>
<a href="#10" id="10">The second choice, however, will slow the inference and learning very significantly due to repeated computation at every step of the AIO algorithm.</a>
<a href="#11" id="11">Finally, it is interesting to see how good the HSCRFs can be an approximation to general multilevel processes, which are not necessarily recursive (e.g., HSCRF as an approximation to DCRFs).</a>
<a href="#12" id="12">This is important because HSCRFs are tractable while DCRFs are generally not.</a>
</body>
</html>