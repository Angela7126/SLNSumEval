<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Better redistribution with inefficient allocation in multi-unit auctions.
   </title>
   <abstract>
    For the problem of allocating one or more items among a group of competing agents, the Vickrey–Clarke–Groves (VCG) mechanism is strategy-proof and efficient. However, the VCG mechanism is not strongly budget balanced: in general, value flows out of the system of agents in the form of VCG payments, which reduces the agents' utilities. In many settings, the objective is to maximize the sum of the agents' utilities (taking payments into account). For this purpose, several VCG redistribution mechanisms have been proposed that redistribute a large fraction of the VCG payments back to the agents, in a way that maintains strategy-proofness and the non-deficit property. Unfortunately, sometimes even the best VCG redistribution mechanism fails to redistribute a substantial fraction of the VCG payments. This results in a low total utility for the agents, even though the items are allocated efficiently. In this paper, we study strategy-proof allocation mechanisms that do not always allocate the items efficiently. It turns out that by allocating inefficiently, more payment can sometimes be redistributed, so that the net effect is an increase in the sum of the agents' utilities. Our objective is to design mechanisms that are competitive against the first-best mechanism in terms of the agents' total utility. We first study multi-unit auctions with unit demand. We characterize the family of linear allocation mechanisms. We propose an optimization technique for simultaneously finding a linear allocation mechanism and a payment redistribution rule, which together are optimal. With the help of this technique, we also analytically characterize several competitive mechanisms, which are based on burning units and partitioning the agents into groups. Finally, we extend the definition of linear allocation mechanisms and the optimization technique to general multi-unit auctions.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Many problems in multiagent systems involve resource allocation. This paper studies the fundamental problem of using economic mechanisms to allocate resources among autonomous agents, with the aim of maximizing the agents' total utility. We focus on settings where the resource consists of multiple indistinguishable units. Example of real-life scenarios includes the allocation of cluster nodes to supercomputing clients, where the cluster nodes are identical. Mechanisms proposed in this paper can be applied to scenarios where each agent requires only one unit of the resource (e.g., the client application contains a single thread, thus requiring only one node) or each agent's marginal valuations for the units are nonincreasing (e.g., the client application runs faster with more nodes, but the marginal benefit is nonincreasing). Besides proposing mechanisms that address a fundamental problem in multiagent systems, our results also demonstrate the effectiveness of using computing techniques to deliver new results in economic theory.
     </paragraph>
     <paragraph>
      For the problem of allocating one or more items among a group of competing agents, the well-known Vickrey–Clarke–Groves (VCG) mechanism [30], [5], [12] is strategy-proof and efficient.{sup:2} That is, under the VCG mechanism, it is a dominant strategy for the agents to report their true valuations for the items, and the mechanism allocates the items in a way that maximizes the sum of the agents' valuations. In the context of resource allocation, the VCG mechanism also satisfies the non-deficit property: the sum of the agents' payments is nonnegative. However, the VCG mechanism is not strongly budget balanced, that is, the agents' payments do not sum to 0. Hence, in general, value flows out of the system of agents in the form of VCG payments, which reduces the agents' utilities. Actually, for sufficiently general settings, no mechanism satisfies strategy-proofness, efficiency, and strong budget balance at the same time [22], [11], [10], [24].{sup:3}
     </paragraph>
     <paragraph>
      In many cases, the objective of the allocation process is to maximize the welfare of the agents, that is, the sum of the agents' utilities, taking payments into account. For this purpose, several VCG redistribution mechanisms have been proposed. These mechanisms first allocate the items efficiently and charge the VCG payments. Then, a large fraction of the VCG revenue is redistributed back to the agents, in a way that maintains the desirable properties of the original VCG mechanism, including strategy-proofness, the non-deficit property, and (sometimes) individual rationality [4], [16], [23], [18], [17], [14], [13], [15], [19], [25].{sup:4}
     </paragraph>
     <paragraph>
      However, in some cases, even the best redistribution mechanism fails to redistribute a substantial amount of the VCG revenue. That is, even though the VCG redistribution mechanisms maximize efficiency (the sum of the agents' valuations), the total welfare (the sum of the agents' utilities, taking payments into account) can be very low (in fact, zero), as a result of poor redistribution. Still, the previously proposed VCG redistribution mechanisms are optimal in various senses – but only under the constraint that allocation is efficient.
     </paragraph>
     <paragraph>
      In this paper, we consider the natural next step of allowing for inefficient allocation. It turns out that even though inefficient allocation reduces efficiency, it sometimes allows for greater redistributions, so that the net effect is an increase in the sum of the agents' utilities. Moulin [23] already provided an example where inefficient allocation can lead to better results, but left a more thorough investigation for future research. As we will see, the example mechanism that he proposed will turn out to be useful for us. In work subsequent to the conference version of our paper, de Clippel et al. [6] also study the problem of allocating inefficiently in order to increase the amount that is redistributed. We will discuss their work in more detail below.
     </paragraph>
     <paragraph>
      In Section 2, we cover the preliminaries. In Section 3, we briefly review the worst-case optimal (WCO) VCG redistribution mechanism [16], [23]. For our setting and objective, the WCO mechanism is optimal among all strategy-proof mechanisms that are based on efficient allocation. We give an example where the WCO mechanism performs poorly, and its performance actually improves when we burn (throw away) one item.{sup:5} This shows that inefficient allocation can indeed (sometimes) lead to better results. In Section 4, we characterize the linear allocation mechanisms for multi-unit auctions with unit demand, and propose an optimization technique for simultaneously finding a linear allocation mechanism and a payment redistribution rule, which together are optimal. With the help of the technique developed in Section 4, in Section 5, we analytically characterize several mechanisms that are guaranteed to perform well for all type profiles, which are based on burning units and partitioning the agents into groups. In Section 6, we compare the performances of the obtained mechanisms. Finally, in Section 7, we extend the definition of linear allocation mechanisms and the optimization technique to general multi-unit auctions.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      From this section to Section 6, we restrict our attention to multi-unit auctions with unit demand. In such auctions, multiple indistinguishable units are for sale at the same time, and each agent is interested in obtaining one and only one unit. In Section 7, we drop the unit demand restriction. To simplify the presentation, we defer everything beyond the unit demand setting to Section 7.
     </paragraph>
     <paragraph>
      Let the number of units be m. Let the number of agents be n. We consider only cases where {a mathematical formula}n&gt;m; otherwise, it is clearly optimal to give every agent a unit and charge nothing. (This reasoning is not valid without the unit demand assumption, so in Section 7 we also consider cases where {a mathematical formula}m≥n.)
     </paragraph>
     <paragraph>
      In the unit demand setting, an agent's type can be denoted by a single nonnegative value, which represents her valuation for winning (one unit). For the i-th agent, we denote her type by {a mathematical formula}vi. We focus on strategy-proof mechanisms in this paper. Therefore, we do not differentiate between “true types” and “reported types.” Without losing generality, we assume that {a mathematical formula}v1≥v2≥…≥vn≥0. Vector ({a mathematical formula}v1,v2,…,vn) is called the type profile.
     </paragraph>
     <paragraph>
      An allocation mechanism determines how we allocate the units, and how much each agent pays (or receives). We allow for randomized allocation mechanisms. In this paper, we assume that the agents are maximizing their expected (quasilinear) utilities, and random bits are not chosen adversarially. Please refer to Section 8 for more discussion on random bits. We use {a mathematical formula}aiM,V to denote agent i's probability of winning (one unit) under allocation mechanism M and for type profile V. When M and V are clear from the context, we simply use {a mathematical formula}ai to denote agent i's probability of winning. We denote the overall allocation by ({a mathematical formula}a1,a2,…,an). Since there are only m units, we must have {a mathematical formula}∑i=1nai≤m. The set of all feasible allocations is {a mathematical formula}{(a1,a2,…,an)|0≤a1,a2,…,an≤1,∑i=1nai≤m}.{sup:6} Similarly, we use {a mathematical formula}tiM,V to denote agent i's payment (expected payment if the allocation mechanism is randomized) under allocation mechanism M and for type profile V. When M and V are clear from the context, we simply use {a mathematical formula}ti to denote agent i's payment. For example, under the VCG mechanism, for a given type profile ({a mathematical formula}v1,v2,…,vn), if {a mathematical formula}i≤m, then {a mathematical formula}ai=1 and {a mathematical formula}ti=vm+1, and if {a mathematical formula}i&gt;m, then {a mathematical formula}ai=0 and {a mathematical formula}ti=0. (Under the VCG mechanism, the agents with the m highest types each win one unit and each pay the value of the {a mathematical formula}(m+1)-th highest type.) As a second example, under the mechanism in which the winners are picked uniformly at random (without payments), for all i, {a mathematical formula}ai=mn and {a mathematical formula}ti=0. We assume that an agent wishes to maximize her expected utility. That is, agent i wishes to maximize {a mathematical formula}aivi−ti.
     </paragraph>
     <paragraph>
      Given a strategy-proof allocation mechanism, we can use the following approach to attempt to increase the agents' utilities while maintaining strategy-proofness: redistribute (pay) to each agent an amount that is independent of her own type. When an agent's redistribution is independent of her own type, no matter what she reports, she receives the same amount of redistribution. This implies that the redistribution is irrelevant to the agent from the perspective of strategic reporting; and hence, if the allocation mechanism without redistribution is strategy-proof, then so is the mechanism with redistribution. In this paper, we use “allocation mechanism” to refer to the mechanism before redistribution – for example, in a VCG redistribution mechanism, the VCG mechanism is the allocation mechanism, whereas the complete mechanism also includes the redistributions. We use the function R to denote the redistribution rule. {a mathematical formula}R(v−i) is the amount of redistribution received by agent i, where {a mathematical formula}v−i are the types of the agents other than i.{sup:7} Not all redistribution rules are feasible. We require that the complete mechanism (after redistribution) satisfies two properties. First, we require that the complete mechanism satisfies the non-deficit property: the total redistribution should never exceed the total payment collected by the allocation mechanism ({a mathematical formula}∑i=1nR(v−i)≤∑i=1nti). Otherwise, we need an external subsidy to run the mechanism. We also require that the complete mechanism is individually rational: every agent's expected utility after redistribution must be nonnegative ({a mathematical formula}aivi−ti+R(v−i)≥0).
     </paragraph>
     <paragraph>
      With redistribution, the agents' welfare is {a mathematical formula}∑i=1naivi−∑i=1nti+∑i=1nR(v−i). Our goal is to find a complete mechanism (a strategy-proof allocation mechanism M and a feasible redistribution function R) that maximizes this expression. However, because the value of the above expression depends on the type profile, it could be that one complete mechanism {a mathematical formula}(M,R) maximizes the expression for some type profiles, while another complete mechanism {a mathematical formula}(M,R) maximizes the expression for some other type profiles. In this paper, we pursue a worst-case analysis approach. Such approaches have been commonly used in the literature on redistribution mechanisms [16], [23], [13], [14], [15], [19], [25]{sup:8} as well as the literature on digital goods auctions [1], [9], [20]. Specifically, consider the first-best mechanism that always correctly identifies the agents with the m highest true valuations, without asking for their types, and allocates the units to these agents at no charge. Clearly this mechanism obtains the largest welfare that we could hope for without external subsidy. Of course, the first-best mechanism is not strategy-proof, so we only use it as a benchmark. Our objective is to design strategy-proof mechanisms that are competitive against the first-best mechanism. We say a complete mechanism {a mathematical formula}(M,R) is α-competitive against the first-best mechanism if the agents' welfare under {a mathematical formula}(M,R) is at least {a mathematical formula}α∑i=1mvi, for all type profiles. ({a mathematical formula}∑i=1mvi is the agents' welfare under the first-best mechanism.) Our objective is to find the complete mechanism {a mathematical formula}(M,R) that is the most competitive, that is, that maximizes α, under the constraints that {a mathematical formula}(M,R) must satisfy strategy-proofness, individual rationality, and the non-deficit property.{sup:9}
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      VCG redistribution mechanisms
     </section-title>
     <paragraph>
      In this section, we first review the worst-case optimal (WCO) VCG redistribution mechanism. For our setting and objective, the WCO mechanism is optimal among all strategy-proof mechanisms that are based on efficient allocation. Then, to motivate the rest of the paper, we construct an example mechanism that allocates inefficiently and is more competitive than the WCO mechanism. This shows that inefficient allocation can indeed (sometimes) lead to higher competitive ratios.
     </paragraph>
     <paragraph>
      In previous work [16], we characterized the worst-case optimal VCG redistribution mechanism, which maximizes the fraction of VCG payment that is redistributed in the worst case, among all VCG redistribution mechanisms that are individually rational and satisfy the non-deficit property. The WCO mechanism is defined for all multi-unit auctions where each agent has nonincreasing marginal values for units.{sup:10} In the more restricted unit demand setting, the WCO mechanism uses the following redistribution function:{a mathematical formula}{a mathematical formula} Here, {a mathematical formula}v−j,i is the i-th highest type among {a mathematical formula}v−j.
     </paragraph>
     <paragraph>
      Around the same time, Moulin [23] independently characterized the same mechanism based on a different objective.{sup:11} In fact, Moulin's characterization of WCO implies that the WCO mechanism has the highest competitive ratio (in the sense of this paper) among all VCG redistribution mechanisms with the required properties.
     </paragraph>
     <paragraph label="Claim 1">
      (See[23].) The WCO mechanism has the highest competitive ratio against the first-best mechanism, among all VCG redistribution mechanisms that are individually rational and satisfy the non-deficit property.
     </paragraph>
     <paragraph>
      It should be noted that, by the result of Holmstrom [21], in multi-unit auctions with unit demand, all efficient and strategy-proof mechanisms are VCG redistribution mechanisms. That is, the above claim essentially says that WCO has the highest competitive ratio among all efficient mechanisms that are strategy-proof, individually rational, and satisfy the non-deficit property.
     </paragraph>
     <paragraph>
      Given the number of agents n and the number of units m ({a mathematical formula}n&gt;m), the WCO mechanism's competitive ratio {a mathematical formula}αWCO(n,m) is characterized by the following equation:{a mathematical formula}
     </paragraph>
     <paragraph>
      When {a mathematical formula}n=3 and {a mathematical formula}m=2, the WCO mechanism (the optimal efficient mechanism) is not competitive at all: {a mathematical formula}αWCO(3,2)=0. In contrast, the following simple mechanism that allocates inefficiently is somewhat competitive:
     </paragraph>
     <list>
      <list-item label="•">
       Burn (throw away) one unit.
      </list-item>
      <list-item label="•">
       Allocate the remaining unit according to the WCO mechanism for {a mathematical formula}n=3 and {a mathematical formula}m=1.
      </list-item>
     </list>
     <paragraph>
      The new mechanism satisfies all the required properties, because it is equivalent to the WCO mechanism for {a mathematical formula}n=3 and {a mathematical formula}m=1. It is not efficient because one unit is burned. Since {a mathematical formula}αWCO(3,1)=13, the new mechanism is {a mathematical formula}13-competitive against the first-best mechanism for one unit ({a mathematical formula}m=1). That is, the new mechanism guarantees a welfare of {a mathematical formula}13v1 for any type profile. Since {a mathematical formula}v1≥v2, it also guarantees a total utility of {a mathematical formula}16(v1+v2) for all type profiles. Hence, the competitive ratio of the new mechanism against the first-best mechanism for two units ({a mathematical formula}m=2) is at least {a mathematical formula}16. That is, this new mechanism has a higher competitive ratio. Essentially, if we keep both items, then no redistribution is possible. On the other hand, if we throw away one item, then we are able to redistribute some payments, which results in a higher competitive ratio. So, ironically, in some cases, the agents are happier if one unit is burned. Motivated by this example, in the rest of the paper, we study mechanisms that allocate inefficiently (and in Section 5.1, we specifically study mechanisms that are based on burning units).
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Linear allocation mechanisms
     </section-title>
     <paragraph>
      In this section, we define and characterize a family of mechanisms that we call linear allocation mechanisms.{sup:12} We then propose an optimization technique for simultaneously finding a linear allocation mechanism and a redistribution rule, which together have the highest competitive ratio among all mechanisms whose allocation part is linear.{sup:13}
     </paragraph>
     <paragraph label="Definition 1">
      An allocation mechanism is linear if the following two conditions are satisfied:
     </paragraph>
     <list>
      <list-item label="•">
       An agent's probability of winning depends only on her rank. That is, under a linear allocation mechanism, the {a mathematical formula}ai are constants ({a mathematical formula}ai only depends on the rank i, but not the value of {a mathematical formula}vi). (We recall that agent i is the agent with the i-th highest type, and {a mathematical formula}ai is agent i's probability of winning.) That is, a linear allocation mechanism corresponds to a constant allocation vector {a mathematical formula}(a1,a2,…,an).
      </list-item>
      <list-item label="•">
       An agent's payment is always 0 if her type is 0.
      </list-item>
     </list>
     <paragraph label="Example 1">
      The VCG mechanism is linear, for the following reasons. In the VCG mechanism, the agents with the highest m types each win one unit. That is, for all type profiles, we have {a mathematical formula}ai=1 for {a mathematical formula}i≤m and {a mathematical formula}ai=0 for {a mathematical formula}i&gt;m. Under the VCG mechanism, when an agent's type is 0, her payment is 0.
     </paragraph>
     <paragraph label="Example 2">
      The random allocation mechanism in which the winners are picked uniformly at random (without replacement), and there are no payments, is linear, for the following reasons. Under this mechanism, for all type profiles, we have {a mathematical formula}ai=m/n for all i, and every agent pays 0.
     </paragraph>
     <paragraph>
      We are only interested in linear allocation mechanisms that are strategy-proof. The next claim gives a standard type of monotonicity characterization of all strategy-proof linear allocation mechanisms.
     </paragraph>
     <paragraph label="Claim 2">
      There is a one-to-one correspondence between strategy-proof linear allocation mechanisms and the following set of allocation vectors:{a mathematical formula}That is, a strategy-proof linear allocation mechanism is characterized by its corresponding allocation vector{a mathematical formula}(a1,a2,…,an)where{a mathematical formula}1≥a1≥a2≥…≥an≥0.
     </paragraph>
     <paragraph>
      From now on, we will simply use allocation vector {a mathematical formula}(a1,a2,…,an) to refer to the (only) corresponding strategy-proof linear allocation mechanism. We will only consider strategy-proof linear allocation mechanisms.
     </paragraph>
     <paragraph>
      Under linear allocation mechanism {a mathematical formula}(a1,a2,…,an), the mechanism's efficiency equals {a mathematical formula}∑i=1naivi. Agent i's VCG-based payment equals the following:{a mathematical formula}
     </paragraph>
     <paragraph>
      The agents' total payment equals{a mathematical formula}
     </paragraph>
     <paragraph>
      Under a given linear allocation mechanism, the mechanism's efficiency and the agents' total payment are both linear functions of the types, and the coefficients are constants. This is why we call these linear allocation mechanisms.
     </paragraph>
     <paragraph>
      Next, we present more example linear allocation mechanisms.
     </paragraph>
     <paragraph label="Example 3">
      Let us consider the case where {a mathematical formula}m&gt;1. The mechanism that burns one unit and allocates the remaining units efficiently is linear. It corresponds to the allocation vector {a mathematical formula}(1,1,…,1︸m−1,0,…,0). (The agents' payments are VCG-based.)
     </paragraph>
     <paragraph label="Example 4">
      The mechanism that excludes one agent uniformly at random and allocates the units among the remaining agents efficiently is linear. Agents 1 to m will win unless excluded, so {a mathematical formula}ai=n−1n for {a mathematical formula}i=1,2,…,m. Agent {a mathematical formula}m+1 will win only when one of the first m agents gets excluded, so {a mathematical formula}am+1=mn. The other agents never win. The mechanism corresponds to the allocation vector {a mathematical formula}(n−1n,n−1n,…,n−1n︸m,mn,0,…,0). (The agents' payments are VCG-based.)
     </paragraph>
     <paragraph label="Example 5">
      It is easy to see that the set {a mathematical formula}{(a1,a2,…,an)|1≥a1≥a2≥…≥an≥0,∑i=1nai≤m} is convex. That is, any probability mixture over linear allocation mechanisms is also linear.
     </paragraph>
     <paragraph>
      In what follows, we introduce an optimization technique for simultaneously finding a linear allocation mechanism and a payment redistribution rule, which together have the highest competitive ratio among all mechanisms whose allocation part is linear.
     </paragraph>
     <paragraph>
      Since there is a one-to-one correspondence between linear allocation mechanisms and allocation vectors in {a mathematical formula}{(a1,a2,…,an)|1≥a1≥a2≥…≥an≥0,∑i=1nai≤m}, essentially, we are solving for the optimal values of the {a mathematical formula}ai, as well as an optimal redistribution function R, so that the linear allocation mechanism {a mathematical formula}(a1,a2,…,an) and R together have the highest competitive ratio. This comes down to the following optimization model:{a mathematical formula}
     </paragraph>
     <paragraph>
      The non-deficit constraint and the competitive ratio constraint are both self-explanatory. (We recall that {a mathematical formula}∑i=1n∑j=i+1n(aj−1−aj)vj is the agents' total payment, {a mathematical formula}∑i=1naivi is the mechanism's efficiency, and {a mathematical formula}∑i=1mvi is the welfare under the first-best mechanism.) What remains to be explained is why the individual rationality constraint is equivalent to {a mathematical formula}R(v−n)≥0. First, {a mathematical formula}R(v−n)≥0 is necessary for individual rationality, because we need to make sure that every agent's final utility is nonnegative for every type profile. When agent n's type is 0, she pays 0 under any linear allocation mechanism. Because she does not care for receiving any unit, her final utility is just her redistribution, which is {a mathematical formula}R(v−n). Hence, {a mathematical formula}R(v−n)≥0 is necessary for individual rationality. On the other hand, when {a mathematical formula}R(v−n) is nonnegative for every {a mathematical formula}v−n, we have that for every collection of {a mathematical formula}n−1 types, denoted by S, {a mathematical formula}R(S)≥0. That is, {a mathematical formula}R(v−i)≥0 for all i. That is, redistribution makes every agent (weakly) better off. Even without redistribution, every agent's utility is at least 0. (An agent can always report 0 and pay 0.) Therefore, {a mathematical formula}R(v−n)≥0 is also sufficient for individual rationality.
     </paragraph>
     <paragraph>
      The above formulation is a functional optimization problem, which may appear difficult to solve. In what follows, we present a linear program formulation. Based on the solution to this linear program, we can construct an optimal solution to the above functional optimization problem.
     </paragraph>
     <paragraph>
      If we only consider the type profiles in which the {a mathematical formula}vi are binary, then the above functional optimization problem turns into a value optimization problem, as follows. When we only consider binary type profiles, we do not have to consider the values of R for other profiles. We use {a mathematical formula}ri ({a mathematical formula}i=0,1,…,n−1) to denote {a mathematical formula}R(1,…,1︸i,0,…,0︸n−1−i): the redistribution received by an agent when i other agents report 1, and the remaining {a mathematical formula}n−1−i agents report 0. In the original functional optimization problem, we are optimizing over the {a mathematical formula}ai and the function R. When we only consider binary type profiles, we only need to optimize over the {a mathematical formula}ai and the {a mathematical formula}ri, which corresponds to the following value optimization problem:{a mathematical formula}
     </paragraph>
     <paragraph>
      The optimal objective value of the above value optimization problem is greater than or equal to the optimal objective value of the original functional optimization problem, because there are fewer constraints (here, we are only enforcing the constraints on binary type profiles).
     </paragraph>
     <paragraph>
      We now show that this is indeed a linear program. The objective is clearly linear in the variables. The two constraints involving only the {a mathematical formula}ai are clearly linear inequalities. The individual rationality constraint is just “for all i from 0 to {a mathematical formula}n−1, {a mathematical formula}ri≥0.” The non-deficit constraint is also equivalent to a set of linear inequalities, as follows. When {a mathematical formula}vi=0 for all i, the non-deficit constraint is {a mathematical formula}0≥nr0.{sup:14} When {a mathematical formula}v1=1 and {a mathematical formula}vi=0 for all {a mathematical formula}i&gt;1, the non-deficit constraint is {a mathematical formula}0≥(n−1)r1+r0. When {a mathematical formula}v1=v2=1 and {a mathematical formula}vi=0 for all {a mathematical formula}i&gt;2, the non-deficit constraint is {a mathematical formula}(a1−a2)v2=a1−a2≥(n−2)r2+2r1. Similarly, for any other binary type profile, the non-deficit constraint also corresponds to a linear inequality. In total, the {a mathematical formula}vi can take {a mathematical formula}n+1 sets of values (from all 0s to all 1s). Therefore, the non-deficit constraint is equivalent to {a mathematical formula}n+1 linear inequalities. By similar reasoning, the competitive ratio constraint is also equivalent to {a mathematical formula}n+1 linear inequalities. We conclude that the above value optimization problem is indeed a linear program.
     </paragraph>
     <paragraph>
      We use the {a mathematical formula}ai⁎, the {a mathematical formula}ri⁎, and {a mathematical formula}α⁎ to denote an optimal solution to the linear program. As we noted, {a mathematical formula}α⁎, the optimal objective value of the linear program, is greater than or equal to the optimal objective value of the original functional optimization problem. That is, {a mathematical formula}α⁎ is an upper bound on the competitive ratio of any complete mechanism whose allocation part is linear. In the following theorem, we show that this upper bound can be achieved: we construct a complete mechanism whose allocation part is linear, and prove that this mechanism has a competitive ratio of {a mathematical formula}α⁎. It follows immediately that the mechanism we construct is optimal among all complete mechanisms whose allocation part is linear.
     </paragraph>
     <paragraph label="Theorem 1">
      For all i and all{a mathematical formula}v−i, let{a mathematical formula}R⁎(v−i)=∑j=1n−1(rj⁎−rj−1⁎)v−i,j. (We recall that{a mathematical formula}v−i,jis the j-th highest type among the agents other than i.) Complete mechanism{a mathematical formula}((a1⁎,a2⁎,…,an⁎),R⁎)is{a mathematical formula}α⁎-competitive. That is, this mechanism has the highest competitive ratio among all complete mechanisms whose allocation part is linear.{sup:15}
     </paragraph>
     <paragraph>
      According to footnote 14, we have {a mathematical formula}r0⁎=0. We note that when the {a mathematical formula}vi are binary, from the perspective of an agent, if all the other agents report 0, then her redistribution equals {a mathematical formula}∑j=1n−1(rj⁎−rj−1⁎)0=0=r0⁎. If among the other agents, k ({a mathematical formula}k&gt;0) agents report 1, and the remaining agents report 0, then her redistribution equals {a mathematical formula}∑j=1k(rj⁎−rj−1⁎)=rk⁎. That is, in a sense, {a mathematical formula}R⁎ is a linear interpolation of the {a mathematical formula}ri⁎. Before proving the theorem, we give the following lemma. A similar lemma appeared in Guo and Conitzer [16].
     </paragraph>
     <paragraph label="Lemma 1">
      When the{a mathematical formula}cido not depend on the{a mathematical formula}xi, the following two systems of inequalities are equivalent:
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}c1x1+c2x2+…+csxs≥0for all{a mathematical formula}x1≥x2≥…≥xs≥0.
      </list-item>
      <list-item label="(b)">
       {a mathematical formula}c1x1+c2x2+…+csxs≥0for all{a mathematical formula}x1≥x2≥…≥xs, where the{a mathematical formula}xiare binary.
      </list-item>
     </list>
     <paragraph label="Proof">
      (a) ⇒ (b) is trivial. We now prove (b) ⇒ (a). (b) implies that {a mathematical formula}∑i=1jci≥0 for all {a mathematical formula}1≤j≤s. We have {a mathematical formula}c1x1+c2x2+…+csxs=∑j=1s−1(∑i=1jci)(xj−xj+1)+(∑i=1sci)xs. For all {a mathematical formula}x1≥x2≥…≥xs≥0, each term of the above expression is nonnegative, hence the whole expression is nonnegative. So (b) ⇒ (a).  □
     </paragraph>
     <paragraph>
      We are now ready to prove the theorem.
     </paragraph>
     <paragraph label="Proof">
      We only need to prove that {a mathematical formula}α⁎, the {a mathematical formula}ai⁎, and the function {a mathematical formula}R⁎ form a feasible solution to the original functional optimization problem. If they form a feasible solution, then {a mathematical formula}((a1⁎,a2⁎,…,an⁎),R⁎) is {a mathematical formula}α⁎-competitive, implying that it is optimal. That is, we need to prove that the following constraints hold (it is obvious that the constraints involving only the {a mathematical formula}ai hold):
      <list>
       For every type profile {a mathematical formula}v1≥v2≥…≥vn≥0,We notice that all the above inequalities are linear inequalities of the
      </list>
      <paragraph>
       {a mathematical formula}vi, which must hold for all {a mathematical formula}v1≥v2≥…≥vn≥0, where the coefficients only depend on the {a mathematical formula}ri⁎, the {a mathematical formula}ai⁎, and {a mathematical formula}α⁎. For example, the individual rationality constraint can be rewritten as “for every type profile {a mathematical formula}v1≥v2≥…≥vn≥0, {a mathematical formula}∑j=1n−1(rj⁎−rj−1⁎)vj≥0.” Similarly, the non-deficit constraint is “for every type profile {a mathematical formula}v1≥v2≥…≥vn≥0, {a mathematical formula}∑i=1n∑j=i+1n(aj−1⁎−aj⁎)vj≥∑i=1n∑j=1n−1(rj⁎−rj−1⁎)v−i,j. Here, the left-hand side of ≥ is a linear function of the {a mathematical formula}vi, where the linear coefficients only depend on the {a mathematical formula}ai⁎. We have that if {a mathematical formula}j&lt;i, then {a mathematical formula}v−i,j=vj, otherwise {a mathematical formula}v−i,j=vj+1. The right-hand side of ≥ is also a linear function of the {a mathematical formula}vi, where the linear coefficients only depend on the {a mathematical formula}ri⁎. Similarly, the competitive ratio constraint is “for every type profile {a mathematical formula}v1≥v2≥…≥vn≥0, {a mathematical formula}∑i=1nai⁎vi−∑i=1n∑j=i+1n(aj−1⁎−aj⁎)vj+∑i=1n∑j=1n−1(rj⁎−rj−1⁎)v−i,j≥α⁎∑i=1mvi. That is, the competitive ratio constraint is also a linear inequality of the {a mathematical formula}vi, which must hold for all {a mathematical formula}v1≥v2≥…≥vn≥0, and the linear coefficients only depend on the {a mathematical formula}ri⁎, the {a mathematical formula}ai⁎, and {a mathematical formula}α⁎. If we apply Lemma 1, then we only need to prove that these constraints hold when the {a mathematical formula}vi are binary. (When the {a mathematical formula}vi are binary, {a mathematical formula}R⁎ reduces to the {a mathematical formula}ri⁎.) But, we already know that linear allocation mechanism {a mathematical formula}(a1⁎,a2⁎,…,an⁎), combined with the redistribution rule characterized by the {a mathematical formula}ri⁎, satisfies all the constraints when the {a mathematical formula}vi are binary.  □
      </paragraph>
     </paragraph>
     <paragraph>
      Using Theorem 1, for different numbers of agents n and different numbers of units m, we solve for the most competitive complete mechanisms whose allocation part is linear. The obtained mechanisms' competitive ratios will be presented in Section 6.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Analytical competitive mechanisms
     </section-title>
     <paragraph>
      One drawback of the technique proposed in the previous section is that we need to solve a linear program for every n and m, and we do not have an analytical characterization of the resulting mechanisms. In this section, we study two restricted families of linear allocation mechanisms. One family is based on burning units. The other is based on partitioning the agents into groups. We will use the technique introduced in the previous section to optimize within both families (adding more constraints on the {a mathematical formula}ai, as we are looking at more restricted families of linear allocation mechanisms). By observing the patterns of the obtained mechanisms, we have analytically characterized several competitive mechanisms. In Section 6, we compare the competitive ratio of the optimal mechanism that is based on linear allocation, and the competitive ratios of the analytical mechanisms.
     </paragraph>
     <section label="5.1">
      <section-title>
       Burning units
      </section-title>
      <paragraph>
       In this subsection, we study linear allocation mechanisms that are based on (sometimes) burning units. We start with the characterization. First, we can construct m linear allocation mechanisms that are based on burning a deterministic number of units. Let {a mathematical formula}Mi ({a mathematical formula}i=1,…,m) be the allocation mechanism in which {a mathematical formula}m−i units are burned, and the remaining i units are allocated efficiently according to the VCG mechanism. {a mathematical formula}Mm is just the original VCG mechanism. We note that it makes no sense to burn all units, hence {a mathematical formula}i&gt;0. We call the {a mathematical formula}Mideterministic burning allocation mechanisms. {a mathematical formula}Mi is the linear allocation mechanism {a mathematical formula}(1,1,…,1︸i,0,0,…,0). We can also construct mechanisms in which a random number of units is burned, by randomizing over the {a mathematical formula}Mi. Let M be a mixture of the {a mathematical formula}Mi, where mechanism {a mathematical formula}Mi is chosen with probability {a mathematical formula}pi. That is, M is the mechanism in which with probability {a mathematical formula}pi, exactly {a mathematical formula}m−i units are burned. We call such mixtures over the {a mathematical formula}Mirandomized burning allocation mechanisms. Under M, for {a mathematical formula}i=1,2,…,m, agent i wins with probability {a mathematical formula}∑j=impj, and the other agents never win. M is the linear allocation mechanism {a mathematical formula}(∑i=1mpi,∑i=2mpi,∑i=3mpi,…,∑i=mmpi,0,0,…,0). The family of linear allocation mechanisms that are based on the idea of burning a random number of units is then the linear allocation mechanisms whose allocation vectors are in {a mathematical formula}{(a1,a2,…,an)|am+1=am+2=…=an=0,1=a1≥a2≥…≥am≥0}.
      </paragraph>
      <paragraph>
       Using Theorem 1, we can find the most competitive burning-based mechanism. To solve for the most competitive randomized burning-based mechanism, we need to add two more constraints to the linear program: {a mathematical formula}am+1=0 and {a mathematical formula}a1=1. To solve for the most competitive deterministic burning-based mechanism, we need to add n more constraints to the linear program and turn it into a mixed integer program: for all i, {a mathematical formula}ai is binary. We will present more results in Section 6. Here, for the case of {a mathematical formula}n=10, {a mathematical formula}m=1,…,9, we compare the values of {a mathematical formula}αWCO⁎ (competitive ratio of the WCO mechanism, which burns nothing), {a mathematical formula}αD⁎ (competitive ratio of the optimal deterministic burning-based mechanism) and {a mathematical formula}αR⁎ (competitive ratio of the optimal randomized burning-based mechanism) in Fig. 1. When m is small, the three values are the same. As m gets large, the value of {a mathematical formula}αWCO⁎ decreases all the way to 0; the value of {a mathematical formula}αD⁎ also decreases but it gets stable when its value goes down to around 0.5; the value of {a mathematical formula}αR⁎ first decreases, but then increases, and at the end almost reaches 1.
      </paragraph>
      <paragraph>
       Of course, {a mathematical formula}αWCO⁎≤αD⁎≤αR⁎; it turns out that all of these inequalities are sometimes strict. Therefore, in general, we need to burn a random number of units to get the most competitive burning-based mechanism.
      </paragraph>
      <paragraph>
       While we can use Theorem 1 to numerically solve for the most competitive burning-based mechanism for given n and m, it is still desirable to have a general analytical characterization for all n and m. The following claim analytically characterizes a burning-based mechanism for all n and m, and gives its competitive ratio. We obtained this analytical competitive mechanism by observing the patterns of the (numerically obtained) optimal burning-based mechanisms for all {a mathematical formula}n&lt;10. We do not know whether this mechanism is still optimal for larger n. However, we do know that this mechanism is feasible and has the specified competitive ratio for all n and m.
      </paragraph>
      <paragraph>
       The intuition behind the proposed mechanism is as follows. We aim to redistribute more by allocating inefficiently, in order to achieve a net benefit. It turns out that we can guarantee {a mathematical formula}100% redistribution by burning at most one unit. For any type profile, the total VCG payment is {a mathematical formula}mvm+1 when nothing is burned, and it is {a mathematical formula}(m−1)vm when one unit is burned. If we burn one unit with probability {a mathematical formula}n−mn−1, then in expectation, the total payment collected by the allocation mechanism is {a mathematical formula}n−mn−1(m−1)vm+(1−n−mn−1)mvm+1=m−1n−1(mvm+1+(n−m)vm). Throughout this paper, for randomized mechanisms, we simply charge agents the expected payments, instead of charging a different payment depending on the realization of the mechanism (e.g., whether a unit was burned). The agents' incentives will not be affected, because agents are assumed to be maximizing their expected (quasilinear) utility. By redistributing to every agent {a mathematical formula}m−1n−1 times the m-th highest type among the others, the total redistribution equals exactly the total payment. When m is not too small, it is an acceptable sacrifice of allocative efficiency to burn at most one unit to achieve strong budget balance. When m is very small, we cannot afford to burn any units, so it is better to use the original worst-case optimal VCG redistribution mechanism (nothing is burned).
      </paragraph>
      <paragraph label="Claim 3">
       For any n and m, we can achieve the following competitive ratio with a burning-based mechanism:{a mathematical formula}If the first expression is greater (or equal), then the mechanism achieving the above ratio is the worst-case optimal VCG redistribution mechanism (nothing is burned).If the second expression is greater, then the mechanism achieving the above ratio is the following:
      </paragraph>
      <list>
       <list-item label="•">
        Burn (throw away) one unit with probability{a mathematical formula}n−mn−1. The remaining units are allocated efficiently. Every agent pays the VCG-based payment. (This is linear allocation mechanism{a mathematical formula}(1,1,…,1,m−1n−1,0,0,…,0).)
       </list-item>
       <list-item label="•">
        Every agent receives a redistribution of{a mathematical formula}m−1n−1times the m-th highest type among types other than this agent's own type.
       </list-item>
      </list>
     </section>
     <section label="5.2">
      <section-title>
       Partitioning units and agents
      </section-title>
      <paragraph>
       In this subsection, we study linear allocation mechanisms that are based on partitioning the agents into groups. This is an idea that has previously been proven effective in mechanism design [3], [9]. Based on this idea, we characterize a family of strongly budget balanced mechanisms. Some of the mechanisms in this class have been proposed previously [7], [23]. We focus on finding the most competitive mechanism in this family. Because all the mechanisms in this family are strongly budget balanced, no redistributions are ever needed.
      </paragraph>
      <paragraph>
       We start with two example mechanisms. They are both based on excluding one agent from the set of all agents. The first one is due to Moulin [23], and the second one is due to Faltings [7].
      </paragraph>
      <paragraph>
       Example Mechanism 1
      </paragraph>
      <list>
       <list-item label="•">
        Exclude one agent uniformly at random.
       </list-item>
       <list-item label="•">
        Assign one unit to the excluded agent at no charge.
       </list-item>
       <list-item label="•">
        The remaining units are allocated to the remaining agents according to the VCG mechanism.
       </list-item>
       <list-item label="•">
        Transfer all the VCG revenue to the excluded agent.
       </list-item>
      </list>
      <paragraph>
       Example Mechanism 2
      </paragraph>
      <list>
       <list-item label="•">
        Exclude one agent uniformly at random.
       </list-item>
       <list-item label="•">
        Units are allocated to the remaining agents according to the VCG mechanism.
       </list-item>
       <list-item label="•">
        Transfer all the VCG revenue to the excluded agent.
       </list-item>
      </list>
      <paragraph>
       Both example mechanisms are strategy-proof, individually rational, and strongly budget balanced. In the first mechanism, one agent is excluded and assigned one unit. In the second mechanism, one agent is excluded and assigned zero units. It should be noted that if we omit the last step in Example Mechanism 2, that is, if we do not transfer all the VCG revenue to the excluded agent, then the mechanism becomes exactly the linear allocation mechanism in Example 4. That is, it becomes linear allocation mechanism{a mathematical formula} Similarly, if we omit the last step in Example Mechanism 1, then the mechanism becomes linear allocation mechanism{a mathematical formula} (The first {a mathematical formula}m−1 agents always win, excluded or not. The m-th agent wins only if she is excluded or one agent from 1 to {a mathematical formula}m−1 is excluded. The other agents win only when excluded.)
      </paragraph>
      <paragraph>
       We now introduce the family of partitioning-based mechanisms; this family generalizes both of the previous two mechanisms.
      </paragraph>
      <paragraph label="Definition 2">
       Given n and m, for {a mathematical formula}n1∈{1,…,⌊n2⌋}, {a mathematical formula}m1∈{0,…,min⁡{n1,m}}, we define the following mechanism:
      </paragraph>
      <list>
       <list-item label="•">
        Pick {a mathematical formula}n1 agents to form one group, uniformly at random. The other {a mathematical formula}n−n1 agents form the second group.
       </list-item>
       <list-item label="•">
        Allocate {a mathematical formula}m1 units among the first group, according to the VCG mechanism.
       </list-item>
       <list-item label="•">
        Allocate the remaining {a mathematical formula}m−m1 units among the second group, according to the VCG mechanism.
       </list-item>
       <list-item label="•">
        Transfer the VCG revenue from the first group to the second group, in any predetermined way.
       </list-item>
       <list-item label="•">
        Transfer the VCG revenue from the second group to the first group, in any predetermined way.
       </list-item>
      </list>
      <paragraph>
       We note that Example Mechanisms 1 and 2 are the {a mathematical formula}(1,1)-partition mechanism and the {a mathematical formula}(1,0)-partition mechanism, respectively. Under any partitioning-based mechanism, whether an agent wins depends on which group she is assigned to, and her rank within her group. Since groups are randomly formed, independent of the type profile, an agent's probability of winning depends only on her rank. If we do not transfer the VCG revenue between the groups, then an agent pays 0 when her type is 0. That is, without transferring the VCG revenue, every partitioning-based mechanism is linear.
      </paragraph>
      <paragraph label="Claim 4">
       The partitioning-based mechanisms are strategy-proof, individually rational, and strongly budget balanced.
      </paragraph>
      <paragraph label="Proof">
       Without transferring the VCG revenue, every agent is participating in a VCG mechanism, which is strategy-proof. For each agent, the transfer payment she receives depends only on the types in the other group of agents, hence it does not affect her incentives. Therefore, the mechanisms are strategy-proof. Similarly, without transferring the VCG revenue, every agent is participating in a VCG mechanism, which is individually rational. With transferring, the agents' utilities become higher or stay the same. Therefore, the mechanisms are individually rational. Finally, the strong budget balance property follows from the fact that the entire VCG revenue is transferred.  □
      </paragraph>
      <paragraph>
       Since the partitioning-based mechanisms are strongly budget balanced, welfare equals efficiency for them. Hence, for our objective of finding the most competitive partitioning-based mechanism, we can completely ignore the VCG payments and the revenue transferring process. That is, for the analysis that follows, we pretend that there are no payments of any kind; when we use the mechanism, we add the VCG payments and transfers back to achieve strategy-proofness.
      </paragraph>
      <paragraph>
       We can use the technique in Theorem 1 to solve for the most competitive partitioning-based mechanism (ignoring all payments and redistributions). However, we now present a simpler solution technique based on the special structure of the family of partitioning-based mechanisms. The following claim characterizes the competitive ratio of a given partitioning-based mechanism.
      </paragraph>
      <paragraph label="Claim 5">
       Given n and m, the competitive ratio of the{a mathematical formula}(n1,m1)-partition mechanism equals{a mathematical formula}Here,{a mathematical formula}UMn1,m1(m)is the expected efficiency (welfare) under the{a mathematical formula}(n1,m1)-partition mechanism when m agents report 1 and the remaining agents report 0. This competitive ratio is equal to{a mathematical formula}Here,{a mathematical formula}X={x|x∈{0,1,…,n1},0≤m−x≤n−n1}. We will call this competitive ratio{a mathematical formula}αn1,m1⁎.
      </paragraph>
      <paragraph>
       So far, we have not considered mixtures over partitioning-based mechanisms. One might think that, by taking such mixtures, we can obtain more competitive mechanisms. However, the following claim rules out this idea.
      </paragraph>
      <paragraph label="Claim 6">
       If M is a mixture over{a mathematical formula}M1,M2,…,Mt, where the{a mathematical formula}Miare partitioning-based mechanisms for different values of{a mathematical formula}n1and{a mathematical formula}m1, and{a mathematical formula}Miis chosen with probability{a mathematical formula}pi, then there exists{a mathematical formula}1≤j≤tso that{a mathematical formula}Mjattains at least the competitive ratio of M.
      </paragraph>
      <paragraph label="Proof">
       By the same argument as in Claim 5, the competitive ratio of M is at most {a mathematical formula}UM(m)m. We have that {a mathematical formula}UM(m)m=∑i=1tpiUMi(m)m≤maxj⁡UMj(m)m. But {a mathematical formula}UMj(m)m is the competitive ratio for {a mathematical formula}Mj by Claim 5. Hence, taking {a mathematical formula}j∈arg⁡maxj⁡UMj(m)m, {a mathematical formula}Mj is at least as competitive as M.  □
      </paragraph>
      <paragraph>
       By Claim 5, for given n and m, by maximizing{a mathematical formula} over {a mathematical formula}n1 and {a mathematical formula}m1, we obtain the optimal {a mathematical formula}(n1,m1)-partition mechanism. This mechanism is also optimal among all mixtures of partitioning-based mechanisms by Claim 6. It is still desirable to have a general analytical characterization of the optimal {a mathematical formula}n1 and {a mathematical formula}m1 for all n and m. The following claim analytically characterizes three partitioning-based mechanisms for all n and m, and gives their corresponding competitive ratios. We identified these three mechanisms by observing the patterns of the (numerically obtained) optimal partitioning-based mechanisms for all {a mathematical formula}n&lt;10. We do not know whether there are other mechanisms that obtain higher competitive ratios for larger n. However, we do know that all three mechanisms are feasible and achieve the specified competitive ratios for all n and m.
      </paragraph>
      <paragraph>
       The intuition behind the following mechanism is as follows. When m is small, given a random agent, most likely this agent does not belong to the m highest agents. Therefore, when m is small, it is an acceptable sacrifice of allocative efficiency to randomly remove one agent and deny her any units (run the {a mathematical formula}(1,0)-partition mechanism). By doing so, we achieve strong budget balance, as well as efficiency for the rest of the agents. Similarly, when m is large relative to n, given a random agent, most likely this agent does belong to the m highest agents. Therefore, when m is large relative to n, it is an acceptable sacrifice of allocative efficiency to randomly remove one agent and give her one unit (run the {a mathematical formula}(1,1)-partition mechanism). Finally, when m is neither small nor large (e.g., m is close to {a mathematical formula}n/2), neither {a mathematical formula}(1,0) nor {a mathematical formula}(1,1) works the best. When m is close to {a mathematical formula}n/2, given two random agents, most likely exactly one of them belongs to the m highest agents. Therefore, in this scenario, it is more reasonable to exclude two agents at random, and give them only one unit (run the {a mathematical formula}(2,1)-partition mechanism).
      </paragraph>
      <paragraph label="Claim 7">
       For any n and m, we can achieve the following competitive ratio with a partitioning-based mechanism:{a mathematical formula}If the first expression is the largest, then the mechanism achieving the above ratio is the{a mathematical formula}(1,0)-partition mechanism.If the second expression is the largest, then the mechanism achieving the above ratio is the{a mathematical formula}(1,1)-partition mechanism.If the third expression is the largest, then the mechanism achieving the above ratio is the{a mathematical formula}(2,1)-partition mechanism.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Numerical results
     </section-title>
     <paragraph>
      In the following table, for different numbers of agents and different numbers of units, we present the competitive ratios of the WCO mechanism ({a mathematical formula}αWCO⁎), the competitive ratios of the optimal deterministic burning-based mechanism ({a mathematical formula}αD⁎), the competitive ratios of the optimal randomized burning-based mechanism ({a mathematical formula}αR⁎), the competitive ratios of the optimal partitioning-based mechanism ({a mathematical formula}αn1,m1⁎), and the competitive ratios of the optimal mechanism whose allocation part is linear ({a mathematical formula}α⁎). It should be noted that in all the experiments, the optimal randomized burning-based mechanism matches the analytical characterization in Claim 3, and the optimal partitioning-based mechanism matches the analytical characterization in Claim 7. The numbers below {a mathematical formula}αD⁎ are the numbers of units burned to achieve {a mathematical formula}αD⁎. The numbers below {a mathematical formula}αR⁎ are the probabilities of having one unit burned to achieve {a mathematical formula}αR⁎. The numbers below {a mathematical formula}αn1,m1⁎ are the values of {a mathematical formula}n1 and {a mathematical formula}m1 to achieve {a mathematical formula}αn1,m1⁎.{a mathematical formula}
     </paragraph>
     <paragraph label="Example 6">
      For illustration, for {a mathematical formula}n=8 and {a mathematical formula}m=5, for type profile {a mathematical formula}(8,7,6,5,4,3,2,1), we present the specific optimal mechanisms:
     </paragraph>
     <list>
      <list-item label="•">
       Optimal deterministic burning-based mechanism: Two units are burned. Agents compete for the remaining 3 units under the original VCG mechanism. Agents pay the VCG payments. On top of this, for all i, agent i receives back a redistribution amount that equals {a mathematical formula}0.4518v−i,4−0.2047v−i,5+0.1412v−i,6−0.1059v−i,7, where {a mathematical formula}v−i,j is the j-th highest type among the agents other than i. For the example type profile, the total valuation is 21. The total VCG-based payment equals 15 while the total redistribution equals 12.3247. The efficiency ratio equals 0.6108 (slightly higher than the worst-case ratio {a mathematical formula}αD⁎=0.422).
      </list-item>
      <list-item label="•">
       Optimal randomized burning-based mechanism: One unit is burned with probability 0.4286. That is, the four highest agents win for sure. The fifth highest agent wins with probability 0.5714. Agents pay the VCG-based payments. On top of this, for all i, agent i receives back a redistribution amount that equals {a mathematical formula}0.5714v−i,5, where {a mathematical formula}v−i,5 is the fifth highest type among the agents other than i. For the example type profile, the total valuation is 28.2857. The total VCG-based payment equals 15.4285 while the total redistribution is the same. The efficiency ratio equals 0.9429 (slightly higher than the worst-case ratio {a mathematical formula}αR⁎=0.914).
      </list-item>
      <list-item label="•">
       Optimal partitioning-based mechanism: One agent is chosen uniformly at random. This agent receives one unit for free and is excluded from the auction. The remaining seven agents compete for the remaining four units under the original VCG mechanism. The VCG payments are redistributed to the excluded agent. Redistribution is always {a mathematical formula}100% under this mechanism. For the example type profile, the total valuation is 28.1250. The efficiency ratio equals 0.9375 (slightly higher than the worst-case ratio {a mathematical formula}α1,1⁎=0.925).
      </list-item>
      <list-item label="•">
       Optimal linear mechanism: The four highest agents win for sure. The fifth highest agent wins with probability 0.7506 and the sixth highest agent wins with probability 0.2494. Agents pay the VCG-based payments. On top of this, for all i, agent i receives back a redistribution amount that equals {a mathematical formula}0.3325v−i,5+0.2969v−i,6−0.0356v−i,7, where {a mathematical formula}v−i,j is the j-th highest type among the agents other than i. For the example type profile, the total valuation is 29.7596. The total VCG-based payment equals 14.5012 while the total redistribution equals 14.0024. The efficiency ratio equals 0.9751 (slightly higher than the worst-case ratio {a mathematical formula}α⁎=0.950).
      </list-item>
     </list>
    </section>
    <section label="7">
     <section-title>
      General multi-unit auctions
     </section-title>
     <paragraph>
      In this section, we drop the unit demand restriction. That is, we study multi-unit auctions in which an agent may demand more than one unit.
     </paragraph>
     <paragraph>
      We no longer require that {a mathematical formula}m&lt;n. However, in this section, we only consider cases where {a mathematical formula}m&gt;1 (cases where {a mathematical formula}m=1 reduce to the unit demand setting). An agent's type is no longer a single value, but a vector of length m. We use {a mathematical formula}vi,j to denote agent i's marginal value for winning her j-th unit. That is, if agent i wins k units, then her valuation equals {a mathematical formula}∑j=1kvi,j. A type profile is then an {a mathematical formula}m×n matrix:{a mathematical formula}
     </paragraph>
     <paragraph>
      We use {a mathematical formula}ei ({a mathematical formula}i=1,2,…,mn) to denote the i-th highest element in the type profile. We still use {a mathematical formula}v−i to denote the types of the agents other than i. That is, {a mathematical formula}v−i is an {a mathematical formula}m×(n−1) matrix:{a mathematical formula}
     </paragraph>
     <paragraph>
      We still use R to denote the redistribution function, where {a mathematical formula}R:[0,∞)m(n−1)→R. Agent i's redistribution equals {a mathematical formula}R(v−i). If for all possible type profiles, {a mathematical formula}vi,j≥vi,j+1 for all i and all j ({a mathematical formula}j&lt;m), then we say we are in the setting of multi-unit auctions with nonincreasing marginal values.
     </paragraph>
     <paragraph>
      In general multi-unit auctions, the first-best mechanism is defined as the mechanism that always correctly identifies the allocation that maximizes the agents' total efficiency, without asking for their types, and allocates the units among the agents accordingly at no charge. Again, clearly this mechanism obtains the largest welfare that we could hope for without an external subsidy. We will only use the first-best mechanism as a benchmark, because it is not strategy-proof. Again, our objective is to design strategy-proof complete mechanisms (consisting of both an allocation mechanism and a redistribution rule) that are competitive against the first-best mechanism, in terms of the agents' welfare.
     </paragraph>
     <paragraph>
      The welfare under the first-best mechanism is{a mathematical formula} If the marginal values are nonincreasing, then the welfare under the first-best mechanism is simply {a mathematical formula}∑i=1mei.
     </paragraph>
     <paragraph>
      Our objective is to simultaneously find an allocation mechanism and a redistribution rule, which together form a mechanism with a high competitive ratio. In the unit demand setting, we had a useful set of candidate allocation mechanisms to choose from – the family of linear allocation mechanisms. The following properties made this set useful. First, the linear allocation mechanisms are characterized by n parameters (the {a mathematical formula}ai). Therefore, it is a value optimization problem to find an optimal linear allocation mechanism (under the premise that we know how to design a corresponding redistribution rule). Second, under a linear allocation mechanism, both the mechanism's efficiency and the agents' total payment are linear functions of the agents' types (ordered types, to be more precise). This fact allows us to consider only binary type profiles when designing a redistribution rule for a given linear allocation mechanism, as shown in Theorem 1.
     </paragraph>
     <paragraph>
      As we will show, we can generalize the definition of linear allocation mechanisms to general multi-unit auctions. However, we no longer have a parameterized characterization of the whole linear family, like that in Claim 2. We can also generalize the optimization technique behind Theorem 1, but only when the marginal values are nonincreasing. Therefore, when the marginal values are nonincreasing, for a given parameterized family of linear allocation mechanisms, we are able to simultaneously find both a linear allocation mechanism within the given family, and a redistribution rule, which together maximize the competitive ratio. As we will see, both the burning allocation mechanisms and the partitioning allocation mechanisms, when generalized to multi-unit auctions with nonincreasing marginal values, can be parameterized and are linear. This allows us to use our technique to solve for the most competitive burning/partitioning-based mechanism, when the marginal values are nonincreasing. Actually, it is easy to prove that the {a mathematical formula}(1,0)-partition mechanism (Faltings' mechanism [7]) has the highest competitive ratio among all partitioning-based mechanisms, so we do not actually need our general technique for this. When the marginal values are not necessarily nonincreasing, our technique no longer works, but still, both the burning allocation mechanisms and the partitioning allocation mechanisms are well defined. It turns out that the {a mathematical formula}(1,0)-partition mechanism is still the most competitive partitioning-based mechanism. We conclude with a negative result saying that no burning-based mechanism can be as competitive as the {a mathematical formula}(1,0)-partition mechanism when the marginal values are not necessarily nonincreasing.
     </paragraph>
     <paragraph>
      The key idea behind Theorem 1 is that if the allocation is linear, then when designing the redistribution rule, we can focus on binary type profiles (type profiles in which the {a mathematical formula}vi are binary). The generalized optimization technique in this section builds on the same idea. That is, in multi-unit auctions with nonincreasing marginal values, if the allocation is linear (according to the generalized definition of linearity), then when we design the redistribution rule, we can focus on binary marginal values (type profiles in which the {a mathematical formula}ei are binary). It should be noted that in previous work [17], when designing VCG redistribution mechanisms, also in the setting of multi-unit auctions with nonincreasing marginal values, we have implicitly used an almost identical idea. In that paper, the objective is to design a redistribution rule that maximizes the expected total redistribution, and the non-deficit constraint is the only constraint. In contrast, in this paper, we adopt a prior-free worst-case approach, and besides the non-deficit property, we also require individual rationality. Despite all these differences, the technique in this section can be interpreted as a slight extension of the technique in our earlier work [17]. There, the basic idea is that, if the allocation mechanism is the VCG mechanism, then for the objective and constraint in that paper, when designing the redistribution rule, it is enough to focus on binary marginal values. Here, we show that as long as the allocation mechanism is linear (VCG is a special case of the linear allocation mechanisms), then when designing the redistribution rule for our objective and constraints, we can focus on binary marginal values.
     </paragraph>
     <paragraph>
      We now generalize the definition of linearity to multi-unit auctions with nonincreasing marginal values.
     </paragraph>
     <paragraph label="Definition 3">
      A type profile is tie-free if no two marginal values in it are equal. That is, for any {a mathematical formula}i,i′,j,j′, {a mathematical formula}vi,j=vi′,j′ implies {a mathematical formula}i=i′ and {a mathematical formula}j=j′.
     </paragraph>
     <paragraph label="Definition 4">
      Let V and {a mathematical formula}V′ be two tie-free type profiles. We use the {a mathematical formula}vi,j to denote the elements in V, and we use the {a mathematical formula}vi,j′ to denote the elements in {a mathematical formula}V′. We say V and {a mathematical formula}V′ are order-consistent{sup:16} if for any {a mathematical formula}i1,i2,j1,j2, {a mathematical formula}vi1,j1&gt;vi2,j2 implies {a mathematical formula}vi1,j1′&gt;vi2,j2′.
     </paragraph>
     <paragraph>
      The set of all tie-free type profiles can be divided into a finite number of maximal order consistent classes, where tie-free type profiles that are order consistent with each other all belong to the same class, and tie-free type profiles that are not order consistent belong to different classes.
     </paragraph>
     <paragraph>
      For example, let us consider the case with three agents and two units ({a mathematical formula}n=3 and {a mathematical formula}m=2). In this case, a type profile is a {a mathematical formula}2×3 matrix:{a mathematical formula}
     </paragraph>
     <paragraph>
      An example maximal order consistent class is the set of all type profiles that satisfy {a mathematical formula}v1,1&gt;v2,1&gt;v3,1&gt;v1,2&gt;v2,2&gt;v3,2. Actually, each ordering of the mn marginal values (satisfying the constraint that marginal values of each agent are non-increasing) corresponds to a maximal order consistent class.
     </paragraph>
     <paragraph>
      We use {a mathematical formula}EM(V) to denote the mechanism's efficiency under allocation mechanism M for type profile V. We use {a mathematical formula}PM(V) to denote the agents' total payment under allocation mechanism M for type profile V. (For redistribution functions, we will omit the M superscript for simplicity.)
     </paragraph>
     <paragraph>
      Now we are ready to define the linear allocation mechanisms in multi-unit auctions with nonincreasing marginal values.
     </paragraph>
     <paragraph label="Definition 5">
      In multi-unit auctions with nonincreasing marginal values, an allocation mechanism M is linear if the following conditions are satisfied:
     </paragraph>
     <list>
      <list-item label="•">
       When we restrict our attention to type profiles in a particular maximal order consistent class S, both {a mathematical formula}EM(V) and {a mathematical formula}PM(V) can be written as linear functions of the elements in V, and the coefficients are constants.
      </list-item>
      <list-item label="•">
       {a mathematical formula}EM(V) and {a mathematical formula}PM(V) are continuous in the elements in V.
      </list-item>
      <list-item label="•">
       An agent's payment is always 0 if all her marginal values are 0.
      </list-item>
     </list>
     <paragraph>
      As in the unit demand setting, the family of linear allocation mechanisms is convex: any probability mixture over linear allocation mechanisms is also linear.
     </paragraph>
     <paragraph>
      When the marginal values are nonincreasing, the VCG mechanism is linear. For the earlier example with three agents and two items, we revisit the example maximal order consistent class containing all type profiles that satisfy {a mathematical formula}v1,1&gt;v2,1&gt;v3,1&gt;v1,2&gt;v2,2&gt;v3,2. When we only consider type profiles in this class, the mechanism's efficiency under the VCG mechanism is always {a mathematical formula}v1,1+v2,1 (agents 1 and 2 each win one unit). That is, the mechanism's efficiency is a linear function of the {a mathematical formula}vi,j, with constant coefficients. Similarly, when we only consider type profiles in this class, the agents' total payment under the VCG mechanism is always {a mathematical formula}2v3,1 (agents 1 and 2 each pay {a mathematical formula}v3,1). That is, the agents' total payment is also a linear function of the {a mathematical formula}vi,j, with constant coefficients. The same holds for other maximal consistent classes.
     </paragraph>
     <paragraph>
      Next, we show that, under the VCG mechanism, the mechanism's efficiency and total payment are both continuous in the {a mathematical formula}vi,j. We use {a mathematical formula}maxi⁡(S) to denote the sum of the i highest values in set S. For any type profile, the mechanism's efficiency equals {a mathematical formula}max2⁡({v1,1,v1,2,v2,1,v2,2,v3,1,v3,2}), which is continuous in the {a mathematical formula}vi,j. For any type profile, the agents' total payment equals {a mathematical formula}max2⁡({v1,1,v1,2,v2,1,v2,2})+max2⁡({v1,1,v1,2,v3,1,v3,2})+max2⁡({v2,1,v2,2,v3,1,v3,2})−2max2⁡({v1,1,v1,2,v2,1,v2,2,v3,1,v3,2}), which is also continuous in the {a mathematical formula}vi,j.
     </paragraph>
     <paragraph>
      Finally, it is clear that when an agent's marginal values are all 0, she pays 0 under the VCG mechanism. Therefore, for {a mathematical formula}n=3 and {a mathematical formula}m=2, the VCG mechanism is linear. By similar reasoning, it can be seen that the VCG mechanism is linear for all n and m, when the marginal values are nonincreasing.
     </paragraph>
     <paragraph>
      We can straightforwardly generalize the burning allocation mechanisms and the partitioning allocation mechanisms to general multi-unit auctions. Just as in the unit demand setting, in a general multi-unit auction, under a burning allocation mechanism, we burn a deterministic/random number of units, and then allocate the remaining units according to the VCG mechanism. Again, a burning allocation mechanism is characterized by the {a mathematical formula}pi: with probability {a mathematical formula}pi, we burn {a mathematical formula}m−i units. (If one of the {a mathematical formula}pi is 1, then we are burning a deterministic number of units.) In general multi-unit auctions, under a partitioning allocation mechanism, we partition both the agents and the units into two groups, and run the VCG mechanism on each group. Again, a partitioning allocation mechanism is characterized by the number of agents in the smaller group ({a mathematical formula}n1) and the number of units assigned to the smaller group ({a mathematical formula}m1). Both the burning allocation mechanisms and the partitioning allocation mechanisms are based on VCG mechanisms. The burning allocation mechanisms are mixtures over VCG mechanisms for different numbers of units, and under a partitioning allocation mechanism, for each subgroup of agents that results from partitioning, we use the VCG mechanism to allocate the units assigned to this subgroup. We can use the same technique that we used to prove the linearity of the VCG mechanism to prove that both the burning allocation mechanisms and the partitioning allocation mechanisms (after ignoring payments) are linear in multi-unit auctions with nonincreasing marginal values.
     </paragraph>
     <paragraph>
      Let us consider a parameterized family of linear allocation mechanisms (e.g., the family of burning allocation mechanisms). We denote the parameters by the {a mathematical formula}pi ({a mathematical formula}i=1,2,…,k). The {a mathematical formula}pi may need to satisfy certain constraints for the corresponding mechanism to be feasible. For example, for the family of burning allocation mechanisms, the {a mathematical formula}pi must sum to 1, because they represent probabilities of burning different numbers of units ({a mathematical formula}k=m in this case). The following optimization model solves for the optimal values of the {a mathematical formula}pi, as well as a redistribution function R, so that together, the linear allocation mechanism characterized by the {a mathematical formula}pi and the redistribution function R have the highest competitive ratio. (We use F to denote the first-best mechanism.){a mathematical formula}
     </paragraph>
     <paragraph>
      Once again, this is a functional optimization problem, which appears difficult to solve. We use the vector {a mathematical formula}(x1,x2,…,xn−1) to denote the matrix {a mathematical formula}v−i in which the j-th column contains {a mathematical formula}xj ones (the {a mathematical formula}xi are integers). For example, {a mathematical formula}[100110] is denoted by the vector {a mathematical formula}(2,1,0). We use {a mathematical formula}r(x1,x2,…,xn−1) to denote the redistribution received by an agent when the other agents' types are {a mathematical formula}(x1,x2,…,xn−1). Just as in the unit demand setting, if we only consider binary marginal values, then the redistribution function R can be represented by the {a mathematical formula}r(⋅), where {a mathematical formula}0≤xi≤m. In the original functional optimization problem, we are optimizing over the {a mathematical formula}pi and the redistribution function R. When we only consider binary marginal values, we are optimizing over the {a mathematical formula}pi and the {a mathematical formula}r(⋅). Hence, we have a value optimization problem. Under some conditions, this optimization problem corresponds to a linear program (e.g., when we focus on the family of burning allocation mechanisms).{a mathematical formula}
     </paragraph>
     <paragraph>
      We use the {a mathematical formula}pi⁎, the {a mathematical formula}r⁎(x1,x2,…,xn), and {a mathematical formula}α⁎ to denote an optimal solution of the above value optimization program. We always have that {a mathematical formula}r⁎(0,0,…,0)=0. (For the type profile in which all the marginal values are 0, individual rationality implies {a mathematical formula}r⁎(0,0,…,0)≥0, and the non-deficit constraint implies {a mathematical formula}r⁎(0,0,…,0)≤0.) Again, {a mathematical formula}α⁎, the optimal objective value of the above linear program, must be greater than or equal to the optimal objective value of the original functional optimization problem. That is, {a mathematical formula}α⁎ is an upper bound on the competitive ratio of any complete mechanism whose allocation part is within the family under consideration. It turns out that we can achieve this upper bound. In what follows, we construct a complete mechanism whose allocation part is within the family under consideration, and prove that this mechanism has a competitive ratio of {a mathematical formula}α⁎. Hence, the constructed mechanism is an optimal solution to the original functional optimization problem.
     </paragraph>
     <paragraph>
      We define function {a mathematical formula}R⁎ as follows:{a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}e−i,j is the j-th highest element in {a mathematical formula}v−i. {a mathematical formula}T−i,j is obtained from {a mathematical formula}v−i by replacing the j highest marginal values in {a mathematical formula}v−i by 1, and by replacing the remaining marginal values by 0.{sup:17}
     </paragraph>
     <paragraph>
      {a mathematical formula}R⁎ is defined in such a way that when {a mathematical formula}v−i is binary, {a mathematical formula}R⁎(v−i) matches {a mathematical formula}r⁎(v−i). Therefore, {a mathematical formula}R⁎ can be interpreted as a linear interpolation of the {a mathematical formula}r⁎(⋅).
     </paragraph>
     <paragraph>
      {a mathematical formula}R⁎, as defined above, is continuous in the elements in {a mathematical formula}v−i, for the following reasons. If we perturb an element x in {a mathematical formula}v−i by δ, then some of the {a mathematical formula}e−i,j are perturbed. Let {a mathematical formula}k1 be the smallest number for which {a mathematical formula}e−i,k1 is perturbed. Let {a mathematical formula}k2 be the largest number for which {a mathematical formula}e−i,k2 is perturbed. We must have that before the perturbation, for all {a mathematical formula}k1≤j≤k2, {a mathematical formula}e−i,j differs from x by at most δ, and after the perturbation, for all {a mathematical formula}k1≤j≤k2, {a mathematical formula}e−i,j differs from x by at most δ. We also have that {a mathematical formula}T−i,j is unchanged for {a mathematical formula}j&lt;k1 and {a mathematical formula}j≥k2. Therefore, before the perturbation, {a mathematical formula}R⁎(v−i) is close to {a mathematical formula}∑j=1k1−1(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j+∑j=k1k2(r⁎(T−i,j)−r⁎(T−i,j−1))x+∑j=k2+1n(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j=∑j=1k1−1(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j+r⁎(T−i,k2)x−r⁎(T−i,k1−1)x+∑j=k2+1n(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j. (The difference between {a mathematical formula}R⁎(v−i) and this expression is bounded above by a multiple of δ.) It should be noted that the value of this expression is unchanged after the perturbation, because {a mathematical formula}T−i,j is unchanged for {a mathematical formula}j&lt;k1 and {a mathematical formula}j≥k2, and {a mathematical formula}e−i,j is unchanged for {a mathematical formula}j&lt;k1 and {a mathematical formula}j&gt;k2. After the perturbation, with the new values of the {a mathematical formula}T−i,j and the {a mathematical formula}e−i,j, we still have that {a mathematical formula}R⁎(v−i) is close to {a mathematical formula}∑j=1k1−1(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j+r⁎(T−i,k2)x−r⁎(T−i,k1−1)x+∑j=k2+1n(r⁎(T−i,j)−r⁎(T−i,j−1))e−i,j. (The difference between {a mathematical formula}R⁎(v−i) after the perturbation and this expression is also bounded above by a multiple of δ.) That is, with or without the perturbation, {a mathematical formula}R⁎(v−i) is close to the same expression (which has the same value with or without the perturbation). Therefore, {a mathematical formula}R⁎, as defined above, is continuous in the elements in {a mathematical formula}v−i.
     </paragraph>
     <paragraph label="Theorem 2">
      Within the family of allocation mechanisms that we consider, let{a mathematical formula}M(p1⁎,p2⁎,…,pk⁎)denote the allocation mechanism characterized by the{a mathematical formula}pi⁎.{a mathematical formula}(M(p1⁎,p2⁎,…,pk⁎),R⁎)is{a mathematical formula}α⁎-competitive. That is, it is optimal among all complete mechanisms whose allocation part is within the family under consideration.
     </paragraph>
     <paragraph>
      Before proving the theorem, we give the following lemma, which is similar to Lemma 1.
     </paragraph>
     <paragraph label="Lemma 2">
      Let the{a mathematical formula}cibe constants. The following two systems of inequalities are equivalent:
     </paragraph>
     <list>
      <list-item label="(a)">
       {a mathematical formula}c1x1+c2x2+…+csxs≥0for all{a mathematical formula}x1&gt;x2&gt;…&gt;xs&gt;0.
      </list-item>
      <list-item label="(b)">
       For any{a mathematical formula}δ&gt;0, there exists{a mathematical formula}ϵ&gt;0, so that{a mathematical formula}c1x1+c2x2+…+csxs&gt;−δfor all{a mathematical formula}(x1,x2,…,xs)∈⋃k=1,2,…,s{(x1,x2,…,xs)|1&gt;x1&gt;x2&gt;…&gt;xs&gt;0,xk&gt;1−ϵ,xk+1&lt;ϵ}.
      </list-item>
     </list>
     <paragraph label="Proof">
      (a) ⇒ (b) is trivial. We now prove (b) ⇒ (a). By Lemma 1, we only need to prove (b) implies the following: {a mathematical formula}c1x1+c2x2+…+csxs≥0 for all {a mathematical formula}x1≥x2≥…≥xs, where the {a mathematical formula}xi are binary. For any δ and ϵ, if we have that {a mathematical formula}c1x1+c2x2+…+csxs&gt;−δ for all {a mathematical formula}(x1,x2,…,xs)∈⋃k=1,2,…,s{(x1,x2,…,xs)|1&gt;x1&gt;x2&gt;…&gt;xs&gt;0,xk&gt;1−ϵ,xk+1&lt;ϵ}, then we have {a mathematical formula}c1x1+c2x2+…+csxs≥−δ for all {a mathematical formula}(x1,x2,…,xs)∈⋃k=1,2,…,s{(x1,x2,…,xs)|1≥x1≥x2≥…≥xs≥0,xk≥1−ϵ,xk+1≤ϵ}. This implies that {a mathematical formula}c1x1+c2x2+…+csxs≥0 for all {a mathematical formula}x1≥x2≥…≥xs, where the {a mathematical formula}xi are binary.  □
     </paragraph>
     <paragraph>
      The above lemma is basically a variant of Lemma 1, where part (b) has been changed slightly (from binary to almost binary and from nonnegative to almost nonnegative). As we mentioned earlier, the technique proposed in this section is a slight generalization of the result in [17]. Therefore, we only present the following proof sketch.
     </paragraph>
     <paragraph label="Proof">
      We only need to prove that {a mathematical formula}α⁎, the {a mathematical formula}pi⁎, and the function {a mathematical formula}R⁎ form a feasible solution to the original functional optimization problem. If they form a feasible solution, then {a mathematical formula}(M(p1⁎,p2⁎,…,pk⁎),R⁎) is {a mathematical formula}α⁎-competitive, implying that it is optimal. That is, we need to prove that the constructed mechanism satisfies individual rationality, the non-deficit constraint, and the competitive ratio constraint (it is obvious that the constraints involving only the {a mathematical formula}pi hold).According to the definition of the linear allocation mechanisms, both {a mathematical formula}EM(V) and {a mathematical formula}PM(V) are continuous in the elements in V. We have also proved that the constructed {a mathematical formula}R⁎ is continuous in the elements in V. We now consider the constraints in the optimization model that are related to the redistribution rule. The individual rationality constraint is that for all type profiles V in which the elements are the {a mathematical formula}vi,j, we must have {a mathematical formula}R⁎(v−i)≥0 for all i and all {a mathematical formula}v−i. Because the set of tie-free type profiles is dense in the set of all type profiles, it suffices to prove that for all tie-free type profiles V in which the elements are the {a mathematical formula}vi,j, we must have {a mathematical formula}R⁎(v−i)≥0 for all i and all {a mathematical formula}v−i. Let V be an arbitrary tie-free type profile. Let S be the maximal order consistent class containing V. When we focus only on type profiles in S, for any type profile/matrix V, the i-th highest element is always in a fixed position {a mathematical formula}(j,k). To prove that all type profiles in S satisfy {a mathematical formula}R⁎(v−i)≥0, we need to prove a linear inequality in the form of part (a) in Lemma 2, because {a mathematical formula}R⁎ is linear in the {a mathematical formula}ei, and the {a mathematical formula}ei can take any values as long as we have {a mathematical formula}e1&gt;e2&gt;…&gt;emn&gt;0. When the type profiles are binary, the individual rationality constraint is satisfied, by the definition of {a mathematical formula}R⁎. Because {a mathematical formula}R⁎ is continuous, when we perturb a binary type profile, the individual rationality constraint can at most be violated by a small amount. It follows that the aforementioned linear inequality in the {a mathematical formula}ei can at most be violated by a small amount if the {a mathematical formula}ei are close to binary. This gives us part (b) in Lemma 2. Therefore, we have that individual rationality is satisfied for all tie-free type profiles (and hence, as we argued before, for all profiles) in an arbitrary maximal order consistent class. Similarly, we can prove that the non-deficit constraint and the competitive ratio constraint are satisfied for all type profiles.  □
     </paragraph>
     <paragraph>
      Based on the technique proposed above, we can solve for an optimal burning-based mechanism. For {a mathematical formula}n=5 and different m, the following table presents the optimal competitive ratios of burning-based mechanisms in multi-unit auctions with nonincreasing marginal values.{a mathematical formula}
     </paragraph>
     <paragraph>
      As a comparison, for the unit demand setting, when {a mathematical formula}n=5 and {a mathematical formula}m=1, the competitive ratio of the optimal randomized burning-based mechanism is also 0.733. This is not surprising, because when there is only one item, the two settings are the same. When {a mathematical formula}n=5 and {a mathematical formula}m=3, for the unit demand setting, the competitive ratio of optimal randomized burning-based mechanism is 0.833 (higher than the value of 0.643 for the multi-demand setting). For the cases where {a mathematical formula}n=5 and {a mathematical formula}m≥5, in the unit demand setting we naturally obtain a competitive ratio of 1 because we can satisfy all agents trivially.
     </paragraph>
     <paragraph label="Example 7">
      Similarly, agent 2's redistribution and agent 3's redistribution equal 0.8 and 2, respectively.The total redistribution is then 3.6. The efficiency ratio equals {a mathematical formula}10−6.4+3.611=0.6545. The worst-case ratio is only 0.3. As a comparison, for {a mathematical formula}n=3 and {a mathematical formula}m=2, in the unit demand setting, the optimal randomized burning-based mechanism has a worst-case ratio of 0.75.
     </paragraph>
     <paragraph>
      We can also use the proposed technique to solve for the optimal partitioning-based mechanism. Actually, it turns out that this is not necessary, as it is easy to prove that the {a mathematical formula}(1,0)-partition mechanism is the most competitive partitioning-based mechanism, whether the marginal values are assumed to be nonincreasing or not.
     </paragraph>
     <paragraph label="Theorem 3">
      In general multi-unit auctions, the{a mathematical formula}(1,0)-partition mechanism is the most competitive partitioning-based mechanism, whether the marginal values are assumed to be nonincreasing or not.
     </paragraph>
     <paragraph label="Example 8">
      For the type profile in Example 7, if we run the {a mathematical formula}(1,0)-partition mechanism, then the valuation equals {a mathematical formula}7+11+113=9.6667. All payments are redistributed. The efficiency ratio equals {a mathematical formula}9.666711=0.8788 (higher than the worst-case ratio {a mathematical formula}n−1n=0.6667).
     </paragraph>
     <paragraph>
      Finally, we conclude with a negative result saying that no burning-based mechanism can be more competitive than the {a mathematical formula}(1,0)-partition mechanism when the marginal values are not necessarily nonincreasing.
     </paragraph>
     <paragraph label="Claim 8">
      In multi-unit auctions, if there are at least two agents,{sup:18}and the marginal values are not necessarily nonincreasing, then no burning-based mechanism's competitive ratio can be strictly more than{a mathematical formula}n−1n.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Future research
     </section-title>
     <paragraph>
      Future research on maximizing the agents' welfare under the constraint of strategy-proofness can take a number of directions. Are there other families of inefficient mechanisms that result in a high welfare for the agents? Among what more general classes of mechanisms are the mechanisms proposed in this paper optimal? Can we generalize some of these results to wider settings, for example, settings with heterogeneous objects? What happens if we change the objective, for example, if we have a prior distribution over type profiles and we wish to maximize expected welfare?
     </paragraph>
     <paragraph>
      Finally, we have assumed in this paper that random bits are not chosen adversarially, that is, the worst-case adversary controls the agents' valuations but not our random choices. If the adversary also controls our random choices (which would correspond to a different notion of worst-case optimality), then it never hurts to use a deterministic mechanism. To illustrate how this affects our results, let us consider Example Mechanism 2 of Subsection 5.2 (the Faltings mechanism), in which we (uniformly) randomly choose one agent to be excluded from the auction and assign this agent zero units. This mechanism is competitive in the sense of this paper. (An agent is excluded with probability {a mathematical formula}1n, hence the competitive ratio is {a mathematical formula}n−1n.) However, if we use the alternative notion of worst-case optimality where the adversary controls the random choices, then the agent with the highest valuation will always be excluded, so that the mechanism is not competitive. It remains to be seen what we can do for this alternative notion of worst-case optimality. There has already been work in this direction. de Clippel et al. [6] study deterministic inefficient mechanisms that are competitive in multi-unit auctions with unit demand. Specifically, their mechanisms are based on burning deterministic numbers of units. The difference between their mechanisms and the deterministic burning-based mechanisms studied in this paper is that in their mechanisms, different numbers of units may be burned for different type profiles, while in our mechanisms, we only consider burning a fixed number of units for all type profiles.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <paragraph label="Proof of Claim 2">
      {sup:19} Let us consider a specific strategy-proof linear allocation mechanism, whose allocation vector is {a mathematical formula}(a1,a2,…,an). Let us reason from the perspective of a particular agent Alice. (We use “agent Alice” instead of “agent i” because agent i specifically refers to the agent whose type is the i-th highest.) We use {a mathematical formula}xi ({a mathematical formula}i=1,2,…,n−1) to denote the i-th highest type among the agents other than Alice. We consider a specific type profile in which the {a mathematical formula}xi are all distinct, and {a mathematical formula}xn−1&gt;0.First of all, we observe that (holding the types of the other agents fixed), Alice's payment depends only on her rank. This is because if there were two types that resulted in the same rank but a different payment, then if she had the type that resulted in the higher payment, she would have an incentive to report the one that results in the lower payment instead, because, by assumption, the allocation will be the same. In particular, if she is ranked n-th, she will pay 0, because an agent bidding 0 always pays 0.We use {a mathematical formula}zi to denote Alice's payment when she is the i-th highest agent (so {a mathematical formula}zn=0). Since we are considering a strategy-proof mechanism, for any {a mathematical formula}1≤i≤n−1, we have the following:{a mathematical formula}{a mathematical formula}Here, ϵ is a sufficiently small positive value. The first inequality says that when Alice's type is just below {a mathematical formula}xi, she prefers winning with probability {a mathematical formula}ai+1 and paying {a mathematical formula}zi+1 (reporting truthfully) to winning with probability {a mathematical formula}ai and paying {a mathematical formula}zi (misreporting to be ranked i-th). The second inequality says that this is reversed when Alice's type is just above {a mathematical formula}xi. It is straightforward to verify that if {a mathematical formula}ai+1&gt;ai, then the above two inequalities cannot be simultaneously satisfied. That is, for a linear allocation mechanism to be strategy-proof, we must have that {a mathematical formula}ai≥ai+1 for all {a mathematical formula}1≤i≤n−1. That is, every strategy-proof linear allocation mechanism corresponds to an allocation vector in {a mathematical formula}{(a1,a2,…,an)|1≥a1≥a2≥…≥an≥0,∑i=1nai≤m}.We now consider Alice's payment for an arbitrary type profile. We still use {a mathematical formula}xi ({a mathematical formula}i=1,2,…,n−1) to denote the i-th highest type from the agents other than Alice. We no longer require the {a mathematical formula}xi to be distinct or {a mathematical formula}xn−1&gt;0. We still use {a mathematical formula}zi to denote Alice's payment when she is the i-th highest agent. We know that {a mathematical formula}zn=0. When Alice's type is exactly {a mathematical formula}xn−1, she should be indifferent between being the {a mathematical formula}(n−1)-th highest agent and the n-th highest agent. That is, we have {a mathematical formula}an−1xn−1−zn−1=anxn−1, or equivalently, {a mathematical formula}zn−1=(an−1−an)xn−1. When Alice's type is exactly {a mathematical formula}xn−2, she should be indifferent between being the {a mathematical formula}(n−2)-th highest agent and the {a mathematical formula}(n−1)-th highest agent. That is, we have {a mathematical formula}an−2xn−2−zn−2=an−1xn−2−zn−1. Using the previous expression for {a mathematical formula}zn−1, we have {a mathematical formula}zn−2=(an−2−an−1)xn−2+(an−1−an)xn−1. Continuing this reasoning, we obtain {a mathematical formula}zi=∑j=in−1(aj−aj+1)xj. Since we are considering an arbitrary agent and an arbitrary type profile, we have that the {a mathematical formula}ai characterize the agents' payments, and thus characterize the entire mechanism (because the {a mathematical formula}ai also characterize the allocation). When the {a mathematical formula}ai are nonincreasing and sum to at most m, the linear allocation mechanism characterized by the {a mathematical formula}ai is exactly the maximal-in-range [27] allocation mechanism under which the allowable allocations are those in which the agents win with probabilities {a mathematical formula}a1,a2,…,an. Moreover, the payments described above are exactly the corresponding VCG-based payments. We know that maximal-in-range allocations combined with VCG-based payments result in strategy-proof mechanisms. Therefore, we have that each allocation vector in {a mathematical formula}{(a1,a2,…,an)|1≥a1≥a2≥…≥an≥0,∑i=1nai≤m} corresponds to a strategy-proof linear allocation mechanism.  □
     </paragraph>
     <paragraph label="Proof of Claim 3">
      We already know that WCO has competitive ratio {a mathematical formula}1−(n−1m)∑j=mn−1(n−1j). Hence, we only need to show that the other mechanism proposed in the claim is feasible and has competitive ratio {a mathematical formula}mn−nmn−m, for the values of n and m for which this mechanism outperforms WCO.If {a mathematical formula}m=1, then {a mathematical formula}mn−nmn−m=0, which cannot be greater than the competitive ratio of WCO. So we only need to consider {a mathematical formula}m&gt;1. We first prove that the mechanism is feasible. That is, it is individually rational and satisfies the non-deficit property. Individual rationality is satisfied because the redistribution is always nonnegative. For any type profile, the total VCG payment is {a mathematical formula}mvm+1 when nothing is burned, and it is {a mathematical formula}(m−1)vm when one unit is burned. In expectation, the total payment collected by the allocation mechanism is {a mathematical formula}n−mn−1(m−1)vm+(1−n−mn−1)mvm+1=m−1n−1(mvm+1+(n−m)vm). For the agents reporting {a mathematical formula}v1,…,vm, the redistribution received is {a mathematical formula}m−1n−1vm+1. For the other agents, the redistribution received is {a mathematical formula}m−1n−1vm. Therefore, the total redistribution equals the total payment, so the non-deficit constraint is satisfied. We conclude that the mechanism is feasible.Now we show that the mechanism has competitive ratio {a mathematical formula}mn−nmn−m. With probability {a mathematical formula}n−mn−1, the total efficiency is {a mathematical formula}∑i=1m−1vi (one unit is burned). When nothing is burned, the total efficiency is {a mathematical formula}∑i=1mvi. In expectation, the total efficiency is {a mathematical formula}n−mn−1∑i=1m−1vi+(1−n−mn−1)∑i=1mvi. This is greater than or equal to {a mathematical formula}n−mn−1m−1m∑i=1mvi+(1−n−mn−1)∑i=1mvi=mn−nmn−m∑i=1mvi (we have equality when all the {a mathematical formula}vi are equal). Since the total payment equals the total redistribution, efficiency is equal to welfare, so we conclude that we obtain the competitive ratio {a mathematical formula}mn−nmn−m.  □
     </paragraph>
     <paragraph label="Proof of Claim 5">
      For the type profile in which m agents report 1 and the remaining agents report 0, the first-best mechanism achieves an efficiency of m. Hence, {a mathematical formula}UMn1,m1(m)m is an upper bound on {a mathematical formula}αn1,m1⁎.We now show that {a mathematical formula}UMn1,m1(m)m is equal to the second expression in the claim; then, we will show that {a mathematical formula}Mn1,m1 does in fact attain this competitive ratio. In the {a mathematical formula}(n1,m1)-partition mechanism, {a mathematical formula}n1 agents are randomly picked to form one group, and the remaining {a mathematical formula}n−n1 agents form a second group. If m agents report 1 and the remaining agents report 0, then the probability of having x agents that report 1 in the group of size {a mathematical formula}n1 is {a mathematical formula}(n1x)(n−n1m−x)(nm). The corresponding total welfare is {a mathematical formula}(min⁡{x,m1}+min⁡{m−x,m−m1}). The set of possible values of x is X. It follows that {a mathematical formula}UMn1,m1(m) is equal to {a mathematical formula}∑x∈X(n1x)(n−n1m−x)(min⁡{x,m1}+min⁡{m−x,m−m1})(nm).All that is left to show is that {a mathematical formula}Mn1,m1 does in fact attain this competitive ratio. Let us consider the following allocation mechanism, which is never better than {a mathematical formula}Mn1,m1:
      <list>
       Pick {a mathematical formula}n1 agents to form one group, uniformly at random. The other {a mathematical formula}n−n1 agents form the second group.Remove the agents with the lowest {a mathematical formula}n−m types.For the first group, if there are more than {a mathematical formula}m1 agents left, allocate {a mathematical formula}m1 units uniformly at random among the remaining agents in group one. Otherwise, allocate one unit to every remaining agent in group one.For the second group, if there are more than {a mathematical formula}m−m1 agents left, allocate {a mathematical formula}m−m1 units uniformly at random among the remaining agents in group two. Otherwise, allocate one unit to every remaining agent in group two.For any type profile, the above mechanism results in (weakly) lower efficiency than the
      </list>
      <paragraph>
       {a mathematical formula}(n1,m1)-partition mechanism, because in the partitioning-based mechanism, the units are assigned efficiently within each group, and in the modified mechanism they are not because of agent removal and random assignment.Under the modified mechanism, only the agents reporting {a mathematical formula}v1,…,vm possibly win any units, and the probability of winning is the same for each of them. For the type profile in which m agents report 1 and the remaining agents report 0, the modified mechanism results in the same efficiency as the partitioning-based mechanism. Therefore, because in this case, a winning agent's utility is 1, the expected number of winners under the modified mechanism is {a mathematical formula}UMn1,m1(m). But this number must be the same for all type profiles. So, using the fact that each of the top m agents is equally likely to win, for a general type profile, the expected efficiency under the modified mechanism is {a mathematical formula}UMn1,m1(m)m∑i=1mvi; and we know that this is (weakly) lower than the expected efficiency under the {a mathematical formula}(n1,m1)-partition mechanism. Hence, the {a mathematical formula}(n1,m1)-partition mechanism has a competitive ratio of at least {a mathematical formula}UMn1,m1(m)m. We have already proved that {a mathematical formula}UMn1,m1(m)m is an upper bound on {a mathematical formula}αn1,m1⁎, so this expression must be exactly equal to the competitive ratio.  □
      </paragraph>
     </paragraph>
     <paragraph label="Proof of Theorem 3">
      Let us consider the type profile in which agent 1's marginal value is 1 for every additional unit, and all the other agents have only marginal values of 0. For this type profile, under the {a mathematical formula}(n1,m1)-partition mechanism, the agents' total welfare equals {a mathematical formula}n1nm1+n−n1n(m−m1). (With probability {a mathematical formula}n1n, agent 1 is assigned to the group of size {a mathematical formula}n1, in which case the welfare equals {a mathematical formula}m1. With probability {a mathematical formula}n−n1n, agent 1 is assigned to the group of size {a mathematical formula}n−n1, in which case the welfare equals {a mathematical formula}m−m1.) This expression is at most {a mathematical formula}n−1nm for any {a mathematical formula}n1 and {a mathematical formula}m1. The agents' total welfare under the first-best mechanism is simply m. Therefore, whether the marginal values are assumed to be nonincreasing or not, any partitioning-based mechanism is at most {a mathematical formula}n−1n-competitive.Given any type profile, let S denote the set of agents that win something under the first-best mechanism. If we apply the {a mathematical formula}(1,0)-partition mechanism, then every agent is excluded with probability {a mathematical formula}1n. Suppose that, when a winner is excluded, we do not change the allocation, but simply throw away the units that the excluded agent would have won; the resulting welfare is exactly {a mathematical formula}n−1n times the welfare under the first-best mechanism; moreover, it is always smaller than or equal to the agents' welfare under the {a mathematical formula}(1,0)-partition mechanism (which allocates efficiently among the non-excluded bidders). Therefore, the {a mathematical formula}(1,0)-partition mechanism is at least {a mathematical formula}n−1n-competitive, which means that it is optimal among all partitioning-based mechanisms, whether the marginal values are assumed to be nonincreasing or not.  □
     </paragraph>
     <paragraph label="Proof of Claim 8">
      To ensure individual rationality, any agent's redistribution should be nonnegative. To ensure the non-deficit property, an agent's redistribution should never exceed the minimal total payment that can result when we hold the other agents' types fixed and change her own type. Otherwise, when her type is one that minimizes the total payment, the total redistribution, which is at least the redistribution received by this agent, is more than the total payment.{sup:20}We first prove the result for the case of two agents. Let M be a burning-based mechanism under which {a mathematical formula}m−i units are burned with probability {a mathematical formula}pi. Let us consider the type profile in which agent 1's marginal values are {a mathematical formula}(0,0,…,0,1). That is, agent 1's valuation equals 1 if she wins all the units, and 0 otherwise. Let agent 2's type be the same. For this type profile, with probability {a mathematical formula}pm, the efficiency equals 1, and the payment equals 1. With probability {a mathematical formula}1−pm, the efficiency equals 0, and the payment equals 0. That is, the expected efficiency is {a mathematical formula}pm, and we try to redistribute as much as possible from the expected payment {a mathematical formula}pm. The welfare is maximized when {a mathematical formula}pm=1 (nothing is burned). That is, among all burning-based mechanisms, nothing can outperform the VCG mechanism with redistribution on this profile. However, when there are only two agents, neither agent can collect any redistribution: for either agent, the minimal total payment is always 0 (when we fix the other agent's type and change her own type), because if her type is {a mathematical formula}(0,0,…,0), then the total payment is 0. Therefore, no burning-based mechanism can result in greater welfare on this profile than the VCG mechanism itself. However, under the VCG mechanism, the agents' total welfare is 0 for this type profile. Thus, when there are two agents, no burning-based mechanism can be competitive at all.Next, we prove the result for the case of at least three agents. Let M be a burning-based mechanism under which {a mathematical formula}m−i units are burned with probability {a mathematical formula}pi, and suppose that its competitive ratio is strictly more than {a mathematical formula}n−1n. Let us consider the type profile in which agent 1's marginal values are {a mathematical formula}(0,0,…,0,1). That is, agent 1's valuation equals 1 if she wins all the units, and 0 otherwise. Let all the other agents have only marginal values of 0. That is, the other agents are not interested in any units. For this type profile, it is clear that if {a mathematical formula}pm≤n−1n, then the mechanism is at most {a mathematical formula}n−1n-competitive. That is, we must have {a mathematical formula}pm&gt;n−1n. Now, let us consider another type profile in which agent 1's type is the same, but we let agent 2's marginal values be {a mathematical formula}(0,0,…,0,1−ϵ,0), where ϵ is a very small positive value. That is, agent 2's valuation equals {a mathematical formula}1−ϵ if she wins at least {a mathematical formula}m−1 units. Let all the other agents' marginal values all be 0. For this type profile, burning more than one unit results in a welfare of 0, and as we have proved, the probability of burning one unit is less than {a mathematical formula}1n. If agent 1's type were {a mathematical formula}(0,0,…,0) instead, then the total payment would be 0 under M. (The total payment would be 0 both under the VCG mechanism, and under the VCG mechanism with one unit burned.) It follows that agent 1's redistribution is 0 for the type profile considered. Similarly, agent 2's redistribution is also 0. For any other agent, if we were to replace her type by {a mathematical formula}(1+ϵ,0,0,…,0), then the total payment under the VCG mechanism would be ϵ, and the total payment under the VCG mechanism with one unit burned would be {a mathematical formula}1−ϵ. Since {a mathematical formula}pm&gt;n−1n, the expected total payment would be at most {a mathematical formula}n−1nϵ+1n(1−ϵ)=n−2nϵ+1n. Therefore, each agent other than agent 1 and 2 at most receives a redistribution of {a mathematical formula}n−2nϵ+1n. Thus, the total redistribution is at most {a mathematical formula}(n−2)2nϵ+n−2n. The total efficiency for this type profile is at most 1. The VCG payment for this type profile is {a mathematical formula}1−ϵ. The VCG payment with one unit burned is 0. Therefore, the total payment is at least {a mathematical formula}n−1n−n−1nϵ. So, the welfare is at most {a mathematical formula}1−n−1n+n−1nϵ+(n−2)2nϵ+n−2n=n−1n+(n−2)2+n−1nϵ. The welfare under the first-best mechanism is 1. Since ϵ can be arbitrarily small, the burning-based mechanism's competitive ratio cannot be strictly more than {a mathematical formula}n−1n, and we have the desired contradiction.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>