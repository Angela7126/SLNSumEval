<html>
<head>
<meta name="TextLength" content="SENT_NUM:34, WORD_NUM:797">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have considered the issue of repairing DL-programs, which are a well-known loose-coupling combination of nonmonotonic logic rules and Description Logic ontologies, in case of inconsistency, i.e., when no answer set (model) of a DL-program exists.</a>
<a href="#1" id="1">To this end, we have introduced repair answer sets based on repairs, which change the data part (ABox) of the ontology to gain consistency.</a>
<a href="#2" id="2">We have characterized the computational complexity of repair answer sets, showing that they do not add to the complexity of answer sets (more specifically, to weak and flp answer sets) for ontologies in {a mathematical formula}DL-LiteA, which is a prominent Description Logic featuring tractable reasoning.</a>
<a href="#3" id="3">This similarly holds for other tractable Description Logics.</a>
<a href="#4" id="4">Indeed, while we concentrated on {a mathematical formula}DL-LiteA, our general methodology for restoring consistency can be applied to DL-programs over ontologies in a range of Description Logics; we refer the reader to [79] for further discussion.</a>
<a href="#5" id="5">We have provided selection functions to single out preferred repairs from a candidate set, and we have discussed the benign property of independence which allows for local preferred repair selection (filtering).</a>
<a href="#6" id="6">We have then extended an in-use algorithm for DL-program evaluation for computing repair answer sets.</a>
<a href="#7" id="7">At the heart of this extension is a generalized Ontology Repair Problem (ORP), which asks for a modified ABox that simultaneously entails respectively non-entails sets of queries, possibly under individual ABox updates.</a>
<a href="#8" id="8">While intractable in general, we have presented several non-trivial tractable cases, among them deletion repairs, which are often applied in practice.</a>
<a href="#9" id="9">As a naive extension lacks scalability, we developed a new evaluation approach that is based on the novel notion of support set for DL-atoms, and we showed that for DL-programs over {a mathematical formula}DL-LiteA ontologies, a complete support family of such supports sets that allows to completely avoid ontology reasoning during the repair computation can be efficiently constructed.</a>
<a href="#10" id="10">For the experimental evaluation of the approach, we have built a set of benchmarks in different scenarios that involve different ontologies.</a>
<a href="#11" id="11">The experimental results are promising.</a>
<a href="#12" id="12">In particular, for inconsistent DL-programs the repair answer set computation is often faster than standard answer set computation.</a>
<a href="#13" id="13">Furthermore, use-case guided restrictions on repairs often did not introduce much overhead.</a>
<a href="#14" id="14">Overall, the empirical evaluation has revealed a great potential of the novel repair methodology.</a>
<a href="#15" id="15">We can see several directions for future work.</a>
<a href="#16" id="16">One is to consider repair semantics and computation for DL-programs over Description Logics other than {a mathematical formula}DL-LiteA.</a>
<a href="#17" id="17">As mentioned above, for {a mathematical formula}EL this was done in [34], [79], but more expressive DLs can be considered, e.g. the DLs {a mathematical formula}SHIQ, {a mathematical formula}SHOIN, and {a mathematical formula}SROIQ that are important in the Semantic Web context.</a>
<a href="#18" id="18">Orthogonal to other DLs, additional repair possibilities may be considered besides ABox changes.</a>
<a href="#19" id="19">For repairing DL-rules the works on ASP debugging [41], [45], [81] may serve as starting point, but the problem is challenging as the search space of possible changes is large.</a>
<a href="#20" id="20">The latter applies to changes of DL-atoms as well, and in both cases restrictions and/or user interaction will be necessary.</a>
<a href="#21" id="21">Another direction would be to consider other formalisms for hybrid knowledge bases, or more general formalisms than DL-programs for combining knowledge bases such as HEX programs [38].</a>
<a href="#22" id="22">Heterogeneity of external sources in HEX-programs makes both repair and inconsistency-tolerant reasoning very challenging.</a>
<a href="#23" id="23">Regarding optimizations, learning techniques may be exploited for repair computation, e.g. caching of intermediate repairs/repair answer sets, considering correlation patters between them, and identifying mutual dependence of DL-atoms might be worthwhile.</a>
<a href="#24" id="24">Furthermore, program and repair decomposition can be considered, where a DL-program is split into modular components that can be handled separately, and local repairs for them are combined into a global repair.</a>
<a href="#25" id="25">It remains to be seen, however, to what extent and for which program classes the repair methods can be adapted for a modular setting.</a>
<a href="#26" id="26">As regards ABox change, localization and decomposition methods from databases may be exploited [29].</a>
<a href="#27" id="27">Another direction are alternative evaluation approaches.</a>
<a href="#28" id="28">Instead of turning answer sets of the replacement program into repair answer sets by suitable changes of the ontology ABox, one could aim at finding repair answer sets incrementally, e.g., by exploiting debugging based on stepping techniques [68].</a>
<a href="#29" id="29">In a user-interactive mode, one traverses the rules of a DL-program until a conflict is identified.</a>
<a href="#30" id="30">If the latter occurred due to a DL-atom, the ontology ABox is repaired and then the stepping process is continued.</a>
<a href="#31" id="31">While this strategy may not work in general, it can be of interest in restricted settings, e.g. for stratified DL-programs.</a>
<a href="#32" id="32">On the practical side, providing other independent selection functions apart from deletions (see Section 3) is an important issue, along with means to incorporate domain specific information in the repair process (e.g., protected ontology parts).</a>
<a href="#33" id="33">This calls for convenient representation and effective exploitation of such information with the dlliteplugin.</a>
</body>
</html>