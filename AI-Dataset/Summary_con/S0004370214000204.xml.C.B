<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:520">
</head>
<body bgcolor="white">
<a href="#0" id="0">Tasks related to computing with minimal models are relevant to several AI applications.</a>
<a href="#1" id="1">The focus of this paper has been devising efficient algorithms to deal with minimal models of CNF theories.</a>
<a href="#2" id="2">In particular, mainly three problems have been considered, that are, minimal model checking, minimal model finding and model minimization.</a>
<a href="#3" id="3">All these problems prove themselves to be intractable for general CNF theories, while it was known that they become tractable for the class of head-cycle-free theories [5] and, in fact, to the best of our knowledge, positive HCF theories form the largest class of CNFs for which polynomial time algorithms solving minimal model finding and minimal model checking are known so far.</a>
<a href="#4" id="4">The research presented here follows the same research target as that of [5] and the main contribution of this work is that of designing a polynomial time algorithm for computing a minimal model for (a superset of) the class of positive HEF (Head Elementary-Set Free) CNF theories, a strict superset of the class of HCF theories, whose definition naturally stems for the analogous one given in the context of logic programming in [14].</a>
<a href="#5" id="5">This contribution thus broadens the tractability frontier associated with minimal model computation problems.</a>
<a href="#6" id="6">In more detail, we have introduced the Generalized Elimination Algorithm (GEA), that computes a minimal model of any positive CNF, whose complexity depends on the complexity of the specific eliminating operator it invokes.</a>
<a href="#7" id="7">Therefore, in order to attain tractability, a specific eliminating operator has been defined which allows for the algorithm to compute in polynomial time a minimal model for a class of CNF that strictly includes HEF theories.</a>
<a href="#8" id="8">However, it is unfortunately already known that recognizing HEF theories is “per sé” an intractable problem, which may apparently limit the applicability range of our algorithmic schema.</a>
<a href="#9" id="9">In order to overcome such a problem, an “incomplete” variant of the GEA (called IGEA) is proposed: the resulting schema, once instantiated with an appropriate elimination operator, always constructs a model of the input CNF, which is guaranteed to be minimal at least if the input theory is HEF.</a>
<a href="#10" id="10">We note that this latter algorithm is able to “declare” if the returned model is indeed minimal or not.</a>
<a href="#11" id="11">The research work presented here can be continued along some interesting direction.</a>
<a href="#12" id="12">As a major research direction, since the IGEA is capable to deal also with theories that are not HEF, it would be relevant to define, via a syntactic specification, as those pinpointing HCF and HEF theories, a superset HEF theories coinciding with those on which the IGEA stops returning a success.</a>
<a href="#13" id="13">While it is not at all clear if this can be reasonably attained, we might consider it enough to get close (from below) to this class of theories.</a>
<a href="#14" id="14">Very related to the above line of research, there is the assessment of the practical occurrence of theories having the HEF property or the property of guaranteeing success to the IGEA and also the assessment of the success rate of the IGEA on generic CNF theories.</a>
<a href="#15" id="15">Moreover, enhancing stable models and answer set engines for logic programs with the IGEA appears a potentially fruitful line of investigation.</a>
</body>
</html>