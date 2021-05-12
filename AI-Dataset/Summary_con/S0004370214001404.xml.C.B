<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:351">
</head>
<body bgcolor="white">
<a href="#0" id="0">The aim of this article was to provide the reader with a basic understanding of the different techniques used to implement the paradigm of abstract argumentation.</a>
<a href="#1" id="1">We have grouped these techniques into two categories.</a>
<a href="#2" id="2">The reduction-based techniques aim at transforming the argumentation problem at hand into an instance of a different problem (SAT, ASP, etc.</a>
<a href="#3" id="3">), thereby delegating the burden of computation to existing systems.</a>
<a href="#4" id="4">On the other hand, the category of direct approaches refers to systems and methods implementing abstract argumentation “from scratch”, thus allowing for tailored algorithms which explicitly realize argumentation specific optimizations.</a>
<a href="#5" id="5">The strengths of reduction-based systems are that they (i) directly scale with newer versions of solvers and (ii) can be easily adapted to specific needs, which is mirrored by a quite flexible support of reasoning problems and argumentation semantics.</a>
<a href="#6" id="6">Ultimately, dedicated direct algorithms (when tuned sufficiently) outperform reduction-based ones (see e.g. [36]), but each reasoning problem and semantics needs its own full-fledged implementation.</a>
<a href="#7" id="7">In conclusion, this suggests that the reduction-based approach provides a good basis for rapid prototyping, while systems that have to scale well for large problems require substantial design efforts.</a>
<a href="#8" id="8">However, the two categories are not as strictly separated as it might look like.</a>
<a href="#9" id="9">For instance, the CEGARTIX approach as introduced in Section 3.1.3 is an example for a system that combines the advantages of the two categories.</a>
<a href="#10" id="10">It is based on a dedicated algorithm for the argumentation problem at hand, but as a subroutine invokes existing systems (i.e., SAT solvers).</a>
<a href="#11" id="11">Systems that combine these approaches are among the fastest systems, in particular significantly faster than pure reduction-based approaches and still directly benefit from improvements in the solvers.</a>
<a href="#12" id="12">However, by this hybrid approach one loses the flexibility of pure reduction-based systems.</a>
<a href="#13" id="13">The current landscape of systems is very heterogeneous (see Section 5).</a>
<a href="#14" id="14">Available systems for argumentation differ in their support for semantics and reasoning problems, summarized in Table 4.</a>
<a href="#15" id="15">Each tool has its unique strengths and characteristics, be it graphical representation of algorithms or results, efficient solving in some setting, or providing broad support for problems to be solved in the context of argumentation.</a>
</body>
</html>