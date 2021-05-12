<html>
<head>
<meta name="TextLength" content="SENT_NUM:27, WORD_NUM:650">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have studied the limits of decidability of ontology consistency in fuzzy DLs.</a>
<a href="#1" id="1">On one hand, we have presented several undecidability results that strengthen all previously-known cases of fuzzy DLs with an undecidable consistency problem.</a>
<a href="#2" id="2">To do this, we have developed a general framework for proving undecidability, which is based on a set of relatively simple properties.</a>
<a href="#3" id="3">Using this framework, we were able to show, for instance, that consistency is undecidable in the very simple DL {a mathematical formula}NEL if the semantics are based on a t-norm with zero divisors.</a>
<a href="#4" id="4">Extensions of this framework with different ways to prove the canonical model property also allowed us to prove that the problem is undecidable in {a mathematical formula}{an inline-figure}-ELC and {a mathematical formula}⊗-IEL= for any t-norm different from the Gödel t-norm.</a>
<a href="#5" id="5">All of these logics are equivalent to classical {a mathematical formula}ALC when their semantics is restricted to two truth values.</a>
<a href="#6" id="6">An analysis of these results suggests that the culprit for undecidability of a fuzzy DL is the capacity of expressing specific upper bounds within a non-idempotent component of the t-norm.</a>
<a href="#7" id="7">Indeed, fuzzy GCIs usually provide a lower bound for the interpretation of a concept.</a>
<a href="#8" id="8">If the involutive negation is allowed, then a lower bound for the concept ¬C corresponds to an upper bound for C. Similarly, the implication constructor can be used to propagate upper bounds through concepts, and the residual negation defines a “local” involutive negation in every t-norm that contains zero divisors.</a>
<a href="#9" id="9">Conversely, our proofs of decidability exploit the fact that for any continuous t-norm ⊗ without zero divisors, upper bounds different from 0 cannot be expressed in {a mathematical formula}⊗-SROIQf,≥.</a>
<a href="#10" id="10">If {a mathematical formula}I is a witnessed model of an ontology {a mathematical formula}O, then mapping all the positive truth degrees given by {a mathematical formula}I to 1 yields a crisp model of {a mathematical formula}O (see Lemma 30).</a>
<a href="#11" id="11">If this intuition is correct, then it suggests that for any t-norm without zero divisors, consistency in {a mathematical formula}⊗-NEL= and {a mathematical formula}⊗-NAL= is decidable.</a>
<a href="#12" id="12">Our analysis of the limits of decidability for fuzzy DLs is almost complete.</a>
<a href="#13" id="13">As can be seen from Table 5, there are only a few remaining gaps, which we plan to cover in future work.</a>
<a href="#14" id="14">In this work, we consider mainly standard constructors studied for classical DLs.</a>
<a href="#15" id="15">Other fuzzy constructors like hedges[44], [57], [58], [59], or aggregation operators[60], [61] may require a different analysis.</a>
<a href="#16" id="16">Note also that we have considered here only the ontology consistency problem.</a>
<a href="#17" id="17">The decidability and complexity of other standard reasoning tasks, such as subsumption or instance checking, are other topics for future research.</a>
<a href="#18" id="18">We also intend to find the precise complexity, and optimal algorithms, for reasoning in light-weight fuzzy DLs, such as {a mathematical formula}⊗-EL and {a mathematical formula}⊗-DL-Lite, over arbitrary continuous t-norms ⊗.</a>
<a href="#19" id="19">As has been noted by several authors [13], [14], the ability to manage vague and imprecise knowledge is a desired feature of intelligent systems to be used in the biological and medical domains, among many others.</a>
<a href="#20" id="20">Studying the complexity of reasoning with different fuzzy DLs allows us to discern which of these may be suitable formalisms for implementing a fuzzy knowledge representation and reasoning system.</a>
<a href="#21" id="21">It is clearly desirable to stay in the decidable part of Table 5.</a>
<a href="#22" id="22">However, the decidability results of Section 4 are also not helpful since they show that consistency can be decided using classical reasoners without any modification of the input ontology.</a>
<a href="#23" id="23">This leaves only the Gödel t-norm as a promising candidate for an implementation.</a>
<a href="#24" id="24">As an alternative, one could use many-valued DLs that support only a finite set of truth values, arranged in a residuated lattice or a total order [31], [33], [34], [40], [41].</a>
<a href="#25" id="25">The complexity of reasoning in such logics is often the same as for the underlying classical DLs.</a>
<a href="#26" id="26">Sometimes, highly-optimized reasoners [62], [63] for classical reasoning problems can be reused after a suitable reduction.</a>
</body>
</html>