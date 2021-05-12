<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Computing cooperative solution concepts in coalitional skill games.
   </title>
   <abstract>
    We consider a simple model of cooperation among agents called Coalitional Skill Games (CSGs). This is a restricted form of coalitional games, where each agent has a set of skills that are required to complete various tasks. Each task requires a set of skills in order to be completed, and a coalition can accomplish the task only if the coalitionʼs agents cover the set of required skills for the task. The gain for a coalition depends only on the subset of tasks it can complete. We consider the computational complexity of several problems in CSGs, such as testing if an agent is a dummy or veto agent, computing the core and core-related solution concepts, and computing power indices such as the Shapley value and Banzhaf power index.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Game theory has uses in many real-world domains, including those involving automated agents. These domains encompass electronic commerce, auctions, and general resource allocation scenarios. One way to analyze these domains is to model them as multi-agent systems, consisting of self-interested agents, with possibly conflicting preferences. Because of the desire to embed game-theoretic principles into artificial multi-agent systems, computational aspects of game theory and social choice have been extensively studied in recent years.
     </paragraph>
     <paragraph>
      A specific domain on the border between game theory and computation is that of cooperative domains. Cooperation is a key issue in many automated agent scenarios. When agents are self-interested, a stable coalition can only be formed if the gains won as a result of the cooperation are distributed in an appropriate way. Cooperative game theory considers the question of how these gains should be distributed, and provides several solution concepts. Several such solutions have been offered, such as the core [40], the ϵ-core and least-core [62], the Shapley value [60], and the nucleolus [58]. The simplest of these concepts is the core, where no coalition of agents can find an outcome that they all prefer (at least one strictly) by breaking away from the game and working amongst themselves.
     </paragraph>
     <paragraph>
      One way in which these solution concepts have been employed has been to measure the power that agents have in real-life domains, such as parties forming a coalition in legislative bodies. This has led to the definition of several power indices, such as the Banzhaf [14] and Shapley-Shubik [61] power indices.
     </paragraph>
     <paragraph>
      Constructing real-world applications requires taking computational considerations into account, and considering the challenges of engineering efficient and robust multi-agent systems. Solutions offered by game theory have been adopted by computer scientists, who have explored their attendant computational considerations [56], [69], [63], [22], [23], [28], [24]. Specifically, much work has been done on computational aspects of agent collaboration through cooperative game theory [19]. For example, agents should be able to concisely express their preferences and capabilities when interacting, and the procedures used by these agents to decide how to operate must be computationally tractable.
     </paragraph>
     <section label="1.1">
      <section-title>
       Motivation
      </section-title>
      <paragraph>
       This paper defines a class of games called Coalitional Skill Games, that model collaboration and are based on the abstract notions of tasks and the skills required to complete them. We begin with a few examples of domains that can be modeled using our class of games.
      </paragraph>
      <paragraph>
       Our first example is that of several companies that are attempting to drill and refine oil at four different locations. The first oil patch is worth $200 million, and is located under ice. The second oil patch is located under the sea and worth $500 million, and the third is located in a remote desert and worth $400 million. To obtain these values, the oil first needs to be extracted. The three oil patches mentioned above contain crude oil, and that oil requires refining to be worth any money. One additional oil patch is also located in the desert, and is a pure oil patch that requires no refining, and worth $10 million. There are four companies that may attempt to engage in activities related to the oil—Aliceʼs Refineries Inc., Bobʼs Oil Industries Ltd., Charlieʼs Petroleum Ltd., and Danaʼs Gasoline Inc., or A, B, C, D for short. Only A and C can refine oil, while B and C have ice drilling facilities. Only B and D can drill in the desert, and the only company with sea drilling capability is D. Obviously, together all the companies can exploit all the patches, with a total worth of {a mathematical formula}200+500+400+10=$1110 million.
      </paragraph>
      <paragraph>
       How should this total reward be split among the companies? What is the fair share each company should get, assuming they work together to bring the oil to market? What would be a stable allocation of the gains? In this example, A cannot achieve any value on its own, as it cannot drill any oil, and D cannot achieve any value on its own as it cannot refine the oil or drill the pure oil in the desert. A and D together can drill and refine all the oil in the desert and sea patches, worth {a mathematical formula}500+400+10=$910 million. On the other hand, without D it is impossible to drill the most lucrative sea patch, worth $500 million of the total $1110 million, and so D certainly helps in achieving the total gain. B might suggest allocating $400 million to A, $150 million to B and C, and $410 million to D. But companies A and D are unlikely to find this satisfying, as they can achieve $910 million on their own. Are there stable payoff allocations in this domain?
      </paragraph>
      <paragraph>
       Another example is voting. Consider a vote in which different entities control how different subsets of the voters choose to vote, and where a coalition of entities can control the votes of all the voters that can be controlled by any member of the coalition. A coalition may have to control more than a certain number of voters to win an election, and thus its utility can depend on the number of voters it controls. A similar example is cooperative knowledge sharing[31], [38]. In such domains, each party may have access to information regarding various propositional variables, and a coalition wins if it can determine the value of a particular subset of the variables that are of interest.
      </paragraph>
      <paragraph>
       Yet another example is the domain of robots and human rescuers in a disaster zone with victims trapped in multiple locations, where each location requires various skills in order to gain access [46], [57]. For example, in the case of a fire, rescuing a trapped victim may require a robot for an initial visual inspection, a firefighter to reach the victim, a stretcher carrier to evacuate the victim outside of the building, and a medic to give initial treatment. Disaster budgets may be allocated to several agencies in charge of handling such situations (for example, different provinces or states may be allocated such budgets). In case of a disaster, an agency may request the assistance of fellow agencies. For example, one agency may request additional firefighters, medics or robots from a fellow agency. How should the budget or costs be allocated to the agencies in such cases?
      </paragraph>
      <paragraph>
       Our final example focuses on the domain of multi-sensor networks[64], [27]. Consider multiple sensor-array facilities, each with several sensors of different types, where each sensor covers a certain geographical area. The goal of the sensor array is to track multiple objects, each traveling through a different path over time. Each sensor can cover a part of the area at different times, and although no single sensor can fully track the objects, some coalitions of sensor arrays can track an object all the time, or even all the objects. When faced with different rewards or budgets for tracking the various objects, which coalition is likely to form? How would this reward be shared?
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Contribution
      </section-title>
      <paragraph>
       We consider a specific model of cooperation among agents, that of Coalitional Skill Games (CSGs). In this form of coalitional games, agents must cooperate to complete certain tasks. Performing each task involves using a set of required skills, and a coalition can accomplish the task only if it covers the taskʼs required skills. Central to solution concepts for coalitional games is the idea of a characteristic function, which defines a coalitional value for every subset of agents. CSGs impose a particular structure on the characteristic function of coalitional games, where this structure depends in a precise way on a problem of task allocation. In general CSGs, the characteristic function of the game maps the achieved set of tasks to a real value.
      </paragraph>
      <paragraph>
       CSGs are highly expressive. For example, CSGs are able to easily express the domains presented in Section 1.1. A task in these domains can include producing oil, rescuing a victim, tracking an object, transmitting data to a certain client, controlling a certain voter, and so forth. In each of these domains, completing a task depends on having the necessary skills. Questions of interest in these domains include how to divide the total gains of a coalition among its members, and finding which members of the coalition are powerful.
      </paragraph>
      <section label="1.2.1">
       <section-title>
        Restricted classes of CSGs and threshold versions of CSGs
       </section-title>
       <paragraph>
        The expressive power of general CSGs comes at the cost of having a representation that is exponential in the number of tasks, which results in high computational complexity in solving various questions related to such games. To achieve a good compromise between expressiveness and conciseness we can impose additional, natural restrictions on the structure of the underlying task allocation problems, and therefore on the characteristic function of the coalitional games. For example, it is possible to define the value a coalition can achieve as the number of tasks it accomplishes, resulting in TCSG—Task Count Skill Games. Another possibility is giving each task its own weight, and defining the value of a coalition as the sum of weights of the accomplished tasks, resulting in WTSG—Weighted Task Skill Games. TCSGs easily allow one to express the fact that the utility of a coalition of agents depends on the number of tasks that they can jointly perform, while WTSG allows for weighting such tasks according to their importance.
       </paragraph>
       <paragraph>
        Any STSG can be expressed as a TCSG (with a single task), and any TCSG can be expressed as a WTSG (with equal weights for the tasks). We can denote this as STSG ⊆ TCSG ⊆ WTSG. We explore the issue of the expressivity of these representation language in Section 3.
       </paragraph>
       <paragraph>
        We also consider threshold versions of skill games, that capture the notion of “acceptable performance,” where there is a discontinuity in utility beyond a certain performance level. Such discontinuities are very common in many real-world scenarios. For example, agents may be under a contract to perform at least a certain number of tasks or to achieve a certain target in sales or profits, as is the case with many service level agreements and employment contracts with sales quotas [21], [49], [26]. Another example is voting and lobbying effort. In many voting situations a decision is made based on the opinion of the majority of voters, so in such cases passing a decision requires convincing at least half of the decision makers. In this case, no utility is gained by convincing less than the required quota of the decision makers. Similarly, once half of the decision makers are convinced, no additional utility is gained by convincing additional decision makers. This has typically been modeled as weighted threshold games (sometimes called weighted voting games) or as lobbying games [33], [14], [15], [53].
       </paragraph>
       <paragraph>
        Both TCSGs and WTSGs also have simple threshold versions, where a coalition of agents either “wins” or “loses.” These CSGs are simple skill games, where the characteristic functionʼs range is either 0 or 1. In TCSG-T, task count skill games with a threshold, a coalition wins if it manages to accomplish at least k tasks, and in WTSG-T a coalition wins if the sum of weights of the tasks it accomplishes is more than k. The simplest form of skill games is that of single task skill games (STSGs), where a single task has to be performed, and requires a coalition to cover all the required skills for that task. These threshold versions can easily express lobbying efforts where agents must complete various tasks to persuade decision makers, or where they must complete different tasks in order to sell products to meet a sales quota.
       </paragraph>
       <paragraph>
        Our threshold versions of CSGs are somewhat similar in spirit to threshold versions of other cooperative games [33], [12], [2], [5], which are discussed in Section 1.3 and Section 5.
       </paragraph>
      </section>
      <section label="1.2.2">
       <section-title>
        Main results
       </section-title>
       <paragraph>
        We first show that even very restricted forms of CSGs are still very expressive. One of the most general classes of cooperative games is that of increasing games, where the value generated is monotonically increasing in the set of agents in the coalition. Even the most restrictive class of STSGs can represent any increasing game where a coalition either wins or loses, and WTSGs can represent any increasing game. We then explore the complexity of computing important properties of CSGs such as power indices and payoff distributions. For power indices, we examine the complexity of calculating the Shapley value and the Banzhaf power index. The Shapley value defines a distribution of the gains of the coalition that meets certain desired fairness criteria. It can also be used to measure the power of agents. The Banzhaf index is a related power index, which focuses on slightly different fairness axioms.
       </paragraph>
       <paragraph>
        For payoff distributions, we first examine the complexity of testing whether a certain agent is a dummy, which means that his addition to any coalition never increases the value that coalition can achieve, and whether an agent is a veto agent, which means that no coalition can win without that agent. The problem of computing the core of a CSG, and testing whether the core is non-empty, is central to determining the basic stability properties of a CSG. If the core exists, then it is possible to distribute the gains in a stable way, so that no subset of the agents will prefer to break away. If the core is empty, then any division of the payoffs is unstable and it is typical to consider relaxed solutions such as the least-core, which seeks to find an allocation of gains to agents in order to minimize the maximum possible gain that any coalition could achieve by breaking away.
       </paragraph>
       <paragraph>
        Our results show that computing the value of a coalition and finding veto agents is tractable in all the above domains. Indeed, in many of them it is possible to test for dummy agents and also compute payoff distributions (also called imputations) in the core. Problems related to the least-core are generally hard, but we present positive results for restricted domains. With regard to power indices, we show that they are typically hard to compute precisely. However, these can be approximated by sampling player permutations or coalitions and averaging the marginal contributions of the target agent [8]. Thus, this work shows that the CSG representation is expressive, and computationally tractable in restricted forms.
       </paragraph>
      </section>
     </section>
     <section label="1.3">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       The concept of the core originated with Gillies [40], the ϵ-core and least-core were introduced by Shapley and Shubik [62], and the Shapley value was introduced by Shapley [60]. The problems of finding the optimal coalition structure and determining whether a coalition structure is stable have been studied in a number of domains [63], [27], including the CSG domain [9]. Values similar to the Shapley value have been used to measure power, e.g., via the Shapley–Shubik [61] and Banzhaf [14] power indices. Deng and Papadimitriou [30] showed that computing the Shapley value in weighted voting games is #P-complete, and that calculating both Banzhaf and Shapley–Shubik indices in weighted voting games is NP-complete [50]. Several papers deal with computing, comparing, and approximating power indices, in general and in restricted domains [51], [30], [24], [36], [8].
      </paragraph>
      <paragraph>
       Conitzer and Sandholm [24] use a decomposition of a coalitional game to several domains to ease the calculation of the Shapley value. While this decomposition technique makes the computation of the Shapley value easier, the same technique cannot be directly used for the Banzhaf index, which we consider in this paper. Also, while our representation employs a decomposition technique via tasks, the success of such tasks depends on a set of skills, rather than on a complete coalitional subgame. Thus our representation is less expressive, but allows for the tractable solution of problems that cannot be easily solved in the more complex decomposition model.
      </paragraph>
      <paragraph>
       There has been significant research on the trade-offs between expressiveness and computation for cooperative games. We examine the relation between the CSG model and other representation languages for cooperative games in Section 5, after discussing our technical results. We compare with linear production games [52], where agents pool together resources in order to manufacture finished goods that can be sold at a given market price. The utility of a coalition in this model is its maximal revenue, achieved when manufacturing the optimal achievable bundle of finished goods, as given by the solution to a certain linear program. Also closely related is the Coalitional Resource Games model [67], in which agents wish to achieve various goals, and are endowed with certain amounts of resources required to achieve these goals. Wooldridge and Dunne [67] examined the reasonable outcomes of agent interaction in such settings. Also similar is a representation adopted by Yokoo et al. [68] for anonymous environments where an agent may use false names and distribute its ability among these identities.{sup:1}
      </paragraph>
      <paragraph>
       Additional work on representation includes Bilbao [16], who studies cooperative games on several combinatorial structures. The marginal contribution network language [44] represents the value of a coalition using a set of rules regarding the participating agents. Another model, cooperative graph games, considers games where agents are represented as nodes of a weighted graph, and a coalitionʼs value is determined by the total weight of the edges that it contains [30]. The sparse synergy representation [23] relies on super-additivity, and is concise when the number of synergies between coalitions is low. The sparse synergy representation allows for efficient checking of whether a given outcome is in the core, but determining whether the core is non-empty remains NP-complete. The Multi-Attribute Coalitional Games (MACG) [45] provides a representation of coalitional games where the value of a coalition is described by a set of agent attributes, along with functions that aggregate the attributes of agents to a single number. Other work has considered coalitional games played over networks, such as network flow games, connectivity games and spanning connectivity games [12], [3], [13]. Several papers have examined the Cost-of-Stability and other solution concepts in network domains [10], [7], [54], [2].
      </paragraph>
     </section>
     <section label="1.4">
      <section-title>
       Outline
      </section-title>
      <paragraph>
       In Section 2 we give some background concerning coalitional games, and define the CSG model. Section 3 examines the expressiveness of the CSG representation of cooperative games. In Section 4 we present the main algorithms and complexity results of the paper. Section 5 examines closely-related models in more detail, and we conclude in Section 6.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this section, we define the CSG model and the game-theoretic concepts that are examined in the context of CSGs.
     </paragraph>
     <section label="2.1">
      <section-title>
       Cooperative game theory solution concepts
      </section-title>
      <paragraph label="Definition 1">
       Transferable Utility (TU) coalitional games provide a model for collaboration between agents. Such games are defined in terms of a specification for the value that each subset of agents (called a coalition) can achieve, while abstracting away details regarding how this value is achieved by the coalition. In the TU-coalitional game model, agents may also share the utility generated by the coalition in any way they choose through side payments among agents. A transferable utility coalitional gameΓ is composed of a set {a mathematical formula}I={a1,…,an} of {a mathematical formula}|I|=n agents, and a characteristic function mapping any subset (coalition) of the agents to a real value {a mathematical formula}vΓ:2I→R, indicating the total utility that these agents achieve together. When the game Γ is clear from the context, we sometimes omit the Γ subscript, and simply denote the characteristic function v.
      </paragraph>
      <paragraph>
       Two common assumptions about coalitional games are that they are increasing and super-additive. A coalitional game Γ is increasing if for all coalitions {a mathematical formula}C′⊂C⊆I we have {a mathematical formula}vΓ(C′)⩽vΓ(C), and is super-additive when for all disjoint coalitions {a mathematical formula}A,B⊂I we have {a mathematical formula}vΓ(A)+vΓ(B)⩽vΓ(A∪B). In some cases increasing games are referred to as monotone games. In super-additive games, it is always worthwhile for two subcoalitions to merge, so that the grand coalition has the largest total utility.
      </paragraph>
      <paragraph>
       In a simple coalitional game Γ, {a mathematical formula}vΓ only gets values of 0 or 1 ({a mathematical formula}vΓ:2I→{0,1}). We say a coalition {a mathematical formula}C⊆Iwins if {a mathematical formula}vΓ(C)=1, and say it loses if {a mathematical formula}vΓ(C)=0. An agent i is critical in a winning coalition C if the agentʼs removal from that coalition would make it a losing coalition: {a mathematical formula}vΓ(C)=1, {a mathematical formula}vΓ(C∖{i})=0.
      </paragraph>
      <paragraph>
       The characteristic function only defines the gains a coalition can achieve, but does not define how these gains are distributed among the agents.
      </paragraph>
      <paragraph label="Definition 2">
       An imputation (also known as a “payoff vector”) {a mathematical formula}(p1,…,pn) is a division of the gains of the grand coalition among the agents, where {a mathematical formula}pi∈R, such that {a mathematical formula}∑i=1npi=v(I).{sup:2}
      </paragraph>
      <paragraph>
       We call {a mathematical formula}pi the payoff of agent {a mathematical formula}ai, and denote the payoff of a coalition C as {a mathematical formula}p(C)=∑i∈{i|ai∈C}pi. An important question is of course how to determine which imputations are likely to be chosen by agents sharing their joint gains, or to characterize imputations with desirable properties such as fairness. Game theory offers several answers to this issue.
      </paragraph>
      <section label="2.1.1">
       Individual rationality, the core, ϵ-core, and least-core
       <paragraph>
        A minimal requirement for an imputation is that of individual rationality, which states that for any agent {a mathematical formula}ai∈C, we have that {a mathematical formula}pi⩾v({ai})—otherwise, some agent is incentivized to work alone. Similarly, we say a coalition C blocks the imputation {a mathematical formula}(p1,…,pn) if {a mathematical formula}p(C)&lt;v(C), since the members of C can split from the original coalition, derive the gains of {a mathematical formula}v(C) in the game, give each member {a mathematical formula}ai∈C its previous gains {a mathematical formula}pi—and still some utility remains, so each member can get more utility. Similarly, it is possible to define the degree by which a subcoalition is incentivized to deviate from the grand coalition.
       </paragraph>
       <paragraph label="Definition 3">
        Given an imputation {a mathematical formula}p=(p1,…,pn), the excess of a coalition is {a mathematical formula}e(C)=v(C)−p(C), which quantifies the amount the subcoalition C can gain by deviating and working on its own.
       </paragraph>
       <paragraph label="Definition 4">
        A coalition Cblocks the imputation {a mathematical formula}p=(p1,…,pn) if its excess under this imputation is strictly positive, {a mathematical formula}e(C)&gt;0. If a coalition C blocks the imputation p, we say that C is unstable under p.
       </paragraph>
       <paragraph>
        A prominent solution concept focusing on stability is that of the core [40].
       </paragraph>
       <paragraph label="Definition 5">
        The core of a coalitional game Γ is the set of all imputations {a mathematical formula}(p1,…,pn) that are not blocked by any coalition, so that for any coalition C, we have {a mathematical formula}p(C)⩾vΓ(C).
       </paragraph>
       <paragraph>
        Having an imputation (payoff distribution) in the core indicates that no subset of the coalition is incentivized to split.
       </paragraph>
       <paragraph>
        The core can be empty, which occurs when every possible imputation in that case is blocked by some coalition. In such cases we must relax the requirement of the solution concept. For example, deviating from the current coalition structure and forming an alternative coalition may be costly. Thus, coalitions that only have a small incentive to drop out of the grand coalition would choose to remain. A relaxed solution concept that follows this rationale is the ϵ-core [62]:
       </paragraph>
       <paragraph label="Definition 6">
        The ϵ-core is the set of all imputations {a mathematical formula}(p1,…,pn) such that the following holds: for any coalition {a mathematical formula}C⊆I, {a mathematical formula}p(C)⩾vΓ(C)−ϵ.
       </paragraph>
       <paragraph label="Definition 7">
        Under an imputation in the ϵ-core, the excess {a mathematical formula}e(C)=vΓ(C)−p(C) of any coalition C is at most ϵ. If ϵ is large enough, the ϵ-core is guaranteed to be non-empty. A natural question is to find the smallest value of ϵ that makes the ϵ-core non-empty. This solution concept is known as the least-core. Formally, consider the game Γ and the set {a mathematical formula}{ϵ|theϵ-core ofΓis not empty}. This set is compact, and thus has a minimal element {a mathematical formula}ϵmin. The least-core of the game Γ is the {a mathematical formula}ϵmin-core of Γ.
       </paragraph>
       <paragraph>
        The imputations in the least-core distribute the gains in a way that minimizes the worst-case deficit, or in other words, minimizes the incentive of a coalition to drop out of the grand coalition.
       </paragraph>
       <paragraph>
        Although the least-core minimizes the worst-case deficit, it can still leave multiple possible imputations. The least-core does not, for example, minimize the number of coalitions with this worst-case deficit, nor does it minimize the second-worst deficit. The nucleolus[58] refines the least-core, selecting the lexicographically minimal core.
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        The Shapley value and Banzhaf power index
       </section-title>
       <paragraph>
        Another solution concept, which defines a single imputation, is the Shapley value [60]. This approach focuses on fairness rather than on stability. This value is the only imputation (payoff distribution) that fulfills certain fairness axioms [60].{sup:3} We denote by π a permutation of the agents, so {a mathematical formula}π:{1,…,n}→{1,…,n} and π is onto, and by Π the set of all possible such permutations. Denote by {a mathematical formula}Sπ(i) the predecessors of i in π, so {a mathematical formula}Sπ(i)={j|π(j)&lt;π(i)}.
       </paragraph>
       <paragraph label="Definition 8">
        The Shapley value of a game Γ (with characteristic function {a mathematical formula}vΓ) is given by the imputation {a mathematical formula}ϕ(vΓ)=(ϕ1(vΓ),…,ϕn(vΓ)) where{a mathematical formula}
       </paragraph>
       <paragraph>
        The Shapley value can be interpreted as the marginal contribution an agent makes, averaged across all possible permutations of agents that may occur. The marginal contribution of an agent is the amount of additional utility generated when that agent is added to its predecessors in the permutation.
       </paragraph>
       <paragraph>
        An important application of the Shapley value is that of power indices, which attempt to measure an agentʼs ability to change the outcome of a game, and are used (for example) to measure political power. One prominent power index is the Shapley–Shubik index, which is simply the Shapley value in a simple coalitional game. Since in such a game the value of a coalition is either 0 or 1, the formula for {a mathematical formula}ϕi(v) simply counts the fraction of all orderings of the agents in which agent i is critical for the coalition of its predecessors and itself.
       </paragraph>
       <paragraph>
        Another prominent power index, again defined for any simple coalitional game, is the Banzhaf power index [14]. The Banzhaf index depends on the number of coalitions in which an agent is critical, out of all possible coalitions.
       </paragraph>
       <paragraph label="Definition 9">
        The Banzhaf power index of a game Γ (with characteristic function {a mathematical formula}vΓ) is given by {a mathematical formula}β(vΓ)=(β1(vΓ),…,βn(vΓ)) where{a mathematical formula}
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Coalitional Skill Games (CSGs)
      </section-title>
      <paragraph>
       A coalitional skill domain is composed of a set of agents, {a mathematical formula}I={a1,…,an}, a set of tasks {a mathematical formula}T={t1,…,tm}, and a set of skills {a mathematical formula}S={s1,…,sk}. Each agent {a mathematical formula}ai has a set of skills {a mathematical formula}S(ai)⊆S,{sup:4} and each task {a mathematical formula}tj requires a set of skills {a mathematical formula}S(tj)⊆S. We denote the set of skills a coalition C has by {a mathematical formula}S(C)=⋃ai∈CS(ai). We say a coalition of agents {a mathematical formula}C⊆I can perform a task {a mathematical formula}tj if every skill required to perform the task is owned by some agent in the coalition, so {a mathematical formula}S(tj)⊆S(C). We denote the set of tasks a coalition C can perform as {a mathematical formula}T(C). The set {a mathematical formula}T(C) consists of all the tasks {a mathematical formula}tj∈T such that C can perform {a mathematical formula}tj.
      </paragraph>
      <paragraph>
       We denote the set of skills required to perform a set of tasks {a mathematical formula}T′⊆T by {a mathematical formula}S(T′)=⋃tj∈T′S(tj). A task value function maps a subset of the tasks a coalition achieves to a real value: {a mathematical formula}u:2T→R. We normalize the function u such that the utility of the empty task set is zero, so {a mathematical formula}u(∅)=0. We also generally assume that we can freely dispose of tasks by not performing them. Thus, u is increasing; so if {a mathematical formula}T1⊂T2⊆T, we have {a mathematical formula}u(T1)⩽u(T2). The free disposal of tasks has important implications, as it means a coalition can never lose utility by being able to perform more tasks. Having the skills required to perform a certain task does not mean the coalition must perform the task. Rather, the coalition may decide not to make use of these skills.
      </paragraph>
      <paragraph>
       An alternative definition may associate some tasks with a negative utility, but our assumption throughout this work is that the utility gained by a coalition is monotone in the set of tasks the coalition can achieve.{sup:5}
      </paragraph>
      <paragraph>
       We define the coalitional skill game for a coalitional skill domain as follows:
      </paragraph>
      <paragraph label="Definition 10">
       CSGA CSG is the coalitional game Γ in a coalitional skill domain, where the players are the agents of the coalitional skill domain, and the characteristic function of a coalition is the value of the tasks that coalition can perform: {a mathematical formula}vΓ(C)=u(T(C)).
      </paragraph>
      <paragraph label="Lemma 1">
       All CSGs are increasing coalitional games.
      </paragraph>
      <paragraph label="Proof">
       Adding agents to a coalition only adds skills to that coalition, so if {a mathematical formula}C′⊆C, we have {a mathematical formula}S(C′)⊆S(C) and thus {a mathematical formula}T(C′)⊆T(C), and {a mathematical formula}u(T(C′))⩽u(T(C)). Therefore, if {a mathematical formula}C′⊆C we get that {a mathematical formula}vΓ(C′)⩽vΓ(C), so CSGs are increasing.  □
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Restricted forms of CSGs
      </section-title>
      <paragraph>
       The ability to tractably answer questions regarding CSGs depends on how they are represented. A naive representation of a CSG is exponential in {a mathematical formula}|T| since every subset of tasks is associated explicitly with the value. In order to make progress we consider restricted forms of CSGs, that remain expressive (e.g., allowing use to represent any monotone characteristic function) while allowing for computational analysis.
      </paragraph>
      <paragraph>
       One restricted form of CSGs expresses the value of a coalition as the number of tasks that coalition can accomplish. This restricted form of CSGs is called TCSG—Task Count Skill Games. A representation of the characteristic function in a TCSG simply contains a list of the tasks and a list of required skills for each task.
      </paragraph>
      <paragraph label="Definition 11">
       TCSGLet {a mathematical formula}T′⊆T be a subset of tasks. A TCSG is a CSG where task value function {a mathematical formula}u(T′)=|T′|.
      </paragraph>
      <paragraph>
       A representation that is more general than TCSG but still concise is that of WTSG—Weighted Task Skill Games. In a WTSG, each task {a mathematical formula}tj has an associated weight {a mathematical formula}wj, and the characteristic function is the sum of the weights of the accomplished tasks.
      </paragraph>
      <paragraph label="Definition 12">
       WTSGLet {a mathematical formula}T′⊆T be a subset of tasks. A WTSG is a CSG where each task {a mathematical formula}tj∈T has a weight {a mathematical formula}wj∈R+.{sup:6} The task value function {a mathematical formula}u(T′)=∑j∈{j|tj∈T′}wj.
      </paragraph>
      <paragraph>
       CSGs where the task value function u can only obtain the values 0 and 1, so {a mathematical formula}u:2T→{0,1}, are called simple skill games. We say a task subset T wins the game if {a mathematical formula}u(T)=1, otherwise we say T loses the game. Since for any coalition C we have {a mathematical formula}vΓ(C)=u(T(C)), in simple skill games {a mathematical formula}vΓʼs range is also {a mathematical formula}{0,1} and we have {a mathematical formula}vΓ:2I→{0,1}.
      </paragraph>
      <paragraph label="Definition 13">
       Both TCSG and WTSG have special cases that are simple skill games. These games require the number of completed tasks or the total weight of completed tasks to exceed a certain threshold value k for a coalition to win. These versions are called TCSG-T (Task Count Skill Games with Threshold) and WTSG-T (Weighted Task Skill Games with Threshold). TCSG-TLet {a mathematical formula}T′⊆T be a subset of tasks. TCSG-T is a CSG with a threshold k where the task value function is {a mathematical formula}u(T′)=1 if {a mathematical formula}|T′|⩾k and {a mathematical formula}u(T′)=0 otherwise. Thus, the game has the characteristic function {a mathematical formula}vΓ(C)=1 if {a mathematical formula}|T(C)|⩾k and {a mathematical formula}vΓ(C)=0 otherwise.
      </paragraph>
      <paragraph label="Definition 14">
       WTSG-TLet {a mathematical formula}T′⊆T be a subset of tasks. WTSG-T is a CSG where each task {a mathematical formula}tj∈T has a non-negative weight {a mathematical formula}wj∈R and with a threshold k, where the task value function u is defined as {a mathematical formula}u(T′)=1 if {a mathematical formula}w(T′)&gt;k and {a mathematical formula}u(T′)=0 otherwise. Thus, the game has the characteristic function {a mathematical formula}vΓ(C)=1 if {a mathematical formula}w(T(C))⩾k and {a mathematical formula}vΓ(C)=0 otherwise.
      </paragraph>
      <paragraph>
       The most restricted form of CSGs is that of STSG—a Single Task Skill Game. In an STSG, there is only one task t, whose set of required skills {a mathematical formula}S(t) are all the skills in the domain, so we have {a mathematical formula}S(t)=S. In STSGs, the task value function is {a mathematical formula}u({t})=1, and {a mathematical formula}u(∅)=0. A coalition C wins if it manages to cover all the skills, so {a mathematical formula}vΓ(C)=1 if and only if {a mathematical formula}S(t)⊆S(C), and since {a mathematical formula}S(t) is the set of all skills, we can simply say that a coalition wins if it covers all the skills in the domain, so {a mathematical formula}S(C)=S.
      </paragraph>
      <paragraph label="Definition 15">
       STSGAn STSG is a TCSG where there is only a single task t, so {a mathematical formula}vΓ(C)=1 if {a mathematical formula}S(C)=S and {a mathematical formula}vΓ(C)=0 otherwise.
      </paragraph>
      <paragraph label="Example 1">
       Consider an STSG, in a domain with two skills: {a mathematical formula}S={s1,s2}, the single task {a mathematical formula}t1 which requires both skills (i.e. {a mathematical formula}S(t1)={s1,s2}), and three agents, {a mathematical formula}I={a1,a2,a3}. Agent {a mathematical formula}a1 has the skill {a mathematical formula}S(a1)={s1}, and agents {a mathematical formula}a2,a3 have the skill {a mathematical formula}S(a2)=S(a3)={s2}. Since in order to complete the task a coalition needs both skills, a winning coalition must contain {a mathematical formula}a1 and one of the two agents {a mathematical formula}a2,a3. Thus, the winnings coalitions are {a mathematical formula}{a1,a2},{a1,a3} and {a mathematical formula}{a1,a2,a3}.It is easy to verify that the imputation {a mathematical formula}p=(1,0,0) is a core imputation. On the one hand, any coalition C such that {a mathematical formula}a1∉C is losing and cannot block this imputation; on the other hand any coalition {a mathematical formula}C′ such that {a mathematical formula}a1∈C′ has a payoff of {a mathematical formula}p(C′)⩾p1=1 and cannot block the imputation. Since p is not blocked by any coalition, it is in the core. Similarly, a direct computation using the formula of Definition 8 shows that the Shapley value is {a mathematical formula}ϕ=(23,16,16).
      </paragraph>
      <paragraph>
       All these restricted forms of skill games have concise representations, since we can find a succinct representation for the task value function, and thus also have a succinct representation for the characteristic function.
      </paragraph>
      <paragraph>
       These restricted representations can also model many situations. For example, TCSGs can express the fact that our goal is to save as many victims as possible in a coordinated rescue problem. WTSGs can express the fact that each oil patch has a different monetary worth, and our goal is to maximize profits. TCSG-Ts can express the fact that to be successful, we must track at least a certain number of objects in the cooperative sensor array domain.
      </paragraph>
      <paragraph>
       Some questions remain computationally hard even with these restrictions. For example, certain problems regarding power indices and the ϵ-core and least-core are generally hard even for STSGs. Below, we either suggest approximation algorithms (for computing power indices) or focus on restricted domains (for least-core related problems).
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Expressiveness of coalitional skill games
     </section-title>
     <paragraph>
      In this section we explore the ability of CSGs to express various characteristic functions.
     </paragraph>
     <paragraph>
      Lemma 1 has shown that CSGs are increasing games, so obviously CSGs cannot represent non-monotone characteristic functions. We show that the CSG representation is fully expressive for increasing games: STSGs can represent any simple increasing cooperative game, and WTSGs can represent any increasing cooperative game.{sup:7}
     </paragraph>
     <paragraph label="Theorem 1">
      STSGs are fully expressive for the class of simple increasing games: it is possible to represent any simple increasing game as an STSG.
     </paragraph>
     <paragraph label="Proof">
      Consider a given simple increasing cooperative game over the set I of players and with the characteristic function {a mathematical formula}v:2I→{0,1}. Given this original game, we construct an STSG representation for it as follows. For any losing coalition {a mathematical formula}L⊆I in the original game, we create a skill {a mathematical formula}sL. This skill is possessed by {a mathematical formula}I∖L, i.e., all the agents who are not in L, and by no other agents. The single task t in the constructed game requires all the skills, so this is a proper STSG. First note that all the agents in L do not possess the skill {a mathematical formula}sL (as by construction this skill is only possessed by agents who are not in L), so L cannot achieve the task t which requires {a mathematical formula}sL. On the other hand, consider a winning coalition {a mathematical formula}W⊆I in the original game. The original game is increasing, so since W is winning in that game, it cannot be the case that W is contained in any losing coalition L. Thus for any losing coalition L, there is an agent {a mathematical formula}j∈W such that {a mathematical formula}j∉L. By our construction, since {a mathematical formula}j∉L, player j is endowed with the skill {a mathematical formula}sL. Thus, for any skill {a mathematical formula}sL the coalition W covers {a mathematical formula}sL, so W covers all the skills and is a winning coalition. Therefore, any losing coalition in the original game is also losing in the constructed game, and any winning coalition in the original game is also winning in the constructed game, so both games have the same characteristic function.  □
     </paragraph>
     <paragraph>
      Theorem 1 shows that STSGs can represent any simple monotone game. We now show that WTSGs can represent any monotone game (not necessarily a simple game). Our method is based on game composition. Given two games over the same set I of agents, {a mathematical formula}v1 and {a mathematical formula}v2 the composed game {a mathematical formula}(v1+v2) over the agents I is defined as follows. For any coalition {a mathematical formula}C⊆I we have {a mathematical formula}(v1+v2)(C)=v1(C)+v2(C).
     </paragraph>
     <paragraph label="Lemma 2">
      If{a mathematical formula}v1and{a mathematical formula}v2have a WTSG representation, then there is a WTSG representation for{a mathematical formula}(v1+v2).
     </paragraph>
     <paragraph label="Proof">
      Let I be the set of agents in {a mathematical formula}v1 and {a mathematical formula}v2. Let {a mathematical formula}S1,S2 be the skills of the agents in {a mathematical formula}v1 and {a mathematical formula}v2, accordingly. Let {a mathematical formula}T1,T2 be the set of tasks in {a mathematical formula}v1,v2 accordingly. Name the tasks and skills such that {a mathematical formula}S1∩S2=∅ and that {a mathematical formula}T1∩T2=∅. Construct a WTSG G over the set I of agents as follows. The set of tasks in G is {a mathematical formula}T=T1∪T2. The set of skills is {a mathematical formula}S=S1∪S2. Each task requires exactly the same skills it originally required in {a mathematical formula}v1 or {a mathematical formula}v2. Every agent {a mathematical formula}ai∈I in the game G is endowed with all the skills she had in both{a mathematical formula}v1 and {a mathematical formula}v2. Denote Gʼs function as v. If a coalition C achieves a task {a mathematical formula}t∈T1 in {a mathematical formula}v1, it can also achieve it in v, as the task requires the same skills it did in {a mathematical formula}v1, and if the agents of C covered them in {a mathematical formula}v1 they also cover them in v. Similarly, if C achieves a task {a mathematical formula}t∈T2 in {a mathematical formula}v2, it can also achieve it in v. However, if C does not achieve t in {a mathematical formula}v1 it would not achieve it in v (the same skills are still missing). Similarly if C does not achieve t in {a mathematical formula}v2 it would not achieve it in v. Denote the set of tasks C can achieve in {a mathematical formula}v1 as {a mathematical formula}W1 and the tasks C can achieve in {a mathematical formula}v1 as {a mathematical formula}W2. The value C achieves in v is thus {a mathematical formula}v(C)=∑t∈W1w(t)+∑t∈W2w(t)=v1(C)+v2(C). Thus, given a WTSG representation for {a mathematical formula}v1 and {a mathematical formula}v2 we have built a WTSG representing {a mathematical formula}(v1+v2).  □
     </paragraph>
     <paragraph>
      We build a WTSG representation for a game by iterating through the possible values the gameʼs function v can take, from lowest to highest. In each step we examine the coalitions that have the next highest value in v, and construct a WTSG where these coalitions get the difference between the values. We then take the WTSG representation of the composed game.
     </paragraph>
     <paragraph label="Theorem 2">
      WTSGs are fully expressive for the class of general monotone games: it is possible to represent any monotone cooperative game as a WTSG.
     </paragraph>
     <paragraph label="Proof">
      A game G over the n agents in I, with function v has {a mathematical formula}2n different coalitions, so v has at most {a mathematical formula}2n different values. Order these values from smallest to largest to obtain {a mathematical formula}u0,…,um (where {a mathematical formula}m&lt;2n). Denote the set of coalitions which have a value of {a mathematical formula}ui as {a mathematical formula}Cui (so if {a mathematical formula}C∈Cui then {a mathematical formula}v(C)=ui). Denote {a mathematical formula}wi=ui−ui−1. Since v is monotone, {a mathematical formula}u0 is obtained by the empty coalition ∅, and w.l.o.g. we assume {a mathematical formula}u0=0.Consider the game {a mathematical formula}v1′ over the agents I, where {a mathematical formula}v1′(C)=0 if {a mathematical formula}v(C)=u0 and {a mathematical formula}v1′(C)=1 if {a mathematical formula}v(C)&gt;u0. This is a simple monotone game, so due to Theorem 1 it has an STSG representation {a mathematical formula}G1′. We can take this representation and modify the weight of the single task from 1 to {a mathematical formula}w1. This is a WTSG representation {a mathematical formula}G1 with characteristic function {a mathematical formula}v1 where {a mathematical formula}v1(C)=v(C)=u1 if {a mathematical formula}C∈Cu0∪Cu1, and where if {a mathematical formula}C∈Cui for some {a mathematical formula}i&gt;1 we have {a mathematical formula}v1(C)=u1. Now consider the game {a mathematical formula}v2′ over the agents I, where {a mathematical formula}v2′(C)=0 if {a mathematical formula}v(C)⩽u1 and {a mathematical formula}v2′(C)=1 if {a mathematical formula}v(C)&gt;u1. Again, this is a simple monotone game, and due to Theorem 1 has an STSG representation {a mathematical formula}G2′. Again we take this representation and modify the weight of the single task from 1 to {a mathematical formula}w2. This is a WTSG representation {a mathematical formula}G2, with characteristic function {a mathematical formula}v2. Due to Lemma 2 we can construct a WTSG representation {a mathematical formula}H2 for {a mathematical formula}(v1+v2). Denote the characteristic function of {a mathematical formula}H2 as {a mathematical formula}h2=(v1+v2). Note that if {a mathematical formula}C∈Cu0∪Cu1∪Cu2 we have {a mathematical formula}h2(C)=v(C), and if {a mathematical formula}C∈Cui for some {a mathematical formula}i&gt;2 we have {a mathematical formula}h2(C)=u2. We can continue this process to construct a WTSG representation for {a mathematical formula}H3 then for {a mathematical formula}H4 and so on, until we obtain the game {a mathematical formula}Hm with characteristic function {a mathematical formula}vm. However, {a mathematical formula}vm(C)=v(C) for any coalition C, so this is a WTSG representation for G, as required.  □
     </paragraph>
     <paragraph label="Example 2">
      We now provide an example for the construction in Theorem 2. Consider the game v over 3 agents {a mathematical formula}I={a1,a2,a3} with the characteristic function {a mathematical formula}v(∅)=v({a1})=v({a2})=v({a3})=0, {a mathematical formula}v({a1,a2})=v({a1,a3})=v({a2,a3})=1 and {a mathematical formula}v({a1,a2,a3})=5. In this game no single agent makes any value, any two agents generate a value of 1, and the grand coalition of all agents has the value of 5.The construction of Theorem 2 generates a WTSG representation for the game {a mathematical formula}v1′ where any two agents have a value of 1, and the grand coalition has a value of 1 as well, and composes it with a representation for the game {a mathematical formula}v2′ where any coalition short of the grand coalition has a value of 0, and the grand coalition has a value of {a mathematical formula}5−1=4.The construction for the game {a mathematical formula}v1′ is done using Theorem 1. Since in the game {a mathematical formula}v1′ the losing coalitions are the singleton coalitions {a mathematical formula}{a1},{a2},{a3}, the construction creates three skills: the skill {a mathematical formula}s11, owned by {a mathematical formula}a2 and {a mathematical formula}a3, the skill {a mathematical formula}s21, owned by {a mathematical formula}a1 and {a mathematical formula}a3, and the skill {a mathematical formula}s31, owned by {a mathematical formula}a1 and {a mathematical formula}a2. The task for the game {a mathematical formula}v1′ requires all these three skills, {a mathematical formula}s11,s21,s31.By generating a representation for {a mathematical formula}v2′, again using the construction of Theorem 1, and composing the representations for the games {a mathematical formula}v1′ and {a mathematical formula}v2′ using Lemma 2, we obtain a representation for the required game v.
     </paragraph>
     <paragraph>
      Not every increasing cooperative game has a succinct representation as a CSG. For example, the construction in Theorem 1 involved generating a skill for every losing coalition, so the number of skills in this construction may be exponential in the number of players. However we believe that many domains, such as the examples in Section 1.1, can be described as CSGs in a concise way. In the reminder of the paper, we show that CSGs also have desirable computational characteristics.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Algorithms for coalitional skill games
     </section-title>
     <paragraph>
      With general CSGs, the representation of the characteristic function may be exponential in the number of tasks. However, restricting it as is done in TCSG, WTSG, STSG (and TCSG-T and WTSG-T) gives a representation that is always polynomial. We now define the specific computational problems of interest. All of these problems are stated with regard to a given CSG, Γ, and sometimes with regard to a target agent {a mathematical formula}ai.
     </paragraph>
     <paragraph label="Definition 16">
      COALITION-VALUE (CV)Given a coalition {a mathematical formula}C⊆I and CSG Γ, compute {a mathematical formula}vΓ(C).
     </paragraph>
     <paragraph label="Definition 17">
      VETOIn a simple CSG Γ, check if {a mathematical formula}ai is a veto player, so for every winning coalition C, we have {a mathematical formula}ai∈C. In a general CSG, test if {a mathematical formula}ai is present in every coalition C where {a mathematical formula}vΓ(C)&gt;0.
     </paragraph>
     <paragraph label="Definition 18">
      DUMMYCheck if {a mathematical formula}ai is a dummy player in CSG Γ, such that for every coalition C (with {a mathematical formula}ai∉C), we have {a mathematical formula}vΓ(C∪{ai})=v(C).
     </paragraph>
     <paragraph label="Definition 19">
      CORE-NON-EMPTY (CNE)Decide whether the core of CSG Γ is non-empty.
     </paragraph>
     <paragraph label="Definition 20">
      COREReturn a representation of all imputations in the core of CSG Γ.
     </paragraph>
     <paragraph label="Definition 21">
      {a mathematical formula}ϵ-CORE-MEMBERSHIP (ECM)Given an imputation {a mathematical formula}p=(p1,…,pn), and CSG Γ, decide whether it is in the ϵ-core of the game.
     </paragraph>
     <paragraph label="Definition 22">
      SHAPLEYCompute agent {a mathematical formula}aiʼs Shapley value {a mathematical formula}ϕi(vΓ) in CSG Γ.
     </paragraph>
     <paragraph label="Definition 23">
      BANZHAFCompute agent {a mathematical formula}aiʼs Banzhaf power index {a mathematical formula}βi(vΓ) in CSG Γ.
     </paragraph>
     <paragraph>
      We summarize our results in Table 1.{sup:8} Complexity results are stated in regard to the succinct representations that are achieved through the restricted forms of CSGs. Thus, our polynomial algorithms run in time that is polynomial in the number of agent tasks and skills. Because the core may sometimes contain infinitely many imputations, it is unclear how it should be represented. When no compact representation is known we enter “N/A” in the table. We have shown that testing whether the Shapley value exceeds a given threshold is an NP-hard problem. However, we have not established whether or not it is in NP. This remains open.
     </paragraph>
     <paragraph>
      The most basic problem regarding the ϵ-core and least-core is ECM, which tests if an imputation is ϵ-stable. Table 1 shows that ECM is hard (co-NP-complete) even in the most restricted case of STSG. In domains where ECM can be solved in polynomial time, one can verify that a certain imputation is in the ϵ-core, so it is “stable enough”. In such domains, another interesting problem is finding such a “sufficiently stable” imputation (i.e., an imputation in the ϵ-core). Further, one may want to determine the best “degree of stability” that can be achieved. We formally define these problems:
     </paragraph>
     <paragraph label="Definition 24">
      {a mathematical formula}ϵ-CORE-FIND-IMPUTATION (ECF)Given ϵ, find an imputation {a mathematical formula}p=(p1,…,pn) in the ϵ-core of a CSG game Γ if one exists, and reply that no such imputation exists otherwise.
     </paragraph>
     <paragraph label="Definition 25">
      LEAST-CORE-VALUE (LCV)Compute the least-core value in CSG Γ, which is the minimal value {a mathematical formula}ϵmin such that the {a mathematical formula}ϵmin-core is non-empty.{sup:9}
     </paragraph>
     <paragraph>
      We provide results regarding restricted domains where the ECM, ECF and LCV are tractable, so one can test for ϵ-core membership, find ϵ-core imputations and compute the least-core value. We show that for tree-like STSGs with a bounded number of skills per agent, ECM, ECF and LCV are all solvable in polynomial time. Further, these problems are also solvable in polynomial time in TCSGs and WTSGs (as well as their threshold versions TCSG-T and WTSG-T) under the additional restriction that the number of tasks is bounded. Unfortunately, we could not provide a polynomial algorithm for solving ECF and LCV in general CSGs, nor provide a hardness result. Thus, this remains an interesting open problem. Since ECM is hard in these domains, we conjecture that these problems are hard in general STSGs, TCSGs and WTSGs.
     </paragraph>
     <paragraph>
      We now present the analysis of each problem in the various CSG domains. Since we focus on a given game Γ, from here on we drop the subscript Γ from our notation.
     </paragraph>
     <section label="4.1">
      <section-title>
       Coalition-value
      </section-title>
      <paragraph label="Theorem 3">
       COALITION-VALUE is in P, for all the following types of CSGs: STSG, TCSG, WTSG, TCSG-T, and WTSG-T.
      </paragraph>
      <paragraph label="Proof">
       Given a coalition C, it is simple to compute {a mathematical formula}S(C) in polynomial time, as the union of all the skills of the agents in C. Thus, we can compute the set of tasks {a mathematical formula}T(C) accomplished by that C: for each {a mathematical formula}tj∈T we check if {a mathematical formula}S(tj)⊂S(C). Given {a mathematical formula}T(C) in all these game forms, we can easily calculate {a mathematical formula}v(C) (as {a mathematical formula}|T(C)| or {a mathematical formula}w(T(C)), or by checking if these are above the threshold).  □
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Veto agents
      </section-title>
      <paragraph label="Theorem 4">
       VETO is in P for all the following types of CSGs: STSG, TCSG, WTSG, TCSG-T, and WTSG-T.
      </paragraph>
      <paragraph label="Proof">
       A veto agent {a mathematical formula}ai in Γ is present in all winning coalitions (with {a mathematical formula}v(C)=1 for simple games and {a mathematical formula}v(C)&gt;0 for general CSGs.) Consider {a mathematical formula}C=I∖{ai}. If {a mathematical formula}v(C)=0 then {a mathematical formula}ai is veto since {a mathematical formula}v(C′)=0 for all {a mathematical formula}C′⊂C by Lemma 1. If {a mathematical formula}v(C)&gt;0 then {a mathematical formula}ai is not veto. As seen in Theorem 3, we can compute {a mathematical formula}v(C) in polynomial time.  □
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Dummy agents
      </section-title>
      <paragraph>
       We now consider testing whether an agent is a dummy. Due to Theorem 3, given a coalition C, we can compute {a mathematical formula}v(C∪{ai}) and {a mathematical formula}v(C) in polynomial time, and see if {a mathematical formula}v(C∪{ai})&gt;v(C). Thus, given a specific coalition, we can check if a target agent contributes to that coalition. If this is the case for some coalition C, then our target agent is a non-dummy. Thus, DUMMY is in co-NP for all CSG classes we have defined.
      </paragraph>
      <paragraph>
       We say that a coalition C covers a set of skills S if for any skill {a mathematical formula}s∈S there exists at least on agent in C who possesses the skill s. We denote the set of agents that do not cover the skill s by {a mathematical formula}I−s={aj∈I|s∉S(aj)}. {a mathematical formula}I−s can be calculated in polynomial time by going over each agentʼs skill list, and removing those whose skill list contains s. The algorithms for testing if an agent is a dummy depend on the following lemma.
      </paragraph>
      <paragraph label="Lemma 3">
       If{a mathematical formula}aiis a non-dummy in an STSG then there is some skill{a mathematical formula}s∈Sisuch that{a mathematical formula}I−scovers{a mathematical formula}S∖Si.
      </paragraph>
      <paragraph label="Theorem 5">
       Suppose {a mathematical formula}ai is not a dummy. Then it contributes to some coalition, so there exists a coalition C such that {a mathematical formula}C∪{ai} is winning but C is losing. This only happens if C covers {a mathematical formula}S∖Si and fails to cover some skill {a mathematical formula}s∈Si. If C covers {a mathematical formula}S∖Si, then any superset of it also covers {a mathematical formula}S∖Si. {a mathematical formula}I−s is a superset of C, since C lacks the skill s (which means every agent {a mathematical formula}aj∈C lacks s). Thus, {a mathematical formula}I−s covers {a mathematical formula}S∖Si.  □DUMMY is in P for STSGs.
      </paragraph>
      <paragraph label="Proof">
       We can iterate through all skills {a mathematical formula}s∈Si, and given each skill {a mathematical formula}s∈Si calculate {a mathematical formula}I−s and check if it covers {a mathematical formula}S∖Si. If there is such an s, then {a mathematical formula}ai is not a dummy (it contributes to {a mathematical formula}I−s). If there is no skill {a mathematical formula}s∈Si for which {a mathematical formula}I−s covers {a mathematical formula}S∖Si, then through Lemma 3, {a mathematical formula}ai is a dummy player.  □
      </paragraph>
      <paragraph label="Theorem 6">
       DUMMY is in P for TCSGs and WTSGs.
      </paragraph>
      <paragraph label="Proof">
       Let Γ be a WTSG, with tasks {a mathematical formula}t1,…,tm. Let {a mathematical formula}Γj be the STSG with the single task {a mathematical formula}tj, with the same agents and skills as Γ. Suppose {a mathematical formula}ai is not a dummy in Γ, so for some {a mathematical formula}C⊆I∖{ai} we have {a mathematical formula}v(C∪{ai})&gt;v(C). Then for at least one task {a mathematical formula}tj, C cannot achieve {a mathematical formula}tj without {a mathematical formula}ai, and {a mathematical formula}ai is not a dummy in {a mathematical formula}Γj. Going the other way, if {a mathematical formula}ai is not a dummy in some {a mathematical formula}Γj, there is some coalition {a mathematical formula}C′ which cannot achieve {a mathematical formula}tj without {a mathematical formula}ai, so that in Γ we also have {a mathematical formula}v(C′∪{ai})&gt;v(C), and {a mathematical formula}ai is not a dummy in Γ. Thus, in order to test if an agent is not a dummy in a WTSG Γ, it is enough to test this for {a mathematical formula}Γ1,…,Γm. If the agent is not a dummy in any of them, he is not a dummy in Γ, and if he is a dummy in all of them, he is a dummy in Γ as well. Since TCSG is a restricted class of WTSG, the same algorithm works for TCSGs as well.  □
      </paragraph>
      <paragraph>
       While DUMMY is polynomial in TCSG and WTSG, it is co-NP-complete in TCSG-T and WTSG-T. This is easy to show for WTSG-T. Matsui and Matsui have shown that testing if an agent is a dummy is hard in weighted voting games [50]. When for each agent {a mathematical formula}ai there is a single task {a mathematical formula}ti which requires a skill {a mathematical formula}si that only {a mathematical formula}ai owns, the WTSG-T becomes a weighted voting game—so we get a natural reduction from weighted voting games. Proving the same for TCSG-T requires a different reduction. We show this by reducing from 3SAT, a well-known NP-hard problem.
      </paragraph>
      <paragraph label="Definition 26">
       3SATWe are given a propositional formula in conjunctive normal form (CNF) over n propositional variables {a mathematical formula}y1,…,yn, denoted {a mathematical formula}ψ=c1∧c2∧⋯∧cm, where {a mathematical formula}ci is a disjunction of three literals {a mathematical formula}ci=li,1∨li,2∨li,3 (each literal is the propositional variable {a mathematical formula}yj or its negation {a mathematical formula}¬yj). We are asked if there is an assignment that satisfies ψ.
      </paragraph>
      <paragraph>
       We show that DUMMY in TCSG-T is co-NP-complete by showing that a restricted case of testing whether an agent is a non-dummy is NP-hard. Consider the restricted case of a TCSG-T Γ with a threshold {a mathematical formula}k+1, that has a certain task t which only requires one skill s (so {a mathematical formula}S(t)={s}), and where an agent {a mathematical formula}ai is the only agent with the skill s, and where no task other than t requires the skill s. Adding {a mathematical formula}ai to any coalition C makes that coalition able to complete exactly one more task, t. A coalition in Γ wins if it covers at least {a mathematical formula}k+1 tasks. Thus, {a mathematical formula}ai is a non-dummy in Γ if and only if there is a coalition of agents (without {a mathematical formula}ai) that covers exactly k tasks (denoted COMPLETE-K-TASKS).
      </paragraph>
      <paragraph label="Theorem 7">
       DUMMY is co-NP-complete for TCSG-T and WTSG-T.
      </paragraph>
      <paragraph label="Proof">
       We have noted that DUMMY, both in TCSG-T and in WTSG-T, is in co-NP; it remains to show that it is co-NP hard. TCSG-T is a restricted form of WTSG-T, so it is enough to show this for TCSG-T. We do this by showing a reduction from 3SAT to COMPLETE-K-TASKS, and set the threshold to be {a mathematical formula}k=m tasks.Given the 3SAT formula {a mathematical formula}ψ=c1∧c2∧⋯∧cm over n propositional variables {a mathematical formula}y1,…,yn (where {a mathematical formula}ci=li,1∨li,2∨li,3), we construct a TCSG-T game with threshold m. For every propositional variable in ψ, the game has two skills, {a mathematical formula}syi and {a mathematical formula}s¬yi. For every clause {a mathematical formula}cj in ψ the game has a skill {a mathematical formula}scj and three agents, {a mathematical formula}acj,1,acj,2,acj,3. The skills of {a mathematical formula}acj,x depend on the literal x of {a mathematical formula}cj, and {a mathematical formula}S(acj,x)={scj,slj,x}. For example, if we have {a mathematical formula}c1=y1∨¬y2∨¬y3, we create 3 agents: agent {a mathematical formula}ac1,1 with skills {a mathematical formula}S(ac1,1)={sc1,sy1}, agent {a mathematical formula}ac1,2 with skills {a mathematical formula}S(ac1,2)={sc1,s¬y2} and agent {a mathematical formula}ac1,3 with skills {a mathematical formula}S(ac1,3)={sc1,s¬y3}. For each clause {a mathematical formula}ci we also create a task {a mathematical formula}tci, which requires the skill {a mathematical formula}sci, so {a mathematical formula}S(tci)={sci}. For each propositional variable {a mathematical formula}yi we create {a mathematical formula}m+1 tasks {a mathematical formula}t(yi,¬yi,1),…,t(yi,¬yi,m+1), each of which requires the skills {a mathematical formula}S(t(yi,¬yi,j))={syi,s¬yi}. The purpose of these tasks is to eliminate covers where both {a mathematical formula}yi and {a mathematical formula}¬yi are chosen.Suppose there is a satisfying truth assignment A for ψ, in which the variables assigned true are {a mathematical formula}yt1,…,ytx and the variables assigned false are {a mathematical formula}yf1,…,yfy. We construct a winning coalition that covers exactly m tasks from the truth assignment A as follows: each clause {a mathematical formula}cj is satisfied through at least one of the literals, say literal x in {a mathematical formula}cj, denoted {a mathematical formula}lj,x. We add the agent {a mathematical formula}acj,x to C. Coalition C covers all the clauses {a mathematical formula}cj of ψ, since A is a satisfying truth assignment. On the other hand, C does not cover any of the tasks {a mathematical formula}t(yi,¬yi,j) (again, A is a valid truth assignment). Thus, if there is a satisfying truth assignment, there is a coalition of agents in the created TCSG-T game that completes exactly m tasks.On the other hand, suppose there is a coalition C which covers exactly m tasks in the created TCSG-T game. The covered tasks cannot include any of the {a mathematical formula}t(yi,¬yi,j) tasks, since each of these have m more identical copies, and covering one of these means covering all {a mathematical formula}m+1 of them. Thus the covered m tasks are the {a mathematical formula}tcj tasks. This means C holds agents that cover the skills {a mathematical formula}scj for all m clauses {a mathematical formula}cj, and for no {a mathematical formula}yi does it cover both {a mathematical formula}syi and {a mathematical formula}s¬yi. We build the following truth assignment A: for each {a mathematical formula}syi covered by C, set {a mathematical formula}yi to true, and set all the other variables to false. This truth assignment satisfies every clause, since for each {a mathematical formula}cj we have some literal in {a mathematical formula}cj matching the value in the truth assignment (or C would not cover {a mathematical formula}scj).  □
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       The core
      </section-title>
      <paragraph>
       We now consider the complexity of calculating the core of CSGs, or checking if it is empty. We denote the set of all agents except {a mathematical formula}ai as {a mathematical formula}I−ai=I∖{ai}.
      </paragraph>
      <paragraph>
       Consider a simple game with no veto players. For every agent {a mathematical formula}ai there is a winning coalition that does not contain {a mathematical formula}ai. Consider an imputation {a mathematical formula}p=(p1,…,pn) where {a mathematical formula}pi&gt;0. Since {a mathematical formula}∑i=0npi=1 and since {a mathematical formula}pi&gt;0 we get that {a mathematical formula}p(C)⩽∑aj∈I−aipj&lt;1, so {a mathematical formula}p(C)&lt;v(C)=1 and C is a blocking coalition. On the other hand, any imputation p that gives nothing to non-veto players is in the core, since any coalition C that can block must have {a mathematical formula}v(C)=1, so it must contain all the veto players; thus, it also has {a mathematical formula}∑aj∈Cpj=1, and therefore is not blocking. As a consequence, calculating the core of simple games simply requires returning a list of veto players in that game, and checking if the core is non-empty simply requires testing if the game has any veto players.{sup:10}
      </paragraph>
      <paragraph label="Theorem 8">
       CORE and CORE-NON-EMPTY are in P for STSG, TCSG-T and WTSG-T.
      </paragraph>
      <paragraph label="Proof">
       Due to Theorem 4, for these games we can find all the veto agents in polynomial time. One representation of the core in any simple game is a list of veto agents, as in such games any imputation that allocates all the payoff among the veto agents, in any way, is in the core and any other imputation is blocked (if there are not veto agents in such games the core is empty). Since we can generate the list of veto agents in polynomial time, we can compute the core in polynomial time.  □
      </paragraph>
      <paragraph label="Theorem 9">
       CORE-NON-EMPTY is in co-NP for STSG, TCSG, TCSG-T and WTSG, and WTSG-T.{sup:11}
      </paragraph>
      <paragraph label="Proof">
       Malizia et al. [48] show that CORE-NON-EMPTY is in co-NP for any coalitional game where the coalitional function can be computed in polynomial time. The result follows by Theorem 3.{sup:12}  □
      </paragraph>
     </section>
     <section label="4.5">
      The ϵ-core and least-core
      <paragraph>
       We now consider ϵ-core and least-core related problems. Determining whether a certain imputation {a mathematical formula}p=(p1,…,pn) is in the ϵ-core is equivalent to testing whether the maximal excess of any coalition is at most ϵ. We can thus focus on the complexity of finding the maximal excess of any coalition given an imputation.{sup:13} For this, it is sufficient to study ECM.
      </paragraph>
      <paragraph>
       Even in the simple domain of STSG, the ECM problem is co-NP Complete and equivalent to the weighted set-cover problem.
      </paragraph>
      <paragraph label="Definition 27">
       Weighted Set-Cover (WSC)We are given a set E of elements and a collection of subsets {a mathematical formula}S={S1,…,Sn} where {a mathematical formula}Si⊆E and {a mathematical formula}⋃Si=E, and positive weights {a mathematical formula}c1,…,cn, and are asked to find a subset {a mathematical formula}S′⊆S that covers E (i.e., such that {a mathematical formula}⋃Si∈S′Si=E) of minimal weight (i.e., minimizing {a mathematical formula}∑i∈S′ci).
      </paragraph>
      <paragraph>
       The restricted version of WSC where all the weights are identical is the SET-COVER problem. SET-COVER is a prominent NP-complete problem [39].
      </paragraph>
      <paragraph label="Theorem 10">
       ECM is co-NP-Complete in any of the CSG forms: STSGs, TCSG, WTSG, TCSG-T, and WTSG-T.{sup:14}
      </paragraph>
      <paragraph label="Proof">
       A coalition C with an excess greater than ϵ (so {a mathematical formula}e(C)=v(C)−p(C)⩾ϵ) violates the ϵ-core constraints. Thus, the decision version of ECM requires making sure that under a given imputation there does not exist a coalition with an excess of at least ϵ for some {a mathematical formula}ϵ⩾0. Equivalently, ECM requires making sure that the maximal excess across all coalitions is at most ϵ. Due to Theorem 3, given a coalition C we can compute the value {a mathematical formula}v(C) and its payoff {a mathematical formula}p(C) in polynomial time, and thus can also compute its excess {a mathematical formula}e(C)=v(C)−p(C). Thus, ECM is in coNP for all of the above CSG classes.We now show that computing the maximal excess {a mathematical formula}emax=max{e(C)|C⊆I} even in the restricted class of STSG is equivalent to a weighted set-cover problem. Any losing coalition C has a non-positive excess (i.e., {a mathematical formula}p(C)⩾v(C)) under any imputation. Thus, the maximal excess occurs for some winning coalition, and we have {a mathematical formula}emax=max{e(C)|v(C)=1}. Any winning coalition C has {a mathematical formula}v(C)=1, so the maximal excess occurs for a winning coalition C that minimizes {a mathematical formula}p(C). By definition {a mathematical formula}p(C)=∑i∈Cpi, so finding the maximal excess coalition requires finding a subset of agents C whose skill set {a mathematical formula}S(C)=⋃i∈C′Si covers all skills S (i.e., {a mathematical formula}⋃i∈C′Si=S) and whose sum of payoffs {a mathematical formula}p(C)=∑i∈Cpi is minimal. This is simply a weighted set-cover instance with subsets {a mathematical formula}S={S1,…,Sn} and weights {a mathematical formula}p={p1,…,pn}.  □
      </paragraph>
      <paragraph>
       The above result holds even if the imputation is always the equal imputation where {a mathematical formula}pi=pj for any two agents {a mathematical formula}i,j, in which case ECM is equivalent to SET-COVER (rather than WSC). The result holds even for the equal imputation when each skill is shared by exactly two agents (i.e., for any skill s we have exactly two agents who own that skill), in which case the ECM problem translates to the prominent NP-complete VERTEX-COVER problem [39].{sup:15}
      </paragraph>
      <paragraph>
       Unfortunately, WSC is also hard to approximate, and unless NP has slightly super-polynomial algorithms (which is highly unlikely), the best polynomial-time approximation algorithm for it achieves an approximation factor of {a mathematical formula}Θ(lnn)[37]. A simple algorithm for computing the maximal excess (or for solving ECM) through approximating WSC requires an FPTAS for SET-COVER.
      </paragraph>
      <paragraph>
       To provide tractable algorithms for the ECM problem, we focus on restricting the inputs. The problem of WSC has been studied for a class of problems in which the inputs are tree-like and have a constant bounded maximal subset size [42].{sup:16}
      </paragraph>
      <paragraph>
       Consider for example the case of sensor networks, where each agent is present in a certain geographical location, and a “skill” represents an agentʼs ability to cover a certain geographical point of interest with its sensors. In this case, a point of interest may only be covered by agents who reside in its vicinity, so a “skill” is owned by agents who reside in a continuous geographical space. Further, in many domains the sensor network may be quite sparse, so each agent would only cover at most a few points of interest. When the coverage is sparse, it is also unlikely that there would be a cycle of agents where every two agents in the cycle share a certain point of interest that both cover. The skill structure in such domains is tree-like in the sense described below, so certain core-related problems that are generally hard can be tractably handled.
      </paragraph>
      <paragraph>
       We use the approach of Guo and Niedermeier [42], who showed that when each of the subsets has a size at most b (where b is constant), so {a mathematical formula}b=maxSi∈S|Si|, and when the subset collection is tree-like, then WSC can be solved in polynomial time.{sup:17} We first give the definition of a “tree-like” subset collection (Guo and Niedermeierʼs work provides a few examples for tree-like subset collections [42]):
      </paragraph>
      <paragraph label="Definition 28">
       Tree-like subset collectionA collection {a mathematical formula}S={S1,…,Sn} of subsets over the elements X (such that {a mathematical formula}Si⊆X) is tree-like if it is possible to arrange the subsets of S in an acyclic undirected graph (unrooted tree) T such that there is a one-to-one correspondence between the vertices of the tree and the subsets, and such that for every element {a mathematical formula}x∈X all the nodes in T corresponding to the subsets that contain x induce a subtree of T.
      </paragraph>
      <paragraph>
       The subset collection is tree-like if it is possible to create edges between the subsets so that for any element {a mathematical formula}x∈X, the induced subgraph on the subsets that contain x is a tree. Many skill domains such as the sensor network domain described above may exhibit these properties, so algorithms tailored for such domains can be used to solve core-related problems in these domains.{sup:18}
      </paragraph>
      <paragraph>
       Since ECM is equivalent to WSC, and since Guo and Niedermeier [42] provide a polynomial algorithm for WSC where the subset collection is tree-like and each subset contains at most b elements (for a constant b), we obtain the following corollary:
      </paragraph>
      <paragraph label="Corollary 1">
       Given an STSG where each agent has at most b skills and the collection of the agentsʼ skill subsets is tree-like, it is possible to solve ECM in polynomial time.
      </paragraph>
      <paragraph label="Definition 29">
       For solving ECM in the other CSG classes, we need another restriction: the number of tasks must also be bounded by a constant q. Bounded tree-like CSG domainWe say a CSG domain is a bounded tree-like CSG domain if each of the agentsʼ skill subsets has at most b skills (where b is a constant), where there are at most q tasks (where q is a constant), and where the agentsʼ skill subsets are tree-like.
      </paragraph>
      <paragraph>
       There is no limitation on the total number of skills or the total number of agents. We now provide the equivalent result to Corollary 1 for the other CSG classes.
      </paragraph>
      <paragraph label="Theorem 11">
       In bounded tree-like CSG domains of the classes TCSG, WTSG, TCSG-T, and WTSG-T, it is possible to solve ECM in polynomial time.
      </paragraph>
      <paragraph label="Proof">
       We say a task subset {a mathematical formula}T′⊆T is achievable by the coalition C if C covers the set of skills {a mathematical formula}S(T′)=⋃tj∈T′S(tj). If {a mathematical formula}T′ is achievable by coalition C, then we have {a mathematical formula}T′⊆T(C) where {a mathematical formula}T(C) is the set of all tasks the coalition C can achieve. We have assumed free disposal of tasks, so {a mathematical formula}u(T(C))⩾u(T′) and the value of a coalition C is {a mathematical formula}v(C)=u(T(C))⩾u(T′). Thus, if for any coalition that can achieve {a mathematical formula}T′ we have {a mathematical formula}p(C)⩽u(T′)−ϵ then C has a deficit {a mathematical formula}e(C)=v(C)−p(C)⩾ϵ and the imputation p is not in the ϵ-core. On the other hand, {a mathematical formula}T(C)⊆T, so if for any {a mathematical formula}T′⊆T we have {a mathematical formula}p(C)&gt;u(T′)−ϵ, then all coalitions have a deficit of at most ϵ, and the imputation p is in the ϵ-core. Thus, to check if the maximal deficit under an imputation is at most ϵ (or in other words, to solve ECM), it suffices to examine every task subset {a mathematical formula}T′⊆T and test whether any coalition C that achieves {a mathematical formula}T′ has a payoff {a mathematical formula}p(C)&gt;u(T′)−ϵ.We now note that in bounded CSG domains, there is a constant number of tasks, so there is a constant number of task subsets. Thus we must only examine a constant number of task subsets {a mathematical formula}T′ and test whether any coalition C that achieves {a mathematical formula}T′ has a payoff {a mathematical formula}p(C)&gt;u(T′)−ϵ. Such a test for a specific task subset {a mathematical formula}T′ requires polynomial time. In all the above CSG domains, it is possible to compute {a mathematical formula}u(T′) in polynomial time. Also, to achieve {a mathematical formula}T′, a coalition must cover {a mathematical formula}S(T′). Since the domain is bounded and tree-like, the method of Guo and Niedermeier [42] allows testing the minimal payoff {a mathematical formula}p(C) of any coalition that covers {a mathematical formula}S(T′): similarly to the proof of Theorem 10, this is simply a Weighted Set-Cover problem and can be solved in polynomial time in tree-like domains where the agentsʼ skill subsets have at most b skills.  □
      </paragraph>
      <paragraph>
       The above Corollary 1 and Theorem 11 indicate that in certain restricted domains, verifying ϵ-core imputations (or computing the maximal excess under a given imputation) can be performed in polynomial time. We now show that in these restricted domains, the problems of finding ϵ-core imputations and computing the least-core are also in P.
      </paragraph>
      <paragraph>
       We first show that ECF can be solved in polynomial time in these restricted domains, using a separation oracle.
      </paragraph>
      <paragraph label="Theorem 12">
       In bounded tree-like CSG domains of the classes STSG, TCSG, WTSG, TCSG-T, and WTSG-T, ECF is solvable in polynomial time.
      </paragraph>
      <paragraph label="Proof">
       We first consider an exponential-size feasibility linear program for computing an imputation in the ϵ-core. The program simply considers all the possible {a mathematical formula}2n coalitions over the n players, {a mathematical formula}C1,…,C2n. The ϵ-core can be written directly as a linear program over the variables {a mathematical formula}p1,…,pn (representing the agentsʼ payoffs in the imputation), with a constraint for each such coalition.{a mathematical formula}The above program is a feasibility linear program, and any solution for it, {a mathematical formula}p=(p1,…,pn), is an imputation in the ϵ-core. However, its size is exponential in the number of agents, so even writing this program requires exponential time. Nonetheless, we can use a separation oracle to either find an ϵ-core imputation or show that the ϵ-core is empty.{sup:19} Our proofs of Corollary 1 and Theorem 11 used the relation between ECM and Weighted Set-Cover, and taking a candidate imputation {a mathematical formula}p=(p1,…,pn) as input, find a coalition C with payoff {a mathematical formula}p(C) that achieves a task subset {a mathematical formula}T′ such that {a mathematical formula}p(C)⩽u(T′)−ϵ, if such a subset exists. Such coalitions are exactly the ones for which the constraint is violated in the above linear program, and provide a separation oracle. Given this separation oracle, the above linear program can be solved in polynomial time and without the need to specify it explicitly.  □
      </paragraph>
      <paragraph>
       Theorem 12 shows that under the above restrictions regarding the CSG domain, given a certain ϵ it is possible to find an imputation in the ϵ-core in polynomial time if one exists, or determine that the ϵ-core is empty. We now consider the problem of finding the least-core.
      </paragraph>
      <paragraph label="Corollary 2">
       In bounded tree-like CSG domains of the classes STSG, TCSG, WTSG, TCSG-T, and WTSG-T, LCV is solvable in polynomial time, and it is also possible to find an imputation in the least-core in polynomial time.{sup:20}
      </paragraph>
      <paragraph label="Proof">
       First note that the maximal value any coalition can achieve is {a mathematical formula}v(I), so the {a mathematical formula}v(I)-core is always non-empty. We can perform a binary search on the minimal value of ϵ such that the ϵ-core is non-empty, applying the algorithm of Theorem 12 on each tested value.  □
      </paragraph>
      <paragraph>
       Thus, although Theorem 10 shows that in general (non-tree-like) CSGs, even testing for an ϵ-core imputation is hard, the key questions regarding the least-core and ϵ-core are tractably solvable for more restricted domains.
      </paragraph>
     </section>
     <section label="4.6">
      <section-title>
       The Shapley value and Banzhaf power index
      </section-title>
      <paragraph>
       We now consider calculating the Shapley value and Banzhaf power index in CSGs. Dummy players have a Shapley value and Banzhaf index of 0. Thus, computing either index allows testing for whether an agent is a dummy player. The problems SHAPLEY and BANZHAF have decision problem versions: testing whether the Shapley value or Banzhaf power index of an agent exceeds a certain threshold k. We show that these decision problems are NP-hard as a corollary of our result regarding the DUMMY problem.
      </paragraph>
      <paragraph label="Corollary 3">
       The decision versions of SHAPLEY and BANZHAF are NP-hard in TCSG-T and WTSG-T.
      </paragraph>
      <paragraph label="Proof">
       DUMMY is NP-hard in these domains, due to Theorem 7. Given the Shapley value or Banzhaf index, we can answer DUMMY by comparing the index to 0. Thus, computing these indices in these domains (or the decision problem of testing whether they are greater than some value) is NP-hard.  □
      </paragraph>
      <paragraph>
       The decision versions of SHAPLEY and BANZHAF are NP-hard, but may not even be in NP, so these problems may not be NP-complete. We show a stronger result of #P-completeness for the Banzhaf value, for all domains. We first define two #P-complete problems:
      </paragraph>
      <paragraph label="Definition 30">
       #SET-COVER (#SC)We are given a set S and a collection {a mathematical formula}C={S1,…,Sn} that for all {a mathematical formula}Si we have {a mathematical formula}Si⊂S. A set-cover is a subset {a mathematical formula}C′⊂C such that {a mathematical formula}⋃Si∈C′Si⊇S. Given S and C, we are asked to compute the number of different set-covers of S.
      </paragraph>
      <paragraph label="Definition 31">
       #VERTEX-COVER (#VC)We are given an undirected graph {a mathematical formula}G=〈V,E〉, and are asked to count the number of vertex-covers in the graph. A vertex-cover is a subset {a mathematical formula}V′⊆V such that for every edge {a mathematical formula}e=(u,v)∈E, either {a mathematical formula}u∈V′ or {a mathematical formula}v∈V′.
      </paragraph>
      <paragraph>
       We note that #VC is a special case of #SC, where the collection S to be covered is the set of all the edges and the collection of subsets includes a subset for every vertex, which contains all the edges in which this vertex occurs (i.e., the subset representing the vertex v contains all the edges that have v as one of their endpoints). The problem #SC is known to be #P-complete, even for some very restricted classes of graphs such as planar bipartite graphs of degree at most four [66]. Since checking if a collection of subsets of a target set S indeed covers all the elements of S, the problem #SC is also #P-complete.
      </paragraph>
      <paragraph>
       We now show that BANZHAF is #P-complete in all the restricted versions of CSGs defined in this paper, using a reduction from #SC.
      </paragraph>
      <paragraph label="Theorem 13">
       BANZHAF in STSG, TCSG, WTSG, TCSG-T and WTSG-T is #P-complete.{sup:21}
      </paragraph>
      <paragraph label="Proof">
       STSG is a restricted case of all the other types of games, so it is enough to show #P-completeness of BANZHAF in STSGs. The Banzhaf power in STSGs is the proportion of coalitions where {a mathematical formula}ai is critical out of all coalitions containing {a mathematical formula}ai. Since the number of coalitions containing {a mathematical formula}ai is known to be {a mathematical formula}2n−1, we only need to calculate the number of coalitions where {a mathematical formula}ai is critical. First, we note this problem is in #P, since due to Theorem 3 we have a simple polynomial procedure that can test if {a mathematical formula}ai is critical in some coalition containing {a mathematical formula}ai.We show that BANZHAF is #P-complete in STSGs by a reduction from #SC. Let the #SC instance contain subsets {a mathematical formula}S={S1,…,Sn}. We build the following STSG, with {a mathematical formula}n+1 agents. Agent {a mathematical formula}ai has the skill set {a mathematical formula}Si, and {a mathematical formula}an+1 has a single new skill, so {a mathematical formula}Sn+1={snew}, such that {a mathematical formula}snew∉S. The BANZHAF query is regarding the Banzhaf index of {a mathematical formula}an+1. Every winning coalition must cover {a mathematical formula}snew, which can only be done using {a mathematical formula}an+1. Consider a coalition C that does not contain {a mathematical formula}an+1 and covers S. While C is losing, {a mathematical formula}C∪{an+1} is winning, and {a mathematical formula}an+1 is critical in {a mathematical formula}C∪{an+1}. Consider a coalition C that does not contain {a mathematical formula}an+1 and does not cover S. C is losing, and {a mathematical formula}C∪{an+1} is also losing, so {a mathematical formula}an+1 is not critical in {a mathematical formula}C∪{an+1}. Denote by x the number of coalitions that do not contain {a mathematical formula}an+1, and do cover S. Since each such coalition covers S, it is a set-cover in the original problem. Since {a mathematical formula}an+1 is not critical to any coalition that does not contain {a mathematical formula}an+1, the number of coalitions where {a mathematical formula}an+1 is critical is exactly x. Thus, if the BANZHAF answer is {a mathematical formula}x2n, then the #SC answer is x. Thus a polynomial algorithm for BANZHAF also solves #SC, so BANZHAF is #P-complete.  □
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Similar cooperative game representation languages
     </section-title>
     <paragraph>
      Related research deals with similar models of cooperation among agents, and alternative cooperative game representation languages. We now examine similarities and differences between these languages and the CSG representation, both in terms of expressivity and computational aspects. We provide a general discussion regarding many representation languages, and provide a deeper discussion regarding the representations we believe are closest to the CSG representation: linear production games [52], the anonymous proof solution representation [68] and Coalitional Resource Games [67].
     </paragraph>
     <section label="5.1">
      <section-title>
       Expressiveness and succinctness of representation languages
      </section-title>
      <paragraph>
       Section 1.3 discussed several representation languages proposed for cooperative games. In Section 3 we showed that even STSGs, the most restrictive CSG class, can represent any simple increasing game. Further, we showed that WTSGs can represent any increasing game. This completeness in terms of expressivity is a significant advantage that CSGs have over other representation languages that are limited in expressiveness. The most prominent restricted representation is the class of weighted voting games [14], [50], [33], [35], where each agent has a weight, and a coalition of agents wins the game if the sum of the weights of its participants exceeds a certain threshold.
      </paragraph>
      <paragraph>
       While some characteristic functions cannot be represented as a weighted voting game (see Elkind et al. [34] for a discussion of the expressiveness of weighted voting games), certain problems such as computing the core or finding veto agents can be solved in polynomial time in these games. Interestingly, even in this simple representation, certain problems are already computationally hard, such as testing whether an agent is a dummy, computing power indices or computing the least-core and the nucleolus.
      </paragraph>
      <paragraph>
       Other examples of restricted cooperative game representations are cooperative graph games [30] and various forms of network games [12], [3], [13]. Many such incomplete representations admit polynomial algorithms for problems that are computationally hard in CSGs, such as computing power indices or core-related problems. Thus, if a game is given in one of these restricted representations, it is better to use algorithms tailored for these representations. On the other hand, these languages are not fully-expressive, and so for each of them there are some characteristic functions that cannot be represented using the language.
      </paragraph>
      <paragraph>
       Recently, Aziz et al. [2] have examined the impact of certain restrictions on CSGs that allow them to be solved more efficiently. Specifically, they show that in STSGs where the total number of skills is bounded by a constant, it is possible to compute the least-core in polynomial time (as well as the Cost-of-Stability and the nucleolus [10], [58]). However, this restriction regarding the bounded number of skills is severe. Our algorithm for computing the least-core in Section 4.5 only requires that the number of skills any single agent may have is bounded, but allows an arbitrary number of skills in total. On the other hand, our algorithm has the additional requirement of a tree-like structure.
      </paragraph>
      <paragraph>
       Previous work on computational game theory has uncovered various fully-expressive representation languages, which can describe any characteristic function. Examples include the marginal contribution network language (MC-Nets) [44], the sparse synergy representation [23], and the Multi-Attribute Coalitional Games (MACGs) [45], which generalize both of these.{sup:22} Any fully-expressive representation can represent any characteristic function, but different representations may require a different amount of space to represent the same game. Work on representing functions in a concise form has provided an insightful definition regarding the succinctness of representations [18], [47], [25], [20]: a language L is at least as expressive as a language {a mathematical formula}L′ if there is a polynomial translator that converts any input of {a mathematical formula}L′ into an equivalent input in L (where ‘equivalence’ means that the value functions coincide).{sup:23} The running time of algorithms that analyze cooperative games depends on the input size, so a polynomial algorithm that takes the input in one language may not be useful if the input is given in another language—the input would need to be converted to the required language, which may take an exponential amount of time and may result in an exponentially long representation. CSGs are closely related to the set-cover problem, and can compactly represent domains where agents must have a certain resource or cover certain skills in order to achieve a task. In contrast, marginal contribution networks and the sparse synergy representation are quite different from a set-cover domain, and so there appears to be no straightforward conversion from these forms into a compact CSG representation. Similarly, we do not see a way to convert a compact CSG representation into a compact form of these other representations.
      </paragraph>
      <paragraph>
       MACGs [45] are a general framework for building representation languages for cooperative games, and is in fact a “meta-model.” The properties of a MACG representation depends on the choice of an aggregator which takes attributes associated with agents and outputs a numeric value. Specifically, the expressive power of an MACG representation and its computational properties depend on the aggregators used. Thus, the computational properties of the MACG model must be examined under a a specific choice of aggregators. It is possible to express CSGs using certain such aggregators, such as an aggregator that tests whether at least one of the agents in a set is endowed with a certain skill. In this sense, CSGs can be thought of as a restricted case of the MACG framework, so our analysis provides algorithmic results for this specific aggregator.
      </paragraph>
      <paragraph>
       We now consider the representations that we see as closest to the CSG representation language.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Linear production games
      </section-title>
      <paragraph>
       Linear production games [52] are games where agents pool together resources in order to manufacture finished goods that can be sold at a given market price. In such games, there are n different types of input resources, and each agent is endowed with a certain quantity of each resource. Similarly, there are k different finished goods that can be produced, each of which can be sold at a certain market price. Each such finished good requires a certain amount of the n different input resources. When several agents form a coalition, they have at their disposal the sum of the individual endowments of the input resources. The utility a coalition can produce is the maximal revenue the coalition can achieve for the finished goods it can produce (fractional quantities of goods are allowed).
      </paragraph>
      <paragraph>
       Linear production games have certain similarities with CSGs, and especially with WTSGs. Both have different “resources” with which agents are endowed—the input resources in linear production games and the agent skills in CSGs. Similarly, there are outputs that coalitions of agents strive to achieve—finished goods in linear production games, and completed tasks in CSGs. Finally, the market prices of finished goods in linear production games are somewhat parallel to the weights of tasks in WTSG.
      </paragraph>
      <paragraph>
       The key difference between linear production games and CSGs is that in CSGs the input resources have no quantities. As these resources in CSGs are skills, they can be used as many times as required. In contrast, quantities lie at the heart of linear production games, where the amounts of the finished goods a coalition can manufacture depends on the amounts of input resources a coalition has, and the amount required to produce each finished good.
      </paragraph>
      <paragraph>
       Interestingly, a key result regarding linear production games is that they always have a non-empty core [52]. In fact, a certain core imputation can be found in these games using linear programming duality. Since CSGs can express games with empty cores, there are some games that can be expressed as a CSG, but not as a linear production game. On the other hand, for some CSG forms, even testing whether the core is empty is computationally hard, whereas a core imputation always exists in a linear production game, and can be found in polynomial time.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Anonymous proof solutions
      </section-title>
      <paragraph>
       Yokoo et al. [68] consider open, anonymous coalitional environments, where a single agent can use multiple identifiers (or false names), pretending to be multiple agents, and distribute its ability among these identifiers. This requires a model of what abilities agents have, so they can be split among their false identities. The setting examined is similar to general CSGs: there are several skills S, and each agent {a mathematical formula}ai has some subset of skills {a mathematical formula}Si⊂S. The model assumes that no two agents possess the same skill, so for any {a mathematical formula}ai≠aj we have {a mathematical formula}Si∩Sj=ϕ. The characteristic function of the game is defined on the set of skills that a coalition has: {a mathematical formula}v:2S→R. Yokoo et al. [68] do not consider the computational complexity of calculating solution concepts, focusing instead on strategic agent behavior.
      </paragraph>
      <paragraph>
       Still, the expressiveness of their anonymous-environment model is essentially equivalent to that of general CSGs. In one direction, any game compactly represented by the anonymous-environment model can also be represented as a compact CSG, by defining a task for each skill (which requires exactly this skill). In this way, it is possible to map any subset of skills a coalition may have to any utility for that coalition. In the other direction, the anonymous-environment model can directly map a subset of skills that a coalition has to the utility of that coalition, and so can express instances described in the CSG model, which defines the utility through tasks. On the other hand, our task-based CSG representation is at least as compact as the anonymous-environment representation, and can sometimes save an exponential amount of space over that representation. The reason for this is that if a certain skill subset {a mathematical formula}S′⊂S enables the achievement of a task, the CSG model does not have to specify the utility for any skill subset X such that {a mathematical formula}S′⊂X, and this is assumed to be at least the utility of {a mathematical formula}S′ (so a new value must only be specified if {a mathematical formula}S″ allows achieving additional tasks).
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Coalitional resource games
      </section-title>
      <paragraph>
       Wooldridge and Dunne [67] present a model of Coalitional Resource Games. In such games, agents are interested in achieving goals. A set of different resources are required to reach these goals. Each agent is endowed with different amounts of each resource, and wants to achieve one of a different subset of goals. A goal subset satisfies a coalition if for every agent in that coalition it contains a goal desired by that agent. A goal set is feasible for a coalition if that coalition has sufficient resources to achieve all the goals in that set.
      </paragraph>
      <paragraph>
       One main concern is in regard to properties of goal subsets that are successful—both feasible and satisfying for a coalition. Wooldridge and Dunne [67] consider the complexity of several questions such as: whether a coalition has a successful goal set (NP-complete); whether a certain resource r is necessary for a coalition (co-NP complete); and whether a successful goal set {a mathematical formula}G′ for a coalition is optimal in its use of the resource r (co-NP complete). Many results for CRGs are negative, so that although small representations, answering many questions regarding them is computationally hard.
      </paragraph>
      <paragraph>
       Formally, Coalitional Resource Games (CRGs) have set {a mathematical formula}I={a1,…,an} of agents, a set {a mathematical formula}G={g1,…,gm} of possible goals, a set {a mathematical formula}R={r1,…,rt} of resources, an endowment function {a mathematical formula}en:I×R→N mapping an agent and a resource to the amount of that resource that the agent has, and a requirement function {a mathematical formula}req:G×R→N mapping a goal and a resource to the amount of that resource required to obtain that goal. The amount of resource {a mathematical formula}rj available to a coalition C of agents is {a mathematical formula}en(C,rj)=∑ai∈Cen(aj,rj). Similarly, the amount of {a mathematical formula}rj required for a set of goals {a mathematical formula}G′ is {a mathematical formula}req(G′,rj)=∑gkinG′req(gk,rj).
      </paragraph>
      <paragraph>
       A goal subset {a mathematical formula}G′⊂G satisfies a coalition {a mathematical formula}C⊂I if for every agent {a mathematical formula}ai∈C there is a goal {a mathematical formula}g∈G′ such that {a mathematical formula}g∈Gi, and the set of goal sets that satisfy a coalition C is denoted by {a mathematical formula}sat(C)={G′⊂G|∀ai∈C,Gi∩G′≠ϕ}. A set of goals {a mathematical formula}G′ is feasible for coalition {a mathematical formula}C⊂I if that coalition has sufficient resources to achieve all the goals in {a mathematical formula}G′. We denote the set of feasible goal sets for coalition C by {a mathematical formula}feas(C)={G′⊂G|∀rj∈R,req(G′,rj)⩽en(C,r)}.
      </paragraph>
      <paragraph>
       Our model of CSGs is somewhat similar to that of CRGs.{sup:24} CSGs define tasks to accomplish, and CRGs define goals desired by agents. Performing a task in CSGs requires a coalition to have a certain set of skills, and achieving a goal in CRGs requires certain resources. However, significant differences exist between the models.
      </paragraph>
      <paragraph>
       First, completing a goal in a CRG requires different amounts of various resources. In a CSG, tasks simply require the use of a skill, and the only requirement is for an agent in the coalition to have the skill (the skill is not consumed when performing the task). This can be modeled in CRGs by requiring just 1 unit of the resource for any goal, giving an agent {a mathematical formula}2|I| units of that resource, enough for any possible coalition. In this sense, CRGs are more expressive than CSGs. However, this expressiveness of CRGs comes at a price, since many questions regarding CRGs are computationally hard. For example, while computing the value of a coalition in a CSG can be done in polynomial time, testing whether there exists a feasible and satisfying goal set (a question that resembles computing the value of a coalition) is NP-hard in CRGs; many questions relating to agent properties are hard in CRGs while finding veto agents in CSGs admits a simple polynomial algorithm.
      </paragraph>
      <paragraph>
       Second, the CRG model does not define a coalitional game, but rather defines for each coalition C the successful goal sets for that coalition, {a mathematical formula}sf(C)⊂G, which are both feasible and satisfying. A solution in the CRG model is simply a goal set that is both feasible and satisfying for a coalition. However, if there are several such goal sets, it is unclear which of them is chosen. It is possible to define a simple coalitional game, with the characteristic function defined to be 1 for coalitions that have successful goal sets and 0 for coalitions that do not, such that,{a mathematical formula}
      </paragraph>
      <paragraph>
       However, such a definition has several drawbacks. Testing if a certain coalition has a successful goal set is NP-complete, so simply evaluating the value of the game is computationally hard, even for a single coalition. More importantly, if a goal satisfies a coalition, all the agents are satisfied as at least one of their goals is achieved. This makes the question of dividing the total utility among the agents meaningless. In comparison, the model of CSG assumes that accomplishing different tasks generates a certain utility, which has to be divided among all the agents. An example of this situation is a common project that requires completing various tasks, that all the agents have to accomplish, and that generate a certain revenue. The agents are not satisfied just by the project having succeeded, but rather gain utility according to the share of the revenue received.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>