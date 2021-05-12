<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Characterizing causal action theories and their implementations in answer set programming.
   </title>
   <abstract>
    We consider a simple language for writing causal action theories, and postulate several properties for the state transition models of these theories. We then consider some possible embeddings of these causal action theories in some other action formalisms, and their implementations in logic programs with answer set semantics. In particular, we propose to consider what we call permissible translations from these causal action theories to logic programs. We identify two sets of properties, and prove that for each set, there is only one permissible translation, under strong equivalence, that can satisfy all properties in the set. We also show that these two sets of conditions are minimal in that removing any condition from each of them will result in multiple permissible mappings. Furthermore, as it turns out, for one set, the unique permissible translation is essentially the same as Balduccini and Gelfond's translation from Gelfond and Lifschitz's action language B to logic programs. For the other, it is essentially the same as Lifschitz and Turner's translation from the action language C to logic programs. This work provides a new perspective on understanding, evaluating and comparing action languages by using sets of properties instead of examples. The results in this paper provide a characterization of two representative action languages B and C in terms of permissible mappings from our causal action theories to logic programs. It will be interesting to see if other action languages can be similarly characterized, and whether new action formalisms can be defined using different sets of properties.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Formal reasoning about action has been a central topic in logic-based AI for a long time, and motivated much of the early work on nonmonotonic logics. The main difficulties have been the frame and the ramification problems. Current consensus in the community is that to solve the ramification problem, a notion of causality is needed. As a result, there has been much work on causal action theories (e.g. [1], [2], [3], [4], [5], [6], [7], [8], [9], [10], [11]), and a variety of languages and semantics have been proposed. These different approaches basically all agree when the set of causal rules is stratified, and in this case yields a complete action theory that can be represented, for example, by a set of successor state axioms. However, when there are cycles in the rules, it is not always clear how these rules are going to be represented according to these different approaches, and what the correct results are supposed to be. For instance, do we allow cyclic rules to produce indeterminate effects on actions?
     </paragraph>
     <paragraph>
      This motivated us to do a computer experiment that would systematically enumerate all possible causal theories in a small language, and look at their desirable models. As it turned out, what counts as a desirable model depends on what properties we want to have about causal theories. This led us to consider various properties of transition models of causal theories. We then consider how these various properties fit into some existing action languages that allow static causal rules. To make the comparisons systematic, and also for computational reasons, we consider what we call permissible translations of our causal action theories to logic programs under the answer set semantics [12], [13]. Specifically, given a set of properties on the transition models, we consider all possible permissible translations from our causal theories to logic programs so that the answer sets of these programs, when mapped back to the transition models of the causal theories, will satisfy all properties in the set. In this paper, we identify two such sets of properties. For both of them, our computer experiment shows that when there are at most three fluents in the language, the permissible translations are unique up to a notion of strong equivalence. The general case is proved by induction with the three fluent language as the base case.
     </paragraph>
     <paragraph>
      These two sets of conditions are minimal in that if any condition is dropped from either of the sets, then there will be multiple permissible translations.
     </paragraph>
     <paragraph>
      Furthermore, for one set of properties, the translation is essentially the same as Balduccini and Gelfond's translation from Gelfond and Lifschitz's action language {a mathematical formula}B[8] to logic programs. For the other, the translation is essentially the same as Lifschitz and Turner's translation from the action language {a mathematical formula}C[14] to logic programs. These results are significant in that they provide a new perspective on understanding, evaluating and comparing action languages by using sets of properties instead of examples. It is possible that other action languages can be similarly characterized, and new action languages defined using different sets of properties.
     </paragraph>
     <paragraph>
      The rest of the paper is organized as follows. In Section 2 we formally introduce the syntax of the causal action theories that we use in this work. Next we list some reasonable properties that we expect the semantics of the causal action theories to satisfy in Section 3. Then in Section 4 we consider some straightforward mappings of our theories to some existing formalisms such as the action languages {a mathematical formula}B and {a mathematical formula}C, and the situation calculus. In Section 5 we consider the problem of mapping causal action theories to logic programs under the answer set semantics, define the notion of permissible translations, and give our main results. And finally in Section 6 we conclude the paper. The detailed proofs of the two main theorems are given in the online Appendix.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Simple causal action theories
     </section-title>
     <paragraph>
      We assume a finite set {a mathematical formula}F of propositional atoms called fluents. We also assume two distinguished symbols “⊤” for tautology, and “⊥” for contradiction. A fluent literal is either f or ¬f where {a mathematical formula}f∈F. So far in work on causal action theory, the focus is on the formalization of the effects of primitive actions, and how the causal rules are used in this formalization. The actions are assumed to be independent, in the sense that the effects of one action are independent of the effects of any other actions. So to make our formalism as simple and to the point as possible, we assume that there is just one unnamed action in our language, and when we talk about the effect of an action, we refer to the effect of this implicitly assumed, unnamed action.
     </paragraph>
     <paragraph>
      Syntactically, a causal action theory is a pair {a mathematical formula}(S,D), where S is a set of static causal rules, and D is a set of dynamic causal rules. Both static and dynamic causal rules are pairs of the form {a mathematical formula}(l,G), where l is a fluent literal, and G a set of fluent literals. As a static causal rule, {a mathematical formula}(l,G) means that in every situation, whenever all fluent literals in G hold, l is caused to be true. As a dynamic causal rule, it means that in every situation where all fluent literals in G hold, if the action is successfully executed, then l will be true in the new situation. Thus our dynamic causal rules are essentially direct action effect axioms. Notice that in the dynamic causal rules, the action argument is omitted here as we have assumed that there is just one action. In the following, we call l the head, and G the premise of the static or dynamic causal rule. We assume that G is consistent, i.e. it does not contain both f and ¬f, and does not contain ⊥. We define a premise G to be a set of fluent literals because the order of fluent literals in the premise does not matter. However, we often write G as a conjunction of fluent literals in it. For instance, both {a mathematical formula}f1∧f2 and {a mathematical formula}f2∧f1 denote the same premise {a mathematical formula}{f1,f2}. In particular, the empty set ∅ is denoted by ⊤.
     </paragraph>
     <paragraph>
      Semantically, a causal action theory specifies a set of transitions. A transition is a pair {a mathematical formula}(s,s′), where both s and {a mathematical formula}s′ are states, which are sets of fluents. A state s can be considered as a truth assignment such that a fluent f is true in s iff {a mathematical formula}f∈s. For a formula φ, we write {a mathematical formula}s⊨φ if φ is true in the truth assignment s. Similarly, for a set of fluent literals G, we write {a mathematical formula}s⊨G if all fluent literals in G hold in the truth assignment. In particular, {a mathematical formula}s⊨∅ for any state s. Intuitively, a transition {a mathematical formula}(s,s′) means that the action can be successfully executed in s to yield {a mathematical formula}s′.
     </paragraph>
     <paragraph label="Definition 1">
      A state is a set of fluent atoms, and a transition is a pair of states. A semantic function δ is a mapping from causal action theories to sets of transitions.
     </paragraph>
     <paragraph>
      Thus a semantic function δ gives a semantics to each causal action theory. We say that two causal action theories {a mathematical formula}T1 and {a mathematical formula}T2 are equivalent under δ if they have the same transitions: {a mathematical formula}δ(T1)=δ(T2). In the next section, we are going to discuss some properties about semantic functions.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Properties
     </section-title>
     <paragraph label="Property 1">
      We assume a fixed semantic function δ below. Thus when we say that {a mathematical formula}(s,s′) is a transition of T, we mean that {a mathematical formula}(s,s′)∈δ(T). We list below some interesting properties about δ. Our first property is that the states in a transition must satisfy every static causal rule. Static causal rules are state constraintsIf{a mathematical formula}(s,s′)is a transition of a causal action theory{a mathematical formula}(S,D), then for every static causal rule{a mathematical formula}(l,G)in S, we have that{a mathematical formula}
     </paragraph>
     <paragraph>
      This property is commonly accepted by most action semantics. So we consider it should be satisfied as a basic property and build it in our permissible mapping.
     </paragraph>
     <paragraph label="Property 2">
      When reasoning about, say whether a switch is open or closed, we can use fluent {a mathematical formula}closed to mean that the switch is closed and represent the fact that the switch is open by {a mathematical formula}¬closed. Or we can do it the other way around, use {a mathematical formula}open to mean that the switch is open and represent {a mathematical formula}closed by {a mathematical formula}¬open. Our following property says that choosing which one to use as primitive is immaterial as long as one does this systematically. Fluent literals are interchangeableFor any causal action theory T, any fluent f, and any pair of states{a mathematical formula}s1and{a mathematical formula}s2,{a mathematical formula}(s1,s2)is a transition of T, iff{a mathematical formula}(s1f,s2f)is a transition of{a mathematical formula}Tf, where for any state s,{a mathematical formula}and for any causal action theory T,{a mathematical formula}Tfis the causal action theory obtained from T by replacing every occurrence of f by ¬f.
     </paragraph>
     <paragraph>
      Our next property says that if the premise of a static causal rule contains the negation of its head, then this rule is basically a constraint according to Property 1.
     </paragraph>
     <paragraph label="Property 3">
      Immediate negative loops can be eliminatedFor any causal action theory{a mathematical formula}(S,D), any{a mathematical formula}r=(l,{¬l}∪G)∈S, and any states s and{a mathematical formula}s′that satisfy all rules in S (i.e.Property 1holds for S), we have that{a mathematical formula}(s,s′)is a transition of{a mathematical formula}(S,D)iff{a mathematical formula}(s,s′)is a transition of{a mathematical formula}(S∖{r},D).
     </paragraph>
     <paragraph>
      Our next property says that if there are no possible interactions between the static and dynamic causal rules, then only the dynamic causal rules can be applied. In other words, there are no ramifications.
     </paragraph>
     <paragraph label="Property 4">
      No ramification when static causal rules do not interact with dynamic causal rulesLet{a mathematical formula}T=(S,D)be a causal action theory. If for every{a mathematical formula}(l,G)∈D, there is no{a mathematical formula}(l′,G′)∈Ssuch that the fluent in l occurs in{a mathematical formula}G′, then{a mathematical formula}(s,s′)is a transition of T iff
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}s′=(s∖s−)∪s+,
      </list-item>
      <list-item label="•">
       {a mathematical formula}s+∩s−=∅, and
      </list-item>
      <list-item label="•">
       both s and{a mathematical formula}s′satisfy the static causal rules in S (Property 1),
      </list-item>
     </list>
     <paragraph>
      The next property is a weaker version of Property 4. Before giving it we first define the dependency graph of a causal action theory. Given a causal action theory {a mathematical formula}T=(S,D), its dependency graph is the directed graph such that
     </paragraph>
     <list>
      <list-item label="•">
       its vertices are arbitrary fluent literals, and
      </list-item>
      <list-item label="•">
       it has an edge from {a mathematical formula}l1 to {a mathematical formula}l2 iff S contains a static causal rule {a mathematical formula}(l1,G) such that {a mathematical formula}l2∈G.
      </list-item>
     </list>
     <paragraph label="Property 4′">
      No ramification when static causal rules do not have a cycle and do not interact with dynamic causal rulesLet{a mathematical formula}T=(S,D)be a causal action theory whose dependency graph is acyclic. If for every{a mathematical formula}(l,G)∈D, there is no{a mathematical formula}(l′,G′)∈Ssuch that the fluent in l occurs in{a mathematical formula}G′, then{a mathematical formula}(s,s′)is a transition of T iff
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}s′=(s∖s−)∪s+,
      </list-item>
      <list-item label="•">
       {a mathematical formula}s+∩s−=∅, and
      </list-item>
      <list-item label="•">
       both s and{a mathematical formula}s′satisfy the static causal rules in S (Property 1),
      </list-item>
     </list>
     <paragraph>
      Property 4′ is weaker than Property 4 as the former applies only to “stratified” causal action theories.
     </paragraph>
     <paragraph>
      The next property concerns the redundancy in premises. If both q and ¬q will cause p, then p must be true regardless. Similarly, if both {a mathematical formula}q∧r and {a mathematical formula}¬q∧r causes p, then we can conclude that q is immaterial and that r causes p.
     </paragraph>
     <paragraph label="Property 5">
      Premises of static causal rules can be combinedLet{a mathematical formula}T=(S,D)be a causal action theory. If both{a mathematical formula}(f,G1)and{a mathematical formula}(f,G2)are in S, and for some set G of fluent literals, formula{a mathematical formula}is logically equivalent to formula{a mathematical formula}then the set of transitions under T is the same as the set of transitions under{a mathematical formula}T′=(S′,D), where{a mathematical formula}S′=(S∖{(f,G1),(f,G2)})∪{(f,G)}.
     </paragraph>
    </section>
    <section label="4">
     Embedding causal action theories in {a mathematical formula}B, C, and others
     <paragraph>
      Our causal action theories can be mapped to theories in action languages {a mathematical formula}B, {a mathematical formula}C, and others in a straightforward way. Notice that our language does not have terms for actions. Instead, there is an implicit action. Let's call this action A.
     </paragraph>
     <paragraph>
      Given a causal action theory {a mathematical formula}T=(S,D), it can be mapped to the following action description {a mathematical formula}TB in language {a mathematical formula}B as follows: if {a mathematical formula}(l,G) is in S, then the static causal rule “{a mathematical formula}l if G” is in {a mathematical formula}TB, and if {a mathematical formula}(l,G) is in D, then the action rule “{a mathematical formula}A causes l if G” is in {a mathematical formula}TB. This mapping induces a semantic function δ for our causal action theories: {a mathematical formula}(s,s′)∈δ(T) iff {a mathematical formula}(s,A,s′) is a transition of {a mathematical formula}TB according to {a mathematical formula}B. For this semantic function, it can be seen that Property 1, Property 3, Property 4 are satisfied (see Theorem 1 below). These three properties give a characterization of {a mathematical formula}B semantics. Besides Property 2, Property 4′ are also satisfied, but Property 5 is not.
     </paragraph>
     <paragraph>
      A causal action theory {a mathematical formula}T=(S,D) can also be translated to the following action description {a mathematical formula}TC in action language {a mathematical formula}C as follows: if {a mathematical formula}(l,G) is in S, then the static causal rule “{a mathematical formula}caused l if ⋀li∈Gli” is in {a mathematical formula}TC, and if {a mathematical formula}(l,G) is in D, then the action rule “{a mathematical formula}caused l if ⊤ after A∧⋀li∈Gli” is in {a mathematical formula}TC. Again this mapping induces a semantic function: {a mathematical formula}(s,s′) is a transition of T if {a mathematical formula}(s,A,s) is a transition of {a mathematical formula}TC according to {a mathematical formula}C semantics. For this semantic function, we can see that Property 1, Property 2, Property 3, Property 5 are satisfied, but not Property 4. For instance, consider the causal action theory {a mathematical formula}T=({(f2,f1),(f1,f2)},∅). If {a mathematical formula}s=∅, and {a mathematical formula}s′={f1,f2}, then both s and {a mathematical formula}s′ satisfies all static causal rules, and according to {a mathematical formula}C semantics, {a mathematical formula}s′ is a possible new state after the action A occurs in state s.
     </paragraph>
     <paragraph>
      A causal action theory {a mathematical formula}T=(S,D) can also be mapped to Lin's causal theory {a mathematical formula}TL in the situation calculus as follows: if {a mathematical formula}(f,G0) is in S, let {a mathematical formula}G=⋀li∈G0li, then the following causal rule is in {a mathematical formula}TL: {a mathematical formula}∀s.Holds(G,s)⊃Caused(f,true,s); if {a mathematical formula}(¬f,G) is in S, then the following causal rule is in {a mathematical formula}TL: {a mathematical formula}∀s.Holds(G,s)⊃Caused(f,false,s); if {a mathematical formula}(f,G) is in D, then the following direct effect axiom is in {a mathematical formula}TL: {a mathematical formula}∀s.(Poss(A,s)⊃(Holds(G,s)⊃Caused(f,true,do(A,s)))); and if {a mathematical formula}(¬f,G) is in D, then the following direct effect axiom is in {a mathematical formula}TL:
     </paragraph>
     <paragraph>
      {a mathematical formula}∀s.(Poss(A,s)⊃(Holds(G,s)⊃Caused(f,false,do(A,s)))).
     </paragraph>
     <paragraph>
      As in {a mathematical formula}C, under this mapping to Lin's causal theories, Property 4 is not satisfied.
     </paragraph>
     <paragraph>
      One could do similar mappings for other formalisms. However, an obvious question is why the mappings have to be the way that we described above. For instance, could we map theories here to language {a mathematical formula}C differently so that Property 1, Property 4 will be satisfied? If we do not have any restrictions on the mappings, then this is certainly possible as one can always compute the transitions first and then find a theory in {a mathematical formula}C that have the same transitions. In this paper we consider this problem by choosing answer set logic programs as the target language. This is for two reasons. One is the availability of good ASP solvers for computing answer sets of a logic program. The other reason is that there are already well-studied mappings from languages like {a mathematical formula}B and {a mathematical formula}C to answer set logic programs. In the next section, we look at all possible compositional mappings of our causal action theories to logic programs that use a “standard” way of encoding inertia.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      From causal action theories to answer set programming
     </section-title>
     <paragraph>
      There has been much work using logic programs for implementing and/or formalizing causal action theories (e.g. [4], [15], [16], [17], [18]). In this paper we consider mapping our causal action theories to logic programs under answer set semantics.
     </paragraph>
     <paragraph>
      Given a set {a mathematical formula}F of fluents, and a causal action theory T in {a mathematical formula}F, we consider mapping T to a normal logic program (with constraints and classical negation) {a mathematical formula}ξ(T) in the language {a mathematical formula}L=F∪¬F∪F′∪¬F′, where {a mathematical formula}¬F={¬f|f∈F}, {a mathematical formula}F′={f′|f∈F}, and similarly for {a mathematical formula}¬F′. We assume here that for each {a mathematical formula}f∈F, {a mathematical formula}f′ is a new atom. The transitions of T and the answer sets of {a mathematical formula}ξ(T) will then be related by identifying s with the fluents in {a mathematical formula}F, and {a mathematical formula}s′ with those in {a mathematical formula}F′: {a mathematical formula}(s,s′) is a transition of T iff there is an answer set A of {a mathematical formula}ξ(T) such that{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Again, if we do not have any restrictions on what programs we can take as {a mathematical formula}ξ(T), then we can have mappings that satisfy any consistent set of properties under the above correspondence between transitions and answer sets. However, from knowledge representation point of view, we would want the mapping to be compositional, in the sense that it can be composed from some mappings on the static and dynamic causal rules. As we mentioned, there has been much work on using logic programs for reasoning about action, and one of the key ideas has been to use the following rules to encode inertia:{a mathematical formula}{a mathematical formula} Also we want the mapping to at least satisfy Property 1 so that both initial and successor states satisfy the static causal rules as constraints, and that a causal rule {a mathematical formula}(l,G) should be translated to some logic program rules about l. Besides, we want the mapping to be uniform in the sense that the fluent names are not material. More precisely, if σ is a permutation of fluent names, then applying the mapping to T after the fluent names are changed according to σ is the same as applying the mapping to T first, and then changing the fluent names in the logic program according to σ.
     </paragraph>
     <paragraph>
      To summarize, we study the following class of mappings.
     </paragraph>
     <paragraph label="Definition 2">
      A mapping ξ from causal action theories to logic programs is said to be permissible if it is
     </paragraph>
     <list>
      <list-item label="1.">
       (Compositional) For each {a mathematical formula}T=(S,D),{a mathematical formula} where
      </list-item>
      <list-item label="2.">
       (Uniform) Both {a mathematical formula}ξs and {a mathematical formula}ξd are homomorphic under any permutation σ on the set {a mathematical formula}F of fluents: {a mathematical formula}ξs(rσ)=(ξs(r))σ, and {a mathematical formula}ξd(rσ)=(ξd(r))σ, where {a mathematical formula}rσ is obtained from r by a fluent substitution according to σ, and for any logic program P, {a mathematical formula}Pσ is the program obtained from P by a fluent substitution according to σ.
      </list-item>
     </list>
     <paragraph>
      Notice that for the translation {a mathematical formula}ξd(r) of a dynamic causal rule, no “negation-as-failure” operator is used. This is because we have the choice rules (8) and (9) in the base that generate all possible complete initial states. Under these choice rules, and given that there is no other rule about f or ¬f in a permissible mapping, fluent literals “f” and “{a mathematical formula}not ¬f” are interchangeable, and so are “¬f” and “{a mathematical formula}not f”. Of course, we could allow the negation-as-failure operator in the translation of dynamic causal rules.
     </paragraph>
     <paragraph label="Proposition 1">
      Notice that a mapping ξ from causal action theories to logic programs yields a semantic function δ under (1) and (2): {a mathematical formula}(s,s′)∈δ(T) iff there is an answer set A of {a mathematical formula}ξ(T) such that (1) and (2) hold. So in the following, when we say that a mapping satisfies a property, we mean that the semantic function yielded by the mapping satisfies this property. If a mapping ξ is permissible, then ξ satisfiesProperty 1.
     </paragraph>
     <paragraph>
      Our main results are about the uniqueness of admissible mappings that satisfies certain sets of properties. Notice that with the presence of (6) and (7), we can easily prove the following proposition. Understandably, this uniqueness needs to be modulo on strong equivalence [19] as two mappings that always yield strongly equivalent logic programs are indistinguishable under the answer set semantics.
     </paragraph>
     <paragraph>
      Our first result shows the correspondence between action language {a mathematical formula}B and permissible mappings that satisfy Property 1, Property 3, Property 4. In the last section, we described a translation from our causal action theories to causal theories in action language {a mathematical formula}B. Given a causal action theory T, let {a mathematical formula}TB denote the causal theory in {a mathematical formula}B according to this translation. We say that {a mathematical formula}(s,s′) is a transition of T under action language {a mathematical formula}B semantics if {a mathematical formula}(s,A,s′) is a transition of {a mathematical formula}TB according to the semantics of action language {a mathematical formula}B.
     </paragraph>
     <paragraph label="Theorem 1">
      Let{a mathematical formula}ξBbe the following mapping from causal action theories to logic programs: for each{a mathematical formula}T=(S,D),{a mathematical formula}where
     </paragraph>
     <list>
      <list-item label="•">
       B is the base,
      </list-item>
      <list-item label="•">
       for each static causal rule{a mathematical formula}(l,G),{a mathematical formula}ξBs(l,G)is the set of rules consisting of constraints(6)and(7)and the following rule{a mathematical formula}
      </list-item>
      <list-item label="•">
       for each dynamic causal rule{a mathematical formula}(l,G),{a mathematical formula}ξBd(l,G)is the singleton set consisting of the following rule{a mathematical formula}
      </list-item>
     </list>
     <paragraph>
      We have a similar result for the action language {a mathematical formula}C as well. In the following, given a causal action theory T, we say that {a mathematical formula}(s,s′) is a transition of T under {a mathematical formula}C semantics if {a mathematical formula}(s,A,s′) is a transition of {a mathematical formula}TC according to {a mathematical formula}C, where {a mathematical formula}TC is the action description in {a mathematical formula}C translated from T given in the last section.
     </paragraph>
     <paragraph label="Theorem 2">
      Let{a mathematical formula}ξCbe the following mapping from causal action theories to logic programs: for each{a mathematical formula}T=(S,D),{a mathematical formula}where
     </paragraph>
     <list>
      <list-item label="•">
       B is the base,
      </list-item>
      <list-item label="•">
       for each static causal rule{a mathematical formula}(l,G),{a mathematical formula}ξCs(l,G)is the set of rules consisting of constraints(6)and(7)and the following rule{a mathematical formula}
      </list-item>
      <list-item label="•">
       for each dynamic causal rule{a mathematical formula}(l,G),{a mathematical formula}ξCd(l,G)is the singleton set consisting of the following rule{a mathematical formula}
      </list-item>
     </list>
     <paragraph>
      The complete proofs of these two theorems are given in the online appendix. They are done inductively. The base case is the language with three fluents. For the base case, the results are verified by a computer program that for each representative dynamic or static causal rule, enumerates all of its possible permissible mappings, and for each possible mapping checks if the respective properties are satisfied. The inductive step is proved manually. As permissible mappings are compositional, we can decompose the proof for causal action theories into that for single causal rules. For each type of static/dynamic causal rules, to satisfy the properties, a permissible mapping has to map it to a logic program strongly equivalent with that in the theorems. We sketch the inductive step in the proof of Theorem 1 to illustrate. First, we prove that for any permissible mapping ξ and any dynamic rule r, if ξ satisfies Property 4′, {a mathematical formula}ξd(r) is strongly equivalent with {a mathematical formula}ξBd(r) in Theorem 1 (and also with {a mathematical formula}ξCd(r) in Theorem 2) under base B. Then we successively prove that for any permissible mapping ξ, for each r of the following types of static rules, if ξ satisfies the properties in Theorem 1, then {a mathematical formula}ξs(r) is strongly equivalent with {a mathematical formula}ξBs(r) under base B and the corresponding state constraints of form (6) and (7):
     </paragraph>
     <list>
      <list-item label="•">
       static rules without any fluent loop
      </list-item>
      <list-item label="•">
       static rules with negative fluent loop
      </list-item>
      <list-item label="•">
       static rules with positive fluent loop
      </list-item>
     </list>
     <paragraph>
      The definition of positive/negative fluent loop is given in the online appendix.
     </paragraph>
     <paragraph>
      While the proof of the inductive step is tedious and non-trivial, the base case is conceptually more important. In fact, the theorems and the properties were “discovered” using our computer program. This is similar to computer-aided theorem discovery that we used earlier for some other problems [20], [21], [22].
     </paragraph>
     <paragraph>
      These two theorems provide interesting insights into the relationships between the two action languages {a mathematical formula}B and {a mathematical formula}C. First of all, they both satisfy Property 1, thus all states in their transition models must satisfy all static causal rules. They also satisfy Property 3, thus treat static causal rules with negative loops as constraints.
     </paragraph>
     <paragraph>
      However, while {a mathematical formula}B seems to treat causal theories with or without positive dependency loops uniformly, {a mathematical formula}C assigns special meanings to static causal rules with positive loops. This can be seen from the fact that while {a mathematical formula}B satisfies Property 4, {a mathematical formula}C only satisfies a weaker version of that, Property 4′, which applies only to stratified theories. As an example, consider {a mathematical formula}T=({(f1,f2),(f2,f1)},∅). The two causal rules cause a cycle between {a mathematical formula}f1 and {a mathematical formula}f2. Under {a mathematical formula}B's semantics, for {a mathematical formula}(∅,s) to be a transition, it must be the case that {a mathematical formula}s=∅. In other words, when both {a mathematical formula}f1 and {a mathematical formula}f2 are false initially, then they must both stay false in the successor state. However, under {a mathematical formula}C's semantics, {a mathematical formula}(∅,{f1,f2}) is also a transition of T. In fact, static causal rules with immediate positive cycles such as {a mathematical formula}(f,f) (or causedfiff in {a mathematical formula}C's language) have a special role: they are used to express the assumption that the fluent f is a default fluent.
     </paragraph>
     <paragraph>
      Another difference between {a mathematical formula}B and {a mathematical formula}C can be seen from Property 5. The language {a mathematical formula}C satisfies this property, thus allows premises from multiple static causal rules to be merged together and simplified by logical equivalence. However, this is in general not allowed in {a mathematical formula}B. Consider the following causal action theories{a mathematical formula} The premises of the first two static causal rules can be merged and simplified according to {a mathematical formula}C: T is equivalent to {a mathematical formula}T′ below:{a mathematical formula} But under {a mathematical formula}B's semantics, these two theories are not equivalent. It can be seen that {a mathematical formula}(∅,{f1,f2,f3}) is a transition of {a mathematical formula}T′ but not T under {a mathematical formula}B.
     </paragraph>
     <paragraph>
      A corollary of these two theorems is that there is no permissible mapping that can satisfy all the properties.
     </paragraph>
     <paragraph label="Corollary 3">
      There does not exist a permissible mapping ξ such that it satisfiesProperty 1, Property 2, Property 3, Property 4, Property 5.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Supplementary material
     </section-title>
     <paragraph>
      The following is the Supplementary material related to this article.{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>