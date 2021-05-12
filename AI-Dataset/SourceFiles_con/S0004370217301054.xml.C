<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Distributed First Order Logic.
   </title>
   <abstract>
    Distributed First Order Logic (DFOL) has been introduced more than ten years ago with the purpose of formalising distributed knowledge-based systems, where knowledge about heterogeneous domains is scattered into a set of interconnected modules. DFOL formalises the knowledge contained in each module by means of first-order theories, and the interconnections between modules by means of special inference rules called bridge rules. Despite their restricted form in the original DFOL formulation, bridge rules have influenced several works in the areas of heterogeneous knowledge integration, modular knowledge representation, and schema/ontology matching. This, in turn, has fostered extensions and modifications of the original DFOL that have never been systematically described and published. This paper tackles the lack of a comprehensive description of DFOL by providing a systematic account of a completely revised and extended version of the logic, together with a sound and complete axiomatisation of a general form of bridge rules based on Natural Deduction. The resulting DFOL framework is then proposed as a clear formal tool for the representation of and reasoning about distributed knowledge and bridge rules.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The method of structuring complex knowledge-based systems in a set of largely autonomous modules has become common practice in several areas such as Semantic Web, Database, Linked Data, Ontologies, and Peer-to-Peer systems. In these practices, knowledge is often structured in multiple interacting sources and systems, hereafter indicated as local knowledge bases or simply knowledge bases (KBs). Several efforts have been devoted to provide a well-founded theoretical background able to represent and reason about distributed knowledge. Several examples can be found in well established areas of Database and Knowledge Representation such as federated and multi-databases [1], [2], [3], database and information integration [4], [5], [6], [7], [8], [9], database schema matching [10], and contextual reasoning [11], [12], [13]. Further examples can also be found in more recent areas of the Semantic Web, such as ontology matching [14], [15], ontology integration [16], [17], [18], ontology modularisation [19], [20], [21], linked data [22], [23], and in Peer-to-Peer systems [24], [25], [26], [27].
     </paragraph>
     <paragraph>
      The formalisms mentioned above share several aspects: they all focus on static and boolean knowledge{sup:1}; local knowledge is expressed using a (restricted form of) first-order language; each module is associated with a specific (first-order) language, called local language; the domains of interpretation of the different local languages can be heterogeneous; the same symbol in different local languages can have different interpretations; knowledge within the different modules is related through some form of cross-language axioms. Despite their commonalities, these formalisms are mainly tailored to the characterisation of specific phenomena of distributed knowledge. Little work exists on the definition of a general logic, comprehensive of a sound and complete calculus and of a rigorous investigation of its properties, as well as able to represent generic semantically heterogeneous distributed systems, based on first-order logic and comprised of heterogeneous domains.
     </paragraph>
     <paragraph>
      As a step towards the definition of such a logic, Distributed First Order Logic (DFOL) was introduced in [28]. As explained in detail in Section 5.5, the original DFOL was able to capture only limited interconnections between local KBs. Nonetheless, the idea presented in [28] of connecting different domains of interpretation by means of directional domain relations, and a number of unpublished efforts to substantially extend DFOL to increase its flexibility and expressiveness, have strongly influenced several frameworks which include Package-Based Description Logics (P-DL)[21], Distributed Description Logic (DDL)[18], and C-OWL[29].
     </paragraph>
     <paragraph>
      In this paper we overcome the limitations of the original formulation of DFOL and present a systematic account of a completely revised and extended version of the formalism, which was elaborated in conjunction with most of the efforts listed above. The unpublished elements described in this paper include: (i) a general version of bridge rules based on the introduction of arrow variables as a way to express general semantic relations between local KBs (Section 3); (ii) a notion of logical consequence between bridge rules (Section 4.4); (iii) a thorough investigation of the properties of DFOL (Section 3) and of how to use it to represent important types of relations between local KBs (Section 4); and (iv) a general sound and complete calculus able to capture the semantic relations enforced by arrow variables, to infer new bridge rules and to discover unsatisfiable distributed knowledge-based systems (Section 6).
     </paragraph>
     <paragraph>
      To make the presentation clearer, but also to show the generality of the approach, we informally describe, and then formalise using DFOL, two examples of distributed knowledge, namely reasoning with viewpoints, and information integration. This material is covered in Section 2 (informal presentation) and Example 5, Example 6, Example 8 (formalisation using DFOL).
     </paragraph>
     <paragraph>
      The extended version of DFOL presented in this paper is also used, in Section 5, as a framework for the encoding of different static and boolean knowledge representation formalisms grounded in first-order logic. In line with the work presented in [14] these formalisms are tailored to the representation of semantically heterogeneous distributed knowledge-base systems (e.g., ontologies, databases, and contexts) with heterogeneous domains.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Two explanatory examples
     </section-title>
     <paragraph>
      The examples introduced in this section are used throughout the paper to discuss and illustrate the ideas and the formalisation of DFOL we propose.
     </paragraph>
     <section label="2.1">
      <section-title>
       Reasoning with viewpoints
      </section-title>
      <paragraph label="Example 1">
       The magic boxConsider the scenario in Fig. 1a: there are two observers, {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2, each having a partial viewpoint of a box and of an indefinite number of balls. The balls can be black or white and the box is composed of six sectors, each possibly containing a ball. Balls can be inside the box or in the grey area outside the box. From their perspectives observers cannot distinguish the depth inside the box. Moreover they cannot see balls hidden behind other balls and balls located behind the box. Fig. 1b shows what {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 actually see in the scenario depicted in Fig. 1a.{sup:2}
      </paragraph>
      <paragraph>
       The magic box, together with the balls, represents a “complex” environment corresponding to the domain of the agents' local knowledge bases. The agents' points of view correspond to their local knowledge. The local knowledge of the agents is constrained one another by the fact that they describe views over the same environment. Assuming that we have a complete description of the box we can build the agents' local knowledge (bases) as views over this complete description. However, such a complete description is often not available. What we often have are only the partial views, and a set of constraints between these views, with no representation of the external world (in our example case, the entire box). In cases like this we need a logical formalism able to describe the point of view of the different agents ({a mathematical formula}Mr.1, and {a mathematical formula}Mr.2, in our example) and the constraints among these views, without having to represent the entire box as we see it in Fig. 1a. The formalism should be able to represent and reason about statements such as:
      </paragraph>
      <list>
       <list-item label="1.">
        “the domain of{a mathematical formula}Mr.1contains 3 balls and a box with 2 sectors”;
       </list-item>
       <list-item label="2.">
        “{a mathematical formula}Mr.2sees a black ball in the right sector”;
       </list-item>
       <list-item label="3.">
        “{a mathematical formula}Mr.1and{a mathematical formula}Mr.2agree on the colour of the balls they both see”;
       </list-item>
       <list-item label="4.">
        “if{a mathematical formula}Mr.1sees an empty box, then{a mathematical formula}Mr.2sees an empty box too”;
       </list-item>
       <list-item label="5.">
        “if{a mathematical formula}Mr.2sees 3 balls in the box, then the leftmost is also seen by{a mathematical formula}Mr.1”.
       </list-item>
      </list>
      <paragraph>
       This example involves, in a very simple form, a number of crucial aspects of distributed knowledge representation: first, it deals with heterogeneous local domains which correspond to the different sets of balls in the different viewpoints. Second, it has to do with cross-domain identity. In fact, we need to represent the connections between the perceptions of the balls by each agent, without having an objective model that completely and correctly describes all the objects (balls) present in the box. An example is statement 5 above. Third, we have heterogeneous local properties. In our example {a mathematical formula}Mr.1 sees a box composed of two sectors, while for {a mathematical formula}Mr.2 the box is composed of three sectors. Thus {a mathematical formula}Mr.2 has a notion of “a ball being in the central sector” which {a mathematical formula}Mr.1 does not have. Fourth, it deals with constrained viewpoints. The viewpoints of the agents are, in fact, not independent, since they are the result of they observing the environment. Thus, if {a mathematical formula}Mr.1 sees an empty box, then {a mathematical formula}Mr.2 is constrained to see an empty box too, as described in statement 4 above.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Mediator-based information integration
      </section-title>
      <paragraph>
       Information integration is often based on architectures that make use of a mediator[30], as in the following example.
      </paragraph>
      <paragraph label="Example 2">
       Consider the databases of two fruit sellers, {a mathematical formula}Sel.1 and {a mathematical formula}Sel.2, depicted in Fig. 2. The information about fruits sold by {a mathematical formula}Sel.1 is contained in two relations {a mathematical formula}Available(fruit,qty), and {a mathematical formula}Price(fruit,x) with the intuitive meaning that a quantity qty of {a mathematical formula}fruit is available for selling and that its price is fixed to x Euros per kilogram (Eur/Kg for short). The value of x could be a number or an interval {a mathematical formula}[x1,x2], expressing the fact that a specific price has not been fixed yet but it is contained within {a mathematical formula}x1 and {a mathematical formula}x2. {a mathematical formula}Sel.2, instead, stores information about fruit prices in a single relation {a mathematical formula}Available(fruit,qty,x), where x indicates the total price of quantity qty of {a mathematical formula}fruit, and not its price per kilo. A mediator m collects the data of {a mathematical formula}Sel.1 and {a mathematical formula}Sel.2 and integrates them into a single relation {a mathematical formula}Offer(fruit,qty,x), meaning that a quantity qty of {a mathematical formula}fruit is available at price x Euros per kilo from (at least) one of the two sellers. Customers looking for information about fruit prices can submit a query to the mediator, instead of asking the two sellers separately as shown in Fig. 2.
      </paragraph>
      <paragraph>
       A system that integrates these informations, and that supports query-answering must be able to represent the heterogeneous schemata and domains of the three subsystems m, {a mathematical formula}Sel.1, and {a mathematical formula}Sel.2 and their relations. In particular the formalism should be able to represent the following facts:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Sel.1 sells “apples”, whereas {a mathematical formula}Sel.2 and m represent the domain of apples at a greater granularity, and are able to offer specific varieties of apples (ranging among Delicious and Granny Smith in our example). Moreover, for the sake of the example, the “apples” of {a mathematical formula}Sel.1 correspond to both “Delicious” and “GrannySmith” in the mediator. This justifies the disjunctive statement retrieved by the mediator as a “translation” of the statements about apples contained in the database of {a mathematical formula}Sel.1;
       </list-item>
       <list-item label="2.">
        total prices of {a mathematical formula}Sel.2 are transformed in prices per kilo in m to be homogeneous with price format of {a mathematical formula}Sel.1;
       </list-item>
       <list-item label="3.">
        m is not interested in retrieving information about fruits whose price is not yet defined (lemons in our case);
       </list-item>
       <list-item label="4.">
        the information goes from {a mathematical formula}Sel.1 (resp. {a mathematical formula}Sel.2) to m and not from the mediator to the sellers.
       </list-item>
      </list>
      <paragraph>
       Again, this example involves heterogeneous local domains and cross-domain identity, as described in statement 1 above. Moreover, it involves heterogeneous local properties represented by the different relations, which are nonetheless constrained by the fact that they all represent the availability of fruit at a certain price. Thus, for example, if 10 Kg of oranges cost 20 Euros in the database of {a mathematical formula}Sel.2, then oranges cost 2 Euros per Kilo in the database of the mediator. In addition, information is required to be directional: in our example it flows from the sellers to the mediator and not vice-versa, since the sellers must be prevented to retrieve knowledge about potential competitors that could be stored in the mediator.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Syntax and semantics of DFOL
     </section-title>
     <paragraph>
      In this section we provide the syntax and semantics of Distributed First Order Logic (DFOL). They are based on the syntax and semantics of first-order logic and Local Models Semantics presented in [13] to the case where each local KB is described by means of a first-order language.
     </paragraph>
     <section label="3.1">
      <section-title>
       DFOL syntax
      </section-title>
      <paragraph>
       Let {a mathematical formula}{Li}i∈I (hereafter {a mathematical formula}{Li}) be a family of first-order languages defined over a non empty set I of indexes. For the sake of simplicity we assume, without loss of generality, that all the languages {a mathematical formula}Li contain the same set X of infinitely many variables. Each language {a mathematical formula}Li is the language used by the i-th local knowledge base to partially describe the world from its own perspective. For instance, in the magic box example {a mathematical formula}I={1,2}.
      </paragraph>
      <paragraph>
       In DFOL, each {a mathematical formula}Li is a first-order language with equality, extended with a new set of symbols, called arrow variables, which are of the same syntactic type as constants and standard individual variables (hereafter often called non-arrow variables). Formally, for each variable {a mathematical formula}x∈X, and each index {a mathematical formula}i,j∈I, with {a mathematical formula}i≠j, the signature of {a mathematical formula}Li is extended to contain the two arrow variables {a mathematical formula}x→j and {a mathematical formula}xj→.
      </paragraph>
      <paragraph>
       The arrow variables {a mathematical formula}x→j and {a mathematical formula}xj→ in {a mathematical formula}Li intuitively denote an object in the domain of interpretation of {a mathematical formula}Li that corresponds to the object x in the domain of {a mathematical formula}Lj. The difference between {a mathematical formula}x→j and {a mathematical formula}xj→ will become clearer later in the paper. We often use {a mathematical formula}x→ to denote a generic arrow variable (that is, either of the form {a mathematical formula}x→j or {a mathematical formula}xj→).
      </paragraph>
      <paragraph>
       Terms of {a mathematical formula}Li, also called i-terms, are recursively defined as in first-order logic starting from the set of constants, variables, and arrow variables, and by recursively applying function symbols. Formally:
      </paragraph>
      <list>
       <list-item label="1.">
        Any constant, variable, and arrow variable of {a mathematical formula}Li is a i-term.
       </list-item>
       <list-item label="2.">
        If f is a function symbol of arity n in {a mathematical formula}Li and {a mathematical formula}t1,…,tn are i-terms, then {a mathematical formula}f(t1,...,tn) is a i-term.
       </list-item>
      </list>
      <paragraph>
       Formulas of {a mathematical formula}Li, called i-formulas, are defined as in first-order logic, with the discriminant that we only quantify over non-arrow variables. Formally:
      </paragraph>
      <list>
       <list-item label="1.">
        If P is a n-ary predicate symbol in {a mathematical formula}Li and {a mathematical formula}t1,…,tn are i-terms, then {a mathematical formula}P(t1,...,tn) is a i-formula.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}t1 and {a mathematical formula}t2 are i-terms, then {a mathematical formula}t1=t2 is a i-formula.
       </list-item>
       <list-item label="3.">
        If ϕ and ψ are i-formulas, then ¬ϕ, {a mathematical formula}ϕ⊃ψ, {a mathematical formula}ϕ∧ψ, {a mathematical formula}ϕ∨ψ, are i-formulas.
       </list-item>
       <list-item label="4.">
        If ϕ is a formula and x is a non-arrow variable, then {a mathematical formula}∀xϕ and {a mathematical formula}∃xϕ are i-formulas.
       </list-item>
      </list>
      <paragraph>
       Examples of i-terms are x, c, {a mathematical formula}x→j, {a mathematical formula}f(c,d), and {a mathematical formula}f(xj→,f(g(d))). Examples of i-formulas are {a mathematical formula}P(x,y,z), {a mathematical formula}P(x→j,w,a), {a mathematical formula}⊥⊃P(f(c),d), {a mathematical formula}∀x.P(x,y), {a mathematical formula}∀x.x=xj→, {a mathematical formula}∃y.P(y,x→j). Instead {a mathematical formula}∀xj→.P(xj→) is not an i-formula as we do not allow quantification on arrow variables.
      </paragraph>
      <paragraph>
       A i-formula ϕ is closed if it does not contain arrow variables and all the occurrences of the variable x in ϕ are in the scope of a quantifier ∀x or ∃x. ϕ is open if it is not closed. A variable x occurs free in a formula if x occurs in ϕ not in the scope of a quantifier ∀x or ∃x. Notice that x, {a mathematical formula}x→i and {a mathematical formula}xi→ are different variables, and therefore x does not occur free in an expression of type {a mathematical formula}p(x→i). The notation {a mathematical formula}ϕ(x) is used to denote the formula ϕ and the fact that the free variables of ϕ are {a mathematical formula}x={x1,…,xn}.
      </paragraph>
      <paragraph>
       Languages {a mathematical formula}Li and {a mathematical formula}Lj are not necessarily disjoint and the same formula ϕ can occur in different languages with different meanings. A labelled formula is a pair {a mathematical formula}i:ϕ{sup:3} and is used to denote that ϕ is a formula in {a mathematical formula}Li. Given a set of i-formulas Γ, we use {a mathematical formula}i:Γ as a shorthand for the set of labelled formulas {a mathematical formula}{i:γ|γ∈Γ}. Note that we do not admit formulas which are composed of symbols coming from different alphabets. Thus {a mathematical formula}1:P(x)∧2:a=b and {a mathematical formula}∀x1:P(x) are not well-formed labelled formulas in DFOL.
      </paragraph>
      <paragraph label="Example 3">
       Languages for the magic boxThe DFOL languages {a mathematical formula}L1 and {a mathematical formula}L2 that describe the knowledge of {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 in the magic box example are defined as follows.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}L1 contains an infinite set of constants {a mathematical formula}b1, {a mathematical formula}b2, … used to denote balls, two constants l and r used to indicate the left-hand side and right-hand side positions in the box, the binary predicate {a mathematical formula}inbox(x,y) which stands for “the ball x is in the position y of the box”, and the unary predicates {a mathematical formula}white(x) and {a mathematical formula}black(x) for “the ball x is white” (resp. black).
       </list-item>
       <list-item label="•">
        {a mathematical formula}L2 is obtained by extending {a mathematical formula}L1 with a new constant c for the centre position in the box.
       </list-item>
      </list>
     </section>
     <section label="3.2">
      <section-title>
       Denoting cross-domain objects
      </section-title>
      <paragraph>
       DFOL associates different domains of interpretation to the local knowledge bases; therefore it needs a mechanism to denote cross-domain identity. Arrow variables provide such a mechanism, and are used to refer to counterpart objects which belong to other domains. In particular, arrow variables of the form {a mathematical formula}xj→ and {a mathematical formula}x→j occurring in a i-formula are used to denote an object in the domain of interpretation of {a mathematical formula}Li, which corresponds to the object denoted by x in the domain of {a mathematical formula}Lj.
      </paragraph>
      <paragraph>
       Consider, for instance, statement 3 at page 3. The formalisation of this statement requires the ability to represent a ball that is seen by both observers. Since DFOL represents the partial viewpoints of {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2, each one with its own domain of interpretation, there is no object that directly represents a ball seen by both. Indeed, consider the black ball in the corner of the magic box represented at the top of Fig. 3. {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 have their own representation of this ball in their different domains, as graphically depicted at the bottom of Fig. 3. The way we represent the connection between these two different objects is by using an arrow variable, say {a mathematical formula}x→2, interpreted in the domain of {a mathematical formula}Mr.1 which corresponds to the ball denoted by x seen by {a mathematical formula}Mr.2. We can then predicate that both {a mathematical formula}x→2 and x are black using the formulas {a mathematical formula}1:black(x→2) and {a mathematical formula}2:black(x). The precise way in which DFOL binds the interpretation of {a mathematical formula}x→2 and x in the different domains will become clear with the definition of Assignment (Definition 4).
      </paragraph>
      <paragraph>
       The notion of arrow variable introduced here is connected to the notion of counterparts introduced by Lewis in [34]. Roughly speaking, the language of Lewis' Counterpart Theory contains a binary predicate {a mathematical formula}C(x,y) meaning that x is the counterpart of y, where x and y are supposed to denote two objects in two different possible worlds. In DFOL, we have local knowledge bases with different local languages instead of possible worlds. Therefore, we cannot explicitly state that x is counterpart of y, when x and y belong to two different languages, but only state it implicitly by means of arrow variables. That is, we can name in the language {a mathematical formula}Li a counterpart of x in {a mathematical formula}Lj by using the arrow variables {a mathematical formula}xj→ and {a mathematical formula}x→j.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       DFOL semantics
      </section-title>
      <paragraph>
       The semantics of a family of DFOL languages {a mathematical formula}{Li} is defined by associating a set of interpretations, called local models, to each {a mathematical formula}Li in {a mathematical formula}{Li} and by relating objects in different domains via, so-called, domain relations. This semantics is an extension of Local Models Semantics as defined in [13]. If we look at the knowledge contained in a knowledge base i we can distinguish three cases. First, i can be complete, that is, for each formula {a mathematical formula}ϕ∈Li either ϕ or ¬ϕ belongs to the (deductive closure of the) knowledge base; second, it can be incomplete, if there exist at least a formula ϕ such that neither ϕ or ¬ϕ belongs to it; third, it can be inconsistent, that is, both ϕ and ¬ϕ belong to it. To represent these three possible statuses, each i is associated with a (possibly empty) set of local models. That is, each i is associated with an epistemic state. A singleton corresponds to a complete KB, the empty set corresponds to an inconsistent KB, whereas all the other sets correspond to an incomplete KB. While completeness w.r.t. the entire language {a mathematical formula}Li may be unrealistic, and even undesirable, it may be a good property to require for certain types of formulas, as we will see in the following paragraphs. To characterise the portion of knowledge upon which i has complete knowledge we introduce the notion of complete sub-language {a mathematical formula}Lic and we restrict the definition of complete knowledge to the formulas of {a mathematical formula}Lic. Let {a mathematical formula}Lic be a sub-language of {a mathematical formula}Li built from a subset of constants, functional symbols, and predicate symbols of {a mathematical formula}Li, including equality, plus the set of arrow and not-arrow variables of {a mathematical formula}Li. We call {a mathematical formula}Lic the complete sub-language of {a mathematical formula}Li. Complete terms and complete formulas are terms and formulas of {a mathematical formula}Lic. Otherwise they are called non complete. Note that in DFOL {a mathematical formula}Lic must contain the equality predicate as we impose that each i-th knowledge base is able to evaluate whether two objects are equal or not. Additional constants, functional symbols, or predicates can be added to {a mathematical formula}Lic to represent domain-specific complete knowledge. For instance, in the magic box example we may assume that {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 have complete knowledge about the position of the balls. That is, they know if a ball is in a slot or not. On the contrary, assume that {a mathematical formula}Mr.2's view over the box is partially concealed by a big wall, as depicted in Fig. 4. In this scenario {a mathematical formula}Mr.2 is able to see one box sector and knows that there are two sectors behind the wall with balls inside and outside the box. In this case {a mathematical formula}Mr.2 has complete knowledge about the left hand side position of the box but is uncommitted to whether there are balls in the sectors behind the wall. This is formalised by including the formulas {a mathematical formula}inbox(b,l) into {a mathematical formula}L2c for all the balls b in the language of {a mathematical formula}Mr.2, and by letting, e.g., sentences of the form {a mathematical formula}inbox(b,c) to be non complete, that is, true in some local model of {a mathematical formula}Mr.2 and false in others.
      </paragraph>
      <paragraph label="Definition 1">
       Set of local modelsA set of local models of {a mathematical formula}Li is a set of first-order interpretations of {a mathematical formula}Li on a (non empty) domain {a mathematical formula}domi, which agree on the interpretation of {a mathematical formula}Lic, the complete sub-language of {a mathematical formula}Li.
      </paragraph>
      <paragraph>
       The semantic overlap between different knowledge bases is explicitly represented in DFOL by means of domain relations.
      </paragraph>
      <paragraph label="Definition 2">
       Domain relationA domain relation{a mathematical formula}rij from {a mathematical formula}domi to {a mathematical formula}domj is a binary relation contained in {a mathematical formula}domi×domj.
      </paragraph>
      <paragraph>
       We often use the simpler expression domain relation from i to j to denote a domain relation {a mathematical formula}rij from {a mathematical formula}domi to {a mathematical formula}domj. We also use the functional notation {a mathematical formula}rij(d) to denote the set {a mathematical formula}{d′∈domj|〈d,d′〉∈rij}.
      </paragraph>
      <paragraph>
       A domain relation from i to j illustrates how the j-th knowledge base represents the domain of the i-th knowledge base in its own domain. Therefore, a pair {a mathematical formula}〈d,d′〉 being in {a mathematical formula}rij means that, from the point of view of j, d in {a mathematical formula}domi is the representation of {a mathematical formula}d′ in {a mathematical formula}domj. Thus, {a mathematical formula}rij formalises j's subjective point of view on the relation between {a mathematical formula}domi and {a mathematical formula}domj, and not an absolute and objective point of view; this implies that {a mathematical formula}〈d,d′〉∈rij must not be read as if d and {a mathematical formula}d′ were the same object in a domain shared by i and j. This latter fact could only be formalised by an external (above, meta) observer to both i and j.
      </paragraph>
      <paragraph>
       Domain relations are not symmetric by default. This represents the fact that the point of view of j over the domain of i may differ from the point of view of i over the domain of j, which may even not exist. For instance, in the mediator system example, it is plausible to impose that m has a representation of the domains of {a mathematical formula}Sel.1 and {a mathematical formula}Sel.2, in its own domain while the opposite is prevented. Domain relations are conceptually analogous to conversion functions between semantic objects, as defined in [35].
      </paragraph>
      <paragraph>
       Specific relations between the domains of different knowledge bases can be modelled by adding constraints about the form of {a mathematical formula}rij. For instance, two knowledge bases with different but isomorphic representations of the same domain can be modelled by imposing {a mathematical formula}rij=rji−1. Likewise, completely unrelated domains can be represented by imposing {a mathematical formula}rij=rji=∅. Transitive mappings between the domains of three knowledge bases i, j and k can be represented by imposing {a mathematical formula}rik=rij∘rjk. Moreover, if {a mathematical formula}domi and {a mathematical formula}domj are ordered according to two ordering relations {a mathematical formula}&lt;i and {a mathematical formula}&lt;j respectively, then a domain relation that satisfies the following property{a mathematical formula} formalises a mapping which preserves the ordering. An example of this last property is a domain relation that captures a currency exchange function. Further constraints on {a mathematical formula}rij are discussed in Section 4.
      </paragraph>
      <paragraph label="Definition 3">
       DFOL modelA DFOL model, or simply a model{a mathematical formula}M (for {a mathematical formula}{Li}) is a pair {a mathematical formula}M=〈{Mi},{rij}〉 where, for each {a mathematical formula}i,j∈I, {a mathematical formula}Mi is a set of local models for {a mathematical formula}Li, and {a mathematical formula}rij is a domain relation from i to j.
      </paragraph>
      <paragraph label="Example 4">
       A DFOL model for the scenario shown in Fig. 1 is a 4-tuple {a mathematical formula}M=〈{m1},{m2},r12,r21〉, where {a mathematical formula}m1=〈{left,right,a,b,c},⋅I1〉 and {a mathematical formula}m2=〈{left,centre,right,a,b,c,d},⋅I2〉 with{a mathematical formula} Moreover, {a mathematical formula}r12={(c,a)} and {a mathematical formula}r21={(a,c)}.
      </paragraph>
      <paragraph label="Definition 4">
       AssignmentLet {a mathematical formula}M=〈{Mi},{rij}〉 be a model for {a mathematical formula}{Li} and {a mathematical formula}{Xi} be a family of sets such that {a mathematical formula}Xi contains all the non-arrow variables plus a subset of the arrow variables of {a mathematical formula}Li. An assignment a is a family {a mathematical formula}{ai} of functions {a mathematical formula}ai from {a mathematical formula}Xi to {a mathematical formula}domi which satisfies the following:
      </paragraph>
      <list>
       <list-item label="1.">
        if {a mathematical formula}ai(x→j) is defined, then {a mathematical formula}ai(x→j)∈rij−1(aj(x));
       </list-item>
       <list-item label="2.">
        if {a mathematical formula}ai(xj→) is defined, then {a mathematical formula}ai(xj→)∈rji(aj(x)).
       </list-item>
      </list>
      <paragraph>
       The definition above extends the classical notion of assignment given for first-order logic to deal with arrow variables. Intuitively, if the non-arrow variable x occurring in the j-th knowledge base is a placeholder for the element {a mathematical formula}d∈domj, then the occurrence of the arrow variable {a mathematical formula}x→j in a formula of the i-th knowledge base is a placeholder for an element {a mathematical formula}d′∈domi which is a pre-image (via {a mathematical formula}rij−1) of d. Analogously, the arrow variable {a mathematical formula}xj→ occurring in {a mathematical formula}i:ψ is a placeholder for any element {a mathematical formula}d″∈domi which is an image (via {a mathematical formula}rji) of d.
      </paragraph>
      <paragraph>
       An assignment {a mathematical formula}a′ is an extension of a, in symbols {a mathematical formula}a≤a′, if {a mathematical formula}ai(v)=d implies {a mathematical formula}ai′(v)=d for all the non-arrow and arrow variables v. Notationally, given an assignment a, a (non-arrow or arrow) variable x, and an element {a mathematical formula}d∈domi, we denote with {a mathematical formula}a(x:=d) the assignment obtained from a by letting {a mathematical formula}ai(x)=d.
      </paragraph>
      <paragraph label="Definition 5">
       Admissible assignmentAn assignment a is (strictly) admissible for a formula{a mathematical formula}i:ϕ if {a mathematical formula}ai assigns all (and only) the arrow variables occurring in ϕ. a is (strictly) admissible for a set of formulas Γ if it is (strictly) admissible for all {a mathematical formula}j:ϕ in Γ.
      </paragraph>
      <paragraph label="Definition 6">
       SatisfiabilityA formula {a mathematical formula}i:ϕ is satisfied by a DFOL model {a mathematical formula}M w.r.t. the assignment a, in symbols {a mathematical formula}M⊨i:ϕ[a], if
      </paragraph>
      <list>
       <list-item label="(i)">
        a is admissible for {a mathematical formula}i:ϕ; and
       </list-item>
       <list-item label="(ii)">
        for all {a mathematical formula}m∈Mi, {a mathematical formula}m⊨ϕ[ai] according to the classic definition of first-order satisfiability.
       </list-item>
      </list>
      <paragraph>
       With an abuse of notation we use the symbol ⊨ of satisfiability to denote both first-order satisfiability and DFOL satisfiability. The context will always make clear the distinction between the two.
      </paragraph>
      <paragraph>
       If we compare satisfiability of a formula in a DFOL model with the standard notion of satisfiability of a first-order formula in a first-order model we can observe three differences: first, assignments do not force all arrow variables to denote objects in the domain; second, we admit partial knowledge as we evaluate the satisfiability of a formula in a set of local models, rather than into a single one; third, we admit islands of inconsistency, by allowing some {a mathematical formula}Mi to be empty. In the following we analyse these three aspects one by one.
      </paragraph>
      <section label="3.3.1">
       <section-title>
        Satisfiability and arrow variables
       </section-title>
       <paragraph>
        Definition 4 requires assignments to be defined for all non-arrow variables, but not necessarily for all arrow variables.{sup:4} To avoid many of the ontological issues raised by free logics [36], where special truth conditions are given for {a mathematical formula}ϕ(t) when t does not denote any object in the domain, condition (i) in Definition 6 guarantees that satisfiability of {a mathematical formula}i:ϕ is defined over admissible assignments for {a mathematical formula}i:ϕ. This provides the first difference between satisfiability in DFOL and satisfiability in first-order logic, whose consequences are highlighted in the proposition below.
       </paragraph>
       <paragraph label="Proposition 1">
        Let{a mathematical formula}x→denote either{a mathematical formula}x→jor{a mathematical formula}xj→for some{a mathematical formula}j≠i, and{a mathematical formula}Mbe a DFOL model such that{a mathematical formula}Micontains a single first-order model m. Then the following properties hold:
       </paragraph>
       <list>
        <list-item label="(i)">
         if a is admissible for ϕ, then{a mathematical formula}M⊨i:ϕ[a]if and only if{a mathematical formula}m⊨ϕ[ai];
        </list-item>
        <list-item label="(ii)">
         if a is not admissible for{a mathematical formula}i:ϕ, then{a mathematical formula}M⊭i:ϕ[a]and{a mathematical formula}M⊭i:¬ϕ[a];
        </list-item>
        <list-item label="(iii)">
         if{a mathematical formula}ai(x→)is not defined, then{a mathematical formula}M⊭i:∃y.y=x→[a];
        </list-item>
        <list-item label="(iv)">
         {a mathematical formula}M⊨i:∀x.ϕ(x)[a]does not imply that{a mathematical formula}M⊨i:ϕ(x→)[a]for an arbitrary arrow variable{a mathematical formula}x→;
        </list-item>
        <list-item label="(v)">
         {a mathematical formula}M⊨i:¬ϕ[a](resp.,{a mathematical formula}M⊨i:ψ[a]) does not imply that{a mathematical formula}M⊨i:ϕ⊃ψ[a];
        </list-item>
        <list-item label="(vi)">
         {a mathematical formula}M⊨i:ϕ[a]does not imply that{a mathematical formula}M⊨i:ϕ∨ψ[a];
        </list-item>
        <list-item label="(vii)">
         if{a mathematical formula}M⊨i:ϕ⊃ψ[a], then{a mathematical formula}M⊨i:ϕ[a]implies that{a mathematical formula}M⊨i:ψ[a];
        </list-item>
        <list-item label="(viii)">
         {a mathematical formula}M⊨i:ϕ(x→)[a]implies that{a mathematical formula}M⊨i:∃x.ϕ(x)[a].
        </list-item>
       </list>
       <paragraph>
        Properties (i)–(viii) follow easily from Definition 6 and satisfiability of first-order formulas. Their proofs can be found in [37].
       </paragraph>
       <paragraph>
        Property (i) shows that DFOL satisfiability and first-order logic satisfiability coincide when {a mathematical formula}Mi is a single first-order model, provided that a is admissible for ϕ. Property (ii) states that {a mathematical formula}M does not satisfy any formula containing arrow variables {a mathematical formula}x→ which are not assigned by a, including formulas which have the form of classical tautologies. Property (iii) shows that the existence of an individual equal to {a mathematical formula}x→ is not always guaranteed in DFOL. Another important difference w.r.t. satisfiability in first-order logic is the fact that a universally quantified variable cannot be instantiated to an arbitrary term that contains arrow variables (property (iv)). The term must contain arrow variables {a mathematical formula}x→ that are assigned to some value by a. Properties (v)–(vi) state that the “introduction” of classical connectives in a formula cannot be done according to the rules for propositional logic, since extending a formula with new terms may introduce new arrow variables not assigned by a. Finally, properties (vii) and (viii) provide examples of first-order properties which still hold in DFOL. In particular (vii) shows that modus ponens is a sound inference rule for satisfiability in DFOL, while property (viii) shows that if ϕ holds for a certain arrow variable {a mathematical formula}x→, then there is an object of the world (i.e., ∃x) such that ϕ holds for it. All the above properties are consequences of the fact that {a mathematical formula}M⊨i:ϕ[a] does not only mean that all the models m in {a mathematical formula}Mi satisfy ϕ, but also that the arrow variables contained in ϕ actually denote elements in {a mathematical formula}domi.
       </paragraph>
      </section>
      <section label="3.3.2">
       <section-title>
        Satisfiability in a set of local models
       </section-title>
       <paragraph>
        Interpreting each {a mathematical formula}Li into a set of models, rather than into a single model, enables the formalisation of partial knowledge about values of terms and about truth values of formulas, as informally described at page 6. Proposition 2 describes the main effects of partial knowledge on the notion of satisfiability in DFOL.
       </paragraph>
       <paragraph label="Proposition 2">
        Let t be a non-complete term and ϕ and ψ be non-complete formulas of{a mathematical formula}Liwhich do not contain arrow variables. There exist a DFOL model{a mathematical formula}Mand an assignment a such as:
       </paragraph>
       <list>
        <list-item label="(i)">
         {a mathematical formula}M⊭i:x=t[a];
        </list-item>
        <list-item label="(ii)">
         {a mathematical formula}M⊨i:ϕ∨ψ[a]but neither{a mathematical formula}M⊨i:ϕ[a]nor{a mathematical formula}M⊨i:ψ[a];
        </list-item>
        <list-item label="(iii)">
         {a mathematical formula}M⊨i:∃x.ϕ(x)[a]but there is no{a mathematical formula}d∈domiwith{a mathematical formula}M⊨i:ϕ(x)[a(x:=d)].
        </list-item>
       </list>
       <paragraph>
        Properties (i)–(iii) are consequence of the fact that each {a mathematical formula}Mi in {a mathematical formula}M can contain more than one local model and the fact that t, ϕ and ψ are not complete. Their proofs can be found in [37].
       </paragraph>
       <paragraph>
        Properties (i) and (ii) emphasise that the value of non-complete terms and of disjuncts of non-complete formulas can be undetermined. An interesting instance of property (ii) is when {a mathematical formula}ψ=¬ϕ. In this case neither {a mathematical formula}M⊨i:ϕ[a] nor {a mathematical formula}M⊨i:¬ϕ[a], as in property (ii) of Proposition 1, but for a different reason: Proposition 1 states that a model {a mathematical formula}M does not satisfy a formula and its negation if assignment a is not complete for that formula. Instead, Proposition 2 states that {a mathematical formula}M does not satisfy a formula and its negation because it contains two local models, one satisfying ϕ and the other satisfying ¬ϕ. Finally, property (iii) states that the value of an existentially quantified variable can be unknown in a given knowledge base.
       </paragraph>
       <paragraph>
        Satisfiability of complete formulas w.r.t. a set of local models shares the same properties of satisfiability w.r.t. a single local model. This is a consequence of the fact that complete formulas are interpreted in the same way in all the local models in {a mathematical formula}Mi. Thus, Proposition 2 does not hold for complete formulas.
       </paragraph>
       <paragraph label="Proposition 3">
        Let t be a complete term and ϕ and ψ be complete formulas of{a mathematical formula}Liwhich do not contain arrow variables. For all models{a mathematical formula}M:
       </paragraph>
       <list>
        <list-item label="(i)">
         there is an assignment a such that{a mathematical formula}M⊨i:x=t[a];
        </list-item>
        <list-item label="(ii)">
         for all assignments a,{a mathematical formula}M⊨i:ϕ∨ψ[a]iff{a mathematical formula}M⊨i:ϕ[a]or{a mathematical formula}M⊨i:ψ[a];
        </list-item>
        <list-item label="(iii)">
         for all assignments a,{a mathematical formula}M⊨i:∃xϕ(x)[a]iff for some{a mathematical formula}d∈domi{a mathematical formula}M⊨i:ϕ(x)[a(x:=d)].
        </list-item>
       </list>
       <paragraph>
        Properties (i)–(iii) are a consequence of the fact that all the local models in {a mathematical formula}Mi agree on the interpretation of complete terms and complete formulas. Their proofs can be found in [37].
       </paragraph>
      </section>
      <section label="3.3.3">
       <section-title>
        Local inconsistency
       </section-title>
       <paragraph>
        A DFOL model {a mathematical formula}M where {a mathematical formula}Mi=∅ and {a mathematical formula}Mj≠∅ for some i and all {a mathematical formula}j≠i, represents local inconsistency of the i-th knowledge base. That is, a situation where one (or more) inconsistent knowledge base can coexist with consistent ones. This basic property of local inconsistence is formally described by the following proposition:
       </paragraph>
       <paragraph label="Proposition 4">
        Let{a mathematical formula}{Li}be a family of first-order languages. There exists a DFOL model{a mathematical formula}Mfor{a mathematical formula}{Li}such that{a mathematical formula}M⊨i:⊥but{a mathematical formula}M⊭j:⊥.
       </paragraph>
       <paragraph>
        To prove this statement consider a trivial model {a mathematical formula}M with {a mathematical formula}Mi=∅ and {a mathematical formula}Mj≠∅.
       </paragraph>
      </section>
     </section>
     <section label="3.4">
      <section-title>
       Denoting cross-KB constraints via bridge rules
      </section-title>
      <paragraph>
       The DFOL language described so far is able to represent the different local KBs, but cannot be used to express properties spanning over different knowledge bases. We enrich DFOL with this ability by introducing a class of “cross language formulas”. These formulas are an extension of the notion of bridge rule, first introduced in [38] in a proof-theoretic setting.
      </paragraph>
      <paragraph label="Definition 7">
       Bridge ruleGiven {a mathematical formula}i,i1,…,in∈I, a bridge rule from{a mathematical formula}i1,…,into i is an expression of the form {a mathematical formula}i1:ϕ1,…,in:ϕn→i:ϕ.
      </paragraph>
      <paragraph>
       A bridge rule can be seen as an axiom spanning between different logical theories (the local knowledge bases); it restricts the set of possible DFOL models to those in which {a mathematical formula}i:ϕ is a logical consequence of {a mathematical formula}i1:ϕ1,…,in:ϕn. We call {a mathematical formula}i1:ϕ1,…,in:ϕn the premises of the rule and {a mathematical formula}i:ϕ the conclusion. As an example, the bridge rule{a mathematical formula} represents the fact that the rightmost ball seen by {a mathematical formula}Mr.1 inside the box is seen also by {a mathematical formula}Mr.2.
      </paragraph>
      <paragraph label="Definition 8">
       Satisfiability of bridge rulesA model {a mathematical formula}Msatisfies a bridge rule {a mathematical formula}i1:ϕ1,…,in:ϕn→i:ϕ if for all the assignments a strictly admissible for {a mathematical formula}{i1:ϕ1,…,in:ϕn} the following holds:{a mathematical formula}
      </paragraph>
      <paragraph>
       Given a set of bridge rules {a mathematical formula}BR on the family of languages {a mathematical formula}{Li}, a {a mathematical formula}BR-model is a DFOL model for {a mathematical formula}{Li} that satisfies all the bridge rules of {a mathematical formula}BR.
      </paragraph>
      <paragraph>
       Definition 8 enables us to illustrate the difference between {a mathematical formula}i:ϕ⊃ψ and {a mathematical formula}i:ϕ→i:ψ. Let us disregard here the requirement of the existence of {a mathematical formula}a′ extension of a. {a mathematical formula}M⊨i:ϕ⊃ψ is satisfied if all local models {a mathematical formula}m∈Mi satisfy {a mathematical formula}ϕ⊃ψ. Instead, {a mathematical formula}M⊨i:ϕ→i:ψ is satisfied if, whenever all local models {a mathematical formula}m∈Mi satisfy ϕ it is also the case that all the local models {a mathematical formula}m∈Mi satisfy ψ. This difference is analogous to the one between {a mathematical formula}□(ϕ⊃ψ) and {a mathematical formula}□ϕ⊃□ψ in modal logic.
      </paragraph>
      <paragraph>
       Bridge rules, together with arrow variables, are used to relate cross-domain objects and knowledge. We illustrate this with the help of simple bridge rules, together with their intuitive reading:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The intuitive (and formal) reading of bridge rules (2)–(5) (and of bridge rules in general) can be expressed also in terms of query containment, given the appropriate transformation via domain relation. Let {a mathematical formula}‖P‖i be the answer of query {a mathematical formula}P(x) to a database i, then bridge rules (2)–(5) can be read as:{a mathematical formula}
      </paragraph>
      <paragraph>
       Definition 8 states that a bridge rule is satisfied if for all the assignments a strictly admissible for the premises of the rule, there exists an extension {a mathematical formula}a′ of a admissible for the conclusion. This implies that arrow variables occurring in the premise of a bridge rule are intended to be universally quantified, while arrow variables occurring in the consequence of a bridge rule are intended to be existentially quantified. In other words, if we use an arrow variable in the consequence of a bridge rule we impose the existence of certain mappings between domains. This happens in (3), where every element of P must have at least one translation into Q (via {a mathematical formula}rij), and in (5), where every element that in Q has at least a pre-image in P (via {a mathematical formula}rij). Conversely, if we use arrow variables in the premise of a bridge rule we restrict the way domain relations can map elements of the different domains without imposing the existence of certain mappings. This happens in (2), where the elements of P are not forced to have a translation into some elements of Q, and in (4), where the elements of Q are not forced to be the translation of some element of P.
      </paragraph>
      <paragraph label="Definition 9">
       Logical consequence{a mathematical formula}i:ϕ is a logical consequence of a set of formulas Γ w.r.t. a set of bridge rules {a mathematical formula}BR, in symbols {a mathematical formula}Γ⊨BRi:ϕ, if for every {a mathematical formula}BR-model {a mathematical formula}M and for every assignment a strictly admissible for Γ, the following holds:{a mathematical formula}
      </paragraph>
      <paragraph>
       DFOL logical consequence bears similarities and differences w.r.t. logical consequence for first-order logic. Focusing on the similarities, we can observe that if we restrict to a single knowledge base i, and we consider a fixed set of arrow variables, for which we assume the existence of an admissible assignment, then the behaviour of logical consequence in DFOL turns out to be similar to that of first-order logic, as shown by the following proposition:
      </paragraph>
      <paragraph label="Proposition 5">
       <section-title>
        Basic properties of logical consequence
       </section-title>
      </paragraph>
      <list>
       <list-item label="(i)">
        Reflexivity:{a mathematical formula}Γ,i:ϕ⊨BRi:ϕ;
       </list-item>
       <list-item label="(ii)">
        Weak monotonicity: if{a mathematical formula}Γ⊨BRi:ϕ, and Σ is a set of formulas whose arrow variables either occur in Γ or do not occur in{a mathematical formula}i:ϕ, then{a mathematical formula}Γ,Σ⊨BRi:ϕ;
       </list-item>
       <list-item label="(iii)">
        Cut: if{a mathematical formula}Γ⊨BRi:ϕand{a mathematical formula}Γ,i:ϕ⊨BRj:ψ, then{a mathematical formula}Γ⊨BRj:ψ;
       </list-item>
       <list-item label="(iv)">
        Extension of first-order logical consequence: Let{a mathematical formula}BRbe an empty set of bridge rules, and Γ be a set of i-formulas. We have that{a mathematical formula}where{a mathematical formula}x1→,…,xn→are the arrow variables occurring in ϕ but not in Γ, and{a mathematical formula}i:Γis used to denote the set{a mathematical formula}{i:ϕ|ϕ∈Γ}. If there are no arrow variables occurring only in ϕ and not in Γ, then(6)reduces to{a mathematical formula}
       </list-item>
      </list>
      <paragraph label="Proof">
       Properties (i)–(iii) are consequences of Definition 9. Concerning item (iv), we prove here the simplified version {a mathematical formula}Γ⊨ϕ if and only if {a mathematical formula}i:Γ⊨BRi:ϕ. The proof of the general case shown in Equation (6) is similar.
      </paragraph>
      <list>
       <list-item label="•">
        The fact that {a mathematical formula}Γ⊨ϕ implies {a mathematical formula}i:Γ⊨BRi:ϕ is a consequence of the fact that each {a mathematical formula}Mi is a set of first-order models for {a mathematical formula}Li.
       </list-item>
       <list-item label="•">
        Assume that {a mathematical formula}i:Γ⊨BRi:ϕ. Since {a mathematical formula}BR is empty, ϕ does not contain new arrow variables, and since Γ is a set of i-formulas, we can rewrite Definition 9 as: for all DFOL models {a mathematical formula}M, {a mathematical formula}Mi⊨Γ[a] implies {a mathematical formula}Mi⊨ϕ[a]. Let m be an arbitrary first-order model for {a mathematical formula}Li. Among all the possible DFOL models there is surely one such that {a mathematical formula}Mi={m}. Thus {a mathematical formula}m⊨Γ implies {a mathematical formula}m⊨ϕ and therefore {a mathematical formula}Γ⊨ϕ. □
       </list-item>
      </list>
      <paragraph>
       The key point in proving that {a mathematical formula}i:Γ⊨BRi:ϕ implies {a mathematical formula}Γ⊨ϕ is the fact that we can consider arbitrary DFOL models, and therefore also models such that {a mathematical formula}Mi={m}. This assumption cannot be made when {a mathematical formula}BR is not empty, as we need to restrict to specific classes of {a mathematical formula}BR-models. In other words, as soon as we consider different local knowledge bases, which interact via bridge rules, the behaviour of logical consequence in DFOL differs from that of logical consequence in first-order logic, even if we restrict to “safe” sets of arrow variables or no arrow variables at all. An important difference with first-order logic is given by the fact that the deduction theorem does not hold in the general case:
      </paragraph>
      <paragraph label="Proposition 6">
       Let{a mathematical formula}BRbe an arbitrary set of bridge rules, and{a mathematical formula}i:ϕbe a formula whose arrow variables occur entirely in Γ.{a mathematical formula}Γ,i:ϕ⊨BRi:ψdoes not imply{a mathematical formula}Γ⊨BRi:ϕ⊃ψ.
      </paragraph>
      <paragraph label="Proof">
       Let us assume that {a mathematical formula}Γ,i:ϕ⊨BRi:ψ holds and let us pick a {a mathematical formula}BR-model {a mathematical formula}M such that {a mathematical formula}Γ⊨BRi:ϕ⊃ψ does not hold. In particular let model {a mathematical formula}M be a {a mathematical formula}BR-model such that {a mathematical formula}M⊨BRΓ but {a mathematical formula}M⊭BRi:ϕ. Assume in particular that {a mathematical formula}Mi contains two local models {a mathematical formula}m1 and {a mathematical formula}m2 such that {a mathematical formula}m1⊨ϕ, {a mathematical formula}m2⊨¬ϕ, and both {a mathematical formula}m1 and {a mathematical formula}m2 satisfy ¬ψ. Since {a mathematical formula}BR is an arbitrary set of bridge rules we are guaranteed that we can perform this construction. Model {a mathematical formula}M is the counterexample we need to falsify {a mathematical formula}Γ⊨BRi:ϕ⊃ψ. In fact, it satisfies Γ but falsifies {a mathematical formula}ϕ⊃ψ because of {a mathematical formula}m1. □
      </paragraph>
      <paragraph>
       Note that, if {a mathematical formula}i:ϕ is a complete formula, or the class of {a mathematical formula}BR-models are such that all {a mathematical formula}m∈Mi satisfy {a mathematical formula}ϕ⊃ψ, the counter-example shown in the proof above cannot be built and we can prove that the deduction theorem holds (modulo arrow variables) using property (iv) in Proposition 5. We can therefore conclude that bridge rules, used together with assumptions which consist of partial knowledge, are the reason of the failure of the deduction theorem in DFOL.
      </paragraph>
      <paragraph>
       Another important characteristics of logical consequence in DFOL is the fact that it preserves local inconsistency, without making it global.
      </paragraph>
      <paragraph label="Proposition 7">
       Let{a mathematical formula}BRbe an arbitrary set of bridge rules,{a mathematical formula}i:⊥⊭BRj:⊥.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}BR is an arbitrary set of bridge rules, we can assume that the model used to validate Proposition 4 is a {a mathematical formula}BR-model. Thus {a mathematical formula}i:⊥⊭BRj:⊥.
      </paragraph>
      <paragraph>
       Finally, from the definition of admissible assignment, we can see that an arrow variable {a mathematical formula}x→j which occur in an i-formula represents the pre-image (via {a mathematical formula}rij−1) of a variable x in j, while an arrow variable {a mathematical formula}yi→ occurring in a formula with index j represents an image of y in i (again via {a mathematical formula}rij). This means that if {a mathematical formula}y=x→j holds in i then {a mathematical formula}yi→=x holds in j. A similar property holds for {a mathematical formula}rji.
      </paragraph>
      <paragraph label="Proposition 8">
       {a mathematical formula}i:y=x→j⊨BRj:yi→=xand{a mathematical formula}j:x=yi→⊨BRi:x→j=y.
      </paragraph>
      <paragraph>
       Note that the proposition above, whose proof can be found in [37], states a logical property of arrow variables which depends upon the semantics of arrow variables, and not upon the form of the domain relation. Additional logical properties involving arrow variables, instead, hold for specific sets of domain relations. These will be illustrated in the next section.
      </paragraph>
      <paragraph>
       Finally, bridge rules enjoy the so-called directionality property. Namely they allow to transfer knowledge from the premises to the conclusion with no back-flow of knowledge in the opposite direction. More formally: given a set {a mathematical formula}BR of bridge rules such that k does not appear in the conclusion of a bridge rule neither as the index of the conclusion nor as an index of an arrow variable, then {a mathematical formula}Γ⊨BRk:ϕ iff {a mathematical formula}Γk⊨ϕ. The proof of this statement is given in Section 6 in a proof theoretical manner (see Proposition 11).
      </paragraph>
      <paragraph>
       We conclude the presentation of the semantics of DFOL by showing how we can use it to formalise the Magic box scenario and the Mediator scenario introduced in Section 2.
      </paragraph>
      <paragraph label="Example 5">
       A formalisation of the magic boxWe start from the languages {a mathematical formula}L1 and {a mathematical formula}L2 defined in Example 3. We also require that both the observers have complete knowledge on their views and therefore we impose that {a mathematical formula}Lic=Li with {a mathematical formula}i=1,2. Local axioms are used to represent the facts that are true in the views of the observers. Examples of local axioms of {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 follow, where {a mathematical formula}empty(p) is a shorthand for {a mathematical formula}∀x¬inbox(x,p) for a given position “p”, and {a mathematical formula}l,c,r are shorthands for “{a mathematical formula}left”, “{a mathematical formula}centre”, and “{a mathematical formula}right”, respectively.{a mathematical formula}{a mathematical formula}{a mathematical formula} Axioms (7) and (8) describe that {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 see two and three slots, respectively. Axiom (9) describes all the possible configurations of the slots of the box as seen by {a mathematical formula}Mr.1.Bridge rules are used to formalise the relation between {a mathematical formula}Mr.1's and {a mathematical formula}Mr.2's knowledge on their respective views. A first group of bridge rules formalises that: (i) the rightmost ball seen by {a mathematical formula}Mr.1 in the box is seen also by {a mathematical formula}Mr.2, and (ii) the leftmost ball seen by {a mathematical formula}Mr.2 in the box is seen also by {a mathematical formula}Mr.1:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} A second group of bridge rules formalise that the two observers agree on the colours of the balls they both see:{a mathematical formula}{a mathematical formula} The domain relations between {a mathematical formula}dom1 and {a mathematical formula}dom2 are used to represent the fact that {a mathematical formula}Mr.1 and {a mathematical formula}Mr.2 look at the same real world objects. A consequence of this is that the domain relations must be one the inverse of the other. This is formalised by a bridge rule as the one below, whose meaning will be better explained in Section 4.1 and Fig. 5:{a mathematical formula} The DFOL model defined in Example 4 satisfies all the bridge rules (10)–(17). To show how the satisfiability of bridge rules works, let us consider bridge rule (10). In particular, let us consider an assignment a such as {a mathematical formula}ai(x)=c. In this case, {a mathematical formula}M⊨1:inbox(x,r)[a] since {a mathematical formula}〈c,right〉∈inboxI1. We need to show that there is an extension {a mathematical formula}a′ of a, admissible for {a mathematical formula}2:∃yinbox(x1→,y), such as {a mathematical formula}M satisfies it. By observing the domain relation {a mathematical formula}r12 we can define {a mathematical formula}a′ as an extension of a with {a mathematical formula}aj′(x1→)=a. It is now easy to show our claim. In fact, {a mathematical formula}〈a,left〉∈inboxI2. Thus, the formula {a mathematical formula}∃yinbox(x1→,y) with {a mathematical formula}x1→ bound to a is satisfied by {a mathematical formula}m2 and, as a consequence, by {a mathematical formula}M.
      </paragraph>
      <paragraph label="Example 6">
       A formalisation of the mediatorLet the languages {a mathematical formula}L1,L2 and {a mathematical formula}Lm be the ones informally defined in Fig. 2. We focus here on the bridge rules able to express the relations between the sellers and the mediator, that is, the fact that the latter sells all and only products sold by each of the formers, whose price has been set to a specific value.First of all, we need to specify the shape of the domain relation, that is, indicate that fruits are mapped into fruits, numbers into numbers, and so on. Let us focus on fruits. The choice made by the mediator is to be able to represent all fruits sold by the two sellers. For the sake of this example, we also have decided that the mediator sells apples by their specific variety (similarly to {a mathematical formula}Sel.2 ) and that he knows that “apples” of {a mathematical formula}Sel.1 correspond to both “Delicious” and “GrannySmith” in his own database. We express all these choices by means of the following bridge rules:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}The mediator offers all the fruits available in {a mathematical formula}Sel.1 (resp. {a mathematical formula}Sel.2) whose price has been set.{a mathematical formula}{a mathematical formula} The mediator sells only fruits that are available in {a mathematical formula}Sel.1 or in {a mathematical formula}Sel.2;{a mathematical formula}In database terms, the above bridge rules can be read as a query definition for the predicate Offer in the database of m.{sup:5} When a user submits the query {a mathematical formula}Offer(x,y,z) to m, it rewrites this in two queries. The first one is {a mathematical formula}Available(x,y)∧Price(x,z), generated by (23), and sent to {a mathematical formula}Sel.1. The second query is {a mathematical formula}Available(x,y,z), generated by (24) and sent to {a mathematical formula}Sel.2. {a mathematical formula}Sel.1 and {a mathematical formula}Sel.2 separately evaluate the two queries and send the result back to the mediator using the domain relations shaped by bridge rules (18)–(22) to appropriately “translate” the result. This reading of bridge rules formalises the GAV (global as view) approach to information integration described in [30]. Finally, bridge rule (25) formalises a closure condition, that is, the fact that all the data relevant to Offer in m are retrieved from the relations {a mathematical formula}Available (and {a mathematical formula}Price) of the sellers' databases. Similar combinations of bridge rules to constrain the domain relation and the interpretation of predicates are exploited in [40] to perform instance migration among heterogeneous ontologies by means of bridge rules between ontology Aboxes and ontology Tboxes.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      How to represent distributed knowledge via bridge rules
     </section-title>
     <paragraph>
      In this section we illustrate how to represent important types of relations between local knowledge bases by means of bridge rules. We first investigate how to model specific relations between different domains (Section 4.1); we then focus on the usage of bridge rules to represent pairwise semantic mappings (Section 4.2); finally, we introduce and investigate the notion of entailment of bridge rules (Section 4.4).
     </paragraph>
     <section label="4.1">
      <section-title>
       Representing specific domain relations
      </section-title>
      <paragraph>
       The definition of domain relation as a generic relation provides DFOL with the capability to represent arbitrary correspondences between systems that have been designed autonomously. Nonetheless, the correlation patterns between domains of different knowledge bases often correspond to well known properties of relations. Examples are isomorphic domains, containment between domains, injective transformations, and so on. As already mentioned in Example 6, bridge rules can be used to impose restrictions on the shape of the domain relation in order to capture specific correspondences. We consider the following properties (further examples can be found in [37]):
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}rij is a (partial) function. In this case, the elements in {a mathematical formula}domi have at most one corresponding element in {a mathematical formula}domj. This is used, for instance, to express the fact that {a mathematical formula}domj has a smaller granularity than {a mathematical formula}domi. An example of this is the mediator example, where {a mathematical formula}dom1 has a smaller granularity w.r.t. {a mathematical formula}domm since it describes apples ignoring their different varieties. In this case, we could safely assume that {a mathematical formula}r1m satisfies the {a mathematical formula}Fij property, while we would not impose it for an hypothetical domain relation {a mathematical formula}rm1.
       </list-item>
       <list-item>
        {a mathematical formula}rij is total. In this case, each element of {a mathematical formula}domi has a corresponding element in {a mathematical formula}domj, and therefore the entire {a mathematical formula}domi can be embedded (via {a mathematical formula}rij) into {a mathematical formula}domj.
       </list-item>
       <list-item>
        {a mathematical formula}rij is surjective. In this case, each element of {a mathematical formula}domj is the corresponding of some object of {a mathematical formula}domi, and the entire {a mathematical formula}domj can be seen as the transformation of some parts of {a mathematical formula}domi.
       </list-item>
       <list-item>
        {a mathematical formula}rij is injective. In this case, inequality is preserved by {a mathematical formula}rij.
       </list-item>
       <list-item>
        {a mathematical formula}rij is the inverse of {a mathematical formula}rji; in this case the transformation from {a mathematical formula}domi to {a mathematical formula}domj corresponds to the way in which {a mathematical formula}domj is transformed into {a mathematical formula}domi.
       </list-item>
       <list-item>
        {a mathematical formula}rik is the composition of {a mathematical formula}rij and {a mathematical formula}rjk, that is {a mathematical formula}rik=rij∘rjk. This property guarantees that if there is a way of transforming an object d of {a mathematical formula}domi into an object {a mathematical formula}d′ of {a mathematical formula}domk via {a mathematical formula}domj, then there is also a direct way of transforming d into {a mathematical formula}d′ using {a mathematical formula}rik (and vice-versa).
       </list-item>
      </list>
      <paragraph>
       As we can see these properties can refer to a single domain relation, as in {a mathematical formula}Fij–{a mathematical formula}Jij, to two domain relations, as in the case of {a mathematical formula}Iij, or to several, as in {a mathematical formula}Cijk.
      </paragraph>
      <paragraph>
       The formalisation of the above properties relies on the usage of arrow variables, together with the equality predicate, to write bridge rules able to constrain the shape of the domain relation. As an example, a model {a mathematical formula}M satisfies a formula of the form {a mathematical formula}i:x=y→j (resp. {a mathematical formula}j:xi→=y) exactly when {a mathematical formula}rij relates the object {a mathematical formula}ai(x) in {a mathematical formula}domi to the object {a mathematical formula}aj(y) in {a mathematical formula}domj as in the graphical representation provided below:{a mathematical formula}
      </paragraph>
      <paragraph>
       A more complex scenario is the one in which {a mathematical formula}M satisfies the two bridge rules {a mathematical formula}i:x=y→j[a] and {a mathematical formula}j:y=zk→[a]. This originates the more complex diagram:{a mathematical formula}
      </paragraph>
      <paragraph>
       Using this graphical notation, we can represent e.g., {a mathematical formula}Iij and {a mathematical formula}Cijk as follows, where solid lines imply the existence of the dashed lines.
      </paragraph>
      <paragraph>
       {a mathematical formula}  {a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 9">
       We say that a model {a mathematical formula}M satisfies {a mathematical formula}Fij–{a mathematical formula}Cijk if the domain relations it contains satisfy {a mathematical formula}Fij–{a mathematical formula}Cijk. A model{a mathematical formula}Msatisfies the properties{a mathematical formula}Fij–{a mathematical formula}Cijkcontained in the left hand side column ofFig. 5if and only if it satisfies the corresponding bridge rules on the right hand side column.
      </paragraph>
      <paragraph label="Proof">
       We provide the proof for {a mathematical formula}Fij. All the other cases can be found in [37].if Direction. Let us assume that {a mathematical formula}rij is a function and that {a mathematical formula}M⊨i:x→j=y→j[a]; we have to show that {a mathematical formula}M⊨j:x=y[a]. From {a mathematical formula}M⊨i:x→j=y→j[a] we have that {a mathematical formula}ai(x→j)=ai(y→j). Since {a mathematical formula}rij is a function then {a mathematical formula}rij(ai(x→j))=rij(ai(y→j)) contains at most one element. This implies that {a mathematical formula}aj(x)=aj(y), and therefore that {a mathematical formula}M⊨j:x=y[a].only if Direction. Suppose that {a mathematical formula}M⊨i:x→j=y→j→j:x=y and let us prove that {a mathematical formula}rij is a function. Let {a mathematical formula}d∈domi and suppose by contradiction that {a mathematical formula}d′≠d″∈rij(d). Consider the assignment a with {a mathematical formula}ai(x→j)=ai(y→j)=d and {a mathematical formula}aj(x)=d′ and {a mathematical formula}aj(y)=d″. Obviously, {a mathematical formula}M⊨i:x→j=y→j[a] but {a mathematical formula}M⊭j:x=y[a], which contradicts the fact that {a mathematical formula}M⊨i:x→j=y→j→j:x=y. Thus, {a mathematical formula}rij is a function. □
      </paragraph>
      <paragraph>
       From now on we use a label, say {a mathematical formula}Fij to refer to both the property of the domain relation and the corresponding bridge rule(s). The context will always make clear what we mean.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Representing semantic mappings
      </section-title>
      <paragraph>
       Bridge rules can be used to formalise the important notion of semantic mapping between knowledge bases. Semantic mappings typically involves two knowledge bases only. In this Section we therefore restrict to pairwise bridge rules.
      </paragraph>
      <paragraph label="Definition 10">
       Pairwise bridge ruleA pairwise bridge rule from i to j, or simply a bridge rule from i to j, is a bridge rule of the form:{a mathematical formula}
      </paragraph>
      <paragraph>
       Pairwise bridge rules can be used to model different forms of mappings between knowledge sources. A proof of that is the fact that almost all the encodings of different formalisms into DFOL shown in Section 5 make use of pairwise bridge rules. A typical example of pairwise bridge rules are ontology mappings. Ontology mapping languages such as Distributed Description Logics (DDL) [18], ϵ-connections [17], [41], and Package-based Description Logics (P-DL) [21] enable the representation of mappings between pairs of ontologies which can be encoded in DFOL as shown in section 5 using and extending the work in [14].{sup:6} To briefly illustrate how pairwise bridge rules capture ontology mappings let us consider DDL into and onto mappings:{a mathematical formula} used to express that concept C in ontology {a mathematical formula}Oi is mapped into (onto) concept D in ontology {a mathematical formula}Oj. As shown in [14], these expressions can be represented by means of pairwise mappings of the form{a mathematical formula}
      </paragraph>
      <paragraph>
       Another typical example of pairwise mappings are mappings occurring in database integration. Here, the work in [27], [25] introduces peer-to-peer mappings as expressions of the form {a mathematical formula}cq1↝cq2 where {a mathematical formula}cq1 and {a mathematical formula}cq2 are conjunctive queries in two distinct knowledge bases. The intuitive meaning of {a mathematical formula}cq1↝cq2, is that the answer of the query {a mathematical formula}cq1 to the knowledge base {a mathematical formula}KB1 must be contained in the answer of {a mathematical formula}cq2 submitted to {a mathematical formula}KB2. We can easily observe that this is similar to the intuitive reading of bridge rules (2)–(5) in terms of query containment provided at page 9. Other examples of pairwise expressions used to semantically map two databases can be found in [6], [42], [9], [30], [43], [44]. Finally, the concept of infomorphism defined by Barwise and Seligman in [45] can be formalised via a set of pairwise bridge rules and one domain relation. Again an encoding of some of these approaches in DFOL is contained in Section 5.
      </paragraph>
      <paragraph>
       A final instance of DFOL pairwise bridge rule is {a mathematical formula}j:⊥→i:⊥. This rule, called inconsistency propagation rule and denoted with {a mathematical formula}IPji, forces inconsistency to propagate from a source knowledge base j to a target knowledge base i. This rule can be used to enforce the propagation of local inconsistency when needed, since in DFOL {a mathematical formula}j:⊥ does not necessarily propagate inconsistency to other knowledge bases (see Proposition 7).
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Joining knowledge through mappings
      </section-title>
      <paragraph>
       While pairwise bridge rules focus on “point-to-point” mappings between two knowledge sources, DFOL bridge rules enable to encode more complex relations involving an arbitrary number of knowledge bases.
      </paragraph>
      <paragraph>
       Bridge rules can be used to express the fact that a certain combination of knowledge coming from {a mathematical formula}i1,…, {a mathematical formula}in source knowledge bases entails some other knowledge in a target knowledge base i. As an example, bridge rule{a mathematical formula} whose graphical representation is provided in Fig. 6, can be read as a mapping from the join between relation {a mathematical formula}P(x,y) in 1 and {a mathematical formula}Q(y,z) in 2, into {a mathematical formula}R(x,y,z) in 3. Indeed bridge rule (27) is satisfied if {a mathematical formula}r13(‖P‖1)⋈r23(‖Q‖2)⊆‖R‖3.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Entailment among bridge rules
      </section-title>
      <paragraph>
       A logic based formalisation of the notion of mapping provides the basis to introduce the notion of entailment (logical consequence) between mappings. Entailment between mappings is important as it enables to prove that a mapping is redundant (as it can be derived from others), or that a set of mappings is inconsistent. Thus, it enables to compute sets of minimal mappings between e.g., ontologies and it can provide the basis for mapping debugging/repair, as shown for instance, in the work of Meilicke et al. [46] and the one of Wang and Xu [47].
      </paragraph>
      <paragraph>
       DFOL provides a precise characterisation of when bridge rules are entailed by others. For instance, to say that the bridge rule {a mathematical formula}1:A→3:C is a logical consequence of {a mathematical formula}1:A→2:B and {a mathematical formula}2:B→3:C. In this section we provide a precise definition of entailment between bridge rules and we study the general properties of such an entailment.
      </paragraph>
      <paragraph label="Definition 11">
       Entailment of bridge rules{a mathematical formula}i1:ϕ1,…,in:ϕn→i:ϕ is entailed by a set of bridge rules {a mathematical formula}BR, in symbols {a mathematical formula}BR⊨i1:ϕ1,…,in:ϕn→i:ϕ, if {a mathematical formula}i1:ϕ1…in:ϕn⊨BRi:ϕ.
      </paragraph>
      <paragraph>
       The following proposition illustrates the effects on bridge rule entailment of the main operations we can perform on mappings, that is: conjunction, disjunction, existential/universal restriction, composition, instantiation and inversion of mappings.
      </paragraph>
      <paragraph label="Proposition 10">
       The following entailments of bridge rules hold:Conjunction
       <list>
        {a mathematical formula}i:ϕ→j:ψ,i:ϕ′→j:ψ′⊨i:ϕ∧ϕ′→j:ψ∧ψ′if ϕ and{a mathematical formula}ϕ′do not have arrow variables in common.If{a mathematical formula}Fijholds, then{a mathematical formula}i:ϕ→j:ψ,i:ϕ′→j:ψ′⊨i:ϕ∧ϕ′→j:ψ∧ψ′Disjunction
       </list>
       <list>
        <list-item label="1.">
         {a mathematical formula}i:ϕ1(x)→j:ψ1(xi→),i:ϕ2(x)→j:ψ2(xi→)⊨i:ϕ1(x)∨ϕ2(x)→j:ψ1(xi→)∨ψ2(xi→), if at least one among{a mathematical formula}ϕ1(x)or{a mathematical formula}ϕ2(x)is a complete formula.
        </list-item>
       </list>
       <paragraph>
        Existential and universal quantification
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}i:ϕ(x)→j:ψ(xi→)⊨i:∃xϕ(x)→j:∃xψ(x)if ϕ is a complete formula.
        </list-item>
        <list-item label="2.">
         If{a mathematical formula}Sijholds, then{a mathematical formula}i:ϕ(x→j)→j:ψ(x)⊨i:∀xϕ(x)→j:∀xψ(x)
        </list-item>
       </list>
       <paragraph>
        CompositionIf{a mathematical formula}Cijkholds, then:
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}i:ϕ(x)→j:ψ(xi→),j:ψ(x)→k:θ(xj→)⊨i:ϕ(x)→k:θ(xi→)
        </list-item>
        <list-item label="2.">
         {a mathematical formula}i:ϕ(x→j)→j:ψ(x),j:ψ(x→k)→k:θ(x)⊨i:ϕ(x→k)→k:θ(x)
        </list-item>
       </list>
       <paragraph>
        Instantiation
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}i:x=t→j:xi→=s,i:ϕ(x→j)→j:ψ(x)⊨i:ϕ(t)→j:ψ(s), with t complete ground term of{a mathematical formula}Li.
        </list-item>
       </list>
       <paragraph>
        InversionIf{a mathematical formula}Fijand{a mathematical formula}Ijihold:
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}i:ϕ(x)→j:ψ(xi→)⊨j:¬ψ(xi→)→i:¬ϕ(x), if{a mathematical formula}ϕ(x)is a complete formula.
        </list-item>
       </list>
      </paragraph>
      <paragraph label="Proof">
       We show here only the case of Conjunction. The remaining cases are shown in [37].Suppose that {a mathematical formula}M⊨i:ϕ→j:ψ, {a mathematical formula}M⊨i:ϕ′→j:ψ′ and {a mathematical formula}M⊨i:ϕ∧ϕ′[a]. Then a can be extended to {a mathematical formula}a′ and {a mathematical formula}a″ admissible for {a mathematical formula}j:ψ and {a mathematical formula}j:ψ′ respectively, and such that {a mathematical formula}m⊨ψ[a′] and {a mathematical formula}m⊨ψ′[a″] for all {a mathematical formula}m∈Mj. If either (case 1) the arrow variables of ψ and {a mathematical formula}ψ′ are disjoint, or (case 2) {a mathematical formula}rij is functional, then {a mathematical formula}a′∪a″ is an extension of a, admissible for {a mathematical formula}ψ∧ψ′ and such that {a mathematical formula}m⊨ψ∧ψ′[a′∪a″]. □
      </paragraph>
      <paragraph>
       To show the usefulness of bridge rules entailment consider a simple scenario composed of three ontologies {a mathematical formula}O1,O2, and {a mathematical formula}O3, pairwise connected by means of the following DDL mappings:{a mathematical formula}{a mathematical formula} and where {a mathematical formula}O2 contains the following terminological axiom {a mathematical formula}2:AcademicPaper⊑2:Document. If we translate the DDL formulas into corresponding DFOL statements as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula} and we impose {a mathematical formula}C123 between the three ontologies we can use a slight modification of the proof of Composition above (item 2) to show that {a mathematical formula}1:AcademicPaper(x→3)→3:Document(x) holds. This, in turn, can be translated into the DDL mapping {a mathematical formula}1:AcademicPaper⟶⊑3:Document. We have intentionally chosen a simple scenario. Nonetheless, being able to compute this inferred mapping may be crucial in the presence of a rich network of mappings containing also assertions {a mathematical formula}1:AcademicPaper⟶⊑3:RethoricalWriting and {a mathematical formula}3:Document⊑¬RethoricalWriting. In that case mapping entailment would enable us to spot an inconsistent set of mappings, paving the way to techniques of mapping debugging/repair [46], [47].
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Analysing formalisms for distributed knowledge through DFOL
     </section-title>
     <paragraph>
      The need to represent and reason about distributed and context-dependent heterogeneous knowledge has fostered the development of various logical formalisms. Research areas such as Semantic Web, Databases, Linked Data, and Peer-to-Peer systems have seen a quest for logics able to represent and reason about knowledge contained in sets of different knowledge bases that describe overlapping knowledge by means of heterogeneous schemata. Examples are: mappings between overlapping ontologies or DB schemas, or relations between different contexts. All these formalisms make (implicit or explicit) assumptions about the following questions: (i) what is the structure (hierarchical, peer-to-peer, mediator based) in which the different local knowledge bases are embedded?; (ii) which is the type of knowledge that can be represented in each KB (e.g., only local knowledge, views on knowledge of other KBs, …)?; (iii) what type of domain is used to interpret the local knowledge (i.e., local domain or global domain)?; (iv) are there any relations between local domains and which ones (e.g., intersection, mapping, subset, identity, …)?; (v) what are the relations between local truth in different KBs? In this section, we consider a significant number of the most relevant first-order logic based frameworks for the representation of static and semantically heterogeneous distributed knowledge-base systems and show how their encoding in DFOL allows us to make these assumptions explicit.{sup:7} Finally, we briefly discuss the relationship between DFOL and non-monotonic extensions of the original multi-context systems (MCS) introduced in [38], [13] focusing especially on the equilibria-based MCS introduced in [48].
     </paragraph>
     <section label="5.1">
      <section-title>
       Quantified modal logics
      </section-title>
      <paragraph>
       Quantified modal logic (QML) [49] extends first-order language with modal operators. The semantics of QML is based on possible worlds. In its general form, the semantics of non logical symbols depends upon the possible worlds. Several important issues in QML arise from the combined semantics of quantifiers and modal operators. These issues have originated the development of different semantics for QML [49], which can be represented in DFOL using different bridge rules. In the following we provide an example of how to represent different QML semantics via DFOL bridge rules by focusing on its original Kripke semantics (Section 5.1.1) and on the more recent counterpart semantics (Section 5.1.2). For the sake of simplicity we restrict our comparison to QML without equality.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Kripke semantics for QML
       </section-title>
       <paragraph>
        A QML language is obtained by extending a first-order language {a mathematical formula}L with the modal operator □. The simplest semantics for QLM is based on possible worlds. A QML model {a mathematical formula}MQML is a 4-tuple {a mathematical formula}〈W,R,D,I〉, where {a mathematical formula}W is a non empty set of worlds, {a mathematical formula}R a binary relation on {a mathematical formula}W, {a mathematical formula}D is a function that associates to each {a mathematical formula}w∈W a non empty set {a mathematical formula}D(w), satisfying {a mathematical formula}wRv⇒D(w)⊆D(v), and {a mathematical formula}I is a function that associates to each w an interpretation {a mathematical formula}I(w) of the first-order language {a mathematical formula}L on the domain {a mathematical formula}D(w). Satisfiability is defined as usual on atomic formulas and propositional connectives. Universal quantification is interpreted w.r.t. the domain of the current world:{a mathematical formula} where {a mathematical formula}a[x:=d] denotes the assignment obtained by setting {a mathematical formula}a(x)=d in a. Modal formulas are interpreted as follows:{a mathematical formula} QML can be translated in a DFOL on a countable set {a mathematical formula}I={0,1,2,…} of indices. Each {a mathematical formula}Li (the language associated to the index {a mathematical formula}i∈I) is obtained by extending {a mathematical formula}L with an n-ary predicate {a mathematical formula}□‘ϕ’(x) for every formula {a mathematical formula}ϕ(x)∈Li−1 that contains n distinct free variables {a mathematical formula}x=〈x1,…,xn〉. Intuitively {a mathematical formula}□‘ϕ’(t1,…,tn) denotes the proposition stating that the tuple of objects denoted by {a mathematical formula}〈t1,…,tn〉 has necessarily the property denoted by the {a mathematical formula}Li−1-formula {a mathematical formula}ϕ(x1,…,xn). Notice that the formulas {a mathematical formula}□‘ϕ’(t1,…,tn) and {a mathematical formula}□‘ϕ(t1,…,tn)’ are syntactically and semantically different. The first is the atomic formula obtained by applying the n-ary predicate {a mathematical formula}□‘ϕ’ to {a mathematical formula}〈t1,…,tn〉, while the second is a 0-ary predicate, i.e., an atomic proposition. This difference corresponds to the two readings of the modal formula {a mathematical formula}□ϕ(t1,…,tn) called “de re” (the former) and “de dicto” (the latter).
       </paragraph>
       <paragraph>
        The translation {a mathematical formula}τQML from QML formulas into {a mathematical formula}Li formulas is defined as follows: {a mathematical formula}τQML is the identity transformation on formulas with no modal operators, and it distributes over connectives and quantifiers. If ϕ is a formula with n distinct free variables that contains at most {a mathematical formula}i−1 nested modal operators, then {a mathematical formula}τQML(□ϕ)=□‘τQML(ϕ)’(x1,…,xn). To provide the DFOL version of the semantics of □ defined in (33), we use the following bridge rules, where {a mathematical formula}x=〈x1,…,xn〉, {a mathematical formula}x→i=〈x1→i,…,xn→i〉 and {a mathematical formula}xi+1→=〈x1i+1→,…,xni+1→〉:{a mathematical formula}{a mathematical formula}{a mathematical formula} The set of bridge rules (34)–(36), called {a mathematical formula}BRQML, allows one to prove the DFOL translation of the (K) axiom for QML (i.e., {a mathematical formula}∀x(□(ϕ⊃ψ)⊃□ϕ⊃□ψ)) and of the Barcan formula (i.e., {a mathematical formula}∀x□ϕ(x)⊃□∀xϕ(x)). This implies that DFOL is stronger than QML. The opposite relation from QML to DFOL is stated in the following theorem.
       </paragraph>
       <paragraph label="Theorem 1">
        Let{a mathematical formula}MQML=〈W,R,D,I〉a QML model. For every{a mathematical formula}w∈Wthere is a DFOL model{a mathematical formula}Mthat satisfies{a mathematical formula}BRQML, and{a mathematical formula}Mis such that{a mathematical formula}where i is greater or equal to the number of nested modal operators of ϕ.
       </paragraph>
       <paragraph label="Proof">
        Given {a mathematical formula}MQML=〈W,R,D,I〉, for every {a mathematical formula}w∈W and for every index {a mathematical formula}i∈I, we define a DFOL model {a mathematical formula}M. Let i be the maximum number of nested modal operators in ϕ. For every {a mathematical formula}j≤i we define the set {a mathematical formula}Wj⊆W as follows:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}Wi={w};
        </list-item>
        <list-item label="•">
         {a mathematical formula}Wj−1=R(Wj)={w′∈W|w″Rw′ for some w″∈Wj} for {a mathematical formula}j≤i.
        </list-item>
       </list>
       <paragraph>
        The DFOL encoding of QML shown above decouples the semantics of the modal operator □, captured by bridge rules (34) and (35), and the assumptions on the possible worlds domains, captured by the bridge rule (36). Different assumptions on the possible worlds domains can be encoded by means of different bridge rules on the equality predicate, thus retaining the bridge rules for □ unchanged. On the contrary, in QML, the semantics of the □ operator needs to be adapted to the different assumptions made on the worlds domains. As an example, decreasing domains can be axiomatized using the bridge rule:{a mathematical formula} and constant domains can be axiomatised by adopting both (36) and (37).
       </paragraph>
       <paragraph>
        A further source of variations in the semantics of QML concerns the interpretation of terms in the scope of a modal operator. For instance what is the meaning of the formula {a mathematical formula}□P(a) when a denotes, in the current world, an object which does not exist in one of the accessible worlds? Or similarly, in evaluating {a mathematical formula}□P(a) should a be interpreted in the current worlds or in all the accessible worlds? In DFOL this ambiguity is solved by providing a syntax for both semantics: the formula {a mathematical formula}□(‘P(x)’(a)) corresponds to the semantics of {a mathematical formula}□P(a) where a is evaluated in the current world (“de re”), whereas the formula {a mathematical formula}□‘P(a)’ corresponds to the semantics of {a mathematical formula}□P(a) where a is evaluated in each accessible world (“de dicto”).
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Counterpart semantics for QML
       </section-title>
       <paragraph>
        To overcome all the difficulties introduced in the Kripke semantics by the interpretation of objects across different worlds, a new semantics for QML called counterpart theory, has been recently introduced [50], [51], [52]. Counterpart semantics extends Kripke semantics by adding relations between objects in different worlds. These relations are similar to domain relations in DFOL. The semantics proposed in [50], [51] extends standard QML models with unconstrained domains, (i.e., for every {a mathematical formula}w∈W, {a mathematical formula}D(w) is an arbitrary non empty set) with a counterpart relation {a mathematical formula}C that maps every pair {a mathematical formula}〈w,v〉∈W×W to a subset of {a mathematical formula}D(w)×D(v). Satisfiability of modal formulas is defined as follows:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}MCP,w⊨□ϕ(x1,…,xn)[a], where a is an assignment to the free variables of ϕ in {a mathematical formula}D(w), if and only if {a mathematical formula}MCP,w⊨ϕ[a′], for every world {a mathematical formula}w′ with {a mathematical formula}wRw′ and for every assignment {a mathematical formula}a′ to the free variables of ϕ into the domain {a mathematical formula}D(w′), such that {a mathematical formula}〈a(xi),a′(xi)〉∈C(w,w′).
        </list-item>
       </list>
       <paragraph>
        With this semantics (which we call basic counterpart semantics), however, the (K) schema no longer holds. The approach presented in [50], [51] overcomes this drawback by deviating from first-order semantics either by adopting typed first-order or free logics (with partial assignments to variables). Since DFOL is based on a first-order semantics for local models, we have to limit the comparison to the basic counterpart semantics. If we take the language of QML and the transformation form QML to DFOL seen in the previous section, then we can formalise the counterpart semantics in DFOL. Let {a mathematical formula}BRCP be the set of bridge rules {a mathematical formula}(35),(34),{Ci,j,k}i&gt;j&gt;k∈I. Let {a mathematical formula}τCP be defined as {a mathematical formula}τQML. The following theorem formally states the correspondence between counterpart semantics and DFOL.
       </paragraph>
       <paragraph label="Theorem 2">
        Let{a mathematical formula}MCP=〈W,R,D,C,I〉a counterpart frame. For every{a mathematical formula}w∈Wthere is a DFOL model{a mathematical formula}Mthat satisfies{a mathematical formula}BRCPsuch that{a mathematical formula}where i is greater or equal to the number of nested modal operators of ϕ.
       </paragraph>
       <paragraph>
        The proof is the same as the one given for QML, with the only difference that the domain relation of {a mathematical formula}M is defined as follows:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}rij for {a mathematical formula}i&gt;j is defined in two phases. First we define {a mathematical formula}ri,i−1, and then {a mathematical formula}ri,i−k as the composition of the relations {a mathematical formula}ri,i−1,…,ri−k+1,i−k.{a mathematical formula}{a mathematical formula} □
        </list-item>
       </list>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Quantified logic of contexts
      </section-title>
      <paragraph>
       Quantified logic of contexts (QLC) is a formalism for reasoning about propositions with context dependent truth values. QLC was originally introduced in [12] and further developed in [53], [54]. In what follows we refer to the original formulation of QLC for two reasons: first, it is a formulation closer to the original logic of context introduced by John McCarthy in [55] and to DFOL; second, the work in [53], [54] extends the formalism introduced in [12] with the possibility of quantifying over contexts, which is not allowed in DFOL, as it would correspond to quantifying over indices in I.
      </paragraph>
      <paragraph>
       In the formulation described in [12], the language of QLC is a two sorted first-order language {a mathematical formula}L extended with the modal operator {a mathematical formula}ist(k,ϕ) formalising the fact that the formula ϕ is true in the context k. The two sorts of {a mathematical formula}L are: a sort for objects and a sort for contexts. The set of terms of sort context is hereafter denoted with {a mathematical formula}K. A QLC model {a mathematical formula}MQLC is defined starting from two disjoint sets {a mathematical formula}Δc and {a mathematical formula}Δd, used to interpret terms of sort context and terms of sort object, respectively. {a mathematical formula}MQLC is a function that associates to each element of {a mathematical formula}Δc a set of interpretations of {a mathematical formula}L on {a mathematical formula}Δ=Δd∪Δc such that{a mathematical formula} Restriction (40) amounts to assume that terms are rigid designators: i.e., a term denotes the same object in all contexts.
      </paragraph>
      <paragraph>
       QLC can be translated in an equivalent DFOL on the set {a mathematical formula}K of indices. The language of the k-th context, {a mathematical formula}Lk, extends the first-order language {a mathematical formula}L of QLC with an extra sort for interpreting well-formed formulas (wffs), the binary predicate {a mathematical formula}ist(x,y) with x of sort context and y of sort wff, and a function symbol {a mathematical formula}fϕ(x1,…,xn) for every formula ϕ with n distinct free variables {a mathematical formula}x1,…,xn (if ϕ is a closed formula {a mathematical formula}fϕ is a constant). The term {a mathematical formula}fϕ(x1,…,xn)(c1,…,cn) is used to denote the formula {a mathematical formula}ϕ(x1,…,xn) where each {a mathematical formula}xi is replaced with {a mathematical formula}ci. Formulas of the form {a mathematical formula}ist(k,w) are complete. We define a translation τ from the language of QLC to DFOL as hinted below. Without loss of generality we assume that QLC formulas are in prenex normal form, and that existential quantifiers have been removed by introducing Skolem constants/functions.
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}τ(ϕ)=ϕ if ϕ is any expression (term or formula) of {a mathematical formula}L;
       </list-item>
       <list-item label="(ii)">
        τ distributes over connectives;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}τ(ist(k,ϕ(x1,…,xn)))=ist(k,fτ(ϕ)(x1,…,xn)).
       </list-item>
      </list>
      <paragraph>
       In QLC, the semantics of the ist operator is analogous to the one of the □ operator in modal logics. Namely {a mathematical formula}I⊨ist(k,ϕ) iff for all {a mathematical formula}I′∈MQLC(kI), {a mathematical formula}I′⊨ϕ. The two semantics however are not completely equivalent. Indeed in QLC, the schema {a mathematical formula}ist(k,ϕ∨ist(k′,ψ))⊃ist(k,ϕ)∨ist(k,ist(k′,ψ)) is valid, while the corresponding modal axiom {a mathematical formula}□(ϕ∨□ψ)⊃□ϕ∨□□ψ is not.
      </paragraph>
      <paragraph>
       QLC semantics is axiomatised by adding specific axioms and specific inference rules. An example of axiom is the one corresponding to the modal axiom (K) for ist: {a mathematical formula}ist(k,ϕ⊃ψ)⊃ist(k,ϕ)⊃ist(k,ϕ). An example of rules is the “enter context” rule: {a mathematical formula}k:ist(k′,ϕ)⇒k′:ϕ. In DFOL, the semantics of the ist predicate is axiomatised by means of bridge rules. The relation between the truth of the formula {a mathematical formula}ist(k,fϕ) in a context h and the truth of ϕ in the context k is axiomatised with the following bridge rules:{a mathematical formula}{a mathematical formula} QLC assumes constant domains, which in DFOL corresponds to isomorphic domains. Isomorphic domains can be imposed by the restriction {a mathematical formula}Fkh,Tkh,Jkh and {a mathematical formula}Ikh for every pair of contextual terms {a mathematical formula}k,h∈K. Furthermore, the rigid designation assumption (40) can be axiomatised using the bridge rule:{a mathematical formula} Let {a mathematical formula}BRQLC be the set of bridge rules {a mathematical formula}{Fkh,Tkh,Jkh,Ikh,(43),(42),(41)}.
      </paragraph>
      <paragraph label="Theorem 3">
       For every QLC model{a mathematical formula}MQLCand any assignment a to the variables of{a mathematical formula}L, there is a DFOL model{a mathematical formula}Mthat satisfies{a mathematical formula}BRQLCsuch that{a mathematical formula}MQLC⊨k:ϕ[a]if and only if{a mathematical formula}M⊨k:τ(ϕ)[τ(a)], where{a mathematical formula}τ(a)is the DFOL assignment such that{a mathematical formula}τ(a)i(x)=τ(a)k(xh→)=τ(a)k(x→h)=a(x).{sup:8}
      </paragraph>
      <paragraph label="Proof">
       For every {a mathematical formula}k∈K, {a mathematical formula}domk=Δc∪Δd∪Δwff. {a mathematical formula}Δwff is a countable set disjoint from {a mathematical formula}Δc∪Δd that is used to interpret the terms of sort wff (i.e., the terms of the form {a mathematical formula}fϕ(…)). For any {a mathematical formula}I∈MQLC(c) with {a mathematical formula}c∈Δc, we define {a mathematical formula}τ(I,a), which is an interpretation of the language {a mathematical formula}Lk obtained extending {a mathematical formula}I as follows:
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}fϕτ(I)(t1τ(I),…,tnτ(I))=fϕ(t1,…,tn)τ(I) for every n-tuple of terms {a mathematical formula}〈t1,…,tn〉.
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}istτ(I)={〈c,w〉∈Δc×Δwff|MQLC(c)⊨ϕ and ϕτ(I,a)=w}
       </list-item>
      </list>
     </section>
     <section label="5.3">
      <section-title>
       Ontology mapping and ontology integration formalisms
      </section-title>
      <paragraph>
       A number of formalisms for distributed knowledge representation have originated in the field of ontology integration and are based on Description Logics (DLs) as a logic for the representation of a single knowledge base (ontology). A comparison between DFOL and several of these formalisms is described in [14]. In the following we recall and extend the results for Distributed Description Logics, ϵ-connection, Package-based Description Logics (P-DL) [21] and peer-to-peer (P2P) data integration [27].
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Distributed description logics
       </section-title>
       <paragraph>
        Distributed Description Logics (DDL) [18], [56], [57] and C-OWL[29] are logical formalisms for ontology mapping where ontologies are expressed using description logics. DDL extends description logics with a local semantics similar to that of DFOL and so-called bridge rules to represent semantic relations between different T-Boxes. A distributed interpretation for DDL on a family of DL languages {a mathematical formula}{Li} is a family {a mathematical formula}{Ii} of interpretations, one for each {a mathematical formula}Li, plus a family {a mathematical formula}{rij}i≠j∈I of domain relations. While the original proposal only considers subsumption between concept expressions, DDL has been extended in [58], [40], [59], [60] to support mappings between (binary) relations, individuals, concept-to-relation (and vice-versa), and, finally, fuzzy values. In DDL, ontology mappings are expressions of the form {a mathematical formula}i:ϕ⟶⊑j:ψ and {a mathematical formula}i:ϕ⟶⊒j:ψ where ϕ and ψ are either concepts, individuals, or role expressions of the descriptive languages {a mathematical formula}Li and {a mathematical formula}Lj respectively.{sup:9} The satisfiability conditions of DDL ontology mappings are:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}I⊨i:ϕ⟶⊑j:ψ if {a mathematical formula}rij(ϕIi)⊆ψIj;
        </list-item>
        <list-item label="•">
         {a mathematical formula}I⊨i:ϕ⟶⊒j:ψ if {a mathematical formula}rij(ϕIi)⊇ψIj;
        </list-item>
       </list>
       <paragraph>
        Since the notion of DDL model is based on the same principles as that of DFOL, we can directly translate DDL bridge rules into DFOL bridge rules. In particular, there are no additional assumptions about the nature of the domains that need to be modelled. The translation is the following:{a mathematical formula} In [56] additional constraints on the domain relation are added in order to augment the information flow between different ontologies induced by DDL ontology mappings. Of particular interest are the bridge rules that support the transitive propagation of mappings:{a mathematical formula}{a mathematical formula} which correspond to the entailment between the following DFOL bridge rules:{a mathematical formula}{a mathematical formula} Since conditions (46) and (47) must hold for any interpretation of A, B, and C, then the entailments can be obtained by imposing condition {a mathematical formula}rij∘rjk=rik among domain relations, which corresponds to bridge rules {a mathematical formula}Cijk.
       </paragraph>
      </section>
      <section label="5.3.2">
       ϵ-connections
       <paragraph>
        A further approach for defining mappings between DL knowledge bases has emerged from the investigation of so-called ϵ-connections between abstract description systems [17], [41]. In the ϵ-connections framework, for every pair of ontologies i and j there is a set {a mathematical formula}ϵij of links, which represent binary relations between the domain of the i-th ontology and the domain of the j-th ontology. Links from i to j can be used to define i concepts in a way that is analogous to how roles are used to define concepts. In the table below we report the syntax and the semantics of the i-concepts definition based on links, where E denotes a link from i to j and ψ denotes a concept in j. The only assumption about the relation between domains is global inconsistency, that is, the fact that the inconsistency of a local knowledge base makes the whole system inconsistent.
       </paragraph>
       <paragraph>
        In comparing DFOL with ϵ-connections we can notice that in DFOL there is only one relation from i to j, while in ϵ-connection there are many possible relations. However, [14] shows how to represent each {a mathematical formula}rij as a relation in {a mathematical formula}ϵij and provides a detailed description of how the concept definition based on links of ϵ-connections can be codified in DFOL. In a nutshell, to represent ϵ-connections in DFOL it is enough to label each arrow variable with the proper link name. The arrow variable {a mathematical formula}x→owni is read as the arrow variable {a mathematical formula}x→i where {a mathematical formula}rij is intended to be the interpretation of Own{a mathematical formula}ij. With this syntactic extension of DFOL, the concept definition based on links (denoted as E) can be codified in DFOL as follows{sup:10}:{a mathematical formula}
       </paragraph>
      </section>
      <section label="5.3.3">
       <section-title>
        Package-based description logics
       </section-title>
       <paragraph>
        (P-DL) [21] is a formalism focused on ontology import, that is, it allows a subset of concepts, relations, and individuals defined in one ontology to be imported and reused in another ontology. These ontologies are called, in P-DL terms, packages. In a nutshell, a package-based ontology is a {a mathematical formula}SHOIQ ontology {a mathematical formula}P which is partitioned into a finite set of packages {a mathematical formula}{Pi}i∈I, using an index set I. Each {a mathematical formula}Pi uses its own alphabet of terms. The alphabets are not mutually disjoint, but for any term t there is a unique home package of t, denoted by home(t). The importing of a term of {a mathematical formula}Pi in {a mathematical formula}Pj is denoted with the expression {a mathematical formula}Pi→tPj, while {a mathematical formula}Pi→⁎Pj is used to denote the transitive closure of →. A distributed interpretation of {a mathematical formula}P is composed of a set of interpretations, one for each package, plus a set of domain relations similar to the ones of DFOL. The main difference with DFOL is that each {a mathematical formula}rij is an injective partial function, and that if {a mathematical formula}i→⁎j and {a mathematical formula}j→⁎k then {a mathematical formula}rik is defined as the composition {a mathematical formula}rij∘rjk. As shown in Fig. 5, these restrictions can be formalised using the bridge rules {a mathematical formula}Jij and {a mathematical formula}Cijk. The semantics of the import of a term t, expressed by {a mathematical formula}Pi→tPj, is defined as {a mathematical formula}rij(tIi)=tIj. If t is a description logic concept (unary predicate) {a mathematical formula}ϕ(x), then the import can be represented in DFOL by the pair of bridge rules:{a mathematical formula}{a mathematical formula} while if t is an individual a, then the import can be represented in DFOL by the bridge rule:{a mathematical formula} If t is a role (binary predicate) {a mathematical formula}ϕ(x,y) then we can define analogous bridge rules, and also impose that {a mathematical formula}rij is role preserving, that is, if {a mathematical formula}(x,y)∈ϕIi, then {a mathematical formula}rij(x)≠∅ iff {a mathematical formula}rij(y)≠∅.
       </paragraph>
      </section>
      <section label="5.3.4">
       <section-title>
        Logical foundation of peer-to-peer (P2P) data integration
       </section-title>
       <paragraph>
        The work in [27] defines an epistemic semantics for P2P systems and applies it to different architectures of P2P systems. The epistemic semantics is based on the introduction of a modal operator K used to express what is known by peers. Mapping assertions of the form {a mathematical formula}cqS↝cqG represent the fact that all the data satisfying the (conjunctive) query {a mathematical formula}cqS over the sources also satisfy the concept in the peer schema represented by {a mathematical formula}cqG. This mapping assertion is captured, in the epistemic semantics, by an axiom of the form:{a mathematical formula} which states that only what is known in S is transferred to G. Differently from DFOL, the epistemic semantics presented in [27] provides a unique model of the P2P system, based on a single domain of interpretation. Similarly to DFOL, this semantics addresses the problem of the representation of complete and incomplete information. In fact, the modal operator K can be considered a way of dealing with non-complete formulas and to consider, in the mappings, only their “complete part” (that is, the tuples that belong to the interpretation of that formula in all possible models).
       </paragraph>
      </section>
     </section>
     <section label="5.4">
      <section-title>
       Annotated logic
      </section-title>
      <paragraph>
       Annotated logics [5] is a formalism that has been applied to a variety of aspects in knowledge representation, expert systems, quantitative reasoning, and hybrid databases. In annotated logics it is possible to integrate a set of logical theories in an unique amalgamated theory. The amalgamated theory is the disjoint union of the original theories plus a set of clauses (called amalgamated clauses) which resolve conflicts due to inconsistent facts and compose uncertain information of different theories. One of the main similarities with our approach is the capability to cope with inconsistent knowledge bases. Annotated logics provide an explicit way to solve conflicts. The main difference between annotated logics and DFOL concerns the ability to represent different interpretation domains. Annotated logics have a single logical language, and the same symbol in different knowledge bases is interpreted in the same object. This of course might be solved by indexing the constant with the name of the knowledge base. In this case explicit relational symbols between objects of different knowledge bases should be introduced.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Original DFOL
      </section-title>
      <paragraph>
       We conclude this section by illustrating the difference between the version of DFOL presented in this paper and the original version introduced in [28], here denoted with DFOL0. The first difference concerns arrow variables. In the current version of DFOL arrow variables are part of the syntax of the local languages and of the bridge rules. In DFOL0 arrow variables are a meta-notation of the calculus, which is used to keep track of the dependencies between variables in different modules. Arrow variables, therefore, are not part of the logical language of DFOL0 and no semantics is provided for them. Also, the bridge rules of DFOL0 (called interpretation constraints) do not contain arrow variables. Thus the DFOL0 bridge rule {a mathematical formula}i:ϕ(x)→j:ψ(x) corresponds to the DFOL bridge rule {a mathematical formula}i:ϕ(x→j)→j:ψ(x). The introduction of bridge rules in the logical language of DFOL is not only a matter of syntax: arrow variables extend the expressivity of the language. Indeed, in DFOL0 there is no way of expressing a constraint represented by a DFOL bridge rules with arrow variables in the conclusion. For instance, the fact “for all the objects of type A in i there is a corresponding object of type B in j” is represented by means of the DFOL bridge rule {a mathematical formula}i:A(x)→j:B(xi→) and is not expressible in DFOL0.
      </paragraph>
      <paragraph>
       A second important difference is the fact that arrow variables allow to unify the two types of constraints introduced in DFOL0: domain constraints and interpretation constraints. Domain constraints between i and j are constraints on the domain of i and j, while interpretation constraints are constraints between the interpretations of the symbols in i and j modulo the transformation via domain relation {a mathematical formula}rij. As shown in section 4 bridge rules with arrow variables enable the formalisation of a wide set of relations between (two or more) domains together with relations between predicates. On the contrary, the only domain constraints allowed in DFOL0 are {a mathematical formula}rij being total or surjective, which correspond to the bridge rules {a mathematical formula}Tij and {a mathematical formula}Sij in Fig. 5.
      </paragraph>
      <paragraph>
       Third, in DFOL0 bridge rules (interpretation constraints) connect only two KBs, that is, they are of the form {a mathematical formula}i:ϕ(x)→j:ψ(x′), where {a mathematical formula}x′⊆x are two sets of variables. In DFOL we generalise bridge rules by allowing more than one index in the premise.
      </paragraph>
      <paragraph>
       Finally, in this paper we have defined a notion of logical consequence between bridge rules. This notion is very important when formalising reasoning about ontology mapping. In fact it makes possible to check the consistency, the redundancy, and the inter-dependency of sets of ontology mappings (see [61], [62] for example). Given a set of DFOL bridge rules {a mathematical formula}BR, the problem of checking if the bridge rule {a mathematical formula}br=i1:ϕ1,…,inϕn→i:ϕ is a logical consequence of {a mathematical formula}BR can be formulated as the problem of proving {a mathematical formula}i1:ϕ1,…,in:ϕn⊨BRi:ϕ.
      </paragraph>
     </section>
     <section label="5.6">
      <section-title>
       Equilibria based multi-context systems
      </section-title>
      <paragraph>
       The last decade has seen a number non-monotonic extensions of the original multi-context systems (MCS) introduced in the 90's [38], [13]. The work in [63] extends MCS with minimal beliefs, while [64] introduces default reasoning with contexts. A notable generalisation of MCS was proposed in [48], where the focus of the work is the ability to deal with distributed heterogeneous reasoning systems, that is, systems that adopt different logics in the different contexts (knowledge modules). The semantics of this version of MCS is called equilibria based semantics. Given the semantics of a set of local logics (that can be either monotonic or non monotonic logics) the equilibria based semantics is obtained by composing the local semantics with a methodology inspired to the answer set programming paradigm.
      </paragraph>
      <paragraph>
       When comparing DFOL with equilibria based MCS, we need to take into account some important aspects. DFOL and equilibria based MCS have been developed to tackle different forms of heterogeneity. From the one hand, DFOL focuses on capturing the heterogeneity that arises in integrating knowledge bases that describe different but overlapping or interconnected domains expressed in a set of first-order languages. On the other hand, equilibria based MCS focus on capturing the heterogeneity that arises in integrating knowledge bases expressed using different logics. From this perspective, DFOL can be seen as a special case of equilibria based MCS. However, due to their generality, equilibria based MCS do not provide a specific investigation on specific relations between heterogeneous domains, semantic shifting of symbols across different contexts, rigid and non-rigid semantics of constants, and so on. These aspects are the ones that DFOL analyses in terms of specific bridge rules. A second difference concerns the different reasoning tasks the two systems are focused on. Equilibria based MCS is a formalism developed with the aim of supporting query answering. Thus, the emphasis is on the computation of equilibria KBs which can then be queried. DFOL is instead focused on the notion of logical consequence and bridge rules entailment. Thus, the emphasis is on the definition of a semantics and a calculus that axiomatise mapping entailment.
      </paragraph>
      <paragraph>
       In the following comparison, therefore, we will concentrate only on the common aspects of DFOL and MCS. In particular we restrict to a specific version of DFOL, where bridge rules involve only closed formulas, and to a specific version of equilibria based MCS, where the local logics are propositional or first-order classical logics. In other words we omit arrow variables and the contribution of the domain relation in the semantics of DFOL and the ability to deal with different logics in equilibria based MCS. Note that a complete formal comparison of equilibria based MCS and DFOL is out of the scope of this paper. In the following we provide some insights and an example about this correspondence. A thorough comparison is left for future work.
      </paragraph>
      <paragraph>
       As already said we focus on MCS where each KB is formalised by means of a propositional or first-order classical logic. This does not make the resulting system monotonic. In fact, an important characteristic of equilibria based MCS are bridge rules that can introduce a form of non monotonicity. Let us go a bit more into details considering a correspondence between DFOL and equilibria based MCS when the local KBs are modelled using propositional logic.
      </paragraph>
      <paragraph>
       Let MCS be an MCS defined on a set I of classical propositional logics with languages {a mathematical formula}{Li}i∈I. The corresponding DFOL logic {a mathematical formula}DFOLMCS is obtained by extending the set of contexts (indexes) with a meta context mc that contains the propositional letter {a mathematical formula}not(j:p) for every propositional letter {a mathematical formula}p∈Lj, {a mathematical formula}j∈I. We also assume that {a mathematical formula}not(j:p) in mc is complete. Since propositions of the form {a mathematical formula}not(i:p) occur only in mc, we simplify the notation by omitting the index mc.
      </paragraph>
      <paragraph>
       The semantics of {a mathematical formula}not(j:p) is fixed by the bridge rules (51) and (52),{sup:11} while (53) enables to export an inconsistency to the meta context mc:{a mathematical formula}{a mathematical formula}{a mathematical formula} As a consequence of these rules{a mathematical formula} Furthermore, {a mathematical formula}Mmc is completely defined by the set {a mathematical formula}{Mi}i∈I. In other words, {a mathematical formula}Mmc⊨not(i:p) if and only if {a mathematical formula}Mi⊭p.
      </paragraph>
      <paragraph>
       For each bridge rule of MCS which is of the form:{a mathematical formula} we add the following bridge rule br into {a mathematical formula}DFOLMCS:{a mathematical formula} Following the logic programming notation, we use {a mathematical formula}head(br) to denote {a mathematical formula}i:p and {a mathematical formula}body(br) to denote the set {a mathematical formula}{i1:p1,…,in:pn,not(j1:q1),…,not(jm:qm)}.
      </paragraph>
      <paragraph>
       Given a model {a mathematical formula}M for {a mathematical formula}DFOLMCS, its local reduction{a mathematical formula}LR(M) is the {a mathematical formula}DFOLMCS model obtained by removing from each {a mathematical formula}Mi any model m such that there exists a model {a mathematical formula}m′∈Mi, with {a mathematical formula}m≠m′, such that {a mathematical formula}m′⊨p implies {a mathematical formula}m⊨p for all propositional letters {a mathematical formula}p∈Li. Notice that if {a mathematical formula}M is a {a mathematical formula}DFOLMCS model then {a mathematical formula}LR(M) is also a {a mathematical formula}DFOLMCS model.
      </paragraph>
      <paragraph>
       We use local reductions to compute minimal models of {a mathematical formula}DFOLMCS as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}M(0) is the {a mathematical formula}DFOLMCS model such that {a mathematical formula}Mi(0) contains all the models of {a mathematical formula}Li that satisfy the local axioms.
       </list-item>
       <list-item label="•">
        {a mathematical formula}M(k+1) is obtained by deleting from {a mathematical formula}Mi(k) all the models that do not satisfy the consequence of some bridge rule if all its premises are satisfied by {a mathematical formula}M(k). Formally {a mathematical formula}Mi(k+1)={m∈Mi(k)|M(k)⊨body(br)⇒m⊨head(br) for all br∈BRDFOLMCS} and {a mathematical formula}Mmck+1 is updated according to condition (54).
       </list-item>
       <list-item label="•">
        {a mathematical formula}M⁎ is the fix-point of this operator. The fix-point exists since the bridge rules have only a finite number of premises.
       </list-item>
       <list-item label="•">
        The minimal model of {a mathematical formula}DFOLMCS is equal to {a mathematical formula}LR(M⁎).
       </list-item>
      </list>
      <paragraph>
       Such a minimal model is the analogous of the grounded equilibrium as defined in [48]. To show how this construction works we consider the example similar to Example 3 in [48].
      </paragraph>
      <paragraph label="Example 7">
       Consider the {a mathematical formula}DFOLMCS consisting of two contexts 1 and 2. Suppose that there are no local axioms and that the set of bridge rules {a mathematical formula}BR contains the two standard bridge rules {a mathematical formula}2:q→1:p and {a mathematical formula}1:p→2:q and the non monotonic bridge rule{a mathematical formula} In the following table we show step by step the construction of {a mathematical formula}RL(M⁎).{a mathematical formula}{a mathematical formula}M(0) is the {a mathematical formula}DFOLMCS model such that each {a mathematical formula}Mi0 satisfies the local axioms. Since there are no local axioms {a mathematical formula}M10 and {a mathematical formula}M20 contain all the possible local models. The only applicable rule to compute {a mathematical formula}M1 is bridge rule (55), which can be applied because {a mathematical formula}Mmc0 satisfies {a mathematical formula}not(2:r). Thus, {a mathematical formula}M1 is obtained by removing all the models that do not satisfy r from {a mathematical formula}M20 and by removing {a mathematical formula}not(2:r) from {a mathematical formula}Mmc1 to comply with condition (54). After that no more rules are applicable. Thus {a mathematical formula}M(2) provides the fix-point {a mathematical formula}M⁎. The last step of our computation concerns the computation of the local reduction {a mathematical formula}RL(M(2) of {a mathematical formula}M(2) which terminates the computation. As we can see from its construction, the resulting model {a mathematical formula}RL(M(2)) satisfies only {a mathematical formula}2:r, {a mathematical formula}1:¬p and {a mathematical formula}2:¬q.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Logical reasoning for the bridge rules
     </section-title>
     <paragraph>
      In this section we define a Natural Deduction (ND) Calculus for DFOL: given a set of bridge rules {a mathematical formula}BR we define a calculus {a mathematical formula}ML(BR) which is strongly sound and complete with respect to the notion {a mathematical formula}⊨BR of logical consequence w.r.t. {a mathematical formula}BR. The calculus provides a proof-theoretic counterpart of the notion of entailment between bridge rules introduced in Section 4.4, and can be therefore used to support formal reasoning in DFOL. By applying a finite set of inference rules, one can prove, for instance, that a set of bridge rules is consistent, or that a bridge rule is redundant being derivable from others, or that two sets of bridge rules are equivalent, and so on.
     </paragraph>
     <paragraph>
      We follow the approach of Multi Language Systems (ML systems) [38], [70] and see a deduction in DFOL as composed of a set of local deductions, which represent reasoning in a single theory, glued together by the applications of bridge rules, which enable the transfer of truth from a local knowledge base to another. For instance, the bridge rule {a mathematical formula}i:ϕ(x)→i:ψ(xi→) can be read as “if a certain object x has the property ϕ in i, then, it has a translation {a mathematical formula}xi→ in j which has the property ψ”.
     </paragraph>
     <section label="6.1">
      <section-title>
       A multi language system for DFOL
      </section-title>
      <paragraph>
       A ML system is a triple {a mathematical formula}〈{Li},{Ωi},Δ〉 where {a mathematical formula}{Li} is a family of languages, {a mathematical formula}{Ωi} is a family of sets of axioms, and Δ is a set of inference rules. Δ contains two kinds of inference rules: rules with premises and conclusions in the same language, and rules with premises and conclusions belonging to different languages.
      </paragraph>
      <paragraph>
       Derivability in a ML system is a generalisation of derivability in a Natural Deduction system.
      </paragraph>
      <paragraph>
       In adapting the original definition of ML system given in [38], [70] to the case of DFOL we require each {a mathematical formula}Li to be a first-order language with equality. This can be axiomatised by setting {a mathematical formula}Ωi as the set of classical Natural Deduction axioms given in [71], and the rules in Δ that take care of connectives, quantifiers, and equality to mimic the inference rules given in [71]. As we will see, we have to slightly modify the applicability conditions of these rules in order to deal with arrow variables in a proper manner. Moreover, Δ has to contain the Natural Deduction version of the DFOL bridge rules introduced in Definition 7, and of the logical properties of arrow variables stated in Proposition 8.
      </paragraph>
      <paragraph>
       Notationally, we use {a mathematical formula}ϕxt to indicate the result of replacing t for all the free occurrences of x in ϕ, provided that x does not occur free in the scope of a quantifier of some variable of t.
      </paragraph>
      <paragraph label="Definition 12">
       The ML system {a mathematical formula}ML(BR) for a DFOL with languages {a mathematical formula}{Li} and bridge rules {a mathematical formula}BR is the triple {a mathematical formula}〈{Li},{Ωi},Δ〉, where {a mathematical formula}Ωi is empty and Δ contains the following inference rules:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       A formula tree in {a mathematical formula}ML(BR) is a tree Π which is constructed starting from a set of assumptions and axioms by applying the i-rules and b-rules given above. The occurrence of an arrow variable in a node {a mathematical formula}i:ϕ of a formula tree Π is called existential if this arrow variable does not occur in the assumptions from which {a mathematical formula}i:ϕ depends on. Given a formula tree Π with root {a mathematical formula}i:ϕ, an assumption {a mathematical formula}j:ψ is called local assumption if {a mathematical formula}i=j and the branch from {a mathematical formula}i:ϕ to {a mathematical formula}j:ψ contains only applications of i-rules. An assumption is global if it is not local. A set of assumptions is local (resp. global) iff all the assumptions it contains are local (resp. global). The distinction between local and global assumptions is necessary to correctly characterise the notion {a mathematical formula}⊨BR of DFOL logical consequence where, as we have seen in Proposition 6, the deduction theorem only holds with complete formulas or local assumptions. This distinction will become clearer in discussing restriction R3 introduced in the next definition. We only remark here that an application of a b-rule makes all the assumptions become global, and this reflects the fact that the satisfiability of bridge rules is defined over sets of local models, instead of a single model.
      </paragraph>
      <paragraph label="Definition 13">
       Derivability{a mathematical formula}i:ϕ is derivable in {a mathematical formula}ML(BR) from a set of global assumptions Γ and a set of local assumptions Σ, in symbols {a mathematical formula}(Γ,Σ)⊢BRi:ϕ, if there is a formula tree Π with root {a mathematical formula}i:ϕ, global assumptions Γ and local assumptions Σ such that the following restrictions on the application of the rules in Δ are satisfied:
      </paragraph>
      <list>
       <list-item label="R1.">
        The only rules whose premises can contain existential variables are {a mathematical formula}Cutji, {a mathematical formula}∨Eji, and {a mathematical formula}∃Eji.
       </list-item>
       <list-item label="R2.">
        The only rules that can introduce new existential variables are {a mathematical formula}→iIij, {a mathematical formula}i→Iij and {a mathematical formula}BR. In addition, the arrow variables contained in the conclusions of {a mathematical formula}→iIij and {a mathematical formula}i→Iij must be existential.
       </list-item>
       <list-item label="R3.">
        The application of {a mathematical formula}⊃Ii,⊥i,∃Eji,Cutji can discharge only assumptions that are either local or complete formulas. The application of {a mathematical formula}∨Eji can discharge only assumptions that are either local or such that at least one is a complete formula.
       </list-item>
       <list-item label="R4.">
        {a mathematical formula}Cutji and {a mathematical formula}∃Eji can be applied only if the existential variables in {a mathematical formula}j:ϕ do not occur in any other assumption employed in the derivation of {a mathematical formula}i:ψ. {a mathematical formula}∨Eji can be applied only if the existential variables in {a mathematical formula}j:ϕ∨ψ do not occur in any other assumption employed in the derivation of {a mathematical formula}i:θ.
       </list-item>
       <list-item label="R5.">
        {a mathematical formula}∀Ii can be applied only if x does not occur free in any assumption with index i, and {a mathematical formula}x→i and {a mathematical formula}xi→ do not appear in any assumption with index {a mathematical formula}j≠i.
       </list-item>
       <list-item label="R6.">
        {a mathematical formula}∃Eji can be applied only if x does not occur free in any assumption with index j different from {a mathematical formula}j:ϕ. Moreover, if {a mathematical formula}j=i then x cannot occur free in {a mathematical formula}i:ψ, otherwise if {a mathematical formula}j≠i, then {a mathematical formula}xj→ and {a mathematical formula}x→j cannot occur in {a mathematical formula}i:ψ or in any assumption employed to derive it.
       </list-item>
      </list>
      <paragraph>
       i-rules {a mathematical formula}⊃Ii, {a mathematical formula}⊃Ei, …, {a mathematical formula}∃Eji provide the DFOL version of Natural Deduction rules for logical connectives and quantifiers, respectively, while i-rules {a mathematical formula}=Ii and {a mathematical formula}=Ei are the DFOL version of Natural Deduction rules for the equality predicate. If we ignore the label of the formulae and restrictions R1–R6 (which will be illustrated in detail later), the shape of the inference rules for connectives, quantifiers, and equality is the same as the ones of first-order logic with equality. Rules {a mathematical formula}i→Iij and {a mathematical formula}→iIij are the proof theoretical counterpart of Property 8. In particular, {a mathematical formula}i→Iij states that x and y belong to the domain relation {a mathematical formula}rij, while {a mathematical formula}→iIij states that x and y belong to the domain relation {a mathematical formula}rji. Rule {a mathematical formula}BR provides an axiomatisation of the propagation of knowledge enforced by bridge rule {a mathematical formula}i1:ϕ1,…,in:ϕn→i:ϕ. Finally, {a mathematical formula}Cutji,∨Eji, and {a mathematical formula}∃Eji together with restrictions R1 and R4 regulate the usage of arrow variables within deduction trees and will be illustrated further in the remaining of the section.
      </paragraph>
      <paragraph>
       Restrictions R1–R6 are used to model the behaviour of local assumptions, global assumptions, and arrow variables. While restrictions R5 and R6 extend the restrictions of the FOL Natural Deduction rules {a mathematical formula}∀Ii and {a mathematical formula}∃Eji to take into account the occurrence of arrow variables, restrictions R1–R4 are proper to DFOL and deserve some explanation. Restriction R1 states that we cannot freely make inferences from inferred facts that contain existential arrow variables. In fact, existential arrow variables have, as their name suggest, an existential meaning. As a consequence, the same existential arrow variable occurring in, say, two different inferred formulae is not guaranteed to denote the same element of the domain in the proof. Therefore a way to control their usage in the proof tree is needed. To further clarify this point consider the following proof:{a mathematical formula} where the application of {a mathematical formula}∧Ii violates R1. In this case the application of {a mathematical formula}∧Ii allows to infer {a mathematical formula}Γ1,Γ2⊢BRi:ψ1∧ψ2(xj→) from {a mathematical formula}Γ1⊢BRi:ψ1(xj→) and {a mathematical formula}Γ2⊢BRi:ψ2(xj→). This inference is unsound. In fact, {a mathematical formula}Γ1⊨BRi:ψ1(xj→) and {a mathematical formula}Γ2⊨BRi:ψ2(xj→) guarantee that if {a mathematical formula}M satisfies both {a mathematical formula}Γ1[a] and {a mathematical formula}Γ2[a], then there are two extensions {a mathematical formula}a′ and {a mathematical formula}a″ of a, admissible for {a mathematical formula}i:ψ1(xj→) and {a mathematical formula}i:ψ2(xj→) respectively, such that {a mathematical formula}M satisfies both {a mathematical formula}i:ψ1(xj→)[a′] and {a mathematical formula}i:ψ2(xj→)[a″]. This unfortunately does not guarantee the existence of an extension {a mathematical formula}a‾ of a admissible for {a mathematical formula}i:ψ1∧ψ2(xj→) such that {a mathematical formula}M⊨i:ψ1∧ψ2(xj→)[a‾]. In fact, assume that {a mathematical formula}a′(xj→)=d′, {a mathematical formula}a′(xj→)=d″, with {a mathematical formula}d′≠d″ where {a mathematical formula}d′ is the only element of {a mathematical formula}domi in the interpretation of {a mathematical formula}ϕ1 and {a mathematical formula}d″ is the only element of {a mathematical formula}domi in the interpretation of {a mathematical formula}ϕ2. It is easy to see that for such a model {a mathematical formula}Γ1⊨BRi:ψ1(xj→) and {a mathematical formula}Γ2⊨BRi:ψ2(xj→), but {a mathematical formula}Γ1,Γ2⊭BRi:ψ1∧ψ2(xj→). To avoid unsound inferences of this kind we provide the ability to infer from formulas containing arrow existential variables using only rules which: (i) combine different proof trees, and (ii) infer one of the premises of the rule, possibly discharging assumptions, as in the case of {a mathematical formula}∨Eji,∃Eji and {a mathematical formula}Cutji.
      </paragraph>
      <paragraph>
       {a mathematical formula}Cutji is the rule that takes mostly care of existential arrow variables in proofs. The idea here is that if we have an inference Π of {a mathematical formula}k:α from Γ which makes use of an inference rule whose premises contain {a mathematical formula}i:ϕ(x→), with {a mathematical formula}x→ existential arrow variable, then we can split this inference in two parts {a mathematical formula}Π1,Π2 and then “glue” them with an application of {a mathematical formula}Cut as depicted below:{a mathematical formula} Restriction R4 ensures that we can perform this “gluing” only for sound deductions. For instance, we can use the {a mathematical formula}Cut rule to enable a sound application of {a mathematical formula}∧Ii as in the following proof tree{a mathematical formula} while we cannot use the {a mathematical formula}Cut rule to enable an unsound application of {a mathematical formula}∧Ii to obtain {a mathematical formula}i:ψ1∧ψ2(xj→) from {a mathematical formula}i:ψ1(xj→) and {a mathematical formula}i:ψ2(xj→) as in proof (56). The key point in proof (57) is obviously the occurrence of two distinct arrow variables {a mathematical formula}x1j→,x2j→, which rules out the scenario described in explaining proof (56).
      </paragraph>
      <paragraph>
       Restriction R2 regulates (prevents) the introduction of new existential variables in the proof. In fact, we must avoid the introduction of terms (existential variables, in this case) which may not denote any element. Consider, for instance, the following unrestricted application of {a mathematical formula}∨Ii{a mathematical formula} with {a mathematical formula}x→j new existential variable. This inference is unsound. In fact, given an assignment a for {a mathematical formula}i:ϕ, we cannot guarantee the existence of an extension {a mathematical formula}a′ admissible for {a mathematical formula}x→j in i (a trivial counter-model is the one with {a mathematical formula}rij=∅). However, if {a mathematical formula}i:ϕ depends upon an assumption {a mathematical formula}i:γ(x→j), then the application of {a mathematical formula}∨Ii satisfies restriction R2 (as {a mathematical formula}x→j is not existential anymore) and the inference of {a mathematical formula}i:ϕ∨ψ(x→j) from {a mathematical formula}i:ϕ is sound. In this case, assumption {a mathematical formula}i:γ(x→j) forces a to be already admissible for {a mathematical formula}x→j removing the obstacle shown above. Definition 8 and Proposition 8 instead ensure that {a mathematical formula}→iIij, {a mathematical formula}i→Iij and {a mathematical formula}BR can safely introduce new existential arrow variables.
      </paragraph>
      <paragraph>
       Restriction R3 reflects the fact that {a mathematical formula}⊨BR is defined over sets of local models, rather than a single model, and that this can cause the failure of the deduction theorem, as seen in Proposition 6. Thus, to ensure soundness of the inference rules we have to force global assumptions to be complete (in {a mathematical formula}∨Eji at least one of the disjuncts to be complete). If proofs consist only of local assumptions, then the requirement of being a complete formula can be dropped. In this case, in fact, {a mathematical formula}⊨BR reduces to first-order logical consequence (modulo arrow variables) as illustrated by property (5) in Proposition 5.
      </paragraph>
      <paragraph>
       We conclude the formal presentation of the DFOL calculus by proving that bridge rules are directional:
      </paragraph>
      <paragraph label="Proposition 11">
       DirectionalityGiven a set{a mathematical formula}BRof bridge rules such that k does not appear in the conclusion of a rule neither as the index of the conclusion nor as an index of an arrow variable, then{a mathematical formula}Γ⊢BRk:ϕiff{a mathematical formula}Γk⊢ϕ.
      </paragraph>
      <paragraph>
       The proof easily follows from the observation that the ML system {a mathematical formula}ML(BR) does not contain any deduction rule which enables to infer a formula in k (apart from local inference rules) unless k appears in the conclusion of a bridge rule as the index or as an index of an arrow variable. By showing that the DFOL calculus is a sound and complete axiomatisation of the notion of logical consequence of DFOL (Section 6.2) we can transfer the result of Proposition 11 to easily show that, for the specific set {a mathematical formula}BR of Proposition 11, {a mathematical formula}Γ⊨BRk:ϕ iff {a mathematical formula}Γk⊨ϕ.
      </paragraph>
      <paragraph>
       We illustrate now the usage of the calculus by applying it to the Magic box scenario. For the sake of presentation we present the proof using a linear notation (similar to the Lemmon-style for ND [72]) rather than a tree-based one. In this notation, each line of the deduction (the deduction step) contains a label, the inferred formula, the set of assumptions from which the inferred formula depends upon, and the inference rule used in the deduction step. Additional examples of proofs, which show how the calculus can be used to infer the statements corresponding to the entailed bridge rules of Proposition 10 can be found in [37].
      </paragraph>
      <paragraph label="Example 8">
       Let us consider the formalisation of the magic box presented in Example 5. Fig. 7 shows a proof where we use the b-rules derived from bridge rules (10) and (11) to prove that if {a mathematical formula}Mr.1 sees a ball in the box, then {a mathematical formula}Mr.2 sees a ball in the box too, that is:{a mathematical formula} Notationally, we use {a mathematical formula}BR(n) to denote the b-rule corresponding to the bridge rule in Equation (n). We also abbreviate “left” to “l” and “right” to “r”.The deduction starts from the assumption that, according to {a mathematical formula}Mr.1, there is a ball in the box (assumption (1)). From this fact, we can use local axioms and inference rules in the knowledge base of {a mathematical formula}Mr.1 to prove that the ball is in the right hand side slot or it is in the left hand side slot and the right hand side one is empty (these steps are omitted for the sake of presentation as our focus is on the usage of b-rules). We now reason by cases, considering first the case in which the ball is on the right hand side (step 4) and then the case in which the ball is in the left hand side slot and the right hand side is empty (step 9). In both cases we can infer that {a mathematical formula}Mr.2 also sees a ball (steps (8) and (12), respectively). This is done by using the b-rules {a mathematical formula}BR(10) and {a mathematical formula}BR(11), and by using the {a mathematical formula}Cut rule to handle the existential arrow variables introduced by {a mathematical formula}BR(10) and {a mathematical formula}BR(11). We can therefore use the “or elimination” rule to infer that {a mathematical formula}Mr.2 also sees a ball directly from the original “or” formula assumed in step (3), and then from assumption (1) by an application of an “exist elimination” rule.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Soundness and completeness
      </section-title>
      <paragraph>
       The goal of this section is to show that the calculus defined in Section 6 for a given set {a mathematical formula}BR of bridge rules is sound and complete with respect to the class of {a mathematical formula}BR-models defined in Section 3.3. In Appendix A we prove the Soundness Theorem and in Appendix B the Completeness Theorem. The main body of Appendix B concentrates on a method for constructing {a mathematical formula}BR-canonical models.
      </paragraph>
      <paragraph>
       Before stating the correspondence between {a mathematical formula}⊢BR and {a mathematical formula}⊨BR which we are going to prove in this section we need to introduce some notation. Given a set of formulas Σ, we use {a mathematical formula}e(Σ) to denote the set of formulas {a mathematical formula}i:∃yy=x→ such that {a mathematical formula}x→ is an arrow variable that occurs in a formula in Σ. {a mathematical formula}e(Σ) intuitively contains the statements of existence for all the arrow variables in Σ.
      </paragraph>
      <paragraph label="Theorem 4">
       Soundness and Completeness theorem{a mathematical formula}where Γ is the set of global assumptions and Σ is the set of local assumptions of the formula tree Π with root{a mathematical formula}i:ϕ.
      </paragraph>
      <paragraph>
       This theorem states that the calculus defined in the previous section computes a derivability relation {a mathematical formula}⊢BR which corresponds to the consequence relation {a mathematical formula}⊨BR between the global assumptions Γ of {a mathematical formula}⊢BR and the logical implication of {a mathematical formula}i:ϕ from the conjunction of all the local assumptions in Σ (that is, {a mathematical formula}i:⋀i:σ∈Σσ⊃ϕ), modulo the existence of all the arrow variables in Σ (that is, {a mathematical formula}e(Σ)). Its proof is a direct consequence of the proofs of Soundness and Completeness summarised in Appendix A and Appendix B, respectively, and provided in full in [37].
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proof of the soundness theorem
     </section-title>
     <paragraph label="Theorem 5">
      Soundness{a mathematical formula}(Γ,Σ)⊢BRi:ϕ⟹Γ,e(Σ)⊨BRi:⋀i:σ∈Σσ⊃ϕ The proof of the Soundness theorem makes use of the following lemma and notation.
     </paragraph>
     <paragraph label="Lemma 1">
      Let a and{a mathematical formula}a′be two assignments that agree on the values assigned to the arrow and free variables of ϕ. Then:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}M⊨i:ϕ[a]if and only if{a mathematical formula}M⊨i:ϕ[a′].
      </list-item>
      <list-item label="•">
       {a mathematical formula}m⊨ϕ[ai]if and only if{a mathematical formula}m⊨ϕ[ai′].
      </list-item>
     </list>
     <paragraph>
      The proof of Lemma 1 follows easily from the definition of satisfiability and from the fact that a and {a mathematical formula}a′ agree on the interpretation of all the variables of ϕ.
     </paragraph>
     <paragraph>
      We write {a mathematical formula}a(i:x=d) to denote the assignment obtained from a by setting {a mathematical formula}ai(x)=d and by letting both {a mathematical formula}aj(x→i) and {a mathematical formula}aj(xi→) undefined. Let t be an i-term, m a local model of {a mathematical formula}Li, and a an assignment admissible for t, we write {a mathematical formula}m(t)[a] to denote the interpretation of t in the local model (first-order interpretation) m under the assignment a. Let a be an assignment strictly admissible for Γ and {a mathematical formula}Δ⊆Γ, we define {a mathematical formula}a|Δ to be the reduction of a strictly admissible for Δ:{a mathematical formula} Given two assignments a and {a mathematical formula}a′ defined over two sets of (regular and arrow) variables X and {a mathematical formula}X′, such that they agree on the set of variables {a mathematical formula}X∩X′ they have in common,{sup:12} we define the assignment {a mathematical formula}a+a′ as follows:{a mathematical formula} Finally, for the sake of readability we write ⋀Σ as a shorthand for {a mathematical formula}⋀i:σ∈Σσ.
     </paragraph>
     <paragraph label="Proof of Theorem 5">
      The proof is by induction on the structure of the derivation of {a mathematical formula}i:ϕ from {a mathematical formula}(Γ,Σ). We first prove the theorem for {a mathematical formula}(Γ,Σ)⊢BRi:ϕ with a one step derivation (base case). Then we prove the theorem for {a mathematical formula}(Γ,Σ)⊢BRi:ϕ with a deduction Π of length {a mathematical formula}n+1, by assuming that the theorem holds for all deductions {a mathematical formula}Π′ of length ≤n and proving that it holds also for Π (inductive step). For the sake of space we include here the proof of the inductive step for a subset of paradigmatic inference rules ρ among the ones presented at page 25. The complete proof for all inference rules can be found in [37]. Base Case:If {a mathematical formula}(Γ,Σ)⊢BRi:ϕ with a one step derivation, then either {a mathematical formula}i:ϕ is an assumption or a direct application of {a mathematical formula}=Ii with {a mathematical formula}n=0. If {a mathematical formula}i:ϕ is an assumption, then we have to prove that {a mathematical formula}e(i:ϕ)⊨i:ϕ⊃ϕ. Let us assume that {a mathematical formula}M⊨e(i:ϕ)[a]. This means that {a mathematical formula}ai is defined on all the arrow variables of ϕ. Therefore, for every {a mathematical formula}m∈Mi, {a mathematical formula}m⊨ϕ⊃ϕ[a] and the proof is done. If {a mathematical formula}i:ϕ is the consequence of an application of {a mathematical formula}=Ii with {a mathematical formula}n=0, then it is of the form {a mathematical formula}i:t=t and t does not contain any arrow variable. This implies that {a mathematical formula}M⊨i:t=t[a] for all models {a mathematical formula}M and assignments a, which also concludes the proof.{a mathematical formula}⊃IiIf {a mathematical formula}(Γ,Σ)⊢BRi:ϕ⊃ψ, and the last rule used is {a mathematical formula}⊃Ii, then {a mathematical formula}(Γ,Σ∪{i:ϕ})⊢BRi:ϕ⊃ψ also holds.To prove that {a mathematical formula}Γ,e(Σ)⊨BRi:⋀Σ⊃(ϕ⊃ψ), let {a mathematical formula}M be a {a mathematical formula}BR-model and a an assignment strictly admissible for {a mathematical formula}Γ,e(Σ) such that {a mathematical formula}M⊨Γ,e(Σ)[a]. From the restriction R1, ϕ and ψ cannot contain existential arrow variables (that is, arrow variables not contained in the premises). Therefore what we have to prove is that {a mathematical formula}M⊨i:⋀Σ⊃(ϕ⊃ψ)[a]. We do this by distinguishing two cases: {a mathematical formula}i:ϕis a local assumption.From the fact that {a mathematical formula}(Γ,Σ∪{i:ϕ})⊢BRi:ϕ⊃ψ is a deduction {a mathematical formula}Π′ of length ≤n we can apply the inductive hypothesis and obtain that {a mathematical formula}Γ,e(Σ∪{i:ϕ})⊨BRi:(⋀Σ∧ϕ)⊃ψ. Since {a mathematical formula}i:ϕ does not contain any existential arrow variable (restriction R1), then {a mathematical formula}M⊨Γ,e(Σ∪{i:ϕ})[a]. Thus, from the inductive hypothesis we have that {a mathematical formula}M⊨i:(⋀Σ∧ϕ)⊃ψ[a]. Since {a mathematical formula}(⋀Σ∧ϕ)⊃ψ is equivalent to {a mathematical formula}⋀Σ⊃(ϕ⊃ψ), and they contain the same arrow variables, we can conclude that {a mathematical formula}M⊨i:⋀Σ⊃(ϕ⊃ψ), and this ends the proof.{a mathematical formula}i:ϕis a global assumption.In this case from the inductive hypothesis we obtain that {a mathematical formula}Γ∪{i:ϕ},e(Σ)⊨BRi:⋀Σ⊃ψ. From the restriction R3 we have that {a mathematical formula}i:ϕ is a complete formula, and either {a mathematical formula}M⊨i:ϕ[a] or {a mathematical formula}M⊨i:¬ϕ[a]. Let us consider the two cases separately. If {a mathematical formula}M⊨i:ϕ[a] we can use the inductive hypothesis to prove that {a mathematical formula}M⊨i:⋀Σ⊃ψ[a]. This, in turn, implies that {a mathematical formula}M⊨i:⋀Σ⊃(ϕ⊃ψ)[a]; if {a mathematical formula}M⊨i:¬ϕ[a] then {a mathematical formula}M⊨i:⋀Σ⊃(ϕ⊃ψ)[a] from the definition of first-order satisfiability, and this ends the proof.{a mathematical formula}i→IijIf {a mathematical formula}(Γ,Σ)⊢BRj:xi→=y and the last rule used is {a mathematical formula}i→Iij, then {a mathematical formula}i≠j, and {a mathematical formula}Σ=∅.{sup:13} Thus, we have to show that {a mathematical formula}Γ⊨BRj:xi→=y.From the shape of the {a mathematical formula}i→Iij rule we know that there is a formula {a mathematical formula}i:x=y→j and two sets {a mathematical formula}Γ1,Σ1 with {a mathematical formula}Γ=Γ1∪Σ1 such that {a mathematical formula}Γ1,Σ1⊢BRi:x=y→j. Thus from the inductive hypothesis we know that {a mathematical formula}Γ1,e(Σ1)⊨BRi:⋀Σ1⊃(x=y→j).Let a be an assignment strictly admissible for Γ such that {a mathematical formula}M⊨Γ[a]. We have to prove that there is an extension {a mathematical formula}a′ of a for {a mathematical formula}j:xi→=y such that {a mathematical formula}M⊨j:xi→=y. From {a mathematical formula}M⊨Γ[a] we have that {a mathematical formula}M⊨Γ1,e(Σ1)[a], and from the inductive hypothesis and the fact that {a mathematical formula}i→Iij cannot be applied to formulae containing existential arrow variables (restriction R1) we also have that {a mathematical formula}M⊨:⋀Σ1⊃(x=y→j)[a]. Again from {a mathematical formula}M⊨Γ[a] we have that {a mathematical formula}M⊨i:x=y→j[a]. This implies that {a mathematical formula}ai(x)=ai(y→j). From restriction R2 we know that {a mathematical formula}xi→ is an existential variable in {a mathematical formula}j:xi→=y. Thus {a mathematical formula}aj(xi→) is undefined, and we can obtain a new assignment {a mathematical formula}a′ by adding to a the value {a mathematical formula}aj′(xi→)=aj(y). We have to show that {a mathematical formula}(ai′(x),aj′(xi→))∈rij. This follows from the fact that {a mathematical formula}(ai′(x),aj′(xi→))=(ai(x)=aj(y))=(ai(y→j),aj(y)), and from the fact that {a mathematical formula}(ai(y→j),aj(y))∈rij because of the fact that a is an assignment (see Definition 4). Since {a mathematical formula}aj′(xi→)=aj′(y) we have that {a mathematical formula}m⊨j:xi→=y[a′] and this ends the proof.{a mathematical formula}BR:If {a mathematical formula}(Γ,Σ)⊢BRi:ϕ and the last rule used is {a mathematical formula}BR, then {a mathematical formula}Σ=∅ because the application of a b-rule makes all the local assumptions become global. Thus we have to prove that {a mathematical formula}Γ⊨BRi:ϕ. From the inductive hypothesis we know that there are n formulae {a mathematical formula}i1:ϕ1,…,in:ϕn such that {a mathematical formula}Γ1,e(Σ1)⊨BRi1:⋀Σ1⊃ϕ1,…,Γn,e(Σn)⊨BRin:⋀Σn⊃ϕn with {a mathematical formula}Γk⊆Γ and {a mathematical formula}Σk⊆Γ for all {a mathematical formula}1≤k≤n.Let a be an assignment strictly admissible for Γ such that {a mathematical formula}M⊨Γ[a]. Since {a mathematical formula}Σk⊆Γ, then a is admissible for all the variables in {a mathematical formula}Σk, for all {a mathematical formula}1≤k≤n. Let {a mathematical formula}a|Γk,e(Σk) be the restrictions of a strictly admissible for {a mathematical formula}Γk,e(Σk). Then, {a mathematical formula}M⊨Γk,e(Σk)[a|Γk,e(Σk)] holds. From the restriction R1 which states that each {a mathematical formula}ik:ϕk cannot contain existential arrow variables, and the inductive hypothesis, we infer that {a mathematical formula}M⊨ik:⋀Σk⊃ϕk[a|Γk,e(Σk)]. Since {a mathematical formula}M⊨Γ and {a mathematical formula}Σk⊆Γ we have that {a mathematical formula}M⊨ik:ϕk for all {a mathematical formula}1≤k≤n. From the definition of satisfiability of a bridge rule we know that a can be extended to an assignment {a mathematical formula}a′ such that {a mathematical formula}M⊨i:ϕ[a′], and this ends the proof.{a mathematical formula}CutjiIf {a mathematical formula}(Γ,Σ)⊢BRi:ψ and the last rule used is {a mathematical formula}Cutji, then there exists a formula {a mathematical formula}j:ϕ and two pairs {a mathematical formula}(Γk,Σk), {a mathematical formula}k=1,2 with {a mathematical formula}Γk⊆Γ∪Σ and {a mathematical formula}Σk⊆Γ∪Σ such that{a mathematical formula} We prove that {a mathematical formula}Γ,e(Σ)⊨BRi:⋀Σ⊃ψ by considering two different cases: {a mathematical formula}j:ϕis a local assumption.In this case {a mathematical formula}i=j, {a mathematical formula}Γ=Γ1∪Γ2, {a mathematical formula}Σ=Σ1∪Σ2, and from the inductive hypothesis we have:{a mathematical formula}{a mathematical formula}Let a be an assignment strictly admissible for {a mathematical formula}Γ,e(Σ) such that {a mathematical formula}M⊨Γ,e(Σ)[a], and let m be an arbitrary local model in {a mathematical formula}Mi. We have to prove that there is an extension {a mathematical formula}a′ of a for {a mathematical formula}i:ψ such that if {a mathematical formula}m⊨σ[a′] for all {a mathematical formula}σ∈Σ then {a mathematical formula}m⊨ψ[a′].Let {a mathematical formula}a|Γ1,e(Σ1) be the restriction of a strictly admissible for {a mathematical formula}Γ1,e(Σ1). Then {a mathematical formula}M⊨Γ1,e(Σ1)[a|Γ1,e(Σ1)], and from the inductive hypothesis (A.1){a mathematical formula}a|Γ1,e(Σ1) can be extended to an assignment {a mathematical formula}a¯|Γ1,e(Σ1) admissible for {a mathematical formula}i:ϕ such that{a mathematical formula} Let {a mathematical formula}a|Γ2,e(Σ2) be the restriction of a strictly admissible for {a mathematical formula}Γ2,e(Σ2). Then {a mathematical formula}M⊨Γ2,e(Σ2)[a|Γ2,e(Σ2)]. Restriction R4 imposes that the existential arrow variables occurring in {a mathematical formula}i:ϕ do not occur in any of the assumptions in {a mathematical formula}Γ2 and {a mathematical formula}Σ2. Thus we can extend {a mathematical formula}a|Γ2,e(Σ2) to an assignment {a mathematical formula}a¯|Γ2,e(Σ2) admissible for {a mathematical formula}i:ϕ by adding to {a mathematical formula}a|Γ2,e(Σ2) the assignment of the existential arrow variables of {a mathematical formula}i:ϕ according to {a mathematical formula}a¯|Γ1,e(Σ1). Then it is easy to show that {a mathematical formula}M⊨Γ2,e(Σ2∪{i:ϕ})[a¯|Γ2,e(Σ2)], and from the inductive hypothesis (A.2) we can infer that {a mathematical formula}a¯|Γ2,e(Σ2) can be extended to an assignment {a mathematical formula}a¯¯|Γ2,e(Σ2) for {a mathematical formula}i:ψ such that{a mathematical formula} Let m be a local model in {a mathematical formula}Mi such that {a mathematical formula}m⊨σ[a] for all {a mathematical formula}σ∈Σ. Since m satisfies all the formulae in {a mathematical formula}Σ1, then we can use (A.3) to obtain {a mathematical formula}m⊨ϕ[a¯|Γ1,e(Σ1)]. By construction we also have that {a mathematical formula}m⊨ϕ[a¯¯|Γ2,e(Σ2)] and {a mathematical formula}m⊨Σ2[a¯¯|Γ2,e(Σ2)]. Thus {a mathematical formula}m⊨ψ[a¯¯|Γ2,e(Σ2)] and this ends the proof.{a mathematical formula}j:ϕis a global assumption.Here we distinguish two cases: {a mathematical formula}i=j and {a mathematical formula}i≠j.If {a mathematical formula}i=j, then {a mathematical formula}Γ=Γ1∪Γ2, {a mathematical formula}Σ=Σ1∪Σ2, {a mathematical formula}i:ϕ is a complete formula (restriction R3) and from the inductive hypothesis we have:{a mathematical formula}{a mathematical formula}Let a be an assignment strictly admissible for {a mathematical formula}Γ,e(Σ) such that {a mathematical formula}M⊨Γ,e(Σ)[a], and let m be an arbitrary local model in {a mathematical formula}Mi. We have to prove that there is an extension {a mathematical formula}a′ of a for {a mathematical formula}i:ψ such that if {a mathematical formula}m⊨σ[a′] for all {a mathematical formula}σ∈Σ then {a mathematical formula}m⊨ψ[a′].Let {a mathematical formula}a|Γ1,e(Σ1) be the restriction of a strictly admissible for {a mathematical formula}Γ1,e(Σ1). Then {a mathematical formula}M⊨Γ1,e(Σ1)[a|Γ1,e(Σ1)], and from the inductive hypothesis (A.5){a mathematical formula}a|Γ1,e(Σ1) can be extended to an assignment {a mathematical formula}a¯|Γ1,e(Σ1) admissible for {a mathematical formula}i:ϕ such that{a mathematical formula} Let {a mathematical formula}a|Γ2,e(Σ2) be the restriction of a strictly admissible for {a mathematical formula}Γ2,e(Σ2). Then {a mathematical formula}M⊨Γ2,e(Σ2)[a|Γ2,e(Σ2)]. Restriction R4 imposes that the existential arrow variables occurring in {a mathematical formula}i:∃xϕ do not occur in any of the assumptions in {a mathematical formula}Γ2 and {a mathematical formula}Σ2. Thus we can extend {a mathematical formula}a|Γ2,e(Σ2) to an assignment {a mathematical formula}a¯|Γ2,e(Σ2) admissible for {a mathematical formula}i:ϕ by adding to {a mathematical formula}a|Γ2,e(Σ2) the assignment of the existential arrow variables of {a mathematical formula}i:ϕ according to {a mathematical formula}a¯|Γ1,e(Σ1). Then it is easy to show that if {a mathematical formula}M⊨i:ϕ[a¯|Γ2,e(Σ2)], then we can use the inductive hypothesis (A.6) to infer that {a mathematical formula}a¯|Γ2,e(Σ2) can be extended to an assignment {a mathematical formula}a¯¯|Γ2,e(Σ2) for {a mathematical formula}i:ψ such that{a mathematical formula} Let m be a local model in {a mathematical formula}Mi such that {a mathematical formula}m⊨σ[a] for all {a mathematical formula}σ∈Σ. Since m satisfies all the formulae in {a mathematical formula}Σ1, then we can use (A.7) to obtain {a mathematical formula}m⊨ϕ[a¯|Γ1,e(Σ1)]. Since ϕ is a complete formula, we have that {a mathematical formula}M⊨i:ϕ[a¯|Γ1,e(Σ1)]. From the way {a mathematical formula}a¯|Γ2,e(Σ2)(i:x=d) is built, we know that {a mathematical formula}M⊨i:ϕ[a¯|Γ1,e(Σ1)]. Thus we can apply the inductive hypothesis to infer (A.8) to obtain {a mathematical formula}M⊨i:⋀Σ2⊃ψ[a¯¯|Γ2,e(Σ2)(i:x=d)].{a mathematical formula}m⊨Σ2[a¯¯|Γ2,e(Σ2)(i:x=d)], from the fact that it satisfies all the formulae in Σ under the assignment a, and that {a mathematical formula}[a¯¯|Γ2,e(Σ2)(i:x=d)] is built from a restriction of a. Thus {a mathematical formula}m⊨ψ[a¯¯|Γ2,e(Σ2)(i:x=d)], and this ends the proof.If {a mathematical formula}i≠j, the proof can be obtained as in the previous case, just taking into account that {a mathematical formula}Γ=Γ1∪Σ1∪Γ2, and {a mathematical formula}Σ=Σ2 (that is, the local assumptions of {a mathematical formula}Σ1 become global due to the change of index from j to i triggered by {a mathematical formula}Cutji). □
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Proof of the completeness theorem
     </section-title>
     <paragraph label="Theorem 6">
      Completeness{a mathematical formula}Γ,e(Σ)⊨BRi:⋀i:σ∈Σσ⊃ϕ⟹(Γ,Σ)⊢BRi:ϕ
     </paragraph>
     <paragraph>
      The contrapositive will be proved: it will be shown that if {a mathematical formula}(Γ,Σ)⊬BRi:ϕ then there exists a {a mathematical formula}BR-model {a mathematical formula}Mc and an assignment a such that {a mathematical formula}M⊨Γ[a], {a mathematical formula}M⊨e(Σ)[a] but {a mathematical formula}M⊭i:⋀i:σ∈Σσ⊃ϕ[a]. The technique we use is based on the construction of canonical model {a mathematical formula}Mc using the method of models constructed from constants originally due to Henkin [73] (see also [74]). This method is based on the ability of constructing a canonical models {a mathematical formula}Mc starting from maximal consistent sets of formulae and an appropriate set of constants (or existential witnesses). The situation in DFOL is more complex than the one of FOL due to the following three reasons: first, the presence of sets of formulas belonging to different languages; second, the presence of partial knowledge; and finally, the presence of arrow variables.
     </paragraph>
     <paragraph>
      The generalisation of the Henkin technique to the case of DFOL is composed by the following steps:
     </paragraph>
     <list>
      <list-item label="1.">
       We generalise the notion of consistency to k-consistency (Definitions 14);
      </list-item>
      <list-item label="2.">
       We introduce the operators cl and {a mathematical formula}⊗i (Definition 15, Definition 16) to be able to deal with sets of sets of formulas and we show some relevant properties of these operators (Lemma 2);
      </list-item>
      <list-item label="3.">
       We modify the Henkin technique to extend a consistent set Γ of DFOL formulas to a set with existential witnesses (Lemma 3);
      </list-item>
      <list-item label="4.">
       We introduce the notion of k-saturated set of formulas (Definition 18) and show how to saturate a k-consistent set of formulas (Lemma 5);
      </list-item>
      <list-item label="5.">
       We define the canonical model {a mathematical formula}Mc as a compatibility relation over sets of (local) models satisfying maximal-k-consistent sets of formulas (Definition 19);
      </list-item>
      <list-item label="6.">
       We show that {a mathematical formula}Mc is a {a mathematical formula}BR-model (Lemma 7).
      </list-item>
     </list>
     <paragraph>
      As already observed in [13], the first step in proving completeness for logical systems whose formulas are scattered among different languages is the introduction of specific notions of consistency and maximal consistency, which generalise the analogous concepts given in [74].
     </paragraph>
     <paragraph label="Definition 14">
      k-ConsistencyΓ is k-consistent if {a mathematical formula}Γ⊬BRk:⊥.
     </paragraph>
     <paragraph>
      This generalisation is needed as a set of DFOL formulas Γ can be locally inconsistent with respect to an index i without being inconsistent with respect to some different index j, that is, {a mathematical formula}Γ⊢BRi:⊥ but {a mathematical formula}Γ⊬BRj:⊥. Thus, we have to prove that every k-consistent set of formulas Γ of DFOL has a (canonical) model, which associates a non empty set {a mathematical formula}Mk of local models to the language {a mathematical formula}Lk.
     </paragraph>
     <paragraph>
      The second step in proving completeness for DFOL is to be able to work with sets of labelled formulas. In fact the scattering of the system in different languages implies that we have to build a canonical model structured as a family {a mathematical formula}M0,M1,… of sets of interrelated (local) models spanning over different languages. From now on we use {a mathematical formula}Γi to denote a set of formulas in {a mathematical formula}Li, and {a mathematical formula}Γi to denote a (finite or infinite) set {{a mathematical formula}Γi0,Γi1,…,Γin,…} of sets of formulas in {a mathematical formula}Li. We instead use Γ to denote a family {a mathematical formula}{Γ0,Γ1,…} of sets {a mathematical formula}Γi of sets of formulas, one for each i in I. The closure of a set {a mathematical formula}Γi of formulas in {a mathematical formula}Li, denoted as {a mathematical formula}cl(Γi), is defined as the set of formulas derivable from {a mathematical formula}Γi using the deduction rules of first-order logic in the context i, and considering the arrow variables occurring in {a mathematical formula}Γi as constants. The closure of a set Γ is instead defined as the set containing all (and only) the formulas {a mathematical formula}i:ϕ that belong to the deductive closure {a mathematical formula}cl(Γi) of all {a mathematical formula}Γi∈Γi, for all {a mathematical formula}i∈I. Formally,
     </paragraph>
     <paragraph label="Definition 15">
      Closure of ΓLet {a mathematical formula}Γ={Γ0,Γ1,…} be a family of sets of sets of formulas in {a mathematical formula}{L0,L1,…}. The closure of Γ, in symbols {a mathematical formula}cl(Γ), is defined as:{a mathematical formula}
     </paragraph>
     <paragraph>
      We say that {a mathematical formula}i:ϕ is derivable from Γ iff {a mathematical formula}i:ϕ is derivable from {a mathematical formula}cl(Γ). Analogously, we say that Γ is k-consistent, iff {a mathematical formula}cl(Γ) is k-consistent. We also write {a mathematical formula}Γ⊢BRi:ϕ as a shorthand for {a mathematical formula}cl(Γ)⊢BRi:ϕ.
     </paragraph>
     <paragraph>
      Note that the computation of {a mathematical formula}cl(Γ) does not take into account any b-rule in {a mathematical formula}ML(BR) but only the (local) i-rules for first-order logic with equality of the different knowledge sources. Instead the deduction of formulas from {a mathematical formula}cl(Γ) is performed taking into account the entire deductive calculus of {a mathematical formula}ML(BR).
     </paragraph>
     <paragraph>
      Given a set of arrow variables {a mathematical formula}AV=⋃i∈IAVi, we define the closure ofΓw.r.t. AV as before but considering the arrow variables in AV like regular first-order terms. We define the notions of derivability from Γ w.r.t. AV and of k-consistency of Γ w.r.t. AV, accordingly.
     </paragraph>
     <paragraph label="Example 9">
      We illustrate the difference between the closure of Γ and the closure of Γ w.r.t. AV by means of an example. Let Γ be a set such that each {a mathematical formula}Γi∈Γi satisfies the fact that a deduction {a mathematical formula}Γi,x=z→⊢ψ involving only formulas in i exists. If there is no other way of proving ψ from all {a mathematical formula}Γi, then {a mathematical formula}ψ∉cl(Γ). This holds because an additional formula {a mathematical formula}x=z→ outside {a mathematical formula}Γi is used to infer it. If {a mathematical formula}z→∈AV and we treat {a mathematical formula}z→ as a first-order regular term, then {a mathematical formula}∃x.x=z→ becomes a regular first-order (valid) formula and therefore we can apply the ∃ elimination rule to obtain a deduction of ψ from {a mathematical formula}Γi (for all i) as follows:{a mathematical formula} Thus, while ψ does not belong to the closure of Γ it belongs to the closure of Γ w.r.t. AV.
     </paragraph>
     <paragraph>
      To be able to generalise the Henkin technique to DFOL, where we need to manipulate sets of sets of formulas Γ, we introduce an operator {a mathematical formula}⊗i, that we use to perform a kind of cross product between sets of formulas.
     </paragraph>
     <paragraph label="Definition 16">
      {a mathematical formula}⊗iLet {a mathematical formula}Σi be a set of formulas in {a mathematical formula}Li. {a mathematical formula}Γ′=Γ⊗iΣi is defined as:{a mathematical formula}
     </paragraph>
     <paragraph label="Example 10">
      Let {a mathematical formula}Γ={Γ1,Γ2} where:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Γ1={{1:A}}
      </list-item>
      <list-item label="•">
       {a mathematical formula}Γ2={{2:B,2:C},{2:¬C}}
      </list-item>
     </list>
     <paragraph label="Lemma 2">
      Let{a mathematical formula}{ϕ1,…,ϕn}be a set of formulas of{a mathematical formula}Li.{a mathematical formula}Γ⊗i{ϕ1,…,ϕn}⊢BRj:ψif and only if{a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn⊢BRj:ψ.
     </paragraph>
     <paragraph label="Proof">
      From the notion of derivability from Γ the statement of the theorem can be reformulated in {a mathematical formula}cl(Γ⊗i{ϕ1,…,ϕn})⊢BRj:ψ if and only if {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn⊢BRj:ψ. In the proof we use Φ to denote the set of {a mathematical formula}Li-formulas {a mathematical formula}{ϕ1,…,ϕn}.“If” direction. Assume that {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn⊢BRj:ψ with a proof Π, and let {a mathematical formula}j1:ψ1,…,jm:ψm be the undischarged assumptions of Π. We show that all the undischarged assumptions of Π can be derived from {a mathematical formula}cl(Γ⊗i{ϕ1,…,ϕn}).For each undischarged assumption {a mathematical formula}jk:ψk, {a mathematical formula}k=1,…,m, we have to consider two cases: (a) {a mathematical formula}ik:ψk∈cl(Γ), and (b) {a mathematical formula}ik:ψk=i:ϕ1∨…∨ϕn:
      <list>
       If {a mathematical formula}ik:ψk∈cl(Γ) then we have to consider two separate cases: if {a mathematical formula}ik≠i then {a mathematical formula}ik:ψk∈cl(Γ)⊗iΦ since {a mathematical formula}cl(Γ) and {a mathematical formula}cl(Γ⊗iΦ) contain the same set of formulas with index {a mathematical formula}j≠i; if {a mathematical formula}ik=i it is easy to see from the definition of the operator {a mathematical formula}cl(.) that{a mathematical formula} This is true because derivability in FOL (and therefore the FOL deductive closure of a set of {a mathematical formula}Li-formulas) is monotone.If {a mathematical formula}ik:ψk=i:ϕ1∨…∨ϕn, then we can easily see that {a mathematical formula}i:ϕ1∨…∨ϕn is derivable, via {a mathematical formula}∨Ii, from all the sets {a mathematical formula}Γi∪ϕl (with {a mathematical formula}Γi∈Γi and {a mathematical formula}ϕl∈Φ). Therefore, from the definition of {a mathematical formula}cl(Γ), {a mathematical formula}i:ϕ1∨…∨ϕn∈cl(Γ⊗iΦ).“Only if” direction
      </list>
      <paragraph>
       . Assume that {a mathematical formula}Γ⊗iΦ⊢BRj:ψ with a proof Π, and let {a mathematical formula}j1:ψ1,…,jm:ψm be the undischarged assumptions of Π. Then all {a mathematical formula}j1:ψ1,…,jm:ψm belong to {a mathematical formula}cl(Γ⊗iΦ) and we show that they can be derived from {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn.For each undischarged assumption {a mathematical formula}jk:ψk, {a mathematical formula}k=1,…,m, we have to consider two cases: (a) {a mathematical formula}ik≠i and (b) {a mathematical formula}ik=i.
      </paragraph>
      <list>
       <list-item label="(a)">
        Assume that {a mathematical formula}ik≠i. From the definition of {a mathematical formula}⊗i and the fact that it only modifies the set {a mathematical formula}Γi, and from the definition of closure ({a mathematical formula}cl(.)) over a set {a mathematical formula}Γi of FOL formulas we can easily see that{a mathematical formula} Thus, since {a mathematical formula}ik:ψk∈cl(Γ⊗iΦ), we can prove that {a mathematical formula}ψk∈cl(Γ).
       </list-item>
       <list-item label="(b)">
        Assume that {a mathematical formula}ik=i. From the definition of {a mathematical formula}⊗i and {a mathematical formula}cl(.) we have that{a mathematical formula}This implies that for all {a mathematical formula}Γi∈Γi, {a mathematical formula}ψk is derivable from all {a mathematical formula}Γi∪ϕl for all {a mathematical formula}ϕl∈Φ with a first-order deduction. We can therefore apply {a mathematical formula}∨Eii to obtain that {a mathematical formula}ik:ψk is derivable from {a mathematical formula}Γi,i:ϕ1∨…∨ϕn, for all {a mathematical formula}Γi∈Γi. Note that Restriction R4 is satisfied as {a mathematical formula}i:ϕ1∨…∨ϕn does not contain existential arrow variables (as it does not depend upon any assumption), and Restriction R3 is satisfied as the derivation of {a mathematical formula}ψk from each of the {a mathematical formula}Γi∪ϕl is local (and therefore we can apply {a mathematical formula}∨Eii and discharge the different {a mathematical formula}ϕl). Therefore we can easily build a deduction {a mathematical formula}Πk of {a mathematical formula}ψk from {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn.
       </list-item>
      </list>
      <paragraph>
       Since all the undischarged assumptions {a mathematical formula}j1:ψ1,…,jm:ψm of Π are derivable from the set {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn we can build a deduction of {a mathematical formula}i:ψ from {a mathematical formula}cl(Γ),i:ϕ1∨…∨ϕn and this ends the proof. □
      </paragraph>
     </paragraph>
     <paragraph>
      The proof of completeness proceeds with the construction of the canonical model {a mathematical formula}Mc using the method of models constructed from constants (see [73], [74]). Roughly speaking the Henkin approach is based on two fundamental ideas: first, for each existential sentence {a mathematical formula}∃xϕ(x) in the language, one adds a new constant c, the so-called existential witness, to the language and inserts an axiom {a mathematical formula}∃xϕ(x)⊃ϕ(c) to the theory; second, the canonical model is built using equivalence classes of existential witnesses as domain elements. Differently from the classical proof for first-order logic, the presence of partial knowledge implies that a DFOL formula {a mathematical formula}i:∃xϕ(x) does not necessarily entail a formula {a mathematical formula}i:ϕ(c) for some c (unless ϕ is a complete formula). This fact forces us to modify the original technique of existential witnesses as follows: we start from a k-consistent set of formulas Γ and examine all the formulas {a mathematical formula}j:ϕ(x) in {a mathematical formula}{Li} with one free variable; if {a mathematical formula}j:∃xϕ(x) is a complete formula then we add the existential witness {a mathematical formula}j:ϕ(c) as usual, while if it is a “regular” (that is, non-complete) formula we add an infinite set of witnesses {a mathematical formula}j:ϕ(c1),…,j:ϕ(cn),…, one for each possible interpretation in {a mathematical formula}Mi (Lemma 3).
     </paragraph>
     <paragraph>
      We first extend the definition of existential witness to the case of multiple languages.
     </paragraph>
     <paragraph label="Definition 17">
      Existential witnessLet Γ be a set {a mathematical formula}{Γ0,Γ1,…} of formulas in {a mathematical formula}{Li}={L0,L1,…} and let {a mathematical formula}C={C0,C1,…} be a set of constant symbols such that each {a mathematical formula}Ci is a set of constants of {a mathematical formula}Li. We say that {a mathematical formula}C is a set of witnesses for Γ in {a mathematical formula}{Li} iff for every formula {a mathematical formula}i:ϕ(x) with exactly one free variable x in {a mathematical formula}Li the following holds:
     </paragraph>
     <list>
      <list-item label="•">
       if {a mathematical formula}i:ϕ(x) is a complete formula, then there is a constant {a mathematical formula}c∈Ci such that {a mathematical formula}Γ⊢BRi:∃ϕ(x)⊃ϕ(c);
      </list-item>
      <list-item label="•">
       if {a mathematical formula}i:ϕ(x) is a non complete formula, then there is a set of constants {a mathematical formula}c1,…,ck,…∈Ci such that {a mathematical formula}Γi⊢BRi:∃ϕ(x)⊃ϕ(ci) for each {a mathematical formula}Γi∈Γi.
      </list-item>
     </list>
     <paragraph label="Lemma 3">
      Let Γ be a k-consistent set of sentences of{a mathematical formula}{Li}. Let{a mathematical formula}Cbe a set{a mathematical formula}{Ci}of new constant symbols of power{a mathematical formula}|C|=∥{Li}∥, and let{a mathematical formula}{Li∪Ci}be the family of languages defined as the simple expansion of each{a mathematical formula}Liformed by adding{a mathematical formula}{Ci}. Then Γ can be extended to a k-consistent set of set of sentences{a mathematical formula}Γ⁎in{a mathematical formula}{Li∪Ci}which has{a mathematical formula}Cas a set of witnesses in{a mathematical formula}{Li∪Ci}.
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula} be an enumeration of all the formulas in {a mathematical formula}{Li} that contain exactly one free variable x. Let {a mathematical formula}C be an infinitely enumerable set of variables. We “split” {a mathematical formula}C into an enumerable sequence of disjoint sets W, {a mathematical formula}U1, {a mathematical formula}U2, {a mathematical formula}U3, …as follows{a mathematical formula} such that {a mathematical formula}V=W∪U1∪U2∪U3∪…. We define an infinite sequence {a mathematical formula}Γ0,Γ1,… as follows:
      <list>
       {a mathematical formula}Γ0 is such that {a mathematical formula}Γi0={Γi} for all {a mathematical formula}i∈I.{a mathematical formula}Γn with {a mathematical formula}n=m+1 is built according to the following rules:Each
      </list>
      <paragraph>
       {a mathematical formula}Γn has a set of witnesses in a subset of V by construction. We have to show that each {a mathematical formula}Γn is k-consistent. We prove this by induction on n.
      </paragraph>
      <list>
       <list-item label="•">
        Base Case ({a mathematical formula}n=0).From the definition of {a mathematical formula}Γ0 we can immediately see that {a mathematical formula}cl(Γ0)⊢i:ϕ if and only if {a mathematical formula}Γ⊢i:ϕ, for all formulas {a mathematical formula}i:ϕ. Therefore the k-consistency of {a mathematical formula}Γ0 follows immediately from the k-consistency of Γ.
       </list-item>
       <list-item label="•">
        Inductive step.Let us assume that {a mathematical formula}Γn−1 is k-consistent. We have to prove that {a mathematical formula}Γn is k-consistent as well. If {a mathematical formula}Γn=Γn−1, then the theorem is trivially true. Let us examine the case {a mathematical formula}Γn≠Γn−1. In this case, the definition of {a mathematical formula}Γn depends upon whether the formula {a mathematical formula}in:ϕn in the enumeration is complete or not. We assume, by contradiction, that {a mathematical formula}Γn is not k-consistent and we split the proof in two different cases depending on whether {a mathematical formula}in:ϕn is a complete formula or not.
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Lemma 4">
      For all{a mathematical formula}n≥0, consider the closure of{a mathematical formula}Γnw.r.t. the set of variables{a mathematical formula}v→that occur in{a mathematical formula}ϕn+1(x)such that{a mathematical formula}Γn⊢BRin+1:∃y.y=z→.{a mathematical formula}Γnis such that if{a mathematical formula}z∉C, then{a mathematical formula}Γn⊢BRi:∃y.z→=yif and only if{a mathematical formula}Γ⊢BRi:∃y.z→=y.
     </paragraph>
     <paragraph label="Proof">
      The proof is by induction on n and is similar to the one for Lemma 3. □
     </paragraph>
     <paragraph>
      The third step in our proof is the construction of saturated sets of formulas that will determine the local models m that belong to the canonical model.
     </paragraph>
     <paragraph label="Definition 18">
      k-saturatedGiven a set of formulas Γ we say that Γ is k-saturated if for all formulas {a mathematical formula}k:ϕ in {a mathematical formula}{Lk} at least one between {a mathematical formula}k:ϕ and {a mathematical formula}k:¬ϕ belongs to Γ. Given a set of set of formulas Γ we say that Γ is k-saturated if for all formulas {a mathematical formula}k:ϕ in {a mathematical formula}{Lk} at least one between {a mathematical formula}k:ϕ and {a mathematical formula}k:¬ϕ belongs to each {a mathematical formula}Γk∈Γ in {a mathematical formula}Lk.
     </paragraph>
     <paragraph label="Lemma 5">
      {a mathematical formula}Γ⁎can be extended to a k-saturated set{a mathematical formula}Σ⁎.
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula} be a new enumeration of the formula in the original languages in {a mathematical formula}{Li} extended with the variables in {a mathematical formula}C and the corresponding extended variables (that is, if {a mathematical formula}c∈C we consider here also formulas containing arrow variables of the form {a mathematical formula}c→j and {a mathematical formula}cj→). We define an infinite sequence of sets of sets of formulas {a mathematical formula}Σ0,Σ1,… as follows:
      <list>
       {a mathematical formula}Σ0=Γ⁎;{a mathematical formula}Σn, with {a mathematical formula}n=m+1 is defined as follows:Let
      </list>
      <paragraph>
       {a mathematical formula}Σ⁎ be the upper-bound of the sequence {a mathematical formula}Σ0,Σ1,…. {a mathematical formula}Σ⁎ is k-saturated by construction. □
      </paragraph>
     </paragraph>
     <paragraph label="Lemma 6">
      {a mathematical formula}Σ⁎is k-consistent.
     </paragraph>
     <paragraph label="Proof">
      We prove that for each {a mathematical formula}n≥0, {a mathematical formula}Σn is k-consistent by induction on n.
     </paragraph>
     <list>
      <list-item label="•">
       Base Case ({a mathematical formula}n=0).{a mathematical formula}Σ0 is k-consistent because of the k-consistency of {a mathematical formula}Γ⁎.
      </list-item>
      <list-item label="•">
       Inductive Step.Suppose that {a mathematical formula}Σn−1 is k-consistent, and let us prove that {a mathematical formula}Σn is k-consistent too. If {a mathematical formula}Σn=Σn−1, then the proof is done. As usual, we split the proof in two parts, depending on whether the n-th formula {a mathematical formula}in:ϕn in the enumeration is complete or not.
      </list-item>
     </list>
     <paragraph>
      The final step in the proof is the definition of the canonical model, and the proof that this canonical model is a {a mathematical formula}BR-model.
     </paragraph>
     <paragraph label="Definition 19">
      Canonical modelThe canonical model{a mathematical formula}Mc=〈{Sic},{rijc}〉 is defined as follows. Domains:Let {a mathematical formula}C be the set of existential witnesses introduced in the construction of {a mathematical formula}Γ⁎. Let {a mathematical formula}Ci→ be the set of the additional arrow variables {a mathematical formula}c→ such that {a mathematical formula}∃x.x=c→ belongs to the intersection {a mathematical formula}⋂Σi⁎ of all {a mathematical formula}Σi in {a mathematical formula}Σi⁎. For two variables {a mathematical formula}c1,c2∈C∪Ci→ we define: {a mathematical formula}c1∼ic2 if and only if {a mathematical formula}c1=c2∈⋂Σi⁎. Since {a mathematical formula}Σ⁎ is saturated w.r.t. complete formulas, we have that each {a mathematical formula}∼i is an equivalence relation on {a mathematical formula}C∪Ci→. For each {a mathematical formula}c∈C∪Ci→, let{a mathematical formula} be the equivalence class of c. Similarly to the usual proof of completeness for first-order logic, we propose to construct a model {a mathematical formula}Mc that associates to each language {a mathematical formula}Li the domain {a mathematical formula}domic of all the equivalence classes {a mathematical formula}[c]i. Formally,{a mathematical formula}Local models:For each {a mathematical formula}i∈I each element {a mathematical formula}Σ∈Σi⁎ is saturated. That is, for each i-formula with arrow variables in {a mathematical formula}C→, at least one between ϕ and ¬ϕ is in Σ. In the general case Σ may be inconsistent (this happens when both ϕ and ¬ϕ belong to Σ), but if this is not the case, then Σ automatically determines a local interpretation of {a mathematical formula}Li over {a mathematical formula}domic. Therefore we define {a mathematical formula}Sic={Σ∈Σi⁎|Σ is i-consistent}.Domain relations:For each pair {a mathematical formula}i≠j∈I, the domain relation {a mathematical formula}rijc⊆domic×domcj is defined as{a mathematical formula}
     </paragraph>
     <paragraph>
      Let us prove that {a mathematical formula}Mc is a model which satisfies the bridge rules {a mathematical formula}BR.
     </paragraph>
     <paragraph label="Lemma 7">
      {a mathematical formula}Mcis a{a mathematical formula}BR-model.
     </paragraph>
     <paragraph label="Proof">
      We have to prove that {a mathematical formula}Mc is not empty, that is, that at least one of the {a mathematical formula}Sic is not empty, and that is satisfies the bridge rules {a mathematical formula}BR. Not emptiness:Since {a mathematical formula}Σ⁎ is k-consistent there is an element {a mathematical formula}Σ∈Σk⁎ which is consistent. Therefore {a mathematical formula}Skc is not empty.Satisfiability of BR:We consider the simple case of {a mathematical formula}i:ϕ(x)→j:ψ(xi→). The proof for more complex interpretation constraints is analogous.Suppose that {a mathematical formula}Mc⊨i:ϕ(x)[a] for an assignment a with {a mathematical formula}ai(x)=[c]. This implies that {a mathematical formula}ϕ(c)∈⋂Σi⁎. Because of the interpretation constraint we have that {a mathematical formula}ψ(ci→)∈⋂Σ⁎j and also {a mathematical formula}∃x.x=ci→∈Σj⁎. This means that a can be extended with {a mathematical formula}aj(xi→)=[ci→] and {a mathematical formula}Mc⊨ϕ(xi→)[a′].  □
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Mc be the canonical model built for {a mathematical formula}(Γ,Σ),i:¬ϕ and let a be an assignment which assigns all variables x to {a mathematical formula}[x]. It is easy to see that {a mathematical formula}M⊨Γ[a], and {a mathematical formula}M⊨e(Σ)[a], but {a mathematical formula}M⊭i:⋀i:σ∈Σσ⊃ϕ[a]. This concludes the completeness proof.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>