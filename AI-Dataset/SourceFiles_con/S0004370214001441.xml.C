<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Speeding up operations on feature terms using constraint programming and variable symmetry.
   </title>
   <abstract>
    Feature terms are a generalization of first-order terms which have recently received increased attention for their usefulness in structured machine learning, natural language processing and other artificial intelligence applications. One of the main obstacles for their wide usage is that, when set-valued features are allowed, their basic operations (subsumption, unification, and antiunification) have a very high computational cost. We present a Constraint Programming formulation of these operations, which in some cases provides orders of magnitude speed-ups with respect to the standard approaches. In addition, exploiting several symmetries – that often appear in feature terms databases – causes substantial additional savings. We provide experimental results of the benefits of this approach.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Structured machine learning (SML) [1] focuses on developing machine learning techniques for rich representations such as feature terms [2], [3], [4], Horn clauses [5], or description logics [6]. SML has received an increased amount of interest in the recent years for several reasons, such as allowing the handling of complex data in a natural way, or allowing sophisticated forms of inference. For example, SML techniques are of special interest in biomedical applications, where they can reason directly over the molecular structure of complex chemical and biochemical compounds. One of the major difficulties in SML is that the basic operations required to design machine learning algorithms for structured representations have a high computational complexity. Consequently, techniques for efficiently implementing such operations are key for the application of SML techniques to real-life applications with large complex data.
     </paragraph>
     <paragraph>
      Efficient algorithms for these operations in some structured representations, such as Horn clauses, have been proposed in the literature [7]. However, efficient algorithms for other representations, such as feature terms, still do not exist. This paper focuses on feature terms, a generalization of first-order terms that has been introduced in theoretical computer science in order to formalize object-oriented capabilities of declarative languages. Feature terms have recently received increased attention for their usefulness in SML applications [8], [9], [10], [11], [12], [4], as well as in natural language processing [13], [14], [15], [16]. The most basic operation among feature terms is subsumption, which determines whether a given term is more general than another and is the most essential component for defining many algorithms using feature terms. For example, subsumption is often used by inductive machine learning methods that work by generating hypotheses (often in the form of rules) that are generalizations of the training instances being provided. The “generality relation” (subsumption) states whether a hypothesis covers a training instance or not, and thus it is one of the most fundamental operations in inductive machine learning. Moreover, it is well known that if we allow set-valued features in feature terms [3] subsumption between feature terms has a high computational cost. Subsumption is known to be linear in feature terms when set-valued features are not allowed [17] but, as noted by [3], it is exponential in the general case, when set-valued features are allowed (for example, when describing family relations as feature terms, the feature “children” would be set-valued, since a person can have more than one child).
     </paragraph>
     <paragraph>
      The two other basic operations in feature terms are unification (also known as the lss, or the least special specialization) and antiunification (also known as the lgg, or the least general generalization). Antiunification is common in structured machine learning algorithms, such as those studied in the Inductive Logic Programming (ILP). On the other hand, unification between feature terms is a common operation in Natural Language Processing (NLP), where feature terms are commonly known as typed feature structures[13], [18]. These operations are defined in terms of subsumption (see Section 2.2), so, when applied to set-valued feature terms they also have a high computational cost{sup:1}; in addition, unification and antiunification do not produce a unique result for set-valued feature terms [21].
     </paragraph>
     <paragraph>
      Set-valued feature terms are required to represent most ILP datasets, where one to many relations appear naturally (for example, in the datasets used in this paper, the relations between atoms in a complex molecule are set-valued). Also set-valued feature terms are useful in NLP, specially for HPSG grammars [21]. Existing implementations of set-valued feature terms operations require an exhaustive search with backtracking in large search spaces (Section 4.1). We have taken as representative of this approach the algorithm described in [22]. The same strategy has been used in other ILP/NLP works when dealing with feature terms (see footnote 4 later).
     </paragraph>
     <paragraph>
      In this paper we formulate the above operations for set-valued feature terms as Constraint Satisfaction Problems (CSP). We have implemented them in existing Constraint Programming (CP) environments. Results show clear efficiency gains: in some cases, our CP implementations provide speed-ups of orders of magnitude with respect to an existing implementation based on depth-first search. In addition, when these CP implementations are enhanced with symmetry breaking constraints that exploit different types of symmetries in feature terms, we obtain substantial extra gains in performance. We believe these results may be of interest for the ILP and NLP communities, where set-valued feature terms can be beneficial. Our CP implementations use the JaCoP [23] and Cream [24] open-source constraint programming libraries for Java.
     </paragraph>
     <paragraph>
      We are aware of a previous use of constraints to compute subsumption in SML [7], focusing on θ-subsumption. However, feature term subsumption is significantly different from θ-subsumption, which is defined as the existence of a variable substitution between logical clauses without considering essential elements of feature terms such as sets or loops [12]. Also, efficient algorithms for unification for the restricted case of non-set-valued feature terms exist [20], but are not applicable to the general case of set-valued feature terms. The work presented in this paper extends our previous work on using constraints for addressing feature term operations [25], [26] by providing a new set of theoretical and practical results which allows the use of symmetry breaking constraints to model not only subsumption but also antiunification, obtaining significant gains in execution time.
     </paragraph>
     <paragraph>
      The remainder of this paper is organized as follows. Section 2 provides some necessary background on feature terms and constraint satisfaction. Then Sections 3, 4, and 5 present our CSP formulation of the subsumption, antiunification and unification operations respectively, providing experimental evidence of the benefits of such formulations (using the CP environments mentioned above). The paper closes with some discussion of the results and potential venues of future research.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      This section provides the necessary background on feature terms and constraint satisfaction that we will use in the rest of the paper.
     </paragraph>
     <section label="2.1">
      <section-title>
       Feature terms
      </section-title>
      <paragraph>
       Feature terms [2], [3] (also called typed feature structures or Ψ-terms, and forming the basis of Order-Sorted Feature logics) are a generalization of first-order terms, introduced in theoretical computer science to formalize object-oriented declarative languages. Feature terms correspond to a different, but equally expressive, subset of first-order logics than description logics [27].
      </paragraph>
      <paragraph>
       Feature terms are defined by their signature: {a mathematical formula}Σ=〈S,F,≤,V〉. {a mathematical formula}S is a set of sort symbols, including ⊥ representing the most general sort (“any”). ≤ is an order relation inducing a single inheritance hierarchy in {a mathematical formula}S, where {a mathematical formula}s≤s′ means s is more general than or equal to {a mathematical formula}s′, for any {a mathematical formula}s,s′∈S (by definition ⊥ is more general than any {a mathematical formula}s∈S). {a mathematical formula}F is a set of feature symbols, and {a mathematical formula}V is a set of variable names. We write a feature term ψ as:{a mathematical formula} where ψ points to the root variable X (that we will note as {a mathematical formula}root(ψ)) of sort s, {a mathematical formula}X∈V, {a mathematical formula}s∈S, {a mathematical formula}fi∈F, and {a mathematical formula}Ψi is a set of variables {a mathematical formula}{X1,...,Xm} (which can recursively have features of their own). If {a mathematical formula}Ψi is a set with only one variable X, for simplicity, and when it does not cause confusion, we will ignore the fact that it is a set. When {a mathematical formula}Ψi is a set {a mathematical formula}{X1,...,Xm}, each element in the set must be different. An example of feature term appears in Fig. 1. It is a train (variable {a mathematical formula}X1) composed of two cars (variables {a mathematical formula}X2 and {a mathematical formula}X3). This term has 8 variables, and one set-valued feature (indicated by a dashed line): cars of {a mathematical formula}X1. The same train can be represented in term notation as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       To make a uniform description, constants (such as integers) are treated as variables of a particular sort. For each variable X in a term with a constant value k of sort s, we consider that X is a regular variable of a special sort {a mathematical formula}sk. For each different constant k, we create a new sort {a mathematical formula}sk of s. For example, if a variable X had an integer value 5, we would create a new sort {a mathematical formula}s5 (sub sort of integer), and consider that X is a regular variable of sort {a mathematical formula}s5. Thanks to this representation change, we can forget about constants and just consider all variables in the same way. The set of variables of a term ψ is {a mathematical formula}vars(ψ), the set of features of a variable X is {a mathematical formula}features(X), and {a mathematical formula}sort(X) is its sort. We will use the dot notation {a mathematical formula}X.f to denote the value of the feature f of variable X.
      </paragraph>
      <paragraph>
       Feature terms can be represented as directed labeled graphs. Given a variable X, its parents are the nodes connected with X by incoming links, and its children are the nodes connected with X by outgoing links.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Operations on feature terms
      </section-title>
      <paragraph>
       The basic operation between feature terms is subsumption, which equates to determining whether a term is more general than (or equal to) another one.
      </paragraph>
      <paragraph label="Definition 1">
       SubsumptionA feature term {a mathematical formula}ψ1subsumes another one {a mathematical formula}ψ2 ({a mathematical formula}ψ1⊑ψ2){sup:2} when there is a total mapping m: {a mathematical formula}vars(ψ1)→vars(ψ2) such that:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}root(ψ2)=m(root(ψ1))
       </list-item>
       <list-item label="•">
        for each {a mathematical formula}X∈vars(ψ1)
       </list-item>
      </list>
      <paragraph>
       Subsumption induces a partial order among feature terms, i.e. the pair {a mathematical formula}〈L,⊑〉 is a poset for a given set of terms {a mathematical formula}L containing the infimum ⊥ (the most general term) and the supremum ⊤ (a special term, which is considered more specific than any other term) with respect to the subsumption order. Notice that in feature terms, the symbol ⊥ is usually used both to denote the most general sort, and the most general term. This partial order forms the subsumption graph, that is a potentially infinite graph with one vertex per possible feature term that can be expressed (given a signature Σ). There is a directed edge between each pair of vertices in the subsumption graph such that one subsumes the other. It is important to note that while subsumption in feature terms is related to θ-subsumption (the mapping m above represents the variable substitution in θ-subsumption), there are two key differences: sorted variables, and semantics of sets (notice that two variables in a set cannot have the same mapping, whereas in θ-subsumption there is no restriction in the variable substitutions found for subsumption).
      </paragraph>
      <paragraph>
       Since feature terms can be represented as labeled graphs, it is natural to relate the problem of feature term subsumption to subgraph isomorphism. However, subsumption cannot be modeled as subgraph isomorphism because larger feature terms can subsume smaller feature terms while the corresponding graphs are not isomorphic. See for example the two terms shown in Fig. 2, where a term {a mathematical formula}ψ2 with three variables subsumes a term {a mathematical formula}ψ1 with two variables (mapping: {a mathematical formula}m(y1)=x1, {a mathematical formula}m(y2)=x2, {a mathematical formula}m(y3)=x1).
      </paragraph>
      <paragraph>
       Given the partial order introduced by subsumption, we can now define the two other basic operations on feature terms: unification and antiunification.
      </paragraph>
      <paragraph label="Definition 2">
       UnificationA unification of two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2, {a mathematical formula}ψ1⊔ψ2, is a term subsumed by both, such that no more general term exists that is also subsumed by both:{a mathematical formula}
      </paragraph>
      <paragraph>
       When two terms have contradictory information then they have no unification: this is equivalent to say that {a mathematical formula}ψ1⊔ψ2=⊤. Some authors use the word unification to refer to the operation, and the word unifier to refer to an actual term that satisfies the definition of unification. We will make no such distinction in this paper.
      </paragraph>
      <paragraph>
       For any two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 we define antiunification ({a mathematical formula}ψ1⊓ψ2) as the least general generalization operation [28]:
      </paragraph>
      <paragraph label="Definition 3">
       AntiunificationAn antiunification of two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2, {a mathematical formula}ψ1⊓ψ2, is a term that subsumes both, such that there is no more specific term that also subsumes both:{a mathematical formula}
      </paragraph>
      <paragraph>
       Both are operations over the subsumption graph: antiunification finds the most specific common “parent”; unification finds the most general common “descendant”. In feature terms, unification and anti unification might not be unique (many different terms might satisfy the condition of being a unification or an antiunification of two given terms). An example of such non-uniqueness is shown in Fig. 3, where two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 are shown with two different unifications, {a mathematical formula}ψ3 and {a mathematical formula}ψ4. Notice that {a mathematical formula}ψ3⋢ψ4 and {a mathematical formula}ψ4⋢ψ3, thus both terms satisfy the conditions of unification. Intuitively, imagine that f means “child”, s is “person” and {a mathematical formula}s′ is “male”, then, we can interpret the terms in Fig. 3 as:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ψ1 represents a man with two children, one of which has a child.
       </list-item>
       <list-item label="•">
        {a mathematical formula}ψ2 represents a man with two children, one of which is a male.
       </list-item>
      </list>
      <paragraph>
       Thus, there are two possible unifications that are maximally general: {a mathematical formula}ψ3 represents a man with two children, where one is male and has a child, and {a mathematical formula}ψ4 represents a man with two children, one of which is a male, and the other has a child. Notice that neither {a mathematical formula}ψ3 nor {a mathematical formula}ψ4 are most specific than the other, and thus they are both valid unifications of {a mathematical formula}ψ1 and {a mathematical formula}ψ2. This multiplicity of unifications and antiunifications happens because of the way feature terms deal with object identity (OI) [29]: in feature terms variables in a set can be seen as treated under OI, whereas variables outside sets are not.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Constraint satisfaction
      </section-title>
      <paragraph>
       A Constraint Satisfaction Problem (CSP) involves a finite set of variables, each taking a value in a finite discrete domain. Subsets of variables are related by constraints that specify permitted value tuples.
      </paragraph>
      <paragraph label="Definition 4">
       CSPA CSP is a tuple {a mathematical formula}(X,D,C), where {a mathematical formula}X={x1,…,xn} is a set of n variables; {a mathematical formula}D={D(x1),…,D(xn)} is a collection of finite discrete domains, {a mathematical formula}D(xi) is the set of {a mathematical formula}xi's possible values; {a mathematical formula}C is a set of constraints. Each constraint {a mathematical formula}c∈C is defined on the ordered set of variables {a mathematical formula}var(c) (its scope). Value tuples permitted by c are in {a mathematical formula}rel(c)⊆∏xj∈var(c)D(xj).
      </paragraph>
      <paragraph>
       A solution is an assignment of values to variables such that all constraints are satisfied. CSP solving is NP-complete (SAT, the first proved NP-complete problem [30], is a special case of CSP). In most cases, CSP instances are solved using specialized systematic search procedures.
      </paragraph>
      <paragraph>
       A symmetry in CSP is a mapping involving variables and values such that it transforms solutions into solutions [31]. When the mapping involves only variables (resp. values), we talk about variable symmetry (resp. value symmetry). For example, let us consider a graph coloring problem on a clique of 3 nodes {a mathematical formula}x1, {a mathematical formula}x2 and {a mathematical formula}x3, using three colors red, blue and green. Any permutation of variables is a variable symmetry, and any permutation of values is a value symmetry.
      </paragraph>
      <paragraph>
       Without symmetry breaking, symmetric states are treated as different states and thus systematic search has to visit all of them. However, if the symmetry connecting them is broken, only one of these states is visited. Since in some CSPs many symmetric states exist, symmetry breaking has reported very substantial efficiency gains when solving some CSP instances [32]. In this paper, we will see how symmetry breaking can also bring very significant performance gains in the context of feature terms.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Subsumption
     </section-title>
     <paragraph>
      This section presents a model of subsumption as a constraint satisfaction problem (Section 3.1), including a collection of symmetry constraints to increase the efficiency of the process (Section 3.2), and an empirical evaluation of this model (Section 3.3).
     </paragraph>
     <section label="3.1">
      <section-title>
       Subsumption as constraint satisfaction
      </section-title>
      <paragraph>
       Testing subsumption between feature terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2, as defined in Section 2.2, can be formalized as a CSP as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        CSP Variables: for each feature term variable {a mathematical formula}X∈vars(ψ1) there is a CSP variable x whose value represents the mapping {a mathematical formula}m(X). To avoid confusion between the two types of variables, feature term variables are written uppercase while CSP variables are written lowercase, and the same letter denotes corresponding variables (x is the CSP variable that represents feature term variable X).
       </list-item>
       <list-item label="2.">
        CSP Domains: the domain of each CSP variable is the set {a mathematical formula}vars(ψ2), except for the CSP variable of {a mathematical formula}root(ψ1), whose domain is the singleton {a mathematical formula}{root(ψ2)}. In the remainder of this paper we will often assume (for simplicity of notation) that CSP variables take integer values (corresponding to the indexes of the variables in {a mathematical formula}vars(ψ2)).
       </list-item>
       <list-item label="3.">
        CSP Constraints:
       </list-item>
      </list>
      <paragraph>
       Since {a mathematical formula}ψ1 and {a mathematical formula}ψ2 have a finite number of variables, there is a finite number of CSP variables (exactly {a mathematical formula}|vars(ψ1)|) and all their domains are finite (assuming that the CSP variable {a mathematical formula}x1 correspond to {a mathematical formula}root(ψ1), the domain of {a mathematical formula}x1 will be {a mathematical formula}{root(ψ2)}, and the common domain of the other CSP variables is the set {a mathematical formula}vars(ψ2)). If {a mathematical formula}n=max⁡(|vars(ψ1)|,|vars(ψ2)|) is the maximum number of variables, and m is the maximum number of features that a variable might have, the maximum number of constraints is:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}O(n) unary constraints on sorts (one per CSP variable),
       </list-item>
       <list-item label="•">
        {a mathematical formula}O(n2m) binary constraints on features (number of possible pairs of variables times the maximum number of features),
       </list-item>
       <list-item label="•">
        {a mathematical formula}O(nm)n-ary constraints on difference (number of variables, each having one all-different constraint, times the maximum number of features).
       </list-item>
      </list>
      <paragraph>
       Constraints on sorts can be tested using the ≤ relation amongst sorts; constraints on features and of difference are directly implemented since they just involve the equality and difference tests between variables. Moreover, notice that if the previous constraints are satisfied, the definition of subsumption is satisfied and vice versa. Therefore, the previous CSP problem is equivalent to subsumption in feature terms.
      </paragraph>
      <paragraph>
       In practice, n varies from a few variables in simple machine learning problems to up to hundreds or thousands for complex biomedical datasets. Most machine learning datasets do not have more than a few different feature labels, and thus m usually stays low. Moreover, in practice, the actual number of constraints is far below its maximum number as computed above.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Variable symmetries in feature terms for subsumption testing
      </section-title>
      <paragraph>
       Inspired by the idea of variable symmetry in CSP, we propose the following definition of variable symmetry for subsumption testing in feature terms. When testing subsumption between a term {a mathematical formula}ψ1 and another term {a mathematical formula}ψ2, a variable symmetry in feature term {a mathematical formula}ψ1 is a bijective mapping {a mathematical formula}σ:vars(ψ1)→vars(ψ1) such that given any mapping {a mathematical formula}m:vars(ψ1)→vars(ψ2), applying σ on term {a mathematical formula}ψ1 does not modify whether m satisfies the conditions of subsumption or not. If m was a mapping through which {a mathematical formula}ψ1 subsumed {a mathematical formula}ψ2, then after applying σ, the mapping still satisfies the subsumption conditions (Definition 1). Conversely, if m was a mapping through which {a mathematical formula}ψ1 did not subsume {a mathematical formula}ψ2, then after applying σ, the mapping still does not satisfy the subsumption conditions.
      </paragraph>
      <paragraph>
       Often, a basic form of variable symmetry, called interchangeable variables, appears in feature terms.{sup:3} Formally,
      </paragraph>
      <paragraph label="Definition 5">
       Interchangeable variablesTwo variables X and Y of {a mathematical formula}vars(ψ) are interchangeable for subsumption in ψ if when exchanging X and Y in ψ, the resulting term does not suffer any syntactic change with respect to the original ψ.
      </paragraph>
      <paragraph>
       If X and Y are interchangeable, neither of them can be the root of ψ. In addition they have to share the same sort, {a mathematical formula}sort(X)=sort(Y). We can see that two variables are interchangeable if and only if they have the same parents and the same children, as proved next.
      </paragraph>
      <paragraph label="Proposition 1">
       Two variables X and Y of{a mathematical formula}vars(ψ)are interchangeable in ψ if and only if they are of the same sort, with the same parents and the same children in ψ through the same features.
      </paragraph>
      <paragraph label="Proof">
       If X and Y are of the same sort, with the same parents and children through the same features, exchanging X and Y does not cause any syntactical change in ψ, so they are interchangeable.If X and Y are not of the same sort, exchanging them causes syntactical changes in ψ. Assuming they share the same sort, if they do not have the same parents or the same children, exchanging X and Y causes syntactical changes in ψ. The same happens when although having the same parents and children, they are connected to them by different features. □
      </paragraph>
      <paragraph>
       Fig. 4 shows an example of interchangeable variables in a feature term containing the chemical structure of methane. It happens that Br atoms are all equivalent, so they can be permuted freely without any change in the problem. The same happens with H atoms. Observe that a Br atom is not interchangeable with a H atom, because they are of a different sort. As a result, variables {a mathematical formula}X2 and {a mathematical formula}X3 are interchangeable, and also {a mathematical formula}X4 with {a mathematical formula}X5.
      </paragraph>
      <paragraph>
       It is well-known that symmetry exploitation can dramatically speed-up CSP solving because it causes substantial search reductions [32]. In the following we exploit the simplest variable symmetry in feature terms, variable interchangeability (Definition 5), inside the CSP model of feature term subsumption.
      </paragraph>
      <paragraph>
       Imagine that we want to test {a mathematical formula}ψ1⊑ψ2 and there are two interchangeable variables {a mathematical formula}X1 and {a mathematical formula}X2 in {a mathematical formula}ψ1. Interchangeability implies that they have the same parents through the same labels. Consequently, {a mathematical formula}m(X1)≠m(X2) (Section 2.1). Since {a mathematical formula}X1 and {a mathematical formula}X2 are interchangeable, any mapping m satisfying the subsumption conditions for {a mathematical formula}X1 will also be valid for {a mathematical formula}X2. Therefore, there is another mapping {a mathematical formula}m′ (symmetric to m) that is equal to m except that permutes the images of {a mathematical formula}X1 and {a mathematical formula}X2, {a mathematical formula}m′(X1)=m(X2) and {a mathematical formula}m′(X2)=m(X1). Since m and {a mathematical formula}m′ are symmetric mappings, we choose one of them by adding the symmetry breaking constraint {a mathematical formula}x1&lt;x2. In consequence, for any pair {a mathematical formula}X1,X2 of interchangeable variables in {a mathematical formula}ψ1 we add a symmetry breaking constraint {a mathematical formula}x1&lt;x2. Often we find subsets {a mathematical formula}X1,...,Xk of mutually interchangeable variables in {a mathematical formula}ψ1, which are also under the constraint {a mathematical formula}alldifferent(x1,...,xk). Therefore, this would add a quadratic number of symmetry breaking constraints:{a mathematical formula} However, as Puget pointed out in [33], many of these constraints are redundant and it is enough to add a linear number of symmetry breaking constraints:{a mathematical formula} to break all symmetries among interchangeable variables.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Experimental results
      </section-title>
      <paragraph>
       From our CSP model we developed a CP implementation using the JaCoP [23] and Cream [24] open-source constraint programming libraries for Java. We compared the time required to compute subsumption by a standard implementation of subsumption in feature terms [22] with (i) our CP implementation, and with (ii) that CP implementation enhanced with symmetry breaking constraints using the idea of interchangeable variables.{sup:4}
      </paragraph>
      <paragraph>
       We used three relational machine learning datasets as the source of terms: trains, predictive toxicology, and mutagenesis. The trains dataset was originally introduced by Larson and Michalski as a structured machine learning challenge [34]. Each instance represents a train (different instances have different number of cars, cargos and other properties). Since the size of each instance is different, this dataset cannot be represented using a standard propositional representation, and a relational machine learning representation is required. In the toxicology dataset [9], each instance represents the chemical structure (atoms and their links) of a chemical compound. This is a very complex dataset with some instances representing chemical compounds with a large number of atoms. The terms in this dataset contain between 5 and 138 variables each, and some of them have up to 76 variables belonging to some set. The mutagenesis dataset is also a biochemical dataset [35]. The terms in this dataset contain between 57 to 253 variables each. Some terms have up to 74 variables in some set (adding up the number of variables in all the sets in a given term), with some sets containing as many as 34 variables.{sup:5}
      </paragraph>
      <paragraph>
       The experimental procedure we followed to compare the three subsumption approaches is as follows. For each term in the trains and toxicology datasets we ran an operation known as disintegration[12], which breaks up a term into smaller terms and is useful for converting terms into a feature-vector representation. Disintegration is a computationally expensive operation that makes heavy use of subsumption, and thus was ideal for our purposes. Additionally, the terms that are generated during disintegration are always generalizations of specific examples from the datasets, and thus are similar to the generalizations handled by inductive machine learning algorithms. Notice that disintegration is only a way to obtain terms for experimentation. If the original terms in the datasets we used are tested for subsumption, none of them subsumes each other, and thus experiments would be meaningless.
      </paragraph>
      <paragraph>
       During disintegration, each time a call to subsumption was made, we recorded the pair of terms that were checked for subsumption. In order to get a varied sample of terms, we discarded pairs of terms for which the time taken to test subsumption using a standard implementation was too similar to any of the previously recorded pairs. We kept disintegrating terms from both datasets, until we recorded results for 8000 pairs of terms. Then, for those 8000 pairs, we evaluated the performance of all three approaches for subsumption.
      </paragraph>
      <paragraph>
       All the execution times reported in this paper were recorded by running the experiments on a computer with an Intel Core i5-2500 CPU running at 3.30 GHz, with 8 GB of RAM. All the algorithms presented in this paper were implemented in Java using the FTL library for feature terms.{sup:6}
      </paragraph>
      <paragraph>
       Fig. 5 shows the results of our experiments, where each dot represents one of the 8000 pairs of terms used for our evaluation. The horizontal axis (in a logarithmic scale), shows the time in seconds required by the traditional method, and the vertical axis (also in a logarithmic scale), shows the time required using CP. Dots that lie below the grey line correspond to problems where CP is faster.
      </paragraph>
      <paragraph>
       We observe that both CP implementations are much faster than the traditional approach because the square dots are below the grey line, achieving speed-ups of several orders of magnitude. Using a CP-based approach, all instances were solved in less than 0.1 seconds. Adding the time required to perform all the 8000 tests, the traditional method required 128665.60 seconds, and the CP implementations required between 27 to 28 seconds (no statistical significant difference was observed in this experiment between using or not using symmetry breaking constraints). This accounts for an improvement of 4 orders of magnitude with respect to the traditional method.
      </paragraph>
      <paragraph>
       Moreover, in order to determine the contribution of symmetry breaking constraints, we generated an additional set of 1000 pairs with terms from the mutagenesis dataset (with a significantly larger number of variables and requiring an unpractical amount of time to solve with a traditional approach). Fig. 6 shows the results only considering the CP-based approaches. Here, we can see that adding symmetry breaking constraints reduces the computation time up to 5 orders of magnitude for some terms with respect to using a CP approach without symmetry constraints. Adding the time required to perform all the 1000 tests, the CP method required 41486.50 seconds, and the CP implementation with symmetry breaking constraints required 19.69 seconds.
      </paragraph>
      <paragraph>
       Although benefits may vary in other datasets, these results clearly show the benefits of the CP approach with respect to the traditional method, as well as the extra benefits we obtain by adding symmetry breaking constraints to the CP implementation.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Antiunification
     </section-title>
     <paragraph>
      In the context of set-valued feature terms, a common approach to compute an antiunification is by performing search in a refinement space; we will refer to this approach as the refinement-based antiunification. Basically, using a downwards refinement operator (which given a term can generate a set of terms which are more specific than the original) in the context of a depth-first search algorithm that looks for the most specific term that still subsumes the input terms generates an antiunification [12]. This approach is defined formally in Section 4.1.{sup:7}
     </paragraph>
     <paragraph>
      Afterwards, the remainder of this section presents four main contributions to increasing the efficiency of computing an antiunification: 1) using the CSP model of subsumption presented in the previous section can greatly accelerate refinement-based antiunification, 2) a new bound on the size of an antiunification, which can reduce the search space, 3) we will propose a novel CSP-based algorithm for antiunification, which models the problem of computing an antiunification directly as a CSP problem, and 4) we present a series of theoretical results, that allow us to define a series of symmetries in the CSP formulation of antiunification, significantly reducing the computational cost.
     </paragraph>
     <section label="4.1">
      <section-title>
       Antiunification as search in the refinement space
      </section-title>
      <paragraph>
       The antiunification operation in set-valued feature terms can be computed by means of a search process and a refinement operator. A refinement operator ρ is a function that returns terms that are more specific (if ρ is a downward refinement operator) or more general (if ρ is a upward refinement operator) than the argument. For example, given a term ψ, and a downward refinement operator ρ, {a mathematical formula}ρ(ψ) is a set of terms such that {a mathematical formula}∀ψ′∈ρ(ψ), {a mathematical formula}ψ⊏ψ′. A refinement operator ρ defines a subgraph of the subsumption graph called the refinement graph. In the refinement graph each vertex is a term, and there is an edge between two terms when one is a refinement of the other. ρ is complete when for each pair of terms such that one subsumes the other, it is possible to construct a refinement path between them. Given a complete downward refinement operator for feature terms, an antiunification of two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 can be obtained by using the following iterative procedure:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}t=0, {a mathematical formula}ϕ0=⊥.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}∀ψ′∈ρ(ϕt) we have that {a mathematical formula}ψ′⋢ψ1∨ψ′⋢ψ2 then return {a mathematical formula}ϕt.
       </list-item>
       <list-item label="3.">
        Otherwise, {a mathematical formula}ϕt+1=ψ′∈ρ(ϕt)|ψ′⊑ψ1∧ψ′⊑ψ2 (if there are many {a mathematical formula}ψ′∈ρ(ψ) satisfying this condition, one is just chosen at random), and go back to 2.
       </list-item>
      </list>
      <paragraph>
       In other words, starting from the most general term (⊥), we keep refining it using the refinement operator ρ, until no more specific terms can be found that subsume both {a mathematical formula}ψ1 and {a mathematical formula}ψ2. In case we are interested on finding all the antiunifications instead of a single one, then we would need a slower branch-and-bound systematic-search algorithm. Notice that subsumption is used in the previous procedure, and thus it can be accelerated by using the subsumption CSP model of Section 3.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Antiunification bound
      </section-title>
      <paragraph>
       One of the big problems of the previous algorithm is that the order in which refinements are selected must be taken into account, otherwise, the algorithm might be stuck in infinite loops. This is because the search space that the algorithm explores is unbounded: given an arbitrary feature term ψ, there might be an infinite set of terms that are more general than ψ. This can be seen considering the example shown in Fig. 2, where a term that consists of a chain of a finite number of variables subsumes a term that consists of a loop with two variables. However, it is possible to find a finite search space for the previous algorithm to ensure termination. Let us start by introducing an operation with which it is possible (under certain conditions) to reduce the number of variables of a term {a mathematical formula}ψ1 that subsumes another term {a mathematical formula}ψ2, while still not making the new term more general than {a mathematical formula}ψ1 and still subsuming {a mathematical formula}ψ2. Then, we will show that (thanks to that operation) we can provide a finite bound in the search space, ensuring that there will be at least one antiunification in this space.
      </paragraph>
      <paragraph label="Definition 6">
       Subsumption-preserving Variable EqualityGiven two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 such that {a mathematical formula}ψ1⊑ψ2, and given two variables {a mathematical formula}X,Y∈vars(ψ1) such that {a mathematical formula}sort(Y)≤sort(X), we define the new term {a mathematical formula}ve(ψ1,Y←X) as the term resulting by substituting every appearance of Y by X, and we call this operation the Subsumption-preserving Variable Equality.
      </paragraph>
      <paragraph label="Proposition 2">
       Let{a mathematical formula}ψ1,{a mathematical formula}ψ2be two terms such that{a mathematical formula}ψ1⊑ψ2by mapping m. If there are{a mathematical formula}X,Y∈vars(ψ1)such that{a mathematical formula}m(X)=m(Y)and{a mathematical formula}sort(Y)≤sort(X), then the term{a mathematical formula}ψ1′=ve(ψ1,Y←X)(resulting from applying subsumption-preserving variable equality), which has at least one less variable than{a mathematical formula}ψ1also subsumes{a mathematical formula}ψ2.
      </paragraph>
      <paragraph label="Proof">
       First, {a mathematical formula}ψ1′ is a legal term, i.e. {a mathematical formula}ψ1′ does not have a repeated element in a set. Since {a mathematical formula}m(X)=m(Y) we know, by Definition 1, that X and Y are not siblings, so {a mathematical formula}ψ1′ will not have a repeated element in a set.Second, {a mathematical formula}ψ1′ verifies the subsumption conditions under mapping m. The sort conditions among variables hold by definition. The conditions over the values of the features also hold: for each {a mathematical formula}Z∈vars(ψ1′) and for each {a mathematical formula}f∈features(Z), we still have that for each {a mathematical formula}R∈Z.f there is a {a mathematical formula}S∈m(Z).f such that {a mathematical formula}m(R)=S (if Z has no X as value of any of its features, this condition trivially holds; otherwise, since {a mathematical formula}m(X)=m(Y) replacing Y by X has no effect after the mapping m).Additionally, since we know that X and Y were not siblings in ψ, the condition that each two variables in a set in {a mathematical formula}ψ1′ have to have a different mapping is also unaffected for these variables. □
      </paragraph>
      <paragraph>
       Using subsumption-preserving variable equality, if there are two variables such that {a mathematical formula}m(X)=m(Y) we can construct a smaller term {a mathematical formula}ψ1′ that subsumes {a mathematical formula}ψ2. The new term {a mathematical formula}ψ1′ is never more general than {a mathematical formula}ψ1 because, even if it might lose all the variables that were hanging from Y, it has an additional restriction, {a mathematical formula}X=Y (and thus it is either more specific or incomparable to {a mathematical formula}ψ1).
      </paragraph>
      <paragraph label="Proposition 3">
       Assume that ψ subsumes{a mathematical formula}ψ1and{a mathematical formula}ψ2with two mappings{a mathematical formula}m1and{a mathematical formula}m2respectively. If we have{a mathematical formula}X,Y∈vars(ψ)such that{a mathematical formula}m1(X)=m1(Y),{a mathematical formula}m2(X)=m2(Y)and{a mathematical formula}sort(Y)≤sort(X), then{a mathematical formula}ψ′=ve(ψ,Y←X)resulting from substituting all the appearances of Y by X in ψ also subsumes{a mathematical formula}ψ1and{a mathematical formula}ψ2.
      </paragraph>
      <paragraph label="Proof">
       {a mathematical formula}ψ′ subsumes {a mathematical formula}ψ1 by Proposition 2; {a mathematical formula}ψ′ subsumes {a mathematical formula}ψ2 by Proposition 2. □
      </paragraph>
      <paragraph>
       As a consequence of the previous proposition, we can now prove that there must exist at least one antiunification that has at most {a mathematical formula}|vars(ψ1)|×|vars(ψ2)| variables. This is important, since this is a finite bound, which means that the search space for antiunifications is also finite.
      </paragraph>
      <paragraph label="Corollary 1">
       There is at least one antiunification such that{a mathematical formula}|vars(ψ1⊓ψ2)|≤|vars(ψ1)|×|vars(ψ2)|.
      </paragraph>
      <paragraph label="Proof">
       First, let us start by noting that there is always at least one antiunification for any two given terms. This is because the term ⊥ (with a single variable, of the most general sort) subsumes any other term. Now, let {a mathematical formula}ψ1 and {a mathematical formula}ψ2 be terms and {a mathematical formula}r=|vars(ψ1)|, {a mathematical formula}s=|vars(ψ2)|. Let's assume that we found an antiunification term ψ such that {a mathematical formula}ψ⊑ψ1 with a mapping {a mathematical formula}m1, {a mathematical formula}ψ⊑ψ2 with a mapping {a mathematical formula}m2, and {a mathematical formula}n=|vars(ψ)|, where {a mathematical formula}n&gt;r×s. Since there are only {a mathematical formula}r×s possible different mappings that a variable {a mathematical formula}Z∈vars(ψ) can have, there must be two variables in {a mathematical formula}vars(ψ) which have a repeated mapping both in {a mathematical formula}m1 and {a mathematical formula}m2. In that case, Proposition 3 applies, so we can find another term more specific or incomparable to ψ subsuming both {a mathematical formula}ψ1 and {a mathematical formula}ψ2 with one less variable. Therefore, if there is an antiunification with more than {a mathematical formula}|vars(ψ1)|×|vars(ψ2)| variables, then we can always construct one with less than {a mathematical formula}|vars(ψ1)|×|vars(ψ2)| variables by repeated application of Proposition 3. □
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Antiunification as constraint satisfaction
      </section-title>
      <paragraph>
       Based on Corollary 1, we provide a direct formulation of the antiunification operation as a CSP. In this formulation, we define a set of restrictions that must be satisfied by any antiunification, then find all the possible terms which satisfy such restrictions (all the solutions to the CSP). We then use subsumption tests to find one antiunification amongst those candidate solutions.
      </paragraph>
      <paragraph>
       The idea behind our model is what we call the antiunification-matrix. Given two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2, which have n and m variables respectively, we know that there is at least one antiunification with at most {a mathematical formula}n×m variables, which subsumes {a mathematical formula}ψ1 with a mapping {a mathematical formula}m1 and {a mathematical formula}ψ2 with a mapping {a mathematical formula}m2. The antiunification-matrix is a binary matrix M with n rows and m columns, like the one shown in Fig. 7, where each row corresponds to a different variable from {a mathematical formula}ψ1 (from {a mathematical formula}X1 to {a mathematical formula}Xn) and each column to a different variable from {a mathematical formula}ψ2 (from {a mathematical formula}Y1 to {a mathematical formula}Ym). Each cell in the matrix set to 1 represents a different variable in the antiunification being computed, where {a mathematical formula}Zi,j represents the antiunification variable in row i and column j. Moreover, {a mathematical formula}m1(Zi,j)=Xi and {a mathematical formula}m2(Zi,j)=Yj. In other words, all the antiunification variables that are mapped to a variable {a mathematical formula}Xi according to {a mathematical formula}m1 are located in the row corresponding to {a mathematical formula}Xi (same for columns with respect to variables {a mathematical formula}Yj). Therefore, the antiunification matrix captures both the variables of one antiunification, as well as the mappings {a mathematical formula}m1 and {a mathematical formula}m2. By Proposition 3, we know that there is at least one antiunification ψ for which not two variables of ψ share the same cell, therefore, there is at least one antiunification representable as a combination of zeroes and ones in the antiunification matrix.
      </paragraph>
      <paragraph label="Definition 7">
       Antiunification matrix associated termGiven an instantiation of the antiunification matrix M, such that {a mathematical formula}M1,1=1, the associated term {a mathematical formula}ϕM is defined as follows. Each cell {a mathematical formula}(i,j) in the matrix M set to 1 corresponds to a different variable {a mathematical formula}Zi,j in {a mathematical formula}ϕM. This variable {a mathematical formula}Zi,j is constructed as follows:
      </paragraph>
      <list>
       <list-item label="•">
        The sort of {a mathematical formula}Zi,j is the most specific sort {a mathematical formula}s∈S such that {a mathematical formula}s≤sort(Xi) and {a mathematical formula}s≤sort(Yj).
       </list-item>
       <list-item label="•">
        For each feature {a mathematical formula}f∈F, {a mathematical formula}Zi,j.f={Zk,ℓ|Xk∈Xi.f∧Yℓ∈Yj.f}.
       </list-item>
      </list>
      <paragraph>
       Notice that any term {a mathematical formula}ϕM defined in this way always subsumes {a mathematical formula}ψ1 and {a mathematical formula}ψ2 with the mappings {a mathematical formula}m1(Zi,j)=Xi and {a mathematical formula}m2(Zi,j)=Yj. Moreover, if we set the sort of any variable in ϕ to a more specific value or we add any additional feature to ϕ, then subsumption would not hold using those mappings. Finally, any term which is an antiunification of at most {a mathematical formula}n×m variables can be represented by a unique instantiation of the matrix.
      </paragraph>
      <paragraph>
       To find an antiunification, we define the following CSP problem:
      </paragraph>
      <list>
       <list-item label="•">
        CSP Variables: for each cell {a mathematical formula}(i,j) in the antiunification matrix there is a CSP variable {a mathematical formula}zi,j; in total there are {a mathematical formula}n×m CSP variables.
       </list-item>
       <list-item label="•">
        CSP Domains: the domain of each CSP variable is {a mathematical formula}{0,1}, except from {a mathematical formula}z1,1 whose domain is {1} (since, by convention, the root variables of the two terms are in the first row and column, respectively).
       </list-item>
       <list-item label="•">
        CSP Constraints:
       </list-item>
      </list>
      <paragraph>
       Constraint 1 implements the above description of the antiunification matrix; constraint 2 sets up the requirement that any legal term nodes must be reachable from the root; constraint 3 is justified by requirements of sets in subsumption; constraint 4 comes from the fact that ψ must subsume {a mathematical formula}ψ1 and {a mathematical formula}ψ2, but if {a mathematical formula}|Zi,j.f|&lt;min⁡(|Xi.f|,|Yj.f|) then ψ is not the most specific term subsuming {a mathematical formula}ψ1 and {a mathematical formula}ψ2, and thus will not be an antiunification.
      </paragraph>
      <paragraph>
       Each solution to the above CSP problem corresponds to a term ψ, which subsumes both {a mathematical formula}ψ1 and {a mathematical formula}ψ2. Moreover, when there are sets in either {a mathematical formula}ψ1 or {a mathematical formula}ψ2, there might be multiple solutions, not all of them being antiunifications (since our CSP definition does not capture the fact that an antiunification must be a “most specific” term that subsumes both {a mathematical formula}ψ1 and {a mathematical formula}ψ2). In order to ensure finding an antiunification, all the solutions are generated, and one of the most specific ones is selected using subsumption tests.
      </paragraph>
      <paragraph>
       Fig. 7 shows an illustration of this process, with two terms: {a mathematical formula}ψ1, with 4 variables, and {a mathematical formula}ψ2 with 5 variables. This results in an antiunification matrix with 4 rows and 5 columns. Fig. 7 shows one possible solution to the CSP (there are 5 different instantiations of the matrix which are a solution to the CSP in this example), and the right hand side shows the resulting antiunification. The shaded cells in Fig. 7 represent unreachable cells, and thus those are set to 0 directly, before starting to solve the CSP. Notice that thanks to this “reachable” concept most variables in the matrix can be directly set to zero in most cases, making the CSP faster to solve.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Symmetries in the antiunification matrix
      </section-title>
      <paragraph>
       As shown in our previous work [25], the previous formulation can result in significant gains in certain cases, but the standard refinement-based search procedure described in Section 4.1 still works faster for other terms (as we will show below, in Fig. 8). In this section, we will present a series of theoretical results allowing us to define symmetries in the antiunification matrix, and obtain further time savings.
      </paragraph>
      <paragraph label="Definition 8">
       Interchangeable rowsTwo rows, i and j, in the antiunification matrix for antiunifying two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 are interchangeable, if the variables corresponding to them, {a mathematical formula}Xi∈vars(ψ1) and {a mathematical formula}Xj∈vars(ψ1) are interchangeable.
      </paragraph>
      <paragraph>
       This definition creates the first symmetry in the antiunification matrix:
      </paragraph>
      <paragraph label="Proposition 4">
       Given two terms,{a mathematical formula}ψ1and{a mathematical formula}ψ2, such that there are two variables,{a mathematical formula}Xi∈vars(ψ1)and{a mathematical formula}Xj∈vars(ψ1)that are interchangeable according toDefinition 5, and given one instantiation of the antiunification matrix M for computing an antiunification of{a mathematical formula}ψ1and{a mathematical formula}ψ2, it follows that:{a mathematical formula}Mi↔j, representing the result of swapping rows i and j in the matrix M, is also a valid instantiation of the antiunification matrix, and also that{a mathematical formula}term(M)and{a mathematical formula}term(Mi↔j)are equivalents, i.e. both M and{a mathematical formula}Mi↔jgenerate the same term.
      </paragraph>
      <paragraph label="Proof">
       By Proposition 1, {a mathematical formula}Xi and {a mathematical formula}Xj have the same sort, same parents and same children through the same features. Since the process for generating a term from a matrix instantiation M, only depends on those three aspects (sorts, parents and children), the resulting terms must be identical. □
      </paragraph>
      <paragraph>
       Analogously, we can define interchangeable columns, with the analogous property, but for interchangeable variables of the second term, {a mathematical formula}ψ2.
      </paragraph>
      <paragraph label="Definition 9">
       Interchangeable cellsTwo cells {a mathematical formula}(i,j), {a mathematical formula}(k,ℓ), corresponding to variables {a mathematical formula}Zi,j and {a mathematical formula}Zk,ℓ in the antiunification matrix for antiunifying two terms {a mathematical formula}ψ1 and {a mathematical formula}ψ2 are interchangeable if: {a mathematical formula}sort(Zi,j)=sort(Zk,ℓ), for each {a mathematical formula}f∈F, {a mathematical formula}Zi.j.f=Zk,ℓ.f, and {a mathematical formula}Zi.j∈Zp,q.f if {a mathematical formula}Zk,ℓ∈Zp,q.f. In other words, {a mathematical formula}Zi,j and {a mathematical formula}Zk,ℓ have the same sort, same children and same parents.
      </paragraph>
      <paragraph label="Proposition 5">
       If two columns, i and j, in the antiunification matrix for antiunifying two terms{a mathematical formula}ψ1and{a mathematical formula}ψ2, are interchangeable, each cell{a mathematical formula}k,iin column i is interchangeable with cell{a mathematical formula}k,jin column j.
      </paragraph>
      <paragraph label="Proof">
       Since columns i and j are interchangeable, by Proposition 1 we know that variables {a mathematical formula}Yi∈vars(ψ2) and {a mathematical formula}Yj∈vars(ψ2) have the same sort, the same children and the same parents, by the same features. Therefore, given a variable {a mathematical formula}Xk∈vars(ψ1), {a mathematical formula}Zk,i and {a mathematical formula}Zk,j must also have the same sort, same children and same parents, by the same features, thus satisfying Definition 9 of interchangeable cells. □
      </paragraph>
      <paragraph>
       Moreover, the opposite is not true. If two cells, {a mathematical formula}(k,i) and {a mathematical formula}(k,j) are interchangeable, the two columns, i and j do not necessarily need to be interchangeable. This is because even if {a mathematical formula}(k,i) and {a mathematical formula}(k,j) are interchangeable, there might be other cells in the same columns that are not interchangeable, thus rendering the whole column not interchangeable.
      </paragraph>
      <paragraph>
       From the previous definitions, the following constraints and simplifications over the antiunification matrix can be introduced:
      </paragraph>
      <list>
       <list-item label="•">
        For each pair of interchangeable rows i, j, where {a mathematical formula}i&lt;j, a non-strict lexicographical constraint in added: {a mathematical formula}LEX(〈zi,1,...,zi,m〉,〈zj,1,...,zj,m〉) (same for interchangeable columns). More formally, this constraint is satisfied if one of the following two conditions is satisfied (recall that {a mathematical formula}zi,j is the CSP variable associated with the feature term variable {a mathematical formula}Zi,j):
       </list-item>
       <list-item label="•">
        For each maximal group of variables {a mathematical formula}Z={Z1,...,Zi} such that all of them are interchangeable, we can replace all of those variables in the antiunification matrix by a single variable {a mathematical formula}Z′ that can take values {a mathematical formula}{0,...,i}. That is, we don't care which specific set of variables in {a mathematical formula}Z has value 1, we just care about how many of them have value 1, which achieves a very significant reduction of the search space. Moreover, if {a mathematical formula}Z1,1∈Z, we know that {a mathematical formula}Z′ cannot take the value 0.
       </list-item>
      </list>
      <paragraph>
       Moreover, the search space can be reduced even further.
      </paragraph>
      <paragraph label="Definition 10">
       DominationA cell {a mathematical formula}Zi,jdominates another cell {a mathematical formula}Zk,ℓ if {a mathematical formula}Zi,j has:
      </paragraph>
      <list>
       <list-item label="1.">
        a more specific (or equal) sort than {a mathematical formula}Zk,ℓ,
       </list-item>
       <list-item label="2.">
        a superset (or equal) of the parents than {a mathematical formula}Zk,ℓ,
       </list-item>
       <list-item label="3.">
        a superset (or equal) of the children than {a mathematical formula}Zk,ℓ by each feature f.
       </list-item>
      </list>
      <paragraph>
       Now consider {a mathematical formula}Zi,jf as the set of variables in the antiunification matrix that represent an antiunification of {a mathematical formula}Xi.f and {a mathematical formula}Yj.f, which might be a set. For example, in Fig. 7, {a mathematical formula}Z1,1f={Z2,2,Z3,2}. If there is any set of variables in {a mathematical formula}Zi,jf which, if set to 1, are going to result necessarily in a set that is more specific or equal than the set resulting from any other set of variables in {a mathematical formula}Zi,jf, then, we know that any other instantiation of variables will result in a less specific (or equal) set, and thus there is no need to search that subspace. This is captured in the following proposition.
      </paragraph>
      <paragraph label="Proposition 6">
       Let{a mathematical formula}Xi∈vars(ψ1),{a mathematical formula}Yj∈vars(ψ2)and{a mathematical formula}f∈features(Xi)∩features(Yj). Let{a mathematical formula}Zi,jf={Zk,ℓ|Xk∈Xi.f∧Yℓ∈Yj.f}be the set of variables in the antiunification matrix that correspond to the children of{a mathematical formula}Xiand{a mathematical formula}Yjvia the feature f. If there is a subset{a mathematical formula}Z⊆Zi,jf, such that{a mathematical formula}|Z|≤min⁡(|Xi.f|,|Yj.f|)and such that all variables inZdominate all the other variables in{a mathematical formula}Zi,jfthen, if{a mathematical formula}Zi,j=1, we know that all the variables inZcan also be set to 1.
      </paragraph>
      <paragraph label="Proof">
       Given that each variable in Z dominates any other variable in {a mathematical formula}Zi,jf, that is not in Z, the term resulting from a matrix M where all the variables in Z are set to 1 will always be subsumed by the term resulting from a matrix {a mathematical formula}M′, where any set of variables in Z has been set to 0 in favor of variable outside of Z. This is because, given that the variables in Z dominate the variables outside of Z, each time one variable {a mathematical formula}Z∈Z is set to 0 in favor of a variable {a mathematical formula}Z′ outside of Z, the sort of {a mathematical formula}Z′ can only be the same or more general, {a mathematical formula}Z′ can only have a subset of the parents, and a subset of the children of Z. Therefore, it is always possible to construct a subsumption mapping m from the term resulting from {a mathematical formula}M′ to the term resulting from M by the definition of subsumption. Therefore, since we are looking for a term that is most specific (an antiunification), there is no need to consider {a mathematical formula}M′. □
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Experimental results
      </section-title>
      <paragraph>
       In order to evaluate our model, we compared the time required to compute an antiunification by (i) a standard implementation using search in the refinement space (standard) as reported in Section 4.1, (ii) by a standard implementation using search in the refinement space but using our CSP model of subsumption using symmetry breaking constraints (standard+CP-based-subsumption), and (iii) our direct CSP model of antiunification (CP+symmetry-breaking-constraints) as reported in Sections 4.3 and 4.4 (including interchangeable rows and columns, interchangeable cells and domination). We do not include results of the CSP model without symmetry breaking constraints, since results were about one order of magnitude slower, and were unpractical to execute in some of the feature terms used in our evaluation. Using feature terms from the three relational datasets described before, we computed an antiunification of 15,000 randomly chosen pairs of those terms.
      </paragraph>
      <paragraph>
       Fig. 8 shows the results of our experiments, where each dot represents one of the 15,000 pairs of terms used for our evaluation. The horizontal axis (in a logarithmic scale) shows the time in seconds required to compute an antiunification by the standard method, and the vertical axis (also in a logarithmic scale), shows the time in seconds required to compute an antiunification using the CP-based implementations. Points that lie below the grey line correspond to problems where the CP-based approaches are faster. We can clearly see that the standard+CP-based-subsumption approach performs identically to the standard approach for problems where the traditional approach requires less than 10 seconds (where refinement and not subsumption is the bottleneck), but clearly outperforms it when subsumption starts becoming the bottleneck. The direct CP+symmetry-breaking-constraints approach has a very large variance for terms for which search takes a small amount of time, but clearly outperforms the standard approach for the most complex terms.
      </paragraph>
      <paragraph>
       Adding up the computation time required to compute an antiunification for the 15,000 pairs used in our experiments, the standard approach required 56609.76 seconds, the standard+CP-based-subsumption approach required 5916.72 seconds, and the CP+symmetry-breaking-constraints approach required 5964.415 seconds. Therefore, both the CP-based approaches outperformed the traditional standard approach by one order of magnitude overall. Moreover, if we consider only the 50 terms for which the standard approach required more time, the numbers are: 52,034.43, 3425.67 and 2756.15 respectively. Therefore, we can see that as the subsumption tests get more time consuming, the CP+symmetry-breaking-constraints approach starts having a clear advantage.
      </paragraph>
      <paragraph>
       Therefore, for simpler problems, the standard+CP-based-subsumption approach seems to be the fastest one, and for more complex problems, the CP+symmetry-breaking-constraints approach presented in this section is preferable.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Unification
     </section-title>
     <paragraph>
      The standard approach to unification is the Robinson algorithm [38], a recursive algorithm that tries to unify the root variables of two terms, if they unify, then it recursively tries to unify its children variables, and so on (an implementation for feature terms without set-values was presented by Aıt-Kaci [39]). The only particularity for the set-valued feature terms case is that, because of sets, such an algorithm is non deterministic and might return many different solutions, some of which might be unifications and some might not. Therefore, after applying Robinson's algorithm in set-valued feature terms, we need to perform a filtering post-process where we eliminate all those terms that are not unifications from the set of results (using subsumption tests). Notice that in the case of set-valued feature terms, there might be more than one unification (see the example in Fig. 3), so more than one term might survive this filtering.
     </paragraph>
     <paragraph>
      By using the CSP model of subsumption of Section 3, the filtering post-process of unification can already be accelerated. Moreover, in this section we will present a novel CSP-based algorithm for unification in set-valued feature terms, following a similar idea as the one proposed for antiunification in Section 4.
     </paragraph>
     <section label="5.1">
      <section-title>
       Unification as constraint satisfaction
      </section-title>
      <paragraph>
       We provide a direct formulation of the unification operation between two feature terms as a CSP. In this formulation, we define a set of restrictions that must be satisfied for sure by any unification, then find all the possible terms which satisfy such restrictions (all the solutions to the CSP), and then use subsumption tests to find one unification amongst those candidate solutions. Let us start by providing some bounds in the number of variables of a unification term.
      </paragraph>
      <paragraph label="Proposition 7">
       Any unification of two terms{a mathematical formula}ψ1and{a mathematical formula}ψ2, with n and m variables respectively, has at most{a mathematical formula}n+m−1variables.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}ψ1, {a mathematical formula}ψ2 and ψ be terms with n, m and k variables, such that {a mathematical formula}ψ1⊑ψ and {a mathematical formula}ψ2⊑ψ. Roots of {a mathematical formula}ψ1 and {a mathematical formula}ψ2 must map {a mathematical formula}root(ψ), so there are at most {a mathematical formula}(n−1)+(m−1) elements of {a mathematical formula}vars(ψ) which would receive any mapping from {a mathematical formula}vars(ψ1) or {a mathematical formula}vars(ψ2). Now we build {a mathematical formula}ψ′ only with the variables from ψ that receive any mapping from {a mathematical formula}vars(ψ1) and {a mathematical formula}vars(ψ2). Notice that, {a mathematical formula}ψ′ is subsumed by {a mathematical formula}ψ1 and {a mathematical formula}ψ2, and also that {a mathematical formula}ψ′ subsumes ψ, so ψ cannot be a unification.
      </paragraph>
      <paragraph>
       We model the unification operation between two terms using a binary unification matrix M of size {a mathematical formula}(n+1)×(m+1), that encodes the mappings {a mathematical formula}m1 and {a mathematical formula}m2 as follows: The top-left {a mathematical formula}n×m part of the matrix forms the main matrix, having a row per each variable in {a mathematical formula}ψ1 and a column for each variable in {a mathematical formula}ψ2 (as illustrated in Fig. 9). The right most column contains one special cell for each variable in {a mathematical formula}ψ1, and the bottom row contains one special cell for each variable in {a mathematical formula}ψ2, the bottom-right cell of the matrix is unused. If there is a 1 in the position {a mathematical formula}Mi,j, it means that the variable {a mathematical formula}Xi of {a mathematical formula}ψ1, and the variable {a mathematical formula}Yj of {a mathematical formula}ψ2 are mapped to the same variable {a mathematical formula}Zi,j in the unification being computed. If there is at least one 1 in row i of the main matrix, then the special variable for {a mathematical formula}Xi is 0, and if the special variable for {a mathematical formula}Xi is 1, then the whole row i in the main matrix must contain all zeroes (same for columns). A 1 in the special variable corresponding to {a mathematical formula}Xi, means that {a mathematical formula}Xi cannot be unified to any variable in {a mathematical formula}ψ2, and is mapped to a variable Z such that no variable in {a mathematical formula}ψ2 is mapped to Z (same for columns). Notice that if there are two positions of the main matrix, {a mathematical formula}Mi,j and {a mathematical formula}Mi,k, which are both 1, then that means that {a mathematical formula}m(Yj)=m(Yk)=m(Xi) (same for columns).
      </paragraph>
      <paragraph label="Definition 11">
       Unification matrix associated termGiven an instantiation of the unification matrix M, such that {a mathematical formula}M1,1=1, the associated term {a mathematical formula}ϕM is defined as follows. Each cell {a mathematical formula}(i,j) in the matrix M set to 1 corresponds to a variable {a mathematical formula}Zi,j in {a mathematical formula}ϕM (if there are more than one 1 in a row or column of the main matrix, then all the variables for those positions would actually be the same variable). This variable {a mathematical formula}Zi,j is constructed as follows:
      </paragraph>
      <list>
       <list-item label="•">
        The sort of {a mathematical formula}Zi,j is the most specific sort {a mathematical formula}s∈S of all the variables from {a mathematical formula}ψ1 and {a mathematical formula}ψ2 that map to it.
       </list-item>
       <list-item label="•">
        For each two variables {a mathematical formula}Zi,j and {a mathematical formula}Zk,ℓ in {a mathematical formula}ϕM, and for each feature f, {a mathematical formula}Zi,j.f=Zk,ℓ if there are two variables in {a mathematical formula}ψ1 such that {a mathematical formula}Xi.f=Xk, {a mathematical formula}m(Xi)=Zi,j, and {a mathematical formula}m(Xk)=Zk,ℓ, or if there are two variables in {a mathematical formula}ψ2 satisfying the same condition.
       </list-item>
      </list>
      <paragraph>
       As in the antiunification case, a way to find an unification would be to generate all the different instantiations of this matrix, generate their corresponding terms, and choose the most general one. However, this involves generating a very large number of terms. By imposing a set of constraints on the possible instantiations of these matrices, we can drastically reduce the number of instantiations we need to test. With this aim, we define the following CSP:
      </paragraph>
      <list>
       <list-item label="•">
        CSP Variables: for each {a mathematical formula}Mi,j (except for the bottom-right position) there is a binary CSP variable {a mathematical formula}zi,j; in total there are {a mathematical formula}(n+1)×(m+1)−1 CSP variables.
       </list-item>
       <list-item label="•">
        CSP Domains: the domain of each CSP variable is {a mathematical formula}{0,1}, except from {a mathematical formula}z1,1 whose domain is {1}.
       </list-item>
       <list-item label="•">
        CSP Constraints:
       </list-item>
      </list>
      <paragraph>
       Constraint 1 ensures sort consistency; constraints 2 and 3 set up the requirement that variables of any legal term must be reachable from the root; constraints 4, 5 and 6 ensure that the main matrix and the special cells are exclusive (each variable can only have ones in either their main matrix column or row or in their special cell, but not in both places); constraint 7 ensures transitive coherence (if the mapping of a variable {a mathematical formula}Xi is the same as another variable {a mathematical formula}Yj, the mapping of {a mathematical formula}Xi is also the same as another variable {a mathematical formula}Yℓ, then we also know that the mapping of {a mathematical formula}Yj is the same as the one for the variable {a mathematical formula}Yℓ); finally, constraint 8 ensures that two variables in a set are not mapped to the same variable in the unification being computed.
      </paragraph>
      <paragraph>
       Moreover, we define the cost of a solution as the number of ones in the special cells. A solution ψ with higher cost than another solution {a mathematical formula}ψ′ will never subsume {a mathematical formula}ψ′ (Proposition 8). When looking for unifications, we are only interested in finding all the solutions with minimum cost.
      </paragraph>
      <paragraph label="Proposition 8">
       Given two solutions to the previous CSP problem, represented as two different instantiations of the unification matrix{a mathematical formula}M1and{a mathematical formula}M2that only differ in that for some{a mathematical formula}1≤i≤nand{a mathematical formula}1≤j≤m,{a mathematical formula}Mi,j1=1,{a mathematical formula}Mi,m+11=0,{a mathematical formula}Mn+1,j1=0, and{a mathematical formula}Mi,j2=0,{a mathematical formula}Mi,m+12=1,{a mathematical formula}Mn+1,j2=1, the unification resulting from{a mathematical formula}M1is more general or incomparable to the one resulting from{a mathematical formula}M2.
      </paragraph>
      <paragraph label="Proof">
       This follows from the fact that according to feature term subsumption, a set of {a mathematical formula}n+1 variables can never subsume a set of n variables. Since the only difference between {a mathematical formula}ϕM1 and {a mathematical formula}ϕM2 is that {a mathematical formula}ϕM2 has an additional variable, making one of its sets larger. Since the rest of {a mathematical formula}ϕM2 is identical to {a mathematical formula}ϕM1, it will not be possible to find a mapping m via which {a mathematical formula}ϕM2 subsumes {a mathematical formula}ϕM1. □
      </paragraph>
      <paragraph>
       Fig. 9 shows an illustration of this process, with two terms, {a mathematical formula}ψ1, with 4 variables, and {a mathematical formula}ψ2 with 5 variables. This results in a unification matrix with 5 rows and 6 columns. Fig. 9 shows one possible solution (there are 2 different instantiations of the matrix which are solutions with minimum cost 1) to the CSP, and the right hand side shows the resulting unification.
      </paragraph>
      <paragraph>
       It is possible to define row and column symmetries in the unification matrix (in an analogous way to the way they are defined for the antiunification matrix). However, the exploitation of these symmetries did not result in any measurable benefits in our experiments, returning results indistinguishable from the CP approach without symmetries, and thus we don't report results using symmetries for unification in this paper. The main reason is that, in the case of unification, the cost is dominated by the filtering step (where all the solutions to the CSP problem are filtered using subsumption). In our experiments, row and column symmetry constraints did not significantly reduce this set of solutions, since the result of Proposition 8 achieved a much stronger filtering of solutions than row and column symmetry constraints. Therefore, unification did not benefit from this type of symmetry breaking constraints.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Experimental results
      </section-title>
      <paragraph>
       In order to evaluate our model, we compared the time required to compute a unification by a standard Robinson implementation (standard), by a standard Robinson implementation but using our CP model of subsumption internally (standard+CP-based-subsumption), and our CP model of unification (CP) as reported in Section 5.1. We tested 30,000 pairs of feature terms using the examples in the same relational datasets as before to evaluate these approaches.
      </paragraph>
      <paragraph>
       Fig. 10 shows the results of our experiments, where each dot represents one of the 30,000 pairs of terms used for our evaluation. The horizontal axis (in a logarithmic scale), shows the time in seconds required to compute a unification by the standard method, and the vertical axis (also in a logarithmic scale), shows the time in seconds required to compute a unification using the CP-based methods. Points that lie below the grey line correspond to problems where the CP-based approaches are faster. We can clearly see that the standard+CP-based-subsumption approach performs identically to the standard approach for problems where the traditional approach takes less than 1 second (where Robinson's algorithm is the bottleneck), but clearly outperforms it as problems require more time (and the subsumption-based filtering step is the bottleneck). As with the antiunification experiments, the CP approach has a larger variance for problems for which the traditional approach takes less than 1 second, but clearly outperforms the standard approach as problems require more time. As an extreme case there was one pair of terms that took 25897.72 seconds using a standard approach, 55.88 seconds using standard+CP-based-subsumption, and only 0.03 seconds using the CP approach.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>