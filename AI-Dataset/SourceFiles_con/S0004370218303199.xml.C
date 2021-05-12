<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Algorithms for electric vehicle scheduling in large-scale mobility-on-demand schemes.
   </title>
   <abstract>
    We study a setting where Electric Vehicles (EVs) can be hired to drive from pick-up to drop-off points in a Mobility-on-Demand (MoD) scheme. The goal of the system is, either to maximize the number of customers that are serviced, or the total EV utilization. To do so, we characterise the optimisation problem as a max-flow problem in order to determine the set of feasible trips given the available EVs at each location. We then model and solve the EV-to-trip scheduling problem offline and optimally using Mixed Integer Programming (MIP) techniques and show that the solution scales up to medium sized problems. Given this, we develop two non-optimal algorithms, namely an incremental-MIP algorithm for medium to large problems and a greedy heuristic algorithm for very large problems. Moreover, we develop a tabu search-based local search technique to further improve upon and compare against the solution of the non-optimal algorithms. We study the performance of these algorithms in settings where either battery swap or battery charge at each station is used to cope with the EVs' limited driving range. Moreover, in settings where EVs need to be scheduled online, we propose a novel algorithm that accounts for the uncertainty in future trip requests. All algorithms are empirically evaluated using real-world data of locations of shared vehicle pick-up and drop-off stations. In our experiments, we observe that when all EVs carry the same battery which is large enough for the longest trips, the greedy algorithm with battery swap with the max-flow solution as a pre-processing step, provides the optimal solution. At the same time, the greedy algorithm with battery charge is close to the optimal (97% on average) and is further improved when local search is used. When some EVs do not have a large enough battery to execute some of the longest trips, the incremental-MIP generates solutions slightly better than the greedy, while the optimal algorithm is the best but scales up to medium sized problems only. Moreover, the online algorithm is shown to be on average at least 90% of the optimal. Finally, the greedy algorithm scales to 10-times more tasks than the incremental-MIP and 1000-times more than the static MIP in reasonable time.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      In a world where over 60% of the total population will be living in, or around, cities the current personal transportation model is not sustainable as it is based almost entirely on privately owned internal combustion engine vehicles. These vehicles cause high pollution (e.g., air and sound), and face low utilization rates{sup:1}[52]. Electric Vehicles (EVs) can be an efficient alternative to those using internal combustion engines when it comes to running costs [17], environmental impact, and quality of driving. However, these advantages come with a trade-off, as EVs have short ranges and long charging times. To address such issues, cities typically resort to building a large number of charging stations with fast chargers, or battery swapping capabilities. Now, such facilities are only worth building if there are enough EVs to use them. However, drivers will not buy EVs if charging stations are not first available, leading to a catch-22 situation.
     </paragraph>
     <paragraph>
      In order to increase vehicle utilization, Mobility-on-Demand (MoD) schemes have been advocated [30]. MoD involves vehicles that are used by either individuals, or small groups of commuters, thus providing them with an alternative from using their privately owned vehicles. Such systems have the potential to reduce traffic congestion in urban areas, as well as the need for large numbers of parking spots.{sup:2} By doing so, MoD also aims to achieve considerably higher vehicle utilization rates compared to individually owned ones (i.e., few vehicles will cover the transportation needs of many commuters). Moreover, other advantages include the fact that car ownership is reduced, as well as less up-front charges which means low-income people may be better served.
     </paragraph>
     <paragraph>
      Given the benefits of EVs and MoD schemes, in this paper we explore scenarios within which EVs could be used within MoD schemes, and consider their associated optimisation challenges. By addressing these challenges, the advantages of the two transportation modes would be combined [30], [10]. Moreover, the use of EVs in MoD schemes offer an opportunity to further market EVs to potential car owners as they get to try the technology before buying it. In this way, EV-equipped MoD schemes would help popularise EVs, while at the same time having a positive impact in urban traffic conditions as well as the environment.
     </paragraph>
     <paragraph>
      To date, a number of MoD schemes, such as ZipCar,{sup:3} or CarShare{sup:4} have been proposed, albeit most of them using normal cars. However, EVs present new challenges for MoD schemes. For example, EVs have a limited range that requires them to either charge regularly or have their battery swapped when they stop. Moreover, if such MoD schemes are to become popular, it is important to ensure that charging/swap capacity is managed and scheduled to allow for the maximum number of consumer requests to be serviced across a large geographical area. In addition, in order for MoD schemes to be economically sustainable, and given the higher cost of buying EVs compared to conventional vehicles, it is important to have them working at maximum capacity and servicing the maximum number of customers around the clock.
     </paragraph>
     <paragraph>
      Against this background, we model the MoD scheme for EVs and develop a number of algorithms to solve the problem of scheduling trips for MoD consumers in order to maximize the number of trip requests serviced while coping with the limited range of EVs. These algorithms attempt to deal with the computational complexity of the scheduling problem in a number of contexts (online v/s offline, with battery swap or battery charge, small-sized or large problems). Thus, we first recast the scheduling problem as a max-flow problem whose solution lets us determine the (upper limit) of trip requests able to be executed given a set of available EVs. Then, we show how the scheduling of trips in the MoD scheme is a highly combinatorial problem, for which an optimal offline solution, where all demand is known in advance, scales only up to medium sized problems (tens of EVs and hundreds of trips). Thus, to cope with large problems, we also develop two near-optimal offline solutions, namely an incremental MIP and a greedy heuristic, as well as a tabu search-based local search technique to further improve the solution quality of the non-optimal algorithms. Moreover, to tackle the online version of the problem, where demand is not known in advance, we develop an online scheduling algorithm. In all cases, and given the limited range of EVs, we consider situations where they can either have their battery swapped (with a fully charged one), or charged at the stations. The work presented here has been initiated at [38] with basic versions of the MIP and the greedy algorithms for battery swapping. Specifically, this paper advances the state of the art as follows:
     </paragraph>
     <list>
      <list-item label="1.">
       We provide a characterisation of the MoD scheme as a max-flow problem. By solving this problem, we are able to determine the set of all feasible trips given a set of available EVs.
      </list-item>
      <list-item label="2.">
       We propose an optimal Mixed Integer Programming (MIP) formulation of the problem of scheduling EVs in a MoD scheme that maximizes the number of completed tasks (i.e., trip requests from consumers) or the EV utilization (i.e., number of time points each EV is travelling), either using battery swap or battery charging at each station.
      </list-item>
      <list-item label="3.">
       Given the average scalability of the optimal solution, we develop an incremental-MIP and a greedy heuristic algorithm which are shown to generate near-optimal solutions with considerably lower execution times.
      </list-item>
      <list-item label="4.">
       We propose a tabu search-based local search technique in order to further improve the solution quality of the non-optimal algorithms.
      </list-item>
      <list-item label="5.">
       We propose a battery swap optimization algorithm which minimizes the number of necessary battery swaps in order to reduce the need for spare batteries and thus, cost.
      </list-item>
      <list-item label="6.">
       We propose an online algorithm for scheduling EV trips across the MoD that can cope with uncertainty in the number of future trip requests.
      </list-item>
      <list-item label="7.">
       Finally, using real-world data of shared vehicle stations in Washington, DC we observe that when all EVs carry the same battery which is large enough for the longest trips, the greedy algorithm with battery swap in combination with the max flow provides the optimal solution. At the same time, the variation with battery charge is at 97% of the optimal without the local search, and at 98.5% when local search is used. Moreover, in case where some EVs do not have a large enough battery to execute some of the longest trips, we observe that the greedy algorithm does not provide the optimal solution anymore and that the incremental MIP is the correct choice as it generates solution 0.5% better than the greedy and with lower execution time, while the optimal algorithm is the best but scales up to medium sized problems only. Moreover, we show that when the objective is the maximization of EV utilization, the utilization increases by 3.6% and the number of completed tasks reduces by 1.5% on average. In addition, the online algorithm is at least 90% of the optimal. In terms of scalability, the greedy algorithm (without local search) scales to 10-times more tasks than the incremental MIP and 1000-times more than the static MIP in reasonable time.
      </list-item>
     </list>
     <paragraph>
      When taken together, our algorithms and results establish the first benchmarks for the study of EV scheduling algorithms in MoD schemes.
     </paragraph>
     <paragraph>
      The rest of the paper is structured as follows: Section 2 discusses the related work, Section 3 presents the model of a typical MoD scheme and Section 4 presents the formulation of the problem as a max flow one. Section 5 presents the MIP formulation of the problem with battery swap (Section 5.1) and with battery charge (Section 5.2), the incremental MIP scheduling algorithm (Section 5.3), the greedy algorithm with battery swap (Section 5.4) and battery charge (Section 5.5), the local search algorithm (Section 5.6) and the battery swap optimization algorithm (Section 5.7). Moreover, Section 6 presents the online scheduling algorithm and Section 7 describes our empirical evaluation. Finally, Section 8 concludes and presents future work.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      In the problem we study in this paper, we have a set of locations which act as pick-up and drop-off stations and a number of EVs available at each station. Tasks (i.e., trip requests for a specific point in time) are collected by the MoD company and an assignment of EVs to tasks is calculated. EV relocation is not supported, thus the end location of one executed task is always the start location of another. After the execution of each task, the EVs' battery is either replaced with a fully charged one, or charged. In this section, related work both in terms of the problem structure, as well as problem domain and application is presented.
     </paragraph>
     <section label="2.1">
      <section-title>
       Vehicle routing and scheduling problems
      </section-title>
      <paragraph>
       Our work shares similarities with other vehicle routing and scheduling problems such as bike sharing, rolling stock, aircraft scheduling, rental car scheduling and ride sharing. For example, Raviv et al. [36], present algorithms for the efficient repositioning of bikes in order to maximize customer satisfaction in a bike sharing system. Agatz et al. [1] summarize a number of optimization techniques for the problem of ride sharing, while Bistaffa et al. [7] apply coalition formation techniques in order to calculate stable (from a game-theoretic point of view) payments for a ride sharing setting. Moreover, Budai et al. [9] present an optimal algorithm for the problem of rolling stock balancing, while Bayen et al. [5] use MIP in order to optimally solve an aircraft scheduling problem. Between these works and ours there are some general similarities, such as the fact that optimization techniques as well as greedy approaches are used, but the nature of our problem, and in particular the need for charging or battery swapping between task execution, makes it quite different from them.
      </paragraph>
      <paragraph>
       In addition, similarities can also be found with problems such as the capacitated vehicle routing problem [14] (i.e., special case of the Vehicle Routing Problem [15], where each vehicle has a limited carrying capacity), the project scheduling problem [51], and the machine scheduling problem [28]. Regarding the capacitated vehicle routing problem, our case is similar to the extent that each EV has a limited capacity, but here, the EVs must not necessarily serve all the customers, each task must be executed at a specific point in time and the EVs have a limited range leading to charging or battery swapping being necessary between tasks. As far as the project scheduling problem is concerned, for an EV to execute a task, it must be in the right location, the right time and it must have enough range in the battery. These could be considered the skills of the EV (i.e., in the project scheduling problem there are skills). However, in contrast to the project scheduling problem, here exactly one EV must execute one task and the starting time as well as the duration of the task are fixed and they do not depend on the EV that will execute it. Finally, regarding the machine scheduling problem, our problem has a similar structure as, for example, all EVs are assumed to be identical, each of them executing one task at a time and each task is executed by one EV. The main difference, is that the execution of each task must start at a specific time point, and that after the execution of a task, an EV may not be available to execute another task before it charges or swaps the battery. Overall, the need for battery charging or swapping as well as the strict order of task execution differentiate our problem compared to the three aforementioned ones, and make it harder to find the optimal solution.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       MoD with conventional vehicles
      </section-title>
      <paragraph>
       To date, a number of works have dealt with problems related to the management of vehicles in MoD schemes. For example, Pavone et al. [33] study a setting similar to ours where a finite number of customers, vehicles as well as pick-up and drop-off stations exist. Due to the fact that the system can, in some cases, become unbalanced (i.e., high number of vehicles at some stations and low at others), the authors apply robotic rebalancing techniques. In more detail, they assume that empty robotic vehicles can be autonomously driven across stations in order to match the high demand. The authors apply mathematical programming-based techniques to minimize the number of necessary rebalancing trips. In addition, Smith et al. [45] study the same problem but, instead of robotic vehicles, the authors assume that rebalancing drivers exist. In doing so, they found, through empirical studies, that on some occasions these rebalancing drivers themselves become unbalanced. In order to solve this problem, they assume that customers can transport rebalancing drivers across locations and they use mathematical programming to optimally route them across the stations. In a slightly different vein, where robotic autonomous driving vehicles exist, Zhang et al. [46] model a MoD system as a closed Jackson network [44] with passenger loss. They show that an optimal algorithm which minimizes the number of vehicles needing rebalancing while achieving good vehicle availability throughout the network can be found by solving a linear program. The authors evaluate and verify the effectiveness of their approach in a realistic setting and they also discuss the environmental benefits of such approaches, as they lead to a reduced need for vehicles. In contrast to all three papers, here we do not use a-posteriori rebalancing techniques. Instead, the decision making procedure for the selection of trips to be executed also takes into account the proper distribution of the EVs across the locations. In doing so, we have taken into consideration insights from [6], where the authors show that leaving tasks unexecuted at a certain time point, can lead to higher task execution in the future.
      </paragraph>
      <paragraph>
       Looking at the vehicle sharing problem from a different perspective, Carpenter et al. [12] focus on the problem of sizing vehicle pools (i.e., a number of vehicles at a single location) for a finite set of customers. The authors aim to minimize the size of these pools, while still achieving high customer satisfaction. They propose three analytical techniques to size a vehicle pool for a finite population of customers, according to the pools' busy period demand. Moreover, they propose an additional heuristic sizing method, which requires no prior data about pool demand. In the same vein, George et al. [22] address the problem of determining the optimal fleet size for a vehicle sharing company and derive analytical results for its relationship to vehicle availability at each station in the company's network of locations. Initially, they formulate a closed queuing network model of the system and later they develop a profit-maximizing optimization problem for determining the optimal fleet size. Similarly, Waserhole et al. [55] formulate the setting as a closed queuing network model of the system with infinite buffer capacity and Markovian demands. However, in this case the authors use pricing techniques to incentivise customers not to choose trips that would unbalance the system. In our case, we do not study the optimal number of vehicles at the stations, but we have considered the case where the initial location of a fixed number of vehicles is optimized in order to maximize customer satisfaction (see Section 7.2).
      </paragraph>
      <paragraph>
       In all works presented so far, internal combustion engine-based vehicles are assumed, and hence they do not account for the limited range of EVs. Thus, while balancing the load (i.e., number of pending requests across the network) across the network (i.e., by choosing which trips to execute) serving at the same time the maximum number of users, the amount of time spent charging the vehicles is not taken into account.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Techniques for the management of EVs in MoD schemes
      </section-title>
      <paragraph>
       In recent years, there has been a significant interest within the research community in addressing the challenges involved in deploying EVs. In this vein, a significant number of AI-based approaches to solve EV-related problems have been proposed. According to [37], the majority of the existing works consider three main problem categories: 1) Energy efficient EV routing and range maximization, where algorithms and mechanisms have been developed to route EVs in order to minimize energy loss and maximize energy harvested{sup:5} during a trip (e.g., [41], [47] and [48]). 2) Congestion management, where algorithms have been designed to manage and control the charging of EVs, so as to minimize queues at charging points and the discomfort to the drivers (e.g., [34], [16] and [49]). 3) Integration of EVs into the Smart Grid, where a number of mechanisms have been developed to schedule and control the charging of EVs (Grid to Vehicle – G2V) so that peaks and possible overloads of the electricity network can be avoided, while minimizing charging cost. Other mechanisms have also been developed to utilize the storage capacity of the EVs (Vehicle to Grid – V2G) in order to balance the electricity demand, or to ease the integration of intermittent renewable energy sources to the grid (e.g., [54], [53], [50], [29], [39] and [40]).
      </paragraph>
      <paragraph>
       Although AI techniques have been applied to EV-related problems for privately owned vehicles, limited work have considered the management of EV activities in an MoD scheme. For example, Cepolina and Farina [13] study the use of single-sitter compact-sized EVs in a MoD scheme operating in a pedestrian zone. The vehicles are shared throughout the day by different users and similarly to the majority of the works presented so far, one way trips are assumed. However, here the authors also assume open ended reservation to exist (i.e., the drop-off time is not fixed), thus adding one more dimension to the problem. Given this, they propose a methodology to optimize the fleet size and its distribution among the stations so as to maximize the number of serviced customers while minimizing cost using a random search algorithm. Finally, Doppers and Iwanowski [18] aim to map EVs to customers based on a set of criteria such as the priority of the mobility needs, the state of battery of each EV and the charging time. In so doing, they model the problem of assigning EVs to tasks in a MoD scheme with the well known quadratic assignment problem [27] and they solve the problem using an ant-colony optimization algorithm. In our case, the only criterion of selecting which trips to execute is either the maximization of the total number of serviced customers, or the maximization of EV utilization. However, in contrast to these works, we study settings where different EV charging approaches are used considering both traditional charging and battery swapping. Next, we formally define the problem.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Problem definition
     </section-title>
     <paragraph>
      We study a MoD setting where customers announce their intentions to drive between pairs of locations at a particular time, a day ahead. After all intentions have been collected by the MoD company,{sup:6} it applies a scheduling algorithm to assign EVs to tasks (i.e., trips across a set of locations). In choosing the tasks it will execute, the MoD company aims to maximize either the number of customers that will be serviced, or the utilization of the EVs. We assume that EVs have a limited driving range which requires them to have their battery either swapped [48], or charged at the stations that are part of the MoD scheme. In a battery swap station the battery is not recharged but instead it is replaced by a fully charged one. Battery swap is an efficient alternative to battery recharging as it significantly reduces the idle time of EVs. Battery swapping with privately owned vehicles raises the problem of battery ownership, as once an EV unloads its battery it may never get the same battery back again. However, in cases of shared EVs, such as the one we study here this is not an issue as a single MoD company exists and all batteries belong to it. Moreover, MoD schemes overcome the high cost and the implementation complexity of battery swapping as they take advantage of economies of scale by using a specific battery type for all EVs (we assume all EVs are of the same model). Thus, the process of battery swapping becomes easier and less expensive.
     </paragraph>
     <paragraph>
      We denote by {a mathematical formula}j∈A a set of EVs and by {a mathematical formula}k∈L a set of locations which are pick-up and drop-off stations, where each {a mathematical formula}k∈L has a maximum capacity {a mathematical formula}ck∈N. We consider a set of discrete time points {a mathematical formula}T⊂N, {a mathematical formula}t∈T, where time is global for the system and the same for all EVs. Moreover, we have a set of tasks {a mathematical formula}i∈Δ where each task is denoted by a tuple {a mathematical formula}〈kistart,kiend,tistart,τi,bi〉 where {a mathematical formula}kistart and {a mathematical formula}kiend are the start and end locations of the task, {a mathematical formula}tistart is the starting time of the task, {a mathematical formula}τi is its travel time (each task has also an end time {a mathematical formula}tiend=tistart+τi), and {a mathematical formula}bi is the energy cost of the task. We also denote all tasks starting from location k at time point t as {a mathematical formula}Δst(t,k)={i∈Δ:tistart=t,kistart=k} and all tasks ending at location k and time point t as {a mathematical formula}Δend(t,k)={i∈Δ:tiend=t,kiend=k}. Note here, that one-way rental is assumed, and therefore, start and end locations of a task are different.{sup:7} One-way rental introduces significant flexibility for users, but management complexities (e.g., complex decision making in choosing which customers to service, and high importance of the initial location of EVs) [4].
     </paragraph>
     <paragraph>
      Each EV j has a current location at time point t, denoted as {a mathematical formula}kj,t, and this location changes only when the EV executes a task (i.e., an EV cannot change its location without executing a task). Here, we assume that at time point {a mathematical formula}t=0 all EVs are at their initial locations {a mathematical formula}kj,t=0initial∈L (the initial location can either be fixed, or optimized at run time), and that their operation starts at time point {a mathematical formula}t≥1. Moreover, each j has a current battery level {a mathematical formula}bt,j∈N, a maximum range {a mathematical formula}τjmax, a fixed consumption rate {a mathematical formula}conj (unit of energy/time point) and therefore, a remaining driving range in terms of time {a mathematical formula}τt(j)=[bt,j/conj]∈N, as well as a fixed charging rate {a mathematical formula}chj. For a task i to be accomplished, at least one EV j must be at location {a mathematical formula}kistart at time point {a mathematical formula}tistart. At any t, each EV should either be parked at exactly one location, or travelling between exactly one pair of locations. Henceforth, index j stands for EVs, k for locations, t for time points and i for tasks (see also Table 1). Where required to simplify the explanation, we slightly abuse notation to denote that some quantities are dependent on others (they are functions – e.g., {a mathematical formula}τt(j)), whereas others are independent (these can be identified solely by indices – e.g., j).
     </paragraph>
     <paragraph>
      In this paper we mainly study this offline setting and then we propose a preliminary solution to an online setting based on our insights from the offline one. In the following section we present a formulation of the problem as a max-flow one.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Formulation as a maximum flow problem
     </section-title>
     <paragraph>
      In this section, we formulate the EV to task allocation problem as a max-flow problem [24] and we solve it using MIP. By using this approach we aim to remove the tasks that are impossible to be executed, thus reducing the execution time and increasing the solution quality of the scheduling algorithms presented in the following section. All pick up and drop off locations are considered to be the nodes of the network and the execution of tasks is the flow in and out of each node. The initial location of each EV is a source node and the end location of each EV is a sink node. In our case we have many sources and many sinks. Thus, it is a multi-source multi-sink maximum flow problem and can be transformed into a maximum flow problem as follows: Given a network N = (V, E) with a set of sources S = {a mathematical formula}s1,...,sn and a set of sinks T = {a mathematical formula}t1,...,tm instead of a single source and sink node, we are to find the maximum flow across N. We transform the multi-source multi-sink problem into a maximum flow problem by adding a consolidated source connecting to each vertex in S and a consolidated sink connected by each vertex in T (also known as supersource and supersink) with infinite capacity on each edge.
     </paragraph>
     <paragraph>
      In this formulation, we have one decision variable, namely {a mathematical formula}λi∈{0,1} denoting whether a task i is accomplished or not and the objective is the maximization of executed tasks (Equation (1)). Alternatively, the utilization of the EVs (i.e., total travelling time) can also be maximized (Equation (2)). This is achieved under the constraint that for each location, the inflow is always greater or equal to the outflow (Equation (3)). Given that an EV changes location only after executing a task, for each location k and time point t, the number of tasks that started from k any time point prior to t, must be less or equal to the tasks that ended at k any time point prior to t, plus the EVs whose initial location was equal to k (i.e., no task can be executed without the existence of at least one EV).{a mathematical formula}{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The outcome of this procedure is the set of tasks that can be executed assuming that battery swap is being used and that (a) all EVs start with the same battery level and (b) a fully charged battery is capable of executing the longest trip. In fact, if (a) and (b) hold, the max flow algorithm returns the optimal solution in terms of the number of completed tasks. This can easily be verified given the following reasons: every task i has a source location {a mathematical formula}kistart and a destination {a mathematical formula}kiend. Moreover, it has a fixed time of departure {a mathematical formula}tidep and a fixed duration {a mathematical formula}τi. In the max flow algorithm, the duration of a task also contains the time for the battery swap. Given that all EVs carry the same battery which is fully charged at the beginning of each task, any EV can execute any task. Thus, a task can be executed if and only if at least one EV exists at {a mathematical formula}kistart the time point {a mathematical formula}tidep. Equation (3) assures that no task will be considered executed if not enough EVs exist at the source location of the task the time of departure. Thus, given the objective function (Equation (1) or Equation (2)), the solver will select to execute the tasks that lead to the maximization of the total number of completed tasks or the EV utilization respectively. In case where either (a), or (b), or both do not hold, then the max flow algorithm will provide the theoretical upper limit in terms of completed tasks. This is true due to the fact that this algorithm assumes all EVs to have the same capabilities. Thus, if an EV is assigned to a task that it cannot actually execute, this task and possibly some future ones will not be executed. The same holds for the case of battery charging, as the charging takes longer time compared to battery swapping. We will refer to this algorithm as MaxFlow.
     </paragraph>
     <paragraph>
      In the case where the initial location of the EVs is not given as input, but it should be optimized, the above formulation is updated as follows: One more decision variable, namely {a mathematical formula}initLocj,k∈{0,1}, denoting whether location k is the initial location for EV j is added. Moreover, Equation (4) which constrains each EV to have exactly one initial location is added to the formulation, and Equation (3) is updated by using the pre-defined decision variable and becomes Equation (5). We will refer to this algorithm as MaxFlowInit{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The max flow algorithm calculates the optimal set of tasks to be executed. However, the task execution schedule for each EV is not calculated. Thus, this algorithm is used as a pre-processing step in order to determine the tasks to be executed. Then, any of the scheduling algorithms described in the following section has to be used in order to calculate the task execution schedule for each EV. As can be seen in Sections 7.1 and 7.2 it improves the scalability of the optimal scheduling algorithm and the solution quality of the greedy one.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Offline scheduling algorithms for MoD schemes
     </section-title>
     <paragraph>
      In this section, we tackle the problem defined in Sections 3 and 4 in the particular context where the demand for trips at each station is known in advance. We term this problem the offline problem, as the algorithm is run to pre-determine all trips for the day ahead. In Section 5.1 we present the MIP formulation of the problem with battery swap and in Section 5.2 the one with battery charge. Then, in Section 5.3 the incremental MIP scheduling algorithm and in Section 5.4 the greedy algorithm with battery swap and in Section 5.5 the one with battery charge. Finally, in Section 5.7 we present the battery swap optimization algorithm.
     </paragraph>
     <section label="5.1">
      <section-title>
       Optimal scheduling with battery swap
      </section-title>
      <paragraph>
       The aim of the MoD scheme is to maximize either the number of tasks that are completed (a.k.a. customer satisfaction) (Equation (6)) or the total number of time points that EVs are travelling (a.k.a. EV utilization) (Equation (7)) (i.e., the objective functions can be used alternately). To achieve this, we present an optimal solution based on Mixed Integer Programming (MIP){sup:8} (solved using IBM ILOG CPLEX 12.6.2), where we use battery swapping to cope with the EVs' limited range. MIP techniques have been particularly useful to solve such large combinatorial problems (e.g., combinatorial auctions [42], [3], travelling salesman problem [19]). Also, such a solution can be used as a benchmark for more customized algorithms (as we do in this paper in Section 5.6 and Section 6). We will refer to this algorithm as Off-Opt-Swap. Note that in case the max flow algorithm returns the optimal set of tasks to be executed, this algorithm simply calculates the EV to task execution schedule. However, if the max flow returns the upper limit in terms of executed tasks, this algorithm also decides which of these tasks can actually be executed. In more detail, we define three binary decision variables: 1) {a mathematical formula}λi∈{0,1} denoting whether a task i is accomplished or not, 2) {a mathematical formula}ϵj,i,t∈{0,1} denoting whether EV j is executing task i at time t or not, and 3) {a mathematical formula}prkj,t,k∈{0,1} denoting whether j is parked at time point t at location k or not. Moreover, a set of constraints is used:
      </paragraph>
      <paragraph>
       Objective functions:{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Subject to:
      </paragraph>
      <list>
       <list-item label="•">
        Completion constraints:
       </list-item>
      </list>
      <paragraph>
       {a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <list>
       <list-item label="•">
        Temporal, spatial, and routing constraints:
       </list-item>
      </list>
      <paragraph>
       {a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <list>
       <list-item label="•">
        Cut constraints:
       </list-item>
      </list>
      <paragraph>
       {a mathematical formula}
      </paragraph>
      <paragraph>
       The completion constraints ensure the proper execution of tasks. Thus, for each executed task, the time travelled must be equal to the duration of the trip concerned{sup:9} (Equation (8)), while, at the same time no travelling must take place when a task is not executed (Equation (9)). Moreover, each task is executed by only one EV at a time (Equation (10) together with Equation (13)). Now, for an EV to execute a task, its full range, calculated based on the battery level at the starting time of the task, must not be violated (Equation (11)) (i.e., in case trip requests are not within the range of a single battery load, the solver will not schedule them). We assume all EVs to have a fixed average consumption, and that each time an EV reaches a parking station a fully charged battery is swapped into it, while the number of swaps is minimized a posteriori (Section 5.7 presents a battery swap minimization algorithm).
      </paragraph>
      <paragraph>
       The temporal, spatial and routing constraints ensure the proper placement of the EVs over time. Equation (12) requires that for each time point at which an EV is executing a task, this EV cannot be parked at any location and also assures (together with Equation (10)) that at each time point, each EV executes at most one task. Moreover, Equation (13) ensures that no EV changes location without executing a task (the sum of all changes of EVs' locations as denoted in prk decision variable, must be double the total number of tasks that are executed). Note that, this constraint is linearized at run time by CPLEX.{sup:10}
      </paragraph>
      <paragraph>
       Now, whenever a task is to be executed, the EV that will execute this task must be at the task's starting location one time point before the task begins (Equation (14)), and similarly, whenever a task has been executed, the EV that has executed this task must be at the task's end location the time point the task ends (Equation (15)). Moreover, at every time point, the maximum capacity of each location must not be violated (Equation (16)). Finally, at time point {a mathematical formula}t=0, all EVs must be at their initial locations (Equation (17)), which also means that no tasks are executed at {a mathematical formula}t=0. Note that, in case Equation (17) is removed, the solver will decide on the optimal initial location of each EV given a specific set of tasks waiting to be executed.
      </paragraph>
      <paragraph>
       Equation (19) ensures that for every location, the total number of EVs at charging stations changes only when EVs depart or arrive to execute a task, or after executing tasks. Despite the fact that this constraint is covered by Equation (13), when added to the formulation, it significantly speeds up the execution time. For example, for a setting with 8 locations, 15 EVs, 60 time points and 70 tasks, constraint 13 reduces the average execution time from 450 s to less than 200 s. In fact, it is known that the introduction of additional cut constraints into a MIP problem may cut off infeasible solutions at an early stage of the branch and bound searching process and thus reduce the time to solve the problem [20].
      </paragraph>
      <paragraph>
       By using battery swapping, an EV can have full range in just a few minutes. However, such battery swap schemes impose high costs and implementation complexity. Thus, in the next section, a variation of the optimal solution where, instead of battery swap, a more traditional battery charge scheme is used is presented.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Optimal scheduling with battery charging
      </section-title>
      <paragraph>
       Here, the problem of scheduling EVs in a MoD scheme is formulated using fast battery charging (we will refer to this algorithm as Off-Opt-Charge). In addition to the decision variables and the constraints presented in the previous section, we define one continuous variable namely {a mathematical formula}bchj,t∈[0,ch(j)] which denotes whether an EV j is charging at time point t and at which charging rate (i.e., the charging rate can be any between 0 and the maximum charging rate – {a mathematical formula}ch(j)),{sup:11} as well as 2 completion constraints.{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Equation (20) ensures that each EV j can charge only while being parked. When an EV is parked, it can charge with a charging rate up to its maximum one. However, when it is driving and {a mathematical formula}prkj,k,t=0 it cannot charge. The charging takes place at any time point chosen by the solver as long as the available range will not compromise the task execution ability. At the same time, Equation (21) ensures that the battery level of an EV j never exceeds 100% and never goes below 0% (i.e., {a mathematical formula}bj,t=0 is the initial battery level, {a mathematical formula}∑t′=0tbchj,t′ is the amount of battery charged and {a mathematical formula}∑i∈Δ∑t″=tistarttϵi,j,t″×con(j) is amount of energy consumed). Thus, no EV j will execute a task i for which it does not have enough range, nor will it charge more than its battery capacity. Note that Equation (21) replaces Equation (11).
      </paragraph>
      <paragraph>
       The solutions presented so far calculate the optimal schedule for the EVs. However, as we show later in Sections 7.1 and 7.7, they have quadratic time complexity and are mainly usable for small and medium sized problems (less than 300 tasks and 20 EVs). For this reason, algorithms that can calculate solutions close to the optimal, but with a low computational complexity, are essential. In the next section, an algorithm which incrementally calls the MIP for each EV is presented.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Incremental MIP scheduling algorithm
      </section-title>
      <paragraph>
       MIP problems are known to be NP-Hard in the worst case [25]. A widely employed strategy to overcome the computational difficulty for the solution of large MIP models is based on the idea of decomposition[20]. The decomposition approach divides a large and complex problem, which may be computationally expensive or even intractable when formulated and solved directly as a single MIP model, to smaller sub-problems, which can be solved much more efficiently. Usually, decomposition approaches only lead to suboptimal solutions. However, they substantially reduce the problem complexity and the solution time, which makes it possible to apply MIP based techniques to large real-world problems.
      </paragraph>
      <paragraph>
       Based on the idea of decomposition, we present an offline scheduling algorithm, which incrementally calls and solves the MIP formulation of the problem. Note that some insights were also taken from [8] and in particular from the discussion on the planning of completely independent agents. The intuition behind this algorithm is the following: Given that the dimension of the problem that affects the execution time the most is the number of EVs (see Section 7.1), we solve the MIP problem for each EV separately. Thus, the MIP formulation is solved sequentially (see Algorithm 1), for each EV within the list of available EVs. In more detail, after the set containing all completed tasks is initialized to the empty one (line 1), the optimal algorithm is called for each EV{sup:12} (lines 2–9): Every time the schedule for one EV is calculated (line 6), the sets for the completed tasks and the remaining tasks are updated accordingly (lines 7, 8). At the end of this procedure, the set that contains the completed tasks is returned (line 10). Note that this algorithm works both with battery swap and battery charge. We will refer to the one with battery swap as Off-Incr-Swap and to the one with battery charge as Off-Incr-Charge.
      </paragraph>
      <paragraph>
       The incremental MIP algorithm achieves near optimal solutions with relatively small execution time (see Section 7.1). However, for problems with more than a few thousands EVs and tasks, the execution time increases.{sup:13} Given that greedy algorithms based on heuristic search have proven to be effective in similar highly combinatorial problems [35], in the next section, such greedy algorithms are presented.
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Greedy scheduling with battery swap
      </section-title>
      <paragraph>
       Given that EVs change locations only when being driven by customers, the tasks that an EV will be able to execute in the future are directly related to the ones it has already executed in the past (i.e., the end location of one task will be the start location for the next one). In large settings, normally not all tasks can be executed. Thus the selection of the ones to execute is of great importance, since each decision can affect future task execution. In the case of our MIP formulation, the solver finds the optimal schedule for EVs that maximises the number of tasks executed, or the EV utilization. However, the scalability of that algorithm is average. For this reason, here we present a greedy algorithm which applies a one-step look ahead heuristic search mechanism. This algorithm achieves, as we show later, near optimal performance and scales to thousands of EVs and tasks. We will refer to this algorithm as Off-Greedy-Swap.
      </paragraph>
      <paragraph>
       For each time point t and for each station k, we consider the number of the available EVs, as well as the number of the remaining tasks to be executed. Given that all tasks to be executed are known in advance, if the number of available EVs is greater than, or equal to the number of tasks remaining to be executed, we can safely assume that enough EVs are available to execute all tasks (note that more EVs may arrive later after executing tasks). In this case, each task is executed according to its starting time.
      </paragraph>
      <paragraph>
       In the case where the number of EVs is lower than the number of the remaining tasks, we need to carefully choose which of the tasks need to be executed in the current time point, so that more tasks can be executed in the future. To this end, we employ a one-step look ahead heuristic criterion. The intuition behind this heuristic is to give priority to the tasks that lead to destinations where either 1) high number of tasks remain to be executed, or 2) many tasks are about to be executed soon, or 3) both. In this way, the EVs do not remain idle for long time (i.e., it combines customer satisfaction and EV utilization).
      </paragraph>
      <paragraph>
       At each time point, we select all tasks i that should start being executed at this time point. Based on the initial location k of a task i, we calculate the score in Equation (22). In calculating the sum, we take into consideration the number of EVs that already exist at the destination. However, we remove the ones that will depart before the arrival of the EV at k. Thus, we come up with a score for each location (i.e., {a mathematical formula}sck={k,scorek}∈R) and we select to execute the tasks that lead to locations with the highest score. The sum guarantees that both locations with tasks which are about to be executed soon and locations with high numbers of remaining tasks will get a high score. Example (see Fig. 1): In the destination of a given task, there are five tasks remaining to be executed with departure times: 5, 7, 8, 9, 12. If the task is executed, the EV will arrive at the destination at time point 7. Thus, it may also be able to execute one of tasks 8, 9, 12. Moreover, 3 EVs already exist at the destination. If these EVs take care of 5,7, 8, then the new EV could be able to execute tasks 9 and 12. For this reason the score is calculated only using 9 and 12.{a mathematical formula}
      </paragraph>
      <paragraph>
       The greedy scheduling formulation that is presented here, consists 1) of a pre-processing phase and 2) of the main scheduling algorithm (Algorithm 4) which applies a task execution algorithm.
      </paragraph>
      <section label="5.4.1">
       <section-title>
        Pre-processing
       </section-title>
       <paragraph>
        During the pre-processing phase, the initialization of the sets and the variables takes place (see Algorithm 2). In more detail, sets {a mathematical formula}Δk⊆Δ and {a mathematical formula}CTk,t⊆Δk are created and initialized to the empty set (line 2). Then, all tasks starting at location {a mathematical formula}k∈L are assigned to set {a mathematical formula}Δk (line 5), and for each location k and time point t, {a mathematical formula}CTk,t (line 9) is populated with all tasks to be executed at t. Moreover, the set {a mathematical formula}Rt,kistart (line 13) containing the number of tasks remaining to be executed from each location and each time point t, is created and initialized. Finally, variable {a mathematical formula}prkj,t,k (line 16) which holds the initial location of each EV, and variable {a mathematical formula}evst,k (line 19) which counts the number of EVs parked at each location, are initialized. In the next section, the steps for the assignment of an EV to a task are presented.
       </paragraph>
      </section>
      <section label="5.4.2">
       <section-title>
        Task execution
       </section-title>
       <paragraph>
        Each time an EV j is assigned to a task i, Algorithm 3 is called and a number of actions take place: Initially, EV j is set to be working on task i, by changing the value of variable {a mathematical formula}ϵj,i,t from 0 to 1 for the duration of the trip (line 1) (variables {a mathematical formula}ϵj,i,t, {a mathematical formula}prkj,t,l and {a mathematical formula}λi are also used here). Then, the parked location k of j is updated based on the end location {a mathematical formula}kiend of the task and the arrival time {a mathematical formula}tcurrent+τi (lines 3, 4). Finally, the total number of completed tasks is increased by one (line 6), and the total number of EVs parked at the start and end location of the trip are updated accordingly (lines 8, 9). Note that following the same modelling of the problem as in the MIP formulation (Equation (15)), once an EV arrives at a destination, it stays there for at least one time point which is used for the necessary battery swap.
       </paragraph>
      </section>
      <section label="5.4.3">
       <section-title>
        The off-greedy-swap algorithm
       </section-title>
       <paragraph>
        Here, we elaborate on the key steps of the greedy algorithm (Algorithm 4). For all {a mathematical formula}i∈CTk,t awaiting to be executed at the current time point, the following steps are executed repetitively for each task:
       </paragraph>
       <list>
        <list-item label="1.">
         If the number of available EVs with enough range is greater than the number of tasks remaining to be executed, starting from this location, then all tasks are set to be executed sequentially (lines 3–8). For each task, if its execution does not lead to a violation of the maximum capacity of the destination location (waiting queues do not exist), then, once there exists an EV that is parked at the current location, it is assigned to the task and the latter is executed by calling Algorithm 3. If no such EV exists, the task is not completed.
        </list-item>
        <list-item label="2.">
         If the number of the EVs parked at the current location and have enough range is less than the tasks remaining to be executed (lines 9–21), the scores for the end location of each task are calculated. Then, {a mathematical formula}sck in descending order based on {a mathematical formula}scorek (lines 10–14). If the execution of the task does not violate the maximum capacity of the destination location, the tasks with the higher scores are executed based on EV availability. Once there exists an EV that is parked at the current location, it is assigned to the task and the latter is executed by calling Algorithm 3. Otherwise, the task is not completed.
        </list-item>
       </list>
       <paragraph>
        The execution of Algorithm 4 generates a schedule for all EVs as well as for the total number of completed tasks. In case where after the max flow algorithm (Section 4), the Greedy algorithm gets as input a set of tasks that all of them can be executed, the problem of scheduling EVs to tasks becomes a simple resource allocation problem. In this case, the heuristic function is not used as enough EVs to execute all tasks always exist (i.e., lines 9–21 of Algorithm 4 are never executed). Thus, at every time point EVs are simply assigned to the tasks.
       </paragraph>
       <paragraph>
        Next, the analysis of the average case time complexity of the greedy algorithm is presented.
       </paragraph>
      </section>
      <section label="5.4.4">
       <section-title>
        Complexity analysis – battery swap
       </section-title>
       <paragraph>
        While the algorithm is greedy, some steps such as the sorting of {a mathematical formula}scorek, can be computationally costly. Hence, in what follows, we elaborate on the complexity of key steps of this algorithm.
       </paragraph>
       <paragraph label="Theorem 1">
        Complexity class of Algorithm 4The average case complexity ofAlgorithm 4is{a mathematical formula}|Δ|×|L|×|A|+|T|×|L|2×log|L|+|L|2×|T|.
       </paragraph>
       <paragraph label="Proof">
        For lines 1 and 2 of Algorithm 4, the number of iterations is fixed to {a mathematical formula}|T|×|L|. Now, for each t and {a mathematical formula}lk the iterations for line 4 depend on {a mathematical formula}|CTk,t|. However, for all T and L they are always equal to {a mathematical formula}|Δ|. The calculation of the scores (lines 10–13), depend on {a mathematical formula}|L|×|CTk,t| (line 12), and the sorting of {a mathematical formula}scorek (line 14) on {a mathematical formula}|L|×log|L|+|L| (i.e., {a mathematical formula}|L|×log|L| for the sorting of {a mathematical formula}scorek and {a mathematical formula}|L| of the update of the order of locations). The selection of the tasks and the selection of the EVs to execute the selected tasks (lines 15–25) depend on {a mathematical formula}|L|×CTk,t×|A|. Thus, the computational cost is given by the following equation:{a mathematical formula} which is equal to:{a mathematical formula}In the average case, where tasks and EVs are equally distributed across locations and time points, {a mathematical formula}CTk,t=|Δ||T|×|L| and Equation (29) becomes:{a mathematical formula} which is equal to:{a mathematical formula} Finally, as {a mathematical formula}|A|&gt;&gt;1 and {a mathematical formula}|L|&gt;&gt;1 Equation (26) becomes:{a mathematical formula} Therefore, the complexity increases proportionally (linearly) with the number of tasks and EVs, and quadratically with the number of locations times {a mathematical formula}log|L| times the time points and quadratically with the number of location times the number of time points. Therefore, the average case complexity of Algorithm 4 is {a mathematical formula}O(|Δ|×|L|×|A|+|T|×|L|2×log|L||L|2×|T|). These results are also verified experimentally (see Section 7.1).
       </paragraph>
       <paragraph>
        In the next section, a variation of the greedy scheduling algorithm, where battery charge, instead of battery swap is used, is presented.
       </paragraph>
      </section>
     </section>
     <section label="5.5">
      <section-title>
       Greedy scheduling with battery charging
      </section-title>
      <paragraph>
       In this section, we present Algorithm 5 which uses battery charge instead of battery swap. Algorithm 5 works similarly to Algorithm 4, but there is one main difference: instead of swapping batteries after each task is completed, the battery level is monitored and updated for each EV based on its status (i.e., parked or travelling) (lines 27–36). In other words, as an EV travels, the battery discharges, while when an EV is parked the battery level may increase if charging takes place. For this reason, variable {a mathematical formula}bj,t∈{0,100} is used in order to capture the level of battery charge at each EV and each time point. In case energy is needed and when being parked at any location, energy is charged into the EV (lines 29–31), whereas when travelling, the battery is discharged (lines 31–33). In order to decide on the charging schedule of an EV, we use one of the algorithms presented in [39]. According to this algorithm, and assuming that an EV needs n units of energy, the charging takes place in the first n time points after the arrival of the EV to the station, during which enough available chargers exist and enough energy can be provided from the grid. In contrast to the Off-Opt-Charge, here the charging rate is fixed to the maximum one, however this does not affect the task execution ability of the algorithm (i.e., the greedy is always using the maximum rate, while the optimal is using it only when is needed. Given that it is optimal and has full knowledge of future demand, if there is no need to use maximum charging rate, it does not do so). The problem of efficient load balancing across the electricity network is not studied in this paper, and therefore the use of more advanced charging scheduling algorithms will be considered in future work. Also, in contrast to Algorithm 4, in order to decide whether an EV can execute a task or not, its current range and not its maximum range (as was happening in the case of battery swap where a fully charged battery was swapped into the EV) is compared with the energy demand of the upcoming task (lines 5 and 20). We will refer to this algorithm as Off-Greedy-Charge.
      </paragraph>
      <section label="5.5.1">
       <section-title>
        Complexity analysis – battery charge
       </section-title>
       <paragraph>
        Here the complexity class of Algorithm 5 is calculated.
       </paragraph>
       <paragraph label="Theorem 2">
        Complexity class of Algorithm 5The average case complexity ofAlgorithm 5is{a mathematical formula}O(|Δ|×|L|×|A|+|T|×|L|×(|L|×log|L|+|L|+|A|)).
       </paragraph>
       <paragraph label="Proof">
        Following a similar thinking as in the previous case, the computational cost is:{a mathematical formula} which is equal to:{a mathematical formula}In the average case, where tasks are equally distributed across locations and time points, {a mathematical formula}CTk,t=|Δ||T|×|L| and Equation (28) becomes:{a mathematical formula} and as {a mathematical formula}|A|&gt;&gt;1 and {a mathematical formula}|L|&gt;&gt;1 it is equal to:{a mathematical formula}Therefore, the average case complexity of Algorithm 5 is {a mathematical formula}O(|Δ|×|L|×|A|+|T|×|L|×(|L|×log|L|+|A|)). Note, that the average case complexity of Algorithm 5 is higher compared to the one of Algorithm 4. However as we show in Section 7.1, the practical difference is very small.
       </paragraph>
       <paragraph>
        In the next section, a local search technique to further improve the solution quality of the non-optimal algorithms is presented.
       </paragraph>
      </section>
     </section>
     <section label="5.6">
      <section-title>
       Local search algorithm
      </section-title>
      <paragraph>
       Local search can be used on problems that can be formulated as finding an optimal solution among a number of candidate solutions. Local search algorithms move from solution to solution in the space of candidate solutions (the search space) by applying local changes, until a solution deemed optimal is found or a stopping condition is met. Local search is a well established technique to improve the solution provided by a non-optimal algorithm. In our case, we need a local search algorithm in order to improve an initial solution that was calculated very fast by the greedy algorithm. Thus, we developed a tabu search-based algorithm. Tabu search is a meta-heuristic technique which includes as a subroutine a local search procedure which is appropriate for the problem being solved. This subroutine runs iteratively and finds new solutions in the neighbourhood of a current solution. A key characteristic of tabu search is that it does not require each new trial solution to be better than the current one. In this way the algorithm can escape from local minima [24]. Tabu-search was preferred over alternative local search methods (e.g., simulated annealing) because 1) its representational characteristics better match our problem formulation and 2) it is known to outperform other local search algorithms in terms of solution quality/robustness and computation time [31]. It has also been proved to perform well in problems with similarities to ours, such as the TSP and the QAP problems [23], [32]. In what follows, we present the formulation of our tabu search-based algorithm for the MoD problem:
      </paragraph>
      <list>
       <list-item label="1.">
        Local search procedure: At each iteration, select the neighbouring solution that leads to the maximum number of serviced tasks (or maximum EV utilization).
       </list-item>
       <list-item label="2.">
        Neighbourhood structure: An immediate neighbour of the current trial solution is one that is reached by changing the task assignment of one EV.
       </list-item>
       <list-item label="3.">
        Form of tabu moves: All EVs and their assigned tasks.
       </list-item>
       <list-item label="4.">
        Addition of a tabu move: We iterate over all EVs and we calculate the task-to-EV assignment using any of the Off-Opt-Swap or Off-Opt-Charge to solve the problem. The EV and its assignment that leads to higher number of total serviced tasks is added to the tabu list.
       </list-item>
       <list-item label="5.">
        Maximum size of the tabu list: The number of EVs (i.e., for each EV, at most one tabu move exists – for some EVs it may not contain any move).
       </list-item>
       <list-item label="6.">
        Stopping rule: A number of iterations without any improvement in the current solution.
       </list-item>
      </list>
      <paragraph>
       Algorithm 6 presents the local search procedure for the MoD scheme. This algorithm takes as input the task-to-EV assignment as this is calculated by the Greedy algorithm. Then all tasks that have been assigned to an EV are added to set {a mathematical formula}EVsTasksMapj. All tasks that were not assigned to any EV are added to set TasksUnexecuted (lines 2–12). Then, Off-Opt-Swap or Off-Opt-Charge is called for each EV and for all tasks that were initially assigned to that EV plus the ones that were not assigned to any EV.{sup:14} The completed tasks for each EV, as calculated by the optimal algorithm, are added to {a mathematical formula}currentSolution variable. After all EVs have been examined, the one that leads to higher increase in the number of executed tasks and is not in the tabu list, is selected and the current solution is updated based on the assignment of that EV. Also, this assignment is added to the tabu list. This procedure continues until at least n iterations over all EVs have finished without any improvement in the current solution. In that case we assume that the solution cannot further improve and the algorithm terminates (lines 13–25). In the next section, a battery swap optimization algorithm which applies to all scheduling algorithms using battery swap, is presented.
      </paragraph>
     </section>
     <section label="5.7">
      <section-title>
       Battery swap optimization
      </section-title>
      <paragraph>
       The algorithms that make use of battery swap, calculate the schedule of each EV assuming that after every stop a fully charged battery is swapped into it. However, battery swap at each station may not actually be necessary as the vehicle might have enough energy to execute more tasks. Moreover, frequent battery swapping demands higher volumes of available batteries at the stations, thus increasing the cost for the MoD company [56]. For these reasons, we present an optimal scheduling algorithm which takes as input the EV's travelling schedule {a mathematical formula}taskExecj,t∈{0,1} and minimizes the number of battery swaps a posteriori.
      </paragraph>
      <paragraph>
       We formulate the problem of the battery swap minimization using MIP techniques and we solve it optimally. We denote two decision variables: 1) {a mathematical formula}swapj,t∈{0,1} which is a binary decision variable on whether EV j swaps its battery at time point t. 2) {a mathematical formula}btj,t∈{0,rangej} which is an integer decision variable on the battery level of each EV at each time point. The value of {a mathematical formula}btj,t must always be between 0 and the maximum range of the EV and CPLEX will limit the values within this range. The objective function (Equation (32)) which consists of the sum of all battery swaps for all EVs, is minimized subject to three constraints: No EV can swap its battery when executing a task (Equation (33)), while the initial battery level of each EV must be equal to its full range (i.e., task execution starts with a fully charged battery) (Equation (34)). Moreover, at each time point, the battery level of each EV must be equal to the level the previous time point, plus full range if a battery was swapped into the EV and minus the energy consumed while driving (Equation (35)) (i.e., CPLEX will limit the values of {a mathematical formula}btj,t between 0 and {a mathematical formula}rangej).
      </paragraph>
      <paragraph>
       Objective functions:{a mathematical formula}
      </paragraph>
      <paragraph>
       Subject to:{a mathematical formula}{a mathematical formula}{a mathematical formula}
      </paragraph>
      <paragraph>
       Having discussed a number of offline approaches to solving the EV allocation in MoD schemes, we next turn to the online problem. In particular, we address the problem of coping with unknown future trip requests.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Online scheduling algorithm
     </section-title>
     <paragraph>
      So far, we assumed complete knowledge of future customer demand to exist. However, as this assumption does not always hold in reality, here we present an algorithm which has the ability to effectively cope with the uncertainty in future demand.
     </paragraph>
     <paragraph>
      This algorithm uses concepts related to the Model Predictive Control (MPC) [11] approach. In more detail, assuming that the MoD company has full knowledge of the demand for only a small number of tasks {a mathematical formula}Δfix⊆Δ, the remainder of (usually longer term) future demand is stochastic in nature and, to some degree, can be captured using a probability distribution learnt from historical data – expected set of tasks, {a mathematical formula}Δexp. Note that the start time of all expected tasks is after the execution of the latest task in the fixed set. Given these two sets of tasks, the aim is to calculate a schedule for the execution of the fixed tasks, such that it leads to higher probability of executing more tasks in the future. To achieve this, two steps are followed (see also Algorithm 7):
     </paragraph>
     <list>
      <list-item label="•">
       Step 1: a set of expected tasks is calculated and a plan for the execution of both fixed and expected tasks is calculated (line 3).
      </list-item>
      <list-item label="•">
       Step 2: the execution plan related to the fixed tasks remains unchanged and a number {a mathematical formula}η∈H of sets of expected tasks (i.e., {a mathematical formula}Δexp) are iteratively sampled to calculate the average expected number of executed tasks (lines 4–7).
      </list-item>
     </list>
     <paragraph>
      This procedure (steps 1 and 2) is executed for a number of rounds {a mathematical formula}r∈R. Then, the schedule of the fixed tasks that leads to a higher expected utility (number of tasks expected to be executed) is selected. The fixed tasks that have been scheduled to be executed can definitely be executed, under the assumption that no overbooking from the side of the stations, nor booking cancellations from the side of the customers exists. If a booking is cancelled, then the schedule may not be feasible anymore. However, we do not study this scenario in this paper.{sup:15} Moreover, a longer time period for the fixed tasks usually leads to higher number of executed tasks, but also leads to higher waiting time for future EVs to announce their request. This algorithm works both with battery swap and battery charge. We will refer to the battery swap variation as On-Swap and to the one with battery charging as On-Charge. In the next section, we present a detailed evaluation of all algorithms.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Evaluation
     </section-title>
     <paragraph>
      Here we evaluate our algorithms on a number of settings in order to determine their ability to handle potentially large numbers of tasks, locations and EVs. To this end, we use real locations of pick-up and drop-off points owned by ZipCar{sup:16} in Washington DC, USA which are available as open data,{sup:17} while the distance and duration of all trips{sup:18} were calculated using Google maps (see Fig. 2). Car station locations too close to each other were ignored and 8 stations were selected.{sup:19} Note, that Washington DC is one of the cities with the highest traffic congestion in the USA{sup:20}[43]. MoD can reduce congestion as it reduces the demand for parking spots (such parked cars create some congestion). Therefore, a MoD scheme would fit perfectly in such a setting as it has the potential to reduce the congestion caused by privately owned vehicles. The evaluation of our algorithms is executed in six main parts:
     </paragraph>
     <list>
      <list-item label="•">
       EXP1: The execution time and the scalability of the max flow, the optimal, the incremental MIP, the greedy and the local search algorithms are evaluated.
      </list-item>
      <list-item label="•">
       EXP2: The performance of the algorithms in terms of the average number of completed tasks and the EV utilization is evaluated.
      </list-item>
      <list-item label="•">
       EXP3: The sensitivity of the max flow algorithm is analyzed.
      </list-item>
      <list-item label="•">
       EXP4: The efficiency of the battery swap optimization algorithm is evaluated.
      </list-item>
      <list-item label="•">
       EXP5: The performance of the online algorithm against the optimal offline one is evaluated.
      </list-item>
      <list-item label="•">
       EXP6: The correctness of the optimal and greedy algorithms is verified.
      </list-item>
     </list>
     <paragraph>
      All experiments were executed in the following setting: 1) one time point was selected to be equal to 15 min, and in total 58 time points exist (i.e., equivalent to the execution of the MoD service from 7:00 to 18:00). 2) For the optimal algorithms, the objective function that maximizes task execution (Equation (6)) is used (i.e., maximization of completed tasks), unless otherwise stated, and 3) tasks can be formulated based on one of 56 possible trips (i.e., the trips are the combinations of the 8 locations that form the MoD scheme. However, locations too close to each other were ignored). Trips were categorized into three groups: 1) from suburbs to the city centre, 2) around the city centre, and 3) from the city centre to the suburbs. These groups were selected according to our intuition of the expected flow of traffic within the city over the day. Also, we have divided the day into three sessions: 1) morning, 2) noon, and 3) afternoon. In the morning session the majority of the trips come from group 1 (i.e., 60% of the tasks are from group 1 and 40% from the rest), in the noon session they come from group 2 i.e., 60% of the tasks are from group 2 and 40% from the rest), and in the afternoon session they come from group 3 (i.e., 60% of the tasks are from group 3 and 40% from the rest). Within each session, tasks are selected using a uniform distribution (i.e., tasks selected with equal probability). Start times of tasks within each group were drawn from a uniform distribution (i.e., for morning session start times are between 1–12 ({a mathematical formula}mean=6.5 and {a mathematical formula}σ=3.17), for noon between 12–36 ({a mathematical formula}mean=24 and {a mathematical formula}σ=6.9) and for the afternoon between 36–50 ({a mathematical formula}mean=43 and {a mathematical formula}variance=4.04). Also, {a mathematical formula}conj=10 and {a mathematical formula}chj=25, i.e., for each time point that an EV is working the battery level is reduced by 10 units of energy, and for each time point an EV is charging the battery level is increased by up to 25 units of energy (fast battery charging). The average range of an EV is currently at around 150 km. We assume an average speed of 40 km/h which means that an EV can drive for 3.75 h. In our evaluation setting, one time point is equal to 15 min, and 3.75 h equal to 15 time points. Thus, {a mathematical formula}conj=10% of battery for each time point. A fast charger can fully charge an EV at around one hour. Thus, {a mathematical formula}chj=25% of the battery for each time point. Both {a mathematical formula}conj and {a mathematical formula}chj are configuration parameters and can be selected by the user. Note, that all experiments were executed on a Windows PC with an Intel i7-4790K CPU and 16 GB of RAM running at 2400 MHz.
     </paragraph>
     <section label="7.1">
      <section-title>
       EXP1: execution time and scalability
      </section-title>
      <paragraph>
       Execution time and scalability are typical metrics for scheduling algorithms. Hence, in this set of experiments, we vary the number of tasks and measure the execution time of the Off-Opt-Swap, the Off-Opt-Charge, the Off-Incr-Swap, the Off-Incr-Charge, the Off-Greedy-Swap, the Off-Greedy-Charge, the Off-Greedy-Swap-LS and the Off-Greedy-Charge-LS (Table 2).
      </paragraph>
      <section label="7.1.1">
       <section-title>
        Improvement in execution time with pre-processing
       </section-title>
       <paragraph>
        Here, we evaluate the improvement in execution time for the Off-Opt-Swap and Off-Opt-Charge when the MaxFlow algorithm is used as a pre-processing step. As can be seen in Fig. 3, when the pre-processing step is used, the execution time decreases significantly. For example, for 200 tasks, the execution time for the Off-Opt-Swap is reduced by 62.9%, and for the Off-Opt-Charge by 60.8%. This is due to the fact that the MaxFlow algorithm prunes the set of tasks. Thus, for the rest of the experiments, we always use the optimal algorithm in combination with the pre-processing step. Note that improvement in execution time is achieved also for the greedy algorithm, but in this case it is very small due to the fact that the execution time was already low.
       </paragraph>
       <paragraph>
        Regarding the pre-processing step itself, the execution time is found to be very low. For example, in a setting with 100 EVs and up to 3000 tasks we see that the execution times of both variations of the MaxFlow algorithm increase linearly (i.e., {a mathematical formula}R2=0.9971 for the MaxFlow and {a mathematical formula}R2=0.992 for the MaxFlowInit).{sup:21} As can be seen in Fig. 4 both have very low execution time as for 3000 tasks both execute in well under 0.35 s with the variation where the initial location is optimized always being the slowest, because one more constraint and one more decision variable exists. The optimization of the initial location of EVs, leads to an increase in average task execution. However, doing so can create other problems. For example, relocation of vehicles may be needed prior to the beginning of the operation of the MoD company which incurs some extra cost. Thus, in the following experiments we focus in the case where the initial location is not optimized.
       </paragraph>
      </section>
      <section label="7.1.2">
       <section-title>
        Scalability across varying (small to medium) task sizes
       </section-title>
       <paragraph>
        In a setting with 15 EVs and up to 300 tasks, in the case of battery swap and as can be seen in Fig. 5, the greedy algorithm is 10 times faster than the incremental-MIP and 1000 times faster than the optimal. The rate of growth of the greedy algorithm is linear, while for the other two algorithms the rate is quadratic (see Table 3). The linear time complexity of the greedy is related to the pre-processing step which prunes all infeasible tasks (see bottom of Section 5.4). The number of tasks shown on the x-axis of the following figures is based on the number of tasks after the pre-processing step. Thus, each point of the plot is the centroid of the execution times of multiple experiments for various actual numbers of tasks. In the case of the incremental-MIP, the pre-processing step leads to a lower number of executed tasks and as will be discussed in the next subsection it is not used in the rest of the experiments. However, here we plot the execution time in combination with the pre-processing step to have a fair comparison with the other algorithms. Regarding the incremental-MIP, we have investigated the use of cut constraints to improve the scalability of this algorithm. In fact, we added two cut constraints: 1) For the tasks that overlap in time, only one of them can be executed. 2) The tasks that are isolated (i.e., they are not in the EV's initial location and there are no tasks leading to that location), are not executed (i.e., decision variable set to zero). The addition of these extra constraints has reduced the MIP pre-processing time, but not the total execution time. For example, in a setting with 2000 tasks and 45 EVs, the MIP pre-processing time has been reduced from 0.352 s to 0.345 s, but the total execution time has been increased from 22296.4 s to 23390 s. Thus, we decided not to use these extra constraints.
       </paragraph>
       <paragraph>
        In the case of battery charge and as can be seen in Fig. 6, all algorithms behave similarly to the battery swap, but the average execution time of all of them is higher (see also Table 4). In the case of battery charge, we also plot the execution time of the greedy algorithm in combination with the local search technique. This combination leads to higher execution times compared to the incremental-MIP, but lower compared to the optimal. In fact, the execution time of the Off-Greedy-Charge-LS initially increases but as the number of tasks increases beyond 120, the execution time decreases. This can be explained by the fact that given the number of EVs remains stable and the number of tasks increases, the greedy algorithm already calculates a schedule which covers most of the EVs' availability and for this reason the local search cannot improve the solution a lot. Thus, it terminates sooner compared to other settings where the space for improvement is larger. As will be described in Section 7.2, when the Off-Greedy-Swap is combined with the MaxFlow and under some assumptions, it provides the optimal solution. Thus, there was no point to combine the local search with battery swap.
       </paragraph>
      </section>
      <section label="7.1.3">
       <section-title>
        Scalability across varying large task sizes
       </section-title>
       <paragraph>
        Here we assume the full range of some EVs (i.e., 20% of the available EVs) not to be long enough to execute some of the longer trips. Thus, the MaxFlow provides the upper limit of all feasible tasks (see more details on this in Section 7.2) (i.e., the Off-Greedy-Swap does not provide the optimal solution any more). We choose a setting with 100 EVs and up to 3000 tasks. For such settings the optimal algorithm does not scale, and the low execution times of the incremental and the greedy algorithms make them the preferable options. When battery swap is used and as can be seen in Fig. 7, the Off-Greedy-Swap is 1000 times faster than the Off-Incr-Swap and 10000 times faster than the Off-Greedy-Swap-LS. It is interesting to notice that when local search is used, the execution time initially increases but then, for more than 1300 tasks starts decreasing (see also Table 5). The explanation is similar to the one given in the previous subsection.
       </paragraph>
       <paragraph>
        When battery charge is used and as can be seen in Fig. 8, the execution times of all algorithms follow a similar trend (see also Table 6). However, in contrast to battery swap, for large number of tasks the Off-Incr-Charge has higher execution time compared to Off-Greedy-Charge-LS. This can be explained by the fact that Off-Opt-Charge, which is used as part of both algorithms, is more time consuming compared to Off-Opt-Swap and similarly to the previous case, for large numbers of tasks, the local search algorithm terminates earlier. Note, that in the case of Off-Greedy-Swap-LS the time is second degree polynomial but the {a mathematical formula}x2 term is negative. However, in the case of Off-Greedy-Charge-LS it is positive. This can be explained by the fact that in the case of battery charging (as we will see in Section 7.2) the space for improvement is bigger. Thus, the local search technique runs for longer time. Note that for much larger numbers of tasks we expect the execution time to start dropping as well. We next evaluate the execution time by varying the rest of the dimensions (i.e., EVs, time points and locations).
       </paragraph>
      </section>
      <section label="7.1.4">
       <section-title>
        Scalability across other dimensions
       </section-title>
       <paragraph>
        In this section, we evaluate our algorithms in terms of execution time while varying the other dimensions of the problem (i.e., EVs, time points and locations). As can be seen in Fig. 9, Fig. 10, Fig. 11 and in Table 7 in all cases the execution times for the Off-Opt-Swap and the Off-Incr-Swap increase quadratically. However, when the locations vary, the term of {a mathematical formula}x2 is negative (i.e., execution time initially increases and then decreases). This can be explained due to the fact that when the number of locations increases, but the number of EVs remains unchanged, the tasks spread around too much and fewer of them can be executed making the problem easier to solve. In terms of the Off-Greedy-Swap, when varying the number of EVs and time points, the execution time increases linearly, while when varying the number of locations it increases quadratically. Thus, the theoretical complexity analysis presented in Section 5.4 is verified. The results for battery charge are similar.
       </paragraph>
      </section>
     </section>
     <section label="7.2">
      <section-title>
       EXP2: completion of tasks and EV utilization
      </section-title>
      <paragraph>
       Here we evaluate all algorithms in terms of average task completion and average EV utilization. In so doing, we have two main scenarios: In the first one we assume that all EVs carry the same battery which, when fully charged, is large enough to execute even the longest task. In the second one we assume that some EVs carry a smaller battery (or a not-fully charged one) and are not able to execute some of the longest tasks.
      </paragraph>
      <paragraph>
       In the case where all EVs carry the same battery and as can be seen in Fig. 12, Fig. 13, when the Off-Greedy-Swap is used after the pre-processing step (i.e., MaxFlow algorithm), it always provides the optimal solution (see explanation in Section 5.4.3). In contrast, when the Off-Greedy-Charge is used after the pre-processing step, it provides a solution close to the optimal (i.e., 97% of the optimal for 300 tasks). This can be explained by the fact that battery charging is more time consuming compared to the battery swap and not all EVs have full range once they are about to start executing a task. However, when the local search algorithm is used, having as input the solution of the greedy algorithm, the performance of the Off-Greedy-Charge improves and reaches 98.5% of the Off-Opt-Charge. It is interesting to note that when the greedy algorithm is combined with the MaxFlow, the improvement in the number of completed tasks, compared to the case where the MaxFlow is not used and for a setting with 200 tasks, is 26.2% for the Off-Greedy-Swap and 24% for the Off-Greedy-Charge. Regarding the incremental-MIP algorithm, in all cases performs worse compared to both the optimal and the greedy algorithms. For example, for 300 tasks it is at 96.34% of the Greedy-Swap and the Off-Opt-Swap and at 98.74% of the Greedy-Charge without local search and at 97.27% when its solution is improved with local search. When it is used in comparison with the MaxFlow, the results are even worse. This could be explained by the fact that the MaxFlow provides the optimal set of tasks given the full set of EVs. Thus, when this is broken down into sub-problems the solution deteriorates. Thus, in this experimental setting, the incremental-MIP is not used.
      </paragraph>
      <paragraph>
       For a larger setting with 100 EVs and up to 4000 tasks, the performance of the algorithms remains similar. The Off-Greedy-Swap in combination with the MaxFlow provides the optimal solution, while the Off-Greedy-Charge is very close to the optimal. In fact, for 4000 tasks the Off-Greedy-Charge is at 99.6% of the optimal, and when the local search is applied, the efficiency increases to 99.75% of the optimal. The better performance of the Off-Greedy-Charge, compared to the smaller setting, can be explained by the fact that for very large numbers of tasks, the options for the greedy algorithm are many and it is not very sensitive on the optimal selection of each task. The fact that the Off-Greedy-Charge does not reach the absolute optimal was expected due to its myopic nature (i.e., local heuristic) (Figs. 14 and 15).
      </paragraph>
      <paragraph>
       Given the performance of all algorithms, we argue that when battery swap is used, the Off-Greedy-Swap in combination with the MaxFlow is the appropriate solution for all problem sizes as it provides the optimal solution with very low execution time. Whereas, when battery charge is used, the combination of the Off-Greedy-Charge with the MaxFlow and the use of local search afterwords leads to the best solution especially for large problems. However, for small problems (i.e., tens of EVs and few hundreds of tasks) the Off-Opt-Charge is the best choice as it provides the optimal solution in reasonable time (even if it slower compared to the others).
      </paragraph>
      <paragraph>
       Now, when trying to maximize the EV utilization (i.e., using as objective function Equation (7)) and as can be seen in Fig. 16, we observe an average 3.6% increase in EV utilization, while the average number of completed tasks is decreased by 1.5%. In other words, the difference between the two objective functions in terms of EV utilization and task completion are small. However, in settings where tasks with longer duration also exist, we expect this difference to increase, as the solver would have more options to fill the travelling schedule of the EVs with long tasks. Note that in all cases the differences between the battery swap and the battery charge variations in terms of completed tasks are very small. For example, for 15 EVs and 200 tasks both the Off-Opt-Swap and the Off-Opt-Charge executed on average 119,6 tasks (see also Fig. 17). On some rare occasions, we have noticed some very slight differences (1 or 2 tasks). This can be explained by the fact that fast charging is used, thus making the delay compared to the battery swap small (i.e., at most 3 time points, as opposed to 1 time point).
      </paragraph>
      <paragraph>
       The MaxFlow algorithm treats all EVs equally and assumes that all of them can execute any task. However, when some EVs (i.e., 20% of the available EVs) carry smaller batteries and cannot execute some of the longest tasks, then the set of tasks returned by the MaxFlow is the upper limit of the tasks that can be executed. An interesting question is how the scheduling algorithms perform in this case. In a setting with up to 200 tasks and 15 EVs and as can be seen in Fig. 18, the Off-Opt-Swap always achieves the best performance (i.e., 11% better performance compared to the greedy for 200 tasks). Note that when the MaxFlow returns the upper limit of tasks to be executed, the Off-Greedy-Swap and as was expected, does not provide the optimal solution anymore. The Off-Greedy-Swap-LS and the Off-Incr-Swap have similar performance with the greedy being slightly ahead for smaller number of tasks, while the incremental-MIP matches the performance of the greedy for larger number of tasks. Now, in a setting with up to 3000 tasks and 100 EVs and as can be seen in Fig. 19, the performance of the Off-Greedy-Swap is at 99.5% of the Off-Greedy-Swap-LS when 3000 tasks exist. Moreover, the Off-Incr-Swap performs initially worse compared to the greedy algorithm, but for more than 1000 tasks, it has an advantage. However, for more than 2500 tasks it starts levelling off. Note that the standard deviation of the Off-Incr-Swap is higher compared to the Off-Greedy-Swap. Also note that the incremental-MIP algorithm is not used in combination with the local search because the execution time increases 10-times on average, and the solution quality improves by less than 0.3% on average. Given the execution time of the incremental and the greedy algorithms combined with local search, we argue that for a setting where the EVs carry different battery types, and when the number of tasks is larger than 1000, the incremental-MIP is the appropriate solution. As can be seen in Fig. 20, the performance for battery charge is similar. We next discuss the sensitivity of the MaxFlow algorithm.
      </paragraph>
     </section>
     <section label="7.3">
      <section-title>
       EXP3: sensitivity of the MaxFlow
      </section-title>
      <paragraph>
       Here, we evaluate the MaxFlow algorithm in a setting where we fix the number of tasks to be completed to 500, and vary the number of EVs as well as the number of the locations of the pick-up and drop-off points in order to determine how the EV-to-task-allocation problem is affected by the change in the number of EVs and locations. Note that here synthetic data on locations are used. Given that the number of tasks to be completed remains fixed, one could expect that by increasing the number of EVs, the number of completed tasks would also increase. In the case where the number of locations remains fixed this is indeed the case (see Fig. 21). However, in the case where the number of locations increases we observe an opposite trend. Interestingly, when 40 EVs and 10 locations exist, the number of completed tasks is actually higher compared to the case where 100 EVs and 60 locations exist. This is an interesting observation which can be explained as follows: 1) as the number of locations increases, the average number of EVs at one location at {a mathematical formula}t=0, decreases and therefore, the probability of an EV being able to execute a future task starting from a given location decreases, and 2) as the number of locations increases, the number of all possible trips increases exponentially, and therefore, EVs tend to spread around too much. Thus, similarly to the previous point, the probability of an EV being able to execute a future task decreases. Thus, the optimization of the number and the location of the pick-up and drop-off points is an important problem to be solved by any MoD company [21] as it is related to the cost of a possible MoD deployment (i.e., number and locations of stations), as well as its performance in terms of serviced tasks and profit. Our algorithms and experimental results can help towards this. We next discuss the efficiency of the battery swap optimization algorithm.
      </paragraph>
     </section>
     <section label="7.4">
      <section-title>
       EXP4: battery swap optimization
      </section-title>
      <paragraph>
       Here, we evaluate our proposed battery swap optimization algorithm against a setting where no such optimization takes place, based on the tasks assigned by the scheduling algorithms to each EV. In doing so, we assume all EVs to carry the same battery type, which has a discharge rate {a mathematical formula}conj=10 (i.e., at each time point, 10% of the battery is discharged) and the average trip duration to be 2 time points. The battery swap minimization algorithm is shown to achieve a reduction of up to 87.5% (see Fig. 22) in the number of necessary battery swaps. Its execution time is well under half second even for large settings. Overall, the minimization of the battery swaps is an important task in order to reduce the cost of battery swapping in a real world deployment. Note that this algorithm can be applied to all scheduling algorithms which use battery swap. In the next section, the optimal offline algorithm is evaluated against the online one.
      </paragraph>
     </section>
     <section label="7.5">
      <section-title>
       EXP5: online VS offline scheduling – task execution
      </section-title>
      <paragraph>
       Given that full knowledge of future demand is not always possible, here the online algorithm (Algorithm 7) is evaluated against the optimal one. We choose {a mathematical formula}η=15 and {a mathematical formula}r=5 (reminder: η represents the number of sets of expected tasks, and r the number of rounds – see Section 6), as these numbers were observed to provide a good balance between performance and execution time. Also, the day is divided into three periods, (i.e., morning, noon, afternoon) and for each round the tasks for one period are fixed, while for the rest are drawn from a distribution (i.e., at first the morning tasks are fixed while noon and afternoon tasks come from the distribution. They are generated from a uniform and a Gaussian distribution: 50% of tasks come from a uniform distribution and 50% come from a Gaussian distribution, while mean and σ are selected in this way so as the tasks to come from future session (i.e., noon, or afternoon and based on the current time point).
      </paragraph>
      <paragraph>
       As can be seen in Fig. 23, Fig. 24, the Online algorithm has an acceptable performance: for a setting with up to 100 tasks, the performance achieved by this algorithm in terms of average task completion, is no less than 90% compared to the optimal offline. Note, that future tasks come 50% from a Gaussian distribution, while the remaining 50% come from a uniform distribution. Thus, we also show that our methodology can efficiency handle tasks coming from different distributions. Also, the execution time for each η is similar to the times presented for the optimal offline algorithms for the same number of tasks. Thus, based on the number and the types of computers the MoD company possesses, η and r can be chosen accordingly so as better accuracy in the prediction to be achieved,{sup:22} while the schedule to be calculated within the available time (i.e., the schedule of the tasks must be decided before the actual execution of them). In the next section, the correctness of the MIP and greedy algorithms is verified.
      </paragraph>
     </section>
     <section label="7.6">
      <section-title>
       EXP6: correctness of the MIP algorithm
      </section-title>
      <paragraph>
       In order to verify the correctness of both the MIP and greedy algorithms we conducted a number of experiments. We created a set of tasks, that could be executed by a single EV (i.e., the end location of one task was the start location of the next one). Then we run both algorithms for this set of tasks and both gave us the optimal solution. Then we expanded the set of tasks (with known outcomes) and we observed that the MIP returned the optimal solution. The greedy could provide the optimal solution up to a certain number of EVs and tasks, but for larger numbers (i.e., more than 20 tasks and more than 1 EV) it was giving sub-optimal solutions as was expected. In the next section, issues related to the time complexity of the MIP formulations of the problem are discussed.
      </paragraph>
     </section>
     <section label="7.7">
      <section-title>
       Discussion on the computational complexity of the offline optimal solution
      </section-title>
      <paragraph>
       The MIP formulation for the offline optimal algorithm is solved using CPLEX. CPLEX uses the Branch &amp; Cut optimization method [26] which is, in turn, based on a Branch &amp; Bound search algorithm. Initially, at the root node the problem is solved as a linear program using, e.g., simplex, or the shifting optimizer algorithm (this approach was first introduced by IBM under the name SPRINT approach [2]). Then, if a solution exists but not all variables are integral, Branch and Bound begins by choosing a non-integral variable and fixing its value to the two closest (upper and lower) integers and resolving the problem with the remaining variables. According to [57], the average case complexity of the branch &amp; bound algorithm is polynomial in the depth of the search tree, when the expected number of the children of a node that has the same cost as their parent, is at least 1. If a MIP problem has d variables, then the search space of Branch &amp; Cut consists of the combination of all the possible splits of the problem variables, which accounts to a binary tree with depth d and {a mathematical formula}2d nodes. In all our experiments we have observed in the CPLEX log that the value of the objective function at the root node of the Branch &amp; Cut starts with the optimal value. Therefore all branches in the search tree lead to nodes that have the same cost with the root node. Due to this observation, we expect that the computational complexity of the algorithm should be polynomial to the number of variables of the problem. Thus, we next calculate the number of decision variables and examine their correlation to the execution time.
      </paragraph>
      <paragraph>
       For Off-Opt-Swap, the number {a mathematical formula}dswap of variables is given by the following equation: {a mathematical formula}dswap=|Δ|+|Δ|×|A|×|T|+|A|×|L|×|T| where {a mathematical formula}|Δ| is the total number of tasks, {a mathematical formula}|A| is the total number of EVs, {a mathematical formula}|T| is the total number of time points that the day is divided in, and |L| is the total number of locations (pick-up and drop-off points) (i.e., the problem has four dimensions in total). Decision variable {a mathematical formula}λδi has 1 dimension namely {a mathematical formula}|Δ|, decision variable {a mathematical formula}ϵj,i,t has 3 dimensions namely {a mathematical formula}|A|, {a mathematical formula}|Δ| and {a mathematical formula}|T| and decision variable {a mathematical formula}prkj,t,k has 3 dimensions namely {a mathematical formula}|A|, {a mathematical formula}|T| and {a mathematical formula}|L|. In order to verify our expectation that the problem grows in polynomial time, we plot the time to solve the MIP problem against the number of the variables {a mathematical formula}dswap of each problem calculated using the above equation. Each time we vary one dimension of the problem and hold the rest fixed (see Fig. 25, Fig. 26, Fig. 27, Fig. 28). Note that the number of decision variables is after the pre-processing step. For Δ, A and T our results verify (in all cases we observe {a mathematical formula}R2&gt;95%) that the time complexity is {a mathematical formula}O(dswap2). Therefore, the complexity according to the problem size is {a mathematical formula}O((Δ+Δ×A×T+A×L×T)2)=O(Δ2+Δ2×A2×T2+A2×L2×T2+2×Δ2×A×T+2×Δ×A×L×T+2×Δ×A2×L×T2)≅O(A2×T2×(Δ2+L2)). Interestingly though, for the L dimension of the problem although the execution time remains second degree polynomial in the number of decision variables, the coefficient for {a mathematical formula}x2 gets negative values (see Fig. 28). As has been explained earlier (see Section 7.2), when the number of locations increases, the EVs spread around too much and their ability to execute tasks is reduced. Therefore, many infeasible tasks exist and the execution time drops. Thus, we can conclude to the result that the time complexity of the MIP formulation is not related solely to the number of decision variables but also to the hardness of the problem to be solved. Next, we evaluate the complexity of the variation with battery charge.
      </paragraph>
      <paragraph>
       For the Off-Opt-Charge, the number {a mathematical formula}dcharge of variables is given by the following equation: {a mathematical formula}dcharge=|Δ|+|Δ|×|A|×|T|+|A|×|L|×|T|+|A|×|T| (i.e., decision variable {a mathematical formula}λδi has 1 dimension namely {a mathematical formula}|Δ|, decision variable {a mathematical formula}ϵj,i,t has 3 dimensions namely {a mathematical formula}|A|, {a mathematical formula}|Δ| and {a mathematical formula}|T|, decision variable {a mathematical formula}prkj,t,k has 3 dimensions namely {a mathematical formula}|A|, {a mathematical formula}|T| and {a mathematical formula}|L| and decision variable {a mathematical formula}bchj,t has 2 dimensions namely {a mathematical formula}|A| and {a mathematical formula}|T|). We executed the same experiments as in the case of Off-Opt-Swap and the results also verify (in all cases we observe {a mathematical formula}R2&gt;96%) that for Δ, A and T the time complexity is {a mathematical formula}O(dcharge2). Therefore, the complexity according to the problem size is {a mathematical formula}O((Δ+Δ×A×T+A×L×T+A×T)2)=O(Δ2+2×Δ2×A×T+2×A×L×T×Δ+2×A×Δ×T+Δ2×A2×T2+2×Δ×A2×L×T2+2×Δ×A2×T2+A2×L2×T2+2×A2×L×T2+A2×T2)≅O(A2×T2×(Δ2+L2)). For dimension {a mathematical formula}|L|, the results are similar to the ones discussed in the previous paragraph.
      </paragraph>
      <paragraph>
       In fact, as can be seen in Section 7.1, all the measurements of the execution times have revealed a quadratic time complexity, which is consistent with the above analysis. In the next section, the main results, observations and conclusions are summarized.
      </paragraph>
     </section>
     <section label="7.8">
      <section-title>
       Summary of key results
      </section-title>
      <paragraph>
       To summarize, in our experimental evaluation we observe that when all EVs carry the same battery which is large enough for the longest trips, the greedy algorithm with battery swap in combination with the max flow provides the optimal solution. At the same time, the variation with battery charge is at 97% of the optimal without the local search, and at 98.5% when local search is used. Moreover, in case where some EVs do not have a large enough battery to execute some of the longest trips, we observe that the greedy algorithm does not provide the optimal solution anymore and that the incremental-MIP is the correct choice as it generates solution 0.5% better than the greedy and with lower execution time, while the optimal algorithm is still the best but scales up to medium sized problems only. Moreover, we show that when the objective is the maximization of EV utilization, the utilization increases by 3.6% and the number of completed tasks reduces by 1.5% on average. In addition, we proposed a battery swap minimization algorithm, which is applied a-posteriori to an already existing task execution schedule and minimizes the necessary battery swaps, thus also minimizing cost. Finally, we also proposed an online algorithm which takes into consideration the uncertainty in future demand and verified that it has good performance.
      </paragraph>
      <paragraph>
       Generally speaking, the performance of these algorithms depends on the number of EVs, the number of pick-up and drop-off locations, and as a consequence of this, the number of all possible trips.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>