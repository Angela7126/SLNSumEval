<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Constrained clustering by constraint programming.
   </title>
   <abstract>
    Constrained Clustering allows to make the clustering task more accurate by integrating user constraints, which can be instance-level or cluster-level constraints. Few works consider the integration of different kinds of constraints, they are usually based on declarative frameworks and they are often exact methods, which either enumerate all the solutions satisfying the user constraints, or find a global optimum when an optimization criterion is specified. In a previous work, we have proposed a model for Constrained Clustering based on a Constraint Programming framework. It is declarative, allowing a user to integrate user constraints and to choose an optimization criterion among several ones. In this article we present a new and substantially improved model for Constrained Clustering, still based on a Constraint Programming framework. It differs from our earlier model in the way partitions are represented by means of variables and constraints. It is also more flexible since the number of clusters does not need to be set beforehand; only a lower and an upper bound on the number of clusters have to be provided. In order to make the model-based approach more efficient, we propose new global optimization constraints with dedicated filtering algorithms. We show that such a framework can easily be embedded in a more general process and we illustrate this on the problem of finding the optimal Pareto front of a bi-criterion constrained clustering task. We compare our approach with existing exact approaches, based either on a branch-and-bound approach or on graph coloring on twelve datasets. Experiments show that the model outperforms exact approaches in most cases.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Constrained Clustering has received much attention this last decade. It allows to make the clustering task more accurate by integrating user constraints. Several kinds of constraints can be considered. First, constraints may be used to limit the size or the diameter of clusters; second, they can enforce expert knowledge instances that must be or cannot be in the same cluster (must-link or cannot-link constraints). Much work has focused on instance-based constraints and has adapted classical clustering methods to handle must-link or cannot-link constraints. A small number of earlier studies have considered the integration of different kinds of constraints. These studies are based on declarative frameworks and offer exact methods that either enumerate all the solutions satisfying the user constraints, or find a global optimum when an optimization criterion is given. For instance, in [1] a SAT based framework for constrained clustering has been proposed, integrating many kinds of user constraints but limited to clustering tasks into two clusters. A framework for conceptual clustering based on Integer Linear Programming has also been proposed in [2]. In [3], we have presented a model based on Constraint Programming for constrained clustering. This model allows to choose one among different optimization criteria and to integrate various kinds of user constraints. As far as we know, the approach we propose is the only one able to handle different optimization criteria and all popular constraints, for any number of clusters. It is based on Constraint Programming (CP): in such a paradigm, a constraint optimization problem or a constraint satisfaction problem is modeled by defining variables with their domains and by expressing constraints on these variables. Solving a CP problem relies on two operations: constraint propagation that reduces the domain of the variables by removing inconsistent values and branching that divides the problem in subproblems, by taking an unassigned variable and by splitting its domain into several parts. It is important to notice that modeling a task in Constraint Programming implies several choices, which have a high impact on the efficiency of the approach: the choice of the variables and the choice of the constraints for the model, the development of filtering algorithms dedicated to the task and the use of adapted search strategies for solving the model. A point in favor of CP is that the requirement of getting an exact solution can be relaxed by using metaheuristics or local search methods. For the time being, we have fully investigated exact methods, to push the efficiency of the framework as far as possible. Approximate search strategies could be integrated in the future.
     </paragraph>
     <paragraph>
      In this paper, we propose a new model for Constrained Clustering, still based on Constraint Programming, but significantly improved compared to the previous model [3]. In the previous model, two sets of variables were introduced, namely a variable for each cluster identifying a cluster by one of its points and a variable for each point expressing its assignment to a cluster. The number of clusters had to be set beforehand. The new model we present here contains only a variable for each point, giving the index of the cluster the point belongs to. As a result, the constraints enforcing the solution to be a partition and breaking symmetries are entirely different. The new model is lighter in terms of the number of variables. It also enables to remove the restriction on the number of clusters; only bounds on the number of clusters are required. Moreover, in order to make this model efficient, we have developed dedicated global constraints for three optimization criteria: minimizing the maximal diameter, maximizing the split between clusters, and minimizing the within-cluster sum of dissimilarities.
     </paragraph>
     <paragraph>
      The approach we propose may be easily embedded in a general process for the task of Constrained Clustering. Considering Data Mining as an iterative and interactive process composed of the classical steps of task formulation, data preparation, application of a tool, thus requiring to set parameters, and validation of the results, a user can specify the task at hand including or not some constraints and decide to change the settings according to the results. He/she may decide to change the constraints, removing or relaxing some constraints, adding or hardening other constraints. The modularity and declarativity of our model allow this easily. In this paper, we illustrate the integration of our model in a more complex process by considering a bi-criterion clustering problem, namely finding the Pareto front when minimizing the maximal diameter and maximizing the minimal split. To achieve this, our framework is integrated in an algorithm, which alternatively calls our model to minimize the maximal diameter and then to maximize the split between clusters with adapted constraints.
     </paragraph>
     <paragraph>
      Our contributions are as follows.
     </paragraph>
     <list>
      <list-item label="•">
       We propose a new model based on Constraint Programming, allowing to find an optimal solution for clustering under constraints, given an optimization criterion. This new model improves substantially the previous one, it is more modular (each criterion is implemented by a global constraint) and it is much more efficient.
      </list-item>
      <list-item label="•">
       We show that such a framework can easily be embedded in a more general process and we illustrate this on the problem of finding the optimal Pareto front of a bi-criterion constrained clustering task. As far as we know, this is the first approach to handle bi-criterion clustering in presence of user-constraints.
      </list-item>
      <list-item label="•">
       We propose new global optimization constraints with dedicated filtering algorithms, thus allowing to make the model more efficient.
      </list-item>
      <list-item label="•">
       We compare this model with existing exact approaches, based either on a branch-and-bound approach [4] or on graph coloring [5] on twelve datasets. Experiments show that the model we propose is generally more efficient. Moreover we compare the two models based on CP that we have developed and we show that the different changes (search strategy and development of global constraints) allow to improve the model.
      </list-item>
     </list>
     <paragraph>
      The paper is organized as follows. Section 2 is dedicated to preliminaries on Constrained Clustering and Constraint Programming. Related work is presented in Section 3. Section 4 is devoted to the presentation of both CP models, the first one presented in [3] and the new one. The filtering algorithms for the optimization criteria are presented in Section 5. We show in Section 6 how our framework can be easily integrated for solving a bi-criterion constrained clustering task. Experiments are presented in Section 7, showing the performance and the flexibility of our approach.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <section label="2.1">
      <section-title>
       Constrained clustering
      </section-title>
      <paragraph>
       Cluster analysis is a Data Mining task that aims at partitioning a given set of objects into homogeneous and/or well-separated subsets, called classes or clusters. It is often formulated as the search for a partition such that the objects inside the same cluster are similar, while being different from the objects belonging to other clusters. These requirements are usually expressed by an optimization criterion and the clustering task is usually defined as finding a partition of objects that optimizes the given criterion. In the remainder of the paper, we consider a dataset of n objects {a mathematical formula}O={o1,…,on} and a dissimilarity measure {a mathematical formula}d(oi,oj) between any two objects {a mathematical formula}oi,oj∈O. A partition Δ of objects into k clusters {a mathematical formula}C1,…,Ck is such that: (1) for all {a mathematical formula}c∈[1,k],{sup:1}{a mathematical formula}Cc≠∅, (2) {a mathematical formula}∪cCc=O and (3) for all {a mathematical formula}c≠c′, {a mathematical formula}Cc∩Cc′=∅. The optimization criterion can be among others:
      </paragraph>
      <list>
       <list-item label="•">
        Minimizing the maximal diameter of clusters: the maximal diameter of a partition Δ is the largest dissimilarity between two objects in the same cluster,{a mathematical formula} A clustering task that minimizes this criterion is also called nonhierarchical complete-link clustering.
       </list-item>
       <list-item label="•">
        Maximizing the minimal split between clusters: the minimal split between clusters of a partition Δ is the smallest dissimilarity between two objects of different clusters,{a mathematical formula} A clustering task that maximizes this criterion is also called single-link clustering.
       </list-item>
       <list-item label="•">
        Minimizing the within-cluster sum of dissimilarities (WCSD): this sum for a partition Δ is defined as{a mathematical formula} For this criterion the dissimilarity {a mathematical formula}d(oi,oj) is usually measured by the squared Euclidean distance between {a mathematical formula}oi and {a mathematical formula}oj.
       </list-item>
       <list-item label="•">
        Minimizing the within-cluster sum of squares (WCSS): in an Euclidean space the within-cluster sum of squares is the sum of the squared Euclidean distances between each object {a mathematical formula}oi and the centroid {a mathematical formula}mc of the cluster containing {a mathematical formula}oi{a mathematical formula} Let us notice that, when the squared Euclidean distance is used for measuring the dissimilarities, the WCSS criterion is mathematically equivalent to the WCSD criterion standardized by the division by the size of each cluster:{a mathematical formula}
       </list-item>
      </list>
      <paragraph>
       Most of the clustering algorithms rely on an optimization criterion. All of these criteria are NP-Hard, except the split criterion. In consequence, most of the algorithms search for a local optimum. For instance, the k-means algorithm finds a local optimum for the WCSS criterion as well as FPF (Furthest Point First) [6] for the diameter criterion. Several optima may exist, some may be closer to the one expected by the user. In order to model the task better, but also in the hope of reducing the complexity, user specified constraints are added, leading to Constrained Clustering that aims at finding clusters that satisfy the user constraints. User constraints can be classified into cluster-level constraints, specifying requirements on clusters, or instance-level constraints, specifying requirements on pairs of objects. Most of the attention has been put on instance-level constraints, first introduced in [7]. Commonly, two kinds of constraints are used: must-link and cannot-link. A must-link constraint on two objects {a mathematical formula}oi and {a mathematical formula}oj expresses that they must be in the same cluster: {a mathematical formula}∀c∈[1,k],oi∈Cc⇔oj∈Cc. A cannot-link constraint on two objects {a mathematical formula}oi and {a mathematical formula}oj expresses that they must not be in the same cluster: {a mathematical formula}∀c∈[1,k],¬(oi∈Cc∧oj∈Cc).
      </paragraph>
      <paragraph>
       Cluster-level constraints impose requirements on the clusters. The minimum capacity constraint requires that each cluster has a number of objects greater than a given threshold α: {a mathematical formula}∀c∈[1,k],|Cc|≥α, whereas the maximum capacity constraint requires each cluster to have a number of objects inferior to a predefined threshold β: {a mathematical formula}∀c∈[1,k],|Cc|≤β.
      </paragraph>
      <paragraph>
       The maximum diameter constraint specifies an upper bound γ on the diameter of the clusters: {a mathematical formula}∀c∈[1,k],∀oi,oj∈Cc,d(oi,oj)≤γ. The minimum split constraint, also called the δ-constraint in [8], requires the distance between any two points of different clusters to be superior or equal to a given threshold δ: {a mathematical formula}∀c∈[1,k],∀c′≠c,∀oi∈Cc,∀oj∈Cc′,d(oi,oj)≥δ. As observed in [8], the maximum diameter constraint can be represented by a conjunction of cannot-link constraints and the minimum split constraint can be represented by a conjunction of must-link constraints.
      </paragraph>
      <paragraph>
       The ϵ-constraint introduced in [8] requires for each point {a mathematical formula}oi to have in its neighborhood of radius ϵ at least another point belonging to the same cluster: {a mathematical formula}∀c∈[1,k],∀oi∈Cc,∃oj∈Cc,oj≠oi and {a mathematical formula}d(oi,oj)≤ϵ. This constraint tries to capture the notion of density, introduced in DBSCAN [9]. We have extended it by proposing a density-based constraint, stronger than the ϵ-constraint: it requires that for each point {a mathematical formula}oi, its neighborhood of radius ϵ contains at least m points belonging to the same cluster as {a mathematical formula}oi.
      </paragraph>
      <paragraph>
       In the last ten years, many works have been done to extend classical algorithms for handling must-link and cannot-link constraints. This is achieved either by modifying the dissimilarity measure, or the objective function or the search strategy. Recently, several works have investigated declarative approaches of constrained clustering, which aim at extending traditional algorithms to different types of user constraints. A presentation of these works is given in Section 3.
      </paragraph>
     </section>
     <section label="2.2">
      <section-title>
       Bi-criterion constrained clustering
      </section-title>
      <paragraph>
       Clustering with the criterion of minimizing the maximal diameter aims at finding homogeneous clusters, but it often suffers from the dissection effect [10], i.e. quite similar objects may be classified in different clusters, in order to keep the diameters small. On the other hand, clustering with the criterion of maximizing the minimal split, which aims at finding well separated clusters, often suffers from the chain effect [11], i.e. a chain of closed objects may lead to group very different objects in the same cluster. The popular WCSS criterion, which minimizes the sum of the squared distances between points and the center of their cluster also suffers from undesirable effects. Considering this criterion, objects that should be in a large group may be classified in different clusters in order to keep this sum small. Fig. 1 gives an illustration of these effects. Image A shows three groups that can be easily identified. Image B shows the obtained solution with the diameter criterion when the number of clusters is set to 3. In this partition, some points are very close but they are classified in two different groups. The partition obtained when considering the split criterion is shown in Image C. Because of the chain effect, the largest group contains points that are very far each from other. The optimal solution with the WCSS criterion is shown in Image D. In this partition, some points that are very close are grouped in different clusters.
      </paragraph>
      <paragraph>
       A good partition with homogeneous and well-separated clusters should have a minimal diameter and a maximal split. Unfortunately, such a partition in general does not exist, since the two criteria are often conflicting. This problem can be modeled by considering the bi-criterion of maximizing the minimal split between clusters and minimizing the maximal diameter, as introduced in [5]. Considering these two criteria together is natural and allows to capture both the homogeneity and the separation requirements for a good clustering. A general approach for handling two optimization criteria is to find the Pareto optimal solutions. A Pareto optimal solution is a solution such that it is not possible to improve the value of one criterion without degrading the value of the other one. A partition {a mathematical formula}Δ′dominates a partition Δ if and only if:{a mathematical formula} or{a mathematical formula} A partition Δ is Pareto optimal if and only if there is no partition {a mathematical formula}Δ′ that dominates Δ. Two Pareto optimal solutions {a mathematical formula}Δ1 and {a mathematical formula}Δ2 are equivalent if {a mathematical formula}D(Δ1)=D(Δ2) and {a mathematical formula}S(Δ1)=S(Δ2). A set {a mathematical formula}P of Pareto optimal solutions is complete if any Pareto optimal solution is either in {a mathematical formula}P or equivalent to an element of {a mathematical formula}P. The set {a mathematical formula}P is minimal if no two partitions of {a mathematical formula}P are equivalent. The Pareto front is the projection of all the Pareto optimal solutions in the criterion space, i.e., the set of pairs {a mathematical formula}(D(Δ),S(Δ)) where Δ is a Pareto optimal solution. If {a mathematical formula}P is a complete and minimal set of Pareto optimal solutions, the set {a mathematical formula}{(D(Δ),S(Δ))|Δ∈P} is equal to the Pareto front. Fig. 2 gives an illustration of the Pareto front. A point in the Pareto front can correspond to several partitions.
      </paragraph>
      <paragraph>
       If the user specifies a function on the criteria to optimize, for example {a mathematical formula}max⁡(S/D) or {a mathematical formula}min⁡[αD−(1−α)S] with {a mathematical formula}0≤α≤1, the optimal solution will be among the Pareto optima.
      </paragraph>
      <paragraph>
       Let us consider, for instance, the example given in Fig. 1. When the number of classes is set to 3, a complete and minimal set of Pareto solutions is given in Fig. 3. If the ratio {a mathematical formula}S/D is minimized, the optimal solution is solution 5, which is the one that fits the best the intuitive groups. The user can specify conditions on the desired solutions. If for instance it is specified that points 5 and 14 must be in the same cluster, then only solutions 5 and 6 are found. If another condition is added, requiring the size of each group to be at least 2, only solution 5 is found.
      </paragraph>
      <paragraph>
       A bi-criterion clustering algorithm finding a complete and minimal set of Pareto solutions for different values of the number k of clusters is proposed in [5]. When {a mathematical formula}k=2, an exact polynomial algorithm is proposed in [12], [13]. However, to the best of our knowledge, there is no algorithm dealing with this bi-criterion, while supporting various kinds of user constraints.
      </paragraph>
     </section>
     <section label="2.3">
      <section-title>
       Constraint programming
      </section-title>
      <paragraph>
       Constraint Programming (CP) is a powerful paradigm to solve combinatorial problems, based on Artificial Intelligence or Operational Research methods. A Constraint Satisfaction Problem (CSP) is a triple {a mathematical formula}〈X,Dom,C〉 where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}X=〈x1,x2,…,xn〉 is an n-tuple of variables,
       </list-item>
       <list-item label="•">
        {a mathematical formula}Dom=〈Dom(x1),Dom(x2),…,Dom(xn)〉 is a corresponding n-tuple of domains such that {a mathematical formula}xi∈Dom(xi),
       </list-item>
       <list-item label="•">
        {a mathematical formula}C=〈C1,C2,…,Ct〉 is a t-tuple of constraints where each constraint {a mathematical formula}Ci expresses a condition on a subset of X.
       </list-item>
      </list>
      <paragraph>
       A solution of a CSP is a complete assignment of values from {a mathematical formula}Dom(xi) to each variable {a mathematical formula}xi that satisfies all the constraints of C. A Constraint Optimization Problem (COP) is a CSP with an objective function to be optimized. An optimal solution of a COP is a solution of the CSP that optimizes the objective function. In general, solving a CSP is NP-Hard. Nevertheless, the methods used by the solvers enable to efficiently solve a large number of real applications. They rely on constraint propagation and search strategies.
      </paragraph>
      <paragraph label="Example 2.1">
       Constraint propagation of a constraint c reduces the domain of the variables of c, by removing some or all inconsistent values, i.e., values that cannot be part of a solution of c. A set of propagators is associated to each constraint, it depends on the kind of consistency required for this constraint. If arc consistency is required, the propagators remove all the inconsistent values in each domain. If bound consistency is required, the propagators modify only the bounds of the domains. The type of consistency is chosen by the programmer when the constraint is defined. Different kinds of constraints are available for the programmer; they can be elementary constraints expressing arithmetic or logic relations, or global constraints expressing meaningful n-ary relations. One of the best known global constraints is the constraint alldifferent{a mathematical formula}(x1,…,xn), which imposes the variables {a mathematical formula}xi to be pairwise different. Global constraints benefit from efficient propagation, performed by a filtering algorithm exploiting results from other domains as for instance graph theory. From a logical point of view, a global constraint is equivalent to a conjunction of elementary constraints, e.g. the constraint alldifferent{a mathematical formula}(x1,x2,x3) is equivalent to the conjunction of binary constraints {a mathematical formula}x1≠x2∧x1≠x3∧x2≠x3. The interesting point is that a global constraint with its filtering algorithm has much more powerful propagation than the set of propagators of the elementary constraints. Different global constraints are developed, each one aims at exploiting more efficiently an n-ary relation. Filtering algorithms for global constraints use operational research techniques or graph theory to achieve generalized arc consistency or bound consistency with low complexity. A catalog of global constraints with more than 400 inventoried global constraints is maintained in [14]. Let {a mathematical formula}X={x1,x2,x3} with {a mathematical formula}Dom(xi)={1,2}. Let {a mathematical formula}P1 be a CSP defined on X by the constraints:{a mathematical formula} The arc consistency for each individual constraint {a mathematical formula}xi≠xj cannot remove any value from the domains {a mathematical formula}Dom(xi) and {a mathematical formula}Dom(xj), since each value is part of a solution ({a mathematical formula}xi=1,xj=2 and {a mathematical formula}xi=2,xj=1). The CSP {a mathematical formula}P1 is however inconsistent, there is no solution that satisfies all the constraints, but the propagation of individual constraints cannot detect it. Let {a mathematical formula}P2 be the CSP defined on X by the single constraint alldifferent{a mathematical formula}(x1,x2,x3). The filtering algorithm for this constraint [15] maintains the bipartite graph {a mathematical formula}G=(V,E), with {a mathematical formula}V={x1,x2,x3}∪{1,2} and {a mathematical formula}E={(xi,v)|v∈Dom(xi)}. This bipartite graph, which is also called the value graph of X, is given in Fig. 4. A matching {a mathematical formula}M⊆E is a set of disjoint edges, i.e. two edges in M cannot share a vertex. Two important observations on the relationship between the constraint alldifferent{a mathematical formula}(x1,…,xn) and matching are introduced in [15]:
      </paragraph>
      <list>
       <list-item label="•">
        There is a matching of cardinality n if and only if the constraint alldifferent{a mathematical formula}(x1,…,xn) is satisfiable.
       </list-item>
       <list-item label="•">
        An edge {a mathematical formula}(xi,v) belongs to a matching of cardinality n if and only if the value v is consistent with the constraint.
       </list-item>
      </list>
      <paragraph>
       In a CP solver, two steps, constraint propagation and branching, are repeated until a solution is found. Constraints are propagated until a stable state, in which the domains of the variables are reduced as much as possible. If the domains of all the variables are reduced to singletons then a solution is found. If the domain of a variable becomes empty, then there exists no solution with the current partial assignment and the solver backtracks. In the other cases, the solver chooses a variable whose domain is not reduced to a singleton and splits its domain into different parts, thus leading to new branches in the search tree. The solver then explores each branch, activating constraint propagation since the domain of a variable has been modified.
      </paragraph>
      <paragraph>
       The search strategy can be determined by the programmer. If a depth-first strategy is used, the solver orders branches following the order given by the programmer and explores in depth each branch. For a constraint optimization problem, a branch-and-bound strategy can be integrated to a depth-first search: each time a solution, i.e. a complete assignment of variables satisfying the constraints, is found, the value of the objective function for this solution is computed and a new constraint is added, expressing that a new solution must be better than this one. Assume that the objective function is represented by a variable y, which is to be minimized. When a solution to the problem is found, its corresponding objective value f is computed and the constraint {a mathematical formula}y&lt;f is added. This implies that only the first best solution found is returned by the solver. The solver performs a complete search, pruning only branches that cannot lead to a solution and therefore finds an optimal solution. The choice of variables and of values at each branching is very important, since it may drastically reduce the search space and therefore computation time.
      </paragraph>
      <paragraph>
       In the context of constraint optimization problems, an optimization constraint is a global constraint that is linked to the objective function. Each solution induces a “cost” and the global constraint exploits this cost to filter not only the variable which represents the objective function, but also other decision variables inside the constraint. The first filtering algorithm for this kind of global constraints has been proposed in [16]. A well-known example of extension of global constraints to optimization constraints is the constraint cost_gcc[17], which extends the Global Cardinality Constraint with cost. For more details on global constraints, search and more generally on CP, we refer the reader to [18].
      </paragraph>
      <paragraph label="Example 2.2">
       Let us illustrate by a simple COP: find an assignment of letters to digits such that {a mathematical formula}SEND+MOST=MONEY, and maximizing MONEY. This problem can be modeled by a COP with eight variables {a mathematical formula}S,E,N,D,M,O,T,Y, having as domain the set of digits {a mathematical formula}{0,…,9} and a variable V of domain integer, which represents the objective function, which is to be maximized. Constraints for this problem are:
       <list>
        the first digits must be different from 0: {a mathematical formula}S≠0,M≠0,the values of the letters are pairwise different: alldifferent{a mathematical formula}(S,E,N,D,M,O,T,Y),{a mathematical formula}(1000S+100E+10N+D)+(1000M+100O+10S+T)=10000M+1000O+100N+10E+Y,{a mathematical formula}V=10000M+1000O+100N+10E+Y.Strategies specifying the way branching is performed are very important. When variables are chosen in the order
       </list>
       <paragraph>
        {a mathematical formula}S,E,N,D,M,O,T,Y and when values are chosen following an increasing order, the search tree is composed of 29 nodes and 7 intermediary solutions (solutions satisfying all the constraints, better than the previous ones found but not optimal). When variables are chosen in the order {a mathematical formula}S,T,Y,N,D,E,M,O, the search tree has only 13 nodes and 2 intermediary solutions. Fig. 5 presents the two corresponding search trees, which are generated by the Gist environment of the Gecode solver [19]. In these search trees, a blue circle represents a stable state but not yet a solution, a red square a fail state (there is no solution), a green diamond is an intermediary solution and the orange diamond (the last diamond) is the optimal solution.
       </paragraph>
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Due to the hardness of the clustering problem, there are few exact algorithms in the literature, and the algorithms used are often heuristic, metaheuristic or approximation algorithms. Finding a partition maximizing the split between clusters is a polynomial problem [5] but it becomes NP-Hard with user constraints such as cannot-link constraints [20]. Concerning the minimization of the maximal diameter, the problem is polynomial for {a mathematical formula}k=2, but it becomes NP-Hard when {a mathematical formula}k≥3[21]. An exact algorithm based on graph coloring is proposed in [21]. Graph coloring is used to check if a distance between two objects can be the maximal diameter. Another exact approach uses a branch-and-bound search [4]. The algorithm uses a hierarchical algorithm to find a good bound and a reordering point strategy to reduce the search space. For the criterion of minimizing the within-cluster sum of dissimilarities, a repetitive branch-and-bound algorithm is presented in [4]. To our knowledge, there is no exact algorithm that supports user constraints with any of those criteria with {a mathematical formula}k&gt;2.
     </paragraph>
     <paragraph>
      For the split-diameter bi-criterion optimization without user constraints, an algorithm finding a complete and minimal set of Pareto optimal solutions, which are partitions with at most {a mathematical formula}kmax clusters, is proposed in [5]. It is proved that for n points, regardless of the number of clusters k, regardless of the partition, the split value can be found among the edges of the minimum weight spanning tree which is constructed from the matrix of dissimilarities between objects. These values are ordered decreasingly and the split s will take value in this order. On the other hand, the diameter value is one of the dissimilarities between two objects. All the dissimilarities are ordered decreasingly and the diameter d will take value in this order. Each couple {a mathematical formula}(s,d) is considered and in case without conflict will induce a graph. Graph coloring on the induced graph helps to find a partition with minimum number of clusters (this number is the chromatic number of the induced graph). The algorithm finds a complete and minimal set of Pareto optimal solutions. Each solution is a partition with at most {a mathematical formula}kmax clusters.
     </paragraph>
     <paragraph>
      In the case of bi-partition ({a mathematical formula}k=2), an exact polynomial algorithm to find Pareto optimal solutions is proposed in [12], [13]. For {a mathematical formula}k&gt;2, [13] also offers a 2-approximation algorithm. These two algorithms [12], [13] are both based on the principle of [5]: a spanning tree is built to find the possible values for split and graph coloring tests are used to verify if a dissimilarity can be the maximal diameter. However none of these bi-criterion cluster analysis approaches does support any kind of user constraints.
     </paragraph>
     <paragraph>
      Most of the attention in constrained clustering has been put on instance-level constraints, i.e. must-link and cannot-link constraints [22]. They were first introduced by Wagstaff [7]. Subsequently, many works have been done to extend classical algorithms for handling must-link and cannot-link constraints, as for instance an extension of COBWEB [7], of k-means [23], [24], hierarchical non-supervised clustering [25] or spectral clustering [26], [27], etc. When the constraints are tight, most of those algorithms may not find a solution that satisfies all the constraints even if such a solution exists.
     </paragraph>
     <paragraph>
      In recent years, it has been realized that many problems in Data Mining, including constrained clustering, can be solved by generic optimization tools. Recent works investigate generic frameworks such as Constraint Programming, SAT or Integer Linear Programming.
     </paragraph>
     <paragraph>
      In [28], L. De Raedt et al. present a framework in Constraint Programming for k-pattern set mining and show how it can be applied to conceptual clustering. In conceptual clustering, an intentional definition represented by a pattern is associated to each cluster. The objective is to find pairs composed of clusters and patterns, such that the elements in a cluster satisfy the pattern. Constraints are imposed on patterns and clusters. In order to find interesting solutions, some optimization criteria can be introduced. J.-P. Métivier et al. present in [29] a constraint-based language expressing queries to discover patterns in Data Mining. Conceptual clustering tasks can be expressed by queries as well as some kinds of user constraints. The language elements are translated into SAT clauses which are solved by a SAT solver.
     </paragraph>
     <paragraph>
      Davidson et al. propose a SAT framework [1] for constrained clustering, but only for problems with {a mathematical formula}k=2. Several kinds of constraints are considered: must-link, cannot-link, diameter and split constraints. The algorithm allows to obtain a global optimum with the criterion of diameter or split.
     </paragraph>
     <paragraph>
      Mueller et al. propose in [2] an approach to constrained clustering based on Integer Linear Programming. This approach takes a set of candidate clusters as input and builds a clustering by selecting a suitable subset. It allows different kinds of constraints on clusters or on the set of clusters, but no constraint on individual objects. It integrates different objective functions based on the quality of the clusters composing the clustering. The framework guarantees to find a global optimum but requires a set of candidate clusters. This condition makes the framework less applicable for clustering in general, since finding a good set of candidate clusters is a difficult task as the number of candidate clusters is exponential compared to the number of objects. This approach is experimented for conceptual clustering where candidate clusters might be generated from frequent patterns.
     </paragraph>
     <paragraph>
      Recently, Babaki et al. present in [30] an exact approach for constrained clustering with the criterion of minimizing the within-cluster sum of squares, based on Integer Linear Programming. This approach extends an exact algorithm which uses column generation [31]. It allows must-link, cannot-link and all constraints that are anti-monotone. User constraints are handled within the branch-and-bound search, used for generating new columns. This approach is experimented in [30] with small datasets containing less than 200 objects. For clustering task which maximizes the inter-cluster distances, Kotthoff et al. present in their talk [32] a Constraint Programming approach and also assert the flexibility and opportunities provided by a CP formulation.
     </paragraph>
     <paragraph>
      Other tasks of clustering are based on a similarity graph between objects. Spectral clustering is a clustering task which aims at minimizing the ratio cut criterion{sup:2}[33]. Wang et al. present in [27], [34] a flexible framework for spectral clustering. The framework integrates different kinds of constraints and allows also to specify a threshold setting a lower bound on how well the given constraints are satisfied. Zhi et al. present in [35] a framework for spectral clustering which integrates logical combinations of constraints. Logical combinations of constraints are expressed as linear equalities and inequalities so that they can be incorporated into various mathematical programming formulations for clustering.
     </paragraph>
     <paragraph>
      Multi-view spectral clustering is an extension of spectral clustering to multi-view datasets. Instead of combining different views into a single objective function, Davidson et al. propose in [36] a natural formulation that treats the problem as a multi-objective problem and solve it using Pareto optimization.
     </paragraph>
     <paragraph>
      The clustering tasks we are interested in aim at finding a partition of objects. Another clustering approach is hierarchical clustering, which aims at finding a hierarchy of partitions, that is a sequence of nested partitions. The result is a tree diagram, called a dendrogram. A framework formalizing hierarchical clustering as an Integer Linear Programming problem has recently been proposed by Gilpin et al. [37]. Gilpin et al. also propose in [38] a framework based on SAT for hierarchical constrained clustering with different types of user constraints.
     </paragraph>
     <paragraph>
      Another clustering setting is correlation clustering, which is based on a similarity graph between objects, and which aims at finding a partition that agrees as much as possible with the similarities. Berg et al. present in [39] a MaxSAT framework for constrained correlation clustering. In this framework, hard clauses are used to ensure a well-defined clustering and soft clauses are used to encode the cost function.
     </paragraph>
     <paragraph>
      In this paper, we investigate the use of Constraint Programming for constrained clustering. Constraint Programming has already been shown to be a promising approach for Data Mining through various tasks, such as itemset mining [40], [41], [42], [43], [44], skypattern mining [45] or decision tree construction [46].
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      New CP model for constrained clustering
     </section-title>
     <paragraph>
      We are given a collection of n points and a dissimilarity measure between pairs of points {a mathematical formula}i,j, denoted by {a mathematical formula}d(i,j). Without loss of generality, let us suppose that points are indexed and named by their index (1 represents the first point). The model aims at finding a partition into k clusters satisfying a set of user constraints and optimizing a given criterion.
     </paragraph>
     <paragraph>
      The model we propose is composed of a set of CP constraints. They are used to model partition requirements, the optimization criterion and different kinds of user constraints. Thus, they can be separated into three groups:
     </paragraph>
     <list>
      <list-item label="•">
       the CP constraints expressing that the result must be a partition,
      </list-item>
      <list-item label="•">
       the CP constraints expressing the user constraints,
      </list-item>
      <list-item label="•">
       the CP constraints expressing the criterion to be optimized. Please note that when no optimization criterion is given, the CP solver searches for all the partitions satisfying all the constraints.
      </list-item>
     </list>
     <paragraph>
      In a previous work [3], we have presented a CP model for this task. This model was based on a two-level representation: a set of variables for the assignment of a representative to each cluster and a set of variables for the assignment of a representative to each point. Choosing such a representation requires the number of clusters k to be fixed beforehand, since each representative is modeled by a CP variable. In this paper, we introduce a new CP model, which is based only on a set of variables for the assignment of a number (or index) of cluster to each point. As a result, the number of clusters k can be only bounded by {a mathematical formula}kmin and {a mathematical formula}kmax, where {a mathematical formula}kmin and {a mathematical formula}kmax are given by the user. In the following, we present the two models to ease the comparison. In both models, the CP constraints expressing the user constraints are similar but those that express partition requirements and optimization criteria are different. All the optimization criteria in the new model are expressed by new global constraints with a filtering algorithm. The differences between the two models are significant, since the new model has much less variables and constraints, while being more efficient than the previous model. Table 1 summarizes the differences between the two models.
     </paragraph>
     <section label="4.1">
      <section-title>
       Variables
      </section-title>
      <paragraph>
       In the first model, for each cluster {a mathematical formula}c∈[1,k], the point with the smallest index is considered as the representative point of the cluster.{sup:3} An integer variable {a mathematical formula}Ic is introduced, its value is the index of the representative point of cluster c; the domain of {a mathematical formula}Ic is therefore the set of integers {a mathematical formula}[1,n]. Let {a mathematical formula}I be the array {a mathematical formula}[I1,…,Ik]. Assigning a point to a cluster becomes assigning the point to the representative of the cluster. Therefore, for each point {a mathematical formula}i∈[1,n], an integer variable {a mathematical formula}Gi∈[1,n] is introduced: {a mathematical formula}Gi is the representative point of the cluster which contains the point i.
      </paragraph>
      <paragraph label="Example 4.1">
       Assume that we have 7 points {a mathematical formula}o1, …, {a mathematical formula}o7 and 2 clusters, the first one composed of {a mathematical formula}o1, {a mathematical formula}o2, {a mathematical formula}o4 and the second one composed of the remaining points. The points are denoted by their index ({a mathematical formula}o1 is denoted by 1, {a mathematical formula}o2 by 2 and so on). Then {a mathematical formula}I1=1 and {a mathematical formula}I2 = 3 (since 1 is the smallest index among {a mathematical formula}{1,2,4} and 3 is the smallest index among {a mathematical formula}{3,5,6,7}), {a mathematical formula}G1=G2=G4=1 (since 1 is the representative of the first cluster) and {a mathematical formula}G3=G5=G6=G7=3 (since 3 is the representative of the second cluster).
      </paragraph>
      <paragraph>
       In the new model, clusters are identified by their index, which varies from 1 to k for a partition into k clusters. To represent the assignment of points to clusters, we use integer variables {a mathematical formula}G1,…,Gn whose domain is the set of integers {a mathematical formula}[1,kmax]. An assignment {a mathematical formula}Gi=c means that the point i is put into the cluster number c.
      </paragraph>
      <paragraph>
       The domains of the variables {a mathematical formula}Gi in the two models are different, but the meaning of these variables is identical: they represent the assignment of points to clusters. Let {a mathematical formula}G denote the array {a mathematical formula}[G1,…,Gn].
      </paragraph>
      <paragraph>
       To represent each optimization criterion, in both models, a float value variable is introduced. It is named D for the diameter criterion, S for the split criterion and V for the WCSD criterion. Their domains are {a mathematical formula}Dom(D)=[mini,j⁡(d(i,j)),+∞), {a mathematical formula}Dom(S)=(−∞,maxi,j⁡(d(i,j))] and {a mathematical formula}Dom(V)=[0,+∞).
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Partition constraints
      </section-title>
      <section label="4.2.1">
       <section-title>
        First model
       </section-title>
       <paragraph>
        To express that the result must be a partition, we put the following constraints:
       </paragraph>
       <list>
        <list-item label="•">
         Each representative belongs to its cluster: for each {a mathematical formula}c∈[1,k], we put {a mathematical formula}GIc=Ic. This constraint is represented by the CP constraint element{a mathematical formula}(G,Ic,Ic). The constraint element({a mathematical formula}A,B,C) with A an array of variables and {a mathematical formula}B,C variables, sets the relation {a mathematical formula}A[B]=C.
        </list-item>
        <list-item label="•">
         Each point is assigned to a representative: for each {a mathematical formula}i∈[1,n], we need {a mathematical formula}⋁c∈[1,k](Gi=Ic). This relation can be expressed by {a mathematical formula}#{c|Ic=Gi}=1, which is represented by a CP constraint exactly{a mathematical formula}(1,I,Gi). This constraint sets the relation requiring that the value of {a mathematical formula}Gi must appear exactly once in the array {a mathematical formula}I.
        </list-item>
        <list-item label="•">
         The representative of a cluster is the point which has the minimal index in the cluster; in other words, the index i of a point is greater or equal to the index of its representative given by {a mathematical formula}Gi: for each {a mathematical formula}i∈[1,n], we put {a mathematical formula}Gi≤i.
        </list-item>
       </list>
       <paragraph>
        A set of clusters could be differently represented, depending on the order of clusters. For instance, in Example 4.1, we could have chosen {a mathematical formula}I1=3 and {a mathematical formula}I2=1, thus leading to another representation of the same set of clusters. To avoid this symmetry, the following constraints are added:
       </paragraph>
       <list>
        <list-item label="•">
         The representatives are sorted in an increasing order: {a mathematical formula}∀c&lt;c′∈[1,k],Ic&lt;Ic′.
        </list-item>
        <list-item label="•">
         The representative of the first cluster is the first point: {a mathematical formula}I1=1.
        </list-item>
       </list>
      </section>
      <section label="4.2.2">
       <section-title>
        Second model
       </section-title>
       <paragraph>
        In this model, clusters are identified by their number (index), and each variable {a mathematical formula}Gi gives the index of the cluster that contains point i. A complete assignment of the variables in {a mathematical formula}G represents a partition. However, a partition can be represented by different complete assignments of {a mathematical formula}G. For instance, given a complete assignment of {a mathematical formula}G, if we make a permutation where all the variables {a mathematical formula}Gi that have the value {a mathematical formula}c1 take the value {a mathematical formula}c2 and at the same time, all the variables {a mathematical formula}Gj having the value {a mathematical formula}c2 take the value {a mathematical formula}c1, we get a new assignment for {a mathematical formula}G, which still represents the same partition in terms of clusters. As a second example, when all the variables {a mathematical formula}Gi with value {a mathematical formula}c1 receive a value {a mathematical formula}c3 that is not yet used in an assignment of the other variables of {a mathematical formula}G, this leads to a new assignment representing a symmetric solution. Such a situation appears when building the clusters, a new created cluster can receive any value among the remaining cluster numbers.
       </paragraph>
       <paragraph>
        To break this kind of symmetries, the clusters are numbered such that the number 1 is the index of the first created cluster and a new number c, with {a mathematical formula}c&gt;1, is used if and only if the number {a mathematical formula}c−1 has been already used. A straightforward way to express this condition is by using a constraint {a mathematical formula}G1=1 and the constraints {a mathematical formula}Gi≤maxj∈[1,i−1]⁡(Gj)+1, for {a mathematical formula}i∈[2,n]. However, in order to have better interactions and propagations between these relations, a better way is to sum up these relations into one global constraint with a good filtering algorithm. The constraint precede[47] helps to achieve this:{a mathematical formula} This constraint imposes that {a mathematical formula}G1=1 and moreover, if {a mathematical formula}Gi=c with {a mathematical formula}1&lt;c≤kmax, there must exist at least an index {a mathematical formula}j&lt;i such that {a mathematical formula}Gj=c−1.
       </paragraph>
       <paragraph>
        The requirement to have at least {a mathematical formula}kmin clusters means that all the numbers among 1 and {a mathematical formula}kmin must be used in the assignment of the variables {a mathematical formula}Gi. When using the constraint precede, one only needs to require that at least one variable {a mathematical formula}Gi is equal to {a mathematical formula}kmin. This is expressed by the relation {a mathematical formula}#{i|Gi=kmin}≥1, which can be represented by the CP constraint:{a mathematical formula} Since the domain of each variable {a mathematical formula}Gi is {a mathematical formula}[1,kmax], there will be at most {a mathematical formula}kmax clusters. If the user needs exactly k clusters, all he/she has to do is to set {a mathematical formula}kmin=kmax=k.
       </paragraph>
      </section>
     </section>
     <section label="4.3">
      <section-title>
       User constraints
      </section-title>
      <paragraph>
       All popular user-defined constraints may be straightforwardly integrated. They are expressed the same way in both models, since they rely on the use of the variables in {a mathematical formula}G, which represent the assignment of points to clusters.
      </paragraph>
      <list>
       <list-item label="•">
        Minimal size α of clusters: this means that each point must be in a cluster with at least α points (including itself). For each {a mathematical formula}i∈[1,n], the assigned value of the variable {a mathematical formula}Gi must then appear at least α times in the array {a mathematical formula}G, i.e. {a mathematical formula}#{j|Gj=Gi}≥α. Therefore, for each {a mathematical formula}i∈[1,n], we put the constraint: atleast{a mathematical formula}(α,G,Gi).This constraint helps also to set a bound on the number of possible clusters. Indeed, the number of clusters cannot exceed {a mathematical formula}⌊n/α⌋. In the second model, this can be expressed by {a mathematical formula}Gi≤⌊n/α⌋, for all {a mathematical formula}i∈[1,n].
       </list-item>
       <list-item label="•">
        Maximal size β of clusters: each number {a mathematical formula}c∈[1,kmax] must appear in the array {a mathematical formula}G at most β times (this is still true for an unused value {a mathematical formula}c∈[kmin+1,kmax], since it appears 0 time), i.e. {a mathematical formula}#{i|Gi=c}≤β. Therefore, for each {a mathematical formula}c∈[1,kmax], we put the constraint: atmost{a mathematical formula}(β,G,c).
       </list-item>
       <list-item label="•">
        Minimal split δ: a δ-constraint requires that the split between two clusters must be at least δ. Therefore for each couple {a mathematical formula}i&lt;j∈[1,n] such that {a mathematical formula}d(i,j)&lt;δ, the constraint {a mathematical formula}Gi=Gj is put. The constraint {a mathematical formula}S≥δ is also put.
       </list-item>
       <list-item label="•">
        Maximal diameter γ: a diameter constraint requires that the diameter of each cluster must be at most γ. The constraint {a mathematical formula}D≤γ is put and for each couple {a mathematical formula}i&lt;j∈[1,n] such that {a mathematical formula}d(i,j)&gt;γ, we put: {a mathematical formula}Gi≠Gj.
       </list-item>
       <list-item label="•">
        Density constraint: a density constraint expresses that each point must have in its neighborhood of radius ϵ, at least m points belonging to the same cluster as itself. So for each {a mathematical formula}i∈[1,n], the set of variables corresponding to points in its ϵ-neighborhood is computed {a mathematical formula}Niϵ={Gj|d(i,j)≤ϵ} and this constraint is put: atleast{a mathematical formula}(m,Niϵ,Gi).
       </list-item>
       <list-item label="•">
        Must-link constraint: a must-link constraint on two points {a mathematical formula}i,j is expressed by: {a mathematical formula}Gi=Gj and {a mathematical formula}D≥d(i,j).
       </list-item>
       <list-item label="•">
        Cannot-link constraint: a cannot-link constraint on {a mathematical formula}i,j is expressed by: {a mathematical formula}Gi≠Gj and {a mathematical formula}S≤d(i,j).
       </list-item>
      </list>
     </section>
     <section label="4.4">
      <section-title>
       Optimization criteria
      </section-title>
      <paragraph>
       In the first model, we have proposed to model the optimization criterion by reified CP constraints.
      </paragraph>
      <list>
       <list-item label="•">
        When minimizing the maximal diameter, since D represents the maximal diameter, any two points at a distance greater than D must be in different clusters:{a mathematical formula} Since D is a variable and its value is still unknown, these relations are expressed using reified constraints.{sup:4}
       </list-item>
       <list-item label="•">
        When maximizing the minimal split between clusters, any two points at a distance less than the minimal split S must be in the same cluster:{a mathematical formula} Since S is a variable, these relations are also expressed by reified constraints.
       </list-item>
       <list-item label="•">
        When minimizing the Within-Cluster Sum of Dissimilarities (WCSD):{a mathematical formula} For this relation, we developed a global constraint wcsd{a mathematical formula}(G,V,d) with a filtering algorithm.
       </list-item>
      </list>
      <paragraph>
       When minimizing the diameter, in [3] we use heuristics provided by the algorithm FPF [6] to get a lower and an upper bound on the diameter without user constraints, and only an upper bound in the presence of user constraints. Such bounds allow to reduce the number of reified constraints that are put in the model.
      </paragraph>
      <paragraph>
       In the new model, for the diameter and split criteria, instead of using reified constraints, we develop two global constraints diameter{a mathematical formula}(G,D,d) and split{a mathematical formula}(G,S,d), which exploit the measure d and which operate on the array {a mathematical formula}G and on the variable D or S. The filtering algorithms for the three constraints diameter{a mathematical formula}(G,D,d), split{a mathematical formula}(G,S,d) and wcsd{a mathematical formula}(G,V,d) are presented in Section 5.
      </paragraph>
      <paragraph>
       If the user specifies an optimization criterion, an objective function is put in the model, which is:
      </paragraph>
      <list>
       <list-item label="•">
        minimize D in case of minimizing the maximal diameter,
       </list-item>
       <list-item label="•">
        maximize S in case of maximizing the minimal split,
       </list-item>
       <list-item label="•">
        minimize V in case of minimizing the WCSD.
       </list-item>
      </list>
      <paragraph>
       When an optimization criterion is specified, if there exist solutions that satisfy all the constraints, the solver finds a global optimal solution. If the user does not specify any optimization criterion, the solver finds all the solutions satisfying all the constraints, if some exist.
      </paragraph>
     </section>
     <section label="4.5">
      <section-title>
       Search strategy
      </section-title>
      <paragraph>
       Symmetry breaking for partition constraints in the two models is based on the indices of points, such as the constraints {a mathematical formula}Ic&lt;Ic′ for all {a mathematical formula}c&lt;c′ in the first model or the constraint precede{a mathematical formula}(G,[1,..,kmax]) in the second model. The way points are indexed is therefore really important. Points are then reordered and reindexed, so that points that are far from the others have a small index. In order to achieve this, we rely on the Furthest Point First algorithm [6]. This algorithm starts by choosing a point, marks it as the first head, links all the points to it and iterates until all points are marked. At each iteration, it chooses the point i that is the furthest to its head, marks it as a new head and links to i all the points that are closer to i than to their head.
      </paragraph>
      <paragraph>
       The search strategy in the first model is based on instantiating the variables in {a mathematical formula}I before the variables in {a mathematical formula}G. This means that cluster representatives are identified before assigning points to clusters. Variables in {a mathematical formula}I are chosen from {a mathematical formula}I1 to {a mathematical formula}Ik. Since the representative is the point with the minimal index in the cluster, values for instantiating each {a mathematical formula}Ic are chosen in an increasing order. The choice of variables and values in {a mathematical formula}G depends on the criterion. For the diameter and split criteria, a variable {a mathematical formula}Gi with the smallest remaining domain is chosen. Recall that each value in {a mathematical formula}j∈Dom(Gi) is the index of a cluster representative. All values in {a mathematical formula}Dom(Gi) are examined and the value j which corresponds to the smallest value {a mathematical formula}d(i,j) is chosen and two alternatives are created {a mathematical formula}Gi=j and {a mathematical formula}Gi≠j.
      </paragraph>
      <paragraph>
       In the new model, the search strategy is based on the choice of variables and values in {a mathematical formula}G, and depends also on the criterion. For the diameter and split criteria, at each branching point, a variable {a mathematical formula}Gi with the smallest remaining domain is chosen. Recall that each value {a mathematical formula}c∈Dom(Gi) is the number of a cluster. All values in {a mathematical formula}Dom(Gi) are examined and the number of the closest cluster to i is chosen. The distance between a point i and a cluster number c is defined as the maximal distance {a mathematical formula}d(i,j) where {a mathematical formula}Gj is already instantiated to c. If the cluster number c is empty (there is no point j such that {a mathematical formula}Gj=c), the distance between i and the cluster c is set to zero. This means that the assignment of a point to a new cluster is favored if there are unused cluster numbers. Moreover, the smallest remaining number is chosen. The closest cluster c to the point i is chosen and two alternatives are created {a mathematical formula}Gi=c and {a mathematical formula}Gi≠c.
      </paragraph>
      <paragraph>
       Concerning the WCSD criterion, a mixed strategy is used in both models. In order to have a good upper bound for the variable V, a greedy search is used to quickly find a solution. At this step, the chosen variable {a mathematical formula}Gi and value c are those such that the assignment {a mathematical formula}Gi=c increases V as little as possible. The first solution found is quite good in general. After finding the first solution, the strategy changes to a “first-fail”, which tends to detect failures quickly. In this strategy, a value {a mathematical formula}sic for each point i and each cluster c is defined as the sum of dissimilarities between i and all points j already assigned to the cluster c. At each branching point, for all points i with {a mathematical formula}Gi uninstantiated, the minimal value {a mathematical formula}si=minc∈Dom(Gi)⁡sic is computed. The variable {a mathematical formula}Gi with the largest value {a mathematical formula}si is then chosen and the value {a mathematical formula}c=arg⁡min⁡sic is chosen.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Filtering algorithms for optimization criteria
     </section-title>
     <paragraph>
      For each optimization criterion, we have developed a filtering algorithm for the global constraint, which links the variables {a mathematical formula}G representing a partition to the variable representing the objective function (D, S or V). This kind of global constraints is also called optimization constraint [18]. When a solution is found, its corresponding objective value is computed and a constraint expressing that new solutions must have a better value than this one is added. This constraint sets a new upper bound for D or V, which have to be minimized, or a new lower bound for S, which has to be maximized. By reasoning globally on the objective variable and on the variables representing a partition, more interactions between the domains of these variables can be captured and the search subspaces can be pruned before instantiating all the variables.
     </paragraph>
     <section label="5.1">
      <section-title>
       Diameter and split criteria
      </section-title>
      <paragraph>
       To represent the relations between points and the diameter or the split, we develop filtering algorithms for two global constraints diameter{a mathematical formula}(G,D,d) and split{a mathematical formula}(G,S,d), which exploit the dissimilarity measure d between any two points and which operate on the array {a mathematical formula}G and the variable D or S. The constraint diameter{a mathematical formula}(G,D,d) ensures that D is the maximal diameter of the clusters formed by the variables {a mathematical formula}G1,…,Gn. This constraint ensures:{a mathematical formula} This kind of relation can be realized by reified constraints, which were indeed used in our previous model [3]. However, a reified constraint is needed for each couple {a mathematical formula}i&lt;j, which implies that the number of reified constraints would be quadratic with respect to the number of points. By developing the constraint diameter{a mathematical formula}(G,D,d), we maintain all these relations in one constraint. The filtering algorithm is presented in Algorithm 1. In this algorithm, {a mathematical formula}Dom(D) is represented by {a mathematical formula}[D.lb,D.ub), where {a mathematical formula}D.lb is the lower bound, which initially can be the minimal dissimilarity between two points, and {a mathematical formula}D.ub is the upper bound, which can be either +∞ or the value of D in the previous solution found. The bound {a mathematical formula}D.ub is strict since in a branch-and-bound search the next solution must have D value strictly smaller than the previous one. The relation (1) is useful when the following cases happen.
      </paragraph>
      <list>
       <list-item label="•">
        The upper bound {a mathematical formula}D.ub has been changed (e.g. by a new found solution or by a diameter constraint). In this case, for each couple {a mathematical formula}i,j, if {a mathematical formula}D.ub≤d(i,j), we can conclude {a mathematical formula}D&lt;d(i,j) and by (1) we can infer {a mathematical formula}Gi≠Gj. However, the relation {a mathematical formula}Gi≠Gj is useful to filter the domain of {a mathematical formula}Gi (or the domain of {a mathematical formula}Gj) only if the variable {a mathematical formula}Gj (or {a mathematical formula}Gi, resp.) has been instantiated. Therefore, Algorithm 1 uses a stack to remember the variables {a mathematical formula}Gi that are instantiated (lines 1–4) and exploits them to filter (line 10). The lower bound {a mathematical formula}D.lb can possibly be revised (line 11).
       </list-item>
       <list-item label="•">
        Some variables {a mathematical formula}Gi have been instantiated. In this case, for each couple {a mathematical formula}i,j such that {a mathematical formula}Gi and {a mathematical formula}Gj are instantiated and have the same value, we infer {a mathematical formula}D≥d(i,j) and can revise {a mathematical formula}D.lb. The stack remembers then the variables {a mathematical formula}Gi which have just been instantiated (lines 6–7). This can lead to the revision of the lower bound {a mathematical formula}D.lb (line 11).
       </list-item>
      </list>
      <paragraph>
       Let us notice that as soon as the domain of one variable becomes empty, a failure case is detected by the solver. The worst case complexity is {a mathematical formula}O(n2). This algorithm is awaken when the upper bound of D is modified or a variable {a mathematical formula}Gi is instantiated. However, because of its complexity, it is scheduled to be effective after other constraints whose propagators are of lower complexity, as for instance constraints representing must-link or cannot-link constraints.
      </paragraph>
      <paragraph>
       The constraint split{a mathematical formula}(G,S,d), on the other hand, maintains that S is the minimal split between the clusters formed by the variables {a mathematical formula}G1,…,Gn. It ensures that:{a mathematical formula} The filtering algorithm is presented in Algorithm 2, where {a mathematical formula}Dom(S)=(S.lb,S.ub]. The lower bound {a mathematical formula}S.lb is either −∞ or the value of S in the previous solution found, since S is to be maximized. In the same manner as for the constraint diameter{a mathematical formula}(G,D,d), this algorithm is invoked if the lower bound {a mathematical formula}S.lb has been changed or some variables in {a mathematical formula}G have been instantiated. In this algorithm, if {a mathematical formula}S.lb has been changed, for each couple {a mathematical formula}i,j, if {a mathematical formula}S.lb≥d(i,j), by (2) we can infer {a mathematical formula}Gi=Gj, which is propagated by enforcing {a mathematical formula}Dom(Gi)=Dom(Gj). Otherwise, if some variables in {a mathematical formula}G have been instantiated, if {a mathematical formula}Gi≠Gj by (2) we infer {a mathematical formula}S≤d(i,j), so the upper bound of S can be changed. The worst case complexity is {a mathematical formula}O(n2).
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Within-cluster sum of dissimilarities criterion
      </section-title>
      <paragraph>
       We have developed a filtering algorithm for a new global optimization constraint wcsd{a mathematical formula}(G,V,d), which links the variable V, the array of variables {a mathematical formula}G and which exploits the dissimilarity measure d. This constraint ensures the relation:{a mathematical formula} where {a mathematical formula}Gi=Gj is 1 if {a mathematical formula}Gi and {a mathematical formula}Gj have the same value and 0 otherwise. The filtering algorithm used in the first model as well as motivations, proofs and experiments are presented in [48]. However, in [48] the algorithm is designed for the clustering task with exactly k clusters, as the case considered in the first model. We present below a revision of the algorithm for clustering tasks where the number of clusters is only bounded, as considered in the second model.
      </paragraph>
      <paragraph>
       Let us assume that we have a partial assignment of variables in {a mathematical formula}G. Let {a mathematical formula}K={i∈[1,n]|Gi is assigned} and {a mathematical formula}U={i∈[1,n]|Gi is unassigned}. We use the computation of a lower bound proposed in [49], which takes into account the unassigned variables. The sum defining V can be split into three parts {a mathematical formula}V=V1+V2+V3, where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}V1 is the sum of dissimilarities between the assigned points:{a mathematical formula}
       </list-item>
       <list-item label="•">
        {a mathematical formula}V2 is the sum of dissimilarities between the unassigned points and the assigned points:{a mathematical formula}
       </list-item>
       <list-item label="•">
        {a mathematical formula}V3 is the sum of dissimilarities between the unassigned points:{a mathematical formula}
       </list-item>
      </list>
      <paragraph>
       Since the set K is already known, the exact value of {a mathematical formula}V1 can be computed. Since the points of U have not been assigned to a cluster, the value of {a mathematical formula}V2 is unknown. However, a lower bound of {a mathematical formula}V2, denoted by {a mathematical formula}V2.lb, can be computed by the sum of the minimal contribution of all unassigned points. For each unassigned point {a mathematical formula}i∈U, each value {a mathematical formula}c∈Dom(Gi) represents an index of cluster to which point i can be assigned to. If point i is assigned to the cluster number c, it will contribute to that cluster the sum of dissimilarities between point i and all the assigned points which are in cluster c, i.e. the sum of dissimilarities {a mathematical formula}d(i,j) for all {a mathematical formula}j∈K such that {a mathematical formula}Gj=c. The minimal contribution {a mathematical formula}v2i of the point i is the minimal added amount when considering all values in {a mathematical formula}Dom(Gi), with respect to the assigned points:{a mathematical formula} A lower bound {a mathematical formula}V2.lb of {a mathematical formula}V2 can be computed by the sum of {a mathematical formula}v2i, for all {a mathematical formula}i∈U:{a mathematical formula} The exact value of {a mathematical formula}V3 is unknown too and we use a heuristic to compute a lower bound of {a mathematical formula}V3. We recall that {a mathematical formula}V3 is the sum of all {a mathematical formula}d(i,j) such that {a mathematical formula}i,j∈U and i and j are in the same cluster. Let p be the cardinality of U and let k be the cardinality of the union {a mathematical formula}∪i∈UDom(Gi). Each value of {a mathematical formula}∪i∈UDom(Gi) is the index of a possible cluster to which the points in U can be assigned. The number k is then the maximal number of clusters to which the points in U can be assigned. We can see that the minimal number of terms {a mathematical formula}d(i,j) in the sum {a mathematical formula}V3 is the minimal number of within-cluster pairwise connections, while considering all partitions of p points into at most k clusters.
      </paragraph>
      <paragraph label="Example 5.1">
       Let m be the quotient of the division of p by k and {a mathematical formula}m′ the remainder. Let {a mathematical formula}f(p,k)=(km2+2mm′−km)/2. It is proved in [48] that the total number of within-cluster pairwise connections for all clusters is greater or equal to {a mathematical formula}f(p,k). The equality is reached when {a mathematical formula}m′ clusters have {a mathematical formula}m+1 elements and {a mathematical formula}k−m′ clusters have m elements. Therefore, for the set U of unassigned points, if we order increasingly the constants {a mathematical formula}d(i,j) for all {a mathematical formula}i&lt;j∈U, a lower bound {a mathematical formula}V3, denoted by {a mathematical formula}V3.lb, is then computed by the sum of the {a mathematical formula}f(p,k) first constants in this order. Let us consider the case given in Fig. 6 with 14 points, which have to be grouped into 2 clusters. Assume that 7 points are grouped and 7 are not. The exact value of {a mathematical formula}V1 is computed by the sum of solid black lines. The lower bound {a mathematical formula}V2.lb is the sum of dash lines for each unassigned points. With 7 unassigned points, we have {a mathematical formula}p=7,k=2,m=3 and {a mathematical formula}m′=1, the minimal number of connections is {a mathematical formula}f(7,2)=9. The lower bound {a mathematical formula}V3.lb the sum of dotted lines. Theses lines are the 9 smallest lines that connect two unassigned points. The lower bound {a mathematical formula}V3.lb is heuristic since these lines do not correspond to any case where the 7 unassigned points are grouped into 2 groups. Assume that the domain of variable V is {a mathematical formula}[V.lb,V.ub) where {a mathematical formula}V.lb is the lower bound, which can initially be 0, and {a mathematical formula}V.ub is the upper bound, which can be either +∞ or the value of V in the previous solution found. The upper bound {a mathematical formula}V.ub is strict since in a branch-and-bound search the next solution must be better than the previous solution found. Given a partial assignment of variables in {a mathematical formula}G, a new lower bound of variable V is computed by:{a mathematical formula} We use this lower bound in the filtering algorithm for wcsd{a mathematical formula}(G,V,d). The algorithm is presented in Algorithm 3. The lower bound {a mathematical formula}V.lb is used for two purposes:
      </paragraph>
      <list>
       <list-item label="•">
        Detecting failure during the branch-and-bound search. A failure happens when {a mathematical formula}V.lb≥V.ub, which means that the domain of V becomes empty.
       </list-item>
       <list-item label="•">
        Filtering inconsistent values of unassigned variables. For each unassigned variable {a mathematical formula}Gi, for each value {a mathematical formula}c∈Dom(Gi), under the assumption that {a mathematical formula}Gi=c, we propose to revise the lower bound in a constant time. If the revised value is greater or equal than the upper bound {a mathematical formula}V.ub then c is inconsistent and is removed from {a mathematical formula}Dom(Gi).
       </list-item>
      </list>
      <paragraph>
       Since the constants {a mathematical formula}d(i,j) ({a mathematical formula}i,j∈U, {a mathematical formula}i&lt;j) must be ordered increasingly for the computation of {a mathematical formula}V3.lb, they are ordered once in the array ord, and at the same time the arrays px and py are constructed. For each value pos, {a mathematical formula}ord[pos] gives the value {a mathematical formula}d(i,j) in this order at position pos, and {a mathematical formula}px[pos] (or {a mathematical formula}py[pos]) gives the index i (or j, respectively) of the constant. The arrays ord, px and py are given in input of Algorithm 3. This algorithm computes arrays add and m, where {a mathematical formula}add[i,c] is the added amount if i is assigned to cluster number c ({a mathematical formula}add[i,c]=∑j∈K,Gj=cd(i,j)) and {a mathematical formula}m[i] is the minimal added amount while considering all possible assignments for i ({a mathematical formula}m[i]=minc∈Dom(Gi)⁡add[i,c]).
      </paragraph>
      <paragraph>
       Lines 1 to 26 computes the lower bound for V, based on a partial assignment of variables in {a mathematical formula}G. Lines 27 to 29 filter the domain of the uninstantiated variables {a mathematical formula}Gi as follows. For each uninstantiated variable {a mathematical formula}Gi, for each value {a mathematical formula}c∈Dom(Gi), in case of assignment of i into cluster number c, a new lower bound for {a mathematical formula}V.lb is revised into {a mathematical formula}V′.lb=V1′+V2′.lb+V3′.lb, where:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}V1′=V1+add[i,c] because point i is supposed to be assigned to cluster c, the sum of dissimilarities between instantiated points is increased by {a mathematical formula}add[i,c].
       </list-item>
       <list-item label="•">
        {a mathematical formula}V2′=V2.lb−m[i] because point i is no more unassigned, the contribution of point i in the computation of {a mathematical formula}V2.lb must be removed.
       </list-item>
       <list-item label="•">
        {a mathematical formula}V3′.lb is the sum of the first {a mathematical formula}f(|U∖{i}|,k) elements that are related to {a mathematical formula}U∖{i} in the increasingly ordered array ord. In order to revise this bound in a constant time, we actually use {a mathematical formula}V4 instead of {a mathematical formula}V3′.lb. Here, {a mathematical formula}V4 is the sum of the first {a mathematical formula}f(|U|−1,k)=f(p−1,k) elements of ord. These elements are related to U, it this therefore possible that some of them are related to i. It is evidence that {a mathematical formula}V3′.lb≥V4. The value {a mathematical formula}V4 can be computed once and independently from i and c (line 24).
       </list-item>
      </list>
      <paragraph>
       The revised lower bound, in case of assignment of point i to cluster c is:{a mathematical formula} which is greater than or equal to:{a mathematical formula} So if this last value is greater than or equal to the actual upper bound of V, point i cannot be assigned to cluster c. The value c is therefore inconsistent and is removed from {a mathematical formula}Dom(Gi). The complexity of this algorithm is {a mathematical formula}O(n2+nk)=O(n2+nkmax), since the domain of each {a mathematical formula}Gi is of size at most {a mathematical formula}kmax. Since {a mathematical formula}kmax≤n, the complexity is then {a mathematical formula}O(n2).
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Bicriterion split-diameter constrained clustering
     </section-title>
     <paragraph>
      Our CP model represents a general and declarative framework for constrained clustering, where a user can choose one among different optimization criteria and can integrate different kinds of user constraints. This flexibility offers different ways of using our framework. We show in this section how it can be applied to handle bi-criterion constrained clustering tasks.
     </paragraph>
     <paragraph>
      Let us consider a constrained clustering task with a set {a mathematical formula}C of user constraints, which is possibly empty. We aim at computing the Pareto front for this constrained clustering task with the bi-criterion {a mathematical formula}(min⁡D,max⁡S). One approach to achieve this is described in Algorithm 4; it is comparable to the ϵ-constraint approach presented in [50]. In this algorithm, optimization steps with a single criterion are iterated, each time with a condition on the value of the other criterion. The function Maximize_Split{a mathematical formula}(C) or Minimize_Diameter{a mathematical formula}(C) means the use of our model with the optimization criterion of maximizing the split or minimizing the diameter, respectively, and with the set of constraints {a mathematical formula}C. It returns an optimal solution which satisfies all the constraints in {a mathematical formula}C, if there exists one, or NULL otherwise. We prove that this algorithm computes a complete and minimal set of Pareto optimal solutions.
     </paragraph>
     <paragraph label="Proposition 6.1">
      Let{a mathematical formula}Δ1D,Δ1S,…,ΔmD,ΔmSbe the partitions visited byAlgorithm 4. We have:
     </paragraph>
     <list>
      <list-item label="1.">
       there is no partition Δ satisfying{a mathematical formula}Csuch that{a mathematical formula}D(Δ)&lt;D(Δ1D),
      </list-item>
      <list-item label="2.">
       if{a mathematical formula}ΔiD≠NULLthen{a mathematical formula}ΔiS≠NULL,
      </list-item>
      <list-item label="3.">
       for all{a mathematical formula}2≤i≤m,{a mathematical formula}S(ΔiS)&gt;S(Δi−1S),
      </list-item>
      <list-item label="4.">
       for all{a mathematical formula}1≤i≤m,{a mathematical formula}D(ΔiS)=D(ΔiD),
      </list-item>
      <list-item label="5.">
       for all{a mathematical formula}2≤i≤m,{a mathematical formula}D(ΔiD)&gt;D(Δi−1D),
      </list-item>
      <list-item label="6.">
       for all{a mathematical formula}1≤i&lt;m, there is no partition Δ satisfying{a mathematical formula}Csuch that{a mathematical formula}S(Δ)≥S(ΔiS)and{a mathematical formula}D(Δ)&lt;D(Δi+1D),
      </list-item>
      <list-item label="7.">
       for all{a mathematical formula}1≤i≤m, there is no partition Δ satisfying{a mathematical formula}Csuch that{a mathematical formula}S(Δ)&gt;S(ΔiS)and{a mathematical formula}D(Δ)=D(ΔiS).
      </list-item>
     </list>
     <paragraph label="Proof">
      <list>
       <list-item label="1.">
        Since {a mathematical formula}Δ1D is a partition that minimizes the diameter among all the partitions satisfying the user constraints {a mathematical formula}C (line 3), there exists no partition Δ satisfying {a mathematical formula}C with {a mathematical formula}D(Δ)&lt;D(Δ1D).
       </list-item>
       <list-item label="2.">
        If {a mathematical formula}ΔiD≠NULL, since {a mathematical formula}ΔiD satisfies the set {a mathematical formula}C and the condition {a mathematical formula}D≤D(ΔiD), the set of partitions satisfying {a mathematical formula}C∪{D≤D(ΔiD)} is not empty. Moreover, this set is finite since the set of all partitions is finite. There exists at least one partition satisfying these constraints and maximizing the split.
       </list-item>
       <list-item label="3.">
        Since {a mathematical formula}ΔiD is among the partitions satisfying {a mathematical formula}C∪{S&gt;S(Δi−1S)} (line 8), we have {a mathematical formula}S(ΔiD)&gt;S(Δi−1S). Since {a mathematical formula}ΔiD satisfies {a mathematical formula}C∪{D≤D(ΔiD)} and since among all the partitions satisfying {a mathematical formula}C∪{D≤D(ΔiD)}, {a mathematical formula}ΔiS is the one that maximizes the split (line 5), we have {a mathematical formula}S(ΔiS)≥S(ΔiD). Therefore {a mathematical formula}S(ΔiS)&gt;S(Δi−1S).
       </list-item>
       <list-item label="4.">
        To prove this we distinguish two cases.Case {a mathematical formula}i=1: {a mathematical formula}Δ1S satisfies {a mathematical formula}C and {a mathematical formula}D(Δ1D) is the minimal diameter of the partitions satisfying the user-constraints {a mathematical formula}C, therefore {a mathematical formula}D(Δ1S)≥D(Δ1D). {a mathematical formula}Δ1S belongs to the partitions satisfying {a mathematical formula}D≤D(Δ1D). So {a mathematical formula}D(Δ1S)=D(Δ1D).Case {a mathematical formula}i≥2: Since {a mathematical formula}ΔiS is a partition satisfying the set {a mathematical formula}C∪{D≤D(ΔiD)} (line 5), we have {a mathematical formula}D(ΔiS)≤D(ΔiD). As proven in the precedent item, {a mathematical formula}S(ΔiS)&gt;S(Δi−1S), so {a mathematical formula}ΔiS satisfies {a mathematical formula}C∪{S&gt;S(Δi−1S)}. Since {a mathematical formula}ΔiD is a partition which minimizes the diameter among all the ones satisfying {a mathematical formula}C∪{S&gt;S(Δi−1S)} (line 8), we have {a mathematical formula}D(ΔiS)≥D(ΔiD). Therefore {a mathematical formula}D(ΔiS)=D(ΔiD).
       </list-item>
       <list-item label="5.">
        For {a mathematical formula}i=2, the set of partitions satisfying {a mathematical formula}C∪{S&gt;S(Δ1S)} is a subset of the set of partitions satisfying {a mathematical formula}C. Therefore {a mathematical formula}D(Δ2D)≥D(Δ1D). For {a mathematical formula}i≥3, the set of partitions satisfying {a mathematical formula}C∪{S&gt;S(Δi−1S)} is a subset of the set of partitions satisfying {a mathematical formula}C∪{S&gt;S(Δi−2S)}, since {a mathematical formula}S(Δi−1S)&gt;S(Δi−2S). Since {a mathematical formula}ΔiD and {a mathematical formula}Δi−1D are the partitions which minimize the diameter among all the ones in these two respective sets, we have {a mathematical formula}D(ΔiD)≥D(Δi−1D).In all cases ({a mathematical formula}2≤i≤m), we have {a mathematical formula}D(ΔiD)≥D(Δi−1D). If {a mathematical formula}D(ΔiD)=D(Δi−1D), then {a mathematical formula}S(ΔiS) = {a mathematical formula}S(Δi−1S) (line 5: the same constraints entail the same set of partitions and therefore the same maximal split) which contradicts {a mathematical formula}S(ΔiS)&gt;S(Δi−1S). Therefore {a mathematical formula}D(ΔiD)&gt;D(Δi−1D).
       </list-item>
       <list-item label="6.">
        Assume that there exists a partition Δ that satisfies {a mathematical formula}C and such that {a mathematical formula}S(Δ)≥S(ΔiS) and {a mathematical formula}D(Δ)&lt;D(Δi+1D). Since {a mathematical formula}S(Δ)≥S(ΔiS) and {a mathematical formula}Δi+1D is a partition which minimizes the diameter among all those satisfying the condition {a mathematical formula}S&gt;S(ΔiS), we have {a mathematical formula}D(Δ)≥D(Δi+1D). This contradicts the fact that {a mathematical formula}D(Δ)&lt;D(Δi+1D).
       </list-item>
       <list-item label="7.">
        Assume that there exists a partition Δ satisfying {a mathematical formula}C such that {a mathematical formula}S(Δ)&gt;S(ΔiS) and {a mathematical formula}D(Δ)=D(ΔiS). By point 4, {a mathematical formula}D(Δ)=D(ΔiD), so Δ satisfies {a mathematical formula}C∪{D≤D(ΔiD)}. By line 5, {a mathematical formula}ΔiS is a partition which maximizes the split among those satisfying {a mathematical formula}C∪{D≤D(ΔiD)}, so {a mathematical formula}S(Δ)≤S(ΔiS). This contradicts the fact that {a mathematical formula}S(Δ)&gt;S(ΔiS).
       </list-item>
      </list>
      <paragraph>
       □
      </paragraph>
     </paragraph>
     <paragraph>
      Fig. 7 illustrates the positions of the solutions found by Algorithm 4, according to Proposition 6.1. The left image presents the first two steps. By point 1, there is no partition in the dark zone, except on the line {a mathematical formula}D=D(Δ1D). By point 7, there is no partition in the segment {a mathematical formula}S&gt;S(Δ1S) of the line {a mathematical formula}D=D(Δ1D). By point 5 and line 8 of Algorithm 4, the partition {a mathematical formula}Δ2D is above the dotted line (partitions in the white zone below the dotted line are dominated by {a mathematical formula}Δ1S). By point 6, there is no partition in the grey zone, except on the line {a mathematical formula}D=D(Δ2D). By point 7, there is no partition in the segment {a mathematical formula}S&gt;S(Δ2S) of the line {a mathematical formula}D=D(Δ2D). The right image presents the positions found by the whole algorithm. There exists no partition in the grey zone. A solution in the white zone is dominated by a solution {a mathematical formula}ΔiS∈P.
     </paragraph>
     <paragraph label="Proposition 6.2">
      The set{a mathematical formula}P={Δ1S,…,ΔmS}computed byAlgorithm 4is complete and minimal i.e.:
     </paragraph>
     <list>
      <list-item label="1.">
       {a mathematical formula}ΔiS({a mathematical formula}1≤i≤m) is a Pareto optimal solution,
      </list-item>
      <list-item label="2.">
       for all Pareto optimal solutions Δ satisfying{a mathematical formula}C, there exists{a mathematical formula}i∈[1,m]such that{a mathematical formula}D(Δ)={a mathematical formula}D(ΔiS)and{a mathematical formula}S(Δ)={a mathematical formula}S(ΔiS).
      </list-item>
     </list>
     <paragraph label="Proof">
      Algorithm 4 terminates since according to Proposition 6.1, {a mathematical formula}S(ΔiS)&gt;S(Δi−1S) and these values are discrete and limited by the maximal dissimilarity of pairs of points.
     </paragraph>
     <list>
      <list-item label="1.">
       We prove that for all {a mathematical formula}i∈[1,m], there exists no partition Δ satisfying {a mathematical formula}C which dominates {a mathematical formula}ΔiS, i.e. such that {a mathematical formula}D(Δ)≤D(ΔiS) and {a mathematical formula}S(Δ)&gt;S(ΔiS), or {a mathematical formula}D(Δ)&lt;D(ΔiS) and {a mathematical formula}S(Δ)≥S(ΔiS). Since {a mathematical formula}D(ΔiS)=D(ΔiD), the partition Δ must satisfy {a mathematical formula}D(Δ)≤D(ΔiD) and {a mathematical formula}S(Δ)&gt;S(ΔiS), or {a mathematical formula}D(Δ)&lt;D(ΔiD) and {a mathematical formula}S(Δ)≥S(ΔiS). The first case is impossible since {a mathematical formula}ΔiS is a partition which maximizes the split among all those satisfying the condition {a mathematical formula}D≤D(ΔiD). For the second case, if {a mathematical formula}i=1 then Δ does not exist according to point 1 of Proposition 6.1. If {a mathematical formula}i&gt;1, since {a mathematical formula}S(ΔiS)&gt;S(Δi−1S), the partition Δ must satisfy {a mathematical formula}D(Δ)&lt;D(ΔiD) and {a mathematical formula}S(Δ)&gt;S(Δi−1S). This is impossible according to point 6 of Proposition 6.1. Therefore each partition {a mathematical formula}ΔiS is Pareto optimal.
      </list-item>
      <list-item label="2.">
       Let Δ be any Pareto optimal solution, i.e. Δ is not dominated, satisfying {a mathematical formula}C.We cannot have {a mathematical formula}S(Δ)&gt;S(ΔmS), since {a mathematical formula}Δm+1D is null (Algorithm 4 terminates) and therefore there exists no partitions satisfying {a mathematical formula}C and {a mathematical formula}S(Δ)&gt;S(ΔmS). Therefore {a mathematical formula}S(Δ)≤S(ΔmS). Since {a mathematical formula}{S(ΔiS)} is strictly increasing, therefore either {a mathematical formula}S(Δ)≤S(Δ1S) or there exists {a mathematical formula}i∈[1,m−1] such that {a mathematical formula}S(ΔiS)&lt;S(Δ)≤S(Δi+1S).Considering the case where {a mathematical formula}S(Δ)≤S(Δ1S). By point 1 of Proposition 6.1, {a mathematical formula}D(Δ1D)≤D(Δ) and by point 4, {a mathematical formula}D(Δ1D)=D(Δ1S), therefore {a mathematical formula}D(Δ1S)≤D(Δ). We have either {a mathematical formula}(D(Δ),S(Δ)) = {a mathematical formula}(D(Δ1S),S(Δ1S)), or {a mathematical formula}Δ1S dominates Δ. Since Δ is not dominated, we must have {a mathematical formula}D(Δ)=D(Δ1S) and {a mathematical formula}S(Δ)=S(Δ1S).In the other case, where there exists {a mathematical formula}i∈[1,m−1] such that {a mathematical formula}S(ΔiS)&lt;S(Δ)≤S(Δi+1S). By point 6 of Proposition 6.1, we have {a mathematical formula}D(Δ)≥D(Δi+1D) and by point 4, {a mathematical formula}D(Δ)≥D(Δi+1S). We then have {a mathematical formula}S(Δi+1S)≥S(Δ) and {a mathematical formula}D(Δi+1S)≤D(Δ), therefore either {a mathematical formula}(D(Δ),S(Δ)) = {a mathematical formula}(D(Δi+1S),S(Δi+1S)), or {a mathematical formula}ΔiS dominates Δ. Since Δ is not dominated, we must have {a mathematical formula}D(Δ)=D(Δi+1S) and {a mathematical formula}S(Δ)=S(Δi+1S).
      </list-item>
     </list>
     <paragraph>
      Minimize_Diameter (resp. Maximize_Split) searches for a partition minimizing the diameter (resp. maximizing the split) among the partitions satisfying the set of constraints given as argument. Let us recall that there may exist several partitions optimizing a criterion but our model returns the first one found. Nevertheless it is later possible to apply our model with no optimization criterion but with the constraint that the diameter of the partitions must be this optimum and the algorithm will enumerate all the partitions satisfying this constraint. In this way, given an element {a mathematical formula}(Di,Si) in the Pareto front, our model without optimization criterion, but with the constraints {a mathematical formula}C∪{D=Di,S=Si}, will enumerate all the partitions Δ that satisfy {a mathematical formula}C and such that {a mathematical formula}D(Δ)=Di and {a mathematical formula}S(Δ)=Si.
     </paragraph>
     <paragraph>
      Multi-objective optimization in Constraint Programming in only one phase of search is proposed in [51]. The idea is to implement a global constraint {a mathematical formula}Pareto(Obj1,…,Objm,A), which keeps a set of non-dominated solutions so far computed {a mathematical formula}A and which operates on the variables representing the objective functions {a mathematical formula}Obji. This constraint reduces the domain of a variable {a mathematical formula}Obji if the domains of the other variables enter into the dominated zone of a solution in {a mathematical formula}A. A detailed description of this constraint as well as an extension with Large Neighborhood Search is proposed in [52]. This constraint Pareto can be introduced in our model. Nevertheless this approach for the moment is still much less efficient than Algorithm 4 and therefore deeper studies, as for instance a study on the search strategy, are needed in order to improve the efficiency.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      Our model is implemented in Gecode solver version 4.2.1.{sup:5} Gecode [19] is an open source Constraint Programming library in C++ and is one of the current state-of-the-art CP solvers. Twelve databases taken from the repository UCI [53] are used in our experiments. They vary on their size and their number of clusters. Table 2 summarizes information on these datasets, which are presented in increasing order of the number of objects. Since the problem we address is finding an exact solution for distance-based clustering, the important factors are the number of objects n and the number of clusters k. For the experiments, we have chosen a wide range of datasets with different values of n and k. The experiments are performed on a 3.4 GHz Intel Core i5 processor with 8G Ram running Ubuntu. All our programs are available at http://cp4clustering.com.
     </paragraph>
     <section label="7.1">
      <section-title>
       Constrained clustering with a single criterion
      </section-title>
      <section label="7.1.1">
       <section-title>
        Minimizing the maximal diameter of clusters
       </section-title>
       <section>
        <section-title>
         Performance test
        </section-title>
        <paragraph>
         We compare the performance of our previous model (denoted by CP1) and our new model (denoted by CP2), both relying on Gecode solver, with the branch-and-bound approach [4] (denoted by BaB) and the algorithm based on graph coloring [5] (denoted by GC). The program BaB has been obtained from the author's website.{sup:6} Since no implementation of the algorithm GC was available, we coded it ourselves in C++ using a well-known available graph coloring program [54]. We consider clustering without user constraints since the other algorithms cannot handle them and to our knowledge, there is no exact algorithm handling user constraints with this criterion. In the experiments, the timeout is set to 1 hour and the Euclidean distance is used to compute the dissimilarity between objects. The value of k is set to the ground truth number of clusters given in Table 2 (in the new model {a mathematical formula}kmin=kmax=k).
        </paragraph>
        <paragraph>
         Table 3 shows the results of experiments. For each dataset we present the value {a mathematical formula}Dopt (the optimal diameter) in the second column and the run-time in seconds of each system. The symbol − is used when the system cannot complete the search after 1 hour and the symbol ⁎ is used to mark that the computer runs out of memory and cannot finish the search. All the algorithms are exact and they find the same value for the optimum diameter.
        </paragraph>
        <paragraph>
         It is clear that with these datasets, our new model (CP2) is the most efficient in all cases. All twelve datasets can be solved by CP2 within one minute. Among the programs, BaB algorithm is the least efficient. It is not able to solve datasets with more than 300 objects. The performance of GC is better than that of BaB but it decreases rapidly when the number n of objects is over 500. BaB algorithm is based on the bounds of the maximal diameter to detect failures during search, while GC algorithm considers all available distances in decreasing order to find the optimum diameter. Our models, which exploits the benefits of Constraint Programming such as constraint propagation and appropriate search strategies, are more efficient.
        </paragraph>
       </section>
       <section>
        <section-title>
         Analysis of search strategy
        </section-title>
        <paragraph>
         Although our two models are based on the Constraint Programming framework, there are two main reasons that explain the significant difference in performance of the two models: the search strategy and the dedicated filtering algorithm. For analyzing the influence of the search strategy, we use our new model (CP2) with different search strategies: the strategy used in the previous model (CP1) and the one used in the new model (CP2). Fig. 8 presents the number of nodes in the search trees with these two strategies for the last six datasets given in Table 2. It is clear that the new strategy is better, since the search trees are always smaller. The new search strategy always finds quickly the first solution, the maximal diameter of which is close to the optimal diameter. As a result, the solver can remove more unfruitful branches and there are less number of nodes in the search tree.
        </paragraph>
       </section>
       <section>
        <section-title>
         Analysis of the dedicated filtering algorithm
        </section-title>
        <paragraph>
         In CP1, for modeling the diameter criterion, the number of reified constraints is at most the square of the number of points n. Although our dedicated global constraint has a complexity in the worst case of {a mathematical formula}O(n2), it considers only necessary variables whereas in CP1, at each node, every reified constraint is checked at least one time. In order to study the efficiency of the filtering algorithm, we test our new model (CP2) but using reified constraints (as in CP1) to express the diameter criterion. Table 4 presents the performances obtained when using reified constraints and when using the dedicated filtering algorithm. We can see that when using reified constraints, the solver cannot find optimal solution with the datasets Wave Form and Multi Features. The reason is that there are too many reified constraints and the computer runs out of memory. Table 4 shows that the filtering algorithm boosts the performance and this becomes more and more significant with larger datasets.
        </paragraph>
       </section>
       <section>
        <section-title>
         Analysis of bounds on the number of clusters of the new model
        </section-title>
        <paragraph>
         We evaluate the influence of the bounds on the number of clusters ({a mathematical formula}k∈[kmin,kmax]) on the performance of CP2. In the first experiment, {a mathematical formula}kmax is set to 10 and {a mathematical formula}kmin varies from 2 to 10. The diameter criterion favors a high number of clusters, since the higher the number of clusters, the smaller the value of the optimal diameter. Without user-constraints, the optimal solution with the diameter criterion has always a number of clusters equal to {a mathematical formula}kmax. For all the datasets, the total time in the search tree is constant when {a mathematical formula}kmin changes. It shows that the propagation of the constraint modeling the diameter criterion is effective. After finding and proving the optimal solution with {a mathematical formula}kmax clusters, the solver can conclude that it does not exist a better solution with less than {a mathematical formula}kmax clusters.
        </paragraph>
        <paragraph>
         In the second experiment, {a mathematical formula}kmin is set to 2 and {a mathematical formula}kmax varies from 2 to 10. Fig. 9 presents the results obtained with the datasets Vehicle, Yeast, Multi Features and Image Segmentation. For each dataset, we report the number of nodes in the search tree, when the bound {a mathematical formula}kmax varies. In general, when {a mathematical formula}kmax increases, more partitions have to be considered. However, we see an interesting trend in Fig. 9: the number of nodes in the search tree does not always increase as {a mathematical formula}kmax increases. Indeed, since {a mathematical formula}kmax is higher, the optimal maximum diameter is smaller, and the propagation of the diameter constraint is more effective. It explains why in some cases, the computation time decreases when {a mathematical formula}kmax increases.
        </paragraph>
       </section>
      </section>
      <section label="7.1.2">
       <section-title>
        Maximizing the minimal split between clusters
       </section-title>
       <paragraph>
        Finding a partition maximizing the split between clusters is a polynomial problem. However, with user constraints the problem becomes NP-Hard. To our knowledge, there is no exact algorithm for this criterion that supports any kind of user constraints for a general value {a mathematical formula}k≥3. When optimizing the split without user constraints, when the number k of clusters is not set ({a mathematical formula}kmin≤k≤kmax), the optimal solution has always a number of clusters equal to {a mathematical formula}kmin. However, this is no longer true with user constraints, as for instance with a diameter constraint. We have experimented this point with the new model by adding a diameter constraint. In order to set it, we have used the results given in Table 3 and set an upper bound on the diameter of each cluster to {a mathematical formula}1.5Dopt. The number of clusters k is not set, it is bounded between {a mathematical formula}kmin=2 and {a mathematical formula}kmax equal to the actual number of clusters given in Table 2. The results are given in Table 5. For each dataset, we present the optimal split {a mathematical formula}Sopt, the number of clusters of the solution {a mathematical formula}ksol, the actual number of clusters {a mathematical formula}kreal and the total execution time in seconds. Our model is able to solve almost all datasets, with the exception for the dataset Waveform, which is the largest dataset.
       </paragraph>
      </section>
      <section label="7.1.3">
       <section-title>
        Minimizing the within-cluster sum of dissimilarities (WCSD)
       </section-title>
       <paragraph>
        Finding an exact solution for minimizing WCSD is difficult and we compare the performance of our new model in Gecode solver with the Repetitive Branch-and-Bound Algorithm (RBBA) [4]. The program RBBA has been obtained from the author's website (http://mailer.fsu.edu/~mbrusco/). To our knowledge, it is the best exact algorithm for the WCSD criterion. The dissimilarity between objects is measured by the squared Euclidean distance. Without user constraints, both our model and the RBBA approach can only find the optimal solution with the Iris dataset. Our model needs 4125 s to complete the search whereas RBBA takes 3249 s. RBBA solves the problem by repetitively solving sub-problems: finding the optimal solution with {a mathematical formula}k+1,k+2,…,n objects. Relying on the optimal value of WCSD computed in the sub-problems, a better lower bound of WCSD can be computed, enabling RBBA to have better performance. However, extending this algorithm to integrate user constraints is difficult.
       </paragraph>
       <paragraph>
        Our model can handle different kinds of user constraints and appropriate combinations of user constraints can boost the performance. A set of 120 instance-level constraints has been generated from the dataset Iris. The constraints were generated following the method described in [7]: two points are chosen randomly from the dataset, if they belong to the same cluster in the ground truth partition, a must-link constraint is generated, otherwise a cannot-link constraint is generated. The first test is without user constraints, the second one considers the first 30 constraints, the third one takes into account the first 60 constraints and so on. Fig. 10 (left) reports the total time needed to solve the dataset with these user constraints. When there are 30 constraints, the solver takes more computation time. The reason is that, with user constraints, the optimal value of WCSD is higher and the propagation of the WCSD constraint is weaker. However, when more user constraints are integrated, the propagation of must-link and cannot-link constraints is stronger and enables to quickly instantiate variables in {a mathematical formula}G. As a result, the solver takes only 94 s for solving the problem with 60 constraints, and less than 10 s when there are 90 or more constraints.
       </paragraph>
       <paragraph>
        We have also evaluated the quality of the partitions found. For measuring the quality of a partition, we consider the Adjusted Rand Index (ARI). It measures the similarity between two partitions, in this case, the ground truth partition P of the dataset and the partition {a mathematical formula}P′ found by our model. It is defined by:{a mathematical formula} where a is the number of pairs of points that are in the same cluster in P and in {a mathematical formula}P′, b is the number of pairs of points that are in different clusters in P and in {a mathematical formula}P′, c is the number of pairs of points that are in the same cluster in P, but in different clusters in {a mathematical formula}P′ and d is the number of pairs of points that are in different clusters in P, but in the same cluster in {a mathematical formula}P′. The results of this experiment are reported in Fig. 10 (right). Since the constraints are generated from the ground truth partition of the dataset, the ARI value of the optimal partition is improved when more and more constraints are considered.
       </paragraph>
      </section>
     </section>
     <section label="7.2">
      <section-title>
       Clustering with bi-criterion split-diameter
      </section-title>
      <section label="7.2.1">
       <section-title>
        Performance test
       </section-title>
       <paragraph>
        For the split-diameter bi-criterion, we compare our new model (CP2) with the bi-criterion clustering algorithm based on graph coloring [5] (denoted bGC). Since no implementation of the algorithm was available, we have coded it in C++. To our knowledge, this is the only exact algorithm for {a mathematical formula}k∈[kmin,kmax]. The datasets given in Table 2 are used in the experiments and the timeout is set to 1 hour. The number of clusters k varies between 2 and the ground truth number of clusters. Table 6 gives the results of our experiments. The second column (#Sol) gives the number of Pareto optimal solutions found, or equivalently, the number of elements in the complete Pareto front. The following columns give the run time of each approach in seconds. The two programs are exact and they find the same Pareto front. It is clear that our model is the most efficient in most cases. It takes advantage of the efficient constraint propagation mechanism to reduce the search space. As in the case of GC, the algorithm bGC is limited to datasets with less than 500 points.
       </paragraph>
      </section>
      <section label="7.2.2">
       <section-title>
        Bi-criterion clustering with user-constraints
       </section-title>
       <paragraph>
        We have generated a set of 80 instance-level constraints from the dataset Iris, as described in Section 7.1.3 and we have applied Algorithm 4 with CP2 for solving the task of bi-criterion constrained clustering. The first test is without user constraints, the second one is with the first 20 user constraints, the third one with the first 40 constraints and so on. Fig. 11 presents the Pareto front for the five cases, using from 0 to 80 user constraints. As more and more user constraints are added, the number of feasible solutions decreases and as a result, the criterion space changes significantly. Since we have generated user constraints from the ground truth partition, it is obvious that the point {a mathematical formula}(Dr,Sr) corresponding to this partition must be in the region delimited by each Pareto front, including the one with 80 constraints. We can see that without user constraints, there are many points in the Pareto front but all of them are very far from {a mathematical formula}(Dr,Sr). For that reason, it is useful to enable user constraints for the task of bi-criterion clustering. Moreover, given an element {a mathematical formula}(Di,Si) in the Pareto front, our model can be used to enumerate all Pareto optimal solutions that have the maximum diameter {a mathematical formula}Di and the minimum split {a mathematical formula}Si. For example, considering the Pareto front in the case of 80 instance-level constraints, it is composed of two points, which correspond respectively to 8704 and 4352 partitions.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>