<html>
<head>
<meta name="TextLength" content="SENT_NUM:90, WORD_NUM:2453">
</head>
<body bgcolor="white">
<a href="#0" id="0">In this paper we have taken important first steps towards solving the problem of updates to MKNF knowledge bases, a mature framework for tightly integrated hybrid knowledge representing and reasoning.</a>
<a href="#1" id="1">We have defined two complementary update semantics.</a>
<a href="#2" id="2">The first semantics (Section 3) applies to DMKBs with static rules, and uses a first-order update operator ⋄ to perform ontology updates.</a>
<a href="#3" id="3">This semantics encompasses applications of hybrid knowledge bases in which the ontology contains highly dynamic information while rules represent defaults, preferences or behaviour that does not undergo changes and that can be overridden by ontology updates when necessary.</a>
<a href="#4" id="4">The second semantics applies to layered DMKBs (Section 5), and modularly combines a first-order update operator ⋄ with a rule update semantics {a mathematical formula}S. We demonstrated the use of this semantics in a realistic scenario involving cargo imports.</a>
<a href="#5" id="5">The approach is capable of performing non-trivial updates, automatically resolving conflicts in the expected manner, and propagating new information across the knowledge base.</a>
<a href="#6" id="6">To define the semantics of layered DMKBs we also introduced Abstract Splitting Properties (Section 4), which reformulate the notion of splitting so that it can be parameterised by different logical formalisms; the Abstract Splitting Properties form the basis of the hybrid update semantics defined in Section 5.</a>
<a href="#7" id="7">The two hybrid update semantics are complementary in the sense that each can handle inputs that the other one cannot.</a>
<a href="#8" id="8">Moreover, they are fully compatible with one another, meaning that they assign the same semantics to inputs accepted by both (cf.</a>
<a href="#9" id="9">Theorem 80).</a>
<a href="#10" id="10">By combining them one thus obtains an integrated hybrid update semantics that can safely handle inputs treated by either of the two semantics.</a>
<a href="#11" id="11">We also examined the basic theoretical properties of both hybrid update semantics.</a>
<a href="#12" id="12">We showed that they are faithful to ⋄ and {a mathematical formula}S: i.e., the hybrid semantics preserves the behaviour of the underlying update semantics when the hybrid knowledge base contains only ontology axioms or only rules.</a>
<a href="#13" id="13">Similarly, both of the introduced semantics are faithful to the static semantics of MKNF knowledge bases, so that when no updates are performed, the assigned models are simply MKNF models of the initial MKNF knowledge base.</a>
<a href="#14" id="14">Furthermore, they respect the principle of primacy of new information.</a>
<a href="#15" id="15">Finally, in Section 6 we have presented basic complexity results on each update semantics.</a>
<a href="#16" id="16">In defining each semantics, we have made as few assumptions as possible about the properties that guarantee the correctness of our definitions.</a>
<a href="#17" id="17">With respect to update operators, we abstract away from particular instantiations of ⋄ and {a mathematical formula}S and allow for any approach to ontology and rule updates – be it an existing one or one that is yet to be discovered – as long as it satisfies the given assumptions.</a>
<a href="#18" id="18">As an example the assumptions of language conservation and fact update are both needed in Section 5 to guarantee that the layered update semantics is independent of the choice of a splitting; both are basic properties of classical and of rule updates.</a>
<a href="#19" id="19">We have formally shown that they are satisfied for Winslett's update operator and the {a mathematical formula}RD-semantics for rule updates.</a>
<a href="#20" id="20">Similarly it can be shown that they hold for other approaches to classical updates, such as Hegner's semantics [47], Forbus' operator [39], Winslett's standard semantics and its syntax-independent version [50], [96], or the modified Winslett's operator [35], as well as by other rule update semantics, such as those introduced in [6], [20], [30], [31], [37], [66], [80], [97].</a>
<a href="#21" id="21">Beyond the assumptions about update operators, few assumptions have been made about the knowledge base, {a mathematical formula}K, that is to be updated.</a>
<a href="#22" id="22">{a mathematical formula}K may have an ontology constructed from any formalism that is translatable into first-order logic.</a>
<a href="#23" id="23">This includes not only most description logics, but other formalisms such as guarded first-order logics [9].</a>
<a href="#24" id="24">Of course, update operators for such fragments of first-order logic may not yet have been formulated, but the results in this paper indicate the sufficient conditions if they are to be extended to update MKNF knowledge bases.</a>
<a href="#25" id="25">The practical usefulness of the introduced semantics is underlined by the fact that the full expressivity of MKNF knowledge bases does not seem to be necessary in a number of practical use cases.</a>
<a href="#26" id="26">In particular, the separation of a hybrid knowledge base into distinct ontology and rule layers, as required by the layered update semantics of Section 5, seems to be a natural way of controlling how the different types of knowledge interact, and is in the spirit of recent work on modules for logic programs [12], [54].</a>
<a href="#27" id="27">Recent research has explored various issues pertaining to updating ontologies that are based on description logics.</a>
<a href="#28" id="28">One such issue may be termed the recovery problem: given an update operator ⋄, and ontologies {a mathematical formula}O1, {a mathematical formula}O2 both in a specific DL {a mathematical formula}D, can {a mathematical formula}O1⋄O2 be expressed in {a mathematical formula}D?</a>
<a href="#29" id="29">Unfortunately, [10] showed that when {a mathematical formula}D is at least as expressive as {a mathematical formula}ALCQI and ⋄ is {a mathematical formula}⋄W, querying {a mathematical formula}O1⋄WO2 is undecidable (and consequently cannot be expressed in {a mathematical formula}ALCQI).</a>
<a href="#30" id="30">Because of this result, one branch of work has focused on the restriction of updates to information in ABoxes.</a>
<a href="#31" id="31">For DLs that are at least as expressive as {a mathematical formula}ALC, ABox updates may be restricted to those that only allow for updates with assertions about concept names (i.e., assertions about classes to which given individuals belong) [15], [36], [73].</a>
<a href="#32" id="32">In these cases, the update semantics used coincides with Winslett's first-order operator {a mathematical formula}⋄W, and several DLs have been identified in which expressibility of the updated ABox is guaranteed.</a>
<a href="#33" id="33">In some of these DLs, the updated ABox may be exponential in size of the original ABox as well as of the update, while in others it may be exponential (only) in the size of the update.</a>
<a href="#34" id="34">An alternate line of work addresses updates of less expressive DLs, such as the DL-Lite [27], [28], [29].</a>
<a href="#35" id="35">Unlike ABox updates for expressive DLs, these update operators ensure that ABox updates do not affect the TBox, treating the TBox the same way that integrity constraints were handled in early belief update semantics [56].</a>
<a href="#36" id="36">This line of work also provides polynomial algorithms for computing the updated ABoxes or their approximations, depending on which flavour of DL-Lite is considered.</a>
<a href="#37" id="37">On the positive side, this means that the operator {a mathematical formula}⋄W ensures that the TBox is invariant under updates; on the negative side, such an approach may suffer from the same issues that arise when augmenting belief update semantics with integrity constraints [48], [49], [68].</a>
<a href="#38" id="38">The ontology update operators just discussed may be termed syntax-independent (or model-based), i.e. they satisfy the postulate (B4).</a>
<a href="#39" id="39">However, just as rule update operators are not syntax-independent, ontology update operators may be formula-based (cf.</a>
<a href="#40" id="40">[96]).</a>
<a href="#41" id="41">For formula-based operators, no semantic issues must be addressed when lifting operators based on propositional logic to first-order logic or ontologies, and expressibility is not an issue.</a>
<a href="#42" id="42">Accordingly, [21] argued that syntax-independent operators provide inappropriate results when applied to TBoxes and introduced a formula-based operator for TBox updates in DL-Lite.</a>
<a href="#43" id="43">Similarly, [67] have used a formula-based operator to tackle ABox updates to DL-Lite.</a>
<a href="#44" id="44">When updates started to be investigated in the context of Logic Programming, it was only natural to adapt belief update principles and operators to this purpose [4], [76].</a>
<a href="#45" id="45">However, such approaches proved insufficiently expressive, principally because the model-based approach fails to capture the essential relationships between literals encoded in rules [66], and the formula-based approach is too crude as it does not allow rules to be reactivated when reasons for their suppression disappear [97].</a>
<a href="#46" id="46">Although state-of-the-art approaches to rule updates are guided by the same basic intuitions and aspirations as belief updates, they build upon fundamentally different principles and methods.</a>
<a href="#47" id="47">Many of them are based on the causal rejection principle[5], [6], [7], [37], [66], [78].</a>
<a href="#48" id="48">Alternative approaches to rule updates employ syntactic transformations and other methods, such as abduction [80], prioritisation and preferences [31], [97], or dependencies on default assumptions [63], [82].</a>
<a href="#49" id="49">Despite the variety of techniques used in these approaches, certain properties are common to all of them, and seem to be taken as fundamental.</a>
<a href="#50" id="50">First, the stable models assigned to a program after one or more updates are always supported: for each true atom p there exists a rule in either the original program or its updates that has p in the head and whose body is satisfied.</a>
<a href="#51" id="51">Second, all mentioned rule update semantics coincide when it comes to updating sets of facts by newer facts.</a>
<a href="#52" id="52">Additionally, they need to refer to the syntactic structure of a logic program: the individual rules and, in most cases, also the literals in their heads and bodies.</a>
<a href="#53" id="53">This is what makes their full reconciliation with ontology updates so difficult since ontology axioms simply have no heads and bodies.</a>
<a href="#54" id="54">Despite this impedance mismatch, some are still looking for a unifying framework that could embrace both belief and rule updates.</a>
<a href="#55" id="55">For such a framework, finding an appropriate notion of equivalence is key.</a>
<a href="#56" id="56">In [32], [33], AGM based revision was reformulated in the context of Logic Programming in a manner analogous to belief revision in classical propositional logic, and specific revision operators for logic programs were investigated.</a>
<a href="#57" id="57">Central to this novel approach are SE models[93] which provide a monotonic semantic characterisation of logic programs that is strictly more expressive than the answer-set semantics.</a>
<a href="#58" id="58">Furthermore, two programs have the same set of SE models if and only if they are strongly equivalent [72], which means that programs {a mathematical formula}P,Q with the same set of SE models can be modularly replaced by each other with respect to the answer-set semantics, because strong equivalence guarantees that {a mathematical formula}P∪R has the same answer sets as {a mathematical formula}Q∪R for any program {a mathematical formula}R.</a>
<a href="#59" id="59">In [85], [90], a similar path was followed for KM based updates.</a>
<a href="#60" id="60">However, despite the promise that the additional expressiveness of SE models could bring, [85], [90] also show that strong equivalence is not a suitable basis for syntax-independent rule update operators because such operators cannot respect both support and fact update.</a>
<a href="#61" id="61">This can be demonstrated on programs {a mathematical formula}P={p.,q.}</a>
<a href="#62" id="62">and {a mathematical formula}Q={p.,q←p.}</a>
<a href="#63" id="63">which are strongly equivalent.</a>
<a href="#64" id="64">Due to syntax independence, an update asserting that p is now false ought to lead in both cases to the same stable models.</a>
<a href="#65" id="65">Due to fact update, such an update on {a mathematical formula}P should naturally lead to a stable model where q is true.</a>
<a href="#66" id="66">But in case of {a mathematical formula}Q such a stable model would be unsupported.</a>
<a href="#67" id="67">Such examples led to the study of stronger notions of program equivalence in [86], [87], and the proposal to view a logic program as the set of sets of models of its rules in order to acknowledge rules as the atomic pieces of knowledge and, at the same time, abstract away from unimportant differences between their syntactic forms, focusing on their semantic content.</a>
<a href="#68" id="68">Within this view of logic programs, updates can be seen to resemble formula-based ontology update operators.</a>
<a href="#69" id="69">In [88] the authors define an abstract framework – dubbed exception driven updates – which is capable of capturing both logic program updates, namely the operator in [66], along with several update operators used for ontology updates, such as the model-based Winslett's operator, or the formula-based WIDTIO and Bold operators [21], [29], [67], [73].</a>
<a href="#70" id="70">This view is closely related to base revision operators[40], [46], and provides a promising avenue to further investigate updates of hybrid knowledge bases.</a>
<a href="#71" id="71">Multi-context systems [17] provide an alternate formalism for representing hybrid knowledge in which each context represents a logic together with a set of beliefs, and where the contexts are integrated through so-called bridge rules.</a>
<a href="#72" id="72">Multi-context systems are more abstract than MKNF knowledge bases overall and so are more general; however, the relationship of the two formalisms has recently been clarified [60].</a>
<a href="#73" id="73">From the perspective of the work described in this paper, there is an interesting relationship between the defined class of layered DMKBs and multi-context systems.</a>
<a href="#74" id="74">Each layer of a DMKB w.r.t.</a>
<a href="#75" id="75">a particular layering splitting sequence can be viewed as a context that includes its own bridge rules.</a>
<a href="#76" id="76">At the same time, the constraints we impose guarantee that each such context either contains only rules, so the context logic can be the stable models semantics, or it contains only DL axioms so that first-order logic can be used as its underlying logic.</a>
<a href="#77" id="77">Though different splitting sequences induce different multi-context systems, their overall semantics remains the same (cf.</a>
<a href="#78" id="78">Proposition 72).</a>
<a href="#79" id="79">Based on this close relationship, a further study of the update frameworks presented here and the update semantics of managed multi-context systems [18], and more recently of reactive multi-context systems [16], [19], and evolving multi-context systems [45] may bring about interesting new insights.</a>
<a href="#80" id="80">Similarly, the relationship remains to be explored with [94], which studies how the first-order belief update postulates (Section 2.5) can be extended to multi-context systems and applied to update operators.</a>
<a href="#81" id="81">Furthermore, the development of similar update semantics under other existing frameworks for hybrid knowledge bases [25], [26], [38], [52], [62], [64] constitutes another topic of future investigation.</a>
<a href="#82" id="82">The results of this paper lay the groundwork for practical experimentation.</a>
<a href="#83" id="83">In this context, two implementations exist that support MKNF knowledge bases with stratified programs: [44] which supports {a mathematical formula}ALCQ, and the NoHR plug-in for the Protégé ontology editor which supports {a mathematical formula}EL[53] and DL-Lite[23].</a>
<a href="#84" id="84">These implementations may serve as starting points to explore the practical behaviour of hybrid updates based on the combination of specific update operators such as those mentioned in Section 7.1, and used in practice to deal with the dynamic aspects of applications which require the expressive power of hybrid knowledge bases, such as normative systems [1], [2].</a>
<a href="#85" id="85">The hybrid update semantics presented in this paper can be further generalised by lifting the various constraints under which they are developed.</a>
<a href="#86" id="86">In case of the semantics for DMKBs with static rules it would be interesting to consider adding support for disjunctive rules and for updates of the rule component, even if only to a limited extent.</a>
<a href="#87" id="87">As for the update semantics for layered DMKBs, one issue to study is type of splitting that it is based on.</a>
<a href="#88" id="88">The main limitation is that the current definition splits on predicate symbols, while in some cases it would be desirable to allow for a more fine-grained splitting, on the level of ground, and possibly generalised, atoms.</a>
<a href="#89" id="89">More broadly, other change operations, such as forgetting, erasure, revision and contraction, also need to be studied and related to updates in the context of hybrid knowledge bases, just as the relationship between dealing with inconsistencies in hybrid knowledge bases through updates and following a paraconsistency approach [55].</a>
</body>
</html>