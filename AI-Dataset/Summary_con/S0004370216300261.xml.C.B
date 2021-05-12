<html>
<head>
<meta name="TextLength" content="SENT_NUM:8, WORD_NUM:195">
</head>
<body bgcolor="white">
<a href="#0" id="0">This paper investigates the one-pass AUC optimization that requires going through the training data only once, without storing the entire dataset.</a>
<a href="#1" id="1">Here, a big challenge lies in the fact that AUC is measured by a sum of losses defined over pairs of instances from different classes.</a>
<a href="#2" id="2">We propose the OPAUC approach, which employs the least square loss and requires the storing of only the first and second-statistics for the received training examples.</a>
<a href="#3" id="3">A nice property of OPAUC is that its storage requirement is O({a mathematical formula}d2), where d is the dimension of data, independent of the number of training examples.</a>
<a href="#4" id="4">To handle high-dimensional tasks, we develop two deterministic strategies to approximate the covariance matrices for dense and sparse datasets, respectively.</a>
<a href="#5" id="5">The effectiveness of our proposed approach is verified both theoretically and empirically.</a>
<a href="#6" id="6">In particular, the performance of OPAUC is significantly better than online AUC optimization approaches, and is even competitive to batch learning approaches; the approximate OPAUC is significantly better than all compared methods.</a>
<a href="#7" id="7">An interesting future issue is to develop one-pass AUC optimization approaches not only with a performance comparable to batch approaches, but also with an efficiency comparable to univariate loss optimization approaches.</a>
</body>
</html>