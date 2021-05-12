<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    New local search methods for partial MaxSAT.
   </title>
   <abstract>
    Maximum Satisfiability (MaxSAT) is the optimization version of the Satisfiability (SAT) problem. Partial Maximum Satisfiability (PMS) is a generalization of MaxSAT which involves hard and soft clauses and has important real world applications. Local search is a popular approach to solving SAT and MaxSAT and has witnessed great success in these two problems. However, unfortunately, local search algorithms for PMS do not benefit much from local search techniques for SAT and MaxSAT, mainly due to the fact that it contains both hard and soft clauses. This feature makes it more challenging to design efficient local search algorithms for PMS, which is likely the reason of the stagnation of this direction in more than one decade. In this paper, we propose a number of new ideas for local search for PMS, which mainly rely on the distinction between hard and soft clauses. The first three ideas, including weighting for hard clauses, separating hard and soft score, and a variable selection heuristic based on hard and soft score, are used to develop a local search algorithm for PMS called Dist. The fourth idea, which uses unit propagation with priority on hard unit clauses to generate the initial assignment, is used to improve Dist on industrial instances, leading to the DistUP algorithm. The effectiveness of our solvers and ideas is illustrated through experimental evaluations on all PMS benchmarks from the MaxSAT Evaluation 2014. According to our experimental results, Dist shows a significant improvement over previous local search solvers on all benchmarks. We also compare our solvers with state-of-the-art complete PMS solvers and a state-of-the-art portfolio solver, and the results show that our solvers have better performance in random and crafted instances but worse in industrial instances. The good performance of Dist has also been confirmed by the fact that Dist won all random and crafted categories of PMS and Weighted PMS in the incomplete solvers track of the MaxSAT Evaluation 2014.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <section label="1.1">
      <section-title>
       The problem
      </section-title>
      <paragraph>
       The Maximum Satisfiability problem (MaxSAT) is the optimization version of the Satisfiability problem (SAT). Given a propositional formula in the conjunctive normal form (CNF), i.e., {a mathematical formula}F=⋀i∨jlij, the task in MaxSAT is to find an assignment to the variables that maximizes the number of satisfied clauses. A significant generalization of MaxSAT is the Partial MaxSAT (PMS) problem, in which clauses are divided into hard and soft clauses and the goal is to find an assignment that satisfies all hard clauses and maximizes the number of satisfied soft clauses. PMS is particularly interesting from an algorithmic point of view because the algorithms can exploit the distinction between hard and soft constraints. Such a structural feature has a great impact on the performance of algorithms.
      </paragraph>
      <paragraph>
       Combinatorial optimization problems containing hard and soft constraints are very common in real world situations. PMS allows to encode such problems in a more natural and compact way than SAT and MaxSAT. PMS solvers has been successfully used in many fields, including network routing [31], scheduling problems [50] and timetabling problems [15]. More recent applications of PMS include FPGA routing [19], the haplotype inference by pure parsimony (HIPP) problem seeking to explain the genetic makeup of a population [20], as well as various planning problems, all of which are reviewed in a PhD thesis [18]. Some application problems, such as the optimal protein alignment problem and the HIPP problem, have been encoded into PMS and used in the MaxSAT evaluations [7].
      </paragraph>
     </section>
     <section label="1.2">
      <section-title>
       Related work
      </section-title>
      <paragraph>
       PMS (as a generalization of MaxSAT) is an NP-hard problem. Most existing practical algorithms for PMS are complete search algorithms, which prove the optimality of the solutions they find when they terminate (before reaching a time limit). There are numerous complete algorithms for solving PMS. A large family of complete algorithms for PMS employ a branch and bound algorithm strategy; they usually incorporate lower bound computation methods and utilize inference rules [35], [37], [23], [36], [17].
      </paragraph>
      <paragraph>
       In the last decade, the use of SAT solvers for solving MaxSAT problems has emerged as another paradigm. This approach is usually referred to as the SAT-based approach, and it is based on iteratively calling a SAT solver. SAT-based MaxSAT solvers can be divided into two categories: core-guided and model-guided. Core-guided algorithms refine the lower bound and guide the search with unsatisfiable subproblems (cores), while model-guided algorithms refine the upper bound and guide the search with satisfying assignments (models). Since Fu and Malik described their core-guided PMS algorithm PM1 [19], there has been much interest in this direction, and many core-guided solvers have been developed [9], [16], [33], [5], [43], [41], [40], [44], [45]. Core-guided PMS solvers are especially well known for their good performance on industrial instances. Some other approaches reduce PMS into a well-known optimization problem and use an off-the-shelf solver for such a problem. A successful example of such approaches is to reduce PMS into integer linear programs (ILP) and solve the instance by a Mixed Integer Programming (MIP) solver [3], [48].
      </paragraph>
      <paragraph>
       Although complete algorithms have shown great success in PMS solving, they may fail to find a good solution within reasonable time for large instances, as essentially they are systemic search approaches that explore the whole search space. An alternative approach to tackling the PMS problem is local search. As a popular approach to solving NP-hard combinatorial problems, local search is well known for its ability to quickly find a good-quality approximate (sometimes even optimal) solution. For combinatorial optimization problems, local search algorithms typically maintain a complete assignment for the problem, and iteratively modify the assignment (in the case of MaxSAT and PMS, this means flipping the value of a variable). An important feature of local search algorithms is that they keep track of the best assignment that was found throughout the search. This makes them anytime algorithms [55], i.e., they are expected to find better and better solutions the more time it keeps running. Therefore, efficient local search algorithms are particularly useful in real world applications where approximate solutions are acceptable while time limit is short or time resource is very important.
      </paragraph>
      <paragraph>
       Local search has been shown to be effective for solving SAT, and is among the best known methods currently available for solving certain types of SAT instances, particularly since recent progress due to several algorithms [8], [34], [10], [13]. Local search techniques for SAT can be directly applied or easily adapted to MaxSAT. Most early successful local search algorithms for SAT have been extended for approximating MaxSAT in the UBCSAT system [53], and a survey can be found in [25]. There have been also efforts devoted to specialized local search algorithms for MaxSAT, e.g., [49], [1], [54], [21]. In particular, a recent local search algorithm for weighted MaxSAT called CCLS[38] won four categories in the incomplete track of the MaxSAT Evaluation 2013, thanks to the configuration checking strategy, which was initially proposed in [11] and has shown success in SAT solving [10]. Local search algorithms for weighted MaxSAT can be used to solve PMS, as PMS can be encoded into weighted MaxSAT, by setting the weight of each soft clause as 1 and that of each hard clause as the number of soft clauses plus 1. However, local search MaxSAT solvers cannot achieve comparable performance with complete PMS solvers on structured PMS instances, as witnessed by recent MaxSAT Evaluations.
      </paragraph>
      <paragraph>
       Compared to the great success of local search for SAT and MaxSAT, there are only few studies on local search for PMS [31], [15], [50], [51], which were proposed since more than a decade. Although many local search techniques for SAT are also effective for solving MaxSAT, local search algorithms for PMS do not benefit that much from the techniques for SAT, mainly due to the fact that it contains both hard and soft clauses. To develop effective local search algorithms for PMS, it is necessary to exploit the distinction between hard and soft clauses. One of the earliest works in this line is a weighted version of WalkSAT[31], which also tackles PMS as weighted MaxSAT, but prefers to flip variables in falsified hard clauses. Afterwards, Cha et al. observed that the larger the weight differential between hard clauses and soft clauses, the slower the search is [15]. This insight has led to an algorithm in which the hard clause weight is set to a hand-tuned optimal level (rather than simply set to the number of soft clauses plus 1) [15]. This was further improved by Thornton et al. by maintaining a dynamic weight differential between hard and soft clauses [50], [51], resulting in the TWO-LEVEL algorithm. Experimental results in [50] showed the superiority of dynamic weighting strategies over the fixed weighting strategy in [15].
      </paragraph>
     </section>
     <section label="1.3">
      <section-title>
       Main contributions
      </section-title>
      <paragraph>
       In this paper, we propose a number of new ideas for local search for PMS, which mainly rely on the distinction between hard and soft clauses. Based on these ideas, we develop two local search algorithms for PMS called Dist and DistUP, the latter of which is an improved version of the former for industrial PMS instances.
      </paragraph>
      <paragraph>
       The first idea we propose is a clause weighting scheme that only works on hard clauses. Indeed, the hard clauses of a PMS instance are tackled as a SAT formula for which weighted local search algorithms are efficient [52], [46], [10]. With the diversification achieved by this weighting scheme, the algorithm tends to visit different satisfying assignments for hard clauses, and thus different groups of feasible assignments. In this way, the algorithm can better explore the space of feasible assignments, and thus is more likely to come across better feasible assignments.
      </paragraph>
      <paragraph>
       The second and more important idea is to separate hard score and soft score. Here the hard score of a variable is the change on the number (or total weight) of satisfied hard clauses caused by flipping the variable, and the soft score of a variable is the change on the number (or total weight) of satisfied soft clauses caused by flipping the variable. By separating hard score and soft score, the algorithm becomes more flexible, in the sense that it can pick the flipping variable according to either hard score or soft score, or both, according to different situations.
      </paragraph>
      <paragraph>
       The third idea is a variable selection heuristic based on hard score and soft score. The heuristic distinguishes three different situations during the search, and uses hard score and soft score in different ways under each situation.
      </paragraph>
      <paragraph>
       The three ideas mentioned above are used in developing a local search algorithm for PMS dubbed Dist, as it makes effective use of Distinctions between hard and soft clauses. Results of the MaxSAT Evaluation 2014 as well as our experiments show that Dist significantly outperforms previous local search solvers on all benchmarks from the MaxSAT Evaluation 2014, with a remarkable improvement in terms of the number of “winning” instances on structured PMS benchmarks. We also compare Dist with latest state-of-the-art complete solvers and a state-of-the-art portfolio solver on PMS benchmarks from the MaxSAT Evaluation 2014. Experimental results show that Dist outperforms the complete solvers on random and crafted benchmarks, while its performance on industrial instances is still considerably worse than complete solvers.
      </paragraph>
      <paragraph>
       The aforementioned ideas and the Dist algorithm have been presented in [12], but in this article we add more experiments and replace the complete solvers in our experiments with latest state-of-the-art ones. The following contributions are new in this article.
      </paragraph>
      <paragraph>
       In order to improve the performance of Dist on industrial PMS instances, we propose an initialization procedure called PrioUP, which utilizes unit propagation and puts priority on hard unit clauses. The procedure produces a complete assignment, which is then used as the initial assignment for the Dist solver. The resulting solver is called DistUP, and it significantly improves Dist on industrial instances, although it still cannot rival complete solvers.
      </paragraph>
      <paragraph>
       We also perform experimental analysis and additional investigations on the ideas in this work. In detail, we compare Dist with its four alternative versions, and the experimental results illustrate the effectiveness of the ideas; more interestingly, all alternatives based on separation of hard and soft score have better performance than previous local search algorithms, indicating separation of hard and soft score is an essential technique and opens up a new direction for local search algorithms for PMS (and also weighted PMS). We also study the effectiveness of the PrioUP procedure on Weighted PMS industrial instances, and provide a discussion on the initialization procedure.
      </paragraph>
     </section>
     <section label="1.4">
      <section-title>
       Structure of the paper
      </section-title>
      <paragraph>
       The remainder of this paper is organized as follows: some preliminary concepts are given in next section. We present in detail three new local search ideas for PMS in Section 3, and present the Dist algorithm in Section 4. Then we present the experimental study on Dist in Section 5. After that, we propose the PrioUP procedure, and apply it to improve Dist in Section 6, where we also present experiments on the improved algorithm DistUP and a discussion on the initialization procedure. Finally, we give some concluding remarks and directions for future research.
      </paragraph>
     </section>
    </section>
    <section label="2">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      Given a set of n Boolean variables{a mathematical formula}{x1,x2,...,xn}, a {a mathematical formula}literal is either a variable {a mathematical formula}xi (which is called a positive literal) or its negation {a mathematical formula}¬xi (which is called a negative literal). A {a mathematical formula}clause is a disjunction of literals (i.e., {a mathematical formula}Ci=ℓi1∨ℓi2∨...∨ℓij). A conjunctive normal form (CNF) formula {a mathematical formula}F=C1∧C2∧...∧Cm is a conjunction of clauses. Alternatively, clauses can be represented as sets of literals and a formula as a multiset of clauses.
     </paragraph>
     <paragraph>
      The variable to which a literal l refers is denoted by {a mathematical formula}var(l). For a literal l, its polarity, denoted by {a mathematical formula}polarity(l), is 1 if l is positive and 0 if l is negative. For a literal l, we denote by ¬l the literal of opposite polarity, and {a mathematical formula}¬¬xi=xi. A complete truth assignment is a mapping that assigns to each variable either 0 or 1. Given an assignment, a clause is satisfied if it has at least one true literal, and falsified otherwise.
     </paragraph>
     <paragraph>
      Given a CNF formula, the Partial MaxSAT (PMS) problem, in which some clauses are declared to be hard and the rest are declared to be soft, is the problem of finding an assignment such that all hard clauses are satisfied and the number of falsified (satisfied) clauses is minimized (maximized). The MaxSAT problem is a special case of PMS in which there are no hard clauses. We can also view the SAT problem as a special case of PMS in which there are no soft clauses.
     </paragraph>
     <paragraph>
      For a PMS instance F, we say a truth assignment α is feasible iff it satisfies all hard clauses in F, and the cost of a feasible assignment α, denoted by {a mathematical formula}cost(α), is defined to be the number of falsified soft clauses under α. An optimal assignment is a feasible assignment with minimum cost. The basic schema for local search algorithms for PMS (as with MaxSAT) is as follows. Starting with a complete assignment, the algorithm chooses a variable and flips it (i.e., changes its truth value) in each subsequent step, trying to find a feasible assignment with a lower cost. PMS can be encoded as weighted MaxSAT where hard clauses are associated with a weight larger than the total weight of soft clauses. A common variable property used in local search algorithms for weighted MaxSAT is the {a mathematical formula}score property, which is defined as the change on the total weight of satisfied clauses caused by flipping the variable. However, in this work, a hard (resp. soft) score is calculated only on the hard (resp. soft) clauses.
     </paragraph>
     <paragraph>
      A clause containing only one literal is a unit clause. For convenience, we use {a mathematical formula}polarity(p) to denote the polarity of the literal in the unit clause p. The process of conditioning a CNF formula F on a literal l amounts to replacing every occurrence of literal l by the constant true, replacing ¬l by the constant false, and simplifying accordingly. Based on the multi-set notation of a CNF formula, the result of conditioning a CNF formula F on a literal l is denoted by {a mathematical formula}F|l, which is defined as follows: {a mathematical formula}F|l={c∖{¬l}|c∈F,l∉c,¬l∈c}∪{c|c∈F,l∉c,¬l∉c}, and can be described succinctly as {a mathematical formula}F|l={c∖{¬l}|c∈F,l∉c}. Note that {a mathematical formula}F|l does not contain any literal l or ¬l.
     </paragraph>
     <paragraph>
      The unit propagation technique is quite simple: For a given CNF formula, we collect all unit clauses in it, and then assume that variables are set to satisfy these unit clauses. That is, if the unit clause {a mathematical formula}{xi} appears in the formula, we set {a mathematical formula}xi to true; and if the unit clause {a mathematical formula}{¬xi} appears in the formula, we set {a mathematical formula}xi to false. We then condition the formula on these settings. The iterative application of this rule until no more unit clause remains is called unit propagation (UP).
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Exploiting the distinction between hard and soft clauses
     </section-title>
     <paragraph>
      In this section, we present three new ideas for local search for PMS, which heavily rely on the distinction between hard and soft clauses. These three new ideas are 1) weighting for hard clause, 2) separating hard score and soft score, and 3) a variable selection heuristic based on hard and soft score. These ideas form the major components of the Dist algorithm.
     </paragraph>
     <section label="3.1">
      <section-title>
       Weighting for hard clauses
      </section-title>
      <paragraph>
       In this subsection, we propose a clause weighting scheme that works only on hard clauses. This is essentially different from previous local search algorithms for PMS which also utilize clause weighting schemes, as they increase weights of all falsified clauses, including both hard and soft ones [15], [50], [51].
      </paragraph>
      <paragraph>
       We now describe the weighting scheme. For each hard clause, we associate an integer number as its weight, which is initialized to 1 at the start of the algorithm.{sup:1} Whenever a “stuck” situation w.r.t. hard clauses is observed, that is, we cannot decrease the total weight of falsified hard clauses by flipping any variable, then hard clause weights are updated as follows:
      </paragraph>
      <paragraph>
       with probability sp (smoothing probability), for each satisfied hard clause whose weight is larger than one, the clause weight is decreased by one; otherwise, the clause weights of all falsified hard clauses are increased by one.
      </paragraph>
      <paragraph>
       The way that hard clause weights are updated is similar to the PAWS scheme [52], and thus we refer to this new weighting scheme as HPAWS (the hard clause version of PAWS). The only difference between PAWS and HPAWS is the condition to decrease clause weights. PAWS increases weights for falsified clauses by one in each step, and all clause weights are decreased by one after a fixed number of increases; while HPAWS employs a probability parameter to decide whether to increase weights or decrease weights in the step.
      </paragraph>
      <paragraph>
       Our weighting scheme is the first one working only on hard clauses. Some intuitive explanations behind the idea of weighting only for hard clauses are presented below.
      </paragraph>
      <paragraph>
       Why to use weighting for hard clauses: (1) Clause weighting for hard clauses helps to obtain feasible solutions. It identifies those hard clauses that are usually falsified in local optima, so that the algorithm can prefer to satisfy such hard clauses. In this way, we can avoid the situation that some hard clauses are always falsified in local optima. (2) Moreover, with the diversification achieved by the weighting scheme, the algorithm tends to visit different satisfying assignments for hard clauses, and thus different groups of feasible assignments. In this way, the algorithm can better explore the space of feasible assignments, and thus is more likely to come across better feasible assignments. In summary, using weighting for hard clauses is inspired by the success of weighting techniques for SAT [27], [52], [46], [10].
      </paragraph>
      <paragraph>
       Why not to use weighting for soft clauses: Some soft clauses might be usually falsified in local optima, due to the high cost of satisfying them, i.e., making more clauses falsified. Indeed, as is usually the case, there are some soft clauses falsified under optimal assignments. However, the object of PMS is to satisfy as many soft clauses as possible rather than all of them, under the constraint that all hard clauses are satisfied. Therefore, our opinion is that compelling the algorithm to satisfy “difficult” soft clauses at the price of falsifying more soft clauses has no clear benefits, and would mislead the algorithm towards feasible solutions with more falsified soft clauses.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Separating hard score and soft score
      </section-title>
      <paragraph>
       Most local search algorithms for SAT and MaxSAT problems utilize the variable property {a mathematical formula}score, which measures the increase of the number (or total weight) of satisfied clauses caused by flipping a variable x. Previous local search algorithms for PMS also utilize the {a mathematical formula}score property to pick variables. In this work, however, we propose to separate hard score and soft score, which allows us to make better use of the special structure of PMS and thus design more efficient local search algorithms for PMS.
      </paragraph>
      <paragraph>
       The concepts of hard score and soft score are formally defined as follows:
      </paragraph>
      <paragraph label="Definition 1">
       (hard score) The hard score of a variable x, denoted by {a mathematical formula}hscore(x), is the increase of the number (or total weight) of satisfied hard clauses caused by flipping x.
      </paragraph>
      <paragraph>
       For convenience, we say a variable x is a 0-{a mathematical formula}hscore variable if and only if {a mathematical formula}hscore(x)=0.
      </paragraph>
      <paragraph label="Definition 2">
       (soft score) The soft score of a variable x, denoted by {a mathematical formula}sscore(x), is the increase of the number (or total weight) of satisfied soft clauses by flipping x.
      </paragraph>
      <paragraph>
       Dist adopts the weighted version of hard score, as it employs a clause weighting scheme for hard clauses. Dist adopts the unweighted version of soft score for PMS instances, and the weighted version of soft score for Weighted PMS instances.
      </paragraph>
      <paragraph>
       To facilitate our discussions about Dist afterwards, we give more definitions here. In local search algorithms for SAT and MaxSAT, a variable is said to be decreasing (which means its flip would decrease the cost of the assignment) if its score is positive, and increasing if its score is negative. Now, we extend the notion of decreasing variables to hard score and soft score.
      </paragraph>
      <paragraph label="Definition 3">
       For a variable x, x is hard-decreasing iff {a mathematical formula}hscore(x)&gt;0, and is soft-decreasing iff {a mathematical formula}sscore(x)&gt;0.
      </paragraph>
      <paragraph>
       Previous local search algorithms for PMS utilize the score property, which can be seen as a weighted sum of hard score and soft score in the form of {a mathematical formula}A⋅hscore(x)+sscore(x), where A is a positive integer number. Intuitively, because hard clauses are compelled to be satisfied, the factor A should be set very large (as an extreme case, A is set to the number of soft clauses plus one). On the other hand, the search would be quite restricted if A is too large. Hence, the main concern in previous local search algorithms for PMS is how to control the value of A to make the search more effective [15], [50], [51].
      </paragraph>
      <paragraph>
       However, no matter what strategies they use, these algorithms set A to be a relatively large number so that hard clauses are more important than soft ones. Therefore, when using a heuristic preferring variables with greater scores, it is likely that those variables with greater hscores are actually picked. This is, in our opinion, a drawback of previous local search algorithms for PMS. We provide an informal explanation for this drawback as follows. Generally speaking, such local search algorithms focus on finding feasible solutions. It is difficult for them to leave an area of a cluster of feasible solutions, as there are infeasible solutions between two clusters of feasible solutions. Thus, the search space they explore would be quite limited.
      </paragraph>
      <paragraph>
       In contrast to previous local search algorithms, we propose to separate hard score and soft score. This makes the algorithm more flexible, in the sense that it can pick the flipping variable according to either hard score or soft score, or both, according to different situations.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Variable selection based on hard and soft scores
      </section-title>
      <paragraph>
       Based on the separation of hard and soft scores, we propose a variable selection heuristic for PMS that works in three levels. The scenario that the search faces varies considerably, and we divide them into three situations. The variable to be flipped is picked according to different scoring functions under each situation as follows:
      </paragraph>
      <list>
       <list-item label="1.">
        There exist hard-decreasing variables. Flipping such variables will decrease the total weight of falsified hard clauses, and hence lead the search to feasible solutions. As the preliminary goal of PMS is to find a feasible solution, such variables are given the highest priority of being flipped.However, there is still one question that needs to be answered: when there is more than one hard-decreasing variables, which one should be selected? Two natural answers are to pick the best one or to pick one uniformly at random. It is difficult to decide which variable is the best, unless there is some variable whose {a mathematical formula}hscore and {a mathematical formula}sscore are both the greatest, which rarely happens. On the other hand, picking a variable at random uniformly is too diversifying in most cases. In our algorithm, we employ a balanced strategy called Best from Multiple Selections (BMS) [14], which chooses t variables (t is an integer parameter) randomly with replacement from the set of hard-decreasing variables and returns the one with the greatest {a mathematical formula}hscore, breaking ties by preferring the one with the greatest {a mathematical formula}sscore.
       </list-item>
       <list-item label="2.">
        There are no hard-decreasing variables, yet there are variables with {a mathematical formula}hscore of 0. In this case, we further consider those 0-{a mathematical formula}hscore variables with positive {a mathematical formula}sscore, as flipping such variables would decrease falsified soft clauses without breaking more hard clauses. Therefore, flipping such variables is of clear benefit, especially when no hard-decreasing variables exist. Specifically, a variable with the best positive {a mathematical formula}sscore is selected uniformly at random, which seems a fastest way towards the goal of PMS under this situation.
       </list-item>
       <list-item label="3.">
        There are neither hard-decreasing variables nor 0-{a mathematical formula}hscore soft-decreasing variables. This means the search gets stuck, as no improving flip is available. In this case, the weights of hard clauses are updated, and then a variable is picked from a falsified clause. Since hard clauses are compelled to be satisfied, we select a random falsified hard clause if any, and otherwise a random falsified soft clause is selected (this strategy has been used in [31]).A question is then which variable should be chosen from the selected clause. Since before the stuck situation occurs we mainly focus on satisfying hard clauses or at least protecting them, here we need to diversify the search w.r.t. variables' {a mathematical formula}hscores. A good heuristic is to pick the variable with the greatest {a mathematical formula}sscore, which is independent of the variables' {a mathematical formula}hscores, while at the same time helps to satisfy as many soft clauses as possible.
       </list-item>
      </list>
      <paragraph>
       Note that, the early version of Dist [12] did not use the BMS strategy. In MaxSAT Evaluation 2014, we adopted the version described in this paper, except small modification for random benchmarks (the performance is similar).
      </paragraph>
     </section>
    </section>
    <section label="4">
     The {a mathematical formula}Dist algorithm
     <paragraph>
      Based on the ideas from the preceding section, we develop an efficient local search algorithm for solving PMS, which is called Dist, as it makes effective use of the Distinctions between hard and soft clauses.
     </paragraph>
     <section label="4.1">
      Description of Dist
      <paragraph>
       The Dist algorithm is outlined in Algorithm 1:
      </paragraph>
      <paragraph>
       In the beginning, Dist generates a complete assignment α randomly, and the cost of the best feasible solution, denoted by {a mathematical formula}cost⁎, is initialized to +∞. After the initialization, a loop (lines 3–17) is executed to modify α until a given time limit is reached. During the search, whenever a better feasible solution is found, the best feasible solution {a mathematical formula}α⁎, and {a mathematical formula}cost⁎, are updated accordingly (lines 4–5).
      </paragraph>
      <paragraph>
       In each iteration, Dist flips a variable, which is selected according to the variable selection heuristic mentioned in the previous section. First, if the set of hard-decreasing variables H is not empty, Dist picks a hard-decreasing variable with the greatest {a mathematical formula}hscore from t samples with replacement from H, breaking ties by preferring the one with the greatest {a mathematical formula}sscore (lines 6–8). If no hard-decreasing variable exists, then Dist picks a best variable (w.r.t. {a mathematical formula}sscore) from the set S of variables with 0-{a mathematical formula}hscore and positive {a mathematical formula}sscore, breaking ties randomly (lines 9–10). If both H and S sets are empty, which means the algorithm gets stuck, then Dist updates hard clause weights according to the HPAWS weighting scheme described in the preceding section (line 12), and picks a variable from a falsified clause. Specifically, it chooses a clause randomly from falsified hard clauses if any, and from falsified soft clauses otherwise (lines 13–14). In order to make the algorithm more robust, we employ a random walk with a small probability in each random step (line 15), as suggested in [26]; Otherwise, the variable with the greatest {a mathematical formula}sscore from the chosen falsified clause is selected (line 16).
      </paragraph>
      <paragraph>
       Finally, when the loop terminates upon reaching the time limit, Dist reports {a mathematical formula}cost⁎ and the best feasible solution {a mathematical formula}α⁎ that has been found, if {a mathematical formula}cost⁎ is not greater than the number of soft clauses (this means a feasible solution is found, since {a mathematical formula}cost⁎ is initialized as +∞ and is updated only when a better feasible solution is found). Otherwise, Dist reports “no feasible assignment found”.
      </paragraph>
     </section>
    </section>
    <section label="5">
     Experimental evaluation of {a mathematical formula}Dist
     <paragraph>
      We empirically evaluate Dist on PMS benchmarks from the MaxSAT Evaluation 2014, including all the three categories namely random, crafted and industrial. We compare Dist with state-of-the-art local search solvers and the best complete solvers for each benchmark, as well as a state-of-the-art portfolio solver. Finally, we empirically analyze the effectiveness of the underlying ideas in Dist.
     </paragraph>
     <section label="5.1">
      <section-title>
       Parameter setting and experiment setup
      </section-title>
      <paragraph>
       Dist is implemented in C++ and complied using g++ with the ‘-O3’ option. There are three parameters in Dist, namely the t parameter for the “Best from Multiple Selections” strategy, wp for random walk, and sp for the weighting scheme. Parameter settings have important impact on the performance of heuristic algorithms. To tune parameters automatically, some automatic configuration tools [29], [30] have been developed and have shown their power on solving SAT and mixed integer programming. In this work, we utilized a powerful automatic configuration tool called SMAC (Sequential Model-based Algorithm Configuration) [30] to tune the parameter settings for our Dist algorithm. The parameter settings suggested by SMAC are as follows:
      </paragraph>
      <list>
       <list-item label="•">
        For random benchmark: {a mathematical formula}t=3, {a mathematical formula}wp=0.1, {a mathematical formula}sp=0.01;
       </list-item>
       <list-item label="•">
        For crafted benchmark: {a mathematical formula}t=17, {a mathematical formula}wp=0.105, {a mathematical formula}sp=0.013;
       </list-item>
       <list-item label="•">
        For industrial benchmark: {a mathematical formula}t=42, {a mathematical formula}wp=0.091, {a mathematical formula}sp=0.00003.
       </list-item>
      </list>
      <paragraph>
       As for the optimal setting of parameters, we observed that there were two outlier instance families namely “maxclique/structured” and “reversi”, both from the crafted benchmark. We found that, the optimal value of t for “maxclique/structured” and the optimal value of sp for “reversi” instances tend to be much smaller than the optimal values for the rest of the crafted benchmark. And for these two families, we use SMAC to find a different setting: (2, 0.1, 0.01) for the “maxclique/structured” family, and (15, 0.1, 0.0001) for the “reversi” family.
      </paragraph>
      <paragraph>
       Our experiments were conducted on a workstation using an Intel(R) Core(TM) i7-2640M CPU with 2.8 GHz, 4 MB L3 cache and 16 GB RAM, running Ubuntu 12.04 Linux operation system. We follow the evaluation methodology adopted in the incomplete solver track of the MaxSAT evaluations: Each solver is executed once on each instance within a time limit which is set to 300 seconds (the same as in the incomplete solver track of the MaxSAT evaluations). In each run, the solver prints successively the best solution it has found so far. For each solver on each instance family, we report within parentheses the number of instances where the solver finds the best solution, and the mean time of doing so over such “winning” instances (not including the proving time for complete solvers). The number of instances of each family is specified in the column “#ins.”. The rules at the MaxSAT Evaluations establish that the winner is the solver which finds the best solution for the most instances and ties are broken by selecting the solver with the minimum mean time. In bold we present the best results for each family.
      </paragraph>
     </section>
     <section label="5.2">
      Comparing Dist with local search solvers
      <paragraph>
       We first compare Dist with state-of-the-art local search solvers, including those participating in the PMS categories of the incomplete track of the MaxSAT Evaluation 2014, as well as the TWO-LEVEL solver [51], which is the best specialized local search solver for PMS we can find, although it did not participate in the MaxSAT Evaluations. Most solvers participating in the PMS categories of the incomplete track are slightly modified from complete solvers, and there are only three local search solvers that participated in the PMS categories, namely Dist, CCLS and CCMPA. This is not surprising, as before Dist, there has been little progress in local search solvers for PMS.
      </paragraph>
      <paragraph>
       Results on Random PMS Benchmark:Table 1 shows the comparative results of local search solvers on the random PMS benchmark in the MaxSAT Evaluation 2014. As is clear from the table, Dist gives the best performance on all instance families. We observe that Dist is more robust and more efficient than its competitors. Dist finds the best solution for all instances very quickly (one instance has no feasible solution), while the other local search solvers fail to find the best solution for some instances. Also, the averaged run time of Dist is usually much less than that of its competitors.
      </paragraph>
      <paragraph>
       Results on Crafted PMS Benchmark: The experimental results of local search solvers on the crafted PMS benchmark are presented in Table 2. Among the 421 instances, Dist finds the best solution for 378 of them, while this number is 293, 282 and 287 for CCLS, CCMPA and TWO-LEVEL respectively. Dist gives the best performance for 7 out of 10 instance families, which clearly shows its superiority over its competitors on crafted PMS instances. In fact, for the other 3 families, Dist and the best solver for these 3 families namely CCLS have the same number of winning instances for 2 of the families (“maxclique/random” and “pseudo/miplib”). Overall, on the crafted PMS benchmark, Dist obviously has better performance than the other local search solvers, while the three competitor local search solvers (CCLS, CCMPA and TWO-LEVEL) have similar performance.
      </paragraph>
      <paragraph>
       Results on Industrial PMS Benchmark:Table 3 summarizes the experimental results of local search solvers on the industrial PMS benchmark. Dist shows dramatic improvement over the other local search solvers. We observe significant performance gap between Dist and its competitors when comparing the solution quality they find. Dist finds the best solution for 384 out of 568 instances, while this figure is only 63, 112 and 38 for CCLS, CCMPA and TWO-LEVEL respectively. This indicates a significant improvement in the solving ability of local search solvers for industrial PMS instances.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Performance variability of local search solvers
      </section-title>
      <paragraph>
       To study the performance variability between independent runs and the robustness of the local search solvers, we conduct additional experiments to execute the local search solvers 10 times with different random seeds for some selected instances from each benchmark. For each benchmark, we select five instances from different families. The results are reported in Table 4.
      </paragraph>
      <paragraph>
       Seen from the results, the performance of Dist is quite robust on these instances, and is better than that of other local search solvers, except for the frb instance where CCLS and CCMPA find better solutions. For the random instances, these local search solvers usually find the best solution steadily, and Dist does so with less run time. For crafted and industrial instances, the solutions found by Dist are always significantly better than those found by other solvers with only one exception (i.e., the frb instance).
      </paragraph>
     </section>
     <section label="5.4">
      Comparing Dist with complete solvers
      <paragraph>
       In this subsection, we compare Dist and state-of-the-art complete PMS solvers. In the following, we first introduce the complete solvers in our experiments, and then present the experiment results of comparing Dist and complete solvers on each benchmark respectively.
      </paragraph>
      <list>
       <list-item label="•">
        For the random PMS benchmark, we compare Dist with ahmaxsat[2], which won the random PMS category of the complete solvers track in the MaxSAT Evaluation 2014.
       </list-item>
       <list-item label="•">
        For the crafted and industrial PMS benchmarks, we compare Dist with three complete solvers, namely scip-maxsat[48], Open-WBO-In[41], [40] and WPM-2014-in[5], [4]. The first two solvers are the best non-portfolio solvers in the crafted and industrial PMS category of the MaxSAT Evaluation 2014 respectively.{sup:2}WPM-2014-in participated in the incomplete track and won both industrial categories of PMS and Weighted PMS, and its early versions also won several categories of the complete track in the past few evaluations [5].
       </list-item>
       <list-item label="•">
        For the industrial benchmarks, we also include the complete solver Eva500 in our experiments. As Eva500 performs a lower bound based core-guided search, it only reports one feasible solution, when it proves optimality. Thus, it is unfair to directly compare Eva with other solvers which print the better-quality solution (‘o’ line) immediately once the solver finds one. As a reference, we report the number of solved instances for Eva500 just to indicate the performance of the current state-of-the-art complete solver Eva500 on industrial PMS benchmarks.
       </list-item>
      </list>
      <paragraph>
       We note that, to make a fair comparison, the running time of complete solvers for solving a “winning” instance only includes the time to get the best found solution and does not include the time to prove it (if it is optimal). To this end, we executed the complete solvers with the runsolver software [47] to get the CPU time for each ‘o’ line, and the time for the last ‘o’ line was recorded.
      </paragraph>
      <paragraph>
       Results on Random PMS Benchmark: The results comparing Dist and ahmaxsat on random PMS instances are presented in Table 5, which clearly show that Dist performs better than the complete solver ahmaxsat on random PMS instances, in terms of the solution quality and the run time. For the instances where ahmaxsat finds the optimal solution, Dist finds the optimal solutions with much less averaged time. For the other instances (except one instance which has no feasible solution), Dist finds better solutions than ahmaxsat, and we tend to believe those solutions are optimal. Overall, the number of “winning” instance of Dist is 8 more than that of ahmaxsat.
      </paragraph>
      <paragraph>
       Results on Crafted PMS Benchmark: The experimental results comparing Dist and complete solvers on the crafted PMS benchmark are presented in Table 6. Among 421 instances, Dist finds the best solution for 368 of them, more than all the complete solvers. In detail, Dist gives the best performance for 6 out of 10 instance families. For the remaining 4 families, 2 of them are dominated by Open-WBO-In while the other 2 families are dominated by WPM-2014-in. We also note that Dist is the only local search solver that performs better than all complete solvers on crafted PMS instances, as witnessed by the results of the MaxSAT Evaluation 2014.
      </paragraph>
      <paragraph>
       Results on Industrial PMS Benchmark:Table 7 summarizes the experimental results comparing Dist and complete solvers on the industrial PMS benchmark. Overall, for these industrial instances, Dist achieves similar performance with the ILP-based solver scip-maxsat, but still cannot compete with the core-based complete solvers. Nevertheless, Dist gives the best performance for 3 instance families, namely “bcp/hipp-yRa1/simp”, “bcp/msp” and “protein_ins”.
      </paragraph>
      <paragraph>
       To sum up, when compared with complete solvers, Dist performs better on random and crafted PMS instances. But the performance of Dist is worse than core-based complete solvers on industrial instances, although it represents a significant improvement over previous local search solvers.
      </paragraph>
     </section>
     <section label="5.5">
      Comparing Dist with portfolio solver
      <paragraph>
       In this subsection, we compare Dist with a state-of-the-art portfolio solver for PMS, namely ISAC+−pms[6], which showed better performance than all non-portfolio solvers and won the crafted and industrial categories of the complete solvers track in the MaxSAT Evaluation 2014.
      </paragraph>
      <paragraph>
       As with complete solvers, the running time of ISAC+−pms for solving a “winning” instance only includes the time to get the best found solution and does not include the time to prove it (if it is optimal). To this end, we executed ISAC+−pms with the runsolver software. Originally, ISAC+−pms outputs all ‘o’ lines just before its termination. For our experiments, we modified the python script of ISAC+−pms to let ISAC+−pms output the ‘o’ line in a successive way so that we could record the correct run time for getting the best found solution (the last ‘o’ line). We also report the results for a Virtual Best Solver (that is, for each instance it hypothetically calls the best solver for the instance to solve it), to see how the performance of Dist can contribute to an expanded portfolio, under the slightly idealizing assumption that Dist could be called for all instances on which it performs better than the existing portfolio.
      </paragraph>
      <paragraph>
       The results comparing Dist with the portfolio solver ISAC+−pms are presented in Table 8. It is clear that Dist has better performance than ISAC+−pms on the random PMS benchmark, while ISAC+−pms has stronger performance on the crafted and industrial benchmarks. The results of Virtual Best Solver are better than ISAC+−pms on all the benchmarks. This indicates that including Dist into the portfolio solver would make a stronger portfolio solver on all the benchmarks.
      </paragraph>
     </section>
     <section label="5.6">
      <section-title>
       Effectiveness of the underlying ideas in Dist
      </section-title>
      <paragraph>
       In this section, we conduct further empirical analyses to study effectiveness of the key components in Dist, including the clause weighting scheme that works only for hard clauses, as well as strategies in the variable selection. We compare Dist with its four alternatives, which are modified from Dist as follows:
      </paragraph>
      <list>
       <list-item label="•">
        Dist_alt1: update clause weights for all clauses (replace line 12 in Algorithm 1). This variant is tested in order to study the effectiveness of clause weighting scheme that works only for hard clauses.
       </list-item>
       <list-item label="•">
        Dist_alt2: when hard-decreasing variables exist, pick the one with the best {a mathematical formula}hscore, breaking ties in favor of the one with the greatest {a mathematical formula}sscore (replace lines 7–8 in Algorithm 1).
       </list-item>
       <list-item label="•">
        Dist_alt3: when hard-decreasing variables exist, pick one of them uniformly at random. (replace lines 7–8 in Algorithm 1). Both Dist_alt2 and Dist_alt3 are tested in order to study the effectiveness of the BMS heuristic in choosing a hard-decreasing variable to be flipped.
       </list-item>
       <list-item label="•">
        Dist_alt4: always pick a random variable from the selected falsified clause (replace lines 15–16 in Algorithm 1). This variant is tested in order to study the effectiveness of the idea of combining random walk with a greedy strategy that chooses a variable with the greatest soft score from the selected falsified clause.
       </list-item>
      </list>
      <paragraph>
       The experimental results (Table 9) demonstrate the superiority of Dist over these variants, which indicates the effectiveness of the algorithmic components. Specifically, the comparison between Dist and Dist_alt1 indicates the effectiveness of the clause weighting scheme that works only for hard clauses; the superiority of Dist over Dist_alt2 and Dist_alt3 demonstrate the effectiveness of the BMS (Best from Multiple Selections) heuristic in choosing the hard-decreasing variable for flipping; finally, the comparison between Dist and Dist_alt4 indicates the effectiveness of the idea of combining random walk with a greedy strategy for choosing the flipping variable from the selected falsified clause.
      </paragraph>
      <paragraph>
       We also note that these degraded alternatives of Dist still exhibit significantly better performance than previous local search solvers on crafted and industrial benchmarks. This indicates that heuristics based on separated hard score and soft score are more promising for solving structured PMS instances than previous local search methods.
      </paragraph>
     </section>
    </section>
    <section label="6">
     Improving {a mathematical formula}Dist on industrial PMS instances
     <paragraph>
      The preceding section has shown the excellent performance of Dist on random and crafted PMS instances, which is better than that of state-of-the-art solvers, including both complete and incomplete (i.e. local search) solvers. However, for industrial PMS instances, although Dist significantly outperforms other local search solvers, its performance is still unsatisfactory, and there is an obvious gap between the performance of Dist and state-of-the-art complete solvers.
     </paragraph>
     <paragraph>
      In this section, we aim to improve Dist on industrial PMS instances. To this end, we propose a procedure for generating a good initial assignment for local search algorithms for PMS and utilize it to improve Dist, resulting in a new local search PMS solver called DistUP.
     </paragraph>
     <section label="6.1">
      <section-title>
       Initialization via priority unit propagation
      </section-title>
      <paragraph>
       In this subsection, we propose a procedure of generating an initial assignment for local search algorithms for PMS. The procedure employs an unit propagation (UP) technique that puts priority on hard unit clauses, and thus is named PrioUP.
      </paragraph>
      <paragraph>
       Before we present the details of the PrioUP procedure, we first introduce the key data structures. The array {a mathematical formula}value records the assigned value for each variable. For each variable x, {a mathematical formula}value(x) has 4 possible values {a mathematical formula}{−2,−1,0,1}, and their meanings are explained as below:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}value(x)=−2 means x is forbidden to be assigned. When unit clauses l and ¬l appear in F simultaneously (due to previous propagations), the corresponding variable x is forbidden to be assigned, as assigning x would cause a conflict.
       </list-item>
       <list-item label="•">
        {a mathematical formula}value(x)=−1 means x is unassigned.
       </list-item>
       <list-item label="•">
        {a mathematical formula}value(x)=0 means x is assigned with the value 0.
       </list-item>
       <list-item label="•">
        {a mathematical formula}value(x)=1 means x is assigned with the value 1.
       </list-item>
      </list>
      <paragraph>
       The queue Q is a priority queue that stores all unit clauses for propagation. In Q, hard unit clauses have higher priority than soft ones. All hard unit clauses have the same priority and are managed in an FIFO (First In First Out) manner, and so do the soft ones. Since each unit clause has only one literal, Q indeed stores those literals. Note that we avoid duplication (i.e., a literal appears more than one time) in Q, and also avoid including opposite literals in Q. This is accomplished via an auxiliary array {a mathematical formula}polarity_in_Q.
      </paragraph>
      <paragraph>
       The auxiliary array {a mathematical formula}polarity_in_Q records the information for each variable with regards to its appearance in Q. For each variable x, {a mathematical formula}polarity_in_Q(x) records whether x appears in Q, and the polarity of the literal when x appears in Q. It has 3 possible values {a mathematical formula}{−1,0,1}, as explained below:
      </paragraph>
      <list>
       <list-item label="•">
        {a mathematical formula}polarity_in_Q(x)=−1 means x does not appear in Q (we say a variable x appears in Q, if Q contains either x or ¬x).
       </list-item>
       <list-item label="•">
        {a mathematical formula}polarity_in_Q(x)=0 means the literal ¬x is in Q.
       </list-item>
       <list-item label="•">
        {a mathematical formula}polarity_in_Q(x)=1 means the literal x is in Q.
       </list-item>
      </list>
      <paragraph>
       The PrioUP procedure is outlined in Algorithm 2,
      </paragraph>
      <paragraph>
       and explained as follows. In the beginning, each variable is marked as “unassigned”, and all unit clauses in the formula F are added into the queue Q.
      </paragraph>
      <paragraph>
       While Q is not empty, the first literal (or say, unit clause) l in Q is extracted from Q and propagated. The variable corresponding to literal l is denoted as x. We know that x could not have been propagated (i.e., {a mathematical formula}value(x) could not be 0 or 1), as otherwise the formula as well as Q would not contain any literal of x. Thus, {a mathematical formula}value(x) is either −1 or −2.
      </paragraph>
      <paragraph>
       If {a mathematical formula}value(x)=−1, which means x is unassigned, then x is assigned to the value of {a mathematical formula}polarity(l) to satisfy the unit clause l, and F is conditioned on the literal l. If this process generates any new unit clause, for each such unit clause p, we do the following checking and operations if needed. Let y denote the corresponding variable of p. If neither literal p nor literal ¬p is in Q (i.e., {a mathematical formula}polarity_in_Q(y)=−1), then p is enqueued into Q, and {a mathematical formula}polarity_in_Q(y) is set to {a mathematical formula}polarity(p). Otherwise, if literal p is already in Q, we do nothing (we do not add p into Q for avoiding duplication). If literal ¬p is in Q (i.e., {a mathematical formula}polarity_in_Q(y)≠polarity(p)), then variable y is marked as “forbidden” (by setting {a mathematical formula}value(y) to −2), as p and ¬p appear in the formula simultaneously and assigning y would cause a conflict.
      </paragraph>
      <paragraph>
       If {a mathematical formula}value(x)=−2, which means x is forbidden to be propagated, we just ignore it. A principle in our unit propagation initialization procedure is to avoid generating conflicts. Thus, for variables marked as “forbidden”, we would rather leave them unassigned during the unit propagation procedure, as assigning them would cause empty clauses.
      </paragraph>
      <paragraph>
       Finally, after Q becomes empty, if there are variables unassigned, including those with {a mathematical formula}value(x)=−1 and also those with {a mathematical formula}value(x)=−2, then these variables are assigned 0 or 1 uniformly randomly.
      </paragraph>
     </section>
     <section label="6.2">
      The DistUP solver
      <paragraph>
       We apply the PrioUP procedure to improve the Dist solver, leading to the DistUP solver. This is done by modifying only a few lines of codes of Dist.
      </paragraph>
      <paragraph>
       In the following, we illustrate how to apply PrioUP to improve a local search PMS solver. To facilitate our discussions, we assume that local search algorithms allow to accept a specific assignment as its initialized assignment.{sup:3} Let us recall the general scheme of local search algorithms for PMS. Starting with a complete assignment α, a local search algorithm chooses a variable and flips it in each search step. Whenever finding a feasible assignment with a lower cost, the algorithm records it as the best found assignment. To apply the PrioUP procedure to a local search solver, we first generate a complete assignment α using PrioUP, and then execute the local search solver on the original PMS instance with α as its initial assignment. Note that the instance is modified in the PrioUP procedure, but we use the original instance for local search. That is, we do not fix the value of any variable and all variables are treated equally during the local search. In this way, variables which are assigned incorrectly by PrioUP have a chance to be corrected.
      </paragraph>
     </section>
     <section label="6.3">
      Empirical evaluations of DistUP
      <paragraph>
       In this subsection, we evaluate the performance of DistUP on industrial PMS instances from the MaxSAT Evaluation 2014. We observe that almost all these industrial PMS instances have unit clauses. Indeed, as stated in [39], most industrial MaxSAT and SAT instances have a non-negligible number of unit clauses, and researchers have pointed out the importance of such clauses. The PrioUP procedure can be considered as a step towards exploiting unit clauses in local search solvers for PMS.
      </paragraph>
      <paragraph>
       We first compare DistUP with the Dist solver from Section 4, and then compare DistUP with state-of-the-art complete solvers on industrial PMS instances. Additionally, we also compare DistUP with Dist and a state-of-the-art complete solver on industrial Weighted PMS instances from the MaxSAT Evaluation 2014. The experimental environment and protocol in this section are the same as those used in Section 5. Also note that, the run time for DistUP always includes the time for PrioUP. Indeed, PrioUP terminates in one second for all the instances in our experiments.
      </paragraph>
      <section label="6.3.1">
       Experiments of DistUP on industrial PMS instances
       <paragraph>
        The experimental results comparing Dist and DistUP on the industrial PMS benchmark are presented in Table 10, which clearly demonstrate the significant improvement of DistUP over Dist. Among the 568 industrial PMS instances, DistUP have 362 “winning” instances, compared to 287 for Dist. DistUP has better performance than Dist on 13 instance families, and has worse performance on 7 families. According to these experimental results, the performance of local search solvers on industrial PMS instances can be improved by using the PrioUP procedure to generate the initial assignment.
       </paragraph>
       <paragraph>
        We also compare DistUP with complete solvers on industrial PMS instances, and the experiment results are presented in Table 11. Although DistUP usually finds better solutions than Dist on industrial PMS instances, the solution quality returned by DistUP is still worse than complete solvers on many instances, and thus DistUP does not show an obvious increase in the number of “winning” instances. Nevertheless, DistUP does have 24 more “winning” instances than Dist when compared to the same complete solvers. Indeed, like the case for SAT, improving local search solvers on industrial benchmarks of PMS (or other MaxSAT variants) remains a big challenge. This has been emphasized in a recent paper [24]. Although DistUP cannot yet rival complete solvers on industrial benchmarks, experiments comparing DistUP with Dist and previous local search solvers show significant progress in this direction.
       </paragraph>
      </section>
      <section label="6.3.2">
       Experiments of DistUP on industrial weighted PMS instances
       <paragraph>
        In order to study the effectiveness of the PrioUP procedure on Weighted PMS industrial instances, we also compare Dist and DistUP on Weighted PMS industrial instances from the MaxSAT Evaluation 2014. We utilize the automatic configuration tool SMAC[30] to tune the parameter settings for Dist on the Weighted PMS industrial benchmark from the MaxSAT Evaluation 2014, and the suggested setting is: {a mathematical formula}t=18, {a mathematical formula}wp=0.1 and {a mathematical formula}sp=0.013. We use this parameter setting for both Dist and DistUP.
       </paragraph>
       <paragraph>
        The experimental results are summarized in Table 12, which show that DistUP obtains better solutions than Dist on most of the instances. Overall, DistUP finds a better or equal quality solution on 325 instances among the 410 instances. Specifically, DistUP performs better on 5 instance families, and worse on the other 3 families. These experimental results indicate that the PrioUP procedure is also beneficial for solving Weighted PMS in most cases.
       </paragraph>
       <paragraph>
        However, the performance of DistUP on industrial instances of Weighted PMS is still much worse than complete solvers. For example, we compared DistUP with WPM-2014-in on these Weighted PMS industrial instances, and the results (Table 13) show that the number of “winning” instances of WPM-2014-in is much more than that of DistUP. Nevertheless, we would like to note that DistUP performs much better than WPM-2014-in on one family namely “wcsp/spot5/log”. In this sense, it could be complementary to some extent to complete solvers for solving Weighted PMS industrial instances.
       </paragraph>
      </section>
     </section>
     <section label="6.4">
      Related work and discussions on PrioUP
      <paragraph>
       There is some work on improving local search algorithms by constructing effective initial solutions, most of which are studied in the context of the Most Probable Explanation (MPE) in Bayesian networks [32], [28], [42]. With regard to MaxSAT, Hains et al. transformed MaxSAT to Walsh polynomials and compute the hyperplane averages, which are then used to generate the initial assignment [21]. Their experiments on unweighted industrial MaxSAT benchmark from the MaxSAT Evaluation 2012 show that, by replacing the randomized initialization with the hyperplane-based initialization, better solutions can be obtained.
      </paragraph>
      <paragraph>
       Unit propagation preserves the satisfiability of the instance but does not preserve the number of falsified clauses for every assignment. Due to this fact, the use of UP was mainly restricted to the SAT problem, and UP was not applied to local search algorithms for MaxSAT until recently. To the best of our knowledge, there are only two studies using UP in local search algorithms for MaxSAT in the literature [22], [1], and we are not aware of any work using UP in local search algorithms for PMS. Heras and Bañeres [22] proposed several preprocessors for MaxSAT and applied them before local search algorithms. One of the preprocessors is the UP preprocessor, which iteratively performs the following operations until no more non-propagated unit clause remains: it first executes a simulation of unit propagation (i.e., the consequences are not applied to the formula) to find a conflicting clause, and then builds the corresponding refutation tree,{sup:4} and finally it applies MaxSAT resolution as indicated by the refutation tree to transform the formula. Abramé and Habet [1] integrated the UP technique into a local search algorithm, by applying UP after each flip step to dynamically build refutation trees and detect conflicts. The processing technique in [1] is similar to the one in [22], but it is used dynamically during the search process. Both of these two methods are mainly evaluated on random and crafted unweighted MaxSAT instances.
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>