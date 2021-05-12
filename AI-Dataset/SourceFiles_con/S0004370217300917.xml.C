<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Three-valued semantics for hybrid MKNF knowledge bases revisited.
   </title>
   <abstract>
    Knorr et al. (2011) [9] formulated a three-valued formalism for the logic of Minimal Knowledge and Negation as Failure (MKNF), and proposed a well-founded semantics for hybrid MKNF knowledge bases. The main results state that if a hybrid MKNF knowledge base has a three-valued MKNF model, its well-founded MKNF model exists, which is unique and can be computed by an alternating fixpoint construction. However, we show that these claims are erroneous. The goal of this paper is two-fold. First, we provide insight into why these claims fail to hold. This leads to a classification of hybrid MKNF knowledge bases into a hierarchy of four classes, of which the smallest one is what works for the well-founded semantics proposed by Knorr et al. After that, we characterize three-valued MKNF models into what we call stable partitions, which are similar to partial stable models in logic programming. The intuitive notion of stable partitions allows us to discover a new proof-theoretic method to determine whether a three-valued MKNF model exists for a given hybrid MKNF knowledge base. We can guess partial partitions and verify their stability by computing alternating fixpoints and by performing a consistency check. This algorithm can be applied to compute all three-valued MKNF models, as well as all two-valued ones originally formulated by Motik and Rosati for query answering. As a result, our work provides a uniform characterization of well-founded, two-valued, and all three-valued MKNF models, in terms of stable partitions and the alternating fixpoint construction.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Motivated by the Semantic Web and other applications that require features from both rules and ontological reasoning, researchers have studied ways to combine rules with description logics (DLs), and in general with decidable first-order theories or external reasoning sources (e.g., [5], [8], [11], [12], [16], [18], [19]). It has been argued that such a combination draws strengths from both and the weaknesses of one are balanced by the strengths of the other. Since reasoning with DLs is based on classic, monotonic logic, there is no support of nonmonotonic features such as defeasible inheritance and default reasoning. On the other hand, rules under the stable model semantics [7], commonly referred to as Answer Set Programming (ASP), are formulated mainly to reason with ground knowledge, without supporting quantifiers or function symbols. Since a combination of the two can offer features of both, there has been a continuous interest in formalisms that support both rules and DLs in an integrated manner.
     </paragraph>
     <paragraph>
      Of various approaches, the formalism of hybrid MKNF knowledge bases studied in the seminal paper [12] is considered a powerful, dominating knowledge representation language developed for integrating nonmonotonic rules with DLs. A hybrid MKNF knowledge base {a mathematical formula}K consists of two components, {a mathematical formula}K=(O,P), where {a mathematical formula}O is a DL knowledge base, which corresponds to a decidable first-order theory, and {a mathematical formula}P is a collection of MKNF rules based on the stable model semantics. One critical issue centers around combining open and closed world reasoning for targeted applications. This issue is addressed in [12] by seamlessly integrating rules with DLs. The authors explain why such an integration is a challenging task and show in great detail how hybrid MKNF knowledge bases capture many of the existing combinations of DLs and rules. MKNF structures in this case are two-valued, which means that they interpret MKNF formulas as true or false.
     </paragraph>
     <paragraph>
      In logic programming, it is known that every nondisjunctive logic program (also called a normal logic program) P possesses a unique well-founded model [6], which can be computed in quadratic time in the size of P, and which approximates all answer sets of P. The latter feature makes it possible to apply the process of computing the well-founded model over a partial assignment as constraint propagation in answer set computation [17].
     </paragraph>
     <paragraph>
      There are strong motivations to develop a well-founded semantics for hybrid MKNF knowledge bases, for applications that require both open and closed world reasoning, and for efficient processing of large knowledge bases and scalability. However, the task is challenging. To tackle this challenge, Knorr et al. [9] formulate a three-valued logic of MKNF, where three truth values, true, false, and undefined, can be properly identified by using two sets of interpretations with one enclosed in the other. They define the notion of the well-founded MKNF model as the least defined (or alternatively, maximally undefined) three-valued MKNF model, and show that, if a hybrid MKNF knowledge base {a mathematical formula}K is MKNF-consistent, meaning that {a mathematical formula}K has at least one three-valued MKNF model, then the well-founded MKNF model for {a mathematical formula}K uniquely exists and can be computed by a pair of alternating fixpoints. A condition for testing whether {a mathematical formula}K is MKNF-consistent is also provided. Unfortunately, these results are incorrect.
     </paragraph>
     <paragraph>
      In this paper, we show the following:
     </paragraph>
     <list>
      <list-item label="•">
       An MKNF-consistent hybrid MKNF knowledge base may have a well-founded MKNF model (as defined in [9]), which cannot be computed by the alternating fixpoint construction.
      </list-item>
      <list-item label="•">
       An MKNF-consistent hybrid MKNF knowledge base may have three-valued MKNF models but none of them is the least defined, since they are not comparable by undefinedness.
      </list-item>
     </list>
     <paragraph>
      These insights lead to a classification of hybrid MKNF knowledge bases into a hierarchy of four classes, with the smallest one being precisely what is intended by the well-founded semantics for these knowledge bases. The class of MKNF-consistent ones turns out to be a strict superclass.
     </paragraph>
     <paragraph>
      The powerful yet much involved notion of three-valued MKNF models motivates the question whether there is a simpler, more intuitive notion to express these models. In [12], two-valued MKNF models are related to total partitions of modal K-atoms and in [9], three-valued MKNF models are related to partial partitions. Building on these ideas and motivated by the familiar notion of partial stable models in logic programming (e.g., [15], [20]), we introduce the notion of stable partition, based on the properties that are both desirable and necessary, and show a one-to-one correspondence between stable partitions and three-valued MKNF models. More importantly, we discover that the alternating fixpoint construction has another, somewhat unexpected, proof-theoretic application: Given an arbitrary hybrid MKNF knowledge base {a mathematical formula}K=(O,P), we can guess a partial partition {a mathematical formula}(T,P) and check whether {a mathematical formula}(T,P) is stable by computing a pair of alternating fixpoints and by performing a consistency test. This is unexpected because the correspondence between arbitrary three-valued MKNF models and the alternating fixpoint construction holds even when the well-founded MKNF model for {a mathematical formula}K does not exist (in contrast, a normal logic program always possesses a well-founded model). This algorithm can be applied to compute three-valued MKNF models, as well as two-valued ones. In fact, Motik and Rosati's algorithm [12] for computing two-valued MKNF models, under the assumption that the underlying DL component is tractable, is a special case based on a propagator that computes one of the two alternating fixpoints. Our work here shows a uniform characterization of well-founded, two-valued, and all three-valued MKNF models by stable partitions, which can be computed or guess-and-verified by the alternating fixpoint construction.
     </paragraph>
     <paragraph>
      The next section introduces MKNF and its three-valued extension, followed by Section 3 which introduces the well-founded semantics for hybrid MKNF knowledge bases. Section 4 gives the details about what went wrong with the main claims in [9] and provides a classification to show what can work under the formalism of [9]. Section 5 presents a characterization of three-valued MKNF models in terms of stable partitions, based on which we show a proof-theoretic characterization for all three-valued MKNF models. Finally, Section 6 provides concluding remarks with an argument that our results point to the potential that alternating fixpoint construction can lead to a formulation of DPLL-based (Davis–Putnam–Logeman–Loveland) search algorithm [3], [14] for hybrid MKNF knowledge bases, which gives rise to an interesting direction for future research.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      The logic of MKNF and its three-valued formalization
     </section-title>
     <paragraph>
      The logic of minimal knowledge and negation as failure (MKNF) [10] is proposed by Lifschitz as a unifying framework for various nonmonotonic formalisms, such as default logic, autoepistemic logic, and logic programming. MKNF formulas are built from first-order formulas and two modal operators, K and not, for closed world reasoning. Intuitively, {a mathematical formula}Kψ asks whether ψ is known w.r.t. a collection of “possible worlds” (formally, interpretations) – the larger the set of interpretations is, the fewer facts are known – while notψ checks whether ψ is not known, based on negation as failure.
     </paragraph>
     <paragraph>
      In this section, we recall the basic theory of MKNF and its three-valued extension [9].
     </paragraph>
     <paragraph>
      First, we summarize the syntax and semantics of MKNF briefly. Let {a mathematical formula}Σ=(Σc,Σf,Σp) be a first-order signature, where {a mathematical formula}Σc, {a mathematical formula}Σf, and {a mathematical formula}Σp are sets of constants, function symbols, and predicate symbols containing the equality predicate ≈, respectively. MKNF formulas over Σ are defined as follows:
     </paragraph>
     <list>
      <list-item label="•">
       A first-order atom {a mathematical formula}P(t1,…,tn) is an MKNF formula, where P is a predicate and {a mathematical formula}ti are first-order terms; a first-order term is either a constant, a variable, or recursively constructed from constants, variables, and function symbols. If no variables occur in such an atom, it is called ground and serves as a proposition. We will write lower case letters, a, b, ..., to denote propositions.
      </list-item>
      <list-item label="•">
       If φ is an MKNF formula, then ¬φ, {a mathematical formula}∃x:φ, {a mathematical formula}Kφ, and notφ are MKNF formulas, so is {a mathematical formula}φ1∧φ2 for MKNF formulas {a mathematical formula}φ1 and {a mathematical formula}φ2. We may write {a mathematical formula}φ1∨φ2, {a mathematical formula}φ1⊃φ2, {a mathematical formula}φ1≡φ2, {a mathematical formula}∀x:φ, {a mathematical formula}t,f, {a mathematical formula}t1≈t2, and {a mathematical formula}t1≉t2 as abbreviations, respectively, for {a mathematical formula}¬(¬φ1∧¬φ2), {a mathematical formula}¬φ1∨φ2, {a mathematical formula}(φ1⊃φ2)∧(φ2⊃φ1), {a mathematical formula}¬(∃x:¬φ), {a mathematical formula}a∨¬a, {a mathematical formula}a∧¬a, {a mathematical formula}≈(t1,t2), and {a mathematical formula}¬(t1≈t2).
      </list-item>
      <list-item label="•">
       {a mathematical formula}φ[t1/x1,...,tn/xn] denotes the formula obtained by substituting the corresponding terms {a mathematical formula}ti for free variables {a mathematical formula}xi in φ (those that are not in the scope of any quantifier).
      </list-item>
     </list>
     <paragraph>
      Given a first-order formula φ, {a mathematical formula}Kφ is called a K-atom and notφ called a not-atom. Both of these are also called modal atoms. An MKNF formula φ without any free variable is closed, and is ground if φ contains no variables.
     </paragraph>
     <paragraph>
      Let Σ be a signature and Δ a nonempty set called a universe. A first-order interpretation I over Σ and Δ assigns an object {a mathematical formula}aI∈Δ to each constant {a mathematical formula}a∈Σc, a function {a mathematical formula}fI:Δn→Δ to each n-ary function symbol {a mathematical formula}f∈Σf, a relation {a mathematical formula}PI⊆Δn to each n-ary predicate {a mathematical formula}P∈Σp. Moreover, for {a mathematical formula}α,β∈Δ, {a mathematical formula}(α,β)∈≈I iff {a mathematical formula}α=β. Unlike in standard first-order logic, for each element {a mathematical formula}α∈Δ, the signature Σ is required to contain a special constant {a mathematical formula}nα, called a name, such that {a mathematical formula}nαI=α.{sup:1} The interpretation of a variable-free term {a mathematical formula}t=f(s1,…,sn) is defined recursively as {a mathematical formula}tI=fI(s1I,…,snI).
     </paragraph>
     <paragraph>
      An MKNF structure is a triple {a mathematical formula}(I,M,N), where I is a first-order interpretation over Δ and Σ, and M and N are nonempty sets of first-order interpretations over Δ and Σ. Given an MKNF structure {a mathematical formula}(I,M,N), two-valued satisfiability of an MKNF formula is defined in Table 1.
     </paragraph>
     <paragraph>
      An MKNF interpretation M over a universe Δ is a nonempty set of first-order interpretations over Δ, and given an MKNF formula φ, M satisfies φ, denoted {a mathematical formula}M⊨φ, if {a mathematical formula}(I,M,M)⊨φ for each {a mathematical formula}I∈M.
     </paragraph>
     <paragraph>
      A notion called standard name assumption is imposed on top of MKNF to avoid unintended behaviors [12]. This requires an interpretation to be a Herbrand interpretation with a countably infinite number of additional constants, and the predicate ≈ to be a congruence relation.{sup:2} Intuitively, given the assumption that each individual in the universe of an interpretation is denoted by a constant and the countability it implies, the standard name assumption becomes a convenient normalized representation of interpretations, since each interpretation is isomorphic to the quotient (w.r.t. ≈) of a Herbrand interpretation, and each quotient of a Herbrand interpretation is an interpretation. In the sequel, we assume the standard name assumption, and due to this assumption, in definitions we need not explicitly mention the universe associated with the underlying interpretations.
     </paragraph>
     <paragraph label="Definition 1">
      Two-valued MKNF modelAn MKNF interpretation M is a two-valued MKNF model of an MKNF formula φ if
     </paragraph>
     <list>
      <list-item label="(1)">
       {a mathematical formula}M⊨φ, and
      </list-item>
      <list-item label="(2)">
       {a mathematical formula}∀M′ s.t. {a mathematical formula}M′⊃M, {a mathematical formula}(I′,M′,M)⊭φ for some {a mathematical formula}I′∈M′.
      </list-item>
     </list>
     <paragraph>
      Condition (1) ensures that M evaluates φ to true, and condition (2) enforces a minimization of derived modal K-atoms in a two-valued MKNF model, which results in “minimal knowledge” under a fixed interpretation of the not-atoms. For example, let {a mathematical formula}φ=nota⊃Kb (which is evaluated by Table 1 in terms of the formula {a mathematical formula}¬(nota∧¬Kb). The MKNF interpretation {a mathematical formula}M={{b},{a,b}} is a two-valued MKNF model of φ. First, M satisfies φ. Furthermore, any {a mathematical formula}M′⊃M would contain either {a mathematical formula}{a} or ∅, or both. For example, with {a mathematical formula}M′={{a},{b},{a,b}}, we have {a mathematical formula}(I′,M′,M)⊭φ, independent of {a mathematical formula}I′, since {a mathematical formula}(I′,M′,M)⊨nota and {a mathematical formula}(I′,M′,M)⊭Kb. On the other hand, {a mathematical formula}M={{a},{a,b}} is not a two-valued MKNF model of φ, since for the same {a mathematical formula}M′ as above, {a mathematical formula}(I′,M′,M)⊨φ, for any {a mathematical formula}I′∈M′.
     </paragraph>
     <paragraph>
      The notion of the MKNF structure above is inherently two-valued because a modal atom {a mathematical formula}Kφ is true in M iff φ is true in every interpretation of M – it thus leaves no room for a third truth value. In [9], the notion of the MKNF structure is extended to that of the three-valued MKNF structure{a mathematical formula}(I,M,N) (also called partial MKNF structure), which consists of a first-order interpretation, I, and two pairs, {a mathematical formula}M=〈M,M1〉 and {a mathematical formula}N=〈N,N1〉, of sets of first-order interpretations, where {a mathematical formula}M1⊆M and {a mathematical formula}N1⊆N. From {a mathematical formula}〈M,M1〉, we can identify three truth values for modal K-atoms in the following way: {a mathematical formula}Kφ is true w.r.t. {a mathematical formula}〈M,M1〉 if φ is true in all interpretations in M; it is false if it is false in at least one interpretation in {a mathematical formula}M1; and it is undefined otherwise, i.e., this is the case where it is true in all interpretations in {a mathematical formula}M1 but there is at least one interpretation in {a mathematical formula}M∖M1 in which it is false. For not-atoms, a symmetric treatment w.r.t. {a mathematical formula}〈N,N1〉 is adopted. Let {a mathematical formula}{t,u,f} be the set of truth values true, undefined, and false with the order {a mathematical formula}f&lt;u&lt;t, and let the operator max (resp. min) choose the greatest (resp. the least) element with respect to this ordering. Table 2 shows a three-valued evaluation of MKNF formulas.
     </paragraph>
     <paragraph>
      Note that first-order atoms are evaluated as in the two-valued case, which captures the goal that for formulas without modal operators, the semantics is essentially that of first-order logic. Notice also that under three-valued MKNF, logic implication {a mathematical formula}φ1⊃φ2 may not be logically equivalent to {a mathematical formula}¬φ1∨φ2 unless both {a mathematical formula}φ1 and {a mathematical formula}φ2 are first-order formulas.
     </paragraph>
     <paragraph>
      A (three-valued) MKNF interpretation pair{a mathematical formula}(M,N) consists of two MKNF interpretations, M and N, with {a mathematical formula}∅⊂N⊆M. An MKNF interpretation pair satisfies an MKNF formula φ, denoted {a mathematical formula}(M,N)⊨φ, iff {a mathematical formula}(I,〈M,N〉,〈M,N〉)(φ)=t for each {a mathematical formula}I∈M. If {a mathematical formula}M=N, then the MKNF interpretation pair is called total. If there exists an MKNF interpretation pair satisfying a formula φ, then φ is said to be consistent; otherwise φ is inconsistent. If φ is a first-order formula, following the standard terminology, we also say that φ is satisfiable when φ is consistent.
     </paragraph>
     <paragraph label="Definition 2">
      Three-valued MKNF modelAn MKNF interpretation pair {a mathematical formula}(M,N) is a three-valued MKNF model of an MKNF formula φ if
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}(M,N)⊨φ, and
      </list-item>
      <list-item label="(b)">
       for all MKNF interpretation pairs {a mathematical formula}(M′,N′) with {a mathematical formula}M⊆M′ and {a mathematical formula}N⊆N′, where at least one of the inclusions is proper and {a mathematical formula}M′=N′ if {a mathematical formula}M=N, {a mathematical formula}∃I′∈M′ s.t. {a mathematical formula}(I′,〈M′,N′〉,〈M,N〉)(φ)≠t.
      </list-item>
     </list>
     <paragraph>
      Condition (a) checks satisfiability while condition (b), with the evaluation of not-atoms fixed, constrains the evaluation of modal K-atoms to be minimal w.r.t the ordering {a mathematical formula}f&lt;u&lt;t while maximizing falsity. That is, by enlarging M to {a mathematical formula}M′ we limit the derivation of modal K-atoms, and by enlarging N to {a mathematical formula}N′ we expand on falsity to reduce undefined. Thus, a three-valued MKNF model is one for which neither of these is possible under the assumption that not-atoms remain to be evaluated w.r.t. {a mathematical formula}(M,N), while still satisfying the given formula.
     </paragraph>
     <paragraph>
      For example, consider {a mathematical formula}φ=(notb∧nota)⊃Ka, and the MKNF interpretation pair {a mathematical formula}(M,M) where {a mathematical formula}M={{a},{a,b}}. Though {a mathematical formula}(M,M)⊨φ, it violates condition (b) of Definition 2, since {a mathematical formula}(I,〈M′,M′〉,〈M,M〉), where {a mathematical formula}M′={∅,{a},{b},{a,b}}, evaluates {a mathematical formula}[notb,nota,Ka] to {a mathematical formula}[t,f,f], respectively, independent of I. It follows that φ evaluates to t, according to Table 2. In fact, {a mathematical formula}(M′,M) is a three-valued MKNF model of φ, which evaluates {a mathematical formula}[notb,nota,Ka] to {a mathematical formula}[t,u,u], respectively.
     </paragraph>
     <paragraph>
      Let φ be an MKNF formula. As shown by Knorr et al. (Proposition 1 of [9]), an MKNF interpretation M is a two-valued MKNF model of φ if and only if the MKNF interpretation pair {a mathematical formula}(M,M) is a three-valued MKNF model of φ. The latter is also called a total three-valued MKNF model.
     </paragraph>
     <paragraph label="Definition 3">
      Definition 10 of [9]If there is a three-valued MKNF model for a given MKNF formula φ, then φ is called MKNF-consistent. Otherwise, φ is MKNF-inconsistent. If {a mathematical formula}(I,〈M,N〉,〈M,N〉)(ψ)=t for all three-valued MKNF models {a mathematical formula}(M,N) of φ, then φ entails ψ, written {a mathematical formula}φ⊨MKNF3ψ.{sup:3}
     </paragraph>
     <paragraph>
      MKNF interpretation pairs can be compared by an order of knowledge.
     </paragraph>
     <paragraph label="Definition 4">
      Definition 11 of [9]Let {a mathematical formula}(M1,N1) and {a mathematical formula}(M2,N2) be MKNF interpretation pairs. {a mathematical formula}(M1,N1)⪰k(M2,N2) iff {a mathematical formula}M1⊆M2 and {a mathematical formula}N1⊇N2.
     </paragraph>
     <paragraph>
      Intuitively, a larger {a mathematical formula}M2 or a smaller {a mathematical formula}N2 would leave more room for modal K-atoms and not-atoms to be undefined. Hence the pair {a mathematical formula}(M2,N2) is “less defined” than {a mathematical formula}(M1,N1).
     </paragraph>
     <paragraph>
      We are ready to define the notion of a well-founded MKNF model.
     </paragraph>
     <paragraph label="Definition 5">
      Definition 12 of [9]Let φ be an MKNF formula and {a mathematical formula}(M,N) a partial MKNF model of φ such that {a mathematical formula}(M1,N1)⪰k(M,N) for all three-valued MKNF models {a mathematical formula}(M1,N1) of φ. Then {a mathematical formula}(M,N) is a well-founded MKNF model of φ.
     </paragraph>
     <paragraph>
      For example, let {a mathematical formula}φ=(nota⊃Kb)∧(notb⊃Ka)∧(nota⊃Ka). The reader can check that φ has two three-valued MKNF models, the least of which is {a mathematical formula}(M,N)=({∅,{a},{b},{a,b}},{{a,b}}), in which all of the modal atoms in φ evaluate to u. The other one, {a mathematical formula}(M1,M1), is total, where {a mathematical formula}M1={{a},{a,b}} in which {a mathematical formula}[Ka,Kb,nota,notb] evaluate to {a mathematical formula}[t,f,f,t], respectively.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Well-founded semantics for hybrid MKNF knowledge bases
     </section-title>
     <paragraph>
      A hybrid MKNF knowledge base {a mathematical formula}K=(O,P) consists of a decidable description logic (DL) knowledge base {a mathematical formula}O, translatable into first-order logic and a rule base {a mathematical formula}P, which is a finite set of rules with modal atoms. The original work on hybrid MKNF knowledge bases [11], [12] defines a two-valued semantics for such knowledge bases with disjunctive rules. In this paper, following [9], our focus is on nondisjunctive rules as presented in [11].{sup:4}
     </paragraph>
     <paragraph>
      An MKNF rule r (or simply a rule) is of the form{a mathematical formula} where H, {a mathematical formula}Ai, and {a mathematical formula}Bj are function-free first-order atoms. {a mathematical formula}KH, {a mathematical formula}{KAi|i=1..m}, and {a mathematical formula}{notBi|i=1..n} are called the head, the positive body, and the negative body, respectively. We use {a mathematical formula}Hd(r) to denote the head of the rule, {a mathematical formula}Bd(r) to denote the body of the rule, and let {a mathematical formula}Bd(r)=Bd+(r)∪Bd−(r), where {a mathematical formula}Bd+(r) and {a mathematical formula}Bd−(r) denote its positive and negative body respectively. Here, we identify a set of modal atoms with the conjunction of modal atoms in it. A rule is positive if it contains no not-atoms. When all rules in {a mathematical formula}P are positive, the corresponding hybrid MKNF knowledge base is called positive.
     </paragraph>
     <paragraph>
      For the interpretation of a hybrid MKNF knowledge base {a mathematical formula}K=(O,P) in the logic of MKNF, a transformation {a mathematical formula}π(K)=Kπ(O)∧π(P) is performed to transform {a mathematical formula}O into a first-order formula and rules {a mathematical formula}r∈P into a conjunction of first-order implications to make each of them coincide syntactically with an MKNF formula. More precisely,{a mathematical formula} where {a mathematical formula}x→ is the vector of free variables in r. In the rest of this paper we may abuse the notation by identifying {a mathematical formula}K with {a mathematical formula}π(K) and {a mathematical formula}P with {a mathematical formula}π(P).
     </paragraph>
     <paragraph>
      As an illustration of the translation {a mathematical formula}π(O), suppose that the DL knowledge base {a mathematical formula}O contains a concept inclusion axiom: {a mathematical formula}seasideCity⊑∃has.beach, where {a mathematical formula}seasideCity and {a mathematical formula}beach are concepts and has is a role. Intuitively, the axiom asserts that seaside cities have a beach. This axiom is translated into a first-order formula as follows: {a mathematical formula}∀x[SeasideCity(x)⊃∃y(Has(x,y)∧Beach(y))], where {a mathematical formula}SeasideCity, {a mathematical formula}Beach, and Has are the corresponding predicates. The reader is referred to [1] for more details on the standard translation. For simplicity, in all examples of this paper we will just write {a mathematical formula}O by a propositional or a first-order formula.
     </paragraph>
     <paragraph>
      Under the additional assumption of DL-safety a first-order rule base is semantically equivalent to a finite ground rule base, in terms of two-valued MKNF models [12] as well as in terms of three-valued MKNF models [9]; hence decidability is guaranteed. Recall that a rule r is DL-safe if every variable in r occurs in at least one K-atom in the body of r whose predicate symbol does not appear in {a mathematical formula}O,{sup:5} and a hybrid MKNF knowledge base {a mathematical formula}K=(O,P) is DL-safe if all rules in {a mathematical formula}P are DL-safe. In this paper, we assume that a given rule base is always DL-safe, and for convenience, when we write {a mathematical formula}P we assume it is already grounded if not said otherwise explicitly.
     </paragraph>
     <paragraph>
      The results of this paper do not depend on any particular syntax of DL. In fact, though we often refer to {a mathematical formula}O of {a mathematical formula}K=(O,P) as a DL knowledge base, {a mathematical formula}O can be considered an external theory, which possibly shares vocabulary with {a mathematical formula}P. In any case, we only need to assume that {a mathematical formula}π(O) is a first-order theory that offers a decidable entailment relation between formulas and ground literals.
     </paragraph>
     <paragraph>
      In [9], the notion of a partition is defined, which is then related to MKNF interpretation pairs.
     </paragraph>
     <paragraph label="Definition 6">
      Let {a mathematical formula}K=(O,P) be a hybrid MKNF knowledge base. {a mathematical formula}KA(K) is the smallest set that contains all ground K-atoms occurring in {a mathematical formula}P and modal atom {a mathematical formula}Kϕ if notϕ occurs in {a mathematical formula}P. A (partial) partition of {a mathematical formula}KA(K) is a pair {a mathematical formula}(T,P) of two sets, where {a mathematical formula}T⊆P⊆KA(K). A partition of the form {a mathematical formula}(T,T) is said to be exact.
     </paragraph>
     <paragraph>
      Intuitively, T contains true modal K-atoms and P contains possibly true modal K-atoms. Thus, the complement of P is the set of false modal K-atoms and {a mathematical formula}P\T the set of undefined modal K-atoms. The condition that {a mathematical formula}T⊆P ensures that these three sets are pairwise non-overlapping, hence {a mathematical formula}(T,P) is consistent.{sup:6}
     </paragraph>
     <paragraph>
      For convenience, we overload the operator {a mathematical formula}KA: given a set of modal atoms S we define {a mathematical formula}KA(S)={Kϕ|Kϕ∈S ornotϕ∈S}.
     </paragraph>
     <paragraph>
      Let S be a subset of {a mathematical formula}KA(K). The objective knowledge of S relevant to {a mathematical formula}K is the set of first-order formulas {a mathematical formula}OBO,S={π(O)}∪{ξ|Kξ∈S}. In [9], the notion that a three-valued MKNF model induces a partition is defined.
     </paragraph>
     <paragraph label="Definition 7">
      Let {a mathematical formula}S⊆KA(K). The partial partition {a mathematical formula}(T,P) of S is induced by an MKNF interpretation pair {a mathematical formula}(M,N) as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Kξ∈T implies {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=t,
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Kξ∉P implies {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=f, and
      </list-item>
      <list-item label="3.">
       {a mathematical formula}Kξ∈P\T implies {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=u.
      </list-item>
     </list>
     <paragraph>
      A clarification is in order: the word implies above should read as if and only if. As our later technical development depends on this property, let us make it precise.
     </paragraph>
     <paragraph label="Lemma 1">
      Let{a mathematical formula}S⊆KA(K). The partial partition{a mathematical formula}(T,P)of S induced by an MKNF interpretation pair{a mathematical formula}(M,N), as defined inDefinition 7, satisfies
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}Kξ∈Tiff{a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=t,
      </list-item>
      <list-item label="2.">
       {a mathematical formula}Kξ∉Piff{a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=f, and
      </list-item>
      <list-item label="3.">
       {a mathematical formula}Kξ∈P\Tiff{a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=u.
      </list-item>
     </list>
     <paragraph label="Proof">
      Let {a mathematical formula}(T,P) be induced by {a mathematical formula}(M,N). We show that if {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=t, then {a mathematical formula}Kξ∈T, for any {a mathematical formula}Kξ∈KA(K). Otherwise, assume {a mathematical formula}Kξ∉T. Then there are two cases to consider: (i) {a mathematical formula}Kξ∈P\T, and (ii) {a mathematical formula}Kξ∈KA(K)\P. For case (i), by Definition 7, {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=u, which is a contradiction. For case (ii), also by Definition 7, {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=f, a contradiction again. Therefore, if {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(Kξ)=t, then {a mathematical formula}Kξ∈T. The proofs for the other two cases are similar.  □
     </paragraph>
     <paragraph label="Example 1">
      Consider a hybrid MKNF knowledge base {a mathematical formula}K=(O,P), where {a mathematical formula}O=a∧(b⊃c)∧¬f∧h and {a mathematical formula}P consists of{a mathematical formula}{a mathematical formula}KA(K) is the set of all K-atoms {a mathematical formula}Kξ where ξ appears in {a mathematical formula}P (note that only h does not appear in {a mathematical formula}P). The combined reasoning with {a mathematical formula}O and {a mathematical formula}P can be seen as follows: Since {a mathematical formula}KO implies {a mathematical formula}Ka and notg is true by negation as failure, using the first rule we derive {a mathematical formula}Kb; then due to {a mathematical formula}b⊃c in {a mathematical formula}O we derive {a mathematical formula}Kc. Thus its occurrence in the body of the second rule can be ignored. For the K-atoms {a mathematical formula}Kd and {a mathematical formula}Ke appearing in the two rules in the middle, without preferring one over the other, both can be undefined. Because both notb and {a mathematical formula}Kf are false (the latter is due to ¬f in {a mathematical formula}O), the last rule is also satisfied. We will show the precise derivations shortly. Now consider an MKNF interpretation pair {a mathematical formula}(M,N)=({I|I⊨O∧b},{I|I⊨O∧b∧d∧e}). The partial partition induced by {a mathematical formula}(M,N) is {a mathematical formula}(T,P)=({Ka,Kb,Kc},{Ka,Kb,Kc,Kd,Ke}). For instance, we have that, for all {a mathematical formula}I∈M, {a mathematical formula}(I,〈M,N〉,〈M,N〉)(Ka)=t, {a mathematical formula}(I,〈M,N〉,〈M,N〉)(Kg)=f, and {a mathematical formula}(I,〈M,N〉,〈M,N〉)(Kd)=u. It can be verified that {a mathematical formula}(M,N) is a three-valued MKNF model of {a mathematical formula}K.  □
     </paragraph>
     <paragraph>
      Based on the relationship between partial partitions and MKNF interpretation pairs given in Definition 7, it is shown in [9] that the objective knowledge derived from the partial partition induced by a three-valued MKNF model is identical to that model.
     </paragraph>
     <paragraph label="Proposition 1">
      Proposition 3 of [9]Let{a mathematical formula}(M,N)be a three-valued MKNF model of a hybrid MKNF knowledge base{a mathematical formula}K=(O,P), and{a mathematical formula}(T,P)the partition of{a mathematical formula}KA(K)induced by{a mathematical formula}(M,N). Then{a mathematical formula}(M,N)=({I|I⊨OBO,T},{I|I⊨OBO,P}).
     </paragraph>
     <paragraph>
      Naturally, if {a mathematical formula}T=P, then {a mathematical formula}M=N and {a mathematical formula}(M,M) is a total three-valued MKNF model.
     </paragraph>
     <paragraph>
      To obtain the well-founded MKNF model of an MKNF-consistent hybrid MKNF knowledge base {a mathematical formula}K, the well-founded partition of {a mathematical formula}KA(K) is computed by the so-called alternating fixpoint construction, which applies two antitonic operators alternately to compute a least fixpoint and a greatest fixpoint, which correspond, respectively, to the true and non-false knowledge. First, an immediate consequence operator is defined for positive hybrid MKNF knowledge bases.
     </paragraph>
     <paragraph label="Definition 8">
      Let {a mathematical formula}K=(O,P) be a positive hybrid MKNF knowledge base. We define the operator {a mathematical formula}TK on subsets S of {a mathematical formula}KA(K) as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      This operator is the standard immediate consequence operator augmented by the consequences of the DL knowledge base {a mathematical formula}O and the knowledge from S. As the rule base {a mathematical formula}P of {a mathematical formula}K is positive, {a mathematical formula}TK is monotonic and thus possesses a least fixpoint, which can be computed by the sequence {a mathematical formula}〈TKi〉i=0∞, where {a mathematical formula}TK0=∅, and {a mathematical formula}TKi+1=TK(TKi), for all {a mathematical formula}i≥0. Let us denote the least fixpoint of the operator {a mathematical formula}TK by {a mathematical formula}lfp(TK).
     </paragraph>
     <paragraph>
      Next, two antitonic operators {a mathematical formula}ΓK and {a mathematical formula}ΓK′ are defined to compute the least fixpoint of {a mathematical formula}TK′, where {a mathematical formula}K′ is a positive hybrid MKNF knowledge base obtained by two different transformations from {a mathematical formula}K. Given a hybrid MKNF knowledge base {a mathematical formula}K and {a mathematical formula}S⊆KA(K), similar to Gelfond–Lifschitz transform [7], we define the MKNF transform of{a mathematical formula}Krelative to S, denoted {a mathematical formula}K/S, by {a mathematical formula}K/S=(O,P/S), where {a mathematical formula}P/S is obtained from {a mathematical formula}P by (i) deleting each rule r in {a mathematical formula}P such that {a mathematical formula}KA(Bd−(r))∩S≠∅, and (ii) deleting {a mathematical formula}Bd−(r) from each remaining rule r.
     </paragraph>
     <paragraph>
      Since hybrid MKNF knowledge bases allow predicates to appear both in the DL knowledge base and in the rules, the above transform may result in inconsistency from the combination of classical negation in {a mathematical formula}O and nonmonotonic negation in {a mathematical formula}P. To avoid this, we define the MKNF-coherent transform, denoted {a mathematical formula}K//S, by {a mathematical formula}K//S=(O,P//S), where {a mathematical formula}P//S is the same as {a mathematical formula}P/S, except that condition (i) of the transform {a mathematical formula}K/S is changed to the following: deleting each rule r such that {a mathematical formula}KA(Bd−(r))∩S≠∅ or {a mathematical formula}OBO,S⊨¬H, where {a mathematical formula}Hd(r)=KH.
     </paragraph>
     <paragraph>
      Since in both cases of {a mathematical formula}K/S and {a mathematical formula}K//S the resulting rule base is positive, a least fixpoint in each case exists. Let us define {a mathematical formula}ΓK(S)=lfp(TK/S) and {a mathematical formula}ΓK′(S)=lfp(TK//S). Then, we can construct two sequences {a mathematical formula}Pi and {a mathematical formula}Ni, as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      The increasing sequence {a mathematical formula}Pi is intended to compute modal K-atoms that are true, while the decreasing sequence {a mathematical formula}Ni computes modal K-atoms that are possibly true, and at the end we reach a fixpoint pair {a mathematical formula}(Pω,Nω), where {a mathematical formula}Pω=ΓK(Nω) and {a mathematical formula}Nω=ΓK′(Pω) (cf. Proposition 6 of [9]). We will call {a mathematical formula}(Pω,Nω) the alternating fixpoint pair of {a mathematical formula}K.
     </paragraph>
     <paragraph label="Definition 9">
      Let {a mathematical formula}K=(O,P) be a hybrid MKNF knowledge base. If the alternating fixpoint pair {a mathematical formula}(Pω,Nω) is a partition of {a mathematical formula}KA(K), it is then called the well-founded partition of {a mathematical formula}K.{sup:7}
     </paragraph>
     <paragraph>
      In Proposition 7 of [9], the authors show that for any {a mathematical formula}Kξ∈KA(K), {a mathematical formula}Kξ∈Pω implies that {a mathematical formula}Kξ is true in all three-valued MKNF models of {a mathematical formula}K, and {a mathematical formula}Kξ∈KA(K)\Nω implies that {a mathematical formula}Kξ is false in all three-valued MKNF models of {a mathematical formula}K. It follows that if {a mathematical formula}K is MKNF-consistent, its alternating fixpoint pair is guaranteed to satisfy {a mathematical formula}Pω⊆Nω, i.e., it is a partition.
     </paragraph>
     <paragraph>
      Clearly, the number of iterations in the construction of the alternating fixpoint pair is linear in the number of K-atoms in {a mathematical formula}KA(K). If the entailment relation {a mathematical formula}OBO,S⊨ξ can be computed in polynomial time for literal ξ, then each iteration takes polynomial time, and so does the computation of the alternating fixpoint pair.
     </paragraph>
     <paragraph label="Example 2">
      Continuing with Example 1, one can verify that the alternating fixpoint pair {a mathematical formula}(Pω,Nω) of {a mathematical formula}K is computed by the following sequences:{a mathematical formula} For instance, {a mathematical formula}N2=ΓK′(P1)=lfp(TK//P1)=N1, where {a mathematical formula}P//P1 consists of{a mathematical formula} We therefore conclude that {a mathematical formula}(Pω,Nω)=({Ka,Kb,Kc},{Ka,Kb,Kc,Kd,Ke}), which is the well-founded partition of {a mathematical formula}K. Note that the iterated computation continues until we reach the state where {a mathematical formula}Pω=ΓK(Nω) and {a mathematical formula}Nω=ΓK′(Pω).  □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Well-founded MKNF semantics re-classified
     </section-title>
     <paragraph>
      In this section, we reveal insights in the well-founded MKNF model by showing that (i) an MKNF-consistent hybrid MKNF knowledge base may not have a well-founded MKNF model, and (ii) the well-founded MKNF model of an MKNF-consistent hybrid MKNF knowledge base may not correspond to its well-founded partition. These observations lead to a reclassification of hybrid MKNF knowledge bases. To place these observations in context, let us first cite the relevant theorems of [9] that are under discussion here. Note that we already assume that MKNF rules are nondisjunctive and ground.
     </paragraph>
     <list>
      <list-item label="•">
       Claim (1) (Theorem 1 in [9]) If {a mathematical formula}K is an MKNF-consistent hybrid MKNF knowledge base, then a well-founded MKNF model exists, and it is unique.
      </list-item>
      <list-item label="•">
       Claim (2) (Theorem 2 in [9]) Let {a mathematical formula}K=(O,P) be a hybrid MKNF knowledge base, {a mathematical formula}Pω the fixpoint of {a mathematical formula}Pi, and {a mathematical formula}Nω the fixpoint of {a mathematical formula}Ni. {a mathematical formula}K is MKNF-inconsistent iff {a mathematical formula}ΓK′(Pω)⊂ΓK(Pω) or {a mathematical formula}ΓK′(Nω)⊂ΓK(Nω), or {a mathematical formula}O is inconsistent.
      </list-item>
      <list-item label="•">
       Claim (3) (Theorem 4 in [9]) Let {a mathematical formula}K=(O,P) be an MKNF-consistent hybrid MKNF knowledge base and {a mathematical formula}(Pω,Nω) the well-founded partition of {a mathematical formula}K. Then {a mathematical formula}(IP,IN) is a three-valued MKNF model of {a mathematical formula}K, where {a mathematical formula}(IP,IN)=({I|I⊨OBO,Pω},{I|I⊨OBO,Nω}).
      </list-item>
     </list>
     <paragraph>
      Below, we show two counterexamples to these claims.
     </paragraph>
     <paragraph label="Example 3">
      Consider {a mathematical formula}K=(O,P), where {a mathematical formula}O=¬c and {a mathematical formula}P consists of{a mathematical formula} Consider the MKNF interpretation pair {a mathematical formula}(M,M), where {a mathematical formula}M={{b},{b,a}}. {a mathematical formula}(M,M) is a total three-valued (hence M is a two-valued) MKNF model of {a mathematical formula}K (more precisely, of the MKNF formula {a mathematical formula}π(K)≡K¬c∧π(P)), since {a mathematical formula}M⊨K and there exists no {a mathematical formula}M′⊃M such that {a mathematical formula}(I′,M′,M)⊨K, for some {a mathematical formula}I′∈M′ (see Definition 1). That is, to satisfy {a mathematical formula}K¬c, {a mathematical formula}M′ must not contain any interpretation that contains c, and we therefore can only expand M by adding ∅ or {a mathematical formula}{a} or both; in each of these cases, we have {a mathematical formula}(I′,M′,M)⊭Kb while {a mathematical formula}(I′,M′,M)⊨nota (independent of {a mathematical formula}I′). As a result, the second rule is not satisfied. As {a mathematical formula}(M,M) is a three-valued MKNF model of {a mathematical formula}K, by Definition 3, {a mathematical formula}K is MKNF-consistent.One can verify that the alternating fixpoint pair of {a mathematical formula}K, which is also the well-founded partition of {a mathematical formula}K, is {a mathematical formula}(Pω,Nω)=(∅,{Ka,Kb}). From {a mathematical formula}ΓK′(Pω)={Ka,Kb} and {a mathematical formula}ΓK(Pω)={Ka,Kb,Kc}, we get {a mathematical formula}ΓK′(Pω)⊂ΓK(Pω). Then by Claim (2) above, {a mathematical formula}K is MKNF-inconsistent. But we already concluded that {a mathematical formula}K is MKNF-consistent by definition. Hence Claim (2) is erroneous.Furthermore, from the partition {a mathematical formula}(Pω,Nω) we get an MKNF interpretation pair{a mathematical formula} which is not a three-valued MKNF-model of {a mathematical formula}K, since for any I, the three-valued MKNF structure {a mathematical formula}(I,〈IP,IN〉,〈IP,IN〉) evaluates {a mathematical formula}[Kc,K¬c,Ka,Kb,nota,notb] to {a mathematical formula}[f,t,u,u,u,u], under which the last rule in {a mathematical formula}P is not satisfied. Therefore, Claim (3) is erroneous too.We note that for this example Claim (1) holds, as {a mathematical formula}(M,M) is the only three-valued MKNF model of {a mathematical formula}K, and it is thus maximally undefined and the well-founded MKNF model of {a mathematical formula}K.  □
     </paragraph>
     <paragraph label="Example 4">
      Let us consider {a mathematical formula}K=(O,P), where {a mathematical formula}O=(a⊃h)∧(b⊃¬h) and {a mathematical formula}P consists of{a mathematical formula} Consider two partitions, {a mathematical formula}({Ka},{Ka}) and {a mathematical formula}({Kb},{Kb}). The corresponding MKNF interpretation pairs turn out to be two-valued MKNF models of {a mathematical formula}K. For example, for the former the interpretation pair is {a mathematical formula}(M,M), where {a mathematical formula}M={{a,h}}. It is a two-valued MKNF model of {a mathematical formula}K because it satisfies {a mathematical formula}K and for any {a mathematical formula}M′⊃M, {a mathematical formula}(I′,M′,M)⊭π(K), independent of {a mathematical formula}I′. For example, to satisfy the first rule with the evaluation of notb fixed, any interpretation I in {a mathematical formula}M′ must contain a and consequently h due to {a mathematical formula}KO. Besides {a mathematical formula}{a,h}, {a mathematical formula}{a,h,b} is the only such interpretation, but {a mathematical formula}{a,h,b}⊭OBO,{Ka}. That is, if {a mathematical formula}M′={{a,h},{a,h,b}} then {a mathematical formula}(I′,M′,M)⊭π(K), for any {a mathematical formula}I′∈M′. As {a mathematical formula}K possesses a two-valued (and therefore a three-valued) MKNF model, by definition it is MKNF-consistent.Let us compute the well-founded partition of {a mathematical formula}K, which turns out to be {a mathematical formula}(Pω,Nω)=(∅,{Ka,Kb}). Applying the conditions in Claim (2), since {a mathematical formula}ΓK′(Nω)=ΓK(Nω)=∅, {a mathematical formula}ΓK′(Pω)=ΓK(Pω)={Ka,Kb}, and {a mathematical formula}O is consistent, no inconsistency is detected. That is, for this example Claim (2) holds. But here, there is no three-valued MKNF interpretation pair {a mathematical formula}(M,N) for the well-founded partition {a mathematical formula}(∅,{Ka,Kb}), as {a mathematical formula}OBO,{Ka,Kb} is unsatisfiable and thus {a mathematical formula}N=∅, while by definition a three-valued MKNF interpretation pair must satisfy the condition {a mathematical formula}∅⊂N⊆M. As a result, for this example Claim (3) fails.Since the above two-valued MKNF models are not comparable w.r.t. undefinedness, let us consider whether there exists a three-valued MKNF model which is strictly less defined than both of the two-valued MKNF models. Take the partition {a mathematical formula}({Ka},{Ka}) for example. We may attempt to switch {a mathematical formula}Kb from f to u, in which case the corresponding partition is {a mathematical formula}({Ka},{Ka,Kb}), which results in {a mathematical formula}OBO,{Ka,Kb} being unsatisfiable; hence the interpretation pair that induces this partition does not exist. Or, we may try to switch {a mathematical formula}Ka from t to u, in which case the corresponding partition is {a mathematical formula}(∅,{Ka}). But the interpretation pair that induces it does not satisfy the first rule in {a mathematical formula}P.To conclude, since the interpretation pair that induces the well-founded partition does not exist and there is no other three-valued MKNF model of {a mathematical formula}K that is strictly less defined than both of the two-valued MKNF models discussed above, no well-founded MKNF model for {a mathematical formula}K exists. Thus Claim (1) fails too.  □
     </paragraph>
     <paragraph>
      In the above examples, that the three-valued MKNF models happen to be total is designed for the sake of simplicity. It is easy to construct counterexamples where three-valued MKNF models are not total. For example, we can add a rule, {a mathematical formula}Kp←notp, to {a mathematical formula}P in Example 4. One can check that, given partition {a mathematical formula}({Ka},{Ka,Kp}) (resp., partition {a mathematical formula}({Kb},{Kb,Kp})), the interpretation pair that induces it is a three-valued MKNF model, which is strictly partial.
     </paragraph>
     <paragraph>
      From the above discussion, we see that an MKNF-consistent hybrid MKNF knowledge base {a mathematical formula}K may have a well-founded MKNF model which does not correspond to its well-founded partition (e.g., Example 3), or {a mathematical formula}K simply does not have a well-founded MKNF model at all (e.g., Example 4). In general, we want our well-founded model to be minimal, unique, and computable by an iterated construction, the three properties that are typically associated with any notion of a well-founded model in logic programming. The notion of a well-founded MKNF model by Knorr et al. satisfies the first two but not the third, while the alternating fixpoint construction is not guaranteed to generate a partition that corresponds to a three-valued MKNF model, even when such a model exists. Since the problem has no easy fix, a reasonable approach is to pursue the correct relationships between the concepts introduced in [9], which leads to a classification of hybrid MKNF knowledge bases by a hierarchy of three classes, in addition to the class of all hybrid MKNF knowledge bases. For comparison, in the following we repeat the definition of MKNF-consistent hybrid MKNF knowledge base.
     </paragraph>
     <paragraph label="Definition 10">
      Let {a mathematical formula}K=(O,P) be a hybrid MKNF knowledge base and {a mathematical formula}(Pω,Nω) its alternating fixpoint pair.
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}K is MKNF-consistent if {a mathematical formula}K has a three-valued MKNF model (the definition is unchanged).
      </list-item>
      <list-item label="•">
       {a mathematical formula}K is MKNF-strongly consistent if {a mathematical formula}K has a well-founded MKNF model.
      </list-item>
      <list-item label="•">
       {a mathematical formula}K is MKNF-coherent if the pair {a mathematical formula}({I|I⊨OBO,Pω},{I|I⊨OBO,Nω}) is a three-valued MKNF model of {a mathematical formula}K.{sup:8}
      </list-item>
     </list>
     <paragraph>
      We have the following results.
     </paragraph>
     <paragraph label="Proposition 2">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base and{a mathematical formula}(Pω,Nω)its alternating fixpoint pair.
     </paragraph>
     <list>
      <list-item label="(a)">
       If{a mathematical formula}Kis MKNF-coherent, a well-founded MKNF model exists, which is unique and equals{a mathematical formula}({I|I⊨OBO,Pω},{I|I⊨OBO,Nω}).
      </list-item>
      <list-item label="(b)">
       If{a mathematical formula}Kis MKNF-coherent, it is MKNF-strongly consistent.
      </list-item>
      <list-item label="(c)">
       If{a mathematical formula}Kis MKNF-strongly consistent, it is MKNF-consistent.
      </list-item>
     </list>
     <paragraph label="Proof">
      The claim in (a) follows from Proposition 7 of [9], where the authors show that for any {a mathematical formula}Kξ∈KA(K), {a mathematical formula}Kξ∈Pω means that {a mathematical formula}Kξ is true (and notξ is false) in all three-valued MKNF models of {a mathematical formula}K, and {a mathematical formula}Kξ∈KA(K)\Nω means that {a mathematical formula}Kξ is false (and notξ is true) in all three-valued MKNF models of {a mathematical formula}K. Applying their proof to our case, since {a mathematical formula}K is MKNF-coherent, {a mathematical formula}(M,N)=({I|I⊨OBO,Pω},{I|I⊨OBO,Nω}) is a three-valued MKNF model by definition, and since all three-valued MKNF models of {a mathematical formula}K maintain and possibly extend the true and false K-atoms entailed by {a mathematical formula}(M,N), it follows that {a mathematical formula}(M,N) is {a mathematical formula}⪯k-minimal and thus the well-founded MKNF model of {a mathematical formula}K. The claim in (a) implies the claim in (b). Finally, (c) holds by definition.  □
     </paragraph>
     <paragraph>
      The definition of MKNF-coherent hybrid MKNF knowledge base given here is semantical, in that we need to check whether the alternating fixpoint pair corresponds to a three-valued MKNF model. Later in this paper, we will present a characterization of all three-valued MKNF models in terms of the alternating fixpoint construction and a consistency check (cf. Theorem 2). When applied to the alternating fixpoint pair {a mathematical formula}(Pω,Nω), the characterization leads to an alternative, but simpler definition of MKNF-coherent hybrid MKNF knowledge base by a consistency check (cf. Corollary 2).
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Characterization of three-valued MKNF models
     </section-title>
     <paragraph>
      In this section we define stable partitions and show two results: there is a one-to-one correspondence between three-valued MKNF models and stable partitions, and the latter can be guess-and-verified by computing the alternating fixpoint pair, plus a consistency test. This relationship will allow us to relate three-valued MKNF models to partial partitions, which are not only simpler in notation and concept but also provide a link of three-valued MKNF models with the familiar notion of partial stable models in logic programming. The latter also gives rise to intuitions of reasoning with hybrid MKNF knowledge bases.
     </paragraph>
     <paragraph>
      Following [12], we define an evaluation scheme of rules, with the eventual goal of relating the rule evaluation by a partition with the rule evaluation by a three-valued MKNF structure. Let {a mathematical formula}K=(O,P), let T and F be subsets of {a mathematical formula}KA(K) such that {a mathematical formula}T∩F=∅, and let r be a rule in {a mathematical formula}P. The rule {a mathematical formula}r[K,T,F] is obtained by replacing each modal atom {a mathematical formula}Kξ in r with t if {a mathematical formula}Kξ∈T, with f if {a mathematical formula}Kξ∈F, and with u otherwise. Similarly, the rule {a mathematical formula}r[not,T,F] is obtained by replacing each modal atom notξ appearing in r with t if {a mathematical formula}Kξ∈F, with f if {a mathematical formula}Kξ∈T, and with u otherwise. Finally, {a mathematical formula}r[T,F]=r[not,T,F][K,T,F].
     </paragraph>
     <paragraph>
      In all these cases, the result is simplified as follows:
     </paragraph>
     <list>
      <list-item label="•">
       If the value of the head atom in a rule is equal to or greater than the value of its body, then the rule is replaced by {a mathematical formula}t← (which means that the rule is satisfied); and
      </list-item>
      <list-item label="•">
       If the value of the head atom in a rule is less than the value of its body, then the rule is replaced by {a mathematical formula}f← (which means that the rule is not satisfied).
      </list-item>
     </list>
     <paragraph>
      The rule sets {a mathematical formula}P[K,T,F], {a mathematical formula}P[not,T,F], and {a mathematical formula}P[T,F] are obtained by replacing each rule r in {a mathematical formula}P with {a mathematical formula}r[K,T,F], {a mathematical formula}r[not,T,F], and {a mathematical formula}r[T,F], respectively. We write {a mathematical formula}P[K,T,F]=t if each rule in {a mathematical formula}P is of the form {a mathematical formula}t←, or {a mathematical formula}P=∅; similarly, we write {a mathematical formula}P[K,T,F]=f if {a mathematical formula}P contains a rule of the form {a mathematical formula}f←.
     </paragraph>
     <paragraph>
      We call the evaluation scheme above rule evaluation w.r.t. a partition, or just rule evaluation when there is no confusion. It is a generalization of the rule evaluation scheme of [12] from the two-valued case to the three-valued one, and is the counterpart of truth value evaluation of rules based on the corresponding interpretation pair. However, this generalization introduces technical subtleties. The following lemma gives the conditions under which rule evaluation coincides with evaluation by the corresponding structure.
     </paragraph>
     <paragraph label="Lemma 2">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base and{a mathematical formula}(T,P)a partition of{a mathematical formula}KA(K)such that{a mathematical formula}OBO,Pis satisfiable. Let{a mathematical formula}(T′,P′)be a partition such that{a mathematical formula}T′⊆Tand{a mathematical formula}P′⊆P, and for all{a mathematical formula}Kξ∈KA(K), if{a mathematical formula}OBO,T′⊨ξthen{a mathematical formula}Kξ∈T′and if{a mathematical formula}OBO,P′⊨ξthen{a mathematical formula}Kξ∈P′. Then, for any rule{a mathematical formula}r∈P,{a mathematical formula}for all{a mathematical formula}I′∈M′, where{a mathematical formula}(M′,N′)=({I|I⊨OBO,T′},{I|I⊨OBO,P′})and{a mathematical formula}(M,N)=({I|I⊨OBO,T},{I|I⊨OBO,P}).
     </paragraph>
     <paragraph>
      Before presenting the proof, let us explain the lemma for the special case with {a mathematical formula}T=T′ and {a mathematical formula}P=P′; we will comment on the general case afterwards. A key condition in the lemma is that if {a mathematical formula}T′ (resp. {a mathematical formula}P′) contains all modal K-atoms whose objective counterparts are derivable from {a mathematical formula}OBO,T′ (resp. {a mathematical formula}OBO,P′), then rule evaluation w.r.t. {a mathematical formula}(T′,P′) is “complete” in the sense that it incorporates the effect of reasoning with {a mathematical formula}O, in which case rule evaluation coincides with the evaluation by the corresponding structure. The coincidence is not guaranteed if the condition does not hold. For example, consider {a mathematical formula}K=(O,P)=({c⊃d},{r:Kd←notc}) and the partition {a mathematical formula}(T,P)=(∅,{Kc}). With{a mathematical formula} we have {a mathematical formula}r[T,KA(K)∖P]=(f←u)=f and {a mathematical formula}(I,〈M,N〉,〈M,N〉)(π(r))=(u⊃u)=t, for which the coincidence does not hold.
     </paragraph>
     <paragraph>
      For the general case with {a mathematical formula}(T′,P′), where {a mathematical formula}T′⊆T and {a mathematical formula}P′⊆P and either of the inclusions may be proper, the goal is to accommodate the situations where condition (b) for the three-valued MKNF model (which is defined in Definition 2) needs to be related to the corresponding rule evaluation.
     </paragraph>
     <paragraph label="Proof of Lemma 2">
      First observe that since {a mathematical formula}(T′,P′) is a partition, we have {a mathematical formula}T′⊆P′. As {a mathematical formula}OBO,P is satisfiable, we have {a mathematical formula}∅⊂N′⊆M′ and thus {a mathematical formula}(M′,N′) is an MKNF interpretation pair. Then, it is easy to check that the truth value evaluation of modal atoms based on such an MKNF structure {a mathematical formula}Ω=(I,〈M′,N′〉,〈M,N〉) (see Table 2) is related to memberships based on a partition {a mathematical formula}(T′,P′) in the following way: for any (ground) first-order atom ξ, we have{a mathematical formula} By the rule evaluation defined in this section and the evaluation by a structure in Table 2, we conclude that these evaluations produce the same result for any rule in {a mathematical formula}P. □
     </paragraph>
     <paragraph>
      We now define an important notion called stable partition.
     </paragraph>
     <paragraph label="Definition 11">
      Let {a mathematical formula}K=(O,P) be a hybrid MKNF knowledge base, and {a mathematical formula}T⊆P⊆KA(K). {a mathematical formula}(T,P) is a stable partition of {a mathematical formula}K if
     </paragraph>
     <list>
      <list-item label="(1)">
       {a mathematical formula}OBO,P is satisfiable;
      </list-item>
      <list-item label="(2)">
       (i) {a mathematical formula}∀Kξ∈KA(K), if {a mathematical formula}OBO,T⊨ξ then {a mathematical formula}Kξ∈T and if {a mathematical formula}OBO,P⊨ξ then {a mathematical formula}Kξ∈P; and (ii) in addition, {a mathematical formula}P[T,KA(K)∖P]=t; and
      </list-item>
      <list-item label="(3)">
       for any other partition {a mathematical formula}(T′,P′) with {a mathematical formula}T′⊆T and {a mathematical formula}P′⊆P, where at least one of the inclusions is proper,
      </list-item>
     </list>
     <paragraph>
      The notion of a stable partition imitates that of a three-valued MKNF model by performing specific checks. Condition (1) requires that the DL component {a mathematical formula}O be consistent with P, which guarantees the consistency of {a mathematical formula}O with T (due to {a mathematical formula}T⊆P). Condition (2) ensures that {a mathematical formula}(T,P) “satisfy” {a mathematical formula}Kπ(O) as well as rules in {a mathematical formula}P; in both cases we are able to devise simple checks to achieve the goal. In (3), we minimize the derivation of modal K-atoms, as well as the set of undefined K-atoms, by not allowing a smaller {a mathematical formula}T′ or a smaller {a mathematical formula}P′ so that {a mathematical formula}(T′,P′) can still “satisfy” {a mathematical formula}Kπ(O) on the one hand and {a mathematical formula}π(P) on the other (with the evaluation of not-atoms fixed to {a mathematical formula}KA(K)∖P). This simulates condition (b) of Definition 2.
     </paragraph>
     <paragraph label="Theorem 1">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base.
     </paragraph>
     <list>
      <list-item label="(I)">
       If an (MKNF) interpretation pair{a mathematical formula}(M,N)is a three-valued MKNF model of{a mathematical formula}K, then the partition{a mathematical formula}(T,P)induced by{a mathematical formula}(M,N)is a stable partition of{a mathematical formula}K.
      </list-item>
      <list-item label="(II)">
       If a partition{a mathematical formula}(T,P)is a stable partition of{a mathematical formula}K, then the interpretation pair{a mathematical formula}(M,N), where{a mathematical formula}(M,N)=({I|I⊨OBO,T},{I|I⊨OBO,P}), is a three-valued MKNF model of{a mathematical formula}K.
      </list-item>
     </list>
     <paragraph label="Fact 1">
      Before presenting the proof, let us state two facts to be used in the proof. The first one directly follows from Lemma 1. Let{a mathematical formula}(M,N)be a three-valued MKNF model of{a mathematical formula}Kand{a mathematical formula}(T,P)the partition induced by{a mathematical formula}(M,N). Then, for any{a mathematical formula}Kξ∈KA(K), if{a mathematical formula}OBO,T⊨ξthen{a mathematical formula}Kξ∈Tand if{a mathematical formula}OBO,P⊨ξthen{a mathematical formula}Kξ∈P.
     </paragraph>
     <paragraph label="Fact 2">
      Let{a mathematical formula}(T,P)be a partition of{a mathematical formula}KA(K)such that{a mathematical formula}OBO,Pis satisfiable, and let{a mathematical formula}(M,N)=({I|I⊨OBO,T},{I|I⊨OBO,P}). Then,{a mathematical formula}(M,N)⊨Kπ(O).
     </paragraph>
     <paragraph>
      This fact is rather direct, as if the conclusion does not hold, then {a mathematical formula}∃I∈M, {a mathematical formula}I⊭π(O), which results in {a mathematical formula}M≠{I|I⊨OBO,T}, a contradiction to the assumption that {a mathematical formula}M={I|I⊨OBO,T}.
     </paragraph>
     <paragraph label="Proof of Theorem 1">
      (I) Let {a mathematical formula}(M,N) be a three-valued MKNF model of {a mathematical formula}K and {a mathematical formula}(T,P) the partition induced from {a mathematical formula}(M,N). From Proposition 1 (i.e., Proposition 3 of [9]), we know that such a partition exists and satisfies{a mathematical formula} Since {a mathematical formula}(M,N) is an interpretation pair, we have {a mathematical formula}∅⊂N⊆M and thus {a mathematical formula}OBO,P is satisfiable; i.e., condition (1) of Definition 11 is satisfied. For any {a mathematical formula}Kξ∈KA(K), if {a mathematical formula}OBO,T⊨ξ then by equation (4)ξ evaluates to true in I for all {a mathematical formula}I∈M; thus it follows from Fact 1 that we have {a mathematical formula}Kξ∈T. The case for P is similar. Furthermore, by {a mathematical formula}(M,N)⊨π(K), {a mathematical formula}∀I∈M,(I,〈M,N〉,〈M,N〉)(π(K))=t. Now since all the conditions in Lemma 2 are satisfied (for the special case where {a mathematical formula}T=T′ and {a mathematical formula}P=P′), it follows that we have {a mathematical formula}P[T,KA(K)∖P]=t. Thus condition (2) of Definition 11 is satisfied.To show condition (3) of Definition 11, consider any other partition {a mathematical formula}(T′,P′) with {a mathematical formula}T′⊆T and {a mathematical formula}P′⊆P, where at least one of the inclusions is proper. Assume that part (i) of condition (3) is false w.r.t. {a mathematical formula}(T′,P′) and we show that part (ii) of the condition (3) must be true w.r.t. {a mathematical formula}(T′,P′) (let us refer to these conditions as 3(i) and 3(ii), respectively). Note that if 3(i) is true w.r.t. {a mathematical formula}(T′,P′), condition (3) of Definition 11 is satisfied trivially. Observe that the negation of 3(i) is that {a mathematical formula}∀ξ∈KA(K), if {a mathematical formula}OBO,T′⊨ξ then {a mathematical formula}Kξ∈T′ and if {a mathematical formula}OBO,P′⊨ξ then {a mathematical formula}Kξ∈P′. As {a mathematical formula}P′⊆P and {a mathematical formula}OBO,P is satisfiable, {a mathematical formula}OBO,P′ is satisfiable. Now all the conditions in Lemma 2 are satisfied for the general case of {a mathematical formula}(T′,P′). For the sake of contradiction, assume 3(ii) does not hold for {a mathematical formula}(T′,P′), i.e., {a mathematical formula}P[not,T,KA(K)∖P][K,T′,KA(K)∖P′]=t. By Lemma 2, we have, for all {a mathematical formula}I∈M, {a mathematical formula}(I,〈M′,N′〉,〈M,N〉)(π(P))=t, where {a mathematical formula}(M′,N′)=({I|I⊨OBO,T′},{I|I⊨OBO,P′}). This contradicts the assumption that {a mathematical formula}(M,N) is a three-valued MKNF model of {a mathematical formula}K. Thus, 3(ii) must hold for {a mathematical formula}(T′,P′) and it follows that condition (3) of Definition 11 is satisfied. Since all the conditions for stable partition are satisfied, we conclude that {a mathematical formula}(T,P) is a stable partition of {a mathematical formula}K.(II) Let {a mathematical formula}(T,P) be a stable partition of {a mathematical formula}K. We show that conditions (a) and (b) of Definition 2 are satisfied for {a mathematical formula}(M,N) to be a three-valued MKNF model, where {a mathematical formula}(M,N)=({I|I⊨OBO,T},{I|I⊨OBO,P}). Since {a mathematical formula}(T,P) is a stable partition, we have that {a mathematical formula}T⊆P and {a mathematical formula}OBO,P is satisfiable. It follows from Fact 2 that {a mathematical formula}(M,N)⊨Kπ(O). As a stable partition, {a mathematical formula}(T,P) has the property that {a mathematical formula}P[T,KA(K)∖P]=t, which, by Lemma 2, implies {a mathematical formula}(M,N)⊨π(P). Note that the conditions in Lemma 2 are all satisfied for the special case of {a mathematical formula}T=T′ and {a mathematical formula}P=P′ because {a mathematical formula}(T,P) is a stable partition of {a mathematical formula}K and thus satisfies condition (2) of Definition 11. Together, we have {a mathematical formula}(M,N)⊨π(K). Thus, condition (a) of Definition 2 is satisfied.Further, {a mathematical formula}(T,P) being stable implies that for any other partition {a mathematical formula}(T′,P′) such that {a mathematical formula}T′⊆T and {a mathematical formula}P′⊆P, with at least one of them being proper, either part (i) or part (ii) of condition (3) of Definition 11 holds. If part (i) holds, then it is easy to see that the corresponding interpretation pair {a mathematical formula}(M′,N′)=({I|I⊨OBO,T′},{I|I⊨OBO,P′}) does not satisfy {a mathematical formula}Kπ(O), i.e., {a mathematical formula}(I,〈M′,N′〉,〈M,N〉)(Kπ(O))≠t for some {a mathematical formula}I∈M′, and therefore condition (b) of Definition 2 is satisfied. Now let us assume that 3(i) of Definition 11 is false. We will then have {a mathematical formula}P[not,T,KA(K)\P][K,T′,KA(K)\P′]≠t. Note that the negation of 3(i) is that if {a mathematical formula}OBO,T′⊨ξ then {a mathematical formula}Kξ∈T′ and if {a mathematical formula}OBO,P′⊨ξ then {a mathematical formula}Kξ∈P′. Thus, Lemma 2 can be applied, which results in {a mathematical formula}∀I∈M′,(I,〈M′,N′〉,〈M,N〉)(π(P))≠t. This means that condition (b) of Definition 2 is satisfied. We therefore conclude that {a mathematical formula}(M,N) is a three-valued MKNF model of {a mathematical formula}K. This completes the proof. □
     </paragraph>
     <paragraph>
      Given two partitions {a mathematical formula}(T,P) and {a mathematical formula}(T′,P′), we define an order of precision{a mathematical formula}⊆p as follows: {a mathematical formula}(T,P)⊆p(T′,P′) if {a mathematical formula}T⊆T′ and {a mathematical formula}P′⊆P. As {a mathematical formula}(T,P) and {a mathematical formula}(T′,P′) are partitions, by definition they satisfy {a mathematical formula}T⊆P and {a mathematical formula}T′⊆P′; therefore {a mathematical formula}(T,P)⊆p(T′,P′) expresses {a mathematical formula}T⊆T′⊆P′⊆P. Intuitively, the pair {a mathematical formula}(T′,P′) is more precise (in fact, no less precise) than {a mathematical formula}(T,P) in terms of truth and falsity of modal atoms, and is an approximation to the full precisions, which are exact partitions {a mathematical formula}(Q,Q) such that Q is in between {a mathematical formula}T′ and {a mathematical formula}P′. This is the familiar notion of approximation given in [4].
     </paragraph>
     <paragraph>
      Note that the order of precision {a mathematical formula}⊆p defined above for partitions is the counterpart of the order of knowledge {a mathematical formula}⪯k defined for MKNF interpretation pairs.
     </paragraph>
     <paragraph label="Definition 12">
      Let {a mathematical formula}K be a hybrid MKNF knowledge base. A stable partition {a mathematical formula}(T,P) of {a mathematical formula}K is called a least stable partition of {a mathematical formula}K if for any other stable partition {a mathematical formula}(T′,P′) of {a mathematical formula}K, {a mathematical formula}(T,P)⊆p(T′,P′).
     </paragraph>
     <paragraph>
      By definition, the least stable partition is unique when it exists.
     </paragraph>
     <paragraph>
      From Theorem 1, we obtain the following:
     </paragraph>
     <paragraph label="Corollary 1">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base and{a mathematical formula}(Pω,Nω)its alternating fixpoint pair.
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Kis MKNF-consistent iff{a mathematical formula}Khas a stable partition,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Kis MKNF-strongly consistent iff{a mathematical formula}Khas a least stable partition,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Kis MKNF-coherent iff{a mathematical formula}(Pω,Nω)is a least stable partition, and
      </list-item>
      <list-item label="•">
       for any stable partition{a mathematical formula}(T,P)of{a mathematical formula}K,{a mathematical formula}(Pω,Nω)⊆p(T,P).
      </list-item>
     </list>
     <paragraph>
      The last claim above is derived as follows. We first apply Proposition 7 of [9], where the authors show that all three-valued MKNF models of {a mathematical formula}K extend the true and false K-atoms expressed in {a mathematical formula}(Pω,Nω). Then, the claim follows from the one-to-one correspondence between three-valued MKNF models and stable partitions given in Theorem 1.
     </paragraph>
     <paragraph>
      Given an MKNF knowledge base {a mathematical formula}K=(O,P), a major advantage of representing three-valued MKNF models in terms of stable partitions is that it allows us to compute three-valued MKNF models using a relatively straightforward guess-and-check approach – guess a partition {a mathematical formula}(T,P) and check whether {a mathematical formula}(T,P) is stable.
     </paragraph>
     <paragraph label="Theorem 2">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base and{a mathematical formula}(T,P)a partition of{a mathematical formula}K. Then,{a mathematical formula}(T,P)is a stable partition iff{a mathematical formula}T=ΓK(P),{a mathematical formula}P=ΓK′(T), and{a mathematical formula}OBO,ΓK(T)is satisfiable.
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}(⇐) Assume {a mathematical formula}T=ΓK(P), {a mathematical formula}P=ΓK′(T), and {a mathematical formula}OBO,ΓK(T) is satisfiable. Given that {a mathematical formula}OBO,ΓK(T) is satisfiable, there exists an interpretation pair {a mathematical formula}(M,N) that satisfies it. Since {a mathematical formula}(M,N)⊨ΓK(T), for any {a mathematical formula}Kξ∈ΓK(T) we have {a mathematical formula}OBO,ΓK(T)⊭¬ξ. From {a mathematical formula}T⊆P and {a mathematical formula}T=ΓK(P), we get {a mathematical formula}T=ΓK(P)⊆ΓK(T). It follows that {a mathematical formula}OBO,T⊭¬ξ. Thus, the two reducts, {a mathematical formula}K/T and {a mathematical formula}K//T, coincide, i.e., {a mathematical formula}ΓK(T)=ΓK′(T)=P. It follows that {a mathematical formula}OBO,P is satisfiable, i.e., condition (1) of Definition 11 is satisfied. For condition 2(i) of Definition 11, since {a mathematical formula}T=ΓK(P)=lfp(TK\P), it follows that if {a mathematical formula}OBO,T⊨Kξ then {a mathematical formula}Kξ∈T, for any {a mathematical formula}Kξ∈KA(K). Similarly, as {a mathematical formula}P=ΓK′(T)=lfp(TK\\T), if {a mathematical formula}OBO,P⊨Kξ then {a mathematical formula}Kξ∈P. Thus condition 2(i) of Definition 11 is satisfied.Next, for the evaluation of {a mathematical formula}P[T,KA(K)∖P], consider each rule {a mathematical formula}r∈P. If {a mathematical formula}Bd(r) evaluates to t w.r.t. {a mathematical formula}r[T,KA(K)\P], by definition, {a mathematical formula}Bd+(r)⊆T and {a mathematical formula}∀notB∈Bd−(r), {a mathematical formula}KB∈KA(K)\P. Then by {a mathematical formula}T=ΓK(P), we have {a mathematical formula}Hd(r)∈T, and thus r evaluates to t, i.e., {a mathematical formula}r[T,KA(K)\P]=t. The case where {a mathematical formula}Bd(r) is f w.r.t. {a mathematical formula}r[T,KA(K)\P] is automatic. Now assume {a mathematical formula}Bd(r) is u w.r.t. {a mathematical formula}r[T,KA(K)\P]. Let {a mathematical formula}Hd(r)=KH. Since {a mathematical formula}Bd+(r)⊆P and {a mathematical formula}Bd−(r)⊆P\T, by {a mathematical formula}ΓK(T)=P, we get {a mathematical formula}Hd(r)∈P. That is, {a mathematical formula}Hd(r) is u or t w.r.t. {a mathematical formula}r[T,KA(K)\P]. Based on all cases of the truth value of the body of r, we conclude that {a mathematical formula}r[T,KA(K)∖P]=t. As r is arbitrary, we have {a mathematical formula}P[T,KA(K)∖P]=t. Thus condition 2(ii) of Definition 11 is satisfied. As a result, the whole condition (2) is satisfied. Finally, condition (3) of Definition 11 easily holds, since T is the least fixpoint of the operator {a mathematical formula}TK/P and P is the least fixpoint of the operator {a mathematical formula}TK//T.{a mathematical formula}(⇒) Given a stable partition {a mathematical formula}(T,P), we first show that the fixpoint equations hold. Consider {a mathematical formula}T=ΓK(P) first. For {a mathematical formula}ΓK(P)⊆T, we show the claim by induction on the computation of {a mathematical formula}ΓK(P)=lfp(TK/P). As {a mathematical formula}TK/P0=∅, the claim holds for {a mathematical formula}n=0. Now for all {a mathematical formula}n≥0, assume {a mathematical formula}TK/Pn⊆T and we show {a mathematical formula}TK/Pn+1⊆T. By the definition of {a mathematical formula}TK/P, for any {a mathematical formula}Kξ∈TK/Pn+1\TK/Pn, either {a mathematical formula}OBO,TK/Pn⊨Kξ or {a mathematical formula}∃r∈P with {a mathematical formula}Hd(r)=Kξ such that {a mathematical formula}Bd+(r)⊆TK/Pn and for each {a mathematical formula}notB∈Bd−(r), {a mathematical formula}KB∉P. For the former case, by induction hypothesis, we have {a mathematical formula}OBO,T⊨Kξ, and then, since {a mathematical formula}(T,P) is a stable partition, by condition 2(i) of Definition 11, we have {a mathematical formula}Kξ∈T. For the latter case, we have {a mathematical formula}Bd+(r)⊆T by induction hypothesis. It then follows from condition 2(ii) of Definition 11, namely {a mathematical formula}r[T,KA(K)\P]=t, that we have {a mathematical formula}Kξ∈T. Thus {a mathematical formula}ΓK(P)⊆T holds.Next, since we already have {a mathematical formula}ΓK(P)⊆T, for the sake of contradiction, let {a mathematical formula}T′=ΓK(P) and assume {a mathematical formula}T′⊂T. We show that, for the partition {a mathematical formula}(T′,P), condition (3) of Definition 11 does not hold and thus {a mathematical formula}(T,P) cannot be a stable partition. For 3(i), by the definition of {a mathematical formula}ΓK(P), for any {a mathematical formula}Kξ∈T∖T′, {a mathematical formula}OBO,T′⊭ξ, which violates condition 3(i) of Definition 11 (with regard to 3(i), note that here {a mathematical formula}P′=P). For 3(ii), consider each {a mathematical formula}r∈P of the form {a mathematical formula}KH←Bd(r) and we show that {a mathematical formula}r[not,T,KA(K)\P][K,T′,KA(K)\P]=t thus violating condition 3(ii). For notational convenience, let {a mathematical formula}Θ=r[not,T,KA(K)\P][K,T′,KA(K)\P]. If {a mathematical formula}Bd(r) is t w.r.t. Θ, we have {a mathematical formula}Bd+(r)⊆T′ and {a mathematical formula}KB∉P, {a mathematical formula}∀notB∈Bd−(r). By the definition of {a mathematical formula}T′, we have {a mathematical formula}KH∈T′ and thus {a mathematical formula}Θ=t in this case. The case where {a mathematical formula}Bd(r) is f w.r.t. Θ is automatic. Now let {a mathematical formula}Bd(r) be u w.r.t. Θ. Then we have {a mathematical formula}Bd+(r)⊆P and {a mathematical formula}KB∈P, {a mathematical formula}∀notB∈Bd−(r). Since {a mathematical formula}(T,P) is a stable partition, it follows that we have {a mathematical formula}r[T,KA(K)\P]=t by condition 2(ii) of Definition 11, hence {a mathematical formula}KH∈P, i.e., {a mathematical formula}KH is either t or u, and in this case we also have {a mathematical formula}Θ=t. This shows that {a mathematical formula}T′⊂T is impossible, and because {a mathematical formula}T′⊆T, we must have {a mathematical formula}T′=T, i.e., {a mathematical formula}ΓK(P)=T. Similarly, we can prove that {a mathematical formula}P=ΓK′(T).We now show that {a mathematical formula}OBO,ΓK(T) is satisfiable. Since {a mathematical formula}(T,P) is a stable partition of {a mathematical formula}K, {a mathematical formula}OBO,P is satisfiable by definition. Consider two cases: (a) {a mathematical formula}ΓK′(T)≠ΓK(T) and (b) {a mathematical formula}ΓK′(T)=ΓK(T). Assume (a). By definition, the only reason for the inequality is because {a mathematical formula}P//T⊂P/T, which causes {a mathematical formula}ΓK′(T)⊂ΓK(T). Let {a mathematical formula}P⁎=ΓK(T). Note that {a mathematical formula}P=lfp(TK//T). As P is a fixpoint of {a mathematical formula}TK//T and {a mathematical formula}P⊂P⁎, there exists a K-atom {a mathematical formula}Kξ∈P⁎∖P, which is derivable by a rule {a mathematical formula}r∈P, whose reduced positive counterpart {a mathematical formula}r′ is in {a mathematical formula}P/T but not in {a mathematical formula}P//T, due to {a mathematical formula}OBO,T⊨¬ξ. That is, {a mathematical formula}∃Kξ∈P⁎∖P and {a mathematical formula}∃r∈P, such that {a mathematical formula}Kξ=Hd(r), and {a mathematical formula}Bd+(r)⊆P and {a mathematical formula}KB∉T, {a mathematical formula}∀notB∈Bd−(r), while {a mathematical formula}OBO,T⊨¬ξ. It follows that r evaluates to false under {a mathematical formula}(T,P), i.e., {a mathematical formula}r[T,KA(K)∖P]=f, which violates condition 2(ii) of Definition 11. Therefore, {a mathematical formula}(T,P) is not a stable partition of {a mathematical formula}K, a contradiction. Since {a mathematical formula}ΓK′(T)≠ΓK(T) is not possible, we must have {a mathematical formula}ΓK′(T)=ΓK(T), which is case (b) above. As {a mathematical formula}OBO,P is satisfiable and {a mathematical formula}P=ΓK′(T)=ΓK(T), it follows that {a mathematical formula}OBO,ΓK(T) is satisfiable. This completes the proof.  □
     </paragraph>
     <paragraph label="Example 5">
      Continuing with Example 2 (also referring to Example 1), we know that the well-founded partition of {a mathematical formula}K is {a mathematical formula}(Pω,Nω)=({Ka,Kb,Kc},{Ka,Kb,Kc,Kd,Ke}). It is easy to check that {a mathematical formula}OBO,ΓK(Pω) is satisfiable. Thus, from Theorem 2 we conclude that {a mathematical formula}(Pω,Nω) is a stable partition of {a mathematical formula}K.  □
     </paragraph>
     <paragraph>
      One useful result derived from this theorem is an alternative way of checking the property of MKNF-coherence of a given hybrid MKNF knowledge base {a mathematical formula}K. Once its alternating fixpoint pair {a mathematical formula}(Pω,Nω) is computed, instead of a full verification that {a mathematical formula}(Pω,Nω) is stable, we can just perform a consistency test.
     </paragraph>
     <paragraph label="Corollary 2">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base and{a mathematical formula}(Pω,Nω)its alternating fixpoint pair.{a mathematical formula}Kis MKNF-coherent iff{a mathematical formula}OBO,ΓK(Pω)is satisfiable.
     </paragraph>
     <paragraph>
      We identify two cases where, to verify whether a partition {a mathematical formula}(T,P) is stable, we can check weaker conditions. In the first case below, instead of checking the satisfiability of {a mathematical formula}OBO,ΓK(E) for an exact partition {a mathematical formula}(E,E), we just check the satisfiability of {a mathematical formula}π(O). It is convenient to check the satisfiability of {a mathematical formula}π(O) independent of rules, as in practice the same underlying ontological knowledge base {a mathematical formula}O may be applied in different applications, each of which is implemented by a different rule base. In the second case, for an MKNF-coherent MKNF knowledge base {a mathematical formula}K, to check whether a partition {a mathematical formula}(T,P) is stable, we can skip the consistency test on {a mathematical formula}OBO,ΓK(T).
     </paragraph>
     <paragraph label="Theorem 3">
      Let{a mathematical formula}K=(O,P)be a hybrid MKNF knowledge base.
     </paragraph>
     <list>
      <list-item label="•">
       Assume{a mathematical formula}π(O)is satisfiable. Then, for any{a mathematical formula}E⊆KA(K),{a mathematical formula}(E,E)is a stable partition of{a mathematical formula}Kiff{a mathematical formula}E=ΓK(E)=ΓK′(E).
      </list-item>
      <list-item label="•">
       Assume{a mathematical formula}Kis MKNF-coherent. Then, for any partition{a mathematical formula}(T,P)of{a mathematical formula}KA(K),{a mathematical formula}(T,P)is a stable partition of{a mathematical formula}Kiff{a mathematical formula}T=ΓK(P)and{a mathematical formula}P=ΓK′(T).
      </list-item>
     </list>
     <paragraph label="Proof">
      For any exact partition {a mathematical formula}(E,E) of {a mathematical formula}KA(K), we show that under the condition that {a mathematical formula}π(O) is satisfiable, the equations {a mathematical formula}E=ΓK(E)=ΓK′(E) guarantee that {a mathematical formula}OBO,ΓK(E) is satisfiable. Assume this is not the case. Then, from {a mathematical formula}E=ΓK(E) we know that {a mathematical formula}OBO,E is unsatisfiable, which implies that the reduct of {a mathematical formula}P (by the coherent transform) w.r.t. E is an empty rule set, i.e., {a mathematical formula}P//E=∅. Thus, it follows from Definition 8 that {a mathematical formula}lfp(TK//E)={Kξ∈KA(K)|OBO,∅⊨ξ}, as derived K-atoms are just those whose objective counterparts are logic consequences of {a mathematical formula}π(O). Since {a mathematical formula}E=ΓK′(E)=lfp(TK//E), E consists of K-atoms whose objective counterparts are logical consequences of {a mathematical formula}π(O). Since {a mathematical formula}π(O) is satisfiable, it follows that {a mathematical formula}OBO,E is also satisfiable. This is a contradiction.For the second claim, we only need to show that the condition {a mathematical formula}T=ΓK(P) and {a mathematical formula}P=ΓK′(T) guarantees the satisfaction of {a mathematical formula}OBO,ΓK(T). Since {a mathematical formula}K is MKNF-coherent, its alternating fixpoint pair {a mathematical formula}(Pω,Nω) is a stable partition, and by Theorem 2, {a mathematical formula}OBO,ΓK(Pω) is satisfiable. From Corollary 1, we know that {a mathematical formula}(Pω,Nω)⊆p(T,P) for any stable partition {a mathematical formula}(T,P) of {a mathematical formula}K. It follows that {a mathematical formula}Pω⊆T, from which we derive {a mathematical formula}ΓK(T)⊆ΓK(Pω). As {a mathematical formula}OBO,ΓK(Pω) is satisfiable, it follows that {a mathematical formula}OBO,ΓK(T) is also satisfiable.  □
     </paragraph>
     <paragraph>
      It is worth mentioning that in [12] the stability of an exact partition {a mathematical formula}(E,E) is verified by an operator similar to the operator {a mathematical formula}ΓK defined in this paper (cf. Proposition 6.13 of [12]); thus their method of verification can be viewed as a special case of computing alternating fixpoints.
     </paragraph>
     <paragraph>
      Finally, we analyze reasoning complexities with three-valued MKNF semantics. We are interested in three questions: the complexity of computing the well-founded MKNF model for MKNF-coherent hybrid MKNF knowledge bases, the complexity of deciding whether a three-valued MKNF model exists, and the complexity of deciding whether a two-valued MKNF model exists. In all of these cases, according to Theorem 1, we can answer each question in terms of stable partitions. We consider data complexity, which is measured in terms of ground facts in {a mathematical formula}π(O) (or A-Box assertions in DL knowledge base {a mathematical formula}O) and rule facts. Here, we consider nonground, but DL-safe rules. Below, given a rule base {a mathematical formula}P, we denote by {a mathematical formula}PG the grounding of {a mathematical formula}P and we let {a mathematical formula}KG=(O,PG).
     </paragraph>
     <paragraph label="Proof">
      Let{a mathematical formula}K=(O,P)be a DL-safe hybrid MKNF knowledge base and{a mathematical formula}(T,P)a partition of{a mathematical formula}KA(KG). Assuming that the entailment of ground literals in the language of{a mathematical formula}Ois decidable with data complexity{a mathematical formula}C, the data complexity of verifying whether{a mathematical formula}(T,P)is a stable partition is in{a mathematical formula}PTimeC.To compute the fixpoints {a mathematical formula}ΓK′(T) and {a mathematical formula}ΓK(P), we need at most {a mathematical formula}|PG| calls to an oracle running in {a mathematical formula}C, where {a mathematical formula}|PG| is polynomial in {a mathematical formula}|P| since nonground rules in {a mathematical formula}P are bounded in size. Based on Theorem 2, we need two more calls to the oracle to check the satisfiability of {a mathematical formula}OBO,ΓK(T). Hence the conclusion.  □
     </paragraph>
     <paragraph label="Corollary 3">
      As a special case, the same complexity applies to computing the well-founded MKNF model. If{a mathematical formula}Kis MKNF-coherent, its well-founded MKNF model can be computed in{a mathematical formula}PTimeC.
     </paragraph>
     <paragraph>
      If {a mathematical formula}C is tractable, so is the verification in Proposition 3 and so is the testing of MKNF-coherence. That is, the true, false, and undefined atoms implied by the well-founded MKNF model of an MKNF-coherent {a mathematical formula}K can be determined in polynomial time.
     </paragraph>
     <paragraph label="Proof">
      Combining Proposition 3 with Theorem 2, we can obtain the following bounds. Let{a mathematical formula}Kbe a DL-safe hybrid MKNF knowledge base, and assume that the entailment of ground literals in the language of{a mathematical formula}Ois decidable with data complexity{a mathematical formula}C. Then, the data complexity of deciding whether a three-valued MKNF model exists, or deciding whether a two-valued MKNF model exists, is in{a mathematical formula}NPPTimeC. If{a mathematical formula}Cis tractable, the same decision problem for both is NP-complete.By Theorem 2, we can guess a partition {a mathematical formula}(T,P) and verify whether {a mathematical formula}P=ΓK′(T) and {a mathematical formula}T=ΓK(P), and check the satisfiability of {a mathematical formula}OBO,ΓK(T). This time we call an oracle running in {a mathematical formula}PTimeC. For the case of two-valued MKNF models, we only need to guess exact partitions. When {a mathematical formula}C is tractable, the membership in NP is guaranteed by Theorem 2, where the alternating fixpoint construction and the consistency test together take polynomial time. The hardness for the two-valued case follows from the complexity under the stable model semantics [2]. To show the hardness for the three-valued case, we encode an NP-hard problem as {a mathematical formula}P, and add polynomially many first-order formulas, each of which is of polynomial size, to {a mathematical formula}O so that no modal atoms may be undefined in any of the three-valued MKNF models of {a mathematical formula}K=(O,P). For example, consider the encoding of the k-colorability problem given in [13] by the following set of MKNF rules:{a mathematical formula} Given a directed graph in terms of facts about vertices and arcs, as well as k colors, let us denote by {a mathematical formula}P the set of rules above and these facts. Then, the given graph is k-colorable iff {a mathematical formula}P has a two-valued MKNF model. Based on the definition of three-valued MKNF model (Definition 2), we can see that the three-valued MKNF models of {a mathematical formula}P that are strictly partial are those where some of the instances of {a mathematical formula}KColor(⋅,⋅) and {a mathematical formula}KOtherColor(⋅,⋅), possibly along with the modal atom {a mathematical formula}Kq, are undefined. To block these partial MKNF models, let {a mathematical formula}O consist of ¬q and{a mathematical formula} which says that it is false that any vertex is colored with two different colors. First, it is easy to see that {a mathematical formula}P and {a mathematical formula}K=(O,P) have exactly the same two-valued MKNF models. Second, suppose {a mathematical formula}(T,P), where {a mathematical formula}T⊂P, is a (strictly partial) stable partition of {a mathematical formula}K. Then, P must contain a pair of modal K-atoms, {a mathematical formula}KColor(n,c1) and {a mathematical formula}KColor(n,c2), for some vertex n and distinct colors {a mathematical formula}c1 and {a mathematical formula}c2 such that {a mathematical formula}KColor(n,c1) and {a mathematical formula}KColor(n,c2) are not in T. That is, to satisfy the relevant rules as well as condition (3) for a stable partition (cf. Definition 11), both of these two K-atoms must be undefined at the same time. This implies that {a mathematical formula}OBO,P is unsatisfiable, and thus {a mathematical formula}(T,P) cannot be a stable partition of {a mathematical formula}K, which is a contradiction. Therefore, no three-valued MKNF models of {a mathematical formula}K can be strictly partial. We thus have shown a polynomial reduction of k-colorability to the stable partition existence problem (and thus to the three-valued MKNF model existence problem), for hybrid MKNF knowledge bases. We are done.  □
     </paragraph>
     <paragraph>
      Our claims here are consistent with the complexity results shown in [9], [12], except that the result for the problem of deciding the existence of a three-valued MKNF model is new. These results can be extended for query answering for ground modal atoms, for which the decision problem is the complement of the model existence problem, and we can get the corresponding complexities by replacing NP in Proposition 4 with coNP. Then, we can apply the same technique of blocking undefined used in the proof of Proposition 4 to show the hardness for the three-valued case. Again, the complexity result for deciding the entailment relation {a mathematical formula}⊨MKNF3 (see Definition 3) between hybrid MKNF knowledge bases and ground literals is new. It is interesting to see that our characterization of three-valued MKNF models in terms of stable partitions and alternating fixpoint construction yields a uniform mechanism for establishing upper bounds on the reasoning complexities for semantics based on various subsets of MKNF models. It is also interesting to note that, unlike three-valued semantics for normal logic programs, where the intersection of all three-valued models equals the well-founded model, here even deciding the existence of a three-valued MKNF model is an NP-hard problem. This is true even for MKNF-consistent, or MKNF-strongly consistent, hybrid MKNF knowledge bases.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>