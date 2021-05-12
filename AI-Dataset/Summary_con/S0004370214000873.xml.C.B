<html>
<head>
<meta name="TextLength" content="SENT_NUM:44, WORD_NUM:1231">
</head>
<body bgcolor="white">
<a href="#0" id="0">In the light of the results reported in the previous sections, the following conclusions can be drawn.</a>
<a href="#1" id="1">Generally speaking, the disjunctive closures of classes {a mathematical formula}L of propositional representations appear as interesting target classes for KC when the application under consideration expects tractability for the queries and transformations CO, CD and their consequences (e.g., CE, ME), as well as FO and/or {a mathematical formula}∨C (depending on the type of closure which is considered).</a>
<a href="#2" id="2">Especially, as soon as {a mathematical formula}L is stable by uniform renaming, the transformations FO, {a mathematical formula}∨C are offered “for free” by the full disjunctive closure {a mathematical formula}L[∨,∃] (even if the underlying class {a mathematical formula}L does not offer any of them), while CO, CD are preserved by the closure.</a>
<a href="#3" id="3">The other queries and transformations considered in the KC map are not guaranteed to be offered or to survive a disjunctive closure operation in the general case.</a>
<a href="#4" id="4">Considering specific disjunctive closures may allow for preserving additional queries or transformations, and for increasing the expressiveness of the underlying language.</a>
<a href="#5" id="5">Thus, the disjunction closure and the full disjunctive closure of any language {a mathematical formula}L containing TERM are complete propositional languages, even if {a mathematical formula}L is not (KROM, HORN, {a mathematical formula}K/H, renH, and AFF are such languages).</a>
<a href="#6" id="6">Clearly enough, fully expressive propositional languages are highly expected by many applications.</a>
<a href="#7" id="7">Of course, it cannot be guaranteed in the general case that the size of a compiled form remains “small enough” when a disjunctive closure is targeted.</a>
<a href="#8" id="8">Nevertheless, every disjunctive closure of a class {a mathematical formula}L includes {a mathematical formula}L as a subset, hence applying a disjunctive closure principle to a class {a mathematical formula}L decreases neither the expressiveness nor the succinctness of {a mathematical formula}L. Actually, applying any/both of those two principles may lead to new classes, which can prove strictly more expressive and strictly more succinct than the underlying class {a mathematical formula}L. Thus, each of the disjunction closure and the full disjunctive closure of any of KROM, HORN, {a mathematical formula}K/H, renH, and AFF is strictly more expressive than the underlying language.</a>
<a href="#9" id="9">Furthermore, the full disjunctive closure {a mathematical formula}HORN[∨,∃] (resp.</a>
<a href="#10" id="10">{a mathematical formula}K/H[∨,∃], {a mathematical formula}renH[∨,∃]) is strictly more succinct than the corresponding disjunction closure {a mathematical formula}HORN[∨] (resp.</a>
<a href="#11" id="11">{a mathematical formula}K/H[∨], {a mathematical formula}renH[∨]).</a>
<a href="#12" id="12">Now, from the application point of view, there are many important problems in AI and in other fields of Computer Science, where one is interested in encoding some pieces of information using representations for which CO, CD, FO and ME are computationally easy.</a>
<a href="#13" id="13">For instance, in model-based diagnosis, it makes sense to compile the description of the system to be diagnosed (during an off-line phase) in order to be able to generate efficiently consistency-based diagnoses, for a number of observations available on-line only [33], [41], [42].</a>
<a href="#14" id="14">Such diagnoses are the models of the system description, once conditioned by the given observation and then projected onto the variables expressing the components statuses (in the simplest case, faulty or not).</a>
<a href="#15" id="15">Accordingly, if the system description has been compiled first into a representation which satisfies CO, CD, FO and ME, then the diagnoses can be computed in input-output polynomial time.</a>
<a href="#16" id="16">Our results thus show full disjunctive closures of languages {a mathematical formula}L satisfying the stability by uniform renaming condition as valuable target languages for the compilation, as soon as {a mathematical formula}L satisfies CO and CD (which is the case for KROM, HORN, {a mathematical formula}K/H, renH, and AFF).</a>
<a href="#17" id="17">In product configuration and interactive recommendation, it is also important to offer some response-time guarantees to the front-end user, especially when the interaction is Web-based.</a>
<a href="#18" id="18">In order to achieve this goal, an approach consists in compiling the product catalog into a propositional representation (the models of it representing the feasible products).</a>
<a href="#19" id="19">Among the operations required by the configuration process are propagating the user's choices (the CD transformation), testing whether at least one feasible product is compatible with the user's choices (the CO query), and listing a fixed number of feasible products compatible with the user's choices (see e.g. [43], [44]).</a>
<a href="#20" id="20">Often, the feasible products are described using two types of variables (or “codes” [45]): the customer variables – the variables the user controls – and the manufacturer control variables – which express some information related to the factory or to the distribution of the product, and are not available to the user.</a>
<a href="#21" id="21">Thus, the manufacturer control variables must be forgotten from the representation before listing the solutions.</a>
<a href="#22" id="22">Our results show that those operations can be achieved efficiently when the catalog has been compiled into a full disjunctive closure of a class {a mathematical formula}L of propositional representations, stable by uniform renaming, and satisfying CO and CD.</a>
<a href="#23" id="23">In particular, the task of enumerating a preset number of solutions is feasible in polynomial time in this case (Algorithm 1 given in Appendix A is a polynomial delay enumeration procedure).</a>
<a href="#24" id="24">Beyond AI applications, enumerating models once projected on a given set of variables appears as a fundamental issue for a number of problems considered in software engineering and formal methods.</a>
<a href="#25" id="25">Thus, in the setting of automatic case generation based on propositional logic, such models correspond to test cases [46].</a>
<a href="#26" id="26">The problem all-sat (or “all-solutions” sat) which consists in enumerating the assignments to “important” variables of a propositional representation, which can be extended to models, turns out to be very significant in symbolic model checking [47], which explains that dedicated algorithms have been developed for solving it [48].</a>
<a href="#27" id="27">Indeed, this problem is considered for predicate abstraction [49], and re-parameterization in symbolic simulation [50].</a>
<a href="#28" id="28">In reachability analysis, one is interested in computing the set of states reachable from (resp.</a>
<a href="#29" id="29">leading to) a given set of states under a transition relation; this is called the image (resp.</a>
<a href="#30" id="30">pre-image) computation problem.</a>
<a href="#31" id="31">The transition relation T can be modeled as a Boolean function T over {a mathematical formula}X∪Y∪X′, complete terms {a mathematical formula}γX over X (resp.</a>
<a href="#32" id="32">{a mathematical formula}X′) are used to denote states before (resp.</a>
<a href="#33" id="33">after) a transition and complete terms {a mathematical formula}γY over Y represent inputs making precise the transition.</a>
<a href="#34" id="34">By construction, the models of {a mathematical formula}∃Y.T|γX (resp.</a>
<a href="#35" id="35">{a mathematical formula}∃Y.T|γX′) represent the image of {a mathematical formula}γX (resp.</a>
<a href="#36" id="36">the pre-image of {a mathematical formula}γX′) by T. The “important” variables are those of {a mathematical formula}X′ (resp.</a>
<a href="#37" id="37">X).</a>
<a href="#38" id="38">Accordingly, many sat solvers have been customized into all-sat solvers precisely for computing images or pre-images (see e.g. [51], [52]) from CNF representations of transition relations.</a>
<a href="#39" id="39">In practice, such sat-based approaches to symbolic model checking can prove much more efficient than {a mathematical formula}OBDD<-based approaches on some instances, which coheres with the fact that the succinctness of {a mathematical formula}OBDD< and the succinctness of CNF are incomparable [53].</a>
<a href="#40" id="40">Interestingly, when T is represented as a full disjunctive closure of a class {a mathematical formula}L of propositional representations, stable by uniform renaming, and satisfying CO and CD, both the computation of {a mathematical formula}∃Y.T|γX (resp.</a>
<a href="#41" id="41">{a mathematical formula}∃Y.T|γX′) and the enumeration of its models can be achieved in polynomial time (in the size of the input plus the size of the output).</a>
<a href="#42" id="42">Contrastingly, no response-time guarantee can be ensured in the general case for computing a single model when T is represented as a CNF formula.</a>
<a href="#43" id="43">Thus, for each of the applications above, considering full disjunctive closures for the representation purpose can prove to be a reasonable choice.</a>
</body>
</html>