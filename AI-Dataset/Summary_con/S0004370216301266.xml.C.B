<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:607">
</head>
<body bgcolor="white">
<a href="#0" id="0">Given the growing numbers of agents in the world in the form of both robots and software agents, it is becoming a necessity for agents to cooperate to achieve their goals.</a>
<a href="#1" id="1">However, cooperating with pre-designed teams is not enough; the agents will need to cooperate with a variety of teammates designed by other developers.</a>
<a href="#2" id="2">Therefore, it is vital that the agents can reason about ad hoc teams, in which the agents adapt to their teammates on the fly.</a>
<a href="#3" id="3">This article investigates a limited version of the ad hoc teamwork problem, in which the ad hoc agent knows the environmental dynamics and has had previous interactions with other teammates and can exploit similarities between the teammates' behaviors.</a>
<a href="#4" id="4">It is an ad hoc teamwork problem due to the fact that the ad hoc agent does not know the behavior of its teammates and its past teammates are not necessarily representative of its current teammates.</a>
<a href="#5" id="5">PLASTIC reuses knowledge learned from past teammates and combines this knowledge with any advice provided by domain experts.</a>
<a href="#6" id="6">This approach allows PLASTIC to quickly adapt to new teammates on the fly.</a>
<a href="#7" id="7">We show that PLASTIC performs well on two disparate domains with a variety of teammates and differing amounts of knowledge about its teammates.</a>
<a href="#8" id="8">While PLASTIC assumes that the current teammates' behaviors are similar to past teammates' behaviors, in our experiments, the behaviors were not explicitly designed to be similar.</a>
<a href="#9" id="9">Instead, the teammates were created by a variety of independent developers.</a>
<a href="#10" id="10">Nonetheless, PLASTIC was still able to discover similarities between these teammates' behaviors.</a>
<a href="#11" id="11">While this article covers many topics on research about ad hoc teams, it also raises many interesting questions.</a>
<a href="#12" id="12">The teammates in this article are not explicitly learning about the ad hoc agent as it interacts with them.</a>
<a href="#13" id="13">Therefore, one question is how to learn about these teammates while they are learning about the ad hoc agent.</a>
<a href="#14" id="14">One approach to tackling this problem is for the ad hoc agent to maintain additional models of learning algorithms its teammates may be using.</a>
<a href="#15" id="15">These models' learning algorithms would be updated with new observations in addition to updating the probabilities of the models relative to each other.</a>
<a href="#16" id="16">Another approach is to consider the problem in the recursive modeling setting [20], whereby the ad hoc agent would reason about how its teammates are reasoning about it.</a>
<a href="#17" id="17">Additionally, PLASTIC may perform arbitrarily poorly when it encounters new teammates.</a>
<a href="#18" id="18">PLASTIC relies on what it has learned about previous teammates, and if the new teammates' behaviors are arbitrarily far from these previous teammates, PLASTIC's performance may be arbitrarily bad.</a>
<a href="#19" id="19">Falling back to learning from scratch is promising, but too slow for the time periods considered in this article.</a>
<a href="#20" id="20">Instead, falling back to using a behavior with known bounds on the team's performance, like a safety strategy, is promising.</a>
<a href="#21" id="21">However, calculating a behavior with bounded performance on ad hoc teamwork problems remains an open question.</a>
<a href="#22" id="22">A further interesting topic is to evaluate how well agents on ad hoc teams can learn about their environment as they also learn about their teammates.</a>
<a href="#23" id="23">To simultaneously learn about unknown tasks and unknown teammates, an ad hoc team agent will need to balance the trade-off between exploiting its current knowledge, exploring the dynamics of the task, and exploring the behavior of its teammates.</a>
<a href="#24" id="24">A possible approach to quickly learn in this scenario is for the ad hoc agent to also consider a set of previous environmental models to select from and update these models over time.</a>
<a href="#25" id="25">We look forward to future research along all these directions and believe that this article takes a significant step towards making such novel research on ad hoc teamwork possible.</a>
</body>
</html>