<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    On the doubt about margin explanation of boosting.
   </title>
   <abstract>
    Margin theory provides one of the most popular explanations to the success of AdaBoost, where the central point lies in the recognition that margin is the key for characterizing the performance of AdaBoost. This theory has been very influential, e.g., it has been used to argue that AdaBoost usually does not overfit since it tends to enlarge the margin even after the training error reaches zero. Previously the minimum margin bound was established for AdaBoost, however, Breiman (1999) [9] pointed out that maximizing the minimum margin does not necessarily lead to a better generalization. Later, Reyzin and Schapire (2006) [37] emphasized that the margin distribution rather than minimum margin is crucial to the performance of AdaBoost. In this paper, we first present the kth margin bound and further study on its relationship to previous work such as the minimum margin bound and Emargin bound. Then, we improve the previous empirical Bernstein bounds (Audibert et al. 2009; Maurer and Pontil, 2009) [2], [30], and based on such findings, we defend the margin-based explanation against Breimanʼs doubts by proving a new generalization error bound that considers exactly the same factors as Schapire et al. (1998) [39] but is sharper than Breimanʼs (1999) [9] minimum margin bound. By incorporating factors such as average margin and variance, we present a generalization error bound that is heavily related to the whole margin distribution. We also provide margin distribution bounds for generalization error of voting classifiers in finite VC-dimension space.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      The AdaBoost algorithm [18], [19], which aims to construct a “strong” classifier by combining some “weak” learners (slightly better than random guess), is a representative of ensemble methods [47] and has been one of the most influential classification algorithms [13], [45], and it has exhibited excellent performance both on benchmark datasets and real applications [5], [16].
     </paragraph>
     <paragraph>
      Many studies are devoted to understanding the mysteries behind the success of AdaBoost, among which the margin theory proposed by Schapire et al. [39] has been very influential. For example, AdaBoost often tends to be empirically resistant (but not completely) to overfitting [8], [17], [35], i.e., the generalization error of the combined learner keeps decreasing as its size becomes very large and even after the training error has reached zero; it seems violating the Occamʼs razor [7], i.e., the principle that less complex classifiers should perform better. This remains one of the most famous mysteries of AdaBoost. The margin theory provides the most intuitive and popular explanation to this mystery, that is: AdaBoost tends to improve the margin even after the error on training sample reaches zero.
     </paragraph>
     <paragraph>
      However, Breiman [9] raised serious doubt on the margin theory by designing arc-gv, a boosting-style algorithm. This algorithm is able to maximize the minimum margin, i.e., the smallest margin over the training data (the formal definition will be given in Eq. (2)), but its generalization error is high on empirical datasets, and similar experimental evidence has also been observed in [22]. Thus, Breiman [9] concluded that the margin theory for AdaBoost failed. Breimanʼs argument was backed up with a minimum margin bound, which is sharper than the generalization bound given by Schapire et al. [39], and a lot of experiments. Garg and Roth [21] presented a margin-distribution algorithm based on a data-dependent complexity measure. Later, Reyzin and Schapire [37] found that there were flaws in the design of experiments: Breiman used CART trees [11] as base learners and fixed the number of leaves for controlling the complexity of base learners. However, Reyzin and Schapire [37] found that the trees produced by arc-gv were usually much deeper than those produced by AdaBoost. Generally, for two trees with the same number of leaves, the deeper one is with a larger complexity because more judgments are needed for making a prediction. Therefore, Reyzin and Schapire [37] concluded that Breimanʼs observation was biased due to the poor control of model complexity. They repeated the experiments by using decision stumps for base learners, considering that decision stump has exactly two leaves and thus with a fixed complexity, and observed that though arc-gv produced a larger minimum margin, its margin distribution was quite poor. Nowadays, it is well-accepted that the margin distribution is crucial to relate margin to the generalization performance of AdaBoost. To support the margin theory, Wang et al. [44] presented a sharper bound in term of Emargin (the formal definition will be given in Theorem 3), which was believed to be relevant to margin distribution.
     </paragraph>
     <paragraph>
      In this paper, we first present the kth margin bound and further study its relationship to previous work such as the minimum margin bound and Emargin bound. Then, by using empirical Bernstein bounds, we present a new generalization error bound for voting classifier, which considers exactly the same factors as Schapire et al. [39], but is sharper than the bounds of Schapire et al. [39] and Breiman [9]. Therefore, we defend the margin-based explanation against Breimanʼs doubt. Moreover, we provide a generalization error bound, by incorporating other factors such as average margin and variance, which are heavily relevant to the whole margin distribution. We also give a margin distribution bound for generalization error of voting classifiers in finite VC-dimension space. It is also worth mentioning that our new empirical Bernstein bounds improve the main results of [2], [30], with a simpler proof, and we present empirical Bernstein bounds for finite VC-dimension space; these results can be interesting, independently to the main purpose of the paper, to the machine learning community.
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. We begin with some notations and background in Sections 2 and 3, respectively. Then, we prove the kth margin bound and discuss on its relation to previous bounds in Section 4. Our main results are presented in Section 5, and detailed proofs are provided in Section 6. We conclude in Section 7.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Notations
     </section-title>
     <paragraph>
      Let {a mathematical formula}X and {a mathematical formula}Y denote an input space and output space, respectively. In this paper, we focus on binary classification problems, i.e., {a mathematical formula}Y={+1,−1}. Denote by D an (unknown) underlying probability distribution over the product space {a mathematical formula}X×Y. A training sample of size m{a mathematical formula} is drawn independently and identically (i.i.d.) according to the distribution D. We use {a mathematical formula}PrD[⋅] to refer as the probability with respect to D, and {a mathematical formula}PrS[⋅] to denote the probability with respect to uniform distribution over the sample S. Similarly, we use {a mathematical formula}ED[⋅] and {a mathematical formula}ES[⋅] to denote the expected values, respectively. For an integer {a mathematical formula}m&gt;0, we set {a mathematical formula}[m]={1,2,…,m}.
     </paragraph>
     <paragraph>
      The Bernoulli Kullback–Leibler (or KL) divergence is defined as{a mathematical formula} For a fixed q, we can easily find that {a mathematical formula}KL(q‖p) is a monotone increasing function for {a mathematical formula}q⩽p&lt;1, and thus, the inverse of {a mathematical formula}KL(q‖p) for the fixed q is given by{a mathematical formula}
     </paragraph>
     <paragraph>
      Let {a mathematical formula}H be a hypothesis space. A base learner is a function which maps a distribution over {a mathematical formula}X×Y onto a function {a mathematical formula}h:X→Y. In this paper, we only focus on binary base classifiers, i.e., the outputs are in {a mathematical formula}{−1,1}. Let {a mathematical formula}C(H) denote the convex hull of H, i.e., a voting classifier {a mathematical formula}f∈C(H) is of the following form{a mathematical formula} For {a mathematical formula}N⩾1, denote by {a mathematical formula}CN(H) the set of unweighted averages over N elements from {a mathematical formula}H, that is{a mathematical formula} For voting classifier {a mathematical formula}f∈C(H), we can associate with a distribution over {a mathematical formula}H by using the coefficients {a mathematical formula}{αi}, denoted by {a mathematical formula}Q(f). For convenience, {a mathematical formula}g∈CN(H)∼Q(f) implies {a mathematical formula}g=∑j=1Nhj/N where {a mathematical formula}hj∼Q(f).
     </paragraph>
     <paragraph>
      For an example {a mathematical formula}(x,y), the margin with respect to the voting classifier {a mathematical formula}f=∑αihi(x) is defined as {a mathematical formula}yf(x); in other words,{a mathematical formula} which shows the difference between the weights of base learners that classify {a mathematical formula}(x,y) correctly and the weights of base learners that misclassify {a mathematical formula}(x,y). Therefore, margin can be viewed as a measure of the confidence of the classification. Given a sample {a mathematical formula}S={(x1,y1),(x2,y2),…,(xm,ym)}, we denote by {a mathematical formula}yˆ1f(xˆ1) the minimum margin and {a mathematical formula}ES[yf(x)] the average margin, which are defined respectively as follows:{a mathematical formula}
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Background
     </section-title>
     <paragraph>
      In the statistics community, great efforts have been devoted to understanding how and why AdaBoost works. Friedman et al. [20] made an important stride by viewing AdaBoost as a stagewise optimization and relating it to fitting an additive logistic regression model. Various new boosting-style algorithms were developed by performing a gradient decent optimization of some potential loss functions [12], [28], [36]. Based on this optimization view, some boosting-style algorithms and their variants have been shown to be Bayesʼs consistent under different settings [3], [4], [6], [10], [24], [27], [34], [46], i.e., those studies theoretically ensure that boosting is asymptotically convergent to the Bayesʼs classifiers. However, such theories cannot be used to explain the resistance of AdaBoost to overfitting for small sample problems, and some statistical views have been questioned by Mease and Wyner [33] with empirical evidences. In this paper, we focus on margin theory.
     </paragraph>
     <paragraph>
      Algorithm 1 provides a unified description of AdaBoost and arc-gv. The only difference between them lies in the choice of {a mathematical formula}αt. In AdaBoost, {a mathematical formula}αt is chosen by{a mathematical formula} where {a mathematical formula}γt=∑i=1mDt(i)yiht(xi) is called the edge of {a mathematical formula}ht, which is an affine transformation of the error rate of {a mathematical formula}ht(x). However, Arc-gv sets {a mathematical formula}αt in a different way. Denote by {a mathematical formula}ρt the minimum margin of the voting classifier of round {a mathematical formula}t−1, that is,{a mathematical formula} where{a mathematical formula} Then, Arc-gv sets {a mathematical formula}αt as to be{a mathematical formula}
     </paragraph>
     <paragraph>
      Schapire et al. [39] proposed the first margin theory for AdaBoost and upper bounded the generalization error as follows:
     </paragraph>
     <paragraph label="Theorem 1">
      (See[39].) For any{a mathematical formula}δ&gt;0and{a mathematical formula}θ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size m, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}
     </paragraph>
     <paragraph>
      Breiman [9] provided the minimum margin bound for arc-gv by Theorem 2 with our notations.
     </paragraph>
     <paragraph label="Theorem 2">
      (See[9].) If{a mathematical formula}then, for any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size m, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}
     </paragraph>
     <paragraph>
      Empirical results show that arc-gv probably generates a larger minimum margin but with higher generalization error, and Breimanʼs minimum bound is {a mathematical formula}O(lnm/m), sharper than {a mathematical formula}O(lnm/m) in Theorem 1. Thus, Breiman cast serious doubt on margin theory. To support the margin theory, Wang et al. [44] presented a sharper bound in term of Emargin by Theorem 3, which was believed to be related to margin distribution. Notice that the factors considered by Wang et al. [44] are different from that considered by Schapire et al. [39] and Breiman [9].
     </paragraph>
     <paragraph label="Theorem 3">
      (See[44].) If{a mathematical formula}8&lt;|H|&lt;∞, then for any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of the training set S of size{a mathematical formula}m&gt;1, every voting classifier{a mathematical formula}f∈C(H)such that{a mathematical formula}satisfies the following bound:{a mathematical formula}where{a mathematical formula}and{a mathematical formula}θˆ(q)=sup{θ∈(8/|H|,1]:PrS[yf(x)⩽θ]⩽q}. Also, the Emargin is given by{a mathematical formula}θ⁎∈arginfq∈{q0,q0+1m,…,1}KL−1(q;u[θˆ(q)]).
     </paragraph>
     <paragraph>
      Instead of the whole function space, much work developed margin-based data-dependent bounds for generalization error, e.g., empirical cover number [40], empirical fat-shattering dimension [1], Rademacher and Gaussian complexities [25], [26], etc. Some of these bounds are proven to be sharper than Theorem 1, but it is hard to show that these bounds are sharper than the bounds of Theorem 2, Theorem 3, and fail to explain the resistance of AdaBoost to overfitting.
     </paragraph>
    </section>
    <section label="4">
     The kth margin bounds
     <paragraph>
      Given a sample S of size m, we define the kth margin{a mathematical formula}yˆkf(xˆk) as the kth smallest margin over sample S, i.e., the kth smallest value in {a mathematical formula}{yif(xi),i∈[m]}. The following theorem shows that the kth margin can be used to measure the performance of a voting classifier, whose proof is deferred in Section 6.1.
     </paragraph>
     <paragraph label="Theorem 4">
      For any{a mathematical formula}δ&gt;0and{a mathematical formula}k∈[m], if{a mathematical formula}θ=yˆkf(xˆk)&gt;8/|H|, then with probability at least{a mathematical formula}1−δover the random choice of sample with size m, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}Particularly, when k is constant with{a mathematical formula}m&gt;4k, we have{a mathematical formula}
     </paragraph>
     <paragraph>
      Here, we present the kth margin bound to link previous results on margin bounds, and it is interesting to study the relation between Theorem 4 and previous results, especially Theorem 2, Theorem 3. It is straightforward to get a result similar to Breimanʼs minimum margin bound in Theorem 2, by setting {a mathematical formula}k=1 in Eq. (5):
     </paragraph>
     <paragraph label="Corollary 1">
      For any{a mathematical formula}δ&gt;0, if{a mathematical formula}θ=yˆ1f(xˆ1)&gt;8/|H|, then with probability at least{a mathematical formula}1−δover the random choice of sample S with size m, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}
     </paragraph>
     <paragraph>
      Notice that when k is a constant, the bound in Eq. (5) is {a mathematical formula}O(lnm/m) and the only difference lies in the coefficient. Thus, there is no essential difference to select constant kth margin (such as the 2nd margin, the 3rd margin, etc.) to measure the confidence of classification for large-size sample.
     </paragraph>
     <paragraph>
      Based on Theorem 4, it is not difficult to get a result similar to the Emargin bound in Theorem 3 as follows:
     </paragraph>
     <paragraph label="Corollary 2">
      For any{a mathematical formula}δ&gt;0, if{a mathematical formula}θk=yˆkf(xˆk)&gt;8/|H|, then with probability at least{a mathematical formula}1−δover the random choice of the sample S with size m, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}
     </paragraph>
     <paragraph>
      From this corollary, we can easily understand that the Emargin bound ought to be tighter than the minimum margin bound because the former takes the infimum over all {a mathematical formula}k∈[m] while the latter only focuses on the minimum margin. Intuitively, the bound of Corollary 2 might be sharper than that of Corollary 1 if the minimum margin is very small whereas some kth margin is very large. We also notice that, as shown by Eq. (2), the minimum margin can also be expressed as taking the infimum over all margin, whereas it is well accepted that the minimum margin bound is a single-margin bound.
     </paragraph>
    </section>
    <section label="5">
     <section-title>
      Main results
     </section-title>
     <paragraph>
      We begin with the standard deviation bounds as follows:
     </paragraph>
     <paragraph label="Theorem 5">
      For independent random variables{a mathematical formula}X1,X2,…,Xm{a mathematical formula}(m⩾5)with values in{a mathematical formula}[0,1], and for{a mathematical formula}δ∈(0,1), we have{a mathematical formula}{a mathematical formula}where the sample variance{a mathematical formula}Vˆm=∑i≠j(Xi−Xj)2/2m(m−1).
     </paragraph>
     <paragraph>
      The detailed proof is presented in Section 6.2. This theorem improves the results of [30, Theorem 10], especially for Eq. (6). Based on this result, we can derive the following empirical Bernstein bounds, with proof deferred to Section 6.3.
     </paragraph>
     <paragraph label="Theorem 6">
      For independent random variables{a mathematical formula}X1,X2,…,Xm{a mathematical formula}(m⩾5)with values in{a mathematical formula}[0,1], and for{a mathematical formula}δ∈(0,1), with probability at least{a mathematical formula}1−δwe have{a mathematical formula}{a mathematical formula}where{a mathematical formula}Vˆm=∑i≠j(Xi−Xj)2/2m(m−1).
     </paragraph>
     <paragraph>
      For identical and independent distribution (i.i.d.) variables, we have
     </paragraph>
     <paragraph label="Corollary 3">
      For i.i.d. random variables{a mathematical formula}X,X1,X2,…,Xm{a mathematical formula}(m⩾5)with values in{a mathematical formula}[0,1], and for{a mathematical formula}δ∈(0,1), with probability at least{a mathematical formula}1−δwe have{a mathematical formula}{a mathematical formula}where{a mathematical formula}Vˆm=∑i≠j(Xi−Xj)2/2m(m−1).
     </paragraph>
     <paragraph>
      There are two results [2], [30] closely related to Theorem 6 (or Corollary 3). Audibert et al. [2] presented the first empirical Bernstein bound and applied to analyze multi-armed bandit algorithms. Soon after, Maurer and Pontil [30] improved the constants and explored the sample variance penalization methods. Comparing with these results, our bounds in Eqs. (8) and (9) are with better constants and the technique of proof is simpler.
     </paragraph>
     <paragraph>
      Based on this Corollary 3, we can derive the following corollary for the finite function space:
     </paragraph>
     <paragraph label="Corollary 4">
      Let{a mathematical formula}S={X1,…,Xm}{a mathematical formula}(m⩾5)be drawn i.i.d. from a distribution{a mathematical formula}Dover{a mathematical formula}X, and let{a mathematical formula}H={h:X→[0,1]}be a finite function space. For any{a mathematical formula}δ∈(0,1), every{a mathematical formula}h∈Hsatisfies the following bound with probability at least{a mathematical formula}1−δ:{a mathematical formula}where{a mathematical formula}Vˆm(h)=∑i≠j(h(Xi)−h(Xj))2/2m(m−1).
     </paragraph>
     <paragraph>
      Then, we get a new generalization bound for infinite hypothesis space with finite VC-dimension, with proof deferred to Section 6.4.
     </paragraph>
     <paragraph label="Theorem 7">
      Let{a mathematical formula}S={X1,…,Xm}{a mathematical formula}(m⩾5)be drawn i.i.d. from a distribution{a mathematical formula}Dover{a mathematical formula}X, and let{a mathematical formula}H={h:X→{0,1}}be a hypothesis space with finite VC-dimension d. For any{a mathematical formula}δ∈(0,1), every{a mathematical formula}h∈Hsatisfies the following bound with probability at least{a mathematical formula}1−δ:{a mathematical formula}where{a mathematical formula}Vˆm(h)=∑i≠j(h(Xi)−h(Xj))2/2m(m−1).
     </paragraph>
     <paragraph>
      We now present our first margin bound for AdaBoost as follows:
     </paragraph>
     <paragraph label="Theorem 8">
      For any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size{a mathematical formula}m⩾5, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}
     </paragraph>
     <paragraph>
      This proof is based on the techniques developed by Schapire et al. [39], and the main difference is that we utilize the empirical Bernstein bound of Eq. (8) in Theorem 6 for the derivation of generalization error. The detailed proof is deferred to Section 6.5.
     </paragraph>
     <paragraph>
      It is noteworthy that Theorem 8 shows that the generalization error can be bounded in term of the empirical margin distribution {a mathematical formula}PrS[yf(x)⩽θ], the training sample size and the hypothesis complexity; in other words, this bound considers exactly the same factors as Schapire et al. [39] in Theorem 1. However, the following corollary shows that, the bound in Theorem 8 is sharper than the bound of Schapire et al. [39] in Theorem 1, as well as the minimum margin bound of Breiman [9] in Theorem 2.
     </paragraph>
     <paragraph label="Corollary 5">
      For any{a mathematical formula}δ&gt;0, if the minimum margin{a mathematical formula}θ1=yˆ1f(xˆ1)&gt;0and{a mathematical formula}m⩾5, then we have{a mathematical formula}where{a mathematical formula}μ=8lnmln(2|H|)/θ2+ln(2|H|/δ)and{a mathematical formula}μ1=8lnmln(2|H|)/θ12+ln(2|H|/δ); moreover, if{a mathematical formula}{a mathematical formula}{a mathematical formula}then we have{a mathematical formula}
     </paragraph>
     <paragraph>
      This proof is deferred to Section 6.6. From Eq. (10), we can see clearly that the bound of Theorem 8 is {a mathematical formula}O(lnm/m), sharper than the bound of Schapire et al. [39]{a mathematical formula}O(lnm/m) in Theorem 1. In fact, we could also guarantee that bound of Theorem 8 is {a mathematical formula}O(lnm/m) even under weaker assumption that {a mathematical formula}yˆkf(xˆk)&gt;0 for some {a mathematical formula}k⩽O(lnm).
     </paragraph>
     <paragraph>
      It is also noteworthy Eqs. (11) and (12) are the conditions of Theorem 2, and the term {a mathematical formula}exp(θ124ln(2|H|)ln|H|δ)⩽(eδ)14 in Eq. (13), which is small for many real applications, e.g., it is less than 13 even if {a mathematical formula}δ=0.0001. Eq. (14) shows that the bound of Theorem 8 is sharper than Breimanʼs minimum margin bound of Theorem 2.
     </paragraph>
     <paragraph>
      Breiman [9] doubted the margin theory because of two recognitions: (i) the minimum margin bound of Breiman [9] is sharper than the margin distribution bound of Schapire et al. [39], and therefore, the minimum margin is more essential than margin distribution to characterize the generalization performance; (ii) arc-gv maximizes the minimum margin, but demonstrates worse performance than AdaBoost empirically. However, our result shows that the margin distribution bound in Theorem 1 can be greatly improved such that it is even sharper than the minimum margin bound, and therefore, it is natural that AdaBoost outperforms arc-gv empirically on some datasets; in a word, our results provide a complete answer to Breimanʼs doubt on margin theory.
     </paragraph>
     <paragraph>
      The Emargin bounds of Wang et al. [44] are also proven to be sharper than those of Schapire et al. [39] and Breiman [9]. The main difference between Theorem 8 and the Emargin bounds lies in the consideration of different factors for margin theory, e.g., Theorem 8 considers exactly the same factors as Schapire et al. [39], whereas Wang et al. [44] considered the Emargin as the key factor. Moreover, Theorem 8 is advantageous in that its margin interval is wider than that of Emargin.{sup:1} Note that it is not easy to directly compare Theorem 8 and the Emargin bounds because it is difficult to get a closed-form for the {a mathematical formula}D−1(p‖q) term contained in the Emargin bounds, whereas Theorem 8 is relatively easier to estimate.
     </paragraph>
     <paragraph>
      It is well-accepted that the margin distribution is crucial to relate margin to the generalization performance of AdaBoost, whereas it is unclear how to measure the “goodness” of a margin distribution. The first-order and second-order statistics, i.e., the average margin and variance, are natural and intuitive measures. Indeed, Reyzin and Schapire [37] have recommended to take the average margin for a characterization of the margin distribution. However, there is no theory, to the best of our knowledge, to support that a larger average margin or a smaller variance implies a smaller generalization error. The following theorem fills the gap for such theory:
     </paragraph>
     <paragraph label="Theorem 9">
      For any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size{a mathematical formula}m⩾5, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph>
      The detailed proof is deferred to Section 6.7. It is easy to find in almost all boosting experiments that the average margin {a mathematical formula}ES[yf(x)] is positive. Thus, the bound of Theorem 9 can be sharper for larger average margin. The statistics {a mathematical formula}Iˆ(⋅) reflects the margin variance in some sense, and the term including {a mathematical formula}Iˆ(⋅) can be small or even vanished except for a small interval when the variance is small. This new generalization error bound depends not only on the sample size and the complexity of base classifiers, but also on the average margin, variance, and empirical margin distribution; this implying that, completely explaining AdaBoostʼs resistance to overfitting is more difficult than what has been expected and disclosed by previous theoretical results.
     </paragraph>
     <paragraph>
      Theorem 9 also provides a theoretical support to the suggestion of Reyzin and Schapire [37]; that is, the average margin can be used to measure the performance. It is noteworthy that, however, merely considering the average margin is insufficient to bound the generalization error tightly, as shown by the simple example in Fig. 1. Indeed, as this theorem discloses, “average” and “variance” are two important statistics to capture a distribution, and it is reasonable that both the average margin and margin variance are considered.
     </paragraph>
     <paragraph>
      We have the following corollary with proof presented in Section 6.8.
     </paragraph>
     <paragraph label="Corollary 6">
      If the minimum margin{a mathematical formula}θ1=yˆ1f(xˆ1)&gt;0, then, for any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size{a mathematical formula}m⩾5, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}μ1=144lnmln(2|H|)/θ12+ln(2|H|/δ), μ and{a mathematical formula}Iˆ(θ)are given inTheorem 9.
     </paragraph>
     <paragraph>
      This corollary shows that the bounds of Theorem 9 are {a mathematical formula}O(lnm/m), comparable to the Emargin bounds [44] and the bounds of Theorem 8, but with different constants. The main difference lies in the consideration of different factors, as we have considered the average margin and variance, that are better for the characterization of margin distribution. It is noteworthy that the best bounds for AdaBoost and arc-gv are both {a mathematical formula}O(lnm/m) whereas AdaBoost outperforms arc-gv empirically because AdaBoost tends to improve the margin distribution; this provides an example showing that it is very important to consider factors that are heavily relevant to the whole distribution. We also notice that a recent study in [41] provides empirical evidence to support our theoretical result. Indeed, designing new Boosting algorithms that maximize average margin but minimize variance simultaneously is an interesting direction, and [42] may shed some light.
     </paragraph>
     <paragraph>
      Finally, we generalize our main margin bounds to the case when the space of base classifiers has finite VC-dimension. The detailed proofs are presented in Section 6.9.
     </paragraph>
     <paragraph label="Theorem 10">
      If the base classifiers space{a mathematical formula}Hhas finite VC-dimension d, then for any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size{a mathematical formula}m⩾5, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}μ=8lnmθ2(ln2+dln(2em/d))+ln(8δ(1+8lnmθ2)).
     </paragraph>
     <paragraph label="Theorem 11">
      If the base classifiers space{a mathematical formula}Hhas finite VC-dimension d, then for any{a mathematical formula}δ&gt;0, with probability at least{a mathematical formula}1−δover the random choice of sample S with size{a mathematical formula}m⩾5, every voting classifier{a mathematical formula}f∈C(H)satisfies the following bound:{a mathematical formula}where{a mathematical formula}{a mathematical formula}
     </paragraph>
    </section>
    <section label="6">
     <section-title>
      Proofs
     </section-title>
     <paragraph>
      In this section, we provide the detailed proofs for the main theorems and corollaries. First, we present a series of useful lemmas as follows:
     </paragraph>
     <paragraph label="Lemma 1">
      Chernoff bound(See[14].) Let{a mathematical formula}X,X1,X2,…,Xmbe{a mathematical formula}m+1i.i.d. random variables with{a mathematical formula}X∈[0,1]. Then, for any{a mathematical formula}ϵ&gt;0, we have{a mathematical formula}{a mathematical formula}
     </paragraph>
     <paragraph label="Lemma 2">
      Relative entropy Chernoff bound(See[23].) For{a mathematical formula}0&lt;ϵ&lt;1, we have{a mathematical formula}
     </paragraph>
     <paragraph label="Lemma 3">
      Bennettʼs inequalities(See[32].) For independent random variables{a mathematical formula}X,X1,X2,…,Xmwith{a mathematical formula}Xi∈[0,1], and for any{a mathematical formula}δ&gt;0, the followings hold with probability at least{a mathematical formula}1−δ{a mathematical formula}{a mathematical formula}where{a mathematical formula}V(X)denotes the variance{a mathematical formula}∑i=1mE[(Xi−E[Xi])2]/m.
     </paragraph>
     <section label="6.1">
      Proof of Theorem 4
      <paragraph>
       We begin with a lemma as follows:
      </paragraph>
      <paragraph label="Lemma 4">
       For{a mathematical formula}f∈C(H), let{a mathematical formula}g∈CN(H)be drawn i.i.d. according to distribution{a mathematical formula}Q(f). If{a mathematical formula}yˆkf(xˆk)⩾θand{a mathematical formula}yˆkg(xˆk)⩽αwith{a mathematical formula}θ&gt;α, then there is an example{a mathematical formula}(xi,yi)in S such that{a mathematical formula}yif(xi)⩾θand{a mathematical formula}yig(xi)⩽α.
      </paragraph>
      <paragraph label="Proof">
       There exists a bijection between {a mathematical formula}{yjf(xj):j∈[m]} and {a mathematical formula}{yjg(xj):j∈[m]} according to the original position in S. Suppose {a mathematical formula}yˆkf(xˆk) corresponds to {a mathematical formula}yˆlg(xˆl) for some l. If {a mathematical formula}l⩽k then the example {a mathematical formula}(xˆk,yˆk) of {a mathematical formula}yˆkf(xˆk) is desired; otherwise, except for {a mathematical formula}(xˆk,yˆk) of {a mathematical formula}yˆkf(xˆk) in S, there are at least {a mathematical formula}m−k elements larger than or equal to θ in {a mathematical formula}{yjf(xj):j∈[m]∖{k}} but at most {a mathematical formula}m−k−1 elements larger than α in {a mathematical formula}{yjg(xj):j∈[m]∖{l}}. This completes the proof from the bijection. □
      </paragraph>
      <paragraph label="Proof of Theorem 4">
       For finite {a mathematical formula}H, we denote by {a mathematical formula}A={i/|H|:i∈[|H|]}. For every {a mathematical formula}f∈C(H), we can construct a {a mathematical formula}g∈CN(H) by choosing N elements i.i.d. according to distribution {a mathematical formula}Q(f), and thus {a mathematical formula}Eg∼Q(f)[g]=f. For {a mathematical formula}α&gt;0, the Chernoffʼs bound in Lemma 1 gives{a mathematical formula} For any {a mathematical formula}ϵN&gt;0, we consider the following probability:{a mathematical formula} where {a mathematical formula}yˆkg(xˆk) denotes the kth margin with respect to g. For any k, Eq. (18) can be bounded by {a mathematical formula}exp(−mKL(k−1m‖ϵN)) from Lemma 2; for constant k with {a mathematical formula}m&gt;4k, we have{a mathematical formula} By using the union bound and {a mathematical formula}|CN(H)|⩽|H|N, we have, for any {a mathematical formula}k∈[m],{a mathematical formula} Setting {a mathematical formula}δN=|H|N+1exp(−mKL(k−1m‖ϵN)) gives{a mathematical formula} Thus, with probability at least {a mathematical formula}1−δN over sample S, for all {a mathematical formula}f∈C(H) and all {a mathematical formula}α∈A, we have{a mathematical formula} Similarly, for constant k, with probability at least {a mathematical formula}1−δN over sample S, it holds that{a mathematical formula} From {a mathematical formula}Eg∼Q(f)[I[yˆkg(xˆk)⩽α]]=Prg∼Q(f)[yˆkg(xˆk)⩽α], we have, for any {a mathematical formula}θ&gt;α,{a mathematical formula} Notice that the example {a mathematical formula}(xˆk,yˆk) in {a mathematical formula}{yˆif(xˆi)} may be different from example {a mathematical formula}(xˆk,yˆk) in {a mathematical formula}{yˆig(xˆi)}; therefore, we cannot bound the last term on the right-hand side of Eq. (21) as done in [44], whereas it can be bounded by using Lemma 4{a mathematical formula} Combining Eqs. (17), (19), (21) and (22), we have that with probability at least {a mathematical formula}1−δN over the sample S, for all {a mathematical formula}f∈C(H), all {a mathematical formula}θ&gt;α, all {a mathematical formula}k∈[m] but fixed N:{a mathematical formula} To obtain the probability of failure for any N at most δ, we select {a mathematical formula}δN=δ/2N. Setting {a mathematical formula}α=θ2−η|H|∈A and {a mathematical formula}N=⌈8θ2ln2m2ln|H|⌉ with {a mathematical formula}0⩽η&lt;1, we have{a mathematical formula} from the fact {a mathematical formula}2m&gt;exp(N/(2|H|)) for {a mathematical formula}θ&gt;8/|H|. Finally we obtain{a mathematical formula} where {a mathematical formula}q=8ln(2|H|)θ2ln2m2ln|H|+ln|H|+lnmδ. This completes the proof of Eq. (4). In a similar manner, we have{a mathematical formula} for constant {a mathematical formula}k&lt;m/4. This completes the proof of Eq. (5) as desired. □
      </paragraph>
     </section>
     <section label="6.2">
      Proof of Theorem 5
      <paragraph>
       For notational simplicity, we denote by {a mathematical formula}X¯=(X1,X2,…,Xm) a vector of m i.i.d. random variables, and further set{a mathematical formula} i.e., the vector with the kth variable {a mathematical formula}Xk in {a mathematical formula}X¯ replaced by variable Y. We first introduce some lemmas as follows:
      </paragraph>
      <paragraph label="Lemma 5">
       McDiarmid formula(See[31].) Suppose that{a mathematical formula}X¯=(X1,X2,…,Xm)is a vector of m i.i.d. random variables taking values in a set{a mathematical formula}A. If{a mathematical formula}|F(X¯)−F(X¯k,Y)|⩽ckfor{a mathematical formula}k∈[m]and{a mathematical formula}Y∈A, then the following holds for any{a mathematical formula}t&gt;0,{a mathematical formula}
      </paragraph>
      <paragraph label="Lemma 6">
       (See[29, Theorem 13].) Let{a mathematical formula}X¯=(X1,X2,…,Xm)be a vector of m independent random variables tanking values in a set{a mathematical formula}A. If{a mathematical formula}F:Am→Rsatisfies that{a mathematical formula}then for any{a mathematical formula}t&gt;0, we have{a mathematical formula}
      </paragraph>
      <paragraph label="Lemma 7">
       For two i.i.d. random variables X and Y, we have{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       This lemma follows from the obvious fact {a mathematical formula}E[(X−Y)2]=E(X2+Y2−2XY)=2E[X2]−2E2[X]=2E[(X−E[X])2]. □
      </paragraph>
      <paragraph label="Proof of Theorem 5">
       We will utilize Lemma 5, Lemma 6 to prove Eqs. (6) and (7), respectively. For Eq. (6), we first observe that, for any {a mathematical formula}k∈[m],{a mathematical formula} where we use {a mathematical formula}Vˆm(X¯),Vˆm(X¯k,Y)⩽1/2 from {a mathematical formula}Xi∈[0,1]. By using the Jensonʼs inequality, we have {a mathematical formula}E[Vˆm(X¯)]⩽E[Vˆm(X¯)] and thus,{a mathematical formula} where the last inequality holds by applying McDiarmid formula in Lemma 5 to {a mathematical formula}Vˆm. Therefore, we complete the proof of Eq. (6) by setting {a mathematical formula}δ=exp(−4mϵ2).To prove Eq. (7), we set {a mathematical formula}ξm(X¯)=mVˆm(X¯). For {a mathematical formula}Xi∈[0,1] and {a mathematical formula}ξm(X¯k,Y), it is easy to obtain the optimal solution by simple calculation{a mathematical formula} which yields that{a mathematical formula} For {a mathematical formula}Xi∈[0,1], it is obvious that{a mathematical formula} and from Lemma 7, we have{a mathematical formula} which yields that, for {a mathematical formula}m⩾5,{a mathematical formula} Therefore, for any {a mathematical formula}t&gt;0, the following holds by using Lemma 6 to {a mathematical formula}ξm(X¯),{a mathematical formula} Setting {a mathematical formula}δ=exp(−mt2/2E[Vˆm(X¯)]) gives{a mathematical formula} which completes the proof of Eq. (7) by using the square-rootʼs inequality and {a mathematical formula}a+b⩽a+b for {a mathematical formula}a,b⩾0.  □
      </paragraph>
     </section>
     <section label="6.3">
      Proof of Theorem 6
      <paragraph>
       For independent random variables {a mathematical formula}X¯=(X1,X2,…,Xm), we set {a mathematical formula}Vˆm(X¯)=∑i≠j(Xi−Xj)2/2m(m−1), and observe that{a mathematical formula} where we denote by {a mathematical formula}V=∑iE(Xi−E[Xi])2/m and the second equality holds from {a mathematical formula}(a+b+c)2=a2+b2+c2+2ab+2ac+2bc. For any {a mathematical formula}δ&gt;0, the following holds with probability at least {a mathematical formula}1−δ from Eq. (15),{a mathematical formula} which completes the proof of Eq. (8) by combining with Eq. (7) in a union bound and simple calculations. Similar proof could be made for Eq. (9).  □
      </paragraph>
     </section>
     <section label="6.4">
      Proof of Theorem 7
      <paragraph>
       We will use classical double sample method [15], [43] to prove Theorem 7. Let {a mathematical formula}A be a subsets of space {a mathematical formula}Z, and we define{a mathematical formula} We first introduce a useful lemma as follows:
      </paragraph>
      <paragraph label="Lemma 8">
       For space{a mathematical formula}Aof subsets of{a mathematical formula}Z, and for sample{a mathematical formula}S=(z1,z2,…,zm)drawn i.i.d. from distribution{a mathematical formula}Dover{a mathematical formula}Z, we have, for{a mathematical formula}t&gt;ln4{a mathematical formula}where{a mathematical formula}PrD[A]=Prz∼D[z∈A],{a mathematical formula}PrS[A]=Prz∼S[z∈A]and{a mathematical formula}VˆS(A)=∑i≠j(I[zi∈A]−I[zj∈A])2/2m(m−1).
      </paragraph>
      <paragraph label="Proof">
       We begin with another sample {a mathematical formula}Sˆ=(zˆ1,zˆ2,…,zˆm) drawn identically and independently from distribution {a mathematical formula}D, and denote by{a mathematical formula} From Corollary 3, we have {a mathematical formula}PrSˆ∼Dm[PrD[A]⩽ΨSˆ(A)]⩾1/2 for {a mathematical formula}h∈H and {a mathematical formula}t&gt;ln4. This follows for any {a mathematical formula}ϵ&gt;0{a mathematical formula} Now, we introduce the sign random variable vector {a mathematical formula}σ=(σ1,σ2,…,σm) with probability {a mathematical formula}Pr[σi=1]=Pr[σi=−1]=1/2 for {a mathematical formula}i∈[m], and denote by {a mathematical formula}Sσ=(ziσ)i=1m and {a mathematical formula}Sˆσ=(zˆiσ)i=1m{a mathematical formula} Given S and {a mathematical formula}S′, {a mathematical formula}ziσ ({a mathematical formula}i∈[m]) are not identically distributed but independent. Conditioned on S and {a mathematical formula}S′, we have{a mathematical formula} where we denote by {a mathematical formula}A⁎∈argsupA∈APrσ[ΨSˆσ(A)&gt;ΨSσ(A)+ϵ|S,S′] and {a mathematical formula}Prσ[A⁎]=Eσ[PrSσ[A⁎]|S,Sˆ]=Eσ[PrSˆσ[A⁎]|S,Sˆ]. Further, we denote by{a mathematical formula} Thus, we have{a mathematical formula} The first term in the above can be bounded by {a mathematical formula}e−t from Bennettʼs inequality (Lemma 3), and the second term can be bound by {a mathematical formula}e−t by setting {a mathematical formula}ϵ=4t/m and using Theorem 5. Similarly, we can prove{a mathematical formula} by setting {a mathematical formula}ϵ=4t/m. This completes the proof as desired. □
      </paragraph>
      <paragraph label="Proof of Theorem 7">
       Let{a mathematical formula} where {a mathematical formula}A(h)={(X,h(X)∈X×{−1,+1})}. For space {a mathematical formula}H with finite VC-dimension d, Sauerʼs lemma [38] gives{a mathematical formula} Combining with Lemma 8, we have, for {a mathematical formula}t⩾ln4{a mathematical formula} Setting {a mathematical formula}δ=8(2m/d)de−t, we have{a mathematical formula} which completes the proof. □
      </paragraph>
     </section>
     <section label="6.5">
      Proof of Theorem 8
      <paragraph>
       Similarly to the proof of Theorem 4, we have{a mathematical formula} for any given {a mathematical formula}α&gt;0, {a mathematical formula}f∈C(H) and {a mathematical formula}g∈CN(H) drawn i.i.d. according to {a mathematical formula}Q(f). Recall that {a mathematical formula}|CN(H)|⩽|H|N. Therefore, for any {a mathematical formula}δN&gt;0, combining union bound with Eq. (8) in Theorem 3 guarantees that the following holds with probability at least {a mathematical formula}1−δN over sample S, for any {a mathematical formula}g∈CN(H) and {a mathematical formula}α∈A,{a mathematical formula} where{a mathematical formula} Furthermore, we have{a mathematical formula} which yields that{a mathematical formula} for {a mathematical formula}m⩾5. By using Lemma 1 again, the following holds for any {a mathematical formula}θ1&gt;0,{a mathematical formula} Setting {a mathematical formula}θ1=α=θ/2 and combining Eqs. (24), (25), (26) and (27), we have{a mathematical formula} where {a mathematical formula}μ=ln(2|H|N+1/δN). By utilizing the fact {a mathematical formula}a+b⩽a+b for {a mathematical formula}a⩾0 and {a mathematical formula}b⩾0, we further have{a mathematical formula} Finally, we set {a mathematical formula}δN=δ/2N so that the probability of failure for any N will be no more than δ. This theorem follows by setting {a mathematical formula}N=⌈8lnm/θ2⌉.  □
      </paragraph>
     </section>
     <section label="6.6">
      Proof of Corollary 5
      <paragraph>
       If the minimum margin {a mathematical formula}θ1=yˆ1f(xˆ1)&gt;0, then we have {a mathematical formula}PrS[yf(x)&lt;θ1]=0 and further get{a mathematical formula} where {a mathematical formula}μ1=8lnmln(2|H|)/θ12+ln(2|H|/δ). This gives the proof of Eq. (10). If {a mathematical formula}m⩾5, then we have{a mathematical formula} Therefore, the following holds by combining Eq. (28) and the above facts,{a mathematical formula} where the last inequality holds from the conditions of Eq. (13) and {a mathematical formula}8/m&lt;R. This completes the proof of Eq. (14). □
      </paragraph>
     </section>
     <section label="6.7">
      Proof of Theorem 9
      <paragraph>
       Our proof is based on a new Bernstein-type bound as follows:
      </paragraph>
      <paragraph label="Lemma 9">
       For{a mathematical formula}f∈C(H)and{a mathematical formula}g∈CN(H)drawn i.i.d. according to distribution{a mathematical formula}Q(f), we have{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       For {a mathematical formula}λ&gt;0, we utilize the Markovʼs inequality to have{a mathematical formula} where the last inequality holds from the independence of {a mathematical formula}hj. Notice that {a mathematical formula}|yhj(x)−yf(x)|⩽2 from {a mathematical formula}H⊆{h:X→{−1,+1}}. By using Taylorʼs expansion, we further get{a mathematical formula} where the last inequality holds from Jensenʼs inequality and {a mathematical formula}1+x⩽ex. Therefore, it holds that{a mathematical formula} If {a mathematical formula}0&lt;λ&lt;3, then we could use Taylorʼs expansion again to have{a mathematical formula} Now by picking {a mathematical formula}λ=t/(1/2−ES2[yf(x)]/2+t/3), we have{a mathematical formula} which completes the proof as desired. □
      </paragraph>
      <paragraph label="Proof of Theorem 9">
       This proof is rather similar to the proof of Theorem 8, and we just give main steps. For any {a mathematical formula}α&gt;0 and {a mathematical formula}δN&gt;0, the following holds with probability at least {a mathematical formula}1−δN over sample {a mathematical formula}Sm ({a mathematical formula}m⩾5),{a mathematical formula} where {a mathematical formula}Vˆm⁎=PrS[yg(x)&lt;α]PrS[yg(x)⩾α]. For any {a mathematical formula}θ1&gt;0, we use Lemma 1 to obtain{a mathematical formula} From Lemma 9, it holds that{a mathematical formula} Let {a mathematical formula}θ1=θ/6, {a mathematical formula}α=5θ/6, and set {a mathematical formula}δN=δ/2N so that the probability of failure for any N will be no more than δ. We complete the proof by setting {a mathematical formula}N=⌈144lnm/θ2⌉ and simple calculation.  □
      </paragraph>
     </section>
     <section label="6.8">
      Proof of Corollary 6
      <paragraph>
       If the minimum margin {a mathematical formula}θ1=yˆ1f(xˆ1)&gt;0, then we have {a mathematical formula}PrS[yf(x)&lt;θ1]=0 and {a mathematical formula}Iˆ(θ1)=PrS[yf(x)&lt;θ1]PrS[yf(x)⩾2θ1/3]=0. Further, we have{a mathematical formula} where {a mathematical formula}μ1=144lnmln(2|H|)/θ12+ln(2|H|/δ). This completes the proof. □
      </paragraph>
     </section>
     <section label="6.9">
      Proof of Theorems 10 and 11
      <paragraph>
       For finite VC-dimension space {a mathematical formula}H, we denote by {a mathematical formula}A={i/N:i∈[N]}. Similarly to the proof of Theorem 4, we have{a mathematical formula} for {a mathematical formula}α∈A, {a mathematical formula}f∈C(H) and {a mathematical formula}g∈CN(H) chosen i.i.d. according to {a mathematical formula}Q(f). Define{a mathematical formula} and by using Sauerʼs lemma [38], we have{a mathematical formula} for {a mathematical formula}m&gt;d. By setting {a mathematical formula}4s(A,2m)e−t=δN&gt;0 in Lemma 8, the following holds with probability at least {a mathematical formula}1−δN over sample S, for any {a mathematical formula}g∈CN(H) and {a mathematical formula}α∈A,{a mathematical formula} where {a mathematical formula}Vˆm⁎=PrS[yg(x)&lt;α]PrS[yg(x)⩾α].
      </paragraph>
      <paragraph>
       To prove Theorem 10, we proceed as the proof of Theorem 8. Setting {a mathematical formula}α=θ/2, we have{a mathematical formula} where {a mathematical formula}μ=ln(8s(A,2m)/δN). This completes the proof by using {a mathematical formula}a+b⩽a+b and setting {a mathematical formula}δN=δ/2N and {a mathematical formula}N=⌈8lnm/θ2⌉.
      </paragraph>
      <paragraph>
       To prove Theorem 11, we proceed as the proof of Theorem 9. Setting {a mathematical formula}α=5θ/6, we have{a mathematical formula} where {a mathematical formula}μ=ln(8s(A,2m)/δN) and {a mathematical formula}Iˆ(θ)=PrS[yf(x)&lt;θ]PrS[yf(x)⩾2θ/3]. This completes the proof by using {a mathematical formula}a+b⩽a+b and setting {a mathematical formula}δN=δ/2N and {a mathematical formula}N=⌈144lnm/θ2⌉.  □
      </paragraph>
     </section>
    </section>
   </content>
  </root>
 </body>
</html>