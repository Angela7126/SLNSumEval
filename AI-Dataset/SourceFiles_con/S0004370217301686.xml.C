<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Belief revision, minimal change and relaxation: A general framework based on satisfaction systems, and applications to description logics.
   </title>
   <abstract>
    Belief revision of knowledge bases represented by a set of sentences in a given logic has been extensively studied but for specific logics, mainly propositional, and also recently Horn and description logics. Here, we propose to generalize this operation from a model-theoretic point of view, by defining revision in the abstract model theory of satisfaction systems. In this framework, we generalize to any satisfaction system the characterization of the AGM postulates given by Katsuno and Mendelzon for propositional logic in terms of minimal change among interpretations. In this generalization, the constraint on syntax independence is partially relaxed. Moreover, we study how to define revision, satisfying these weakened AGM postulates, from relaxation notions that have been first introduced in description logics to define dissimilarity measures between concepts, and the consequence of which is to relax the set of models of the old belief until it becomes consistent with the new pieces of knowledge. We show how the proposed general framework can be instantiated in different logics such as propositional, first-order, description and Horn logics. In particular for description logics, we introduce several concrete relaxation operators tailored for the description logic ALC and its fragments EL and ELU, discuss their properties and provide some illustrative examples.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Belief change, the process that makes an agent's beliefs evolve with newly acquired knowledge, is one of the classical but still challenging problems in artificial intelligence. It is gaining more and more interest these days, due to the emergence of new logical-based knowledge representation frameworks enjoying good complexity properties, allowing them to tackle large scale knowledge bases, and to reason on massive datasets. Among these logical frameworks, one can mention Description Logics (DLs) and Horn Clause theories. Description logics, for instance, are now pervasive in many knowledge-based representation systems such as ontological reasoning, semantic web, scene understanding, cognitive robotics, to mention a few. In all these domains, the expert knowledge is not fixed, but rather a flux evolving over time, hence requiring the definition of rational change operators.
     </paragraph>
     <paragraph>
      Studying the rationality of belief change operators, when knowledge bases are logical theories, i.e. sets of sentences in a given logic, goes back to the seminal work of Alchourròn, Gardenfors and Makinson [1], that gave birth to what is now known as AGM theory. Three change operations are studied within this framework, expansion, contraction and revision. Belief expansion consists in adding new knowledge without checking consistency, while both contraction and revision consist in consistently removing and adding new knowledge, respectively. We focus in this paper on belief revision.
     </paragraph>
     <paragraph>
      Although defined in the abstract framework of logics given by Tarski [40] (so called Tarskian logics), postulates of the AGM theory make strong assumptions on the considered logics. Indeed, in [1] the considered logics have to be closed under the standard propositional connectives in {a mathematical formula}{∧,∨,¬,⇒}, to be compact (i.e. inference depends on a finite set of axioms), and to satisfy the deduction theorem (i.e. entailment and implication are equivalent). While compactness is a standard property of logics, to be closed under the standard propositional connectives is more questionable. Indeed, many logics (called hereafter non-classical logics) such as description logics, equational logic or Horn clause logic, widely used for various modern applications in computing science, do not satisfy such a constraint. Recently, in many works, belief change has been studied in such non-classical logics [12], [17], [34], [35]. For instance, Ribeiro et al. in [35] studied contraction at the abstract level of Tarskian logics, and recently Zhuang et al. in [42] proposed an extension of AGM contraction to arbitrary logics. The adaptation of the AGM postulates for revision for non-classical logics has been studied but only for specific logics, mainly description logics [16], [17], [28], [29], [31], [33], [41] and Horn logics [11], [43]. The reason is that revision can be abstractly defined in terms of expansion and retraction following the Levi identity [23], but this requires the use of negation, which rules out some non-classical logics that do not consider this connective [34].
     </paragraph>
     <paragraph>
      The AGM postulates were interpreted in terms of minimal change in [22], in the sense that the models of the revision should be as close as possible, according to some metric, to the models of the initial knowledge set. However, to the best of our knowledge, the generalization of the AGM theory with minimality criteria on the set of models of knowledge bases has never been proposed. The reason is that semantics is not explicit in the abstract framework of logics defined by Tarski.
     </paragraph>
     <paragraph>
      We propose here to generalize AGM revision but in the abstract model theory of satisfaction systems, which formalizes the intuitive notion of logical systems, including syntax, semantics and the satisfaction relation. This notion was introduced in [18] under the name of “rooms”, and then of “satisfaction systems” in [38]. See also [26]. Then, we propose to generalize to any satisfaction system the approach developed in [22] for propositional logic and in [30] for description logics. In this abstract framework, we will also show how to define revision operators from the relaxation notion that has been introduced in description logics to define dissimilarity measures between concepts [14], [15]. The main idea is to relax the set of models of the old belief until it becomes consistent with the new pieces of knowledge. This notion of relaxation, defined in an abstract way through a set of properties, turns out to generalize several revision operators introduced in different contexts e.g. [9], [20], [25], [29]. This is another key contribution of our work.
     </paragraph>
     <paragraph>
      To concretize our abstract framework, we provide examples of relaxations in propositional logics, first order logics, and Horn logic. The case of description logics (DLs) is more detailed. This is motivated, as mentioned above, by their broad scope of applications, including reasoning on large web data.
     </paragraph>
     <paragraph>
      The paper is organized as follows. Section 2 reviews some concepts, notations and terminology about satisfaction systems which are used in this work. In Section 3, we adapt the AGM theory in the framework of satisfaction systems, and then give an abstract model-theoretic rewriting of the AGM postulates. We then show in Section 3.2 that any revision operator satisfying such postulates accomplishes an update with minimal change to the set of models of knowledge bases. In Section 3.3, we introduce a general framework of relaxation-based revision operators and show that our revision operators lead to faithful assignments and then also satisfy the AGM postulates. In Section 4, we illustrate our abstract approach by providing revision operators in different logics, including classical logics (propositional and first order logics) and non-classical ones (Horn and description logics). The case of DL is further developed in Section 4.4, with several examples. Finally, Section 5 is dedicated to related works.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Satisfaction systems
     </section-title>
     <paragraph>
      Satisfaction systems [26] generalize Tarski's classical “semantic definition of truth” [39] and Barwise's “Translation Axiom” [4]. For the sake of generalization, sentences are simply required to form a set. All other contingencies such as inductive definition of sentences are not considered. Similarly, models are simply seen as elements of a class, i.e. no particular structure is imposed on them.
     </paragraph>
     <section label="2.1">
      <section-title>
       Definition and examples
      </section-title>
      <paragraph label="Definition 1">
       Satisfaction systemA satisfaction system{a mathematical formula}R=(Sen,Mod,⊨) consists of
      </paragraph>
      <list>
       <list-item label="•">
        a set Sen of sentences,
       </list-item>
       <list-item label="•">
        a class Mod of models, and
       </list-item>
       <list-item label="•">
        a satisfaction relation {a mathematical formula}⊨⊆Mod×Sen.
       </list-item>
      </list>
      <paragraph>
       Let us note that the non-logical vocabulary, so-called signature, over which sentences and models are built, is not specified in Definition 1.{sup:1} Actually, it is left implicit. Hence, as we will see in the examples developed in the paper, a satisfaction system always depends on a signature.
      </paragraph>
      <paragraph label="Example 1">
       The following examples of satisfaction systems are of particular importance in computer science and in the remainder of this paper. Propositional Logic (PL)Given a set of propositional variables Σ, we can define the satisfaction system {a mathematical formula}RΣ=(Sen,Mod,⊨) where Sen is the least set of sentences finitely built over propositional variables in Σ and Boolean connectives in {a mathematical formula}{¬,∨}, Mod contains all the mappings {a mathematical formula}ν:Σ→{0,1} (0 and 1 are the usual truth values), and the satisfaction relation ⊨ is the usual propositional satisfaction.Horn Logic (HCL)A Horn clause is a sentence of the form {a mathematical formula}Γ⇒α where Γ is a finite (possibly empty) conjunction of propositional variables and α is a propositional variable. The satisfaction system of Horn clause logic is then defined as for PL except that sentences are restricted to be conjunctions of Horn clauses.First Order Logic (FOL) and Many-sorted First Order LogicWe detail here only the many-sorted variant of FOL, FOL being a particular case. Signatures are triplets {a mathematical formula}(S,F,P) where S is a set of sorts, and F and P are a set of functions and a set of predicate names, respectively, both with arities in {a mathematical formula}S⁎×S and {a mathematical formula}S+ respectively ({a mathematical formula}S+ is the set of all non-empty sequences of elements in S and {a mathematical formula}S⁎=S+∪{ϵ} where ϵ denotes the empty sequence). In the following, to indicate that a function name {a mathematical formula}f∈F (respectively a predicate name {a mathematical formula}p∈P) has for arity {a mathematical formula}(s1…sn,s) (respectively {a mathematical formula}s1…sn), we will note {a mathematical formula}f:s1×…×sn→s (resp. {a mathematical formula}p:s1×…×sn).Given a signature {a mathematical formula}Σ=(S,F,P), we can define the satisfaction system {a mathematical formula}RΣ=(Sen,Mod,⊨) where:
       <list>
        Sen is the least set of sentences built over atoms of the form {a mathematical formula}p(t1,…,tn) where {a mathematical formula}p:s1×…×sn∈P and {a mathematical formula}ti∈TF(X)si for every i, {a mathematical formula}1≤i≤n ({a mathematical formula}TF(X)s is the term algebra of sort s built over F with sorted variables in a given set X) by finitely applying Boolean connectives in {a mathematical formula}{¬,∨} and the quantifier ∀.Mod is the class of models {a mathematical formula}M defined by a family {a mathematical formula}(Ms)s∈S of sets (one for every {a mathematical formula}s∈S), each one equipped with a function {a mathematical formula}fM:Ms1×…×Msn→Ms for every {a mathematical formula}f:s1×…×sn→s∈F and with an n-ary relation {a mathematical formula}pM⊆Ms1×…×Msn for every {a mathematical formula}p:s1×…×sn∈P.Finally, the satisfaction relation ⊨ is the usual first-order satisfaction.Description logic (DL)Signatures are triplets
       </list>
       <paragraph>
        {a mathematical formula}(NC,NR,I) where {a mathematical formula}NC, {a mathematical formula}NR and I are nonempty pairwise disjoint sets where elements in {a mathematical formula}NC, {a mathematical formula}NR and I are called concept names, role names and individuals, respectively.Given a signature {a mathematical formula}Σ=(NC,NR,I), we can define the satisfaction system {a mathematical formula}RΣ=(Sen,Mod,⊨) where:
       </paragraph>
       <list>
        <list-item label="•">
         Sen contains{sup:2} all the sentences of the form {a mathematical formula}C⊑D, {a mathematical formula}x:C and {a mathematical formula}(x,y):r where {a mathematical formula}x,y∈I, {a mathematical formula}r∈NR and C is a concept inductively defined from {a mathematical formula}NC∪{⊤} and binary and unary operators in {a mathematical formula}{_⊓_,_⊔_} and in {a mathematical formula}{_c,∀r._,∃r._}, respectively.
        </list-item>
        <list-item label="•">
         Mod is the class of models {a mathematical formula}I defined by a set {a mathematical formula}ΔI equipped for every concept name {a mathematical formula}A∈NC with a set {a mathematical formula}AI⊆ΔI, for every relation name {a mathematical formula}r∈NR with a binary relation {a mathematical formula}rI⊆ΔI×ΔI, and for every individual {a mathematical formula}x∈I with a value {a mathematical formula}xI∈ΔI.
        </list-item>
        <list-item label="•">
         The satisfaction relation ⊨ is then defined as:
        </list-item>
       </list>
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Knowledge bases and theories
      </section-title>
      <paragraph>
       Let us now consider a fixed but arbitrary satisfaction system {a mathematical formula}R=(Sen,Mod,⊨) (since the signature Σ is supposed fixed, the subscript Σ will be omitted from now on).
      </paragraph>
      <paragraph label="Notation 1">
       Let {a mathematical formula}T⊆Sen be a set of sentences.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Mod(T) is the sub-class of Mod whose elements are models of T, i.e. for every {a mathematical formula}M∈Mod(T) and every {a mathematical formula}φ∈T, {a mathematical formula}M⊨φ. When T is restricted to a formula φ (i.e. {a mathematical formula}T={φ}), we will denote {a mathematical formula}Mod(φ), the class of model of {a mathematical formula}{φ}, rather than {a mathematical formula}Mod({φ}).
       </list-item>
       <list-item label="•">
        {a mathematical formula}Cn(T)={φ∈Sen|∀M∈Mod(T),M⊨φ} is the set of semantic consequences of T.
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}M⊆Mod. Let us note {a mathematical formula}M⁎={φ∈Sen|∀M∈M,M⊨φ}. Therefore, we have for every {a mathematical formula}T⊆Sen, {a mathematical formula}Cn(T)=Mod(T)⁎. When {a mathematical formula}M is restricted to one model {a mathematical formula}M, {a mathematical formula}M⁎ will be equivalently noted {a mathematical formula}M⁎.
       </list-item>
       <list-item label="•">
        Let us note {a mathematical formula}Triv={M∈Mod|M⁎=Sen}, i.e. the set of models in which all formulas are satisfied. In PL and FOL, {a mathematical formula}Triv is empty because the negation is considered. Similarly, the complementation is involved in the DL{a mathematical formula}ALC, hence {a mathematical formula}Triv is empty. In HCL, {a mathematical formula}Triv only contains the unique model where all propositional variables have a truth value equal to 1. In FHCL, {a mathematical formula}Triv contains all models {a mathematical formula}M where for every predicate name {a mathematical formula}p:s1×…×sn∈P, {a mathematical formula}pM=Ms1×…×Msn.
       </list-item>
      </list>
      <paragraph>
       Let us note that for every {a mathematical formula}T⊆Sen, {a mathematical formula}Triv⊆Mod(T).
      </paragraph>
      <paragraph>
       From the above notations, we obviously have:{a mathematical formula}
      </paragraph>
      <paragraph>
       The two functions {a mathematical formula}Mod(_) from {a mathematical formula}P(Sen) into {a mathematical formula}P(Mod) and {a mathematical formula}_⁎ from {a mathematical formula}P(Mod) into {a mathematical formula}P(Sen) form what is known as a Galois connection in that they satisfy the following properties: for all {a mathematical formula}T,T′⊆Sen and {a mathematical formula}M,M′⊆Mod, we have (see [13] and the proof of Proposition 1 below)
      </paragraph>
      <list>
       <list-item label="(1)">
        {a mathematical formula}T⊆T′⟹Mod(T′)⊆Mod(T)
       </list-item>
       <list-item label="(2)">
        {a mathematical formula}M⊆M′⟹M′⁎⊆M⁎
       </list-item>
       <list-item label="(3)">
        {a mathematical formula}T⊆Mod(T)⁎
       </list-item>
       <list-item label="(4)">
        {a mathematical formula}M⊆Mod(M⁎)
       </list-item>
      </list>
      <paragraph label="Definition 2">
       Knowledge base and theoryA knowledge baseT is a set of sentences (i.e. {a mathematical formula}T⊆Sen). A knowledge base T is said to be a theory if and only if {a mathematical formula}T=Cn(T).A theory T is finitely representable if there exists a finite set {a mathematical formula}T′⊆Sen such that {a mathematical formula}T=Cn(T′).
      </paragraph>
      <paragraph label="Proposition 1">
       For every satisfaction system{a mathematical formula}R, we have:Inclusion{a mathematical formula}∀T⊆Sen,T⊆Cn(T);Iteration{a mathematical formula}∀T⊆Sen,Cn(T)=Cn(Cn(T));Monotonicity{a mathematical formula}∀T,T′⊆Sen,T⊆T′⟹Cn(T)⊆Cn(T′).
      </paragraph>
      <paragraph label="Proof">
       For the sake of completeness, let us first show that Mod is decreasing (Property 1): let us assume {a mathematical formula}T⊆T′, then {a mathematical formula}∀M∈Mod(T′) we have {a mathematical formula}∀φ∈T,φ∈T′, and thus {a mathematical formula}M⊨φ. Hence {a mathematical formula}M∈Mod(T).Let us now show that Cn is increasing (monotonicity property): let us assume {a mathematical formula}T⊆T′, then {a mathematical formula}∀φ∈Cn(T) we have {a mathematical formula}∀M∈Mod(T′),M∈Mod(T) since Mod is decreasing, and {a mathematical formula}M⊨φ. Hence {a mathematical formula}φ∈Cn(T′).We have {a mathematical formula}T⊆Mod(T)⁎ (Property 3): indeed, {a mathematical formula}∀φ∈T we have {a mathematical formula}∀M∈Mod(T),M⊨φ by definition of {a mathematical formula}Mod(T). Hence {a mathematical formula}φ∈Mod(T)⁎.It is then easy to see that Cn is extensive (inclusion property) from the previous property and {a mathematical formula}Cn(T)=Mod(T)⁎.Let us finally show that Cn is idempotent (iteration property): extensivity implies {a mathematical formula}∀T,Cn(T)⊆Cn(Cn(T)). Since {a mathematical formula}T⊆Mod(T)⁎ and Cn is increasing, we have {a mathematical formula}Cn(T)⊆Cn(Mod(T)⁎)=Cn(Cn(T)).  □
      </paragraph>
      <paragraph>
       Hence, satisfaction systems are Tarskian according to the definition of logics given by Tarski: a logic is a pair {a mathematical formula}(L,Cn) where {a mathematical formula}L is a set of expressions (formulas) and {a mathematical formula}Cn:P(L)→P(L) is a mapping that satisfies the inclusion, iteration and monotonicity properties [40]. Indeed, from any satisfaction system {a mathematical formula}R we can define the following Tarskian logic {a mathematical formula}(L,Cn) where {a mathematical formula}L=Sen and Cn is the mapping that associates to every {a mathematical formula}T⊆Sen, the set {a mathematical formula}Cn(T) of semantic consequences of T.
      </paragraph>
      <paragraph>
       Classically, the consistency of a theory T is defined as {a mathematical formula}Mod(T)≠∅. The problem of such a definition of consistency is that its significance depends on the considered logic. Hence, this consistency is significant for FOL, while in FHCL it is a trivial property since each set of sentences is consistent because {a mathematical formula}Mod(T) always contains {a mathematical formula}Triv which is non-empty. Here, for the notion of consistency to be more appropriate for our purpose of defining revision for the largest family of logics, we propose a more general definition of consistency, the meaning of which is that there is at least a sentence which is not a semantic consequence.
      </paragraph>
      <paragraph label="Definition 3">
       Consistency{a mathematical formula}T⊆Sen is consistent if {a mathematical formula}Cn(T)≠Sen.
      </paragraph>
      <paragraph label="Proposition 2">
       For every{a mathematical formula}T⊆Sen, T is consistent if and only if{a mathematical formula}Mod(T)∖Triv≠∅.
      </paragraph>
      <paragraph label="Proof">
       Let us prove that {a mathematical formula}Cn(T)=Sen iff {a mathematical formula}Mod(T)∖Triv=∅. Let us first assume that {a mathematical formula}Mod(T)∖Triv=∅. Therefore, this means that the only models that satisfy T are {a mathematical formula}M such that {a mathematical formula}M⁎=Sen (if they exist). Hence, we have {a mathematical formula}Cn(T)=Mod(T)⁎=Sen.Conversely, let us assume that {a mathematical formula}Cn(T)=Sen. This means that every model {a mathematical formula}M such that {a mathematical formula}M⁎≠Sen does not belong to {a mathematical formula}Mod(T), and {a mathematical formula}Mod(T)∖Triv=∅.  □
      </paragraph>
      <paragraph label="Corollary 1">
       For every{a mathematical formula}T⊆Sen, T is inconsistent is equivalent to{a mathematical formula}Mod(T)=Triv.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      AGM postulates for revision in satisfaction systems
     </section-title>
     <section label="3.1">
      <section-title>
       AGM postulates and weakened AGM postulates
      </section-title>
      <paragraph>
       The AGM postulates for knowledge base revision in satisfaction systems are easily adaptable. We build upon the model-theoretic characterization introduced by Katsuno and Mendelzon (KM) [22] for propositional logic. Note, however, that in propositional logic, a belief base can be represented by a formula, and then the KM postulates exploit this property. This is no longer the case in our context, but we argue that the postulates are still appropriate, except the one on syntax independence, as discussed next. Given two knowledge bases {a mathematical formula}T,T′⊆Sen, {a mathematical formula}T∘T′ denotes the revision ofTby{a mathematical formula}T′, that is, {a mathematical formula}T∘T′ is obtained by adding consistently new knowledge {a mathematical formula}T′ to the old knowledge base T. Note that {a mathematical formula}T∘T′ cannot be defined as {a mathematical formula}T∪T′ because nothing ensures that {a mathematical formula}T∪T′ is consistent. The revision operator has then to minimally change T so that {a mathematical formula}T∘T′ is consistent. This is what the AGM postulates ensure.
      </paragraph>
      <paragraph>
       Here we use the following weakened AGM postulates{sup:3}:
      </paragraph>
      <list>
       <list-item>
        If {a mathematical formula}T′ is consistent, then so is {a mathematical formula}T∘T′.
       </list-item>
       <list-item>
        {a mathematical formula}Mod(T∘T′)⊆Mod(T′).
       </list-item>
       <list-item>
        if {a mathematical formula}T∪T′ is consistent, then {a mathematical formula}T∘T′=T∪T′.
       </list-item>
       <list-item>
        {a mathematical formula}Mod((T∘T′)∪T″)⊆Mod(T∘(T′∪T″)).
       </list-item>
       <list-item>
        if {a mathematical formula}(T∘T′)∪T″ is consistent, then {a mathematical formula}Mod(T∘(T′∪T″))⊆Mod((T∘T′)∪T″).
       </list-item>
      </list>
      <paragraph>
       In the literature such as in [22], [30], an additional postulate concerns the independence of the syntax:{a mathematical formula}
      </paragraph>
      <paragraph>
       This postulate states a complete independence of the syntactical forms of both the original knowledge base and the newly acquired knowledge. The problem with Postulate (G4) is that it is almost never satisfied when we want to preserve the structure of knowledge bases and then apply revision operators over the formulas that compose knowledge bases. Indeed, let us consider in the logic PL the following knowledge bases {a mathematical formula}T1={p,q} and {a mathematical formula}T2={q⇒p,q} over the signature {a mathematical formula}{p,q}. Obviously, we have that {a mathematical formula}Mod(T1)=Mod(T2)={ν:p↦1,q↦1}. Let us consider the knowledge base {a mathematical formula}T′={¬q}. We have now that {a mathematical formula}T1∪T′ (and then {a mathematical formula}T2∪T′) is inconsistent. A way to retrieve the consistency is to replace in {a mathematical formula}T1 and {a mathematical formula}T2 the atomic formula q by ¬q. Hence, {a mathematical formula}T1∘T′={p,¬q} and {a mathematical formula}T2∘T′={q⇒p,¬q}. Then {a mathematical formula}Mod(T1∘T′)={ν:p↦1,q↦0}, {a mathematical formula}Mod(T2∘T′)={ν:p↦1,q↦0;ν′:p↦0,q↦0}, and {a mathematical formula}Mod(T1∘T′)≠Mod(T2∘T′). This example shows that syntax independence may be too strong a requirement.
      </paragraph>
      <paragraph>
       In [22], the authors bypass the problem by representing any knowledge base K (which is a theory in [22]) by a propositional formula ψ such that {a mathematical formula}K=Cn(ψ). Hence, they apply their revision operator on ψ and not on K, and so they lose the structure of the knowledge base K.
      </paragraph>
      <paragraph>
       A weaker form of this postulate could be written as:{a mathematical formula} which ensures a partial independence of the syntax, only on the new knowledge. Remarkably, this weaker form can be derived from the other postulates (as expressed in Proposition 3), and is hence not used in the subsequent proofs (see e.g. Theorem 1 below).
      </paragraph>
      <paragraph label="Proposition 3">
       Postulates (G1)–(G3), (G5) and (G6) imply Postulate (G'4).
      </paragraph>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
      <paragraph>
       Based on this result, the only weakened AGM postulates (G1)–(G3), (G5) and (G6) are considered next.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Faithful assignment and weakened AGM postulates
      </section-title>
      <paragraph>
       Intuitively, any revision operator ∘ satisfying the weakened AGM postulates above induces minimal change, that is the models of {a mathematical formula}T∘T′ are the models of T that are the closest to models of {a mathematical formula}T′, according to some distance for measuring how close are models. This is what is now shown in this section by establishing a correspondence between the weakened AGM postulates and binary relations over models with minimality conditions.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}M⊆Mod and ⪯ be a binary relation over {a mathematical formula}M. We define ≺ as {a mathematical formula}M≺M′ if and only if {a mathematical formula}M⪯M′ and {a mathematical formula}M′⪯̸M. We also define {a mathematical formula}Min(M,⪯)={M∈M|∀M′∈M,M′⊀M}.
      </paragraph>
      <paragraph label="Definition 4">
       Faithful assignmentAn assignment is a mapping that assigns to each knowledge base T a binary relation {a mathematical formula}⪯T over Mod. We say that this assignment is faithful (FA) if the following two conditions are satisfied:
      </paragraph>
      <list>
       <list-item label="(1)">
        if {a mathematical formula}M,M′∈Mod(T), {a mathematical formula}M⊀TM′.
       </list-item>
       <list-item label="(2)">
        for every {a mathematical formula}M∈Mod(T) and every {a mathematical formula}M′∈Mod∖Mod(T), {a mathematical formula}M≺TM′.
       </list-item>
      </list>
      <paragraph>
       This definition of FA differs from the one originally given in [22] on two points:
      </paragraph>
      <list>
       <list-item label="(1)">
        In [22], a third condition is stated:{a mathematical formula} As for (G4), this condition expresses a syntactical independence.
       </list-item>
       <list-item label="(2)">
        It is not required for {a mathematical formula}⪯T to be a pre-order. As shown below, the only important feature to have to make a correspondence between a FA and the fact that ∘ satisfies the weakened AGM Postulates is that there is a minimal model for {a mathematical formula}⪯T in {a mathematical formula}Mod(T′) as expressed by Theorem 1.
       </list-item>
      </list>
      <paragraph label="Theorem 1">
       Let ∘ be a revision operator. The operator ∘ satisfies the weakened AGM Postulates (as defined in Section3.1) if and only if there exists a FA that maps each knowledge base{a mathematical formula}T⊆Sento a binary relation{a mathematical formula}⪯Tsuch that for every knowledge base{a mathematical formula}T′⊆Sen:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Mod(T∘T′)∖Triv=Min(Mod(T′)∖Triv,⪯T);
       </list-item>
       <list-item label="•">
        if{a mathematical formula}T′is consistent, then{a mathematical formula}Min(Mod(T′)∖Triv,⪯T)≠∅;
       </list-item>
       <list-item label="•">
        for every{a mathematical formula}T″⊆Sen, if{a mathematical formula}(T∘T′)∪T″is consistent, then{a mathematical formula}Min(Mod(T′)∖Triv,⪯T)∩Mod(T″)=Min(Mod(T′∪T″)∖Triv,⪯T).
       </list-item>
      </list>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
      <paragraph>
       Note that if {a mathematical formula}T′ is inconsistent, then so is {a mathematical formula}T∘T′, and we can set arbitrarily {a mathematical formula}T∘T′=T′, which corresponds to a cautious revision. The case where T is inconsistent is not considered in this paper (and is usually excluded from the scope of revision procedures), since in that case other operators could be more relevant than revision, in particular debugging methods (see e.g. [36] for debugging of terminologies, or [32] for base revision for ontology debugging, both in description logics).
      </paragraph>
      <paragraph>
       Given a revision operator ∘ satisfying the weakened AGM postulates, any FA satisfying the supplementary conditions of Theorem 1 will be called FA+. To a revision operator ∘ satisfying the weakened AGM postulates, we can associate many FA+. An example of such a FA+ was given in the proof of Theorem 1. Another example is the mapping f that associates to every {a mathematical formula}T⊆Sen the binary relation {a mathematical formula}⪯T defined as follows:
      </paragraph>
      <paragraph>
       Given {a mathematical formula}T′⊆Sen, let us start by defining {a mathematical formula}⪯TT′⊆Mod(T′)×Mod(T′) as:{a mathematical formula} Let us then set {a mathematical formula}f(T)=⪯T=⋃T′⪯TT′ (i.e. {a mathematical formula}M⪯TM′⇔∃T′,M⪯TT′M′).
      </paragraph>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
      <paragraph>
       Actually, the set of FA+ associated with a revision operator satisfying the weakened AGM postulates has a lattice structure, as shown by the following definition and propositions.
      </paragraph>
      <paragraph label="Definition 5">
       Let {a mathematical formula}f1,f2 be two FA. Let us denote {a mathematical formula}f1⊔f2 (resp. {a mathematical formula}f1⊓f2) the mapping that assigns to each knowledge base {a mathematical formula}T⊆Sen the binary relation {a mathematical formula}⪯T=⪯T1∪⪯T2 (resp. {a mathematical formula}⪯T=⪯T1∩⪯T2) where {a mathematical formula}fi(T)=⪯Ti for {a mathematical formula}i=1,2.
      </paragraph>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
      <paragraph label="Proposition 5">
       The relation ≤ defined on FA+ by:{a mathematical formula}is a partial ordering.Given a revision operator ∘ which satisfies the weakened AGM postulates, the poset{a mathematical formula}(FA+(∘),≤)of FA+ associated with ∘ is a lattice. For any{a mathematical formula}f,g∈FA+(∘),{a mathematical formula}f⊔g(respectively{a mathematical formula}f⊓g) is the least upper bound (respectively the greatest lower bound) of{a mathematical formula}{f,g}. The lattice{a mathematical formula}(FA+(∘),≤)is further complete.
      </paragraph>
      <paragraph label="Proof">
       The fact that the relation ≤ actually defines a partial order is straightforward. The fact that {a mathematical formula}f⊔g and {a mathematical formula}f⊓g are the least upper bound and greatest lower bound of {a mathematical formula}{f,g} is also easy to show.Given a subset {a mathematical formula}S⊆FA+(∘), its least upper bound is the mapping {a mathematical formula}⊔S:T↦⋃f∈Sf(T), and its greatest lower bound is the mapping {a mathematical formula}⊓S:T↦⋂f∈Sf(T). By extending the proof of Proposition 4, it is easy to show that ⊔S and ⊓S are FA+.  □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Relaxation and AGM postulates
      </section-title>
      <paragraph>
       Relaxations have been introduced in [14], [15] in the framework of description logics with the aim of defining dissimilarity between concepts. Here, we propose to generalize this notion in the framework of satisfaction systems.
      </paragraph>
      <paragraph label="Definition 6">
       RelaxationA relaxation is a mapping {a mathematical formula}ρ:Sen→Sen satisfying the following properties: Extensivity{a mathematical formula}∀φ∈Sen,Mod(φ)⊆Mod(ρ(φ)).Exhaustivity{a mathematical formula}∃k∈N,Mod(ρk(φ))=Mod, where {a mathematical formula}ρ0 is the identity mapping, and for all {a mathematical formula}k&gt;0,ρk(φ)=ρ(ρk−1(φ)).
      </paragraph>
      <paragraph>
       Let us observe that relaxations exist if and only if the underlying satisfaction system {a mathematical formula}(Sen,Mod,⊨) has tautologies (i.e. formulas {a mathematical formula}φ∈Sen such that {a mathematical formula}Mod(φ)=Mod). Indeed, when the satisfaction system has tautologies, we can define the trivial relaxation {a mathematical formula}ρ:φ↦ψ where ψ is any tautology.{sup:4} Conversely, all relaxations imply that the underlying satisfaction system has tautologies to satisfy the exhaustivity condition.
      </paragraph>
      <paragraph>
       The interest of relaxations is that they give rise to revision operators which have demonstrated their usefulness in practice (see Section 4).
      </paragraph>
      <paragraph label="Notation 2">
       Let {a mathematical formula}T⊆Sen be a knowledge base. Let {a mathematical formula}K={kφ∈N|φ∈T}, and {a mathematical formula}K′={kφ′∈N|φ∈T}. Let us note:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ρK(T)={ρkφ(φ)|kφ∈K,φ∈T},
       </list-item>
       <list-item label="•">
        {a mathematical formula}∑K=∑kφ∈Kkφ,
       </list-item>
       <list-item label="•">
        {a mathematical formula}K≤K′ when for every {a mathematical formula}φ∈T, {a mathematical formula}kφ≤kφ′,
       </list-item>
       <list-item label="•">
        {a mathematical formula}K&lt;K′ if {a mathematical formula}K≤K′ and {a mathematical formula}∃φ∈T, {a mathematical formula}kφ&lt;kφ′.
       </list-item>
      </list>
      <paragraph>
       In this notation, {a mathematical formula}kφ is a number associated with each formula φ of the knowledge base (equivalently it can be considered as a function of φ taking values in {a mathematical formula}N), which intuitively represents the degree to which φ is relaxed.
      </paragraph>
      <paragraph label="Definition 7">
       Revision based on relaxationLet ρ be a relaxation. A revision operator overρ is a mapping {a mathematical formula}∘:P(Sen)×P(Sen)→P(Sen) satisfying for every {a mathematical formula}T,T′⊆Sen:{a mathematical formula} for some {a mathematical formula}K={kφ∈N|φ∈T} such that:
      </paragraph>
      <list>
       <list-item label="(1)">
        if {a mathematical formula}T′ is consistent, then {a mathematical formula}T∘T′ is consistent;
       </list-item>
       <list-item label="(2)">
        for every {a mathematical formula}K′ such that {a mathematical formula}ρK′(T)∪T′ is consistent, {a mathematical formula}∑K≤∑K′ (minimality on the number of applications of the relaxation);
       </list-item>
       <list-item label="(3)">
        for every {a mathematical formula}T″ such that {a mathematical formula}Mod(T′)⊆Mod(T″), if {a mathematical formula}T∘T″=ρK′(T)∪T″, then {a mathematical formula}K′≤K.
       </list-item>
      </list>
      <paragraph>
       Revision based on relaxation is illustrated in Fig. 1 where theories are represented as sets of their models. Intermediate steps to define the revision operators are then the definitions of formula and theory relaxations.
      </paragraph>
      <paragraph>
       It is important to note that given a relaxation ρ, several revision operators can be defined. Without Condition 3 of Definition 7, we could accept revision operators ∘ that do not satisfy Postulates (G5) and (G6). Hence, Condition 3 allows us to exclude such operators. To illustrate this, let us consider in FOL the satisfaction system {a mathematical formula}R=(Sen,Mod,⊨) over the signature {a mathematical formula}(S,F,P) where {a mathematical formula}S={s}, {a mathematical formula}F=∅ and {a mathematical formula}P={=:s×s}. Let us consider {a mathematical formula}T,T′⊆Sen such that:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Obviously, {a mathematical formula}T′ is consistent. As T does not contain the axioms for equality, it is also consistent. Indeed, the model {a mathematical formula}M with its associated set {a mathematical formula}Ms={0,1,2} and the binary relation {a mathematical formula}=M⊆Ms×Ms, defined by the following set {a mathematical formula}{(0,0),(1,1),(2,0)}, satisfies T.
      </paragraph>
      <paragraph>
       But {a mathematical formula}T∪T′ is not consistent. The reason is that when the meaning of = is the equality, the first axiom of T can only be satisfied by models with two values while the second axiom is satisfied by models with three values. A way to retrieve the consistency is to remove one of the two axioms. This can be modeled by the relaxation ρ that maps each formula to a tautology.{sup:5} But in this case, we have then two options depending on whether we remove and change the first or the second axiom by a tautology, which give rise to two revision operators {a mathematical formula}∘1 and {a mathematical formula}∘2. The first two conditions of Definition 7 are satisfied by both {a mathematical formula}∘1 and {a mathematical formula}∘2.
      </paragraph>
      <paragraph>
       Now, let us take {a mathematical formula}T″={∃x.∃y.¬x=y} which is satisfied, when added to the axioms in {a mathematical formula}T′, by any model with at least two elements. Hence, {a mathematical formula}(T∘1T′)∪T″ and {a mathematical formula}(T∘2T′)∪T″ are consistent. Without the third condition, nothing would prevent to define {a mathematical formula}T∘1(T′∪T″) (respectively {a mathematical formula}T∘2(T′∪T″)) by removing and change in T the second (respectively the first) axiom by a tautology which would be a counter-example to Postulates (G5) and (G6). Actually, as shown by the result below, this third condition of Definition 7 entails Postulates (G5) and (G6), and then, by Proposition 3, entails Postulate (G'4).
      </paragraph>
      <paragraph>
       However in some situations Condition 3 may be considered as too strong, forcing to relax more than what would be needed to satisfy only Condition 2. This could typically be the case when Condition 2 could be obtained in two different ways, for instance for {a mathematical formula}K′={0,1,0,0...} or for {a mathematical formula}K″={1,0,0,0...}. Then taking {a mathematical formula}Cn(T′)=Cn(T″), and revising {a mathematical formula}T∘T′ using {a mathematical formula}K′ and {a mathematical formula}T∘T″ using {a mathematical formula}K″ would not meet Condition 3. To satisfy it, relaxation should be done for instance with {a mathematical formula}K={1,1,0,0...}. Therefore in concrete applications, we will have to find a compromise between Condition 3 and (G5)–(G6) at the price of potential larger relaxations on the one hand, and less relaxation but potentially the loss of (G5)–(G6) on the other hand.
      </paragraph>
      <paragraph label="Notation 3">
       In the context of Definition 7, let {a mathematical formula}T,T′⊆Sen be two knowledge bases. If {a mathematical formula}T∘T′=ρK(T)∪T′ with {a mathematical formula}K={kφ∈N|φ∈T}, then we note {a mathematical formula}KTT′=K.
      </paragraph>
      <paragraph label="Theorem 3">
       Any revision operator ∘ based on a relaxation (Definition 7) satisfies the weakened AGM postulates.
      </paragraph>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
      <paragraph>
       So far we showed that several FA+ can be associated with a given revision operator ∘ satisfying the weakened AGM postulates. Here, we define a particular one, which is more specific to revision operators based on relaxation. Let ρ be a relaxation and {a mathematical formula}fρ be the mapping that associates to every {a mathematical formula}T⊆Sen the binary relation {a mathematical formula}⪯T defined as follows:
      </paragraph>
      <paragraph>
       Given {a mathematical formula}T′⊆Sen, let us start by defining {a mathematical formula}⪯TT′⊆Mod(T′)×Mod(T′) as:{a mathematical formula} Let us then set {a mathematical formula}⪯T=⋃T′⪯TT′ (i.e. {a mathematical formula}M⪯TM′⇔∃T′,M⪯TT′M′). We have {a mathematical formula}⪯T⊆Mod×Mod because {a mathematical formula}⪯T∅⊆⪯T.
      </paragraph>
      <paragraph>
       Intuitively, it means that T has to be relaxed more to be satisfied by {a mathematical formula}M′ than to be satisfied by {a mathematical formula}M.
      </paragraph>
      <paragraph label="Theorem 4">
       For any revision operator ∘ based on a relaxation ρ as defined inDefinition 7, the mapping{a mathematical formula}fρis a FA+.
      </paragraph>
      <paragraph label="Proof">
       See Appendix.  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Applications
     </section-title>
     <paragraph>
      In this section, we illustrate our general approach by defining revision operators based on relaxations for the logics PL, HCL, and FOL. We further develop the case of DLs in Section 4.4, by defining several concrete relaxation operators for different fragments of the DL {a mathematical formula}ALC.
     </paragraph>
     <section label="4.1">
      Revision in PL
      <paragraph>
       Here, inspired by the work in [7], [8] on Morpho-Logics, we define relaxations based on dilations from mathematical morphology [6]. In PL, knowing a formula is equivalent to knowing the set of its models, and we can identify any propositional formula φ with the set of its interpretations {a mathematical formula}Mod(φ). To define relaxations in PL, we will apply set-theoretic morphological operations. First, let us recall a basic definition of dilation in mathematical morphology [6]. Let X and B be two subsets of {a mathematical formula}Rn. The dilation of X by the structuring element B, denoted by {a mathematical formula}DB(X), is defined as follows:{a mathematical formula} where {a mathematical formula}Bx denotes the translation of B at x. More generally, dilations in any space can be defined in a similar way by considering the structuring element as a binary relationship between elements of this space.{sup:6}
      </paragraph>
      <paragraph>
       In PL, this leads to the following dilation of a formula {a mathematical formula}φ∈Sen:{a mathematical formula} where {a mathematical formula}Bν contains all the models that satisfy some relationship with ν. The relationship standardly used is based on a discrete distance δ between models, and the most commonly used is the Hamming distance {a mathematical formula}dH where {a mathematical formula}dH(ν,ν′) for two propositional models over a same signature is the number of propositional symbols that are instantiated differently in ν and {a mathematical formula}ν′. From any distance δ between models, a distance from models to a formula is derived as follows: {a mathematical formula}d(ν,φ)=minν′⊨φδ(ν,ν′). In this case, we can rewrite the dilation of a formula as follows:{a mathematical formula} This consists in using the distance ball of radius 1 as structuring element B. To ensure the exhaustivity condition to our relaxation, we need to add a condition on distances, the betweenness property[14].
      </paragraph>
      <paragraph label="Definition 8">
       Betweenness propertyLet δ be a discrete distance over a set S. δ has the betweenness property if for all {a mathematical formula}x,y in S and all k in {a mathematical formula}{0,1,…,δ(x,y)}, there exists z in S such that {a mathematical formula}δ(x,z)=k and {a mathematical formula}δ(z,y)=δ(x,y)−k. The Hamming distance trivially satisfies the betweenness property. The interest for our purpose of this property is that it allows from any model to reach any other one, and then ensuring the exhaustivity property of relaxation.{sup:7}
      </paragraph>
      <paragraph label="Proposition 6">
       Let{a mathematical formula}DBbe a dilation applied to formulas{a mathematical formula}φ∈Senfor a finite signature, and based on a distance between models that satisfies the betweenness property. Such a dilation{a mathematical formula}DBis a relaxation.
      </paragraph>
      <paragraph label="Proof">
       It is extensive. Indeed, for every φ and for every model {a mathematical formula}ν∈Mod(φ), we have that {a mathematical formula}d(ν,φ)=0, and then {a mathematical formula}φ⊨DB(φ). Exhaustivity results from the fact that the considered signature is a finite set and from the betweenness property.  □
      </paragraph>
      <paragraph>
       Using Definition 7, this relaxation allows defining revision operators that include the classical Dalal's revision as a particular case (see [7], [8]).
      </paragraph>
      <paragraph>
       A simple example is illustrated in Fig. 2. Three propositional symbols a, b and c are considered. The set of models is represented by the vertices of a cube, and we assimilate a formula formed by a simple conjunction of symbols with its corresponding model. For instance {a mathematical formula}a∧b∧c is assimilated to the corresponding world, represented by the point {a mathematical formula}(1,1,1) in the cube. The edges link two worlds differing by one instantiation of a propositional symbol, i.e. at a distance 1 for the Hamming distance. For instance vertices representing {a mathematical formula}a∧b∧c and {a mathematical formula}¬a∧b∧c are linked by an edge (we have {a mathematical formula}dH(a∧b∧c,¬a∧b∧c)=1). Colored dots define φ and ψ: {a mathematical formula}φ=a∧b∧c and {a mathematical formula}ψ=¬c. The red circle represents the result of the revision {a mathematical formula}φ∘ψ=a∧b∧¬c. Indeed, φ and ψ are inconsistent, hence we relax φ by a dilation of size 1 according to the Hamming distance, leading to {a mathematical formula}DB(φ)=(a∧b∧c)∨(¬a∧b∧c)∨(a∧¬b∧c)∨(a∧b∧¬c), which is now consistent with φ and the conjunction provides the revision. The result here simply amounts to change the old belief which included c, by negating this atom according to the new knowledge expressed by ψ.
      </paragraph>
     </section>
     <section label="4.2">
      Revision in HCL
      <paragraph>
       Many works have focused on belief revision involving propositional Horn formulas (cf. [12] to have an overview on these works). Here, we propose to extend relaxations that we have defined in the framework of PL to deal with the Horn fragment of propositional theories.
      </paragraph>
      <paragraph label="Definition 9">
       Model intersectionGiven a propositional signature Σ and two Σ-models {a mathematical formula}ν,ν′:Σ→{0,1}, we note {a mathematical formula}ν∩ν′:Σ→{0,1} the Σ-model defined by:{a mathematical formula} Given a set of Σ-models {a mathematical formula}S, we note{a mathematical formula}{a mathematical formula}cl∩(S) is then the closure of {a mathematical formula}S under intersection of positive atoms.
      </paragraph>
      <paragraph>
       For any set {a mathematical formula}S closed under intersection of positive atoms, there exists a Horn sentence φ that defines {a mathematical formula}S (i.e. {a mathematical formula}Mod(φ)=S). Given a distance δ between models, we then define a relaxation ρ as follows: for every Horn formula φ, {a mathematical formula}ρ(φ) is any Horn formula {a mathematical formula}φ′ such that {a mathematical formula}Mod(φ′)=cl∩(Mod(DB(φ)) (by the previous property, we know that such a formula {a mathematical formula}φ′ exists).
      </paragraph>
      <paragraph label="Proposition 7">
       With the same conditions as inProposition 6, the mapping ρ is a relaxation.
      </paragraph>
      <paragraph>
       Then a revision operator can be defined from ρ according to Definition 7.
      </paragraph>
     </section>
     <section label="4.3">
      Revision in FOL
      <paragraph>
       A trivial way to define a relaxation in FOL is to map any formula to a tautology. A less trivial and more interesting relaxation is to change universal quantifiers to existential ones. Indeed, given a formula φ of the form {a mathematical formula}∀x.ψ, if φ is not consistent with a given theory T, {a mathematical formula}∃x.ψ may be consistent with T (it is quite intuitive that if it cannot be consistent for all values, it can be for some of them). A similar approach has been adopted for defining merging operators using dilations in FOL in [20]. In the following we suppose that given a signature, every formula φ in Sen is a disjunction of formulas in prenex form (i.e. φ is of the form {a mathematical formula}⋁jQ1jx1j…Qnjjxnjj.ψj where each {a mathematical formula}Qij is in {a mathematical formula}{∀,∃}). Let us define the relaxation ρ as follows, for a tautology τ:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ρ(τ)=τ;
       </list-item>
       <list-item label="•">
        {a mathematical formula}ρ(∃1x1…∃nxn.φ)=τ;
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}φ=Q1x1…Qnxn.ψ be a formula such that the set {a mathematical formula}Eφ={i,1≤i≤n|Qi=∀}≠∅. Then, {a mathematical formula}ρ(Q1x1…Qnxn.φ)=⋁i∈Eφφi where {a mathematical formula}φi=Q1′x1…Qn′xn.ψ such that for every {a mathematical formula}j≠i, {a mathematical formula}1≤j≤n, {a mathematical formula}Qj′=Qj and {a mathematical formula}Qi′=∃;
       </list-item>
       <list-item label="•">
        {a mathematical formula}ρ(⋁jQ1jx1j…Qnjjxnjj.ψ)=⋁jρ(Q1jx1j…Qnjjxnjj.ψ).
       </list-item>
      </list>
      <paragraph label="Proposition 8">
       ρ is a relaxation.
      </paragraph>
      <paragraph label="Proof">
       It is obviously extensive, and exhaustivity results from the fact that in a finite number of steps, we always reach the tautology τ.  □
      </paragraph>
      <paragraph>
       Again a revision operator can then be defined from ρ using Definition 7.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Revision in DL
      </section-title>
      <section label="4.4.1">
       <section-title>
        General construction scheme
       </section-title>
       <paragraph>
        The instantiation of our abstract framework to DLs follows the scheme depicted in Fig. 3.
       </paragraph>
       <paragraph>
        The necessary ingredient is the specialization of formulas relaxations as abstractly defined in Definition 6. To this end, we propose to define a formula relaxation in two ways (other definitions may also exist). For sentences of the form {a mathematical formula}C⊑D, the first proposed approach consists in relaxing the set of interpretations of D, while the second one amounts to “retracting” the set of interpretations of C. We give hereafter formal definitions of these notions of concept relaxation and retraction.
       </paragraph>
       <paragraph label="Definition 10">
        Concept relaxationGiven a signature {a mathematical formula}(NC,NR,I), we note {a mathematical formula}C the set of concepts over this signature. A concept relaxation is an operator {a mathematical formula}ρ:C→C that satisfies, in every model, the following properties for all C in {a mathematical formula}C:
       </paragraph>
       <list>
        <list-item label="(1)">
         ρ is extensive, i.e. {a mathematical formula}C⊑ρ(C)
        </list-item>
        <list-item label="(2)">
         ρ is exhaustive, i.e. {a mathematical formula}∃k∈N,⊤⊑ρk(C)
        </list-item>
       </list>
       <paragraph>
        A similar notion of concept relaxation has first been introduced in [14], [15] but with an additional constraint of non-decreasingness property that we do not need in this work.
       </paragraph>
       <paragraph>
        A trivial concept relaxation is the operation {a mathematical formula}ρ⊤ that maps every concept C to ⊤. Other non-trivial concrete concept relaxations will be discussed in the sequel.
       </paragraph>
       <paragraph label="Definition 11">
        Concept retractionA (concept) retraction is an operator {a mathematical formula}κ:C→C that satisfies, in every model, the following properties for all C in {a mathematical formula}C:
       </paragraph>
       <list>
        <list-item label="(1)">
         κ is anti-extensive, i.e. {a mathematical formula}κ(C)⊑C, and
        </list-item>
        <list-item label="(2)">
         κ is exhaustive, i.e. {a mathematical formula}∀D∈C,∃k∈N such that κk(C)⊑D.
        </list-item>
       </list>
       <paragraph>
        Note that in this definition, D could be replaced equivalently by ⊥.
       </paragraph>
       <paragraph>
        With these definitions at hand, formulas relaxation can be defined as follows, using either concept relaxation (Definition 10) or concept retraction (Definition 11). We suppose that any signature {a mathematical formula}(NC,NR,I) always contains in {a mathematical formula}NR a relation name {a mathematical formula}r⊤ the meaning of which is, in any model {a mathematical formula}O, {a mathematical formula}r⊤O=ΔO×ΔO.
       </paragraph>
       <paragraph label="Definition 12">
        Formula relaxation based on concept relaxationLet ρ a concept relaxation as in Definition 10. A formula relaxation based onρ, denoted {a mathematical formula}ρFρ is defined as follows, for any two complex concepts C and D, any individuals {a mathematical formula}a,b, and any role r:{a mathematical formula} Note that the relaxation of the role assertion axiom amounts to delete it from the knowledge base, since a tautology is satisfied by any model.
       </paragraph>
       <paragraph label="Proof">
        {a mathematical formula}ρFρis a formula relaxation in the sense ofDefinition 6.It directly follows from the extensivity and exhaustivity of ρ.  □
       </paragraph>
       <paragraph label="Definition 13">
        Formula relaxation based on concept retractionA formula relaxation based on a concept retractionκ, denoted {a mathematical formula}ρFκ, is defined as follows, for any two complex concepts C and D, any individuals {a mathematical formula}a,b, and any role r:{a mathematical formula} Similarly, the relaxation of the concept assertion amounts to delete it from the knowledge base.
       </paragraph>
       <paragraph>
        A similar construction can be found in [29] for sentences of the form {a mathematical formula}(a:C).
       </paragraph>
       <paragraph label="Proof">
        {a mathematical formula}ρFκis a formula relaxation in the sense ofDefinition 6.Extensivity and exhaustivity follow directly from the properties of κ.  □
       </paragraph>
       <paragraph>
        To complete the picture, it remains to define concrete concept relaxation and retraction operators for particular Description Logics families. We consider the logic {a mathematical formula}ALC, as defined in Section 2.1, and its fragments {a mathematical formula}EL and {a mathematical formula}ELU. {a mathematical formula}EL-concept description constructors are existential restriction (∃), conjunction (⊓), ⊤ and ⊥, while {a mathematical formula}ELU-concept constructors are those of {a mathematical formula}EL enriched with disjunction (⊔).
       </paragraph>
      </section>
      <section label="4.4.2">
       Relaxation and retraction in {a mathematical formula}EL
       <section>
        {a mathematical formula}EL-concept retractions.
        <paragraph>
         A trivial concept retraction is the operator {a mathematical formula}κ⊥ that maps every concept to ⊥. Note that this operator is also particularly interesting for debugging ontologies expressed in {a mathematical formula}EL[37]. Let us illustrate this operator for revision through the following example adapted from [29] to restrict the language to {a mathematical formula}EL.
        </paragraph>
        <paragraph label="Example 2">
         Let {an inline-figure} and {an inline-figure}. Clearly {a mathematical formula}T∪T′ is inconsistent. The formula relaxation based on the retraction {a mathematical formula}κ⊥ amounts to apply {a mathematical formula}κ⊥ to the concept {an inline-figure} resulting in the following new knowledge base {an inline-figure} which is now consistent with {a mathematical formula}T′. An alternative solution is to retract the concept {an inline-figure} in {an inline-figure} which results in the following knowledge base {an inline-figure} which is also consistent with {a mathematical formula}T′. The sets of minimal sum {a mathematical formula}K1 and {a mathematical formula}K2 in Condition 2 of Definition 7 are {a mathematical formula}K1={1,0}, (i.e. {a mathematical formula}kφ1=1,kφ2=0, where {an inline-figure}) and {a mathematical formula}K2={0,1}. However, Condition 3 of the same definition is not satisfied: let us take {a mathematical formula}T″=T′. Then a fortiori we have {a mathematical formula}Mod(T′)⊆Mod(T″). We can then write {a mathematical formula}T∘T′=ρK1(T)∪T′ and {a mathematical formula}T∘T″=ρK2(T)∪T″=ρK2(T)∪T′. But we do not have any ordering relation between {a mathematical formula}K1 and {a mathematical formula}K2. To ensure Condition 3, we must relax one more time the axioms in T leading to the following knowledge base {an inline-figure} (for {a mathematical formula}K={1,1}). The final revision then writes {an inline-figure}. This revision satisfies the weakened AGM postulates but may appear too strong, and one may prefer one of the following solutions: {an inline-figure} or {an inline-figure} at the price of loosing (G5)–(G6).
        </paragraph>
        <paragraph>
         Although the results are rather intuitive, one should note that it is pretty hard to figure out what each DL researcher would like to have as a result in such an example, and this enforces the interest of relying on an established theory such as AGM or its extension. In our work we propose operators enjoying a set of properties stemming from our adaptation of the AGM theory. Some of them can meet the requirement of a knowledge engineer, and some other may not completely, depending on the context, the ontology, etc.
        </paragraph>
       </section>
       <section>
        {a mathematical formula}EL-concept relaxations.
        <paragraph>
         Dually, a trivial relaxation is the operator {a mathematical formula}ρ⊤ that maps every concept to ⊤. Other non-trivial {a mathematical formula}EL-concept description relaxations have been introduced in [14]. We summarize here some of these operators.
        </paragraph>
        <paragraph>
         {a mathematical formula}EL concept descriptions can appropriately be represented as labeled trees, often called {a mathematical formula}ELdescription trees[3]. An {a mathematical formula}EL description tree is a tree whose nodes are labeled with sets of concept names and whose edges are labeled with role names. An {a mathematical formula}EL concept description{a mathematical formula} with {a mathematical formula}Pi∈NC∪{⊤}, can be translated into a description tree by labeling the root node {a mathematical formula}v0 with {a mathematical formula}{P1,…,Pn}, creating an {a mathematical formula}rj successor, and then proceeding inductively by expanding {a mathematical formula}Cj for the {a mathematical formula}rj-successor node for all {a mathematical formula}j∈{1,…,m}.
        </paragraph>
        <paragraph>
         An {a mathematical formula}EL-concept description relaxation then amounts to apply simple tree operations. Two relaxations can hence be defined [14]: (i) {a mathematical formula}ρdepth that reduces the role depth of each concept by 1, simply by pruning the description tree, and (ii) {a mathematical formula}ρleaves that removes all leaves from a description tree.
        </paragraph>
       </section>
      </section>
      <section label="4.4.3">
       Relaxations in {a mathematical formula}ELU
       <paragraph>
        The relaxation defined above exploits the strong property that an {a mathematical formula}EL concept description is isomorphic to a description tree. This is arguably not true for more expressive DLs. Let us try to go one step further in expressivity and consider the logic {a mathematical formula}ELU. Here we only propose some definitions of relaxations. Retractions could be designed similarly. A relaxation operator, as introduced in [14], requires a concept description to be in a special normal form, called normal form with grouping of existentials, defined recursively as follows.
       </paragraph>
       <paragraph label="Definition 14">
        Normal form with grouping of existential restrictionsWe say that an {a mathematical formula}EL-concept D is written in normal form with grouping of existential restrictions if it is of the form{a mathematical formula} where {a mathematical formula}ND⊆NC is a set of concept names and the concepts {a mathematical formula}Dr are of the form{a mathematical formula} where no subsumption relation holds between two distinct conjuncts and {a mathematical formula}CDr is a set of complex {a mathematical formula}EL-concepts that are themselves in normal form with grouping of existential restrictions.
       </paragraph>
       <paragraph>
        The purpose of {a mathematical formula}Dr terms is simply to group existential restrictions that share the same role name. For an {a mathematical formula}ELU-concept C we say that C is in normal form if it is of the form ({a mathematical formula}C≡C1⊔C2⊔⋯⊔Ck) and each of the {a mathematical formula}Ci is an {a mathematical formula}EL-concept in normal form with grouping of existential restrictions.
       </paragraph>
       <paragraph label="Definition 15">
        Relaxation from normal form [14]Given an {a mathematical formula}ELU-concept description C we define an operator {a mathematical formula}ρe recursively as follows.
       </paragraph>
       <list>
        <list-item label="•">
         For {a mathematical formula}C=⊤ we define {a mathematical formula}ρe(C)=⊤.
        </list-item>
        <list-item label="•">
         For {a mathematical formula}C=Dr, where {a mathematical formula}Dr is a group of existential restrictions as in Equation (4), we need to distinguish two cases:
        </list-item>
        <list-item label="•">
         For {a mathematical formula}C=D as in Equation (3) we define {a mathematical formula}ρe(D)=⨆G∈CD(ρe(G)⊓⨅H∈CD∖{G}H), where {a mathematical formula}CD=ND∪{Dr|r∈NR}.
        </list-item>
        <list-item label="•">
         Finally for {a mathematical formula}C=C1⊔C2⊔⋯⊔Ck we set {a mathematical formula}ρe(C)=ρe(C1)⊔ρe(C2)⊔⋯⊔ρe(Ck).
        </list-item>
       </list>
       <paragraph label="Proposition 11">
        [14]{a mathematical formula}ρeis a relaxation.
       </paragraph>
       <paragraph>
        Let us illustrate this operator with an example.
       </paragraph>
       <paragraph label="Example 3">
        Suppose an agent believes that a person {an inline-figure} is married to a female judge: {an inline-figure}. Suppose now that due to some obscurantist law, it happens that females are not allowed to be judges. This new belief is captured as {an inline-figure}. By applying {a mathematical formula}ρe one can resolve the conflict between the two belief sets. To ease the reading, let us rewrite the concepts as follows: {an inline-figure}. Hence, from Definition 15 we have {a mathematical formula}ρe(A⊓D)≡(ρe(A)⊓D)⊔(A⊓ρe(D)), with {a mathematical formula}ρe(A)≡⊤ and{a mathematical formula} Then{a mathematical formula} The new agent's belief, up to a rewriting, becomes{an inline-figure}.
       </paragraph>
       <paragraph>
        One can notice from this example that the relaxation {a mathematical formula}ρe leads to a refined revision operator. Indeed, the resulting relaxed axiom in T emphasizes all the minimal possible changes (through the disjunction operator) on {an inline-figure}'s condition. This is due to the fact that the relaxation operator {a mathematical formula}ρe corresponds to dilating the set of models of a ball defined from an edit distance on the concept description tree of size one. For more details on the correspondence between this relaxation operator, the set of models and tree edit distances, one can refer to [14].
       </paragraph>
       <paragraph>
        Another possibility for defining a relaxation in {a mathematical formula}ELU is obtained by exploiting the disjunction constructor by augmenting a concept description with a set of exceptions.
       </paragraph>
       <paragraph label="Definition 16">
        Relaxation from exceptions in {a mathematical formula}ELUGiven a set of exceptions {a mathematical formula}E={E1,⋯,En}, we define a relaxation of degree k of an {a mathematical formula}ELU-concept description C as follows: for a finite set {a mathematical formula}Ek⊆E with {a mathematical formula}|Ek|=k, C is relaxed by adding the sets {a mathematical formula}Eij∈Ek such that {a mathematical formula}Eij⊓C⊑⊥{a mathematical formula}
       </paragraph>
       <paragraph label="Proof">
        Extensivity of this operator follows directly from the definition.  □
       </paragraph>
       <paragraph>
        However, exhaustivity is not necessarily satisfied unless the exception set includes the ⊤ concept, or the disjunction of some or all of its elements entails the ⊤ concept.
       </paragraph>
       <paragraph>
        If we consider againExample 2, a relaxation of the formula{an inline-figure}using the operator{a mathematical formula}ρEkover the concept{an inline-figure}with the exception set{an inline-figure}results in the formula{an inline-figure}. The new revised knowledge base, if Condition 3 inDefinition 7is not considered, is then{an inline-figure}which is consistent. This is obviously a more refined revision than the one obtained from the operator{a mathematical formula}ρ⊥, but requires the logic to be equipped with the disjunction connective and the definition of a set of exceptions.
       </paragraph>
       <paragraph>
        Another example involving this relaxation will be discussed in the {a mathematical formula}ALC case (cf. Example 4).
       </paragraph>
      </section>
      <section label="4.4.4">
       Relaxation and retraction in {a mathematical formula}ALC
       <paragraph>
        We consider here operators suited to {a mathematical formula}ALC language. Of course, all the operators defined for {a mathematical formula}EL and {a mathematical formula}ELU remain valid.
       </paragraph>
       <section>
        {a mathematical formula}ALC-concept retractions.
        <paragraph>
         A first possibility for defining retraction is to remove iteratively from an {a mathematical formula}ALC-concept description one or a set of its subconcepts. A similar construction has been introduced in [29]. Interestingly enough, almost all the operators defined in [20], [29] are relaxations.
        </paragraph>
        <paragraph label="Definition 17">
         Retraction from exceptions in {a mathematical formula}ALCGiven a set of exceptions {a mathematical formula}E={E1,⋯,En}, we retract any {a mathematical formula}ALC-concept description C by constraining it to the elements {a mathematical formula}Eic such that {a mathematical formula}Ei⊑C:{a mathematical formula}
        </paragraph>
        <paragraph label="Proof">
         The proof follows directly from the definition.  □
        </paragraph>
        <paragraph>
         As for its counterpart relaxation ({a mathematical formula}ρEk), exhaustivity of {a mathematical formula}κEn is not necessarily satisfied unless the exception set includes the ⊥ concept, or the conjunction of some or all of its elements entails the ⊥ concept.
        </paragraph>
        <paragraph>
         Consider againExample 2. We have{an inline-figure}. The resulting revised knowledge base, if Condition 3 inDefinition 7is not considered, is then{an inline-figure}which is consistent.
        </paragraph>
        <paragraph>
         Another possibility, suggested in [20] and related to operators defined in propositional logic as introduced in [7], consists in applying the retraction at the atomic level. This captures somehow Dalal's idea of revision operators in propositional logic [10].
        </paragraph>
        <paragraph label="Definition 18">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qmrm.D, where {a mathematical formula}Qi is a quantifier and D is quantifier-free and in CNF form,{sup:8} i.e. {a mathematical formula}D=E1⊓E2⊓⋯En with {a mathematical formula}Ei being disjunctions of possibly negated atomic concepts, i.e. {a mathematical formula}Ei=⊔k∈Ξ(i)Ak, where {a mathematical formula}Ξ(i) is the index set of the atomic (possibly negated) concepts {a mathematical formula}Ak forming {a mathematical formula}Ei. We define, as in the propositional case [7], {a mathematical formula}κ(Ei)=⊓k∈Ξ(i)⊔j∈Ξ(i)∖{k}Aj and {a mathematical formula}κpn(D)=⊓i∈{1...n}κ(Ei). Then we set {a mathematical formula}κDalal(C)=Q1r1⋯Qmrm.κp(D).
        </paragraph>
        <paragraph label="Proof">
         {a mathematical formula}κDalalnis a retraction.Exhaustivity and anti-extensivity follow from those of {a mathematical formula}κp. Indeed the operator {a mathematical formula}κp is exhaustive and anti-extensive, and if applied n times it reaches the ⊥ concept (see [7] for properties of this operator).  □
        </paragraph>
        <paragraph>
         This idea can be generalized to consider any retraction defined in {a mathematical formula}ELU.
        </paragraph>
        <paragraph label="Definition 19">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qmrm.D, where {a mathematical formula}Qi is a quantifier and D is quantifier-free.Then we define {a mathematical formula}κ∩(C)=Q1r1⋯Qmrm.κEn(D).
        </paragraph>
        <paragraph label="Proof">
         {a mathematical formula}κ∩nis anti-extensive.The properties of this operator follows from the ones of {a mathematical formula}κEn(D). Hence, anti-extensivity is verified but not necessarily exhaustivity.  □
        </paragraph>
        <paragraph>
         Another possible {a mathematical formula}ALC-concept description retraction is obtained by substituting the existential restriction by an universal one. This idea has been sketched in [20] for defining dilation operators by transforming ∀ into ∃, i.e. special relaxation operators enjoying additional properties [14], and also used for defining revision in FOL (see Section 4.3). We adapt it here, by transforming ∃ into ∀, to define retraction in DL syntax.
        </paragraph>
        <paragraph label="Definition 20">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qnrn.D, where {a mathematical formula}Qi is a quantifier, D is quantifier-free, then we define{a mathematical formula}
        </paragraph>
        <paragraph label="Proposition 16">
         {a mathematical formula}κqis anti-extensive.
        </paragraph>
        <paragraph label="Proof">
         See Appendix.  □
        </paragraph>
        <paragraph>
         Note that for {a mathematical formula}κq exhaustivity can be obtained by further removing recursively the remaining universal quantifiers and apply at the final step any retraction defined above on the concept D.
        </paragraph>
       </section>
       <section>
        {a mathematical formula}ALC-concept relaxations.
        <paragraph>
         Let us now introduce some relaxation operators suited to {a mathematical formula}ALC language.
        </paragraph>
        <paragraph label="Definition 21">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qmrm.D, where {a mathematical formula}Qi is a quantifier and D is quantifier-free and in DNF form, i.e. {a mathematical formula}D=E1⊔E2⊔⋯En with {a mathematical formula}Ei being a conjunction of possibly negated atomic concepts, i.e. {a mathematical formula}Ei=⊓k∈Ξ(i)Ak, where {a mathematical formula}Ξ(i) is the index set of the atomic (possibly negated) concepts {a mathematical formula}Ak forming {a mathematical formula}Ei. We define {a mathematical formula}ρ(Ei)=⊔k∈Ξ(i)⊓j∈Ξ(i)∖{k}Aj and {a mathematical formula}ρpn(D)=⊔i∈{1...n}ρ(Ei), as in the propositional case [7], and then {a mathematical formula}ρDalaln(C)=Q1r1⋯Qmrm.ρpn(D).
        </paragraph>
        <paragraph>
         As for retraction, this idea can be generalized to consider any relaxation defined in {a mathematical formula}ELU.
        </paragraph>
        <paragraph label="Definition 22">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qnrn.D, where {a mathematical formula}Qi is a quantifier and D is quantifier-free, then we define {a mathematical formula}ρ∪n(C)=Q1r1⋯Qnrn.ρEn(D).
        </paragraph>
        <paragraph>
         Let us consider another example adapted from the literature to illustrate these operators [29].
        </paragraph>
        <paragraph label="Example 4">
         Let us consider the following knowledge bases: {an inline-figure} and {an inline-figure} (we consider here individuals as concepts). Relaxing the formula {an inline-figure} by applying {a mathematical formula}ρ∪n to the concept on the right hand side results in the following formula {an inline-figure} which resolves the conflict between the two knowledge bases.
        </paragraph>
        <paragraph>
         A last possibility, dual to the retraction operator given in Definition 20, consists in transforming universal quantifiers into existential ones (as done for relaxation in FOL in Section 4.3).
        </paragraph>
        <paragraph label="Definition 23">
         Let C be an {a mathematical formula}ALC-concept description of the form {a mathematical formula}Q1r1⋯Qnrn.D, where {a mathematical formula}Qi is a quantifier and D is quantifier-free, then we define a relaxation as:{a mathematical formula} If we consider again Example 4, relaxing the formula {an inline-figure} by applying {a mathematical formula}ρq to the concept on the right hand side results in the following formula {an inline-figure}, which resolves the conflict between the two knowledge bases.
        </paragraph>
        <paragraph label="Proof">
         The operators{a mathematical formula}ρDalaland{a mathematical formula}ρqare extensive and exhaustive. The operator{a mathematical formula}ρ∪is extensive but not exhaustive.The properties of {a mathematical formula}ρDalal and {a mathematical formula}ρ∪ are directly derived from the definitions and from properties of {a mathematical formula}ρp detailed in [7] and {a mathematical formula}ρE. The proof of {a mathematical formula}ρq being extensive and exhaustive can be found in [20].  □
        </paragraph>
       </section>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Recently a first generalization of AGM revision has been proposed in the framework of Tarskian logics considering minimality criteria on removed formulas [34] following previous works of the same authors for contraction [35]. Representation results that make a correspondence between a large family of logics containing non-classical logics such as DL and HCL and AGM postulates for revision with such minimality criteria have then been obtained. Here, the proposed generalization also gives similar representation theorems (cf. Theorem 1) but for a different minimality criterion. Indeed, we showed in Section 3.2 that revision operators satisfying the weakened AGM postulates are precisely the ones that accomplish an update with minimal change to the set of models of knowledge bases, generalizing the approach developed in [22] for the logic PL and [30] for DL. However, our revision operator based on relaxation also has a minimality criterion on transformed formulas. Indeed, a simple consequence of Definition 7 is the property
     </paragraph>
     <paragraph>
      (Relevance) Let {a mathematical formula}T,T′⊆Sen be two knowledge bases such that {a mathematical formula}T∘T′=ρK(T)∪T′. Then, for every {a mathematical formula}φ∈T such that {a mathematical formula}kφ≠0, {a mathematical formula}ρK′(T)∪T′ is inconsistent for {a mathematical formula}K′=K∖{kφ}∪{kφ′=0}.
     </paragraph>
     <paragraph>
      This property states that only formulas that contribute to inconsistencies with {a mathematical formula}T′ are allowed to be transformed. Our property (Relevance) is similar to the property with the same name in [34], [35], but for contraction operators, and that states that only the formulas that somehow “contribute” to derive the formulas to abandon can be removed.
     </paragraph>
     <paragraph>
      Since the primary aim of this paper is to show that a more general framework, encompassing different logics, can be useful, it is out of the scope of this paper to provide an overview of all existing relaxation methods. However, some works deserve to be mentioned, since they are based on ideas that show some similarity with the relaxation notion proposed in our framework.
     </paragraph>
     <paragraph>
      The relaxation idea originates from the work on Morpho-Logics, initially introduced in [7], [8]. In this seminal work, revision operators (and explanatory relations) were defined through dilation and erosion operators. These operators share some similarities with relaxation and retraction as defined in this paper. Dilation is a sup-preserving operator and erosion is inf-preserving, hence both are increasing. Some particular dilations and erosions are exhaustive and extensive while relaxation and retraction operators are defined to be exhaustive and extensive but not necessarily sup- and inf-preserving. Dilation has been further exploited for merging first-order theories in [20].
     </paragraph>
     <paragraph>
      In [1], the notion of partial meet contraction is defined as the intersection of a non-empty family of maximal subsets of the theory that do not imply the proposition to be eliminated. Revision is then defined from the Levi identity. The maximal subsets can also be selected according to some choice function. The authors also define a notion of partial meet revision, which can be seen as a special case of the relaxation operator introduced in this paper. In [21], the author also discusses choice functions and compares the postulates for partial meet revision to the AGM postulates. He also highlights the distinction between belief sets (which can be very large) and belief bases (which are not necessarily closed by Cn). More precisely, A is a belief base of a belief set K iff {a mathematical formula}K=Cn(A). A permissive belief revision is defined in [9], based on the notion of weakening. The beliefs which are suppressed by classical revision methods are replaced by weaker forms, which keep the resulting belief set consistent. This notion of weakening is closed to the one of relaxation developed in this paper. In the last decade, several works have studied revision operators in description logics. While most of them concentrated on the adaptation of the AGM theory, few works have addressed the definition of concrete operators [25], [27], [28], [29]. For instance, in [25], based on the seminal work in [5], revision in DL is studied by defining strategies to manage inconsistencies and using the notion of knowledge integration (see also the work by Hansson). The authors propose a conjunctive maxi-adjustment, for stratified knowledge bases and lexicographic entailment. In [28], weakening operators, that are in fact relaxation operators, are defined. Our work brings a principled formal flavor to these operators. In [27], revision of ontologies in DL is based on the notion of forgetting, which is also a way to manage inconsistencies. The authors propose a model based approach, inspired by Dalal's revision in PL, and based on a distance between terminologies and on the difference set between two interpretations. The models of the revision {a mathematical formula}T∘T′ are then the interpretations {a mathematical formula}I for which there exists an interpretation {a mathematical formula}I′ such that the cardinality of the difference set between {a mathematical formula}I and {a mathematical formula}I′ is equal to the distance between T and {a mathematical formula}T′. In [24], updating Aboxes in DL is discussed, and some operators are introduced. The rationality of these operators is not discussed, hence the interest of a formal theory such as the AGM postulates. In [2] an original use of DL revision is introduced for the orchestration of processes. A closely related field is inconsistency handling in ontologies (e.g. [36], [37]), with the main difference that the rationality of inconsistency repairing operators is not investigated, as suggested by the AGM theory.
     </paragraph>
     <paragraph>
      As previously highlighted, some of our DL-based relaxation operators are closely related to the ones introduced in [29] for knowledge bases revision. Our relaxation-based revision framework, being abstract enough (i.e. defined through easily satisfied properties), encompasses these operators. Moreover, the revision operator defined in [29] considers only inconsistencies due to Abox assertions. Our operators are general in the sense that Abox assertions are handled as any formula of the language.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix">
     <section-title>
      Proofs of the main results
     </section-title>
     <paragraph>
      Proof ofProposition 3. Let us suppose that {a mathematical formula}Cn(T1′)=Cn(T2′). Here, three cases have to be considered:
     </paragraph>
     <list>
      <list-item label="(1)">
       One of {a mathematical formula}T1′ and {a mathematical formula}T2′ is inconsistent (say {a mathematical formula}T1′ without loss of generality). Since {a mathematical formula}Cn(T1′)=Cn(T2′) by hypothesis, {a mathematical formula}T2′ is also inconsistent. By Postulate (G2), we then have that, for {a mathematical formula}i=1,2, {a mathematical formula}Mod(T∘Ti′)⊆Mod(Ti′), and {a mathematical formula}Mod(Ti′)=Triv (Corollary 1). Hence {a mathematical formula}Mod(T∘Ti′)⊆Triv, and {a mathematical formula}Mod(T∘T1′)=Mod(T∘T2′)=Triv.
      </list-item>
      <list-item label="(2)">
       Both {a mathematical formula}T∪T1′ and {a mathematical formula}T∪T1′ are consistent. Since {a mathematical formula}Cn(T1′)=Cn(T2′), we know that {a mathematical formula}Mod(T1′)=Mod(T2′) (Equation (1)), and then {a mathematical formula}Mod(T∪T1′)=Mod(T∪T2′). Therefore, by Postulate (G3), we have that {a mathematical formula}Mod(T∘T1′)=Mod(T∘T2′).
      </list-item>
      <list-item label="(3)">
       {a mathematical formula}T1′ and {a mathematical formula}T2′ are consistent but {a mathematical formula}T∪T1′ or {a mathematical formula}T∪T2′ is not (say {a mathematical formula}T∪T1′). From {a mathematical formula}Cn(T1′)=Cn(T2′), we derive that {a mathematical formula}T∪T2′ is also inconsistent. By Postulate (G1), both {a mathematical formula}T∘T1′ and {a mathematical formula}T∘T2′ are consistent. Let {a mathematical formula}M∈Mod(T∘T1′). If {a mathematical formula}M∈Triv, then obviously {a mathematical formula}M∈Mod(T∘T2′). Therefore, let us suppose that {a mathematical formula}M∉Triv. By Postulate (G2), {a mathematical formula}M∈Mod(T1′), and then {a mathematical formula}M∈Mod(T2′). Let {a mathematical formula}M′∈Mod(T∘T2′)∖Triv. Such a model exists as {a mathematical formula}T∘T2′ is consistent. By Postulate (G2) and the hypothesis that {a mathematical formula}Cn(T1′)=Cn(T2′), {a mathematical formula}{M,M′}⁎ contains both {a mathematical formula}T1′ and {a mathematical formula}T2′. Obviously, we have that {a mathematical formula}(T∘T1′)∪{M,M′}⁎ and {a mathematical formula}(T∘T2′)∪{M,M′}⁎ are consistent. Therefore, by Postulates (G5) and (G6), we have that {a mathematical formula}Mod((T∘T1′)∪{M,M′}⁎)=Mod((T∘(T1′∪{M,M′}⁎)=Mod(T∘{M,M′}⁎) and {a mathematical formula}Mod((T∘T2′)∪{M,M′}⁎)=Mod((T∘(T2′∪{M,M′}⁎)=Mod(T∘{M,M′}⁎). We can then derive that {a mathematical formula}Mod((T∘T1′)∪{M,M′}⁎)=Mod((T∘T2′)∪{M,M′}⁎), and conclude that {a mathematical formula}M∈Mod(T∘T2′). Similarly, by reversing the roles of {a mathematical formula}T1′ and {a mathematical formula}T2′, if {a mathematical formula}M∈Mod(T∘T2′), we can conclude that {a mathematical formula}M∈Mod(T∘T1′).
      </list-item>
     </list>
     <paragraph>
      Proof ofTheorem 1.
     </paragraph>
     <list>
      <list-item label="(1)">
       Let us suppose that ∘ satisfies AGM Postulates. For every knowledge base T, let us define the binary relation {a mathematical formula}⪯T⊆Mod×Mod by: for all {a mathematical formula}M,M′∈Mod,{a mathematical formula}Let us first show that {a mathematical formula}⪯T satisfies the two conditions of FA.
       <list>
        The first condition easily follows from the definition of {a mathematical formula}⪯T.To prove the second one, let us assume that {a mathematical formula}M∈Mod(T) and {a mathematical formula}M′∉Mod(T). Since {a mathematical formula}M∈Mod(T), we have {a mathematical formula}M⪯TM′. Here two cases have to be considered:Let us now prove the three supplementary conditions.
       </list>
       <list>
        <list-item label="•">
         First, let us show that {a mathematical formula}Mod(T∘T′)=Min(Mod(T′)∖Triv,⪯T). If {a mathematical formula}T′ is inconsistent, then by Proposition 2{a mathematical formula}Mod(T′)∖Triv=∅, and by (G2) {a mathematical formula}Mod(T∘T′)⊆Mod(T′)⊆Triv, hence {a mathematical formula}Mod(T∘T′)∖Triv=∅=Min(Mod(T′)∖Triv,⪯T).Let us assume now that {a mathematical formula}T′ is consistent.
        </list-item>
        <list-item label="•">
         Secondly, let us show that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)≠∅ if {a mathematical formula}T′ is consistent. By Postulate (G1), we have that {a mathematical formula}T∘T′ is consistent, and then {a mathematical formula}Mod(T∘T′)∖Triv≠∅. We can directly conclude by the previous point that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)≠∅.
        </list-item>
        <list-item label="•">
         Finally, let us show that for every {a mathematical formula}T′,T″⊆Sen, {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)∩Mod(T″)=Min(Mod(T′∪T″)∖Triv,⪯T) if {a mathematical formula}(T∘T′)∪T″ is consistent. By (G5) and (G6), we have that {a mathematical formula}Mod(T∘(T′∪T″))=Mod((T∘T′)∪T″). Therefore, by the first point, we can directly conclude that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)∩Mod(T″)=Min(Mod(T′∪T″)∖Triv,⪯T).
        </list-item>
       </list>
      </list-item>
      <list-item label="(2)">
       Let us now suppose that for a revision operation ∘ there exists a FA which maps any knowledge base {a mathematical formula}T⊆Sen to a binary relation {a mathematical formula}⪯T⊆Mod×Mod satisfying the three conditions of Theorem 1. Let us prove that ∘ verifies the AGM Postulates.
      </list-item>
     </list>
     <paragraph>
      Proof of Theorem 2. First, let us show that f is a FA.
     </paragraph>
     <list>
      <list-item label="•">
       Let {a mathematical formula}M,M′∈Mod(T). Let us suppose that {a mathematical formula}M≺TM′. This means that there exists {a mathematical formula}T′⊆Sen such that {a mathematical formula}M,M′∈Mod(T′), {a mathematical formula}M∈Mod(T∘T′) and {a mathematical formula}M′∉Mod(T∘T′). Hence we have that {a mathematical formula}T∪T′ is consistent, and then by Postulate (G3), {a mathematical formula}T∘T′=T∪T′. We then have that {a mathematical formula}M′∈Mod(T∘T′) which is a contradiction.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}M∈Mod(T) and let {a mathematical formula}M′∈Mod∖Mod(T). We have that {a mathematical formula}M⪯T∅M′, and then {a mathematical formula}M⪯TM′ by definition of {a mathematical formula}⪯T. Now, let us suppose that {a mathematical formula}M′⪯TM. This means that there exists {a mathematical formula}T′⊆Sen such that {a mathematical formula}M,M′∈Mod(T′), {a mathematical formula}M′∈Mod(T∘T′) and {a mathematical formula}M∉Mod(T∘T′). But, as {a mathematical formula}M∈Mod(T), we have that {a mathematical formula}T∪T′ is consistent, and then by Postulate (G3), {a mathematical formula}T∘T′=T∪T′. Hence, we have that {a mathematical formula}M∈Mod(T∘T′) which is a contradiction.
      </list-item>
     </list>
     <paragraph>
      Let us show now the supplementary conditions of Theorem 1.
     </paragraph>
     <list>
      <list-item label="•">
       First, let us show that {a mathematical formula}Mod(T∘T′)∖Triv=Min(Mod(T′)∖Triv,⪯T). The case where {a mathematical formula}T′ is inconsistent follows the same proof as in Theorem 1.Let us suppose that {a mathematical formula}T′ is consistent. Let {a mathematical formula}M∈Mod(T∘T′)∖Triv. Let us suppose that {a mathematical formula}M∉Min(Mod(T′)∖Triv,⪯T). This means that there exists {a mathematical formula}M′∈Mod(T′)∖Triv such that {a mathematical formula}M′≺TM. Therefore, there exists {a mathematical formula}T″⊆Sen such that {a mathematical formula}M,M′∈Mod(T″), {a mathematical formula}M′∈Mod(T∘T″) and {a mathematical formula}M∉Mod(T∘T″). Hence, both {a mathematical formula}(T∘T′)∪T″ and {a mathematical formula}(T∘T″)∪T′ are consistent, and then by Postulates (G5) and (G6), {a mathematical formula}Mod((T∘T′)∪T″)=Mod((T∘T″)∪T′)=Mod(T∘(T′∪T″)). We can then derive that {a mathematical formula}M∈Mod(T∘T″) which is a contradiction.Let {a mathematical formula}M∈Min(Mod(T′)∖Triv,⪯T). Let us suppose that {a mathematical formula}M∉Mod(T∘T′)∖Triv. As {a mathematical formula}T′ is consistent, by Postulates (G1) and (G2), there exists {a mathematical formula}M′∈Mod(T∘T′)∖Triv. By definition of {a mathematical formula}⪯TT′, we have that {a mathematical formula}M′⪯TT′M, and then {a mathematical formula}M′⪯TM which is a contradiction.
      </list-item>
      <list-item label="•">
       The proof of the two other conditions corresponds to the one given in Theorem 1.
      </list-item>
     </list>
     <paragraph>
      Proof ofProposition 4. It is sufficient to show that {a mathematical formula}⪯T1∪⪯T2 and {a mathematical formula}⪯T1∩⪯T2 satisfy Conditions (1) and (2) of Definition 4 plus all the conditions of Theorem 1.
     </paragraph>
     <paragraph>
      Let us first show that they are FA. Let {a mathematical formula}T⊆Sen. Let {a mathematical formula}M,M′∈Mod(T). By definition of FA, then we have either {a mathematical formula}M⪯̸TiM′ and {a mathematical formula}M′⪯̸TiM or {a mathematical formula}M⪯TiM′ and {a mathematical formula}M′⪯TiM for {a mathematical formula}i=1,2. We then have four cases to consider, but for {a mathematical formula}f1⊓f2(T)=⪯T (resp. {a mathematical formula}f1⊔f2(T)=⪯T), we always end up at either {a mathematical formula}M⪯̸TM′ and {a mathematical formula}M′⪯̸TM or {a mathematical formula}M⪯TM′ and {a mathematical formula}M′⪯TM. Likewise, for every {a mathematical formula}M∈Mod(T) and every {a mathematical formula}M′∈Mod∖Mod(T), we have that {a mathematical formula}M≺TiM′ for {a mathematical formula}i=1,2. Therefore, it is obvious to conclude that {a mathematical formula}M≺TM′.
     </paragraph>
     <paragraph>
      Now, by the first supplementary condition for {a mathematical formula}⪯T1 and {a mathematical formula}⪯T2 in Theorem 1, we have for every {a mathematical formula}T′⊆Sen that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T1)=Min(Mod(T′)∖Triv,⪯T2){a mathematical formula}=Mod(T∘T′)∖Triv. Hence, we can write that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T1∪⪯T2)=Min(Mod(T′)∖Triv,⪯T1∩⪯T2)=Min(Mod(T′)∖Triv,⪯Ti) for {a mathematical formula}i=1,2. The three supplementary conditions are then straightforward, and this allows us to directly conclude that {a mathematical formula}f1⊔f2 and {a mathematical formula}f1⊓f2 are FA+.
     </paragraph>
     <paragraph>
      Proof ofTheorem 3. ∘ obviously satisfies Postulates (G1), (G2) and (G3). To prove (G5)–(G6), let us suppose {a mathematical formula}T,T′,T″⊆Sen such that {a mathematical formula}(T∘T′)∪T″ is consistent (the case where {a mathematical formula}(T∘T′)∪T″ is inconsistent is obvious). This means that {a mathematical formula}ρKTT′(T)∪T′∪T″ is consistent. Now, obviously we have that {a mathematical formula}Mod(T′∪T″)⊆Mod(T′). Hence, by the second and the third conditions of Definition 7, we necessarily have that {a mathematical formula}T∘(T′∪T″)=ρKTT′(T)∪T′∪T″, and then {a mathematical formula}Mod((T∘T′)∪T″)=Mod(T∘(T′∪T″)).
     </paragraph>
     <paragraph>
      Proof ofTheorem 4. Let {a mathematical formula}T⊆Sen. Let us first show that {a mathematical formula}fρ(T)=⪯T is faithful.
     </paragraph>
     <list>
      <list-item label="•">
       Obviously, we have for every {a mathematical formula}M,M′∈Mod(T) and every {a mathematical formula}T′⊆Sen that both {a mathematical formula}M⪯̸TT′M′ and {a mathematical formula}M′⪯̸TT′M. Hence the same relations hold for {a mathematical formula}⪯T.
      </list-item>
      <list-item label="•">
       Let {a mathematical formula}M∈Mod(T) and let {a mathematical formula}M′∈Mod∖Mod(T). Obviously, we have that {a mathematical formula}M⪯T∅M′. Let {a mathematical formula}T′⊆Sen such that {a mathematical formula}M,M′∈Mod(T′) (the case where for all {a mathematical formula}T′⊆Sen{a mathematical formula}M or {a mathematical formula}M′ is not in {a mathematical formula}Mod(T′) implies that {a mathematical formula}M and {a mathematical formula}M′ are incomparable by {a mathematical formula}⪯TT′, and then we directly have that {a mathematical formula}M′⪯̸TM). Here two cases have to be considered:
      </list-item>
     </list>
     <paragraph>
      Let us prove that {a mathematical formula}Mod(T∘T′)∖Triv=Min(Mod(T′)∖Triv,⪯T). This will directly prove that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)≠∅ when {a mathematical formula}T′ is consistent. Indeed, by definition, we have that {a mathematical formula}T∘T′ is consistent when {a mathematical formula}T′ is consistent, and then {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)≠∅ if {a mathematical formula}Mod(T∘T′)∖Triv=Min(Mod(T′)∖Triv,⪯T).
     </paragraph>
     <paragraph>
      If {a mathematical formula}T′ is inconsistent, then so is {a mathematical formula}T∘T′ by definition. Hence, {a mathematical formula}Mod(T∘T′)∖Triv=Min(Mod(T′)∖Triv,⪯T)=∅.
     </paragraph>
     <paragraph>
      Let us now suppose that {a mathematical formula}T′ is consistent.
     </paragraph>
     <list>
      <list-item label="•">
       Let us show that {a mathematical formula}Mod(T∘T′)∖Triv⊆Min(Mod(T′)∖Triv,⪯T). Let {a mathematical formula}M∈Mod(T∘T′)∖Triv. Let {a mathematical formula}M′∈Mod(T′)∖Triv. Two cases have to be considered:
      </list-item>
      <list-item label="•">
       Let us now show that {a mathematical formula}Min(Mod(T′)∖Triv,⪯T)⊆Mod(T∘T′)∖Triv. Let {a mathematical formula}M∈Min(Mod(T′)∖Triv,⪯T). Let us suppose that {a mathematical formula}M∉Mod(T∘T′)∖Triv. As {a mathematical formula}T′ is consistent, then so is {a mathematical formula}T∘T′. Hence, there exists {a mathematical formula}M′∈Mod(T∘T′)∖Triv. As {a mathematical formula}M∈Mod(T′)∖Mod(T∘T′), we have that {a mathematical formula}M′⪯TT′M, and then as {a mathematical formula}M∈Min(Mod(T′)∖Triv,⪯T) we also have that {a mathematical formula}M⪯TM′. This means that there exists {a mathematical formula}T″⊆Sen such that {a mathematical formula}M,M′∈Mod(T″) and {a mathematical formula}M⪯TT″M′. By hypothesis, we then have that {a mathematical formula}(T∘T′)∪T″ is consistent. Therefore, by Conditions 2 and 3 of Definition 7, we have that {a mathematical formula}(T∘T′)∪T″=T∘(T′∪T″). Hence, we also have that {a mathematical formula}T∘(T′∪T″)=ρKTT′(T)∪T′∪T″. Consequently, we have by Condition 3 of Definition 7 that {a mathematical formula}KTT″≤KTT′. Hence, there exists {a mathematical formula}K″≥KTT″ such that {a mathematical formula}K″&lt;KTT′ and {a mathematical formula}M∈Mod(ρK″(T)). We can then deduce that {a mathematical formula}ρK″(T)∪T′ is consistent, and then by Condition 2 of Definition 7 we have that {a mathematical formula}∑KTT′≤∑K″, which is a contradiction.
      </list-item>
     </list>
     <paragraph>
      Finally, to prove the last point, we follow the same steps as in the proof of Theorem 1.
     </paragraph>
     <paragraph>
      Proof of Proposition 15. The proof relies on the following general result:{a mathematical formula} Indeed, for each interpretation {a mathematical formula}I, if {a mathematical formula}riI≠∅, we have{a mathematical formula} Hence {a mathematical formula}(∀r.C)I⊆(∃r.C)I for each {a mathematical formula}I (if {a mathematical formula}riI=∅ it is obvious), and {a mathematical formula}∀r.C⊑∃r.C.
     </paragraph>
     <paragraph>
      In a similar way, we can show, that for any {a mathematical formula}C1,C2,r, and {a mathematical formula}Q∈{∃,∀}:{a mathematical formula}
     </paragraph>
     <paragraph>
      Now, let us consider any j such that {a mathematical formula}Qj=∃, and set {a mathematical formula}C′=Qj+1rj+1...Qnrn.D. We have from the first result {a mathematical formula}Qj′rj.C′⊑Qjrj.C′. Applying the second result recursively on each {a mathematical formula}Qi for {a mathematical formula}i&lt;j, we then have{a mathematical formula}The same relation holds for the conjunction over any j such that {a mathematical formula}Qj=∃, from which we conclude that {a mathematical formula}∀C,κq(C)⊑C, i.e. {a mathematical formula}κq is anti-extensive.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>