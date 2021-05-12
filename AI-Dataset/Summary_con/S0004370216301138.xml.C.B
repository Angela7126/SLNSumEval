<html>
<head>
<meta name="TextLength" content="SENT_NUM:13, WORD_NUM:360">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this article, we have described the design of the Configurable SAT Solver Challenge (CSSC) and the details of CSSC 2013 and CSSC 2014.</a>
<a href="#1" id="1">We have highlighted two main insights that we gained from this competition:</a>
<a href="#2" id="2">Automated algorithm configuration often improved performance substantially, in several cases yielding average speedups of orders of magnitude.</a>
<a href="#3" id="3">Some solvers benefited more from automated configuration than others, leading to substantially different algorithm rankings after configuration than before (as, e.g., measured by the SAT competition).</a>
<a href="#4" id="4">Also, the configuration budget influenced which algorithm would perform best, and with the competition budget of 2 days on 4–5 cores, algorithms with larger parameter spaces exhibited more capacity for improvement.</a>
<a href="#5" id="5">These conclusions have interesting implications for algorithm design: if an algorithm is likely to be applied across a range of specialized applications, then it should be made flexible by parameterization of its key mechanisms and components, and this flexibility should be exploited by automated algorithm configuration.</a>
<a href="#6" id="6">Our findings thus challenge the traditional approach to solver design that tries to avoid having too many algorithm parameters (since these parameters complicate manual tuning and analysis).</a>
<a href="#7" id="7">Rather, they promote the design paradigm of Programming by Optimization (PbO)[41], which aims to avoid premature design choices and to rather actively develop promising alternatives for parts of the design that enable an automated customization to achieve peak performance on particular benchmarks of interest.</a>
<a href="#8" id="8">Indeed, in the CSSC, we have already observed a trend towards PbO, as evidenced by the introduction of a host of new parameters into state-of-the-art solvers, such as Riss-4.27 and Lingeling, between 2013 and 2014.</a>
<a href="#9" id="9">Finally, there is no reason why a configurable solver competition should be appropriate and insightful only for SAT.</a>
<a href="#10" id="10">On the contrary, similar events would be interesting in the context of many other challenging computational problems, such as answer set programming, constraint programming or AI planning.</a>
<a href="#11" id="11">Another interesting application domain is automatic machine learning, where algorithm configuration can adapt flexible machine learning frameworks to each new dataset at hand [80], [32].</a>
<a href="#12" id="12">We believe that for those and many other problems, similar findings to those we reported here for CSSC would be obtained, leading to analogous conclusions regarding algorithm design.</a>
</body>
</html>