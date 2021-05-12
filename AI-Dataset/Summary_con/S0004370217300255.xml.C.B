<html>
<head>
<meta name="TextLength" content="SENT_NUM:49, WORD_NUM:1109">
</head>
<body bgcolor="white">
<a href="#0" id="0">Localising inconsistency in knowledge bases is an important step towards better managing inconsistency.</a>
<a href="#1" id="1">Additionally, methods for both measuring and repairing inconsistency can benefit from its localisation.</a>
<a href="#2" id="2">Inconsistent knowledge bases can hide conflicts that are not captured by minimal inconsistent sets.</a>
<a href="#3" id="3">Dually, some formulas regarded as free may be involved in conflicts together with parts of other formulas.</a>
<a href="#4" id="4">To circumvent these issues, we presented ⋆-innocuous formulas and ⋆-conflicts — which indirectly define ⋆-free formulas — as alternative ways to localise the controversial formulas in an inconsistent knowledge base and identify its atomic conflicts.</a>
<a href="#5" id="5">We showed how these concepts generalise free formulas and minimal inconsistent sets and how they relate to an underlying consolidation procedure.</a>
<a href="#6" id="6">We proved that, for modular consequence operations {a mathematical formula}Cn⋆, ⋆-innocuous and ⋆-free formula concepts are extensionally equivalent.</a>
<a href="#7" id="7">We also showed that allowing classical consequences ({a mathematical formula}Cn⋆=Cn or {a mathematical formula}⊢⋆=⊢) yields the trivial notion of ⋆-conflict that encompasses all inconsistent bases without tautologies.</a>
<a href="#8" id="8">Applying our framework to measuring inconsistency, we introduced new general inconsistency measures defined via ⋆-conflicts.</a>
<a href="#9" id="9">We investigated the debatable postulates of (Independence) and (Dominance), proposing a formal method to relax them into properties parameterised by the consequence operation {a mathematical formula}Cn⋆.</a>
<a href="#10" id="10">In particular, we analysed the possibility of reconciling a version of (Dominance) with an inconsistency measure based on counting conflicts.</a>
<a href="#11" id="11">How one define {a mathematical formula}Cn⋆ depends on the application.</a>
<a href="#12" id="12">Though, as a general rule, the expressivity of {a mathematical formula}Cn⋆ should reflect the degree to which those considering the knowledge will deconstruct and/or synthase it.</a>
<a href="#13" id="13">For instance, Santos et al. [39] describe different scenarios in belief revision that, for the desirable results to follow, require different subclassical consequence operations to be applied before performing a contraction.</a>
<a href="#14" id="14">Our framework can then be instantiated via these consequence operations in the corresponding situations.</a>
<a href="#15" id="15">Dealing with inconsistency is needed in different areas, for instance in descriptive logic [30] and ontologies [31].</a>
<a href="#16" id="16">Thus, iceberg inconsistencies may appear in several contexts, under different formal languages.</a>
<a href="#17" id="17">Using classical propositional logical as a prototype, we provided a general framework that can be applied to many different formalisms, such as description logics, probabilistic logics, mathematical constraints, etc.</a>
<a href="#18" id="18">Wherever there is a minimal inconsistent subset, there might be inconsistencies hidden under the water.</a>
<a href="#19" id="19">Once these submerged conflicts are spotted via a consequence operation, ⋆-conflicts brings them to the surface, localising its possible causes.</a>
<a href="#20" id="20">Dually, ⋆-free formulas are those that do not contribute to these hidden inconsistencies.</a>
<a href="#21" id="21">If inconsistency is to be resolved through a given formal procedure, then ⋆-innocuous formulas can be safely ignored during the consolidation.</a>
<a href="#22" id="22">In general, formalising a consistency restoring procedure through a ⋆-consolidation yields, via our proposal, methods for localising (via ⋆-conflicts) and measuring (via {a mathematical formula}I⋆) inconsistency.</a>
<a href="#23" id="23">Due to this flexibility, the ideas we put forward can be adapted to problems in a variety of areas, such as belief revision (see [12]), belief merging, requirements engineering, constraints satisfaction, incoherence measuring in formal epistemology and so on.</a>
<a href="#24" id="24">In requirements engineering, we can envisage that when inconsistencies are found in sets of requirements, our techniques can be used to determine who should be invited to discussions on resolving the inconsistencies (as suggested by Example 3.4, Example 5.6).</a>
<a href="#25" id="25">Our results show how choices for instance for {a mathematical formula}Cn⋆ can affect the identification of ⋆-conflicts, which in turn can affect how we can identify participants to the discussions.</a>
<a href="#26" id="26">Similarly, if we want to invoke a procedure for resolving inconsistencies in the set of requirements, and at each stage, we want to reduce the degree of inconsistency, we need to be clear about the notion of inconsistency we are measuring, and that in turn calls for clarity over the properties we expect of our inconsistency measure (such as whether (⋆-Dominance) holds).</a>
<a href="#27" id="27">In general, if the management of inconsistent requirements is logic-based, as in [37], our framework might be employed to improve the data analysis.</a>
<a href="#28" id="28">We therefore see that with the proposals in this paper, there is a range of conceptual tools for better managing the subtleties in iceberg inconsistencies that arise in diverse domains of computer science.</a>
<a href="#29" id="29">Inconsistency management policies [32], [33] offer context-dependent mechanisms for managing inconsistencies.</a>
<a href="#30" id="30">To illustrate, consider a client database with information on salaries, and for a particular individual, there are different tuples giving different values for the salary.</a>
<a href="#31" id="31">Different users of the database might require different policies for resolving the inconsistency.</a>
<a href="#32" id="32">For example, a tax inspector might take the maximum value as the salary, whereas a loan risk assessor might take the lowest value.</a>
<a href="#33" id="33">Localising and assessing inconsistencies is an important aspect of applying such policies, and they could be enhanced by considering iceberg conflicts.</a>
<a href="#34" id="34">Furthermore, as acknowledged in Martinez et al. [32], inconsistency measures may be a useful tool for helping to decide which inconsistency management policy to use.</a>
<a href="#35" id="35">For instance, if an inconsistency management policy involves weakening some of the information (represented as formulae), it may be prudent to first check whether weakening the formulae would actually reduce the degree of inconsistency where this measure takes into account iceberg conflicts.</a>
<a href="#36" id="36">Multi-context systems [14], [10] also offer context-dependent mechanisms for managing and resolving inconsistencies.</a>
<a href="#37" id="37">They harness heterogeneous information sources using bridge rules which specify how information can be pooled from these sources.</a>
<a href="#38" id="38">When inconsistencies arise in the pooled information, explanations can be used to localise and assess them.</a>
<a href="#39" id="39">These explanations are subsets of the information, and in [16], an adaptation of an inconsistency measure based on minimal inconsistent subsets is used to assess inconsistency.</a>
<a href="#40" id="40">This approach to assessing inconsistency can be augmented by considering iceberg conflicts.</a>
<a href="#41" id="41">Also in [15] these inconsistency explanations are formalised via logic, possibly enabling the application of our framework.</a>
<a href="#42" id="42">For relational databases, there is a range of repair techniques for resolving consistency [3], [7], [44], [6], [38].</a>
<a href="#43" id="43">These include deleting tuples, inserting null values, and attribute-based repairs (i.e. changing attributes in tuples), and they can be harnessed according to context using distance-based methods [4].</a>
<a href="#44" id="44">Depending on the precise specification of the repair technique, consideration of iceberg conflicts could be important in determining whether a particular approach to repair is appropriate.</a>
<a href="#45" id="45">The need to consider iceberg conflicts could also arise in other options for resolving inconsistency in databases such as revising tuples (e.g. for values in conflict, taking an interval of the values), and weakening integrity constraints.</a>
<a href="#46" id="46">Future work includes exploring different forms of localising inconsistency in knowledge bases by instantiating the framework introduced here.</a>
<a href="#47" id="47">For instance, the consequence operation could be defined by classical elimination rules, by paraconsistent logics or by substructural logics.</a>
<a href="#48" id="48">Another future task is to characterise primitive conflicts via a set of rationality postulates that they should satisfy, in the style of the AGM-operations.</a>
</body>
</html>