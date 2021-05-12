<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Online belief tracking using regression for contingent planning.
   </title>
   <abstract>
    In online contingent planning under partial observability an agent decides at each time step on the next action to execute, given its initial knowledge of the world, the actions executed so far, and the observation made. Such agents require some representation of their belief state to determine which actions are valid, or whether the goal has been achieved. Efficient maintenance of a belief state is, given its potential exponential size, a key research challenge in this area. In this paper we develop the theory of regression as a useful tool for belief-state maintenance. We provide a formal description of regression, discussing various alternatives and optimization techniques, and analyze its space and time complexity. In particular, we show that, with some care, the regressed formula will contain variables relevant to the current query only, rather than all variables in the problem description. Consequently, under suitable assumptions, the complexity of regression queries is at most exponential in its contextual width. This parameter is always upper bounded by Bonet and Geffner's width parameter, introduced in their state-of-the-art factored belief tracking (FBT) method. In addition, we show how to obtain a poly-sized circuit representation for the online regression formula even with non-deterministic actions. We provide an empirical comparison of regression with FBT-based belief maintenance, showing the power of regression for online belief tracking. We also suggest caching techniques for regression, and demonstrate their value in reducing runtime in current benchmarks.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Agents that act in the real world are often limited to partial knowledge about the world, obtained through their sensors. This is typically known as planning under partial observability. Agents that plan in a partially observable domain, typically maintain some representation of their state of knowledge online. A complete description of the agent's state of knowledge, consisting of the set of possible states of the world (or a probability distribution over possible states, in the probabilistic case), is called the agent's belief state. Many planners for partially observable domains search directly in the space of belief states, known as the belief space.
     </paragraph>
     <paragraph>
      Maintaining and updating an explicit belief state can be expensive because the number of possible states of the world can be exponential in the description size of a single state, i.e. the number of state variables. Thus, directly maintaining sets of states becomes unmanageable both space and time-wise as the problem grows. To alleviate this, methods that maintain a more compact, symbolic description of the set of possible states have been developed, such as methods based on BDDs [3], prime-implicates, CNF, and DNF [27]. Unfortunately, symbolic representations also have an exponential worst-case description, and when not, may be expensive to update. Furthermore, every representation that was suggested thus far, while being very compact for certain benchmark problems, demonstrated the worst-case performance on other benchmarks.
     </paragraph>
     <paragraph>
      Still, planning algorithms can benefit from an important observation [15] – during planning and plan execution it is sufficient for the agent to answer only two types of queries with respect to a belief state: has the goal been achieved? and for each action, is this action applicable? That is, whether the action's precondition is satisfied in the belief state.
     </paragraph>
     <paragraph>
      The regression-based method we study takes a lazy approach to belief maintenance, maintaining only the initial belief state, the set of actions executed, and sensed observations. This approach is similar in spirit to the Situation Calculus [16] where a state is represented in terms of the initial state and sequence of actions. Using this information, one could regress the conditions required currently (e.g., p) towards the initial belief state. If the regressed condition is implied by the initial state then we know that p holds now. Otherwise, there exists some current possible state that does not satisfy p.
     </paragraph>
     <paragraph>
      In earlier work [8], we implemented this approach within an online contingent planner and showed that, empirically, the regression-based method, coupled with some caching, is highly efficient on current benchmark problems. In this paper we provide detailed description and analysis of regression-based belief-state maintenance, focusing on online belief maintenance – which is sometimes called filtering[2], [25]. In online belief maintenance, the agent, after having performed a sequence of actions and observing some observations, must determine whether the goal or a precondition literal l holds. This is a somewhat simpler task than offline belief maintenance, where the agent must consider arbitrary hypothetical sequences, and for each such sequence, not only determine the resulting belief state, but also, determine whether this sequence is possible.
     </paragraph>
     <paragraph>
      There is a long line of research on regression in the area of KR (e.g., [21], [13], [24]). Regression is also a key component of the circuit-based filtering approach proposed by Shahaf and Amir [25]. Yet, none of the previous regression-based methods have been shown to be empirically efficient or competitive for modern, state-space planning, whereas the method we describe has been implemented as part of a number of state-of-the-art contingent planners [7], [8].
     </paragraph>
     <paragraph>
      Our first contribution is to extend Rintanen's formalism of regression [22] to handle observations, allowing us to use regression for online belief-state queries in domains with partial observability. Exploiting our focus on online belief maintenance, we obtain a method that is on par with the state of the art, as our empirical evaluation shows. On the theoretical side, we exploit the notion of width [19], [5], [6] to provide a tighter, width-based bound on the complexity of regression. We show that regression enjoys similar, and potentially better, complexity bounds to those of the state-of-the-art factored belief tracking (FBT) method [6]. FBT maintains an explicit model of a factored belief state which utilizes a notion of relevant variables. We show that one can ensure that the regression formula, too, will contain relevant variables only. This occurs naturally when regressing actions, but requires more care for regression of observations. Moreover, the worst-case complexity of regression depends only on the actions that actually appear in the sequence, as opposed to the entire set of actions in the progression-based FBT, potentially leading to a lower width notion, which we call contextual width.
     </paragraph>
     <paragraph>
      Then, we use a well-known technique to compile non-deterministic actions into deterministic actions. Now, with deterministic actions only, one can easily update the initial state formula with the regression of each observation once, ignoring these observations afterward while maintaining completeness. This compilation leads to a surprising result – the existence of a poly-sized circuit representation of the regression formula (assuming polynomial horizon), which typically requires exponential space in other forms. Earlier work considered this to be possible only for domains with deterministic actions.
     </paragraph>
     <paragraph>
      Next, we empirically evaluate our method, comparing the belief update and the query time of the regression method to approximate FBT, showing regression to be very efficient, scaling up similarly. We also empirically analyze the effect of simple caching – the main optimization to regression we suggest. We conclude with a discussion of related work.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Background
     </section-title>
     <paragraph>
      We begin by defining the contingent planning model and its specification language, following in most places the definitions of Bonet and Geffner (BG henceforth) [6]. We then review the various concepts of problem width introduced by Bonet and Geffner.
     </paragraph>
     <section label="2.1">
      <section-title>
       Model
      </section-title>
      <paragraph>
       We focus on contingent planning problems with sensing. A contingent planning problem is a tuple of the form {a mathematical formula}〈S,bI,SG,A,Tr,Ω,O〉, where S is a set of states, {a mathematical formula}bI⊆S is the set of possible initial states, also called the initial belief state, {a mathematical formula}SG⊆S is the set of goal states, A is a set of action symbols, and Tr is a transition function, such that {a mathematical formula}Tr(s,a)⊆S is the set of states that can be reached by applying a in state s, Ω is a set of observation symbols, and {a mathematical formula}O(a,s′)∈Ω is the observation obtained when {a mathematical formula}s′ is reached following the application of a. Without loss of generality, we assume an observation follows each action.
      </paragraph>
      <paragraph>
       In this paper we allow for non-deterministic outcomes of actions, but restrict ourselves to deterministic observations. Semantically, this is not a limiting assumption, as non-deterministic observations can be compiled away using non-deterministic actions; If {a mathematical formula}s′∈Tr(a,s) and {a mathematical formula}O(a,s′)={o1,o2}, copy {a mathematical formula}s′ into two new states {a mathematical formula}s1′,s2′ such that {a mathematical formula}s1′,s2′∈Tr(a,s). Define {a mathematical formula}O(a,s1′)=o1 and {a mathematical formula}O(a,s2′)=o2. Transitions from {a mathematical formula}s1 and {a mathematical formula}s2 are identical to those from s.
      </paragraph>
      <paragraph>
       At each point in execution, there is a set of possible states, called the current belief-state. The initial belief state – the set of initially possible states – is denoted {a mathematical formula}bI. If b is the current belief state, a is executed, and o is observed then the resulting belief state {a mathematical formula}τ(b,a,o) is defined as:{a mathematical formula} That is, states {a mathematical formula}s′ that can result from the execution of a in a state in b, such that o is observed in {a mathematical formula}s′ if a was executed. We extend this notation to a sequence {a mathematical formula}a¯,o¯ of actions and observations recursively:{a mathematical formula} As an observation always follows an action, {a mathematical formula}|a¯|=|o¯|.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Language
      </section-title>
      <paragraph>
       A contingent planning problem is specified as a tuple {a mathematical formula}〈P,A,φI,φG〉. P is a set of atomic boolean propositions, {a mathematical formula}A is the set of actions, {a mathematical formula}φI is a propositional formula over P in conjunctive normal form that represents the initial state, and {a mathematical formula}φG is a propositional formula over P that represents the goal condition.
      </paragraph>
      <paragraph>
       A state of the world s assigns a truth value to all elements of P. The initial belief state, {a mathematical formula}bI, consists of the set of states that satisfy {a mathematical formula}φI, i.e. {a mathematical formula}bI={s:s⊨φI}. The goal is to achieve a belief state in which {a mathematical formula}φG holds, i.e., {a mathematical formula}b⊨φG.
      </paragraph>
      <paragraph>
       A deterministic action, {a mathematical formula}a∈A, is a triple: {pre(a), effects(a), obs(a)}. We shall use the common {a mathematical formula}a(s) to denote {a mathematical formula}Tr(s,a) in the deterministic case. The action precondition, pre(a), is a propositional formula. The action effects, effects(a), is a set of pairs, {a mathematical formula}(ca,l,l), denoting conditional effects, where {a mathematical formula}ca,l is a propositional formula and l is a literal. For notational convenience, we assume that only one condition {a mathematical formula}ca,l exists for every action a and literal l. In practice, {a mathematical formula}ca,l=false for most literals l, i.e., l is typically not a possible conditional effect of a, and this pair can be omitted. obs(a) is also a set of pairs, {a mathematical formula}{(ωa,o,o)|o∈Ω}, where {a mathematical formula}ωa,o is a propositional formula over P and {a mathematical formula}o∈Ω. Formally, Ω is specified implicitly as the set of observation symbols appearing in actions in {a mathematical formula}A. Thus, {a mathematical formula}o=O(a,s′) iff {a mathematical formula}s′⊨ωa,o.
      </paragraph>
      <paragraph>
       Formally, an observation always occurs following the execution of an action. Thus, for every {a mathematical formula}a∈A, {a mathematical formula}⋁o∈Ωωa,o≡true. Furthermore, sensing is deterministic and therefore {a mathematical formula}ωa,o for different observations must be mutually exclusive. In practice, not all actions are followed by a meaningful observation. This can be captured by a special, uninformative, no-obs observation. If a is followed by a no-obs, then {a mathematical formula}ωa,no-obs=true, i.e., it is the only observation possible following a. As no-obs can be treated like any other observation, we make no special distinction between it and “real” observations.
      </paragraph>
      <paragraph>
       For deterministic actions, if {a mathematical formula}s⊭pre(a) then {a mathematical formula}a(s) is undefined. Otherwise, {a mathematical formula}a(s) satisfies l iff either (i) {a mathematical formula}s⊨ca,l or (ii) {a mathematical formula}s⊨l∧¬ca,¬l.
      </paragraph>
      <paragraph>
       We assume that the conditions are mutually exclusive, i.e., for every atomic proposition p and action a: no state in which both {a mathematical formula}ca,p and {a mathematical formula}ca,¬p hold is reachable. That is, an action a executed in a reachable state s cannot make both p and ¬p true.
      </paragraph>
      <paragraph>
       A non-deterministic action is defined as a set of deterministic actions, {a mathematical formula}a={a1,…,am}, one of which is non-deterministically selected when a is executed. The actions in this set are restricted to have an identical precondition – as the applicability of the action does not depend on the outcome, and identical observations – as the observation depends on the identity of the action, which in this case is the non-deterministic a, and the outcome state. Formally, we require that for all {a mathematical formula}1≤i,j≤m, {a mathematical formula}pre(ai)=pre(aj) and {a mathematical formula}obs(ai)=obs(aj). As in the deterministic case, if {a mathematical formula}s⊭pre(a) then {a mathematical formula}a(s) is undefined. The set of states that are possible following the execution of a in s is thus {a mathematical formula}a(s)=a1(s)∪⋯∪am(s). However, each time a is executed, exactly one of its elements, {a mathematical formula}ai occurs, and the actual outcome is {a mathematical formula}ai(s).
      </paragraph>
      <paragraph>
       As we explained earlier, semantically, non-deterministic observations are not a limitation, and the approach we use to compile them away applies here as well. A simple scheme would be to add {a mathematical formula}log⁡(|Ω|) new variables to the state, and use them to encode the observation as part of the state. The values of these variables can be non-deterministically determined, but the agent would deterministically observe their value. These new variables do not influence the transition to a new state. Of course, for specific domains, less generic methods could be more efficient.
      </paragraph>
      <paragraph label="Example 1">
       As a running example, consider the Localize problem (Fig. 1), where an agent in a grid must reach the top-right cell. In our examples, for ease of exposition, we will abuse notation and allow conditional effects of the form {a mathematical formula}(c,e) where c is a formula and e is a conjunction of literals.The agent moves deterministically, and has a sensor that observes nearby walls. In this domain we have 4 movement actions, each with conditional effects modifying the agent location. For example, the move-up action would have a conditional effect {a mathematical formula}(at3,1,¬at3,1∧at3,2), denoting that if the agent was at {a mathematical formula}x=3,y=1 prior to the action, it is at cell {a mathematical formula}x=3,y=2 following the action. The sensor activation action checking has conditional effects for specifying nearby walls. For example, it would contain a conditional effect {a mathematical formula}(at3,1,¬wallup∧walldown∧wallright∧¬wallleft). There are 2 observations, RED denoting a wall, and GREEN denoting no wall, and 4 sensing actions, with {a mathematical formula}ωsensed,RED=walld and {a mathematical formula}ωsensed,GREEN=¬walld, {a mathematical formula}d∈{up,down,left,right}.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Online belief tracking
      </section-title>
      <paragraph>
       In some applications belief tracking may require consistent maintenance of the current belief state of the agent. For planning algorithms we can focus on a narrower scope, which requires only answering specific queries concerning the set of possible states.
      </paragraph>
      <paragraph>
       We distinguish between the case of belief tracking for offline planning algorithms and online planning algorithms. In offline planning, given a sequence of actions {a mathematical formula}a¯ and a sequence of observations {a mathematical formula}o¯, the agent must know whether the sequence is executable starting from {a mathematical formula}bI. That is, the agent must determine whether the sequence is executable – technically, whether {a mathematical formula}τ(bI,a¯,o¯) is non-empty – and whether the goal is satisfied following the sequence, i.e., whether {a mathematical formula}τ(bI,a¯,o¯)⊨φG.
      </paragraph>
      <paragraph>
       In online planning, where an agent computes at each step the next action to perform, the task is slightly different. The agent has already executed a sequence of actions, {a mathematical formula}a¯, successfully, and sensed a sequence {a mathematical formula}o¯ of observations (i.e., the execution history). This immediately implies that {a mathematical formula}τ(bI,a¯,o¯) is non-empty, and so the agent only needs to query, for a given precondition or goal formula ϕ whether {a mathematical formula}τ(bI,a¯,o¯)⊨ϕ.
      </paragraph>
      <paragraph>
       Computationally, the two problems are closely related. One can check whether a sequence of actions and observations is possible in a belief state by checking whether the preconditions of each action hold following the prefix of actions and observation that precedes it, and whether the condition {a mathematical formula}ωa,o holds for each action and sensed observation following the relevant prefix. Checking the applicability of an action requires one online belief-tracking query for each of its preconditions. However, checking whether an observation is possible could be complex, as {a mathematical formula}ωa,o is not necessarily a conjunction. Thus, one can answer an online belief-tracking query using one offline query, but not necessarily vice versa.
      </paragraph>
      <paragraph>
       Finally, an important advantage of online belief tracking, discussed in Section 6, is that it allows us to cheaply transform non-deterministic actions into deterministic actions. We need only add a number of new variables that is linear in the number of non-deterministic actions executed so far. Compiling non-deterministic actions in the offline case is problematic, as one new variable must be added for every potential action instance. This usually forces researchers to place some limitation, e.g., on the number of instances executed from each action, or requires that effects of different instances of the same action be correlated.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Relevance and width
      </section-title>
      <paragraph>
       Bonet and Geffner [6] introduce a measure of the complexity of belief tracking, called problem width. Essentially, it is the number of variables that must be maintained when answering a belief tracking query regarding the value of some state variable p.
      </paragraph>
      <paragraph label="Definition 1">
       BGp is an immediate cause of a variable q, written {a mathematical formula}p∈Ca(q) iff {a mathematical formula}p≠q and p occurs (possibly negated) in the body {a mathematical formula}ca,l of a conditional effect {a mathematical formula}(ca,l,l) of some action a, and {a mathematical formula}l∈{q,¬q}. For an observation o, {a mathematical formula}p∈Ca(o) is similarly defined, where {a mathematical formula}ca,l is replaced by {a mathematical formula}ωa,o.
      </paragraph>
      <paragraph label="Definition 2">
       BGp is causally relevant to q if {a mathematical formula}p=q or {a mathematical formula}p∈Ca(q) or {a mathematical formula}p∈Ca(r) and r is causally relevant to q.
      </paragraph>
      <paragraph label="Definition 3">
       BGp is initially relevant to q if p and q appear in the same clause in {a mathematical formula}φI.{sup:1}
      </paragraph>
      <paragraph label="Definition 4">
       BG{a mathematical formula}o∈O is evidentially relevant to q if q is causally relevant to o.
      </paragraph>
      <paragraph label="Definition 5">
       BGp is relevant to q if p is causally, evidentially, or initially relevant to q, or if p is evidentially, causally or initially relevant to r, and r is relevant to q.
      </paragraph>
      <paragraph>
       Intuitively, the variables relevant to p are variables whose value could impact the value of p in the future because their value determines whether p will be a conditional effect of some action or not; or because these variables affect our ability to make an observation that will revise our belief regarding whether p holds or not.
      </paragraph>
      <paragraph label="Definition 6">
       BGThe width of a variable p, {a mathematical formula}w(p) is the number variables relevant to p: {a mathematical formula}w(p)=|{q|q is relevant to p}|.
      </paragraph>
      <paragraph label="Definition 7">
       BGThe width of a planning problem {a mathematical formula}〈P,A,φI,φG〉 is max{{a mathematical formula}w(p)|p∈P, and p appears in the goal or a precondition of some action a}.
      </paragraph>
      <paragraph>
       Computing the relevant variables is a simple low-order poly-time procedure.
      </paragraph>
      <paragraph label="Definition 9">
       The notion of causal width will later become helpful: BGThe causal width of a variable p, {a mathematical formula}wc(p) is the number variables that are causally relevant to p: {a mathematical formula}wc(p)=|{q|q is causally relevant to p}|.BGThe causal width of a planning problem {a mathematical formula}〈P,A,φI,φG〉 is max{{a mathematical formula}wc(p)|p∈P is an observed variable or p appears in the goal or a precondition of some action a}.
      </paragraph>
      <paragraph label="Example 2">
       In the Localize problem, the move-up action has a conditional effect {a mathematical formula}(at3,2,at3,3). Hence, {a mathematical formula}at3,2 is an immediate cause of {a mathematical formula}at3,3. The action has another conditional effect {a mathematical formula}(at3,1,at3,2), making {a mathematical formula}at3,1 causally relevant to {a mathematical formula}at3,3.The checking action contains a conditional effect {a mathematical formula}(at3,3,wallup), making {a mathematical formula}at3,3 causally relevant to {a mathematical formula}wallup. As {a mathematical formula}ωsenseup,RED=wallup, {a mathematical formula}wallup is an immediate cause of the observation RED, and {a mathematical formula}at3,3 is causally relevant to RED. As such, RED is evidentially relevant to {a mathematical formula}at3,3.Furthermore, as the observation {a mathematical formula}GREEN is also similarly relevant for {a mathematical formula}at3,2, and {a mathematical formula}at3,2 is relevant for {a mathematical formula}at3,3, {a mathematical formula}GREEN is also evidentially relevant for {a mathematical formula}at3,3.
      </paragraph>
      <paragraph>
       In many problems some variables are always known, or determined – their values are known initially and change only deterministically, conditioned on the value of other determined variables. This means that at each time point during the execution of a valid sequence of actions, their value is the same in all possible states. Thus, one can easily track their value independently of all other variables, costing linear time and space for each update. For the purpose of our analysis of belief tracking, like Bonet and Geffner, we ignore these variables.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Regression
     </section-title>
     <paragraph>
      Regression is the process of answering queries concerning the current state, by reasoning backwards through a sequence of actions and observations, combined with a description of the initial state. The basis of regression operations is the substitution of a variable by an expression that describes its new value. This was used in the assignment axioms of the Hoare calculus [14] and later by Dijkstra [10] for computing weakest preconditions.
     </paragraph>
     <paragraph>
      In the area of planning, we build on two relevant lines of work on regression: Rintanen [22] and Shahaf and Amir [25] offer theoretically well-founded and practical tools for the use of regression in planning. Rintanen provides an efficient, theoretically sound definition for the regression formula in the context of state-space planning without sensing actions. Shahaf and Amir focus on filtering, which fits well with our online perspective, providing an efficient (polynomial) circuit representation for the regression formula. This is to be contrasted with the standard representation in which the formula's size can grow exponentially with the number of regression steps. However, it should be noted that the SAT-based encoding Ferraris and Giunchiglia [12] used by CFF Hoffmann and Brafman [15] is polynomial, too.
     </paragraph>
     <paragraph>
      We now review Rintanen's formalization of regression and extend it to address observations. First, we define the applicability of actions. Next, we define regression over a single action with no observation, and then extend the results to regression over an observation. Finally, we discuss regression over a sequence of actions and observations.
     </paragraph>
     <section label="3.1">
      <section-title>
       Applicability
      </section-title>
      <paragraph>
       An action is applicable in state s if s satisfies its preconditions, i.e., {a mathematical formula}s⊨pre(a). An action is applicable in a set of states S if {a mathematical formula}∀s∈S,s⊨pre(a), denoted {a mathematical formula}S⊨pre(a). An action a is applicable given the initial belief state {a mathematical formula}bI and an action–observation sequence {a mathematical formula}a¯,o¯ if a is applicable in {a mathematical formula}τ(bI,a¯,o¯). Finally, {a mathematical formula}a¯=a1,…,an;o¯=o1,…,on is applicable in a belief state b iff {a mathematical formula}ai is applicable in {a mathematical formula}τ(b,a1,…,ai−1,o1,…,oi−1), for every {a mathematical formula}i=1,…,n.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Regression without observations
      </section-title>
      <paragraph>
       Let ϕ be a propositional formula and a a deterministic action. Recall that {a mathematical formula}ca,l is the condition under which l is an effect of a, and that {a mathematical formula}a(s) satisfies l iff either {a mathematical formula}s⊨ca,l or {a mathematical formula}s⊨l∧¬ca,¬l. Hence, following Rintanen [22], we define the regression of ϕ with respect to a as:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       The second equation may seem ambiguous, but as we assume that {a mathematical formula}ca,l→¬ca,¬l in all reachable beliefs, then {a mathematical formula}¬(ca,l∨(l∧¬ca,¬l))≡ca,¬l∨(¬l∧¬ca,l).
      </paragraph>
      <paragraph>
       Clearly, all variables that appear in {a mathematical formula}rga(ϕ) are relevant to some primitive proposition that appears in ϕ.
      </paragraph>
      <paragraph label="Example 3">
       In the Localize problem, let us regresses the formula {a mathematical formula}ϕ=at3,2 through the move-up action. The precondition of move-up is {a mathematical formula}¬wallup. There is one condition in move-up that adds {a mathematical formula}at3,2, {a mathematical formula}(at3,1,¬at3,1∧at3,2), and there is one condition that removes it, {a mathematical formula}(at3,2,¬at3,2∧at3,3). Thus, the regression is {a mathematical formula}¬wallup∧(at3,1∨(at3,2∧¬at3,2)). Simplifying, we get {a mathematical formula}¬wallup∧at3,1.
      </paragraph>
      <paragraph label="Lemma 1">
       The regression of a compound formula can be decomposed:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}(ϕ1∧ϕ2)r(a)≡(ϕ1)r(a)∧(ϕ2)r(a)
       </list-item>
       <list-item label="2.">
        {a mathematical formula}(ϕ1∨ϕ2)r(a)≡(ϕ1)r(a)∨(ϕ2)r(a)
       </list-item>
       <list-item label="3.">
        {a mathematical formula}(¬ϕ)r(a)≡¬(ϕr(a))
       </list-item>
      </list>
      <paragraph label="Proof">
       As {a mathematical formula}ϕr(a) is a syntactic manipulation of the formula ϕ that is a point-wise replacement of each literal by a formula, the above is immediate, except for the case where ϕ is a literal in (3). For example:{a mathematical formula} If {a mathematical formula}ϕ=p for an atomic proposition, then: {a mathematical formula}(¬p)r(a)=ca,¬p∨(¬p∧¬ca,p), by definition. {a mathematical formula}¬(pr(a))=¬(ca,p∨(p∧¬ca,¬p))≡¬ca,p∧(¬p∨ca,¬p)≡(¬ca,p∧¬p)∨(¬ca,p∧ca,¬p). However, {a mathematical formula}ca,p and {a mathematical formula}ca,¬p are mutually exclusive. Hence, {a mathematical formula}¬(pr(a))≡(¬ca,p∧¬p)∨ca,¬p=(¬p)r(a). For {a mathematical formula}ϕ=¬p, the proof is identical. □
      </paragraph>
      <paragraph label="Proof">
       [22]Given a formula ϕ, a deterministic action a, and a state s,{a mathematical formula}s⊨rga(ϕ)iff a is applicable in s and{a mathematical formula}a(s)⊨ϕ.By structural induction on the formula ϕ.
      </paragraph>
      <list>
       <list-item label="•">
        Base case: let {a mathematical formula}ϕ=l for some literal l, and {a mathematical formula}s⊨rga(ϕ). As {a mathematical formula}rga(ϕ)=pre(a)∧ϕr(a), then a is applicable in s. As ϕ is a literal, {a mathematical formula}ϕr(a)=ca,l∨(l∧¬ca,¬l), thus either s satisfies {a mathematical formula}ca,l, the condition for l to hold following a, or {a mathematical formula}s⊨l and {a mathematical formula}s⊭ca,¬l, the condition for ¬l. Thus, based on the semantics of action execution, {a mathematical formula}a(s)⊨l.For the other direction, suppose that a is applicable in s and {a mathematical formula}s⊭rga(l). Thus:{a mathematical formula}{a mathematical formula}{a mathematical formula} In both cases, based on the semantics of action execution, ¬l holds in {a mathematical formula}a(s), i.e., {a mathematical formula}a(s)⊭l, as required.
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}ϕ=ϕ1∧ϕ2. From Lemma 1, {a mathematical formula}rga(ϕ1∧ϕ2)≡rga(ϕ1)∧rga(ϕ2). Following the induction hypothesis, {a mathematical formula}a(s)⊨ϕ1 and {a mathematical formula}a(s)⊨ϕ2 and a is applicable in s. The other direction is similar. The same holds for {a mathematical formula}ϕ=ϕ1∨ϕ2.
       </list-item>
       <list-item label="•">
        Let {a mathematical formula}ϕ=¬ψ where ψ is not a literal, and suppose that {a mathematical formula}s⊨rga(¬ψ). Thus, a is applicable in s. By Lemma 1.3, we know that {a mathematical formula}s⊨¬rga(ψ). By the induction hypothesis, and as a is applicable in s this implies that {a mathematical formula}a(s)⊭ψ, and thus {a mathematical formula}a(s)⊨¬ψ as {a mathematical formula}a(s) is a single state. For the other direction, suppose that a is applicable in s and {a mathematical formula}a(s)⊨¬ψ. Thus, {a mathematical formula}a(s)⊭ψ. By the induction hypothesis, {a mathematical formula}s⊭rga(ψ), i.e., {a mathematical formula}s⊨¬rga(ψ)=¬pre(a)∨¬(ψr(a)). As a is applicable in s, we must have that {a mathematical formula}s⊨¬(ψr(a)). By Lemma 1.3, we have {a mathematical formula}s⊨(¬ψ)r(a). Thus, {a mathematical formula}s⊨rga(¬ψ).  □
       </list-item>
      </list>
     </section>
     <section label="3.3">
      <section-title>
       Non-deterministic actions
      </section-title>
      <paragraph label="Theorem 2">
       For a non-deterministic action {a mathematical formula}a={a1,…,am} we define [22]:{a mathematical formula}[22]Let ϕ be a formula, let a be a non-deterministic action, and s a state. Then{a mathematical formula}s⊨rga(ϕ)iff a is applicable in s, and for every{a mathematical formula}s′∈a(s),s′⊨ϕ.
      </paragraph>
      <paragraph label="Proof">
       We know that {a mathematical formula}s⊨rgaj(ϕ) iff {a mathematical formula}aj is applicable in s and {a mathematical formula}aj(s)⊨ϕ. Thus, {a mathematical formula}s⊨rga1(ϕ) and⋯and s⊨rgam(ϕ) iff {a mathematical formula}a1,⋯,am are applicable in s and {a mathematical formula}a1(s)⊨ϕ and ⋯ and {a mathematical formula}am(s)⊨ϕ. Thus, {a mathematical formula}s⊨rga(ϕ) iff a is applicable in s and {a mathematical formula}a(s)⊨ϕ.  □
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Regression with observations
      </section-title>
      <paragraph>
       We now extend regression to an action and an ensuing observation. Suppose we want to validate that ϕ holds following the execution of a in some state s given that we observed o. Thus, we need to ensure that following a, if {a mathematical formula}ωa,o holds then ϕ holds. That is:{a mathematical formula}
      </paragraph>
      <paragraph>
       When {a mathematical formula}a={a1,…,ak} is non-deterministic, then:{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       Given a formula ϕ, an action a, an observation o, and a state s,{a mathematical formula}s⊨rga,o(ϕ)iff a is applicable in s and{a mathematical formula}τ({s},a,o)⊨ϕ.{a mathematical formula}s⊨rga,o(ϕ) iff (by definition) {a mathematical formula}s⊨rga(ωa,o→ϕ) iff (Theorem 2) a is applicable in s and for every {a mathematical formula}s′∈a(s), {a mathematical formula}s′⊨ωa,o→ϕ. By definition, {a mathematical formula}s′⊨ωa,o iff {a mathematical formula}o=O(a,s′). Thus, {a mathematical formula}s⊨rga,o(ϕ) iff a is applicable in s and for every {a mathematical formula}s′∈a(s), we have that {a mathematical formula}o=O(a,s′) implies {a mathematical formula}s′⊨ϕ. To conclude the proof, {a mathematical formula}τ({s},a,o) contains precisely all states in {a mathematical formula}a(s) in which it is possible to observe o following a. □
      </paragraph>
      <paragraph label="Corollary 1">
       The following is an immediate corollary: For a belief state b,{a mathematical formula}b⊨rga,o(ϕ)iff a is applicable in b and{a mathematical formula}τ(b,a,o)⊨ϕ.
      </paragraph>
      <paragraph label="Proof">
       For deterministic actions, we have: Given a formula ϕ, a deterministic action a, an observation o, and a state s,{a mathematical formula}s⊨rga,o(ϕ)iff{a mathematical formula}s⊨rga(ωa,o)⇒s⊨rga(ϕ).{a mathematical formula}s⊨rga,o(ϕ) iff (by definition) {a mathematical formula}s⊨rga(ωa,o→ϕ) iff (1) a is applicable in s, and (2) {a mathematical formula}a(s)⊨ωa,o→ϕ; iff (1') a is applicable in s, and (2') {a mathematical formula}a(s)⊨ωa,o implies {a mathematical formula}a(s)⊨ϕ.{sup:2} Using Theorem 2, we have (i) a is applicable in s and {a mathematical formula}a(s)⊨ωa,o iff {a mathematical formula}s⊨rga(ωa,o), and (ii) a is applicable in s and {a mathematical formula}a(s)⊨ϕ iff {a mathematical formula}s⊨rga(ϕ). Combining (1') and (2') with (i) and (ii), we get: {a mathematical formula}s⊨rga,o(ϕ) iff {a mathematical formula}s⊨rga(ωa,o) implies {a mathematical formula}s⊨rga(ϕ), as required. □
      </paragraph>
      <paragraph>
       Theorem 4 does not apply to a non-deterministic action a. The proof requires that if {a mathematical formula}s⊨rga,o(ϕ) then o will be observed following the execution of a in s. But for non-deterministic actions, it only holds that if o is observed then ϕ must be satisfied. While {a mathematical formula}rga,o(ϕ) implies that {a mathematical formula}rga(ωa,o)→rga(ϕ), the other direction does not hold for non-deterministic actions. For example, suppose that a has two possible effects, p, and ¬p, which are observable. {a mathematical formula}rega(p) is false because there is no condition under which we are guaranteed to see p after a. Thus: {a mathematical formula}rga,o(ϕ)≢rga(ωa,o)→rga(ϕ).
      </paragraph>
      <paragraph>
       A different problem arises when regressing {a mathematical formula}ϕ=false with an impossible observation, as in {a mathematical formula}rga,o(false), where o contradicts an effect of a. This would lead to counter-intuitive results. However, in the online setting which we focus on, we regress only with actual, and hence possible, observations, avoiding this problem.
      </paragraph>
      <paragraph label="Theorem 5">
       Finally, regression has a number of useful properties: For any two formulas{a mathematical formula}ϕ1and{a mathematical formula}ϕ2we have:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}ϕ1≡ϕ2⇒rga,o(ϕ1)≡rga,o(ϕ2)
       </list-item>
       <list-item label="2.">
        {a mathematical formula}ϕ1≡ϕ2⇒rga(ϕ1)≡rga(ϕ2)
       </list-item>
       <list-item label="3.">
        {a mathematical formula}rga,o(ϕ1∧ϕ2)≡rga,o(ϕ1)∧rga,o(ϕ2)
       </list-item>
       <list-item label="4.">
        For deterministic a,{a mathematical formula}rga,o(ϕ1∨ϕ2)≡rga,o(ϕ1)∨rga,o(ϕ2)
       </list-item>
      </list>
      <paragraph label="Proof">
       <list>
        <list-item label="1.">
         Follows immediately from {a mathematical formula}τ({s},a,o)⊨ϕ1 iff {a mathematical formula}τ({s},a,o)⊨ϕ2 and Theorem 3.
        </list-item>
        <list-item label="2.">
         Identical to 1, using Theorem 2 instead of Theorem 3.
        </list-item>
        <list-item label="3.">
         Suppose {a mathematical formula}s⊨rga,o(ϕ1∧ϕ2). By Theorem 3, {a mathematical formula}τ({s},a,o)⊨ϕ1∧ϕ2, implying {a mathematical formula}τ({s},a,o)⊨ϕ1 and {a mathematical formula}τ({s},a,o)⊨ϕ2. Applying Theorem 3 again, we get {a mathematical formula}s⊨rga,o(ϕ1) and {a mathematical formula}s⊨rga,o(ϕ2). The other direction is identical.
        </list-item>
        <list-item label="4.">
         Same as 3, noting that for deterministic a, {a mathematical formula}τ({s},a,o) contains a single state, and thus, {a mathematical formula}τ({s},a,o)⊨ϕ1∨ϕ2 implies {a mathematical formula}τ({s},a,o)⊨ϕ1 or {a mathematical formula}τ({s},a,o)⊨ϕ2. □
        </list-item>
       </list>
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Regression over a sequence
      </section-title>
      <paragraph>
       We extend the definition of regression recursively to a sequence of actions and observations {a mathematical formula}a¯,o¯ as follows:{a mathematical formula} where ϵ is the empty sequence.
      </paragraph>
      <paragraph label="Proof">
       Theorem 3 generalizes as follows: Given a formula ϕ, an action–observation sequence{a mathematical formula}a¯,o¯, and a belief state b,{a mathematical formula}b⊨rga¯,o¯(ϕ)iff{a mathematical formula}a¯,o¯is applicable in b and{a mathematical formula}τ(b,a¯,o¯)⊨ϕ.Proof by induction on {a mathematical formula}|a¯|. The base case is immediate. For the inductive step: {a mathematical formula}b⊨rga¯⋅a,o¯⋅o(ϕ) iff (by definition of rg) {a mathematical formula}b⊨rga¯,o¯(rga,o(ϕ)) iff (using the inductive hypothesis) {a mathematical formula}a¯,o¯ is applicable in b and {a mathematical formula}τ(b,a¯,o¯)⊨rga,o(ϕ). Applying Corollary 1, this holds iff a is applicable in {a mathematical formula}τ(b,a¯,o¯) and {a mathematical formula}τ(τ(b,a¯,o¯),a,o)⊨ϕ. As {a mathematical formula}τ(τ(b,a¯,o¯),a,o)=τ(b,a¯⋅a,o¯⋅o) the latter is equivalent to: {a mathematical formula}a¯⋅a,o¯⋅o is applicable in b and {a mathematical formula}τ(b,a¯⋅a,o¯⋅o)⊨ϕ, as required. □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Efficient belief tracking using regression
     </section-title>
     <paragraph>
      Given Theorem 6, we can now use regression as a convenient method for online belief tracking, which is the main contribution of this paper.
     </paragraph>
     <paragraph label="Corollary 2">
      For any propositional formula ϕ and any action–observation sequence{a mathematical formula}a¯,o¯that was applied in{a mathematical formula}bI,{a mathematical formula}τ(bI,a¯,o¯)⊨ϕiff{a mathematical formula}bI⊨rga¯o¯(ϕ).
     </paragraph>
     <paragraph>
      That is, following a valid sequence of actions and observations, querying the current belief state for a given formula ϕ is identical to regressing ϕ through the sequence of actions and observations, and checking whether the regressed formula is satisfied over the initial belief. Thus, there is no need to forward update the belief state – one could just maintain the sequence of already executed actions and observations, and use regression to answer any needed query.
     </paragraph>
     <section label="4.1">
      <section-title>
       Ignoring preconditions
      </section-title>
      <paragraph>
       Recall that in online belief tracking there are two types of queries – checking whether an action can be applied, i.e., checking whether the action precondition holds, and checking whether the goal holds in the current belief state.
      </paragraph>
      <paragraph>
       However, one practical problem with this method is that {a mathematical formula}rga,o(⋅) contains {a mathematical formula}pre(a) and hence when we regress repeatedly over a sequence, as in {a mathematical formula}rga¯,o¯(⋅), we will also have to regress the variables in {a mathematical formula}pre(a). This can adversely affect the size of {a mathematical formula}rga¯,o¯(⋅) and the number of variables it involves, leading, in the worst case, to a formula exponential in {a mathematical formula}|P|. Fortunately, this is not necessary for online belief tracking, because the preconditions of already executed actions were already regressed and shown to hold in the initial belief state. Using the {a mathematical formula}ϕr(a) operation we define:{a mathematical formula} Thus, essentially, {a mathematical formula}rg⁎ is the same as rg, except that we avoid regressing {a mathematical formula}pre(a). As before:{a mathematical formula} As with rg, {a mathematical formula}rg⁎ is also extended recursively to sequences.{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       For any propositional formula ϕ and action–observation sequence{a mathematical formula}a¯,o¯that is applicable in{a mathematical formula}bI, we have that{a mathematical formula}bI⊨rga¯o¯(ϕ)iff{a mathematical formula}bI⊨rga¯o¯⁎(ϕ).By induction on {a mathematical formula}|a¯|, exploiting the observation that if a is applicable in b then {a mathematical formula}b⊨pre(a) and thus {a mathematical formula}b⊨rga(ϕ) iff {a mathematical formula}b⊨rga⁎(ϕ). This immediately extends to {a mathematical formula}rga,o and {a mathematical formula}rga,o⁎ as they are defined using {a mathematical formula}rga. Formally, the base case (empty sequence) is immediate. Let ϕ be a propositional formula and {a mathematical formula}a⋅a¯,o⋅o¯ be an action–observation sequence that is applicable in {a mathematical formula}bI. Let {a mathematical formula}b=τ(bI,a,o). By the induction hypothesis, observing that if {a mathematical formula}a⋅a¯,o⋅o¯ is applicable in {a mathematical formula}bI then {a mathematical formula}a¯,o¯ is applicable in b, we obtain: {a mathematical formula}b⊨rga¯,o¯(ϕ) iff {a mathematical formula}b⊨rga¯,o¯⁎(ϕ). Thus, {a mathematical formula}bI⊨rgaa¯,oo¯(ϕ) iff (by definition of rg on sequences) {a mathematical formula}bI⊨rga,o(rga¯,o¯(ϕ)) iff (by the observation above) {a mathematical formula}bI⊨rga,o⁎(rga¯,o¯(ϕ)) iff (by the induction hypothesis) {a mathematical formula}bI⊨rga,o⁎(rga¯,o¯⁎(ϕ)). In the latter case we show that regression of equivalent formulas is equivalent (Theorem 5). □
      </paragraph>
      <paragraph label="Example 4">
       We now illustrate how an agent that has soundly executed two move-up actions in our localize {a mathematical formula}3×3 example, cannot guarantee that the goal {a mathematical formula}at3,3 holds in all possible states. We regress {a mathematical formula}l=¬at3,3 through the action sequence backward, starting with the last action. There is one condition in move-up that adds {a mathematical formula}at3,3 – {a mathematical formula}(at3,2,¬at3,2∧at3,3), and there is no condition in move-up that removes {a mathematical formula}at3,3, hence, the result of the regression through the last action would be {a mathematical formula}false∨(¬at3,3∧¬at3,2)=¬at3,3∧¬at3,2.We can now regress the two literals independently through the first move-up action in the sequence. Focusing on {a mathematical formula}¬at3,2, we see two relevant conditional effects – {a mathematical formula}(at3,1,¬at3,1∧at3,2) and {a mathematical formula}(at3,2,¬at3,2∧at3,3), the first removing {a mathematical formula}¬at3,2 and the second adding it. Thus, the regression result through the first action is {a mathematical formula}at3,2∨(¬at3,2∧¬at3,1)=at3,2∨¬at3,1, combined with the regression for {a mathematical formula}¬at3,3, the simplified complete regression is {a mathematical formula}¬at3,3∧¬at3,2∧¬at3,1. If the initial state formula allows the agent to be initially in any place, i.e., {a mathematical formula}ϕI=(one-of at1,1...at3,3), then there are satisfying assignments to the {a mathematical formula}ϕI∧rg(¬at3,3), such as {a mathematical formula}at1,1. Thus, we cannot prove that following two movements upwards we have reached the goal cell {a mathematical formula}3,3.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Ignoring irrelevant observations
      </section-title>
      <paragraph>
       We have already seen that, without observations, the regression formula contains only variables relevant to the regressed formula. However, the regression of observations that were received throughout the execution of an action sequence may involve variables that appear in {a mathematical formula}ωa,o, yet are not relevant for any primitive proposition in ϕ. Recall that, earlier, we defined observation o resulting from action a as being relevant to p if {a mathematical formula}ωa,o contains an atomic proposition relevant to p.
      </paragraph>
      <paragraph>
       It is not surprising that when verifying the validity of ϕ, we can ignore observations that are irrelevant to l. To model the removal of irrelevant observations, we define, for every action a, a new artificial action {a mathematical formula}ano-obs, identical to a except that {a mathematical formula}obs(a)=(true,no-obs). Recall that no-obs is an empty observation, such that {a mathematical formula}ωa,no-obs=true, and thus provides no information. Now, to model the removal of an irrelevant observation of an action a that appears in the sequence executed, we replace a with {a mathematical formula}ano-obs.
      </paragraph>
      <paragraph label="Proof">
       Let{a mathematical formula}a¯,o¯be a sequence of actions and observations made, and let{a mathematical formula}a¯′,o¯′be a corresponding sequence where every action a associated with an observation o that is irrelevant to all primitive propositions in ϕ is replaced by{a mathematical formula}ano-obs. Then, ϕ holds following{a mathematical formula}a¯,o¯iff{a mathematical formula}bI⊨rga′¯o¯′⁎(ϕ).Let us start with the case of a single deterministic action a and observation o, such that o is irrelevant to all propositions in ϕ. From our previous results we have that l holds following {a mathematical formula}a,o iff {a mathematical formula}bI⊨rga,o⁎(ϕ) iff {a mathematical formula}bI⊨rga⁎(ωa,o→ϕ). We have that ϕ holds following {a mathematical formula}ano-obs iff {a mathematical formula}bI⊨(true→rgano-obs,no-obs⁎(ϕ)) iff {a mathematical formula}bI⊨(true→rga⁎(ϕ)), i.e., iff {a mathematical formula}bI⊨rga⁎(ϕ) (because, naturally, the initial state formula is satisfiable). Thus, we need to show that {a mathematical formula}bI⊨rga⁎(ωa,o→ϕ) iff {a mathematical formula}bI⊨rga⁎(ϕ) when o is irrelevant to all propositions in ϕ.By definition, {a mathematical formula}rga,o⁎(ϕ)≡{ωa,o→ϕ}r(a)≡{ωa,o}r(a)→{ϕ}r(a) because the {a mathematical formula}r(a) operation manipulates each literal independently and a is deterministic. Moreover, as noted earlier, by definition of relevance, {a mathematical formula}{ϕ′}r(a) contains only literals relevant to propositions in {a mathematical formula}ϕ′.Thus, we need to show that: {a mathematical formula}bI⊨{ωa,o}r(a)→{ϕ}r(a) iff {a mathematical formula}bI⊨{ϕ}r(a), i.e., that {a mathematical formula}φI∧{ωa,o}r(a)⊨{ϕ}r(a) iff {a mathematical formula}φI⊨{ϕ}r(a). {a mathematical formula}φI can be partitioned into clauses that contain literals relevant to some proposition in ϕ only, {a mathematical formula}φI,rel(ϕ), and clauses that contain no literal relevant to ϕ, {a mathematical formula}φI,irrel(ϕ). This follows from the definition of relevance, where if {a mathematical formula}l1 is relevant to l, and {a mathematical formula}l2 appears with {a mathematical formula}l1 in the same clause of {a mathematical formula}φI, then {a mathematical formula}l2 is relevant to l. Thus, we have to show that: {a mathematical formula}φI,irrel(ϕ)∧φI,rel(ϕ)∧{ωa,o}r(a)⊨{ϕ}r(a) iff {a mathematical formula}φI,irrel(ϕ)∧φI,rel(ϕ)⊨{ϕ}r(a). However, from logic we know that if {a mathematical formula}ϕ,ψ are two formulas over disjoint sets of atomic propositions, and φ is a formula that contains only atomic propositions that appear in ϕ then {a mathematical formula}ϕ∧ψ⊨φ iff {a mathematical formula}ϕ⊨φ. Thus, {a mathematical formula}φI∧{ωa,o}r(a)⊨{ϕ}r(a) iff {a mathematical formula}φI,irrel(ϕ)∧φI,rel(ϕ)∧{ωa,o}r(a)⊨{ϕ}r(a) iff {a mathematical formula}φI,irrel(ϕ)∧φI,rel(ϕ)⊨{ϕ}r(a) iff {a mathematical formula}φI⊨{ϕ}r(a), as required.Next, assume that {a mathematical formula}a={a1,…,am} is non-deterministic. Recall that the observations associated with the component {a mathematical formula}ai's are identical, by definition. Using the same reasoning as above, we have that for every {a mathematical formula}1≤i≤m: {a mathematical formula}bI⊨rgai⁎(ωai,o→ϕ) iff {a mathematical formula}bI⊨rgai⁎(ϕ). That is: for every {a mathematical formula}1≤i≤m: {a mathematical formula}bI⊨rgai,o⁎(ϕ) iff {a mathematical formula}bI⊨rgai⁎(ϕ), which implies {a mathematical formula}bI⊨rga,o⁎(ϕ) iff {a mathematical formula}bI⊨rga⁎(ϕ), as required.The general case follows by induction, as {a mathematical formula}rga¯⋅a,o¯⋅o⁎(ϕ)=rga¯,o¯⁎(rga,o⁎(ϕ)). By the induction hypothesis, {a mathematical formula}rga¯,o¯⁎(rga,o⁎(ϕ))=rga¯′,o¯′⁎(rga,o⁎(ϕ)). If o is relevant to some proposition in ϕ, then this implies {a mathematical formula}rga¯⋅a,o¯⋅o⁎(ϕ)=rga¯′⋅a,o¯′⋅o⁎(ϕ) as required, since {a mathematical formula}o¯′⋅o is the correct sequences of observations in this case. If o is irrelevant to all propositions in ϕ, then we know from above that {a mathematical formula}rga,o⁎(ϕ)=rgano-obs,no-obs⁎(ϕ) and this implies {a mathematical formula}rga¯⋅a,o¯⋅o⁎(ϕ)=rga¯′⋅ano-obs,o¯′⋅no-obs⁎(ϕ), as required. □
      </paragraph>
      <paragraph>
       Thus, regression with observations, as long as irrelevant observations are ignored, also involves only variables relevant to some proposition that appears in the regressed formula.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Complexity analysis
     </section-title>
     <paragraph>
      Our analysis will focus on the complexity per step under the assumption that the action sequence is of polynomial length. If the action sequence is exponential then both methods must perform exponentially many updates. However, in the worst case, the regression method will suffer even more, because while FBT pays a fixed price per step, the regression method's cost increases (polynomially) with the length of the action sequence.
     </paragraph>
     <paragraph label="Definition 10">
      As we shall see, regression allows us to use a more refined, context sensitive width notion, that is never larger than BG's notion of width. We start by introducing a natural extension of BG's width notion to the online setting, i.e., in the context of an action–observation sequence. Later, we farther refine this notion using additional properties of regression. {a mathematical formula}wa¯,o¯(p), the contextual width of variable p w.r.t. {a mathematical formula}a¯ and {a mathematical formula}o¯ is the width of p with respect to the original planning problem, restricted to the set of actions appearing in {a mathematical formula}a¯ and the set of observations appearing in {a mathematical formula}o¯.
     </paragraph>
     <paragraph label="Proof">
      For any literal l, the time complexity of computing{a mathematical formula}rga¯′,o¯′⁎(ϕ)is{a mathematical formula}O(2cw|a¯|), and the space complexity is{a mathematical formula}O(2cw), where{a mathematical formula}w=wa¯′,o¯′(l)is the contextual width of l in the context of the sequence{a mathematical formula}a¯′,o¯′, ignoring observations irrelevant to l.For every literal l in ϕ, we have seen that {a mathematical formula}rga¯′,o¯′⁎(l) contains only atomic propositions relevant to l with respect to the planning problem, restricted to the actions and observations in {a mathematical formula}a¯′ and {a mathematical formula}o¯′, where observations irrelevant to l are excluded. We denote the number of such relevant propositions by w. Below we heavily rely on restricting our attention to only w primitive propositions, and consequently to a number of possible models that is exponential in w, rather than in the total number of primitive propositions. This means that, while conversion from DNF to CNF and vice versa can cause an exponential increase in formula size, as long as we are careful to remove repeated/subsumed terms, this is still bounded by {a mathematical formula}exp⁡(w).The size of the regression formula is initially 1, corresponding to the literal l. In each regression step, we replace a literal by a formula of the form {a mathematical formula}ca,l∨(l∧¬ca,¬l). We convert the latter into CNF, which results (following the above) in a formula with size that is at most exponential in w. It is easy to maintain the regression formula in CNF – as we replace a literal in a CNF formula by another CNF formula, we just have to distribute the disjuncts in the respective clause. This is polynomial in the size of the formula and the CNF representation of the inserted formula.However, as the above transformation is applied {a mathematical formula}|a¯| times during the regression process, the formula size can become exponential in {a mathematical formula}|a¯|, the length of the action sequence, rather than in w. However, we can maintain a formula size exponential in w by simplifying the formula following each step, removing subsumed and repeated clauses, at a cost that is at most exponential in w for each step. Specifically, the number of non-subsumed disjuncts is at most {a mathematical formula}22w and we can remove each subsumed disjunct in time proportional to the number of clauses squared, which is thus bounded by {a mathematical formula}24w. This gives us the desirable space complexity. For the time complexity, as we perform this simplification at every step, we have to multiply the simplification cost {a mathematical formula}24w by the sequence length {a mathematical formula}|a¯|. □
     </paragraph>
     <paragraph label="Proof">
      For any formula ϕ, the time complexity of computing{a mathematical formula}rga¯′,o¯′⁎(ϕ)is{a mathematical formula}O(2cw|a¯||ϕ|), and the space complexity is{a mathematical formula}O(2cw|ϕ|), where{a mathematical formula}w=maxl∈ϕ⁡wa¯′,o¯′(l)and{a mathematical formula}wa¯′,o¯′(l)is as above.This follows immediately from Theorem 8 and the decomposability of the regression formula as shown in Lemma 1. We need to replace every literal in ϕ by its regression formula. □
     </paragraph>
     <paragraph>
      Presentations support rapid, poly-time validity checks. Examples of such forms are formulas in prime-implicate form [9] as well as conjunctions of literals. Representing the initial belief using such a form allows us to bound the complexity of the satisfiability query that follows the regression.
     </paragraph>
     <paragraph label="Proof">
      If the form of{a mathematical formula}φIallows for polynomial clause validity checks then the complexity of determining whether l is valid following{a mathematical formula}a¯,o¯is polynomial in{a mathematical formula}|a¯|and at most exponential in{a mathematical formula}wa¯′,o¯′(l).Based on Lemma 2, determining whether a literal l holds following {a mathematical formula}a¯,o¯, can be determined by checking whether {a mathematical formula}φI⊨rga¯′,o¯′⁎(l). As we have seen, the time required to compute {a mathematical formula}rga¯′,o¯′⁎(l), as well as its size, are polynomial in {a mathematical formula}|a¯| and exponential in {a mathematical formula}w=wa¯′,o¯′(l). Furthermore, if the latter formula is in CNF then it has at most a number of clauses exponential in w. Given our assumption on the form of {a mathematical formula}φI, the result follows. □
     </paragraph>
     <paragraph>
      Online belief tracking replaces the offline query: “is {a mathematical formula}a¯,o¯ executable in {a mathematical formula}bI?” with a sequence of queries for the precondition of each action in the sequence separately. Thus, to determine executability, one needs query only regarding the preconditions of the last action in the sequence. It might well be that some relevant variables for the precondition of an action do not appear in the specific actions that were executed, and the regression would not involve these variables, reducing the practical width for the specific query.
     </paragraph>
     <section label="5.1">
      <section-title>
       A tighter definition of contextual width
      </section-title>
      <paragraph>
       The contextual width {a mathematical formula}wa¯,o¯(p), as defined so far, is based on BG's notion of width, restricted to a subset of actions and observations. A closer look, though, reveals that it can be much smaller.{sup:3}
      </paragraph>
      <paragraph label="Definition 11">
       At the extreme, imagine that the last observation in {a mathematical formula}o¯ reveals the value of p. In that case, the value of earlier actions and observations is not needed for determining whether p or ¬p holds. More generally, some observations can provide information that makes earlier actions irrelevant to the current regressed query. To better define this, let us consider a more refined definition of context: The {a mathematical formula}a,o context of p, denoted {a mathematical formula}ctxa,o(p), consists of all atomic propositions q that are relevant to p given the singleton action set {a mathematical formula}{a} and the singleton observation set {a mathematical formula}{o} (set)minus the set of propositions {a mathematical formula}{r} such that {a mathematical formula}ωa,o implies r or ¬r.The {a mathematical formula}a¯⋅a,o¯⋅o context of p, denoted {a mathematical formula}ctxa¯⋅a,o¯⋅o(p), is defined recursively as {a mathematical formula}⋃r∈ctxa,o(p)ctxa¯,o¯(r). We define {a mathematical formula}wa¯,o¯⁎(p)=|ctxa¯,o¯(p)|.
      </paragraph>
      <paragraph label="Lemma 3">
       The following is straightforward from the definition of ctx and {a mathematical formula}ctxa¯,o¯. For any sequence{a mathematical formula}a¯,o¯and an atomic proposition p, we have that{a mathematical formula}ctxa¯,o¯(p)⊆ctx(p). Therefore,{a mathematical formula}wa¯,o¯⁎(p)≤wa¯,o¯(p)≤w(p).
      </paragraph>
      <paragraph label="Proof">
       We can replace{a mathematical formula}wa¯,o¯inTheorem 8by{a mathematical formula}wa¯,o¯⁎.Using the recursive definition of regression over sequences, and focusing on relevant observations only, {a mathematical formula}bI⊨rga¯⋅a,o¯⋅o⁎(l) iff {a mathematical formula}bI⊨rga¯,o¯⁎(rga,o⁎(l)) iff {a mathematical formula}bI⊨rga¯,o¯⁎(ωa,o→rga⁎(l)). {a mathematical formula}rga⁎(l) contains only variables relevant to l with respect to action a. If r is such a variable and {a mathematical formula}ωa,o implies r we can simplify {a mathematical formula}rga⁎(l) by replacing r with true. If {a mathematical formula}ωa,o implies ¬r, we replace it by false. In both cases, we maintain logical equivalence. Thus, r will not be carried backwards through the regression at this step. Of course, r could reoccur later in the regression process at some other step, but that will be accounted for in the definition of that particular step. Consequently, the set of variables that will appear in {a mathematical formula}rga¯⋅a,o¯⋅o⁎(l) will be contained in {a mathematical formula}ctxa¯⋅a,o¯⋅o(l). □
      </paragraph>
      <paragraph>
       The above result can give us some insight into the potential advantage of caching. In planning, one must perform multiple regression queries at each step. One for every precondition of a potentially applicable action, and for every sub-goal. If following the regression query the value of some variable at time step t becomes known, we can cache this information. In the worst case, the amount of information cached is linear in the length of the sequence. These cached values can be used to simplify the regression formula much like observations are used in the above analysis. Of course, in the worst-case, the context of a propositional variable contains no variable that was cached, hence the worst-case complexity remains unchanged. In practice, as our experiments demonstrate, caching is quite valuable.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Regression vs. factored belief tracking
      </section-title>
      <paragraph label="Theorem 10">
       Bonet and Geffner show that the complexity of the FBT method is exponential in the width of the problem: BGIf{a mathematical formula}φIis a conjunction of literals than the time and space complexity of online belief tracking over a propositional description using FBT is{a mathematical formula}O(2w), where w is the width of the planning problem.
      </paragraph>
      <paragraph>
       Compare this result to Theorem 9, and note that under the assumption that {a mathematical formula}φI is a conjunction of literals, clausal entailment is polynomial. Furthermore, note that with such an initial state, the initial formula plays no role in the definition of relevance, and so our definition becomes identical to that of BG. Thus, if the action sequence is of polynomial size, then the complexity of both methods is exponential in the width of the problem, except that in the case of regression, it is the contextual width, which is always bounded above by the width, and can often be smaller. Thus, in terms of the bounds, regression is superior, as long as the action sequence is not too long.
      </paragraph>
      <paragraph>
       The original definition of width in BG's work is with respect to multi-valued variables, whereas we focus on the Boolean case. Thus, one might ask what happens if a Boolean domain is compiled into a multi-valued one and FBT is applied, or if a multi-valued domain is compiled into a Boolean one, and regression is applied, as width is not necessarily invariant under such compilations. A multi-valued domain may have smaller width than its corresponding Boolean domain, and even smaller than the contextual width of the Boolean domain for various action–observation sequence.
      </paragraph>
      <paragraph>
       As far as the complexity analysis is concerned, compiling a domain from multi-valued variables to Boolean variables increases width because, to the best of our knowledge, existing methods cannot exploit the additional constraints imposed on Boolean variables that correspond to multi-valued domains. For example, if loc is a multi-valued variable denoting the location of some object, then as we increase its size linearly, its width remains the same, while the number of possible belief states (which FBT tracks) increases polynomially. In its natural Boolean representation, where new propositions denote that the object is in a particular location, the number of variables increases linearly, and so does the width. And while the set of legal truth assignments increases only polynomially, we are not aware of methods for enhancing regression with invariants that will ensure that the size of formula does not grow exponentially in w, and perhaps more importantly, that the validity check is guaranteed to exploit this information.{sup:4} This is an interesting open issue.
      </paragraph>
      <paragraph>
       In the experimental evaluation, we compare regression on Boolean domains to FBT on multi-valued domains. Despite the fact that the latter may have smaller width, regression appears to perform very well.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Compiling away non-deterministic actions
     </section-title>
     <paragraph>
      We have previously explained how to handle regression with non-deterministic actions. In this section we suggest an alternative approach to handling non-deterministic actions by compiling them into deterministic actions. In theory, this compilation can have a high cost. In practice, it allows us to decouple observations from the conditions we are checking, and to simplify future regressions.
     </paragraph>
     <paragraph>
      The reason to compile away non-deterministic actions is that deterministic actions have two important properties:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}rga,o(ϕ1∨ϕ2)≡rga,o(ϕ1)∨rga,o(ϕ2)
      </list-item>
      <list-item label="2.">
       {a mathematical formula}s⊨rga,o(ϕ) iff {a mathematical formula}s⊨rga(ωa,o)⇒s⊨rga(ϕ).
      </list-item>
     </list>
     <paragraph>
      The first property, together with the factoring of regression over conjunctions, implies that we can factor the regression formula and regress it in parts, reusing similar parts. This is the essential idea behind the circuit construction of Shahaf and Amir [25] which we discuss later.
     </paragraph>
     <paragraph>
      The second property has important practical implications. It implies that following an observation o via action a, we can conjoin the regression of {a mathematical formula}ωa,o to the initial state independently of the condition ϕ we are checking. Thus, once the regression of {a mathematical formula}ωa,o is conjoined with the initial state, we can simply ignore this observation in future regressions. In practice, the regression of observation conditions often simplifies the initial state considerably, making future validity checks simpler. In theory, however, it can complicate the initial state.
     </paragraph>
     <paragraph>
      To replace non-deterministic actions with deterministic ones we use a classical compilation scheme that replaces the uncertainty on the effect of the actions with uncertainty on the initial state. For simplicity, let us assume that a non-deterministic action a has only two possible options: {a mathematical formula}a={a1,a2}. We add a new atomic proposition, {a mathematical formula}pa, whose value is unknown initially. We now change a into a deterministic action {a mathematical formula}adet with two conditional effects: if {a mathematical formula}pa then {a mathematical formula}a1 and if {a mathematical formula}¬pa then {a mathematical formula}a2.
     </paragraph>
     <paragraph>
      Formally, define {a mathematical formula}ca,l (the condition under which l becomes true following a) to be{a mathematical formula}
     </paragraph>
     <paragraph label="Example 5">
      In our localize example, we add a drift action, moving the agent non-deterministically vertically to one of the neighboring cells. Formally, {a mathematical formula}drift={a mathematical formula}{driftup,driftdown}, where {a mathematical formula}driftup contains a condition {a mathematical formula}(at3,2,at3,3∧¬at3,2) and {a mathematical formula}driftdown contains a condition {a mathematical formula}(at3,2,at3,1∧¬at3,2). We add a new atomic proposition {a mathematical formula}pdriftv, and the new action {a mathematical formula}driftvdet will contain two conditional effects {a mathematical formula}(at3,2∧pdriftv,at3,3∧¬at3,2) and {a mathematical formula}(at3,2∧¬pdriftv,at3,1∧¬at3,2).
     </paragraph>
     <paragraph>
      This compilation must be carried out for every action instance. That is, if a appears three times in the sequence at times {a mathematical formula}t1,t2,t3, then we need three different variables {a mathematical formula}pat1,pat2,pat3, to allow for the outcome at {a mathematical formula}t1 to differ from the outcome at {a mathematical formula}t2, etc. For offline planning, this compilation requires a number of additional variables that is exponential in the problem horizon. In online planning and belief tracking, however, we can add these variables lazily, only when a non-deterministic action is chosen for execution. Thus, the number of atomic propositions that we need to add equals the number of non-deterministic actions performed so far, and is therefore at most linear in the sequence length.
     </paragraph>
     <paragraph>
      Once we compile non-deterministic actions into deterministic ones, we can perform regression over the sequence of actions as before. The complexity analysis remains as above, except that {a mathematical formula}wa¯,o¯(p), the width of an atomic proposition p can become larger by {a mathematical formula}|a¯| because each non-deterministic action may introduce a new variable when compiled, which may be relevant for the regressed literal.
     </paragraph>
     <section label="6.1">
      <section-title>
       Regressing observations independently
      </section-title>
      <paragraph>
       We have seen above that {a mathematical formula}rga,o⁎=rga⁎(ωa,o→ϕ), and discussed how irrelevant observations to the currently regressed literal l can be ignored during the regression. We now suggest a different method for handling observations, and analyze its theoretical and practical implications. Specifically, we suggest to regress observations as they are received, conjoin the regressed formula to the initial belief state, and ignore the observation during later regressions.
      </paragraph>
      <paragraph>
       That is, following each observation o, we regress it to the initial state, obtaining {a mathematical formula}φo=rga¯,o¯⁎(ωa,o). Now, we conjoin {a mathematical formula}φo with {a mathematical formula}φI obtaining an updated initial state formula. To verify whether l is valid following {a mathematical formula}a¯,o¯=a1,…,ak;o1…ok, we check whether {a mathematical formula}φI∧rga1⁎(ωa1,o1)∧⋯∧rga1,…,ak⁎(ωak,ok)⊨rga1,…,ak⁎(l).
      </paragraph>
      <paragraph>
       This method has several advantages:
      </paragraph>
      <list>
       <list-item label="1.">
        Observations are regressed only once, and the cost of their regression is amortized over all future regressions.
       </list-item>
       <list-item label="2.">
        The regression formula is simpler and smaller, as it no longer refers to the observation conditions ({a mathematical formula}ωa,o). This means that variables that will appear in it are only those that are causally relevant to the regressed literal, which is of course a subset of the set of relevant variables. The complexity is no longer exponential in the width, but rather, in the causal width, which can be much smaller (and even smaller given the context-based definition of width). We use {a mathematical formula}wa¯,o¯c(l) to denote the contextual causal width.
       </list-item>
       <list-item label="3.">
        As the regression of the formula {a mathematical formula}ωa,o→ϕ makes the decomposition of the regression operator more complex, regression over deterministic actions avoiding the observations decomposes conveniently.
       </list-item>
       <list-item label="4.">
        In many cases, {a mathematical formula}φI∧rga‾⁎(ωa,o) creates a formula that is simpler than the original {a mathematical formula}φI, reducing the cost of future entailment queries.
       </list-item>
      </list>
      <paragraph label="Example 6">
       In the localize domain, let us assume that the agent has executed the sensor activation action checking, and then the observe-wall-up action, observing the green light observation. We can now regress {a mathematical formula}wa,o=¬wallup through the action sequence. The observe-wall-up is a sensing action with no effects, thus regressing through it has no effect on the regressed formula. We hence need to regress {a mathematical formula}¬wallup through the checking action. For this action {a mathematical formula}ca,l=at1,1∨at1,2∨at3,1∨at3,2 – the list of cells where there is no wall above the agent. The condition {a mathematical formula}ca,¬l=at2,1∨at1,3∨at2,3∨at3,3, and {a mathematical formula}¬ca,¬l=¬at2,1∧¬at1,3∧¬at2,3∧¬at3,3. Thus, the regressed term {a mathematical formula}ca,l∨(l∧¬ca,l)=at1,1∨at1,2∨at3,1∨at3,2∨(¬wallup∧¬at2,1∧¬at1,3∧¬at2,3∧¬at3,3), we can now conjoin the initial state formula {a mathematical formula}(one-of at1,1...at3,3) with this regressed formula, limiting the set of possible initial state only to {a mathematical formula}(one-of at1,1at1,2at3,1at3,2).
      </paragraph>
      <paragraph>
       The major theoretical disadvantage of this method is that the initial state formula must be updated following every observation with the regressed observation condition. For example, formulas in PI form, which are convenient for SAT queries, do not support simple conjunction. Thus, if we seek to maintain the PI form of the initial state, the price is worst-case exponential in the entire set of variables. If we use a CNF representation, however, the conjunction is worst-case exponential in the number of variables which appear in the regressed formula, which is no greater than the width of the problem, but with CNF, entailment can be exponential.
      </paragraph>
      <paragraph>
       One may worry that, as we add new clauses or change the initial state, non-relevant atomic propositions will become relevant to each other, as l is relevant to p if it appears in an initial clause with another literal relevant to p. However, the new formulas conjoined with the {a mathematical formula}φI have the form {a mathematical formula}rga1,…,ak⁎(ωak,ok), i.e., they are obtained via regression over actions only. Consequently, by definition of regression, they refer only to atomic propositions relevant to {a mathematical formula}ωa,o. Thus, the set of atomic propositions relevant to an atomic proposition p remains the same as in the original problem, with the exception of the new determinization propositions, {a mathematical formula}pa.
      </paragraph>
      <paragraph>
       The following is a simple corollary of Theorem 8:
      </paragraph>
      <paragraph label="Proof">
       The time and space complexity of determining whether some literal l is valid following{a mathematical formula}a¯,o¯is{a mathematical formula}O(2cw⋅|a¯|⋅poly(|bIa¯,o¯|)), where{a mathematical formula}w=wa¯′cis the contextual causal width of l with respect to the set of actions in{a mathematical formula}a¯′, the determinized sequence of actions executed, and{a mathematical formula}|bIa¯,o¯|is the size of the initial state formula conjoined with regressed, past observations, and converted into PI form or some other form supporting polynomial time validity checks.This follows immediately from Theorem 8 after we notice that the regressed formula will only contain causally relevant variables that appear in the determinized sequence {a mathematical formula}a¯′, as we no longer need to regress through o.  □
      </paragraph>
      <paragraph>
       As noted, the size of the initial state formula, modified by conjunction with a regressed observation o can increase. In principle, if the initial state formula is maintained in a convenient form that supports polynomial-time conjunction, an equivalent formula whose size is polynomial in {a mathematical formula}|bI| and {a mathematical formula}2wa¯′,o¯c exists. This is true for a number of forms (see Darwiche and Marquis [9]). In particular, for {a mathematical formula}OBDD&lt;, both conjunction and validity checks are polytime. However, even in this case, unless a stronger property of unbounded conjunction holds, we cannot prove that an unbounded sequence of updates to the initial state formula yields a poly-sized formula. Thus, in principle, the size can become exponential in the length of {a mathematical formula}|o¯|.
      </paragraph>
      <paragraph>
       In practice, however, regressed observations often simplify the initial state rather than complicate it, as they often establish the value of some proposition at the initial state. For example, in the localize domain, observing that there is no wall above the agent, we know that any location where there is a wall above the agent is impossible. Thus, the set of currently possible locations is reduced following every observation.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Representing beliefs using circuits
      </section-title>
      <paragraph>
       Shahaf and Amir [25] suggest logical circuits as a convenient form for representing beliefs. A logical circuit is a directed acyclic graph, where leaves represent variables, and inner nodes are tagged with a logical operation, such as {a mathematical formula}∧,∨,¬. An advantage of circuits, aside from their compact form, is that specialized SAT procedures that exploit the circuit structure can lead to efficient computation of SAT and UNSAT queries. Shahaf and Amir show how a poly-sized circuit can be constructed to represent the belief given a sequence of deterministic actions. They, as well as others [22], [25], were pessimistic about extending logical circuits to non-deterministic actions, while preserving a polynomial size.
      </paragraph>
      <paragraph>
       Surprisingly, our compilation scheme from non-deterministic actions into deterministic actions allows us to prove the existence of a polynomial size circuit representation of the regression formula. Using this compilation, it is easy to see that the circuit construction works for non-deterministic actions too, as long as we pay the price of determinization.
      </paragraph>
      <paragraph label="Proof">
       Let l be a literal and{a mathematical formula}a¯,o¯an action–observation sequence. Then, a circuit C can be constructed in time and space{a mathematical formula}O(poly(|φI|+|a¯|⋅ActDesc)), where ActDesc is the maximal description size of an action, such that l holds following{a mathematical formula}a¯,o¯iff C is unsatisfiable.This result is an immediate consequence of Theorem 5.5 of Shahaf and Amir [25] combined with the idea of action determinization that we described above. Their result holds for deterministic actions, and the determinization step can only increase the description of the action polynomially.  □
      </paragraph>
      <paragraph>
       We also provide a direct, recursive construction, which given the machinery developed in this paper may be more appropriate in this context than Shahaf and Amir's description. The basic intuition should be clear: regression over deterministic action sequences decomposes over disjunctions and conjunctions, so we can reuse sub-parts of the formula.
      </paragraph>
      <paragraph label="Proof">
       Let l be a literal and{a mathematical formula}a¯,o¯an action–observation sequence and assume that the conditions{a mathematical formula}ca,l,ωa,lhave size polynomial in the number of variables appearing in them. Then,{a mathematical formula}rga¯,o¯⁎(l)can be represented by a circuit with size{a mathematical formula}O(|a¯|⋅poly(wa¯,o¯)).We shall assume that for all {a mathematical formula}a,l, {a mathematical formula}ωa,l and {a mathematical formula}ca,l are in negation normal form. Converting a formula to negation normal form doubles it size, at most.We begin by describing the circuit construction, then we analyze the circuit size. The proof is by induction on {a mathematical formula}|a¯| and it yields a simple recursive construction. For the base case {a mathematical formula}a¯=ϵ, and the circuit contains l only.For the inductive step: we explain how we take circuits constructed for the set of literals relevant to l and the sequence {a mathematical formula}a¯,o¯ and build a circuit for l given {a mathematical formula}a¯a,o¯o.First, if a is a non-deterministic action, we transform it into a deterministic action. That will only affect the size of the various {a mathematical formula}ca,l polynomially. Note, also, that the variable added does not impact any part of the circuit constructed earlier.Now, given a constructed circuit for {a mathematical formula}a¯,o¯ we consider {a mathematical formula}rga¯⋅a,o¯⋅o⁎(l). By definition, {a mathematical formula}rga¯⋅a,o¯⋅o⁎(l)=rga¯,o¯⁎(rga,o⁎(l))≡rga¯,o¯⁎(rga⁎(ωa,o→l)). By our inductive assumption, we know that for every literal l, we can construct a circuit {a mathematical formula}rga¯,o¯⁎(l). By definition, {a mathematical formula}rga⁎(ωa,o→l)=(ωa,o→l)r(a). Recall that (Equation (3.2)){a mathematical formula} Thus, {a mathematical formula}rga¯⋅a,o¯⋅o⁎(l)=rga¯,o¯⁎((ωa,o→l)r(a)). Next, we convert {a mathematical formula}(ωa,o→l)r(a) to negation normal form. Denote the resulting formula by ϕ. Now, we use Theorem 5, which tells us that ϕ can be decomposed to some Boolean formula with conjunctions and disjunctions over basic elements of the form {a mathematical formula}rga¯,o¯⁎(l). Since we have a circuit for each of these elements, we now only need to combine the existing elements with some and and or gates to get the desired circuit.Next, we analyze the circuit size. First, note that given the definition of relevance, if {a mathematical formula}l′ is relevant to l given {a mathematical formula}a¯⋅a,o¯⋅o, and {a mathematical formula}l″ is relevant to {a mathematical formula}l′ given {a mathematical formula}a¯⋅a,o¯⋅o, then {a mathematical formula}l″ is relevant to l given {a mathematical formula}a¯⋅a,o¯⋅o. And furthermore, if {a mathematical formula}l′ is relevant to l given some prefix of {a mathematical formula}a¯⋅a,o¯⋅o, then it is also relevant given {a mathematical formula}a¯⋅a,o¯⋅o. Now, to build the circuit for {a mathematical formula}rga¯⋅a,o¯⋅o⁎(l) we maintain circuits for all the literals relevant to l given {a mathematical formula}a¯⋅a,o¯⋅o. Their number if {a mathematical formula}w=o(wa¯a,o¯o(l)). As described above, moving from a set of circuits for any such {a mathematical formula}l′, given a prefix of length m of the sequence of actions and observations, to one representing the prefix of length {a mathematical formula}m+1, can be done by adding a single circuit of size k. This circuit corresponds to {a mathematical formula}rega,o⁎(l), for the most recent action observation pair, {a mathematical formula}a,o. We do this for all w literals, and repeat it a number of times that equals to the length of the sequence. Thus, the overall size is polynomial in {a mathematical formula}w⋅k⋅|a¯|.It remains to show that k is {a mathematical formula}O(poly(w)). But k is the size of a circuit that represents {a mathematical formula}(ωa,o→l′)r(a). (It is the circuit whose inputs are the various {a mathematical formula}rga¯,o¯⁎(l′) which is constructed in the last step.) The latter, by assumption, is {a mathematical formula}O(poly(w)), and its conversion to negation normal form maintains this property.  □
      </paragraph>
     </section>
    </section>
    <section label="7">
     <section-title>
      Empirical evaluation
     </section-title>
     <paragraph>
      We start by discussing a few optimizations used in our code, and then proceed to empirically evaluate the regression method and compare it to BG's beam-tracking method.
     </paragraph>
     <section label="7.1">
      <section-title>
       Practical optimizations
      </section-title>
      <paragraph>
       The run-time of regression can be improved considerably by using a number of optimizations. Two of these methods were briefly discussed earlier: caching and initial-state simplification. First, during planning we perform many regression queries that lead to the learning of new facts. For example, we always learn that the preconditions of an executed action are valid. These learned facts can be cached at each step and used to simplify formulas generated when answering future queries. We maintain at each time step t the set of facts {a mathematical formula}Ft that are known at time t. Each successful precondition regression query may add new facts to {a mathematical formula}Ft.
      </paragraph>
      <paragraph>
       Second, we utilize observations to constrain and simplify the initial state as explained earlier. Often the regressed formula φ is a unit literal, e.g., if o is an observation of a static fact. We then use unit propagation to discover additional facts about the set of possible initial states. The learned facts are then propagated forward through the executed action–observation sequence to update the {a mathematical formula}Ft cache (Algorithm 1).
      </paragraph>
      <paragraph>
       Sometimes, however, φ could be a more complex formula, requiring an exponential price for converting {a mathematical formula}bI∧φ to PI form. In our current implementation, we do not maintain a PI form, but rather use CNF and determine validity using the MiniSAT SAT solver [11]. Theoretically, these queries can take exponential time to answer, but in practice they are very fast.
      </paragraph>
      <paragraph>
       Instead of checking whether {a mathematical formula}bI⊨rga¯⁎(l), for a precondition or goal literal l, we regress ¬l, obtaining {a mathematical formula}rga¯⁎(¬l). Then we run a SAT query for {a mathematical formula}bI∧rga¯⁎(¬l). If there is no solution to this SAT query, then l must hold following {a mathematical formula}a¯ (Algorithm 2).
      </paragraph>
      <paragraph>
       We also use some additional caching mechanisms; as the actual PDDL problem specification allows a literal l to appear in the effect of many conditional effects of an action a, we maintain a mapping from each literal l to the conditions it appears in, for every executed action a. This allows us in future regressions to rapidly access only the conditional effects that are relevant to the current query. We also maintain a mapping from each literal to the clauses where it appears in the initial state formula {a mathematical formula}bI. Recalling that relevance is defined recursively, and that if p appears with q in an initial clause and r appears with p, then r is relevant to q, this allows us to run SAT queries only on variables relevant to the currently regressed formula.
      </paragraph>
     </section>
     <section label="7.2">
      <section-title>
       Experimental set-up
      </section-title>
      <paragraph>
       We now demonstrate the practical value of regression, showing it to scale up well. We experiment with the more interesting benchmark domains from the contingent planning literature. Table 1 shows the properties of the various benchmarks. As can be seen, these benchmarks vary greatly on their properties. For examples, some domains exhibit many conditional effects over hidden propositions, while others do not. Some domains allow for many observations while for others information concerning the hidden propositions must be concluded from a single observation.
      </paragraph>
      <paragraph>
       The domain sizes that we experiment with are currently unsolvable using all state-of-the-art generic online contingent planners [26], [7], [4], [1]. As such, in all these domains, we use a simple and fast domain-specific heuristic for action selection. In each step the “planner” chooses an action, runs a regression query to check if its preconditions hold, executes it, and runs a second regression query to check if the goal has been reached. If an observation is sensed following the action, the planner regresses the observed value, conjoins it with the initial belief, and caches the resulting information. Thus, in every step, there can be up to 3 different regression operations. We report the average step time, rather than the pure regression time, to be comparable to previous experiments. For every problem, we run 25 iterations, varying on the hidden initial state, and hence the observations, and report the average time per step in milliseconds.
      </paragraph>
      <paragraph>
       Our heuristic is not trivial. For example, in the battleship domain, once a cell containing a ship is hit, we hit its neighboring cells until the entire ship was drowned. On the other hand, if, e.g., cells {a mathematical formula}3,2 and {a mathematical formula}3,3 both contain a ship, then the updated belief following the observations will conclude that cells {a mathematical formula}4,2 and {a mathematical formula}4,3 cannot contain a ship, and we will not fire on them. We must thus check for a set of cells whether they were hit, or possibly contain a ship. For this, we use only the cached facts in the heuristic computation, avoiding additional regression queries. Thus, the heuristic uses sound but incomplete information for making decisions, but it is very fast to compute. Our heuristic is less effective than the heuristic implemented by BG. For example, we require about 50 shots to solve Battleship {a mathematical formula}5×5 while BG require about 39 shots. On MineSweeper, we evaluate on a set of specially designed boards{sup:5} where only a single action is applicable at each step, and no heuristic is needed. Hence, on this domain, the measured time purely estimates belief queries. In Wumpus, our heuristic maintains a grid map of the domain, marking all locations that are known to be safe. We repeatedly direct the agent towards the closest safe place from which additional information concerning nearby possibly safe cells can be sensed, until the treasure has been found.
      </paragraph>
      <paragraph>
       We compare regression to Beam Tracking [5], [6], which is a more advanced, approximate implementation of the ideas behind FBT. This method maintains for each proposition p that appears in a precondition, the goal, or an observation, a belief over the causally relevant propositions to p, called beams. When updating the belief, pairs of beams that share propositions are joined iteratively until convergence. This method is sound but incomplete.
      </paragraph>
      <paragraph>
       We chose to compare to CBT/FBT for two reasons: First, it is the current state of the art in terms of its ability to scale-up to large domain sizes. Second, it has the best worst-case bounds on run-time due to its analysis in terms of problem width. In fact, a key point of our theoretical analysis is to show that regression enjoys similar properties. Thus, when the problem width is bounded by a constant or is even logarithmic in the input size, these are the only two methods that have polynomial run-time guarantees (contingent on a convenient representation of the initial state).
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       Comparing regression to BG beam tracking
      </section-title>
      <paragraph>
       We first compare our implementation of regression to the published implementation of beam tracking.{sup:6} This implementation is non-generic, allowing execution only over three domains: Battleship, Wumpus, and Minesweeper, where it performs very well. Also, its implementation makes use of a manually designed multi-valued variable representation. As we have explained above (Section 5), the use of multi-valued variables impacts the width of the problem, and thus the worst-case performance of the methods. Furthermore, it is reasonable to believe that it lends additional practical efficiency, compared to the more generic PDDL-like propositional representation that we use.
      </paragraph>
      <paragraph>
       Our experiments were run on a Windows Server machine with 24 2.66 GHz cores (although only a single core is used), and 32 GB RAM. Regression is implemented in C# while beam tracking uses Cygwin.
      </paragraph>
      <paragraph>
       Nevertheless, as shown in Table 2 our regression-based method which is sound, complete, and uses a generic implementation, accepting domains in a PDDL-like language, does very well. It is able to scale-up to similar domain sizes as BG, although in the Battleship domain it is much slower. It is interesting to observe that in the Wumpus domain, the only domain in which Boolean variables are used by BG, regression is faster than beam tracking. In addition, as shown in Table 3, over domains not supported by the current BG code, regression-based belief tracking scales very well to domain sizes that cannot be handled by any other method.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       Comparing regression to a non-optimized implementation of beam tracking
      </section-title>
      <paragraph>
       To further understand how regression compares to FBT and CBT,{sup:7} we implemented a simple version of beam tracking into our own framework, which allows us to experiment with domains specified in a PDDL-like language, using the same planning heuristics and basic operations as our regression method. We implement beam tracking [5], where separated beliefs are maintained over the causally relevant propositions to any goal, precondition, or observation. In our implementation the separated beliefs are maintained by a simple DNF representation, that is, an explicit enumeration of all the possible assignments of truth values to the causally relevant propositions. As such, the local beliefs can be represented only if the number of relevant propositions (the causal width) is relatively low. In our implementation, once the number of relevant propositions grows beyond 15, enumerating the possible assignments becomes too time consuming to experiment with.
      </paragraph>
      <paragraph>
       When updating the belief, complete joins of all the possible assignments of the neighboring beliefs that share a variable in common becomes infeasible, and we therefore implement the iterative method that joins only pairs of local beliefs until convergence. We implemented an optimized join operation, removing first identical states, and searching for propositions that have only a single valid value in some belief, before running the actual join operation. In all the domains that we experiment with, only a handful of iterations were required before convergence. The implementation uses the same caching mechanism as our regression method, allowing us to use the above belief mechanism only for propositions whose value is currently unknown.
      </paragraph>
      <paragraph>
       Conforming with the definitions of Bonet and Geffner [6], the initial belief is specified only over single literals, avoiding complex constraints over sets of literals. Such constraints are introduced by the conditional effects of a special init action. As such, the implementation of these domains differs from the domains used in the experiments in the previous section, and runtime may vary. Furthermore, such an implementation is less convenient for regression, which benefits from a CNF definition of the initial belief instead of additional conditional effects that must be regressed. On the other hand, we did not implement the invariant constraints of Bonet and Geffner, which may reduce runtime for beam tracking.
      </paragraph>
      <paragraph>
       Table 4 compares the average time for executing a single action using regression and our implementation of beam tracking. When executing an action using beam tracking, we perform a belief update, including the iterative joins. When executing an action using regression we validate that the preconditions hold using one regression query, then, in case of an observation action, execute a second regression query to join the regressed observation to the initial belief state. As such, we also report in Table 4 the execution time of observation actions. In all experiments we run both methods together over the exact same sequence of actions and observations, and we report the average over 25 runs.
      </paragraph>
      <paragraph>
       There are some interesting observations in Table 4. First, in all these domains, the complete regression is much faster than the incomplete beam tracking over the larger domains. This may be attributed to the simplistic and inefficient DNF belief representation.
      </paragraph>
      <paragraph>
       Different domains exhibit different properties. The Wumpus domain has pits and wumpuses that need to be avoided, while searching for the gold that is hidden on a map. Wumpus n-m-k has a board size of {a mathematical formula}n×n with m wumpuses and k pits hidden on the board. Wumpus is perhaps the simplest domain here, with a relatively low number of causally relevant variables (4 at most), and hence scaling up does not require significant additional effort from both methods. In this domain, beam tracking is about 4 times slower than regression.
      </paragraph>
      <paragraph>
       In Battleship n, where n is the board size, the causally relevant propositions represent cells in the immediate vicinity of the tracked cell. In this domain, as the number of cells grows quadratically with the board size, the belief update becomes more difficult. We also tried to add additional constraints over cells with a distance of 2 from the tracked cell, resulting in 25 relevant literals, but our DNF belief representation could not handle this many propositions, although regression had no trouble scaling up to 25 relevant propositions.
      </paragraph>
      <paragraph>
       RockSample is arguably the most interesting domain of this set, as it contains additional conditional effects aside from the init action. In RockSample n-m, a rover patrols an {a mathematical formula}n×n board containing m rocks whose location is known. The rover can activate a medium range sensor, capturing the existence of “good” rocks containing an interesting mineral up to 2 cells away. The rover can then observe whether a green light was lit on the sensor, meaning that at least one good rock is in range. Thus, all rocks are causally relevant to the green light observation. On the other hand, during a regression of a green light observation, only rocks in range of the current cells are relevant to the observation. Indeed, this domain demonstrates the advantage of regression over beam tracking, when the contextual width, which is the number of relevant propositions given a specific sequence of actions and observations, is much lower than the true causal width of the problem.
      </paragraph>
     </section>
     <section label="7.5">
      <section-title>
       Regression and caching
      </section-title>
      <paragraph>
       In Section 7.1 we suggest an improvement to regression, caching at each time step the set of literals whose value is known at that time step. Then, future regression queries can be simplified using this cached information, resulting in smaller formulas. We experiment over the Localize domain, containing many conditional effects, and thus, potentially large regressed formulas, to study the effect of caching on regression queries.
      </paragraph>
      <paragraph>
       We measure the average time over 25 runs, with and without caching, for regressing observations. Table 5 shows the substantial benefits that the caching of known facts provides in this case. In domains with less conditional effects, such as Battleship and Wumpus, there is almost no effect to the caching of learned facts.
      </paragraph>
      <paragraph>
       Another interesting effect of caching learned facts is with respect to the action–observation sequence length. As more facts are learned, the formulas can be reduced to a smaller size. Therefore, regression queries produce larger formulas in the beginning of the action–observation sequence, and much smaller formulas later on. Fig. 2 shows the size of the formula (size of the syntax tree of the formula) and the width of the formula (number of propositions) as the length of the action–observation sequence grows, for observation regressions in the Localize domain. We report the maximal number for each time step over 25 executions.
      </paragraph>
      <paragraph>
       As can be seen, with no caching, the width of the formula is constant, including all the unknown propositions in this domain. With caching, the width rapidly becomes significantly lower. The size of the formula can be significantly larger than the width. When no caching is allowed, there are many cases where the regression queries result in very large formulas. With caching, the size of the formula is always of the same order of magnitude as the width. These experiments clearly show the value of caching learned facts.
      </paragraph>
     </section>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      We now review related work, starting with previous usage of regression for various applications, then regression in planning, and finally similar methods for belief tracking, and their comparison to our work.
     </paragraph>
     <paragraph>
      Regression was introduced into planing as a method for generalizing backwards search and goes back at least to [28]. Goal-regression refers to the computation of the weakest pre-image or weakest precondition of some goal condition under a given operator. That is, the weakest condition that if satisfied before the operator is applied ensures that the goal will hold after the operator is applied. Nowadays, regression-based planning refers to planning backwards from the goal using goal-regression. Our focus is not on regression-based planners, but on the goal regression technique as a method for answering queries about an implicitly represented belief state in planning under uncertainty with partial observability.
     </paragraph>
     <paragraph>
      Much work on goal regression techniques was done in the context of the situation calculus [20], [21]. Regression is a natural technique in situation calculus because situations are defined in terms of an initial situation and a sequence of applied actions, using the {a mathematical formula}do(a,s) relation. This is exactly the implicit state representation used in this paper. Consequently, many of the techniques explored in this paper have their background in situation calculus. The very nature of the regression formula stems from the successor-state axiom of the situation calculus. The situation calculus uses {a mathematical formula}poss(a,s) to denote that a is executable in situation s. As in our work, this aspect of the action is not propagated in the regression formula [20], [21]. More specifically, the issue of the regression of knowledge producing actions, i.e., actions with observations, was discussed in Scherl and Levesque [23], and the technique of conditioning the regression formula on the observation condition ({a mathematical formula}ωa,o in our case, and {a mathematical formula}ψ(s) in situation calculus) was considered in earlier work on diagnosis with situation calculus [18].
     </paragraph>
     <paragraph>
      However, the situation calculus is a first-order formalism that is much more expressive than the propositional formalism used in most planners. As such, it must deal with the issue of ramification, stemming from the ability to formulate various state axioms, and with quantification. And in the context of the work on reasoning about knowledge producing actions [23], the formulas developed use a modal logic of knowledge. Our work focuses specifically on the simple propositional language that is used in most current planners, and even more specifically, on belief tracking, leading to a thinner and simpler formalism. We extend Rintanen's work [22] on regression to handle observations, paying special attention to the computational complexity of the reasoning algorithms, and leading to theoretically appealing and empirically validated results.
     </paragraph>
     <paragraph>
      Explicit belief tracking refers to the maintenance of an explicit or symbolic representation of the set of possible states of the world. Enumerating the set of possible states is not a practical option – their number is worst-case exponential in the number of state variables, and in practice, it often grows quickly. To alleviate this, methods that maintain a more compact, symbolic description of the set of possible states have been developed, such as methods based on BDDs [3], prime-implicates, CNFs, and DNFs [27]. Unfortunately, symbolic representations also have an exponential worst-case description, and some methods can require worst-case exponential work per update. Furthermore, every representation that was suggested thus far, while being very compact for certain benchmark problems, demonstrated the worst-case performance on other benchmarks.
     </paragraph>
     <paragraph>
      One way to address the exponential worst-case description is to try to focus on maintaining and/or computing relevant information only. For planning algorithms we can focus on a narrower scope, which requires only answering specific queries concerning the set of possible states. CFF [15] exploited this observation within a planner that searches over belief states. It uses an implicit representation of the belief state, avoiding the explicit update of belief states. CFF maintains a copy of the state variables for every time point, together with constraints over the values of these variables. This produces a SAT encoding similar to earlier work on SAT-based solutions to planning under uncertainty [12]. The representation is updated with each action and grows linearly with the number of actions executed, and hence has low-order polynomial space complexity. However, answering a query regarding the current value of a variable requires solving an UNSAT problem is co-NP hard, although seems to work quite well in practice. As information is obtained, the representation and constraints concerning earlier stages can be simplified. Our regression-based method takes this lazy approach to the extreme, avoiding the maintenance and update required by CFF's belief representation altogether. In a previous paper [8] we showed that CFF's belief tracking method scales worse than regression.
     </paragraph>
     <paragraph>
      Closely related to CFF's method, and very similar in many aspects to our own work, is Shahaf and Amir's work on logical filtering with circuits [25]. In that work, the authors show how to maintain a circuit representation of the current belief state, whose size is polynomial in the set of propositional fluents and the length of the action–observation sequence. The circuit construction is closely related to the regression formula developed in this paper. More precisely, the circuit could be thought of as incrementally updating a regression formula for every literal in a forward manner. Initially, a circuit corresponding to the initial state formula is constructed. For each primitive proposition p, a sub-circuit that “explains” the conditions under which p is true is maintained. Initially, p is true iff it is true in the initial state. After each action and observation, the circuit is updated. The explanation for p being true following an action is based on Equation (3.2), that is, if p was true before the action was executed and was not destroyed by the action, or if p is an effect of the action. This new explanation replaces the old explanation for p (i.e., in the one that explains p in the state that preceded the execution of the last action). Thus, one does not explicitly maintain explanations for intermediate states, although, in fact, a node that corresponds to the explanation of every primitive proposition at every state in the sequence will always be maintained in the circuit. If an observation p is made, then the initial state formula is conjoined with p's explanation.
     </paragraph>
     <paragraph>
      If a standard formula is used, the new formula that “explains” p could be twice as large as the old formula, and hence the formula grows exponentially. However, when a circuit representation is used, identical substructures require only a single copy, plus multiple pointers to this copy, ensuring a poly-sized representation. Although constructed forward and incrementally, the circuit represents, compactly, the same formula that we obtain via regression, with observations conjoined to the initial belief state, and without the intermediate simplifications we perform on that formula. Hence, the essential differences between Shahaf and Amir's method and ours are as follows: they use a compact representation for the regression formula, constructing and updating this formula for every primitive proposition at every step. This formula is maintained in the form of a circuit that need not replicate identical sub-structure. A new explanation is generated following each action using a forward update of the formula. When querying, they feed the entire formula into a SAT solver for circuits. As such, their approach is very similar to CFF, aside from the different formula structure. As opposed to CFF and the Shahaf and Amir, we take a lazy approach, in which very little information (i.e., our cache) is maintained, and a regression formula is computed on the fly when needed. This formula is simplified during its backwards construction using the cache and previous observations.
     </paragraph>
     <paragraph>
      In many respects, Shahaf and Amir's technique is quite similar to CFF's belief maintenance approach. CFF explicitly maintains a proposition for every fluent and every time point, which corresponds to the pointers used within the circuit. Both structures implicitly represent the belief state using a formula, that is maintained and updated as actions are executed. Both representations require only low-order polynomial space to maintain, and this is achieved by not replicating identical sub-structures – in the case of circuits these are sub-circuits, and in the case of the SAT encoding, these are identical intermediate variables. In both cases, verifying the validity of some condition requires a validity check (with respect to the current circuit or formula), which is Co-NP hard. It is claimed that the circuit representation, with its explicit sub-structures, can be exploited for added efficiency, and Shahaf and Amir's experimental results indicate that it is better than what they refer to as “unrolling”, which appears to be similar to the SAT-based encoding. It is an open question whether similar width-based guarantees can be provided for the circuit validity checks. Given the close similarity to our regression formula with regressed observation (Section 6.1), it is likely to face similar issues regarding the impact of regressed observations on the structure of the initial state formula.
     </paragraph>
     <paragraph>
      More recently, Bonet and Geffner further exploited the idea of focusing on relevant information. They maintain the beliefs over each variable p separately, by maintaining the possible set of assignments of relevant variables to p[5], [6]. In this scheme, a variable may appear in multiple belief spaces, corresponding to different variables, as one variable may be relevant to multiple variables and the “belief-state” associated with each variable is exponential in the number of variables relevant to it. In problems where the number of relevant variables is large, this can still be too large to store and update.
     </paragraph>
     <paragraph>
      To address this problem, BG suggest maintaining beliefs only over the causally relevant variables, ignoring the evidentially relevant ones. To compensate for the lack of evidentially relevant variables, they maintain causally relevant beliefs over observed variables as well. Thus, their second algorithm, causal belief tracking (CBT) uses more factored beliefs, but of a smaller width – the causal width of the problem.
     </paragraph>
     <paragraph>
      To pass information between different factored beliefs that share similar variables, CBT uses join operations. But while the size of the factored beliefs is reduced in CBT, the complete join operation over all beliefs that share a variable may still be infeasible. BG therefore suggest to run iterative join operations of pairs of beliefs that share a variable, until convergence. They also suggest to leverage invariant constraints over the problem to add power to the iterative join operations. This version of CBT, which they call beam tracking is sound but incomplete, yet scales up to much larger problems than previous methods. An extensive empirical evaluation of this method with the regression method was presented in the previous section.
     </paragraph>
    </section>
   </content>
  </root>
 </body>
</html>