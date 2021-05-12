<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    From model checking to equilibrium checking: Reactive modules for rational verification.
   </title>
   <abstract>
    Model checking is the best-known and most successful approach to formally verifying that systems satisfy specifications, expressed as temporal logic formulae. In this article, we develop the theory of equilibrium checking, a related but distinct problem. Equilibrium checking is relevant for multi-agent systems in which system components (agents) are assumed to be acting rationally in pursuit of delegated goals, and is concerned with understanding what temporal properties hold of such systems under the assumption that agents select strategies in equilibrium. The formal framework we use to study this problem assumes agents are modelled using Reactive Modules, a system modelling language that is used in a range of practical model checking systems. Each agent (or player) in a Reactive Modulesgame is specified as a nondeterministic guarded command program, and each player's goal is specified with a temporal logic formula that the player desires to see satisfied. A strategy for a player in a Reactive Modules game defines how that player selects enabled guarded commands for execution over successive rounds of the game. For this general setting, we investigate games in which players have goals specified in Linear Temporal Logic (in which case it is assumed that players choose deterministic strategies) and in Computation Tree Logic (in which case players select nondeterministic strategies). For each of these cases, after formally defining the game setting, we characterise the complexity of a range of problems relating to Nash equilibria (e.g., the computation or the verification of existence of a Nash equilibrium or checking whether a given temporal formula is satisfied on some Nash equilibrium). We then go on to show how the model we present can be used to encode, for example, games in which the choices available to players are specified using STRIPS planning operators.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Our main interest in this paper is in the analysis of concurrent systems composed of multiple non-deterministic computer programs, in which at run-time each program resolves its non-determinism rationally and strategically in pursuit of an individual goal, specified as a formula of temporal logic. Since the programs are assumed to be acting strategically, game theory provides a natural collection of analytical concepts for such systems [53]. If we apply game-theoretic analysis to such systems, then the main questions to be answered about such systems are not just “what computations might the system produce?”, but rather, “what computations might the system produce if the constituent programs act rationally?” If we interpret acting rationally to mean choosing strategies (for resolving non-determinism) that are in Nash equilibrium, then this question amounts to asking “which of the possible computations of the system will be produced in equilibrium?” Further, if we use temporal logic as the language for expressing properties of our multi-agent and concurrent system (as is standard in the computer aided verification community [20]), then we can also interpret this question as “which temporal logic formulae are satisfied by computations arising from the selection of strategies in equilibrium?” We refer to this general problem as equilibrium checking[75].
     </paragraph>
     <paragraph>
      Related questions have previously been considered within computer science and artificial intelligence – see e.g., [14], [23], [29], [30], [51], [13], [8]. However, a common feature in this previous work is that the computational models used as the basis for analysis are highly abstract, and in particular are not directly based on real-world programming models or languages. For example, in [29] the authors define and investigate iterated Boolean games (iBG), a generalisation of Boolean games [36], [37], in which each agent exercises unique control over a set of Boolean variables, and system execution proceeds in an infinite sequence of rounds, with each agent selecting a valuation for the variables under their control in each round. Each player has a goal, specified as a formula of Linear Temporal Logic (LTL), which it desires to see achieved. The iterated Boolean games model is simple and natural, and provides a compelling framework with which to pose questions relating to strategic multi-agent interaction in settings where agents have goals specified as logical formulae. However, this model is arguably rather abstract, and is some distance from realistic programming languages and system modelling languages; we discuss such work in more detail in the related work section towards the end of this article.
     </paragraph>
     <paragraph>
      In brief, our main aim is to study a framework without these limitations. Specifically, we study game-like systems in which players are specified using (a subset of) the Reactive Modules language [2], which is widely used as a system modelling language in practical model checking systems such as mocha[4] and Prism[43]. Reactive Modules is intended to support the succinct, high-level specification of concurrent and multi-agent systems. As we will see, Reactive Modules can readily be used to encode other frameworks for modelling multi-agent systems (such as multi-agent STRIPS planning systems [10]).
     </paragraph>
     <paragraph>
      The remainder of the article is structured as follows:
     </paragraph>
     <list>
      <list-item label="•">
       We begin in the following section by motivating our work in detail, in particular by arguing that the classical notion of system correctness is of limited value in multi-agent systems, and introducing the idea of equilibrium checking as representing a more appropriate framework through which to understand the behaviour of such systems.
      </list-item>
      <list-item label="•">
       We then survey the logics LTL and CTL, and their semantic basis on Kripke structures, present srml – a sublanguage of Reactive Modules that we use throughout the article – and then develop a formal semantics for it.
      </list-item>
      <list-item label="•">
       We then introduce Reactive Modules games, in which the structure of the game (what we call the “arena”) is specified using Reactive Modules, and the preferences of players are specified by associating a temporal (LTL or CTL) goal formula with each player, which defines runs or computation trees that would satisfy the player's goal.
      </list-item>
      <list-item label="•">
       We then investigate the complexity of various game-theoretic questions in Reactive Modules games, for both the LTL and the CTL settings, and conclude by discussing the complexity and expressiveness of our new framework against the most relevant related work. Table 2 at the end of the paper summarises our findings.
      </list-item>
      <list-item label="•">
       Finally, to demonstrate the wider applicability of our framework, we show how it can be used to capture propositional STRIPS games (cf. [22], [12], [25]), such as the MA-STRIPS model of Brafman and Domshlak [10].
      </list-item>
     </list>
     <paragraph>
      Although largely self-contained, our technical presentation is necessarily terse, and readers may find it useful to have some familiarity with temporal logics [20], [18], model checking [16], complexity theory [54], and basic concepts of non-cooperative game theory [53].
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Motivation
     </section-title>
     <paragraph>
      Our aim in this section is to motivate and introduce the idea of equilibrium checking as a multi-agent systems counterpart to the standard notion of verification and model checking. (Many readers will be familiar with much of this material – we beg their indulgence so that we can tell the story in its entirety.)
     </paragraph>
     <paragraph>
      Correctness and formal verification  The correctness problem has been one of the most widely studied problems in computer science over the past fifty years, and remains a topic of fundamental concern to the present day [9]. Broadly speaking, the correctness problem is concerned with checking that computer systems behave as their designer intends. Probably the most important problem studied within the correctness domain is that of formal verification. Formal verification is the problem of checking that a given computer program or system P is correct with respect to a given formal (i.e., mathematical) specification φ. We understand φ as a description of system behaviours that the designer judges to be acceptable – a program that guarantees to generate a behaviour as described in φ is deemed to correctly implement the specification φ.
     </paragraph>
     <paragraph>
      A key insight, due to Amir Pnueli, is that temporal logic can be a useful language with which to express formal specifications of system behaviour [56]. Pnueli proposed the use of Linear Temporal Logic (LTL) for expressing desirable properties of computations. LTL extends classical logic with tense operators X (“in the next state…”), F (“eventually…”), G (“always…”), and U (“…until …”) [20]. For example, the requirement that a system never enters a “crash” state can naturally be expressed in LTL by a formula {a mathematical formula}G¬crash. If we let {a mathematical formula}〚P〛 denote the set of all possible computations that may be produced by the program P, and let {a mathematical formula}〚φ〛 denote the set of state sequences that satisfy the LTL formula φ, then verification of LTL properties reduces to the problem of checking whether {a mathematical formula}〚P〛⊆〚φ〛. Another key temporal formalism is Computation Tree Logic (CTL), which modifies LTL by prefixing tense operators with path quantifiersA (“on all paths…”) and E (“on some path…”). While LTL is suited to reasoning about runs or computational histories, CTL is suited to reasoning about transition systems that encode all possible system behaviours.
     </paragraph>
     <paragraph>
      Model checking  The most successful approach to verification using temporal logic specifications is model checking[16]. Model checking starts from the idea that the behaviour of a finite state program P can be represented as a Kripke structure, or transition system {a mathematical formula}KP. Now, Kripke structures can be interpreted as models for temporal logic. So, for example, checking whether a program P satisfies an LTL property φ reduces to the problem of checking whether φ is satisfied on every path through {a mathematical formula}KP. Checking a CTL specification φ is even simpler: the Kripke structure {a mathematical formula}KP is a CTL model, so we simply need to check whether {a mathematical formula}KP⊨φ holds. For an illustration see Fig. 1. These checks can be efficiently automated for many cases of interest. In the case of CTL, for example, checking whether {a mathematical formula}KP⊨φ holds can be solved in time {a mathematical formula}O(|KP|⋅|φ|)[15], [20]; for LTL, the problem is more complex (PSPACE-complete [20]), but using automata theoretic techniques it can be solved in time {a mathematical formula}O(|KP|⋅2|φ|)[69], the latter result indicating that such an approach is feasible for small specifications. Since the model checking paradigm was first proposed in 1981, huge progress has been made on extending the range of systems amenable to verification by model checking, and to extending the range of properties that might be checked [16].
     </paragraph>
     <paragraph>
      Multi-agent systems  We now turn the class of systems that we will be concerned with in the present paper. The field of multi-agent systems is concerned with the theory and practice of systems containing multiple interacting semi-autonomous software components known as agents[72], [62]. Multi-agent systems are generally understood as distinct from conventional distributed or concurrent systems in several respects, but the most important distinction for our purposes is that different agents are assumed to be operating on behalf of different external principals, who delegate their preferences or goals to their agent. Because different agents are “owned” by different principals, there is no assumption that agents will have preferences that are aligned with each other.
     </paragraph>
     <paragraph>
      Correctness in multi-agent systems  Now, consider the following question: How should we interpret correctness and formal verification in the context of multi-agent systems? In one sense, this question is easily answered: We can certainly think of a multi-agent system as a collection of interacting non-deterministic computer programs, with non-determinism representing the idea that agents have choices available to them; we can model such a system using any number of readily available model checking systems, which would then allow us to start reasoning about the possible computational behaviours that the system might in principle exhibit. But while such an analysis is entirely legitimate, and might well yield important insights, it nevertheless misses a key part of the story that is relevant in order to understand a multi-agent system. This is because it ignores the fact that agents are assumed to pursue their preferences rationally and strategically. Thus, certain system behaviours that might be possible in principle will never arise in practice because they could not arise from rational choices by agents within the system.
     </paragraph>
     <paragraph>
      The classical formulation of correctness does not naturally match the multi-agent system setting because there is no single specification φ against which the correctness of a multi-agent system is judged. Instead, the agents within such a system each carry their own specification: an agent is judged to be correct if it acts rationally to achieve its delegated preferences or goals. There is no single standard of correctness by which the system as a whole can be judged, and attempting to apply such a standard does not help to understand the behaviour of the system. So, what should replace the classical notion of correctness in the context of multi-agent systems? We will now argue for the concept of rational verification and equilibrium checking.
     </paragraph>
     <paragraph>
      Rational verification and equilibrium checking  We believe (as do many other researchers [52], [62]) that game theory provides an appropriate analytical framework for the analysis of multi-agent systems. Originating within economics, game theory is essentially the theory of strategic interaction between self-interested entities [49]. While the mathematical framework of game theory was not developed specifically to study computational settings, it nevertheless seems that the toolkit of analytical concepts it provides can be adapted and applied to multi-agent settings. A game in the sense of game theory is usually understood as an abstract mathematical model of a situation in which self-interested players must make decisions. A game specifies the decision-makers in the game – the players – and the choices available to them – their strategies. For every combination of possible choices by players, the game also specifies what outcome will result, and each player has their own preferences over possible outcomes. A key concern in game theory is to try to understand what the outcomes of a game can or should be, under the assumption that the players within it choose rationally in pursuit of their preferences. To this end, many solution concepts have been proposed, of which Nash equilibrium is probably the best-known. A Nash equilibrium is a collection of choices, one for each participant in the game, such that no player can benefit by unilaterally deviating from this combination of choices. Nash equilibria seem like reasonable candidates for the outcome of a game because to unilaterally move away from a Nash equilibrium would result in that player being worse off – which would clearly not be rational. In general, it could be the case that a given game has no Nash equilibrium, or multiple Nash equilibria.
     </paragraph>
     <paragraph>
      It should be easy to see how this general setup maps to the multi-agent systems setting: players map to the agents within the system, and each player's preferences are defined as their delegated goals; the choices available to each player correspond to the possible courses of action that may be taken by each agent in the system. Outcomes will correspond to the computations or runs of the system, and agents will have preferences over these runs; they act to try and bring about their most preferred runs.
     </paragraph>
     <paragraph>
      With this in mind, we believe it is natural to think of the following problem as a counterpart to model checking and classical verification. We are given a multi-agent system, and a temporal logic formula φ representing a property of interest. We then ask whether φ would be satisfied in some run that would arise from a Nash equilibrium collection of choices by agents within the system. We call this equilibrium checking, and refer to the general paradigm as rational verification. For an illustration see Fig. 2. This idea is captured in the following decision problem: E-Nash:Given: Multi-agent system M; temporal formula φ.Question: Is it the case that φ holds on some computation of M that could arise through the agents in M choosing strategies that form a Nash equilibrium? The obvious counterpart of this decision problem is A-Nash, which asks whether a temporal formula φ is satisfied on all computations that could arise as a result of agents choosing strategies that form a Nash equilibrium.
     </paragraph>
     <paragraph>
      A higher-level question is simply whether a system has some Nash equilibria: Non-Emptiness:Given: Multi-agent system M.Question: Does M have some Nash equilibria? A system without any Nash equilibria is inherently unstable: whatever collection of choices we might consider for the agents within it, some player would have preferred to make an alternative choice. Notice that an efficient algorithm for solving E-Nash would imply an efficient algorithm for Non-Emptiness.
     </paragraph>
     <paragraph>
      Finally, we might consider the question of verifying whether a given strategy profile represents a Nash equilibrium: NE-Membership:Given: Multi-agent system M, strategy profile {a mathematical formula}σ→.Question: Is {a mathematical formula}σ→ a Nash equilibrium?
     </paragraph>
     <paragraph>
      The aim of the present article is to formulate and investigate the main computational questions relating to equilibrium checking. In order to be able to study these questions, we need to fix on an appropriate model of multi-agent systems, and also some way of defining preferences for this model. As we noted above, the model of multi-agent systems that we adopt is that of Reactive Modules[2]. Our argument for studying this framework is that it is a well-known, widely studied, and most importantly, widely used framework for modelling concurrent and multi-agent systems [4], [67], [43]. In short, Reactive Modules represents a realistic computational framework within which to study the questions of interest to us. This leaves the question of how to define preferences. Our approach here is very natural: we assume that preferences are defined by giving each agent a temporal logic goal, which the agent is required to try to accomplish. The use of logically-specified goals is commonplace in AI, and temporal logic itself is widely used as a goal specification language within the AI planning community [25]. Moreover, this approach also fits well with the classic view of correctness, as discussed above, wherein a temporal logic goal can be interpreted as a specification that the agent should satisfy.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      We will be dealing with logics that extend propositional logic. Thus, these logics are based on a finite set Φ of Boolean variables, and contain the classical connectives “∧” (and), “∨” (or), “¬” (not), “→” (implies), and “↔” (iff), as well as the Boolean constants “⊤” (truth) and “⊥” (falsity). A valuation for propositional logic is given by a subset {a mathematical formula}v⊆Φ, with the intended interpretation that {a mathematical formula}x∈v means that x is true under valuation v, while {a mathematical formula}x∉v means that x is false under v. For propositional formulae φ we write {a mathematical formula}v⊨φ to mean that φ is satisfied by v. Let {a mathematical formula}V(Φ)=2Φ be the set of all valuations for variables Φ; where Φ is clear, we omit reference to it and write V. Let {a mathematical formula}v⊥=∅ be the valuation under which all variables are false. Where {a mathematical formula}v∈V, we let {a mathematical formula}χv denote the characteristic formula of v, which is satisfied only by the valuation v, that is,{a mathematical formula}
     </paragraph>
     <section label="3.1">
      <section-title>
       Kripke structures
      </section-title>
      <paragraph>
       We use Kripke structures[16, p. 14] to model the dynamics of our systems. A Kripke structure K over Φ is given by a tuple {a mathematical formula}K=(S,S0,R,π), where S is a finite non-empty set of states with typical element s and {a mathematical formula}R⊆S×S is a left total transition relation on S. Left totality means that for every state {a mathematical formula}s∈S, there is another state {a mathematical formula}s′∈S such that {a mathematical formula}(s,s′)∈R. Moreover, {a mathematical formula}S0⊆S is the set of initial states and {a mathematical formula}π:S→V is a valuation function, assigning a valuation {a mathematical formula}π(s) to every {a mathematical formula}s∈S. See Fig. 3 for an illustration of a Kripke structure over {a mathematical formula}Φ={x,y}. Where {a mathematical formula}K=(S,S0,R,π) is a Kripke structure over Φ, and {a mathematical formula}Ψ⊆Φ, then we denote the restriction of K to Ψ by {a mathematical formula}K|Ψ, where {a mathematical formula}K|Ψ=(S,S0,R,π|Ψ) is the same as K except that the valuation function {a mathematical formula}π|Ψ is defined as follows: {a mathematical formula}π|Ψ(s)=π(s)∩Ψ. We say that the size of a Kripke structure K, denoted by {a mathematical formula}|K|, is {a mathematical formula}|S|+|R|+|π|.
      </paragraph>
      <paragraph>
       {a mathematical formula}
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Computation runs
      </section-title>
      <paragraph>
       A run of a Kripke structure K is a sequence {a mathematical formula}ρ=s0,s1,s2,… of states where for all {a mathematical formula}t∈N we have {a mathematical formula}(st,st+1)∈R. Using square brackets around parameters referring to time points, we let {a mathematical formula}ρ[t] denote the state assigned to time point {a mathematical formula}t∈N by run ρ. We say ρ is an s-run if {a mathematical formula}ρ[0]=s. A run ρ of K where {a mathematical formula}ρ[0]∈S0 is referred to as an initial run. Thus, in our example in Fig. 3, {a mathematical formula}s0,s0,s2,s3,s3,s3… and {a mathematical formula}s2,s3,s1,s0,s1,s0,… are both runs but only the former is an initial run. Let {a mathematical formula}runs(K,s) be the set of s-runs of K, and let {a mathematical formula}runs(K) be the set of initial runs of K. Notice that a run {a mathematical formula}ρ∈runs(K) is a sequence of states. Every such sequence induces an infinite sequence {a mathematical formula}ρ∈Vω of valuations, given by
      </paragraph>
      <paragraph>
       which we also refer to as a computation run. In our example in Fig. 3, we thus find that {a mathematical formula}{x,y},{x,y},{x},∅,∅,∅,… is a computation run, whereas, for instance, {a mathematical formula}{y},{x},∅,{x,y},{x,y},… is not. The set of these sequences, (i.e., sequences of valuations corresponding to runs in {a mathematical formula}runs(K)) we denote by {a mathematical formula}runs(K).
      </paragraph>
      <paragraph>
       Given {a mathematical formula}Ψ⊆Φ and {a mathematical formula}ρ:N→V(Φ), we denote the restriction of ρ to Ψ by {a mathematical formula}ρ|Ψ, i.e., {a mathematical formula}ρ|Ψ[t]=ρ[t]∩Ψ for each {a mathematical formula}t∈N. We refer to a finite prefix of a run as a partial run, and denote partial runs by {a mathematical formula}ϱ,ϱ′,… etc. We extend the notations for runs, restrictions of runs, etc., to initial runs, restrictions of partial runs, etc., in the obvious way.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Linear temporal logic
      </section-title>
      <paragraph>
       We use the well-known framework of Linear Temporal Logic (LTL) to express properties of runs of our systems [20], [46], [47]. Formulae of LTL are essentially predicates over infinite sequences of states. LTL extends propositional logic with two modal tense operators, namely, X (“next”) and U (“until”). Formally, the syntax of LTL is defined with respect to a set Φ of Boolean variables as follows:{a mathematical formula} where {a mathematical formula}x∈Φ. The remaining classical logical connectives are defined in terms of ¬ and ∨ in the usual way. Two key derived LTL operators are F (“eventually”) and G (“always”), which are defined in terms of U as follows: {a mathematical formula}Fφ=⊤Uφ, and {a mathematical formula}Gφ=¬F¬φ. Given a set of variables Ψ, let {a mathematical formula}Ltl(Ψ) be the set of LTL formulae over Ψ; where the variable set is clear from the context, we write Ltl.
      </paragraph>
      <paragraph>
       We interpret formulae of LTL with respect to pairs {a mathematical formula}(ρ,t) where {a mathematical formula}ρ∈Vω is a run and {a mathematical formula}t∈N is a temporal index into ρ. Any given LTL formula may be true at none or multiple time points on a run; for example, a formula {a mathematical formula}Xp will be true at a time point {a mathematical formula}t∈N on a run ρ if p is true on run ρ at time {a mathematical formula}t+1. We will write {a mathematical formula}(ρ,t)⊨φ to mean that {a mathematical formula}φ∈Ltl is true at time {a mathematical formula}t∈N on run ρ. The rules defining when formulae are true (i.e., the semantics of LTL) are defined as follows, where {a mathematical formula}x∈Φ:{a mathematical formula}
      </paragraph>
      <paragraph>
       If {a mathematical formula}(ρ,0)⊨φ, we write {a mathematical formula}ρ⊨φ and say that ρ satisfies φ. We say that φ and ψ are equivalent if for all ρ we have {a mathematical formula}ρ⊨φ if and only if {a mathematical formula}ρ⊨ψ. A formula {a mathematical formula}φ∈Ltl is satisfiable if there is some run satisfying φ; moreover, it is satisfied by a Kripke structure K if it is satisfied by all its initial runs, that is, if, and only if, it is satisfied by all {a mathematical formula}ρ∈runs(K). As usual, we say that the size of an LTL formula φ, denoted by {a mathematical formula}|φ|, is its number of subformulae.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Computation tree logic
      </section-title>
      <paragraph>
       In order to express branching-time properties, we use Computation Tree Logic (CTL), a branching temporal logic that extends propositional logic with tense modalities and path quantifiers[20]. Specifically, CTL combines the tense operators X and U with the path quantifiers A and E; the path quantifier A means “on all paths…”, while E means “on some path…”. Formally, given a set Φ of Boolean variables, the syntax of CTL is defined as follows:{a mathematical formula} where {a mathematical formula}x∈Φ. Assuming the remaining classical connectives have been defined as usual, we can define the remaining CTL operators as follows:{a mathematical formula} Let {a mathematical formula}Ctl(Φ) denote the set of CTL formulae over Φ; when Φ is clear from the context, we write Ctl. CTL formulae are interpreted with respect to pairs {a mathematical formula}(K,s), where K is a Kripke structure and s is a state in K. We write {a mathematical formula}(K,s)⊨φ to mean that the CTL formula {a mathematical formula}φ∈Ctl is satisfied in state s of K. Formally, for Kripke structures K, states s in K, and {a mathematical formula}x∈Φ, we have:{a mathematical formula}
      </paragraph>
      <paragraph>
       If {a mathematical formula}(K,s0)⊨φ for all {a mathematical formula}s0∈S0, we write {a mathematical formula}K⊨φ and say that K satisfies φ. A CTL formula φ is satisfiable if {a mathematical formula}K⊨φ for some K. We say that φ and ψ are equivalent if {a mathematical formula}K⊨φ iff {a mathematical formula}K⊨ψ, for all K. We also say that the size of a CTL formula φ, denoted by {a mathematical formula}|φ|, is its number of subformulae.
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Computation trees
      </section-title>
      <paragraph>
       We sometimes find it convenient to adopt an alternative view of Kripke structures, where we unfold the transition relation R to obtain a computation tree. We now present the associated technical definitions for such unfoldings.
      </paragraph>
      <paragraph>
       First, we assume the standard definitions of a word, string, and prefix of a string. Where w is a finite word over some alphabet, we denote by {a mathematical formula}prefix(w) the set of non-empty prefixes of w. A tree over an alphabet Σ we define by a non-empty set {a mathematical formula}T⊆Σ+ of non-empty strings over Σ, such that
      </paragraph>
      <list>
       <list-item>
        {a mathematical formula}T∩Σ is a singleton (the root of the tree),
       </list-item>
       <list-item>
        T is closed under non-empty prefixes, i.e., {a mathematical formula}prefix(w)⊆T for every {a mathematical formula}w∈T, and
       </list-item>
       <list-item>
        {a mathematical formula}w∈T implies {a mathematical formula}wa∈T for some {a mathematical formula}a∈Σ.
       </list-item>
      </list>
      <paragraph>
       The set T then fixes the set of the vertices and there is an edge between vertices {a mathematical formula}w,w′∈T iff there is an {a mathematical formula}a∈Σ such that {a mathematical formula}w′=wa.
      </paragraph>
      <paragraph>
       A state-tree for a Kripke structure {a mathematical formula}K=(S,S0,R,π) is a tree κ over S such that {a mathematical formula}(s,s′)∈R whenever {a mathematical formula}ws,wss′∈T for some {a mathematical formula}w∈S⁎. An s-tree is a state-tree κ with root s (i.e., with {a mathematical formula}s∈κ). Observe that by condition (i) every state-tree is an s-tree for exactly one state s in S. If {a mathematical formula}s∈S0, an s-tree is also called an initial state-tree. By {a mathematical formula}trees(K,s) we denote the set of s-trees and by {a mathematical formula}trees(K) the set of initial state-trees for the Kripke structure K.
      </paragraph>
      <paragraph>
       By a computation tree we understand a tree on the set {a mathematical formula}V(Φ) of valuations over Φ. For {a mathematical formula}Ψ⊆Φ we have {a mathematical formula}κ|Ψ denote the restriction of κ to Ψ, i.e., for every {a mathematical formula}u∈T, {a mathematical formula}κ|Ψ(u)=κ(u)∩Ψ. Notice that every state-tree κ for a Kripke structure K induces a computation tree κ such that{a mathematical formula} In such a case κ is said to be a computation tree for K. If κ is an initial state-tree, the corresponding computation tree κ is said to be an initial computation tree. The set of all initial computation trees for K we denote by {a mathematical formula}trees(K). We refer to Fig. 4 for an illustration of this concept.
      </paragraph>
      <paragraph>
       By an unfolding of {a mathematical formula}K=(S,S0,R,π) we understand a maximal initial computation tree of K. Let {a mathematical formula}κ∈trees(K) be an initial state-tree for K such that {a mathematical formula}s0…sk∈κ implies {a mathematical formula}s0…sksk+1∈κ for every state {a mathematical formula}sk+1 with {a mathematical formula}skRsk+1. Then, the corresponding computation tree {a mathematical formula}κ:T→V for K is an unfolding of K. Each initial state {a mathematical formula}s∈S0 induces a unique unfolding. By {a mathematical formula}unfold(K) we denote the set of unfoldings of K.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      The simple reactive modules language
     </section-title>
     <paragraph>
      In this section, we describe the language we use for modelling multi-agent systems: the Simple Reactive Modules Language (srml). This language is a subset of the Reactive Modules Language (rml[2]) that is widely used in model checkers such as Mocha[4] and Prism[43]. The fragment we make use of, known as srml, was introduced by van der Hoek et al. [67] to study the complexity of model checking for the Alternating-time Temporal Logic (ATL) [3]. Our presentation of srml largely follows that in [67], except that while a formal semantics for srml was hinted at in [67], we here give a complete formal semantics for the language, showing how srml-defined systems induce computational runs and Kripke structures.
     </paragraph>
     <paragraph>
      The structures used to define agents in srml are known as modules. An srml module consists of:
     </paragraph>
     <list>
      <list-item>
       an interface, which defines the name of the module and lists the Boolean variables under the control of the module; and
      </list-item>
      <list-item>
       a number of guarded commands, which define the choices available to the module at every state.
      </list-item>
     </list>
     <paragraph>
      Guarded commands are of two kinds: those used for initialising the variables under the module's control (init guarded commands), and those for updating these variables subsequently (update guarded commands). A guarded command has two parts: a condition part (the “guard”) and a corresponding action part, which defines how to update the value of (some of) the variables under the control of a module. The intuitive reading of a guarded command {a mathematical formula}φ↝α is “if the condition φ is satisfied, then one of the choices available to the module is to execute the action α”. It is important to note that the truth of the guard φ does not mean that α will be executed: only that it is enabled for execution – i.e., that it may be chosen.
     </paragraph>
     <paragraph>
      An action α is a sequence of assignment statements. These statements define how (some subset of) the module's controlled variables should be updated if the guarded command is executed. If in some state no guarded command of a given module is enabled, then the values of the variables in that module are assumed to remain unchanged in the next state: the module has no choice.
     </paragraph>
     <paragraph>
      Here is an example of a guarded command:{a mathematical formula} The guard is the propositional logic formula {a mathematical formula}x∧y, so this guarded command will be enabled in any system state where both variables x and y take the value “⊤”. If the guarded command is chosen for execution, then the effect is that in the next state of the system, the variable x will take value ⊥, while y will take value ⊤. (The “prime” notation {a mathematical formula}x′ means “the value of variable x after the statement is executed”.)
     </paragraph>
     <paragraph>
      The following example illustrates the concrete syntax for modules:{a mathematical formula} This module, named toggle, controls a single Boolean variable, x. There are two init guarded commands and two update guarded commands. (The symbol “::” is a syntactic separator.) The init guarded commands of toggle define two choices for the initialisation of this variable: assign it the value ⊤ or the value ⊥. With respect to update guarded commands, the first command says that if x has the value ⊤, then the corresponding choice is to assign it the value ⊥, while the second command says that if x has the value ⊥, then it can subsequently be assigned the value ⊤. In other words, the module nondeterministically chooses a value for x initially, and then on subsequent rounds toggles this value. Notice that in this example, the init commands are nondeterministic, while the update commands are deterministic.
     </paragraph>
     <section label="4.1">
      <section-title>
       Formal definition
      </section-title>
      <paragraph>
       We now give a formal definition of the semantics of srml. Formally, a guarded command g over Boolean variables Φ is an expression{a mathematical formula} where φ and every {a mathematical formula}ψi is a propositional logic formula over Φ and each {a mathematical formula}xi is a member of Φ. Let {a mathematical formula}guard(g) denote the guard of g. Thus, in the above rule, {a mathematical formula}guard(g)=φ. We will require that no variable appears on the left hand side of two assignment statements in the same guarded command, that is, {a mathematical formula}x1′ through {a mathematical formula}xk′ are all distinct. The intended interpretation of g is that if the propositional formula φ evaluates to true against the valuation v corresponding to the current state of the system, then the statement is enabled for execution; executing the statement means evaluating each {a mathematical formula}ψi against the current state v of the system, and setting the corresponding variable {a mathematical formula}xi to the truth value obtained from evaluating {a mathematical formula}ψi in this way. We say that {a mathematical formula}x1,…,xk are the controlled variables of g, and denote this set by {a mathematical formula}ctr(g). If none of the guarded commands of a module is enabled, the values of all variables in {a mathematical formula}ctr(g) are left unchanged. In what follows, we will write skip as an abbreviation for the assignment that leaves the value of every variable controlled by a module unchanged.
      </paragraph>
      <paragraph>
       Now, recall that an init guarded command is only used to initialise the values of variables when the system begins execution. Full rml allows for quite sophisticated initialisation schemes, but in srml, it is assumed that the guards to init command are “⊤”, i.e., every init command is enabled for execution in the initialisation round of the system. We will also assume that in the assignment statements {a mathematical formula}x′:=ψ on the right hand side of an init command, the expressions ψ are simply Boolean constants, i.e., either ⊤ or ⊥. Formally, an srml module, {a mathematical formula}mi, is then defined as a triple:{a mathematical formula} where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Φi⊆Φ is the (finite) set of variables controlled by {a mathematical formula}mi;
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ii is a (finite) set of initialisation guarded commands, such that for all {a mathematical formula}g∈Ii, we have {a mathematical formula}ctr(g)⊆Φi; and
       </list-item>
       <list-item label="•">
        {a mathematical formula}Ui is a (finite) set of update guarded commands, such that for all {a mathematical formula}g∈Ui, we have {a mathematical formula}ctr(g)⊆Φi.
       </list-item>
      </list>
      <paragraph>
       An srmlarena A is then given by an {a mathematical formula}(n+2)-tuple:{a mathematical formula} where {a mathematical formula}N={1,…,n} is a set of agents, Φ is a set of Boolean variables, and for each {a mathematical formula}i∈N, {a mathematical formula}mi=(Φi,Ii,Ui) is an srml module over Φ that defines the choices available to agent i. We require that {a mathematical formula}{Φ1,…,Φn} forms a partition of Φ (so every variable in Φ is controlled by some agent, and no variable is controlled by more than one agent). For a propositional valuation {a mathematical formula}v⊆Φ, let {a mathematical formula}vi denote {a mathematical formula}v∩Φi.
      </paragraph>
      <paragraph>
       The size of an srml arena {a mathematical formula}A=(N,Φ,m1,…,mn), denoted by {a mathematical formula}|A|, is defined to be {a mathematical formula}|m1|+…+|mn|, where the size of a module {a mathematical formula}mi, denoted by {a mathematical formula}|mi|, is given by {a mathematical formula}Φi and the number of guards and assignment statements in such a module, which is polynomially bounded by the number of guarded commands multiplied by the number of variables controlled by {a mathematical formula}mi, that is, polynomially bounded by {a mathematical formula}(|Ii|+|Ui|)⁎|Φi|.
      </paragraph>
      <paragraph>
       For technical reasons, we introduce for every module {a mathematical formula}mi=(Φi,Ii,Ui) an auxiliary guarded command, {a mathematical formula}giskip given by:{a mathematical formula} Thus, executing {a mathematical formula}giskip leaves all values for the variables in {a mathematical formula}Φi unchanged.{sup:1}
      </paragraph>
      <paragraph>
       Given a module {a mathematical formula}mi=(Φi,Ii,Ui) and a valuation v, we define {a mathematical formula}enabledi(v) as the set of update guarded commands that are enabled at v, under the proviso that, if none of the guarded commands in {a mathematical formula}Ui is enabled, {a mathematical formula}giskip will be. Formally,{a mathematical formula} Observe that, defined in this way, {a mathematical formula}enabledi(v) is never empty, and will contain {a mathematical formula}giskip as the unique element if none of the guarded commands in {a mathematical formula}Ui is enabled.{sup:2}
      </paragraph>
      <paragraph>
       We now define a function that specifies the semantics of guarded commands. Let {a mathematical formula}g:φ↝x1′:=ψ1;⋯;xk′:=ψk be a guarded command in a module {a mathematical formula}mi that controls the variables in {a mathematical formula}Φi. Then, {a mathematical formula}execi(g,v) denotes the propositional valuation for the variables {a mathematical formula}Φi that would result from the execution of g on v. Notice that {a mathematical formula}execi(⋯) only gives a valuation for the variables {a mathematical formula}Φi controlled by {a mathematical formula}mi; it does not specify the value of variables controlled by other modules. Formally, the function {a mathematical formula}execi(⋯) is defined for guarded command {a mathematical formula}g=φ↝x1′:=ψ1;⋯;xk′:=ψk and valuation v as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The behaviour of an srml arena is obtained by executing enabled guarded commands, one for each module, in a synchronous and concurrent way. A joint guarded command{a mathematical formula}J=(g1,…,gn) is a profile of guarded commands, one for each module. We extend the notations from guarded commands to joint guarded commands in the obvious way. In particular we write{a mathematical formula} Moreover, we use{a mathematical formula} to denote the execution of a joint guarded command {a mathematical formula}J=(g1,…,gn) at valuation v. Then, the deterministic execution of an srml arena proceeds in rounds. In the first round, the choices available to a module {a mathematical formula}mi correspond to the initialisation guarded commands {a mathematical formula}Ii of {a mathematical formula}mi; the module selects one of these for execution; call this guarded command {a mathematical formula}gi. The result of the choice made by {a mathematical formula}mi is defined to be {a mathematical formula}execi(gi,v⊥). The collection of choices made by all players then defines the initial valuation that appears in the run. In subsequent rounds, the choices available to a module {a mathematical formula}mi correspond to the update guarded commands that are enabled for execution by the valuation that was produced on the previous round. Again, each player selects one such enabled guarded command for execution, and the collective result of these choices defines the next valuation that appears in the run, and so on. More formally, the deterministic execution of an srml arena {a mathematical formula}A=(N,Φ,m1,…,mn) produces a run {a mathematical formula}ρ:N→V such that, for some joint guarded command {a mathematical formula}J∈I1×…×In, we have {a mathematical formula}ρ[0]=exec(J,v⊥) and, for all {a mathematical formula}t&gt;0, there is some joint command {a mathematical formula}J∈enabled(ρ[t−1]) with {a mathematical formula}ρ[t]=exec(J,ρ[t−1]). An srml arena A may allow different runs, depending on which joint guarded commands are selected for execution, and the set of runs an arena A permits we will denote by {a mathematical formula}runs(A).
      </paragraph>
      <paragraph>
       An srml arena {a mathematical formula}A=(N,Φ,m1,…,mn) can also be executed nondeterministically, in which case it produces a computation tree κ. For any such computation tree there is some joint initial guarded command {a mathematical formula}J∈I1×…×In, such that {a mathematical formula}exec(J,v⊥)∈κ and, for all {a mathematical formula}v0…vk and {a mathematical formula}v0…vkvk+1 in κ, there is some enabled J in {a mathematical formula}enabled(vk) with {a mathematical formula}exec(J,vk)=vk+1. An arena A may allow multiple computation trees, and the set of computation trees an arena A allows we denote by {a mathematical formula}trees(A). Since bisimilar trees satisfy the same set of both LTL and CTL formulae, to simplify the presentation of our results we may allow {a mathematical formula}trees(A) – and {a mathematical formula}trees(K), with K a Kripke structure – to be closed under bisimulation [38].
      </paragraph>
      <paragraph label="Example 1">
       To illustrate these concepts, consider the following example of an SRML arena. Let {a mathematical formula}Φ={x,y} and consider the srml arena{a mathematical formula} where agent i controls x and agent j controls y and {a mathematical formula}mi and {a mathematical formula}mj are further specified as in Fig. 5. Thus,{a mathematical formula}
      </paragraph>
      <paragraph>
       Furthermore, observe that {a mathematical formula}exec((gi1,gj1),v⊥)={x,y}, {a mathematical formula}exec((gi3,gj3),{x,y})={x}, {a mathematical formula}exec((gi5,gj3),{x})={x}, and {a mathematical formula}exec((giskip,gj4),∅)=∅. It follows that {a mathematical formula}{x,y},{x},∅,∅,… is a run in {a mathematical formula}runs(A). By a similar argument, it can also readily be appreciated that the (partial) computation tree in Fig. 4 depicts the initial part of a computation tree contained in {a mathematical formula}trees(A). Fig. 6 further illustrates the transitions between valuations that are induced by enabled guarded commands.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Kripke-based and logic-based semantics
      </section-title>
      <paragraph>
       Above, we have presented a formal semantics for srml, showing how arenas can be executed deterministically (leading to runs), or non-deterministically (leading to computation trees). We now present two further semantics, both of which are used extensively in what follows. In the first, we show how srml arenas induce Kripke structures, while in the second, we see how the semantics of srml arenas can be defined in terms of temporal logic formulae.
      </paragraph>
      <paragraph>
       Whenever an enabled joint guarded command of an srml arena is executed, the system it describes can be seen as transitioning from one state to the next. Moreover, as the set of enabled commands at a state only depends on the set of propositional set to true in that state, states with the same associated valuation can be viewed as identical. Thus, every srml arena induces a finite Kripke structure. For instance, a comparison with Fig. 6 reveals that the Kripke structure in Fig. 3 models the behaviour of the srml arena of Example 1 in this way.
      </paragraph>
      <paragraph>
       At this point, it is useful to remind ourselves that one of the reasons for using srml specifications is that they allow a succinct representation of models that capture the possible (infinite) computations of a distributed, concurrent, and multi-agent (computer) system. For technical reasons, however, in some cases it is useful to explicitly refer to the Kripke structure – i.e., transition system – that is induced by an arena {a mathematical formula}A=(N,Φ,m1,…,mn); such a structure we denote by {a mathematical formula}KA, which may in general be exponential in the size of A. Formally, we have:
      </paragraph>
      <paragraph label="Lemma 2">
       Kripke-based semanticsFor every arena A, there is a Kripke structure{a mathematical formula}KAof size at most exponential in{a mathematical formula}|A|with the same set of runs and the same set of computation trees, i.e., with:{a mathematical formula}Likewise, for every Kripke structure{a mathematical formula}K=(S,S0,R,π), there exists ansrmlarena{a mathematical formula}AKcontaining a singlesrmlmodule{a mathematical formula}mK=(Φ∪S,IK,UK)of linear size with respect to{a mathematical formula}|K|whose runs and computation trees when restricted to Φ are exactly those in K, i.e.,{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       An algorithm to construct Kripke structures {a mathematical formula}KA for srml arenas A is given in Fig. 12 in the Appendix.To prove the second half of the lemma, we now provide a general explicit construction of an srml module based on a given Kripke structure. Thus, let {a mathematical formula}K=(S,S0,R,π) with {a mathematical formula}π:S→V(Φ). Define the srml module {a mathematical formula}mK for the Kripke structure K as in Fig. 7. Observe that this construction introduces new variables, in addition to the variables Φ of the Kripke structure. Specifically, we introduce a new variable for each state of the Kripke structure.{sup:3}In the module in Fig. 7, {a mathematical formula}s0′:=⊤; means that the initial state is {a mathematical formula}s0. In the update rules the transition relation R is modelled as follows: for each {a mathematical formula}(s,s′)∈R we have a rule indicating that at s we can choose {a mathematical formula}s′ as a next state where propositions {a mathematical formula}p,… hold. All other states are set to ⊥ to indicate that the system is currently not in those states.To see that the size of {a mathematical formula}mK is linear in the size of K, observe that we have exactly one controlled variable for each state of the Kripke structure as well as exactly one update guarded command for each pair in R. On the other hand, the fact that both K and {a mathematical formula}mK have the same sets of runs and computation trees (when the trees induced by {a mathematical formula}AK are restricted to the variables Φ) immediately follows from the construction in Fig. 7.  □
      </paragraph>
      <paragraph>
       We now present another lemma that will also be useful subsequently. The lemma shows, firstly, that for every arena A, it is possible to define an LTL formula {a mathematical formula}ThLTL(A) that acts as the LTL theory of A, in the sense that the runs satisfying {a mathematical formula}ThLTL(A) are exactly the runs of A. Formally, we have the following result:
      </paragraph>
      <paragraph label="Lemma 3">
       Logic-based semanticsFor every arena A of size{a mathematical formula}|A|, there is an LTL formula{a mathematical formula}ThLTL(A)of size polynomial in{a mathematical formula}|A|such that for all{a mathematical formula}ρ:N→2Φ,{a mathematical formula}Moreover,{a mathematical formula}ThLTL(A)can be computed in time polynomial in the size of A.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}A=(N,Φ,m1,…,mn) be the given arena. We define the formula {a mathematical formula}ThLTL(A) as the conjunction of two formulae, which roughly speaking define the effect of the initialisation and update commands in A, respectively:{a mathematical formula} We begin by defining a temporal predicate {a mathematical formula}Unch(Ψ), which asserts that the variables {a mathematical formula}Ψ⊆Φ take the same value in the next state that they do in the present state (i.e., they remain unchanged):{a mathematical formula} Then, we define the effect of a single initialisation guarded command.{a mathematical formula} The expression {a mathematical formula}Initi then captures the semantics of initialisation commands (we write ⊕ as an abbreviation of the “exactly one” operator – which is equivalent to the “exclusive-or” operator in the binary case):{a mathematical formula} Then:{a mathematical formula} Next we define the semantics of update rules. Again, we do this in two parts. We first define the effect of a single update guarded command:{a mathematical formula} We then define the overall effect of i's update commands:{a mathematical formula} Finally:{a mathematical formula} In order to show that {a mathematical formula}ρ∈runs(A) if, and only if, {a mathematical formula}ρ|Φ⊨ThLTL(A), one proceeds by induction. Moreover, that {a mathematical formula}ThLTL(A) is polynomial in the size of A immediately follows from the construction of the LTL formula, and that it can be computed in time polynomial in the size of A follows similarly.  □
      </paragraph>
      <paragraph>
       Hereafter, we will write {a mathematical formula}Th(A) for {a mathematical formula}ThLTL(A). Moreover, we will say that a temporal logic formula φ characterises or represents the behaviour of an arena A if φ is logically equivalent to {a mathematical formula}Th(A). It should also be easy to see that the constructions of {a mathematical formula}Th(A), for arenas, can be restricted to characterise the behaviour of (subsets of) single modules. In particular, we write {a mathematical formula}Th(mi) for the formula that characterises the behaviour of module {a mathematical formula}mi, and write {a mathematical formula}Th(m−i) for the formula that characterises the behaviour of the set of modules {a mathematical formula}{mj:j∈N and i≠j}.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Reactive modules games
     </section-title>
     <paragraph>
      We can now introduce the game model we work with in the remainder of this article. The games we consider are called reactive modules games (RMGs) and have two components. The first component is an arena: this defines the players in the game, the variables they control, and the choices available to these players in every game state. The arena in an RMG plays a role analogous to that of a game form in conventional game theory [53, p. 201]: while it defines players and their choices, it does not specify the preferences of players. Preferences in RMGs are specified by the second component of an RMG: every player i is assumed to be associated with a goal{a mathematical formula}γi, which in RMGs will be a temporal logic formula. The idea is that players desire to see their goal satisfied. Moreover, as one would expect, they are indifferent between two outcomes that satisfy their goal, and indifferent between outcomes that do not achieve it.
     </paragraph>
     <paragraph>
      Formally, an RMG G is given by a structure:{a mathematical formula} where:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}A=(N,Φ,m1,…,mn) is an srml arena with components as defined earlier;
      </list-item>
      <list-item label="•">
       for all {a mathematical formula}i∈N, the formula {a mathematical formula}γi is the goal of player i, represented as a temporal logic formula; in what follows, we consider both LTL and CTL as possible goal languages.
      </list-item>
     </list>
     <paragraph>
      Games in which all players have goals expressed as LTL formulae are called LTL RMGs, while games in which players have goals expressed as CTL formulae are called CTL RMGs. Both types of game are played by each player i selecting a strategy{a mathematical formula}σi that will define how to make choices over time. In the case of LTL RMGs strategies will be deterministic, whereas for CTL RMGs strategies are non-deterministic. (Formal definitions will be given shortly.) Then, once every player i has selected a strategy {a mathematical formula}σi, a strategy profile{a mathematical formula}σ→=(σ1,…,σn) results and the game has an outcome, which given the nature of the strategies will be:
     </paragraph>
     <list>
      <list-item label="•">
       A run (an infinite word), denoted by {a mathematical formula}ρ(σ→), for LTL RMGs;
      </list-item>
      <list-item label="•">
       A Kripke structure, denoted by {a mathematical formula}Kσ→, for CTL RMGs.
      </list-item>
     </list>
     <paragraph>
      In either case, the outcome will determine whether or not each player's goal is or is not satisfied. Recall that LTL formulae are interpreted on runs and CTL formulae on Kripke structures. In order to simplify notation, whenever the game is clear from the context, we will write {a mathematical formula}σ→⊨φ for both {a mathematical formula}ρ(σ→)⊨φ, if {a mathematical formula}φ∈Ltl, and {a mathematical formula}Kσ→⊨φ, if {a mathematical formula}φ∈Ctl. Although neither strategies nor outcomes {a mathematical formula}ρ(σ→) and {a mathematical formula}Kσ→ have been formally given yet (defined in the next sections), we are now in a position to define a preference relation {a mathematical formula}≿i over outcomes for each player i with goal {a mathematical formula}γi. For strategy profiles {a mathematical formula}σ→ and {a mathematical formula}σ→′, we say that{a mathematical formula} We say that player i strictly prefers outcome σ over {a mathematical formula}σ′ if {a mathematical formula}σ≿iσ′ but not {a mathematical formula}σ′≿iσ, and is indifferent between σ and {a mathematical formula}σ′ whenever both {a mathematical formula}σ≿iσ′ and {a mathematical formula}σ′≿iσ. As defined above, players strictly prefer outcomes that satisfy their goals over outcomes that do not, and will be indifferent otherwise. It can easily be established that the preference relations {a mathematical formula}≿i satisfy the standard requirements of reflexivity, transitivity, and completeness, so that they can play their conventional role in subsequent game-theoretic definitions (see, e.g., [53, p. 7]). Here, we state the lemma but omit the straightforward proof.
     </paragraph>
     <paragraph label="Lemma 4">
      Each relation{a mathematical formula}≿i, as defined above, is reflexive, transitive, and complete.
     </paragraph>
     <paragraph>
      We now define the standard solution concept of Nash equilibrium for RMGs. For this we need one small additional piece of notation. Given a strategy profile {a mathematical formula}σ→=(σ1,…,σi−1,σi,σi+1,…,σn) and a strategy {a mathematical formula}σi′ for player i, then by {a mathematical formula}(σ→−i,σi′) we will denote the strategy profile that is the same as {a mathematical formula}σ→ except that the strategy for player i is {a mathematical formula}σi′, that is:{a mathematical formula} Then {a mathematical formula}σ→ is said to be a Nash equilibrium of G if for all players i and all strategies {a mathematical formula}σi′ for player i, we have{a mathematical formula} Hereafter, we let {a mathematical formula}NE(G) be the set of (pure strategy) Nash equilibria for an RMG G. As is usually the case in game theory, it is possible that {a mathematical formula}NE(G)=∅ (there are no equilibria), or that {a mathematical formula}NE(G) contains just one, or multiple equilibria; there may even be infinitely many equilibria. If there are no equilibria, then the system is inherently unstable – this is one of the key system properties that we will be interested in checking, in the form of the Non-Emptiness problem, described below. If there are multiple equilibria, then this presents the players in the game with a coordination problem: they need to find some way of fixing on one of the equilibria. One way for players to do this is to look for focal points, that is, equilibria that “stand out” from others in the sense that they have certain distinctive features; see, e.g., [61]. In the RMGs setting, for example, an equilibrium that satisfied the goals of all players might be regarded as particularly distinctive. From the point of view of a system designer, the existence of multiple equilibria may not be an issue if all of these equilibria satisfy certain desirable properties. This is another key computational problem that we study, in the form of the A-Nash decision problem, described below.
     </paragraph>
     <paragraph>
      Before studying LTL and CTL RMGs in detail, we should make explicit some important assumptions that underpin our work. The game-theoretic interpretation that we place on RMGs essentially corresponds to the standard game-theoretic model of non-cooperative strategic form games, and in common with this work, we make two assumptions. First, we assume that the game is common knowledge to all players, i.e., all the players know the arena A and goals {a mathematical formula}γi, and know that other players know this, etc. Second, we assume that all players act rationally, taking into account the fact that all other players act rationally. We emphasise that these are common (although not universal) assumptions in game theory. Dropping them would be an interesting topic for future work, but beyond the present paper.
     </paragraph>
     <section label="5.1">
      <section-title>
       LTL reactive modules games
      </section-title>
      <paragraph>
       Players in an LTL RMG possess LTL goals and choose deterministic strategies. The interaction between (i.e., parallel composition of) such strategies will determine a unique run of the arena, that is, an infinite sequence of states/valuations, which can be used as the LTL model against which to interpret players' goals.
      </paragraph>
      <paragraph>
       Let us fix some notation. We will write {a mathematical formula}Φ−i for {a mathematical formula}Φ∖Φi and let {a mathematical formula}Vi (respectively, {a mathematical formula}V−i) denote the set of valuations to variables in {a mathematical formula}Φi (respectively, {a mathematical formula}Φ−i).
      </paragraph>
      <paragraph>
       For LTL RMGs, we model strategies as finite state machines with output – technically, deterministic Moore machines. The input language of such a machine representing a strategy for player i corresponds to the choices of other players, i.e., assignments for variables that other players control, {a mathematical formula}Vi, while outputs are variable assignments for the player implementing the strategy, i.e., {a mathematical formula}Vi.
      </paragraph>
      <paragraph>
       Representing strategies as finite state machines has a number of advantages. First, as the name suggests, it is a finite representation scheme. A more mathematically abstract representation for strategies would be model them as functions {a mathematical formula}fi:V−i⁎→Vi, i.e., functions that map a sequence of choices for other players to a choice for player i. The problem with this representation from a computational point of view is that the domain of such functions is infinite, which raises substantial difficulties if we want to study decision problems that take such strategies as input. Second, while it may appear that finite state machine representations are weaker than the more mathematically abstract representation, this is in fact not the case if we are only concerned with players whose goals are expressed as temporal logic formulae. In such cases, all we need are finite state machine strategies: the existence of a “general” strategy for a player that will accomplish a player's goal implies the existence of a finite state machine strategy that will do the same job. Finally, the use of finite state machine strategies is, in fact, standard in the literature on iterated games [6]. These and related questions are discussed in more detail in [29].
      </paragraph>
      <paragraph>
       Now, given {a mathematical formula}A=(N,Φ,m1,…,mn), an srml arena, we define a deterministic strategy for module {a mathematical formula}mi=(Φi,Ii,Ui) as a structure {a mathematical formula}σi=(Qi,qi0,δi,τi), where
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}Qi is a finite and non-empty set of states,
       </list-item>
       <list-item label="•">
        {a mathematical formula}qi0∈Qi is the initial state,
       </list-item>
       <list-item label="•">
        {a mathematical formula}δi:Qi×V−i→Qi is a transition function, and
       </list-item>
       <list-item label="•">
        {a mathematical formula}τi:Qi→Vi is an output function.
       </list-item>
      </list>
      <paragraph>
       Note, in particular, that not all strategies for a given module will comply with that module's specification. For instance, if the only guarded command of a module {a mathematical formula}mi has the form {a mathematical formula}⊤↝x′:=⊥, then a strategy for {a mathematical formula}mi should not prescribe {a mathematical formula}mi to set x to true under any contingency. Thus, given an arena {a mathematical formula}A=(N,Φ,m1,…,mn), a strategy {a mathematical formula}σi=(Qi,qi0,δi,τi) for module {a mathematical formula}mi is consistent with{a mathematical formula}mi if the following two conditions are satisfied:
      </paragraph>
      <list>
       <list-item>
        for the initial state {a mathematical formula}qi0, we have {a mathematical formula}τi(qi0)=execi(g,v⊥) for some {a mathematical formula}g∈I1×…×In, and
       </list-item>
       <list-item>
        for all {a mathematical formula}q,q′∈Qi and {a mathematical formula}v=vi∪v−i∈V such that {a mathematical formula}δ(q,v−i)=q′ and {a mathematical formula}vi=τi(q), we have {a mathematical formula}τi(q′)=execi(gi,v) for some {a mathematical formula}gi∈enabledi(v).
       </list-item>
      </list>
      <paragraph>
       Note that, defined in this way, strategies implicitly have perfect information: the player can completely and correctly perceive the choices of other players in the game. Clearly this is ultimately too strong an assumption in many settings, but it will suffice as a first approximation. Also, we are implicitly assuming strategies have finite memory (although we impose no bounds on memory size).
      </paragraph>
      <paragraph>
       If a strategy {a mathematical formula}σi is consistent with module {a mathematical formula}mi, we simply say that {a mathematical formula}σi is a strategy for{a mathematical formula}mi. Given an srml arena {a mathematical formula}A=(N,Φ,m1,…,mn), we say that a strategy profile {a mathematical formula}σ→=(σ1,…,σn) is consistent with A if each {a mathematical formula}σi is consistent with {a mathematical formula}mi. In the remainder of the article, we restrict our attention to consistent strategies, and so from here on, the term “strategy” should be understood to mean “consistent strategy”.
      </paragraph>
      <paragraph>
       Finally, because each strategy {a mathematical formula}σi is deterministic, there is a unique run induced by {a mathematical formula}σ→, which we denote by {a mathematical formula}ρ(σ→).
      </paragraph>
      <paragraph label="Example 5">
       Consider once more the srml arena of Example 1 and the (deterministic) strategies depicted in Fig. 8. First consider the strategy profile {a mathematical formula}(σi,σj), which gives rise to the computation run that starts with:{a mathematical formula} Here, the machine strategy {a mathematical formula}σi subsequently visits the states {a mathematical formula}qi0,qi,qi,qi′,qi0,… and {a mathematical formula}σj the states {a mathematical formula}qj0,qj0,qj,qj,qj0,…. Both strategies comply with their respective modules. For instance, the transition {a mathematical formula}δ(qi,∅)=qi′ in {a mathematical formula}σi is warranted on basis of the guarded command {a mathematical formula}gi5, i.e., {a mathematical formula}x↝x′:=y. Notice that {a mathematical formula}{x}⊭y and, as {a mathematical formula}execi(gi5,{x})=∅=τ(qi′), condition {a mathematical formula}(ii) above is satisfied. By contrast strategy {a mathematical formula}σi′ does not comply with {a mathematical formula}mi. To see this, consider the transition {a mathematical formula}δ(ri′,{y})=ri0 and observe that {a mathematical formula}gi4, i.e., {a mathematical formula}y↝x′:=¬x, is the only update guarded command that is enabled at valuation {a mathematical formula}{y}. Yet, {a mathematical formula}τi(ri0)=∅, whereas, as {a mathematical formula}{y}⊨¬x and thus {a mathematical formula}execi(gi4,{y})={x}, condition {a mathematical formula}(ii) above would require that {a mathematical formula}τi(ri0)={x}.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       CTL reactive modules games
      </section-title>
      <paragraph>
       Players in a CTL RMG possess CTL goals and have non-deterministic strategies at their disposal. Intuitively, whereas deterministic strategies can be seen as controllers, which resolve the non-determinism of the system by choosing a single computation path, non-deterministic strategies should be understood as supervisors, which disable undesirable behaviours of the system but leave the remaining choices to be selected/executed in a non-deterministic manner.
      </paragraph>
      <paragraph>
       Thus, whereas a profile {a mathematical formula}σ→ of deterministic strategies can be associated with a unique and infinite sequence of states/valuations of the system, a profile of non-deterministic strategies can be associated with a unique and infinite tree of system states/valuations – where only the non-deterministic choices made by {a mathematical formula}σ→ are left in the tree.
      </paragraph>
      <paragraph>
       The definition of non-deterministic strategies is a simple generalisation of that of deterministic ones, where only the transition function is redefined, as follows: {a mathematical formula}δi:Qi×V−i→2Qi∖{∅}. Finally, the definitions of outcome (that is, of {a mathematical formula}Kσ→), consistency, and Nash equilibrium with respect to profiles {a mathematical formula}σ→ of consistent non-deterministic strategies are straightforwardly extended.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Example: rational mutual exclusion
      </section-title>
      <paragraph>
       Mutual exclusion algorithms (MEAs) play a fundamental role in distributed computing. As the name suggests, they are designed to ensure mutual exclusion, i.e., that in concurrent settings two processes or agents cannot simultaneously enter a “critical region” (CR). Classic examples of MEAs are Peterson's algorithm [55], Lamport's bakery algorithm [44], and Ricart and Agrawala's improvement of the latter [59]. We now show how such an algorithm can be defined using srml, how it ensures mutual exclusion, and how rational action can moreover guarantee non-starvation. Non-starvation is the desirable property that no process or agent is perpetually denied access to a shared resource; in the context of MEAs, the resource in question is access to the CR.
      </paragraph>
      <paragraph>
       In a ring-based MEA, the agents are organised in a cycle along which a “token” is passed – similar to a distributed implementation of a round-robin scheduler [40]. Possession of the token signifies exclusive permission to enter the CR, i.e., an agent can enter the CR only if she is in possession of the token. The modules in Fig. 9 specify a srml arena{a mathematical formula} which implements a three-agent distributed ring-based MEA (cf., [17], pp. 474–475). The algorithm easily extends to settings with any finite number of agents.
      </paragraph>
      <paragraph>
       Thus, in {a mathematical formula}Arbme each agent i controls two variables, {a mathematical formula}xi and {a mathematical formula}yi. Variable {a mathematical formula}xi being true means that agent i has the token and enters the CR, whereas {a mathematical formula}yi indicates that agent i has the token and passes it to the next agent {a mathematical formula}i+1. (We assume arithmetic modulo 3 throughout the example). In the initial state, agent 2 has the token and passes it on to agent 0; no agent is in the CR. On possession of the token, each agent can decide whether to enter the CR or to pass on the token. Once an agent i is in the CR, i.e., if {a mathematical formula}xi is true, it can remain there as long as it suits him. On exiting the CR, i.e., if {a mathematical formula}¬xi∧yi holds, agent i immediately passes the token on to agent {a mathematical formula}i+1. The behaviour of the system is described by the modules' specifications. The Kripke structure for arena {a mathematical formula}Arbme is depicted in Fig. 10 and Table 1 further illustrates the dynamics of the system.
      </paragraph>
      <paragraph>
       Observe that, in every state – and thus at every time and on all runs of {a mathematical formula}Arbme – at most one agent has the token and can enter the CR. Hence, the formula{a mathematical formula} is satisfied, which signifies that the protocol guarantees mutual exclusion.
      </paragraph>
      <paragraph>
       The system, however, still allows for many different runs, some of which are undesirable, e.g., if at some point some agent enters the CR and does not leave it ever afterwards. Such behaviour would violate the desired starvation-free property. This is even the case if we assume that each agent i has as a goal to have the token (and thus the ability to enter the CR) infinitely often, i.e., {a mathematical formula}γi=GF(xi∨yi), and we restrict our attention to runs that are sustained by a Nash equilibrium. If all agents adopt a strategy in which they enter the CR and remain there for ever when given the opportunity, a Nash equilibrium results in which two agents can never enter the CR.
      </paragraph>
      <paragraph>
       If, on the other hand, each agent i has as a goal the CTL formula {a mathematical formula}γi=GF¬xi, i.e., to be out of the CR infinitely often, then each of them can guarantee its own goal to be satisfied by simply adopting any strategy according to which it exits the CR after a finite period of time in possession of the token. Thus, no agent will perpetually be excluded from having the opportunity to enter the CR and each agent rationally follows a starvation-free protocol. Under these preferences, a powerful property of our game-like specification of the ring-based mutual exclusion algorithm is that on all runs that are sustained by a Nash equilibrium, the distributed system is guaranteed to be starvation-free! Thus, safety (mutual exclusion) and starvation-freeness for the distributed system can all be uniformly dealt with within RMGs.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Example: deferred acceptance
      </section-title>
      <paragraph>
       The deferred acceptance algorithm, as proposed in 1962 by David Gale and Lloyd Shapley [24], has been tremendously influential both in theory and in practice. The power of this two-sided allocation scheme lies in its very simplicity and its ramifications have numerous and various practical applications to, e.g., kidney exchange, school choice, and the assignment of doctors to hospitals (also see [60], [27], [45]).
      </paragraph>
      <paragraph>
       Agents are divided in two disjoint finite groups, m-agents and f-agents, and each agent has preferences over the agents in the other group. The goal is to find a stable matching, that is, a pairing of m-agents and f-agents for which there are no matched pairs {a mathematical formula}(mi,fi) and {a mathematical formula}(mj,fj) such that {a mathematical formula}mi and {a mathematical formula}fj prefer one another to {a mathematical formula}fi and {a mathematical formula}mj, respectively. The deferred acceptance algorithm (DA) is a scheme in which each m-agent proposes to one of his most preferred f-agents. If the offer is accepted the engagement stands until a more preferred m-agent comes along and proposes to f-agent. If the offer is rejected, the m-agent strikes the f-agent from his list and proposes to one of his next most preferred f-agents. The algorithm is guaranteed to terminate and to yield a stable matching.
      </paragraph>
      <paragraph>
       We can model and reason about the DA setting within the RMG framework. We assume there to be m-agents{a mathematical formula}m1,…,mk and an equal number of f-agents{a mathematical formula}f1,…,fk. Every m-agent {a mathematical formula}mi controls a set of variables {a mathematical formula}Φmi={xi1,…,xik,zi1,…,zik}, where {a mathematical formula}xij indicates that m-agent {a mathematical formula}mi proposes to f-agent {a mathematical formula}fj, while {a mathematical formula}zij records that {a mathematical formula}mi has proposed to {a mathematical formula}fj in the past. Similarly, every f-agent {a mathematical formula}fj controls a set of variables {a mathematical formula}Φfj={y1j,…,ykj}, where {a mathematical formula}yij signifies that f-agent {a mathematical formula}fj provisionally accepts {a mathematical formula}mi's proposal.
      </paragraph>
      <paragraph>
       In our setting, each agent has dichotomous preferences, dividing the agents of the other group into those that are approved and those that are not approved. Let for every m-agent {a mathematical formula}mi the set of indices of approved f-agents be denoted by {a mathematical formula}Fi and for every f-agent {a mathematical formula}fj the set of indices of approved m-agents by {a mathematical formula}Mj. That is, {a mathematical formula}Fi={j:miapprovesfj} and {a mathematical formula}Mj={i:fjapprovesmi}. The preferences of m-agent {a mathematical formula}mi and f-agent {a mathematical formula}fj are then given by{a mathematical formula} respectively, that is, every m-agent wishes to be eventually for ever matched with one of his approved f-agents, and every f-agent with one of her approved m-agents. In our setting with dichotomous preferences, stability means that there is no m-agent {a mathematical formula}mi and no f-agent {a mathematical formula}fj such that {a mathematical formula}fj is one of {a mathematical formula}mi's approved f-agents and {a mathematical formula}mi is one of {a mathematical formula}fj's approved m-agents, and neither {a mathematical formula}mi is matched to one of his approved f-agents and {a mathematical formula}fj is not matched with one of her approved m-agents. If {a mathematical formula}j∈Fmi and {a mathematical formula}i∈Mj, we say that {a mathematical formula}(i,j) is a blocking pair and let {a mathematical formula}X⁎ denote the set of blocking pairs. Then,{a mathematical formula} signifies that on every computation path eventually stable matchings will obtain for ever after, a desirable property.
      </paragraph>
      <paragraph>
       The execution of the DA algorithm takes place over several rounds. We assume that, in every odd round, m-agents that are not engaged can (non-deterministically) propose to any of the f-agents he has not proposed to before. By contrast, in every even round each of the f-agents can (non-deterministically) engage any m-agent that proposed to her in the previous round or, alternatively, decide to stay with her current fiancé, if any, and remain single otherwise. Observe that once an f-agent is engaged, she will be engaged for ever after, be it not necessarily to the same m-agent. These provisions are laid down by the modules depicted in Fig. 11. It is worth observing that these specifications are independent of the agents' preferences and that they guarantee that none of the agents will be engaged with more than one agent at any one time.
      </paragraph>
      <paragraph>
       Obviously, {a mathematical formula}φstability does not hold in every computation tree of the resulting RMG {a mathematical formula}GDA: an f-agent may very well accept an unfavourable offer and stick to it, even if one of her approved m-agents is rejected by all of his approved f-agents. More surprisingly, {a mathematical formula}φstability does hold not even hold in every run that is sustained by a Nash equilibrium. To see this, consider the case with two m-agents, {a mathematical formula}m1 and {a mathematical formula}m2, and two f-agents, {a mathematical formula}f1 and {a mathematical formula}f2, such that both m-agents approve of {a mathematical formula}f1, but not of {a mathematical formula}f2, and both f-agents approve of {a mathematical formula}m1, but not of {a mathematical formula}m2. Thus, {a mathematical formula}m1 and {a mathematical formula}fi are the only blocking pair. Let, furthermore, {a mathematical formula}m1 and {a mathematical formula}m2 adopt strategies in which they propose in the first round to {a mathematical formula}f2 and {a mathematical formula}f1, respectively, and {a mathematical formula}f1 one in which she invariably accepts offers from {a mathematical formula}m2 only. Then, if {a mathematical formula}f2 accepts {a mathematical formula}f1's proposal in the first round, a non-stable matching will prevail ever after, that is, {a mathematical formula}φstability will fail to hold forever. Even though {a mathematical formula}m1's and {a mathematical formula}f1's strategies may seem irrational and leads to neither the former's nor the latter's goal being satisfied, they cannot offset each others' folly by choosing another strategy. As, moreover, {a mathematical formula}m2 and {a mathematical formula}f2 are fully satisfied with the outcome, it follows that the strategy profile described above is a Nash equilibrium.
      </paragraph>
      <paragraph>
       If, however, the situation had been different and all m-agents, rather than wishing to end up with an approved f-agent, weaken their goals to and aim to have at least proposed to all approved f-agents before proposing to a non-approved f-agent, all (non-deterministic) computations sustained by a Nash equilibrium will satisfy {a mathematical formula}φstability. To appreciate this, assume that some blocking pair {a mathematical formula}mi and {a mathematical formula}fj ends up to be forever unmatched with any of their approved agents. Then, either {a mathematical formula}mi has successfully proposed to an non-approved f-agent before proposing to {a mathematical formula}fj or {a mathematical formula}fj has declined a proposal by {a mathematical formula}mi. In the former case, {a mathematical formula}mi can achieve his goal by diverting to strategy in which he proposes to his approved f-agents before proposing to the other agents. In the latter case, {a mathematical formula}fj would have obtained a better outcome if she had accepted {a mathematical formula}mi's proposal and stuck with it.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Equilibrium analysis
     </section-title>
     <paragraph>
      In this section, we study the following game-theoretic decision problems for RMGs:
     </paragraph>
     <list>
      <list-item label="•">
       Realizability: whether a player can guarantee the satisfaction of a temporal formula within a given arena;
      </list-item>
      <list-item label="•">
       Non-emptiness: whether a given game has at least one Nash equilibrium;
      </list-item>
      <list-item label="•">
       NE-membership: whether a strategy profile forms a Nash equilibrium; and
      </list-item>
      <list-item label="•">
       E-Nash and A-Nash: whether a temporal logic formula can be satisfied on some or on all Nash equilibria of a given game.
      </list-item>
     </list>
     <paragraph>
      In order to solve the problems above mentioned, we first note that, similar to the case of Kripke structures, any strategy {a mathematical formula}σi for a player i can be specified by an srml module. We will describe the construction of modules for non-deterministic strategies; clearly, the construction for deterministic strategies appears as a, simpler, special case.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}m(σi)=(Φi′,Ii′,Ui′) be the module specifying some {a mathematical formula}σi=(Qi,qi0,δi,τi) for a module {a mathematical formula}mi=(Φi,Ii,Ui). With each state {a mathematical formula}qi∈Qi, we associate a fresh propositional variable, which, for presentational convenience, we will denote by {a mathematical formula}qi as well. The module {a mathematical formula}m(σi) then controls the variables {a mathematical formula}Φi′=Φi∪Qi. The init part {a mathematical formula}Ii′ of {a mathematical formula}mi(σi) contains a single guarded command:{a mathematical formula} We then use the update commands {a mathematical formula}Ui′ of the module {a mathematical formula}mi(σi) to encode both the output function {a mathematical formula}τi and the transition function {a mathematical formula}δi. The update part contains for all valuations {a mathematical formula}vi∈v and {a mathematical formula}v−i∈V−i and all {a mathematical formula}q,r∈Qi such that {a mathematical formula}r∈δi(q,v−i) and {a mathematical formula}τi(q)=vi an update guarded command – and recall that we have defined {a mathematical formula}χv=⋀x∈vx∧⋀x∉v¬x – given by{a mathematical formula} if {a mathematical formula}q≠r, or, otherwise, an update guarded command given by{a mathematical formula}
     </paragraph>
     <paragraph>
      Note that {a mathematical formula}m(σi) has one initialisation rule and one rule for each transition in {a mathematical formula}δi. Then, {a mathematical formula}m(σi) is of size linear in {a mathematical formula}|σi|. That the behaviour of {a mathematical formula}m(σi) is exactly as the behaviour of {a mathematical formula}σi is obvious from the construction. Moreover, using Lemma 2, Lemma 3, and the fact that the size of {a mathematical formula}m(σi) is linear in {a mathematical formula}|σi|, analogous results with respect to strategies and strategy profiles are obtained.
     </paragraph>
     <paragraph>
      In particular, given an arena {a mathematical formula}A=(N,Φ,m1,…,mn) and a strategy {a mathematical formula}σi, we can define the Kripke structure and runs induced by {a mathematical formula}σi on A by replacing {a mathematical formula}mi with {a mathematical formula}m(σi), that is, induced by the semantics of the srml arena {a mathematical formula}Aσi=(N,Φ∪Qi,m1,…,m(σi),…,mn). The outcome with respect to some {a mathematical formula}σ→, then, is given by the Kripke structure or runs associated with the srml arena {a mathematical formula}Aσ→=(N,Φ∪⋃i∈NQi,m(σ1),…,m(σn)). Since we are interested only in the computation runs and trees with respect to Φ associated with both {a mathematical formula}Kσ→ and {a mathematical formula}Aσ→, let us write {a mathematical formula}runs(Kσ→)|Φ for the restriction with respect to Φ, that is for the set {a mathematical formula}{ρ|Φ:ρ∈runs(Kσ→)}, and similarly for the set of computation trees. Then, once {a mathematical formula}σ→ is specified in srml, the following result immediately follows from Lemma 2.
     </paragraph>
     <paragraph label="Lemma 6">
      srml semantics of strategiesLet{a mathematical formula}σ→be some strategy profile with respect to an arena A. Then, there aresrmlmodules{a mathematical formula}m(σ1),…,m(σn), where eachsrmlmodule{a mathematical formula}m(σi)is of linear size in{a mathematical formula}|σi|such that{a mathematical formula}
     </paragraph>
     <paragraph>
      Notice that in the case of strategy profiles containing non-deterministic strategies, the behaviour of such strategies is very easily handled by the semantics of the modules: non-determinism is simply captured by the choices that the module representing a particular strategy has at its disposal.
     </paragraph>
     <paragraph>
      Finally, since strategy profiles can be specified (in linear size) as arenas in srml, while preserving their induced sets of runs and computation trees, we can define a temporal logic-based theory for strategy profiles. Note, however, that outcomes of this new arena, {a mathematical formula}Aσ→, are now with respect to valuations in the set {a mathematical formula}Φ∪⋃i∈NQi rather than with respect to valuations in Φ only. One can, nevertheless, restrict outcomes to their projection over valuations in Φ. A simple corollary of Lemma 6, using Lemma 3, is the following result.
     </paragraph>
     <paragraph label="Corollary 7">
      Logic theory of strategiesLet{a mathematical formula}A=(N,Φ,m1,…,mn)be an arena. For every strategy profile{a mathematical formula}σ→=(σ1,…,σn), of size{a mathematical formula}|σ→|, for A there is an LTL formula{a mathematical formula}ThLTL(Aσ→), of size polynomial in{a mathematical formula}|σ→|, such that{a mathematical formula}
     </paragraph>
     <paragraph>
      With these results in place, we can now start to investigate the decision problems discussed at the beginning of this section, for both the linear and branching time case.
     </paragraph>
     <section label="6.1">
      <section-title>
       On the complexity of LTL RMGs
      </section-title>
      <paragraph label="Proposition 8">
       The first problem we study is Realizability for LTL RMGs, which asks whether a player has a strategy to achieve its temporal logic goal with the context of a given arena, no matter how the other agents behave. {a mathematical formula}Realizabilityfor LTL RMGs is 2EXPTIME-complete. It is 2EXPTIME-hard for 2-player games, and PSPACE-complete for 1-player games.
      </paragraph>
      <paragraph label="Proof">
       For membership we reduce Realizability to the synthesis problem with respect to reactive environments, a problem known to be 2EXPTIME-complete for LTL specifications [42]. First, let {a mathematical formula}Th(mi) be an LTL formula characterising the module for player i and let {a mathematical formula}Th(m−i) be an LTL formula characterising the modules of all other players in G – i.e., an LTL formula for the srml system comprising the modules in {a mathematical formula}{m1,…,mi−1,mi+1,…,mn}. (We do not give the construction for {a mathematical formula}Th(mi), which should be immediate from results given above.) Then, it should be easy to see that the LTL formula φ is realizable in the context of LTL srml games if, and only if, the following LTL formula can be synthesised with respect to any reactive environment:{a mathematical formula} provided that the environment (the coalition of players in {a mathematical formula}N∖{i}) controls the variables in {a mathematical formula}Φ∖Φi and the system (player i) controls the variables in {a mathematical formula}Φi.Note that since in order to solve the Realizability problem we checked whether the LTL formula {a mathematical formula}Th(mi)∧(Th(m−i)→φ) can be synthesised, and the size of such a formula is polynomial in the sizes of both the LTL formula φ and the game G, then it follows that Realizability is 2EXPTIME in the sizes of both the game G and the input formula φ.For hardness, we first reduce LTL games (also called control games for LTL [5]) to an instance of Realizability with 3 players/modules (for the sake of simplicity in the presentation), and then such an instance to a game with only 2 modules. Now, let us introduce LTL games. An LTL game is a two-player zero-sum game given by {a mathematical formula}(GLTL,φ,v0) where φ is an LTL formula over a set {a mathematical formula}2Σ, and{a mathematical formula} is a graph with vertices in {a mathematical formula}VG which are partitioned in player 0 vertices {a mathematical formula}V0 and player 1 vertices {a mathematical formula}V1. The transitions of the graph are given by γ; if {a mathematical formula}v′∈γ(v), for some {a mathematical formula}v,v′∈VG, then there is a transition from v to {a mathematical formula}v′, which we may assume is labelled by {a mathematical formula}v′. Each vertex v has a set of properties P associated to it, which are given by μ; thus {a mathematical formula}P∈2Σ holds in vertex v if {a mathematical formula}P=μ(v). The graph {a mathematical formula}GLTL is assumed to be total: for every {a mathematical formula}v∈VG, we have {a mathematical formula}γ(v)≠∅.The game is played for infinitely many rounds by each player choosing a successor vertex whenever it is their turn: player 0 plays in vertices in {a mathematical formula}V0 and player 1 plays in vertices in {a mathematical formula}V1. The game starts in the initial vertex {a mathematical formula}v0∈VG. Playing the game defines an infinite sequence of vertices {a mathematical formula}w=v0,v1,v2,…, such that for each {a mathematical formula}vk, with {a mathematical formula}k∈N, we have {a mathematical formula}vk+1∈γ(vk). An LTL game is won by player 0 if {a mathematical formula}w⊨φ; otherwise player 1 wins. LTL games are determined, that is, there is always a winning strategy either for player 0 or for player 1. Checking whether player 0 has a winning strategy in an LTL game is a 2EXPTIME-complete problem [5].We construct an LTL RMG with three players {a mathematical formula}m0, {a mathematical formula}m1, and out and show that player 0 has a winning strategy in the LTL game {a mathematical formula}(GLTL,φ,v0) if, and only if, there exists a strategy {a mathematical formula}σ0 for {a mathematical formula}m0 such that for all strategy profiles {a mathematical formula}σ→, {a mathematical formula}K(σ→−0,σ0)⊨φ. The construction given below is similar to the one used in Lemma 2 to translate Kripke transition systems to srml modules. Let us, first, define the following sets of controlled variables:
       <list>
        {a mathematical formula}S00={xv:v∈V0}{a mathematical formula}S01={xv:v∈V1}{a mathematical formula}S10={yv:v∈V0}{a mathematical formula}S11={yv:v∈V1}Now, see that the runs with respect to
       </list>
       <paragraph>
        out are completely defined by the possible runs of the LTL game. More precisely, we have{a mathematical formula} As a consequence, for every formula ψ and run ρ in the LTL game {a mathematical formula}GLTL, there is a strategy profile {a mathematical formula}σ→ such that the following holds:{a mathematical formula} Based on the above facts, we can now show that player 0 has a winning strategy {a mathematical formula}σc in the LTL game {a mathematical formula}(GLTL,φ,v0) if, and only if, there exist a winning strategy {a mathematical formula}σ0 for {a mathematical formula}m0 in the associated srml game, as defined above.(⟹) First, suppose that player 0 has a winning strategy {a mathematical formula}σc in the given LTL game {a mathematical formula}(GLTL,φ,v0), which can be assumed to be of finite memory. Then, we can use a construction similar to the one given for Lemma 6 to define an srml module, say {a mathematical formula}m(σc), that characterises {a mathematical formula}σc. Because of the definition of the srml game induced by an LTL game, it immediately follows that module {a mathematical formula}m0 has a winning strategy, specified by {a mathematical formula}m(σc), for {a mathematical formula}Xφ.(⟸) Now, suppose that the srml module {a mathematical formula}m0 has a winning strategy {a mathematical formula}σ0 in the game {a mathematical formula}(A,γ0=Xφ,γ1=¬Xφ,γout=⊤), with A defined by srml modules as those given above. Then, because {a mathematical formula}σ0 is a finite-memory strategy, it straightforwardly defines a strategy in the LTL game for φ.This part of the proof shows that the problem is 2EXPTIME-hard for 3-player games. However, note that out is a deterministic module with the trivial goal ⊤. As a consequence, it can be eliminated from the game. Let {a mathematical formula}G2 be the game built based on G such that the controlled variables and guarded commands of out are given to player i. It then follows that player i has a strategy {a mathematical formula}σi such that for all {a mathematical formula}σ→−i it holds that {a mathematical formula}ρ(σ→−i,σi)⊨φ in G if and only if i has a strategy {a mathematical formula}σi⁎ such that for all {a mathematical formula}σ→−i⁎ it holds that {a mathematical formula}ρ(σ→−i⁎,σi⁎)⊨φ in {a mathematical formula}G2. The only if direction is trivial: simply let {a mathematical formula}σi⁎ be the strategy that plays as {a mathematical formula}σi and {a mathematical formula}σout, any strategy for out in G. The if direction is almost just as easy. Consider the contrapositive argument, that is, that if i does not have a strategy to realise φ in {a mathematical formula}G2, then it does not have a strategy to realise φ in G. Now, we only have to simply observe that the set of strategies for i in {a mathematical formula}G2 is a super set of the set of strategies for i in G. Therefore if i does not have a strategy to realise φ in {a mathematical formula}G2, then o does not have such a strategy in G either, which completes the proof of the 2EXPTIME-hardness result in 2-player games.Finally consider the case of 1-player games. For membership of PSPACE, consider an arena A and a formula φ. We simply need to check whether the LTL formula {a mathematical formula}Th(A)∧φ is satisfiable, which is clearly in PSPACE. For hardness, we can immediately reduce the LTL satisfiability problem for formulae over one variable; the details are straightforward from the description given above.  □
       </paragraph>
      </paragraph>
      <paragraph>
       It is natural to ask whether there are classes of games for which the decision problems we study are easier. While the study of such classes is not the main focus of this paper, there are natural subsets of LTL for which some of the decision problems we discuss are easier. Consider the class of as Objective LTL (OLTL) formulae. Informally, an OLTL formula is one in which no temporal connective occurs within the scope of a classical connective. Thus {a mathematical formula}FGp and {a mathematical formula}pUGq are OLTL formulae, but {a mathematical formula}p∧Xq is not an OLTL formula; the latter is not an OLTL formula because the “X” operator occurs within the scope of the “∧” operator. Formally, the syntax of OLTL formulae is given as follows:{a mathematical formula} Now, we can show:
      </paragraph>
      <paragraph label="Proposition 9">
       Realizabilityfor OLTL RMGs is EXPTIME-complete.
      </paragraph>
      <paragraph label="Proof">
       We first give an overview. Given an arena A, player i, and target formula φ, we start by constructing {a mathematical formula}KA, the Kripke structure induced by A. As we already noted, {a mathematical formula}KA can be computed in time exponential in the size of A. We then use dynamic programming to label each state s of {a mathematical formula}KA with the subformulae of φ that i can guarantee to be able to bring about in s. The actual algorithm for this is closely related to the standard explicit state CTL model checking algorithm (see, e.g., [20]). The algorithm cannot be used for this purpose for arbitrary LTL formulae, because of the possibility of temporal operators occurring within the scope of a classical connective. However, the approach works for OLTL formulae. The algorithm operates in time polynomial in the size of {a mathematical formula}KA. Finally, we check whether all initial states of {a mathematical formula}KA are labelled with the target formula φ; if the answer is “yes”, then the answer to the Realizability problem is “yes”, otherwise it is “no”. The detailed algorithm is presented in Fig. 13 in the Appendix. For EXPTIME-hardness, we can straightforwardly reduce the problem of determining whether a player has a winning strategy in the game Peek-{a mathematical formula}G4 (see the proof of Proposition 15, below, for details of the problem).  □
      </paragraph>
      <paragraph label="Proposition 10">
       Next, we ask whether a strategy profile is a Nash equilibrium: {a mathematical formula} Note that the strategies {a mathematical formula}σ→=(σ1,…,σn) given in the input to this problem are represented as finite state machines. We assume that they are represented by explicitly enumerating the various components of the finite state machine. NE-membershipfor LTL RMGs is PSPACE-complete. In addition, it is PSPACE-hard even for one-player games and LTL goals over a singleton variable set Φ.
      </paragraph>
      <paragraph label="Proof">
       For membership in PSPACE we define a procedure that uses two oracles, one for LTL model-checking and one for satisfiability, which are both known to be in PSPACE [63]. The procedure is based on the observation that if the profile {a mathematical formula}σ→ is a Nash equilibrium, then either {a mathematical formula}ρ(σ→)⊨γi or {a mathematical formula}ρ(σ→−i,σi′)⊭γi, for every player i and strategy {a mathematical formula}σi′. For hardness, we reduce LTL satisfiability for formulae with one propositional variable [19] to a one-player LTL RMG. Let us first prove membership in PSPACE.Recall that a profile {a mathematical formula}σ→ of deterministic strategies in an LTL RMG is a pure-strategy Nash equilibrium if and only if for every player i in N,{a mathematical formula} Thus, we can, for every player i, check whether{a mathematical formula} and conclude {a mathematical formula}σ→∉NE(G) if such a statement holds; otherwise {a mathematical formula}σ→∈NE(G).Checking {a mathematical formula}ρ(σ→)⊭γi can be done in PSPACE. First, use Lemma 6 and Corollary 7 to construct an LTL formula {a mathematical formula}Th(Aσ→) that characterises {a mathematical formula}σ→. It is not difficult to show that, for all runs ρ that satisfy {a mathematical formula}Th(Aσ→), it is the case that {a mathematical formula}ρ|Φ=ρ(σ→). To simplify notation, hereafter, we will write {a mathematical formula}Th(σ→) for {a mathematical formula}Th(Aσ→). Such a formula, namely {a mathematical formula}Th(σ→), is polynomial in {a mathematical formula}|σ→|.Following the automata-theoretic approach to model checking, we now construct two alternating Büchi word (ABW) automata {a mathematical formula}ATh(σ→) and {a mathematical formula}Aγi which accept exactly all the words that satisfy the formulae {a mathematical formula}Th(σ→) and {a mathematical formula}γi, respectively. Such alternating automata are polynomial in {a mathematical formula}|Th(σ→)| and {a mathematical formula}|γi|. We now simply ask whether {a mathematical formula}L(ATh(σ→))|Φ⊆L(Aγi), that is, whether the language accepted by {a mathematical formula}ATh(σ→) and restricted to Φ is included in the language accepted by {a mathematical formula}Aγi. Such a question can be answered in PSPACE. If {a mathematical formula}L(ATh(σ→))|Φ⊆L(Aγi) then {a mathematical formula}ρ(σ→)⊨γi; otherwise {a mathematical formula}ρ(σ→)⊭γi. Since PSPACE is a deterministic complexity class, checking {a mathematical formula}ρ(σ→)⊭γi is also in PSPACE, as required.On the other hand, checking that {a mathematical formula}ρ(σ→−i,σi′)⊨γi for some {a mathematical formula}σi′∈Σi can be done using constructions very similar to those used in Lemma 6 and Corollary 7, but in this case we check LTL satisfiability instead. First, let us write {a mathematical formula}Th(m(σj)) for the LTL formula that characterises {a mathematical formula}σj, with {a mathematical formula}j∈N. Specifically, we check whether the LTL formula {a mathematical formula}γi∧⋀j∈N∖{i}Th(m(σj)) is satisfiable, which also can be done in PSPACE.Note that since in order to solve the NE-membership problem we checked whether the LTL formula {a mathematical formula}γi∧⋀j∈N∖{i}Th(m(σj)) is satisfiable, and the size of such a formula is polynomial in the sizes of both the LTL goals {a mathematical formula}γi and the strategies {a mathematical formula}σj, then it follows that NE-membership is PSPACE in the sizes of both the game G and the input strategy profile {a mathematical formula}σ→.Now, for hardness, we reduce the LTL satisfiability problem (which is PSPACE-complete, even for formulae with only one propositional variable [19]) in the same way that is done for iBG [29]. More specifically, we take the class of LTL formulae over one propositional variable and ask whether a given LTL formula φ in this class is satisfiable. Because this formula is over only one propositional variable, say p, any model can be produced by an srml module.Then, reasoning as in the proof for iBG [29], we can show that the srml module m, defined below, has a winning strategy to satisfy {a mathematical formula}φ∧q if, and only if, the formula φ is satisfiable. This strategy can be used to build a strategy profile {a mathematical formula}σm that is not a Nash equilibrium if, and only if, φ is satisfiable.{a mathematical formula}Now, consider a strategy {a mathematical formula}σm such that {a mathematical formula}q∉τ(q0). Then, it follows that {a mathematical formula}σm⊭φ∧q. If φ is satisfiable then m has a beneficial deviation: switch to a strategy {a mathematical formula}σm′ that builds a model for φ and such that {a mathematical formula}q∈τ(q0). However, if φ is not satisfiable, then no strategy for m will satisfy {a mathematical formula}φ∧q, and hence {a mathematical formula}σm would be a Nash equilibrium in such a case. Note that the reason this reduction works is because the arena where the game is played has constant size (because φ is a formula with only one propositional variable).  □
      </paragraph>
      <paragraph>
       The next problem asks if a game has any Nash equilibrium. {a mathematical formula}
      </paragraph>
      <paragraph label="Proposition 11">
       Non-emptinessfor LTL RMGs is 2EXPTIME-complete, and it is 2EXPTIME-hard for 2-player games.
      </paragraph>
      <paragraph label="Proof">
       For membership in 2EXPTIME, we instantiate the E-Nash problem (described below) with {a mathematical formula}φ=⊤. For hardness, one can reduce LTL synthesis with two variables, say x and y to a two-player game with five Boolean variables. The reduction takes as input an LTL synthesis game with two players, 1 and 2, and an LTL formula φ such that player 1 has a winning strategy in the synthesis game if and only if φ can be synthesised; otherwise, player 2 has a winning strategy to show that ¬φ can be synthesised – because it is a zero-sum game. Based on this input game, the reduction uses the two modules below and following LTL goals:
       <list>
        {a mathematical formula}γ1=(¬φ→(p↔q))∧(φ→r){a mathematical formula}γ2=(¬φ→¬(p↔q))∧(φ→(φ↔¬r))Given this two-player game,
       </list>
       <paragraph>
        G, it is not hard to check that player 1 has a winning strategy to synthesise φ if and only if G has a Nash equilibrium, from which 2EXPTIME-hardness follows.
       </paragraph>
       <list>
        <list-item label="•">
         (⇒) Assume that player 1 has a winning strategy to synthesise φ. Then, module {a mathematical formula}m1 can use such a winning strategy to ensure that φ holds, while setting r to ⊤. Then, {a mathematical formula}γ1 is satisfied and {a mathematical formula}m1 will not deviate. On the other hand, in this case, {a mathematical formula}m2 will not have its goal {a mathematical formula}γ2 satisfied, but cannot beneficially deviate since {a mathematical formula}(φ→(φ↔¬r)) will still be false in every unilateral deviation of {a mathematical formula}m2.
        </list-item>
        <list-item label="•">
         (⇐) We prove the contrapositive statement: assume that player 1 does not have a winning strategy to synthesise φ and show that in such a case G does not have a Nash equilibrium. Since the game for LTL synthesis is determined and player 1 does not have a winning strategy to synthesise φ then we know that player 2 has a winning strategy for ¬φ. We will analyse all possible cases and show that in each instance at least one of the players has a beneficial deviation. Let {a mathematical formula}σ→=(σ1,σ2) be an arbitrary strategy profile and assume first that {a mathematical formula}σ→⊨¬φ. Then, if {a mathematical formula}σ→⊨(p↔q) player {a mathematical formula}m2 will have a beneficial deviation. If, on the other hand, {a mathematical formula}σ→⊨¬(p↔q) then player {a mathematical formula}m1 will have a beneficial deviation. Now, suppose that {a mathematical formula}σ→⊨φ. Then, if {a mathematical formula}σ→⊨¬r player {a mathematical formula}m1 will have a beneficial deviation. If, on the other hand, {a mathematical formula}σ→⊨r then player {a mathematical formula}m2 will have a beneficial deviation: in case {a mathematical formula}σ→⊨¬(p↔q), player {a mathematical formula}m2 simply has to deviate to a strategy {a mathematical formula}σ2′ that is winning for ¬φ and keep the same value for q; in case {a mathematical formula}σ→⊨(p↔q), player {a mathematical formula}m2 can deviate to a strategy {a mathematical formula}σ2′ that is winning for ¬φ and change the value of q with respect to the one given by {a mathematical formula}σ2. This analysis covers all possible cases with respect to φ, r, and {a mathematical formula}p,q.
        </list-item>
       </list>
       <paragraph>
        Then, the problem is 2EXPTIME-hard with two players and five Boolean variables.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Arguably, the two key decision problems relating to the game-theoretic analysis of game-like concurrent and multi-agent systems are (i) checking whether an LTL formula holds on some run given by a Nash equilibrium of the system; and (ii) checking whether a given LTL formula holds on all runs given by the Nash equilibria of the system. These two problems are formalised in the E-Nash and A-Nash problems, respectively. {a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       These two decision problems were first studied in [29] for iterated Boolean games (iBG). In such a setting, there was no language to specify the systems that the iBGs were to model. Even more, the setting was quite simple: it was assumed that in every system state all variables could be updated. In this article, we study systems that do not impose this restriction, and we show that we obtain similar complexity results in this case. Note that using RMGs allows us to express systems that cannot be directly expressed in iBGs; however, as we noted above, RMGs cannot succinctly express iBGs.
      </paragraph>
      <paragraph>
       More specifically, even though RMGs can be used to impose constraints in the choices that players can make (i.e., the values they can give the variables they control), it is still possible to find a reduction from the E-Nash and A-Nash for LTL RMGs to the same problems in the context of iBGs. Before describing the reduction, let us define an iBG {a mathematical formula}G′, which we will call a ‘supervised game’, in which all the Nash equilibria of the iBG {a mathematical formula}G′ must be consistent with the Nash equilibria of some initially given LTL RMG G.
      </paragraph>
      <paragraph>
       Formally, an iterated Boolean game is a structure{a mathematical formula} where every element of the structure is as for LTL RMGs. Strategies are defined as for LTL RMGs, that is, as Moore finite-state machines. However, as we can see, the arena where an iBG is played is implicitly given: it is the unique clique whose vertices are the valuations {a mathematical formula}V=2Φ. Having such an arena to play the game informally means that, in an iBG, it is assumed that in every state all agents can update the values of all the variables they control; note that, in contrast, in an LTL RMG only the variables that are in the scope of enabled guarded commands can be updated.
      </paragraph>
      <paragraph>
       More specifically, note that, in general, the LTL RMG representation of an iBG may result in a game of exponential size since one would have to specify in the LTL RMG all the (exponentially many) choices with respect to Φ that players in an iBG have at their disposal. This is, indeed, the reason why a simple polynomial-time reduction from iBG to LTL RMGs is not possible – e.g., in order to obtain hardness results for LTL RMGs.
      </paragraph>
      <paragraph>
       Nevertheless, as mentioned above, for the particular case of the E-Nash and A-Nash problems, a reduction from LTL RMGs to iBGs is possible. We first present a key technical result, which relies on the following game construction. Given an LTL RMG {a mathematical formula}G=(A=(N,Φ,(mi)i∈N),(γi)i∈N), we let the iBG {a mathematical formula}G′=(N′,Φ′,(Φi)i∈N′,(γi′)i∈N′) be its supervised game, given by
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}N′=N∪{n+1,n+2} and {a mathematical formula}Φ′=Φ∪{xn+1,xn+2},
       </list-item>
       <list-item label="•">
        {a mathematical formula}γi′=⋀j∈NTh(mj)∧γi,
       </list-item>
       <list-item label="•">
        {a mathematical formula}γn+1′=⋀j∈NTh(mj)∨(xn+1↔xn+2),
       </list-item>
       <list-item label="•">
        {a mathematical formula}γn+2′=⋀j∈NTh(mj)∨¬(xn+1↔xn+2),
       </list-item>
      </list>
      <paragraph>
       where {a mathematical formula}i∈N. Recall that each {a mathematical formula}Th(mi) is an LTL formula that characterises module {a mathematical formula}mi. Based on this definition of supervised games, we obtain the following result.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}G=(A=(N,Φ,(mi)i∈N),(γi)i∈N)be an LTL RMG and let{a mathematical formula}G′=(N′,Φ′,(Φi)i∈N′,(γi′)i∈N′)be its supervised game, then:{a mathematical formula}for all{a mathematical formula}σ→and strategies{a mathematical formula}σn+1,{a mathematical formula}σn+2for players{a mathematical formula}n+1and{a mathematical formula}n+2.We first prove the left-to-right direction. Since {a mathematical formula}σ→ is a profile of strategies that is consistent with A, then the LTL formula{a mathematical formula} is satisfied and, hence, also the LTL goals {a mathematical formula}γn+1 and {a mathematical formula}γn+2. Thus, players {a mathematical formula}n+1 and {a mathematical formula}n+2 will not deviate. Moreover, because players {a mathematical formula}n+1 and {a mathematical formula}n+2 do not control any variable already present in the game G and the goals {a mathematical formula}(γi′)i∈N do not depend on the Boolean variables in {a mathematical formula}{xn+1,xn+2}, it follows that{a mathematical formula} for all goals in {a mathematical formula}(γi′)i∈N and strategies {a mathematical formula}σn+1,σn+2 for players {a mathematical formula}n+1 and {a mathematical formula}n+2. Then, players i in N who have their goal achieved in G by {a mathematical formula}ρ(σ→) will also have it satisfied in {a mathematical formula}G′ by {a mathematical formula}ρ(σ→,σn+1,σn+2) – thus, they will not want to deviate. Similarly, players i in N who did not have their goal achieved in G by {a mathematical formula}ρ(σ→) will not have it satisfied in {a mathematical formula}G′ by {a mathematical formula}ρ(σ→,σn+1,σn+2) either, and hence will not have a beneficial deviation in {a mathematical formula}G′, provided that they only use strategies that are consistent with A. Then, if a player i has a beneficial deviation in {a mathematical formula}G′ and not in G it must be by switching to a strategy {a mathematical formula}σi′ that is not consistent with A. But, in such a case its goal {a mathematical formula}γi will not be satisfied because the conjunct {a mathematical formula}⋀j∈NTh(mj) will be false. Then, in {a mathematical formula}G′ no player can have a beneficial deviation by switching to a strategy that is not consistent with A. As a consequence, {a mathematical formula}(σ→,σn+1,σn+2)∈NE(G′), as desired.We now prove the right-to-left direction. Since {a mathematical formula}(σ→,σn+1,σn+2)∈NE(G′), we know both that players {a mathematical formula}n+1 and {a mathematical formula}n+2 have their goals achieved and that the strategies in {a mathematical formula}σ→ are consistent with the srml modules {a mathematical formula}(mi)i∈N – because the LTL formula {a mathematical formula}⋀j∈NTh(mj) is necessarily satisfied in all Nash equilibria of {a mathematical formula}G′ (because the two final players are playing a version of Matching Pennies, for which there is no pure Nash equilibrium).Hence, {a mathematical formula}σ→ is a legal strategy in G (i.e., consistent with the arena given by {a mathematical formula}(mi)i∈N). For exactly the same reasons given in the left-to-right direction, the strategy profile {a mathematical formula}σ→ is, therefore, a Nash equilibrium in G, that is, because{a mathematical formula} as needed. Note, in particular, that if a player i did not have its goal {a mathematical formula}γi′ satisfied in {a mathematical formula}G′ by {a mathematical formula}ρ(σ→,σn+1,σn+2), then such a strategy profile does not satisfy {a mathematical formula}γi either – because the LTL formula {a mathematical formula}⋀j∈NTh(mj) is necessarily satisfied. Then, {a mathematical formula}ρ(σ→)⊭γi. Moreover, player i cannot have a beneficial deviation in G by switching to an alternative strategy because every strategy in G was already available in {a mathematical formula}G′.  □
      </paragraph>
      <paragraph>
       The reason why we call the iBG {a mathematical formula}G′ “the supervised game of G,” under the definition given above, is that in {a mathematical formula}G′ we have introduced two new players, namely {a mathematical formula}n+1 and {a mathematical formula}n+2, who act as “supervisors” of the behaviour of the players i in N in the following sense: they (players {a mathematical formula}n+1 and {a mathematical formula}n+2) can easily ensure that any strategy profile in the iBG {a mathematical formula}G′ which forms a Nash equilibrium is possible if, and only if, the other players comply with the constrained behaviour imposed by the specification of the modules in G, that is, the behaviour formally specified by the LTL formula {a mathematical formula}⋀j∈NTh(mj). Then, using Lemma 12, we can show the next result.
      </paragraph>
      <paragraph label="Proposition 13">
       TheE-NashandA-Nashproblems for LTL RMGs are both 2EXPTIME-complete.
      </paragraph>
      <paragraph label="Proof">
       Consider E-Nash first. For hardness, we can trivially reduce the Non-emptiness problem for LTL RMGs by asking whether ⊤ is satisfied on some Nash equilibrium outcome. For membership, use Lemma 12 to construct a supervised game and straightforwardly reduce E-Nash for LTL RMGs to E-Nash for iBG, which is known to be 2EXPTIME-complete [29]. Since 2EXPTIME is a deterministic complexity class, the desired complexity result for the A-Nash problem immediately follows.Finally, since in [29] we use rational synthesis [23] to solve the E-Nash problem for iBG, which is 2EXPTIME in the sizes of players' goals and input LTL formula, then we obtain that E-Nash for LTL RMGs is 2EXPTIME with respect to both the size of the RMG G and input LTL formula φ.  □
      </paragraph>
      <paragraph>
       This result shows, in particular, that in the linear-time setting analysing equilibrium properties (via the E-Nash and A-Nash problems) is as hard as the controller synthesis problem for LTL [57] – or, expressed in game-theoretic terms, as hard as solving two-player zero-sum perfect-information games with LTL goals.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       On the complexity of CTL RMGs
      </section-title>
      <paragraph>
       In this section, we are interested in the computational complexity of the decision problems just investigated, but now in the branching-time framework we developed in previous sections. The first complexity result we are to present is for Realizability, which we obtain via a reduction to CTL supervisory-control games in [42] (aka CTL games on graphs).
      </paragraph>
      <paragraph label="Proposition 14">
       Realizabilityfor CTL RMGs is 2EXPTIME-complete.
      </paragraph>
      <paragraph label="Proof">
       For membership in 2EXPTIME, similar to the case for LTL, we use a reduction to the control-synthesis problem for CTL specifications with reactive environments [42]. Firstly, from the set of modules in the given game G, construct the induced Kripke structure K, which is at most exponential in the size of the modules. Now, associate player i with the “system” in the CTL control-synthesis problem, the set of players {a mathematical formula}N∖{i} with its (reactive) “environment” and let φ be the CTL goal of the system – hence, ¬φ would be the CTL goal of the environment since it is a zero-sum game. It is not hard to show that player i has a strategy to achieve φ if, and only if, the system has a strategy to win the CTL control-synthesis game.{sup:4} Because the complexity is doubly exponential in the size of the formula φ, but only exponential in the size of the given graph (K in this case), then the procedure is now doubly exponential in the size of the initial game G. Therefore, containment in 2EXPTIME still follows, but with an exponentially higher system complexity, matching the result in the linear-time case using a logic-based approach instead, that is, a decision procedure that is doubly exponential in the sizes of both the system/game and the formula.For hardness, again analogous to the LTL case, we use the CTL supervisory-control games in [5], where, in particular, non-deterministic strategies instead of only deterministic ones are considered.  □
      </paragraph>
      <paragraph>
       This result sharply contrasts with the computational complexity of the usual realizability problem for CTL specifications, which is known to be EXPTIME-complete [21]. There is, however, a clear difference between the standard realizability problem and the one we are considering: whereas in the former a strategy (for player i, the system) must be constructed with respect to a known special strategy of the environment (for players in {a mathematical formula}N∖{i}), in the latter we have to construct a strategy that ensures the goal of player i with respect to any strategy of player i's opponents.
      </paragraph>
      <paragraph>
       Proposition 14 shows, in addition, that whereas in the linear-time framework Realizability for a multi-player game is as hard as synthesis in a two-player system, in the branching-time context the problem is considerably harder, that is, while synthesis for CTL specifications is EXPTIME-complete, Realizability for CTL RMGs is 2EXPTIME-complete.
      </paragraph>
      <paragraph>
       On the other hand, the following complexity result shows that, as in the linear-time case, the NE-membership problem is as hard as the satisfiability problem for the temporal logic under consideration.
      </paragraph>
      <paragraph label="Proposition 15">
       NE-membershipfor CTL RMGs is EXPTIME-complete.
      </paragraph>
      <paragraph label="Proof">
       To show membership in EXPTIME, we use a variation of the algorithm given to show Proposition 6 in [29]. In particular, we use the following two facts:
       <list>
        CTL model checking over Kripke structures can be done in polynomial time (and the Kripke structure {a mathematical formula}KA induced by an arena A may be exponential in the size of A);the intersection non-emptiness problem for Alternating Büchi Tree (ABT) automata is EXPTIME-complete.Hardness, on the other hand, is shown by a reduction from the problem of determining whether a given player has a winning strategy in the game
       </list>
       <paragraph>
        peek-{a mathematical formula}G4[64, p. 158]; our construction of a CTL RMG for an instance of peek-{a mathematical formula}G4 is inspired by the construction presented in [67].An instance of peek-{a mathematical formula}G4 is given by a structure: {a mathematical formula}(X1,X2,X3,φ), where:
       </paragraph>
       <list>
        <list-item label="•">
         {a mathematical formula}X1 and {a mathematical formula}X2 are disjoint, finite sets of Boolean variables, with the intended interpretation that the variables in {a mathematical formula}X1 are under the control of agent 1, and {a mathematical formula}X2 are under the control of agent 2;
        </list-item>
        <list-item label="•">
         {a mathematical formula}X3⊆(X1∪X2) are the variables deemed to be true in the initial state of the game; and
        </list-item>
        <list-item label="•">
         φ is a propositional logic formula over the variables {a mathematical formula}X1∪X2, representing the winning condition.
        </list-item>
       </list>
       <paragraph>
        The game is played in a series of rounds, with agents {a mathematical formula}i∈{1,2} alternating turns – and agent 1 moving first – to select a value (⊤ or ⊥) for one of their variables in {a mathematical formula}Xi. The game starts from the initial assignment of truth values defined by {a mathematical formula}X3. Variables that were not changed retain the same truth value in the subsequent round. An agent wins in a given round if it makes a move such that the resulting truth assignment defined by that round makes φ true.The decision problem associated with peek-{a mathematical formula}G4 is determining if agent 2 has a winning strategy in a given instance {a mathematical formula}(X1,X2,X3,φ). We would like to remark that since peek-{a mathematical formula}G4 only requires “memoryless” strategies, they can be modelled with our finite-state machine model of strategies: whether an agent i can win depends only on the current truth assignment, the distribution of variables, the winning formula, and whose turn it is currently. As a corollary, if agent i can force a win, then it can force it in {a mathematical formula}O(2|X1∪X2|) moves.From {a mathematical formula}(X1,X2,X3,φ), the following CTL RMG can be constructed. For each Boolean variable {a mathematical formula}x∈(X1∪X2), we create a variable with the same name in our srml model, and we create two additional Boolean variables: {a mathematical formula}turn and p. The former, will have the intended interpretation that if {a mathematical formula}turn=⊤, then it is agent 1's turn to move, while if {a mathematical formula}turn=⊥, then it is agent 2's turn to move. We then have an srml module, which we call {a mathematical formula}move, the purpose of which is to control {a mathematical formula}turn, toggling its value in each successive round, starting from the initial case of it being agent 1's move. Note that because of the definition of the module move, it has only one possible legal strategy up to equality with respect to its observable behaviour, namely {a mathematical formula}⊤,⊥,⊤,⊥,…. The goal {a mathematical formula}γmove of this player in the CTL RMG is defined to be {a mathematical formula}γmove=⊤.{a mathematical formula}Moreover, for each of the two peek-{a mathematical formula}G4 players {a mathematical formula}i∈{1,2}, we create an srml module {a mathematical formula}agi that controls the variables {a mathematical formula}Xi. We also let the module {a mathematical formula}ag2 control p. The modules {a mathematical formula}ag1 and {a mathematical formula}ag2 are as follows. For {a mathematical formula}ag1, it begins by deterministically initialising the values of all its variables to the values defined by {a mathematical formula}X3 (that is, if variable {a mathematical formula}x∈X1 appears in {a mathematical formula}X3 then this variable is initialised to ⊤, otherwise it is initialised to ⊥). The module {a mathematical formula}ag2 is the same as defined for {a mathematical formula}ag1, save that {a mathematical formula}ag2 has two init commands instead of only one: while one of the init commands sets p to ⊤, the other one sets p to ⊥.Then, after initialisation, when it is a player's turn, such a player can non-deterministically choose at most one of the variables under its control and toggle the value of this variable; when it is not this player's turn, it has no choice but to do nothing, leaving the value of all its variables unchanged. The general structure of {a mathematical formula}ag1 is thus as follows, where {a mathematical formula}X1={x1,…,xk}.{a mathematical formula} And the general structure of {a mathematical formula}ag2 is thus as follows, where {a mathematical formula}X2={y1,…,yl}.{a mathematical formula}Notice that an agent can always skip, electing to leave its variables unchanged; and, if it is not this agent's turn to move, this is the only choice it has. The srml arena under consideration contains just these three modules. We define the goal of agent 1 to be {a mathematical formula}γ1=⊤, and the goal of agent 2 to be the CTL formula {a mathematical formula}γ2=p∧A(¬φU(turn∧φ)).In addition, we also let the strategy {a mathematical formula}σ1 of agent 1 be the trivial non-deterministic strategy that contains all possible choices available at each round of the game, i.e., a strategy that in every round non-deterministically chooses any of the commands in the update part of the module {a mathematical formula}ag1. For {a mathematical formula}ag2 we let the strategy {a mathematical formula}σ2 be any strategy such that it chooses the initialisation command where {a mathematical formula}p=⊥. Then, clearly, with this strategy profile, namely {a mathematical formula}(σ1,σ2,σmove), players {a mathematical formula}ag1 and {a mathematical formula}move have their goals satisfied, whereas player {a mathematical formula}ag2 fails to have its goal {a mathematical formula}γ2 satisfied (because {a mathematical formula}σ2 makes {a mathematical formula}p=⊥). More formally, with respect to this strategy profile we know that {a mathematical formula}K(σ1,σ2,σmove)⊭γ2.However, if agent 2 has a winning strategy in peek-{a mathematical formula}G4, then the player {a mathematical formula}ag2 has a beneficial deviation {a mathematical formula}σ2′ to a strategy making the same choices as such a winning strategy and which sets {a mathematical formula}p=⊤ in the initialisation stage, so that its goal {a mathematical formula}γ2 is achieved. Hence, whereas {a mathematical formula}(σ1,σ2,σmove) is not a Nash equilibrium, the strategy profile {a mathematical formula}(σ1,σ2′,σmove) would be an equilibrium as in that case all players get their goals satisfied. Formally, the following holds:{a mathematical formula} If, on the other hand, agent 2 does not have a winning strategy in peek-{a mathematical formula}G4, then, because the strategy {a mathematical formula}σ1 of {a mathematical formula}ag1, as defined above, contains all possible choices that agent 1 can make, it necessarily follows that there would be a run of the game that can be used as a witness to show that {a mathematical formula}γ2 is not satisfied, in particular, for all strategies {a mathematical formula}σ2′ that set {a mathematical formula}p=⊤ (as otherwise agent 2 would have a winning strategy – contradicting our initial hypothesis). Then, it follows that in this case player {a mathematical formula}ag2 cannot have a beneficial deviation and that the strategy profile {a mathematical formula}(σ1,σ2,σmove) is in fact a Nash equilibrium. Formally, in this case, the following statement holds:{a mathematical formula}Thus, agent 2 has a winning strategy for the instance of peek-{a mathematical formula}G4 if, and only if, {a mathematical formula}(σ1,σ2,σmove) is not a Nash equilibrium. Since EXPTIME is a deterministic complexity class, hardness of the NE-membership problem for CTL RMGs with respect to the EXPTIME complexity class follows. Finally, observe that because we use intersection non-emptiness to show membership in EXPTIME, we obtain that NE-membership is EXPTIME in the sizes of both the RMG G and the strategy profile {a mathematical formula}σ→.  □
       </paragraph>
      </paragraph>
      <paragraph>
       Finally, we show that, as in the linear-time case, checking both whether a system/game has at least one Nash equilibrium as well as whether a CTL formula holds on some or on all Nash equilibria of such a game-like multi-agent system are 2EXPTIME-hard problems. Formally:
      </paragraph>
      <paragraph label="Proposition 16">
       The following three problems are 2EXPTIME-hard:Non-emptiness,E-Nash, andA-Nashfor CTL RMGs.
      </paragraph>
      <paragraph label="Proof">
       For these results, we reduce CTL supervisory-control games on graphs to the Non-emptiness problem – a game construction in which we add two new players who ensure that the “system” player in the initially given CTL supervisory-control game has a winning strategy if, and only if, there is a Nash equilibrium in the constructed CTL RMG. Then, the other two decision problems we have considered, namely, E-Nash and A-Nash, inherit such a hardness complexity result.  □
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Beyond reactive modules
     </section-title>
     <paragraph>
      The results we prove in this article may at first sight appear to be closely tied to a single formalism for defining game arenas, i.e., the Reactive Modules language. However, this language is in fact very general. To illustrate the scope of our framework, we now show how a standard AI formalism for planning agents can be directly modelled within our framework: the propositional STRIPS notation [22], [12], [25]. Descendants of the STRIPS notation remain widely used within the planning community, and various multi-agent planning models based on STRIPS have been investigated within the literature, such as the MA-STRIPS model of Brafman and Domshlak [10].
     </paragraph>
     <paragraph>
      The basic idea of the STRIPS notation is to model the effects of actions in terms of “pre-condition, delete, add lists”: the pre-condition defines what must be true in order for the action to be executed; the add list defines what propositions will be made true by the execution of the action; and the delete list defines what propositions will be made false by the execution of the action. As we did previously, we assume a vocabulary Φ of propositional variables, used to characterise the state of the system. Formally, a STRIPS descriptor for an action α is given by a structure{a mathematical formula} where:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Tα is the set of propositions that must be true in order for α to be executed;
      </list-item>
      <list-item label="•">
       {a mathematical formula}Fα is the set of propositions that must be false in order for α to be executed;
      </list-item>
      <list-item label="•">
       {a mathematical formula}Dα is the set of propositions that characterise those facts made false by the performance of α (the delete list); and
      </list-item>
      <list-item label="•">
       {a mathematical formula}Aα is the set of propositions that characterise those facts made true by the performance of α (the add list).
      </list-item>
     </list>
     <paragraph>
      As with RMGs, we model the state of the system at any given time as a valuation {a mathematical formula}v∈V. For every action α we define a propositional formula {a mathematical formula}preα, such that this formula is satisfied by a valuation whenever the pre-condition of α is met:{a mathematical formula} The effect of executing an action α when the world is as described by the valuation v is denoted {a mathematical formula}eff(α,v), where this partial function is defined as follows:{a mathematical formula} We can then naturally define a multi-agent STRIPS arena:{a mathematical formula} where {a mathematical formula}N={1,…,n} is the set of players, Φ is the vocabulary of propositional variables used to represent the state of the system, {a mathematical formula}v0∈V is the initial state of the game, and for each player {a mathematical formula}i∈N, {a mathematical formula}Aci={αi1,…,αik} is set of action descriptors, representing the actions that i can perform. The domain of an action α, denoted {a mathematical formula}domα, is the set of variables whose truth status can be changed by the performance of α, i.e., {a mathematical formula}domα=Dα∪Aα. To keep things simple, we assume that the actions of different players are disjoint:{a mathematical formula} Let {a mathematical formula}Φi=⋃α∈Acidomα be the set of variables under the control of player i.
     </paragraph>
     <paragraph>
      The execution of a STRIPS arena then proceeds over an infinite sequence of rounds: in the first round, variables are initialised to their values in {a mathematical formula}v0; on each subsequent round, each player i selects an action {a mathematical formula}α∈Aci whose pre-condition is satisfied, and the profile of actions selected by players are then executed as defined in the {a mathematical formula}eff(⋯) function to generate the next state of the system. Each player then chooses another action whose pre-condition is satisfied, and so on.
     </paragraph>
     <paragraph>
      A STRIPS game is then given by a structure{a mathematical formula} where A is a multi-agent STRIPS arena, and {a mathematical formula}γi is the temporal logic goal of player i; as with RMGs, we might consider LTL or CTL goals. Given this setup, it should be clear that we can then define strategies for agents in the same way that we did for RMGs, and then runs, Kripke structures, etc. similarly. (The details are straightforward but tedious, and we omit them here.) We remark that the definition we give here is very similar to that of the MA-STRIPS model of Brafman and Domshlak [10], except that in MA-STRIPS, goals are represented as sets of states, with the idea being that an agent wants to bring about one of the set. This can be represented directly within our model by giving agents goals of the form {a mathematical formula}Fφ.
     </paragraph>
     <paragraph>
      We now show how we can translate a STRIPS arena into an equivalent RML arena. First, let {a mathematical formula}α=(Tα,Fα,Dα,Aα) be an action descriptor. Then we define a guarded command {a mathematical formula}gα for this action descriptor as follows:{a mathematical formula} We define a single init guarded command {a mathematical formula}gi0 for player i, which sets the variables under the control of i to correspond to the valuation {a mathematical formula}v0:{a mathematical formula} Finally, the module {a mathematical formula}mi for each player i is then simply {a mathematical formula}mi=(Φi,Ii,Ui) where {a mathematical formula}Φi is as defined above, {a mathematical formula}Ii={gi0} is the single initialisation guarded command for i as defined above, and {a mathematical formula}Ui={gα|α∈Aci} is the set of update guarded commands for i.
     </paragraph>
     <paragraph>
      Now, it should be clear from construction that the srml arena constructed in this way will operate in the same way as the STRIPS arena that we began with. In particular, when each player i selects an enabled update command {a mathematical formula}gα for execution, this corresponds to selecting an action {a mathematical formula}α∈Aci whose pre-condition is satisfied. Executing a guarded command simulates the behaviour of executing the action α as defined by the descriptor {a mathematical formula}(Tα,Fα,Dα,Aα).
     </paragraph>
     <paragraph>
      Thus, we can translate propositional multi-agent STRIPS systems into our formalism. Note that translation in the opposite direction is not directly possible, however, because srml guarded commands are richer than propositional STRIPS operators: in the action part of a guarded command, we are allowed to have actions such as {a mathematical formula}x′:=φ, meaning that the variable x should take the value of the formula φ. Such constructs are not provided in propositional STRIPS (they can be simulated, but only at the cost of an exponential blow up in the number of actions).
     </paragraph>
     <paragraph>
      Finally, note that the fact that propositional STRIPS planning games can be encoded within our game framework implies that membership results for the corresponding decision problems studied in the article carry over directly (hardness results do not carry over automatically, although many of them can be seen to hold from the constructions presented earlier).
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Our work has its antecedents in two closely related threads of computer science research: the first, arising from the computer-aided verification community, is the use of logics and techniques inspired by game theory for the automated verification of computer programs (see, e.g., [3]); the second, arising largely from the artificial intelligence community, is the use of logic in the formal specification and verification of multi-agent systems (see, e.g., [76], [68] for surveys).
     </paragraph>
     <paragraph>
      Historically, the computer-aided verification community focussed on the problem of checking whether a system S satisfies a given property φ, where φ is expressed as a formula of temporal logic (typically either LTL or CTL) [20], [16]. Using temporal logics such as LTL or CTL makes it possible to express properties relating to the temporal ordering of events in a system, but does not enable the expression of strategic properties, such as “component i can guarantee that the system never enters a fail state.” This observation motivated Alur et al. to develop Alternating-time Temporal Logic (ATL) [3], which is explicitly intended to support such reasoning. However, there are important limitations on the game properties that can be expressed using ATL. First, ATL provides no direct mechanism to refer to strategies in the object language – which appears to be required if one intends to capture game-theoretic properties such as Nash equilibrium. Second, the language provides no mechanism for directly representing the preferences of system components – and again, this seems appropriate if one hopes to reason about game-theoretic equilibrium properties, as we do in this paper.
     </paragraph>
     <paragraph>
      The idea of introducing strategies into the object language has been pursued by a number of researchers [14], [50]. Probably the best-known and most successful such formalism is Strategy Logic (SL), which can be thought of as a temporal logic that includes a framework for naming strategies and reasoning about their properties [66], [14], [50].
     </paragraph>
     <paragraph>
      Relatively little work within the computer aided verification community has addressed the problem of capturing the preferences of players, and the role that these preferences play in strategic, game theoretic reasoning. However, of the work on this topic that is present in the literature, it seems fairly common to model player preferences in the same way that we do in the present paper: as temporal logic formulae that the player desires to see satisfied [5], [23] (or else, more generally, as ω-regular objectives [13], [8]). To pick one example of this work, Alur et al. [5] investigated the complexity of game-theoretic questions for games played on graphs, in which players attempt to satisfy a goal, expressed as a temporal logic formula. One aspect of such work is that it assumes that agents make moves in a game arena that is explicitly modelled as a graph. This is an unrealistic assumption in practice, since the state transition graph for any real system will be of size exponential in the number of variables in the system. Moreover, the significance of complexity results for such games might reasonably be questioned, since an unrealistic representation of the game arena is assumed. Similar comments apply to many other studies of game-theoretic properties of concurrent systems.
     </paragraph>
     <paragraph>
      In the second strand of work, researchers in the AI community have developed a range of formalisms intended for the specification and verification of multi-agent systems. Originally, this work focussed on practical reasoning agents, (i.e., planning systems [25]), and in particular, on the belief-desire-intention model of agency [58]. In this model, agents are viewed as selecting intentions from a set of possible desires, which then represent commitments to achieve certain states of affairs; they then select and execute plans of action to achieve their intentions. However, difficulties in obtaining a satisfactory formalisation of rational mental states led researchers to seek alternative foundations for modelling rational action in multi-agent systems, and game theory became increasingly adopted as a foundation. See, e.g., [39] for an excellent survey of this stream of work. Of this body of work, it is worth identifying several threads of research that are related to the present paper. Bulling et al. [11] consider variations of ATL with the explicit intention of reasoning about temporal properties of strategic notions such as Nash equilibrium. The key differences with the present work are, first, that our aim is not to reason about game theoretic properties in the object language; and second, our use of a compact system modelling language (srml) to define the underpinning game structure.
     </paragraph>
     <paragraph>
      Our work in the present article draws upon both of these paradigms, and it is most closely related to the work presented in [29], [30], [33]. In [29], Gutierrez et al. introduced a model called Iterated Boolean Games (iBGs). In an iBG, each player exercises unique control over a set of Boolean variables, and play proceeds over an infinite series of rounds, where at each round each player makes a Boolean assignment to the variables they control. Each player is associated with an LTL formula that the player desires to see satisfied in the LTL model traced out by the infinite play of the game. A key concern of Gutierrez et al. was to classify the complexity of game-theoretic decision problems in iBGs (such as checking for the existence of pure strategy Nash equilibria).{sup:5} Observe that, in contrast to many other studies of game properties in concurrent systems, the arena in which an iBG is played is defined succinctly: simply by listing the variables that each player controls. While we believe the iBG model and the Boolean games model that it generalises are simple and elegant models with which to formulate questions of strategic interaction in multi-agent systems, they clearly represent a very high-level abstraction of real systems. In particular, in iBGs, it is assumed that at every time point, every player has complete freedom to assign values to the variables it controls. This greatly limits the multi-agent scenarios that can be modelled with iBGs. In [30], [33], Gutierrez et al. presented a more realistic model of concurrent programs, but as with other studies of game-like properties in concurrent systems, it assumes that game arenas are explicitly presented – and for the reasons described above, we believe this is an unrealistic assumption in practice.
     </paragraph>
     <paragraph>
      In short, while our broad aim is the same as [5], [11], [13], [8], [29], [30], [33] (i.e., the game-theoretic analysis of concurrent and multi-agent systems), our approach is to use a language for defining game arenas that is much closer to real-world programming and system modelling. We represent game arenas using the Reactive Modules language, which permits the succinct definition of concurrent and multi-agent systems and protocols. Questions relating to the complexity of game-theoretic questions on such succinctly-specified arenas are, we believe, much more meaningful in this context than on arenas in which the game graph is explicitly presented. Interestingly, we find that for many of the decision problems we consider, the complexity does not increase when studying game arenas specified using Reactive Modules.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Algorithms from the main text
     </section-title>
     <paragraph>
      In this appendix, we present algorithms that we held over from the main text in the interests of readability.
     </paragraph>
     <paragraph>
      First, Fig. 12 presents an algorithm that takes as input an RML arena A, and from this arena computes the Kripke structure induced by A. From inspection it is straightforward to see that the algorithm is correct, and is guaranteed to terminate in time exponential in {a mathematical formula}|A|. Lines (3)–(7) compute the initial states {a mathematical formula}SA0. Lines (8)–(18) then extend these initial states to compute all reachable states of the system. Finally, lines (19)–(26) compute the relation {a mathematical formula}RA.
     </paragraph>
     <paragraph>
      Fig. 13 presents an algorithm for checking whether an OLTL formula φ is realizable for a player i from a state s in a Kripke structure {a mathematical formula}KA=(SA,SA0,RA,πA). The algorithm works by backwards induction, building up a labelling function ℓ, which associates with each state in {a mathematical formula}SA the formulae that i can realize from that state. The algorithm is closely related to Zermelo's algorithm, and critically depends upon the fact that the input is an OLTL formula.
     </paragraph>
     <paragraph>
      The algorithm makes use of a subsidiary function {a mathematical formula}can(i,φ,s), which checks to see whether player i has a guarded command available for execution in state s, such that in all states that could result from the execution of this guarded command, the formula φ is true.
     </paragraph>
     <paragraph>
      It is straightforward from construction that the algorithm is correct, and guaranteed to terminate in time exponential in the size of A.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>