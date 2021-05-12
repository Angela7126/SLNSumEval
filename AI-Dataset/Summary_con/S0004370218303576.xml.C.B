<html>
<head>
<meta name="TextLength" content="SENT_NUM:22, WORD_NUM:519">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper, we investigated why a preferred labelling may not be stable.</a>
<a href="#1" id="1">Our contributions can be summarised as follows:</a>
<a href="#2" id="2">We gave three labelling-based and three structural characterisations of sets of undec arguments deemed responsible that a given preferred labelling is not a stable labelling.</a>
<a href="#3" id="3">We proved that our characterised sets of arguments are indeed responsible by examining the effect of enforcing the label in or out for responsible arguments in these sets through some structural revision.</a>
<a href="#4" id="4">In particular:</a>
<a href="#5" id="5">The stable iterative SCUP revision can be used to constructively obtain a stable labelling (of a revision) from a given preferred labelling (of the original AF).</a>
<a href="#6" id="6">Our characterisations also explain the non-existence of stable labellings, in the sense that they characterise for each preferred labelling why it is not a stable labelling.</a>
<a href="#7" id="7">We compared our labelling-based and structural characterisations, proving that SCUPs provide a constructive approximation of our precise labelling-based characterisations.</a>
<a href="#8" id="8">Furthermore, our comparison shows that odd-length cycles are an important feature of all our characterisations.</a>
<a href="#9" id="9">One of our results states that a SCUP revision has a preferred labelling that is more (or equally) committed than the chosen preferred labelling of the original AF.</a>
<a href="#10" id="10">We did, however, not discuss how to obtain such a preferred labelling.</a>
<a href="#11" id="11">The naïve approach is to compute all preferred labellings of the SCUP revision, compare them to the SCUP revision labelling, and choose a preferred labelling that is more or equally committed than the SCUP revision labelling.</a>
<a href="#12" id="12">There exists a large variety of computational tools to solve this task, see [50] for an overview.</a>
<a href="#13" id="13">Another possibility is to use a slight modification of the algorithm by Cerutti et al. [51] for computing preferred labellings through an iterative procedure that splits the AF into different parts.</a>
<a href="#14" id="14">Future work includes studying the complexity and developing a tool for finding our different notions of responsible sets of arguments and revising the AF based on these sets combined with the user's choice of labels (e.g. of arguments in a SCUP).</a>
<a href="#15" id="15">Furthermore, we plan to investigate how different revision operators from the literature (e.g. [44], [45], [46], [43]) can be combined with our characterisations.</a>
<a href="#16" id="16">Various authors have shown that there is a semantic correspondence between logic programs and AFs that encode the same information as the logic program [10], [52], [53].</a>
<a href="#17" id="17">It follows from these results that if a logic program has no stable models, the encoding AF has no stable labellings.</a>
<a href="#18" id="18">A future direction of research is thus to study whether our notions of responsible sets and revisions based on these sets can be carried over to logic programs, and how they relate to existing work on the inconsistency and debugging of logic programs, e.g. [54], [55], [56], [57], [58], [59], [60], [61].</a>
<a href="#19" id="19">We here only considered semantics that assign one of three labels to arguments.</a>
<a href="#20" id="20">Other types of semantics for AFs rank arguments or assign a numerical value to each argument, e.g. [62], [63], [64], [65], [66], [67], [68], [69].</a>
<a href="#21" id="21">It will be interesting to investigate if there is any connection between our responsible sets of arguments and their numerical value or rank according to these different semantics.</a>
</body>
</html>