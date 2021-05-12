<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Efficient nonconvex sparse group feature selection via continuous and discrete optimization.
   </title>
   <abstract>
    Sparse feature selection has proven to be effective in analyzing high-dimensional data. While promising, most existing works apply convex methods, which may be suboptimal in terms of the accuracy of feature selection and parameter estimation. In this paper, we consider both continuous and discrete nonconvex paradigms to sparse group feature selection, which are motivated by applications that require identifying the underlying group structure and performing feature selection simultaneously. The main contribution of this article is twofold: (1) computationally, we develop efficient optimization algorithms for both continuous and discrete formulations, of which the key step is a projection with two coupled constraints; (2) statistically, we show that the proposed continuous model reconstructs the oracle estimator. Therefore, consistent feature selection and parameter estimation are achieved simultaneously. Numerical results on synthetic and real-world data suggest that the proposed nonconvex methods compare favorably against their competitors, thus achieving desired goal of delivering high performance.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      During the past decade, sparse feature selection has been extensively investigated, on both optimization algorithms [1] and statistical properties [39], [52], [4]. When the data possesses certain group structure, sparse modeling has been explored in [49], [30], [21], [47] for group feature selection. The group lasso [49], [40] proposes an {a mathematical formula}L2-regularization method for each group, which ultimately yields a group-wisely sparse model. The utility of such a method has been demonstrated in detecting splice sites [48]—an important step in gene finding and theoretically justified in [21]. The sparse group lasso [17] enables to encourage sparsity at the level of both features and groups simultaneously. In the literature, most approaches use convex methods to pursue the grouping effect due to globality of the solution and tractable computation. However, this may lead to suboptimal results. Recent studies demonstrate that nonconvex methods [14], [42], [8], [20], [22], particularly the truncated {a mathematical formula}L1-penalty [35], [29], [51], may deliver superior performance than the standard {a mathematical formula}L1-formulation. In addition, [36] suggests that a constrained nonconvex formulation is slightly more preferable than its regularization counterpart in terms of the capability of feature selection. In this paper, we investigate the sparse group feature selection through a constrained nonconvex formulation. Ideally, we wish to optimize the following {a mathematical formula}L0-model:{a mathematical formula} where A is an n by p data matrix with its columns representing different features. {a mathematical formula}x=(x1,⋯,xp) is partitioned into {a mathematical formula}|G| non-overlapping groups {a mathematical formula}{xGi} and {a mathematical formula}I(⋅) is the indicator function. The advantage of the {a mathematical formula}L0-model (1) lies in its complete control on two levels of sparsity {a mathematical formula}(s1,s2), which are the numbers of features and groups respectively. However, problems such like (1) are known to be NP-hard [31] because of the discrete nature.
     </paragraph>
     <paragraph>
      We develop two methods for the sparse group feature selection problem. The first method makes use of a continuous computational surrogate of the {a mathematical formula}L0-method described above, and has theoretically guaranteed performance. On the contrary, the second proposed method retains the discrete nature and the key is to solve a sparse group subset selection problem via dynamic programming. We develop efficient algorithms for both methods. In addition, we explore the statistical properties of the first method; specifically we show that the proposed method retains the merits of the {a mathematical formula}L0-approach (1) in the sense that the oracle estimator can be reconstructed, which leads to consistent feature selection and parameter estimation. An earlier version of this paper [45] containing only the first approach was accepted by the 30th International Conference on Machine Learning (ICML).
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. Section 2 presents our continuous optimization approach, in which a nonconvex formulation with its optimization algorithm and theoretical properties are explored. The discrete optimization approach is discussed in Section 3, where we transform the key projection into a discrete sparse group subset selection problem and develop a dynamic programming algorithm to compute the globally optimal solution. The significance of this work is presented in Section 4. Section 5 demonstrates the efficiency of the proposed methods as well as the performance on real-world applications. Section 6 concludes the paper with a discussion of future research.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Continuous optimization approach
     </section-title>
     <paragraph>
      One major difficulty of solving (1) comes from nonconvex and discrete constraints, which require enumerating all possible combinations of features and groups to achieve the optimal solution. Therefore we approximate these constraints by their continuous computational surrogates:{a mathematical formula} where {a mathematical formula}Jτ(z)=min⁡(|z|/τ,1) is a truncated {a mathematical formula}L1-function approximating the {a mathematical formula}L0-function [35], [50], and {a mathematical formula}τ&gt;0 is a tuning parameter such that {a mathematical formula}Jτ(z) approximates the indicator function {a mathematical formula}I(|z|≠0) as τ approaches zero.
     </paragraph>
     <paragraph>
      To solve the nonconvex problem (2), we develop a Difference of Convex (DC) algorithm [38] based on a decomposition of each nonconvex constraint function into a difference of two convex functions:{a mathematical formula} where{a mathematical formula} are convex in x. Then each trailing convex function, say {a mathematical formula}S2(x), is replaced by its affine minorant at the previous iteration{a mathematical formula} where g is a subgradient of {a mathematical formula}S2 at {a mathematical formula}xˆ(m−1) and an upper approximation of the constraint function {a mathematical formula}∑j=1pJτ(|xj|) can be obtained as follows:{a mathematical formula} Similarly, the second nonconvex constraint in (2) can be approximated by{a mathematical formula} Note that both (4) and (5) are convex constraints, which result in a convex subproblem as follows:{a mathematical formula} where {a mathematical formula}T1, {a mathematical formula}T2 and {a mathematical formula}T3 are the support sets{sup:1} defined as:{a mathematical formula}{a mathematical formula}‖xT1‖1 and {a mathematical formula}‖xT3‖G denote the corresponding value restricted on {a mathematical formula}T1 and {a mathematical formula}T3 respectively, and {a mathematical formula}‖x‖G=∑i=1|G|‖xGi‖2. Solving (6) would provide us an updated solution, denoted as {a mathematical formula}xˆ(m), which leads to a refined formulation of (6). Such procedure is iterated until the objective value stops decreasing. The DC algorithm is summarized in Algorithm 1, from which we can see that efficient computation of (6) is critical to the overall DC routine. We defer detailed discussion of this part to Section 2.1.
     </paragraph>
     <section label="2.1">
      <section-title>
       Optimization procedures
      </section-title>
      <paragraph>
       As mentioned in our previous discussion, efficient computation of the convex subproblem (6) is of critical importance for the proposed DC algorithm. Note that (6) has an identical form of the constrained sparse group lasso problem:{a mathematical formula} except that x is restricted to the two support sets. As to be shown in Section 2.1.3, an algorithm for solving (6) can be obtained through only a few modifications on that of (7). Therefore, we first focus on solving (7). Notice that if problem (7) has only one constraint, the solution is well-established [13], [1]. However, the two coupled constraints here make the optimization problem more challenging to solve.
      </paragraph>
      <section label="2.1.1">
       <section-title>
        Accelerated gradient method
       </section-title>
       <paragraph>
        For large-scale problems, the dimensionality of data can be very high, therefore first-order optimization is often preferred. We adapt the well-known accelerated gradient method (AGM) [32], [3], which is commonly used due to its fast convergence rate.
       </paragraph>
       <paragraph>
        To apply AGM to our formulation (7), the crucial step is to solve the following Sparse Group Lasso Projection (SGLP):{a mathematical formula} which is a Euclidean projection onto a convex set and a special case of (7) when A is the identity. For convenience, let {a mathematical formula}C1 and {a mathematical formula}C2 denote the above two constraints in what follows.
       </paragraph>
       <paragraph>
        Since the AGM is a standard framework whose efficiency mainly depends on that of the projection step, we leave the detailed description of AGM in Appendix A Proof of, Appendix B Proof of, Appendix C Accelerated gradient method, Appendix D Algorithm for solving, Appendix E The ADMM projection algorithm, Appendix F Dykstra's algorithm, Appendix G Proof of and introduce the efficient algorithm for this projection step (8).
       </paragraph>
      </section>
      <section label="2.1.2">
       <section-title>
        Efficient projection
       </section-title>
       <paragraph>
        We begin with some special cases of (8). If only {a mathematical formula}C1 exists, (8) becomes the well-known {a mathematical formula}L1-ball projection [13], [9], whose optimal solution is denoted as {a mathematical formula}P1s1(v), standing for the projection of v onto the {a mathematical formula}L1-ball with radius {a mathematical formula}s1. On the other hand, if only {a mathematical formula}C2 is involved, it becomes the group lasso projection, denoted as {a mathematical formula}PGs2. Moreover, we say a constraint is active, if and only if an equality holds at the optimal solution {a mathematical formula}x⁎; otherwise, it is inactive.
       </paragraph>
       <paragraph>
        Preliminary results are summarized in Lemma 1:
       </paragraph>
       <paragraph label="Lemma 1">
        Denote a global minimizer of(8)as{a mathematical formula}x⁎. Then the following results hold:
       </paragraph>
       <list>
        <list-item label="1.">
         If both{a mathematical formula}C1and{a mathematical formula}C2are inactive, then{a mathematical formula}x⁎=v.
        </list-item>
        <list-item label="2.">
         If{a mathematical formula}C1is the only active constraint, i.e.,{a mathematical formula}‖x⁎‖1=s1,{a mathematical formula}‖x⁎‖G&lt;s2, then{a mathematical formula}x⁎=P1s1(v).
        </list-item>
        <list-item label="3.">
         If{a mathematical formula}C2is the only active constraint, i.e.,{a mathematical formula}‖x⁎‖1&lt;s1,{a mathematical formula}‖x⁎‖G=s2, then{a mathematical formula}x⁎=PGs2(v).
        </list-item>
       </list>
       <paragraph>
        Computing{a mathematical formula}x⁎from the optimal dual variables:Lemma 1 describes a global minimizer when either constraint is inactive. Next we consider the case in which both {a mathematical formula}C1 and {a mathematical formula}C2 are active. By the convex duality theory [7], there exist unique non-negative dual variables {a mathematical formula}λ⁎ and {a mathematical formula}η⁎ such that {a mathematical formula}x⁎ is also the global minimizer of the following regularized problem:{a mathematical formula} whose solution is given by the following theorem.
       </paragraph>
       <paragraph label="Theorem 1">
        (See[17].) The optimal solution{a mathematical formula}x⁎of(9)is given by{a mathematical formula}where{a mathematical formula}vGiλ⁎is computed via soft-thresholding[12]{a mathematical formula}vGiwith threshold{a mathematical formula}λ⁎as follows:{a mathematical formula}where{a mathematical formula}SGN(⋅)is the sign function and all the operations are taken element-wisely.
       </paragraph>
       <paragraph>
        Theorem 1 gives an analytical solution of {a mathematical formula}x⁎ in an ideal situation when the values of {a mathematical formula}λ⁎ and {a mathematical formula}η⁎ are given. Unfortunately, this is not the case and the values of {a mathematical formula}λ⁎ and {a mathematical formula}η⁎ need to be computed directly from (8). Based on Theorem 1, we have the following conclusion characterizing the relations between the dual variables:
       </paragraph>
       <paragraph label="Corollary 1">
        The following equations hold:{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Suppose {a mathematical formula}λ⁎ is given, then computing {a mathematical formula}η⁎ from (12) amounts to solving a median finding problem, which can be done in linear time [13].
       </paragraph>
       <paragraph>
        Finally, we treat the case of unknown {a mathematical formula}λ⁎ (thus unknown {a mathematical formula}η⁎). We propose an efficient bisection approach to compute it.
       </paragraph>
       <paragraph>
        Computing{a mathematical formula}λ⁎via bisection: Given an initial guess (estimator) of {a mathematical formula}λ⁎, says {a mathematical formula}λˆ, one may perform bisection to locate the optimal {a mathematical formula}λ⁎, provided that there exists an oracle procedure indicating if the optimal value is greater than {a mathematical formula}λˆ.{sup:2} This bisection method can estimate {a mathematical formula}λ⁎ in logarithm time. Next, we shall design an oracle procedure.
       </paragraph>
       <paragraph>
        Let the triples{a mathematical formula} be the optimal solution of (8) with both constraints active, i.e., {a mathematical formula}‖x⁎‖1=s1, {a mathematical formula}‖x⁎‖G=s2, with {a mathematical formula}(λ⁎,η⁎) be the optimal dual variables. Consider the following two sparse group lasso projections:{a mathematical formula}{a mathematical formula} The following key result holds.
       </paragraph>
       <paragraph label="Theorem 2">
        If{a mathematical formula}λ≤λ′and{a mathematical formula}s2=s2′, then{a mathematical formula}s1≥s1′.
       </paragraph>
       <paragraph>
        We give the proof of Theorem 2 by presenting a more general conclusion.
       </paragraph>
       <paragraph label="Lemma 2">
        Let{a mathematical formula}Ω⊂Rnand consider the following optimization problem:{a mathematical formula}where g is non-negative. Let{a mathematical formula}x1and{a mathematical formula}x2be the optimal solution of this optimization problem with{a mathematical formula}λ=λ1and{a mathematical formula}λ=λ2respectively and suppose{a mathematical formula}λ1&lt;λ2. Then we have:
       </paragraph>
       <list>
        <list-item label="1.">
         {a mathematical formula}g(x1)≥g(x2).
        </list-item>
        <list-item label="2.">
         {a mathematical formula}F(x1)≤F(x2).
        </list-item>
        <list-item label="3.">
         {a mathematical formula}f(x1)≤f(x2).
        </list-item>
       </list>
       <paragraph label="Proof">
        From the optimality of {a mathematical formula}x1 and {a mathematical formula}x2 we can obtain:{a mathematical formula}{a mathematical formula} Add the above two equalities leads to {a mathematical formula}(λ1−λ2)(g(x1)−g(x2))≤0 which proves the first result. The second conclusion can be shown in the following relation, where we use the non-negativity of g in the second inequality:{a mathematical formula} The third conclusion follows directly from the first two results.  □
       </paragraph>
       <paragraph label="Proof of Theorem 2">
        Let {a mathematical formula}Ω={x:‖x‖G=s2}, {a mathematical formula}g(x)=‖x‖1 and applying Lemma 2 gives the result.  □
       </paragraph>
       <paragraph>
        Theorem 2 gives exactly the oracle procedure we need. For a given estimator {a mathematical formula}λˆ, we compute its corresponding {a mathematical formula}ηˆ from (12) and then {a mathematical formula}s1ˆ from (11), satisfying {a mathematical formula}(xˆ,λˆ,ηˆ)=SGLP(v,s1ˆ,s2). Then {a mathematical formula}s1ˆ is compared with {a mathematical formula}s1. Clearly, by Theorem 2, if {a mathematical formula}s1ˆ≤s1, the estimator {a mathematical formula}λˆ is no less than {a mathematical formula}λ⁎. Otherwise, {a mathematical formula}s1ˆ&gt;s1 means {a mathematical formula}λˆ&lt;λ⁎. In addition, from (11) we know that {a mathematical formula}s1ˆ is a continuous function of {a mathematical formula}λˆ. Together with the monotonicity given in Theorem 2, a bisection approach can be employed to calculate {a mathematical formula}λ⁎. Algorithm 2 gives a detailed description of this bisection procedure and Algorithm 3 summarizes the entire projection method.
       </paragraph>
       <paragraph label="Remark">
        In Su et al.'s work [37], the authors develop similar bisection algorithm for solving Problem (8). However, both works are accomplished independently and are publicly available around the same time.
       </paragraph>
      </section>
      <section label="2.1.3">
       Solving restricted version of (7)
       <paragraph>
        Finally, we modify the above procedures to compute the optimal solution of the restricted problem (6). To apply the accelerated gradient method, we consider the following projection step:{a mathematical formula}
       </paragraph>
       <paragraph>
        Our first observation is: {a mathematical formula}T3(x)⊂T1(x), since if an element of x lies in a group whose {a mathematical formula}L2-norm is less than τ, then the absolute value of this element must also be less than τ. Secondly, from the decomposable nature of the objective function, we conclude that:{a mathematical formula} since there are no constraints on {a mathematical formula}xj if it is outside {a mathematical formula}T1 and involves only the {a mathematical formula}L1-norm constraint if {a mathematical formula}j∈T1\T3. Following routine calculations as in [13], we obtain the following results similar to (11) and (12):{a mathematical formula}{a mathematical formula}
       </paragraph>
       <paragraph>
        Based on (14) and (15), we design a similar bisection approach to compute {a mathematical formula}λ⁎ and thus {a mathematical formula}(x⁎)T3, as in Algorithm 3. Details can be found in Appendix A Proof of, Appendix B Proof of, Appendix C Accelerated gradient method, Appendix D Algorithm for solving, Appendix E The ADMM projection algorithm, Appendix F Dykstra's algorithm, Appendix G Proof of.
       </paragraph>
       <paragraph>
        Since the projection (13) does not possess a closed-form, it is instructive to discuss the convergence property of overall accelerated gradient method. Follow the discussion in [34], we can provide sufficient conditions for a guaranteed convergence rate. Moreover, we found in practice that a reasonable convergence property can be obtained as long as the precision level for the computation of the projection is small, as revealed in Section 5.
       </paragraph>
       <paragraph label="Remark">
        Problem (7) can also be solved using the Alternating Direction Method of Multiplier (ADMM) [6] instead of the accelerated gradient method (AGM). However, our evaluations show that AGM with our projection algorithm is more efficient than ADMM.
       </paragraph>
      </section>
     </section>
     <section label="2.2">
      <section-title>
       Theoretical results
      </section-title>
      <paragraph>
       This section investigates theoretical aspects of the proposed method. More specifically, we show that the oracle estimator {a mathematical formula}xˆo, the least squares estimator based on the true model, can be reconstructed by a global minimizer of (2). As a result, consistent selection as well as optimal parameter estimation can be achieved by our method.
      </paragraph>
      <paragraph>
       For presentation, we introduce some notations to be used subsequently. Let {a mathematical formula}G=(Gi1,⋯,Gik) be a collection of groups, each containing nonzero elements. Let {a mathematical formula}BGj=BGj(x) and {a mathematical formula}BG=BG(x) denote the indices of nonzero elements of x in {a mathematical formula}Gj and x, respectively. Define{a mathematical formula} where {a mathematical formula}S is a feasible region of (2) and {a mathematical formula}G0 represents the true nonzero groups.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}s10, {a mathematical formula}G0 and {a mathematical formula}x0 denote the true nonzero features, the true nonzero groups and the true parameter under {a mathematical formula}G0. The following conditions are assumed to establish consistent reconstruction of the oracle estimator:
      </paragraph>
      <paragraph label="Assumption 1">
       Degree of group separationDefine{a mathematical formula} then for some constant {a mathematical formula}c1&gt;0,{a mathematical formula} where{a mathematical formula} is the Hellinger-distance for densities with respect to a dominating measure μ.
      </paragraph>
      <paragraph>
       Assumption 1 requires that the degree of separation {a mathematical formula}Cmin(x0), as measured by the Hellinger-distance, exceeds a certain thresholding level, given by {a mathematical formula}c1log⁡|G0|+log⁡s10n. In other words, it assumes that the underlying groups have a certain degree of separability so that these groups can be well-estimated by data, where the thresholding level quantifies the requirement. Note that this thresholding level is proportional to the logarithm of the true group size {a mathematical formula}|G| over n and logarithm of the true degree of the {a mathematical formula}L0 sparsity over n.
      </paragraph>
      <paragraph label="Assumption 2">
       Complexity of the parameter spaceFor some constants {a mathematical formula}c0&gt;0 and any {a mathematical formula}0&lt;t&lt;ε≤1,{a mathematical formula} where {a mathematical formula}Bj,i=Sj,i∩{x∈h(x,x0)≤2ε} is a local parameter space and {a mathematical formula}Fj,i={g1/2(x,y):x∈Bj,i} is a collection of square-root densities. {a mathematical formula}H(⋅,F) is the bracketing Hellinger metric entropy of space {a mathematical formula}F[24].
      </paragraph>
      <paragraph>
       Assumption 2 concerns the complexity of the parameter space, which is defined by the metric entropy. Such a requirement is often used in parameter estimation in the statistics literature [35].
      </paragraph>
      <paragraph label="Assumption 3">
       For some positive constants {a mathematical formula}d1,d2,d3 with {a mathematical formula}d1&gt;10,{a mathematical formula} where {a mathematical formula}xτ=(x1I(|x1|≥τ),⋯,xpI(|xp|≥τ)).
      </paragraph>
      <paragraph>
       Assumption 3 quantifies the degree of approximation of {a mathematical formula}Jτ(⋅) to the {a mathematical formula}L0-function with respect to τ in terms of the Hellinger-distance. Under these assumptions, we derive a non-asymptotic error bound regarding the reconstruction of the oracle estimator {a mathematical formula}xˆo. The proof is provided in Appendix A Proof of, Appendix B Proof of, Appendix C Accelerated gradient method, Appendix D Algorithm for solving, Appendix E The ADMM projection algorithm, Appendix F Dykstra's algorithm, Appendix G Proof of.
      </paragraph>
      <paragraph label="Theorem 3">
       Suppose thatAssumption 2, Assumption 3hold. For a global minimizer of(2){a mathematical formula}xˆwith{a mathematical formula}(s1,s2)=(s10,s20)and{a mathematical formula}τ≤((d1−10)Cmin(x0)d3d)1/d2, the following result holds:{a mathematical formula}Moreover, underAssumption 1,{a mathematical formula}P(xˆ=xˆo)→1and{a mathematical formula}as{a mathematical formula}n→∞,{a mathematical formula}|G0|→∞.
      </paragraph>
      <paragraph>
       Theorem 3 says that the oracle estimator {a mathematical formula}xˆo can be accurately reconstructed, which in turn yields feature selection consistency as well as the recovery of the optimal performance of the oracle estimator in the Hellinger-distance in (16). Moreover, as indicated in Assumption 1, the asymptotic result in Theorem 3 holds when {a mathematical formula}s10|G0| grows in the order of {a mathematical formula}exp⁡(c1−1nCmin). This is in contrast to existing results on consistent feature selection, where the number of candidate features should be no greater than {a mathematical formula}exp⁡(c⁎n) for some {a mathematical formula}c⁎[52], [42]. In this sense, the number of candidate features is allowed to be much larger when an additional group structure is assumed, particularly when each group contains a large number of redundant features. It remains unclear whether such a result continues to hold for other bi-level{sup:3} variable selection methods, such as the composite MCP [20] and group bridge [8].
      </paragraph>
      <paragraph>
       To our knowledge, our theory for the grouped selection is the first of this kind. However, it has a root in feature selection. The large deviation approach used here is applicable to derive bounds for feature selection consistency. In such a situation, the result agrees with the necessary condition for feature selection consistency for any method, except for the constants independent of the sample size [35]. In other words, the required conditions are weaker than those for {a mathematical formula}L1-regularization commonly used in the literature [41]. The use of the Hellinger-distance is to avoid specifying a sub-Gaussian tail of the random error. This means that the result continues to hold even when the error does not have a sub-Gaussian tail. This is because of the one-sided property of the likelihood ratios [43].
      </paragraph>
      <paragraph label="Remark">
       Although we require {a mathematical formula}xˆ to be a global minimizer of (2), a weaker version of the theory can be derived for a local minimizer obtained from the DC programming by following similar derivations in [36], and will not pursue this direction in here.
      </paragraph>
      <paragraph>
       Now we consider a special case that the random error follows a Gaussian distribution. Specifically assume the response vector y of n observations follows a linear model as follows:{a mathematical formula} where the random vector ε follows {a mathematical formula}N(0,σ2I). We can obtain a simplified version of Theorem 3 where both of the {a mathematical formula}L2-norm and Hellinger-distance can be applied.
      </paragraph>
      <paragraph label="Proposition 1">
       Under the linear model(17), suppose x is uniformly bounded away from infinity and{a mathematical formula}for some constant{a mathematical formula}c1&gt;0, where{a mathematical formula}γminis the smallest absolute nonzero element of{a mathematical formula}x0, and{a mathematical formula}ΣBis the covariance matrix indexed by subset B, and{a mathematical formula}cminis a minimum eigen-value of a matrix. Then all the results inTheorem 3hold for both of the Hellinger-distance and the{a mathematical formula}L2-norm.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      Discrete optimization approach
     </section-title>
     <paragraph>
      Motivated by the iterative hard thresholding algorithm for {a mathematical formula}ℓ0-regularized problems [5], [28] and the recent advances on nonconvex iterative shrinkage algorithm [18], we adopt the Iterative Shrinkage and Thresholding Algorithm (ISTA) framework and propose the following algorithm for solving Problem (1).
     </paragraph>
     <paragraph>
      In the proposed algorithm above, f denotes the objective function and the “SGHT” in Algorithm 4 stands for the following Sparse Group Hard Thresholding (SGHT) problem with v as the input:{a mathematical formula}
     </paragraph>
     <paragraph>
      Like most ISTA-based optimization algorithms, it is of critical importance that we can compute the proximal/projection step accurately and efficiently. In our case, the key part is exactly the SGHT problem. Although there are well-established results on hard thresholding algorithms for {a mathematical formula}ℓ0-regularization, adding one more constraint on group cardinality greatly complicates the problem and requires deeper analysis. We develop a novel combinatorial optimization algorithm based on dynamic programming and we show that it is capable of finding a global optimum efficiently.
     </paragraph>
     <section label="3.1">
      <section-title>
       Optimal solution for the sparse group hard thresholding problem
      </section-title>
      <paragraph>
       Before presenting our algorithm, we first explore some key properties of Problem (18). As highlighted previously, the major challenge comes from the two coupled constraints. Therefore, we first consider the special case where only one of the two constraints is present. Some straight-forward analysis leads to the following results:
      </paragraph>
      <paragraph label="Lemma 3">
       If only the cardinality constraint is present, the optimal solution of Problem(18)can be obtained by setting the{a mathematical formula}p−s1smallest (in absolute value) elements of v to zero. Similarly for group cardinality constraint, it suffices to find the{a mathematical formula}|G|−s2smallest groups (in{a mathematical formula}ℓ2-norm) and set them to zero.
      </paragraph>
      <paragraph>
       Based on Lemma 3, it is also easy to verify that for any optimal solution {a mathematical formula}x⁎ of Problem (18), each element {a mathematical formula}xi⁎ is either equal to {a mathematical formula}vi or zero, where the subscript i denotes the ith element of the vector. Therefore we have the following proposition providing an equivalent but discrete characterization of the original SGHT problem:
      </paragraph>
      <paragraph label="Proposition 2">
       Finding the optimal solution of problem(18)is equivalent to the following Sparse Group Subset Selection (SGSS) problem:Given a set S on which a nonnegative value function f is defined.{a mathematical formula}C={C1,C2,⋯,C|G|}is a collection of disjoint subsets of S such that{a mathematical formula}S=⋃i=1|G|Ci. Find a subset{a mathematical formula}S′⊂Swith the maximum value such that the cardinality of S is no more than{a mathematical formula}s1and{a mathematical formula}S′has nonempty intersections with at most{a mathematical formula}s2elements from C. The value of a subset is defined as the summation of all the values of its elements.
      </paragraph>
      <paragraph>
       We claim that the SGHT has an optimal solution if and only if we can find an optimal solution for the SGSS problem. We provide a one-way reduction (the “if” part) here. The other way is almost identical. The original SGHT problem can be reduced to SGSS by simply setting {a mathematical formula}S={1,2,⋯,p} with the value function defined as {a mathematical formula}f(i)=vi2 for all {a mathematical formula}1≤i≤p and {a mathematical formula}Ci=Gi for all {a mathematical formula}1≤i≤|G|. Suppose {a mathematical formula}S′ is the optimal solution of SGSS. Then the optimal solution of SGHT can be readily obtained via:{a mathematical formula}
      </paragraph>
      <paragraph>
       In the sequel, we will focus on the SGSS problem and provide an efficient algorithm to compute its globally optimal solution. The term cardinality and group cardinality are used to characterize the size of {a mathematical formula}S′ and the number of elements from C with which {a mathematical formula}S′ has a nonempty intersection, respectively.
      </paragraph>
      <paragraph>
       Let {a mathematical formula}T(i,j,k) denote the maximum value we can obtain by choosing a subset {a mathematical formula}S′, whose cardinality is no more than k and group cardinality is at most j. In addition, {a mathematical formula}S′ is only allowed to have nonempty intersection with {a mathematical formula}C1,C2,⋯,Ci. Therefore T is in essence a three-dimensional table of size {a mathematical formula}(|G|+1)×(s2+1)×(s1+1) (the table is zero-indexed). It is easy to verify that, if we are able to compute all the values in table T correctly, the maximum value one can get in the SGSS problem is given by {a mathematical formula}T(|G|,s2,s1).
      </paragraph>
      <paragraph>
       Next we propose a dynamic programming algorithm to compute the table T. The motivation behind our method is the existence of optimal substructure and overlapping subproblems [26], two major ingredients for an efficient dynamic programming algorithm. More specifically, when we try to compute {a mathematical formula}T(i,j,k), the optimal solution must fall into one of the two situations: whether the {a mathematical formula}Ci is selected or not. If not, we can simply conclude that {a mathematical formula}T(i,j,k)=T(i−1,j,k). On the other hand, if {a mathematical formula}Ci is selected, we need to determine how many elements from {a mathematical formula}Ci are included in the optimal solution. Suppose the optimal solution takes t elements from {a mathematical formula}Ci, then we must have {a mathematical formula}T(i,j,k)=T(i−1,j−1,k−t)+CH(i,t), where {a mathematical formula}CH(i,t) denotes the maximum value one can get from choosing t elements out of {a mathematical formula}Ci. The optimal t can be computed via enumeration. To sum up, the computation of {a mathematical formula}T(i,j,k) can be written in the following recursive form:{a mathematical formula}
      </paragraph>
      <paragraph>
       It is clear from above that {a mathematical formula}T(i,j,k) can be computed using only the values in the table T with smaller indices. Therefore we can compute each element of the table T in increasing order for each index; see Fig. 1 for more detail. In addition, to further reduce the complexity, function {a mathematical formula}CH(i,t) can be precomputed before the dynamic programming process. We present the detailed description of the proposed method in Algorithm 5. From table T, we are able to calculate the minimum objective value of the SGHT problem, which is exactly {a mathematical formula}12(‖v‖22−T(|G|,s2,s1)). In order to calculate the optimal solution {a mathematical formula}x⁎, all we need to know is the indices of selected elements in S and the optimal solution can be constructed through Eq. (19). We compute such information by adding one table P (stands for path) in the proposed algorithm. Specifically, {a mathematical formula}P(i,j,k)=0 means the {a mathematical formula}Ci is not selected in the computation of {a mathematical formula}T(i,j,k). Otherwise we set{a mathematical formula} which is just the number of selected features in the ith group ({a mathematical formula}Ci) in the optimal solution. To recover the indices of all the selected elements, we will start from {a mathematical formula}P(|G|,s2,s1) with a backtracking procedure and record the number of selected elements in each group. Algorithm 6 provides a formal description of this process. It accepts the table P as input and returns the cnt table which contains the number of selected elements in each group. Finally computing the optimal {a mathematical formula}x⁎ only amounts to keeping the top selected elements for each group and setting the remains to zero.
      </paragraph>
      <paragraph>
       We analyze the time complexity of our proposed algorithm as follows. Notice that the time needed to precompute the table CH is given by:{a mathematical formula} the dynamic programming part for computing both T and P takes{a mathematical formula} and the backtracking needs clearly {a mathematical formula}O(|G|) operations. Therefore the overall time complexity is{a mathematical formula} When the number of features and feature groups selected is small, the SGHT problem can be solved efficiently.
      </paragraph>
      <paragraph label="Remark">
       In R. Jenatton et al.'s work [23], the authors show that the regularization model that involves similar grouping structures also admits a global solution via dynamic programming. The difference is that our method focuses on solving the discrete optimization directly while the other paper deals with the convex relaxation. In addition, they show that their algorithm possesses a one-pass convergence for only {a mathematical formula}ℓ2 and {a mathematical formula}ℓ∞-norm (Section 3.3).
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Variants of the optimization framework
      </section-title>
      <paragraph>
       In order to get more insight into the dominating factors for performance, we consider several variants of our optimization framework proposed in Algorithm 4. Notice that the target of Algorithm 4 is a nonconvex optimization problem. This means that change of options such as initialization, step-size, not only will provide different convergence behavior, but also could lead to completely different solution. This again justifies the necessity of our investigations. We consider three aspects in this paper: step-size initialization, line search criterion and acceleration option.
      </paragraph>
      <section label="3.2.1">
       <section-title>
        Step-size initialization
       </section-title>
       <paragraph>
        To provide an initial value of the step-size (Line 6. in Algorithm 4), we consider both using a constant value and applying the Barzilai–Borwein (BB) method [2]. The BB method essentially finds the best multiple of identity matrix to approximate the Hessian matrix such that the least squares error of the secant equation is minimized, i.e., {a mathematical formula}Lk is initialized to{a mathematical formula} with a safeguard bound, where {a mathematical formula}Δg=∇f(xk)−∇f(xk−1) and {a mathematical formula}Δx=xk−xk−1. In this paper, we set {a mathematical formula}Lk=max⁡(1,αk).
       </paragraph>
      </section>
      <section label="3.2.2">
       <section-title>
        Line search criterion
       </section-title>
       <paragraph>
        We consider two line search termination criteria in this paper, which we name as Lipschiz criterion and sufficient decrease criterion. Specifically the Lipschiz criterion finds such an L that the following inequality is satisfied:{a mathematical formula}
       </paragraph>
       <paragraph>
        On the other hand, the sufficient decrease criterion aims to find the smallest L such that:{a mathematical formula}
       </paragraph>
       <paragraph>
        Inequality (20) is the standard way for {a mathematical formula}ℓ1-regularized optimization [3] and is applied extensively in structured sparse learning [27]. Inequality (21) and its variants are favored by most of the recent investigations on nonconvex regularized problems [44], [18].
       </paragraph>
      </section>
      <section label="3.2.3">
       <section-title>
        Acceleration option
       </section-title>
       <paragraph>
        The ISTA framework has been shown to possess a convergence rate of {a mathematical formula}O(1/k) for a class of {a mathematical formula}ℓ1-regularized/constrained optimization problems and can be further improved to {a mathematical formula}O(1/k2) via adding a carefully designed search point [3]. However, whether the same strategy still works or makes the optimization diverge in the regime of nonconvex optimization remains unknown. In this paper we consider both of them and retain the notation of FISTA [3] to denote the ISTA with the acceleration trick. See Algorithm 7 for more detail about our FISTA.
       </paragraph>
       <paragraph>
        Table 1 summarizes the different variants we considered in this paper. All these variants will be examined in our experiment part.
       </paragraph>
      </section>
     </section>
     <section label="3.3">
      <section-title>
       Convergence analysis
      </section-title>
      <paragraph>
       In this section, knowing that the key SGHT sub-problem can be efficiently computed, we assess the quality of the solution produced by the overall optimization procedure (Algorithm 4). Specifically, since the constraints of Eq. (1) are nonconvex and only a local minimum can be found through our proposed method, we are interested in studying how close (in terms of Euclidean distance) the obtained solution to the optimal solution of the optimization problem (1). Although we are not aware of the optimal solution, the bound between our solution and the optimal one can be analyzed under the theoretical framework of restricted isometry property (RIP) [10]. A matrix {a mathematical formula}A∈Rn×p is said to satisfy the RIP property with constant {a mathematical formula}δs if the following property holds for any s-sparse vector x, i.e., {a mathematical formula}‖x‖0≤s:{a mathematical formula}
      </paragraph>
      <paragraph>
       The RIP constant essentially assesses the extent to which the given matrix resembles an orthogonal matrix and theoretical analyses often require certain upperbound on the RIP constant. It is easy to see that {a mathematical formula}δs is non-decreasing w.r.t. s and a smaller value of {a mathematical formula}δs indicates more rigid conditions we require from A. In order to apply the RIP based analysis for our method, a group-RIP constant is introduced to incorporate the group structure. Matrix A has a group-RIP constant {a mathematical formula}δg if for any vector x that spans no more than g groups, i.e., {a mathematical formula}∑j=1|G|I(‖xGj‖2≠0)≤g, the following relation are satisfied:{a mathematical formula}
      </paragraph>
      <paragraph>
       Our next result provides an error bound between an optimal solution of Problem (1) and the solution produced by our proposed Algorithm 4 with L fixed to 1.
      </paragraph>
      <paragraph label="Theorem 4">
       Let{a mathematical formula}x⁎be a globally optimal solution of Problem(1)and{a mathematical formula}xkbe the solution we obtain after the kth iteration inAlgorithm 4with{a mathematical formula}L=1. If{a mathematical formula}c1&lt;12, the following result holds:{a mathematical formula}where{a mathematical formula}e⁎=y−Ax⁎,{a mathematical formula}c1=min⁡{δ3s1,δ3s2},{a mathematical formula}c2=min⁡{δ2s1,δ2s2}. In addition, if{a mathematical formula}c2&lt;14, it is also true that:{a mathematical formula}
      </paragraph>
      <paragraph>
       Theorem 4 clearly shows that the parameter estimation error of the proposed algorithm decreases linearly (with coefficient of {a mathematical formula}2c1 or {a mathematical formula}4c2) till a fixed error term is met. In addition, such an error term is proportional to the prediction error of the optimal solution of Problem (1). The proof of Theorem 4 mainly utilizes the technique in [15] and the details are left in Appendix A Proof of, Appendix B Proof of, Appendix C Accelerated gradient method, Appendix D Algorithm for solving, Appendix E The ADMM projection algorithm, Appendix F Dykstra's algorithm, Appendix G Proof of. We provide an illustrative example of the convergence procedure in Fig. 2: if the assumptions on the (group) RIP constant hold, the sequence generated by running our algorithm is guaranteed to converge into a region centered at {a mathematical formula}x⁎ with radius at most {a mathematical formula}c‖e⁎‖2, where c is a constant. As we can observe from Fig. 2 and Theorem 4, the difference between the unknown globally optimal solution of Problem (1) and ours is upperbounded by a multiple of the underlying error term {a mathematical formula}‖e⁎‖2. In addition, such a difference cannot be canceled unless we have {a mathematical formula}e⁎=0, in which case Theorem 4 essentially states that our method admits a linear convergence rate [33].
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Discussions
     </section-title>
     <paragraph>
      This section is devoted to a brief discussion of advantages of our work statistically and computationally. Moreover, it explains why the proposed methods is useful to perform efficient and interpretable feature selection given a natural group structure.
     </paragraph>
     <paragraph>
      Interpretability. The parameters in both of the two proposed methods are highly interpretable in that {a mathematical formula}s1 and {a mathematical formula}s2 are upper bounds of the number of nonzero elements as well as that of groups. This is advantageous, especially in the presence of certain prior knowledge regarding the number of features and/or that of groups. However, such an interpretation vanishes with other (convex &amp; nonconvex) methods such as lasso, sparse group lasso, composite MCP or group bridge, in which incorporating such prior knowledge often requires repeated trials of different parameters.
     </paragraph>
     <paragraph>
      Parameter tuning. Typically, tuning parameters for good generalization usually requires considerable amount work due to a large number of choices of parameters. However, parameter tuning in model (1) may search through integer values in a bounded range, and can be further simplified when certain prior knowledge is available. This permits more efficient tuning than its regularization counterpart. Based on our limited experience, we note that τ does not need to be tuned precisely as we may fix at some small values.
     </paragraph>
     <paragraph>
      Performance and computation. Although our model (2) is proposed as a computational surrogate of the ideal {a mathematical formula}L0-method, its performance can also be theoretically guaranteed, i.e., consistent feature selection can be achieved. Moreover, the computation of our model is much more efficient and applicable to large-scale applications.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Empirical evaluation
     </section-title>
     <section label="5.1">
      <section-title>
       Evaluation of projection algorithms
      </section-title>
      <paragraph>
       Since DC programming and the accelerated gradient methods are both standard, the efficiency of the proposed nonconvex formulation (2) depends on the projection step in (8). Therefore, we focus on evaluating the projection algorithms and comparing with two popular projection algorithms: Alternating Direction Method of Multiplier (ADMM) [6] and Dykstra's projection algorithm [11]. We give a detailed derivation of adapting these two algorithms to our formulation in Appendix A Proof of, Appendix B Proof of, Appendix C Accelerated gradient method, Appendix D Algorithm for solving, Appendix E The ADMM projection algorithm, Appendix F Dykstra's algorithm, Appendix G Proof of.
      </paragraph>
      <paragraph>
       To evaluate the efficiency, we first generate the vector v whose entries are uniformly distributed in {a mathematical formula}[−50,50] and the dimension of v, denoted as p, is chosen from the set {a mathematical formula}{102,103,104,105,106}. Next we partition the vector into 10 groups of equal size. Finally, {a mathematical formula}s2 is set to {a mathematical formula}5log⁡(p) and {a mathematical formula}s1, the radius of the {a mathematical formula}L1-ball, is computed by {a mathematical formula}102s2 (motivated by the fact that {a mathematical formula}s1≤10s2).
      </paragraph>
      <paragraph>
       For a fair comparison, we run our projection algorithm until converge and record the minimal objective value as {a mathematical formula}f⁎. Then we run ADMM and Dykstra's algorithm until their objective values become close to ours. More specifically, we terminate their iterations as soon as {a mathematical formula}fADMM−f⁎≤10−3 and {a mathematical formula}fDykstra−f⁎≤10−3, where {a mathematical formula}fADMM and {a mathematical formula}fDykstra stand for the objective value of ADMM and Dykstra's algorithm respectively. Table 2 summarizes the average running time of all three algorithms over 100 replications.
      </paragraph>
      <paragraph>
       Next we demonstrate the accuracy of our projection algorithm. Toward this end, the general convex optimization toolbox CVX [19] is chosen as the baseline. Following the same strategy of generating data, we report the distance (computed from the Euclidean norm {a mathematical formula}‖⋅‖2) between optimal solution of the three projection algorithms and that of the CVX as well as the running time. Note that the projection is strictly convex with a unique global optimal solution.
      </paragraph>
      <paragraph>
       For ADMM and Dykstra's algorithm, the termination criterion is that the relative difference of the objective values between consecutive iterations is less than a threshold value. Specifically, we terminate the iteration if {a mathematical formula}|f(xk−1)−f(xk)|≤10−7f(xk−1). For our projection algorithm, we set the tol in Algorithm 3 to be {a mathematical formula}10−7. The results are summarized in Table 3 and Fig. 3. Powered by second-order optimization algorithms, CVX can provide fast and accurate solutions for medium-size problems but would suffer from great computational burden for large-scale ones. Therefore we only report the results up to 5000 dimensions.
      </paragraph>
      <paragraph>
       From the above results we can observe that for projections of a moderate size, all three algorithms perform well. However, for large-scale ones, the advantage of the proposed algorithm is evident as our method provides more accurate solution with less time.
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Evaluation of convergence
      </section-title>
      <paragraph>
       We study the convergence behavior of different implementations of our discrete optimization approach proposed in Section 3.2. The evaluation is carried out on a collection of randomly generated data sets {a mathematical formula}(A,y). Specifically, we generate {a mathematical formula}A∈Rn×p, {a mathematical formula}y∈Rn, where the values of n and p are chosen from the pairs {a mathematical formula}{(100,2000),(100,5000),(1000,20000),(1000,50000)}. All of the p features are partitioned into groups of size 100. The value of {a mathematical formula}s2 is selected from {a mathematical formula}{0.1|G|,0.2|G|}, i.e., we select {a mathematical formula}10% and {a mathematical formula}20% groups. {a mathematical formula}s1 is set to {a mathematical formula}5s2, which leads to the effect of within-group sparsity.
      </paragraph>
      <paragraph>
       For all of the variants, we terminate the programs when either the relative change of objective value in two consecutive iterations or the gradient of the objective is less than a given threshold. The objective values of up to the first 100 iterations as well as the running time for each variant are reported in Fig. 4. The results demonstrate the effect of BB to initialize the step-size. Both ISTA with Lipschitz line search criterion (blue in Fig. 4) and FISTA (black in Fig. 4) deliver superior performance, particularly for large data sets and large numbers of selected groups/features.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Performance on synthetic data
      </section-title>
      <paragraph>
       We generate a {a mathematical formula}60×100 matrix A, whose entries follow i.i.d. standard normal distribution. The 100 features (columns) are partitioned into 10 groups of equal size. The ground truth vector {a mathematical formula}x0 possesses nonzero elements only in 4 of the 10 groups. In addition, only 4 elements in each nonzero group are nonzero. Finally y is generated according to {a mathematical formula}Ax0+z with z following distribution {a mathematical formula}N(0,0.52). The data are divided into training and testing set of equal size.
      </paragraph>
      <paragraph>
       We fit our methods to the training set and compare with both convex methods (lasso, group lasso and sparse group lasso) and methods based on nonconvex bi-level penalties (group bridge and composite MCP). Since the data are intentionally generated to be sparse in both group-level and feature-level, approaches that only perform group selection, such as group lasso, group SCAD and ordinary group MCP, are not included due to their suboptimal results.
      </paragraph>
      <paragraph>
       The tuning parameters of the convex methods are selected from the following set {a mathematical formula}{0.01,0.1,1,10}, whereas for our methods, the number of nonzero groups ({a mathematical formula}s2) is selected from the set {a mathematical formula}{2,4,6,8} and the number of features ({a mathematical formula}s1) is chosen from the set {a mathematical formula}{2s2,4s2,6s2,8s2}. 10-fold cross validation is taken for parameter tuning. Group bridge and composite MCP are carried out using their original R-package grpreg and the tuning parameters are set to the default values (100 parameters with 10-fold cross-validation).
      </paragraph>
      <paragraph>
       Following similar settings in [8], we list the number of selected groups and features by each method. In addition, the number of false positive or false negative groups/features are also reported in Table 4. We can observe that our models correctly identify the underlying groups and features. Moreover, our methods effectively exclude redundant features and groups compared to other methods, which is illustrated by our low false positive numbers and relatively high false negative numbers. Such a phenomenon also appears in the evaluations in [8].
      </paragraph>
     </section>
     <section label="5.4">
      <section-title>
       Performance on real-world application
      </section-title>
      <paragraph>
       Our method is evaluated on the application of examining Electroencephalography (EEG) correlates of genetic predisposition to alcoholism [16]. EEG records the brain's spontaneous electrical activity by measuring the voltage fluctuations over multiple electrodes placed on the scalp. This technology has been widely used in clinical diagnosis, such as coma, brain death and genetic predisposition to alcoholism. In fact, encoded in the EEG data is a certain group structure, since each electrode records the electrical activity of a certain region of the scalp. Identifying and utilizing such spatial information has the potential of increasing stability of a prediction.
      </paragraph>
      <paragraph>
       The training set contains 200 samples of {a mathematical formula}16384 dimensions, sampled from 64 electrodes placed on subject's scalps at 256 Hz (3.9-msec epoch) for 1 second. Therefore, the data can naturally be divided into 64 groups of size 256. We apply the lasso, group lasso, sparse group lasso, group SCAD, group MCP, group bridge, composite MCP and our proposed method on the training set and adapt the 5-fold cross-validation for selecting tuning parameters. More specifically, for lasso and group lasso, the candidate tuning parameters are specified by 10 parameters{sup:4} sampled using the logarithmic scale from the parameter spaces, while for the sparse group lasso, the parameters form a {a mathematical formula}10×10 grid,{sup:5} sampled from the parameter space in logarithmic scale. For our methods, the number of groups is selected from the set: {a mathematical formula}s2={30,40,50} and {a mathematical formula}s1, the number of features is chosen from the set {a mathematical formula}{50s2,100s2,150s2}. The R-package grpreg (80 parameters, 10-fold cross validation) are applied to other nonconvex methods. The accuracy, sensitivity and specificity of classification together with the number of selected features and groups over a test set, which also contains 200 samples, are reported in Table 5. Clearly our methods achieve the best classification performance. Note that, although lasso's performance is comparable with ours with even less features, however, it fails to identify the underlying group structure in the data, as revealed by the fact that all 64 groups are selected. Moreover, other nonconvex approaches such as the group SCAD, group MCP and group bridge seem to over-penalize the group penalty, which results in very few selected groups and suboptimal performance.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Proof of Theorem 3
     <paragraph>
      The proof uses a large deviation probability inequality of [43] to treat one-sided log-likelihood ratios with constraints.
     </paragraph>
     <paragraph>
      Let {a mathematical formula}S={xτ:‖xτ‖0≤s10,‖xτ‖0,G≤s20}, {a mathematical formula}‖x‖0=∑j=1pI(|xj|≠0) is the {a mathematical formula}L0-norm of x, and {a mathematical formula}‖x‖0,G=∑j=1|G|I(‖xj‖2≠0) is the {a mathematical formula}L0-norm over the groups. Now we partition {a mathematical formula}S. Note that for {a mathematical formula}G⊂(G1,⋯,G|G|), it can be partitioned into {a mathematical formula}G=(G∖G0)∪(G∩G0). Then{a mathematical formula} where {a mathematical formula}SBG={xτ∈S:G(x)=G=(Gi1,⋯,Gik),∑j|BGj|≤s10}, and {a mathematical formula}Bi={G≠G0:|G0∖G|=i,|G|≤s20}, with {a mathematical formula}|Bi|=(s20s20−i)∑j=0i(|G|−s20j); {a mathematical formula}i=0,⋯,s20.
     </paragraph>
     <paragraph>
      To bound the error probability, let {a mathematical formula}L(x)=−12‖Ax−y‖2 be the likelihood. Note that{a mathematical formula} This together with {a mathematical formula}{xˆ≠xˆo}⊆{xˆ∈S} implies that{a mathematical formula} Consequently,{a mathematical formula} where {a mathematical formula}P⁎ is the outer measure and {a mathematical formula}S={−log⁡(1−h2(x,x0))≥max⁡(i,1)Cmin(x0)−d3τd2p,x∈SBG}. The last two inequalities use the fact that {a mathematical formula}SBG⊆{x∈SBG:max⁡(|G0∖G|,1)Cmin(x0)≤−log⁡(1−h2(x,x0))}⊆S, under Assumption 3.
     </paragraph>
     <paragraph>
      For I, we apply Theorem 1 of [43] to bound each term. Towards this end, we verify their entropy condition (3.1) for the local entropy over {a mathematical formula}SBG for {a mathematical formula}|G|=1,⋯,s20 and {a mathematical formula}|BG|=1,⋯,s10. Under Assumption 2{a mathematical formula}ε=εn,p=(2c0)1/2c4−1log⁡(21/2/c3)log⁡p(s10n)1/2 satisfies there with respect to {a mathematical formula}ε&gt;0, that is,{a mathematical formula} for some constant {a mathematical formula}c3&gt;0 and {a mathematical formula}c4&gt;0, say {a mathematical formula}c3=10 and {a mathematical formula}c4=(2/3)5/2512. By Assumption 2, {a mathematical formula}Cmin(x0)≥εn,p0,p2 implies (A.1), provided that {a mathematical formula}s10≥(2c0)1/2c4−1log⁡(21/2/c3).
     </paragraph>
     <paragraph>
      Note that {a mathematical formula}|Bi|=(s20s20−i)∑j=0i(|G|−s20j)≤(|G|(|G|−s20)i≤(|G|2/4)i by the binomial coefficients formula. Moreover, {a mathematical formula}∑j=1s102jij≤is10, and {a mathematical formula}∑j1+⋯+ji=j(jj1,⋯,ji)2j=(2i)j using the Multinomial Theorem. By Theorem 1 of [43], there exists a constant {a mathematical formula}c2&gt;0, say {a mathematical formula}c2=42711926,{a mathematical formula}
     </paragraph>
     <paragraph>
      Let {a mathematical formula}D={xˆ≠xˆ0}. For the risk property, {a mathematical formula}Eh2(xˆ,x0)=Eh2(xˆ0,x0)+Eh2(xˆ,x0)I(D) is upper bounded by{a mathematical formula} using the fact that {a mathematical formula}h(xˆ,x0)≤1. This completes the proof.
     </paragraph>
    </section>
    <section label="Appendix B">
     Proof of Proposition 1
     <paragraph>
      Note that under the boundedness condition, the {a mathematical formula}L2-norm is equivalent to the Hellinger-distance under (17). We give the proof by verifying each assumption in Theorem 3.
     </paragraph>
     <paragraph>
      We first notice that Assumption 2 follows from [25] by plugging{a mathematical formula} Note that {a mathematical formula}|∂h2(x,x0)∂xj|≤12E(|Aj|), where {a mathematical formula}Aj is the jth column of A; {a mathematical formula}1≤j≤p and {a mathematical formula}x∈Rp. Thus we can conclude{a mathematical formula} Then Assumption 3 is fulfilled with {a mathematical formula}d1=d2=1 and {a mathematical formula}d3=2maxj⁡Σjj.
     </paragraph>
     <paragraph>
      To simplify Assumption 1, we derive an inequality through some straightforward calculations. Let {a mathematical formula}x˜=((xBG,0)−(0,xBG0)), where {a mathematical formula}xBG is obtained by removing zero components from x. Then{a mathematical formula} for some constant {a mathematical formula}c1⁎&gt;0, because the derivative of {a mathematical formula}1−exp⁡(−18x2) is bounded away from zero under the compactness assumption.
     </paragraph>
    </section>
    <section label="Appendix C">
     <section-title>
      Accelerated gradient method
     </section-title>
     <paragraph>
      The AGM procedure is listed in Algorithm 8, in which {a mathematical formula}f(x) is the objective function {a mathematical formula}12‖Ax−y‖22 with {a mathematical formula}∇f(x) denotes its gradient at x. In addition, {a mathematical formula}fL,u(x) is the linearization of {a mathematical formula}f(x) at u defined as follows:{a mathematical formula}
     </paragraph>
    </section>
    <section label="Appendix D">
     Algorithm for solving (13)
     <paragraph>
      We give a detailed description of algorithm for solving the restricted projection (13) in Algorithm 9.
     </paragraph>
    </section>
    <section label="Appendix E">
     <section-title>
      The ADMM projection algorithm
     </section-title>
     <paragraph>
      Alternating Direction Method of Multipliers (ADMM) is widely chosen for its capability of decomposing coupled variables/constraints, which is exactly the case in our projection problem. Before applying ADMM, we transform (8) into an equivalent form as follows:{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The augmented Lagrangian is:{a mathematical formula} Utilize the scaled form [6], i.e., let {a mathematical formula}λ=λρ, {a mathematical formula}η=ηρ, we can obtain an equivalent augmented Lagrangian:{a mathematical formula}
     </paragraph>
     <paragraph>
      Now we calculate the optimal x, λ and η through alternating minimization. For fixed u and w, the optimal x possesses a closed-form solution:{a mathematical formula}
     </paragraph>
     <paragraph>
      For fixed x and u, finding the optimal w is a group lasso projection:{a mathematical formula}
     </paragraph>
     <paragraph>
      For fixed x and w, finding the optimal u amounts to solve an {a mathematical formula}L1-ball projection:{a mathematical formula} The update of multipliers is standard as follows:{a mathematical formula}Algorithm 10 summarizes the above procedure. Note that, the value of the penalty term ρ is fixed in Algorithm 10. However, in our implementation, we increase ρ whenever necessary to obtain faster convergence.
     </paragraph>
    </section>
    <section label="Appendix F">
     <section-title>
      Dykstra's algorithm
     </section-title>
     <paragraph>
      Dykstra's algorithm is a general scheme to compute the projection onto intersections of convex sets. It is carried out by taking Euclidean projections onto each convex set alternatively in a smart way and is guaranteed to converge for least squares objective function [11]. The details of applying Dykstra's Algorithm to our projection problem are listed in Algorithm 11.
     </paragraph>
    </section>
    <section label="Appendix G">
     Proof of Theorem 4
     <paragraph label="Proof">
      Let {a mathematical formula}wk denote {a mathematical formula}xk−∇f(xk). It is clear that{a mathematical formula} where the last inequality comes from the optimality of {a mathematical formula}xk+1. After eliminating {a mathematical formula}‖x⁎−wk‖22 from both sides we can obtain:{a mathematical formula} where the set U is the union of support of {a mathematical formula}x⁎, {a mathematical formula}xk and {a mathematical formula}xk+1 and the last inequality is from the fact that the spectral norm of {a mathematical formula}I−AUTAU is upperbounded by {a mathematical formula}δ|U|[5]. The first conclusion then follows from expanding the last term and compute the power series.To prove the second result, a finer treatment of the set U above is needed. Specifically, we consider the following four sets:{a mathematical formula}{a mathematical formula}{a mathematical formula} and it is easy to verify that:{a mathematical formula}{a mathematical formula}{a mathematical formula} Therefore we can conclude that:{a mathematical formula}{a mathematical formula} where the first inequality is from our proof of the first result and we apply the Cauchy inequality to obtain the last inequality. The proof is completed by expanding the last term and computing the resulting power series.  □
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>