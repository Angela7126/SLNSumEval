<html>
<head>
<meta name="TextLength" content="SENT_NUM:69, WORD_NUM:1423">
</head>
<body bgcolor="white">
<a href="#0" id="0">The {a mathematical formula}DLN family of logics results from a novel, utilitarian way of approaching nonmonotonic logic design, whose main goal is addressing the practical needs of ontology and policy designers, that have been illustrated with several examples in the literature on biomedical ontologies and semantic web policies.</a>
<a href="#1" id="1">We deliberately refrained from adding a priori any requirements that are not directly motivated by the applicative examples.</a>
<a href="#2" id="2">In general, the utilitarian approach led us to make {a mathematical formula}DLN neutral with respect to the inferences that are not always desired: when possible, {a mathematical formula}DLN gives knowledge engineers the ability of switching those inferences on and off.</a>
<a href="#3" id="3">The final result of this investigation is a logic that enjoys the following unique set of properties{sup:32}:</a>
<a href="#4" id="4">No inheritance blocking.</a>
<a href="#5" id="5">Recall that most of the logics grounded on preferential semantics and rational closure block the propagation of all default properties towards exceptional subclasses (so they fail to address correctly Example 6, Example 30).</a>
<a href="#6" id="6">The plain notion of overriding cast into {a mathematical formula}DLN (based solely on consistency with higher priority defaults) yields the correct results.</a>
<a href="#7" id="7">No CWA effects.</a>
<a href="#8" id="8">Many nonmonotonic DLs extend default properties to as many individuals as possible, introducing CWA effects that clash with the intended behavior of biomedical ontologies.</a>
<a href="#9" id="9">For instance, a concept (such as Whale or SitusInversus) may collapse to the inconsistent concept or a small set of individuals just because it has some exceptional property (cf.</a>
<a href="#10" id="10">the discussion in Section 6 and in particular Example 21, Example 28).</a>
<a href="#11" id="11">Moreover, such normality maximization introduces a sort of optimization problem in reasoning that increases computational complexity.</a>
<a href="#12" id="12">{a mathematical formula}DLN does not introduce any CWA effect because it does not force individuals to be normal, unless explicitly stated otherwise.</a>
<a href="#13" id="13">Nonetheless it is easy to check which properties would an individual have if it were normal (cf.</a>
<a href="#14" id="14">Section 3.6).</a>
<a href="#15" id="15">Fine-grained control on role ranges.</a>
<a href="#16" id="16">Should role values be restricted to normal individuals?</a>
<a href="#17" id="17">This is a kind of inference that is neither universally desirable nor undesirable, cf.</a>
<a href="#18" id="18">Example 11, Example 12.</a>
<a href="#19" id="19">Some logics are completely unable to apply default properties to role values.</a>
<a href="#20" id="20">Some others cannot switch this inference off when it is not desired.</a>
<a href="#21" id="21">Only {a mathematical formula}DLN and {a mathematical formula}ALC+Tmin make it possible to control this kind of inference.</a>
<a href="#22" id="22">Due to its explicit priorities, {a mathematical formula}DLN is also able to encode a design pattern that makes role ranges normal whenever this does not override any explicit DI.</a>
<a href="#23" id="23">Inconsistent prototype detection.</a>
<a href="#24" id="24">We argued that when conflicts cannot be settled by priorities, silent conflict resolution is not a desirable feature: knowledge engineers should be involved because there is no universally correct automated resolution criterion (cf.</a>
<a href="#25" id="25">Example 1, Example 2).</a>
<a href="#26" id="26">Only {a mathematical formula}DLN and probabilistic description logics (and {a mathematical formula}ALC+Tmin, in some very specific cases) detect inconsistent prototypes and make them evident.</a>
<a href="#27" id="27">Canonical {a mathematical formula}DLN knowledge bases confine such inconsistencies to the corresponding normality concepts.</a>
<a href="#28" id="28">Unique deductive closure.</a>
<a href="#29" id="29">As a result of automated conflict resolution, several nonmonotonic logics yield multiple deductive closures, corresponding to all the alternative ways of solving each conflict.</a>
<a href="#30" id="30">{a mathematical formula}DLN is one of the logics that has a unique closure.</a>
<a href="#31" id="31">Low complexity.</a>
<a href="#32" id="32">The reduction of {a mathematical formula}DLN subsumption and instance checking to classical reasoning iterates the inference procedure of {a mathematical formula}DL a polynomial number of times.</a>
<a href="#33" id="33">It follows that {a mathematical formula}DLN preserves the tractability of these reasoning tasks—which cover all the applicative examples—for all low-complexity DLs, including the rich tractable logics {a mathematical formula}EL++ and {a mathematical formula}DL-liteHorn(HN).</a>
<a href="#34" id="34">Currently, no other nonmonotonic DL enjoys this property.</a>
<a href="#35" id="35">Some logics, such as [18], [17], [19], preserve the asymptotic complexity of ExpTime-complete DLs like {a mathematical formula}ALC.</a>
<a href="#36" id="36">However, the additional cost of nonmonotonic reasoning is exponential in these logics, because in the worst case inferences must be repeated for all permutations of the individual constants in the ABox, as each permutation may yield a different deductive closure.</a>
<a href="#37" id="37">This is likely to have practical consequences.</a>
<a href="#38" id="38">The complete set of complexity results for the {a mathematical formula}DLN logics considered in this paper are reported in Table 2.</a>
<a href="#39" id="39">Control on priorities.</a>
<a href="#40" id="40">Since priorities are not fixed a priori in {a mathematical formula}DLN, knowledge engineers can adapt them to their needs.</a>
<a href="#41" id="41">In principle, it is possible to override DIs based on temporal criteria (which may be useful in legal ontologies and ontology versioning), define default conflict resolution criteria (as in the nonmonotonic design pattern after Example 12), and even use rational closure's specificity-based axiom ranking, if so desired, thereby getting a similar behavior in Example 26, Example 27.</a>
<a href="#42" id="42">The logics derived from inheritance networks, preferential semantics, and rational closure can only support their fixed, specificity-based overriding criterion.</a>
<a href="#43" id="43">Since these kinds of specificity (that take the consequences of defeasible axioms into account) and ours (based on strong axioms only) yield incomparable results, evaluating them in the perspective of knowledge engineering needs is an interesting topic for further research.</a>
<a href="#44" id="44">Moreover, {a mathematical formula}DLN enjoys nice technical properties, that are not universally satisfied by other nonmonotonic semantics, such as the finite model property and the preservation of classical knowledge base satisfiability (the latter holds for canonical knowledge bases).</a>
<a href="#45" id="45">The translation of {a mathematical formula}DLN knowledge bases into equivalent classical knowledge bases (26), (27), (28) constitutes one of the simplest accounts of nonmonotonic inferences and overriding introduced so far: DIs are applied in decreasing priority order, checking their consistency with higher priority DIs without any further complication.</a>
<a href="#46" id="46">There is no real nondeterminism, as all linearizations of ≺ yield the same deductive closure.</a>
<a href="#47" id="47">Overriding in the other logics is only apparently similar, as witnessed by the comparison in Table 1; various kinds of additional constraints or mechanisms complicate their behavior, as discussed in Section 6.</a>
<a href="#48" id="48">{a mathematical formula}DLN (like any other nonmonotonic DL) facilitates the incremental refinement of knowledge bases with new subclasses and related exceptions.</a>
<a href="#49" id="49">The advantages over monotonic design patterns are discussed in detail in Appendix C, using applicative examples from the biomedical domain.</a>
<a href="#50" id="50">Moreover, by highlighting inconsistent prototypes, and confining those inconsistencies to individual concepts, {a mathematical formula}DLN may facilitate ontology debugging.</a>
<a href="#51" id="51">The first experimental scalability tests are promising.</a>
<a href="#52" id="52">The result graphs show that DIs cause an approximately linear increase in reasoning time.</a>
<a href="#53" id="53">A semi-naive implementation (relying only on the optimization techniques of the underlying classical reasoner) can construct and classify the classical translation {a mathematical formula}KBΣ for the large {a mathematical formula}KB Gene Ontology (GO) in less than 30 seconds when DIs are 5% of GO's inclusions, and in less than 2 minutes when DIs grow to 25%.</a>
<a href="#54" id="54">The subsequent query phase remains below 4 milliseconds.</a>
<a href="#55" id="55">As it is, the prototype is compatible with practical applications where the above response times are acceptable, or those where the set of interesting queries can be identified in advance so that {a mathematical formula}KBΣ can be pre-computed.</a>
<a href="#56" id="56">We are planning to investigate optimization techniques to reduce the number of classifications during the construction of {a mathematical formula}KBΣ.</a>
<a href="#57" id="57">The test case generator should be considered as a contribution, as well.</a>
<a href="#58" id="58">Its output has been analyzed in depth to verify that the synthetic ontologies it constructs and their classification are not trivial.</a>
<a href="#59" id="59">The test case generator and the above validation criteria will hopefully be of help for other researchers in this field, where real nonmonotonic knowledge bases are not yet available.</a>
<a href="#60" id="60">The semantics of {a mathematical formula}DLN specifies how to entail defeasible inclusions (unlike Circumscribed DLs and Default DLs).</a>
<a href="#61" id="61">This feature does not immediately help in our reference applications, but it might turn out to be helpful in designing optimization techniques.</a>
<a href="#62" id="62">We leave the problem of general DI entailment as an open issue; Theorem 4 shows how to check DI entailments {a mathematical formula}KB{an inline-figure}δ when both {a mathematical formula}KB and δ are N-free.</a>
<a href="#63" id="63">The complexity of N-free DI entailment is reported in Table 2.</a>
<a href="#64" id="64">In some cases, inferring DIs is harder than subsumption and instance checking problems (unless {a mathematical formula}P=NP).</a>
<a href="#65" id="65">It should be remarked that [18], [17], [19], [40] support analogues of DI inference and provide suitable algorithms for computing them without restrictions.</a>
<a href="#66" id="66">The complexity of these reasoning tasks in the cited papers is at least ExpTime hard, and matches the complexity of classical inference in the underlying DL, namely {a mathematical formula}ALC in [18], [17], [19], {a mathematical formula}SHIF(D) and {a mathematical formula}SHOIN(D) in [40].</a>
<a href="#67" id="67">Another topic that deserves further attention is conjunctive query answering (especially in the context of the DL-lite family).</a>
<a href="#68" id="68">We expect the nice properties of subsumption and instance checking in {a mathematical formula}DLN to carry over to this class of queries.</a>
</body>
</html>