<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Asynchronous knowledge with hidden actions in the situation calculus.
   </title>
   <abstract>
    We present a powerful new account of multi-agent knowledge in the situation calculus and an automated reasoning procedure for knowledge queries. Existing accounts of epistemic reasoning in the situation calculus require that whenever an action occurs, all agents know that an action has occurred. This demands a level of synchronicity that is unreasonable in many multi-agent domains. In asynchronous domains, each agent's knowledge must instead account for arbitrarily-long sequences of hidden actions. By using a persistence condition meta-operator to augment traditional regression techniques, we show how agents can reason about their own knowledge using only their internal history of observations, rather than requiring a full history of the world. The result is a more robust and flexible account of knowledge in the situation calculus suitable for asynchronous, partially-observable multi-agent domains.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In their landmark paper Knowledge, Action, and the Frame Problem, Scherl and Levesque [45] incorporate knowledge-producing actions into the situation calculus [37], inheriting Reiter's solution to the frame problem [38] and so enabling use of the regression operator to reason about the changing knowledge of an agent. Extensions to multiple agents [48] and concurrent actions [44] have produced an expressive logic of knowledge, action and change in which regression provides an automated reasoning procedure
     </paragraph>
     <paragraph>
      While powerful, this formalism has a restriction that can make it unsuitable for modelling complex multi-agent domains. It requires that whenever an action occurs, all agents know that an action has occurred, demanding a level of synchronicity that is unreasonable in many multi-agent domains. If this restriction is lifted then each agent's knowledge must account for arbitrarily-long sequences of hidden actions [21], and proofs about knowledge must use a second-order induction axiom for quantifying over all future situations. This precludes the use of regression for automated reasoning. It also makes it difficult for agents to reason about their own knowledge, as they may not have enough information to formulate an appropriate query.
     </paragraph>
     <paragraph>
      We overcome this limitation by combining two elements – an explicit representation of an agent's local perspective and a persistence condition meta-operator – to formulate an account of knowledge in the situation calculus that can faithfully represent the hidden actions inherent in asynchronous domains while maintaining regression as a key tool for automated reasoning.
     </paragraph>
     <paragraph>
      To decouple knowledge from the specific actions that have occurred, we explicitly reify the local observations made by each agent, so that every situation corresponds to an agent-local view. An agent is said to know proposition ϕ if and only if ϕ is true in all situations matching its current view. Our work thus has strong parallels with the classic view-based account of knowledge of Halpern and Moses [15], but grounded in the situation calculus and with an emphasis on regression for automated reasoning. This work appeared in preliminary form in [17]; the current paper presents an expanded treatment including proofs, properties and application domains.
     </paragraph>
     <paragraph>
      The main challenge we overcome is developing regression rules that can handle arbitrarily long sequences of hidden actions. To ensure its knowledge is valid, an agent must reason about all future situations that are compatible with its observations. Such universal quantification over situation terms requires a second-order induction axiom, which the standard regression operator cannot handle. In previous work we have developed the persistence condition operator to handle this induction as a meta-level fixpoint calculation [19]. Using this operator to augment the regression techniques developed by Scherl and Levesque [45], we maintain their elegant solution to the frame problem while handling arbitrarily long sequences of hidden actions.
     </paragraph>
     <paragraph>
      The formulation is shown to respect basic intuitions about how knowledge should behave, and to preserve important properties of the agent's epistemic state through the occurrence of actions. Moreover, it is elaboration tolerant, automatically preserving these properties in the face of more complex information-producing actions, such as the guarded sensing actions of [32], that can be tricky to axiomatize correctly in existing formalisms.
     </paragraph>
     <paragraph>
      Decoupling knowledge from action in this manner makes it easy to express varying degrees of observability, from actions that are public through to ones that are completely hidden. To illustrate, we present a running example based on the well-known “Hunt the Wumpus” domain [41] which has been previously used to demonstrate the interleaved sensing and action typical of realistic domains in the situation calculus [42]. Our variant is complicated by the presence of multiple agents and partial observability of actions:
     </paragraph>
     <list>
      <list-item>
       Ann and Bob are hunting a Wumpus in a dungeon with many interconnecting rooms. They can fully observe each other's actions if they are in the same room, can hear each other's actions from adjacent rooms, and have no other means of synchronisation.
      </list-item>
      <list-item>
       Like any Wumpus, this one does not move, causes a stench in all adjacent rooms, and if shot will emit a piercing scream that can be heard anywhere in the dungeon.
      </list-item>
      <list-item>
       Can Ann and Bob coordinate their knowledge and actions in order to find and shoot the Wumpus?
      </list-item>
     </list>
     <paragraph>
      The possibility of hidden actions makes this domain difficult to represent, let alone reason about, in standard theories of knowledge in the situation calculus. Our approach offers a straightforward formulation and an automated reasoning procedure.
     </paragraph>
     <paragraph>
      Further demonstrating the utility of our approach, we show how the new regression rules can be applied using an agent's individual view, rather than requiring a full situation term. Agents can thus use our techniques to reason about their own knowledge using only their local information, making the formalism suitable both for reasoning about, and for reasoning in, rich multi-agent domains.
     </paragraph>
     <paragraph>
      The end result is a significantly more general and robust theory of knowledge in the situation calculus that still permits an automated reasoning procedure. There is a large body of work that could benefit from our formalism, including: specification and verification of multi-agent systems [52]; theories of coordination [13] and ability [22]; reasoning about the epistemic feasibility of plans [23]; analysing multi-player games [1]; and our own work on the computation of complex epistemic modalities [18] and the cooperative execution of Golog programs [16].
     </paragraph>
     <paragraph>
      The paper now proceeds with a review of the standard account of multi-agent knowledge in the situation calculus, before treating the individual knowledge of each agent in the face of hidden actions. We develop the axioms for our new observation-based account of knowledge in Section 3 and develop a regression rule for our formalism using the persistence condition operator in Section 4. Potential applications are shown in Section 5, where we show how our approach to axiomatising observations overcomes several difficulties encountered in previous formulations. An illustrative example of its use for reasoning about a partially-observable domain is provided in Section 6.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      Our work utilises the situation calculus [28], [37] with multiple agents [48] and concurrent actions [40], and we begin from the standard account of knowledge due to Scherl and Levesque [45]. Several conservative extensions to the standard situation calculus meta-theory are also employed: the Poss predicate is subsumed by a general class of action description predicates; the unique names axioms for actions are subsumed by a general background theory; reasoning is performed using the single-step regression operator along with a new reasoning tool called the persistence condition operator [19].
     </paragraph>
     <paragraph>
      There are of course a wide range of related formalisms for reasoning about knowledge, action and change, which we do not directly consider in this paper. We find the notation and meta-theory of the situation calculus particularly suitable for expressing our main ideas. Moreover, the strong underlying similarities between the major action formalisms should allow these ideas to transcend the specifics of the situation calculus [46], [53], [54].
     </paragraph>
     <section label="2.1">
      <section-title>
       The situation calculus for multiple agents
      </section-title>
      <paragraph>
       The situation calculus is a many-sorted language of first-order logic augmented with a second-order induction axiom. Its has the following sorts: Agent terms represent the agents operating in the world; Action terms are functions denoting individual instantaneous events that can cause the state of the world to change, with the initiating agent indicated by their first argument; Concurrent terms are non-empty, finite sets of actions that occur simultaneously; Situation terms are histories of the actions that have occurred in the world, with the initial situation represented by {a mathematical formula}S0 and successive situations built using the function {a mathematical formula}do:Concurrent×Situation→Situation; Object terms represent any other object in the domain. Fluents are predicates or functions that represent properties of the world that may change between situations; they take a situation term as their final argument.
      </paragraph>
      <paragraph>
       We follow standard naming conventions for the situation calculus: lower-case Roman names indicate variables; upper-case Roman names indicate constants; Greek letters indicate meta-variables and meta-operators; macros are presented in bold face; all axioms universally close over their free variables. The connectives ∧, ¬, ∃ are taken as primitive, with ∨, →, ≡, ∀ defined in the usual manner. The name s is used for variables of sort Situation, a for sort Action, c for sort Concurrent, agt for sort Agent and x for sort Object. The notation {a mathematical formula}x¯ indicates a vector of terms of context-appropriate sort and arity.
      </paragraph>
      <paragraph>
       Some example statements from the “Hunt the Wumpus” domain are “Initially everyone is in the first room of the dungeon, R1” and “Bob is not in room R1 after moving to room R2”. Written formally:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The dynamics of a particular domain are captured by a set of sentences called a basic action theory. Queries about the behaviour of the world are posed as logical entailment queries relative to this theory.
      </paragraph>
      <paragraph label="Definition 1">
       Basic action theoryA basic action theory, denoted {a mathematical formula}D, is a set of situation calculus sentences (of the specific syntactic form outlined below) describing a particular dynamic world. It consists of the following disjoint sets: the foundational axioms of the situation calculus (Σ); action description axioms defining various aspects of action performance, such as preconditions ({a mathematical formula}Dad); successor state axioms describing how primitive fluents change between situations ({a mathematical formula}Dssa); axioms describing the value of primitive fluents in the initial situation ({a mathematical formula}DS0); and axioms describing the static background facts of the domain ({a mathematical formula}Dbg):{a mathematical formula}
      </paragraph>
      <paragraph>
       These axioms must satisfy some simple consistency criteria to constitute a valid domain description; see [37] for details. This is a conservative extension of the definition used by Pirri and Reiter, designed to accommodate our forthcoming extensions.
      </paragraph>
      <paragraph>
       The uniform formulae can be thought of as properties of the state of the world, and are basically logical combinations of fluents referring to a common situation term. The meta-variable ϕ is used to refer to an arbitrary uniform formula. For the moment we restrict ourselves to objective uniform formulae; the complete definition includes statements about knowledge and will be introduced in the next section.
      </paragraph>
      <paragraph label="Definition 2">
       Uniform termsLet σ be a fixed situation term, r an arbitrary rigid{sup:1} function symbol, f an arbitrary fluent function symbol, and x a variable that is not of sort Situation. Then the terms uniform in σ are the smallest set of syntactically-valid terms satisfying:{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 3">
       Objective uniform formulaeLet σ be a fixed situation term, R an arbitrary rigid predicate, F an arbitrary primitive fluent predicate, τ an arbitrary term uniform in σ, and x an arbitrary variable that is not of sort Situation. Then the objective formulae uniform in σ are the smallest set of syntactically-valid formulae satisfying:{a mathematical formula}
      </paragraph>
      <paragraph>
       Since they represent properties of the world, it is often useful to evaluate uniform formulae at several different situation terms, and to suppress the situation terms in order to simplify the presentation. The notation {a mathematical formula}ϕ[s′] represents a uniform formula in which all fluents have their situation argument replaced with the particular situation term {a mathematical formula}s′, while {a mathematical formula}ϕ−1 represents a uniform formula with the situation argument removed from all its fluents.
      </paragraph>
      <paragraph>
       The axiom set {a mathematical formula}Dbg contains all the static background facts about the domain. It must include: the definitions for sets and set membership; unique names axioms to ensure that action terms with different names or different arguments are in fact different; and the function {a mathematical formula}actor(a) giving the agent performing an action, which is always the action's first argument. It may also contain domain-specific background facts, such as situation-independent formulae or simple state invariants.
      </paragraph>
      <paragraph>
       The axiom set {a mathematical formula}Dssa contains one successor state axiom for each primitive fluent in the domain, providing a monotonic solution to the frame problem for that fluent. These axioms have the following general form:{a mathematical formula}
      </paragraph>
      <paragraph>
       Here {a mathematical formula}ΦF+ and {a mathematical formula}ΦF− are formulae uniform in s. This may be read as “F is true after performing c if c made it true, or it was previously true and c did not make it false”.
      </paragraph>
      <paragraph>
       The axiom set {a mathematical formula}Dad defines fluents that describe various aspects of the performance of an action, which we call action description predicates. The precondition predicate {a mathematical formula}Poss(c,s) is the canonical example, indicating whether it is possible to perform a set of actions c in a given situation s. In principle there can be any number of predicates or functions defined in a similar way – forthcoming examples include the sensing-result function SR and the observability predicate CanObs. The meta-predicate α will denote an arbitrary action description predicate. For each such predicate the set {a mathematical formula}Dad contains a single axiom of the following form, where {a mathematical formula}Πα is uniform in s:{a mathematical formula}
      </paragraph>
      <paragraph>
       Note that this is a departure from the standard approach of Pirri and Reiter [37] where a separate axiom specifies the preconditions for each individual action type. The single-axiom approach used in this paper embodies a domain-closure assumption on the Action sort. It is necessary when reasoning about formulae that universally quantify over actions [43], [58], and is assumed to appropriately axiomatise any interactions that may occur between primitive actions when they are performed concurrently [36].
      </paragraph>
      <paragraph>
       For convenience we will allow action description predicates to be defined in terms of other action description predicates; as long as these definitions are well-founded they can be expanded out to a definition that uses only uniform formulae.
      </paragraph>
      <paragraph>
       The foundational axioms Σ capture axiomatically the intuition that situations are finite sequences of actions. There are initial situations identified by the predicate {a mathematical formula}Init(s), with a distinguished initial situation {a mathematical formula}S0 called the actual initial situation. Other initial situations are used to represent the agents' epistemic uncertainty, and will be discussed in the following section. Situations in general form a tree structure with an initial situation at the root and {a mathematical formula}do(c,s) constructing the successor situation resulting when the actions c are performed in s; all situations thus produced are distinct:{a mathematical formula}
      </paragraph>
      <paragraph>
       We abbreviate the performance of several successive actions by writing:{a mathematical formula}
      </paragraph>
      <paragraph>
       There is also a second-order induction axiom asserting that all situations must be constructed in this way, which is needed to prove statements that universally quantify over situations [39]:{a mathematical formula}
      </paragraph>
      <paragraph>
       The root of a situation is the initial situation from which it was constructed:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The relation {a mathematical formula}s⊏s′ indicates that {a mathematical formula}s′ is in the future of s and is defined as follows:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Here {a mathematical formula}s⊑s′ is the standard abbreviation for {a mathematical formula}s⊏s′∨s=s′. This notation for “in the future of” can be extended to consider only those futures in which all actions satisfy a particular action description predicate. We include a relation {a mathematical formula}&lt;α(x¯) for each action description predicate {a mathematical formula}α(x¯,c,s), with the following definitions:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Note that we suppress the action and situation arguments to the action description predicate in order to simplify the presentation. For notational simplicity we will henceforth leave any additional arguments {a mathematical formula}x¯ implicit, writing just {a mathematical formula}&lt;α for a generic relation of this kind.
      </paragraph>
      <paragraph>
       For example, by stating that {a mathematical formula}s&lt;Posss′ we assert that not only is {a mathematical formula}s′ in the future of s, but that all actions performed between s and {a mathematical formula}s′ were actually possible; this is equivalent to the &lt; operator of Pirri and Reiter [37] in the sense that the legal situations are those in which every action performed was actually possible:{a mathematical formula}
      </paragraph>
      <paragraph>
       Finally, the axiom set {a mathematical formula}DS0 describes the state of the world before any actions are performed. It is a collection of sentences uniform in {a mathematical formula}S0 stating what holds in the actual initial situation. The initial knowledge of each agent is also captured in these axioms, as described in the next section.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Knowledge and sensing
      </section-title>
      <paragraph>
       Epistemic reasoning was first introduced to the situation calculus by Moore [29], and formalised extensively by Scherl and Levesque [45] whose paper is now the canonical reference for these techniques. Their work has been extended to include concurrent actions [44] and multiple agents [48].
      </paragraph>
      <paragraph>
       The semantics of knowledge are based on a reification of the “possible worlds” semantics of modal logic, using situation terms rather than abstract worlds. A special fluent {a mathematical formula}K(agt,s′,s) is used to indicate that “in situation s, the agent agt considers the alternate situation {a mathematical formula}s′ to be possible”. The macro Knows is then defined as a shorthand for the standard possible-worlds definition of knowledge, stating that an agent knows ϕ when ϕ is true in all situations considered possible:{a mathematical formula}
      </paragraph>
      <paragraph>
       The foundational axioms Σ define a special fluent {a mathematical formula}K0(agt,s′,s) that is used to model the initial epistemic uncertainty of the agents, with {a mathematical formula}DS0 containing sentences of the form {a mathematical formula}Knows0(agt,ϕ,S0) to specify what is initially known{sup:2}:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The action description function {a mathematical formula}SR(a,s) specifies the sensing result returned by a when executed in situation s. For non-sensing actions the value of SR is an arbitrary constant. The dynamics of knowledge are then specified by an additional set of axioms.
      </paragraph>
      <paragraph label="Definition 4">
       We will denote by {a mathematical formula}DKstd the axioms of the standard account of knowledge due to Scherl and Levesque [45], as detailed in Eqs. (2), (3) below:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Eq. (2) ensures that the agents begin with their knowledge as specified by {a mathematical formula}DS0. Eq. (3) takes the form of a standard successor state axiom for the K fluent. It ensures that {a mathematical formula}s″ is considered a possible alternative to {a mathematical formula}do(c,s) when {a mathematical formula}s″ is the result of doing the same actions c in a situation {a mathematical formula}s′ that is considered a possible alternative to s. It must furthermore have been possible to perform those actions in {a mathematical formula}s′, and the sensing results must match for each action that was carried out by the agent in question. Thus an agent's knowledge after an action occurs is completely determined by its knowledge before the action, and the sensing results from the action.
      </paragraph>
      <paragraph>
       Scherl and Levesque [45] show how the Knows macro can be treated syntactically as if it were a primitive fluent, allowing it to appear as part of a uniform formula for the purposes of reasoning. We can now present the complete definition of a uniform formula, which may contain statements about knowledge:
      </paragraph>
      <paragraph label="Definition 5">
       Uniform formulaeLet σ be a fixed situation term, let τ, {a mathematical formula}τ1 and {a mathematical formula}τ2 be arbitrary terms uniform in σ and x an arbitrary variable that is not of sort Situation. Then the formulae uniform in σ are the smallest set of syntactically-valid formulae satisfying:{a mathematical formula}
      </paragraph>
      <paragraph>
       While powerful, this knowledge-representation formalism has an important limitation: it is fundamentally synchronous. Each agent is assumed to have full knowledge of all actions that have occurred – in other words, all actions are public. While suitable for some domains, there are clearly many multi-agent domains where achieving total awareness of actions would be infeasible. A major contribution of this paper is a more flexible formalism for knowledge that can be applied to a much wider range of domains.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Reasoning and regression
      </section-title>
      <paragraph>
       One of the attractions of the situation calculus is the existence of automated reasoning procedures for certain types of query. These are generally based on syntactic manipulation of a query into a form that is more amenable to reasoning – for example, because it can be proven without using some of the axioms from {a mathematical formula}D.
      </paragraph>
      <paragraph>
       In the general case, answering a query about a basic action theory {a mathematical formula}D is a theorem-proving task in second-order logic (denoted SOL) due to the induction axiom included in the foundational axioms. This is clearly problematic for automated reasoning, but fortunately there exist particular syntactic forms for which some of the axioms in {a mathematical formula}D are not required [37]. In particular, queries about the initial situation can be answered using only first-order logic (FOL) and a limited set of axioms:{a mathematical formula}
      </paragraph>
      <paragraph>
       By making a closed-world assumption over {a mathematical formula}DS0∪Dbg, logic programming environments such as Prolog can be used to handle this type of query quite effectively [38]. Automated reasoning depends on transforming queries into more easily-handled forms such as this.
      </paragraph>
      <paragraph>
       The principle tool for automated reasoning in the situation calculus is the regression meta-operator {a mathematical formula}RD, a syntactic manipulation that encodes the preconditions and effects of actions into the query itself, meaning fewer axioms are needed for the final reasoning task [37]. The idea is to reduce a query about some future situation to a query about the current situation only.
      </paragraph>
      <paragraph>
       Regression is only defined for a certain class of formulae, the regressable formulae.
      </paragraph>
      <paragraph label="Definition 6">
       Regressable termsLet σ be an arbitrary situation term, x an arbitrary variable not of sort situation, r an arbitrary rigid function and f an arbitrary fluent function. Then the regressable terms are the smallest set of syntactically-valid terms satisfying:{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 7">
       Regressable formulaeLet σ be an arbitrary situation term, x an arbitrary variable not of sort situation, ν an arbitrary regressable term, R an arbitrary rigid predicate, F an arbitrary primitive fluent predicate, α an arbitrary action description predicate and c a set of actions. Then the regressable formulae are the smallest set of syntactically-valid formulae satisfying:{a mathematical formula}
      </paragraph>
      <paragraph>
       Regressable formulae are more general than uniform formulae. In particular, they can contain action description predicates and may mention different situation terms. They cannot, however, quantify over situation terms or compare situations using a {a mathematical formula}≤α relation.
      </paragraph>
      <paragraph>
       The regression operator is then defined using a series of regression rules such as those shown below, which mirror the structural definition of regressable formulae.
      </paragraph>
      <paragraph label="Definition 8">
       Regression operatorLet R be a rigid predicate, α be an action description predicate with axiom {a mathematical formula}α(ν¯,c,s)≡Πα(c,s) in {a mathematical formula}Dad, and F be a primitive fluent with axiom {a mathematical formula}F(x¯,s)≡ΦF(x¯,s) in {a mathematical formula}Dssa. Then the regression of ϕ, denoted {a mathematical formula}RD(ϕ), is defined according to the following structural rules:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       We have omitted some technical details here, such as the handling of functional fluents; consult [37] for the details. The key point is that each application of the regression operator replaces action description predicates with their definitions from {a mathematical formula}Dad and primitive fluents with their successor state axioms from {a mathematical formula}Dssa, “unwinding” a single action from each {a mathematical formula}do(c,σ) term in the query. Situation terms not constructed using do are left unchanged.
      </paragraph>
      <paragraph>
       Since {a mathematical formula}D is fixed, we will henceforth drop the subscript and simply write {a mathematical formula}R for the regression operator. When dealing with situation-suppressed uniform formulae, we will use a two-argument operator {a mathematical formula}R(ϕ,c) to indicate the regression of ϕ over the action c. It should be read as a shorthand for {a mathematical formula}R(ϕ[do(c,s)])−1 using the situation-suppression operator from Section 2.1.
      </paragraph>
      <paragraph>
       Repeated applications of this operator, denoted by {a mathematical formula}R⁎, can transform a query about some future situation into a query about the initial situation only. This is typically easier to answer as it requires fewer axioms from the theory, as shown in [37]. The axioms {a mathematical formula}Dad and {a mathematical formula}Dssa are essentially “compiled into” the query. The trade-off is that the length of the regressed query may be exponential in the length of ϕ. While an efficiency gain is not guaranteed, regression has proven a very effective technique in practice [24] and there are techniques to avoid exponential growth of the query in some cases [57].
      </paragraph>
      <paragraph>
       A key contribution of Scherl and Levesque [45] was showing how to apply the regression operator to formulae containing the Knows macro, allowing it to be treated syntactically as if it were a primitive fluent. This means that epistemic queries can be approached using standard reasoning techniques of the situation calculus. Although we have changed the notation somewhat to foreshadow the techniques we will develop in Section 3, their definition operates as follows.
      </paragraph>
      <paragraph>
       First, we introduce a notational convenience for pairing an action with its corresponding sensing result:
      </paragraph>
      <paragraph label="Definition 9">
       Action#Result PairAn action#result pair, denoted a#r, represents an Action term a and a corresponding Result term r as might be returned from the sensing-result function {a mathematical formula}r=SR(a,s). We require unique-names axioms for the pairing operator:{a mathematical formula}We will use the special Result term Nil as the sensing result for non-information-producing actions.
      </paragraph>
      <paragraph>
       We then define the results of a concurrent action to be the set of action#result pairs for all primitive actions performed by the agent in question.{a mathematical formula}
      </paragraph>
      <paragraph>
       This definition can be used to formulate a regression rule (denoted {a mathematical formula}R(SL) to distinguish it from our subsequent rule) as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       This works by collecting the sensing results from each action performed by the agent into the set y, then ensuring matching sensing results in every situation considered possible. It expresses the knowledge of the agent after a concurrent action in terms of what it knew before the action, along with the information returned by the action. This technique relies heavily on the fact that all actions are public, since it requires every agent's knowledge to be updated in response to every action.
      </paragraph>
      <paragraph>
       Repeated applications of {a mathematical formula}R can thus transform a knowledge query into one that is uniform in the initial situation. While it would be valid to then expand the Knows macros and handle the query using first-order logic, in practice the reasoning procedure would leave Knows intact and use a specialised prover based on modal logic.
      </paragraph>
      <paragraph>
       It is possible to formulate an alternate successor state axiom for knowledge that does not assume all actions are public, such as that of Lespérance et al. [21]. Such formulations invariably require universal quantification over situation terms, to account for arbitrarily-long sequences of hidden actions. This is incompatible with regression rules like the above, and these formulations offer no reasoning procedure other than general second-order theorem proving. By utilising a new reasoning technique called the persistence condition to factor out this universal quantification, our work is the first to provide an account of knowledge with hidden actions while maintaining regression in the style presented above as an effective reasoning tool.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Property persistence and the persistence condition
      </section-title>
      <paragraph>
       Queries that universally quantify over situation terms are often in a simple syntactic form called property persistence queries [19]. Such queries assert that a uniform formula ϕ holds in a given situation, and will continue to hold as long as all future actions satisfy some action description predicate α:{a mathematical formula}
      </paragraph>
      <paragraph>
       In [19] we developed the persistence condition meta-operator {a mathematical formula}PD(ϕ,α) to handle such queries more effectively. It is a meta-level fixpoint calculation producing a uniform formula such that:{a mathematical formula}
      </paragraph>
      <paragraph>
       As with regression, we will use the simpler notation {a mathematical formula}P(ϕ,α) and leave {a mathematical formula}D implicit. We briefly describe its operation below since we will need some details for a worked example; for a full treatment see our previous work [19].
      </paragraph>
      <paragraph>
       First, the one-step-persistence operator {a mathematical formula}P1 is defined to assert that ϕ holds in s and all its immediate successors:{a mathematical formula}
      </paragraph>
      <paragraph>
       Repeated application asserts persistence after greater numbers of actions:{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively {a mathematical formula}P(ϕ,α) should be a fixpoint of {a mathematical formula}P1(ϕ,α), and indeed it can be shown that:{a mathematical formula}
      </paragraph>
      <paragraph>
       The calculation of {a mathematical formula}P(ϕ,α) thus replaces a second-order reasoning task with a fixpoint search, using iterated first-order reasoning against the background theory. This is in contrast to the regression operator, which is a purely syntactic transformation, and so it comes with two important caveats: the fixpoint {a mathematical formula}P(ϕ,α) may not exist at all, or it may be impossible to calculate within finitely many iterations.
      </paragraph>
      <paragraph>
       Nevertheless, our experience has shown this technique to be useful in practice, thanks to the relative simplicity of the axioms in {a mathematical formula}Dbg. Claßen and Lakemeyer [4] have also had success with a similar approach in a modal variant of the situation calculus know as {a mathematical formula}ES, where they study fixpoint properties of non-terminating Golog programs.
      </paragraph>
      <paragraph>
       Our paper [19] discusses several restricted domains in which a terminating calculation of {a mathematical formula}P(ϕ,α) can be guaranteed, including finite domains (which can be reduced to propositional logic) and certain kinds of context-free domains (which can be shown to have a finite state-space). We shall have more to say on the effectiveness of this technique in Section 4.
      </paragraph>
      <paragraph>
       The important point is that {a mathematical formula}P(ϕ,α) allows one to factor out certain kinds of universally-quantified queries, dealing with them via special-purpose meta-level reasoning machinery, and reducing them to a uniform formula that can then be approached via standard regression techniques.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Observations, views and knowledge
     </section-title>
     <paragraph>
      Existing accounts of knowledge in the situation calculus directly express the dynamics of knowledge update in terms of the actions that have occurred, as seen in Section 2.2. This works well when agents can be assumed to have full knowledge of the actions that have been performed, but quickly becomes cumbersome when trying to allow for hidden actions. In this Section we first develop a principled axiomatisation of the observability of actions, then build a powerful yet succinct axiomatisation of knowledge upon it.
     </paragraph>
     <paragraph>
      The basic idea is as follows: each occurrence of an action results in an agent making a set of observations. Every situation then corresponds to a local view for that agent: the sequence of all its observations, excluding cases where the set of observations was empty. An agent knows something if it is true in all situations matching its current view. Decoupling knowledge in this manner makes it easy to express various degrees of observability of actions, from public actions through to actions that are completely hidden.
     </paragraph>
     <paragraph>
      The direct coupling between knowledge and action also has undesirable implications for situated agents reasoning about their own knowledge. As a consequence of using regression to handle knowledge queries, one can only reason about knowledge if one has a situation term rooted in {a mathematical formula}S0, as the required query is:{a mathematical formula}
     </paragraph>
     <paragraph>
      In asynchronous domains with hidden actions, where agents are not necessarily aware how many actions have been performed, the agents cannot use this formulation to reason about their own knowledge. Since knowledge is directly coupled to actions, and hence to situation terms, they cannot construct the appropriate query.
     </paragraph>
     <paragraph>
      Our approach will allow this kind of query to be posed in terms of an agent's local view, rather than requiring a full situation term, allowing them to reason about their own knowledge using only their local information
     </paragraph>
     <section label="3.1">
      <section-title>
       Observations and views
      </section-title>
      <paragraph>
       To remove the direct coupling between knowledge and actions, we introduce an explicit notion of observations. These are internal notifications that agents receive when an action has occurred. By expressing knowledge in terms of observations rather than actions, we ensure that agents can always reason about their own knowledge based on their own internal history of observations.
      </paragraph>
      <paragraph label="Definition 10">
       An observation is a notification event received by an agent, making it aware of some change in the state of the world. When an agent receives such a notification, we may say that it “observed”, “made” or “perceived” that observation.
      </paragraph>
      <paragraph>
       Since the state of the world may only change in response to some action, observations can only be made as a result of some action. For simplicity we assume that agents perceive observations instantaneously, i.e. in the same instant as the actions that cause them.
      </paragraph>
      <paragraph>
       Since “observation” is quite a loaded term, it is worth re-iterating this point: observations are instantaneous events generated internally by each agent in response to actions occurring in the world. We make no commitment as to how these events are generated, preferring a clean delineation between the task of observing change and the dynamics of knowledge update based on those observations. As with the work of Scherl and Levesque [45], we consider change-awareness to be the responsibility of a lower-level component of the agent's control software.
      </paragraph>
      <paragraph>
       To make this idea concrete, let us introduce an additional sort Observations to the language of the situation calculus, for the moment without any particular commitment towards what this sort will contain. We then add to {a mathematical formula}Dad an axiom for the action description function Obs:{a mathematical formula} This function returns a finite set of observations, and should be read as “when actions c are performed in situation s, agent agt will perceive o”. Using a set of observations allows an agent to perceive any number of observations in response to an action occurrence – perhaps several observations, perhaps none. When {a mathematical formula}Obs(agt,c,s) is the empty set (denoted ∅) then the agent makes no observations and the actions c are completely hidden.
      </paragraph>
      <paragraph>
       The concept of a view follows naturally, it is the sequence of all the observations made by an agent as the world evolves.
      </paragraph>
      <paragraph label="Definition 11">
       ViewsAn agent's view in a given situation, s, is the corresponding sequence of observations made by the agent as a result of each action in s, excluding those actions for which no observations were made.
      </paragraph>
      <paragraph>
       We introduce another sort Views consisting of sequences of finite sets of observations. Using ϵ to represent the empty sequence and ⋅ to prepend a new element to a sequence,{sup:3} the functional fluent View is defined as follows to give the history of observations associated with a particular situation:{a mathematical formula}
      </paragraph>
      <paragraph>
       Observations and views can be seen as localised analogues of actions and situations respectively. An action is a global event that causes the state of the world to change, while an observation is an internal event that causes an agent's knowledge of the state of the world to change. Similarly, a situation represents a complete, global history of all the actions that have occurred in the world, while a view is an agent's local history of all the observations it has made. The situation is an omniscient perspective on the world, the view a local perspective. This distinction is fundamental to developing a truly general multi-agent semantics for knowledge, as we shall see.
      </paragraph>
      <paragraph>
       The axiomatisation of Obs will depend on the particulars of the domain being modelled, and we make no commitment beyond requiring it to be formulated as an action description predicate. Under the common assumption that all actions are public, it may be as simple as defining:{a mathematical formula}
      </paragraph>
      <paragraph>
       With sensing actions included, Obs may be extended to include Action#Result pairs so that:{a mathematical formula}
      </paragraph>
      <paragraph>
       For an asynchronous domain where all actions are private, Obs may instead be defined to include only the actions of the agent in question:{a mathematical formula}
      </paragraph>
      <paragraph>
       We will discuss some more detailed axiomatisations for Obs in Section 5. The main point, as we shall see, is that the particular axiomatisation of Obs does not affect the general axioms and behaviour of knowledge.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Knowledge
      </section-title>
      <paragraph>
       It is a basic tenet of epistemic reasoning that an agent's knowledge at any particular time must depend solely on its local history: the knowledge that it started out with combined with the observations it has made since then [15]. Given an explicit account of the observations made by each agent, the required semantics of the K relation are clear: {a mathematical formula}K(agt,s′,s) must hold whenever {a mathematical formula}s′ is legal, both s and {a mathematical formula}s′ would result in the same view for the agent, and s and {a mathematical formula}s′ are rooted at K-related initial situations:{a mathematical formula}
      </paragraph>
      <paragraph>
       In essence, this is a direct encoding into the situation calculus of the definition of knowledge in classical epistemic reasoning [30], [15], [10].
      </paragraph>
      <paragraph>
       While a wonderfully succinct definition of how knowledge should behave, this formulation cannot be used directly in a basic action theory. The dynamics of fluent change must be specified by a successor state axiom, expressing K at {a mathematical formula}do(c,s) in terms of K at situation s. We must formulate a successor state axiom for the K fluent which enforces the equivalence in Eq. (6).
      </paragraph>
      <paragraph>
       For notational convenience, let us first introduce an action description predicate PbU (for “possible but unobservable”) indicating that the actions c are possible in s, but no observations will be made by agt if they occur:{a mathematical formula}
      </paragraph>
      <paragraph>
       By stating that {a mathematical formula}s≤PbU(agt)s′, we assert that agt would make no observations were the world to move from situation s to {a mathematical formula}s′. This means that the agent's view in both situations would be identical, so if it considers s possible then it must also consider {a mathematical formula}s′ possible. Following this intuition, we propose the following successor state axiom to capture the desired dynamics of the knowledge fluent:{a mathematical formula}
      </paragraph>
      <paragraph>
       This axiom considers two independent cases, depending on whether the actions c produced any observations. The cases are illustrated in Fig. 1 and Fig. 2 respectively.
      </paragraph>
      <paragraph>
       Fig. 1 shows the case where {a mathematical formula}Obs(agt,c,s)=∅ and the actions c are hence totally unobservable. In this case the agent's state of knowledge does not change – the situations considered possible in {a mathematical formula}do(c,s) are precisely those considered possible in s.
      </paragraph>
      <paragraph>
       Fig. 2 shows the case where {a mathematical formula}Obs(agt,c,s)≠∅ and hence the actions c produce some observations o. In this case the agent considers possible any legal successor to a possible alternate situation {a mathematical formula}s′ that can be brought about by actions {a mathematical formula}c′ yielding identical observations. Actions that would not produce matching observations do not produce K-related situations. Crucially, the agent also considers possible any future of {a mathematical formula}do(c′,s′) that could be reached through a sequence of unobservable actions.
      </paragraph>
      <paragraph>
       To reiterate: unlike the standard successor state axiom from Eq. (3), our approach requires agents to consider any possible future situation in which they would make no further observations. This requirement is fundamental to the correct specification of knowledge in asynchronous domains.
      </paragraph>
      <paragraph>
       It remains to specify K in the initial situation. The relation {a mathematical formula}K0 defines knowledge before any actions have occurred, but the agents must consider the possibility that some hidden actions have occurred. In other words, we must include situations where {a mathematical formula}root(s)≤PbU(agt)s in the K-relation for initial situations. We therefore propose the following axiom:{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 12">
       We will denote by {a mathematical formula}DKobs the axioms for our new observation-based semantics for knowledge, as detailed in Eqs. (8), (9) above.
      </paragraph>
      <paragraph>
       These axioms suffice to ensure that knowledge behaves as we require: two situations will be related by {a mathematical formula}K(agt,s′,s) if and only if they result in identical views for that agent, {a mathematical formula}s′ is legal, and their root situations were initially related:
      </paragraph>
      <paragraph label="Theorem 1">
       For any agent agt and situations s and{a mathematical formula}s″:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof sketch">
       For the if direction we show how to construct an {a mathematical formula}s′ satisfying the {a mathematical formula}∃s′ parts of Eqs. (8), (9). For the only-if direction we establish each of the three conjuncts individually. The root case is trivial since Eq. (8) always expresses {a mathematical formula}K(s″,do(c,s)) in terms of {a mathematical formula}K(s′,s), while Eq. (9) relates K for initial situations back to {a mathematical formula}K0. The Legal case relies on the fact that PbU implies Poss, while the View case relies on the fact that {a mathematical formula}s≤PbUs′→View(s)=View(s′). For the complete proof, see Appendix C.  □
      </paragraph>
      <paragraph>
       Using this new formulation, an agent's knowledge is completely decoupled from the global notion of actions, instead depending only on the local information that it has observed. Of course, this must be combined with a specific axiomatisation of how the Obs function behaves. We detail a variety of axiomatisations in Section 5, and our account of knowledge is directly applicable to all of them.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Properties of knowledge
      </section-title>
      <paragraph>
       As a demonstration of the correctness of their axioms, Scherl and Levesque [45] prove five properties of their formalism: that knowledge-producing actions have only knowledge-producing effects; that unknown fluents remain unknown by default; that knowledge incorporates the results of sensing actions; that known fluents remain known by default; and that agents have knowledge of the effects of their actions.
      </paragraph>
      <paragraph>
       However, the intuition behind these properties depends heavily on the assumption of public actions and on the separation of actions into two classes: knowledge-producing actions that only return sensing information, and ordinary actions that only affect the state of the world. In asynchronous multi-agent domains, these restrictions cannot be meaningfully applied.
      </paragraph>
      <paragraph>
       For example, it is entirely possible that a knowledge-producing action and an ordinary action are performed concurrently by two different agents, so the results of a sensing action might immediately be made invalid. Moreover, suppose that an agent performs an action to make a formula ϕ true, but there is a series of hidden actions that could subsequently make ϕ false. The agent cannot meaningfully claim to know ϕ, since it could become false without updating the local view of that agent.
      </paragraph>
      <paragraph>
       The proofs used in [45] all hinge on showing that the situations K-related to {a mathematical formula}do(a,s) are precisely the “correct” ones, where correctness is formulated in terms of the preconditions and effects of a. We claim that in our formulation, the “correct” situations to be related to {a mathematical formula}do(c,s) are precisely those that are legal and have the same view, and the validity of Theorem 1 provides sufficient justification for the correctness of our knowledge axioms.
      </paragraph>
      <paragraph>
       Indeed, it can be shown that our formulation is strictly equivalent to the standard account of Scherl and Levesque [45] when all actions are public. Let each agent observe all actions, as well as the sensing results of actions that they themselves perform:{a mathematical formula}
      </paragraph>
      <paragraph>
       Our new account of knowledge will then behave identically to the standard account:
      </paragraph>
      <paragraph label="Theorem 2">
       Suppose{a mathematical formula}Dadcontains Eq.(10)as its definition of the Obs function, then for any legal situation terms σ and{a mathematical formula}σ′:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       Eq. (10) means that {a mathematical formula}Obs(agt,c,s) cannot be empty for {a mathematical formula}c≠∅, so {a mathematical formula}s≤PbU(agt)s′ iff {a mathematical formula}s=s′. Since we restrict our attention to legal situations, we can substitute ⊥ for {a mathematical formula}Obs(agt,c,s)=∅ and ⊤ for {a mathematical formula}Obs(agt,c,s)≠∅ into Eqs. (8), (9) to obtain the following:{a mathematical formula}{a mathematical formula}Which further simplifies to:{a mathematical formula}{a mathematical formula}Using Eq. (10), it is straightforward to show that:{a mathematical formula} Eqs. (11), (12) are therefore equivalent to Eqs. (2), (3) from {a mathematical formula}DKstd, meaning that K behaves the same under both theories.  □
      </paragraph>
      <paragraph>
       Having established that our account subsumes the standard “public actions” account of knowledge, we can also show that it maintains many of its desirable properties in the general case. One of the fundamental results in [45] is that if the initial knowledge relation {a mathematical formula}K0 is reflexive, symmetric, transitive or Euclidean, then the K relation has these properties for any situation. In our formalism, such preservation of accessibility properties follows immediately from Theorem 1 and the reflexive, symmetric, transitive and Euclidean nature of the equality operator.
      </paragraph>
      <paragraph label="Theorem 3">
       If the{a mathematical formula}K0relation is restricted to be reflexive, transitive, symmetric or Euclidean, then the K relation defined by{a mathematical formula}DKobswill satisfy the same restrictions at every legal situation.
      </paragraph>
      <paragraph label="Proof">
       Each follows directly from Theorem 1 and the properties of equality. We will take the transitive case as an example; the rest are virtually identical.Suppose that {a mathematical formula}K0 is transitive, and we have legal situations {a mathematical formula}s1, {a mathematical formula}s2, {a mathematical formula}s3 such that {a mathematical formula}K(agt,s2,s1) and {a mathematical formula}K(agt,s3,s2). Then by Theorem 1 we have the following:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} From the transitivity of {a mathematical formula}K0 we can conclude that {a mathematical formula}K0(agt,root(s3),root(s1)) and from the transitivity of equality we can conclude that {a mathematical formula}View(agt,s1)=View(agt,s3). Since {a mathematical formula}s3 is restricted to be legal, we have enough to satisfy the RHS of the equivalence in Theorem 1, so {a mathematical formula}K(agt,s3,s1) and K is therefore transitive.  □
      </paragraph>
      <paragraph>
       That these properties hold regardless of the axiomatisation of Obs is a compelling argument in favour of our approach. Certain kinds of sensing actions can easily invalidate these properties if not axiomatised carefully under the standard account, such as the guarded sensing actions of [32]. We will explore this case in detail in Section 5.
      </paragraph>
      <paragraph>
       Our formalism is not only a proper generalisation of the standard account of knowledge in the situation calculus, it is an elaboration tolerant generalisation. It maintains important general properties of knowledge as more complex models of sensing and observability are introduced.
      </paragraph>
      <paragraph>
       One problem remains: the successor state axiom for K in Eq. (8) is incompatible with standard regression techniques. The right-hand side is not a regressable formula, as the {a mathematical formula}≤PbU(agt) component universally quantifies over situation terms. A similar problem prevented the development of a regression rule in [21]. In the following section we will use the persistence condition operator to formulate a regression rule that can handle these arbitrarily-long sequences of hidden actions.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Reasoning about knowledge
     </section-title>
     <paragraph>
      For our new account of knowledge to be useful in practice, we must extend the standard techniques for automated reasoning in the situation calculus to handle the modified formalism – that is to say, we must provide a regression rule for Knows.
     </paragraph>
     <section label="4.1">
      <section-title>
       Regressing knowledge queries
      </section-title>
      <paragraph>
       The appearance of {a mathematical formula}≤PbU(agt) in Eq. (8) means that our new successor state axiom universally quantifies over situations, so the regression technique developed in [45] cannot be used directly. We must appeal to the persistence condition meta-operator introduced in Section 2.4 to handle the inductive component of this reasoning, by transforming the quantification into a uniform formula so that standard regression techniques can be applied.
      </paragraph>
      <paragraph>
       We propose the following as the regression rule for Knows under our formalism:{a mathematical formula}
      </paragraph>
      <paragraph>
       Note the similarity to the standard regression rule for knowledge from Eq. (4). New in our version are: the replacement of the res macro with an explicit definition of what the agent has observed; explicit handling of the case when the agent makes no observations; and use of the persistence condition to account for arbitrarily-long sequences of hidden actions.
      </paragraph>
      <paragraph>
       As required for a regression rule, Eq. (13) reduces a knowledge query at {a mathematical formula}do(c,s) to a knowledge query at s. It is also intuitively appealing: to know that ϕ holds, the agent must know that in all situations that agree with its observations, ϕ cannot become false without it making some further observation. This is the meaning of {a mathematical formula}P(ϕ,PbU(agt)) in the above, to state that “if ϕ were to become false, I would notice”.
      </paragraph>
      <paragraph>
       We must also specify a regression rule for Knows in the initial situation, as Eq. (9) also uses the {a mathematical formula}≤PbU(agt) ordering. This clause produces an expression in {a mathematical formula}Knows0 at {a mathematical formula}S0, meaning that it can be handled by epistemic reasoning about the initial situation only:{a mathematical formula}
      </paragraph>
      <paragraph>
       The use of {a mathematical formula}P here is similar to its use in the previous regression rule. The use of {a mathematical formula}R(…[S0])−1 ensures that the transform is applied recursively to any nested knowledge formulae – when the enclosed formula ϕ does not contain nested knowledge macros, regressing it at {a mathematical formula}S0 and suppressing the situation term leaves it unchanged.
      </paragraph>
      <paragraph>
       Assuming that {a mathematical formula}P can be calculated as described in Section 2.4, these regression rules provide a sound and complete procedure for reducing queries about knowledge to queries about the initial knowledge of the agents:
      </paragraph>
      <paragraph label="Theorem 4">
       Given a basic action theory{a mathematical formula}Dand a uniform formula ϕ for which{a mathematical formula}P(ϕ,PbU(agt))exists:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof Sketch">
       By induction on situation terms. In the {a mathematical formula}do(c,s) case, we proceed by expanding the definition for Knows using our new successor state axiom for K, collecting sub-formulae that match the form of the Knows macro, and using regression and the persistence condition to render the resulting expressions uniform in s. In the base case, we apply the persistence condition to an expansion of Knows at {a mathematical formula}S0 to produce the desired result. For the complete proof, see Appendix C.  □
      </paragraph>
      <paragraph>
       These regression rules thus enable us to handle knowledge queries in our formalism using a standard regression-based approach, with the persistence condition operator allowing us to “factor out” the inductive component of the reasoning.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Regression over views
      </section-title>
      <paragraph>
       While this regression rule is suitable for modelling and simulation purposes, it would be unreasonable for a situated agent to ask “do I know ϕ in the current situation?” using the situation calculus query {a mathematical formula}D⊨Knows(agt,ϕ,σ). As discussed in Section 3, an agent cannot be expected to have the full current situation σ. It will however have its current view v and can construct a query about its own knowledge as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Such a query universally quantifies over situations and so cannot be handled using regression. It is also not in a form amenable to the persistence condition operator.
      </paragraph>
      <paragraph>
       However, we should expect from Theorem 1 that the quantification over situations is unnecessary in this case – after all, any situation with the same view for that agent should result in it having the same knowledge. Let us explicitly define knowledge with respect to a view as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       We can then modify the regression rules in Eqs. (13), (14) to work directly on formulae of this form. The resulting rules are actually simpler than for regression over situations, as there are no empty observations in a view. The result is:{a mathematical formula}{a mathematical formula} Using regression in this way, an agent can reduce the query {a mathematical formula}Knows(agt,ϕ,v) to an equivalent query about its knowledge in the initial situation.
      </paragraph>
      <paragraph label="Theorem 5">
       Given a basic action theory{a mathematical formula}Dand a uniform formula ϕ for which{a mathematical formula}P(ϕ,PbU(agt))exists:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof Sketch">
       The proof hinges on a simple corollary of Theorem 1: that situations with the same root and same view entail the same knowledge:{a mathematical formula} We can then proceed by induction over views. For the ϵ and {a mathematical formula}o⋅v cases we split on whether there exists a situation having that view. If no such situation exists, we show that the regression rules (15), (16) generate a formula that is vacuously true, as an invalid view causes anything to be known. If such a situation does exist, we select an arbitrary witness and demonstrate that rules (15), (16) generate an equivalent formula to rules (13), (14) using that witness. By the above corollary, this is enough to establish equivalence for any such situation. For the complete proof, see Appendix C.  □
      </paragraph>
      <paragraph>
       Our formalism thus allows agents to reason about their own knowledge using only their local information, even in asynchronous domains where they do not know how many actions have been performed.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Reasoning in practice
      </section-title>
      <paragraph>
       It is worth re-iterating that our regression rules are no longer straightforward syntactic transformations – rather, they involve a fixpoint calculation to generate {a mathematical formula}P(ϕ,PbU(agt)). Our previous work on the persistence condition meta-operator [19] discussed the advantages of this approach in detail, but its primary advantage is to make automated reasoning approachable at all – the alternative is second-order theorem proving against the full theory {a mathematical formula}D.
      </paragraph>
      <paragraph>
       Section 6 demonstrates our technique in action, answering multi-agent knowledge queries in a purely mechanical fashion. We have also completed a preliminary implementation of our technique in Prolog, using a modal variant of the {a mathematical formula}LeanTAP theorem prover [3], [11] as its core reasoning engine, and have verified its operation on several simple domains, including some of the Hunt the Wumpus examples presented in Section 6. More details of the domains and examples are available along with the implementation.{sup:4}
      </paragraph>
      <paragraph>
       At a high level, we replace a single second-order theorem-proving task:{a mathematical formula}
      </paragraph>
      <paragraph>
       With iterated first-order reasoning to calculate the persistence condition:{a mathematical formula}
      </paragraph>
      <paragraph>
       Followed by first-order reasoning about the initial situation only:{a mathematical formula}
      </paragraph>
      <paragraph>
       We thus “factor out” the components of the reasoning process, allowing each to be treated in isolation. The inductive aspects are handed by property persistence, and the dynamic aspects are handled by regression, leaving just static epistemic reasoning in the target domain. Each may be more or less challenging depending on the target domain, and each may be studied and improved in isolation.
      </paragraph>
      <paragraph>
       The problem of performing possible-worlds reasoning in the initial situation has received considerable attention in the literature [32], as has the general problem of full epistemic reasoning about unrestricted forms of nested knowledge in {a mathematical formula}Kn[14]. Since our approach has these challenges in common with the standard account from [45], we will not discuss them further here.
      </paragraph>
      <paragraph>
       Our insistence on considering “all possible future actions” introduces an additional challenge not faced by the standard account – the calculation of {a mathematical formula}P may be very complex, and is not guaranteed to terminate in the general case. Our previous work identified several classes of basic action theory in which the persistence condition can be computed [19], and we will review some specific examples below.
      </paragraph>
      <paragraph>
       Since decidability results for the most general reasoning tasks in the situation calculus are known to be rather rare, recent approaches frequently seek to restrict action theories in an appropriate way to achieve termination, depending upon the problem domain. Importantly, our approach is compatible with a range of existing techniques, facilitated by our first-order representation used for answering property persistence queries.
      </paragraph>
      <paragraph>
       We consider below three classes of action theory in which {a mathematical formula}P(ϕ,PbU(agt)) is guaranteed to be calculable.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        Synchronous action theories
       </section-title>
       <paragraph>
        An important sanity-check for our approach is that is does not introduce additional complexity for purely synchronous domains.
       </paragraph>
       <paragraph label="Definition 13">
        Synchronous action theoryA basic action theory {a mathematical formula}D is synchronous if every agent observes something whenever an action occurs:{a mathematical formula}
       </paragraph>
       <paragraph>
        It is straightforward to show that {a mathematical formula}P(ϕ,PbU(agt)) in synchronous domains is always equivalent to ϕ. The regression rules in Eqs. (13), (14) then reduce to purely syntactic manipulations:
       </paragraph>
       <paragraph label="Theorem 6">
        Let{a mathematical formula}Dsyncbe a synchronous basic action theory, then:{a mathematical formula}
       </paragraph>
       <paragraph label="Proof">
        By definition, we have:{a mathematical formula}Recall from Eq. (7) that:{a mathematical formula}So clearly:{a mathematical formula}The definition of {a mathematical formula}P1(ϕ,PbU(agt)) will then produce:{a mathematical formula}The calculation of {a mathematical formula}P thus terminates immediately at the first iteration, giving {a mathematical formula}P(ϕ,PbU(agt)) equal to {a mathematical formula}P1(ϕ,PbU(agt)), which is equivalent to ϕ as desired.  □
       </paragraph>
       <paragraph>
        We thus do not introduce unnecessary complications for domains in which effective reasoning procedures already exist, while extending the reach of our formalism into richer domains where some inductive reasoning is required.
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Propositional action theories
       </section-title>
       <paragraph>
        For domains in which all non-situation sorts are finite, reasoning about uniform formulae can be reduced to propositional logic and is therefore strongly decidable. Calculating the persistence condition is also decidable in this case – since the domain has a finite state-space, the fixpoint calculation operates over a complete well-founded lattice and is therefore guaranteed to terminate [19].
       </paragraph>
       <paragraph>
        The Scherl and Levesque [45] account of knowledge has been shown to admit to an optimal decision procedure and regression algorithm by integrating observation actions and modal knowledge operators into a dynamic epistemic logic encoding [57].
       </paragraph>
       <paragraph>
        There are advantages to maintaining the expressive power of first-order logic, even when the domain can be propositionalized, as the use of quantifiers and free variables can produce exponentially-shorter formulae and hence lead to shorter proofs.
       </paragraph>
      </section>
      <section label="4.3.3">
       <section-title>
        Context-free action theories
       </section-title>
       <paragraph>
        Suppose that the theory of action is context free[27]. In such theories successor state axioms have the following form:{a mathematical formula} The effects of an action are thus independent of the situation in which it is performed. Quantification is still permitted, provided the quantifiers only range over the situation-independent formulae.
       </paragraph>
       <paragraph>
        Lin and Levesque [25, Lemma 6.2] show that context-free theories with a finite number of parameterless actions have a finite state space. This is therefore sufficient to ensure a terminating computation of persistence condition, {a mathematical formula}P, in the same manner as propositional domains [19].
       </paragraph>
       <paragraph>
        Context free theories capture the expressivity of the usual formation of classical planning problems encoded in STRIPS, with add and delete lists, in which every action is considered to be context-free, as identified in [25].
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Approximate reasoning
      </section-title>
      <paragraph>
       Rather than restricting the domain to guarantee terminating calculation of {a mathematical formula}P(ϕ,PbU(agt)), it is also possible to restrict the form of queries so that it can be pre-calculated offline. This kind of approximate reasoning about knowledge is key to the formalism of Demolombe and del Pilar Pozos Parra [9], in which knowledge is limited to be about fluent literals only.
      </paragraph>
      <paragraph>
       Their basic idea is to introduce, for each fluent F in the domain, two additional fluents {a mathematical formula}Kagt+F and {a mathematical formula}Kagt−F to explicitly represent “agt knows F” and “agt knows ¬F”. By formulating ordinary successor state axioms for these fluents, literal-level knowledge can be reasoned about using standard regression and does not require an explicit possible-worlds K-relation. The trade-off is that this approach cannot represent indeterminate disjunctive knowledge such as “agt knows F or G”.
      </paragraph>
      <paragraph>
       The Demolombe and del Pilar Pozos Parra approach has been formally related to the standard Scherl and Levesque approach by Petrick and Levesque [31]. They show there is an equivalence between the two approaches when an agent's knowledge is restricted to be disjunctive, so that the following holds:{a mathematical formula}
      </paragraph>
      <paragraph>
       In [32] this equivalence is extended to cover existential quantification by restricting knowledge to also satisfy the following:{a mathematical formula} These disjunctive properties of knowledge are not entailed by a general possible-worlds style theory in the tradition of [45], although there are restrictions that can be placed on the theory in order to enforce them [33], [32].
      </paragraph>
      <paragraph>
       Even when these disjunctive knowledge properties are not enforced by the domain, they permit a sound approximation of knowledge that can be reasoned about more tractably than the standard possible-worlds account. Following the style of [31] we can provide the following definitions:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       A knowledge query is split across the logical operators until we are left with only knowledge of fluent literals, which is then handled using our formalism. If we assume a finite number of fluents, then we can use our regression rule for knowledge to pre-calculate an explicit successor state axiom for {a mathematical formula}KnowsA(agt,F,s) and {a mathematical formula}KnowsA(agt,¬F,s), allowing them to be treated as primitive fluents and reasoned about at run-time using purely syntactic transformations.
      </paragraph>
      <paragraph>
       Unlike the approach of Demolombe and del Pilar Pozos Parra [9] in which knowledge fluents must be axiomatised separately from the concrete fluents they describe, the approach suggested here would allow a successor state axiom for literal-level knowledge to be derived from the dynamics of the domain. The calculation of {a mathematical formula}P(F,PbU(agt)) for each fluent could be performed once, offline, and then used directly for approximate reasoning about knowledge.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Axiomatising observations
     </section-title>
     <paragraph>
      We now show how observations and views can be used to model a variety of common domain dynamics from the situation calculus literature. We argue that these axiomatisations intuitively capture the “correct” information in each case, and show how our explicit representation of the agent's local perspective can overcome difficulties encountered in previous formulations.
     </paragraph>
     <section label="5.1">
      <section-title>
       Public actions
      </section-title>
      <paragraph>
       In Section 3 we showed how public actions can be easily captured using the following axiom for Obs (reproduced from Eq. (10)):{a mathematical formula}
      </paragraph>
      <paragraph>
       It should be clear that these definitions capture the intuition behind the most common model of action observability, and indeed Section 3 formally proved an equivalence to the standard knowledge axioms of [45].
      </paragraph>
      <paragraph>
       This approach clearly leads to synchronous domains, since an agent's set of observations can only be empty if the set of actions is also empty, and the empty action set is never legal to perform.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Private actions
      </section-title>
      <paragraph>
       Private actions can be easily modelled by the following definition of Obs:{a mathematical formula}
      </paragraph>
      <paragraph>
       As noted by Lespérance et al. [21], private actions mean that agents need to consider arbitrarily-long sequences of hidden actions which may or may not have occurred, and standard regression techniques are insufficient to handle this case. By explicitly formalising this situation, we are able to provide an approach to effective automated reasoning in such asynchronous domains.
      </paragraph>
      <paragraph>
       Private actions also serve to demonstrate the elaboration tolerance of our approach. Consider the successor state axiom for knowledge with hidden actions that is formulated in [21]:{a mathematical formula}
      </paragraph>
      <paragraph>
       While the axiom seems intuitively plausible, it has a subtle problem: an agent's knowledge can change in response to actions performed by others. Suppose that agt has just performed action {a mathematical formula}a1, so the world is in situation {a mathematical formula}do(a1,s). Another agent then performs the action {a mathematical formula}a2, leaving the world in situation {a mathematical formula}do(a2,do(a1,s)). Since it is not aware of the occurrence of {a mathematical formula}a2, the knowledge of agt should be unchanged between these two situations. This is not the case under the formulation of [21], which introduces arbitrarily-long sequences of hidden actions into the past of the possible situation {a mathematical formula}s″. Based on our explicit formalisation of the agent's local view, our axiom includes hidden actions in the future of {a mathematical formula}s″ and avoids this unintuitive behaviour.
      </paragraph>
      <paragraph>
       By explicitly formalising the notion of a view, Theorem 1 guarantees that our formulation will avoid subtle problems such as this.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Guarded sensing actions
      </section-title>
      <paragraph>
       Petrick [32] extends the approach of [45] to include guarded sensing actions. These actions cause the agent to learn that some formula ϕ holds, but only if an additional guard formula ψ also holds in the world. They are introduced by modifying the successor state axiom for K as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       Petrick [32] demonstrates that this modified successor state axiom is no longer guaranteed to preserve the symmetry of the K fluent, invalidating one of the fundamental properties of knowledge. The problem is that although the agent will learn ϕ if the guard ψ is true, it cannot conclude that the guard was false by virtue of not learning ϕ. Since the agent's local perspective is only modelled implicitly, it has no way of detecting that the action failed to produce its sensing result.
      </paragraph>
      <paragraph>
       To ensure that symmetry is preserved through action, it is necessary to axiomatise these sensing actions in such a way that the status of the guard formula itself also becomes known. This is achieved in [32] through special syntactic restrictions, but our approach of explicitly representing the observations made by each agent avoids this problem automatically.
      </paragraph>
      <paragraph>
       To model guarded sensing actions in our framework, one would leave K unchanged and instead modify the definition of Obs to add guard conditions Ψ as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       For example, an action {a mathematical formula}senseϕ,ψ that senses the truth of some formula ϕ when the guard condition ψ is true would require something like the following to be entailed by the definition of Obs:{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       An agent using our formalism can therefore explicitly conclude, by virtue of not receiving a sensing result from {a mathematical formula}senseϕ,ψ, that the guard condition must not hold. This is sufficient to maintain symmetry of the knowledge accessibility relation as guaranteed by Theorem 3.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Speech acts
      </section-title>
      <paragraph>
       Communication in the situation calculus is traditionally modelled using explicit communicative actions or “speech acts” [50], [49]. These actions are axiomatised as per standard actions, but special-case handling is introduced in the axioms for knowledge in order to model their communicative effects.
      </paragraph>
      <paragraph>
       Instantaneous communication is modelled using actions such as inform, where {a mathematical formula}inform(agts,agtr,ϕ) means the sender {a mathematical formula}agts informs the receiver {a mathematical formula}agtr of the truth of some formula ϕ. If we assert that only truthful speech acts are allowed, and all actions are publicly observable, then this requires no further axiomatisation:{a mathematical formula}
      </paragraph>
      <paragraph>
       The inform action will be included in each agent's observations whenever it occurs, from which the agent can conclude that it was possible and thus that the contained formula holds in the world.
      </paragraph>
      <paragraph>
       However, this simple approach can lead to third-party agents being aware of what was communicated, which is often undesirable. In [50] encrypted speech acts are introduced to overcome this limitation, ensuring that only the intended recipient of a message is able to access its contents by performing a special decrypt action. While it would be straightforward to copy this approach in our formalism, the problem it was introduced to solve no longer exists – we can directly limit the accessibility of the message contents adding another type of observation, {a mathematical formula}inform(agts,agtr), that indicates the occurrence of the action but not its contents:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Here all agents will observe that the communication occurred, but only the sender and recipient can observe the contents of the message.
      </paragraph>
      <paragraph>
       Non-instantaneous communication can be modelled using a message queue for each agent with separate send and check actions [21]. The send action adds a message to the queue, while the check action returns the details of pending messages as its sensing result. Since this approach uses the standard sensing-result machinery, it requires no special axiomatisation here.
      </paragraph>
     </section>
     <section label="5.5">
      <section-title>
       Explicit observability axioms
      </section-title>
      <paragraph>
       Our approach offers a straightforward way to explore the middle ground between the two extremes of “public actions” and “private actions” discussed above. To axiomatise general partial observability of actions, we introduce a new action description predicate {a mathematical formula}CanObs(agt,a,s) that defines the conditions under which agent agt would observe action a being performed in situation s. If {a mathematical formula}CanObs(agt,a,s) is false, then that action will be hidden. We can then define Obs as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       This permits a great deal of flexibility in the axiomatisation. In our Hunt the Wumpus domain, agents are aware of all the actions performed in the same room as themselves:{a mathematical formula}
      </paragraph>
      <paragraph>
       It is also possible to allow partial observability of sensing results using an analogous predicate {a mathematical formula}CanSense(agt,a,s) and the following definition of Obs:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       For example, consider an agent waiting for a train who activates a speaker to determine when it will arrive. The results of this sensing action would provide information to any other agent within earshot:{a mathematical formula}
      </paragraph>
      <paragraph>
       We feel that this formulation provides a good balance between simplicity and expressiveness; it allows the observability of actions to vary according to the state of the world, but provides agents with a complete description of each action that they are capable of observing.
      </paragraph>
     </section>
     <section label="5.6">
      <section-title>
       Observability interaction
      </section-title>
      <paragraph>
       Reasoning about observability of concurrent actions raises the potential for observability interaction, in which some actions produce different observations when they are performed concurrently with another action. Like the precondition interaction problem for Poss, which has undergone extensive research and is discussed in [36], [34], [35], we assume that the axiom defining Obs contains the appropriate logic to handle such interaction. A simple axiomatisation might have actions being “masked” by the co-occurrence of another action, and would appear like so:{a mathematical formula}
      </paragraph>
      <paragraph>
       The important point is that, given an explicit account of the local perspective of each agent, such interaction can be axiomatised independently of the rest of the action theory.
      </paragraph>
     </section>
     <section label="5.7">
      <section-title>
       Observing the effects of actions
      </section-title>
      <paragraph>
       In many domains it would be infeasible for an agent to observe all of the details of a particular action when it occurs, but it may observe some of the effects of that action. For example, suppose that an agent monitors the state of a light in its environment, such that it notices it changing from dark to light. While it knows that some action must have occurred to produce that effect, it may not be sure precisely what action took place (e.g. precisely who turned on the light). This can be modelled by further extending the Observation sort to contain a special “effect observation” term lightCameOn, and axiomatising like so:{a mathematical formula}
      </paragraph>
      <paragraph>
       When the light is switched on, each agent's observation set will contain the term lightCameOn, and they will be able to deduce that this change has occurred without necessarily knowing the specific action responsible for the change. This is similar to the “fluent change” actions proposed by De Giacomo et al. [6], but embedded in the theory itself rather than generated by the agent when it discovers that it must update its beliefs.
      </paragraph>
     </section>
     <section label="5.8">
      <section-title>
       Delayed communication
      </section-title>
      <paragraph>
       Delayed communication can be modelled using separate send and recv actions. However, unlike the use of explicit communication channels discussed previously, we do not want the receiving agent to have to poll the message queue. Rather, the recv action should occur automatically some time after the send action.
      </paragraph>
      <paragraph>
       This is easily modelled using natural actions as defined by Reiter [40], actions that occur automatically at a particular time. By making recv a natural action, {a mathematical formula}send/recv pair can be axiomatised mirroring the standard account of long-running tasks in the situation calculus. A fluent {a mathematical formula}PendMsg(s,r,m,t). indicates that some message is pending and will be delivered at time t. We have:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       A send action thus causes the message to become pending, with its delivery time determined by the functional fluent delay. Once the delay time has elapsed, the natural action recv will be triggered and the message delivered. The send and recv actions are observed only by the sender and receiver respectively.
      </paragraph>
      <paragraph>
       If the agents have incomplete information about the delay function, this could easily model domains in which the message delay is unpredictable or even unbounded, giving asynchronous communication in the style of [15].
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      An illustrative example
     </section-title>
     <paragraph>
      We now give a brief demonstration of our formalism in action, using it to model the “Hunt The Wumpus” domain outlined in Section 1. Our variant is complicated by the presence of multiple hunters and partial observability, but we also simplify it by omitting common features such as pits and breezes. The full axiomatisation is available in Appendix A.
     </paragraph>
     <paragraph>
      We take as a static background fact the predicate {a mathematical formula}Adjacent(r,r′) defining the layout of the dungeon, as shown in Fig. 3. Since it is part of {a mathematical formula}Dbg, the layout is known to all agents.
     </paragraph>
     <paragraph>
      The actions of interest in the domain are {a mathematical formula}move(agt,r) by which agents may move between adjacent rooms, {a mathematical formula}shoot(agt,r) by which an agent may shoot into an adjacent room, and {a mathematical formula}alert(agt) by which agents may alert each other to the presence of a stench in their current room.
     </paragraph>
     <paragraph>
      The fluents of interest are the function {a mathematical formula}r=Loc(agt,s) giving the current room each agent is in, {a mathematical formula}r=Wumpus(s) giving the room containing the Wumpus, {a mathematical formula}Stench(r,s) indicating whether a room contains a stench, and {a mathematical formula}Killed(s) indicating whether the Wumpus has been killed.
     </paragraph>
     <paragraph>
      We have the following precondition axioms:{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Along with the following successor state axioms:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Note that Wumpus and Stench do not vary, but they must be fluents to allow for agents having partial knowledge of these facts. They are related by the following background theory axiom, stating that only rooms adjacent to the Wumpus have a stench:{a mathematical formula}
     </paragraph>
     <paragraph>
      This is a simple state invariant that, if true initially, is implied for all situations by the successor state axioms above. Typical approaches would discard such invariants after encoding their effects into the successor state axioms, as in [26]. We keep it as part of the background theory since it is useful when calculating the persistence condition; see Appendix B for a detailed treatment.
     </paragraph>
     <paragraph>
      For Observation terms we include all actions along with the following: footsteps indicating movement of an agent in an adjacent room, alert indicating an announcement by an agent in an adjacent room, stench as a sensing result when moving into a stench-filled room, and scream to indicate the death of the Wumpus. They are axiomatized as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The hunters know their initial state, being located in room R1 where there is no Wumpus and no stench:{a mathematical formula}{a mathematical formula} The Wumpus is in room R5, but this is not known to the agents. It is a fact about the actual initial situation rather than all possible initial situations:{a mathematical formula} The agents have no additional knowledge about the state of the dungeon.
     </paragraph>
     <paragraph>
      The following are examples of knowledge queries that can be posed in our formalism, a brief explanation of their outcome, and a demonstration of how they can be answered using our new regression rules.
     </paragraph>
     <paragraph label="Example 1">
      Initially, Ann does not know where the wumpus is:{a mathematical formula}
     </paragraph>
     <paragraph>
      Intuitively: it is given that {a mathematical formula}¬∃r:Knows0(A,Wumpus()=r,S0), and there is no sequence of hidden actions that could result in her learning the location of the wumpus.
     </paragraph>
     <paragraph>
      Formally: we answer the query by regressing it to produce a query about her initial knowledge {a mathematical formula}Knows0:{a mathematical formula}
     </paragraph>
     <paragraph>
      The calculation of this persistence condition is trivial since the location of the wumpus cannot change, so the fixpoint search terminates after a single iteration:{a mathematical formula} Which gives:{a mathematical formula}
     </paragraph>
     <paragraph>
      The nested regression of {a mathematical formula}Wumpus(r) at {a mathematical formula}S0 leaves the formula unchanged. The query thus regresses to the following, which is entailed by the domain:{a mathematical formula}
     </paragraph>
     <paragraph label="Example 2">
      Bob knows that the wumpus is not in an adjacent room, since he knows there is no stench in room R1.{a mathematical formula} It is therefore safe for him to move to an adjacent room.
     </paragraph>
     <paragraph>
      Regressing as in the previous example gives the equivalent query:{a mathematical formula}
     </paragraph>
     <paragraph>
      All initial situations have {a mathematical formula}¬Stench(R1) and the background theory has {a mathematical formula}Adjacent(R2,R1), {a mathematical formula}Adjacent(R4,R1), and the axiom relating a stench to an adjacent wumpus. All initial situations thus have no Wumpus in rooms adjacent to R1, so the regressed query is entailed by the domain.
     </paragraph>
     <paragraph label="Example 3">
      After Bob moves into room R2, he knows that it has a stench.{a mathematical formula}
     </paragraph>
     <paragraph>
      The move action causes Bob to receive a stench observation, and since a room's stenchiness cannot change, he can be sure the stench persists after any hidden actions.
     </paragraph>
     <paragraph>
      Formally, we regress over the move action like so:{a mathematical formula}
     </paragraph>
     <paragraph>
      Since this domain has a finite number of possible observations, we can expand the “∃o” clause into a finite disjunction. Indeed there are only two possible values for {a mathematical formula}Obs(B,{move(B,R2)},s), corresponding to the room having or not having a stench:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Stench(R2,s)≡Obs(B,{move(B,R2)},s)={move(B,R2),stench}
      </list-item>
      <list-item label="•">
       {a mathematical formula}¬Stench(R2,s)≡Obs(B,{move(B,R2)},s)={move(B,R2)}
      </list-item>
     </list>
     <paragraph>
      Expanding and replacing each observation with its preconditions yields:{a mathematical formula}
     </paragraph>
     <paragraph>
      The domain entails {a mathematical formula}Stench(R2,S0) so we can simplify the other option away, leaving:{a mathematical formula}
     </paragraph>
     <paragraph>
      The persistence condition calculation again terminates after one iteration:{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      So the query further simplifies to:{a mathematical formula}
     </paragraph>
     <paragraph>
      Since this domain has a finite number of possible actions, we can expand the “{a mathematical formula}∀c′” clause into a finite conjunction – indeed, the only value of {a mathematical formula}c′ that can produce those observations is {a mathematical formula}{move(B,R2)}. Substituting it and its action description predicates Poss and Obs gives:{a mathematical formula} This tautology is clearly entailed by the domain.
     </paragraph>
     <paragraph label="Example 4">
      Ann learns that Bob is in room R2 by observing Bob's move.{a mathematical formula}
     </paragraph>
     <paragraph>
      Ann observes {a mathematical formula}move(B,R2) and learns that Bob is in room R2. If Bob leaves room R2, Ann will observe footsteps and know that he has left, provided she remains in room R1.
     </paragraph>
     <paragraph>
      Regressing and enumerating the possible observations as before, we know that Ann's observations in this case will be {a mathematical formula}{move(B,R2)} and we have:{a mathematical formula} As before, there is only a single possible value of {a mathematical formula}c′ that would match these observations. Setting {a mathematical formula}c′={move(B,R2)} and its definitions for Poss and Obs gives:{a mathematical formula}
     </paragraph>
     <paragraph>
      Unlike previous examples, it is possible for {a mathematical formula}Loc(B)=R2 to become false by some sequence of hidden actions. Calculation of {a mathematical formula}P terminates after two iterations, yielding:{a mathematical formula}
     </paragraph>
     <paragraph>
      Ann will observe any actions that falsify {a mathematical formula}Loc(B)=R2, as long as she is either in the same room (so she will see Bob move) or in an Adjacent room (so she will hear Bob's footsteps).
     </paragraph>
     <paragraph>
      Since {a mathematical formula}move(B,R2) makes {a mathematical formula}Loc(B)=R2 true, regressing over it gives the following:{a mathematical formula} Substituting into the overall expression results in:{a mathematical formula} At this point we must apply {a mathematical formula}R again to convert it into a formula about {a mathematical formula}Knows0, the details of which proceed identically to the previous examples. It suffices to note that {a mathematical formula}D⊨Knows(A,Adjacent(R2,Loc(A)),S0) which is enough to satisfy the implication in the above formula.
     </paragraph>
     <paragraph label="Example 5">
      After Bob alerts that there is a stench, Ann knows there is a stench in room R2, since Ann knows that Bob is in room R2.{a mathematical formula}
     </paragraph>
     <paragraph>
      Ann observes alert which informs her that there is a stench in an adjacent room, and since she knows that Bob is in room R2, she infers {a mathematical formula}Stench(R2).
     </paragraph>
     <paragraph>
      We begin by regressing over the most recent action {a mathematical formula}{alert(B)} to get a formula uniform in {a mathematical formula}σ=defdo({move(B,R2)},S0):{a mathematical formula} The only possible case for the “∃o” clause is {a mathematical formula}o={alert}, and the only possible case for the “{a mathematical formula}∀c′” clause is {a mathematical formula}c′={alert(B)}. From a previous example we have {a mathematical formula}R(P(Stench(R2),PbU(B)),c′)⇒Stench(R2). We can thus simplify this to:{a mathematical formula} Inserting definitions of Poss and Obs gives:{a mathematical formula}
     </paragraph>
     <paragraph>
      From a previous example, we have that Ann knows {a mathematical formula}Loc(B,do({move(B,R2)},S0))=R2, so this will reduce the following tautology:{a mathematical formula}
     </paragraph>
     <paragraph>
      Which is clearly entailed by the domain.
     </paragraph>
     <paragraph label="Example 6">
      After moving to room R4 Ann observes a stench, knows that there is a stench in both R2 and R4:{a mathematical formula} And hence knows that the wumpus is in room R5:{a mathematical formula}
     </paragraph>
     <paragraph>
      The mechanics of Ann learning {a mathematical formula}Stench(R4) are identical to Example 3, so we will not repeat them here. The interesting point is that, since agents know all logical consequences of their knowledge, Ann can deduce the location of the Wumpus based on:{a mathematical formula}
     </paragraph>
     <paragraph label="Example 7">
      Ann doesn't know where Bob is, since she can't observe his footsteps from room R4.{a mathematical formula}
     </paragraph>
     <paragraph>
      Ann isn't adjacent to Bob, so she is no longer assured of hearing his footsteps if he moves out of room R2.
     </paragraph>
     <paragraph>
      Formally, using {a mathematical formula}σ=do([{move(B,R2)},{alert(B)}],S0) we have:{a mathematical formula}
     </paragraph>
     <paragraph>
      Expanding “∃o” and “{a mathematical formula}∀c′” as before, we find that the only relevant value of {a mathematical formula}c′ is {a mathematical formula}{move(A,R4)}. Recall from Example 4 that:{a mathematical formula}
     </paragraph>
     <paragraph>
      Regressing this over {a mathematical formula}move(A,R4) fixes Ann's location as R4, producing:{a mathematical formula}
     </paragraph>
     <paragraph>
      In Example 4 we also established that:{a mathematical formula}
     </paragraph>
     <paragraph>
      So there can be no value of r satisfying {a mathematical formula}(R4=r∨Adjacent(r,R4)), which is required in this expression, and therefore no r satisfying the initial query.
     </paragraph>
     <paragraph label="Example 8">
      Ann shoots the wumpus, observes the scream and knows the wumpus is dead.{a mathematical formula}
     </paragraph>
     <paragraph>
      Abbreviating all but the last action as σ, and using {a mathematical formula}Obs(A,{shoot(A,R5)},σ)={shoot(A,R5),scream}, we have:{a mathematical formula}
     </paragraph>
     <paragraph>
      No actions can cause Killed to become false, so:{a mathematical formula}
     </paragraph>
     <paragraph>
      Regressing over action {a mathematical formula}{shoot(A,B5)} results in:{a mathematical formula}
     </paragraph>
     <paragraph>
      Substituting definitions of Poss and Obs we get:{a mathematical formula}
     </paragraph>
     <paragraph>
      This tautology is clearly entailed by the domain.
     </paragraph>
     <paragraph label="Example 9">
      Ann knows that Bob knows the wumpus is dead, as he will have heard the scream regardless of his location.{a mathematical formula}
     </paragraph>
     <paragraph>
      Abbreviating all but the last action as σ, and using {a mathematical formula}Obs(A,{shoot(A,R5)},σ)={shoot(A,R5),scream}, as in Example 8, we have:{a mathematical formula}
     </paragraph>
     <paragraph>
      Since no future actions can cause Killed to be false:{a mathematical formula}
     </paragraph>
     <paragraph>
      We then need to regress this inner knowledge expression over the action {a mathematical formula}{shoot(A,R5)}, which can proceed in much the same way as previous examples:{a mathematical formula}
     </paragraph>
     <paragraph>
      Note, however, that we cannot expand the “∃o” into a disjunction based on the value of {a mathematical formula}Obs(B,{shoot(A,R5)},σ). We must instead enumerate all possible observations that Ann thinks he might make. There are three cases to consider:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Obs(B,{shoot(A,R5)},s)={shoot(A,R5),scream}
      </list-item>
      <list-item label="•">
       {a mathematical formula}Obs(B,{shoot(A,R5)},s)={shoot(A,R5)}
      </list-item>
      <list-item label="•">
       {a mathematical formula}Obs(B,{shoot(A,R5)},s)={scream}
      </list-item>
     </list>
     <paragraph>
      From previous examples, we have that {a mathematical formula}Knows(A,Wumpus()=R5,σ) and {a mathematical formula}Knows(A,Loc(B)≠R4,σ). This is enough to limit Bob's potential observations to a single option:{a mathematical formula}
     </paragraph>
     <paragraph>
      So regression of the inner expression can proceed in an identical manner to Example 8.
     </paragraph>
     <paragraph>
      In fact, at this point the hunters will have common knowledge that the Wumpus is dead. The current formalism is not rich enough to reason directly about common knowledge, but we have preliminary work on this topic in [18] that could be integrated with the approach taken here.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Related and future work
     </section-title>
     <paragraph>
      There has been a great deal of work on multi-agent systems in the situation calculus, including: specification of multi-agent systems Shapiro et al. [52]; theories of coordination [13] and ability [22]; reasoning about the epistemic feasibility of plans [23]; analysing multi-player games [1]; and our own work on the cooperative execution of Golog programs [16]. Many of these explicitly assume that all actions are public, in order to use regression to reason about knowledge. Our richer theory of knowledge could immediately be used to extend and generalise formalisms such as these to more complex multi-agent domains.
     </paragraph>
     <paragraph>
      We have developed the first principled axiomatisation of the observability of actions, using the notion of observations and views as analogues of actions and situations that are localised to an individual agent. This terminology has been deliberately chosen to match similar concepts in other formalisations of knowledge, such as the well-known treatise of Halpern and Moses [15]. By reifying these concepts as terms in the logic, we are able to give a succinct definition of the dynamics of the knowledge fluent and prove that its behaviour matches our intuitive expectations.
     </paragraph>
     <paragraph>
      A further advantage of our explicit axiomatisation of observations is in establishing properties of the knowledge relation. A major theorem of Scherl and Levesque [45] states that if the K-relation is reflexive, symmetric or transitive at the initial situation, then it has that property at every situation. In our formulation these are all simple corollaries of Theorem 1, based on the reflexive, symmetric and transitive nature of the equality symbol.
     </paragraph>
     <paragraph>
      As we discussed in Sections 3 and 5, different kinds of information-generating actions have previously been modelled by directly modifying the successor state axiom for K[48], [21], [50], [32], [49]. Unfortunately, these extensions do not in general maintain the important theorems of the standard account of knowledge [45]; there is no guarantee that a modified axiom will preserve accessibility properties of K, or will permit a regression rule for Knows. This approach is not elaboration tolerant.
     </paragraph>
     <paragraph>
      By contrast, the proof of Theorem 3 and the examples in Section 5 have shown that our approach is naturally elaboration tolerant in the face of private actions, guarded sensing actions, speech acts, and other extensions that have required special treatment in previous work. By basing our approach on an explicit, separately-axiomatised account of the local perspective of each agent, our formulation robustly maintains both accessibility property preservation and a regression rule regardless of the specific semantics of information-producing actions.
     </paragraph>
     <paragraph>
      Our approach depends crucially on the ability to do epistemic reasoning about unrestricted forms of nested knowledge in {a mathematical formula}Kn. Several promising tractable approaches have been developed for such reasoning, such as restricting theories to proper epistemic knowledge bases (PEKBs) and transforming queries into a certain normal form, which is complete and tractable for important classes of applications [20]. Lakemeyer and Lespérance [20] point out that reasoning about other agents' actions is really also required in such systems, and highlight the importance of future work on the first-order case. Our approach could form a component of such work.
     </paragraph>
     <paragraph>
      While our formalism has explicitly focused on modelling knowledge, there has also been substantial work on modelling belief in the situation calculus, where agents may be mistaken about the state of the world [51]. In such systems there are alternatives to reasoning about arbitrarily-long sequences of hidden actions, such as assuming that no hidden actions occur until there is evidence to the contrary. Shapiro and Pagnucco [47] show how agents may hypothesise the occurrence of hidden exogenous actions when they discover that their beliefs are wrong. We note that these belief-based systems are also based on the original formulation of epistemic modalities by Scherl and Levesque [45], therefore aspects of our approach could be used to enrich such systems.
     </paragraph>
     <paragraph>
      Our explicit notions of observations and views could also provide benefits for such formalisms, as well as for the formulation of other modalities (e.g. goals as in [49]) in the situation calculus. Our approach could facilitate the monitoring of goal achievement during execution, where ongoing commitment to the planned execution of goals is subject to what an agent believes. We could potentially answer the relativized persistent goal queries of Cohen and Levesque [5], where agents must consider dropping persistent goals should they believe that they have become unachievable.
     </paragraph>
     <paragraph>
      The knowledge formalism we have developed here is permissive, in that it assumes the world could potentially evolve via any legal sequence of actions. In the wider field of epistemic reasoning, it is common to constrain the world to evolve according to a given protocol[15], [10], [55]. One then speaks of an agent's knowledge under a particular protocol. The situation calculus has shown promise for verifying protocols, such as cryptographic protocols [8].
     </paragraph>
     <paragraph>
      As discussed in [55], permissive formulations of knowledge can easily be extended to support local protocols, where the allowable next actions can be determined based on the current state of the world. Our use of Poss in the axioms for knowledge could easily be replaced with predicates axiomatising actions that are, for example, Permissable or Motivated. But recent work by Fritz et al. [12] also presents an intriguing possibility to extend our approach to more general protocols.
     </paragraph>
     <paragraph>
      The most natural language for expressing a protocol in the situation calculus is Golog, so one may wish to reason about an agent's knowledge assuming the world evolves as specified by the Golog program δ:{a mathematical formula}
     </paragraph>
     <paragraph>
      Such knowledge would be queried like so:{a mathematical formula}
     </paragraph>
     <paragraph>
      It is this kind of knowledge that would be needed to integrate epistemic reasoning into our MIndiGolog execution planner [16], as the agents in that case know their teammates will act according to the shared control program.
     </paragraph>
     <paragraph>
      Fritz et al. [12] have demonstrated that the details of a given ConGolog program δ can be compiled into a theory of action {a mathematical formula}D, producing a new theory {a mathematical formula}Dδ in which the only legal situations are those that form part of a legal execution of δ:{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      So to investigate the knowledge of an agent under a protocol, we could use the compilation technique of [12] to get a query which can be handled using our formalism:{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The details are not quite so straightforward, as the compilation procedure introduces some auxiliary actions and fluents that should be hidden from the agent's knowledge. However, it does offer a possibility for future work.
     </paragraph>
     <paragraph>
      Another promising avenue of future research is to bound the number of fluents maintained at any point in time, based on the implicit assumption that agents will eventually forget facts after a certain period of time. In a model checking setting this leads to an abstract transition system with a finite number of states that can be decidably checked, and can still represent infinite executions [7]. This bounds the number of fluents in the active domain and could have merit for computing the property persistence fixpoint of {a mathematical formula}P.
     </paragraph>
     <paragraph>
      Finally, we note that a multi-agent logic of knowledge and action naturally raises the question of common knowledge, a key concept in the coordination and distributed systems literature [15]. The formalism presented here does not include a common knowledge operator, as it would be difficult to handle using regression – indeed, Batlag et al. [2] have shown that epistemic logic with both actions and common knowledge is more expressive than epistemic logic with common knowledge alone. The proper treatment of common knowledge requires a much richer language of complex epistemic modalities in the style of van Benthem et al. [56]. In previous work we have introduced such modalities to the situation calculus for synchronous domains [18], and our ongoing research will unify that approach with the asynchronous formalism developed in this paper.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Hunt the Wumpus domain axioms
     </section-title>
     <paragraph>
      The following are the complete axioms for the “Hunt the Wumpus” example domain from Section 6. Free variables are assumed to be universally quantified at outermost scope.
     </paragraph>
     <paragraph>
      The background theory {a mathematical formula}Dbg defines room adjacency, including symmetry of the predicate:{a mathematical formula}
     </paragraph>
     <paragraph>
      The background theory contains the usual unique names axioms, asserting that terms with different types or arguments are in fact different. The form is standard and we do not reproduce the full set here. Example axioms are:{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      It also captures the fact that only rooms adjacent to the Wumpus have a stench, using the following state invariant:{a mathematical formula}
     </paragraph>
     <paragraph>
      The axioms {a mathematical formula}Dadp define the precondition predicate Poss:{a mathematical formula}
     </paragraph>
     <paragraph>
      And the observation function Obs:{a mathematical formula}
     </paragraph>
     <paragraph>
      The successor state axioms {a mathematical formula}Dssa define fluent change as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The initial state axioms {a mathematical formula}DS0 state that the Wumpus is in room R5:{a mathematical formula}
     </paragraph>
     <paragraph>
      And that the hunters begin in room R1 with identical knowledge, knowing the state of R1 but not of any other rooms:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Background state invariants
     </section-title>
     <paragraph>
      We allow the background theory {a mathematical formula}Dbg to include simple state invariants in the style of [26], as long as their maintenance is implied by the successor state axioms. That is, if they hold initially, then the successor state axioms must ensure that they will hold for all future situations.
     </paragraph>
     <paragraph>
      Formally, let {a mathematical formula}Dinv⊂Dbg be the set of such invariants, each of which have the form:{a mathematical formula}
     </paragraph>
     <paragraph>
      Let {a mathematical formula}Dinv0 be the same formulae applied to just the initial situations:{a mathematical formula}
     </paragraph>
     <paragraph>
      Then we require that:{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      Such invariants thus do not imply any additional dynamics of the world, but merely provide an explicit encoding of static facts of the domain, such as fixed relationships between fluents.
     </paragraph>
     <paragraph>
      Typical approaches to state invariants in the situation calculus, such as [26], would modify {a mathematical formula}Dssa and {a mathematical formula}DS0 to ensure maintenance of the constraints as above, then discard {a mathematical formula}Dinv from the theory as redundant.
     </paragraph>
     <paragraph>
      We keep the invariants as an explicit part of the background theory because they are useful when calculating the persistence condition. The algorithm for calculating {a mathematical formula}P(ϕ,α) requires reasoning relative to {a mathematical formula}D−DS0 and hence cannot take advantage of implicitly-encoded state constraints.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Complete proofs
     </section-title>
     <paragraph label="Lemma 1">
      For situation terms s and{a mathematical formula}s″, and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation {a mathematical formula}s″. The base case is {a mathematical formula}s″=s, for which the lemma is trivial. The inductive case is {a mathematical formula}s″=do(c′,s′) where {a mathematical formula}s≤PbU(agt)s′ and {a mathematical formula}PbU(agt,c′,s′). Expanding the definition of Legal, the inductive hypothesis gives {a mathematical formula}root(s′)≤Posss′. Since {a mathematical formula}PbU(agt,c′,s′) implies {a mathematical formula}Poss(c′,s′) we have {a mathematical formula}root(s′)≤Possdo(c′,s′), which matches the definition of {a mathematical formula}Legal(s″) as required.  □
     </paragraph>
     <paragraph label="Lemma 2">
      For situation terms s and{a mathematical formula}s″, and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation {a mathematical formula}s″. The base case is {a mathematical formula}s″=s, for which the lemma is trivial. The inductive case is {a mathematical formula}s″=do(c′,s′) where {a mathematical formula}s≤PbU(agt)s′ and {a mathematical formula}PbU(agt,c′,s′). In this case we have that PbU implies {a mathematical formula}Obs(agt,c′,s′)=∅, so {a mathematical formula}View(agt,s″)=View(agt,s′) by Eq. (5), and the inductive hypothesis of {a mathematical formula}View(agt,s′)=View(agt,s) gives the required result.  □
     </paragraph>
     <paragraph label="Lemma 3">
      For situation terms s and{a mathematical formula}s″, and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation s. In the base case of {a mathematical formula}Init(s), Eq. (9) ensures there is some {a mathematical formula}s′ such that {a mathematical formula}K0(agt,s′,s)∧s′≤PbU(agt)s″, and we have the desired implication using {a mathematical formula}root(s″)=root(s′)=s′.For the {a mathematical formula}do(c,s) case, suppose that we have {a mathematical formula}K(agt,s″,do(c,s)). Then by Eq. (8) there is some {a mathematical formula}s′ such that {a mathematical formula}s′⊑s″ and {a mathematical formula}K(agt,s′,s). Then {a mathematical formula}root(s″) = {a mathematical formula}root(s′), and {a mathematical formula}K0(agt,root(s′),root(s)) by the inductive hypothesis, giving the required result.  □
     </paragraph>
     <paragraph label="Lemma 4">
      For situation terms s and{a mathematical formula}s″, and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation s. In the base case of {a mathematical formula}Init(s), using Eq. (9), if {a mathematical formula}K(agt,s″,s) then there must be an {a mathematical formula}s′ such that {a mathematical formula}K0(agt,s′,s) and {a mathematical formula}s′≤PbU(agt)s″. The foundational axioms ensure that {a mathematical formula}K0(agt,s′,s)→Init(s′), so all such {a mathematical formula}s′ are legal, making {a mathematical formula}s″ legal by Lemma 1.For the {a mathematical formula}do(c,s) case, the inductive hypothesis gives that {a mathematical formula}K(agt,s′,s)→Legal(s′) and we split on {a mathematical formula}Obs(agt,c,s). Suppose {a mathematical formula}Obs(agt,c,s)=∅, then Eq. (8) gives {a mathematical formula}K(agt,s″,s) and {a mathematical formula}Legal(s″) follows immediately from the inductive hypothesis.Alternately, suppose {a mathematical formula}Obs(agt,c,s)≠∅, then Eq. (8) ensures there must be a {a mathematical formula}c′, {a mathematical formula}s′ satisfying three conditions: {a mathematical formula}K(agt,s′,s), {a mathematical formula}Poss(c′,s′) and {a mathematical formula}do(c′,s′)≤PbU(agt)s″. The first of these yields {a mathematical formula}Legal(s′) by the inductive hypothesis. Given that, the second yields {a mathematical formula}Legal(do(c′,s′)) by the definition of Legal. Given that, the third yields {a mathematical formula}Legal(s″) by Lemma 1 and we have the required result in both cases.  □
     </paragraph>
     <paragraph label="Lemma 5">
      For situation terms s and{a mathematical formula}s″, and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation s. For the base case of {a mathematical formula}Init(s), using Eq. (9), {a mathematical formula}K(agt,s″,s) implies that there must be an {a mathematical formula}s′ such that {a mathematical formula}Init(s′) and {a mathematical formula}s′≤PbU(agt)s″. Then {a mathematical formula}View(s′)=View(s)=ϵ by definition, and {a mathematical formula}View(s″)=View(s′) by Lemma 2 to give the required result.For the {a mathematical formula}do(c,s) case, suppose {a mathematical formula}Obs(agt,c,s)=∅. The definition of View gives {a mathematical formula}View(agt,do(c,s))=View(agt,s), while Eq. (8) gives {a mathematical formula}K(agt,s″,s) and hence {a mathematical formula}View(agt,s″)=View(agt,s) by the inductive hypothesis.Alternately, suppose {a mathematical formula}Obs(agt,c,s)≠∅, then Eq. (8) gives us {a mathematical formula}s′, {a mathematical formula}c′ where {a mathematical formula}do(c′,s′)≤PbU(agt)s″, {a mathematical formula}Obs(agt,c,s)=Obs(agt,c′,s′), and {a mathematical formula}K(agt,s′,s). The definition of View gives:{a mathematical formula}{a mathematical formula} The inductive hypothesis gives us {a mathematical formula}View(agt,s′)=View(agt,s) and hence {a mathematical formula}View(agt,do(c′,s′))=View(agt,do(c,s)), while Lemma 2 completes the equivalence by giving us {a mathematical formula}View(agt,s″)=View(agt,do(c′,s′)).  □
     </paragraph>
     <paragraph label="Lemma 6">
      For any situation s and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation s. For the base case of {a mathematical formula}Init(s) the lemma is trivial since {a mathematical formula}root(s)=s.For the {a mathematical formula}do(c,s) case, the empty view implies {a mathematical formula}Obs(agt,c,s)=∅ and {a mathematical formula}View(agt,s)=ϵ, while {a mathematical formula}Legal(do(c,s)) implies {a mathematical formula}Poss(c,s) and {a mathematical formula}Legal(s). This gives {a mathematical formula}s≤PbU(agt)do(c,s), and using {a mathematical formula}root(s)≤PbU(agt)s from the inductive hypothesis gives the required result.  □
     </paragraph>
     <paragraph label="Lemma 7">
      For any situation s, observations o, view v and agent agt:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      By induction on situation s. For the base {a mathematical formula}Init(s) case we have {a mathematical formula}View(agt,s)=ϵ, so the LHS is never true and the lemma is trivial. For the {a mathematical formula}do(c,s) case we split on whether c is observable.Suppose {a mathematical formula}Obs(agt,c,s)≠∅. Then by definition of View we have that {a mathematical formula}Obs(agt,c,s)=o and {a mathematical formula}View(agt,s)=v, and the {a mathematical formula}∃c′,s′ on the RHS of the lemma is trivially satisfied by c and s themselves.Alternately, suppose {a mathematical formula}Obs(agt,c,s)=∅. Then by definition of View we have {a mathematical formula}View(agt,do(c,s))=View(agt,s). The inductive hypothesis gives us {a mathematical formula}c′ and {a mathematical formula}s′ satisfying the RHS of the lemma with {a mathematical formula}do(c′,s′)≤PbU(agt)s. Since the LHS gives us {a mathematical formula}Legal(do(c,s)) we have {a mathematical formula}Poss(c,s), hence {a mathematical formula}PbU(agt,c,s), hence {a mathematical formula}do(c′,s′)≤PbU(agt)do(c,s). So the {a mathematical formula}c′,s′ for the predecessor situation s also satisfy the RHS of the lemma for {a mathematical formula}do(c,s).  □
     </paragraph>
     <paragraph label="Lemma 8">
      (From[37], [45].) Suppose φ is a regressable formula of the situation calculus and{a mathematical formula}Dis a basic action theory. Then:{a mathematical formula}where{a mathematical formula}(∀)ϕdenotes the universal closure of the formula ϕ with respect to its free variables.
     </paragraph>
     <paragraph label="Proof">
      This is a foundational result of the situation calculus, proven for example as Theorem 2 in [37] and as part of Theorem 7 in [45]. We repeat it here for completeness.  □
     </paragraph>
     <paragraph label="Theorem 1">
      For any agent agt and situations s and{a mathematical formula}s″:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      The only-if direction is a trivial combination of Lemma 3, Lemma 4, Lemma 5. For the if direction we proceed by induction on situation s.In the base case of {a mathematical formula}Init(s), we need some {a mathematical formula}s′ to satisfy the {a mathematical formula}∃s′ part of Eq. (9). Using {a mathematical formula}root(s″) is sufficient, since we have {a mathematical formula}View(agt,s″)=View(agt,s)=ϵ and hence {a mathematical formula}root(s″)≤PbU(agt)s″ by Lemma 6.For the inductive case with {a mathematical formula}do(c,s), we have two sub-cases to consider. Suppose {a mathematical formula}Obs(agt,c,s)=∅: then {a mathematical formula}View(agt,s″)=View(agt,do(c,s))=View(agt,s) and hence {a mathematical formula}K(agt,s″,s) holds by the inductive hypothesis, satisfying the equivalence in Eq. (8) and giving {a mathematical formula}K(agt,s″,do(c,s)) as required.Alternately, suppose {a mathematical formula}Obs(agt,c,s)≠∅: then we have:{a mathematical formula} And we need some {a mathematical formula}s′,c′ to satisfy the {a mathematical formula}∃s′,c′ part of Eq. (8).Since {a mathematical formula}s″ is legal, Lemma 7 implies there is some {a mathematical formula}s′, {a mathematical formula}c′ satisfying {a mathematical formula}Obs(agt,c′,s′)=Obs(agt,c,s), {a mathematical formula}View(agt,s′)=View(agt,s) and {a mathematical formula}do(c′,s′)≤PbU(agt)s″. This is enough to satisfy Eq. (8) and so the equivalence holds as required.  □
     </paragraph>
     <paragraph label="Theorem 4">
      Given a basic action theory{a mathematical formula}D∪DKobsand a uniform formula ϕ for which{a mathematical formula}P(ϕ,PbU(agt))exists:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      To obtain this result, we must establish that our new regression rules in Eqs. (13) and (14) are equivalences under the theory of action {a mathematical formula}D∪DKobs. The proof proceeds by cases on situation s and its mechanics mirror the analogous Theorem 7 in [45], but with the addition of a persistence condition application.For notational clarity we define the abbreviation {a mathematical formula}PEO(agt,ϕ,o,s) (for “persists under equivalent observations”) which states that ϕ holds in all legal futures of s compatible with observations o:{a mathematical formula}First, note that we need only consider two cases: {a mathematical formula}do(c,s) and {a mathematical formula}S0. We do not provide a regression rule for knowledge at other situation terms, so {a mathematical formula}R(Knows(agt,ϕ,s)) would leave the formula unchanged and the theorem is trivial.In the {a mathematical formula}do(c,s) case, by definition of the Knows macro we have:{a mathematical formula}Applying the successor state axiom from Eq. (8), introducing a variable to name {a mathematical formula}Obs(agt,c,s), and distributing {a mathematical formula}∀s″ across the two conjuncts gives us:{a mathematical formula}To make the third conjunct match PEO we rearrange using:{a mathematical formula}To give:{a mathematical formula}Pushing quantifiers over independent conjuncts and re-arranging using:{a mathematical formula}We obtain:{a mathematical formula}Which matches the form of our PEO macro:{a mathematical formula}Since both conjuncts contain sub-formulae matching the form of the Knows macro, it can be substituted back in to give:{a mathematical formula}For {a mathematical formula}PEO(agt,ϕ,o,s′) to legitimately appear inside the Knows macro it must be uniform in the situation variable {a mathematical formula}s′. Applying the persistence condition and regressing to make the expression uniform, we develop the following equivalence:{a mathematical formula}Suppressing the situation term in this uniform formula gives the regression rule from Eq. (13) as required.For the base case of {a mathematical formula}S0, a straightforward transformation of Eqs. (1) and (9) gives:{a mathematical formula} Applying the persistence condition operator, this can easily be re-written as:{a mathematical formula}This matches the form of the definition for {a mathematical formula}Knows0, which we can substitute in to give:{a mathematical formula}Since all situations reachable by {a mathematical formula}K0 are initial, and since Lemma 8 ensures that regression preserves equivalence with respect to the original query, it is therefore valid to use {a mathematical formula}R(ψ[S0])−1 on the enclosed formula to give:{a mathematical formula}This is the regression rule from Eq. (14) as required.Our regression rules are thus equivalences under the theory {a mathematical formula}D∪DKobs.For base cases {a mathematical formula}Init(s) other than {a mathematical formula}S0 there is no explicit regression rule defined, so it would leave the formula unchanged in this case. The theorem thus holds for all situations s.  □
     </paragraph>
     <paragraph label="Theorem 5">
      Given a basic action theory{a mathematical formula}Dand a uniform formula ϕ for which{a mathematical formula}P(ϕ,PbU(agt))exists:{a mathematical formula}
     </paragraph>
     <paragraph label="Proof">
      Recall the definition of {a mathematical formula}Knows(agt,ϕ,v) as follows:{a mathematical formula}We also have the following simple corollary of Theorem 1:{a mathematical formula}The definition of {a mathematical formula}Knows(agt,ϕ,v) is thus equivalent to:{a mathematical formula}We thus need to find a single witness situation rather than examining all situations with that view. We proceed by induction over views. For the ϵ case, {a mathematical formula}S0 serves as an appropriate witness since it is always legal, {a mathematical formula}View(agt,S0)=ϵ and {a mathematical formula}root(S0)=S0. Applying the regression rule for {a mathematical formula}Knows(agt,ϕ,S0) gives us the same expression as applying the regression rule for {a mathematical formula}Knows(agt,ϕ,ϵ). So if {a mathematical formula}R(Knows(agt,ϕ,ϵ)) holds then so does {a mathematical formula}Knows(agt,ϕ,S0). Using {a mathematical formula}S0 as a witness we conclude that {a mathematical formula}Knows(agt,ϕ,ϵ) iff {a mathematical formula}R(Knows(agt,ϕ,ϵ)) as desired.For the inductive {a mathematical formula}o⋅v case we split on whether there is any situation having that view. Suppose there is no such situation, then the definition of {a mathematical formula}Knows(agt,ϕ,o⋅v) is trivially satisfied and the agent must know all statements. We need to show that the regression of {a mathematical formula}Knows(agt,ϕ,o⋅v) is always entailed by the domain in this case. The regressed expression is:{a mathematical formula}If there is no situation having view v, then there is also no situation having view {a mathematical formula}o⋅v, and the above is entailed by the inductive hypothesis in this case.Alternately, suppose there is a situation s having view v but no legal situation having view {a mathematical formula}o⋅v. Then all situations {a mathematical formula}s′ that have view equal to v must satisfy {a mathematical formula}¬∃c:Obs(agt,c,s′)=o∧Poss(c,s′), otherwise we could construct a situation with view {a mathematical formula}o⋅v. Since these situations {a mathematical formula}s′ are the only ones that can be K-related to s, the antecedent in the above implication is falsified at all such situations, and the regressed expression is equivalent to {a mathematical formula}Knows(agt,⊤,v) which is trivially entailed.Finally, suppose there is a legal situation {a mathematical formula}do(c,s) having view {a mathematical formula}o⋅v. We can assume without loss of generality that {a mathematical formula}Obs(agt,c,s)=o and {a mathematical formula}View(agt,s)=v. Regressing {a mathematical formula}Knows(agt,ϕ,do(c,s)) in this case will produce:{a mathematical formula}We have that {a mathematical formula}Obs(agt,c,s)=o and {a mathematical formula}o≠∅, so this is equivalent to:{a mathematical formula}Since this matches the form of {a mathematical formula}R(Knows(agt,ϕ,o⋅v)), and we have that the view of s is v, this will be entailed by the domain precisely when the regression of {a mathematical formula}Knows(agt,ϕ,o⋅v) is entailed by the domain.Thus if there is no legal situation with view v then {a mathematical formula}R(Knows(agt,ϕ,v)), is always entailed, while if there is such a situation s then {a mathematical formula}R(Knows(agt,ϕ,v)) is equivalent to {a mathematical formula}R(Knows(agt,ϕ,s)). The regression rules over observations are thus equivalences as desired.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>