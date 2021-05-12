<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Information capture and reuse strategies in Monte Carlo Tree Search, with applications to games of hidden information.
   </title>
   <abstract>
    Monte Carlo Tree Search (MCTS) has produced many breakthroughs in search-based decision-making in games and other domains. There exist many general-purpose enhancements for MCTS, which improve its efficiency and effectiveness by learning information from one part of the search space and using it to guide the search in other parts. We introduce the Information Capture And ReUse Strategy (ICARUS) framework for describing and combining such enhancements. We demonstrate the ICARUS framework's usefulness as a frame of reference for understanding existing enhancements, combining them, and designing new ones. We also use ICARUS to adapt some well-known MCTS enhancements (originally designed for games of perfect information) to handle information asymmetry between players and randomness, features which can make decision-making much more difficult. We also introduce a new enhancement designed within the ICARUS framework, EPisodic Information Capture and reuse (EPIC), designed to exploit the episodic nature of many games. Empirically we demonstrate that EPIC is stronger and more robust than existing enhancements in a variety of game domains, thus validating ICARUS as a powerful tool for enhancement design within MCTS.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Monte Carlo Tree Search (MCTS) is a decision tree search algorithm that has produced a huge leap in AI player strength for a range of two-player zero-sum games and proven effective in a wide range of games and decision problems [1]. In particular, MCTS is effective when it is difficult to evaluate non-terminal states so that traditional depth-limited search methods perform poorly. For example, MCTS has advanced the state of the art in computer Go from the level of weak amateur to approach that of professional players in only a few years [2], [3]. MCTS has also produced state-of-the-art performance in many other domains, with over 250 papers published since the algorithm's invention in 2006 [1]. MCTS shows promise in real-time games, being the basis of winning competition entries for both Ms. Pac-Man [4] and the Physical Travelling Salesman Problem [5].
     </paragraph>
     <paragraph>
      Generally speaking, MCTS algorithms heuristically build an asymmetric partial search tree by applying machine learning, using the weak reward signal given by randomly simulating a playout to the end of the game from nodes representing intermediate positions. The tree is descended by recursively applying a multi-armed bandit formula (such as UCB1 [6]) to each tree node's counts of simulation wins and visits.
     </paragraph>
     <paragraph>
      While MCTS has provided effective and even state-of-the-art decision-making in its “vanilla” form (particularly UCT [7]), it is often enhanced [1]. Some of these enhancements incorporate external knowledge into the search, whereas others are general purpose enhancements which can be applied to any domain without specific knowledge. In some cases these enhancements are crucial aspects of successful MCTS programs, for example the RAVE enhancement [8] used in champion Go [9] and Hex [10] programs. In vanilla MCTS, the only information retained from a playout is the terminal reward, and the only use for that information is to update the nodes visited during the playout. Many enhancements aim to extract more data from each playout and spread the influence of that data across more of the search tree, thus increasing the value of each playout.
     </paragraph>
     <paragraph>
      In this work we investigate the use of general purpose enhancements to improve the performance of MCTS. In some games{sup:1} a move that is good in one state may be good in other similar states, and we argue that general purpose MCTS enhancements improve the performance of the algorithm by exploiting opportunities for learning in these situations. The enhancements in this paper bootstrap the learning of whether states and actions are good or bad by using analogy with similar states and actions elsewhere in the search tree. A substantial contribution of this work is to develop a framework which formalises the correlation between states and actions, and the effects that this has on the tree and default policies of MCTS. Further, we develop and empirically investigate combination operators for MCTS enhancements, and show how we can use our framework and operators to understand, categorise and invent new enhancements. Hence we can explain the effectiveness of MCTS enhancements by understanding how information is shared between states and actions and how this information is used to improve the MCTS selection and simulation policies. Additionally we show that enhancements developed for games of perfect information (where the state is fully observable to all players and state transitions are deterministic) can also be effective in games of imperfect information (where the state is partially observable with different observations for different players, and state transitions may be stochastic).
     </paragraph>
     <paragraph>
      The framework in this paper aims to unify MCTS and its various enhancements, whereas other authors have sought to unify MCTS and related search techniques. Keller and Helmert [11] propose a framework for finite horizon Markov decision processes (i.e. single-player games). This framework can express UCT as well as other heuristic search and dynamic programming techniques. By interchanging the component parts of the methods within the framework, new methods are derived. Maes et al. [12] define a grammar over Monte Carlo search algorithms for single-player games (including UCT and Nested Monte Carlo Search [13]), and use this to evolve new algorithms. Saffidine [14] presents a framework for “best first search” methods in two-player games, which encompasses methods such as MCTS-Solver [15] and Proof-Number Search [16] and guarantees that methods expressible in this framework must converge to the minimax solution of the game.
     </paragraph>
     <paragraph>
      The idea of enhancing an algorithm to better capture and reuse information as it executes is used in a number of search and learning algorithms. The efficiency of the α–β pruning strategy in minimax search is largely dependent on the order in which actions are visited in the tree [17]. Enhancements such as the killer heuristic [18], history heuristic [19] and iterative deepening [20] use information gathered during the search to refine this ordering as the search progresses. Even α–β pruning itself can be seen as an information reuse enhancement, as it uses information gathered in one part of the tree to influence the search in other parts (specifically, to prune other parts entirely). Machine learning algorithms can also bootstrap learning through reuse. In transfer learning[21] or lifelong learning[22], the learner uses information learned from previous problems to bootstrap learning for the present problem. In multitask learning[23], the system learns to solve several problems in parallel. In both cases the system can be thought of as “learning to learn”, thus these approaches are often termed meta-learning[24]. Typically meta-learning systems work by learning reusable features or representations, or by adjusting the parameters of an underlying learning algorithm. Although the actual methods used are different, the idea of a learning system acquiring knowledge over its lifetime as it is confronted by different problems is similar to the idea of a tree search algorithm transferring knowledge from one part of the game tree to another over the “lifetime” of a single search.
     </paragraph>
     <paragraph>
      Most general purpose MCTS enhancements derive knowledge by comparing and combining simulations from different states. We show that these general purpose enhancements do not always work and are sometimes detrimental to the performance of MCTS, adding to existing observations that certain enhancements which are effective in some domains fail to provide any benefit in other domains (e.g. [25], [26]). The most effective enhancements correctly identify which states have correlated action values. This suggests that even if a general purpose enhancement is knowledge-free, there is implicit knowledge contained in the AI designer's decision of whether or not to use that enhancement.
     </paragraph>
     <paragraph>
      As well as letting us choose between existing enhancements, consideration of correlated states allows us to design entirely new enhancements. In this paper we present a new enhancement, EPisodic Information Capture and reuse (EPIC), that was designed by considering correlation between states in the card game Dou Di Zhu. Dou Di Zhu has an episodic structure, where a game consists of a sequence of somewhat independent rounds, and EPIC is designed to correlate states in analogous positions within different episodes. Many games have an episodic structure, and we demonstrate that EPIC is an effective general purpose enhancement for other games.
     </paragraph>
     <paragraph>
      Capturing information in the correct way is important, but reusing it in the correct way is equally crucial. Our framework separates reuse from capture, enabling us to study the effectiveness of different information reuse techniques. In [27] we show that the precise information reuse method has an impact on the performance of an enhancement, and in particular we show that policies designed to balance exploitation and exploration, such as ε-greedy and UCB1 [6], produce strong simulation policies. In the case of UCB1, this leads to an elegant MCTS algorithm which uses a bandit algorithm to select all moves in the playout, where in the MCTS tree the action value estimates correspond to information about a single state and in simulations the action value estimates correspond to information reused between many states. Thus the only difference between the “in tree” (selection) and “out of tree” (simulation) modes of MCTS is whether the context in which the bandit algorithm executes is specific to a single state or general across a larger collection of states.
     </paragraph>
     <paragraph>
      The structure of this paper is as follows. In Section 2 we give a brief overview of MCTS, and Section 3 introduces the definitions and notations we use throughout the paper. In Section 4 we define the ICARUS framework and show that many existing MCTS enhancements can be defined within this framework. We cast the best-known MCTS enhancements in this framework, adapting them to games of imperfect information in the process, and consider operators which allow us to combine information reuse enhancements. In Section 5 we define a new enhancement, EPisodic Information Capture and reuse (EPIC), which captures information in such a way as to exploit the episodic nature of the search tree. In Section 6 we use the ICARUS framework to identify similarities and differences between enhancements. In particular we argue that MCTS enhancements differ in two ways: how information is captured, and how the captured information is reused within the MCTS algorithm. Section 7 introduces the three games we use in this paper as experimental domains, and Section 8 empirically compares the performance in these domains of EPIC and existing enhancements from the literature, studying a wide range of combinations using our ICARUS combination operators. Finally Section 9 gives some concluding remarks and directions for future work.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Monte Carlo Tree Search (MCTS)
     </section-title>
     <section label="2.1">
      <section-title>
       The MCTS algorithm
      </section-title>
      <paragraph>
       Monte Carlo Tree Search (MCTS) is a class of decision tree search algorithms discovered independently by several authors [28], [7], [29]. The most common MCTS implementations are based on the UCT algorithm [7], although there are many different versions of the algorithm [1]. MCTS builds a search tree iteratively where on each iteration the following four steps are performed:
      </paragraph>
      <list>
       <list-item label="1.">
        Selection: The tree policy (often UCB1 [6]) is used to descend the existing search tree (the “tree search” in MCTS).
       </list-item>
       <list-item label="2.">
        Expansion: A child of the final selected node is added, if possible.
       </list-item>
       <list-item label="3.">
        Simulation: A simulation is run to estimate the outcome of the game. Typically this is done by playing random actions from the position reached during selection/expansion, until the end of the game (the “Monte Carlo” in MCTS).
       </list-item>
       <list-item label="4.">
        Backpropagation: The result of the simulation is used to update all nodes visited during selection and expansion.
       </list-item>
      </list>
      <paragraph>
       We refer collectively to the selection, expansion and simulation stages as the playout. The playout can be seen as a sequence of actions from the current (root) state to a terminal state.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Information Set MCTS
      </section-title>
      <paragraph>
       Information Set MCTS (ISMCTS) is a variant of MCTS that handles imperfect information [30], [31]. This is achieved by building a tree of information sets (sets of states indistinguishable from one player's view point) rather than individual states, and dealing with the increased branching factor by restricting each MCTS iteration to a random determinization (a state sampled at random from the current information set). In this paper we use the MO-ISMCTS version of the algorithm, which deals with games that have partially observable moves by constructing a separate search tree (a “projection” of the underlying game tree) to reflect each player's observation of the game.
      </paragraph>
      <paragraph>
       Each ISMCTS iteration uses a different determinization, and restricts selection and expansion to actions legal in that determinization. This leads to the subset-armed bandit problem: the set of children available for selection can differ between visits to the same node. To avoid over-exploration of “rare” children (corresponding to actions that are legal in relatively few determinizations), we use as the number of trials in the UCB1 formula the number of times the action was available for selection, rather than the number of times the parent node was visited [30].
      </paragraph>
      <paragraph>
       ISMCTS is an effective algorithm for handling imperfect information, producing strong play and outperforming other determinization-based approaches [30]. In particular it overcomes the problem of strategy fusion, where a simpler approach incorrectly assumes it can tailor its future strategy to the opponent's private information [32], [33]. MCTS approaches combined with determinization have proven successful in games such as Klondike Solitaire [34], Skat [35] and Kriegspiel [36], as well as in General Game Playing for games of imperfect information [37].
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Definitions and notation
     </section-title>
     <paragraph>
      For a set X, a sequence over X is written as {a mathematical formula}〈x1,…,xn〉 for {a mathematical formula}xi∈X. The empty sequence is denoted 〈〉. The set of all sequences over X is denoted {a mathematical formula}X⁎. The concatenation of two sequences {a mathematical formula}x=〈x1,…,xn〉 and {a mathematical formula}y=〈y1,…,yn〉 is {a mathematical formula}x{an inline-figure}y=〈x1,…,xn,y1,…,yn〉. We also use the concatenation operator for prepending or appending single elements to a sequence, for example {a mathematical formula}x{an inline-figure}xn+1=〈x1,…,xn,xn+1〉 for {a mathematical formula}xn+1∈X.
     </paragraph>
     <paragraph>
      Let X be a set and let ∼ be an equivalence relation on X. Then {a mathematical formula}[x]∼ is the ∼-class of {a mathematical formula}x∈X, and {a mathematical formula}X/∼ is the set of all ∼-classes.
     </paragraph>
     <paragraph>
      We now describe our terminology and notation for games. The notation is described in more detail in [30], and more detail on the concepts behind it can be found in [38] or other standard textbooks on game theory.
     </paragraph>
     <paragraph label="Definition 1">
      A game is defined by the following elements:
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}(S,Λ)is a finite nonempty directed graph, with S the set of states and Λ the set of state transitions;
      </list-item>
      <list-item label="•">
       {a mathematical formula}s0∈Sis the initial state;
      </list-item>
      <list-item label="•">
       {a mathematical formula}κ∈Nis the number of players;
      </list-item>
      <list-item label="•">
       {a mathematical formula}μ:ST→Rκis the utility function, where{a mathematical formula}ST⊆Sis the set of terminal states;
      </list-item>
      <list-item label="•">
       {a mathematical formula}ρ:S→{0,1,…,κ}defines the player about to act in each state;
      </list-item>
      <list-item label="•">
       {a mathematical formula}π0:Λ→[0,1], where for all{a mathematical formula}r∈Swith{a mathematical formula}ρ(r)=0we have{a mathematical formula}∑s:(r,s)∈Λπ0(r,s)=1, is the environment policy;
      </list-item>
      <list-item label="•">
       {a mathematical formula}∼i, for each player{a mathematical formula}i=0,1,…,κ, is an equivalence relation on S, whose classes are player i's information sets;
      </list-item>
      <list-item label="•">
       {a mathematical formula}⌣i, for each player{a mathematical formula}i=0,1,…,κ, is an equivalence relation on Λ, whose classes are moves as observed by player i, such that for all{a mathematical formula}q,r,s∈S,{a mathematical formula}(q,r)⌣ρ(q)(q,s)implies{a mathematical formula}r=s.
      </list-item>
     </list>
     <paragraph>
      A game can be described as a sequential decision problem, where the players collectively choose a path through {a mathematical formula}(S,Λ) from {a mathematical formula}s0 to a terminal state. When the current state is {a mathematical formula}st, player {a mathematical formula}ρ(st) chooses an edge {a mathematical formula}(st,st+1) and the process continues from state {a mathematical formula}st+1. If {a mathematical formula}ρ(st)=0 then the edge is instead selected according to the probability distribution induced by {a mathematical formula}π0; this models chance events such as dice rolls or card deals. In practice the players do not choose edges but actions: these are moves from the point of view of the moving player, and represent sets of analogous edges from different states (e.g. the set of edges that correspond to playing the card Q♠ from all states in which that is legal).
     </paragraph>
     <paragraph>
      In a game of imperfect information, players do not observe the current state but observe the information set that contains it. Likewise they do not observe state transitions or actions but moves. (Note the distinction between state transitions, actions and moves in this paper: a player chooses an action, which induces a state transition, and the other players observe a move.) An information set consists of all states that are indistinguishable from the player's point of view; a move consists of all actions that are indistinguishable from the player's point of view. Thus a player's choices of action can depend only on the information sets and moves that he observes, not on the underlying states and actions.
     </paragraph>
     <paragraph label="Definition 2">
      Consider a game Γ, a state s and a player i. The set of legal moves from state s from player i's point of view is{a mathematical formula}The set of all moves from player i's point of view is the set of all moves legal in at least one state:{a mathematical formula}The set of all moves is the set of all moves from all players' points of view:{a mathematical formula}The set of legal actions from s is{a mathematical formula}i.e. the set of legal moves from the point of view of the player about to act. The set of all actions is the set of all actions legal in at least one state:{a mathematical formula}Let{a mathematical formula}B={(s,a):s∈S,a∈A(s)}, the set of all pairs of states and their legal actions. The transition function for Γ is the function{a mathematical formula}f:B→Ssuch that given{a mathematical formula}s∈S, we have that{a mathematical formula}∀a∈A(s),{a mathematical formula}(s,s′)∈a⇒f(s,a)=s′. In other words:{a mathematical formula}f(s,a)is the state reached by starting from s and traversing the edge corresponding to a;{a mathematical formula}f(s,a)is the state resulting from performing action a in state s.
     </paragraph>
     <paragraph label="Definition 3">
      An action history{sup:2}from state s is a sequence of actions{a mathematical formula}〈a1,…,an〉∈A⁎, such that{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}Denote the set of all action histories from s by{a mathematical formula}H(s). Extend the transition function f to operate on action histories by defining{a mathematical formula}{a mathematical formula}An action history h is terminal if{a mathematical formula}f(s,h)is a terminal state. Denote the set of terminal action histories from s by{a mathematical formula}HT(s).
     </paragraph>
     <paragraph label="Definition 4">
      A move history for player i from state s is a sequence of moves from player i's point of view,{a mathematical formula}〈[a1]⌣i,…,[an]⌣i〉∈Mi⁎, where{a mathematical formula}〈a1,…,an〉is an action history from s. Denote the set of all move histories for player i from s by{a mathematical formula}Hi⌣(s), and the set of all move histories for all players by{a mathematical formula}H⌣(s). If{a mathematical formula}h=〈a1,…,an〉is an action history then the corresponding move history from player i's point of view is denoted{a mathematical formula}[h]⌣i. Let{a mathematical formula}ρ=ρ(f(s,〈a1,…,an−1〉)), so ρ is the player who played the last action{a mathematical formula}anin the history. Then the move history from player ρ's point of view is denoted by omission of the player number, i.e.{a mathematical formula}[h]⌣.
     </paragraph>
     <paragraph>
      Tree search algorithms operate on trees of histories. The history at a node is precisely the sequence of moves or actions that label the edges from the root to that node. Perfect information MCTS operates on trees of action histories, whereas MO-ISMCTS operates on trees of move histories.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Information Capture And ReUse Strategies (ICARUSes)
     </section-title>
     <paragraph>
      An Information Capture And ReUse Strategy (ICARUS) is an enhancement to MCTS that collects information from visits to one area of the game tree and uses that information to inform the future policy in other areas. The ICARUS framework introduced in this section allows us to define and analyse such enhancements and their combinations in an instructive, formal and consistent way. Furthermore, the framework is generic enough to be able to express any kind of information reuse enhancement (for example consulting an oracle of arbitrary complexity is permitted), but imposes a structure on how information is captured and used. This allows the structure of different enhancements to be easily compared, and provides useful pointers towards the design of future enhancements.
     </paragraph>
     <section label="4.1">
      <section-title>
       Defining ICARUSes
      </section-title>
      <paragraph>
       The sharing of information between different parts of the tree is facilitated by records. These can be any objects. During the search, each record has a piece of information associated. The piece of information can also be any object; for example, it may be a tuple of numbers representing rewards and visit counts. The ICARUS defines three functions: the policy function specifying how the information is used during each MCTS playout, the capture function specifying which records are to be updated in response to the playout, and the backpropagation function specifying how each record's information is updated. This is similar to reinforcement learning, where the policy function is to be optimised, playouts provide a performance measure and the capture and backpropagation functions define a learning mechanism. Depending on the enhancement, records can be updated for different reasons: for example some records may be updated because they were selected, and others because they were available for selection but not actually selected. We use capture contexts to communicate this between the capture function and the backpropagation function.
      </paragraph>
      <paragraph label="Definition 5">
       Given a game as defined in Section3, an information capture and reuse strategy (ICARUS) is a 7-tuple{a mathematical formula}(R,Θ,θinitial,α,Ψ,ξ,ω)where
      </paragraph>
      <list>
       <list-item label="1.">
        R is a nonempty set of records. The elements of R can be any objects.
       </list-item>
       <list-item label="2.">
        Θ is a nonempty set, the information domain. The elements of Θ can be any objects.
       </list-item>
       <list-item label="3.">
        {a mathematical formula}θinitial:R→Θis the initial information function, which maps each record to a piece of information.
       </list-item>
       <list-item label="4.">
        {a mathematical formula}α:M⁎×(R→Θ)×2A→(A→[0,1])is the policy function. This function takes three arguments (the current move history, the current mapping of records to information, and the legal action set for the current state) and returns a probability distribution over the action set. The same function α is used during selection and simulation phases of the playout.
       </list-item>
       <list-item label="5.">
        Ψ is a nonempty set of capture contexts. The elements of Ψ can be any objects, and are used to communicate contextual information between ξ and ω defined below.
       </list-item>
       <list-item label="6.">
        {a mathematical formula}ξ:S×M⁎→(R×Ψ)⁎is the capture function. This function takes two arguments (the root game state and the current move history) and maps them to a sequence of (record, capture context) pairs which are to be updated following a playout. The capture function returns a sequence rather than a set to allow the same record to be updated more than once for the playout, and to specify the order of updates with different contexts in cases where this matters.
       </list-item>
       <list-item label="7.">
        {a mathematical formula}ω:Θ×Ψ×Rκ→Θis the backpropagation function. This function takes three arguments (the current information for a record, the capture context specified by the capture function, and the reward vector from the simulation) and returns the new information for the record following a playout.
       </list-item>
      </list>
      <paragraph>
       Algorithm 1 shows an MCTS algorithm using ICARUS to choose the best action from an information set {a mathematical formula}Iroot. The algorithm begins by initialising the information associated with each record (lines 2–4); however, a practical implementation would initialise these values lazily as and when they are needed. Each iteration begins at the root node corresponding to the empty history (line 7), and samples a determinization (state) {a mathematical formula}sroot from the root information set (line 8) which becomes the current state s for this iteration (line 9).
      </paragraph>
      <paragraph>
       Each step of the playout uses the policy function α to choose an action a, depending on the current move history {a mathematical formula}[h]⌣ρ(s) for the player about to act from state s, the current information mapping θ, and the set of available actions {a mathematical formula}A(s) (line 11). The current history h is updated by appending a, and the current state s is updated by applying a.
      </paragraph>
      <paragraph>
       After the playout has reached a terminal state, the capture function is applied to the root determinization {a mathematical formula}sroot and the terminal history h to obtain the sequence of (record, context) pairs to be updated (line 16). For each of these pairs, the backpropagation function ω is used to update the information associated with the record (line 17).
      </paragraph>
      <paragraph>
       The experimental domains in this paper are games of imperfect information, thus Algorithm 1 is designed to handle imperfect information using the approach of Information Set MCTS [30]. However it is equally applicable to games of perfect information. In this case the information set {a mathematical formula}Iroot is a singleton {a mathematical formula}{sroot} and line 8 can be omitted.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Baseline ICARUS definition
      </section-title>
      <paragraph>
       Specification 1 describes the baseline ICARUS definition used by an unenhanced search algorithm, defining the functions used in Algorithm 1. The resulting algorithm is equivalent to UCT [7] in the perfect information case and MO-ISMCTS with the UCB1 selection policy [30] in the imperfect information case. The algorithm uses reward vectors and assumes that each player tries to maximise his own reward in a {a mathematical formula}maxn fashion [39], [40], thus the algorithm can handle games with {a mathematical formula}κ&gt;2 players as well as single-player and two-player games.
      </paragraph>
      <paragraph>
       Each history has its own record (Base-1), and the information associated with a record is a total reward, a number of visits and an availability count (Base-2, Base-3). The policy is defined to use the subset-armed UCB1 algorithm (Base-4). During expansion all unexpanded actions have {a mathematical formula}n=0 and thus UCB1 value ∞, and so the policy chooses between them uniformly. Similarly during simulation, all actions have UCB1 value ∞ and so the simulation policy is uniform random. The capture function specifies that the records to be updated during backpropagation are those that were selected, and those that were available to be selected due to being compatible with the current determinization; this is restricted to the portion of the playout corresponding to selection and expansion, i.e. the first {a mathematical formula}te actions (Base-6). These two collections of records are labelled with contexts {a mathematical formula}ψvisit and {a mathematical formula}ψavail respectively (Base-5). Selected records have their rewards, visits and availabilities updated in the natural way: the simulation reward is added to the record's total reward, and the visit and availability counts are incremented by 1. Available records have their availability count incremented by 1, with reward and visit count remaining unchanged (Base-7).
      </paragraph>
      <paragraph>
       Many ICARUSes apply different policies during selection, expansion and simulation. Let {a mathematical formula}θnbase denote the visit count component of {a mathematical formula}θbase, i.e. {a mathematical formula}θnbase([h]⌣) denotes the number of visits to history {a mathematical formula}[h]⌣. A history h with an available action set {a mathematical formula}As is said to be
      </paragraph>
      <list>
       <list-item label="•">
        a selection node if {a mathematical formula}θnbase([h]⌣)&gt;0 and {a mathematical formula}θnbase([h{an inline-figure}a]⌣)&gt;0 for all {a mathematical formula}a∈As;
       </list-item>
       <list-item label="•">
        an expansion node if {a mathematical formula}θnbase([h]⌣)&gt;0 but {a mathematical formula}θnbase([h{an inline-figure}a]⌣)=0 for at least one {a mathematical formula}a∈As;
       </list-item>
       <list-item label="•">
        a simulation node if {a mathematical formula}θnbase([h]⌣)=0.
       </list-item>
      </list>
      <paragraph>
       It is important to note that when this terminology is used in the definitions of ICARUSes, it always relates to the baseline statistics and not to the information maintained by the ICARUS itself.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Enhancements in the ICARUS framework
      </section-title>
      <paragraph>
       This section casts some well-known information reuse enhancements from the literature into the ICARUS framework.
      </paragraph>
      <section label="4.3.1">
       <section-title>
        All moves as first (AMAF)
       </section-title>
       <paragraph>
        The all moves as first (AMAF) heuristic was introduced by Brügmann [41] in the context of Monte Carlo methods for Go, and was first combined with MCTS by Gelly and Silver [8] and independently by Drake and Uurtamo [42]. The underlying idea is that the value of an action is somewhat independent of the time at which it is played. This time independence is particularly true for games with pieces that rarely or never move once played, such as Go and Hex. AMAF and its variants have proven highly successful in these [3], [10] and other similar games. AMAF updates statistics for each action in the playout not just at the point when that action was played, but also at all earlier points when the action could legally have been played.
       </paragraph>
       <paragraph>
        Specification 2 formulates AMAF in the ICARUS framework. Each history has its own record (AMAF-1), and the information associated with a record is a total reward and a number of visits (AMAF-2, AMAF-3). The policy uses a UCB1 formula based on the AMAF information (AMAF-4), here using as the number of trials the sum of visit counts for all currently available actions. The capture function specifies that the nodes to be updated are those siblings of nodes visited during tree descent that correspond to actions played later in the playout (AMAF-6). This is the key property of the AMAF algorithm. Backpropagation updates the rewards and visits in the natural way (AMAF-7), and does not require any contextual information (AMAF-5).
       </paragraph>
       <paragraph>
        One well-known variant of AMAF is rapid action value estimation (RAVE)[8], [3], in which the influence of the AMAF value decays the more a node is visited. In Section 4.4 we define composition operators on ICARUSes, and express RAVE as a composition of baseline and AMAF ICARUSes.
       </paragraph>
      </section>
      <section label="4.3.2">
       <section-title>
        Move-average sampling technique (MAST)
       </section-title>
       <paragraph>
        Move-average sampling technique (MAST){sup:3} was introduced by Finnsson and Björnsson [43] and used in their CadiaPlayer general game player [44]. The idea is to maintain average reward statistics for each action independently of where it occurs in the game tree, and use these statistics to bias the simulation policy.
       </paragraph>
       <paragraph>
        MAST is defined in Specification 3. There is a record for each combination of an action and a player who plays that action (MAST-1). The information associated with a record is a total (scalar) reward and a visit count (MAST-2, MAST-3). The policy selects actions according to a Gibbs distribution, using the average reward calculated from the total reward and visit count (MAST-4). Backpropagation updates the records associated with the actions played during the playout (MAST-6), with the player who played each action as contextual information (MAST-5). The total reward and number of visits are updated in the natural way (MAST-7). If the same (action, player) pair appears more than once in the playout, it is updated more than once during backpropagation.
       </paragraph>
       <paragraph>
        This formulation of MAST applies the same policy throughout the playout, whereas [43] applies the Gibbs policy during expansion and simulation only. This behaviour can be implemented within the ICARUS framework by use of composition operators (Section 4.4).
       </paragraph>
       <paragraph>
        In its original formulation, MAST uses a policy based on a Gibbs distribution. Tak et al. [45] propose instead using an ε-greedy policy, i.e. replacing the policy function in Specification 3 with{a mathematical formula} for a constant ε. With probability ε this policy chooses uniformly over all available actions; with probability {a mathematical formula}1−ε it chooses uniformly over the actions whose average value is maximal.
       </paragraph>
       <paragraph>
        Another possibility is to use a roulette wheel policy, in which the probability for each move is proportional to its average reward:{a mathematical formula}
       </paragraph>
       <paragraph>
        Yet another possibility is to use a bandit policy such as UCB1, requiring us to keep track of availability counts for each action and update these during backpropagation.
       </paragraph>
      </section>
      <section label="4.3.3">
       <section-title>
        Variants of MAST
       </section-title>
       <paragraph>
        Finnsson and Björnsson [46] describe a variant of MAST called tree-only MAST (TO-MAST), in which only statistics for the actions played during selection and expansion (i.e. not during simulation) are updated. This can be defined by modifying the capture function of Specification 3:{a mathematical formula}
       </paragraph>
       <paragraph>
        Finnsson and Björnsson [46] describe two refinements of MAST to enable embedding of domain specific knowledge. In predicate-average sampling technique (PAST), states are labelled using a list of predicates; instead of maintaining average rewards for actions, rewards are maintained for (predicate, action) pairs consisting of a predicate that holds in a state and the action played from that state. PAST can be represented in the ICARUS framework by modifying Specification 3, including the predicate as an element of the record tuple and modifying the policy and capture functions to take predicates into account.
       </paragraph>
       <paragraph>
        The second refinement is features-to-action sampling technique (FAST). This uses the {a mathematical formula}TD(λ) temporal difference learning algorithm to learn a value function for actions, both offline before the search begins and online based on the MCTS playouts. In the ICARUS framework, the values learned offline can be encoded in the initial information function {a mathematical formula}θinitial, and the online learning by embedding {a mathematical formula}TD(λ) in the backpropagation function ω.
       </paragraph>
      </section>
      <section label="4.3.4">
       <section-title>
        Last good reply (LGR)
       </section-title>
       <paragraph>
        Last good reply (LGR) is a simulation policy introduced by Drake [47]. When playing a game, each action can be thought of as a reply to the opponent's previous move. If the replying player goes on to win the game, this gives us some evidence that the reply was good. LGR records good replies from MCTS playouts; during simulation, if a good reply is recorded for the previous move then it is played deterministically. LGR has been shown to improve the performance of MCTS for Go [47], [48], Havannah [49] and General Game Playing [45].
       </paragraph>
       <paragraph>
        Specification 4 gives LGR as an ICARUS. Each record specifies a move to be replied to, and the player making the reply (LGR-1). The information associated with a record is the last good action played in reply to that move by that player, or {a mathematical formula}⊥∉A if no reply has yet been recorded (LGR-2, LGR-3). The policy examines the most recent move {a mathematical formula}[at]⌣ρt from the point of view of the player about to act {a mathematical formula}ρt. If a reply has been recorded, and that reply is compatible with the current determinization, then it is played. Otherwise, a legal action is chosen uniformly at random (LGR-4). During backpropagation, the records updated are those corresponding to the actions in the playout, each action observed from the point of view of the player immediately following it (LGR-6). The context specifies the action with which that player replied, as well as the identity of the player (LGR-5). If the player won the simulated game (i.e. achieved a reward greater than zero), the action is recorded as the last good reply; if not, the existing information is retained (LGR-7).
       </paragraph>
       <paragraph>
        In [47], the reply information is used only during simulation, whereas Specification 4 has it used for the entire playout. This is likely to be very weak. However we define it in this way so that the stage at which the reply information is used can be specified naturally by composition operators (Section 4.4) rather than as a part of the ICARUS itself.
       </paragraph>
       <paragraph>
        Baier and Drake [48] describe a variant of LGR called last good reply with forgetting (LGRF), in which replies that led to a loss are deleted from the reply table. Specification 4 can be modified to describe LGRF simply by modifying the backpropagation function:{a mathematical formula}
       </paragraph>
      </section>
      <section label="4.3.5">
       n-Gram average sampling technique (NAST)
       <paragraph>
        n-Gram average sampling technique (NAST) was introduced by Powley et al. [27], based on previous work by Stankiewicz et al. [49] and Tak et al. [45]. NAST generalises the notion of MAST: instead of learning values for single moves, NAST learns values for sequences of consecutive moves (indeed, MAST can be thought of as the {a mathematical formula}N=1 case for NAST).
       </paragraph>
       <paragraph>
        NAST is defined in Specification 5. Each record is an n-gram, i.e. a sequence of n moves (NAST-1). Note that n is a parameter here; Specification 5 defines a family of enhancements for {a mathematical formula}n=1,2,3,…. The information associated with a record is the total reward and number of visits (NAST-2, NAST-3). The policy uses these to select actions according to UCB1 (NAST-4). Backpropagation updates the records associated with each sequence of n moves in the playout (NAST-6), with the player who played the last move in the sequence as contextual information (NAST-5). The total reward and number of visits are updated in the natural way (NAST-7). Note that NAST with {a mathematical formula}n=1 is equivalent to MAST (Section 4.3.2) with the UCB1 policy.
       </paragraph>
       <paragraph>
        Stankiewicz et al. [49] demonstrate the effectiveness of n-gram techniques in MCTS for the game Havannah, and Tak et al. [45] show that similar techniques work in a General Game Playing setting. In [50] we show that NAST works for the three imperfect information games studied in the present paper (Section 7), with {a mathematical formula}n=2 typically giving the strongest performance.
       </paragraph>
      </section>
      <section label="4.3.6">
       <section-title>
        Other examples
       </section-title>
       <paragraph>
        The literature contains many other examples of MCTS enhancements that involve either using information from external sources or capturing and reusing information within the search. All such approaches designed to date can be represented in the ICARUS framework. We chose AMAF, MAST, LGR and NAST as examples because they capture and reuse information in significantly different ways, whereas many enhancements are modifications of existing ones (for example the different AMAF variants described in [51]). Furthermore, these four enhancements have led to significant increases in the power of the MCTS algorithm for diverse application domains. This section briefly describes how some other enhancements from the literature can be defined within the ICARUS framework.
       </paragraph>
       <paragraph>
        Chaslot et al. [52] introduce progressive bias and progressive unpruning, which use a heuristic value function to bias selection and restrict expansion respectively. In the ICARUS framework this can be achieved by encoding the heuristic in the initial information function {a mathematical formula}θinitial and modifying the policy function α appropriately.
       </paragraph>
       <paragraph>
        Nijssen and Winands [53] propose a modification of progressive bias called progressive history, which replaces the heuristic function with values extracted from simulations. Within the ICARUS framework this is similar to progressive bias, except that the information is updated by the backpropagation function ω instead of being initialised heuristically.
       </paragraph>
       <paragraph>
        Rimmel and Teytaud [54] introduce contextual MCTS, which works by mapping each terminal history to several “tiles”, where a tile corresponds to a pair of (not necessarily consecutive) actions played by the same player. During backpropagation the average values of tiles are updated, and these values are used to bias simulations. When contextual MCTS is encoded as an ICARUS, the tiles become records and the policy and backpropagation functions are defined in the natural way.
       </paragraph>
       <paragraph>
        The MCTS-Solver enhancement introduced by Winands et al. [15], [55] works by backpropagating game-theoretic values through the tree. A terminal state is always known to be a win or a loss; at a decision node for player p, if one of the children is a known win then the node itself is a known win; if all of the children are known losses then the node itself is a known loss. This can be implemented by allowing nodes to take reward values of +∞ and −∞ to represent known wins and losses respectively, and modifying backpropagation to handle these values appropriately.
       </paragraph>
      </section>
     </section>
     <section label="4.4">
      <section-title>
       Combining ICARUSes
      </section-title>
      <paragraph>
       For a particular domain, the most effective information reuse approach is often a combination of other approaches. Thus it is useful to have well-defined ways to combine ICARUSes.
      </paragraph>
      <paragraph>
       In this paper we consider three ways of combining ICARUSes. The first is sequential combination. For two ICARUSes {a mathematical formula}I1=(R1,Θ1,θinitial1,α1,Ψ1,ξ1,ω1) and {a mathematical formula}I2=(R2,Θ2,θinitial2,α2,Ψ2,ξ2,ω2), the combination {a mathematical formula}I1▹I2 is defined in Specification 6. Here ⊔ denotes disjoint union: the sets are assumed to be disjoint, by relabelling elements if necessary. Each enhancement maintains its own records and information; the policy functions are combined so that {a mathematical formula}I1▹I2 uses the policy from {a mathematical formula}I1 during selection and expansion, and the policy from {a mathematical formula}I2 during simulation. Selection and expansion nodes are defined in Section 4.2.
      </paragraph>
      <paragraph>
       The second way of combining enhancements is linear combination. For two ICARUSes {a mathematical formula}I1 and {a mathematical formula}I2 as above, and a function {a mathematical formula}λ:Θbase→[0,1] (the mixing coefficient, which is a function of the information for the baseline ICARUS as defined in Specification 1), the combination {a mathematical formula}λI1+(1−λ)I2 is defined as in Specification 6 with the exception of the policy function:{a mathematical formula} We can generalise this to define any convex combination of two or more enhancements in the natural way.
      </paragraph>
      <paragraph>
       The third combination type is maxilinear combination. This is valid only for ICARUSes where the policy function has the form{a mathematical formula} for some function {a mathematical formula}v:A→R. For two ICARUSes {a mathematical formula}I1 and {a mathematical formula}I2 satisfying this condition with functions {a mathematical formula}v1 and {a mathematical formula}v2 respectively, and a function {a mathematical formula}λ:Θbase→[0,1], the combination {a mathematical formula}λI1⊕(1−λ)I2 is defined as in Specification 6 with the exception of the policy function:{a mathematical formula}
      </paragraph>
      <paragraph>
       For example, this allows us to define RAVE [8] as{a mathematical formula} where{a mathematical formula} for some constant k (which specifies the number of visits, i.e. the value of n, for which {a mathematical formula}λRAVE=0.5). Again, maxilinear combination can be generalised to combine more than two ICARUSes.
      </paragraph>
      <paragraph>
       All ways of combining ICARUSes make use of information from the baseline definition (Section 4.2) in some way, whether to determine the current stage (selection, expansion or simulation) of the playout or to vary the combination coefficient. Thus for a combination to make sense, it must incorporate the baseline ICARUS.
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Convergence properties
      </section-title>
      <paragraph>
       Kocsis and Szepesvári [7] prove that, for games of perfect information, UCT converges on the optimal move in the limit. That is, as the number of iterations tends to infinity, the probability of selecting a suboptimal move tends to zero.
      </paragraph>
      <paragraph label="Definition 6">
       Consider a history h, which when applied to the initial game state{a mathematical formula}s0gives a state{a mathematical formula}f(s0,h)=swith legal actions{a mathematical formula}As. Let{a mathematical formula}As⁎⊆Asbe the set of optimal actions from state s. An ICARUS I with policy α is convergent if, for all{a mathematical formula}a∈As∖As⁎, we have{a mathematical formula}That is, for every suboptimal action a, the probability assigned to a by the playout policy tends to zero in the limit.
      </paragraph>
      <paragraph>
       For the baseline ICARUS (Specification 1) applied to a game of perfect information, we have the following two results:
      </paragraph>
      <paragraph label="Lemma 1">
       The baseline ICARUS is convergent.
      </paragraph>
      <paragraph label="Proof">
       It follows immediately from [7, Theorem 5] that (16) holds for {a mathematical formula}α=αbase.  □
      </paragraph>
      <paragraph label="Lemma 2">
       There exists an iteration number t such that, after t iterations, h is a selection node.
      </paragraph>
      <paragraph label="Proof">
       From [7, Theorem 3], there exists a constant k such that, after t iterations, the number of visits to h is at least {a mathematical formula}⌈klog⁡t⌉. In particular there is a t such that {a mathematical formula}⌈klog⁡t⌉≥2, which implies that h is expanded and is now a selection node.  □
      </paragraph>
      <paragraph>
       From these results, we can easily show that certain combinations of ICARUS are convergent:
      </paragraph>
      <paragraph label="Theorem 1">
       Let{a mathematical formula}I1and{a mathematical formula}I2be ICARUSes such that{a mathematical formula}I1is convergent. Let{a mathematical formula}λ:Θbase→[0,1]such that{a mathematical formula}λ(q,n,m)→0as{a mathematical formula}n→∞. Then the following ICARUSes are convergent:
      </paragraph>
      <list>
       <list-item label="(i)">
        {a mathematical formula}λI2+(1−λ)I1;
       </list-item>
       <list-item label="(ii)">
        {a mathematical formula}λI2⊕(1−λ)I1(if defined);
       </list-item>
       <list-item label="(iii)">
        {a mathematical formula}I1▹I2.
       </list-item>
      </list>
      <paragraph label="Proof">
       The convergence of (i) and (ii) follows from the fact that λ tends to 0 as the number of visits to a node tends to infinity. This ensures that {a mathematical formula}I1 dominates in the limit, so the combination inherits its convergent behaviour.The convergence of (iii) follows from Lemma 2: after some finite number of iterations, all nodes are selection nodes (recall from Definition 1 that we require games to have a finite number of states). At this point, {a mathematical formula}I1▹I2 behaves identically to {a mathematical formula}I1 and thus converges.  □
      </paragraph>
      <paragraph>
       It follows from Lemma 1 and Theorem 1(ii) that RAVE (14) converges. The ICARUS combinations used in the experiments in Section 8 (Table 1) all have the form {a mathematical formula}I1▹I2 for {a mathematical formula}I1∈{IBaseline,IRAVE}, and so also converge.
      </paragraph>
      <paragraph>
       Note that these convergence results only apply to games of perfect information. For games of imperfect information, we have no proof equivalent to that of Kocsis and Szepesvári [7] that ISMCTS converges. Indeed, we have some empirical evidence that ISMCTS does not converge in the sense of Definition 6, either oscillating between several policies or settling on a policy which does not form part of a Nash equilibrium. Nevertheless, designing enhancements that converge in the perfect information case seems to be a useful way to obtain plausible play across all domains.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      EPisodic Information Capture and reuse (EPIC)
     </section-title>
     <paragraph>
      Many games are episodic in nature: multiplayer games have a sequence of opponents' turns; ladder games such as Dou Di Zhu [31], President and Cheat [56] have a sequence of moves until a “reset” action occurs; strategic board and card games such as Lord Of The Rings: The Confrontation [30] and Magic: The Gathering [57] have compound turns consisting of several individual decisions.
     </paragraph>
     <paragraph>
      In this section we introduce EPisodic Information Capture and reuse (EPIC), an enhancement designed within the ICARUS framework. The unique feature of EPIC is how information is captured, i.e. which states are considered to be correlated. We consider a game to be divided into a number of time windows called episodes, and share information between states that correspond to the same position in different episodes. That is, states reached by the same sequence of actions from the beginning of their respective episodes, but where the starting points of those episodes may be different. The aim of information capture and reuse is to exploit the correlations between the values of nodes in different parts of the game tree. EPIC is designed to exploit the correlation between subtrees rather than individual nodes.
     </paragraph>
     <paragraph>
      If the episodes truly are independent, this implies that the strength of a policy for a particular episode does not depend on the context of where that episode occurs in the game. Thus strong play overall can be achieved by constructing a good policy for each episode, and combining these policies to obtain a policy for the full game. The fact that the same episode occurs in several different parts of the game tree implies that a naïve tree search algorithm must rediscover the strong episode policy many times. EPIC aims to discover the episode policy only once, and reapply it throughout the game tree.
     </paragraph>
     <paragraph>
      The assumption that episodes are independent of context may be reasonable but is never strictly true in real games. In this paper we combine EPIC with the baseline player, with EPIC used only as a simulation policy. This ensures that the baseline tree policy can tailor itself to the context of the current episode if that context matters, whilst the simulation policy that uses episode information but ignores context is still likely to be much stronger than a random policy.
     </paragraph>
     <paragraph>
      The idea of episodes is not specific to any particular game, but it is also not universal. Games such as Chess and Go do not have a natural episodic structure, or rather the highly spatial nature of these games means that a purely temporal notion of episode does not make sense. However, even for these games, notions such as combinations in Chess [58] and joseki or tesuji in Go [59], [60] are a type of spatial episode. In this paper we will consider only temporal episodes, consisting of consecutive game turns. Nevertheless, a spatially episodic nature could conceivably be exploited by enhancements similar to EPIC.
     </paragraph>
     <section label="5.1">
      <section-title>
       Definition of EPIC
      </section-title>
      <paragraph>
       Although episodes do not feature in the formal definition of a game given in Section 3, the division into episodes is usually highly intuitive when it exists, for example identifying the start of a new round or hand in a card game or a particular event happening such as a piece being captured. In other words, it is a piece of domain knowledge which does not require expert insight into the game. In most cases the episode information can be read directly from an implementation's representation of the game state.
      </paragraph>
      <paragraph>
       We now introduce some notation for dealing with episodes. Let E be a finite nonempty set of episode labels. Define {a mathematical formula}e:S→E∪{″}, the episode function. The element {a mathematical formula}″∉E is the continuation label.
      </paragraph>
      <paragraph>
       Consider a game Γ. An episode of Γ is a subtree of Γ's game tree such that
      </paragraph>
      <list>
       <list-item label="1.">
        for the subtree's root node {a mathematical formula}sr we have {a mathematical formula}e(sr)∈E;
       </list-item>
       <list-item label="2.">
        for all leaf nodes {a mathematical formula}sl of the subtree, either {a mathematical formula}e(sl)∈E or {a mathematical formula}sl is a terminal state;
       </list-item>
       <list-item label="3.">
        for all other nodes s we have {a mathematical formula}e(s)=″.
       </list-item>
      </list>
      <paragraph>
       If the initial state has episode label in E then the episodes partition the game tree, as illustrated in Fig. 1.
      </paragraph>
      <paragraph>
       The position-in-episode of a history {a mathematical formula}〈a1,…,at〉∈A⁎ is the pair{a mathematical formula} where {a mathematical formula}si=f(s0,〈a1,…,ai〉) and i is maximal such that {a mathematical formula}e(si)≠″. The position-in-episode specifies the label of the current episode and the suffix of the history restricted to that episode. If a state has a position-in-episode of {a mathematical formula}(e1,〈a1,…,at〉), then that state can be reached by starting from some state with episode label {a mathematical formula}e1 and applying actions {a mathematical formula}a1,…,at. In particular if {a mathematical formula}e(s)≠″, the position-in-episode of state s is {a mathematical formula}(e(s),〈〉). The two circled nodes in Fig. 1 have the same position-in-episode. The position-in-episode of a move history is defined similarly to that of a state. Positions-in-episode are always defined relative to the initial state {a mathematical formula}s0 of the game, regardless of the current state.
      </paragraph>
      <paragraph>
       Conceptually an episode should be somewhat independent of its context: when episodes with the same root label appear in different parts of the game tree, they should look similar and have similar outcomes for all players. In other words, if two different histories have the same positions-in-episode, they should have similar rewards. This statement is deliberately vague: the assignment of episode labels to states is a decision to be made when designing the AI agent rather than a part of the formal game definition. Examples of episode functions for our experimental domains are given in Section 7.
      </paragraph>
      <paragraph>
       Specification 7 defines EPIC with game specific episodes as an ICARUS. The records used by EPIC are the positions-in-episode (EPIC-1), each of which has the standard ISMCTS information of total reward, visit count and availability count (EPIC-2, EPIC-3). The positions-in-episode for a particular episode label can be organised into a tree structure. Each history is mapped to its position-in-episode. If EPIC is combined with the baseline algorithm using sequential combination then during simulation, subset-armed UCB1 selection is applied according to the current position-in-episode (EPIC-4): effectively this means that the simulation policy for the overall search is provided by the tree policy in the episode trees. Rewards are backpropagated as in the baseline case, but in the episode trees rather than the full tree (EPIC-5, EPIC-6, EPIC-7).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Comparing ICARUSes
     </section-title>
     <paragraph>
      Having a common notation for information reuse enhancements provides a tool for their analysis and comparison. We can identify common themes that occur in several enhancements, easily see which enhancements deviate from them, and use them as building blocks to define new enhancements. For example, we can make the following observations from Specification 1, Specification 2, Specification 3, Specification 4, Specification 7:
     </paragraph>
     <list>
      <list-item label="•">
       Baseline, AMAF and EPIC all have records that are, or contain, move histories Specification 1, Specification 2, Specification 7. This implies that their records have a tree or forest structure. In contrast, MAST and LGR have a flat record structure with one record per move or action Specification 3, Specification 4. NAST is between the two extremes, with one record per sequence of n moves (NAST-1).
      </list-item>
      <list-item label="•">
       For all enhancements studied here with the exception of LGR, the information associated with a record consists of a total reward (vector or scalar), a visit count, and in some cases an availability count Specification 1, Specification 2, Specification 3, Specification 5, Specification 7.
      </list-item>
      <list-item label="•">
       Baseline, AMAF, NAST and EPIC all use some variation on the UCB1 policy Specification 1, Specification 2, Specification 5, Specification 7.
      </list-item>
      <list-item label="•">
       LGR is the only enhancement whose policy explicitly sets the probabilities of some moves to 1, giving a simulation policy that is more deterministic than for other enhancements (LGR-4).
      </list-item>
      <list-item label="•">
       If we ignore updates for availability, most of these ICARUSes update one record per state visited in the playout Specification 1, Specification 3, Specification 4, Specification 5, Specification 7. The exception is AMAF, which potentially updates several records per playout step (AMAF-6).
      </list-item>
     </list>
     <paragraph>
      At a higher level, we can identify sets of nodes which share information. There are two ways in which information can be shared between nodes via records:
     </paragraph>
     <list>
      <list-item label="1.">
       nodes use information from the same record during playout and update that record during backpropagation; or
      </list-item>
      <list-item label="2.">
       nodes use information from different records but a visit to one node causes both records to be updated.
      </list-item>
     </list>
     <paragraph>
      In other words, to share information we can either write to one record that is read by many nodes, or write to many records that are each read by one node. MAST, NAST, LGR and EPIC are of the former type, whereas AMAF is of the latter type.
     </paragraph>
     <paragraph>
      Fig. 2 illustrates this information sharing. In each tree, information is shared between the nodes connected by a dotted line. Comparing these types of pictures with our intuition about the game, particularly which states we expect to be correlated, can give us insight into which enhancements are likely to work well for which games. Looking at Fig. 2 and the corresponding ICARUS definitions, we can make the following observations about the type of games for which each enhancement should be effective:
     </paragraph>
     <list>
      <list-item label="•">
       AMAF: Works well for games where the strength of an action is often independent of time. This has shown to be true in games such as Go [3] and Hex [10], where the RAVE enhancement works well. Both of these games are characterized by moves which, with few exceptions, are fixed in place once made.
      </list-item>
      <list-item label="•">
       MAST: Effective when the quality of an action is independent of the state from which it is played. This is effective in General Game Playing where little is known about the state and it is somewhat true for most games. (Arguably any interesting game that people would play will at least slightly satisfy this property, as it would otherwise be difficult for human players to develop an intuition of strategy). This is similar to AMAF, but assumes even less about the dependence of action value on context.
      </list-item>
      <list-item label="•">
       LGR: Works well for games with a notion of “sente” (such as Go), where some moves imply a certain reply is necessary.
      </list-item>
      <list-item label="•">
       NAST: Generalises the notion of replies in LGR, so is useful when the reply is to the previous {a mathematical formula}n−1 moves rather than the previous move. Note that LGR and NAST with {a mathematical formula}n=2 both use the same correlation structure, so any difference in their performance is a result of the exact way in which the captured information is reused in the playouts.
      </list-item>
      <list-item label="•">
       EPIC: Useful in games with an episodic nature (e.g. ladder-based card games) or complex compound turns (such as LOTR:C; see Section 7.3), where contextual information can be learned from these episodes.
      </list-item>
     </list>
     <paragraph>
      The information capture methods of MAST, LGR, NAST and EPIC all belong to a class which learns the value of actions given some episode preceding the action. In the case of MAST, LGR and NAST the episodes are of fixed length (1, 2, and a fixed parameter n respectively) whereas EPIC uses episodes that are aligned to the natural episodic structure of a particular game. MAST, LGR and NAST are based on the game-independent notion of n-grams with a fixed n, whereas EPIC allows n to differ over the playout according to game-specific criteria.
     </paragraph>
     <paragraph>
      There are also possibilities for other new types of enhancement that can be built with the ICARUS framework. Fig. 2 illustrates enhancements which exploit a particular type of correlation between states in a game, but any other type of correlation can be encoded as an information capture enhancement within the ICARUS framework. Similarly there are many ways of injecting knowledge into the MCTS algorithm, with tree selection biasing and heavy playouts being amongst the most common [1], [61]. New techniques for injecting knowledge into MCTS can be combined with any existing information reuse enhancement. One potential application for the ICARUS framework could be to use techniques from machine learning (for example genetic programming) to automatically search the space of possible enhancements to discover new ones which work for a particular game. There are currently no widely used enhancements to MCTS which deal explicitly with hidden information and uncertainty in games. ICARUS provides a framework for exploring new enhancements in this area, for example considering information asymmetry when performing information capture.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Experimental domains
     </section-title>
     <paragraph>
      In this section we present the games that form the basis of our empirical analysis. For each game, we also present the corresponding EPIC episode structure.
     </paragraph>
     <section label="7.1">
      <section-title>
       Dou Di Zhu
      </section-title>
      <paragraph>
       Dou Di Zhu is a three-player ladder-based (or climbing) card game, played with a standard deck of 52 cards plus two jokers, hugely popular in China [31], [62]. One of the players is designated the Landlord, with the other two players in coalition against him. At the beginning of the game, the entire deck is dealt to the players: 20 cards to the Landlord, and 17 to each of the other players. The game is played in several rounds, with each round consisting of a leading play (a combination of cards from one of several categories: singleton, pair, straight etc.) after which players take turns to play cards of the same category but higher rank, or pass if they are unable or unwilling to play cards. The winner is the first player to play out all of the cards from their hand; if the winner is a non-Landlord player then both non-Landlord players win. For a complete description of the rules see [62].
      </paragraph>
      <paragraph>
       Our previous work on this game [63], [31], [30] showed that ISMCTS is competitive with existing commercial AI [30], although a simpler multiple tree determinization approach (similar to those used for Bridge [64] and Klondike Solitaire [34]) performs slightly better. The main strategic element in Dou Di Zhu is subdividing one's hand into non-overlapping groups, given that some groups may render others unplayable (for example if holding cards {a mathematical formula}3,4,4,5,6,7, playing the pair {a mathematical formula}4,4 means that the straight run {a mathematical formula}3,4,5,6,7 is unavailable). All cards must eventually be played, so playing groups in such a way that one is not left with a weak hand towards the end of the game is key.
      </paragraph>
      <paragraph>
       We define the EPIC episode function for Dou Di Zhu as follows. Set {a mathematical formula}E={L1,L2,L3} and{a mathematical formula} Here an episode is a stream from one leading play to the next. EPIC aims to improve on a weakness of ISMCTS for Dou Di Zhu caused by the high branching factor associated with leading plays (several hundred in some cases [31]). EPIC helps to more accurately model the sequence of plays that follows each leading play, and thus give a more accurate evaluation of each leading play, without having to rediscover this sequence in several parts of the tree.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Hearts
      </section-title>
      <paragraph>
       Hearts is a four-player trick taking card game played with a standard 52-card deck. Cards in the ♡ suit have a point value of 1 each and the Q♠ card has a point value of 13. The goal is to score as few points as possible, i.e. to avoid winning tricks with those cards in them. There is one exception to this goal: taking all thirteen ♡ cards and Q♠ in a round is called shooting the moon, and causes every player to score 26 points except the player who shot the moon. Shooting the moon is a risky strategy: the reward for success is high, but so is the cost of failure. For a complete description of the rules see [65].
      </paragraph>
      <paragraph>
       Previous work on MCTS for Hearts [66] has treated the game as one of perfect information, i.e. played with all cards face up. We use ISMCTS to handle the imperfect information explicitly. Other approaches applied to Hearts include {a mathematical formula}maxn search with various pruning mechanisms and reinforcement learning [67], [68].
      </paragraph>
      <paragraph>
       Hearts is played over several rounds, the game ending when any player reaches a score threshold (50 points in our experiments). It would be possible to simulate only to the end of the current round and have our players seek to minimise their per-round score. However this removes some of the strategic richness from the game, as certain decisions (such as whether to force Q♠ upon a certain player, or whether to attempt shooting the moon) can depend on the overall game score. To capture this, we simulate offline a large number of rounds ({a mathematical formula}10000 for our experiments), and construct a database of per-round scores. During the search, we simulate to the end of the current round as usual, and then sample round scores from this database until the score threshold is reached. This is equivalent to simulating to the end of the game, but much more efficient.
      </paragraph>
      <paragraph>
       To define the episode function for EPIC, we set {a mathematical formula}E={D,L1,L2,L3,L4} and{a mathematical formula} The first episode in a game of Hearts encompasses the dealing and card passing stages; subsequent episodes are single tricks. Here EPIC makes use of the fact that similar tricks may appear in many different places in the search tree.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Lord of the rings: the confrontation
      </section-title>
      <paragraph>
       Lord of the Rings: The Confrontation (LOTR:C) [69] is a two-player strategy board game. Each player has nine character pieces, each with its own strength value and special ability. Each player can see the identities and locations of his own pieces, but only the locations of his opponent's pieces. If a player moves a piece into a square occupied by his opponent, combat ensues: the identities of the attacking and defending pieces are revealed, and the players simultaneously choose a card each which affects the outcome of combat. The two players have asymmetric win conditions: the “Light” player wins by moving one of his pieces (Frodo) into the opponent's home square (Mordor), whereas the “Dark” player wins by killing Frodo in combat.
      </paragraph>
      <paragraph>
       ISMCTS performs strongly for LOTR:C [30], both against determinized MCTS approaches and against human players. We also found that the asymmetric nature of the game has an influence on the relative strengths of AI techniques: handling hidden information is important to the Dark player, whereas for the Light player it is more beneficial to concentrate on planning one's own moves further ahead.
      </paragraph>
      <paragraph>
       For EPIC's episode function, we set {a mathematical formula}E={M1,M2} and{a mathematical formula} An episode begins when a player moves a piece. If this movement does not result in combat, the episode ends immediately. Otherwise, the episode continues until combat is resolved. The benefit of EPIC here is twofold: it collects statistics for each movement action in a manner similar to MAST, and it refines the simulation policy for combat.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Checkers
      </section-title>
      <paragraph>
       Checkers, or Draughts, is a two-player game of perfect information, played on an {a mathematical formula}8×8 board with 12 pieces per player. Pieces may be moved forwards to a diagonally adjacent empty square, or may jump diagonally forwards by two squares if the target square is empty and the intervening square contains an opponent piece. Jumping over an opponent's piece causes it to be captured, and removed from the game. Captures may be chained together, if the jumping piece can immediately capture another piece. Otherwise the turns alternate between the two players after each move. In the variant of Checkers studied in this paper, captures are forced: if a capture move is available then it must be played, although if more than one is available the player may choose which one to take. If a piece moves onto the opponent's home row, it becomes crowned and may subsequently move and capture backwards as well as forwards. A player wins by leaving their opponent with no legal moves, i.e. by blocking or capturing all their pieces.
      </paragraph>
      <paragraph>
       Draws (stalemates) are common in checkers; indeed, perfect play by both sides will always lead to a draw [70]. AI programs capable of perfect play exist, such as Chinook [70]. As Checkers was solved more than a decade before the invention of MCTS, there has been little work on developing strong MCTS players. However Checkers is often used as a test domain for enhancements in General Game Playing systems [46], [45].
      </paragraph>
      <paragraph>
       To apply EPIC to Checkers, we set {a mathematical formula}E={M1,M2} and{a mathematical formula} Here a “non-chained” capture is one which does not continue a chain of captures, but may start one. An episode begins when a capture is made, and ends the next time a capture is made (by either player) on a subsequent turn.
      </paragraph>
     </section>
     <section label="7.5">
      <section-title>
       Othello
      </section-title>
      <paragraph>
       Othello, or Reversi, is a two-player game with perfect information, played on an {a mathematical formula}8×8 board. The game starts with the centre four squares of the board containing two black and two white pieces placed diagonally opposite each other. A move consists of placing a piece on the board; for the move to be legal, it must sandwich a horizontal, vertical or diagonal line of one or more opponent pieces between the newly placed piece and an existing own piece. The sandwiched pieces are captured, and converted to the colour of the player who moved. If (and only if) a player has no legal moves, he must pass; when both players pass consecutively, the game is over. The player with the most pieces on the board wins the game.
      </paragraph>
      <paragraph>
       Strong Othello programs exist which are capable of beating the strongest human players, one of the first such programs being Logistello [71]. More recently, MCTS has been combined with offline learning methods to produce strong play [72], [73], [74].
      </paragraph>
      <paragraph>
       The EPIC episode function is defined by {a mathematical formula}E={M1,M2} and{a mathematical formula} An episode begins on the turn after a player places a new piece on one of the 28 squares around the edge of the board. This captures the strategic notion that controlling the edges of the board is important: pieces placed on the edge are difficult to capture but create opportunities to capture opponent pieces.
      </paragraph>
     </section>
     <section label="7.6">
      <section-title>
       Backgammon
      </section-title>
      <paragraph>
       Backgammon is a two-player game which has stochasticity in the form of dice rolls, but otherwise has perfect information (i.e. there is no information hidden from one player but visible to another). The board has 24 spaces, which are numbered 1–24 in opposite directions for the two players. Each player begins with 15 pieces in a standard initial setup. The aim of the game is to move all of one's pieces towards space 1 and off the end of the board. A player's turn begins with a roll of two dice. The player then takes two moves, one for each of the two rolled numbers, moving a piece forward the given number of spaces. The same piece can be moved twice in one turn. If the two dice have the same number, the player makes four moves instead of two.
      </paragraph>
      <paragraph>
       A piece cannot be moved to a space occupied by two or more opponent pieces. However a piece can be moved to a space occupied by a single opponent piece, in which case the opponent piece is captured and moved to the bar, equivalent to space number 25. If a player has pieces on the bar, they must move them back onto the board before they may move any other pieces. A common basic strategy in Backgammon is to force the opponent to skip several turns, by capturing a piece having blocked the spaces into which it could be moved back onto the board. When all of a player's pieces are on spaces 1–6, pieces may be moved off the board (beyond point 1) and removed from the game. The first player to remove all their pieces in this way is the winner.
      </paragraph>
      <paragraph>
       Strong AI players for Backgammon, such as TD-Gammon [75], are capable of beating the strongest human players. MCTS has also been demonstrated to produce strong decisions in Backgammon [76].
      </paragraph>
      <paragraph>
       The compound turns of Backgammon give a natural episode structure. We set {a mathematical formula}E={R} and{a mathematical formula} Thus an episode consists of a full turn: the dice roll and the two or four moves that follow it.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      A wide range of experiments were conducted to compare ICARUSes and combinations of ICARUSes for the six domains listed in Section 7. We aim to compare the performance of enhancements for games of perfect and imperfect information, and investigate whether combinations of enhancements can be greater than the sum of their parts.
     </paragraph>
     <paragraph>
      In each experiment our opponent was an unenhanced player using MO-ISMCTS (for games of imperfect information) or UCT (for games of perfect information), with 5000 playouts per decision in all cases. In [30] we showed the MOSIMCTS player was on a par with the strongest setting of a commercial Dou Di Zhu AI developed by AI Factory Ltd.{sup:4} In [30] we also showed that MO-ISMCTS is on a par with intermediate-to-expert level human players for LOTR:C. For Hearts we conducted a trial of our MO-ISMCTS player against the AI for Hearts which ships with the Microsoft Windows 7 operating system (arguably one of the most played AI opponents of all time), again showing strength parity. For Checkers, Othello and Backgammon, unenhanced UCT is significantly worse than state-of-the-art AI players, but largely because the state-of-the-art is so advanced for these games. We have found unenhanced UCT to be around the level of a novice human player for these games.
     </paragraph>
     <paragraph>
      We compare the sixteen combinations of ICARUSes listed in Table 1, for the six games described in Section 7. The component enhancements used are:
     </paragraph>
     <list>
      <list-item label="•">
       the baseline ICARUS (Section 4.2);
      </list-item>
      <list-item label="•">
       RAVE (Section 4.4), itself based on AMAF (Section 4.3.1);
      </list-item>
      <list-item label="•">
       MAST (Section 4.3.2);
      </list-item>
      <list-item label="•">
       LGRF, i.e. LGR with forgetting (Section 4.3.4);
      </list-item>
      <list-item label="•">
       NAST (Section 4.3.5) with an n-gram length of {a mathematical formula}n=2.
      </list-item>
     </list>
     <paragraph>
      Where the enhancements use parameters, we performed an initial round of parameter tuning experiments to set the values for the main experiment. The parameter values are {a mathematical formula}c=0.7 for the exploration constant in both the baseline player and NAST, {a mathematical formula}k=250 for RAVE, and {a mathematical formula}τ=1 for MAST. These values give consistently good performance (relative to other parameter settings) across all our games.
     </paragraph>
     <paragraph>
      In all games, a win has a reward value of 1 and a loss a value of 0. If a draw is possible, it has a value of 0.5. In Hearts, finishing in first place has a value of 1, in last place a value of 0, and in second or third place a value of 0.5. These values are used by the MCTS players, but not in the reporting of results in this section: that is, Fig. 3, Fig. 4, Fig. 5 count the win rate (i.e. number of wins), not the cumulative reward over all trials.
     </paragraph>
     <paragraph>
      The ICARUSes listed in Table 1 cover all subsets of the four enhancements tested here. Each enhancement was originally designed for a specific phase of the MCTS iteration: RAVE [8] for selection, and MAST [43], LGR [47] and NAST [27] for simulation. The sequential combinations, using the ▹ operator, are defined to use each enhancement only for the appropriate phase. Where we have more than one enhancement for one of the phases, we combine them using a linear combination (as described in Section 4.4) with equal weights. Equivalently, at each step in the simulation we choose one of the enhancements at random and then choose the action according to that enhancement's policy. For example if the simulation enhancement is {a mathematical formula}12(ILGRF+INAST), the simulation plays according to LGRF with probability {a mathematical formula}12 and according to NAST with probability {a mathematical formula}12. The definition (Eq. (14)) of {a mathematical formula}IRAVE as a maxilinear combination of {a mathematical formula}IAMAF and {a mathematical formula}IBaseline with decaying weight {a mathematical formula}λRAVE is as used by Gelly and Silver [8].
     </paragraph>
     <paragraph>
      For a κ-player game, we play one instance of the ICARUS combination in question against {a mathematical formula}κ−1 instances of the baseline player (unenhanced MO-ISMCTS). Each algorithm (enhanced and baseline) uses 5000 MCTS iterations per decision. For Dou Di Zhu the ICARUS player plays as the Landlord against two non-Landlord baseline players. For Hearts the ICARUS player plays against three baseline players. For LOTR:C the ICARUS player plays as both Light and Dark against a baseline player (and due to the asymmetry of the game we consider the results for each player separately). For Checkers, Othello and Backgammon the ICARUS player plays against a baseline player, playing half the games as white and half as black. For each experiment we played a large number of games (between 1000 and 2500) across a cluster of PCs, using just over one CPU-year in total. Win rates are calculated with Clopper–Pearson intervals [77] at the {a mathematical formula}95% confidence level. Each game of Dou Di Zhu, LOTR:C and Backgammon has a clear winner with no possibility of a draw. In Hearts we count finishing in first or equal first place as a win, and any other outcome as a loss. In Checkers (where draws are common) and Othello (where draws are possible but rare), we only count the number of wins; draws are counted as losses.
     </paragraph>
     <paragraph>
      Average results for each enhancement are presented in Fig. 3. For each enhancement we aggregate the results for those combinations in Table 1 which feature the given enhancement, and compare with the results for those combinations which do not. For example in the pairs of bars labelled “RAVE”, the left-hand (diagonally shaded) bar sums the results for the eight combinations in Table 1 for which the RAVE column is blank, and the right-hand (solid shaded) bar for the eight combinations where the RAVE column is marked •. Where each combination in Table 1 was tested for 1000 trials, each of the bars in Fig. 3 represents 8000 trials.
     </paragraph>
     <paragraph>
      Results for individual combinations are shown in Fig. 4. The dotted lines indicate 95% confidence intervals for evenly-matched UCT (perfect information) or MO-ISMCTS (imperfect information) players. Any AI with results above this band is significantly better than an unenhanced player.
     </paragraph>
     <paragraph>
      In Fig. 3 we see that NAST provides a significant improvement for almost all games (the exceptions being LOTR:C as Light and Checkers, where there is no significant difference between players with and without NAST). Analysis of variance (ANOVA) over all results shows that NAST yields an improvement significant at the 99.9% level. It is interesting to note that NAST provides an improvement even in cases where LGRF does not, despite the two enhancements being based on a similar principle of learning the value of moves as replies to previous moves. This shows the influence of the precise way in which this information is used by the simulation policy.
     </paragraph>
     <paragraph>
      Fig. 3 also shows that RAVE is not effective in the imperfect information games. It is actually detrimental to performance in Hearts, and as the Dark player in LOTR:C, where the order in which moves are played is important to the strategy of the game. This makes intuitive sense: for example in Hearts the value of a particular card is very much dependent on when that card is played. For example, leading a trick with K♠ will be either a reasonably good or a terribly bad idea, depending whether the high-scoring Q♠ has already been played, so that AMAF/RAVE will fail to correctly learn whether K♠ is a good move. For Dou Di Zhu and LOTR:C as the Light player, RAVE did not make matters worse, but nor did it significantly improve playing strength. The only game where RAVE is significantly beneficial in our experiments is Checkers.
     </paragraph>
     <paragraph>
      MAST, LGRF and NAST are more robust enhancements than RAVE: they are sometimes beneficial, and never detrimental to a statistically significant degree. As observed by Tom and Müller [25], RAVE performs poorly in situations where relative ordering of moves is important. However MAST is based on a similar principle, and is more robust. One intuition for this is that RAVE alters the tree policy in a way that can reinforce the assumption that move ordering is not important in situations where this assumption is false. MAST on the other hand learns whether a move is good or bad on average. This implies that if move ordering is not important to the goodness of a move, MAST will reinforce selection of this move, whereas if move ordering is important MAST will enforce no preference over selecting the move, falling back to the behaviour of the default random policy of MCTS. Thus the potential for MAST to learn the wrong thing, as opposed to learning nothing at all, is much less than for RAVE.
     </paragraph>
     <paragraph>
      For MAST we conducted further experiments to investigate the impact of different reuse methods [27]. The policies in question were the four described in Section 4.3.2: Gibbs distribution, ε-greedy, roulette wheel and UCB1. We observed that ε-greedy and UCB1 offered the most consistently strong simulation policy, and that the Gibbs sampling approach which is standard in MAST is generally slightly worse than the other methods, although sensitivity to the sampling method is not terribly marked.
     </paragraph>
     <paragraph>
      In Fig. 4 we see that linear combinations of the enhancements are often greater than the sum of their parts. LGRF produced limited improvements on its own, but it enhanced other techniques (e.g. consider NL beat both N and L for Dou Di Zhu, despite L being significantly worse than −, and ML beat both M and L for LOTR:C as Dark despite no significant difference between − and L). MAST was generally effective across all games, but proved even more effective in combination (e.g. consider RML beat all of R, M and L for LOTR:C as Light and ML beat both M and L for LOTR:C as Dark). NAST performed strongly across all games, but was most effective in combination for Dou Di Zhu (NL beat both N and L) and LOTR:C as Light (NRL beat all of N, R and L).
     </paragraph>
     <paragraph>
      Analysis of the MCTS trees shows that the final number of visits for the chosen action is significantly (often 10–{a mathematical formula}30%) higher for NAST than for the baseline and LGRF, RAVE or MAST. Hence NAST is converging more quickly to an action which is generally stronger. The average reward assigned by NAST to the chosen action is also markedly different from that in trees using other enhancements, and presumably this value is more accurate given the increased playing strength due to NAST. Of the enhancements tested here, only RAVE has a significant impact on the depth of the MCTS tree. RAVE tends to construct deeper trees, with the deepest node being on average one ply deeper than for the other algorithms. That RAVE is detrimental despite this suggests that it is expanding too deeply the “wrong” areas of the tree, although the fact that the degree of exploitation at the root is the same as without RAVE suggests that this mostly occurs at levels in the tree below the root.
     </paragraph>
     <paragraph>
      Our experimental results for NAST shows that learning contextual values for moves is an effective way of improving the simulation policy. EPIC provides a way of refining this context in a game-specific way. To determine whether this refinement is helpful, we tested EPIC against NAST with {a mathematical formula}n=2. Both enhancements use UCB1 as a simulation policy, the difference being the context in which the multi-armed bandit statistics are collected: for EPIC the context is game-specific, whereas for {a mathematical formula}n=2 NAST the context is the previous move in the game (similar to LGRF). EPIC uses the episode functions for each game described in Section 7. Results are shown in Fig. 5. In Othello we find that NAST is significantly better than EPIC; in all other cases, NAST and EPIC have the same performance within {a mathematical formula}95% significance. As a corollary to this, we can conclude that EPIC is at least as robust as NAST for the games studied (even in the case of Othello, EPIC significantly outperforms the baseline player).
     </paragraph>
     <paragraph>
      The effectiveness of EPIC is particularly marked for Dou Di Zhu, which has a strongly episodic nature, since during an episode (a ladder) many cards cannot be played, but these unplayable cards will be played in future episodes. Furthermore, the order of episodes is not often important for Dou Di Zhu. There is also some independence between tricks in Hearts and between turns in LOTR:C and Backgammon, though less than between ladders in Dou Di Zhu, so that the improvements due to EPIC, while significant, are not so marked. Checkers and Othello lack a natural episodic structure, so instead we use basic notions of strategically important moves (captures in Checkers and edge piece placement in Othello) to delimit episodes. This works in both games, but for Othello proves less effective than simply fixing the episode length to 2 (i.e. using NAST).
     </paragraph>
     <paragraph>
      EPIC remains an interesting method for injecting knowledge into search in other game domains, but for these games it is clear that the episodes do not need to be so carefully chosen. Both EPIC and NAST are methods for learning useful lines of play for the playout policy; EPIC achieves this by learning fragments of lines delimited by game-specific episodes, whereas NAST with {a mathematical formula}n=2 essentially learns a Markov model. For the games tested here the Markov model is rich enough to capture useful information, but for other games a more sophisticated model such as EPIC may be required.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>