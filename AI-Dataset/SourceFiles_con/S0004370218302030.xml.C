<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Online spatio-temporal matching in stochastic and dynamic domains.
   </title>
   <abstract>
    Online spatio-temporal matching of servers/services to customers is a problem that arises at a large scale in many domains associated with shared transportation (e.g., taxis, ride sharing, super shuttles, etc.) and delivery services (e.g., food, equipment, clothing, home fuel, etc.). A key characteristic of these problems is that the matching of servers/services to customers in one stage has a direct impact on the matching in the next stage. For instance, it is efficient for taxis to pick up customers closer to the drop off point of the customer from the first stage of matching. Traditionally, greedy/myopic approaches have been adopted to address such large scale online matching problems. While they provide solutions in a scalable manner, due to their myopic nature, the quality of matching obtained can be improved significantly (demonstrated in our experimental results). In this paper, we present a multi-stage stochastic optimization formulation to consider potential future demand scenarios (obtained from past data). We then provide an enhancement to solve large scale problems more effectively and efficiently online. We also provide the worst-case theoretical bounds on the performance of different approaches. Finally, we demonstrate the significant improvement provided by our techniques over myopic approaches and two other multi-stage approaches from literature (Approximate Dynamic Programming and Hybrid Multi-Stage Stochastic optimization formulation) on three real world taxi data sets.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In many spatio-temporal problems associated with shared transportation [2], [3], [4] which includes taxis, ride sharing, super shuttles, etc., customers have to be assigned to servers (e.g., taxis, shuttles) in an online fashion to optimize the revenue or quality of service. Also in case of emergency services [5] such as ambulances, fire trucks, etc. and delivery services [6], [7] involving pickup and delivery of food, equipment, clothing, home fuel etc., effective online matching of customers to servers is of great value.
     </paragraph>
     <paragraph>
      The wide usage of applications such as Uber, Lyft, etc. is a testament to the importance of doing matching well and in quick time. In these applications, a set of available taxis are matched to the customers that are looking for taxis. A key observation that is not exploited in such applications and in most existing literature is that after taking the matched customer to their destination location, the taxi will be best served in next stage of assignment to customers typically around the destination location. In this paper, we are specifically interested in considering such dependence (e.g., assignment for a taxi in the second stage is dependent on the assignment in the first stage) in matching across multiple stages. Specifically, we focus on online matching in domains where:
     </paragraph>
     <list>
      <list-item label="•">
       Customer demand is uncertain and time dependent, with data available about past customer demand;
      </list-item>
      <list-item label="•">
       Problems are at a societal scale (with thousands of customers and servers) with a need to make online decisions; and
      </list-item>
      <list-item label="•">
       There is a need or an opportunity to optimize revenue or quality of service (e.g., time to pick up customers or time to delivery);
      </list-item>
     </list>
     <paragraph>
      Given the challenging nature of the problems (stochasticity, dynamism, societal scale, online, multi-stage), most existing work on relevant problems (described in Section 2) has focused on myopic algorithms [8], [9] like greedy and randomized ranking. While these approaches have good competitive ratios in case of online bipartite matching (single stage), they have obvious inefficiencies in handling multi-stage problems due to their myopic nature. To address these, there has been research on multi-stage stochastic models and Approximate Dynamic Programming approaches that consider expected demand for the future stages. However, these approaches have been limited to small scale problems and in restricted settings [10], [11], [12], [13], [7], [14], [15].
     </paragraph>
     <paragraph>
      In this paper, we address the key limitations of previous work by providing the following contributions:
     </paragraph>
     <list>
      <list-item label="•">
       We first formalize the offline and online spatio-temporal matching problems. The offline problem considers that the customer requests at every decision epoch are known beforehand. The online problem on the other hand considers that only the current decision epoch customer requests are known and the future decision epoch requests arrive according to some partially known (through past demand scenarios) distribution.
      </list-item>
      <list-item label="•">
       We then provide a two-stage stochastic optimization formulation, which considers samples of future customer demand (typically obtained from historical data) for finding the assignment of servers to customers. We also provide a multi-stage extension.
      </list-item>
      <list-item label="•">
       Given the large scale of problems of interest with thousands of servers and customers, we provide a decomposition of the above formulation to improve parallelism in handling future demand.
      </list-item>
      <list-item label="•">
       We provide the theoretical results on competitive ratios for myopic and two-stage algorithms for online spatio-temporal matching problems.
      </list-item>
      <list-item label="•">
       Apart from considering randomly generated problems, we have also evaluated our approach on datasets of three major taxi companies. We compare against myopic algorithms (typically employed by standard taxi matching applications) such as greedy and one-stage bipartite optimal assignment. In addition, we also compare against the Approximate Dynamic Programming (ADP) approach that has been successfully applied in many resource allocation problem [11], [12], [13] and Hybrid Multi-Stage Stochastic optimization (HSS) approach used for the truckload assignment problem [10]. We show that our multi-stage formulation can be solved in times that are competitive to these approaches, while providing significantly better solutions.
      </list-item>
     </list>
     <paragraph>
      We provide a detailed description of the related work, along with a background of existing methods in Section 2. We provide a model and a linear optimization formulation to represent the offline spatio-temporal matching problem in Section 3. We then describe the online variant along with a linear optimization model in Section 4. A decomposition method to improve the scalability in solving the optimization model is also presented in the same section. In Section 5, we describe the key assumptions and how they can be relaxed. Finally, in Section 6, we provide a detailed experimental analysis of our methods against existing benchmarks on three real world taxi data sets and specially created synthetic scenarios. In the appendix, we provide detailed proofs for all the propositions described in Sections 3 and 4. In the appendix, we also provide the details of Approximate Dynamic Programming (ADP) and Hybrid Multi-Stage Stochastic optimization (HSS) approaches used in experimental comparison.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      We now describe the multiple threads of research in online sequential decision making that are of relevance to this paper. Online algorithms [16] typically consider requests that are revealed incrementally over time and algorithms have to make decisions based on the requests that are revealed. The key threads of research that are of relevance are: online matching, online multi vehicle pickup and delivery, online MDPs and online stochastic optimization algorithms.
     </paragraph>
     <section label="2.1">
      <section-title>
       Online matching
      </section-title>
      <paragraph>
       A matching, M in a graph {a mathematical formula}G(V,E) is defined as the set of edges {a mathematical formula}M⊂E such that for every {a mathematical formula}v∈V there is at most one edge in M incident on v. In classical online bipartite matching problem [8], one side of the vertices is known and the other side of the vertices arrive online. This is formally defined as a graph {a mathematical formula}G(U,V,E) where vertices in the set U are known and vertices in the set V appear online. The goal is to maximize the size of the matching M.
      </paragraph>
      <paragraph>
       A simple generalization of the online bipartite matching is the weighted case where vertices or edges have weights associated with them and the goal is to maximize the total weight of the matching. This problem has applications in online advertising employed by Yahoo, Google etc. Specifically in such applications, the goal is to optimize the allocation of a fixed advertising space to incoming advertisers who typically arrive at different times.
      </paragraph>
      <paragraph>
       We describe the commonly used approaches for solving online bipartite matching problems. In the experimental section, we compare our proposed approach with the following approaches.
      </paragraph>
      <list>
       <list-item label="1.">
        Greedy: Greedy algorithm matches the incoming vertex with the best available choice. In case of weighted models, it matches with the maximum weighted vertex or edge. Greedy algorithm is shown to have a competitive ratio{sup:1} of {a mathematical formula}12[8].
       </list-item>
       <list-item label="2.">
        Randomized greedy: The randomized greedy algorithm perturbs the value of matching by multiplying it by a random number w between 0 and 1. It then greedily matches the servers to customer by using perturbed value. Goel et al. [9] show that the randomized greedy algorithm achieves a ratio of {a mathematical formula}1−1e for the vertex weighted bipartite matching.
       </list-item>
      </list>
      <paragraph>
       In classical online bipartite matching, vertices appear one by one. In our model, discussed in the introduction, a group of requests (possibly more than one) arrive simultaneously at each decision epoch, therefore we can apply standard bipartite matching algorithm on the currently available partial graph. We call this One-Stage Algorithm as it only considers requests available at one stage (the current decision epoch). One-Stage Optimal finds the maximum weighted bipartite matching between available vertices at every decision epoch by solving a linear program. Although most work in online bipartite matching addresses the problem where one side is fixed [17], [18], [19], results in [20] show that greedy algorithm achieves a competitive ratio of 1/2 when both sides of vertices appear online. Recently in Wang et al. [21] an algorithm based on water-filling algorithm has been proposed which achieves a competitive ratio of 0.526 in case both sides of vertices appear online.
      </paragraph>
      <paragraph>
       While there are similarities, there are multiple differences in our work from research in online matching:
      </paragraph>
      <list>
       <list-item label="•">
        We consider a multi-stage problem, where there are multiple connected rounds of bipartite matching. Therefore, unlike in online bipartite matching that assigns one service to only one customer, in this paper, we match one service to multiple customers (with one customer at any specific point) over time. A recent work by Dickerson et al. [22] proposes a new model for Online Matching with (offline) Reusable resources in which resources on one side are reusable, i.e., resources are matched multiple times over time but their model assumes that each resource has a fixed position and comes back to its original position before it can be matched again. This assumption is not valid for the problems of interest in this paper where position of resource (server) depends on the previous match (assignment).
       </list-item>
       <list-item label="•">
        In addition, the spatio-temporal aspect of requests (not present in traditional online matching problems) adds further computational complexity to the matching problem.
       </list-item>
       <list-item label="•">
        Finally, in terms of approaches, unlike work in online matching which has primarily considered myopic approaches, we pursue multi-stage approaches that consider potential future requests.
       </list-item>
      </list>
     </section>
     <section label="2.2">
      <section-title>
       Online multi vehicle pickup and delivery problem
      </section-title>
      <paragraph>
       Online Multi Vehicle Pickup and Delivery problems typically represent problems where there are multi-capacity servers that transport multiple goods/loads from their origins to destinations. When servers are used to move people instead of goods, the problem is referred to as dial-a-ride problem [23], [24], [25] and when all the origins or all the destinations are located at a depot, the problem is referred to as vehicle routing problem [7].
      </paragraph>
      <paragraph>
       The general representation of the dial-a-ride problems is ideally suited to represent problems faced by companies such as super shuttle (transports people from an airport to different locations in the city), uber pooling (transports customers from near by start locations to near by destination locations). These problems are hard to solve and the traditional approaches for these problems can solve only very small instances of 96 requests and 8 vehicles [26].
      </paragraph>
      <paragraph>
       The integer programming formulation, without any spatial or temporal aggregation [26], is difficult to solve and is not scalable to large scale problems and online decision making even for unit capacity. So in the online setting, the problems are solved by either using the heuristics [27], [28], [29] or by optimizing at each timestep using only current set of available requests [6], [30]. Even after considering discretization of timesteps, exact formulation of this problem involves product of variables. Even after linearizing the product terms , the formulation (shown in Appendix A) is a mixed integer program that is not scalable.
      </paragraph>
      <paragraph>
       Therefore existing work [10], [31], [12] and even our paper considers matching supply and demand at the level of zones, cities or areas (abstraction of locations) and not at the level of individual locations. That is to say, all demand and/or supply of a specific type within an area are deemed equivalent to improve scalability.
      </paragraph>
      <paragraph>
       There are multiple key differences in assumptions/constraints made in existing work on truckload assignment problem (and other similar ones) as compared to the problem of interest in this paper (e.g. taxi matching). These differences in assumptions are significant as the computational complexity class changes due to these assumptions/constraints.
      </paragraph>
      <list>
       <list-item label="•">
        Zone assignment constraints: In the existing models used for truckload assignment problem, at any timestep, truck can only be assigned to load in the same zone.{sup:2} This is a strong assumption which makes the formulation a pure network flow problem that can be solved in polynomial time. The complexity in truckload assignment comes due to other generalizations (such as returning trucks to their base locations, each truck serving multiple loads etc.). On the other hand, due to requirement of smaller duration (about 5 minutes) for picking up customers, zones cannot be very large and a server from a neighboring zone can be assigned to the customer in a zone (if it is the nearest server). These assumptions/constraints of our problem result in NP-hardness and thereby increase the complexity.
       </list-item>
       <list-item label="•">
        Time to compute dispatch strategies: Since truckload tasks typically take anywhere from 1 day to 4 days, the time available to compute a dispatch strategy is in the order of tens of minutes or even an hour. In the problem of interest of this paper, decisions on dispatch have to be decided in real time (in less than a minute) and the number of servers is in the order of thousands and demand is in the order of at least 300–400 customers per minute.
       </list-item>
       <list-item label="•">
        Representation of current and future assignments in formulation: The differences in the assumptions/constraints also introduce a key change in the formulations for modeling the problems. Unlike our approach, the existing work on truckload (and other similar domains) employ pure network flow formulations (i.e., only assigning demand from the same zone as supply) for both current and future time steps, or only for the future time step [10]. This is the reason for better approximations provided by our formulation, as shown in the non-trivial improvements in results (on an average 9%) provided by our approach over Hybrid Multi-Stage Stochastic optimization (HSS) [10] on three different taxi data sets.
       </list-item>
       <list-item label="•">
        Linear or piecewise linear approximation of value function: Existing work on the Approximate Dynamic Programming in solving fleet optimization MDPs [31], [12], [32] approximates the future value using the linear or piece-wise linear functions. While this seems to have provided good results in the truck fleet optimization problems, it is not a good approximation in the taxi fleet optimization. The value function approximation considered for fleet management problem is separable over zones but as in our case servers can be assigned from the nearby regions, the value of having one extra server in a zone will depend on the number of servers present in the nearby zones. Experimentally, our approaches provide on an average 9% improvement over ADP as well.
       </list-item>
      </list>
     </section>
     <section label="2.3">
      <section-title>
       Online MDPs
      </section-title>
      <paragraph>
       Another relevant thread of research is Online Markov Decision Processes (MDPs). In the online setting, rewards and transition functions of MDP for future timesteps are unknown. To learn these unknown reward and transition functions, following two cases are considered.
      </paragraph>
      <list>
       <list-item label="•">
        The more popular sub-thread has focused on the cases where the reward and the transition function are assumed to be stochastically stationary and the instances of the reward and the transition function are revealed depending on the action. In this case, Reinforcement Learning [33] has presented numerous techniques for learning the policies, which are guaranteed to maximize the expected value.
       </list-item>
       <list-item label="•">
        In the second sub-thread [34], [35], [36] the revealed reward and transition functions are adversarial to the executed action.
       </list-item>
      </list>
      <paragraph>
       While it is possible to represent our problem as an online MDP, the number of states and actions are exponential in the number of agents. Since the number of agents is in the thousands, it is even difficult to specify the model. For the large scale MDPs, existing works have used state aggregation [37] and Approximate Dynamic Programming methods [13] to compute policies. As described in Section 2.2, Approximate Dynamic Programming methods have been widely applied for the resource allocation problems. We used linear and piecewise linear value function approximation which are shown to work well for truckload assignment and fleet management problem [32], [12]. We provide a comparison with this approach in our experiment section. In summary, following are the differentiating factors of the work presented in this paper:
      </paragraph>
      <list>
       <list-item label="•">
        While it is possible to represent our problem as an online MDP, the number of states and actions are exponential in the number of agents. We provide an experimental comparison of our model with the Approximate Dynamic Programming approach which is generally used to solve the large scale MDPs.
       </list-item>
       <list-item label="•">
        We neither associate adversarial behavior with the nature nor do we assume stationarity with respect to reward and transition functions. Instead, we assume that the behavior is similar to what has been observed in the training demand settings.
       </list-item>
      </list>
      <paragraph>
       Given that both Online MDPs and our work are focused on online sequential decision making under uncertainty, existing work in online MDPs can benefit by adapting the following two key ideas mentioned in this paper in order to scale to problems with multiple agents:
      </paragraph>
      <list>
       <list-item label="•">
        Exploiting anonymity (lack of identity) and homogeneity of agents to address the exponential complexity associated with increasing the number of agents.
       </list-item>
       <list-item label="•">
        Exploiting decomposability across multiple samples of the future state space evolution.
       </list-item>
      </list>
     </section>
     <section label="2.4">
      <section-title>
       Online stochastic optimization
      </section-title>
      <paragraph>
       Stochastic programming is used to model the optimization problems that involve uncertainty. These models take advantage of the fact that the probability distributions which represent the data are known or can be estimated [38]. To represent the future uncertainty, multiple samples (scenarios) from the known or estimated probability distribution are considered.
      </paragraph>
      <paragraph>
       The complexity of these multi-stage stochastic programs increases with increasing the number of stages and sample scenarios [39]. Online anticipatory algorithms [40], [41], [42], [43] are generally used to solve large scale stochastic integer programs when the set of feasible decisions at each stage is finite [40]. The assumption is that there exists an offline deterministic algorithm for the application. Online anticipatory algorithms relax the non anticipativity constraints in the stochastic program and make decisions online at a time t in three steps:
      </paragraph>
      <list>
       <list-item label="•">
        Sample the distribution to obtain a subset of future scenarios.
       </list-item>
       <list-item label="•">
        Optimize each scenario for each possible decision.
       </list-item>
       <list-item label="•">
        Select the best decision over all scenarios.
       </list-item>
      </list>
      <paragraph>
       The above algorithm requires evaluating each decision for each possible sample which is computationally expensive. Hence, in general, the following two approximations are used.
      </paragraph>
      <list>
       <list-item label="•">
        Consensus: Instead of optimizing each sample for each decision, consensus optimizes each sample once. Only decisions which are optimal for a sample receive positive score, other decisions are given zero score. The decision having highest score is executed at time t.
       </list-item>
       <list-item label="•">
        Regrets: Regrets algorithm assumes the availability of an application specific regret function which gives fast approximation on the regret value of any decision. Now similar to consensus, regrets algorithm optimizes each sample once but unlike consensus, it assigns score to all decision using the application specific regret function.
       </list-item>
      </list>
      <paragraph>
       Online Anticipatory algorithms have been used in the applications like online vehicle routing, packet scheduling, reservation systems but these applications typically have a small set of feasible decisions at each stage (50–100 requests) [41], [44], [40].
      </paragraph>
      <paragraph>
       Unfortunately, in our case, the number of feasible decisions are in millions (tens of thousands of servers and hundreds/thousands of requests). Furthermore, if we are to optimize for each sample separately (using the optimization problem presented in Section 3), we can only handle very few samples within the online time constraints. Thus, the key differentiating factor of this paper is in providing approaches (relaxation and Benders Decomposition on top of the linear optimization) that improve scalability considerably to handle millions of decisions. Though Benders Decomposition is typically used to solve the large scale stochastic optimization problems [45], [46], [47], the novelty is to use this for our updated formulation to obtain competitive results.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Offline spatio-temporal matching (OSTM)
     </section-title>
     <paragraph>
      We first provide an intuitive description of the OSTM problem. We assume that the time is divided into discrete blocks of duration Δ minutes. Given a set of customer requests available at each decision epoch and the initial location of servers (e.g., taxis), the goal of the OSTM is to find a matching between servers and customer requests such that the objective function (e.g., revenue, number of requests) of the matching is optimized. The key constraint is that the requests should be assigned to a server at the decision epoch at which they become available and the server should start serving the request on assignment. On serving a customer request the server moves to the destination location of the customer request. Therefore, the location and availability of servers at each decision epoch depends on the matching performed at previous decision epochs. Formally, an OSTM problem is described using the following tuple:{a mathematical formula}
     </paragraph>
     <list>
      <list-item label="•">
       {a mathematical formula}Z is the set of all zones. A zone groups all nearby locations into one abstract entity. For instance, in the context of taxis,{sup:3} we represent each zone as an area where the distance between any two points in that area is 0.5 km.
      </list-item>
      <list-item label="•">
       {a mathematical formula}Dt represents the demand or the set of customer requests for servers at decision epoch t. Each element {a mathematical formula}j∈Dt is characterized by a tuple {a mathematical formula}〈oj,dj,Rjt〉 where {a mathematical formula}oj,dj∈Z denote the origin and destination zone of the requests and {a mathematical formula}Rjt denotes the number of requests having origin at zone {a mathematical formula}oj and destination at zone {a mathematical formula}dj at decision epoch t. In the context of taxis, this would correspond to the set of customer requests that travel between certain starting and ending zones.
      </list-item>
      <list-item label="•">
       {a mathematical formula}Ni indicates the initial number of servers in zone {a mathematical formula}i∈Z.
      </list-item>
      <list-item label="•">
       {a mathematical formula}C represents the objective (e.g., revenue, number of requests served, negative of waiting time), with {a mathematical formula}Ci,oj,djt denoting the objective value obtained by matching a server in zone i to a single customer request with origin and destination zones given by {a mathematical formula}〈oj,dj〉 at decision epoch t.
      </list-item>
      <list-item label="•">
       {a mathematical formula}T(z,z′,t) gives the time taken by a server to move from zone z to {a mathematical formula}z′ at decision epoch t.
      </list-item>
      <list-item label="•">
       {a mathematical formula}f(z,t) gives the list of zones for servers that can be assigned to a request originating in zone z at decision epoch t. Depending on the quality of service (QoS) constraints in the domain, these can be appropriately defined. We can define f as a function returning the set of zones, which can be reached from z within a duration τ at decision epoch t, i.e., {a mathematical formula}z′∈f(z,t) if and only if {a mathematical formula}T(z′,z,t)≤τ. This ensures that waiting time for any request is less than τ. Such QoS constraints can be employed to derive f as well as g, that is described next.
      </list-item>
      <list-item label="•">
       {a mathematical formula}g(z,t) provides the list of originating zones for requests that can be assigned to a server in zone z at decision epoch t, i.e., {a mathematical formula}z′∈g(z,t)⇒z∈f(z′,t).
      </list-item>
      <list-item label="•">
       M is the total number of decision epochs.
      </list-item>
     </list>
     <paragraph>
      Our goal is to identify the assignment of requests to servers so as to maximize the sum of objective value over M decision epochs. This is subject to considering valid matching and the number of requests at each decision epoch.
     </paragraph>
     <section label="3.1">
      <section-title>
       Optimization formulation for OSTM problems
      </section-title>
      <paragraph>
       We provide the integer linear optimization formulation for OSTM problems in Table 1. Intuitively, the goal of the formulation is to set values for the assignment (of servers to demand) variables while ensuring the flow of servers between zones and the corresponding assignment to demand are valid. Depending on whether the Markovian property for resource allocation is satisfied, the complexity of this formulation can either be polynomial time or NP-Hard. We provide a detailed discussion on this aspect in Section 3.1.1 and an example to describe symbols of the formulation in Section 3.1.2.
      </paragraph>
      <paragraph>
       The complexity of the formulation is determined by the assumptions on the underlying binary constants {a mathematical formula}δijt,t′,1≤t≤t′≤M (refer to Section 3.1.1) and hence these binary constants are defined first. {a mathematical formula}δijt,t′ indicates whether zone i server assigned to a single request belonging to the element j of {a mathematical formula}Dt at decision epoch t completes its trip exactly at decision epoch {a mathematical formula}t′. The formal definition is as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The integer variable {a mathematical formula}xijt denotes the number of zone i servers assigned to the element {a mathematical formula}j∈Dt at decision epoch t. The number of servers available in any zone, at any decision epoch depends on assignments at previous decision epochs. Constraints (3) and (5) ensure that at any decision epoch t, the number of servers assigned from a zone is less than the number of available servers in the zone at decision epoch t. Constraint (4) ensures that for each element in {a mathematical formula}Dt, the number of requests assigned to servers is less than the number of available requests between origin and destination zone pairs corresponding to element j of {a mathematical formula}Dt.
      </paragraph>
      <section label="3.1.1">
       Discussion on {a mathematical formula}δijt,t′
       <paragraph>
        We can observe in equation (1) that the values of binary constants {a mathematical formula}δijt,t′ depends on the total time taken by a zone i server to reach destination zone of element j of {a mathematical formula}Dt. Therefore, as shown in the Fig. 1, we have two cases
       </paragraph>
       <list>
        <list-item label="•">
         The time at which server becomes available again after serving a request is independent of the assigned server.
        </list-item>
        <list-item label="•">
         The time at which server becomes available again after serving a request is dependent of the assigned server. For example, suppose server A assigned to a request r at {a mathematical formula}t=1 becomes available again for assignment at {a mathematical formula}t=4. Now if request r is served by another server B at {a mathematical formula}t=1, then it is possible that B will still be serving the request r at {a mathematical formula}t=4 and becomes available again at {a mathematical formula}t=6. One of the cases where this is possible is when the time taken by different servers to reach pickup location of request is different. In the above example A reaches pickup location of r at {a mathematical formula}t=2 and B reaches pickup location of r at {a mathematical formula}t=4.
        </list-item>
       </list>
       <paragraph>
        Case 1 is similar to the Markov property defined in the context of resource allocation problem{sup:4} and makes the problem polynomial time solvable as the formulation is equivalent to a minimum cost network flow problem. Formally stating the above discussion, for the special case when {a mathematical formula}δijt,t′=δi′jt,t′,∀j,t,t′,i,i′ (i.e., a request completion decision epoch is same irrespective of the server assigned to it), we show the reduction of the OSTM to a min cost flow problem with integer capacities (Proposition 1). As the min cost flow problem is polynomial time solvable, the OSTM is also polynomial time solvable for this special case.
       </paragraph>
       <paragraph label="Proof">
        If{a mathematical formula}∀j,i,i′,t,t′δijt,t′=δi′jt,t′, then the OSTM is reducible to a min cost flow problem.See Appendix D.1.  □
       </paragraph>
       <paragraph label="Proof">
        For case 2 (i.e., for at least one setting of {a mathematical formula}j,i,i′,t,t′ if {a mathematical formula}δijt,t′≠δi′jt,t′), we show that the OSTM is NP-hard by reducing the well known 3-SAT problem to it (Proposition 2). If{a mathematical formula}∃j,i,i′,t,t′s.t.δijt,t′≠δi′jt,t′, then the OSTM is NP-hard.See Appendix D.2.  □
       </paragraph>
       <paragraph>
        Relaxation of optimization formulation As shown in Proposition 1, if special condition on δ values holds, the problem is reducible to min cost flow. Therefore, we will get the integer optimal solution even if we relax the integrality constraints in the integer program for the OSTM.
       </paragraph>
       <paragraph>
        For the general case, we do not have any theoretical guarantees on the linear relaxation of the integer program. But in our experiments, we observed that the linear relaxation of the OSTM integer program is tight and the difference between the optimal value of the integer program and the relaxed linear program is always less than 1%. Therefore, the objective value obtained on solving the relaxation of the OSTM, provides a tight upper bound on the value of the optimal solution. In addition, a major part of the solution has integer values. A simple heuristic of taking the integer part of the solution satisfying all constraints provides a solution which is nearly 95% of the optimal integer solution. In Section 4, we also provide a heuristic to extract an integral solution from the LP relaxation solution.
       </paragraph>
      </section>
      <section label="3.1.2">
       <section-title>
        Example
       </section-title>
       <paragraph label="Example 1">
        The server availability at decision epochs 2 and 3 will depend on the assignments at the decision epoch 1. The server, if assigned, will be available in the destination zone of the requests at the decision epoch where the dashed line from the corresponding assignment line ends. Unassigned servers will be available in the same zone at next decision epoch.We can also observe from this example, the importance of considering multi-stage matching. For this, we compare the revenue earned by two kinds of decisions
       </paragraph>
       <list>
        <list-item label="1.">
         Single-stage decision, i.e., decisions which do not consider future requests: In this case, at decision epoch 1 zone 1 server will be assigned to the demand element 2 and zone 2 server will be assigned to the demand element 1, i.e., {a mathematical formula}x121=1,x211=1 and rest all variables as 0. This will give a total revenue of {a mathematical formula}20+14. As none of the servers will be available at decision epoch 2, no other requests can be served.
        </list-item>
        <list-item label="2.">
         Multi-stage decision, i.e., decisions which consider future requests: In this case, at decision epoch 1, zone 1 server will be assigned to the demand element 1 and zone 2 server will not serve any request, i.e., {a mathematical formula}x111=1 and rest all variables for decision epoch 1 are set to 0. At decision epoch 2 both servers will be available in the zone 2 and can serve both requests, i.e., {a mathematical formula}x212=1 and {a mathematical formula}x222=1. This will give a total revenue of {a mathematical formula}15+15+10=40.
        </list-item>
       </list>
       <paragraph>
        We have presented the model for the case where the exact demand information is available for all decision epochs. In the next section, we extend this model to consider uncertain customer demand which is revealed in an online fashion.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="4">
     <section-title>
      Online spatio-temporal matching (OLSTM)
     </section-title>
     <paragraph>
      In the OnLine Spatio Temporal Matching (OLSTM) problem, requests for all the decision epoch are not known in advance, but instead requests for each decision epoch are only revealed at that decision epoch. The goal is to make matching decisions at each decision epoch so as to optimize the overall objective. Considering potential future scenarios can help in making better matching decisions [10], [15], [32]. Therefore, we use multiple potential scenarios of demand requests at future decision epochs. One way of obtaining the potential scenarios is to consider the scenarios observed in the past data.
     </paragraph>
     <section label="4.1">
      <section-title>
       Problem
      </section-title>
      <paragraph>
       An OLSTM problem is described using the following tuple:{a mathematical formula}
      </paragraph>
      <paragraph>
       We only define, the new elements (i.e., the scenario related information) beyond those defined for the OSTM problem.{sup:5}
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}ξD is the set of customer request samples for the future decision epoch, where {a mathematical formula}ξtD,k, {a mathematical formula}t&gt;1, represents the set of customer requests at {a mathematical formula}t−1 decision epochs in the future in sample k. Each element {a mathematical formula}j∈ξtD,k is characterized by a tuple {a mathematical formula}〈oj,dj,Rjt,k〉 where {a mathematical formula}oj,dj∈Z denote the origin and destination zone of requests and {a mathematical formula}Rjt,k denotes the number of requests having origin at zone {a mathematical formula}oj and destination at zone {a mathematical formula}dj at decision epoch t for sample k.
       </list-item>
       <list-item label="•">
        {a mathematical formula}ξS,t is the set of servers that are not available at the current decision epoch but will become available at decision epoch t,{sup:6} where {a mathematical formula}ξiS,t represents the number of servers that will become available in zone i.
       </list-item>
      </list>
      <paragraph>
       Similar to the binary constants δ defined in OSTM model, we will have binary constants {a mathematical formula}δijt,t′,k(t&gt;1), which are set to 1 if zone i server assigned to a single request belonging to the element j of {a mathematical formula}ξD,kt at decision epoch t completes its trip exactly at decision epoch {a mathematical formula}t′.
      </paragraph>
      <paragraph>
       For ease of explanation, we first describe the formulation for a two-stage model, where we only consider requests at the next decision epoch in making matching decisions at the current decision epoch.
      </paragraph>
      <paragraph>
       Our goal is to identify the assignment of requests to the servers so as to maximize the sum of objective values for the current decision epoch and the expected objective value for the next decision epoch. An integer linear optimization formulation is provided in the Table 2 for computing the best match at the current decision epoch while considering multiple samples of potential requests in the next decision epoch. We refer to this as TSS(). Integer variables {a mathematical formula}xij1 denote the number of zone i servers assigned to element {a mathematical formula}j∈D1. Similarly, integer variables {a mathematical formula}xij2,k denote the number of zone i servers assigned to the element {a mathematical formula}j∈ξ2D,k.
      </paragraph>
      <paragraph>
       While the first component of the objective value corresponds to the current decision epoch, the second component computes the expected value associated with the future requests (provided in {a mathematical formula}ξD). Constraints (8) and (10) ensure that at any decision epoch, the number of assigned servers from the zone i is less than the number of available servers. In Constraint (10) the number of servers available at decision epoch “2” in zone i is calculated by considering the remaining servers in zone i after doing assignments for decision epoch “1”. Constraints (9) and (11) ensure that at any decision epoch, between any zone pair, the number of requests assigned to servers is less than the number of available requests between the origin and destination zone pair. For a single sample, the above integer program is equivalent to an OSTM integer program with {a mathematical formula}M=2. Therefore, as shown in Proposition 1, if {a mathematical formula}δi′j1,2=δij1,2∀i,i′,j, the relaxation of TSS, for a single sample, will have an integer optimal solution.
      </paragraph>
      <paragraph label="Proof">
       For a general case with multiple samples, we show in Proposition 3 that TSS is NP-hard. Solving TSS for more than one sample is an NP-hard problem irrespective of δ values.See Appendix D.3.  □
      </paragraph>
      <paragraph>
       Relaxation of the TSS optimization formulation
      </paragraph>
      <paragraph>
       For a general case with multiple samples, the linear relaxation of the TSS integer program can yield fractional solutions. But in our experiments on synthetic domains and two real world datasets, we observe that the linear relaxation of TSS is tight and the difference between the optimal value of the integer program and the relaxed linear program is always less than 1%. We also observe that most of the time, the solution is integral and even if the solution is not integral, major part of the solution has integer values. Therefore, our approach is to solve the relaxed version of the problem and in case the solution is not integral, we round it to an integer solution as described below.
      </paragraph>
      <paragraph>
       While converting a fractional solution to an integer, only the parts of the solution that are fractional are modified. From the fractional part, variables {a mathematical formula}xij1 are rounded in such a way that the number of servers assigned from each zone at the first decision epoch remain close to the fractional optimal solution. This ensures that the servers which were left unassigned by the TSS, remain unassigned and the assignments at the second stage are least affected. We denote {a mathematical formula}Fi as {a mathematical formula}⌈∑jxij1−∑j⌊xij1⌋⌉, i.e., the sum of fractional assigned servers from zone i rounded up to the nearest integer. We denote {a mathematical formula}Gj as {a mathematical formula}⌈∑ixij1−∑i⌊xij1⌋⌉, i.e., the number of fractionally assigned requests rounded up to the nearest integer. We further divide the set {a mathematical formula}Gj into two parts with the set {a mathematical formula}G1j containing requests which complete on or before decision epoch 2 and the set {a mathematical formula}G2j containing remaining requests. We greedily assign the servers available in {a mathematical formula}Fi,∀i to the requests available in the set {a mathematical formula}Gj,∀j in two rounds. In the first round, we only consider the requests in the set {a mathematical formula}G1j, i.e., we give priority to the requests which can be completed by decision epoch 2. If after first round {a mathematical formula}∃i,Fi&gt;0, we greedily assign them to the requests in {a mathematical formula}G2j.
      </paragraph>
      <section label="4.1.1">
       <section-title>
        Example
       </section-title>
       <paragraph>
        In this section, we show an example that explains the different parameters and elements of the OLSTM model.
       </paragraph>
       <paragraph label="Example 2">
        Similar to OSTM, we consider a 3 zone problem as shown in the Fig. 3. The following table provides a mapping between the formal notation and the visual depiction of the OLSTM problem. We only define the new elements as compared to the OSTM example.{a mathematical formula}For decision epoch 1, the assignment decisions are independent of samples, but server which will become available after serving the request, will be available for all samples. Therefore, in the graphical representation, we represent it by creating copies of first stage δ constants for each sample and represent them with colored dash lines even for first decision epoch. All these copies will have identical values. In the formulation, this is shown by having {a mathematical formula}δij1,t′ and {a mathematical formula}xij1 in constraint (10).The value of τ and Δ is taken as 5. Travel time T and sets f and g are populated as explained in the OSTM example.We can also observe from this example, that the optimal decision for individual samples will not remain optimal when all the samples are considered together. We show the decisions and revenue computation in following three cases:
       </paragraph>
       <list>
        <list-item label="1.">
         Only sample 1 is considered: If only sample 1 is considered, it will be beneficial to move both servers to zone 2 at decision epoch 2. Therefore, the optimal decision will be, {a mathematical formula}x121=1,x241=1,x212,1=1,x222,1=1 and rest all variables as 0. This will give a total revenue of {a mathematical formula}15+14+15+14=58.
        </list-item>
        <list-item label="2.">
         Only sample 2 is considered: Similar to above case, if only sample 2 is considered, the optimal decision will be {a mathematical formula}x111=1,x231=1,x112,1=1,x112,1=1 and rest all variables as 0. This will give a total revenue of {a mathematical formula}15+14+15+14=58.
        </list-item>
        <list-item label="3.">
         Both samples are considered: On the other hand if both samples are considered, the optimal decision will be {a mathematical formula}x121=1,x211=1,xij2,1=1,xij2,1=1 and rest all variables as 0. This will give a total revenue of {a mathematical formula}14+14+{a mathematical formula}((15+12)+(15+12))2=55. In this case, individual sample's optimal decision will give a revenue of {a mathematical formula}15+14+((15+14)+(7+12))2=53.
        </list-item>
       </list>
      </section>
     </section>
     <section label="4.2">
      <section-title>
       Benders decomposition
      </section-title>
      <paragraph label="Observation 1">
       Given the scale of the problems of interest in this paper (i.e., thousands of taxis serving thousands of customers spread across hundreds of zones), we reduce the complexity associated with increasing the number of samples by exploiting the following observation: In TSS, once the assignment at the first decision epoch,{a mathematical formula}{xij1}is given, the optimization models for computing the assignment at the second decision epoch,{a mathematical formula}{xij2,k}for each of the samples k, are independent of each other.
      </paragraph>
      <paragraph>
       We exploit Observation 1 by using the Benders Decomposition [48] method, a master slave decomposition technique where the Master Problem is responsible for obtaining the solutions for the “difficult” variables; and the Slave problem(s) is (are) responsible for finding the solutions to other variables, given a fixed assignment of values to “difficult” variables (from the master). The Slave problem(s) also generate Benders cuts, which are added to the master problem and the master problem is solved with these cuts to obtain an improved solution. This process continues until no more cuts can be added to the master problem.
      </paragraph>
      <paragraph>
       Based on Observation 1, {a mathematical formula}{xij1} are the difficult variables as they impact the values assigned to all the other variables. Therefore, the master is responsible for obtaining the assignments for the {a mathematical formula}{xij1} variables and the slave(s) are responsible for obtaining the assignments to the {a mathematical formula}{xij2,k}. For the master (Table 3), in the optimization provided in TSS, we replace the part of the objective dealing with future variables, {a mathematical formula}{xij2,k} by the recourse function {a mathematical formula}Q({xij1}i∈Z,(j∈D1,oj∈g(i,1)),k) which becomes the objective function in the slave problems. The recourse function {a mathematical formula}Q() needs to be computed for each value of {a mathematical formula}xij1. In the slaves (Table 4), we consider the fixed values of {a mathematical formula}xij1 and to avoid confusion, we refer to them using the capital letter notation, {a mathematical formula}Xij1.
      </paragraph>
      <paragraph>
       The dual{sup:7} of the primal slave problems are provided in Table 5, where α variables are the dual variables corresponding to the constraints (18) and β variables are the dual variables corresponding to the constraints (19).
      </paragraph>
      <paragraph>
       The weak duality theorem[49] states that the solution to a maximization primal problem is always less than or equal to the solution of the corresponding dual problem. Therefore, using the concept of weak duality we can say that by taking the dual of the slave problems, we can find an upper bound on the value of the recourse function ({a mathematical formula}Q()) (objective of primal slave problem), in terms of the master problem variables {a mathematical formula}xij1. These can then be added as optimality cuts to the master problem [47] for generating better first stage assignments.{sup:8} Let {a mathematical formula}θk be the approximation of {a mathematical formula}Q() function then the master problem with optimality cuts is provided in the Table 6. It should be noted that we are using {a mathematical formula}xij1 variables in the “master with optimality cuts” and not the fixed values, {a mathematical formula}Xij1. In each iteration we solve the master problem and the computed {a mathematical formula}xij1 variable values are passed to the dual slave problems. After solving the dual slave problems, optimality cuts are generated. If the current values of {a mathematical formula}θk(∀k) satisfy the optimality cut conditions then we have obtained an optimal solution, else cuts are added to the master problem and the master problem is solved again. As we can see in the “Dual Slave” linear programs, the slave problems are independent of each other and are only connected by the choice of the master variables (“difficult” variables). Therefore, once the master variables are fixed, the slave problems can be solved in a parallel fashion.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       Complexity analysis
      </section-title>
      <paragraph>
       The complexity of a linear program depends on the number of variables and constraints in the formulation. The maximum number of variables in the TSS formulation are {a mathematical formula}|Z|.|D1|+∑k|Z|.|ξ2D,k|. This maximum value will be obtained when any request can be served using server from any zone. But in practice depending on the value of τ, f and g function will restrict the number of variables. For {a mathematical formula}τ=0, request can only be served using the server present at its origin zone, therefore, the number of variables are {a mathematical formula}|D1|+∑k|ξ2D,k|. As the value of τ increases, the number of variables increases. The number of constraints are {a mathematical formula}|Z|+|D1|+|ξD|.|Z|+∑kξ2D,k.
      </paragraph>
      <paragraph>
       Therefore, on increasing the number of zones and the number of samples, both variables and constraints increase. The size of {a mathematical formula}D1 and {a mathematical formula}ξ2D,k increases with the value of Δ. This is because Δ is the duration between 2 decision epochs, so when Δ is small, the number of requests between two decision epochs will be less. Therefore, on increasing the value of Δ, the number of variables and constraints both increase.
      </paragraph>
      <paragraph>
       In addition to τ, the travel time between zones (T) also affect the number of variables. For a constant τ, if travel time between zones increases, there will be less zones from where servers can be used to serve any requests. Hence the number of variables decrease on increasing travel time keeping the value τ constant.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Competitive ratio
      </section-title>
      <paragraph>
       Competitive analysis is typically employed for evaluating the quality of online algorithms. The metric used is called as the competitive ratio [16] and it compares a solution produced by an online algorithm with the best possible solution. Specifically, the competitive ratio of an online algorithm is defined as the worst-case ratio between the objective of the solution found by the algorithm and the objective of an optimal solution, which assumes all uncertain information is known beforehand. For deterministic input model and maximization problems, an online algorithm is called c-competitive if for any instance of the problem{a mathematical formula} where {a mathematical formula}ALG(I) is the value of any given online algorithm and {a mathematical formula}OPT(I) is the value of the offline optimal algorithm for instance I. Equivalently, this can be written as{a mathematical formula}
      </paragraph>
      <paragraph>
       In stochastic environments, we calculate empirical competitive ratio, {a mathematical formula}cμD that is defined as{a mathematical formula}
      </paragraph>
      <paragraph>
       For stochastic input models where multiple distributions of uncertainty are provided, we can also calculate expected competitive ratio (Please refer Section 2.2.1 in [18]). It is computed in expectation over the randomness in the input:{a mathematical formula} where D is the distribution over instances I from which input is drawn and expected competitive ratio is the expectation over the ratio achieved by the algorithm and the optimum for that distribution.
      </paragraph>
      <paragraph label="Proof">
       In OLSTM without sample information and adversarial behavior from environment,{sup:9}when maximizing the number of requests satisfied for a fixed number of servers N, the competitive ratio, c for any deterministic b-stage algorithm (i.e., with information available up to the bth decision epoch) in a M-decision epoch ({a mathematical formula}M≥b) problem is{a mathematical formula}See Appendix D.4.  □
      </paragraph>
      <paragraph label="Proof">
       In OLSTM with sample information and stochastic behavior from environment according to the samples, when maximizing the number of requests satisfied, the expected competitive ratio,{a mathematical formula}cμ, of the TSS algorithm is{a mathematical formula}where M is the number of decision epochs ({a mathematical formula}M≥3).See Appendix D.5.  □
      </paragraph>
      <paragraph>
       The expected competitive ratio value is typically overly pessimistic as it measures the worst case. However, the algorithms can have good average case performance, {a mathematical formula}cμD as demonstrated in our experimental results. We will compute this for our formulations and other one-stage approaches, by comparing the solution values obtained with the M-stage optimal offline solution. We solve the OSTM integer program defined in Section 3 to compute the M-stage optimal offline solution.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Relaxing the assumptions
     </section-title>
     <paragraph>
      In our optimization models for the OSTM and OLSTM, we make a few assumptions. In this section, we describe the assumptions and provide the ways of relaxing them:
     </paragraph>
     <list>
      <list-item label="1.">
       The time is divided into discrete blocks (each with duration Δ) and we consider only the next decision epoch in TSS. Such an approach is limiting as different requests have different travel time. We relax this assumption by providing a multi-stage model, which allows for smaller values of Δ and also considers multiple discrete blocks at once. More details about the multi-stage model is provided in the Section 5.1.
      </list-item>
      <list-item label="2.">
       The server moves from one place to another if and only if it is assigned to a request. It is fairly trivial to relax this assumption by introducing the notion of dummy requests. We provide a detailed description in the Section 5.2.
      </list-item>
      <list-item label="3.">
       Customers are impatient and if they are not assigned a server in one decision epoch, they will not wait for the next decision epoch for a server to be assigned. However, we can easily relax this assumption by representing a customer staying across multiple decision epochs as a customer who leaves and arrives as a new customer at the next decision epoch.
      </list-item>
      <list-item label="4.">
       The server will start moving as soon as it is assigned to a request. The time taken to compute the assignment is ignored. Therefore, a server assigned to a request at decision epoch t will start moving towards request at the time corresponding to decision epoch t. This is a reasonable assumption, as we are able to obtain solutions in less than a minute (as shown in our experiments).
      </list-item>
     </list>
     <section label="5.1">
      <section-title>
       Multi-stage model
      </section-title>
      <paragraph>
       In TSS, we only consider the future requests for the next decision epoch. Given that different requests may have different travel time, we extend the TSS model to consider the samples for multiple decision epochs to improve the performance for small Δ values. The extended model is referred to as MSS.
      </paragraph>
      <paragraph>
       The optimization model for MSS is shown in the Table 7. A parameter Q is added to the formulation which denotes the look-ahead timesteps, i.e., Q denotes the number of decision epochs for which future demand samples are considered. The number of variables and constraints in the formulation increase with the value of Q. Therefore, the complexity of MSS formulation increases as the value of Q increases.
      </paragraph>
      <paragraph>
       The variable {a mathematical formula}xij1 denotes the number of zone i servers assigned to the jth element of {a mathematical formula}D1 at the current decision epoch. The variable {a mathematical formula}xijt,k,t&gt;1 denotes the number of zone i servers assigned to element j of {a mathematical formula}ξtD,k.
      </paragraph>
      <paragraph>
       Constraints (33) and (35) ensure that at any decision epoch, the number of servers assigned from zone i is less than the number of available servers. Constraints (34) and (36) ensure that at any decision epoch, between any zone pair, the number of requests assigned to servers is less than the number of available requests between the origin and destination zone pair.
      </paragraph>
      <paragraph>
       Given the similarity in the formulations, we can again employ Benders Decomposition to reduce the complexity with increasing the number of samples. Difficult variables will still be the stage 1 variables, i.e., {a mathematical formula}xij1 and all other variables, {a mathematical formula}xijt,k(t&gt;1) would be the slave variables with a slave for each sample of customer requests.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Dummy requests
      </section-title>
      <paragraph>
       We can remove the assumption that servers will only move when they are assigned to a request by introducing dummy requests. Dummy requests have zero revenue and have a destination in a given zone. We introduce {a mathematical formula}uij′1 as an integer variable denoting the number of zone i servers assigned to move to zone {a mathematical formula}j′ at the current decision epoch, i.e., the number of zone i servers assigned to dummy requests with destination in zone {a mathematical formula}j′ at the current decision epoch. Similarly, {a mathematical formula}uij′t,k denote the number of zone i servers assigned to move to zone {a mathematical formula}j′ in sample k at decision epoch {a mathematical formula}t,t&gt;1. We modify the MSS formulation to include these variables. There will be a cost associated with the movement of server to serve dummy requests which is included in the objective function. The modified MSS formulation is shown in Table 8.{sup:10}{a mathematical formula}Costi,j′t denotes the cost of moving a server from zone i to zone {a mathematical formula}j′ at decision epoch t.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      In this section, we will compare the performance of seven approaches Multi-Stage Stochastic optimization (MSS){sup:11} and Benders Decomposition (BD), Greedy (GD) algorithm, Randomized Greedy Algorithm (RGD), One-Stage optimization (OS), Approximate Dynamic Programming formulation (ADP) and Hybrid Multi-Stage Stochastic optimization approach (HSS) used in [10]. We employ MSS{a mathematical formula}(Δ=x,Q=y) and BD{a mathematical formula}(Δ=x,Q=y) to refer to our approaches when the time interval Δ is set to x and the look ahead duration Q is set to y. We compare different approaches with respect to (i) Revenue earned by taxis; (ii) Number of requests satisfied; and (iii) Run-time to compute the assignment.
     </paragraph>
     <paragraph>
      Table 9 provides the outline for this section. We will show two main results that demonstrate the significant utility of our approaches:
     </paragraph>
     <list>
      <list-item label="•">
       MSS and BD consistently outperform myopic (GD, RGD and OS) and multi-stage approaches (ADP and HSS). While the improvement varies, on an average (across data sets and other settings) there was a 20% improvement over GD, RGD and OS and 9% improvement over HSS and ADP.
      </list-item>
      <list-item label="•">
       BD provides the best trade off between run-time and solution quality. It can solve the problems in quickly while achieving roughly the same solution quality as MSS.
      </list-item>
     </list>
     <section label="6.1">
      <section-title>
       Datasets
      </section-title>
      <paragraph>
       We conducted our experiments by taking the demand distribution from three real world datasets of major taxi companies. The first dataset is the publicly available New York Yellow Taxi Dataset [50], henceforth referred to as NYDataset. The names of the other two real world datasets can not be revealed due to confidentiality agreements. They are referred to as Dataset1 and Dataset2. These datasets contain the data of past customer requests for taxis at different times of the day and for different days of the week. From these datasets, we take the following fields:
      </paragraph>
      <list>
       <list-item label="•">
        Pickup and Drop off Location (Latitude and Longitude coordinates): These locations are mapped to the zones as mentioned in the Section 6.1.1.
       </list-item>
       <list-item label="•">
        Pickup Time: This time is converted to the appropriate timestep based on the value of Δ. The pickup time {a mathematical formula}hh:mm is mapped to the timestep/decision epoch {a mathematical formula}⌈hh⁎60+mmΔ⌉. For example, for {a mathematical formula}Δ=5, 08:04 AM is mapped to the timestep {a mathematical formula}⌈8⁎60+45⌉=97, i.e., all the requests between time 08:00 AM and 08:05 AM are mapped to the time 08:05 AM.
       </list-item>
      </list>
      <paragraph>
       The distance of a trip and the revenue earned from a trip are computed using the underlying model typically employed by the taxi companies (an initial base fare + a quantum that accrues with the distance traveled/time taken). We describe it in Section 6.2.
      </paragraph>
      <paragraph>
       Since our approaches perform well on these three real world data sets, we also provide the specially created scenarios where our approaches may not work as well. The details of these specially created synthetic scenarios are described in Section 6.5.
      </paragraph>
      <paragraph>
       In the next subsection, we describe the zone creation process using the publicly available NYDataset. The zone creation process is important because we perform matching at the level of zones. The zone level matching ensures scalability while providing a good approximation.
      </paragraph>
      <section label="6.1.1">
       <section-title>
        Zone creation
       </section-title>
       <paragraph>
        We employ past data of pickups and drop-offs to divide a city into zones. Using past data helps in providing the right tradeoff between having few zones and the error introduced due to consideration of zones. There are four key steps to the zone creation process for all three data sets:
       </paragraph>
       <list>
        <list-item label="•">
         We divide the entire city area into small grids (0.5 km × 0.5 km).
        </list-item>
        <list-item label="•">
         We consider the minimum number of grids that make up most of the pickups and drop-offs (&gt;90%). These are the first set of zones. This will ensure that the error is negligible for most of the requests.
        </list-item>
        <list-item label="•">
         We then add a minimum number of zones, so that 9% of the remaining pickups and drop-offs are within 1 km × 1 km of a zone.
        </list-item>
        <list-item label="•">
         We add a minimum number of zones, so that the remaining 1% of the pickups and drop-offs are within 2 km × 2 km of zone.
        </list-item>
       </list>
       <paragraph>
        Fig. 4 provides the spatial configuration of zones in case of New York city. All the red grids represent zones. Green grids represent the areas that are within 1 km × 1 km of a zone and account for 9% of the pickups/drop-offs. Blue grids represent the areas that are within 2 km × 2 km of a zone and account for 1% of past pickups/drop-offs. We used the trip data for 6 months from Jan 2016–June 2016 (total 136830072 pickups/drop-offs) to create these zones. To assign zone to any new location, we check the distance of the location from the centers of these created zones and assign the zone with minimum distance. The percentage values can be changed depending on the need and dataset,
       </paragraph>
      </section>
     </section>
     <section label="6.2">
      <section-title>
       Experimental settings
      </section-title>
      <paragraph>
       There are three different categories of settings that have an
      </paragraph>
      <paragraph>
       1. Inputs provided to all algorithms: These include:
      </paragraph>
      <list>
       <list-item label="•">
        τ: It represents the maximum time within which the taxi should reach the pickup point. We take the value of τ as 5 minutes, i.e., at any decision epoch a taxi can be assigned to a request if and only if the time taken by the taxi to reach the request origin zone is less than or equal to 5 minutes.
       </list-item>
       <list-item label="•">
        Revenue model: We employed the following model for experimental evaluation that is a well accepted standard ([51]). The model calculates revenue as follows:{a mathematical formula} where {a mathematical formula}dist(oj,dj) is the distance between the centers of zones {a mathematical formula}oj and {a mathematical formula}dj. For different cities, the values of {a mathematical formula}B,R and P are different.{sup:12}
       </list-item>
       <list-item label="•">
        Travel time between zones: For the experimental results, the time taken to travel between zones{sup:13} is also same irrespective of the time of day and is calculated as{a mathematical formula} where {a mathematical formula}vtaxi is the speed of taxi which is taken as 40 km per hour.
       </list-item>
       <list-item label="•">
        Number of taxis ({a mathematical formula}Ni1): The number of taxis used is dependent on the fleet size of the taxi company. At the start of the experiment taxis in different zones are distributed either uniformly if taxi locations are not observed (NYDataset and Dataset1) or as observed in the data (Dataset2). Based on the assignment obtained by algorithms at any decision epoch availability of taxis at the next decision epoch is updated. In the results section, we vary the number of taxis to show the performance of all algorithms for different number of taxis.
       </list-item>
       <list-item label="•">
        Number of zones ({a mathematical formula}|Z|): We described the zone creation process in the Section 6.1.1. Using our zone creation process we obtained 483 zones for the 2 confidential datasets and 436 zones for the NYDataset. For a different city and dataset, the number of zones will be different.
       </list-item>
      </list>
      <paragraph>
       2. Parameters of algorithms: The parameters required by our algorithms (MSS and BD) are:
      </paragraph>
      <list>
       <list-item label="•">
        Decision epoch length (Δ): This parameter determines how often, the algorithm should be executed and assignment decisions are made. We identify the right value of Δ through experiments as described in results section.
       </list-item>
       <list-item label="•">
        Look ahead timesteps (Q): The value of Q is taken such that {a mathematical formula}Δ⁎(Q+1)=30 minutes, i.e., if Δ is 1, Q is taken as 29 and if Δ is 15, Q is taken as 1. We choose a fix value of 30 minutes because more than 90% of the requests complete within 30 minutes with average travel time between 5–10 minutes. So 30 minutes provides a good look ahead. But this value can be changed depending on the dataset.
       </list-item>
       <list-item label="•">
        Number of samples ({a mathematical formula}ξD): While computing an assignment at decision epoch t, our approaches (MSS and BD) and existing multi-stage approaches (HSS and ADP) require samples of customer requests at decision epochs {a mathematical formula}t+1,t+2,..,t+Q from past data (at the same decision epoch on a weekday/weekend depending on whether the decision epochs are on a weekday/weekend). We identify the right value for the number of samples through experiments as described in results section.
       </list-item>
      </list>
      <paragraph>
       3. Evaluation settings: For each algorithm, once the assignment is computed at each decision epoch, we evaluate the assignment on the realized requests (which are samples from the past data that are not considered while computing the assignment). The objective for all the algorithms is to maximize revenue. To provide the right trade-off between run-time and solution quality, we considered 3 iterations in BD. The evaluation settings include the following :
      </paragraph>
      <list>
       <list-item label="•">
        Number of decision epochs (M): Typically transitions in the taxi demand happen approximately every 3 hours (morning and evening peak hours, lunch), so we choose the value of 2.5 hours, i.e., {a mathematical formula}M=2.5⁎60Δ. However, we did try other values for M (lower and higher than 2.5 hrs) and the results were similar.
       </list-item>
       <list-item label="•">
        Number of days and the time of evaluation: We performed experiments with requests at various times of the day, 8:00 AM, 3:00 PM, 6:00 PM and on different days. We evaluated the approaches by running them on 45 different days and taking the average values over 45 days for Dataset1 and Dataset2. For NYDataset, we evaluated the approaches on 15 weekdays between 4th April 2016–22nd April 2016.
       </list-item>
      </list>
      <paragraph>
       We conducted experiments with all the combinations of settings and inputs mentioned in this section. To avoid repeating similar results over and over again, we provide the representative results.
      </paragraph>
     </section>
     <section label="6.3">
      <section-title>
       Main results
      </section-title>
      <paragraph>
       In this section, we compare the revenue and the number of requests served by all seven algorithms. We also compare the run-time of all the approaches by using different number of taxis.
      </paragraph>
      <paragraph>
       We conducted experiments by considering the demand distributions from all the datasets. We choose the best configuration for parameters of all algorithms (justification provided in the next section). All approaches are executed for {a mathematical formula}Δ=5. For our approaches, we use 10 samples and the look ahead timesteps (Q) as 5. For HSS and ADP as well, we use the number of samples as 10. For HSS similar to MSS, we use the look ahead timesteps as 5. For ADP, we use the look ahead timesteps as 10. ADP algorithm as described in the Appendix C involves solving an optimization problem for each sample and for each time step in the planning horizon. As opposed to other multi-stage approaches, ADP algorithm considers one sample at a time, therefore, we use a higher value of Q for ADP. But it is not possible to run ADP algorithm for more than 10 time steps for sufficient number of samples in real time. Moreover, we checked on few instances by using all the M(30) time steps as planning horizon and did not see any significant improvement in the performance of ADP algorithm. Therefore, we report the results for ADP algorithm with a fixed value of Q as 10.
      </paragraph>
      <paragraph>
       We first compare the revenue obtained by all the algorithms at each time step for 2000 taxis starting from 8AM. We have similar results while starting from 3:00 PM and 6:00 PM. Fig. 5, Fig. 6 show the comparison of the total revenue obtained and the total number of requests served by different algorithms at each decision epoch for all the datasets. Here are the key observations:
      </paragraph>
      <list>
       <list-item label="•">
        For the first decision epoch, the value obtained by the myopic approaches is higher than MSS and BD. This is because MSS and BD take sub-optimal decisions at the current decision epoch to obtain high revenue over future decision epochs. After initial decision epochs, MSS and BD starts outperforming other approaches.
       </list-item>
       <list-item label="•">
        With respect to the revenue, on NYDataset, MSS and BD provided close to $37 improvement per taxi as compared to the myopic approaches and close to $22 improvement per taxi as compared to ADP and HSS. For Dataset2, MSS and BD provided nearly $41 improvement per taxi as compared to the myopic approaches and $26 improvement as compared to ADP and HSS. Similarly, on Dataset1, we get $8 improvement as compared to the myopic approaches and $4 improvement as compared to ADP and HSS.
       </list-item>
       <list-item label="•">
        With respect to the number of requests served, on NYDataset, MSS and BD serve 21 381 additional requests as compared to the myopic approaches and they serve 9378 additional requests as compared to ADP and HSS. For Dataset2, MSS and BD serve 24 000 additional requests as compared to myopic approaches and it serves additional 11 000 requests as compared to ADP and HSS. Similarly, on Dataset1, we serve 3000 additional requests as compared to the myopic approaches and 1400 additional requests as compared to ADP and HSS. This is a significant result, because in most cities at rush hours, the number of taxis is almost always lower than the actual demand available.
       </list-item>
       <list-item label="•">
        On NYDataset, ADP and HSS have identical results (requests served by HSS is more but revenue is almost the same). On Dataset2, HSS slightly outperforms ADP and on Dataset1 ADP outperforms HSS. Dataset1 has higher variance in requests as compared to the other 2 datasets at 8AM. Therefore, for NYDataset and Dataset2, ADP gets almost similar samples in each iteration but with Dataset1 it gets different samples which could be the reason for better performance of ADP on Dataset1.
       </list-item>
      </list>
      <paragraph>
       The reason for MSS and BD providing better results as compared to HSS is that HSS works with larger regions at future stages, so MSS and BD have better approximation of future as compared to HSS. One of the reasons for ADP not performing as well as MSS is that the decision epoch at which the request completes depends on the assigned server (as described in the Section 3) which breaks the Markov property. In addition, as described in Appendix C, possible assignment of the taxis from nearby regions makes the value function non separable across zones, but ADP approximation assumes this separation. Due to these reasons, the value function approximation updated using the dual variables of a relaxed linear program is not accurate.
      </paragraph>
      <paragraph>
       The value function approximation used for ADP is linear. With piece-wise linear value function approximation, the time taken to run each optimization increases, so it is not possible to perform significant number of iterations using piece-wise linear value function approximation. The results obtained using the piece-wise linear value function approximation with smaller number of taxis are similar to the linear value function approximation. Therefore, we use linear value function approximation for reporting the results.
      </paragraph>
      <paragraph>
       Peak and non-peak time: To evaluate the sensitivity of performance of algorithms with respect to the time of the day, we now compare the competitive ratio of algorithms in the morning (8:00AM), evening (06:00PM) and afternoon (03:00PM) for all datasets. For NYDataset, as shown in the next section, the distribution of requests remains almost same throughout the day and the number of requests were low only at the night time. Therefore, for NYDataset, we also compare the competitive ratio at 12AM.
      </paragraph>
      <paragraph>
       For Dataset1, the average number of requests at each decision epoch is 700 at 08:00AM, 200 at 03:00PM and 350 at 06:00PM. We can observe in the Fig. 7 that at 03:00PM, when there are more taxis as compared to the number of requests, the gap between the competitive ratio of MSS, BD and myopic approaches is less than 10% but at 08:00AM and 06:00PM, on an average the gap between the competitive ratio of MSS, BD and myopic approaches is more than 25%, the gap between MSS, BD and ADP is nearly 12% and the gap with HSS is nearly 19%.
      </paragraph>
      <paragraph>
       Similar results are observed on Dataset2. For Dataset2, the number of available taxis is taken as observed in the data. The average number of requests at each decision epoch is 2000 at 08:00AM, 1700 at 03:00PM and 1800 at 06:00PM. We can observe that at 3PM the gap between the competitive ratio of MSS, BD and other approaches is less than 1% due to fewer requests and more available taxis (nearly 8000 taxis at 3PM as compared to 5500 taxis at 08:00AM). At 08:00AM the gap is nearly 10% from all the approaches.
      </paragraph>
      <paragraph>
       For NYDataset, the average number of requests at each decision epoch is 1941.8 at 08:00AM, 1726.1 at 03:00PM, 2407.617 at 06:00PM and 712.88 at 12:00AM. Fig. 7 shows the comparison of the competitive ratio of algorithms at different times. In NYdataset, we did not observe the competitive ratio of myopic algorithm improve with fixed number of taxis at different time but the competitive ratio of ADP improves at 12:00AM. This improvement is more likely due to variance in the samples provided. As shown in the Section 6.4, NYDataset has low mean and high variance in the number of requests at night time. The gap between the competitive ratio of MSS, BD and myopic approaches is more than 40% at all times. The maximum gap between MSS, BD and ADP is 40% and minimum gap is 20%. The maximum gap between MSS, BD and HSS is 12% and minimum gap is 7%.
      </paragraph>
      <paragraph>
       Number of taxis: Finally, we also compare all the algorithms by experimenting with different number of taxis (Fig. 8, Fig. 9). We observe that as the number of taxis increase, the gap between MSS, BD and other approaches decreases. This is because when more taxis are available, taxis will be free even after executing assignments at the current decision epoch, so future demands can be met irrespective of the current assignment. Furthermore, when there are significantly more taxis than the demand, sophisticated matching approaches are not required.
      </paragraph>
      <paragraph>
       We also compare the run-time of algorithms with different number of taxis. Fig. 10 shows the run-time of MSS and BD with different number of taxis. We observed that when the number of taxis are much less or taxis are available in excess, run-time of MSS is lower as compared to the case when the number of taxis is comparable to the available requests. For Dataset1, MSS has maximum run-time at 2000 taxis and for the other 2 datasets it has maximum run-time for 5000 taxis. Though run-time of MSS changes with the number of taxis, run-time of BD(P) remains almost same irrespective of the number of taxis.{sup:14} Moreover we conducted our experiments on academic systems, on commercial servers this will take much less time.
      </paragraph>
     </section>
     <section label="6.4">
      <section-title>
       Justification for values of parameter settings
      </section-title>
      <paragraph>
       In this section, we show the reason for using the Δ value as 5 and the number of samples as 10 in the previous section.
      </paragraph>
      <paragraph>
       Decision epoch length (Δ): We identify the appropriate value of Δ which provides the right trade-off between solution quality and run-time. The solution quality increases with decreasing the value of Δ. This is because a server is assigned to only one request in each decision epoch (Section 5). Therefore, for large Δ values, even if a server can serve more than one request in Δ duration, it will be serving only one request. To observe the change in solution quality on decreasing the value of Δ, we compare the objective value of OSTM over 2.5 hours for different value of Δ on both datasets.
      </paragraph>
      <paragraph>
       Fig. 11 shows the comparison of total revenue earned and run-time of OSTM for different Δ values (in minutes) on all the datasets.{sup:15}
      </paragraph>
      <paragraph>
       As mentioned in the Section 6.2, the value of Q is taken such that {a mathematical formula}Δ⁎(Q+1)=30 minutes, i.e., if Δ is 1, Q is taken as 29 and if Δ is 15, Q is taken as 1.
      </paragraph>
      <paragraph>
       Fig. 11a shows the total revenue obtained on executing OSTM. We observe that on all the datasets, there is a major increase in revenue on decreasing the value of Δ from 15 to 10 and 10 to 5. But the increase in revenue on decreasing the value of Δ from 5 to 3 and 3 to 1 is comparatively less. Fig. 11b shows the maximum time taken to compute a single assignment with 1 sample of future demand. We observe that the time taken to compute an assignment, drastically increases on decreasing the value of Δ from 3 to 1. This is due to the large increase in the number of constraints in the optimization formulation. Even for {a mathematical formula}Δ=3, the time taken to compute a single assignment with one sample is 100 seconds on Dataset2.
      </paragraph>
      <paragraph>
       As the time taken is high for {a mathematical formula}Δ&lt;5 and quality of solution at {a mathematical formula}Δ=5 is comparable to the solution quality at {a mathematical formula}Δ=1, we take the value of Δ as 5 for our experiments.
      </paragraph>
      <paragraph>
       Number of samples ({a mathematical formula}|ξD|): Our next set of experiments measure the performance of our approaches with respect to change in the number of samples. Fig. 12 shows the mean and deviation in the number of requests available at each hour over 15 weekdays in NYDataset. From the figure, we can observe that there is a high variance in the number of requests at night between 10:00PM to 02:00AM, but during the day, the variance is low. Therefore, during the day, even with a single sample, we can obtain good quality results. Due to this reason, to observe the effect of using different number of samples for NYDataset, we provide the results at 12:00AM (as there is low mean and high variance at 12:00AM). On the other hand, Dataset1 has high variance in the number of requests in the morning at 8:00AM on weekday (minimum: 6000, maximum: 60000 over 2.5 hours). Therefore, for Dataset1, we provide the results at 08:00AM. The average number of requests at each decision epoch is 700 for Dataset1 and 712.88 for NYDataset. The total number of taxis is set to 1000 for NYDataset and 2000 for Dataset1.
      </paragraph>
      <paragraph>
       Fig. 13 provides the results for the average value of empirical competitive ratio for Dataset1 and NYDataset. In Fig. 13a and 13b, X-axis denotes the number of samples considered while computing the assignment and Y-axis denotes the empirical competitive ratio (from Section 4.4). The key observations are as follows:
      </paragraph>
      <list>
       <list-item label="(1)">
        The most significant result is that MSS and BD are able to achieve more than 88% of the optimal revenue with 10 samples on Dataset1 and more than 95% on NYDataset. Even though both datasets have high variance in the number of requests, Dataset1 has higher variance. Moreover, Dataset1 has more requests within the same pair of zones which makes a single zone more prominent than the others. So in case of Dataset1, the important zones for different samples are different and can be completely different from the test day. On the other hand, requests are more distributed in NYDataset, therefore, NYDataset has higher empirical competitive ratio as compared to the Dataset1.
       </list-item>
       <list-item label="(2)">
        Even with 1 sample, on an average MSS and BD obtain 84% of the optimal revenue on the Dataset1 and more than 85% of the optimal revenue on NYDataset.
       </list-item>
       <list-item label="(3)">
        With respect to the revenue, on Dataset1, on an average, MSS provides 1.5% additional improvement over BD, while on NYDataset, with higher number of samples, MSS provides 1% improvement over BD.
       </list-item>
       <list-item label="(4)">
        BD provides the right trade-off between run-time and solution quality. While MSS provides high quality solutions (especially for Dataset1), it can take significantly more time (up to 1500 seconds when making online decisions).
       </list-item>
       <list-item label="(5)">
        BD(P) on an average takes 24 seconds with 10 samples to compute an assignment for Dataset1 and 83 seconds with 10 Samples for NYDataset.
       </list-item>
      </list>
      <paragraph>
       On the other hand, there is very low variance over the requests on different days in Dataset2 (minimum:56000, maximum:60000 over 2.5 hours). Therefore, the empirical competitive ratio is more than 95% even on taking only one sample and does not improve much on adding more samples. The run-time results on Dataset2 are similar to NYDataset. NYDataset and Dataset2 take more time to compute an assignment as compared to Dataset1 because as discussed before Dataset1 has more requests between same zone pairs while requests are more distributed in other 2 datasets. Therefore, the number of zone pairs which have requests between them is much lower for Dataset1. Due to this, the overall size of linear program is larger for other two datasets resulting in higher run-time. (See Fig. 14, Fig. 15.)
      </paragraph>
      <paragraph>
       On all the datasets, MSS and BD provide high value of competitive ratio with very few samples. One of the major reasons for this is that the samples need not be exactly similar to the test data to provide a gain in the competitive ratio. As mentioned before, a taxi can be assigned to a request if it can reach the pickup location of request within 5 (τ) minutes and the cost of traveling to reach the request pickup location is negligible as compared to the revenue obtained. Therefore, unless samples are drastically different, they will contribute a lot in increasing the competitive ratio.
      </paragraph>
     </section>
     <section label="6.5">
      <section-title>
       Synthetic scenarios where MSS and BD do not improve performance
      </section-title>
      <paragraph>
       To better understand the settings where our approaches work well and where it does not, we also performed experiments on the synthetic datasets. We investigate the following cases, where our approaches can potentially yield bad results as compared to the myopic approaches:
      </paragraph>
      <paragraph>
       1. Requests between zones generated using uniform, binomial and Poisson distributions: For this setting, we obtained similar results (as on the real world data sets) with MSS and BD outperforming myopic approaches. On synthetic data sets with uniform distribution, MSS and BD do not get the advantage of making taxis available in the locations with more demand (based on samples) as requests are available in all the zones. The reason behind MSS and BD still outperforming myopic approaches in this scenario is the revenue model which rewards shorter trips over longer trips.
      </paragraph>
      <paragraph>
       2. Revenue model with no bias for short trips (over long trips): As myopic approaches consider the revenue for only the current decision epoch, they will assign taxis to a trip having long distance. On the other hand, MSS and BD will prefer serving multiple short distance trips. When we change the revenue model in equation (46) such that the revenue is directly proportional to the distance, MSS and BD do not get the advantage by serving multiple short distance trips. On synthetic dataset with uniform distribution of requests and the modified revenue model, all algorithms have comparable value of the competitive ratio, as shown in Fig. 16.
      </paragraph>
      <paragraph>
       3. High proportion of long distance trips with far apart zones: To simulate this scenario, we had to create a specific setting that is hard to replicate in real world data sets. We took 5 zones and no request has an origin and destination in the same zone. The time taken to travel between zones is taken such that the taxis need to be in exactly the same zone to serve the requests. In the 5 zones considered, we take the minimum time taken to travel between any pair of zones as 15 minutes and maximum time as 40 minutes. Out of 20 possible (5*4) zone pair combinations, time taken to travel between 6 zone pairs is taken as more than 30 minutes (revenue 12.5), between 6 other zone pairs as 15 minutes (revenue 7.2), 4 other zone pair as 20 minutes (revenue 8.2) and between remaining 4 zone pairs as 25 minutes (revenue 10.5). Requests are generated such that the requests with travel time 15, 20 and 25 minutes are not available at all decision epochs but the requests having travel time 30 minutes or more are available at all decision epochs. The value of τ and Δ is 5 minutes and the value of Q is 5, i.e., {a mathematical formula}Δ⁎(Q+1) = 30 minutes.
      </paragraph>
      <paragraph>
       In these settings, MSS and BD can perform arbitrarily bad as compared to the myopic approaches. The intuition is that MSS and BD can keep on taking sub-optimal decision at the current decision epoch with an expectation of getting higher revenue at the next decision epochs but on reaching the next decision epoch it again takes a sub-optimal decision.
      </paragraph>
      <paragraph>
       The competitive ratio of MSS and BD in this setting is constantly less than the myopic approaches even after providing multiple samples as shown in Fig. 17. The reason is as MSS and BD are only looking at the next 30 minutes, they decide to first serve a request with 15 minute travel time followed by a request having travel time 30 minutes or more. But on reaching the next decision epoch it ignores the request of higher travel time even if there are no requests with 15-minute travel time available. MSS and BD find it a better option to be idle for a couple of decision epochs in order to wait for a 15 minute request so that it can serve that and follow it with a request having travel time more than 30 minutes. This keeps on happening till the last decision epoch. As a result, MSS and BD remain idle, waiting for a short trip and the myopic approaches keep on serving the requests, resulting in higher revenue for them.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      Two-stage formulation of assignment problem
     </section-title>
     <paragraph>
      In this section, we provide the two-stage formulation for the pure assignment problem in the Table A.10. In this formulation, the locations are not grouped in the zones and each server and request is considered individually. Time is discretized into timesteps of duration Δ. We provide the formulation for the offline problem. The formulation does not provide a solution within 5 minutes even for 20 servers.
     </paragraph>
     <paragraph>
      We use {a mathematical formula}V to denote the set of servers and {a mathematical formula}Wt to denote the set of requests at timestep t. The set {a mathematical formula}Wt corresponds to the element {a mathematical formula}Dt in our OSTM model as both represent the demand. But as each element of the set {a mathematical formula}Dt corresponds to multiple requests and set {a mathematical formula}Wt corresponds to individual requests, for each element in {a mathematical formula}Dt, there will be multiple elements in the set {a mathematical formula}Wt.
     </paragraph>
     <paragraph>
      {a mathematical formula}xvwt denotes that the server v is assigned to the request w at time t. {a mathematical formula}bvwt denotes the waiting time of the request w when it is served using server v at timestep t. {a mathematical formula}avt is the binary variable which is set to 1 if the server v is available at timestep t. {a mathematical formula}Cvwt provides the net revenue obtained on assigning the server v to the request w at time t. The revenue for the timestep {a mathematical formula}t+1 depends on the updated location of the server as shown in the constraint A.8. Constraint (A.2) ensures that the server is assigned to atmost one request at each timestep and constraint (A.3) ensures that the request is assigned to atmost one server. Constraint (A.4) ensures that the waiting time of any request is less than τ. Constraint (A.5) computes the waiting time of request depending on the updated position of server. Constraint (A.7) checks the availability time of server depending on its updated position.
     </paragraph>
     <paragraph>
      {a mathematical formula}Tvw(v,w,t) denotes the time taken to travel from server's initial location at t to the pick up location of request w at timestep t. {a mathematical formula}Tww(w′,t,w,t+1) denotes the time taken to travel from the drop location of request {a mathematical formula}w′ at t to the pickup location of request w at {a mathematical formula}t+1. {a mathematical formula}Tw(w,t) denotes the travel time of request w at timestep t.
     </paragraph>
     <paragraph>
      Similarly {a mathematical formula}cvw(v,w,t) denotes the cost to travel from server's initial location at t to the pick up location of the request w at timestep t. {a mathematical formula}cww(w′,t,w,t+1) denotes the cost to travel from the drop location of the request {a mathematical formula}w′ at t to the pickup location of the request w at {a mathematical formula}t+1. {a mathematical formula}rev(w,t) denotes the revenue of request w at time t.
     </paragraph>
     <paragraph>
      Extending this formulation to multiple timesteps further increases the complexity. Linearizing the product of {a mathematical formula}bvwt+1 and {a mathematical formula}xvwt+1 we can write, (M is a large constant){a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} Similarly, we need to linearize the product of {a mathematical formula}Cvwt+1 and {a mathematical formula}xvwt+1 and the constraint (A.7).
     </paragraph>
    </section>
    <section label="Appendix B">
     <section-title>
      Hybrid multi-stage stochastic optimization (HSS)
     </section-title>
     <paragraph>
      In this section, we provide the details and the formulation of the model used by Powell et al. [10]. This formulation solves the assignment problem at first stage and a pure network flow approximation at the future stages. As for the truckload problem, the typical value of time step is one day, therefore, even after having an assignment problem at first stage, this formulation will be a pure network for the truckload assignment using a single sample of future demand. As described in Sections 2.2 and 3, in our case, due to smaller timesteps and specifically as the completion timestep of the customer request depends on the server assigned, this formulation will not be a pure network. But using this formulation for our case, allows us to measure the impact of using more accurate information for future demands. As opposed to the formulation and experimental evaluation in [10], we use multiple samples of future demand for this approach.
     </paragraph>
     <paragraph>
      Table B.11 presents the Hybrid Multi-Stage Stochastic optimization formulation for our problem. As HSS considers pure assignment problem at the current timestep, we use {a mathematical formula}V to denote the set of servers and {a mathematical formula}W to denote the set of requests at current timestep. The set {a mathematical formula}W in this model and {a mathematical formula}D1 in our model both represent current demand but as each element of {a mathematical formula}D1 corresponds to multiple requests and as the set {a mathematical formula}W corresponds to individual requests, for each element in {a mathematical formula}D1, there will be multiple elements in the set {a mathematical formula}W. {a mathematical formula}xvw denotes that a server v is assigned to the request w. We set {a mathematical formula}xvw to 0 if the server v can not reach the pickup zone of the request w within τ minutes. {a mathematical formula}uv1 denotes that the server v is held at its initial zone. {a mathematical formula}zoj,djt,k denotes the number of servers moving from the zone {a mathematical formula}oj to the zone {a mathematical formula}dj at time t in the sample k. {a mathematical formula}yit,k denotes the number of servers held at the zone i at timestep t in sample k. We abuse the notation a bit and also use {a mathematical formula}δijt,t′ as a binary constant which is 1 if the server starting at the decision epoch t from the zone i reaches zone j exactly at the decision epoch {a mathematical formula}t′. We use {a mathematical formula}ov to denote the initial zone of server v and {a mathematical formula}ow and {a mathematical formula}dw to denote the origin and destination zones of the request j.
     </paragraph>
     <paragraph>
      Constraint (A.14) ensures that either the server is assigned to atmost one request or it is held at its initial position. Constraint (A.15) ensures that a request is assigned to utmost one server. Constraint (A.16) ensures that for any sample at any timestep, the number of servers moving between zones is equal to the number of available requests between those pair of zones. Constraint (A.17)–(A.18) ensure that the number of servers held at any zone at any decision epoch is the difference between the number of available servers in the zone and the number of assigned servers from the zone.
     </paragraph>
     <paragraph>
      As at the future stages, servers get assigned to requests if and only if they are present in the same zone, we use zones of large size (2 km) for HSS formulation at future stages as opposed to 0.5 km for our formulation. We did some experiments with 0.5 km zones as well but results were worse than the results obtained with 2 km zone size.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Approximate dynamic programming (ADP)
     </section-title>
     <paragraph>
      In this section, we provide the Approximate Dynamic Programming formulation for our problem of matching servers with the customer demand. The modeling is similar to the stochastic dynamic resource allocation formulation presented by Godfrey et al. [32] for multi-timestep travel time. The modeling uses the language of dynamic resource management where the servers are resources and the customers are tasks. We now describe the different dimensions of the model We define resources (servers) using the following vector
     </paragraph>
     <paragraph>
      {a mathematical formula}At = the total number of servers that we know about at time t.
     </paragraph>
     <paragraph>
      {a mathematical formula}Att′ = the total number of servers that we know about at time t but will become available at time {a mathematical formula}t′, with {a mathematical formula}Aitt′ denoting the number of servers in the zone i.{sup:16}
     </paragraph>
     <paragraph>
      {a mathematical formula}Dt = the customer demand at time t where each element j of {a mathematical formula}Dt has attributes origin zone ({a mathematical formula}oj), destination zone ({a mathematical formula}dj) and the number of requests between the origin and destination zone denoted by {a mathematical formula}Rj. As exact demand is known only for the current time step, {a mathematical formula}Dt=ϕ,t&gt;1.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}ξtD represent the new demand arriving in time step t, where {a mathematical formula}ξtD,k representing the kth sample or scenario.
     </paragraph>
     <paragraph>
      {a mathematical formula}Dt,+ = total customer demand at time t including the new customer demand that first become available in time step t. Therefore, while solving for sample k, {a mathematical formula}Dt,+ includes {a mathematical formula}ξtD,k.
     </paragraph>
     <paragraph>
      Therefore, the system state is given by{a mathematical formula}
     </paragraph>
     <paragraph>
      {a mathematical formula}xijt are the decision variables denoting the number of servers assigned to the demand element j at time t. We use Q to denote the planning timesteps or look ahead timesteps. {a mathematical formula}yit are the intermediate variables denoting the number of servers in the zone i at time t.
     </paragraph>
     <paragraph>
      Therefore, the dynamic programming recursion is given by
     </paragraph>
     <paragraph>
      {a mathematical formula}Vt(St)=E[maxxt,yt⁡gt(xt,yt)+Vt+1(St+1)|St] where {a mathematical formula}gt(xt,yt) denotes the single step reward/objective function value.
     </paragraph>
     <paragraph>
      We then drop the expectation and solve for a single sample at a time. {a mathematical formula}Vt(St,ξtD,k)=[maxxt(ξtD,k),yt(ξtD,k)⁡gt(xt(ξtD,k),yt(ξtD,k)+Vt+1(St+1(ξtD,k)].
     </paragraph>
     <section label="C.1">
      <section-title>
       Value function approximation
      </section-title>
      <paragraph>
       The value function defined above is replaced by a suitable approximation. In general, the value function approximation is defined in terms of resources and it works well when the tasks should be served as soon as possible and in case the tasks are not served they will not be available at the next time step. This holds true for our case where if the demand is unserved, it is removed from the system. Therefore, the value function approximation can be written as
      </paragraph>
      <paragraph>
       {a mathematical formula}Vt(At,ξtD,k)=[maxxt(ξtD,k),yt(ξtD,k)⁡gt(xt(ξtD,k),yt(ξtD,k)+Vt+1(At+1(ξtD,k)] The problem is solved by executing a forward pass through time, determining the set of decisions for a single sample at a time. As we are solving for a single sample at a time, we can drop the samples symbol from the value function.
      </paragraph>
      <paragraph>
       Godfrey et al. [32] proposed a separable approximation, for the multi-timestep travel time, of the form
      </paragraph>
      <paragraph>
       {a mathematical formula}Vt(At)=∑i∈Z∑t′=1Q[Vt,t+t′(At,t+t′)].
      </paragraph>
      <paragraph>
       As the travel times span multiple timesteps, some servers are next available for assignment at time {a mathematical formula}t+1, some at time {a mathematical formula}t+2 and so on. The function {a mathematical formula}Vt,t+t′(At,t+t′) estimates the expected value of only those servers which are next available for assignment at time {a mathematical formula}t+t′. After taking the sum over all possible travel times and all zones, we get the estimated future contribution of all the servers.
      </paragraph>
      <paragraph>
       Here, we would like to highlight that in our case, as the servers can be assigned from nearby zones, the value function may not remain separable across zones as the value of having a extra resource in zoneiwill depend on the number of resources in nearby zones.
      </paragraph>
      <paragraph>
       But it is still possible to assume the separation and apply these approximations for our problem. Linear and piecewise linear value function approximations are typically used to solve these problems as the subproblem has network structure but as we show in the following subsections, in our case the linear and piecewise value function approximation do not have a network subproblem.
      </paragraph>
      <section label="C.1.1">
       <section-title>
        Linear value function approximation
       </section-title>
       <paragraph>
        Linear value function approximation generally works well when value of function is linear in terms of the number of resources or the number of resources in each state can be either 0 or 1. But even when this is not the case, sometimes linear approximations can work reasonably well. {a mathematical formula}Vt(At)=∑i∈Z∑t′=1Q[Vi,t,t+t′(Ai,t,t+t′)] where each of {a mathematical formula}Vi,t,t+t′(Ai,t,t+t′) is given by {a mathematical formula}vi,t,t+t′k⁎Ai,t,t+t′ where {a mathematical formula}vi,t,t+t′k is the slope of the approximation at kth iteration.
       </paragraph>
       <paragraph>
        The formulation which is solved at each time step for each sample is provided in the Table C.12.
       </paragraph>
       <paragraph>
        As we can see, the formulation does not have a network structure due to the presence of binary constants δ in equations (C.4) and (C.5), i.e., the Markov property is broken.
       </paragraph>
       <paragraph>
        Updating the value function
       </paragraph>
       <paragraph>
        The slopes are updated in each forward simulation using the standard update equation as follows{a mathematical formula} where {a mathematical formula}πi,t,t+t′ are the dual variable corresponding to equations C.4 and C.5. We use the dual values obtained after solving the linear relaxation. {a mathematical formula}αk−1 is the step size. We use the stepsize as {a mathematical formula}24+k as mentioned in [32]. For the multi-timestep travel time we perform adjustment to dual values using dual next as proposed in [32].
       </paragraph>
       <paragraph>
        The complete algorithm is presented in Algorithm 1.
       </paragraph>
      </section>
      <section label="C.1.2">
       <section-title>
        Piecewise linear value function approximation
       </section-title>
       <paragraph>
        When we need to estimate the value of having a quantity of some resource and the function is piecewise linear, i.e., the slopes of the function are monotonically increasing or decreasing, piecewise linear value function approximations are used. This is more suitable approximation for the problem of interest in this paper as the value of function increases linearly on having more resources but after reaching a threshold (when the number of servers is sufficient to serve the demand), the value remains constant. Therefore, the slope of value function is monotonic decreasing, i.e., we have a piecewise linear concave function. Let {a mathematical formula}|N| denote the total number of servers in the system, then value function approximation is given by
       </paragraph>
       <paragraph>
        {a mathematical formula}Vt(At)=∑i∈Z∑t′=1Q∑r=1|N|[vi,t,t+t′r(Ai,t,t+t′)] where each of {a mathematical formula}vi,t,t+t′r(Ai,t,t+t′) is given by {a mathematical formula}vˆi,t,t+t′r⁎Ai,t,t+t′ where {a mathematical formula}vˆi,t,t+t′r is the slope of the piecewise component r.
       </paragraph>
       <paragraph>
        The formulation which is solved at each time step for each sample is provided in the Table C.13. As the slopes (v) are monotonic, it ensures that the right values are assigned to the y variables.
       </paragraph>
       <paragraph>
        As we can see, the formulation does not have a network structure due to the presence of binary constants δ in the equations (C.11) and (C.12), i.e., the Markov property is broken.
       </paragraph>
       <paragraph>
        Due to the presence of large number of servers ({a mathematical formula}|N| varies from 1000 to 8000 in our experiments) and the need to execute the formulation multiple times (multiple timesteps and multiple samples), it is not possible to execute this approximation in real time. We also tried using the alternate formulation which defines one variable for each component of the piecewise approximation instead of having the number of variables equal to the number of servers but as we need the dual values to update the value function approximation, we need to solve the linear relaxation of the formulation. The linear relaxation of this modified formulation provides worse result than the linear approximation presented previously.
       </paragraph>
       <paragraph>
        Updating the value function
       </paragraph>
       <paragraph>
        We use the CAVE algorithm used by Godfrey et al. [32] to preserve the concavity after the update of the value function using the piece wise value function approximations.
       </paragraph>
       <paragraph>
        But in our case, as the formulation is not pure network due to the presence of binary constants δ in constraints (C.11) and (C.12), we need to solve the optimization multiple times to compute the left and right hand side dual values and this can not be done within the online time constraints. Similarly re-optimizations are needed to compute the numerical derivatives. Therefore, we use the dual values for the constraints obtained after solving the linear relaxation of the optimization problem in the Table C.13.
       </paragraph>
       <paragraph>
        The complete algorithm is presented in the Algorithm 2.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="Appendix D">
     <section-title>
      Complete proofs of propositions
     </section-title>
     <section label="D.1">
      Proof of Proposition 1
      <paragraph>
       Proposition 1: If {a mathematical formula}∀j,i,i′,t,t′{a mathematical formula}δijt,t′=δi′jt,t′, then the OSTM is reducible to a min cost flow problem.
      </paragraph>
      <paragraph>
       Proof: Min cost flow optimization problems are polynomial time solvable, as they consider deterministic unconditional flows. For the case when each request completes at a fixed decision epoch irrespective of the server assigned to it, we show that the OSTM problem also has deterministic unconditional flows and hence the optimization model for OSTM is equivalent to the min cost flow optimization model. We first describe the network corresponding to the OSTM problem.
      </paragraph>
      <paragraph>
       Nodes: Nodes of the network represent the server zones and requests. Formally, we create a node for each element in the set {a mathematical formula}Z at each decision epoch. A node is also created for each element in {a mathematical formula}Dt,∀t. We also create a source node S and a sink node T. Therefore, the maximum number of nodes in the network will be {a mathematical formula}(|Z|+(|Z|⁎|Z|))⋅M+2.
      </paragraph>
      <paragraph>
       Edges: Intuitively, we have edges to indicate the assignment (server zone to a request) and movement (origin zone to the destination zone). Specifically, we have the following edges in the network.
      </paragraph>
      <list>
       <list-item label="•">
        An edge is created between a node corresponding to the zone i at the decision epoch t and a node for the element j of {a mathematical formula}Dt if {a mathematical formula}oj∈f(i,t). The capacity of the edge is equal to {a mathematical formula}Rjt and the cost of the edge is {a mathematical formula}−Ci,oj,djt. The flow on these edges is given by {a mathematical formula}xijt.
       </list-item>
       <list-item label="•">
        An edge is created between the element j of {a mathematical formula}Dt and the node corresponding to the zone i at decision epoch {a mathematical formula}t′ ({a mathematical formula}t′&gt;t), if {a mathematical formula}dj=i and {a mathematical formula}δjt,t′=1 ({a mathematical formula}∀j,i,i′,t,t′δijt,t′=δi′jt,t′, therefore we define {a mathematical formula}δjt,t′=δijt,t′∀i,j,t,t′). The capacity of the edge is {a mathematical formula}Rjt and the cost is 0. We denote the flow on these edges by {a mathematical formula}yjt.
       </list-item>
       <list-item label="•">
        An edge is created between the node corresponding to the zone i at decision epoch t and the node corresponding to the zone i at decision epoch {a mathematical formula}t+1 to have the flow of unassigned servers, i.e., to ensure that the unassigned servers from the zone i at decision epoch t remain in the same zone at next decision epoch. The capacity of this edge is equal to {a mathematical formula}∑iNi and the cost is 0. The flow on these edges is denoted by {a mathematical formula}wit.
       </list-item>
       <list-item label="•">
        From source node S, we create an edge to all the zone nodes at the decision epoch 1. The capacity of edge between the source node S and the zone i node is {a mathematical formula}Ni (the number of initial servers in zone i) and the cost is 0.
       </list-item>
       <list-item label="•">
        If the requests present in the element j of {a mathematical formula}Dt,∀t complete at a decision epoch &gt;M, then we create an edge between the element j of {a mathematical formula}Dt to the sink T. The capacity of the edge is {a mathematical formula}Rjt and the cost is 0.
       </list-item>
       <list-item label="•">
        We also create edges from the zone nodes at decision epoch M (last decision epoch) to the sink node T. The capacity of the edge is {a mathematical formula}∑iNi and the cost is 0.
       </list-item>
      </list>
      <paragraph>
       Given this network, we can view the similarity of the two optimization models in Table C.14. The transformation uses slack variables ({a mathematical formula}wit) and the intermediate variables ({a mathematical formula}yjt) to convert the original OSTM constraints into the flow and capacity constraints present in the min cost flow model. As the min cost flow is polynomial time solvable and gives integral flow values for the integer capacities, we can solve the OSTM also in polynomial time to get integer solutions.  □
      </paragraph>
      <paragraph label="Example 3">
       The example network with three zones and {a mathematical formula}M=3 is shown in the Fig. D.18. S and T denote the source and sink node. Circular nodes represent the server zone nodes and rectangular nodes represent the request nodes between zones. Requests between the zones {a mathematical formula}Z2 and {a mathematical formula}Z3 at decision epoch 1 complete at decision epoch 3. Requests between the zones {a mathematical formula}Z1 and {a mathematical formula}Z3 complete at decision epoch 4 and as {a mathematical formula}M=3, they are connected to sink node T. N denotes the total number of servers available initially, i.e., {a mathematical formula}N=N1+N2+N3. Each arc contains 2 values with the first value representing capacity and the second value representing the cost.
      </paragraph>
      <paragraph>
       In general, depending on the server assigned, a request can have a maximum of {a mathematical formula}⌈τΔ⌉+1 different completion decision epochs. Therefore, in the network constructed in the Proposition 1, we will have edges between the decision epoch t request nodes to the decision epoch {a mathematical formula}t′,t′+1,..,t′+⌈τΔ⌉ zone nodes with the flow on these edges conditioned to be equal to the flow on the edges from the server node to request nodes.
      </paragraph>
      <paragraph>
       In the example shown in the Fig. D.18, suppose if the {a mathematical formula}Z2 server is assigned to the request between zones {a mathematical formula}Z2 and {a mathematical formula}Z3, then the request completes at decision epoch 3 and if the {a mathematical formula}Z1 server is assigned to the request between zones {a mathematical formula}Z2 and {a mathematical formula}Z3, the request will complete at decision epoch 4. The modified network is shown in Fig. D.19. Now the node {a mathematical formula}Z2,Z3 at decision epoch 1 will have the capacity {a mathematical formula}R231 with the condition that flow on 2 green edges should be equal and flow on 2 orange edges should be equal. Proposition 2 shows that in the above case where there are conditional flows, the OSTM is NP-hard.
      </paragraph>
     </section>
     <section label="D.2">
      Proof of Proposition 2
      <paragraph>
       Proposition 2: If {a mathematical formula}∃j,i,i′,t,t′s.t.δijt,t′≠δi′jt,t′, then the OSTM is NP-hard.
      </paragraph>
      <paragraph>
       Proof: To show that the OSTM is NP-hard in general case, we reduce the well known 3-SAT problem to OSTM. We construct an instance of the OSTM for any arbitrary instance of 3-SAT with L clauses and V variables. We show that we obtain the optimal value for the OSTM if and only if there exists an assignment to variables in 3-SAT formula such that all the clauses in 3-SAT will evaluate to true.
      </paragraph>
      <paragraph>
       For any arbitrary instance of 3-SAT with L clauses and V variables, we construct an instance of OSTM as follows:
      </paragraph>
      <list>
       <list-item label="•">
        We create an OSTM problem instance with {a mathematical formula}4L+1 decision epochs, i.e., {a mathematical formula}M=4L+1. At first decision epoch, we create 2V requests. At remaining 4L decision epochs, we create one request each.
       </list-item>
       <list-item label="•">
        We create {a mathematical formula}2V+1 zones, denoted by {a mathematical formula}Z0 and {a mathematical formula}Zi,Zi′,i&lt;=V. So the set of zones {a mathematical formula}Z={Z0,Zi,Zi′,i&lt;=V}.
       </list-item>
       <list-item label="•">
        Initially zones {a mathematical formula}Zi have one server each and zones {a mathematical formula}Z0 and {a mathematical formula}Zi′ have zero servers.
       </list-item>
       <list-item label="•">
        We create 2V requests at first decision epoch. Each zone {a mathematical formula}Zi is the origin zone of two requests with one request having destination in {a mathematical formula}Zi and one request having destination in {a mathematical formula}Zi′. Requests having origin in {a mathematical formula}Zi at decision epoch 1, can only be assigned server from the zone {a mathematical formula}Zi. Therefore, {a mathematical formula}D1={&lt;Zi,Zi,1&gt;,&lt;Zi,Zi′,1&gt;} and {a mathematical formula}f(Zi,1)={Zi}. All the requests at the first decision epoch have unit revenue.
       </list-item>
       <list-item label="•">
        If zone i server is assigned to the request between zone pairs {a mathematical formula}&lt;Zi,Zi&gt; then the variable {a mathematical formula}xi is true else if it is assigned to the request between zone pairs {a mathematical formula}&lt;Zi,Zi′&gt; then {a mathematical formula}xi is false. Requests served at decision epoch 1 determines the value of variables {a mathematical formula}xi. Therefore, at second decision epoch, server will be available in zone {a mathematical formula}Zi if {a mathematical formula}xi is true, and will be available in the zone {a mathematical formula}Zi′ if {a mathematical formula}xi is false.
       </list-item>
       <list-item label="•">
        If there are L clauses, we create L requests with request corresponding to kth clause at decision epoch {a mathematical formula}4k−2. Each of these requests have destination in the zone {a mathematical formula}Z0. The origin zone of these requests is the zone corresponding to the first literal of the kth clause.In addition, if the kth clause has literal {a mathematical formula}xi then the zone {a mathematical formula}Zi server can be assigned to the request at decision epoch {a mathematical formula}4k−2 and if the kth clause has literal {a mathematical formula}¬xi, then the zone {a mathematical formula}Zi′ can be assigned to the request. On the other hand, if the kth clause does not contain literal {a mathematical formula}xi then zone {a mathematical formula}Zi server can not be assigned to the request at decision epoch {a mathematical formula}4k−2. In short, request at the decision epoch {a mathematical formula}4k−2 can be assigned server only from 3 zones which correspond to the literals present in the kth clause. Therefore, the request at decision epoch {a mathematical formula}4k−2 will have at least one server available if clause evaluates to true, i.e., if at least one of the literals has true value.On assigning a server from the zone corresponding to the first literal, request completes at decision epoch {a mathematical formula}4k−1 earning revenue 1, on assigning a server from the zone corresponding to second literal, request completes at decision epoch 4k earning revenue 2 and on assigning a server from the zone corresponding to the third literal, request completes at decision epoch {a mathematical formula}4k+1 earning revenue 3.
       </list-item>
       <list-item label="•">
        At decision epoch {a mathematical formula}4k−1, a request is present between zone {a mathematical formula}Z0 and the zone corresponding to first literal of kth clause with revenue 3. At decision epoch 4k, a request is present between zone {a mathematical formula}Z0 and the zone corresponding to second literal of kth clause with revenue 2. Similarly, at the decision epoch {a mathematical formula}4k+1, a request is present between zones {a mathematical formula}Z0 and the zone corresponding to the third literal of kth clause with revenue 1.The requests at decision epoch {a mathematical formula}4k−1,4k and {a mathematical formula}4k+1 can be assigned a server only from zone {a mathematical formula}Z0. The server will be available in zone {a mathematical formula}Z0 only if the request at decision epoch {a mathematical formula}4k−2 is served. As there is only one request available at the decision epoch {a mathematical formula}4k−2, maximum one of these three requests can be served. The maximum revenue which can be earned by serving the requests between decision epochs {a mathematical formula}4k−2 to {a mathematical formula}4k+1 is 4.After serving the request at decision epoch {a mathematical formula}4k−2 and one of the requests at decision epochs {a mathematical formula}4k−1,4k or {a mathematical formula}4k+1 such that total revenue is 4, the availability of servers in the zones at decision epoch {a mathematical formula}4k+2 will be same as decision epoch {a mathematical formula}4k−2. Therefore, next clause will be evaluated for the same assignment of variables.
       </list-item>
      </list>
      <paragraph>
       We now show that there is an assignment of values to the variables in the 3-SAT instance so that the formula evaluates to true if and only if there exists a solution to the OSTM problem with objective value {a mathematical formula}V+4L.
      </paragraph>
      <paragraph>
       The “if” direction: Suppose there exists a solution with the objective value {a mathematical formula}V+4L. As maximum revenue which can be earned by serving the requests between decision epochs {a mathematical formula}4k−2 and {a mathematical formula}4k+1 is 4 and the maximum revenue earned at first decision epoch is V, it means that V requests are assigned a server at first decision epoch earning a total revenue V and one request is served at each of the decision epochs {a mathematical formula}4k−2,∀k=1..L and one request is served from every three decision epochs {a mathematical formula}4k−1,4k and {a mathematical formula}4k+1 earning a total revenue of 4L. The variable {a mathematical formula}xi is set to true if at first decision epoch zone {a mathematical formula}Zi server is assigned to the request having destination in zone {a mathematical formula}Zi otherwise it is set to false.
      </paragraph>
      <paragraph>
       This will be a solution to 3-SAT instance as all the request at decision epoch {a mathematical formula}4k−2 are served (i.e., all clauses are true) and as the revenue earned between decision epochs {a mathematical formula}4k−2 and {a mathematical formula}4k+1 is 4, at decision epoch {a mathematical formula}4k+2 the servers availability is same as at decision epoch 2.
      </paragraph>
      <paragraph>
       So if there is a solution to the OSTM problem, we can find an assignment for 3-SAT instance.
      </paragraph>
      <paragraph>
       The “only if” direction: Suppose there is an assignment of values to the variables such that the 3-SAT formula evaluates to true. So at decision epoch 1, if {a mathematical formula}xi is true, we assign {a mathematical formula}Zi server to request having destination in zone {a mathematical formula}Zi otherwise it is assigned to the request having destination in zone {a mathematical formula}Zi′. Therefore, revenue earned at decision epoch 1 will be V. Now, as the 3-SAT formula evaluates to true, at decision epoch 2, we will have at least one server available to serve the request. If the first literal of the first clause is true we assign it to request at decision epoch 2 and serve the request at decision epoch 3 earning a revenue of 4. If first literal is false but second literal is true, then we assign it to request at decision epoch 2 and serve the request at decision epoch 4 earning a revenue of 4. If first and second literal are false but the third literal is true then we assign it to request at decision epoch 2 and serve the request at decision epoch 5 earning a revenue of 4. Therefore we can serve request at decision epoch 2 and one of the requests at decision epoch {a mathematical formula}3,4 or 5 and earn a total revenue of 4. At decision epoch 6 the servers, the availability of servers will be same as at decision epoch 2. As all the clauses of 3-SAT evaluate to true, the second clause will also be true and at decision epoch 6 we will have at least one server available to serve the request. Therefore, for each clause in 3-SAT, we will serve 2 requests earning a revenue of 4 resulting in objective value of the OSTM to be {a mathematical formula}V+4L  □
      </paragraph>
      <paragraph label="Example 4">
       We show the graphical representation in the Fig. D.20 for an example 3-SAT clause {a mathematical formula}(x1∨x2∨x3)∧(x1∨¬x2∨¬x3). Initially, there is one server available in zone {a mathematical formula}Z1,Z2 and {a mathematical formula}Z3 denoted by flow of 1 from the source S. At each decision epoch, the circular nodes represent the server zone nodes and rectangular nodes represent the request nodes with vertex capacity as the number of requests between the zone pairs. The edge between the server node and the request node at a decision epoch represent that server can be assigned to the request. The revenue obtained on assigning a server to the request is marked on the edge. The value of flow on the edge will represent the number of zone servers assigned to request. At first decision epoch, depending on the assignment of server to the requests, the value of {a mathematical formula}x1,x2,x3 will be 1 or 0 (true or false). At second decision epoch, the request node has edges from {a mathematical formula}Z1,Z2 and {a mathematical formula}Z3. That is the server will be assigned to the request if one of these zones has a server available. Also as the capacity of node is 1, only one of the servers from these zones will be assigned a request. If server of {a mathematical formula}Z1 is assigned to the request at decision epoch 2, the black edges represent the movement of server. After serving the request at decision epoch 3, the server will become available in the zone {a mathematical formula}Z1 again. Similarly green edges show the movement of server if server from zone {a mathematical formula}Z2 is assigned and orange edges show the movement of server, if server from zone {a mathematical formula}Z3 is assigned. Unassigned servers at decision epoch 2, will remain in the same zones and their movement is represented through dotted lines in the graph. At decision epoch 6, the server distribution in the zones will be same as decision epoch 2 as the servers which moved between decision epoch 2 and 6 came back into the same zone at decision epoch 6.
      </paragraph>
     </section>
     <section label="D.3">
      Proof of Proposition 3
      <paragraph>
       Proposition 3: Solving TSS for more than one sample is an NP-hard problem irrespective of the δ values.
      </paragraph>
      <paragraph>
       Proof: To show that solving TSS for more than one sample is NP-hard, we reduce the 3-SAT problem to TSS. We construct an instance of TSS for any arbitrary instance of 3-SAT with L clauses and V variables. We show that we obtain the optimal value of {a mathematical formula}V+1 for TSS if and only if there exists an assignment of variables such that the 3-SAT clause evaluates to true.
      </paragraph>
      <paragraph>
       Each clause of 3-SAT corresponds to one sample in TSS. Each sample has one request, i.e., if the clause evaluates to true, request in the sample is served by a server else it will not be served. The first stage requests are created so that they consider all possible (true/false) values for the variables. Intuitively, the first stage decides the assignment of variables present in clauses and the second stage evaluates the clauses for those variable assignments.
      </paragraph>
      <paragraph>
       The detailed steps are as follows:
      </paragraph>
      <list>
       <list-item label="•">
        If there are V variables L clauses we create {a mathematical formula}2V+L zones, denoted by {a mathematical formula}{Zi,Zi′,i&lt;=V} and {a mathematical formula}{Zsk,k=1,2,...,L}.
       </list-item>
       <list-item label="•">
        Initially zones {a mathematical formula}Zi have one server each and other zones have zero servers.
       </list-item>
       <list-item label="•">
        We create 2V requests at the first stage. Each zone {a mathematical formula}Zi is the origin zone of two requests with one request having destination in {a mathematical formula}Zi and one request having destination in {a mathematical formula}Zi′. Requests having origin in zone {a mathematical formula}Zi can only be assigned servers from zones {a mathematical formula}Zi. Therefore, {a mathematical formula}D1={&lt;Zi,Zi,1&gt;,&lt;Zi,Zi′,1&gt;i&lt;=V}, {a mathematical formula}f(Zi,1)={Zi}. All the requests have unit revenue.
       </list-item>
       <list-item label="•">
        If the zone {a mathematical formula}Zi server is assigned to the request having destination in zone {a mathematical formula}Zi then the variable {a mathematical formula}xi is true else if it is assigned to the request having destination in the zone {a mathematical formula}Zi′ then {a mathematical formula}xi is false. Requests served at the first decision epoch determine the value of variables {a mathematical formula}xi. Therefore, at the second stage, server will be available in the zone {a mathematical formula}Zi if {a mathematical formula}xi is true, and will be available in zone {a mathematical formula}Zi′ if {a mathematical formula}xi is false.
       </list-item>
       <list-item label="•">
        If there are n clauses, we create n requests (one request in each sample). {a mathematical formula}|ξD|=L and {a mathematical formula}ξ2D,k has one element. Request in kth sample has origin in the zone {a mathematical formula}Zsk and destination in {a mathematical formula}Z1.{a mathematical formula}ξ2D,k={&lt;Zsk,Z1,1&gt;. All requests have unit revenue.
       </list-item>
       <list-item label="•">
        If the kth clause has literal {a mathematical formula}xi then zone {a mathematical formula}Zi server can be assigned to the request in sample k, and if the kth clause has literal {a mathematical formula}¬xi, then zone {a mathematical formula}Zi′ can be assigned to the request in sample k. On the other hand, if the kth clause does not contain literal {a mathematical formula}xi then zone {a mathematical formula}Zi server can not be assigned to the request in sample k. In short, request in kth sample can be assigned server only from 3 zones which correspond to literals present in kth clause.
       </list-item>
       <list-item label="•">
        Now, the request in sample k will have at least one server available if clause evaluates to true, i.e., if one of the literals has true value.
       </list-item>
      </list>
      <paragraph>
       We now show that there is an assignment of values to the variables in the 3-SAT instance so that the formula evaluates to true if and only if there exists a solution to TSS with objective value {a mathematical formula}V+1.
      </paragraph>
      <paragraph>
       The “if” direction: Suppose there exists a TSS solution with the objective value {a mathematical formula}V+1, it means that V requests are assigned a server at the first stage and in all the L samples requests are assigned a server. The variable {a mathematical formula}xi is set to true if at the first stage zone {a mathematical formula}Zi server is assigned to the request having destination in zone {a mathematical formula}Zi otherwise it is set to false. This will be a solution to the 3-SAT instance as requests in all the samples are served so at least one of the literals in each clause is set to true. So if there is a solution to TSS instance, we can find an assignment for 3-SAT instance.
      </paragraph>
      <paragraph>
       The “only if” direction: Suppose there is an assignment of values to the variables such that the 3-SAT formula evaluates to true. So if {a mathematical formula}xi is true, we assign {a mathematical formula}Zi server to request having destination in zone {a mathematical formula}Zi otherwise it is assigned to the request having destination in zone {a mathematical formula}Zi′. Now, in each sample for each request, we will have at least one server available so we can serve all the L requests at the second stage. Therefore objective value of TSS will be {a mathematical formula}V+1L⋅L=V+1.  □
      </paragraph>
     </section>
     <section label="D.4">
      Proof of Proposition 4
      <paragraph>
       Proposition 4In OLSTM without sample information and adversarial behavior from environment, when maximizing the number of requests satisfied for a fixed number of servers N, the competitive ratio, c for any deterministic b-stage algorithm (i.e., with information available up to the bth decision epoch) in a M-decision epoch ({a mathematical formula}M≥b) problem is{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       Before we describe the key elements of the proof, we first provide the key terms that will be used in this proof:
       <list>
        ALG denotes the value of the best deterministic b-stage algorithm over M decision epochs.OPT denotes the value obtained by an M-stage optimal algorithm over M decision epochs.N is the number of servers available.Let {a mathematical formula}OPTb denote the value of optimal solution for first b decision epochs (i.e., the maximum number of requests which can be served in first b decision epochs).In order to show the upper bound on competitive ratio, we will consider different cases on values that can be taken by
       </list>
       <paragraph>
        o. Since we are computing competitive ratio (least value of {a mathematical formula}ALG(I)OPT(I)), we identify the least value of the numerator and the highest value of the denominator.
       </paragraph>
       <list>
        <list-item label=" (1)">
         {a mathematical formula}OPTb≥N, i.e., the number of requests served in the first b decision epochs is greater than NAs ALG denotes the number of requests served by the best deterministic b-stage algorithm over M decision epochs. Therefore, at the very least, it can obtain the optimal solution for b decision epochs and hence:{a mathematical formula}Since OPT is the value obtained by an M-stage optimal algorithm, it can potentially serve N requests for every one of the remaining {a mathematical formula}(M−b) time steps. Therefore,{a mathematical formula}Hence, we have:{a mathematical formula}The above expression will be minimum when {a mathematical formula}OPTbN is minimum. As {a mathematical formula}OPTb≥N, the minimum value of {a mathematical formula}OPTbN is 1. Therefore,{a mathematical formula}(2) {a mathematical formula}OPTb&lt;N, i.e., the number of requests served in first b decision epochs is lower than NAs the number of requests served in first b decision epochs is lower than N, there will be some servers which did not move from their initial position. So if optimal algorithm uses these servers to serve requests, deterministic algorithm can also serve requests using them, As the minimum value of ALG and OPT is {a mathematical formula}OPTb, we take {a mathematical formula}ALG=OPTb+x and {a mathematical formula}OPT=OPTb+y. Assume the competitive ratio in this case is better than {a mathematical formula}11+M−b. Therefore,{a mathematical formula}{a mathematical formula}{a mathematical formula}
        </list-item>
       </list>
       <paragraph>
        As the maximum number of requests served in remaining {a mathematical formula}M−b decision epochs is {a mathematical formula}N⁎(M−b),{a mathematical formula} From equation (D.14) and (D.15),{a mathematical formula}As the value of ALG in all M decision epochs is less than N, {a mathematical formula}N−(OPTb+x) servers did not move from their initial position. Therefore, even for the optimal algorithm, {a mathematical formula}N−(OPTb+x) servers will not be moving. So,{a mathematical formula} RHS {a mathematical formula}&gt;1M−b+1. But we assumed {a mathematical formula}OPTb+xOPTb+y&lt;1M−b+1 which is a contradiction. Thus,{a mathematical formula}
       </paragraph>
      </paragraph>
      <paragraph>
       We can also extend the above reasoning for the case when objective is to maximize revenue. If revenue of any request {a mathematical formula}C∈{Cmin,Cmax}, then at first b stages, requests with revenue {a mathematical formula}Cmin are served by both deterministic and optimal algorithm and for the remaining decision epochs requests with revenue {a mathematical formula}Cmax are served by optimal algorithm. Therefore, the competitive ratio will be {a mathematical formula}CminCmin+(M−b)⁎Cmax.
      </paragraph>
      <paragraph>
       The competitive ratio is low mainly due to the assumption that server only moves when it is assigned to a request. Therefore, the adversary can take more advantage by creating requests in the zones which are not reachable from the server position.
      </paragraph>
      <paragraph>
       It should be possible to improve the competitive ratio on removing this assumption. By taking decision to move randomly to another zone if no request is available at the current stage, we may improve the competitive ratio against an online adversary (i.e., the adversary who is not aware of the output of random decision).
      </paragraph>
     </section>
     <section label="D.5">
      Proof of Proposition 5
      <paragraph>
       Proposition 5: In OLSTM with sample information and stochastic behavior from environment according to the samples, when maximizing the number of requests satisfied, the expected competitive ratio, {a mathematical formula}cμ, of the TSS algorithm is{a mathematical formula} where M is the number of decision epochs ({a mathematical formula}M≥3).
      </paragraph>
      <paragraph>
       Proof: To prove the upper bound on the expected competitive ratio, we construct a worst case distribution and show the value of expected competitive ratio for that distribution. The value of expected competitive ratio for any specific distribution is upper bound on the true value.
      </paragraph>
      <paragraph>
       We assume that there is a positive probability of having a request at second decision epoch.{sup:17} As the TSS only knows distribution for the next decision epoch, we create an instance such that TSS can not serve any requests after first two decision epochs.
      </paragraph>
      <paragraph>
       We construct a worst case instance with one server and two requests at first two decision epochs. Initially, the server is located in zone {a mathematical formula}Z1, the two requests are request 1, {a mathematical formula}r1=&lt;Z1,Z1&gt; and request 2, {a mathematical formula}r2=&lt;Z1,Z2&gt;. Requests originating in zone {a mathematical formula}Z1 can only be served by server in zone {a mathematical formula}Z1. Similarly request originating in zone {a mathematical formula}Z2 can only be served by server in {a mathematical formula}Z2.
      </paragraph>
      <paragraph>
       As per the distribution at decision epoch 2, the probability that request has origin and destination in {a mathematical formula}Z1 is {a mathematical formula}P1 and probability that request has origin and destination in {a mathematical formula}Z2 is {a mathematical formula}P2 and the probability is zero for all other zone pairs. {a mathematical formula}P1 and {a mathematical formula}P2 are independent of each other. Also as per the distribution, at subsequent decision epochs, there is zero probability of a request having origin in zone {a mathematical formula}Z1 and 1 probability of requests having origin and destination at {a mathematical formula}Z2.
      </paragraph>
      <paragraph>
       The TSS algorithm will make the first stage assignment based on the expected number of requests served, i.e., it will maximize {a mathematical formula}1+max⁡(P1,P2). If {a mathematical formula}P1≥P2, TSS will assign the server to request 1 at decision epoch 1 and will serve request at decision epoch 2 with probability {a mathematical formula}P1. TSS will not be able to serve any more requests at subsequent decision epoch.
      </paragraph>
      <paragraph>
       The M-stage optimal algorithm will assign server to request 2 at first decision epoch. At second decision epoch, the M-stage optimal algorithm will be able to serve the request if it originates in zone {a mathematical formula}Z2 otherwise it will not. The M-stage algorithm will be able to serve requests at all subsequent decision epochs.{sup:18} Therefore, the expected competitive ratio is given by{a mathematical formula} The four terms correspond to four possible cases of drawing 2 requests from the given distribution. Rearranging the terms, we get{a mathematical formula} From equation (D.17), as {a mathematical formula}1M−1&gt;1M, for a fix value of {a mathematical formula}P1, on increasing the value of {a mathematical formula}P2 the expected competitive ratio decreases. As {a mathematical formula}P1≥P2, to minimize the expected value of competitive ratio, we take {a mathematical formula}P2=P1. Substituting {a mathematical formula}P2=P1 in equation (D.17), we get{a mathematical formula} The above expression will be minimum when the derivative (with respect to {a mathematical formula}P1) is 0, i.e.,{a mathematical formula}
      </paragraph>
      <paragraph>
       As {a mathematical formula}0≤P1≤1, and M is a positive integer, the possible value of {a mathematical formula}P1 are 0, 0.5 and 1.0. Since, we have a positive probability of having request at second decision epoch, {a mathematical formula}P1=0 is not possible. Therefore, the competitive ratio will be minimum when {a mathematical formula}P1=0.5 or 1. On substituting {a mathematical formula}P1=P2=1.0, in equation (D.17), we get {a mathematical formula}2M and on substituting {a mathematical formula}P1=P2=0.5, in equation (D.17), we get {a mathematical formula}34⁎(M−1)+34⁎M
      </paragraph>
      <paragraph>
       As {a mathematical formula}2M&gt;34⁎(M−1)+34⁎M, for {a mathematical formula}M≥3, therefore{a mathematical formula}
      </paragraph>
      <paragraph>
       As there exists an instance for which the expected competitive ratio of TSS can not be more than {a mathematical formula}34⁎(M−1)+34⁎M, we can say that {a mathematical formula}34⁎(M−1)+34⁎M is the upper bound on the expected competitive ratio of TSS.
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>