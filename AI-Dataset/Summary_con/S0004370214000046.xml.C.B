<html>
<head>
<meta name="TextLength" content="SENT_NUM:15, WORD_NUM:370">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we presented a very general framework for consequence-based reasoning in description logics.</a>
<a href="#1" id="1">Then, we introduced a notion of decomposition that allows us to quantify the effects of andand or-branching during reasoning.</a>
<a href="#2" id="2">Finally, we presented what we believe to be the first result on fixed-parameter tractability of description logic reasoning.</a>
<a href="#3" id="3">We see several theoretical and practical challenges for our future work.</a>
<a href="#4" id="4">On the theoretical side, we will try to extend our results to logics with number restrictions and nominals and thus obtain a consequence-based algorithm that can handle all of OWL 2 DL.</a>
<a href="#5" id="5">Number restrictions have already been successfully integrated into resolution-based procedures so, while not trivial, incorporating them into consequence-based algorithms should be possible.</a>
<a href="#6" id="6">We see two main challenges towards that goal.</a>
<a href="#7" id="7">First, we believe that the notion of a context core will have to include two sets of literals (representing the types of an individual and its predecessor in a model) and a set of roles (describing the connections between the two individuals); the reason for this is analogous to why the hypertableau algorithm must use pairwise instead of single blocking [14] when an ontology contains both number restrictions and inverse roles.</a>
<a href="#8" id="8">Second, we believe that our clauses will have to represent disjunctive properties of an individual's successors, which one can likely achieve using a skolemized clausal form as in first-order theorem proving [31].</a>
<a href="#9" id="9">In contrast, the combination of nominals, number restrictions, and inverse roles is a significant source of complexity, and it is currently unclear whether and how this combination of constructs can be handled in a consequence-based framework.</a>
<a href="#10" id="10">On the practical side, our results suggest several significant improvements to existing consequence-based reasoners.</a>
<a href="#11" id="11">First, context reuse may allow reasoners to handle ontologies on which the eager strategy introduces a large number of contexts.</a>
<a href="#12" id="12">Second, redundancy elimination techniques may turn out to further reduce the search space.</a>
<a href="#13" id="13">Third, although computing tree decompositions in advance may incur significant overhead, we believe that computing ϵ-refinements “on demand” for contexts with large widths has the potential to further reduce the number of clauses derived.</a>
<a href="#14" id="14">We will incorporate these ideas into a consequence-based reasoner and try to determine the extent to which they optimize the performance of reasoning in practice.</a>
</body>
</html>