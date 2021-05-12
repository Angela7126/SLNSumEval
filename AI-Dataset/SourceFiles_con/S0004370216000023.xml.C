<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Construction of system of spheres-based transitively relational partial meet multiple contractions: An impossibility result.
   </title>
   <abstract>
    In this paper we show that, contrary to what is the case in what concerns contractions by a single sentence, there is not a system of spheres-based construction of multiple contractions which generates each and every transitively relational partial meet multiple contraction. Before proving the general result, we consider the class of system of spheres-based multiple contractions introduced in [17], [5] and show that this class neither subsumes nor is subsumed by the class of transitively relational partial meet multiple contractions. Furthermore, we propose two system of spheres-based constructions of multiple contractions which generate (only) transitively relational partial meet multiple contractions. Therefore we can conclude that, although it is impossible to obtain a system of spheres-based definition of all the transitively relational partial meet multiple contractions, there are classes of system of spheres-based multiple contractions which are subsumed by the class of transitively relational partial meet multiple contractions.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In the belief revision literature the partial meet contraction, introduced in the seminal paper [1], constitutes the standard model of belief contraction functions. The main purpose of such framework — which is commonly known as AGM contraction — is modelling the dynamics of the set of beliefs of an agent. More precisely, the AGM model essentially provides a definition for a class of contraction functions that receive a belief set — a logically closed set of sentences — and a sentence, and return a belief set which is a subset of the original one that does not contain the received sentence. A possible worlds semantics for partial meet contractions (i.e. a characterization of those functions in terms of possible worlds) was proposed in [8], [12]. Furthermore, based on such semantics, Grove [8] presented a way of defining contraction function by means of a system of spheres — the so-called system of spheres-based contractions. In that same paper it was shown that such class of functions coincides with the class of transitively relational partial meet contractions, a special (proper) subclass of partial meet contractions which was also introduced in [1].
     </paragraph>
     <paragraph>
      A natural generalization of the above mentioned contraction functions is to allow the epistemic input to be a set of sentences rather than a single sentence. In this case, the new belief set is a subset of the original belief set that does not contain the set of sentences given as input. In [7], Fuhrmann and Hansson remarked that two kinds of such functions may be considered, namely, on the one hand, package contractions which are operations that account for the removal of all the sentences of a given set from the original belief set and, on the other hand, choice contractions which are functions that, receiving as input a belief set and a set of sentences, return as output a belief set which is contained in the input belief set and does not contain at least one of the sentences of the received set. In that same paper, it was shown that when the set to be contracted is finite, the choice contraction can be reduced to a contraction by a single sentence (namely by the conjunction of all the elements from that set). Since in this paper we study only contractions by finite sets of sentences, we will only consider package contractions, which from now on we shall call multiple contractions. We shall often use the expression singleton contraction to refer to an operation of contraction by a single sentence.
     </paragraph>
     <paragraph>
      Multiple contraction is an important type of belief change that has been studied extensively in the literature since the early '90s [14], [7], [23], [16], [18], [5], [6], [19]. Nowadays its significance has increased even further, partially due to the emergence of intelligent agents (softbots, robots, etc.) which typically receive input from more than one source simultaneously (for example, through several sensors). We note that such scenarios are outside the scope of classical belief change operators that can only handle changes by a single input at a time.
     </paragraph>
     <paragraph>
      The generalization of partial meet singleton contractions was originally presented in [9], [10] where the class of partial meet multiple contractions was introduced. Afterwards, in [17], [18] the possible worlds semantics for such functions was provided (which can be seen as a generalization to the multiple contraction level of the possible worlds semantics for partial meet singleton contraction). In [17], [5] the class of spheres filtration-based multiple contractions was presented,{sup:1} which is a generalization to the multiple contraction case of Grove's class of system of spheres-based singleton contractions. Later, in [6], [19] three different axiomatic characterizations for this class of multiple contractions were presented.
     </paragraph>
     <paragraph>
      Furthermore, in [17], [5] it was shown that every spheres filtration-based multiple contraction is a partial meet multiple contraction. However, in order to verify whether there is a complete analogy between the proposed class of spheres filtration-based multiple contractions and Grove's class of system of spheres-based (singleton) contractions it remains to analyse if the class of spheres filtration-based multiple contractions coincides with the class of transitively relational partial meet multiple contractions (as it is the case regarding their singleton contraction counterparts).
     </paragraph>
     <paragraph>
      In this paper we will show that this does not hold and, more generally, we will prove that it is in fact impossible to obtain a system of spheres-based definition of multiple contraction functions which encompasses all the transitively relational partial meet multiple contractions.
     </paragraph>
     <paragraph>
      More precisely, we will start by showing that the class of spheres filtration-based multiple contractions (proposed in [17], [5]) neither contains nor is contained in the class of transitively relational partial meet multiple contractions. This conclusion naturally leads to question if there is a (different) system of spheres-based definition of multiple contractions which generates precisely the class of transitively relational partial meet multiple contractions or at least a class of functions which is contained in it. We shall address this issue as follows. First we will prove that it is not possible to construct all the transitively relational partial meet multiple contractions by means of a system of spheres-based method. Afterwards we will present two system of spheres-based methods for constructing multiple contractions and show that both those methods give rise (only) to transitively relational partial meet multiple contractions.
     </paragraph>
     <paragraph>
      The paper is organized as follows: In Section 2 we recall all the background needed for the rest of the paper. In Section 3 we show, by means of two counterexamples that neither all spheres filtration-based multiple contractions are transitively relational partial meet multiple contractions nor the converse holds. Afterwards, in Section 4 we show that, in general, using a system of spheres-based approach it is not possible to obtain all the transitively relational partial meet multiple contractions. Then, in Section 5 we propose two system of spheres-based definitions of partial meet multiple contraction functions, which give rise (only) to transitively relational partial meet multiple contractions. Subsequently, in Section 6 we briefly describe some works that can be found in the literature and whose topics are closely related to the one of the present paper. Finally, in Section 7 we summarize the main contributions of the paper and identify some open questions related to the topic of this paper.
     </paragraph>
     <section label="1.1">
      <section-title>
       Basic notations and conventions
      </section-title>
      <paragraph>
       We will assume a language {a mathematical formula}L that is built from a finite set of propositional symbols and the Boolean connectives ¬, ∧, ∨, → and ↔. We shall make use of a consequence operation Cn that takes sets of sentences to sets of sentences and which satisfies the standard Tarskian properties, namely inclusion, monotony and iteration. Furthermore we will assume that Cn satisfies supraclassicality, compactness and deduction. We will sometimes use {a mathematical formula}Cn(α) for {a mathematical formula}Cn({α}), {a mathematical formula}A⊢α for {a mathematical formula}α∈Cn(A), ⊢α for {a mathematical formula}α∈Cn(∅), {a mathematical formula}A⊬α for {a mathematical formula}α∉Cn(A), ⊬α for {a mathematical formula}α∉Cn(∅). The letters {a mathematical formula}α,αi,β,… (except for γ) will be used to denote sentences. ⊤ stands for an arbitrary tautology and ⊥ for an arbitrary contradiction. {a mathematical formula}A,Ai,B,… shall denote sets of sentences of {a mathematical formula}L. K is reserved to represent a set of sentences that is closed under logical consequence (i.e. {a mathematical formula}K=Cn(K)) — such a set is called a belief set or theory. We shall denote the set of all theories of {a mathematical formula}L by {a mathematical formula}TL and the set of all consistent complete theories (i.e. maximal consistent subsets) of {a mathematical formula}L by {a mathematical formula}ML. We will use the expression possible world (or just world) to designate an element of {a mathematical formula}ML. Given a possible world W, we shall denote by ⋀W the conjunction of all literal in W. {a mathematical formula}M,Ni,W,… (except for {a mathematical formula}L and {a mathematical formula}P), shall be used to denote subsets of {a mathematical formula}ML. Such sets are called propositions. Given a set of sentences R, the set consisting of all the possible worlds that contain R is denoted by {a mathematical formula}‖R‖. The elements of {a mathematical formula}‖R‖ are the R-worlds. {a mathematical formula}‖φ‖ is an abbreviation of {a mathematical formula}‖{φ}‖ and the elements of {a mathematical formula}‖φ‖ are the φ-worlds. To any set of possible worlds {a mathematical formula}V we associate a belief set {a mathematical formula}Th(V) given by {a mathematical formula}Th(V)=⋂V — under the convention that {a mathematical formula}⋂∅=L. {a mathematical formula}M,Ni,W,… shall be used to denote subsets of {a mathematical formula}P(ML).
      </paragraph>
      <paragraph>
       Now we introduce the following useful definitions and notations.
      </paragraph>
      <paragraph label="Definition 1.1">
       Let {a mathematical formula}W be a (possibly empty) collection of sets of worlds. A hitting set for {a mathematical formula}W is any subset {a mathematical formula}Q of {a mathematical formula}⋃W that intersects every element of {a mathematical formula}W. {a mathematical formula}Q is a minimal hitting set for {a mathematical formula}W if no other hitting set for {a mathematical formula}W is a proper subset of {a mathematical formula}Q. The set of all minimal hitting sets for {a mathematical formula}W is denoted by {a mathematical formula}H(W).
      </paragraph>
      <paragraph label="Notation 1.2">
       For any set of sentences A, we denote by {a mathematical formula}〈A〉 the following collection of sets of worlds:{a mathematical formula}
      </paragraph>
      <paragraph>
       In what follows the above introduced notations shall be essentially used in order to refer to the set {a mathematical formula}H(〈B∩K〉),{sup:2} where K is a belief set and B is a set of sentences. This set is formed by (all) the minimal hitting sets for the set {a mathematical formula}{‖¬αi‖:αi∈B∩K} (i.e. the set formed by the sets of {a mathematical formula}¬αi-worlds, for (all) sentences {a mathematical formula}αi∈B∩K). For convenience we present here the following explicit definition of that set:
      </paragraph>
      <paragraph label="Definition 1.3">
       (See [17], [18].) Let K be a belief set and B be a set of sentences. The set {a mathematical formula}H(〈B∩K〉) is the subset of {a mathematical formula}P(⋃{‖¬αi‖:αi∈B∩K}) such that {a mathematical formula}W∈H(〈B∩K〉) if and only if:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}W∩‖¬αi‖≠∅, for all {a mathematical formula}αi∈B∩K.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}W′⊂W then there is some {a mathematical formula}αj∈B∩K such that {a mathematical formula}W′∩‖¬αj‖=∅.
       </list-item>
      </list>
      <paragraph>
       The following example clarifies the concept introduced in the above definition.
      </paragraph>
      <paragraph label="Example 1.4">
       Let {a mathematical formula}L be the propositional language that is built from the two propositional symbols p and q. Define the worlds {a mathematical formula}W0, {a mathematical formula}W1, {a mathematical formula}W2 and {a mathematical formula}W3 as follows:{a mathematical formula}Let K be the theory {a mathematical formula}K=W0, consider the sentences {a mathematical formula}α=q, {a mathematical formula}β=p and {a mathematical formula}δ=p∨¬q and set {a mathematical formula}B={α,β,δ}.In these circumstances, {a mathematical formula}α,β,δ∈K and {a mathematical formula}‖¬α‖={W1,W2}, {a mathematical formula}‖¬β‖={W2,W3} and {a mathematical formula}‖¬δ‖={W3}.Therefore the set {a mathematical formula}H(〈B∩K〉) is composed by all the subsets of {a mathematical formula}{W1,W2,W3} which contain one element of each one of the sets {a mathematical formula}‖¬α‖, {a mathematical formula}‖¬β‖ and {a mathematical formula}‖¬δ‖ and whose proper subsets do not fulfil that requirement. Hence, it holds that{a mathematical formula}
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      In this section we recall the main definitions and results which we shall need in the remaining of the paper.
     </paragraph>
     <section label="2.1">
      <section-title>
       Singleton contraction
      </section-title>
      <paragraph>
       In what follows we recall two of the most well known models of singleton contraction (i.e. contraction of a belief set K by a single sentence α).
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Partial meet contractions
       </section-title>
       <paragraph>
        A Partial Meet Contraction function [3], [1] is built upon a selection from the maximal subsets of K that do not imply the sentence to be contracted. In what follows we present the formal definition of such functions.
       </paragraph>
       <paragraph>
        We start by recalling the basic concepts necessary for the definition of the partial meet contractions introduced in [1]. Given a belief set K and a set of sentences B, the remainder set of K by B is the set of maximal subsets of K that do not imply any element of B and is denoted by {a mathematical formula}K⊥B. Its elements are the remainders (of K, by B) [2]. It is also convenient to notice here that, according to [2, Observation 2.2], since we are assuming that the consequence operation Cn is compact, it holds that {a mathematical formula}K⊥B≠∅ if and only if {a mathematical formula}B∩Cn(∅)=∅.
       </paragraph>
       <paragraph>
        For any sentence α, {a mathematical formula}K⊥α is an abbreviation of {a mathematical formula}K⊥{α} and is called the remainder set of K by α.
       </paragraph>
       <paragraph label="Definition 2.1">
        (See [1].) Let K be a belief set. A selection function for K is a function γ such that for all sentences α: if {a mathematical formula}K⊥α≠∅ then {a mathematical formula}∅≠γ(K⊥α)⊆K⊥α, and if {a mathematical formula}K⊥α=∅, then {a mathematical formula}γ(K⊥α)={K}.An operation − is a partial meet contraction on K if and only if there is a selection function γ for K such that for all sentences α: {a mathematical formula}K−α=⋂γ(K⊥α).
       </paragraph>
       <paragraph>
        In the following definition we present a special class of partial meet contractions.
       </paragraph>
       <paragraph label="Definition 2.2">
        (See [1].) A selection function γ for a belief set K is transitively relational over K if and only if there is a reflexive transitive relation ⊑ over {a mathematical formula}⋃ε∈LK⊥ε such that for all {a mathematical formula}α∈L∖Cn(∅):{a mathematical formula}The above formula is called the marking-off identity and ⊑ is the marking-off relation.A partial meet contraction function − is transitively relational over K if and only if it is determined by some selection function that is so.
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        Possible worlds semantics for partial meet contractions
       </section-title>
       <paragraph>
        In this subsubsection we present the possible worlds semantics for partial meet multiple contraction that was presented in [12]. We start by recalling the concept of propositional selection function.
       </paragraph>
       <paragraph label="Definition 2.3">
        (See [12].) Let {a mathematical formula}M be a proposition. A propositional selection function for {a mathematical formula}M is a function f such that for all sentences α: (1) {a mathematical formula}f(‖α‖)⊆‖α‖, (2) If {a mathematical formula}‖α‖≠∅ then {a mathematical formula}f(‖α‖)≠∅ and (3) If {a mathematical formula}M∩‖α‖≠∅, then {a mathematical formula}f(‖α‖)=M∩‖α‖.
       </paragraph>
       <paragraph>
        Now we are in a position to present the characterization of the partial meet contractions in terms of possible worlds.
       </paragraph>
       <paragraph label="Observation 2.4">
        (See[8], [12].) LetKbe a belief set. An operation − onKis a partial meet contraction if and only if there is a propositional selection function f for{a mathematical formula}‖K‖such that for all sentences α:{a mathematical formula}K−α=Th(‖K‖∪f(‖¬α‖)).
       </paragraph>
      </section>
      <section label="2.1.3">
       <section-title>
        System of spheres-based contractions
       </section-title>
       <paragraph>
        Now we recall the definitions of a system of spheres and of the system of spheres-based contractions presented in [8].
       </paragraph>
       <paragraph label="Definition 2.5">
        (See [8].) Let {a mathematical formula}X be a subset of {a mathematical formula}ML. A system of spheres (abrev. S.S.) centred on {a mathematical formula}X is a collection {a mathematical formula}S of subsets of {a mathematical formula}ML, i.e. {a mathematical formula}S⊆P(ML), that satisfies the following conditions:
        <list>
         {a mathematical formula}S is totally ordered with respect to set inclusion; that is, if {a mathematical formula}U,V∈S, then {a mathematical formula}U⊆V or {a mathematical formula}V⊆U.{a mathematical formula}X∈S, and if {a mathematical formula}U∈S then {a mathematical formula}X⊆U.{a mathematical formula}ML∈S (and so it is the largest element of {a mathematical formula}S).For every {a mathematical formula}φ∈L, if there is any element in {a mathematical formula}S intersecting {a mathematical formula}‖φ‖ then there is also a smallest element in {a mathematical formula}S intersecting {a mathematical formula}‖φ‖.{sup:3}The elements of
        </list>
        <paragraph>
         {a mathematical formula}S are called spheres. For any consistent sentence {a mathematical formula}φ∈L, the smallest sphere in {a mathematical formula}S intersecting {a mathematical formula}‖φ‖ is denoted by {a mathematical formula}Sφ and {a mathematical formula}fS(φ) denotes the set consisting of the φ-worlds closest to {a mathematical formula}X, i.e.,{a mathematical formula}
        </paragraph>
       </paragraph>
       <paragraph label="Definition 2.6">
        (See [8].) Let K be a belief set and {a mathematical formula}S be a system of spheres centred on {a mathematical formula}‖K‖. The {a mathematical formula}S-based contraction onK is the contraction operation {a mathematical formula}−S defined, for any {a mathematical formula}φ∈L, by:{a mathematical formula}An operation − on K is a system of spheres-based contraction onK if and only if there is a system of spheres {a mathematical formula}S centred on {a mathematical formula}‖K‖, such that, for all sentences {a mathematical formula}φ∈L, {a mathematical formula}K−φ=K−Sφ.
       </paragraph>
       <paragraph>
        To close this subsection we remind that Grove [8] has shown that the class of system of spheres-based contractions coincides with the class of transitively relational partial meet contractions.
       </paragraph>
       <paragraph label="Observation 2.7">
        (See[8].) LetKbe a belief set and − be a (singleton) contraction function onK. Then − is a system of spheres-based contraction if and only if it is a transitively relational partial meet contraction.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Multiple contraction
      </section-title>
      <paragraph>
       Below we recall two models of multiple contraction (i.e. contraction of a belief set K by a set of sentences B) which result of generalizing the models presented in the previous subsection.
      </paragraph>
      <section label="2.2.1">
       <section-title>
        Partial meet multiple contractions
       </section-title>
       <paragraph>
        The partial meet multiple contractions are a generalization of the partial meet contraction functions to the case of contractions by (possibly non-singleton) sets.
       </paragraph>
       <paragraph label="Definition 2.8">
        (See [9], [7].) Let K be a belief set. A package selection function for K is a function γ such that for all sets of sentences B: if {a mathematical formula}K⊥B≠∅, then {a mathematical formula}∅≠γ(K⊥B)⊆K⊥B, and if {a mathematical formula}K⊥B=∅ then {a mathematical formula}γ(K⊥B)={K}.An operation ÷ is a partial meet multiple contraction (abrev. PMMC) on K if and only if there is some package selection function γ for K, such that for all sets of sentences B: {a mathematical formula}K÷B=⋂γ(K⊥B).
       </paragraph>
       <paragraph>
        We close this subsubsection with the following definition which introduces the class of transitively relational partial meet multiple contraction that is a the natural generalization to the case of multiple contraction of the class of functions presented in Definition 2.2.
       </paragraph>
       <paragraph label="Definition 2.9">
        Let K be a belief set. An operation ÷ is a transitively relational partial meet multiple contraction (abrev. TRPMMC) on K if and only if there is a transitive relation ⊑ on the set {a mathematical formula}⋃B⊆LK⊥B such that, for all sets of sentences B, {a mathematical formula}K÷B=⋂γ(K⊥B), where γ is a (transitively) relational package selection function defined by {a mathematical formula}γ(K⊥B)={K} if {a mathematical formula}B∩Cn(∅)≠∅, and by the marking-off identity:{a mathematical formula} if {a mathematical formula}B∩Cn(∅)=∅.
       </paragraph>
      </section>
      <section label="2.2.2">
       <section-title>
        Possible worlds semantics for partial meet multiple contractions
       </section-title>
       <paragraph>
        The possible worlds semantics for partial meet multiple contraction was presented in [17], [18]. In this subsubsection we recall the concepts and results (as well as some immediate consequences of some results) of the mentioned references which we will need further ahead.
       </paragraph>
       <paragraph>
        We start by recalling the following result concerning the composition of the set {a mathematical formula}H(〈B∩K〉) (cf. Definition 1.3).
       </paragraph>
       <paragraph label="Observation 2.10">
        (See[17], [18].) LetKbe a belief set and B be a set of sentences. Then the following statements hold:
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}B∩Cn(∅)≠∅if and only if{a mathematical formula}H(〈B∩K〉)=∅.
        </list-item>
        <list-item label="2.">
         {a mathematical formula}B∩K=∅if and only if{a mathematical formula}H(〈B∩K〉)={∅}.
        </list-item>
        <list-item label="3.">
         {a mathematical formula}B∩Cn(∅)=∅and{a mathematical formula}B∩K≠∅if and only if{a mathematical formula}H(〈B∩K〉)≠∅and{a mathematical formula}∅∉H(〈B∩K〉).
        </list-item>
       </list>
       <paragraph>
        The following lemma shall be used further ahead.
       </paragraph>
       <paragraph label="Lemma 2.11">
        (See[17], [18].) LetKbe a belief set, B be a finite set of sentences and{a mathematical formula}Nbe a subset of{a mathematical formula}ML. If{a mathematical formula}N∩‖¬αi‖≠∅, for all{a mathematical formula}αi∈B∩K, then there is some set{a mathematical formula}N′such that{a mathematical formula}N′⊆Nand{a mathematical formula}N′∈H(〈B∩K〉).
       </paragraph>
       <paragraph>
        Now we present the relation between the sets {a mathematical formula}H(〈B∩K〉) and {a mathematical formula}K⊥B.
       </paragraph>
       <paragraph label="Observation 2.12">
        (See[17], [18].) LetKbe a belief set and B be a finite set of sentences. Then{a mathematical formula}X∈K⊥Bif and only if there is some{a mathematical formula}W∈H(〈B∩K〉)such that{a mathematical formula}X=Th(‖K‖∪W).
       </paragraph>
       <paragraph label="Corollary 2.13">
        LetKbe a belief set and B be a set of sentences. Then the function{a mathematical formula}is a bijection.
       </paragraph>
       <paragraph label="Proof">
        It follows immediately from Observation 2.12 that t is a (well defined) surjective function. On the other hand, since we are working under the assumption that the underlying language {a mathematical formula}L is based on a finite alphabet, it holds, moreover, that t is injective and, therefore, it is a bijection.  □
       </paragraph>
       <paragraph>
        Next we recall the concept of propositional package selection function and a couple of results which involve that concept, and which will be necessary further ahead.
       </paragraph>
       <paragraph label="Definition 2.14">
        Let K be a belief set. A propositional package selection function for {a mathematical formula}‖K‖ is a function f such that for all sets of sentences B: (1) {a mathematical formula}f(H(〈B∩K〉))⊆H(〈B∩K〉), and (2) if {a mathematical formula}H(〈B∩K〉)≠∅ then {a mathematical formula}f(H(〈B∩K〉))≠∅.
       </paragraph>
       <paragraph label="Proof">
        (See[17], [18].) If ÷ is a partial meet multiple contraction onK, i.e. ÷ is such that for all finite sets B,{a mathematical formula}K÷B=⋂γ(K⊥B), where γ is a package selection function forK, then the function f defined for all sets B by{a mathematical formula}f(H(〈B∩K〉))={W∈H(〈B∩K〉):Th(‖K‖∪W)∈γ(K⊥B)}{sup:4}is a propositional package selection function for{a mathematical formula}‖K‖such that{a mathematical formula}K÷B=Th(‖K‖∪(⋃f(H(〈B∩K〉)))), for all sets B.See the left-to-right part of the Proof of [18, Theorem 3.14].  □
       </paragraph>
       <paragraph label="Proof">
        (See[17], [18].) If ÷ is an operation such that, for all sets B,{a mathematical formula}K÷B=Th(‖K‖∪(⋃f(H(〈B∩K〉)))), where f is a propositional package selection function for{a mathematical formula}‖K‖, then the function γ defined by{a mathematical formula}γ(K⊥B)={K}if{a mathematical formula}K⊥B=∅, and{a mathematical formula}γ(K⊥B)={Th(‖K‖∪W):W∈f(H(〈B∩K〉))}if{a mathematical formula}K⊥B≠∅is a package selection function forK, such that{a mathematical formula}K÷B=⋂γ(K⊥B), for all sets B.See the right-to-left part of the Proof of [18, Theorem 3.14].  □
       </paragraph>
       <paragraph>
        Finally, the following observation, which is an immediate consequence of the two above lemmas, provides the characterization of partial meet multiple contractions in terms of possible worlds:
       </paragraph>
       <paragraph label="Observation 2.17">
        (See[17], [18].) LetKbe a belief set. An operation ÷ is a partial meet multiple contraction onKif and only if there exists a propositional package selection function f for{a mathematical formula}‖K‖such that, for any set of sentences B:{a mathematical formula}
       </paragraph>
      </section>
      <section label="2.2.3">
       <section-title>
        Spheres filtration-based multiple contractions
       </section-title>
       <paragraph>
        In this subsection we present the definition of spheres filtration-based multiple contraction{sup:5} which was introduced in [17], [5] and is a generalization to the case of multiple contraction of Grove's definition of system of spheres-based (singleton) contraction.
       </paragraph>
       <paragraph>
        Such definition makes use of the concept of {a mathematical formula}Sfiltration of a set of sentences B,{sup:6} where {a mathematical formula}S is a system of spheres centred on {a mathematical formula}‖K‖, for some given belief set K:
       </paragraph>
       <paragraph label="Definition 2.18">
        (See [17], [5].) Let K be a belief set and {a mathematical formula}S be a system of spheres centred on {a mathematical formula}‖K‖.Consider a set of sentences {a mathematical formula}B={α1,α2,…,αn}⊆L such that {a mathematical formula}B∖Cn(∅)≠∅.Denote by {a mathematical formula}C1,…,Cm the (different) equivalence classes in the quotient set of {a mathematical formula}(B∖Cn(∅)) by ∽, i.e. {a mathematical formula}{C1,…,Cm}=(B∖Cn(∅))/∽, where ∽ is the equivalence relation on {a mathematical formula}B∖Cn(∅) defined by:{a mathematical formula}Moreover, assume that the equivalence classes {a mathematical formula}C1,…,Cm are ordered according to the following condition:{a mathematical formula}Now consider the following list of subsets of B:{a mathematical formula}Moreover, if {a mathematical formula}m&gt;1 for all {a mathematical formula}l∈{2,…,m}, let {a mathematical formula}Cl′, {a mathematical formula}Cl″ and {a mathematical formula}Bl be the sets defined by:{a mathematical formula}The set {a mathematical formula}BS=Bm is the {a mathematical formula}Sfiltration of B.If D is a set of sentences such that {a mathematical formula}D⊆Cn(∅), then the {a mathematical formula}Sfiltration of D is the empty set and is denoted by {a mathematical formula}DS, i.e. {a mathematical formula}DS=∅.
       </paragraph>
       <paragraph label="Definition 2.19">
        (See [17], [5].) Let K be a belief set and {a mathematical formula}S be a system of spheres centred on {a mathematical formula}‖K‖. The {a mathematical formula}Sfiltration-based multiple contraction onK is the multiple contraction function {a mathematical formula}÷S defined by:{a mathematical formula} for any set of sentences B and where {a mathematical formula}BS is the {a mathematical formula}S filtration of B. An operator ÷ on K is a spheres filtration-based multiple contraction onK (abrev. S.F.-bMC) if and only if there is a system of spheres {a mathematical formula}S centred on {a mathematical formula}‖K‖, such that {a mathematical formula}K÷B=K÷SB, for any set of sentences B.
       </paragraph>
       <paragraph>
        Next, in order to clarify the two definitions above — i.e. the concepts of {a mathematical formula}S filtration and of spheres filtration-based multiple contraction —, we present an example.
       </paragraph>
       <paragraph label="Example 2.20">
        Let {a mathematical formula}L be the propositional language that is built from the three propositional symbols p, q and r. Define the worlds {a mathematical formula}W0,…,W7 as follows:{a mathematical formula}Set {a mathematical formula}K=W0 and consider the sentences {a mathematical formula}α=¬(⋀W3), {a mathematical formula}β=¬(⋀W1∨⋀W2), {a mathematical formula}δ=¬(⋀W2∨⋀W3) and {a mathematical formula}ϵ=¬(⋀W3∨⋀W4). Furthermore, let {a mathematical formula}S be the following system of spheres centred on {a mathematical formula}‖K‖:{a mathematical formula}Fig. 1 contains a possible graphical representation of the system of spheres {a mathematical formula}S, where the sets {a mathematical formula}‖¬α‖={W3}, {a mathematical formula}‖¬β‖={W1,W2}, {a mathematical formula}‖¬δ‖={W2,W3} and {a mathematical formula}‖¬ϵ‖={W3,W4} are highlighted.Let {a mathematical formula}÷S be the {a mathematical formula}S filtration-based multiple contraction, and consider the sets {a mathematical formula}A={α,β} and {a mathematical formula}B={β,δ,ϵ}. In what follows we illustrate how to obtain the sets {a mathematical formula}K÷SA and {a mathematical formula}K÷SB.We start by obtaining the former. First of all we need to identify the set {a mathematical formula}AS, i.e. the {a mathematical formula}S filtration of A.According to the process described in Definition 2.18 and based on the information exposed in Fig. 1 we obtain that:
        <list>
         Since {a mathematical formula}S¬β⊂S¬α, the set {a mathematical formula}(A∖Cn(∅))/∽ is composed of the following two equivalence classes: {a mathematical formula}C1={α} and {a mathematical formula}C2={β} (and, therefore, {a mathematical formula}m=2).{a mathematical formula}A1=C1″=C1′=C1={α}.{a mathematical formula}C2′=C2={β} (notice that {a mathematical formula}fS(¬α)⊄‖¬β‖).{a mathematical formula}C2″=C2′={β}.{a mathematical formula}AS=A2=A1∪C2″={α,β}.Thus, according to
        </list>
        <paragraph>
         Definition 2.19, we have that{a mathematical formula}Next we find {a mathematical formula}BS — the {a mathematical formula}S filtration of the set B — and we obtain the set {a mathematical formula}K÷SB. So, proceeding as above, we obtain that:
        </paragraph>
        <list>
         <list-item label="•">
          Since {a mathematical formula}S¬β⊂S¬δ⊂S¬ϵ, the set {a mathematical formula}(B∖Cn(∅))/∽ is composed of the following three equivalence classes: {a mathematical formula}C1={ϵ}, {a mathematical formula}C2={δ} and {a mathematical formula}C3={β} (and, therefore, {a mathematical formula}m=3).
         </list-item>
         <list-item label="•">
          {a mathematical formula}B1=C1″=C1′=C1={ϵ}.
         </list-item>
         <list-item label="•">
          {a mathematical formula}C2′=C2={δ} (notice that {a mathematical formula}fS(¬ϵ)⊄‖¬δ‖).
         </list-item>
         <list-item label="•">
          {a mathematical formula}C2″=C2′={δ}.
         </list-item>
         <list-item label="•">
          {a mathematical formula}B2=B1∪C2″={ϵ,δ}.
         </list-item>
         <list-item label="•">
          {a mathematical formula}C3′=C3∖{β}=∅ (notice that {a mathematical formula}β∉C3′ because {a mathematical formula}fS(¬δ)⊂‖¬β‖).
         </list-item>
         <list-item label="•">
          {a mathematical formula}C3″=C3′=∅.
         </list-item>
         <list-item label="•">
          {a mathematical formula}BS=B3=B2∪C3″={ϵ,δ}.
         </list-item>
        </list>
        <paragraph>
         Hence, according to Definition 2.19, we have that{a mathematical formula}
        </paragraph>
       </paragraph>
       <paragraph>
        To close this subsection we remark that three alternative axiomatic characterizations for the class of spheres filtration-based multiple contraction can be found in [6], [19]. Moreover, we recall that in [17], [5] it was shown that all spheres filtration-based multiple contractions are partial meet multiple contractions, but the interrelation between the class of spheres filtration-based multiple contractions and the class of transitively relational partial meet multiple contractions has not been studied there.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Spheres filtration-based multiple contractions vs. TRPMMCs
     </section-title>
     <paragraph>
      In this section we show that not all spheres filtration-based multiple contractions are TRPMMCs and that, vice versa, not all TRPMMCs are spheres filtration-based multiple contractions.
     </paragraph>
     <paragraph>
      We start by showing, in the following counterexample, that the spheres filtration-based multiple contraction function considered in Example 2.20 is different from any transitively relational partial meet multiple contraction on K.
     </paragraph>
     <paragraph label="Counterexample 3.1">
      Let {a mathematical formula}L,W0,…,W7,K,α,β,δ,ϵ and {a mathematical formula}S be as stated in Example 2.20 and recall that Fig. 1 contains a possible graphical representation of the system of spheres {a mathematical formula}S, where the sets {a mathematical formula}‖¬α‖={W3}, {a mathematical formula}‖¬β‖={W1,W2}, {a mathematical formula}‖¬δ‖={W2,W3} and {a mathematical formula}‖¬ϵ‖={W3,W4} are highlighted.Let {a mathematical formula}÷S be the {a mathematical formula}S filtration-based multiple contraction. In what follows we show that {a mathematical formula}÷S is not a TRPMMC. Assume towards contradiction that there is a transitive binary relation ⊑ on the K-remainders, i.e. on {a mathematical formula}⋃B⊆LK⊥B, such that {a mathematical formula}÷S coincides with the TRPMMC which is based on ⊑. Consider the set {a mathematical formula}A={α,β}.As we have seen in Example 2.20, it holds that {a mathematical formula}K÷SA=Th({W0,W1,W3}). Moreover, having in mind Observation 2.12, it is not hard to see that the only remainders in {a mathematical formula}K⊥A are {a mathematical formula}Th({W0,W1,W3}) and {a mathematical formula}Th({W0,W2,W3}). Thus, the binary relation ⊑ must be such that:{a mathematical formula}Similarly, let B be the set of sentences {a mathematical formula}{β,δ,ϵ}.It was shown in Example 2.20 that {a mathematical formula}K÷SB=Th({W0,W2,W3,W4}). Moreover we have{a mathematical formula} Thus, the binary relation ⊑ must be such that{a mathematical formula}Since this contradicts (1) we can conclude that {a mathematical formula}÷S is not a transitively relational partial meet multiple contraction, as we wished to show. □
     </paragraph>
     <paragraph>
      The above counterexample shows that not all spheres filtration-based multiple contractions are TRPMMCs.
     </paragraph>
     <paragraph>
      Next, by means of another counterexample, we show that the converse inclusion does not hold either, i.e. that not all TRPMMCs are spheres filtration-based multiple contractions. Thus, in the following counterexample we present a transitively relational partial meet multiple contraction function ÷ on a belief set K which is different from the {a mathematical formula}S filtration-based multiple contraction {a mathematical formula}÷S, for any system of spheres {a mathematical formula}S centred on {a mathematical formula}‖K‖.
     </paragraph>
     <paragraph label="Counterexample 3.2">
      Let {a mathematical formula}L, {a mathematical formula}W0, {a mathematical formula}W1, {a mathematical formula}W2 and {a mathematical formula}W3 be as stated in Example 1.4.Define K to be the theory {a mathematical formula}K=W0 and let ÷ be the transitively relational partial meet multiple contraction that is based on the preorder ⊑ on {a mathematical formula}⋃B⊆LK⊥B — the set of all remainders of K — defined as follows (where, as usual, ⊏ denotes the strict part of ⊑):{a mathematical formula}Now consider the sentences {a mathematical formula}α=q, {a mathematical formula}β=p and {a mathematical formula}δ=p∨¬q. Hence, it holds that {a mathematical formula}‖¬α‖={W1,W2}, {a mathematical formula}‖¬β‖={W2,W3} and {a mathematical formula}‖¬δ‖={W3}. Thus, having in mind Observation 2.12, it follows that{a mathematical formula}{a mathematical formula}{a mathematical formula}Finally, according to the definition of ⊑, it follows that:{a mathematical formula}{a mathematical formula}{a mathematical formula}Now assume towards contradiction that there is a system of spheres {a mathematical formula}S centred on {a mathematical formula}‖K‖={W0} such that ÷ is the {a mathematical formula}S filtration-based multiple contraction. Then it follows from (2) and (4) that {a mathematical formula}S⋀W1⊂S⋀W2. Similarly, from (3) and (5) it follows that {a mathematical formula}S⋀W2⊂S⋀W3. Hence,{a mathematical formula}Fig. 2 contains a possible graphical representation of the system of spheres {a mathematical formula}S, where the sets {a mathematical formula}‖¬α‖ and {a mathematical formula}‖¬δ‖ are highlighted.However, the {a mathematical formula}S filtration-based multiple contraction {a mathematical formula}÷S is such that {a mathematical formula}K÷S{α,δ}=Th({W0,W1,W3}) and, therefore, according to (6), ÷ differs from {a mathematical formula}÷S. Thus we can conclude that ÷ is not a spheres filtration-based multiple contraction. □
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      The impossibility of constructing (all the) TRPMMCs by means of systems of spheres
     </section-title>
     <paragraph>
      Next we show that not only the construction of spheres filtration-based multiple contractions proposed in [17], [5] fails to generate all TRPMMCs (cf. Counterexample 3.2) but, furthermore, any (other) method for constructing multiple contractions which is based on systems of spheres shall equally fail to fulfil such goal.
     </paragraph>
     <paragraph>
      Indeed, apart from confirming that not all TRPMMCs are S.F.-bMCs, Counterexample 3.2 allows us to conclude that there is no way of defining multiple contractions from systems of spheres which is such that the class of all the thus constructed functions subsumes the class of TRPMMCs.
     </paragraph>
     <paragraph>
      The reason why there is not a method of constructing multiple contraction functions which is based on systems of spheres and which gives rise to the whole class of TRPMMCs can be informally exposed as follows: Let K be a belief set and ÷ and {a mathematical formula}÷′ be two multiple contractions on K induced (by the same method) from the systems of spheres {a mathematical formula}S and {a mathematical formula}S′, respectively. Assume additionally that ÷ and {a mathematical formula}÷′ are such that for any sentence α of {a mathematical formula}L, {a mathematical formula}K÷{α}=K−Sα and {a mathematical formula}K÷′{α}=K−S′α, where {a mathematical formula}−S is the {a mathematical formula}S-based contraction on K and {a mathematical formula}−S′ is the {a mathematical formula}S′-based contraction on K. It follows that if ÷ and {a mathematical formula}÷′ agree on all contractions by singleton sets, then it must be the case that {a mathematical formula}S=S′, and therefore ÷ and {a mathematical formula}÷′ have to agree on contractions by sets of arbitrary size (i.e. {a mathematical formula}K÷A=K÷′A, for any set of sentences A), no matter what the method of producing ÷ and {a mathematical formula}÷′ from {a mathematical formula}S (and {a mathematical formula}S′) might be. On the other hand, there exist partial orders ⊏ and {a mathematical formula}⊏′ on the set of remainders of K, that agree when restricted to remainders of K by singleton sets, but differ otherwise (and, therefore, induce TRPMMCs which are different from each other but, nevertheless, agree on all contractions by singleton sets).
     </paragraph>
     <paragraph>
      In what follows, we clarify the above statement with the help of Counterexample 3.2.
     </paragraph>
     <paragraph>
      So, let {a mathematical formula}L, {a mathematical formula}W0, {a mathematical formula}W1, {a mathematical formula}W2, {a mathematical formula}W3, K, ⊑, ÷, α, β and δ be as described in Counterexample 3.2 and let {a mathematical formula}÷′ be the transitively relational partial meet multiple contraction that is based on the transitive relation {a mathematical formula}⊑′ on the set of all remainders of K (i.e. on {a mathematical formula}⋃B⊆LK⊥B) defined in the following way:{sup:8}{a mathematical formula}
     </paragraph>
     <paragraph>
      In the above conditions we obtain:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Thus, on the one hand, according to (9) and (10) we have that the multiple contraction functions ÷ and {a mathematical formula}÷′ are different from each other. On the other hand, reasoning as we did in the analogous part of Counterexample 3.2 from (7) and (8) we can conclude that if {a mathematical formula}÷′ is a spheres filtration-based multiple contraction then the system of spheres from which it is obtained must be precisely the same system of spheres {a mathematical formula}S that arose in Counterexample 3.2. In other words, we have that, in spite of the fact that the TRPMMCs ÷ and {a mathematical formula}÷′ are different, the two transitive relations ⊑ and {a mathematical formula}⊑′ on which they are (respectively) based induce the same system of spheres {a mathematical formula}S={{W0},{W0,W1},{W0,W1,W2},{W0,W1,W2,W3}}.
     </paragraph>
     <paragraph>
      Now, assume there is a method for constructing all the transitively relational partial meet multiple contractions by means of systems of spheres and let {a mathematical formula}K⊖SA denote the result of contracting the belief set K by (the set of sentences) A using the above exposed system of spheres {a mathematical formula}S and applying such method.{sup:9}
     </paragraph>
     <paragraph>
      It follows that, when considering the result of the multiple contraction of K by {a mathematical formula}{α,δ} we have that one and only one of the following identities holds:
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}K⊖S{α,δ}=Th({W0,W1,W3})
      </list-item>
      <list-item label="(b)">
       {a mathematical formula}K⊖S{α,δ}=Th({W0,W2,W3})
      </list-item>
      <list-item label="(c)">
       {a mathematical formula}K⊖S{α,δ}=Th({W0,W1,W2,W3})
      </list-item>
     </list>
     <paragraph>
      However, the two transitively relational partial meet multiple contractions that we have presented above ÷ and {a mathematical formula}÷′ are such that, on the one hand, they induce the (same) system of spheres {a mathematical formula}S,{sup:10} and, on the other hand, they return different results for the contraction of K by {a mathematical formula}{α,δ} (cf. (9) and (10)).
     </paragraph>
     <paragraph>
      Therefore at most one (and eventually none) of the two TRPMMCs ÷ and {a mathematical formula}÷′ coincides with the multiple contraction function obtained from {a mathematical formula}S by means of the method that we have assumed to exist. Thus, at least one of those two TRPMMCs cannot be obtained by any system of spheres through such method (independently of how it is defined).
     </paragraph>
     <paragraph>
      And from all the above we can conclude that there is not any method for constructing (partial meet) multiple contractions which (simultaneously) is based on systems of spheres and generates each and every transitively relational partial meet multiple contraction. That is, there is not a method for constructing multiple contractions which is based on systems of spheres and is such that for any TRPMMC there is a system of spheres such that the multiple contraction obtained from that system of spheres by means of that method coincides with that TRPMMC. This fact is highlighted in the following observation.
     </paragraph>
     <paragraph label="Observation 4.1">
      There is not a system of spheres-based definition of multiple contractions which generates each and every TRPMMC.
     </paragraph>
     <paragraph>
      In what follows we present a formal proof for the fact that we have exposed above by means of a counterexample. More precisely, below we show that no construction of a multiple contraction which is based on a system of spheres can cover the entire spectrum of transitively relational partial meet multiple contractions. The proof is basically a counting argument: loosely speaking, we prove that there are more transitive binary relations ⊑ on remainders than there are systems of spheres, and moreover, that each such relation ⊑ induces a different multiple contraction.
     </paragraph>
     <paragraph>
      We start by introducing the following notation which shall be used in what follows:
     </paragraph>
     <paragraph label="Notation 4.2">
      We shall denote the set of all remainders of K not including K by {a mathematical formula}KR, i.e. {a mathematical formula}KR=(⋃B⊆LK⊥B)∖K.{sup:11}
     </paragraph>
     <paragraph>
      Now we present some results concerning the interrelation among systems of spheres and preorders on the set of remainders.
     </paragraph>
     <paragraph label="Proof">
      LetKbe a theory such that{a mathematical formula}ML∖‖K‖contains at least two worlds. Then there are more preorders in{a mathematical formula}KR, than there are systems of spheres centred on{a mathematical formula}‖K‖.Let K be a theory and let n be the size of {a mathematical formula}ML∖‖K‖. Furthermore, assume that {a mathematical formula}n&gt;1. We must show that there are more preorders in {a mathematical formula}KR, than there are systems of spheres centred on {a mathematical formula}‖K‖. Given the one-to-one correspondence between systems of spheres centred on {a mathematical formula}‖K‖ and preorders in {a mathematical formula}ML∖‖K‖, it suffices to show that there are less elements in {a mathematical formula}ML∖‖K‖ than there are in {a mathematical formula}KR. If follows from Corollary 2.13 that there is a one-to-one correspondence between {a mathematical formula}KR and non-empty subsets of {a mathematical formula}ML∖‖K‖. Hence there are {a mathematical formula}2n−1 remainders in {a mathematical formula}KR while there are n worlds in {a mathematical formula}ML∖‖K‖. Finally we notice that, since {a mathematical formula}n&gt;1, it holds that {a mathematical formula}2n−1&gt;n, and this concludes the proof.  □
     </paragraph>
     <paragraph label="Proof">
      LetKbe a theory and ⊑,{a mathematical formula}⊑′be two preorders on the remainders ofKsuch that ⊑ and{a mathematical formula}⊑′disagree on their projection on{a mathematical formula}KR. Then the transitively relational partial meet multiple contractions ÷ and{a mathematical formula}÷′induced from ⊑ and{a mathematical formula}⊑′respectively, are different.Since ⊑ and {a mathematical formula}⊑′ disagree on their projection on {a mathematical formula}KR, we can assume without loss of generality that there are two K-remainders H and {a mathematical formula}H′, both different from K, such that {a mathematical formula}H⊑H′ and {a mathematical formula}H⋢′H′. Define {a mathematical formula}R1,…,Rm to be the worlds in {a mathematical formula}(‖H‖∩‖H′‖)∖‖K‖, {a mathematical formula}V1,…,Vp to be the worlds in {a mathematical formula}‖H‖∖‖H′‖, and {a mathematical formula}U1,…,Uq to be the worlds in {a mathematical formula}‖H′‖∖‖H‖. That is, {a mathematical formula}‖H‖=‖K‖∪{R1,…,Rm,V1,…,Vp}, and {a mathematical formula}‖H′‖=‖K‖∪{R1,…,Rm,U1,…,Uq}. Notice that since both H and {a mathematical formula}H′ are different from K and from each other, {a mathematical formula}{V1,…,Vp}≠∅ and {a mathematical formula}{U1,…,Uq}≠∅. Define {a mathematical formula}H×H′ as follows:{a mathematical formula} It is not hard to verify that H and {a mathematical formula}H′ are the only two remainders of K with respect to {a mathematical formula}H×H′; i.e. {a mathematical formula}K⊥(H×H′)={H,H′}. Since {a mathematical formula}H⊑H′, it follows that {a mathematical formula}K÷(H×H′)⊆H′. On the other hand, since {a mathematical formula}H⋢′H′ we derive that {a mathematical formula}K÷′(H×H′)⊈H′. Thus {a mathematical formula}÷≠÷′.  □
     </paragraph>
     <paragraph>
      The following corollary follows immediately from the two previous results:
     </paragraph>
     <paragraph label="Corollary 4.5">
      LetKbe a theory such that{a mathematical formula}ML∖‖K‖contains at least two worlds. Then there are more transitively relational partial meet multiple contractions onK, than there are systems of spheres centred on{a mathematical formula}‖K‖.
     </paragraph>
     <paragraph>
      At this point we must emphasise that it follows from the above theorem that (given a theory K which is such that {a mathematical formula}ML∖‖K‖ contains at least two worlds) independently of how we define it, any class of multiple contractions (on K) defined by means of system of spheres does not subsume the class of transitively relational partial meet multiple contractions (on K). This fact is more formally stated in the following observation:
     </paragraph>
     <paragraph label="Observation 4.6">
      LetKbe a belief set such that the set{a mathematical formula}ML∖‖K‖contains more than one possible world,{a mathematical formula}Sbe an arbitrary system of spheres centred on{a mathematical formula}‖K‖and{a mathematical formula}÷Sbe a multiple contraction onKwhose definition is based on (i.e., depends on){a mathematical formula}S. Then the class of all such contraction function does not contain the class of (all) transitively relational partial meet multiple contractions, i.e.{a mathematical formula}
     </paragraph>
     <paragraph>
      It is also worth highlighting here that the above result exposes a major difference among singleton contractions and multiple contractions. Namely because in what concerns singleton contractions, as we have already mentioned before, the class of system of spheres-based contractions (cf. Definition 2.6) coincides with the class of transitively relational partial meet contractions (cf. Definition 2.2), which means that it is possible to obtain all the transitively relational partial meet (singleton) contractions by means of a system of spheres-based method for constructing singleton contractions. Indeed, moreover, in [8] the proof for the above mentioned fact is based on the explicit presentation of an one-to-one correspondence between the class of systems of spheres centred on {a mathematical formula}‖K‖ and the class of preorders on the remainders of K, i.e. on the set {a mathematical formula}⋃ε∈LK⊥ε, for a given belief set K.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Two methods for constructing (some) TRPMMCs by means of systems of spheres
     </section-title>
     <paragraph>
      The definition of the spheres filtration-based multiple contractions (see Definition 2.19) is quite intricate and, at first sight, unintuitive. On the other hand, as we have clarified by means of Counterexample 3.1, not all spheres filtration-based multiple contractions are TRPMMCs. These two facts are enough to motivate the search for alternative constructions of multiple contractions from systems of spheres. And, in particular, the latter one raises the issue of finding out a way of defining multiple contraction functions from systems of spheres which generates TRPMMCs.
     </paragraph>
     <paragraph>
      Having the above in mind, in Subsection 5.1 we present two ways of constructing multiple contraction functions by means of systems of spheres (alternative to the one used in Definition 2.19) and afterwards, in Subsection 5.2, we investigate the interrelations among those constructions, the spheres filtration-based multiple contractions and the transitively relational partial meet multiple contractions.
     </paragraph>
     <section label="5.1">
      <section-title>
       Two (alternative) system of spheres-based definitions of multiple contraction functions
      </section-title>
      <paragraph>
       In what follows we present some definitions of multiple contraction functions on a belief set K which are based on a system of spheres {a mathematical formula}S centred on {a mathematical formula}‖K‖.
      </paragraph>
      <paragraph>
       In order to be in a position for proposing two alternative ways of defining multiple contraction functions by means of the system of spheres {a mathematical formula}S, we need to start by introducing two binary relations on {a mathematical formula}2ML. We denote those two relations by {a mathematical formula}⊑S1 and {a mathematical formula}⊑S2, and the definitions we propose for each of them are as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}V′⊑S1V iff for all {a mathematical formula}W∈V there is some {a mathematical formula}W′∈V′ such that {a mathematical formula}S∧W⊆S∧W′.
       </list-item>
       <list-item label="•">
        {a mathematical formula}V′⊑S2V iff for all {a mathematical formula}W∈V there is some {a mathematical formula}W′∈V′ such that {a mathematical formula}S∧W⊆S∧W′ and for all {a mathematical formula}R∈V′ there is some {a mathematical formula}S∈V such that {a mathematical formula}S∧S⊆S∧R.
       </list-item>
      </list>
      <paragraph>
       In order to clarify the intuitions behind the above proposed binary relations we now present an example.
      </paragraph>
      <paragraph label="Example 5.1">
       Let {a mathematical formula}L, {a mathematical formula}W0, {a mathematical formula}W1, {a mathematical formula}W2 and {a mathematical formula}W3 be as stated in Example 1.4 and let {a mathematical formula}K=W0 and {a mathematical formula}S be the following system of spheres centred on {a mathematical formula}‖K‖:{a mathematical formula} Furthermore, consider the sentences {a mathematical formula}α=q and {a mathematical formula}δ=p∨¬q and set {a mathematical formula}A={α,δ}.Since {a mathematical formula}‖¬α‖={W1,W2} and {a mathematical formula}‖¬δ‖={W3}, it holds that:{a mathematical formula}Fig. 3 contains a possible graphical representation of the system of spheres {a mathematical formula}S, where the sets {a mathematical formula}V1 and {a mathematical formula}V2 are highlighted.In these circumstances, {a mathematical formula}S∧W1⊂S∧W2=S∧W3. Therefore, having in mind the two above defined binary relations {a mathematical formula}⊑S1 and {a mathematical formula}⊑S2 we have that:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The following observation highlights a property that is satisfied by both relations {a mathematical formula}⊑S1 and {a mathematical formula}⊑S2.
      </paragraph>
      <paragraph label="Observation 5.2">
       Let A be any set of sentences and{a mathematical formula}Vbe any element of{a mathematical formula}H(〈A∩K〉). If{a mathematical formula}V⊆⋃α∈A∩KfS(¬α)then for all{a mathematical formula}V′∈H(〈A∩K〉),{a mathematical formula}V′⊑S1Vand{a mathematical formula}V′⊑S2V.
      </paragraph>
      <paragraph>
       At this point we remark that it is natural to require that the property mentioned in the above observation is satisfied by a binary relation to be used in the context of choosing the best elements of {a mathematical formula}H(〈A∩K〉) (which is precisely the use that we shall give to those two binary relations in what follows).
      </paragraph>
      <paragraph>
       Now, making use of the two binary relations introduced above we can provide two new constructions of multiple contraction functions from {a mathematical formula}S.
      </paragraph>
      <paragraph label="Definition 5.3">
       Let K be a belief set and {a mathematical formula}S be a system of spheres centred on {a mathematical formula}‖K‖, the multiple contraction function {a mathematical formula}÷S1 is defined, for any set of sentences B, as follows:{a mathematical formula} where {a mathematical formula}⊑S1 is the binary relation on {a mathematical formula}2ML defined by:{a mathematical formula}V′⊑S1V iff for all {a mathematical formula}W∈V there is some {a mathematical formula}W′∈V′ such that {a mathematical formula}S∧W⊆S∧W′.
      </paragraph>
      <paragraph label="Definition 5.4">
       Let K be a belief set and {a mathematical formula}S be a system of spheres centred on {a mathematical formula}‖K‖, the multiple contraction function {a mathematical formula}÷S2 is defined, for any set of sentences B, as follows:{a mathematical formula} where {a mathematical formula}⊑S2 is the binary relation on {a mathematical formula}2ML defined by:{a mathematical formula}V′⊑S2V iff for all {a mathematical formula}W∈V there is some {a mathematical formula}W′∈V′ such that {a mathematical formula}S∧W⊆S∧W′ and for all {a mathematical formula}R∈V′ there is some {a mathematical formula}S∈V such that {a mathematical formula}S∧S⊆S∧R.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Interrelations among the newly proposed multiple contraction functions, the S.F.-bMCs and the TRPMMCs
      </section-title>
      <paragraph>
       Throughout this subsection we assume that K is a belief set, {a mathematical formula}S is a system of spheres centred on {a mathematical formula}‖K‖ and {a mathematical formula}÷S1 and {a mathematical formula}÷S2 are the multiple contraction functions whose definitions we have introduced in the previous subsection. In what follows we shall investigate the interrelations among those functions, the {a mathematical formula}S filtration-based multiple contraction, denoted by {a mathematical formula}÷S (cf. Definition 2.19), and the transitively relational partial meet multiple contractions (cf. Definition 2.9).
      </paragraph>
      <paragraph>
       We start by showing that the multiple contraction functions {a mathematical formula}÷S1 and {a mathematical formula}÷S2 are different from each other.
      </paragraph>
      <paragraph label="Proof">
       It does not hold in general that, given a belief setKand a system of spheres{a mathematical formula}Scentred on{a mathematical formula}‖K‖, the multiple contraction function{a mathematical formula}÷S1onKis identical to the multiple contraction function{a mathematical formula}÷S2onK. That is, for some belief setKthere is a system of spheres{a mathematical formula}Scentred on{a mathematical formula}‖K‖and a set of sentences A, such that{a mathematical formula}K÷S1A≠K÷S2A, i.e.{a mathematical formula}Let {a mathematical formula}L, {a mathematical formula}W0, {a mathematical formula}W1, {a mathematical formula}W2, {a mathematical formula}W3, K, {a mathematical formula}S and A be as stated in Example 5.1 and recall that, in such circumstances, it holds that {a mathematical formula}H(〈A∩K〉)={V1,V2}, with {a mathematical formula}V1={W1,W3} and {a mathematical formula}V2={W2,W3}. For convenience recall also that Fig. 3 contains a possible graphical representation of the system of spheres {a mathematical formula}S, where the sets {a mathematical formula}V1 and {a mathematical formula}V2 are highlighted.From (11), (12) and Definition 5.3, Definition 5.4 (of the multiple contraction functions {a mathematical formula}÷S1 and {a mathematical formula}÷S2) it follows that:
       <list>
        {a mathematical formula}K÷S1A=Th(‖K‖∪V1∪V2)=Th({W0,W1,W2,W3}).{a mathematical formula}K÷S2A=Th(‖K‖∪V1)=Th({W0,W1,W3}).Thus, we can conclude that
       </list>
       <paragraph>
        {a mathematical formula}K÷S1A≠K÷S2A, as we wished to prove.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Our next goal is to prove that the multiple contraction functions {a mathematical formula}÷S1 and {a mathematical formula}÷S2 are TRPMMCs. Having that in mind we start by introducing the concept of transitively relational propositional package selection function and a characterization for the TRPMMCs in terms of such concept.
      </paragraph>
      <paragraph label="Definition 5.6">
       A propositional package selection function f for {a mathematical formula}‖K‖ is (transitively) relational if and only if there is a (transitive) relation ⪯ over {a mathematical formula}⋃B⊆LH(〈B∩K〉) such that for any set of sentences B:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       LetKbe a belief set. An operation ÷ is a transitively relational partial meet multiple contraction onKif and only if there is a transitively relational propositional package selection function f for{a mathematical formula}‖K‖such that:{a mathematical formula}for any set of sentences B.Left-to-right: Let ÷ be a transitively relational partial meet multiple contraction on K. Then there is a transitive relation ⊑ on the set {a mathematical formula}⋃B⊆LK⊥B such that {a mathematical formula}K÷B=⋂γ(K⊥B), where γ is a transitively relational package selection function defined, for all sets of sentences B, by {a mathematical formula}γ(K⊥B)={K} if {a mathematical formula}B∩Cn(∅)≠∅, and by the marking-off identity:{a mathematical formula} if {a mathematical formula}B∩Cn(∅)=∅.Now let ⪯ be the binary relation over {a mathematical formula}⋃B⊆LH(〈B∩K〉) defined by:{a mathematical formula}It follows from the transitivity of ⊑ that ⪯ is also a transitive relation. Now let f be defined by {a mathematical formula}f(WK⊥B)={V∈H(〈B∩K〉):V′⪯V for all V′∈H(〈B∩K〉)}, for any set of sentences B.Having in mind that, according to Observation 2.12, for all {a mathematical formula}X∈K⊥B there is some {a mathematical formula}W∈H(〈B∩K〉) such that {a mathematical formula}X=Th(‖K‖∪W) we can conclude that, for any set of sentences B:{a mathematical formula}Thus, according to Lemma 2.15, we have that f is a propositional package selection function for {a mathematical formula}‖K‖ such that {a mathematical formula}K÷B=Th(‖K‖∪(⋃f(H(〈B∩K〉)))), for all sets B. Furthermore, from the above we can also conclude that f is transitively relational, and this finishes the first part of the proof.Right-to-left: Let ÷ be such that, for any set of sentences B:{a mathematical formula} where f is a transitively relational propositional package selection function defined by:{a mathematical formula} for some transitive relation ⪯ over {a mathematical formula}⋃B⊆LH(〈B∩K〉).Now let ⊑ be the binary relation over {a mathematical formula}⋃B⊆LK⊥B defined by:{a mathematical formula} where {a mathematical formula}V,W∈⋃B⊆LH(〈B∩K〉) are such that {a mathematical formula}X=Th(‖K‖∪V) and {a mathematical formula}Y=Th(‖K‖∪W).Notice that the relation ⊑ is well defined because it follows from Corollary 2.13 that, for any given remainder {a mathematical formula}X∈⋃B⊆LK⊥B there is one and only one {a mathematical formula}V∈⋃B⊆LH(〈B∩K〉) such that {a mathematical formula}X=Th(‖K‖∪V). Furthermore, it follows from the transitivity of ⪯ that ⊑ is also a transitive relation.To lighten the writing, in all that follows, given a set {a mathematical formula}X∈⋃B⊆LK⊥B we shall denote by {a mathematical formula}VX the only element of {a mathematical formula}⋃B⊆LH(〈B∩K〉) such that {a mathematical formula}X=Th(‖K‖∪VX).Now let γ be defined by {a mathematical formula}γ(K⊥B)={K} if {a mathematical formula}B∩Cn(∅)≠∅, and {a mathematical formula}γ(K⊥B)={X∈K⊥B:X′⊑X for all X′∈K⊥B} if {a mathematical formula}B∩Cn(∅)=∅.{sup:12}Having in mind that, according to Corollary 2.13, there is a one-to-one correspondence between the sets {a mathematical formula}K⊥B and {a mathematical formula}H(〈B∩K〉) we can conclude that, for any set of sentences B, such that {a mathematical formula}B∩Cn(∅)=∅:{a mathematical formula}Thus, it follows from Lemma 2.16 that γ is a transitively relational package selection function for K, such that {a mathematical formula}K÷B=⋂γ(K⊥B), for all sets B. Therefore, ÷ is a transitively relational partial meet multiple contraction.  □
      </paragraph>
      <paragraph>
       We are now finally in a position to prove that {a mathematical formula}÷S1 and {a mathematical formula}÷S2 are TRPMMCs.
      </paragraph>
      <paragraph label="Proof">
       LetKbe a belief set and{a mathematical formula}Sbe a system of spheres centred on{a mathematical formula}‖K‖. Then the multiple contraction{a mathematical formula}÷S1onKis a transitively relational partial meet multiple contraction.We start by recalling that {a mathematical formula}÷S1 is defined as follows:{a mathematical formula} where {a mathematical formula}⊑S1 is the binary relation on {a mathematical formula}2ML defined by: {a mathematical formula}V′⊑S1V iff for all {a mathematical formula}W∈V there is some {a mathematical formula}W′∈V′ such that {a mathematical formula}S∧W⊆S∧W′.Now let f be such that, for any set of sentences B, {a mathematical formula}f(H(〈B∩K〉))={V∈H(〈B∩K〉): for all V′∈H(〈B∩K〉),V′⊑S1V}.It follows from Theorem 5.7 that to prove that {a mathematical formula}÷S1 is a transitively relational partial meet multiple contraction it is enough to show that f is a transitively relational propositional package selection function for {a mathematical formula}‖K‖.It follows immediately from its definition that f is a function, i.e. that if B and C are sets of sentences such that {a mathematical formula}H(〈B∩K〉)=H(〈C∩K〉) then {a mathematical formula}f(H(〈B∩K〉))=f(H(〈C∩K〉)).To prove that f is a propositional package selection function for {a mathematical formula}‖K‖ we must show that for any set of sentences B:
       <list>
        {a mathematical formula}f(H(〈B∩K〉))⊆H(〈B∩K〉).If {a mathematical formula}H(〈B∩K〉)≠∅ then {a mathematical formula}f(H(〈B∩K〉))≠∅.That condition (i) is satisfied follows immediately from the definition of
       </list>
       <paragraph>
        f. Now we show that (ii) also holds. Assume {a mathematical formula}H(〈B∩K〉)≠∅. Then it must hold that {a mathematical formula}B∩Cn(∅)=∅ and it follows from Lemma 2.11 that there exists a set {a mathematical formula}V such that {a mathematical formula}V⊆⋃α∈B∩KfS(¬α) and {a mathematical formula}V∈H(〈B∩K〉). Thus, according to Observation 5.2, it holds that {a mathematical formula}f(H(〈B∩K〉))={V∈H(〈B∩K〉): for all V′∈H(〈B∩K〉),V′⊑S1V}≠∅.Finally, that f is transitively relational follows immediately from the fact that the binary relation {a mathematical formula}⊑S1 over {a mathematical formula}2ML is transitive.  □
       </paragraph>
      </paragraph>
      <paragraph label="Proof">
       A proof for this theorem can be obtained by making only a few small and obvious modifications to the above presented proof for the previous theorem.  □
      </paragraph>
      <paragraph>
       At this point it is worth to remark that both {a mathematical formula}÷S1 and {a mathematical formula}÷S2 differ from the multiple contraction function {a mathematical formula}÷S, as it is stated in the following corollary:
      </paragraph>
      <paragraph label="Corollary 5.10">
       Given a belief setKand a system of spheres{a mathematical formula}Scentred on{a mathematical formula}‖K‖, in general, none of the multiple contraction functions{a mathematical formula}÷S1and{a mathematical formula}÷S2coincides with the{a mathematical formula}Sfiltration-based multiple contraction{a mathematical formula}÷S. That is, it holds that:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}÷S1≠÷S.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}÷S2≠÷S.
       </list-item>
      </list>
      <paragraph label="Proof">
       Follows trivially from the fact that {a mathematical formula}÷S1 and {a mathematical formula}÷S2 are TRPMMCs (cf. Theorem 5.8, Theorem 5.9) whereas {a mathematical formula}÷S is not a TRPMMC (cf. Counterexample 3.1). □
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Related works
     </section-title>
     <paragraph>
      In this section we shall make a very brief exposition of some works where multiple change operations are studied and which are related to the investigation reported in the present paper. Furthermore, some of the natural topics of future research (cf. Section 7) which arise from the study presented in this text consist in the investigation of the interconnections as well as of the possible combinations of the main contributions of this paper with some of the works referred in this section.
     </paragraph>
     <paragraph>
      We start by mentioning paper [14], where an impossibility result concerning multiple contractions has also been presented. In that reference, firstly some intuitive properties are presented concerning the interrelation between the result of the multiple contraction of a belief set K by a set of sentences {a mathematical formula}{α,β} and the results of the singleton contraction of K by α and by {a mathematical formula}α∨β. Then, with the central goal of arguing against the recovery postulate, it is shown that, given a belief set K and a partial meet (singleton) contraction function, it is not possible to define a multiple contraction function such that the presented properties are all (simultaneously) satisfied. We notice that this result is quite different from the one underlying the present paper. In fact, very roughly speaking we can say that on the one hand, Niederée's result states that, given a certain contraction function, there is not any multiple contraction that satisfies certain conditions (concerning its interrelation with the given singleton contraction) while, on the other hand, our result states that there are some (transitively relational partial meet) multiple contraction functions which cannot be generated (in any way) from any (transitively relational partial meet) singleton contraction.
     </paragraph>
     <paragraph>
      Another work where an impossibility result concerning multiple contraction has been presented is [13]. In that paper Sven Ove Hansson has shown that in general, given a partial meet multiple contraction ÷ on a belief set K there is not a partial meet singleton contraction − on K such that ÷ can be reconstructed from − in the sense that the following condition holds:
     </paragraph>
     <list>
      <list-item>
       For each set of sentences A there is a set B such that{a mathematical formula}
      </list-item>
     </list>
     <paragraph>
      Furthermore, Hansson proved also that the converse does not hold either, i.e. that, given a partial meet singleton contraction − in general there is not a partial meet multiple contraction ÷ such that:
     </paragraph>
     <list>
      <list-item>
       For each set of sentences B there is a set A such that equality (13) holds.
      </list-item>
     </list>
     <paragraph>
      However, despite this strong impossibility result, in the mentioned paper some special situations where identified in which conditions (M-S) and/or (S-M) are satisfied.
     </paragraph>
     <paragraph>
      We note that the impossibility result of the present paper is somehow akin to Hansson's one. In fact Corollary 4.5 yields that there are some transitively relational partial meet multiple contraction functions which cannot be obtained (neither as an intersection of certain singleton contraction results nor in any other way) from a transitively relational partial meet singleton contraction. Furthermore, this result leads to the question of identifying the conditions under which a transitively relational partial meet multiple contraction is such that it can be obtained by means of a system of spheres-based construction of multiple contractions, a question which is somehow similar to the one which underlays Hansson's paper.
     </paragraph>
     <paragraph>
      Next we highlight some of the main existing works on two kinds of multiple change operations — namely, set contraction and multiple revision — which differ from but are strongly related with multiple contraction.
     </paragraph>
     <paragraph>
      Thus, we start by introducing some notation and terminology concerning these kinds of operations. Given a belief set K, generally speaking, by a multiple revision onK we mean a function, say ⊕ that associates to each set of sentences B a belief set {a mathematical formula}K⊕B which, if possible, (i) contains the set B, (ii) is consistent, and (iii) contains as many sentences of K as it is possible. On the other hand given a belief set K, in general, the expression set contraction onK designates a function, say ⊖ whose output for an arbitrary argument B, denoted {a mathematical formula}K⊖B, is a logically closed subset of K which is consistent with the set B (i.e. {a mathematical formula}(K⊖B)∪B is a consistent set of sentences).
     </paragraph>
     <paragraph>
      The class of set contractions was introduced in [21], [22], as consisting of the family of functions that satisfied a certain set of eight postulates which, in [23, pp. 530–531], are divided in two sets: six basic postulates for set contraction and two supplementary postulates for set contraction. In [22], [23], a partial meet model for set contraction was introduced and two representation theorems for those functions were obtained, one involving (only) the basic postulates for set contractions (see, e.g., [23, Theorem 3.13]) and another one involving the basic and the supplementary postulates for set contractions (see, e.g., [23, Theorem 3.26]). Additionally, in the mentioned papers, Zhang et al. introduced the NOP-based contractions, another class of set contraction functions whose definition is based on the concept of nicely-ordered partition (NOP) of a belief set. Moreover, in those references a representation theorem for such functions has been presented (e.g. [23, Theorem 4.19]) which asserts that a function ⊖ is a NOP-based contraction if and only if it satisfies the basic and the supplementary postulates for set contraction as well as an additional postulate — the so-called Limit Postulate (for set contraction) — which is essentially a principle concerning the relationship between the result of the set contraction by an infinite set and the results of the set contractions by the finite subsets of that infinite set and its precise formulation can be found in, e.g., [23, p. 548].
     </paragraph>
     <paragraph>
      In [21], Zhang presented the definition of multiple revision by means of a list of eight postulates, namely postulates {a mathematical formula}(⊗1)−(⊗8) listed in [23, Subsection 2.1], which are the result of the generalization to the case of revision by sets of sentences of the basic and the supplementary AGM postulates for revision. Furthermore, yet in [21], it was shown that the two mentioned kinds of operations are interdefinable by means of the following identities, which are analogous to the Levi identity and the Harper identity (that expose the relationship between AGM (singleton) contraction and revision operations):{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Now, to highlight the interconnection between multiple revision and multiple contraction we recall the generalization of the Levi Identity that was proposed by Sven Ove Hansson in [10], [11]. Given a belief set K, an arbitrary set of sentences B and a multiple contraction ÷ on K, the first step towards the mentioned generalization was the definition of a set ¬B — called the negation of B —, whose elements are, roughly speaking, the (finite) disjunctions of sentences that are negations of elements of B (e.g. [12, Definition 3.35]), and which is such that the result of the multiple contraction of K by ¬B (i.e. {a mathematical formula}K÷¬B) is (a subset of K which is) consistent with B. Afterwards, making use of the above mentioned concept of negation of a set (of sentences), Hansson proposed the following straightforward generalization of the Levi identity for defining of a multiple revision function ⊕ on K:{a mathematical formula}
     </paragraph>
     <paragraph>
      Next we briefly describe the constructive models for multiple revision and for set contraction that were proposed by Peppas and which are strongly related with the above mentioned ones.
     </paragraph>
     <paragraph>
      In [15], Peppas proposed a generalization of Grove's system of spheres-based definition of (singleton) revision functions to the case of multiple revision and showed that the resulting class of functions is axiomatically characterized by eight postulates for multiple revision — namely, postulates {a mathematical formula}(K⊕1)−(K⊕8) listed in [15, p. 365] — which are very similar to the above mentioned multiple revision postulates considered in [23]. The proposed generalization of Grove's construction requires that the systems of spheres considered are well ranked (where a system of spheres {a mathematical formula}S is said to be well ranked if it holds that for every nonempty consistent set of sentences B, there exists a smallest sphere {a mathematical formula}SB in {a mathematical formula}S intersecting {a mathematical formula}‖B‖ and {a mathematical formula}‖B‖∩SB=‖⋂(‖B‖∩SB)‖).
     </paragraph>
     <paragraph>
      More recently, in [16], a constructive model for set contraction was presented. This model is based on a certain kind of binary relations on the set of nonempty sets of sentences — named comparative possibility preorders — which are a generalization of the epistemic entrenchment relations (in the sense of being preorders on sets of sentences rather than (simply) preorders on sentences). The class of comparative possibility preorder-based set contractions is axiomatically characterized by the basic and the supplementary postulates for set contraction. Thus, since the limit postulate is not included in its axiomatic characterization, we can conclude that this class of functions subsumes the one consisting of the NOP-based contractions. In this regard we mention yet that in [16], three properties were identified whose fulfilment by a comparative possibility preorder ⩽ is necessary and sufficient to assure that the (corresponding) ⩽-based set contraction satisfies the limit postulate.
     </paragraph>
     <paragraph>
      Finally, to close this section, we mention reference [4], where Delgrande et al. have proposed two operators of belief change of logic programs: an expansion operator and a revision operator. The operators proposed there are the result of the adaptation to the context of logic programs of some well known operators of belief change developed in the context of classical propositional logic. The main idea behind the adaptations presented was the analogy that was made between a specific logic program and a formula or set of formulas in classical logic and also between sets of SE models ([20]) of a logic program and propositions (i.e. sets of possible worlds) in the context of propositional logic. We notice yet that, having the mentioned analogy in mind, the revision operator proposed there can be seen as a multiple revision operator.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>