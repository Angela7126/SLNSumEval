<html>
<head>
<meta name="TextLength" content="SENT_NUM:20, WORD_NUM:623">
</head>
<body bgcolor="white">
<a href="#0" id="0">We derived several properties of propagation complete formulas and empowering implicates.</a>
<a href="#1" id="1">Let us now recollect the answers to the four questions we posed in the introduction.</a>
<a href="#2" id="2">We showed that given a clause C, the problem of deciding whether C is an empowering implicate of a CNF formula φ is co-NP complete.</a>
<a href="#3" id="3">This result comes as no big surprise as the hard part of this decision is answering the question whether C is even an implicate of φ and the new information brought here is that restricting the attention to the subset of empowering implicates does not make this problem easier.</a>
<a href="#4" id="4">On the other hand, if there is an empowering implicate of φ, there is always a 1-provable empowering implicate of φ as stated in Theorem 4.2 which follows from Proposition 2 of [15].</a>
<a href="#5" id="5">It means that in this case there is always a clause for which it is easy to show that it is an implicate of φ simply by unit propagation.</a>
<a href="#6" id="6">Extending this reasoning further, we can even find an empowering implicate C, such that it can be derived by a series of resolutions of linear length with respect to the number of literals occurring in a given formula (Proposition 4.3 which relates to Proposition 4 of [15] and other results in [33], [34], [35]).</a>
<a href="#7" id="7">We also showed that this bound is tight, in some cases linear length of resolution proof is necessary.</a>
<a href="#8" id="8">It is important that in this case we consider a general implicate C since we also showed that if we want to derive a prime empowering implicate C, an exponential length of resolution proof might be necessary.</a>
<a href="#9" id="9">We showed that the problem in which we ask whether there is an empowering implicate for given CNF formula φ is NP-complete, which means that checking whether given CNF formula φ is propagation complete is co-NP complete.</a>
<a href="#10" id="10">Note that this strenghtens the results of [9] where the authors showed that the decision problem whether φ has an empowering implicate belongs to {a mathematical formula}Σ2p.</a>
<a href="#11" id="11">At a first sight we might see a slight contrast between the fact that checking whether given clause C is an empowering implicate of given CNF formula φ is co-NP complete while checking whether there exists an empowering implicate for a given CNF formula φ is NP-complete.</a>
<a href="#12" id="12">The difference is that in the former problem we are given a particular clause C and it is already co-NP complete to decide whether C is an implicate of φ checking the empowering property is then easy.</a>
<a href="#13" id="13">In the latter case we are given only a CNF formula φ and thus we may look for special empowering implicates, in particular the 1-provable ones.</a>
<a href="#14" id="14">Checking whether a given clause C is 1-provable empowering implicate of φ is then polynomial and the hard part is to find one.</a>
<a href="#15" id="15">Finally, we showed that there is a uniform and size increasing family of CNF formulas such that given CNF formula φ from this family we have to add an exponential number of empowering implicates to make it propagation complete.</a>
<a href="#16" id="16">This result strenghtens a quasi-polynomial bound which follows from the results of [21] and the connection between CNF decompositions of domain consistency propagators in CSP.It remains an interesting question whether a similar result can be obtained for different representations of propositional formulas, such as ZBDD (zero-suppressed binary decision diagrams [43], [44], see e.g. [45] for use in propositional formula representation).</a>
<a href="#17" id="17">In particular it may be interesting to investigate, whether the family of formulas defined in Theorem 5.8 requires an exponentially sized ZBDD to represent its propagation complete counterpart.</a>
<a href="#18" id="18">We leave this question for further research.</a>
<a href="#19" id="19">We can consider other representations as well, see e.g. [17] for a comprehensive list of various representations used in knowledge compilation.</a>
</body>
</html>