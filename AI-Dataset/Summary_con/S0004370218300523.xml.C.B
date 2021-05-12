<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:573">
</head>
<body bgcolor="white">
<a href="#0" id="0">A growing number of inconsistency measures have been proposed so far.</a>
<a href="#1" id="1">Most measures satisfy some properties that are considered intuitive and rational within their own contexts.</a>
<a href="#2" id="2">In this sense, such measures have provided some characterizations of the inconsistency for a knowledge base from their own perspectives.</a>
<a href="#3" id="3">However, we are more interested in incorporating inconsistency measures in the whole process of inconsistency resolving in many practical applications.</a>
<a href="#4" id="4">To this purpose, establishing a meaningful linkage between inconsistency measures and actions needed to render a knowledge base consistent is more necessary.</a>
<a href="#5" id="5">Causality can be considered as a promising starting point to establish such a linkage.</a>
<a href="#6" id="6">Generally, from the point of view of inconsistency resolving, only formulas causing the inconsistency of a knowledge base should be involved in actions for restoring the consistency of that base.</a>
<a href="#7" id="7">That is, only causes of the inconsistency are of interest when we choose formulas that need to be changed in order to resolve the inconsistency.</a>
<a href="#8" id="8">From the perspective of inconsistency measuring, inconsistency measures based on counterfactual dependence (under some contingency) allow us to better understand the nature of inconsistency at both base-level and formula-level from the perspective of causality.</a>
<a href="#9" id="9">Then causality-based explanations of inconsistency measures make them more applicable in the practical application domains.</a>
<a href="#10" id="10">Our previous measures presented in [21] have made the first attempt to introduce the causality in measuring inconsistency.</a>
<a href="#11" id="11">On the other hand, constraints specify some conditions for acceptable actions for restoring the consistency of a knowledge base in practical applications.</a>
<a href="#12" id="12">Then a useful linkage between inconsistency measures and inconsistency resolving should take into account the role of constraints in practical inconsistency resolving.</a>
<a href="#13" id="13">We made an attempt to extend causality-based measures to the case with constraints so as to establish more practical linkage between inconsistency measures and inconsistency resolving in this paper.</a>
<a href="#14" id="14">The graph-based approach to measuring the inconsistency for a knowledge base with one or both of the two typical kinds of constraints has been proposed.</a>
<a href="#15" id="15">Given an inconsistent knowledge base with a constraint, the MIS-graph is constructed to represent the set of minimal inconsistent subsets of that base from multiple perspectives.</a>
<a href="#16" id="16">In particular, the one-to-one correspondence between minimal correction subsets and minimal Y-dominating sets of the MIS-graph allows us to incorporate constraints on modifying formulas in such a graph-based characterization of inconsistency in a concise way.</a>
<a href="#17" id="17">Based on this incorporation, then the degree of inconsistency of a knowledge base with the constraint is defined as the minimum cardinality of minimal Y-dominating sets compatible with the constraint, moreover, it is interpreted as the minimum size of sets of formulas which the inconsistency counterfactually depends on in the presence of the constraint from a perspective of causality.</a>
<a href="#18" id="18">At the level of formulas, if a formula is subsumed in a minimal Y-dominating set of the MIS-graph that is compatible with the constraint, then the degree of responsibility of that formula for the inconsistency in the presence of the constraint is defined as the reciprocal of the minimum cardinality of compatible minimal Y-dominating sets with the constraint that contain the formula, otherwise, it is defined as 0.</a>
<a href="#19" id="19">All these measures for inconsistency with constraints can be well explained in the framework of Halpern–Pearl's causal model and Chockler and Halpern's notion of responsibility.</a>
<a href="#20" id="20">This causality-based interpretation makes the inconsistency measure more comprehensible and applicable to the practical application domains.</a>
<a href="#21" id="21">Lastly, some interesting logical properties of these inconsistency measures, especially about monotony or antimonotony with regard to constraints, have been also studied.</a>
</body>
</html>