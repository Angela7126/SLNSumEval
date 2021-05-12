<html>
<head>
<meta name="TextLength" content="SENT_NUM:67, WORD_NUM:1925">
</head>
<body bgcolor="white">
<a href="#0" id="0">In the first part of the paper we have provided a semantic reconstruction of the well known notion of propositional rational closure.</a>
<a href="#1" id="1">We have provided two minimal model semantics, based on the idea that preferred rational models are those in which the rank of the worlds is minimized.</a>
<a href="#2" id="2">We have then shown that when adding suitable possibility assumptions to a knowledge base, these two minimal model semantics correspond to rational closure.</a>
<a href="#3" id="3">The correspondence between the proposed minimal model semantics and rational closure suggests the possibility of defining variants of rational closure by varying the three ingredients underlying our approach, namely: (i) the properties of the preference relation <: for instance just preorder, or multi-linear or weakly-connected; (ii) the comparison relation on models: based for instance on the rank of the worlds or on the inclusion between the relations <, or on a special kind of formulas satisfied by a world, as in the logic {a mathematical formula}Pmin[19]; (iii) the choice between fixed or variable interpretations.</a>
<a href="#4" id="4">The systems obtained by various combinations of the three ingredients are largely unexplored and may give rise to useful nonmonotonic logics.</a>
<a href="#5" id="5">In the second part of the paper we have defined a rational closure construction for the Description Logic {a mathematical formula}ALC extended with a typicality operator and provided a minimal model semantics for it based on the idea of minimizing the rank of objects in the domain, that is their level of “untypicality”.</a>
<a href="#6" id="6">This semantics corresponds to a natural extension to DLs of Lehmann and Magidor's notion of rational closure.</a>
<a href="#7" id="7">We have also extended the notion of rational closure to the ABox, by providing an algorithm for computing it that is sound and complete with respect to the minimal model semantics.</a>
<a href="#8" id="8">Last, we have shown an ExpTime upper bound for the algorithm.</a>
<a href="#9" id="9">The work presented in this paper is an extension of the work in [22] and in [24].</a>
<a href="#10" id="10">In another direction, we aim to develop a generalization of the notion of rational closure introduced in this paper and of its minimal model semantics to deal with more expressive DLs and, in particular, with DLs which do not enjoy the finite model property, such as {a mathematical formula}ALCOIQ and {a mathematical formula}SHOIQ, for which the notion of canonical model as introduced in this paper appears to be too strong.</a>
<a href="#11" id="11">As far as rational closure is concerned, it is worth noticing that rational closure for Description Logics inherits both the virtues and the weakness of propositional rational closure.</a>
<a href="#12" id="12">We have already said about the strengths, among which there are the good computational properties.</a>
<a href="#13" id="13">For what concerns the weaknesses, rational closure does not allow to separately reason about the inheritance of different properties.</a>
<a href="#14" id="14">For instance, in the classical birds and penguins example, rational closure does not allow to reason in this way: penguins inherit all typical properties of birds, except those for which we know they are an exception (as the property of flying).</a>
<a href="#15" id="15">On the contrary, once penguins are recognized as non-typical birds, no inheritance of typical properties is possible.</a>
<a href="#16" id="16">In order to solve this problem, a strengthening of a rational closure-like algorithm with defeasible inheritance networks has been studied by [9].</a>
<a href="#17" id="17">In future work, we aim to explore possible strengthening of the notion of rational closure at the semantic level, to overcome the weaknesses mentioned above.</a>
<a href="#18" id="18">One possible direction we briefly discuss here, could be to “relativize” the notion of typicality enforced by the semantics.</a>
<a href="#19" id="19">In order to achieve this, we aim to refine the semantics by considering models equipped with multiple preference relations, whence with multiple “typicality” operators.</a>
<a href="#20" id="20">In this variant, it should be possible to distinguish different aspects of typicality/exceptionality and consequently to avoid the “all or nothing” behavior of rational closure with respect to property inheritance.</a>
<a href="#21" id="21">For the time being, we just notice that in order to make this variant interesting and meaningful, one should deal with issues like: what does differentiate one preference relation from another?</a>
<a href="#22" id="22">What are the dependencies between different preference relations?</a>
<a href="#23" id="23">Can different preference relations or (syntactically) different typicality operators be combined?</a>
<a href="#24" id="24">All these issues require a suitable analysis/understanding which is preliminary to the technical development.</a>
<a href="#25" id="25">Furthermore, one should also study an algorithmic counterpart of this semantics, that is to say, a suitable reformulation of the rational closure mechanism, with the hope of keeping a reasonable complexity.</a>
<a href="#26" id="26">In [23], [21] nonmonotonic extensions of DLs based on the T operator have been proposed.</a>
<a href="#27" id="27">In these extensions, the semantics of T is based on preferential logic P. Nonmonotonic inference is obtained by restricting entailment to minimal models, where minimal models are those that minimize the truth of formulas of a special kind.</a>
<a href="#28" id="28">In this work, we have presented an alternative approach.</a>
<a href="#29" id="29">First, the semantics underlying the T is R. Moreover and more importantly, we have adopted a minimal model semantics, where, as a difference with the previous approach, the notion of minimal model is completely independent from the language and is determined only by the relational structure of models.</a>
<a href="#30" id="30">Casini and Straccia in [8] develop a notion of rational closure for DLs.</a>
<a href="#31" id="31">They propose a construction to compute the rational closure of an {a mathematical formula}ALC knowledge base, which is not directly based on Lehmann and Magidor definition of rational closure [33], but is similar to the construction of rational closure proposed by Freund in [14] for the propositional calculus.</a>
<a href="#32" id="32">[8] keeps the ABox into account, and defines closure operations over individuals.</a>
<a href="#33" id="33">It introduces a consequence relation ⊩ among a knowledge base K and assertions, under the requirement that the TBox is unfoldable and the ABox is closed under completion rules, such as, for instance, that if {a mathematical formula}a:∃R.C∈ABox, then both aRb and {a mathematical formula}b:C (for some individual constant b) must belong to the ABox, too.</a>
<a href="#34" id="34">Under such restrictions, a procedure is defined to compute the rational closure of the ABox, assuming that the individuals explicitly named are linearly ordered, and different orders determine different sets of consequences.</a>
<a href="#35" id="35">The authors show that, for each order s, the consequence relation {a mathematical formula}⊩s is rational and can be computed in PSpace.</a>
<a href="#36" id="36">In a subsequent work [9], [11], the authors introduce an approach based on the combination of rational closure and Defeasible Inheritance Networks (INs).</a>
<a href="#37" id="37">The authors first develop their approach at a propositional level, then they extend it to DLs, addressing both TBox and ABox reasoning.</a>
<a href="#38" id="38">The resulting construction is a nonmonotonic mechanism enjoying the logical properties of rational entailment, but not suffering from the “all-or-nothing” behavior with respect to inheritance of defeasible properties.</a>
<a href="#39" id="39">The nonmonotonic mechanism proposed by the authors corresponds to an algorithm to compute inferences, however, as a difference with our proposal, no declarative characterization of those inferences is provided.</a>
<a href="#40" id="40">To overcome the limitations of rational closure, in [10] Casini and Straccia also define a notion of lexicographic closure for {a mathematical formula}ALC.</a>
<a href="#41" id="41">In [7] a semantic characterization of a variant of the notion of rational closure introduced in [8] has been presented, which is based on a generalization to {a mathematical formula}ALC of our semantics in [22].</a>
<a href="#42" id="42">In [7], defeasible subsumption statements have the form {a mathematical formula}C⊏̰D and typicality assertions are not allowed in the ABox, which is defined as a standard {a mathematical formula}ALC ABox.</a>
<a href="#43" id="43">As we have seen, in this paper the presence of typicality assertions in the ABox may force some typicality inclusion not to hold, which is similar to allowing negated conditionals in KLM logics.</a>
<a href="#44" id="44">While the minimal model semantics naturally deals with the presence of typicality assertions, the presence of typicality assertions in the ABox has to be taken into account, as we have done, in the definition of rational closure of the TBox and of the ABox.</a>
<a href="#45" id="45">A further difference of our construction with those in [8], [7] is in the notion of exceptionality: our definition of exceptionality exploits preferential entailment, while [8], [7] directly use entailment in {a mathematical formula}ALC over a materialization of the knowledge base.</a>
<a href="#46" id="46">We have seen in Section 3.2 that we cannot replace entailment in {a mathematical formula}ALC+TR by entailment in {a mathematical formula}ALC over a materialization of the knowledge base.</a>
<a href="#47" id="47">However, when typicality assertions are not allowed in the ABox, our notion of rational closure for TBox can be computed in {a mathematical formula}ALC by defining a linear encoding of {a mathematical formula}ALC+TR entailment into {a mathematical formula}ALC (the encoding is exactly the same as the one provided in [26] for encoding of {a mathematical formula}SHIQRT entailment into {a mathematical formula}SHIQ).</a>
<a href="#48" id="48">A related approach can be found in [3].</a>
<a href="#49" id="49">The basic idea of their semantics for the propositional case is similar to ours: to consider models of the K where the rank of each world is as small as possible.</a>
<a href="#50" id="50">This idea has its roots in the work by Pearl [38] and by Lehmann and Magidor [33].</a>
<a href="#51" id="51">The construction of [3] differs from ours as the very notion of model is different (although equivalent): a model is a sequence of sets of “atoms” (conjunctions of literals for every propositional variable).</a>
<a href="#52" id="52">Each set of the sequence represents a set of worlds with the same ranking.</a>
<a href="#53" id="53">A unique model of the rational closure is then defined by considering all models of the K and by taking for each level, starting from the bottom one, the union of the worlds (not already considered) at that level.</a>
<a href="#54" id="54">This construction corresponds to building a model where each world has a minimal rank.</a>
<a href="#55" id="55">In contrast, we proceed in a different way: our semantics is defined in terms of standard Kripke models where the rank is given by the preference (or accessibility) relation, and models of the rational closure are defined as the minimal ones with respect to a comparison relation on models.</a>
<a href="#56" id="56">Our presentation is then more abstract and declarative than the one proposed in [3], whilst theirs is more “operational”, as it relies on a specific representation of models and it provides a recipe to build a model of the rational closure, rather than a characterization of its properties.</a>
<a href="#57" id="57">The logic {a mathematical formula}ALC+TR we consider as our base language is equivalent to the logic for defeasible subsumptions in DLs proposed by [5].</a>
<a href="#58" id="58">At a syntactic level the two logics differ, so that in [5] one finds the defeasible inclusions {a mathematical formula}C⊏̰D instead of {a mathematical formula}T(C)⊑D of {a mathematical formula}ALC+TR, however it has be shown in [20] that the logic of defeasible subsumption can be translated into {a mathematical formula}ALC+TR by replacing {a mathematical formula}C⊏̰D with {a mathematical formula}T(C)⊑D.</a>
<a href="#59" id="59">In [6] the semantics of the logic of defeasible subsumptions is strengthened by a preferential semantics.</a>
<a href="#60" id="60">Intuitively, given a TBox, the authors first introduce a preference ordering ≪ on the class of all subsumption relations ⊏̰ including TBox, then they define the rational closure of TBox as the most preferred relation ⊏̰ with respect to ≪, i.e. such that there is no other relation {a mathematical formula}⊏̰′ such that TBox {a mathematical formula}⊆⊏̰′ and {a mathematical formula}⊏̰′≪⊏̰.</a>
<a href="#61" id="61">Furthermore, the authors describe an ExpTime algorithm in order to compute the rational closure of a given TBox.</a>
<a href="#62" id="62">[6] does not address the problem of dealing with the ABox.</a>
<a href="#63" id="63">In [36] a plug-in for the Protégé ontology editor implementing the mentioned algorithm for computing the rational closure for a TBox for OWL ontologies is described.</a>
<a href="#64" id="64">Recent works discuss the combination of open and closed world reasoning in DLs.</a>
<a href="#65" id="65">In particular, formalisms have been defined for combining DLs with logic programming rules (see, for instance, [13] and [37]).</a>
<a href="#66" id="66">A grounded circumscription approach for DLs with local closed world capabilities has been defined in [32].</a>
</body>
</html>