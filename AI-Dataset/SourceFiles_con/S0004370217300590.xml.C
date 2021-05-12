<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Low-rank decomposition meets kernel learning: A generalized Nyström method.
   </title>
   <abstract>
    Low-rank matrix decomposition and kernel learning are two useful techniques in building advanced learning systems. Low-rank decomposition can greatly reduce the computational cost of manipulating large kernel matrices. However, existing approaches are mostly unsupervised and do not incorporate side information such as class labels, making the decomposition less effective for a specific learning task. On the other hand, kernel learning techniques aim at constructing kernel matrices whose structure is well aligned with the learning target, which improves the generalization performance of kernel methods. However, most kernel learning approaches are computationally very expensive. To obtain the advantages of both techniques and address their limitations, in this paper we propose a novel kernel low-rank decomposition formulation called the generalized Nyström method. Our approach inherits the linear time and space complexity via matrix decomposition, while at the same time fully exploits (partial) label information in computing task-dependent decomposition. In addition, the resultant low-rank factors can generalize to arbitrary new samples, rendering great flexibility in inductive learning scenarios. We further extend the algorithm to a multiple kernel learning setup. The experimental results on semi-supervised classification demonstrate the usefulness of the proposed method.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Advanced learning systems typically have two basic requirements: computational efficiency and generalization ability. In this paper, we are interested in building kernel based learning algorithms. To generate desired kernel machines catering to these requirements, significant research efforts have been devoted to low-rank matrix decomposition and kernel learning.
     </paragraph>
     <paragraph>
      Low-rank decomposition aims at factorizing a Positive Semi-Definite (PSD) kernel matrix into a product of low-rank factorsp. Given an {a mathematical formula}n×n kernel matrix K with rank {a mathematical formula}r&lt;&lt;n, the kernel matrix can be represented as {a mathematical formula}K=GG⊤, with G an {a mathematical formula}n×r matrix. Low-rankness is an important property that has been widely exploited in machine learning. For example, the kernel matrix often has a rapidly decaying spectrum and thus small rank, and eigenvectors corresponding to large eigenvalues create useful basis functions for classification [1], [2]. The low-rank property is also quite useful in reducing the memory and computational cost in large scale problems using low-rank approximations. It has been used widely to scale up various machine learning algorithms [3], [4], [5], [6], [7]. However, there are certain limitations with existing approaches. First, many such methods are intrinsically unsupervised and only focus on numerical approximation of the kernel matrix. For example, well known decomposition techniques such as eigenvalue decomposition, QR factorization, Cholesky decomposition are all unsupervised methods. When confronted with a specific learning task, however, we believe that incorporating side information (such as partially labeled samples or grouping constraints) will lead to more effective decomposition and improved performance. Second, many existing decomposition methods, such as QR decomposition, incomplete Cholesky factorization [8], work in a transductive manner. That means the factorization can only be computed for samples that are available in the training stage. For new samples that are only available in the testing stage, it is not straightforward to generalize the decomposition to these data, and the difficulty becomes more pronounced if (partial) label information is considered.
     </paragraph>
     <paragraph>
      Apart from computational efficiency, kernel learning is another research area that aims to improve the generalization performance of kernel methods. Note that kernel based learning algorithms implicitly embed data in a Euclidean space [9] via the kernel matrix. The goal of kernel learning therefore is to obtain a kernel matrix such that the induced geometry (1) preserves the original similarities in the data and, (2) correlates well with the class labels and henceforth better predicts them. Lanckriet et al. [9] proposed to learn the kernel matrix whose embedding shows maximal margin while keeping the trace of the kernel matrix constant. Instead of using the margin of SVM as the optimization criterion, Cristianini et al. [10] proposed the kernel alignment as a general objective independent of classifiers. Maximizing alignment of the learned kernel with the ideal kernel[11] provides a general and effective way for kernel design. The concept of ideal kernel and kernel alignment has led to a family of Multiple Kernel Learning (MKL) algorithms [10], [12], [9], [13], [14], [15]. The key idea of MKL is to choose a set of base kernels and then optimize their weighting coefficients via maximizing the alignment with the ideal kernel. Recently, an improved alignment criterion called centralized kernel alignment was proposed by Cortes et al. [16]. Here the kernel matrix is subject to double-centering before computing their correlations, which has been shown to overcome some of the limitations with the traditional kernel alignment and provides a novel concentration bound in both classification and regression tasks. Cortes et al. [16] showed that the weighting coefficients in the maximal alignment kernel can be solved via Quadratic Programming (QP). In [17], an order constraint on the weighting coefficients is imposed that gives higher priority to eigenvectors corresponding to smaller eigenvalues of the graph Laplacian.
     </paragraph>
     <paragraph>
      Although kernel learning algorithms can improve the quality of the kernel matrix and therefore the generalization performance, the computational cost is typically demanding. For instance, most algorithms will need to store multiple {a mathematical formula}n×n base kernel matrices, which takes at least {a mathematical formula}O(n2) space and time. In addition, computing the eigenvalue decomposition of the kernel matrix takes {a mathematical formula}O(n2) space and {a mathematical formula}O(n3) time. This has become a bottleneck in many real-life applications with large scale data.
     </paragraph>
     <paragraph>
      To summarize, both low-rank decomposition and kernel learning have their advantages and limitations. The former has a computational advantage but is not very well-tailored to fit specific learning tasks; the latter usually involves careful design to boost the generalization performance, but the high computational cost makes it impractical for big data problems.
     </paragraph>
     <paragraph>
      To obtain the advantages of both low-rank decomposition and kernel learning, in this paper we propose a novel low-rank decomposition algorithm that incorporates side information in producing efficient and effective low-rank kernel. We achieve this by generalizing the Nyström method in a novel way. The Nyström method is a sampling based approach and has gained great popularity in unsupervised kernel low-rank approximation, with both theoretical performance guarantees and empirical successes [5], [6], [18]. Our main novelty is to provide an interesting interpretation of the matrix completion view of the Nyström method as a an extrapolation of a dictionary kernel, and generalize it to incorporate side information in computing improved low-rank decompositions. Our approach has two important advantages. First, it has a flexible, generative structure that allows us to generalize computed low-rank factorizations to arbitrary new unseen samples. Second, both the space and time complexities of our approach are linear in the sample size, rendering great efficiency in learning a useful low-rank kernel.
     </paragraph>
     <paragraph>
      Our method also has connections to sparse Gaussian process [19], [20], [21], [22], [23], [24]. An important goal of sparse Gaussian process is to determine the choice of a small set of “pseudo”-samples to build a sparse model with significantly reduced computational cost. This shows the similarity to sample based approximations of the kernel matrix. Our approach shares some features with sparse GP but has some distinct aspects. We provide an in-depth discussion in Section 5.
     </paragraph>
     <paragraph>
      The rest of the paper is organized as follows. In Section 2, we introduce the Nyström method. In Section 3, we propose the generalized Nyström low-rank decomposition incorporating side information. In Section 4 we discuss the multiple kernel version of the generalized Nyström method. In Section 5 we discuss related work. In Section 6 we report empirical evaluation results. The last section concludes the paper. A preliminary conference version of this paper is published by Zhang et al. [25].
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Nyström method
     </section-title>
     <paragraph>
      The Nyström method is a sampling based algorithm for approximating large kernel matrices and their eigen-systems. It originated from solving integral equations and was introduced to the machine learning community by Williams and Seeger [5], Fowlkes et al. [6].
     </paragraph>
     <paragraph>
      Given a kernel function {a mathematical formula}k(⋅,⋅) and a sample set with underlying distribution {a mathematical formula}p(⋅), the Nyström method aims at solving the following integral equation{a mathematical formula} Here {a mathematical formula}ϕi(x) and {a mathematical formula}λi are the ith eigenfunction and eigenvalue of the operator {a mathematical formula}k(⋅,⋅) with regard to p. By drawing a set of m samples {a mathematical formula}Z (landmark points) from {a mathematical formula}p(⋅), an empirical average can be computed as{a mathematical formula} By choosing x in (2) as {a mathematical formula}z1,z2,...,zm, one has an eigenvalue decomposition as {a mathematical formula}Wϕi=λiϕi, where {a mathematical formula}W∈Rm×m is the kernel matrix defined on landmark points, {a mathematical formula}ϕi∈Rm×1 and {a mathematical formula}λi are the ith eigenvector and eigenvalue of W. Note that the Nyström method is a special case of collocation method [26], which approximates the eigenfunctions {a mathematical formula}ϕi(x) by a linear combination of a set of basis functions and solves (1) based on selected collocation points.
     </paragraph>
     <paragraph>
      In practice, given a large data set {a mathematical formula}X={xi}i=1n, the Nyström method randomly selects m landmark points {a mathematical formula}Z with {a mathematical formula}m≪n, and computes the eigenvalue decomposition of W. Then the eigenvectors of W are extrapolated to the whole sample set by (2). Interestingly, the Nyström method is shown to implicitly reconstruct the whole {a mathematical formula}n×n kernel matrix K by{a mathematical formula} Here {a mathematical formula}W† is the pseudo-inverse of W, and {a mathematical formula}E∈Rn×m is the kernel matrix defined on the sample set {a mathematical formula}X and landmark points {a mathematical formula}Z. The Nyström method requires {a mathematical formula}O(mn) space and {a mathematical formula}O(m2n) time, which are linear in the sample size considering {a mathematical formula}m≪n. It has drawn considerable interest in clustering and manifold learning [27], [18], Gaussian processes [5], and kernel methods [3].
     </paragraph>
     <paragraph>
      Landmark selection in Nyström method. Selection of the landmark points {a mathematical formula}Z in the Nyström method can have a great impact on its performance. In the literature, various sampling schemes have been proposed. The simplest approach is random sampling [5], [6]. Recently various non-uniform sampling schemes are also studied. Smola and Schökopf [28] proposed a greedy sampling scheme to sequentially select columns which maximally decreases the approximation error; Kumar et al. [29] proposed an adaptive sampling scheme that only requires visiting part of the kernel matrix, together with relative error bound; Drineas and Mahoney [30] proposed a probabilistic sampling scheme where the probability for choosing the ith row/column of the kernel matrix K is proportional to the norm of that row/column.
     </paragraph>
     <paragraph>
      Zhang et al. [7], Zhang and Kwok [18] proposed to select the landmark points as the k-means clustering centers of the input data. They showed that the Nyström low-rank approximation error is closely related to the error of reconstructing input samples with selected landmark points. In previous evaluations [31], researchers have found that k-means based sampling method outperforms many other sampling schemes (random, greedy, or adaptive) by a clear margin, and at the same time being computationally very efficient.
     </paragraph>
     <paragraph>
      In this work we adopt the k-means based sampling because of its efficiency and competitive performance. Other sampling schemes are applicable as well, but our main focus is on how to generalize the procedures of the Nyström method such that it can further incorporate class label information.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Generalized Nyström low-rank decomposition
     </section-title>
     <section label="3.1">
      <section-title>
       Extrapolation of the dictionary kernel
      </section-title>
      <paragraph>
       We first present an interesting interpretation of the matrix completion view of the Nyström method (3). It reconstructs {a mathematical formula}(i,j)th entry of the kernel matrix as{a mathematical formula} where {a mathematical formula}Ei∈R1×m is the ith row of the extrapolation matrix E. In other words, the similarity between any two samples {a mathematical formula}xi and {a mathematical formula}xj is constructed by first computing their respective similarities to the landmark set ({a mathematical formula}Ei and {a mathematical formula}Ej), and then modulated by the inverse of the similarities among the landmark points {a mathematical formula}W†. With regards to this, we have the following proposition.
      </paragraph>
      <paragraph label="Proposition 1">
       Given m landmark points{a mathematical formula}Z, we use(4)to construct the similarity between any two samples,{a mathematical formula}xiand{a mathematical formula}xj. Let{a mathematical formula}zpand{a mathematical formula}zqbe the closest landmark points to{a mathematical formula}xiand{a mathematical formula}xj, respectively. Let{a mathematical formula}dp=‖xi−zp‖2, and{a mathematical formula}dq=‖xj−zq‖2. Let the kernel function{a mathematical formula}k(⋅,⋅)satisfy the Lipschitz property{sup:1}{a mathematical formula}|k(x,y)−k(x,z)|≤η‖y−z‖2, and{a mathematical formula}c=max⁡k(⋅,⋅). Then the reconstructed similarity{a mathematical formula}Kijand the{a mathematical formula}(p,q)th entry of W will have the following relation{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       Let {a mathematical formula}Ei=[k(xi,z1)k(xi,z2)…k(xi,zm)], and {a mathematical formula}Wp=[k(zp,z1)k(zp,z2)…k(zp,zm)], and define {a mathematical formula}Δp=Ei−Wp, {a mathematical formula}Δq=Ej−Wq. We have {a mathematical formula}‖Δp‖22=∑o=1m(k(xi,zo)−k(zp,zo))2≤mη2dp2, similarly, {a mathematical formula}‖Δq‖22≤mη2dq2. We also have {a mathematical formula}‖Ei‖22,‖Ej‖22≤c, then we have{a mathematical formula} Here we used the equality {a mathematical formula}WpW†Wq⊤=Wpq, since {a mathematical formula}Wp and {a mathematical formula}Wq are the pth and qth row (column) of W. □
      </paragraph>
      <paragraph>
       Proposition 1 gives an interesting interpretation of the kernel reconstruction mechanism of the Nyström method (4). If {a mathematical formula}xi and {a mathematical formula}xj happen to coincide with a pair of landmark points, {a mathematical formula}zp and {a mathematical formula}zq, then {a mathematical formula}Kij=Wpq, i.e., the pqth entry of W will be extrapolated exactly to {a mathematical formula}(xi,xj). In case {a mathematical formula}xi and {a mathematical formula}xj do not coincide with any landmark point, the difference between {a mathematical formula}Kij and {a mathematical formula}Wpq, with {a mathematical formula}zp and {a mathematical formula}zq being the closest landmark points to {a mathematical formula}xi and {a mathematical formula}xj, will be bounded by the distances {a mathematical formula}‖xi−zp‖2 and {a mathematical formula}‖xj−zq‖2. The smaller the distances, the closer {a mathematical formula}Kij and {a mathematical formula}Wpq. In other words, the similarity matrix W on the landmark points serves as a dictionary kernel, whose entries are extrapolated (on both sides) to any pairs of samples ({a mathematical formula}xi,xj) according to the proximity relation between landmark points and samples, and the reconstruction is exact on the landmark points {a mathematical formula}Z which serve as the “nodes” for extrapolation.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Including side information
      </section-title>
      <paragraph>
       The kernel extrapolation view of the Nyström method (Proposition 1) inspires us to generalize it to handle side information in learning a low-rank kernel. Note that quality of the dictionary kernel will have a large impact on the whole kernel matrix. In the original Nyström method (3), the dictionary kernel W is simply computed as the pairwise similarity between landmark points, which can deviate from an “ideal” one. Therefore, instead of using such an “unsupervised” dictionary kernel, we propose to learn a new dictionary kernel that better coincides with given side information.
      </paragraph>
      <paragraph>
       Suppose we are given a set of labeled and unlabeled samples. Let {a mathematical formula}Z be a set of m pre-selected landmark points. Let {a mathematical formula}E∈Rn×m be the extrapolation kernel matrix between samples {a mathematical formula}X and landmark {a mathematical formula}Z, and let {a mathematical formula}El∈Rl×m be the rows of E corresponding to labeled samples. For simplicity, let {a mathematical formula}S0=W† denote the inverse of the dictionary kernel in the standard Nyström method (3). Our task is to learn (the inverse of) a new dictionary kernel, denoted by S, subject to the following considerations:
      </paragraph>
      <list>
       <list-item label="1.">
        unsupervised information: the reconstructed kernel {a mathematical formula}ESE⊤ should preserve the structure of the original kernel matrix K, since K encodes important pairwise relation between samples;
       </list-item>
       <list-item label="2.">
        supervised information: the reconstructed kernel on the labeled samples, {a mathematical formula}ElSEl⊤, should be consistent with the given side information.
       </list-item>
      </list>
      <paragraph>
       Note that in the standard Nyström method, {a mathematical formula}EW†E⊤ provides an effective approximation of K. Therefore, to achieve the first goal, we use{a mathematical formula} as a prior for the (inverse) dictionary kernel S, namely, they should be close to each other. The choice of the scaling factor β will be clear in the sequel.
      </paragraph>
      <paragraph>
       To achieve the second goal, we use the concept of kernel target alignment [10] and require that the reconstructed kernel, {a mathematical formula}ElSEl⊤, is close to the ideal kernel {a mathematical formula}Kl⁎ defined on labeled samples. The ideal kernel is defined as [11]{a mathematical formula}
      </paragraph>
      <paragraph>
       We therefore arrive at the following problem{a mathematical formula} Here, we used the Frobenius norm to measure the closeness between two matrices. Note that in [10], the closeness between two kernel matrices is measured by their inner product {a mathematical formula}〈K1,K2〉=∑ijK1(xi,xj)K2(xi,xj). Since {a mathematical formula}‖K1−K2‖F2=〈K1,K1〉+〈K2,K2〉−2〈K1,K2〉, minimizing the Frobenius norm is related to maximizing the alignment. We choose the Frobenius norm here because it leads to a convex optimization, which can be computationally more feasible than if we choose kernel alignment score in [10]. We will use the normalized kernel alignment score [16] afterwards as an independent measure to choose the hyper-parameter λ. Details will be discussed in Section 3.8.
      </paragraph>
      <paragraph>
       In practical implementations, we choose the scaling factor β in (5) as{a mathematical formula} such that solutions from the two competing terms respectively in (7), namely {a mathematical formula}W† and {a mathematical formula}El†Kl⁎(ElT)†, would have the same magnitude. In this case the resultant combined objective would be more meaningful. One can also optimize the scaling factor β iteratively with the other variable S, which we found in our experiments produce similar result with (8) with higher computational cost (see Appendix A). So we simply adopt (8) in our evaluations.
      </paragraph>
      <paragraph>
       We call our method generalized Nyström low-rank decomposition. The method has several desirable properties. First, as long as the inverse dictionary kernel S is PSD, the resultant kernel {a mathematical formula}ESE⊤ will also be PSD; second, the rank of the kernel matrix can be easily controlled by the landmark size; this can be computationally much more efficient than learning a full kernel matrix subject to rank constraint; third, the extrapolation (4) is “generative” and allows us to compute the similarity between any pair of samples; this means the learned kernel matrix generalizes easily to new unseen samples. Since the dictionary kernel is learned with side information, the generalization to new samples naturally incorporates such information, which provides much more convenience in updated environments.
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Must-link grouping constraints as side information
      </section-title>
      <paragraph>
       Suppose we are given a set of must-link grouping constraints denoted by {a mathematical formula}I. Let {a mathematical formula}XI be the subset of samples with such constraints. Then we define {a mathematical formula}T∈R|XI|×|XI| such that{a mathematical formula} Then our objective can be written conveniently as{a mathematical formula} Here ⊙ denotes the element-wise multiplication and {a mathematical formula}KI⁎ is defined similarly as in (6). The objective can be transferred to (7) by element-wise multiplying T with {a mathematical formula}EISEIT and {a mathematical formula}KI⁎ respectively.
      </paragraph>
      <paragraph>
       Our current formulation does not handle “do-not-link” constraints directly. To achieve this, different loss functions are needed that take into account geometric relations between samples of different classes such as in [32].
      </paragraph>
     </section>
     <section label="3.4">
      <section-title>
       Optimization
      </section-title>
      <paragraph>
       The objective (7) is convex with respect to S, and the PSD constraint {a mathematical formula}S⪰0 is also convex. Therefore a global optimum can be guaranteed.
      </paragraph>
      <paragraph>
       Note that S is a matrix with only {a mathematical formula}m2 variables, where {a mathematical formula}m≪n is a user defined value. Therefore the problem (7) is relatively easy to optimize. We use the gradient mapping strategy [33] that is composed of iterative gradient descent equipped with a projection step to find the optimal solution. Given an initial solution {a mathematical formula}S(t), we update it by{a mathematical formula} where {a mathematical formula}∇S is the gradient of the objective J(7) at S,{a mathematical formula} The step length {a mathematical formula}η(t) is determined by the Armijo–Goldstein rule [33]. In particular, we start from an initial small scalar a and solve{a mathematical formula}This is a standard matrix nearness problem with PSD constraint, and {a mathematical formula}Ba⁎ can be computed in a closed-form as {a mathematical formula}S(t)−1a∇S(t) with removal of negative eigenvectors/values. Then we examine [33]{a mathematical formula} If this inequality is violated, we increase a by a constant factor and re-calculate (10) until the relation holds. Then we use {a mathematical formula}η(t)=1a as the step length for (9).
      </paragraph>
      <paragraph>
       After the descent step (9), we project the {a mathematical formula}S(t+1) onto the set of positive semi-definite cones as follows{a mathematical formula} where {a mathematical formula}U(t+1) and {a mathematical formula}Λ(t+1) are the eigenvectors and eigenvalues of {a mathematical formula}S(t+1), and{a mathematical formula} One can also use more advanced approaches such as the Nesterov's method [33] to improve the convergence rate. We do not explore more options here because the size of our optimization problem is small and empirically it converges quickly due to a principled initialization (see next subsection).
      </paragraph>
     </section>
     <section label="3.5">
      <section-title>
       Initialization
      </section-title>
      <paragraph>
       In this section, we propose a closed-form initialization which helps quickly locate the optimal solution. The basic idea is to drop the PSD constraint in (7) first, and compute the vanishing point of the gradient, i.e., {a mathematical formula}∂J(S)∂S=0, which leads to{a mathematical formula} Then we have{a mathematical formula} where{a mathematical formula} Equation (12) can be solved as follows. Suppose the diagonalization of P is {a mathematical formula}P=UΛU⊤, and define {a mathematical formula}S=US˜U⊤, {a mathematical formula}Q=UQ˜U⊤, then (12) reduces to{a mathematical formula} Since Λ is a diagonal matrix, this becomes {a mathematical formula}m2 equations{a mathematical formula} Therefore we have a closed-form solution of S, as{a mathematical formula} After computing S, we then project it onto the set of positive semi-definite cones similar to (11). Such an initial solution can be deemed as the closest PSD matrix to the unconstrained version of (7). Empirically, such an initial solution alone already leads to satisfactory prediction result.
      </paragraph>
     </section>
     <section label="3.6">
      <section-title>
       Time and space complexity
      </section-title>
      <paragraph>
       The space complexity of our algorithm is {a mathematical formula}O(mn), where n is sample size and m is the number of landmark points. Computationally, it only requires repeated eigenvalue decomposition of {a mathematical formula}m×m matrices, and a single multiplication between the {a mathematical formula}n×m extrapolation E and the {a mathematical formula}m×m dictionary kernel S. The overall time complexity is {a mathematical formula}O(m2n)+O(tlog⁡(μmax)m3), where t is the number of gradient mapping iterations, and {a mathematical formula}μmax is the maximum eigenvalue of the Hessian. This is because a in (10) is bounded by {a mathematical formula}μmax and one can always find a suitable step-length in {a mathematical formula}log⁡(μmax) steps. Empirically, with the initialization in Section 3.5, only a few iterations are needed. Therefore t is a small integer and our algorithm has a linear time and space complexity.
      </paragraph>
     </section>
     <section label="3.7">
      <section-title>
       Selecting the rank
      </section-title>
      <paragraph>
       The parameter m specifies the number of landmark points in the Nyström method. On the one hand, it directly determines the computational complexity, therefore the smaller the m, the more savings we can expect. On the other hand, m is closely related to the rank of the kernel matrix K. In practice, depending on the size of the kernel matrix and whether or not it really has a low-rank structure, m may be quite large. In [1], it was observed that even if the kernel matrix has a relatively high rank, using a low-rank approximation can still be useful in terms of the learning performance. Therefore in practice we typically choose m as 10% of the training sample size. In case the training data is very large and even 10% of the data still cannot fit in memory, we will set m as a small constant.
      </paragraph>
     </section>
     <section label="3.8">
      Selecting λ
      <paragraph>
       The hyper-parameter λ in (7) can be difficult to choose if the side information (e.g., partially labeled samples) is limited. Here we propose a heuristic to choose λ. Note that the objective (7) contains two residuals, {a mathematical formula}S0−S, and {a mathematical formula}ElSEl⊤−Kl⁎, in terms of the Frobenius norm, which are additive and require a tradeoff parameter λ. Here, we use a new criterion with certain invariance property to re-evaluate the goodness of the solution. More specifically, we used Normalized Kernel Alignment (NKA) [16] between kernel matrices,{a mathematical formula} where {a mathematical formula}〈⋅,⋅〉F is the Frobenius inner product, {a mathematical formula}Kc is the centered kernel associated to K. The NKA score always has a magnitude that is smaller than 1. It is independent of the scale of the solution, and is multiplicative by nature. Let {a mathematical formula}S(λ) be the optimum of (7) for a fixed λ. Then we choose the best λ by{a mathematical formula} Here {a mathematical formula}G is the set of candidate λ's. The criterion (15) has the following properties: (1) it is scale invariant, and does not require any extra trade-off parameter due to its multiplicative form; (2) the first term measures the closeness between S and {a mathematical formula}S0, which is related to unsupervised structures of kernel matrix; the second term measures the closeness between {a mathematical formula}ElSEl⊤ and {a mathematical formula}Kl⁎, which is related to side information; therefore the criterion is consistent with the objective (7) but is numerically different; (3) a higher alignment (second term in (15)) indicates existence of a good predictor with higher probability [16]; (4) computation of the criterion does not require any extra validation set, which is convenient if only limited labeled samples are available. Therefore, this is an informative criterion to measure the quality of the solution. Empirically, it correlates nicely with the prediction accuracy on the test samples, as will be reported in Section 6.1.
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Multiple kernel low-rank decompositions
     </section-title>
     <paragraph>
      In practical scenarios, the choice of kernel parameter (such as the Gaussian kernel width) can greatly affect the performance of learning algorithms. Recent research in multiple kernel learning has emphasized the need to adopt multiple kernels, which not only provides more flexibility but also alleviates the difficulty in hyper-parameter selection.
     </paragraph>
     <paragraph>
      We represent the desired kernel matrix using a mixture of low-rank decompositions. Suppose we use M different kernel parameters, each associated with a kernel matrix {a mathematical formula}K(j)∈Rn×n for {a mathematical formula}j=1,2,...,M. Among these M kernel matrices, we use a shared landmark set {a mathematical formula}Z and obtain their respective decomposition as{a mathematical formula} Then our objective is to learn the multiple dictionary kernels {a mathematical formula}S(j)'s such that the mixed kernel {a mathematical formula}K˜=∑jαjK(j) will maximally correlate with the ideal kernel on the labeled samples. To achieve this we use the following objective{a mathematical formula} Here {a mathematical formula}El(j) are the rows in {a mathematical formula}E(j) corresponding to labeled samples, and {a mathematical formula}K˜l are sub-block of {a mathematical formula}K˜ corresponding to labeled samples. The weighting coefficients {a mathematical formula}αj's are all non-negative, such that the mixed kernel {a mathematical formula}K˜ and its sub-block {a mathematical formula}K˜l are both PSD matrices. In the optimization problem (17), the first term states that for each kernel parameter (or a source domain), the dictionary {a mathematical formula}S(j) should be close to the prior {a mathematical formula}S0(j); the second term states that the mixed kernel should be aligned with the target variables on the labeled samples.
     </paragraph>
     <section label="4.1">
      <section-title>
       Alternating optimization
      </section-title>
      <paragraph>
       Fixing{a mathematical formula}αj's and solving{a mathematical formula}S(j)'s. When {a mathematical formula}αj's are fixed, we will solve {a mathematical formula}S(j)'s for {a mathematical formula}j=1,2,...,M in a cyclic manner. For each j, we have the following{a mathematical formula} By computing {a mathematical formula}αjS(j) together as a single variable {a mathematical formula}T(j), the resultant problem will be exactly the same as (7), namely{a mathematical formula} Here {a mathematical formula}S0(j)'s are computed in a similar way as (5). Finally, the mixed kernel is simply the summation of all {a mathematical formula}E(j)T(j)(E(j))⊤'s.
      </paragraph>
      <paragraph>
       Fixing{a mathematical formula}T(j)'s and solving{a mathematical formula}αj's. When {a mathematical formula}T(j)'s are fixed, solving {a mathematical formula}αj becomes the following{a mathematical formula}
      </paragraph>
      <paragraph>
       The closed-form solution for {a mathematical formula}αj is{a mathematical formula}
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Empirical setup for multiple kernel learning
      </section-title>
      <paragraph>
       In practice, we choose {a mathematical formula}M=5−10 different kernel matrices as bases. Here M either corresponds to the number of different kernel parameters or the number of source domains. The number of landmark points is chosen as {a mathematical formula}m¯. Usually we choose {a mathematical formula}m¯=m⋅τ/M, where m is the number of landmark points typically chosen for single kernel case. For example, if {a mathematical formula}τ=3, that means the complexity of the multiple kernel scenario would be three times as much as the single kernel case. The final learned kernel {a mathematical formula}K˜=∑jE(j)T(j)(E(j))⊤ can be written as{a mathematical formula} where{a mathematical formula}{a mathematical formula} which can be plugged in any kernel machine for training and testing.
      </paragraph>
      <paragraph>
       For computational efficiency, we first express {a mathematical formula}K˜ in decomposition form, such that only a linear algorithm needs to be implemented. The details are as follows. Compute the eigenvalue decomposition {a mathematical formula}T=UΛU⊤, and let {a mathematical formula}Q=EUΛ1/2. As shown in [34], the final kernel SVM using kernel matrix {a mathematical formula}K˜ can be equivalently transformed to a linear SVM using virtual samples {a mathematical formula}Q=EUΛ1/2. This decomposition itself is efficient since the matrix T is block-diagonal and therefore its eigenvalue decomposition can be performed independently inside each block, and the overall complexity is {a mathematical formula}O(M(m¯3+nm¯2)).
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Related work
     </section-title>
     <section label="5.1">
      <section-title>
       Low-rank decomposition
      </section-title>
      <paragraph>
       Low-rank decomposition is a powerful tool in scaling up machine learning algorithms. For example, Fine and Scheinberg [3] used low-rank approximation to solve the linear systems in interior-point iterations, which reduces the complexity of SVM from {a mathematical formula}O(n3) to {a mathematical formula}O(nr2). Similarly, in kernel k-means clustering [4], the per-iteration cost can be reduced from {a mathematical formula}O(n2) to {a mathematical formula}O(nkr). Other examples include spectral clustering [6], SVM [7] and manifold learning [27]. The Nyström method provides efficient approximation to low-rank decomposition of PSD matrices, with only linear space and time complexities [5]. It reconstructs the input matrix by sampling a subset of representative rows or columns. In the literature, various sampling strategies were studied including random sampling [5], [6], [35], probabilistic sampling [30], k-means based sampling [7], and adaptive sampling [31], [28].
      </paragraph>
     </section>
     <section label="5.2">
      <section-title>
       Kernel learning
      </section-title>
      <paragraph>
       In the literature, many algorithms have been proposed in kernel learning [10], [36], [12], [9], [13], [14], [15]. For example, many multiple kernel learning algorithms have been proposed to search for a combination of base kernel matrices that maximizes the alignment with the “ideal kernel” {a mathematical formula}K⁎(x,z)=y(x)y(z), where {a mathematical formula}y(x) is the class label of x[11]. However, most existing multiple kernel learning algorithms need to manipulate multiple {a mathematical formula}n×n base kernel matrices, which will take at least {a mathematical formula}O(n2) space and time. In comparison, the multiple-kernel-learning version of the proposed method still has a linear time and space complexity.
      </paragraph>
     </section>
     <section label="5.3">
      <section-title>
       Low-rank decomposition and kernel learning
      </section-title>
      <paragraph>
       Although both low-rank decomposition and kernel learning have been studied extensively, works on combining matrix low-rank decomposition with kernel learning were relatively limited.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Cholesky with Side Information
       </section-title>
       <paragraph>
        A pioneering work that incorporates class label information in the low-rank decomposition is the Cholesky with Side Information (CSI) [2]. It iteratively selects columns of the kernel matrix that maximally reduces the hybrid of the matrix approximation error and a linear prediction error, which can significantly reduce the rank of factorization needed in a kernel classifier. The complexity is linear in the number of data points.
       </paragraph>
       <paragraph>
        Our approach was motivated similarly but has important differences. First, the CSI method assumes that labels of all training instances are given (extension to semi-supervised setting is still an open problem); in comparison, we consider the more generalized semi-supervised learning scenario. Second, the CSI procedure is transductive and it does not provide a principled way to compute factorizations for new unseen samples; whereas our approach generalizes easily to new unseen samples by design.
       </paragraph>
      </section>
      <section label="5.3.2">
       <section-title>
        Bregman kernel learning
       </section-title>
       <paragraph>
        Although kernel learning has drawn considerable interest, there are few works that provide computationally efficient learning of low rank kernel matrices. Recently, Kulis et al. [37] proposed to learn a low-rank kernel by minimizing its divergence with an initial kernel subject to distance constraints. It can automatically enforce the positive definiteness of the kernel. In particular, by using the LogDet divergence one can evaluate the kernel function over new data points. Computationally, the algorithm has a time and space complexity that is quadratic with the sample size. An earlier work [38] adopted the von-Neumann matrix divergence to learn a (full rank) kernel matrix, whose complexity is cubic with sample size.
       </paragraph>
      </section>
      <section label="5.3.3">
       <section-title>
        Other methods
       </section-title>
       <paragraph>
        Recently, the low-rank constraint has been shown to be a useful tool for model regularization. For example, Shalit et al. [39] proposed an online learning procedure that consists of iterative gradient projections and efficient second-order retractions back to the low-rank manifold of PSD matrices. In [40], a low-rank kernel learning approach was proposed for regression by using conical combinations of base kernels and a stochastic optimization framework. The low-rank constraint was also used in matrix completion [41].
       </paragraph>
       <paragraph>
        Cesa-Bianchi et al. [42] pointed out some possible limitations of approximating the kernel matrix: it may be difficult to obtain a non-trivial classification accuracy if only a limited number of kernel evaluations is possible. They found that the performance of the approximation also depends on other factors such as the loss function and the regularization parameter, which provides a new perspective in scaling up kernel methods.
       </paragraph>
      </section>
     </section>
     <section label="5.4">
      <section-title>
       Sparse Gaussian processes
      </section-title>
      <paragraph>
       Gaussian Processes (GP) are a popular tool for non-parametric Bayesian inference for nonlinear regression and classification, which can be deemed as a Bayesian version of kernel methods. Recently, sparse Gaussian process has drawn considerable interest in scalable Gaussian process inference.
      </paragraph>
      <paragraph>
       Sparse Gaussian process is aimed at computing a prediction model that is composed of a small number of basis (“pseudo”-samples), in comparison with a dense model that potentially spans on all the available samples. In the regression setting, Matthias Seeger et al. [22] proposed a sparse greedy approximation for Gaussian process regression using a novel fast forward selection strategy to select candidate points, which can be interpreted as a direct approximation to the full GP marginal likelihood. Lawrence et al. [23] proposed the “Informative Vector Machine” (IVM), which used a fully randomized greedy scheme to select candidate points to include in the model, which leads to an approximation to a non-sparse GP model and competitive performance against SVM. Quiñonero-Candela and Rasmussen [24] proposed a unifying view of many existing sparse approximate Gaussian process methods by analyzing the so-called “effective prior” adopted in different methods, giving more insights on the impact of approximations.
      </paragraph>
      <paragraph>
       Besides greedy selection, the locations of the pseudo-inputs can also be optimized together with other variational parameters or hyper-parameters (e.g. kernel function, noise parameter) in a principled way in learning the model. For example, Snelson and Ghahramani [19] proposed a smooth joint optimization framework to find the locations of a small, active set of point locations (also called “pseudo-inputs”) and kernel/noise parameters, which can significantly reduce the computational cost of Gaussian process regression to {a mathematical formula}O(m2n) where m is the number of pseudo-inputs and n is the sample size. Titsias [20] proposed a variational formulation for sparse approximations that jointly infers the inducing inputs (as variational parameters) and the kernel hyper-parameters by maximizing a lower bound of the true log marginal likelihood. Very recently, Hensman et al. [21] proposed novel variational bounds on the marginal likelihood that allow for more efficient inference not only in regression, but also in the more challenging classification setting. In particular, one of their marginal bounds avoids introducing additional latent variables or factorizing assumptions, which combines the scalability of the stochastic optimization with the ability to optimize the positions of the inducing points. Their method has been shown to work efficiently on millions of data points. Sheth et al. [43] generalized this for general likelihood, including classification, regression, ordinal prediction, count prediction etc.
      </paragraph>
      <paragraph>
       For semi-supervised learning, Lawrence and Jordan [44] proposed the Null Category Noise Model (NCNM) for semi-supervised classification, by extending the IVM method in [23] that finds the decision boundary which avoids passing through densely populated regions. Srijith et al. [45] proposed a semi-supervised ordinal regression using Gaussian Processes, by matching ordinal label distributions approximately between labeled and unlabeled data.
      </paragraph>
      <paragraph>
       The important advantage of sparse Gaussian process regression is that a principled selection of the active sets (i.e., the locations of the basis vectors) can be achieved, often in conjunction with the kernel matrix (and other hyper-parameters) in a joint optimization framework thanks to the flexible Bayesian inference procedures. In other words, all the parameters can be learned simultaneously using available training samples and their labels. This can be attractive in terms of both theoretical analysis and convenience for practitioners. In comparison, our approach adopts a more heuristic, two-step procedure. In the first (unsupervised) step, representative samples are selected mainly based on the data distribution so as to better approximate the kernel matrix in the form of low-rank decomposition; in the second (semi-supervised) step, the kernel matrix defined on the representative samples is then computed using available training labels (which will be further extrapolated to the whole data set), and so a kernel-based classifier can be finally obtained using the learned kernel matrix. In other words, the training samples and their labels are utilized separately in two different but consecutive steps in our approach. Our approach has the advantage that the semi-supervised formulation is naturally easier than the one in Gaussian Process. On the other hand, the GP approach works with general likelihoods, not just classification, whereas our use of the kernel alignment is limited to classification.
      </paragraph>
     </section>
    </section>
    <section label="6">
     <section-title>
      Experiments
     </section-title>
     <paragraph>
      In this section, we have performed extensive experiments to compare the proposed methods with state-of-the-arts techniques across different benchmark data sets. We report our experimental results for single kernel setting and multiple kernel setting in Section 6.1 and Section 6.2, respectively.
     </paragraph>
     <section label="6.1">
      <section-title>
       Single kernel setting
      </section-title>
      <paragraph>
       This section compares 8 algorithms on learning low-rank kernel: (1) LibSVM [46]: support vector machine, which uses only the small number of labeled samples for training; (2) Nyström: standard Nyström method; (3) CSI: Cholesky with Side Information [2]; (4) Cluster: cluster kernel [47]; (5) Spectral: non-parametric spectral graph kernel [17]; (6) Breg: low-rank kernel learning with Bregman divergence [37]; (7) NCNM [44]: Sparse Gaussian Process for Semi-supervised Learning; and (8) Our proposed method. Most algorithms can learn the {a mathematical formula}n×n low-rank kernel{sup:2} matrix on labeled and unlabeled samples{sup:3} in the form of {a mathematical formula}K=GG⊤, which can then be fed into an SVM for classification. The resultant problem will be a linear SVM using G as training/testing samples [34].
      </paragraph>
      <paragraph>
       We use benchmark data sets from the SSL data sets [48]{sup:4} and the LIBSVM data.{sup:5} For each data set, we randomly pick 100 labeled samples evenly among all classes and use the remaining samples as unlabeled data, repeat 30 times, and report the averaged classification error on unlabeled data. We use the Gaussian kernel {a mathematical formula}K(x1,x2)=exp⁡(−‖x1−x2‖2/b). Parameter selection is difficult in semi-supervised learning, so, we chose the kernel width as the averaged pairwise squared distances between samples because it empirically gives reasonable performance. For the regularization parameter C in linear SVM, we use the heuristic implemented in LIBLINEAR package [49]. Most implementations are in Matlab (for method (3) we use implementation in [2] with core functions written in C) and run on a PC with 2G memory and 2.8 GHz processor.
      </paragraph>
      <paragraph>
       Results are reported in Table 1. Methods statistically better than others with a confidence level that is at least {a mathematical formula}95% (paired t-test) are highlighted. Method (1) and (2) are baseline methods that do not involve any kernel learning, therefore they are computationally very efficient. Note that Method (1) only uses labeled samples for training, so it has higher error rates. Method (3) is computationally efficient as well because it only uses labeled samples for training. Method (4) and (5) require eigenvalue decomposition of the kernel matrix (or graph Laplacian), therefore they are computationally more expensive. Method (6) and (7) are observed to require a relatively larger number of iterations to converge. Our approach is very efficient and can be orders of magnitudes faster than methods (4), (5), (6) and (7).
      </paragraph>
      <paragraph>
       From Table 1, we can see that on most data sets, algorithms using labels in kernel learning outperform the baseline algorithm (standard Nyström), indicating the value of side information. Our approach is competitive with state-of-the-art kernel learning algorithms. On the largest data set mnist, method (4), (5), (7) can not run on our PC due to huge memory consumption; in comparison, our approach is very efficient and gives the lowest error rate on this data set. We also examine the alignment score (15) used to choose the hyper-parameter λ in Fig. 1. As can be seen, the alignment score correlates nicely with the classification accuracy on unlabeled data.
      </paragraph>
     </section>
     <section label="6.2">
      <section-title>
       Multiple kernels setting
      </section-title>
      <paragraph>
       In this section we explore the multiple kernel learning scenario. The data sets used for evaluating the performance are summarized in Table 2. For each data set, we randomly pick 100 labeled samples evenly among all classes, repeat 30 times, and report the averaged classification error on unlabeled data. By changing the RBF kernel parameter b used in the Gaussian kernel {a mathematical formula}K(x1,x2)=exp⁡(−‖x1−x2‖2/b) from {a mathematical formula}{2−4b0,2−3b0,…,23b0,24b0}, where {a mathematical formula}b0 is the average pairwise squared distances between samples, we choose altogether 9 base kernel matrices.
      </paragraph>
      <paragraph>
       We compare our proposed method with the following 5 state-of-the-art multiple kernel learning algorithms{sup:6}: (1) ABMKL: Alignment based Multiple Kernel Learning [9]; (2) CABMKL: Center Alignment based Multiple Kernel Learning [16]; (3) Support Kernel Machines (SKM): a SMO-like algorithm for multiple kernel learning proposed by Bach et al. [13]; (4) SimpleMKL: an alternating optimization approach for multiple kernel learning [14] and (5) GLMKL: Group lasso-based Multiple Kernel Learning [15]. We set the regularization parameter C in SVM to 1 for all algorithms. The parameter λ for our proposed method is chosen from {a mathematical formula}{10−5,10−4,…,104,105}. Similarly to (15), the optimal λ for multiple kernel learning is also selected based on the alignment score as follows,{a mathematical formula}
      </paragraph>
      <paragraph>
       Experimental results are reported in Table 2. The computing time is evaluated on a laptop with 4 G memory and Intel{sup:®} Core{sup:™} i5-3317U CPU@1.70 GHz. For each data set, the methods statistically better than others with a confidence level that is at {a mathematical formula}95% are highlighted in bold. As shown in Table 2, our proposed method achieves the lowest classification error on 11 out of 17 data sets. For the other 6 data sets, our method is the second best in 5 data sets (i.e., USPS, german, usps49, usps27 and svmgd1a). Overall, our method performs better than other multiple kernel learning algorithms. In terms of computing time, our method is much faster than other methods on large datasets with sample size larger than 6,000 (i.e., satimage, usps-full, mnist, webspam).
      </paragraph>
      <paragraph>
       The effect of number of labeled samples. We use the mnist dataset with 70,000 samples to study how the computing time and classification error rate changes when the number of labeled samples increases. In our experimental setting, the number of labeled samples varies from {a mathematical formula}l={200,300,400,…,1000,2000,3000}. We use the remaining {a mathematical formula}n−l{a mathematical formula}(n=70,000) unlabeled samples to evaluate the classification error rate. As shown in the subfigure (a) of Fig. 2, the error rate decreases when the number of labeled samples increases. The error rates obtained by our methods on mnist dataset are significantly lower than other multiple kernel learning algorithms. The subfigure (b) of Fig. 2 clearly shows our method are several times faster than other algorithms. In our experimental setting, the computing time is dominated by prediction time because the number of labeled samples is very small compared to the data size. So, as shown in the subfigure (b) of Fig. 2, the computing time of other multiple kernel learning algorithms roughly increases linearly with the number of labeled samples. The computing time of our proposed method do not increase because we fixed the number of landmark points (i.e., the rank of the learned kernel) at 100.
      </paragraph>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     Comparison of different choices of β
     <paragraph>
      In this section, we present our empirical results on testing two different methods for choosing the scaling factor β in (5): (1) A heuristic way as shown in (8); and (2) Iterative optimization of β with S in (7). The experimental setting is the same as in section 6.1. Our empirical results are summarized in Table A1. Overall speaking, the iterative approach can be a little more accurate but computationally more expensive.
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>