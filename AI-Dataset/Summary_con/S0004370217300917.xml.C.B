<html>
<head>
<meta name="TextLength" content="SENT_NUM:17, WORD_NUM:383">
</head>
<body bgcolor="white">
<a href="#0" id="0">The three-valued formalism of MKNF proposed in [9] is elegant, but it involves complex notations.</a>
<a href="#1" id="1">The first part of this paper is an attempt to clarify the challenges in formulating a well-founded semantics for hybrid MKNF knowledge bases as introduced in [9].</a>
<a href="#2" id="2">Interestingly, though this paper serves as an erratum in this sense, it actually confirms the validity of the approach to the well-founded semantics – it does work, but only for a proper subset of the claimed knowledge bases.</a>
<a href="#3" id="3">The notational burdens in dealing with three-valued MKNF models prompted us to seek intuitive ways to represent three-valued MKNF models, and for this we formulated the notion of stable partitions.</a>
<a href="#4" id="4">We then showed a one-to-one correspondence between stable partitions and three-valued MKNF models.</a>
<a href="#5" id="5">A key idea in developing the well-founded semantics in [9] is to apply the alternating fixpoint construction.</a>
<a href="#6" id="6">In this paper we have shown that, in addition to computing well-founded MKNF models, alternating fixpoint construction can also serve as a constraint propagator to verify the stability of an arbitrary partition.</a>
<a href="#7" id="7">In this way, we obtained a precise relationship between three-valued MKNF models and alternating fixpoints.</a>
<a href="#8" id="8">Our results on stable partitions shed light on how to devise a DPLL-style solver for semantics based on two-valued MKNF models.</a>
<a href="#9" id="9">Recall that a fundamental idea in a DPLL-based solver is a search engine that propagates a partial assignment at each decision point, to prune the search space [14].</a>
<a href="#10" id="10">This is in contrast with the state-of-the-art reasoning method for hybrid MKNF knowledge bases, which is based on a guess-and-verify approach.</a>
<a href="#11" id="11">Two of the most familiar constraint propagators are Unit Propagation in Boolean Satisfiability (SAT) [14] and the Expand function in answer set solvers [17].</a>
<a href="#12" id="12">A critical question for a DPLL-style solver for hybrid MKNF knowledge bases is what constitutes constraint propagation for reasoning with such knowledge bases.</a>
<a href="#13" id="13">Our work on partial partitions shows that the alternating fixpoint construction may serve this role; it can be used to expand partial partitions and check whether a partial partition is stable.</a>
<a href="#14" id="14">Thus useful properties may be explored.</a>
<a href="#15" id="15">If the DL component is tractable, alternating fixpoints can be computed in polynomial time hence an efficient implementation is possible.</a>
<a href="#16" id="16">A successful formulation of such a solver and its implementation enhanced by conflict-directed clause learning constitutes an interesting direction for future research.</a>
</body>
</html>