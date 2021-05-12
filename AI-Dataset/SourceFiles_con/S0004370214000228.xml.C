<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    CTL update of Kripke models through protections.
   </title>
   <abstract>
    We present a nondeterministic, recursive algorithm for updating a Kripke model so as to satisfy a given formula of computation-tree logic (CTL). Recursive algorithms for model update face two dual difficulties: (1) Removing transitions from a Kripke model to satisfy a universal subformula may dissatisfy some existential subformulas. Conversely, (2) adding transitions to satisfy an existential subformula may dissatisfy some universal subformulas. To overcome these difficulties, we employ protections of the form 〈E,A,L〉, recording information about the satisfaction of subformulas previously treated by the algorithm. Intuitively, (1) E is the set of transitions that we cannot remove without compromising the satisfaction of previously treated subformulas. Conversely, (2) A is the set of transitions that we can add. Hence, update proceeds without diminishing E and without augmenting A. Finally, (3) L is a set of literals protecting the model labels. We illustrate our algorithm through several examples: Emerson and Clarke's mutual-exclusion problem, Clarke et. al.'s microwave-oven example, synchronous counters, and randomly generated models and formulas. In addition, we compare our method with other update approaches for either CTL or fragments of CTL. Lastly, we provide proofs of soundness and completeness and a complexity analysis.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A computation-tree logic (CTL) model checker is an automated tool that usually has as input (1) a Kripke model {a mathematical formula}M formalizing a system, (2) a CTL formula φ expressing a desirable property of this system, and (3) a set of initial states. The output is either a confirmation or a denial that {a mathematical formula}M satisfies φ at all initial states, meaning that the system respectively has, or does not have, the required property.{sup:1} In case of denial, model checkers often produce a counterexample, consisting of an error trace. This counterexample is intended as a guide for manually updating or repairing {a mathematical formula}M, or a high-level description of {a mathematical formula}M, so that the unsatisfied property is fulfilled. We believe that even a partial automation of such a repairing process could have a significant impact on the use of the model checking technique. Besides, the problem of model update is closely related to that of reasoning about actions and change (e.g., [14]). Model update is therefore an important subject in Artificial Intelligence, namely that of modifying transition systems.
     </paragraph>
     <paragraph>
      In spite of its relevance, the problem of mechanically updating a Kripke model has been little studied. As far as we know, Buccafurri et al. [1] proposed the first work on CTL model update: an updater for repairing, through abduction, Kripke models with the addition and removal of transitions. In a later work, Calzone et al. [3] gave a method for updating Kripke models with the addition and removal not only of transitions, but of labels as well, dependent on biases determined by the application domain (biochemical networks). More recently, Zhang and Ding [22] have devised a repair algorithm producing “admissible” models.
     </paragraph>
     <paragraph>
      Model update methods based on counterexamples produced by a model checker have a drawback. Model repair focused on invalidating one particular counterexample to a universal property does not guarantee that the repaired model satisfies this property, because there may be more than one counterexample, and all counterexamples must be treated simultaneously. Furthermore, if the defective model does not satisfy an existential property, the model checker does not provide a useful counterexample, because all traces are counterexamples. Hence, this drawback invites us to consider a method based on a concept other than counterexamples.
     </paragraph>
     <paragraph>
      We present a recursive method for repairing models in a nondeterministic way, based on the preservation of the satisfaction of subformulas via a mechanism of “protections”. To update a model with respect to a formula φ, our method recursively updates the model to satisfy the subformulas of φ. Every time our method updates a model to satisfy a subformula α, the satisfaction of α is protected. This protection ensures that if α is a proper subformula of β, then an update to satisfy β causes no loss of the satisfaction of α achieved by a previous update. To facilitate the treatment of negation, our algorithm requires that CTL formulas be in negation normal form and written with a set of operators closed under duality.
     </paragraph>
     <paragraph>
      A previous version [5] of this article showed the behavior of a software tool implementing our algorithm using Emerson and Clarke's mutual-exclusion problem [15]. We have now extended that study to include more examples: Clarke et al.'s microwave-oven model [11] illustrating a specification, a scalable counter exhibiting larger models, and randomly generated models and formulas also showing larger models. In addition, [5] only outlined soundness and completeness proofs of our method, whereas we now give more detailed proofs, and perform a complexity analysis of our algorithm. Finally, the cursory comparison with two methods in [5] has now been detailed and extended to more approaches for either CTL or fragments of CTL.
     </paragraph>
     <paragraph>
      In another previous work [4], we extended a former version of the method presented here so as to modify a concise representation of a Kripke model instead of the Kripke model itself. The former version, however, employed a more primitive form of universal protection (covered in Section 6). This kind of protection, unlike the one used here, is unsatisfactory because it is unclear if the resulting algorithm is complete.
     </paragraph>
     <paragraph>
      After fixing the notation in Section 2, we treat CTL model update in Section 3. Next, we devote Section 4 to nondeterminism elimination. Examples illustrating the behavior of a software tool implementing our algorithm appear in Section 5; comparisons with other approaches occur in Section 6. Section 7 gives a summary and outlines possible future directions for research. The soundness and completeness proofs are in Appendix A; the complexity analysis is in Appendix B.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Technical preliminaries
     </section-title>
     <paragraph>
      This section gives introductory definitions and fixes the notation. We assume some familiarity with CTL model checking and refer the reader to [11] for a more thorough treatment.
     </paragraph>
     <paragraph>
      A signature{a mathematical formula}Σ=〈S,V〉 consists of a pair of nonempty finite sets. We call the elements of S and V, states, and (propositional) variables, respectively. Unless otherwise stated, we assume that {a mathematical formula}Σ=〈S,V〉 is an arbitrary fixed signature. If {a mathematical formula}E=〈c1,…,cn〉, {a mathematical formula}ciE is the i-th component of {a mathematical formula}E. The set of literals over {a mathematical formula}VΣ is {a mathematical formula}Lit(VΣ)=VΣ∪{¬p|p∈VΣ}. The complement of literals is defined by {a mathematical formula}p¯=¬p and {a mathematical formula}¬p¯=p, {a mathematical formula}∀p∈VΣ. If {a mathematical formula}X⊆Lit(VΣ) then: {a mathematical formula}X¯={ℓ¯|ℓ∈X}; X is consistent if {a mathematical formula}∀ℓ∈X,ℓ¯∉X; and X is {a mathematical formula}VΣ-maximal if for all {a mathematical formula}p∈VΣ, {a mathematical formula}p∈X or {a mathematical formula}¬p∈X. If {a mathematical formula}R⊆SΣ×SΣ then R is total if {a mathematical formula}∀s∈SΣ, {a mathematical formula}∃t∈SΣ such that {a mathematical formula}(s,t)∈R. The set of successors of s under R is {a mathematical formula}R[s]={t|(s,t)∈R}. If {a mathematical formula}A∩B=∅, {a mathematical formula}f:A→C, and {a mathematical formula}g:B→D, {a mathematical formula}f∪g is the function {a mathematical formula}f∪g:A∪B→C∪D such that {a mathematical formula}f∪g(t)=f(t) if {a mathematical formula}t∈A and {a mathematical formula}f∪g(t)=g(t) if {a mathematical formula}t∈B. We use {a mathematical formula}ID to denote the identity on D, and {a mathematical formula}CD to denote a constant function such that {a mathematical formula}∀t∈D,CD(t)=C. To denote the symmetric difference of C and D, we use {a mathematical formula}Δ(C,D).
     </paragraph>
     <paragraph label="Definition 2.1">
      {a mathematical formula}Kripke Σ-modelsWe say that {a mathematical formula}M=〈S,R,L〉 is a Kripke Σ-model if {a mathematical formula}S=SΣ, {a mathematical formula}R⊆S2 is total, and {a mathematical formula}L:S→P(Lit(VΣ)) is such that for all {a mathematical formula}t∈S, {a mathematical formula}L(t) is consistent and {a mathematical formula}VΣ-maximal.
     </paragraph>
     <paragraph>
      If {a mathematical formula}(s,t)∈R we call {a mathematical formula}(s,t) a transition from s to t and we abbreviate this to sRt. We call L the labeling function of {a mathematical formula}M. If {a mathematical formula}ℓ∈Lit(VΣ) and {a mathematical formula}s∈S, then {a mathematical formula}L[s⊕ℓ] denotes the labeling function such that {a mathematical formula}L[s⊕ℓ](s)=(L(s)∪{ℓ})−{ℓ¯} and {a mathematical formula}L[s⊕ℓ](t)=L(t) for {a mathematical formula}t≠s. {a mathematical formula}KΣ denotes the set of Σ-models.
     </paragraph>
     <paragraph>
      We define the distance between {a mathematical formula}M and {a mathematical formula}M′∈KΣ, as {a mathematical formula}d(M,M′)=|Δ(SM,SM′)|+|Δ(RM,RM′)|+∑t∈SM(|Δ(LM(t),LM′(t))|/2). It can be proved that d is a metric on {a mathematical formula}KΣ.
     </paragraph>
     <paragraph>
      Models are often represented graphically as in Section 5, writing only positive literals as labels of the states.
     </paragraph>
     <paragraph>
      Next, we define an extension of CTL. We use a base of operators closed under duality with the following pairs of dual operators: {a mathematical formula}(F,T), {a mathematical formula}(∨,∧), {a mathematical formula}(EX,AX), {a mathematical formula}(EU,AR), and {a mathematical formula}(AU,ER). We restrict formulas to a negation normal form (NNF), by limiting the application of negation to variables. However, since we use a base of operators closed under duality, other instances of negation may be considered as shorthand. We add to CTL out-degree formulas{a mathematical formula}OD⩽n, and their duals {a mathematical formula}OD&gt;n, to limit the number of transitions going out of a state.
     </paragraph>
     <paragraph label="Definition 2.2">
      {a mathematical formula}Σ-CTL and Σ-XCTLFormulas of computation-tree logic of signature Σ,{a mathematical formula}Σ-CTL (abbreviated Φ), have the following syntax:{a mathematical formula} where ℓ stands for any literal in {a mathematical formula}Lit(VΣ) and {a mathematical formula}0&lt;n⩽|SΣ|.We will single out the modal fragment of Σ-CTL. {a mathematical formula}Σ-XCTLformulas (abbreviated Ψ) have the following syntax:{a mathematical formula}
     </paragraph>
     <paragraph>
      We use {a mathematical formula}φ∈Σ-CTL to indicate that φ is a {a mathematical formula}Σ-CTL formula. The size of {a mathematical formula}φ∈Σ-CTL, written {a mathematical formula}|φ|, is defined by {a mathematical formula}|F|=|T|=0, {a mathematical formula}|ℓ|=|OD⩽n|=|OD&gt;n|=1, {a mathematical formula}|EXα|=|AXα|=|α|+1, and {a mathematical formula}|α∨β|=|α∧β|=|E[αUβ]|=|A[αUβ]|=|E[αRβ]|=|A[αRβ]|=|α|+|β|+1.
     </paragraph>
     <paragraph>
      If φ is built from atomic formulas ({a mathematical formula}F, {a mathematical formula}T, or ℓ) by using ∨ or ∧, we say that φ is propositional; otherwise we say that φ is a non-propositional formula. We view other propositional operators (→, ↔, exclusive or ⊻) and temporal operators (EF, AF, EG, AG) as abbreviations: {a mathematical formula}EFα=E[TUα], {a mathematical formula}AFα=A[TUα], {a mathematical formula}EGα=E[FRα], {a mathematical formula}AGα=A[FRα].
     </paragraph>
     <paragraph>
      The above CTL syntax is a key point in the simplicity of our model update algorithm. Any syntax that has a base of operators similar to those used in model checking [11], e.g., {a mathematical formula}{¬,∧,EX,AF,EU}, complicates model update w.r.t. formulas ¬α, AFα, and {a mathematical formula}E[αUβ]. Another key point is that our algorithm focuses on {a mathematical formula}Σ-XCTL formulas, and deals with path operators (EU, AU, ER, and AR) through their fixed-point characterizations [11].
     </paragraph>
     <paragraph label="Definition 2.3">
      Next, we provide basic definitions for the protection mechanism. Σ-Protections{a mathematical formula}P=〈E,A,L〉 is a Σ-protection if:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}E⊆A⊆SΣ×SΣ, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}L:SΣ→P(Lit(VΣ)) is such that {a mathematical formula}∀t∈SΣ, {a mathematical formula}L(t) is consistent.
      </list-item>
     </list>
     <paragraph>
      Protections are the main key point of our update algorithm. Intuitively, a protection {a mathematical formula}P=〈E,A,L〉 records information about the satisfaction of previously treated subformulas by our algorithm. In P, E is the set of transitions {a mathematical formula}(s,t) such that {a mathematical formula}(s,t)cannot be removed without compromising the satisfaction of previously treated subformulas. Analogously, A is the set of transitions {a mathematical formula}(s,t) such that {a mathematical formula}(s,t)can be added. Finally, L is the set of literals ℓ such that ℓ cannot be changed to{a mathematical formula}ℓ¯ without compromising the satisfaction of previously treated subformulas. Transitions related to the satisfaction of universal (existential) subformulas are recorded in A (E). Thus, to preserve the satisfaction of previously treated subformulas, we proceed without diminishing E or augmenting A, and without complementing literals in L.
     </paragraph>
     <paragraph>
      We refer to states in {a mathematical formula}E[s] ({a mathematical formula}A[s]) as the existentially (universally) protected successors of s. We will use {a mathematical formula}PΣ to denote the set of Σ-protections.
     </paragraph>
     <paragraph label="Definition 2.4">
      {a mathematical formula}Protected models, PM, and P⊥Let {a mathematical formula}M∈KΣ and {a mathematical formula}P∈PΣ. We say that {a mathematical formula}Mis protected by P, and we write {a mathematical formula}M▷P if:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}EP⊆RM⊆AP, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}∀t∈SM:LM(t)⊇LP(t).
      </list-item>
     </list>
     <paragraph>
      If {a mathematical formula}R⊆S2 and {a mathematical formula}s∈S, a path in R beginning at s, is a sequence {a mathematical formula}π:N→S, such that {a mathematical formula}π(0)=s and {a mathematical formula}∀n∈N, {a mathematical formula}π(n)Rπ(n+1). We write {a mathematical formula}πn instead of {a mathematical formula}π(n) and we use {a mathematical formula}ΠR,s to denote the set of paths in R beginning at s.
     </paragraph>
     <paragraph label="Definition 2.5">
      {a mathematical formula}Σ-CTL protected semanticsIf {a mathematical formula}(M,P)∈KPΣ is a protected Σ-model, {a mathematical formula}s∈SM and {a mathematical formula}φ∈Σ-CTL, then we say that {a mathematical formula}(M,P)satisfies φ at s, and we write {a mathematical formula}(M,P),s⊨φ, if:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}(M,P),s⊭F. {a mathematical formula}(M,P),s⊨T. {a mathematical formula}(M,P),s⊨ℓ if {a mathematical formula}ℓ∈LP(s).
      </list-item>
      <list-item label="2.">
       {a mathematical formula}(M,P),s⊨α∨β if {a mathematical formula}(M,P),s⊨α or {a mathematical formula}(M,P),s⊨β.
      </list-item>
      <list-item label="3.">
       {a mathematical formula}(M,P),s⊨α∧β if {a mathematical formula}(M,P),s⊨α and {a mathematical formula}(M,P),s⊨β.
      </list-item>
      <list-item label="4.">
       {a mathematical formula}(M,P),s⊨EXα if {a mathematical formula}∃t∈EP[s] such that {a mathematical formula}(M,P),t⊨α.
      </list-item>
      <list-item label="5.">
       {a mathematical formula}(M,P),s⊨AXα if {a mathematical formula}∀t∈AP[s], {a mathematical formula}(M,P),t⊨α.
      </list-item>
      <list-item label="6.">
       {a mathematical formula}(M,P),s⊨E[αUβ] if {a mathematical formula}∃π∈ΠEP,s, and {a mathematical formula}∃j∈N such that{a mathematical formula}(M,P),πj⊨β and {a mathematical formula}∀i∈N, {a mathematical formula}i&lt;j→(M,P),πi⊨α.
      </list-item>
      <list-item label="7.">
       {a mathematical formula}(M,P),s⊨A[αUβ] if {a mathematical formula}∀π∈ΠAP,s, {a mathematical formula}∃j∈N such that{a mathematical formula}(M,P),πj⊨β and {a mathematical formula}∀i∈N, {a mathematical formula}i&lt;j→(M,P),πi⊨α.
      </list-item>
      <list-item label="8.">
       {a mathematical formula}(M,P),s⊨E[αRβ] if {a mathematical formula}∃π∈ΠEP,s such that either
      </list-item>
      <list-item label="9.">
       {a mathematical formula}(M,P),s⊨A[αRβ] if {a mathematical formula}∀π∈ΠAP,s, either
      </list-item>
      <list-item label="10.">
       {a mathematical formula}(M,P),s⊨OD⩽n if {a mathematical formula}|AP[s]|⩽n.
      </list-item>
      <list-item label="11.">
       {a mathematical formula}(M,P),s⊨OD&gt;n if {a mathematical formula}|EP[s]|&gt;n.
      </list-item>
     </list>
     <paragraph label="Definition 2.6">
      {a mathematical formula}Σ-CTL semanticsIf {a mathematical formula}M is a Σ-model, {a mathematical formula}s∈SM and {a mathematical formula}φ∈Σ-CTL, we say that {a mathematical formula}Msatisfies φ at s, {a mathematical formula}M,s⊨φ, if {a mathematical formula}(M,PM),s⊨φ.
     </paragraph>
     <paragraph>
      We extend {a mathematical formula}Σ-CTL protected semantics to sets of states and sets of formulas. If {a mathematical formula}S⊆SM then {a mathematical formula}(M,P),S⊨φ if for all {a mathematical formula}s∈S, {a mathematical formula}(M,P),s⊨φ. If {a mathematical formula}Γ⊆Σ-CTL then {a mathematical formula}(M,P),s⊨Γ if for all {a mathematical formula}φ∈Γ, {a mathematical formula}(M,P),s⊨φ. If {a mathematical formula}φ1,φ2 are two {a mathematical formula}Σ-CTL formulas, we say that {a mathematical formula}φ1 and {a mathematical formula}φ2 are logically equivalent, and we write {a mathematical formula}φ1≡φ2, if for all {a mathematical formula}M∈KΣ and all {a mathematical formula}s∈SM: {a mathematical formula}M,s⊨φ1 if {a mathematical formula}M,s⊨φ2.
     </paragraph>
     <paragraph>
      In Section 5, we use the equivalence {a mathematical formula}AGα∧AGβ≡AG(α∧β) to factor conjunctions of AG formulas. Our algorithm uses the following equivalences, known as fixed-point characterizations, to recursively compute a model update in the respective cases:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      A model update w.r.t. EU and AU formulas can be computed with a least fixed-point (lfp) operator, while a model update w.r.t. ER and AR can be computed with a greatest fixed-point (gfp) operator [11, p. 63].
     </paragraph>
    </section>
    <section label="3">
     CTL update algorithms
     <paragraph>
      In this section, we describe an algorithm that uses protected models for model update w.r.t. {a mathematical formula}Σ-CTL formulas. After a brief explanation of the pseudo-code notational conventions and basic update operations, we describe two model-update algorithms for {a mathematical formula}Σ-XCTL formulas. The first one is a direct algorithm that we include here for the purpose of emphasizing the main features of the model-update problem. The second one implements our method for model update using protected models. Finally, we describe how to extend our method to all formulas in {a mathematical formula}Σ-CTL, and how to add states to the signature Σ if the input formula is not satisfiable by any Σ-model. Appendix A includes a proof of the correctness and completeness of {a mathematical formula}XUpdprot, and Appendix B provides a complexity analysis of {a mathematical formula}Updprot.
     </paragraph>
     <section label="3.1">
      <section-title>
       Nondeterministic pseudo-code
      </section-title>
      <paragraph>
       We use a nondeterministic pseudo-code. Besides usual control statements and procedures, our pseudo-code has the following commands.
      </paragraph>
      <paragraph>
       Given a finite multiset A, the command “{a mathematical formula}guessx∈A” computes a nondeterministic choice of an element u from A and assigns u to x; if {a mathematical formula}A=∅, the computation fails. The command “{a mathematical formula}x←e” is a nondeterministic assignment equivalent to “{a mathematical formula}guessx∈Ae”, where {a mathematical formula}Ae is the multiset of values produced by the nondeterministic computation of e.
      </paragraph>
      <paragraph>
       We say that P is a nondeterministic procedure if P is a procedure and there is some occurrence of guess in the commands defining P. If P is a nondeterministic procedure, and {a mathematical formula}P(a1,…,an) is a call to P with arguments {a mathematical formula}a1,…,an, the computation of{a mathematical formula}P(a1,…,an) consists of a set of execution paths. Each occurrence of a command {a mathematical formula}guessx∈A allows to continue a computation on different execution paths, one path for each element of A.
      </paragraph>
      <paragraph>
       We use two commands to indicate the end of an execution path in a nondeterministic procedure P. “returnr” halts the execution and, as one of the results computed by P, returns r. “fail” halts the execution without returning any result.
      </paragraph>
      <paragraph>
       Execution paths ending with return are successful paths, and those ending with fail are unsuccessful paths. The multiset of results computed by {a mathematical formula}P(a1,…,an), is denoted by {a mathematical formula}P[a1,…,an]. Thus, {a mathematical formula}P[a1,…,an]=∅ means that, for the given arguments, all execution paths of P are unsuccessful; in this case we say that P fails.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Modification of models
      </section-title>
      <paragraph>
       We build our algorithm for model update by using a few basic operations to gradually change the input model.
      </paragraph>
      <paragraph label="Definition 3.1">
       Update operationsLet {a mathematical formula}M∈KΣ, {a mathematical formula}s,s′∈SM, {a mathematical formula}ℓ∈Lit(VΣ), {a mathematical formula}S′⊆SM, and {a mathematical formula}S″≠∅ a finite set, such that {a mathematical formula}S′≠∅ and {a mathematical formula}S″∩SM=∅. The update operations on Kripke models are:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Lu(M,s,ℓ)=〈SM,RM,LM[s⊕ℓ]〉. Add ℓ to {a mathematical formula}LM(s), and remove {a mathematical formula}ℓ¯.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}T+(M,s,s′)=〈SM,RM∪{(s,s′)},LM〉. Add {a mathematical formula}(s,s′) to {a mathematical formula}RM.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}Tu(M,s,S′)=〈SM,(RM−({s}×RM[s]))∪({s}×S′),LM〉. Replace the successors of s, {a mathematical formula}RM[s], by {a mathematical formula}S′.
       </list-item>
       <list-item label="4.">
        {a mathematical formula}S+(M,S″)=〈SM∪S″,RM∪IS″,LM∪V¯S″〉. Add {a mathematical formula}S″ to {a mathematical formula}SM, add {a mathematical formula}IS″ to {a mathematical formula}RM, and label all {a mathematical formula}t∈S″ with {a mathematical formula}V¯.
       </list-item>
      </list>
      <paragraph>
       Successive applications of the operations {a mathematical formula}Lu, {a mathematical formula}T+, and {a mathematical formula}Tu are sufficient to transform a given Σ-model into any other Σ-model. Besides, these operations are instrumental to achieve that a modification of a model satisfies literals, EX formulas, and AX formulas, respectively. Note that {a mathematical formula}S+(M,S″) is not a model over Σ, i.e., {a mathematical formula}S+(M,S″)∉KΣ.
      </paragraph>
      <paragraph>
       Below, we give a precise definition of what we regard as an acceptable modification of a model {a mathematical formula}M w.r.t. a formula φ.
      </paragraph>
      <paragraph label="Definition 3.2">
       {a mathematical formula}Modifications of M w.r.t.φIf {a mathematical formula}M is a Σ-model, {a mathematical formula}s∈SM and {a mathematical formula}φ∈Σ-XCTL, we define, by recursion on φ, the set of modifications of{a mathematical formula}Mw.r.t. φ at s, {a mathematical formula}Modif(M,s,φ):
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Modif(M,s,F)=∅ and {a mathematical formula}Modif(M,s,T)={M}
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Modif(M,s,ℓ)={Lu(M,s,ℓ)}
       </list-item>
       <list-item label="3.">
        {a mathematical formula}Modif(M,s,α∨β)=Modif(M,s,α)∪Modif(M,s,β)
       </list-item>
       <list-item label="4.">
        {a mathematical formula}Modif(M,s,α∧β)={M′∈KΣ|∃Mα∈Modif(M,s,α).M′∈Modif(Mα,s,β)&amp;M′,s⊨α∧β}
       </list-item>
       <list-item label="5.">
        {a mathematical formula}Modif(M,s,EXα)={M′∈KΣ|∃s′∈SM.M′∈Modif(T+(M,s,s′),s′,α)&amp;M′,s⊨EXα}
       </list-item>
       <list-item label="6.">
        {a mathematical formula}Modif(M,s,AXα)={M′∈KΣ|∃S′∈2SM−{∅}.M′∈Modif⁎(Tu(M,s,S′),S′,α)&amp;M′,s⊨AXα}
       </list-item>
       <list-item label="7.">
        {a mathematical formula}Modif(M,s,OD⊙n)={M′∈KΣ|∃S′∈2SM−{∅}.|S′|⊙n&amp;M′=Tu(M,s,S′)},for ⊙∈{⩽,&gt;}
       </list-item>
      </list>
      <paragraph>
       Observe that for all {a mathematical formula}M′∈Modif(M,s,φ), {a mathematical formula}M′,s⊨φ.
      </paragraph>
     </section>
     <section label="3.3">
      A direct update algorithm for {a mathematical formula}Σ-XCTL
      <paragraph>
       We now define a direct algorithm, {a mathematical formula}XUpd1, that we use as reference to compare our algorithm that updates protected models. For simplicity, we temporarily ignore some concerns that will be considered in the following sections. We now focus on {a mathematical formula}Σ-XCTL, we do not include an operation for adding states, and we are not concerned about efficiency. {a mathematical formula}XUpd1 (see Fig. 1) is an algorithm similar to generate-and-test methods. First, using basic update operations, {a mathematical formula}XUpd1 generates models to satisfy the simplest subformulas of the given formula. Then, {a mathematical formula}XUpd1 modifies these models to satisfy more complex subformulas. Finally, the produced models are tested to verify whether or not they satisfy the whole formula. The case {a mathematical formula}φ=AXα uses {a mathematical formula}XUpd1⁎, a procedure implementing {a mathematical formula}Modif⁎(M,S′,φ).
      </paragraph>
      <paragraph>
       By using fixed-point characterizations (Section 2) and a mechanism for detecting loops (see Section 3.5), {a mathematical formula}XUpd1(M,s,φ) may be extended to an algorithm {a mathematical formula}Upd1 to compute {a mathematical formula}Modif(M,s,φ) for {a mathematical formula}φ∈Σ-CTL. This extension is analogous to that of Section 3.5.
      </paragraph>
      <paragraph>
       Note that line (12) of {a mathematical formula}XUpd1 is necessary to guarantee that the returned model, {a mathematical formula}M′, meets the requirement {a mathematical formula}M′,s⊨φ in three cases of φ[5].
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       An algorithm for updating protected models
      </section-title>
      <paragraph>
       Intuitively, a call to {a mathematical formula}XUpdprot((M,P),s,φ) gradually transforms {a mathematical formula}M attempting to satisfy the subformulas of φ. Models {a mathematical formula}M′ produced by {a mathematical formula}XUpdprot to satisfy a subformula ψ are accompanied by a protection{a mathematical formula}P′ containing a part of {a mathematical formula}M′ sufficient to satisfy ψ. In this case, we will say that {a mathematical formula}M′is protected by{a mathematical formula}P′. A key feature of {a mathematical formula}XUpdprot is that if {a mathematical formula}M is protected by P and {a mathematical formula}XUpdprot((M,P),s,ψ) produces {a mathematical formula}(M′,P′), then {a mathematical formula}M′ is protected by {a mathematical formula}P′ and {a mathematical formula}P′ is a protection greater than or equal to P (Definition A.1). Hence, {a mathematical formula}XUpdprot preserves satisfaction of previously treated subformulas.
      </paragraph>
      <paragraph label="Definition 3.3">
       Protected update operationsLet {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s,s′∈SM, {a mathematical formula}ℓ∈Lit(VΣ), {a mathematical formula}S′⊆SM, and {a mathematical formula}S″≠∅ a finite set. The update operations on protected models are:
      </paragraph>
      <list>
       <list-item label="1.">
        Update ℓ and protect ℓ.{a mathematical formula}Lu((M,P),s,ℓ)=(Lu(M,s,ℓ),〈EP,AP,LP[s⊕ℓ]〉) if {a mathematical formula}ℓ¯∉LP(s).
       </list-item>
       <list-item label="2.">
        Add {a mathematical formula}(s,s′) to {a mathematical formula}M and add {a mathematical formula}(s,s′) to {a mathematical formula}EP.{a mathematical formula}T∃+((M,P),s,s′)=(T+(M,s,s′),〈EP∪{(s,s′)},AP,LP〉) if {a mathematical formula}s′∈AP[s].
       </list-item>
       <list-item label="3.">
        Replace {a mathematical formula}RM[s] and {a mathematical formula}AP[s] by {a mathematical formula}S′.{a mathematical formula}T∀u((M,P),s,S′)=(Tu(M,s,S′),〈EP,AP−({s}×(AP[s]−S′)),LP〉) if {a mathematical formula}EP[s]⊆S′⊆AP[s] and {a mathematical formula}S′≠∅.
       </list-item>
       <list-item label="4.">
        Replace {a mathematical formula}RM[s] and {a mathematical formula}EP[s] by {a mathematical formula}S′.{a mathematical formula}T∃u((M,P),s,S′)=(Tu(M,s,S′),〈EP∪({s}×(S′−EP[s])),AP,LP〉) if {a mathematical formula}EP[s]⊆S′⊆AP[s] and {a mathematical formula}S′≠∅.
       </list-item>
       <list-item label="5.">
        Add {a mathematical formula}S″ to {a mathematical formula}M and extend {a mathematical formula}AP and {a mathematical formula}LP.{a mathematical formula}S∀+((M,P),S″)=(S+(M,S″),〈EP,AP∪(SM×S″)∪(S″×(SM∪S″)),LP∪∅S″〉) if {a mathematical formula}S″∩SM=∅.
       </list-item>
      </list>
      <paragraph>
       Since the above are partial functions, we assume that their application in cases not covered by the corresponding definitions produces an undefined value (⊥). Note that all above operations, except {a mathematical formula}S∀+, preserve the signature Σ.
      </paragraph>
      <paragraph>
       We extend to protected models our definition of modification of a model.
      </paragraph>
      <paragraph label="Definition 3.4">
       {a mathematical formula}Modifications of (M,P) w.r.t.φIf {a mathematical formula}(M,P)∈KPΣ is a protected model, {a mathematical formula}s∈SM and {a mathematical formula}φ∈Σ-XCTL, we define, by recursion on φ, the set of modifications of{a mathematical formula}(M,P)w.r.t. φ at s, {a mathematical formula}Modif((M,P),s,φ):
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Modif((M,P),s,F)=∅ and {a mathematical formula}Modif((M,P),s,T)={(M,P)}
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Modif((M,P),s,ℓ)={Lu((M,P),s,ℓ)}
       </list-item>
       <list-item label="3.">
        {a mathematical formula}Modif((M,P),s,α∨β)=Modif((M,P),s,α)∪Modif((M,P),s,β)
       </list-item>
       <list-item label="4.">
        {a mathematical formula}Modif((M,P),s,α∧β)={(M′,P′)∈KPΣ|∃(Mα,Pα)∈Modif((M,P),s,α).(M′,P′)∈Modif((Mα,Pα),s,β)}
       </list-item>
       <list-item label="5.">
        {a mathematical formula}Modif((M,P),s,EXα)={(M′,P′)∈KPΣ|∃s′∈AP[s].(M′,P′)∈Modif(T∃+((M,P),s,s′),s′,α)}
       </list-item>
       <list-item label="6.">
        {a mathematical formula}Modif((M,P),s,AXα)={(M′,P′)∈KPΣ|∃S′⊆AP[s].EP[s]⊆S′≠∅&amp;(M′,P′)∈Modif⁎(T∀u((M,P),s,S′),S′,α)}
       </list-item>
       <list-item label="7.">
        {a mathematical formula}Modif((M,P),s,OD⊙n)={(M′,P′)∈KPΣ|∃S′⊆AP[s].EP[s]⊆S′≠∅&amp;|S′|⊙n&amp;(M′,P′)=TQu((M,P),s,S′)}for {a mathematical formula}⊙∈{⩽,&gt;}; {a mathematical formula}Q=∀ if {a mathematical formula}⊙∈{⩽}, and {a mathematical formula}Q=∃ if {a mathematical formula}⊙∈{&gt;}
       </list-item>
      </list>
      <paragraph>
       In Fig. 2, we define an algorithm for updating protected models. Intuitively, {a mathematical formula}XUpdprot((M,P),s,φ) finds models for φ at state s by modifying {a mathematical formula}M and respecting the protection P. The initial call to {a mathematical formula}XUpdprot may use the empty protection {a mathematical formula}P⊥. The case {a mathematical formula}φ=AXα uses {a mathematical formula}XUpdprot⁎, a procedure implementing {a mathematical formula}Modif⁎((M,P),S′,φ).
      </paragraph>
      <paragraph>
       Observe that {a mathematical formula}XUpdprot does not need a verification similar to the verification in line (12) of {a mathematical formula}XUpd1. Protections guarantee that the returned model, {a mathematical formula}(M′,P′), meets the requirement {a mathematical formula}(M′,P′),s⊨φ. First, such a requirement is fulfilled when {a mathematical formula}XUpdprot is applied to basic formulas ({a mathematical formula}T, ℓ, OD). Then, subsequent applications of {a mathematical formula}XUpdprot use the current protection to preserve the satisfaction of previously treated subformulas. For a comparison between {a mathematical formula}XUpdprot and {a mathematical formula}XUpd1, see Section 5.
      </paragraph>
     </section>
     <section label="3.5">
      Model update for {a mathematical formula}Σ-CTL and addition of states
      <paragraph>
       We extend {a mathematical formula}XUpdprot to formulas that use the operators EU, AU, ER, and AR. These operators are replaced by their fixed-point characterizations (Section 2) and then treated by a mechanism for detecting loops. This loop-detecting mechanism is controlled by a parameter {a mathematical formula}Q⊆SM×Σ-CTL. The intuition behind Q is that if {a mathematical formula}(s,ψ)∈Q, then state s has already been visited while updating w.r.t.  ψ. {a mathematical formula}Updprot, depicted in Fig. 3, illustrates how to modify the pseudo-code in the cases of EU and AR; the modifications for AU and ER are similar. The initial call to {a mathematical formula}Updprot uses an empty set of visited states.
      </paragraph>
      <paragraph>
       A state addition is only necessary when a model update fails to find a model with a given signature. For example, if {a mathematical formula}Σ=〈{s0},{p}〉, {a mathematical formula}(M,P) is any protected Σ-model, and {a mathematical formula}φ=EXp∧EX¬p, then {a mathematical formula}XUpdprot[(M,P),s0,φ]=∅. In this case, and assuming that {a mathematical formula}n=|φ|, we can extend our model update procedure so as to be able to add states to {a mathematical formula}M until {a mathematical formula}XUpdprot[(M,P),s,φ]≠∅ or {a mathematical formula}|SM|&gt;n8n. This bound on the number of states is justified by a small model theorem for CTL[16, p. 9]: if φ is satisfiable then φ is satisfiable in a model of size less than or equal to {a mathematical formula}n8n, where the size of a model {a mathematical formula}M is {a mathematical formula}|SM|[16, p. 4]. In Fig. 4, {a mathematical formula}XUpdS+ shows how to add states in the update process.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Heuristics and search strategies
     </section-title>
     <paragraph>
      A significant feature of {a mathematical formula}Updprot (and {a mathematical formula}Upd1) is nondeterminism. Direct deterministic implementations of nondeterministic algorithms, however, may suffer from inefficiency. To improve the efficiency of {a mathematical formula}Updprot, we propose heuristics based on an order on the generation of nondeterministic choices from: (1) a set of states, (2) a set of sets of states, and (3) a set of two CTL formulas. To find minimal solutions we propose a search strategy similar to iterative deepening.
     </paragraph>
     <paragraph>
      For practical purposes, we make some assumptions. We assume that a finite set A is represented by a list, {a mathematical formula}[A], containing the elements of A in an arbitrary order, e.g., {a mathematical formula}[A]=[a1,a2,…,an]. We also assume that the command guess {a mathematical formula}x∈[A] produces nondeterministic choices in the order of {a mathematical formula}[A], i.e., the first choice is {a mathematical formula}a1, then {a mathematical formula}a2 and so on. We use + and Σ to represent the concatenation of two lists and the concatenation of a finite sequence of lists, respectively. Under these assumptions, we show how to improve the efficiency of {a mathematical formula}XUpd1(M,s,φ) in cases where {a mathematical formula}φ=EXα, {a mathematical formula}φ=AXα, or {a mathematical formula}φ=α∨β (improvements for {a mathematical formula}XUpdprot are analogous).
     </paragraph>
     <section label="4.1">
      <section-title>
       Ordering nondeterministic choices of states
      </section-title>
      <paragraph>
       To improve the efficiency of {a mathematical formula}XUpd1(M,s,EXα) we use an order on the generation of nondeterministic choices of states. In line (7) of {a mathematical formula}XUpd1, we replace the command “{a mathematical formula}guesss′∈SM” by “{a mathematical formula}guesss′∈[RM[s]]+[SM−RM[s]]”. Thus, the first nondeterministic choices will be elements of {a mathematical formula}RM[s].
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Ordering nondeterministic choices of sets of states
      </section-title>
      <paragraph>
       To improve the efficiency of {a mathematical formula}XUpd1(M,s,AXα) we use an order on the generation of nondeterministic choices of sets of states. Let {a mathematical formula}m=|SM|, and for {a mathematical formula}i=0,…,m, let {a mathematical formula}Qi(M,s)={S′⊆SM|S′≠∅&amp;|Δ(S′,RM[s])|=i}. Therefore, if {a mathematical formula}S′∈Qi(M,s) then {a mathematical formula}d(Tu(M,s,S′),M)=i.
      </paragraph>
      <paragraph>
       It can be shown that the elements of {a mathematical formula}∑i=0m[Qi(M,s)] are lists representing the nonempty subsets of {a mathematical formula}SM. Besides, if {a mathematical formula}S1 and {a mathematical formula}S2 are two elements of the list {a mathematical formula}∑i=0m[Qi(M,s)] and {a mathematical formula}S1 occurs before {a mathematical formula}S2 in such a list, then {a mathematical formula}d(Tu(M,s,S1),M)⩽d(Tu(M,s,S2),M).
      </paragraph>
      <paragraph>
       In line (8) of {a mathematical formula}XUpd1, we replace the command “{a mathematical formula}guessS′∈2SM−{∅}” by “{a mathematical formula}guessS′∈∑i=0m[Qi(M,s)]”.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Ordering nondeterministic choices of formulas
      </section-title>
      <paragraph>
       To improve the efficiency of {a mathematical formula}XUpd1(M,s,α∨β) we use an order on the generation of nondeterministic choices of CTL formulas. In line (5) of {a mathematical formula}XUpd1, we replace the command “{a mathematical formula}guessδ∈{α,β}” by “{a mathematical formula}guessδ∈[δ1,δ2]”, where {a mathematical formula}δ1=α, {a mathematical formula}δ2=β if {a mathematical formula}|α|⩽|β|, and {a mathematical formula}δ1=β, {a mathematical formula}δ2=α otherwise.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Limiting the number of changes
      </section-title>
      <paragraph>
       Besides improving efficiency, the above heuristics help {a mathematical formula}Updprot to produce first models close to the input model. The above heuristics, however, do not ensure that {a mathematical formula}Updprot produces first minimal solutions. Therefore, for cases requiring a minimal solution, we propose a variant of {a mathematical formula}Updprot, {a mathematical formula}Updmin, that uses a search strategy similar to iterative deepening.
      </paragraph>
      <paragraph>
       We get an implementation of {a mathematical formula}Updmin by modifying {a mathematical formula}Updprot as follows. First, we add to {a mathematical formula}Updprot a parameter, n, to record the number of changes applied to the input model. We also include a variable, w, to fix the maximum number of changes allowed. Second, we modify {a mathematical formula}Updprot to compute the number of changes required, r, before applying an update operation. Third, we modify {a mathematical formula}Updprot to halt if {a mathematical formula}n+r&gt;w, i.e., {a mathematical formula}Updprot halts if the number of changes already made, plus the number of changes to apply, is greater than the number of changes allowed. Finally, to produce first the minimal solutions, we initialize w to zero and we iterate {a mathematical formula}Updprot, increasing w by 1, until {a mathematical formula}Updprot produces a solution.
      </paragraph>
     </section>
    </section>
    <section label="5">
     Behavior of {a mathematical formula}Updprot
     <paragraph>
      We illustrate the behavior of {a mathematical formula}Updprot with several examples, including a classical mutual exclusion problem and models with hundreds of states. We show other examples at the web site of {a mathematical formula}Updprot, http://turing.iimas.unam.mx/ctl_upd3/form1.prl.
     </paragraph>
     <section label="5.1">
      <section-title>
       Synthesizing a model of the mutual exclusion problem
      </section-title>
      <paragraph>
       Emerson and Clarke [15] present a method for automatically synthesizing synchronization skeletons, from a CTL specification, through a decision procedure that constructs a model of the specification. We use Emerson and Clarke's mutual-exclusion example to show that our CTL update method can also be used as a decision procedure for satisfiability of CTL formulas.
      </paragraph>
      <paragraph>
       The specification of the mutual exclusion problem by Emerson and Clarke uses a variant of CTL with processes[15]. We adapt such a specification to a specification Γ in {a mathematical formula}Σ-CTL. The specification Γ is the result of factoring AG in the conjunction of the following formulas, where {a mathematical formula}i,j∈{1,2} and {a mathematical formula}i≠j:
      </paragraph>
      <list>
       <list-item label="1.">
        Start state. Both processes are in their noncritical region: {a mathematical formula}(n1∧n2)
       </list-item>
       <list-item label="2.">
        Each process i is always exactly in one of the three code regions:{a mathematical formula}AG((ni∨ti∨ci)∧(ni→¬(ti∨ci))∧(ti→¬(ni∨ci))∧(ci→¬(ni∨ti)))
       </list-item>
       <list-item label="3.">
        Any move that process i makes from its noncritical (critical) region is into its trying (noncritical) region, and such a move is always possible:{a mathematical formula}AG((ni→((AX(ti∨ni))∧(EXti)))∧(ci→((AX(ni∨ci))∧(EXni))))
       </list-item>
       <list-item label="4.">
        Any move that process i makes from its trying region is into its critical region and such a move is possible when it is the turn of process i:{a mathematical formula}AG((ti→(AX(ci∨ni)))∧((ti∧turni)→(EXci)))
       </list-item>
       <list-item label="5.">
        A transition by one process cannot cause the other process to move. If process i is in region {a mathematical formula}ri∈{ni,ti,ci} and process j moves, then i remains in {a mathematical formula}ri:{a mathematical formula}AG(((ri∧nj)→(AX(tj→ri)))∧((ri∧tj)→(AX(cj→ri)))∧((ri∧cj)→(AX(nj→ri))))
       </list-item>
       <list-item label="6.">
        Some process can always move. If some process is in its noncritical region then both processes can move; otherwise only one process can move:{a mathematical formula}AG(((n1∨n2)→(turn1∧turn2))∧((¬n1∧¬n2)→(turn1⊻turn2)))
       </list-item>
       <list-item label="7.">
        Each transition is due to the movement of exactly one process:{a mathematical formula}AG(((turn1∧turn2)→(OD⩽2))∧((¬turn1∨¬turn2)→(OD⩽1)))
       </list-item>
       <list-item label="8.">
        Split state {a mathematical formula}s=(t1,t2,turn1,turn2) into states {a mathematical formula}(t1,t2,turn1,¬turn2) and {a mathematical formula}(t1,t2,¬turn1,turn2) and separate the transitions going towards s. This requirement reflects a preference of Emerson and Clarke to distinguish all states by their propositional labels [15, p. 258]:{a mathematical formula}AG((ti∧nj)→(EX(tj∧turni)))
       </list-item>
      </list>
      <paragraph>
       Note that, in the specification Γ, we only use formulas to specify the local structure of the system, through the operators AX and EX and an outermost operator AG. We do not include formulas to specify global behavior of the system by using operators {a mathematical formula}F,G,U, or R. Global behavior formulas, for example {a mathematical formula}AG(ti→EFci) and {a mathematical formula}AG¬EF(c1∧c2), are generally expected to be a consequence of formulas specifying local structure. Intuitively, it is relatively easier to synthesize a model from formulas specifying local structure than to synthesize a model from formulas specifying global behavior. Global behavior formulas can be used instead to update a faulty model, presumably close to a correct model. A difference between model synthesis and model update is related to the difference between these two kinds of formula.
      </paragraph>
      <paragraph>
       In Table 1, we compare {a mathematical formula}Upd1 and {a mathematical formula}Updprot in the repair of faulty models of mutual exclusion w.r.t. Γ. Column N indicates the number of changes needed to repair the model. Input models were obtained by removing, according to the marks ✗, transitions {a mathematical formula}(si,sj) and labels {a mathematical formula}ni in {a mathematical formula}sj, from the model in Fig. 5. A mark ✗  in column D means that the input model is the dummy model in Fig. 6. Columns -cN restrict the search to a maximum of N changes. Columns -c? record searches with an unlimited number of changes. Entries “—” mean “no answer after one hour”. The last four columns show the time, in seconds, necessary to produce the first solution on a PC with a dual-core processor at 2.0 GHz and 2 GB of RAM.
      </paragraph>
      <paragraph>
       Table 1 shows tests where we gradually removed some parts of the model in Fig. 5. Observe that the more parts were removed, the more time {a mathematical formula}Upd1 required to produce a solution. The option -cN helped both {a mathematical formula}Upd1 and {a mathematical formula}Updprot to limit the search for solutions to models that result from applying at most N changes to the input model. Note that even with the aid of the switch -cN, {a mathematical formula}Upd1 was incapable of computing a first solution after one hour.
      </paragraph>
      <paragraph>
       By using the specification Γ, the first solution produced by {a mathematical formula}Updprot from the dummy model in Fig. 6 is the model in Fig. 5, having the expected structure [15, Fig. 11, p. 259]. This happened after 16.4 s (Table 1).
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Updating a microwave oven model
      </section-title>
      <paragraph>
       In Section 5.1, we showed that the application of {a mathematical formula}Updprot to a dummy model can build a model that satisfies a given formula. We now assume that the non-dummy model in Fig. 7, {a mathematical formula}Moven, is given. Clarke et al. [11] use {a mathematical formula}Moven to illustrate the model-checking technique and, following Zhang and Ding [22], we use {a mathematical formula}Moven to show the application of {a mathematical formula}Updprot in the update of (modifications of) {a mathematical formula}Moven w.r.t. some given formulas.
      </paragraph>
      <paragraph>
       The intuition behind {a mathematical formula}Moven is an informal specification of the oven operation:
      </paragraph>
      <list>
       <list-item label="1.">
        Open the door and put the food inside ({a mathematical formula}→s0).
       </list-item>
       <list-item label="2.">
        Close the door ({a mathematical formula}s0→s2).
       </list-item>
       <list-item label="3.">
        Press START ({a mathematical formula}s2→s5) to begin the warming of the oven ({a mathematical formula}s5→s6).
       </list-item>
       <list-item label="4.">
        After warming, cooking starts automatically ({a mathematical formula}s6→s3).
       </list-item>
       <list-item label="5.">
        When cooking is finished, the heat is turned off ({a mathematical formula}s3→s2).
       </list-item>
       <list-item label="6.">
        While cooking, the door may be opened ({a mathematical formula}s3→s0).
       </list-item>
       <list-item label="7.">
        Pressing START while the door is open produces an error ({a mathematical formula}s0→s1).
       </list-item>
       <list-item label="8.">
        On error, close the door ({a mathematical formula}s1→s4) and press RESET ({a mathematical formula}s4→s2).
       </list-item>
      </list>
      <paragraph>
       We formalize the above informal specification of the microwave oven by a CTL formula Ψ. The formula Ψ is the result of factoring AG in the conjunction of the following formulas:
      </paragraph>
      <list>
       <list-item label="1.">
        Initial state:{a mathematical formula}Ψ1=(¬start∧¬close∧¬heat∧¬error)
       </list-item>
       <list-item label="2.">
        At any time, if the door is open, it may be closed:{a mathematical formula}Ψ2=AG(¬close→EXclose)
       </list-item>
       <list-item label="3.">
        If the heat is off, START may be pressed:{a mathematical formula}Ψ3=AG((¬start∧¬heat)→EXstart)
       </list-item>
       <list-item label="4.">
        If START is pressed and there is no error, warming may start:{a mathematical formula}Ψ4=AG((start∧close∧¬heat∧¬error)→EX(start∧heat))
       </list-item>
       <list-item label="5.">
        After warming, cooking may begin:{a mathematical formula}Ψ5=AG((start∧heat)→EX(¬start∧heat))
       </list-item>
       <list-item label="6.">
        While cooking, the heat may be turned off (by elapsed time):{a mathematical formula}Ψ6=AG((¬start∧heat)→EX(close∧¬heat))
       </list-item>
       <list-item label="7.">
        While cooking, the door may be opened:{a mathematical formula}Ψ7=AG((¬start∧heat)→EX¬close)
       </list-item>
       <list-item label="8.">
        If START is pressed and the door is open, an immediate error occurs:{a mathematical formula}Ψ8=AG((start∧¬close)→error)
       </list-item>
       <list-item label="9.">
        On error, if the door is open, the error persists:{a mathematical formula}Ψ9=AG((error∧¬close)→AXerror)
       </list-item>
       <list-item label="10.">
        On error, if the door is closed, the oven may be reset:{a mathematical formula}Ψ10=AG((error∧close)→EX(¬start∧close))
       </list-item>
      </list>
      <paragraph>
       Unlike the example in Section 5.1, {a mathematical formula}Moven (Fig. 7) is not characterized by the specification Ψ, but it can be proved that {a mathematical formula}Moven satisfies Ψ at {a mathematical formula}s0. Besides, {a mathematical formula}Moven does not satisfy at {a mathematical formula}s0 a formula expressing that if START is pressed, then the heat will eventually be turned on, {a mathematical formula}ρ1=AG(start→AFheat).
      </paragraph>
      <paragraph>
       In Table 2, we show results of tests comparing {a mathematical formula}Upd1 and {a mathematical formula}Updprot in the repair of modifications of {a mathematical formula}Moven. Input models for these tests were obtained by modifying {a mathematical formula}Moven according to the changes indicated in column “Modifications”. We use {a mathematical formula}t,c,h, and e as shorthand for variables start, close, heat and error, respectively. Given {a mathematical formula}x∈{t,c,h,e}, a modification ix complements the label x in the state {a mathematical formula}si. A modification ij adds the transition {a mathematical formula}(si,sj) to {a mathematical formula}Moven if {a mathematical formula}(si,sj)∉RMoven, otherwise ij removes {a mathematical formula}(si,sj) from {a mathematical formula}Moven. Column φ shows the formula used for updating the input model. For {a mathematical formula}j⩾0, {a mathematical formula}φj=ρ1∧(⋀i=1jΨi). We designed modifications so that the modification of {a mathematical formula}Moven in row {a mathematical formula}φj does not satisfy {a mathematical formula}⋀i=1jΨi. Columns -cm and -c? show time (in seconds) necessary to produce a first solution. Columns -cm show solutions with a search restricted to a maximum of m changes. Columns -c? record solutions of searches with an unlimited number of changes, i.e., without using m. Columns n indicate the number of changes needed to generate a first solution with the option -c?. Column m, computed by {a mathematical formula}Updmin, is the minimum number of changes needed to repair the input model. Entries “—” mean “no answer after 600 s”. The initial protection in the execution of {a mathematical formula}Updmin and {a mathematical formula}Updprot was {a mathematical formula}P⊥. These tests were performed on a PC with a quad-core processor at 2.0 GHz and 8 GB of RAM.
      </paragraph>
      <paragraph>
       We gradually removed some parts of {a mathematical formula}Moven and gradually augmented the complexity of the input formula. Observe that the more parts were removed, {a mathematical formula}Upd1 required more (or the same) time to produce a solution. Intuitively, the option -cm helps both {a mathematical formula}Upd1 and {a mathematical formula}Updprot because it restricts the search space to the set of models that result from applying at most m changes.
      </paragraph>
      <paragraph>
       Remark that in the update of {a mathematical formula}Moven w.r.t. {a mathematical formula}ρ1, both {a mathematical formula}Upd1 and {a mathematical formula}Updprot produced a first solution in less than one second, even without the aid provided by a limit on the number of changes (Table 2). Thus, {a mathematical formula}Upd1 and {a mathematical formula}Updprot had a similar performance when updating {a mathematical formula}Moven w.r.t. {a mathematical formula}ρ1. Unlike {a mathematical formula}Updprot, however, an update through {a mathematical formula}Upd1 may cause {a mathematical formula}Moven to lose some of its properties, for example satisfying (parts of) the specification Ψ. Indeed, the first solution of {a mathematical formula}Upd1(Moven,s0,ρ1) does not satisfy Ψ. Even worse, many of the first solutions of {a mathematical formula}Upd1(Moven,s0,ρ1) do not satisfy Ψ, as can be inferred from the running time of {a mathematical formula}Upd1(Moven,s0,φ10) (Table 2).
      </paragraph>
      <paragraph>
       In practice, a formula used to update a given model is usually more complex than {a mathematical formula}ρ1. A formula for a model update may include subformulas expressing properties that motivated the design of the model, i.e., a model specification (e.g., Ψ).
      </paragraph>
      <paragraph>
       Note that {a mathematical formula}ρ1 expresses an undesirable property. If {a mathematical formula}Moven satisfied {a mathematical formula}ρ1, then the heat could be turned on with the door open and thus harm the user. Following [22], we considered an update of {a mathematical formula}Moven to satisfy {a mathematical formula}ρ1 at {a mathematical formula}s0.
      </paragraph>
      <paragraph>
       Column -c? of {a mathematical formula}Upd1 of Table 2 shows that, without the help of m, {a mathematical formula}Upd1 can produce an answer in less than 600 s only in the case of formula {a mathematical formula}ρ1. In contrast, all the corresponding answers of {a mathematical formula}Updprot are produced in less than one second.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Updating the model of a counter
      </section-title>
      <paragraph>
       The next example exhibits the behavior of {a mathematical formula}Updprot in a readily scalable problem: a synchronous counter. Nondeterminism is reflected as an external input making the counter either count or halt. Each state has exactly two successors, intended to represent a system with two successors per state on average. Instead of making the counter halt immediately, we ask it to eventually halt, making our example more representative of typical model-checking uses, where a property is required to eventually hold.
      </paragraph>
      <paragraph>
       A specification of an n-bit synchronous counter is the conjunction of the formulas below, where {a mathematical formula}i∈{0,…,n−1}:
      </paragraph>
      <list>
       <list-item label="1.">
        Each state has exactly two successors: {a mathematical formula}OD⩽2∧OD&gt;1.
       </list-item>
       <list-item label="2.">
        If the input is “count” (¬h) and either the bit i is on or the i least-significant bits are on, then the bit i will be on. Otherwise the bit i will be off (two formulas for each i):{a mathematical formula}(¬h∧(xi⊻(x0∧⋯∧xi−1)))→AXxi{a mathematical formula}¬(¬h∧(xi⊻(x0∧⋯∧xi−1)))→AX¬xiBy convention {a mathematical formula}(x0⊻(x0∧⋯∧x0−1))=¬x0.
       </list-item>
       <list-item label="3.">
        If a state having all its bits off is reached when not counting (h), then the counter remains there:{a mathematical formula}(h∧¬x0∧⋯∧¬xn−1)→AX(¬x0∧⋯∧¬xn−1)
       </list-item>
       <list-item label="4.">
        When not counting, the counter eventually reaches a state having all its bits off:{a mathematical formula}h→A[hU¬x0∧⋯∧¬xn−1]
       </list-item>
      </list>
      <paragraph>
       In this example, we will assume that we wish the state labels to remain fixed, and will update the transitions only. This can be readily achieved in {a mathematical formula}Updprot with an initial protection protecting all the labels. In {a mathematical formula}Upd1, we can simply inhibit the fragment code that modifies labels. Note also that the specification must hold at all states.
      </paragraph>
      <paragraph>
       Input models were obtained by intentionally modifying a model satisfying the specification with either the removal of correct transitions of the addition of wrong transitions. The wrong transitions added are self-loops, so that if all correct transitions are removed and all states have loops, we obtain the dummy model as input model, representing the worst of cases.
      </paragraph>
      <paragraph>
       Table 3 shows the time, in seconds, taken by {a mathematical formula}Updprot to obtain a synchronous counter from the specification for different faulty models. ({a mathematical formula}Upd1 took more than one hour even for the simplest (i.e., the first) instance on the table.) The columns labeled “states” have the number of states resulting from considering the bits of the counter itself in addition to the control bit h. The columns labeled “trans. removed” indicate the number of transitions removed from the correct model. The columns labeled “loops added” indicate the number of loops added. The lines in boldface refer to dummy models.
      </paragraph>
      <paragraph>
       The tests were done on a PC with a dual-core processor at 2.0 GHz and 2 GB of RAM.
      </paragraph>
      <paragraph>
       Although current model checking practice often employs models with a vast number of states, the fact that {a mathematical formula}Updprot can handle some examples with hundreds of states shows that our method could at least be useful for abstractions of systems.
      </paragraph>
     </section>
     <section label="5.4">
      {a mathematical formula}Updprot applied to random models and formulas
      <paragraph>
       Here we show the behavior of {a mathematical formula}Updprot when applied to randomly generated models and formulas. Table 4 (left) shows the application of {a mathematical formula}Updprot to a random model, M, generated with 10 variables, 1024 states and 2048 transitions. We applied {a mathematical formula}Updprot to update M w.r.t. random formulas that were generated with the operators listed in the first column. All formulas in this column were generated with a set of operators containing 10 ∨, 10 ∧, 10 EX, and 10 AX. The formula in the second row was generated by using two additional U operators, one EU and one AU. The formulas in the other rows were similarly generated. Columns “chg” and “time” of Table 4 (left and right) respectively show the number of changes made by {a mathematical formula}Updprot and the running time in seconds. Entries “—” mean “no answer after 600 seconds”. We discarded running times greater than 600 seconds because the formula (left) or the model (right) along the respective model or formula, could be a case of unsatisfiable formula or a case of hard complexity, respectively.
      </paragraph>
      <paragraph>
       Table 4 (right) shows the application of {a mathematical formula}Updprot to a random formula, φ, generated with 10 variables, five operators ∨, five ∧, and one of all other operators (EX, AX, EU, AU, ER, AR, EF, AF, EG, AG). We applied {a mathematical formula}Updprot to update, w.r.t. φ, models that were generated using 10 variables and the number of states and transitions listed respectively in the first two columns.
      </paragraph>
      <paragraph>
       Note that the running times of {a mathematical formula}Updprot in Table 4 are for specific instances of the update problem tackled by {a mathematical formula}Updprot. The running times cannot be as good for all instances because the worst-case complexity of {a mathematical formula}Updprot is exponential w.r.t. the size of φ (see Appendix B). The results in Table 4, however, show that {a mathematical formula}Updprot may have an acceptable performance when applied to models with hundreds of states, without a particular structure, w.r.t. non-simple CTL formulas.
      </paragraph>
     </section>
     <section label="5.5">
      {a mathematical formula}Updprot applied to models with few states
      <paragraph>
       Finally, we mention an example comparing {a mathematical formula}Upd1 and {a mathematical formula}Updprot with a single-state model. This example can be found at the website of {a mathematical formula}Updprot. The formula used in this example was built as follows. First, by using 25 variables, we built a propositional formula φ resulting from the conjunction of 105 clauses with three literals. By construction, φ is satisfiable only by one truth assignment. Then, we transformed φ into a temporal formula {a mathematical formula}φ′ by prefixing every literal of φ with EX. We observe that {a mathematical formula}Updprot updated a dummy one-state model w.r.t. {a mathematical formula}φ′ in less than 30 seconds, while {a mathematical formula}Upd1 did not produce any model after more than one hour. When we changed the model to a two-state dummy model, {a mathematical formula}Updprot produced a solution in less than one second. Of course, a SAT solver can be efficiently solve these problems by using φ instead of {a mathematical formula}φ′. This example, however, shows two points. First, even CTL-update instances with few states can be hard for a CTL updater. Second, an increase in the number of states may reduce the time required by a CTL updater.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In this section, we first give a simple example of the structure of counterexamples for CTL formulas with references to the main work on this issue. Then, we compare our work with other approaches, both for full CTL and for CTL fragments.
     </paragraph>
     <section label="6.1">
      <section-title>
       Structure of counterexamples
      </section-title>
      <paragraph>
       Some of the existing methods for CTL model update are wholly or partially based on counterexamples. Thus, we include here some of the main concepts of counterexamples.
      </paragraph>
      <paragraph>
       In general, existential properties cannot be disproved by counterexamples. Therefore, counterexamples for CTL formulas are limited to ACTL, the universal fragment of CTL where only the path quantifier A is allowed, and negation is restricted to atomic subformulas.
      </paragraph>
      <paragraph>
       Buccafurri et al. [1, p. 25] observe that in many cases a counterexample for an ACTL formula is (essentially) a single path, but there are cases in which a counterexample tree is required. Hence, these authors extend the concept of counterexample presented by Clarke et al. [10] through the introduction of multi-paths as a suitable formalization of counterexample trees.
      </paragraph>
      <paragraph>
       We illustrate multi-paths with a simple example. Suppose {a mathematical formula}M is a Kripke model such that {a mathematical formula}SM={s0,s1,s2}, {a mathematical formula}RM={(s0,s1),(s0,s2),(s1,s1),(s2,s2)}, {a mathematical formula}LM(s0)=∅, {a mathematical formula}LM(s1)={p} and {a mathematical formula}LM(s2)={q}. If {a mathematical formula}φ1=AFp, then {a mathematical formula}π1=[s0,s2,s2,…] is a path having all information needed to explain why {a mathematical formula}M,s0⊭φ1. Thus, the single path {a mathematical formula}π1 is a (linear) counterexample for {a mathematical formula}φ1. Conversely, if {a mathematical formula}φ2=AFAGp, then {a mathematical formula}π1 may help to track down causes of {a mathematical formula}M,s0⊭φ2, but {a mathematical formula}π1 does not have all the information needed to provide an explanation for this failure. A detailed explanation of why {a mathematical formula}M,s0⊭φ2 is contained in a multi-path {a mathematical formula}π2=[π1,π3,π3,…], where {a mathematical formula}π3=[s2,s2,…]. Each element of {a mathematical formula}π2 is a path, π, explaining why {a mathematical formula}M,π(0)⊭AGp. Hence, unlike the single path {a mathematical formula}π1, the multi-path {a mathematical formula}π2 is a counterexample for {a mathematical formula}φ2.
      </paragraph>
      <paragraph>
       Linear counterexamples are preferred for their simplicity and efficient generation through widely used algorithms. Unfortunately, these algorithms are incomplete w.r.t. ACTL because only properties in {a mathematical formula}ACTL∩LTL have linear counterexamples. In addition, it is PSPACE-hard to decide whether a given ACTL formula always admits a linear counterexample [2]. Thus, to construct linear counterexamples, an ACTL model checker must solve an unfeasible problem for detecting those cases where this construction is possible.
      </paragraph>
      <paragraph>
       In a later work, Clarke et al. [9] propose tree-like counterexamples as a class of counterexamples not bearing the inadequacies of linear counterexamples. The class of tree-like counterexamples is complete for AΩ, a logic containing ACTL, i.e., each violation of an ACTL formula is witnessed by a suitable tree-like counterexample [9]. Clarke et al. also provide an efficient algorithm to generate tree-like counterexamples for AΩ.
      </paragraph>
      <paragraph>
       We conclude that, in addition to considering that a formula may have more than one counterexample, update methods based on counterexamples should take into account the structure of the counterexamples.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Other approaches to CTL model update
      </section-title>
      <paragraph>
       We compare our work with other approaches in chronological order of publication: Buccafurri et al. [1], Calzone et al. [3], Zhang and Ding [22], a previous work by us [4], Ding and Hemer [13], Kelly et al. [19] and [20], Guerra and Wassermann [17], and Chatzieleftheriou et al. [7].
      </paragraph>
      <section label="6.2.1">
       <section-title>
        Buccafurri et al.
       </section-title>
       <paragraph>
        Buccafurri et al. [1] develop an update method, employing multi-path counterexamples to generate fewer plausible modifications than those of a naive method. Their method, based on counterexamples, is limited to ACTL.
       </paragraph>
       <paragraph>
        Buccafurri et al.'s method modifies programs composed of collections of processes running in parallel. Such programs are modeled as Kripke models with an asynchronous accessibility relation having interleaving and processes that are synchronized with a fair scheduler. These authors assume a mapping between a program and its corresponding Kripke model. Such a mapping only allows modifications at the Kripke-model level that correspond to modifications at the program level belonging to a repertoire of modifications and respecting the fairness constraints. At the program level, the modifications are of three kinds: (a) negation of the right-hand side of an assignment statement having either “true” or “false” on the right-hand side, (b) change of the variable on the left-hand side of an assignment statement, and (c) the swapping of two consecutive assignment statements. At the Kripke-model level, these modifications correspond to the addition and removal of transitions.
       </paragraph>
       <paragraph>
        Given a counterexample, only statements corresponding to states occurring in such a counterexample are considered for either right-hand side assignment changes or swapping of statements. Similarly, only variables occurring in counterexamples are considered for left-hand side assignment changes. Buccafurri et al. [1] illustrate their method in a mutual-exclusion example, assuming a single error. A naive repair method makes 77 correction attempts, whereas their method makes only 17.
       </paragraph>
       <paragraph>
        As a conclusion, Buccafurri et al.'s method is centered around the use of tree-like counterexamples to reduce the number of correction attempts of a naive repair method.
       </paragraph>
      </section>
      <section label="6.2.2">
       <section-title>
        Calzone et al.
       </section-title>
       <paragraph>
        Calzone et al. [3] present a modeling system, Biocham, able to translate a biochemical network N into a Kripke model {a mathematical formula}MN. If φ is a CTL formula expressing a property of N, and {a mathematical formula}MN does not satisfy φ, then, in some cases of φ, Biocham can generate an update {a mathematical formula}N′ such that {a mathematical formula}MN′ does satisfy φ.
       </paragraph>
       <paragraph>
        Biocham's update algorithm proceeds according to three kinds of CTL formulas: universal formulas contain only non-negated universal operators, existential formulas contain only non-negated existential operators, and unclassified formulas contain both universal and existential operators.
       </paragraph>
       <paragraph>
        If φ is universal, then Biocham uses NuSMV [8] to compute a counterexample. Next, Biocham generates and tests models by deleting transitions occurring in such a counterexample. If φ is existential, then Biocham generates and tests models by adding transitions with a bias taken from the application domain. If φ is unclassified, then Biocham treats φ by deleting and adding transitions. However, the deletions (additions) for satisfying universal (existential) formulas may dissatisfy some existential (universal) or unclassified formulas. Therefore, trying to satisfy the three kinds of formulas, Biocham uses a heuristic: it first treats the existential formulas, then the unclassified ones, and finally the universal ones. If some formulas are dissatisfied by the last step, the process repeats.
       </paragraph>
       <paragraph>
        On the one hand, a drawback of Biocham, compared with our method, is that the use of biases and heuristics makes it incomplete. Another disadvantage is that the use of domain-dependent biases makes it a non-general method. On the other hand, since NuSMV represents models with usually compact binary decision diagrams (BDDs), Biocham is able to process large models [6]. This is a significant advantage of Biocham compared to {a mathematical formula}Updprot or any other extensional updater.
       </paragraph>
      </section>
      <section label="6.2.3">
       <section-title>
        Zhang and Ding
       </section-title>
       <paragraph>
        Zhang and Ding [22] devise a recursive and syntax-directed model-update method w.r.t. CTL formulas that employs “constraints”. Constraints appear in the treatment of conjunction {a mathematical formula}α∧β, which is performed as follows (see Fig. 8). First Zhang and Ding's algorithm updates the input model w.r.t. α. Then such an algorithm updates the models obtained when treating α to produce models satisfying β, using α as a constraint.
       </paragraph>
       <paragraph>
        The treatment of constraints is described in Fig. 9: Candidate models are simply model-checked w.r.t. the input constraints. If a model satisfying the constraints is found, such a model is returned; otherwise, Zhang and Ding's algorithm looks for another model.
       </paragraph>
       <paragraph>
        Let us compare the treatment of conjunction of Zhang and Ding's {a mathematical formula}Update∧ (Fig. 8) with that of our generate-and-test {a mathematical formula}XUpd1 (Section 3.3). Observe that {a mathematical formula}Update∧ employs the first conjunct α of a conjunction {a mathematical formula}α∧β as a constraint for repeatedly updating w.r.t. β until a candidate model satisfying α is found. Next note that when dealing with conjunction, our {a mathematical formula}XUpd1 model-checks the candidate models (line 12) resulting from updating w.r.t. a conjunction {a mathematical formula}α∧β until a model satisfying such a conjunction is found (or failure occurs), hence also model-checking w.r.t. α the models that were obtained when treating β. Consequently, the treatments by Zhang and Ding's {a mathematical formula}Update∧ and our {a mathematical formula}XUpd1 of formulas of the form {a mathematical formula}α∧β are similar to each other. In comparison, {a mathematical formula}Updprot does not verify that an update w.r.t. β satisfies α.
       </paragraph>
       <paragraph>
        Zhang and Ding [22, Theorem 8] assert that “{a mathematical formula}CTLUpdate((M,s0),ϕ) terminates and generates an admissible model to satisfy ϕ”. However, there is no guarantee that {a mathematical formula}CTLUpdate((M,s0),ϕ) generates all possible “admissible” models [17]. By contrast, we prove that {a mathematical formula}XUpdprot is sound and complete (Appendix A). Besides, Zhang and Ding's algorithm is less clear than {a mathematical formula}Updprot because it uses an operator base ({a mathematical formula}{EX,AF,EU}) more appropriate for model checking than for model update. For example, it is not clear how Zhang and Ding's algorithm updates a model to satisfy any of the formulas AXα, EFα, or {a mathematical formula}A[αUβ].
       </paragraph>
      </section>
      <section label="6.2.4">
       <section-title>
        Carrillo and Rosenblueth
       </section-title>
       <paragraph>
        In another work [4], we extend a former version of {a mathematical formula}Updprot so as to update a concise representation of a Kripke model instead of the Kripke model itself. This former version of {a mathematical formula}Updprot is also based on protections, but the universal protection is different from the one we developed here. Instead of consisting of the set of transitions that we can add, as happens in {a mathematical formula}Updprot, this former universal protection is a set of (state, formula)-pairs meant for preserving the truth value of already-treated AX subformulas. Recall that for AXα to hold at {a mathematical formula}s0, α must hold at all successors of {a mathematical formula}s0. By recording a pair of the form {a mathematical formula}(s0,α), it is possible to accompany the addition of a successor of {a mathematical formula}s0 with an invocation to the update algorithm so that α holds at the new successor of {a mathematical formula}s0. The recording of {a mathematical formula}(s0,α) hence allows this method to avoid having to update the old successors again, as would happen in a generate-and-test method. The protections used in [4], however, are unsatisfactory because it is unclear if the resulting algorithm is complete.
       </paragraph>
       <paragraph>
        To achieve a good scaling, this state-by-state method is extended with a concise representation of Kripke models, which can be viewed as a simplification of SMV's model-description language. The next value {a mathematical formula}xi′ of a variable {a mathematical formula}xi is defined by a function {a mathematical formula}fi:S→P({0,1})−{∅}, which can be written with a number of abbreviations, including a default value. In addition, [4] provides operations modifying such descriptions of Kripke models. It remains to explore the possibility of extending {a mathematical formula}Updprot to such descriptions possibly achieving a better scaling than {a mathematical formula}Updprot.
       </paragraph>
      </section>
      <section label="6.2.5">
       <section-title>
        Ding and Hemer
       </section-title>
       <paragraph>
        Ding and Hemer [13] make an improvement over [12], [22] in the treatment of formulas of the form AGφ, where φ is a propositional formula. Such an improvement produces fewer candidate models than the method in Ding's thesis [12]. Essentially, the original method of [12] preserves existing paths between an initial state and an arbitrary state. The improved method [13], by contrast, preserves existing paths between any two states. Ding and Hemer apply their improved update method to a cache coherence protocol for the Andrew file system (AFS-1) [21], and generate 125 candidate models, instead of 225.
       </paragraph>
       <paragraph>
        As [13] is an improvement over [22], we must now evaluate [13]. In the AFS-1 example, Ding [12] gives as input to the updater a Kripke model and a formula:{a mathematical formula} which is false in the input Kripke model. Note that this formula represents an undesired property, and is included in [21] only to illustrate SMV's counterexamples. Hence, the produced models have an undesired property. Ding [12, p. 100], however, observes that: “[…] after our model updating, we do not need to consider the logic outcome of the updated models under the false specification property.”
       </paragraph>
       <paragraph>
        Moreover, Ding ignores another formula given in [21]:{a mathematical formula} which is true in the input model and represents a desired property. As a result, the produced models may not satisfy (2). If (2) were considered, not only would fewer models be produced, but such models would satisfy a formula representing a desired property. When more properties are given to an updater, even fewer models are generated. For instance, we gave {a mathematical formula}Updprot a complete CTL specification of the input model, together with (1), reducing the number of produced models to zero (the reason is that (1) is not only false in the model, it is also inconsistent with the specification).
       </paragraph>
       <paragraph>
        We conclude that the proliferation of models produced by Ding's updater is not an inherent problem of model update, but rather a consequence of ignoring desired properties. Hence, instead of preferring models preserving existing paths (the reason for which, incidentally, is not justified in [12], [22]), formulas representing desired properties should be considered.
       </paragraph>
      </section>
      <section label="6.2.6">
       <section-title>
        Kelly et al.
       </section-title>
       <paragraph>
        Kelly et al. [19] and Kelly and Zhang [20] present a counterexample-based method for ACTL. They report experiments on the mutual-exclusion problem of [1] and the sliding-window protocol, respectively.
       </paragraph>
       <paragraph>
        Although the authors do not give their algorithm, we know that “[it] was designed with a top down recursive approach with respect to the given model and properties.” [20, p. 16]. In addition, Kelly et al. [19] observe that “when we perform a model update, we may require this update not violate other specified functions (e.g. breaking a deadlock should not violate a liveness in a concurrent program).” [19, p. 138]. For this purpose, a Kripke model is augmented with “actions” labeling transitions, as well as a set of two kinds of deterministic finite-state automaton, meant to encode constraints on the values of variables, and constraints on the precedence of actions within a path, respectively. Each such automata has a distinguished “violation” state. Although Kelly et al. [19] do not describe the construction of the automata, we know that such automata encode “complex constraints that are usually not expressible […] in the form of ACTL (or CTL) formulas.” [19, p. 139]. In the experiments of both [19] and [20], the formulas are of the form AGφ, where φ is a propositional formula. Kelly and Zhang [20] report updates of models with up to 512 states (though apparently the automata were not used for these experiments).
       </paragraph>
      </section>
      <section label="6.2.7">
       <section-title>
        Guerra and Wassermann
       </section-title>
       <paragraph>
        In the next work we cover, Guerra and Wassermann [17] give an algorithm for performing CTL model revision using Zhang and Ding's CTLUpdate. Belief update supposes a dynamic world, and new information represents changes in such a world. Belief revision, by contrast, assumes a static world and the objective is to restore consistency as new information is added.
       </paragraph>
       <paragraph>
        Guerra and Wassermann give the following algorithm for model revision: Let ψ be a belief base and ϕ a new belief. Let S be a set of models initialized to ∅. Models satisfying ψ are enumerated. Models satisfying ψ which also satisfy ϕ are added to S. Models satisfying ψ which do not satisfy ϕ are updated with CTLUpdate and the results are added to S. Finally, Guerra and Wassermann remove the models that are not minimal w.r.t. the models satisfying ψ from the set S.
       </paragraph>
       <paragraph>
        These authors assert that their model-revision algorithm can be more adequate than Zhang and Ding's CTL model update when applied to system modifications in a static context. Since the advantages these authors find over Zhang and Ding's model-update method do not depend on the inner workings of such a method, it seems fair to conclude that Guerra and Wassermann's algorithm would also be preferable to ours for model revision if {a mathematical formula}Updprot were substituted for CTLUpdate.
       </paragraph>
      </section>
      <section label="6.2.8">
       <section-title>
        Chatzieleftheriou et al.
       </section-title>
       <paragraph>
        Finally, Chatzieleftheriou et al. [7] develop a CTL update method employing model abstraction. An abstraction of a Kripke model is determined by a function mapping a set of concrete states to an abstract state. Instead of an accessibility relation, such an abstraction has two relations: {a mathematical formula}Rmust and {a mathematical formula}Rmay. There is a transition in {a mathematical formula}Rmust from {a mathematical formula}sˆ1 to {a mathematical formula}sˆ2 if there are transitions from all concrete states of {a mathematical formula}sˆ1 to some concrete state of {a mathematical formula}sˆ2. By contrast, there is a transition in {a mathematical formula}Rmay from {a mathematical formula}sˆ1 to {a mathematical formula}sˆ2 if there is a transition from some concrete state of {a mathematical formula}sˆ1 to some concrete state of {a mathematical formula}sˆ2. A literal labels an abstract state only if such a literal labels all concrete states of such an abstract state. Hence, the abstract labeling function is partial. As a result, abstraction uses 3-valued semantics. If the truth value of a formula at an abstract state is undefined, a refinement step is performed so as to get a more concrete abstraction and thus obtain a true or false value.
       </paragraph>
       <paragraph>
        Like both our technique and Zhang and Ding's (2008), this method is recursive and employs additional, auxiliary information generated by other subformulas. Such information, in this case, is a set of (state, formula)-pairs, also called constraints, and is used as follows. Chatzieleftheriou et al.'s algorithm produces models satisfying both the input formula and constraints as output. At the same time, update at a state s w.r.t. {a mathematical formula}α∧β proceeds by first treating α with {a mathematical formula}(s,β) added to the set of pairs, then treating β with {a mathematical formula}(s,α) added to the set of pairs, and finally “combining both results appropriately” [7, p. 349].
       </paragraph>
       <paragraph>
        Let us now assess Chatzieleftheriou et al.'s method. First, although Chatzieleftheriou et al. assert the soundness of their method, these authors do not assert its completeness.
       </paragraph>
       <paragraph>
        Second, Chatzieleftheriou et al. [7] give a deterministic algorithm, as opposed to our method, which is nondeterministic. We believe that a nondeterministic approach has the advantage of allowing a separation of the essence from the search strategy of the algorithm.
       </paragraph>
       <paragraph>
        Lastly, Chatzieleftheriou et al. [7] use abstractions, thus introducing a relevant improvement element in terms of efficiency. This suggests that it would be promising to explore the possibility of developing an algorithm combining Chatzieleftheriou et al.'s abstractions with our protections so as to obtain a method having the best of both these methods.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Soundness and completeness
     </section-title>
     <paragraph label="Definition A.1">
      We outline here a proof of soundness and completeness for {a mathematical formula}XUpdprot. The application of {a mathematical formula}XUpdprot to a protected model {a mathematical formula}(M,P) should produce protected models {a mathematical formula}(M′,P′) such that {a mathematical formula}P′ is “greater than or equal to” P. Therefore, we start by defining a partial order on protections suitable for model update. Relation ≽If {a mathematical formula}P,P′∈PΣ are two protections, then we say that {a mathematical formula}P′ is greater than or equal to P, and we write {a mathematical formula}P′≽P if {a mathematical formula}EP′⊇EP, {a mathematical formula}AP′⊆AP, and {a mathematical formula}∀t∈SΣ:LP′(t)⊇LP(t).
     </paragraph>
     <paragraph label="Proof">
      Note that the relation ≽ is defined by the partial orders ⊆ and ⊇.Thus, if {a mathematical formula}P∈PΣ, then {a mathematical formula}EP⊇EP, {a mathematical formula}AP⊆AP, and {a mathematical formula}∀t∈SΣ:LP(t)⊇LP(t). Therefore, {a mathematical formula}P≽P, and ≽ is reflexive. Similarly, we can show that ≽ is antisymmetric and transitive.  □
     </paragraph>
     <paragraph>
      Protected update operations, when applicable, produce a protected model with a protection greater than or equal to the protection of the input model. That is, these operations do not decrease protections.
     </paragraph>
     <paragraph label="Theorem A.3">
      Operations do not decrease protectionsGiven{a mathematical formula}(M,P)∈KPΣ,{a mathematical formula}s,s′∈SM,{a mathematical formula}ℓ∈Lit(VΣ),{a mathematical formula}S′⊆SM, and the following conditions:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}ℓ¯∉LP(s)and{a mathematical formula}(M′,P′)=Lu((M,P),s,ℓ)
      </list-item>
      <list-item label="2.">
       {a mathematical formula}s′∈AP[s]and{a mathematical formula}(M′,P′)=T∃+((M,P),s,s′)
      </list-item>
      <list-item label="3.">
       {a mathematical formula}EP[s]⊆S′⊆AP[s],{a mathematical formula}S′≠∅, and{a mathematical formula}(M′,P′)=T∀u((M,P),s,S′)
      </list-item>
      <list-item label="4.">
       {a mathematical formula}EP[s]⊆S′⊆AP[s],{a mathematical formula}S′≠∅, and{a mathematical formula}(M′,P′)=T∃u((M,P),s,S′),
      </list-item>
     </list>
     <paragraph label="Proof">
      (According to the above 1–4 conditions)
     </paragraph>
     <list>
      <list-item label="1.">
       If {a mathematical formula}ℓ¯∉LP(s) and {a mathematical formula}(M′,P′)=Lu((M,P),s,ℓ), then{a mathematical formula}(M′,P′)=(Lu(M,s,ℓ),〈EP,AP,LP[s⊕ℓ]〉).Therefore, {a mathematical formula}M′=Lu(M,s,ℓ)=〈SM,RM,LM[s⊕ℓ]〉, and{a mathematical formula}P′=〈EP,AP,LP[s⊕ℓ]〉.Hence, the only difference between {a mathematical formula}M′ and {a mathematical formula}M, and between {a mathematical formula}P′ and P is in the third component.Since {a mathematical formula}M▷P, we have {a mathematical formula}EP⊆RM⊆AP, and {a mathematical formula}∀t∈SM:LM(t)⊇LP(t). Thus, to conclude that {a mathematical formula}M′▷P′, all we need to show is that {a mathematical formula}∀t∈SM:LM[s⊕ℓ](t)⊇LP[s⊕ℓ](t).If {a mathematical formula}t≠s then {a mathematical formula}LM[s⊕ℓ](t)=LM(t)⊇LP(t)=LP[s⊕ℓ](t).If {a mathematical formula}t=s then {a mathematical formula}LM[s⊕ℓ](t)=(LM(s)∪{ℓ})−{ℓ¯}⊇(LP(s)∪{ℓ})−{ℓ¯}=LP[s⊕ℓ](t).Hence, {a mathematical formula}M′▷P′ and {a mathematical formula}(M′,P′)∈KPΣ.Besides, {a mathematical formula}EP′=EP⊇EP, and {a mathematical formula}AP′=AP⊆AP. Thus, to conclude that {a mathematical formula}P′≽P, all we need to show is that {a mathematical formula}∀t∈SΣ:LP′(t)⊇LP(t).If {a mathematical formula}t≠s then {a mathematical formula}LP′(t)=LP[s⊕ℓ](t)=LP(t)⊇LP(t).If {a mathematical formula}t=s then {a mathematical formula}LP′(t)=LP[s⊕ℓ](t)=(LP(s)∪{ℓ})−{ℓ¯}⊇LP(s)=LP(t), because {a mathematical formula}ℓ¯∉LP(s).Therefore, {a mathematical formula}P′≽P.
      </list-item>
      <list-item label="2.">
       If {a mathematical formula}s′∈AP[s] and {a mathematical formula}(M′,P′)=T∃+((M,P),s,s′), then{a mathematical formula}(M′,P′)=(T+(M,s,s′),〈EP∪{(s,s′)},AP,LP〉)Therefore, {a mathematical formula}M′=T+(M,s,s′)=〈SM,RM∪{(s,s′)},LM〉, and{a mathematical formula}P′=〈EP∪{(s,s′)},AP,LP〉.Hence, the only difference between {a mathematical formula}M′ and {a mathematical formula}M, and between {a mathematical formula}P′ and P is in the first and second components, respectively.Since {a mathematical formula}M▷P, we have {a mathematical formula}EP⊆RM⊆AP, and {a mathematical formula}∀t∈SM:LM(t)⊇LP(t). Thus, to conclude that {a mathematical formula}M′▷P′, all we need to show is that {a mathematical formula}EP′⊆RM′⊆AP′.Since {a mathematical formula}s′∈AP[s], {a mathematical formula}EP′=EP∪{(s,s′)}⊆RM∪{(s,s′)}=RM′⊆AP∪{(s,s′)}=AP′.Hence, {a mathematical formula}M′▷P′ and {a mathematical formula}(M′,P′)∈KPΣ.Besides, we have {a mathematical formula}AP′=AP⊆AP, and {a mathematical formula}∀t∈SΣ:LP′(t)=LP(t)⊇LP(t). Thus, to conclude that {a mathematical formula}P′≽P, all we need to show is that {a mathematical formula}EP′⊇EP.Clearly, {a mathematical formula}EP′=EP∪{(s,s′)}⊇EP.Therefore, {a mathematical formula}P′≽P.
      </list-item>
      <list-item label="3.">
       If {a mathematical formula}EP[s]⊆S′⊆AP[s], {a mathematical formula}S′≠∅, and {a mathematical formula}(M′,P′)=T∀u((M,P),s,S′), then{a mathematical formula}(M′,P′)=(Tu(M,s,S′),〈EP,AP−({s}×(AP[s]−S′)),LP〉).Therefore, {a mathematical formula}M′=Tu(M,s,S′)=〈SM,(RM−({s}×RM[s]))∪({s}×S′),LM〉, and {a mathematical formula}P′=〈EP,AP−({s}×(AP[s]−S′)),LP〉.Hence, the only difference between {a mathematical formula}M′ and {a mathematical formula}M, and between {a mathematical formula}P′ and P is in the second component.Since {a mathematical formula}M▷P, we have {a mathematical formula}EP⊆RM⊆AP, and {a mathematical formula}∀t∈SM:LM(t)⊇LP(t). Thus, to conclude that {a mathematical formula}M′▷P′, all we need to show is that {a mathematical formula}EP′⊆RM′⊆AP′.Since {a mathematical formula}EP[s]⊆S′⊆AP[s], and {a mathematical formula}S′≠∅, we have{a mathematical formula}EP′=EP⊆(RM−({s}×RM[s]))∪({s}×S′)⊆AP−({s}×(AP[s]−S′))=AP′.Hence, {a mathematical formula}M′▷P′ and {a mathematical formula}(M′,P′)∈KPΣ.Besides, we have {a mathematical formula}EP′=EP⊇EP, and {a mathematical formula}∀t∈SΣ:LP′(t)=LP(t)⊇LP(t). Thus, to conclude that {a mathematical formula}P′≽P, all we need to show is that {a mathematical formula}AP′⊆AP.Clearly, {a mathematical formula}AP′=AP−({s}×(AP[s]−S′))⊆AP.Therefore, {a mathematical formula}P′≽P.
      </list-item>
      <list-item label="4.">
       If {a mathematical formula}EP[s]⊆S′⊆AP[s], {a mathematical formula}S′≠∅, and {a mathematical formula}(M′,P′)=T∃u((M,P),s,S′), then{a mathematical formula}(M′,P′)=(Tu(M,s,S′),〈EP∪({s}×(S′−EP[s])),AP,LP〉).In a manner analogous to the above case, we can show that {a mathematical formula}(M′,P′)∈KPΣ and {a mathematical formula}P′≽P. □
      </list-item>
     </list>
     <paragraph>
      As a consequence of Theorem A.3, we get one of the key features of the modification of protected models: The protection of a modification is greater than or equal to the protection of the input model.
     </paragraph>
     <paragraph label="Theorem A.4">
      Modifications do not decrease protectionsLet{a mathematical formula}(M,P)∈KPΣ,{a mathematical formula}s∈SM,{a mathematical formula}S′⊆SM, and{a mathematical formula}φ∈Σ-XCTL.If{a mathematical formula}(M′,P′)∈Modif((M,P),s,φ)or{a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ)then{a mathematical formula}P′≽P.
     </paragraph>
     <paragraph label="Proof">
      If {a mathematical formula}(M′,P′)∈Modif((M,P),s,φ) or {a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ), then either {a mathematical formula}(M′,P′)=(M,P), or {a mathematical formula}(M′,P′) is obtained from {a mathematical formula}(M,P) by the application of protected update operations. Therefore, by Theorem A.3, {a mathematical formula}P′≽P.  □
     </paragraph>
     <paragraph label="Proof">
      ≽ preserves satisfiabilityLet{a mathematical formula}(M,P),(M′,P′)∈KPΣ,{a mathematical formula}s∈SM, and{a mathematical formula}φ∈Σ-XCTL. If{a mathematical formula}P′≽Pand{a mathematical formula}(M,P),s⊨φthen{a mathematical formula}(M′,P′),s⊨φ.Suppose {a mathematical formula}P′≽P and {a mathematical formula}(M,P),s⊨φ. We proceed by induction on the structure of φ.Basis.
      <list>
       Cases {a mathematical formula}φ=F and {a mathematical formula}φ=T are trivial.If {a mathematical formula}φ=ℓ, then {a mathematical formula}ℓ∈LP(s)⊆LP′(s). Thus, {a mathematical formula}(M′,P′),s⊨ℓ.Cases of {a mathematical formula}φ=OD⩽n and {a mathematical formula}φ=OD&gt;n are similar to the case {a mathematical formula}φ=AXα (see below).Induction.
      </list>
      <paragraph>
       Let IH be the induction hypothesis.
      </paragraph>
      <list>
       <list-item label="1.">
        If {a mathematical formula}φ=α∨β, then w.l.o.g. {a mathematical formula}(M,P),s⊨α.Therefore, by IH, {a mathematical formula}(M′,P′),s⊨α. Thus, {a mathematical formula}(M′,P′),s⊨α∨β.
       </list-item>
       <list-item label="2.">
        The case {a mathematical formula}φ=α∧β is similar to the case {a mathematical formula}φ=α∨β.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}φ=EXα, then {a mathematical formula}∃t∈EP[s]⊆EP′[s] such that {a mathematical formula}(M,P),t⊨α. Therefore, by IH, {a mathematical formula}(M′,P′),t⊨α. Thus, {a mathematical formula}(M′,P′),s⊨EXα.
       </list-item>
       <list-item label="4.">
        If {a mathematical formula}φ=AXα, then {a mathematical formula}∀t∈AP[s]⊇AP′[s], {a mathematical formula}(M,P),t⊨α. Therefore, by IH, {a mathematical formula}∀t∈AP′[s], {a mathematical formula}(M′,P′),t⊨α. Thus, {a mathematical formula}(M′,P′),s⊨AXα. □
       </list-item>
      </list>
     </paragraph>
     <paragraph>
      Next, we show in three steps that Modif and {a mathematical formula}Modif⁎ are sound. First, given {a mathematical formula}φ∈Σ-XCTL, {a mathematical formula}(M,P)∈KPΣ, and {a mathematical formula}S′⊆SM, we show that {a mathematical formula}Modif⁎ is conditionally sound: assuming that Modif is sound for φ and {a mathematical formula}(M,P), we show that {a mathematical formula}Modif⁎ is sound by induction on {a mathematical formula}|S′|. Second, using the conditional soundness of {a mathematical formula}Modif⁎, we show that Modif is sound by induction on φ. Finally, as a corollary, we obtain the soundness of {a mathematical formula}Modif⁎.
     </paragraph>
     <paragraph label="Proof">
      Conditional soundness of {a mathematical formula}Modif⁎Let{a mathematical formula}(M,P)∈KPΣand{a mathematical formula}φ∈Σ-XCTLsuch that{a mathematical formula}Then{a mathematical formula}∀S′⊆SM, if{a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ)then{a mathematical formula}(M′,P′),S′⊨φ.Induction on {a mathematical formula}|S′|.Basis. If {a mathematical formula}|S′|=0, then {a mathematical formula}S′=∅. Therefore, {a mathematical formula}(M′,P′),S′⊨φ.Induction. Suppose {a mathematical formula}0&lt;m∈N and assume that{a mathematical formula} We show that if {a mathematical formula}|S′|=m and {a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ), then {a mathematical formula}(M′,P′),S′⊨φ.Since {a mathematical formula}|S′|=m&gt;0, {a mathematical formula}S′≠∅. Thus, by Definition 3.4, if {a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ), then {a mathematical formula}∃t∈SM and {a mathematical formula}∃(Mt,Pt)∈Modif((M,P),t,φ), such that {a mathematical formula}(M′,P′)∈Modif⁎((Mt,Pt),S′−{t},φ). By (A.2), {a mathematical formula}(M′,P′),S′−{t}⊨φ and, by (A.1), {a mathematical formula}(Mt,Pt),t⊨φ. Besides, by Theorem A.4, {a mathematical formula}P′≽Pt and {a mathematical formula}Pt≽P. Thus, {a mathematical formula}P′≽P and {a mathematical formula}(M′,P′),t⊨φ. Hence, {a mathematical formula}(M′,P′),S′⊨φ.  □
     </paragraph>
     <paragraph label="Proof">
      Soundness of ModifFor all{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}(M,P)∈KPΣ, and{a mathematical formula}s∈SM:{a mathematical formula}(M′,P′)∈Modif((M,P),s,φ)⇒(M′,P′),s⊨φ.Induction on the structure of φ.Let {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s∈SM, and suppose {a mathematical formula}(M′,P′)∈Modif((M,P),s,φ).Basis.
      <list>
       Cases {a mathematical formula}φ=F and {a mathematical formula}φ=T are trivial.If {a mathematical formula}φ=ℓ, we have two cases: {a mathematical formula}ℓ¯∈LP[s] and {a mathematical formula}ℓ¯∉LP[s].If {a mathematical formula}ℓ¯∈LP[s], then {a mathematical formula}Modif((M,P),s,ℓ)=∅.If {a mathematical formula}ℓ¯∉LP[s], then {a mathematical formula}Modif((M,P),s,ℓ) uses {a mathematical formula}Lu to generate exactly one model, {a mathematical formula}(M′,P′), by adding ℓ to the protected labels of s. Thus, {a mathematical formula}ℓ∈LP′(s), {a mathematical formula}(M′,P′),s⊨ℓ, and {a mathematical formula}∀s∈SM, {a mathematical formula}Q(s,ℓ).If {a mathematical formula}φ=OD⩽n, then {a mathematical formula}∃S′⊆AP[s] such that {a mathematical formula}EP[s]⊆S′≠∅, {a mathematical formula}|S′|⩽n, and {a mathematical formula}(M′,P′)=T∀u((M,P),s,S′). Therefore, by the definition of {a mathematical formula}T∀u, {a mathematical formula}AP′[s]⊆S′. Thus, {a mathematical formula}|AP′[s]|⩽|S′|⩽n and {a mathematical formula}(M′,P′),s⊨OD⩽n.The case {a mathematical formula}φ=OD&gt;n is similar to the case {a mathematical formula}φ=OD⩽n.Induction.
      </list>
      <paragraph>
       Let IH be the induction hypothesis, i.e., IH states that the theorem is true for {a mathematical formula}φ=α,β.
      </paragraph>
      <list>
       <list-item label="1.">
        If {a mathematical formula}φ=α∨β, then, w.o.l.g. {a mathematical formula}(M′,P′)∈Modif((M,P),s,α). By IH, {a mathematical formula}(M′,P′),s⊨α. Therefore, {a mathematical formula}(M′,P′),s⊨α∨β.
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}φ=α∧β, then {a mathematical formula}∃(Mα,Pα)∈Modif((M,P),s,α) such that{a mathematical formula}(M′,P′)∈Modif((Mα,Pα),s,β).By IH, {a mathematical formula}(Mα,Pα),s⊨α and {a mathematical formula}(M′,P′),s⊨β. Since {a mathematical formula}P′≽Pα, by Theorem A.5, {a mathematical formula}(M′,P′),s⊨α. Therefore, {a mathematical formula}(M′,P′),s⊨α∧β.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}φ=EXα, then {a mathematical formula}∃t∈AP[s] such that{a mathematical formula}(M′,P′)∈Modif(T∃+((M,P),s,t),t,α).By IH, {a mathematical formula}(M′,P′),t⊨α. Besides, if {a mathematical formula}(Mt,Pt)=T∃+((M,P),s,t), then {a mathematical formula}t∈EPt[s], and by Theorem A.4{a mathematical formula}P′≽Pt. Thus, {a mathematical formula}t∈EP′[s] and {a mathematical formula}(M′,P′),t⊨α. Therefore, {a mathematical formula}(M′,P′),s⊨EXα.
       </list-item>
       <list-item label="4.">
        If {a mathematical formula}φ=AXα, then {a mathematical formula}∃S′⊆AP[s] such that {a mathematical formula}EP[s]⊆S′≠∅ and {a mathematical formula}(M′,P′)∈Modif⁎((MS′,PS′),S′,α), where {a mathematical formula}(MS′,PS′)=T∀u((M,P),s,S′).By IH, {a mathematical formula}∀s∈SM, if {a mathematical formula}(M″,P″)∈Modif((MS′,PS′),s,α) then{a mathematical formula}(M″,P″),s⊨α.Therefore, by Theorem A.6, {a mathematical formula}(M′,P′),S′⊨α. By the definition of {a mathematical formula}PS′, we have {a mathematical formula}S′=APS′[s], and, by Theorem A.4, {a mathematical formula}P′≽PS′. Thus, {a mathematical formula}S′=APS′[s]⊇AP′[s]. Since {a mathematical formula}(M′,P′),S′⊨α and {a mathematical formula}AP′[s]⊆S′, {a mathematical formula}(M′,P′),AP′[s]⊨α. Therefore, {a mathematical formula}(M′,P′),s⊨AXα. □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      Soundness of {a mathematical formula}Modif⁎For all{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}(M,P)∈KPΣ, and{a mathematical formula}S′⊆SM:{a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ)⇒(M′,P′),S′⊨φ.Let {a mathematical formula}φ∈Σ-XCTL, {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}S′⊆SM, and suppose {a mathematical formula}(M′,P′)∈Modif⁎((M,P),S′,φ). By Theorem A.7,{a mathematical formula}∀s∈SM, {a mathematical formula}(M″,P″)∈Modif((M,P),s,φ)⇒{a mathematical formula}(M″,P″),s⊨φ.Therefore, by Theorem A.6, {a mathematical formula}(M′,P′),S′⊨φ.  □
     </paragraph>
     <paragraph>
      To prove completeness of Modif, it is important to know whether there is a modification of {a mathematical formula}(M,P) for φ, i.e., whether {a mathematical formula}(M,P) is “φ-modifiable”.
     </paragraph>
     <paragraph label="Definition A.9">
      φ-modifiableLet {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s∈SM, and {a mathematical formula}φ∈Σ-CTL. {a mathematical formula}(M,P) is φ-modifiable at s if {a mathematical formula}Modif((M,P),s,φ)≠∅.
     </paragraph>
     <paragraph>
      In addition, we need to prove that if φ is “satisfiable”, then {a mathematical formula}XUpdprot produces at least one result. Thus, we need to clarify the notion of “satisfiable”.
     </paragraph>
     <paragraph label="Definition A.10">
      SatisfiableLet {a mathematical formula}φ∈Σ-CTL, {a mathematical formula}P∈PΣ, and {a mathematical formula}s∈SΣ.
     </paragraph>
     <list>
      <list-item label="1.">
       φ is P-satisfiable at s if {a mathematical formula}∃(M′,P′)∈KPΣ.(M′,P′),s⊨φ&amp;P′≽P.
      </list-item>
      <list-item label="2.">
       φ is {a mathematical formula}KΣ-satisfiable at s if {a mathematical formula}∃M′∈KΣ.M′,s⊨φ.
      </list-item>
     </list>
     <paragraph>
      To state completeness of Modif it is not enough to reverse the implication of Theorem A.7. We analyze two wrong statements of completeness.
     </paragraph>
     <paragraph>
      First, the statement
     </paragraph>
     <paragraph>
      (1) {a mathematical formula}(M′,P′),s⊨φ⇒{a mathematical formula}(M′,P′)∈Modif((M,P),s,φ) is not true.
     </paragraph>
     <paragraph>
      For example, if {a mathematical formula}ℓ¯1∈LP(s) and {a mathematical formula}ℓ1∈LP′(s), then {a mathematical formula}(M′,P′)⊨ℓ1 but {a mathematical formula}(M′,P′)∉Modif((M,P),s,ℓ1)=∅.
     </paragraph>
     <paragraph>
      Second, a weaker statement,
     </paragraph>
     <paragraph>
      (2) {a mathematical formula}(M′,P′),s⊨φ and {a mathematical formula}P′≽P⇒(M′,P′)∈Modif((M,P),s,φ), is not true either.
     </paragraph>
     <paragraph>
      For example, if {a mathematical formula}ℓ¯1,ℓ¯2∉LP(s), and {a mathematical formula}(M′,P′) is the result of adding {a mathematical formula}ℓ1 and {a mathematical formula}ℓ2 to {a mathematical formula}(M,P), i.e., {a mathematical formula}(Mℓ1,Pℓ1)=Lu((M,P),s,ℓ1), and {a mathematical formula}(M′,P′)=Lu((Mℓ1,Pℓ1),s,ℓ2), then
     </paragraph>
     <paragraph>
      {a mathematical formula}(M′,P′)⊨ℓ1 and {a mathematical formula}P′≽P
     </paragraph>
     <paragraph>
      but {a mathematical formula}(M′,P′)∉Modif((M,P),s,ℓ1)={(Mℓ1,Pℓ1)}.
     </paragraph>
     <paragraph>
      According to our purposes (e.g., Corollary A.15), a more appropriate statement for completeness of Modif is as in Theorem A.12. To prove this theorem, we follow three steps. First, we show that {a mathematical formula}Modif⁎ is conditionally complete: assuming that Modif is complete for given φ and {a mathematical formula}(M,P), we show that {a mathematical formula}Modif⁎ is complete by induction on {a mathematical formula}|S′|. Second, using the conditional completeness of {a mathematical formula}Modif⁎, we show that Modif is complete by induction on φ. Finally, as a corollary, we obtain the completeness of {a mathematical formula}Modif⁎.
     </paragraph>
     <paragraph label="Proof">
      Conditional completeness of {a mathematical formula}Modif⁎Let{a mathematical formula}(M,P)∈KPΣand{a mathematical formula}φ∈Σ-XCTLsuch that{a mathematical formula}Then{a mathematical formula}∀S′⊆SM, if{a mathematical formula}∃(M′,P′)∈KPΣsuch that{a mathematical formula}(M′,P′),S′⊨φand{a mathematical formula}P′≽P, then{a mathematical formula}∃(MS′,φ,PS′,φ)∈Modif⁎((M,P),S′,φ)such that{a mathematical formula}P′≽PS′,φ.Induction on {a mathematical formula}|S′|.Basis. If {a mathematical formula}|S′|=0, then {a mathematical formula}S′=∅ and {a mathematical formula}Modif⁎((M,P),∅,φ)={(M,P)}. Therefore, if we take {a mathematical formula}(MS′,φ,PS′,φ)=(M,P)∈Modif⁎((M,P),∅,φ), then {a mathematical formula}P′≽P=PS′,φ.Induction. Suppose {a mathematical formula}0&lt;m∈N and assume that{a mathematical formula} We show that if {a mathematical formula}S′⊆SM, {a mathematical formula}|S′|=m, and {a mathematical formula}∃(M′,P′)∈KPΣ such that {a mathematical formula}(M′,P′),S′⊨φ and {a mathematical formula}P′≽P, then {a mathematical formula}∃(MS′,φ,PS′,φ)∈Modif⁎((M,P),S′,φ) such that {a mathematical formula}P′≽PS′,φ.Let {a mathematical formula}S′⊆SM such that {a mathematical formula}|S′|=m&gt;0. Suppose {a mathematical formula}(M′,P′)∈KPΣ is such that (1) {a mathematical formula}(M′,P′),S′⊨φ and (2) {a mathematical formula}P′≽P.Since {a mathematical formula}|S′|&gt;0, {a mathematical formula}S′≠∅. Let {a mathematical formula}t∈S′ and {a mathematical formula}St′=S′−{t}.On the one hand, by (1) and (2), {a mathematical formula}(M′,P′),t⊨φ and {a mathematical formula}P′≽P. Thus, by (A.3), there exists {a mathematical formula}(Mt,φ,Pt,φ)∈Modif((M,P),s,φ) such that {a mathematical formula}P′≽Pt,φ. On the other hand, by (1), {a mathematical formula}(M′,P′),St′⊨φ and {a mathematical formula}P′≽Pt,φ. Thus, by (A.4), {a mathematical formula}∃(MSt′,φ,PSt′,φ)∈Modif⁎((Mt,φ,Pt,φ),St′,φ) such that {a mathematical formula}P′≽PSt′,φ.Hence, by using {a mathematical formula}St′=S′−{t} and Definition 3.4, {a mathematical formula}(MSt′,φ,PSt′,φ)∈Modif⁎((M,P),S′,φ) and {a mathematical formula}P′≽PS′,φ.  □
     </paragraph>
     <paragraph label="Proof">
      Completeness of ModifFor all{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}(M,P)∈KPΣ, and{a mathematical formula}s∈SM: if{a mathematical formula}∃(M′,P′)∈KPΣsuch that{a mathematical formula}(M′,P′),s⊨φand{a mathematical formula}P′≽Pthen{a mathematical formula}∃(Ms,φ,Ps,φ)∈Modif((M,P),s,φ)such that{a mathematical formula}P′≽Ps,φ.Induction on the structure of φ.Let {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s∈SM, and suppose {a mathematical formula}(M,P)∈KPΣ is such that{a mathematical formula}{a mathematical formula}Basis.
      <list>
       If {a mathematical formula}φ=F, then {a mathematical formula}∄(M′,P′)∈KPΣ such that {a mathematical formula}(M′,P′),s⊨F and {a mathematical formula}P′≽P.If {a mathematical formula}φ=T, take {a mathematical formula}(Ms,T,Ps,T)=(M,P)∈Modif((M,P),s,T), i.e. {a mathematical formula}(Ms,T,Ps,T)={(M,P)}. Thus, {a mathematical formula}P′≽P=Ps,T.If {a mathematical formula}φ=ℓ, then, by (A.5), {a mathematical formula}ℓ∈LP′(s). Therefore, {a mathematical formula}ℓ¯∉LP′(s) and, by (A.6), {a mathematical formula}ℓ¯∉LP(s). Let {a mathematical formula}(Ms,ℓ,Ps,ℓ)=Lu((M,P),s,ℓ), the only element of {a mathematical formula}Modif((M,P),s,ℓ). By Theorem A.3, {a mathematical formula}(Ms,ℓ,Ps,ℓ)∈KPΣ (and {a mathematical formula}Ps,ℓ≽P). Besides, {a mathematical formula}P′≽P, {a mathematical formula}EPs,ℓ=EP, {a mathematical formula}APs,ℓ=AP, and {a mathematical formula}LPs,ℓ=LP[s⊕ℓ]; therefore {a mathematical formula}P′≽Ps,ℓ. Hence, {a mathematical formula}(Ms,ℓ,Ps,ℓ)∈Modif((M,P),s,ℓ) and {a mathematical formula}P′≽Ps,ℓ.Cases {a mathematical formula}φ=OD⩽n and {a mathematical formula}φ=OD&gt;n are similar to the case {a mathematical formula}φ=AXα (see below).Induction.
      </list>
      <paragraph>
       Let IH be the induction hypothesis, i.e., IH states that the theorem is true for {a mathematical formula}φ=α and {a mathematical formula}φ=β.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}φ=α∨β. By (A.5), and w.l.o.g. {a mathematical formula}(M′,P′),s⊨α. Thus, by IH, {a mathematical formula}∃(Ms,α,Ps,α)∈Modif((M,P),s,α) such that {a mathematical formula}P′≽Ps,α. Hence, {a mathematical formula}(Ms,α,Ps,α)∈Modif((M,P),s,α∨β) and {a mathematical formula}P′≽Ps,α.
       </list-item>
       <list-item label="2.">
        {a mathematical formula}φ=α∧β. By (A.5), {a mathematical formula}(M′,P′),s⊨α. Thus, by IH, {a mathematical formula}∃(Ms,α,Ps,α)∈Modif((M,P),s,α) such that {a mathematical formula}P′≽Ps,α.Therefore, {a mathematical formula}P′≽Ps,α and, by (A.5), {a mathematical formula}(M′,P′),s⊨β. Thus, by applying IH with {a mathematical formula}(M,P)=(Ms,α,Ps,α) and {a mathematical formula}φ=β, we have that {a mathematical formula}∃(Ms,β,Ps,β)∈{a mathematical formula}Modif((Ms,α,Ps,α),s,β) such that {a mathematical formula}P′≽Ps,β. Hence, {a mathematical formula}(Ms,β,Ps,β)∈Modif((M,P),s,α∧β) and {a mathematical formula}P′≽Ps,β.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}φ=EXα. By (A.5), {a mathematical formula}∃s′∈EP′[s] such that {a mathematical formula}(M′,P′),s′⊨α. Let {a mathematical formula}(Ms′,Ps′)=T∃+((M,P),s,s′). Since {a mathematical formula}s′∈EP′[s], by (A.6), {a mathematical formula}P′≽Ps′. Thus, by applying IH with {a mathematical formula}(M,P)=(Ms′,Ps′) and {a mathematical formula}φ=α, we have that {a mathematical formula}∃(Ms′,α,Ps′,α)∈Modif((Ms′,Ps′),s′,α) such that {a mathematical formula}P′≽Ps′,α. Thus, {a mathematical formula}s′∈EP′[s]⊆AP′[s] and{a mathematical formula}(Ms′,α,Ps′,α)∈{a mathematical formula}Modif(T∃+((M,P),s,s′),s′,α).Therefore, {a mathematical formula}(Ms′,α,Ps′,α)∈Modif((M,P),s,EXα) and {a mathematical formula}P′≽Ps′,α.
       </list-item>
       <list-item label="4.">
        {a mathematical formula}φ=AXα. By (A.5), {a mathematical formula}∀s′∈AP′[s], {a mathematical formula}(M′,P′),s′⊨α. Let {a mathematical formula}S′=AP′[s] and {a mathematical formula}(MS′,PS′)=T∀u((M,P),s,S′). Since {a mathematical formula}S′⊆AP′[s], by (A.6), {a mathematical formula}P′≽PS′. Thus, by applying IH with {a mathematical formula}(M,P)=(MS′,PS′) and {a mathematical formula}φ=α, we have that {a mathematical formula}∃(MS′,α,PS′,α)∈Modif⁎((MS′,PS′),S′,α) such that {a mathematical formula}P′≽PS′,α. Since {a mathematical formula}S′=AP′[s]⊇EP′[s] and {a mathematical formula}AP′[s]⊇RM′[s]≠∅, we have {a mathematical formula}S′⊆AP′[s] and {a mathematical formula}EP′[s]⊆S′≠∅. Thus, {a mathematical formula}S′⊆AP′[s], {a mathematical formula}EP′[s]⊆S′≠∅, and {a mathematical formula}(MS′,α,PS′,α)∈Modif⁎(T∀u((M,P),s,S′),S′,α). Therefore, {a mathematical formula}(MS′,α,PS′,α)∈Modif((M,P),s,AXα) and {a mathematical formula}P′≽PS′,α. □
       </list-item>
      </list>
     </paragraph>
     <paragraph label="Proof">
      Completeness of {a mathematical formula}Modif⁎For all{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}(M,P)∈KPΣ, and{a mathematical formula}S′⊆SM: if{a mathematical formula}∃(M′,P′)∈KPΣsuch that{a mathematical formula}(M′,P′),S′⊨φand{a mathematical formula}P′≽P, then{a mathematical formula}∃(MS′,φ,PS′,φ)∈Modif⁎((M,P),S′,φ)such that{a mathematical formula}P′≽PS′,φ.Let {a mathematical formula}φ∈Σ-XCTL, {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}S′⊆SM, and suppose {a mathematical formula}(M′,P′)∈KPΣ is such that (1) {a mathematical formula}(M′,P′),S′⊨φ and (2) {a mathematical formula}P′≽P.By Theorem A.12, {a mathematical formula}∀s∈SM, if {a mathematical formula}∃(M′,P′)∈KPΣ such that {a mathematical formula}(M′,P′),s⊨φ and {a mathematical formula}P′≽P then {a mathematical formula}∃(Ms,φ,Ps,φ)∈Modif((M,P),s,φ) such that {a mathematical formula}P′≽Ps,φ. Therefore, by Theorem A.11, if {a mathematical formula}∃(M′,P′)∈KPΣ such that {a mathematical formula}(M′,P′),S′⊨φ and {a mathematical formula}P′≽P, then {a mathematical formula}∃(MS′,φ,PS′,φ)∈Modif⁎((M,P),S′,φ) such that {a mathematical formula}P′≽PS′,φ. Therefore, by (1) and (2), {a mathematical formula}∃(MS′,φ,PS′,φ)∈Modif⁎((M,P),S′,φ) such that {a mathematical formula}P′≽PS′,φ.  □
     </paragraph>
     <paragraph>
      Hence, as stated in the following theorem, “φ is P-satisfiable” is equivalent to “{a mathematical formula}(M,P) is φ-modifiable”.
     </paragraph>
     <paragraph label="Theorem A.14">
      {a mathematical formula}P-satisfiable ≈φ-modifiableLet{a mathematical formula}(M,P)∈KPΣand{a mathematical formula}s∈SM. If{a mathematical formula}φ∈Σ-XCTL, then φ is P-satisfiable at s iff{a mathematical formula}(M,P)is φ-modifiable at s.
     </paragraph>
     <paragraph label="Proof">
      {a mathematical formula}(⇒). If φ is P-satisfiable at s, then there is {a mathematical formula}(M′,P′)∈KPΣ such that {a mathematical formula}(M′,P′),s⊨φ and {a mathematical formula}P′≽P. Therefore, by Theorem A.12, there exists {a mathematical formula}(Mφ,Pφ)∈Modif((M,P),s,φ) such that {a mathematical formula}P′≽Pφ.Thus, {a mathematical formula}Modif((M,P),s,φ)≠∅, and {a mathematical formula}(M,P) is φ-modifiable at s.{a mathematical formula}(⇐). If {a mathematical formula}(M,P) is φ-modifiable at s, then {a mathematical formula}Modif((M,P),s,φ)≠∅. Let {a mathematical formula}(M′,P′)∈Modif((M,P),s,φ). By Theorem A.7, {a mathematical formula}(M′,P′),s⊨φ, and, by Theorem A.4, {a mathematical formula}P′≽P. Therefore, φ is P-satisfiable at s.  □
     </paragraph>
     <paragraph label="Proof">
      Finally, completeness of {a mathematical formula}XUpdprot is a consequence of the next corollary. {a mathematical formula}KΣ-satisfiable ≈φ-modifiableFor all{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}s∈SΣ, and{a mathematical formula}M∈KΣ: φ is{a mathematical formula}KΣ-satisfiable at s iff{a mathematical formula}(M,P⊥)is φ-modifiable at s.{a mathematical formula}(⇒). Let {a mathematical formula}M′∈KΣ such that {a mathematical formula}M′,s⊨φ. Then, by Definition 2.6, {a mathematical formula}(M′,PM′),s⊨φ. Besides, {a mathematical formula}PM′≽P⊥. Therefore, φ is {a mathematical formula}P⊥-satisfiable at s and, by Theorem A.14, {a mathematical formula}(M,P⊥) is φ-modifiable at s.{a mathematical formula}(⇐). If {a mathematical formula}(M′,P′)∈Modif((M,P⊥),s,φ), then, by Theorem A.7, {a mathematical formula}(M′,P′),s⊨φ.Besides, {a mathematical formula}PM′≽P′. Hence, {a mathematical formula}(M′,PM′),s⊨φ and, by Definition 2.6, {a mathematical formula}M′,s⊨φ. Therefore, φ is {a mathematical formula}KΣ-satisfiable at s.  □
     </paragraph>
     <paragraph>
      Note that pseudo-code of {a mathematical formula}XUpdprot is an intuitive implementation of Modif. If we assume that models computed by {a mathematical formula}XUpdprot are exactly modifications of the input model, i.e., for all {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s∈SM, and {a mathematical formula}φ∈Σ-XCTL, {a mathematical formula}XUpdprot[(M,P),s,φ]=Modif((M,P),s,φ), then the following theorem formalizes, in a sense, that {a mathematical formula}XUpdprot is sound and complete.
     </paragraph>
     <paragraph label="Theorem A.16">
      {a mathematical formula}XUpdprot is sound and completeIf for all{a mathematical formula}(M,P)∈KPΣ,{a mathematical formula}s∈SM, and{a mathematical formula}φ∈Σ-XCTL,{a mathematical formula}XUpdprot[(M,P),s,φ]=Modif((M,P),s,φ), then for all{a mathematical formula}M∈KΣ,{a mathematical formula}s∈SM, and{a mathematical formula}φ∈Σ-XCTL:
     </paragraph>
     <list>
      <list-item label="1.">
       If{a mathematical formula}(M′,P′)∈XUpdprot[(M,P⊥),s,φ], then{a mathematical formula}(M′,P′),s⊨φ.
      </list-item>
      <list-item label="2.">
       If φ is{a mathematical formula}KΣ-satisfiable at s, then{a mathematical formula}XUpdprot[(M,P⊥),s,φ]≠∅.
      </list-item>
     </list>
     <paragraph label="Proof">
      (1). If {a mathematical formula}(M′,P′)∈XUpdprot[(M,P⊥),s,φ]=Modif((M,P),s,φ), then, by Theorem A.7, {a mathematical formula}(M′,P′),s⊨φ. Therefore, {a mathematical formula}XUpdprot is sound.(2). If φ is {a mathematical formula}KΣ-satisfiable at s, then, by Corollary A.15, {a mathematical formula}(M,P⊥) is φ-modifiable at s. Therefore, {a mathematical formula}XUpdprot[(M,P⊥),s,φ]=Modif((M,P⊥),s,φ) ≠∅.  □
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Complexity
     </section-title>
     <paragraph>
      This section offers a complexity analysis of our model-update method. We measure the complexity of {a mathematical formula}Updprot with respect to the size of the input formula and the size of the input model. For {a mathematical formula}Σ-CTL formulas, we use the size defined in Section 2.
     </paragraph>
     <paragraph>
      To define the size of a model in {a mathematical formula}KPΣ, we note that it is common to consider that the states of a model are vectors whose components correspond to variable values. In such case, the number of states is exponential with respect to the number of variables and therefore the size of a model may be estimated by considering only {a mathematical formula}|S×S| or just {a mathematical formula}|S|. In general, however, it is possible that the number of variables is greater than the number of states. In addition, some parts of {a mathematical formula}Updprot depend not only on the states of input model but also on the model transitions. Therefore, we define the size of a model as follows.
     </paragraph>
     <paragraph label="Definition B.1">
      Size of protected modelsThe size of a protected model {a mathematical formula}(M,P)∈KPΣ is defined by {a mathematical formula}|(M,P)|=max{|Lit(VΣ)|,|SΣ×SΣ|}.
     </paragraph>
     <paragraph>
      Note that all {a mathematical formula}(M,P)∈KPΣ have the same size. Besides, update operations in the execution of {a mathematical formula}XUpdprot((M,P),s,φ) preserve Σ. Therefore, we use {a mathematical formula}m=|(M,P)| as a fixed parameter in the next complexity analysis.
     </paragraph>
     <paragraph label="Definition B.2">
      Number of stepsLet {a mathematical formula}(M,P)∈KPΣ, {a mathematical formula}s∈SM, and {a mathematical formula}φ∈CTLΣ. If {a mathematical formula}m=|(M,P)|, {a mathematical formula}n=|φ|, and {a mathematical formula}φ∈XCTLΣ, we use {a mathematical formula}Tm(n) to denote the number of steps required in a nondeterministic execution of {a mathematical formula}XUpdprot((M,P),s,φ).If {a mathematical formula}φ∈CTLΣ−XCTLΣ, we use {a mathematical formula}Tm′(n) to denote the number of steps required in a nondeterministic execution of {a mathematical formula}Updprot((M,P),s,φ).
     </paragraph>
     <paragraph>
      We use {a mathematical formula}Tm(n) to analyze the worst-case time complexity of {a mathematical formula}XUpdprot.
     </paragraph>
     <paragraph label="Theorem B.3">
      Complexity of {a mathematical formula}XUpdprotLet{a mathematical formula}(M,P)∈KPΣ,{a mathematical formula}s∈SM, and{a mathematical formula}φ∈XCTLΣ. If{a mathematical formula}m=|(M,P)|, and{a mathematical formula}n=|φ|, then{a mathematical formula}Tm(n)is{a mathematical formula}O(mn).
     </paragraph>
     <paragraph label="Proof">
      We analyze {a mathematical formula}Tm(n) according to the structure of φ.
      <list>
       If {a mathematical formula}φ=F or {a mathematical formula}φ=T, then, by lines (3–4), {a mathematical formula}XUpdprot((M,P),s,φ) fails or returns {a mathematical formula}(M,P). In both cases the execution of {a mathematical formula}XUpdprot((M,P),s,φ) requires at most one step. Therefore, if {a mathematical formula}n=|F|=|T|, {a mathematical formula}Tm(n)=1.If {a mathematical formula}φ=ℓ, then, since {a mathematical formula}|LP(s)|⩽|Lit(VΣ)|⩽m, computing the test {a mathematical formula}ℓ¯∈LP(s) in line (5) requires at most m steps.Next, to compute {a mathematical formula}Lu((M,P),s,ℓ) in line (6), we need to calculate {a mathematical formula}LM[s⊕ℓ] and {a mathematical formula}LP[s⊕ℓ]. Thus, to compute {a mathematical formula}LM[s⊕ℓ] we search for {a mathematical formula}LM(s) in {a mathematical formula}LM, and we modify {a mathematical formula}LM(s) by adding ℓ to {a mathematical formula}LM(s) and removing {a mathematical formula}ℓ¯ from {a mathematical formula}LM(s).The search for {a mathematical formula}LM(s) in {a mathematical formula}LM can be done in at most m steps because {a mathematical formula}|SM|⩽m. The addition (without duplication) of ℓ, and the removal of {a mathematical formula}ℓ¯, can be done in at most 2m steps because {a mathematical formula}|LM(s)|⩽|Lit(VΣ)|⩽m. Therefore, the computation of {a mathematical formula}LM[s⊕ℓ] requires at most 3m steps.Analogously, the computation of {a mathematical formula}LP[s⊕ℓ] requires at most 3m steps. Hence, {a mathematical formula}XUpdprot((M,P),s,ℓ) needs at most {a mathematical formula}m+3m+3m steps.Therefore, if {a mathematical formula}n=|ℓ|, {a mathematical formula}Tm(n)=7m.If {a mathematical formula}φ=α∨β, then, by lines (7–8), after guessing {a mathematical formula}δ∈{α,β} in one step, {a mathematical formula}XUpdprot((M,P),s,α∨β) makes a recursive call to{a mathematical formula}XUpdprot((M,P),s,δ).Therefore, if δ is the guess that requires more execution steps, the number of steps required by {a mathematical formula}XUpdprot((M,P),s,α∨β) is 1 plus the number of steps needed by {a mathematical formula}XUpdprot((M,P),s,δ).Thus, if {a mathematical formula}n=|α∨β|, {a mathematical formula}Tm(n)=1+Tm(n−1).Therefore, the number of steps required to compute{a mathematical formula}XUpdprot((M,P),s,α∧β) is given by the sum of: {a mathematical formula}Tm(n−1) steps for computing {a mathematical formula}XUpdprot((M,P),s,α), 1 step for guessing {a mathematical formula}(M′,P′)∈XUpdprot((M,P),s,α), and {a mathematical formula}Tm(n−1) steps for computing{a mathematical formula}XUpdprot((M′,P′),s,β).Thus, if {a mathematical formula}n=|α∧β|, {a mathematical formula}Tm(n)=1+2Tm(n−1).Therefore, the number of steps required to compute{a mathematical formula}XUpdprot((M,P),s,EXα) is 1 plus the sum of 2m and the number of steps needed to compute {a mathematical formula}XUpdprot((M″,P″),s′,α).Thus, if {a mathematical formula}n=|EXα|, {a mathematical formula}Tm(n)=1+2m+Tm(n−1).If {a mathematical formula}φ=AXα, then line (13) guesses {a mathematical formula}S′∈{a mathematical formula}{X⊆AP[s]|EP[s]⊆X and X≠∅} in one step.Now, to compute {a mathematical formula}T∀u((M,P),s,S′) in line (14), we need to calculate {a mathematical formula}Tu(M,s,S′) and {a mathematical formula}(AP−s×(AP[s]−S′)).The computation of {a mathematical formula}Tu(M,s,S′) requires at most 3m steps: m steps to compute {a mathematical formula}RM[s]; m steps to remove {a mathematical formula}s×RM[s] from {a mathematical formula}RM; and m steps to add {a mathematical formula}s×S′ to {a mathematical formula}RM.The computation of {a mathematical formula}(AP−s×(AP[s]−S′)) requires at most 3m steps: m to compute s in {a mathematical formula}AP[s]; m to compute {a mathematical formula}AP[s]−S′; and m to remove {a mathematical formula}s×(AP[s]−S′) from {a mathematical formula}AP.Therefore, the computation of {a mathematical formula}T∀u((M,P),s,S′) in line (14) requires at most 6m steps.Then, the call to {a mathematical formula}XUpdprot⁎(T∀u((M,P),s,S′),S′,α) in line (14) corresponds to {a mathematical formula}|S′| consecutive calls to {a mathematical formula}XUpdprot(̲,s′,α) with all {a mathematical formula}s′∈S′. Since {a mathematical formula}|S′|⩽m and {a mathematical formula}|α|=n−1, the maximum number of steps required by all these calls to {a mathematical formula}XUpdprot is {a mathematical formula}mTm(n−1).Thus, if {a mathematical formula}n=|AXα|, {a mathematical formula}Tm(n)=1+6m+mTm(n−1).If {a mathematical formula}φ=OD⊙j, where {a mathematical formula}⊙∈{⩽,&gt;}, then line (15) guesses {a mathematical formula}S′ in one step. Analogously to the case {a mathematical formula}φ=AXα, the computation of {a mathematical formula}TQu((M,P),s,S′) in line (17) requires at most 6m steps.Therefore, if {a mathematical formula}n=|OD⊙j|, {a mathematical formula}Tm(n)=1+6m.The worst case of
      </list>
      <paragraph>
       {a mathematical formula}XUpdprot((M,P),s,φ) is when {a mathematical formula}φ=AXα. Therefore, a lower bound for the worst-case complexity of {a mathematical formula}XUpdprot is given by a solution of the recurrence relation defined by {a mathematical formula}Tm(n)=1+6m+mTm(n−1), if {a mathematical formula}n&gt;1, and {a mathematical formula}Tm(1)=7m. The factor m in {a mathematical formula}Tm(1) and the term {a mathematical formula}mTm(n−1) in {a mathematical formula}Tm(n) imply that a solution of this recurrence relation has a factor {a mathematical formula}mn. Therefore, the worst-case time complexity of {a mathematical formula}XUpdprot is {a mathematical formula}O(mn).  □
      </paragraph>
     </paragraph>
     <paragraph>
      The above theorem can be extended to formulas in {a mathematical formula}CTLΣ.
     </paragraph>
     <paragraph label="Theorem B.4">
      Complexity of {a mathematical formula}UpdprotLet{a mathematical formula}(M,P)∈KPΣ,{a mathematical formula}s∈SM, and{a mathematical formula}φ∈CTLΣ−XCTLΣ. If{a mathematical formula}m=|(M,P)|, and{a mathematical formula}n=|φ|, then{a mathematical formula}Tm′(n)is{a mathematical formula}O(mn+1).
     </paragraph>
     <paragraph label="Proof">
      Let ψ be a subformula of φ such that {a mathematical formula}ψ∈CTL has the form {a mathematical formula}E[αUβ] or {a mathematical formula}A[αUβ] or {a mathematical formula}E[αRβ] or {a mathematical formula}A[αRβ].The evaluation of {a mathematical formula}Updprot((M,P),s,ψ) is done replacing ψ by the corresponding fixed-point formula {a mathematical formula}ψfix. On the one hand, the size of {a mathematical formula}ψfix is linear w.r.t. the size of ψ, {a mathematical formula}|ψfix|=c⁎|ψ| for some {a mathematical formula}c∈N. On the other hand, the application of {a mathematical formula}Updprot to {a mathematical formula}ψfix implies the recursive application of {a mathematical formula}XUpdprot to ψ at a state {a mathematical formula}s′, where {a mathematical formula}s′ is a successor of s (obtained from {a mathematical formula}RM with cost m). In each recursive call to {a mathematical formula}XUpdprot the pair {a mathematical formula}(ψ,s′) is added to a list of visited states with the formula ψ and {a mathematical formula}XUpdprot continues in this manner provided that the pair {a mathematical formula}(ψ,s′) does not represent a visited state with ψ. Thus, the maximum number of recursive calls to {a mathematical formula}XUpdprot is bounded by m. Therefore, by Theorem B.3, {a mathematical formula}Tm′(n)⩽m⁎(m+Tm(n))⩽m2+m⁎d⁎mn, for some {a mathematical formula}d∈N. Hence, {a mathematical formula}Tm′(n)⩽k⁎mn+1, for some {a mathematical formula}k∈N, and {a mathematical formula}Tm′(n) is {a mathematical formula}O(mn+1).  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>