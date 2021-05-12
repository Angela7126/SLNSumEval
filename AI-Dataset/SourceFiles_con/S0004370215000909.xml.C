<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Differential evolution for noisy multiobjective optimization.
   </title>
   <abstract>
    We propose an extension of multiobjective optimization realized with the differential evolution algorithm to handle the effect of noise in objective functions. The proposed extension offers three merits with respect to its traditional counterpart. First, an adaptive selection of the sample size for the periodic fitness evaluation of a trial solution based on the fitness variance in its local neighborhood is proposed. This avoids the computational complexity associated with the unnecessary reevaluation of quality solutions without disregarding the necessary evaluations for relatively poor solutions to ensure accuracy in fitness estimates. The second strategy is concerned with determining the expected value of the noisy fitness samples on the basis of their distribution, instead of their conventional averaging, as the fitness measure of the trial solutions. Finally, a new crowding-distance-induced probabilistic selection criterion is devised to promote quality solutions from the same rank candidate pool to the next generation, ensuring the population quality and diversity in the objective spaces. Computer simulations performed on a noisy version of a well-known set of 23 benchmark functions reveal that the proposed algorithm outperforms its competitors with respect to inverted generational distance, spacing, error ratio, and hypervolume ratio metrics.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The multiobjective optimization (MOO) literature has witnessed a radically different perspective in solving real-world problems using evolutionary computing methods. A MOO is concerned with mathematical optimization problems involving two or more complex, nonlinear, conflicting objectives to be optimized simultaneously. Usually, a derivative-free single-objective optimization algorithm generates new trial solutions that are biased toward the better region of the objective space, and weeds out poor solutions using a competitive selection over iterations. However, for a nontrivial MOO problem, there exists no single solution that simultaneously optimizes each objective. To jointly optimize multiple objective functions in a MOO [1], selection of trial solutions is performed by Pareto ranking, which is concerned with judiciously identifying nondominated trial solutions from the rest of the population. Pareto ranking is induced by the fitness measure of all objective functions for individual trial solutions.
     </paragraph>
     <paragraph>
      The objectives, being functions of certain variables describing a specific problem, usually return a unique value for the variables in their argument. However, in many scientific/engineering problems, it has been observed that even though the measurements of the variables remain constant, the objective functions return different values because of noise-induced dynamic variation of the objective surfaces. This class of problem is referred to as the “noisy optimization problem.” Noise creeps into the picture because of technological limitations, modeling errors, and incomplete data, leading to different results from repeated evaluations for the same set of parameter values of the objective functions. In such circumstances, a quality trial solution in a MOO may be deprived of being promoted to the next generation because of its poor (noisy) fitness estimates, while a deceptive solution with illusive good fitness may not be discarded from the current population [2], [3].
     </paragraph>
     <paragraph>
      This paper addresses the issues of uncertainty management (regarding the selection of qualitative trial solutions) in MOO in the presence of noise by incorporating the following three policies: adaptation of the sample size of a trial solution for its periodic fitness evaluation, expected fitness estimation from the measured noisy fitness samples, and crowding-distance-induced stochastic selection. First, the sample size for periodic fitness evaluation of each trial solution is adapted by means of the fitness variance in their local neighborhood. “Sampling” refers to the periodic fitness evaluation of a trial solution to diminish the risk of promoting inferior solutions in the noisy environment. It is worth mentioning that the adaptive selection of the sample size is momentous as increasing the sample size augments the quality measure of fitness at the cost of additional runtime. Here a nonlinear form (capturing the relationship between the sample size of a trial solution and the fitness variance in its local neighborhood) induced by an exponential function is regarded to efficiently balance the trade-off between runtime complexity and computational accuracy.
     </paragraph>
     <paragraph>
      Second, while measuring the fitness of a trial solution, traditional methods [4], [5], [6] refer to the average fitness of the samples. However, the average fitness presumes equal probability of occurrence of all fitness samples, and thus returns a poor fitness estimate when the noise variance (in the fitness measure of the solutions) in the local neighborhood of a selected trial solution is large. This problem is circumvented here by referring to the expected value of the fitness samples as the true fitness estimate of a trial solution. The expected fitness concerned with the occurrence probability of the fitness samples seems to give a better fitness measure of a given trial solution. We introduce a novel strategy to evaluate the expected fitness of the trial solutions from the distribution of the fitness samples in the entire sample space. In the present context, a density-based nonuniform partitioning of the fitness sample space is employed to capture the uncertainty involved in the fitness measurement of the noisy fitness samples.
     </paragraph>
     <paragraph>
      Finally, we develop a probabilistic selection (PS) policy to encapsulate the diversity as well as the quality of the nondominated trial solutions even in noisy fitness landscapes. It is observed that the deterministic selection scheme of the crowding-distance-based sorting (used for promoting trial solutions from the same rank candidate pool to the next generation), which is employed in traditional MOO algorithms, can lead to suboptimal or misleading sets of nondominated solutions in the noisy environment even when sampling is used [7]. The selection strategy here depends not only on the density of nondominated solutions surrounding an individual in the objective space, but also on the reliability of its measured fitness samples. We develop a new probabilistic measure of the reliability based on the skewness of the distribution of the fitness samples. The degree of asymmetry of the distribution of the fitness samples is captured by skewness. Consequently, it provides a unique approach for identifying the rare fitness samples lying in the tail of the distribution. These infrequent samples (far away from the expected fitness) are assumed to occur because of the creeping of noise in the fitness landscapes. The rarer the occurrence of the infrequent samples (i.e., the closer the fitness samples are to the expected value with small skewness of the distribution), the greater is the degree of credibility of the fitness estimates of a given trial solution. The trial solutions having a greater crowding distance and a high grade of reliability (assessed using the probability of occurrence of no rare samples) are given more precedence during ranking of solutions in the same front.
     </paragraph>
     <paragraph>
      The evolutionary component of the proposed noisy MOO algorithm has been realized here by the differential evolution for MOO (DEMO) [8] algorithm for its proven merits in global optimization. Some of the attractive features of DEMO justifying its selection in the design of the proposed noisy optimization algorithm include the simplicity of its structure leading to ease of coding, very few control parameters, and faster convergence [48], [49] in comparison with other MOO algorithms.
     </paragraph>
     <paragraph>
      Performance analysis of the proposed noisy optimization algorithm realized with DEMO—referred to as “differential evolution for noisy MOO” (DENMO) henceforth—is studied using the noisy version of a set of 23 benchmark functions. Experiments were undertaken to compare the potency of the proposed algorithm with differential evolution for MOO with noise (DEMON) [9], nondominated sorting genetic algorithm II (NSGA-II) with α-dominance operator (NSGA-II-A) [10], confidence-based dynamic resampling (CDR) [11], simulated annealing for noisy MOO [12], elitist evolutionary multiagent system [13], multiobjective evolutionary algorithm with robust features (MOEA-RF) [14], modified NSGA-II [7], noise-tolerant strength Pareto evolutionary algorithm [15], and Pareto front-efficient global optimization [16]. In this study, the objective functions are contaminated with noise samples taken from five noise distributions—namely, Gaussian, Poisson, Rayleigh, exponential, and random (with positive and negative expeditions of the noise amplitude within {a mathematical formula}±25% of the true fitness function values). Experiments reveal that the proposed realization outperforms other algorithms for four important performance metrics—that is, inverted generational distance (IGD), spacing, error ratio (ER), and hypervolume ratio (HVR).
     </paragraph>
     <paragraph>
      The paper is divided into seven sections. Section 2 briefly reviews the literature on the strategies adopted by evolutionary algorithms to solve noisy MOO problems. In Section 3, we provide an overview of MOO and the DEMO algorithm. Section 4 provides the noise handling mechanism in DENMO. The experimental settings for the benchmarks and the simulation strategies are explained in Sections 5 and 6, respectively. Conclusions are given in Section 7.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Literature review
     </section-title>
     <paragraph>
      Recently, researchers have been very interested in developing robust MOO algorithms that can search for optimal solutions even when deceived by noise. Stagge et al. [17] employed the concept of sampling (fitness reevaluation of the same trial solutions) to enhance the objective estimates in the presence of noise. The average fitness of the samples provides a relatively safe measure of the fitness of a trial solution, thereby reducing the possible risk of certifying a low-grade trial solution to enter the optimal Pareto front. Syberfeldt et al. [11] proposed a CDR strategy to adaptively select the sample size using a Welch confidence interval test. For a user-defined confidence level, the resampling of solutions is performed iteratively until the noise is sufficiently reduced, which is assessed by the Welch confidence interval. Inspired by the role of the momentum term in back-propagation in neural networks, Goh and Tan [14] adopted an experiential-learning-directed perturbation strategy to govern the candidate movement toward the direction of fitness improvement on the basis of the information acquired from the last few generations for faster convergence. Moreover, the trade-off between the explorative and exploitative capabilities of the MOO here are balanced by the proposed gene adaptation selection strategy. Finally a possibility and necessity measure induced possibilistic archiving method is used to resolve the uncertainty in including a solution in the nondominated set.
     </paragraph>
     <paragraph>
      Babbar et al. [7] recommended a new Pareto ranking strategy to approve the ingress of apparently inferior trial solutions in the optimal Pareto front by satisfying a statistical comparison. The comparison is concerned with the difference between the mean values of the fitness samples of two individual solutions with respect to the scaled average of their fitness variance. The executed ranking policy thus prevents the probable dismissal of quality solutions from the optimal Pareto front as the true potential of such solutions may be incomprehensible because of noise. However, the inadequacy of their strategy lies in the context of uniform sampling. The scope of a new noise-aware α-dominance operator was explored by Boonma et al. [10] to evaluate the dominance relationship (with a confidence level of α) between two individuals on the basis of the measurement of their noisy fitness samples. The merit of the proposed strategy lies in no prerequisite of knowledge of the noise distribution in the objective space being needed.
     </paragraph>
     <paragraph>
      The “soft” selection scheme of the multiagent system employed by Siwik et al. [13] ensures the survival of a quality solution (agent) even with its seemingly poor fitness estimates in a noisy uncertain environment. Some resources, denoted by life energy, are assigned to each solution (agent) on the basis of its fitness: life energy is an indirect measure of the agent's survival and offspring-generation capabilities, and is reduced on reallocation of some resources to other dominating agents, and vice versa. Hence, if a quality solution seems to be dominated, it loses only a finite part of its energy, and it can prolong its functionality until its energy is reduced to zero. The strategy also guarantees that under little influence of noise, such a quality solution may get an opportunity to enhance its energy in the future by communicating with the agents it dominates. Buche et al. [15] proposed a noise-tolerant MOO algorithm. Here, each population member is assigned with a dominance-dependant lifetime, which varies inversely with the number of solutions it dominates. Thus, the strategy defends the overall population against the impact of the illusive fitness of unreliable solutions. Conversely, the survival of quality solutions is ensured by reevaluating the archived solutions with expired lifetime and adding them to the current population. Finally, the loss of information in noisy environments is hindered by appending all the solutions with nonexpired lifetime to the archive along with the nondominated members.
     </paragraph>
     <paragraph>
      Rakshit et al. [9] implemented a nonuniform sampling strategy utilizing a linear relationship between the sample size of a trial solution and the fitness variance in its local neighborhood. Moreover, the statistical expectation of the fitness samples is referred to as the “fitness measure of the trial solutions.” On the basis of the proposed strategies, Goldberg's method [7] is extended to verify possible accommodation of slightly inferior population members in the optimal Pareto front. Das et al. [18] integrated a threshold-based selection policy with a random-scale-factor-induced stochastic model of the differential evolution to proficiently explore the dynamic fitness landscape contaminated with noise. The strategy promotes an offspring vector to the next generation only if its fitness is better than that of its respective parent by a certain threshold value. This, in turn, circumvents the approval of misleading solutions over generations.
     </paragraph>
     <paragraph>
      A probabilistic dominance approach was adopted by Hughes [19] to deal with the uncertainty of decisions concerned with the supremacy of a trial solution over another in the context of noisy fitness landscapes. The placement of trial solutions in the Pareto fronts is thus governed by the quantified dominance probability. Singh et al. [20] utilized a hypothesis test based on a Student t distribution for stochastic selection of nondominated solutions. Knowles and Hughes [16] used a Gaussian-process-assisted surrogate model to discover the most competent solution possessing the largest expected improvement at the minimum cost. It is designed with the aim of optimization on a very restricted evaluation budget by weighing up both the predicted fitness of solutions and the associated error. Knowles et al. [21] proposed a fitness-distance-based correlation strategy for quality performance of a MOO problem in the presence of noise constrained by a very limited evaluation budget. Mattila et al. [12] devised a new criterion to selectively include the candidate solutions in the optimal Pareto front based on the probability that the solution is dominated by the nondominated solutions of the current generation. In addition, the generation of offsprings is guided by the information content of the nondominated solutions of the previous generations. The strategy proposed here is realized in the context of simulated annealing.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Preliminaries
     </section-title>
     <paragraph>
      In this section, we provide an overview of two important concepts—MOO and DEMO—which will be referred to frequently in the rest of the paper to develop a solution of noisy MOO problems.
     </paragraph>
     <section label="3.1">
      <section-title>
       Multiobjective optimization
      </section-title>
      <paragraph>
       The principal objective of MOO algorithms is to attain Pareto optimal solutions in a single run. The following definitions will be used to explain DEMO and its extension.
      </paragraph>
      <paragraph label="Definition 1">
       Let us consider two trial solutions {a mathematical formula}X→i and {a mathematical formula}X→j of a MOO problem where all N objectives need to be minimized. The kth objectives of {a mathematical formula}X→i and {a mathematical formula}X→j are represented by {a mathematical formula}fk(X→i) and {a mathematical formula}fk(X→j), respectively. Then {a mathematical formula}X→i is said to dominate{a mathematical formula}X→j, denoted by {a mathematical formula}X→i≺X→j, if the following conditions are jointly satisfied:
      </paragraph>
      <list>
       <list-item label="1.">
        {a mathematical formula}X→i is no worse than {a mathematical formula}X→j in all objective functions—that is, {a mathematical formula}fk(X→i)≤fk(X→j) for {a mathematical formula}k=[1,N].
       </list-item>
       <list-item label="2.">
        {a mathematical formula}X→i is strictly better than {a mathematical formula}X→j for at least one objective function—that is, {a mathematical formula}fl(X→i)&lt;fl(X→j) for at least one {a mathematical formula}l∈[1,N].
       </list-item>
      </list>
      <paragraph label="Definition 2">
       In a MOO, a trial solution {a mathematical formula}X→⁎ is said to be nondominated if there is no {a mathematical formula}X→ that dominates {a mathematical formula}X→⁎.
      </paragraph>
      <paragraph label="Definition 3">
       Let P be a set of potential solutions to a MOO problem. {a mathematical formula}P′⊆P is called the optimal Pareto set of solutions if the members of {a mathematical formula}P′ are not dominated by any member of P.
      </paragraph>
      <paragraph label="Definition 4">
       Let {a mathematical formula}f1 and {a mathematical formula}f2 be two objective functions in a MOO problem, and let {a mathematical formula}X→, {a mathematical formula}X→i, and {a mathematical formula}X→j be the members of a nondominated list of solutions. Furthermore, {a mathematical formula}X→i and {a mathematical formula}X→j are the nearest neighbors of {a mathematical formula}X→ in the objective spaces. The crowding distance of a trial solution {a mathematical formula}X→ in a nondominated set depicts the perimeter of a hypercube formed by its nearest neighbors—that is, {a mathematical formula}X→i and {a mathematical formula}X→j—at the vertices in the fitness landscapes. In other words, the crowding distance of {a mathematical formula}X→ is computed by {a mathematical formula}CD(X→)=|f1(X→i)−f1(X→j)|+|f2(X→i)−f2(X→j)|.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Differential evolution for MOO
      </section-title>
      <paragraph>
       DEMO [8] employs an evolutionary strategy that utilizes the advantages of the differential evolution [22] with the mechanisms of Pareto-based ranking and crowding distance sorting. An overview of the main steps of the DEMO algorithm is presented next:
      </paragraph>
      <list>
       <list-item label="(a)">
        Initialization: The ith member {a mathematical formula}X→i(t) of the current population {a mathematical formula}Pt for {a mathematical formula}i=[1,NP] at generation {a mathematical formula}t=0 is selected by uniformly randomizing individuals in the range [{a mathematical formula}X→min,X→max], where {a mathematical formula}X→min={x1min,x2min,…,xDmin} and {a mathematical formula}X→max={x1max,x2max,…,xDmax}, and thus the jth component of the ith member at {a mathematical formula}t=0 is initialized by{a mathematical formula} for {a mathematical formula}j=[1,D]. Here {a mathematical formula}randi,j(0,1) is a uniformly distributed random number lying between 0 and 1. The crossover rate is initialized in [0, 1]. The kth objective function {a mathematical formula}fk(X→i(0)) is evaluated for the target vector {a mathematical formula}X→i(0) with {a mathematical formula}i=[1,NP] and {a mathematical formula}k=[1,N].
       </list-item>
       <list-item label="(b)">
        Mutation: A donor vector {a mathematical formula}V→i(t) corresponding to each {a mathematical formula}X→i(t) is created by randomly selecting three other members {a mathematical formula}X→rand1(t),X→rand2(t), and {a mathematical formula}X→rand3(t)(i≠rand1≠rand2≠rand3) from {a mathematical formula}Pt, where{a mathematical formula} and F is a scaling factor in [0, 2]. The mutation operation given in (2) is referred to as DE/rand/1 [23]. This is done for {a mathematical formula}i=1 to NP. There are other mutation operations, details of which are available in [23].
       </list-item>
       <list-item label="(c)">
        Crossover: There are two types of crossover—binomial and exponential [23].In the case of binomial crossover, a trial vector {a mathematical formula}U→i(t) is generated for each pair of {a mathematical formula}V→i(t) and {a mathematical formula}X→i(t) by the following operation:{a mathematical formula} where {a mathematical formula}jrand∈[1,D] is a randomly chosen index.In the case of exponential crossover, we randomly select an integer n from [1, D]. It represents the starting point of the target vector {a mathematical formula}X→i(t) to commence the exchange of components with the corresponding donor vector {a mathematical formula}V→i(t). We also select another integer L from [1, D], where L denotes the number of components the donor vector contributes to the target. The selection of L is given in [24]. Now, we obtain the trial vector {a mathematical formula}U→i(t) with{a mathematical formula} where {a mathematical formula}〈〉D denotes a modulo function with modulus D. The kth objective function {a mathematical formula}fk(U→i(t)) is evaluated for the trial vector {a mathematical formula}U→i(t) with {a mathematical formula}i=[1,NP] and {a mathematical formula}k=[1,N].
       </list-item>
       <list-item label="(d)">
        Selection: Now the trial vector {a mathematical formula}U→i(t) replaces the corresponding target vector {a mathematical formula}X→i(t) if {a mathematical formula}U→i(t)≺X→i(t) based on the measures of their objective functions. However, when {a mathematical formula}U→i(t) and {a mathematical formula}X→i(t) are nondominated, {a mathematical formula}U→i(t) is inserted into the current population {a mathematical formula}Pt; otherwise, {a mathematical formula}U→i(t) is discarded. This assists in a faster convergence to the true Pareto front. This step is repeated for all the trial vectors, and hence a population of solution vectors is obtained with size S lying in [NP, 2NP].
       </list-item>
       <list-item label="(e)">
        Nondominated sorting: The population {a mathematical formula}Pt of size S ({a mathematical formula}NP&lt;S&lt;2NP) thus obtained is sorted into a number of Pareto fronts according to nondominating criteria. All the nondominated solutions of the current population are given same rank 1 (named optimal Pareto front Front_Set(1)). The second front is formed by identifying the nondominated solutions from the set {a mathematical formula}Pt−Front_Set(1). The ranking process continues until all the nondominated sets are identified and ranked as Front_Set(1), Front_Set(2), Front_Set(3), and so on. The pseudocode for nondominated sorting is given in [25].
       </list-item>
       <list-item label="(f)">
        Truncation of the extended population using the crowding-distance-based ranking: The parent population for the next iteration {a mathematical formula}Pt+1 is constructed by selecting the nondominated sets of solutions from {a mathematical formula}Pt according to the ascending order of their Pareto ranking. Let Front_Set(l) be the set beyond which no other set can be accommodated in {a mathematical formula}Pt+1 (i.e., by adding Front_Set(l), {a mathematical formula}|Pt+1| exceeds NP). Then the solutions in Front_Set (l) are sorted in descending order of the crowding distance. To ensure diversity in the population, the solutions with the highest crowding distances are included in {a mathematical formula}Pt+1 from Front_Set(l) until {a mathematical formula}|Pt+1| becomes NP.
       </list-item>
       <list-item label="(g)">
        Convergence: After each evolutionary step, we repeat the process from step (b) until one of the following conditions for convergence is satisfied. The stop criteria include a bound by the number of iterations, achieving a sufficiently low error or aggregations thereof.
       </list-item>
      </list>
     </section>
    </section>
    <section label="4">
     <section-title>
      Optimization in the presence of noise
     </section-title>
     <paragraph>
      This paper is concerned with real-world MOO problems, where measured variables are contaminated with stochastic noise due to the aging of sensors and/or measurement inaccuracies. The objectives in MOO, being functions of measurement variables, are also contaminated with noise and thus lack precision. Traditional deterministic MOO algorithms are unable to capture the global optima on the fitness landscapes in the presence of stochastic noise [7]. This section extends the traditional DEMO algorithm to improve its optimization efficacy in the presence of stochastic noise [26], [27] in the ways described in the following sections.
     </paragraph>
     <section label="4.1">
      <section-title>
       Adaptive selection of sample size
      </section-title>
      <paragraph>
       First, the repercussion of noise on the fitness measurements is diminished by taking repeated samples of the objective functions for each trial solution. Because objective functions in noisy MOO are contaminated with noise, a single measure of the fitness estimate is likely to be largely influenced by noise. To ensure the fitness estimates are minimally influenced by noise, one approach is to take a large sample size of the fitness estimates. Apparently, the larger the sample size, the higher the precision of the fitness estimates of a given trial solution. However, a very large sample size adds computational overhead without much contribution to improving the fitness estimates of a quality solution. Contrarily, if very few samples are considered, the fitness estimates will be inaccurate, leading to selection of a deceptive trial solution over a qualitative one. Sample size selection is thus constrained by a trade-off between accurate fitness estimation and computational complexity. Consequently, the incorporation of a method for an adaptive selection of the sample size in a MOO problem in the presence of noise is envisaged.
      </paragraph>
      <paragraph>
       We attempt to realize this strategy in the noisy MOO algorithm by introducing a test criterion on the fitness variance in the local neighborhood of a trial solution to control its sample size. In other words, the essence of the current work is to induce a trial solution with the information about the sample size (for its periodic fitness evaluation) acquired from the fitness variance in its local neighborhood. The design philosophy adopted here relies on an underlying premise that a possible measure of creeping of noise in the neighborhood of a trial solution is anticipated from the fitness variance of a subpopulation around it. A large fitness variance (among the trial solutions) in the subpopulation indicates a large-scale detrimental effect of noise in the local neighborhood (of the given trial solution) in the fitness landscape. Under this situation, it is obvious to draw a large sample size to accurately estimate the fitness of the given trial solution. On the other hand, small fitness variance in the local neighborhood portrays a smaller contamination effect of noise, and hence, in turn, requires a small sample size to reduce computational cost without sacrificing the quality fitness measurement.
      </paragraph>
      <list>
       <list-item label="(a)">
        Mathematical model for sample size adaptation: Several formulations of the sample size selection can be adopted by maintaining a smaller sample size at lower fitness variance and a larger sample size at larger fitness variance in the local neighborhood of a trial solution. One simple approach could be proportional selection, where the sample size n is proportional to the fitness variance v in the local neighborhood of a trial solution. However, simply setting a proportional law demands a very large sample size n at very large variance v, which may not be economic in many contexts, particularly for practical MOO problems. Alternatively, a logistic function may be employed to serve the purpose. Expression (5) refers to such a model with sample size {a mathematical formula}nk,i corresponding to the kth objective function {a mathematical formula}fk(X→i) of the trial solution {a mathematical formula}X→i for {a mathematical formula}k=[1,N], having a lower bound {a mathematical formula}nk,i≥nmin and a largest bound {a mathematical formula}nk,i≤nmax. As shown in Fig. 1, the function within these two bounds is a continuous nondecreasing function, and the fitness variance {a mathematical formula}vk,i in the local neighborhood of {a mathematical formula}X→i (corresponding to the kth objective) controls the value of {a mathematical formula}nk,i within {a mathematical formula}[nmin,nmax] for {a mathematical formula}k=[1,N]. In Fig. 1, {a mathematical formula}vkmax denotes the maximum fitness variance in the local neighborhood of all trial solutions in the current population for the kth objective with {a mathematical formula}k=[1,N].{a mathematical formula}
       </list-item>
       <list-item label="(b)">
        Local neighborhood selection: To determine the neighborhood of a D-dimensional trial solution {a mathematical formula}X→i from a population of NP members in the parameter space, the search range [{a mathematical formula}xjmin,xjmax] is first divided into equally spaced intervals of {a mathematical formula}Δxj=(xjmax−xjmin)/NP for {a mathematical formula}j=[1,D]. Now the neighborhood of {a mathematical formula}X→i, denoted by {a mathematical formula}Ni, is constructed by selecting the trial solutions lying within a hyperspace bounded by [{a mathematical formula}ΔX→imin,ΔX→imax ], where{a mathematical formula}{a mathematical formula}
       </list-item>
       <list-item label="(c)">
        Fitness variance in the local neighborhood: Once all trial solutions {a mathematical formula}X→j in the local neighborhood {a mathematical formula}Ni around {a mathematical formula}X→i have been identified, the fitness variance in {a mathematical formula}Ni is determined as follows:{a mathematical formula} where {a mathematical formula}nk,j symbolizes the sample size and {a mathematical formula}sk,j represents the spread of the samples of {a mathematical formula}fk(X→j) for {a mathematical formula}k=[1,N], which will be discussed very shortly.
       </list-item>
      </list>
     </section>
     <section label="4.2">
      <section-title>
       Sample-distribution-based fitness estimation
      </section-title>
      <paragraph>
       Because of the adaptive selection of the sample size, we have multiple fitness measurements of a given trial solution. These measurements in general take different values with a nonzero variance. Traditional noisy MOO algorithms estimate the true fitness estimate of a given trial solution by averaging over its noisy fitness samples. However, this averaging strategy presumes equal probability of occurrence of all fitness samples, thereby offering a poor fitness estimate in most of the real situations. This can be circumvented by the second extension of the traditional DEMO algorithm in this paper. The alternative approach proposed is concerned with the fitness-sample-density-based partitioning of the sample space and then referring to the expected value of the entire sample space as the true fitness estimate of a trial solution. In other words, the fitness estimate of a trial solution is more biased toward the fitness samples in the crowded regions in the sample space, while imposing less importance on the rare fitness samples. It is assumed here that the fitness samples in the sparse zones in the sample space result from noise contamination. Sample-distribution-based fitness estimation (SDFE) includes four main steps:
      </paragraph>
      <list>
       <list-item label="(a)">
        Fitness interval selection in the sample space: We first record the variance {a mathematical formula}Vk(X→i) of the measured samples of the kth fitness of trial solution {a mathematical formula}X→i. We also note down the minimum and the maximum values of the observed fitness samples—say, {a mathematical formula}fkmin(X→i) and {a mathematical formula}fkmax(X→i), respectively. Now the entire range [{a mathematical formula}fkmin(X→i),fkmax(X→i)] is first divided into two intervals of equal length. The resulting intervals are represented by [{a mathematical formula}fkmin(X→i),fkmid(X→i)] and [{a mathematical formula}fkmid(X→i),fkmax(X→i)], respectively where {a mathematical formula}fkmid(X→i)=(fkmin(X→i)+fkmax(X→i))/2. If the variance of the fitness samples lying in the first interval is found to be greater than {a mathematical formula}Vk(X→i)/nk,i, it is again subdivided into two more equal intervals, represented by [{a mathematical formula}fkmin(X→i),fkmid,1(X→i)] and [{a mathematical formula}fkmid,1(X→i),fkmid(X→i)], respectively, where {a mathematical formula}fkmid,1(X→i)=(fkmin(X→i)+fkmid(X→i))/2. The same approach is used in the second interval also. The same procedure is repeated for all subsequent intervals until the variance of the fitness samples in each interval falls below {a mathematical formula}Vk(X→i)/nk,i. As a consequence, the entire sample space [{a mathematical formula}fkmin(X→i),fkmax(X→i)]is now divided into L intervals of unequal length as indicated in Fig. 2.
       </list-item>
       <list-item label="(b)">
        Occurrence probability of the fitness samples: It is evident from the proposed nonuniform partitioning of the sample space that the fitness samples in the longer intervals are rare samples, probably owing to noise, and hence their contribution to the true fitness estimate of {a mathematical formula}X→i should not be regarded similarly to that of the fitness samples in the smaller interval. We measure the contribution of the fitness samples of the interval j to the fitness estimate of the trial solution {a mathematical formula}X→i by a probability measure {a mathematical formula}pj:{a mathematical formula} where {a mathematical formula}nk,ij represents the number of samples of {a mathematical formula}fk(X→i) in the jth interval for {a mathematical formula}j=[1,L].
       </list-item>
       <list-item label="(c)">
        Expected fitness estimation: Let {a mathematical formula}fkj(X→i) be the median value of the fitness samples of {a mathematical formula}X→i in the jth interval, for {a mathematical formula}j=[1,L]. We obtain the expected value—say, {a mathematical formula}E(fk(X→i))=f‾k(X→i)—of the kth fitness of {a mathematical formula}X→i by (9):{a mathematical formula}The expected value thus obtained provides a unique measure of the kth objective of {a mathematical formula}X→i from the noisy local distribution of its fitness samples over a wide space. The fitness samples in a particular interval are represented here by their median because the median value of a frequency distribution is less prone to noisy measurements [28]. A schematic diagram of the evaluation of the expected fitness of the kth objective is given in Fig. 3. The entire procedure is performed for each objective—that is, {a mathematical formula}k=[1,N].
       </list-item>
       <list-item label="(d)">
        Spread of the fitness samples: The level of contamination of noise on {a mathematical formula}fk(X→i) can be captured by the spread of sample values of {a mathematical formula}fk(X→i) away from {a mathematical formula}f‾k(X→i), denoted by {a mathematical formula}sk,i, for {a mathematical formula}k=[1,N]. To evaluate {a mathematical formula}sk,i, the median values of fitness samples of each of the L intervals are sorted in ascending order of magnitude. The lower and upper quartiles from the sorted list are identified and recorded as {a mathematical formula}Qk,0.25(X→i) and {a mathematical formula}Qk,0.75(X→i), respectively. The interquartile range corresponding to {a mathematical formula}fk(X→i) is then used as a measure of {a mathematical formula}sk,i as defined by (10) for {a mathematical formula}k=[1,N]:{a mathematical formula}To eliminate the impact of the extreme values of the noisy fitness samples, the interquartile range is referred to as a measure of the spread of the samples of {a mathematical formula}fk(X→i) from the respective expected measurement {a mathematical formula}f‾k(X→i), instead of the sample variance.
       </list-item>
      </list>
     </section>
     <section label="4.3">
      <section-title>
       PS during truncation of the extended population
      </section-title>
      <paragraph>
       The next-generation population (of size NP) of a MOO is formed by identifying the trial solutions with higher Pareto ranks from the merged population (of size lying in [NP, 2NP]) in the current generation. It is apparent that the entire accommodation of all the nondominated members of a definite front may not be granted in the next generation to keep the next-generation population size fixed at NP. A greedy selection process is then employed to promote the members from the same front to the next generation, ensuring diversity in the distribution of trial solutions in the objective spaces. To rank the solutions in the same front, the crowding distance metric is used. The crowding distance of a solution {a mathematical formula}X→i, denoted by {a mathematical formula}CD(X→i), offers an estimate of the density of nondominated solutions neighboring {a mathematical formula}X→i. It is the sum of the distances between each of the fitness measures of its two nearest neighboring solutions in the objective spaces. In traditional MOO, the conqueror of the two same-rank solutions is the one having the greater crowding distance. This, in turn, improves the diversity performance of the algorithm, enriching its explorative capability.
      </paragraph>
      <paragraph>
       This conventional process for ranking solutions in the same front using the crowding distance metric does not take into account the uncertainty in the measurement of the noisy fitness samples. The possible promotion of a trial solution {a mathematical formula}X→i to the next generation (from the same-rank candidate pool) in the presence of noise depends on two important issues. First, the greater the crowding distance measure CD({a mathematical formula}X→i), the higher is the chance of selecting {a mathematical formula}X→i from its competitors residing in the same front. The uncertainty involved in the fitness measurement is taken care of by the second criterion—the probability of the nonoccurrence of the rare samples of {a mathematical formula}fk(X→i). A higher value of this probability ensures proximity of the measured fitness samples to {a mathematical formula}f¯k(X→i) in the sample space. The intermittent samples, far away from {a mathematical formula}f¯k(X→i), are supposed to result from the contamination effect of noise, and evidently their occurrence produces a longer tail in the sample distribution. Finally, a new selection strategy, induced by the crowding distance and the probability of nonoccurrence of rare samples, is devised to promote quality solutions to the next generation from the same front.
      </paragraph>
      <paragraph>
       The contamination effect of noise on fitness samples is realized here using quartile skewness (of the distribution of fitness samples) to capture the possible occurrence of rare fitness samples away from the expected fitness estimate. The quartile skewness {a mathematical formula}γk,i, defined by (11), provides a robust measure of the degree of asymmetry of the distribution of fitness samples of {a mathematical formula}fk(X→i) with respect to the expected value {a mathematical formula}f¯k(X→i) for {a mathematical formula}k=[1,N]:{a mathematical formula}
      </paragraph>
      <paragraph>
       It is apparent from (11) that {a mathematical formula}γk,i&lt;0 indicates the tail on the left of the fitness sample distribution is more pronounced than the tail on the right, signifying that fitness samples with values comparatively less than {a mathematical formula}f¯k(X→i) are rare. The reverse case is true for {a mathematical formula}γk,i&gt;0. It is apparent that for {a mathematical formula}γk,i approaching −1 (or {a mathematical formula}γk,i approaching +1), the frequency of the occurrence of fitness samples lying on the left (or right) tail of the fitness sample distribution, far away from {a mathematical formula}f¯k(X→i), is extremely small and these may be regarded as noisy samples [29]. It is thus evident that skewness is greatly influenced by the occurrence of rare noisy fitness samples far away from the expected value {a mathematical formula}f¯k(X→i). Hence, it is expected that for {a mathematical formula}fk(X→i) less affected by noise, the measured fitness samples will be very close to {a mathematical formula}f¯k(X→i) and hence {a mathematical formula}γk,i≈ 0. This observation motivated us to denote {a mathematical formula}0&lt;|γk,i|&lt;1 as the probability of occurrence of rare samples encompassing the uncertainty involved in the measurement of fitness samples of {a mathematical formula}fk(X→i). Thus, we define the probability of nonoccurrence of rare samples, providing a measure of the degree of reliability on the samples of {a mathematical formula}fk(X→i), as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The normalized measure of CD({a mathematical formula}X→i), denoted by {a mathematical formula}CD‾(X→i), is given in (13), where {a mathematical formula}X→i and {a mathematical formula}X→j lie in the same Pareto front:{a mathematical formula}
      </paragraph>
      <paragraph>
       Now, treating {a mathematical formula}CD‾(X→i) like probability and presuming that {a mathematical formula}pk,i for {a mathematical formula}k=[1,N] and {a mathematical formula}CD‾(X→i) are independent, we define the selection probability of {a mathematical formula}X→i for the next generation as{a mathematical formula} The product function introduced in (14) reveals that an increase in either {a mathematical formula}pk,i for {a mathematical formula}k=[1,N] or {a mathematical formula}CD‾(X→i) or in both of them ensures an increase in {a mathematical formula}psi.
      </paragraph>
      <paragraph>
       The pseudocode for the proposed DENMO algorithm with N objectives is given below. Termination criteria for the algorithm include a bound by the maximum number of function evaluations (FEs) or the achievement of a sufficiently low difference between the performance metric values (discussed in Section 5.3) of two successive generations or aggregations thereof.
      </paragraph>
      <paragraph>
       Procedure DENMO
      </paragraph>
      <paragraph>
       Begin
      </paragraph>
      <list>
       <list-item label="I.">
        Initialization:
       </list-item>
       <list-item label="II.">
        While the stopping criterion is not reached do begin
       </list-item>
      </list>
      <paragraph>
       End While;
      </paragraph>
      <paragraph>
       End.
      </paragraph>
     </section>
     <section label="4.4">
      <section-title>
       Comparative framework and parameter setting
      </section-title>
      <paragraph>
       The MOO algorithms used for the comparative study included DEMON [9], NSGA-II-A [10], CDR [11], simulated annealing for noisy MOO [12], elitist evolutionary multiagent system [13], MOEA-RF [14], modified NSGA-II [7], noise-tolerant strength Pareto evolutionary algorithm [15], and Pareto front-efficient global optimization [16]. These algorithms were selected for the comparative framework for their wide popularity in the realm of noisy MOO. The population size and the maximum number of FEs for all the algorithms were fixed at 50 and {a mathematical formula}104×D for a D-dimensional problem, respectively. To make the comparison fair, the population of all the algorithms (over all the benchmark functions discussed in Section 5.1) was initialized using the same random seeds. The best parametric setups for all these algorithms were chosen following their respective sources. In our proposed DENMO algorithm, the minimum and maximum sample sizes are considered to be {a mathematical formula}nmin=10 and {a mathematical formula}nmax=30, respectively, with a crossover rate of 0.9. The parameter settings are given in Table 1, Table 2.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Benchmark functions and evaluation metrics
     </section-title>
     <section label="5.1">
      <section-title>
       Benchmark functions
      </section-title>
      <paragraph>
       The most challenging issue in substantiating the performance of a MOO algorithm is to identify the right benchmark functions with diverse characteristics such as multimodality, deception, isolation, and particularly, the location of the true optimal Pareto front in the objective spaces to resemble complicated real-world problems. Traditional benchmark functions [31], [32] usually have the global optima located either in the center of the parameter space or on the search bounds. Naturally, these benchmark functions are insufficient to profoundly validate the performance of a MOO algorithm. To surmount the above problem, a set of benchmark functions [30] was recommended in the Congress of Evolutionary Computation (CEC'2009) conference. The proposed benchmarks include extension, stretching, and rotation of the objective functions, thereby assimilating diversity in the optimization problems of the traditional benchmark functions.
      </paragraph>
      <paragraph>
       The performance of the proposed DENMO algorithm is analyzed here with respect to the noisy-version of 23 CEC'2009—recommended multiobjective benchmark functions [30]. Among these benchmarks, seven (UF1–UF7) are two-objective, three (UF8–UF10) are three-objective, and three (UF11–UF13) are five-objective unconstrained (bound-constrained) test functions. UF11–UF13 are the extended and rotated versions of two immensely popular test suites—the Deb–Thiele–Laumanns–Zitzler test suites [31], [32]—and one test function from the Walking Fish Group test suite [33]. The set of 23 benchmark functions also includes seven (CF1–CF7) two-objective and three (CF8–CF10) three-objective general constrained test instances.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Noise models
      </section-title>
      <paragraph>
       The noisy version of the kth objective {a mathematical formula}fk(X→), of any trial solution {a mathematical formula}X→, is given by{a mathematical formula} where {a mathematical formula}ηk represents the injected stochastic noise amplitude that follows a certain probability distribution function (PDF). The following five variants of {a mathematical formula}ηk are considered here:
      </paragraph>
      <list>
       <list-item label="(a)">
        Gaussian:{a mathematical formula}ηk has a Gaussian PDF, which is given by{a mathematical formula} where m and {a mathematical formula}σ2 stand for the mean and variance of the Gaussian PDF. We have used a well-known technique called the Box–Muller method [34] to inject {a mathematical formula}ηk into {a mathematical formula}fk(X→) following the Gaussian distribution.
       </list-item>
       <list-item label="(b)">
        Poisson:{a mathematical formula}ηk has a Poisson PDF, which is given by{a mathematical formula} where λ represents the mean (as well as the variance) in the Poisson distribution. The injection of Poisson noise {a mathematical formula}ηk on {a mathematical formula}fk(X→) is performed here using Knuth's algorithm [35].
       </list-item>
       <list-item label="(c)">
        Rayleigh:{a mathematical formula}ηk has a Rayleigh PDF, which is given by{a mathematical formula} where the mean and the variance of the noise distribution are {a mathematical formula}m=bπ/2 and {a mathematical formula}σ2=b2(4−π)/2, respectively. The injection of Rayleigh noise {a mathematical formula}ηk on {a mathematical formula}fk(X→) is performed here using inverse transform sampling [36].
       </list-item>
       <list-item label="(d)">
        Exponential:{a mathematical formula}ηk has an exponential PDF, which is given by{a mathematical formula} where the mean and the variance of the noise distribution are {a mathematical formula}m=1/a and {a mathematical formula}σ2=1/a2, respectively. We have used the Ziggurat method [37] to inject {a mathematical formula}ηk into {a mathematical formula}fk(X→) following an exponential distribution.
       </list-item>
       <list-item label="(e)">
        Random: Lastly, we consider {a mathematical formula}ηk to be random noise with maximum noise amplitude within {a mathematical formula}±25% of the true fitness amplitudes {a mathematical formula}fk(X→). Linear congruential pseudorandom number generator code [38] is used to generate the random noise.
       </list-item>
      </list>
     </section>
     <section label="5.3">
      <section-title>
       Performance metrics
      </section-title>
      <list>
       <list-item label="(a)">
        Inverted generational distance (IGD): Let {a mathematical formula}P⁎ be a set of uniformly distributed points along the true optimal Pareto front and let A be an approximate set to the optimal Pareto front, both defined in the objective space of a MOO problem. Then, the average distance from {a mathematical formula}P⁎ to A[30] may be defined as follows:{a mathematical formula} Here {a mathematical formula}d(v,A) represents the minimum Euclidean distance between v and the points in A. A lower value of IGD ensures that the approximate Pareto front A, obtained by the proposed MOO, is very close to the optimal Pareto front.
       </list-item>
       <list-item label="(b)">
        Spacing (Δ): Schott [39] proposed a metric to measure “the range variance of the neighboring vectors of the nondominated solutions” obtained by the algorithm in question. The metric provides a distinctive measure of the spread and distribution of the vectors. The metric is defined as follows:{a mathematical formula} Here {a mathematical formula}di=minj=1,j≠iM⁡∑k=1N|f‾k(X→i)−f‾k(X→j)| with M as the nondominated vectors found by the method. Here {a mathematical formula}X→i and {a mathematical formula}X→j are nondominated vectors belonging to the approximate Pareto front A. A value of zero for this metric signifies all the members of the approximate Pareto front are equidistantly spaced.
       </list-item>
       <list-item label="(c)">
        Error ratio (ER): This metric was introduced by van Veldhuizen [40] and is defined as follows:{a mathematical formula} An ideal value of zero for this metric designates that all the nondominated solutions in the approximate Pareto front A belong to the optimal Pareto front {a mathematical formula}P⁎.
       </list-item>
       <list-item label="(d)">
        Hypervolume ratio (HVR): This metric was proposed by Coello et al. [41], and is defined as follows.{a mathematical formula} Here, HV(A) and HV(P⁎) denote the hypervolume of the approximate Pareto front A and optimal Pareto front P⁎, respectively. The size of the objective spaces covered by a set of nondominated solutions S is termed as its hypervolume {a mathematical formula}HV(S). Mathematically,{a mathematical formula} Here Λ symbolizes the Lebesgue measure. {a mathematical formula}X→ref denotes the reference point with the lowest fitness (i.e., the maximum objective function value in the case of a minimization problem). HVR(A) attains its maximum (ideal) value of 1 [42] provided the nondominated vectors belonging to A (in the objective spaces) are identical to the members of the optimal Pareto front {a mathematical formula}P⁎.
       </list-item>
      </list>
      <paragraph>
       However, under the circumstances of noisy fitness landscapes, there is a need to address the uncertainty related to the fitness measurements while determining the hypervolume of the approximate Pareto front A. The uncertainty problem is resolved here by weighting the size of the objective space covered by a nondominated solution {a mathematical formula}X→ with the probability that {a mathematical formula}X→ dominates at least one population member. The higher the probability, the more reliable the measure of the objective space covered by {a mathematical formula}X→. For a MOO problem with all objectives to be minimized, the probability of a trial solution {a mathematical formula}X→ dominating another solution {a mathematical formula}X→j is given in (25):{a mathematical formula}
      </paragraph>
      <paragraph>
       The validation of the above probability distribution is evident from the following observations:
      </paragraph>
      <list>
       <list-item label="1.">
        If c approaches ∞ and {a mathematical formula}f‾k(X→j)&gt;f‾k(X→) for {a mathematical formula}k=[1,N], then {a mathematical formula}p(X→≺X→j)=1, indicating the dominance of {a mathematical formula}X→ over {a mathematical formula}X→j.
       </list-item>
       <list-item label="2.">
        If c approaches ∞ and {a mathematical formula}f‾k(X→j)&lt;f‾k(X→) for {a mathematical formula}k=[1,N], then {a mathematical formula}p(X→≺X→j)=0, indicating the dominance of {a mathematical formula}X→j over {a mathematical formula}X→.
       </list-item>
       <list-item label="3.">
        If {a mathematical formula}f‾k(X→j)≅f‾k(X→) for {a mathematical formula}k=[1,N], then {a mathematical formula}p(X→≺X→j)=1/2N, indicating the nondominance relationship between {a mathematical formula}X→ and {a mathematical formula}X→j.
       </list-item>
      </list>
      <paragraph>
       It is apparent that the probability that at least one population member is dominated by {a mathematical formula}X→ is given by (26):{a mathematical formula}
      </paragraph>
      <paragraph>
       Hence the hypervolume of the approximate front A can now be evaluated using (24) with the objective space covered by any trial solution {a mathematical formula}X→ being weighted by {a mathematical formula}pX→ for all {a mathematical formula}X→∈A.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Simulation results
     </section-title>
     <paragraph>
      This section provides the relative performance of the individual extensions of DEMO introduced before through computer simulations. A comparative analysis of the performance of DENMO and the performance of a few standard algorithms is also undertaken in this section.
     </paragraph>
     <section label="6.1">
      <section-title>
       Effectiveness of different extensions of DENMO
      </section-title>
      <paragraph>
       In Section 4, we extended DEMO by introducing three strategies—namely, adaptive selection of sample size (ASSS), SDFE, and PS—to suit its application in noisy MOO problems. The ASSS, SDFE, and PS strategies are mutually independent as they deal with three different issues in the context of noisy optimization. To be more specific, while the ASSS strategy is concerned with the sample size adaptation, the SDFE strategy deals with expected fitness of trial solutions based on the distribution of fitness samples, and the PS strategy takes care of relative comparison of trial solutions of the same rank to ensure diversity as well as quality of the solutions in the population. Naturally, incorporation of any one of the three strategies into DEMO does not necessarily require exclusion of the rest. The following groups of strategies are considered below for the experiments:
      </paragraph>
      <list>
       <list-item label="(a)">
        DEMO-ASSS: Traditional DEMO is extended here with the ASSS strategy only. The mean value of the fitness samples is used as the fitness estimate of a given trial solution. The crowding-distance-induced selection scheme is employed for the truncation of the extended population.
       </list-item>
       <list-item label="(b)">
        DEMO-SDFE: Here, the SDFE strategy is integrated with the traditional DEMO with equal sample size (size 20) being assigned to all the trial solutions for their fitness reevaluation. Here also the crowding-distance-induced selection scheme is employed for selection of quality solutions from the same-rank front.
       </list-item>
       <list-item label="(c)">
        DEMO-PS: The performance of traditional DEMO is improved here by the PS approach. Here also the sample size of all the trial solutions is fixed at 20 to estimate their mean fitness.
       </list-item>
       <list-item label="(d)">
        DEMO-ASSS-SDFE: Traditional DEMO here utilizes the benefits of both the ASSS strategy and the SDFE strategy. Truncation of the extended population using crowding distance sorting of traditional DEMO remains unchanged.
       </list-item>
       <list-item label="(e)">
        DEMO-ASSS-PS: The extension here encompasses the ASSS and PS strategies to govern the diversity and quality of the solutions in the population.
       </list-item>
       <list-item label="(f)">
        DEMO-SDFE-PS: Traditional DEMO is extended here with SDFE and PS. The same sample size (size 20) is assigned to each trial solution.
       </list-item>
       <list-item label="(g)">
        DENMO: All three extensions are integrated into traditional DEMO.
       </list-item>
      </list>
      <paragraph>
       The mean and the standard deviation of the best-of-run IGD metric values for 50 independent runs of each of the seven variants considered in this section, along with their traditional counterpart DEMO, are presented in Table 3 for 23 30-dimensional CEC'2009-recommended multiobjective benchmark functions [30], each contaminated with random noise of restricted amplitude. To obtain the results shown in Table 3, all algorithms were run from the same initial population in every run. The relative ranking of different extensions was also examined with respect to the remaining performance metrics with different noise settings. The results obtained follow a trend similar to those reported in Table 3; however, they are not given here because of space restrictions. Friedman two-way analysis of variances by ranks [43], a nonparametric statistical test, was also performed on the mean of the IGD metric values for 50 independent runs of each variant as reported in Table 3. The null hypothesis here states that all the algorithms are equivalent, so their individual ranks should be equal. The last row in Table 3 summarizes the rankings obtained by the Friedman procedure. It is evident that DENMO outperforms the other extended versions of the traditional DEMO in handling noise in fitness landscapes. With a level of significance {a mathematical formula}α=0.05, the Friedman statistic exhibits significant differences in the performance of the competing algorithms with a test value of 161. The results highlight DENMO as the best algorithm, so post hoc analysis [44] was applied with DENMO as the control method. Although we provide the results for the IGD metric only, the trend remains the same for each of the remaining performance metrics—that is, Δ, ER, and HVR—and for all five variants of the stochastic noise. In the post hoc analysis, the Holm test [44] was employed on the results of the Friedman procedure with DENMO as the control algorithm, and the results are given in Table 4. The null hypothesis here considers that the performance of DENMO and any of the seven competitor algorithms is equally good. However, the outcome of the analysis indicates that only for DEMO-SDFE-PS the null hypothesis cannot be rejected with any of the benchmark functions. The performance of DENMO, however, may be considered as significantly better than that of the other six variants in the present context.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Performance analysis of DENMO
      </section-title>
      <paragraph>
       The comparative analysis of the relative performance of the proposed DENMO algorithm and its competitors is discussed in this section. Although all the experiments were performed for all five variants of noise with noise variance {a mathematical formula}σ2∈[0,1] and also for 10-, 30-, and 50-dimensional problems, we report here the results for finite values of {a mathematical formula}σ2, and for specific problem dimensions to save space. The results omitted follow a trend similar to that in the tables and figures in this section.
      </paragraph>
      <section label="6.2.1">
       <section-title>
        Comparative performance of algorithms with respect to the IGD metric
       </section-title>
       <paragraph>
        The mean and standard deviation of the IGD metric for 50 independent runs (each with 300,000 FEs for a 30-dimensional problem) of each of the ten algorithms are presented in Table 5 with {a mathematical formula}ηk as the Poisson noise (mean 0.25 and variance 0.25).
       </paragraph>
       <paragraph>
        Since all the algorithms commence with the same initial population for each problem instance, we use paired t tests to compare the means of the results produced by the best and the second-best algorithms [45]. The statistical significance level for the difference of the means of the best two algorithms is presented in the 12th column in Table 5, Table 6, Table 7, Table 8. Here a plus sign designates that the t value of 49 degrees of freedom is significant at the 0.05 level of significance by a two-tailed test, a minus sign denotes that the difference of means is not statistically significant, and “not applicable” refers to the cases for which two or more algorithms achieve the same best accuracy results. The statistical significance hence refers to the comparison of DENMO with the best of the remaining nine algorithms.
       </paragraph>
       <paragraph>
        The simulation results in Table 5 show that DENMO outperformed its competitors for 21 of the 23 benchmark functions. Of these 21, for 20 functions the difference between the mean of the IGDs of DENMO and its nearest competitor is statistically significant. DEMON, which remains the second-best algorithm, achieves the best average IGD, outperforming DENMO in one case (UF7).
       </paragraph>
       <paragraph>
        Plots of the final approximation sets with the smallest IGD in the objective spaces for some test instances with two- and three-objectives are shown in Fig. 4. It is evident from Fig. 4 that the approximate Pareto front found by the DENMO algorithm is closer to the optimal Pareto front in comparison with the other competing algorithms.
       </paragraph>
      </section>
      <section label="6.2.2">
       <section-title>
        Comparative performance of algorithms with respect to the Δ metric
       </section-title>
       <paragraph>
        The mean and standard deviation of the Δ metric for 50 independent runs (each with 500,000 FEs for a 50-dimensional problem) of each of the ten algorithms are presented in Table 6 with {a mathematical formula}ηk as the Rayleigh noise (mean 0.3 and variance 0.025). Table 6 indicates that DENMO outperformed all the contender algorithms in a statistically significant fashion for 20 functions with respect to the Δ metric. It remains the second-best algorithm for the benchmark function UF11, being outperformed by DEMON alone. In the case of the benchmark functions UF13 and CF7, the performance of DENMO remains comparable to that of DEMON. However, it is noteworthy that for UF13 DENMO achieves the lowest standard deviation once again.
       </paragraph>
      </section>
      <section label="6.2.3">
       <section-title>
        Comparative performance of algorithms with respect to the ER metric
       </section-title>
       <paragraph>
        The mean and standard deviation of the ER metric for 50 independent runs (each with 300,000 FEs for a 30-dimensional problem) of each of the ten algorithms are presented in Table 7 with {a mathematical formula}ηk as exponential noise (mean 0.86 and variance 0.75). Close scrutiny of Table 7 reveals that DENMO outperformed all nine evolutionary/swarm noisy MOO algorithms in a statistically significant fashion for 19 of the 23 test functions in achieving near optimal values of the ER metric. It yielded results statistically equivalent to those of DEMON in the case of benchmark functions UF3 and CF2. It achieved the second-best rank among the contender algorithms for benchmarks UF7 and UF13.
       </paragraph>
      </section>
      <section label="6.2.4">
       <section-title>
        Comparative performance of algorithms with respect to the HVR metric
       </section-title>
       <paragraph>
        The mean and standard deviation of the HVR metric for 50 independent runs (each with 300,000 FEs for a 30-dimensional problem) of each of the ten algorithms are presented in Table 8 with {a mathematical formula}ηk as Gaussian noise (mean 0 and variance 0.4). Close inspection of Table 8 indicates that the performance of the proposed DENMO algorithm remained consistently superior to that of the other noisy MOO algorithms with respect to the HVR metric. Of the 23 benchmark functions, in 20 cases DENMO outperforms its nearest-neighbor competitor in a statistically significant fashion.
       </paragraph>
      </section>
      <section label="6.2.5">
       <section-title>
        Effect of varying the noise variance
       </section-title>
       <paragraph>
        In this subsection, we scrutinize the effect of varying the noise variance on the performance of all the algorithms. Fig. 5 shows the evolution of the average Δ and ER metric values of the population with the noise variance for all ten algorithms number when the number of generations is fixed at 300,000 (for problem dimension {a mathematical formula}D=30) for Poisson and exponential noise, respectively. It is evident from Fig. 5 that all the noisy MOO algorithms eventually lose their accuracy in achieving values of Δ and ER close to the ideal value (i.e., zero) as noise of increasing variance creeps into the fitness landscapes. However, DENMO appears to be most effective in achieving an approximate Pareto front with lower values of the Δ and ER metrics, even when noise is a predominant factor and the fitness landscape itself is very complex.
       </paragraph>
      </section>
      <section label="6.2.6">
       <section-title>
        Effect of varying the problem dimension
       </section-title>
       <paragraph>
        Plots of the average HVR and IGD metric values against the problem dimension (within [10, 100]) are given in Fig. 6 for Rayleigh and random distribution of noise, respectively. We note from Fig. 6 that the HVR and IGD metrics are nonincreasing and nondecreasing functions, respectively, of the problem dimension D for specific noise settings. An intuitive interpretation of this phenomenon is that with increase in D, a more complex terrain needs to be explored by the population members to obtain the Pareto optimal solutions, thereby decreasing the HVR and increasing the IGD metric values. However, for all instances DENMO achieves the best rank among the contestants by providing the largest and smallest values of the HVR and IGD metrics, as substantiated by Fig. 6.
       </paragraph>
      </section>
      <section label="6.2.7">
       <section-title>
        Convergence characteristics
       </section-title>
       <paragraph>
        To compare the relative speed of convergence and the quality of the solution of DENMO and the other competitors, the Δ and ER metric values of the median run of each algorithm versus the number of FEs are plotted in Fig. 7. Fig. 7 shows that DENMO outperformed all the contender algorithms.
       </paragraph>
      </section>
      <section label="6.2.8">
       <section-title>
        Robustness and runtime analysis
       </section-title>
       <paragraph>
        The latter part of the experiment compared the consistent performance and the speed of different algorithms with respect to the HVR metric. First, a threshold value of the HVR metric was selected corresponding to each benchmark function. Then each of the ten algorithms was run on each benchmark function (for different settings of noise and problem dimension). The algorithm was terminated if either the best value of the HVR metric achieved by the algorithm fell above the predefined threshold or if the maximum number of FEs (300,000 for 30-D problems and 500,000 for 50-D problems) was reached, whichever occurred earlier. The termination of an algorithm because of the occurrence of the first condition indicates that the algorithm succeeds in finding the approximate Pareto front within the prescribed tolerance limit of the HVR metric in that specific run (without reaching the maximum number of FEs) and hence it is said to be a successful run. The number of such successful runs out of a total of 50 runs was recorded for each algorithm with respect to the predefined threshold value of the HVR metric. A lower number of unsuccessful runs (i.e., total runs minus successful runs) of an algorithm corresponds to robustness in its performance. In Fig. 8, we present a plot of number of unsuccessful runs versus the runtime in terms of the expected number of FEs over 50 independent runs, with respect to the HVR tolerance limit of 0.75 for each of the ten algorithms for UF5 (tested for different settings of the problem dimension and stochastic noise). The plot provides a visual means of elucidating the efficacy of all algorithms with respect to both robustness and runtime (in terms of the expected number of FEs). The x and y coordinates are scaled properly to have uniformity in magnitude. The performance of an algorithm was then assessed by measuring the distance of the representative point from the origin. The smaller the measure, the better is the performance of the algorithm in terms of both robustness and expected runtime. The rankings thus obtained for different dimensional problems are given in Table 9. The experiment was repeated for all benchmark functions with different settings of stochastic noise and the problem dimension with respect to all three remaining metrics. The results omitted for economy of space follow a trend similar to that in Fig. 8 and Table 9. It is observed from Fig. 8 that DEMON, MOEA-RF, and simulated annealing in the case of a 30-D problem (with zero mean Gaussian noise of {a mathematical formula}σ2=0.35) and DEMON, NSGA-II-A, and CDR in the case of a 50-D problem (with Poisson noise of {a mathematical formula}σ2=0.7) manage to attain a smaller number of unsuccessful runs than DENMO but at the cost of increased expected runtime.
       </paragraph>
      </section>
      <section label="6.2.9">
       <section-title>
        Nonparametric statistical analysis of performance
       </section-title>
       <paragraph>
        A series of nonparametric statistical tests were also performed on the mean of all four performance metrics for 50 independent runs of each of the ten competitor algorithms as reported in Table 5, Table 6, Table 7, Table 8. The first test was the Friedman two-way analysis of variances by ranks [43]. Additionally, we used the Iman-Davenport test as a variant of the Friedman test [46]. The objective of the Friedman and Iman-Davenport tests is to show that there is a significant statistical difference between different algorithms. Table 10 summarizes the rankings obtained by the Friedman procedure, highlighting DENMO as the best algorithm. With a level of significance α of 0.05, both the Friedman statistics and the Iman-Davenport statistics show significant differences in the performance of the contender algorithms, with the test values as presented in Table 10 and {a mathematical formula}p&lt;0.001. So the post hoc analysis was performed with DENMO as the control method.
       </paragraph>
       <paragraph>
        In the post hoc analysis, we applied the Bonferroni–Dunn test [47] to the ranking results of the Friedman procedure. The analysis indicates the level of significance of the superiority of the control algorithm over each of the remaining nine algorithms. For the Bonferroni–Dunn test, a critical difference [44] was calculated, which for these data was 2.2677. The interpretation of this measure is that the performance of the two algorithms is significantly different only if their corresponding average Friedman ranks differ by at least a critical difference, which is depicted in Fig. 9. Fig. 9 shows a bar graph, the height of each bar being proportional to the average Friedman ranking obtained for the representative algorithm. We chose the smallest of them (corresponding to the best/control algorithm, i.e., here DENMO), and we summed its height and the critical difference obtained by the Bonferroni–Dunn test. The result is represented by a cut-line going through all the bars. Then we can conclude that the behaviors of the algorithms characterized by the bars above the cut-line are significantly inferior to the behavior of the control algorithm. Only for DEMON and NSGA-II-A the null hypothesis cannot be rejected with any of the tests for {a mathematical formula}α=0.05 for all four metrics. However, the other seven algorithms may be regarded as significantly poorer than DENMO with a level of significance {a mathematical formula}α=0.05.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>