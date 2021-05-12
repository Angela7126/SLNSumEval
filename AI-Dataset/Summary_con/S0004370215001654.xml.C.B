<html>
<head>
<meta name="TextLength" content="SENT_NUM:33, WORD_NUM:846">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we presented an approach to addressing the issue of real time approximate reasoning in expressive DL {a mathematical formula}SROIQ, the logic underpinning OWL 2 DL.</a>
<a href="#1" id="1">Although our approach does not produce an optimal approximation like semantic approximation [61], which is expensive to compute, it is soundness preserving, tractable (in PTime) and produces very high recalls, evidenced by our evaluations on benchmark and real-world ontologies.</a>
<a href="#2" id="2">The proposed approach consists of two parts.</a>
<a href="#3" id="3">The first part is a transformation from an {a mathematical formula}SROIQ ontology to an {a mathematical formula}EL++ ontology plus a complement table (CT) maintaining the complementary relations between predicates, a cardinality table (QT) maintaining cardinality information and a inverse table (IT) maintaining inverse relations.</a>
<a href="#4" id="4">Such a transformation can be performed on TBox alone (Definition 4), or on both TBox and ABox (Definition 8).</a>
<a href="#5" id="5">The result is essentially a syntactic variant of the original TBox or ontology that preserves all reasoning results, as we have shown in Theorem 2 and Theorem 8.</a>
<a href="#6" id="6">Therefore this part can be regarded as a normalisation or structural transformation procedure.</a>
<a href="#7" id="7">The second part of our approach is a set of TBox approximate deduction rules and several more and more optimised ABox approximate deduction procedures with more and more fine-grained completion rules.</a>
<a href="#8" id="8">The purpose of these rule sets is to approximate a fully-fledged {a mathematical formula}SROIQ materialisation procedure by considering only the interactions between axiom patterns that can be addressed in polynomial time.</a>
<a href="#9" id="9">We show that the optimised ABox reasoning procedures can improve efficiency without losing results compared to the internalisation procedure (Theorem 12, Theorem 14 and Theorem 15) when certain syntactic requirements are met.</a>
<a href="#10" id="10">Particularly, we extend the notion of {a mathematical formula}EL++ nominal-safety (as described in Definition 6, Definition 7 and Theorem 6) to facilitate the optimisation of combined TBox and ABox materialisation with nominals.</a>
<a href="#11" id="11">Our approach is different from many other approximation approaches in a sense that instead of weakening an ontology in a more expressive language {a mathematical formula}L1 into a less expressive language {a mathematical formula}L2 so that it can be reasoned with by a fully-fledged reasoner of {a mathematical formula}L2, we are actually weakening the reasoning procedure of {a mathematical formula}L1, granted that this weaker procedure is obtained by extending the reasoning procedure of {a mathematical formula}L2.</a>
<a href="#12" id="12">To facilitate such an approximate deduction procedure between those of {a mathematical formula}L1 and {a mathematical formula}L2, we transform the ontology into {a mathematical formula}L2-like forms.</a>
<a href="#13" id="13">Nevertheless, such a transformation is purely syntactic and the approximate deduction are actually performed on {a mathematical formula}L1 axioms.</a>
<a href="#14" id="14">In fact, it is possible to rewrite the rules so that they can be directly used to materialise {a mathematical formula}SROIQ ontologies.</a>
<a href="#15" id="15">An important consequence of the above characteristic that distinguishes our approach from the other tractable reasoning solutions is that the tractability is not achieved by restricting the syntax of the ontology, but rather the possible interactions between axioms.</a>
<a href="#16" id="16">Therefore it allows users to construct ontologies with more expressive constructors as they see appropriate but still enjoy the tractable reasoning service with high quality, especially when the expressive constructors in these ontologies only interact with each other in reasoning in limited manners.</a>
<a href="#17" id="17">From our evaluation it can be seen that many real-world ontologies, despite being in very complex DLs, are actually created in this way hence our approach can offer highly efficient reasoning with very high recalls.</a>
<a href="#18" id="18">By further restricting the interactions between different DL features to avoid intractability, it is even possible to devise partial completeness guarantee for our approach (Theorem 17).</a>
<a href="#19" id="19">Recall that in the introduction we discussed three categories of approaches to ontology reasoning, namely fully-fledged algorithms for expressive DLs, dedicated algorithms for light-weight DLs and approximation-based approaches.</a>
<a href="#20" id="20">Our work belongs to the third category.</a>
<a href="#21" id="21">In the future we would like to further explore its implication on the other two categories.</a>
<a href="#22" id="22">Particularly:</a>
<a href="#23" id="23">Our work approximates a fully-fledged reasoning procedure of {a mathematical formula}SROIQ with a completion-based algorithm.</a>
<a href="#24" id="24">It is interesting to extend on the current rule set to develop an actual fully-fledged completion-based algorithm for {a mathematical formula}SROIQ by introducing certain intractable rules, e.g. the ones examined in Sec.</a>
<a href="#25" id="25">8.2.</a>
<a href="#26" id="26">Following the result of Theorem 17, another interesting research topic is to establish a maximal completeness guarantee for our approach.</a>
<a href="#27" id="27">In other words, we would like to identify a set of conditions such that when an ontology satisfies these conditions, our approach is guaranteed to provide complete materialisation results.</a>
<a href="#28" id="28">The discovery of such conditions essentially means the development of a new tractable DL.</a>
<a href="#29" id="29">Despite their relevance to the work presented in the current paper, they are exploring either an intractable algorithm, or a new stand-alone tractable DL.</a>
<a href="#30" id="30">Hence they are not within the scope of the current paper and should be investigated as their own tracks of work.</a>
<a href="#31" id="31">Last but not least, we would like to adopt the idea of parallel reasoning presented by Kazakov et al. [42] in our approach so that efficiency can be further improved.</a>
<a href="#32" id="32">In this work, the new research challenge is to formulate the rules in ways that parallelisation can be achieved.</a>
</body>
</html>