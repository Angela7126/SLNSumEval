<html>
<head>
<meta name="TextLength" content="SENT_NUM:14, WORD_NUM:392">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this work, we demonstrated that sequential algorithms can be combined automatically and effectively into parallel portfolios, following an approach we call Automatic Construction of Parallel Portfolios (ACPP).</a>
<a href="#1" id="1">This approach enables solver developers to leverage parallel resources without having to be concerned with synchronization, race conditions or other difficulties that arise in the explicit design of parallel code.</a>
<a href="#2" id="2">Of course, inherently parallel solving techniques (e.g., based on clause sharing) can further improve the performance of our ACPP portfolios.</a>
<a href="#3" id="3">In this view, ACPP can also be used to support a human developer by determining a well-performing parallel portfolio which can provide a base for (i) adding clause sharing, (ii) identifying complementary configurations or (iii) as starting point for further manual fine-tuning and development of new techniques.</a>
<a href="#4" id="4">We investigated two different ACPP procedures: (i) configuration in the joint configuration space of all portfolio components (Global); and (ii) iteratively adding one or more component solvers at a time (parHydra).</a>
<a href="#5" id="5">We assessed these procedures on widely studied classes of satisfiability problems: the application and hard combinatorial tracks of the 2012 SAT Challenge.</a>
<a href="#6" id="6">Overall, we found that parHydra was the most practical method.</a>
<a href="#7" id="7">The configuration space of Global grows exponentially with the size of the portfolio; thus, while in principle it subsumes the other methods, in practice, it tended to find worse portfolios than parHydra within available time budgets.</a>
<a href="#8" id="8">In contrast to Global, parHydra was able to find well-performing portfolios on all of our domains; using pfolioUZK's solvers on application instances, it even was able to reach the performance level of Plingeling(aqw), which won the 2013 parallel track.</a>
<a href="#9" id="9">We expect that as additional highly parametric SAT solvers become available, parHydra will produce even stronger parallel portfolios.</a>
<a href="#10" id="10">In future work, it would be interesting to investigate how information exchange strategies such as clause sharing can be integrated more deeply into our procedures.</a>
<a href="#11" id="11">This could be done, e.g., by combining our ACPP approach with HordeSAT[9], a modular, massively parallel SAT solver with clause sharing that can make use of arbitrary CDCL solvers.</a>
<a href="#12" id="12">Since parameters governing such information exchange are global (rather than restricted to an individual component solver), we also intend to investigate improved methods for handling global portfolio parameters.</a>
<a href="#13" id="13">Finally, we plan to investigate ways of reusing previously-trained portfolios for building new ones, for instance, in cases where the instance set changes slightly or new solvers become available.</a>
</body>
</html>