<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Iterative voting and acyclic games.
   </title>
   <abstract>
    Multi-agent decision problems, in which independent agents have to agree on a joint plan of action or allocation of resources, are central to artificial intelligence. In such situations, agents' individual preferences over available alternatives may vary, and may try to reconcile these differences by voting. We consider scenarios where voters cannot coordinate their actions, but are allowed to change their vote after observing the current outcome, as is often the case both in offline committees and in online voting. Specifically, we are interested in identifying conditions under which such iterative voting processes are guaranteed to converge to a Nash equilibrium state—that is, under which this process is acyclic. We classify convergence results based on the underlying assumptions about the agent scheduler (the order in which the agents take their actions) and the action scheduler (the actions available to the agents at each step). By so doing, we position iterative voting models within the general framework of acyclic games and game forms. In more detail, our main technical results provide a complete picture of conditions for acyclicity in several variations of Plurality voting. In particular, we show that (a) under the traditional lexicographic tie-breaking, the game converges from any state and for any order of agents, under a weak restriction on voters' actions; and that (b) Plurality with randomized tie-breaking is not guaranteed to converge under arbitrary agent schedulers, but there is always some path of better replies from any initial state of the game to a Nash equilibrium. We thus show a first separation between order-free acyclicity and weak acyclicity of game forms, thereby settling an open question from [7]. In addition, we refute another conjecture of Kukushkin regarding strongly acyclic voting rules, by proving the existence of strongly acyclic separable game forms.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Voting mechanisms are a popular tool for preference aggregation and collective decision making in multi-agent systems. One major concern when applying such mechanisms is that voters may misreport their real preferences in order to affect the outcome in their favor. Indeed, most voting rules are known to be susceptible to such strategic behavior [3], [4]. It is therefore natural to employ game-theoretic tools in order to model voting behavior and assess the outcome of a voting process. Specifically, in this work we are interested in identifying conditions under which the process will converge to an equilibrium state where no voter has an incentive to change his vote—that is, conditions such that the game induced by the voting process is acyclic.
     </paragraph>
     <paragraph>
      Researchers in economics and game theory since Cournot [5] have been developing a formal framework to study questions about acyclicity (see, for example, [6], [7], [8]). Acyclic games have several attractive features: not only do they possess an equilibrium in pure strategies, they also guarantee that local improvement dynamics will always lead to one. These properties are highly desirable both from an economic and a computational perspective, as they imply that a system has a stable state which is reachable in a decentralized way, often with little information and communication.
     </paragraph>
     <paragraph>
      The analysis of acyclicity of voting games is of particular interest to AI as it tackles the fundamental problem of multi-agent decision making, where autonomous agents (that may be distant, self-interested and/or unknown to one another) have to choose a joint plan of action or allocate resources or goods. Agents may vote strategically based on their current information, and keep updating their vote as the current state changes, and thus it is the local dynamics (in addition to preferences) that determines the outcome.
     </paragraph>
     <paragraph>
      Now, there are several degrees of acyclicity, depending on the initial state of the process, the type of improvement steps that agents may take and the order in which they may act (see the classification scheme of Kukushkin [7], [9], [10]). In particular, a better reply denotes any change of strategy that strictly improves the utility of the agent, and a game that admits no cycles of better replies whatsoever is called strongly acyclic. In contrast, weak acyclicity means that while cycles may generally occur, there is at least one path of better replies that leads to an equilibrium from any initial state. Order-free acyclicity is a middle ground,{sup:1} requiring convergence for any order of agents (agent scheduler), but allowing the action scheduler to restrict the way agents choose among several available replies (e.g., only allowing best replies that maximize the agent's utility among all better replies). In this work, we apply this classification to games that arise in the context of voting.
     </paragraph>
     <paragraph>
      Specifically, we consider the model of iterative voting. In this model, voters have fixed private preferences and start from some announcement (e.g., sincerely report their preferences or submit random votes). Votes are then aggregated via some predefined rule (e.g., Plurality, Veto or Borda), and agents can change their votes after observing the current announcement and the outcome, but not other voters' true preferences. The game proceeds in turns, where a single voter changes his vote at each turn, until no voter has objections and the final outcome is announced. Note that voters remain ignorant regarding the true preferences of the other voters. This process is similar to online polls via Doodle or Facebook, where users can log-in at any time and change their ballot. Similarly, some offline committees (e.g., for recruitment processes or art competitions) often hold straw votes, or an informal process where a member can ask to change his vote when she sees the current outcome or receives additional information about the applicants. Another voter may react by changing his vote as well, and so on. Interestingly, even in presidential elections, in several states of the United States people can change their votes if they cast their ballots early [11].
     </paragraph>
     <paragraph>
      The formal study of iterative voting rules was initiated about seven years ago in our AAAI paper that was a preliminary version of this work [1]. Subsequent papers on iterative voting typically focused on common voting rules such as Plurality, Veto and Borda, and studied the conditions under which convergence of the iterative process to an equilibrium is guaranteed [12], [13], [14]. However, despite the fact that both fields ask similar questions, the iterative voting literature has remained largely detached from the more general literature on acyclicity in games. Bridging this gap is the main conceptual contribution of this work, and is important for two reasons. First, the analysis of conditions that entail acyclicity of games and game forms is crucial to the understanding of iterative voting scenarios and the ability to properly compare their convergence properties (e.g., convergence of any best reply dynamics is a special case of order-free acyclicity and convergence under a particular order of voters implies weak acyclicity). Second, convergence results for specific voting rules under best/better reply dynamics may shed light on more general questions regarding acyclicity of voting processes. To this end, we apply the formalism of Kukushkin [7] for strong/order-free/weak acyclicity of game forms, which allows us to re-interpret both known and new results on convergence of better and best reply dynamics in voting games, and to answer some open questions.
     </paragraph>
     <section label="1.1">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       Kukushkin [7] provided several partial characterizations for game forms with strong acyclicity. In particular, he showed that if we further strengthen the acyclicity requirement to demand an ordinal potential [6], then this is attained if and only if the game form is dictatorial—i.e., there is at most one voter that can affect the outcome. He further characterized game forms that are strongly acyclic under coalitional improvements, and provided broad classes of game forms that are “almost strongly acyclic”—i.e., order-free acyclic with only mild restrictions on voters' actions. Other partial characterizations have been provided for acyclicity in complete information extensive form games [15], [16]. The most relevant aspects of this work are explained in more detail in the following sections.
      </paragraph>
      <paragraph>
       The study of classes of games with specific utility structures that are guaranteed to be acyclic or weakly acyclic has attracted much attention, in particular regarding the existence and properties of potential functions [6], [8], [17], [18]. We discuss these below.
      </paragraph>
      <section>
       <section-title>
        Strategic voting
       </section-title>
       <paragraph>
        The notion of strategic voting has been highlighted in research on social choice as crucial to understanding the relationship between preferences of a population and the final outcome of elections (see, for example, [19], [20], [21]). In various applications, ranging from political domains to AI, the most widely used voting rule is Plurality, in which each voter has one vote and the winner is the candidate who receives the highest number of votes. While it is known that no reasonable voting rule is completely immune to strategic behavior [3], [4], Plurality has been shown to be particularly susceptible, both in theory [21], [22] and in practice [23]. This makes the analysis of any election campaign—even one where the simple Plurality rule is used—a challenging task. As voters may speculate and counter-speculate, it would be beneficial to have formal tools that help us understand (and perhaps predict) the final outcome.
       </paragraph>
       <paragraph>
        In particular, natural tools for this task include the well-studied solution concepts developed for normal form games, such as better/best replies, dominant strategies or different variants of equilibrium. Now, while voting settings are commonly presented in other forms, several natural normal form formulations have been proposed in the past [24], [25], [26], [27], [28]. These formulations are extremely simple for Plurality voting games, where voters have only few available ways to vote. Specifically, some of this previous work has been devoted to the analysis of solution concepts such as elimination of dominated strategies [24] and strong equilibria [26]. Other multi-step voting procedures that have been proposed in the literature are the iterated majority vote [29] and extensive form games, where voters vote one by one [30]. However, in contrast to iterative voting, these models are inconsistent with the better reply dynamics in the framework of normal form games, and are analyzed via different techniques. A model somewhat more similar to ours was recently studied in [31], where voters can choose between voting truthfully or manipulating under the assumption that everyone else is truthful. That is, in this model each voter has exactly two available actions, whereas in ours all valid votes are allowed.
       </paragraph>
       <paragraph>
        Convergence of better reply dynamics in iterative voting for particular voting rules has been studied extensively in the computational social choice literature. We summarize and compare these findings with our results in the concluding section, particularly in Table 3.
       </paragraph>
       <paragraph>
        An important question in the context of strategic voting, including the iterative voting model, is whether an obtained equilibrium state is good for the society according to various metrics. To this end, Branzei et al. [32] showed bounds on what they term the dynamic price of anarchy, that evaluates how far the final outcome can be from the initial truthful outcome. Other work in this line used simulations to show that iterative voting may improve the social welfare or Condorcet efficiency [33], [34], [35].
       </paragraph>
       <paragraph>
        A similar variant of iterative voting in the context of multi-issue voting was studied by [36] via simulations.
       </paragraph>
      </section>
      <section>
       <section-title>
        Biased and sophisticated voting
       </section-title>
       <paragraph>
        Some recent work on iterative voting deals with voters who are uncertain, truth-biased, lazy-biased, bounded-rational, non-myopic, or apply some other restrictions and/or heuristics that diverge from the standard notion of better reply in games [13], [33], [34], [37], [38], [39], [40], [41], [42]. The outcomes of such dynamics are not necessarily Nash equilibria, which means that some voters could still benefit from changing their votes in such states, should the limitations on their available actions be removed. In this work, we exclude the possibility of this potential instability, and deal exclusively with myopic better and best reply dynamics that (if they converge) lead to a Nash equilibrium state.{sup:2}
       </paragraph>
      </section>
     </section>
     <section label="1.2">
      <section-title>
       Contribution
      </section-title>
      <paragraph>
       On the conceptual level we introduce a model to handle dynamics of strategic behavior in voting settings and position variants of this iterative voting model within the general framework of acyclic games and game forms.
      </paragraph>
      <paragraph>
       In Section 3 we consider strong acyclicity, and settle an open question regarding the existence of acyclic non-separable game forms, by explicitly constructing one, thereby refuting a conjecture by Kukushkin [7].
      </paragraph>
      <paragraph>
       Section 4 focuses on order-free acyclicity of the Plurality rule. Our main result in this section shows that to guarantee convergence, it is necessary and sufficient that voters restrict their actions in a natural way that we term direct reply—meaning that a voter will only reassign his vote to a candidate that will become a winner as a result. Importantly, it is not sufficient to restrict the set of actions to best (but possibly indirect) replies: best reply dynamics, as we demonstrate, may contain cycles. However, best reply dynamics is guaranteed to converge from the truthful state, under either lexicographic or randomized tie-breaking.
      </paragraph>
      <paragraph>
       In Section 5, we use variations of Plurality to show a strict separation between order-free acyclicity and weak acyclicity, thereby settling another open question from [7]. In particular, we show that if we add either weights (plus some restriction on the votes) or random tie-breaking to the Plurality rule, we get a game form that is weakly acyclic, but not order-free acyclic, since the order of voters is crucial for convergence.
      </paragraph>
      <paragraph>
       We conclude in Section 6, where we also classify all known convergence results in iterative voting according to the standard taxonomy of acyclicity in games.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Model and preliminaries
     </section-title>
     <paragraph>
      We usually denote sets by uppercase letters (e.g., {a mathematical formula}A,B,…), and vectors by bold letters (e.g., {a mathematical formula}a=(a1,…,an)). In some cases the i'th entry of a is referred to as {a mathematical formula}a(i). For a set X we denote by {a mathematical formula}L(X) the set of permutations over X.
     </paragraph>
     <section label="2.1">
      <section-title>
       Voting rules and game forms
      </section-title>
      <paragraph>
       There is a set C of m alternatives (or, candidates), and a set N of n strategic agents (voters). A game form (also called a voting rule) f allows each agent {a mathematical formula}i∈N to select an action {a mathematical formula}ai from a set {a mathematical formula}Ai (we also refer to {a mathematical formula}ai as the vote of agent i). The input to f is therefore a vector {a mathematical formula}a=(a1,…,an) called an action profile (or, a voting profile). Then, f chooses a winning alternative—i.e., it is a function {a mathematical formula}f:A→C, where {a mathematical formula}A=×i∈NAi (see Fig. 1 for examples).
      </paragraph>
      <paragraph>
       A voting rule f is standard if {a mathematical formula}Ai=A for all i, and A is either {a mathematical formula}L(C) or a coarsening of {a mathematical formula}L(C).{sup:3} For example, in Plurality—one of the most prominent voting rules—we have that {a mathematical formula}A=C, and the winner is the candidate with the most votes; thus, all permutations with the same leading candidate are considered to be the same action. For a permutation {a mathematical formula}L∈L(C), we denote the first element—i.e., the leading candidate—in L by {a mathematical formula}⊤(L). Like Plurality, most common voting rules except Approval are standard.
      </paragraph>
      <paragraph>
       We allow for a broader set of “Plurality game forms” by considering weighted and fixed voters, and varying the tie-breaking method. Specifically, each of the strategic voters {a mathematical formula}i∈N has an integer weight {a mathematical formula}wi∈N, and there are also {a mathematical formula}nˆ fixed voters who do not play strategically or change their vote. The value {a mathematical formula}sˆ(c) (called the initial score) specifies the number of fixed votes for each candidate c. The vector {a mathematical formula}w∈Nn of weights and the vector {a mathematical formula}sˆ∈Nm of initial scores are part of the game form.{sup:4}
      </paragraph>
      <paragraph>
       The final score of a candidate c for a given profile {a mathematical formula}a∈An in the Plurality game form {a mathematical formula}fsˆ,w is the sum of the initial score and the total weight of strategic voters that vote for c. We denote the final score vector by {a mathematical formula}ssˆ,w,a (often just {a mathematical formula}sa or s when the other parameters are clear from the context), where {a mathematical formula}s(c)=sˆ(c)+∑i∈N:ai=cwi.
      </paragraph>
      <paragraph>
       The Plurality rule selects a candidate from {a mathematical formula}W=argmaxc∈Cssˆ,w,a(c), breaking ties according to some specified method. As our results show, acyclicity properties may strongly depend on the tie-breaking method. The two primary variations we consider are {a mathematical formula}fsˆ,wPL which breaks ties lexicographically, and {a mathematical formula}fsˆ,wPR which selects a winner from W uniformly at random. As with s, we omit the subscripts w and {a mathematical formula}sˆ when they are clear from the context.
      </paragraph>
      <paragraph>
       For illustration, consider an example in Fig. 2, demonstrating a specific weighted Plurality game form with two agents.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Incentives
      </section-title>
      <paragraph>
       Games are attained by adding either cardinal or ordinal utility to a game form. The linear order relation {a mathematical formula}Li∈L(C) reflects the preferences of agent i. That is, i prefers c over {a mathematical formula}c′ (denoted {a mathematical formula}c≻ic′) if {a mathematical formula}(c,c′)∈Li. The vector containing the preferences of all n agents is called a preference profile, and is denoted by {a mathematical formula}L=(L1,…,Ln). The game form f, coupled with a preference profile L, defines an ordinal utility normal form game {a mathematical formula}G=〈f,L〉 with n agents, where agent i prefers outcome {a mathematical formula}f(a) over outcome {a mathematical formula}f(a′) if {a mathematical formula}f(a)≻if(a′). In standard game forms, the action {a mathematical formula}ai may indicate the agent's preferences, hence their common identification with voting rules.
      </paragraph>
      <section>
       <section-title>
        Improvement steps and equilibria
       </section-title>
       <paragraph>
        Having defined a normal form game, we can now apply standard solution concepts. Let {a mathematical formula}G=〈f,L〉 be a game, and let {a mathematical formula}a=(a−i,ai) be a joint action in G.
       </paragraph>
       <paragraph>
        We denote by {a mathematical formula}a→ia′ an individual improvement step (or, better reply), if (1) {a mathematical formula}a,a′ differ only by the action of agent i; and (2) {a mathematical formula}f(a−i,ai′)≻if(a−i,ai). We sometimes omit the actions of the other voters {a mathematical formula}a−i when they are clear from the context, only writing {a mathematical formula}ai→iai′. We denote by {a mathematical formula}Ii(a)⊆Ai the set of actions {a mathematical formula}ai′ s.t. {a mathematical formula}ai→iai′ is an improvement step of agent i in a. Similarly, {a mathematical formula}I(a)=⋃i∈N⋃ai′∈Ii(a)(a−i,ai′) contains all states accessible from a by some better reply. {a mathematical formula}a→iai′ is called a best reply if i weakly prefers {a mathematical formula}f(a−i,ai′) over any candidate {a mathematical formula}f(a−i,bi) s.t. {a mathematical formula}b∈Ii(a).
       </paragraph>
       <paragraph>
        A joint action a is a (pure strategy) Nash equilibrium (NE) in G if {a mathematical formula}I(a)=∅. That is, no agent can gain by changing his vote, provided that others keep their strategies unchanged. A priori, a game may not admit any NE in pure strategies.
       </paragraph>
       <paragraph>
        Now, observe that when f is a standard voting rule the preference profile L induces a special joint action {a mathematical formula}a⁎=a⁎(L), termed the truthful state, where {a mathematical formula}ai⁎ equals (the coarsening of) {a mathematical formula}Li. For example, in Plurality {a mathematical formula}ai⁎=⊤(Li). We refer to {a mathematical formula}f(a⁎) as the truthful outcome of the game {a mathematical formula}〈f,L〉.
       </paragraph>
       <paragraph>
        The truthful state may or may not be included in the NE points of the game, as can be seen from Fig. 3, Fig. 4 that demonstrate games that are induced by adding incentives to the game form shown in Fig. 2, and indicate the truthful states and the NE points in these games.
       </paragraph>
      </section>
     </section>
     <section label="2.3">
      <section-title>
       Iterative games
      </section-title>
      <paragraph>
       We consider natural dynamics in iterative games. Assume that agents start by announcing some initial profile {a mathematical formula}a0, and then proceed as follows: at each step t a single agent i may change his vote to {a mathematical formula}ai′∈Ii(at−1), resulting in a new state (joint action) {a mathematical formula}at=(a−it−1,ai′). The process ends when no agent has objections, and the outcome is set by the last state.
      </paragraph>
      <paragraph>
       Local improvement graphs and schedulers  Any game G induces a directed graph whose vertices are all action profiles (states) {a mathematical formula}A, and edges are all local improvement steps [16], [44]. The pure Nash equilibria of G are all states with no outgoing edges.
      </paragraph>
      <paragraph>
       Since generally a state may have multiple outgoing edges ({a mathematical formula}|I(a)|&gt;1), we need to specify which one is selected in a given play. An agent scheduler is a function {a mathematical formula}ϕN that given a finite sequence of states {a mathematical formula}a0,…,at where {a mathematical formula}at is not a PNE, selects a player i such that {a mathematical formula}Ii(at)≠∅[8].{sup:5} Since we also need to decide which action is played by i, we define an action scheduler as a function {a mathematical formula}ϕA that selects a single action from {a mathematical formula}Ii(at). Thus a scheduler {a mathematical formula}ϕ=(ϕN,ϕA) is a function mapping any sequence not ending in a PNE to a better reply of some agent.
      </paragraph>
      <paragraph>
       Convergence and acyclicity  Given a game G, an initial action profile {a mathematical formula}a0 and a scheduler ϕ, we get a unique (possibly infinite) path of steps.{sup:6} Also, it is readily apparent to see that the path is finite if and only if it reaches a Nash equilibrium (which is the last state in the path). We say that the triple {a mathematical formula}〈G,a0,ϕ〉converges if the induced path is finite.
      </paragraph>
      <paragraph>
       Following [6], [17], a game G has the finite improvement property (we say that G is FIP), if {a mathematical formula}〈G,a0,ϕ〉 converges for any{a mathematical formula}a0 and scheduler ϕ. Games that are FIP are also known as (strongly) acyclic games and as generalized ordinal potential games[6]. It is quite easy to see that not all Plurality games are FIP (see examples in Section 4).
      </paragraph>
      <paragraph>
       However, there are alternative, weaker notions of acyclicity and convergence.
      </paragraph>
      <list>
       <list-item label="•">
        A game G is weakly-FIP if there is some scheduler ϕ such that {a mathematical formula}〈G,a0,ϕ〉 converges for any {a mathematical formula}a0. Such games are known as weakly acyclic[8].
       </list-item>
       <list-item label="•">
        A game G is order-free-FIP (or, order-free acyclic) if there is some action scheduler{a mathematical formula}ϕA such that {a mathematical formula}〈G,a0,(ϕN,ϕA)〉 converges for any {a mathematical formula}a0 and {a mathematical formula}ϕN[7].
       </list-item>
      </list>
      <paragraph>
       Intuitively, order-free-FIP means that there is some restriction agents can adopt such that convergence is guaranteed regardless of the order in which they play. Kukushkin identifies a particular restriction of interest, namely restriction to best reply improvements. Formally, an action scheduler {a mathematical formula}ϕA is a BR action scheduler if it always selects from {a mathematical formula}Ii(at) a best reply of i. {a mathematical formula}ϕ=〈ϕN,ϕA〉 is BR if {a mathematical formula}ϕA is BR. We get the following definitions for a game G, where FBRP stands for finite best reply property:
      </paragraph>
      <list>
       <list-item label="•">
        G is FBRP if {a mathematical formula}〈G,a0,ϕ〉 converges for any {a mathematical formula}a0 and any BR ϕ.
       </list-item>
       <list-item label="•">
        G is weakly-FBRP if there is a BR ϕ such that {a mathematical formula}〈G,a0,ϕ〉 converges for any {a mathematical formula}a0.
       </list-item>
       <list-item label="•">
        G is order-free-FBRP if there is a BR {a mathematical formula}ϕA such that {a mathematical formula}〈G,a0,(ϕN,ϕA)〉 converges for any {a mathematical formula}a0 and {a mathematical formula}ϕN.
       </list-item>
      </list>
      <paragraph>
       In this paper, we identify a different restriction, namely direct reply, that is well defined under the Plurality rule. Formally, a step {a mathematical formula}a→ia′ is a direct reply if {a mathematical formula}f(a′)=ai′, i.e., if i votes for the new winner (see labeled examples in Section 4). Another rule where a natural direct reply exists is Veto, where a voter can veto the current winner [46].{sup:7} Formally, {a mathematical formula}ϕA is a DR action scheduler if it always selects a direct reply from {a mathematical formula}Ii(at), and {a mathematical formula}ϕ=〈ϕN,ϕA〉 is DR if {a mathematical formula}ϕA is DR. We get the following definitions for a Plurality game G, where FDRP stands for finite direct reply property:
      </paragraph>
      <list>
       <list-item label="•">
        G is FDRP if {a mathematical formula}〈G,a0,ϕ〉 converges for any {a mathematical formula}a0 and any DR ϕ.
       </list-item>
       <list-item label="•">
        G is weakly-FDRP if there is a DR ϕ such that {a mathematical formula}〈G,a0,ϕ〉 converges for any {a mathematical formula}a0.
       </list-item>
       <list-item label="•">
        G is order-free-FDRP if there is a DR {a mathematical formula}ϕA such that {a mathematical formula}〈G,a0,(ϕN,ϕA)〉 converges for any {a mathematical formula}a0 and {a mathematical formula}ϕN.
       </list-item>
       <list-item label="•">
        FDBRP means that replies are both best and direct. Note that it is unique and thus cannot be further restricted.{sup:8}
       </list-item>
      </list>
      <paragraph>
       Restricted dynamics that may disallow all better replies (as in [33], [38]) do not select an action from {a mathematical formula}Ii(at) and thus do not fall under the definition of order-free-FIP (but can be considered as a separate dynamics).
      </paragraph>
      <paragraph>
       Finally, a game form f has the X property (where X is any of the above versions of finite improvement) if {a mathematical formula}〈f,L〉 is X for all preference profiles {a mathematical formula}L∈(L(C))n. Since some convergence properties entail others, we describe these entailments in Fig. 5.
      </paragraph>
      <paragraph>
       Kukushkin notes that there are no known examples of game forms that are weak-FIP, but not order-free-FIP. In this paper, we settle this question by constructing such examples explicitly (see Section 5.2).
      </paragraph>
      <paragraph>
       Convergence from the truth  We say that a game G is FIP from state a if {a mathematical formula}〈G,a,ϕ〉 converges for any ϕ. Clearly, a game is FIP iff it is FIP from a for any {a mathematical formula}a∈An. The definitions for all other notions of finite improvement are analogous.
      </paragraph>
      <paragraph>
       We are particularly interested in convergence from the truthful state {a mathematical formula}a⁎. This is because it is reasonable to assume that agents will start by voting truthfully, especially when not sure about others' preferences. Even with complete information, voters may be inclined to start truthfully, as they can always later change their vote.
      </paragraph>
      <section>
       <section-title>
        Heuristic voting
       </section-title>
       <paragraph>
        Much work on iterative voting deals with heuristics that apply different limitations on the sets of available moves at each state. The properties of strong, weak and order-free convergence can be defined in the same way as for best and better replies, where the only difference is in the way of defining the set {a mathematical formula}Ii(a) (i.e., the set of all steps that are allowed for agent i at state a by the considered heuristics). For example, the truth-bias heuristic assumes that if a voter does not have any local improvement step, she reverts to her truthful vote [1], [39]. Some heuristics only allow an agent a single action at a given state (for example, “k-pragmatist” [37], “second chance” or “best upgrade” [33]). In such cases, the only meaningful distinction is between FIP and weak-FIP.
       </paragraph>
       <paragraph>
        However, as we mentioned earlier, the outcomes of such heuristics are not necessarily Nash equilibria, meaning that voters could further improve by changing their votes, should the restrictions on their actions be removed. Therefore, in this paper we focus on better and best reply dynamics that (if they converge) reach a Nash equilibrium state. We refer the reader to [13] for a more thorough discussion of heuristics.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="3">
     <section-title>
      Properties of strongly acyclic rules
     </section-title>
     <paragraph>
      Recall that a voting rule (or game-form) is strongly acyclic if any sequence of better-replies by voters must converge to an equilibrium, regardless of voters' preferences. An ordinal potential is a function that strictly increases if and only if some agent plays a better reply [6]. A generalized ordinal potential is a function that strictly increases with every better reply, but may also increase with other steps. Clearly, a game is FIP if and only if it has a generalized potential (by a topological sort of the better reply graph) [6]. In the context of voting, even most common rules may not admit a generalized ordinal potential or an ordinal potential function; in fact, the latter only exists for dictatorships.
     </paragraph>
     <paragraph label="Theorem 3.1">
      Kukushkin [7]A game form f guarantees an ordinal potential (i.e., every derived game has an ordinal potential function) if and only if f is a dictatorship.
     </paragraph>
     <paragraph>
      Let us stress that this result does not preclude the existence of other game forms with FIP, as an ordinal potential is a stronger condition than a generalized ordinal potential. Indeed, Kukushkin provides a partial characterization of FIP game forms. For example, the Lexicographic rule where there is a linear order L over C and the winner is the first candidate according to L that is top-ranked by at least one voter, has this property.
     </paragraph>
     <paragraph>
      A game form f is called “separable” [7] if there are mappings {a mathematical formula}gi:Ai→C for {a mathematical formula}i∈N s.t. for all {a mathematical formula}a∈A, {a mathematical formula}f(a)∈{g1(a1),g2(a2),…,gn(an)}. That is, the vote of each voter is mapped to a single candidate via some function {a mathematical formula}gi, and the outcome is always one of the candidates in the range. Examples of separable rules include Plurality, the Lexicographic rule, and dictatorial rules, in all of which {a mathematical formula}gi are the identity functions.
     </paragraph>
     <paragraph>
      We now demonstrate another separable game form which (unlike the examples above) is non-standard. In the direct kingmaker voting rule [47] all voters {a mathematical formula}i∈N∖{1} specify a single candidate {a mathematical formula}a∈C, whereas voter 1 selects {a mathematical formula}i∈N∖{1} to be a “dictator of the day.” The direct kingmaker is a separable game form, since {a mathematical formula}f(a)∈{a2,…,an}. However, since {a mathematical formula}A1 is not a coarsening of {a mathematical formula}L(C), it is non-standard. We prove the following.
     </paragraph>
     <paragraph label="Proposition 3.2">
      The direct kingmaker is FIP.
     </paragraph>
     <paragraph label="Proof">
      Denote {a mathematical formula}dt=a1t as the dictator in {a mathematical formula}at. In every state {a mathematical formula}at, only agents 1 and {a mathematical formula}dt may have a better reply. Further, any better reply of {a mathematical formula}dt is selecting a more preferred candidate, i.e., {a mathematical formula}adtt+1≻dtadtt. Thus any agent except agent 1 may move at most {a mathematical formula}m−1 times. Since any cycle implies an unlimited number of steps by at least 2 agents, there can be no cycles. □
     </paragraph>
     <paragraph>
      It was conjectured by Kukushkin that separability is a necessary condition for a game form to be FIP.
     </paragraph>
     <paragraph label="Conjecture 3.3">
      Kukushkin [7]Any FIP game form is separable.
     </paragraph>
     <paragraph>
      Some weaker variations of this conjecture have been proved. In particular, the statement is true for game forms with finite coalitional improvement property [7], and for FIP game forms with {a mathematical formula}n=2 voters [48] (separable game forms are called “assignable” there). We believe that Conjecture 3.3 holds for other small values of n. Yet, next we show that for sufficiently large n, there are non-separable FIP game forms, thereby refuting the conjecture.
     </paragraph>
     <paragraph label="Theorem 3.4">
      For any{a mathematical formula}n≥7, there is a non-separable game form{a mathematical formula}fn⁎with n agents s.t.{a mathematical formula}fn⁎is FIP.
     </paragraph>
     <paragraph label="Proof">
      The proof outline is as follows. Suppose that each voter only has two possible actions. Clearly any separable game form may have at most 2n possible outcomes in C, otherwise it is impossible to find mappings {a mathematical formula}gi from actions to outcomes as required. However the number of possible action profiles is exponential in n. We will define a voting rule/game form with {a mathematical formula}2n+1 outcomes, such that almost all {a mathematical formula}2n profiles yield the same outcome z, with “special” profiles that are few (only 2n) and far between (several steps are required to get from one special profile to another). Note that for sufficiently high n, such game forms are very easy to construct, but with small n construction has to be more careful. Such game forms must be FIP, and for a very “boring” reason: any cycle must contain a several consecutive steps where the outcome remains z. Such steps cannot be a better-reply for any agent.We begin by constructing {a mathematical formula}fn⁎. The following construction works for {a mathematical formula}n≥8. For {a mathematical formula}n=7 we use a somewhat different construction, see appendix. Let {a mathematical formula}X={x1,…,xn}, {a mathematical formula}Y={y1,…,yn} and {a mathematical formula}C=X∪Y∪{z}. Let {a mathematical formula}Ai={0,1} for each voter. Every voting function {a mathematical formula}fn is a function from the n dimensional binary cube {a mathematical formula}B={0,1}n to C.The challenge is to “pack” our 2n special profiles corresponding to {a mathematical formula}X∪Y in this cube such that they are “far between.” Fortunately, coding theory deals with exactly this type of challenges, albeit for very different reasons. What we will do is write our 2n special outcomes as (short) binary vectors, then use an error-correcting code to map them back into n-bits (i.e., to profiles), but with the guarantee that they are sufficiently far from one another (a distance of 3 ‘bits’ will suffice).Denote by {a mathematical formula}k‾ the total number of bits required for an optimal single error-correcting code (Hamming code) with k data bits. For example, for {a mathematical formula}k=4 we need {a mathematical formula}4‾=7 bits. In particular, there is a mapping {a mathematical formula}q:{0,1}k→{0,1}k‾ such that the Hamming distance between any two words is at least 3 [49]. Formally, for all {a mathematical formula}w,w′∈{0,1}k, it holds that {a mathematical formula}|{j:q(w)j≠q(w′)j}|≥3.For reasons that will become apparent later, we want to have {a mathematical formula}k‾≤n−1, and {a mathematical formula}n=|X|≤2k.Set {a mathematical formula}r=⌊log2⁡(n)⌋, and {a mathematical formula}k=⌈log2⁡(n)⌉. Thus for {a mathematical formula}n∈[8,15],{a mathematical formula} for {a mathematical formula}n∈[16,31],{a mathematical formula} and for {a mathematical formula}n≥32,{a mathematical formula} So for all {a mathematical formula}n≥8 we get {a mathematical formula}k≤2r−r−1. From coding theory [49], for all {a mathematical formula}r≥2, if {a mathematical formula}k≤2r−r−1, then {a mathematical formula}k‾=2r−1 bits are sufficient to code all k-bit strings. That is, there is a valid code q from {a mathematical formula}{0,1}k to {a mathematical formula}{0,1}k‾.It thus holds that:{a mathematical formula}{a mathematical formula}Let {a mathematical formula}bin(t,k)∈{0,1}k be the k-bit binary representation of {a mathematical formula}t∈{1,2,…,n} (e.g., {a mathematical formula}bin(5,4)=0101). Since {a mathematical formula}n≤2k, all of {a mathematical formula}t≤n are represented with k bits. Using the Hamming code q, we map each outcome {a mathematical formula}xt∈X to a specific profile {a mathematical formula}at∈{0,1}n by setting the first {a mathematical formula}k‾ bits of {a mathematical formula}at to {a mathematical formula}q(bin(t,k))∈{0,1}k‾, the n'th bit to 0. Since {a mathematical formula}n≥k‾+1 we pad any remaining bits with 0's. Similarly, we map each {a mathematical formula}yt∈Y to the profile {a mathematical formula}bt=(q(bin(t,k)),0,…,0,1)∈{0,1}n.This provides us with a mapping from candidates to profiles. We now define {a mathematical formula}fn⁎ (which is a reverse mapping from profiles to candidates) as follows:
      <list>
       for all {a mathematical formula}t≤n, set {a mathematical formula}fn⁎(at)=xt;for all {a mathematical formula}t≤n, set {a mathematical formula}fn⁎(bt)=yt;for all other {a mathematical formula}2n−2n profiles, set {a mathematical formula}fn⁎(a)=z.For any two profiles
      </list>
      <paragraph>
       {a mathematical formula}a,a′, let {a mathematical formula}d(a,a′) be the number of voters that disagree in {a mathematical formula}a,a′ (the Hamming distance on the cube). By the construction above, we have that for all {a mathematical formula}t≠t′, {a mathematical formula}d(at,bt)=1, {a mathematical formula}d(at,at′)≥3, and {a mathematical formula}d(at,bt′)≥3. Let {a mathematical formula}Ct={xt,yt}.Assume towards a contradiction that there is some cycle of better replies in {a mathematical formula}fn⁎. Since each “special outcome” in {a mathematical formula}X∪Y appears in only one profile, there must be a path containing at least three distinct outcomes. This is possible in one of two ways:
      </paragraph>
      <list>
       <list-item label="1.">
        There are two distinct outcomes in the cycle from the same set {a mathematical formula}Ct={xt,yt}. In this case the cycle contains a path from {a mathematical formula}at to {a mathematical formula}btand a different path from {a mathematical formula}bt to {a mathematical formula}at. At least one of these paths must be of length 3, and contain at least two consequent profiles whose outcome is z.
       </list-item>
       <list-item label="2.">
        There are two outcomes in the cycle from distinct sets {a mathematical formula}Ct,Ct′. In this case the cycle must contain a path from {a mathematical formula}{at,bt} to {a mathematical formula}{at′,bt′}or vice versa. In either case this path must be of length 3, and contain at least two consequent profiles whose outcome is z.
       </list-item>
      </list>
      <paragraph>
       A path that contains two consequent profiles with outcome z cannot be a better reply path, since a better reply must in particular change the outcome. Hence we get a contradiction, and {a mathematical formula}fn⁎ is FIP.Finally, note that {a mathematical formula}at,bt are all distinct profiles, and {a mathematical formula}fn⁎ has {a mathematical formula}2n+1&gt;∑i≤n|Ai| possible outcomes. In contrast, for any separable rule {a mathematical formula}fn the size of the range of {a mathematical formula}fn is at most {a mathematical formula}∑i≤n|Ai|, since {a mathematical formula}fn(a)=gi(b) for some voter {a mathematical formula}i∈N and action {a mathematical formula}b∈Ai. This means that {a mathematical formula}fn⁎ is non-separable. □
      </paragraph>
     </paragraph>
     <paragraph>
      For {a mathematical formula}n≤6 such a construction is impossible, since any function with {a mathematical formula}2n+1 distinct outcomes will necessarily contain a cycle. It may still be possible to construct non-separable rules with fewer outcomes, but we believe that Conjecture 3.3 holds for all {a mathematical formula}n≤6.
     </paragraph>
     <paragraph>
      For most common voting rules, separable or not, it is easy to find examples where some cycles occur. Thus the importance of Conjecture 3.3 (or its refutation) is mainly to game theory rather than social choice. In the remainder of this paper we focus on the weaker notions of convergence as discussed in Section 1, which are more relevant to social choice.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Plurality is order-free acyclic
     </section-title>
     <paragraph>
      In this section, we analyze convergence of order-free dynamics in Plurality—that is, there is no scheduler prescribing in which order the agents should take their improvement steps. We look at sequences of better, best and direct best replies, initiated at an arbitrary or a specific (namely, truthful) profile. We consider variations of the game where the agents may have different or equal weights, and the ties are broken lexicographically or arbitrarily.
     </paragraph>
     <section label="4.1">
      <section-title>
       Lexicographic tie-breaking
      </section-title>
      <paragraph>
       We start with the case of lexicographic tie-breaking. Given some score vector s, we denote by {a mathematical formula}s¨(c)∈R the score of {a mathematical formula}c∈C that includes the lexicographic tie-breaking component. One way to formally define it is by setting {a mathematical formula}s¨(c)=s(c)+1m+1(m−L(c)), where {a mathematical formula}L(c) is the lexicographic index of candidate c. However the only important property of {a mathematical formula}s¨ is that {a mathematical formula}s¨(c)&gt;s¨(c′) if either {a mathematical formula}s(c)&gt;s(c′) or the score is equal and c has a higher priority (lower index) than {a mathematical formula}c′.
      </paragraph>
      <paragraph>
       Thus, for Plurality with lexicographic tie-breaking, a given weight vector w and a given initial score vector {a mathematical formula}sˆ, we denote the outcome by{a mathematical formula}
      </paragraph>
      <paragraph>
       As with s, we omit the scripts {a mathematical formula}w,sˆ and PL when they are clear from the context.
      </paragraph>
      <paragraph label="Lemma 4.1">
       Consider a game{a mathematical formula}〈fw,sˆPL,L〉. If there exists a better reply for a given agent i at state{a mathematical formula}at−1, then i has a direct best reply at state{a mathematical formula}at−1.
      </paragraph>
      <paragraph>
       The proof is trivial under lexicographic tie-breaking, by letting i vote for her most preferred candidate among all better replies. In this case the direct best reply is also unique.
      </paragraph>
      <paragraph>
       One implication of the lemma is that it is justified and natural to restrict our discussion to direct replies and focus on FDRP, as w.l.o.g. a voter always has a direct reply that is at least as good as any other reply.
      </paragraph>
      <paragraph>
       We next introduce some additional notation that we can use to classify all possible improvement steps under the lexicographic Plurality rule into three types. This classification will be useful in the proofs and examples throughout the section.
      </paragraph>
      <section>
       <section-title>
        Types of improvement steps in plurality
       </section-title>
       <paragraph>
        Recall that along a given path, {a mathematical formula}at∈An=Cn denotes the voting profile at time t. We next denote by {a mathematical formula}st=sat the score vector at time t; by {a mathematical formula}cwt=fPL(at) the candidate that wins at time t; and by {a mathematical formula}swt=s¨t(cwt) the highest score at time t. Note that the score of a losing candidate is always strictly lower than {a mathematical formula}swt, even if she has the same number of votes as the winner and loses only by tie-breaking.
       </paragraph>
       <paragraph>
        Suppose that agent i has an improvement step (i.e., better reply) {a mathematical formula}ait−1→iait at time t. We classify all possible steps into the following types (an example of such a step appears in parentheses):
       </paragraph>
       <list>
        <list-item label="Type 1.">
         from {a mathematical formula}ait−1≠cwt−1 to {a mathematical formula}ait=cwt; (step 1 in Ex. 4.3)
        </list-item>
        <list-item label="Type 2.">
         from {a mathematical formula}ait−1=cwt−1 to {a mathematical formula}ait=cwt; (step 1 in Ex. 4.4),
        </list-item>
        <list-item label="Type 3.">
         from {a mathematical formula}ait−1=cwt−1 to {a mathematical formula}ait≠cwt; (step 2 in Ex. 4.3)
        </list-item>
       </list>
       <paragraph>
        Note that steps of type 1 and 2 are direct, whereas type 3 steps are indirect.
       </paragraph>
       <paragraph>
        We first show our main result: when voters all have unit weight, any sequence of direct replies converges to equilibrium. Then, we show that this no longer holds if voters may have different weights.
       </paragraph>
      </section>
      <section>
       <section-title>
        Unweighted voters
       </section-title>
       <paragraph label="Theorem 4.2">
        {a mathematical formula}fsˆPLis FDRP. Moreover, any path of direct replies will converge after at most{a mathematical formula}m2n2steps. In particular, Plurality is order-free acyclic.
       </paragraph>
       <paragraph>
        This extends a weaker version of the theorem that appeared in the preliminary version of this paper [1], which only showed FDBRP. The bound on the number of direct best reply steps was improved to {a mathematical formula}O(mn) in [12, Theorem 5.4].
       </paragraph>
       <paragraph label="Proof">
        By our restriction to direct replies, there can only be moves of types 1 and 2. We first consider moves of type 1, and inductively prove two invariants that yield a bound on the total number of such moves. Next, we bound the number of moves of type 2 by a given voter between any of his moves of type 1, which completes the proof.Consider time {a mathematical formula}t−1 and denote the score of the current winner (including tie-breaking) by {a mathematical formula}s¯=swt−1. Suppose that a move {a mathematical formula}a→ib of type 1 occurs at time t: that is, {a mathematical formula}a≠cwt−1 and {a mathematical formula}b=cwt. We then have (see Fig. 6):{a mathematical formula}The strict inequality is since {a mathematical formula}cwt−1 beats a. We claim that at any later time {a mathematical formula}t′≥t the following two invariants hold:
        <list>
         Either there is a candidate {a mathematical formula}c≠a whose score is at least {a mathematical formula}s¯+1, or there are at least two candidates {a mathematical formula}c,c′≠a whose score is at least {a mathematical formula}s¯. In particular it holds in either case that {a mathematical formula}swt′≥s¯.The score of a does not increase: {a mathematical formula}s¨t′(a)≤s¨t(a).We now prove both invariants by induction on time
        </list>
        <paragraph>
         {a mathematical formula}t′. In the base case {a mathematical formula}t′=t, (I) holds since both {a mathematical formula}cwt−1 and b have a score of at least {a mathematical formula}s¯, and (II) holds trivially.Assume by induction that both invariants hold until time {a mathematical formula}t′−1, and consider step {a mathematical formula}t′ by voter j. Due to (I), we either have at least two candidates whose score is at least {a mathematical formula}s¯, or a candidate with a score of at least {a mathematical formula}s¯+1. Due to (II) and Eq. (3) we have that {a mathematical formula}s¨t′−1(a)≤s¨t(a)&lt;s¯−1.Let {a mathematical formula}d→jd′ be the step at time {a mathematical formula}t′ by voter j (that is, {a mathematical formula}d=ajt′−1,d′=ajt′). We first argue that {a mathematical formula}d′≠a: by adding the vote of j to a its score will still be strictly less than {a mathematical formula}s¯, whereas by removing a vote from any other candidate d, we still have at least one candidate c with score at least {a mathematical formula}s¯. Thus a cannot be a direct reply for any voter j, and (II) still holds after step {a mathematical formula}t′.It remains to show that (I) holds. If d is not one of the candidates in (I) with the score of at least {a mathematical formula}s¯ at time {a mathematical formula}t′−1, then their score does not decrease after step {a mathematical formula}t′, and we are done. Otherwise, we divide into the following cases:
        </paragraph>
        <list>
         <list-item label="1.">
          At {a mathematical formula}t′−1, {a mathematical formula}d=c is the (only) candidate with a score of at least {a mathematical formula}s¯+1.
         </list-item>
         <list-item label="2.">
          At {a mathematical formula}t′−1, candidates {a mathematical formula}c,c′ have scores of at least {a mathematical formula}s¯, and d is one of them (w.l.o.g. {a mathematical formula}d=c).
         </list-item>
        </list>
        <paragraph>
         In the first case, {a mathematical formula}s¨t′(d)=s¨t−1(d)−1≥s¯+1−1=s¯, whereas {a mathematical formula}s¨t′(d′)&gt;s¨t′(d)≥s¯. Thus, both {a mathematical formula}d,d′ have scores of at least {a mathematical formula}s¯ at time {a mathematical formula}t′, as required. In the second case, since only {a mathematical formula}c=d can lose votes, then if {a mathematical formula}d′≠c′,{a mathematical formula} and thus both {a mathematical formula}c′,d′ have scores of at least {a mathematical formula}s¯ at time t, as required. If {a mathematical formula}d′=c′, then{a mathematical formula} that is, {a mathematical formula}d′ has a score of at least {a mathematical formula}s¯+1, as required.Next, we demonstrate that invariants (I) and (II) supply us with a polynomial bound on the rate of convergence. Indeed, as we mentioned before, at every step of type 1, at least one candidate is ruled out permanently, and there are at most n times that a vote can be withdrawn from a given candidate. Thus in total there can be at most mn steps of type 1. Also note that, since a type 2 move by a given voter i implies that he prefers {a mathematical formula}ait to {a mathematical formula}ait−1, each voter can make at most {a mathematical formula}m−1 type 2 moves before making a move of type 1, and the total number of steps between any two type 1 steps is {a mathematical formula}(m−1)n. Hence, there are in total at most {a mathematical formula}m2n2 steps until convergence. □
        </paragraph>
       </paragraph>
       <paragraph>
        Next, we show that the restriction to direct replies is necessary to guarantee convergence, whereas a restriction to best replies is insufficient.
       </paragraph>
       <paragraph label="Proposition 4.3">
        {a mathematical formula}fPLis not FBRP.
       </paragraph>
       <paragraph label="Remark 4.1">
        In the example below and in other examples throughout the paper we use an initial score vector {a mathematical formula}sˆ. However, this is w.l.o.g. since we could replace {a mathematical formula}sˆ with additional voters that do not participate in the cycle. Initial scores are only useful to construct examples that are simpler and/or with fewer strategic agents. This holds for all negative results in the paper.{sup:9} For positive results, we have to show convergence for every initial score vector {a mathematical formula}sˆ. Clearly, any such positive result also holds for the case of {a mathematical formula}sˆ=0.
       </paragraph>
       <paragraph label="Example 4.3">
        Let {a mathematical formula}C={a,b,c} and {a mathematical formula}N={1,2}. We have a single fixed voter voting for a, thus {a mathematical formula}sˆ=(1,0,0). The preference profile is defined as {a mathematical formula}a≻1b≻1c, {a mathematical formula}c≻2b≻2a. The following cycle consists of individual improvement steps of the strategic voters (the vector denotes the votes {a mathematical formula}(a1,a2) at time t, and the winner appears in curly brackets):{a mathematical formula} Note that all steps are best replies, but the steps of agent 1 are indirect. □
       </paragraph>
       <paragraph>
        Proposition 4.3 in particular implies that {a mathematical formula}fPL is not FIP. As we show below, cycles of better replies may occur even from the truthful state.
       </paragraph>
       <paragraph label="Proposition 4.4">
        {a mathematical formula}fPLis not FIP even from the truthful state.
       </paragraph>
       <paragraph label="Example 4.4">
        Let {a mathematical formula}C={a,b,c,d}. Candidates {a mathematical formula}a,b, and c have 2 fixed voters each, thus {a mathematical formula}sˆ=(2,2,2,0). We use 3 strategic agents {a mathematical formula}N={1,2,3} with the following preferences: {a mathematical formula}d≻1a≻1b≻1c, {a mathematical formula}c≻2b≻2a≻2d and {a mathematical formula}d≻3a≻3b≻3c. Starting from the truthful state {a mathematical formula}(d,c,d) the agents can make the following two improvement steps, which are direct replies (showing only the outcome s and the winner): {a mathematical formula}(2,2,3,2){c}→1(2,3,3,1){b}→3(3,3,3,0){a}, after which agents 1 and 2 repeat the cycle shown in Example 4.3. □
       </paragraph>
       <paragraph>
        There is still the question of convergence from the truthful state, when voters are restricted to best replies that are not necessarily direct. This was shown to be positive as well.
       </paragraph>
       <paragraph label="Proposition 4.5">
        Reijngoud [50]{a mathematical formula}fPLis FBRP from the truth. Moreover, any path of best replies will converge after at most mn steps.
       </paragraph>
       <paragraph>
        The reason is that under best-response dynamics from the truthful state, only type 1 steps can occur. This fact was also shown independently by Branzei et al. [32].
       </paragraph>
      </section>
      <section>
       <section-title>
        Weighted voters
       </section-title>
       <paragraph>
        Next, we show that if the voters may have non-identical weights, then convergence to equilibrium is not guaranteed even if they start from the truthful state and use direct best replies.
       </paragraph>
       <paragraph label="Proposition 4.6">
        {a mathematical formula}fwPLis not order-free-FDRP for some w, even from the truthful state.
       </paragraph>
       <paragraph label="Example 4.6">
        Let the initial fixed score of candidates {a mathematical formula}C={a,b,c,d} be {a mathematical formula}sˆ=(0,1,2,3). The weight of each voter {a mathematical formula}i∈N={1,2,3} is i. The preference profile is as follows: {a mathematical formula}c≻1d≻1b≻1a, {a mathematical formula}b≻2c≻2a≻2d, and {a mathematical formula}a≻3b≻3c≻3d. The initial truthful profile is thus {a mathematical formula}a0=(c,b,a), which results in the score vector {a mathematical formula}s0=(3,3,3,3) where a is the winner.{a mathematical formula} Our example shows a cycle of direct replies. Note that at every step there is only one direct reply available to the agent, thus it is not possible to eliminate the cycle by further restricting the action scheduler. □
       </paragraph>
       <paragraph>
        However, if there are only two strategic weighted voters (and possibly other fixed voters), either restriction to direct replies or to a truthful initial state is sufficient to guarantee convergence.
       </paragraph>
       <paragraph label="Lemma 4.7">
        Suppose that there are{a mathematical formula}n=2weighted voters, and that at some state{a mathematical formula}t′both voters vote for distinct candidates, and one of these candidates is the winner. Then the score of the winner is strictly higher at any later state{a mathematical formula}t&gt;t′.
       </paragraph>
       <paragraph label="Proof">
        W.l.o.g, voter 1 plays in all the odd steps, and voter 2 in all the even steps (if a voter plays several consecutive steps we consider them as a single step). Denote the current votes by {a mathematical formula}a1t′=x and {a mathematical formula}a2t′=y≠x. In order to change the outcome, voter 1 must vote in step {a mathematical formula}t′+1 for some {a mathematical formula}z∉{x,y} s.t. {a mathematical formula}cwt′+1=z. Since {a mathematical formula}x≠y, we have {a mathematical formula}swt′+1=s¨t′+1(z)&gt;s¨t′+1(y)=s¨t′(y)=swt. We can now apply the same argument inductively, as in state {a mathematical formula}t′+1 voters vote for distinct candidates, one of whom is the winner. □
       </paragraph>
       <paragraph label="Theorem 4.8">
        {a mathematical formula}fsˆ,wPLis FDRP for{a mathematical formula}n=2.
       </paragraph>
       <paragraph label="Proof">
        Let state {a mathematical formula}t′&gt;2 be any state where voters vote for two distinct candidates. W.l.o.g. {a mathematical formula}t′ is even, meaning voter 2 just moved to y from some other candidate. By our restriction to direct replies, {a mathematical formula}cwt′=y. By applying Lemma 4.7, the score of the winner must increase in every step until convergence. □
       </paragraph>
       <paragraph label="Theorem 4.9">
        {a mathematical formula}fsˆ,wPLis FIP from the truth for{a mathematical formula}n=2.
       </paragraph>
       <paragraph label="Proof">
        The first step must be of type 1 since initial votes are truthful. Thus at state {a mathematical formula}a1 at least one voter (w.l.o.g. voter 2) is voting for the winner {a mathematical formula}a21=cw1=x. If {a mathematical formula}a11=x as well then we are done since neither voter will want to move. Otherwise, the voters are voting for distinct candidates and thus by Lemma 4.7, the score of the winner must increase in every step until convergence. □
       </paragraph>
       <paragraph>
        Thus, in either case convergence is guaranteed after at most 2m steps.
       </paragraph>
       <paragraph>
        It remains an open question whether there is any restriction on better replies that guarantees order-free acyclicity in weighted games, i.e., if {a mathematical formula}fwPL is order-free-FIP for any {a mathematical formula}n&gt;2 and weights w. However, Proposition 4.6 shows that if such a restricted order-free dynamic exists, it must make use of indirect replies, which is rather unnatural. We thus conjecture that such order-free dynamics do not exist.
       </paragraph>
       <paragraph>
        We next consider how the tie-breaking method affects the convergence properties of the (unweighted) Plurality rule.
       </paragraph>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Arbitrary tie-breaking
      </section-title>
      <paragraph>
       Lev and Rosenschein [14], [46] showed that for any positional scoring rule (including Plurality), we can assign some deterministic tie-breaking rule, so that the resulting voting rule may contain cycles. For any positional scoring rule {a mathematical formula}fα with score vector α, denote by {a mathematical formula}fαLR the same rule with the Lev-Rosenschein tie-breaking.
      </paragraph>
      <paragraph label="Proposition 4.10">
       Theorem 1 in Lev and Rosenschein [46]{a mathematical formula}fαLRis not FBRP for any α, even for{a mathematical formula}n=2, and even from the truth. In particular, Plurality with the Lev-Rosenschein tie-breaking ({a mathematical formula}fPLR) is not FBRP.
      </paragraph>
      <paragraph>
       In fact, a slight modification of their example yields the following:
      </paragraph>
      <paragraph label="Proposition 4.11">
       {a mathematical formula}fPLRis not order-free-FIP, even for{a mathematical formula}n=2, and even from the truth.
      </paragraph>
      <paragraph label="Example 4.11">
       The original example used in [46] for Plurality has four candidates {a mathematical formula}{a,b,c,d} and two voters with preferences {a mathematical formula}a≻1b≻1c≻1d and {a mathematical formula}c≻2d≻2b≻2a. The (non linear) tie-breaking rule is defined such that: a beats d; b beats a and c; c beats a and d; and d beats b. We modify the preferences by switching a and b in voter 2's preferences, so that {a mathematical formula}c≻2d≻2a≻2b.We get the following cycle from the truthful state {a mathematical formula}a0=(a,c):{a mathematical formula} Since each voter has only one available better reply in every step, no restriction on the action scheduler would break the cycle. □
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Randomized tie-breaking
      </section-title>
      <paragraph>
       Let {a mathematical formula}Fsˆ,wP denote the game form that maps any state {a mathematical formula}a∈An to the set {a mathematical formula}argmaxc∈Cssˆ,w,a(c) (all candidates with maximal Plurality score). Let {a mathematical formula}Wt=FP(at)⊆C denote the set of winners at time t. We thus define a direct reply {a mathematical formula}ait−1→iait as one where {a mathematical formula}ait∈Wt.
      </paragraph>
      <paragraph>
       It is easy to see that a preference order {a mathematical formula}Li does not induce a complete order over outcomes of {a mathematical formula}FP. For instance, the order {a mathematical formula}a≻ib≻ic does not determine if i prefers {a mathematical formula}{b} over {a mathematical formula}{a,c}. However, we can naturally extend {a mathematical formula}Li to a partial preference order over subsets, using the following axioms:
      </paragraph>
      <paragraph>
       {a mathematical formula}
      </paragraph>
      <paragraph>
       These axioms reflect various beliefs a rational voter may have on the tie-breaking procedure: the K axiom reflects no assumptions whatsoever; the K+G axioms are consistent with tie-breaking according to a fixed and unknown order [52]; and K+G+R axioms are consistent with random tie-breaking with equal probabilities (see Lemma 4.15 and Proposition 4.23). In this section, we assume all axioms hold, however our results do not depend on the interpretation of this preference extension as a result of random tie-breaking, and we do not specify the voters' preferences in cases not covered by the above axioms. Under strict preferences, it also holds that G entails K [53]. We can also define “weak” variants G2 and R2 for axioms G and R, by replacing all strict relations with weak ones; however, as long as we restrict attention to strict preferences over the alternatives, the weak variants are not required.
      </paragraph>
      <paragraph>
       We define the Plurality with random tie-breaking rule {a mathematical formula}fsˆ,wPR by selecting the winner uniformly at random from {a mathematical formula}Fsˆ,wP. We emphasize that the ties are resolved only after the voting process ends, and thus voters' decisions cannot take the realized outcome into consideration (ex-ante better reply).{sup:10} In order to be able to identify all better replies in a game {a mathematical formula}〈fsˆ,wPR,L〉, we need to extend each {a mathematical formula}Li using Axioms K+G+R. The extended relation {a mathematical formula}Li is just a partial order over subsets of C, but nonetheless this is sufficient to prove our main result in this section.
      </paragraph>
      <paragraph>
       For the following lemma we only need Axiom K, i.e., it does not depend on the tie-breaking assumptions.
      </paragraph>
      <paragraph label="Lemma 4.12">
       If there exists a better reply in{a mathematical formula}fsˆ,wPRfor agent i at state{a mathematical formula}at−1, then i has a direct best reply.
      </paragraph>
      <paragraph label="Proof">
       Suppose there is a better reply {a mathematical formula}ait−1→ib at time {a mathematical formula}t−1. As some best reply always exists, denote by {a mathematical formula}b′ an arbitrary best reply. Let {a mathematical formula}W=Fsˆ,wP(a−it−1,b′), and let {a mathematical formula}a′ be the most preferred candidate of i in W. Then we argue that {a mathematical formula}ait−1→ia′ is a direct best reply of i. Since {a mathematical formula}a′ is a direct reply by definition, it is left to show that {a mathematical formula}a′ is a best reply (for the lexicographic case this follows immediately from {a mathematical formula}W={a′} and {a mathematical formula}fPL(a−it−1,a′)=W={a′}).If {a mathematical formula}b′ is a direct reply then {a mathematical formula}b′=a′ and we are done. Thus assume that {a mathematical formula}b′ is not a direct reply from {a mathematical formula}ait−1. Then {a mathematical formula}b′∉W. By voting for {a mathematical formula}a′∈W, we get that {a mathematical formula}Fsˆ,wP(a−it−1,a′)={a′}, i.e., {a mathematical formula}a′ remains the unique winner. If {a mathematical formula}|W|=1 then we are done as in the lexicographic case. Otherwise we apply Axiom K2 with {a mathematical formula}X={a′},Y=W, and get that {a mathematical formula}a′⪰iW. That is,{a mathematical formula} which means that {a mathematical formula}a′ is also a best reply in {a mathematical formula}fsˆ,wPR. □
      </paragraph>
      <section>
       <section-title>
        Weighted voters
       </section-title>
       <paragraph>
        In contrast with the lexicographic case, the weighted randomized case does not always converge to equilibrium, even with (only) two strategic agents. Moreover, a pure strategy Nash equilibrium may not exist at all [1]. We therefore restrict attention in the rest of this section to unweighted voters.
       </paragraph>
      </section>
      <section>
       <section-title>
        Unweighted voters
       </section-title>
       <paragraph>
        In this case, we show that while better replies may not converge, best replies converge from the truthful profile.
       </paragraph>
       <paragraph label="Proposition 4.13">
        {a mathematical formula}fPRis not FIP.
       </paragraph>
       <paragraph label="Example 4.13">
        {a mathematical formula}C={a,b,c} with initial score {a mathematical formula}sˆ=(0,1,0). The initial state is {a mathematical formula}a0=(a,a,b)—that is, {a mathematical formula}s(a0)=(2,2,0) and the outcome is the winner set {a mathematical formula}FsˆP(a0)={a,b}. The preferences are {a mathematical formula}a≻1c≻1b, {a mathematical formula}b≻2a≻2c and {a mathematical formula}c≻3b≻3a. We get the following cyclic sequence:{a mathematical formula} We emphasize that each step is justified as a better reply by either Axiom K or Axiom G. For example, in the step of agent 2 in the top row, agent 2 prefers {a mathematical formula}b≻2a, and thus {a mathematical formula}b≻2{a,b} by Axiom G. This will be used later in Section 4.4.
       </paragraph>
       <paragraph label="Theorem 4.14">
        {a mathematical formula}fsˆPRis FBRP from the truth.
       </paragraph>
       <paragraph label="Proof">
        We denote the sets of winners and runner-ups at time t as {a mathematical formula}Wt=FsˆP(at) (i.e., we omit the scripts); and {a mathematical formula}Rt={c:st(c)=swt−1}. We will show by induction that at any step {a mathematical formula}at−1→iat:
        <list>
         {a mathematical formula}Wt∪Rt⊆Wt−1∪Rt−1 (i.e., the set of potential winners is never expanding).{a mathematical formula}ait∈Wt (i.e., step t is a direct reply).{a mathematical formula}ait is the most preferred candidate for i in {a mathematical formula}Wt∪Rt.{a mathematical formula}ait−1≻iait (in the terminology of [34], this is a compromise step).Either {a mathematical formula}swt&gt;swt−1 (the score of the winner strictly increases), or {a mathematical formula}swt=swt−1 and {a mathematical formula}|Wt|&gt;|Wt−1|.Assume that for some
        </list>
        <paragraph>
         {a mathematical formula}t≥1, all of the above holds for any {a mathematical formula}t′&lt;t (so we prove the base case together with the other cases). Since {a mathematical formula}a0 is truthful, the first step of any voter is always a compromise move. Also, if i had already moved at some previous time {a mathematical formula}t′&lt;t, then {a mathematical formula}ait′ is most preferred in {a mathematical formula}Wt′∪Rt′.By induction, {a mathematical formula}a=ait−1 is the most preferred candidate in some {a mathematical formula}C′ that contains {a mathematical formula}Wt−1∪Rt−1 ({a mathematical formula}C′=C in i's first step, and {a mathematical formula}C′=Wt′∪Rt′ at any other step {a mathematical formula}t′). Let x and y be i's most preferred candidates in {a mathematical formula}Wt−1 and in {a mathematical formula}Rt−1, respectively, and denote the best reply by {a mathematical formula}a′=ait. Each of a or {a mathematical formula}a′ may belong to {a mathematical formula}Wt−1, to {a mathematical formula}Rt−1, or to neither set. This means there are {a mathematical formula}3⋅3=9 cases to check. Fortunately, we can show that some of these cases immediately lead to a contradiction, and in the other cases all invariants 1–5 will hold after step t.Consider first the case {a mathematical formula}a∈Wt−1. Since a is most preferred in {a mathematical formula}C′, it is strictly more preferred than any other candidate in {a mathematical formula}Wt−1 or in {a mathematical formula}Rt−1 (in particular, {a mathematical formula}a=x).
        </paragraph>
        <list>
         <list-item label="•">
          If {a mathematical formula}a′∈Wt−1, then we show that all invariants hold: (1) {a mathematical formula}Wt∪Rt=Wt−1∖{a}⊆Wt−1∪Rt−1; (2) holds since {a mathematical formula}a′ becomes the unique winner; (3) if there was another candidate {a mathematical formula}z∈Wt∪Rt=Wt−1∖{a} such that {a mathematical formula}z≻ia′, then z would be i's best reply; (4) follows since {a mathematical formula}a′∈C′ and a is the most preferred in {a mathematical formula}C′; and (5) follows since the score of the winner {a mathematical formula}a′ increases by 1.
         </list-item>
         <list-item label="•">
          If {a mathematical formula}a′∈Rt−1 we get {a mathematical formula}Wt=(Wt−1∖{a})∪{a′}≺iWt−1 by Axiom R. Thus {a mathematical formula}a→ia′ is not an improvement step.
         </list-item>
         <list-item label="•">
          If {a mathematical formula}a′∉Wt−1∪Rt−1 then we further split into two cases:
         </list-item>
        </list>
        <paragraph>
         Next, suppose {a mathematical formula}a∉Wt−1. We further split to subcases based on {a mathematical formula}a′.
        </paragraph>
        <list>
         <list-item label="•">
          If {a mathematical formula}a′∈Wt−1 then {a mathematical formula}Wt=FsˆP(a−i,a′)={a′}. Then {a mathematical formula}a′=x, as otherwise {a mathematical formula}FsˆP(a−i,x)={x}≻i{a′}, and i is strictly better off by voting for x. This entails {a mathematical formula}Wt={x},Rt=Wt−1∖{x} so all invariants 1–5 hold: (1) since {a mathematical formula}Wt−1=Wt∪Rt; (2) since {a mathematical formula}Wt={a′}; (3) follows from (1) since {a mathematical formula}a′=x is the most preferred in {a mathematical formula}Wt−1; (4) follows from (1) since {a mathematical formula}a=ait−1 is the most preferred in {a mathematical formula}C′, and {a mathematical formula}a′∈C′; (5) follows since the score of the unique winner {a mathematical formula}a′ increases by 1.
         </list-item>
         <list-item label="•">
          If {a mathematical formula}a′∈Rt−1 then {a mathematical formula}Wt=FsˆP(a−i,a′)={a′}∪Wt−1. Then {a mathematical formula}a′=y, as otherwise {a mathematical formula}F(a−i,y)={y}∪Wt−1≻i{a′}∪Wt−1 by Axiom R, which means i is strictly better off by voting for y. This entails {a mathematical formula}Wt={y}∪Wt−1, {a mathematical formula}Rt=Rt−1∖{y}. We also get that {a mathematical formula}a′=y≻ix or else x would have been a strictly better reply since {a mathematical formula}FsˆP(a−i,x)={x}≻i{y}∪Wt−1 by Axiom K. Thus all invariants 1–5 hold: (1) {a mathematical formula}Wt=Wt−1∪{y}⊆Wt−1∪Rt−1 and {a mathematical formula}Rt=Rt−1∖{y}; (2) since {a mathematical formula}a′∈Wt; (3) follows from (1) since {a mathematical formula}a′=ait=y is most preferred in {a mathematical formula}Rt−1 and strictly preferred to x; (4) follows from (1) as in the previous case; and (5) follows since {a mathematical formula}Wt=Wt−1∪{a′}.
         </list-item>
         <list-item label="•">
          If {a mathematical formula}a′∉Wt−1∪Rt−1, then {a mathematical formula}Wt=F(a−i,a′)=Wt−1. The outcome does not change so this cannot be an improvement step for i. □
         </list-item>
        </list>
       </paragraph>
       <paragraph>
        The proofs and examples above make use only of the axioms, without specifying an explicit cardinal scale. To show that the result is tight, we next consider games with specific cardinal utility scales.
       </paragraph>
      </section>
      <section>
       <section-title>
        Cardinal utilities
       </section-title>
       <paragraph>
        A (cardinal) utility function is a mapping of candidates to real numbers {a mathematical formula}u:C→R, where {a mathematical formula}ui(c)∈R denotes the utility of candidate c to agent i. We say that {a mathematical formula}ui is consistent with a preference relation {a mathematical formula}Li if {a mathematical formula}ui(c)&gt;ui(c′)⇔c≻ic′. The definition of cardinal utility naturally extends to multiple winners by setting {a mathematical formula}ui(W)=1|W|∑c∈Wui(c) for any subset {a mathematical formula}W⊆C. As explained above, one interpretation of this is that the winner is selected uniformly at random from the set W.
       </paragraph>
       <paragraph label="Lemma 4.15">
        Consider any cardinal utility function u and the partial preference order L it induces on subsets by random tie-breaking. Then, L satisfies Axioms K+G+R.
       </paragraph>
       <paragraph>
        The proof is rather straightforward, and is deferred to the appendix. Note that a cardinal scale {a mathematical formula}ui may induce additional preference relations that are not implied by (nor contradict) the axioms.
       </paragraph>
       <paragraph label="Proposition 4.16">
        {a mathematical formula}fPRis not FIP from the truth, even for{a mathematical formula}n=2.
       </paragraph>
       <paragraph label="Example 4.16">
        We use 5 candidates with initial score {a mathematical formula}sˆ=(1,1,2,0,0), and 2 agents with preferences that imply {a mathematical formula}{b,c}≻1c, {a mathematical formula}{a,c}≻1{a,b,c} (with {a mathematical formula}d=⊤(L1)), and {a mathematical formula}{a,b,c}≻2{b,c}, {a mathematical formula}c≻2{a,c} (with {a mathematical formula}e=⊤(L2)). The following cycle occurs: {a mathematical formula}(1,1,2,1,1){c}→1(1,2,2,0,1){b,c}→2(2,2,2,0,0){a,b,c}→1(2,1,2,1,0){a,c}→2(1,1,2,1,1){c}.To see why there must exist valid preferences as above, note that {a mathematical formula}L1 is consistent with (for example) {a mathematical formula}u1=(5,3,2,8,0) and likewise {a mathematical formula}L2 is consistent with {a mathematical formula}u2=(4,2,5,0,8). Then by Lemma 4.15 the preferences hold all axioms. □
       </paragraph>
       <paragraph>
        Finally, in contrast to the lexicographic case, convergence is no longer guaranteed if agents start from an arbitrary profile of votes, or are allowed to use direct replies that are not best replies. In the next propositions we define voters' preferences directly as cardinal utilities. The following example shows that in the randomized tie-breaking setting even direct best reply dynamics may have cycles, albeit for specific utility scales.
       </paragraph>
       <paragraph label="Proposition 4.17">
        {a mathematical formula}fPRis not order-free-FIP.
       </paragraph>
       <paragraph label="Example 4.17">
        There are 4 candidates {a mathematical formula}{a,b,c,x} and 3 agents with utilities {a mathematical formula}u1=(7,3,0,4), {a mathematical formula}u2=(0,7,3,4) and {a mathematical formula}u3=(3,0,7,4). In particular, the following preference relations hold: {a mathematical formula}a≻1{a,b}≻1x≻1{a,c}; {a mathematical formula}b≻2{b,c}≻2x≻2{a,b}; and {a mathematical formula}c≻3{a,c}≻3x≻3{b,c}.Consider the initial state {a mathematical formula}a0=(a,b,x) with {a mathematical formula}s(a0)=(1,1,0,1) and the outcome {a mathematical formula}{a,b,x}. We have the following cycle where every step is the unique reply of the playing agent.{a mathematical formula}
       </paragraph>
       <paragraph label="Proposition 4.18">
        {a mathematical formula}fPRis not FDRP even from the truth.
       </paragraph>
       <paragraph label="Example 4.18">
        We take the game from Ex. 4.17, and add for each voter {a mathematical formula}i∈{1,2,3} a candidate {a mathematical formula}di, s.t. {a mathematical formula}ui(di)=8,ui(dj)=j for {a mathematical formula}j≠i. Thus initially each voter i votes for {a mathematical formula}di. We also add an initial score of 3 to each of the candidates {a mathematical formula}{a,b,c,x}. Voter 3 moves first to {a mathematical formula}a31=x, which is a direct reply. Then voters 1 and 2 move to their best replies {a mathematical formula}a,b, respectively. Now the cycle continues as per Ex. 4.17. □
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Stochastic dominance and local dominance
      </section-title>
      <paragraph>
       Extending {a mathematical formula}Li to a complete preference over subsets (that is consistent with the axioms) is one way to define a better reply dynamics for {a mathematical formula}FP. Another way to derive a well-defined dynamics from any partial order{a mathematical formula}Li over subsets of candidates, is by assuming that a voter performs a better reply step if she strictly prefers the new outcome according to {a mathematical formula}Li, and otherwise (if the new outcome is same, worse, or incomparable) she does not move.
      </paragraph>
      <paragraph>
       One example of such a partial order is stochastic dominance (SD), which was applied to tie-breaking by [12]. A different partial order is implied by local dominance (LD) which was defined for voting with uncertainty about the outcome [34], [54]. We show how convergence results for LD/SD dynamics fit with other results.
      </paragraph>
      <section>
       <section-title>
        Stochastic dominance
       </section-title>
       <paragraph>
        Reyhani and Wilson [12] assume that ties are broken uniformly at random, and that a voter will only perform a step that stochastically dominates the current winner(s), if such exists.
       </paragraph>
       <paragraph label="Theorem 4.19">
        Theorem 5.7 in Reyhani and Wilson [12]Plurality with stochastic dominance tie-breaking is FDBRP.
       </paragraph>
       <paragraph>
        A natural question is how is this result related to the results in Section 4.3, where voters have cardinal utilities.
       </paragraph>
       <paragraph>
        Since any SD step is also a better reply under any cardinal utility scale [12], any strong or order-free convergence result for the latter applies to the former, but not vice-versa. In particular, if we restrict attention to convergence from the truth, we have the following immediate corollary from Theorem 4.14:
       </paragraph>
       <paragraph label="Corollary 4.20">
        Plurality with stochastic dominance tie-breaking is FBRP from the truth.
       </paragraph>
      </section>
      <section>
       <section-title>
        Local dominance
       </section-title>
       <paragraph>
        Suppose that there are several candidates with maximal score. A voter may consider all of them as “possible winners,” without specifying how the actual winner is selected. If the voter is concerned about making a move that will leave him worse off, he will only make moves that will improve his utility with certainty, i.e., that dominate his current action (where possible worlds are all strict tie-breaking orders) [34], [41], [54].{sup:11}
       </paragraph>
       <paragraph label="Theorem 4.21">
        Theorem 11 in the full version of Meir [41]Plurality with Local-Dominance tie-breaking is FDRP.
       </paragraph>
      </section>
      <section>
       <section-title>
        Which tie-breaking axioms are required for convergence?
       </section-title>
       <paragraph>
        We can use our axioms to characterize all better replies. Note that by our assumption voters that cannot conclude that a step will myopically benefit them prefer to keep their current vote. Thus adding more axioms lets the voter make a more informed decision and therefore only increases the number of improvement steps and may only add cycles. We emphasize that in either case convergence may be to a state that is not a Nash equilibrium.
       </paragraph>
       <paragraph>
        If we assume that voters only follow steps that are better replies by Axiom K (an extreme risk-averse behavior), then it is easy to see that only moves to a more-preferred candidate can be better replies (any move to or from a tie cannot follow from Axiom K and is thus forbidden), which means that there are trivially no cycles, and Plurality becomes FIP.
       </paragraph>
       <paragraph label="Proposition 4.22">
        See appendix for the proofA step{a mathematical formula}a→ia′is a better reply under unknown tie-breaking and local dominance, if and only if{a mathematical formula}FP(a′)≻iFP(a)is entailed by{a mathematical formula}Li, Axioms K+G, and transitivity.
       </paragraph>
       <paragraph label="Proposition 4.23">
        Meir [55]A step{a mathematical formula}a→ia′is a better reply under random tie-breaking and stochastic dominance, if and only if{a mathematical formula}FP(a′)≻iFP(a)is entailed by{a mathematical formula}Li, Axioms K+G+R, and transitivity.
       </paragraph>
       <paragraph>
        Thus by Theorem 4.21, Proposition 4.22, Plurality with voters that follow Axioms K+G is FDRP (i.e., guaranteed to converge if voters stick to direct replies). In contrast, the analysis of Ex. 4.13 shows that all steps are entailed by Axioms K+G, meaning that imposing Axioms K+G make it possible to have cycles of arbitrary better replies.
       </paragraph>
       <paragraph>
        Similarly, by Theorem 4.19, Corollary 4.20, Proposition 4.23, Plurality with voters that follow all Axioms K+G+R is both FDBRP and FBRP from the truth. That is, convergence is guaranteed if voters both stick to best replies, and either keep them direct or start from the truthful state. It is left as an open question if cycles of arbitrary direct replies are possible, i.e., whether FDRP holds even with Axiom R.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="5">
     <section-title>
      Separating order-free and weak acyclicity
     </section-title>
     <paragraph>
      Except for Plurality and Veto, convergence is not guaranteed even under restrictions on the action scheduler and the initial state. In contrast, simulations [33], [34], [35] show that iterative voting almost always converges even when this is not guaranteed by theory. We believe that weak acyclicity is an important part of the explanation to this gap. Recall that a voting rule is weakly acyclic if from any initial profile, there is some sequence of better-replies that reaches a pure strategy Nash equilibrium. Indeed, we show that there are voting rules, including a common variation of the Plurality rule, that are not order-free acyclic, but are weakly acyclic. This explains convergence in practice, since in a weakly acyclic game with a random scheduler, every cycle will only be repeated a finite number of times before convergence must occur.
     </paragraph>
     <section label="5.1">
      <section-title>
       Plurality with random tie-breaking
      </section-title>
      <paragraph>
       We have seen in Section 4 that while {a mathematical formula}fPR is FBRP from the truthful initial state, this is no longer true from arbitrary states, and in fact {a mathematical formula}fPR is not order-free-FIP under any action scheduler. Our main theorem in this section shows that under a certain scheduler (of both agents and actions), convergence is guaranteed from any state. Further, this still holds if actions are restricted to direct replies. We use the following lemma, whose proof is in the appendix.
      </paragraph>
      <paragraph label="Lemma 5.1">
       Consider any game{a mathematical formula}G=〈fsˆPR,L〉. Consider some candidate z, and suppose that in{a mathematical formula}a0, there are{a mathematical formula}x,ys.t.{a mathematical formula}s0(x)≥s0(y)≥s0(z)+2. Then, for any sequence of direct replies,{a mathematical formula}z∉f(at).
      </paragraph>
      <paragraph label="Theorem 5.2">
       {a mathematical formula}fsˆPRis weak-FDRP.
      </paragraph>
      <paragraph label="Proof">
       Consider a game {a mathematical formula}G=〈fsˆPR,L〉, and an initial state {a mathematical formula}a0. For a state a, denote by {a mathematical formula}B(a)⊆An all states reachable from a via paths of direct replies. Let {a mathematical formula}B=B(a0), and assume towards a contradiction that B does not contain a Nash equilibrium. For every {a mathematical formula}b∈B, let {a mathematical formula}C(b)={c∈C:∃a∈B(b)∧c∈f(a)}, i.e., all candidates that are winners in some state reachable from b.For any {a mathematical formula}b∈B(a0), define a game {a mathematical formula}Gb by taking G and eliminating all candidates not in{a mathematical formula}C(b). Since we only consider direct replies, for any {a mathematical formula}a∈B(b), the set of outgoing edges {a mathematical formula}I(a) is the same in G and in {a mathematical formula}Gb (as any direct reply must be to a candidate in {a mathematical formula}C(b)). Thus by our assumption, the set {a mathematical formula}B(b) in game {a mathematical formula}Gb does not contain a NE.For any {a mathematical formula}b∈B(a0), let {a mathematical formula}b⁎ be the truthful state of game {a mathematical formula}Gb, and let {a mathematical formula}T(b)⊆N be the set of agents who are truthful in b. That is, {a mathematical formula}i∈T(b) if {a mathematical formula}bi=bi⁎.Let {a mathematical formula}b0 be some state {a mathematical formula}b∈B(a0) s.t. {a mathematical formula}|T(b)| is maximal, and let {a mathematical formula}T0=T(b0). If {a mathematical formula}|T0|=n then {a mathematical formula}b0 is the truthful state of {a mathematical formula}Gb0, and thus by Theorem 4.14 all best reply paths from {a mathematical formula}b0 in {a mathematical formula}Gb0 lead to a NE, in contradiction to {a mathematical formula}B(b0) not containing any NE. Thus {a mathematical formula}T0&lt;n. We will prove that there is a path from {a mathematical formula}b0 to a state {a mathematical formula}b′ s.t. {a mathematical formula}|T(b′)|&gt;|T0|.Let {a mathematical formula}i∉T(b0) (must exist by the previous paragraph). Consider the score of candidate {a mathematical formula}bi⁎ at state {a mathematical formula}b0. We divide into 6 cases. All scores specified below are in the game {a mathematical formula}Gb0.
      </paragraph>
      <list>
       <list-item label="Case 1.">
        {a mathematical formula}|f(b0)|&gt;1 and {a mathematical formula}bi⁎∈f(b0) (i.e {a mathematical formula}bi⁎ is one of several winners). Then consider the step {a mathematical formula}b0→ibi⁎. This make {a mathematical formula}bi⁎ the unique winner, and thus it is a direct best reply for i. In the new state {a mathematical formula}b′=(b−i0,bi⁎), and we have {a mathematical formula}T(b′)=T(b0)∪{i}.
       </list-item>
       <list-item label="Case 2.">
        {a mathematical formula}s0(bi⁎)=sw0−1 (i.e., {a mathematical formula}bi⁎ needs one more vote to become a winner). By Axioms G and R, i prefers {a mathematical formula}f(b−i0,bi⁎) over {a mathematical formula}f(b0). Then similarly to case 1, i has a direct step {a mathematical formula}b0→ibi⁎, which results in a state {a mathematical formula}b′ that is closer to being truthful.{sup:12}
       </list-item>
       <list-item label="Case 3.">
        {a mathematical formula}bi⁎=f(b0) (i.e {a mathematical formula}bi⁎ is the unique winner). Then the next step {a mathematical formula}b0→jb1 will bring us to one of the two previous cases. Moreover, it must hold that {a mathematical formula}j∉T(b0) since otherwise {a mathematical formula}bj0=bj⁎=f(b0) which means {a mathematical formula}Ij(b0)=∅. Thus {a mathematical formula}|T(b′)|=|T(b1)|+1≥|T(b0)|+1.
       </list-item>
       <list-item label="Case 4.">
        There are {a mathematical formula}x,y s.t. {a mathematical formula}s0(x)≥s0(y)≥s0(bi⁎)+2. Then by Lemma 5.1{a mathematical formula}bi⁎ can never be selected, in contradiction to {a mathematical formula}bi⁎∈C(b0).
       </list-item>
       <list-item label="Case 5.">
        There is a unique winner {a mathematical formula}x=f(b0), and {a mathematical formula}s0(x)≥s0(y)+2 for all other candidates (note that there has to be an equality for at least one candidate, or else there is no better reply). Then the next step (by some voter j) must be from x, which brings us to one of the Cases 1, 2 (if {a mathematical formula}s0(bi⁎)=sw0−2) or in Case 4 (if {a mathematical formula}s0(bi⁎)&lt;sw0−2).
       </list-item>
       <list-item label="Case 6.">
        The last case is when there is a unique winner {a mathematical formula}x=f(b0), some other candidate y with {a mathematical formula}s0(y)=sw0−1, and {a mathematical formula}s0(bi⁎)=sw0−2. Then there are two types of steps: a type I step is from x to y (by a voter that prefers y over x), and a type II step is any other step. A type I step puts us back in Case 6, but there can be at most 1 such step by each voter. Thus eventually there will be a type II step. Finally, any type II move puts us either in Case 1 or 2 (if x loses a vote) or in Case 4 (if y gains a vote).
       </list-item>
      </list>
      <paragraph label="Remark 5.1">
       Theorem 5.2 and Ex. 4.17 provide a partial answer to an open question regarding whether there are game forms that admit weak-FIP but not order-free-FIP [7]. Indeed, the game form {a mathematical formula}fPR for {a mathematical formula}m=4,n=3 is such an example, but one that uses randomization. However, if we think of {a mathematical formula}fPR as a deterministic game form with {a mathematical formula}2m−1 possible outcomes (all nonempty subsets of candidates), where agents are restricted to m actions each, then the allowed utility profiles are constrained (by Axioms G and R) and thus this result does not settle Kukushkin's question completely.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Weighted plurality
      </section-title>
      <paragraph>
       When voters are weighted, cycles of direct replies can emerge [1], [56]. We conjecture that such cycles must depend on the order of agents, and that certain orders will break such cycles and reach an equilibrium, at least from the truthful state.
      </paragraph>
      <paragraph label="Conjecture 5.3">
       {a mathematical formula}fsˆ,wPLis weak-FDRP (in particular weak-FIP).
      </paragraph>
      <paragraph>
       Similar techniques to those used so far (where some invariants are maintained throughout the better reply path) appear to be insufficient to prove the conjecture. For example, in contrast to the unweighted case, a voter might return to a candidate she deserted in any scheduler, even if only two weight levels are present. We thus leave the proof of the general conjecture for future work, possibly with the aid of “non-constructive” convergence proofs, such as the ones in [41].
      </paragraph>
      <paragraph>
       Yet, we want to demonstrate the power of weak acyclicity over order-free acyclicity, even when there are no randomness or restrictions on the utility space. That is, we intend to provide a definite (negative) answer to Kukushkin's question of whether weak acyclicity entails order-free acyclicity. To this end, we use a slight variation of Plurality with weighted voters and lexicographic tie-breaking.
      </paragraph>
      <paragraph label="Theorem 5.4">
       There exists a game form{a mathematical formula}f⁎s.t.{a mathematical formula}f⁎is weak-FIP but not order-free-FIP.
      </paragraph>
      <paragraph label="Proof">
       Consider the game {a mathematical formula}〈fsˆ,wPL,L〉 from Example 4.6: The initial fixed score of candidates {a mathematical formula}{a,b,c,d} is {a mathematical formula}sˆ=(0,1,2,3). The weight of each voter {a mathematical formula}i∈{1,2,3} is i. The preference profile is as follows: {a mathematical formula}c≻1d≻1b≻1a, {a mathematical formula}b≻2c≻2a≻2d, and {a mathematical formula}a≻3b≻3c≻3d. This game was used in Section 4.1 to demonstrate that Plurality with weighted voters is not FDRP, however it can be verified that this game is order-free-FIP so it is not good enough for our use.If we ignore the agents' preferences, we get a particular game form {a mathematical formula}fsˆ,wPL where {a mathematical formula}N={1,2,3}, {a mathematical formula}M={a,b,c,d}, {a mathematical formula}sˆ=(0,1,2,3) and {a mathematical formula}w=(1,2,3).We define {a mathematical formula}f⁎ by modifying {a mathematical formula}fsˆ,wPL with the following restrictions on agents' actions: {a mathematical formula}A1={c,d},A2={b,c}, and {a mathematical formula}A3={a,b,d}. Thus {a mathematical formula}f⁎ is a {a mathematical formula}2×2×3 game form, presented in Fig. 7(a).We first show that {a mathematical formula}f⁎ is not order-free-FIP. Indeed, consider the game {a mathematical formula}G⁎ accepted from {a mathematical formula}f⁎ with the same preferences from game G (Fig. 7(b)). We can see that there is a cycle of length 6 (in bold). An agent scheduler that always selects the agent with the bold reply guarantees that convergence does not occur, since in all 6 relevant states the selected agent has no alternative replies.Next, we show that {a mathematical formula}f⁎ is weak-FIP. That is, for any preference profile there is some scheduler that guarantees convergence. We thus divide into cases according to the preferences of agent 3. In each case, we specify a state where the scheduler selects agent 3, the action of the agent, and the new state.We note that since all thick edges must be oriented in the same direction, {a mathematical formula}a≻3b if and only if {a mathematical formula}b≻3c. Thus the following three cases are exhaustive.{a mathematical formula} In either case, agent 3 moves from a state on the cycle to a Nash equilibrium. □
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Proofs
     </section-title>
     <paragraph label="Theorem 3.4">
      For any{a mathematical formula}n≥7, there is a non-separable game form{a mathematical formula}fn⁎with n agents s.t.{a mathematical formula}fn⁎is FIP.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}C′={c1,…,c2n} and {a mathematical formula}C=C′∪{z}. Let {a mathematical formula}Ai={0,1} for each voter. Every voting function {a mathematical formula}fn is a function from the n dimensional binary cube {a mathematical formula}B={0,1}n to C.Denote by {a mathematical formula}k‾ the total number of bits required for an optimal single error-correcting code (Hamming code) with k data bits. For example, for {a mathematical formula}k=4 we need {a mathematical formula}4‾=7 bits. In particular, there is a mapping {a mathematical formula}q:{0,1}k→{0,1}k‾ such that the Hamming distance between any two words is at least 3 [49]. Formally, for all {a mathematical formula}w,w′∈{0,1}k, it holds that {a mathematical formula}|{j:q(w)j≠q(w′)j}|≥3.For reasons that will become apparent later, we want to have {a mathematical formula}k‾≤n, and {a mathematical formula}2n=|C′|≤2k.For any {a mathematical formula}n=7, set {a mathematical formula}r=⌈log2⁡(n+1)⌉=3, and {a mathematical formula}k=⌈log2⁡(2n)⌉=4. Thus {a mathematical formula}2r−r−1=23−3−1=4=k. From coding theory [49], for all {a mathematical formula}r≥2, if {a mathematical formula}k≤2r−r−1, then {a mathematical formula}k‾=2r−1=7 bits are sufficient to code all {a mathematical formula}(k=4)-bit strings. That is, there is a valid code q from {a mathematical formula}{0,1}4 to {a mathematical formula}{0,1}7.Note that {a mathematical formula}k‾=7=n, and that {a mathematical formula}|C′|=2n=14&lt;24=2k.Let {a mathematical formula}bin(t,k)∈{0,1}k be the k-bit binary representation of {a mathematical formula}t≤2n (e.g., {a mathematical formula}bin(5,4)=0101). Since {a mathematical formula}2n&lt;16=24, all of {a mathematical formula}t≤2n=14 have a 4-bit representation. Using the Hamming code q, we map each outcome {a mathematical formula}ct∈C′ to a specific profile {a mathematical formula}at=q(bin(t,4))∈{0,1}7={0,1}n.We now define {a mathematical formula}fn⁎ by setting {a mathematical formula}fn⁎(at)=ct for all {a mathematical formula}t≤2n, and {a mathematical formula}fn⁎(a)=z for all {a mathematical formula}2n−2n=114 other profiles.For any two profiles {a mathematical formula}a,a′, let {a mathematical formula}d(a,a′) be the number of voters that disagree in {a mathematical formula}a,a′ (the Hamming distance on the cube). Let {a mathematical formula}B⊆B be all 14 profiles whose outcome is not z. By the construction above, we have that {a mathematical formula}d(a,a′)≥3 for all {a mathematical formula}a,a′∈B.Assume towards a contradiction that there is some cycle of better replies in {a mathematical formula}fn⁎. Then there must be a path containing at least three distinct outcomes, and thus at least two profiles from B. Denote these profiles by {a mathematical formula}a,b∈B. Since any path between a and b is of length at least 3, the path must contain at least two consequent profiles whose outcome is z. This path cannot be a better reply path, since a better reply must in particular change the outcome. Hence we get a contradiction, and {a mathematical formula}fn⁎ is FIP.Finally, {a mathematical formula}fn⁎ cannot be separable, exactly as in the proof for {a mathematical formula}n≥8. □
     </paragraph>
     <paragraph label="Lemma 4.15">
      Consider any cardinal utility function u and the partial preference order L it induces on subsets by random tie-breaking. L holds Axioms K+G+R.
     </paragraph>
     <paragraph label="Proof">
      Let u be any utility scale, we will show that all axioms hold. Let {a mathematical formula}a,b∈C and {a mathematical formula}W⊆C∖{a,b}.{a mathematical formula} thus {a mathematical formula}{a}∪W≻L{b}∪W, and Axiom R holds.Let {a mathematical formula}a∈C,W⊆C s.t. {a mathematical formula}∀b∈W,a≻b. Then{a mathematical formula} thus {a mathematical formula}a≻L{a}∪W≻LW and Axiom G holds.Axiom K1 follows immediately from G. K2 also follows if preferences are strict. Even if there are ties, and {a mathematical formula}a⪰w for all {a mathematical formula}a∈A,w∈W then:{a mathematical formula} i.e., {a mathematical formula}A⪰LW. □
     </paragraph>
     <paragraph label="Proposition 4.22">
      A step{a mathematical formula}a→ia′is a better-response under unknown tie-breaking and local dominance, if and only if{a mathematical formula}f(a′)≻if(a)is entailed by{a mathematical formula}Li, Axioms K+G, and transitivity.
     </paragraph>
     <paragraph label="Proof">
      Suppose that {a mathematical formula}X=f(a′) locally-dominates {a mathematical formula}Y=f(a). Let {a mathematical formula}Z=X∩Y, and {a mathematical formula}X′=X∖Z, {a mathematical formula}Y′=Y∖Z. We must have {a mathematical formula}x≻iy for any {a mathematical formula}x∈X,y∈Y′, otherwise, a tie-breaking order that selects y first and x second would make i strictly lose when moving from Y to X. Similarly, {a mathematical formula}x≻iy for any {a mathematical formula}x∈X′,y∈Y. If {a mathematical formula}Z=∅ then {a mathematical formula}X=X′≻iY′=Y follows from Axiom K. Otherwise, by repeatedly applying Axiom G we get {a mathematical formula}X⪰iZ⪰iY with at least one relation being strict.In the other direction, since Axiom G can only be used to add elements lower (or higher) than all existing elements, it may only induce relations of the form {a mathematical formula}Z≻Z∪Y′ where {a mathematical formula}z≻y for all {a mathematical formula}z∈Z,y∈Y′; or relations of the form {a mathematical formula}Z∪X′≻Z where {a mathematical formula}x≻z for all {a mathematical formula}z∈Z,x∈X′. Thus if {a mathematical formula}X≻Y follows from Axiom G, they must have the form {a mathematical formula}X=Z∪X′,Y=Z∪Y′ where {a mathematical formula}x≻z≻y for all {a mathematical formula}x∈X′,z∈Z,y∈Y′. To see that this entails local dominance, let {a mathematical formula}xL=L(X) be the first element in X according to order {a mathematical formula}L∈π(C), and likewise for Y. For any L, {a mathematical formula}xL⪰yL (with equality iff {a mathematical formula}L(X)=L(Y)∈Z). Further, either {a mathematical formula}X′ or {a mathematical formula}Y′ are non-empty (w.l.o.g. {a mathematical formula}X′). Consider an order {a mathematical formula}L′ such that {a mathematical formula}L′(X)∈X′, then {a mathematical formula}xL′≻y for all {a mathematical formula}y∈Y and in particular {a mathematical formula}xL′≻yL′. □
     </paragraph>
     <paragraph label="Lemma 5.1">
      Consider any game{a mathematical formula}G=〈fsˆPR,L〉. Consider some candidate z, and suppose that in{a mathematical formula}a0, there are{a mathematical formula}x,ys.t.{a mathematical formula}s0(x)≥s0(y)≥s0(z)+2. Then, for any sequence of direct replies,{a mathematical formula}z∉f(at).
     </paragraph>
     <paragraph label="Proof">
      We show that at any time {a mathematical formula}t≥0 there are {a mathematical formula}xt,yt s.t. {a mathematical formula}s0(x),s0(y)≥s0(z)+2. For {a mathematical formula}t=0 this holds for {a mathematical formula}xt=x,yt=y. Assume by induction that the premise holds for {a mathematical formula}at−1. Then there are two cases:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}|f(at−1)|≥2. Then since step t must be a direct reply, it must be to some candidate z with {a mathematical formula}st−1(z)≥swt−1−1. Also, either {a mathematical formula}xt−1 or {a mathematical formula}yt−1 did not lose votes (w.l.o.g. {a mathematical formula}xt−1). Thus {a mathematical formula}st(x),st(z)≥swt−1≥st−1(z)+2≥st(z)+2.
      </list-item>
      <list-item label="2.">
       {a mathematical formula}|f(at−1)|=1. Then suppose {a mathematical formula}f(at−1)={xt−1}, and we have that {a mathematical formula}swt−1≥st−1(z)+3. The next step is z where either {a mathematical formula}st−1(z)=swt−1−1 (and then we conclude as in case 1), or {a mathematical formula}st−1(z)=swt−1−2 and {a mathematical formula}xt−1 loses 1 vote. In the latter case, {a mathematical formula}st(xt−1)=st(z)=swt−1−1≥st−1(z)+2≥st(z)+2. □
      </list-item>
     </list>
    </section>
   </appendices>
  </root>
 </body>
</html>