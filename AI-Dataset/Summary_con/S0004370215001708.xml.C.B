<html>
<head>
<meta name="TextLength" content="SENT_NUM:53, WORD_NUM:1165">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have argued that the standard definition of certain answers in the database literature has a number of deficiencies, and proposed a new approach to handling queries over incomplete databases.</a>
<a href="#1" id="1">Its key features are as follows.</a>
<a href="#2" id="2">Certain answers can be defined at two different levels: as (database) objects, or as knowledge we possess about query answers with certainty.</a>
<a href="#3" id="3">The proposed framework, that applies to multiple data models, defines both types of certain answers as greatest lower bounds in orderings that capture the level of informativeness.</a>
<a href="#4" id="4">It also leads to a proper definition of representation systems for query answers.</a>
<a href="#5" id="5">If the semantics of query answering is chosen properly, then the process of finding certain answers is reduced to query evaluation, at both object and knowledge level.</a>
<a href="#6" id="6">Furthermore, the knowledge level is crucial for obtaining results at the object level.</a>
<a href="#7" id="7">This tells us that with the right choice of semantics, no new tools are needed for computing query answers and one can rely on the standard database query evaluation engine.</a>
<a href="#8" id="8">It also tells us that using the traditional way of finding certain answers only makes sense under owa, and with restricted representation systems.</a>
<a href="#9" id="9">In general, certain answers as knowledge give us more information than certain answers as objects.</a>
<a href="#10" id="10">The next step is to use the general framework of this paper to provide efficient techniques for producing query answers with certainty guarantees.</a>
<a href="#11" id="11">There are three directions one can pursue.</a>
<a href="#12" id="12">Efficient evaluation procedures for large classes of queries So far, such techniques have mainly concentrated on finding classes of queries where naïve evaluation works [2], [21].</a>
<a href="#13" id="13">Our framework lets us shift focus and concentrate on finding proper query semantics to ensure the basic principle of preserving informativeness.</a>
<a href="#14" id="14">One way to approach this is to use the fact that the certain answer query {a mathematical formula}certO(Q) preserves informativeness (Proposition 8).</a>
<a href="#15" id="15">One can then look for evaluation procedures that are guaranteed to produce results which are below {a mathematical formula}certO(Q,D) in the informativeness ordering on the answers.</a>
<a href="#16" id="16">If there is an efficient procedure with such properties, then it gives us an efficient way of producing query answers with certainty guarantees.</a>
<a href="#17" id="17">Similar ideas have been tried before, for relational algebra queries [40] and for SQL queries under the three-valued logic approach that SQL uses [38].</a>
<a href="#18" id="18">Approaches of [40], [38] were tailored for specific languages, and likewise had certainty guarantees tailored to specific requirements of those languages.</a>
<a href="#19" id="19">Our general frameworks should let us find general schemes of generating efficient evaluation procedures for different languages and different correctness requirements.</a>
<a href="#20" id="20">Note also that the procedure of [38] for SQL queries uses three-valued logic for reasoning.</a>
<a href="#21" id="21">Evaluation algorithms of a similar nature have been explored in the knowledge base literature [41], sometimes even using database evaluation techniques [42].</a>
<a href="#22" id="22">While not directly applicable to relational databases, the connection is worth studying, especially for representing certain answers as knowledge.</a>
<a href="#23" id="23">Easy to understand representation mechanisms for query answers Our results suggest that it may be easier – and perhaps more natural sometimes – to produce certain answers in the form of knowledge rather than objects.</a>
<a href="#24" id="24">This of course has been explored in the database literature.</a>
<a href="#25" id="25">One of the early ideas was to use minimal disjunctive answers, cf.</a>
<a href="#26" id="26">[43], incorporating disjunctions into query answers.</a>
<a href="#27" id="27">An analog of those in the order-based setting is finding not the greatest lower bound of a set X but rather a finite set {a mathematical formula}X0 such that every element of X is above some element of {a mathematical formula}X0.</a>
<a href="#28" id="28">A more expressive mechanism is that of conditional tables.</a>
<a href="#29" id="29">Already in [2] it was shown that under cwa they form a strong representation system.</a>
<a href="#30" id="30">Conditional tables, however, as explained earlier, are essentially FO formulae, from a rather bizarre fragment, that are simply made to look a bit like tables.</a>
<a href="#31" id="31">Thus, mechanisms like disjunctive answers are preferable as they are much easier to understand, but we are still very far from having a good understanding of the expressiveness of various representation mechanisms.</a>
<a href="#32" id="32">We now give a couple of examples showing that simple representation mechanisms can be quite useful, and an alternative to hard-to-understand conditional tables.</a>
<a href="#33" id="33">Take a query {a mathematical formula}Q=R−S, and a database D with {a mathematical formula}RD={1,2} and {a mathematical formula}SD={3,⊥}.</a>
<a href="#34" id="34">Under cwa, we have {a mathematical formula}Q(〚D〛cwa)={{1,2},{1},{2}}.</a>
<a href="#35" id="35">If we take the greatest lower bound of these, then for {a mathematical formula}⪯cwa it simply does not exist, and for {a mathematical formula}⪯owa ordering, it is ∅, which is, incidentally, what a commercial DBMS would return if one runs this query in SQL, written as select r.a from r where r.a not in (select * from s).</a>
<a href="#36" id="36">This is of course yet another illustration that returning certain answers as objects is not always possible, and one needs to return certain answers as knowledge instead.</a>
<a href="#37" id="37">What sort of knowledge will depend, of course, on the representation system.</a>
<a href="#38" id="38">If we use the set of {a mathematical formula}∃Pos formulae, then we get essentially minimal disjunctive answers, as {a mathematical formula}Q(〚D〛cwa) can be described by {a mathematical formula}A(1)∨A(2).</a>
<a href="#39" id="39">If we consider the same query under owa, then {a mathematical formula}Q(〚D〛owa)={A|3∉A}.</a>
<a href="#40" id="40">Again, this is not representable by a single object: taking the greatest lower bound of {a mathematical formula}Q(〚D〛owa) results again in ∅, missing some valuable information.</a>
<a href="#41" id="41">If we use representation systems that allow negations of atomic formulae, then {a mathematical formula}¬A(3) will represent the certain answer properly.</a>
<a href="#42" id="42">This suggests that one needs a deeper study of certain answers as knowledge, concentrating on representations of answers that make sense to users.</a>
<a href="#43" id="43">Applications We explained that certain answers are the preferred way of dealing with incompleteness in many applications, including data integration, data exchange, ontology based query answering, and consistent query answering.</a>
<a href="#44" id="44">So far we have used the approach proposed here to understand query answering over incomplete relational databases (see Section 7.2 and [38]).</a>
<a href="#45" id="45">Our next goal is to use the same ideas to understand when we can make answering queries in the application scenarios easier.</a>
<a href="#46" id="46">In some cases, query answering in those scenarios is reduced to building a database (typically incomplete) and answering queries over it (e.g., in data exchange).</a>
<a href="#47" id="47">Then we can directly take advantage of techniques developed here.</a>
<a href="#48" id="48">One question is to identify cases when this can be done.</a>
<a href="#49" id="49">In other cases, most likely we would need to use Proposition 8 as the starting point, and look for approximations.</a>
<a href="#50" id="50">Note also that approximations are easier to find under cwa rather than owa, as is already evident in the case of relational queries [38].</a>
<a href="#51" id="51">Thus, using our approach to find good quality and computationally efficient answers may be more challenging in settings relying on owa (like ontology based query answering), although incorporating closed-world reasoning [44] can perhaps make finding approximate answers easier.</a>
<a href="#52" id="52">Other data models Yet another direction is to apply the framework to non-relational models, particularly semi-structured and XML, for which incompleteness has been studied extensively [45], [26], [46], [31], and beyond, to graph data and RDF, where only preliminary results have been established so far [47], [48].</a>
</body>
</html>