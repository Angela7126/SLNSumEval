<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Bounded model checking of strategy ability with perfect recall.
   </title>
   <abstract>
    The paper works with a logic which has the expressiveness to quantify over strategies of bounded length. The semantics of the logic is based on systems with multiple agents. Agents have incomplete information about the underlying system state and their strategies are based on perfect recall memory over observations and local actions. The computational complexity of model checking is shown to be PSPACE-complete. We give two BDD-based model checking algorithms. The algorithms are implemented in a model checker and experimental results are reported to show their applications.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Model checking [1] is a promising technique to automatically verify whether a given system satisfies some property. A property is usually described by a logic formula. Linear temporal logic LTL [2] is used to specify properties such as “Something bad will never happen” (safety property) and “Something good will eventually happen” (liveness property). Computation tree logic CTL [3] and its superset {a mathematical formula}CTL⁎ use branching operators to specify properties over all or some of the paths from a state. Alternating-time temporal logic (ATL) [4] extends CTL with the expressiveness of selective quantifications over the paths. The selective quantifications are expressed with strategy operators which quantify over agents' strategies. ATL has been applied to reason about systems of multiple agents, who make moves by following strategies.
     </paragraph>
     <paragraph>
      Reasoning about strategies generally needs to be done on the basis of incomplete information. In many practical systems like poker games, agents are not supposed to observe everything, especially not able to observe the local states of their opponents. A strategy may be memoryless, which decides the next action by utilising the information available in the current round, or perfect recall, which decides the next action by utilising all available information up to the current round. In this paper, we work about perfect recall strategies. An agent with perfect recall strategy can make maximal use of its reasoning capabilities. Therefore, perfect recall is an optimal assumption over the adversary and a meaningful setting when designing and verifying critical systems.
     </paragraph>
     <paragraph>
      Model checking ATL of incomplete information and perfect recall is shown to have a very high complexity [5]. This pessimistic result prevents us from working with the full logic. In this paper, we work with one of its fragments. The fragment can specify agents' strategies of bounded length, e.g., “Agents in G have a collective strategy to reach the goal ϕ within k steps”, etc. We call this fragment bounded ATL, and show that its model checking problem is PSPACE-complete, no harder than the LTL model checking [6].
     </paragraph>
     <paragraph>
      We present two model checking algorithms for bounded ATL. The idea of bounded model checking [7] has achieved success in software verification, by reducing the model checking problem to the satisfiability problem. Starting from temporal logics, it has been extended to deal with the logic of knowledge, in e.g., [8], [9]. The bounded model checking technique based on SAT solvers usually deals with the positive fragment of a logic to avoid the alternations between existential and universal quantifications. Therefore, it cannot be directly extended to work with bounded ATL, because the semantics of the strategy operator needs a nesting of existential and universal quantifications. Our model checking algorithms are based on binary decision diagrams (BDDs) [10], which is a canonical representation of boolean formulas and has efficient operations including existential and universal quantifications. The first algorithm works with all formulas of bounded ATL. It is, however, less efficient in our experiments. The second algorithm works with an important fragment of bounded ATL, and is significantly more efficient.
     </paragraph>
     <paragraph>
      The research on ATL for both complete information systems and incomplete information systems has been intensive in recent years. However, there are fewer efforts on developing verification tools to work with examples. Mocha [11] works with complete information systems and MCMAS [12], [13] works with incomplete information systems where strategies are memoryless. We implement our algorithms in MCK [14], a model checker for temporal epistemic logics. This is the first time a practical algorithm and tool is brought forward for ATL with incomplete information and perfect recall. We conduct experiments on several examples, including Iterated Prisoner's Dilemma, Kriegspiel Tic-Tac-Toe, and a patrolling game.
     </paragraph>
     <paragraph>
      We also mention that the developed technique can be useful in strategic planning, which has a strong interaction with logic-based knowledge representation and reasoning schemes. Given a start state, a goal condition, and available actions, the objective of planning is to find a sequence of actions leading from start to goal. Most planning techniques are devoted to design specialized algorithms to deal with specific systems and goals. Planning as model checking has been shown to be an effective technique for planning, and is fully motivated by the flexibility of describing goals as logic formulas. It first works with temporal logics [15] and then extends to the logic of knowledge [16] and ATL [17], [18]. Currently, using ATL model checking for planning focuses on memoryless strategies or complete information systems.
     </paragraph>
     <paragraph>
      The outline of the paper is as follows. In the next section, we introduce iterated prisoners' dilemma, which serves as a running example. In Section 3, we present bounded ATL and some formulas describing properties of the running example. The semantics of bounded ATL is settled on a variant of interpreted systems [19] in Section 4 and partially-observed concurrent game structures in Section 5. In Section 6, the running example is analyzed with the provided semantics. Then, we show the complexity of model checking bounded ATL in Section 7 and give two BDD-based algorithms in Section 8 and Section 9, respectively. In Section 10, we present our experimental results. We will then discuss some related works and conclude the paper.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Running example: Iterated Prisoner's Dilemma
     </section-title>
     <paragraph>
      Iterated Prisoner's Dilemma (IPD) [20] is a canonical game in game theory, and has been experimentally analysed by a tournament held in 1980 [21], in which contestants submitted strategies for a 200-repetition Prisoner's Dilemma and the strategies could not be updated during play. The tournament was held again in 2004 and 2005.
     </paragraph>
     <paragraph>
      Prisoner's Dilemma (PD) is described as follows. Two men Carl and Adam are arrested, but the police do not possess enough information for a conviction. Following the separation of the two men, the police offer both a similar deal: if one testifies against his partner (defect) and the other remains silent (cooperate), then the betrayer goes free and the one that remains silent receives a 5-month sentence. If both remain silent, both are sentenced to only one month in jail for a minor charge. If each ‘rats out’ the other, each receives a three-month sentence. Each prisoner must choose either to betray or remain silent. Instead of using penalties as described above, we use rewards to ease the following interpretation. Table 1 gives the rewards. That is, {a mathematical formula}rwd(a1,a2) denotes the rewards of the pair of actions {a mathematical formula}(a1,a2), taken by Carl and Adam, respectively. For example, we have {a mathematical formula}rwd(cooperate,defect)=(0,5), which says that if Carl chooses to cooperate and Adam chooses to defect, then the former gets 0 rewards and the latter gets 5 rewards.
     </paragraph>
     <paragraph>
      An IPD game is a repeated PD game, such that two agents play PD more than once in succession and they remember previous actions of their opponent and may change their actions accordingly. In the games that we are concerned, the agent Adam is given a set of strategies (details will be given later), from which he can choose one to follow. The agent Carl is not informed about which strategy his opponent is following. The incomplete information exists because Carl is not sure about Adam's strategy. The perfect recall is useful for Carl as he may use it to reason, from the past observations, about the strategy Adam is following. The goal of the agent Carl is to maximise the benefits (expressed in terms of logic formulas) under the incomplete information. The game can be seen as a single-agent game of the agent Carl, because the other agent Adam will follow a specific strategy that is chosen initially.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Bounded ATL
     </section-title>
     <paragraph>
      Suppose that we are working with a system of a finite set {a mathematical formula}Agt={1,…,n} of agents. Let Prop be a set of propositions. Bounded ATL combines the temporal operators and the strategic operator to reason about the strategic ability of the agents. It has the syntax as follows.{a mathematical formula} where {a mathematical formula}p∈Prop, {a mathematical formula}k≥0, and {a mathematical formula}A⊆Agt. Instead of setting an overall bound to terminate model checking whenever the bound is reached, as is done in traditional bounded model checking, we impose bounds on formulas to pursue greater flexibility in specifying properties. Intuitively, formula {a mathematical formula}《A》Xϕ expresses that agents in A have a strategy to enforce ϕ at the next time, {a mathematical formula}《A》ϕ1U≤kϕ2 means that, within k steps, agents in A have a strategy to keep enforcing {a mathematical formula}ϕ1 until {a mathematical formula}ϕ2 holds, and {a mathematical formula}《A》ϕ1R≤kϕ2 means that, within k steps, agents in A have a strategy to make sure that only when {a mathematical formula}ϕ1 holds can {a mathematical formula}ϕ2 be released. Formula {a mathematical formula}DAϕ expresses that agents in A have distributed knowledge on the fact ϕ, i.e., they know ϕ by pooling together their available information [19]. Other operators can be obtained in the usual way, e.g., {a mathematical formula}《A》F≤kϕ≡《A》TrueU≤kϕ, {a mathematical formula}《A》G≤kϕ≡《A》FalseR≤kϕ, {a mathematical formula}Kiϕ≡D{i}ϕ, etc. The formula {a mathematical formula}Kiϕ means that agent i knows ϕ[19]. We will present concrete semantics for the formulas, in particular for the statement of “have a strategy to enforce”, later in the next section.
     </paragraph>
     <paragraph>
      In the following, we present several formulas to describe interesting properties of the running example. For instance, in the IPD example, let carlRwd be the accumulated rewards of agent Carl and adamRwd be the accumulated rewards of agent Adam, we may want to check the following specification{a mathematical formula} which expresses that the agent Carl has a strategy to achieve, within k iterations, a better rewards than its opponent Adam. The second specification{a mathematical formula} expresses that the agent Carl can achieve, after k iterations, a rewards more than that defined by Nash Equilibrium, i.e., both of them always defect. Here, we write {a mathematical formula}(《{Carl}》X)kϕ as an abbreviation of {a mathematical formula}《{Carl}》X…《{Carl}》Xϕ, for k repeated {a mathematical formula}《{Carl}》X operators. The third query we might be interested in is, if the agent Carl has the strategy to achieve, after k iterations, the best combined scores, i.e., both of them always cooperate,{a mathematical formula}
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Interpreted systems semantics
     </section-title>
     <paragraph>
      We enrich an interpreted system [19] by actions performed by the agents, and call the resulting system an action interpreted system (AIS). At all times in an AIS, each agent is assumed to be in some local state that records all the information that the agent can access at that time. The environment e records “everything else that is relevant”. Let S be the set of environment states and let {a mathematical formula}Li be the set of local states of agent {a mathematical formula}i∈Agt. A global state s of a multi-agent system is an {a mathematical formula}(n+1)-tuple {a mathematical formula}(se,s1,…,sn) such that {a mathematical formula}se∈S and {a mathematical formula}si∈Li for all {a mathematical formula}i∈Agt.
     </paragraph>
     <paragraph>
      At a global state, every agent independently takes a local action, which represents the decision it makes. The environment, taking into consideration the actions taken by the agents, also takes an action to update the environment state. Let {a mathematical formula}Acte be the set of environment actions and {a mathematical formula}Acti be the set of local actions of agent {a mathematical formula}i∈Agt. A global action of a multi-agent system in some global state is an {a mathematical formula}(n+1)-tuple {a mathematical formula}a=(ae,a1,…,an) such that {a mathematical formula}ae∈Acte and {a mathematical formula}ai∈Acti for all {a mathematical formula}i∈Agt. Let {a mathematical formula}Act=Acte×Act1×…×Actn.
     </paragraph>
     <paragraph>
      Time is represented discretely by using natural numbers. A run is a function {a mathematical formula}r:N→S×L1×…×Ln×Acte×Act1×…×Actn from time to global states and actions. A pair {a mathematical formula}(r,m) consisting of a run r and time m is called a point, which may also be written as {a mathematical formula}r(m). If {a mathematical formula}r(m)=(se,s1,…,sn,ae,a1,…,an) then we define {a mathematical formula}se(r,m)=se, {a mathematical formula}ae(r,m)=ae and {a mathematical formula}si(r,m)=si and {a mathematical formula}ai(r,m)=ai for {a mathematical formula}i∈Agt. Moreover, we write {a mathematical formula}sx(r,k..m) for the sequence {a mathematical formula}sx(r,k)…sx(r,m) and {a mathematical formula}ax(r,k..m) for {a mathematical formula}ax(r,k)…ax(r,m), for {a mathematical formula}x∈Agt∪{e}. Let a system {a mathematical formula}R be a set of runs. Relative to a system {a mathematical formula}R, we define the set {a mathematical formula}Ki(r,m)={(r′,m′)∈R×N|viewi(r′,m′)=viewi(r,m)} to be the set of points that are, for agent i, indistinguishable from the point {a mathematical formula}(r,m). The view function {a mathematical formula}viewi will be defined later in Section 4.1.
     </paragraph>
     <paragraph>
      For a system {a mathematical formula}R of runs, we define a cell c to be a set of runs {a mathematical formula}Rc such that {a mathematical formula}Rc⊆R. (In the game structure semantics presented in the following section, {a mathematical formula}Rc will be made concrete as the set of runs compatible with the strategies that define c.) The set of indistinguishable points for agent i at point {a mathematical formula}(r,m) assuming c is {a mathematical formula}Kic(r,m)=Ki(r,m)∩(Rc×N). Two cells {a mathematical formula}c1 and {a mathematical formula}c2 are strategic equivalent for agent i, denoted as {a mathematical formula}c1≃ic2, if for any two points {a mathematical formula}(r,m),(r′,m′) in {a mathematical formula}c1 or {a mathematical formula}c2, {a mathematical formula}viewi(r,m)=viewi(r′,m′) implies {a mathematical formula}ai(r,m+1)=ai(r′,m′+1). We assume deterministic strategy for all agents, i.e., at each time, the strategy of an agent will give a single action for it to take. Note that, the relation {a mathematical formula}≃i is an equivalence relation, i.e., it is reflexive, symmetric, and transitive. We use {a mathematical formula}[c]C≃i to denote the equivalence class of c in {a mathematical formula}C with respect to the relation {a mathematical formula}≃i and {a mathematical formula}[≃i]C to denote the set of all equivalence classes in {a mathematical formula}C with respect to the relation {a mathematical formula}≃i.
     </paragraph>
     <paragraph>
      An action interpreted system (AIS) is a tuple {a mathematical formula}(R,C,{≃i}i∈Agt,π), where {a mathematical formula}R is a system of runs, {a mathematical formula}C is a set of cells in {a mathematical formula}R such that {a mathematical formula}R=⋃{Rc|c∈C}, {a mathematical formula}{≃i}i∈Agt is a set of strategic equivalences over cells for all agents in Agt, and {a mathematical formula}π:R×N→P(Prop) is an interpretation such that {a mathematical formula}π(r,m)=π(se(r,m)) for all points {a mathematical formula}(r,m). Let {a mathematical formula}A⊆Agt be a set of agents. We assume the distributed knowledge among them, that is, define {a mathematical formula}KA(r,m)=⋂i∈AKi(r,m), {a mathematical formula}KAc(r,m)=⋂i∈AKic(r,m). Moreover, we let {a mathematical formula}≃A=⋂i∈A≃i and {a mathematical formula}aA(r,m)={ai(r,m)|i∈A} be the collective action of agents in A at point {a mathematical formula}(r,m). Likewise, we can define {a mathematical formula}[c]C≃A and {a mathematical formula}[≃A]C.
     </paragraph>
     <paragraph label="Definition 1">
      The semantics of the language in an AIS {a mathematical formula}I=(R,C,{≃i}i∈Agt,π) is given by interpreting formulas ϕ at points {a mathematical formula}(r,m) of {a mathematical formula}I, using a satisfaction relation {a mathematical formula}I,(r,m)⊨ϕ, which is defined inductively as follows.
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨p for {a mathematical formula}p∈Prop if {a mathematical formula}p∈π(r,m).
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨¬ϕ if not {a mathematical formula}I,(r,m)⊨ϕ.
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨ϕ∧ψ if {a mathematical formula}I,(r,m)⊨ϕ and {a mathematical formula}I,(r,m)⊨ψ.
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨《A》Xϕ if there exists an equivalence class {a mathematical formula}[c]C≃A∈[≃A]C of agents A such that
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨《A》ϕU≤kψ if
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨《A》ϕR≤kψ if
      </list-item>
      <list-item label="•">
       {a mathematical formula}I,(r,m)⊨DAϕ if for all {a mathematical formula}(r′,m′)∈KA(r,m), there is {a mathematical formula}I,(r′,m′)⊨ϕ.
      </list-item>
     </list>
     <paragraph>
      Intuitively, in the semantics of {a mathematical formula}《A》Xϕ, the equivalence class {a mathematical formula}[c]C≃A represents a joint winning strategy of A such that for all joint opponent strategies, {a mathematical formula}[c]C≃A enforces a win on every path starting from the current state. The condition that {a mathematical formula}I, {a mathematical formula}(r′,m′+1)⊨ϕ for all {a mathematical formula}(r′,m′)∈KA(r,m) means that, not only there exists such a strategy for agents in A to win, but also they know by pooling together their available information that they will win if follow the strategy. More concretely, the first condition says that the agents A have a strategy that is compatible with the current view. The second condition says that under the new strategy, agents in A have a distributed knowledge that the formula ϕ holds at the next time.
     </paragraph>
     <paragraph>
      A prominent characteristics of the ATL is that it can express, as a formula {a mathematical formula}《A》ϕ, the statement that “a set A of agents have a strategy to enforce ϕ”. The concrete semantics for the formula is unambiguous in complete information system by the “selective quantification” over the paths. More precisely, it says that the formula ϕ holds on those paths where agents in A follow the strategy quantified in the formula. However, it is more involved for incomplete information systems, on which different proposals about the syntax and the semantics are presented, see e.g., [17], [22], [23], [24], [25], [26], [5], [27]. In [17], agents select strategies as if it has the complete information about the system state. It is pointed out in [22], [23] that, in an incomplete information system, it is not appropriate to assume that agents' strategies can base on the full information about the system state. Instead, a strategy should be uniform in the way that the same action should be taken on those states where agents cannot distinguish. It has been further argued that the formula may be interpreted as the existence of a uniform strategy such that every agent in A knows ϕ[24], [25], [26] or the existence of a uniform strategy such that agents in A have a distributed knowledge on ϕ[5]. In [27], Jamroga and van der Hoek formulate a general construct {a mathematical formula}《A》K(B)ϕ which says that there is a strategy for the set A of agents that another set B of agents knows (for notion of group knowledge K, which could be E for everyone knows, D for distributed knowledge, or C for common knowledge) to achieve goal ϕ. In the paper, we assume a similar semantics as that of [5].
     </paragraph>
     <section label="4.1">
      <section-title>
       Synchronous perfect recall view
      </section-title>
      <paragraph>
       Now we define a view function for agents. An agent i has synchronous perfect recall view, denoted as spr, in system {a mathematical formula}R if there exists a set {a mathematical formula}O (of observations) such that for each point {a mathematical formula}(r,m) of {a mathematical formula}R, the view {a mathematical formula}viewi(r,m) is a sequence of exactly {a mathematical formula}(m+1) elements of {a mathematical formula}O and m elements of {a mathematical formula}Acti. The observation of the agent i at a specific point is given by a function {a mathematical formula}Oi:R×N→O. Then the view of agent i is defined by
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}viewi(r,0)=Oi(r,0), and
       </list-item>
       <list-item label="•">
        {a mathematical formula}viewi(r,m+1)=viewi(r,m)⋅ai(r,m+1)⋅Oi(r,m+1) for all {a mathematical formula}m∈N.
       </list-item>
      </list>
      <paragraph>
       There exist other view functions, e.g., the observational view that {a mathematical formula}viewi(r,m)=Oi(r,m), representing that the agent i can only observe the current observation, and the clock view {a mathematical formula}viewi(r,m)=(m,Oi(r,m)), representing that the agent i can observe the current time and the current observation. In this paper, we focus on the synchronous perfect recall view.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Game structure semantics
     </section-title>
     <paragraph>
      In this section we present a finite model called partially observed concurrent game structure (PO-CGS) and define a translation to AIS. A finite PO-CGS for a set Agt of agents is a tuple {a mathematical formula}M=(S,{Actx}x∈{e}∪Agt,{Nx}x∈{e}∪Agt,{Oi}i∈Agt,I,T,π), where
     </paragraph>
     <list>
      <list-item label="•">
       S is a finite set of states,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Acte is a finite set of actions of the environment e, and {a mathematical formula}Acti for {a mathematical formula}i∈Agt is a finite set of local actions of agent i,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Nx:S→P(Actx) indicates the set of actions that are available to {a mathematical formula}x∈Agt∪{e} at a specific state,
      </list-item>
      <list-item label="•">
       {a mathematical formula}I⊆S is a set of initial states,
      </list-item>
      <list-item label="•">
       {a mathematical formula}T⊆S×Act×S is a transition relation,
      </list-item>
      <list-item label="•">
       {a mathematical formula}Oi:S→O is an observation function for agent {a mathematical formula}i∈Agt, and
      </list-item>
      <list-item label="•">
       {a mathematical formula}π:S→P(Prop) is an interpretation of atomic propositions Prop at the states.
      </list-item>
     </list>
     <paragraph>
      We assume that the transition relation T is serial, i.e., for all states s and joint actions a, there exists a state t such that {a mathematical formula}(s,a,t)∈T. For consistency, we further require that for all states {a mathematical formula}s1,s2∈S and {a mathematical formula}i∈Agt, {a mathematical formula}Oi(s1)=Oi(s2) implies {a mathematical formula}Ni(s1)=Ni(s2). We treat the set S of states as the states of the environment rather than as the set of global states, and agent i's local states are derived from the observation function {a mathematical formula}Oi and the actions in {a mathematical formula}Acti that i performs.
     </paragraph>
     <section label="5.1">
      <section-title>
       Executions to runs
      </section-title>
      <paragraph>
       Let {a mathematical formula}s,s′∈S and {a mathematical formula}a∈Act. A path ρ from a state s is a finite or infinite sequence of states and actions {a mathematical formula}s0a1s1a2s2… such that {a mathematical formula}s0=s and {a mathematical formula}(sk,ak+1,sk+1)∈T for all {a mathematical formula}k≥0. Given a path {a mathematical formula}ρ=s0a1s1a2s2… , we use {a mathematical formula}s(ρ,m) to denote its {a mathematical formula}(m+1)-th state {a mathematical formula}sm, {a mathematical formula}a(ρ,m) to denote its m-th action {a mathematical formula}am, in which {a mathematical formula}ae(ρ,m) is its m-th environment action and {a mathematical formula}ai(ρ,m) is its m-th local action of agent i. A fullpath from a state s is an infinite path from s. A path ρ is initialized if {a mathematical formula}s(ρ,0)∈I.
      </paragraph>
      <paragraph>
       From each initialized fullpath ρ, one may define a run in an AIS satisfying spr for all agents. Recall that we interpret the states of the PO-CGS as states of the environment, and the global actions of the PO-CGS as actions of the agents as well as the environment. Given an initialized fullpath ρ, we obtain a run {a mathematical formula}ρspr by defining each point {a mathematical formula}(ρspr,m) with {a mathematical formula}m∈N as follows.
      </paragraph>
      <list>
       <list-item label="•">
        The environment state at time {a mathematical formula}m≥0 is {a mathematical formula}se(ρspr,m)=s(ρ,m).
       </list-item>
       <list-item label="•">
        The environment action and agents' local actions are {a mathematical formula}ae(ρspr,m)=ae(ρ,m) and {a mathematical formula}ai(ρspr,m)=ai(ρ,m) for time {a mathematical formula}m≥1, and {a mathematical formula}ae(ρspr,0)=ai(ρspr,0)=⊥. The symbol ⊥ means empty action. That is, the actions of time 0 does not matter.
       </list-item>
       <list-item label="•">
        The view of agent i at time m is {a mathematical formula}viewi(ρspr,m)=⊥⋅Oi(s(ρ,0))⋅…⋅ai(ρ,m)⋅Oi(s(ρ,m)), representing that the agent remembers all its observations and past local actions, according to spr. Recall that, the local state of agent i at time m is {a mathematical formula}si(ρspr,m)=viewi(ρspr,m).
       </list-item>
      </list>
     </section>
     <section label="5.2">
      <section-title>
       Complete coalition strategies to cells
      </section-title>
      <paragraph>
       A strategy {a mathematical formula}σi of an agent i is a function that maps each finite path {a mathematical formula}ρ=s0a1s1…ansn to an action in {a mathematical formula}Ni(sn). A (finite or infinite) path ρ is compatible with {a mathematical formula}σi if {a mathematical formula}ak+1,i=σi(s0a1…sk) for all {a mathematical formula}k≥0, where {a mathematical formula}ak+1,i is agent i's local action in the global action {a mathematical formula}ak+1. Given a PO-CGS M and a strategy {a mathematical formula}σi of agent i, write {a mathematical formula}Path(M,σi) for the set of fullpaths in M that are compatible with {a mathematical formula}σi. A strategy {a mathematical formula}σi is uniform if for all paths {a mathematical formula}ρ,ρ′∈Path(M,σi) and {a mathematical formula}m∈N, we have {a mathematical formula}viewi(ρ,m)=viewi(ρ′,m) implies {a mathematical formula}ai(ρ,m+1)=ai(ρ′,m+1), i.e., i's reactions following {a mathematical formula}σi respect its views.
      </paragraph>
      <paragraph>
       Let A be a set of agents. A coalition strategy {a mathematical formula}σA fixes a strategy {a mathematical formula}σi for each agent {a mathematical formula}i∈A. We let {a mathematical formula}Path(M,σA)=⋂i∈AgtPath(M,σi). Note that, in {a mathematical formula}Path(M,σA) for a uniform strategy {a mathematical formula}σA, the strategies of agents in {a mathematical formula}Agt∖A are not required to be uniform, i.e., they are allowed to perform arbitrary behaviours.
      </paragraph>
      <paragraph>
       We call {a mathematical formula}σA a complete coalition strategy if {a mathematical formula}A=Agt, or an incomplete coalition strategy if {a mathematical formula}A⊂Agt. Given a complete coalition strategy {a mathematical formula}σAgt={σi|i∈Agt}, a cell c is a subset of runs {a mathematical formula}Rc=Path(M,σAgt).
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Incomplete coalition strategies to equivalence classes over cells
      </section-title>
      <paragraph>
       Let {a mathematical formula}A¯=Agt∖A be the complement set of agents of A. For each incomplete coalition strategy {a mathematical formula}σA, there may exist more than one incomplete coalition strategy {a mathematical formula}σA¯. As a complete coalition strategy {a mathematical formula}σA∪σA¯ restricts the system {a mathematical formula}R into a cell, an incomplete coalition strategy {a mathematical formula}σA restricts {a mathematical formula}R into a set of cells, each of which corresponds with an incomplete coalition strategy of {a mathematical formula}σA¯ of agents {a mathematical formula}A¯. The following statement ascertains that these cells are strategic equivalent.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}σAbe an incomplete uniform coalition strategy of A and{a mathematical formula}σA¯1and{a mathematical formula}σA¯2be two incomplete (maybe non-uniform) coalition strategies of{a mathematical formula}A¯. Let{a mathematical formula}c1and{a mathematical formula}c2be the cells for complete strategy{a mathematical formula}σA∪σA¯1and{a mathematical formula}σA∪σA¯2respectively. Then we have{a mathematical formula}c1≃Ac2.Let {a mathematical formula}i∈A be any agent in A, and {a mathematical formula}(r1,m1)∈Rc1 and {a mathematical formula}(r2,m2)∈Rc2 be any two points. Assume that {a mathematical formula}viewi(ρ1,m)=viewi(ρ2,m). Then because agent i has the same strategy {a mathematical formula}σi in {a mathematical formula}c1 and {a mathematical formula}c2, spr ensures {a mathematical formula}m=m′ and {a mathematical formula}ai(r,m+1)=σi(s(ρ,m))=σi(s(ρ,m′))=ai(r′,m′+1).  □
      </paragraph>
      <paragraph>
       Here we remark that, a single run {a mathematical formula}r∈R may belong to different cells or even different equivalence classes. Also, there might exist more than one strategy of coalition A that are mapped to the same equivalence class over cells. Plainly, such strategies may disagree only on incompatible runs.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       PO-CGS to AIS
      </section-title>
      <paragraph>
       The system M gives us an interpretation π on its states, and we may lift this to an interpretation on the points {a mathematical formula}(r,m) of {a mathematical formula}R by defining {a mathematical formula}π(r,m)=π(se(r,m)). Using the construction above, we then obtain the action interpreted system {a mathematical formula}I(M)=I(R,C,{≃i}i∈Agt,π) where {a mathematical formula}C is the set of cells corresponding to complete coalition strategies and {a mathematical formula}≃i is a strategic equivalence of agent i over {a mathematical formula}C.
      </paragraph>
      <paragraph>
       We will be interested in the problem of model checking in the PO-CGS. A formula ϕ is said to hold in M, written as {a mathematical formula}M⊨ϕ, if {a mathematical formula}I(M),(r,0)⊨ϕ for all {a mathematical formula}r∈R. The model checking problem is then to determine, given a PO-CGS M and a formula ϕ, whether {a mathematical formula}M⊨ϕ.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Analyzing Iterated Prisoner's Dilemma
     </section-title>
     <paragraph>
      Recall that, in the IPD games, carlRwd and adamRwd are accumulated rewards of Carl and Adam and the agent Adam follows a strategy τ chosen from a set of strategies. A game state is a tuple {a mathematical formula}(carlRwd,adamRwd,τ), where τ is the strategy selected by agent Adam. Let Φ be the set of strategies provided to agent Adam. The initial game states are {a mathematical formula}I={(0,0,τ)|τ∈Φ}. Intuitively, Adam's strategy is chosen initially.
     </paragraph>
     <paragraph>
      A play ρ of the game consists of a sequence of finite or infinite number of states and actions {a mathematical formula}s0a1s1… , where {a mathematical formula}s0∈I, {a mathematical formula}am=(am,Carl,am,Adam) is the global action of the agents such that {a mathematical formula}am,i∈{cooperate,defect} for {a mathematical formula}i∈{Carl,Adam}, and if {a mathematical formula}sm=(rw1,rw2,τ) and {a mathematical formula}sm+1=(rw1′,rw2′,τ′) then {a mathematical formula}τ=τ′ and {a mathematical formula}(rw1′−rw1,rw2′−rw2)=rwd(am+1) is the reward pair of joint action {a mathematical formula}am+1 in Table 1.
     </paragraph>
     <paragraph>
      In each game state, each agent makes an observation of the game state. This is captured by an observation function {a mathematical formula}Oi with domain the set of game states for {a mathematical formula}i∈{Carl,Adam}. We define
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}OCarl(rw1,rw2,τ)=(rw1,rw2), representing that Carl cannot observe the strategy selected by Adam, and
      </list-item>
      <list-item label="•">
       {a mathematical formula}OAdam(rw1,rw2,τ)=(rw1,rw2,τ), representing that Adam can observe the game state.
      </list-item>
     </list>
     <paragraph>
      An agent's perfect recall view of a play {a mathematical formula}s0a1s1… , denoted as {a mathematical formula}viewi(s0a1s1…), is the sequence of observations and local actions {a mathematical formula}Oi(s0)a1,iOi(s1)… . Recall that, a strategy {a mathematical formula}σi for agent i maps each finite possible view {a mathematical formula}α=Oi(s0)a1,i…Oi(sm) of the agent to a set of actions {a mathematical formula}{cooperate,defect}. A complete strategy is a mapping σ associating a strategy {a mathematical formula}σi to each agent i.
     </paragraph>
     <paragraph>
      Now, in a concrete game, assuming that Adam's strategy can be either
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}τ1: cooperate first and then follow the previous action of Carl, or
      </list-item>
      <list-item label="2.">
       {a mathematical formula}τ2: alternate between cooperate and defect.
      </list-item>
     </list>
     <paragraph>
      We use IPD(k) to denote such a game of up to k iterations. Fig. 1 gives the finite model for the game IPD(3). Each node {a mathematical formula}(rw1,rw2,τ) denotes a game state. An arrow from a node s to another node t denotes the transition relation between the two states. The label {a mathematical formula}(a1,a2) on an arrow denotes the action taken by Carl and Adam, respectively. We ignore the environment action skip. For abbreviation, in the figure, we write co for cooperate and de for defect.
     </paragraph>
     <paragraph>
      First, let's see the capability of synchronous perfect recall in reasoning about strategies. For example, in game states {a mathematical formula}(8,8,τ1) or {a mathematical formula}(8,8,τ2), if the agent Carl can only observe his current state, then he cannot distinguish them by the definition of function {a mathematical formula}OCarl. However, with spr, if the view is {a mathematical formula}(0,0)co(3,3)co(3,8)de(8,8) then Carl knows exactly that Adam is following the strategy {a mathematical formula}τ2. After identifying the opponent's strategy, he can play optimally.
     </paragraph>
     <paragraph>
      Now, let's find Carl's strategies for the specifications presented before. For specification (1), there exists at least a strategy {a mathematical formula}σCarl1 such that
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}σCarl1((0,0))=defect,
      </list-item>
      <list-item label="•">
       {a mathematical formula}σCarl1((0,0)de(5,0))=cooperate,
      </list-item>
      <list-item label="•">
       {a mathematical formula}σCarl1((0,0)de(5,0)co(5,5))=defect.
      </list-item>
     </list>
     <paragraph>
      For specification (2), it's not hard to see that Carl can take any strategy.
     </paragraph>
     <paragraph>
      For specification (3), we notice that there is a path{a mathematical formula} leading from an initial state to a state satisfying the proposition {a mathematical formula}carlRwd+adamRwd≥18. However, the agent Carl does not have a strategy to guarantee the achievement of this goal.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Model checking complexity
     </section-title>
     <paragraph>
      In this section, we confirm the intuition about the decidability of model checking bounded ATL. More precisely, we show that it is PSPACE-complete.
     </paragraph>
     <paragraph label="Proof">
      Let M be a PO-CGS of n agents, ϕ be a bounded ATL formula, and{a mathematical formula}m≥0be the maximal number appears in ϕ. Then the complexity of deciding if{a mathematical formula}M⊨ϕis in PSPACE.We present an alternating algorithm, different with the one in the next section, for model checking {a mathematical formula}M⊨ϕ. It works on a set of initialized paths of length {a mathematical formula}|ϕ|⋅m, i.e.,{a mathematical formula} Note that the set {a mathematical formula}Rh is of size {a mathematical formula}O((|M|⋅|Act|)|ϕ|⋅k) by letting {a mathematical formula}|M| be the number of states and {a mathematical formula}|Act| be the number of global actions. Our algorithm avoids the explicit construction of this set.The satisfiability of an expression {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ is computed recursively by the following procedure, where {a mathematical formula}(r,k) is a point in {a mathematical formula}Rh and {a mathematical formula}vi is a sequence of observations and actions of agent i. Intuitively, this expression states that the formula ϕ holds in the point {a mathematical formula}(r,k) of {a mathematical formula}Rh under the view {a mathematical formula}vi for all agent {a mathematical formula}i∈Agt.
      <list>
       Let {a mathematical formula}ϕ=p. Then {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ if {a mathematical formula}p∈π(r,k).Let {a mathematical formula}ϕ=¬ϕ′. Then {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ if not {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ′.Let {a mathematical formula}ϕ=ϕ1∧ϕ2. Then {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ if {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ1 and {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ2.Let {a mathematical formula}ϕ=《A》Xϕ′. Then {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ if we canThe cases of {a mathematical formula}ϕ=《A》ϕ1U≤kϕ2 and {a mathematical formula}ϕ=《A》ϕ1R≤kϕ2 are done by unfolding the formulas as the way in the semantics.Let {a mathematical formula}ϕ=DAϕ′. Then {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ if we can universally verify {a mathematical formula}Rh,(r′,k),{v1′,…,vn′}⊨ϕ′ for all runs {a mathematical formula}r′ such that {a mathematical formula}si(r′,k)=vi for all {a mathematical formula}i∈A, where {a mathematical formula}vi′=si(r′,k) for {a mathematical formula}i∈Agt.The algorithm proceeds from time 0 to time
      </list>
      <paragraph>
       {a mathematical formula}O(m⋅|ϕ|). When handling relation {a mathematical formula}Rh,(r,k),{v1,…,vn}⊨ϕ, it needs {a mathematical formula}s(M,Act,ϕ,m)=O(n⋅|ϕ|⋅m⋅(log⁡|M|+log⁡|Act|)) bits to remember the views {a mathematical formula}{v1,…,vn}, where n is the number of agents, {a mathematical formula}|ϕ|⋅m is the maximal length of the view, and {a mathematical formula}log⁡|M|+log⁡|Act| is the number of bits to store an observation. The whole recursive procedure needs {a mathematical formula}a(ϕ,m)=O(|ϕ|⋅m) alternations. By Theorem 4.2 of [28], the algorithm can be simulated by a deterministic machine using {a mathematical formula}a(ϕ,m)s(M,Act,ϕ,m)+s(M,Act,ϕ,m)2=O(|ϕ|⋅m⋅n⋅|ϕ|⋅m⋅(log⁡|M|+log⁡|Act|)+(n⋅|ϕ|⋅m⋅(log⁡|M|+log⁡|Act|))2) space. Therefore, we have the upper bound of PSPACE.  □
      </paragraph>
     </paragraph>
     <paragraph label="Proof">
      Let M be a PO-CGS of n agents, ϕ be a bounded ATL formula, and{a mathematical formula}k≥0be the maximal number appears in ϕ. Then the complexity of deciding if{a mathematical formula}M⊨ϕis PSPACE-hard.The lower bound can be obtained by a reduction from the satisfiability problem of the quantified Boolean formula (QBF), which is to determine if a QBF formula is satisfiable. A canonical form of a QBF is{a mathematical formula} where {a mathematical formula}Qi=∃ if i is an odd number and {a mathematical formula}Qi=∀ otherwise, and {a mathematical formula}lkj∈{x1,…,xn,¬x1,…,¬xn} for all {a mathematical formula}1≤k≤m and {a mathematical formula}1≤j≤3. Without loss of generality, we assume that n is an even number. Every QBF formula can be transformed into this format by inserting dummy variables. For a literal {a mathematical formula}lkj, we write {a mathematical formula}var(lkj) for its variable and {a mathematical formula}sign(lkj) for its sign. For example, if {a mathematical formula}lkj=¬x1 then {a mathematical formula}var(lkj)=x1 and {a mathematical formula}sign(lkj)=neg, and if {a mathematical formula}lkj=xn then {a mathematical formula}var(lkj)=xn and {a mathematical formula}sign(lkj)=pos.The problem can be simulated by a game between two agents ∀ and ∃. The game consists of two phases: in the first phase, agents decide the values of variables {a mathematical formula}{x1,…,xn}, and in the second phase, agents evaluate the boolean formula {a mathematical formula}(l11∨l12∨l13)∧…∧(lm1∨lm2∨lm3). We write {a mathematical formula}odd(k) ({a mathematical formula}even(k)) to denote that the number k is an odd (even, resp.) number. The sets of local actions are {a mathematical formula}Act∃={at,af}∪{l1,l2,l3}∪{⊥} and {a mathematical formula}Act∀={at,af}∪{c1,…,cm}∪{⊥}. A joint action is written as a pair {a mathematical formula}(a∃,a∀) such that {a mathematical formula}a∃∈Act∃ and {a mathematical formula}a∀∈Act∀. The set of atomic propositions is {a mathematical formula}Prop={l,r}∪{x1,…,xn}∪{pos,neg}∪{c1,…,cm}. The set of observations is {a mathematical formula}O=P(Prop). A diagram to ease the understanding of the reduction is shown in Fig. 2.The core part of the first phase of a game is a chain of diamond structures, each of which is to decide the value of a variable by one of the agents. Concretely, we introduce a state c and for every variable {a mathematical formula}xk, three states {a mathematical formula}xk,xk0,xk1. We use pair {a mathematical formula}(a∃,a∀) for {a mathematical formula}a∃∈Act∃ and {a mathematical formula}a∀∈Act∀ to denote a global action. The environment action is omitted. The transition relation T is defined as follows.
      <list>
       {a mathematical formula}(xk,(at,⊥),xk1),(xk,(af,⊥),xk0)∈T for {a mathematical formula}1≤k≤n and {a mathematical formula}odd(k),{a mathematical formula}(xk,(⊥,at),xk1),(xk,(⊥,af),xk0)∈T for {a mathematical formula}1≤k≤n and {a mathematical formula}even(k),{a mathematical formula}(xk1,(⊥,⊥),xk+1),(xk0,(⊥,⊥),xk+1)∈T for {a mathematical formula}1≤k&lt;n, and{a mathematical formula}(xn1,(⊥,⊥),c),(xn0,(⊥,⊥),c)∈T.In
      </list>
      <paragraph>
       Fig. 2, we write action {a mathematical formula}at for the joint action {a mathematical formula}(at,⊥) or {a mathematical formula}(⊥,at), depending on the current state {a mathematical formula}xk. The same for action {a mathematical formula}af. We omit the action if it is {a mathematical formula}(⊥,⊥).Agent ∃ decides the value of variable {a mathematical formula}xk if k is an odd number and agent ∀ decides the value of variable {a mathematical formula}xk if k is an even number. On state {a mathematical formula}xk, if one of the agents take {a mathematical formula}at action, then the value is true and the next state is {a mathematical formula}xk1, and if one of the agents take {a mathematical formula}af action, then the value is false and the next state is {a mathematical formula}xk0. The game will deterministically move into state {a mathematical formula}xk+1 or c if the current state is either {a mathematical formula}xk0 or {a mathematical formula}xk1. The observation function and the labelling function are defined as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}O∃(xk0)={r} and {a mathematical formula}O∃(xk1)={l} for {a mathematical formula}1≤k≤n and {a mathematical formula}even(k), and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}r∈π(xk0) and {a mathematical formula}l∈π(xk1) for {a mathematical formula}1≤k≤n and {a mathematical formula}even(k).
       </list-item>
      </list>
      <paragraph>
       Intuitively, propositions {a mathematical formula}l,r are labelled on states {a mathematical formula}xk0,xk1 for k an even number, and are allowed to be observed by agent ∃. This is designed for ∃ to learn the decisions made by its adversary ∀. In Fig. 2, a state may be labelled with a set of atomic propositions. For example, the state {a mathematical formula}x211 is labelled with {a mathematical formula}{x1,pos}.After all variables are assigned values via agents taking actions, the game will move into state c, from which the second phase of the game starts. In the second phase, we need to verify the satisfiability of literals {a mathematical formula}lkj. Without loss of generality, we assume that {a mathematical formula}var(lkj)=xq. Notice that although the value of {a mathematical formula}xq has been decided before, it cannot be encoded into the game state, because that would incur a polynomial space to remember the values of all variables, while the desired reduction should be a polynomial time or logarithmic space reduction. Therefore, we exploit the ability of incomplete information by taking another two chains of diamond structures for variable {a mathematical formula}xq, exactly the same as the one in the core part from the state {a mathematical formula}xq+1 to the state c. We call them helper chains.Concretely, we introduce a set {a mathematical formula}{xkq0,xk1q0,xk0q0,xkq1,xk1q1,xk0q1|1≤q≤n,q&lt;k≤n}∪{cq0,cq1|1≤q≤n} of states, where {a mathematical formula}xkq0,xk1q0,xk0q0,cq0 are for the chain of diamond structures in which variable {a mathematical formula}xq has been given value 0 and {a mathematical formula}xkq1,xk1q1,xk0q1,cq1 are for the chain of diamond structures in which variable {a mathematical formula}xq has been given value 1. The transition relation for the chains with {a mathematical formula}1≤q≤n and {a mathematical formula}i∈{0,1} is such that
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(xkqi,(at,⊥),xk1qi),(xkqi,(af,⊥),xk0qi)∈T for {a mathematical formula}q&lt;k≤n and {a mathematical formula}odd(k),
       </list-item>
       <list-item label="2.">
        {a mathematical formula}(xkqi,(⊥,at),xk1qi),(xkqi,(⊥,af),xk0qi)∈T for {a mathematical formula}q&lt;k≤n and {a mathematical formula}even(k),
       </list-item>
       <list-item label="3.">
        {a mathematical formula}(xk1qi,(⊥,⊥),xk+1qi),(xk0qi,(⊥,⊥),xk+1qi)∈T for {a mathematical formula}q&lt;k&lt;n, and
       </list-item>
       <list-item label="4.">
        {a mathematical formula}(xn1qi,(⊥,⊥),cqi),(xn0qi,(⊥,⊥),cqi)∈T.
       </list-item>
      </list>
      <paragraph>
       The structure of helper chains are the same as that of the main chain, except that they start from the state {a mathematical formula}xq+1q0 or {a mathematical formula}xq+1q1. The observation function and labelling function are defined as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}O∃(xk0qi)={r} and {a mathematical formula}O∃(xk1qi)={l} for {a mathematical formula}q&lt;k≤n and {a mathematical formula}even(k).
       </list-item>
       <list-item label="2.">
        {a mathematical formula}r∈π(xk0qi) and {a mathematical formula}l∈π(xk1qi) for {a mathematical formula}q&lt;k≤n and {a mathematical formula}even(k).
       </list-item>
      </list>
      <paragraph>
       Intuitively, it allows the agent ∃ to observe the behaviour of its adversary. The assigned values of the variables taken by the agent ∃ can be retrieved from her history of local actions, because we assume perfect recall. On the other hand, the assigned values of the variables taken by the agent ∀ cannot be retrieved from agent ∃'s history of observations, as our semantics assumes that agents cannot observe their opponent's local actions. The agent ∃'s observations {a mathematical formula}{l} and {a mathematical formula}{r} on states are to simulate the procedure of the agent ∀ announcing the value to the agent ∃.The helper chains are connected with the main chain by the following transition relation.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(xk0,(⊥,⊥),xk+1k0),(xk1,(⊥,⊥),xk+1k1)∈T for {a mathematical formula}1≤k&lt;n, and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}(xn0,(⊥,⊥),cn0),(xn1,(⊥,⊥),cn1)∈T.
       </list-item>
      </list>
      <paragraph>
       We need some extra labelling as follows. They tell the values of variables and will be used later in the formula expressing the existence of ∃'s strategy.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}{xk,pos}⊆π(xk+1k1) and {a mathematical formula}{xk,neg}⊆π(xk+1k0) for {a mathematical formula}1≤k&lt;n, and
       </list-item>
       <list-item label="2.">
        {a mathematical formula}{xn,pos}⊆π(cn1) and {a mathematical formula}{xn,neg}⊆π(cn0).
       </list-item>
      </list>
      <paragraph>
       The helper chains and the main chain of diamond structures form the first phase of the game. Intuitively, if one of the agents decides that the variable {a mathematical formula}xi is true, then the game may nondeterministically explore either the main chain or the helper chain labelled with {a mathematical formula}{xi,pos}. Otherwise, it may nondeterministically explore either the main chain or the helper chain labelled with {a mathematical formula}{xi,neg}. The agent ∃ cannot distinguish these chains and therefore the same actions should be taken on them because of the uniformity of strategy.At the end of the chains of diamond structures, the game may reach one of the states {a mathematical formula}{c}∪{ck0,ck1|1≤k≤n}, from which the second phase of the game starts. This phase consists of two steps. In the first step, the agent ∀ selects one of the clauses {a mathematical formula}ck which she believes is not satisfiable. In the second step, the agent ∃ challenges this by selecting one of the literals {a mathematical formula}lkj. The game ends with an evaluation on their choices. We say that agent ∃ wins if {a mathematical formula}lkj is satisfiable, and loses, otherwise.Concretely, we introduce states {a mathematical formula}{c1,…,cm}∪{c1k0,…,cmk0|1≤k≤n}∪{c1k1,…,cmk1|1≤k≤n}∪{vk0,vk1|1≤k≤n}. The transition relation is defined as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(c,(⊥,ck),ck)∈T for {a mathematical formula}1≤k≤m,
       </list-item>
       <list-item label="2.">
        {a mathematical formula}(cdi,(⊥,ck),ckdi)∈T for {a mathematical formula}1≤k≤m, {a mathematical formula}1≤d≤n, {a mathematical formula}i∈{0,1},
       </list-item>
       <list-item label="3.">
        {a mathematical formula}(ckdi,(lj,⊥),vdi)∈T for {a mathematical formula}1≤k≤m, {a mathematical formula}1≤d≤n, {a mathematical formula}i∈{0,1}, {a mathematical formula}j∈{1,2,3}, and
       </list-item>
       <list-item label="4.">
        {a mathematical formula}(ck,(lj,⊥),xd+1di)∈T for {a mathematical formula}1≤k≤m and {a mathematical formula}j∈{1,2,3} such that {a mathematical formula}var(lkj=xd) and {a mathematical formula}sign(lkj)=i.
       </list-item>
      </list>
      <paragraph>
       In Fig. 2, to keep the diagram simple, we make a copy of states c, {a mathematical formula}c11 and {a mathematical formula}c10 to the right part of the diagram, and connect them via dashed lines with their original states in the left part of the diagram. Also, we write action {a mathematical formula}ck for {a mathematical formula}(⊥,ck) and {a mathematical formula}lj for {a mathematical formula}(lj,⊥).Also, we define the observation function and the labelling function as follows.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}O∃(ck)={ck}, {a mathematical formula}O∃(ckdi)={ck} for {a mathematical formula}1≤k≤m, {a mathematical formula}1≤d≤n, {a mathematical formula}i∈{0,1},
       </list-item>
       <list-item label="2.">
        {a mathematical formula}ck∈π(ck), {a mathematical formula}ck∈π(ckdi) for {a mathematical formula}1≤k≤m, {a mathematical formula}1≤d≤n, {a mathematical formula}i∈{0,1}, and
       </list-item>
       <list-item label="3.">
        {a mathematical formula}{xk,pos}⊆π(vk1) and {a mathematical formula}{xk,neg}⊆π(vk0) for {a mathematical formula}1≤k≤n.
       </list-item>
      </list>
      <paragraph>
       Intuitively, each of the states {a mathematical formula}{c}∪{ck0,ck1|1≤k≤n} will lead to m states, each of which represents a clause. If the clause state is from a helper chain where the value of variables {a mathematical formula}xk is selected to be {a mathematical formula}sg∈{pos,neg}, then all choices of literal actions by agent ∃ result in a state labelled {a mathematical formula}{xk,sg}. If the clause state is from the main chain, then the literal action will take the game state to some state {a mathematical formula}xd+1di in the chains which is labelled with {a mathematical formula}{xd,sg}, such that {a mathematical formula}xd is the variable of the literal selected by the agents, and {a mathematical formula}sg=pos and {a mathematical formula}i=1 if the value of the variable {a mathematical formula}xd selected by one of the agents is true, and {a mathematical formula}sg=neg and {a mathematical formula}i=0, otherwise. Each clause state is labelled with a proposition {a mathematical formula}ci which is allowed to be observed by the agent ∃. In other word, the agent ∃ knows the current clause that its adversary thinks is unsatisfiable. She is uncertain about which chains the state is from and therefore is expected to take the same literal action across them.The obtained PO-CGS M is a tuple {a mathematical formula}(S,{Actx}x∈{e}∪Agt,{Nx}x∈{e}∪Agt,{Oi}i∈Agt,I,T,π). The set of initial states is {a mathematical formula}I={x1}. The set S of states, the observation function {a mathematical formula}Oi for {a mathematical formula}i∈{∃,∀}, the transition relation T, and the labelling function π have been introduced in the above construction. The environment does not have meaningful action, i.e., {a mathematical formula}Acte={⊥} and {a mathematical formula}Nx(s)=⊥ for all {a mathematical formula}s∈S. We therefore ignore its ⊥ action in the joint action and transition relation. The function {a mathematical formula}N∃ and {a mathematical formula}N∀ can be easily computed from the transition relation T, i.e., let {a mathematical formula}ai∈Ni(s) for {a mathematical formula}i∈{∃,∀} and {a mathematical formula}s∈S if there exist an adversary action {a mathematical formula}aj∈Actj, with {a mathematical formula}j∈{∃,∀} and {a mathematical formula}j≠i, and a state {a mathematical formula}t∈S such that {a mathematical formula}(s,a,t)∈T, where {a mathematical formula}a=(ai,aj) if {a mathematical formula}i=∃ and {a mathematical formula}a=(aj,ai) if {a mathematical formula}i=∀.We proceed to introduce the formula expressing the existence of a strategy of agent ∃ to win the game. Before giving the winning condition, we say that the game ends after the two phases have finished. The first phase takes exactly 2n steps, i.e., each variable needs 2 steps to decide its value and pass through a diamond structure. The second phase takes exactly 2 steps: the agent ∀ chooses a clause and then the agent ∃ chooses a literal within the clause. Therefore, we have{a mathematical formula} which states that agent ∃ has a strategy to win the game after {a mathematical formula}2n+2 steps.For the winning condition win, we assume that after {a mathematical formula}2n+2 steps, the game reaches a literal, say {a mathematical formula}l11. Without loss of generality, we let {a mathematical formula}var(l11)=x1 and {a mathematical formula}sign(l11)=pos. Then by the construction, the game may be at the state labelled with {a mathematical formula}{x1,pos}, reachable from the state c in the main chain of diamond structures. If the agent ∃ assigns value true to the variable {a mathematical formula}x1 in the first phase, then we know that the game may explore either the main chain or the chain labelled with {a mathematical formula}{x1,pos}. Therefore, the game may nondeterministically move into a set of states, including those two labelled with {a mathematical formula}{x1,pos}. Also notice that, none of the states labelled with {a mathematical formula}{x1,neg} can be in the set, since the chain labelled with {a mathematical formula}{x1,neg} is not explored. Therefore, we have {a mathematical formula}K∃(x1⇒pos), meaning that all states in the set satisfy {a mathematical formula}x1⇒pos. In this case, we say that agent ∃ wins, i.e., the clause {a mathematical formula}c1 is satisfiable (recall that the agent ∀ selects {a mathematical formula}c1 because she believes that it is unsatisfiable). On the other hand, if the agent ∃ assigns value false to the variable {a mathematical formula}x1 in the first phase, then the game may reach states {a mathematical formula}{x1,pos} and {a mathematical formula}{x1,neg}. In this case, we have that {a mathematical formula}¬K∃(x1⇒pos) and thus the agent ∃ loses, i.e., the clause {a mathematical formula}c1 is not satisfiable.We can also conclude {a mathematical formula}K∃(x1⇒neg), and agent ∃ wins, if {a mathematical formula}sign(l11)=neg and the agent ∃ assigns value false to the variable {a mathematical formula}x1. In this case, the clause {a mathematical formula}c1 is also satisfiable. We further notice that, if {a mathematical formula}var(l11)≠x1 then the expression {a mathematical formula}(K∃(x1⇒pos))∨(K∃(x1⇒neg)) is a tautology. Therefore, we have{a mathematical formula}It's not hard to see that the system M is of size {a mathematical formula}O(n2+nm) and can be constructed in polynomial time. Because the QBF problem is PSPACE-complete, the complexity of model checking bounded ATL is PSPACE-hard.  □
      </paragraph>
     </paragraph>
     <paragraph>
      The PSPACE complexity result is interesting by its own. As is known [29], two agent reachability game is EXPTIME-complete. However, the reachability game of polynomial steps is strictly simpler at PSPACE-complete.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      A symbolic BDD-based bounded model checking algorithm
     </section-title>
     <paragraph>
      While in general, model checking ATL of incomplete information and synchronous perfect recall has a very high complexity [5], we have shown that one of its fragments, bounded ATL, is PSPACE-complete, no harder than LTL model checking. In this section, we put forward a symbolic model checking algorithms based on BDD's for bounded ATL.
     </paragraph>
     <section label="8.1">
      <section-title>
       BDD
      </section-title>
      <paragraph>
       BDDs [10] are a canonical representation of boolean functions that can, in practice, be quite compact and that support efficient computation of operations, e.g., boolean operations {a mathematical formula}∧,¬,∨,⟹,⇔, boolean quantification {a mathematical formula}∃,∀, an operation = to decide if two functions are equivalent, and a variable substitution operation {a mathematical formula}f[v↦v′] which renames input variable v to {a mathematical formula}v′ in the function f. These BDD operations allow us to map a boolean or QBF formula to a BDD in an obvious way.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Algorithm
      </section-title>
      <paragraph>
       Given a formula ϕ, we define {a mathematical formula}d(ϕ) to be its maximal temporal depth such that
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}d(p)=0, {a mathematical formula}d(¬ϕ)=d(ϕ),
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(ϕ1∧ϕ2)=max{d(ϕ1),d(ϕ2)}
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(《A》Xϕ)=d(ϕ)+1
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(《A》ϕ1U≤kϕ2)=max{d(ϕ1),d(ϕ2)}+k
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(《A》ϕ1R≤kϕ2)=max{d(ϕ1),d(ϕ2)}+k
       </list-item>
       <list-item label="•">
        {a mathematical formula}d(DAϕ)=d(ϕ)
       </list-item>
      </list>
      <paragraph>
       Let the size of formula be the number of operators and the size of model be the number of states. The maximal temporal depth is {a mathematical formula}O(|ϕ|⋅k). Let {a mathematical formula}ase[0..d](r)=se(r,0)a(r,1)…a(r,d)se(r,d) be the run prefix of {a mathematical formula}r∈R up to time d. It is computed by the following expression.{a mathematical formula} We write {a mathematical formula}Rd(M) for the set of run prefixes up to time d, i.e.,{a mathematical formula}
      </paragraph>
      <paragraph label="Definition 2">
       Given a formula ϕ, we define a function {a mathematical formula}f(φ,x):Rd(ϕ)(M)→{0,1}, to be the encoding of the subformula φ of ϕ holds at time x of runs with prefix {a mathematical formula}t∈Rd(ϕ)(M). These values can be computed recursively by the rules as follows.
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}f(p,x)(t)=p∈π(t(x))
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(¬φ,x)(t)=¬f(φ,x)(t)
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(φ1∧φ2,x)(t)=f(φ1,x)(t)∧f(φ2,x)(t)
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(《A》φ1U≤kφ2,x)(t)={a mathematical formula}
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(《A》φ1R≤kφ2,x)(t)={a mathematical formula}
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(《A》Xφ,x)(t)=∃aA:{a mathematical formula}
       </list-item>
       <list-item label="•">
        {a mathematical formula}f(DAφ,x)(t)=∀t′∈Rd(M):viewequA(t,t′,x)⇒f(φ,x)(t′)
       </list-item>
      </list>
      <paragraph>
       The function {a mathematical formula}viewequA(t,t′,x) represents that two run fragments t and {a mathematical formula}t′ are indistinguishable to agents in A up to time x. The following theorem characterises model checking using the function {a mathematical formula}f(φ,x). Note that both the set {a mathematical formula}Rd(M) of run fragments and the encoding {a mathematical formula}f(ϕ,0)(t) are parameterised over the bound {a mathematical formula}d(ϕ).
      </paragraph>
      <paragraph label="Theorem 3">
       Let M be any finite PO-CGS and ϕ a bounded ATL formula, we have{a mathematical formula}M⊨ϕiff{a mathematical formula}∀t∈Rd(M):(f(ϕ,0)(t)=1), where{a mathematical formula}d=d(ϕ).
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Correctness
      </section-title>
      <paragraph>
       In the following, we show the correctness of Theorem 3. First of all, we claim that if two strategies result in the same view in a finite number of steps, then they will enforce the same goals since then. The main intuition is that every future step will involve a strategic update and both of the strategies can be updated into the same strategy. The intuition comes from the fact that in any bounded ATL formula, a temporal operator is immediately prefixed with a coalition operator. Let {a mathematical formula}EA(r,m,aA)={r′∈R|viewA(r′,m)=viewA(r,m)∧aA(r′,m)=aA} be a set of runs that 1) have the same view as that of run r up to time m and 2) take the action {a mathematical formula}aA∈ActA. Let {a mathematical formula}aAc(r,m) be the action that is taken by agents in A on cell c if their view is consistent with that of point {a mathematical formula}(r,m). We have the following lemma.
      </paragraph>
      <paragraph label="Lemma 1">
       Let{a mathematical formula}(r,m)be a point in{a mathematical formula}Iand{a mathematical formula}aAbe an action of agents in A such that{a mathematical formula}EA(r,m,aA)≠∅. Let{a mathematical formula}[c1]C≃Aand{a mathematical formula}[c2]C≃Abe two equivalence classes of an AIS{a mathematical formula}Isuch that{a mathematical formula}[c1]C≃A∩EA(r,m,aA)≠∅and{a mathematical formula}[c2]C≃A∩EA(r,m,aA)≠∅. Then for any bounded ATL formula ϕ, we have that{a mathematical formula}∀r1′∈[c1]C≃A∩EA(r,m,aA):I,(r1′,m+1)⊨ϕif and only if{a mathematical formula}∀r2′∈[c2]C≃A∩EA(r,m,aA):I,(r2′,m+1)⊨ϕ.
      </paragraph>
      <paragraph label="Proof">
       Firstly, we note that for any cell c, if {a mathematical formula}[c]C≃A∩EA(r,m,aA)≠∅ then {a mathematical formula}aAc(r,m)=aA. Therefore, we have {a mathematical formula}aAc1(r,m)=aA=aAc2(r,m).Now we show that for any two points {a mathematical formula}(r1,m) and {a mathematical formula}(r2,m), if {a mathematical formula}ase[0..m](r1)=ase[0..m](r2) then {a mathematical formula}I,(r1,m)⊨ϕ if and only if {a mathematical formula}I,(r2,m)⊨ϕ. We make an induction on the structure of ϕ. If {a mathematical formula}ϕ=p∈Prop then it is obtained by the fact that {a mathematical formula}se(r1,m)=se(r2,m).If {a mathematical formula}ϕ=ϕ1∧ϕ2 then by {a mathematical formula}I,(r1,m)⊨ϕ, we have {a mathematical formula}I,(r1,m)⊨ϕ1 and {a mathematical formula}I,(r1,m)⊨ϕ2, which by inductive hypothesis, are equivalent to {a mathematical formula}I,(r2,m)⊨ϕ1 and {a mathematical formula}I,(r2,m)⊨ϕ2. The latter is {a mathematical formula}I,(r2,m)⊨ϕ.If {a mathematical formula}ϕ=¬ϕ′ then {a mathematical formula}I,(r1,m)⊨ϕ if and only if not {a mathematical formula}I,(r1,m)⊨ϕ′ if and only if not {a mathematical formula}I,(r2,m)⊨ϕ′ if and only if {a mathematical formula}I,(r2,m)⊨ϕ.If {a mathematical formula}ϕ=DAϕ′ then because the agents' knowledge depends only on the past behaviour, it is obtained from {a mathematical formula}ase[0..m](r1)=ase[0..m](r2).If {a mathematical formula}ϕ=《A》Xϕ′ then by {a mathematical formula}I,(r1,m)⊨ϕ, there exists an equivalence class {a mathematical formula}[c]C≃A∈[≃A]C of agents A such that there exist {a mathematical formula}r′∈[c]C≃A and {a mathematical formula}m′∈N such that {a mathematical formula}(r′,m′)∈KA(r,m) and for all {a mathematical formula}r′∈[c]C≃A and {a mathematical formula}m′∈N, if {a mathematical formula}(r′,m′)∈KA(r,m) then {a mathematical formula}I,(r′,m′+1)⊨ϕ. Note that the existence of such an equivalence class also means that {a mathematical formula}I,(r2,m)⊨ϕ.The cases of {a mathematical formula}ϕ=《A》ϕ1U≤kϕ2 and {a mathematical formula}ϕ=《A》ϕ1R≤kϕ2 can be obtained by their recursive definitions over operator {a mathematical formula}《A》X.Now let {a mathematical formula}FA(r,m,c)={ase[0..m](r′)|r′∈[c]C≃A∩EA(r,m,aAc(r,m))}. We proceed to show that {a mathematical formula}FA(r,m,c1)=FA(r,m,c2). We make an induction on m. For the base case, {a mathematical formula}FA(r,0,c1)=FA(r,0,c2)=I. Assume that {a mathematical formula}FA(r,k,c1)=FA(r,k,c2) for {a mathematical formula}0≤k≤m. Note that {a mathematical formula}FA(r,k+1,c1)={ρ(aAc1(r,k)aA¯)s′|ρ∈FA(r,k,c1),aA¯∈ActAgt∖A,s′∈T(s(ρ,k),aAc1(r,k)aA¯)}, which by {a mathematical formula}aAc1(r,k)=aAc2(r,k) and {a mathematical formula}FA(r,k,c1)=FA(r,k,c2), is equivalent to {a mathematical formula}{ρ(aAc2(r,k)aA¯)s′|ρ∈FA(r,k,c2),aA¯∈ActAgt∖A,s′∈T(s(ρ,k),aAc2(r,k)aA¯)}. Therefore, we have {a mathematical formula}FA(r,k+1,c1)=FA(r,k+1,c2).Finally, assume that {a mathematical formula}∀r1′∈[c1]C≃A∩EA(r,m,aA):I,(r1′,m+1)⊨ϕ but not {a mathematical formula}∀r2′∈[c2]C≃A∩EA(r,m,aA):I,(r2′,m+1)⊨ϕ, then there exists a run {a mathematical formula}r2′ in {a mathematical formula}[c2]C≃A∩EA(r,m,aA) such that {a mathematical formula}I,(r2′,m+1)⊨¬ϕ. Then by {a mathematical formula}r2′∈[c2]C≃A∩EA(r,m,aA) and {a mathematical formula}FA(r,m,c1)=FA(r,m,c2), there must exist in cell {a mathematical formula}c1 another run {a mathematical formula}r1′ such that {a mathematical formula}r1′∈[c1]C≃A∩EA(r1,m) and {a mathematical formula}ase[0..m](r1′)=ase[0..m](r2′). Therefore, we have {a mathematical formula}I,(r1′,m+1)⊨¬ϕ, which contradicts with {a mathematical formula}∀r1′∈[c1]C≃A∩EA(r,m,aA):I,(r1′,m+1)⊨ϕ.  □
      </paragraph>
      <paragraph label="Proof">
       Let M be any finite PO-CGS, and{a mathematical formula}I=(R,C,{≃i}i∈Agt,π)be an interpreted system constructed from M and synchronous perfect recall. For any formula φ of bounded ATL and any point{a mathematical formula}(r,m)∈R×N, we have that{a mathematical formula}I,(r,m)⊨φiff{a mathematical formula}f(φ,m)(ase[0..d](r))=True.We prove it by induction on the structure of the formula φ.
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}I,(r,m)⊨p is equivalent to {a mathematical formula}p∈π(r,m)=π(re(m)) (by Definition 1). By {a mathematical formula}m≤d, we have {a mathematical formula}re(m)=ase[0..d](r)(m). Then by the algorithm, we have {a mathematical formula}p∈π(ase[0..d](r)(m))=f(p,m)(ase[0..d](r)).
       </list-item>
       <list-item label="2.">
        {a mathematical formula}I,(r,m)⊨¬φ′ is equivalent to {a mathematical formula}¬(I,(r,m)⊨φ′), which by inductive hypothesis, is equivalent to {a mathematical formula}¬f(φ′,m)(ase[0..d](r)). Therefore, we have {a mathematical formula}f(φ,m)(ase[0..d](r)) by the algorithm.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}I,(r,m)⊨φ1∧φ2 is equivalent to {a mathematical formula}(I,(r,m)⊨φ1)∧(I,(r,m)⊨φ2), which by inductive hypothesis, is equivalent to {a mathematical formula}f(φ1,m)(ase[0..d](r))∧f(φ2,m)(ase[0..d](r)). Therefore, we have {a mathematical formula}f(φ,m)(ase[0..d](r)) by the algorithm.
       </list-item>
       <list-item label="4.">
        {a mathematical formula}I,(r,m)⊨《A》Xφ′ is equivalent to {a mathematical formula}∃[c]C≃A∈[≃A]C:(∃r′∈[c]C≃A:((r′,m)∈KA(r,m)))∧(∀r′∈[c]C≃A:(r′,m)∈KA(r,m)⇒I,(r′,m+1)⊨φ′) (by Definition 1). Let {a mathematical formula}aA be the action taken by the agents A in cell {a mathematical formula}[c]C≃A for their view that is consistent with point {a mathematical formula}(r,m). Then the latter is equivalent to {a mathematical formula}∃[c]C≃A∈[≃A]C:∃aA∈ActA:(EA(r,m,aA)∩[c]C≃A≠∅)∧(∀r′∈EA(r,m,aA)∩[c]C≃A:I,(r′,m+1)⊨φ′), which by Lemma 1, is equivalent to {a mathematical formula}∃aA∈ActA:(∃[c]C≃A∈[≃A]C:EA(r,m,aA)∩[c]C≃A≠∅)∧(∀r′∈EA(r,m,aA):I,(r′,m+1)⊨φ′). Finally, because {a mathematical formula}aA is defined in the cell {a mathematical formula}[c]C≃A∈[≃A]C, we have that {a mathematical formula}∃aA∈ActA:(EA(r,m,aA)≠∅)∧(∀r′∈EA(r,m,aA):I,(r′,m+1)⊨φ′). Then by inductive hypothesis and the algorithm, we have {a mathematical formula}f(《A》Xφ′,m)(t)=1.
       </list-item>
       <list-item label="5.">
        The cases of {a mathematical formula}I,(r,m)⊨《A》φ1Uφ2 and {a mathematical formula}I,(r,m)⊨《A》φ1Rφ2 is straightforward by the unfolding rules.
       </list-item>
       <list-item label="6.">
        {a mathematical formula}I,(r,m)⊨DAφ′ is equivalent to {a mathematical formula}∀r∈R:(r′,m)∈KA(r,m)⇒I,(r′,m)⊨φ′. By the definition, {a mathematical formula}(r′,m)∈KA(r,m) if and only if {a mathematical formula}(∀0≤j≤m:OA(se(r,j))=OA(se(r′,j)))∧(∀1≤j≤m:aA(r,j)=aA(r′,j)), which is equivalent to {a mathematical formula}viewequA(ase[0..d](r),ase[0..d](r′),m) for {a mathematical formula}m≤d. Then by the fact that {a mathematical formula}Rd(M) contains all prefixes up to time d for runs in {a mathematical formula}R, we have that {a mathematical formula}I,(r,m)⊨DAφ′ is equivalent to {a mathematical formula}∀t′∈Rd(M):viewequA(t,t′,m)⇒f(φ′,m)(t′). By the algorithm, the later is {a mathematical formula}f(φ,m)(ase[0..d](r)).
       </list-item>
      </list>
      <paragraph label="Proof of Theorem 3">
       Let {a mathematical formula}I=(R,C,{≃i}i∈Agt,π) be the interpreted system constructed from M and synchronous perfect recall. By the definition, {a mathematical formula}M⊨ϕ is equivalent to {a mathematical formula}∀r∈R:(I,(r,0)⊨ϕ), which by Lemma 2, is equivalent to {a mathematical formula}∀r∈R:(f(ϕ,0)(ase[0..d](r))=True). The latter is equivalent to {a mathematical formula}∀t∈Rd(M):(f(ϕ,0)(t)=True) by the definition of {a mathematical formula}Rd(M).  □
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      An efficient BDD-based algorithm for a useful fragment
     </section-title>
     <paragraph>
      The algorithm in the last section can be applied to solve any model checking problem whose specification formula is a bounded ATL logic formula. It is, however, not efficient enough to handle practical problems. In this section, we present another BDD-based algorithm which is much more efficient and works with an important fragment of bounded ATL logic. The fragment can be used to describe the existence of a fixed length strategy to reach some goal.
     </paragraph>
     <paragraph>
      Formally, the algorithm deals with formulas of the form {a mathematical formula}(《A》X)dϕ, where d is the length of a strategy and ϕ is an expression with only boolean operators and knowledge operator, i.e., no strategy operator and temporal operators are allowed. Formulas like {a mathematical formula}《A》X《B》Xϕ for {a mathematical formula}A≠B, which is a valid bounded ATL formula, is not in this fragment. All formulas considered in the examples of this paper are in the form of {a mathematical formula}(《A》X)dϕ or {a mathematical formula}《A》TrueU≤dϕ. The former can be handled directly by the algorithm. For the latter, it can be handled by the algorithm after a simple transformation as follows.{a mathematical formula}
     </paragraph>
     <paragraph>
      First of all, given a set T of states, the evaluation of ϕ on a state {a mathematical formula}s∈T is defined recursively as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}T,s⊨p for {a mathematical formula}p∈Prop if {a mathematical formula}p∈π(s),
      </list-item>
      <list-item label="2.">
       {a mathematical formula}T,s⊨ϕ1∧ϕ2 if {a mathematical formula}T,s⊨ϕ1 and {a mathematical formula}s⊨ϕ2,
      </list-item>
      <list-item label="3.">
       {a mathematical formula}T,s⊨¬ϕ if not {a mathematical formula}T,s⊨ϕ,
      </list-item>
      <list-item label="4.">
       {a mathematical formula}T,s⊨DAϕ if {a mathematical formula}∀t∈T:T,t⊨ϕ.
      </list-item>
     </list>
     <paragraph>
      Note that, for distributed knowledge formulas, the above evaluation holds if and only if the set T is a set of states which agents A cannot distinguish. Our algorithm will guarantee this when evaluating formula ϕ.
     </paragraph>
     <paragraph>
      The components of the algorithm will implicitly use {a mathematical formula}sk,ok for {a mathematical formula}0≤k≤d and {a mathematical formula}ak for {a mathematical formula}1≤k≤d as parameters, which represent state and agents A's observation of time k, and agents A's action to reach states at time k, respectively. Let {a mathematical formula}B=Agt∪{e}∖A be the opponents of agents in A, and we write {a mathematical formula}aB for its action. The pair {a mathematical formula}(ak,aB) is used to denote a global action. Let {a mathematical formula}R(o0…akok) be the set of runs on which agents A's view at time k is {a mathematical formula}o0…akok. That is,{a mathematical formula} Based on this, we let {a mathematical formula}S(o0…akok)≡{se(r,k)|r∈R(o0…akok)} be the set of environment states at time k on the runs {a mathematical formula}R(o0…akok). Also, we use {a mathematical formula}L(o0…akok,ak+1) to express that action {a mathematical formula}ak+1 is agents A's legal action on the view {a mathematical formula}o0…akok, i.e.,{a mathematical formula} The set of possible states after the view {a mathematical formula}o0…akok and action {a mathematical formula}ak+1 is{a mathematical formula} Moreover, we define boolean expressions {a mathematical formula}F(o0…akok,ak+1) as follows.
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}F(o0…akok,ak+1)=∀ok∃ak+1(L(o0…akok,ak+1)∧F(o0…ak+1ok+1,ak+2)), for {a mathematical formula}0≤k≤d−2, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}F(o0…ad−1od−1,ad)=∀s:(s∈S(o0…ad−1od−1,ad)⇒S(o0…ad−1od−1,ad),s⊨ϕ)
      </list-item>
     </list>
     <paragraph label="Proof">
      The following theorem characterises the model checking problem with expression {a mathematical formula}F(o0,a1), which is parameterised over the bound d of bounded ATL formula {a mathematical formula}(《A》X)dϕ. Given a PO-CGS M and a propositional formula ϕ over Prop,{a mathematical formula}M⊨(《A》X)dϕif and only if{a mathematical formula}F(o0,a1)=True.For brevity, we write {a mathematical formula}consist(r,k) for the expression{a mathematical formula} which says that the run r is consistent with the view {a mathematical formula}o0…ak−1ok−1 and action {a mathematical formula}ak. First of all, we have following equations.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} We let {a mathematical formula}∀r∈R:consist(r,k)⇒I,(r,k)⊨(《A》X)d−kϕ be {a mathematical formula}F(o0…ok,ak+1) for {a mathematical formula}1≤k≤d−1. For the cases of {a mathematical formula}1≤k≤d−2, it can be computed inductively as follows.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} In the following, we show that {a mathematical formula}∀r∈R:consist(r,d)⇒I,(r,d)⊨ϕ if and only if {a mathematical formula}∀ad+1∀s:(s∈S(o0…od−1,ad)⇒S(o0…od−1,ad),s⊨ϕ). Because the formula can only contain boolean operators and knowledge operators, we can show this by having {a mathematical formula}S(o0…ok−1,ak)={se(r,k)|r∈R,consist(r,k)} for all {a mathematical formula}1≤k≤d. We have that{a mathematical formula}  □
     </paragraph>
     <paragraph label="Lemma 3">
      We still need to give an approach to compute the components {a mathematical formula}L(o0…akok,ak+1) and {a mathematical formula}S(o0…akok,ak+1). The component {a mathematical formula}L(o0…akok,ak+1) can be obtained by having that{a mathematical formula} Therefore, it can be computed if we have {a mathematical formula}S(o0…akok). By its definition, the component {a mathematical formula}S(o0…akok,ak+1) can also be obtained if we have {a mathematical formula}S(o0…akok). The computation of{a mathematical formula}S(o0…akok)can be done by the following recursive rules.
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}S(o0)={s∈S|s∈I∧OA(s)=o0}, and
      </list-item>
      <list-item label="2.">
       {a mathematical formula}S(o0…akok)={s∈S|∃t:t∈S(o0…ak−1ok−1)∧∃aB:(t,(ak,aB),s)∈T∧OA(s)=ok}for{a mathematical formula}1≤k≤d.
      </list-item>
     </list>
     <paragraph label="Proof">
      For the base case of {a mathematical formula}S(o0), we have that {a mathematical formula}S(o0)={se(r,0)|r∈R(o0)}={se(r,0)|r∈R,OA(se(r,0))=o0}={s∈S|s∈I∧OA(s)=o0}. For the inductive cases, we have that {a mathematical formula}S(o0…akok)={se(r,k)|r∈R(o0…akok)}={se(r,k)|r∈R(oo…ak−1ok−1),aA(r,k)=ak,OA(se(r,k))=ok}={s∈S|t∈S(o0…ak−1ok−1),OA(s)=ok,∃aB:(t,(ak,aB),s)∈T}. □
     </paragraph>
     <paragraph>
      Before proceeding to the application of the two algorithms on examples, we make an analysis on the potential performance discrepancy between the algorithms, when working on the same bounded ATL formula. Both algorithms reduce the model checking problem to the satisfiability of quantified boolean formulas, which are represented as BDDs. The performance of BDDs is subject to the number of boolean variables and time-consuming operations e.g., universal and existential quantifications. In general, a BDD-based algorithm using less number of boolean variables will outperform the one needs more boolean variables, and a BDD-based algorithm using less number of universal and existential quantifications will outperform the one needs more quantifications.
     </paragraph>
     <paragraph>
      Let m be the number of boolean variables to represent a state and q be the number of boolean variables to represent a joint action. Note that, for a formula {a mathematical formula}ϕ=(《A》X)dφ, there is {a mathematical formula}d=d(ϕ). In the first algorithm, given a bounded ATL formula ϕ to be checked, for each time step, a run fragment from {a mathematical formula}Rd(ϕ)(M) is quantified. Each run fragment takes {a mathematical formula}(d(ϕ)+1)⁎m+d(ϕ)⁎q boolean variables. The algorithm runs {a mathematical formula}d(ϕ) steps. Therefore, the total number of boolean variables used during the construction is {a mathematical formula}d(ϕ)⁎((d(ϕ)+1)⁎m+d(ϕ)⁎q), or approximately {a mathematical formula}d(ϕ)2⁎(m+q). In the second algorithm, given a formula ϕ, for each time step, it computes either {a mathematical formula}L(o0…akok,ak+1) or {a mathematical formula}S(o0…ad−1od−1,ad), which take {a mathematical formula}(k+1)⁎m+k⁎q boolean variables for {a mathematical formula}0≤k≤d−1. In total, it uses {a mathematical formula}1/2⁎d⁎((d+1)⁎m+(d−1)⁎q) boolean variables, or approximately {a mathematical formula}1/2⁎d2⁎(m+q). Therefore, comparing with the first algorithm, the second algorithm uses about one half of the number of the boolean variables. Please note that, the algorithms do not construct of a monolithic BDD of this number of variables. Variables are gradually quantified away during the construction.
     </paragraph>
     <paragraph>
      For the quantifications, the first algorithm has a deepest nesting of the form {a mathematical formula}∃aA∀t′∈Rd(M)…∃aA∀t′∈Rd(M), while the second algorithm has a deepest nesting of the form {a mathematical formula}∀o0∃a1…∀od−1∃ad. Although they have the same nesting depth, their numbers of quantified variables are largely different: {a mathematical formula}d(ϕ)⁎((d(ϕ)+1)⁎m+d(ϕ)⁎q) variables are quantified in the first algorithm, while only {a mathematical formula}(d+1)⁎m+d⁎q variables are quantified in the second algorithm.
     </paragraph>
    </section>
    <section label="10">
     <section-title>
      Applications
     </section-title>
     <paragraph>
      Both algorithms have been implemented in the model checker MCK [14]. As our experiments, they are used to verify several applications. All experimental data are collected on an Apple iMac machine with core i3 CPU. Each computation is allocated up to 500M memory. Running times are measured in seconds. We write alg1 for the general algorithm of Section 8 and alg2 for the algorithm of Section 9.
     </paragraph>
     <paragraph>
      Before proceeding to the examples, we need to handle the assumption that in a PO-CGS M, for all states {a mathematical formula}s1,s2∈S and {a mathematical formula}i∈Agt, {a mathematical formula}Oi(s1)=Oi(s2) implies {a mathematical formula}Ni(s1)=Ni(s2). In our modelling language, a system state s is an assignment to a set of state variables, and agent i's observation is defined to be a subset of the set of state variables. Therefore, the above assumption does not hold generally. We therefore apply a pre-processing procedure on the modelled system, by adding into state variables a set {a mathematical formula}{oai|ai∈Acti,i∈Agt} of extra boolean variables, letting variable {a mathematical formula}oai represent the observability of local action {a mathematical formula}ai at the current state, and allowing agent i to observe variables {a mathematical formula}{oai|ai∈Acti}. The observability of action {a mathematical formula}ai at state s is defined to be {a mathematical formula}∃t∈S:(s,a,t)∈T for {a mathematical formula}ai being agent i's local action in the global action a. Let {a mathematical formula}s′ be the updated system state of s. We have that {a mathematical formula}Oi(s1′)=Oi(s2′) if {a mathematical formula}Oi(s1)=Oi(s2) and {a mathematical formula}∀v∈{oa|a∈Acti}:s1′(v)=s2′(v). Therefore, the assumption holds on the updated system, i.e., for all {a mathematical formula}s1′,s2′ and {a mathematical formula}i∈Agt, {a mathematical formula}Oi(s1′)=Oi(s2′) implies {a mathematical formula}Ni(s1′)=Ni(s2′).
     </paragraph>
     <section label="10.1">
      <section-title>
       Iterated Prisoner's Dilemma
      </section-title>
      <paragraph>
       First of all, the model checking results justify our analysis for the three specifications on IPD(3). To show the capability of the algorithms in dealing with IPD, we scale up the number of iterations k. As the three specifications need similar running times for a given k with the algorithm alg1, we only report the results for the specification formula (2) in Table 2. In our modelling, the number of boolean state variables is 28 and the number of action variables is 4. Therefore, the number of variables to construct the transition relation, which is essential to BDD-based model checking algorithms [1], is {a mathematical formula}28+4+28=60.
      </paragraph>
     </section>
     <section label="10.2">
      <section-title>
       Kriegspiel Tic-Tac-Toe
      </section-title>
      <paragraph>
       The game of Kriegspiel Tic-Tac-Toe [30] is played on an {a mathematical formula}n×n board, as shown in Fig. 3. Two agents × and ◯ take turns, by marking X and O on the squares of the board, respectively. The first agent to occupy a horizontal, vertical, or diagonal row wins the game. Agents cannot see where their opponent plays. If they try to mark a square that has been marked by their opponent, they are informed of this fact but not allowed to play again.
      </paragraph>
      <paragraph>
       The game state is a tuple {a mathematical formula}(xb,ob,x,o,t), where xb and ob are arrays of length {a mathematical formula}n×n, recording the marking status of agents × and ◯ respectively, x and o are boolean variables, denoting whether in the current round agents × and ◯ have successfully marked the squares they are requesting for, and {a mathematical formula}t∈{×,◯} is a variable, denoting which agent is active at the current round. Each of the agents can only observe part of a system state, i.e., {a mathematical formula}O×(xb,ob,x,o,t)=(x,t) and {a mathematical formula}O◯(xb,ob,x,o,t)=(o,t). Here we make a remark that, agents do not need to explicitly keep tracking the xb or ob arrays of variables. The status of the board can be obtained from a sequence of games states and local actions observed from the past rounds. Let {a mathematical formula}mx,y be the action of marking the square {a mathematical formula}(x,y). An action of an agent is to mark a square in the board, that is, {a mathematical formula}a×,a◯∈{mx,y|(x,y)∈board}. A global action is of the form {a mathematical formula}(mx,y,nil) or {a mathematical formula}(nil,mx,y), depending on which agent is taking a turn, where nil denotes an empty action.
      </paragraph>
      <paragraph>
       In this game, an interesting property is the fairness of the game, i.e., if one of the agents has a winning strategy in a bounded number of rounds, e.g.,{a mathematical formula} where the atomic proposition xwin expresses that the agent × wins the game. To compare the two algorithms, we instead check the formula{a mathematical formula} which says that agent × has a strategy to win at time k. The checking of formula in (4) can be done by repeatedly checking formula (5) on increasing number k. The experiments are conducted by scaling up both the size of board and the number of rounds. Table 3 gives the running time results.{sup:1} In our modelling, the number of boolean state variables is {a mathematical formula}2(n2+n+2) and the number of action variables is {a mathematical formula}2(n+1), for the board of {a mathematical formula}n×n size. Therefore, for {a mathematical formula}6×6 board, the encoding of transition relation into BDD uses {a mathematical formula}88+14+88=190 boolean variables.
      </paragraph>
     </section>
     <section label="10.3">
      <section-title>
       Patrolling game
      </section-title>
      <paragraph>
       Growing interests has been accumulated on the study of patrolling problem from the game theoretical view [33]. This line of research has resulted in successful applications in, e.g., the development of security scheduler for the Los Angeles International Airport [34]. Most of the works focus on developing a designated algorithm to synthesise a strategy. We here propose a way to investigate a patrolling game from the view of model checking, by following the notations of [35], [16].
      </paragraph>
      <paragraph>
       There are two agents, a guard G and an attacker A. The guard G patrols the area by following a specific plan. The attacker A can succeed if holding an attack at a position for a continuous z rounds without being captured by G. Moreover, an attack, once started, cannot be terminated and thus will always result in a successful attack or a capture.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}G=(V,E) be a discrete graph consisting of a set V of positions and a set E of edges connecting positions. A game state is a tuple {a mathematical formula}(posG,posA,counter,capture), where {a mathematical formula}posG is current position of G, {a mathematical formula}posA is current position of A, counter shows the elapsed time of an attack, and capture denotes whether A has been captured by G. The observation functions are defined as{a mathematical formula} and{a mathematical formula} which means that the attacker A can observe its neighbouring nodes.
      </paragraph>
      <paragraph>
       At each time, the available actions for an agent is to stay at its current position or move to an adjacent position if they are connected.
      </paragraph>
      <paragraph>
       In such a game, an interesting specification is{a mathematical formula} which expresses that the attacker A has a strategy to hold a successful attack, or its negation which says that the guard G can guarantee the security of the area.
      </paragraph>
      <paragraph>
       In our experiments, we assume an area as described in Fig. 4. The area consists of 6 positions {a mathematical formula}{1..6} and an outside position 0. The attacker starts in 0 and the guard can start at any position except for 0. The guard plays by following a specific strategy: {a mathematical formula}1→2→3→4→5→6→3→2→1.
      </paragraph>
      <paragraph>
       Assume that the attack time is {a mathematical formula}z≤4. A strategy for the attacker is that, each time it sees the guard at position 2, it moves to position 2 at the next time. If the guard appears at position 1, then it moves back to position 0. Otherwise, it starts attacking position 2. Because the guard can only return to position 2 after 5 rounds, the attacker can make a successful attack.
      </paragraph>
      <paragraph>
       If {a mathematical formula}5≤z&lt;7, the attacker can still make a successful attack by following the guard to the circle area, i.e., positions in {a mathematical formula}{4,5,6}, and then start attacking. The experimental results are shown in Table 4 by scaling up the number k of rounds. The setting of z does not affect the running times. It needs {a mathematical formula}10+z steps to have a successful strategy for the attacker. In our modelling, the number of boolean state variables is 24 and the number of action variables is 5. Therefore, the number of variables in constructing the transition relation is {a mathematical formula}24+5+24=53.
      </paragraph>
      <paragraph>
       The attack will absolutely fail if {a mathematical formula}z≥7.
      </paragraph>
     </section>
    </section>
    <section label="11">
     <section-title>
      Related works
     </section-title>
     <paragraph>
      ATL has been intensively studied in recent years. For complete information systems, the complexity of verifying ATL has been solved, for both perfect recall strategies [4], [36] and memoryless strategies [4], [37]. Mocha [11] is a model checker that can check ATL formulas on complete information systems. Here we focus on the incomplete information systems and the ATL variants based on them.
     </paragraph>
     <paragraph>
      The consideration of ATL under partial observation was first proposed in [17], where the formula {a mathematical formula}《A》ϕ is interpreted over agents A's arbitrary deterministic group strategies, that is, an agent selects its action as if it has full information of the state. It is then argued, e.g., in [22], [23], that partial observations are intended precisely to represent that agents do not have full information of the state. It is then converged to an interpretation where agents in A can only follow uniform deterministic group strategies, which means that an agent has to select the same action on those states with the same observation. The consideration of uniform strategies makes the complexity of model checking intractable [23].
     </paragraph>
     <paragraph>
      The above interpretations assume that agents do not have memory, that is, an agent decides its strategy based on current observation (there is a disagreement over whether to based on its own current observation or based on the current observation of the group). In some situations, e.g., game playing or security protocols, we need to assume that an agent has infinite memory to remember what it has seen and what it has done. That is, an agent decides its strategy based on its perfect recall view. The complexities for ATL variants based on perfect recall strategies are very high [5].
     </paragraph>
     <paragraph>
      MCMAS [12] can verify formulas with memoryless strategies on incomplete information system, with its algorithm reported in [13]. The algorithm proceeds by first abstracting all possible strategies and then verify them one by one by symbolic model checker. It is extended with the capability of handling fairness constraint in [38]. In MCK, we implement a more efficient algorithm [39] for an epistemic strategy logic [40], [41] with memoryless strategies. The logic is more expressive than ATL and therefore the algorithm is also applicable on ATL formulas. The novelty of the algorithm is a symbolic representation of the strategy, which enables the model checking to be fully-symbolic. It is an extension of the algorithm we present in [42] for synthesising knowledge-based programs. We also mention a recent development of MCMAS on model checking a strategy logic with knowledge [43].
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>