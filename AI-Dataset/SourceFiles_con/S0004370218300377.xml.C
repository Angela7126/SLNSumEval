<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Extracting mutual exclusion invariants from lifted temporal planning domains.
   </title>
   <abstract>
    We present a technique for automatically extracting mutual exclusion invariants from temporal planning instances. It first identifies a set of invariant templates by inspecting the lifted representation of the domain and then checks these templates against properties that assure invariance. Our technique builds on other approaches to invariant synthesis presented in the literature but departs from their limited focus on instantaneous actions by addressing temporal domains. To deal with time, we formulate invariance conditions that account for the entire temporal structure of the actions and the possible concurrent interactions between them. As a result, we construct a more comprehensive technique than previous methods, which is able to find not only invariants for temporal domains but also a broader set of invariants for sequential domains. Our experimental results provide evidence that our domain analysis is effective at identifying a more extensive set of invariants, which results in the generation of fewer multi-valued state variables. We show that, in turn, this reduction in the number of variables reflects positively on the performance of the temporal planners that use a variable/value representation.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      This paper presents a technique for synthesising mutual exclusion invariants from temporal planning domains expressed in PDDL2.1 [21]. A mutual exclusion invariant over a set of ground atoms means that at most one atom in the set is true at any given moment. Mutual exclusion invariants can be expressed as multi-valued state variables by adding a special “null” value so that, at all moments, precisely one value holds. For instance, consider the {a mathematical formula}Floortile domain from the 8th International Planning Competition (IPC'14 – see Appendix A). A mutual exclusion invariant for this domain states that two ground atoms that indicate the position of a robot can never be true at the same time. Intuitively, this means that a robot cannot be at two different locations simultaneously. To give a concrete case, consider a planning problem for the {a mathematical formula}Floortile domain with one robot r1 and three locations, t1, t2 and t3. We can create a state variable that indicates the position of r1 with a domain of three values: robotAt_r1_t1, robotAt_r1_t2 and robotAt_r1_t3.
     </paragraph>
     <paragraph>
      Although a number of approaches to invariant synthesis have been proposed so far [27], [45], [46], [20], [33], they are limited in scope because they deal with sequential domains only. Recently, Rintanen [47] has proposed a technique for temporal domains, but this technique does not scale to complex problems because it requires grounding the domain. We address both limitations. We find invariants for temporal domains by applying an algorithm that works at the lifted level of the representation and, in consequence, is very efficient and scales to large instances.
     </paragraph>
     <paragraph>
      Our invariant synthesis builds on Helmert [33], which presents a technique to translate the non-temporal subset of PDDL2.2 [17] into the Finite Domain Representation (FDR), a multi-valued planning task formalism used by Fast Downward [32]. Since finding invariants for temporal tasks is much more complex than for tasks with instantaneous actions, a simple generalisation of Helmert's technique to temporal settings does not work. In the temporal case, simultaneity and interference between concurrent actions can occur, hence our algorithm cannot check actions individually against the invariance conditions, but needs to consider the entire set of actions and their possible intertwinements over time. In capturing the temporal case, we formulate invariance conditions that take into account the entire structure of the action schemas as well as the possible interactions between them. As a result, we construct a significantly more comprehensive technique that is able to find not only invariants for temporal domains, but also a broader set of invariants for sequential domains.
     </paragraph>
     <paragraph>
      We describe our approach in two major steps. First, we provide a general theory at the ground level and offer results that insure invariance under two types of properties: safety conditions for individual instantaneous and durative actions as well as collective conditions that prevent dangerous intertwinements between durative actions. Then, we lift these results to the level of schemas so that all checks needed for verifying invariance can be performed at this higher level, without the need for grounding the domain. The complexity of these checks are of linear or low polynomial order in terms of the number of schemas and literals appearing in the domain.
     </paragraph>
     <section label="1.1">
      <section-title>
       Motivations
      </section-title>
      <paragraph>
       Automated planning is a well-established field of artificial intelligence and, in the more than fifty years since its appearance, several paradigms have emerged. One fundamental difference between these paradigms is whether time is treated implicitly or explicitly. While classical planning focuses on the causal evolution of the world, temporal planning is concerned with the temporal properties of the world. In classical planning, actions are considered to be instantaneous, whereas in temporal planning actions have durations and can be executed concurrently. Another important difference between planning paradigms relates to whether the world is modelled by adopting a Boolean propositional representation or a representation based on multi-valued state variables. The majority of the work in planning has been devoted to classical planning with domains expressed using propositional languages, and in particular PDDL [41] and its successors [21], the language of the International Planning Competition (IPC). However, in parallel with the development of classical propositional planning, a number of temporal planning systems have been proposed for coping with practical problems, especially space mission operations [23], [11], [28], [42], [24]. Typically, these systems use variable/value representations. Table 1 shows a classification of several well-known planners based on these different characteristics.
      </paragraph>
      <paragraph>
       Recently, a few techniques have been proposed for translating propositional representations into variable/value representations [32], [5], [47]. A central task of all these techniques is the generation of state variables from propositions and actions. The basic procedure to do this (which we use as the baseline in our experiments) relies on generating one state variable with two values, true and false, for each proposition. Naturally, such translation produces no performance advantage. A more sophisticated strategy, which produces more compact and optimised encodings, rests on extracting mutual exclusion invariants from propositional domains and using such invariants to generate multi-valued state variables. This is the focus of our work.
      </paragraph>
      <paragraph>
       These translation techniques are important as they allow fair testing of planners developed for variable/value representations on PDDL benchmarks (which are propositional). The practical issue is that planners that permit variable/value representation need this feature to be thoroughly exploited and perform competitively. Since translation between the two different representations can be cheaply automated, there is no reason to avoid providing the richer representations to those planners that accept them (if the translation was expensive, one might reasonably argue about the fairness of this process). As a consequence, these translation techniques are extremely useful for comparing alternative planning paradigms and for promoting cross-fertilisation of ideas between different planning communities, which is our primary motivation.
      </paragraph>
      <paragraph>
       However, the importance of these translation techniques goes beyond the engineering of a bridge between different input languages. In transforming propositional representations into state variable representations, they generate new domain knowledge, where new means accessible in this context. Effectively, these techniques are internal mini theorem provers since, rather than merely translating, they firstly selectively explore the deductive closure of the original theory to find theorems that permit optimising the representation, and secondly execute those optimisations. We will show that the cost of performing these optimisations is worth it because it is very fast and can be amortised over many problems.
      </paragraph>
      <paragraph>
       Mutual exclusion invariants are also beneficial in pruning the search space for search methods such as symbolic techniques based on SAT [39], [37] and backward chaining search [8]. In addition, as invariants help to reduce the number of variables required to encode a domain, they are used in planning systems based on binary decision diagrams (BDDs) [16], constraint programming [14], causal graph heuristics [32] and pattern databases [31].
      </paragraph>
      <paragraph>
       Finally, from a knowledge engineering perspective, the invariant synthesis presented in this paper can be used as a powerful tool for debugging temporal planning domains. We do not focus on this specifically in this paper, but present a case study in Example 19. As shown in Cushing et al. [13], several temporal planning tasks developed for the various IPC competitions are buggy, with the consequence that the planners take a long time to solve them, when they actually manage to do so. As invariants capture intuitive properties of the physical systems described in the domains, it is easy for a domain expert to identify modelling mistakes by inspecting them. Discrepancies between the invariants found by the automatic technique and those that the expert expects to see for a given domain indicate that the domain does not encode the physical system correctly. In consequence, the expert can revise the domain and repair it. For example, considering the {a mathematical formula}Rover domain, we expect that a store could be either full or empty at any time point. However, the invariant synthesis does not produce an invariant with the atoms full and empty. It can be shown that this is because the action drop is not properly modelled. Our technique not only alerts the expert that the system is not properly modelled, but also refers the expert to the action that is not encoded correctly. This is a useful feature to fix modelling errors quickly and safely.
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Contributions of the paper
      </section-title>
      <paragraph>
       In brief, the contributions of this paper are the following.
      </paragraph>
      <paragraph>
       From a theoretical point of view:
      </paragraph>
      <list>
       <list-item label="•">
        We give the first formal account of a mutual exclusion invariant synthesis for temporal domains that works at the lifted level of the representation. Our presentation of this topic is rigorous and comprehensive and our theory is general.
       </list-item>
       <list-item label="•">
        Our technique is based on inferring general properties of the state space by studying the structure of the action schemas and the lifted relations in the domain, without the need to ground it. This is generally a hard task. Our theoretical framework is sophisticated, but it results in practical tools that have high efficiency and low computational cost.
       </list-item>
      </list>
      <paragraph>
       From a practical point of view:
      </paragraph>
      <list>
       <list-item label="•">
        We provide a domain analysis tool for optimising the generation of state variables from propositions and actions (both instantaneous and durative). This results in more compact encodings than related techniques (see Sections 10.1 and 10.2). Succinct domain representations often benefit the performance of planners (see Section 10.3).
       </list-item>
       <list-item label="•">
        We offer a technique that can be used as a debugging tool for temporal planning domains. As these types of domains are particularly challenging to encode, especially when large and complex, a rigorous debugging process is crucial in producing correct representations of the systems under consideration (see Example 19).
       </list-item>
      </list>
     </section>
     <section label="1.3">
      <section-title>
       Organisation of the paper
      </section-title>
      <paragraph>
       This paper is organised as follows. After presenting PDDL2.1, our input language, in Section 2, we formally introduce the notion of invariance in Section 3.
      </paragraph>
      <paragraph>
       Sections 4, 5 and 6 are devoted to a detailed analysis of actions at the ground level. In particular, Section 4 focuses on instantaneous actions: the fundamental concept of strong safety is introduced and analysed and a first sufficient result for invariance, Corollary 23, is established. Section 5 analyses sequences of actions and, in particular, durative actions (seen as a sequence of three instantaneous actions) for which two new concepts of safety are formulated and investigated: individual and simple safety. Our main technical results are presented in Section 6 and consist of Theorem 51, Theorem 53 and Corollary 58: these results ensure invariance under milder safety requirements on the durative actions than Corollary 23. This is obtained by adding requirements that prevent the intertwinement of durative actions that are not strongly safe.
      </paragraph>
      <paragraph>
       Sections 7 and 8lift the concepts and results obtained in the previous sections to the level of action schemas. In particular, Section 7 deals with the problem of lifting the concept of strong safety for instantaneous schemas, while Section 8 considers durative action schemas and presents the lifted version of our main results, Corollary 92, Corollary 97, Corollary 98.
      </paragraph>
      <paragraph>
       These results are the basic ingredients of our algorithm to find invariants, which we present in Section 9. Section 10 reports an extensive experimental evaluation of our approach against the domains of all the temporal IPCs. Sections 11 and 12 conclude the paper with a description of related works and closing remarks. There are four appendices, Appendix A PDDL2.1 specification of the, Appendix B PDDL2.1 specification of the, Appendix C PDDL2.1 specification of the, Appendix D PDDL2.1 specification of the, that contain the specifications of the planning domains used as the running examples in the paper.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Canonical form of planning tasks
     </section-title>
     <paragraph>
      In this work, we consider planning instances that are expressed in PDDL2.1 [21]. However, before applying our algorithm to find invariants, we manipulate the domain to enforce a regular structure in the specification of the action schemas. In Section 2.1, we give a detailed account of this canonical form that we use and then, in Section 2.2, we describe how such a form can be obtained starting from a domain expressed in PDDL2.1.
     </paragraph>
     <section label="2.1">
      <section-title>
       PDDL canonical form
      </section-title>
      <paragraph>
       Let us consider a first order language {a mathematical formula}L with a denumerable set of individual variable symbols {a mathematical formula}V={v1,v2,…} and a signature that has a denumerable set of constants{a mathematical formula}K={k1,k2,…} and a denumerable set of relation symbols {a mathematical formula}Z, where each {a mathematical formula}r∈Z is associated with a positive integer called arity and indicated as {a mathematical formula}arity(r).
      </paragraph>
      <paragraph>
       Given the language {a mathematical formula}L, a planning instance is a tuple {a mathematical formula}I=(D,P), where {a mathematical formula}D is a planning domain and {a mathematical formula}P a planning problem. The domain {a mathematical formula}D=(R,Ai,Ad) is a 3-tuple consisting of finite sets of relation symbols {a mathematical formula}R⊆Z, instantaneous and durative actions. The problem {a mathematical formula}P=(O,Init,G) is a triple consisting of the objects {a mathematical formula}O⊆K, the initial logical state and the logical goal specification.
      </paragraph>
      <paragraph>
       The ground atoms of the planning instance, Atms, are the (finitely many) atomic formulas formed by applying the relations in {a mathematical formula}R to the objects in {a mathematical formula}O (respecting arities). A logical state is any subset of Atms. Considering a logical state s, we denote with {a mathematical formula}sc its complement: {a mathematical formula}sc=Atms∖s. {a mathematical formula}S=2Atms denotes the set of logical states. The initial logical state can be chosen arbitrarily: {a mathematical formula}Init∈S. A logical goal specification is any choice of a desired set of final logical states: {a mathematical formula}G⊆S. It is typical to restrict to considering goals only of the form {a mathematical formula}G={S|C⊆S∈S} for some conjunction of atoms {a mathematical formula}C⊆Atms.
      </paragraph>
      <paragraph>
       A state is a tuple in {a mathematical formula}R×S, where the first value is the time of the state and the second value (logical state) is a subset of Atms. The initial state for the planning instance {a mathematical formula}I is, implicitly, of the form {a mathematical formula}(t0,Init) where {a mathematical formula}t0, the beginning of the plan execution time, will always take the value {a mathematical formula}t0=0 in this paper, which is also the convention used in the IPC benchmarks.{sup:1}
      </paragraph>
      <paragraph>
       The set {a mathematical formula}Ai is a collection of instantaneous action schemas. An instantaneous action schema α is composed of the following sets:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Vα⊆V, the distinct schema's variables;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Preα+, the positive preconditions;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Preα−, the negative preconditions;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Effα+, the add effects;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Effα−, the delete effects.
       </list-item>
      </list>
      <paragraph>
       If the schema α is clear in context we drop the subscript. For convenience, we also define:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Preα=Preα+∪Preα−;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Effα=Effα+∪Effα−
       </list-item>
      </list>
      <paragraph>
       Preconditions and effects are sets of formulas l of the form: {a mathematical formula}(∀v1,…,vk:q) where:
      </paragraph>
      <list>
       <list-item label="•">
        q is an atomic formula: {a mathematical formula}q=r(v1′,…,vn′) with {a mathematical formula}r∈R and {a mathematical formula}arity(r)=n≥k;
       </list-item>
       <list-item label="•">
        {a mathematical formula}{v1,…,vk}⊆{v1′,…,vn′}⊆V are the quantified variables in l;
       </list-item>
       <list-item label="•">
        {a mathematical formula}{v1′,…,vn′}∖{v1,…,vk}⊆Vα are the schema's variables in l.
       </list-item>
      </list>
      <paragraph>
       The universal quantification can be trivial (i.e. quantification over zero variables) and, in this case, it is omitted. Note that we do not allow repeated arguments in the specification of a schema and all the formulas that appear in the preconditions and effects are positive. The representation is untyped.
      </paragraph>
      <paragraph>
       Given a formula l of the form {a mathematical formula}(∀v1,…,vk:q), we indicate the sets of the positions of its free and quantified variables (starting with zero and in the order they appear in q) respectively as {a mathematical formula}VarF[l] and {a mathematical formula}VarQ[l]. For example, if {a mathematical formula}l=(∀x,z:f(x,y,z,k)), we have: {a mathematical formula}VarQ[l]={0,2} and {a mathematical formula}VarF[l]={1,3}. Let {a mathematical formula}Rel[l]=〈r/k〉 denote the relation symbol r of arity k that appears in the atomic formula q. In our example, {a mathematical formula}Rel[l]=f/4. Considering a position {a mathematical formula}i∈VarF[l] , we indicate the corresponding variable as {a mathematical formula}Var[i,l]. For instance, {a mathematical formula}Var[2,l]=z.
      </paragraph>
      <paragraph>
       The set {a mathematical formula}Ad is a collection of durative action schemas. A durative action schema Dα is a triple of instantaneous action schemas {a mathematical formula}Dα=(αst,αinv,αend) with a common set of variables {a mathematical formula}VDα (i.e. {a mathematical formula}VDα=Vαst=Vαinv=Vαend) and with {a mathematical formula}αinv having no effects (i.e. {a mathematical formula}Effαinv=∅). We indicate as {a mathematical formula}{Dα} the set {a mathematical formula}{αst,αinv,αend}.
      </paragraph>
      <paragraph>
       We call {a mathematical formula}A the set of all the instantaneous action schemas in the domain, including those induced by durative actions: {a mathematical formula}A=Ai∪⋃Dα∈Ad{Dα}. Consider any two action schemas {a mathematical formula}α1 and {a mathematical formula}α2 in {a mathematical formula}A such that there does not exist a durative action Dα with both {a mathematical formula}α1 and {a mathematical formula}α2 in {a mathematical formula}{Dα}. We assume that the variables of {a mathematical formula}α1 and {a mathematical formula}α2 are disjoint sets,{sup:2} i.e. {a mathematical formula}Vα1∩Vα2=∅.
      </paragraph>
      <paragraph>
       Given an action schema {a mathematical formula}α∈Ai with variables {a mathematical formula}Vα, consider a grounding function {a mathematical formula}gr:Vα→O that maps the schema's variables in α to the problem's objects {a mathematical formula}O. The function gr induces a function on the formulas in α as follows. Take a formula l that appears in α. We call {a mathematical formula}gr˜(l) the formula that is obtained from l by substituting the schema's variables in l with objects in {a mathematical formula}O according to gr. We call {a mathematical formula}gr(l) the set of ground atoms obtained from {a mathematical formula}gr˜(l) by substituting each quantified variable in l with objects in {a mathematical formula}O in all possible ways. Note that, when there are no quantified variables, {a mathematical formula}{gr˜(l)}=gr(l) and they are singletons. For a set L containing formulas {a mathematical formula}l1,…,ln, we call {a mathematical formula}gr˜(L)={gr˜(l1),…,gr˜(ln)} and {a mathematical formula}gr(L)=gr(l1)∪…∪gr(ln). We call {a mathematical formula}gr˜(α) the action schema obtained from α by grounding each formula l that appears in α according to gr and {a mathematical formula}gr(α) the ground action that is obtained from {a mathematical formula}gr˜(α) by replacing the quantified variables with the set of ground atoms formed by substituting objects in {a mathematical formula}O for the quantified variables in all possible ways.
      </paragraph>
      <paragraph>
       Considering a durative action schema {a mathematical formula}Dα∈Ad and a grounding function gr, the ground durative action {a mathematical formula}gr(Dα) is obtained by applying gr to the instantaneous fragments of Dα, i.e. {a mathematical formula}gr(Dα)=(gr(αst),gr(αinv),gr(αend)). Note that we cannot apply different grounding functions to different parts of a durative action schema.
      </paragraph>
      <paragraph>
       We indicate the positive and negative preconditions of an instantaneous ground action a as {a mathematical formula}Prea± and its add and delete effects as {a mathematical formula}Effa±. We also put {a mathematical formula}Prea=Prea+∪Prea− and {a mathematical formula}Effa=Effa+∪Effa−. Ground actions obtained by grounding different action schema are always assumed to be distinct even in the case they might have the same preconditions and effects. In particular, two different durative actions always have distinct start and end fragments. Such fragments are also distinct from any other instantaneous action. We call {a mathematical formula}GAi and {a mathematical formula}GAd, respectively, the set of instantaneous and durative ground actions. Finally, we call {a mathematical formula}GA the set of all ground actions in {a mathematical formula}I (obtained from grounding all schemas in {a mathematical formula}A).
      </paragraph>
      <paragraph>
       For the sake of simplicity, from now on we will call a ground action simply an action, while at the lifted level we will use the term action schema. Moreover, the term instantaneous will be dropped, whenever this does not cause any ambiguity, assuming that actions and action schemas without the appellative durative are always instantaneous.
      </paragraph>
      <paragraph>
       An action a is applicable in a logical state s if {a mathematical formula}Prea+⊆s and {a mathematical formula}Prea−∩s=∅. We denote by {a mathematical formula}Sa the set of states on which a is applicable. The result of applying a in s is the state {a mathematical formula}s′ such that {a mathematical formula}s′=(s∖Effa−)∪Effa+. We call ξ this transition function: {a mathematical formula}s′=ξ(s,a).
      </paragraph>
      <paragraph>
       The transition function ξ can be generalised to a finite set of actions A to be executed simultaneously: {a mathematical formula}s′=ξ(s,A). However, in order to handle simultaneous actions, we need to introduce the so-called no moving targets rule: no two actions can simultaneously make use of a value if one of the two is accessing the value to update it. The value is a moving target for the other action to access. This rule avoids conflicting effects, but also applies to the preconditions of an action: no concurrent actions can affect the parts of the state relevant to the precondition tests of other actions in the set (regardless of whether those effects might be harmful or not). In formula, two actions a and b are non-interfering if:{a mathematical formula} If two actions are not non-interfering, they are mutex.
      </paragraph>
      <paragraph>
       In this work, whenever we consider a set of simultaneous actions A, we implicitly assume that the component actions are pairwise non-interfering. Moreover, we define{a mathematical formula} We say that A is applicable in a state s if each component {a mathematical formula}a∈A is applicable in s. The set of states on which A is applicable is thus {a mathematical formula}SA={s|PreA+⊆s,PreA−⊆sc}. Given {a mathematical formula}s∈SA, the transition function {a mathematical formula}s′=ξ(s,A) is defined as follows:{a mathematical formula} We say that A is executable if {a mathematical formula}SA≠∅ or, equivalently, if{a mathematical formula} Sets of actions that are not executable do not play any role in our analysis as they will never appear in executable plans (see below for the exact definition). For this reason, in our analysis, we always restrict consideration to executable sets of actions. This implies, in particular, that each single action a that we consider satisfies the condition {a mathematical formula}Prea+∩Prea−=∅.
      </paragraph>
      <paragraph>
       The following result shows that the application of a set of actions can always be serialised.
      </paragraph>
      <paragraph label="Proposition 1">
       SerialisabilityConsider a set of pairwise non-interfering actions A and a logical state{a mathematical formula}s∈SA. Let{a mathematical formula}σ:{1,…,n}→Abe any permutation of A and consider the sequence of states recursively defined as{a mathematical formula}s0=sand{a mathematical formula}sk=ξ(sk−1,σ(k))for{a mathematical formula}k=1,…,n. Then,
      </paragraph>
      <list>
       <list-item>
        Each{a mathematical formula}σ(k)is applicable in{a mathematical formula}sk−1(so each{a mathematical formula}skis well-defined):{a mathematical formula}Preσ(k)+⊆sk−1and{a mathematical formula}Preσ(k)−∩sk−1=∅.
       </list-item>
       <list-item>
        The final logical state coincides with the state that is obtained by applying the set A, namely{a mathematical formula}sn=ξ(s0,A).
       </list-item>
      </list>
      <paragraph label="Proof">
       The action {a mathematical formula}σ(1) is applicable in {a mathematical formula}s0 by definition. Assuming that {a mathematical formula}σ(j) is applicable in {a mathematical formula}sj−1 for {a mathematical formula}j=1,…,k, we now show that {a mathematical formula}σ(k+1) is applicable in {a mathematical formula}sk. Note that from the definition of transition function ξ for single actions {a mathematical formula}sk=(s0∖⋃j=1kEffσ(j)−)∪⋃j=1kEffσ(j)+. Since {a mathematical formula}Preσ(k+1)+⊆s0 and {a mathematical formula}Preσ(k+1)−∩s0=∅ by assumption and {a mathematical formula}σ(k+1) is not interfering with {a mathematical formula}σ(1), {a mathematical formula}σ(2),…,σ(k), we have that {a mathematical formula}Preσ(k+1)+⊆sk and {a mathematical formula}Preσ(k+1)−∩sk=∅. Also, note that: {a mathematical formula}sn=(s0∖⋃j=1nEffσ(j)−)∪⋃j=1nEffσ(j)+=ξ(s,A).  □
      </paragraph>
      <paragraph>
       An instantaneous timed action has the following syntactic form: {a mathematical formula}(t,a), where t is a positive rational number in floating point syntax and a is an action. A durative timed action has the following syntactic form: {a mathematical formula}(t,Da[t′]), where t is a rational valued time point, Da is a durative action and {a mathematical formula}t′ is a non-negative rational-valued duration. It is possible for multiple timed actions to be given the same time stamp, indicating that they should be executed concurrently.
      </paragraph>
      <paragraph>
       Given a planning instance {a mathematical formula}I, a plan Π consists of a finite set of (instantaneous and durative) timed actions. The happening time sequence{a mathematical formula}{ti}i=0,…,k¯ for a plan Π is: {a mathematical formula}{t|(t,a)∈Π or {a mathematical formula}(t,Da[t′])∈Π or {a mathematical formula}(t−t′,Da[t′])∈Π}.
      </paragraph>
      <paragraph>
       The simple planπ induced by a plan Π is the set of instantaneous timed actions such that:
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}(t,a)∈π for each {a mathematical formula}(t,a)∈Π, where a is an action;
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}(t,ast)∈π and {a mathematical formula}(t+t′,aend)∈π for all {a mathematical formula}(t,Da[t′])∈Π, where Da is a durative action;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}((ti+ti+1)/2,ainv)∈π for each {a mathematical formula}(t,Da[t′])∈Π and for each i such that {a mathematical formula}t≤ti&lt;(t+t′), where {a mathematical formula}ti and {a mathematical formula}ti+1 are in the happening time sequence for Π.
       </list-item>
      </list>
      <paragraph>
       For each durative action {a mathematical formula}(t,Da[t′]) in Π, the simple plan π contains the instantaneous timed actions {a mathematical formula}(t,ast) and {a mathematical formula}(t+t′,aend) as well as, midway between them, the instantaneous timed action {a mathematical formula}((ti+ti+1)/2,ainv). A plan Π and its corresponding induced simple plan π is admissible if concurrent instantaneous actions are non-interfering between each other and actions happening inside a durative action {a mathematical formula}Da=(ast,ainv,aend) are non-interfering with the action {a mathematical formula}ainv. More precisely, if
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}(t,a),(t,b)∈π imply that a and b are non-interfering.
       </list-item>
       <list-item label="•">
        {a mathematical formula}(t,Da[t′])∈Π and {a mathematical formula}(s,b)∈π for some time {a mathematical formula}s∈(t,t+t′) imply that {a mathematical formula}ainv and b are non-interfering.
       </list-item>
      </list>
      <paragraph>
       The happening time sequence{a mathematical formula}{ti}i=0,…,k¯ for a plan π is: {a mathematical formula}{t0}∪{t|(t,a)∈π}. The happening at time t of the plan π is defined as {a mathematical formula}At={a∈GA|(t,a)∈π}. Clearly, {a mathematical formula}At≠∅ iff t is in the happening time sequence. The sequence of action sets {a mathematical formula}Aπ=(At0,…,Atk¯) is called the happening sequence of π.
      </paragraph>
      <paragraph>
       An admissible simple plan π for a planning instance {a mathematical formula}I is executable if, given its happening time sequence {a mathematical formula}{ti}i=0…k¯, there is a sequence of logical states {a mathematical formula}{si}i=0…k¯ such that {a mathematical formula}s0=Init and for each {a mathematical formula}i=0,…,k, {a mathematical formula}si+1 is the result of executing the happening at time {a mathematical formula}ti in π. Formally, we have that {a mathematical formula}Ati+1 is applicable in {a mathematical formula}si and {a mathematical formula}si+1=ξ(si,Ati+1). The state {a mathematical formula}sk¯ is called the final logical state produced by π. The sequence of times and states {a mathematical formula}{Si=(ti,si)i=0…k} is called the (unique) trace of π, {a mathematical formula}trace(π). Two simple plans are said to be equivalent if they give rise to the same trace. We call {a mathematical formula}Plans all the executable simple plans for {a mathematical formula}I and we call {a mathematical formula}Sr the union of all the logical states that appear in the traces associated with the plans in {a mathematical formula}Plans: {a mathematical formula}Sr={s|π∈Plans,(t,s)∈trace(π)}. Note that {a mathematical formula}Sr⊆S. We call the states in {a mathematical formula}Srreachable states. Finally, an executable simple plan for a planning instance {a mathematical formula}I is valid if it produces a final state {a mathematical formula}sk¯∈G.
      </paragraph>
      <paragraph>
       Note that in the passage from the original plan Π to the simple plan π we have formally lost the coupling among the start and end fragments of durative actions. Since in certain cases this information is necessary, we set a definition: a durative action Da is said to happen in π in the time interval {a mathematical formula}[t,t+t′] whenever this holds true in the original plan Π, namely when {a mathematical formula}(t,Da[t′])∈Π. It will also be convenient to make the following assumption. Whenever two durative timed actions {a mathematical formula}(t1,Da1[t1′]){a mathematical formula}(t2,Da2[t2″]) either start at the same point {a mathematical formula}t1=t2 or end at the same point {a mathematical formula}t1+t1′=t2+t2′, in a plan Π, but have different durations {a mathematical formula}t1′≠t2′, the constituent durative actions are different: {a mathematical formula}Da1≠Da2. This entails no loss of generality. In fact, if {a mathematical formula}Da1 and {a mathematical formula}Da2 are different, this is obvious. If not, we can always create multiple copies of the same durative action with different labels: they have the same preconditions and effects in each fragment but have a different name. Durative actions of this type are called equivalent. Note, finally, that if two equivalent durative actions {a mathematical formula}Da1 and {a mathematical formula}Da2 appear in a plan with the same starting point and duration, {a mathematical formula}(t,Da1[t′]),(t,Da2[t′])∈Π, we can get rid of one of them and obtain an equivalent simple plan. For this reason, we assume from now on that the plans considered are free from such simultaneous happening of equivalent durative actions.
      </paragraph>
      <paragraph>
       All concepts and results presented in this paper will not take into consideration the goal {a mathematical formula}G. They will be concerned with the family {a mathematical formula}Plans of all executable plans and not just the valid ones. Moreover, it will be convenient to think of Init as a parameter taking all possible values in {a mathematical formula}S, as our results will be universally quantified with respect to it. Whenever in this paper we fix an instance {a mathematical formula}I, we think of a family of instances parameterised by all possible Init and {a mathematical formula}G.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       From PDDL2.1 to canonical PDDL
      </section-title>
      <paragraph>
       We build the canonical form described above starting from PDDL2.1 instances, which are characterised by numeric and temporal information [21]. We do not consider numeric expressions in our canonical form. We could potentially exploit metric information to find additional invariants, but currently we do not do that. Instead, we ignore the numeric expressions in the domain and focus only on its logical and temporal structure. Setting numeric expressions aside has several consequences: we eliminate numeric constraints from the actions' specification, the actions' preconditions and effects do not depend on the duration and actions' durations become the interval {a mathematical formula}(0,+∞) in the rational numbers. Note that, crucially, the invariants that we find for the domain without numeric constraints are also invariants for the original domain since, in removing them, we are only expanding the set of possible valid plans.
      </paragraph>
      <paragraph>
       Temporal information is handled in PDDL2.1 by means of durative actions. They can be either discretised or continuous, but we focus on discretised durative actions here. They have a duration field and temporally annotated conditions and effects.
      </paragraph>
      <paragraph>
       The duration field contains temporal constraints involving terms composed of arithmetic expressions and the dedicated variable {a mathematical formula}duration. As already mentioned above, we ignore numeric constraints and consequently the specific durations of the actions, which we substitute with the interval {a mathematical formula}(0,+∞). Such precise durations are irrelevant to our technique. We care about the possible intertwinement between durative actions, which can be studied without considering the exact durations.
      </paragraph>
      <paragraph>
       The annotation of a condition makes explicit whether the associated proposition must hold at the start of the interval (the point at which the action is applied), the end of the interval (the point at which the final effects are asserted) or over all the interval (open at both ends) from the start to the end (invariant over the duration of the action). The annotation of an effect makes explicit whether the effect is immediate (it happens at the start of the interval) or delayed (it happens at the end of the interval). No other time points are accessible. Logical changes are considered to be instantaneous and can only happen at the accessible points. To build our canonical form, we transform durative actions into triples of instantaneous actions. We do this in such a way that we do not change the set of plans that can be obtained for any goal specification. Plans with durative actions, in fact, are always assigned a semantics in terms of the semantics of simple plans [21], as explained in the previous section.
      </paragraph>
      <paragraph>
       Let us see now in more detail how we obtain the PDDL canonical form from PDDL2.1 instances. PDDL2.1 is a typed representation. We compile away types: for each type that occurs in the domain, we introduce a new unary relation with the same name. For example, the Floortile domain contains the type robot, tile and color and so we introduce three new unary relations: {a mathematical formula}〈robot,1〉, {a mathematical formula}〈tile,1〉, and {a mathematical formula}〈color,1〉. We use such relations in the specification of the initial state, where we list the objects of the planning instance, and in the specification of the actions. For each typed variable that appears in an action, we specify it without giving its type, but then we introduce a new precondition in the action that associates the variable to its corresponding unary relation. We follow the same procedure described in Helmert [33], which can be consulted for further details.
      </paragraph>
      <paragraph>
       In a PDDL2.1 domain, instead of {a mathematical formula}Ai and {a mathematical formula}Ad, we find a set {a mathematical formula}Aa that contains both instantaneous and durative action schemas, which have the following characteristics. Durative action schemas have temporally annotated conditions and effects, which we indicate as {a mathematical formula}Prepx and {a mathematical formula}Effpy, where {a mathematical formula}p∈{+,−}, {a mathematical formula}x∈{st,inv,end}, and {a mathematical formula}y∈{st,end}. For an action schema in {a mathematical formula}Aa (durative or not), the condition formula can be a relation, a negation, a conjunction or disjunction of relations or a quantified formula on relations. The effect formula can be a relation, a negation or a conjunction of relations, a universally quantified formula on relations or a conditional effect formula, which is a tuple formed by a precondition formula and effect formula. We manipulate the action schemas in {a mathematical formula}Aa to obtain {a mathematical formula}Ai and {a mathematical formula}Ad, where each action schema in these sets has the canonical form described in Section 2.1.
      </paragraph>
      <paragraph>
       First, we eliminate conditional effects and existentially quantified formulae through an operation referred to as flattening (see Fox and Long [21] for details). These features can be eliminated by applying syntactic transformations with the resulting schemas being equivalent to the original ones. This procedure can potentially lead to an exponential blow-up of the task description.
      </paragraph>
      <paragraph>
       Given a flattened action schema α, we take the formulas (temporally annotated or not) in its conditions and effects and normalise them by using the algorithm introduced by Helmert [33]. (We refer the interested reader to this paper for a full description of the normalisation process.) Our normalisation differs from Helmert [33] only in that we initially eliminate conditional effects by applying the flattening operation before normalisation and we keep universal quantification in the preconditions. We also apply normalisation not only to formulas appearing in instantaneous actions as in Helmert [33], but also to temporally annotated formulas in durative actions. We normalise the formulas and leave the temporal annotation unchanged. After normalisation, all action schema conditions and effects become sets of formulas l of the form {a mathematical formula}∀v1,…,vk:q, where q is an atomic formula and the quantification can be trivial. We indicate by {a mathematical formula}Preα+ and {a mathematical formula}Effα+ the set of positive formulas that appear positive in α and by {a mathematical formula}Preα− and {a mathematical formula}Effα− the set of positive formulas that appear negative in α.
      </paragraph>
      <paragraph>
       After flattening and normalisation, we transform the durative action schemas in {a mathematical formula}Aa into triples of instantaneous action schemas. For each durative action {a mathematical formula}Dα∈Aa, we create two instantaneous action schemas that correspond to the end points of Dα, {a mathematical formula}αst and {a mathematical formula}αend, and one that corresponds to the invariant conditions that must hold over that duration of Dα, {a mathematical formula}αinv. More formally, for a durative action schema Dα, we create {a mathematical formula}αst, {a mathematical formula}αinv and {a mathematical formula}αend as indicated in Table 2.
      </paragraph>
      <paragraph>
       At this point, we are ready to construct {a mathematical formula}Ai and {a mathematical formula}Ad from {a mathematical formula}Aa. We add each flattened and normalised instantaneous action in {a mathematical formula}Aa to {a mathematical formula}Ai. For each durative action {a mathematical formula}Dα∈Aa, after applying flattening and normalisation, we create the corresponding tuple {a mathematical formula}(αst,αinv,αend) and add it to {a mathematical formula}Ad.
      </paragraph>
      <paragraph>
       Consider a planning instance {a mathematical formula}I in canonical form obtained from a PDDL2.1 instance {a mathematical formula}I′ and a valid plan Π for {a mathematical formula}I. Π can be converted into an equivalent valid plan {a mathematical formula}Π′ for {a mathematical formula}I′.
      </paragraph>
     </section>
     <section label="2.3">
      Running example: the Floortile domain
      <paragraph>
       We use the Floortile domain as our running example. It has been introduced in the IPC'14 and then reused in 2015. The full PDDL2.1 specification is available in Appendix A. The domain describes a set of robots that use different colours to paint patterns in floor tiles. The robots can move around the floor tiles in four directions (up, down, left and right). Robots paint with one color at a time, but can change their spray guns to any available color. Robots can only paint the tile that is in above (up) and below (down) them, and once a tile has been painted no robot can stand on it.
      </paragraph>
      <paragraph>
       We have the following relations in this domain: {a mathematical formula}R={up,down,right,left,robotAt,robotHas,painted,clear,availableColor}. They have arity two, except for the last two, which have arity one. availableColor indicates whether a colour gun is available to be picked by a robot and up, down, right, left indicate the respective positions of two tiles. As we will automatically infer via our invariant synthesis (see Example 1), the relation clear in this context means not only that a tile is still unpainted, but also that it is not being painted and is unoccupied.
      </paragraph>
      <paragraph>
       The set of instantaneous action schemas {a mathematical formula}Ai is empty, while the set of durative action schemas {a mathematical formula}Ad is: {a mathematical formula}Ad={changeColor,paintUp,paintDown,up,down,right,left}.
      </paragraph>
      <paragraph>
       As an example, the durative action schema paintUp corresponds to the following triple: ({a mathematical formula}paintUpst, {a mathematical formula}paintUpinv, {a mathematical formula}paintUpend), where the single instantaneous action schemas have the specifications as shown in Table 3.
      </paragraph>
      <paragraph>
       Note that the triple of single instantaneous action schemas in canonical form is obtained from the following PDDL2.1 specification:
      </paragraph>
      <paragraph>
       {a mathematical formula}
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Mutual exclusion invariants and templates
     </section-title>
     <paragraph>
      In this section, we formally introduce the concept of mutual exclusion invariant and give examples of them.
     </paragraph>
     <paragraph>
      In the PDDL2.1 language, an invariant of a planning instance is a property of the world states such that when it is satisfied in the initial state Init, it is satisfied in all reachable states {a mathematical formula}Sr. For example, for the {a mathematical formula}Floortile domain, a trivial invariant says that for each object x, if x is a robot, then x is not a tile. Similar invariants hold for each type defined in the original PDDL domain. A more interesting invariant says that, for any two objects x and y, if up(x,y) holds, then down(y,x) holds too, but down(x,y) does not. It is possible to identify several invariants for the {a mathematical formula}Floortile domain, ranging from trivial invariants such as those involving type predicates to very complex invariants.
     </paragraph>
     <paragraph label="Definition 2">
      In this paper, we focus on mutual exclusion invariants, which state that a set of ground atoms can never be true at the same time. From now on we assume we have fixed a planning instance {a mathematical formula}I in PDDL canonical form. Mutual exclusion invariantA set of ground atoms {a mathematical formula}Z∈S is a mutual exclusion invariant set when, if at most one element of Z is true in the initial state, then at most one element of Z is true in any reachable state, namely{a mathematical formula} We abuse the distinction between the set Z and a formula such as {a mathematical formula}⋀x,y∈Z¬x∨¬y and call Z a mutual exclusion invariant directly and, for brevity, an invariant.
     </paragraph>
     <paragraph label="Example 1">
      Floortile domainA mutual exclusion invariant for this domain states that two ground atoms indicating the position of a robot identified as rbt1, such as robotAt(rbt1,tile1) and robotAt(rbt1,tile2), can never be true at the same time. Intuitively, this means that rbt1 cannot be in two different positions simultaneously. Another more complex invariant states that, given a tile tile1, a robot rbt1 and a colour clr1, atoms of the form clear(tile1), robotAt(rbt1, tile1) and painted(tile1,clr1) can never be true at the same time. This means that a tile can be in one of four possible states: not yet painted (clear), already painted, occupied by a robot that is painting an adjacent tile or none of the preceding (which can only be because the tile is being painted).
     </paragraph>
     <paragraph>
      Although we aim to find sets of mutually exclusive ground atoms, we often work with relations and action schemas to control complexity. A convenient and compact way for indicating several invariant sets at the same time involves using invariant templates, which are defined below, after introducing a few preliminary definitions.
     </paragraph>
     <paragraph label="Definition 3">
      ComponentA componentc is a tuple {a mathematical formula}〈r/k,p〉, where r is a relation symbol in {a mathematical formula}R of arity {a mathematical formula}k=arity(r) and {a mathematical formula}p∈{0,…,k}.
     </paragraph>
     <paragraph>
      Take a component {a mathematical formula}c=〈r/k,p〉 and a set of variables {a mathematical formula}v0,…,vk−1 and consider the atomic formula {a mathematical formula}m=r(v0,…,vk−1). When {a mathematical formula}p≤k−1, the number p in c represents the position of one of the variables of m, which we call the counted variable. When {a mathematical formula}p=k, there are no counted variables. The set of the fixed variables of c is formally defined as {a mathematical formula}Fc={(c,i)|i=0,…,k−1;i≠p}. We define the set of fixed variables of a set of components {a mathematical formula}C={c1,c2,…,cn} as {a mathematical formula}FC=⋃c∈CFc.
     </paragraph>
     <paragraph label="Definition 4">
      Admissible partitionGiven a set of components {a mathematical formula}C and corresponding set of fixed variables {a mathematical formula}FC, an admissible partition of {a mathematical formula}FC is a partition {a mathematical formula}FC={G1,…,Gs} such that {a mathematical formula}|Gj∩Fc|=1 for each {a mathematical formula}c∈C.
     </paragraph>
     <paragraph>
      If two elements {a mathematical formula}(c1,i) and {a mathematical formula}(c2,j) of {a mathematical formula}FC belong to the same set of the partition {a mathematical formula}FC, we use the notation: {a mathematical formula}(c1,i)∼FC(c2,j).
     </paragraph>
     <paragraph label="Remark 5">
      Note that the existence of an admissible partition of {a mathematical formula}FC implies that all the components in {a mathematical formula}C have the same number of fixed variables, which is also the number of the sets in the partition. In the special case in which the number of fixed variables in each component is equal to one, there is just one admissible (trivial) partition {a mathematical formula}FC={FC}.
     </paragraph>
     <paragraph label="Definition 6">
      TemplateA template{a mathematical formula}T is a pair {a mathematical formula}(C,FC) such that {a mathematical formula}C is a set of components and {a mathematical formula}FC is an admissible partition of {a mathematical formula}FC. We simply write {a mathematical formula}T=(C) when the partition is trivial, i.e. {a mathematical formula}FC={FC}.
     </paragraph>
     <paragraph label="Definition 7">
      Template instanceGiven objects {a mathematical formula}O and template {a mathematical formula}T=(C,FC), an instance{a mathematical formula}γ:FC→O of {a mathematical formula}T maps (all the elements of) each part of its partition to the same object, that is {a mathematical formula}γ(ca,i)=γ(cb,j) if and only if {a mathematical formula}(ca,i)∼FC(cb,j) for all {a mathematical formula}(ca,i),(cb,j)∈C.
     </paragraph>
     <paragraph label="Definition 8">
      Template instantiationThe instantiation of {a mathematical formula}T according to instance γ, {a mathematical formula}γ(T), is the set of ground atoms in {a mathematical formula}2Atms obtained as follows: for each component {a mathematical formula}c=〈r/k,p〉 of {a mathematical formula}T, take the relation symbol r, for each element {a mathematical formula}(c,i)∈Fc bind the variable in position i according to {a mathematical formula}γ(c,i) and the counted variable in position p to all the objects {a mathematical formula}O. In formula,{a mathematical formula}
     </paragraph>
     <paragraph>
      Instances are interesting because they can be used to reason about their (exponentially larger) instantiations without, in fact, constructing those instantiations.
     </paragraph>
     <paragraph>
      Considering a template {a mathematical formula}T and an instance γ, if the ground atoms in the instantiation of {a mathematical formula}T according to γ are mutually exclusive in the initial state Init and remain so in any reachable state {a mathematical formula}s∈Sr, then {a mathematical formula}γ(T) is (by definition) a mutual exclusion invariant set. A template with this property for each possible instantiation γ is called an invariant template.
     </paragraph>
     <paragraph label="Definition 9">
      Invariant templateA template {a mathematical formula}T is an invariant template if, for each instance γ, the instantiation of {a mathematical formula}T according to γ is a mutual exclusion invariant set.
     </paragraph>
     <paragraph>
      Given an invariant template {a mathematical formula}T, we can create one state variable for each of its instances. The domains of these variables are the corresponding mutual exclusion invariant sets with an additional null value, which is used when no element in the mutual exclusion invariant set is true.
     </paragraph>
     <paragraph>
      Before describing in what situations we can feasibly prove that a template is invariant, we introduce a final concept:
     </paragraph>
     <paragraph label="Definition 10">
      Template instance's weightTake an instance γ of template {a mathematical formula}T with instantiation {a mathematical formula}γ(T). The weight{a mathematical formula}w(γ,s) of γ in state s is the number of ground atoms of its instantiation true in s:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      A template{a mathematical formula}Tis invariant if and only if, for each instance γ of{a mathematical formula}Twith instantiation{a mathematical formula}γ(T), if{a mathematical formula}w(γ,Init)≤1, then{a mathematical formula}w(γ,s)≤1for each state{a mathematical formula}s∈Sr.It follows from Definition 9, Definition 10.  □
     </paragraph>
     <paragraph label="Example 2">
      Floortile domainA template for this domain is {a mathematical formula}Tft=({c1,c2,c3}), where:
      <list>
       {a mathematical formula}c1=〈robotAt/2,0〉 is the first component. It includes the relation robotAt that has an arity of two (i.e. the relation {a mathematical formula}robotAt(robot,tile) has two variables) and the variable in position zero, i.e. robot, is the counted variable. The remaining variable, tile, which is in position one, is the fixed variable: {a mathematical formula}Fc1={(c1,1)}.{a mathematical formula}c2=〈painted/2,1〉 is the second component with {a mathematical formula}Fc2={(c2,0)}.{a mathematical formula}c3=〈clear/1,1〉 is the last component with {a mathematical formula}Fc3={(c3,0)}.For this example, because each component has only one fixed argument, there is only one admissible partition – the trivial one – that places all components together:
      </list>
      <paragraph>
       {a mathematical formula}Assume that we have a problem {a mathematical formula}P with two robots rbt1 and rbt2, three tiles, tile1, tile2 and tile3 and one colour black. Consider one possible instance {a mathematical formula}γ1 such that {a mathematical formula}γ1(c1,1)=γ1(c2,0)=γ1(c3,0)=tile1. The instantiation of the template {a mathematical formula}Tft according to {a mathematical formula}γ1 is: {an inline-figure}. The weight of the instance {a mathematical formula}γ1 in some state s is how many of the atoms in {a mathematical formula}γ1(Tft) are true in s. For example, {a mathematical formula}w(γ1,s0)=1 for the plausible initial state {an inline-figure}, because the intersection of the state {a mathematical formula}s0 and the instantiation {a mathematical formula}γ1(Tft) contains just clear(tile1).We will see that we can actually prove that {a mathematical formula}Tft is an invariant, which states that any given tile (e.g., tile1 for the instance/instantiation {a mathematical formula}γ1) satisfies at most one of: (1) clear, (2) painted a colour, or (3) occupied by a robot. Hence, for the problem {a mathematical formula}P, we can create three state variables that represent each of the three tiles. The domains of these variables are the three possible configurations of the tiles and the null value. As it happens, there is only one situation in which none of the above-mentioned three values can be true, and that is when some robot in some adjacent tile is painting the tile in question. The special null value of the state variable has that meaning. For example, {an inline-figure} and similarly for {a mathematical formula}SVtile2 and {a mathematical formula}SVtile3.
      </paragraph>
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Safe instantaneous ground actions
     </section-title>
     <paragraph>
      In this and in the following sections, we fix a planning instance {a mathematical formula}I=(D,P) recalling that we consider a family of planning instances parameterised by the initial state Init and {a mathematical formula}G. We then consider a template {a mathematical formula}T and discuss the conditions for {a mathematical formula}T to be invariant. More precisely, we determine a few sufficient conditions on the families of instantaneous and durative actions in {a mathematical formula}D that ensure that if, for some instance γ, {a mathematical formula}w(γ,Init)≤1, then {a mathematical formula}w(γ,s)≤1 for all other reachable states {a mathematical formula}s∈Sr.
     </paragraph>
     <section label="4.1">
      <section-title>
       Strong safety
      </section-title>
      <paragraph>
       We assume a template {a mathematical formula}T to be fixed as well as an instance γ. In the following, {a mathematical formula}A⊆GA always denotes a set of pairwise non-interfering actions and is assumed to be executable.
      </paragraph>
      <paragraph label="Definition 12">
       Strongly safe actionsThe set of actions A is stronglyγ-safe if, for each {a mathematical formula}s∈SA where {a mathematical formula}w(γ,s)≤1, the successor state {a mathematical formula}s′=ξ(s,A) also satisfies {a mathematical formula}w(γ,s′)≤1.
      </paragraph>
      <paragraph>
       The following result shows that strong γ-safety can always be checked at the level of single actions.
      </paragraph>
      <paragraph label="Proof">
       Let A be a set of actions. Then, A is strongly γ-safe if a is strongly γ-safe for all{a mathematical formula}a∈A.Write {a mathematical formula}A={a1,…,an} and let {a mathematical formula}s∈SA. Note that from Proposition 1, the actions in A can be serialised and the successor state {a mathematical formula}s′=ξ(s,A) can be recursively obtained as {a mathematical formula}s0=s, {a mathematical formula}sk=ξ(sk−1,ak), {a mathematical formula}k=2,…,n and {a mathematical formula}s′=sn. By assumption, it follows that {a mathematical formula}w(γ,si)≤1 for every i. In particular, {a mathematical formula}w(γ,s′)≤1.  □
      </paragraph>
      <paragraph>
       The converse of the above result does not hold. A counterexample will be shown later (see Example 3).
      </paragraph>
      <paragraph>
       In order to tease apart the property of strong γ-safety, we will need several more formal definitions, which we will give here and in the following subsections. Firstly, consider restricting an action to a particular instantiation and its complement.
      </paragraph>
      <paragraph label="Definition 14">
       Given an action {a mathematical formula}a∈GA, {a mathematical formula}aγ and {a mathematical formula}a¬γ are the actions, respectively, specified by{a mathematical formula} (where {a mathematical formula}Ac denotes the set complement of A).Given an action set A, we define the action sets {a mathematical formula}Aγ={aγ|a∈A} and {a mathematical formula}A¬γ={a¬γ|a∈A}.We also split the states in a similar way: take {a mathematical formula}s∈S, put {a mathematical formula}sγ=s∩γ(T) and {a mathematical formula}s¬γ=s∩γ(T)c.
      </paragraph>
      <paragraph label="Remark 15">
       For a state s and an action set A, we have that {a mathematical formula}s∈SA if and only if {a mathematical formula}sγ∈SAγ and {a mathematical formula}s¬γ∈SA¬γ and it holds that:{a mathematical formula}
      </paragraph>
      <paragraph>
       This leads to the following simple but useful result.
      </paragraph>
      <paragraph label="Proposition 16">
       For a set of actions A, the following conditions are equivalent:
      </paragraph>
      <list>
       <list-item>
        A is strongly γ-safe;
       </list-item>
       <list-item>
        {a mathematical formula}Aγis strongly γ-safe;
       </list-item>
       <list-item>
        For every{a mathematical formula}s∈SAγsuch that{a mathematical formula}s⊆γ(T)and{a mathematical formula}w(γ,s)≤1, it holds that the successor state{a mathematical formula}s′=ξ(s,Aγ)is such that{a mathematical formula}w(γ,s′)≤1.
       </list-item>
      </list>
      <paragraph label="Proof">
       (ii) ⇒ (iii) is trivial and (iii) ⇒ (i) is an immediate consequence of (4) and of the fact that {a mathematical formula}w(γ,s)=w(γ,sγ) and {a mathematical formula}w(γ,s′)=w(γ,sγ′).Finally, (i) ⇒ (ii) follows from the following argument. Take any {a mathematical formula}s∈SAγ such that {a mathematical formula}w(γ,s)≤1. Consider {a mathematical formula}s⁎=sγ∪PreA¬γ+. Since {a mathematical formula}sγ⁎=sγ∈SAγ and {a mathematical formula}s¬γ⁎=PreA¬γ+∈SA¬γ, it follows that {a mathematical formula}s⁎∈SA. If we consider the successor states {a mathematical formula}s′=ξ(s,Aγ) and {a mathematical formula}s′⁎=ξ(s⁎,Aγ), it follows from (4) that{a mathematical formula} Therefore,{a mathematical formula} where the last equality follows from the assumption that A is strongly γ-safe.  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Characterisation of ground actions with respect to strong safety
      </section-title>
      <paragraph>
       Based on the structure of the preconditions and effects, we classify actions in four classes and then relate each class to the notion of strong safety.
      </paragraph>
      <paragraph label="Definition 17">
       Classification of ground actionsA set of actions A is:
      </paragraph>
      <list>
       <list-item label="•">
        γ-unreachable if {a mathematical formula}|PreAγ+|≥2;
       </list-item>
       <list-item label="•">
        γ-heavy if {a mathematical formula}|PreAγ+|≤1 and {a mathematical formula}|EffAγ+|≥2;
       </list-item>
       <list-item label="•">
        γ-irrelevant if {a mathematical formula}|PreAγ+|≤1 and {a mathematical formula}|EffAγ+|=0;
       </list-item>
       <list-item label="•">
        γ-relevant if {a mathematical formula}|PreAγ+|≤1 and {a mathematical formula}|EffAγ+|=1.
       </list-item>
      </list>
      <paragraph>
       Each {a mathematical formula}A⊆GA belongs to one and only one of the above four disjoint classes. The following result clarifies their relation with strong safety.
      </paragraph>
      <paragraph label="Proposition 18">
       Let A be a set of actions. Then,
      </paragraph>
      <list>
       <list-item>
        if A is γ-unreachable or γ-irrelevant, A is strongly γ-safe;
       </list-item>
       <list-item>
        if A is γ-heavy, A is not strongly γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       If A is γ-unreachable and A is applicable in the state s, it follows that {a mathematical formula}PreA+⊆s and thus {a mathematical formula}w(γ,s)≥|PreAγ+)|≥2. This shows that the condition {a mathematical formula}w(γ,s)≤1 is never verified and thus A is strongly γ-safe.If A is γ-irrelevant and A is applicable in the state s, we have that the successor state {a mathematical formula}s′=ξ(s,a)⊆s. This yields {a mathematical formula}w(γ,s′)≤w(γ,s). This implies that A is strongly γ-safe.Suppose that A is γ-heavy and consider the state {a mathematical formula}s=PreA+. A is applicable in s (because of assumption (2)) and {a mathematical formula}w(γ,s)=|PreAγ+|≤1. After applying A in s, the successor state {a mathematical formula}s′=ξ(s,A) is such that {a mathematical formula}s′⊇EffAγ+ This yields {a mathematical formula}w(γ,s′)≥|Effα+|≥2 and proves that A is not strongly γ-safe.  □
      </paragraph>
      <paragraph>
       The following example shows how the converse of Proposition 13 does not hold.
      </paragraph>
      <paragraph label="Example 3">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′,q″}, where q, {a mathematical formula}q′, {a mathematical formula}q″ are distinct ground atoms as well as {a mathematical formula}q‴. Let {a mathematical formula}A={a,a′}, where a and {a mathematical formula}a′ are actions such that:{a mathematical formula} Then, a is γ-unreachable and thus strongly γ-safe, while {a mathematical formula}a′ is γ-heavy and not strongly γ-safe. However, the set of actions A is γ-unreachable and thus strongly γ-safe.
      </paragraph>
      <paragraph>
       As the next example shows, γ-relevant action sets may be strongly γ-safe or not.
      </paragraph>
      <paragraph label="Example 4">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′,q″}, where q, {a mathematical formula}q′ and {a mathematical formula}q″ are three distinct ground atoms, and a is an action such that {a mathematical formula}|Prea+|≤1 and {a mathematical formula}Effa+={q}. Since {a mathematical formula}|Effa+∩γ(T)|=1, a is γ-relevant.
      </paragraph>
      <list>
       <list-item label="•">
        Suppose that {a mathematical formula}Prea+={q′} and {a mathematical formula}Effa−={q′} as shown in Fig. 1, left. In this case, a is strongly γ-safe. In fact, if {a mathematical formula}s∈Sa is such that {a mathematical formula}w(γ,s)≤1, {a mathematical formula}q′∈s and in consequence {a mathematical formula}w(γ,s)=1. Given {a mathematical formula}s′=ξ(s,a), {a mathematical formula}q′∉s′, but {a mathematical formula}q∈s′ and therefore {a mathematical formula}w(γ,s′)=1.
       </list-item>
       <list-item label="•">
        Suppose that {a mathematical formula}Prea=∅ and {a mathematical formula}Effa−={q′} as shown in Fig. 1, right. In this case, a is γ-relevant, but is not strongly γ-safe. In fact, consider the starting state {a mathematical formula}s={q″} so that {a mathematical formula}w(γ,s)=1. Since {a mathematical formula}q″∉Effa− and {a mathematical formula}q∈Effa+, {a mathematical formula}s′=ξ(s,a) is such that {a mathematical formula}w(γ,s′)=2.
       </list-item>
      </list>
      <paragraph>
       Proposition 18 classifies all but relevant actions. Let us now consider relevance. We split it in four categories and then analyse the strong safety of each case.
      </paragraph>
      <paragraph label="Definition 19">
       Classification of relevant actionsA γ-relevant set of actions A has at most one relevant precondition ({a mathematical formula}|PreAγ+|≤1). A is γ-weighty, at p, when that is the single relevant precondition: {a mathematical formula}PreAγ+={p}. A is γ-weightless if {a mathematical formula}|PreAγ+|=0.A γ-weighty at p action set A is either:
       <list>
        γ-balanced if the precondition is an effect: {a mathematical formula}p∈EffAγ; orγ-unbalanced if otherwise: {a mathematical formula}p∉EffAγ.A
       </list>
       <paragraph>
        γ-weightless action set A is either:
       </paragraph>
       <list>
        <list-item label="•">
         γ-bounded if the entire instantiation is accessed: {a mathematical formula}PreAγ∪EffAγ=γ(T); or
        </list-item>
        <list-item label="•">
         γ-unbounded if otherwise: {a mathematical formula}PreAγ∪EffAγ≠γ(T).
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       Every relevant set of actions A belongs to one and only one of the above four disjoint classes. The balanced and unbounded cases are discussed in Example 4. To understand the bounded case better, recall that a relevant action set has just one relevant positive effect l, as in {a mathematical formula}EffAγ+={l}. When A is bounded, then the rest of the instantiation {a mathematical formula}γ(T)∖{l} is accessed negatively: {a mathematical formula}γ(T)=PreAγ∪EffAγ, {a mathematical formula}PreAγ+=∅ and {a mathematical formula}EffAγ+={l} together imply that {a mathematical formula}γ(T)∖{l}=PreA−∪EffA−. So the weight after executing a bounded set will be exactly one, regardless of what it was before. In other words, bounded is even safer than balanced. Formally:
      </paragraph>
      <paragraph label="Proposition 20">
       Let A be a γ-relevant set of actions. Then,
      </paragraph>
      <list>
       <list-item>
        if A is γ-balanced or γ-bounded, A is strongly γ-safe;
       </list-item>
       <list-item>
        if A is γ-unbalanced or γ-unbounded, A is not strongly γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       We will prove the corresponding property for {a mathematical formula}Aγ making use of Condition (iii) of Proposition 16. We first analyse the case when A is γ-weighty. Let {a mathematical formula}PreAγ+={q1} and {a mathematical formula}EffAγ+={q2}. Suppose now that A is γ-balanced and fix a state {a mathematical formula}s∈γ(T) such that {a mathematical formula}w(γ,s)≤1 and {a mathematical formula}Aγ is applicable in s. Since {a mathematical formula}q1⊆s, necessarily, {a mathematical formula}s={q1} and {a mathematical formula}w(γ,s)=1. Consider the subsequent state {a mathematical formula}s′=ξ(s,Aγ). If {a mathematical formula}q1=q2, we have that {a mathematical formula}s′=s so that {a mathematical formula}w(γ,s′)=1. If instead {a mathematical formula}q1∈EffAγ−, we have that {a mathematical formula}s′=(s∖{q1})∪{q2}={q2} and thus {a mathematical formula}w(γ,s′)=1. Suppose that A is unbalanced and consider the state {a mathematical formula}s={q1}. The subsequent state {a mathematical formula}s′=ξ(s,Aγ)={q1,q2} so that {a mathematical formula}w(γ,s′)=2.We now consider the case when A is γ-weightless, i.e. {a mathematical formula}PreAγ+=∅. Let {a mathematical formula}EffAγ+={q2}. Suppose that A is γ-bounded and fix a state {a mathematical formula}s∈γ(T) such that {a mathematical formula}w(γ,s)≤1 and {a mathematical formula}Aγ is applicable in s. Since A is γ-relevant, the subsequent state {a mathematical formula}s′=ξ(s,Aγ) is such that {a mathematical formula}w(γ,s′)≤w(γ,s)+1. The only case we need to consider is thus when {a mathematical formula}w(γ,s)=1. Suppose that {a mathematical formula}s={q1}. Since, by assumption {a mathematical formula}PreAγ∪EffAγ=T(γ), it follows that {a mathematical formula}q1∈PreAγ∪EffAγ. We have that {a mathematical formula}q1∉PreAγ− (otherwise {a mathematical formula}Aγ would not be applicable on the state s). Therefore, necessarily, either {a mathematical formula}q1∈EffAγ+ or {a mathematical formula}q1∈EffAγ−. In the first case, we have that {a mathematical formula}q1=q2 and thus {a mathematical formula}s′=s={q1}. In the second case, {a mathematical formula}s′={q2}. In both cases, {a mathematical formula}w(γ,s′)=1. Finally, if A is γ-unbounded, we consider any ground atom {a mathematical formula}q1∈γ(T)∖(PreAγ∪EffAγ) and we set {a mathematical formula}s={q1}. We have that {a mathematical formula}Aγ is applicable in {a mathematical formula}q1 since {a mathematical formula}PreAγ+=∅ and {a mathematical formula}q1∉PreAγ−, and {a mathematical formula}w(γ,s)=1. Since it also holds that {a mathematical formula}q1∉EffAγ−, we have that the subsequent state {a mathematical formula}s′=ξ(s,Aγ)={q1,q2} and {a mathematical formula}w(γ,s′)=2.  □
      </paragraph>
      <paragraph>
       Putting the Proposition 18, Proposition 20 together, we get the following result:
      </paragraph>
      <paragraph label="Theorem 21">
       Let A be a set of actions. Then,
      </paragraph>
      <list>
       <list-item>
        if A is either γ-unreachable, γ-irrelevant, γ-balanced, or γ-bounded, A is strongly γ-safe;
       </list-item>
       <list-item>
        if A is either γ-heavy, γ-unbalanced, or γ-unbounded, A is not strongly γ-safe.
       </list-item>
      </list>
      <paragraph>
       Any state in which a γ-heavy or γ-unbalanced action can be executed will immediately have weight 2 (or more). In contrast, it is possible for a γ-unbounded action to execute without violating the weight bound, and it is conceivable that all reachable states are such that γ-unbounded actions end up being safe. In that sense, Theorem 21 is arguably less of a complete classification than it may appear.
      </paragraph>
      <paragraph>
       A possibly interesting way to approach knowledge generated by a stronger prover would be to augment the descriptions of actions with derived preconditions, i.e. properties that hold in all reachable states and could be freely added as a precondition on all actions. That could convert γ-unbounded actions into γ-balanced or γ-bounded actions (if negative conditions are added).
      </paragraph>
      <paragraph label="Example 5">
       Floortile domainTake the schema {a mathematical formula}α=paintUpend with variables {a mathematical formula}Vα={r,y,x,c} (see Table 3) and grounding gr such that {an inline-figure}, {an inline-figure}, {an inline-figure}, {an inline-figure}. Let {a mathematical formula}c=〈painted/2,1〉 be the component that counts the colour argument of painted and {a mathematical formula}T=({c},{{(c,0)}}) be the template on just that component. Consider the safety of {a mathematical formula}a=gr(α) with respect to {a mathematical formula}T. Let {an inline-figure} be the instance for the tile the robot is painting, {an inline-figure} be the instance for an unrelated tile, and {an inline-figure} be the instance for the tile the robot is standing on. Each instantiation is the set of all possible colours per tile.The action a is {a mathematical formula}γ2-irrelevant (as expected), meaning none of {a mathematical formula}γ2(T) are preconditions or effects, so also a is (trivially) strongly {a mathematical formula}γ2-safe.While tile3 is relevant to the action as a whole, a does not access painted at tile3 so a is likewise irrelevant and thus safe with respect to {a mathematical formula}γ3.The action a is {a mathematical formula}γ1-relevant, because it adds {an inline-figure}. It is not strongly {a mathematical formula}γ1-safe, because if executed in a state where the tile was already black, the tile would end up being painted both colours: {an inline-figure}. In particular, a is {a mathematical formula}γ1-unbounded. If we altered it by adding negative preconditions on all the other colours, it would become both bounded and safe.If we added clear to the template, then instead a would be balanced (and thus safe) at the instantiation for tile1.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Template safety
      </section-title>
      <paragraph>
       This concluding section presents a definition of strong safety with respect to a template, and presents a first result that expresses a sufficient condition for a template to be invariant.
      </paragraph>
      <paragraph label="Definition 22">
       For a template {a mathematical formula}T, a set of actions {a mathematical formula}A⊆GA is strongly safe if it is strongly γ-safe for every instance γ.
      </paragraph>
      <paragraph>
       We have the following result:
      </paragraph>
      <paragraph label="Proof">
       For a template{a mathematical formula}T,{a mathematical formula}Tis invariant if for each{a mathematical formula}a∈GA, a is strongly safe.We proceed as follows. We fix any instance γ of {a mathematical formula}T and we show that if {a mathematical formula}w(γ,Init)≤1, then {a mathematical formula}w(γ,s)≤1 for every {a mathematical formula}s∈Sr. This, by Proposition 11, yields the result. By definition of the set of reachable states {a mathematical formula}Sr, any {a mathematical formula}s∈Sr can be obtained by the initial state Init by recursively applying a sequence of action sets. Precisely, there exists a sequence of sets (each consisting of pairwise non-interfering actions) {a mathematical formula}A1,A2,…,Ak and a sequence of states {a mathematical formula}{si}i=0…k such that {a mathematical formula}s0=Init, {a mathematical formula}sk=s and for each {a mathematical formula}i=0,…,k−1, {a mathematical formula}si+1=ξ(si,Ai+1). We prove that {a mathematical formula}w(γ,s)≤1 by induction on k. Notice that the case {a mathematical formula}k=0 boils down to {a mathematical formula}s=s0=Init and {a mathematical formula}w(γ,Init)≤1 is our standing assumption. Assume it to be true for {a mathematical formula}k−1 and let us prove it for k. Notice that, we can write {a mathematical formula}s=sk=ξ(sk−1,Ak) and the induction assumption implies that {a mathematical formula}w(γ,sk−1)≤1. By assumption every {a mathematical formula}a∈GA is strongly safe and thus, by Definition 22, strongly γ-safe. Using Proposition 13 we obtain in particular that {a mathematical formula}Ak is strongly γ-safe. Consequently, also {a mathematical formula}w(γ,sk)≤1.  □
      </paragraph>
      <paragraph>
       The condition expressed in Corollary 23 cannot be inverted in general. Indeed, a template can be invariant even if not all actions are strongly safe. We will see when this happens in the following section.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Safe action sequences and safe durative actions
     </section-title>
     <paragraph>
      A template can be invariant even if not all actions are strongly safe. This happens for two reasons. On the one hand, since the set of reachable states {a mathematical formula}Sr is in general smaller than {a mathematical formula}S, it may be that all the states that are responsible for the lack of strong safety are unreachable, i.e. they are not in {a mathematical formula}Sr. On the other hand, in domains with durative actions, some instantaneous actions are temporally coupled because they are the start and end fragments of the same durative action. This coupling imposes constraints on the states where the end part can be applied, which might prove helpful to establish that a template is invariant. While in this paper we will not analyse the first case as it would require an analysis of the set of reachable states {a mathematical formula}Sr, which is infeasible, we now elaborate suitable simple concepts of safety for durative actions, which are weaker than strong safety. These extensions are important in many real-world temporal planning domains. In our experience, these domains often present end-fragments of durative actions that are unsafe as written, often, γ-unbalanced. Nonetheless, every use in an executable plan preserves the weight condition, typically because the associated start-fragments force the weight to zero and the invariant-fragments keep it there. (A γ-unbalanced action is safe if it only executes in weight zero states.) We give a definition of safety for durative actions that captures this case. However, since in a plan a durative action may intertwine with other actions that happen between its start and end points, we need to work out a concept of safety for more general sequences of actions than just durative ones.
     </paragraph>
     <paragraph>
      Below, we consider general sequences of action sets {a mathematical formula}A=(A1,A2,…,An). Any simple plan π generates such an object. Indeed, if {a mathematical formula}{ti}i=0,…,k¯ is the related happening time sequence and {a mathematical formula}Ati are the relative happenings, we can consider the happening sequence {a mathematical formula}Aπ=(At0,…,Atk¯) that contains all the information on the plan π except the time values at which the various actions happen.
     </paragraph>
     <paragraph>
      To study the invariance of a template, we break the happening sequence of each plan into subsequences determined by the happenings of durative actions. More precisely, we consider sequences {a mathematical formula}A=(A1,A2,…,An) where, for some durative action {a mathematical formula}Da=(ast,ainv,aend), we have that {a mathematical formula}ast∈A1 and {a mathematical formula}aend∈An. The sets {a mathematical formula}A2,…,An−1, as well as {a mathematical formula}A1 and {a mathematical formula}An, possibly contain other actions that are executed over the duration of Da. However, it is convenient to consider general sequences of actions {a mathematical formula}A=(A1,A2,…,An) without referring to plans or durative actions. Hence, in this section, we first give a definition of safety for A such that, when A is executed serially in any executable plan π, if the weight constraint is not violated in the state where the sequence is initially applied, it is not violated in any intermediate step and at the end of the sequence. For single action sets (sequences of length {a mathematical formula}n=1), this concept coincides with the notion of strong safety.
     </paragraph>
     <paragraph>
      We then consider a slightly stronger notion of safety which is robust to the insertion, between elements of the sequence, of other actions whose positive effects have no intersection with the template. To do this, it is necessary to introduce a number of auxiliary concepts relating to the state dynamics induced by the execution of A. This general theory will then be applied to sequences constructed from durative actions.
     </paragraph>
     <paragraph>
      We recall our standing assumption that any considered subset of actions, {a mathematical formula}Ai, consists of pairwise non-interfering actions and is assumed to be executable.
     </paragraph>
     <section label="5.1">
      <section-title>
       Safe ground action sequences
      </section-title>
      <paragraph>
       For a sequence of action sets {a mathematical formula}A=(A1,A2,…,An), we denote with {a mathematical formula}SA the set of state sequences {a mathematical formula}(s0,…,sn)∈Sn+1 such that{a mathematical formula} If {a mathematical formula}(s0,…,sn)∈SA, we say that {a mathematical formula}(s0,…,sn) is a state sequence compatible with A. Given an instance γ, we also define {a mathematical formula}SA(γ)={(s0,…,sn)∈SA|w(γ,s0)≤1}. We use the following notation for subsequences of A: {a mathematical formula}Ahk=(Ah,Ah+1,…,Ak).
      </paragraph>
      <paragraph>
       We now fix a template {a mathematical formula}T and an instance γ and give the following natural definition of safety for a sequence.
      </paragraph>
      <paragraph label="Definition 24">
       Individually safe actionsA sequence of action sets {a mathematical formula}A=(A1,A2,…,An) is individually γ-safe if for every sequence of states {a mathematical formula}(s0,…,sn){a mathematical formula}∈SA we have that{a mathematical formula}
      </paragraph>
      <paragraph>
       The invariance of a template can now be expressed in terms of individual safety for the happening sequences.
      </paragraph>
      <paragraph label="Proposition 25">
       Let{a mathematical formula}Tbe a template. Suppose that for every executable simple plan π, the happening sequence{a mathematical formula}Aπis individually γ-safe for every instance γ. Then,{a mathematical formula}Tis invariant.
      </paragraph>
      <paragraph label="Proof">
       Take any instance γ and assume that {a mathematical formula}w(γ,Init)≤1. We need to show that {a mathematical formula}w(γ,s)≤1 for every {a mathematical formula}s∈Sr. For each {a mathematical formula}s∈Sr, there exists an executable simple plan π having {a mathematical formula}trace(π)={Si=(ti,si)i=0,…,k¯} with {a mathematical formula}s0=Init, {a mathematical formula}sk¯=s, and with happening sequence {a mathematical formula}Aπ. We have that the state sequence {a mathematical formula}(s0,…,sk¯)∈SAπ. Since by assumption {a mathematical formula}w(γ,s0)≤1 the individual γ-safety of {a mathematical formula}Aπ implies that {a mathematical formula}w(γ,sj)≤1 for every {a mathematical formula}j=1,…,k¯. In particular, {a mathematical formula}w(γ,s)≤1.  □
      </paragraph>
      <paragraph>
       Below are elementary properties of individual γ-safety for subsequences of A.
      </paragraph>
      <paragraph label="Proposition 26">
       Consider a sequence of action sets{a mathematical formula}A=(A1,A2,…,An). The following properties hold:
      </paragraph>
      <list>
       <list-item>
        if, for some k and h such that{a mathematical formula}k≥h−1,{a mathematical formula}A1k=(A1,A2,…,Ak)and{a mathematical formula}Ahn=(Ah,…,An)are both individually γ-safe, thenAis also individually γ-safe;
       </list-item>
       <list-item>
        ifAis individually γ-safe and{a mathematical formula}Akand{a mathematical formula}Ak+1are non-interfering, then{a mathematical formula}A′=(A1,A2,…,Ak∪Ak+1,…,An)is individually γ-safe;
       </list-item>
       <list-item>
        ifAis individually γ-safe and{a mathematical formula}Bj, for{a mathematical formula}j=1,…,nare action sets such that{a mathematical formula}EffBj=∅, then,{a mathematical formula}A′=(A1,B1,A2,…,Bn,An)is individually γ-safe. If, in addition,{a mathematical formula}Ajand{a mathematical formula}Bjare non-interfering for every{a mathematical formula}j=1,…,n, also{a mathematical formula}A″=(A1∪B1,…,An∪Bn)is individually γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i): If {a mathematical formula}(s0,s1,…,sn)∈SA, we have that{a mathematical formula} Therefore, if {a mathematical formula}w(γ,s0)≤1, from the fact that {a mathematical formula}A1k is individually γ-safe, it follows that {a mathematical formula}w(γ,sj)≤1 for every {a mathematical formula}j=1,…,k. In particular, since {a mathematical formula}k≥h−1, we have that {a mathematical formula}w(γ,sh−1)≤1. From the fact that {a mathematical formula}Ahn is also individually γ-safe, it now follows that {a mathematical formula}w(γ,sj)≤1 for every {a mathematical formula}j=h,…,n. This implies that {a mathematical formula}w(γ,sj)≤1 for every {a mathematical formula}j=1,…,n and proves property (i).(ii): Suppose {a mathematical formula}(s0,s1,…,sk−1,sk+1,…,sn)∈SA′ where {a mathematical formula}sk+1=ξ(Ak∪Ak+1,sk−1). Put {a mathematical formula}sk=ξ(Ak,sk−1) and note that, by serialisability (see Proposition 1), {a mathematical formula}sk+1=ξ(Ak+1,sk), and therefore {a mathematical formula}(s0,s1,…,sk−1,sk,sk+1,…,sn)∈SA. This implies that {a mathematical formula}w(γ,sj)≤1 for every {a mathematical formula}j=1,…,n and proves property (ii).(iii): If {a mathematical formula}(s0,s′0,s1,…,s′n−1,sn)∈SA′, then, {a mathematical formula}s′k−1=sk for every {a mathematical formula}k=1,…,n and {a mathematical formula}(s0,s1,…,sn)∈SA. Individual γ-safety of A now establishes property (iii). Regarding {a mathematical formula}A″ the property follows from the fact that {a mathematical formula}A′ is individually γ-safe and case (ii).  □
      </paragraph>
      <paragraph>
       The following is a useful consequence of the previous results: it asserts that if individual safety holds locally in a sequence, then it also holds globally.
      </paragraph>
      <paragraph label="Corollary 27">
       For a sequence of action sets{a mathematical formula}A=(A1,A2,…,An), the following conditions are equivalent:
      </paragraph>
      <list>
       <list-item>
        the sequenceAis individually γ-safe;
       </list-item>
       <list-item>
        for each{a mathematical formula}j=1,…,n, there exists a subsequence{a mathematical formula}Aj−rj+s, with{a mathematical formula}r,s≥0, that is individually γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i) ⇒ (ii) is trivial and (ii) ⇒ (i) follows from an iterative use of (i) of Proposition 26.  □
      </paragraph>
      <paragraph>
       Individual safety is a weak property since it is not robust with respect to the insertion of other actions, even when these actions are irrelevant but possess delete effects. This is connected to the fact that, while individual safety has this nice local to global feature illustrated in Corollary 27, it does not possess the opposite feature: subsequences of individually safe sequences may not be individually safe. The following example shows both these phenomena.
      </paragraph>
      <paragraph label="Example 6">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′}. The set of state sequences compatible with {a mathematical formula}A=(a1,a2) (Fig. 2 – top diagram) is: {a mathematical formula}SA={(s0,s1,s2)|q∉s0,s1=s0∪{q′},s2=s1}. Note that {a mathematical formula}q∉s0 because, by hypothesis, {a mathematical formula}a2 is applicable in {a mathematical formula}s1 and {a mathematical formula}s1=s0∪{q′}. A is individually γ-safe since {a mathematical formula}w(γ,si)≤1 for every state {a mathematical formula}si that appears in {a mathematical formula}SA. Note that {a mathematical formula}a1 is γ-unbounded and thus not strongly γ-safe and that {a mathematical formula}A11=(a1) is not individually γ-safe as well.Now consider the sequence {a mathematical formula}A˜=(a1,b,a2) (Fig. 2 – bottom diagram) where a γ-irrelevant action b is inserted between {a mathematical formula}a1 and {a mathematical formula}a2. The new set of state sequences compatible with {a mathematical formula}A˜ is: {a mathematical formula}SA˜={(s0,s1,s2,s3)|s1=s0∪{q′},s2=s1∖{q},s3=s2}. Note that now q can be in {a mathematical formula}s0 since it is the action b that ensures the applicability of {a mathematical formula}a2. If {a mathematical formula}q∈s0, since {a mathematical formula}a1 adds {a mathematical formula}q′ to {a mathematical formula}s0, {a mathematical formula}w(γ,s1)=2. This new sequence is not individually γ-safe. The insertion of a γ-irrelevant action has failed the individual γ-safety of the sequence A.
      </paragraph>
      <paragraph>
       For proving some of our results, the concept of individual safety is not sufficient. Below we present a stronger definition of safety for an action sequence that is robust with respect to the insertion of irrelevant actions in it. First, we define the simple concepts of executable and reachable sequences.
      </paragraph>
      <paragraph label="Definition 28">
       Executable and reachable actionsThe sequence {a mathematical formula}A=(A1,A2,…,An) is called:
      </paragraph>
      <list>
       <list-item label="•">
        executable if {a mathematical formula}SA≠∅;
       </list-item>
       <list-item label="•">
        γ-(un)reachable if {a mathematical formula}SA(γ)≠∅ ({a mathematical formula}SA(γ)=∅).
       </list-item>
      </list>
      <paragraph label="Remark 29">
       Note the following chain of implications:{a mathematical formula} Note that if π is an executable simple plan, γ is an instance and {a mathematical formula}w(γ,Init)≤1, then the happening sequence {a mathematical formula}Aπ is γ-reachable. Moreover, every subsequence A of {a mathematical formula}Aπ is executable. If a subsequence A of {a mathematical formula}Aπ is γ-unreachable, the weight will surely exceed 1 at some point of the plan π and thus the template {a mathematical formula}T will not be invariant.
      </paragraph>
      <paragraph>
       In the special case of a sequence of length 2, executability and reachability admit very simple characterisations. We report them below as we will need them later. First define, for a generic set of actions A, the postconditions:{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 30">
       We have the following result: For a sequence of two action sets{a mathematical formula}A=(A1,A2), the following conditions are equivalent:
      </paragraph>
      <list>
       <list-item>
        Ais executable;
       </list-item>
       <list-item>
        {a mathematical formula}ΓA1+∩PreA2−=∅=ΓA1−∩PreA2+.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i) ⇒ (ii): Note that if {a mathematical formula}(s0,s1,s2)∈SA, it follows that {a mathematical formula}PreA1+⊆s0. Since {a mathematical formula}s1=(s0∖EffA1−)∪EffA1+ it follows that {a mathematical formula}ΓA1+⊆s1. Analogously, using the fact that {a mathematical formula}(PreA1−)c⊇s0, it follows that {a mathematical formula}(ΓA1−)c⊇s1. Since {a mathematical formula}A2 must be applicable on {a mathematical formula}s1, condition (ii) immediately follows.(ii) ⇒ (i): Consider {a mathematical formula}s0=PreA1+∪(PreA2+∖EffA1+). Straightforward set theoretic computation, using conditions (ii), show that {a mathematical formula}A1 can be applied on {a mathematical formula}s0 and that {a mathematical formula}A2 can be applied on {a mathematical formula}s1=ξ(A1,s0). This proves (i).  □
      </paragraph>
      <paragraph label="Proposition 31">
       For a sequence of two action sets{a mathematical formula}A=(A1,A2), the following conditions are equivalent:
      </paragraph>
      <list>
       <list-item>
        Ais γ-reachable;
       </list-item>
       <list-item>
        Ais executable and{a mathematical formula}|PreAγ1+∪(PreAγ2+∖EffAγ1+)|≤1.
       </list-item>
      </list>
      <paragraph label="Proof">
       (ii) ⇒ (i): It follows from the proof of (ii) ⇒ (i) in Proposition 30 that there exists {a mathematical formula}(s0,s1,s2)∈SA with {a mathematical formula}s0=PreA1+∪(PreA2+∖EffA1+). By the assumption, {a mathematical formula}w(γ,s0)≤1 and this proves (i).(i) ⇒ (ii): it follows from the fact that if {a mathematical formula}(s0,s1,s2)∈SA, necessarily {a mathematical formula}PreA1+∪(PreA2+∖EffA1+)⊆s0.  □
      </paragraph>
      <paragraph>
       The following result shows how executability and γ-reachability are robust with respect to some specific modifications of a sequence, notably, the deletion of actions containing no effects, and serialisation.
      </paragraph>
      <paragraph label="Proposition 32">
       Consider a sequence{a mathematical formula}A=(A1,A2,…,An)that is executable or γ-reachable. Then,
      </paragraph>
      <list>
       <list-item>
        if{a mathematical formula}Bj⊆Ajare such that{a mathematical formula}EffBj=∅for every{a mathematical formula}j=1,…,n−1,{sup:3}then also{a mathematical formula}A′=(A1∖B1,A2∖B2,…,An∖Bn)is, respectively, executable or γ-reachable.
       </list-item>
       <list-item>
        if{a mathematical formula}Aj=A′j∪A″jfor some{a mathematical formula}j=1,…,n, then also{a mathematical formula}A′=(A1,A2,…,A′j,A″j,…,An)is, respectively, executable or γ-reachable.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i): If {a mathematical formula}(s0,s1,…,sn−1,sn)∈SA, we have that {a mathematical formula}(s0,s1,…,sn−1,s′n)∈SA′ for a suitable state {a mathematical formula}s′n. The result then follows from the definition of executability and γ-reachability.(ii): This follows immediately from serialisability (see Proposition 1).  □
      </paragraph>
      <paragraph>
       Here is our stronger notion of safety:
      </paragraph>
      <paragraph label="Definition 33">
       Safe actionsA sequence of action sets {a mathematical formula}A=(A1,A2,…An) is γ-safe if it is executable and the subsequences {a mathematical formula}A1k are individually γ-safe for every {a mathematical formula}k=1,…,n.
      </paragraph>
      <paragraph>
       Example 6 illustrates why individual safety is too fragile a concept by itself. We would like to infer that A in Example 6 is unsafe for some appropriate notion of safety, but, as the example shows, that concept cannot be individual safety. Definition 33 accomplishes that aim. Indeed, note how the sequence {a mathematical formula}A=(a1,a2) considered in Example 6 is not γ-safe, since {a mathematical formula}(a1) is not individually γ-safe.
      </paragraph>
      <paragraph>
       The definition of safety asks for executability – in addition to asking for every prefix to be individually safe – because, without executability, individual safety is a vacuous condition. In particular, we would like to conclude that the happening sequence in Example 7 considered next is unsafe, for the reason shown. By having Definition 33 require executability, we attain that judgment.
      </paragraph>
      <paragraph label="Example 7">
       Motivating executability in safetyConsider the non-executable sequence {a mathematical formula}A=(a1,a2) depicted in Fig. 3 – top diagram ({a mathematical formula}q″ is required to be false by {a mathematical formula}a2, but it is asserted by {a mathematical formula}a1). Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′,q″}. As it happens, A is individually safe: vacuously, since it is non-executable. However, this is not really a safe arrangement: we would like to say that inserting γ-irrelevant actions preserves safety, but consider inserting such an action b, deleting {a mathematical formula}q″, as in {a mathematical formula}A˜=(a1,b,a2) and depicted in Fig. 3 – bottom diagram. Then the weight bound, which held (vacuously) for A, is violated in {a mathematical formula}A˜ (both q and {a mathematical formula}q′ end up true), and so we can conclude that individually safe is too weak for our purposes. Observe that, by requiring executability, the definition of safety rules out this (counter-)example: A is notγ-safe, as desired. (Note that, unlike Example 6, here all the prefixes are individually safe.)
      </paragraph>
      <paragraph label="Remark 34">
       If {a mathematical formula}A=(A1,A2,…An) is γ-safe, the first action set {a mathematical formula}A1 must necessarily be strongly γ-safe. In the other direction, note that if A is executable and every {a mathematical formula}Aj for {a mathematical formula}j=1,…,n is strongly γ-safe then, A is γ-safe.
      </paragraph>
      <paragraph>
       This motivates the following definition.
      </paragraph>
      <paragraph label="Definition 35">
       Strongly and weakly safe actionsA sequence of action sets {a mathematical formula}A=(A1,A2,…,An) is:
      </paragraph>
      <list>
       <list-item label="•">
        strongly γ-safe if it is executable and every {a mathematical formula}Aj for {a mathematical formula}j=1,…,n is strongly γ-safe;
       </list-item>
       <list-item label="•">
        weakly γ-safe if it is γ-safe but not strongly γ-safe.
       </list-item>
      </list>
      <paragraph>
       With this, we are finished with upgrading our notion of safety, but there is one last point to consider: having safety alone still does not let us prove anything, because safety only preserves a weight bound, it does not force it true initially. So in general we need to consider sequences that are both γ-safe and γ-reachable. We keep those notions separate, rather than combine them in another definition, for technical reasons: e.g. γ-safe can be shown for an entire planning domain, and then γ-reachable can be checked per problem. The first things that can be said of sequences that are both γ-safe and γ-reachable is that they exclude γ-heavy and γ-unbalanced actions (cf., Proposition 16, Proposition 18).
      </paragraph>
      <paragraph label="Example 8">
       Motivating reachability in Proposition 36Consider the template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′}. Now consider the executable, but γ-unreachable sequence {a mathematical formula}A=(a1,a2) depicted in Fig. 4, consisting of a γ-unreachable action {a mathematical formula}a1 and a γ-heavy action {a mathematical formula}a2. In general, we want to quickly exclude any sequence containing a γ-heavy action; but insisting on safety alone is not enough, as this example demonstrates. Action {a mathematical formula}a1 requires both q and {a mathematical formula}q′ to be true and so the weight has to be 2 initially for A to execute (consequently, A is not γ-reachable). Perhaps counterintuitively, for the same reason, A is γ-safe: its two prefixes {a mathematical formula}(a1) and {a mathematical formula}(a1,a2) are both individually safe since all executions begin with the weight bound violated, and then all the implications comprising “safety” just hold vacuously.
      </paragraph>
      <paragraph>
       What the example illustrates is that, in general, undesirables such as γ-heavy actions can be hidden in nominally safe sequences only by failing reachability. Formally, by insisting on safety and reachability together, we can rule out heavy and unbalanced actions everywhere:
      </paragraph>
      <paragraph label="Proposition 36">
       Let{a mathematical formula}A=(A1,A2,…,An)be a sequence of action sets. IfAis γ-safe and γ-reachable, then, for every{a mathematical formula}j=1,…,n,{a mathematical formula}Ajis neither:
      </paragraph>
      <list>
       <list-item label="•">
        γ-heavy, nor
       </list-item>
       <list-item label="•">
        γ-unbalanced.
       </list-item>
      </list>
      <paragraph label="Proof">
       Since A is γ-reachable, the set {a mathematical formula}SA(γ) is not empty. Fix any {a mathematical formula}(s0,…,sn)∈SA(γ) and note that, since A is γ-safe, {a mathematical formula}w(γ,si)≤1 for every {a mathematical formula}i=1,…,n. For any {a mathematical formula}j=1,…,n, we have that {a mathematical formula}sj=(sj−1∖EffAj−)∪EffAj+⊇(PreAj+∖EffAj−])∪EffAj+. This implies that{a mathematical formula} As a consequence, {a mathematical formula}|EffAγj+|≤1, which says that {a mathematical formula}Aj can not be γ-heavy. If we now assume that {a mathematical formula}|EffAγj+|=1, Relation (6) implies that {a mathematical formula}PreAγj+⊆EffAγj+∩EffAγj−. Hence {a mathematical formula}Aj cannot be γ-unbalanced.  □
      </paragraph>
      <paragraph>
       In studying the two safety properties for a sequence A introduced so far, we can essentially restrict ourselves to study the state dynamics on the template instantiation {a mathematical formula}γ(T) as we did for strong γ-safety of instantaneous actions (see Remark 15).
      </paragraph>
      <paragraph>
       Considering the sequence {a mathematical formula}A=(A1,A2,…An), we denote by {a mathematical formula}Aγ=(Aγ1,Aγ2,…Aγn) and {a mathematical formula}A¬γ=(A¬γ1,A¬γ2,…A¬γn) the corresponding restricted sequences. We have the following result.
      </paragraph>
      <paragraph label="Proposition 37">
       Given the sequence{a mathematical formula}A=(A1,A2,…An),
      </paragraph>
      <list>
       <list-item>
        Ais executable if and only if{a mathematical formula}Aγand{a mathematical formula}A¬γare both executable;
       </list-item>
       <list-item>
        Ais γ-reachable if and only if{a mathematical formula}Aγis γ-reachable and{a mathematical formula}A¬γis executable;
       </list-item>
       <list-item>
        Ais individually γ-safe if and only if{a mathematical formula}Aγis individually γ-safe.
       </list-item>
       <list-item>
        Ais γ-safe if and only if{a mathematical formula}Aγis γ-safe and{a mathematical formula}A¬γis executable.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i): It follows from (4) that, for any sequence of states {a mathematical formula}(s0,…,sn)∈Sn+1, we have that{a mathematical formula} This immediately proves the ‘only if’ implication. On the other hand, if {a mathematical formula}s′∈SAγ and {a mathematical formula}s″∈SA¬γ, we have that {a mathematical formula}sγ′∈SAγ and {a mathematical formula}s¬γ″∈SA¬γ and thus {a mathematical formula}s=sγ′∪s¬γ″∈SA by (7).Statement (ii) can be proven analogously to (i), and statement (iii) follows by a straightforward extension of the argument used to prove Proposition 16. Finally, statement (iv) follows from the definition of strong γ-safety together with the previous statements, (i) and (iii).  □
      </paragraph>
      <paragraph>
       We are now ready to state and prove the following fundamental result, which ensures that the concept of safe sequence is robust to the insertion of irrelevant actions.
      </paragraph>
      <paragraph label="Theorem 38">
       Consider a γ-safe sequence{a mathematical formula}A=(A1,A2)and γ-irrelevant action sets{a mathematical formula}B1,B2,…,Bn. Then, the sequence{a mathematical formula}A˜=(A1,B1,…,Bn,A2)is either non executable or γ-safe.
      </paragraph>
      <paragraph label="Proof">
       Consider the sequences restricted on the instantiation {a mathematical formula}γ(T) and its complement: {a mathematical formula}Aγ, {a mathematical formula}A¬γ and, respectively, {a mathematical formula}A˜γ, {a mathematical formula}A˜¬γ. By virtue of Proposition 37, we have that {a mathematical formula}Aγ is γ-safe and to prove the result it is sufficient to show that {a mathematical formula}A˜γ is either non executable or γ-safe.Assume that {a mathematical formula}A˜γ is executable and let {a mathematical formula}(s0,s1,s2,…,sn+1,sn+2)∈SA˜γ be such that {a mathematical formula}w(γ,s0)≤1. Since {a mathematical formula}(s0,s1)∈SAγ1 and {a mathematical formula}Aγ1 is strongly safe, it follows that {a mathematical formula}w(γ,s1)≤1. Note now that {a mathematical formula}sj=sj−1∖EffBγj−1− for {a mathematical formula}j=2,…,n+1 and this immediately implies that{a mathematical formula} What remains to be shown is that also {a mathematical formula}w(γ,sn+2)≤1. To accomplish this, we introduce the set {a mathematical formula}F=∪i=1nEffBγi− and we consider the new initial state {a mathematical formula}s˜0=s0∖(F∖PreAγ1+). Since {a mathematical formula}s˜0⊆s0, we know that {a mathematical formula}PreAγ1−∩s˜0=∅. Moreover, by construction, we also have that {a mathematical formula}PreAγ1+⊆s˜0. Thus {a mathematical formula}Aγ1 can be applied to the state {a mathematical formula}s˜0 and we obtain the next state:{a mathematical formula}Note that {a mathematical formula}sn+1=s1∖F⊆s˜1, which implies that {a mathematical formula}PreAγ2+⊆s˜1. Also, {a mathematical formula}s˜1⊆sn+1∪ΓAγ1+. Since {a mathematical formula}Aγ2 is applicable in the state {a mathematical formula}sn+1, it follows that {a mathematical formula}PreAγ2−⊆sn+1=∅. The fact that {a mathematical formula}Aγ, being γ-safe, is executable implies, by Proposition 30, that {a mathematical formula}ΓAγ1+∩PreAγ2−=∅. Therefore {a mathematical formula}PreAγ2−⊆s˜1=∅. {a mathematical formula}Aγ2 is thus applicable in the state {a mathematical formula}s˜1 and there exists {a mathematical formula}s˜2∈S such that {a mathematical formula}(s˜1,s˜2)∈SAγ2. Therefore, we can conclude that {a mathematical formula}(s˜0,s˜1,s˜2)∈SAγ. Since {a mathematical formula}Aγ is γ-safe and {a mathematical formula}w(γ,s˜0)≤w(γ,s0)≤1, we have that {a mathematical formula}w(γ,s˜2)≤1. At the same time, since {a mathematical formula}sn+1⊆s˜1, we also have that {a mathematical formula}sn+2⊆s˜2 and thus {a mathematical formula}w(γ,sn+2)≤1. This completes the proof.  □
      </paragraph>
      <paragraph label="Remark 39">
       We conjecture that Theorem 38 could be generalised to sequences of actions of length longer than two, but the proof is much more complex. Since this extension is not needed in this paper, we do not present such a proof here.
      </paragraph>
      <paragraph>
       For future use, it will be convenient to have a definition of safeness that does not depend on the particular chosen instance.
      </paragraph>
      <paragraph label="Definition 40">
       A sequence of action sets A is safe for a template {a mathematical formula}T if it is γ-safe for every instance γ of {a mathematical formula}T. A sequence of action sets A is strongly safe for a template {a mathematical formula}T if it is strongly γ-safe for every instance γ of {a mathematical formula}T. It is weakly safe if it is safe but not strongly safe.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Safe ground durative actions
      </section-title>
      <paragraph>
       We now restrict our attention to durative actions {a mathematical formula}Da=(ast,ainv,aend). If we interpret Da as a sequence of three actions, we can treat it using the properties defined for general sequences such as γ-safety and strong γ-safety. Before studying these properties, it is convenient to make some considerations on the way durative actions appear in admissible simple plans. Indeed, several constraints emerge as a direct consequence of the definition of an induced simple plan as well as from the concept of admissibility explained in Section 2.1. Consider an admissible simple plan π with happening sequence {a mathematical formula}Aπ=(At0,…,Atk¯). If a durative action Da happens in π in the time interval {a mathematical formula}[ti+1,tj], we have that {a mathematical formula}ast∈Ati+1 and {a mathematical formula}aend∈Atj. Moreover, {a mathematical formula}j−i is necessarily odd and for every even {a mathematical formula}h=2,4,…,j−i−1, {a mathematical formula}Ati+h consists of {a mathematical formula}ainv and, possibly, over all conditions of other durative actions happening in the original plan Π simultaneously or intertwined with Da. Finally, for {a mathematical formula}h=1,3,…,n−2, {a mathematical formula}Ati+h consists of actions that appear in simple admissible plans and that, consequently, inherit such constraints.
      </paragraph>
      <paragraph label="Definition 41">
       Admissible actionsA sequence {a mathematical formula}A=(A1,A2,…,An) is:
      </paragraph>
      <list>
       <list-item label="•">
        admissible if there exists an admissible simple plan π with happening sequence {a mathematical formula}Aπ=(At0,…,Atk¯) such that {a mathematical formula}(A1,A2,…,An)=(Ati+1,…,Ati+n) for some {a mathematical formula}i=0,…,k¯−n.
       </list-item>
       <list-item label="•">
        Da-admissible, for some durative action Da, if it is admissible and Da happens in the corresponding simple plan π as above in {a mathematical formula}[ti+1,ti+n]. In particular, {a mathematical formula}ast∈A1 and {a mathematical formula}aend∈An.
       </list-item>
      </list>
      <paragraph>
       The existence of Da-admissible sequences that are executable imposes specific conditions on the durative action Da:
      </paragraph>
      <paragraph label="Proof">
       Consider a durative action{a mathematical formula}Da=(ast,ainv,aend)and assume that there exists an executable Da-admissible sequence. Then, the following conditions are satisfied:{a mathematical formula}{a mathematical formula}where the postconditions{a mathematical formula}Γ±have been defined in(5).Suppose that {a mathematical formula}A=(A1,A2,…,An) is Da-admissible and executable. Since {a mathematical formula}(A1,A2) is executable, Proposition 30 implies that{a mathematical formula} Since {a mathematical formula}ast∈A1 and {a mathematical formula}A1 consists of pairwise non-interfering actions, we have that{a mathematical formula} Finally, equations (10) and (11), together with the fact that {a mathematical formula}ainv∈A2, yield conditions (8). Conditions (9) can be similarly proven.  □
      </paragraph>
      <paragraph>
       Durative actions not satisfying any of the conditions expressed in the previous result, can be ignored in our analysis. From now on we thus assume that all durative actions satisfy conditions (8) and (9) above.
      </paragraph>
      <paragraph>
       To study the safety of a Da-admissible sequence, we can, in many cases, reduce the analysis of the durative action Da to the analysis of an auxiliary sequence of just two actions {a mathematical formula}Da⁎=(a⁎st,a⁎end), where {a mathematical formula}a⁎st and {a mathematical formula}a⁎end are actions such that:{a mathematical formula}
      </paragraph>
      <paragraph label="Remark 43">
       The executability assumption (2) automatically extends from {a mathematical formula}ast and {a mathematical formula}aend to the auxiliary actions {a mathematical formula}a⁎st and {a mathematical formula}a⁎end, as a consequence of condition (9).
      </paragraph>
      <paragraph>
       The relation between the two sequences Da and {a mathematical formula}Da⁎ is clarified by the following result. Assume, as always, that a template {a mathematical formula}T and an instance γ have been fixed.
      </paragraph>
      <paragraph label="Proposition 44">
       The following facts hold:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}(s0,s1,s2)∈S(ast,ainv)if and only if{a mathematical formula}s1=s2and{a mathematical formula}(s0,s1)∈Sa⁎st;
       </list-item>
       <list-item>
        {a mathematical formula}(s0,s1,s2)∈S(ainv,aend)if and only if{a mathematical formula}s0=s1and{a mathematical formula}(s1,s2)∈Sa⁎end;
       </list-item>
       <list-item>
        {a mathematical formula}(s0,s1,s2,s3)∈SDaif and only if{a mathematical formula}s1=s2and{a mathematical formula}(s0,s1,s3)∈SDa⁎;
       </list-item>
       <list-item>
        {a mathematical formula}(ast,ainv)is individually γ-safe if and only if{a mathematical formula}a⁎stis strongly γ-safe;
       </list-item>
       <list-item>
        {a mathematical formula}(ainv,aend)is individually γ-safe if and only if{a mathematical formula}a⁎endis strongly γ-safe;
       </list-item>
       <list-item>
        Da is individually γ-safe if and only if{a mathematical formula}Da⁎is individually γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       (i): Suppose {a mathematical formula}(s0,s1,s2)∈S(ast,ainv). Since {a mathematical formula}ainv only contains preconditions, we have that {a mathematical formula}s1=s2. Note now that {a mathematical formula}s1=ξ(ast,s0)=(s0∪Effast+)∖Effast− must satisfy the conditions {a mathematical formula}Preainv+⊆s1⊆(Preainv−)c. This yields {a mathematical formula}Preainv+⊆s0∪Effast+ and thus {a mathematical formula}Preainv+∖Effast+⊆s0. Similarly, from {a mathematical formula}s0∖Effast−⊆(Preainv−)c, we obtain that {a mathematical formula}s0⊆(Preainv−∖Effast−)c. This implies that also {a mathematical formula}a⁎st is applicable on {a mathematical formula}s0 and {a mathematical formula}s1=ξ(a⁎st,s0) since {a mathematical formula}ast and {a mathematical formula}a⁎st have the same effects. If instead {a mathematical formula}(s0,s1)∈Sa⁎st, we have that {a mathematical formula}ast is applicable on {a mathematical formula}s0 (since the preconditions of {a mathematical formula}ast are also preconditions of {a mathematical formula}a⁎st) and {a mathematical formula}s1=ξ(a⁎st,s0)=ξ(ast,s0). (ii) is proven similarly to (i). (iii) follows from (i) and (ii) and, finally, (iv), (v), and (vi) follow, respectively, from (i), (ii), and (iii).  □
      </paragraph>
      <paragraph>
       The next result studies the effect of exchanging the start and end of a durative action Da with those of the auxiliary sequence {a mathematical formula}Da⁎ in a Da-admissible sequence.
      </paragraph>
      <paragraph label="Proof">
       Consider a durative action{a mathematical formula}Da=(ast,ainv,aend)and a Da-admissible sequence of actions{a mathematical formula}A=({ast},A2,…,An−1,{aend}). Let{a mathematical formula}A⁎=({a⁎st},A2,…,An−1,{a⁎end}). Then{a mathematical formula}SA=SA⁎. In particular,Ais individually γ-safe if and only if{a mathematical formula}A⁎is individually γ-safe.Since {a mathematical formula}A⁎ differs from A only for having more preconditions, it holds that {a mathematical formula}SA⊇SA⁎. Conversely, suppose {a mathematical formula}(s0,…,sn)∈SA. Then, {a mathematical formula}(s0,s1,s1)∈S(ast,ainv). Therefore, by (i) of Proposition 44, we have that {a mathematical formula}(s0,s1)∈Sa⁎st. Similarly, using (ii) of Proposition 44, we obtain that {a mathematical formula}(sn−1,sn)∈Sa⁎end. These two facts together with {a mathematical formula}(s1,s2,…,sn−1)∈S(A2,…,An−1), yield {a mathematical formula}(s0,…,sn)∈SA⁎.  □
      </paragraph>
      <paragraph>
       The last proposition implies that, in analysing the state dynamics in an executable plan, we can replace the start and end of each durative action Da with the corresponding ones of the auxiliary sequence {a mathematical formula}Da⁎, if the start and end are isolated from other actions. This is useful for two reasons. On the one hand, there are cases in which {a mathematical formula}Da⁎ is strongly safe even if Da is not. On the other hand, we can directly apply Theorem 38 to {a mathematical formula}Da⁎ since it is of length 2.
      </paragraph>
      <paragraph>
       As we shall see later, our sufficient results for the invariance of a template always require safety (strong or simple) of the auxiliary actions {a mathematical formula}Da⁎=(a⁎st,a⁎end). The check for strong safety can be done by considering the single components of {a mathematical formula}Da⁎ and referring back to the analysis that we carried out in the previous section. Below, we give a full characterisation of simple safety for auxiliary actions.
      </paragraph>
      <paragraph>
       Note first that if {a mathematical formula}Da⁎=(a⁎st,a⁎end) is weakly γ-safe (Definition 35), necessarily {a mathematical formula}Da⁎ is executable, {a mathematical formula}a⁎st is strongly γ-safe and {a mathematical formula}a⁎end is not strongly γ-safe. If, besides these three properties, {a mathematical formula}Da⁎ is γ-unreachable, then {a mathematical formula}Da⁎ is weakly γ-safe because of Remark 29. If we instead assume that {a mathematical formula}Da⁎ is weakly γ-safe and γ-reachable, then, because of Proposition 36, we have that {a mathematical formula}a⁎end is γ-unbounded. The following result completely characterises simple γ-safety for such actions.
      </paragraph>
      <paragraph label="Proposition 46">
       Let{a mathematical formula}Da⁎=(a⁎st,a⁎end)be a γ-reachable sequence such that{a mathematical formula}a⁎stis strongly γ-safe and{a mathematical formula}a⁎endis γ-unbounded. Then,{a mathematical formula}Da⁎is weakly γ-safe if and only if one of the following mutually exclusive conditions are satisfied:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}a⁎stis γ-irrelevant,{a mathematical formula}|Prea⁎γst+|=1,{a mathematical formula}Prea⁎γst+⊆Effa⁎γst−;
       </list-item>
       <list-item>
        {a mathematical formula}a⁎stis γ-irrelevant,{a mathematical formula}|Prea⁎γst+|=1,{a mathematical formula}Prea⁎γst+⊈Effa⁎γst−,{a mathematical formula}Prea⁎γst+⊆Effa⁎γend;
       </list-item>
       <list-item>
        {a mathematical formula}a⁎stis γ-irrelevant,{a mathematical formula}|Prea⁎γst+|=0,{a mathematical formula}Prea⁎γst−∪Effa⁎γst∪Effa⁎γend=γ(T);
       </list-item>
       <list-item>
        {a mathematical formula}a⁎stis γ-relevant,{a mathematical formula}Effa⁎γst+⊆Effa⁎γend.
       </list-item>
      </list>
      <paragraph label="Proof">
       Note that {a mathematical formula}Da⁎ is γ-reachable and {a mathematical formula}a⁎st strongly γ-safe. Hence, {a mathematical formula}Da⁎ is weakly γ-safe if and only if {a mathematical formula}Da⁎γ is individually γ-safe. This last fact is equivalent to showing that, given any state sequence {a mathematical formula}(s0,s1,s2)∈SDa⁎γ such that {a mathematical formula}s0∈γ(T) and {a mathematical formula}w(γ,s0)≤1, it holds that {a mathematical formula}w(γ,si)≤1 for {a mathematical formula}i=2 (since for {a mathematical formula}i=1 that follows from the strong safety of {a mathematical formula}a⁎st). Let{a mathematical formula} We need to show that, for every {a mathematical formula}s1∈Wγ, we have that {a mathematical formula}w(γ,s2)≤1, where{a mathematical formula} Since {a mathematical formula}a⁎end is γ-unbounded, the condition {a mathematical formula}w(γ,s2)≤1 is equivalent to{a mathematical formula}Since {a mathematical formula}a⁎st is γ-reachable and strongly γ-safe, it follows from Theorem 18 that it is either γ-irrelevant or γ-relevant. If {a mathematical formula}a⁎st is γ-irrelevant and {a mathematical formula}|Prea⁎γst+|=1, we have that {a mathematical formula}Wγ={Prea⁎γst+∖Effa⁎γst−}. Combining this with (12), we thus have that in this case {a mathematical formula}Da⁎ is γ-safe if and only if{a mathematical formula} This leads to the two possible cases (a) and (b).Suppose now that {a mathematical formula}a⁎st is γ-irrelevant and {a mathematical formula}|Prea⁎γst+|=0. In this case,{a mathematical formula} Combining this with (12), we thus have that in this case {a mathematical formula}Da⁎ is γ-safe if and only if{a mathematical formula} This leads to case (c).Finally, if {a mathematical formula}α⁎γst is relevant we have that {a mathematical formula}Wγ={Effa⁎γst+}. Combining this with (12), we obtain that in this case {a mathematical formula}Da⁎ is γ-safe if and only if condition (d) is verified.  □
      </paragraph>
      <paragraph label="Remark 47">
       If Condition (a) of Proposition 46 holds, this implies that the same conditions need to be satisfied by {a mathematical formula}ast: {a mathematical formula}|Preaγst+|=1, {a mathematical formula}Preaγst+⊆Effaγst−.
      </paragraph>
      <paragraph label="Definition 48">
       Weakly safe durative actionsWe say that {a mathematical formula}Da⁎ is weakly γ-safe of type (x) where {a mathematical formula}x∈{a,b,c,d} if it is γ-reachable, {a mathematical formula}a⁎st is strongly γ-safe, {a mathematical formula}a⁎end is γ-unbounded, and, finally, {a mathematical formula}Da⁎ satisfies the condition (x) of Proposition 46.
      </paragraph>
      <paragraph label="Example 9">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′}. Fig. 5 shows possible instances of actions of types (a)–(d).
      </paragraph>
      <paragraph>
       When the start or the end of a durative action Da happens simultaneously with other actions, the reduction of Da to {a mathematical formula}Da⁎ cannot be performed in general as shown in the following example.
      </paragraph>
      <paragraph label="Example 10">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′,q″}. Fig. 6 shows that, when the durative actions Da and {a mathematical formula}Da′ are considered in isolation, both {a mathematical formula}a⁎st and {a mathematical formula}a⁎′st are strongly γ-safe since they are γ-unreachable. Since {a mathematical formula}a⁎end and {a mathematical formula}a⁎′end are γ-irrelevant, {a mathematical formula}Da⁎ and {a mathematical formula}Da⁎′ are strongly γ-safe and thus (by Proposition 44) Da and {a mathematical formula}Da′ are individually γ-safe. However, if we now consider the case in which Da and {a mathematical formula}Da′ happen simultaneously, giving rise to the sequence {a mathematical formula}A=(A1={ast,a′st},A2={ainv,a′inv}), we see that A is not individually γ-safe. In fact, if we set {a mathematical formula}s0={q″} with {a mathematical formula}w(γ,s0)=1, we have that {a mathematical formula}s1=ξ(s0,A1)={q,q″,q‴} with {a mathematical formula}w(γ,s1)=3, which violates the definition of individual γ-safety.
      </paragraph>
      <paragraph>
       Note that, in the previous example, the two durative actions are γ-unreachable. The following result shows that such pathological phenomena can only happen in that case and will be instrumental for the results of the next section.
      </paragraph>
      <paragraph label="Proposition 49">
       Let Da be a γ-reachable durative action such that{a mathematical formula}astis not strongly γ-safe, while{a mathematical formula}a⁎stis strongly γ-safe. Then,
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}a⁎stis γ-bounded;
       </list-item>
       <list-item>
        for every action set{a mathematical formula}A1such that{a mathematical formula}({ast}∪A1,ainv)is executable,{a mathematical formula}({ast}∪A1,ainv)is individually γ-safe.
       </list-item>
      </list>
      <paragraph label="Proof">
       Since Da is γ-reachable, it follows from Proposition 36, that {a mathematical formula}ast must necessarily be γ-unbounded. In particular, this yields {a mathematical formula}Preaγst+=∅. Therefore, {a mathematical formula}Prea⁎γst+=Preaγinv+∖Effaγst+ cannot have any intersection with {a mathematical formula}Effaγst. This says that {a mathematical formula}a⁎st cannot be γ-balanced. Since it also cannot be γ-unreachable (since Da is γ-reachable), it follows from Corollary 21 that {a mathematical formula}a⁎st must be γ-bounded. This proves (i).Suppose now that the sequence {a mathematical formula}({ast}∪A1,ainv) is executable and let {a mathematical formula}q∈EffAγ1+. By (i), it follows that {a mathematical formula}q∈Effaγst∪Prea⁎γst−. Note that q cannot belong to either {a mathematical formula}Effaγst− or {a mathematical formula}Preaγst−, since {a mathematical formula}ast and the actions in {a mathematical formula}A1 must be non-interfering. On the other hand, q cannot belong to {a mathematical formula}Preaγinv−, otherwise the sequence would not be executable. Therefore the only possibility is that {a mathematical formula}q∈Effaγst+. As a result we have that {a mathematical formula}EffAγ1+⊆Effaγst+. Consider now {a mathematical formula}A˜1 the action set obtained from {a mathematical formula}A1 by eliminating all positive effects belonging to {a mathematical formula}γ(T). We have that {a mathematical formula}{ast}∪A1={ast}∪A˜1. Consider now the sequence {a mathematical formula}(A˜1,ast,ainv) and note that {a mathematical formula}A˜1 is γ-irrelevant, and {a mathematical formula}(ast,ainv) is individually γ-safe because of (iv) of Proposition 44. Therefore, by Proposition 26, {a mathematical formula}(A˜1,ast,ainv) is also individually γ-safe, and thus also {a mathematical formula}({ast}∪A1,ainv).  □
      </paragraph>
      <paragraph>
       No similar results hold for the end parts of durative actions as next example shows.
      </paragraph>
      <paragraph label="Example 11">
       Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′}. When the durative actions Da and {a mathematical formula}Da′ (Fig. 7) are considered in isolation, both {a mathematical formula}a⁎end and {a mathematical formula}a⁎′end are strongly γ-safe since they are γ-bounded. Since {a mathematical formula}a⁎st and {a mathematical formula}a⁎′st are γ-irrelevant, {a mathematical formula}Da⁎ and {a mathematical formula}Da⁎′ are strongly γ-safe and thus (by Proposition 44) Da and {a mathematical formula}Da′ are individually γ-safe. Moreover, Da and {a mathematical formula}Da′ are both γ-reachable. However, if Da and {a mathematical formula}Da′ happen simultaneously, giving rise to the sequence {a mathematical formula}A=(A1={ainv,a′inv},A2={aend,a′end}), A is not individually γ-safe. If we put {a mathematical formula}s0=∅ with {a mathematical formula}w(γ,s0)=0, we have that {a mathematical formula}s1=ξ(s0,A1)=∅ and {a mathematical formula}s2=ξ(s1,A2)={q,q′} with {a mathematical formula}w(γ,s2)=2, which violates the definition of individual γ-safety.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Conditions for the invariance of a template
     </section-title>
     <paragraph>
      Any plan π where all actions are strongly safe and all durative actions are safe and take place in isolation, i.e. with no other actions happening in between them, yields a safe happening sequence {a mathematical formula}Aπ, as a consequence of Corollary 27. The difficulty, in general, is that durative actions can in principle start or end together and be intertwined with other instantaneous or durative actions. Safety of durative actions must therefore be accompanied by suitable hypotheses guaranteeing that dangerous intertwinements or simultaneous happenings cannot take place in executable plans. In this way, we can work out sufficient conditions for the invariance of a template, which will be useful in analysing concrete examples.
     </paragraph>
     <paragraph>
      In this section, we present two results that give sufficient conditions for the invariance of a template. The first deals with the particular case when all instantaneous actions are strongly safe and all durative actions Da are such that {a mathematical formula}Da⁎ is strongly safe. The second result considers a more general case when there are durative actions Da for which {a mathematical formula}Da⁎ is only weakly safe.
     </paragraph>
     <paragraph>
      Considering a template {a mathematical formula}T and an instance γ, we denote by {a mathematical formula}GAd(wk,γ) the collection of durative actions that are not strongly γ-safe and with {a mathematical formula}GAst(wk,γ) and {a mathematical formula}GAend(wk,γ) the collection of their start and end fragments, respectively. The following property prevents the simultaneous end of durative actions that could yield unsafe phenomena.
     </paragraph>
     <paragraph label="Definition 50">
      Relevant right isolated actionsFor a template {a mathematical formula}T, the set of durative actions {a mathematical formula}GAd is said to be relevant right isolated if, for every instance γ and for every {a mathematical formula}Da1,Da2∈GAd(wk,γ), one of the following conditions is satisfied:
     </paragraph>
     <list>
      <list-item label="(i)">
       {a mathematical formula}|Effaγ1end+∪Effaγ2end+|≤1;
      </list-item>
      <list-item label="(ii)">
       at least one of the two pairs {a mathematical formula}{a1end,a2end}, {a mathematical formula}{a1inv,a2inv} is either mutex or non executable;
      </list-item>
      <list-item label="(iii)">
       the sequence {a mathematical formula}({a1inv,a2inv},{a1end,a2end}) is γ-unreachable.
      </list-item>
     </list>
     <paragraph label="Theorem 51">
      Consider a template{a mathematical formula}Tand suppose that the set of instantaneous actions{a mathematical formula}GAiand that of durative actions{a mathematical formula}GAdsatisfy the following properties:
     </paragraph>
     <list>
      <list-item>
       every{a mathematical formula}a∈GAiis strongly safe;
      </list-item>
      <list-item>
       for every instance γ and every{a mathematical formula}Da∈GAd(wk,γ),{a mathematical formula}Da⁎is γ-reachable and strongly γ-safe;
      </list-item>
      <list-item>
       {a mathematical formula}GAdis relevant right isolated.
      </list-item>
     </list>
     <paragraph label="Proof">
      Consider an executable simple plan π with happening sequence {a mathematical formula}Aπ=(At0,…,Atk¯) and any instance γ. We prove that {a mathematical formula}Aπ is individually γ-safe.We split happenings as follows: {a mathematical formula}Ati=Atist∪Atis∪Atiend where
      <list>
       {a mathematical formula}Atist is either empty or consists of the start fragments in {a mathematical formula}GAd(wk,γ);{a mathematical formula}Atiend is either empty or consists of the ending fragments in {a mathematical formula}GAd(wk,γ);{a mathematical formula}Atis=At∖(Atist∪Atiend) consists of strongly γ-safe actions (either instantaneous or possibly the starting and ending of durative actions in {a mathematical formula}GAd∖GAd(wk,γ)).Similarly, if
      </list>
      <paragraph>
       {a mathematical formula}Atiend≠∅, it either consists of all strongly γ-safe actions and is thus strongly γ-safe, or there exists a durative action {a mathematical formula}Da∈GAd(wk,γ) such that {a mathematical formula}aend is not strongly γ-safe and {a mathematical formula}aend∈Atiend. Suppose that there exists another durative action {a mathematical formula}Da′∈GAd(wk,γ) such that {a mathematical formula}a′end∈Atiend and {a mathematical formula}{aend,a′end} is γ-heavy. The two pairs {a mathematical formula}{ainv,a′inv}, {a mathematical formula}{aend,a′end} are necessarily composed of non-interfering actions and each of them is executable. Since {a mathematical formula}GAd is right relevant isolated, this implies that the sequence {a mathematical formula}({ainv,a′inv},{aend,a′end}) is γ-unreachable. Since {a mathematical formula}Ati−1 only consists of actions with no effects, it then follows from Proposition 32 that the sequence {a mathematical formula}(Ati−1,Atiend) is also γ-unreachable and thus individually γ-safe. The other possibility is that {a mathematical formula}EffAtiγend+=Effaγend+. Consider in this case {a mathematical formula}A˜tiend to be the action set obtained from {a mathematical formula}Atiend∖{aend} by eliminating all positive effects belonging to {a mathematical formula}γ(T). We have that {a mathematical formula}Atiend={aend}∪A˜tiend. Note now that {a mathematical formula}(ainv,) is individually γ-safe by (v) of Proposition 44. Considering that {a mathematical formula}Ati−1∖{ainv} only contains preconditions and {a mathematical formula}A˜tiend is strongly γ-safe, applying, in order, items (iii), (i) and (ii) of Proposition 26, we obtain that {a mathematical formula}(Ati−1,aend), {a mathematical formula}(Ati−1,aend,A˜tiend), and finally {a mathematical formula}(Ati−1,Atiend) are individually γ-safe.Note that, for each happening time {a mathematical formula}ti, there are four possibilities:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Atist=∅, {a mathematical formula}Atiend=∅: in this case {a mathematical formula}Ati=Atis is strongly γ-safe by definition;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Atist≠∅, {a mathematical formula}Atiend=∅: in this case, since {a mathematical formula}Atis and {a mathematical formula}(Atist,Ati+1) are individually γ-safe, using (i) and (ii) of Proposition 26, we obtain that {a mathematical formula}(Atis,Atist,Ati+1) and {a mathematical formula}(Ati,Ati+1)=(Atis∪Atist,Ati+1) are also individually γ-safe.
       </list-item>
       <list-item label="•">
        {a mathematical formula}Atist=∅, {a mathematical formula}Atiend≠∅: arguing analogously to the case above we obtain that {a mathematical formula}(Ati−1,Ati) is individually γ-safe.
       </list-item>
       <list-item label="•">
        {a mathematical formula}Atist≠∅, {a mathematical formula}Atiend≠∅: arguing analogously to the case above we obtain that {a mathematical formula}(Ati−1,Ati,Ati+1) is individually γ-safe.
       </list-item>
      </list>
      <paragraph>
       Using Corollary 27 we obtain that {a mathematical formula}Aπ is individually γ-safe.  □
      </paragraph>
     </paragraph>
     <paragraph>
      Note that assumption (iii) in the statement of Theorem 51 excludes the simultaneous end of durative actions; if such phenomena can be excluded a-priori, the hypothesis can be removed.{sup:4}
     </paragraph>
     <paragraph>
      When there are durative actions Da for which {a mathematical formula}Da⁎ is not strongly γ-safe, further hypotheses are needed in order to guarantee that the template {a mathematical formula}T is invariant. In this case, simultaneity can be harmful, but also any intertwinement between such a durative action and other actions. The following examples show the type of phenomena that can happen and that any theorem extending Theorem 51 needs to prevent.
     </paragraph>
     <paragraph label="Example 12">
      Consider a template {a mathematical formula}T and an instance γ such that {a mathematical formula}γ(T)={q,q′,q″}. Both the durative actions Da and {a mathematical formula}Da′ (Fig. 8) are γ-safe. However, they can intertwine in such a way that they give rise to a sequence that is not individually γ-safe: {a mathematical formula}A=(A1={ast},A2={a′st},A3={aend},A4={a′end}). If we put {a mathematical formula}s0={q} with {a mathematical formula}w(γ,s0)=1, we have that {a mathematical formula}s4={q′,q″} with {a mathematical formula}w(γ,s4)=2.
     </paragraph>
     <paragraph>
      The following definition describes a set of durative actions for which such phenomena cannot take place. It consists of three requirements acting, for each instantiation γ, on a subset {a mathematical formula}GAd(γ) of durative actions containing the potentially dangerous actions {a mathematical formula}GAd(wk,γ). The first prevents the simultaneous happening of two start fragments of such durative actions. The second requirement states instead that between the happening of two such start fragments there must be the end of a third durative action in {a mathematical formula}GAd(γ). This fact, because of the finiteness of the plans, will lead to the impossibility of intertwining between durative actions in the family {a mathematical formula}GAd(γ). Finally, the third requirement prevents the possibility that other γ-relevant actions might happen in the middle of a durative action in {a mathematical formula}GAd(γ).
     </paragraph>
     <paragraph>
      Before stating the exact definition, we set the following notation. Given an instance γ and a {a mathematical formula}GAd(γ) subset of durative actions, we denote by {a mathematical formula}GAst(γ) and {a mathematical formula}GAend(γ), respectively, the set of its start and end fragments.
     </paragraph>
     <paragraph label="Definition 52">
      Relevant non intertwining actionsGiven a template {a mathematical formula}T, the set of durative actions {a mathematical formula}GAd is said to be relevant non intertwining if, for every instance γ, we can find a subset of durative actions {a mathematical formula}GAd(γ)⊇GAd(wk,γ) such that the following property is satisfied. For every {a mathematical formula}Da∈GAd(γ) and for every γ-reachable Da-admissible sequence of actions{a mathematical formula} with {a mathematical formula}A1⊆GAst(γ), the following conditions are satisfied:
     </paragraph>
     <list>
      <list-item label="(i)">
       {a mathematical formula}A1={ast};
      </list-item>
      <list-item label="(ii)">
       If {a mathematical formula}b∈Aj∩GAst(γ) for {a mathematical formula}1&lt;j&lt;n, then there exists {a mathematical formula}b′∈Aj′∩GAend(γ) for some {a mathematical formula}1&lt;j′≤j;
      </list-item>
      <list-item label="(iii)">
       If {a mathematical formula}Aj∩(GAst(γ)∪GAend(γ))=∅ for every {a mathematical formula}j=2,…,n−1, then each {a mathematical formula}Aj is γ-irrelevant for {a mathematical formula}j=2,…,n−1.
      </list-item>
     </list>
     <paragraph>
      Considering, in this definition, subsets of durative actions possibly larger than {a mathematical formula}GAd(wk,γ) leads to a more flexible theory. An instance of this flexibility is later shown in Example 13.
     </paragraph>
     <paragraph>
      The following is the main technical result of this section: it expresses a sufficient condition for a template to be invariant under the assumptions that instantaneous and durative actions are safe and that the relevant-non-intertwining property holds. Later on, we will look for more easy-to-check conditions that guarantee the relevant non intertwining property.
     </paragraph>
     <paragraph label="Theorem 53">
      Consider a template{a mathematical formula}Tand suppose that the set of instantaneous actions{a mathematical formula}GAiand durative actions{a mathematical formula}GAdsatisfy the following properties:
     </paragraph>
     <list>
      <list-item>
       every{a mathematical formula}a∈GAiis strongly safe;
      </list-item>
      <list-item>
       for every{a mathematical formula}Da∈GAd,{a mathematical formula}Da⁎is safe;
      </list-item>
      <list-item>
       the set{a mathematical formula}GAdis relevant non intertwining.
      </list-item>
     </list>
     <paragraph label="Proof">
      Fix any executable simple plan π with happening sequence {a mathematical formula}Aπ=(At0,…,Atk¯) and any instance γ. Assume that {a mathematical formula}w(γ,Init)≤1. We prove that {a mathematical formula}Aπ is individually γ-safe.Consider the set of durative actions {a mathematical formula}GAd(γ) as in Definition 52. Suppose that we can prove that if {a mathematical formula}Da∈GAd(γ) appears in π at the time window {a mathematical formula}[th,tk] (namely, {a mathematical formula}ast∈Ath and {a mathematical formula}aend∈Atk), the corresponding action sequence {a mathematical formula}A=(Ath,…,Atk) satisfies the following conditions:
      <list>
       for every {a mathematical formula}i∈(h,k), {a mathematical formula}Ati consists exclusively of γ-irrelevant actions;for every {a mathematical formula}i∈[h,k), {a mathematical formula}Ati does not contain actions in {a mathematical formula}GAst(γ) except {a mathematical formula}ast∈Ath.It follows from
      </list>
      <paragraph>
       Proposition 1 on serializability that plan {a mathematical formula}π˜ is also executable. We denote its happening sequence as {a mathematical formula}Aπ˜=(A˜t0,…,A˜tk¯). For the sake of notational simplicity, happening times are denoted as those in π even if in general they differ and form a larger set. Note now that the happening times in {a mathematical formula}π˜ can be split into singletons {a mathematical formula}ti such that {a mathematical formula}A˜ti only consists of strongly γ-safe actions, and intervals {a mathematical formula}[ti+1,tj] such that there exists a durative action {a mathematical formula}Da∈GAd(γ) happening in that interval. In this case, we have that the subsequence {a mathematical formula}A=(A˜ti+1,…,A˜tj) is Da-admissible. Let {a mathematical formula}A⁎=(A˜ti∪{ainv},…,Atj∪{ainv}). Note that, since A is executable (since it appears in an executable plan), {a mathematical formula}A⁎ is also executable by Proposition 45. Since, by assumption (ii), {a mathematical formula}Da⁎ is γ-safe, it follows from Theorem 38, that {a mathematical formula}A⁎ is also γ-safe. Using again Proposition 45 we finally obtain that A is individually γ-safe.We have thus proven that each happening time {a mathematical formula}ti in the new plan {a mathematical formula}π˜ stays inside an individually γ-safe sequence (possibly of length 1) (see Fig. 9). By Corollary 27 this implies that {a mathematical formula}Aπ˜ is individually γ-safe. A repetitive use of statement (ii) of Proposition 26 now yields that {a mathematical formula}Aπ is also individually γ-safe.We are thus left with proving that every durative action {a mathematical formula}Da∈GAd(γ) in π satisfies properties (a) and (b) stated above. Suppose this is not true and let Da be the first action to start in π (in the time window {a mathematical formula}[th,tk]) and to violate either condition (a) or (b). Note that all durative actions in {a mathematical formula}GAd(γ) happening in π and starting strictly before time {a mathematical formula}th, will necessarily end at a time {a mathematical formula}t≤th by the way Da has been chosen. Moreover, all such durative actions will satisfy properties (a) and (b). We can then proceed as before and consider the splitting {a mathematical formula}Ati=Atist∪Atis∪Atiend for every {a mathematical formula}i≤h (note that in {a mathematical formula}th there could be, in principle, more than one starting action in {a mathematical formula}Athst). Consider now the auxiliary plan {a mathematical formula}π˜ constructed exactly like before for {a mathematical formula}t≤th and coinciding with π for {a mathematical formula}t&gt;th. As before, we denote its happening sequence as {a mathematical formula}Aπ˜=(A˜t0,…,A˜tk¯) using the same notation for the happening times as in π and we assume that {a mathematical formula}A˜th=Athst (this is for simplicity of notation considering that it would be instead {a mathematical formula}A˜th+ϵ=Athst). Note that since π is executable and {a mathematical formula}w(γ,Init)≤1, the sequence {a mathematical formula}Aπ is γ-reachable and consequently, because of (ii) of Proposition 32, {a mathematical formula}Aπ˜ is also γ-reachable. Arguing as above, we obtain that {a mathematical formula}(A˜t0,…,A˜th−1) is individually γ-safe. If we take any {a mathematical formula}(s˜0,…,s˜k¯)∈SAπ˜(γ), we thus have that {a mathematical formula}w(γ,s˜h−1)≤1. Consider now {a mathematical formula}A=(A˜th,A˜th+1,…,A˜tk)=(Athst,Ath+1,…,Atk) and note that, {a mathematical formula}(s˜h−1,…,s˜k)∈SA(γ) so that A is γ-reachable. It then follows from the relevant non intertwining property ((i) of Definition 52) that {a mathematical formula}Athst={ast}. Suppose now that property (b) stated above is not satisfied and let {a mathematical formula}l∈(h,k) be the first index such that {a mathematical formula}Atl∩GAst(γ)≠∅. By (ii) of Definition 52, it follows that there must exist a durative action {a mathematical formula}Da′∈GAd(γ) such that {a mathematical formula}a′end∈Atl′ for some {a mathematical formula}l′∈(h,l]. Note that such a durative action cannot start, in the plan π and thus also in the plan {a mathematical formula}π˜, before time {a mathematical formula}th for the way Da was chosen, it cannot either start at time {a mathematical formula}th by previous considerations or in the interval {a mathematical formula}(th,tl′) because of the way {a mathematical formula}l′ has been chosen. This proves that property (b) must be satisfied. Note that this also shows that {a mathematical formula}Ati does not contain actions in {a mathematical formula}GAend(γ) for any {a mathematical formula}i∈(h,k) (as the corresponding start fragment cannot happen either before or after time {a mathematical formula}th). Finally, {a mathematical formula}Ati is γ-irrelevant for every {a mathematical formula}i∈(h,k) because of (iii) of Definition 52. Therefore A satisfies properties (a) and (b) contrarily to the assumptions made on Da. The proof is now complete.  □
      </paragraph>
     </paragraph>
     <paragraph>
      The properties that the set of durative actions {a mathematical formula}GAd needs to satisfy to be relevant non intertwining, which are expressed in Definition 52, are in general difficult to check as they require considering sequences of actions of possibly any length. Below we give a sufficient condition that guarantees these properties hold but only involves pairs of durative and instantaneous actions. It is computationally much simpler and suitable to be later analysed at the lifted level of action schemas.
     </paragraph>
     <paragraph>
      We start with a property for pairs of actions {a mathematical formula}a,a′ that, when verified, prevents the happening of the action a followed by {a mathematical formula}a′, in any executable plan, where only irrelevant actions in a certain family happen in between. See (5) to recall the definition of the postconditions {a mathematical formula}Γa+ and {a mathematical formula}Γa− of an action a.
     </paragraph>
     <paragraph label="Definition 54">
      {a mathematical formula}M(γ)-unreachable actionsConsider a template {a mathematical formula}T, an instantiation γ and a subset {a mathematical formula}M(γ)⊆GA of γ-irrelevant actions. A pair of actions {a mathematical formula}(a,a′) is {a mathematical formula}M(γ)-unreachable if any of the following conditions are satisfied:
     </paragraph>
     <list>
      <list-item label="(i)">
       there exists {a mathematical formula}q∈Γa+∩Prea′− such that, for every {a mathematical formula}a″∈M(γ), {a mathematical formula}q∉Effa″−;
      </list-item>
      <list-item label="(ii)">
       there exists {a mathematical formula}q∈Γa−∩Prea′+ such that, for every {a mathematical formula}a″∈M(γ), {a mathematical formula}q∉Effa″+;
      </list-item>
      <list-item label="(iii)">
       {a mathematical formula}|Preaγ+∪(Preaγ′+∖Effaγ+)|&gt;1.
      </list-item>
     </list>
     <paragraph>
      The first condition essentially says that the application of the action a leads to a state containing a ground atom q that needs to be false in order to then apply {a mathematical formula}a′ and that there is no action in {a mathematical formula}M(γ) that can make this atom false. The second condition is analogous to the first, but exchanges the role of true and false atoms. Finally, the third condition requires that {a mathematical formula}(a,a′) be a γ-unreachable pair, assuming that it is executable. The following result explains the name that we have chosen for these properties.
     </paragraph>
     <paragraph label="Proof">
      A similar argument can be used when condition (ii) is satisfied.Finally, assume that condition (iii) is satisfied. Note that, since {a mathematical formula}A2,…,An−1 are γ-irrelevant, {a mathematical formula}Preaγ+∪(Preaγ′+∖Effaγ+)⊆s0 and this contradicts the fact that {a mathematical formula}(s0,…,sn)∈SA(γ).  □
     </paragraph>
     <paragraph>
      The following is a stronger version of the relevant non intertwining property that is completely formulated at the level of pairs of actions, without referring to sequences. It consists of three points that correspond to the three properties required in Definition 52. It will be convenient to first introduce some additional notation. Given an instance γ and a {a mathematical formula}GAd(γ) subset of durative actions, we denote by {a mathematical formula}GA(γ)irr and {a mathematical formula}GA(γ)rel the set of actions in {a mathematical formula}GA∖(GAst(γ)∪GAend(γ)) that are, respectively, γ-irrelevant and γ-relevant.
     </paragraph>
     <paragraph label="Definition 56">
      Pairwise relevant non-overlapping actionsFor a template {a mathematical formula}T, the set of durative actions {a mathematical formula}GAd is said to be pairwise relevant non-overlapping if, for every instance γ, we can find a subset of durative actions {a mathematical formula}GAd(γ)⊇GAd(wk,γ) such that the following properties are satisfied:
     </paragraph>
     <list>
      <list-item label="(A)">
       for every {a mathematical formula}Da1,Da2∈GAd(γ), one of the following conditions holds true:
      </list-item>
      <list-item label="(B)">
       for every {a mathematical formula}Da1,Da2∈GAd(γ), one of the following conditions holds true:
      </list-item>
      <list-item label="(C)">
       for every {a mathematical formula}Da1∈GAd(γ), {a mathematical formula}a2∈GA(γ)rel, one of the following conditions is satisfied:
      </list-item>
     </list>
     <paragraph>
      The next result expresses a sufficient condition for the set {a mathematical formula}GAd to be relevant non intertwining.
     </paragraph>
     <paragraph label="Proposition 57">
      Consider a template{a mathematical formula}T. The set{a mathematical formula}GAdis relevant non intertwining if the following conditions are satisfied:
     </paragraph>
     <list>
      <list-item>
       for every{a mathematical formula}Da∈GAd,{a mathematical formula}astis strongly safe;
      </list-item>
      <list-item>
       {a mathematical formula}GAdis pairwise relevant non-overlapping
      </list-item>
     </list>
     <paragraph label="Proof">
      For a fixed γ, consider the set of durative actions {a mathematical formula}GAd(γ) as in Definition 56. Let {a mathematical formula}Da∈GAd(γ) and consider a γ-reachable Da-admissible sequence{a mathematical formula} such that {a mathematical formula}A1⊆GAst(γ). We first show that property (i) in Definition 52 holds true. Assume, by contradiction, that {a mathematical formula}Da′≠Da is such that {a mathematical formula}a′st∈A1. We now show that Da and {a mathematical formula}Da′ violate property A in the above definition. Indeed, since A is admissible, {a mathematical formula}{ast,a′st} and {a mathematical formula}{ainv,a′inv} are non-interfering and executable. We now show that {a mathematical formula}({ast,a′st},{ainv,a′inv}) is γ-reachable. Note first that {a mathematical formula}(A1,A2) is clearly γ-reachable. By assumption (ii), {a mathematical formula}A˜1=A1∖{ast,a′st} only consists of strongly γ-safe actions. Consider {a mathematical formula}A˜=(A˜1,{ast,a′st},A2). Notice that if {a mathematical formula}(s0,s1,s2)∈S(A1,A2)(γ), then {a mathematical formula}(s0,s˜1,s1,s2)∈SA˜(γ) for some {a mathematical formula}s˜1 such that {a mathematical formula}w(γ,s˜1)≤1. This implies that {a mathematical formula}B=({ast,a′st},A2) is also γ-reachable since {a mathematical formula}(s˜1,s1,s2)∈SB. Considering that {a mathematical formula}A2 only consists of invariants, by (i) of Proposition 32, we have that {a mathematical formula}({ast,a′st},{ainv,a′inv}) is γ-reachable. Finally, note that the end fragment of the durative action {a mathematical formula}Da′ can either appear in {a mathematical formula}Ak for some {a mathematical formula}k&lt;n, or appear in {a mathematical formula}An, or not appear in the sequence as the durative action {a mathematical formula}Da′ ends (in the plan of which A is a subsequence) after the end of Da. In the first and the third case we have, respectively, that {a mathematical formula}{ainv,a′end} or {a mathematical formula}{aend,a′inv} is non-interfering. In the second case, {a mathematical formula}{aend,a′end}, is either mutex or non executable. Note that this second case can only happen when Da and {a mathematical formula}Da′ are not equivalent (they must differ in at least a fragment by the standing assumption made on simple plans). This shows that also (Aiii) does not hold. Therefore {a mathematical formula}GAst(γ)={ast}. This proves (i) in Definition 52.Suppose now that (ii) in Definition 52 does not hold true for A. Let {a mathematical formula}j&gt;1 be the first index for which (ii) is violated, namely for which we can find {a mathematical formula}Da′∈GAd(γ) such that {a mathematical formula}a′st∈Aj while {a mathematical formula}Aj′∩GAend(γ)=∅ for every {a mathematical formula}0&lt;j′&lt;j. The pair {a mathematical formula}{ainv,a′st} is non-interfering by Definition 41 of an admissible sequence. Moreover, arguing as in the previous case above regarding the timing of the end fragments of Da and {a mathematical formula}Da′, we conclude that either one of the pairs {a mathematical formula}{a1inv,a2end}, {a mathematical formula}{a1end,a2inv} must be non-interfering or the pair {a mathematical formula}{a1end,a2end} must be non-interfering and executable. Since {a mathematical formula}({ast},A2,…,Aj−1,{a′st}) is γ-reachable, it follows from assumption B in Definition 56 that there must exist {a mathematical formula}0&lt;j′&lt;j such that {a mathematical formula}Aj′⊈GA(γ)irr. Let {a mathematical formula}j′ be the first index for which this happens. Since, by construction, {a mathematical formula}Aj′∩(GAst(γ)∪GAend(γ))=∅, there must exist {a mathematical formula}b∈Aj′∩∈GA(γ)rel. Clearly, {a mathematical formula}{ainv,b} is non interfering and since {a mathematical formula}({ast},A2,…,Aj′−1,{b}) is γ-reachable and by construction {a mathematical formula}Ah⊆GA(γ)irr for every {a mathematical formula}h=2,…,j′−1, property (C) in Definition 56 is violated. Therefore this proves (ii) in Definition 52.Suppose now that {a mathematical formula}Aj∩(GAst(γ)∪GAend(γ))=∅ for every {a mathematical formula}j=2,…,n−1. If (iii) in Definition 52 does not hold true for A, consider {a mathematical formula}j&gt;1 to be the first index for which (iii) is violated, namely {a mathematical formula}Aj is not γ-irrelevant, and let {a mathematical formula}b∈Aj be any action which is not γ-irrelevant. Clearly, {a mathematical formula}b∈GA(γ)rel and, arguing as above, we deduce that Da and b again violate property (C). The proof is thus complete.  □
     </paragraph>
     <paragraph>
      Based on the previous results, we conclude with a simple sufficient condition for the invariance, which is very useful in analysing concrete cases.
     </paragraph>
     <paragraph label="Corollary 58">
      Consider a template{a mathematical formula}Tand suppose that, for every instance γ,
     </paragraph>
     <list>
      <list-item label="•">
       every{a mathematical formula}Da∈GAd(wk,γ)is such that{a mathematical formula}Da⁎is weakly γ-safe of type (a);
      </list-item>
      <list-item label="•">
       every{a mathematical formula}a∈GA∖(GAst(wk,γ)∪GAend(wk,γ))is either γ-irrelevant or γ-balanced.
      </list-item>
     </list>
     <paragraph label="Proof">
      It is clear that condition (i) and (ii) of Theorem 53 are satisfied. In order to check that {a mathematical formula}GAd is relevant non intertwining, we show that the properties (i) and (ii) of Proposition 57 are satisfied. Fix any instance γ. Note that the assumption that {a mathematical formula}Da⁎ is weakly γ-safe of type (a) implies, in particular, that {a mathematical formula}a⁎st and {a mathematical formula}ast are irrelevant and thus strongly γ-safe. Therefore property (i) is satisfied. We now show that, choosing {a mathematical formula}GAd(γ)=GAd(wk,γ), properties (A), (B), and (C) of the pairwise relevant non overlapping property are satisfiedConsider {a mathematical formula}Da1,Da2∈GAd(wk,γ). It follows from the fact that {a mathematical formula}Da⁎1 and {a mathematical formula}Da⁎2 are both weakly γ-safe of type (a) (see Remark 47) that{a mathematical formula} If {a mathematical formula}a1st and {a mathematical formula}a2st are non-interfering, it follows that {a mathematical formula}q1≠q2 and, in this case, {a mathematical formula}{a1st,a2st} is γ-unreachable. This proves property (A). In order to prove (B), we go back to (16) and we consider two possible cases. If {a mathematical formula}q1=q2 we have that {a mathematical formula}q1∈Γa1st−∩Prea2st+ and, since {a mathematical formula}q1∈γ(T), for sure {a mathematical formula}q1∉Effa″+ for any {a mathematical formula}a″ that is γ-irrelevant. This implies that condition (ii) of Definition 54 is satisfied. If instead {a mathematical formula}q1≠q2, we have that condition (iii) of Definition 54 is instead satisfied. In any case this says that the pair {a mathematical formula}(a1 st,a2 st) is {a mathematical formula}GA(wk,γ)irr-unreachable. This proves (B). Finally (C) can be proven exactly like (B).  □
     </paragraph>
     <paragraph>
      Our results have a broader application than the case in Corollary 58 as shown in the following example.
     </paragraph>
     <paragraph label="Example 13">
      Consider a domain with two durative actions {a mathematical formula}Da1 and {a mathematical formula}Da2 (shown in Fig. 10) and a template {a mathematical formula}T with just an instance γ such that {a mathematical formula}γ(T)={q,q′}. {a mathematical formula}Da1 is strongly γ-safe, while {a mathematical formula}Da2 is weakly γ-safe of type (a). Note that Corollary 58 cannot be applied since {a mathematical formula}a1end is γ-bounded. Indeed, the template is not invariant: Fig. 10 shows a triple intertwinement of two copies of {a mathematical formula}Da1 and {a mathematical formula}Da2 that leads to a sequence that is not individually γ-safe. This sequence can certainly be thought of as the happening sequence of an executable simple plan. Consequently, {a mathematical formula}T is not invariant.If we modify the durative action {a mathematical formula}Da1 adding an over all condition {a mathematical formula}Prea1inv={q}, the intertwining proposed would no longer be an admissible sequence. Even if Corollary 58 can still not be applied, we now show that, with this modification, the set {a mathematical formula}GAd={Da1,Da2} is pairwise relevant non overlapping. To show this, we fix {a mathematical formula}GAd(γ)={Da1,Da2} in Definition 56. Conditions (A) and (B) must be checked for any ordered pair of durative actions. In our case, there are four possibilities: two identical copies of {a mathematical formula}Da1 or of {a mathematical formula}Da2, the pair {a mathematical formula}Da1,Da2 or the pair {a mathematical formula}Da2,Da1. Note that if we pick two copies of {a mathematical formula}Da1, conditions (Aiii) and (Biii) hold true because of the over all condition. If we pick two copies of {a mathematical formula}Da2, (Ai) holds true. Moreover, considering that {a mathematical formula}GA(γ)irr=∅, it follows that the pair {a mathematical formula}(a2st,a2st) is {a mathematical formula}GA(γ)irr-unreachable (condition (ii) in Definition 54 is satisfied). Therefore two copies of {a mathematical formula}Da2 satisfy condition (Bii). Finally, if we consider the pair {a mathematical formula}Da1,Da2 or {a mathematical formula}Da2,Da1, we have that {a mathematical formula}Prea1st,a2st+={q,q′} so that {a mathematical formula}{a1st,a2st} is γ-unreachable and thus (Aii) is satisfied. Using again condition (ii) in Definition 54 we can check that both pairs {a mathematical formula}(a1st,a2st) and {a mathematical formula}(a2st,a1st) are {a mathematical formula}GA(γ)irr-unreachable, so that (Bii) holds true. Finally, note that condition (C) is empty in our case since {a mathematical formula}GA(γ)rel=∅. Thanks to Proposition 57 and Theorem 53, we conclude that {a mathematical formula}T is invariant.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Safety of action schemas for a template
     </section-title>
     <paragraph>
      In Section 6, we presented results that guaranteed the invariance of a template: Theorem 51, Theorem 53 and Corollary 58. To be applied, we need to check that all instantaneous and durative actions satisfy a safety condition as well as other extra properties, which prevent potentially dangerous simultaneous happenings or intertwinements among actions. Since we aim to find invariants off-line quickly and efficiently, our algorithm does not work at the level of actions. Instead, it reasons at the lifted level and uses the structure of the action schemas, i.e. their conditions and effects, to decide whether the ground instantiations of these schemas are safe or not. Our main goal in this section is to obtain lifted versions of Theorem 51, Theorem 53 and Corollary 58.
     </paragraph>
     <paragraph>
      In this section and in the following sections, we make an important assumption about the groundings of the action schemas. Precisely, for any action schema α, instantaneous or durative, we always assume that the grounding functions we consider {a mathematical formula}gr:Vα→O are injective. This restriction plays a crucial role in the formulations of our results and, on the other hand, does not essentially entail any loss of generality, if we allow a suitable modification of the domain's action schemas. First, we observe that, for many domains, injectivity follows automatically from type restrictions and explicit constraints (i.e. given two variables {a mathematical formula}x1 and {a mathematical formula}x2 of an action α, the preconditions of α contain the requirement {a mathematical formula}x1≠x2). If there are variables that can be bound to the same value, we can proceed as follows. Given a subset of variables {a mathematical formula}W⊆V, we define the action schema {a mathematical formula}αW by substituting any variable {a mathematical formula}w∈W with an amalgamated symbol {a mathematical formula}[W] in all the formulas of α. For example, if we have an action schema {a mathematical formula}move(rbt,loc1,loc2), we create an additional schema {a mathematical formula}moveSame(rbt,loc). The set of free variables of the new action schema {a mathematical formula}αW is thus {a mathematical formula}VαW=(Vα∖W)∪{[W]}. Note how an injective grounding for {a mathematical formula}αW corresponds to a grounding gr of α such that {a mathematical formula}gr(w1)=gr(w2) for every {a mathematical formula}w1,w2∈W while injectivity is otherwise maintained, namely, {a mathematical formula}gr(v1)≠gr(v2) if {a mathematical formula}{v1,v2}⊈W. Adding all action schemas {a mathematical formula}αW, as W varies among all possible subsets of {a mathematical formula}Vα, is equivalent to considering all possible grounding functions for the original action schema α. This procedure potentially leads to an exponential increase (in the cardinality {a mathematical formula}|Vα|) of the number of action schemas. However, in practical applications, the possibility of non-injectivity is typically limited to a few variables, and so the procedure leads to a controlled growth of the number of schemas and, consequently, of the computation complexity.
     </paragraph>
     <paragraph>
      Following assumption (2) concerning singleton actions and sets of actions, we assume that any action schema satisfies the condition:{a mathematical formula} Note that conditions (17) together with the injectivity constraint for groundings automatically imply that any grounded action {a mathematical formula}a=gr(α) satisfies the condition (2).
     </paragraph>
     <paragraph>
      In general, we call liftable a property P of ground actions if, given an action schema α, if one instantiation {a mathematical formula}a⁎=gr⁎(α) satisfies P, then all instantiations {a mathematical formula}a=gr(α) satisfy P. In this case, we say that the action schema α satisfies property P.
     </paragraph>
     <paragraph>
      The results presented in this and the next sections achieve two main goals. On the one hand, they show that the properties of safety introduced for instantaneous and durative actions in Sections 4 and 5 are liftable as well as the non intertwining properties, even if in a weaker sense, behind the formulation of Theorem 51, Theorem 53. On the other hand, they will give efficient characterisations of such properties at the lifted level, which we use in our algorithmic implementation (see Section 9).
     </paragraph>
     <paragraph>
      In the remaining part of this section, we analyse action schemas and their ground instantiations. We show that strong safety is liftable and work out a complete characterisation of this property at the lifted level. The next section is devoted to lifting properties for durative actions.
     </paragraph>
     <section label="7.1">
      <section-title>
       Structure and properties of action schemas
      </section-title>
      <paragraph>
       We start with the following definition that introduces the key concept of matching. It couples an action schema to a template and allows us to understand if, in the ground world, a ground formula appearing in an action schema is or is not in {a mathematical formula}γ(T).
      </paragraph>
      <paragraph label="Definition 59">
       MatchingConsider a template {a mathematical formula}T=(C,FC) and an action schema {a mathematical formula}α∈A. A formula l that appears in α is said to match{a mathematical formula}T via the template's component {a mathematical formula}c=〈r/k,p〉∈C if:
       <list>
        {a mathematical formula}Rel[l]=〈r/k〉; andif l is universally quantified, {a mathematical formula}VarQ[l]={p}.Given two formulas
       </list>
       <paragraph>
        l and {a mathematical formula}l′ in α, we say that they are {a mathematical formula}T-coupled (and we write {a mathematical formula}l∼Tl′) if:
       </paragraph>
       <list>
        <list-item label="(a)">
         l and {a mathematical formula}l′ individually match {a mathematical formula}T via the components c and {a mathematical formula}c′; and
        </list-item>
        <list-item label="(b)">
         if {a mathematical formula}(c,i)∼FC(c′,j), {a mathematical formula}Var[l,i]=Var[l′,j].
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       We now fix a template {a mathematical formula}T and an action schema α and study the properties of the relation {a mathematical formula}∼T on the literals of α that match {a mathematical formula}T, introduced above. First, we have the following simple result.
      </paragraph>
      <paragraph label="Proof">
       For a template{a mathematical formula}T=(C,FC)and an action schema α,{a mathematical formula}∼Tis an equivalence relation.Reflexivity and symmetry are obvious from the definition. Regarding transitivity, assume that {a mathematical formula}l1,l2,l3 are three formulas in α matching {a mathematical formula}T through the components {a mathematical formula}c1,c2,c3 respectively, such that {a mathematical formula}l1∼Tl2 and {a mathematical formula}l2∼Tl3. Suppose that {a mathematical formula}(c1,i)∈Fc1 and {a mathematical formula}(c3,j)∈Fc3 are such that {a mathematical formula}(c1,i)∼FC(c3,j). The fact that {a mathematical formula}FC is an admissible partition implies that there exists {a mathematical formula}(c2,h)∈Fc2 such that {a mathematical formula}(c1,i)∼FC(c2,h)∼FC(c3,j). The assumptions {a mathematical formula}l1∼Tl2 and {a mathematical formula}l2∼Tl3 yield {a mathematical formula}Var[l1,i]=Var[l2,h]=Var[l3,j]. This shows that {a mathematical formula}l1∼Tl3.  □
      </paragraph>
      <paragraph label="Definition 61">
       {a mathematical formula}T-classFor a template {a mathematical formula}T=(C,FC) and an action schema α, an equivalence class of literals with respect to {a mathematical formula}∼T is called a {a mathematical formula}T-class.
      </paragraph>
      <paragraph label="Remark 62">
       We now derive a more concrete description of the concept of matching. Suppose that l is a formula in the action schema α that matches the template {a mathematical formula}T via the component {a mathematical formula}c=〈r/k,p〉. The possible structure of l is shown below:{a mathematical formula}Suppose now that {a mathematical formula}l1 and {a mathematical formula}l2 are two formulas in the action schema α that match the template {a mathematical formula}T via {a mathematical formula}c1=〈r1/k1,p1〉 and {a mathematical formula}c2=〈r2/k2,p2〉, respectively. We can represent, for {a mathematical formula}i=1,2, {a mathematical formula}li=ri(v0i,…vki−1i) (or {a mathematical formula}li=(∀vpi:ri(v0i,…vki−1i)) if {a mathematical formula}pi&lt;ki). The {a mathematical formula}T coupling condition {a mathematical formula}l1∼Tl2 is equivalent to requiring that for any pair of fixed variables {a mathematical formula}(c1,j)∈Fc1 and {a mathematical formula}(c2,h)∈Fc2, the following holds:{a mathematical formula}
      </paragraph>
      <paragraph>
       We now consider a grounding function gr for α and an instance γ for {a mathematical formula}T. If l is a formula in α that matches {a mathematical formula}T via the component {a mathematical formula}c=〈r/k,p〉, depending on the structure of l, as illustrated in (18), we have that{a mathematical formula} Considering the definition of {a mathematical formula}γ(T) in (3) and the fact that the quantified case above can only appear when {a mathematical formula}p&lt;k, it follows that {a mathematical formula}gr(l) is either a subset of {a mathematical formula}γ(T) or it must have empty intersection with {a mathematical formula}γ(T). This motivates the following definition:
      </paragraph>
      <paragraph label="Definition 63">
       Coherencegr and γ are coherent over l if {a mathematical formula}gr(l)⊆γ(T).
      </paragraph>
      <paragraph>
       Referring to the representation (20), coherence can be equivalently expressed as{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 64">
       The following result is immediate from the conditions (21): Consider a template{a mathematical formula}T=(C,FC)and an action schema α. Let l be a formula in the action schema α that matches{a mathematical formula}T. Then, for every grounding function gr of α, it is possible to find an instance γ of{a mathematical formula}Tsuch that gr and γ are coherent over l and vice versa.
      </paragraph>
      <paragraph label="Lemma 65">
       The following result explains how coherence interacts with the equivalence relation {a mathematical formula}∼T. Consider a template{a mathematical formula}T=(C,FC)with an instance γ and an action schema α with a grounding gr. Assume that gr and γ are coherent over a formula{a mathematical formula}l1in α and let{a mathematical formula}l2be another formula in α that matches{a mathematical formula}T. Then, gr and γ are coherent over{a mathematical formula}l2if and only if{a mathematical formula}l2∼Tl1.
      </paragraph>
      <paragraph label="Proof">
       We assume that for {a mathematical formula}i=1,2, {a mathematical formula}li matches {a mathematical formula}T through components {a mathematical formula}ci=〈ri/ki,pi〉. We now represent each {a mathematical formula}li as in Remark 62:{a mathematical formula} The fact that gr and γ are coherent over {a mathematical formula}l1 yields{a mathematical formula} Suppose now that {a mathematical formula}l2∼Tl1 and consider any fixed variable {a mathematical formula}(c2,h) of {a mathematical formula}c2 for some {a mathematical formula}h∈{0,…,k2−1}∖{p2}. From the fact that {a mathematical formula}FC is an admissible partition, it follows that we can find a fixed variable {a mathematical formula}(c1,j) of {a mathematical formula}c1 such that {a mathematical formula}(c1,j)∼FC(c2,h). The {a mathematical formula}T coupling condition (19) implies that {a mathematical formula}vj1=vh2. This yields, using (22) and the fact that γ is an instance{a mathematical formula} We have thus proven that{a mathematical formula}On the other hand, assume now that gr and γ are coherent over {a mathematical formula}l2 and pick any fixed variables {a mathematical formula}(c1,j) and {a mathematical formula}(c2,h) of {a mathematical formula}c1 and {a mathematical formula}c2 respectively such that {a mathematical formula}(c1,j)∼FC(c2,h). Using the definition of an instance and equations (22) and (23), we obtain that {a mathematical formula}gr(vh2)=gr(vj1). The standing assumption that gr is injective yields {a mathematical formula}vj1=vh2. This shows that the {a mathematical formula}T coupling condition (19) expressed in Remark 62 holds true. Therefore, {a mathematical formula}l2∼Tl1.  □
      </paragraph>
      <paragraph label="Proposition 66">
       The following result immediately follows from the definition of coherence and Lemma 65. Suppose that M is a subset of formulas appearing in α. Then,{a mathematical formula}gr(M)∩γ(T)=gr(M∩L)where L is the{a mathematical formula}T-class of formulas of α on which gr and γ are coherent.
      </paragraph>
      <paragraph>
       Proposition 66 has an important practical consequence. Once gr and γ have been fixed, only the part of α made of formulas in the class L where gr and γ are coherent affect the part of state dynamics concerning the set {a mathematical formula}γ(T). Precisely, if {a mathematical formula}a=gr(α), it follows from the definition of {a mathematical formula}aγ (see Remark 15) that:{a mathematical formula} Considering that, by Proposition 16, a is strongly γ-safe if and only if {a mathematical formula}aγ is also strongly γ-safe, the property of strong safety of an action schema α does not depend on the formulas in α that do not match {a mathematical formula}T. Hence, in principle, such a property should be analysed by studying the restrictions of α to the different {a mathematical formula}T-classes L of matching formulas. This intuition leads to the following definition.
      </paragraph>
      <paragraph label="Definition 67">
       Pure action schemasConsidering a template {a mathematical formula}T, an action schema α and a {a mathematical formula}T-class L of formulas in α, we define {a mathematical formula}αL to be the action schema where we only consider formulas belonging to L. More precisely, {a mathematical formula}αL is the action schema such that{a mathematical formula} We call {a mathematical formula}αL a pure action schema.
      </paragraph>
      <paragraph label="Example 14">
       Floortile domainConsider the template {a mathematical formula}Tft in Example 2 and the action schema {a mathematical formula}α=paintUpst: {an inline-figure}, {an inline-figure}.Note that both formulas robotAt(r,x) and clear(y) in α match {a mathematical formula}Tft and form two different {a mathematical formula}T-classes because they do not satisfy condition (ii) in Definition 59: {an inline-figure} and {an inline-figure}.Consider the instance {a mathematical formula}γ1 that associates tile1 to each fixed variable in the components of {a mathematical formula}Tft and grounding function {an inline-figure}, {an inline-figure} and {an inline-figure}. In this case, gr and {a mathematical formula}γ1 are coherent on the {a mathematical formula}T-class {a mathematical formula}L1.We have two pure action schemas corresponding to α: {a mathematical formula}αL1 and {a mathematical formula}αL2. {a mathematical formula}αL1 has the following specification: {a mathematical formula}PreαL1+={robotAt(r,x)} and {a mathematical formula}αL2: {a mathematical formula}PreαL2+={clear(y)},EffαL2−={clear(y)}.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Pure action schema classification
      </section-title>
      <paragraph>
       We now carry on a detailed analysis of pure action schemas, showing in particular how the check for strong safety for an action {a mathematical formula}a=gr(α) can be efficiently performed at the lifted level working with the different pure action schemas {a mathematical formula}αL.
      </paragraph>
      <paragraph>
       We fix an action schema α and a {a mathematical formula}T-class L of its formulas. First, we introduce a concept of weight at the level of formulas in L that allows us to distinguish between simple and universally quantified formulas. Precisely, given {a mathematical formula}l∈L, we define {a mathematical formula}wl=1 if l is simple, and {a mathematical formula}wl=ω if l is universally quantified, where {a mathematical formula}ω=|O|. For a subset {a mathematical formula}A⊆L, we define {a mathematical formula}w(A)=∑l∈Awl. Note that {a mathematical formula}w(⋅) is simply cardinality when all formulas in L are simple. If we consider a grounding function gr for α, then for every subset {a mathematical formula}A⊆L, the following holds:{a mathematical formula} Similarly, if c is a component of {a mathematical formula}T, we define {a mathematical formula}wc equal to 1 or to ω if c, respectively, does not have or does have a counted variable.
      </paragraph>
      <paragraph>
       We also need one additional concept:
      </paragraph>
      <paragraph label="Definition 68">
       CoverageConsider a component {a mathematical formula}c∈T. We let {a mathematical formula}Lc be the subset of formulas in L that match {a mathematical formula}T through the component c. A subset of formulas {a mathematical formula}M⊆L is said to cover the component c, if {a mathematical formula}w(M∩Lc)=wc. M is said to cover{a mathematical formula}T, if M covers every component {a mathematical formula}c∈T.
      </paragraph>
      <paragraph label="Remark 69">
       If we consider a component {a mathematical formula}c∈T, all ground atoms generated by c are in {a mathematical formula}gr(M) if and only if M covers c. In particular, {a mathematical formula}γ(T)=gr(M) if and only if M covers {a mathematical formula}T.
      </paragraph>
      <paragraph>
       We now give a classification of the pure action schemas {a mathematical formula}αL, formally analogous to that introduced for action sets in Definition 17, Definition 19: we simply replace preconditions and effects of {a mathematical formula}aγ with those of {a mathematical formula}αL and the concept of cardinality with that of weight.
      </paragraph>
      <paragraph label="Definition 70">
       Classification of pure action schemasThe pure action schema {a mathematical formula}αL is:
      </paragraph>
      <list>
       <list-item label="•">
        unreachable for {a mathematical formula}T if {a mathematical formula}w(PreαL+)≥2;
       </list-item>
       <list-item label="•">
        heavy for {a mathematical formula}T if {a mathematical formula}w(PreαL+)≤1 and {a mathematical formula}w(EffαL+)≥2;
       </list-item>
       <list-item label="•">
        irrelevant for {a mathematical formula}T if {a mathematical formula}w(PreαL+)≤1 and {a mathematical formula}w(EffαL+)=0;
       </list-item>
       <list-item label="•">
        relevant for {a mathematical formula}T if {a mathematical formula}w(PreαL+)≤1 and {a mathematical formula}w(EffαL+)=1.
       </list-item>
      </list>
      <paragraph label="Definition 71">
       Classification of relevant action schemasThe pure relevant action schema {a mathematical formula}αL is weighty when it has a single relevant precondition: {a mathematical formula}w(PreαL+)=1. A is weightless if {a mathematical formula}w(PreαL+)=0.A weighty action schema {a mathematical formula}αL is either:
       <list>
        balanced for {a mathematical formula}T if {a mathematical formula}PreαL+⊆EffαL+∪EffαL−;unbalanced for {a mathematical formula}T if {a mathematical formula}PreαL+∩(EffαL+∪EffαL−)=∅;A weightless action schema
       </list>
       <paragraph>
        {a mathematical formula}αL is either:
       </paragraph>
       <list>
        <list-item label="•">
         bounded for {a mathematical formula}T if L covers {a mathematical formula}T;
        </list-item>
        <list-item label="•">
         unbounded for {a mathematical formula}T if L does not cover {a mathematical formula}T.
        </list-item>
       </list>
      </paragraph>
      <paragraph>
       The following result clarifies the relation with the corresponding grounded actions.
      </paragraph>
      <paragraph label="Proof">
       Consider an action schema α, a{a mathematical formula}T-class L of its formulas, a grounding function gr and an instance γ coherent over L. Let{a mathematical formula}a=gr(α). Then,{a mathematical formula}αLsatisfies a property expressed inDefinition 70, Definition 71if and only if a satisfies the corresponding γ-property as defined inDefinition 17, Definition 19.An immediate consequence of the fact that {a mathematical formula}aγ=gr(αL), of Equation (24), and of Remark 69.  □
      </paragraph>
      <paragraph>
       We are now ready to give the following final result concerning strong safety of general action schemas. It shows how strong safety can be seen as a property of an action schema and can be interpreted by analysing its pure parts.
      </paragraph>
      <paragraph label="Proof">
       Strong safety is a liftable property. Moreover, an action schema α is strongly safe if and only if, for every{a mathematical formula}T-class of formulas L of α,{a mathematical formula}αLis unreachable, irrelevant, balanced or bounded.Suppose that {a mathematical formula}a=gr(α) for some gr and let γ be an instance. Then, {a mathematical formula}aγ=gr(αL) where L is the {a mathematical formula}T-class on which gr and γ are coherent. The result is now a straightforward consequence of Proposition 72 and Corollary 21.  □
      </paragraph>
      <paragraph label="Example 15">
       Floortile domainConsider the template {a mathematical formula}Tft and the action schema {a mathematical formula}α=paintUpst in Example 14. The two pure action schemas {a mathematical formula}αL1 and {a mathematical formula}αL2 are both irrelevant and hence strongly safe. Hence, α is strongly safe.Now consider the action schema {a mathematical formula}α′=paintUpend with specification: {an inline-figure}. This is a pure action schema. It is unbounded and thus not strongly safe.
      </paragraph>
      <paragraph label="Corollary 74">
       An immediate consequence of Corollary 23 is: Given a template{a mathematical formula}T,{a mathematical formula}Tis invariant if for each{a mathematical formula}α∈A, α is strongly safe.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Durative action schemas
     </section-title>
     <paragraph>
      Our goal now is to work out proper lifted versions of the properties of durative actions presented in Section 5, in particular those involved in the statement of our main results, Theorem 51, Theorem 53. Some of these properties concern just one durative action (e.g. safety), while others involve more actions (e.g. non-interfering, irrelevant-unreachable). We start analysing the first type of properties, presenting, in particular, an explicit characterisation of safety for durative actions at the lifted level.
     </paragraph>
     <paragraph>
      We use the following notation. Take a durative action schema {a mathematical formula}Dα=(αst,αinv,αend) and a grounding function gr for Dα. We let {a mathematical formula}Da=gr(Dα), where {a mathematical formula}Da=(ast,ainv,aend) with {a mathematical formula}ast=gr(αst), {a mathematical formula}ainv=gr(αinv), and {a mathematical formula}aend=gr(αend).
     </paragraph>
     <paragraph>
      Our first goal is to lift the assumptions (8) and (9) on durative actions. First define, for a generic action schema α, the subsets of postconditions:{a mathematical formula} We will make the standing assumption that every durative action schema {a mathematical formula}Dα=(αst,αinv,αend) satisfies the relations{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Since, we recall, grounding functions must be injective, (25) and (26) are equivalent to requiring that any grounding function {a mathematical formula}Da=gr(Dα) satisfies conditions (8) and (9).
     </paragraph>
     <paragraph>
      Also, we define the auxiliary durative action schema {a mathematical formula}Dα⁎=(α⁎st,α⁎end) where {a mathematical formula}α⁎st and {a mathematical formula}α⁎end are the action schema such that:{a mathematical formula}{a mathematical formula}Da⁎=gr(Dα⁎) is the corresponding auxiliary action previously defined in Section 5.2.
     </paragraph>
     <section label="8.1">
      <section-title>
       Safety of durative action schemas
      </section-title>
      <paragraph>
       We now fix a template {a mathematical formula}T and start to analyse safety. We consider a durative action schema Dα, its auxiliary action schema {a mathematical formula}Dα⁎ and its groundings {a mathematical formula}Da=gr(Dα) and {a mathematical formula}Da⁎=gr(Dα⁎). Strong safety for durative actions reduces to strong safety of its components and it is thus a liftable property. As a consequence, we can talk about the strong safety of Dα or {a mathematical formula}Dα⁎: this is equivalent to the strong safety of all its groundings, {a mathematical formula}Da=gr(Dα) or, respectively, {a mathematical formula}Da⁎=gr(Dα⁎). Checking such a property at the lifted level can be done by applying Corollary 73 to the start and end fragments.
      </paragraph>
      <paragraph>
       We now want to characterise simple safety of the auxiliary durative action {a mathematical formula}Da⁎=gr(Dα⁎) at the lifted level. First we consider executability.
      </paragraph>
      <paragraph label="Proof">
       Executability of auxiliary durative actions is a lifted property. Precisely,{a mathematical formula}Dα⁎is executable if and only if{a mathematical formula}An immediate consequence of Proposition 30.  □
      </paragraph>
      <paragraph>
       Assume now that {a mathematical formula}Dα⁎ is executable. Fix a grounding gr and let {a mathematical formula}Da⁎=gr(Dα⁎). Consider an instance γ and let L be the {a mathematical formula}T-class of formulas in Dα on which gr and γ are coherent. Let {a mathematical formula}DαL=(αLst,αLinv,αLend) and {a mathematical formula}Dα⁎L=(α⁎Lst,α⁎Lend). Note that {a mathematical formula}Da⁎γ=gr(Dα⁎L). Therefore, since simple γ-safety of {a mathematical formula}Da⁎ only depends on {a mathematical formula}Da⁎γ (since executability has already been assumed), we expect that such a property can be formulated in terms of the pure auxiliary durative action schema {a mathematical formula}Dα⁎L. To this aim, we now give, for such durative action schemas, the same classification introduced for durative actions in Definition 48. First, we need a further concept:
      </paragraph>
      <paragraph label="Definition 76">
       Reachable action schemas{a mathematical formula}Dα⁎L is said to be reachable if it is executable and{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       If gr and γ are coherent over L and{a mathematical formula}Da⁎=gr(Dα⁎), we have that{a mathematical formula}Da⁎γis γ-reachable if and only if{a mathematical formula}Dα⁎Lis reachable.An immediate consequence of Proposition 31, Proposition 66 and of equation (24).  □
      </paragraph>
      <paragraph label="Definition 78">
       Safe durative action schemasWhen {a mathematical formula}Dα⁎L is such that
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}Dα⁎L is reachable;
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}α⁎Lst is strongly safe;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}α⁎Lend is unbounded;
       </list-item>
       <list-item label="(iv)">
        {a mathematical formula}Dα⁎L satisfies any of the conditions below:
       </list-item>
      </list>
      <paragraph label="Corollary 79">
       Safety for durative auxiliary actions is a liftable property.{a mathematical formula}Da⁎=gr(Dα⁎)is safe if and only if:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Dα⁎is executable;
       </list-item>
       <list-item label="•">
        For every{a mathematical formula}T-class L of formulas in Dα, one of the following conditions hold:
       </list-item>
      </list>
      <paragraph label="Proof">
       An immediate consequence of previous definitions and Proposition 46.  □
      </paragraph>
      <paragraph label="Example 16">
       Floortile domainConsider our usual template:{a mathematical formula} and the action schema:{a mathematical formula}where the single instantaneous action schemas have the specifications shown in Table 4.In this action schema, we have three formulas that match {a mathematical formula}Tft: robotAt(r,x), clear(y) and painted(y,c). They form two {a mathematical formula}T-classes: {an inline-figure} and {an inline-figure}. Note that in this case {a mathematical formula}paintUpList is equal to {a mathematical formula}paintUp⁎List for {a mathematical formula}i=1,2 and the same holds for {a mathematical formula}paintUpLiend.The pure action schemas {a mathematical formula}paintUpL1st, {a mathematical formula}paintUpL2st and {a mathematical formula}paintUpL1end are strongly safe because they are irrelevant. The pure schema {a mathematical formula}paintUpL2end is unbounded.The pure durative action schema {a mathematical formula}paintUpL1 is strongly safe because {a mathematical formula}paintUpL1st and {a mathematical formula}paintUpL1end are strongly safe since they are irrelevant.The pure schema {a mathematical formula}paintUpL2 is weakly safe of type (a) since:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}paintUpL2 is reachable because {a mathematical formula}paintUpL2st is reachable and {a mathematical formula}paintUpL2end does not contain preconditions;
       </list-item>
       <list-item label="•">
        {a mathematical formula}paintUpL2st is strongly safe since it is irrelevant;
       </list-item>
       <list-item label="•">
        {a mathematical formula}paintUpL2end is unbounded;
       </list-item>
       <list-item label="•">
        {a mathematical formula}w(PrepaintUpL2st+)=1 because the preconditions at start consist of clear(y);
       </list-item>
       <list-item label="•">
        {a mathematical formula}PrepaintUpL2st+⊆EffpaintUpL2st− because the delete effects at start also contain clear(y).
       </list-item>
      </list>
     </section>
     <section label="8.2">
      <section-title>
       Lifting properties of multiple actions
      </section-title>
      <paragraph>
       In this section, we study how properties that involve more than one action (e.g. mutex) can be lifted. This requires working simultaneously with different groundings and, for this reason, additional concepts are needed.
      </paragraph>
      <paragraph>
       Consider two action schemas {a mathematical formula}α1 and {a mathematical formula}α2 (instantaneous or durative) with sets of variables {a mathematical formula}Vα1 and {a mathematical formula}Vα2, respectively. Whenever we consider two groundings {a mathematical formula}gr1 and {a mathematical formula}gr2 for {a mathematical formula}α1 and {a mathematical formula}α2, respectively, the pairwise properties of the two actions {a mathematical formula}ai=gri(αi) (e.g. properties regarding the sequence {a mathematical formula}(a1,a2) or the set {a mathematical formula}{a1,a2}) are non liftable, as in general they may depend on the specific groundings chosen. A key aspect is the possible presence, in the two action schemas, of pairs of variables {a mathematical formula}vi∈Vif such that {a mathematical formula}gr1(v1)=gr2(v2): this may cause the same ground atom to appear in the two actions {a mathematical formula}a1 and {a mathematical formula}a2, which in principle can affect the validity of certain properties, such as non-interference. To cope with this complexity at the lifted level, we introduce a concept of reduced union of the two sets {a mathematical formula}Vα1 and {a mathematical formula}Vα2 to be used as a common set of variables for the two schemas.
      </paragraph>
      <paragraph>
       We define a matching between {a mathematical formula}α1 and {a mathematical formula}α2 as any subset {a mathematical formula}M⊆Vα1×Vα2 such that:
      </paragraph>
      <list>
       <list-item label="•">
        If {a mathematical formula}(v1,v2),(w1,v2)∈M, then {a mathematical formula}v1=w1;
       </list-item>
       <list-item label="•">
        If {a mathematical formula}(v1,v2),(v1,w2)∈M, then {a mathematical formula}v2=w2.
       </list-item>
      </list>
      <paragraph>
       We now define the set {a mathematical formula}Vα1⊔MVα2 obtained by {a mathematical formula}Vα1∪Vα2 by reducing each pair of variables {a mathematical formula}v1∈Vα1 and {a mathematical formula}v2∈Vα2 such that {a mathematical formula}(v1,v2)∈M to a new variable, denoted as {a mathematical formula}v1v2. Note that in the case when {a mathematical formula}M=∅, no reduction takes place and {a mathematical formula}Vα1⊔∅Vα2=Vα1∪Vα2.
      </paragraph>
      <paragraph>
       For a matching {a mathematical formula}M, we have natural maps {a mathematical formula}πMi:Vif→Vα1⊔MVα2 associating to each variable {a mathematical formula}vi, {a mathematical formula}vi itself or the new reduced variable {a mathematical formula}vivj in case {a mathematical formula}(vi,vj)∈M. The two schemas {a mathematical formula}α1 and {a mathematical formula}α2 can thus be rewritten in this new alphabet by formally substituting each variable {a mathematical formula}vi∈Vif in their formulas with {a mathematical formula}πMi(vi). If {a mathematical formula}li is a formula of {a mathematical formula}αi, we denote by {a mathematical formula}πMi(li) the formula obtained with this substitution. Similarly, if {a mathematical formula}Ai is a set of formulas of {a mathematical formula}αi, we put {a mathematical formula}πMi(Ai)={πMi(li)|li∈Ai}.
      </paragraph>
      <paragraph>
       For the formulas of the two schemas, expressed in the common variable set {a mathematical formula}Vα1⊔MVα2, we can jointly apply set theoretic operators. If {a mathematical formula}li is a formula of {a mathematical formula}αi and {a mathematical formula}Ai is a set of formulas of {a mathematical formula}αi, for {a mathematical formula}i=1,2, we will use the notation {a mathematical formula}l1=Ml2 for {a mathematical formula}πM1(l1)=πM2(l2) and {a mathematical formula}l1∈MA2 for {a mathematical formula}πM1(l1)∈πM2(A2). Similarly, we put {a mathematical formula}A1⁎MA2=πM1(A1)⁎πM2(A2) where {a mathematical formula}⁎∈{∪,∩,∖}.
      </paragraph>
      <paragraph>
       We now investigate the relation between matchings and specific groundings of the two schemas.
      </paragraph>
      <paragraph label="Definition 80">
       Coherent grounding functionsConsider two action schemas {a mathematical formula}α1 and {a mathematical formula}α2 and a matching {a mathematical formula}M between them. Two grounding functions {a mathematical formula}gr1 and {a mathematical formula}gr2 for {a mathematical formula}α1 and {a mathematical formula}α2, respectively, are said to be {a mathematical formula}M-adapted if given {a mathematical formula}vi∈Vif for {a mathematical formula}i=1,2, it holds that {a mathematical formula}gr1(v1)=gr2(v2) if and only if {a mathematical formula}(v1,v2)∈M.
      </paragraph>
      <paragraph label="Remark 81">
       Note that, for two groundings {a mathematical formula}gr1 and {a mathematical formula}gr2, if we consider {a mathematical formula}M={(v1,v2)|gr1(v1)=gr2(v2)} we have that {a mathematical formula}M is a matching (recall that maps {a mathematical formula}gri are injective) and {a mathematical formula}gr1 and {a mathematical formula}gr2 are {a mathematical formula}M-adapted.
      </paragraph>
      <paragraph>
       Coherent groundings can be factored through the reduced set {a mathematical formula}Vα1⊔MVα2:
      </paragraph>
      <paragraph label="Proposition 82">
       Consider two action schemas{a mathematical formula}α1and{a mathematical formula}α2, a matching{a mathematical formula}Mbetween them, and grounding functions{a mathematical formula}grifor{a mathematical formula}αi,{a mathematical formula}i=1,2. The following conditions are equivalent:
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}gr1and{a mathematical formula}gr2are{a mathematical formula}M-adapted;
       </list-item>
       <list-item>
        there exists an injective function{a mathematical formula}gr:Vα1⊔MVα2→Osuch that,{a mathematical formula}gri=gr∘πMifor{a mathematical formula}i=1,2.
       </list-item>
      </list>
      <paragraph>
       Suppose that {a mathematical formula}gr1 and {a mathematical formula}gr2 are two {a mathematical formula}M-adapted groundings of {a mathematical formula}α1 and {a mathematical formula}α2 and let gr be the function as in (ii) of the previous proposition. If {a mathematical formula}Ai is a set of formulas of {a mathematical formula}αi, for {a mathematical formula}i=1,2, for any set theoretic operation {a mathematical formula}⁎∈{∪,∩,∖} it holds that:{a mathematical formula} This follows from Proposition 82 and the fact that gr is injective. An iterative use of (28) shows that any set theoretic expression on the two grounded actions {a mathematical formula}gri(αi) is in bijection (through gr) with a corresponding expression on the two action schemas {a mathematical formula}αi expressed in the common reduced set {a mathematical formula}Vα1⊔MVα2. As a consequence, any property of actions (with the standing assumption of {a mathematical formula}M-adapted groundings) that can be expressed by set theoretic operations on their formulas can be reformulated by rewriting these formulas in the new alphabet {a mathematical formula}Vα1⊔MVα2. This is the key observation in order to lift properties of pairs of actions. To be more concrete, we consider the example of non-interfering actions, which will be needed in what follows.
      </paragraph>
      <paragraph label="Definition 83">
       Mutex simple action schemasWe say that two action schemas {a mathematical formula}α1 and {a mathematical formula}α2 are {a mathematical formula}Mnon-interfering if for {a mathematical formula}i≠j{a mathematical formula} If {a mathematical formula}α1 and {a mathematical formula}α2 are not {a mathematical formula}M non-interfering, they are called {a mathematical formula}M-mutex.
      </paragraph>
      <paragraph label="Definition 84">
       Executable action schemasWe say that a set of two {a mathematical formula}Mnon-interfering action schemas {a mathematical formula}{α1,α2} is {a mathematical formula}M-executable if for {a mathematical formula}i≠j{a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 85">
       Consider two action schemas{a mathematical formula}α1and{a mathematical formula}α2, a matching{a mathematical formula}Mbetween them and grounding functions{a mathematical formula}gr1and{a mathematical formula}gr2for, respectively,{a mathematical formula}α1and{a mathematical formula}α2, that are{a mathematical formula}M-adapted. Put{a mathematical formula}ai=gri(αi)for{a mathematical formula}i=1,2. Then,
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}α1and{a mathematical formula}α2are{a mathematical formula}M-mutex if and only if{a mathematical formula}a1and{a mathematical formula}a2are mutex;
       </list-item>
       <list-item>
        {a mathematical formula}{α1,α2}is{a mathematical formula}M-executable if and only if{a mathematical formula}{a1,a2}is executable.
       </list-item>
      </list>
      <paragraph label="Proof">
       An immediate consequence of Definition 88, Definition 84 and of equation (28).  □
      </paragraph>
      <paragraph label="Remark 86">
       Note that certain properties that depend on the matching {a mathematical formula}M have a monotonic behaviour, i.e. if they are true for a matching {a mathematical formula}M, they remain true for a larger matching {a mathematical formula}M′⊇M. This is the case, for instance, of properties that can be expressed in terms of identities between formulas of type {a mathematical formula}l1=Ml2, such as the {a mathematical formula}M-mutex property.
      </paragraph>
      <paragraph>
       To cope with properties related to a template and its instantiations, it is useful to introduce a family of matchings induced by the presence of formulas in the two schemas matching in a template. Precisely, consider now a template {a mathematical formula}T=(C,FC) and two action schemas {a mathematical formula}α1 and {a mathematical formula}α2. Consider {a mathematical formula}T-classes {a mathematical formula}Li of formulas of {a mathematical formula}αi for {a mathematical formula}i=1,2. There is a natural way to associate a matching to {a mathematical formula}L1 and {a mathematical formula}L2 as follows. Pick formulas {a mathematical formula}li∈Li for {a mathematical formula}i=1,2 and consider components {a mathematical formula}ci∈C such that {a mathematical formula}li matches {a mathematical formula}T through {a mathematical formula}ci. Let:{a mathematical formula} It immediately follows from the definition of {a mathematical formula}T-coupled pairs of formulas (Definition 59) that {a mathematical formula}ML1,L2 does not depend on the particular formulas {a mathematical formula}li chosen, but only on the {a mathematical formula}T-classes {a mathematical formula}Li.
      </paragraph>
      <paragraph>
       Essentially, in {a mathematical formula}ML1,L2, we are rewriting variables in the formulas of {a mathematical formula}L1 and {a mathematical formula}L2 that correspond to {a mathematical formula}FC-equivalent variables in the template {a mathematical formula}T. The next proposition shows the role played by such a matching.
      </paragraph>
      <paragraph label="Proposition 87">
       Consider two groundings{a mathematical formula}gr1and{a mathematical formula}gr2for{a mathematical formula}α1and{a mathematical formula}α2, respectively, which are{a mathematical formula}M-adapted. Then the following facts hold:
      </paragraph>
      <list>
       <list-item>
        for an instance γ for{a mathematical formula}T, if{a mathematical formula}Liare the{a mathematical formula}T-classes of formulas of{a mathematical formula}αion which{a mathematical formula}griand γ are coherent. Then,{a mathematical formula}ML1,L2⊆M;
       </list-item>
       <list-item>
        for{a mathematical formula}T-classes of formulas{a mathematical formula}Liof{a mathematical formula}αi, if{a mathematical formula}ML1,L2⊆M, there exists just one instance γ of{a mathematical formula}Tsuch that{a mathematical formula}griand γ are coherent on{a mathematical formula}Li.
       </list-item>
      </list>
      <paragraph label="Proof">
       Fix, for {a mathematical formula}i=1,2, {a mathematical formula}li∈Li. Assume that {a mathematical formula}li matches {a mathematical formula}T through components {a mathematical formula}ci=〈ri/ki,pi〉 and represent {a mathematical formula}li as in Remark 62:{a mathematical formula}(i): Let {a mathematical formula}j≠p1 and {a mathematical formula}h≠p2 be such that {a mathematical formula}(c1,j)∼FC(c2,h). The fact that {a mathematical formula}gri and γ are coherent yields:{a mathematical formula} This implies, by Definition 80, that {a mathematical formula}(vj1,vh2)∈M. By definition (29), we thus have {a mathematical formula}ML1,L2⊆M.(ii): Choose γ in such a way that {a mathematical formula}gr1 and γ are coherent: {a mathematical formula}γ(c1,j)=gr1(vj1) for every {a mathematical formula}j≠p1. Now fix {a mathematical formula}h≠p2 and choose {a mathematical formula}j≠p1 such that {a mathematical formula}(c1,j)∼FC(c2,h). Then, since {a mathematical formula}ML1,L2⊆M,{a mathematical formula} This implies that {a mathematical formula}gr2 is also coherent with γ.  □
      </paragraph>
      <paragraph>
       We are now ready to lift the properties used in Section 6. We start with unreachability for fragments of durative action schemas.
      </paragraph>
      <paragraph label="Definition 88">
       Unreachable durative action schemasTake two durative action schemas {a mathematical formula}Dα1, {a mathematical formula}Dα2 and the corresponding {a mathematical formula}T-classes of formulas {a mathematical formula}L1 and {a mathematical formula}L2.
      </paragraph>
      <list>
       <list-item label="1.">
        We say that {a mathematical formula}({α1inv,α2inv},{α1end,α2end}) is {a mathematical formula}(L1,L2)-unreachable if at least one of the following conditions is satisfied:
       </list-item>
       <list-item label="2.">
        We say that {a mathematical formula}({α1st,α2st},{α1inv,α2inv}) is {a mathematical formula}(L1,L2)-unreachable if at least one of the following conditions is satisfied:
       </list-item>
      </list>
      <paragraph>
       Note that the check of property (iii) of the above definition in principle involves all possible matchings containing {a mathematical formula}ML1,L2. In Section 9.2, we propose an efficient check of this condition that exhibits a computational complexity of polynomial order in the number of variables and formulas of the domain.
      </paragraph>
      <paragraph label="Proposition 89">
       Suppose that{a mathematical formula}Dα1,{a mathematical formula}Dα2are two durative action schemas and{a mathematical formula}gr1,{a mathematical formula}gr2two corresponding grounding functions. Let{a mathematical formula}Dai=gr(Dαi)and consider an instance γ. Let{a mathematical formula}Libe the{a mathematical formula}T-class of formulas of{a mathematical formula}Dαion which{a mathematical formula}griand γ are coherent.
      </paragraph>
      <list>
       <list-item label="•">
        If{a mathematical formula}({α1inv,α2inv},{α1end,α2end})is{a mathematical formula}(L1,L2)-unreachable, then{a mathematical formula}({a1st,a2st},{a1inv,a2inv})is γ-unreachable.
       </list-item>
       <list-item label="•">
        If{a mathematical formula}({α1st,α2st},{α1inv,α2inv})is{a mathematical formula}(L1,L2)-unreachable, then{a mathematical formula}({a1st,a2st},{a1inv,a2inv})is γ-unreachable.
       </list-item>
      </list>
      <paragraph label="Proof">
       We only prove the first point, the second being analogous. Let {a mathematical formula}M be the matching such that {a mathematical formula}gr1 and {a mathematical formula}gr2 are {a mathematical formula}M-adapted. It follows from Proposition 87 that {a mathematical formula}M⊇ML1,L2. Note that the conditions (i) and (ii) expressed in Definition 88, if true for {a mathematical formula}ML1,L2, are also true for the matching {a mathematical formula}M, because of Remark 86. Consequently we know that at least one of the conditions (i), (ii), or (iii) expressed in Definition 88 holds true for such {a mathematical formula}M. It then follows from (28) that at least one of the following conditions holds:
      </paragraph>
      <list>
       <list-item label="(ib)">
        {a mathematical formula}Prea1inv+∩Prea2end−≠∅;
       </list-item>
       <list-item label="(iib)">
        {a mathematical formula}Prea1inv−∩Prea2end+≠∅;
       </list-item>
       <list-item label="(iiib)">
        {a mathematical formula}|Preaγ1inv+∪Preaγ1end+∪Preaγ2inv+∪Preaγ2end+|≥2.
       </list-item>
      </list>
      <paragraph>
       We now give the lifted version of relevant right isolated.
      </paragraph>
      <paragraph label="Definition 90">
       Relevant right isolated schemasFor a template {a mathematical formula}T, the set of durative action schemas {a mathematical formula}Ad is said to be relevant right isolated if, for every {a mathematical formula}Dα1,Dα2∈Ad, corresponding {a mathematical formula}T-classes {a mathematical formula}L1,L2 of formulas of each of them such that {a mathematical formula}DαLii are both not strongly safe, one of the following conditions is satisfied (we use the notation {a mathematical formula}M=ML1,L2):
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}|EffαL11end+∪MEffαL22end+|≤1;
       </list-item>
       <list-item label="(ii)">
        at least one of the two pairs {a mathematical formula}{α1end,α2end}, {a mathematical formula}{α1inv,α2inv} is either {a mathematical formula}M-mutex or non {a mathematical formula}M-executable;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}({α1inv,α2inv},{α1end,α2end}) is {a mathematical formula}(L1,L2)-unreachable.
       </list-item>
      </list>
      <paragraph label="Proof">
       For a template{a mathematical formula}T, suppose that the set of durative action schemas{a mathematical formula}Adis relevant right isolated. Then{a mathematical formula}GAdis also relevant right isolated.Fix any instance γ and consider {a mathematical formula}Da1,Da2∈GAd(wk,γ). Let {a mathematical formula}Dαi and {a mathematical formula}gri, for {a mathematical formula}i=1,2, be durative schemas and groundings such that {a mathematical formula}Dai=gri(Dαi). Let {a mathematical formula}Li be the {a mathematical formula}T-class of formulas of each schema {a mathematical formula}Dαi such that {a mathematical formula}gri and γ are coherent over {a mathematical formula}Li for {a mathematical formula}i=1,2. Therefore, {a mathematical formula}Dα1 and {a mathematical formula}Dα2 must satisfy one of the conditions (i) to (iii) in the Definition 90. Let {a mathematical formula}M be the matching to which {a mathematical formula}gr1 and {a mathematical formula}gr2 are adapted (in the sense of Remark 81). We know from Proposition 87 that {a mathematical formula}M⊇ML1,L2. Note now that if condition (i) holds true, it also holds true for such larger {a mathematical formula}M (Remark 86) and this yields condition (i) of Definition 50. Similarly, condition (ii) yields the same condition with this new {a mathematical formula}M (Remark 86) from which condition (ii) in Definition 90 follows using Proposition 85. Finally, if condition (iii) holds true, then condition (iii) in Definition 90 follows by using Proposition 89. Therefore, by Definition 90 we have that the two durative action schemas {a mathematical formula}Dα1 and {a mathematical formula}Dα2 must satisfy one of the conditions (i) to (iii) in the definition. From the fact that {a mathematical formula}gr1 and {a mathematical formula}gr2 are {a mathematical formula}M-adapted, it follows that conditions (i) of Definition 90 yields condition (i) of Definition 50. Condition (ii) and (iii) in Definition 50 finally follow conditions (ii) and (iii) in Definition 90 using Proposition 85, Proposition 89.  □
      </paragraph>
      <paragraph>
       We are now ready to propose the lifted version of our first invariant result Theorem 51.
      </paragraph>
      <paragraph label="Corollary 92">
       Consider a template{a mathematical formula}Tand suppose that the set of instantaneous action schemas{a mathematical formula}Aiand that of durative action schemas{a mathematical formula}Adsatisfy the following properties:
      </paragraph>
      <list>
       <list-item>
        every{a mathematical formula}α∈Aiis strongly safe;
       </list-item>
       <list-item>
        for every{a mathematical formula}Dα∈Adand every{a mathematical formula}T-class L such that{a mathematical formula}DαLis not strongly safe,{a mathematical formula}Dα⁎Lis reachable and strongly safe;
       </list-item>
       <list-item>
        {a mathematical formula}Adis relevant right isolated.
       </list-item>
      </list>
      <paragraph>
       In order to lift the remaining results on the invariance of a template, a key point is to lift the fundamental Definition 56 of pairwise relevant non overlapping. To do this it will be convenient to introduce some compact notation concerning sets of action schemas and relative classes. We define{a mathematical formula}
      </paragraph>
      <paragraph>
       {a mathematical formula}(α,L) and {a mathematical formula}(Dα,L) are called, respectively, schema-class and durative schema-class pairs.
      </paragraph>
      <paragraph label="Definition 93">
       We now propose a lifted version of the property of unreachability expressed in Definition 54. MC-unreachable schemasConsider a template {a mathematical formula}T and a subset {a mathematical formula}MC⊆AC(T) such that for every {a mathematical formula}(α,L)∈MC, {a mathematical formula}αL is irrelevant. Consider a pair of action schemas {a mathematical formula}α1,α2∈A and relative classes {a mathematical formula}L1 and {a mathematical formula}L2, respectively. {a mathematical formula}(α1,α2) is {a mathematical formula}(MC;L1,L2)-unreachable if any of the following conditions is satisfied:
      </paragraph>
      <list>
       <list-item label="(i)">
        there exist {a mathematical formula}l1∈Γα1+, {a mathematical formula}l2∈Preα2− with {a mathematical formula}l1=ML1,L2l2 such that, for every schema-class {a mathematical formula}(α,L)∈MC and for every matching {a mathematical formula}M between {a mathematical formula}α1 and α for which {a mathematical formula}M⊇ML1,L, we have that {a mathematical formula}l1∉MEffα−;
       </list-item>
       <list-item label="(ii)">
        there exist {a mathematical formula}l1∈Γα1−, {a mathematical formula}l2∈Preα2+ with {a mathematical formula}l1=ML1,L2l2 such that, for every schema-class {a mathematical formula}(α,L)∈MC and for every matching {a mathematical formula}M between {a mathematical formula}α1 and α for which {a mathematical formula}M⊇ML1,L, we have that {a mathematical formula}l1∉MEffα+;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}w(PreαL11+∪M(PreαL22+∖MEffαL11+))≥2 for every matching {a mathematical formula}M⊇ML1,L2.
       </list-item>
      </list>
      <paragraph>
       Note that the check of all these properties in principle involve all possible matchings containing {a mathematical formula}ML1,L2. In Section 9.2, we propose an efficient check of this condition that exhibits a computational complexity of polynomial order in the number of variables and formulas of the domain.
      </paragraph>
      <paragraph>
       The following result shows how the notion of unreachability in Definition 93 is the lifted version of the one expressed in Definition 54.
      </paragraph>
      <paragraph label="Proof">
       Consider a template{a mathematical formula}Tand a subset{a mathematical formula}MC⊆AC(T)such that for every{a mathematical formula}(α,L)∈MC,{a mathematical formula}αLis irrelevant. Consider a pair of action schemas{a mathematical formula}α1,α2∈Aand relative groundings{a mathematical formula}gr1and{a mathematical formula}gr2. Let{a mathematical formula}ai=gr(αi)and consider an instance γ. Let{a mathematical formula}Libe the{a mathematical formula}T-class of formulas of{a mathematical formula}αion which{a mathematical formula}griand γ are coherent. If{a mathematical formula}(α1,α2)is{a mathematical formula}(MC;L1,L2)-unreachable, then{a mathematical formula}(a1,a2)is M-unreachable where M is the set of actions a so obtained. For every{a mathematical formula}(α,L)∈MCand grounding gr of α such that gr and γ are coherent over L, we let{a mathematical formula}a=gr(α).Let {a mathematical formula}M be the matching such that the two groundings {a mathematical formula}gr1 and {a mathematical formula}gr2 are {a mathematical formula}M-adapted. By Proposition 87, we have that {a mathematical formula}M⊇ML1,L2. Suppose (i) holds and put {a mathematical formula}q=gr1(l1)=gr2(l2)∈Γa1+∩Prea2−. Consider now any action {a mathematical formula}a∈M and let α be an action schema such that {a mathematical formula}a=gr(α) for some grounding gr. Let L be the {a mathematical formula}T-class of formulas of α on which gr and γ are coherent. By construction, it follows that {a mathematical formula}(α,L)∈MC. Consider now the matching {a mathematical formula}M˜ between {a mathematical formula}α1 and α such that {a mathematical formula}gr1 and gr are {a mathematical formula}M˜-adapted. We have that {a mathematical formula}M˜⊇ML1,L. Then, by (i) we have that {a mathematical formula}l1∉M˜Effα+, which implies that {a mathematical formula}q∉Effa−. This shows that condition (i) of Definition 54 is satisfied. Similarly, one can prove that condition (ii) of Definition 93 yields condition (ii) of Definition 54. Finally the fact that (iii) of Definition 93 yields condition (iii) of Definition 54 follows from a repeated application of relation (28).  □
      </paragraph>
      <paragraph>
       We are now ready to lift Definition 56. Given a set of durative actions and classes {a mathematical formula}AdC(T)⁎⊆AdC(T), we put{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 95">
       Pairwise relevant non-overlapping action schemasFor a template {a mathematical formula}T, the set of durative action schemas {a mathematical formula}Ad is said to be pairwise relevant non-overlapping if we can find a set of durative schema-class pairs {a mathematical formula}AdC(T)⁎⊆AdC(T) with {a mathematical formula}AdC(T)⁎⊇AdC(wk,T) such that the following properties are satisfied:
      </paragraph>
      <list>
       <list-item label="(A)">
        for every {a mathematical formula}(Dα1,L1),(Dα2,L2)∈AdC(T)⁎, denoted {a mathematical formula}M=ML1,L2, one of the following conditions holds true:
       </list-item>
       <list-item label="(B)">
        for every {a mathematical formula}(Dα1,L1),(Dα2,L2)∈AdC(T)⁎, denoted {a mathematical formula}M=ML1,L2, one of the following conditions holds true:
       </list-item>
       <list-item label="(C)">
        for every {a mathematical formula}(Dα1,L1)∈AdC(T)⁎, {a mathematical formula}(α2,L2)∈AC(T)rel⁎, denoted {a mathematical formula}M=ML1,L2, one of the following conditions is satisfied:
       </list-item>
      </list>
      <paragraph label="Proof">
       The proof is therefore complete.  □
      </paragraph>
      <paragraph>
       We are now ready to give the lifted versions of our main results: Theorem 53 and Corollary 58. Proofs are straightforward consequences of our previous definitions and results.
      </paragraph>
      <paragraph label="Corollary 97">
       Consider a template{a mathematical formula}Tand suppose that the set of instantaneous action schemas{a mathematical formula}Aiand that of durative action schemas{a mathematical formula}Adsatisfy the following properties:
      </paragraph>
      <list>
       <list-item>
        every{a mathematical formula}α∈Aiis strongly safe;
       </list-item>
       <list-item>
        for every{a mathematical formula}Dα∈Ad,{a mathematical formula}Dαstis strongly safe and{a mathematical formula}Dα⁎is safe;
       </list-item>
       <list-item>
        {a mathematical formula}Adis pairwise relevant non-overlapping.
       </list-item>
      </list>
      <paragraph label="Corollary 98">
       Consider a template{a mathematical formula}Tand suppose that the set of instantaneous action schemas{a mathematical formula}Aiand that of durative action schemas{a mathematical formula}Adsatisfy the following properties:
      </paragraph>
      <list>
       <list-item>
        for every{a mathematical formula}(Dα,L)∈AdC(wk,T), then{a mathematical formula}Dα⁎Lis weakly safe of type (a);
       </list-item>
       <list-item>
        for every{a mathematical formula}(α,L)∈AC(T)∖(AstC(wk,T)∪AendC(wk,T)), then,{a mathematical formula}αLis either irrelevant or balanced.
       </list-item>
      </list>
      <paragraph>
       We end this section by presenting two examples from the IPCs in which we apply Corollary 98, Corollary 92 to demonstrate the invariance of the templates under consideration. Corollary 97 is the most general one and can be used in more complex cases.
      </paragraph>
      <paragraph label="Example 17">
       Floortile domainConsider our usual template:{a mathematical formula} The action schemas in the domains are: {a mathematical formula}Ad={changeColor,paintUp,paintDown,up,down,right,left}. The schemas paintUp and paintDown are symmetrical and differ only on formulas not matching {a mathematical formula}Tft. They have the same {a mathematical formula}T-classes {an inline-figure} and {an inline-figure}. As seen in Example 16, the pure schemas {a mathematical formula}paintUp⁎L1st and {a mathematical formula}paintUp⁎L1end are irrelevant and {a mathematical formula}paintUp⁎L2 is weakly safe of type (a). The same holds for {a mathematical formula}paint-down⁎L1 and {a mathematical formula}paint-down⁎L2.The schemas up, down, right, left are also symmetrical and differ only on formulas not in the components of {a mathematical formula}Tft. They have the same {a mathematical formula}T-classes {an inline-figure} and {an inline-figure}. The schemas {a mathematical formula}up⁎Li, {a mathematical formula}down⁎Li, {a mathematical formula}right⁎Li and {a mathematical formula}left⁎Li, with {a mathematical formula}i=3,4, are all weakly safe of type (a).The schema changeColor has no formula matching the template, hence its start and end fragments are both irrelevant.By Corollary 98, the template {a mathematical formula}Tft is invariant.
      </paragraph>
      <paragraph label="Example 18">
       Depot domainConsider the domain Depot (see Appendix B) and the template:{a mathematical formula} Invariants of this template mean that a hoist can be in two possible states: lifting a crate or available. The action schemas in the domains are all durative:{a mathematical formula} We indicate them as {a mathematical formula}Dα1,…,Dα5 respectively and, given {a mathematical formula}Dαi, its variables as {a mathematical formula}xi,yi,….To demonstrate that {a mathematical formula}Tdp is invariant, we want to apply Corollary 92. We start with condition (ii) since {a mathematical formula}Ai is empty.The action {a mathematical formula}Dα1=drive has no formulas that match the template so it is strongly safe. The other schemas have respectively {a mathematical formula}T-classes {an inline-figure}. There are only two fragments of the durative actions that are not strongly safe as they are unbounded: {a mathematical formula}αL33end and {a mathematical formula}αL44end. However, their auxiliary versions {a mathematical formula}α⁎L33end and {a mathematical formula}α⁎L44end are strongly safe since they are balanced (when the over all condition {an inline-figure} is added to the end effects, it matches the delete effect {an inline-figure} and balances the add effect {an inline-figure}; similar considerations hold for {a mathematical formula}Dα4). Reachability for {a mathematical formula}α⁎L33end and {a mathematical formula}α⁎L44end is a straightforward check. In consequence, condition (ii) holds.We now need to verify condition (iii) of Corollary 92, i.e. {a mathematical formula}Ad is relevant right isolated. Under the re-writing {a mathematical formula}ML3L4, we have that {a mathematical formula}x3=x4 and {a mathematical formula}y3=y4 and therefore {a mathematical formula}EffαL33end+∪ML3L4EffαL44end+={available(x3)=available(x4)}. Hence condition (i) of Definition 90 is satisfied.We can conclude that {a mathematical formula}Tdp is an invariant template.
      </paragraph>
      <paragraph label="Example 19">
       This example shows how our invariant synthesis can be used as a debugging tool and as a method to improve the modelling of planning domains. In this case, the addition of an over all condition is sufficient to prevent erroneous physical phenomena as a store being full and empty at the same time.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Guess, check and repair algorithm
     </section-title>
     <paragraph>
      As with related techniques [26], [27], [45], [33], our algorithm for finding invariants implements a guess, check and repair approach. It starts by generating a set of initial simple templates. For each template {a mathematical formula}T, it then applies the results stated in the previous sections to check its invariance. If {a mathematical formula}T is invariant, the algorithm outputs it. However, if the algorithm does not manage to prove the invariance of {a mathematical formula}T, it discards it. Before rejection, however, the algorithm tries to fix the template by generating a set of new templates that are guaranteed not to fail for the same reasons as {a mathematical formula}T. In turn, these new templates need to be checked against the invariance conditions as they might fail for other reasons.
     </paragraph>
     <section label="9.1">
      <section-title>
       Guessing initial templates
      </section-title>
      <paragraph>
       When we create the set of initial templates, we ignore constant relations, i.e. relations whose ground atoms have the same truth value in all the states (for example, type predicates). In fact, they are trivially invariants and so are typically not interesting.
      </paragraph>
      <paragraph>
       For each modifiable relation r with arity k, we generate {a mathematical formula}k+1 initial templates. They all have one component and zero or one counted variable (which can be in any position from 0 to {a mathematical formula}k−1): {a mathematical formula}〈r/k,k〉 (no counted variable) and {a mathematical formula}〈r/k,p〉 with {a mathematical formula}p∈{0,…,k−1}. Since the templates have one component, there is only one possible admissible partition {a mathematical formula}FC, with {a mathematical formula}C={c}. Hence, we construct the template {a mathematical formula}T=(C,FC).
      </paragraph>
      <paragraph label="Example 20">
       Floortile domainConsider the components {a mathematical formula}c1=〈robotAt,2,1〉. Let {a mathematical formula}FC={F1} where {a mathematical formula}F1={(c1,0)}. An initial template is {a mathematical formula}T1=({c1},{F1}). Intuitively, invariants of {a mathematical formula}T1 mean that a robot can occupy only one position at any time and our algorithm validates it as an invariant. Another initial template is built by considering the component {a mathematical formula}c2=〈robotAt,2,0〉 and the partition {a mathematical formula}FC={F2} where {a mathematical formula}F2={(c2,1)}. We have another initial template: {a mathematical formula}T2=({c2},{F2}). Invariants of this template mean that a tile cannot be occupied by more than one robot, which is not true in general, and our algorithm correctly discards it. Finally, consider the component {a mathematical formula}c3=〈robotAt,2,2〉 and the partition {a mathematical formula}FC={F3} where {a mathematical formula}F3={(c3,0),(c3,1)}. Another initial template is {a mathematical formula}T3=({c3},{F3}). This is also not an invariant and is rejected.If we repeat this process with every modifiable relation r in the {a mathematical formula}Floortile domain, we obtain the full set of initial templates.
      </paragraph>
     </section>
     <section label="9.2">
      <section-title>
       Checking conditions for invariance
      </section-title>
      <paragraph>
       We apply the results stated in the previous sections to check the invariance of a template. In particular, we apply our most operative results: Corollary 74, Corollary 92, Corollary 97, Corollary 98. All these results work at the level of action schemas, not ground actions.
      </paragraph>
      <paragraph>
       We first need to verify if all the instantaneous action schemas {a mathematical formula}A in the domain, both the native ones and those obtained from the fragmentation of durative actions, respect the strong safety conditions. We then check safety conditions that only involve durative action schemas that are not strongly safe. Finally, we validate additional conditions that avoid the intertwinement of potentially dangerous durative actions. Given the different computational complexity of our results (see considerations below), our algorithm checks the applicability of them in the following order: first, Corollary 74, which involves only conditions for instantaneous schemas, then Corollary 98, which considers safety conditions for individual action schemas, and finally Corollary 92, Corollary 97, which need to verify conditions involving pairs of durative action schemas. To implement this procedure, we apply the decision tree shown in Fig. 11 to the set of action schemas {a mathematical formula}A. The leaves labelled as Possibly Not Invariant arise when our sufficient results do not apply. In this case, we cannot assert anything about the invariance of the template.
      </paragraph>
      <paragraph>
       Our checks involve the analysis of all {a mathematical formula}T-classes in each action schema α in the domain. Since the {a mathematical formula}T-classes form a partition of the set of formulas in the schema that match the template, the maximum number of {a mathematical formula}T-classes is equal to the number of such formulas. We can estimate this term with the product {a mathematical formula}ω⋅|C| where ω is the maximum number of formulas in any schema that shares the same relation and {a mathematical formula}|C| is the cardinality of the template's component set {a mathematical formula}C. We deduce that all safety checks for individual schemas (both the instantaneous and the durative ones) have a computational complexity of the order of {a mathematical formula}M⋅|A|⋅ω⋅|C|, where M is the maximum number of formulas appearing in any schema and {a mathematical formula}|A| is the total number of schemas. Consequently, this is the computational complexity of Corollary 74, Corollary 98 that only involve safety checks.
      </paragraph>
      <paragraph>
       The check of the right relevant isolated property of Definition 90, which is needed in Corollary 92, and the check of the pairwise relevant non overlapping property of Definition 95, which is used in Corollary 97, instead involve schema-class pairs and possibly families of matchings. When the condition to be checked only involves a fixed matching, its computational complexity is of the order of {a mathematical formula}M2⋅|A|2⋅ω2⋅|C|2. This leaves out all the checks of the unreachability conditions for pairs of schemas, namely, (iii) of Definition 90 and (Aii), (Bii), (Cii) of Definition 95 that need to verify the conditions expressed in Definition 88, Definition 93. Below, we provide some details on how these conditions can also be efficiently checked at the algorithmic level.
      </paragraph>
      <list>
       <list-item label="•">
        Check ofDefinition 88: The two instances of conditions (i) and (ii) involve a fixed matching. The two instances of condition (iii) instead are quantified over the all possible matchings containing {a mathematical formula}ML1,L2. Consider the first case (the second one being analogous). We first check if {a mathematical formula}w(Preα⁎Liiend+)≥2 for {a mathematical formula}i=1 or for {a mathematical formula}i=2: if this is the case, then condition (iii) is verified. If {a mathematical formula}Preα⁎Liiend+={li} and the formulas {a mathematical formula}li are such that {a mathematical formula}Rel[l1]≠Rel[l2] then, again, condition (iii) is verified. If, instead, {a mathematical formula}Rel[l1]=Rel[l2], we show that condition (iii) is never satisfied. Indeed, in this case, the two formulas match the template through the same component {a mathematical formula}c=〈r/k,p〉. We write {a mathematical formula}li=r(v0i,…,vk−1i) for {a mathematical formula}i=1,2 and we note that {a mathematical formula}(vj1,vj2)∈ML1,L2 for every {a mathematical formula}j≠p. Therefore, if {a mathematical formula}p=k (all variables are fixed in the component), necessarily, {a mathematical formula}l1=ML1,L2l2. If instead {a mathematical formula}p&lt;k, then {a mathematical formula}l1=Ml2 when we consider {a mathematical formula}M=ML1,L2∪{(vp1,vp2)}. Finally, condition (iii) is certainly not verified if {a mathematical formula}Preα⁎Liiend+=∅ for {a mathematical formula}i=1 or {a mathematical formula}i=2. For two given schema-class pairs, this check therefore has complexity {a mathematical formula}M2.
       </list-item>
       <list-item label="•">
        Check ofDefinition 93: All three properties in this definition, in principle, involve checking a condition over all possible matchings containing {a mathematical formula}ML1,L2. We first consider (i). Suppose that we find {a mathematical formula}l1 and {a mathematical formula}l2 that satisfy {a mathematical formula}l1=ML1,L2l2. Now fix {a mathematical formula}(α,L)∈MC. If for every {a mathematical formula}l∈Effα− we have that {a mathematical formula}Rel[l]≠Rel[l1], then (i) holds. If instead there are {a mathematical formula}l∈Effα− such that {a mathematical formula}Rel[l]=Rel[l1]=〈r/k〉, for each of them we proceed as follows. We write {a mathematical formula}l1=r(v01,…,vk−11) and {a mathematical formula}l=r(v0,…,vk−1) and for each {a mathematical formula}j=0,…,k−1 we consider the two variables {a mathematical formula}vj1 and {a mathematical formula}vj. If there exists j such that either {a mathematical formula}(vj1,w)∈ML1,L for some {a mathematical formula}w∈Vα∖{vj}, or {a mathematical formula}(w1,vj)∈ML1,L for some {a mathematical formula}w1∈Vα1∖{vj1}, then for sure {a mathematical formula}(vj1,vj)∉M for any matching {a mathematical formula}M⊇ML1,L and (i) is verified. Now consider the case in which (i) is not verified. Now {a mathematical formula}M=ML1,L∪{(vj1,vj)|j=1,…,k} is a matching such that {a mathematical formula}l1=Ml.Checking condition (ii) is analogous to (i). As far as condition (iii) is concerned, note that when we need to check this property, the schemas involved will be reachable and not heavy. For property (iii) to hold, we must have {a mathematical formula}PreαLii+={li} for {a mathematical formula}i=1,2. Following the same argument as in the previous item, if {a mathematical formula}Rel[l1]=Rel[l2], then (iii) is not verified. If instead {a mathematical formula}Rel[l1]≠Rel[l2], we consider the set {a mathematical formula}EffαL11+. If it is empty or if {a mathematical formula}EffαL11+={l} and {a mathematical formula}Rel[l]≠Rel[l2], then (iii) is verified. Otherwise, it is not. We conclude that for two given schema-class pairs, this check has complexity {a mathematical formula}M3⋅|A|⋅ω⋅|C|⋅N where N is the maximum number of variables in any formula in the domain.
       </list-item>
      </list>
      <paragraph>
       The above considerations allow us to conclude that the check of the right relevant isolated property has complexity {a mathematical formula}M2⋅|A|2⋅ω2⋅|C|2, while the check of the pairwise relevant non overlapping property has complexity {a mathematical formula}M3⋅|A|3⋅ω3⋅|C|3⋅N. There are also the complexities of checking the properties of Corollary 92, Corollary 97, respectively.
      </paragraph>
      <paragraph label="Example 21">
       Floortile domainThe variables for the computational complexity analysis are as follows:{a mathematical formula}
      </paragraph>
     </section>
     <section label="9.3">
      <section-title>
       Repairing templates
      </section-title>
      <paragraph>
       In analysing an action schema α, when we reach a failure node in our decision tree, we discard the template {a mathematical formula}T under consideration since we cannot prove its invariance. This might be because of two reasons: either {a mathematical formula}T is not an invariant or our sufficient conditions are not powerful enough to capture it. Before discarding the template, however, we try to fix it in such a way as to obtain new templates for which it might be possible to prove invariance under our conditions. In particular, based on the schema α, we enlarge the set of components of the template by adding suitable formulas that appear in the preconditions and negative effects of α since they can be useful to prove that α is weakly or strongly safe.
      </paragraph>
      <paragraph>
       If the algorithm rejects {a mathematical formula}T because it finds an instantaneous schema that is heavy or unbalanced (first step in the decision tree), no fixes are possible for {a mathematical formula}T. Since α leads to a weight greater than or equal to two for at least one instance of {a mathematical formula}T, enlarging the set of components of {a mathematical formula}T cannot help in repairing the template. Similarly, if there are durative schemas that are non-executable or unreachable, no fixes are possible since these properties cannot be changed by adding components. However, when a failure node is reached in the presence of unbounded schemas, enlarging the set of components might prove useful in making them weakly or strongly safe schemas. We operate as follows: for each unbounded schema α, we try to turn it into a balanced action schema and, when α is the end fragment of a durative action Dα, we alternatively attempt to make Dα a weakly safe schema, as defined in Definition 78.
      </paragraph>
      <paragraph>
       Take a template {a mathematical formula}T=(C,FC) that has been rejected by the algorithm. Let k be the number of fixed variables for {a mathematical formula}T and let m be the number of its components. Consider an unbounded schema α with relevant formula l. We look for another formula {a mathematical formula}l′ in α with the following characteristics:
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}Rel[l′]=〈r′/a′〉, where {a mathematical formula}a′=k or {a mathematical formula}a′=(k+1);
       </list-item>
       <list-item label="(ii)">
        There exists a bijection β from the variables of l to the variables of {a mathematical formula}l′ such that {a mathematical formula}Arg[i,l]=Arg[β(i),l′] for every {a mathematical formula}i∈I;
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}l′∈Preα+∩Effα−.
       </list-item>
      </list>
      <paragraph>
       If α is the end fragment of a durative action Dα, then condition (iii) can be substituted with one of the alternative following conditions:
      </paragraph>
      <list>
       <list-item label="(iv)">
        {a mathematical formula}l′∈Preα⁎st+∩Effα⁎st−
       </list-item>
       <list-item label="(v)">
        {a mathematical formula}l′∈Preα⁎st+∩Effα⁎end−
       </list-item>
      </list>
      <paragraph>
       For each formula {a mathematical formula}l′ that satisfies conditions (i), (ii) and one of conditions (iii), (iv) and (v), we create a new component {a mathematical formula}c′=〈r′/k′,p′〉, where {a mathematical formula}p′∈{0,…,k′}, and one new template {a mathematical formula}T′=(C′,FC′), where {a mathematical formula}C′=C∪{c′} and {a mathematical formula}FC′ is an admissible partition of {a mathematical formula}FC′ such that for each {a mathematical formula}c1,c2∈C, we have that {a mathematical formula}(c1,i)∼FC′(c2,j) if and only if {a mathematical formula}(c1,i)∼FC(c2,j) and {a mathematical formula}(c,i)∼FC′(c′,j) if and only if {a mathematical formula}Arg[i,l]=Arg[j,l′] (or, equivalently, {a mathematical formula}j=β(i)).
      </paragraph>
      <paragraph>
       If we find a formula {a mathematical formula}l′ that satisfies condition (iii), the schema α is guaranteed to be balanced for {a mathematical formula}T′; if the formula {a mathematical formula}l′ satisfies condition (iv), α is guaranteed to be weakly safe of type (a) for {a mathematical formula}T′; finally, if the formula {a mathematical formula}l′ satisfies condition (v), α is guaranteed to be weakly safe of type (b) for {a mathematical formula}T′.
      </paragraph>
      <paragraph label="Example 22">
       Floortile domainConsider the template {a mathematical formula}T2=({c2},{F2}) as indicated in Example 21 and the action schema {a mathematical formula}α=upend: {a mathematical formula}Preα=∅, {an inline-figure}. The formula robotAt(r,y) matches {a mathematical formula}T2 and forms a {a mathematical formula}T-class {an inline-figure}. The pure action schema {a mathematical formula}αL1 is unbounded as well as the end parts of the other schemas that indicate movements. If we apply our decision tree to {a mathematical formula}T2 and the set of actions {a mathematical formula}A, we cannot prove that {a mathematical formula}T2 is an invariant since the unbounded schemas are not weakly safe. Before discarding {a mathematical formula}T2, we try to fix it. In particular, the formula clear(y) satisfies conditions (i), (ii) and (iv) above. If we add it to {a mathematical formula}T2, we obtain a new template {a mathematical formula}T2′=({c2,c2′},{F2′}) where {a mathematical formula}c2′=〈clear,1,1〉 with {a mathematical formula}Fc2′={(c2′,0)} and {a mathematical formula}F2′={(c2,1),(c2′,0)}. If we apply our decision tree to this new template, we can prove that {a mathematical formula}T2′ is an invariant since Corollary 98 can be successfully applied (all schemas are either strongly safe or weakly safe of type (a)). Intuitively, invariants of this template mean that a tile is either clear or occupied by a robot.
      </paragraph>
     </section>
    </section>
    <section label="10">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      To evaluate the performance of our Temporal Invariant Synthesis, referred as TIS in what follows, we have performed a number of experiments on the IPC benchmarks. We implemented the TIS algorithm, reported in Section 9, in the Python language and conducted the experiments by using a Quad Core 2.6 GHz Intel i5 processor with 4 GB memory.
     </paragraph>
     <paragraph>
      Since our paper proposes a domain analysis, the core measure of success is whether this analysis can find invariants that previous methods cannot. We carry out this evaluation in Sections 10.1 and 10.2. In particular, in Section 10.1, we focus on the number and quality of the invariants found by TIS. In Section 10.2, we present a comparison between our TIS and the invariant synthesis that is used within the planner TFD [18], both in terms of the invariants found and of the state variables that can be synthesised based on such invariants. The experimental results (in particular, Fig. 13 and Table 6) show that TIS finds more invariants than related techniques, which in turn results in a more compact representation using a smaller set of state variables.
     </paragraph>
     <paragraph>
      To enrich our experimental analysis, we also test the hypothesis that more compact encodings benefit the performance of the planners that use state variables. In Section 10.3, we present experiments that show the impact of using TIS, which results in a smaller set of state variables, on the performance of two state-of-the-art planners that use a variable/value representation.
     </paragraph>
     <section label="10.1">
      <section-title>
       Quality of the representation
      </section-title>
      <paragraph>
       In this section, we discuss the number and quality of the invariants found by TIS, and the efficiency of our algorithm.
      </paragraph>
      <paragraph>
       Fig. 12 shows the invariants that our technique finds for all the IPC temporal domains (from IPC'02 to IPC'14). Each set in Fig. 12 corresponds to a set {a mathematical formula}C of components, which are separated by a comma and indicated with the relation name (arity is omitted here for brevity), the positions of the fixed variables (not enclosed in square brackets) and the position of the counted variable (enclosed in square brackets). For example, {at 0 [1], in 0 [1]} indicates the invariant with the components {a mathematical formula}c1=〈at/2,1〉 and {a mathematical formula}c2=〈in/2,1〉. The admissible partitions are not shown for brevity, however in most of the cases the only admissible partition is the trivial one.
      </paragraph>
      <paragraph>
       For comparison purposes only, we have devised a variant of our invariant synthesis technique, which we refer to as Simple Invariant Synthesis (SIS). SIS is the simplest possible extension of Helmert's original technique to temporal domains. It fragments each durative schema into three instantaneous schemas and then applies Helmert's original technique, i.e. it judges safe only instantaneous schemas that in our classification are irrelevant or balanced. We use the SIS technique to explore the impact on runtime of the sophisticated checks that we need to perform to make sure that the durative actions that are not balanced are indeed safe.
      </paragraph>
      <paragraph>
       The second and the third columns of Table 5 compare the number of invariants found by SIS to those found by TIS for the temporal domains of the last three competitions: IPC'08, IPC'11, and IPC'14. The fourth column reports the TIS runtime (RT) for generating the invariants. The numbers tell us that the TIS computation time to calculate invariants is negligible and that there is no significant delay associated with the checks required by our algorithm, in particular the complex checks involving pairs of schemas. While these checks do not impact the computational time, they allow us to find a more comprehensive set of invariants than a simpler technique such as SIS.
      </paragraph>
      <paragraph>
       The last column in Table 5 (# Fix) reports the number of invariants obtained by repairing failed templates in our TIS algorithm and provides an indication of the importance of the repair step in our algorithm.
      </paragraph>
     </section>
     <section label="10.2">
      <section-title>
       Comparison with the temporal fast downward invariant synthesis
      </section-title>
      <paragraph>
       Currently, it is difficult to compare our technique for generating temporal invariants from lifted domains to related techniques since they either handle non temporal domains only [20], [27], [45], [46], [33] or work at the ground level of the representation [47], [48]. The approach that appears most similar to ours is the invariant synthesis implemented within the Temporal Fast Downward (TFD) planner [18], which we refer to as TFD-IS (simply TFD in the tables and figures). This technique also works on lifted domains, but it refines the results obtained at this level by using information on reachable ground atoms. In this section, we present a comparison between our TIS and TFD-IS with respect to: (i) the invariants found by the two approaches; and (ii) the state variables that can be synthesised based on such invariants. In comparing invariants, we consider the temporal domains of all IPCs, while in comparing state variables we focus on those domains in which TFD-IS and TIS output different invariants. We start with a brief description of TFD-IS.
      </paragraph>
      <paragraph>
       Our knowledge of TFD-IS is based on examination of the code{sup:5} and an analysis of the results that the code produces, since there is no formal account of the technique. TFD-IS is an extension of Helmert's original synthesis (described in Section 11.2) devised to deal with temporal and numeric domains. As with the original technique, TFD-IS employs a guess, check and repair approach to find invariants. The algorithm analyses the temporal schemas directly, without splitting them into their start, over all and end fragments. Only two types of relevant durative action schemas are evaluated as safe: those that in our classification are balanced at start and irrelevant at end and those that are weakly safe of type (a). In all the other cases, the action schemas are labelled as unsafe and the candidate invariant is dismissed.
      </paragraph>
      <paragraph>
       Fig. 13 shows a few examples of the different sets of invariants found by the TFD-IS and our TIS, taking one temporal domain from each IPC competition.
      </paragraph>
      <paragraph>
       Table 6 shows the number of invariants found by the two techniques in all the domains of the IPC competitions. In 12 out of 33 cases the TIS outperforms the TFD synthesis, and in all the other cases the two synthesis output the same invariants. In several cases, the difference in the number of invariants is significant (e.g. for {a mathematical formula}Depots, TIS finds five invariants against zero for TFD-IS; for {a mathematical formula}Airport, TIS finds ten invariants against one for TFD-IS).
      </paragraph>
      <paragraph>
       We next investigate how the different number of invariants reflects on the number of state variables that are generated based on them. In this context, together with TIS and TFD-IS, we also consider the case in which no invariants are used to synthesise state variables, referred to as NIS (No Invariant Synthesis). In this case, a state variable with two truth values (true and false) is produced for each atom in the domain. We use NIS as a baseline for our experiments. Table 7 reports the comparison for those IPC temporal domains in which TIS and TFD-IS produce different invariants and, for brevity, shows three problems for each domain. The table shows that, by increasing the number of invariants found, TIS gives rise to a more compact representation than NIS or TFD-IS. In all the domains TIS produces a significant reduction in the number of state variables in comparison to NIS and TFD-IS. In {a mathematical formula}Sokoban, for example, the reduction is greater than one order of magnitude.
      </paragraph>
     </section>
     <section label="10.3">
      <section-title>
       Performance in temporal planners
      </section-title>
      <paragraph>
       We have performed a number of additional experiments in order to evaluate the impact of using the state variables generated by TIS on the performance of those planners that use a variable/value representation. In particular, we focus here on the performance of two planners: Temporal Fast Downward (TFD) [18] and POPF-SV, a version of POPF [12] that makes use of multi-valued state variables.{sup:6}
      </paragraph>
      <section label="10.3.1">
       <section-title>
        TFD: temporal fast downward
       </section-title>
       <paragraph>
        TFD is a planning system for temporal and numeric problems based on Fast Downward (FD) [32], which is limited to non temporal and non numeric domains. TFD uses a multi-valued variable representation called “Temporal Numeric {a mathematical formula}SAS+” (TN-{a mathematical formula}SAS+), which is a direct extension of the “Finite Domain Representation” (FDR) used within FD to handle tasks with time and numeric fluents. TN-{a mathematical formula}SAS+ captures all the features of PDDL – Level 3 and represents planning tasks by using: i) a set of state variables, which are divided into logical and numeric state variables; ii) a set of axioms, which are used to represent logical dependencies and arithmetic sub-terms; and iii) a set of durative actions, which comprise: a) a duration variable; b) start, persistent and end conditions; and c) start and end effects.
       </paragraph>
       <paragraph>
        TFD translates PDDL2.1 tasks into TN-{a mathematical formula}SAS+ tasks first and then performs a heuristic search in the space of time-stamped states by using a context-enhanced additive heuristic [34] extended to handle time and numeric fluents. The translation from PDDL2.1 to TN-{a mathematical formula}SAS+ works in four steps. First, the PDDL instance is normalised, i.e. types are removed and conditions and effects are simplified. Then, an instance where all the formulas are ground is produced through a grounding step and the invariant synthesis (which we have previously indicated as TFD-IS) is applied to generate invariants (the grounding and the invariant synthesis can be performed in parallel). Starting from the invariants provided by the invariant synthesis and the ground domain, a set of multi-valued state variables is generated. Finally, a set of actions is obtained starting from PDDL actions, which describe how the state variables change over time.
       </paragraph>
       <paragraph>
        In Fig. 14, Fig. 15, Fig. 16, we compare TFD with two alternative versions, one in which we substitute our technique, TIS, for the original TFD-IS, and one in which we substitute the baseline technique, NIS (No Invariant Synthesis), for TFD-IS. We focus on the IPC domains in which TFD-IS and TIS produce different invariants (see Table 6). The search time (ST) is in seconds and, following the conventions of the IPCs, the timeout has been set to 1800 seconds. Problems for which a plan could not be found within the timeout by all three techniques do not appear in the table.
       </paragraph>
       <paragraph>
        In several cases, the lower number of state variables produced by TIS speeds up the TFD planner, for example in the domains {a mathematical formula}Modeltrain, {a mathematical formula}Sokoban and {a mathematical formula}Storage, and, for some problems, the gain is very high, for example {a mathematical formula}Storage – p12, p14, p15 and {a mathematical formula}Sokoban – p03, p05, p07, p16. In domains such as {a mathematical formula}Rover, {a mathematical formula}Mapanalyser and {a mathematical formula}Floortile, when TFD manages to solve the problems, it is so fast that the impact of the number of state variables is negligible. There are also a few cases where the results are mixed, see for example {a mathematical formula}Depots as well as both versions of {a mathematical formula}Pipesworld (tankage and no tankage). The reduction in the number of variables sometimes constitutes an advantage for the planner (see for example {a mathematical formula}Depots – p16, {a mathematical formula}PipesworldNoTankage – p13, p20, p25, {a mathematical formula}p30, p31,p35, p37, {a mathematical formula}PipesworldTankage – p09, p29, p30), while other times it seems to be detrimental for the search (see {a mathematical formula}Depots – p21, {a mathematical formula}PipesworldNoTankage – p27, p28, p39, {a mathematical formula}PipesworldTank{a mathematical formula}age – p36, p37, p39, p45, p49). It should be noted that in {a mathematical formula}Depots and {a mathematical formula}PipesworldNoTankage, TFD-IS does not find any invariants so we are effectively comparing the binary encoding based on NIS against the multi-value state variables encoding based on TIS. It is interesting to see that in {a mathematical formula}PipesworldTankage there are several instances (for example, p36, p39, p49) in which the binary encoding performs best.
       </paragraph>
       <paragraph>
        In terms of problem coverage, the two techniques perform similarly. In some cases, finding more invariants helps in solving difficult problems, see for example PipesworldNoTankage – p25, p35, p37, Storage – p15, and Sokoban – p07. However, there are also cases in which the opposite is true, for example in PipesworldNoTankage – p39, PipesworldTankage – p36, p37, p45, p49. Note that there are also problems in which the binary representation works best: {a mathematical formula}PipesworldTankage – p39, {a mathematical formula}p49.
       </paragraph>
       <paragraph>
        The intuition of the influence of the number of state variables on planning performance comes from the observation that TFD uses graph structures for the computation of the heuristic estimates whose complexity is strongly influenced by this number. Our results indicate that, while this intuition is probably correct, there are other details in the heuristic computation that need to be considered and the connection between the number of state variables and the graphs' structure must be analysed in greater depth. The experiments show that TIS has the potential to speed up search and to improve the coverage of planners, but more research is needed to understand how a more compact representation can be exploited at its full potential across all the domains and problems. For example, it would be interesting to analyse the performance of TFD when different subsets of the invariants are used to generate state variables. We did not perform such experiments as this analysis is beyond the scope of this work.
       </paragraph>
      </section>
      <section label="10.3.2">
       <section-title>
        POPF-SV: forward-chaining partial-order planner with state variables
       </section-title>
       <paragraph>
        POPF-SV is a version of the forward-chaining temporal planner POPF [12] that reads a variable/value representation of the domain and uses it for performing an inference step in a pre-processing phase and for reducing the size of the states during search. In particular, POPF-SV reads a standard PDDL task along with its corresponding TN-{a mathematical formula}SAS+ translation. This translation is the same as in TFD, so the invariant synthesis used in POPF-SV is TFD-IS, as described in the previous section. However, unlike TFD, POPF-SV reasons with both the original PDDL domain and the TN-{a mathematical formula}SAS+ version of the domain. The multi-valued state variable representation of the task is not used in the heuristic computation, but it is employed for two different purposes. An inference step based on the state variables is performed to support temporal preferences. This step extracts rules that are then used during search (for example, is it possible to have action a within 10 time units of action b). The second use of the invariant analysis aims to make the state representation more efficient. Only one value for each multi-valued state variable needs to be stored within a state since if one is true then the others must necessarily be false. This property results in massive savings in memory. This is particularly beneficial for POPF as memory is generally what causes the planner to fail (rather than time).
       </paragraph>
       <paragraph>
        In Fig. 17, Fig. 18, Fig. 19, we compare POPF-SV with two alternative versions, one in which we replace the original TFD-IS used within POPF-SV with our technique, TIS, and one in which we replace TFD-IS with NIS, which we use as a baseline for our experiments. We focus on the IPC domains in which TFD-IS and TIS produce different invariants (see Table 6). The search time (ST) is in seconds and, following the conventions of the IPCs, the timeout has been set to 1800 seconds. Problems for which a plan could not be found within the timeout by all three techniques do not appear in the table.
       </paragraph>
       <paragraph>
        The tables clearly show that for POPF-SV dealing with fewer state variables is beneficial to the algorithm across all the domains. In the domains that are more challenging for the planner, such as {a mathematical formula}Depots, {a mathematical formula}PipesworldTankage, {a mathematical formula}PipesworldNoTankage{a mathematical formula}Sokoban, and {a mathematical formula}Floortile, the gain is significant. These results are in line with our intuition that a larger set of invariants help to obtain more compact representations, which in turn have a positive impact on the planners' performance. The three versions work similarly in terms of coverage.
       </paragraph>
      </section>
     </section>
     <section label="10.4">
      <section-title>
       Beyond the IPC
      </section-title>
      <paragraph>
       The generality of our approach for synthesising invariants from lifted temporal domains cannot be fully appreciated by considering IPC domains only. This is because the durative actions of such domains present a rather uniform structure: most of the actions are either balanced or weakly safe of type (a). However, in domains that describe practical applications, other types of actions are often used. For example, in data processing, web services composition, production and software domains [2], [29], [40], [30], the creation of new objects from an empty set is often required. Typically, the actions that create the new objects are bounded or weakly safe of type (c). TFD-IS fails to identify invariants in such situations as it regards such actions as unsafe.
      </paragraph>
      <paragraph>
       As an example, consider the following case.
      </paragraph>
      <paragraph label="Example 23">
       DataProcessing domainConsider the domain DataProcessing (see Appendix D) and the template:{a mathematical formula} Assuming that each file has a unique identification in the file system, an invariant of this template is that a file can be in only one location at any point in time. The action schemas in the domains are all durative:{a mathematical formula} We indicate them as {a mathematical formula}Dα1,…,Dα5 respectively and, given {a mathematical formula}Dαi, its variables as {a mathematical formula}xi,yi,….For {a mathematical formula}i=2,5, {a mathematical formula}Dαi has just one equivalence class {an inline-figure}. Instead for {a mathematical formula}i=1,3,4, {a mathematical formula}Dαi has two equivalence classes {an inline-figure} and {an inline-figure}. We set {a mathematical formula}AdC(Tdl)1={(Dαi,Li)|i=2,5}, {a mathematical formula}AdC(Tdl)2={(Dαi,Li)|i=1,3,4}, and {a mathematical formula}AdC(Tdl)3={(Dαi,Li′)|i=1,3,4}. We then note that for each {a mathematical formula}(Dα,L)∈AdC(Tdl)1, {a mathematical formula}DαL is weakly safe of type (b), while for every {a mathematical formula}(Dα,L)∈AdC(Tdl)2, {a mathematical formula}DαL is weakly safe of type (c). Moreover, for every {a mathematical formula}(Dα,L)∈AdC(Tdl)3, {a mathematical formula}DαL is irrelevant. In particular, {a mathematical formula}AdC(wk,Tdl)=AdC(Tdl)1∪AdC(Tdl)2.We want to use Corollary 97 to prove the invariance of this template. Assumptions (i) and (ii) are evident. We need to show property (iii), i.e. {a mathematical formula}Ad is pairwise relevant non-overlapping (see Definition 95). To this aim, we fix {a mathematical formula}AdC(T)⁎=AdC(wk,T) and we check that properties A, B, and C hold true.We note that if {a mathematical formula}(Dαi,Li),(Dαj,Lj)∈AdC(Tdl)1, properties (Ai) and (Bi) hold true. Indeed, {an inline-figure} and {an inline-figure} so that {a mathematical formula}{αist,αjst} and {a mathematical formula}{αiinv,αjst} are both {a mathematical formula}MLi,Lj-mutex. Instead, if {a mathematical formula}(Dαi,Li),(Dαj,Lj)∈AdC(Tdl)2, properties (Aiii) and (Biii) hold true. Indeed, {an inline-figure} and {an inline-figure} so that {a mathematical formula}{αiinv,αjend} and {a mathematical formula}{αiend,αjend} are {a mathematical formula}MLi,Lj-mutex. We now consider {a mathematical formula}(Dαi,Li)∈AdC(Tdl)1 and {a mathematical formula}(Dαj,Lj)∈AdC(Tdl)2. We have that {an inline-figure} so that {a mathematical formula}{αist,αjst} is non {a mathematical formula}MLi,Lj-executable. This yields property (Ai). We now prove property (Bii) for this pair. To this end, we note that {a mathematical formula}AC(T)irr⁎=AstC(Tdl)3∪AendC(Tdl)3 and we show that property (i) of Definition 93 holds true for {a mathematical formula}(αist,αjst). Indeed, {an inline-figure} and, on the other hand, if {a mathematical formula}(α,L)∈AC(T)irr⁎, {a mathematical formula}L∩Effα=∅ so that {an inline-figure} for every matching {a mathematical formula}M⊇MLi,L. This tells us that {a mathematical formula}(αist,αjst) is {a mathematical formula}(AC(T)irr⁎,Li,Lj)-unreachable. Finally, following an analogous argument, we can show that {a mathematical formula}{αjinv,αist} is non {a mathematical formula}MLi,Lj-executable so that property (Bi) holds for the pair {a mathematical formula}(Dαj,Lj),(Dαi,Li). Finally, the properties (C) are trivially verified since {a mathematical formula}AC(T)rel⁎=∅.TFD-IS does not reason about weakly safe actions of type (b) and (c) and, in consequence, does not produce the invariant {a mathematical formula}Tdl. The FD invariant synthesis would have a similar behaviour for the corresponding sequential domain.
      </paragraph>
     </section>
    </section>
    <section label="11">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Several approaches to invariant synthesis are available in the literature. In what follows, we present these approaches in depth by highlighting similarities and differences with our technique.
     </paragraph>
     <section label="11.1">
      <section-title>
       Previous work on synthesising temporal invariants
      </section-title>
      <paragraph>
       The invariant synthesis presented in Bernardini and Smith [6] represents a preliminary version of the technique described in this paper. Bernardini and Smith [6] lacks a rigorous presentation of the theoretical framework behind the synthesis of invariants. In addition, the algorithm does not capture all the cases in which unsafe intertwinements between durative actions can happen, which results in the generation of unsafe invariants that could be violated under some circumstances. For example, for the domain ZenoTravel (IPC'02), the algorithm classifies {a mathematical formula}Tzt=({〈fuel-level/2,1〉}) as an invariant. However, it can be shown that {a mathematical formula}Tzt is not an invariant because the schema refuel is weakly safe of type (b) and can give rise to dangerous intertwinements that can invalidate the invariant conditions.
      </paragraph>
     </section>
     <section label="11.2">
      <section-title>
       Fast downward and temporal fast downward
      </section-title>
      <paragraph>
       Helmert [33] presents a translation from a subset of PDDL2.2 into FDR (Finite Domain Representation), a multi-valued planning task formalism used within the planner Fast Downward [32]. The translation only handles non-temporal and non-numeric PDDL2.2 domains, the so-called “PDDL Level 1” (equivalent to STRIPS [19] with the extensions known as ADL [43]. One of the steps of this translation is the identification of mutual exclusion invariants and it is an extension of the technique presented in Edelkamp and Helmert [15] developed for STRIPS.
      </paragraph>
      <paragraph>
       When considering sequential domains, the invariant synthesis presented in this paper works similarly to Helmert's technique. In particular, both work at the lifted level, while all the other related techniques discussed below work at the ground level. Both techniques start from simple invariant candidates and check them against conditions that ensure invariance by analysing the structure of the action schemas in the domain. When a candidate is rejected, they both try to refine it to create a new stronger candidate, which is then checked from scratch.
      </paragraph>
      <paragraph>
       However, in contrast with our technique, Helmert's method considers a schema safe only when the weight transitions from one, to zero and back to one. Potentially safe transitions from zero to one are ignored. This simplified analysis results in the identification of a smaller set of invariants compared to our technique. For example, Helmert's invariant synthesis labels as unsafe all the action schemas that add a relevant formula without deleting that formula or another relevant one, even when the preconditions impose that the weight is zero when the action schema is applied. In this way, Helmert's invariant synthesis misses invariants that our technique is able to find (see Example 23).
      </paragraph>
      <paragraph>
       Chen et al. [10] builds on Helmert's invariant synthesis and his multi-valued domain formulation to synthesise long-distance mutual exclusions (londex), which capture constraints over actions and facts not only at the same time step but also across multiple steps. The londex has been successfully used in SAT-based planners to improve their performance. It is worth considering how the concept of londex can be extended to temporal domains.
      </paragraph>
      <paragraph>
       Within the context of Temporal Fast Downward (TFD) [18], a simple extension of Helmert's invariant synthesis is used to deal with temporal and numeric domains of the ICPs. See Section 10.2 for a description of this technique.
      </paragraph>
     </section>
     <section label="11.3">
      <section-title>
       Rintanen's invariant synthesis
      </section-title>
      <paragraph>
       An algorithm for inferring invariants in propositional STRIPS domains is proposed by Rintanen [45], [46]. It synthesises not only mutual-exclusion invariants, but also other types of invariants. The algorithm works on a ground representation of the domain and, starting from an inductive definition of invariants as formulae that are true in the initial state and are preserved by the application of every action, the algorithm is based on an iterative computation of a fix-point, which is useful for reasoning about all the invariants of a domain at the same time rather than inferring some invariants first and then using them for inferring others.
      </paragraph>
      <paragraph>
       Rintanen's algorithm uses a guess, check and repair approach but, unlike our technique, it starts from stronger invariant candidates and then progressively weakens them if they are not preserved by the actions. Thus, the repair phase starts by considering a less general invariant instead of a more general one. For example, let us consider the schema {a mathematical formula}σ=x≠y→P(x,y)∨Q(y,z) as a potential invariant (all the invariants considered have this implicative form). One of the weakening operation consists of identifying two variables. In this case, if z is set equal to x, the weaker candidate {a mathematical formula}σ=x≠y→P(x,y)∨Q(y,x) is obtained and checked.
      </paragraph>
      <paragraph>
       This technique has been successfully used within both Graphplan based planners [8], where it helps to identify unreachable subgoals, and SAT-based planners [39], where it can be useful to reduce the amount of search required. However, even though its implementation is limited to invariants involving two formulas at the most, it incurs a high performance penalty on large instances.
      </paragraph>
      <paragraph>
       Rintanen [47] extends the original algorithm presented in Rintanen [45], [46] in order to handle temporal domains. As in the original algorithm, the temporal one works on ground domains, not using a lifted representation at any stage. The format of the invariants found is {a mathematical formula}l1V(r)l2, where {a mathematical formula}l1 and {a mathematical formula}l2 are positive or negative ground facts, r is a floating point number, and the formula says that either {a mathematical formula}l1 is true or {a mathematical formula}l2 is true over the interval [{a mathematical formula}0..r] relative to the current time point. If {a mathematical formula}r=inf, the formula means that if {a mathematical formula}l1 is false, then {a mathematical formula}l2 will remain true forever. Since Rintanen's invariant synthesis exploits the initial conditions and the ground representation of the domain, it usually finds a broader range of invariants than our technique. However, this makes the invariant synthesis computationally costly. Reachability analysis on a ground representation of the planning instances is computationally very expensive, so while our algorithm takes a few seconds to run, Rintanen's synthesis requires tens of minutes to find invariants in several domains (see Table 1 in Rintanen [47]). In recent work, Rintanen [48] has proposed a hybrid algorithm that performs the basic invariance tests with a ground method, but grounds the actions and formulas only with respect to a smaller number of objects in order to reduce complexity.
      </paragraph>
      <paragraph>
       We do not directly compare our technique against Rintanen's algorithm in Section 10 because the two techniques aim to find different types of invariants (our focuses on mutual exclusion invariants, while Rintanen's tackles a broad range of invariant types) and they work on different representations of the problem (lifted versus ground). However, in what follows, we give examples of the output of Rintanen's technique for completeness.
      </paragraph>
      <paragraph>
       Consider the {a mathematical formula}Crewplanning domain (IPC'08 and IPC'11). For each crew member {a mathematical formula}ci, Rintanen's algorithm finds ground invariants of the type:{a mathematical formula} which means that if it is day {a mathematical formula}dj for the crew member {a mathematical formula}ci, it cannot be day {a mathematical formula}dk at the same time. If there are k days, this results in {a mathematical formula}k2 invariants for each crew member. All these invariants correspond to the single lifted invariant {a mathematical formula}current_day0[1] that is found by our invariant synthesis. For the same domain, however, Rintanen's algorithm finds additional invariants that express temporal relations between atoms. Our technique does not aim to find this type of invariant. For example, Rintanen's method finds temporal invariants of the form:{a mathematical formula} which means that, for the crew member {a mathematical formula}ci, the atom {a mathematical formula}done_meal in day {a mathematical formula}k+1 becomes true 255 time units after the atom {a mathematical formula}done_sleep was true in day k. In fact, in day k, {a mathematical formula}done_sleep is made true by the end effects of the action {a mathematical formula}sleep. From this time point, in order to make {a mathematical formula}done_meal true the day after {a mathematical formula}k+1, two actions need to be executed: {a mathematical formula}post_sleep, with duration 195, and {a mathematical formula}have_meal with duration 60, for a total time separation of 255 time units. For the {a mathematical formula}Crewplanning domain, the run time of our algorithm is 0.29 seconds, while Rintanen's algorithm has a runtime of 1 minute and 23.24 seconds for hard instances. This is actually one of the best run times, since for problems such as Parcprinter, Elevators, Sokoban, Transport-numeric and others, the algorithm has a run time of more than 4 hours. Given these run times, it does not seem plausible to use Rintanen's algorithm as a pre-processing step to improve search in planning, which is one of the most important uses of invariant synthesis algorithms.
      </paragraph>
     </section>
     <section label="11.4">
      <section-title>
       DISCOPLAN
      </section-title>
      <paragraph>
       DISCOPLAN (DIScovering State COnstraints for PLANning) [26] is a technique for generating invariants from the non-temporal PDDL Level 1 tasks. DISCOPLAN supports conditional effects without compiling them. DISCOPLAN discovers not only mutual exclusion invariants, but also other types of invariants: static predicates, simple implicative, (strict) single valuedness and n-valuedness, anti-simmetry, OR and XOR invariants.
      </paragraph>
      <paragraph>
       For mutual exclusion invariants, DISCOPLAN uses a guess, check and repair approach similar to our approach: a hypothetical invariant is generated by simultaneously analysing the preconditions and the effects of each action to see whether an instantiation of a literal is deleted whenever another instantiation of the same literal is added. Then, this candidate is checked against all the other actions and the initial conditions. If the hypothetical invariant is not found to be valid, then all the unsafe actions are collected together and a set of possible refinements are generated. However, whereas our technique tries to refine a candidate as soon as an unsafe action is found, DISCOPLAN tries to address all the unsafe causes at the same time while generating refinements. This approach leads to more informed choices on how to refine hypothetical invariants and can result in the identification of more invariants. However, it is more expensive from a computational point of view, which is why DISCOPLAN is often inefficient on big instances.
      </paragraph>
      <paragraph>
       DISCOPLAN can be used not only for finding invariants, but also for inferring action-variable domains. An action-variable domain is a set that includes all the objects that can be used to instantiate the variables of an action. Such sets of possible tuples of variables are found by forward propagation of ground atoms from the initial state. This technique is related to the reachability analysis performed by Graphplan [8], but does not implement mutual exclusion calculation.
      </paragraph>
      <paragraph>
       DISCOPLAN is usually used in combination with SAT encodings of planning problems. In particular, a pre-processing step is performed over the domain under consideration in order to find invariants and variable domains, then the domain as well as the invariants and the variable domains are translated into SAT. Finally, a SAT-based planner is used to solve the resulting translated domain. SAT-based planners [39], [37] show significant speed-up when invariants and action-variable domains are used.
      </paragraph>
     </section>
     <section label="11.5">
      <section-title>
       Type inference module
      </section-title>
      <paragraph>
       TIM (Type Inference Module) [20] uses a different approach for finding invariants in non-temporal PDDL Level 1 domains. More precisely, TIM is a pre-preprocessing technique for inferring object types on the basis of the actions and the initial state. Data obtained from this computation is then used for inferring invariants. TIM recognises four kinds of invariants:
      </paragraph>
      <list>
       <list-item label="1.">
        Identity invariants (for example, considering the domain {a mathematical formula}Blockworld, two objects cannot be at the same place at the same time);
       </list-item>
       <list-item label="2.">
        Unique state invariants (for example, every object must be in at most one place at any time point);
       </list-item>
       <list-item label="3.">
        State membership invariants (for example, every object must be in at least one place at any time point); and
       </list-item>
       <list-item label="4.">
        Resource invariants (for example, in a 3-blocks world, there are 4 surfaces).
       </list-item>
      </list>
      <paragraph>
       Invariants of types 1 and 2 correspond to mutual exclusion invariants. The invariants found by TIM have been exploited to improve the performance of the STAN planner [22].
      </paragraph>
     </section>
     <section label="11.6">
      <section-title>
       Knowledge representation and engineering
      </section-title>
      <paragraph>
       In addition to works that address the creation of invariants directly, there are works in the literature that highlight the importance of multi-valued state variables for debugging domain descriptions and for assisting the domain designer in building correctly encoded domains [20], [7], [13]. In particular, Cushing et al. [13] analyse well-studied IPC temporal and numeric domains and reveal several modelling errors that affect such domains. This analysis lead the authors to suggest better ways of describing temporal domains. They identify the direct specification of multi-valued state variables as a key feature for doing this, and show how this can help domain experts to write correct models.
      </paragraph>
      <paragraph>
       Other works in the literature use the creation of invariants and state variables as an intermediate step in the translation from PDDL to other languages. In particular, Huang et al. [37] introduce SASE, a novel SAT encoding scheme based on the SAS+ formalism [1]. The state variables (extracted from invariants) used by SASE play a key role in improving efficiency. Since our technique generates a broader set of invariants than related techniques, it results in SAS+ tasks with smaller sets of state variables. We speculate that this positively impact SAT-based planners that use an SASE encoding. Testing of this hypothesis is future work.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     PDDL2.1 specification of the Floortile domain
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix B">
     PDDL2.1 specification of the Depot domain
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix C">
     PDDL2.1 specification of the Rovers domain
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix D">
     PDDL2.1 specification of the DataProcessing domain
     <paragraph>
      {a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>