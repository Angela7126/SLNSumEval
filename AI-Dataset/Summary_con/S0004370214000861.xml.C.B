<html>
<head>
<meta name="TextLength" content="SENT_NUM:9, WORD_NUM:263">
</head>
<body bgcolor="white">
<a href="#0" id="0">Abstraction from demonstration approaches perform better than policies built using direct LfD, even when LfD uses an order of magnitude more demonstrations.</a>
<a href="#1" id="1">Sample efficiency is one of the key advantages of our algorithms, given that obtaining good human demonstrations is often expensive and time-consuming.</a>
<a href="#2" id="2">Because of the cost of acquiring human samples, it might be desirable to avoid it altogether and use direct RL algorithms without using demonstrations; however, AfD and ADA achieve significant speed-ups by taking advantage of the exponential savings of dimensionality reduction, and converge to a high-performance policy in minutes, while learning without demonstrations did not show improvement over the initial random policy, even after days of computation.</a>
<a href="#3" id="3">This speed-up suggests that, in many domains, even including the time and cost required to acquire the human demonstrations, AfD will be more cost-effective and time-effective than learning without using human demonstrations.</a>
<a href="#4" id="4">Another advantage of abstraction from demonstration is that its performance is not limited to that of the teacher.</a>
<a href="#5" id="5">AfD and ADA use the reward signal to obtain the best policy that can sometimes be expressed in their reduced feature space.</a>
<a href="#6" id="6">This policy, as our results show, can be significantly better than that of the teacher.</a>
<a href="#7" id="7">Abstraction from demonstration can also extend the class of sequential decision problems that can be solved with FA-based RL algorithms such as fitted Q-learning and LSPI, simultaneously reducing the amount of manual feature engineering necessary to adapt the algorithms to new domains.</a>
<a href="#8" id="8">This is achieved through polynomial speed-ups with respect to the number of state features and extensions of the hypothesis space by task decomposition.</a>
</body>
</html>