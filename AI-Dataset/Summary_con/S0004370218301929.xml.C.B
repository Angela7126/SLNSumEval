<html>
<head>
<meta name="TextLength" content="SENT_NUM:26, WORD_NUM:739">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have presented LARS, a logic-based formalism to model and analyze stream processing respectively reasoning over data streams, where the data volume is reduced by using data snapshots called windows.</a>
<a href="#1" id="1">LARS is equipped with a model-based semantics and offers besides “classical” semantics also an expressive rule-based language that adopts the answer set semantics for dealing with incomplete information.</a>
<a href="#2" id="2">Drawing from the observation about what operations are typically performed on windows in stream processing, we have considered the temporal modalities □, ◇ and the nominal operator {a mathematical formula}@t; that is, LARS allows for distinguishing truth of a formula at (i) specific time points, but also (ii) at some respectively every time point in a window; furthermore, it offers general window operators that may be nested, which enables reasoning over streams within the language.</a>
<a href="#3" id="3">After discussing some elementary properties of LARS programs, we have investigated the computational complexity of major reasoning tasks in LARS, viz.</a>
<a href="#4" id="4">model checking and satisfiability testing, for both LARS formulas and programs, where we have put emphasis on specific classes of windows that are widely used in practice (time-based, tuple-based, and partition-based windows).</a>
<a href="#5" id="5">In that, we have characterized the complexity of instance classes of the problems ranging from {a mathematical formula}P-completeness in the propositional (ground) case to {a mathematical formula}NExpTimeNP-completeness in the Datalog setting.</a>
<a href="#6" id="6">Notably, the use of common windows in practice does not add to the worst-case complexity of the underlying fragment of temporal logic, nor does bounded nesting depth in general.</a>
<a href="#7" id="7">We have then related LARS to selected other languages and formalisms for reasoning over streams.</a>
<a href="#8" id="8">We have shown that propositional LARS formulas with sliding time windows can be expressed in linear temporal logic, and thus amount to a (strict) fragment of the regular languages, while LARS program with such windows capture the regular languages.</a>
<a href="#9" id="9">Furthermore, we have shown that queries in the well-known Continuous Query Language (CQL) [11] can be captured by LARS, and we have briefly discussed that the operational semantics of the RDF Stream Processing engines CQELS [88] and C-SPARQL [14] can modeled in LARS, while the prominent ETALIS language [8], which is geared towards complex event processing, is beyond a natural representation.</a>
<a href="#10" id="10">The modeling of CQL, CQELS and C-SPARQL illustrates the usage of LARS as a formal representation and analysis framework, which was one of the motivations behind the formalism.</a>
<a href="#11" id="11">As it turned out, the formalism and its affinity to Answer Set Programming make it attractive as a genuine reasoning language, which has been pursued in a pilot application in the context of content-centric network management [17], [18]; follow up research in cyber-physical systems is on the agenda.</a>
<a href="#12" id="12">For these endeavors, recent experimental implementation prototypes of LARS fragments, which cater for incremental reasoning, will be instrumental.</a>
<a href="#13" id="13">There are several directions for future work.</a>
<a href="#14" id="14">One is to enrich the LARS framework.</a>
<a href="#15" id="15">Besides aggregates, towards event processing further temporal operators such as next time {a mathematical formula}(X) and until {a mathematical formula}(U), as well as their past time versions {a mathematical formula}(X−1,U−1) can be considered.</a>
<a href="#16" id="16">The entailment relation over streams can be naturally extended adhering to the usual semantics of these operators (where at the end of a stream, {a mathematical formula}Xα evaluates to false).</a>
<a href="#17" id="17">Accordingly, the evaluation algorithms discussed in Section 4 can be extended, without an increase of worst case complexity in the general case.</a>
<a href="#18" id="18">However, the complexity of fragments of the language, as well their expressiveness, might be affected.</a>
<a href="#19" id="19">Another direction is a refined picture of the complexity and expressivity of LARS fragments.</a>
<a href="#20" id="20">Restrictions to the general framework can be defined in form of syntactic and semantic criteria.</a>
<a href="#21" id="21">The fragments introduced in [19], [20] may serve here as a starting point.</a>
<a href="#22" id="22">Based on the results, efficient implementations and optimization may be developed, where in particular incremental methods (as discussed in Sections 6.1–6.3), data reduction via small window size (to be determined from the data) and approximation are of interest.</a>
<a href="#23" id="23">Related to the previous direction is to extend and deepen the investigation of the relationship to other formalisms and languages for stream reasoning, in particular to metric temporal logic and datalogMTL as the Horn fragment thereof.</a>
<a href="#24" id="24">In connection with this, further reasoning tasks, such as prediction based on future evolutions of the stream might be considered; some initial results have been obtained in [20], [38].</a>
<a href="#25" id="25">Finally, further use of LARS to model stream reasoning languages, e.g., {a mathematical formula}SPARQLStream[30], and to develop reasoning modules for applications remain to be continued.</a>
</body>
</html>