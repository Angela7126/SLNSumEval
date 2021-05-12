<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:356">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we proposed an extension of betweenness centrality, which is based on Semivalues—a wide and flexible family of solution concepts from coalitional game theory.</a>
<a href="#1" id="1">Our measure provides a ranking of nodes by considering the roles they each play in different groups of nodes, where a group is evaluated in terms of its group-betweenness centrality.</a>
<a href="#2" id="2">Although Semivalues are, in general, computationally challenging, we showed that the new measure can be computed efficiently.</a>
<a href="#3" id="3">More specifically, we proposed polynomial-time algorithms to compute all Semivalue-based betweenness centralities for weighted graphs as well as unweighted graphs.</a>
<a href="#4" id="4">These include both the Shapley value-based and the Banzhaf Index-based betweenness centralities.</a>
<a href="#5" id="5">Interestingly, our algorithm for computing the Shapley value-based centrality for unweighted networks has the same time complexity as the best known algorithm due to Brandes [15] for computing the standard betweenness centrality.</a>
<a href="#6" id="6">To compare our Semivalue-based betweenness centrality measure against the standard one, we considered scenarios in which simultaneous node failures occur.</a>
<a href="#7" id="7">Here, the level of protection (against failure) for each node was set to be proportional to its centrality.</a>
<a href="#8" id="8">This way, each centrality measure can be evaluated based on the quality of the corresponding node protection, which in turn is evaluated based on its ability to preserve as much as possible of the network's performance after the failure has occurred.</a>
<a href="#9" id="9">This revealed that our measure outperforms the standard one in several real-life networks.</a>
<a href="#10" id="10">There are several potential directions for future work.</a>
<a href="#11" id="11">Firstly, it would be interesting to extend the algorithms proposed in this article to streaming graphs [37].</a>
<a href="#12" id="12">The challenge here is to efficiently re-compute the centralities and update the ranking of nodes after each change in the structure of the network, i.e., after adding/removing some nodes and/or edges.</a>
<a href="#13" id="13">Secondly, we are keen to develop polynomial-time algorithms for other versions of betweenness centrality, such as routing betweenness centrality [24].</a>
<a href="#14" id="14">Finally, we would like to identify various axiomatic systems that each uniquely characterize our centrality measure.</a>
<a href="#15" id="15">Such an axiomatic approach is common in the literature on cooperative game theory, and we believe it would be interesting to follow a similar approach to analyze centrality measures in general, and ours in particular.</a>
</body>
</html>