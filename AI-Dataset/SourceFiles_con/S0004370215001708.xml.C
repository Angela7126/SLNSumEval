<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Certain answers as objects and knowledge.
   </title>
   <abstract>
    The standard way of answering queries over incomplete databases is to compute certain answers, defined as the intersection of query answers on all complete databases that the incomplete database represents. But is this universally accepted definition correct? We argue that this “one-size-fits-all” definition can often lead to counterintuitive or just plain wrong results, and propose an alternative framework for defining certain answers. The idea of the framework is to move away from the standard, in the database literature, assumption that query results be given in the form of a database object, and to allow instead two alternative representations of answers: as objects defining all other answers, or as knowledge we can deduce with certainty about all such answers. We show that the latter is often easier to achieve than the former, that in general certain answers need not be defined as intersection, and may well contain missing values in them. We also show that with a proper choice of semantics, we can often reduce computing certain answers – as either objects or knowledge – to standard query evaluation. We describe the framework in the most general way, applicable to a variety of data models, and test it on three concrete relational semantics of incompleteness: open, closed, and weak closed world.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Handling incomplete information is one of the oldest topics in data management research. It has been tackled both from the database perspective, resulting in classical notions of the semantics and complexity of query evaluation [1], [2], and from the AI perspective, providing an alternative view of the problem, see, e.g., [3], [4]. With the shifting focus in database applications, owing to the ever increasing amounts of data as well as data heterogeneity, the problem of incomplete information is becoming much more pronounced. It appears in many important application areas, particularly those where techniques from both the data management community and the knowledge representation community have been heavily used. These include data integration [5], data exchange [6], ontology-based data access [7], [8], inconsistent databases [9], probabilistic data [10], and data quality [11]. Here we treat the notion of “incompleteness” rather broadly: it means that data at our disposal does not provide a complete description, but rather suggests a number – perhaps infinite – of possible worlds. Most of the development here will need just this intuition, but in concrete examples we shall use a common scenario of relational databases with missing (null) values [2], [3].
     </paragraph>
     <paragraph>
      The central problem in all applications of incomplete databases is query answering. In the presence of incompleteness, one normally looks for certain answers: those that do not depend on the interpretation of unknown data. The concept was first mentioned in [12] and formally defined 35 years ago in [13] as follows. Assume that the semantics {a mathematical formula}〚D〛 of an incomplete database D is given as a set of complete databases, or possible worlds, {a mathematical formula}D′. These are databases which the incomplete D can represent. Then the certain answer to Q on D is defined as{a mathematical formula} Since database queries produce collections (sets, multisets, etc.), it makes sense to talk about their intersection. This definition has been universally applied to all the semantics of incompleteness, and in all the scenarios such as those listed above. The intuition is that this gives us the set of tuples independent of the interpretation of the data that was not completely specified.
     </paragraph>
     <paragraph>
      If D is a relational, or an XML, or a graph database, {a mathematical formula}〚D〛 is usually obtained by replacing nulls (missing values) with real values, and perhaps adding extra information, such as tuples that were not in the database. In other applications, the definition of {a mathematical formula}〚D〛 varies, but the notion of certain answers does not. We now give a few examples. Data integration.Here D is a source database (in fact it may contain multiple sources) and we need to answer queries over an integrated global schema database. The integration process is guided by a schema mapping M relating the schema of the source with that of the global schema over which queries must be answered. The process is virtual: the integrated database is not built, as M rarely makes it unique. Instead, D and M together provide an incomplete description of the integrated database, i.e.,{a mathematical formula} If a query Q is posed against the global schema database, and we have access to the source D, query answers are typically defined as certain answers, i.e., {a mathematical formula}⋂{Q(D′)|D′∈〚D〛M}, see [14], [5].Data exchange.This scenario is similar to the previous one: we have a schema mapping M between two schemas (usually called source and target schemas in this context), and still want to compute certain answers defined just as above. The difference is that this time the target schema database is materialized, and certain answers must be found based on a specific instance containing data exchanged between the source and the target, see [6], [15].Consistent query answering.Assume we have a database D and a set Σ of integrity constraints over it, such as keys, foreign keys, etc, that D is supposed to satisfy. An inconsistent database fails to satisfy Σ, so one looks for its repairs {a mathematical formula}D′; those are smallest changes that restore consistency (these can be defined in a variety of ways [9]). Then {a mathematical formula}〚D〛Σ consists of all such repairs, and for a given query Q one looks for consistent query answers defined as {a mathematical formula}⋂{Q(D′)|D′∈〚D〛Σ}. These are query answers that are true in all the repairs that restore consistency.Ontology based query answering.An ontology Θ provides additional information about an incomplete database. Together, a database D and an ontology Θ define a set {a mathematical formula}〚D〛Θ of possible worlds that are completions of the database D that make it satisfy all the ontology constraints. Ontology-based query answering – a very active research theme as of late – boils down to taking a query Q and finding certain answers to it over {a mathematical formula}〚D〛Θ, see [7], [8], [16].
     </paragraph>
     <paragraph>
      Thus, in all these applications, spanning a large spectrum of data management and knowledge representation tasks, certain answers are the standard way of defining answers to queries. While the exact semantics of possible worlds changes, the definition of certain answers stays intact.
     </paragraph>
     <paragraph>
      The question that we address here is the following: Is this standard “one-size-fits-all” definition really the right one to use for all the semantics, and all the applications? The answer, as we shall argue, is negative: the standard intersection semantics leads to many problems, and crucially to producing meaningless query answers.
     </paragraph>
     <paragraph>
      To argue that this is the case, and to explain basic ideas behind the approach we present, note that in the database field, one tends to operate with objects (i.e., relations, XML documents, graph databases, etc.). In particular, queries take objects and return objects. Thus, the idea behind certain answers is to find an object A representing the set of objects{a mathematical formula}Q(〚D〛)={Q(D′)|D′∈〚D〛}. Such an object A must contain information common to all the objects in {a mathematical formula}Q(〚D〛): that is, it must be no more informative than any of the objects in {a mathematical formula}Q(〚D〛). The definition of {a mathematical formula}cert∩ uses the intersection operator as a means of extracting such common information.
     </paragraph>
     <paragraph>
      Now take a simple example: we have a relation {a mathematical formula}R={(1,2),(3,⊥)} in a database D, where ⊥ represents a null, or a missing value. The query Q returns R itself. Then {a mathematical formula}cert∩(Q,D)={(1,2)} under every reasonable semantics of incompleteness. But is it less informative than all of {a mathematical formula}Q(D′) for {a mathematical formula}D′∈〚D〛? The answer depends on the semantics. Under the common open-world semantics, the answer is yes: in fact {a mathematical formula}(1,2) is precisely the greatest lower bound of {a mathematical formula}Q(〚D〛) under the ordering whose meaning is “being less informative”. But under the equally common closed-world semantics, the answer is no. Even worse, {a mathematical formula}(1,2) is not less informative than any of the answers {a mathematical formula}Q(D′) for {a mathematical formula}D′∈〚D〛 which are of the form {a mathematical formula}{(1,2),(3,n)} for different values n. Indeed, under the closed world semantics, the answer {a mathematical formula}{(1,2)} contains additional information that no tuple except {a mathematical formula}(1,2) is present. Thus, returning just {a mathematical formula}(1,2) in this case makes no sense at all.
     </paragraph>
     <paragraph>
      The problem with returning the single tuple {a mathematical formula}(1,2) as the certain answer becomes even more pronounced if we follow the approach, pioneered by [3], that views databases as logical theories and query answering as logical implication. The fact {a mathematical formula}R(1,2) is certainly implied by the database. But is it the only fact that is implied? Of course not: under the open-world semantics, we can deduce {a mathematical formula}∃xR(1,2)∧R(3,x) with certainty, adding the fact that there is a tuple whose first component is 3. And under the closed world semantics, we know for certain even more, for instance {a mathematical formula}∃x∀y(y=1∨y=2∨y=3∨y=x), since we cannot expand the domain of the database.
     </paragraph>
     <paragraph>
      Even from this simple example, we learn a few lessons:
     </paragraph>
     <list>
      <list-item label="•">
       certain answers can be presented as both objects and logical formulae;
      </list-item>
      <list-item label="•">
       they depend on both logical languages and semantics used; and
      </list-item>
      <list-item label="•">
       taking intersection and removing missing values from the answers is not always the right way to compute them.
      </list-item>
     </list>
     <paragraph>
      Note that viewing answers as formulae brings us closer to knowledge bases. The difference though is that while in databases we start with objects and produce objects, and in querying knowledge bases we start with logical theories and produce logical theories, here we may also combine the two, starting with an object, and returning a formula, or a theory, as the result.
     </paragraph>
     <paragraph>
      The goal of this paper is to develop an alternative framework for handling certain answers to queries. For that, we combine the approaches to viewing databases as objects [2] and as logical theories [3], rather than treat them separately. In addition, we bring in ideas from another approach, based on ordering incomplete databases in terms of their informativeness [17], [18]. Combining these three approaches, taking, essentially, only what is really needed from each one of them, allows us to define certain answers in a new way that avoids some of the problems exhibited by the standard accepted definition.
     </paragraph>
     <paragraph>
      Specifically, the key elements of our framework are as follows.
     </paragraph>
     <list>
      <list-item label="•">
       Certain answers can be viewed as either objects or theories, depending on the semantics, and the logical formalism used. The former is in line with the standard database approach, while the latter defines certain knowledge about query answers over incomplete databases.
      </list-item>
      <list-item label="•">
       Both ways are based on extracting certain information from a set of objects. Each way defines certainty as a greatest lower bound: either of a set of objects, or the theory of that set of objects, with the ordering meaning “being more informative”.
      </list-item>
     </list>
     <paragraph>
      We concentrate here on the general problem of answering queries over incomplete databases, rather than specific applications, such as those listed earlier. In fact, in several of those applications the query answering problem is reduced to running a query on a specific incomplete database. Our main technical contributions are as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       Query answering is then based on the notion of representation systems: these are a natural relaxation of a rather restrictive concept of what database people call strong representation systems, and yet more disciplined than what is called weak representation systems (which define certain information exclusively by means of intersection). Representation systems let one define important sets of objects by logical formulae, in the spirit of [3].
      </list-item>
      <list-item label="2.">
       Our key result is that under the right choice of the semantics for both query inputs and query answers, certain answers – as both objects and knowledge – can be found by straightforward database query evaluation. Thus, with the correct choice of semantics and representation system, we can use existing query evaluation techniques for obtaining correct answers in the presence of incomplete information. Even when such an evaluation is expensive, the approach suggests how to look for approximating query answers.The right choice of the semantics relies on the notion of informativeness and simply says that one cannot get less informative answers on more informative inputs (indeed, if we have an input I to a query Q, and then we gain extra information about I and obtain a more informative instance {a mathematical formula}I′, at the very least we could just go back to I and evaluate Q on it; hence, gaining information about the input can only make query output more informative). This very basic principle however has been ignored by most of the research on incompleteness in databases; we shall explain later why this happened.
      </list-item>
      <list-item label="3.">
       We also show that it is easier to find certain answers as knowledge as opposed to certain answers as objects: sometimes the former exists and the latter does not. Also, even when both exist, we need certain answers as knowledge to prove that certain answers as objects are correct. Thus, representing certain knowledge about query answers is not a mere convenience, it may well be a necessity – even if not seen by the end user, it is necessary to provide correctness guarantees.
      </list-item>
     </list>
     <paragraph>
      Most of the results in the paper are shown in an abstract setting, for two reasons. First, it makes them applicable to other data models, beyond relational databases (e.g., XML and graph data). Second, it helps us see the essential conditions that need to be imposed on queries and the semantics of incompleteness, without being too “clouded” by details of a particular data model. At the same time we use three common relational semantics – open world, closed world, and weak closed world – to translate general results into concrete examples, to test the approach.
     </paragraph>
     <paragraph>
      Organization. After presenting basic facts about relational incompleteness in Section 2, we introduce the abstract setting and notions of certainty as objects and knowledge in Section 4. Section 5 defines representation systems and connects knowledge certainty with greatest lower bounds. Section 6 defines certain answers for queries, and Section 7 shows how to compute them. Summary and future work are in Section 8.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background: relational incompleteness
     </section-title>
     <paragraph>
      Incomplete databases  These have two types of values: constants (e.g., {a mathematical formula}1,2,…) and nulls, representing unknown values. We thus assume countably infinite sets of constants, denoted by {a mathematical formula}Const, and of nulls, denoted by {a mathematical formula}Null. Nulls themselves are denoted by ⊥, sometimes with sub- or superscripts.
     </paragraph>
     <paragraph>
      A relational vocabulary (often called schema in database literature) is a set of relation names with associated arities. An incomplete relational instance D assigns to each k-ary relation symbol R from the vocabulary a k-ary relation {a mathematical formula}RD over {a mathematical formula}Const∪Null, i.e., a finite subset of {a mathematical formula}(Const∪Null)k. If the instance D is clear from the context, we may write R instead of {a mathematical formula}RD. Sets of constants and nulls that occur in D are denoted by {a mathematical formula}Const(D) and {a mathematical formula}Null(D). The active domain of D is {a mathematical formula}adom(D)=Const(D)∪Null(D). A complete database D has no nulls, i.e., {a mathematical formula}adom(D)⊆Const.
     </paragraph>
     <paragraph>
      Semantics and valuations  A valuation of nulls on an incomplete database D is a map {a mathematical formula}v:Null(D)→Const assigning a constant value to each null. It naturally extends to databases, so we can write {a mathematical formula}v(D) as well. The standard semantics of incompleteness in relational databases are defined in terms of valuations, see [19], [2]. These are the closed world assumption, or cwa semantics:{a mathematical formula} and the open-world assumption, or owa semantics:{a mathematical formula} where {a mathematical formula}D′ is over the same vocabulary as D, and union is taken relation-by-relation. We shall also consider the weakcwa, or wcwa semantics, inspired by [20], given by{a mathematical formula} That is, under cwa, we simply instantiate nulls by constants; under owa, we can also add arbitrary new tuples (the database {a mathematical formula}D′), and under wcwa, we can only add new tuples formed by elements already present (which is expressed by the condition {a mathematical formula}adom(D′)⊆adom(v(D))). For instance, if {a mathematical formula}D0={(⊥,⊥′)}, then {a mathematical formula}〚D〛cwa only has instances {a mathematical formula}{(c,c′)} for {a mathematical formula}c,c′∈Const, while {a mathematical formula}〚D〛wcwa can have in addition instances that add to {a mathematical formula}(c,c′) tuples {a mathematical formula}(c,c),(c′,c′), and {a mathematical formula}(c′,c), and {a mathematical formula}〚D〛owa has all instances containing at least one tuple.
     </paragraph>
     <paragraph>
      If one has a query Q to be evaluated on an incomplete database D, one needs to represent the set{a mathematical formula} of possible answers to Q on complete databases that are represented by D. One possibility is to look for an answer A so that {a mathematical formula}〚A〛=Q(〚D〛), i.e., A denotes exactly the answers to Q over {a mathematical formula}〚D〛. When such an answer A exists for every query Q from a given class of queries, one talks about strong representation systems for that class, under the semantics {a mathematical formula}〚〛, see [19], [2]. Unfortunately, strong representation systems may not exist even for simple queries over standard semantics of incompleteness, e.g., even quantifier-free queries for the closed-world semantics [2].
     </paragraph>
     <paragraph>
      Classical definition of certain answers
     </paragraph>
     <paragraph>
      In an attempt to overcome the problem of non-existence of strong representation systems, [2] proposed a notion of weak representation systems, whose idea, in essence, is that only the certain information in {a mathematical formula}Q(〚D〛) and A should be the same. In the process of defining it formally, they introduced the notion of certain answers, that has since dominated the literature of query answering over incomplete databases.
     </paragraph>
     <paragraph>
      Given an incomplete database D, a semantics of incompleteness {a mathematical formula}〚〛, and a query Q, the standard notion of certain answers under {a mathematical formula}〚〛 is{a mathematical formula} Note that {a mathematical formula}cert∩(Q,D) cannot contain any tuples with nulls.
     </paragraph>
     <paragraph>
      In some cases, these answers are obtained by almost straightforward query evaluation, namely by evaluating {a mathematical formula}Q(D) and then throwing away the tuples with nulls. We shall denote this by {a mathematical formula}QC(D). For instance, if the query Q just returns a relation R, and {a mathematical formula}RD={(1,2),(1,⊥)}, then both {a mathematical formula}QC(D) and {a mathematical formula}cert∩(Q,D) are {a mathematical formula}{(1,2)}. In general of course the two need not coincide, as finding certain answers may be computationally very expensive: for instance, undecidable under owa, or coNP-hard under cwa for first-order queries [1].
     </paragraph>
     <paragraph>
      Logics  Most database query languages are based on first-order predicate logic, or FO. Its formulae, over a relational vocabulary, are built from relational atoms {a mathematical formula}R(x¯), where R is a vocabulary symbol, and equational atoms {a mathematical formula}x=y, by closing them under the Boolean connectives {a mathematical formula}∧,∨,¬ and quantifiers ∃ and ∀. Free variables of a formula φ are defined in the standard way. If {a mathematical formula}x¯ is the tuple of free variables of φ, we may indicate this explicitly by writing {a mathematical formula}φ(x¯). For FO formulae in this paper we use the standard semantics, even when structures mix elements from {a mathematical formula}Const and {a mathematical formula}Null. Recall that these sets are disjoint, and hence every equality between a constant and a null will evaluate to false. Equalities between nulls evaluate to true if nulls are the same. Using this standard FO semantics (i.e., not looking at the semantic distinction between constants and nulls) is common in databases and is often referred to as naïve evaluation. That is, a query is evaluated by the standard query evaluation engine, despite the fact that some entries are unknown.
     </paragraph>
     <paragraph>
      We shall deal with several fragments of FO, of importance both in logic and in databases.
     </paragraph>
     <list>
      <list-item label="•">
       Conjunctive queries are the {a mathematical formula}∃,∧-fragment of FO, i.e., it has no disjunction, negation, and universal quantification. Such formulae are of the form {a mathematical formula}φ(x¯)=∃y¯R1(u¯1)∧…∧Rk(u¯k), where the {a mathematical formula}Ris are relation symbols from the vocabulary, and each tuple {a mathematical formula}u¯i, whose length equals the arity of {a mathematical formula}Ri, contains variables from {a mathematical formula}x¯, {a mathematical formula}y¯. One can also add explicit equalities between variables in conjunctive queries (they do not add expressiveness of course).
      </list-item>
      <list-item label="•">
       The class of existential positive formulae, denoted by {a mathematical formula}∃Pos, is the {a mathematical formula}∧,∨,∃-fragment of FO (i.e., it disallows negation and universal quantification). In terms of their expressiveness, {a mathematical formula}∃Pos formulae correspond precisely to unions of conjunctive queries, i.e., disjunctions of conjunctive queries, although {a mathematical formula}∃Pos formulae can be more succinct.
      </list-item>
      <list-item label="•">
       The class of positive formulae, denoted by {a mathematical formula}Pos, is the {a mathematical formula}∧,∨,∃,∀-fragment of FO (i.e., it disallows negation).
      </list-item>
      <list-item label="•">
       Formulae true and false belong to all these classes.
      </list-item>
     </list>
     <paragraph>
      It is known that {a mathematical formula}cert∩(Q,D)=QC(D) for {a mathematical formula}∃Pos queries under owa[2], and for {a mathematical formula}Pos queries under wcwa[21]. There is a fragment for which the equality holds under cwa as well, and it will be given later in Section 5.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Problematic certain answers
     </section-title>
     <paragraph>
      The standard treatment of incompleteness in commercial DBMSs (in particular SQL's treatment of nulls) has been heavily criticized in the past [22], [23], [24], but the theoretical approaches have so far been spared. The goal of this section, which serves as additional motivation for our re-thinking of the standard approaches to certain answers, is to re-examine some of the most basic theoretical notions related to handling incompleteness in databases, and to demonstrate their severe shortcomings.
     </paragraph>
     <paragraph>
      Semantics of query answers  Let us look at the seemingly uncontroversial definition saying that if we are lucky enough to get A satisfying {a mathematical formula}〚A〛=Q(〚D〛), then A should be viewed as the answer to Q on D. At the first glance it looks like a reasonable condition, but nonetheless there is one questionable assumption built into it. Note that this definition requires that both the input database D, and the answer A, be interpreted under the same semantics {a mathematical formula}〚〛. However, a priori, there is no reason for it. Why, for instance, should the answer to a query be interpreted under cwa if this is the semantics of the input? And what if we have data of different formats, e.g., XML-to-relational or relational-to-XML queries?
     </paragraph>
     <paragraph>
      The importance of intersection, and certainty of certain answers  The idea of using certain answers given as intersections of all query answers initially came from weak representation systems of [2]. If {a mathematical formula}〚A〛=Q(〚D〛) is too strong a condition, one tries to replace it by {a mathematical formula}〚A〛∼Q(〚D〛), where ∼ is some equivalence relation. In the definition of [2], the relation is defined as follows. Given two sets of database instances, {a mathematical formula}I1 and {a mathematical formula}I2, and a query language {a mathematical formula}L, we let {a mathematical formula}I1∼LI2 if {a mathematical formula}⋂{q(D′)|D′∈I1}=⋂{q(D′)|D′∈I2} for each query q in {a mathematical formula}L.
     </paragraph>
     <paragraph>
      This equivalence relation looks quite ad hoc. It was defined that way to ensure compositionality of queries, and what really survived from it in applications is the idea of intersection for certain answers. But that is problematic for two reasons. First, there are models other than relational. What can one do, for instance, for XML queries returning documents? (A side remark: much of the work on incompleteness in XML has been restricted to XML-to-relational queries, for this very reason [25], [26], [27].) But even more importantly, we may lose information by taking intersection and removing tuples from the answer. Indeed, taking tuples away amounts to removing data, not information. In fact, the process can actually add information: for instance, under cwa, by removing a tuple we gain information that it is not in the answer, as discussed in the introduction. Hence, certain answers defined by the intersection operator cannot be called certain in all scenarios.
     </paragraph>
     <paragraph>
      Representation of query answers  We are used to queries returning database objects – tables, XML documents, graphs. But are these sufficiently expressive to describe answers on incomplete databases? Specifically, are these sufficiently expressive to represent sets {a mathematical formula}Q(〚D〛)? Such sets may well be infinite, and describing them may require a more complex representation mechanism than simple database objects. Some attempts have been made, for instance with conditional tables [2] which “look” like relations and give a strong representation system. There is a price to pay: they correspond to a rather bizarre fragment of FO, and have intractable complexity even for simple queries [1]. But is it really necessary to have representations of answers that look like database relations, while they are not?
     </paragraph>
     <paragraph>
      The approach we now present will try to address these lines of criticism, and will provide a new and more disciplined version of certain answers.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Objects, knowledge, and information ordering
     </section-title>
     <paragraph>
      The key idea, as explained in the introduction, is to decouple objects and their descriptions in terms of some logical formalisms, i.e., to decouple objects and knowledge about them. We want to do this at the highest level of abstraction, so that the framework would not be limited to just relational databases, but instead would be applicable across multiple data models. For this, we use a very minimalistic setting inspired by abstract model theory [28] or information systems [29], with some specific features tailored to handle incompleteness, as also used in [30], [21]. A word on notation: in our abstract setting, we shall refer to objects by letters {a mathematical formula}x,y, etc., while dealing with relational databases (which serve as the main example here) we shall use D, {a mathematical formula}D′, etc.
     </paragraph>
     <paragraph>
      The key elements of this minimalistic settings are:
     </paragraph>
     <list>
      <list-item label="•">
       the notion of a database pre-domain, capturing the basic intuition that database objects can be complete or incomplete, and the semantics of an incomplete object is a set of possible complete worlds for it;
      </list-item>
      <list-item label="•">
       the notion of an information ordering capturing the intuition that some objects are more informative than others; and
      </list-item>
      <list-item label="•">
       the notion of a pre-representation system that introduces formulae that can be satisfied by objects.
      </list-item>
     </list>
     <paragraph>
      We now formalize these as follows.
     </paragraph>
     <paragraph label="Definition 1">
      Pre-domainA database pre-domain is a triple {a mathematical formula}D∘=〈D,C,〚〛〉, where {a mathematical formula}D is a set, {a mathematical formula}C⊆D, and {a mathematical formula}〚〛 is a function from {a mathematical formula}D to {a mathematical formula}2C, such that {a mathematical formula}c∈〚c〛 for every {a mathematical formula}c∈C and {a mathematical formula}〚c〛⊆〚x〛 whenever {a mathematical formula}c∈〚x〛.
     </paragraph>
     <paragraph>
      The intuition is as follows:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}D is a set of database objects (e.g., relational databases over the same schema);
      </list-item>
      <list-item label="•">
       {a mathematical formula}C is the set of complete objects (e.g., databases without nulls);
      </list-item>
      <list-item label="•">
       {a mathematical formula}〚〛 is the semantic function: {a mathematical formula}〚x〛⊆C is the semantics of an incomplete database x, i.e., the set of all complete databases that x can represent.
      </list-item>
     </list>
     <paragraph>
      The last two conditions hold in the standard semantics of incompleteness: they say that a complete object should denote at least itself, and that we have less uncertainty about an object c in the semantics of x than about x itself.
     </paragraph>
     <paragraph label="Definition 2">
      Information orderingGiven a semantics {a mathematical formula}〚〛 of incompleteness, an information ordering associated with it is given by{a mathematical formula}
     </paragraph>
     <paragraph>
      The intuition is that y is at least as informative as x. Indeed, the more possible objects we have in the semantics of an incomplete object, the less we know about it. In the extreme case, when we know nothing about an object, its semantics is everything, i.e., it can denote any other object. Note that ⪯ is a preorder, i.e., it is reflexive and transitive, but both {a mathematical formula}x⪯y and {a mathematical formula}y⪯x may be true for equivalent objects x and y, i.e., if {a mathematical formula}〚x〛=〚y〛.
     </paragraph>
     <paragraph>
      Note that the last condition in the definition of pre-domain simply says that if {a mathematical formula}c∈〚x〛, then {a mathematical formula}x⪯c, i.e., an incomplete object is less informative than the objects it represents.
     </paragraph>
     <paragraph label="Definition 3">
      Pre-representation systemA pre-representation system is a triple {a mathematical formula}RS∘=〈D∘,F,⊨〉, where {a mathematical formula}D∘=〈D,C,〚〛〉 is a pre-domain, {a mathematical formula}F is a set, and ⊨ is a relation between {a mathematical formula}D and {a mathematical formula}F (written as {a mathematical formula}x⊨φ for {a mathematical formula}x∈D and {a mathematical formula}φ∈F) such that {a mathematical formula}x⪯y and {a mathematical formula}x⊨φ imply {a mathematical formula}y⊨φ.
     </paragraph>
     <paragraph>
      The intuition is that {a mathematical formula}F is a set of formulae that express knowledge we possess about objects in {a mathematical formula}D, and ⊨ is the satisfaction relation between objects in {a mathematical formula}D and formulae in {a mathematical formula}F. The last condition says that if we know something about an object, we also know it about a more informative object.
     </paragraph>
     <paragraph>
      We shall write {a mathematical formula}Th(x) for the theory of x, that is, {a mathematical formula}{φ|x⊨φ} and {a mathematical formula}Mod(φ) for models of φ, that is, {a mathematical formula}{x|x⊨φ}. These are extended to sets in the usual way:{a mathematical formula}
     </paragraph>
     <paragraph>
      It is well known that {a mathematical formula}Mod and {a mathematical formula}Th define a Galois connection between {a mathematical formula}D and {a mathematical formula}F. That is, both {a mathematical formula}Mod and {a mathematical formula}Th are anti-monotone, {a mathematical formula}X⊆Mod(Th(X)) and {a mathematical formula}Φ⊆Th(Mod(Φ)) for all X and Φ. In particular, this implies that {a mathematical formula}Mod(Th(⋅)) is a closure operator.
     </paragraph>
     <section label="4.1">
      <section-title>
       Certain information
      </section-title>
      <paragraph>
       Computing certain answers boils down to finding certain information contained in a set of objects; in the case of query answering, in {a mathematical formula}Q(〚D〛)={Q(D′)|D′∈〚D〛}. Thus, we need to know how to define certain information contained in a set of objects {a mathematical formula}X⊆D. The usual database approach is to represent this information as another object, but of course we argue that it can be viewed as both object and knowledge. We now present two ways of extracting certain information from {a mathematical formula}X⊆D. Certain information as objectIf we want to represent what we know about X with certainty by an object y, this object must be less informative than any object {a mathematical formula}x∈X (as it reflects knowledge contained in all other objects in X as well). If we have two such objects y and {a mathematical formula}y′, and {a mathematical formula}y′⪯y, then of course we prefer y as giving us more information.Thus, the object that we seek must be less informative than all objects in X, and at the same time the most informative among such objects. This is precisely the greatest lower bound of X, with respect to ⪯ (or ⋀X, using the standard order-theoretic notation). If it exists, we denote it by {a mathematical formula}□OX. The subscript {a mathematical formula}O is for ‘object’.Certain information as knowledgeWe want to describe X by a single formula summarizing what we know about it with certainty. If {a mathematical formula}X=Mod(φ), then φ is such a formula, but generally, X need not be of the form {a mathematical formula}Mod(φ).So we go for the next best thing: we want a formula that is equivalent to the theory of X. Of course two sets of formulae are equivalent when they have the same models, so a formula equivalent to the theory of X is a formula φ such that {a mathematical formula}Mod(φ)=Mod(Th(X)). We denote such a formula by {a mathematical formula}□KX. The subscript {a mathematical formula}K is for ‘knowledge’.Note that {a mathematical formula}□KX is a formula in {a mathematical formula}Th(X): indeed, since {a mathematical formula}Mod(Th(⋅)) is a closure operator, {a mathematical formula}X⊆Mod(Th(X))=Mod(□KX). Thus, certain information contained in X is described
      </paragraph>
      <list>
       <list-item label="•">
        at the object level as {a mathematical formula}□OX=⋀X; and
       </list-item>
       <list-item label="•">
        at the knowledge level as a formula {a mathematical formula}□KX so that {a mathematical formula}Mod(□KX)=Mod(Th(X)).
       </list-item>
      </list>
      <paragraph>
       We now make a couple of observations about these concepts. First, neither {a mathematical formula}□OX nor {a mathematical formula}□KX need exist in general (in fact it is easy to come up with the examples of preorders without greatest lower bounds).
      </paragraph>
      <paragraph>
       Second, even if they exist, they are not unique. This is not an issue, however, as they are equivalent. Since ⪯ is a preorder, the greatest lower bound is, technically speaking, a set of objects, but every two such objects {a mathematical formula}y,y′ are equivalent: {a mathematical formula}y⪯y′ and {a mathematical formula}y′⪯y, and thus {a mathematical formula}〚y〛=〚y′〛. If we have multiple formulae φ for which {a mathematical formula}Mod(φ)=Mod(Th(X)), then every two such formulae {a mathematical formula}φ,φ′ are equivalent: {a mathematical formula}Mod(φ)=Mod(φ′). So we shall write {a mathematical formula}y=□OX or {a mathematical formula}φ=□KX, meaning y or φ is one of the equivalent objects or formulae.
      </paragraph>
      <paragraph>
       Also note that a much simplified version of the framework was used in [30] and in [31] for XML documents. Crucially, the framework lacked the notion of representation systems, as there were no formulae defined on database domains. A rudimentary case of {a mathematical formula}□KX was used there, by identifying what we view as the set {a mathematical formula}F of formulae here with {a mathematical formula}D itself. If {a mathematical formula}x⊨y means {a mathematical formula}y⪯x, then analog of Theorem 1 below for that simple case is a consequence of results in [30]. An attempt to give conditions for query evaluation to compute certain answers was made there as well, but without representation systems it required some rather ad hoc conditions on complete objects and was not satisfactory.
      </paragraph>
      <paragraph label="Example 1">
       Consider the example from the introduction, of a database D containing {a mathematical formula}(1,2) and {a mathematical formula}(3,⊥) in a relation R. If {a mathematical formula}X=〚D〛owa, then {a mathematical formula}□OX is just D itself, as expected. If {a mathematical formula}F=∃Pos, then {a mathematical formula}□KX=∃zR(1,2)∧R(3,z). If {a mathematical formula}F is the set of ground facts and their conjunctions, then {a mathematical formula}□KX=R(1,2).If {a mathematical formula}X=〚D〛cwa, then ⋀X is still D, but we need a more complex class to describe {a mathematical formula}□KX; in fact the two formulae above violate the definition of {a mathematical formula}□KX in this case. We shall continue with this example later in Example 2 and use the machinery developed in the paper to formally prove the results stated here. We shall also present a formula {a mathematical formula}□KX under cwa that comes from a more expressive subclass of FO.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Representation systems
     </section-title>
     <paragraph>
      So far we imposed no conditions on pre-domains and pre-representation systems. We now define representation systems, which are pre-representation systems with two conditions imposed. These conditions, that hold in the standard semantics of incompleteness, say essentially that the sets of objects and formulae are not too “thin”: there are enough complete objects, and there are formulae defining some fairly basic sets of objects.
     </paragraph>
     <paragraph>
      There are enough objects  In real life, we have (potentially) infinite domains of database elements. If we have a database with the tuple {a mathematical formula}(1,2), we should expect to have a database with the tuple {a mathematical formula}(2,3), or {a mathematical formula}(3,4), and so on. The condition that we introduce now captures this intuition in our abstract model.
     </paragraph>
     <paragraph>
      To see how this can be done, consider an arbitrary relational database D, and a renaming f of elements of its active domain, i.e., a one-to-one mapping {a mathematical formula}f:adom(D)→U for some set U. If {a mathematical formula}f(D) is the database obtained by replacing each element {a mathematical formula}a∈adom(D) with {a mathematical formula}f(a), then databases D and {a mathematical formula}f(D) are isomorphic: a tuple {a mathematical formula}t¯ is in a relation R of D iff {a mathematical formula}f(t¯) is in the same relation R in {a mathematical formula}D′. Note that such a map does not distinguish nulls and constants. Two isomorphic databases will agree on logical formulae not mentioning constants. Even if we have a logical formula mentioning constants from a finite set C, databases D and {a mathematical formula}f(D) will agree on it as long as {a mathematical formula}f(a)=a for every {a mathematical formula}a∈C.
     </paragraph>
     <paragraph>
      The intuition behind the ‘enough objects’ condition is that for every such renaming f of elements of the active domain, {a mathematical formula}f(D) is a legitimate database, and D and {a mathematical formula}f(D) agree on formulae that only mention constants preserved by f.
     </paragraph>
     <paragraph>
      To formulate this at the abstract level of database pre-domains, consider the relation {a mathematical formula}D≈CD′ saying that there is a one-to-one mapping f preserving C such that {a mathematical formula}D′=f(D). It is easily seen to be an equivalence relation; moreover, if the range of f only includes constants, then {a mathematical formula}f(D) is a complete database that is in {a mathematical formula}〚D〛 for the standard semantics like owa, cwa, wcwa. Finally, if {a mathematical formula}D≈C∪C′D′, then {a mathematical formula}D≈CD′ and {a mathematical formula}D≈C′D′. These conditions are easy to state at the level of database pre-domains.
     </paragraph>
     <paragraph label="Definition 4">
      Database domainA database domain{a mathematical formula}D as a tuple {a mathematical formula}〈D,C,〚〛,Iso〉 where {a mathematical formula}〈D,C,〚〛〉 is a pre-domain, and Iso is a family {a mathematical formula}{≈j}j∈J of equivalence relations on {a mathematical formula}D so that:
     </paragraph>
     <list>
      <list-item label="•">
       the set {a mathematical formula}〚x〛≈j={c∈〚x〛|x≈jc} is nonempty for each {a mathematical formula}x∈D and {a mathematical formula}j∈J;
      </list-item>
      <list-item label="•">
       for every {a mathematical formula}j,j′∈J, there is {a mathematical formula}k∈J so that {a mathematical formula}x≈ky implies both {a mathematical formula}x≈jy and {a mathematical formula}x≈j′y.
      </list-item>
     </list>
     <paragraph>
      Coming back to the relational intuition, the relations {a mathematical formula}≈j are exactly the relations {a mathematical formula}≈C, where C ranges over finite sets of constants. The first condition says that we can replace nulls by constants outside C (since {a mathematical formula}Const−C is infinite); the second one was explained earlier.
     </paragraph>
     <paragraph>
      There are enough formulae  First, we assume that formulae are closed under conjunction, i.e. for {a mathematical formula}φ,ψ∈F we have {a mathematical formula}φ∧ψ∈F with {a mathematical formula}Mod(φ∧ψ)=Mod(φ)∩Mod(ψ). This is just a technical condition so that we could represent a finite set {a mathematical formula}{φ1,…,φn} of formulae by a single formula, namely their conjunction {a mathematical formula}φ1∧…∧φn.
     </paragraph>
     <paragraph>
      The second assumption is that the formulae have something to do with the intended meaning of incomplete information. For this we require that some basic sets of objects be definable by formulae. In our minimalistic model the most basic sets are of the form {a mathematical formula}〚x〛. Thus, we shall require their definability; since {a mathematical formula}〚x〛⊆C, we shall require the existence, for each object x, of a formula {a mathematical formula}δx such that {a mathematical formula}Mod(δx)∩C=〚x〛. We shall see that this is the same as asking that {a mathematical formula}Mod(δx)=↑x, where {a mathematical formula}↑x={y|x⪯y} is the set of objects at least as informative as x. Note that we simply require their existence, although we shall see that for basic relational semantics of incompleteness they will be easy to construct explicitly.
     </paragraph>
     <paragraph>
      All these are summarized in the following definition.
     </paragraph>
     <paragraph label="Definition 5">
      Representation systemsA representation system is a triple {a mathematical formula}RS=〈D,F,⊨〉, where:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}D is a database domain and {a mathematical formula}〈D,F,⊨〉 is a pre-representation system whose formulae are closed under conjunction;
      </list-item>
      <list-item label="•">
       for each {a mathematical formula}x∈D, there is a formula {a mathematical formula}δx∈F with {a mathematical formula}Mod(δx)∩C=〚x〛;
      </list-item>
      <list-item label="•">
       for each {a mathematical formula}φ∈F, there is {a mathematical formula}j∈J so that {a mathematical formula}x⊨φ⇔y⊨φ whenever {a mathematical formula}x≈jy.
      </list-item>
     </list>
     <paragraph>
      The last condition is essentially the analog of the condition that a formula can only refer to finitely many constants, and thus cannot distinguish objects equivalent with respect to {a mathematical formula}≈j for some j.
     </paragraph>
     <section label="5.1">
      <section-title>
       Examples of domains and representation systems
      </section-title>
      <paragraph>
       We now provide examples of representation systems corresponding to relational owa, wcwa, and cwa semantics. We use the notation {a mathematical formula}D(σ) for the set of all relational databases of vocabulary σ over {a mathematical formula}Const∪Null, and {a mathematical formula}C(σ) for the set of all such databases that do not use nulls in {a mathematical formula}Null. The database domains will be of the form {a mathematical formula}D⁎(σ)=〈D(σ),C(σ),〚〛⁎,Iso〉, where ⁎ is one of owa, wcwa, or cwa.
      </paragraph>
      <paragraph>
       The equivalence relations Iso were already explained. They are indexed by finite subsets of {a mathematical formula}Const, and for such a finite set C, we have {a mathematical formula}D≈CD′ iff there is an isomorphism f between D and {a mathematical formula}D′ such that both f and {a mathematical formula}f−1 are identity on C. More precisely, f is a one-to-one mapping from {a mathematical formula}adom(D) to {a mathematical formula}adom(D′) so that {a mathematical formula}f(a)=f−1(a)=a if {a mathematical formula}a∈C, and {a mathematical formula}t¯∈RD iff {a mathematical formula}f(t¯)∈RD′.
      </paragraph>
      <paragraph>
       We write {a mathematical formula}⪯⁎ for the information ordering given by {a mathematical formula}〚〛⁎, i.e., {a mathematical formula}D⪯⁎D′ iff {a mathematical formula}〚D′〛⁎⊆〚D〛⁎. These orderings {a mathematical formula}⪯owa,⪯cwa, and {a mathematical formula}⪯wcwa are known to be expressible in terms of homomorphisms. Given two relational databases D and {a mathematical formula}D′, a homomorphism {a mathematical formula}h:D→D′ is a map from {a mathematical formula}adom(D) to {a mathematical formula}adom(D′) such that {a mathematical formula}h(c)=c for each constant c, and such that for every relation symbol R and tuple {a mathematical formula}t¯∈RD, the tuple {a mathematical formula}h(t¯) is in {a mathematical formula}RD′. The image of the homomorphism is denoted by {a mathematical formula}h(D). A homomorphism is onto if {a mathematical formula}adom(h(D))=adom(D′), and strong onto if {a mathematical formula}D′=h(D).
      </paragraph>
      <paragraph>
       It was shown in [30], [21] that {a mathematical formula}D⪯⁎D′ iff there exists a
      </paragraph>
      <list>
       <list-item label="•">
        homomorphism {a mathematical formula}h:D→D′, for ⁎=owa;
       </list-item>
       <list-item label="•">
        onto homomorphism {a mathematical formula}h:D→D′, for ⁎=wcwa;
       </list-item>
       <list-item label="•">
        strong onto homomorphism {a mathematical formula}h:D→D′, for ⁎=cwa.
       </list-item>
      </list>
      <paragraph>
       In what follows, we describe sets of formulae {a mathematical formula}F and formulae {a mathematical formula}δD for each D. Let {a mathematical formula}PosDiag(D) be the positive diagram of D in the vocabulary including constants for each {a mathematical formula}a∈Const, where with each null {a mathematical formula}⊥i in D we associate a variable {a mathematical formula}xi. For instance, if D contains relation R with tuples {a mathematical formula}(1,2),(2,⊥1),(⊥1,⊥2), then {a mathematical formula}PosDiag(D)=R(1,2)∧R(2,x1)∧R(x1,x2).
      </paragraph>
      <paragraph>
       OWA  The OWA representation system is {a mathematical formula}RSowa(σ)=〈Dowa(σ),∃Pos,⊨〉. For each D with {a mathematical formula}Null(D)={⊥1,…,⊥n}, we have {a mathematical formula}δD=∃x1,…,xnPosDiag(D).
      </paragraph>
      <paragraph>
       WCWA  The WCWA representation system is {a mathematical formula}RSwcwa(σ)=〈Dwcwa(σ),Pos,⊨〉. For each D with {a mathematical formula}Const(D)={a1,…,am} and {a mathematical formula}Null(D)={⊥1,…,⊥n}, the formula {a mathematical formula}δD is{a mathematical formula}
      </paragraph>
      <paragraph>
       CWA  We need to define an extension of the class of positive formulae, introduced by [32] and used recently in [21]. The class, denoted by {a mathematical formula}Pos∀G, extends {a mathematical formula}Pos with a special type of guarded formulae. It is defined as the closure of logical constants true and false and positive atoms of the form {a mathematical formula}R(x¯) and {a mathematical formula}x=y under {a mathematical formula}∧,∨,∀,∃ and the following rule:
      </paragraph>
      <list>
       <list-item label="•">
        if {a mathematical formula}φ(x¯,y¯) is a {a mathematical formula}Pos∀G formula in which all variables in {a mathematical formula}x¯ are distinct, and {a mathematical formula}α(x¯) is an atomic formula, then{a mathematical formula} is a {a mathematical formula}Pos∀G formula.
       </list-item>
      </list>
      <paragraph>
       That is, such formulae are either {a mathematical formula}∀x1,x2(x1=x2→φ(x1,x2,y¯)) for equational atoms, or {a mathematical formula}∀x¯(R(x¯)→φ(x¯,y¯)), where R is of arity {a mathematical formula}|x¯|.
      </paragraph>
      <paragraph>
       With this, the CWA representation system is defined as {a mathematical formula}RSowa(σ)=〈Dcwa(σ),Pos∀G,⊨〉. For each D with {a mathematical formula}Null(D)={⊥1,…,⊥n}, the formula {a mathematical formula}δD is{a mathematical formula} where {a mathematical formula}y¯=(y1,…,ym) is a tuple of variables whose length m is the arity of R, and for a tuple {a mathematical formula}t¯=(a1,…,am) in {a mathematical formula}RD we write {a mathematical formula}y¯=t¯ for {a mathematical formula}(y1=a1)∧…∧(ym=am).
      </paragraph>
      <paragraph label="Proposition 1">
       Each of{a mathematical formula}RSowa(σ),{a mathematical formula}RSwcwa(σ), and{a mathematical formula}RScwa(σ)is a representation system.
      </paragraph>
      <paragraph label="Proof">
       Conditions on Iso are easily checked: sets {a mathematical formula}〚D〛C are nonempty, since one can replace nulls with distinct constants from {a mathematical formula}Const−C, and {a mathematical formula}≈C∪C′⊆≈C∩≈C′. Monotonicity follows from the description of orderings {a mathematical formula}⪯⁎ by the existence of homomorphisms, and the fact that {a mathematical formula}∃Pos, {a mathematical formula}Pos and {a mathematical formula}Pos∀G formulae are preserved under homomorphisms (respectively onto and strong onto homomorphism), see [33], [34] for {a mathematical formula}∃Pos and {a mathematical formula}Pos and [32], [21] for {a mathematical formula}Pos∀G. And the properties of {a mathematical formula}δD are again straightforward from the definition of the semantics, as they simply state it in the language of FO.  □
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Properties of representation systems
      </section-title>
      <paragraph>
       We now collect some basic properties of representation systems, essentially the toolkit that will be useful later. We look at certain information contained in sets {a mathematical formula}〚x〛 and prove that, as expected, it is represented at the object level by x itself, and at the knowledge level by {a mathematical formula}δx, defining the semantics of x.
      </paragraph>
      <paragraph label="Proposition 2">
       In a pre-domain,{a mathematical formula}□O〚x〛=xfor every x.
      </paragraph>
      <paragraph label="Proof">
       Assume that {a mathematical formula}x≠⋀〚x〛. Then there is {a mathematical formula}y⪯̸x such that {a mathematical formula}y⪯c for each {a mathematical formula}c∈〚x〛. Since {a mathematical formula}y⪯̸x we have {a mathematical formula}〚x〛⊈〚y〛, i.e., there is {a mathematical formula}c∈〚x〛 such that {a mathematical formula}c∉〚y〛. But since {a mathematical formula}y⪯c, we have {a mathematical formula}〚c〛⊆〚y〛, and since {a mathematical formula}c∈C, this implies {a mathematical formula}c∈〚y〛 as {a mathematical formula}c∈〚c〛, which gives us the desired contradiction.  □
      </paragraph>
      <paragraph>
       Let {a mathematical formula}≈=⋃j∈J≈j, and let {a mathematical formula}〚x〛≈={c∈〚x〛|c≈x}. In the case of relational databases, {a mathematical formula}D≈D′ if {a mathematical formula}D,D′ are isomorphic objects; for instance, {a mathematical formula}D={(⊥,⊥)} and {a mathematical formula}D′={(1,1)} are isomorphic. Note that FO formulae not using constants are preserved by ≈. In general though, objects related by {a mathematical formula}≈j may not agree on all the formulae of {a mathematical formula}F (e.g., D and {a mathematical formula}D′ do not agree on the sentence {a mathematical formula}∃x(x=1)) and hence there are potentially formulae in {a mathematical formula}Th(〚x〛≈j) which are not satisfied by x. However, the following holds.
      </paragraph>
      <paragraph label="Proposition 3">
       In a representation system,{a mathematical formula}Th(〚x〛)=Th(〚x〛≈)=Th(x)for every x.
      </paragraph>
      <paragraph label="Proof">
       It suffices to prove {a mathematical formula}Th(〚x〛≈)=Th(x) since {a mathematical formula}Th(x)⊆Th(〚x〛)⊆Th(〚x〛≈). Let {a mathematical formula}c∈〚x〛≈; then {a mathematical formula}x⪯c and thus {a mathematical formula}Th(x)⊆Th(c), and hence {a mathematical formula}Th(x)⊆Th(〚x〛≈). Conversely, take {a mathematical formula}φ∈Th(〚x〛≈). We know that there is {a mathematical formula}j∈J so that whenever {a mathematical formula}y≈jy′, then {a mathematical formula}y,y′ agree on φ. Note that {a mathematical formula}φ∈Th(〚x〛≈j), since {a mathematical formula}〚x〛≈j⊆〚x〛≈. We know that {a mathematical formula}〚x〛≈j≠∅, so pick {a mathematical formula}c∈〚x〛≈j. Since {a mathematical formula}φ∈Th(〚x〛≈j), we have {a mathematical formula}c⊨φ, and since {a mathematical formula}c≈jx, we have {a mathematical formula}x⊨φ. Hence {a mathematical formula}φ∈Th(x), as required.  □
      </paragraph>
      <paragraph>
       Now we can show:
      </paragraph>
      <paragraph label="Proposition 4">
       In a representation system, for every object x:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Mod(δx)=↑x;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}δx=□K〚x〛.
       </list-item>
      </list>
      <paragraph label="Proof">
       To show the first item, choose {a mathematical formula}j∈J so that two objects related by {a mathematical formula}≈j agree on {a mathematical formula}δx. Since {a mathematical formula}〚x〛≈j is not empty, pick an object c from this set. Then {a mathematical formula}c⊨δx since {a mathematical formula}c∈〚x〛. Since c and x agree on {a mathematical formula}δx, we have {a mathematical formula}x⊨δx. By the monotonicity of formulae we conclude {a mathematical formula}↑x⊆Mod(δx). Suppose we have an object y such that {a mathematical formula}x⪯̸y and {a mathematical formula}y⊨δx. Then {a mathematical formula}〚y〛⊈〚x〛 and thus we have a complete object {a mathematical formula}c∈〚y〛−〚x〛. Since {a mathematical formula}y⪯c, we have {a mathematical formula}c⊨δx, contradicting {a mathematical formula}Mod(δx)∩C=〚x〛. This shows {a mathematical formula}Mod(δx)⊆↑x and thus {a mathematical formula}Mod(δx)=↑x.To prove the second item, we start by showing that {a mathematical formula}Mod(Th(x))=↑x. Let {a mathematical formula}y⪰x. By monotonicity we have {a mathematical formula}y∈Mod(Th(x)). Conversely let {a mathematical formula}y⪰̸x; then {a mathematical formula}δx∈Th(x)−Th(y) and hence {a mathematical formula}y∉Mod(Th(x)). Thus indeed {a mathematical formula}Mod(Th(x))=↑x. Since {a mathematical formula}↑x=Mod(δx) and {a mathematical formula}Mod(Th(x))=Mod(Th(〚x〛)) by Proposition 3, we have {a mathematical formula}Mod(δx)=Mod(Th(〚x〛)), i.e., {a mathematical formula}δx=□K〚x〛.  □
      </paragraph>
      <paragraph label="Corollary 1">
       In a representation system:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Mod(δx)=Mod(Th(x)), and
       </list-item>
       <list-item label="•">
        {a mathematical formula}□O〚x〛⊨□K〚x〛
       </list-item>
      </list>
      <paragraph>
       We remark that the condition {a mathematical formula}Mod(δx)=↑x could alternatively be used to define formulae {a mathematical formula}δx, since {a mathematical formula}Mod(φ)=↑x implies {a mathematical formula}Mod(φ)∩C=〚x〛. Indeed, consider any complete object c that satisfies φ. Then {a mathematical formula}x⪯c and we have {a mathematical formula}c∈〚c〛⊆〚x〛 by the properties of representation systems.
      </paragraph>
      <paragraph>
       Corollary 1 says that for sets X of the form {a mathematical formula}〚x〛 we have {a mathematical formula}□OX⊨□KX. We shall see later that the same is true for the important sets of the form {a mathematical formula}Q(〚x〛) that we need for defining certain answers. But in general, this condition need not hold. The reason is that taking the greatest lower bound of X may lose more information than taking the greatest lower bound of {a mathematical formula}Th(X), which indicates that working with certain knowledge may be preferable, as it conveys more information.
      </paragraph>
      <paragraph label="Proposition 5">
       There is a representation system and a set of objects X such that{a mathematical formula}□OX⊭□KX.
      </paragraph>
      <paragraph label="Proof">
       Consider a domain {a mathematical formula}D with the ordering {a mathematical formula}x1⪰x2⪰…⪰xn⪰…⪰x⁎. We assume that all {a mathematical formula}≈js are the same, and for each {a mathematical formula}xi, there is {a mathematical formula}ci⪰xi with {a mathematical formula}xi≈ci. The formulas are {a mathematical formula}φi for {a mathematical formula}i≥0. Let {a mathematical formula}Th(xi)={φ0}∪{φj|j≥i} (with {a mathematical formula}Th(ci)=Th(xi)) and {a mathematical formula}Th(x⁎)=∅. Let {a mathematical formula}X={xi|i≠0}. Then {a mathematical formula}⋀X=x⁎ and {a mathematical formula}Th(X)={φ0}; hence {a mathematical formula}□OX=x⁎ and {a mathematical formula}□KX=φ0 and thus {a mathematical formula}□OX⊭□KX.  □
      </paragraph>
      <paragraph>
       We finally give a condition equivalent to the existence of formulae {a mathematical formula}δx. A set Φ of formulae is finitely axiomatizable if there is a finite set {a mathematical formula}Φ0 such that {a mathematical formula}Mod(Φ)=Mod(Φ0).
      </paragraph>
      <paragraph label="Proposition 6">
       In a pre-representation system{a mathematical formula}RS∘whose formulae are closed under conjunction, the following are equivalent:
      </paragraph>
      <list>
       <list-item label="1.">
        each{a mathematical formula}Th(x)is finitely axiomatizable, and{a mathematical formula}Th(x)⊆Th(y)implies{a mathematical formula}x⪯yfor all{a mathematical formula}x,y;
       </list-item>
       <list-item label="2.">
        for each x, there is a formula{a mathematical formula}δxso that{a mathematical formula}Mod(δx)=↑x.
       </list-item>
      </list>
      <paragraph label="Proof">
       Assume the conditions in 1. hold and let {a mathematical formula}Φ0={φ1,…,φm} axiomatize {a mathematical formula}Th(x). Take {a mathematical formula}δx to be {a mathematical formula}φ1∧…∧φm. Then {a mathematical formula}Mod(δx)=Mod(Th(x)). Suppose {a mathematical formula}y⪰x. If {a mathematical formula}φ∈Th(x) then {a mathematical formula}y⊨φ and thus {a mathematical formula}y∈Mod(Th(x)). Conversely, let {a mathematical formula}y⪰̸x. Then we have {a mathematical formula}ψ∈Th(x)−Th(y) and thus {a mathematical formula}y∉Mod(Th(x)). Hence {a mathematical formula}↑x=Mod(Th(x))=Mod(δx).If we have {a mathematical formula}δx for each x, then {a mathematical formula}Mod(Th(x))=↑x. Indeed, assume {a mathematical formula}x⪯y; then {a mathematical formula}y⊨Th(x) by monotonicity. If {a mathematical formula}x⪯̸y, then {a mathematical formula}y⊭δx while {a mathematical formula}x⊨δx, so {a mathematical formula}y⊭Th(x). By the definition of {a mathematical formula}δx this implies {a mathematical formula}Mod(Th(x))=Mod(δx), with {a mathematical formula}δx axiomatizing {a mathematical formula}Th(x). Also if {a mathematical formula}Th(x)⊆Th(y), then {a mathematical formula}δx∈Th(y), hence {a mathematical formula}y⊨δx and thus {a mathematical formula}x⪯y.  □
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Certain knowledge as a greatest lower bound
      </section-title>
      <paragraph>
       We now show that {a mathematical formula}□KX can be viewed as a greatest lower bound as well. Note that we have a well-known preorder on sets of formulae, namely entailment: {a mathematical formula}Φ⊢Ψ iff {a mathematical formula}Mod(Φ)⊆Mod(Ψ). Thus, for any set of formulae Φ, we can look at its greatest lower bound in this preorder, i.e., a formula φ so that {a mathematical formula}φ⊢Φ, and whenever {a mathematical formula}ψ⊢Φ, we have {a mathematical formula}ψ⊢φ. If such a formula exists, it is denoted by ⋀Φ. Note that as with objects, ⊢ is a preorder, so technically ⋀Φ is a set of formulae, all of which, however, are equivalent, so we shall write {a mathematical formula}φ=⋀Φ when φ is one of such formulae.
      </paragraph>
      <paragraph label="Theorem 1">
       In a representation system,{a mathematical formula}□KX=⋀Th(X)for every set X of objects.
      </paragraph>
      <paragraph label="Proof">
       Assume that {a mathematical formula}α=⋀Th(X) exists. We have {a mathematical formula}Mod(α)⊆Mod(φ) for each {a mathematical formula}φ∈Th(X) and thus {a mathematical formula}Mod(α)⊆Mod(Th(X)). Suppose, for the sake of contradiction, that {a mathematical formula}Mod(α)⊊Mod(Th(X)), and take {a mathematical formula}y∈Mod(Th(X))−Mod(α). Since {a mathematical formula}y⊨φ for each {a mathematical formula}φ∈Th(X), we have that the same is true for every {a mathematical formula}z⪰y, and hence {a mathematical formula}Mod(δy)⊆Mod(φ) for each {a mathematical formula}φ∈Th(X). Thus {a mathematical formula}δy⊢Th(X), and by the definition of α as the greatest lower bound, we have {a mathematical formula}δy⊢α, and thus {a mathematical formula}Mod(δy)⊆Mod(α).Now assume {a mathematical formula}Mod(α)⊆Mod(δy). Then {a mathematical formula}Mod(α)=Mod(δy) and {a mathematical formula}y∈Mod(α), a contradiction. Hence, {a mathematical formula}Mod(α)⊈Mod(δy). But then {a mathematical formula}Mod(δy)⊈Mod(α) since {a mathematical formula}y⊭α, and at the same time {a mathematical formula}Mod(δy)⊆Mod(Th(X)) since {a mathematical formula}y∈Mod(Th(X)). Thus sets {a mathematical formula}Mod(δy) and {a mathematical formula}Mod(α) are incomparable subsets of {a mathematical formula}Mod(Th(X)): in particular, {a mathematical formula}α⊢Th(X), {a mathematical formula}δy⊢Th(X), and yet neither {a mathematical formula}α⊢δy nor {a mathematical formula}δy⊢α holds, contradicting the assumption that {a mathematical formula}α=⋀Th(X). This shows that {a mathematical formula}Mod(Th(X))−Mod(α)=∅ and thus {a mathematical formula}Mod(α)=Mod(Th(X)).Conversely, suppose we have α so that {a mathematical formula}Mod(α)=Mod(Th(X))=⋂φ∈Th(X)Mod(φ). Then {a mathematical formula}Mod(α)⊆Mod(φ) for each {a mathematical formula}φ∈Th(X) and thus {a mathematical formula}α⊢φ for each such φ. If there is any other formula ψ such that {a mathematical formula}ψ⊢φ for each {a mathematical formula}φ∈Th(X), then {a mathematical formula}Mod(ψ)⊆⋂φ∈Th(X)Mod(φ)=Mod(α) and thus {a mathematical formula}ψ⊢α, proving that {a mathematical formula}α=⋀Th(X).  □
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Defining certain answers to queries
     </section-title>
     <paragraph>
      Now we move to answering queries. We take an abstract view of queries, introduced in [35] and standard in database literature [19], when a query is viewed a mapping Q that takes an object and returns another object. In real life queries are written in a specific query language, but their semantics is of course such. For instance, relational queries take relational databases and return relational databases (most commonly, single relations), while they can be written in many languages such as FO, SQL, datalog, etc.
     </paragraph>
     <paragraph>
      Thus, for two database domains {a mathematical formula}D=〈D,C,〚〛,Iso〉 and {a mathematical formula}D′=〈D′,C′,〚〛′,Iso′〉, a query{a mathematical formula}Q:D→D′ is a mapping associating with an object {a mathematical formula}x∈D its answer, {a mathematical formula}Q(x)∈D′.
     </paragraph>
     <paragraph>
      The key requirement to queries is that they preserve informativeness, which can be stated as follows: if we know more about the input, then we know more about the output. By “knowing more”, we mean the information orderings ⪯ and {a mathematical formula}⪯′, given by the semantics of inputs and outputs (technically, they mean ‘knowing at least as much’). Indeed, if we have {a mathematical formula}x⪯y and we want to find {a mathematical formula}Q(y), then as a start, we could have used a less informative object x to compute {a mathematical formula}Q(x). Thus, {a mathematical formula}Q(y) should give us at least the information contained in {a mathematical formula}Q(x). If it does not, it simply means that the semantics {a mathematical formula}〚〛′ of query answers was chosen incorrectly. Thus, blindly using some fixed semantics for query results – as in fact is often done – does not necessarily make sense.
     </paragraph>
     <paragraph>
      Formally, this notion is defined as follows.
     </paragraph>
     <paragraph label="Definition 6">
      Preserving informativenessA query {a mathematical formula}Q:D→D′preserves informativeness if it is monotone with respect to the information orderings given by the semantics of query inputs and query answers, i.e.,{a mathematical formula}
     </paragraph>
     <paragraph>
      Certain answers to Q on an object x represent certain information in the set {a mathematical formula}Q(〚x〛)={Q(c)|c∈〚x〛}. We have seen that there are two ways to define it: as object, and as knowledge. For the latter, we need to have a representation system {a mathematical formula}RS=〈D′,F,⊨〉 over the target domain {a mathematical formula}D′. If we have it, we can either extract the most general object representing {a mathematical formula}Q(〚x〛), or the most general knowledge representing {a mathematical formula}Th(Q(〚x〛)). That is, we have two notions of certain answers:
     </paragraph>
     <list>
      <list-item label="•">
       as objects {a mathematical formula}certO(Q,x)=□OQ(〚x〛);
      </list-item>
      <list-item label="•">
       as knowledge {a mathematical formula}certK(Q,x)=□KQ(〚x〛).
      </list-item>
     </list>
     <paragraph>
      Comparing with relational theory  Let us now review the standard approach to query answering in relational databases. Ideally, one tries to find a query answer A so that {a mathematical formula}〚A〛′=Q(〚D〛). This is often impossible, in fact even for very simple queries [2]. So the next attempt is to find a formula {a mathematical formula}φQ,D in some logical formalism so that{a mathematical formula} When this happens, one refers to such a logical formalism as a strong representation system (see [19], [2]), which explains why we used the name ‘representation system’.
     </paragraph>
     <paragraph>
      The problem is that the structure of {a mathematical formula}Q(〚D〛) may be too “irregular” to be described by a nice formalism. For instance, it is known that under cwa, for relational calculus queries formulae {a mathematical formula}φQ,D can be of the following form: {a mathematical formula}∃u¯(α(u¯)∧⋀R∈σ∀x¯(R(x¯)↔⋁i(x¯=v¯i∧βi(x¯,u¯)))), where α and {a mathematical formula}βi are boolean combinations of equalities, {a mathematical formula}v¯is combine variables from {a mathematical formula}u¯ and constants, and {a mathematical formula}u¯ ranges over the underlying domain of constants rather than the active domain, see [2]. Syntactically, this is quite heavy, does not correspond to any natural fragment of FO, and it works only under the cwa.
     </paragraph>
     <paragraph>
      If the set {a mathematical formula}Q(〚D〛) does not happen to be of the form {a mathematical formula}Mod(φ) for some nice formula φ, the approach adopted in the database literature is to consider the object {a mathematical formula}⋂Q(〚D〛) as the answer. This is completely ad hoc, however: in general it does not have much in common with certain information contained in {a mathematical formula}Q(〚D〛).
     </paragraph>
     <paragraph>
      It seems much better to ask then, in place of (1), for an answer {a mathematical formula}φQ,D that is equivalent to the theory of {a mathematical formula}Q(〚D〛), rather than defining {a mathematical formula}Q(〚D〛) precisely. That is, we replace (1) with{a mathematical formula} which is, of course, our definition of certain answers expressed as knowledge.
     </paragraph>
     <paragraph>
      Note that (1) implies (2): this is an immediate consequence of the fact that {a mathematical formula}Mod(⋅) and {a mathematical formula}Th(⋅) define a Galois connection. Thus, the notion of certain answers as knowledge in a representation system is a weakening of the notion of the strong representation system, but much less ad hoc that replacing {a mathematical formula}Q(〚D〛) with {a mathematical formula}⋂Q(〚D〛).
     </paragraph>
     <paragraph>
      Example: when the representation system makes a difference  We can easily construct examples of relational queries Q and representation systems so that (1) fails while (2) is easily achieved. Suppose we have a schema with two relations {a mathematical formula}R,S (for simplicity, just sets), and the query {a mathematical formula}R−S (in FO, {a mathematical formula}R(x)∧¬S(x)), and assume closed-world semantics. Consider D in which {a mathematical formula}R={1,2} and {a mathematical formula}S={⊥}. Then {a mathematical formula}Q(〚D〛cwa)={{1},{2},{1,2}}. Suppose the representation system is {a mathematical formula}〈D(σ),∃Pos,⊨〉. Since {a mathematical formula}∃Pos formulae are monotone, there is no {a mathematical formula}φ∈∃Pos with {a mathematical formula}Mod(α)=Q(〚D〛cwa). But there an {a mathematical formula}∃Pos formula φ one such that {a mathematical formula}Mod(φ)=Mod(Th(Q(〚D〛cwa))). In fact, the obvious answer {a mathematical formula}φ=A(1)∨A(2) does the job (we use predicate {a mathematical formula}A(⋅) for ‘answer’). To see this, it suffices to note that {a mathematical formula}∃Pos formulae, which are disjunctions of conjunctive queries, are in {a mathematical formula}Th(Q(〚D〛cwa)) if they are disjunctions of conjunctive queries that are true in {1}, {2}, and {a mathematical formula}{1,2}. Those are conjunctive queries implied by the positive diagrams of such instances, i.e., {a mathematical formula}A(1), {a mathematical formula}A(2), and {a mathematical formula}A(1)∧A(2). From this one easily derives that {a mathematical formula}Mod(Th(Q(〚D〛cwa))) consists of instances containing either 1 or 2.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Computing certain answers
     </section-title>
     <paragraph>
      We now look at computing certain answers for queries. We show that with the proper semantics of query answering, where more informative inputs lead to more informative answers, finding certain answers is reduced to query evaluation. That is, certain answer as object, or {a mathematical formula}certO(Q,x), is just {a mathematical formula}Q(x), while certain answer as knowledge, {a mathematical formula}certK(Q,x), is {a mathematical formula}δQ(x).
     </paragraph>
     <paragraph>
      Crucially, the former condition is a corollary of the latter: without a representation system for query answers, it may not be true. We explain how these general results apply to relational owa, wcwa, and cwa semantics. We also revisit the intersection-based definition of certain answers and show that it only makes sense under very restricted scenarios. Finally, we show that the knowledge approach to certain answers gives us extra flexibility compared to the object approach.
     </paragraph>
     <paragraph>
      Recall that queries are required to preserve informativeness: {a mathematical formula}x⪯y implies {a mathematical formula}Q(x)⪯′Q(y). We need an additional condition of genericity, which is standard in the database context (see, e.g., [19]). Essentially, this condition says that queries applied to isomorphic objects return isomorphic objects. For instance, for queries expressible in first-order logic that do not refer to constants, if two databases D and {a mathematical formula}D′ are isomorphic, then so are the answers {a mathematical formula}Q(D) and {a mathematical formula}Q(D′). If queries use constants, this is true when isomorphisms of databases leave those constants intact. In our abstract setting such isomorphisms are captured via relations in Iso. Hence, the analog of the genericity condition in this setting is as follows.
     </paragraph>
     <paragraph label="Definition 7">
      GenericityA query {a mathematical formula}Q:D→D′ is generic if for every j, there is k so that {a mathematical formula}x≈ky implies {a mathematical formula}Q(x)≈j′Q(y).
     </paragraph>
     <paragraph>
      We now state the main result about computing certain answers, and after proving it discuss what it means for finding query answers, and what are the conditions imposed on queries and databases.
     </paragraph>
     <paragraph label="Theorem 2">
      Let{a mathematical formula}Q:D→D′be a query that preserves informativeness and is generic. Assume that there is a representation system{a mathematical formula}RS=〈D′,F,⊨〉over the domain of query answers. Then, for every object x,
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}certO(Q,x)=Q(x), and
      </list-item>
      <list-item label="•">
       {a mathematical formula}certK(Q,x)=δQ(x).
      </list-item>
     </list>
     <paragraph label="Proof">
      We start by showing {a mathematical formula}certK(Q,x)=δQ(x). By the definition of {a mathematical formula}certK(Q,x) as {a mathematical formula}□KQ(〚x〛), it suffices to show that{a mathematical formula} for every x. Since we know that {a mathematical formula}Mod(δz)=Mod(Th(z)), for every z, by Corollary 1, we just need to show{a mathematical formula} to conclude (3). Suppose {a mathematical formula}φ∈Th(Q(x)). Since {a mathematical formula}c⪰x for every {a mathematical formula}c∈〚x〛, then {a mathematical formula}Q(x)⪯′Q(c) and {a mathematical formula}Q(c) satisfies φ as well by the properties of representation systems, proving that {a mathematical formula}φ∈Th(Q(〚x〛)).Conversely, if {a mathematical formula}φ∈Th(Q(〚x〛)), consider j such that {a mathematical formula}z≈j′z′ implies that {a mathematical formula}z,z′ agree on φ for every {a mathematical formula}z,z′ (which exists by the definition of representation systems). By genericity, we have k so that {a mathematical formula}y≈ky′ implies {a mathematical formula}Q(y)≈j′Q(y′) for every {a mathematical formula}y,y′. We know that {a mathematical formula}〚x〛≈k is nonempty; this pick an element c in this set. We have {a mathematical formula}c∈〚x〛 and {a mathematical formula}c≈kx. Hence (a) {a mathematical formula}Q(c)∈Q(〚x〛) and (b) {a mathematical formula}Q(c)≈j′Q(x). Then (a) implies that {a mathematical formula}Q(c)⊨φ, and (b) then implies that {a mathematical formula}Q(x)⊨φ, thus showing that {a mathematical formula}φ∈Th(Q(x)) and proving (4) and (3).Now we prove the result about certain answers at the object level. Since Q is monotone, we have {a mathematical formula}Q(x)⪯′z for each {a mathematical formula}z∈Q(〚x〛) (we denote this by {a mathematical formula}Q(x)⪯′Q(〚x〛). Suppose we have {a mathematical formula}y⪯′Q(〚x〛). Then {a mathematical formula}Th(y)⊆Th(Q(〚x〛)) and by (4), {a mathematical formula}Th(y)⊆Th(Q(x)). Since {a mathematical formula}δy∈Th(y), we have {a mathematical formula}δy∈Th(Q(x)), and thus {a mathematical formula}Q(x)⊨δy and {a mathematical formula}y⪯′Q(x). Therefore, {a mathematical formula}Q(x) is the greatest lower bound of {a mathematical formula}Q(〚x〛), that is, {a mathematical formula}Q(x)=certO(Q,x).  □
     </paragraph>
     <section label="7.1">
      <section-title>
       Discussion
      </section-title>
      <paragraph>
       Theorem 2 says that the new definition of certain answers based on greatest lower bounds provides correctness guarantees. The conditions required for this are genericity and monotonicity of the query, as well as having a representation system for query answers. We now discuss the importance of these requirements, and how much they actually impose on the setting.
      </paragraph>
      <paragraph>
       The existence of a representation system  This condition is essential: one can easily find examples where, in the absence of a representation system, correctness guarantees do not hold. For instance, as the input domain we consider {a mathematical formula}D={x,c1,c2} such that {a mathematical formula}c1,c2 are complete objects, incomparable with each other, and {a mathematical formula}x≺c1,c2 (of course {a mathematical formula}x≺y means that {a mathematical formula}x⪯y holds but {a mathematical formula}y⪯x does not). In {a mathematical formula}D′, we have three complete objects {a mathematical formula}c′,c1′,c2′ and an incomplete object {a mathematical formula}x′, with the ordering {a mathematical formula}x′⪯′c′ and {a mathematical formula}c′⪯′c1′,c2′. Now define the query Q by {a mathematical formula}Q(x)=x′, {a mathematical formula}Q(c1)=c1′ and {a mathematical formula}Q(c2)=c2′. Then {a mathematical formula}Q(x)≺′certO(Q,x)=c′. The existence of representation systems prevents this behavior. Indeed, if we had formulae δ, we would have had {a mathematical formula}δc′∈Th(Q(〚x〛))−Th(Q(x)), which is made impossible by (4) in the presence of a representation system.
      </paragraph>
      <paragraph>
       Thus, it is essential to go via certain answers as knowledge to get the object representation. On the positive side, for common semantics (e.g., owa and cwa), representation systems can easily be constructed.
      </paragraph>
      <paragraph>
       Genericity  In many formalisms, this is essentially a “free” condition: genericity applies to most of the logical formalisms used for querying databases. There are exceptions, however, but the machinery developed here lets us handle those exceptions.
      </paragraph>
      <paragraph>
       One of the exceptions is given by languages capable of referring to infinitely many constants. Such languages occur, for instance, in data exchange [6], where it is sometimes necessary to distinguish constants from nulls [36], [37], especially with rather expressive mappings. But then we can use another condition in place of genericity.
      </paragraph>
      <paragraph>
       The condition is a substitution property with respect to two representation systems {a mathematical formula}RS=〈D,F,⊨〉 and {a mathematical formula}RS′=〈D′,F′,⊨′〉. We say that a query Q has the substitution property with respect to {a mathematical formula}RS and {a mathematical formula}RS′ if for each {a mathematical formula}φ∈F′, there exists {a mathematical formula}φQ∈F so that {a mathematical formula}x⊨φQ iff {a mathematical formula}Q(x)⊨′φ. Intuitively, we can think of both φ and Q given as logical formulae, and allow Q to be substituted for predicate symbols used in φ.
      </paragraph>
      <paragraph label="Proposition 7">
       Let{a mathematical formula}Q:D→D′be a query that preserves informativeness, and assume we have representation systems{a mathematical formula}RSand{a mathematical formula}RS′so that Q has the substitution property with respect to them. Then, for every object x,
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}certO(Q,x)=Q(x), and
       </list-item>
       <list-item label="•">
        {a mathematical formula}certK(Q,x)=δQ(x).
       </list-item>
      </list>
      <paragraph label="Proof">
       We just need to prove (4) and then the proof of Theorem 2 will apply. The inclusion {a mathematical formula}Th(Q(x))⊆Th(Q(〚x〛)) is proved as before. For the converse, let φ be in {a mathematical formula}Th(Q(〚x〛)); take {a mathematical formula}φQ that exists by the substitution property. Since {a mathematical formula}Q(c)⊨′φ for each {a mathematical formula}c∈〚x〛, we have {a mathematical formula}c⊨φQ, and thus {a mathematical formula}φQ∈Th(〚x〛). But we know by Proposition 3 that {a mathematical formula}Th(〚x〛)=Th(x) and hence {a mathematical formula}φQ∈Th(x). But now the substitution property and {a mathematical formula}x⊨φQ imply {a mathematical formula}Q(x)⊨′φ, showing {a mathematical formula}φ∈Th(Q(x)) and proving the converse inclusion.  □
      </paragraph>
      <paragraph>
       Yet another situation where genericity is lost is when nulls and constants behave differently in queries. This is the standard behavior of SQL, for instance: any comparison involving a null results in a truth value unknown[24]. That is, checking {a mathematical formula}⊥1=⊥2 results in unknown, but of course under the mapping {a mathematical formula}⊥1↦1,⊥2↦2 the comparison becomes false, which easily leads to non-genericity. In fact there are several variants of SQL-like evaluation procedures with nulls [38], and they all lack genericity.
      </paragraph>
      <paragraph>
       However, in this case we get a simple corollary that provides us with some correctness guarantees.
      </paragraph>
      <paragraph label="Corollary 2">
       If genericity is dropped as an assumption ofTheorem 2, i.e., we have a query Q that preserves informativeness but is not necessarily generic, then{a mathematical formula}Q(x)⪯′certO(Q,x), and{a mathematical formula}δQ(x)∈Th(Q(〚x〛)).
      </paragraph>
      <paragraph>
       In other words, in this case the basic query evaluation {a mathematical formula}Q(x) provides us with an approximation of certain answers, since it gives us some, but perhaps not all, information that certain answers contain. Assuming that Q itself is efficient, this becomes an efficient approximation. In fact this idea was recently used to provide efficient evaluation of SQL queries with nulls that provides certainty guarantees [38].
      </paragraph>
      <paragraph>
       Preserving informativeness  Monotonicity, or preserving informativeness, is the crucial condition. However natural it is, it was ignored by most of the work on incompleteness which also ignored the task of choosing the right semantics of query answers. In fact most often one just blindly uses some fixed semantics for query outputs, which is often not justified. So to get correctness “for free”, one has to work after all, and the important work is to understand the right semantics of query answers which ensures the basic principle of preserving informativeness.
      </paragraph>
      <paragraph>
       One possible approach to achieving monotonicity of queries is to insist on some fixed semantics of query answers, and then look at restrictions of queries under which monotonicity is achieved. This is essentially what approaches based on naïve evaluation[2], [21], [30] do. Indeed, Theorem 2 says that certain answers are computed by the evaluation of the query itself, and the goal of naïve evaluation is the same.
      </paragraph>
      <paragraph>
       A different approach is to fix a language {a mathematical formula}L, and try to find a semantics of query answering so that all the queries in {a mathematical formula}L are monotone. This has been explored to a lesser extent, although this is the direction that needs to be developed if we want to learn how to answer complex queries with certainty (since naïve evaluation inevitably imposes restrictions on queries).
      </paragraph>
      <paragraph>
       We now offer one simple observation in this direction, showing that a defining certain answers as greatest lower bounds makes them behave reasonably. Namely, assume that a query Q is only defined on complete objects, and we want to extend it to all objects. The natural way to do this is to use certain answers as objects, i.e., the query {a mathematical formula}certO(Q) that sends each object x to {a mathematical formula}certO(Q,x). The following is immediate from the definitions.
      </paragraph>
      <paragraph label="Proposition 8">
       For an arbitrary query Q defined on complete objects, the query{a mathematical formula}certO(Q)preserves informativeness.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}x⪯y. Then {a mathematical formula}〚y〛⊆〚x〛 and {a mathematical formula}Q(〚y〛)⊆Q(〚x〛). Thus if greatest lower bounds of these sets are defined, we have {a mathematical formula}⋀Q(〚x〛)⪯′Q(〚y〛), i.e., {a mathematical formula}certO(Q,x)⪯′certO(Q,y).  □
      </paragraph>
      <paragraph>
       This proposition only confirms that certain answers, as defined here, behave logically. It does not give a recipe to compute them, but suggests new approaches which we shall discuss in the concluding section.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Certain answers for relational queries
      </section-title>
      <paragraph>
       We now look at examples of concrete domains and representation systems for relational databases. The domains of input databases are always {a mathematical formula}D⁎(σ), containing databases of vocabulary σ, with ⁎ being the semantics. If a query Q returns sets of m-ary tuples, the domain {a mathematical formula}D′ will have as objects databases of vocabulary {a mathematical formula}σm that contains a single m-ary relation {a mathematical formula}A(⋅). But what will the semantics be?
      </paragraph>
      <paragraph>
       To see what semantics was used, look at the classical certain answers, as defined in [2], [19], for Boolean queries. For an input database D, we have {a mathematical formula}cert∩(Q,D)=true iff {a mathematical formula}Q(D′)=true for every {a mathematical formula}D′∈〚D〛, and {a mathematical formula}cert∩(Q,D)=false iff just one {a mathematical formula}Q(D′) evaluates to false. Viewing this way of computing certain answers as the greatest lower bound corresponds to the ordering false ⪯ true. Or, if false is represented by the empty set and true by the set {a mathematical formula}{()} containing the empty tuple, this corresponds to the subset ordering. Going to non-Boolean queries, we note that {a mathematical formula}cert∩(Q,D) is the greatest lower bound in the same ordering ⊆ on query answers that happen not to contain nulls.
      </paragraph>
      <paragraph>
       In particular, this means that in the standard relational query answering over incomplete databases one assumes the open world semantics for query answers since tuples can be added. And note that the ordering {a mathematical formula}⪯owa becomes ⊆ when restricted to databases without nulls.
      </paragraph>
      <paragraph>
       We thus look at relational queries as mappings {a mathematical formula}Q:D⁎(σ)→Dowa(σm). The following proposition states that monotonicity (i.e., preservation of informativeness) for these classes is achieved for classes of FO formulae seen earlier.
      </paragraph>
      <paragraph label="Proposition 9">
       Consider an m-ary relational query{a mathematical formula}Q:D⁎(σ)→Dowa(σm). Then Q is preserves informativeness
      </paragraph>
      <list>
       <list-item label="•">
        for ⁎=owa, when Q is an{a mathematical formula}∃Posquery;
       </list-item>
       <list-item label="•">
        for ⁎=wcwa, when Q is an{a mathematical formula}Posquery;
       </list-item>
       <list-item label="•">
        for ⁎=cwa, when Q is an{a mathematical formula}Pos∀Gquery.
       </list-item>
      </list>
      <paragraph label="Proof">
       We need to show the following. Suppose {a mathematical formula}h:D→D′ is a homomorphism, and {a mathematical formula}a¯ is an m-tuple of elements of {a mathematical formula}adom(D) such that {a mathematical formula}a¯∈Q(D). Then {a mathematical formula}h(a¯)∈Q(D′) if:
      </paragraph>
      <list>
       <list-item label="•">
        Q is definable in {a mathematical formula}∃Pos, or
       </list-item>
       <list-item label="•">
        Q is definable in {a mathematical formula}Pos and h is onto, or
       </list-item>
       <list-item label="•">
        Q is definable in {a mathematical formula}Pos∀G, and h is strong onto.
       </list-item>
      </list>
      <paragraph>
       This proposition, combined with Theorem 2, gives us the following.
      </paragraph>
      <paragraph label="Corollary 3">
       Let Q be an m-ary relational query. If its answers are interpreted under theowasemantics, then{a mathematical formula}certO(Q,D)=Q(D)provided that
      </paragraph>
      <list>
       <list-item label="•">
        input databases are interpreted underowaand Q is definable in{a mathematical formula}∃Pos, or
       </list-item>
       <list-item label="•">
        input databases are interpreted underwcwaand Q is definable in{a mathematical formula}Pos, or
       </list-item>
       <list-item label="•">
        input databases are interpreted undercwaand Q is definable in{a mathematical formula}Pos∀G.
       </list-item>
      </list>
      <paragraph>
       For the “classical” way of defining certain answers, which involves throwing away tuples with nulls and computing intersection, the notion of naïve evaluation involves computing {a mathematical formula}Q(D) and throwing away tuples with nulls [2], [21]. Note that using the new notion of certain answers, namely {a mathematical formula}certO(Q,D), for the same classes of queries we no longer need to throw away tuples containing nulls: simply computing {a mathematical formula}Q(D) does the job. Returning to the example from the introduction, if we have a database D with a relation {a mathematical formula}RD={(1,2),(3,⊥)} and a query Q that returns that relation, the classical naïve evaluation produces a single tuple {a mathematical formula}(1,2), while {a mathematical formula}certO(Q,D) returns {a mathematical formula}RD itself, as expected.
      </paragraph>
      <paragraph>
       The operator {a mathematical formula}πC that simply keeps all tuples that only use constants, is monotone (i.e., preserves informativeness) with respect {a mathematical formula}⪯owa. Thus, if we use the owa semantics for answers, it is harmless, but still it may unnecessarily eliminate tuples from answers, as we have seen (not to mention that it costs us computationally). Furthermore, for other orderings, such as {a mathematical formula}⪯cwa and {a mathematical formula}⪯wcwa, it is not even monotone, as the above example of {a mathematical formula}RD={(1,2),(3,⊥)} shows. Thus, the use of the intersection operator is not necessary under owa and is rather problematic under wcwa and cwa.
      </paragraph>
      <paragraph label="Example 2">
       We now show how Theorem 2, together with descriptions of representation systems for owa and cwa, immediately yields results presented in Example 1.Recall that we have a database D with a single relation R with tuples {a mathematical formula}(1,2) and {a mathematical formula}(3,⊥). Consider the identity query Q (i.e., a query that simply returns R). We can view it as a query from {a mathematical formula}Dowa(σ2) to {a mathematical formula}Dowa(σ2); recall that {a mathematical formula}σ2 is the vocabulary of a single binary relation. For the representation system on {a mathematical formula}Dowa we use {a mathematical formula}∃Pos formulae, as before. Clearly Q is generic and preserves informativeness (i.e., is monotone), and thus {a mathematical formula}□K〚D〛owa=certK(Q,D)=δD by Theorem 2. The latter is the positive diagram of D as we saw, and hence {a mathematical formula}□K〚D〛owa=∃zR(1,2)∧R(3,z), as was stated in Example 1.Next we consider the query {a mathematical formula}πC eliminating tuples with nulls as a query from {a mathematical formula}Dowa(σ2) to {a mathematical formula}DowaC(σ2), where the range of the latter is restricted only to databases without nulls. Again this query is monotone and generic, and it is easy to see that with the class of ground atoms and their conjunctions, {a mathematical formula}DowaC(σ) forms a representation system. Hence Theorem 2 tells us that {a mathematical formula}certK(πC,D)=□K〚D〛owa=δπC(D) (with respect to the representation system based on conjunctions of ground atoms). Since the semantics remains to be owa, we get {a mathematical formula}δπC(D)=R(1,2), again as stated in Example 1.Finally, we can consider the identity query Q as a query from {a mathematical formula}Dcwa(σ2) to {a mathematical formula}Dcwa(σ2). We know what representation system to use for cwa: it is the one based on {a mathematical formula}Pos∀G formulae. Query Q is clearly monotone and generic, and hence again by Theorem 2 we have {a mathematical formula}certK(Q,D)=□K〚D〛cwa=δD, where the latter, in the {a mathematical formula}Pos∀G representation system is given by {a mathematical formula}∃z(R(1,2)∧R(3,z)∧∀x,yR(x,y)→((x=1∧y=2)∨(x=3∧y=z))).
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Closed world query answering
      </section-title>
      <paragraph>
       We have seen that under cwa, we have the largest class of queries for which certain answers can be found by straightforward query evaluation, applying Theorem 2. We now have a deeper look at {a mathematical formula}Pos∀G queries and provide more intuition about their power, both in terms of their logical expressiveness, and their procedural implementation in terms of relational algebra.
      </paragraph>
      <paragraph>
       We first extend the class {a mathematical formula}Pos∀G syntactically. Define a class {a mathematical formula}∃Pos0 as follows:
      </paragraph>
      <list>
       <list-item label="•">
        if x and y are distinct variables, then {a mathematical formula}x=y is in {a mathematical formula}∃Pos0;
       </list-item>
       <list-item label="•">
        if {a mathematical formula}x¯ is an n-tuple of distinct variables and R is a relation symbol of arity n, then {a mathematical formula}R(x¯) is in {a mathematical formula}∃Pos0;
       </list-item>
       <list-item label="•">
        if {a mathematical formula}φ1(x¯) and {a mathematical formula}φ2(x¯) are formulae in {a mathematical formula}∃Pos0, then {a mathematical formula}ψ(x¯)=φ1(x¯)∨φ2(x¯) is in {a mathematical formula}∃Pos0;
       </list-item>
       <list-item label="•">
        if {a mathematical formula}φ1(x¯1) and {a mathematical formula}φ2(x¯2) are formulae in {a mathematical formula}∃Pos0, and {a mathematical formula}x¯1,x¯2 have no variables in common, then {a mathematical formula}ψ(x¯1,x¯2)=φ1(x¯1)∧φ2(x¯2) is in {a mathematical formula}∃Pos0;
       </list-item>
       <list-item label="•">
        if {a mathematical formula}φ(x¯,z¯) is a formula in {a mathematical formula}∃Pos0, then {a mathematical formula}ψ(x¯)=∃z¯φ(x¯,z¯) is a formula in {a mathematical formula}∃Pos0.
       </list-item>
      </list>
      <paragraph>
       In other words, we restrict the class {a mathematical formula}∃Pos so that conjunction can only be taken when the conjuncts have no free variable in common, and disjunction when the free variables of disjuncts coincide.
      </paragraph>
      <paragraph>
       Using this, we define an extension {a mathematical formula}Posext∀G of the class {a mathematical formula}Pos∀G by changing the last formation rule from {a mathematical formula}∀x¯(α(x¯)→φ(x¯,y¯)) for atomic α by allowing the formulae {a mathematical formula}α(x¯) to be from {a mathematical formula}∃Pos0.
      </paragraph>
      <paragraph label="Proposition 10">
       The classes{a mathematical formula}Pos∀Gand{a mathematical formula}Posext∀Gare equally expressive (i.e., for every formula of{a mathematical formula}Posext∀Gthere is an equivalent formula of{a mathematical formula}Pos∀Gand vice versa).
      </paragraph>
      <paragraph label="Proof">
       To show this, one simply transforms the guarded formulae until the antecedents α become atomic formulae. This is done by using equivalences of{a mathematical formula} when {a mathematical formula}x¯1,x¯2 share no variables, as well as of{a mathematical formula} and{a mathematical formula} which are all readily verified. By applying these to a {a mathematical formula}Posext∀G formula, we eventually put it into the {a mathematical formula}Pos∀G format, as follows from the definition of {a mathematical formula}∃Pos0.  □
      </paragraph>
      <paragraph>
       We can turn the above observation into a statement about the expressiveness of {a mathematical formula}Pos∀G queries at the relational algebra level, showing how much we can move away from the traditional unions of conjunctive queries under the cwa. Recall that relational algebra [19] consists of five operations: projection π, selection σ, Cartesian product ×, union ∪, and difference −. The first four, known as positive relational algebra, capture exactly the power of {a mathematical formula}∃Pos, or unions of conjunctive queries (hence also called select–project–join–union queries [19]). With the difference operator −, we get the full power of FO.
      </paragraph>
      <paragraph>
       However, relational algebra often relies on some derived operations for implementing commonly occurring queries. When it comes to queries with for-all conditions, the most common such operation is division[19], [39]. If we have a relation R with attributes {a mathematical formula}A1,…,Am,B1,…,Bk and a relation S with attributes {a mathematical formula}B1,…,Bk, then {a mathematical formula}R÷S contains tuples of A-attributes of R that appear in R in every possible combination with a tuple from S, i.e., {a mathematical formula}R÷S={t¯∈πA¯(R)|∀s¯∈S:(t¯,s¯)∈R} (here {a mathematical formula}πA¯ is the projection operator that only keeps attributes {a mathematical formula}A1,…,Am). It correspond to a very common class of queries, such as ‘find students who take all classes’. The operation of division is of course expressible with {a mathematical formula}σ,π,×,∪,−.
      </paragraph>
      <paragraph>
       To show what the class {a mathematical formula}Pos∀G gives us in terms of relational algebra, we first define a class {a mathematical formula}RA(Δ,π,×,∪) of queries as follows. Let Δ be the query returning {a mathematical formula}{(a,a)|a∈adom(D)}; it is easily definable in positive relational algebra. Then {a mathematical formula}RA(Δ,π,×,∪) is the class of relational algebra queries obtained from base relations and Δ by closing them under π, ×, and ∪. Now we define {a mathematical formula}RAcwa as follows:
      </paragraph>
      <list>
       <list-item label="•">
        Each relation name is an {a mathematical formula}RAcwa query;
       </list-item>
       <list-item label="•">
        {a mathematical formula}RAcwa is closed under {a mathematical formula}σ,π,×, and ∪ (i.e., all operations of the positive relational algebra);
       </list-item>
       <list-item label="•">
        if Q is an {a mathematical formula}RAcwa query, and {a mathematical formula}Q′ is an {a mathematical formula}RA(Δ,π,×,∪) query, then {a mathematical formula}Q÷Q′ is in {a mathematical formula}RAcwa.
       </list-item>
      </list>
      <paragraph>
       Now noticing that the guarded formulae used in the definition of {a mathematical formula}Posext∀G correspond to the division operator, one can follow the definition of {a mathematical formula}Posext∀G and obtain the following corollary of Proposition 10.
      </paragraph>
      <paragraph label="Corollary 4">
       {a mathematical formula}Pos∀Gand{a mathematical formula}RAcwaare equally expressive.
      </paragraph>
      <paragraph>
       Consequently if input databases are interpreted under cwa and query outputs under owa, as is very common, then {a mathematical formula}certO(Q,D)=Q(D) for all {a mathematical formula}RAcwa queries. This gives so far the largest known class of relational algebra queries for which we can produce certain answers by simply evaluating queries on the input database, and it is expressed using well known operations of relational algebra, both basic and derived ones.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>