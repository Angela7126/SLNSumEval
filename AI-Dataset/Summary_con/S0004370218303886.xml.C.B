<html>
<head>
<meta name="TextLength" content="SENT_NUM:28, WORD_NUM:606">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we motivated and studied (the use of) second-order propositional modal logic as a specification language for reasoning about knowledge as well as spatial and temporal properties in artificial intelligence.</a>
<a href="#1" id="1">Specifically, we aimed at developing proofand model-theoretic techniques, notably complete axiomatisations and truth-preserving (bi)simulations, to support the use of sopml in applications.</a>
<a href="#2" id="2">In Section 2 we introduced 20 different classes of Kripke frames, according to the structure of the domain D of quantification and the features of the accessibility relations.</a>
<a href="#3" id="3">In Section 4 we provided complete axiomatisations for some of these classes, while proving that other classes are unaxiomatisable.</a>
<a href="#4" id="4">Further, we introduced suitable notions of (bi)simulation and proved that they preserve the satisfaction of (universal) sopml.</a>
<a href="#5" id="5">Finally, we made use of (bi)simulations to obtain some inexpressibility results.</a>
<a href="#6" id="6">Specifically, we showed that being finite and having a Hamiltonian path are not expressible in sopml, while other properties, viz.</a>
<a href="#7" id="7">topological completeness and 3-colorability, are indeed expressible.</a>
<a href="#8" id="8">We conclude that sopml can indeed be used as a modelling language for artificial intelligence, particularly for temporal and spatial reasoning, as well as to describe higher-level knowledge of agents, that is, the knowledge agents have about other agents' knowledge and beliefs, as shown in Section 3.</a>
<a href="#9" id="9">In this respect, we reckon that the development of model-theoretic techniques is key for applications.</a>
<a href="#10" id="10">We have presented several results about sopml, but there are of course also a number of remaining questions for future research.</a>
<a href="#11" id="11">One such question is the relative expressivity of sopml and QCTL.</a>
<a href="#12" id="12">As mentioned in Section 1.1, the variant of sopml with full domain of quantification is similar to one of the variants of QCTL presented in [41], with the main difference being that QCTL is based on ctl, while sopml is based on basic modal logic.</a>
<a href="#13" id="13">The temporal logic ctl has more operators than modal logic, and it is strictly more expressive.</a>
<a href="#14" id="14">It is not currently clear whether QCTL is also strictly more expressive than sopml, however.</a>
<a href="#15" id="15">Another direction for future research is to find fragments of sopml that are “well-behaved”.</a>
<a href="#16" id="16">As discussed in Section 4, most of sopml variants are unaxiomatisable on full frames, and variants that include the reachability operator {a mathematical formula}□⁎ are unaxiomatisable even on frames with coarser domains of quantification.</a>
<a href="#17" id="17">It would be interesting to find fragments of sopml that are large enough to be interesting, but that are axiomatisable or even decidable.</a>
<a href="#18" id="18">In this respect the monodic fragment of first-order modal logic, that restrict the number of free varibles in the scope of any modal operator, looks promising [2], [29], [53].</a>
<a href="#19" id="19">We leave this direction for future work.</a>
<a href="#20" id="20">At the end of Section 5 we mentioned the interest of checking whether sopml is the bisimulation-invariant fragment of MSO, according to the newly introduced notion of bisimulation.</a>
<a href="#21" id="21">Such a result would provide us with a precise characterisation of the expressive power of sopml (with respect to MSO), in the spirit of van Benthem's result for modal logic [6].</a>
<a href="#22" id="22">It would also be of interest to define games in the style of Ehrenfeucht-Fraïssé to have a more fine-grained approach to the analysis of the expressivity of sopml, similarly to the case for first-order and modal logic [34].</a>
<a href="#23" id="23">Finally, here we considered a unique domain D of quantification in any of our frames.</a>
<a href="#24" id="24">But more elaborate forms of quantification can be taken into account, for instance, we might consider a different quantification domain for each state in the frame.</a>
<a href="#25" id="25">Then, we might also consider state-dependent assignments.</a>
<a href="#26" id="26">These variants have been studied extensively in the realm of first-order modal logic [10], [24], but never addressed in sopml.</a>
<a href="#27" id="27">They might be of interest for specific applications.</a>
</body>
</html>