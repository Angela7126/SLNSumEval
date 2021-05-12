<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Enhancing context knowledge repositories with justifiable exceptions.
   </title>
   <abstract>
    Dealing with context dependent knowledge is a well-known area of study that roots in John McCarthy's seminal work. More recently, the Contextualized Knowledge Repository (CKR) framework has been conceived as a logic-based approach in which knowledge bases have a two layered structure, modeled by a global context and a set of local contexts. The global context not only contains the meta-knowledge defining the properties of local contexts, but also holds the global (context independent) object knowledge that is shared by all of the local contexts. In many practical cases, however, it is desirable to leave the possibility to “override” the global object knowledge at the local level: in other words, it is interesting to recognize the pieces of knowledge that can admit exceptional instances in the local contexts that do not need to satisfy the general axiom. To address this need, we present in this paper an extension of CKR in which defeasible axioms can be included in the global context. The latter are verified in the local contexts only for the instances for which no exception to overriding exists, where exceptions require a justification in terms of facts that are provable from the knowledge base. We formally define this semantics and study some semantic and computational properties, where we characterize the complexity of the major reasoning tasks, among them satisfiability testing, instance checking, and conjunctive query answering. Furthermore, we present a translation of extended CKRs with knowledge bases in the Description Logic SROIQ-RL under the novel semantics to datalog programs under the stable model (answer set) semantics. We also present an implementation prototype and examine its scalability with respect to the size of the input CKR and the amount (level) of defeasibility in experiments. Finally, we compare our representation approach with some major formalisms for expressing defeasible knowledge in Description Logics and contextual knowledge representation. Our work adds to the body of results on using deductive database technology such as SQL and datalog in these areas, and provides an expressive formalism (in terms of intrinsic complexity) for exception handling by overriding.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In the field of Knowledge Representation and Reasoning, the problem of dealing with context dependent knowledge is a well-known area of study. Initial proposals for a formal definition of contextual knowledge and reasoning date back to the works of McCarthy [4], Lenat [5], and Giunchiglia et al. [6], [7]. In the era of the Semantic Web (SW), representation of context dependent knowledge has been recognized as an extremely relevant issue, due to the necessity to qualify each data set with meta-data to allow users and applications to interpret the data set contents in the right context. This interest has led to a number of logic based proposals, e.g. [8], [9], [10], [11], [12], [13], [14], [15]. In the current article we will extend one of the current formalisms, the Contextualized Knowledge Repository (CKR) framework[12], [16], [17], with its latest formulation in [1], with a new form of non monotonic reasoning based on justification.
     </paragraph>
     <paragraph>
      A CKR knowledge base is a two-layer structure: the higher level consists of a global context; the lower level consists of a set of local contexts. For example, a CKR for a touristic recommendation system in the Trentino region,{sup:1} is composed of a global context that describes all the locations, the venues and the events that are available in the region, and by a set of local contexts each of which describes the details of an event or the profile, interests and plans of a single user. The global context contains two types of knowledge: the former is composed by a context independent kernel of facts about the domain of discourse. The truth of these pieces of knowledge is assumed to be immutable; for instance, the fact that Castello del Buonconsiglio is located in Trento. This knowledge is accessible by all the local contexts. The second type of knowledge contained in the global context, is meta-knowledge specifying the properties of local contexts. Local contexts, on the other hand, contain knowledge that holds under specific circumstances or assumptions (e.g. during a certain period of time, or when a certain event occurs) and thus they represent different partial and perspective views of the domain. Knowledge in different contexts is not completely independent, as the global context independent knowledge is propagated from the global to the local contexts and it is used to constrain local knowledge in different contexts.
     </paragraph>
     <paragraph>
      In many practical cases, however, it is desirable to leave the possibility to “override” the global object knowledge at the local level, by allowing axioms to admit exceptions in their local instantiations. For example, in the above scenario of the event recommendation system, we might want to assert at the global level that “by default, all of the cheap events are interesting”, but then override this implication for particular kind of events in the context of a specific participant. (e.g., a user might not be interested in sport events independently of their price). We might also want to express defeasibility on the propagation of information: for instance, in a CKR representing an organization, we might want to express that “by default, all the employees of a year will be employees in the next year” and override the axiom in the context of a specific year for employees that finished their working contract.{sup:2} In other words, we want to allow certain global axioms to be defeasible, so that they admit exceptional instances in local contexts, while holding in the general case: this clearly requires to add a notion of non-monotonicity across the global and the local parts of a CKR.
     </paragraph>
     <paragraph>
      The aim of this work is thus to extend the CKR framework in order to support the form of defeasibility for global object knowledge as described above, under some desiderata: (1) defeasibility should be used parsimoniously, in the sense that information is inherited as much as possible, such that the information loss in conclusions at the local level is as little as necessary; (2) overriding should be supported by clear evidence, in terms of facts that lead to a contradiction; and (3) reasoning with exceptions should be realized using deductive database technology, in particular SQL and datalog, that has been fostered for CKRs [1] in line with work around Description Logics [18], [19], [20], [21], [22], [23], [24].
     </paragraph>
     <paragraph>
      To this end, we introduce defeasible axioms guided by the approach of inheritance logic programs in [25], extending the datalog representation of CKR semantics in [1]. In inheritance logic programs the idea is that special rules recognize exceptional facts at the local level and others propagate global facts only if they are not proved to be overridden at the local level, which happens if the opposite is derived; in the same vein, we consider instances of axioms that might be overridden at the local level. On the basis of this semantics, we develop a translation for CKRs on {a mathematical formula}SROIQ-RL (i.e. OWL-RL [26]) with defeasible axioms into datalog programs. Specifically, instance checking over a CKR reduces this way to (cautious) inference from such programs under the answer set semantics [27] (also known as stable model semantics [28]), which thus can be used to implement query answering for CKR with defeasibility.
     </paragraph>
     <paragraph>
      The main contributions of this paper are briefly summarized as follows:
     </paragraph>
     <paragraph>
      (1) We present a new syntax and semantics of an extension of CKR for defeasible axioms{a mathematical formula}D(α) in the global context. Notably, this allow us to introduce for the first time a notion of non-monotonicity across contexts in CKR (Section 3). Intuitively, a global defeasible axiom {a mathematical formula}D(α) means that, at the level of instantiations for individuals, α is inherited by local contexts unless it generates a contradiction in the local context knowledge base. Model based semantics of CKR needs thus to be extended in order to reason with exceptions for such axioms. Axiom instances {a mathematical formula}α(e) representing local exceptions are called clashing assumptions: in the evaluation of α at a local context, its instantiation with e is not considered (i.e. α is “overridden” for e). However, such assumptions of exceptions must be justified: the instance of α for e must be provable to be unsatisfiable at the local context. This is ensured if (atomic) assertions can be derived which prove this unsatisfiability; we call such assertions clashing sets (cf. Section 3.2). As such, CKR interpretations are thus extended with a set of the local clashing assumptions CAS and called CAS-interpretations: intuitively, CAS-interpretations interpret local axioms by disregarding exceptional instances in CAS (cf. Section 3.2.1). Then, CKR models can be defined as those CAS-models that are justified, i.e. that provide a reason for the presence of each clashing assumption in CAS by verifying a correspondent local clashing set.
     </paragraph>
     <paragraph>
      (2) We characterize reasoning in CKR with defeasible axioms, where we consider entailment of axioms and conjunctive queries (CQs) (Section 4). In details, we derive helpful semantic characterizations of justified clashing assumptions; based on this, we study the computational complexity of major reasoning tasks. We show that justified CAS- and CKR-model checking are tractable, while satisfiability is NP-complete in general. Under data complexity, entailment of axioms is coNP-complete while answering conjunctive queries is {a mathematical formula}Π2p-complete, with lower complexity for restricted inputs.
     </paragraph>
     <paragraph>
      (3) We extend the datalog translation for {a mathematical formula}SROIQ-RL based CKR from [1] with rules for the translation of defeasible axioms and for considering local exceptions in the propagation of such knowledge (Section 5). We express non-monotonicity using answer set semantics, such that instance checking over a CKR with defeasible axioms reduces to cautious inference from all answer set of the translation, and likewise conjunctive query answering. In particular, we note that the proposed translation (based on positive datalog programs) is not trivial and need special attention for dealing with the negative knowledge inside clashing sets that needs to be derived for the justification of a clashing assumption (in particular in presence of negative disjunctive information, cf. Section 5.2). As a solution to this problem, we propose a translation in which reasoning over such negative knowledge is performed by encoding it through individual proofs by contradiction. In Section 5.3 we show that the proposed translation provides a sound and complete materialization calculus for instance checking and conjunctive query answering over CKRs in OWL-RL.
     </paragraph>
     <paragraph>
      (4) We study scalability of our approach. In particular, the experiments confirm that scalability of the approach is influenced by the percentage of defeasible axioms in the initial CKR and the number of their exceptional instances. To this aim, we have developed a prototype implementation, called CKRew(CKR datalog Rewriter) that compiles a CKR to a datalog program following the presented translation (Section 6). We present the prototype and we study its behavior with respect to different sizes of the input CKR and percentage of defeasible axioms. The prototype and test sets are freely distributed for use, replication of experiments and possible comparison with other similar implementations.
     </paragraph>
     <paragraph>
      The contributions of this work are interesting in general for the area of (logic based) Knowledge Representation: our solution proposes an expressive means for combining reasoning with structured Description Logics knowledge bases (viz. contextualized Semantic Web knowledge bases) with a notion of axiom overriding. As such, our work can be compared not only with respect to methods for representation of defeasibility in contextualized logics (e.g. [9], [29]), but also to solutions for introducing non-monotonic reasoning in Description Logics (e.g. [30], [31]). In Section 7, we provide an extended comparison of our approach with some of the major non-monotonic formalisms for description logics and contextual knowledge representation mentioned above, highlighting commonalities and differences. In particular, our work differs from these formalisms with respect to some relevant aspects:
     </paragraph>
     <list>
      <list-item label="–">
       our approach allows to reason with non-monotonic features in modular knowledge bases under an expressive language (cf. Sections 7.1 and 7.2);
      </list-item>
      <list-item label="–">
       in case of conflicts across possible overridings, it does not request or elicit a preference on possible interpretations, but it presents—in line with the ASP paradigm—alternatives as different models, thus allowing to “reason by cases” on the conflicting solutions (cf. Sections 7.2 and 7.4);
      </list-item>
      <list-item label="–">
       the definition of model is not defined by minimization, but through the idea of justification of exceptions which is based on semantic consequence (cf. Section 7.3). In particular, no “normal” members of a concept are defined, but instead single or tuples of individuals are regarded as “exceptional” w.r.t. defeasible axioms: this allows us to deal with inheritance of properties at the level of instances (cf. Section 7.4);
      </list-item>
      <list-item label="–">
       we provide a translation to datalog that is a direct extension of the materialization calculus approach proposed for the monotonic case in [1] and shows how modular knowledge can be encoded for non-monotonic reasoning using existing tools.
      </list-item>
     </list>
     <paragraph>
      To increase readability, some proofs of technical results have been moved to the Appendix. The prototype and test sets used in the experiments are available on-line at http://ckrew.fbk.eu/.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this section, we recall the relevant languages from description logics (DLs) and from logic programming that underlie the context knowledge repositories presented in the later sections. More specifically, these are {a mathematical formula}SROIQ-RL, which is a fragment of {a mathematical formula}SROIQ[32] corresponding to OWL-RL in [26], and datalog under answer set (i.e., stable model) semantics [27].
     </paragraph>
     <section label="2.1">
      {a mathematical formula}SROIQ syntax and semantics
      <paragraph>
       In the following we assume the usual presentation of description logics [33] and we will consider the logic {a mathematical formula}SROIQ[32]. For ease of reference, the detailed presentation of syntax and semantics for {a mathematical formula}SROIQ constructors and axioms is presented in Table A.13 in the Appendix. We summarize in the following the basic definitions that we will use throughout the paper.
      </paragraph>
      <paragraph>
       A DL vocabulary{a mathematical formula}Σ=NC∪NR∪NI consists of three mutually disjoint countably infinite sets NC of atomic concepts, NR of atomic roles, and NI of individual constants. Complex concepts (complex roles) are recursively defined as the smallest sets containing all concepts and roles that can be inductively constructed using the usual concept constructors ¬, ⊓, ⊔, ∃, ∀ etc. and role constructors {sup:−}, ∘ etc. as usual (see Table A.13).
      </paragraph>
      <paragraph>
       A {a mathematical formula}SROIQknowledge base{a mathematical formula}K=〈T,R,A〉 consists of a TBox {a mathematical formula}T which contains general concept inclusion (GCI) axioms {a mathematical formula}C⊑D and concept equivalence axioms {a mathematical formula}C≡D, where C and D are concepts; an RBox {a mathematical formula}R which contains role inclusion (RIA) axioms {a mathematical formula}S⊑R, reflexivity, and role disjointness axioms, where S and R are roles; and an ABox {a mathematical formula}A which contains assertions of the forms {a mathematical formula}D(a), {a mathematical formula}R(a,b), {a mathematical formula}¬R(a,b), {a mathematical formula}a=b, and {a mathematical formula}a≠b, where a and b are any individual constants (see Table A.13).{sup:3}
      </paragraph>
      <paragraph>
       A DL interpretation is a pair {a mathematical formula}I=〈ΔI,⋅I〉 where {a mathematical formula}ΔI is a non-empty set called interpretation domain and {a mathematical formula}⋅I is the interpretation function which provides denotations for individuals, concepts and roles: it assigns an element {a mathematical formula}aI∈ΔI to each individual constant {a mathematical formula}a∈NI, a subset {a mathematical formula}AI⊆ΔI to each concept {a mathematical formula}A∈NC, and a subset {a mathematical formula}RI⊆ΔI×ΔI to each role {a mathematical formula}R∈NR. Furthermore, {a mathematical formula}⋅I extends to complex concepts and roles as described in Table A.13. An interpretation {a mathematical formula}Isatisfies an axiom (inclusion, assertion etc.) ϕ, denoted {a mathematical formula}I⊨DLϕ, if the respective semantic constraint in Table A.13 is fulfilled; {a mathematical formula}I is a model of {a mathematical formula}K, denoted {a mathematical formula}I⊨DLK, if it satisfies all axioms of {a mathematical formula}K.
      </paragraph>
      <paragraph>
       Furthermore, in the context of {a mathematical formula}K each role in min-cardinality and self restrictions as well as in (ir)reflexivity, asymmetry, and disjointness axioms must be simple[32], which is defined as follows:
      </paragraph>
      <list>
       <list-item label="a)">
        an atomic role R is simple, if it does not occur on the right-hand side of a RIA in {a mathematical formula}R;
       </list-item>
       <list-item label="b)">
        an inverse role {a mathematical formula}R− is simple, if R is simple;
       </list-item>
       <list-item label="c)">
        if R occurs on the right-hand side of a RIA in {a mathematical formula}R and each such RIA is of the form {a mathematical formula}S⊑R where S is simple, then also R is simple.
       </list-item>
      </list>
      <paragraph>
       To preserve decidability, the RBox {a mathematical formula}R in {a mathematical formula}SROIQ knowledge bases is required to be regular[32]. Formally, a regular order is a strict partial order ≺ on roles such that, for any roles {a mathematical formula}R,S, {a mathematical formula}R≺S iff {a mathematical formula}R−≺S. A RIA is ≺-regular if it is in one of the following forms: (i) {a mathematical formula}R∘R⊑R; (ii) {a mathematical formula}R−⊑R; (iii) {a mathematical formula}S1∘…∘Sn⊑R with {a mathematical formula}Si≺R for {a mathematical formula}i∈{1,…,n}; (iv) {a mathematical formula}R∘S1∘…∘Sn⊑R with {a mathematical formula}Si≺R for {a mathematical formula}i∈{1,…,n}; (v) {a mathematical formula}S1∘…∘Sn∘R⊑R with {a mathematical formula}Si≺R for {a mathematical formula}i∈{1,…,n}. An RBox {a mathematical formula}R is regular, if there exists a regular order ≺ such that all role inclusions in {a mathematical formula}R are ≺-regular.
      </paragraph>
      <paragraph>
       For developing our approach, we use without loss of generality the standard name assumption (SNA) in the DL context, cf. [35], [36]: we have an infinite subset {a mathematical formula}NIS⊆NI of individual constants, called standard names such that in every interpretation {a mathematical formula}I we have (i) {a mathematical formula}ΔI=NISI={cI|c∈NIS} and (ii) {a mathematical formula}cI≠dI, for every distinct {a mathematical formula}c,d∈NIS; thus we may assume that {a mathematical formula}ΔI=NIS and {a mathematical formula}cI=c for each {a mathematical formula}c∈NIS. Equality = is then in the FO-translation replaced by a predicate ≈ for which the axioms of a congruence relation are added, i.e., reflexivity, symmetry, transitivity, and {a mathematical formula}∀x.P(x)∧x≈x′→P(x′), where {a mathematical formula}x=x1,…,xn, and {a mathematical formula}x′=x1′,…,xn′ and {a mathematical formula}x≈x′ stands for {a mathematical formula}⋀i=1nxi≈xi′. The standard names are supposed not to occur in the knowledge base, and allow us to access each element in an interpretation, apart from those elements that are “named” by individual constants occurring in a knowledge base (which are from {a mathematical formula}NI∖NIS). The unique name assumption can as usual be enforced by assertions {a mathematical formula}c≠d for all individual constants in {a mathematical formula}NI∖NIS resp. occurring in the knowledge base.
      </paragraph>
      <section label="2.1.1">
       {a mathematical formula}SROIQ-RL
       <paragraph>
        We base our framework on a restriction of the {a mathematical formula}SROIQ syntax that corresponds to OWL-RL [26], which we refer to as {a mathematical formula}SROIQ-RL. To this end, we define the following grammars for a left-side conceptC and a right-side conceptD respectively:{a mathematical formula}{a mathematical formula} where A is a concept name, R is role name and {a mathematical formula}n∈{0,1}. A both-side concept is a concept expression that is both a left- and right-side concept. Then, in {a mathematical formula}SROIQ-RL TBox axioms can only take the form {a mathematical formula}C⊑D, where C is a left-side and D is a right-side or {a mathematical formula}E≡F, where E and F are both-side concepts. Next, in {a mathematical formula}SROIQ-RL the RBox can contain all role axioms of {a mathematical formula}SROIQ except {a mathematical formula}Ref(R). Finally, ABox concept assertions can only be of form {a mathematical formula}D(a), where D is a right-side concept; without loss of generality, we may also assume that D is atomic. For example, the following expressions are well-formed {a mathematical formula}SROIQ-RL axioms and assertions: {a mathematical formula}A⊑¬B, {a mathematical formula}{a}⊑∃R.{b}, {a mathematical formula}∃R.{b}≡A, {a mathematical formula}¬B(a).
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Datalog programs and answer sets
      </section-title>
      <paragraph>
       Following the approach in [20], we will express our rules in the language of datalog. However, while the rules in [20], [1] are positive, in order to capture defeasibility we need (default) negationnot under the interpretation of answer sets semantics [27].
      </paragraph>
      <section label="2.2.1">
       <section-title>
        Syntax
       </section-title>
       <paragraph>
        A signature is a tuple {a mathematical formula}〈C,P〉 of a finite set C of constants and a finite set P of predicates. We assume a set V of variables; the elements of {a mathematical formula}C∪V are terms. An atom is of the form {a mathematical formula}p(t1,…,tn) where {a mathematical formula}p∈P and {a mathematical formula}t1, …, {a mathematical formula}tn, are terms.{sup:4}
       </paragraph>
       <paragraph>
        A (datalog) rule r is an expression of the form{a mathematical formula} where {a mathematical formula}a,b1,…,bm are atoms and not is the negation as failure symbol (NAF). We denote with {a mathematical formula}Head(r) the head a of rule r and with {a mathematical formula}Body(r)={b1,…,bk,notbk+1,…,notbm} the body of r, respectively. We allow that a is missing (constraint), viewing a as logical constant for falsity. A (datalog) programP is a finite set of rules.
       </paragraph>
       <paragraph>
        An atom (rule etc.) is ground, if no variables occur in it. A ground substitutionσ for {a mathematical formula}〈C,P〉 is any function {a mathematical formula}σ:V→C; the ground instance of an atom (rule, etc.) χ from σ, denoted χσ, is obtained by replacing in χ each occurrence of variable {a mathematical formula}v∈V with {a mathematical formula}σ(v). A factH is a ground rule r with empty body (i.e., {a mathematical formula}m=0); we then omit ←. The grounding of a rule r, {a mathematical formula}grnd(r), is the set of all ground instances of r, and the grounding of a program P is {a mathematical formula}grnd(P)=⋃r∈Pgrnd(r).
       </paragraph>
      </section>
      <section label="2.2.2">
       <section-title>
        Semantics
       </section-title>
       <paragraph>
        Given a program P, the (Herbrand) universe{a mathematical formula}UP of P is the set of all constants occurring in P and the (Herbrand) base{a mathematical formula}BP of P is the set of all the ground atoms constructible from the predicates in P and the constants in {a mathematical formula}UP. An interpretation{a mathematical formula}I⊆BP is any subset of {a mathematical formula}BP. An atom l is true in I, denoted {a mathematical formula}I⊨l, if {a mathematical formula}l∈I.{sup:5}
       </paragraph>
       <paragraph>
        Given a rule {a mathematical formula}r∈grnd(P), we say that {a mathematical formula}Body(r) is true in I, denoted {a mathematical formula}I⊨Body(r), if (i) {a mathematical formula}I⊨b for each atom {a mathematical formula}b∈Body(r) and (ii) {a mathematical formula}I⊭b for each atom {a mathematical formula}notb∈Body(r). A rule r is satisfied in I, denoted {a mathematical formula}I⊨r, if either {a mathematical formula}I⊨Head(r) or {a mathematical formula}I⊨Body(r). An interpretation I is a model of P, denoted {a mathematical formula}I⊨P, if {a mathematical formula}I⊨r for each {a mathematical formula}r∈grnd(P); moreover, I is minimal, if {a mathematical formula}I′⊭P for each subset {a mathematical formula}I′⊂I.
       </paragraph>
       <paragraph label="Proposition 1">
        Given an interpretation I for P, the (Gelfond–Lifschitz) reduct of P w.r.t. I, denoted by {a mathematical formula}GI(P), is the set of rules obtained from {a mathematical formula}grnd(P) by (i) removing every rule r such that {a mathematical formula}I⊨l for some {a mathematical formula}notl∈Body(r); and (ii) removing the NAF part from the bodies of the remaining rules. Then I is an answer set of P, if I is a minimal model of {a mathematical formula}GI(P); the minimal model is unique and exists iff {a mathematical formula}GI(P) has some model. Furthermore, the minimal model is obtainable by fixpoint iteration. The following property is well-known. If M is an answer set for P, then M is a minimal model of P.
       </paragraph>
       <paragraph>
        Using this interpretation for our programs, we say that an atom {a mathematical formula}a∈BP is a consequence of P and we write {a mathematical formula}P⊨a iff for every answer set M of P we have that {a mathematical formula}M⊨a.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Contextualized knowledge repositories with defeasible axioms
     </section-title>
     <paragraph>
      We now introduce CKRs and extend them with primitives to express defeasible axioms. We first present the syntax and then define a model-based semantics for the interpretation of defeasible inheritance from the upper contexts.
     </paragraph>
     <paragraph>
      A Contextualized Knowledge Repository (CKR) is a two layered structure. The upper layer consists of a knowledge base {a mathematical formula}G, which describes two types of knowledge:
     </paragraph>
     <list>
      <list-item label="(i).">
       the structure and the properties of contexts of the CKR (called meta-knowledge), and
      </list-item>
      <list-item label="(ii).">
       the knowledge that is context independent, i.e., that holds in every context (called global knowledge).
      </list-item>
     </list>
     <paragraph>
      The lower layer is constituted by a set of (local) contexts; each contains (locally valid) facts and can also refer to what holds in other contexts. In order to support knowledge reuse, the knowledge of each context is organized in multiple knowledge modules that may be shared with other contexts. To model this, an association between contexts and modules is represented in the meta-knowledge via a binary relation ({a mathematical formula}mod), which can be either explicitly asserted or inferred from the meta-knowledge by reasoning; hence, each context can be associated with one or more knowledge modules which define its contents, while a knowledge module can be shared by one or more contexts. The {a mathematical formula}mod association also allows the knowledge engineer to link modules to classes of contexts, and thus to describe the general knowledge that is valid for all contexts of the same kind. In principle, the knowledge in a CKR can be expressed using any DL language: we thus provide in the following a parametric definition for any DL language and we successively instantiate it to {a mathematical formula}SROIQ-RL.
     </paragraph>
     <section label="3.1">
      <section-title>
       Syntax
      </section-title>
      <paragraph label="Definition 1">
       Meta-Language. The meta-knowledge of a CKR is expressed in a DL language containing the elements to define the contextual structure.{sup:6}meta-vocabularyA meta-vocabulary is a DL vocabulary {a mathematical formula}Γ=NCΓ⊎NRΓ⊎NIΓ that consists of sets {a mathematical formula}NCΓ of atomic concepts, a set {a mathematical formula}NRΓ of atomic roles, and a set {a mathematical formula}NIΓ of individual constants that are mutually disjoint and contain the following sets of symbols:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}N⊆NIΓ of context names;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}M⊆NIΓ of module names;
       </list-item>
      </list>
      <paragraph>
       We use the role {a mathematical formula}mod∈NRΓ defined on {a mathematical formula}N×M to express associations between contexts and modules. Intuitively, modules represent pieces of knowledge specific to a context or context class.{sup:8}
      </paragraph>
      <paragraph label="Definition 2">
       meta-languageThe meta-language{a mathematical formula}LΓ of a CKR is a DL language over Γ with the following syntactic conditions on the application of role restrictions: for every {a mathematical formula}•∈{∀,∃,⩽n,⩾n} and concept C, if {a mathematical formula}C=•mod.B, then {a mathematical formula}B={m} with {a mathematical formula}m∈M.
      </paragraph>
      <paragraph>
       Object Language. The knowledge in contexts of a CKR is expressed via a DL language called object-language{a mathematical formula}LΣ over an object-vocabulary {a mathematical formula}Σ=NCΣ∪NRΣ∪NIΣ akin to Γ. Expressions in {a mathematical formula}LΣ will be evaluated locally at each context, i.e., each context can interpret each symbol independently. However, sometimes one wants to constrain the meaning of a symbol in a context with the meaning of a symbol in some other context. For instance, if John likes all Indian restaurants in Trento, then the extension of the concept GoodRestaurant in the context of John preferences, contains the extension of IndianRestaurant in the context of tourism in Trento. To access the interpretation of expressions inside a specific context or context class, we extend the object language as follows.
      </paragraph>
      <paragraph label="Example 1">
       object language with evalThe language {a mathematical formula}LΣe extends {a mathematical formula}LΣ with eval expressions{a mathematical formula} where X is a concept or role expression of {a mathematical formula}LΣ and {a mathematical formula}C is a concept expression of {a mathematical formula}LΓ (with {a mathematical formula}C⊑Ctx). The DL language {a mathematical formula}LΣe extends {a mathematical formula}LΣ with the set of eval-expressions in {a mathematical formula}LΣ. Intuitively, the expression {a mathematical formula}eval(C,{c}) represents the extension of the concept C in the context {a mathematical formula}c, and {a mathematical formula}eval(C,C), with {a mathematical formula}C a context class, represents the union of the extensions of C in each context {a mathematical formula}c of type {a mathematical formula}C. For {a mathematical formula}eval(R,C) with R a role, this is similar. The example above can be formalized by adding the following axiom to the context of John's preferences: {a mathematical formula}eval(IndianRestaurant,{trento_tourism})⊑GoodRestaurant  ◇ We note that nested eval expressions are not allowed: every expression occurring inside an eval must be an expression in {a mathematical formula}LΣ. Moreover, as for {a mathematical formula}SROIQ-RL the occurrence of eval expressions in axioms and assertions will be syntactically restricted.
      </paragraph>
      <paragraph>
       Defeasible Axioms. With respect to the initial definition of CKR in [1], we extend the types of axioms that can appear in the global object knowledge with defeasible axioms.
      </paragraph>
      <paragraph label="Definition 4">
       defeasible axiomA defeasible axiom is any expression of the form {a mathematical formula}D(α), where {a mathematical formula}α∈LΣ.
      </paragraph>
      <paragraph>
       Intuitively, {a mathematical formula}D(α) means that at the level of instantiations for individuals, α is inherited by local contexts unless it generates a contradiction there. In other words, a local exception to α for some individuals is tolerated.
      </paragraph>
      <paragraph label="Example 2">
       A defeasible global axiom {a mathematical formula}D(Concert⊑Expensive) might be used to express that “in general concerts are expensive” and propagate this piece of knowledge to local contexts. At such a context, this might be contradicted by local assertions {a mathematical formula}Concert(freeconcert2016), {a mathematical formula}¬Expensive(freeconcert2016) which “override” the global axiom for {a mathematical formula}freeconcert2016.  ◇
      </paragraph>
      <paragraph label="Example 3">
       Note that we want that global defeasible axioms hold globally for all their local instances, but they allow exceptional instances in local contexts. For example, let us say that in the global context we assert that {a mathematical formula}D(Horse⊑¬Fly). However, in the local context greek_myths of Greek mythology, we can assert that this axiom does not hold for the particular instance of the flying horse Pegasus: {a mathematical formula}Horse(pegasus), {a mathematical formula}Fly(pegasus). On the other hand, for any other instance of Horse not explicitly violating the axiom, we want to be able to apply the global axiom: for example, if we consider Pedasos, one of Achilles' horses, and assert {a mathematical formula}Horse(pedasos), we want to be able to derive {a mathematical formula}¬Fly(pedasos). ◇
      </paragraph>
      <paragraph label="Definition 5">
       object language with defeasible axiomsThe DL language {a mathematical formula}LΣD extends {a mathematical formula}LΣ with the set of defeasible axioms in {a mathematical formula}LΣ.
      </paragraph>
      <paragraph>
       Equipped with the above languages, we are now ready to give our formal definition of Contextualized Knowledge Repository with defeasible axioms.
      </paragraph>
      <paragraph label="Definition 6">
       contextualized knowledge repository, CKRA contextualized knowledge repository (CKR) over a meta-vocabulary Γ and an object vocabulary Σ is a structure{a mathematical formula} where:
      </paragraph>
      <list>
       <list-item label="–">
        {a mathematical formula}G is a DL knowledge base over {a mathematical formula}LΓ∪LΣD, and
       </list-item>
       <list-item label="–">
        every {a mathematical formula}Km is a DL knowledge base over {a mathematical formula}LΣe, for each module name {a mathematical formula}m∈M.
       </list-item>
      </list>
      <paragraph>
       In the following, we tacitly focus on {a mathematical formula}SROIQ-RL CKRs.
      </paragraph>
      <paragraph label="Example 4">
       We introduce an example from the tourism recommendation domain.{sup:9} In this scenario, we use a CKR to implement a knowledge base {a mathematical formula}Ktour that, after being populated with touristic events, locations, organizations, and tourist preferences and profiles, is capable of identifying events that are interesting for a particular tourist (or for a generic tourist class) starting from their preferences. A simplified version of the structure of {a mathematical formula}Ktour and its contexts is shown in Fig. 1. For our example, we focus on sportive events and in particular on volleyball matches.
      </paragraph>
      <list>
       <list-item label="–">
        Intuitively, in the global context {a mathematical formula}G, every sport event and tourist is modeled with a context; in the figure, these are depicted as black diamonds and we see some of the official volleyball matches and a tourist. Contexts are grouped by types and organized in hierarchies by means of context classes; in the figure, they are depicted as boxes and we see distinct context class hierarchies for event types (e.g. {a mathematical formula}SportiveEvent, {a mathematical formula}VolleyMatch) and for tourists types (e.g. {a mathematical formula}SportiveTourist).
       </list-item>
       <list-item label="–">
        The meta-knowledge in {a mathematical formula}G associates to contexts and context classes sets of knowledge modules, by axioms of the form {a mathematical formula}Event⊑∃mod.{m_event} and {a mathematical formula}{modena_trento}⊑∃mod.{m_match2}: in the figure these associations are represented by dotted lines to the gray empty diamonds depicting module name individuals.
       </list-item>
       <list-item label="–">
        Knowledge bases associated with modules are depicted as the corresponding gray boxes in the lower part of Fig. 1: for example, in {a mathematical formula}Kv_match we have general axioms about the structure of volleyball matches, while in modules for specific matches as {a mathematical formula}Kmatch1 we store assertions about the actual results of the match. Intuitively, the semantics will enforce a form of inheritance of modules via context class hierarchy.
       </list-item>
       <list-item label="–">
        Contextual relations across events and tourists are depicted as bold arrows in the figure: the only relation {a mathematical formula}hasParentEvent connects matches with the competition in which they occur.
       </list-item>
      </list>
      <paragraph label="Example 5">
       We can extend this example with defeasible information: we can assert some general preferences that can be locally overriden by tourist specific assertions. In particular, we want to assert that, in general, all of the Cheap events are Interesting: we can do this using a defeasible axiom in the global context. Furthermore, we propose local markets (market) and football matches (fbmatch) as examples of cheap events. However, we want to reflect that tourists interested in cultural events are not interested in a sports event like a football match: we express this by locally negating their interest in {a mathematical formula}fbmatch. Thus, our example CKR {a mathematical formula}Ktour can be extended with the following axioms:{a mathematical formula} Note that the negative assertion in the local context represents an exception to the defeasible axiom: we want to recognize this “overriding” for the fbmatch instance, but still apply the defeasible inclusion for market. ◇
      </paragraph>
      <paragraph label="Example 6">
       Our next example shows how we can represent a form of defeasible propagation of information across local contexts using eval expressions. We want to represent the information about an organization in a CKR, using contexts to represent its situation in different years. We express the rule that every employee working the years before (WorkingBefore) also works in the current year (WorkingNow) by a defeasible inclusion. In the module associated to 2015, we say that alice, bob and charlie were working last year. In the module for 2016, we say (using an eval expression) that all of the employees working in 2015 have to be considered in the set of employees working in the past years; moreover, we say that charlie no longer works for the organization. This can be encoded in the CKR {a mathematical formula}Korg=〈G,{Kem2015_m,Kem2016_m}〉, where{a mathematical formula} Intuitively, at the local context {a mathematical formula}employees2016, where {a mathematical formula}WorkingBefore(charlie) can be derived, the negative assertion {a mathematical formula}¬WorkingNow(charlie) should override the instance of the inclusion axiom in the global context for charlie, as it would lead to the opposite, i.e., {a mathematical formula}WorkingNow(charlie); on the other hand, for alice and bob no overriding should happen and we can derive that they still work for the organization.  ◇
      </paragraph>
      <paragraph>
       In the previous example, the overriding of the defeasible axiom is uncontroversial and leads to an intuitive set of conclusions. However, it may be the case that axioms lead to conflicting conclusions; while this results for strict (classical) axioms in inconsistency, for defeasible axioms we still may retain consistency but different sets of conclusions can be appealing, in line with conflict resolutions.
      </paragraph>
      <paragraph label="Example 7">
       cont'dConsider an extension of the CKR in Example 6, where the global knowledge contains a further defeasible axiom {a mathematical formula}D(LotteryWinner⊑¬WorkingNow) that states that who wins in the lottery usually does no longer work, and the module {a mathematical formula}Kem2016_m an additional assertion {a mathematical formula}LotteryWinner(alice). Then, at the local context {a mathematical formula}employees2016, where {a mathematical formula}WorkingBefore(alice) can be derived, the defeasible axioms in {a mathematical formula}G lead to the conflicting conclusions {a mathematical formula}WorkingNow(alice) and {a mathematical formula}¬WorkingNow(alice); thus, at least one of the defeasible axiom instances for alice must be overridden if consistency should be maintained.  ◇
      </paragraph>
      <paragraph>
       The readers familiar with nonmonotonic logics and formalisms will recognize that the situation emerging in the previous example amounts to the classic Nixon diamond scenario, which we shall discuss in more detail in Section 7.4. Accordingly, a solution is to override one of the two defeasible axioms such that we can conclude either {a mathematical formula}WorkingNow(alice) or alternatively {a mathematical formula}¬WorkingNow(alice). The semantics of CKRs that we propose has this feature, where assumptions about overriding in models must be reasonably justified; informally, we obtain in Example 7 two classes of models for the CKR, in which {a mathematical formula}WorkingNow(alice) resp. {a mathematical formula}¬WorkingNow(alice) is true.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Semantics
      </section-title>
      <paragraph>
       We now define a model-based semantics of CKRs with defeasible axioms, which extends the semantics of CKRs [1] in order to reason with exceptions and their justifications. Intuitively, we model local exceptions of axiom instances by pairs {a mathematical formula}〈α,e〉 of an axiom {a mathematical formula}α∈LΣ and a tuple e of individuals in {a mathematical formula}NIΣ (called clashing assumptions): in the evaluation of α at a local context, its instantiation with e is not considered. However, such assumptions of exceptions must be justified: the instance of α for e must be unsatisfiable at the local context. This is ensured if assertions can be derived which prove this unsatisfiability; we call such assertions clashing sets.
      </paragraph>
      <paragraph label="Example 8">
       If we consider the concert scenario with the defeasible axiom{a mathematical formula} our clashing assumptions on the local context should contain {a mathematical formula}〈Concert⊑Expensive,freeconcert2016〉; this clashing assumption is in fact justified by the clashing set{a mathematical formula} Models of a CKR will be then CKR interpretations extended with clashing assumptions that are all justified. ◇
      </paragraph>
      <paragraph>
       We start with a formal definition of CKR interpretations.
      </paragraph>
      <paragraph label="Definition 7">
       CKR interpretationA CKR interpretation for {a mathematical formula}〈Γ,Σ〉 is a structure {a mathematical formula}I=〈M,I〉 where
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}M is a DL interpretation of {a mathematical formula}Γ∪Σ such that {a mathematical formula}cM∈CtxM, for every {a mathematical formula}c∈N, and {a mathematical formula}CM⊆CtxM, for every {a mathematical formula}C∈C;
       </list-item>
       <list-item label="(ii)">
        for every {a mathematical formula}x∈CtxM, {a mathematical formula}I(x) is a DL interpretation over Σ s.t., {a mathematical formula}ΔI(x)=ΔM and {a mathematical formula}aI(x)=aM, for every {a mathematical formula}a∈NIΣ.
       </list-item>
      </list>
      <paragraph>
       The interpretation of ordinary DL expressions on {a mathematical formula}M and {a mathematical formula}I(x) in {a mathematical formula}I=〈M,I〉 is as usual (e.g. see Table A.13); eval expressions are interpreted as follows: for every {a mathematical formula}x∈CtxM,{a mathematical formula} According to the previous definition, a CKR interpretation is composed by an interpretation for the “upper-layer” {a mathematical formula}M (which includes the global knowledge and the meta-knowledge) and an interpretation {a mathematical formula}I(x) of the object language for each instance x of type context (i.e., for all {a mathematical formula}x∈CtxM), providing a semantics of the object-vocabulary in x.
      </paragraph>
      <paragraph>
       We next aim to extend CKR interpretation with exceptions for defeasible axioms. To this end, we need some further notions.
      </paragraph>
      <paragraph>
       First-order translation. As well-known, {a mathematical formula}SROIQ-RL knowledge bases can be expressed in first-order (FO) logic [26], where every axiom {a mathematical formula}α∈LΣ is translated into an equivalent FO sentence {a mathematical formula}∀x.ϕα(x) where x contains all free variables of {a mathematical formula}ϕα depending on the type of the axiom (see below). A reference translation is given in A.2; notably, the resulting formulas {a mathematical formula}ϕα(x) amount semantically to Horn formulas. In fact, each left-side concept C can be expressed by an existential positive FO-formula, and every right-side concept D by a conjunction of Horn clauses.
      </paragraph>
      <paragraph>
       To contextualize DL-axioms for CKR knowledge bases, the translation is extended with a further argument {a mathematical formula}xc for the context, such that the formula {a mathematical formula}∀x.ϕα(x,xc) expresses the axiom α within context {a mathematical formula}xc; in particular, for any context name {a mathematical formula}c the sentence {a mathematical formula}∀x.ϕα(x,c) expressed α within {a mathematical formula}c. Furthermore this translation is easily extended to {a mathematical formula}LΣe such that the Horn property is maintained for {a mathematical formula}SROIQ-RL, due to the restrictions on the form and occurrence of eval expressions; the presence of eval expressions requires the contextualized form. We note the following property.
      </paragraph>
      <paragraph label="Lemma 1">
       For any DL knowledge base{a mathematical formula}Kover{a mathematical formula}LΓresp.{a mathematical formula}LΣe, its FO-translation (resp. its contextualized FO translation){a mathematical formula}is semantically equivalent to a conjunction of universal Horn clauses.
      </paragraph>
      <paragraph>
       Notably this lemma remains valid under the SNA, as the axioms defining a congruence relation ≈ are Horn clauses.
      </paragraph>
      <paragraph>
       We now formally introduce the notion of instantiation of an axiom. This notion forms the basis for defining exceptions to axioms in terms of clashing assumptions about violated instances, which have to be evidenced by clashing sets that, in our formalization, are provable from the knowledge base.
      </paragraph>
      <paragraph label="Definition 8">
       axiom instantiationGiven an axiom {a mathematical formula}α∈LΣ with FO-translation {a mathematical formula}∀x.ϕα(x), the instantiation of α with a tuple e of individuals in {a mathematical formula}NIΣ, written {a mathematical formula}α(e), is the specialization of α to e, i.e., {a mathematical formula}ϕα(e), depending on the type of α.
      </paragraph>
      <paragraph>
       In particular, e is (i) void for assertions α, (ii) a single element e for GCIs α, and (iii) a pair {a mathematical formula}e1,e2 of elements for role axioms α.
      </paragraph>
      <paragraph label="Definition 9">
       clashing assumptions and setsA clashing assumption is a pair {a mathematical formula}〈α,e〉 such that {a mathematical formula}α(e) is an axiom instantiation for an axiom {a mathematical formula}α∈LΣ. A clashing set for a clashing assumption {a mathematical formula}〈α,e〉 is a satisfiable set S of ABox assertions over {a mathematical formula}LΣ such that {a mathematical formula}S∪{α(e)} is unsatisfiable.
      </paragraph>
      <paragraph>
       Intuitively, a clashing assumption {a mathematical formula}〈α,e〉 represents that {a mathematical formula}α(e) is not (DL-)satisfiable, and a clashing set S provides an assertional “justification” for the assumption of local overriding of α on e.
      </paragraph>
      <paragraph label="Example 9">
       For example, the clashing assumption {a mathematical formula}〈A⊑B,a〉 has {a mathematical formula}{A(a),¬B(a)} as a clashing set, and {a mathematical formula}〈A⊓B⊑C,a〉 has {a mathematical formula}{A(a),B(a),¬C(a)}. Furthermore, {a mathematical formula}〈A⊑∃R.{a},b〉 has the clashing set {a mathematical formula}{A(b),¬R(b,a)}, and {a mathematical formula}〈A⊑⩽1R.B,a〉 has {a mathematical formula}{A(a),R(a,a),R(a,b),B(a),B(b),¬A(b)}, for instance. In each case the clashing set S is minimal in that no proper subset {a mathematical formula}S′⊂S is a clashing set; multiple minimal clashing sets may exist (e.g., {a mathematical formula}{A(a),R(a,a),R(a,b),B(a),B(b),C(a),¬C(b)} would be another minimal clashing set for {a mathematical formula}〈A⊑⩽1R.B,a〉. ◇
      </paragraph>
      <paragraph>
       We remark that this notion of “assertional justification” is directly connected with the datalog translation in Section 5: it corresponds to the provability of an assertional condition stating the inconsistency of the inherited axiom. By the Horn nature of {a mathematical formula}SROIQ-RL, such a “constructive” justification can always be found.
      </paragraph>
      <paragraph label="Proposition 2">
       Let{a mathematical formula}〈α,e〉be a clashing assumption where α is a{a mathematical formula}SROIQ-RLaxiom. If{a mathematical formula}α(e)is not valid (i.e.,{a mathematical formula}¬ϕα(e)is satisfiable), then a clashing set S for{a mathematical formula}〈α,e〉exists and each concept assertion in S is of the form{a mathematical formula}A(a)resp.{a mathematical formula}¬A(a), and{a mathematical formula}A∈NC. Furthermore, every non-redundant (i.e. ⊆-minimal) such set S has size linear in the size of α.
      </paragraph>
      <section label="3.2.1">
       <section-title>
        CAS-models
       </section-title>
       <paragraph>
        We then extend CKR interpretations to CAS-interpretations that take clashing assumptions into account as follows.
       </paragraph>
       <paragraph label="Definition 10">
        CAS-interpretationA CAS-interpretation is a structure {a mathematical formula}ICAS=〈M,I,χ〉 where {a mathematical formula}I=〈M,I〉 is a CKR interpretation and χ maps every {a mathematical formula}x∈ΔM to a set {a mathematical formula}χ(x) of clashing assumptions for x.
       </paragraph>
       <paragraph>
        Intuitively, a CAS-interpretation pairs a usual CKR interpretation with an exception set for each local context.
       </paragraph>
       <paragraph>
        What remains then is to define satisfaction of axioms on CKR-resp. CAS-interpretations, and to single out appropriate models of a given CKR {a mathematical formula}K. To achieve this, we extend the definition of CKR models from [1] by introducing the condition to disregard “exceptional elements” asserted by clashing assumptions in {a mathematical formula}χ(x) in the local interpretation of their defeasible axioms, leading to CAS-models. However, such models have arbitrary exceptions, while we are interested in justifiable exceptions; this will be captured by the notion of justified CAS-models.
       </paragraph>
       <paragraph>
        For convenience, we call two DL interpretations {a mathematical formula}I1 and {a mathematical formula}I2 (resp. CAS-interpretations {a mathematical formula}ICASi=〈Mi,Ii,χi〉, {a mathematical formula}i∈{1,2}) NI-congruent, if {a mathematical formula}cI1=cI2 (resp. {a mathematical formula}cM1=cM2) holds for every {a mathematical formula}c∈NI.
       </paragraph>
       <paragraph label="Definition 11">
        CAS-modelGiven a CKR {a mathematical formula}K=〈G,{Km}m∈M〉, a CAS-interpretation {a mathematical formula}ICAS=〈M,I,χ〉 is a CAS-model for {a mathematical formula}K (denoted {a mathematical formula}ICAS⊨K), if the following holds:
       </paragraph>
       <list>
        <list-item label="(i)">
         for every {a mathematical formula}α∈LΣ∪LΓ in {a mathematical formula}G, {a mathematical formula}M⊨α;
        </list-item>
        <list-item label="(ii)">
         for every {a mathematical formula}D(α)∈G (where {a mathematical formula}α∈LΣ), {a mathematical formula}M⊨α;
        </list-item>
        <list-item label="(iii)">
         for every {a mathematical formula}〈x,y〉∈modM such that {a mathematical formula}y=mM, {a mathematical formula}I(x)⊨Km;
        </list-item>
        <list-item label="(iv)">
         for every {a mathematical formula}α∈G∩LΣ and {a mathematical formula}x∈CtxM, {a mathematical formula}I(x)⊨α, and
        </list-item>
        <list-item label="(v)">
         for every {a mathematical formula}D(α)∈G (where {a mathematical formula}α∈LΣ), {a mathematical formula}x∈CtxM, and {a mathematical formula}|x|-tuple d of elements in {a mathematical formula}NIΣ such that {a mathematical formula}d∉{e|〈α,e〉∈χ(x)}, we have {a mathematical formula}I(x)⊨ϕα(d).
        </list-item>
       </list>
       <paragraph>
        In the previous definition, conditions (i) and (ii) verify that the global interpretation {a mathematical formula}M satisfies the (strict and defeasible) axioms in {a mathematical formula}G. Condition (iii) states that each local interpretation {a mathematical formula}I(x) satisfies all local modules {a mathematical formula}Km that are associated with context x. Moreover, by condition (iv), all strict axioms from global object knowledge in {a mathematical formula}G need to be satisfied in local interpretations. The local interpretation of defeasible axioms is defined by condition (v): for every global defeasible axiom {a mathematical formula}D(α) and instantiation {a mathematical formula}α(d) of it, {a mathematical formula}I(x) must satisfy {a mathematical formula}α(d) if {a mathematical formula}〈α,d〉∉χ(x), i.e., {a mathematical formula}α(d) is not an exceptional instantiation.
       </paragraph>
       <paragraph>
        As for condition (iii), we note that contexts and module names are not necessarily interpreted as the same objects, and that a module can be shared by more contexts: the fact that the piece of knowledge identified by {a mathematical formula}m should be included in the knowledge of context {a mathematical formula}c is provided by the truth of the role assertion {a mathematical formula}mod(c,m). Thus, it is not the case that if a context {a mathematical formula}c belongs to a context class {a mathematical formula}C then its modules belong to {a mathematical formula}C too: on the other hand, if we write {a mathematical formula}C⊑∃mod.{m}, we can state that all contexts in {a mathematical formula}C share the same module {a mathematical formula}m (e.g. defining the common features of elements in {a mathematical formula}C).
       </paragraph>
       <paragraph>
        We can express the CAS-models of a CKR {a mathematical formula}K using an extended FO translation, in which the clashing assumption χ is represented by predicates {a mathematical formula}appα(x,xc) which informally state that in context {a mathematical formula}xc, the axiom {a mathematical formula}α=∀x.ϕα(x) has for x not an exception, i.e., α applies on x (cf. Appendix). More in detail, let us call{a mathematical formula}{a mathematical formula} the context-constraint resp. clashing-constraint translation of α; then the sentence{a mathematical formula} where {a mathematical formula}GΣ,Γ=G∩(LΣ∪LΓ)∪{α|D(α)∈G}, expresses the CAS-models of {a mathematical formula}K, i.e., those CAS-interpretations which are CAS-models relative to the represented clashing assumption. Clearly, {a mathematical formula}ϕK amounts semantically to a Horn sentence.
       </paragraph>
       <paragraph label="Example 10">
        We can now provide an example of CAS model for the CKR {a mathematical formula}KtourD from Example 5.We can consider the model {a mathematical formula}ICASt1=〈M,I,χt1〉 such that{a mathematical formula} In this case we have the intuitive interpretation where {a mathematical formula}I(cultural_touristM)⊭Interesting(fbmatch).However, it is not the only legitimate CAS model for {a mathematical formula}KtourD: we can also consider the model {a mathematical formula}ICASt2=〈M,I,χt2〉 where:{a mathematical formula} In this case, also the individual {a mathematical formula}market is considered as exceptional and it holds that {a mathematical formula}I(cultural_touristM)⊭Interesting(market). We will see in the following how to limit the models we consider only to the exceptional cases that are actually motivated by the contents of the CKR at hand. ◇
       </paragraph>
       <paragraph>
        Justification. A clashing assumption allows us to dispense the application of an axiom in a context. However, for this to happen, we should have a good reason; an exception should be made only if needed. To reflect this, we say that a clashing assumption {a mathematical formula}〈α,e〉∈χ(x) is justified for a CAS model {a mathematical formula}ICAS=〈M,I,χ〉, if some clashing set {a mathematical formula}S=S〈α,e〉,x exists such that, for every CAS-model {a mathematical formula}ICAS′=〈M′,I′,χ〉 of {a mathematical formula}K that is NI-congruent with {a mathematical formula}ICAS, it holds that {a mathematical formula}I′(x)⊨S〈α,e〉,x. Informally, justification requires that we have factual evidence that an instantiation of an axiom can not be satisfied, and this evidence is provable. This leads us to justified CAS-models, from which we obtain CKR-models of {a mathematical formula}K by stripping off the clashing part.
       </paragraph>
       <paragraph label="Definition 12">
        justified CAS model and CKR modelA CAS model {a mathematical formula}ICAS=〈M,I,χ〉 of a CKR {a mathematical formula}K is justified, if every {a mathematical formula}〈α,e〉∈⋃x∈CtxMχ(x) is justified. An interpretation {a mathematical formula}I=〈M,I〉 is a CKR model of {a mathematical formula}K (in symbols, {a mathematical formula}I⊨K), if {a mathematical formula}K has some justified CAS model {a mathematical formula}ICAS=〈M,I,χ〉.
       </paragraph>
       <paragraph label="Example 11">
        ◇
       </paragraph>
       <paragraph label="Example 12">
        We can now show an example of CKR models satisfying the CKRs presented in Example 5, Example 6. In the case of {a mathematical formula}KtourD, let us consider the model {a mathematical formula}ICASt1=〈M,I,χt1〉 of Example 10. We note that this interpretation is justified as it is easy to check that{a mathematical formula} that represents a clashing set for the defeasible axiom. On the other hand, the CAS model {a mathematical formula}ICASt2 is not justified: indeed, in the case of the individual {a mathematical formula}market we can not find a clashing set for the respective clashing assumption, since {a mathematical formula}I(cultural_touristM)⊭¬Interesting(market).In the case of {a mathematical formula}Korg, we have that the model {a mathematical formula}ICASorg=〈M,I,χorg〉 with{a mathematical formula} is a CKR model for the example CKR. For the interpretation of eval expressions, in every interpretation of {a mathematical formula}Ktour we have that {a mathematical formula}{aliceI(x),bobI(x),charlieI(x)}⊆WorkingBeforeI(x), where {a mathematical formula}x=employees2016. Thus the justification of the model can be easily seen as{a mathematical formula} which represents a clashing set for the defeasible axiom on charlie.  ◇
       </paragraph>
       <paragraph>
        Different from arbitrary CAS-models, a characterization of justified CAS-models by a FO translation (even less into Horn formulas) is not straightforward; furthermore, no modular translation can exist, due to the inherent non-monotonicity of exceptions (see below).
       </paragraph>
      </section>
     </section>
     <section label="3.3">
      <section-title>
       Semantic properties
      </section-title>
      <paragraph>
       It appears that CAS-models and in particular justified CAS-models (thus CKR-models), have interesting properties.
      </paragraph>
      <paragraph>
       Irrelevance of syntax  Straight from the definition is the property that the syntactic form of an axiom with exceptions is not important. That is,
      </paragraph>
      <paragraph label="Proposition 3">
       irrelevance of syntaxSuppose{a mathematical formula}K=〈G,{Km}m∈M〉has in{a mathematical formula}Ga defeasible axiom{a mathematical formula}D(α). If{a mathematical formula}β∈LΣsatisfies{a mathematical formula}ϕα(x)≡ϕβ(x)(i.e., β is of the same genus and logically equivalent to α), then{a mathematical formula}Kand{a mathematical formula}K′=〈(G∖α)∪{β},{Km}m∈M〉have the same CKR-models.
      </paragraph>
      <paragraph>
       Note that Proposition 3 does not hold for arbitrary CAS-models, as clashing assumptions are syntactically defined; however, the sets of CAS-models correspond under exchange of α and β there.
      </paragraph>
      <paragraph>
       Nonmonotonicity  As expected, justified CAS-models behave nonmonotonically, in the following sense. Let us write {a mathematical formula}K⊆K′ for {a mathematical formula}K=〈G,{Km}m∈M〉 and {a mathematical formula}K′=〈G′,{Km′}m∈M〉, if {a mathematical formula}G⊆G′ and {a mathematical formula}Km′⊆Km, for all {a mathematical formula}m∈M.
      </paragraph>
      <paragraph label="Proposition 4">
       non-monotonicitySuppose{a mathematical formula}ICAS=〈M,I,χ〉is a justified CAS-model of a CKR{a mathematical formula}K′. Then{a mathematical formula}ICASis not necessarily a justified CAS-model of every{a mathematical formula}K⊆K′.
      </paragraph>
      <paragraph>
       For example, if {a mathematical formula}G′ consists of {a mathematical formula}D(A(c)) and a context {a mathematical formula}c with an associated module {a mathematical formula}Km′ consisting of {a mathematical formula}¬A(c), then {a mathematical formula}¬A(c) is true at {a mathematical formula}c in the justified CAS-model of {a mathematical formula}K′, thanks to the justified clashing assumption {a mathematical formula}〈A(c),ϵ〉; if we remove {a mathematical formula}¬A(c), then {a mathematical formula}¬A(c) is false in the justified CAS-model of {a mathematical formula}K, as the clashing assumption {a mathematical formula}〈A(c),ϵ〉 is no longer justified and must be dropped.
      </paragraph>
      <paragraph>
       Context focus  A further simple property is that in CAS-models, only the clashing assumptions for contexts matter. Formally,
      </paragraph>
      <paragraph label="Proposition 5">
       context focusSuppose{a mathematical formula}ICAS=〈M,I,χ〉⊨Kfor a CAS-interpretation of a CKR{a mathematical formula}Kand that{a mathematical formula}χ′coincides with χ on{a mathematical formula}CtxM. Then{a mathematical formula}ICAS′=〈M,I,χ′〉⊨K. Furthermore, if{a mathematical formula}ICASis justified, then also{a mathematical formula}ICAS′is justified.
      </paragraph>
      <paragraph>
       That is, if we consider a justified CAS model {a mathematical formula}ICAS, any other CAS-interpretation {a mathematical formula}ICAS′ that differs from CAS only on the clashing assumptions of elements not in {a mathematical formula}CtxM (i.e. non-context individuals) is also a justified model. Thus, clashing assumptions can be safely assumed to be void for non-context individuals.
      </paragraph>
      <paragraph>
       Minimality of justification  In case of justified CAS-models, the clashing assumptions associated with the contexts are minimal in the sense that no assumption can be omitted. This follows from the property that the clashing assumptions must be setwise incomparable.
      </paragraph>
      <paragraph label="Proposition 6">
       minimality of justificationSuppose that{a mathematical formula}ICAS=〈M,I,χ〉and{a mathematical formula}ICAS′=〈M′,I′,χ′〉are justified CAS-models of a CKR{a mathematical formula}Kthat are NI-congruent. Then,{a mathematical formula}CtxM=CtxM′and{a mathematical formula}χ′(x)⊆χ(x)for every{a mathematical formula}x∈CtxMimplies{a mathematical formula}χ=χ′.
      </paragraph>
      <paragraph>
       As a consequence, exceptions in CKR models are minimally justified in this sense; notably, this minimality condition is intrinsic and not explicitly part of the definition.
      </paragraph>
      <paragraph>
       Intersection property and least model  Another property is that CAS-models of a {a mathematical formula}SROIQ-RL CKR enjoy an intersection property; this is due to the fact that the global and the local knowledge bases of a CKR amount to Horn theories, which as it is well-known have the intersection property.
      </paragraph>
      <paragraph>
       Formally, for two NI-congruent DL interpretations {a mathematical formula}I1 and {a mathematical formula}I2, we denote by {a mathematical formula}I1∩I2 the NI-congruent interpretation such that {a mathematical formula}CI1∩I2=C1I∩C2I and {a mathematical formula}RI1∩I2=R1I∩R2I for all {a mathematical formula}C∈NC and {a mathematical formula}R∈NR, respectively. Then:
      </paragraph>
      <paragraph label="Proposition 7">
       intersection propertyLet{a mathematical formula}ICASi=〈Mi,Ii,χ〉,{a mathematical formula}i∈{1,2}be NI-congruent CAS-models of a CKR{a mathematical formula}K. Then{a mathematical formula}ICAS=〈M,I,χ〉where{a mathematical formula}M=M1∩M2and{a mathematical formula}I=I1∩I2is the intersection of the{a mathematical formula}Miresp.{a mathematical formula}Ii, is also a CAS-model of{a mathematical formula}K. Furthermore,{a mathematical formula}ICASis justified if some{a mathematical formula}ICASiis justified,{a mathematical formula}i∈{1,2}.
      </paragraph>
      <paragraph>
       An immediate consequence of this result is that a least (justified) CAS-model exists. Technically, let a name assignment be any interpretation {a mathematical formula}ν:NI→Δ of the individual constants on the domain Δ (respecting SNA); the name assignment of a DL interpretation {a mathematical formula}I (resp. CAS-interpretation {a mathematical formula}ICAS=〈M,I,χ〉) is the one induced by {a mathematical formula}NII (resp. {a mathematical formula}NIM). We call a clashing assumption CAS for a CKR {a mathematical formula}Ksatisfiable (resp., justified) for a name assignment ν, if {a mathematical formula}K has some CAS-model (resp., justified CAS-model) {a mathematical formula}ICAS with name assignment ν. Then:
      </paragraph>
      <paragraph label="Corollary 1">
       least model propertyIf a clashing assumption χ for a CKR{a mathematical formula}Kis satisfiable for name assignment ν, then{a mathematical formula}Khas a least (unique minimal) CAS-model{a mathematical formula}IˆK(χ,ν)=〈Mˆ,Iˆ,χ〉w.r.t. inclusion{a mathematical formula}M′⊆Mand{a mathematical formula}I′⊆Ifor ν. Furthermore,{a mathematical formula}IˆK(χ,ν)is justified if χ is justified.
      </paragraph>
      <paragraph>
       Named model focus  An important property concerns the scope of an interpretation. For {a mathematical formula}SROIQ-RL DL knowledge bases {a mathematical formula}K, and likewise for {a mathematical formula}SROIQ-RL CKRs {a mathematical formula}K, we can focus on the named part of a DL interpretation {a mathematical formula}I resp. a CAS-interpretation {a mathematical formula}ICAS=〈M,I,χ〉. We say {a mathematical formula}I is named relative to {a mathematical formula}N⊆NI∖NIS, if {a mathematical formula}CI⊆NI and {a mathematical formula}RI⊆NI×NI for each {a mathematical formula}C∈NC and {a mathematical formula}R∈NR; if in addition {a mathematical formula}cI≠dI for any distinct {a mathematical formula}c,d∈N and N includes all constants that occur in {a mathematical formula}K, we call {a mathematical formula}I a pseudo Herbrand interpretation for {a mathematical formula}K relative to N.{sup:10} The following lemma is then not hard to establish. For convenience, let for any {a mathematical formula}N⊆NI∖NIS be the N-restriction of{a mathematical formula}I, denoted by {a mathematical formula}IN, the interpretation that results from {a mathematical formula}I by restricting {a mathematical formula}CI to {a mathematical formula}NI for all {a mathematical formula}C∈NC and {a mathematical formula}RI to {a mathematical formula}NI×NI for every {a mathematical formula}R∈NR.
      </paragraph>
      <paragraph label="Lemma 2">
       Suppose{a mathematical formula}Iis a model of a{a mathematical formula}SROIQ-RLknowledge base{a mathematical formula}Kand{a mathematical formula}N⊆NI∖NISincludes all individuals occurring in{a mathematical formula}K. Then the N-restriction{a mathematical formula}INis named w.r.t. N and a model of{a mathematical formula}K.
      </paragraph>
      <paragraph>
       In essence, we have model preservation under restriction to {a mathematical formula}NI (technically, because of the standard names we need to keep the whole domain).
      </paragraph>
      <paragraph label="Theorem 1">
       This property extends to CAS-interpretations {a mathematical formula}ICAS(M,I,χ) of CKRs {a mathematical formula}K. Given that N includes each individual constant that occurs in {a mathematical formula}K, a CAS-interpretation {a mathematical formula}ICASN results from {a mathematical formula}ICAS by (i) replacing {a mathematical formula}M and each {a mathematical formula}I(x) with its N-restriction, (ii) removing each clashing assumption {a mathematical formula}〈α,d〉 from χ where d is not over {a mathematical formula}N∪NM, and (iii) interpreting each constant symbol {a mathematical formula}c∈NI∖(N∪NIS) such that {a mathematical formula}cM∈NM (resp. {a mathematical formula}cI(x)∈NI(x)) its interpretation {a mathematical formula}cMN (resp. {a mathematical formula}cI(x)N) by some arbitrary element not in {a mathematical formula}NM.{sup:11} In particular, we write {a mathematical formula}NK for N if the latter consists precisely of the individual constants that occur in {a mathematical formula}K. Then we obtain: named model focusLet{a mathematical formula}ICASbe a CAS-model of{a mathematical formula}Kand suppose{a mathematical formula}NK⊆N⊆NI∖NIS. Then, also{a mathematical formula}ICASN, and in particular{a mathematical formula}ICASNK, is a CAS-model for{a mathematical formula}K. Furthermore,{a mathematical formula}ICASNis justified if{a mathematical formula}ICASis justified, and every clashing assumption{a mathematical formula}〈α,e〉in{a mathematical formula}ICASNis justified by some clashing set S formulated with constants from N.
      </paragraph>
      <paragraph>
       Based on this, we can restrict query answering, which we will turn to next, to named CKR-models. This property is crucial for the datalog translation that we shall present in Section 5.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Reasoning and complexity
     </section-title>
     <paragraph>
      In this section, we consider reasoning from CKRs: to this end, we first define entailment of axioms from a CKR, and then we proceed to define conjunctive queries over a CKR. After that, we characterize the computational complexity of elementary reasoning tasks and query answering from CKRs.
     </paragraph>
     <section label="4.1">
      <section-title>
       CKR entailment
      </section-title>
      <paragraph>
       Based on CKR-models, we define notions of context and global entailment of axioms from a CKR as follows.
      </paragraph>
      <paragraph label="Definition 13">
       {a mathematical formula}c-entailment, global entailmentAssume a CKR {a mathematical formula}K over {a mathematical formula}〈Γ,Σ〉 and {a mathematical formula}c∈NK. An axiom {a mathematical formula}α∈LΣe is {a mathematical formula}c-entailed by {a mathematical formula}K, denoted {a mathematical formula}K⊨c:α, if {a mathematical formula}I(cM)⊨α for every CKR-model {a mathematical formula}I=〈M,I〉 of {a mathematical formula}K. Furthermore, an axiom α is (globally) entailed by {a mathematical formula}K, denoted {a mathematical formula}K⊨α, if{a mathematical formula}
      </paragraph>
      <paragraph label="Example 13">
       Considering the CKR {a mathematical formula}KtourD and the model {a mathematical formula}ICASt1 from Example 12, we have that{a mathematical formula} On the other hand, for the definition of satisfiability under the assumptions in {a mathematical formula}CASt1, we obtain that {a mathematical formula}I(cultural_touristM)⊨Interesting(market).For {a mathematical formula}Korg and the model {a mathematical formula}ICASorg, similarly, we have:{a mathematical formula} However, for the satisfiability under the assumptions in {a mathematical formula}CASorg, we obtain that {a mathematical formula}I(employeesM)⊨WorkingNow(alice) and {a mathematical formula}I(employeesM)⊨WorkingNow(bob).  ◇
      </paragraph>
      <paragraph>
       In order to decide entailment of an axiom, it is helpful to know when a clashing assumption is justified. The following theorem provides such a characterization, which resorts to the least model {a mathematical formula}IˆK(χ,ν) for a clashing assumption χ and a name assignment ν.
      </paragraph>
      <paragraph label="Theorem 2">
       justified CAS characterizationLet χ be a satisfiable clashing assumption for CKR{a mathematical formula}Kand name assignment ν. Then χ is justified iff{a mathematical formula}〈α,e〉∈χ(x)implies some clashing set{a mathematical formula}S=S〈α,e〉,xexists such that
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}Iˆ(x)⊨β, for each positive{a mathematical formula}β∈S, where{a mathematical formula}IˆK(χ,ν)=(Mˆ,Iˆ,χ), and
       </list-item>
       <list-item label="(ii)">
        no CAS-model{a mathematical formula}ICAS=〈M,I,χ〉with name assignment ν exists such that{a mathematical formula}I(x)⊨βfor some{a mathematical formula}¬β∈S.
       </list-item>
      </list>
      <paragraph label="Proof">
       Given that χ is a satisfiable clashing assumption for {a mathematical formula}K and ν, by Corollary 1 the least CAS-model {a mathematical formula}IˆK(χ,ν)=〈Mˆ,Iˆ,χ〉 w.r.t. inclusion {a mathematical formula}M′⊆M and {a mathematical formula}I′⊆I for ν exists.(⇒) If χ is justified, then {a mathematical formula}IˆK(χ,ν) is justified and hence by definition for every {a mathematical formula}〈α,e〉∈χ(x) some clashing set {a mathematical formula}S=S〈α,e〉,x exists such that for each CAS-model {a mathematical formula}ICAS′=(M′,I′,χ) of {a mathematical formula}K that is NI-congruent with {a mathematical formula}IˆK(χ,ν), i.e., with name assignment ν, it holds that {a mathematical formula}I′(x)⊨S; hence, (ii) clearly holds. Furthermore, as {a mathematical formula}ICAS′ is NI-congruent with itself, also (i) holds.(⇐) Suppose every {a mathematical formula}〈α,e〉∈χ(x) has some clashing set {a mathematical formula}S=S〈α,e〉,x such that items (i) and (ii) hold. Let {a mathematical formula}ICAS′=(M′,I′,χ) be any CAS-model of {a mathematical formula}K that is NI-congruent with {a mathematical formula}IˆK(χ,ν). As {a mathematical formula}Iˆ⊆I′, it follows from (i) that {a mathematical formula}I′(x)⊨β for each positive {a mathematical formula}β∈S; furthermore, from (ii) it follows that {a mathematical formula}I′(x)⊨¬β for each {a mathematical formula}¬β∈S. Hence, {a mathematical formula}I′(x)⊨S, and thus {a mathematical formula}〈α,e〉 is justified for {a mathematical formula}IˆK(χ,ν). Consequently, {a mathematical formula}IˆK(χ,ν) is justified.  □
      </paragraph>
      <paragraph>
       As for testing (ii), we can add to {a mathematical formula}K a module {a mathematical formula}Kmβ={β} and the global assertion {a mathematical formula}mod(c,mβ) where {a mathematical formula}cIˆ=x, and test whether the resulting CKR {a mathematical formula}Kβ,c has no CAS-model {a mathematical formula}ICAS′=〈M′,I′,χ〉 with naming ν; in other words, that the clashing assumption χ is not satisfiable for {a mathematical formula}Kβ (equivalently, that {a mathematical formula}IˆKβ,c(χ,ν) does not exist).
      </paragraph>
      <paragraph>
       With the characterization of justified clashing assumptions at hand, we can devise a refutation algorithm for {a mathematical formula}K⊨c:α resp. {a mathematical formula}K⊨α that finds a justified CAS-model {a mathematical formula}ICAS of {a mathematical formula}K in which the query does not hold. As the axiom α amounts to a universal sentence {a mathematical formula}∀x.ϕα(x) resp. {a mathematical formula}∀x.ϕα(x,c), it is sufficient to consider named models relative to the individual constants in {a mathematical formula}K and fresh (Skolem) constants for the negated query. This naturally leads to a non-deterministic algorithm. As we show in the next subsection, the refutation is feasible in nondeterministic polynomial time; this is worst-case optimal, as the entailment problem is coNP-hard.
      </paragraph>
      <paragraph>
       Specifically, for positive assertions α, Corollary 1 implies that entailment (resp. {a mathematical formula}K⊨α) is equivalent to truth of α at context {a mathematical formula}c in (resp. at the global part of) the least model {a mathematical formula}IˆK(χ,ν), for every justifiable χ of {a mathematical formula}K and name assignment ν. For negative assertions {a mathematical formula}α=¬β entailment {a mathematical formula}K⊨c:α reduces similarly as in Theorem 2 to the nonexistence of the least model {a mathematical formula}Iˆ(χ,ν) for {a mathematical formula}Kβ,c, for all justified χ and ν; for global entailment, this is analogous.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Conjunctive queries
      </section-title>
      <paragraph>
       We can easily extend these results to manage conjunctive queries over different contexts. Formally, a (general) conjunctive query (CQ) is a formula {a mathematical formula}Q(x)=∃yγ(x,y) where x, y are disjoint lists of different variables and {a mathematical formula}γ(x,y)=γ1∧⋯∧γm is a conjunction of atoms {a mathematical formula}γi of the form {a mathematical formula}ci:αi(ti) resp. {a mathematical formula}αi(ti), {a mathematical formula}1≤i≤m where {a mathematical formula}ci is a context name and {a mathematical formula}αi is either a concept name or a role name from the object vocabulary Σ or the meta-vocabulary Γ, and {a mathematical formula}ti is a tuple of variables from {a mathematical formula}x∪y and individual constants that matches the arity of {a mathematical formula}αi. The CQ is Boolean, if x is empty.
      </paragraph>
      <paragraph label="Example 14">
       Given the knowledge base {a mathematical formula}Korg in previous employees examples, a simple general CQ is to retrieve all employees that are currently working and also worked in the past years:{a mathematical formula} We can obtain a Boolean query by instantiating {a mathematical formula}Q1 on one of the individuals in {a mathematical formula}Korg, for example:{a mathematical formula}  ◇
      </paragraph>
      <paragraph>
       A CKR interpretation {a mathematical formula}I=〈M,I〉 satisfies a Boolean CQ Q, denoted {a mathematical formula}I⊨Q, if for some substitution {a mathematical formula}ϑ:y→NIs it holds that {a mathematical formula}I(ciI)⊨αi(tiϑ) resp. {a mathematical formula}M⊨αi(tiϑ) for all {a mathematical formula}1≤i≤m. A CKR {a mathematical formula}K entails Q, denoted {a mathematical formula}K⊨Q, if every CKR model of {a mathematical formula}K satisfies Q. Based on this, the (certain) answers for a general CQ {a mathematical formula}Q(x) are defined as usual, i.e., as the tuples c of individual constants such that {a mathematical formula}K⊨Q′ where {a mathematical formula}Q′ is the boolean query {a mathematical formula}Q(c).
      </paragraph>
      <paragraph label="Example 15">
       Considering the models for {a mathematical formula}Korg introduced in previous examples, it clearly holds that {a mathematical formula}Korg⊨Q2 since we have that:{a mathematical formula} Moreover, the general query {a mathematical formula}Q1 then has as certain answers {a mathematical formula}c∈{alice,bob}, since we can verify that {a mathematical formula}Korg⊨Q1(alice)=Q2 and {a mathematical formula}Korg⊨Q1(bob).  ◇
      </paragraph>
      <paragraph>
       Conjunctive queries basically allow us to generalize the CKR-entailment to joins of one or more atomic facts. As such, from the results presented on CKR-entailment and the definition of CQ entailment, we directly obtain that also the evaluation of conjunctive queries can be restricted to named CKR models. Moreover, since Boolean CQs are basically conjunctions of positive atomic assertions, from Corollary 1 we have that for a Boolean conjunctive query Q, {a mathematical formula}K⊨Q iff {a mathematical formula}IˆK(χ,ν)⊨Q, for every justifiable χ of {a mathematical formula}K and name assignment ν.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Computational complexity
      </section-title>
      <paragraph>
       We conduct in this section an analysis of the computational complexity of some major reasoning tasks for CKRs. In particular, we consider model checking, the entailment problem and conjunctive query answering. As for model checking, we assume throughout that interpretations are named and that constants not mapped to the named part are omitted; thus the named part and set the constants mapped to it are finite.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Model checking
       </section-title>
       <paragraph>
        To begin with, we first note that satisfiability testing and model checking in (extended) {a mathematical formula}SROIQ-RL is tractable.
       </paragraph>
       <paragraph label="Lemma 3">
        Given a{a mathematical formula}SROIQ-RLknowledge base{a mathematical formula}Kover{a mathematical formula}LΣor{a mathematical formula}LΣe(resp.{a mathematical formula}LΓ), one can decide in polynomial time (i) whether a given DL interpretation{a mathematical formula}Iof Σ (resp., Γ) satisfies{a mathematical formula}K, and (ii) whether for a given CKR interpretation{a mathematical formula}I=(M,I)and{a mathematical formula}x∈CtxM, it holds that{a mathematical formula}I(x)⊨K(resp.{a mathematical formula}M⊨K).
       </paragraph>
       <paragraph>
        Indeed, for each concept expression E and role expression R, we can compute {a mathematical formula}EI and {a mathematical formula}SI, as well as for any {a mathematical formula}x∈CtxM also {a mathematical formula}EI(x) and {a mathematical formula}SI(x), inductively along its structure in polynomial time; note that each {a mathematical formula}EI is a unary relation, and each {a mathematical formula}SI is a binary relation. Based on this, we can easily check whether every axiom in {a mathematical formula}K is satisfied in polynomial time.
       </paragraph>
       <paragraph>
        For model checking of CAS-semantics, we then obtain the following result.
       </paragraph>
       <paragraph label="Proposition 8">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉and a CAS-interpretation{a mathematical formula}ICAS=〈M,I,χ〉, deciding whether{a mathematical formula}ICAS⊨Kholds is feasible in polynomial time.
       </paragraph>
       <paragraph label="Proof">
        From Lemma 3, it is immediate that the items (i)–(iv) of {a mathematical formula}ICAS⊨K in Definition 11 can be checked in polynomial time. As for item (v), we must test the axiom α for all tuples {a mathematical formula}d∉{e|〈α,e〉∈χ(x)} in {a mathematical formula}I(x). To this end, it is sufficient consider d over {a mathematical formula}N∪{c1,…,c|e|} where the {a mathematical formula}ci are distinct standard names not in {a mathematical formula}NM. There are polynomially many such d and for each the test is feasible in polynomial time (by Lemma 3). Overall, it follows that deciding {a mathematical formula}ICAS⊨K is feasible in polynomial time.  □
       </paragraph>
       <paragraph>
        For justified CAS-model checking, in addition to {a mathematical formula}ICAS⊨K we must verify that CAS is justified for the name assignment given by {a mathematical formula}ICAS. We can exploit Proposition 2 and Theorem 2, given the fact that the least model {a mathematical formula}IˆK(χ,ν) can be efficiently constructed.
       </paragraph>
       <paragraph label="Lemma 4">
        Given a CKR{a mathematical formula}K, a clashing assumption χ for{a mathematical formula}Kand a name assignment ν,{sup:12}one can compute{a mathematical formula}IˆK(χ,ν)in polynomial time resp. recognize that{a mathematical formula}IˆK(χ,ν)does not exist.
       </paragraph>
       <paragraph label="Proof">
        (Sketch) This can be done by computing the least model of the Horn sentence {a mathematical formula}ϕK in (8) for χ and ν represented as facts (and tacitly including the congruence axioms), which is possible using a standard fixpoint iteration of a one-step consequence operator {a mathematical formula}TϕK. To avoid an exponential blowup of the naive translation, occurrences of disjunction {a mathematical formula}C1⊔C2 are eliminated using auxiliary predicates {a mathematical formula}PC1⊔C2 (see Appendix). In each iteration, we must evaluate Horn implications of the form (A.1) where the antecedent {a mathematical formula}p1(x,xi,y1)∧⋯∧pk(x,xi,yk) forms an acyclic conjunctive query. Matching acyclic queries against a relational interpretation is well-known to be feasible in polynomial time (cf. [37]). As all predicate arities are bounded by a constant, the number of iterations is polynomially bounded. If ⊥ is derived, then {a mathematical formula}IˆK(χ,ν) does not exist, otherwise it is easily extracted from the computed least fixpoint.  □
       </paragraph>
       <paragraph label="Proposition 9">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉and a CAS-interpretation{a mathematical formula}ICAS=〈M,I,χ〉, deciding whether{a mathematical formula}Iis a justified CAS-model of{a mathematical formula}Kis feasible in polynomial time.
       </paragraph>
       <paragraph label="Proof">
        By Proposition 8, we can check whether {a mathematical formula}ICAS⊨K in polynomial time. By Theorem 2, it thus remains to check whether for every {a mathematical formula}〈α,e〉,x such that the conditions (i) and (ii) of the theorem are satisfied some clashing set {a mathematical formula}S〈α,e〉,x exists. To this end, we let S consist of (a) all positive atomic assertions β such that {a mathematical formula}Iˆ(x)⊨β where {a mathematical formula}IˆK(χ,ν)=(Mˆ,Iˆ,χ), and β is over N, where N are the constants of the named part,{sup:13} and (b) all negative atomic assertions ¬β over N such that {a mathematical formula}IˆKβ,c(χ,ν) does not exist (i.e., no CAS-model {a mathematical formula}ICAS=〈M′,I′,χ〉 with name assignment ν exists such that {a mathematical formula}I′(x)⊨β).It is easy to see that S is satisfiable, and it follows from the proof of Theorem 1 and Theorem 2 that S is moreover a clashing set for {a mathematical formula}〈α,e〉 iff some clashing set {a mathematical formula}S〈α,e〉{a mathematical formula}〈α,e〉 exists, and that S includes some irredundant (minimal) clashing set {a mathematical formula}S′ of size linear in the size of α; thus we can restrict the candidates β resp. ¬β for {a mathematical formula}S′ to axiom instances over a small (linear) extension of the individual constants {a mathematical formula}NK.Testing whether {a mathematical formula}{ϕα(e)}∪S′ is unsatisfiable can be done in polynomial time. As for each candidate β in (a) (resp. ¬β in (b)) the test for inclusion in S is by Lemma 4 feasible in polynomial time, {a mathematical formula}S′ can for each {a mathematical formula}〈α,e〉,x be constructed in polynomial time; furthermore, the number of x is linear in the input. Hence overall, the test is feasible in polynomial time.  □
       </paragraph>
       <paragraph>
        As a corollary, we obtain that also CKR model checking is tractable.
       </paragraph>
       <paragraph label="Corollary 2">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉and a CKR-interpretation{a mathematical formula}I=〈M,I〉, deciding whether{a mathematical formula}Iis a CKR-model of{a mathematical formula}Kis feasible in polynomial time.
       </paragraph>
       <paragraph label="Proof">
        Indeed, we can by Proposition 5 and item (v) in Definition 11 construct a unique clashing assumption χ in which we collect at each context {a mathematical formula}x∈CtxM all instances of defeasible axioms {a mathematical formula}D(α) in {a mathematical formula}G that are violated by {a mathematical formula}I, and set {a mathematical formula}χ(x)=∅ for each {a mathematical formula}x∈ΔM∖CtxM; then we test whether {a mathematical formula}ICAS(M,I,χ) is a justified CAS-model. By the form of {a mathematical formula}ϕα(x), the number of instances {a mathematical formula}〈α,e〉 is polynomial and by Lemma 3 each test is polynomial. Furthermore, the test for {a mathematical formula}ICAS(M,I,χ) is polynomial by Proposition 9; this proves the result.  □
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Satisfiability
       </section-title>
       <paragraph>
        Based on the results above, we can characterize the complexity of satisfiability testing for CKRs. In general, defeasible axioms can lead to inconsistency that leaves one with a choice for exceptions; e.g., if we had {a mathematical formula}D(A(a)) and {a mathematical formula}D(¬A(a)) in the global knowledge. It is thus no surprise that the problem is intractable in general.
       </paragraph>
       <paragraph label="Theorem 3">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉, deciding whether{a mathematical formula}Khas some justified CAS-model resp. some CKR-model is NP-complete. The NP-hardness holds even if the module structure is fixed and only the assertions in the modules{a mathematical formula}Kmvary (i.e., under data complexity).
       </paragraph>
       <paragraph label="Proof">
        (Sketch) As for membership in NP, we can guess a justified CAS-model {a mathematical formula}ICAS=〈M,I,χ〉 over the (pseudo) Herbrand domain and verify {a mathematical formula}ICAS in polynomial time by Proposition 9. The hardness part is shown by a reduction from 3SAT: further details are provided in A.4.  □
       </paragraph>
       <paragraph>
        In the absence of defeasible axioms, satisfiability is tractable, as clashing assumptions play no role.
       </paragraph>
       <paragraph label="Proposition 10">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉where{a mathematical formula}G⊆LΓ∪LΣ, deciding whether{a mathematical formula}Khas some justified CAS-model resp. some CKR-model is feasible in polynomial time.
       </paragraph>
       <paragraph label="Proof">
        The reason is that the semantics of {a mathematical formula}K over any CAS-interpretation {a mathematical formula}ICAS(M,I,χ) is independent of CAS; thus we can assume χ is void. We then can simplify {a mathematical formula}ϕK to the sentence{a mathematical formula} As for satisfiability, we can as discussed in the proof of Lemma 4 eliminate disjunctions {a mathematical formula}C1⊔C2 from {a mathematical formula}K in polynomial time to avoid an exponential blowup, and arrive at a formula {a mathematical formula}ϕK″.By a standard fixpoint-iteration, we can compute the least (pseudo) Herbrand model of {a mathematical formula}ϕK″ for the universe {a mathematical formula}NK in polynomially many steps (as only polynomially many ground atoms exist), or find out that no model exists. The rule matching in each iteration is polynomial, as the Horn clause bodies form acyclic conjunctive queries; thus the total computation is polynomial.  □
       </paragraph>
      </section>
      <section label="4.3.3">
       <section-title>
        CKR entailment
       </section-title>
       <paragraph>
        For context and global entailment from a CKR, the complexity is dual to the one of satisfiability, as expected.
       </paragraph>
       <paragraph label="Theorem 4">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉, a context name{a mathematical formula}cand an axiom α, deciding whether{a mathematical formula}K⊨c:αresp.{a mathematical formula}K⊨αholds is coNP-complete, and coNP-hardness holds under data complexity and assertional queries α.
       </paragraph>
       <paragraph label="Proof">
        (Sketch) As for membership of {a mathematical formula}K⊨c:α in coNP, since evaluating α at context {a mathematical formula}c amounts to evaluating a universal FO sentence {a mathematical formula}∀x,xc.ϕαCAS(x,xc), in order to refute {a mathematical formula}K⊨c:α we can by Theorem 1 guess a CKR-interpretation {a mathematical formula}I=〈M,I〉 of {a mathematical formula}K that is named relative to N, {a mathematical formula}NK⊆N⊆NI∖NIS, such that (a) {a mathematical formula}I⊨K and (b) {a mathematical formula}I(cI)⊭α, where N includes all constants that occur in α. The test (a) is feasible in polynomial time by Corollary 2, and the test (b) by Lemma 3.The coNP-hardness under the given restrictions follows from the reduction of 3SAT to CKR-model existence in the proof of Theorem 3: the 3SAT instance E is unsatisfiable iff {a mathematical formula}K⊨c:V(c1) resp. {a mathematical formula}K⊨V(c1), say, as this is equivalent to {a mathematical formula}K not having a CKR-model.  □
       </paragraph>
       <paragraph>
        As in the case of satisfiability, entailment is tractable if no defeasible axioms are present.
       </paragraph>
       <paragraph label="Proposition 11">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉where{a mathematical formula}G⊆LΓ∪LΣ, a context name{a mathematical formula}cand an axiom α, deciding whether{a mathematical formula}K⊨c:αresp.{a mathematical formula}K⊨αholds is feasible in polynomial time.
       </paragraph>
       <paragraph label="Proof">
        Extending the argument in the proof of Proposition 10, to decide {a mathematical formula}K⊨c:α we can test whether {a mathematical formula}ϕK″⊨ψα holds, or equivalently whether {a mathematical formula}ϕK″∧¬ψα is unsatisfiable, where {a mathematical formula}ψα is the Horn variant of {a mathematical formula}∀x.ϕαCtx(x,c) that avoids exponential blowup. As {a mathematical formula}ψα can be written as a conjunction of (polynomially many and linear size) Horn clauses as in (A.1). This reduces to a polynomial number of unsatisfiability tests for {a mathematical formula}ϕi=ϕK″∧p1(e1)∧⋯∧pk(ek)∧¬p0(e0), where the {a mathematical formula}ej are fresh (Skolem) constants.By a standard fixpoint-iteration, we can compute the least (pseudo) Herbrand model of {a mathematical formula}ϕi (where equality is replaced by congruence ≈) respectively detect that no model exists. As the bodies of the Horn implications are acyclic and all predicate arities are bounded by a constant, the fixpoint iteration can be done in polynomial time (cf. proof of Lemma 4); as there are polynomially many {a mathematical formula}ϕi, the test {a mathematical formula}ϕK″⊨ψα is feasible in polynomial time.The proof for global entailment {a mathematical formula}K⊨α is similar; this proves the result.  □
       </paragraph>
       <paragraph>
        We conclude with a remark that under suitably limited use of default axioms, satisfiability and CKR entailment would still be tractable, depending on the structure of the knowledge base {a mathematical formula}K. For example, if the global knowledge base contains few defeasible assertions, and contexts do not access other contexts, i.e., eval does not occur. A detailed complexity study is beyond the scope of this paper, however.
       </paragraph>
      </section>
      <section label="4.3.4">
       <section-title>
        Conjunctive queries
       </section-title>
       <paragraph>
        From well-known results in database theory [38], [37], it follows that deciding given a CKR-interpretation {a mathematical formula}I and a conjunctive query Q, deciding whether {a mathematical formula}I⊨Q is NP-complete. As a CKR {a mathematical formula}K can have multiple (even exponentially many) named CKR-models, as expected CQ answering from CKRs is lifted to the second level of the polynomial hierarchy.
       </paragraph>
       <paragraph label="Theorem 5">
        Given a CKR{a mathematical formula}K=〈G,{Km}m∈M〉and a Boolean CQ Q, deciding whether{a mathematical formula}K⊨Qis{a mathematical formula}Π2p-complete. The problem remains{a mathematical formula}Π2p-hard even if the module structure is fixed and only the assertions in the modules{a mathematical formula}Kmvary. If in addition also the query Q is fixed (i.e., under data complexity), then the problem is coNP-complete.
       </paragraph>
       <paragraph label="Proof">
        (Sketch) As for membership in {a mathematical formula}Π2p, to refute Q we can guess a justified CAS-model {a mathematical formula}ICASN=〈M,I,χ〉 such that {a mathematical formula}N=NK and {a mathematical formula}IN=〈M,I〉⊭Q. Indeed, if {a mathematical formula}ICAS=〈M,I,χ〉 is an arbitrary justified CAS-model such that {a mathematical formula}〈M,I〉⊭Q, then by Theorem 1 its named restriction can not satisfy Q either. We can verify that {a mathematical formula}ICASN is a named justified CAS model in polynomial time by Proposition 8, and check that {a mathematical formula}IN⊭Q using an NP oracle in polynomial time; for fixed Q, the latter test is feasible in polynomial time. The {a mathematical formula}Π2p-hardness is shown by a reduction from evaluating quantified Boolean formulas (QBF) Φ of the form {a mathematical formula}∀X∃YE (see A.4 for the complete proof).  □
       </paragraph>
       <paragraph>
        We note that {a mathematical formula}Π2p-hardness can also be shown if alternatively the module structure and the set of assertions (the data) are fixed. Furthermore, the complexity drops to coNP for acyclic CQs, and to NP for CKRs without defeasible axioms; the combined restrictions yield tractability. Indeed, answering acyclic CQs over a relational database is feasible in polynomial time (cf. [37]), and thus the check {a mathematical formula}IN⊭Q in the refutation algorithm in the proof sketch is feasible in polynomial time; this yields coNP membership. On the other hand, if the global knowledge {a mathematical formula}G contains no defeasible axioms, then the guess for a justified CAS-model {a mathematical formula}ICASN in which the query Q has no match in the proof sketch can be eliminated, and following the arguments in the proof of Proposition 10 a single such candidate {a mathematical formula}ICASN can be constructed in polynomial time. Clearly then, the combination of the restrictions yields a query refutation algorithm that runs in polynomial time.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     Datalog translation for CKR in {a mathematical formula}SROIQ-RL
     <paragraph>
      In this section, we present a translation of reasoning from {a mathematical formula}SROIQ-RL CKRs with defeasible axioms into Datalog. It extends a translation for CKRs without defeasible axioms into Datalog presented in [1] with rules for the detection of axiom overriding (i.e., making exceptions) and defeasible propagation of global knowledge; this requires the use of nonmonotonic negation.
     </paragraph>
     <paragraph>
      In particular, we focus on positive instance queries under {a mathematical formula}c- resp. global entailment (negative instance queries can be handled as described at the end of Section 4.1), and on conjunctive queries. For such queries, we provide an implementation considering a core fragment of {a mathematical formula}SROIQ-RL for expressing defeasible axioms that we call {a mathematical formula}SROIQ-RLD. Formally, we denote with {a mathematical formula}SROIQ-RLD the fragment of {a mathematical formula}SROIQ-RL in which (i) {a mathematical formula}D⊓D can not appear as a right-side concept, and (ii) each right-side concept {a mathematical formula}∀R.D has {a mathematical formula}D∈NC. We confine here to CKRs {a mathematical formula}K in which defeasible axioms are of the form {a mathematical formula}D(α) where α is in {a mathematical formula}SROIQ-RLD, and denote by {a mathematical formula}SROIQ-RLD the class of such {a mathematical formula}K. While this restriction is a slight limitation from the view of modeling, as we will illustrate by Example 16 in the following, it allows us to formulate an easier characterization for the datalog translation.
     </paragraph>
     <paragraph>
      For developing a generic datalog encoding, we first introduce a useful normal form for the axioms of {a mathematical formula}SROIQ-RL. After that, we present the translation and argue about its correctness.
     </paragraph>
     <section label="5.1">
      <section-title>
       Normal form
      </section-title>
      <paragraph label="Definition 14">
       In this section, we introduce a normal form for axioms that allows us to represent a CKR {a mathematical formula}K conveniently as facts of a datalog program, as it bounds the number of concept and role constructors to a single application in each axiom. A CKR {a mathematical formula}K=〈G,{Km}m∈M〉 is in normal form, if every non-defeasible axiom in {a mathematical formula}G and {a mathematical formula}Km matches a form in Table 1, and every defeasible axiom in {a mathematical formula}G is of the form {a mathematical formula}D(α) where α is of the form (I) in Table 1.
      </paragraph>
      <paragraph>
       In Table 1 and elsewhere, we assume that in {a mathematical formula}C resp. {a mathematical formula}NCΣ the empty concept ⊥ is available (which is easily expressed by {a mathematical formula}⊥⊑¬⊥). In Table 2 we present a set of rules that can be used to transform any {a mathematical formula}SROIQ-RLD CKR into an “equivalent” CKR in normal form. As in [20], we assume that rule chain axioms in the input are already decomposed in binary role chains.
      </paragraph>
      <paragraph>
       It can be seen that for named interpretations, i.e., of the form {a mathematical formula}ICASNK, every CKR can be rewritten into an equivalent one in normal form (using new symbols).
      </paragraph>
      <paragraph label="Lemma 5">
       For every{a mathematical formula}SROIQ-RLDCKR{a mathematical formula}K=〈G,{Km}m∈M〉over meta and object vocabularies{a mathematical formula}〈Γ,Σ〉, a CKR{a mathematical formula}K′=〈G′,{Km′}m∈M〉over extended vocabularies{a mathematical formula}〈Γ′,Σ′〉can be computed such that
      </paragraph>
      <list>
       <list-item label="(a)">
        all axioms in{a mathematical formula}K′are in normal form;
       </list-item>
       <list-item label="(b)">
        the size of{a mathematical formula}K′is linear in the size of{a mathematical formula}K;
       </list-item>
       <list-item label="(c)">
        for every axiom α on{a mathematical formula}Γ∪Σ:
       </list-item>
      </list>
      <paragraph label="Example 16">
       In the following, we also refer with explicit negated assertions to any normal form ABox assertions of the kind {a mathematical formula}¬A(b), {a mathematical formula}¬R(a,b), {a mathematical formula}a≠b that explicitly appear in the input CKR {a mathematical formula}K. We show how enabling the normal form translation to full {a mathematical formula}SROIQ-RL (i.e. considering also right-hand {a mathematical formula}D⊓D and {a mathematical formula}∀R.D with {a mathematical formula}D∉NC) can cause problems in the interpretation of justifications. Consider the following CKR {a mathematical formula}Knf=〈G,{Km}〉 where:{a mathematical formula} Note that the clashing assumption {a mathematical formula}〈A⊑B1⊓B2,a〉 admits two minimal clashing sets {a mathematical formula}S1={A(a),¬B1(a)} and {a mathematical formula}S2={A(a),¬B2(a)}. However, neither of them can be proved in {a mathematical formula}Knf, thus no justified model exists. On the other hand, if we normalize the right-hand conjunction defeasible axiom with the simple rule:{a mathematical formula} we obtain the CKR {a mathematical formula}Knf′=〈G′,{Km}〉 where:{a mathematical formula} In this case, the only clashing assumption would be {a mathematical formula}〈A⊑X,a〉, which admits only one clashing set {a mathematical formula}S1={A(a),¬X(a)}. Differently from the non-normalized case, {a mathematical formula}S1 can be proved from {a mathematical formula}Knf, thus a justified model exists.Similarly, this can be shown for right-hand {a mathematical formula}∀R.D with {a mathematical formula}D∉NC: that is, the simple translation provided for strict {a mathematical formula}SROIQ-RL axioms can not be applied naively to such defeasible axioms as it might not preserve their justification. ◇
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Translation overview
      </section-title>
      <paragraph>
       We are now prepared to present our translation of entailment reasoning into Datalog with non-monotonic negation. To ease the development, we adopt for it the unique name assumption in any interpretation; this allows us to omit dealing with equality in models, which else can be done by emulating a congruence relation via a standard guess-and-check approach.
      </paragraph>
      <paragraph>
       As mentioned above, it extends a translation of CKR without defeasible axioms into Datalog presented in [1]. That translation was inspired by the materialization calculus {a mathematical formula}Kinst of Krötzsch [20] for instance checking in the description logic {a mathematical formula}SROEL(⊓,×) (in essence, OWL-EL). Briefly, Krötzsch showed that a calculus for that problem can be encoded in a Datalog program, where the rules mimick inference rules. Furthermore, he presented – exploiting a normal form of axioms – a fixed datalog program that gives a universal encoding of the proof systems associated with concrete DL knowledge bases {a mathematical formula}K, where {a mathematical formula}K and the instance query are represented by a set of facts. This technique was carried over to {a mathematical formula}SROIQ-RL and extended for CKRs in [1].
      </paragraph>
      <paragraph>
       In the sequel, we present an extension of this translation for CKRs with defeasible axioms. This extension is non-trivial, as (i) it requires us to deal with exceptions for axioms, via clashing assumptions, which requires the use of non-monotonic negation; and in connection with this, (ii) it requires us to deal with strong negation, as provable falsity of atoms (resp. assertions) is crucial for clashing sets. As for (i), we can take advantage of a mechanism for inheritance axioms from [39], while for (ii), we extend the materialization calculus to conclude negative literals. However, the latter requires us to deal with negative disjunctive information; e.g. from {a mathematical formula}A⊓B⊑C and {a mathematical formula}¬C(a) we can infer {a mathematical formula}(¬A⊔¬B)(a), but neither {a mathematical formula}¬A(a) nor {a mathematical formula}¬B(a); this can not be readily expressed with datalog rules, even in the presence of strong negation; viewing {a mathematical formula}A⊓B⊑C as {a mathematical formula}A⊓¬C⊑¬B, {a mathematical formula}B⊓¬C⊑¬A and mimicking respective inference rules as datalog rules would not work, as the calculus would be incomplete. For this reason, we encode inference of negative literals through individual proofs by contradiction, which will be indicated by presence of a designated atom {a mathematical formula}unsat(⋯) for the literal in the answer set; notably, from the absence of {a mathematical formula}unsat(⋯) we can conclude that the literal is not derivable. Overall, this leads to a linear number of contradiction tests for the literals, which are encoded using designated test rules.{sup:14}
      </paragraph>
      <paragraph>
       The whole translation is rather involved and contains a number of rules and facts that serve different purposes. From a high level structural perspective, the translation has three components:
      </paragraph>
      <list>
       <list-item label="(1)">
        the input translations{a mathematical formula}Iglob, {a mathematical formula}Iloc, {a mathematical formula}ID, {a mathematical formula}Irl, where given an axiom or signature symbol α and {a mathematical formula}c∈N, each {a mathematical formula}I(α,c) is a (possibly empty) set of datalog facts or rules: intuitively, they encode the contents of the global and the local DL knowledge bases as datalog facts and rules. These input translations I are extended to knowledge bases (sets of axioms) S with their signature Σ, by {a mathematical formula}I(S,c)=⋃α∈SI(α,c)∪⋃s∈ΣI(s,c).
       </list-item>
       <list-item label="(2)">
        the deduction rules{a mathematical formula}Ploc, {a mathematical formula}PD, {a mathematical formula}Prl, which are sets of datalog rules: they represent the inference rules for the instance-level reasoning over the translated axioms; and
       </list-item>
       <list-item label="(3)">
        the output translationO, where given an axiom α and {a mathematical formula}c∈N, {a mathematical formula}O(α,c) is either empty or a single datalog fact: O encodes the ABox assertion α that we want to prove to be entailed by the input CKR (in the context {a mathematical formula}c) as a datalog fact.
       </list-item>
      </list>
      <paragraph>
       We will describe next these components, the translation process as such and we will then consider an example.
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Translation rule sets
       </section-title>
       <paragraph>
        The components of the translation comprise in turn groups of rules that serve different purposes: we show here some example rules for each group, while the complete rule sets are given in Table 3, Table 4, Table 5, Table 6, Table 7, Table 8 on the next pages.
       </paragraph>
       <list>
        <list-item label="(i).">
         {a mathematical formula}SROIQ-RLinput translation: Rules in {a mathematical formula}Irl(S,c) translate to datalog facts {a mathematical formula}SROIQ-RL axioms and signature (in a context c). E.g., we translate atomic concept inclusions with the rule {a mathematical formula}A⊑B↦{subClass(A,B,c)}. Note that, for instance level predicates, we distinguish between the asserted (i.e. insta, triplea) and derived (i.e. instd, tripled) atoms: this distinction is needed in the rules for the (defeasible) propagation of knowledge, where we want to recognize which facts are part of the asserted “content” of the global context that might be propagated to lower contexts.
        </list-item>
        <list-item label="(ii).">
         {a mathematical formula}SROIQ-RLdeduction rules: The rules in {a mathematical formula}Prl are the deduction rules corresponding to axioms in {a mathematical formula}SROIQ-RL: e.g., for atomic concept inclusions, we have{a mathematical formula} The rules of {a mathematical formula}Irl and {a mathematical formula}Prl are listed in Table 3. Note that the translation produces purely positive programs: possible derived inconsistencies are represented by the unsat predicate and constrained by the rule (prl-sat). The last argument in the instance level predicates (instd, tripled, eq) keeps track of the hypothesis used in the proofs for contradiction for negative literals (as mentioned in the translation overview): in the translation of instance level assertions in {a mathematical formula}Irl, this parameter is initialized to the constant {a mathematical formula}main. The predicate {a mathematical formula}unsat(t) denotes that the proof relative to the hypothesis t leads to an inconsistency: as noted above, in the case of {a mathematical formula}main this is limited by the constraint (prl-sat). As we adopted the unique name assumption, reasoning on equality can be omitted; an explicit equality assertion raises an inconsistency by the rule (prl-eq), while inequality assertions – assuming that assertions {a mathematical formula}a≠a are not admissible – are simply discarded.
        </list-item>
        <list-item label="(iii).">
         Global and local translations: Global input rules of {a mathematical formula}Iglob encode the interpretation of {a mathematical formula}Ctx in the global context (i.e. conditions from Definition 7). Similarly, local input rules {a mathematical formula}Iloc and local deduction rules {a mathematical formula}Ploc provide the translation and rules for elements of the local object language. In particular for eval expressions in concept inclusions, we have the input rule {a mathematical formula}eval(A,C)⊑B↦{subEval(A,C,B,c)} and the corresponding positive deduction rule:{a mathematical formula} The rules of {a mathematical formula}Iglob, {a mathematical formula}Iloc and {a mathematical formula}Ploc are presented in Table 4.
        </list-item>
        <list-item label="(iv).">
         Defeasible axioms input translation: Input rules in {a mathematical formula}ID provide the translation of defeasible axioms {a mathematical formula}D(α) in the global context: {a mathematical formula}ID(D(α),gk) adds to the program (in the module {a mathematical formula}gk for the global object knowledge) an atom specifying that the asserted axiom is defeasible. For example, {a mathematical formula}D(A⊑B) translates to {a mathematical formula}def_subclass(A,B).
        </list-item>
        <list-item label="(v).">
         Overriding rules: The inheritance and overriding of defeasible axioms is encoded by different sets of deduction rules in {a mathematical formula}PD, inspired by [39]. Overriding rules provide rules defining when an axiom of a certain form is locally overridden. Intuitively, such rules encode the proof of existence for a clashing set for an instance of such axiom. For example, for axioms of the form {a mathematical formula}D(A⊑B), the following overriding rule is added to the local programs:{a mathematical formula} Intuitively, this rule states that, if {a mathematical formula}y=A is included in {a mathematical formula}z=B by a defeasible global axiom ({a mathematical formula}def_subclass(y,z)) and in context c we can prove for {a mathematical formula}x=e that {a mathematical formula}A(e) (i.e., {a mathematical formula}instd(x,y,c,main)) but {a mathematical formula}¬B(e) ({a mathematical formula}nottest_fails(nlit(x,z,c))), then there is an overriding for this axiom with respect to e in context c ({a mathematical formula}ovr(subClass,x,y,z,c)). Here {a mathematical formula}prec(c,g) expresses that context c is more specific than context g, which represents the global context. The condition on the negative part {a mathematical formula}¬B(e) of the clashing set {a mathematical formula}{A(e),¬B(e)} for {a mathematical formula}〈A⊑B,e〉 is verified, exploiting Theorem 2 and the remark after it, by a proof by contradiction: if this “test” does not fail,{sup:15} i.e., after adding the positive version of the literal (in the example {a mathematical formula}B(e)) inconsistency can be derived, then the clashing assumption is justified and we can derive the overriding. In the example rule above, such proof is performed on the term {a mathematical formula}nlit(x,z,c), which represents the negative literal {a mathematical formula}¬instd(x,z,c,main). The complete list of overriding rules in {a mathematical formula}PD is shown in Table 6 ; they incorporate sufficient clashing sets for the clashing assumptions that are made in overriding (cf. Table A.17 in the Appendix).
        </list-item>
        <list-item label="(vi).">
         Inheritance rules: {a mathematical formula}PD provides the rules for defeasible inheritance of axioms from the global context to the local contexts. E.g., the following rule propagates an atomic concept inclusion axiom: if the (possibly defeasible) axiom is in the program of the global context and applicable to a local instance, it is applied unless the latter is recognized as an exception.{a mathematical formula} The inheritance rules in {a mathematical formula}PD are shown in Table 7. Similar as for the rules {a mathematical formula}Prl above, the predicate unsat is used to indicate inconsistency. Note that such rules are applied both to the defeasible and strict axioms: in the latter case, the axioms are always inherited by the lower contexts, as no exception can arise.
        </list-item>
        <list-item label="(vii).">
         Test rules: the last kind of rules in {a mathematical formula}PD are the test rules, which are used to instantiate and define the “environments” for the tests for negative literals in overriding rules. Intuitively, the asserted instance knowledge from the input CKR is stated to belong to the {a mathematical formula}main test environment (note, e.g., the input translation rules for {a mathematical formula}A(b) and {a mathematical formula}R(a,b)). Additional test environments are generated when a proof for contradiction of a negative literal is needed (cf. {a mathematical formula}nlit(x,z,c) in the previous overriding rule example): the environment consists of a copy of the original program to which a positive version of the literal is added to the context in which the overriding is tested. If an inconsistency is found, then the test is successful, otherwise the test fails.A first set of rules is used to instantiate the tests on the base of the form of defeasible axioms. For example, for atomic inclusions, the rule reads as:{a mathematical formula} Similarly, a set of constraints makes sure that, if the test fails, no overriding can take place. For example, for the subClass overriding, we have:{a mathematical formula} A test fails if no clashes (i.e. instances of the predicate unsat) can be found. This is expressed by the rule:{a mathematical formula} Finally, a set of rules generates the test environment by copying the instance knowledge from {a mathematical formula}main and adding the complement of the tested literal. E.g., the following two rules copy all the (class assertion) instance data from {a mathematical formula}main and add the complement for nlit:{a mathematical formula} The set of test rules in {a mathematical formula}PD is shown in Table 8.
        </list-item>
        <list-item label="(viii).">
         Output rules: Finally, the rules in {a mathematical formula}O(α,c) translate ABox assertions that can be verified to hold in context {a mathematical formula}c by applying the rules of the final program. For example, assertions {a mathematical formula}A(a) in a given context {a mathematical formula}c are translated by {a mathematical formula}A(a)↦{instd(a,A,c,main)}. The rules in O are listed in Table 4.
        </list-item>
       </list>
       <paragraph>
        We remark that the translation parts as presented above include all rules that are structurally expected. Logical optimization by eliminating some rules or constraints is possible (e.g. (constr-subc) can be omitted as (ovr-subc) is the single rule defining subclass overriding), but we refrain from this here.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Translation process
       </section-title>
       <paragraph>
        We describe in the following the “translation process” to produce, given a CKR {a mathematical formula}K=〈G,{Km}m∈M〉 in {a mathematical formula}SROIQ-RLD normal form, a program {a mathematical formula}PK(K) that encodes query answering from the CKR-models of {a mathematical formula}K:
       </paragraph>
       <list>
        <list-item label="1.">
         the global program for {a mathematical formula}G is constructed as (where {a mathematical formula}gm,gk are new context names):{a mathematical formula} where {a mathematical formula}GΓ=G∩LΓ, {a mathematical formula}GΣ=G∩LΣD and {a mathematical formula}GΣD={α∈LΣ|D(α)∈GΣ}. Intuitively, {a mathematical formula}PG(G) encodes all metaknowledge information in facts with a context parameter {a mathematical formula}gm, and it encodes the global knowledge (including defeasible axioms){sup:16} in facts with a parameter {a mathematical formula}gk. Notably, {a mathematical formula}PG(G) is a datalog program without negation, and hence it has a unique answer set (which is its least model), if it has a model.
        </list-item>
        <list-item label="2.">
         We define the set of contexts {a mathematical formula}NG as{a mathematical formula} and for every {a mathematical formula}c∈NG its associated knowledge base {a mathematical formula}Kc as{a mathematical formula}
        </list-item>
        <list-item label="3.">
         We define for each {a mathematical formula}c∈NG the each local program{a mathematical formula}PC(c,K) as{a mathematical formula} that is, local programs encode the object knowledge in all modules associated with the context {a mathematical formula}c as datalog facts and include {a mathematical formula}SROIQ-RL deduction rules {a mathematical formula}Prl, local deduction rules {a mathematical formula}Ploc and propagation rules {a mathematical formula}PD for defeasible axioms.
        </list-item>
        <list-item label="4.">
         Finally, the CKR program{a mathematical formula}PK(K) is defined as follow:{a mathematical formula}
        </list-item>
       </list>
       <paragraph>
        Intuitively, the knowledge from the global program {a mathematical formula}PG(G), which is Horn, is passed on to the local programs {a mathematical formula}PC(c,K). The contexts in {a mathematical formula}NG are those relevant for CKR-inference, and we can focus on them.{sup:17} At the local contexts {a mathematical formula}c, clashing assumptions {a mathematical formula}〈α,e〉 are reflected by literals {a mathematical formula}ovr(α,e,c), where α is represented in a reified form; the answer set semantics ensures that these literals must be derived from rules whose bodies resemble clashing sets {a mathematical formula}Sc,〈α,e〉 for {a mathematical formula}〈α,e〉. In turn, the positive literals in {a mathematical formula}Sc,〈α,e〉 must be derived via the materialization calculus, and the negative literals via contradiction proofs defined by the test mechanism mentioned at the beginning of Section 5.2 and previously detailed. In all these derivations, the materialization rules for defeasible axiom must respect the ovr-assumptions.
       </paragraph>
       <paragraph>
        Query answering {a mathematical formula}K⊨c:α is then achieved by testing whether the query, translated into its datalog rendering {a mathematical formula}O(α,c), is a consequence of {a mathematical formula}PK(K), i.e., whether {a mathematical formula}PK(K)⊨O(α,c) holds; for global entailment and conjunctive queries, this is analogous.
       </paragraph>
       <paragraph label="Example 17">
        We consider the translation of {a mathematical formula}KtourD from Example 5 into its CKR program {a mathematical formula}PK(KtourD). In Step 1, the content of the global context {a mathematical formula}G is translated to the global program {a mathematical formula}PG(G). In particular, this program contains the structure of the metaknowledge represented as facts, e.g. {a mathematical formula}insta(cultural_tourist,Ctx,gm,main) and {a mathematical formula}triplea(cultural_tourist,mod,ctourist_m,gm,main). By the rules in {a mathematical formula}ID, {a mathematical formula}PG(G) contains the translation of the defeasible axioms in {a mathematical formula}G. E.g. for {a mathematical formula}D(Cheap⊑Interesting), it includes the atom{a mathematical formula} Note that the rules in {a mathematical formula}Irl also add to {a mathematical formula}PG(G) the “non-defeasible” translation of this axiom: {a mathematical formula}subClass(Cheap,Interesting,gk). Furthermore, {a mathematical formula}PG(G) also contains the translation of the global assertions {a mathematical formula}Cheap(fbmatch) and {a mathematical formula}Cheap(market):{a mathematical formula}In Step 2 of the translation process, the relevant contexts and their associations to the modules are determined. In particular, from the facts above and the rules prl-instd and prl-tripled, we obtain that {a mathematical formula}cultural_tourist∈NG and that {a mathematical formula}Kctourist_m∈Kcultural_tourist. Then, the local programs {a mathematical formula}PC(c,KtourD) for all contexts {a mathematical formula}c are computed: in the case of context {a mathematical formula}cultural_tourist, note that {a mathematical formula}PC(cultural_tourist,KtourD) contains the fact {a mathematical formula}¬Interesting(fbmatch), which is represented as {a mathematical formula}ninsta(fbmatch,Interesting,cultural_tourist). In the translation of local programs, we also add the defeasibility deduction rules of {a mathematical formula}PD, defining the rules for overriding and defeasible propagation of the global knowledge: in particular, the following rule ovr-subc provides the condition for overriding of atomic inclusion axioms like the one considered in our example:{a mathematical formula} Propagation of defeasible atomic inclusion axioms is defined by the rule prop-subc:{a mathematical formula} In Step 3 of the translation, the final program {a mathematical formula}PK(KtourD) results as the union of {a mathematical formula}PG(G) and all the local programs, including {a mathematical formula}PC(cultural_tourist,KtourD).Let us now consider what can be inferred from {a mathematical formula}PK(KtourD). From the contents of {a mathematical formula}G and the context {a mathematical formula}cultural_tourist, it is easy to verify that by the rules{a mathematical formula} This holds because the test (instantiated by the overriding rule on {a mathematical formula}fbmatch) for negative literal {a mathematical formula}nlit(fbmatch,Interesting,cultural_tourist) succeeds: {a mathematical formula}¬Interesting(fbmatch) holds locally and {a mathematical formula}Interesting(fbmatch) is added in the test environment, thus a contradiction is found. Hence the inheritance rule prop-subc is not applicable and {a mathematical formula}PK(KtourD)⊭instd(fbmatch,Interesting,cultural_tourist,main). On the other hand, since {a mathematical formula}PK(KtourD)⊭ovr(subClass,market,Cheap,Interesting,cultural_tourist), rule prop-subc can be applied and{a mathematical formula} These results coincide with the semantic interpretation of overridings given in Example 12. ◇
       </paragraph>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Correctness
      </section-title>
      <paragraph>
       The presented rules and translation provide a sound and complete materialization calculus for instance checking (with respect to {a mathematical formula}c-entailment) and conjunctive query answering on {a mathematical formula}SROIQ-RLD CKRs in normal form. This can be shown by establishing a correspondence between minimal justified CKR-models of {a mathematical formula}K and answer sets of {a mathematical formula}PK(K). Having considered UNA and named models in the definition of our translation, we can concentrate on showing the result on Herbrand models: thus, naming ν in the definition of least CAS-models {a mathematical formula}IˆK(χ,ν) is irrelevant and we will simplify the denotation of such models as {a mathematical formula}IˆK(χ).
      </paragraph>
      <paragraph>
       Let {a mathematical formula}ICAS be a justified named CAS-model. We define the set of corresponding overriding assumptions:{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively, given a CAS-interpretation {a mathematical formula}ICAS=〈M,I,χ〉, we can define a corresponding Herbrand interpretation {a mathematical formula}I(ICAS) of the program {a mathematical formula}PK(K) by including the following atoms in it (see the Appendix for a formal definition):
      </paragraph>
      <list>
       <list-item label="–">
        all facts of {a mathematical formula}PK(K);
       </list-item>
       <list-item label="–">
        {a mathematical formula}instd(a,A,c,main), if {a mathematical formula}I(c)⊨A(a);
       </list-item>
       <list-item label="–">
        {a mathematical formula}tripled(a,R,b,c,main), if {a mathematical formula}I(c)⊨R(a,b);
       </list-item>
       <list-item label="–">
        each ovr-literal from {a mathematical formula}OVR(ICAS);
       </list-item>
       <list-item label="–">
        each literal l with environment {a mathematical formula}t≠main, if {a mathematical formula}test(t)∈I(ICAS) and l is in the head of a rule {a mathematical formula}r∈grnd(PK(K)) with {a mathematical formula}Body(r)⊆I(ICAS);
       </list-item>
       <list-item label="–">
        {a mathematical formula}test(t), if {a mathematical formula}test_fails(t) appears in the body of an overriding rule r in {a mathematical formula}grnd(PK(K)) and the head of r is an ovr literal in {a mathematical formula}OVR(ICAS);
       </list-item>
       <list-item label="–">
        {a mathematical formula}unsat(t)∈I(ICAS), if adding the literal corresponding to t to the local interpretation of its context {a mathematical formula}c violates some axiom of the local knowledge {a mathematical formula}Kc;
       </list-item>
       <list-item label="–">
        {a mathematical formula}test_fails(t), if {a mathematical formula}unsat(t)∉I(ICAS).
       </list-item>
      </list>
      <paragraph>
       Note that {a mathematical formula}unsat(main) is not included in {a mathematical formula}I(ICAS). We can establish the following property, which informally says that the least models of the global context is represented in the least justified named CAS-models.
      </paragraph>
      <paragraph label="Proposition 12">
       Let{a mathematical formula}K=〈G,{Km}m∈M〉be a CKR in{a mathematical formula}SROIQ-RLDnormal form. Then for every least justified CAS-model{a mathematical formula}IˆK(χ)=〈Mˆ,Iˆ,χ〉, it holds that{a mathematical formula}Mˆ=MG, where{a mathematical formula}MGis the least Herbrand model of{a mathematical formula}G.
      </paragraph>
      <paragraph>
       This result follows from the intersection property of CAS-models (Proposition 7): it is easy to verify that the CAS-interpretation {a mathematical formula}ICAS′=〈Mˆ∩MG,Iˆ,χ〉 is also a CAS-model of the CKR {a mathematical formula}K; as {a mathematical formula}IˆK(χ) is a least CAS-model, {a mathematical formula}MG=Mˆ must hold.
      </paragraph>
      <paragraph>
       The next proposition shows that the least Herbrand model {a mathematical formula}MG of {a mathematical formula}G is reflected in the answer set of the global program {a mathematical formula}PG(G). Let {a mathematical formula}I(MG) denoted the Herbrand interpretation for {a mathematical formula}PG(G) that is defined analogously to {a mathematical formula}I(ICAS) above for {a mathematical formula}PK(K).
      </paragraph>
      <paragraph label="Proposition 13">
       Let{a mathematical formula}K=〈G,{Km}m∈M〉be a CKR in{a mathematical formula}SROIQ-RLDnormal form. If{a mathematical formula}Gis satisfiable, then{a mathematical formula}I(MG)is the unique answer set of{a mathematical formula}PG(G); otherwise,{a mathematical formula}PG(G)has no answer sets.
      </paragraph>
      <paragraph>
       The main result on the correctness of the translation is achieved by showing that the answer sets of the final program {a mathematical formula}PK(K) correspond with the least justified models of {a mathematical formula}K as follows:
      </paragraph>
      <paragraph label="Lemma 6">
       Let{a mathematical formula}Kbe a CKR in{a mathematical formula}SROIQ-RLDnormal form. Then
      </paragraph>
      <list>
       <list-item label="(i).">
        for every (named) justified clashing assumption χ, the interpretation{a mathematical formula}S=I(Iˆ(χ))is an answer set of{a mathematical formula}PK(K);
       </list-item>
       <list-item label="(ii).">
        every answer set S of{a mathematical formula}PK(K)is of the form{a mathematical formula}S=I(Iˆ(χ))where χ is a (named) justified clashing assumption for{a mathematical formula}K.
       </list-item>
      </list>
      <paragraph label="Theorem 6">
       The correctness result for instance checking of atomic concepts and roles is then an easy consequence of Lemma 6 and Corollary 1 (cf. the discussion at the end of Section 4.1; negative instance checking can be reduced to unsatisfiability). Let{a mathematical formula}Kbe a CKR in{a mathematical formula}SROIQ-RLDnormal form, and let α and{a mathematical formula}csuch that{a mathematical formula}O(α,c)is defined. Then{a mathematical formula}K⊨c:αiff{a mathematical formula}PK(K)⊨O(α,c).
      </paragraph>
      <paragraph>
       Similarly, we obtain the correctness for conjunctive query answering from the correspondence of Lemma 6. Given a logic program P and a conjunction {a mathematical formula}q(t)=p1(t1)∧⋯∧pm(tm) of atoms {a mathematical formula}pi(ti) in its language, where all variables in {a mathematical formula}ti occur in t, we say that P entails {a mathematical formula}q(t), denoted {a mathematical formula}P⊨q(t), if for every answer set I some ground instance {a mathematical formula}q(c)=p1(c1)∧⋯∧pm(cm) of {a mathematical formula}q(t) exists such that {a mathematical formula}I⊨q(c).
      </paragraph>
      <paragraph>
       Now for a Boolean CQ {a mathematical formula}Q=∃yγ(y) on {a mathematical formula}K, where {a mathematical formula}γ(y)=γ1∧⋯∧γm and {a mathematical formula}γi=ci:αi(ti), let {a mathematical formula}O(Q)=O(αi(t1),c1)∧⋯∧O(αi(tm),cm) denote its translation into the corresponding conjunction of atoms of a logic program, where variables are treated like special constants. Then we obtain:
      </paragraph>
      <paragraph label="Theorem 7">
       Let{a mathematical formula}Kbe a CKR in{a mathematical formula}SROIQ-RLDnormal form, and let{a mathematical formula}Q=∃yγ(y)be a Boolean CQ on{a mathematical formula}K. Then{a mathematical formula}K⊨Qiff{a mathematical formula}PK(K)⊨O(Q).
      </paragraph>
      <paragraph>
       As above, this result is a consequence of Lemma 6 and Corollary 1. Furthermore, it naturally generalizes to the certain answers of general conjunctive queries.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Discussion: justification safeness
      </section-title>
      <paragraph>
       Test environments are needed to check the derivation of negative literals in the clashing sets and thus to assure completeness of justifications. Still, this proof-by-contradiction encoding is less natural than a direct encoding of negative reasoning, where strong negation is used to represent negative instance-level literals and rules are used to conclude negative facts by modus ponens.
      </paragraph>
      <paragraph>
       However, such a direct encoding involves reasoning on disjunctive knowledge which is not easy to represent using ASP interpretation of disjunctive rules [27]. For example, consider the negative version of rule (prl-subcnj) to reason on negative instances of {a mathematical formula}A1⊓A2⊑B. Using disjunction in the head of rules, one could write the rule as:{a mathematical formula} As noted in the example in Section 5.2, this would lead to a calculus that is incomplete with respect to negative reasoning. For example, from {a mathematical formula}A⊓B⊑C,¬C(a),D⊑A⊓B we can classically infer {a mathematical formula}¬D(a), but neither {a mathematical formula}¬A(a) nor {a mathematical formula}¬B(a): however, the interpretation of the rule above would lead to two distinct answer sets, one in which {a mathematical formula}¬A(a) holds and one where {a mathematical formula}¬B(a) holds, but in neither of them {a mathematical formula}¬D(a) is inferred.
      </paragraph>
      <paragraph>
       One possible solution is to require a notion of justification safeness for the input knowledge base. Intuitively, this condition guarantees that whenever an axiom gives rise to reasoning on negative disjunctive cases, one of the disjuncts is provable from the knowledge base. Then, proofs for justifications do not depend on non-deterministic choices. For instance, in the example above, a knowledge base K containing {a mathematical formula}A⊓B⊑C would be justification safe if, whenever {a mathematical formula}¬C(a) is derivable, either {a mathematical formula}¬A(a) or {a mathematical formula}¬B(a) can be derived from K. If the input CKR is justification safe, the translation can be modified by omitting the test environment mechanism and using direct reasoning on negative instance-level literals (sample deduction rules for this setting are shown in Table A.18).
      </paragraph>
      <paragraph>
       Furthermore, in such a modified program we could also recognize violations of safeness by reasoning inside the program (namely, on the least justified CAS-models {a mathematical formula}Iˆ(χ)). In the case of {a mathematical formula}A⊓B⊑C, a violation of safety can be recognized with the following rule:{a mathematical formula} By adding rules of this kind, if unsafe is derived we recognize that the input CKR was not justification safe and thus it might happen that some of the justifications are not established in an answer set. Justification safeness, however, ensures completeness of justification in each answer set. Furthermore, the direct encoding of negative reasoning would also be complete for both positive and negative instance queries.
      </paragraph>
     </section>
    </section>
    <section label="6">
     CKRew: CKR datalog rewriter prototype
     <paragraph>
      The datalog translation from above has been implemented in a prototype called CKRew(CKR datalog Rewriter). After a brief description of its structure and implementation details, we will report on an experimental evaluation with respect to performance and different degrees of defeasibility.
     </paragraph>
     <section label="6.1">
      <section-title>
       Prototype description
      </section-title>
      <paragraph>
       CKRew has been implemented as a Java-based command line application. It accepts as input global and local modules of the initial CKR represented as RDF files (either as distinct N3 RDF files or as a single TRIG file) that contain OWL-RL axioms in normal form and produces as output a single .dlv text file that contains the complete datalog rewriting for the input CKR. The newly added contextual primitives have been defined in an RDF vocabulary (imported in the translation); in particular, axiom defeasibility assertions have been encoded as OWL axiom annotations hasAxiomType having the value defeasible. The conceptual system architecture is depicted in Fig. 2. The prototype takes advantage of the DL-to-datalog rewriter DReW[40], which is used in the translation of global and local OWL axioms into their datalog counterparts. The loading of OWL-RL RDF files is managed using the OWL API 3.4.{sup:18} The CKR system structure is managed by the prototype; external calls to the DLV solver{sup:19} by means of the DLVWrapper Java library [41] are used to determine the set of contexts and their module associations, which are extracted from the computed answer set(s) of the global program {a mathematical formula}PG(G).
      </paragraph>
      <paragraph>
       The translation process, which is depicted in Fig. 2, follows the strategy in Section 5. After checking that the CKR represented in the input files is in the required {a mathematical formula}SROIQ-RLD normal form, the system proceeds to produce the rewriting. First of all, the global module is translated (step ➀), basically using translation rules from {a mathematical formula}Iglob and {a mathematical formula}Irl; if an axiom is recognized as defeasible, the corresponding defeasible declaration in {a mathematical formula}ID is added to the program. The global program {a mathematical formula}PG(G) is completed by adding the deduction rules from {a mathematical formula}Prl. The set of contexts and their association to local modules are then computed by submitting the global program to DLV and retrieving the instances of Context concept and hasModule role in the resulting answer sets (step ➁). Using this information, the prototype computes local knowledge bases for all contexts and applies the rewriting process to compute the local program {a mathematical formula}PC(c,K) for each of them using rules in {a mathematical formula}Iloc and {a mathematical formula}Irl (step ➂). The resulting program is completed with deduction rules {a mathematical formula}Ploc and {a mathematical formula}PD and saved in a file (step ➃). The final program {a mathematical formula}PK(K) is then evaluated using the DLV solver, resorting to the syntax defined by the output translation O (step ➄). Note that DLV supports query answering, and also allows the evaluation of non-ground conjunctive queries on the produced CKR program.
      </paragraph>
      <paragraph>
       A demo of the prototype, together with RDF files implementing the examples in [2], [1], can be found at http://ckrew.fbk.eu/.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Experimental evaluation
      </section-title>
      <paragraph>
       In this section, we describe an experimental evaluation that we have conducted to measure the performance of the prototype, which is similar in spirit to the evaluation of the RDF based implementation of non-defeasible CKRs in [42]. In particular, we want to study the behavior of the translation and the resulting program in presence of different dimensions of the input CKR or degrees of defeasibility. We note, however, that scalability of the approach is inherently limited by the coNP-completeness of the reasoning problems (reaching {a mathematical formula}Π2p-completeness in case of conjunctive queries).
      </paragraph>
      <section label="6.2.1">
       <section-title>
        Generation of synthetic testsets
       </section-title>
       <paragraph>
        To create our test sets, we developed a simple generator that can output synthetically generated CKRs with certain features. For each generated CKR, the generator takes as input:
       </paragraph>
       <list>
        <list-item label="–">
         the number n of contexts (i.e. local named graphs) to be generated;
        </list-item>
        <list-item label="–">
         the dimensions of the signature to be declared (number m of base classes, l of properties and k of individuals);
        </list-item>
        <list-item label="–">
         the number of axioms for the global and local modules (number of global TBox, ABox and RBox axioms and number of TBox, ABox and RBox axioms per context);
        </list-item>
        <list-item label="–">
         optionally, the number of additional local eval axioms and the number of individuals to be propagated across contexts.
        </list-item>
        <list-item label="–">
         optionally, the percentage of axioms in the global context to be declared as defeasible and the percentage of local overriding instances of such axioms.
        </list-item>
       </list>
       <paragraph>
        Intuitively, the generation of a CKR proceeds as follows:
       </paragraph>
       <list>
        <list-item label="1.">
         The contexts (named {a mathematical formula}:c0,…,:cn) are declared in the global context named graph and are linked to a different module name ({a mathematical formula}:m0,…,:mn), corresponding to the named graph containing their local knowledge.
        </list-item>
        <list-item label="2.">
         Base classes (named {a mathematical formula}:A0,…,:Am), object properties ({a mathematical formula}:R0,…,:Rl) and individuals ({a mathematical formula}:a0,…, :ak) are added to the global graph: these symbols are used in the generation of global and local axioms.
        </list-item>
        <list-item label="3.">
         Then generation of global axioms takes place. We chose to generate axioms as follows, in order to create realistic instances of knowledge bases:
        </list-item>
        <list-item label="4.">
         The same generation criteria are then applied in the case of local graphs representing the local knowledge of contexts.
        </list-item>
        <list-item label="5.">
         If specified, the requested number for eval axioms of the form {a mathematical formula}eval(A,C)⊑B and a set of individuals in the scope of the eval operator (i.e. as local members of A) are added to local contexts graphs.
        </list-item>
        <list-item label="6.">
         If specified, the requested percentage of global axioms is generated (using the same criteria as above) which are declared defeasible: in particular, in order to control the number of local overridings, the defeasible axioms are generated using “fresh” symbols (i.e. not occurring in the signature of other strict global or local axioms).
        </list-item>
        <list-item label="7.">
         If defeasible axioms have been generated, a fixed number of instances is added to randomly chosen contexts. For example, for {a mathematical formula}D(A⊑B), in case of a positive instance {a mathematical formula}A(a) is added locally, while in case of a negative (exceptional) instance {a mathematical formula}A(a),¬B(a) is added. The percentage of such instances that represent overridings (i.e. clashing sets) is specified by the user.
        </list-item>
       </list>
      </section>
      <section label="6.2.2">
       <section-title>
        Evaluation setup
       </section-title>
       <paragraph>
        Evaluation experiments were carried out on a 4 core Dual Intel Xeon Processor machine with 32 GB 1866 MHz DDR3 RAM, standard S-ATA (7.200 RPM) HDD, running a Linux RedHat 6.5 distribution. We allocated 10 GB of memory to the JVM running the prototype command line application and the utility scripts managing the upload, profiling and reporting of test instances. The datalog engine that we used to test the computation of the answer sets of the translated programs (and in the computation of the global context structure) is the latest DLV solver.{sup:20}
       </paragraph>
       <paragraph>
        Using the profiling methods, we could measure the time needed (1) to translate the whole CKR program, (2) to interact with DLV in computing the global model and (3) to compute the answer sets for the final program via DLV. We will use these values to evaluate our reasoning method with respect to different dimensions of input CKR and different levels of defeasibility.
       </paragraph>
      </section>
      <section label="6.2.3">
       <section-title>
        TS1: scalability evaluation
       </section-title>
       <paragraph>
        The first experiments served to determine the (average) translation and model computation time depending on the number of contexts and their contents. In other words, we wanted to answer the following question: What is the effect on the amount of time requested for rewriting and model computation with respect to the number and size of contexts of a CKR? Using the CKR generator described above, we generated a suite of CKRs whose profiles are shown in Table 10. We will refer to this suite as TS1: this test set (basically corresponding to an extension of TS1 from [42]) contains sets of CKRs with an increasing number of contexts, in which CKRs have an increasing number of axioms; no eval-axioms or defeasible axioms were added during the generation.
       </paragraph>
       <paragraph>
        We have tested the rewriting and answer set computation over 3 random generations of the TS1 profile and 5 independent test runs: the different generation instances of TS1 are necessary in order to reduce the impact of special cases in the random generation. The results of the experiments on TS1 are reported in Table 11. In the table, for each of the generated CKRs (referred by number of contexts and number of base classes in the first two columns), we show their number of total effective input axioms in column Statements (averaged on the 3 versions of TS1). The column Prog. size reports the corresponding dimensions of the output program in terms of program statements. The rewriting time is listed in the following two columns: Gl. time lists the (average) time in milliseconds for rewriting and computing the answer sets for the global context, and RW time lists the (average) time for the rewriting of the complete CKR program. The column DLV time lists the (average) time in milliseconds needed for computing the answer sets of the output program. A dash indicates a timeout, which was set to 20 minutes (1.200.000 ms).
       </paragraph>
       <paragraph>
        In order to analyze the results, the behavior of the rewriting and answer sets computation has been plotted to graphs, shown in Fig. 3. Each of the series represents a set with a fixed number of contexts (1 to 100) and each point a CKR. The x axis represents the number of asserted statements, while the y axis shows the time in milliseconds. To better visualize the behavior of the series, we plotted a trend line for each of the series: the lines represent an approximation of the data trend calculated by polynomial regression.{sup:21}
       </paragraph>
       <paragraph>
        Some conclusions can be drawn from these data and graphs. In particular, we note that the expected behavior of the rewriting process and answer set computation is reflected by these results. About the rewriting, it is clear that the dimension of the output program (and the corresponding rewriting time) is basically linear in the dimension of the input CKR. In fact, the size of the output program can be determined quite precisely given the applied rules and the translation process: some variability may occur due to the translation of the local signatures, which is determined randomly in the axiom generation. The size of the output program can be estimated by considering how each of its components is built. The global program contains a fixed number of statements to represent CKR primitives and deduction rules; its variable part depends on the size of the signature, the number of global axioms and finally a fixed number of statement for each context (for context declaration, declaration of the associated module and module association). For each of the contexts, every local program needs a fixed number of statements for the declaration of CKR primitives and the local prec statement; then its size depends on the local signature declaration and the number of local axioms.
       </paragraph>
       <paragraph>
        On the other hand, DLV answer sets computation for the final program is clearly not linearly dependent from the size of the program, and the computational hardness of the materialization solution is evident in the graphs growth. From the results, it is evident that the feasibility of the reasoning is affected by the number of contexts of the CKR: for example, this can be seen in Fig. 3.b by comparing the case of 1 context and 1000 classes (having 7014 statements, with DLV time 33469 ms.) with the cases of 5 contexts and 350 classes (having 7396 statements, with DLV time 14554 ms.) and 50 contexts and 35 classes (having 6655 statements, with DLV time 4803 ms.). This suggest that the modularization of knowledge provided by contextual sub-programs may allow to limit local reasoning and manage larger numbers of local axioms. On the other hand, it is evident that while the rewriting is applicable to large datasets, as expected, the current materialization based translation does not allow to scale to very large number of (complex) statements and contextual structures.
       </paragraph>
      </section>
      <section label="6.2.4">
       <section-title>
        TS2: defeasibility evaluation
       </section-title>
       <paragraph>
        The second set of experiments over the CKR prototype served to determine the impact of defeasible axioms. Basically they were modeled inspired by the defeasibility evaluation of Casini et al. in [43]. The question is as follows. Which effect does the percentage of global defeasible axioms and their overridings have on the time for rewriting and model computation?
       </paragraph>
       <paragraph>
        Using the CKR generator, we generated a second suite TS2 of CKRs. We fixed the number of contexts to 5 and number of global axioms to 175: basically, this amounts in size and form to the case of 5 contexts and 50 classes in TS1; this setting was chosen to fix a reasonable number of contexts and axioms to a case that was proved to be easily treatable from the tests on TS1. We generated 9 groups of CKRs with a percentage of global axioms declared as defeasible varying from 10% to 100%. Each group has 10 CKRs with different percentage of overridings (from 10% to 100%, with an increase of 10% across CKRs). No random local axioms have been generated; instead, 10 local instances of each (strict or defeasible) global axiom scheme have been generated. In case of defeasible axioms, these instances are negative (i.e. clashing sets) and their number yields the specified overriding percentage, while the other instances are positive. In this way, we keep the number of instances fixed. Intuitively, this allows us to verify the behavior of the prototype in CKRs with equal size but different ratios of defeasibility and overridings.
       </paragraph>
       <paragraph>
        We tested computing the rewriting and the answer sets over 5 instances of the TS2 profile and 5 independent test runs for each instance. Results of the experiments on TS2 are reported in Table 12, where the first two columns show the percentages of defeasible axioms and overridings, respectively. The following columns (number of statements, output program size, global and total rewriting time, and DLV computation time) are as in Table 11, where DLV time is for computing one answer set. Finally, last column reports the number of test instances (of the nlit kind) in the computed model.
       </paragraph>
       <paragraph>
        For a representative selection of the data, Fig. 4 shows histograms for the output program size, the rewriting time and the DLV time. The y-axis represents the number of statements for program size and time in ms. for rewriting and DLV time respectively, while on the x-axis the bars are ordered by percentage of overridings (from 10% to 100%). Each series represents a different percentage of defeasibility (from 10% to 100%), i.e. a CKR group in Table 12.
       </paragraph>
       <paragraph>
        As we can see from the data and the graphs, the program size grows linearly with number of defeasible axioms and overridings. As in the case of scalability, we can precisely count the number of added rules and statements in the output program by considering the translation process. As we specified above, in this experiment the numbers of global and local axioms, contexts and signature size are fixed. For each defeasible global axiom, one corresponding defeasibility atom (e.g. {a mathematical formula}def_subclass) has to be added to the global program. The evident growth in the number of statements w.r.t. the number of overridings is also justified by the larger number of axioms that is needed in general to represent the negative instances of axioms. For example, in the case of an atomic subsumption {a mathematical formula}A⊑B, its positive instance is a single assertion axiom {a mathematical formula}A(a), while the set expressing its negative assertion (that is, its clashing set), is {a mathematical formula}{A(a),A⊓B⊑⊥,B(a)}. Also, negative instances need the declaration of a larger set of auxiliary signature elements.
       </paragraph>
       <paragraph>
        In the rewriting time histogram, the growth is less evident given the quite limited size of the reference CKRs.{sup:22}
       </paragraph>
       <paragraph>
        As expected, the number of defeasible axioms and overridings clearly influences the time needed for the model computation by DLV. In particular, if we fix the percentage of overridings, DLV computing time grows polynomially in the percentage of defeasible axioms.{sup:23} Moreover, by fixing the percentage of defeasible axioms (i.e. each sub-table in Table 12), model computation also grows polynomially in the percentage of overridings.{sup:24}
       </paragraph>
       <paragraph>
        This behavior can also be justified by the growth in the number of test environments needed to verify the conditions for overriding of such defeasible axioms: in particular, by definition of the rules, a test literal is added to the model for each instance (exceptional or not) of a defeasible axiom. Note that, by definition of test rules, each instantiation of a test environment (corresponding to a different instance of a test literal) leads to a copy of the instance knowledge derived from the {a mathematical formula}main environment. This intuition is reflected by the results in last column of Table 12, representing the number of test literals in the computed model: as expected (cf. introduction of Section 5.2), this value is linearly dependent on the percentage of defeasible axioms in the input CKR.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="7">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section, we relate and compare our proposal with other approaches for including notions of defeasibility contextual systems and in description logics. In particular, we compare it to non-monotonic multi-context systems (MCS) [9], multi-context systems under argumentation semantics [29], typicality in DLs [30], and nonmonotonic description logics [31]. We will briefly present these approaches and aim to give an intuition about analogies and differences in our representation of defeasible inheritance (also by means of some representative examples).
     </paragraph>
     <section label="7.1">
      <section-title>
       Non-monotonic multi-context systems
      </section-title>
      <paragraph>
       The idea of multi-context systems (MCS) is to align knowledge from different contexts in a single system using special bridge rules, dating back to [7]. We consider here the expressive concept of non-monotonic MCS in [9], in which contexts may be based on possibly different monotonic and non-monotonic logic, and bridge rules can be non-monotonic. The semantics of nonmonotonic MCS is defined in terms of equilibria: intuitively, an equilibrium is a collection of one belief set (local model) per context that verifies the knowledge content of contexts and the knowledge propagated through bridge rules.
      </paragraph>
      <paragraph>
       Formally, in this approach a logic is abstractly defined as a triple {a mathematical formula}L=(KBL,BSL,ACCL), where {a mathematical formula}KBL is the set of well-formed KBs of L, which are sets of formulas; {a mathematical formula}BSL⊆2BL is the set of possible belief sets of the logic, where {a mathematical formula}BL is base set of beliefs; and {a mathematical formula}ACCL:KBL→2BSL is the set of accepted belief sets, i.e., the set of belief sets associated with a KB kb (thus providing the “semantics” of L). Propagation of knowledge across knowledge bases in different logics can be defined using bridge rules: given a set of logics {a mathematical formula}L1,…,Ln, a bridge rule for {a mathematical formula}Li has the form:{a mathematical formula} where {a mathematical formula}rk∈{1,…,n}, {a mathematical formula}pk∈BLk, and s is a formula of {a mathematical formula}Li. A nonmonotonic MCS is then a collection {a mathematical formula}M=(C1,…,Cn) of contexts {a mathematical formula}Ci=(Li,kbi,bri), where {a mathematical formula}Li=(KBi,BSi,ACCi) is the logic of the context, {a mathematical formula}kbi∈KBi is a knowledge base and {a mathematical formula}bri is a set of bridge rules for {a mathematical formula}Li over logics {a mathematical formula}L1,…,Ln. An equilibrium of M is a collection {a mathematical formula}S=(S1,…,Sn) of belief sets {a mathematical formula}Si∈BSi for the context {a mathematical formula}Ci such that {a mathematical formula}Si∈ACCi(kbi)∪{head(r)|r∈app(bri,S)}, where {a mathematical formula}head(r)=(i:s) for any bridge rule r of form (10), and {a mathematical formula}app(bri,S) consists of all bridge rules {a mathematical formula}r∈bri such that (i) {a mathematical formula}pj∈Sj, for {a mathematical formula}1≤j≤k and (ii) {a mathematical formula}pj∉Sj, for {a mathematical formula}k&lt;j≤n.
      </paragraph>
      <paragraph>
       The idea of CKRs with defeasible inheritance based on justifiable assumptions may also be realized within the nonmonotonic MCS framework of [9], where contexts {a mathematical formula}Ci with local semantics (acceptable belief sets over a local knowledge base {a mathematical formula}kbi) can add via bridge rules formulas to their {a mathematical formula}kbi depending on the local belief sets of the contexts. Adopting open bridge rules, i.e. bridge rules with variables that are instantiated over a given domain (using standard names in case, similar as in [44]), we may encode the global context {a mathematical formula}G as an MCS context {a mathematical formula}g and associate each element x of the domain with a context name in the MCS. We then may mimic satisfaction relative to assumptions as in CAS-interpretations with bridge rules that access {a mathematical formula}G to determine whether axioms resp. axiom instances must be evaluated at x (if {a mathematical formula}x∈CtxM). In particular, defeasible axioms α of the kind {a mathematical formula}D(C⊑D) can be encoded using auxiliary concept names {a mathematical formula}Aα and bridge rules:{a mathematical formula} and for defeasible concept assertions {a mathematical formula}D(A(c)) bridge rules{a mathematical formula} Intuitively, {a mathematical formula}Aα serves as guard for the inclusion which by default is true for an individual, and thus the inclusion axiom applies to it; likewise, a concept assertion is true by default. The guard is blocked if a violation of the inclusion (an exception) is provable. The equilibria of the so constructed MCS are then akin to CKR-models. However, while this or a similar MCS approach is elegant, we need to extend the language and basically encode the problem in a framework that is very expressive and propositional in nature. Furthermore, currently only limited computational support is available for MCS. Above we aim at a formalization from first principles (giving a model-based semantics) that is suitable for realization in a well-supported host formalism.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       MCS under argumentation semantics
      </section-title>
      <paragraph>
       A different non-monotonic semantics for MCS, based on argumentation, was proposed in [29]. The authors aimed at reasoning in presence of “imperfect” knowledge in ambient intelligence where knowledge is distributed across different contexts.
      </paragraph>
      <paragraph>
       In this formulation, a MCS is a collection {a mathematical formula}C=(C1,…,Cm) of contexts of the form {a mathematical formula}Ci=(Vi,Ri,Ti) where {a mathematical formula}Vi is the vocabulary (i.e. propositional literals) of {a mathematical formula}Ci, {a mathematical formula}Ri is the set of rules of the context, and {a mathematical formula}Ti is a local preference ordering over all contexts. Rules can be either local rules, corresponding to local knowledge of {a mathematical formula}Ci, or mapping rules, which basically amount to bridge rules across different contexts. Local rules are either strict, denoted {a mathematical formula}ril:ai1,…,ain−1→ain, or defeasible, denoted {a mathematical formula}rid:bi1,…,bin−1⇒bin, where all {a mathematical formula}aij and {a mathematical formula}bij are from {a mathematical formula}Vi; they represent strict and “soft” knowledge in the local theories, respectively. Mapping rules, denoted {a mathematical formula}rim:ak11,…,akn−1n−1⇒ain with every {a mathematical formula}akjj∈Vkj where {a mathematical formula}kj∈{1,…,m} and {a mathematical formula}ain∈Vi, are regarded as defeasible and serve to “import” knowledge from other contexts into {a mathematical formula}Ci. Finally, the local preference ordering{a mathematical formula}Ti=[Ck1,…,Ckm], {a mathematical formula}kj∈{1,…,m}, on contexts expresses confidence in the knowledge imported from the other contexts by mapping rules.
      </paragraph>
      <paragraph>
       The argumentation semantics for these MCS is based on the common argumentation semantics of Defeasible Logic (cf. [45]) extended with distribution of knowledge and preferences across contexts. A support relation for the MCS C is a set {a mathematical formula}SRC of triples {a mathematical formula}(Ci,PTpi,pi) where {a mathematical formula}Ci∈C, {a mathematical formula}pi∈Vi, and {a mathematical formula}PTpi is a proof tree for {a mathematical formula}pi using the local and mapping rules in {a mathematical formula}Ri (we omit further details); any such triple is an argument for {a mathematical formula}pi. The set {a mathematical formula}ARGSCi of arguments for all {a mathematical formula}pi∈Vi represents all possible logical consequences in {a mathematical formula}Ci that are derivable using local or mapping rules.
      </paragraph>
      <paragraph>
       If consequences are derived using “external” knowledge by mapping rules, conflicts over a literal {a mathematical formula}pi are resolved using the local context preference {a mathematical formula}Ti, where clashes across arguments are considered. Intuitively, an argument Aattacks another argument B if (i) A has a literal {a mathematical formula}pi in its consequences, (ii) B has the complementary literal {a mathematical formula}∼pi in its consequences, and (iii) {a mathematical formula}∼pi is a consequence of some defeasible local rule. An argument AdefeatsB at {a mathematical formula}pi if {a mathematical formula}pi has lower rank than the complementary {a mathematical formula}∼pi in B, where the rank of a literal {a mathematical formula}pi in {a mathematical formula}Ci is 0 if {a mathematical formula}pi∈Vi and is the rank of {a mathematical formula}Cj in {a mathematical formula}Ti if {a mathematical formula}pi∈Vj≠Vi. In case of conflicting literals in mapping rules, an argumentation line{a mathematical formula}AL for a literal {a mathematical formula}pi can be formed as a sequence of arguments, possibly from different contexts, where attacks are extended to sequences. Based on attacks and defeats across arguments resp. argumentation lines, each literal in a MCS is either found justified, i.e. proved by a non-defeatable argument, or rejected, i.e. it can not overcome attacks from stronger arguments.
      </paragraph>
      <paragraph>
       Compared to our CKR, we first note the different setting of defeasible MCS as in [29]: every context is seen as an independent agent having its own knowledge and preferences (ordering) on contexts. A CKR instead has a global structure of contexts and it only represents one level of “preference”, namely the precedence of {a mathematical formula}G w.r.t. local contexts. Viewing a CKR as a defeasible MCS (with preferences), the local preference ordering of each context {a mathematical formula}ci may thus be defined as {a mathematical formula}Ti=[ci,G]. Local and global axioms of a CKR can be translated to local rules and mapping rules, where similar as for nonmonotonic MCS in Section 7.1 schematic (open) rules are used that are instantiated over a concrete domain. In particular, global default axioms can be here introduced as local defeasible rules: e.g., {a mathematical formula}D(A⊑B) can be represented (in every context {a mathematical formula}ci) as the defeasible rule {a mathematical formula}Ai(x)⇒Bi(x). Global subsumptions can be propagated to each context as strict local rules: e.g. if {a mathematical formula}C⊑D is in {a mathematical formula}G, then every context {a mathematical formula}ci contains the strict rule {a mathematical formula}Ci(x)→Di(x). We can relate eval expressions to mapping rules: e.g. {a mathematical formula}eval(A,{c1})⊑C in context {a mathematical formula}c2 is expressible by the mapping rule {a mathematical formula}A1(x)⇒C2(x). Note, however, that eval expressions are strict inclusions and may contain complex context expressions; thus a proper encoding of eval-expression using defeasible and strict rules is more involved.
      </paragraph>
      <paragraph>
       Our notion of overriding of a defeasible axiom compares to a “conflict” among two arguments for conflicting literals in [29]. In a CKR, conflicts occur only among arguments of the global and the local contexts. Using the above preference ordering, local arguments are preferred over global arguments and thus relate to clashing sets; as in our semantics, they serve to justify the local conclusions. To this extent, the clashing assumptions {a mathematical formula}χ(x) for context x are akin to the rejected global arguments of x. However, the emerging semantics differs from our CKR-models in an important respect: while defeasible MCS resolve conflicts deterministically using local preferences, CKRs incorporate reasoning by cases; this manifests in tractable inference of literal queries from defeasible MCs, while literal queries on all CKR-models are intractable in general.
      </paragraph>
      <paragraph>
       As for valuation, [46] showed how to translate defeasible MCSs into single theories of Defeasible Logic, where the idea is to include strict and defeasible (mapping) rules in such a theory and to express the local preference ordering on contexts by rule priorities. Our translation of CKRs into datalog programs is analogous in this respect, and shows how a fragmented knowledge base can be compiled in a way such that available efficient tools can be utilized for reasoning.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Normality in description logics
      </section-title>
      <paragraph>
       In the area of Description Logics, a number of different proposals have been made to incorporate non-monotonic features, dating back at least to terminological default logic [47]. We refer for a more extensive bibliography and classification to [48], where preferential approaches (e.g. [49], [50]), circumscription-based approaches (e.g. [51], [52]) and others (e.g., [53]) are distinguished. We concentrate here on some recent proposals that aim at supporting defeasible subsumption respectively entailment, viz. [30], [54], [31], [51], [52], and we omit here works that aim at establishing semantic properties of entailment relations (such as rational closure [50], [55], [56]) or consider a finer grained notion of defeasibility depending on the nature of the relationship between elements of the vocabulary (cf. [48]). This is because our interest stands, at this point, with a basic mechanism for a formalism with explicit hierarchical structure, which is usually not reflected in nonmonotonic entailment relations.
      </paragraph>
      <section label="7.3.1">
       <section-title>
        Typicality in DLs
       </section-title>
       <paragraph>
        Default assumptions about properties of the members in a class C and the properties of prototypical elements of C, as defined in [30], [54], are closely related notions. Giordano et al. [30] formalize in their logic {a mathematical formula}ALC+Tmin the intuition that a prototypical element of a concept C is a “generic element” of C. This definition stands on the possibility to organize objects in a generic-specific hierarchy, formally a partial order &lt;, where {a mathematical formula}y&lt;x means that object y is more generic (less specific) than object x. For instance, if x is a red Ferrari car and y is a yellow one, {a mathematical formula}x&lt;y models that a Ferrari is more typically red than yellow.
       </paragraph>
       <paragraph>
        Formally, the language of the description logic {a mathematical formula}ALC is extended with the typicality operator T: each (possibly complex) concept C in the language is associated with an extended concept {a mathematical formula}T(C) representing its “typical” instances. In knowledge bases, extended concepts can appear on the left-hand sides of concept inclusions in the TBox and as concepts of assertions in the ABox.
       </paragraph>
       <paragraph>
        The semantics of the typicality operator is obtained by extending DL interpretations with a preference relation on the domain. Thus, a {a mathematical formula}ALC+T interpretation is a structure {a mathematical formula}〈ΔI,I,&lt;〉 where {a mathematical formula}〈ΔI,I〉 is a usual {a mathematical formula}ALC interpretation and &lt; is irreflexive and transitive relation over {a mathematical formula}ΔI. The relation has to satisfy a smoothness condition, which eliminates infinitely decreasing chains: for each subset {a mathematical formula}S⊆ΔI, for every {a mathematical formula}x∈S, either {a mathematical formula}x∈min&lt;⁡(S) or some {a mathematical formula}y∈min&lt;⁡(S) exists such that {a mathematical formula}y&lt;x, where {a mathematical formula}min&lt;⁡(S)={x∈S|∄y∈S.y&lt;x} are the minimal elements of S under &lt;. The interpretation of the extended concept {a mathematical formula}T(C)I corresponds then to {a mathematical formula}min&lt;⁡CI. As noted by Giordano et al., this can be seen as a modal expression w.r.t. &lt;: by defining {a mathematical formula}(□C)I={x∈ΔI|∀y∈ΔI.y&lt;x→y∈CI}, the typical elements of a concept C are described by {a mathematical formula}(C⊓□¬C)I.
       </paragraph>
       <paragraph>
        While this models typicality, it does not yet enforce that elements of a concept C must belong to its typical subconcept {a mathematical formula}T(C), unless known otherwise. Basically, this corresponds to introducing non-monotonicity in the logic {a mathematical formula}ALC+T. This is achieved by restricting the models to those which minimize the set of exceptional instances of concepts; the resulting logic is {a mathematical formula}ALC+Tmin. By exploiting the modal definition of typical concepts, exception minimization is effected by considering the models in which {a mathematical formula}(¬□¬C)I is minimized, for each C with typicality, in parallel; respective minimal models are called preferred models. Query entailment in {a mathematical formula}ALC+Tmin is then defined via entailment from all preferred models.
       </paragraph>
       <paragraph>
        Compared to our approach, the main analogy of the approach by Giordano et al. is that membership of an element in a concept must be blocked. However, the way this is achieved is fundamentally different: Giordano et al. use semantic model minimization, where the blocking results for minimal subsets of non-specific elements of C (i.e., the set ◇C); intuitively, every element of C is regarded as prototypical unless this is infeasible. Our approach instead is syntactic and consequence-based, as exceptions have to be justified in terms of a semantic consequence. Notably, different from preferred models there is no notion of minimality in the definition of our CKR-models, even though it comes as a property (Proposition 6). Furthermore, we deal with explicit modular structure of a knowledge base and cross-references, which Giordano et al. do not consider. We note that, similarly to our approach, the authors recently proposed in [57] a datalog translation for reasoning with a typicality extension of {a mathematical formula}SROEL(⊓,×).
       </paragraph>
       <paragraph>
        Our approach is geared towards syntactically guided exception handling in query answering, and not conceived as a logic of typicality of individuals per se. Nonetheless, prototypical concepts may be mimicked in our formalism using an extra concept for each concept C, say {a mathematical formula}CT, for the typical elements of C, and by the axioms{a mathematical formula} which state that prototypical C's are C's and that C's are prototypical unless the contrary is entailed; {a mathematical formula}CT is then used for the prototypical concept. A deeper formal analysis of the correspondence between the two approaches will require some adaptation of the approach in [30] to {a mathematical formula}SROIQ-RL, and is beyond the present paper.
       </paragraph>
      </section>
      <section label="7.3.2">
       <section-title>
        Normality via circumscription
       </section-title>
       <paragraph>
        Besides [30], another approach to express typicality or “normality” via model-based minimization is to exploit McCarthy's circumscription principle [58]. This has been adopted for DLs e.g. in [51] and [52], where in particular DL-LiteR and {a mathematical formula}EL resp. {a mathematical formula}EL⊥ were considered, which are related to the OWL profiles OWL QL and OWL EL, respectively. From a semantical perspective, similar considerations as for the approach of Giordano et al. apply at a general level. Computationally, instance checking is in circumscribed DL-LiteR{a mathematical formula}Π2p-complete and in {a mathematical formula}EL⊥ ExpTime-hard; while circumscription of {a mathematical formula}SROIQ-RL has to the best of our knowledge not been studied, results in [59] and Section 3 suggest that instance checking should be coNP-complete, and thus have the same complexity under CKR-model semantics.
       </paragraph>
      </section>
     </section>
     <section label="7.4">
      Nonmonotonic description logic {a mathematical formula}DLN
      <paragraph>
       A recent approach to overriding in description logics was presented by Bonatti et al. [31], which aims at a natural representation of exceptional classes of elements in a DL and retaining its tractability; in this way, applicability to large size knowledge bases should be secured.
      </paragraph>
      <paragraph>
       A family {a mathematical formula}DLN of non monotonic DLs is defined by extending a generic base DL {a mathematical formula}DL with an operator NC for normality concepts, which are the prototypical “normal” instances of type C, and with defeasible inclusions (DIs){a mathematical formula}C⊑nD between concepts, which can be interpreted as “normally, instances of C are instances of D, unless stated otherwise.”
      </paragraph>
      <paragraph>
       Formally, for each concept C in {a mathematical formula}DL, a normality concept name NC is added to {a mathematical formula}DLN; defeasible inclusions {a mathematical formula}C⊑nD require that C is from {a mathematical formula}DL and D from {a mathematical formula}DLN. A {a mathematical formula}DLN knowledge base has the form {a mathematical formula}K=S∪D, where {a mathematical formula}S and {a mathematical formula}D are disjoint finite sets of {a mathematical formula}DLN axioms and defeasible inclusions, respectively.
      </paragraph>
      <paragraph>
       In any {a mathematical formula}DLN interpretation {a mathematical formula}I, the inclusion {a mathematical formula}NC⊑C must hold for each NC. The semantics of a defeasible inclusion {a mathematical formula}C⊑nD w.r.t. normal individuals is defined by resorting to the set {a mathematical formula}satI(C⊑nD)={NE|∀x∈NEI,x∉CI∨x∈DI}, which are the normal concepts satisfied by the DI in {a mathematical formula}I; the idea is that normality concepts NE can not satisfy all DIs, and thus some DIs may be in conflict on NE. To decide which DIs then should be overridden, a priority relation {a mathematical formula}δ1≺δ2 is used expressing that {a mathematical formula}δ1 has higher priority and is preferred over {a mathematical formula}δ2. While ≺ could be any strict partial order, Bonatti et al. mainly concentrated on specificity, i.e., {a mathematical formula}(C1⊑nD1)≺(C2⊑nD2) iff {a mathematical formula}S⊨C1⊑C2 and {a mathematical formula}S⊨C2⋢C1.{sup:25} Using {a mathematical formula}satI and ≺, the semantics of overriding is recursively defined by a function {a mathematical formula}ovd: a DI δ is overridden in NC for interpretation {a mathematical formula}I (denoted {a mathematical formula}NC∈ovdI(δ)), if no interpretation {a mathematical formula}J exists such that: (i) {a mathematical formula}J⊨S; (ii) {a mathematical formula}NC∈satJ(δ); (iii) {a mathematical formula}NCJ≠∅; and (iv) for any other {a mathematical formula}δ′∈D s.t. {a mathematical formula}δ′≺δ, it holds that {a mathematical formula}satI(δ′)∖ovdI(δ′)⊆satJ(δ′), i.e. {a mathematical formula}J satisfies all non-overridden higher priority DIs that are satisfied in {a mathematical formula}I. Based on this, an interpretation {a mathematical formula}I satisfies a {a mathematical formula}DLN axiom α, if {a mathematical formula}I⊨α for {a mathematical formula}α∈S, and if for every normality concept NC, it holds that {a mathematical formula}NC∈satI(α)∪ovdI(α) if {a mathematical formula}α∈D.
      </paragraph>
      <paragraph>
       To decide satisfaction in the presence of defeasible inclusions, Bonatti et al. provided a translation that compiles defeasible inclusions away. Intuitively, it proceeds as follows. First a set Σ of relevant normality concepts NC has to be fixed, which must include the normality concepts occurring in the initial KB. Given a linearization {a mathematical formula}δ1,…,δn of {a mathematical formula}(D,≺), the KB {a mathematical formula}KΣ is built from {a mathematical formula}K=S∪D by augmenting {a mathematical formula}S along the linearization while omitting overridden DIs, as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        set {a mathematical formula}K0=S∪{NC⊑C|NC∈Σ};
       </list-item>
       <list-item label="2.">
        for {a mathematical formula}i=1,…,n: let {a mathematical formula}Ki=K(i−1) and consider {a mathematical formula}δi=Di⊑nEi; add to {a mathematical formula}Ki every {a mathematical formula}δiNC=(NC⊓Di⊑Ei), {a mathematical formula}NC∈Σ, s.t. {a mathematical formula}K(i−1)∖{δNC|δ⊀δi}∪{δiNC}⊭NC⊑⊥;
       </list-item>
       <list-item label="3.">
        finally, let {a mathematical formula}KΣ=Kn.
       </list-item>
      </list>
      <paragraph>
       Intuitively, in each step the KB is enriched with an axiom {a mathematical formula}δiNC if it does not cause an inconsistency in NC; otherwise, the DI is omitted, corresponding to an overriding w.r.t. NC.
      </paragraph>
      <paragraph>
       Compared to our approach, the overall idea of individual exceptions and axiom overriding is similar in spirit. A notable difference is the extended notion of precedence between defeasible axioms in {a mathematical formula}DLN. In our formalism, precedence is via the CKR structure, viz. from the global context to the local contexts. Accordingly, we can simulate a {a mathematical formula}DLN knowledge base {a mathematical formula}K=S∪D with void preference by representing the defeasible inclusions of {a mathematical formula}D as defeasible axioms in the global context {a mathematical formula}G and the strong axioms {a mathematical formula}S as a single local context.
      </paragraph>
      <paragraph>
       Another relevant difference is that our formalism has no notion of “normal” concepts: every individual is “normal” w.r.t. all axioms, but can be exceptional w.r.t. given defeasible axioms. Thus while our formalism is not capable of reasoning about classes of “normal” and “exceptional” individuals, it can deal with property inheritance at the instance level; we illustrate this on the situs inversus example.
      </paragraph>
      <paragraph label="Example 18">
       [31], rephrasedWhile normally humans have their heart oriented to the left part of their chest, in the exceptional case of situs inversus the heart is positioned towards the right part. We want to represent this fact while ensuring that the other anatomical features of such humans are not overridden. We can represent this scenario as a CKR {a mathematical formula}Ksi=〈G,{Km1}〉 where{a mathematical formula} In this case, it is easy to verify that {a mathematical formula}Ksi has a CKR model {a mathematical formula}I in which d1 is overridden, as it has a justified CAS-model with {a mathematical formula}χ(c1)={〈Human⊑∃hasHeartPosition.{chest-left},bob〉} and clashing set {a mathematical formula}S={Human(bob), {a mathematical formula}¬hasHeartPosition(bob,chest-left)} for the clashing assumption. On the other hand, d2 is naturally inherited even by the exceptional individual: that is, we have that {a mathematical formula}I(c1M)⊨hasNosePosition(bob,face-center). ◇
      </paragraph>
      <paragraph>
       As for the case of clashing inheritance, let us consider as in [31] a classic example.
      </paragraph>
      <paragraph label="Example 19">
       Nixon diamondWe can easily represent the classical Nixon diamond, considered in [31, Example 9], also in our formalism as a CKR {a mathematical formula}Knd=〈G,{Km1}〉, where{a mathematical formula} This CKR has two CKR models corresponding to the two possible overridings of the defeasible axioms (with the same priority). In particular, we have a CKR model {a mathematical formula}I1 s.t. {a mathematical formula}I1(c1)⊨Pacifist(nixon) with {a mathematical formula}χ1(c1)={〈Republican⊑¬Pacifist,nixon〉} and the clashing set S= {a mathematical formula}{Republican(nixon),Pacifist(nixon)}, and symmetrically a CKR model {a mathematical formula}I2 s.t. {a mathematical formula}I2(c1)⊨¬Pacifist(nixon) with {a mathematical formula}χ2(c1)={〈Quaker⊑Pacifist,nixon〉} and clashing set {a mathematical formula}S={Quaker(nixon),¬Pacifist(nixon)}. Thus it holds that {a mathematical formula}Knd⊭c:Pacifist(nixon) and {a mathematical formula}Knd⊭c:¬Pacifist(nixon); similarly, neither {a mathematical formula}Pacifist(nixon) nor {a mathematical formula}¬Pacifist(nixon) is concluded by the approach of Bonatti et al. However, if we change d2 to {a mathematical formula}D(Republican⊑Hawk) and add in {a mathematical formula}G the axioms {a mathematical formula}Dis(Hawk,Pacifist), {a mathematical formula}Hawk⊑Activist, {a mathematical formula}Pacifist⊑Activist, then for the modified CKR {a mathematical formula}Knd′ we obtain {a mathematical formula}Knd′⊨c:Activist(nixon) in our approach, while one can not infer {a mathematical formula}Activist(nixon) from the corresponding knowledge base using Bonatti et al.'s approach; this demonstrates that the latter is not geared towards reasoning by cases if conflicts surface. ◇
      </paragraph>
      <paragraph>
       A distinctive feature of our approach over [31] and others is of course the possibility to define a complex contextual structure of the knowledge base, allowing contextual reasoning inside each module. Moreover, our definition of defeasibility allows for an extension of the materialization calculus that was developed for the monotonic case and its implementation in the datalog rewriter, where the rewriting is not data dependent and can be done without solving reasoning problems on the knowledge base.
      </paragraph>
      <paragraph>
       Regarding implementation and test results, we note that the defeasibility tests are similar: both study the effect of varying the degree of defeasible axioms and their overridings (which in turn is similar to the tests carried out by Casini et al. in [43]). However, the results are hard to compare, as they have been carried out on ontologies in {a mathematical formula}EL, which is a DL language of different characteristics than {a mathematical formula}SROIQ-RL.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Further details
     </section-title>
     <section label="A.1">
      {a mathematical formula}SROIQ syntax and semantics
      <paragraph>
       Table A.13 shows the syntax and semantics of {a mathematical formula}SROIQ.
      </paragraph>
     </section>
     <section label="A.2">
      FO-translation for {a mathematical formula}SROIQ-RL
      <paragraph>
       In Table A.14, we present a FO-translation for contextualized {a mathematical formula}SROIQ-RL axioms: given a {a mathematical formula}SROIQ-RL axiom α in {a mathematical formula}LΣe, the formula {a mathematical formula}∀x.ϕα(x,xc), where {a mathematical formula}x=x1,x2,…,xn is a list of variables and {a mathematical formula}xc expresses that α is in the context {a mathematical formula}xc.
      </paragraph>
      <paragraph>
       The translation rules are recursively defined using additional set of rules for left-side and right-side expressions: translations {a mathematical formula}βE(x,xc) and {a mathematical formula}γE(x,xc) for left-side and right-side expressions E are defined in Table A.15, Table A.16, respectively. Note that the translation of eval-expressions, i.e., {a mathematical formula}βeval(A,C)(x,xc) and {a mathematical formula}βeval(R,C)(x,xc), omits the context argument {a mathematical formula}xc in {a mathematical formula}βC(yc); this context-free form serves to represent the global knowledge base {a mathematical formula}G. Thus, a concept A is represented for contexts by the binary predicate {a mathematical formula}A(x,xc), while in the global knowledge base by the unary predicate {a mathematical formula}A(x); similar for roles etc.
      </paragraph>
      <paragraph>
       More generally, the context-free form {a mathematical formula}ϕα(x) (resp., {a mathematical formula}βE(x), {a mathematical formula}γE(x)) of {a mathematical formula}ϕα(x,xc) (resp., {a mathematical formula}βE(x,xc), {a mathematical formula}γE(x,xc)) is obtained by omitting the context argument {a mathematical formula}xc; it is applicable to axioms {a mathematical formula}α∈LΓ∪LΣ, i.e., of the global knowledge base {a mathematical formula}G (and expressions E occurring in them).
      </paragraph>
      <paragraph label="Proof of Lemma 1">
       Then, more formally Lemma 1 can be established. We show the claim for the contextualized FO-translation {a mathematical formula}ϕK,xc in (5); the result for the ordinary translation {a mathematical formula}ϕK is then obvious.To prove the result, we need to show that each axiom α in K can be written as a universal Horn sentence {a mathematical formula}∀x.ϕα(x,xc), where {a mathematical formula}x=x1,…,xn is a list of free variables in {a mathematical formula}ϕα(x,xc) depending on the type of the axiom α as follows:
      </paragraph>
      <list>
       <list-item label="–">
        if α is an assertion, then {a mathematical formula}n=0 (and x is omitted);
       </list-item>
       <list-item label="–">
        if α is a concept inclusion axiom, then {a mathematical formula}n=1; and
       </list-item>
       <list-item label="–">
        if α is a role inclusion axiom or a role constraint, then {a mathematical formula}n=2.
       </list-item>
      </list>
      <paragraph>
       Furthermore, the context-constraint translation of {a mathematical formula}α∈LΣ is {a mathematical formula}ϕαCtx(x,xc):=Ctx(xc)→ϕα(x,xc), and the clashing-constraint translation is {a mathematical formula}ϕαCAS(x,xc):=Ctx(xc)∧appα(x,xc)→ϕα(x,xc), where {a mathematical formula}appα is a predicate that informally represents that in context {a mathematical formula}xc the axiom α is applicable for x. That is, {a mathematical formula}appα represents the complement of the clashing assumptions in a CAS-interpretation {a mathematical formula}I=(M,I,χ) and contains all tuples {a mathematical formula}e,c over {a mathematical formula}NIΣ such that {a mathematical formula}〈α,e〉 is not in {a mathematical formula}χ(c). If the interpretation {a mathematical formula}I is named relative to N, we can restrict to tuples over N.
      </paragraph>
      <paragraph>
       In abuse of notation, we also denote with {a mathematical formula}∀x.ϕα(x,xc) such a Horn rewriting. Note that in the presence of disjunction ⊔, the natural rewriting (which treats {a mathematical formula}(C1⊔C2)⊓C3⊑D as {a mathematical formula}C1⊓C3⊑D, {a mathematical formula}C2⊓C3⊑D) may have exponential size; otherwise, it is of polynomial size. The blowup can be avoided by normalizing axioms using auxiliary concepts, or at the level of translation, auxiliary predicates {a mathematical formula}PC1⊔C2(x1,xc) for {a mathematical formula}C1⊔C2 that are defined by Horn clauses {a mathematical formula}∀x1.βCi(x1,xc)→PC1⊔C2(x1,xc), for {a mathematical formula}i=1,2.
      </paragraph>
      <paragraph>
       Furthermore, also the context-free translation {a mathematical formula}ϕα(x), the context-constraint translation{a mathematical formula}ϕαCtx(x,xc), and the context-constraint translation{a mathematical formula}ϕαCAS(x,xc) can be easily rewritten to conjunctions of Horn clauses of the form (A.1), where now in the antecedent {a mathematical formula}Ctx and {a mathematical formula}appα may occur; again we shall assume in abuse of notation that they are of this form.
      </paragraph>
      <paragraph label="Proof of Proposition 2">
       The FO-translation {a mathematical formula}∀x.ϕα(x) of any {a mathematical formula}SROIQ-RL axiom α can be rewritten as a conjunction {a mathematical formula}⋀i=1ℓ∀xiγi(x,xi) of Horn clauses with {a mathematical formula}γi is in (A.2). If {a mathematical formula}ϕα(e) is not valid, then for some clause {a mathematical formula}γi a substitution {a mathematical formula}θ:xi→NI must exist such that the assertion set{a mathematical formula} is satisfiable; as {a mathematical formula}Sθ∪{ϕα(e)} is unsatisfiable, {a mathematical formula}Sθ is a clashing set. On the other hand, each clashing set S for {a mathematical formula}〈α,e〉 must violate some ground instance of some clause {a mathematical formula}γi, and thus modulo equality among constants (as determined by all CAS-models {a mathematical formula}ICAS′ that are NI-congruent with some justified CAS-model {a mathematical formula}ICAS, we must have {a mathematical formula}Sθ⊆S for some θ; the size of {a mathematical formula}γi is linear in the size of {a mathematical formula}γi(e,xiθ) and thus of α, and likewise is the size of {a mathematical formula}Sθ.  □
      </paragraph>
     </section>
     <section label="A.3">
      <section-title>
       CKR models: semantic properties
      </section-title>
      <paragraph label="Proof of Proposition 3">
       If {a mathematical formula}α≡β holds, then {a mathematical formula}ϕα(x) and {a mathematical formula}ϕβ(x) are logically equivalent. Thus items (ii) and (v) in the definition of CAS-model hold for α iff they hold for β replacing α (in particular also in {a mathematical formula}χ(x)). Furthermore, {a mathematical formula}S∪{ϕα(e)} and {a mathematical formula}S∪{ϕβ(e)} are equi-satisfiable for all sets of formulas S; hence, the clashing assumptions {a mathematical formula}〈α,e〉 and {a mathematical formula}〈β,e〉 have the same clashing sets. It follows that a CAS-model {a mathematical formula}ICAS=〈M,I,χ〉 for {a mathematical formula}K is justified iff the CAS-model {a mathematical formula}ICAS′=〈M,I,χ′〉 in which β replaces α in χ is justified for {a mathematical formula}K′. Hence the CKR-models of {a mathematical formula}K and {a mathematical formula}K′ coincide.  □
      </paragraph>
      <paragraph label="Proof of Proposition 5">
       We proceed by contraposition. Suppose that {a mathematical formula}ICAS′⊭K. Hence, item (v) of a CAS-model must be violated for some {a mathematical formula}D(α)∈G and {a mathematical formula}x∈CtxM; the same pair also violates (v) for {a mathematical formula}ICAS. For the second part, assume that {a mathematical formula}ICAS′ is not justified. Hence, some {a mathematical formula}〈α,e〉∈χ′(x) for some {a mathematical formula}x∈CtxM is not justified. That is, no clashing set S for {a mathematical formula}〈α,e〉∈χ(x) exists such that {a mathematical formula}ICAS″⊨S for every CAS-model {a mathematical formula}ICAS″=〈M″,I″,χ′〉 that is NI-congruent with {a mathematical formula}ICAS′. As every such {a mathematical formula}ICAS″ is also NI-congruent with {a mathematical formula}ICAS and {a mathematical formula}χ(x)=χ′(x), no clashing set S for {a mathematical formula}〈α,e〉∈χ(x) either can exist to witness that {a mathematical formula}〈α,e〉∈χ(x) is justified wrt. {a mathematical formula}ICAS; hence {a mathematical formula}ICAS is not justified.  □
      </paragraph>
      <paragraph label="Proof of Proposition 6">
       Towards a contradiction, suppose that some {a mathematical formula}x∈CtxM exists such that {a mathematical formula}χ′(x)⊊χ(x), i.e., some {a mathematical formula}〈α,e〉∈χ(x)∖χ′(x) exists. As {a mathematical formula}ICAS′⊨K it follows that (a) {a mathematical formula}I′(x)⊨ϕα(e). Furthermore, as {a mathematical formula}ICAS=〈M,I,χ〉 is justified for {a mathematical formula}K, there exists a clashing set {a mathematical formula}S=S〈α〉e,x such that {a mathematical formula}ICAS″⊨S for every CAS-model {a mathematical formula}ICAS″=〈M″,I″,χ〉 of {a mathematical formula}K that is NI-congruent with {a mathematical formula}ICAS. Now let {a mathematical formula}ICAS‴=〈M′,I′,χ〉. As {a mathematical formula}ICAS′⊨K and {a mathematical formula}χ′(x)⊆χ(x), it follows that {a mathematical formula}ICAS‴⊨K as well (item (v) is monotonic in enlarging clashing assumptions). Furthermore, by construction {a mathematical formula}ICAS‴ is NI-congruent with {a mathematical formula}ICAS′ and thus also with {a mathematical formula}ICAS. Thus it follows that (b) {a mathematical formula}I′(x)⊨S. From (a) and (b) follows {a mathematical formula}I′(x)⊨S∪{α(e)}. This however contradicts that S is a clashing set for {a mathematical formula}〈α,e〉, as {a mathematical formula}S∪{α(e)} would be satisfiable. This proves the result.  □
      </paragraph>
      <paragraph label="Proof of Proposition 7">
       The sentence {a mathematical formula}ϕK defined in (8) characterizes the CAS-models of a {a mathematical formula}SROIQ-RL CKR {a mathematical formula}K; as it amounts to a Horn sentence, its models relative to an interpretation of the constants symbols NI are closed under intersections. As {a mathematical formula}ICASi=〈Mi,Ii,χ〉, {a mathematical formula}i∈{1,2}, are CAS-models of {a mathematical formula}K, it follows that {a mathematical formula}ICAS=〈M1∩M2,I1∩I2,χ〉 is a CAS-model of {a mathematical formula}K as well. (Alternatively, this can be assessed straight from the definition of CAS-model (Definition 11), as α resp. {a mathematical formula}∀x.ϕα(x) and {a mathematical formula}Km resp. {a mathematical formula}ϕKm amount to Horn sentences, and their models wrt. an interpretation of NI are closed under intersection.)For the second part, assume without loss of generality that {a mathematical formula}ICAS1 is justified. That is, {a mathematical formula}〈α,e〉∈χ(x) for {a mathematical formula}x∈CtxM1 implies that some clashing set {a mathematical formula}S=S〈α,e〉,x for {a mathematical formula}〈α,e〉 exists such that {a mathematical formula}ICAS′⊨S for every CAS-model {a mathematical formula}ICAS′ of {a mathematical formula}K that is NI-congruent with {a mathematical formula}ICAS1. As {a mathematical formula}CtxM⊆CtxM1 and {a mathematical formula}ICAS1 is NI-congruent with {a mathematical formula}ICAS, it follows that if {a mathematical formula}x∈CtxM then {a mathematical formula}〈α,e〉∈χ(x) has the witnessing clashing set S relative to {a mathematical formula}ICAS. Consequently, {a mathematical formula}ICAS is justified for {a mathematical formula}K as well.  □
      </paragraph>
      <paragraph label="Proof of Lemma 2">
       By Lemma 1 the sentence {a mathematical formula}ϕK captures {a mathematical formula}K; these sentences amount to a conjunction {a mathematical formula}⋀i=1ℓ∀xiγi(x,xi) where {a mathematical formula}γi(x,xi) is the Horn clause (A.2). By construction, the interpretation {a mathematical formula}IN is named relative to N; Furthermore for each assignment {a mathematical formula}θ:xi→NIs the antecedens of {a mathematical formula}γiθ evaluates to false in {a mathematical formula}IN, if for some {a mathematical formula}pi, {a mathematical formula}i≥1, we have {a mathematical formula}θ(x)∉N for some variable x in {a mathematical formula}xi: any concept or role is false outside {a mathematical formula}NI, and equality atoms in the antecendent are of the form {a mathematical formula}xj≈c where {a mathematical formula}c∈N. Thus it follows that {a mathematical formula}I,θ⊨γi(e,xi) implies that {a mathematical formula}IN,θ⊨γi(e,xi) holds. Hence, it follows that {a mathematical formula}I⊨ϕK implies {a mathematical formula}IN⊨ϕK which proves the claim.  □
      </paragraph>
      <paragraph label="Proof of Theorem 1">
       Suppose that {a mathematical formula}ICAS⊨K, where {a mathematical formula}ICAS=〈M,I,χ〉. Then it follows from Lemma 2 that for any {a mathematical formula}ICASN=〈MN,IN,χN〉 the items (i), (ii) and (iv) of Definition 11 hold. Item (iii) holds by an extension of the argument in Lemma 2 to the contextualized form of Horn clauses in (A.1), which respects eval expressions: if {a mathematical formula}〈x,y〉∈modMN such that {a mathematical formula}y=mMN, then {a mathematical formula}〈x,y〉∈modM and {a mathematical formula}y=mM, and thus it follows from Lemma 1 we have that {a mathematical formula}I(x)⊨ϕKm,xc(x). Furthermore, we have {a mathematical formula}x∈NM; if for some axiom {a mathematical formula}α∈Km an assignment θ to {a mathematical formula}x,xi,y1,…yk in (A.1) maps some variable outside {a mathematical formula}NI, then some {a mathematical formula}pj(x,xi,yj) evaluates to false under {a mathematical formula}θ′=θ∪{xc↦x}, and hence {a mathematical formula}IN(x),θ′⊨γi(x,xi,xc); otherwise, as {a mathematical formula}IN(x) and {a mathematical formula}I(x) coincide on {a mathematical formula}θ′ and {a mathematical formula}I(x),θ′⊨γi(x,xi,xc), we again have {a mathematical formula}IN(x),θ′⊨γi(x,xi,xc). Hence, it follows {a mathematical formula}IN(x)⊨ϕα(x), and consequently {a mathematical formula}IN(x)⊨ϕKm,xc(x).Finally, by construction of {a mathematical formula}χN also item (v) holds: let {a mathematical formula}d∉{e|〈α,e〉∈χN(x)} for {a mathematical formula}D(α)∈G and {a mathematical formula}x∈CtxMN. If d is over {a mathematical formula}N∪NI, then {a mathematical formula}d∉{e|〈α,e〉∈χ(x)}, and hence {a mathematical formula}I(x)⊨ϕα(d) holds; similar as in Lemma 2, we then conclude that {a mathematical formula}IN(x)⊨ϕα(d) holds. Otherwise, if d is not over {a mathematical formula}N∪NM, then in the Horn rewriting of {a mathematical formula}ϕα(d), in each clause {a mathematical formula}γi(d,xi) in (A.2) some constant {a mathematical formula}d∉N∪NI occurs in the antecedent; hence, {a mathematical formula}γi(d,xi) evaluates to false under any assignment to {a mathematical formula}xi.We next show that {a mathematical formula}ICASN is justified if {a mathematical formula}ICAS is justified. Towards a contradiction, suppose {a mathematical formula}ICASN is not justified. Then some {a mathematical formula}〈α,e〉∈χN(x) is not justified, i.e., for every clashing set {a mathematical formula}S=S〈α,e〉,x for {a mathematical formula}〈α,e〉, there exists some CAS-model {a mathematical formula}ICASN′=〈MN′,IN′,χN〉 of {a mathematical formula}K that is NI-congruent to {a mathematical formula}ICAS and {a mathematical formula}IN′(x)⊭S. In particular, this must hold for the S witnessing that {a mathematical formula}〈α,e〉 is justified wrt. {a mathematical formula}ICAS; without loss of generality, in S no constants from {a mathematical formula}NI∖(NIS∪N) occur. Consider then the CAS-interpretation {a mathematical formula}ICAS′=〈M′,I′,χ〉 that results from {a mathematical formula}ICAS by changing the interpretations of concept and role names in {a mathematical formula}M resp. {a mathematical formula}I to those in {a mathematical formula}MN′ resp. {a mathematical formula}IN′. It holds that {a mathematical formula}ICAS′⊨K and {a mathematical formula}ICAS′ is NI-congruent with {a mathematical formula}ICAS (as no {a mathematical formula}c∈NI∖N occurs in {a mathematical formula}K and {a mathematical formula}χN⊆χ), but {a mathematical formula}I′(x)⊭S; this contradicts that {a mathematical formula}〈α,e〉 is justified at x w.r.t. {a mathematical formula}ICAS. Hence, {a mathematical formula}ICASN is justified.It remains to show that each {a mathematical formula}〈α,e〉∈χ(x) is justified by some clashing set {a mathematical formula}S=S〈α,e〉,x with constants from N. By Proposition 2, without loss of generality S amounts to a ground instance of some clause {a mathematical formula}γi(e,xi) in (A.2). As {a mathematical formula}ICASN⊨S holds, by construction we must have that {a mathematical formula}cMN∈NMN holds for each constant c that occurs in {a mathematical formula}pj(e,xi,jθ), {a mathematical formula}j&gt;0; thus, we can replace each c in S with some {a mathematical formula}d∈N such that {a mathematical formula}cMN=dMN. By safety of (A.2), this turns S into an equivalent clashing set w.r.t. the name assignment given by {a mathematical formula}ICAS resp. {a mathematical formula}ICASN.  □
      </paragraph>
     </section>
     <section label="A.4">
      <section-title>
       Proofs of section on reasoning and complexity
      </section-title>
      <paragraph label="Proof of Theorem 3 (continued)">
       The hardness part is shown by a reduction from 3SAT, and in fact for a fixed set of inclusion axioms, that is, under data complexity. Let {a mathematical formula}E=⋀i=1mγi be an instance of 3SAT over propositional atoms {a mathematical formula}X={x1,…,xn}. Without loss of generality, each clause {a mathematical formula}γi in E is either positive or negative. Then we construct {a mathematical formula}K as follows, where {a mathematical formula}V,F,T,A are concepts, {a mathematical formula}P1,P2,P3,N1,N2,N3 are roles, and {a mathematical formula}x1,…,xn, {a mathematical formula}c1,…,cm are individual constants.
       <list>
        the global knowledge {a mathematical formula}G contains defeasible axioms {a mathematical formula}D(V⊑T) and {a mathematical formula}D(V⊑F) and a module association {a mathematical formula}∃mod.{m}(c);a single module {a mathematical formula}Km that contains the inclusion axioms:{a mathematical formula} where ⊥ stands for {a mathematical formula}A⊓¬A. Furthermore, {a mathematical formula}Km contains assertions{a mathematical formula}V(xh), {a mathematical formula}h=1,…,n, and{a mathematical formula}Pj(ci,xij) for {a mathematical formula}i=1,…,m and {a mathematical formula}j=1,2,3 such that the clause {a mathematical formula}γi is of form {a mathematical formula}xi1∨xi2∨xi3,{a mathematical formula}Nj(ci,xij) for {a mathematical formula}i=1,…,m and {a mathematical formula}j=1,2,3 such that the clause {a mathematical formula}γi is of form {a mathematical formula}¬xi1∨¬xi2∨¬xi3.Conversely, if
       </list>
       <paragraph>
        {a mathematical formula}K has some justified CAS-model {a mathematical formula}ICAS(M,I,χ), without loss of generally we assume it is named, and moreover that it is a pseudo Herbrand model (as no equality occurs in {a mathematical formula}G and {a mathematical formula}Km). Due to {a mathematical formula}T⊓F⊑⊥, we have that {a mathematical formula}χ(c) must contain at least one of {a mathematical formula}〈V⊑F,xh〉 and {a mathematical formula}〈V⊑T,xh〉; on the other hand, it can not contain both: indeed, in this case {a mathematical formula}I(c)⊨¬T(xh) and {a mathematical formula}I(c)⊨¬F(xh); we then can modify {a mathematical formula}I(c) to {a mathematical formula}I′(c) by switching {a mathematical formula}T(xh) true and {a mathematical formula}A(xh) to false. The resulting CAS-interpretation {a mathematical formula}ICAS′(M,I′,χ) satisfies {a mathematical formula}K; this however implies that {a mathematical formula}〈V⊑T,xh〉 is not justified, and thus {a mathematical formula}ICAS(M,I,χ) is not a justified, which is a contradiction.It is then easy to check that the natural truth assignment σ to X represented by {a mathematical formula}χ(c), viz. {a mathematical formula}σ(xh)=true if {a mathematical formula}〈V⊑F,xh〉∈χ(c) and {a mathematical formula}σ(xh)=false otherwise, satisfies the formula E, as for each {a mathematical formula}ci at least one of {a mathematical formula}T(xi1), {a mathematical formula}T(xi2), {a mathematical formula}T(xi3) resp. of {a mathematical formula}F(xi1), {a mathematical formula}F(xi2), {a mathematical formula}F(xi3) must be false, and thus the clause {a mathematical formula}γi evaluates under σ to true. As {a mathematical formula}K is easily constructed from E, this proves the NP-hardness.  □
       </paragraph>
      </paragraph>
      <paragraph label="Proof of Theorem 5 (continued)">
       To show {a mathematical formula}Π2p hardness under the stated restriction, consider evaluating a QBF Φ of the form {a mathematical formula}∀X∃YE, where {a mathematical formula}E=⋀i=1kγi is a conjunction of clauses {a mathematical formula}γi=ℓi,1∨ℓi,2∨ℓi,3 over atoms {a mathematical formula}X={x1,…,xn} and {a mathematical formula}Y={y1,…,ym}.We construct {a mathematical formula}K as follows, where {a mathematical formula}V,F,T,X are concepts, {a mathematical formula}val,opp,l1,l2,l3 are roles, and {a mathematical formula}0,1,…,7,c1,…,cn, are individual constants.
       <list>
        the global knowledge {a mathematical formula}G contains defeasible axioms {a mathematical formula}D(X⊑T) and {a mathematical formula}D(X⊑F) and a module association {a mathematical formula}∃mod.{m}(c);a single module {a mathematical formula}Km that contains the inclusion axioms:The Boolean query that we construct is
       </list>
       <paragraph>
        {a mathematical formula} where for every literal ℓ over {a mathematical formula}X∪Y and {a mathematical formula}j∈{1,2,3},{a mathematical formula} Informally, the first part of the query must match each variable {a mathematical formula}xi to the value that has been chosen for it by the defeasible axioms; the second part must match all {a mathematical formula}yi variables then to either 0 or 1, such that each clause {a mathematical formula}γj is satisfied: the assignment to the variables of {a mathematical formula}ℓj,1, {a mathematical formula}ℓj,2 and {a mathematical formula}ℓj,3 must be such that {a mathematical formula}wj represents a satisfying assignment to {a mathematical formula}γj that is via “opp” renamed to a positive clause.It is then not difficult to verify that for the least CAS-model for {a mathematical formula}χσ w.r.t. identity ν, denoted {a mathematical formula}Iσ=Iˆ(χσ,ν), we have that {a mathematical formula}Iσ⊨Q, iff the formula {a mathematical formula}∃YEσ evaluates to true, i.e., after applying σ on E, the resulting CNF Eσ is satisfiable. Hence, {a mathematical formula}K⊨Q iff the QBF Φ evaluates to true. Furthermore, the module structure in {a mathematical formula}K is fixed and only the assertions in the modules {a mathematical formula}Km vary in order to encode Φ. This proves {a mathematical formula}Π2p-hardness under the stated restriction.Remark. To establish the result for constant-free queries, we can easily remove in Q above the constants {a mathematical formula}ci by introducing in {a mathematical formula}Km assertions {a mathematical formula}R(ci,ci+1), {a mathematical formula}1≤i&lt;n, where R is a fresh role, replacing each {a mathematical formula}ci in Q with a fresh variable {a mathematical formula}zi and adding {a mathematical formula}⋀i=1n−1c:R(zi,zi+1) (assuming {a mathematical formula}n≥2).We can alternatively establish {a mathematical formula}Π2p-hardness of CQ answering under the restriction that the set of assertions (the data) is fixed by a reduction from CERT3COL [62], which is a generalization of graph 3-colorability: given a graph {a mathematical formula}G=(V,E) where each edge {a mathematical formula}e∈E is labeled with a disjunction {a mathematical formula}δe=ℓe,1∨ℓe,2 of literals {a mathematical formula}ℓe,j over propositional variables {a mathematical formula}x1,…,xm, decide whether each graph {a mathematical formula}Gσ=(V,Eσ) where {a mathematical formula}Eσ contains all edges {a mathematical formula}e∈E such that {a mathematical formula}ϑ(δe) evaluates to true, is 3-colorable. Note that the graph 3-colorability problem results if {a mathematical formula}ℓe,1 and {a mathematical formula}ℓe,2 are always opposite literals, i.e., {a mathematical formula}δe is a tautology and then e is always selected.Our reduction is inspired by a well-known reduction from deciding graph 3-colorability to CQ answering over a relational database, cf. [63], where the database holds tuples that state admissible color combinations of adjacent nodes, and the query describes the graph; the query answers correspond then to the legal 3-colorings of the graph.We construct {a mathematical formula}K as follows, where {a mathematical formula}V,Fxi,Txi,Ce are concepts and {a mathematical formula}R,Ee are roles, for all {a mathematical formula}e∈E and {a mathematical formula}xi, and where {a mathematical formula}a,r,g,b are individual constants:
       </paragraph>
       <list>
        <list-item label="–">
         the global knowledge {a mathematical formula}G contains defeasible axioms {a mathematical formula}D(V⊑Txi) and {a mathematical formula}D(V⊑Fxi), {a mathematical formula}1≤i≤m and a module association {a mathematical formula}∃mod.{m}(c);
        </list-item>
        <list-item label="–">
         a single module {a mathematical formula}Km that contains the inclusion axioms:
        </list-item>
       </list>
       <paragraph>
        Intuitively, we must at context {a mathematical formula}c make for a an exception to either {a mathematical formula}V⊑Fxi or {a mathematical formula}V⊑Txi, for each i; the respective single minimal clashing set is {a mathematical formula}{V(a),¬Fxi(a)} resp. {a mathematical formula}{V(a),¬Txi(a)}. Keeping {a mathematical formula}V⊑Txi (resp. {a mathematical formula}V⊑Fxi) justifies {a mathematical formula}¬Fxi(a) (resp. {a mathematical formula}¬Txi(a)) via the axiom {a mathematical formula}Txi⊓Fxi⊑⊥. Every truth assignment σ to {a mathematical formula}x1,…,xm thus gives rise to a natural justified clashing assumption {a mathematical formula}χσ that for {a mathematical formula}c includes {a mathematical formula}〈V⊑Fxi,a〉 if {a mathematical formula}σ(xi)=true and {a mathematical formula}〈V⊑Txi,a〉 if {a mathematical formula}σ(xi)=false. Furthermore, if σ does not satisfy the disjunct {a mathematical formula}δe, then {a mathematical formula}∃R.({c}⊓Ce) for a is concluded; in further steps then, {a mathematical formula}Ee(x,y) is concluded for each pair {a mathematical formula}(c,c′)∈{r,g,b}2. If σ satisfies the disjunct {a mathematical formula}δe, then no such conclusion is made, and we have {a mathematical formula}Ee(c,c′) only if {a mathematical formula}c≠c′. On the other hand, no justified clashing assumption χ for {a mathematical formula}c can include both {a mathematical formula}〈V⊑Fxi,c〉 or {a mathematical formula}〈V⊑Txi,c〉 where c is a or its standard name, as without an inherited axiom {a mathematical formula}V⊑F resp. {a mathematical formula}V⊑T it is not possible to derive {a mathematical formula}¬Fxi(a) and {a mathematical formula}¬Txi(a).The Boolean query that we construct is{a mathematical formula} Informally, the graph G is encoded in Q, where the variables {a mathematical formula}yi, {a mathematical formula}yj amount to nodes i and j. If in the assignment σ, the edge e is selected (i.e., {a mathematical formula}δe is satisfied), then we must match {a mathematical formula}yu and {a mathematical formula}yv to different colors, as all {a mathematical formula}Ee(c,c), where {a mathematical formula}c∈{r,g,b} are not possible; if e is not selected, {a mathematical formula}yi and {a mathematical formula}yj can be matched to any colors. For the least CAS-model for {a mathematical formula}χσ w.r.t. identity ν, {a mathematical formula}Iσ=Iˆ(χσ,ν), we have that {a mathematical formula}Iσ⊨Q iff the graph {a mathematical formula}Gσ is 3-colorable.It is then is not difficult to verify that {a mathematical formula}K⊨Q holds iff for every assignment σ, we have {a mathematical formula}Iσ⊨Q, i.e., {a mathematical formula}Gσ is 3-colorable. Hence, {a mathematical formula}K⊨Q iff G is a yes-instance of CERT3COL. Furthermore, in {a mathematical formula}K the module structure and all assertions are fixed, and only the inclusion axioms vary; hence {a mathematical formula}Π2p-hardness under the stated restriction holds.For the data-complexity (i.e., fixed module structure, only the assertions in the modules {a mathematical formula}Km vary, and the query Q fixed), the coNP-hardness follows from the reduction of 3SAT to CKR-model existence in the proof of Theorem 3: the 3SAT instance E is unsatisfiable iff {a mathematical formula}K⊨c:V(c1) resp. {a mathematical formula}K⊨V(c1), say, as this is equivalent to {a mathematical formula}K not having a CKR-model.  □
       </paragraph>
      </paragraph>
     </section>
     <section label="A.5">
      <section-title>
       Proofs of section on datalog translation
      </section-title>
      <section label="A.5.1">
       <section-title>
        Normal form
       </section-title>
       <paragraph>
        Table A.17 shows minimal clashing sets for instances of defeasible axioms in normal form (under unique name assumption, some particular instances can be further be simplified).
       </paragraph>
       <paragraph label="Proof of Lemma 5">
        Intuitively, to prove item (a) we need to show that the rules for normal form transformation are complete with respect to the possible input axioms; to prove item (b) one has to show that the translations produce at most a linear increase in the size of the output CKR. Finally, to prove item (c), we have to show that any interpretation satisfying the original axiom can be extended to an interpretation satisfying the transformed axiom set, and, conversely, that any interpretation satisfying the transformed axioms set satisfies the original axiom: in verifying this, we have also to prove that the interpretations agree on the justification of the overridings.
       </paragraph>
       <list>
        <list-item label="(a).">
         Let {a mathematical formula}Σ=NCΣ⊎NRΣ⊎NIΣ. and {a mathematical formula}Γ=NCΓ⊎NRΓ⊎NIΓ. We extend such vocabulary to {a mathematical formula}Σ‾ and {a mathematical formula}Γ‾ in all of its components by adding a distinct set of new symbols: that is {a mathematical formula}Σ‾=NCΣ‾⊎NRΣ‾⊎NIΣ‾ with {a mathematical formula}NCΣ‾=NCΣ∪XΣ‾, {a mathematical formula}NRΣ‾=NRΣ∪WΣ‾, {a mathematical formula}NIΣ‾=NIΣ∪ZΣ‾. similarly, {a mathematical formula}Γ‾=NCΓ‾⊎NRΓ‾⊎NIΓ‾ with {a mathematical formula}NCΓ‾=NCΓ∪XΓ‾, {a mathematical formula}NRΓ‾=NRΓ∪WΓ‾, {a mathematical formula}NIΓ‾=NIΓ∪ZΓ‾. The extended vocabularies are only used to consider the new symbols added in the translation.We prove the assertion showing the following claim: the CKR{a mathematical formula}K′over extended vocabulary{a mathematical formula}〈Σ‾,Γ‾〉, that is obtained by exhaustively applying the rules inTable 2to axioms in{a mathematical formula}K, is in{a mathematical formula}SROIQ-RLand in normal form. We can prove the claim by cases on the possible form of input axioms.Let {a mathematical formula}α∈K be a {a mathematical formula}SROIQ-RL axiom. We assume {a mathematical formula}α∈LΣe: the case for {a mathematical formula}α∈LΓ can be shown similarly. We consider all of the possible cases in which α is not already in normal form and show how the rules can be applied to yield a normal form equivalent. In the following we use the same conventions on symbols used in Table 2 (e.g., {a mathematical formula}C,D represent complex concepts while {a mathematical formula}A,B are concept names).
        </list-item>
        <list-item label="(b).">
         The assertion can be proved by introducing a measure on input axioms from {a mathematical formula}K. Given a concept C over Σ or Γ, we define its size {a mathematical formula}‖C‖ as:
        </list-item>
        <list-item label="(c).">
         For every axiom α in {a mathematical formula}LΣe (as above, the case for {a mathematical formula}α∈LΓ can be proved similarly), let S be the set of axioms obtained from the application of the corresponding rule in Table 2 to α.Let {a mathematical formula}ICASNK be a justified named CAS-model for {a mathematical formula}K on {a mathematical formula}〈Σ,Γ〉 such that {a mathematical formula}ICASNK⊨c:α for {a mathematical formula}c∈N. We can extend this interpretation to the interpretation {a mathematical formula}I‾CASNK on {a mathematical formula}〈Σ‾,Γ‾〉 such that:
         <list>
          Let {a mathematical formula}A∈NCΣ‾. If {a mathematical formula}A∈NCΣ then {a mathematical formula}AI(c)‾=AI(c). Otherwise, if {a mathematical formula}A∈XΣ‾ then it has been introduced in the translation in an axiom set S: then {a mathematical formula}AI(c)‾ is the least set of {a mathematical formula}d∈ΔI(c)‾ such that {a mathematical formula}I(c)‾⊨S. Similarly for {a mathematical formula}A∈NCΓ‾ and the global interpretation {a mathematical formula}M‾.Let {a mathematical formula}R∈NRΣ‾. If {a mathematical formula}R∈NRΣ then {a mathematical formula}RI(c)‾=RI(c). Otherwise, if {a mathematical formula}R∈WΣ‾ then it has been introduced in the translation in an axiom set S: then {a mathematical formula}RI(c)‾ is the least set of {a mathematical formula}(d,d)∈ΔI(c)‾×ΔI(c)‾ such that {a mathematical formula}I(c)‾⊨S. Similarly for {a mathematical formula}R∈NRΓ‾ and the global interpretation {a mathematical formula}M‾.Let {a mathematical formula}a∈NIΣ‾. If {a mathematical formula}a∈NIΣ then {a mathematical formula}aI(c)‾=aI(c). Otherwise, if {a mathematical formula}a∈ZΣ‾ then it has been introduced in the translation in an axiom set S: then {a mathematical formula}aI(c)‾ is a new domain element {a mathematical formula}d∈ΔI(c)‾ such that {a mathematical formula}I(c)‾⊨S. Similarly for {a mathematical formula}a∈NIΓ‾ and the global interpretation {a mathematical formula}M‾.If {a mathematical formula}〈α,e〉∈χ(x): if α is in normal form, then {a mathematical formula}〈α,e〉∈χ′(x); otherwise, let {a mathematical formula}α′ be the (single) defeasible axiom in the set obtained by exhaustively applying the rules in Table 2 to α, then {a mathematical formula}〈α′,e〉∈χ′(x).For the first direction (i), we show that for all axioms
         </list>
         <paragraph>
          α in {a mathematical formula}LΣe, with {a mathematical formula}ICASNK⊨c:α, we have {a mathematical formula}I‾CASNK built as above is a model of {a mathematical formula}K′ and {a mathematical formula}I‾CASNK⊨c:α.For strict axiom cases, we can show the claim by induction on the form of α and transformation rules, for example:
         </paragraph>
         <list>
          <list-item label="–">
           If {a mathematical formula}α=C⊑D, then {a mathematical formula}S={C⊑X,X⊑D}. By hypothesis {a mathematical formula}I(c)⊨C⊑D, that is {a mathematical formula}CI(c)⊆DI(c): by construction we have that {a mathematical formula}CI(c)‾⊆XI(c)‾ and {a mathematical formula}XI(c)‾⊆DI(c)‾. This implies that {a mathematical formula}CI(c)‾⊆DI(c)‾ and thus {a mathematical formula}I(c)‾⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=C(a), then {a mathematical formula}S={X(a),X⊑C}. By hypothesis {a mathematical formula}I(c)⊨C(a) that is {a mathematical formula}aI(c)∈CI(c): by construction, {a mathematical formula}aI(c)‾∈XI(c)‾ and {a mathematical formula}XI(c)‾⊆CI(c)‾, which directly implies {a mathematical formula}aI(c)‾∈XI(c)‾ and thus {a mathematical formula}I(c)‾⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=A⊑C⊓D, then {a mathematical formula}S={A⊑C,A⊑D}. By hypothesis {a mathematical formula}I(c)⊨α, thus {a mathematical formula}AI(c)⊆CI(c)∩DI(c). This implies that {a mathematical formula}AI(c)⊆CI(c) and {a mathematical formula}AI(c)⊆DI(c): then, by definition of {a mathematical formula}I(c)‾, {a mathematical formula}AI(c)‾⊆CI(c)‾ and {a mathematical formula}AI(c)‾⊆DI(c)‾ which directly implies that {a mathematical formula}I(c)‾⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=eval(C1,C)⊑B, then {a mathematical formula}S={eval(X,Y)⊑B∈Km,C1⊑X∈Kmx,C⊑Y∈G,Y⊑∃mod.{mx}∈G}. By hypothesis {a mathematical formula}I(c)⊨eval(C1,C)⊑B: hence for every {a mathematical formula}xM∈CM, {a mathematical formula}aI(x)∈C1I(x) implies {a mathematical formula}aI(c)∈BI(c). Considering the translated set S and the definition of {a mathematical formula}I‾CASNK, we have that {a mathematical formula}xM‾∈YM‾ and, by the content of its newly associated module {a mathematical formula}mx, {a mathematical formula}C1I(x)‾⊆XI(x)‾. By the interpretation of the eval expression in S, we have that for every {a mathematical formula}aI(x)‾∈C1I(x)‾ then {a mathematical formula}aI(c)‾∈BI(c)‾, and thus {a mathematical formula}I(c)‾⊨α.
          </list-item>
         </list>
         <paragraph>
          In the case of defeasible axioms, we can moreover show that the translation preserves the justification of the axioms. For all defeasible axioms, if we consider the case of {a mathematical formula}M and the non-exceptional case for every {a mathematical formula}I(c) (i.e. for instances e s.t. {a mathematical formula}〈α,e〉∉χ(c)), the result can be shown as in the strict case. Otherwise, consider the case in which there exists some {a mathematical formula}〈α,e〉∈χ(c). Then, for example:
         </paragraph>
         <list>
          <list-item label="–">
           If {a mathematical formula}α=D(C⊑D), then {a mathematical formula}S={C⊑X,D(X⊑D)}. Then, by construction, if {a mathematical formula}〈α,e〉∈χ(c), we have {a mathematical formula}〈X⊑D,e〉∈χ′(c). Since {a mathematical formula}ICASNK is justified for {a mathematical formula}K, then there exists a clashing set {a mathematical formula}Q={¬D(e),C(e)} that is satisfied by {a mathematical formula}I(c). By definition, we also have that {a mathematical formula}I(c)‾⊨Q. Then, in {a mathematical formula}I‾CASNK we also have a justification for {a mathematical formula}〈X⊑D,e〉, since it holds that {a mathematical formula}Q′={¬D(e),X(e)} is a clashing set that is satisfied in {a mathematical formula}I(c)‾.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=D(D(a)), then {a mathematical formula}S={X(a),D(X⊑D)}. Then, if {a mathematical formula}〈α,a〉∈χ(c), we have {a mathematical formula}〈X⊑D,a〉∈χ′(c). Since {a mathematical formula}ICASNK is justified for {a mathematical formula}K, then there exists a clashing set {a mathematical formula}Q={¬D(a)} that is satisfied by {a mathematical formula}I(c). We also have that, by definition, {a mathematical formula}I(c)‾⊨Q. Then, {a mathematical formula}I‾CASNK contains a justification for {a mathematical formula}〈X⊑D,a〉, since {a mathematical formula}I(c)‾ satisfies the clashing set {a mathematical formula}Q′={¬D(a),X(a)}.
          </list-item>
         </list>
         <paragraph>
          Finally, the converse direction (ii) is proved by showing that: considering the definition of {a mathematical formula}I‾CASNK given above, for all axioms α in {a mathematical formula}LΣ, for every justified {a mathematical formula}I‾CASNK s.t. {a mathematical formula}I‾CASNK⊨K′ and {a mathematical formula}I‾CASNK⊨c:α, then {a mathematical formula}ICASNK (i.e. the original model on {a mathematical formula}〈Σ,Γ〉) is a justified model of {a mathematical formula}K and {a mathematical formula}ICASNK⊨c:α. We can then again show the claim proceeding by induction on the form of α and transformation rules, for example:
         </paragraph>
         <list>
          <list-item label="–">
           If {a mathematical formula}α=C⊑D, then {a mathematical formula}S={C⊑X,X⊑D}. By hypothesis {a mathematical formula}I(c)‾⊨α, thus {a mathematical formula}CI(c)‾⊆XI(c)‾⊆DI(c)‾. This implies that {a mathematical formula}CI(c)‾⊆DI(c)‾ and thus {a mathematical formula}CI(c)⊆DI(c) (since {a mathematical formula}C,D∈Σ), that is {a mathematical formula}I(c)⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=C(a), then {a mathematical formula}S={X(a),X⊑C}. By hypothesis {a mathematical formula}I(c)‾⊨α, thus {a mathematical formula}aI(c)‾∈XI(c)‾ and {a mathematical formula}XI(c)‾⊆CI(c)‾. This implies that {a mathematical formula}aI(c)‾∈CI(c)‾ and thus {a mathematical formula}aI(c)∈CI(c) (since {a mathematical formula}a,C∈Σ), that is {a mathematical formula}I(c)⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=C⊓A⊑B, then {a mathematical formula}S={C⊑X,X⊓A⊑B}. By hypothesis {a mathematical formula}I(c)‾⊨α, thus {a mathematical formula}CI(c)‾⊆XI(c)‾ and {a mathematical formula}XI(c)‾∩AI(c)‾⊆BI(c)‾. This implies that {a mathematical formula}CI(c)‾∩AI(c)‾⊆BI(c)‾. Hence {a mathematical formula}CI(c)∩AI(c)⊆BI(c) (since {a mathematical formula}C,A,B∈Σ), that is {a mathematical formula}I(c)⊨α.
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=eval(C1,C)⊑B then {a mathematical formula}S={eval(X,Y)⊑B∈Km,C1⊑X∈Kmx,C⊑Y∈G,Y⊑∃mod.{mx}∈G}. It holds that {a mathematical formula}I‾CASNK⊨c:α, then we have that {a mathematical formula}⋃e∈YM‾XI(e)‾⊆BI(c)‾. This implies that {a mathematical formula}⋃e∈CM‾C1I(e)‾⊆BI(c)‾, that is {a mathematical formula}ICASNK⊨c:α.
          </list-item>
         </list>
         <paragraph>
          In the case of defeasible axioms, we can again show that the justification of the original axiom is preserved. For all defeasible axioms, if we consider the case of {a mathematical formula}M‾ and the non-exceptional case for every {a mathematical formula}I(c)‾ (i.e. for instances e s.t. {a mathematical formula}〈α′,e〉∉χ′(c)), the result can be shown as in the strict cases. Thus, let us consider the case in which there exists some {a mathematical formula}〈α′,e〉∈χ′(c). Then, for example:
         </paragraph>
         <list>
          <list-item label="–">
           If {a mathematical formula}α=D(C⊑D), then {a mathematical formula}S={C⊑X,D(X⊑D)}. Then, if {a mathematical formula}〈X⊑D,e〉∈χ′(c), by construction we have {a mathematical formula}〈α,e〉∈χ(c). By hypothesis {a mathematical formula}I‾CASNK is justified for {a mathematical formula}K′: then there exists a clashing set {a mathematical formula}Q′={¬D(e),X(e)} that is satisfied by {a mathematical formula}I(c)‾. By definition of the translation, we also have that {a mathematical formula}I(c)‾⊨C(e). Then, in {a mathematical formula}ICASNK we also have a justification for {a mathematical formula}〈α,e〉, since the corresponding clashing set {a mathematical formula}Q={¬D(e),C(e)} is satisfied in {a mathematical formula}I(c).
          </list-item>
          <list-item label="–">
           If {a mathematical formula}α=D(D(a)), then {a mathematical formula}S={X(a),D(X⊑D)}. Supposing {a mathematical formula}〈X⊑D,a〉∈χ′(c), we have {a mathematical formula}〈α,a〉∈χ(c). Since {a mathematical formula}I‾CASNK is justified for {a mathematical formula}K′, then there exists a clashing set {a mathematical formula}Q′={¬D(a),X(a)} that is satisfied by {a mathematical formula}I(c)‾. This directly implies that {a mathematical formula}I(c)⊨¬D(a). Since {a mathematical formula}Q={¬D(a)} is a clashing set for {a mathematical formula}〈α,a〉, then we also have a justification in {a mathematical formula}ICASNK.  □
          </list-item>
         </list>
        </list-item>
       </list>
      </section>
      <section label="A.5.2">
       <section-title>
        Translation correctness
       </section-title>
       <paragraph>
        Given a CAS-interpretation {a mathematical formula}ICAS=〈M,I,χ〉, we construct a corresponding Herbrand interpretation {a mathematical formula}S=I(ICAS) of the program {a mathematical formula}PK(K) as the smallest set of literals so defined:
       </paragraph>
       <list>
        <list-item label="–">
         {a mathematical formula}l∈S, if {a mathematical formula}l∈PK(K);
        </list-item>
        <list-item label="–">
         {a mathematical formula}instd(a,A,c,main)∈S, if {a mathematical formula}I(c)⊨A(a);
        </list-item>
        <list-item label="–">
         {a mathematical formula}tripled(a,R,b,c,main)∈S, if {a mathematical formula}I(c)⊨R(a,b);
        </list-item>
        <list-item label="–">
         {a mathematical formula}ovr(p(e))∈S, if {a mathematical formula}ovr(p(e))∈OVR(ICAS);
        </list-item>
        <list-item label="–">
         {a mathematical formula}l∈S with {a mathematical formula}l=instd(a,A,c,t),tripled(a,R,b,c,t) and {a mathematical formula}t≠main, if {a mathematical formula}test(t)∈S and {a mathematical formula}l←b1,…,bn∈grnd(PK(K))OVR(ICAS) where {a mathematical formula}{b1,…,bn}⊆S.
        </list-item>
        <list-item label="–">
         {a mathematical formula}test(t)∈S, if {a mathematical formula}ovr(p(e))∈OVR(ICAS) and {a mathematical formula}r∈grnd(PK(K)), with {a mathematical formula}ovr(p(e))∈Head(r) and {a mathematical formula}test_fails(t)∈Body(r);
        </list-item>
        <list-item label="–">
         {a mathematical formula}unsat(nlit(a,A,c))∈S, if {a mathematical formula}I(c)⊭Kc∪{A(a)};
        </list-item>
        <list-item label="–">
         {a mathematical formula}unsat(nrel(a,R,b,c))∈S, if {a mathematical formula}I(c)⊭Kc∪{R(a,b)};
        </list-item>
        <list-item label="–">
         {a mathematical formula}test_fails(t)∈S, if {a mathematical formula}unsat(t)∉S.
        </list-item>
       </list>
       <paragraph label="Proof of Proposition 13">
        Note that {a mathematical formula}unsat(main)∉S. We will prove that {a mathematical formula}I(MG) is an answer set for {a mathematical formula}PG(G) if {a mathematical formula}G is satisfiable. Note that, by restricting the definition of {a mathematical formula}I(ICAS) to the global context, {a mathematical formula}I(MG) is as follows:
        <list>
         Facts of {a mathematical formula}PG(G) are included in {a mathematical formula}I(MG);{a mathematical formula}instd(a,A,g,main)∈I(MG) iff {a mathematical formula}MG⊨A(a) for {a mathematical formula}A∈NC and {a mathematical formula}a∈NI;{a mathematical formula}tripled(a,R,b,g,main)∈I(MG) iff {a mathematical formula}MG⊨R(a,b) for {a mathematical formula}R∈NR and {a mathematical formula}a,b∈NI;{a mathematical formula}unsat(main)∉I(MG);To show that
        </list>
        <paragraph>
         {a mathematical formula}M is a model for {a mathematical formula}G, we must verify that {a mathematical formula}M satisfies (a) the condition (i) of a CKR interpretation and (b) the conditions (i) and (ii) of a CAS-model. As for (a), we easily prove that {a mathematical formula}NM⊆CtxM: by rule (igl-subctx2), for every {a mathematical formula}c∈N we have {a mathematical formula}M⊨instd(c,Ctx,gm,main), which implies {a mathematical formula}cM∈CtxM. The condition {a mathematical formula}CM⊆CtxM for every {a mathematical formula}C∈C can be shown similarly by the rule (igl-subctx1). As for (b), we consider the form of all axioms β in {a mathematical formula}LΓ resp. {a mathematical formula}LΣ that can occur in {a mathematical formula}G. We show here only some of the cases (the others are similar):
        </paragraph>
        <list>
         <list-item label="–">
          Let {a mathematical formula}β=A(a)∈G, then, by rule (prl-instd), {a mathematical formula}M⊨instd(a,A,g,main). This directly implies that {a mathematical formula}aM∈AM.
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=¬A(a)∈G, then {a mathematical formula}M⊨ninsta(a,A,g,main). Assuming that {a mathematical formula}M⊨A(a), we would have that {a mathematical formula}M⊨instd(a,A,g,main). But, by the rule (prl-ninstd), we would have that {a mathematical formula}unsat(main)∈M and M would violate the constraint (prl-sat). Thus {a mathematical formula}M⊭A(a).
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=A⊑B∈G, then {a mathematical formula}M⊨subClass(A,B,g). If {a mathematical formula}d∈AM, then by definition {a mathematical formula}M⊨instd(d,A,g,main): by rule (prl-subc) we obtain that {a mathematical formula}M⊨instd(d,B,g,main) and thus {a mathematical formula}d∈BM.
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=A1⊓A2⊑B∈G. Then {a mathematical formula}M⊨subConj(A1,A2,B,g). Supposing {a mathematical formula}d∈A1M∩A2M, then by definition {a mathematical formula}M⊨instd(d,A1,g,main) and {a mathematical formula}instd(d,A2,g,main): by rule (prl-subcnj) we obtain that {a mathematical formula}M⊨instd(d,B,g,main) and thus {a mathematical formula}d∈BM.
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=∃R.A⊑B∈G, then {a mathematical formula}M⊨subEx(R,A,B,g). Let {a mathematical formula}d∈(∃R.A)M: by definition of the semantics this means that some {a mathematical formula}d′∈AM exists such that {a mathematical formula}〈d,d′〉∈RM. Thus, {a mathematical formula}M⊨instd(d′,A,g,main) and {a mathematical formula}M⊨tripled(d,R,d′,g,main). By rule (prl-subex), we obtain that {a mathematical formula}M⊨instd(d,B,g,main): thus {a mathematical formula}d∈BM as required.
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=A⊑∀R.B∈G. Then {a mathematical formula}M⊨supForall(R,A,B,g). Let {a mathematical formula}d∈AM and there is {a mathematical formula}(d,d′)∈RM: then {a mathematical formula}M⊨instd(d,A,g,main) and {a mathematical formula}M⊨tripled(d,R,d′,g,main). By rule (prl-forall), we have that {a mathematical formula}M⊨instd(d′,B,g,main) which implies {a mathematical formula}M⊨B(d′).
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=R∘S⊑T∈G. Then {a mathematical formula}M⊨subRChain(R,S,T,g). Supposing {a mathematical formula}(a,c)∈RM and {a mathematical formula}(c,b)∈RM, we have {a mathematical formula}M⊨tripled(a,R,c,g,main) and {a mathematical formula}M⊨tripled(c,S,b,g,main). By rule (prl-subrc), we have that {a mathematical formula}M⊨tripled(a,T,b,g,main) which implies {a mathematical formula}M⊨T(a,b).
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=Dis(R,S)∈G, then {a mathematical formula}M⊨dis(R,S,g). Suppose that {a mathematical formula}〈d,d′〉∈RM and {a mathematical formula}〈d,d′〉∈SM: then we have {a mathematical formula}M⊨tripled(d,R,d′,g,main) and {a mathematical formula}M⊨tripled(d,S,d′,g,main). By rule (prl-dis) we would obtain {a mathematical formula}unsat(main); but then M would violate (prl-sat), a contradiction.
         </list-item>
        </list>
        <paragraph>
         By definition of the translation, for every {a mathematical formula}D(β)∈G with {a mathematical formula}β∈LΣ, it also holds that {a mathematical formula}M⊨β: for example, let {a mathematical formula}β=A(b); then the fact {a mathematical formula}insta(b,A,gk,main). is added to {a mathematical formula}PG(G), which implies that {a mathematical formula}M⊨instd(b,A,gk,main) and, by construction of the model, {a mathematical formula}M⊨A(b).  □
        </paragraph>
       </paragraph>
       <paragraph label="Proof of Lemma 6">
        Let us consider {a mathematical formula}S=I(Iˆ(χ)) defined above and the reduct {a mathematical formula}GS(PK(K)) of {a mathematical formula}PK(K) with respect S. That is, {a mathematical formula}GS(PK(K)) is the set of rules obtained from all ground instances of rules in {a mathematical formula}PK(K) by removing: (i) every rule r such that {a mathematical formula}S⊨l for some NAF literal {a mathematical formula}notl∈Body(r); and (ii) the NAF part from the bodies of the remaining rules. Note that the NAF literals in {a mathematical formula}PK(K) involve instances of {a mathematical formula}ovr,test_fails and unsat.We can then proceed to prove items (i) and (ii) of the lemma, showing that the answer sets of {a mathematical formula}PK(K) coincide with the sets {a mathematical formula}S=I(Iˆ(χ)) where χ is a justified clashing assumption of {a mathematical formula}K.(i). Assuming that χ is a justified clashing assumption, we show that {a mathematical formula}S=I(Iˆ(χ)) is an answer set of {a mathematical formula}PK(K).We first show that {a mathematical formula}S⊨GS(PK(K)), that is for every rule instance {a mathematical formula}r∈GS(PK(K)) it holds that {a mathematical formula}S⊨r. We can prove this by examining the possible rule forms that occur in {a mathematical formula}GS(PK(K)). The cases for the rules in {a mathematical formula}Prl are analogous to the proof of Proposition 13. Here we show some of the representative cases (other cases can be shown by similar reasoning). Assuming that {a mathematical formula}S⊨Body(r) and r stems from a rule {a mathematical formula}r′ in {a mathematical formula}grnd(PK(K)) of the following form, we show that {a mathematical formula}Head(r)∈S and thus r is satisfied:
        <list>
         (prl-instd): then {a mathematical formula}insta(a,A,c,t)∈I(Iˆ(χ)) and, by definition of the translation, {a mathematical formula}A(a)∈Kc (as t can only be {a mathematical formula}main). This implies that {a mathematical formula}I(c)⊨A(a) and thus {a mathematical formula}instd(a,A,c,main) is added to {a mathematical formula}I(Iˆ(χ)).(prl-subc): then {a mathematical formula}{subClass(A,B,c),instd(a,A,c,t)}⊆I(Iˆ(χ)). By definition of the translation we have {a mathematical formula}A⊑B∈Kc. For the construction of {a mathematical formula}I(Iˆ(χ)), if {a mathematical formula}t=main then {a mathematical formula}I(c)⊨A(a). This implies that {a mathematical formula}I(c)⊨B(a) and {a mathematical formula}instd(a,B,c,t) is added to {a mathematical formula}I(Iˆ(χ)). Otherwise, if {a mathematical formula}t≠main then {a mathematical formula}instd(a,B,c,t) is directly added to {a mathematical formula}I(Iˆ(χ)) by its construction.(plc-evalat): then {a mathematical formula}{subEval(A,C,B,c),instd(c1,C,g,t),instd(a,A,c1,t)}⊆I(Iˆ(χ)). Thus we have that {a mathematical formula}eval(A,C)⊑B∈G and {a mathematical formula}G⊨C(c1). For the construction of {a mathematical formula}I(Iˆ(χ)), if {a mathematical formula}t=main then {a mathematical formula}I(c1)⊨A(a); This implies that {a mathematical formula}I(c)⊨B(a) and {a mathematical formula}instd(a,B,c,t) is added to {a mathematical formula}I(Iˆ(χ)). Otherwise, if {a mathematical formula}t≠main then {a mathematical formula}instd(a,B,c,t) is directly added to {a mathematical formula}I(Iˆ(χ)) by its construction.(prop-inst): then {a mathematical formula}insta(a,A,g)∈I(Iˆ(χ)). Since {a mathematical formula}r∈GS(PK(K)), we have that {a mathematical formula}ovr(insta,a,A,c)∉OVR(Iˆ(χ)), thus {a mathematical formula}〈A(a)〉∉χ(c). By definition of the translation, {a mathematical formula}A(a)∈G and thus {a mathematical formula}I(c)⊨A(a); hence {a mathematical formula}instd(a,A,c,main) is added to {a mathematical formula}I(Iˆ(χ)).(prop-subc): then {a mathematical formula}{subClass(A,B,g),instd(a,A,c,t)}⊆I(Iˆ(χ)). As {a mathematical formula}r∈GS(PK(K)), we have {a mathematical formula}ovr(subClass,a,A,B,c)∉OVR(Iˆ(χ)) and hence {a mathematical formula}〈A⊑B,a〉∉χ(c). By definition, {a mathematical formula}A⊑B∈G and, if {a mathematical formula}t=main, {a mathematical formula}I(c)⊨A(a). Thus, for the definition of CAS-model and the semantics, {a mathematical formula}instd(a,B,c,t) is added to {a mathematical formula}I(Iˆ(χ)). If {a mathematical formula}t≠main, then {a mathematical formula}instd(a,B,c,t) is added to {a mathematical formula}I(Iˆ(χ)) by construction.(ovr-subc): then {a mathematical formula}{def_subclass(A,B),prec(c,g),instd(a,A,c,main)}⊆I(Iˆ(χ)). As {a mathematical formula}r∈GS(PK(K)), we have {a mathematical formula}test_fails(nlit(a,B,c))∉I(Iˆ(χ)). By construction of {a mathematical formula}I(Iˆ(χ)) this implies that {a mathematical formula}unsat(nlit(a,B,c))∈I(Iˆ(χ)), meaning that {a mathematical formula}I(c)⊨¬B(a). Thus, {a mathematical formula}I(c) satisfies the clashing set {a mathematical formula}{A(a),¬B(a)} for the clashing assumption {a mathematical formula}〈A⊑B,a〉. Consequently, {a mathematical formula}〈A⊑B,a〉∈χ and by construction {a mathematical formula}ovr(subClass,a,A,B,c) is added to {a mathematical formula}I(Iˆ(χ)).(test-subc): then {a mathematical formula}{def_subclass(A,B),prec(c,g),instd(a,A,c,main)}⊆I(Iˆ(χ)). Thus {a mathematical formula}D(A⊑B)∈G and {a mathematical formula}I(c)⊨A(a) (an instance of such defeasible axiom). By the construction of {a mathematical formula}I(Iˆ(χ)) we have that {a mathematical formula}test(nlit(a,B,c))∈I(Iˆ(χ)).(test-fails1): then {a mathematical formula}instd(a,A,c,nlit(a,A,c))∈I(Iˆ(χ)). As {a mathematical formula}r∈GS(PK(K)), we have that {a mathematical formula}unsat(nlit(a,A,c))∉I(Iˆ(χ)). By construction of S, {a mathematical formula}test_fails(nlit(a,A,c))∈I(Iˆ(χ)).(test-add1): then {a mathematical formula}test(nlit(a,A,c))∈I(Iˆ(χ)). By definition of S, this directly implies that {a mathematical formula}instd(a,A,c,nlit(a,A,c))∈I(Iˆ(χ)).(test-copy1): then {a mathematical formula}{test(nlit(a,A,c)),instd(b,B,c,main)}⊆I(Iˆ(χ)). By definition of S, this directly implies that {a mathematical formula}instd(b,B,c,nlit(a,A,c))∈I(Iˆ(χ)).Minimality of
        </list>
        <paragraph>
         {a mathematical formula}S=I(Iˆ(χ)) w.r.t. the (positive) deduction rules of {a mathematical formula}GS(PK(K)) can be motivated as in case of the global least model {a mathematical formula}I(MG) for {a mathematical formula}PG(G). Indeed, no model {a mathematical formula}S′⊆S of {a mathematical formula}GS(PK(K)) such that {a mathematical formula}S′≠S can exist: as {a mathematical formula}Iˆ(χ) is the least model of {a mathematical formula}K w.r.t. χ, {a mathematical formula}S′ can not be a proper subset of S on any of the facts from the input translations, nor on insta, triplea, instd, tripled for the environment (i.e., last argument) {a mathematical formula}main. Consequently, {a mathematical formula}S′ will also contain all atoms on ovr from S, as for every corresponding clashing assumption {a mathematical formula}〈α,e〉∈χ(c), the body of the (reduct of) some overriding rule in {a mathematical formula}PK(K) that encodes a clashing set for {a mathematical formula}〈α,e〉 will be satisfied. Furthermore, {a mathematical formula}S′ will also contain all literals over test from S: consequently {a mathematical formula}S′ has to contain all literals instd, tripled for environments different from {a mathematical formula}main and all literals on unsat and {a mathematical formula}test_fails from S. That is, {a mathematical formula}S′=S must hold.(ii). Let S be an answer set of {a mathematical formula}PK(K). We show that there is some justified clashing assumption χ for {a mathematical formula}K such that {a mathematical formula}S=I(Iˆ(χ)) holds.First of all, we note that as S is an answer set for the CKR program, all literals on ovr and {a mathematical formula}test_fails in S are derivable from the reduct {a mathematical formula}GS(PK(K)).By the definition of {a mathematical formula}I(Iˆ(χ)) we can easily build a model {a mathematical formula}IS=〈MS,IS,CASS〉 from the answer set S as follows: the global interpretation {a mathematical formula}MS is analogous to the structure {a mathematical formula}M that was defined for the answer set M of {a mathematical formula}PG(G) in Proposition 13. We note that, by well-known modularity properties of answer set semantics (splitting sets [64]), the restriction of S to the vocabulary of the global part {a mathematical formula}G, denoted {a mathematical formula}S|G, is an answer set of {a mathematical formula}PG(G): thus by Proposition 13, it follows that {a mathematical formula}MS=MG and that {a mathematical formula}MS is the least Herbrand model of {a mathematical formula}G. Thus, if {a mathematical formula}c∈NG (that is, if {a mathematical formula}grnd(PG(G))⊨instd(c,Ctx,gm,main)) then {a mathematical formula}cM∈CtxM; if {a mathematical formula}Km∈Kc (that is, if {a mathematical formula}grnd(PG(G))⊨tripled(c,mod,m,gm,main)) then {a mathematical formula}〈cM,mM〉∈modM. For every {a mathematical formula}c∈NG (and thus, for every {a mathematical formula}cM∈CtxM), we build the local interpretation {a mathematical formula}IS(c)=〈Δc,⋅I(c)〉 as follows:
        </paragraph>
        <list>
         <list-item label="–">
          {a mathematical formula}Δc={d|d∈NIΣ};
         </list-item>
         <list-item label="–">
          {a mathematical formula}aI(c)=a, for every {a mathematical formula}a∈NIΣ;
         </list-item>
         <list-item label="–">
          {a mathematical formula}AI(c)={d∈Δc|S⊨instd(d,A,c,main)}, for every {a mathematical formula}A∈NCΣ;
         </list-item>
         <list-item label="–">
          {a mathematical formula}RI(c)={(d,d′)∈Δc×Δc|S⊨tripled(d,R,d′,c,main)} for {a mathematical formula}R∈NRΣ;
         </list-item>
        </list>
        <paragraph>
         Finally, {a mathematical formula}χS(c)={〈α,e〉|Irl(α,c)=p,ovr(p(e))∈S}. To prove the claim, we have to show that {a mathematical formula}IS meets the definition of a least justified CAS-model for {a mathematical formula}K, that is:
        </paragraph>
        <list>
         <list-item label="(i).">
          {a mathematical formula}cM∈CtxM, for every {a mathematical formula}c∈N, and {a mathematical formula}CM⊆CtxM, for every {a mathematical formula}C∈C;
         </list-item>
         <list-item label="(ii).">
          for every {a mathematical formula}x∈CtxM, {a mathematical formula}ΔI(x)=ΔM and {a mathematical formula}aI(x)=aM, for {a mathematical formula}a∈NIΣ;
         </list-item>
         <list-item label="(iii).">
          for every {a mathematical formula}α∈LΣ∪LΓ in {a mathematical formula}G, {a mathematical formula}M⊨α;
         </list-item>
         <list-item label="(iv).">
          for every {a mathematical formula}D(α)∈G (where {a mathematical formula}α∈LΣ), {a mathematical formula}M⊨α;
         </list-item>
         <list-item label="(v).">
          for every {a mathematical formula}〈x,y〉∈modM s.t. {a mathematical formula}y=mM, then {a mathematical formula}I(x)⊨Km;
         </list-item>
         <list-item label="(vi).">
          for every {a mathematical formula}α∈G∩LΣ and {a mathematical formula}x∈CtxM, {a mathematical formula}I(x)⊨α, and
         </list-item>
         <list-item label="(vii).">
          for every {a mathematical formula}D(α)∈G (with {a mathematical formula}α∈LΣ), {a mathematical formula}x∈CtxM, and {a mathematical formula}|x|-tuple d of elements in {a mathematical formula}NIΣ such that {a mathematical formula}d∉{e|〈α,e〉∈χ(x)}, {a mathematical formula}I(x)⊨α(d).
         </list-item>
        </list>
        <paragraph>
         Conditions (i), (iii) and (iv) directly follow from Proposition 13. Condition (ii) holds since, given {a mathematical formula}x∈CtxM, for every {a mathematical formula}a∈NIΣ it holds that {a mathematical formula}aI(x)=aM=a. Condition (v) is verified by showing that for every {a mathematical formula}Km s.t. {a mathematical formula}〈c,mM〉∈modM (that is, every {a mathematical formula}Km∈Kc) we have {a mathematical formula}I(c)⊨Km. We proceed by cases and consider the form of all of the axioms {a mathematical formula}β∈LΣe that can occur in {a mathematical formula}Kc. The case for axioms in the general normal form of Table 1 can be proved analogously as in the cases of Proposition 13: thus we have to prove the case of local reference axioms.
        </paragraph>
        <list>
         <list-item label="–">
          Let {a mathematical formula}β=eval(A,C)⊑B∈Kc, then {a mathematical formula}S⊨subEval(A,C,B,c). If {a mathematical formula}c′∈CM and {a mathematical formula}d∈AI(c′), then by definition {a mathematical formula}S⊨instd(d,A,c′,main) and {a mathematical formula}S⊨instd(c′,C,gm,main). By rule (plc-evalat) we obtain that {a mathematical formula}S⊨instd(d,B,c,main): hence, by definition {a mathematical formula}d∈BI(c).
         </list-item>
         <list-item label="–">
          The case for {a mathematical formula}β=eval(R,C)⊑T can be shown analogously.
         </list-item>
        </list>
        <paragraph>
         To prove, condition (vii), let us assume that {a mathematical formula}D(β)∈G with {a mathematical formula}β∈LΣ. We proceed by cases on the possible forms of β. In the following we only show some of the relevant cases.
        </paragraph>
        <list>
         <list-item label="–">
          Let {a mathematical formula}β=A(a). Then, by definition of the translation, we have that {a mathematical formula}S⊨insta(a,A,g,main). Suppose that {a mathematical formula}〈A(x),a〉∉χN(c), and hence {a mathematical formula}〈A(x),a〉∉χS(cM). Then by definition, {a mathematical formula}ovr(insta,a,A,c)∉OVR(Iˆ(χ)). By the definition of the reduction, the corresponding instantiation of rule (prop-inst) has not been removed from {a mathematical formula}GS(PK(K)): this implies that {a mathematical formula}S⊨instd(a,A,c,main). By definition, this means that {a mathematical formula}aI(c)∈AI(c).
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=A⊑B. Then, by definition of the translation, we have that {a mathematical formula}S⊨subClass(A,B,g). Let us suppose that {a mathematical formula}bI(c)∈AI(c): then {a mathematical formula}S⊨instd(b,A,c,main). Suppose that {a mathematical formula}〈A⊑B,b〉∉χS(c): by definition, {a mathematical formula}ovr(subClass,b,A,B,c)∉OVR(Iˆ(χ)). By the definition of the reduction, the corresponding instantiation of rule (prop-subc) has not been removed from {a mathematical formula}GS(PK(K)): this implies that {a mathematical formula}S⊨instd(b,B,c,main). Thus, by definition, this means that {a mathematical formula}bI(c)∈BI(c).
         </list-item>
         <list-item label="–">
          Let {a mathematical formula}β=∃R.A⊑B. Then {a mathematical formula}S⊨subEx(R,A,B,g). Suppose that {a mathematical formula}d∈(∃R.A)I(c): by definition of the semantics this means that some {a mathematical formula}d′∈AI(c) exists such that {a mathematical formula}〈d,d′〉∈RI(c). Thus, {a mathematical formula}S⊨instd(d′,A,c,main) and {a mathematical formula}S⊨tripled(d,R,d′,c,main). Suppose that {a mathematical formula}〈∃R.A⊑B,d〉∉χS(c): by definition, {a mathematical formula}ovr(subEx,d,R,A,B,c)∉OVR(Iˆ(χ)). By the definition of the reduction, the corresponding instantiation of rule (prop-subex) has not been removed from {a mathematical formula}GS(PK(K)). Thus it holds that {a mathematical formula}S⊨instd(d,B,c,main), and hence {a mathematical formula}dI(c)∈BI(c).
         </list-item>
        </list>
        <paragraph>
         Condition (vi) can be verified similarly as (vii): non-defeasible global axioms {a mathematical formula}β∈G∩LΣ can not appear in clashing assumptions in {a mathematical formula}χS, thus they can not give rise to the corresponding overriding assumptions in {a mathematical formula}OVR(χS); this implies that the corresponding instantiations of propagation rules in {a mathematical formula}PD are never removed from {a mathematical formula}GS(PK(K)) and thus the cases can be proved like in the proof for the previous condition.Thus, {a mathematical formula}IS is a CAS-model of {a mathematical formula}K. We next argue that in fact {a mathematical formula}IS=Iˆ(χS), i.e., {a mathematical formula}IS is the least CAS-model of {a mathematical formula}K for the clashing assumption {a mathematical formula}χS as in Corollary 1. We already noted that w.r.t. the global context, {a mathematical formula}MS coincides with {a mathematical formula}Mˆ from Proposition 13. Assuming that {a mathematical formula}I⊂IS is a CAS-model of {a mathematical formula}K with clashing assumption {a mathematical formula}χS, we can construct an interpretation {a mathematical formula}S′⊂S such that {a mathematical formula}S′⊨GS(PK(K)), by removing (at least) one fact {a mathematical formula}insta(d,A,c,main) or {a mathematical formula}triple(d,R,d′,c,main) from S; however, this would contradict that S is an answer set of {a mathematical formula}PK(K). Hence, {a mathematical formula}IS=Iˆ(χS) holds.Finally, it remains to show that {a mathematical formula}χS is justified. As {a mathematical formula}〈α,e〉∈χS(c) is due to {a mathematical formula}ovr(p(e))∈S and {a mathematical formula}ovr(p(e)) is derived from the reduct {a mathematical formula}GS(PK(K)), it follows that S must satisfy the body {a mathematical formula}Body(r) of some overriding rule r for {a mathematical formula}p(e). Consequently, {a mathematical formula}IS(c) must satisfy the clashing set {a mathematical formula}Sc,〈α,e〉 for {a mathematical formula}〈α,e〉 that is encoded in {a mathematical formula}Body(r); note that satisfaction of {a mathematical formula}nottest_fails(nlit(x,y,c)) means that {a mathematical formula}test_fails(nlit(x,y,c)) is not satisfied, which due to the rule (test-fails1) means that {a mathematical formula}unsat(nlit(x,y,c)) is derived. From the latter, however, we conclude that for the negative literal ¬β that is encoded by {a mathematical formula}nlit(x,y,c), item (ii) of Theorem 2 holds. As item (i) of this theorem holds for every positive literal {a mathematical formula}β∈Sc,〈α,e〉, it follows that the clashing assumption {a mathematical formula}〈α,e〉 at c is justified. In conclusion, {a mathematical formula}χS is justified. This proves the result.  □
        </paragraph>
       </paragraph>
      </section>
     </section>
     <section label="A.6">
      <section-title>
       Justification safeness
      </section-title>
      <paragraph>
       Table A.18 shows a set of negative deduction rules (corresponding to the positive rules in {a mathematical formula}Prl) that can be added to the translation under the assumption of justification safeness (see Section 5.4).
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>