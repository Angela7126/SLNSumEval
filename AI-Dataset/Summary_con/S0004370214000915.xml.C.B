<html>
<head>
<meta name="TextLength" content="SENT_NUM:27, WORD_NUM:747">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have considered the problem of inconsistency analysis in nonmonotonic Multi-Context Systems (MCS), which are a flexible, abstract formalism to interlink heterogeneous knowledge sources for information exchange.</a>
<a href="#1" id="1">We have presented a consistency-based and an entailment-based notion of inconsistency explanation, called diagnosis and explanation, which are in a duality relation that can be exploited for computational purposes, and which enjoy modularity properties.</a>
<a href="#2" id="2">We have characterized the computational complexity of the two notions, establishing generic results for a range of context complexities.</a>
<a href="#3" id="3">They show that in many cases, explaining inconsistency does not lead to a jump in complexity compared to inconsistency testing, although (unsurprisingly) depending on the interlinking intractability might arise.</a>
<a href="#4" id="4">We have furthermore shown how the notions can be computed by a transformation to hex programs, which has been implemented in the experimental software tool mcs-ie.</a>
<a href="#5" id="5">Our results provide a basis for building advanced systems of interlinked knowledge sources, in which the natural need for inconsistency management is supported, by taking specifically the information linkage as a source of inconsistency into account, in contrast to traditional works on inconsistency management that focus on the contents of the knowledge sources; however, in loosely connected systems, control over autonomous knowledge sources is elusive and modifying the information exchange may be the only resort to remove inconsistency.</a>
<a href="#6" id="6">The work presented in this article has been continued in several directions.</a>
<a href="#7" id="7">One of them is to impose different kinds of preferences on the notions of diagnosis and explanation that were introduced here, as in [39], [91].</a>
<a href="#8" id="8">They allow for filtering and comparing diagnoses; using meta-programming techniques, the most-preferred ones can be selected from all diagnoses.</a>
<a href="#9" id="9">Another direction concerns incomplete information about contexts.</a>
<a href="#10" id="10">The setting considered in this article assumes complete information about the behavior of the contexts in information exchange, i.e., for each ‘input’ of relevant beliefs from other contexts accessed via bridge rules, the ‘output’ in terms of firing bridge rules is fully known.</a>
<a href="#11" id="11">In real-world applications, however, this information may be only available for specific (classes of) inputs, and querying a context arbitrarily often to gain this knowledge might be infeasible.</a>
<a href="#12" id="12">In such scenarios the notions introduced in [36] allow to obtain reasonable approximations for diagnoses and explanations of inconsistency.</a>
<a href="#13" id="13">Finally, another implementation is currently underway in which diagnoses and explanations can be computed by distributed algorithms, exploiting the distributed MCS evaluation framework of [3], [4], [30].</a>
<a href="#14" id="14">Several issues remain for future work.</a>
<a href="#15" id="15">Building on the notions of preferred diagnosis and explanation, a further topic is to establish concrete inconsistency management procedures for analysis.</a>
<a href="#16" id="16">To this end, a system administrator might ask repeatedly for diagnoses and explanations, considering subsystems and/or a modified interlinkage, and select among the ones presented a most appealing one; the information about past selections may in turn be used to adjust the preferences for calculations.</a>
<a href="#17" id="17">On the computational side, scalability to scenarios with larger data volume and number of bridge rules is desirable, where the intrinsic complexity of our diagnoses and explanations is prohibitive in general.</a>
<a href="#18" id="18">It remains to single out settings where scalability is still possible, and to get a clearer picture of the scalability frontier.</a>
<a href="#19" id="19">This is linked to the complexity of consistency checking for an MCS; restrictions on the interlinking, in numbers and structure (for the latter, see [4]) will be helpful, as well as properties of the context logics (e.g., monotonicity and unique accepted belief sets).</a>
<a href="#20" id="20">Related to this is developing pragmatic variants of our notions, like focusing by protecting bridge rules (which does not increase worst case complexity), giving up properties (e.g., minimality), or by tolerating inconsistency in parts of the system.</a>
<a href="#21" id="21">Another issue is to combine inconsistency management of contents and of context interlinking.</a>
<a href="#22" id="22">Recall that B.2 points out how maximal consistent subsets of a knowledge base (which are ubiquitous in content-based inconsistency management) might be simulated using bridge rules.</a>
<a href="#23" id="23">However, an emerging combination—although in a uniform formalism—would be inflexible and less amenable to refinement.</a>
<a href="#24" id="24">More promising is to combine the notions in this article and in [23], which generalized MCS with a management component for each context and operations to be performed on the knowledge base when a bridge rule fires; this allows for a more sophisticated content-change than simple addition of formulas.</a>
<a href="#25" id="25">Nevertheless, consistency cannot be guaranteed in general with such content-based approaches, as inconsistency caused by cyclic information flow cannot be resolved.</a>
<a href="#26" id="26">Since the latter can be dealt with by modifying the interlinking, as for instance by our notion of diagnosis, a combination of techniques can be successful.</a>
</body>
</html>