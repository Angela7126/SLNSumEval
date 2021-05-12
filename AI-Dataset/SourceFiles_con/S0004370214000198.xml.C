<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Limitations of acyclic causal graphs for planning.
   </title>
   <abstract>
    Causal graphs are widely used in planning to capture the internal structure of planning instances. Researchers have paid special attention to the subclass of planning instances with acyclic causal graphs, which in the past have been exploited to generate hierarchical plans, to compute heuristics, and to identify classes of planning instances that are easy to solve. This naturally raises the question of whether planning is easier when the causal graph is acyclic. In this article we show that the answer to this question is no, proving that in the worst case, the problem of plan existence is PSPACE-complete even when the causal graph is acyclic. Since the variables of the planning instances in our reduction are propositional, this result applies to Strips planning with negative preconditions. We show that the reduction still holds if we restrict actions to have at most two preconditions. Having established that planning is hard for acyclic causal graphs, we study two subclasses of planning instances with acyclic causal graphs. One such subclass is described by propositional variables that are either irreversible or symmetrically reversible. Another subclass is described by variables with strongly connected domain transition graphs. In both cases, plan existence is bounded away from PSPACE, but in the latter case, the problem of bounded plan existence is hard, implying that optimal planning is significantly harder than satisficing planning for this class.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The causal graph offers insight into the interdependence among the variables of a planning instance. A sparse causal graph characterizes a planning instance with few variable dependencies, potentially making it easier to determine when and how to change the value of some variable. Acyclic causal graphs have been of particular interest, implying an asymmetry: while changing the value of some variable v, we do not have to worry about dependencies that other variables might have on v. This knowledge has been exploited in a variety of ways among the planning community.
     </paragraph>
     <paragraph>
      Among other things, acyclic causal graphs have been exploited to decompose planning instances into action hierarchies [1], [2], to compute domain-independent heuristics for planning [3], and to identify classes of planning instances that are easy to solve [4], [5], [6], [7], [8]. In each case, the resulting algorithm or procedure will not work if the causal graph is not acyclic. Thus one may be led to believe that planning is easier when the causal graph is acyclic. However, the exact complexity of planning over acyclic causal graphs has remained unknown: several researchers have shown that it is NP-hard [9], [6], [10], while planning is known to be PSPACE-complete in the general case of Strips[11] and Sas{sup:+}[12].
     </paragraph>
     <paragraph>
      In this article we close this complexity gap, establishing that the complexity of planning is PSPACE-complete for the class Acyc of planning instances with acyclic causal graphs. This result holds both for plan existence, the problem of determining whether there exists a solution to a given planning instance, and bounded plan existence, the problem of determining whether there exists a solution of bounded length. The results also holds for both Strips and Sas{sup:+} planning, although in the case of Strips our reduction requires the use of negative preconditions (when only positive preconditions are allowed, plan existence is known to be in P and bounded plan existence is NP-complete). As a consequence of our result, planning is no easier when the causal graph is acyclic, at least not in the worst case.
     </paragraph>
     <paragraph>
      We also study two subclasses of Acyc: the class ISR-Acyc of planning instances with propositional variables that are either irreversible or symmetrically reversible, and the class SC-Acyc of planning instances with strongly connected domain transition graphs. We show that plan existence is NP-complete for ISR-Acyc and in P for SC-Acyc; i.e. in both cases, planning becomes easier when we impose additional restrictions. We also show that bounded plan existence is PSPACE-hard for SC-Acyc, implying that optimal planning is significantly harder than satisficing planning for this class.
     </paragraph>
     <paragraph>
      The work presented in this article was previously published in the proceedings of the 2013 International Conference on Automated Planning and Scheduling (ICAPS). Compared to the conference publication, the present article includes the following novel content:
     </paragraph>
     <list>
      <list-item label="•">
       An encoding of the reduction from Qbf-Sat to plan existence for Acyc in PDDL, effectively translating quantified Boolean formulae to planning instances.
      </list-item>
      <list-item label="•">
       A modification of the reduction such that actions have at most two preconditions, strengthening a previous result of Bylander [11].
      </list-item>
      <list-item label="•">
       An analysis showing that plan existence is NP-complete for the subclass ISR-Acyc of Acyc.
      </list-item>
      <list-item label="•">
       A proof that bounded plan existence for SC-Acyc is PSPACE-complete, strengthening our previous result (which stated that it is #P-hard).
      </list-item>
     </list>
     <paragraph>
      The rest of the article is organized as follows. Section 2 introduces the notation that we use in the article. Section 3 describes how to define planning instances that simulate nested loops over an arbitrary number of propositional variables. Section 4 shows how to use these ideas to reduce Qbf-Sat to plan existence for Acyc, and describes a PDDL encoding of the reduction. Section 5 shows how to modify the previous reduction such that actions have at most two preconditions. Sections 6 and 7 study the complexity of the two subclasses ISR-Acyc and SC-Acyc. Section 8 relates our results to previous work in the field, while Section 9 concludes with a discussion.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Notation
     </section-title>
     <paragraph>
      In this article we study the complexity of both Strips and Sas{sup:+} planning. To simplify the notation, we use a common description of planning instances that is valid for either formalism. The only difference between formalisms is the size of the variable domains, which equals two for Strips planning but is generally larger than two for Sas{sup:+} planning. For Strips planning, since each variable v is propositional, we use literals v and {a mathematical formula}v¯ to describe the possible values of v instead of an explicit domain such as {a mathematical formula}{0,1}.
     </paragraph>
     <paragraph>
      Let V be a set of variables, and let {a mathematical formula}D(v) be the finite domain of each variable {a mathematical formula}v∈V. A partial state p is a function on a subset of variables {a mathematical formula}Vp⊆V that maps each variable {a mathematical formula}v∈Vp to a value {a mathematical formula}p(v)∈D(v) in its domain. A state s is a partial state such that {a mathematical formula}Vs=V. The projection {a mathematical formula}p|U of a partial state p onto a subset of variables {a mathematical formula}U⊆V is a partial state q such that {a mathematical formula}Vq=Vp∩U and {a mathematical formula}q(v)=p(v) for each {a mathematical formula}v∈Vq. The composition {a mathematical formula}p⊕q of two partial states p and q is a partial state r such that {a mathematical formula}Vr=Vp∪Vq, {a mathematical formula}r(v)=q(v) for each {a mathematical formula}v∈Vq, and {a mathematical formula}r(v)=p(v) for each {a mathematical formula}v∈Vp∖Vq. Composition is not a commutative operation, but it is left associative.
     </paragraph>
     <paragraph>
      When variables are propositional, we use sets of literals to define partial states, where each literal simultaneously defines a variable and its value. Given a subset {a mathematical formula}U⊆V of propositional variables, let {a mathematical formula}U¯={u¯:u∈U} denote the partial state with all variables in U negated.
     </paragraph>
     <paragraph>
      A planning instance is a tuple {a mathematical formula}P=〈V,A,I,G〉 where V is a set of variables defined as above, A is a set of actions with unit cost, I is an initial state, and G is a (partial) goal state. Each action {a mathematical formula}a=〈pre(a),post(a)〉∈A has precondition {a mathematical formula}pre(a) and postcondition {a mathematical formula}post(a), both partial states on V. Action a is applicable in state s if {a mathematical formula}s|Vpre(a)=pre(a), and applying a in s results in a new state {a mathematical formula}s′=s⊕post(a).
     </paragraph>
     <paragraph>
      A plan is a sequence of actions {a mathematical formula}〈a1,…,ak〉 such that {a mathematical formula}a1 is applicable in the initial state I and, for each {a mathematical formula}2⩽i⩽k, {a mathematical formula}ai is applicable in the state {a mathematical formula}I⊕post(a1)⊕⋯⊕post(ai−1). The plan solves P if the goal state is satisfied after applying {a mathematical formula}〈a1,…,ak〉, i.e. if {a mathematical formula}(I⊕post(a1)⊕⋯⊕post(ak))|VG=G. A landmark is a subgoal that must be achieved on every plan (in this article we only consider subgoals on single variables).
     </paragraph>
     <paragraph>
      The causal graph of P is a directed graph {a mathematical formula}G=(V,E) with the variables of P as nodes. There is an edge {a mathematical formula}(u,v)∈E if and only if there exists an action {a mathematical formula}a∈A such that {a mathematical formula}u∈Vpre(a)∪Vpost(a) and {a mathematical formula}v∈Vpost(a). In this article we focus on planning instances with acyclic causal graphs, implying that each action {a mathematical formula}a∈A is unary, i.e. satisfies {a mathematical formula}|Vpost(a)|=1, since two or more variables in a postcondition would induce a cycle in the causal graph.
     </paragraph>
     <paragraph>
      The domain transition graph (DTG) of a variable v is a directed graph {a mathematical formula}DTG(v)=(D(v),E) with the values in the domain {a mathematical formula}D(v) of v as nodes, and there is an edge {a mathematical formula}(x,y)∈E if and only if {a mathematical formula}x≠y and there exists an action {a mathematical formula}a∈A such that {a mathematical formula}post(a)(v)=y and either {a mathematical formula}v∉Vpre(a) or {a mathematical formula}pre(a)(v)=x. {a mathematical formula}DTG(v) is strongly connected if and only if there is a directed path between x and y for each pair of values {a mathematical formula}x,y∈D(v).
     </paragraph>
     <paragraph>
      A propositional variable {a mathematical formula}v∈V is irreversible if there exists no pair of actions {a mathematical formula}a,a′∈A such that {a mathematical formula}post(a)={v} and {a mathematical formula}post(a′)={v¯}. Variable {a mathematical formula}v∈V is symmetrically reversible if for each action {a mathematical formula}a∈A such that {a mathematical formula}v∈Vpost(a), there exists an action {a mathematical formula}a′∈A such that {a mathematical formula}post(a′)=post¯(a) and {a mathematical formula}pre(a′)|(Vpre(a)∖{v})=pre(a)|(Vpre(a)∖{v}), i.e. {a mathematical formula}a′ and a have opposite effects but the same precondition on variables other than v.
     </paragraph>
     <paragraph>
      We define three classes of planning instances whose complexity we study in the article:
     </paragraph>
     <list>
      <list-item label="•">
       Acyc: planning instances with acyclic causal graphs.
      </list-item>
      <list-item label="•">
       ISR-Acyc: the subclass of planning instances in Acyc with propositional variables that are either irreversible or symmetrically reversible.
      </list-item>
      <list-item label="•">
       SC-Acyc: the subclass of planning instances in Acyc such that all variables have strongly connected DTGs.
      </list-item>
     </list>
     <paragraph>
      Given an arbitrary planning instance P, we can check in polynomial time whether it belongs to Acyc, ISR-Acyc, and/or SC-Acyc.
     </paragraph>
     <paragraph>
      For each class of planning instances X, we define Pe(X), the decision problem of plan existence for X, as follows:
     </paragraph>
     <paragraph>
      Input: A planning instance {a mathematical formula}P∈X.
     </paragraph>
     <paragraph>
      Question: Does there exist a plan solving P?
     </paragraph>
     <paragraph>
      We also define the decision problem Bpe(X), the decision problem of bounded plan existence for X, as follows:
     </paragraph>
     <paragraph>
      Input: A planning instance {a mathematical formula}P∈X and an integer K.
     </paragraph>
     <paragraph>
      Question: Is there a plan solving P of length at most K?
     </paragraph>
     <paragraph>
      Note that Pe(X) is polynomially reducible to Bpe(X) since each solvable planning instance must have a solution of length at most {a mathematical formula}K=∏v∈V|D(v)|. Any longer plan must revisit states, and such a plan can always be shortened by removing all actions between a state and itself.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Loop instances
     </section-title>
     <paragraph>
      In this section we introduce a novel mechanism for simulating nested loops using planning instances with propositional variables and acyclic causal graphs. There are examples in the literature of planning instances in Acyc that iterate over all assignments to n variables [12], but none of these guarantee that assignments are not repeated, something that is crucial in our work. We describe our novel mechanism separately for two reasons: it is the most complicated part of our subsequent reductions, and it might have uses beyond those exploited in this article. Here, we present three loop instances of increasing complexity, and finish with an example.
     </paragraph>
     <section label="3.1">
      <section-title>
       Single variable loops
      </section-title>
      <paragraph>
       Our mechanism for simulating loops is based on a simple idea that we call loop instance, defined with respect to a specific planning instance.
      </paragraph>
      <paragraph label="Definition 1">
       Given a planning instance {a mathematical formula}P=〈V,A,I,G〉, a loop instance is a subset {a mathematical formula}U={a,b,x,u1,u2}⊆V such that {a mathematical formula}{u¯1,u¯2}⊆I and {a mathematical formula}u2 is a landmark of P, and the only actions on U are those in the set {a mathematical formula}A(U)⊆A, which we define below.
      </paragraph>
      <paragraph>
       In other words, {a mathematical formula}u1 and {a mathematical formula}u2 are initially false, and either {a mathematical formula}u2∈G or {a mathematical formula}u2 is a precondition of some action required to reach the goal state G.
      </paragraph>
      <paragraph>
       Fig. 1 shows the actions in {a mathematical formula}A(U), where {a mathematical formula}v1, {a mathematical formula}v2, etc. are the actions affecting a variable v. The actions in {a mathematical formula}A(U) may have preconditions other than those appearing in the table, which is why we refer to them as partial preconditions. The names of the variables in a loop instance may vary as long as the associated actions match those in the set {a mathematical formula}A(U). Action {a mathematical formula}x2 is not strictly needed until later; its purpose in this section is to show that the subsequent lemmas hold even when it is present.
      </paragraph>
      <paragraph>
       Fig. 1 also shows the causal graph of a loop instance, which is in general a subgraph of the causal graph of its associated planning instance P. It is easy to verify that the causal graph is acyclic; a topological ordering is given by {a mathematical formula}a→b→x→u1→u2.
      </paragraph>
      <paragraph>
       We proceed to prove several lemmas regarding loop instances. Although the initial state only explicitly mentions variables {a mathematical formula}u1 and {a mathematical formula}u2, the remaining variables have to be initially false for a loop instance to be solvable. Moreover, the solution always contains a unique subsequence of actions.
      </paragraph>
      <paragraph label="Lemma 2">
       Given a planning instance P with associated loop instance{a mathematical formula}U={a,b,x,u1,u2}, the following holds:
      </paragraph>
      <list>
       <list-item label="1.">
        P is unsolvable unless the variables in{a mathematical formula}{a,b,x}are initially false.
       </list-item>
       <list-item label="2.">
        Any plan solving P contains the subsequence{a mathematical formula}〈u11,b1,a1,x1,b2,u21〉.
       </list-item>
      </list>
      <paragraph label="Proof">
       We first assume that the variables in {a mathematical formula}{a,b,x} are initially false and prove the second part of the lemma. Since {a mathematical formula}u2 is a landmark of P, any plan solving P has to apply action {a mathematical formula}u21 with precondition {a mathematical formula}u1, requiring action {a mathematical formula}u11 to appear before {a mathematical formula}u21. The precondition {a mathematical formula}{b¯,x¯} of {a mathematical formula}u11 is satisfied in the initial state, but to satisfy the precondition x of {a mathematical formula}u21, action {a mathematical formula}x1 has to appear between {a mathematical formula}u11 and {a mathematical formula}u21. The precondition b of {a mathematical formula}x1 requires {a mathematical formula}b1 to appear between {a mathematical formula}u11 and {a mathematical formula}x1, and the precondition {a mathematical formula}b¯ of {a mathematical formula}u21 requires {a mathematical formula}b2 between {a mathematical formula}x1 and {a mathematical formula}u21. Finally, the precondition a of {a mathematical formula}x1 and {a mathematical formula}b2 requires {a mathematical formula}a1 between {a mathematical formula}b1 and {a mathematical formula}x1. Taken together, this results in the unique subsequence {a mathematical formula}〈u11,b1,a1,x1,b2,u21〉.We next show that the variables in {a mathematical formula}{a,b,x} have to be false before applying action {a mathematical formula}u11 for P to be solvable. If a is initially true, there is no action making a false, rendering it impossible to satisfy the precondition {a mathematical formula}a¯ of {a mathematical formula}b1 required to make b true between {a mathematical formula}u11 and {a mathematical formula}x1. If b is initially true, we have to apply action {a mathematical formula}b2 to satisfy the precondition {a mathematical formula}{b¯,x¯} of {a mathematical formula}u11, which in turn requires a to be true. Finally, if x is initially true we have to apply action {a mathematical formula}x2 to satisfy the precondition {a mathematical formula}{b¯,x¯} of {a mathematical formula}u11, which in turn requires b to be true.  □
      </paragraph>
      <paragraph>
       We also show that the values of the variables in the subset {a mathematical formula}{a,b,x} are fixed before action {a mathematical formula}u11 and after action {a mathematical formula}u21.
      </paragraph>
      <paragraph label="Lemma 3">
       No plan solving P can change the value of a variable in the subset{a mathematical formula}{a,b,x}before action{a mathematical formula}u11or after action{a mathematical formula}u21.
      </paragraph>
      <paragraph label="Proof">
       In the proof of Lemma 2 we already showed that the variables in {a mathematical formula}{a,b,x} have to be false before applying action {a mathematical formula}u11, implying that no action can change the value of a variable in {a mathematical formula}{a,b,x} before {a mathematical formula}u11. The action subsequence from Lemma 2 applies action {a mathematical formula}u21 in the partial state {a mathematical formula}{a,b¯,x}, in which no action on {a mathematical formula}{a,b,x} is applicable, making it impossible for any plan to change the value of a variable in {a mathematical formula}{a,b,x} after {a mathematical formula}u21.  □
      </paragraph>
      <paragraph>
       The name “loop instance” derives from the fact that variable x is false before action {a mathematical formula}u11 and true after {a mathematical formula}u21, causing any solution to “iterate” over the two possible values of x. Another direct consequence of Lemma 2 is that the variables in {a mathematical formula}{a,b,x} have to be false in the initial state; we can therefore say that a loop instance U has implicit initial state {a mathematical formula}U¯.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Nested loops on two variables
      </section-title>
      <paragraph>
       In this section we show how to combine loop instances to represent nested loops on two variables. Consider a planning instance {a mathematical formula}P2=〈V,A,I,G〉 with the following components:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}V={a1,b1,x1,u10,u11,u12,u13}∪{a2,b2,x2,u21,u22},
       </list-item>
       <list-item label="•">
        {a mathematical formula}I=V¯,
       </list-item>
       <list-item label="•">
        {a mathematical formula}G={u13}.
       </list-item>
      </list>
      <paragraph>
       Table 1 shows the actions of the planning instance {a mathematical formula}P2. It is easy to verify that {a mathematical formula}U1={a1,b1,x1,u11,u12} is a loop instance: the actions on these variables match those in Fig. 1, {a mathematical formula}u11 and {a mathematical formula}u12 are initially false, and {a mathematical formula}u12 is a precondition of the only action {a mathematical formula}u131 that adds the goal {a mathematical formula}u13. For clarity, we have separated the partial preconditions of actions {a mathematical formula}u111 and {a mathematical formula}u121 that match those in Fig. 1.
      </paragraph>
      <paragraph>
       The subset {a mathematical formula}U2={a2,b2,x2,u21,u22} is also similar to a loop instance, but if we compare to Fig. 1, {a mathematical formula}P2 has three additional actions {a mathematical formula}a22, {a mathematical formula}u212, and {a mathematical formula}u222, each with precondition {a mathematical formula}b1 and making the corresponding variable false. We refer to {a mathematical formula}U2 as a conditional loop instance: whenever {a mathematical formula}b1 is false, the actions on {a mathematical formula}U2 are exactly those of a loop instance, but when {a mathematical formula}b1 is true, the properties of a loop instance no longer hold.
      </paragraph>
      <paragraph label="Definition 4">
       Given a planning instance {a mathematical formula}P=〈V,A,I,G〉, a conditional loop instance{a mathematical formula}U={a,b,x,u1,u2} is a loop instance with three additional actions {a mathematical formula}a2=〈{v},{a¯}〉, {a mathematical formula}u12=〈{v},{u¯1}〉, and {a mathematical formula}u22=〈{v},{u¯2}〉, where {a mathematical formula}v∉U. We say that U is conditional on v and activated whenever v is false.
      </paragraph>
      <paragraph>
       A secondary function of loop instances is to activate and deactivate other, conditional, loop instances. For example, the loop instance {a mathematical formula}U1 of {a mathematical formula}P2 regulates the conditional loop instance {a mathematical formula}U2 by means of the variable {a mathematical formula}b1. Lemma 3 implies that {a mathematical formula}b1 is false before action {a mathematical formula}u111 and after action {a mathematical formula}u121; as a consequence, conditional loop instance {a mathematical formula}U2 is activated at those portions of the plan.
      </paragraph>
      <paragraph>
       Let us study the structure of a plan for {a mathematical formula}P2. Due to Lemma 2 and the fact that {a mathematical formula}U1 is a loop instance, any plan for {a mathematical formula}P2 contains the subsequence {a mathematical formula}〈u111,b11,a11,x11,b12,u121〉. The precondition {a mathematical formula}u10 of {a mathematical formula}u111 requires action {a mathematical formula}u101 to appear before {a mathematical formula}u111, and action {a mathematical formula}u131, needed to achieve the goal {a mathematical formula}u13, has to appear after {a mathematical formula}u121 because of its precondition {a mathematical formula}u12.
      </paragraph>
      <paragraph>
       As a consequence, any plan solving {a mathematical formula}P2 contains the action subsequence {a mathematical formula}〈u101,u111,b11,a11,x11,b12,u121,u131〉. Actions {a mathematical formula}u101 and {a mathematical formula}u121 both have precondition {a mathematical formula}{u¯21,u¯22}, and {a mathematical formula}u111 and {a mathematical formula}u131 have precondition {a mathematical formula}{u22}. As previously mentioned, Lemma 3 implies that {a mathematical formula}b1 is false before {a mathematical formula}u111 and after {a mathematical formula}u121, causing the conditional loop instance {a mathematical formula}U2 to be activated.
      </paragraph>
      <paragraph>
       To apply the two pairs of actions {a mathematical formula}(u101,u111) and {a mathematical formula}(u121,u131), we have to make {a mathematical formula}u22 true starting from {a mathematical formula}{u¯21,u¯22} while {a mathematical formula}U2 is activated. This corresponds to a partial planning instance {a mathematical formula}P2′=〈U2,A(U2),U¯2,{u22}〉 with associated loop instance {a mathematical formula}U2, where {a mathematical formula}U¯2 is the implicit initial state required for {a mathematical formula}P2′ to be solvable. Lemma 2 implies that any plan solving {a mathematical formula}P2′ contains the subsequence {a mathematical formula}ω2=〈u211,b21,a21,x21,b22,u221〉. In a plan solving the original instance {a mathematical formula}P2, {a mathematical formula}ω2 has to be appended between {a mathematical formula}u101 and {a mathematical formula}u111, and between {a mathematical formula}u121 and {a mathematical formula}u131.
      </paragraph>
      <paragraph>
       When we apply action {a mathematical formula}u111, the partial state on {a mathematical formula}U2 is {a mathematical formula}{a2,b¯2,x2,u21,u22}. Prior to applying action {a mathematical formula}u121, we have to reset the variables in {a mathematical formula}U2 to false to achieve the implicit initial state {a mathematical formula}U¯2 of {a mathematical formula}P2′. When {a mathematical formula}b1 is true, the action sequence {a mathematical formula}ρ2=〈a22,b21,x22,a21,b22,a22,u212,u222〉 first resets the variables in {a mathematical formula}{a2,b2,x2} to false, and then variables {a mathematical formula}u21 and {a mathematical formula}u22.
      </paragraph>
      <paragraph>
       Summarizing, a plan for {a mathematical formula}P2 is of the form{a mathematical formula} Some actions can change places, but {a mathematical formula}ω2 has to appear between {a mathematical formula}u101 and {a mathematical formula}u111 and between {a mathematical formula}u121 and {a mathematical formula}u131. Likewise, {a mathematical formula}ρ2 has to appear between {a mathematical formula}b11 and {a mathematical formula}b12 (where {a mathematical formula}b1 is true). A plan for {a mathematical formula}P2 describes a nested loop on {a mathematical formula}x1 and {a mathematical formula}x2: variable {a mathematical formula}x1 is false before {a mathematical formula}u111 and true after {a mathematical formula}u121 and, for each of the two values on {a mathematical formula}x1, variable {a mathematical formula}x2 is false before {a mathematical formula}u211 and true after {a mathematical formula}u221 in the subsequence {a mathematical formula}ω2.
      </paragraph>
      <paragraph>
       Note that if variables {a mathematical formula}u10,…,u13 are initially false, all other variables in V have to be false for {a mathematical formula}P2 to be solvable. Since {a mathematical formula}U1 is a loop instance, the variables in {a mathematical formula}{a1,b1,x1} have to be initially false due to Lemma 2. Since {a mathematical formula}b1 is false before action {a mathematical formula}u111, conditional loop instance {a mathematical formula}U2 is activated, and to apply the action pair {a mathematical formula}(u101,u111) we have to solve the partial planning instance {a mathematical formula}P2′ with implicit initial state {a mathematical formula}U¯2.
      </paragraph>
      <paragraph>
       Fig. 2 shows the causal graph of the planning instance {a mathematical formula}P2. The subgraphs on {a mathematical formula}U1 and {a mathematical formula}U2 are those of a loop instance. There are edges from {a mathematical formula}b1 to {a mathematical formula}a2, {a mathematical formula}u21, and {a mathematical formula}u22 due to {a mathematical formula}U2 being a loop instance conditional on {a mathematical formula}b1, and edges from {a mathematical formula}u21 and {a mathematical formula}u22 to {a mathematical formula}u10,…,u13 due to actions {a mathematical formula}u101,…,u131. By stacking {a mathematical formula}a1,b1,x1 at the top and {a mathematical formula}u10,…,u13 at the bottom, a topological ordering is given by scanning variables left-to-right in each row, starting from the top.
      </paragraph>
     </section>
     <section label="3.3">
      Nested loops on n variables
      <paragraph>
       We next show how to extend the idea from the previous section to simulate nested loops on any number n of variables. Consider a planning instance {a mathematical formula}Pn=〈V,A,I,G〉 with the following components:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}V=⋃i=1n(Xi∪Vi),
       </list-item>
       <list-item label="•">
        {a mathematical formula}Xi={ai,bi,xi} for each {a mathematical formula}1⩽i⩽n,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Vi={ui0,ui1,ui2,ui3} for each {a mathematical formula}1⩽i⩽n,
       </list-item>
       <list-item label="•">
        {a mathematical formula}I=V¯,
       </list-item>
       <list-item label="•">
        {a mathematical formula}G={u13}.
       </list-item>
      </list>
      <paragraph>
       Table 2 shows the actions of the planning instance {a mathematical formula}Pn for {a mathematical formula}1&lt;i⩽n and {a mathematical formula}0⩽k⩽3. For each {a mathematical formula}1⩽i⩽n, let {a mathematical formula}Ui={ai,bi,xi,ui1,ui2}, let {a mathematical formula}Ai⊆A be the subset of actions on variables in {a mathematical formula}Xi, and let {a mathematical formula}Bi⊆A be the actions on {a mathematical formula}Vi. The actions are defined such that {a mathematical formula}U1 is a loop instance and, for each {a mathematical formula}1&lt;i⩽n, {a mathematical formula}Ui is a loop instance conditional on {a mathematical formula}bi−1.
      </paragraph>
      <paragraph>
       Compared to the planning instance {a mathematical formula}P2 from the previous section, the set {a mathematical formula}Vi, {a mathematical formula}1&lt;i⩽n, contains additional variables {a mathematical formula}ui0 and {a mathematical formula}ui3 with associated actions in {a mathematical formula}Bi. Consequently, actions {a mathematical formula}u(i−1)01 and {a mathematical formula}u(i−1)21 have partial precondition {a mathematical formula}{u¯i0,u¯i1,u¯i2,u¯i3}, and actions {a mathematical formula}u(i−1)11 and {a mathematical formula}u(i−1)31 have partial precondition {a mathematical formula}{ui3}. These extra variables are not strictly needed for {a mathematical formula}i=n but including them makes action definitions uniform (and hence more compact).
      </paragraph>
      <paragraph>
       For each {a mathematical formula}1⩽i⩽n, define a partial planning instance {a mathematical formula}Pi′=〈Vi′,Ai′,Ii′,Gi′〉 with components
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Vi′=⋃j=in(Xj∪Vj),
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ai′=⋃j=in(Aj∪Bj)∖⋃j=2i{aj2,uj12,uj22},
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ii′=V¯i′,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Gi′={ui3}.
       </list-item>
      </list>
      <paragraph label="Lemma 5">
       For each{a mathematical formula}1⩽i⩽n, any solution to{a mathematical formula}Pi′iterates over all possible assignments to variables{a mathematical formula}xi,…,xn.
      </paragraph>
      <paragraph label="Proof">
       With {a mathematical formula}{ai2,ui12,ui22} removed, the actions of {a mathematical formula}Ui are exactly those of a loop instance. Variable {a mathematical formula}ui2 is a precondition of the only action {a mathematical formula}ui31 that achieves the goal {a mathematical formula}ui3, and {a mathematical formula}ui1 and {a mathematical formula}ui2 are initially false. Lemma 2 states that any plan solving {a mathematical formula}Pi′ contains the action subsequence {a mathematical formula}〈ui11,bi1,ai1,xi1,bi2,ui21〉.We now prove the lemma by induction on i. For {a mathematical formula}i=n, since {a mathematical formula}Un is a loop instance for {a mathematical formula}Pn′, any plan solving {a mathematical formula}Pn′ iterates over the two possible values of {a mathematical formula}xn. For {a mathematical formula}i&lt;n, because of the way actions are defined, {a mathematical formula}ui01 has to appear before {a mathematical formula}ui11, and {a mathematical formula}ui31 has to appear after {a mathematical formula}ui21. The action pairs {a mathematical formula}(ui01,ui11) and {a mathematical formula}(ui21,ui31) each requires achieving {a mathematical formula}u(i+1)3 starting from {a mathematical formula}{u¯(i+1)0,u¯(i+1)1,u¯(i+1)2,u¯(i+1)3}. Due to Lemma 3, variable {a mathematical formula}bi is false while doing so, causing conditional loop instance {a mathematical formula}Ui+1 to be activated. This corresponds to solving the partial planning problem {a mathematical formula}Pi+1′, which has implicit initial state {a mathematical formula}V¯i+1′ since variables in {a mathematical formula}{ai+1,bi+1,xi+1} have to be false for {a mathematical formula}Pi+1′ to be solvable due to Lemma 2 and, if {a mathematical formula}i+1&lt;n, we recursively have to satisfy the implicit initial state {a mathematical formula}V¯i+2′ of {a mathematical formula}Pi+2′ to apply the action pair {a mathematical formula}(u(i+1)01,u(i+1)11) while {a mathematical formula}bi+1 is false.Let {a mathematical formula}ωi+1 be a plan solving {a mathematical formula}Pi+1′. By hypothesis of induction, {a mathematical formula}ωi+1 iterates over all possible values to variables {a mathematical formula}xi+1,…,xn. A plan for {a mathematical formula}Pi′ is given by{a mathematical formula} where {a mathematical formula}ρi+1 is an action sequence resetting the variables in {a mathematical formula}Vi+1′ to false. Since {a mathematical formula}ωi+1 appears before {a mathematical formula}ui11 and after {a mathematical formula}ui21, this plan iterates over all possible assignments to variables {a mathematical formula}xi+1,…,xn, first for {a mathematical formula}xi false, then for {a mathematical formula}xi true. This corresponds exactly to iterating over all assignments to {a mathematical formula}xi,…,xn.  □
      </paragraph>
      <paragraph>
       We omit the causal graph of {a mathematical formula}Pn, which has the same structure as the causal graph of {a mathematical formula}P2: a topological ordering is given by{a mathematical formula} It is possible to verify that no action on a variable v has a precondition on a variable u appearing after v in this ordering.
      </paragraph>
     </section>
     <section label="3.4">
      Case study: reducing Unsat to Pe(Acyc)
      <paragraph>
       In this section, we show how to use loop instances to reduce the decision problem Unsat to Pe(Acyc). Prior to our work, it was not known how to do this, not even for Sas{sup:+} planning. Using loop instances, the reduction is almost trivial.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}ϕ=(c1∧⋯∧cm) be a 3SAT formula on n variables {a mathematical formula}x1,…,xn where, for each {a mathematical formula}1⩽j⩽m, {a mathematical formula}cj=ℓj1∨ℓj2∨ℓj3 is a 3-literal clause on {a mathematical formula}x1,…,xn. The decision problem Unsat consists in determining whether or not ϕ is unsatisfied for all assignments to {a mathematical formula}x1,…,xn.
      </paragraph>
      <paragraph>
       Given ϕ, we construct (in polynomial time) a planning instance in Acyc by modifying the planning instance {a mathematical formula}Pn from the previous section. The only modification is replacing actions {a mathematical formula}un11 and {a mathematical formula}un21 with m actions each, corresponding to the clauses {a mathematical formula}c1,…,cm of ϕ. For each {a mathematical formula}1⩽j⩽m, the actions {a mathematical formula}un1j and {a mathematical formula}un2j associated with {a mathematical formula}cj have additional precondition {a mathematical formula}{ℓ¯j1,ℓ¯j2,ℓ¯j3} where, for each {a mathematical formula}1⩽k⩽3, {a mathematical formula}ℓ¯jk=x¯i if {a mathematical formula}ℓjk=xi for some variable {a mathematical formula}xi, and {a mathematical formula}ℓ¯jk=xi if {a mathematical formula}ℓjk=x¯i. Technically, a loop instance on {a mathematical formula}Un should only have one action {a mathematical formula}un11 and one action {a mathematical formula}un21, but {a mathematical formula}Un still shares all the properties of a loop instance since each of the new actions has the same precondition as the original {a mathematical formula}un11 or {a mathematical formula}un21.
      </paragraph>
      <paragraph label="Lemma 6">
       The modified planning instance{a mathematical formula}Pnhas a solution if and only if ϕ is unsatisfiable.
      </paragraph>
      <paragraph label="Proof">
       Lemma 5 states that a plan solving {a mathematical formula}Pn iterates over all possible assignments to variables {a mathematical formula}x1,…,xn. Since the innermost loop is over {a mathematical formula}xn, for each such assignment we have to apply one of the actions {a mathematical formula}un1j or {a mathematical formula}un2j. If ϕ is unsatisfied, for each assignment to {a mathematical formula}x1,…,xn there exists an unsatisfied clause {a mathematical formula}cj, making {a mathematical formula}un1j or {a mathematical formula}un2j applicable. On the other hand, if there exists an assignment to {a mathematical formula}x1,…,xn that satisfies ϕ, none of the actions {a mathematical formula}un1j or {a mathematical formula}un2j are applicable, breaking the chain and rendering {a mathematical formula}Pn unsolvable.  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      The complexity of planning for Acyc
     </section-title>
     <paragraph>
      In this section we show that the decision problem Pe(Acyc) is PSPACE-complete by reduction from Qbf-Sat. The reduction makes heavy use of the loop instances introduced in the previous section. We first introduce the decision problem Qbf-Sat and describe a general strategy for solving it. We then show how to construct a planning instance in Acyc that simulates this strategy, and finally prove that the reduction is correct. At the end of the section we present an encoding of the reduction in PDDL.
     </paragraph>
     <section label="4.1">
      The decision problem Qbf-Sat
      <paragraph>
       A quantified Boolean formula, or QBF, is a conjunction of clauses such that the variables are bound by quantifiers, either existential or universal. The decision problem Qbf-Sat is to determine whether a given QBF F is satisfiable, and is known to be PSPACE-complete [13], even when F is in prenex normal form, i.e. the quantifiers alternate between existential and universal. Although the reduction from Qbf-Sat to Pe(Acyc) can be implemented for any QBF, the resulting planning instance in Acyc is significantly simpler when the QBF is in prenex normal form.
      </paragraph>
      <paragraph>
       A QBF in prenex normal form is a formula {a mathematical formula}F=∀x1∃x2⋯∀xn−1∃xn.ϕ, where n is an even integer, {a mathematical formula}ϕ=(c1∧⋯∧cm) is a 3SAT formula, and {a mathematical formula}cj=ℓj1∨ℓj2∨ℓj3 is a 3-literal clause for each {a mathematical formula}1⩽j⩽m. In what follows we describe a general algorithm for determining whether F is satisfiable.
      </paragraph>
      <paragraph>
       For each {a mathematical formula}1⩽i⩽n, let {a mathematical formula}pi be a partial state representing an assignment to the variables {a mathematical formula}x1,…,xi−1. Let {a mathematical formula}Fi(pi)=Qixi⋯∀xn−1∃xn.ϕ(pi) denote the partial QBF obtained from F by removing the quantifiers on {a mathematical formula}x1,…,xi−1 and replacing {a mathematical formula}x1,…,xi−1 in ϕ with the respective truth values in {a mathematical formula}pi. Fig. 3 describes a recursive algorithm QSat that checks whether {a mathematical formula}Fi(pi) is satisfiable for any arbitrary {a mathematical formula}1⩽i⩽n and {a mathematical formula}pi. The algorithm {a mathematical formula}Check(pn+1) returns true if and only if the 3SAT formula ϕ is satisfied by the assignment {a mathematical formula}pn+1. Note that {a mathematical formula}F1(p1)=F1(∅)=F, so the following lemma implies that F is satisfiable if and only if QSat{a mathematical formula}(1,∅) returns true. We remark that QSat is a well-known solution to the decision problem Qbf-Sat.
      </paragraph>
      <paragraph label="Lemma 7">
       The algorithm QSat runs in polynomial space on input{a mathematical formula}(i,pi)and returns true if and only if{a mathematical formula}Fi(pi)is satisfiable.
      </paragraph>
      <paragraph label="Proof">
       The recursive algorithm QSat essentially performs a nested loop on the variables {a mathematical formula}xi,…,xn with the body in the inner loop described by a call to Check. The proof follows directly from the meaning of each quantifier. If {a mathematical formula}i=n, the quantifier on {a mathematical formula}xi is existential, and {a mathematical formula}Fn(pn) is satisfiable if and only if ϕ is satisfiable for either of the assignments {a mathematical formula}pn∪{x¯n} or {a mathematical formula}pn∪{xn}. If i is odd, {a mathematical formula}xi is universal, so {a mathematical formula}Fi(pi) is satisfiable if and only if {a mathematical formula}Fi+1(pi∪{xi¯})and{a mathematical formula}Fi+1(pi∪{xi}) are satisfiable. Otherwise {a mathematical formula}xi is existential, so {a mathematical formula}Fi(pi) is satisfiable if and only if {a mathematical formula}Fi+1(pi∪{xi¯})or{a mathematical formula}Fi+1(pi∪{xi}) is satisfiable.By sharing the memory needed to store {a mathematical formula}pn+1 (which requires {a mathematical formula}O(n) space), each recursive call only needs {a mathematical formula}O(logi)=O(logn) memory to represent i, and a single bit of memory to remember the outcome of Check or QSat for {a mathematical formula}pi∪xi¯. Checking whether an assignment {a mathematical formula}pn+1 satisfies ϕ requires {a mathematical formula}O(n+m) space where m is the number of clauses, and the recursive calls require a total of {a mathematical formula}O(nlogn) space since there are never more than n such calls on the stack. Thus QSat runs in {a mathematical formula}O(nlogn+m) space, which is polynomial in F.  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Construction
      </section-title>
      <paragraph>
       In this section we show how to reduce the decision problem Qbf-Sat to Pe(Acyc). Specifically, for any QBF F in prenex normal form, we construct a planning instance in Acyc that is solvable if and only if F is satisfiable.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}F=∀x1∃x2⋯∀xn−1∃xn.ϕ be the QBF in prenex normal form with {a mathematical formula}ϕ=(c1∧⋯∧cm) and {a mathematical formula}cj=ℓj1∨ℓj2∨ℓj3 for each {a mathematical formula}1⩽j⩽m. Given F, we construct a planning instance {a mathematical formula}PF=〈VF,AF,IF,GF〉 where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}VF=⋃i=1n(Xi∪Vi)∪S,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Xi={ai,bi,xi} for each {a mathematical formula}1⩽i⩽n,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Vi={ui0,ui1,ui2,ui3,vi1,vi2,vi3} for each {a mathematical formula}1⩽i⩽n,
       </list-item>
       <list-item label="•">
        {a mathematical formula}S={s1,…,sm,t},
       </list-item>
       <list-item label="•">
        {a mathematical formula}AF=⋃i=1n(Ai∪Bi)∪AS,
       </list-item>
       <list-item label="•">
        {a mathematical formula}IF=V¯F,
       </list-item>
       <list-item label="•">
        {a mathematical formula}GF={u13}.
       </list-item>
      </list>
      <paragraph>
       For each {a mathematical formula}1⩽i⩽n, the set of actions {a mathematical formula}Ai on {a mathematical formula}Xi={ai,bi,xi} are exactly those of the planning instance {a mathematical formula}Pn from the previous section.
      </paragraph>
      <paragraph>
       However, if we compare to {a mathematical formula}Pn, {a mathematical formula}Vi contains additional variables {a mathematical formula}vi1,vi2,vi3. To implement the algorithm QSat in Fig. 3, we need to remember whether or not the partial QBF {a mathematical formula}Fi(pi) is satisfiable. The variables in {a mathematical formula}Vi constitute a simple memory for doing so. As a consequence, we cannot immediately apply the results regarding loop instances from the previous section.
      </paragraph>
      <paragraph>
       The purpose of the variables in the set S is to implement the subroutine Check, i.e. to verify whether the 3SAT formula ϕ is satisfied given the current assignment {a mathematical formula}pn+1 to the variables {a mathematical formula}x1,…,xn. Table 3 shows the actions in the associated set {a mathematical formula}AS, with the precondition {a mathematical formula}sj−1 of actions {a mathematical formula}sj1, {a mathematical formula}sj2, and {a mathematical formula}sj3 omitted for {a mathematical formula}j=1. For each {a mathematical formula}1⩽j⩽m, literals {a mathematical formula}ℓj1, {a mathematical formula}ℓj2, and {a mathematical formula}ℓj3 should be replaced with the corresponding variable among {a mathematical formula}x1,…,xn, appropriately negated.
      </paragraph>
      <paragraph>
       The actions in {a mathematical formula}AS are defined such that starting from {a mathematical formula}S¯, we can make {a mathematical formula}sm true if and only if ϕ is satisfied, and t true if and only if ϕ is unsatisfied. To make t true, it is sufficient to find a clause {a mathematical formula}cj that is unsatisfied by the current assignment to {a mathematical formula}x1,…,xn, and apply the associated action {a mathematical formula}tj. To make {a mathematical formula}sm true, we have to verify that each clause is satisfied by the current assignment to {a mathematical formula}x1,…,xn. This is the reason why actions {a mathematical formula}sj1, {a mathematical formula}sj2, and {a mathematical formula}sj3 have precondition {a mathematical formula}sj−1. The purpose of actions {a mathematical formula}sj4, {a mathematical formula}1⩽j⩽m, and {a mathematical formula}tm+1 is to reset the variables in S to false when {a mathematical formula}bn is true.
      </paragraph>
      <paragraph>
       Table 4 shows the actions in the set {a mathematical formula}B1∪⋯∪Bn for {a mathematical formula}1⩽i&lt;n and {a mathematical formula}0⩽k⩽3. For each {a mathematical formula}1⩽i⩽n, the two subsets {a mathematical formula}Ui1={ai,bi,xi,ui1,ui2} and {a mathematical formula}Ui2={ai,bi,xi,vi1,vi2} are similar to loop instances, conditional on {a mathematical formula}bi−1 for {a mathematical formula}i&gt;1, but {a mathematical formula}ui2 and {a mathematical formula}vi2 are not always landmarks, violating the definition of loop instances. In these cases, {a mathematical formula}{ui2,vi2} is a disjunctive landmark, implying that any plan has to use one of {a mathematical formula}Ui1 and {a mathematical formula}Ui2 to achieve the goal.
      </paragraph>
      <paragraph>
       For {a mathematical formula}1⩽i⩽n, let {a mathematical formula}pi be an assignment to {a mathematical formula}x1,…,xi−1. We define a partial planning instance {a mathematical formula}Pi1′(pi)=〈Vi′,Ai′,Ii′,{ui3}〉 as follows:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Vi′=Zi′∪{x1,…,xi−1},
       </list-item>
       <list-item label="•">
        {a mathematical formula}Zi′=⋃j=in(Xj∪Vj)∪S,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ai′=⋃j=in(Aj∪Bj)∪AS∖⋃j=2i{aj2,uj14,uj24,vj14,vj24},
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ii′=Z¯i′∪pi.
       </list-item>
      </list>
      <paragraph>
       Note that variables {a mathematical formula}x1,…,xi−1 are static in {a mathematical formula}Pi1′(pi) and initialized to {a mathematical formula}pi. Actions in {a mathematical formula}AS may have preconditions on {a mathematical formula}x1,…,xi−1, which is the purpose of including these variables. We define another partial planning instance {a mathematical formula}Pi2′(pi) identical to {a mathematical formula}Pi1′(pi) except the goal is {a mathematical formula}vi3 instead of {a mathematical formula}ui3.
      </paragraph>
      <paragraph>
       For each {a mathematical formula}1⩽i⩽n, the partial planning instance {a mathematical formula}Pi1′(pi) has associated loop instance {a mathematical formula}Ui1 since {a mathematical formula}ui1 and {a mathematical formula}ui2 are initially false and {a mathematical formula}ui2 is a precondition of the only action {a mathematical formula}ui31 that adds the goal {a mathematical formula}ui3. However, if we instead consider {a mathematical formula}Pi2′(pi), there are three actions that add the goal {a mathematical formula}vi3, namely {a mathematical formula}vi31 with precondition {a mathematical formula}ui2 and {a mathematical formula}vi32, {a mathematical formula}vi33 with precondition {a mathematical formula}vi2. In other words, neither {a mathematical formula}ui2 nor {a mathematical formula}vi2 is a landmark for {a mathematical formula}Pi2′(pi), but rather {a mathematical formula}{ui2,vi2} is a disjunctive landmark.
      </paragraph>
      <paragraph>
       For each {a mathematical formula}1⩽i⩽n and each assignment {a mathematical formula}pi, the actions are defined such that exactly one of {a mathematical formula}Pi1′(pi) and {a mathematical formula}Pi2′(pi) is solvable. Which of the two instances is solvable depends on the partial QBF {a mathematical formula}Fi(pi) and the parity of i. If i is odd, {a mathematical formula}xi is universal, in which case {a mathematical formula}Pi1′(pi) is solvable if and only if {a mathematical formula}Fi(pi) is satisfiable and {a mathematical formula}Pi2′(pi) is solvable if and only if {a mathematical formula}Fi(pi) is unsatisfiable. Conversely, if i is even, {a mathematical formula}xi is existential, in which case {a mathematical formula}Pi2′(pi) is solvable if and only if {a mathematical formula}Fi(pi) is satisfiable and {a mathematical formula}Pi1′(pi) is solvable if and only if {a mathematical formula}Fi(pi) is unsatisfiable. Since {a mathematical formula}P11′(p1)=P11′(∅)=PF and {a mathematical formula}i=1 is odd, this implies that {a mathematical formula}PF is solvable if and only if the QBF {a mathematical formula}F1(p1)=F1(∅)=F is satisfiable.
      </paragraph>
      <paragraph>
       Fig. 4 shows the causal graph of the planning instance {a mathematical formula}PF. To avoid cluttering, many vertical edges have been omitted, but it is easy to verify that each edge is either left-to-right within the same row of variables, or top-to-bottom between rows of variables, implying that the causal graph is acyclic. All edges induced by the actions for {a mathematical formula}Xi are already present. For S, the edges not shown are those associated with the literals of each clause, i.e. each edge is from a variable among {a mathematical formula}x1,…,xn to either {a mathematical formula}sj or t. The edges to {a mathematical formula}Vi not shown are from {a mathematical formula}bi−1 (for {a mathematical formula}i&gt;1), {a mathematical formula}bi, {a mathematical formula}xi, and {a mathematical formula}Vi+1 or, in the case of {a mathematical formula}i=n, from S. Variables {a mathematical formula}v11, {a mathematical formula}v12, {a mathematical formula}v13 do not appear since they are irrelevant.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Proof of correctness
      </section-title>
      <paragraph>
       In this section we prove that the reduction is correct, i.e. that the planning instance {a mathematical formula}PF constructed in the previous section has a solution if and only if the QBF F is satisfiable. We first prove that the variables in S and actions in {a mathematical formula}AS correspond to the algorithm Check that tests whether the formula ϕ is satisfied given the current assignment {a mathematical formula}pn+1 to {a mathematical formula}x1,…,xn.
      </paragraph>
      <paragraph label="Lemma 8">
       Given an assignment{a mathematical formula}pn+1, starting from{a mathematical formula}S¯it is possible to set{a mathematical formula}smto true if and only if ϕ is satisfied, and t to true if and only if ϕ is unsatisfied.
      </paragraph>
      <paragraph label="Proof">
       We show by induction on {a mathematical formula}1⩽j⩽m that we can set {a mathematical formula}sj to true if and only if clauses {a mathematical formula}c1,…,cj are satisfied, and t to true if and only if at least one of these clauses is unsatisfied. For {a mathematical formula}j=1, if {a mathematical formula}c1 is satisfied, at least one action among {a mathematical formula}s11, {a mathematical formula}s12, {a mathematical formula}s13 is applicable, but not {a mathematical formula}t1, making it possible to set {a mathematical formula}s1 to true, but not t. If {a mathematical formula}c1 is unsatisfied, action {a mathematical formula}t1 is applicable, but not {a mathematical formula}s11, {a mathematical formula}s12, {a mathematical formula}s13, making it possible to set t to true, but not {a mathematical formula}s1.For {a mathematical formula}j&gt;1, if at least one clause among {a mathematical formula}c1,…,cj−1 is unsatisfied, by hypothesis of induction we can set t to true but not {a mathematical formula}sj−1. Then no action among {a mathematical formula}sj1, {a mathematical formula}sj2, {a mathematical formula}sj3 is applicable, making it impossible to set {a mathematical formula}sj to true. If, on the contrary, clauses {a mathematical formula}c1,…,cj−1 are satisfied, we can set {a mathematical formula}sj−1 to true but not t. Then if {a mathematical formula}cj is satisfied, at least one action among {a mathematical formula}sj1, {a mathematical formula}sj2, {a mathematical formula}sj3 is applicable, but not {a mathematical formula}tj, making it possible to set {a mathematical formula}sj to true, but not t. If {a mathematical formula}cj is unsatisfied, action {a mathematical formula}tj is applicable, but not {a mathematical formula}sj1, {a mathematical formula}sj2, {a mathematical formula}sj3, making it possible to set t to true, but not {a mathematical formula}sj.  □
      </paragraph>
      <paragraph>
       We next prove that, given some assignment {a mathematical formula}pi to the variables {a mathematical formula}x1,…,xi−1, which of {a mathematical formula}Pi1′(pi) and {a mathematical formula}Pi2′(pi) is solvable tells us whether or not {a mathematical formula}Fi(pi) is satisfiable, effectively simulating the algorithm QSat in Table 3.
      </paragraph>
      <paragraph label="Lemma 9">
       For each{a mathematical formula}1⩽i⩽n, let{a mathematical formula}pibe an assignment to{a mathematical formula}x1,…,xi−1. The instance{a mathematical formula}Pi1′(pi)is solvable if and only if i is odd and{a mathematical formula}Fi(pi)satisfiable, or i is even and{a mathematical formula}Fi(pi)unsatisfiable. The instance{a mathematical formula}Pi2′(pi)is solvable if and only if i is odd and{a mathematical formula}Fi(pi)unsatisfiable, or i is even and{a mathematical formula}Fi(pi)satisfiable.
      </paragraph>
      <paragraph label="Proof">
       By induction on {a mathematical formula}1⩽i⩽n. For {a mathematical formula}i=n, to solve {a mathematical formula}Pn1′(pi) we have to apply the action subsequence {a mathematical formula}〈un01,un11,un21,un31〉. Actions {a mathematical formula}un01 and {a mathematical formula}un21 have precondition {a mathematical formula}S¯, and actions {a mathematical formula}un11 and {a mathematical formula}un31 have precondition t. Moreover, {a mathematical formula}Un1 is a loop instance for {a mathematical formula}Pn1′(pi). We thus have to make t true starting from {a mathematical formula}S¯ for {a mathematical formula}xn false and {a mathematical formula}xn true given the assignment {a mathematical formula}pn. Due to Lemma 8, this is possible if and only if ϕ is unsatisfied for {a mathematical formula}pn∪{x¯n} and {a mathematical formula}pn∪{xn}. Since n is even, and hence {a mathematical formula}xn existential, this corresponds to {a mathematical formula}Fn(pn) being unsatisfied.On the other hand, to solve {a mathematical formula}Pi2′(pi) we have to apply one of the three following action subsequences, with associated precondition sequences:{a mathematical formula}{a mathematical formula}{a mathematical formula} The subset {a mathematical formula}Un1 is a loop instance of the former, while {a mathematical formula}Un2 is a loop instance of the two latter, implying that {a mathematical formula}xn is false before {a mathematical formula}un11/vn11 and true after {a mathematical formula}un21/vn21.The three sequences of preconditions are mutually exclusive since we can only make one of {a mathematical formula}sm and t true starting from {a mathematical formula}S¯. In all three cases, we have to make {a mathematical formula}sm true starting from {a mathematical formula}S¯ for either {a mathematical formula}pn∪{x¯n} or {a mathematical formula}pn∪{xn}, which corresponds to {a mathematical formula}Fn(pn) being satisfied since {a mathematical formula}xn is existential.For {a mathematical formula}1⩽i&lt;n, the reasoning is similar. To solve {a mathematical formula}Pi1′(pi) we have to make {a mathematical formula}v(i+1)3 true starting from {a mathematical formula}V¯i+1 for {a mathematical formula}pi∪{x¯i} and {a mathematical formula}pi∪{xi}, which corresponds to solving the instances {a mathematical formula}P(i+1)2′(pi∪{x¯i}) and {a mathematical formula}P(i+1)2′(pi∪{xi}). If i is odd, the induction hypothesis states that {a mathematical formula}Fi+1(pi∪{x¯i}) and {a mathematical formula}Fi+1(pi∪{xi}) are satisfiable, implying that {a mathematical formula}Fi(pi) is satisfiable since {a mathematical formula}xi is universal. If i is even, {a mathematical formula}Fi+1(pi∪{x¯i}) and {a mathematical formula}Fi+1(pi∪{xi}) are unsatisfiable, implying that {a mathematical formula}Fi(pi) is unsatisfiable since {a mathematical formula}xi is existential.Conversely, to solve {a mathematical formula}Pi2′(pi) we have to make {a mathematical formula}u(i+1)3 true starting from {a mathematical formula}V¯i+1 for either {a mathematical formula}pi∪{x¯i} or {a mathematical formula}pi∪{xi}, which corresponds to solving the instance {a mathematical formula}P(i+1)1′(pi∪{x¯i}) or {a mathematical formula}P(i+1)1′(pi∪{xi}). If i is odd, the induction hypothesis states that {a mathematical formula}Fi+1(pi∪{x¯i}) or {a mathematical formula}Fi+1(pi∪{xi}) is unsatisfiable, implying that {a mathematical formula}Fi(pi) is unsatisfiable since {a mathematical formula}xi is universal. If i is even, {a mathematical formula}Fi+1(pi∪{x¯i}) or {a mathematical formula}Fi+1(pi∪{xi}) is satisfiable, implying that {a mathematical formula}Fi(pi) is satisfiable since {a mathematical formula}xi is existential.  □
      </paragraph>
      <paragraph>
       We are now ready to prove the main result of this section.
      </paragraph>
      <paragraph label="Theorem 1">
       Pe(Acyc) is PSPACE-complete.
      </paragraph>
      <paragraph label="Proof">
       Let F be an arbitrary QBF on n variables and m clauses in prenex normal form. We can construct the planning instance {a mathematical formula}PF in polynomial time given F. A plan solving {a mathematical formula}PF simulates a nested loop on {a mathematical formula}x1,…,xn. Lemma 9 states that since {a mathematical formula}i=1 is odd, we can solve {a mathematical formula}P11′(p1)=P11′(∅)=PF if and only if the QBF {a mathematical formula}F1(∅)=F is satisfiable.We have presented a polynomial-time reduction from Qbf-Sat, a known PSPACE-complete problem, to Pe(Acyc). Membership in PSPACE follows from Theorem 4 of Bäckström and Nebel [12].  □
      </paragraph>
      <paragraph>
       As an immediate consequence of Theorem 1, bounded plan existence is also PSPACE-complete for the class Acyc.
      </paragraph>
      <paragraph label="Corollary 10">
       Bpe(Acyc) is PSPACE-complete.
      </paragraph>
      <paragraph>
       We remark that for Strips planning instances with acyclic causal graph and positive preconditions, plan existence is in P and bounded plan existence is NP-complete. These results follow from Theorems 3.7 and 4.2 of Bylander [11], who did not mention the causal graph but nevertheless proved results that are valid for acyclic causal graphs.
      </paragraph>
      <paragraph>
       We also prove an upper bound on the length of an optimal plan solving {a mathematical formula}PF, which we later need to prove PSPACE-completeness of Bpe(SC-Acyc).
      </paragraph>
      <paragraph label="Lemma 11">
       An upper bound on the length of an optimal plan solving{a mathematical formula}PFis given by{a mathematical formula}L(m,n)=(2n+1−1)m+18⋅2n−10n−18, where m is the number of clauses of the QBF formula F, and n is the number of variables of F.
      </paragraph>
      <paragraph label="Proof">
       We prove by induction on i that the length of an optimal plan for {a mathematical formula}Pi1′(pi) and {a mathematical formula}Pi2′(pi) is upper bounded by {a mathematical formula}L(m,n+1−i), regardless of the assignment {a mathematical formula}pi. The base case is given by {a mathematical formula}i=n. To solve {a mathematical formula}Pn1′(pn) or {a mathematical formula}Pn2′(pn) we need to apply one of four action subsequences:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The fourth sequence requires first making {a mathematical formula}sm true starting from {a mathematical formula}S¯, then resetting all variables in S to false, then making {a mathematical formula}sm true again, for a total of 3m actions. Since {a mathematical formula}Un2={an,bn,xn,vn1,vn2} is a loop instance for this partial planning instance, we have to insert the action sequence {a mathematical formula}〈bn1,an1,xn1,bn2〉 between actions {a mathematical formula}vn11 and {a mathematical formula}vn21, for a total of {a mathematical formula}3m+8=L(m,1) actions. The remaining three sequences require making t true at some point instead of {a mathematical formula}sm, which needs a single action instead of m actions, making all of them shorter.For {a mathematical formula}i&lt;n, we also need to apply one of four action sequences:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Each of these sequences requires solving {a mathematical formula}P(i+1)1′(pi+1) or {a mathematical formula}P(i+1)2′(pi+1) twice, first for {a mathematical formula}pi+1=pi∪{x¯i}, then for {a mathematical formula}pi+1=pi∪{xi}. Between {a mathematical formula}ui11/vi11 and {a mathematical formula}ui21/vi21 we have to reset all variables in {a mathematical formula}Zi+1′=⋃j=i+1n(Xj∪Vj)∪S to false and insert the action sequence {a mathematical formula}〈bi1,ai1,xi1,bi2〉.By hypothesis of induction, solving {a mathematical formula}P(i+1)1′(pi+1) or {a mathematical formula}P(i+1)2′(pi+1) requires at most {a mathematical formula}L(m,n−i) actions. Resetting all variables in {a mathematical formula}Zi+1′ to false requires at most {a mathematical formula}m+10(n−i) actions: m actions to reset variables in S to false and, for each {a mathematical formula}i&lt;j⩽n, 6 actions to reset variables in {a mathematical formula}Xj to false and 4 actions to reset variables in {a mathematical formula}Vj to false. The number of actions is upper bounded by{a mathematical formula} Since {a mathematical formula}P11′(p1)=P11′(∅)=PF, an optimal plan for {a mathematical formula}PF is upper bounded by {a mathematical formula}L(m,n+1−1)=L(m,n).  □
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       PDDL encoding
      </section-title>
      <paragraph>
       In this section we show how to encode two planning domains in PDDL: a planning domain containing instances of type {a mathematical formula}Pn from Section 3, simulating nested loops on n variables, and a planning domain containing instances of type {a mathematical formula}PF, encoding instances of Qbf-Sat as planning instances.
      </paragraph>
      <paragraph>
       To implement a planning domain simulating nested loops, we define a single type {a mathematical formula}index as well as predicates {a mathematical formula}a, {a mathematical formula}b, {a mathematical formula}x, {a mathematical formula}u0, {a mathematical formula}u1, {a mathematical formula}u2, and {a mathematical formula}u3, each with a single parameter in the form of an index. We also need two predicates {a mathematical formula}last, on one index, and {a mathematical formula}consecutive, on two indices.
      </paragraph>
      <paragraph>
       For a given n, the idea is to introduce objects {a mathematical formula}j1,…,jn of type {a mathematical formula}index. For each {a mathematical formula}1⩽i⩽n, the fluent {a mathematical formula}a(ji) corresponds to the variable {a mathematical formula}ai of the planning instance {a mathematical formula}Pn, and so on. The initial state of the PDDL planning instance is given by {a mathematical formula}{last(jn),consecutive(j1,j2),…,consecutive(jn−1,jn)}, consisting solely of static fluents.
      </paragraph>
      <paragraph>
       Each action in Table 2 has preconditions and effects on variables in {a mathematical formula}Xi∪Vi for some {a mathematical formula}1⩽i⩽n, or on variables in consecutive sets {a mathematical formula}Xi∪Vi and {a mathematical formula}Xi+1∪Vi+1. We parameterize actions of the first type on a single index {a mathematical formula}ji, and actions of the second type on two indices {a mathematical formula}ji and {a mathematical formula}ji+1, using the precondition {a mathematical formula}consecutive(ji,ji+1) to ensure that the indices are consecutive. Finally, we append the precondition {a mathematical formula}last(ji) to actions {a mathematical formula}un01,…,un31, ensuring that these actions are only applicable for index {a mathematical formula}jn.
      </paragraph>
      <paragraph>
       In total, the resulting planning domain has 18 actions: six actions on variables in {a mathematical formula}Xi for {a mathematical formula}1⩽i⩽n, four actions making variables in {a mathematical formula}Vi true for {a mathematical formula}1⩽i&lt;n, four actions making variables in {a mathematical formula}Vi true for {a mathematical formula}i=n, and four actions resetting variables in {a mathematical formula}Vi to false for {a mathematical formula}1⩽i⩽n. A sample PDDL encoding that includes some actions of the domain appears in Table 5.
      </paragraph>
      <paragraph>
       In experiments, the planning domain is highly challenging, which we attribute to the fact that there are a lot of deadends. LAMA 2011 [14] performs best of the planners we tested, but is only able to solve the planning instance {a mathematical formula}Pn for {a mathematical formula}n⩽4. For {a mathematical formula}n=4, the solution contains 200 grounded operators (the optimal plan length of {a mathematical formula}Pn is {a mathematical formula}16⋅2n−10n−16).
      </paragraph>
      <paragraph>
       The planning domain encoding QBF instances is similar to that simulating nested loops. There is a type {a mathematical formula}index with associated predicates that correspond to variables in the sets {a mathematical formula}Xi and {a mathematical formula}Vi, the latter containing additional variables compared to the planning instance {a mathematical formula}Pn.
      </paragraph>
      <paragraph>
       In addition to the variables in {a mathematical formula}Xi∪Vi, we have to represent the variables in the set S, corresponding to the clauses of the QBF formula. To do so, we introduce a second type {a mathematical formula}clause with associated predicates {a mathematical formula}sat, on one clause, and {a mathematical formula}unsat, with no parameters. To represent the precondition {a mathematical formula}S¯ of actions {a mathematical formula}un01, {a mathematical formula}un21, and {a mathematical formula}vn21 we have to use an ADL type {a mathematical formula}forall construct since the number of clauses may vary between QBF instances. We remark that we can get rid of the {a mathematical formula}forall construct using our modified reduction described in the next section.
      </paragraph>
      <paragraph>
       Just as for indices, we have to keep track of the last clause as well as consecutive clauses. To distinguish between indices and clauses we introduce predicates {a mathematical formula}last-{a mathematical formula}index, {a mathematical formula}consecutive-{a mathematical formula}indices, {a mathematical formula}last-{a mathematical formula}clause, and {a mathematical formula}consecutive-{a mathematical formula}clauses. For a QBF formula F on n variables and m clauses, we introduce objects {a mathematical formula}j1,…,jm of type {a mathematical formula}index and {a mathematical formula}c1,…,cm of type {a mathematical formula}clause, and define the initial state by indicating the last clause and index as well as consecutive clauses and indices. Once this is done, defining the actions is straightforward.
      </paragraph>
      <paragraph>
       This planning domain is even more challenging than the previous one: no planner can solve the planning instance {a mathematical formula}PF associated with a satisfiable QBF F on four variables and one clause. Since our encoding requires the QBF to be in prenex normal form, the number of variables has to be a multiple of two, and with only two variables we cannot define a meaningful QBF. Consequently, it appears that our reduction from Qbf-Sat to planning instances with acyclic causal graphs is impractical to implement and solve, at least using current state-of-the-art planners.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Bounded number of preconditions
     </section-title>
     <paragraph>
      Bylander [11] showed that the problem of plan existence is PSPACE-complete for Strips planning instances whose actions have one postcondition and unbounded number of preconditions (either positive or negative). He did not prove a result for a bounded number k of preconditions, but conjectured that plan existence falls into the polynomial hierarchy in a regular way, with the precise complexity determined by k. In this section we modify our previous reduction such that actions have at most two preconditions, thus showing that plan existence is PSPACE-complete for {a mathematical formula}k=2 and proving Bylander's conjecture to be wrong.
     </paragraph>
     <paragraph>
      We first modify loop instances such that they have at most two preconditions. Given a planning instance {a mathematical formula}P=〈V,A,I,G〉, such a modified loop instance is a subset of variables {a mathematical formula}U={a,b,x,u1,u2,u3,u4}⊆V with associated actions {a mathematical formula}A(U)⊆A such that {a mathematical formula}{u¯1,u¯2,u¯3,u¯4}⊆I and {a mathematical formula}u4 is a landmark of P. In other words, variables {a mathematical formula}u1,…,u4 are initially false, and either {a mathematical formula}u4∈G or {a mathematical formula}u4 is a precondition of some action required to reach the goal state G. Table 6 shows the action set {a mathematical formula}A(U) of a modified loop instance U.
     </paragraph>
     <paragraph>
      Unlike the original notion of loop instance, the solution to a modified loop instance is not unique: action {a mathematical formula}b1 may appear before or after {a mathematical formula}u21, and action {a mathematical formula}b2 may appear before or after action {a mathematical formula}u31. However, the key property of loop instances still holds: on any plan solving a modified loop instance, {a mathematical formula}{b¯,x¯} holds before action {a mathematical formula}u11 and {a mathematical formula}{b¯,x} holds after {a mathematical formula}u41. Moreover, although the initial state does not explicitly mention the variables in {a mathematical formula}{a,b,x}, these have to be initially false for the modified loop instance U to be solvable.
     </paragraph>
     <paragraph>
      We now modify our reduction from Qbf-Sat to Pe(Acyc) by redefining the planning instance {a mathematical formula}PF′=〈VF′,AF′,IF′,GF′〉 such that
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}VF′=⋃i=1n(Xi∪Vi′)∪E′∪S′,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Vi′={ui0,ui1,ui2,…,ui9,vi2,…,vi9} for each {a mathematical formula}1⩽i⩽n,
      </list-item>
      <list-item label="•">
       {a mathematical formula}E′=⋃j=0m{ej0,…,ej5},
      </list-item>
      <list-item label="•">
       {a mathematical formula}S′={s1,…,sm,r2,…,rm}∪⋃j=1m{tj1,…,tj3},
      </list-item>
      <list-item label="•">
       {a mathematical formula}AF′=⋃i=1n(Ai∪Bi′)∪AE′∪AS′,
      </list-item>
      <list-item label="•">
       {a mathematical formula}IF′=V¯F′,
      </list-item>
      <list-item label="•">
       {a mathematical formula}GF′={u19}.
      </list-item>
     </list>
     <paragraph>
      For each {a mathematical formula}1⩽i⩽n, the set {a mathematical formula}Xi={ai,bi,xi} and the action set {a mathematical formula}Ai on variables in {a mathematical formula}Xi are the same as in the original reduction.
     </paragraph>
     <paragraph>
      The set {a mathematical formula}S′ includes many more variables than the original set S. Variables {a mathematical formula}s1,…,sm are still used to verify that each clause is satisfied for the current assignment to {a mathematical formula}x1,…,xn. For each {a mathematical formula}1⩽j⩽m, variables {a mathematical formula}tj1,…,tj3 are used to verify that clause {a mathematical formula}cj is unsatisfied. Variables {a mathematical formula}r2,…,rm are used to aggregate the information regarding some clause being unsatisfied, which is necessary since the proof of unsatisfiability for each clause is a separate chain of variables. More specifically, {a mathematical formula}rm can be made true if and only if at least one clause is unsatisfied, and can be reset to false only if {a mathematical formula}r2,…,rm−1 and their predecessors are false. Variables in {a mathematical formula}E′ are used to ensure that we can only make one variable true among {a mathematical formula}s1,t11,…,tm1 while {a mathematical formula}bn is false.
     </paragraph>
     <paragraph>
      Table 7 shows the actions in the sets {a mathematical formula}AE′ and {a mathematical formula}AS′. To help understand the mechanism behind these actions, Fig. 5 shows the subgraph of the causal graph on variables in {a mathematical formula}E′∪S′. Intuitively, we can no longer use a single action to check whether a given clause {a mathematical formula}cj is unsatisfied, since this would require at least three preconditions. Instead, we check each literal of {a mathematical formula}cj in turn, corresponding to the actions {a mathematical formula}tj11, {a mathematical formula}tj21, and {a mathematical formula}tj31. The intermediate states have to be different for each clause, which is why we need variables {a mathematical formula}tj1, {a mathematical formula}tj2, and {a mathematical formula}tj3 for each clause {a mathematical formula}cj.
     </paragraph>
     <paragraph>
      We proceed to prove several lemmas regarding the actions in {a mathematical formula}AE′ and {a mathematical formula}AS′.
     </paragraph>
     <paragraph label="Lemma 12">
      While{a mathematical formula}bnis false, starting from{a mathematical formula}E¯′∪S¯′it is impossible to make a variable{a mathematical formula}v∈E′∪S′true and then reset v to false.
     </paragraph>
     <paragraph label="Proof">
      By induction on v in the topological ordering induced by the causal graph. The base case is given by {a mathematical formula}v=e01, an antecessor of all other variables in {a mathematical formula}E′∪S′. While {a mathematical formula}bn is false we can make {a mathematical formula}e01 true using action {a mathematical formula}e011, but {a mathematical formula}e012, the only action resetting {a mathematical formula}e01 to false, has precondition {a mathematical formula}bn.In the inductive case, by inspection of the actions we can verify that there exists a predecessor {a mathematical formula}u∈E′∪S′ of v such that each action making v true has precondition u, while each action making v false has precondition {a mathematical formula}u¯. By hypothesis of induction we cannot make u true and then reset it to false, rendering it impossible to make v true and reset it to false.  □
     </paragraph>
     <paragraph label="Lemma 13">
      While{a mathematical formula}bnis false, to make{a mathematical formula}smor{a mathematical formula}rmtrue starting from{a mathematical formula}E¯′∪S¯′we can make at most one of{a mathematical formula}e(j−1)3and{a mathematical formula}ej0true for each{a mathematical formula}1⩽j⩽m.
     </paragraph>
     <paragraph label="Proof">
      To make {a mathematical formula}sm or {a mathematical formula}rm true starting from {a mathematical formula}E¯′∪S¯′ while {a mathematical formula}bn is false, we have to either make {a mathematical formula}s1,…,sm true in sequence, thus verifying that the 3SAT formula ϕ is satisfied by the current assignment to {a mathematical formula}x1,…,xn, or choose a clause {a mathematical formula}cj and make {a mathematical formula}tj1,tj2,tj3 true in sequence, thus verifying that {a mathematical formula}cj is unsatisfied. In the latter case, we have to finish by making {a mathematical formula}rj,…,rm true (or {a mathematical formula}rj+1,…,rm if {a mathematical formula}j=1).Making {a mathematical formula}s1,…,sm true requires first making {a mathematical formula}e03,e04,e05 true. Due to Lemma 12 we cannot make {a mathematical formula}e10 true before applying action {a mathematical formula}e051 since the latter has precondition {a mathematical formula}e¯10. Likewise, we cannot make {a mathematical formula}e10 true after {a mathematical formula}e041, since the latter has precondition {a mathematical formula}e02 and the only action {a mathematical formula}e101 making {a mathematical formula}e10 true has precondition {a mathematical formula}e¯02. Since {a mathematical formula}e041 has to appear before {a mathematical formula}e051 to make {a mathematical formula}e03,e04,e05 true, this prevents us from making {a mathematical formula}e10 true at all. The same argument holds regarding {a mathematical formula}e(j+1)0 if we want to make {a mathematical formula}tj1,tj2,tj3 true for any {a mathematical formula}1⩽j&lt;m.Conversely, if we want to make {a mathematical formula}t11,t12,t13 true, we first have to make {a mathematical formula}e10,e11,e12 true. Due to Lemma 12 we cannot make {a mathematical formula}e03 true before applying action {a mathematical formula}e121 since the latter has precondition {a mathematical formula}e¯03. Likewise, we cannot make {a mathematical formula}e03 true after {a mathematical formula}e111, since the latter has precondition {a mathematical formula}e02 and the only action {a mathematical formula}e031 making {a mathematical formula}e03 true has precondition {a mathematical formula}e¯02. Since {a mathematical formula}e111 has to appear before {a mathematical formula}e121 to make {a mathematical formula}e10,e11,e12 true, this prevents us from making {a mathematical formula}e03 true at all. The same argument holds regarding {a mathematical formula}e(j−1)3 if we want to make {a mathematical formula}tj1,tj2,tj3 true for any {a mathematical formula}2⩽j⩽m.  □
     </paragraph>
     <paragraph>
      As a consequence of Lemma 13, to make {a mathematical formula}sm or {a mathematical formula}rm true we can only make variables true along a single path.
     </paragraph>
     <paragraph label="Corollary 14">
      After making{a mathematical formula}smor{a mathematical formula}rmtrue starting from{a mathematical formula}E¯′∪S¯′while{a mathematical formula}bnis false, there is a directed path p in the causal graph from{a mathematical formula}e01to{a mathematical formula}smor{a mathematical formula}rmsuch that all variables on p are true and all other variables in{a mathematical formula}E′∪S′are false.
     </paragraph>
     <paragraph>
      If the 3SAT formula ϕ is satisfiable, the path p from Corollary 14 is {a mathematical formula}〈e01,…,e05,s1,…,sm〉, else there exists {a mathematical formula}1⩽j⩽m such that the path is {a mathematical formula}〈e01,e02,e10,e11,e12,…,ej0,…,ej5,tj1,tj2,tj3,rj,…,rm〉. The only other actions whose preconditions are satisfied during this process are those making a variable among {a mathematical formula}e03,…,e(j−1)3,e(j+1)0 true. All other actions require a variable not on the path p to be true. Due to Lemma 13, no variable among {a mathematical formula}e03,…,e(j−1)3,e(j+1)0 can be made true simultaneously with the variables {a mathematical formula}e10,…,ej0,ej3 on the path p.
     </paragraph>
     <paragraph label="Lemma 15">
      Assume that all variables in{a mathematical formula}E′∪S′are false except those on a path p from{a mathematical formula}e01to{a mathematical formula}smor{a mathematical formula}rm. Starting from this situation, satisfying{a mathematical formula}{s¯m,r¯m}while{a mathematical formula}bnis true causes all variables in{a mathematical formula}E′∪S′to be false.
     </paragraph>
     <paragraph label="Proof">
      From the given situation it is easy to show that the converse of Lemma 12 holds: we cannot make a variable in {a mathematical formula}E′∪S′ false and then true. While {a mathematical formula}bn is true, action {a mathematical formula}e012 making {a mathematical formula}e01 false is applicable, but not {a mathematical formula}e011. The inductive case is identical to that in the proof of Lemma 12. Moreover, making a variable on p false requires first making its predecessor false. Since the last variable on p is {a mathematical formula}sm or {a mathematical formula}rm, making {a mathematical formula}sm and {a mathematical formula}rm false has the effect of making all variables on p false. During this process we cannot make any variable outside p true, since the precondition of actions {a mathematical formula}ej3 and {a mathematical formula}e(j+1)0 is {a mathematical formula}{ej1,e¯j2} and {a mathematical formula}ej1 has to be false before making {a mathematical formula}ej2 false.  □
     </paragraph>
     <paragraph>
      Table 8 shows the actions in the set {a mathematical formula}Bn′ for {a mathematical formula}1⩽k⩽9. There are a number of differences with respect to the original action set {a mathematical formula}Bn. First, the precondition {a mathematical formula}S¯ has been replaced with {a mathematical formula}{s¯m,r¯m}, which in turn has been split across two actions (the pairs {a mathematical formula}(un01,un11), {a mathematical formula}(un71,un81), and {a mathematical formula}(vn71,vn81), respectively). Second, action {a mathematical formula}un01 has precondition {a mathematical formula}b¯n−1. Finally, action {a mathematical formula}un02 has precondition {a mathematical formula}bn−1 and, for each {a mathematical formula}1⩽k⩽9, the actions making {a mathematical formula}unk or {a mathematical formula}vnk false have precondition {a mathematical formula}{u¯n(k−1),v¯n(k−1)} (the action {a mathematical formula}vnk4 is omitted for {a mathematical formula}k=1, and the precondition {a mathematical formula}v¯n(k−1) is omitted for {a mathematical formula}k=1 and {a mathematical formula}k=2).
     </paragraph>
     <paragraph>
      Table 9 shows the actions in the set {a mathematical formula}Bi′ for {a mathematical formula}1⩽i&lt;n and {a mathematical formula}1⩽k⩽9. These actions are essentially the same as those in {a mathematical formula}Bn′, except we have replaced the precondition {a mathematical formula}V¯i+1 with {a mathematical formula}{u¯(i+1)9,v¯(i+1)9} and split it across two actions. Just as before we define two partial planning instances {a mathematical formula}Pi1″(pi) and {a mathematical formula}Pi2″(pi) for each {a mathematical formula}1⩽i⩽n and each assignment {a mathematical formula}pi. The goal of {a mathematical formula}Pi1″(pi) is {a mathematical formula}ui9, while the goal of {a mathematical formula}Pi2″(pi) is {a mathematical formula}vi9.
     </paragraph>
     <paragraph>
      In spite of the differences between {a mathematical formula}PF and {a mathematical formula}PF′, the mechanism is the same: for each {a mathematical formula}1⩽i⩽n, the planning instance {a mathematical formula}Pi1″(pi) has associated modified loop instance {a mathematical formula}Ui1={ai,bi,xi,ui3,ui4,ui5,ui6}, while {a mathematical formula}Pi2″(pi) has alternative modified loop instances {a mathematical formula}Ui1 and {a mathematical formula}Ui2={ai,bi,xi,vi3,vi4,vi5,vi6}. It is easy to prove the equivalent of Lemma 12, Lemma 15 for the variables in {a mathematical formula}Vi′: while solving {a mathematical formula}Pi1″(pi) or {a mathematical formula}Pi2″(pi), we cannot make a variable in {a mathematical formula}Vi′ true and then false, and when subsequently making {a mathematical formula}ui9 and {a mathematical formula}vi9 false while {a mathematical formula}bi−1 is true, all variables in {a mathematical formula}Vi′ become false.
     </paragraph>
     <paragraph label="Theorem 2">
      The planning instance{a mathematical formula}PF′has a solution if and only if the QBF formula F is satisfiable.
     </paragraph>
     <paragraph label="Proof">
      We show that the equivalent of Lemma 9 holds for partial planning instances {a mathematical formula}Pi1″(pi) and {a mathematical formula}Pi2″(pi). For {a mathematical formula}i=n, to solve {a mathematical formula}Pn1″(pn) we have to apply the action subsequence {a mathematical formula}〈un01,…,un91〉 with associated loop instance {a mathematical formula}Un1. This requires making {a mathematical formula}rm true starting from {a mathematical formula}E¯′∪S¯′ while {a mathematical formula}bn is false, then satisfying {a mathematical formula}{s¯m,r¯m} while {a mathematical formula}bn is true, then making {a mathematical formula}rm true again while {a mathematical formula}bn is false. Corollary 14 implies that after making {a mathematical formula}rm true, there is a single path of variables in {a mathematical formula}E′∪S′ that are true. Lemma 15 then implies that when satisfying {a mathematical formula}{s¯m,r¯m} while {a mathematical formula}bn is true, all variables in {a mathematical formula}E′∪S′ become false. Making {a mathematical formula}rm true is possible if and only of the formula ϕ is unsatisfied, implying that {a mathematical formula}Pi1″(pi) is solvable if and only if {a mathematical formula}Fn(pn) is unsatisfiable.Conversely, to solve {a mathematical formula}Pn2″(pn) we have to apply one of three subsequences:{a mathematical formula}{a mathematical formula}{a mathematical formula} The first of these subsequences has associated loop instance {a mathematical formula}Un1, while the latter two have associated loop instance {a mathematical formula}Un2. Since each subsequence requires making {a mathematical formula}sm true for {a mathematical formula}pn∪{x¯n} or {a mathematical formula}pn∪{xn}, {a mathematical formula}Pn2″(pn) is solvable if and only if {a mathematical formula}Fn(pn) is satisfiable.For {a mathematical formula}i&lt;n, solving {a mathematical formula}Pi1″(pi) or {a mathematical formula}Pi2″(pi) requires making {a mathematical formula}u(i+1)9 or {a mathematical formula}v(i+1)9 true starting from {a mathematical formula}V¯i+1′ while {a mathematical formula}bi is false, then satisfying {a mathematical formula}{u¯(i+1)9,v¯(i+1)9} while {a mathematical formula}bi is true, then making {a mathematical formula}u(i+1)9 or {a mathematical formula}v(i+1)9 true again while {a mathematical formula}bi is false. Satisfying {a mathematical formula}{u¯(i+1)9,v¯(i+1)9} while {a mathematical formula}bi is true causes all variables in {a mathematical formula}Vi+1′ to be false. Technically, we can apply {a mathematical formula}u(i+1)01 before the precondition {a mathematical formula}{u¯(i+1)9,v¯(i+1)9} is checked, but {a mathematical formula}u(i+1)01 has to appear after {a mathematical formula}bi2, at which time the value of {a mathematical formula}xi is already fixed.Making {a mathematical formula}u(i+1)9 or {a mathematical formula}v(i+1)9 true starting from {a mathematical formula}V¯i+1′ while {a mathematical formula}bi is false corresponds to solving {a mathematical formula}P(i+1)1″(pi+1) or {a mathematical formula}P(i+1)2″(pi+1), first for {a mathematical formula}pi+1=pi∪{x¯i}, then for {a mathematical formula}pi+1=pi∪{xi}. We can now apply the same reasoning as in the proof of Lemma 9. Since {a mathematical formula}P11″(p1)=P11″(∅)=PF′, we have shown that {a mathematical formula}PF′ is solvable if and only if {a mathematical formula}F1(p1)=F1(∅)=F is satisfiable.  □
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      The complexity of planning for ISR-Acyc
     </section-title>
     <paragraph>
      In the previous section we established that plan existence is PSPACE-complete for planning instances with acyclic causal graphs. This raises the question whether there are subclasses of Acyc for which plan existence is easier. In this section we identify one such subclass by showing that Pe(ISR-Acyc) is NP-complete. Without loss of generality we assume that the initial state of each propositional variable {a mathematical formula}v∈V is {a mathematical formula}v¯.
     </paragraph>
     <paragraph label="Proposition 16">
      Pe(ISR-Acyc) is NP-complete.
     </paragraph>
     <paragraph label="Proof">
      NP-hardness follows immediately from Theorem 2 in Brafman and Domshlak [6]; merely note that each variable in their construction is irreversible.We continue by proving membership in NP. Let {a mathematical formula}P=〈V,A,I,G〉 be an arbitrary instance of ISR-Acyc, and let {a mathematical formula}VI⊆V be the subset of irreversible variables. A plan solving P cannot change the values of variables in {a mathematical formula}VI more than once. We construct a non-deterministic guess as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       a subset {a mathematical formula}U⊆VI of variables whose values change once,
      </list-item>
      <list-item label="2.">
       a total order ≺ on U (the order in which variables change),
      </list-item>
      <list-item label="3.">
       for each {a mathematical formula}v∈U, a state {a mathematical formula}sv and an action {a mathematical formula}av applicable in {a mathematical formula}sv that satisfies {a mathematical formula}post(av)={v}.
      </list-item>
     </list>
    </section>
    <section label="7">
     <section-title>
      The complexity of planning for SC-Acyc
     </section-title>
     <paragraph>
      In this section we study the complexity of plan existence and bounded plan existence when the causal graph is acyclic and the DTG of each variable is strongly connected. We first show that the decision problem Pe(SC-Acyc) is in P by proving that all planning instances in SC-Acyc have a solution. We then show that the decision problem Bpe(SC-Acyc) is PSPACE-complete. This latter result generalizes that of Helmert [3], who showed that bounded plan existence is NP-hard for the subclass of SC-Acyc with inverted fork causal graphs.
     </paragraph>
     <paragraph label="Lemma 17">
      For each planning instance P in SC-Acyc, there exists a plan that solves P (andPe(SC-Acyc) is in P).
     </paragraph>
     <paragraph label="Proof">
      By induction on the cardinality {a mathematical formula}|V|. If {a mathematical formula}|V|=1, the resulting planning instance has a single variable, and the fact that {a mathematical formula}DTG(v) is strongly connected implies that we can always reach any value in {a mathematical formula}D(v) from any other value. Thus P has a solution regardless of the values of I and G.If {a mathematical formula}|V|=n&gt;1, choose a variable {a mathematical formula}v∈V without incoming edges in the causal graph G. Such a variable exists since G is acyclic. Let {a mathematical formula}W=V∖{v}, and let {a mathematical formula}A|W={〈pre(a)|W,post(a)〉:a∈A,Vpost(a)⊆W} be the projection of the actions in A onto W. Compute a solution to the planning instance {a mathematical formula}〈W,A|W,I|W,G|W〉. Such a solution exists by induction hypothesis since {a mathematical formula}|W|&lt;n.If we convert the actions in the resulting plan back to A, some of them might have preconditions on v. To compute a solution to P we can now simply insert actions on v that achieve these preconditions. Such actions exist since {a mathematical formula}DTG(v) is strongly connected and since no actions on v have a precondition on other variables (else v would have an incoming edge in the causal graph). If {a mathematical formula}v∈VG, also insert actions that satisfy the goal state {a mathematical formula}G(v) on v.  □
     </paragraph>
     <paragraph>
      To prove that Bpe(SC-Acyc) is PSPACE-complete, we take advantage of our reduction from Qbf-Sat to Pe(Acyc), described in Section 4. Given a QBF formula F, the planning instance {a mathematical formula}PF that we construct has a single variable whose DTG is not strongly connected, namely {a mathematical formula}a1 (incidentally implying that a single irreversible variable is sufficient to increase the complexity of plan existence from P to PSPACE). We modify the planning problem {a mathematical formula}PF by adding variables {a mathematical formula}c1,…,ck where {a mathematical formula}k=⌈logL(m,n)⌉ and {a mathematical formula}L(m,n) is the upper bound on the length of optimal plans for {a mathematical formula}PF from Lemma 11 (implying that k is polynomial in the size of F). The variables {a mathematical formula}c1,…,ck are initially false.
     </paragraph>
     <paragraph>
      Table 10 shows the actions on {a mathematical formula}c1,…,ck, causing these variables to act as a Gray counter from 0 to {a mathematical formula}2k−1[12]. The causal graph on these variables is acyclic since there is no edge from a variable {a mathematical formula}ci to a variable {a mathematical formula}cj with {a mathematical formula}j&lt;i. We now define a single additional action {a mathematical formula}a12 whose precondition on {a mathematical formula}c1,…,ck encodes the value {a mathematical formula}L(m,n), and whose effect is {a mathematical formula}a¯1.
     </paragraph>
     <paragraph label="Theorem 3">
      The decision problemBpe(SC-Acyc) is PSPACE-complete.
     </paragraph>
     <paragraph label="Proof">
      Membership is trivial, and we prove PSPACE-hardness by reduction from Qbf-Sat. Let F be an arbitrary QBF formula, and let {a mathematical formula}PF″ be our modified planning instance from above. The causal graph of {a mathematical formula}PF″ is acyclic and each variable has strongly connected DTG, including {a mathematical formula}a1 and {a mathematical formula}c1,…,ck. Then Lemma 17 implies that there exists a plan solving {a mathematical formula}PF″.Let {a mathematical formula}L(m,n) be the bound on the optimal plan length of the planning instance {a mathematical formula}PF from Lemma 11. We claim that {a mathematical formula}PF″ has a solution of length at most {a mathematical formula}L(m,n) if and only if F is satisfiable. If F is satisfiable, the original planning instance {a mathematical formula}PF has a solution plan of length at most {a mathematical formula}L(m,n), and this plan is also a solution to {a mathematical formula}PF″. If F is not satisfiable, the original planning instance {a mathematical formula}PF does not have a solution. This means that we have to use action {a mathematical formula}a12 to solve {a mathematical formula}PF″, which requires us to first use the Gray counter {a mathematical formula}c1,…,ck to count to {a mathematical formula}L(m,n), causing any plan solving {a mathematical formula}PF″ to have length greater than {a mathematical formula}L(m,n).  □
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      The conception of the causal graph is usually credited to Knoblock [1], who devised an algorithm that constructs abstraction hierarchies for planning instances with acyclic causal graphs. Bacchus and Yang [2] extended this idea, improving the chance of obtaining a hierarchical solution. The causal graph heuristic [3] exploits acyclic causal graphs to approximate the cost of reaching the goal. When necessary, the algorithm breaks cycles in the graph by ignoring some of the preconditions of each action.
     </paragraph>
     <paragraph>
      Several authors have studied the computational complexity of planning when the causal graph is acyclic. Bäckström and Nebel [12] showed that there are planning instances with acyclic causal graphs that have exponentially long solutions. However, this does not necessarily imply that it is hard to determine whether a solution exists [5]. Williams and Nayak [4] proposed a reactive planner that outputs each action in polynomial time when the causal graph is acyclic and variables are reversible. A similar algorithm was proposed by Jonsson and Bäckström [5] for the class 3S of planning instances with acyclic causal graph and propositional variables that are either static, splitting, or symmetrically reversible. Brafman and Domshlak [6] studied the class of planning instances with propositional variables and polytree causal graphs, and designed a polynomial-time algorithm that outputs a complete solution when the causal graph has bounded indegree. Giménez and Jonsson [7] showed that the problem of plan existence is NP-complete for this class when the indegree is unbounded. Chen and Giménez [15] showed that when variables have domains of unbounded size, any connected causal graph containing an unbounded number of variables causes plan existence to be bounded away from P.
     </paragraph>
     <paragraph>
      Regarding our PDDL encoding for translating QBF formulae to planning instances, we are only aware of two previous related approaches. The first is the reduction by Bylander [11] from deterministic Turing machine (DTM) acceptance to Strips planning. Although no PDDL encoding was provided, in principle we could first reduce Qbf-Sat to DTM acceptance and then use Bylander's reduction to produce a planning instance. The second approach is the work of Porco et al. [16], who introduced a general approach to translating formulae in second order logic to planning instances in PDDL. However, this is only sufficient to translate problems in the polynomial hierarchy, not PSPACE.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>