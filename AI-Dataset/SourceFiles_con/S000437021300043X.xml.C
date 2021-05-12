<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Belief functions on distributive lattices.
   </title>
   <abstract>
    The Dempster–Shafer theory of belief functions is an important approach to deal with uncertainty in AI. In the theory, belief functions are defined on Boolean algebras of events. In many applications of belief functions in real world problems, however, the objects that we manipulate is no more a Boolean algebra but a distributive lattice. In this paper, we employ Birkhoffʼs representation theorem for finite distributive lattices to extend the Dempster–Shafer theory to the setting of distributive lattices, which has a mathematical theory as attractive as in that of Boolean algebras. Moreover, we use this more general theory to provide a framework for reasoning about belief functions in a deductive approach on non-classical formalisms which assume a setting of distributive lattices. As an illustration of this approach, we investigate the theory of belief functions for a simple epistemic logic the first-degree-entailment fragment of relevance logic R by providing an axiomatization for reasoning about belief functions for this logic and by showing that the complexity of the satisfiability problem of a belief formula with respect to the class of the corresponding Dempster–Shafer structures is NP-complete.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Dealing with uncertainty is a fundamental issue for Artificial Intelligence [31]. Numerous approaches have been proposed, including Dempster–Shafer theory of belief functions (also called Dempster–Shafer theory of evidence). Ever since the pioneering works by Dempster [10] and Shafer [52], belief functions were brought into a practically usable form by Smets [59] and have become a standard tool in Artificial Intelligence for knowledge representation and decision-making.
     </paragraph>
     <paragraph>
      Dempster–Shafer belief functions on a finite frame of discernment S are defined on the power set of S, which is a Boolean algebra. They have an attractive mathematical theory and many intuitively appealing properties. Belief functions satisfy the three axioms which generalize the Kolmogorov axioms for probability functions. Interestingly enough, they can also be characterized in terms of mass functions m. Intuitively, for a subset event A, {a mathematical formula}m(A) measures the belief that an agent commits exactly to A, not the total belief that an agent commits to A. Shafer [52] showed that an agentʼs belief in A is the sum of the masses he has assigned to all the subsets of A. This characterization of belief functions through mass functions is simply an example of the well-known Inclusion–Exclusion principle in Enumerative Combinatorics [61] and hence has a strong combinatorial flavor. In this theory, mass functions are recognized as Möbius transforms of belief functions.
     </paragraph>
     <paragraph>
      Dempster–Shafer theory of belief functions is closely related to other approaches dealing with uncertainty. It includes the Bayesian theory [51] as a special case. The first three rules of the Bayesian theory are simply those three axioms for probability functions. It is shown [52] that a belief function on S is Bayesian (also a probability function) if and only if its corresponding mass function assigns positive weights only to singletons. So a Bayesian belief function μ is more like a point function than a set function in its level of complexity in the sense that μ is determined by its values at singletons rather by its values at all events (its values at other non-singletons are 0). This implies that generally Bayesian belief functions are simpler and easier to describe than belief functions. As Shafer pointed out in Chapter 9 of his book [52], this simplicity makes the Bayesian belief functions awkward for the representation of evidence. In practice, the Bayesian approach is criticized for having difficulty in efficiently providing reasonable estimate of the probability of some events and for describing confidence by a single point rather than a range [18]. The main advantage of the Dempster–Shafer theory over the Bayesian theory is that it allows for a proper representation of ignorance under incomplete information and assigns a meaningful interval to an event as a representation of the uncertainty of the event. In this aspect, the theory of belief functions is equivalent to the approach adopted by Fagin and Halpern [18] dealing with uncertainty using inner and outer probability measures. In contrast with the Dempster–Shafer theory, probability theory does not assign a probability to every event [30] and probability measures are defined on a σ-algebra, which is a subclass of the power set of the space under consideration. Non-measurable events, those without probabilities, are usually considered as meaningless in probability theory. However, in modeling uncertainty in artificial intelligence, they are used to represent those events to which an agent has insufficient information to assign probabilities. A non-measurable event E is provided with inner probability measure (outer probability measure) which is the probability of the largest measurable event contained in E (the smallest measurable one containing E). The inner (outer) measure gives a lower bound (upper bound) on the agentʼs degree of beliefs in E. So inner probability measure (together with outer probability measure) induced by probability measure assigns an interval to every event as a representation of uncertainty of the event E, which is similar to belief/plausibility functions. Moreover, belief functions and inner probability measures are equivalent on formulas[18]. There is an immediate payoff to this view of Dempster–Shafer belief functions: a logic for reasoning about belief functions can be obtained from that for inner probability measures [19].
     </paragraph>
     <paragraph>
      The first investigation of mathematical properties of belief functions on more general lattices was initiated by Barthélemy [4] with the combinatorial theory on lattices by Rota [47], which was motivated by possible applications of belief functions for non-standard representation of knowledge. Grabisch [26] continued along this direction and showed that such properties as Dempsterʼs rule of combination and Smetsʼs canonical decomposition [57] in the case of Boolean algebras can be transposed in general lattice setting. This generalized theory has been applied to many objects in real world problems that may not form a Boolean algebra. Let us give some examples: set-valued variables in multi-label classification[13], [70], the set of partitions in ensemble clustering[39] and bi-capacities in cooperative game theory [29]. Because of its generality, however, Grabischʼs theory loses many intuitively appealing properties in the Dempster–Shafer theory. For example, since a lattice does not necessarily admit a probability function [26], belief functions in general lattice settings fail to maintain a close connection with the Bayesian theory and therefore lack many of the desirable properties associated with this theory as in Dempster–Shafer theory [18]. Since pignistic probabilities are used for decision-making in the transferable belief model by Smets [65], [58], it would be impossible to develop decision theory for general lattice structures along a similar line. In particular, most non-classical formalisms{sup:1} in AI assume a setting of distributive lattices and hence it would be difficult to apply Grabischʼs theory directly to obtain a deductive approach for reasoning about belief functions over these formalisms as developed in Section 5 of this paper. Our deductive approach requires a setting of distributive lattices. Moreover, in many real-world problems such as evidential reasoning on fuzzy events [68], [55], [56], [66] and bipolar belief pairs on vague propositions [36] which do assume a setting of distributive lattices, belief functions are defined in totally different forms. It would be desirable to establish a uniform theory for all these applications of belief functions.
     </paragraph>
     <paragraph>
      An optimal balance between utility and elegance of a theory of belief functions is achieved for distributive lattices, which is the main contribution of this paper. Not only does our approach for distributive lattices yield a mathematical theory as appealing as Dempster–Shafer theory, but also its applications extend to many non-classical formalisms of structures in Artificial Intelligence (quantum theory [67] is one of very few important exceptions). The main difficulty in the extension is how to characterize the class of belief functions without reference to mass assignments. Birkhoffʼs fundamental theorem for finite distributive lattices solves this problem. Through this characterization, many fundamental properties of belief functions in the Boolean case are also preserved in distributive lattices. Just as in the Dempster–Shafer theory, we obtain nice formulas for Möbius functions of distributive lattices. We show that, for any lattice (not necessarily distributive), a capacity is totally monotone iff its Möbius transform is non-negative, which answers an open question raised in [26] and further justifies the proposal by Barthélemy and Grabisch that evidential reasoning can be done naturally on lattices while probability theory can only live on distributive lattices. A more fundamental result is that there is a one-to-one correspondence from the perspective viewing belief functions as lower envelopes between belief functions on a distributive lattice L and those on its generated Boolean algebra, which is the smallest Boolean algebra of which L is a sublattice. We establish a close connection to the Bayesian theory by showing that a belief function Bel on a finite distributive lattice L is Bayesian (or a probability function) if and only if all focal elements i.e., those elements with positive weights assigned by its mass function are join-irreducible in L. For belief functions, join-irreducibles to distributive lattices are the same as singletons to Boolean algebras. Moreover, we prove by appealing to Smileyʼs theory on measurability in lattices [60] that belief functions on distributive lattices can be viewed as generalized probability functions in the sense that Bel is equivalent to the inner measure induced by some probability function on formulas. This perspective paves the way to our following deductive approach for reasoning about belief functions.
     </paragraph>
     <paragraph>
      After establishing the mathematical theory for belief functions on distributive lattices, we use this more general theory to provide a framework for reasoning about belief functions in a deductive approach on non-classical formalisms which assume a distributive lattice. The integrating of belief functions and non-classical formalisms is intended to master two sources of ignorance. While belief functions take care of the limitation of the information that the agent has at his disposal, non-classical formalisms usually take care of the incompleteness or inconsistency in the knowledge-base due to imperfect data. So, the advantage of our framework over the well-known work by Fagin and Halpern [18] is that it provides a deductive machinery to reason about belief functions for these non-classical formalisms. As an illustration of this deductive approach, we deal with belief functions on two particular classes of distributive lattices: bilattices and de Morgan lattices, which are actually mathematical objects in reasoning under incomplete and inconsistent information. A well-known simple non-Boolean epistemic logic the first-degree-entailment fragment {a mathematical formula}Rfde of relevance logic R[1] provides a complete deductive system for this type of non-classical information, which is used to deal with the famous logical-omniscience problem in the foundations of Knowledge Representation [20], [37], and used for reasoning in the presence of inconsistency in knowledge base systems [38]. A sound and complete axiomatization is provided for the integration of belief functions and the non-classical logic {a mathematical formula}Rfde, and finally the complexity of the satisfiability problem of a belief formula with respect to the class of the corresponding Dempster–Shafer structures is shown to be NP-complete.
     </paragraph>
     <paragraph>
      Although we have generalized only some important properties in the Dempster–Shafer theory to the setting of distributive lattices, we have no doubt that almost all other important properties in this theory can be transposed in a similar way through the techniques developed in this paper. Note that here we mainly focus on the perspective viewing belief functions as generalized probability functions, which is one of the two perspectives for belief functions pointed out by Halpern and Fagin [32]. The rest is organized as follows. In Section 2, we provide a preliminary background on lattice theory and belief functions on lattices, and answer an open question raised by Grabisch [26]. Section 3 is the main part of this paper. There we generalize the Dempster–Shafer theory on Boolean algebras to the setting of distributive lattices through Birkhoffʼs fundamental theory for finite distributive lattices, establish a close connection to the Bayesian theory and provide a perspective from which belief functions on distributive lattices can be regarded as generalized probability functions. In Section 4, we present the semantical framework for belief functions on both distributive bilattices and de Morgan lattices. In Section 5, we provide a sound and complete deductive system for reasoning about belief functions for the first-degree-entailment fragment of R and show that the complexity of the satisfiability problem of belief formulas with respect to the class of the corresponding Dempster–Shafer structures is NP-complete. And in the final section, we discuss related work and possible applications of our theory in this paper to knowledge representation and decision-making. Appendix A provides some properties of distributive lattices which are needed in other parts of this paper.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Belief function on lattices
     </section-title>
     <paragraph>
      We will first recall some basic definitions about lattices. Next Dempster–Shafer theory of belief functions on Boolean algebras will be generalized to this more general setting.
     </paragraph>
     <paragraph>
      All posets and lattices occurring in this paper are supposed to be finite. All lattice-theoretical notation and terminology in this paper follows [61].
     </paragraph>
     <section label="2.1">
      <section-title>
       Lattices
      </section-title>
      <paragraph>
       A partially ordered set P (or poset for short) is a set (which by abuse of notation we also call P), together with a binary relation denoted ⩽, satisfying the following three axioms:
      </paragraph>
      <list>
       <list-item label="1.">
        For all {a mathematical formula}t∈P,t⩽t (reflexivity).
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}s⩽t and {a mathematical formula}t⩽s, then {a mathematical formula}s=t (antisymmetry).
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}s⩽t and {a mathematical formula}t⩽u, then {a mathematical formula}s⩽u (transitivity).
       </list-item>
      </list>
      <paragraph>
       A subset I of P is called an order ideal (or semi-ideal or down-set or decreasing subset) if, for any {a mathematical formula}x,y∈L, {a mathematical formula}x∈I provided that {a mathematical formula}x⩽y and {a mathematical formula}y∈I. I is called a principal order ideal if {a mathematical formula}I={y∈L:y⩽x} for some {a mathematical formula}x∈I. Otherwise, it is called a non-principal order ideal. Dually, a subset F of L is called a dual order ideal (or up-set or increasing subset or filter) if, for any {a mathematical formula}x,y∈L, {a mathematical formula}y∈F provided that {a mathematical formula}x⩽y and {a mathematical formula}x∈F.
      </paragraph>
      <paragraph>
       A strict partial ordering &lt; is defined from ⩽ as {a mathematical formula}x&lt;y if {a mathematical formula}x⩽y and {a mathematical formula}x≠y. x is said to cover y if {a mathematical formula}x&gt;y and no other element z such that {a mathematical formula}x&lt;z&lt;y. A chain is a poset in which any two elements are comparable. An antichain is a subset {a mathematical formula}C′ of L such that any two distinct elements of {a mathematical formula}C′ are incomparable. A subset C of a poset P is called a chain if C is a chain when regarded as an ordered set in its own right. The chain C of P is called saturated (also maximal) if there does not exist {a mathematical formula}z∈P−C such that {a mathematical formula}x&lt;z&lt;y for some {a mathematical formula}x,y∈C and such that {a mathematical formula}C∪{z} is a chain. The length{a mathematical formula}l(C) of a finite chain is defined by {a mathematical formula}l(C):=|C|−1. The height (or rank) of a finite poset is {a mathematical formula}l(P):=max{C:Cis a chain ofP}. If every maximal chain of P has the same height n, then we say that P is ranked. In this case, the associated rank function{a mathematical formula}ρ:P→{0,1,…,n} is defined as: {a mathematical formula}ρ(x)=0 if x is a minimal element of P, and {a mathematical formula}ρ(y)=ρ(x)+1 if y covers x in P.
      </paragraph>
      <paragraph>
       If s and t belong to a poset P, then an upper bound of s and t is an element {a mathematical formula}u∈P satisfying {a mathematical formula}u⩾s and {a mathematical formula}u⩾t. A least upper bound (or join or supremum) of s and t is an upper bound u of s and t such that every upper bound v of s and t satisfies {a mathematical formula}v⩾u. If a least upper bound exists, then it is clearly unique and is denoted {a mathematical formula}s∨t. Dually one can define the greatest lower bound (or meet or infimum) {a mathematical formula}s∧t, when it exists. A lattice is a poset L for which every pair of elements has a least upper bound and greatest lower bound and is denoted {a mathematical formula}〈L,∨,∧〉. When the context is clear, we simply write the lattice as L. For finite lattices, the greatest element (denoted ⊤) and the least element (denoted ⊥) always exist. An element s of the lattice L is called join-irreducible if {a mathematical formula}s≠⊥ and one cannot write {a mathematical formula}s=t∨u where {a mathematical formula}t&lt;s and {a mathematical formula}u&lt;s; otherwise, it is called join-reducible. Meet-irreducible as well as meet-reducible is defined dually. A lattice {a mathematical formula}〈L′,∨′,∧′〉 is called a sublattice of the lattice {a mathematical formula}〈L,∨,∧〉 if {a mathematical formula}L′⊆L and, for any two elements {a mathematical formula}x,y∈L′, {a mathematical formula}x∧′y=x∧y and {a mathematical formula}x∨′y=x∨y.
      </paragraph>
      <paragraph>
       For a given lattice L, a subset I of L is called an ideal if it is an order ideal with respect to the associated partial order and additionally, for any {a mathematical formula}x,y∈L, {a mathematical formula}x∨y∈I. Dually, a subset F of L is called a filter if it is a dual order ideal (or filter) with respect to the associated partial order and additionally, for any {a mathematical formula}x,y∈F, {a mathematical formula}x∧y∈F. F is called a prime filter if it satisfies the following additional condition: for any {a mathematical formula}a,b∈L, {a mathematical formula}a∈F or {a mathematical formula}b∈F whenever {a mathematical formula}a∨b∈F.
      </paragraph>
      <paragraph>
       The map {a mathematical formula}h:〈L,∧,∨〉→〈L′,∧′,∨′〉 where L and {a mathematical formula}L′ are two lattices is called a homomorphism if, for any two elements {a mathematical formula}x,y∈L, {a mathematical formula}h(x∧y)=h(x)∧′h(y) and {a mathematical formula}h(x∨y)=h(x)∨′h(y). If h is onto, it is called a surjective homomorphism. And if it is one-to-one and onto, then it is called an isomorphism. L can be embedded into {a mathematical formula}L′ if L is isomorphic to a sublattice of {a mathematical formula}L′ (denoted as {a mathematical formula}L≼L′).
      </paragraph>
      <paragraph>
       A lattice L is distributive if {a mathematical formula}(x∨y)∧z=(x∧z)∨(y∧z) holds for all {a mathematical formula}x,y,z∈L. For any {a mathematical formula}x∈L, we say that x has a complement in L if there exists {a mathematical formula}x′∈L such that {a mathematical formula}x∧x′=⊥ and {a mathematical formula}x∨x′=⊤. L is said to be complemented if every element has a complement. Boolean lattices (algebras) are distributive and complemented lattices. In a Boolean lattice, every element has a unique complement. According to the famous Stone representation theorem, every Boolean lattice is isomorphic to the concrete Boolean lattice {a mathematical formula}〈2S,⊆〉 for some set S. For the lattice {a mathematical formula}〈2S,⊆〉, we have {a mathematical formula}∨=∪, {a mathematical formula}∧=∩, {a mathematical formula}⊤=S and {a mathematical formula}⊥=∅.
      </paragraph>
      <paragraph>
       A de Morgan lattice D is a bounded distributive lattice {a mathematical formula}〈D,∨,∧,⊤,⊥〉 with an involution ¬ which satisfies the following de Morganʼs laws:{a mathematical formula} It follows immediately that {a mathematical formula}¬(x∨y)=¬x∧¬y, {a mathematical formula}¬⊤=⊥ and {a mathematical formula}¬⊥=⊤. So ¬ is a dual automorphism. Note that in a de Morgan lattice, the following laws do not always hold:{a mathematical formula}
      </paragraph>
      <paragraph>
       De Morgan lattices are important for the study of the mathematical aspects of fuzzy logic [69]. The standard fuzzy algebra {a mathematical formula}F=〈[0,1],max(x,y),min(x,y),0,1,1−x〉 is an example of a de Morgan lattice. Moreover, de Morgan lattices are the algebraic semantics for the non-classical formalism relevance logic [16].
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Belief functions on lattices
      </section-title>
      <paragraph>
       Let {a mathematical formula}(L,⩽) be a poset having a bottom element ⊥ and a top one ⊤ and {a mathematical formula}R be the real field. Without further notice, every function in this paper is meant to be a real-valued map. The Möbius function{a mathematical formula}μ:L2→R of L is defined recursively by{a mathematical formula} Note that μ solely depends on L.
      </paragraph>
      <paragraph label="Proposition 2.1">
       Möbius inversion formula(See Proposition 3.7.1 in[61].) Let P be a poset. Let f and g be two functions. Then{a mathematical formula}if and only if{a mathematical formula}where μ is the Möbius function of P.
      </paragraph>
      <paragraph>
       The function f in the above proposition is called the Möbius transform of g. And the co-Möbius transform{sup:2} of g, denoted by q, is defined as: for any {a mathematical formula}x∈P,{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 2.2">
       Given a lattice {a mathematical formula}〈L,⩽〉, a function f on L is called a capacity if it satisfies the following three conditions:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}f(⊥)=0;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}f(⊤)=1;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}x⩽y implies {a mathematical formula}f(x)⩽f(y).
       </list-item>
      </list>
      <paragraph>
       Note that any belief function is a monotonic function by nonnegativity of m, and hence a capacity.
      </paragraph>
      <paragraph label="Example 2.3">
       In the above definition, if L is a Boolean algebra, then bel on L is defined in the same way as in the Dempster–Shafer theory [52]. Let Ω be a finite space. In this case, a function {a mathematical formula}m:2Ω→[0,1] is a mass allocation function if {a mathematical formula}m(∅)=0 and {a mathematical formula}∑A⊆Ωm(A)=1. A belief function on Ω is a function {a mathematical formula}bel:2Ω→[0,1] generated by a mass allocation function as follows:{a mathematical formula} Note that {a mathematical formula}bel(∅)=0 and {a mathematical formula}bel(Ω)=1. The Möbius function {a mathematical formula}μ:2Ω×2Ω→[0,1] is{a mathematical formula}m is the Möbius transform of bel and is expressed as the following formula:{a mathematical formula}And the associated plausibility function pl is defined as{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 2.4">
       Let K denote the set {a mathematical formula}{1,2,…,k}. Given a lattice {a mathematical formula}〈L,⩽〉, a function f on L is called a k-monotone whenever for each {a mathematical formula}(x1,…,xk)∈Lk, we have{a mathematical formula} A capacity is totally monotone if it is k-monotone for every {a mathematical formula}k⩾2. A k-monotone function f is called a k-valuation if the above inequality degenerates into the following equality:{a mathematical formula}It is an ∞-valuation if it is a k-valuation for each integer k. f is called a probability function if it is both a capacity and an ∞-valuation.
      </paragraph>
      <paragraph label="Lemma 2.5">
       If L is distributive, then the following equality is sufficient for an ∞-valuation f:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       We prove by induction on the number of disjuncts.
       <list>
        Base case: {a mathematical formula}k=1,2. The equality (4) for ∞-valuation follows immediately from (5).Induction case: Assume that the equality (4) holds for {a mathematical formula}k=n. Now we need to show that it holds for {a mathematical formula}k=n+1.{a mathematical formula}{a mathematical formula} Note that both the third and fourth equalities follow from the Induction Hypothesis.So we have finished the proof that the equality
       </list>
       <paragraph>
        (4) holds.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Before we show Theorem 2.8, we need a lemma, which is obvious in measure theory and follows directly from the above lemma. Define a function {a mathematical formula}μ:P(X)→R on the power set {a mathematical formula}P(X) of an arbitrary finite set X to be additive if {a mathematical formula}μ(∅)=0, and {a mathematical formula}μ(A)+μ(B)=μ(A∩B)+μ(A∪B).
      </paragraph>
      <paragraph label="Lemma 2.6">
       If μ is additive, then{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       The lemma follows from Lemma 2.5 and the fact that {a mathematical formula}P(X) with the usual set operations is a Boolean algebra and hence is a distributive lattice. This is also well-known as the principle of inclusion and exclusion in probability theory (formula (2.9) on page 24 in [8]).  □
      </paragraph>
      <paragraph>
       The following proposition [4] tells us that every belief function is totally monotone.
      </paragraph>
      <paragraph label="Proposition 2.7">
       Let{a mathematical formula}f:L→[0,1]be a capacity and m be its Möbius transform. If f is a belief function, then it is totally monotone.
      </paragraph>
      <paragraph>
       Shafer proved that the converse is also true for any belief function on Boolean algebras (Theorem 2.1 in [52]). We show that actually it holds generally for any lattice, which answers an open question raised in [26].
      </paragraph>
      <paragraph label="Theorem 2.8">
       Let L be a lattice and{a mathematical formula}f:L→[0,1]be a capacity on L and m be its Möbius transform. The following two statements are equivalent:
      </paragraph>
      <list>
       <list-item label="•">
        m is nonnegative;
       </list-item>
       <list-item label="•">
        f is totally monotone.
       </list-item>
      </list>
      <paragraph>
       The essential part of the following proof is based on a structurally inductive construction of the Möbius transform m from f: {a mathematical formula}m(a)=f(a)−∑b&lt;am(b).
      </paragraph>
      <paragraph label="Proof">
       Here we only need to show that, if f is totally monotone, then its Möbius transform m is nonnegative, since the other direction is simply Proposition 2.7. That is to say, any totally monotone capacity on a lattice is a belief function. Given a totally monotone capacity f on L, we are computing inductively {a mathematical formula}m:L→R as follows:
       <list label="Claim 1">
        For the minimal element ⊥, {a mathematical formula}m(⊥)=0;For any non-minimal element {a mathematical formula}a∈L,{a mathematical formula}{a mathematical formula}m(a)⩾0for all{a mathematical formula}a∈L.It is easy to see that, when
       </list>
       <paragraph>
        a is the minimal element, {a mathematical formula}m(a)⩾0. Now assume that a is a non-minimal element. We need to show that {a mathematical formula}m(a)⩾0. Let {a mathematical formula}A:={x:x∈L,x&lt;a}. For each {a mathematical formula}b&lt;a, {a mathematical formula}Ib denotes the set {a mathematical formula}{x:x∈L,x⩽b}. It is easy see that {a mathematical formula}A=⋃b&lt;aIb. So{a mathematical formula}{a mathematical formula}The first equality comes from Lemma 2.6 if we define an additive set function {a mathematical formula}μ(X):=∑x∈Xm(x) for all {a mathematical formula}X⊆L. In other words, {a mathematical formula}∑b∈{x∈L:x&lt;a}m(b)=∑J⊆{x∈L:x&lt;a},J≠∅(−1)|J|+1f(⋀x∈Jx). Moreover, since f is a totally monotonic capacity,{a mathematical formula} Note that the second inequality comes from the total monotonicity of f. It follows that{a mathematical formula}
       </paragraph>
      </paragraph>
      <paragraph>
       So any probability function is also a belief function. From Proposition A.1 in Appendix A, we know that a belief function can be defined on any lattice while probability functions can live only on distributive lattices. In Example 2 in [27], Grabisch constructed a “counterexample” to show that Theorem 2.8 does not hold. But, his counterexample does not work because 6-monotonicity there is equivalent to {a mathematical formula}1⩾6β−6α not to {a mathematical formula}1⩾6β−9α as provided by Grabisch.
      </paragraph>
      <paragraph label="Example 2.9">
       Here we adapt an example of belief functions on set-valued variables [13] from [12] to illustrate the theory in this section. Let {a mathematical formula}Θ={a,b,c,d} be the set of possible faults of a given system. For any {a mathematical formula}A,B⊆Θ, {a mathematical formula}[A,B] denotes the interval {a mathematical formula}{C⊆Θ:A⊆C⊆B}. The interval means that the faults in B may be present but those in A are definitely present in the system. Let Ω be the set of all these intervals in Θ. Ω is a lattice associated with the following two operations: for any two {a mathematical formula}[A1,A2],[B1,B2]∈Ω,{a mathematical formula} and{a mathematical formula} where {a mathematical formula}∅Ω is the empty set of Ω while {a mathematical formula}∅Θ denotes the empty set of Θ.From different pieces of evidence, we may derive the representation of degrees of beliefs in different events as the following mass assignment:{a mathematical formula}{a mathematical formula}It is easy to check that {a mathematical formula}〈Ω,∧,∨〉 is a lattice but not distributive and even the focal elements donʼt satisfy the law of distributivity. For example,{a mathematical formula} From the above mass assignment, we may derive the degree of belief in the proposition that fault d is not present:{a mathematical formula}
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Belief functions on distributive lattices
     </section-title>
     <paragraph>
      In this section, we study belief functions on distributive lattice from two perspectives. The first one treats mass functions on distributive lattices as the Möbius transforms of their corresponding belief functions, and characterizes belief functions without reference to mass assignments. A more general result is that there is a one-to-one correspondence between belief functions on a distributive lattice L and those on its generated Boolean algebra, which is the smallest Boolean algebra of which L is a sublattice. We rely on the techniques from Birkhoffʼs representation theorem for finite distributive lattices (Theorem A.2 in Appendix A). The second one regards belief functions as generalized probability functions. More specifically, we investigate the condition when a belief function is Bayesian or a probability function and the perspective from which belief functions can be regarded as inner probability functions. So, in the general setting of distributive lattices, a key part of the theory of belief functions is firmly rooted in probability theory. The immediate payoff to this view is a logic of reasoning about belief functions, which will be provided in Section 5.
     </paragraph>
     <section label="3.1">
      <section-title>
       Möbius transforms of belief functions
      </section-title>
      <paragraph>
       Given a poset P, {a mathematical formula}J(P) denotes the lattice of order ideals of P with the ordinary union and intersection (as subsets of P). So {a mathematical formula}J(P) is distributive. Conversely, from Theorem A.2 (Birkhoffʼs fundamental theorem for finite distributive lattices) in Appendix A, we know that for any finite distributive lattice L, there is a unique (up to isomorphism) finite poset P for which {a mathematical formula}L≅J(P). Usually P is chosen to be the poset of join-irreducibles in L. Note that all valid propositions for {a mathematical formula}J(P) are dually valid for {a mathematical formula}F(P), which denotes the lattice of filters of P with the ordinary union and intersection. If we replace in this section all posets {a mathematical formula}〈P,⩽〉 by its dual {a mathematical formula}〈P,⩽∂〉 (where {a mathematical formula}x⩽∂y iff {a mathematical formula}y⩽x) and all ⩽-order ideals by {a mathematical formula}⩽∂ filters, the dual forms of these propositions remain valid.
      </paragraph>
      <paragraph>
       The following two propositions provide formulas for Möbius functions and Möbius transforms in distributive lattices.
      </paragraph>
      <paragraph label="Proposition 3.1">
       (See Example 3.9.6 in[61].) The Möbius function of the distributive lattice{a mathematical formula}L=J(P)where P is a poset is: for any{a mathematical formula}I,I′∈J(P),{a mathematical formula}where{a mathematical formula}[I,I′]denotes the interval{a mathematical formula}{K∈J(P):I⊆K⊆I′}.
      </paragraph>
      <paragraph>
       From this proposition, we immediately obtain a nice formula for Möbius transforms.
      </paragraph>
      <paragraph label="Theorem 3.2">
       Let{a mathematical formula}L=J(P)be a distributive lattice for some poset P. Suppose{a mathematical formula}Bel:L→[0,1]is the belief function given by the mass assignment{a mathematical formula}m:L→[0,1]. Then{a mathematical formula}for all{a mathematical formula}A∈J(P).
      </paragraph>
      <paragraph>
       In order to compare the following proposition to Theorem 2.1 in [52], we prove the following proposition from the above two theorems about Möbius transforms along the same line as Shaferʼs proof of Theorem 2.1 in [52]. The relationship to Shaferʼs original proof on Boolean algebras can be made through the following fact (Section 3.4. in [61]): for any two elements {a mathematical formula}I,I′∈J(P) for some poset P, {a mathematical formula}[I,I′] is a Boolean algebra iff {a mathematical formula}I′∖I is an antichain.
      </paragraph>
      <paragraph>
       The following theorem is also the distributive version of Theorem 2.8.
      </paragraph>
      <paragraph label="Theorem 3.3">
       Given a distributive lattice{a mathematical formula}L=J(P), a monotonic function{a mathematical formula}Bel:L→[0,1]is a belief function iff it satisfies the following conditions:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Bel(⊥)=0;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Bel(⊤)=1;
       </list-item>
       <list-item label="3.">
        For every positive number n and every collection{a mathematical formula}A1,…,Anof elements of L,{a mathematical formula}
       </list-item>
      </list>
      <paragraph label="Proof">
       The left-to-right direction is simply Proposition 2.7. Now we mainly focus on the right-to-left direction. Assume that Bel satisfies the above three conditions and, for any {a mathematical formula}A∈L, {a mathematical formula}Bel(A)=∑B⊆Am(B). According to Theorem 3.2, we know its Möbius transform:{a mathematical formula} In order to show that Bel is a belief function, it suffices to show that {a mathematical formula}m(A)⩾0 for all {a mathematical formula}A∈L=J(P). Give an element {a mathematical formula}A∈J(P), define {a mathematical formula}Amax to be the set of maximal elements of A in P. It is easy to see that
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}A∖Amax is an order ideal in P and hence is an element of {a mathematical formula}J(P) and
       </list-item>
       <list-item label="•">
        {a mathematical formula}Amax is an antichain in P.
       </list-item>
      </list>
      <paragraph>
       This theorem gives another characterization of belief functions on distributive lattices without reference to mass functions. So it plays an important role in our axiomatization of reasoning about belief functions. If L is Boolean, then the formulas in Proposition 3.1 and Theorem 3.2 are the same as those corresponding formulas in Example 2.3.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Belief functions on distributive lattices and Boolean algebras
      </section-title>
      <paragraph>
       In this subsection, we discuss some direct connections between belief functions on distributive lattices to those on Boolean algebras. Given a distributive lattice {a mathematical formula}L=J(P) for some poset P, we know that L as a lattice is a sublattice of the powerset of P with the usual set operations, which is a Boolean algebra. So, for any distributive lattice L, the set of Boolean algebras of which L is a sublattice is not empty, i.e., {a mathematical formula}{B:Lis a sublattice ofBandBis a Boolean algebra}≠∅. Also the intersection of any finite number of Boolean algebras is a Boolean algebra.
      </paragraph>
      <paragraph label="Definition 3.4">
       A Boolean algebra {a mathematical formula}BL is generated by the distributive lattice L if {a mathematical formula}BL=⋂{B:L is a sublattice of BandBisaBoolean algebra}.
      </paragraph>
      <paragraph>
       If {a mathematical formula}L=J(P) is a distributive lattice for some poset P, then the Boolean algebra {a mathematical formula}BL generated by L is the powerset of P with the usual set operations (Theorem 2.1. in [41]). A more general result than this lemma but in a different form follows from Theorem 1 in [45]. For any two Boolean algebras {a mathematical formula}B1 and {a mathematical formula}B2, {a mathematical formula}B1≼B2 iff {a mathematical formula}|B1|⩽|B2|. So, for any distributive lattice L, the generated Boolean algebra {a mathematical formula}BL is the smallest Boolean algebra into which L can be embedded.
      </paragraph>
      <paragraph label="Lemma 3.5">
       Let L be a finite distributive lattice and{a mathematical formula}BLbe the Boolean algebra generated by L. If μ is a probability function on L, then μ has a unique extension of probability function on{a mathematical formula}BL. Conversely, if μ is a probability function on{a mathematical formula}BL, then the restriction of μ into L is also a probability function on L.
      </paragraph>
      <paragraph label="Proof">
       Since the second part is clear, we focus on the first one. Assume that {a mathematical formula}L=J(P) for some poset P and μ is a probability function on L. According to the above discussion, we know that {a mathematical formula}2P with the usual set operations is the Boolean algebra generated by {a mathematical formula}J(P). In order to extend the probability function on {a mathematical formula}L=J(P) to {a mathematical formula}2P, it suffices to know probabilities on singletons. For any {a mathematical formula}x∈P, define {a mathematical formula}μ¯({x}):=μ((x])−μ((x]∖{x}) where {a mathematical formula}(x]:={y∈L:y⩽x}. Note that the last two probabilities are well-defined because both {a mathematical formula}(x] and {a mathematical formula}(x]∖{x} are elements of {a mathematical formula}J(P). Probabilities of all other subsets of P can be obtained easily from the additivity property. Since the extended probability function {a mathematical formula}μ¯ on {a mathematical formula}BL totally depends on the function μ on L, this extension is unique.  □
      </paragraph>
      <paragraph>
       In the following, we use {a mathematical formula}μ¯ to denote this unique extension on {a mathematical formula}BL for any probability function μ on L. So there is a one-to-one correspondence between probability functions on a distributive lattice and those on its generated Boolean algebra. Surprisingly, this property is also shared by belief functions.
      </paragraph>
      <paragraph label="Lemma 3.6">
       Let L be a finite distributive lattice and{a mathematical formula}BLbe the Boolean algebra generated by L. For any belief function Bel on{a mathematical formula}BL, the restriction{a mathematical formula}Bel↾Lof Bel to L is a belief function on L.
      </paragraph>
      <paragraph label="Proof">
       The proof follows from Theorem 3.3. It is easy to check that {a mathematical formula}Bel↾L satisfies the following properties:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}Bel↾L(⊥)=0;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}Bel↾L(⊤)=1;
       </list-item>
       <list-item label="3.">
        For every positive number n and every collection {a mathematical formula}x1,…,xn of elements of L,{a mathematical formula}
       </list-item>
      </list>
      <paragraph label="Lemma 3.7">
       Let L be a finite distributive lattice and{a mathematical formula}BLbe the Boolean algebra generated by L. Any belief function Bel on L can be extended to a belief function{a mathematical formula}Bel⁎on{a mathematical formula}BLin the sense that, for any{a mathematical formula}x∈L,{a mathematical formula}Bel⁎(x)=Bel(x).
      </paragraph>
      <paragraph label="Proof">
       Here we will appeal to the fundamental theorem for belief functions on distributive lattices Theorem 3.3. For a belief function Bel on L, there is a mass assignment m on L such that, for any {a mathematical formula}x∈L, {a mathematical formula}m(x)⩾0 and {a mathematical formula}Bel(x)=∑y⩽xm(y). Now we define a mass assignment {a mathematical formula}m⁎ on {a mathematical formula}BL which is an extension of m on L. Define{a mathematical formula}According to Theorem 3.3, there is a belief function {a mathematical formula}Bel⁎ on {a mathematical formula}BL: {a mathematical formula}Bel⁎(x):=∑y⩽xm⁎(y) which is an extension of Bel on L in the sense that, for any element {a mathematical formula}x∈L, {a mathematical formula}Bel(x)=Bel⁎(x).  □
      </paragraph>
      <paragraph>
       However, the extension of belief functions on distributive lattice to their generated Boolean algebras are generally not unique. Consider a simple poset {a mathematical formula}P0=〈{x1,x2},{(x1,x1),(x2,x2),(x1,x2)}〉. The Hasse diagram of this poset is illustrated in Fig. 1.
      </paragraph>
      <paragraph>
       Now we define a belief function Bel on {a mathematical formula}L0:=J(P0) as follows: {a mathematical formula}m({x1})=12=m({x1,x2}). So {a mathematical formula}Bel({x1})=12, and {a mathematical formula}Bel({x1,x2})=1. In addition to the type of extension {a mathematical formula}Bel⁎ in Lemma 3.7, there is at least another different extension {a mathematical formula}Bel′ on the generated Boolean algebra {a mathematical formula}BL0 with the following mass assignment {a mathematical formula}m′: {a mathematical formula}m′({x1})=12,m′({x2})=14,m′({x1,x2})=14.
      </paragraph>
      <paragraph>
       But, in the following, we show that {a mathematical formula}Bel⁎ in Lemma 3.7 is unique from the perspective viewing belief functions as lower envelopes. For any belief function Bel on a distributive lattice L, we define{a mathematical formula} where {a mathematical formula}μ⩾Bel means that, for all {a mathematical formula}x∈L, {a mathematical formula}μ(x)⩾Bel(x).
      </paragraph>
      <paragraph label="Lemma 3.8">
       For any{a mathematical formula}x∈L,{a mathematical formula}Bel(x)=inf{μ(x):μ∈PBel}.
      </paragraph>
      <paragraph label="Proof">
       It suffices to show that, for each {a mathematical formula}x∈L, there is a probability function {a mathematical formula}μ∈PBel such that {a mathematical formula}μ(x)=Bel(x). But this follows directly from Lemma 3.5, Lemma 3.7 and Dempsterʼs similar result on Boolean algebras [10]. Given {a mathematical formula}x∈L and a belief function Bel on L, we consider x as an element in {a mathematical formula}BL and Bel as {a mathematical formula}Bel⁎ on {a mathematical formula}BL. According to Dempsterʼs result on Boolean algebras [10], we know that there is a probability function {a mathematical formula}μ′∈PBel⁎ (i.e., for every element {a mathematical formula}a∈BL, {a mathematical formula}μ′(a)⩾Bel⁎(a)) such that {a mathematical formula}μ′(x)=Bel⁎(x). It follows that {a mathematical formula}μ′↾L(x)=Bel(x).  □
      </paragraph>
      <paragraph>
       Recall that {a mathematical formula}μ¯ denotes the unique extension of a probability function μ on L to {a mathematical formula}BL (Lemma 3.5). The extension {a mathematical formula}Bel⁎ defined in Lemma 3.7 is unique in the following sense.
      </paragraph>
      <paragraph label="Theorem 3.9">
       For any{a mathematical formula}x∈BL,{a mathematical formula}Bel⁎(x)=inf{μ¯(x):μ∈PBel}.
      </paragraph>
      <paragraph label="Claim 2">
       Without loss of generality, we assume that {a mathematical formula}L=J(P) and {a mathematical formula}BL=2P for some poset P. From the above lemma, we know that, for any {a mathematical formula}A∈L, {a mathematical formula}Bel⁎(A)=inf{μ¯(A):μ∈PBel}. It suffices to show the following claim: For any{a mathematical formula}A∈BL∖L, there is a probability function{a mathematical formula}μ∈PBelsuch that{a mathematical formula}μ¯(A)=Bel⁎(A).Denote {a mathematical formula}A⁎=⋃{I∈J(P):I⊆A}, {a mathematical formula}A⁎=⋂{I∈J(P):I⊇A} and {a mathematical formula}A−=A⁎∖A. Note that {a mathematical formula}A⁎∈J(P),A⁎∈J(P), {a mathematical formula}A⁎⊊A⊊A⁎ and hence {a mathematical formula}A−≠∅. It follows from Lemma 3.8 that there is a probability function {a mathematical formula}μ∈PBel on {a mathematical formula}J(P) such that {a mathematical formula}Bel⁎(A)=Bel(A⁎)=μ(A⁎).If {a mathematical formula}μ¯(A)=Bel⁎(A)(=μ(A⁎)), then we are done. If {a mathematical formula}μ¯(A)&gt;Bel⁎(A)(=μ¯(A⁎)=μ(A⁎)), then we need to construct a new probability function {a mathematical formula}μA such that {a mathematical formula}μA↾L∈PBel and {a mathematical formula}μA(A)=μ(A⁎) in order to prove the claim. Recall that, for each {a mathematical formula}a∈P, {a mathematical formula}(a] denotes the set {a mathematical formula}{b∈P:b⩽a}. For each {a mathematical formula}a∈A∖A⁎, {a mathematical formula}(a]∩A−≠∅. For, otherwise, since {a mathematical formula}(a]⊆A⁎, {a mathematical formula}A⁎⊊(a]∪A⁎⊆A, which contradicts the fact that {a mathematical formula}A⁎ is the largest element in L that is a subset of A. Let {a mathematical formula}fA denote a function from {a mathematical formula}A∖A⁎ to {a mathematical formula}A− such that, for each {a mathematical formula}a∈A∖A⁎,fA(a)∈(a]∩A−.Now we transpose the mass of {a mathematical formula}μ¯ at each {a mathematical formula}a∈A∖A⁎ to {a mathematical formula}fA(a) in {a mathematical formula}(a]∩A−. We define a new probability function {a mathematical formula}μA on {a mathematical formula}BL with the mass assignment as follows: for any {a mathematical formula}a∈P,{a mathematical formula}The transposition defined in {a mathematical formula}μA can be illustrated in Fig. 2.It is easy to see that {a mathematical formula}∑a∈PμA({a})=1 and hence it defines a probability function on {a mathematical formula}BL, which is still denoted as {a mathematical formula}μA. Note that {a mathematical formula}μA(A)=μ¯(A⁎)=Bel⁎(A) and the only elements in P where the masses of {a mathematical formula}μA may be smaller than those of {a mathematical formula}μ¯ are those elements in {a mathematical formula}A∖A⁎. In order to show that {a mathematical formula}μA is the probability function that we want, we only need to show that, for all {a mathematical formula}I∈J(P), {a mathematical formula}μA(I)⩾Bel(I). For every {a mathematical formula}I∈J(P), if {a mathematical formula}a∈I and {a mathematical formula}a∈A∖A⁎, then {a mathematical formula}fA(a)∈(a]⊆I. So{a mathematical formula}This equality implies that, for each {a mathematical formula}I∈J(P), {a mathematical formula}μA(I)⩾μ¯(I). Since {a mathematical formula}μ∈PBel and {a mathematical formula}μ¯ is the extension of μ, {a mathematical formula}μA(I)⩾Bel(I). So we have shown that {a mathematical formula}μA(A)=Bel⁎(A) and {a mathematical formula}μA↾L∈PBel.  □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Bayesian belief functions
      </section-title>
      <paragraph>
       In this part, we investigate Bayesian belief functions and the condition in the setting of distributive lattices when a belief function is Bayesian. Shafer showed that a belief function on a Boolean algebra is Bayesian if and only if all of its focal elements are singletons (Theorem 2.8 in [52]). We have a similar property for distributive lattices. This property can be summarized in a simple comparison: join-irreducibles to distributive lattices are the same as singletons to Boolean algebras.
      </paragraph>
      <paragraph label="Definition 3.10">
       Given a distributive lattice {a mathematical formula}L=〈L,⩽〉, a belief function {a mathematical formula}Bel:L→[0,1] is called Bayesian if,{a mathematical formula}
      </paragraph>
      <paragraph>
       From Lemma 2.5, for any distributive lattice {a mathematical formula}L=〈L,⩽〉, a belief function {a mathematical formula}Bel:L→[0,1] is Bayesian if and only if it is a probability function.
      </paragraph>
      <paragraph label="Remark 3.11">
       The condition (7) canʼt be replaced with another simpler but weaker additivity condition:{a mathematical formula} The counterexample is illustrated in Fig. 3.It is easy to see that the above lattice {a mathematical formula}L0 is a distributive lattice. Define a function {a mathematical formula}Bel:L0→[0,1] as follows:{a mathematical formula} The condition (8) hold vacuously for the above defined Bel. However, {a mathematical formula}Bel(a∨b)+Bel(a∧b)≠Bel(a)+Bel(b). This implies that the condition (7) does not hold for Bel.
      </paragraph>
      <paragraph label="Definition 3.12">
       Let Bel be a belief function on a distributive lattice L with the set {a mathematical formula}IL of join-irreducibles in L. The inner belief function{a mathematical formula}Bel∘ of Bel is defined as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       In other words, {a mathematical formula}Bel∘(a) is the sum of all mass assignments on join-irreducibles which are less than or equal to a. So {a mathematical formula}Bel∘(a)⩽Bel(a).
      </paragraph>
      <paragraph label="Lemma 3.13">
       Let Bel be a belief function on a distributive lattice L with the set{a mathematical formula}ILof join-irreducibles in L. Then the above defined inner belief function{a mathematical formula}Bel∘is an ∞-valuation on L.
      </paragraph>
      <paragraph label="Proof">
       Let Bel be a belief function on a distributive lattice L with the set {a mathematical formula}IL of join-irreducibles in L and {a mathematical formula}Bel∘ be the corresponding inner belief function. For any elements {a mathematical formula}a1,…,an∈L,{a mathematical formula} The second equality follows from the fact that, for elements {a mathematical formula}x,x1,…,xn in a distributive lattice, if {a mathematical formula}x⩽⋁1⩽i⩽nxi and x is join-irreducible, then {a mathematical formula}x⩽xi at least for some {a mathematical formula}xi ({a mathematical formula}1⩽i⩽n). And the third one comes from Lemma 2.6 if we define an additive set function {a mathematical formula}μ(X):=∑x∈Xm(x) for all {a mathematical formula}X⊆L. For example, {a mathematical formula}μ({x∈L:x is join-irreducible and x⩽ai})=∑xis join-irreduciblex⩽aim(x).So indeed {a mathematical formula}Bel∘ is an ∞-valuation on L.  □
      </paragraph>
      <paragraph>
       Note that {a mathematical formula}Bel∘ is not necessarily a probability function on L because {a mathematical formula}Bel∘(⊤) may not be equal to 1. The following theorem is a partial converse to this lemma and is also the distributive counterpart of Lemma 2.7 in [52].
      </paragraph>
      <paragraph label="Theorem 3.14">
       A belief function Bel on a distributive lattice{a mathematical formula}L=J(P)where P is a poset is Bayesian iff its corresponding mass assignment m is given by{a mathematical formula}m(A′)=Bel(A′)for any minimal join-irreducibles{a mathematical formula}A′in{a mathematical formula}J(P)and{a mathematical formula}m(A)=0for all join-reducibles{a mathematical formula}A∈J(P).
      </paragraph>
      <paragraph label="Proof">
       Let Bel be a belief function on a distributive lattice {a mathematical formula}L=J(P) where P is a poset and m be its corresponding mass assignment. First note that
       <list>
        {a mathematical formula}I∈J(P) is join-irreducible in the lattice {a mathematical formula}J(P) iff I is a principal order ideal in P;Minimal join-irreducible elements are atoms, hence singletons. And {a mathematical formula}A′ is a minimal join-irreducible in {a mathematical formula}J(P) iff {a mathematical formula}A′={θ} for some minimal element {a mathematical formula}θ∈P.Assume that
       </list>
       <paragraph label="Claim 4">
        Bel is also a probability function on {a mathematical formula}J(P).For any minimal element{a mathematical formula}θ∈P,{a mathematical formula}Bel({θ})=m({θ}).It follows directly from the fact that, for any minimal element {a mathematical formula}θ∈P, {a mathematical formula}{θ} is a singleton principal order ideal of P, i.e., {a mathematical formula}{θ}∈J(P) that {a mathematical formula}Bel({θ})=m({θ}). Next we show{a mathematical formula}m(A)=0for all join-reducibles A in L, which are non-principal order ideals of P.We prove this by induction on the rank of A, which is actually the number {a mathematical formula}|A| of elements in A (according to Theorem A.4 in Appendix A). Note that the lowest rank of a join-reducible element in L is 2.
       </paragraph>
       <list>
        <list-item label="•">
         Base case: {a mathematical formula}rank(A)=2 and A is a non-principal order ideal of P. It follows that {a mathematical formula}A={a1,a2} for some two distinct minimal elements {a mathematical formula}a1 and {a mathematical formula}a2 in P. Since Bel is a probability function, {a mathematical formula}Bel({a1,a2})=Bel({a1})+Bel({a2}). On the other hand, since Bel is a belief function, {a mathematical formula}Bel({a1,a2})=m({a1,a2})+m({a1})+m({a2}). From the above Claim 3, it follows that {a mathematical formula}m({a1,a2})=0.
        </list-item>
        <list-item label="•">
         Induction case: Suppose that {a mathematical formula}m(A′)=0 for all non-principal order ideals {a mathematical formula}A′ of rank ⩽k. Given a non-principal order ideal A of rank {a mathematical formula}k+1, we need to show that {a mathematical formula}m(A)=0. First note that, for any order ideal B (not necessarily non-principal) of rank ⩽k,{a mathematical formula} Since A is a non-principal order ideal in P, it must be a union of some different principal order ideals {a mathematical formula}(a1],…,(an] for some {a mathematical formula}a1,…,an∈P where {a mathematical formula}n⩾2 and {a mathematical formula}(ai]={x∈L:x⩽ai}(1⩽i⩽n).{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}It follows that {a mathematical formula}m(A)=0. So we have finished the induction case and hence the claim.
        </list-item>
       </list>
       <paragraph>
        By summarizing the above inductive proof, we prove the left-to-right direction. Now we go for the other direction.Assume that the mass assignment m that corresponds to Bel is given by {a mathematical formula}m({θ})=Bel({θ}) for any minimal elements θ in P and {a mathematical formula}m(A)=0 for all non-principal order ideals {a mathematical formula}A∈J(P). It immediately follows that, for any {a mathematical formula}A′∈J(P), {a mathematical formula}Bel(A′)=Bel∘(A′). So indeed Bel is an ∞-valuation and hence a probability function on {a mathematical formula}J(P).  □
       </paragraph>
      </paragraph>
      <paragraph label="Corollary 3.15">
       A belief function Bel on a distributive lattice is Bayesian (or a probability function) iff all its focal elements are join-irreducibles.
      </paragraph>
      <paragraph>
       So a Bayesian belief function (or probability function) μ on a distributive lattice {a mathematical formula}L=J(P) for some poset P is more like a point function than a set function in its level of complexity in the sense that μ is determined by its values at elements of P (which correspond to principal order ideals in P) rather by its values at all order ideals of P (all values at non-principal order ideals are 0). This implies that generally probability functions are simpler and easier to describe than belief functions.
      </paragraph>
      <paragraph>
       The Bayesian theory adopts a rule of conditioning for updating beliefs, which is a special case of Dempsterʼs rule of combination in the Dempster–Shafer theory. Since this rule is related to another view of belief functions as evidence, we choose to leave it for another occasion.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Belief functions as inner probability functions
      </section-title>
      <paragraph>
       We have provided the condition when a belief function is Bayesian. In the remainder of this section, we explore one perspective from which a belief function is regarded as a generalized probability function in the sense that a belief function can be regarded as an inner probability function of a certain structure. The significance of this perspective is that the satisfiability problem of a given belief formula with respect to the class of belief-function structures is equivalent to that with respect to the class of probability-function structures. So we can translate the complexity of satisfiability problem with respect to the class of belief-function structures into that of satisfiability problem with respect to the class of probability structures, which follows directly from the well-known result in [18] with respect to the class of Boolean algebras as well as the representation theorem for distributive lattices (Theorem A.2 in Appendix A). In Section 5, we show that the complexity of deciding whether a belief formula is satisfiable with respect to the class of belief-function structures on distributive lattices (especially on those structures for many non-classical logics) is NP-complete. Moreover, this perspective provides an alternative representation of belief functions to the well-known one by Shafer through the composition of probability functions with ∩-homomorphisms [53].
      </paragraph>
      <paragraph>
       Unlike belief functions, probability functions in classical probability theory and measure theory [30] are usually not defined on all events. Letʼs consider a probability function Pr on the structure called measurable space{a mathematical formula}〈S,A〉 where S is a finite sample space and {a mathematical formula}A is an algebra on S and is a subclass of {a mathematical formula}2S. Pr is defined on {a mathematical formula}A but not on {a mathematical formula}2S. In other words, not every subset of {a mathematical formula}2S, which is called an event, is assigned a probability. Only those in {a mathematical formula}A are assigned a probability and are called “measurable”. Non-measurable events are usually considered mathematically meaningless. However, the notion of non-measurability is a desirable feature in reasoning with probabilities [18]. It provides a means to model uncertainty under incomplete information. The example in Section 1 in [11] and Example 2.3 in [18] give a motivation for this notion in dealing with uncertainty.
      </paragraph>
      <paragraph>
       In order to generalize the above idea to the setting of distributive lattices, we need first to define the notion of measurability. Let L be a distributive lattice and Bel be a belief function on L. Define{a mathematical formula} Every element {a mathematical formula}a∈LBel is called Bel-measurable or simply measurable when the context is clear. This is a natural generalization of a classic approach to measure extension due to Caratheodory [8]. From Theorem 1 in [60], the following theorem follows immediately:
      </paragraph>
      <paragraph label="Theorem 3.16">
       {a mathematical formula}LBelis a sublattice of L and hence is distributive. Moreover,{a mathematical formula}Bel↾LBelis a probability function on{a mathematical formula}LBel.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}L′ be a sublattice of L. So {a mathematical formula}L′ is distributive. If μ is a probability function on {a mathematical formula}L′, then, for each element {a mathematical formula}x∈L, we can define
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}μ⁎(x)=sup{μ(y):y∈L′,y⩽x};
       </list-item>
       <list-item label="•">
        {a mathematical formula}μ⁎(x)=inf{μ(y):y∈L′,y⩾x}.
       </list-item>
      </list>
      <paragraph>
       The above defined two functions {a mathematical formula}μ⁎ and {a mathematical formula}μ⁎ on L are called inner and outer probability functions on L respectively. Note that they depend on the choice of {a mathematical formula}L′. The probability function μ assigns a precise probability to each element in the sublattice{a mathematical formula}L′ and is not well-defined at other elements in L. So it is actually a partial function on L. In contrast, both {a mathematical formula}μ⁎ and {a mathematical formula}μ⁎ which are induced by μ, are total on L. Intuitively, for each element {a mathematical formula}a∈L, {a mathematical formula}μ⁎(a) is the probability of the biggest element in {a mathematical formula}L′ which is less than or equal to a; dually, {a mathematical formula}μ⁎(a) is the probability of the smallest element in {a mathematical formula}L′ which is greater than or equal to a. In other words, given the probability function on the sublattice {a mathematical formula}L′, {a mathematical formula}μ⁎ and {a mathematical formula}μ⁎ give the best bounds on the “true” probability at each element {a mathematical formula}a∈L.
      </paragraph>
      <paragraph>
       The following proposition reveals a relation of inner probability functions to belief functions.
      </paragraph>
      <paragraph label="Lemma 3.17">
       The above defined{a mathematical formula}μ⁎is a belief function on L.
      </paragraph>
      <paragraph label="Claim 5">
       Let L be a distributive lattice, {a mathematical formula}L′ be a sublattice and μ be a probability function on {a mathematical formula}L′. It follows that there is a mass assignment {a mathematical formula}mL′ that corresponds to μ such that, for any element {a mathematical formula}a∈L′, {a mathematical formula}μ(a)=∑b⩽a,b∈L′mL′(b). Now we define a mass assignment {a mathematical formula}mL on L as follows:{a mathematical formula} It is easy to see that {a mathematical formula}mL(a)⩾0 for all {a mathematical formula}a∈L. In other words, {a mathematical formula}mL is an extension of {a mathematical formula}mL′ to L.For the above defined{a mathematical formula}μ⁎,{a mathematical formula}μ⁎(a)=∑b∈L′,b⩽amL(b)for all{a mathematical formula}a∈L.For any {a mathematical formula}a∈L, let {a mathematical formula}aL′:=⋁y⩽ay∈L′y. The proof of the claim proceeds as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula} This is to say, {a mathematical formula}μ⁎ is a belief function on L that corresponds to the mass assignment {a mathematical formula}mL.  □
      </paragraph>
      <paragraph label="Corollary 3.18">
       If Bel is a belief function on a distributive lattice L, then{a mathematical formula}Bel⩾(Bel↾LBel)⁎in the sense that{a mathematical formula}Bel(a)⩾(Bel↾LBel)⁎(a)for all{a mathematical formula}a∈L.
      </paragraph>
      <paragraph>
       Lemma 3.17 says that every inner probability function is a belief function. But the converse does not quite hold. Let Bel be a belief function on the powerset of {a mathematical formula}S={s1,s2} such that {a mathematical formula}Bel({s1})=12 and {a mathematical formula}Bel({s2})=0. It is easy to check that Bel is not an inner probability function. So the inequalities in the above corollary may be strict. Still we can show that any belief function on a distributive lattice L is equivalent to an inner probability function in some logical sense. In order to show this equivalence, we need the following positive language which is the standard language for propositional logic without negation.
      </paragraph>
      <paragraph>
       We start with a fixed infinite set {a mathematical formula}P:={p1,p2,…} of propositional letters. We also use {a mathematical formula}p,q,… to denote propositional letters. The set of formulas φ is built from propositional letters as usual by connectives ∨ and ∧. Equivalently, a formula φ is formed by the following syntax:{a mathematical formula} where p is a propositional letter. We define {a mathematical formula}Φ0 the set of formulas in this syntax. Here we also use ∧ and ∨ as connectives in logic. The context will determine whether they are used as lattice operations or as logical connectives.
      </paragraph>
      <paragraph label="Definition 3.19">
       A probability structure is a tuple {a mathematical formula}M=〈P,L,L′,μ,v〉 where P is a poset, both L and {a mathematical formula}L′ are distributive lattices, {a mathematical formula}L=J(P), {a mathematical formula}L′ is a sublattice of L, μ is a probability measure on {a mathematical formula}L′, and v associates each p with an element in L. v can be easily extended to a homomorphism from {a mathematical formula}Φ0 to L:
       <list>
        {a mathematical formula}v(φ1∧φ2):=v(φ1)∧v(φ2);{a mathematical formula}v(φ1∨φ2):=v(φ1)∨v(φ2).{a mathematical formula}L0
       </list>
       <paragraph>
        is called a basis of M if the elements in {a mathematical formula}L0 are disjoint from each other and {a mathematical formula}L′ consists precisely of all finite unions of elements in {a mathematical formula}L0. For any formula φ, {a mathematical formula}v(φ)∈L. Generally, it is not true that {a mathematical formula}v(φ)∈L′; in other words, {a mathematical formula}v(φ) is not necessarily “measurable”.
       </paragraph>
      </paragraph>
      <paragraph label="Definition 3.20">
       A DS structure is a tuple {a mathematical formula}D=〈P,L,Bel,v〉 where P is a poset, L is a distributive lattice, {a mathematical formula}L=J(P), Bel is a belief function on L and v maps each propositional letter p to an element in L. Similarly, v can be easily extended to a homomorphism from {a mathematical formula}Φ0 to L as in the above definition.
      </paragraph>
      <paragraph>
       We call a probability structure {a mathematical formula}M=〈P,L,L′,μ,v〉 and a DS structure {a mathematical formula}D=〈PD,LD,Bel,vD〉equivalent if{a mathematical formula}
      </paragraph>
      <paragraph label="Theorem 3.21">
       For any probability structure{a mathematical formula}M=〈P,L,L′,μ,v〉, there is an equivalent DS-structure.
      </paragraph>
      <paragraph label="Proof">
       This follows directly from Lemma 3.17.  □
      </paragraph>
      <paragraph>
       Now we prove the converse to this proposition.
      </paragraph>
      <paragraph label="Theorem 3.22">
       For every DS structure{a mathematical formula}D=〈PD,LD,Bel,vD〉, there is an equivalent probability structure{a mathematical formula}M=〈P,L,L′,μ,v〉.
      </paragraph>
      <paragraph>
       Here we simulate the proof in [18] to give a detailed proof, which can also be used to easily show the following corollaries.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}D=〈PD,LD,Bel,vD〉 be a DS-structure and m be the corresponding mass assignment of Bel. According to the definition, {a mathematical formula}LD=J(PD).The probability structure {a mathematical formula}M:=〈P,L,L′,μ,v〉 is defined as follows. Let P be the set {a mathematical formula}{(A,s):s∈A,A∈J(PD)} with the identity relation. Let {a mathematical formula}A⁎={(A,s):s∈A} for any {a mathematical formula}A∈J(P). It is easy to see that, if {a mathematical formula}A≠B, then {a mathematical formula}A⁎∩B⁎=∅. In addition, {a mathematical formula}⋃A∈J(PD)A⁎=P. We take {a mathematical formula}{A⁎:A∈J(PD)} to be the “basis” for the distributive lattice {a mathematical formula}L′ in the sense that {a mathematical formula}L′ is the set of all finite unions of elements {a mathematical formula}A⁎. It is easy to see that {a mathematical formula}L′ with the usual set operations is indeed a distributive lattice and is actually a sublattice of {a mathematical formula}L:=〈2P,∩,∪〉. It is interesting to note that both L and {a mathematical formula}L′ with the set complement are Boolean algebras.Define {a mathematical formula}μ(A⁎)=m(A) for any {a mathematical formula}A∈J(PD). Then we extend μ to all of {a mathematical formula}L′ by additivity. So μ is a probability function on {a mathematical formula}L′. Define a valuation to L as follows: {a mathematical formula}v(p)={(B,s):s∈vD(p)∩B,B∈J(PD)}. We can show by induction on the complexity of φ that, for all formulas {a mathematical formula}φ∈Φ0, {a mathematical formula}v(φ)={(B,s):s∈vD(φ)∩B,B∈J(PD)}.Now we will show that such defined probability structure {a mathematical formula}M=〈P,L,L′,μ,v〉 is equivalent to the belief structure D. For each formula φ and {a mathematical formula}A∈J(PD), we have {a mathematical formula}A⁎⊆v(φ) iff {a mathematical formula}(A,s)∈v(φ) for all {a mathematical formula}s∈A iff {a mathematical formula}s∈vD(φ) for all {a mathematical formula}s∈A iff {a mathematical formula}A⊆vD(φ). So the largest “measurable” set (simply the largest element in {a mathematical formula}L′) contained in {a mathematical formula}v(φ) is {a mathematical formula}⋃A⊆vD(φ)A⁎. It follows that{a mathematical formula} So we have shown that M and D are equivalent.  □
      </paragraph>
      <paragraph label="Corollary 3.23">
       For every DS-structure{a mathematical formula}D=〈PD,LD,Bel,vD〉on a distributive lattice{a mathematical formula}LD, there is an equivalent probability structure{a mathematical formula}M=〈P,L,L′,μ,v〉such that both L and{a mathematical formula}L′are Boolean algebras.
      </paragraph>
      <paragraph label="Proof">
       This follows directly from the above construction of L and {a mathematical formula}L′.  □
      </paragraph>
      <paragraph>
       These equivalence results turn out to be crucial to show the complexity of reasoning about belief functions over some non-Boolean structures (Lemma 5.5 in Section 5). By summarizing the results in the above two theorems, we conclude that belief functions and inner probability functions are equivalent on distributive lattices if we view them both as functions on formulas rather on sets. Just as in [18], there is an immediate payoff to this view of belief functions as inner probability functions: a logic for reasoning about belief functions in Section 5 is obtained from that for inner probability functions [19] with minor modifications. The following proposition is simply a corollary of the above theorem, which is a partial converse to Lemma 3.17. Also it provides an alternative representation of belief functions to the well-known one by Shafer through the composition of probability functions with ∩-homomorphisms in [53].
      </paragraph>
      <paragraph label="Corollary 3.24">
       Given a DS structure{a mathematical formula}〈PD,LD,BelD,vD〉defined on a finite distributive lattice{a mathematical formula}LD(=J(PD)), there is a probability structure{a mathematical formula}〈P,L,L′,μ,v〉and a surjection{a mathematical formula}f:P→PDsuch that, for each{a mathematical formula}x∈LD, we have{a mathematical formula}Bel(x)=μ⁎(f−1(x)).
      </paragraph>
      <paragraph label="Proof">
       Here we choose L and {a mathematical formula}L′ in the proof of Theorem 3.22. A function {a mathematical formula}f:P→PD is defined as: {a mathematical formula}f((A,s))=s for {a mathematical formula}(A,s)∈P such that {a mathematical formula}s∈A and {a mathematical formula}A∈J(PD). f is a surjection from P to {a mathematical formula}PD. Then the argument in the last part of the proof of Theorem 3.22 works here simply by replacing x for {a mathematical formula}vD(φ) and {a mathematical formula}f−1(x) for {a mathematical formula}v(φ).  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Belief functions on non-classical formalisms
     </section-title>
     <paragraph>
      The integration of belief functions and non-classical formalisms is intended to master two sources of ignorance. Non-classical formalisms usually take care of the incompleteness or inconsistency in the knowledge-base due to imperfect data while belief functions take care of the limitation of the information that the agent has at his disposal. In artificial intelligence especially in Knowledge Representation, non-classical formalisms play an important role in handling imperfect information in different forms. Most of these non-classical formalisms assume a mathematical setting of distributive lattices (quantum logic is probably one of the very few important exceptions [67]). Each of these formalisms was intended for reasoning about some specific form of information. For example, Kleeneʼs three valued logic has been used to take into account statements that being undefined makes sense to be a third truth value, which is useful to model the situation in computer science when a computation does not return any result [23]; paraconsistent logics have been used to deal with contradictory knowledge bases [3], [44]; relevance logic is used to deal with the famous logical omniscience problem in the foundation of knowledge representation, and used for reasoning in the presence of inconsistency in knowledge base systems [37], [38], [19].
     </paragraph>
     <paragraph>
      Belief functions in the Dempster–Shafer theory are defined on Boolean algebras [52]. One essential difference of non-classical formalisms from the Boolean setting is their specific treatments of negation. Negation is closely related to the treatment of bipolarity in information [14], which means that there is an intrinsic positive and negative effect in dealing with information. In the classical Dempster–Shafer theory, negation is assumed to be Boolean, i.e., every element has a complement (for any element a, there is an element {a mathematical formula}a′ such that {a mathematical formula}a∨a′ is the top element and {a mathematical formula}a∧a′ is the bottom), which is used to represent complete information. Any distributive lattice with a Boolean negation is a Boolean algebra and any Boolean algebra is represented as a power set with the usual set operations (Example 2.3). It is shown [18] that reasoning about belief functions in this case is the same as that for inner probability measures [19]. In Kleeneʼs three valued logic, there are three truth values: true, false and undetermined. Logically, the treatment of negation considers some formulas to be neither true nor false (undetermined) but forbids any formula to be both true and false. In other words, positive and negative sides donʼt exhaust all possibilities. So this logic is used to represent incompleteness in information. There is an implicit intuitionistic negation in any finite distributive lattice. Since any finite distributive lattice {a mathematical formula}L=J(P) for some poset P is also a Heyting algebra, {a mathematical formula}max{I′∈J(P):I′∩I=∅} exists for any {a mathematical formula}I∈J(P), and is defined to be the negation of I (denoted by ∼I), which is in {a mathematical formula}J(P). The duality relation between belief function and plausibility function in Dempster–Shafer theory can be expressed in the following form: for any {a mathematical formula}I∈L,{a mathematical formula} where Bel is a belief function on L and m is the corresponding mass assignment of Bel. So, the duality relation is essentially intuitionistic. One may also reason about belief functions in this case by replacing the classical proposition logic by intuitionistic propositional logic (see discussion in Section 6). A good example in this direction is bipolar belief pairs on vague propositions as an integrated model combining epistemic uncertainty and indeterminacy [36].
     </paragraph>
     <paragraph>
      Kleeneʼs three-valued logic finds a natural generalization in Belnapʼs four-valued logic [5], which can be naturally extended to distributive bilattices. A distributive bilattice is a distributive lattice with a second ordering which interacts with the original one in a certain way. In addition to their applications in logic programming [23], distributive bilattices are also used to represent the inconsistency in knowledge base systems. In these structures, another form of negation called de Morgan negation is employed. The most important aspect of de Morgan negations is their intrinsic ability to model inconsistency in knowledge base systems. In this paper, we will consider this type of negations and integrate belief functions with de Morgan lattices, which are distributive lattices with de Morgan negations, provide an axiomatization of reasoning about belief functions over this type of non-classical structures and discuss computational complexities of different problems in this setting. More importantly, this approach to reasoning about belief functions on de Morgan lattices also provides a framework to reason about belief functions on other non-classical structures.
     </paragraph>
     <paragraph>
      A well-known slogan in algebraic methods for non-classical logics (Section 18 of [1]) tells us that algebra and logic are dual to each other. Given a non-classical logic {a mathematical formula}L, the Lindenbaum algebra {a mathematical formula}AL of this logic is in the class of algebras which characterize the logic but also the possible-world-like structure derived from the Lindenbaum algebra {a mathematical formula}AL through the Duality theorem for this class of algebras is the canonical structure for this logic. On the other hand, given any possible-world-like structure for the logic {a mathematical formula}L, the interpretations of the formulas is an algebra that characterizes {a mathematical formula}L. So, in the following section, before we reason about belief functions on specific classes of algebras, we elaborate on this kind of duality between logics and their corresponding algebraic structures (and possible-world-like semantics) and wonʼt distinguish belief functions on algebras and for their logics.
     </paragraph>
     <paragraph>
      In addition to this duality, algebra and logic are dual to each other in the sense that (order) ideals to algebra are the same as filters to logic. If we replace in Section 3 all posets {a mathematical formula}〈P,⩽〉 with its dual {a mathematical formula}〈P,⩽∂〉 (where {a mathematical formula}x⩽∂y iff {a mathematical formula}y⩽x) and all ⩽-order-ideals by {a mathematical formula}⩽∂-filters, the dual forms of all propositions there remain valid. So, in order to apply the algebraic propositions in Section 3 to non-classical logics in this section, we have to keep this duality in mind.
     </paragraph>
     <section label="4.1">
      <section-title>
       Reasoning about bilattices
      </section-title>
      <paragraph>
       Bilattices are algebras with two separate lattice structures. Ginsberg [25] suggested using bilattices as the underlying framework for various AI inference systems including those based on default logics, truth maintenance systems, probabilistic logics, and others. These ideas were later pursued in the context of logic programming semantics [22], [21]. Moreover, bilattices and their extensions have been used in the literature to model a variety of reasoning mechanisms about uncertainty in the presence of incomplete or contradictory information [33], [3], [54]. Also they have been employed to represent bipolar information [34]. In the following, we first present a well-known algebraic result about the representation of bilattices. In logic, we employ the Belnapʼs four-valued logic to decouple the interpretation of each formula φ into the set of states where φ is “true” and that of states where it is “false” [15]. In this way, the interpretations of all formulas form a distributive bilattices with two partial orderings: the truth ordering and the knowledge ordering.
      </paragraph>
      <paragraph>
       One may refer to [40], [23] for the technical details about the duality theorem of bilattices which is presented below. Recall that all lattices are assumed to be finite.
      </paragraph>
      <paragraph label="Definition 4.1">
       A bilattice is an algebra {a mathematical formula}B=〈B,∧1,∨1,⊥1,⊤1,∧2,∨2,⊥2,⊤2〉 such that {a mathematical formula}B1=〈B,∧1,∨1,⊥1,⊤1〉 and {a mathematical formula}B2=〈B,∧2,∨2,⊥2,⊤2〉 are lattices. By a negation on B we mean a unary operation ¬ on B satisfying the conditions:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}¬¬x=x;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}¬(x∨1y)=¬x∧1¬y,¬(x∧1y)=¬x∨1¬y;
       </list-item>
       <list-item label="3.">
        {a mathematical formula}¬(x∨2y)=¬x∨2¬y,¬(x∧2y)=¬x∧2¬y.
       </list-item>
      </list>
      <paragraph>
       The lattice ordering corresponding to the lattice {a mathematical formula}B1 will be denoted by {a mathematical formula}⩽1 and the lattice ordering corresponding to {a mathematical formula}B2 by {a mathematical formula}⩽2; often the bilattice B is written in the form {a mathematical formula}〈B,⩽1,⩽2〉. Alternatively, {a mathematical formula}⩽1 and {a mathematical formula}⩽2 are often denoted by {a mathematical formula}⩽t and {a mathematical formula}⩽k, respectively, reflecting the fact that they represent the “truth” and “knowledge” orderings, which will become clear in the following Definition 4.4 and in Remark 4.7.
      </paragraph>
      <paragraph label="Definition 4.2">
       Let {a mathematical formula}L=〈L,∧,∨,⊥,⊤〉 and {a mathematical formula}L′=〈L′,∧′,∨′,⊥′,⊤′〉 be lattices. Define {a mathematical formula}B(L,L′)=〈L×L′,⊓1,⊔1,⊥1,⊤1,⊓2,⊔2,⊥2,⊤2〉 as follows: for all {a mathematical formula}(x,x′),(y,y′)∈L×L′,
       <list>
        {a mathematical formula}(x,x′)⊓1(y,y′)=(x∧y,x′∨′y′),(x,x′)⊔1(y,y′)=(x∨y,x′∧′y′);{a mathematical formula}(x,x′)⊓2(y,y′)=(x∧y,x′∧′y′),(x,x′)⊔2(y,y′)=(x∨y,x′∨′y′);{a mathematical formula}⊥1=(⊥,⊤′),⊤1=(⊤,⊥′),⊥2=(⊥,⊥′),⊤2=(⊤,⊤′).{a mathematical formula}B(L,L′)
       </list>
       <paragraph>
        is called the product bilattice associated with L and {a mathematical formula}L′. If {a mathematical formula}L=L′, we define{a mathematical formula} and call {a mathematical formula}B(L,L) the square bilattice with negation associated with L. Usually in this case we write {a mathematical formula}B(L) for {a mathematical formula}B(L,L).
       </paragraph>
      </paragraph>
      <paragraph>
       Any abstract distributive bilattice with negation can be represented as a square bilattice with negation (Corollary 9 in [40]). Let {a mathematical formula}B=〈B,⩽1,⩽2〉 be a distributive bilattice. An element {a mathematical formula}x∈B is called positive if, for every {a mathematical formula}y∈B, {a mathematical formula}x⩽1y implies {a mathematical formula}x⩽2y. It is called negative if, for every {a mathematical formula}y∈B, {a mathematical formula}y⩽1x implies {a mathematical formula}x⩽2y. Intuitively, an element x is positive (negative) if it should increase in the knowledge ordering whenever it increases (decreases) in the truth order. Denote by {a mathematical formula}POS(B) and {a mathematical formula}NEG(B) the set of positive and negative elements (they are called t-grounded and f-grounded in [25]), respectively, of B. An element {a mathematical formula}x∈B is called positive (resp. negative) {a mathematical formula}⩽2-join-irreducible if it is positive (resp. negative) and join-irreducible with respect to {a mathematical formula}⩽2-ordering. We denote by {a mathematical formula}ℑ2+(B) (resp. {a mathematical formula}ℑ2−(B)) the set of non-bottom positive (resp. negative) {a mathematical formula}⩽2-join-irreducible elements of B. Note that both {a mathematical formula}ℑ2+(B) and {a mathematical formula}ℑ2−(B) are posets with respect to the ordering {a mathematical formula}⩽2. Moreover, {a mathematical formula}ℑ2(B) denotes the set of all {a mathematical formula}⩽2-join-irreducible elements of B. If a bilattice B is distributive and is represented as a square bilattice, then it is easy to recognize those positive and negative elements. Let L be a distributive lattice and let 0 be the least element. An element x of {a mathematical formula}B(L) is positive iff {a mathematical formula}x=(y,0) for some {a mathematical formula}y∈L, and is negative iff {a mathematical formula}x=(0,y) for some {a mathematical formula}y∈L (Corollary 8 in [40]). The positive and negative elements here correspond to the two support relations {a mathematical formula}⊨T and {a mathematical formula}⊨F in the following four-valued models.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}P=〈P,≼〉 and {a mathematical formula}Q=〈Q,⊑〉 be two disjoint partially ordered sets. Define the lift of P, denoted by {a mathematical formula}P⊥ by {a mathematical formula}P⊥=〈P∪{0},⩽〉, where {a mathematical formula}0∉P and {a mathematical formula}x⩽y in {a mathematical formula}P⊥ iff {a mathematical formula}x=0 or {a mathematical formula}x≼y in P. Define the disjoint union{a mathematical formula}P⊎Q=〈P∪Q,⩽〉 to be the partially ordered set with {a mathematical formula}x⩽y iff either {a mathematical formula}x,y∈P and {a mathematical formula}x≼y or {a mathematical formula}x,y∈Q and {a mathematical formula}x⊑y.
      </paragraph>
      <paragraph>
       Given two partially ordered sets P and Q, define the separated sum of P and Q, denoted {a mathematical formula}P⊕⊥Q, to be the poset {a mathematical formula}P⊕⊥Q=(P⊎Q)⊥. The following theorem is the bilattice counterpart of Birkhoffʼs representation theorem.
      </paragraph>
      <paragraph label="Theorem 4.3">
       (See Corollary 23 in[40].) Let B be a distributive bilattice with negation. Then{a mathematical formula}ℑ2(B)≅ℑ2+(B)⊕⊥ℑ2−(B)and{a mathematical formula}ℑ2+(B)≅ℑ2−(B). Conversely, for any finite poset P, there is a finite distributive bilatticeBsuch that{a mathematical formula}ℑ2(B)≅P⊕⊥P. So there is a one-to-one correspondence between finite distributive bilattices and finite posets.
      </paragraph>
      <paragraph>
       Intuitively, the theorem says that any distributive lattice with negation can be represented as a concrete square bilattice. Let {a mathematical formula}J2(ℑ2(B)) denote the set of {a mathematical formula}⩽2-order-ideals in {a mathematical formula}ℑ2(B). It is easy to check that it is the same as the Cartesian product of the set of order ideals in {a mathematical formula}ℑ2+(B) with that in {a mathematical formula}ℑ2−(B). Since {a mathematical formula}ℑ2+(B)≅ℑ2−(B), {a mathematical formula}J2(ℑ2(B))≈J(P)×J(P) for some poset P which is isomorphic to {a mathematical formula}ℑ2+(B). For any two elements {a mathematical formula}(I1,I2),(I1′,I2′)∈J2(ℑ2(B)),
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}(I1,I2)⩽1(I1′,I2′) if {a mathematical formula}I1⊆I2 and {a mathematical formula}I1′⊇I2′;
       </list-item>
       <list-item label="•">
        {a mathematical formula}(I1,I2)⩽2(I1′,I2′) if {a mathematical formula}I1⊆I2 and {a mathematical formula}I1′⊆I2′.
       </list-item>
      </list>
      <paragraph>
       The above representation theorem tells us that B is isomorphic to {a mathematical formula}〈J2(ℑ2(B)),⩽1,⩽2〉. It also connects bilattice theory to the well-known four-valued logic [5].
      </paragraph>
      <paragraph>
       FOUR, the structure that corresponds to Belnapʼs four-valued logic [5], is the minimal bilattice, exactly as the structure {a mathematical formula}2={true,false} or {a mathematical formula}{0,1} that is based on the classical two valued logic is the minimal Boolean algebra. It plays an important role in bilattice-based multi-valued logics. The Hasse diagram of the lattice FOUR is illustrated in Fig. 4.
      </paragraph>
      <paragraph>
       Following Dunn [17], we interpret FOUR in terms of the power set of {a mathematical formula}{0,1}. The meaning of the capital letters attached to the elements of FOUR in the above figure is obvious from this type of interpretation. For example, B informally means “both” and can be translated as both “true” (1) and “false” (0). The truth ordering {a mathematical formula}⩽t can be formalized as follows: for any two elements {a mathematical formula}x,y∈{T,F,N,B},{a mathematical formula}
      </paragraph>
      <paragraph>
       The lattice FOUR is the tuple {a mathematical formula}〈{T,F,N,B},∨,∧,∼〉 where ∧ and ∨ are the lattice operations associated with the above truth ordering. Also we define ∼ as an order inverting that leaves N and B as fixed points, i.e., {a mathematical formula}∼N=N, {a mathematical formula}∼B=B, {a mathematical formula}∼T=F, {a mathematical formula}∼F=T. Then meaning of this negation ∼ will be clear from the following semantical meaning of formulas (See Remark 4.7).
      </paragraph>
      <paragraph>
       It is interesting to note that there is a natural knowledge ordering implicit in the above lattice FOUR. The knowledge ordering {a mathematical formula}⩽k is defined as follows: for any two elements {a mathematical formula}x,y∈{T,F,N,B},{a mathematical formula}
      </paragraph>
      <paragraph>
       So the lattices operations ⊓ and ⊔ associated with {a mathematical formula}⩽k are simply the usual set operations ∩ and ∪. It is easy to check that {a mathematical formula}〈{T,F,N,B},∨,∧,⊓,⊔,∼,〉 is a distributive bilattice. It is actually the smallest distributive bilattice. 2 is simply the sublattice {a mathematical formula}〈{T,F},∧,∨〉 of the reduct {a mathematical formula}〈{T,F,N,B},∧,∨〉.
      </paragraph>
      <paragraph>
       The interpretations of standard propositional formulas in FOUR form exactly a distributive bilattice. Moreover, it was shown in [2] that all the natural bilattice-valued logics that we had introduced for various purposes can be characterized using only the four basic “epistemic truth values”. The meaning of such epistemic truth values highly differs from the meaning of standard Boolean truth values since they are not intrinsic to propositions but are intended to reflect what an agent may have been informed about (regarding these propositions). Thus, interpreting a proposition φ as 0 (resp., 1) does not mean that φ is false (resp., true) but that the agent under consideration has some reasons to consider that φ is false (resp., true) or is told that φ is “false” (resp. “true”). The agent may have some reasons to consider that φ is false and other reasons to consider that φ is true, and the epistemic truth value B reflects this situation. Similarly, the agent may have no reasons to consider φ as true and no reasons to consider it as false; in this situation, φ is given the epistemic truth value N (or ∅). So B reflects a situation of inconsistency and N of ignorance. The epistemic nature in the interpretations into FOUR agrees well with Shaferʼs emphasis of the epistemic nature of the set of possibilities on the frame of discernment in his theory (page 36 in [52]) but under incomplete or inconsistent information.
      </paragraph>
      <paragraph>
       In order to reason about belief functions for the four-valued logic, we expand {a mathematical formula}Φ0 in the last section to Φ by adding the connective negation ∼. In other words, a formula in Φ is formed by the following syntax:{a mathematical formula} where p is a propositional letter.
      </paragraph>
      <paragraph>
       A valuation v into the lattice FOUR is a function from the set P of propositional letters into FOUR. It is easy to see that v can be extended to the set of formulas naturally as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}v(∼φ)=∼v(φ);
       </list-item>
       <list-item label="•">
        {a mathematical formula}v(φ∧ψ)=v(φ)∧v(ψ);
       </list-item>
       <list-item label="•">
        {a mathematical formula}v(φ∨ψ)=v(φ)∨v(ψ).
       </list-item>
      </list>
      <paragraph>
       Following Belnap [5], we simply say “φ is at least true” if {a mathematical formula}1∈v(φ); “φ is at least false” if {a mathematical formula}0∈v(φ). It follows immediately that
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}1∈v(φ) iff {a mathematical formula}0∈v(∼φ), {a mathematical formula}0∈v(φ) iff {a mathematical formula}1∈v(∼φ);
       </list-item>
       <list-item label="•">
        {a mathematical formula}1∈v(φ∨ψ) iff {a mathematical formula}1∈v(φ) or {a mathematical formula}1∈v(ψ), {a mathematical formula}0∈v(φ∨ψ) iff {a mathematical formula}0∈v(φ) and {a mathematical formula}0∈v(ψ);
       </list-item>
       <list-item label="•">
        {a mathematical formula}1∈v(φ∧ψ) iff {a mathematical formula}1∈v(φ) and {a mathematical formula}1∈v(ψ), {a mathematical formula}0∈v(φ∧ψ) iff {a mathematical formula}0∈v(φ) or {a mathematical formula}0∈v(ψ).
       </list-item>
      </list>
      <paragraph>
       In order to reason about belief functions on distributive bilattices, we simulate Kripkeʼs semantics for intuitionistic logic [35] and choose to define belief structures in a more abstract form.
      </paragraph>
      <paragraph label="Definition 4.4">
       A Belnap structure is a tuple {a mathematical formula}S=〈S,⩽,v〉 where
       <list>
        {a mathematical formula}〈S,⩽〉 is a poset where S is a non-empty set of states called situations [37] or set-ups [16], which are like possible worlds{sup:3} except that they are not required to be either consistent or complete;for each {a mathematical formula}s∈S, {a mathematical formula}v(s) is a valuation into FOUR on the set of propositional letters such that the following persistency condition is satisfied: for any {a mathematical formula}s1,s2∈S and propositional letter p,{a mathematical formula}It is a
       </list>
       <paragraph>
        Boolean structure if ⩽ is the identity relation and v is a valuation into 2.
       </paragraph>
      </paragraph>
      <paragraph>
       Two support relations between states and formulas [15], [37] are defined inductively as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}S,s⊨Tp if {a mathematical formula}1∈v(s)(p),{a mathematical formula}S,s⊨Fp if {a mathematical formula}0∈v(s)(p);
       </list-item>
       <list-item label="•">
        {a mathematical formula}S,s⊨Tφ1∧φ2 if {a mathematical formula}S,s⊨Tφ1 and {a mathematical formula}S,s⊨Tφ2;{a mathematical formula}S,s⊨Fφ1∧φ2 if {a mathematical formula}S,s⊨Fφ1 or {a mathematical formula}S,s⊨Fφ2;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S,s⊨Tφ1∨φ2 if {a mathematical formula}S,s⊨Tφ1 or {a mathematical formula}S,s⊨Tφ2;{a mathematical formula}S,s⊨Fφ1∨φ2 if {a mathematical formula}S,s⊨Fφ1 and {a mathematical formula}S,s⊨Fφ2;
       </list-item>
       <list-item label="•">
        {a mathematical formula}S,s⊨T∼φ if {a mathematical formula}S,s⊨Fφ;{a mathematical formula}S,s⊨F∼φ if {a mathematical formula}S,s⊨Tφ.
       </list-item>
      </list>
      <paragraph>
       Note that, for any {a mathematical formula}s∈S and any formula φ, {a mathematical formula}1∈v(s)(φ) iff {a mathematical formula}S,s⊨Tφ and {a mathematical formula}0∈v(s)(φ) iff {a mathematical formula}S,s⊨Fφ. Actually the persistency condition for the valuation is satisfied by all formulas, as shown by the following lemma.
      </paragraph>
      <paragraph label="Lemma 4.5">
       Let{a mathematical formula}〈S,⩽,v〉be a Belnap structure. If{a mathematical formula}s1,s2∈Sand{a mathematical formula}s1⩽s2, then, for any formula{a mathematical formula}φ∈Φ,
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}S,s1⊨Tφimplies{a mathematical formula}S,s2⊨Tφ;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}S,s1⊨Fφimplies{a mathematical formula}S,s2⊨Fφ.
       </list-item>
      </list>
      <paragraph label="Proof">
       Let {a mathematical formula}〈S,⩽,v〉 be a Belnap structure and {a mathematical formula}s1,s2∈S and {a mathematical formula}s1⩽s2. We prove by induction on the complexity of φ. Here we only prove the case that {a mathematical formula}φ=∼φ′. The proof of the other cases is straightforward.We reason as follows:{a mathematical formula}{a mathematical formula} and{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph label="Remark 4.6">
       The persistency condition in a Belnap structure is quite similar to that in the Kripke semantics for intuitionistic logic [35], [64]. Following the interpretation of the non-standard propositional logic in [20], we analyze the above semantics in terms of knowledge-bases. Each state s can be seen as a pair of knowledge bases. The set of formulas that are at least true at s is the knowledge base of true facts and the set of formulas which are at least false at s constitutes the knowledge base for the false facts. This pair of knowledge evolves in the course of time. Both the knowledge base of true facts and that of false facts expand at every later stage. They are considered to be independent of each other and both take the open-world assumption, which also explains the incompleteness in the information in another way. So the essential difference of our interpretation from that in intuitionistic logic is that the persistency condition here considers not only the knowledge of true facts but also that of false facts.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}[[φ]]T denote the set of all states where φ is “told true” {a mathematical formula}{s∈S:S,s⊨Tφ} and {a mathematical formula}[[φ]]F={s∈S:S,s⊨Fφ} for all formulas φ. It is easy to check that both of them are filters in {a mathematical formula}(S,⩽). Denote{a mathematical formula}
      </paragraph>
      <paragraph>
       We can define two partial orders on B.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}([[φ1]]T,[[φ1]]F)⩽1([[φ2]]T,[[φ2]]F) if {a mathematical formula}[[φ1]]T⊆[[φ2]]T and {a mathematical formula}[[φ1]]F⊇[[φ2]]F;
       </list-item>
       <list-item label="•">
        {a mathematical formula}([[φ1]]T,[[φ1]]F)⩽2([[φ2]]T,[[φ2]]F) if {a mathematical formula}[[φ1]]T⊆[[φ2]]T and {a mathematical formula}[[φ1]]F⊆[[φ2]]F.
       </list-item>
      </list>
      <paragraph label="Remark 4.7">
       The four valued logic is employed to decouple the bipolar information in the semantics. And the interpretation of each formula φ is decomposed into two parts: the part for the epistemic truth and the other part for the epistemic falsity. For the partial ordering {a mathematical formula}⩽1, the agent has more reasons to consider {a mathematical formula}φ2 as true than {a mathematical formula}φ1 and more reasons to consider {a mathematical formula}φ1 as false than {a mathematical formula}φ2. In other words, {a mathematical formula}φ2 is considered at least as true as and at most as false as {a mathematical formula}φ1. The agent is more confident in considering that overall{a mathematical formula}φ2 is at least as true as {a mathematical formula}φ1. This is the reason why {a mathematical formula}⩽1 is also called the truth ordering. For the other ordering {a mathematical formula}⩽2, the agent has both more reasons to consider {a mathematical formula}φ2 as true than {a mathematical formula}φ1 and more reasons to consider {a mathematical formula}φ2 as false than {a mathematical formula}φ1. So the agent is more informative (in reasons) about {a mathematical formula}φ2 than about {a mathematical formula}φ1. This is the reason why {a mathematical formula}⩽2 is called the information or knowledge ordering.
      </paragraph>
      <paragraph>
       It is easy to check that the associated structure {a mathematical formula}B:=〈B,⩽1,⩽2〉 is a distributive bilattice with the following negation:{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively, for each formula φ, {a mathematical formula}[[φ]]T and {a mathematical formula}[[φ]]F are the positive and negative sides of the interpretation of this formula and they correspond to positive and negative elements in the bilattice {a mathematical formula}B, respectively.
      </paragraph>
      <paragraph label="Definition 4.8">
       A formula ψ is a logical consequence of a formula φ (φ logically implies ψ) with respect to the class {a mathematical formula}B of Belnap structures (denoted {a mathematical formula}φ⊨Bψ) if, for any Belnap structure {a mathematical formula}S=〈S,⩽,v〉 and any {a mathematical formula}s∈S, {a mathematical formula}S,s⊨Tφ implies {a mathematical formula}S,s⊨Tψ and {a mathematical formula}S,s⊨Fψ implies {a mathematical formula}S,s⊨Fφ.
      </paragraph>
      <paragraph>
       Now we investigate deductive system for this logical implication {a mathematical formula}⊨B with respect to the class of Belnap structures. The following is the deductive system {a mathematical formula}Rfde which is the well-known first-degree entailment fragment of the relevance logic R[1], [16]. Without further notice, ⊢ denotes ⊢ and {a mathematical formula}φ⊣⊢ψ is short for both {a mathematical formula}φ⊢ψ and {a mathematical formula}ψ⊢φ.
      </paragraph>
      <paragraph>
       Axioms:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Rules:
      </paragraph>
      <list>
       <list-item label="•">
        From {a mathematical formula}φ⊢ψ and {a mathematical formula}ψ⊢γ, infer {a mathematical formula}φ⊢γ (Transitivity)
       </list-item>
       <list-item label="•">
        From {a mathematical formula}φ⊢ψ and {a mathematical formula}φ⊢γ, infer {a mathematical formula}φ⊢ψ∧γ (∧-introduction)
       </list-item>
       <list-item label="•">
        From {a mathematical formula}φ⊢γ and {a mathematical formula}ψ⊢γ, infer {a mathematical formula}φ∨ψ⊢γ (∨-elimination)
       </list-item>
       <list-item label="•">
        From {a mathematical formula}φ⊢ψ, infer {a mathematical formula}∼ψ⊢∼φ (Contraposition)
       </list-item>
      </list>
      <paragraph>
       Actually the logical implication relation in the class of Belnap structures coincides with the above consequence relation ⊢.
      </paragraph>
      <paragraph label="Theorem 4.9">
       (See Theorem 7 in[17].) For any two formulas φ and ψ in Φ,{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 4.10">
       A Dempster–Shafer structure B (DS-structure for short) on a Belnap structure is a tuple {a mathematical formula}〈S,⩽,v,Bel〉 where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}S=〈S,⩽,v〉 is a Belnap structure;
       </list-item>
       <list-item label="•">
        Bel is a belief function on {a mathematical formula}〈F(S)×F(S),⩽t〉=〈{(I,I′):I and {a mathematical formula}I′ are filters in {a mathematical formula}S},⩽t〉.
       </list-item>
      </list>
      <paragraph>
       Note that, for any {a mathematical formula}(I1,I2),(I1′,I2′)∈F(S)×F(S), if {a mathematical formula}(I1,I2)⩽t(I1′,I2′), i.e., {a mathematical formula}I1⊆I1′ and {a mathematical formula}I2⊇I2′, then {a mathematical formula}Bel(I1,I2)⩽Bel(I1′,I2′). For the Belnap structure {a mathematical formula}〈S,⩽,v〉, {a mathematical formula}([[φ]]TS,[[φ]]FS) denotes the pair of the set of states where φ is satisfied, i.e., {a mathematical formula}[[φ]]TS={s∈S:S,s⊨Tφ}, which can be shown to be a filter in S, and that of states where φ is falsified, i.e., {a mathematical formula}[[φ]]FS={s∈S:S,s⊨Fφ}, which can be shown to be also a filter in S. So the belief in the formula φ is defined to be {a mathematical formula}Bel([[φ]]TS,[[φ]]FS). It is easy to see that the above definition agrees with Definition 3.20.
      </paragraph>
      <paragraph label="Definition 4.11">
       For any two formulas φ and ψ in Φ, φ probabilistically entails ψ with respect to the class of Belnap structures (denoted as {a mathematical formula}φ⊨DSBψ) if, for any DS-structure {a mathematical formula}S=〈S,⩽,Bel,v〉 where {a mathematical formula}〈S,⩽,v〉 is a Belnap structure, {a mathematical formula}Bel([[φ]]TS,[[φ]]FS)⩽Bel([[ψ]]TS,[[ψ]]FS).
      </paragraph>
      <paragraph>
       The following theorem tells us that the deductive system {a mathematical formula}Rfde provides a sound and complete system for both logical implication but also probabilistic entailment.
      </paragraph>
      <paragraph label="Theorem 4.12">
       For any formulas φ and ψ in Φ,{a mathematical formula}φ⊢ψif and only if{a mathematical formula}φ⊨DSBψ.
      </paragraph>
      <paragraph label="Proof">
       The left-to-right direction is straightforward. Now we show the other direction by contraposition. Assume that {a mathematical formula}φ⊬ψ. According to Theorem 4.9, {a mathematical formula}φ⊭Bψ. It follows that there is a Belnap model {a mathematical formula}B=〈S,⩽,v〉 such that either {a mathematical formula}[[φ]]TB⊈[[ψ]]TB or {a mathematical formula}[[ψ]]FB⊈[[φ]]FB. In other words, {a mathematical formula}([[φ]]TB,[[φ]]FB)≰Φ1([[ψ]]TB,[[φ]]FB). It is easy to find a belief function Bel on B such that {a mathematical formula}Bel([[φ]]TB,[[φ]]FB)≰Bel([[ψ]]TB,[[φ]]FB). This implies that {a mathematical formula}φ⊭DSBψ.  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Reasoning about de Morgan lattices
      </section-title>
      <paragraph>
       De Morgan lattices are important for the study of the mathematical aspects of fuzzy logic [69]. The standard fuzzy algebra {a mathematical formula}F=〈[0,1],max(x,y),min(x,y),0,1,1−x〉 is an example of a de Morgan lattice. Moreover, de Morgan lattices are the algebraic semantics for relevance logic [16]. In this part, we investigate belief functions on de Morgan lattices which covers those for fuzzy events [68], [55], [66]. It is interesting to note that the first degree entailments {a mathematical formula}Rfde also provides a calculus for reasoning about de Morgan lattices. In the following, we will give a presentation of the semantics in terms of de Morgan lattices which is in parallel to that for bilattices. For simplicity, we will not repeat those motivations which are similar to those in last part about bilattices but simply present the main ideas. Note that the {a mathematical formula}∧1-{a mathematical formula}∨1-¬-reduct of a distributive bilattice {a mathematical formula}B=〈B,∧1,∨1,∧1′,∨2′,¬〉 is a de Morgan lattice.
      </paragraph>
      <paragraph>
       We need the following duality theorem for finite de Morgan lattices which is based on [7], [16], [62], [45]:
      </paragraph>
      <paragraph label="Theorem 4.13">
       Any finite de Morgan lattice D can be represented as the lattice{a mathematical formula}J(PD)of order ideals in the subposet{a mathematical formula}PDof join-irreducibles with an order-reversing involution g. And there is a one-to-one correspondence between de Morgan lattices and posets with order-reversing involutions.
      </paragraph>
      <paragraph>
       So each de Morgan lattice can be regarded as a poset with an order-reversing involution. Similarly, in order to reason about belief functions on de Morgan lattices, we choose to define underlying structures in a more abstract form.
      </paragraph>
      <paragraph label="Definition 4.14">
       A Routley structure is a tuple {a mathematical formula}S=〈S,⩽,g,v〉 where
       <list>
        {a mathematical formula}〈S,⩽,g〉 is a poset with an order-reversing involution g;For each {a mathematical formula}s∈S,v(s) is a valuation into {a mathematical formula}2={true,false} on the set of propositional letters satisfying the following persistency condition: for any {a mathematical formula}s1,s2∈S and propositional letter p,{a mathematical formula}It is a Boolean structure if ⩽ is the identity relation and
       </list>
       <paragraph>
        g is the identity function on S.
       </paragraph>
      </paragraph>
      <paragraph>
       From the persistency condition, we may immediately derive a “reverse” persistency condition as follows: for any {a mathematical formula}s1,s2∈S and propositional letter p,{a mathematical formula}
      </paragraph>
      <paragraph>
       A satisfaction relation between states and formulas can be defined exactly as in standard propositional logic except the following clause for negation{a mathematical formula} Actually the persistency condition for the valuation is satisfied by all formulas, as shown in the following proposition.
      </paragraph>
      <paragraph label="Lemma 4.15">
       Let{a mathematical formula}〈S,⩽,g,v〉be a Routley structure. If{a mathematical formula}s1,s2∈Sand{a mathematical formula}s1⩽s2, then, for any formula φ,
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}S,s1⊨φimplies{a mathematical formula}S,s2⊨φ;
       </list-item>
       <list-item label="2.">
        {a mathematical formula}S,g(s2)⊨φimplies{a mathematical formula}S,g(s1)⊨φ.
       </list-item>
      </list>
      <paragraph label="Remark 4.16">
       The persistency condition in a Routley structure is quite similar to that in the Kripke semantics for intuitionistic logic [64]. Each pair {a mathematical formula}(s,g(s)) of a state s and its adjunct can be seen as a pair of knowledge bases. s is the knowledge base consisting of true facts and {a mathematical formula}g(s) is the knowledge base for the false facts. Here we take the closed-world assumption[46] for {a mathematical formula}g(s) in the sense that, if a proposition is not implied in {a mathematical formula}g(s), then the negation of this proposition is implied at s. This pair of knowledge evolves in the course of time. The knowledge base of true facts expands at every later stage while the knowledge base for false facts decreases. So the essential difference from those in Belnap structures is that the knowledge of true facts and that for false facts are rather dual to each other than independent of each other as in Belnap structures.If the second (reverse) persistency condition is replaced by a new adjunct but independent valuation {a mathematical formula}v⁎ which is defined as {a mathematical formula}v⁎(s)=v(g(s)), then we may also define a Routley structure as a poset {a mathematical formula}〈S,⩽g〉 with an order-reversing involution g and two “independent” but adjunct-to-each-other valuations v and {a mathematical formula}v⁎ satisfying the following two persistency conditions:
       <list>
        if {a mathematical formula}s1⩽s2, {a mathematical formula}v(s1)(p)=true implies {a mathematical formula}v(s2)(p)=true for all propositional letters p;if {a mathematical formula}s1⩽s2, {a mathematical formula}v⁎(s2)(p)=true implies {a mathematical formula}v⁎(s1)(p)=true for all propositional letters p.The new valuation
       </list>
       <paragraph>
        {a mathematical formula}v⁎ is for false facts. So the semantics with this new type of Routley structures is the same as the above except that for the negated formulas:{a mathematical formula}The adjunct valuation is used to decouple the semantics to interpret negation. Since there is a straightforward interpretation between this semantics and the above one, they are equivalent. So each possibility in the epistemic frame for belief functions on Routley structures (Definition 4.19) consists of a pair of valuations. It would be interesting to compare this pair with the two support relations {a mathematical formula}⊨T and {a mathematical formula}⊨F in the valuation for the four-valued logic. Note that, although Routley semantics and Belnap semantics are different, the notion of satisfiability in the two semantics are equivalent (Proposition 9.1 in [20]).
       </paragraph>
      </paragraph>
      <paragraph>
       The connection (duality) between Routley structures and de Morgan lattices can be analyzed as follows. Define an equivalence relation ≍ on Φ,{a mathematical formula} Let {a mathematical formula}Φ/≍ denote the set of ≍-equivalence classes {a mathematical formula}[φ]≍. Now we define the operations on this set as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}[φ1]≍∧≍[φ2]≍=[φ1∧φ2]≍;
       </list-item>
       <list-item label="•">
        {a mathematical formula}[φ1]≍∨≍[φ2]≍=[φ1∨φ2]≍;
       </list-item>
       <list-item label="•">
        {a mathematical formula}∼≍[φ]≍=[∼φ]≍.
       </list-item>
      </list>
      <paragraph>
       It is easy to check that these operations are well-defined. Such a defined algebra {a mathematical formula}〈Φ/≍,∧≍, {a mathematical formula}∨≍,∼≍〉 is the Lindenbaum algebra on {a mathematical formula}Φ/≍ and is actually a de Morgan lattice.
      </paragraph>
      <paragraph>
       With respect to Φ, we define the canonical Routley structure as follows.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}SΦ is the set of all prime filters in {a mathematical formula}Φ/≍;
       </list-item>
       <list-item label="•">
        {a mathematical formula}gΦ:SΦ→SΦ is defined: for each {a mathematical formula}F∈SΦ, {a mathematical formula}gΦ(F)=Φ/≍∖∼≍F where {a mathematical formula}∼≍F={∼≍[φ]≍:[φ]≍∈F}, which is a prime filer;
       </list-item>
       <list-item label="•">
        {a mathematical formula}vΦ(F)(p)=true if {a mathematical formula}[p]≍∈F for any {a mathematical formula}F∈SΦ.
       </list-item>
      </list>
      <paragraph>
       It is easy to check that {a mathematical formula}〈SΦ,⩽Φ,gΦ〉 is a poset with the order-reversing involution {a mathematical formula}gΦ where {a mathematical formula}⩽Φ is the subset relation. If Φ is finite, according to the dual form of the representation theorem for finite de Morgan lattices, the Lindenbaum algebra {a mathematical formula}〈Φ/≍,∧≍,∨≍,∼≍〉 is isomorphic to the concrete lattice of filters in the poset {a mathematical formula}〈SΦ,⩽Φ,gΦ〉 which underlies the canonical Routley structure.
      </paragraph>
      <paragraph label="Definition 4.17">
       A formula φ logically implies a formula ψ with respect to the class of Routley structures (denoted as {a mathematical formula}φ⊨Rψ) if, for any Routley structure {a mathematical formula}S=〈S,g,v〉, {a mathematical formula}S,s⊨φ implies {a mathematical formula}S,s⊨ψ.
      </paragraph>
      <paragraph>
       The difference of this definition from that for Belnap structures (Definition 4.8) is that we donʼt need to consider the “negative side”. Actually the logical implication relation in the class of Routley structures coincides with the above consequence relation {a mathematical formula}⊢Rfde.
      </paragraph>
      <paragraph label="Theorem 4.18">
       (See Theorem 7 in[17].) For any two formulas φ and ψ in Φ,{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 4.19">
       A Dempster–Shafer structure B (DS-structure for short) on a de Morgan lattice is a tuple {a mathematical formula}〈S,⩽,g,v,Bel〉 where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}S=〈S,⩽,g,v〉 is a Routley structure;
       </list-item>
       <list-item label="•">
        Bel is a belief function on {a mathematical formula}F(S)={I⊆S:Iis a filter inS}.
       </list-item>
      </list>
      <paragraph>
       For the Routley structure {a mathematical formula}〈S,⩽,g,v〉, {a mathematical formula}[[φ]]S denotes the set of states where φ is satisfied, i.e., {a mathematical formula}[[φ]]S={s∈S:S,s⊨φ}, which can be shown to be a filter in S. So the belief in the formula φ is defined to be {a mathematical formula}Bel([[φ]]S). Compared with belief functions on bilattices, belief functions on de Morgan lattices are much simpler in the following sense. In a Belnap structure B, {a mathematical formula}[[φ]]TB⊆[[ψ]]TB does not necessarily imply that {a mathematical formula}[[φ]]FB⊇[[ψ]]FB; in other words, the fact the agent have more reasons to consider ψ as true than φ does not imply that the agent have more reasons to consider φ false than ψ. However, this is not the case in a Routley structure. So, in the definition of belief functions for de Morgan lattices, we donʼt need to consider the second parameter of the set of facts that falsify the proposition. Our definition here agrees with the definition of DS-structures in Definition 3.20.
      </paragraph>
      <paragraph label="Definition 4.20">
       For any two formulas φ and ψ in Φ, φ probabilistically entails ψ with respect to the class of de Morgan lattices (denoted as {a mathematical formula}φ⊨DSRψ) if, for any DS-structure {a mathematical formula}S=〈S,⩽,g,v,Bel〉, {a mathematical formula}Bel([[φ]]S)⩽Bel([[ψ]]S).
      </paragraph>
      <paragraph>
       The following theorem tells us that the deductive system {a mathematical formula}Rfde provides a sound and complete system for both logical implication but also probabilistic entailment with respect to both the class of Belnap structures and that of Routley structures.
      </paragraph>
      <paragraph label="Theorem 4.21">
       For any formulas φ and ψ in Φ,{a mathematical formula}φ⊢ψif and only if{a mathematical formula}φ⊨DSRψ.
      </paragraph>
      <paragraph label="Proof">
       The proof is similar to that for Theorem 4.12.  □
      </paragraph>
      <paragraph>
       The following theorem tells us that the logical implication problem with respect to the class of Routley-structures (Belnap structures) is as hard as logical implication in standard propositional logic.
      </paragraph>
      <paragraph label="Theorem 4.22">
       The complexity of deciding logical implication with respect to the class of Routley structures (Belnap structures) is co-NP-complete.
      </paragraph>
      <paragraph label="Proof">
       The proof can be easily adapted from that of the similar problem in Section 8 in [20] (also [63], [37]).  □
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Reasoning about belief functions for first-degree entailments
     </section-title>
     <paragraph>
      In this section, we provide a sound and complete deductive system for reasoning about belief functions for first degree entailments and show that the satisfiability problem of a belief formula with respect to the corresponding class of Dempster–Shafer structures is NP-complete.
     </paragraph>
     <paragraph>
      In this part, we adapt the deductive machineries in [19], [18] to provide a sound and complete axiomatization for reasoning about belief functions over Routley structures (Belnap structures).
     </paragraph>
     <paragraph label="Definition 5.1">
      For the above given set Φ of formulas, a term is an expression of the form {a mathematical formula}a1bel(φ1)+a2bel(φ2)+⋯+akbel(φk), where {a mathematical formula}a1,a2,…,ak are integers, bel is the belief function symbol and {a mathematical formula}φ1,φ2,…,φk are formulas in Φ. A basic belief formula is one of the form {a mathematical formula}t⩾b, where t is a term and b is an integer. A belief formula is a Boolean combination of basic belief formulas. We can always allow rational numbers in our formulas as abbreviations for the formula that would be obtained by clearing the dominator. And other derived relations {a mathematical formula}=,⩽,&lt;and&gt; can be defined as usual.
     </paragraph>
     <paragraph label="Definition 5.2">
      Given a DS-structure {a mathematical formula}B=〈S,⩽,g,v,Bel〉 on a Routley structure {a mathematical formula}S:=〈S,⩽,g,v〉 and a basic belief formula {a mathematical formula}f:=a1bel(φ1)+a2bel(φ2)+⋯+akbel(φk)⩾b, B satisfies f (denoted as {a mathematical formula}B⊨f) if{a mathematical formula}We then extend the above ⊨ in the obvious way to all belief formulas. Let {a mathematical formula}B be a class of Dempster–Shafer structures. A belief formula {a mathematical formula}f′ is satisfiable with respect to{a mathematical formula}B if it is satisfied in some {a mathematical formula}B∈B. It is valid with respect to{a mathematical formula}B if {a mathematical formula}B⊨f for all {a mathematical formula}B∈B.
     </paragraph>
     <paragraph label="Definition 5.3">
      Given a basic belief formula {a mathematical formula}f:=a1bel(φ1)+a2bel(φ2)+⋯+akbel(φk)⩾b and a probability structure {a mathematical formula}M=〈S,L,L′,v,μ〉 on a Routley structure {a mathematical formula}S:=〈S,⩽,g,v〉 where {a mathematical formula}L=J(S), {a mathematical formula}L′ is a sublattice of L and μ is a probability function on {a mathematical formula}L′, M satisfies f (denoted as {a mathematical formula}M⊨f) if{a mathematical formula}We then extend the above ⊨ in the obvious way to all belief formulas. Let {a mathematical formula}M be a class of probability structures. A belief formula {a mathematical formula}f′ is satisfiable with respect to{a mathematical formula}M if it is satisfied in some {a mathematical formula}M∈M. It is valid with respect to{a mathematical formula}M if {a mathematical formula}M⊨f for all {a mathematical formula}M∈M.
     </paragraph>
     <paragraph>
      The axiomatization {a mathematical formula}Bfde of reasoning about belief functions for first degree entailments consists of three parts: the first-degree entailments, reasoning about linear inequalities and reasoning about belief functions.
     </paragraph>
     <list>
      <list-item label="1.">
       First-degree entailments
      </list-item>
      <list-item label="2.">
       Reasoning about linear inequalities
      </list-item>
      <list-item label="3.">
       Reasoning about belief functions
      </list-item>
     </list>
     <paragraph>
      Note that the principle 3. (e) is the connection of reasoning about belief functions to first degree entailments.
     </paragraph>
     <paragraph label="Theorem 5.4">
      {a mathematical formula}Bfdeis a sound and complete axiomatization of belief formulas with respect to the class of DS-structures.
     </paragraph>
     <paragraph label="Proof">
      The soundness is trivial except the principle 3(e), which follows from Theorem 4.21 (and Theorem 4.12). Here we mainly focus on the completeness proof. The completeness proof is similar to that of the system AX with respect to the class of general probability structures in [19] except that we need to replace propositional reasoning with reasoning about first degree entailments.Fix a belief formula f. Without loss of generality, we may assume that f is a conjunction of basic belief formulas and negated basic belief formulas.{sup:4} Let {a mathematical formula}Pf={p1,…,pk} be the set of all the propositional letters occurring in f and {a mathematical formula}ΦPf be the set of formulas in Φ with propositional letters occurring in {a mathematical formula}Pf. Recall that two formulas are ≍-equivalent iff they are deductively equivalent in {a mathematical formula}Rfde. As in the duality between de Morgan lattices and Routley structures, we define the Lindenbaum algebra {a mathematical formula}〈ΦPf/≍,∧≍,∨≍,∼≍〉 as follows:
      <list>
       {a mathematical formula}ΦPf/≍ is the set of all ≍-equivalence classes {a mathematical formula}[φ]≍ for all {a mathematical formula}φ∈ΦPf, which can be easily shown to be finite;for any two formulas {a mathematical formula}φ,ψ whose propositional letters are in {a mathematical formula}PfIn other words,
      </list>
      <paragraph label="Claim 7">
       {a mathematical formula}ΦPf/≍ is isomorphic to {a mathematical formula}J(SΦPf). Let h denote this isomorphic function. In the following, we wonʼt distinguish between a formula and its equivalence class. Enumerate all formulas {a mathematical formula}φ∈ΦPf:{a mathematical formula}Let {a mathematical formula}x0,x1,…,xm be the variables that correspond to these formulas. Now we turn f into a group of linear inequalities. For each conjunct of f, say, {a mathematical formula}a1bel(φ1)+⋯+akbel(φk)⩾b, we replace each {a mathematical formula}bel(φi) by the variable, say, {a mathematical formula}xi that corresponds to {a mathematical formula}φi and get{a mathematical formula}By collecting all these inequalities, we obtain a group {a mathematical formula}fˆ of linear inequalities that captures the linear relations of beliefs on different formulas in f. For each formula {a mathematical formula}φi∈ΦPf, we have a new inequality:{a mathematical formula} where {a mathematical formula}h(φj),h(φi) are order ideals in {a mathematical formula}SPf and {a mathematical formula}[h(φj),h(φi)] is an interval in {a mathematical formula}J(SPf). Intuitively, it says that the mass assignment at each formula {a mathematical formula}φi is nonnegative. The principle guiding the construction is Theorem 3.2. Let {a mathematical formula}ΦPfˆ denote the set of all linear inequalities of this kind.If f is satisfiable, then{a mathematical formula}ΦPfˆhas a solution.Assume that f is satisfied in a DS-structure {a mathematical formula}S=〈S,⩽,g,v,Bel〉. Let m be the corresponding mass assignment. Since each term on the left side of the inequality 10 is actually the mass assignment {a mathematical formula}m([[φi]]S), it is nonnegative according to Theorem 3.3. So {a mathematical formula}xi=Bel([[φi]]S)(0⩽i⩽m) is a solution of {a mathematical formula}ΦPfˆ and hence we have proved the claim.f is satisfiable if and only if the following group of inequalities has a solution:{a mathematical formula}From the above claim, the left-to-right direction follows immediately. Assume that {a mathematical formula}f˜ has a solution. Now we define {a mathematical formula}Bel(φi)=xi(0⩽i⩽m). From the constraints in {a mathematical formula}f˜ and Theorem 3.2, it follows that Bel is a belief function on the canonical Routley structure. Moreover, the constraints in {a mathematical formula}fˆ guarantees that f is satisfied in this canonical structure.Now we are back to show the theorem. Assume that f is unsatisfiable. It follows from the above claim that {a mathematical formula}f˜ does not have a solution. Since {a mathematical formula}AXIq is a complete axiomatization for reasoning about linear inequalities, {a mathematical formula}f˜ is inconsistent in {a mathematical formula}AXIq. Since {a mathematical formula}ΦPfˆ∪{x0=0,xm=1} correspond to Axioms 3(b)(c)(d) in {a mathematical formula}Bfde, {a mathematical formula}fˆ is not consistent in {a mathematical formula}Bfde. This is equivalent to say that f is not consistent in {a mathematical formula}Bfde. So we have finished the whole proof of the theorem.  □
      </paragraph>
     </paragraph>
     <paragraph>
      Let {a mathematical formula}|f| denote the length of the belief formula f which is the number of symbols required to write f, where we count the length of each coefficient as 1 and {a mathematical formula}‖f‖ be the length of the longest coefficient appearing in f, when written in binary.
     </paragraph>
     <paragraph label="Lemma 5.5">
      Let f be a belief formula that is satisfied in some DS-structure on a Routley structure (a Belnap structure). Then f is satisfied in a probability structure on a Boolean algebra with at most{a mathematical formula}|f|2states, with a basis of size at most{a mathematical formula}|f|, where the probability assigned to each member of the basis is a rational number with size{a mathematical formula}O(|f|‖f‖+|f|log(|f|)).
     </paragraph>
     <paragraph label="Proof">
      From the results in Theorem 3.22 (particular from Corollary 3.23), we know that each DS-structure on a distributive lattice is equivalent to a probability structure on a Boolean algebra. Actually the whole argument there works to show that each DS structure {a mathematical formula}B:=〈S,⩽,g,v,Bel〉 on a de Morgan lattice {a mathematical formula}J(S) (or on a Routley structure {a mathematical formula}〈S,⩽,g,v〉) is equivalent to a probability structure {a mathematical formula}M:=〈S′,L,L′,v′,μ′〉 where {a mathematical formula}L=2S′, {a mathematical formula}L′ is a Boolean algebra and {a mathematical formula}μ′ is a probability function on {a mathematical formula}L′ in the sense that, for any formula {a mathematical formula}φ∈Φ,{a mathematical formula}Note that, compared to Theorems 3.22 (and Corollary 3.23), our equivalence here is stronger because the language Φ here includes the negation ∼ while {a mathematical formula}Φ0 in Theorems 3.22 (and Corollary 3.23) does not. Then the lemma follows immediately from Theorem 3.10 in [19].  □
     </paragraph>
     <paragraph label="Theorem 5.6">
      The time complexity of deciding whether a belief formula is satisfiable with respect to the class of DS-structures is NP-complete.
     </paragraph>
     <paragraph label="Proof">
      Since every probability structure is also a DS-structure, the theorem follows from Theorem 3.11 in [19]. The interested reader may refer to [19] for the details.  □
     </paragraph>
     <paragraph>
      We may define logical implication for belief formulas as usual. The above theorem tells us that the complexity of the logical implication problem with respect to the class of DS-structures on Routley structures is the same as that with respect to the class of Routley-structures (Theorem 4.22) and hence is not affected by the expansion of the propositional language with belief functions.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Some properties of distributive lattices
     </section-title>
     <paragraph>
      A lattice L is called a modular lattice if its elements satisfy the following condition:{a mathematical formula}
     </paragraph>
     <paragraph>
      With the following proposition, we know that a belief function can be defined on any lattice while probability functions can live only on distributive lattices.
     </paragraph>
     <paragraph label="Proposition A.1">
      (See Lemma 3 in[26].) Let L be a lattice. Then
     </paragraph>
     <list>
      <list-item label="1.">
       L is a modular if and only if it admits a strictly monotone 2-valuation.
      </list-item>
      <list-item label="2.">
       L is distributive if and only if it is modular and every strictly monotone 2-valuation on L is a 3-valuation.
      </list-item>
      <list-item label="3.">
       L is distributive if and only if it admits a strictly monotone 3-valuation.
      </list-item>
      <list-item label="4.">
       L is distributive if and only if it is modular and every strictly monotone 2-valuation on L is an ∞-valuation.
      </list-item>
     </list>
     <paragraph>
      Given a poset P, {a mathematical formula}J(P) denotes the lattice of order ideals of P. The lattice operations ∨ and ∧ on order ideals are just ordinary union and intersection (as subsets of P). The interested reader may refer to Section 3.4 in [61] (and Chapter IX in [9]) for the detailed proofs of the following propositions.
     </paragraph>
     <paragraph label="Theorem A.2">
      Let L be a finite distributive lattice. Then there is a unique (up to isomorphism) finite poset P for which{a mathematical formula}L≅J(P).
     </paragraph>
     <paragraph>
      This theorem is so important in combinatorial aspects of distributive lattices that it is called by Stanley the fundamental theorem for finite distributive lattices [61].
     </paragraph>
     <paragraph label="Lemma A.3">
      Let{a mathematical formula}I⩽I′in the distributive lattice{a mathematical formula}J(P). The interval{a mathematical formula}[I,I′]is isomorphic to{a mathematical formula}J(I′∖I), where{a mathematical formula}I′∖Iis regarded as an induced subposet of P. In particular,{a mathematical formula}[I,I′]is a distributive lattice.
     </paragraph>
     <paragraph label="Theorem A.4">
      If P is an n-element poset, then{a mathematical formula}J(P)is graded of rank n. Moreover, the rank{a mathematical formula}ρ(I)of{a mathematical formula}I∈J(P)is just the cardinality of I.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>