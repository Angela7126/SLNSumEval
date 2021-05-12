<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Distributed fair allocation of indivisible goods.
   </title>
   <abstract>
    Distributed mechanisms for allocating indivisible goods are mechanisms lacking central control, in which agents can locally agree on deals to exchange some of the goods in their possession. We study convergence properties for such distributed mechanisms when used as fair division procedures. Specifically, we identify sets of assumptions under which any sequence of deals meeting certain conditions will converge to a proportionally fair allocation and to an envy-free allocation, respectively. We also introduce an extension of the basic framework where agents are vertices of a graph representing a social network that constrains which agents can interact with which other agents, and we prove a similar convergence result for envy-freeness in this context. Finally, when not all assumptions guaranteeing envy-freeness are satisfied, we may want to minimise the degree of envy exhibited by an outcome. To this end, we introduce a generic framework for measuring the degree of envy in a society and establish the computational complexity of checking whether a given scenario allows for a deal that is beneficial to every agent involved and that will reduce overall envy.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The problem of fairly dividing a number of goods between several agents has been studied in a variety of settings. First, we may distinguish allocation problems for divisible and for indivisible goods. The literature on cake cutting, for instance, is concerned with divisible goods [3], [4], [5]. As for indivisible goods, we can distinguish assignment problems[6], where each agent can consume at most a single good, from more general settings where each agent may receive a set (or bundle) of goods [7], [8], [9]. If agents can receive sets of goods, and if their preferences over the goods are not additively separable, then fair division becomes a combinatorial optimisation problem. We may also distinguish whether or not to allow for monetary side payments to be added to the bundles allocated to the agents, and if so we have to decide what assumptions to make regarding the agents' appreciation of money (such as quasi-linearity, for instance). Finally, there are many different ways in which to interpret the term fairness itself [10]. For instance, we may be interested in equitable allocations, in proportional allocations, or in allocations where agents do not envy each other. In this paper, we adopt a model where sets of indivisible goods need to be allocated to a number of agents; agents express their preferences in terms of valuation functions over sets of goods; and side payments are possible and agents have quasi-linear preferences regarding money. We focus on two fairness criteria: first, we look for solutions that are proportionally fair (i.e., where the utility of each of the n agents is at least 1/nth of the value she ascribes to the full set of goods) and, second, we look for envy-free solutions (where no agent envies any of the other agents). (These criteria will get formally defined in Sections 3 and 4.)
     </paragraph>
     <paragraph>
      While fair division is a problem originating in Economics and Political Science, with a number of important contributions by mathematicians, it eventually also started to attract the attention of researchers in Artificial Intelligence, Multiagent Systems, and Theoretical Computer Science [11], [12], [13], [14], [15], [16], [9], [5]. The reason for this trend is twofold: first, concepts from fair division are immediately relevant to these disciplines (e.g., finding acceptable agreements in a multiagent system) and, second, the tools and techniques of these disciplines can shed new light on previously unexplored aspects of fair division (e.g., by applying ideas from complexity theory).
     </paragraph>
     <paragraph>
      There is large variety concerning the procedures that have been proposed to address fair division problems. Some work emphasises that such procedures should be simple enough to be executable by humans. Others have concentrated on devising computationally efficient algorithms. Our own approach is to use a distributed mechanism in which agents can locally agree on deals to exchange some of the goods in their possession. In this approach, we initially choose a random allocation of goods to agents and then let the agents negotiate freely to, hopefully, find a superior allocation. Each agent's preferences are defined using a (not necessarily additive) valuation function. Agents agree on a sequence of deals to exchange goods, which may be combined with monetary side payments. Once negotiation is underway, there is no central control regulating the process and agents are assumed to make deals according to their own preferences. Standard cake-cutting procedures that have been proposed for the fair partitioning of a single divisible good [3], for instance, are not distributed in this sense. While some of them, like, e.g., the well-known Banach–Knaster “last diminisher procedure”, do not require a referee to execute the procedure, they nevertheless proceed according to a fixed (global) protocol specifying which agent has to perform which type of action at any given time. The same is true for the “descending demand procedure” of Herreiner and Puppe [17], a procedure for finding equitable allocations of indivisible goods.
     </paragraph>
     <paragraph>
      The kind of distributed approach followed here has been studied by several authors [18], [13], [19], [20], [21]. It is particularly attractive for large systems of autonomous software agents that need to negotiate an allocation of resources or agree on a distribution of tasks amongst themselves. Being able to distribute the computation of an optimal allocation of goods over the agents is useful in many applications where no central authority can be relied upon to eventually decide on the allocation. This may, for instance, be the case in view of computational limitations of a potential centre, or in view of its trustworthiness. In such a context the use of combinatorial auctions or similar mechanisms [22], which in principle could be employed to find an optimal allocation of indivisible goods, may be considered problematic. The same argument has also been made by Netzer et al. [23], who proposed a framework for finding fair allocations of goods based on distributed constraint optimisation. But even when we give up central control of the optimisation algorithm, as system designers, we still would want to try to set up the system in such way that it guarantees certain desirable properties, although now without directly interfering into the process of negotiation.
     </paragraph>
     <paragraph>
      In this paper we study convergence properties for distributed allocation mechanisms when used as fair division procedures. Specifically, we identify sets of assumptions under which any sequence of deals meeting certain conditions can be shown to converge to a proportionally fair allocation and to an envy-free allocation, respectively. We also introduce an extension of the basic framework where agents are vertices of a graph (which we might think of as representing a social network) limiting which agents can interact with each other. The concept of envy-freeness is very naturally extended to such a setting: an agent will not envy another agent if they either believe that their own bundle is more valuable or if they cannot see that other agent, because there is no edge between them in the network. This allows us to prove a similar convergence result for envy-freeness in the context of fair division on a graph. Finally, when not all assumptions guaranteeing envy-freeness are satisfied, it is interesting to study the degree of envy exhibited by an outcome. To this end, we introduce a generic framework for defining measures for assessing the degree of envy in a society and establish the computational complexity of checking whether a given scenario allows for a deal that is beneficial to every agent involved and that will reduce envy.
     </paragraph>
     <paragraph>
      The remainder of this paper is organised as follows. Section 2 introduces the framework of distributed negotiation over indivisible goods we have adopted and recalls two results from the literature regarding convergence to an economically efficient allocation, maximising the sum of individual utilities. Section 3 studies the case of proportionally fair outcomes. We show how to adapt the classical Knaster procedure to our setting and obtain a distributed procedure that guarantees convergence to a proportionally fair outcome. In Section 4 we carry out a similar programme, this time choosing envy-freeness as our goal. Envy-freeness is considerably more demanding a criterion than proportionality, so the convergence results that we obtain rely on somewhat stricter assumptions. The framework is extended to fair division on graphs in Section 5. We discuss possible extensions of the notions of efficiency, proportionality, and envy-freeness to this richer setting, and in the case of envy-freeness we arrive at a particularly satisfying definition as well as an attractive convergence result. We also argue that proportionality and efficiency are not naturally generalised to this setting. Section 6 proposes a framework for assessing the degree of envy in a society. It also establishes a computational complexity result that shows that identifying a deal that is acceptable to each agent involved and that reduces envy is NP-complete (but not harder than finding a deal that is simply acceptable to the agents involved). This holds for all the concrete measures of envy we define, and indeed for a much larger class of such measures, defined by a simple axiom. Section 7 concludes.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Distributed mechanisms for allocating indivisible goods
     </section-title>
     <paragraph>
      In this section we define the class of distributed mechanisms that we want to employ to negotiate fair allocations of goods and briefly recall a number of known results [13], [18].
     </paragraph>
     <section label="2.1">
      <section-title>
       Agents, goods, allocations, valuations
      </section-title>
      <paragraph>
       Let {a mathematical formula}N={1,…,n} be a finite set of agents and let {a mathematical formula}G, with {a mathematical formula}m=|G|, be a finite set of indivisible goods. An allocation{a mathematical formula}A:N→2G is a partitioning of the items in {a mathematical formula}G amongst the agents in {a mathematical formula}N, i.e., each good is owned by exactly one agent (here {a mathematical formula}2G denotes the powerset of {a mathematical formula}G). As an example, allocation A, defined via {a mathematical formula}A(i)={g1} and {a mathematical formula}A(j)={g2,g3}, would allocate {a mathematical formula}g1 to agent i, and {a mathematical formula}g2 and {a mathematical formula}g3 to agent j. We assume that the initial allocation, denoted by {a mathematical formula}A0, has been chosen at random, so agents cannot derive any rights from this allocation (as far as the definition of fairness is concerned).
      </paragraph>
      <paragraph>
       The interests of individual agents {a mathematical formula}i∈N are modelled using valuation functions{a mathematical formula}vi:2G→R, mapping bundles of goods to the reals. Valuation functions are private information. However, we assume that when asked for the valuation of a given bundle of goods S, any agent i will truthfully reveal the value {a mathematical formula}vi(S) she assigns to S. To simplify presentation, throughout this paper, we will make the assumption that all valuations {a mathematical formula}vi are normalised, in the sense that {a mathematical formula}vi(∅)=0, and non-negative, meaning that {a mathematical formula}vi(S)⩾0 for all {a mathematical formula}S⊆G. We sometimes use {a mathematical formula}vi(A) as a shorthand for {a mathematical formula}vi(A(i)), the value agent i assigns to the bundle received in allocation A.
      </paragraph>
      <paragraph>
       Some of our results only apply to scenarios where all valuation functions meet additional properties. A valuation function is called modular (or additive) if {a mathematical formula}v(S1∪S2)=v(S1)+v(S2)−v(S1∩S2) for all bundles {a mathematical formula}S1,S2⊆G. Similarly, v is called supermodular if {a mathematical formula}v(S1∪S2)⩾v(S1)+v(S2)−v(S1∩S2). Finally, a valuation function is called single-minded if there exist a bundle {a mathematical formula}S⁎⊆G and a positive number c such that {a mathematical formula}v(S)=c in case {a mathematical formula}S⁎⊆S and {a mathematical formula}v(S)=0 otherwise. Thus, in a single-minded agent is only interested in a single bundle of goods and assigns a fixed value to that bundle (and to all larger bundles including that specific bundle as a subset).
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Deals, payments, utility
      </section-title>
      <paragraph>
       Agents negotiate sequences of deals to improve their own welfare. A deal{a mathematical formula}δ=(A,A′) is a pair of allocations (with {a mathematical formula}A≠A′), specifying the situation before and after the deal. Observe that a single deal may involve the reassignment of any number of goods amongst any number of agents. A 1-deal is a deal involving only a single good (and hence only two agents). The set of agents involved in the deal {a mathematical formula}δ=(A,A′) is denoted as {a mathematical formula}Nδ={i∈N|A(i)≠A′(i)}. (In Section 5 we will introduce a refinement of the basic model, where agents can only make deals with agents to which they are connected in an underlying negotiation topology.)
      </paragraph>
      <paragraph>
       Deals may be accompanied by monetary side payments to allow agents to compensate others for otherwise disadvantageous deals. This is modelled using so-called payment functions:{a mathematical formula}p:N→R, which are required to satisfy {a mathematical formula}∑ip(i)=0. A positive value {a mathematical formula}p(i) indicates that agent i pays money, while a negative value means that she receives money. We associate each allocation A that is reached in a sequence of deals with a function {a mathematical formula}π:N→R mapping agents to the sum of payments they have made so far, i.e., we also have {a mathematical formula}∑iπ(i)=0. A state of the system is a pair {a mathematical formula}(A,π) of an allocation A and a payment balance π. It is possible to impose an initial payment on each agent, at the time of awarding them the bundle they receive in the initial allocation. Payment function and initial payments together are referred to as the payment scheme.
      </paragraph>
      <paragraph>
       Each agent {a mathematical formula}i∈N is also equipped with a utility function{a mathematical formula}ui:2G×R→R mapping pairs of bundles and previous payments to the reals. These are fully determined by the valuation functions: {a mathematical formula}ui(S,x)=vi(S)−x. That is, utilities are quasi-linear: they are linear in the monetary component, but the valuation over bundles of goods may be any set function. For example, {a mathematical formula}ui(A(i),π(i)) is the utility of agent i in state {a mathematical formula}(A,π), while {a mathematical formula}ui(A(j),π(j)) is the utility that i would experience if she were to swap places with j (in terms of both the bundle owned, and the sum of payments made so far).
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Individual rationality and efficiency
      </section-title>
      <paragraph>
       Agents are assumed to only negotiate individually rational (IR) deals, i.e., deals that benefit everyone involved:
      </paragraph>
      <paragraph label="Definition 1">
       IR dealsA deal {a mathematical formula}δ=(A,A′) is called individually rational (IR) if there exists a payment function p such that {a mathematical formula}vi(A′)−vi(A)&gt;p(i) for all agents {a mathematical formula}i∈N, except possibly {a mathematical formula}p(i)=0 for agents i with {a mathematical formula}A(i)=A′(i).
      </paragraph>
      <paragraph>
       While negotiation is driven by the individual preferences of agents, we are interested in reaching states that are attractive from a “social” point of view. A common measure for efficiency is (utilitarian) social welfare[24]:
      </paragraph>
      <paragraph label="Definition 2">
       Social welfareThe social welfare of an allocation A is defined as {a mathematical formula}sw(A)=∑i∈Nvi(A(i)).
      </paragraph>
      <paragraph>
       We also speak of the social welfare of a state{a mathematical formula}(A,π). As the sum of all {a mathematical formula}π(i) is always 0, the two notions coincide, i.e., it does not matter whether we define social welfare in terms of valuations or in terms of utilities. A state/allocation with maximal social welfare is called efficient.
      </paragraph>
      <paragraph label="Example 1">
       Let us consider an allocation problem with three agents, {a mathematical formula}N={1,2,3}, and four goods, {a mathematical formula}G={g1,g2,g3,g4}. Table 1 defines the valuation functions {a mathematical formula}vi by indicating for each agent how much she values the four individual goods and how much she values the full bundle. The values of bundles not shown are assumed to always be equal to the sum of the values of the items in them. Thus, {a mathematical formula}v1 and {a mathematical formula}v3 are modular, and all three valuation functions are supermodular.Maximal social welfare for this allocation problem is 20, namely when agent 1 holds the bundle {a mathematical formula}{g1,g2}, agent 2 gets nothing, and agent 3 holds {a mathematical formula}{g3,g4}. Let us denote this optimal allocation by {a mathematical formula}A⁎. Suppose now we are in allocation A, in which all four items are held by agent 2. Social welfare for A is 18. If our agents are only willing to negotiate 1-deals, then we will remain stuck in this suboptimal allocation and never reach {a mathematical formula}A⁎. To see this, check that agent 2 giving any single item to one of the other two agents would result in a drop of her utility from 18 to 12, thus requiring a price strictly above 6, which neither one of the other two agents would be willing to pay. We will return to this example throughout this paper.
      </paragraph>
      <paragraph>
       A central result in distributed negotiation, due to Sandholm [18], shows that the problem we observed in Example 1 does not persist if we do not impose any structural constraints on deals:
      </paragraph>
      <paragraph label="Theorem 1">
       Efficient outcomesAny sequence of IR deals will eventually result in an efficient allocation.
      </paragraph>
      <paragraph>
       That is, if agents continue to agree on IR deals, they will eventually reach a state from which no further IR deal is possible, and that state will be efficient. This result guarantees that agents can agree on any sequence of deals meeting the IR condition without getting stuck in a local optimum; and there can be no infinite sequence of IR deals. On the downside, this result presupposes that agents are able to negotiate complex multilateral deals between any number of agents and involving any number of goods. In modular domains, we can get a much stronger convergence result [13]:
      </paragraph>
      <paragraph label="Theorem 2">
       Efficient outcomes by 1-dealsIf all valuation functions are modular, then any sequence of IR 1-deals will eventually result in an efficient allocation.
      </paragraph>
      <paragraph label="Lemma 3">
       Theorem 1, Theorem 2 are easy consequences of the fact that a move from one allocation to another is an IR deal if and only if that move increases social welfare (see Endriss et al. [13] for a proof): IR deals and social welfareA deal{a mathematical formula}δ=(A,A′)is IR if and only if{a mathematical formula}sw(A)&lt;sw(A′).
      </paragraph>
      <paragraph>
       We will frequently rely on this fact in the sequel, mostly without explicit reference to Lemma 3. Note that Lemma 3 also entails that we can always reach an efficient allocation by means of just a single IR deal. Importantly, this does not diminish the importance of Theorem 1. Finding that particular IR deal to reach the optimum in a single step requires full coordination between all agents, while Theorem 1 guarantees convergence also in the absence of such global coordination and only requires agents to make deals locally that benefit themselves then and there.
      </paragraph>
     </section>
     <section label="2.4">
      <section-title>
       Specific payment functions
      </section-title>
      <paragraph>
       Requiring deals to be IR puts restrictions on what deals are possible at all and it limits the range of possible payments, but it does not determine the precise side payments to be made. This is a matter to be negotiated by the participating agents. Estivie et al. [25] introduce several concrete payment functions that agents may choose to adopt. The two simplest ones are the locally uniform payment function (LUPF) and the globally uniform payment function (GUPF).
      </paragraph>
      <paragraph>
       Choosing a payment function amounts to choosing how to distribute the social surplus{a mathematical formula}sw(A′)−sw(A) generated by a deal {a mathematical formula}δ=(A,A′). By Lemma 3, the social surplus is positive if and only if δ is IR. The LUPF divides this amount equally amongst the participating agents {a mathematical formula}Nδ; the GUPF divides it equally amongst all agents {a mathematical formula}N:{a mathematical formula} Importantly, note that the social surplus {a mathematical formula}sw(A′)−sw(A) can always be computed from the valuation functions of the participating agents alone:{a mathematical formula} Thus, the LUPF is a fully local payment function: it only requires us to consider input from the participating agents and only the payment balances of these agents will be affected. The GUPF is also local as far as the information required is concerned, except that we need to know the quantity n before we can compute it. On the other hand, the GUPF is global in the sense that payment balances of all agents are affected. Having said this, agents not participating in the deal can only ever receive money, but never have to make a payment themselves.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Proportional fairness and Knaster payments
     </section-title>
     <paragraph>
      Our first goal is to devise a distributed mechanism of the kind described in the previous section that can be used to negotiate outcomes that are proportionally fair (or simply proportional). An outcome, assigning each agent a bundle of goods and a payment balance, is proportional if the utility each agent assigns to their lot is at least {a mathematical formula}1/nth of the value they place on the full set of goods (where n is the number of agents).
     </paragraph>
     <paragraph label="Definition 3">
      ProportionalityA negotiation state {a mathematical formula}(A,π) is called proportional if {a mathematical formula}ui(A,π)⩾vi(G)/n for all agents {a mathematical formula}i∈N.
     </paragraph>
     <paragraph>
      Proportionality is the central fairness criterion applied in the cake-cutting literature, which addresses the problem of fairly dividing a single divisible good [3], [4], [5]. Before we proceed, let us briefly pause and consider under what circumstances proportionality is a reasonable fairness concept also in our context. Importantly, in almost all of the cake-cutting literature, agents are assumed to have additive preferences, which is an assumption we do not always want to make. As a minimum requirement for Definition 3 to be meaningful, we need to make the assumption that valuation functions are monotonic:{a mathematical formula}S1⊆S2 implies {a mathematical formula}vi(S1)⩽vi(S2). When agent valuations are supermodular, then it will often be impossible to obtain a proportional solution without using money (both for divisible and indivisible goods), because 1/nth of the value of the full set of goods would often be considered more than the value of 1/nth of the goods. For submodular valuations, on the other hand, proportionality would be a very undemanding fairness criterion, as it would often be easy to give an agent 1/nth of the value they ascribe to the full set by handing them a very small bundle. It is therefore questionable whether proportionality should be considered a relevant fairness criterion in case valuations may be submodular. This caution not withstanding, due to the central importance of proportionality in the classical literature, we nevertheless choose to demonstrate here how to apply our methodology to this concept. We will be able to obtain a positive result for arbitrary domains, but the reader should keep in mind that this result is at its most attractive when applied to supermodular rather than to submodular domains.
     </paragraph>
     <paragraph>
      To define a distributed procedure that can guarantee proportional outcomes we will take inspiration from the classical fair division procedure proposed by Bronisław Knaster in the 1940s [26], [3], [27].{sup:1} In this section, we recall the classical Knaster procedure, show how to adapt it to define a payment scheme, and prove a convergence theorem showing that this scheme guarantees outcomes that are both efficient and proportional.
     </paragraph>
     <section label="3.1">
      <section-title>
       The Knaster procedure
      </section-title>
      <paragraph>
       Our exposition of the Knaster procedure follows Raith [27]. An important difference between the classical and our (more general) setting is that in the classical setting valuation functions are assumed to be modular (additive). This difference affects the first step of the procedure.
      </paragraph>
      <list>
       <list-item label="(1)">
        Compute an allocation {a mathematical formula}A⁎ that maximises social welfare. (In the classical setting this step simplifies to assigning each good to the agent who values it the most.)
       </list-item>
       <list-item label="(2)">
        For each agent i, compute her excess{a mathematical formula}exi(A⁎)=vi(A⁎)−vi(G)/n over her fair share. The total excess is defined as {a mathematical formula}Ex(A⁎)=∑iexi(A⁎).
       </list-item>
       <list-item label="(3)">
        Split the total excess evenly amongst all the agents; that is, require a payment of {a mathematical formula}exi(A⁎)−Ex(A⁎)/n from each agent i.
       </list-item>
      </list>
      <paragraph>
       Note that the individual excess of an agent could be a negative number, as could be the payment she has to make (in which case she would receive money). Clearly, the payments of all agents sum up to zero, so are feasible. While an agent's individual excess {a mathematical formula}exi could be negative, the total excess {a mathematical formula}Ex(A⁎) will always be positive (or zero). This follows from the fact that {a mathematical formula}Ex(A⁎)=sw(A⁎)−1n⋅∑ivi(G) and that we must have {a mathematical formula}sw(A⁎)⩾vi(G) for any i (because {a mathematical formula}A⁎ is efficient by definition and hence at least as good as giving all goods to i). After the procedure has been executed, agent i will enjoy utility {a mathematical formula}vi(A⁎)−[exi(A⁎)−Ex(A⁎)/n]=vi(G)/n+Ex(A⁎)/n. Hence, the Knaster procedure does indeed produce a proportional outcome.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Definition of a payment scheme
      </section-title>
      <paragraph>
       As demonstrated by Theorem 1, our distributed negotiation procedure is capable of selecting an allocation {a mathematical formula}A⁎ with maximal social welfare. We now want to devise a payment scheme that guarantees proportionality on top of efficiency. At the point of convergence we would like to obtain an outcome that is equivalent to the outcome we would have gotten by using the Knaster procedure.
      </paragraph>
      <paragraph>
       Recall that defining a payment scheme involves fixing an initial payment {a mathematical formula}π0(i) for each agent and choosing a payment function p. Our approach is simply to choose {a mathematical formula}π0 and p such that at each stage {a mathematical formula}(A,π) of the negotiation we will have {a mathematical formula}π(i)=exi(A)−Ex(A)/n, thereby emulating the payments prescribed by the Knaster procedure (with the crucial difference that in the Knaster procedure payments are only required once, at the very end). Let {a mathematical formula}A0 be the initial (randomly chosen) allocation. We must fix {a mathematical formula}π0 as follows:{a mathematical formula} Here {a mathematical formula}exi and Ex are defined as in Section 3.1. Of course, if {a mathematical formula}A0 is sufficiently close to an efficient allocation, then these payments will already result in a proportional outcome. On the other hand, for a sufficiently inefficient {a mathematical formula}A0 neither these nor any other payments could possibly ensure proportionality.
      </paragraph>
      <paragraph>
       Next we choose a payment function p. We want to maintain {a mathematical formula}π(i)=exi(A)−Ex(A)/n as an invariant for all negotiation states {a mathematical formula}(A,π). This forces the following payments for a deal {a mathematical formula}δ=(A,A′), with π being the payment balance for allocation A and {a mathematical formula}π′ being the payment balance for {a mathematical formula}A′:{a mathematical formula} But this is exactly the GUPF, defined in Section 2.4. In particular, the payments prescribed by this choice of p are IR. In summary, the Knaster payment scheme is given by the GUPF together with the initial payments defined in Equation (1).
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Convergence
      </section-title>
      <paragraph>
       We are now going to show that, indeed, negotiation using the Knaster payment scheme will always converge to a proportional outcome.
      </paragraph>
      <paragraph label="Theorem 4">
       Proportional outcomesUnder the Knaster payment scheme, any sequence of IR deals will eventually result in a state that is efficient and proportional.
      </paragraph>
      <paragraph label="Proof">
       By Theorem 1, any sequence of IR deals must converge to an efficient state, independently from the specific payment scheme in use. As we are using the Knaster payment scheme, any state {a mathematical formula}(A,π) reached during negotiation will satisfy {a mathematical formula}π(i)=exi(A)−Ex(A)/n for each agent i. Hence, we are bound to converge to a state {a mathematical formula}(A⁎,π⁎) with an efficient allocation {a mathematical formula}A⁎ where {a mathematical formula}π⁎(i)=exi(A⁎)−Ex(A⁎)/n. This is exactly the kind of outcome we would have obtained had we used the Knaster procedure, which we have seen to always be proportional (see Section 3.1).  □
      </paragraph>
      <paragraph>
       Thus, convergence to a proportional outcome is guaranteed. If all agents have modular valuation functions (as is the case for the classical setting of the Knaster procedure), then we can guarantee convergence to a proportional state using a simpler negotiation protocol.
      </paragraph>
      <paragraph label="Theorem 5">
       Proportional outcomes by 1-dealsUnder the Knaster payment scheme, if all valuation functions are modular, any sequence of IR 1-deals will eventually result in a state that is efficient and proportional.
      </paragraph>
      <paragraph label="Proof">
       By Theorem 2, any sequence of IR 1-deals must converge to an efficient state whenever all valuation functions are modular. The rest of the argument is identical to the proof of Theorem 4.  □
      </paragraph>
      <paragraph label="Example 2">
       Recall Example 1, with three agents with valuation functions as specified in Table 1. The only efficient allocation here is {a mathematical formula}A⁎, which assigns {a mathematical formula}{g1,g2} to agent 1 and {a mathematical formula}{g3,g4} to agent 3 and which has a social welfare of 20. We may write this more compactly as {a mathematical formula}A⁎=〈{g1,g2},∅,{g3,g4}〉. Suppose the initial allocation is {a mathematical formula}A0=〈{g4},{g2,g3},{g1}〉, giving utility 0, 8, and 0 to agents 1, 2, and 3, respectively.Let us illustrate convergence to a proportional allocation with Knaster payments. First, we compute the excess {a mathematical formula}exi(A0) for each agent i:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ex1(A0)=0−10/3=−10/3
       </list-item>
       <list-item label="•">
        {a mathematical formula}ex2(A0)=8−18/3=6/3
       </list-item>
       <list-item label="•">
        {a mathematical formula}ex3(A0)=0−10/3=−10/3
       </list-item>
      </list>
      <paragraph>
       We continue our treatment of proportionality by briefly discussing alternative payment schemes for guaranteeing proportional outcomes. As shown in Section 3.1, the Knaster procedure guarantees each agent i a marginal utility of {a mathematical formula}Ex(A⁎)/n above and beyond their fair share of {a mathematical formula}vi(G)/n. But any alternative division of the total excess {a mathematical formula}Ex(A⁎) will also satisfy proportionality. The equal division chosen by Knaster is a particularly natural choice, but it is not the only one. Raith [27], for instance, argues that a division of the total excess that is proportional to each individual's valuation of the full set of goods may be more appropriate and proposes an adjustment of the Knaster procedure to achieve this.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}(αi)i∈N with {a mathematical formula}αi⩾0 and {a mathematical formula}∑iαi=1 be a vector specifying for each agent their entitlement to a proportion of the total excess. By revisiting the proofs given above, it is not difficult to see that Theorem 4, Theorem 5 will continue to hold if the Knaster payment scheme is replaced by any payment scheme of the following form:{a mathematical formula} For the Knaster payment scheme we have {a mathematical formula}αi=1n, while for the payment scheme corresponding to the Raith–Knaster procedure [27] we have {a mathematical formula}αi=vi(G)∑jvj(G). The two payment schemes coincide in case we have {a mathematical formula}vi(G)=1 for all {a mathematical formula}i∈N.
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Path length
      </section-title>
      <paragraph>
       In the previous section we have seen that convergence to an efficient and proportional state can always be guaranteed by our scheme. But how many deals do we require to reach a social optimum? First, observe that by Lemma 3, it is always possible to reach the optimum using (at most) one deal, i.e., 1 is a (tight) upper bound on the shortest path. Much more interesting in practice, however, is the longest path, i.e., the longest sequence of IR deals that agents may end up agreeing on before convergence. For convergence to an efficient allocation by means of IR deals, {a mathematical formula}nm−1, with n being the number of agents and m being the number of goods, is known to be a (tight) upper bound on the longest path, i.e., there exist profiles of valuation functions and initial allocations such that it is possible to visit all allocations before convergence [29]. Inspection of the proof of that result shows that it does not depend on the payment scheme used. Hence, {a mathematical formula}nm−1 is also an upper bound on the number of deals for scenarios covered by Theorem 4—at least if we do not put restrictions on the nature of our agents' valuation functions.
      </paragraph>
      <paragraph>
       If we do require valuation functions to be normalised and monotonic (and possibly also supermodular, which we have argued to be reasonable in the context of studies of proportionality), then the construction used in previous work [29] does not apply any longer. We now want to show that the result itself nevertheless carries over.
      </paragraph>
      <paragraph label="Lemma 6">
       Distinct welfareWe can find a valuation function for each agent that is normalised, non-negative, and modular such that any two allocations have distinct utilitarian social welfare.
      </paragraph>
      <paragraph label="Proof">
       We first define the valuation function {a mathematical formula}v1 of the first agent in a way that ensures that she assigns a distinct value to every possible bundle. Let {a mathematical formula}G={g1,…,gm} and define:{a mathematical formula} That is, {a mathematical formula}v1 maps bundles to the numbers from 0 to {a mathematical formula}2m−1 (the reader may find it helpful to think of bundles as representing binary numbers with m digits). Note that {a mathematical formula}v1 is normalised, non-negative, and modular. Now define the valuation functions of the remaining agents as follows:{a mathematical formula} That is, each agent's valuation function is operating “at its own scale”. Now, if we are given the utilitarian social welfare of an allocation A as a binary number, then we know that that number will have a 1 in position {a mathematical formula}m⋅(i−1)+k (counting from the right) if and only if agent i has obtained good {a mathematical formula}gk under A. Hence, there is a bijection between allocations and social welfare values, i.e., any two distinct allocations must have distinct social welfare, as claimed.  □
      </paragraph>
      <paragraph>
       Observe that any valuation function that is normalised, non-negative, and modular is also monotonic and supermodular. Hence, there exist normalised, monotonic and supermodular valuation functions such that no two allocations have the same utilitarian social welfare. This means, that there exists a sequence of IR deals that visits all {a mathematical formula}nm allocations (each of the m goods may be given to any of the n agents), and thus {a mathematical formula}nm−1 is a tight upper bound on the length of the longest path for scenarios covered by Theorem 4, also when valuations are subject to the restrictions we have argued to be natural for studies of proportional fairness.
      </paragraph>
      <paragraph>
       This bound applies in case we are interested in finding an allocation that is both proportional and efficient. Can we do better if we only require proportionality? This might seem a possibility, given the fact that, if agents negotiate IR deals using the Knaster payment scheme, then efficiency is only achieved at the very last deal, but proportionality will often get achieved already much earlier, namely as soon as the total excess {a mathematical formula}Ex(A) of the current allocation A is non-negative. Yet, the answer to our question is still negative:
      </paragraph>
      <paragraph label="Proposition 7">
       Path length to a proportional stateWe can find a valuation function for each agent and an initial allocation such that there exists a sequence of IR deals with Knaster payments that will achieve proportionality only after exactly{a mathematical formula}nm−1deals.
      </paragraph>
      <paragraph label="Proof">
       Take a scenario where the agents have the valuation functions used in the proof of Lemma 6, except that {a mathematical formula}vn(G) is set to such a high value that the only way of achieving a proportional state is to give all goods to agent n (because no payments the other agents would be prepared to make could be large enough to give utility {a mathematical formula}vn(G)/n to agent n). Then all allocations have distinct social welfare, i.e., we can construct a sequence of deals visiting all of them, and proportionality would only get achieved at the very end of the sequence.  □
      </paragraph>
      <paragraph>
       Finally, given Lemma 6, known results for convergence by means of 1-deals in case all valuation functions are additive (i.e., the kind of scenario covered by Theorem 5) now also carry over immediately [29]. Concretely, this means that m is a tight upper bound for the shortest path (as we need at most one deal per item if we only choose optimal deals) and {a mathematical formula}m⋅(n−1) is a tight upper bound for the longest path (as each item may, in the worst case, pass through every single agent).
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Envy-freeness and globally uniform payments
     </section-title>
     <paragraph>
      Besides proportionality, another important fairness criterion is envy-freeness[30], [3], [11], [10]. An allocation of goods is envy-free if no agent would rather have the bundle held by one of the other agents. This is a more demanding requirement than proportionality. Indeed, if we require all goods to be allocated, then an envy-free allocation may not even exist at all, and the problem of checking whether or not an envy-free allocation exists has been shown to be computationally intractable [14]. Fortunately, in the presence of money, when envy-freeness is defined in terms of both bundles of goods and payments received, the situation is more favourable and envy-free solutions do exist [7].
     </paragraph>
     <paragraph label="Definition 4">
      In this section we will identify conditions under which we can guarantee convergence to an envy-free outcome. Envy-freenessA negotiation state {a mathematical formula}(A,π) is called envy-free if {a mathematical formula}ui(A(i),π(i))⩾ui(A(j),π(j)) for all agents {a mathematical formula}i,j∈N.
     </paragraph>
     <paragraph>
      A state that is both efficient (in the sense of maximising social welfare) and envy-free will be referred to as an EEF state.
     </paragraph>
     <paragraph>
      If all valuation functions are submodular (or modular), that is, when no agent ever likes the union of two disjoint bundles strictly more than the sum of the valuations of the two individual bundles, then any state that is envy-free is also proportional. The converse is not true: a proportional state is not necessarily envy-free. If valuation functions are supermodular, then envy-freeness does not guarantee proportionality, nor vice versa.
     </paragraph>
     <section label="4.1">
      <section-title>
       Existence of envy-free states
      </section-title>
      <paragraph>
       In the presence of money, intuitively, chances for finding an envy-free solution are better than when there is no money. In particular, in the context of assignment problems, i.e., when each agent can only receive at most a single good, states that are both efficient and envy-free are known to always exist. This has been shown by Alkan et al. [6]. When agents can obtain (and express preferences over) bundles consisting of several goods, there is in general no such guarantee, i.e., as demonstrated by Tadenuma [8], for some allocation problems there simply exists no state that is both efficient and envy-free. However, the assumption of quasi-linearity of money is very important here: if we require quasi-linearity, as we do in this paper, then the existence of EEF states can be proven by an argument similar to the one used by Alkan et al. [6], appealing to the Duality Theorem [31], as demonstrated by Beviá [7]. When all valuation functions are supermodular, we can give a much simpler argument for the existence of EEF states, which does not rely on the Duality Theorem. As we will see later on, this case is of special interest to us, which is why we present this argument here in some detail.
      </paragraph>
      <paragraph>
       There clearly always exists an allocation that is efficient: some allocation must yield a maximal sum of individual valuations. Let {a mathematical formula}A⁎ be such an efficient allocation. We show that a payment balance {a mathematical formula}π⁎ can be arranged such that the state {a mathematical formula}(A⁎,π⁎) is EEF. Define {a mathematical formula}π⁎(i) for each agent i:{a mathematical formula} First, note that {a mathematical formula}π⁎ is a valid payment balance: the {a mathematical formula}π⁎(i) do indeed sum up to 0. Now let {a mathematical formula}i,j∈N be any two agents in the system. We show that i does not envy j in state {a mathematical formula}(A⁎,π⁎). As {a mathematical formula}A⁎ is efficient, giving both {a mathematical formula}A⁎(i) and {a mathematical formula}A⁎(j) to i will not increase social welfare any further:{a mathematical formula} As {a mathematical formula}vi is assumed to be supermodular (and normalised), this entails:{a mathematical formula} Adding {a mathematical formula}sw(A⁎)/n to both sides of this inequality, together with some simple rearrangements, yields {a mathematical formula}ui(A⁎(i),π⁎(i))⩾ui(A⁎(j),π⁎(j)), i.e., agent i does indeed not envy agent j. Hence, {a mathematical formula}(A⁎,π⁎) is not only efficient, but also envy-free.
      </paragraph>
      <paragraph>
       Of course, the mere existence of an EEF state alone is not sufficient in the context of negotiation amongst autonomous agents. Why should rational decision-makers accept the allocation and payments prescribed above? And even if they do, how can we compute them in practice? Just finding an efficient allocation is already known to be NP-hard [32]. Finally, as argued in the introduction, we are interested in a distributed procedure, where agents identify the optimal state in an interactive manner.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Convergence in supermodular domains
      </section-title>
      <paragraph>
       We are now going to prove a result on the reachability of EEF states by means of distributed negotiation. Our result applies to supermodular domains only. The payment scheme it employs consists of the GUPF in combination with the following initial payments:{a mathematical formula} That is, each agent has to first pay an amount equivalent to their valuation of the initial allocation {a mathematical formula}A0, and will then receive an equal share of the social welfare as a kick-back. We refer to this choice of initial payment as an initial equitability payment. Note that this payment does not achieve envy-freeness (and it does not affect efficiency at all). In the special case where none of the agents has an interest in the goods they hold initially ({a mathematical formula}vi(A0)=0 for all {a mathematical formula}i∈N), the initial payments reduce to 0.
      </paragraph>
      <paragraph label="Theorem 8">
       Envy-free outcomesIf all valuation functions are supermodular and if initial equitability payments have been made, then any sequence of IR deals using the GUPF will eventually result in an EEF state.
      </paragraph>
      <paragraph label="Proof">
       We first show that the following invariant will be true for every state {a mathematical formula}(A,π) and every agent i, provided that agents only negotiate IR deals using the GUPF:{a mathematical formula} Our proof proceeds by induction over the number of deals negotiated. As we assume that initial equitability payments have been made, claim (2) will certainly be true for the initial state {a mathematical formula}(A0,π0). Now let {a mathematical formula}δ=(A,A′) and assume (2) holds for A and the associated payment balance π. We obtain the payment balance {a mathematical formula}π′ associated with {a mathematical formula}A′ by adding the appropriate GUPF payments to π:{a mathematical formula} This proves our claim (2). Now, Theorem 1 shows that negotiation via IR deals (whichever payment function is used) must eventually terminate and that the final allocation will be efficient. Let {a mathematical formula}A⁎ be that final allocation, and let {a mathematical formula}π⁎ be the associated payment balance. Equation (2) also applies to the state {a mathematical formula}(A⁎,π⁎). But as we have already seen in Section 4.1, the efficiency of {a mathematical formula}A⁎ together with Equation (2) applied to {a mathematical formula}(A⁎,π⁎) implies that {a mathematical formula}(A⁎,π⁎) must be an EEF state.  □
      </paragraph>
      <paragraph label="Example 3">
       Observe that the final state attained in Example 2 is not envy-free. This is so, because, for instance, {a mathematical formula}u1(A⁎(1),πK(1))=52/9, while {a mathematical formula}u1(A⁎(2),πK(2))=76/9: agent 1 envies agent 2, even though the latter does not own any goods, because of the amount of money she receives through the Knaster payments (here, {a mathematical formula}πK denotes the payment balances according to the Knaster scheme for the final state, corresponding to the efficient allocation {a mathematical formula}A⁎=〈{g1,g2},∅,{g3,g4}〉). To illustrate the difference between the Knaster payment scheme and the payment scheme of Theorem 8, let us consider the simple example shown in Table 3, involving the initial allocation {a mathematical formula}A0=〈{g4},{g2,g3},{g1}〉 and a single IR deal leading to the efficient allocation {a mathematical formula}A⁎. Note that the initial state is not envy-free, not even after the initial equitability payments, as for instance agent 2 envies agent 1, given that {a mathematical formula}u2(A0(1),π0(1))=4+8/3=20/3&gt;8/3=8−16/3=u2(A0(2),π0(2)).
      </paragraph>
      <paragraph>
       As argued in Section 3.4, Lemma 6 shows that the bounds on the lengths of paths to convergence established in previous work on negotiating efficient allocation for arbitrary valuation functions [29] apply also to the types of scenarios covered by Theorem 8: 1 is a (tight) upper bound on the shortest path and {a mathematical formula}nm−1 is a (tight) upper bound on the longest path.
      </paragraph>
      <paragraph>
       Theorem 8 is a surprising result. As pointed out elsewhere [13], it is not possible to define a “local” criterion for the acceptability of deals (which can be checked taking only the valuation functions of the agents involved into account) that would guarantee that a sequence of such deals always converges to an envy-free state. We circumvent this problem here by using the GUPF, which adds a (very limited) non-local element. It is limited, because only the agents involved in a deal can ever be asked to give away money, and all payments can be computed taking only the valuations of those involved into account.
      </paragraph>
      <paragraph>
       A natural question that follows is whether Theorem 8 could be generalised, namely whether a more general class of valuations would still allow us to guarantee convergence to an envy-free state. The following result shows that this is not the case, at least not if we keep the payment scheme of Theorem 8 in place.
      </paragraph>
      <paragraph label="Theorem 9">
       Maximality of supermodularityNo class{a mathematical formula}Fof valuation functions that strictly includes the class of supermodular functions can guarantee the following property: if all valuation functions are drawn from{a mathematical formula}Fand initial equitability payments have been made, then any sequence of IR deals using the GUPF will eventually result in an EEF state.
      </paragraph>
      <paragraph label="Proof">
       First, observe that under the payment scheme of Theorem 8, which is characterised by Inequality (2), the envy-freeness condition {a mathematical formula}ui(A(i),π(i))⩾ui(A(j),π(j)) is equivalent to the following inequality (which must hold for any two agents i and j):{a mathematical formula} To prove the claim of the theorem, we give an example with two agents and two goods, where Inequality (3) fails to be satisfied for the unique efficient allocation. Hence, as negotiation by means of IR deals is bound to lead to that efficient allocation, and as the payment scheme is fixed, this will show that the final allocation cannot be envy-free. The first agent will have an arbitrary non-supermodular valuation function; for the second agent we will construct a supermodular valuation function. Thus, our counterexample is generic and will apply for any superclass {a mathematical formula}F of the supermodular functions (which must include at least one non-supermodular function and all supermodular functions). Showing failure of convergence for the simple case of two agents and two goods immediately implies failure of convergence for larger negotiation problems.Our counterexample is constructed as follows. Take {a mathematical formula}v1 to be any non-supermodular valuation function defined over two goods {a mathematical formula}g1 and {a mathematical formula}g2; that is{a mathematical formula} where {a mathematical formula}d&gt;0. Now we construct a second valuation function {a mathematical formula}v2, which will be modular (so it certainly also will be supermodular), as follows:{a mathematical formula} But now, in a scenario with two agents with these two valuation functions, the (only) efficient allocation is to give good {a mathematical formula}g1 to agent 1 and good {a mathematical formula}g2 to agent 2, yielding a social welfare of {a mathematical formula}v1({g1})+v1({g2})−d/3. However, it is clear that this allocation does not satisfy Inequality (3). Indeed, agent 1 values {a mathematical formula}g2 more than agent 2 does; that is, it is not the case that agent 2 values her own share at least as much as anyone else would.  □
      </paragraph>
      <paragraph>
       Theorem 9 is reminiscent of so-called maximality theorems in multiagent resource allocation [20], which are results that show that certain classes of valuation functions that can guarantee convergence under a certain negotiation protocol are maximal in the sense of no strictly larger class being able to still provide the same guarantee. Observe that the proof of Theorem 9 uses Equation (3), which is only mandatory if the payment scheme being used is the GUPF with initial equitability payments. In particular, it could be the case that for different payment functions, different valuation functions could work. However, as the GUPF is attractive due to its simplicity, Theorem 9 offers an interesting characterisation of a domain of valuation functions guaranteeing convergence to states without envy.
      </paragraph>
      <paragraph>
       Vice versa, as we will see next, if we fix the supermodularity condition, then the payment scheme of Theorem 8 turns out to be the only scheme (meeting certain mild conditions) that would allow us to obtain a convergence result. To make this claim precise, let us call a payment function p path-independent if there exists a function {a mathematical formula}f:N×Rn→R such that for any deal {a mathematical formula}δ=(A,A′) the payment {a mathematical formula}p(i) of any agent i is equal to {a mathematical formula}f(i,〈Δ1,…,Δn〉), where {a mathematical formula}Δj=vj(A′)−vj(A). That is, a payment function is path-independent if payments only depend on the agents' changes in valuation resulting from a deal. In particular, payments are not dependent on the position of the deal in the overall sequence. We call a payment scheme path-independent if the associated payment function is path-independent.
      </paragraph>
      <paragraph label="Theorem 10">
       Payment schemesNo path-independent payment scheme Π other than the GUPF with initial equitability payments can guarantee the following property: if all valuation functions are supermodular, then any sequence of IR deals using Π will eventually result in an EEF state.
      </paragraph>
      <paragraph label="Proof">
       Observe that there are many scenarios where, for the final state to be EEF, the final payment balance must be defined by {a mathematical formula}π⁎(i)=vi(A⁎)−sw(A⁎)/n, as in the proof of Theorem 8. Any situation where all agents have the same valuation function may serve as an example. Of course, any number of payment functions could achieve these final payment balances, as long as we can be sure that the rule applied during the very last deal is such that we get the correct values for {a mathematical formula}π⁎. We need to show that, amongst the path-independent payment schemes, the scheme of Theorem 8 is the only one with this property.Path-independent schemes do not allow us to make payments dependent on where in the sequence of deals we currently are. In particular, knowing only the differences in individual valuations between two allocations A and {a mathematical formula}A′ is not sufficient information to determine whether {a mathematical formula}A′ is efficient, i.e., whether the process will terminate once {a mathematical formula}A′ is reached. Therefore, {a mathematical formula}π(i)=vi(A)−sw(A)/n must hold after every deal. But this forces initial payments to be exactly as in Theorem 8 (initial equitability payments), because the initial allocation may already be efficient and hence final; and the only possible payment function is the GUPF, as it is precisely the function we obtain when we compute the difference of the payment balances for two consecutive negotiation states.  □
      </paragraph>
      <paragraph>
       In summary, Theorem 9, Theorem 10 together show that our convergence result, Theorem 8, is in some sense as strong as possible: we can neither relax the range of valuation functions to which it applies nor the payment scheme for which it will go through.
      </paragraph>
      <paragraph>
       In related work, there have been some proposals for procedures for finding EEF states in the social choice literature [6], [33], [34], albeit with little or no attention to computational issues. The work of Haake et al. [34] is particularly interesting. These authors propose two variants of the same procedure, the first of which assumes that an efficient allocation is given to begin with. The actual procedure determines compensatory payments to envious agents such that an EEF state will eventually be reached. While their solution is elegant and intuitively appealing, it does not address the main issue as far as the computational aspect of the problem is concerned: by taking the efficient allocation as given, the problem is being limited to finding an appropriate payment balance. Certainly for supermodular domains, as our discussion in Section 4.1 demonstrates, this is not a hard combinatorial problem: there is a simple procedure for choosing the payments.
      </paragraph>
      <paragraph>
       The second procedure put forward by Haake et al. [34] interleaves reallocations for increasing efficiency with payments for eliminating envy. However, here the authors also do not address a hard combinatorial problem, because they assume “exogenously given bundles”. That is, negotiation relates only to who gets which bundle, but the composition of the bundles themselves cannot be altered. This is equivalent to the assignment problem of allocating n objects to n agents, which, unlike the problem addressed by Theorem 8, is not an NP-hard problem [35].
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Convergence in modular domains
      </section-title>
      <paragraph>
       In modular domains, we can strengthen Theorem 8 and even guarantee convergence to an EEF state by means of 1-deals (over one item at a time):
      </paragraph>
      <paragraph label="Theorem 11">
       Envy-free outcomes by 1-dealsIf all valuation functions are modular and if initial equitability payments have been made, then any sequence of IR 1-deals using the GUPF will eventually result in an EEF state.
      </paragraph>
      <paragraph label="Proof">
       This works as for Theorem 8, except that we rely on Theorem 2 for convergence by means of 1-deals (in place of Theorem 1). Note that the argument of Section 4.1 still applies, because any modular valuation function is also supermodular.  □
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Fair division on social networks
     </section-title>
     <paragraph>
      As argued in the introduction, there are good reasons for studying distributed mechanisms for fair division, such as a lack of confidence in—or the mere absence of—a central authority for regulating interaction. One even more compelling reason is that agents may be spatially distributed, with restricted interaction opportunities between them. In this context, the assumption of a fully connected graph (or global network) connecting agents quickly becomes unrealistic. The pervasiveness of applications exhibiting underlying graph-like structures, like for instance small-world networks, is thus a solid motivation to study distributed mechanisms for allocating goods. But it also necessitates making appropriate assumptions about agents being only able to act and perceive their environment locally.
     </paragraph>
     <paragraph>
      To account for this, we will assume that not every agent is able to “see” all of the other agents and formulate an appropriate generalisation of our model.{sup:2} A negotiation topology (or social network) is an undirected graph {a mathematical formula}G=(N,E), the vertices of which are the agents in {a mathematical formula}N. Two agents i and j stand in the relation E if and only if they can see each other. This means, in particular, that i and j may engage in negotiation and exchange goods. The visibility relation E is symmetric (the graph is undirected); this is important to be able to define negotiation along graphs in a meaningful manner.
     </paragraph>
     <paragraph>
      We put the following structural restriction on deals: any deal is possible, as long as it only involves agents belonging to a common clique of G. (Recall that a clique is a set of vertices {a mathematical formula}C⊆N such that {a mathematical formula}(i,j)∈E for all distinct {a mathematical formula}i,j∈C.) We call deals meeting this condition clique-deals.
     </paragraph>
     <paragraph label="Definition 5">
      Clique-dealsA deal {a mathematical formula}δ=(A,A′) is called a clique-deal if the set of involved agents {a mathematical formula}Nδ is a clique of the negotiation topology G.
     </paragraph>
     <paragraph>
      We will be particularly interested in deals that are both clique-deals and IR. Note that we will soon use the same topological constraints in order to define what information is available to agents in the graph. For instance, agents may not be aware of the goods being held by agents outside of their scope of visibility. (In theory, different graphs could be used for these two aspects, but we will not consider this possibility here.)
     </paragraph>
     <paragraph>
      As we will see in greater detail below, it will not always be straightforward to adapt notions of fairness to the context of social networks. In particular, we will see that no definition of proportionality seems totally satisfying, while envy gives rise to a very natural interpretation.
     </paragraph>
     <section label="5.1">
      <section-title>
       Defining fairness on graphs
      </section-title>
      <paragraph>
       Defining proportional fairness on graphs is less straightforward than one might expect. This is so because we need to make more precise what information is available to agents located on the graph when they have to assess whether their share is proportionally fair. Proportionality is typically evaluated with respect to the full set of goods {a mathematical formula}G available in the system. In the distributed settings involving graphs discussed in this section, agents may not have full information regarding the current location of the goods, so it is important to define exactly what information is available to them. It is natural to assume that each agent must have at least access to its local neighbourhood (agents and goods that they can “see”). Then, depending on what we assume to be available to agents on top of this, we may favour different intuitive definitions of proportionality on a graph.
      </paragraph>
      <paragraph>
       The first option is to assume that the full set of goods is known to the agents (even if their exact location is not known), and to define proportionality accordingly. A less demanding (and arguably more intuitive) definition is to have proportionality defined with respect to a subset of the full set of goods of the system, namely the goods an agent has seen so far. The rationale behind this approach is that agents start the process with very little knowledge regarding the goods being negotiated, and learn during interactions. Unfortunately, it is easy to see that, for both definitions, our framework could not possibly guarantee proportional outcomes to occur in all cases (even though the second option is more likely to reach such an outcome, of course). The reason is simple: even though “full” efficiency is not required as such to guarantee proportionality, allocations can be too inefficient to allow proportionality. But it is easy to design negotiation topologies so that outcomes are bound to be highly inefficient, due to agents with low valuations for particular goods acting as bottlenecks. A third alternative option is to define proportionality with respect to what an agent can currently see in the network. This solution is highly questionable though, because it means that agents must forget about the goods they have seen in previous states.
      </paragraph>
      <paragraph>
       Unlike proportionality, the notion of envy happens to give rise to a very natural extension in the context of graphs. In this case indeed, the restriction to the information available to agents in their neighbourhood is very appealing: envy can only be experienced by agents with respect to the agents they can see on the network. For example, in the extreme case of a society of completely disconnected agents, no agent would ever be envious of the situation of any other agent. To account for a negotiation topology, we then propose the following modification of the definition of envy-freeness:
      </paragraph>
      <paragraph label="Definition 6">
       GEF statesA state {a mathematical formula}(A,π) is called graph-envy-free (GEF) with respect to the graph {a mathematical formula}G=(N,E) if {a mathematical formula}ui(A(i),π(i))⩾ui(A(j),π(j)) for all agents {a mathematical formula}(i,j)∈E.
      </paragraph>
      <paragraph>
       As we have seen in Section 4, our guarantee for convergence to envy-freeness relies on the final allocation being efficient (or at least efficient “enough”). But as argued above, it is always possible to construct scenarios that would keep outcomes very far from full efficiency. In what follows, we see however that some weaker notion of efficiency can be satisfied, which will suffice to permit envy-freeness on graphs to hold.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Clique-wise efficiency
      </section-title>
      <paragraph>
       We now develop a notion of efficiency that takes the negotiation topology into account and relate this notion to IR negotiation when restricted to clique-deals.
      </paragraph>
      <paragraph label="Definition 7">
       Clique-variantsLet A be an allocation. Another allocation {a mathematical formula}A′ is called a clique-variant of A if and only if there exists a clique {a mathematical formula}C⊆N such that {a mathematical formula}⋃i∈CA(i)=⋃i∈CA′(i) and {a mathematical formula}A(i)=A′(i) for all {a mathematical formula}i∉C.
      </paragraph>
      <paragraph>
       Observe that A and {a mathematical formula}A′ are clique-variants of each other if and only if {a mathematical formula}δ=(A,A′) is a clique-deal.
      </paragraph>
      <paragraph label="Definition 8">
       Clique-wise efficiencyAn allocation A is called clique-wise efficient if {a mathematical formula}sw(A)⩾sw(A′) for every clique-variant {a mathematical formula}A′ of A.
      </paragraph>
      <paragraph>
       It should be noted that, in its own right, this notion of efficiency would only be of very limited interest. In particular, as the following example demonstrates, an allocation that is clique-wise efficient can be arbitrarily bad in terms of global efficiency. Consider Fig. 1, showing a negotiation topology between three agents, together with the valuation each of these three agents assigns to the good g. Now suppose that in allocation A, item g is assigned to agent 1, i.e., social welfare is 1. The only clique-variant of A is the allocation where g is given to agent 2, which would reduce social welfare to 0. Thus, A is clique-wise efficient. On the other hand, allocation {a mathematical formula}A′, giving g to agent 3 instead, would increase social welfare by a factor of 100.
      </paragraph>
      <paragraph>
       The reader might doubt the significance of this example and point out that the chosen valuation functions are extremely different from each other, or that a line topology might be a particularly problematic case to handle. But in fact, this kind of situation can occur also under much more favourable circumstances, as the following result shows:
      </paragraph>
      <paragraph label="Proposition 12">
       Global inefficiency of clique-wise efficiencyIf the negotiation topology is not complete, then the social welfare of a clique-wise efficient allocation can be arbitrarily far from the optimum. This holds even when all agents share the same single-minded valuation function.
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}G=(N,E) be a graph that is missing at least one edge. W.l.o.g., assume that agent 1 is not connected to agent 2. Let the set of goods be {a mathematical formula}{g1,g2}. Assume all agents share the same single-minded valuation function v with {a mathematical formula}v({g1,g2})=1 and {a mathematical formula}v(S)=0 for all bundles {a mathematical formula}S≠{g1,g2}. Consider the allocation A in which agent 1 owns {a mathematical formula}g1 and agent 2 owns {a mathematical formula}g2. In allocation A, if no payments have been made in the past, the utility of every agent is equal to 0, and thus so is social welfare. Nevertheless, A is clique-wise efficient, because any clique of G must be a subset of either {a mathematical formula}{1,3,4,…,n} or {a mathematical formula}{2,3,4,…,n}, i.e., no clique collectively owns both {a mathematical formula}g1 and {a mathematical formula}g2. On the other hand, any allocation where one agent owns both items has a social welfare of 1. Thus, the ratio between the social welfare of efficient allocations and the social welfare of clique-wise efficient allocations cannot be bounded by a constant.  □
      </paragraph>
      <paragraph>
       This result may call into question the usefulness of Definition 8. While our definition of envy with respect to a graph is very natural and reaching GEF states seems indeed desirable, it is questionable whether it is at all possible to relativise the standard notion of efficiency with respect to a negotiation topology in a meaningful manner. Our interest in the purely technical definition of clique-wise efficiency given above stems from the fact that it will be helpful in characterising conditions under which convergence to a GEF state can be guaranteed (as will become clear in the sequel). But first we prove a convergence result for clique-wise efficiency:
      </paragraph>
      <paragraph label="Lemma 13">
       Clique-wise efficient outcomesAny sequence of IR clique-deals will eventually result in a clique-wise efficient allocation of goods.
      </paragraph>
      <paragraph label="Proof">
       There can be no infinite sequence of deals (clique-deals or otherwise), because any deal strictly increases social welfare and the set of possible allocations is finite. Now let A be the terminal allocation. For the sake of contradiction, suppose that A is not clique-wise efficient. Then there exists an allocation {a mathematical formula}A′ that is a clique-variant of A such that {a mathematical formula}sw(A)&lt;sw(A′). But then, by Lemma 3, {a mathematical formula}δ=(A,A′) must be IR (besides being a clique-deal). This contradicts our assumption of A being a terminal allocation.  □
      </paragraph>
      <paragraph>
       Lemma 13 generalises Theorem 1. The latter corresponds to the case of a fully connected graph. While Lemma 13 guarantees clique-efficient outcomes, it does not say anything about which clique-efficient allocation will be reached. For most graphs there will be a range of clique-efficient allocation of varying quality in terms of global efficiency (in this sense the concept is similar to that of Pareto efficiency). There is no guarantee that we will end up with the “best” clique-efficient allocation. And even if it does, as Proposition 12 shows, global efficiency may still be arbitrarily bad. Nevertheless, as we will see next, clique-wise efficiency is a sufficiently strong notion to serve as a basis for negotiating envy-free states.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Convergence
      </section-title>
      <paragraph>
       We now prove a convergence theorem for GEF states, which extends Theorem 8 to the framework with a negotiation topology: we show that under the same conditions (on the valuation functions and for a particular choice of payment scheme), any sequence of IR deals that respect the negotiation topology will result in a GEF state.
      </paragraph>
      <paragraph label="Theorem 14">
       Convergence on graphsIf all valuations are supermodular and if initial equitability payments have been made, then any sequence of IR clique-deals using the GUPF will eventually result in a GEF state.
      </paragraph>
      <paragraph label="Proof">
       Recall from the proof of Theorem 8 that the use of the GUPF together with initial equitability payments ensures that we get a payment balance satisfying {a mathematical formula}π(i)=vi(A)−sw(A)/n for every state {a mathematical formula}(A,π) reached during negotiation and every agent {a mathematical formula}i∈N. By Lemma 13, negotiation will eventually terminate and the final allocation {a mathematical formula}A⁎ will be clique-wise efficient. The associated payment balance will be {a mathematical formula}π⁎(i)=vi(A⁎)−sw(A⁎)/n. We need to show that the state {a mathematical formula}(A⁎,π⁎) must be GEF whenever all valuations {a mathematical formula}vi are supermodular. Let i and j be any two agents. If i cannot see j then we are done. Otherwise, i and j are part of a clique, and due to the clique-wise efficiency of {a mathematical formula}A⁎, giving both {a mathematical formula}A⁎(i) and {a mathematical formula}A⁎(j) to i will not increase the sum of valuations for this clique any further. Hence, by the argument familiar from Section 4.1, i does not envy j in state {a mathematical formula}(A⁎,π⁎).  □
      </paragraph>
      <paragraph>
       Theorem 14 means that agents can negotiate in a distributed manner, guided only by their own rational interests and limited to their “neighbourhoods” as given by the cliques of the negotiation topology, and—as long as all the side conditions are satisfied—a state that is envy-free according to all agents (whose vision is limited by the negotiation topology) will eventually emerge. In particular, agents can go ahead and negotiate any beneficial deals, without fear of getting stuck in a local optimum.
      </paragraph>
      <paragraph label="Example 4">
       We consider once more the allocation problem of Table 1, but now the agents are arranged on a line, with agent 1 in the middle position, i.e., {a mathematical formula}E={(1,2),(2,1),(1,3),(3,1)}. Suppose the initial allocation is {a mathematical formula}A0=〈{g2,g3},{g1,g4},∅〉. Table 4 shows the allocations visited during a sequence consisting of a single IR clique-deal, which culminates in a clique-wise efficient state {a mathematical formula}(A′,π′), in which the final payment balances of the agents are as follows: {a mathematical formula}π′(1)=12/3, {a mathematical formula}π′(2)=6/3, and {a mathematical formula}π′(3)=−18/3. The final utility of each agent is 18/3. It can be checked that the following statements hold.
      </paragraph>
      <list>
       <list-item label="•">
        Agent 2 does not envy agent 1, as {a mathematical formula}u2(A′(1),π′(1))=8−12/3=12/3&lt;18/3
       </list-item>
       <list-item label="•">
        Agent 3 does not envy agent 1, as {a mathematical formula}u3(A′(1),π′(1))=0−12/3=−12/3&lt;18/3
       </list-item>
       <list-item label="•">
        Agent 1 does not envy agent 2 nor agent 3, as both:
       </list-item>
      </list>
      <paragraph>
       A critical point in Theorem 14 is the use of the GUPF, as this payment function does not respect the negotiation topology. However, it is easy to show that there can be no clique-wise payment function (a payment function giving non-zero payments only to agents belonging to a particular maximal clique within which the deal is taking place) that would allow us to achieve a convergence result for GEF states. To see this, consider the following example. Suppose again there are three agents on a line, the payment balance is currently 0 for all agents, and the valuation function of agent 3 is {a mathematical formula}v3(S)=0 for any {a mathematical formula}S⊆G. Then any deal between agents 1 and 2, where the former makes a non-zero payment to the latter, will render agent 3 envious of agent 2.
      </paragraph>
      <paragraph>
       A variation of this example shows that even when there exists a clique-wise payment function leading to a GEF state, the exact amount of the payments to be made may depend on agents outside the clique where the deal is taking place. For the same negotiation topology as above, let again {a mathematical formula}v3(S)=0 for any {a mathematical formula}S⊆G, but now suppose that agent 3 has benefited from a previous deal in monetary terms, i.e., {a mathematical formula}π(3)=x for some {a mathematical formula}x&lt;0. Then an envy-eliminating deal between agents 1 and 2 should be such that it brings the payment balance of agent 2 to at least x as well (which may or may not be possible, depending on the scenario at hand). This shows that the best possible clique-wise payment function may not be identifiable locally.
      </paragraph>
      <paragraph>
       A positive point to be made about the GUPF is that the payments to non-involved agents (in particular those outside the clique where the deal is taking place) solely depend on the social surplus generated by the deal and the overall number of agents in the system. So agents do only need to be “aware” of agents they cannot “see” in so far as they need to know their overall number. This arguably corresponds well to human society: our sphere of influence may be very much restricted to a small section of society defined by the social network we belong to, but we are still aware of some basic facts concerning society as a whole (such as the number of its members).
      </paragraph>
      <paragraph>
       Finally, in analogy to Theorem 5, Theorem 11, if all valuation functions are modular, then we can strengthen Theorem 14 and prove convergence by means of IR 1-deals between connected agents using our by now familiar technique.
      </paragraph>
      <paragraph label="Theorem 15">
       GEF outcomes by 1-dealsIf all valuation functions are modular and if initial equitability payments have been made, then any sequence of IR 1-deals between pairs of connected agents using the GUPF will eventually result in a GEF state.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Path length
      </section-title>
      <paragraph>
       Just as we did for Theorem 4, Theorem 8, also for Theorem 14 we may ask how many deals are required before the system converges. Now the bounds on the longest (as well as the shortest) path will depend on the negotiation topology. At one extreme, if the graph is fully connected then Theorem 14 reduces to Theorem 8 and we obtain the same bounds as before. In particular, {a mathematical formula}nm−1 will always be an upper bound on the longest path. At the other extreme, if no two agents are connected to each other, then no deals are possible, and the upper bound reduces to 0. In general, it is clear that the sparser the graph, the shorter the longest path to convergence we can construct. The question now arises whether there is a class of graphs that is relatively sparse (but still natural and attractive for applications) that would result in a significant reduction of the length of the longest possible path. The answer to this question, unfortunately, is negative. As we will see next, even if agents are arranged on a line (a highly simplistic negotiation topology), there may still be a number of IR deals that is exponential in the number of goods.
      </paragraph>
      <paragraph label="Proposition 16">
       Path length for line topologySuppose the negotiation topology{a mathematical formula}G=(N,E)is a line:{a mathematical formula}E={(i,j)∈N2‖i−j|=1}. Then we can find a valuation function for each agent such that there exists a sequence of IR clique-deals of length{a mathematical formula}(2m−1)⋅(n−1).
      </paragraph>
      <paragraph label="Proof">
       Suppose the agents have the valuation functions defined in the proof of Lemma 6 and initially allocate all goods to agent 1. Then agents 1 and 2 can go through all {a mathematical formula}2m allocations that divide all goods between the two of them and end up in the allocation where agent 2 owns all items (that is, there are {a mathematical formula}2m−1 IR deals between them). We can do the same for every one of the {a mathematical formula}n−1 pairs {a mathematical formula}(i,i+1) of connected agents and thus end up with a path of the claimed length of {a mathematical formula}(2m−1)⋅(n−1) deals.  □
      </paragraph>
      <paragraph>
       Note that our construction is independent of the payment scheme used. In particular, it applies in case the payment scheme of Theorem 14 is in operation.
      </paragraph>
      <paragraph>
       Interestingly, the upper bound of the shortest path may increase as the graph connecting the agents becomes sparser, simply because this means that some transactions cannot be executed as a single deal anymore. For the scenario described in the proof of Proposition 16 the shortest path would be {a mathematical formula}n−1 (rather than 1, the bound for fully connected graphs): we can reach the social optimum by implementing one deal per pair of neighbouring agents.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Degrees of envy and computational complexity
     </section-title>
     <paragraph>
      The convergence theorems of the previous two sections show that envy-freeness can be guaranteed for the outcome of a distributed negotiation process, under specific assumptions. But this is certainly not the final word on the matter. The payment scheme used in these theorems introduces a non-local element, in the sense that it redistributes the social surplus over the whole of society. One may ask how a local payment function, such as the LUPF, would fare in comparison. Also, one could object to the requirement that initial payments have to be made. The restriction to supermodular valuation functions in Theorem 8, Theorem 14 is another limitation. Lastly, our convergence theorems do not say how envy evolves over the course of negotiation. Because negotiation can become very long in practice, it is possible that the process will have to be stopped before completion. In that event, it would be valuable to be able to guarantee some monotonicity properties—but with respect to what parameter?
     </paragraph>
     <paragraph>
      To be able to address such questions, more than the mere classification of a negotiation state as being either envy-free or not is needed. We require a way to measure the degree of envy in a society. In this section, we will propose a systematic approach to defining measures for assessing the degree of envy. We propose to analyse the degree of envy of a society as a three-level aggregation process, starting with envy between two agents, over envy of a single agent towards everyone else, to eventually provide a definition for the degree of envy of a society. We also formulate a number of fundamental axioms that any reasonable measure of envy, not only the concrete measures proposed here, should satisfy. Towards the end of the section we then prove a theorem on the computational complexity of the problem of finding an IR deal that reduces envy according to any such measure.
     </paragraph>
     <section label="6.1">
      <section-title>
       Envy between two individual agents
      </section-title>
      <paragraph>
       How much does agent i envy agent j in state {a mathematical formula}(A,π)? Any measure of envy between i and j will be based on {a mathematical formula}Δi,j(A,π)=ui(A(j),π(j))−ui(A(i),π(i)), the difference in utility that i assigns to their own lot and that of j. If this number is negative or equal to 0, then agent i does not envy agent j, nor does she in case she cannot see agent j in the social network. This gives rise to a matrix of dimension {a mathematical formula}n×n, with entries {a mathematical formula}ei,j:{a mathematical formula} We now use {a mathematical formula}ei,j to define two different measures for the degree of envy between individual agents:{a mathematical formula} The second measure ({a mathematical formula}ebool) only allows us to specify whether or not i envies j. In many cases this is all that is needed. The first measure is useful if we also want to say how much i envies j. In principle one could also consider the notion of “negative envy” [1], i.e., one could consider treating the case of {a mathematical formula}Δi,j(A,π)&lt;0 differently from the case where that difference is exactly 0 or where i cannot see j, but we will not pursue this route here.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Degree of envy of a single agent
      </section-title>
      <paragraph>
       How envious is a single agent i in state {a mathematical formula}(A,π)? This notion considers the agent in relation to all the other agents. That is, we need to aggregate the individual envies that i experiences vis-à-vis each of the other agents. The most natural aggregation operators are max and summation, but other options are possible as well.{a mathematical formula} Here op may stand for either raw or bool. For instance, {a mathematical formula}emax,raw(i) measures how much i envies the agent she envies the most, while {a mathematical formula}esum,bool(i) counts the number of agents envied by i.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Degree of envy of a society
      </section-title>
      <paragraph>
       Given the degrees of envy of each individual agent in a system for a given negotiation state, we can now define suitable aggregation operators to yield the degree of envy for the agent society as a whole. As for the aggregation of individual preferences to obtain a social preference ordering [24], there are a multitude of different options available for doing this. Here again, just as for the case of the degree of envy of a given agent, we only list two options that appear particularly appropriate in our context, namely max and summation.{a mathematical formula} Using the max-operator means focusing on the most envious agent of the society (whatever operator was chosen to measure that), while summation (or, equivalently, averaging) provides a more global picture of the situation. The former has an egalitarian flavour, while the latter is utilitarian in nature.
      </paragraph>
      <paragraph>
       Our framework allows us to define a range of different measures for measuring envy. Several of these have been proposed in the literature before:
      </paragraph>
      <list>
       <list-item label="•">
        Feldman and Kirman [37] make several proposals for how to measure envy. Their first suggestion is to count the number of pairs of agents where the first agent envies the second ({a mathematical formula}esum,sum,bool). They also define two alternative measures for the degree of envy of a single agent, one of which corresponds to our {a mathematical formula}esum,raw(i) and the other of which takes negative envies into account (so is not covered by our system). They then propose to measure the degree of envy of a society by means of a weighted sum of either one of their measures for individual envy. Thus, their discussion includes, in particular, the measure {a mathematical formula}esum,sum,raw.
       </list-item>
       <list-item label="•">
        Lipton et al. [12] work with two envy measures. The first of these is the “maximum envy between any pair of players” ({a mathematical formula}emax,max,raw). Their second envy measure is the maximum envy ratio, defined as {a mathematical formula}maxi,j∈N⁡{ui(A(j),π(j))ui(A(i),π(i)),1}, which is not covered by our system. Caragiannis et al. [15] also work with {a mathematical formula}emax,max,raw and Netzer et al. [23] use both {a mathematical formula}emax,max,raw and {a mathematical formula}esum,max,raw.
       </list-item>
       <list-item label="•">
        Brams et al. [38] refer to two measures of envy: the “number of envies of all players” ({a mathematical formula}esum,sum,bool) and the “maximum number of envies of an individual player” ({a mathematical formula}emax,sum,bool).
       </list-item>
       <list-item label="•">
        Lindner and Rothe [39] also work with {a mathematical formula}esum,sum,bool, at least implicitly—explicitly they count the number of ordered pairs of agents such that the first agent does not envy the second.
       </list-item>
      </list>
      <paragraph>
       Thus, our simple system covers many of the measures of envy proposed in the literature. Another obvious choice for measuring envy is the number of envious agents in a society ({a mathematical formula}esum,max,bool). Finally, {a mathematical formula}emax,max,bool should be considered a degenerate measure of envy, as it only allows us to distinguish between situations that are envy-free and those that are not.
      </paragraph>
      <paragraph>
       As noted above, one of the measures proposed by Lipton et al. [12] does not fit our system, as that measure is grounded in utility ratios rather than utility differences. Such ratio-based measures are useful when establishing approximability results (as envy-freeness then corresponds to a value of 1 rather than 0) and have been used by several authors [12], [40], [23]. In related work, Nguyen and Rothe [40] have adapted an early version of our three-stage system [1] to define a family of ratio-based measures of envy. The basic idea of measuring degrees of envies has also been adapted to the context of matching [41].
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Axioms for envy measures
      </section-title>
      <paragraph>
       Next, we want to formulate some minimal requirements on any reasonable measure of envy, which will allow us to state results regarding the reduction of envy in generic terms.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}envy:(2G)N×RN→R be a measure of envy, i.e., a function mapping states to the non-negative reals, that satisfies {a mathematical formula}envy(A,π)⩾0 for every state {a mathematical formula}(A,π). Every state {a mathematical formula}(A,π) gives rise to a matrix {a mathematical formula}(ei,j)i,j∈N of local envies. Our most fundamental requirement on {a mathematical formula}envy(.,.) is that this function must be computable from the values recorded in the matrix alone. We call any measure of envy that satisfies this requirement a proper measure of envy. Thus, we may think of a proper measure of envy as a function {a mathematical formula}envy:Rn×n→R mapping envy matrices to the reals.{sup:3}
      </paragraph>
      <paragraph>
       Beyond the basic requirement of {a mathematical formula}envy(.,.) being proper, we propose four natural axioms that any reasonable measure of envy should satisfy:
      </paragraph>
      <list>
       <list-item label="•">
        Discernibility: It must be the case that {a mathematical formula}envy((eij)i,j∈N)=0 if and only if {a mathematical formula}ei,j=0 for all agents {a mathematical formula}i,j∈N. Thus, the degree of envy of a state should be zero if and only if it is an envy-free state. This excludes situations where states that are “almost” envy-free are not discernible from the truly envy-free states by using the measure of envy in question.
       </list-item>
       <list-item label="•">
        Dominance: If {a mathematical formula}(ei,j)i,j∈N and {a mathematical formula}(ei,j′)i,j∈N are envy matrices satisfying {a mathematical formula}ei,j⩾ei,j′ for all agents {a mathematical formula}i,j∈N, then we must have {a mathematical formula}envy((ei,j)i,j∈N)⩾envy((ei,j′)i,j∈N). Thus, if all local envies either increase or stay the same, then overall envy cannot go down.
       </list-item>
       <list-item label="•">
        Source Anonymity: If {a mathematical formula}(ei,j)i,j∈N and {a mathematical formula}(ei,j′)i,j∈N are envy matrices such that there exists a permutation {a mathematical formula}σ:N→N for which {a mathematical formula}ei,j=eσ(i),j′ for all agents {a mathematical formula}i,j∈N, then we must have {a mathematical formula}envy((ei,j)i,j∈N)=envy((ei,j′)i,j∈N). In other words, {a mathematical formula}envy(.,.) is indifferent under permutations of the rows of the matrix of local envies. Thus, every individual agent's envy is equally important.
       </list-item>
       <list-item label="•">
        Target Anonymity: If {a mathematical formula}(ei,j)i,j∈N and {a mathematical formula}(ei,j′)i,j∈N are envy matrices such that there exist an agent {a mathematical formula}i⁎∈N and a permutation {a mathematical formula}σ:N→N for which {a mathematical formula}ei⁎,j=ei⁎,σ(j)′ for all {a mathematical formula}j∈N and {a mathematical formula}ei,j=ei,j′ for all {a mathematical formula}i,j∈N with {a mathematical formula}i≠i⁎, then we must have {a mathematical formula}envy((ei,j)i,j∈N)=envy((ei,j′)i,j∈N). In other words, {a mathematical formula}envy(.,.) is indifferent under permutations of the elements of a single row of the envy matrix. Thus, we do not care about who an individual agent envies, but only about how many agents she envies and to what degree she does so.
       </list-item>
      </list>
      <paragraph>
       A weaker form of target anonymity would merely require indifference under permutations of the columns of the matrix of local envies. Such a weaker axiom would allow us to distinguish, say, a situation where {a mathematical formula}n−1 agents all envy the nth agent from a situation where the same {a mathematical formula}n−1 agents all envy a different agent, which may be useful in some circumstances.
      </paragraph>
      <paragraph>
       Source and target anonymity together mean that we can think of the input to the function envy as a multiset of multisets of local envies, rather than as a matrix of envies. Note that we do not require {a mathematical formula}envy(.,.) to be computable from the single multiset of all local envies—that would be an even stronger requirement that, for instance, would be violated by the measure of envy counting the number of envious agents in a society ({a mathematical formula}esum,max,bool).
      </paragraph>
      <paragraph>
       It is readily verified that all of the concrete measures of envy for a society defined earlier meet our axiomatic requirements:
      </paragraph>
      <paragraph label="Proposition 17">
       Envy measuresLet{a mathematical formula}op1,op2∈{max,sum}and let{a mathematical formula}op3∈{raw,bool}. Then{a mathematical formula}eop1,op2,op3is a proper measure of envy that satisfies discernibility, dominance, target anonymity, and source anonymity.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Complexity of reducing envy
      </section-title>
      <paragraph>
       The objectives of achieving envy-freeness and of maintaining individual rationality during negotiation are not entirely compatible. This is why we have required initial payments for our convergence results. Indeed, as the following example shows, without initial payments, there can be negotiation states such that no IR deal would allow us to eliminate envy. Consider a scenario with two agents and one good:{a mathematical formula} Suppose agent 1 holds g in the initial allocation {a mathematical formula}A0. There is only a single possible deal, which amounts to passing g to agent 2, and which will result in the efficient allocation {a mathematical formula}A⁎. How should payments be arranged? To ensure that the deal is IR for both agents, agent 2 should pay agent 1 any amount in the open interval {a mathematical formula}(4,7). On the other hand, to ensure that the final state is envy-free, agent 2 should pay any amount in the closed interval {a mathematical formula}[2,3.5]. The two intervals do not overlap.
      </paragraph>
      <paragraph>
       So it is a relevant question whether a given negotiation state admits a deal that would not only be IR but that also reduces envy in the system (or, as a special case, that completely eliminates envy). As a final contribution, we now want to analyse the computational complexity of this problem, for arbitrary measures of envy of the form {a mathematical formula}envy(.,.). For the purposes of stating the problem, let a negotiation problem be specified by a negotiation topology {a mathematical formula}G=(N,E), a set of goods {a mathematical formula}G, and a profile of valuations {a mathematical formula}〈v1,…,vn〉.{a mathematical formula} That is, WIER asks whether, for a given negotiation state, there exists a clique-deal that is IR (second condition) and for which payments can be arranged such that the degree of envy is reduced (third condition).
      </paragraph>
      <paragraph>
       WIER is related to the Welfare Improvement problem (WI) studied in the literature [11], which is identical to WIER, except that it does not impose any conditions on envy. WI is known to be NP-complete for a number of languages for representing valuation functions (i.e., the input to the problem). Despite this similarity, we are unaware of any simple reduction from WI to WIER, which could be used to prove NP-completeness of WIER.{sup:4} Instead, below we will provide a reduction from the fundamental Clique problem. Clearly, there is no chance for WIER being computable in polynomial time unless {a mathematical formula}envy(.,.) is computable in polynomial time, so we will require this. Regarding the language used to represent valuation functions, we will use the simplest of all such languages, namely the language for expressing single-minded valuations [42]. Specifying a valuation function in this setting amounts to fixing one bundle and its value. Finally, our result applies to every proper envy measure that satisfies the discernibility axiom, rather than just to the specific measures defined earlier.
      </paragraph>
      <paragraph label="Theorem 18">
       Complexity of WIERWIER is NP-complete for single-minded agents for every proper measure of envy that is polynomial-time computable and that satisfies the discernibility axiom.
      </paragraph>
      <paragraph label="Proof">
       NP-membership follows from the fact that the conditions of WIER can be verified in polynomial time for any proposed solution state.To establish NP-hardness we give a polynomial-time reduction from the NP-hard Clique problem [43], defined as follows: Given an undirected graph {a mathematical formula}G=(V,E) and a positive integer {a mathematical formula}K⩽|V|, is it the case that G contains a clique of size K or larger? W.l.o.g., assume {a mathematical formula}K⩾2.Given a Clique instance with {a mathematical formula}|V|=n, we build the following instance of WIER. Fix some {a mathematical formula}Ω&gt;2K and some positive {a mathematical formula}ϵ&lt;1. There are 2n goods in the system, {a mathematical formula}G=R∪D with {a mathematical formula}R={r1,…,rn} (the “real” goods) and {a mathematical formula}D={d1,…,dn} (the “dummy” goods). There furthermore are {a mathematical formula}2n+1 agents with single-minded valuations, meaning that they each value just a single bundle of goods (and all their supersets). We indicate this single bundle and its value for each agent:
       <list>
        a single auctioneer agent{a mathematical formula}xa, with {a mathematical formula}va(R)=K−1;one real agent{a mathematical formula}xir, with {a mathematical formula}vir({ri})=1, for all {a mathematical formula}i∈{1,…,n};one dummy agent{a mathematical formula}xid, with {a mathematical formula}vid({di})=Ω, for all {a mathematical formula}i∈{1,…,n}.Let us take note of the envies experienced in this state. The auctioneer envies each of the real agents: her own utility is
       </list>
       <paragraph>
        {a mathematical formula}K−1, but each real agent has a monetary amount of {a mathematical formula}K−ϵ. The real agents and the dummy agents do not experience any envy. In particular, no real agent envies the auctioneer, because {a mathematical formula}K−ϵ (the amount of money she owns) is greater than 1 (the utility she ascribes to the bundle held by the auctioneer).Now suppose there is a clique of size at least K in the original graph. We will show how to construct an envy-reducing IR clique-deal in this case. The clique in question must be part of some maximal clique (which could be that clique itself). Let {a mathematical formula}K′⩾K be the size of that maximal clique. Let us call the real agents corresponding to the vertices in the maximal clique the clique agents and let us call the remaining real agents the non-clique agents. Consider the following deal, starting from the initial state described earlier and shown in Fig. 2:
       </paragraph>
       <list>
        <list-item label="•">
         Each clique agent {a mathematical formula}xir obtains item {a mathematical formula}ri from the auctioneer and pays her an amount of {a mathematical formula}(K−ϵ)/K′ in return, i.e., the auctioneer obtains a total amount of {a mathematical formula}K−ϵ.
        </list-item>
        <list-item label="•">
         The remaining real goods are also given to the clique agents, in such a way that no non-clique agent {a mathematical formula}xir can see the item {a mathematical formula}ri she desires. This is possible due to the maximality of the clique (for every non-clique agent there exists a clique agent she is not connected to).
        </list-item>
       </list>
       <paragraph>
        This deal is an IR clique-deal: all the agents involved are fully connected to each other, and social welfare increases from {a mathematical formula}n⋅Ω+(K−1) to {a mathematical formula}n⋅Ω+K′. This deal is also envy-reducing. Indeed, this deal reduces envy to zero (which, by the discernibility axiom, makes it an envy-reducing deal). To see this, first note that nobody envies anyone for goods anymore (nobody can see another agent holding a good she desires herself), so we only need to compare every agent's utility with the monetary balances of the agents she can see:
       </paragraph>
       <list>
        <list-item label="•">
         Each dummy agent has utility {a mathematical formula}Ω−(K−ϵ)&gt;K, while no agent possesses an amount of money exceeding K.
        </list-item>
        <list-item label="•">
         The auctioneer has an amount of {a mathematical formula}K−ϵ (which is also her utility), while no agent she can see either holds a bundle she desires or owns an amount of money exceeding {a mathematical formula}K−ϵ. The same is true for every non-clique agent.
        </list-item>
        <list-item label="•">
         Each clique agent {a mathematical formula}xir has utility {a mathematical formula}1+(K−ϵ)−(K−ϵ)/K′, composed of the value she ascribes to {a mathematical formula}ri, the amount of money she held before the deal, and the payment she made to the auctioneer. But this sum is strictly greater than {a mathematical formula}K−ϵ, the maximal amount of money held by any of the agents she can see.
        </list-item>
       </list>
       <paragraph>
        This concludes the first direction of the proof: if there is a clique of size K, then there exists an envy-reducing IR clique-deal. For the other direction, suppose the largest clique in the given graph is strictly smaller than K. We will see that then there exists no IR clique-deal (and thus certainly no such deal that would also be envy-reducing). So consider all maximal cliques of agents that might conduct a deal for the state shown in Fig. 2:
       </paragraph>
       <list>
        <list-item label="•">
         No group of real agents could raise enough money to reimburse the auctioneer for giving up some or all of the real goods.
        </list-item>
        <list-item label="•">
         No real agent would have an interest in buying a dummy good from a dummy agent.
        </list-item>
       </list>
       <paragraph>
        Hence, if there is no clique of size K, then no deal is possible. This concludes the proof.  □
       </paragraph>
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>