<html>
<head>
<meta name="TextLength" content="SENT_NUM:23, WORD_NUM:556">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we have provided an analysis of disclosure of source data in ontology-based integration.</a>
<a href="#1" id="1">For indistinguishability, we have been able to prove tractability in data complexity for standard OBDA.</a>
<a href="#2" id="2">In the case of compliance problems, we have still obtained very general decidability results; however, achieving tractability for standard OBDA requires additional restrictions on both the mappings and the policy.</a>
<a href="#3" id="3">Finally, we have shown that instance-independent compliance is decidable for the important case of CQ view mappings and empty ontology, but becomes undecidable as soon as this setting is slightly generalised.</a>
<a href="#4" id="4">As shown in Section 8, our results provide some significant modifications of the complexity landscape outlined in prior work.</a>
<a href="#5" id="5">Our results lead to a number of directions for future research.</a>
<a href="#6" id="6">From a theoretical perspective, it would be interesting to address the problems mentioned next.</a>
<a href="#7" id="7">The decidability (and complexity) of {an inline-figure} for LAV mappings, which was left open in Section 7.</a>
<a href="#8" id="8">The computational properties of {an inline-figure}, which remain completely unexplored.</a>
<a href="#9" id="9">Databases are typically equipped with different types of integrity constraints such as primary and foreign keys, which may provide valuable additional information to an attacker.</a>
<a href="#10" id="10">We believe that most of our decidability results extend to the setting where source constraints are allowed.</a>
<a href="#11" id="11">It would be interesting to confirm this hypothesis and study the impact of source constraints on the complexity of our reasoning problems (by this, extending the results of Chirkova and Yu [26]).</a>
<a href="#12" id="12">Our notion of compliance does not limit the computational resources of the attacker.</a>
<a href="#13" id="13">Although Lemma 3 shows that the attacker can always make due with polynomially many queries, our lower bounds can be seen as showing that it may be hard in general for an attacker to determine if the policy holds.</a>
<a href="#14" id="14">Thus, a main open issue is to distinguish the combinations of schemata and queries that are computationally easy for an attacker from those that are hard (as the data varies).</a>
<a href="#15" id="15">Lutz et al. in [60] and [61] performed a similar kind of analysis for hybrid closed-and-open world query answering, and their techniques may be directly relevant.</a>
<a href="#16" id="16">From a practical perspective, we see our complexity bounds for source indistinguishability and (strong) compliance in the setting of standard OBDA as rather favourable.</a>
<a href="#17" id="17">In particular, source indistinguishability has {an inline-figure} data complexity and, if we assume mappings to be LAV, it is also tractable in combined complexity; in turn, compliance and strong compliance both have {an inline-figure} data complexity under the assumption that mappings are LAV and the policy is ground.</a>
<a href="#18" id="18">We believe that these are all reasonable assumptions in practice, and we are planning to develop and implement practical, rewriting-based, compliance checking algorithms for the aforementioned cases.</a>
<a href="#19" id="19">In contrast, our bounds for the compliance problem in more general settings (and especially the intractability results in data complexity), paint a rather pessimistic picture.</a>
<a href="#20" id="20">We conjecture that for source databases arising in practice, the data can be abstracted—for example, by grouping values with similar types—in such a way that the abstraction is orders of magnitude smaller than the source data, while compliance results about the source can be inferred from compliance results about the abstraction.</a>
<a href="#21" id="21">We believe that criteria for a sound abstraction technique can be extracted from the critical instance technique described in Section 7.</a>
<a href="#22" id="22">We will investigate this technique both from a practical and theoretical perspective in the future.</a>
</body>
</html>