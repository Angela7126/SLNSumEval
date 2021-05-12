<html>
<head>
<meta name="TextLength" content="SENT_NUM:16, WORD_NUM:409">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have introduced a model-theoretic notion of inseparability for description logic TBoxes, analysed the complexity of deciding inseparability in various cases, and explored several forms of modules based on inseparability.</a>
<a href="#1" id="1">This has led to module extraction algorithms for acyclic {a mathematical formula}ALCI-TBoxes and acyclic {a mathematical formula}ELI-TBoxes.</a>
<a href="#2" id="2">Experiments for the {a mathematical formula}ELI-case show that our algorithm often extracts modules of significantly smaller size than other state-of-the-art techniques, and that our algorithms scale very well to large TBoxes such as SNOMED CT.</a>
<a href="#3" id="3">There are two main conclusions one can draw from this investigation: firstly, deciding model-theoretic inseparability for DLs that contain {a mathematical formula}ALC is undecidable or of very high computational complexity, even for acyclic TBoxes and even if one TBox is empty.</a>
<a href="#4" id="4">For such expressive DLs, practical tools for checking inseparability and extracting modules should thus be based on approximations of model-theoretic inseparability.</a>
<a href="#5" id="5">One important known methodology for approximations is based on locality.</a>
<a href="#6" id="6">The results in this paper suggest to consider, in addition, approximations based on syntactic dependencies.</a>
<a href="#7" id="7">Secondly, for the description logics {a mathematical formula}EL and its extension {a mathematical formula}ELI, model-theoretic inseparability becomes tractable in important cases and can be deployed in practical applications without resorting to approximations.</a>
<a href="#8" id="8">In addition, the tractability results for checking inseparability of {a mathematical formula}ELI-TBoxes from the empty TBox show that the complexity of standard reasoning (subsumption) can be significantly higher than the complexity of model-theoretic inseparability.</a>
<a href="#9" id="9">As future research, it would be interesting to fill the gaps in Table 1 by determining the decidability/complexity of inseparability of acyclic {a mathematical formula}ELand {a mathematical formula}ELI-TBoxes in the general case.</a>
<a href="#10" id="10">From an application perspective, it would also be relevant to study inseparability of acyclic TBoxes formulated in mild extensions of {a mathematical formula}ELand {a mathematical formula}ELI-TBoxes, such as with role inclusions, transitive roles, range restrictions, and nominals.</a>
<a href="#11" id="11">In addition, it is of interest to investigate model-theoretic inseparability for DL-Lite dialects introduced in [67] and for which inseparability has not been investigated in [14].</a>
<a href="#12" id="12">Examples include {a mathematical formula}DL-Litecore and {a mathematical formula}DL-Litecore with role inclusions.</a>
<a href="#13" id="13">From a practical viewpoint, it would be interesting to implement the module extraction algorithm for acyclic {a mathematical formula}ALCI-TBoxes.</a>
<a href="#14" id="14">We are optimistic that the straightforward implementation using off-the-shelf QBF solvers can be applied to large-scale acyclic non-{a mathematical formula}ELI-TBoxes such as the NCI thesaurus.</a>
<a href="#15" id="15">A further extension to practical minimal module extraction with mild syntactic restrictions seems to be in reach even for acyclic {a mathematical formula}SHIQ-TBoxes.</a>
</body>
</html>