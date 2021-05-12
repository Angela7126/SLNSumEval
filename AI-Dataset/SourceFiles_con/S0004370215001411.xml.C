<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Real-time dynamic programming for Markov decision processes with imprecise probabilities.
   </title>
   <abstract>
    Markov Decision Processes have become the standard model for probabilistic planning. However, when applied to many practical problems, the estimates of transition probabilities are inaccurate. This may be due to conflicting elicitations from experts or insufficient state transition information. The Markov Decision Process with Imprecise Transition Probabilities (MDP-IPs) was introduced to obtain a robust policy where there is uncertainty in the transition. Although it has been proposed a symbolic dynamic programming algorithm for MDP-IPs (called SPUDD-IP) that can solve problems up to 22 state variables, in practice, solving MDP-IP problems is time-consuming. In this paper we propose efficient algorithms for a more general class of MDP-IPs, called Stochastic Shortest Path MDP-IPs (SSP MDP-IPs) that use initial state information to solve complex problems by focusing on reachable states. The (L)RTDP-IP algorithm, a (Labeled) Real Time Dynamic Programming algorithm for SSP MDP-IPs, is proposed together with three different methods for sampling the next state. It is shown here that the convergence of (L)RTDP-IP can be obtained by using any of these three methods, although the Bellman backups for this class of problems prescribe a minimax optimization. As far as we are aware, this is the first asynchronous algorithm for SSP MDP-IPs given in terms of a general set of probability constraints that requires non-linear optimization over imprecise probabilities in the Bellman backup. Our results show up to three orders of magnitude speedup for (L)RTDP-IP when compared with the SPUDD-IP algorithm.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A Markov Decision Process (MDP) encodes the interaction between an agent and its environment: at every stage, the agent decides to execute an action (with probabilistic effects) which leads to a next state and yields a reward. The agent's objective is to maximize the expected reward though a sequence of actions. MDPs [40] have been used as the standard model for probabilistic planning problems where the uncertainty is represented by a state transition probability matrix for each possible action.
     </paragraph>
     <paragraph>
      There are three important types of MDPs: finite horizon MDPs, where the agent has to act for {a mathematical formula}H≠∞ steps; infinite horizon MDPs where the agent has to act for {a mathematical formula}H=∞ steps; and indefinite horizon MDPs where the agent has to act for a finite and unknown number of steps (also known as Stochastic Shortest Path MDPs – SSP MDPs). Some of the efficient algorithms to MDPs have sought to exploit the factored structure in their representation [11], [31], [46], [9], [30], as well as the initial state information of SSP MDPs with a focus on the solution quality of states via asynchronous dynamic programming [3], [8].
     </paragraph>
     <paragraph>
      However, when addressing many real-world problems, it is simply impossible to obtain a precise representation of the transition probabilities in an MDP. There may be many reasons for this, including (a) imprecise or conflicting elicitations from experts [29], (b) insufficient data to form a basis for estimating precise transition models [23], (c) non-stationary transition probabilities due to insufficient state information, or (d) the occurrence of unpredictable events [51]. In all these situations, the agent can be seen making decisions against the adversarial choices of Nature.
     </paragraph>
     <paragraph label="Example 1.1">
      In an automated navigation system, the probabilities of reaching different locations after a movement, may change in the course of time depending on environmental factors (such as weather and road conditions), which can make the navigation more difficult and subject to failure. In general, it is hard to accurately model all these changes since they can include many external dependencies. In view of this, it would be better to have a policy that is optimized for a range of feasible probabilities so that it can be made robust against transition uncertainty.
     </paragraph>
     <paragraph label="Example 1.2">
      In the field of genetics, a genetic regulatory network and a set of actions (therapeutic interventions) can be modeled as an MDP [20], [38], [13]. This procedure should prevent the network from moving into undesirable states associated with diseases. However, modeling the exact MDP transition probabilities may not be possible when there are few samples or even when exogenous events occur. In this case, a model with imprecise transitions can be used to compute a robust policy for therapeutic interventions.
     </paragraph>
     <paragraph>
      The Markov Decision Process with Imprecise transition Probabilities (MDP-IP) was introduced [44], [50] to accommodate optimal models of sequential decision-making in the presence of constraints on the transition probabilities. An MDP-IP is a sequential decision process endowed with a state space, actions and rewards like any MDP, but where transition probabilities may be imprecisely specified via the parameterized state transition matrices. For instance, the probability of moving from state {a mathematical formula}s1 to state {a mathematical formula}s2, after executing action {a mathematical formula}a1 can be given by a parameter {a mathematical formula}p1 that is subject to a constraint such as {a mathematical formula}0≤p1≤0.75. That is, instead of a probability measure we have a set of probability measures, for a fixed state-action pair subject to a set of constraints φ over k parameters denoted by {a mathematical formula}p→∈[0,1]k.
     </paragraph>
     <paragraph>
      While the MDP-IP establishes a solid framework for the real-world application of decision-theoretic planning, its solution is extremely time-consuming in practice [23] and involves a complex optimization problem rather than an MDP problem: the agent's goal is to maximize its expected reward during a sequence of actions, by taking into account the worst case scenario of imprecise transition probabilities.
     </paragraph>
     <paragraph>
      The state-of-the-art algorithms for MDP-IPs are based on factored representations and synchronous dynamic programming[44], [50], [23]. The efficiency of the factored MDP-IP algorithm, SPUDD-IP [23], is due to the use of PADDs [23], algebraic decision diagrams with parameterized expressions on its leaves, which can efficiently compute an exact solution that yields speedups of up to two orders of magnitude with the current exact Value Iteration techniques for MDP-IPs. In this study, our concern is to make further improvements in the performance of approaches for solving MDP-IPs. In particular, we seek to explore asynchronous algorithms for a more general class of MDP-IP, called Stochastic Shortest Path MDP-IP (SSP MDP-IP).
     </paragraph>
     <paragraph>
      An asynchronous dynamic programming algorithm for SSP MDPs [4] of particular interest has been the trial-based real-time dynamic programming (RTDP) [3] as is corroborated by a wide range of recent work [8], [37], [45], [43]. Starting from the initial state, this approach updates sampled states during trials (runs), which are the result of simulating a greedy policy. RTDP algorithms have a number of distinct advantages for practical SSP MDP, which are as follows:
     </paragraph>
     <list>
      <list-item label="(a)">
       Anytime performance: RTDP algorithms can be interrupted at any time, and generally yield a better solution the longer they are allowed to run; and
      </list-item>
      <list-item label="(b)">
       Optimality without exhaustive exploration: By focusing on trial-based searches of reachable states from the initial state and using informed heuristics, RTDP algorithms can obtain an optimal policy while visiting (sampling) only a fraction of the state space.
      </list-item>
     </list>
     <paragraph>
      LRTDP [8] is an extension of RTDP that adds a label to states s when all the states {a mathematical formula}s′ that are reachable with the greedy policy from s have their utility estimates changed by less than ϵ.
     </paragraph>
     <paragraph>
      An efficient asynchronous dynamic programming algorithm for SSP MDP-IPs with enumerated states has been previously proposed although it is restricted to interval-based imprecision [14]. However, in general the problem is given in a factored form, i.e., in terms of state variables and in this case even if an interval-based imprecision is assumed for the variables, the previous algorithm is no longer applicable since there are multilinear parameterized joint transition probabilities and a nonlinear optimization over imprecise probabilities in the Bellman backup. This paper outlines the first asynchronous algorithm for SSP MDP-IPs in terms of a general set of constraints on probabilities that can also be applied to factored SSP MDP-IPs. The challenges of extending the RTDP and LRTDP algorithms to solve SSP MDP-IP problems are: (i) How to ensure the convergence of an asynchronous dynamic programming algorithm for SSP MDP-IPs? (ii) How to sample the next state in a trial given the imprecise probabilities? These can be addressed by making the following innovative contributions:
     </paragraph>
     <list>
      <list-item label="•">
       We propose the first asynchronous algorithm for SSP MDP-IPs given in terms of a general set of probability constraints that requires nonlinear optimization over imprecise probabilities in the Bellman backup, called (L)RTDP-IP.
      </list-item>
      <list-item label="•">
       We propose three possible methods of choosing the probability measures to sample the next state (Question (ii)) in RTDP-IP: (1) best worst-case legal probability measures; (2) random probability measures; and (3) predefined legal probability measures. We seek to show, that despite the imprecision of the transition probabilities, the RTDP-IP algorithm (with any of the three methods) also converges for a robust objective criterion (Question (i)).
      </list-item>
      <list-item label="•">
       We also propose two symbolic versions of the (L)RTDP-IP algorithm, named factRTDP-IP and factLRTDP-IP that use parameterized decision diagrams to represent and efficiently update the state value function.
      </list-item>
      <list-item label="•">
       We show in empirical terms our ability to obtain up to three orders of magnitude speedup and compare this with what can be achieved by the state-of-the-art optimal algorithms for SSP MDP-IP domains with sparse transition matrices. This proves that in practice for sparse problems, asynchronous methods are much more efficient than synchronous Value Iteration and allow us to solve larger instances of SSP MDP-IP problems than was previously possible. However, although factored Value Iteration is better than enumerated Value Iteration for MDP-IPs, it turns out that fact(L)RTDP-IP did not outperform the enumerated version, i.e., (L)RTDP-IP.
      </list-item>
      <list-item label="•">
       We empirically compare the three proposed methods for choosing the probability measures to sample the next state. Our results show that there is no significant difference between the three sampling methods in terms of time.
      </list-item>
     </list>
     <paragraph>
      Sections 2, 3 and 4 review the definitions of SSP MDP, SSP MDP-IP and factored SSP MDP-IP, respectively. Section 5 describes the state-of-the-art MDP-IP exact algorithm, SPUDD-IP [23]. Section 6 provides the first enumerated SSP MDP-IP asynchronous algorithm, called RTDP-IP with proof of its convergence. Section 7 describes two factored versions of RTDP-IP, called factRTDP-IP and factLRTDP-IP. We then analyze our empirical results in Section 8 and compare the performance of the proposed algorithms with SPUDD-IP [23]. In Section 9 we discuss related works. Finally, Section 10 summarizes our conclusions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Indefinite horizon enumerated MDPs
     </section-title>
     <paragraph>
      An indefinite horizon enumerated MDP, also called a Stochastic Shortest Path MDP (SSP MDP)[6], is a tuple {a mathematical formula}〈S,A,C,P,G,s0〉 where:
     </paragraph>
     <list>
      <list-item label="•">
       S is a finite set of states;
      </list-item>
      <list-item label="•">
       A is a finite set of actions;
      </list-item>
      <list-item label="•">
       {a mathematical formula}C:S×A→R is a cost function;
      </list-item>
      <list-item label="•">
       {a mathematical formula}P(s′|s,a) defines the conditional transition probability of reaching state {a mathematical formula}s′ when starting in state {a mathematical formula}s∈S and executing action {a mathematical formula}a∈A;
      </list-item>
      <list-item label="•">
       {a mathematical formula}G⊆S is a set of absorbing goal states. For each {a mathematical formula}s∈G, {a mathematical formula}P(s|s,a)=1 and {a mathematical formula}C(s,a)=0 for all {a mathematical formula}a∈A; and
      </list-item>
      <list-item label="•">
       {a mathematical formula}s0∈S is an optional initial state.
      </list-item>
     </list>
     <paragraph>
      The solution form for SSP MDP is a function mapping states into actions, called policy. Policies of this type are called stationary. A non-stationary policy, on the other hand, is a function of both state and time. If the mapping is complete for all {a mathematical formula}s∈S, this policy is a complete policy. However, if only a subset of states is mapped, this policy is called a partial policy. If the initial state is unknown, the solution of an SSP MDP must be an optimal stationary complete policy, i.e., a policy whose execution allows the agent to reach a goal state in the least costly way from any state {a mathematical formula}s∈S. If the initial state is given, the solution may be an optimal stationary (partial) policy rooted at {a mathematical formula}s0, i.e., a policy that allows the agent to reach a goal in the least costly way from {a mathematical formula}s0 and is defined for every state that can be reached from {a mathematical formula}s0[35].
     </paragraph>
     <paragraph label="Definition 2.1">
      Let {a mathematical formula}P(π) be the transition probability matrix {a mathematical formula}|S|×|S| corresponding to a stationary policy π with elements: {a mathematical formula}[P(π)]ij=P(sj|si,π(si)),∀si and {a mathematical formula}sj∈S. The probability that the agent is at state {a mathematical formula}sj at time k, given that the initial state is {a mathematical formula}si and using policy π is:{a mathematical formula}SSP MDP proper policyA stationary policy π is called proper if it leads to a goal with probability 1 for any possible initial state, i.e., {a mathematical formula}limk→∞⁡[Pk(π)]ij=1 for a {a mathematical formula}sj∈G and for all {a mathematical formula}si∈S[6].
     </paragraph>
     <paragraph>
      A policy that is not proper is called improper. Thus, the following conditions must be satisfied for SSP MDPs:
     </paragraph>
     <paragraph label="Assumption 2.2">
      There exists at least one proper policy.
     </paragraph>
     <paragraph label="Assumption 2.3">
      Every improper policy must incur the cost of ∞ from all the states from which it cannot reach the goal with probability 1.
     </paragraph>
     <paragraph>
      Notice that if the cost function is strictly positive for all states {a mathematical formula}s∈S∖G, the Assumption 2.3 is always true.
     </paragraph>
     <paragraph>
      We define a value function as a mapping {a mathematical formula}V:S→R∪{∞}. The value of a policy π at a state s, {a mathematical formula}Vπ(s), is defined as the expectation of the total cost that the policy π incurs when starting in s, i.e.:{a mathematical formula} where {a mathematical formula}ct is the cost incurred at time t when the agent is in state {a mathematical formula}st and takes action {a mathematical formula}π(st).
     </paragraph>
     <paragraph>
      Finding an optimal solution of an SSP MDP means finding a policy {a mathematical formula}π⁎ that minimizes {a mathematical formula}Vπ. The optimal value function {a mathematical formula}V⁎=Vπ⁎ defined as {a mathematical formula}V⁎=minπ⁡Vπ, also satisfies the following condition for all {a mathematical formula}s∈S:{a mathematical formula} known as the Bellman equation.
     </paragraph>
     <paragraph>
      SSP MDPs, which satisfy Assumption 2.2, disallow the existence of dead ends that are states from which the goal cannot be reached [35], [28], [48]. Different types of SSP MDPs with different assumptions about the existence of dead ends were defined in [35] plus algorithms for solving them. One class of interest in this paper is the SSP where dead ends exist but they are avoidable.
     </paragraph>
     <section label="2.1">
      <section-title>
       SSP MDPs with avoidable dead ends
      </section-title>
      <paragraph>
       A Stochastic Shortest Path MDP with avoidable dead ends[35], is a tuple {a mathematical formula}〈S,A,C,P,G,s0〉 where {a mathematical formula}S,A,C,P,G and {a mathematical formula}s0 are defined as in the SSP MDP definition replacing Assumption 2.2, Assumption 2.3 by the following assumptions:
      </paragraph>
      <paragraph label="Assumption 2.4">
       The initial state {a mathematical formula}s0 is known.
      </paragraph>
      <paragraph label="Assumption 2.5">
       There exists at least one proper policy rooted at {a mathematical formula}s0.
      </paragraph>
      <paragraph label="Assumption 2.6">
       Every improper policy π has {a mathematical formula}Vπ(s0)=∞.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Value Iteration: SSP MDP synchronous algorithm
      </section-title>
      <paragraph>
       Value Iteration (VI) [34] is a classical synchronous dynamic programming (DP) algorithm of an SSP MDP. Starting with an arbitrary {a mathematical formula}V0(s), VI performs value updates for all states s, computing the next value function {a mathematical formula}Vt+1(s) by applying the B operator:{a mathematical formula} where {a mathematical formula}Qt+1(s,a) is the value of state s when applying action a, and is given by:{a mathematical formula}
      </paragraph>
      <paragraph>
       This update is known as a Bellman update in {a mathematical formula}Vt. A greedy policy {a mathematical formula}π(s) w.r.t. {a mathematical formula}Vt and state s is defined as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       {a mathematical formula}Vt(s) converges to the unique optimal value function {a mathematical formula}V⁎(s) in the infinite limit of updates, i.e., {a mathematical formula}limt→∞⁡maxs⁡|Vt(s)−V⁎(s)|=0[5].
      </paragraph>
      <paragraph>
       In practice, Value Iteration is stopped when:{a mathematical formula} where {a mathematical formula}S′ is the set of states reachable from {a mathematical formula}s0 under some greedy policy π w.r.t. V and BE is known as the Bellman residual.
      </paragraph>
      <paragraph>
       Value Iteration does not converge on SSP MDPs with avoidable dead ends since, in general, it is not possible to detect divergence of state values [35]. However, when dead ends are easy to be detected, a simple modification of the VI algorithm, converges.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Admissibility
      </section-title>
      <paragraph>
       We say that the value function {a mathematical formula}V0 is admissible iff {a mathematical formula}V0(s)≤V⁎(s),∀s∈S. The operator B preserves admissibility, i.e., if {a mathematical formula}V(s)≤V⁎(s),∀s∈S, then {a mathematical formula}(BkV)(s)≤V⁎(s),∀s∈S and {a mathematical formula}k∈N⁎[7]. In this definition {a mathematical formula}Bk is the composition of the operator B, i.e., {a mathematical formula}(BkV)(s)=(B(Bk−1)V)(s),∀s∈S.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       RTDP and LRTDP: SSP MDP asynchronous algorithms
      </section-title>
      <paragraph>
       It should be noted that while Value Iteration updates all states at each iteration, an asynchronous dynamic programming method [4] applies the Bellman update to states of an SSP MDP problem in an arbitrary order, while still retaining convergence properties under certain conditions.
      </paragraph>
      <paragraph>
       The real-time dynamic programming (RTDP) algorithm [3] exploits its knowledge of the initial state by updating states encountered during trial-based simulations of a greedy policy, starting from the initial state. This DP variant explores the state space in trials and performs Bellman updates at each visited state (Fig. 1a). RTDP selects the next state to visit by drawing next state samples {a mathematical formula}s′ from the transition distribution for the current greedy action a and current state s (Fig. 1b), i.e.,{a mathematical formula}
      </paragraph>
      <paragraph>
       Since we are now looking for partial policies, i.e., policies that only involve reachable states from {a mathematical formula}s0, we can also define the idea of relevant states.
      </paragraph>
      <paragraph label="Definition 2.7">
       Relevant statesThe states reachable from {a mathematical formula}s0 by any optimal policy are called relevant states [3].
      </paragraph>
      <paragraph>
       Thus, we need to ensure convergence for optimal values only for the relevant states. The convergence of RTDP is guaranteed if all the states are initialized with an admissible value function {a mathematical formula}V0.
      </paragraph>
      <paragraph>
       However, the convergence of RTDP may be slow because states with low transition probability will be less visited and their successor states will not receive many updates. The algorithm Labeled Real-Time Dynamic Programming (LRTDP) [8] has been proposed (Algorithm 1) to improve the time of convergence of RTDP by labeling states s as solved when all the states {a mathematical formula}s′ that are reachable with the greedy policy from s have their utility estimates changed by less than ϵ. And thus it terminates trials that attain labeled states early. LRTDP first initializes V with an admissible value function and applies trial-based simulations that are almost the same as RTDP trials, except that they stop when a solved state is reached (Algorithm 1, Line 10). At the end of each trial the CheckSolved algorithm [8] is employed for each state visited during this trial, in reverse order, to determine if the state can be labeled as solved (Algorithm 1, Lines 16–22). A state is marked as solved if its greedy graph (the states reachable from s with a greedy policy) is also solved. It should be noted that by stopping a trial when a solved state has been reached, these trials are shortened and the states that have not been solved will be visited more often.
      </paragraph>
      <paragraph>
       In Algorithm 1, Update (V) computes Equations (4) and (5), while GreedyAction(V) computes Equation (6).
      </paragraph>
      <paragraph>
       LRTDP can also be used to solve SSP MDPs with avoidable dead ends, defined in Section 2.1, with little adaptation [35].
      </paragraph>
     </section>
     <section label="2.5">
      <section-title>
       RTDP convergence for SSP MDPs
      </section-title>
      <paragraph>
       In this section there is a general outline of Barto's RTDP convergence proof for SSP MDPs, which will be used as the basis of the RTDP-IP convergence proof for SSP MDP-IPs given in Section 6. Since RTDP is a special case of asynchronous DP algorithm, its convergence proof is built on the convergence proof of asynchronous DP.
      </paragraph>
      <paragraph label="Definition 2.8">
       Asynchronous dynamic programming(See [47].) In asynchronous DP, the updates of a value function do not have to be executed in a systematically arranged way. The states are updated in any order using values of other states that are available. Before the values of some states are updated, other states may be updated several times.
      </paragraph>
      <paragraph>
       Notice that Definition 2.8 is general and does not make a commitment to a particular updating operator or initial value function. Bertsekas [4] has provided evidence to show that a sufficient condition for the convergence of asynchronous DP is that the updating operator must have a contraction property w.r.t. the sup-norm [4].
      </paragraph>
      <paragraph label="Theorem 2.9">
       Asynchronous DP for SSP MDPs converges to the optimal value if the value of each state is updated infinitely often[4].
      </paragraph>
      <paragraph>
       The key to the proof of Theorem 2.9 is that the B operator, as defined by Equation (4), has a contraction property w.r.t. the sup-norm [4]. Note that RTDP is a special case of asynchronous dynamic programming where a single state is updated at each time step. If we consider a set of initial states I, as in the original proof, and if {a mathematical formula}I=S, it can be guaranteed that each state is updated infinitely often [3]. However, for {a mathematical formula}I={s0}, as considered in this paper, where only a subset of S is reachable from {a mathematical formula}s0, we cannot guarantee that all states are updated infinitely often, and therefore Theorem 2.9 cannot be directly employed to prove the convergence of RTDP.
      </paragraph>
      <paragraph>
       Thus, in order to prove the convergence of RTDP with {a mathematical formula}I={s0}, we have to guarantee that asynchronous DP is performed for the set of relevant states (Definition 2.7). Theorem 2.10 guarantees that for an SSP MDP with an admissible initial value function, RTDP converges over the set of relevant states.
      </paragraph>
      <paragraph label="Theorem 2.10">
       Convergence of RTDPIn an SSP MDP, if the initial value function{a mathematical formula}V0is admissible, repeated RTDP trials eventually yield optimal values over all relevant states[3].
      </paragraph>
      <paragraph>
       The key to the proof of this theorem is the ability of the B operator to preserve admissibility during the RTDP trials since this will eventually cause RTDP to choose the optimal policy.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Indefinite horizon enumerated MDP-IPs
     </section-title>
     <paragraph>
      An indefinite horizon Markov Decision Process with Imprecise Probabilities, also called a Stochastic Shortest Path MDP-IP (SSP MDP-IP) is a sequential decision process with states, actions, a cost function, a set of goal states and an initial state, like an SSP MDP, but with a transition probability function that can be imprecisely defined. That is, an SSP MDP-IP is an extension of an SSP MDP where, instead of a probability distribution {a mathematical formula}P(⋅|s,a) over the state space S, there is a set of probability distributions.
     </paragraph>
     <paragraph>
      For instance, consider an SSP MDP-IP with four states and two actions, {a mathematical formula}a1 and {a mathematical formula}a2. Fig. 2 shows the probability transition function for state {a mathematical formula}s0 and action {a mathematical formula}a1 with three possible next states, {a mathematical formula}s1, {a mathematical formula}s2 and {a mathematical formula}s3, and with the transition probabilities given by the parameters {a mathematical formula}p1, {a mathematical formula}p2 and {a mathematical formula}p3, i.e., {a mathematical formula}p1=P(s1|s0,a1), {a mathematical formula}p2=P(s2|s0,a1) and {a mathematical formula}p3=P(s3|s0,a1) (Fig. 2a). We denote {a mathematical formula}P(⋅|s0,a1) for the whole set of probability transition values, i.e., the set of particular values for {a mathematical formula}p1, {a mathematical formula}p2 and {a mathematical formula}p3, with {a mathematical formula}p1+p2+p3=1. Other parameters and/or probability values must be also defined for the transitions applying {a mathematical formula}a1 to states {a mathematical formula}s1,s2 and {a mathematical formula}s3. Fig. 2b shows the complete transition matrix for action {a mathematical formula}a1, which includes parameters {a mathematical formula}pi, with {a mathematical formula}i≤5, all of them subject to the following sets of constraints {a mathematical formula}φ1={p1≤2/3;p3≤2/3;2⁎p1≥p2;p1+p2+p3=1} and {a mathematical formula}φ2={p4+p5=1}. By analogy, we should define the transition function for action {a mathematical formula}a2, which may also include other parameters subject to a set of constraints. The set of constraints is called φ; the vector containing the value of each parameter that satisfies the probability constraints is represented by {a mathematical formula}p→; and the set of all probability measures that satisfy a set of constraints φ is referred to as a transition credal set.
     </paragraph>
     <paragraph label="Definition 3.1">
      Transition credal set(See [23].) A credal set containing conditional probability distributions over the next state {a mathematical formula}s′, given a state s and an action a, is referred to as a transition credal set[17] and denoted by {a mathematical formula}K(⋅|s,a). Thus, {a mathematical formula}K(⋅|s,a) (or simply {a mathematical formula}Ks,a) is used to define imprecisely specified transition probabilities.
     </paragraph>
     <paragraph>
      Notice that {a mathematical formula}P(⋅|s,a)∈K(⋅|s,a) is a conditional probability distribution and {a mathematical formula}P(s′|s,a) is a probability measure for {a mathematical formula}s′ given s and a. As in [15], we assume state-action pair independence.
     </paragraph>
     <paragraph label="Assumption 3.2">
      State-action pair independence(See [15].) Probability distributions {a mathematical formula}P(⋅|s,a) are independent from one state-action pair to another.
     </paragraph>
     <paragraph>
      In this work, we also assume that all credal sets are closed and convex and that they do not depend on stage t, that is, {a mathematical formula}K(s′|s,a) is stationary. In addition, it is assumed that the imprecise probabilities of an SSP MDP-IP are given in terms of a set of probability parameters {a mathematical formula}pi subject to a set of general constraints φ, where {a mathematical formula}∀P(⋅|s,a)∈K(⋅|s,a), {a mathematical formula}P(⋅|s,a) satisfies φ. Note that in this definition each {a mathematical formula}P(s′|s,a) is either linked to a constant between 0 and 1 or to a single parameter {a mathematical formula}pi.
     </paragraph>
     <paragraph label="Definition 3.3">
      SSP MDP-IPFormally an SSP MDP-IP is defined by {a mathematical formula}〈S,A,C,K,G,s0〉 where {a mathematical formula}S,A,C,G and {a mathematical formula}s0 are defined as for any SSP MDP and {a mathematical formula}K is a set of transition credal sets, where each transition credal set {a mathematical formula}Ks,a is defined for a state-action pair, i.e., {a mathematical formula}|K|=|S×A|.
     </paragraph>
     <paragraph label="Assumption 3.5">
      There exists at least one proper policy for the minimizer.If a pair of arbitrary policies {a mathematical formula}πM for the minimizer and {a mathematical formula}πN for the maximizer does not lead to the goal with probability 1, then the cost to the minimizer must be ∞.
     </paragraph>
     <paragraph>
      For an SSP game (with Assumption 3.4, Assumption 3.5), there is a unique equilibrium value and stationary policies which achieve this equilibrium [39].
     </paragraph>
     <paragraph label="Definition 3.6">
      Let {a mathematical formula}PIP(π) be the parameterized transition probability matrix {a mathematical formula}|S|×|S| of an SSP MDP-IP, corresponding to a policy π for the minimizer with elements: {a mathematical formula}[PIP(π)]ij=P(sj|si,π(si)), where each {a mathematical formula}P(sj|si,π(si)) is either linked to a constant between 0 and 1 or to a single parameter {a mathematical formula}pz subject to a set of constraints φ. SSP MDP-IP proper policyA stationary policy π for the minimizer is called proper if it leads to a goal with probability 1 for any possible initial state and for any probability that the maximizer chooses, i.e., {a mathematical formula}limk→∞⁡{[PIPk(π)]ij}=1 for a {a mathematical formula}sj∈G, for all {a mathematical formula}si∈S and for all values of {a mathematical formula}pz subject to φ, i.e., {a mathematical formula}∀P(⋅|si,π(si))∈K(⋅|si,π(si)).
     </paragraph>
     <paragraph>
      For example, consider an SSP MDP-IP of a robot navigation problem with six states {a mathematical formula}si, with {a mathematical formula}0≤i≤5, and four actions ({a mathematical formula}↑,↓,←,→). Let {a mathematical formula}G={s4}. Let π be a stationary policy such that {a mathematical formula}π(s0)=←, {a mathematical formula}π(s1)=↑, {a mathematical formula}π(s2)=↑, {a mathematical formula}π(s3)=↑, {a mathematical formula}π(s4)=↑ and {a mathematical formula}π(s5)=→. Fig. 3a shows the parameterized transition matrix for policy π (for simplicity, we have only include one parameter {a mathematical formula}p1). Fig. 3b shows that π is proper. {a mathematical formula}[PIPk(π)]ij=0 for any {a mathematical formula}0≤i≤5 and any {a mathematical formula}j≠4, for {a mathematical formula}k≥6. In particular {a mathematical formula}[PIPk(π)]22 is 0 for {a mathematical formula}k→∞, i.e., {a mathematical formula}limk→∞⁡(1−p1)k=0 considering the constraint {a mathematical formula}1/3≤p1≤2/3. Consequently, {a mathematical formula}limk→∞⁡{[PIPk(π)]24}=1. Thus, π is a proper policy since independently of the maximizer choices for {a mathematical formula}p1, it leads to the goal with probability 1 from any state {a mathematical formula}si (probability 1 for the whole column 4).
     </paragraph>
     <paragraph label="Assumption 3.8">
      The following conditions must be satisfied for SSP MDP-IPs: There exists at least one proper policy for the minimizer agent.If an arbitrary policy π for the minimizer agent and any probability that the maximizer chooses do not lead to the goal with probability 1, then the cost to the minimizer must be ∞.
     </paragraph>
     <paragraph>
      As in SSP games, for an SSP MDP-IP with Assumption 3.7, Assumption 3.8, there is a unique equilibrium value of the SSP MDP-IP and a deterministic stationary policy that achieves this equilibrium. This policy induces an optimal value function that is the unique fixed-point solution of [39]:{a mathematical formula}
     </paragraph>
     <section label="3.1">
      <section-title>
       SSP MDP-IPs with avoidable dead ends
      </section-title>
      <paragraph label="Assumption 3.11">
       We can also extend the definition of SSP MDP with avoidable dead ends (Section 2.1) for SSP MDP-IPs. A Stochastic Shortest Path MDP-IP with avoidable dead ends is a tuple {a mathematical formula}〈S,A,C,K,G,s0〉 where {a mathematical formula}S,A,C,K,G and {a mathematical formula}s0 are defined as in the SSP MDP-IP definition and the following conditions are satisfied: The initial state {a mathematical formula}s0 is known.There exists at least one proper policy for the minimizer agent rooted at {a mathematical formula}s0.If an arbitrary policy π for the minimizer agent and any probability that the maximizer chooses do not lead to the goal with probability 1, then the cost to the minimizer must be ∞.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Value Iteration for SSP MDP-IPs
      </section-title>
      <paragraph>
       A popular algorithm for solving enumerated SSP MDP-IPs based on dynamic programming is Value Iteration (VI) [39] that performs Bellman updates for all states s, by computing the next value function {a mathematical formula}Vt+1(s) applying operator T as follows:{a mathematical formula} where{a mathematical formula}
      </paragraph>
      <paragraph>
       Equations (10) and (11) optimize the action choice {a mathematical formula}a∈A w.r.t. the worst-case distribution {a mathematical formula}P∈Ks,a that maximizes the future expected value. Note that this algorithm (which works with an enumerated state space representation) must solve an optimization problem by calling (an LP solver if φ is a set of linear constraints or otherwise, a nonlinear solver) for every state-action pair at each step; hence it is very computationally expensive in large state spaces.
      </paragraph>
      <paragraph label="Theorem 3.12">
       Convergence of Value Iteration for SSP MDP-IPs(See[39].) For SSP MDP-IP problems,{a mathematical formula}Vt(s)converges to the unique equilibrium value function{a mathematical formula}V⁎(s)in the infinite limit of updates, i.e.:{a mathematical formula}
      </paragraph>
      <paragraph>
       In practice, Value Iteration for SSP MDP-IPs is stopped when:{a mathematical formula} where {a mathematical formula}S′ is the set of states reachable from {a mathematical formula}s0 under some greedy policy π w.r.t. V and {a mathematical formula}BEIP is known as the Bellman residual for SSP MDP-IP.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Bounded-parameter enumerated MDP
      </section-title>
      <paragraph>
       A particular sub-class of enumerated infinite horizon MDP-IP [44] is the Bounded-parameter Markov Decision Process (BMDP)[29], where the imprecise probabilities are specified by intervals, for example {a mathematical formula}{0.3≤pj≤0.5}. One algorithm for BMDPs is Interval Value Iteration [29] that can find an optimal policy (under the worst model) without requiring expensive optimization techniques. The algorithm arranges the next states by the value function in descending order and tries to assign valid higher probabilities for states with a higher value function. There are also algorithms to SSP BMDPs that are extensions of RTDP [14] and LAO* [19], [52]. However, they do not address the more general case of probability constraints considered in this work.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Factored SSP MDP-IPs
     </section-title>
     <paragraph>
      A factored SSP MDP-IP is an SSP MDP-IP where states {a mathematical formula}x→ are specified as a joint assignment to a vector {a mathematical formula}X→ of n state variables {a mathematical formula}(X1,…,Xn) and where the dynamic credal networks (DCNs)[17], [18], [23] are used to represent the transition function. {a mathematical formula}xi is used to represent the value assignment of the state variable {a mathematical formula}Xi. In this paper binary variables are employed to simplify the notation, although the definitions in this paper can be easily extended to cover multivalued variables. The cost function is also given in terms of a subset of {a mathematical formula}{X1,…,Xn}.
     </paragraph>
     <paragraph>
      We call a partial assignment {a mathematical formula}w→∈{0,1}m, where {a mathematical formula}m&lt;n, an abstract state. E.g., for {a mathematical formula}n=3, the abstract state {a mathematical formula}w→={X1=1,X2=0} corresponds to the set of states {a mathematical formula}{{X1=1,X2=0,X3=0},{X1=1,X2=0,X3=1}}.
     </paragraph>
     <paragraph label="Definition 4.1">
      Parents of a variableGiven an action a, the value of a variable {a mathematical formula}Xi′ depends on a set (possibly empty) of variables {a mathematical formula}{Xj,Xk,Xl,…}. We call this set of variables the parents of {a mathematical formula}Xi′ w.r.t. action a denoted by {a mathematical formula}paa(Xi′).
     </paragraph>
     <paragraph label="Definition 4.2">
      Factored transition credal set(See [23].) Consider an action {a mathematical formula}a∈A and a variable {a mathematical formula}Xi. A credal set containing conditional distributions over the values of {a mathematical formula}Xi given the values of {a mathematical formula}paa(Xi) is referred to as a factored transition credal set and denoted by {a mathematical formula}Ka(xi|paa(Xi),a).
     </paragraph>
     <paragraph>
      The imprecise probabilities of factored SSP MDP-IPs are given in terms of probability parameters subject to a set of constraints φ. Thus the factored transition credal set {a mathematical formula}Ka(xi|paa(Xi),a), for {a mathematical formula}i={1,⋯,n} and {a mathematical formula}∀a∈A, must satisfy φ. As for enumerated SSP MDP-IPs, we also assume that all the factored transition credal sets are closed and convex and do not depend on stage t.
     </paragraph>
     <paragraph label="Definition 4.3">
      Dynamic Credal Network – DCN(See [23].) It is a generalization of a Dynamic Bayesian Network (DBN) [21] where, given an action {a mathematical formula}a∈A, each variable {a mathematical formula}Xi is associated with factored transition credal sets {a mathematical formula}Ka(xi|paa(Xi),a) for each value of {a mathematical formula}paa(Xi). A DCN represents a joint credal set [18], [17] over all of its variables consisting of all distributions that satisfy:{a mathematical formula}For each variable {a mathematical formula}Xi′ in a DCN, there is a conditional probability table (CPT) with imprecise probabilities, where each line corresponds to a possible combination of values of {a mathematical formula}paa(Xi′), which defines an abstract state. The entries of a CPT are specified by parameters {a mathematical formula}pij (i for variable {a mathematical formula}Xi′, j for the jth parameter in the CPT for {a mathematical formula}Xi′).
     </paragraph>
     <paragraph label="Definition 4.4">
      Factored SSP MDP-IPFormally a Factored SSP MDP-IP is defined by {a mathematical formula}〈X→,A,C,K,G,x→0〉 where A is defined as for any SSP MDP-IP, {a mathematical formula}X→ is a vector of n state variables {a mathematical formula}(X1,…,Xn), C is a factored cost function, {a mathematical formula}K is a set of factored transition credal sets (Definition 4.2), G is a set of goal states and {a mathematical formula}x→0 the initial state.
     </paragraph>
     <paragraph>
      From Equations (9) and (14), the factored optimal value function for SSP MDP-IPs is given by:{a mathematical formula}
     </paragraph>
     <paragraph>
      To solve Equation (15) we can first compute the product (the joint transition probability) or use variable elimination as SPUDD-IP [23] (as explained in Section 5.3).
     </paragraph>
     <section label="4.1">
      <section-title>
       Abstract state and action pair independence and the number of credal sets
      </section-title>
      <paragraph>
       For enumerated SSP MDP-IPs we assume state and action pair independence (Assumption 3.2). In the case of factored SSP MDP-IP, instead of assuming independence for single states we now assume independence for abstract states, i.e., a set of states that are defined by the partial assignment of {a mathematical formula}paa(Xi′).
      </paragraph>
      <paragraph label="Assumption 4.5">
       Abstract state and action pair independenceProbability distributions {a mathematical formula}P(Xi′|paa(Xi′),a) are independent from one abstract state and an action pair to another.
      </paragraph>
      <paragraph>
       An example of a DCN is shown in Fig. 4a. The CPTs for variables {a mathematical formula}X1′ and {a mathematical formula}X2′ are shown in Figs. 4b and 4c. The set of constraints φ on {a mathematical formula}pij are shown below the CPTs. The CPT of Fig. 4b is defined for two abstract states {a mathematical formula}w→1={X1=0} and {a mathematical formula}w→2={X1=1}. Note that the parameters for different lines of the CPTs (abstract states) are different and the constraints are also independent for different abstract states.
      </paragraph>
      <paragraph>
       The number of credal sets {a mathematical formula}|K| depends on the number of state variables n, the number of actions {a mathematical formula}|A| and the state variable independence, i.e.:{a mathematical formula} where {a mathematical formula}maxa,Xi⁡|paa(Xi)| is the maximum number of parents in the problem for all state variables and actions. For example, for a domain with 30 variables, {a mathematical formula}maxa,Xi⁡|paa(Xi)|=5 and {a mathematical formula}|A|=10, {a mathematical formula}|K|≤30×10×25, while in the enumerated version we have {a mathematical formula}|K|=10×230.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Generating an enumerated SSP MDP-IP from a factored SSP MDP-IP
      </section-title>
      <paragraph>
       Different from an enumerated SSP MDP-IP, a factored SSP MDP-IP enables us to specify the independence that exists among state variables. The fact that a variable only depends on its parents allows variable elimination of SPUDD-IP [23] to be more efficient, depending on {a mathematical formula}|paa(Xi′)|.
      </paragraph>
      <paragraph>
       Given a factored SSP MDP-IP, we can transform it into its corresponding enumerated SSP MDP-IP by computing the joint transition probability according to Equation (14). Fig. 5 shows the joint credal sets computed for a factored SSP MDP-IP given in Fig. 4. For instance, to compute the probability to be at state {a mathematical formula}x→′={X1′=0,X2′=0} given that we are at state {a mathematical formula}x→={X1=1,X2=1} and we take action {a mathematical formula}a1, we have to multiply the probability parameters {a mathematical formula}p12 (Fig. 4b) and {a mathematical formula}p24 (Fig. 4c), i.e, {a mathematical formula}P(X1′=0,X2′=0|X1=1,X2=1,a1)=p12p24, which corresponds to {a mathematical formula}P(s0′|s3,a1) in the matrix of Fig. 5. Note that even considering sets of linear constraints {a mathematical formula}φ1 and {a mathematical formula}φ2 (Fig. 5), we now have a nonlinear optimization problem due to multiplied parameters.
      </paragraph>
      <paragraph>
       Thus, while for enumerated SSP MDP-IPs as defined in Section 3, the transition probability can be trivially linear (a single probability parameter {a mathematical formula}pi for each {a mathematical formula}P(s′|s,a)), in an enumerated SSP MDP-IP generated from a factored SSP MDP-IP, there are multilinear parameterized joint transition probabilities.
      </paragraph>
      <paragraph>
       Notice also that if the constraints are simple intervals, as in Figs. 4b and 4c, which could define a factored BMDP (Section 3), when the joint transition probabilities are calculated, we no longer have an interval-based model and thus the Interval Value Iteration algorithm [29] for BMDPs cannot be applied.
      </paragraph>
      <paragraph>
       Since in practice, problems are commonly described in a factored way, it must be assumed that any SSP MDP-IP generated from a factored description will have to deal with nonlinear optimization problems, even though the set of constraints for the probability parameters are simple intervals.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Value Iteration for factored MDP-IPs
     </section-title>
     <paragraph>
      SPUDD [31] is an efficient Value Iteration solver for factored infinite horizon MDPs. It uses Algebraic decision diagrams (ADDs)[2] to compactly represent the transition and cost function and efficiently compute the optimal policy. An extension of ADDs, called Parameterized ADDs (PADDs) was proposed in [23] to efficiently solve factored infinite horizon MDP-IPs in an algorithm called SPUDD-IP that proves to be up to two orders of magnitude faster than Value Iteration when solving the corresponding enumerated infinite horizon MDP-IPs.
     </paragraph>
     <section label="5.1">
      <section-title>
       Algebraic decision diagrams
      </section-title>
      <paragraph>
       Algebraic decision diagrams (ADDs) [2] are used to compactly represent functions {a mathematical formula}f:{0,1}n→R with context-specific independence [10]. ADDs are an extension of BDDs [12] that represent boolean functions {a mathematical formula}f:{0,1}n→{0,1}. ADDs are directed acyclic graphs (DAGs) whose nodes are associated to decision variables {a mathematical formula}Yi∈Y{a mathematical formula}(1≤i≤n) and the two out-going arcs for a node are labeled true (high) and false (low), respectively [2]. Additionally, any path from root to leaf follows a fixed total variable ordering {a mathematical formula}O. In an ADD, identical subgraphs are merged, which can result in a compact representation of f. For example, the cost function {a mathematical formula}C:{0,1}n→R+ represented in Fig. 6a as a decision tree can be represented as an ADD in a compact form (Fig. 6b).
      </paragraph>
      <paragraph>
       Given a boolean function f represented as an ADD, called F, and a set of variables Y with variable assignment {a mathematical formula}y→∈{0,1}n; {a mathematical formula}EvalADD(F,y→) returns the real value of the leaf following the corresponding path from the ADD root.
      </paragraph>
      <paragraph>
       Unary operations such as min, max, restriction, marginalization over variables ({a mathematical formula}∑xi∈Xi), as well as binary operations such as addition (⊕), subtraction (⊖), multiplication (⊗), {a mathematical formula}min⁡(⋅,⋅) and {a mathematical formula}max⁡(⋅,⋅) can be performed efficiently on ADDs.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Parameterized ADDs (PADDs)
      </section-title>
      <paragraph>
       PADDs [23] are an extension of ADDs used to compactly represent functions {a mathematical formula}f:{0,1}n→E, where {a mathematical formula}E is the space of expressions over a set of parameters Z and where {a mathematical formula}Zi∈Z ({a mathematical formula}1≤i≤k) belongs to the interval {a mathematical formula}[0,1] and it is given a set of constraints over these parameters. For example, the CPTs from Figs. 4b and 4c can be represented as PADDs (Fig. 7) that contain in the leaves polynomials involving probability parameters {a mathematical formula}pij and a set of constraints φ for them.
      </paragraph>
      <paragraph>
       Since the expressions in {a mathematical formula}E can be restricted to polynomials, a PADD that represents a boolean function f, called F, can be defined by the following BNF grammar [23]:{a mathematical formula} where {a mathematical formula}Zi∈Z is subject to a given set of constraints. In the if-then-else statement of PADDs we call {a mathematical formula}Fh the true (high) branch, {a mathematical formula}Fl the false (low) branch and {a mathematical formula}Fvar the test variable of the decision node, which can be any {a mathematical formula}Yi, {a mathematical formula}(1≤i≤n). Notice that this definition allows Poly to be any polynomial expression.
      </paragraph>
      <paragraph>
       ADD operations can be easily extended and efficiently performed on PADDs. Binary operations are ⊕ (sum), ⊖ (subtraction), and ⊗ (product). Unary operations are restriction, denoted by {a mathematical formula}F|Yi=yi, which can be calculated by replacing all decision nodes for variable {a mathematical formula}Yi with either the true or false branch (see the example in Fig. 8); and sum out (also called marginalization), which eliminates a variable {a mathematical formula}Yi from the PADD and is computed by {a mathematical formula}∑yi∈{0,1}F=F|Yi=0+F|Yi=1. N-ary operations are: {a mathematical formula}⨂i=1n (the product of a sequence) and {a mathematical formula}∑y1,⋯,yn/yi∈{0,1} (multiple sum out, which computes a sequence of n sum out operations, i.e., {a mathematical formula}∑y1,⋯,ynF=∑yn(⋯(∑y2(∑y1F))⋯)). All these operations are closed for PADDs (i.e., these operations on PADDs yield new PADDs with leaves that can also be expressed as Poly, i.e., Poly can be any polynomial expression). To avoid notational clutter, instead of {a mathematical formula}∑y1,⋯,yn/yi∈{0,1} we will use {a mathematical formula}∑y1,⋯,yn and instead of {a mathematical formula}∑yi∈{0,1} we will use {a mathematical formula}∑yi.
      </paragraph>
      <paragraph>
       Next, five PADD functions are defined (Definition 5.1, Definition 5.2, Definition 5.3, Definition 5.4, Definition 5.5) that are going to be used in the algorithms proposed in Section 7 and we refer the reader to [23] for an algorithmic description of the basic PADD operations.
      </paragraph>
      <paragraph label="Definition 5.1">
       PADD evaluation – {a mathematical formula}EvalPADD(F,y→)Given a set of variables Y with a variable assignment {a mathematical formula}y→∈{0,1}n, the polynomial returned by the operation PADD evaluation, called {a mathematical formula}EvalPADD(F,y→), can be computed recursively by:{a mathematical formula} where {a mathematical formula}y→(Fvar) means the value of {a mathematical formula}Fvar in the variable assignment {a mathematical formula}y→.
      </paragraph>
      <paragraph>
       {a mathematical formula}EvalPADD(F,y→) can be also computed as a sequence of PADD restriction operations by {a mathematical formula}(((F|Y1=y→(Y1))|Y2=y→(Y2))…)|Yn=y→(Yn) resulting in a terminal node Poly.
      </paragraph>
      <paragraph>
       An example of PADD Evaluation is given in Fig. 9 where F is the probability transition function {a mathematical formula}PDD(X2′|X1,X2,a1), {a mathematical formula}n=4 and {a mathematical formula}y→ is an assignment for the state variables {a mathematical formula}X1′, {a mathematical formula}X2′, {a mathematical formula}X1 and {a mathematical formula}X2, which results in the polynomial {a mathematical formula}1−p24.
      </paragraph>
      <paragraph label="Definition 5.2">
       PADD partial evaluation – {a mathematical formula}pEvalPADD(F,w→)Given a partial assignment, {a mathematical formula}w→∈{0,1}m, {a mathematical formula}m&lt;n, over {a mathematical formula}W⊂Y, the partial evaluation of a PADD F, named {a mathematical formula}pEvalPADD(F,w→), returns a PADD (instead of a polynomial) and is computed by {a mathematical formula}(((F|W1=w→(W1))|W2=w→(W2))…)|Wm=w→(Wm).
      </paragraph>
      <paragraph>
       Fig. 10 gives an example of PADD partial evaluation, where F is the probability transition function {a mathematical formula}PDD(X2′|X1,X2,a1) and {a mathematical formula}w→ is an assignment for the state variables {a mathematical formula}X1 and {a mathematical formula}X2, which results in a PADD with a single variable {a mathematical formula}X2′.
      </paragraph>
      <paragraph label="Definition 5.3">
       Polynomial evaluation – {a mathematical formula}ValPoly(Poly,z→)Given a polynomial Poly (i.e., a leaf of a PADD), containing a set Z of k parameters and an assignment {a mathematical formula}z→∈[0,1]k over Z, the operation polynomial evaluation, named {a mathematical formula}ValPoly(Poly,z→), returns the value of Poly according to {a mathematical formula}z→ and can be recursively defined by:{a mathematical formula} where {a mathematical formula}z→(Zi) means the value of {a mathematical formula}Zi in the parameter assignment {a mathematical formula}z→.
      </paragraph>
      <paragraph>
       For example, given {a mathematical formula}k=4, a polynomial {a mathematical formula}Poly=p12p22 and {a mathematical formula}z→={p11=0.5,p12=0.3,p21=0.65,p22=0.4}, {a mathematical formula}ValPoly(Poly,z→) results in 0.12.
      </paragraph>
      <paragraph label="Definition 5.4">
       PADD replacing parameters – {a mathematical formula}ValPADDLeaves(F,z→)Given a PADD F containing a set of k parameters Z and an assignment {a mathematical formula}z→∈[0,1]k over Z, the operation PADD replacing parameters, named {a mathematical formula}ValPADDLeaves(F,z→), returns an ADD, where each polynomial leaf Poly is replaced by {a mathematical formula}ValPoly(Poly,z→) (Equation (19)).
      </paragraph>
      <paragraph>
       {a mathematical formula}ValPADDLeaves(F,z→) can be recursively computed by constructing a unique canonical ADD, from the terminal leaf nodes (replaced by the value returned by {a mathematical formula}ValPoly(Poly,z→)) all the way up to the root node.
      </paragraph>
      <paragraph>
       An example of PADD ReplacingParameters is given in Fig. 11 where {a mathematical formula}k=4, {a mathematical formula}z→={p11=0.5,p12=0.3,p21=0.65,p22=0.4} and F is the probability transition function {a mathematical formula}PDD(X1′|X1,a1) which results in an ADD of Fig. 11b.
      </paragraph>
      <paragraph label="Definition 5.5">
       PADD MaxParameterOut – {a mathematical formula}MaxParameterOut(F,φ)(See [23].) Given a PADD F with a set of parameters Z such that {a mathematical formula}|Z|=k and a set of constraints φ over Z, {a mathematical formula}MaxParameterOut(F,φ) returns an ADD, where each polynomial leaf Poly is replaced by the value returned by calling a nonlinear solver with {a mathematical formula}maxZ1,⋯,Zk⁡Polys.t.φ.
      </paragraph>
      <paragraph>
       {a mathematical formula}MaxParameterOut(F,φ) can be recursively computed by an algorithm similar to {a mathematical formula}ValPADDLeaves(F,z→)[23].
      </paragraph>
      <paragraph>
       An example of PADD MaxParameterOut is given in Fig. 12 where F is the value function {a mathematical formula}VDD and {a mathematical formula}φ1 is the set of constraints, which results in an ADD of Fig. 12b.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       SPUDD-IP
      </section-title>
      <paragraph>
       Satia and Lave, 1970 [44], were the first to propose an exact Value Iteration algorithm for enumerated infinite horizon MDP-IPs. A more efficient algorithm was proposed by Delgado et al., 2011 [23], which could solve factored infinite horizon MDP-IP by using PADDs in all steps of the Value Iteration algorithm, which is called SPUDD-IP. This algorithm is adapted to solve SSP MDP-IP and defines Equations (10) and (11) by means of a factored representation of the transition probability function (Equation (14)) and the cost function. Thus, a factored Bellman update for all states is given by{sup:1}:{a mathematical formula} where{a mathematical formula}
      </paragraph>
      <paragraph>
       All the operations in (20) and (21) can be computed through decision diagram operations where the cost and value functions for all the states are ADDs (denoted by {a mathematical formula}CDD and {a mathematical formula}VDDt); and the transition functions (CPTs) are represented as PADDs, denoted by {a mathematical formula}PDD(Xi′|paa(Xi′),a), one for each pair of variable {a mathematical formula}Xi′ and action a. Note that the maximization {a mathematical formula}maxp→∈Ka in Equation (21) is performed by applying the MaxParameterOut operation on a PADD, i.e., by calling a nonlinear solver to maximize each PADD leaf, which results in an ADD (this operation corresponds to choosing the worst model for an abstract state and action pair). Therefore {a mathematical formula}QDDt+1 is an ADD. This is important because {a mathematical formula}mina∈A operation{sup:2} in Equation (20) can only be performed on ADDs. By using PADDs, SPUDD-IP performs operations for sets of states (i.e., abstract states) that have the same value and only need to call a nonlinear solver for PADDs leaves, not necessarily for all the states. This is a key factor in improving efficiency by orders of magnitude. For efficient calculations, SPUDD-IP exploits the variable elimination algorithm [53] by using the sum out operation for PADDs (rectangle expression of Equation (21)). The termination criterion of SPUDD-IP is when the Bellman residual {a mathematical formula}BEIP becomes smaller than a bound ϵ (Equation (13)).
      </paragraph>
      <paragraph>
       Two approximate Value Iteration extensions have been proposed for factored infinite horizon MDP-IPs: (i) APRICODD-IP, a direct extension of the approximate version of SPUDD (APRICODD [46]); and (ii) Objective-IP [23] that seeks to convert the polynomial leaves into constants in order to target the main source of time complexity, i.e., the number of calls to the nonlinear solver during the MDP-IP Value Iteration [23].
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      RTDP-IP: enumerated asynchronous algorithm for SSP MDP-IPs
     </section-title>
     <paragraph>
      In this section we propose the first general asynchronous algorithm for SSP MDP-IPs: RTDP-IP, which involves optimization problems and is based on the well-known RTDP [3] algorithm for SSP MDPs and its extension (LRTDP-IP), which is based on the LRTDP [8] algorithm for SSP MDPs.
     </paragraph>
     <paragraph>
      An asynchronous dynamic programming algorithm for enumerated SSP MDP-IPs, called RTDP-IP (Algorithm 2), modifies the RTDP algorithm (Section 2) in two important aspects: (i) the Bellman update and (ii) the next state sampling.
     </paragraph>
     <paragraph>
      The SSP MDP-IP Bellman backup for the current state that was visited in a trial is carried out through Equations (10) and (11) that are computed by RTDP-IP-Update method (Algorithm 3). This method is called by Algorithm 2 in Line 15 and 24. In contrast with the Value Iteration algorithm, the Bellman update is only performed for the current state in a trial. Notice that the ComputeSuccessors method (called by Algorithm 3 in Line 4) must consider a state {a mathematical formula}s′ as a successor of a state s, under a greedy action a, if the parameter {a mathematical formula}pi=P(s′|s,a) can assume a legal value greater than 0.
     </paragraph>
     <paragraph>
      The next state sampling is carried out by taking into account the imprecise probabilities, i.e.: given a greedy action, we first have to choose values for each parameter {a mathematical formula}pi, subject to a set of constraints φ, before finally doing the sampling itself (Algorithm 2, Line 19). The algorithm RTDP-IP-Sampling (Algorithm 4) is explained in the next section.
     </paragraph>
     <section label="6.1">
      <section-title>
       RTDP-IP sampling
      </section-title>
      <paragraph>
       In order to sample the next state, three different methods are considered for choosing a value for each probability parameter {a mathematical formula}pi, subject to a set of constraints φ: (1) the use of the same parameter values computed in the Bellman update called minimax_parameter_choice; (2) computing a random legal parameter value at each step during the trial called rand_parameter_choice; (3) computing a predefined legal parameter value only once called predefined_parameter_choice.
      </paragraph>
      <paragraph>
       The minimax_parameter_choice method uses the same {a mathematical formula}p→∈Ks,a, computed in Line 15 (Algorithm 2) by the RTDP-IP-Update method. Thus, {a mathematical formula}p→ can be used for both purposes, i.e., to update a state value and to sample the next state.
      </paragraph>
      <paragraph>
       The predefined_parameter_choice and rand_parameter_choice methods compute valid probability distributions for the set of credal sets. Since we assume convex and closed credal sets, we can obtain the vertices {a mathematical formula}u0→,⋯,ul→ of each credal set {a mathematical formula}K(⋅|s,a) (each vertex is a distribution over S) by using the LRS software [1].
      </paragraph>
      <paragraph>
       For instance, consider a problem where for state {a mathematical formula}s0 and action {a mathematical formula}a2 there are only three possible next states {a mathematical formula}s3, {a mathematical formula}s4 and {a mathematical formula}s5 with the transition probabilities given by the parameters {a mathematical formula}p1, {a mathematical formula}p2 and {a mathematical formula}p3, i.e., {a mathematical formula}P(s3|s0,a2)=p1, {a mathematical formula}P(s4|s0,a2)=p2 and {a mathematical formula}P(s5|s0,a2)=p3, defined with the following constraints: {a mathematical formula}φ1={p1≤2/3,p3≤2/3,2,p1≥p2,p1+p2+p3=1}. The region of all probability measures that satisfy {a mathematical formula}φ1 is shown in Fig. 13 where the vertices of the polytope (gray region) are: {a mathematical formula}u0→={1/3,0,2/3}, {a mathematical formula}u1→={0,1/3,2/3}, {a mathematical formula}u2→={1/3,2/3,0}, {a mathematical formula}u3→={2/3,1/3,0} and {a mathematical formula}u4→={2/3,0,1/3}. A valid probability distribution (i.e., a point inside the gray region) could be {a mathematical formula}p→={0.5,0.2,0.3}, which is a linear combination of {a mathematical formula}uj→.
      </paragraph>
      <paragraph>
       Hence, the vertices of the polytope defined by each credal set {a mathematical formula}K(⋅|s,a) can be used to generate a random point {a mathematical formula}p→∈K(⋅|s,a) as a linear combination of {a mathematical formula}uj→[24], that is:{a mathematical formula} where {a mathematical formula}wj are generated by a uniform random sample on {a mathematical formula}[0,1] and then normalized to ensure {a mathematical formula}∑j=0lwj=1.
      </paragraph>
      <paragraph>
       The predefined_parameter_choice first computes all the credal set vertices (Algorithm 2, Line 8) and then uses the ComputeRandomPointForAllCredalSets function to compute random points {a mathematical formula}p→∈Ks,a (Equation (22)) for all the credal sets (Algorithm 2, Line 9), i.e., for the credal sets {a mathematical formula}K(⋅|s,a), {a mathematical formula}∀s∈S and {a mathematical formula}∀a∈A. This method computes them before starting the trials and uses the same {a mathematical formula}p→ for each state-action pair.
      </paragraph>
      <paragraph>
       The rand_parameter_choice method computes a random point (Equation (22)) for the credal set {a mathematical formula}K(⋅|s,a), where s is the current state in a trial and a is the greedy action (Algorithm 4, Lines 3–7). Thus, while the predefined_parameter_choice computes {a mathematical formula}p→ for all state-action pairs before starting the trials, the rand_parameter_choice only computes {a mathematical formula}p→ for the visited state and corresponding greedy action. Note that the vertices {a mathematical formula}u0→,⋯,ul→ for the credal set {a mathematical formula}K(⋅|s,a) are stored in a hash table called CredalSetVerticesHash (Algorithm 4, Line 6). These vertices can be reused if s is revisited and a is still a greedy action, to compute a new {a mathematical formula}p→.
      </paragraph>
      <paragraph>
       After having chosen the values for {a mathematical formula}p→, with one of the three sampling methods, we can finally carry out the sampling of the next state as follows:{a mathematical formula} where {a mathematical formula}P(⋅|s,a) is completely known, i.e., all the probability parameters, {a mathematical formula}p→, are known.
      </paragraph>
      <paragraph>
       Fig. 14 provides an example of a Bellman update for an SSP MDP-IP and the next state sampling. For the Bellman update, Fig. 14a shows the two calls to a linear solver to choose the probability measure that maximizes the future cost of the agent following action {a mathematical formula}a1 or {a mathematical formula}a2, with {a mathematical formula}a2 being the action that minimizes the results. Fig. 14b illustrates the computation of {a mathematical formula}p→ using the rand_parameter_choice method with the greedy action {a mathematical formula}a2 that results in {a mathematical formula}p1=0.5, {a mathematical formula}p2=0.2 and {a mathematical formula}p3=0.3. Finally, RTDP-IP samples the next state with the chosen parameter values {a mathematical formula}p1, {a mathematical formula}p2 and {a mathematical formula}p3 (Fig. 14c).
      </paragraph>
      <paragraph>
       We can modify Algorithm 2 to a Labeled RTDP-IP, called LRTDP-IP (Algorithm 5). Unlike CheckSolved[8] for SSP MDP, CheckSolved-IP (called by Algorithm 5, line 27) computes the greedy graph by taking into account all the states that can be reached with the greedy policy with a probability value greater than 0.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       RTDP-IP convergence
      </section-title>
      <paragraph>
       Buffet's proof outline [14] is followed for Robust RTDP since it allows us to refer to the imprecision as a set of possible models in the polytope defined by the credal set. However, two points of this proof need to be clarified:
      </paragraph>
      <list>
       <list-item label="1.">
        The convergence of asynchronous DP for SSP MDP-IPs, which in order to be complete must rely on the fact that the operator T of Equation (10) is monotonic (Theorem 6.1).
       </list-item>
       <list-item label="2.">
        The preservation of the admissibility of the value function (Proposition 6.2).{sup:3}
       </list-item>
      </list>
      <paragraph label="Proof">
       Asynchronous DP for SSP MDP-IP converges to V* if the value of each state is updated infinitely often.The proof follows directly from the fact that the operator T of SSP MDP-IPs (Equation (10)) can be seen as a particular case of the updating operator for sequential SSP games [39]. Thus, T is monotonic (Lemma A.1 in [39]) and based on the Assumption 3.7, Assumption 3.8 (Section 3), T has a unique fixed point (Proposition 4.5 in [39]), which is the equilibrium cost of the SSP MDP-IP (Proposition 4.6 in [39]). Also, there exist stationary policies for the minimizer and maximizer that achieve the equilibrium (Proposition 4.6 in [39]). These are sufficient conditions for the convergence of asynchronous DP for SSP MDP-IPs [4].  □
      </paragraph>
      <paragraph>
       Second, we show that the admissibility of the value function of an SSP MDP-IP is preserved during the RTDP-IP trials.
      </paragraph>
      <paragraph label="Proposition 6.2">
       If the initial value{a mathematical formula}V0is admissible, the admissibility of the value function is preserved during the execution of RTDP-IP, i.e., if{a mathematical formula}V0(s)≤V⁎(s),∀s∈Sthen{a mathematical formula}Vt(s)≤V⁎(s),∀s∈Sand{a mathematical formula}t∈N⁎.
      </paragraph>
      <paragraph label="Proof">
       We will prove by induction that {a mathematical formula}Vt(s)≤V⁎(s),∀s∈S at any time t.Base case: For {a mathematical formula}t=0, {a mathematical formula}V0(s)≤V⁎(s) is true.Induction step: Let {a mathematical formula}st be the current state, {a mathematical formula}at the greedy action and {a mathematical formula}Vt the value function at time step t, generated by executing RTDP-IP starting from an arbitrary initial state. Since RTDP-IP updates only the state {a mathematical formula}st at time t, {a mathematical formula}Vt+1(s)=Vt(s),∀s≠st and by the induction hypothesis if {a mathematical formula}Vt(s)≤V⁎(s),∀s∈S, then {a mathematical formula}Vt+1(s)≤V⁎(s),∀s≠st. Now we have to prove for {a mathematical formula}st, again by the induction hypothesis if {a mathematical formula}Vt(s)≤V⁎(s),∀s′∈S, then for {a mathematical formula}st:{a mathematical formula} Thus, {a mathematical formula}Vt+1(s)≤V⁎(s),∀s∈S at any time t.  □
      </paragraph>
      <paragraph>
       Note that the only difference from Barto's proof is the addition of {a mathematical formula}maxP∈Kst,a in Equation (24), which also involves the same inequality. Thus, Barto's proof for the preservation of admissibility by RTDP was easily extended to RTDP-IP.
      </paragraph>
      <paragraph>
       To complete the convergence proof, we still have to guarantee that the relevant states are visited infinitely often. Thus, it must be ensured that the method of choosing a probability distribution {a mathematical formula}P∈Ks,a to sample the next state never eliminates any state to be eventually visited. In our proposal, since rand_parameter_choice chooses a different {a mathematical formula}P∈Ks,a for each visited state during a trial, it will eventually visit all the reachable states. However, when using the other two methods (minimax_parameter_choice and predefined_parameter_choice) we must avoid choosing a probability measure equal to 0. For example, the predefined_parameter_choice method, could lead us to choose {a mathematical formula}P(⋅|s,a)∈K(⋅|s,a) such that {a mathematical formula}P(s′|s,a)=0 for some {a mathematical formula}s′∈S and use it thereafter, which means it would never visit {a mathematical formula}s′. In the worst case scenario, the same thing can happen if minimax_parameter_choice chooses {a mathematical formula}P(⋅|s,a)∈K(⋅|s,a) such that {a mathematical formula}P(s′|s,a)=0 for some {a mathematical formula}s′∈S, every time we visit state s with action a. Thus, convergence can also be guaranteed by using the minimax_parameter_choice or predefined_parameter_choice methods if we choose {a mathematical formula}P(⋅|s,a)∈K(⋅|s,a) such that {a mathematical formula}P(s′|s,a)≠0 for any {a mathematical formula}s′∈S.
      </paragraph>
      <paragraph>
       In general the convergence theorem of RTDP-IP can be stated as follows:
      </paragraph>
      <paragraph label="Theorem 6.3">
       Convergence of RTDP-IP with different methods for sampling the next stateIn an SSP MDP-IP, repeated RTDP-IP trials eventually yield optimal values over all relevant states if: (i) the initial value function is admissible, i.e.,{a mathematical formula}V0(s)≤V⁎(s),∀s∈Sand (ii) the method of choosing a probability distribution{a mathematical formula}P(⋅|s,a)∈K(⋅|s,a)to sample the next state guarantees choosing{a mathematical formula}P(⋅|s,a)∈K(⋅|s,a)such that{a mathematical formula}P(s′|s,a)≠0for any{a mathematical formula}s′∈S.
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      factRTDP-IP and factLRTDP-IP: factored asynchronous algorithms for SSP MDP-IPs
     </section-title>
     <paragraph>
      In this section the efficiency of SPUDD-IP [31], a factored version of Value Iteration for infinite horizon MDP-IPs, has led us to propose factored versions of RTDP-IP and LRTDP-IP called factRTDP-IP and factLRTDP-IP, respectively.
     </paragraph>
     <section label="7.1">
      factRTDP-IP algorithm
      <paragraph>
       Based on a factored asynchronous algorithm for MDPs [33], we propose the first factored asynchronous algorithm for SSP MDP-IPs, called factRTDP-IP, that combines ideas of SPUDD-IP [23] (Section 5.3) and RTDP-IP (Section 6).
      </paragraph>
      <section>
       <section>
        <section-title>
         factRTDP-IP update
        </section-title>
        <paragraph>
         As in an RTDP-like algorithm, the Bellman update is only performed for the currently visited state during a trial, with the following Equation:{a mathematical formula} where{a mathematical formula}
        </paragraph>
        <paragraph>
         It should be noted that, after computing Equation (26), {a mathematical formula}Qt+1(x→,a) and {a mathematical formula}Vt+1(x→) end up having real values, different from the resulting ADD computed by SPUDD-IP backup (Equations (20) and (21)), where {a mathematical formula}QDDt+1(X→,a) and {a mathematical formula}VDDt+1(X→) are ADDs that represent the corresponding values for the complete set of states. This is because we are exploring the state space in trials and performing Bellman updates only for the currently visited state and as a result only a constant value {a mathematical formula}Vt+1 is obtained for the state {a mathematical formula}x→.
        </paragraph>
        <paragraph>
         As in the case of SPUDD-IP, the computation of Equation (26) can be performed in an efficient way by eliminating a variable whenever it does not depend on any other variable. For example, if {a mathematical formula}X1′ is not dependent on any other {a mathematical formula}Xi′,∀i≠1 using action a, we can “push” the sum over {a mathematical formula}X1′ inwards by expanding Equation (26) into:{a mathematical formula} which can be repeated for all variables, obtaining:{a mathematical formula}
        </paragraph>
        <paragraph>
         Since {a mathematical formula}Xi′ represents a variable {a mathematical formula}Xi in the next state and {a mathematical formula}paa(Xi′) the parents of {a mathematical formula}Xi′, {a mathematical formula}pEvalPADD(PDD(Xi′|paa(Xi′),a),x→), which applies the restriction operation for each state variable, results in a PADD with a single variable {a mathematical formula}Xi′.
        </paragraph>
        <paragraph>
         We show an example of variable elimination in Fig. 15 for the currently visited state {a mathematical formula}x→={X1=1,X2=1} and action a. Fig. 15a shows the product between the first value function {a mathematical formula}VDD0(X→′) (obtained after “priming” the variables of {a mathematical formula}VDD0(X→)) and the transition probabilities for {a mathematical formula}X1′ given the current state {a mathematical formula}x→ (i.e., the resulting PADD after applying {a mathematical formula}pEvalPADD(PDD(X1′|paa(X1′),a),x→)). Fig. 15b takes the result of the previous product and eliminates variable {a mathematical formula}X1′ applying summing out over {a mathematical formula}x1′. After that {a mathematical formula}X2′ can be eliminated by first multiplying the previous result by the transition probabilities for {a mathematical formula}X2′ given the current state {a mathematical formula}x→ and action a (Fig. 15c). Finally, in Fig. 15d we apply summing out over {a mathematical formula}x2′. Notice that the resulting PADD corresponds to a polynomial, which is multilinear as a result of Assumption 4.5. This is important since there are efficient implementations for multilinear optimizations that can be used in practice.
        </paragraph>
        <paragraph>
         Next, the MaxParameterOut PADD operation is employed to perform the maximization over the parameters in Equation (26). Notice that maximizing parameters in PADDs is equivalent to maximizing parameters in the leaves. This is done by calling an optimization solver for a leaf in the PADD, where the result is also an ADD with one leaf, i.e., corresponds to a real value. For the example computed in Fig. 15, the optimization solver is called with {a mathematical formula}(1−p12)(1−p24) (Fig. 15d) and the set of constraints φ returning the probability values {a mathematical formula}{p11=0,p12=0.8,p21=0.5,p22=0.5,p23=0.25,p24=0.15} and the polynomial value that is used with {a mathematical formula}EvalPADD(CDD(X→,a),x→) to compute {a mathematical formula}Qt+1(x→,a).
        </paragraph>
        <paragraph>
         Finally, Equation (25) performs the minimization operation over the {a mathematical formula}Qt+1 values for all actions, resulting in a constant value {a mathematical formula}Vt+1. FactRTDP-IP must insert this new constant {a mathematical formula}Vt+1 into the current value function {a mathematical formula}VDDt to obtain {a mathematical formula}VDDt+1. This insertion is carried out by constructing a simple indicator function ADD {a mathematical formula}x→DD that takes the value 1 for state {a mathematical formula}x→ and 0 otherwise, i.e., given a variable assignment {a mathematical formula}v→:{a mathematical formula}
        </paragraph>
        <paragraph>
         One way to construct the indicator function {a mathematical formula}x→DD is to employ a sequential product operation {a mathematical formula}⨂i=1nXiDD, where {a mathematical formula}XiDD is the single variable PADD:{a mathematical formula} that associates {a mathematical formula}xi to the true branch and ({a mathematical formula}1−xi) to the false branch.
        </paragraph>
        <paragraph>
         Then, the new value {a mathematical formula}Vt+1(x→) can be “masked into” the old value function {a mathematical formula}VDDt(X→) to obtain the updated function {a mathematical formula}VDDt+1(X→) by computing {a mathematical formula}VDDt⊕((Vt+1(x→)−Vt(x→))⊗x→DD). An example is given in Fig. 16. Remember that we use DD for functions represented by ADDs or PADDs; {a mathematical formula}x→ for representing a state and {a mathematical formula}X→ for representing a vector of binary state variables.
        </paragraph>
       </section>
       <section>
        <section-title>
         factRTDP-IP sampling
        </section-title>
        <paragraph>
         We also consider the three methods described in Section 6 for choosing the value of the probability parameters, i.e., minimax_parameter_choice, predefined_parameter_choice and rand_parameter_cho- ice. Note that for the second and third methods, it is necessary to compute the vertices for the factored transition credal sets (as was done in Section 6.1). After having the values for {a mathematical formula}p→, factRTDP-IP carries out the sampling of each next state variable {a mathematical formula}Xi′ based on its CPT for the chosen action a, i.e.:{a mathematical formula} where the probabilistic distribution {a mathematical formula}P(⋅|x→,a) is taken from the leaves of the ADD returned by {a mathematical formula}ValPADDLeaves(pEvalPADD(PDD(Xi′|paa(Xi′),a),x→),p→). Note that this ADD has a single variable {a mathematical formula}Xi′ (i.e., the result of evaluating {a mathematical formula}PDD with the variable assignment {a mathematical formula}x→ and replace the probability parameters values {a mathematical formula}p→). Fig. 17 shows an example of the process for choosing the next state {a mathematical formula}x→′, given that the current state is {a mathematical formula}x→={X1=1,X2=1} and the chosen parameter values are {a mathematical formula}{p11=0, {a mathematical formula}p12=0.8, {a mathematical formula}p21=0.5, {a mathematical formula}p22=0.5, {a mathematical formula}p23=0.25, {a mathematical formula}p24=0.15}.
        </paragraph>
        <paragraph>
         The factRTDP-IP algorithm (Algorithm 6) initializes {a mathematical formula}VDD as an ADD with an admissible value function and runs trials until it achieves a goal state. For each visited state, the factRTDP-IP-Update algorithm is called (Algorithm 6, Line 16) and returns the updated value function and the parameter values which can be reused by the minimax_parameter_choice. After a greedy action (Algorithm 6, Line 19) has been chosen, the next state sampling is carried out (Algorithm 6, Line 20). From Line 23 to 25, the algorithm updates all the states in the trial path, from the end to the initial state.
        </paragraph>
        <paragraph>
         The factRTDP-IP-Update algorithm (Algorithm 7) updates the factored value function for state {a mathematical formula}x→ as follows: after “priming” the variables (Algorithm 7, Line 4) of {a mathematical formula}VDDt (by converting each {a mathematical formula}Xi into {a mathematical formula}Xi′), {a mathematical formula}QDDa is derived by computing Equation (26) in terms of PADD operations (Algorithm 7, Lines 5–7). After applying the MaxParameterOut PADD operation (Algorithm 7, Line 9) the result is a real value. The computation of {a mathematical formula}Vt+1(x→) yields a constant {a mathematical formula}Vt+1 for a known {a mathematical formula}x→ (Algorithm 7, Line 13) and then factRTDP-IP inserts this new constant {a mathematical formula}Vt+1 into the current value function {a mathematical formula}VDDt to obtain {a mathematical formula}VDDt+1 calling the method factRTDP-IP-MaskedVintoADD (Algorithm 8).
        </paragraph>
        <paragraph>
         The factRTDP-IP-Sampling algorithm (Algorithm 9) samples a next state {a mathematical formula}x→′ given a current state {a mathematical formula}x→, action a and {a mathematical formula}p→. We first choose values for the parameters {a mathematical formula}p→, using minimax_parameter_choice, predefined_parameter_choice or rand_parameter_choice. If the minimax_parameter_choice method is employed, {a mathematical formula}p→ has the same values that have been computed for the last update. If the predefined_parameter_choice method is used, {a mathematical formula}p→ is only computed once at the beginning of Algorithm 6 (Lines 7–9) by first computing the vertices of all the credal sets (stored in a hash table called CredalSetVerticesHash), and then using those vertices to generate random points. Finally, if the rand_parameter_choice is used, {a mathematical formula}p→ is computed for the tuple {a mathematical formula}〈Xi′,x→(paa(Xi′)),a〉 with {a mathematical formula}i={1,⋯,n}, where a is the current greedy action and {a mathematical formula}x→(paa(Xi′)) means the values of the parents of {a mathematical formula}Xi′ in the variable assignment {a mathematical formula}x→, i.e., the configuration of the parents of {a mathematical formula}Xi′ in the current state {a mathematical formula}x→ (Algorithm 9, Lines 5–10). Notice that the size of CredalSetVerticesHash will be the number of credal sets for the predefined_parameter_choice method and less or equal to this number for the rand_parameter_choice method, given the fact that not all the states will be visited. Thus, in the worst case scenario the size is equal to {a mathematical formula}n⁎2maxa,Xi⁡|paa(Xi)|⁎|A| (Equation (16)). Since we are considering binary variables and assume closed and convex credal sets, the number of vertices for each credal set is equal to 2. Thus, the space required by CredalSetVerticesHash is proportional to a constant times {a mathematical formula}n⁎2maxa,Xi⁡|paa(Xi)|⁎|A|.
        </paragraph>
        <paragraph>
         After defining the values for {a mathematical formula}p→ we carry out the sampling of each next state variable {a mathematical formula}Xi′ (Algorithm 9, Line 12). This is done by using the ADD (of a single variable {a mathematical formula}Xi′) returned by {a mathematical formula}ValPADDLeaves(pEvalPADD(PDD(Xi′|paa(Xi′),a),x→),p→), where we have the probabilities to do the sampling.
        </paragraph>
       </section>
      </section>
     </section>
     <section label="7.2">
      factLRTDP-IP algorithm
      <paragraph>
       The Labeled Factored RTDP-IP algorithm, called factLRTDP-IP, (Algorithm 10) is similar to the factRTDP-IP, but has two main differences: (i) in the trial termination condition (Algorithm 10, Line 14), we determine if the state {a mathematical formula}x→ is marked as solved; (ii) at the end of each trial (Algorithm 10, Lines 25–29) we check if each state in the trial can be labeled as solved through the factCheckSolved-IP procedure [8] (this is also done in a factored way as in [33]).
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      In this section, we empirically evaluate the proposed asynchronous algorithms, RTDP-IP, LRTDP-IP, factRTDP-IP and factLRTDP-IP, as opposed to SPUDD-IP [23], which is a synchronous algorithm that produces optimal policies (see Section 5.3). The algorithms were applied in three well-known planning domains: SysAdmin, proposed by Guestrin et al. (2003); Navigation and Triangle Tire world from the International Probabilistic Planning Competition (IPPC). SSP MDP-IP problems were generated for these domains, and modified by parameterizing the probability transition function and adding a set of constraints, as described below.
     </paragraph>
     <paragraph>
      In SysAdmin[30], there are n computers {a mathematical formula}c1,…,cn connected via a given topology (unidirectional ring, bidirectional ring and independent bidirectional rings) and {a mathematical formula}n+1 actions: {a mathematical formula}reboot(c1),…,reboot(cn) and notreboot (i.e., no machine is rebooted). Let state variable {a mathematical formula}xi denote whether computer {a mathematical formula}ci is up and running ({a mathematical formula}xi=1) or not ({a mathematical formula}xi=0). Let {a mathematical formula}Conn(cj,ci) denote a connection from {a mathematical formula}cj to {a mathematical formula}ci. Formally, the transition probabilities have the following form:{a mathematical formula} The probability parameters {a mathematical formula}pi1 and {a mathematical formula}pi2 are restricted by {a mathematical formula}0.85+pi2≤pi1≤0.95. This domain has many transitions with imprecise probabilities and is a dense domain since most states are reachable in one step. There is no goal state, thus this is an infinite horizon MDP-IP problem. To convert this problem to an SSP MDP-IP problem, we used the conversion described in [7], i.e., we added a goal state g and the transition probability P was transformed into {a mathematical formula}P′ as following:{a mathematical formula} Rewards were transformed into positive cost. Thus, the cost is 0 for the goal state and {a mathematical formula}C(x→)=n−∑i=1nxi for the others. The initial state is a single state where half of the computers are running and we consider the discount factor {a mathematical formula}γ=0.9 for the transformation.
     </paragraph>
     <paragraph>
      In Navigation[16] (from IPPC 2011), a robot must walk in a grid of {a mathematical formula}n×m cells and find a path to reach a goal cell, while avoiding dangerous cells that can make it disappear with a certain probability. The robot can walk across one cell per time in four directions (north, south, east and west) or can stay in the same place (noop). The factored version is given by {a mathematical formula}n×m variables for representing if the robot is in the cell. The action of walking in any direction is deterministic but there is a probability that the robot will disappear in dangerous cells which is given by the probability parameter {a mathematical formula}pi subject to: {a mathematical formula}bj≤pi≤bk+0.1, where {a mathematical formula}bj and {a mathematical formula}bk grow for cells near the goal. The location of the initial and goal cell are, respectively, {a mathematical formula}[1,m] and {a mathematical formula}[n,m]. The safe cells are the cells in the row 1 and row n and the cells in the column 1. The cost is 0 when the robot is in the goal cell, otherwise it is 1. To reach the goal in this domain, the robot must walk in the longest path, i.e., walk in the cells in the border of the grid, where all cells are safe. It can be regarded as a sparse domain since, for any domain action, the number of reachable states in one step is a constant for all instances.
     </paragraph>
     <paragraph>
      In Triangle Tireworld[36] (from IPPC 2005), the aim is to move a car from an initial location to a goal location through a sequence of roads. Each road connects two locations. The factored problem has one variable to indicate if the car has a spare tire, one to indicate if the car is flat-tired and n variables, one per location, to show if the car is in this location. There is a probability that the car can become flat-tired when moving from one location to another. In this situation the flat tire can be replaced with a spare tire. In addition, in some locations the car can be loaded with an extra spare tire to be used in the future. The probability for the parameter {a mathematical formula}pi of an SSP MDP-IP problem for the car to become flat-tired is subject to the constraint {a mathematical formula}bj≤pi≤bk+0.1, where {a mathematical formula}bj and {a mathematical formula}bk are parameters, with high values in the cells close to the goal; the cost is 0 when the car is in the goal, otherwise it is 1. Like in Navigation domain, the car can reach the goal location safely moving in the longest path, where all locations have an extra spare to avoid the car be flat-tired with no spare in the path. This domain is also considered to be a sparse domain, i.e., the number of reachable states in one step is a constant.
     </paragraph>
     <paragraph>
      For all the experiments we used a virtual machine running with 2 processors at 3.40 GHz and 5 GB of memory. In the case of SPUDD-IP, LRTDP-IP and factLRTDP-IP, we set {a mathematical formula}ϵ=0.01 (convergence error) as the residual error used for all domains. All runs that did not complete in two hours or lacked enough memory to solve the problem were marked with DNF (Did Not Finish).
     </paragraph>
     <paragraph>
      Since our Navigation and Triangle Tireworld domains have avoidable dead ends that are easy to be detected (dead-ends in which no action is available), we also implement a dead end detection procedure for all the algorithms. In RTDP-like algorithms a trial is interrupted when a dead-end is reached and its value is updated to ∞. In CheckSolved-IP procedure, if a dead-end is found, we also update its value to ∞ and ignore that state in the CheckSolved-IP's search.
     </paragraph>
     <paragraph>
      The proposed algorithms were analyzed in terms of both the initial state convergence rate and convergence time. We also analyzed the algorithms w.r.t. the number of calls to a multilinear solver.
     </paragraph>
     <section label="8.1">
      <section-title>
       The initial state convergence rate
      </section-title>
      <paragraph>
       Analyzing the convergence behavior of SPUDD-IP, RTDP-IP, LRTDP-IP, factRTDP-IP and factLRTDP-IP, we examined the value of the initial state {a mathematical formula}s0 during the time, until convergence, for three planning problems: instance 18 of Navigation; 17 of Triangle Tireworld; and instance 6 of SysAdmin.{sup:4} Each of these problems corresponds to the largest instance of the corresponding domain for which all of the algorithms were able to return a policy (as will be seen in Section 8.2).
      </paragraph>
      <paragraph>
       We ran the algorithms to assess the three methods of choosing the probability for sampling the next state, i.e., minimax_parameter_choice, predefined_parameter_choice and rand_parameter_choice methods. Intuitively, we expected that using the minimax_parameter_choice method could cause {a mathematical formula}V(s0) to converge faster. However, in each of the three methods, {a mathematical formula}V(s0) converges at the same rate. In this section we only show the results for the minimax_parameter_choice method and leave comparisons of these methods in terms of time to the next section.
      </paragraph>
      <paragraph>
       In Fig. 18 it can be seen that for sparse domains (Navigation and Triangle Tireworld), asynchronous algorithms (e.g., with minimax_para- meter_choice method) perform much better than SPUDD-IP. For the Navigation instance it is clear that RTDP-IP, LRTDP-IP, factRTDP-IP and factLRTDP-IP quickly reach a near-optimal value in the first 4 seconds, while SPUDD-IP takes more than 5000 seconds. A similar behavior can be observed in the Triangle Tireworld instance. However, for the SysAdmin instance (Fig. 18, bottom), which is a dense domain, SPUDD-IP has a better convergence rate than the asynchronous algorithms, RTDP-IP, LRTDP-IP, factRTDP-IP and factLRTDP-IP. It should be noted that in this domain all states are reachable, as a result of probabilistic exogenous events, and hence asynchronous algorithms are unable to take advantage of the initial state information. In this case, asynchronous algorithms consume more time updating state by state than SPUDD-IP which updates all the states at each step. Moreover, when labeling solved states, LRTDP-IP and factLRTDP-IP exploit the greedy graph structure, which can be very costly when the graph is dense. In fact, in a dense domain, the CheckSolved procedure just wastes time, since all the states may converge together. Note that since SPUDD-IP performs a synchronous dynamic programming, {a mathematical formula}V(s0) changes uniformly (see the SPUDD-IP curve at the bottom of Fig. 18) at each iteration, while, for the asynchronous algorithms, the value of {a mathematical formula}s0 may not change during certain time intervals (depending on which states were updated during the trials).
      </paragraph>
      <paragraph>
       Since LRTDP-IP and factLRTDP-IP converge faster than RTDP-IP and factRTDP-IP for all the domains and instances, in the rest of our analysis we only include the results of LRTDP-IP and factLRTDP-IP.
      </paragraph>
     </section>
     <section label="8.2">
      <section-title>
       Convergence time per problem instance
      </section-title>
      <paragraph>
       Fig. 19 shows the global convergence time of SPUDD-IP, LRTDP-IP and factLRTDP-IP for different instances of the Navigation, Triangle Tireworld and SysAdmin domains. We also compare the convergence time for the three methods for sampling next state in factLRTDP-IP, i.e., the minimax_parameter_choice method (abbreviated as minimax), the predefined_parameter_choice (pre) and rand_ parameter_choice (rand).
      </paragraph>
      <paragraph>
       For sparse domains such as Navigation and Triangle Tireworld, the asynchronous algorithms LRTDP-IP and factLRTDP-IP show up to three orders of magnitude speedup unlike the synchronous dynamic programming approach, SPUDD-IP. Additionally, while SPUDD-IP is not able to return a policy for instances with more than 20 variables, LRTDP-IP and factLRTDP-IP return optimal policies for instances with up to 121 variables, in the Navigation domain and for instances up to 80 variables in the Triangle Tireworld domain. As expected, this happens because in these domains the LRTDP-IP and factLRTDP-IP algorithms only perform the Bellman backup in the set of states reachable from the initial state, while SPUDD-IP has to update all the states at each iteration. Note also that LRTDP-IP shows up to 2 times speedup in comparison to factLRTDP-IP, so the difference is not significant.
      </paragraph>
      <paragraph>
       We also show that there is no significant difference in terms of time for the minimax_parameter_choice, predefined_parameter_choice and rand_parameter_ choice methods for the three domains we have analyzed. An explanation is that for these domains, {a mathematical formula}maxa,Xi⁡|paa(Xi)|=2 or 3 and {a mathematical formula}|K|≤n⁎23⁎|A| (Equation (16)). Notice that there is a small number of credal sets and the number of vertices of each credal set is up to 2 (since we are working with boolean variables). Thus, there is no significant extra cost involved in computing the credal set vertices or generating random points using Equation (22) for the predefined_parameter_choice and rand_parameter_choice methods, which causes no difference in time when sampling in compliance with minimax_parameter_choice, predefined_parameter_choice or rand_parameter_choice methods. Thus we believe that for domains with a large variable dependency and a large number of vertices for the credal sets, the rand_parameter_choice method might show a worse performance.
      </paragraph>
      <paragraph>
       In a dense domain such as SysAdmin, the results are not so promising. It is clear that LRTDP-IP and factLRTDP-IP take more time to converge (approximately 4×) than SPUDD-IP. As explained in the previous section, in a dense domain where the convergence depends on all the state values, the synchronous dynamic programming algorithm achieves a better performance.
      </paragraph>
     </section>
     <section label="8.3">
      <section-title>
       Number of calls to a multilinear solver
      </section-title>
      <paragraph>
       In showing the relationship between the number of calls to a multilinear solver and the overall solution time (convergence time), a comparison was made between SPUDD-IP, LRTDP-IP and factLRTDP-IP with the minimax_parameter_choice method to choose the values for each {a mathematical formula}pi for different instances of the Triangle Tireworld domain.
      </paragraph>
      <paragraph>
       Fig. 20 shows that for each of the analyzed approaches, there is a strong correlation between the running time and the number of calls to a multilinear solver which suggests that the number of calls dominates the running time. Note that the number of calls to a multilinear solver of SPUDD-IP grows faster than the number of calls to a multilinear solver of the LRTDP-IP and factLRTDP-IP algorithms. This is because SPUDD-IP updates all the states while LRTDP-IP and factLRTDP-IP only update the reachable states and the number of calls to a multilinear solver is proportional to the number of updates.
      </paragraph>
     </section>
    </section>
    <section label="9">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      As mentioned in Section 3, a particular sub-class of MDP-IP is the Bounded-parameter Markov Decision Process (BMDP)[29], where the probabilities and rewards are specified by intervals over a set of enumerated states. Algorithms to solve an (enumerated) BMDP can find an optimal policy without requiring expensive optimization techniques, although they have some limitations: they do not deal either with the general constraints or factored inputs. Remember that the translation of the problems described in factored forms into enumerated MDP-IPs result in polynomial expressions in the transition probabilities.
     </paragraph>
     <paragraph>
      Another sub-class of MDP-IPs is the Markov Decision Process with Set-valued Transitions (MDP-ST)[49], where probability distributions are given for finite sets of states. In this model there are two varieties of uncertainty: a probabilistic selection of a reachable set and a non-deterministic choice of a successor state from the reachable set. Algorithms to solve this problem can also find an optimal policy without requiring expensive optimization techniques since the Bellman principle for MDP-STs can be simplified to a great extent [49].
     </paragraph>
     <paragraph>
      Fig. 21 shows the relationship between MDP, BMDP, MDP-ST and MDP-IP. Notice that BMDP and MDP-ST do not have the same representational power, i.e., some MDP-ST problems cannot be reduced to BMDP, and vice versa. Note also that since BMDPs and MDP-STs are special cases of MDP-IPs, we can represent them as MDP-IPs; thus the algorithms for MDP-IPs clearly apply to both BMDPs and MDP-STs [49].
     </paragraph>
     <paragraph>
      Alternative frameworks that consider imprecise transition models that can be captured by MDP-IPs are Contingent planning [32] and Possibilistic approaches [41], [25], even though these models are not probabilistic. Contingent planning [32] is the task of generating a conditional plan when there is uncertainty about the initial state and non-deterministic action effects, but with the ability to sense some aspects of the current state. Possibilistic approaches [42], [41], [25] take a different view about transition uncertainty that is modeled as qualitative possibility distributions over S instead of probability distributions.
     </paragraph>
     <paragraph>
      Although there is no work on factored asynchronous algorithms for SSP MDP-IPs, there are a few studies in the literature on factored asynchronous algorithms for SSP MDPs: sRTDP [27], symbolic LAO* [26], factRTDP [33], factLRTDP [33] and factBRTDP [22]. While sRTDP [27] updates an abstract state (a group of similar states), factRTDP and factLRTDP [33] update a single state in the trial-based simulations. The factBRTDP algorithm is the factored version of the Bounded RTDP algorithm [37] and it is not as efficient as factLRTDP since it is very costly to update both a lower and upper bound value function. The factored algorithms proposed in this paper are based on the algorithms factRTDP and factLRTDP [33].
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>