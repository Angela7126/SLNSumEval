<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    Online Transfer Learning.
   </title>
   <abstract>
    In this paper, we propose a novel machine learning framework called “Online Transfer Learning” (OTL), which aims to attack an online learning task on a target domain by transferring knowledge from some source domain. We do not assume data in the target domain follows the same distribution as that in the source domain, and the motivation of our work is to enhance a supervised online learning task on a target domain by exploiting the existing knowledge that had been learnt from training data in source domains. OTL is in general very challenging since data in both source and target domains not only can be different in their class distributions, but also can be diverse in their feature representations. As a first attempt to this new research problem, we investigate two different settings of OTL: (i) OTL on homogeneous domains of common feature space, and (ii) OTL across heterogeneous domains of different feature spaces. For each setting, we propose effective OTL algorithms to solve online classification tasks, and show some theoretical bounds of the algorithms. In addition, we also apply the OTL technique to attack the challenging online learning tasks with concept-drifting data streams. Finally, we conduct extensive empirical studies on a comprehensive testbed, in which encouraging results validate the efficacy of our techniques.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      Transfer learning (TL) is an emerging family of machine learning techniques and has been actively studied in machine learning and AI communities in recent years [27]. In a regular transfer learning task, we assume two datasets, one from a source domain and the other from a target domain, are available where their data distributions or representations of the two domains can be very different. TL aims to build models from the target-domain dataset by exploring information from the source-domain dataset through some knowledge transferring process. Transfer learning is important for many applications where training data in a new domain may be limited or too expensive to collect. Despite being explored actively in literature [27], [26], [2], [12], [20], most existing approaches on transfer learning often have been studied in an offline/batch learning fashion, which assumes training data in the new domain is given a priori. Such an assumption may not always hold for some real applications where training examples may arrive in an online/sequential manner.
     </paragraph>
     <paragraph>
      Unlike the existing transfer learning studies, this paper investigates a new framework of Online Transfer Learning (OTL) [33], which addresses the transfer learning problem in an online learning framework. Specifically, OTL makes two assumptions: (i) training data in the new domain arrives sequentially; and (ii) some classifiers/models had been learnt from source domains. Online transfer learning is beneficial to many real applications. Below we give two examples to illustrate some potential applications.
     </paragraph>
     <paragraph>
      The first example application is for online spam detection, such as spam email filtering. Typically, a universal classifier is trained to detect the spam as accurately as possible by a batch learning approach [25]. However, a universal classifier might not be always optimal for every individual as different persons may have different opinions on the definition of spam. This raises an open question, i.e., how to transfer useful knowledge from the universal classifier to personalize the spam detector for every individual in an online learning manner. Such a problem can be naturally attacked by applying the proposed OTL technique, in which the key challenge is that the “spam” concept in the target domain for each individual can be very different from that in the source domain. For such problems, as we assume the feature spaces of both source and target domains are the same, we thus refer to this scenario as OTL on homogeneous domains of common feature space.
     </paragraph>
     <paragraph>
      The second example application is for climate forecast in environment and climate science [24], such as weather forecast, earthquake and tsunami prediction. For example, consider a situation where new types of instruments or sensors are introduced to improve an existing weather forecast system. In this scenario, training data with new features will be added to the forecast system while old features are still retained. Such a problem also can be formulated as an online transfer learning task, which aims to build an improved forecasting system on the new domain with the augmented features by transferring the knowledge of the old classifier in the source domain. This task can be potentially more challenging than the previous example as the feature spaces of both source and target domains are different, making it difficult to train the classifier on the new data by a simple transfer from the old classifier. We thus refer to this scenario as OTL across heterogeneous domains of diverse feature spaces.
     </paragraph>
     <paragraph>
      As a summary, this paper addresses two challenging scenarios: (i) OTL on homogeneous domains, and (ii) OTL across heterogeneous domains. One straightforward approach to OTL is based on a continuous learning strategy, which initializes a regular online learning algorithm on the target domain with the existing classifier learnt from source domains. However, such a simple solution suffers from some critical drawbacks: (i) when studying OTL on homogeneous domains, it could suffer from negative transfer (transferred knowledge is harmful to learning target task) whenever there exists much significant difference between two conditional probabilities; and (ii) when studying OTL across heterogeneous domains, the old classifiers cannot be trained continuously with the new features because of the inconsistence of the two feature spaces.
     </paragraph>
     <paragraph>
      In addition to these two challenges, we note that online transfer learning is in general more challenging than a classical batch transfer learning task. This is because in an OTL task it is very hard to directly measure the distribution difference of the two domains as only a predictive model of the source domain is provided, and the data instances on the target domain arrive on-the-fly sequentially and typically must be predicted immediately. This work aims to investigate effective and efficient OTL techniques to tackle these challenges.
     </paragraph>
     <paragraph>
      In particular, to tackle the first challenge, we propose two ensemble learning based strategies for transferring knowledge from source domain by combining two sets of classifiers built on different domains. The key idea is to dynamically update the combination weights for the base classifiers according to their online performance. We propose two effective algorithms and give theoretical bounds to justify their efficacy. To tackle the second challenge, we propose a co-regularization learning strategy for knowledge transfer, which can effectively handle the learning task on diverse feature spaces. The key idea of the proposed co-regularization strategy was partially inspired by the co-training principle for batch learning tasks (semi-supervised learning or multi-view learning) [5], [29], which combines classifiers co-trained from different “views” of the same training instances to boost the learning efficacy.
     </paragraph>
     <paragraph>
      Last but not least, we extend the idea of the proposed OTL technique to attack a real-world open challenge in data mining and machine learning, i.e., the concept-drifting data stream mining task [21] where the underlying distributions and concepts often change over time. Despite being studied extensively in literature, it remains a critical open challenge for the existing approaches based on either batch learning or online learning techniques. In this paper, we propose an effective algorithm to attack this challenge based on a natural extension of the proposed OTL technique.
     </paragraph>
     <paragraph>
      The rest of this paper is organized as follows. Section 2 reviews related work. Section 3 presents the proposed OTL framework and addresses the homogeneous and heterogeneous OTL tasks for classification. Section 4 presents the extension of OTL to address concept-drift online learning tasks. Section 5 gives our experimental results and discussions, and Section 6 concludes this work. Finally, we note that a short version of this work has appeared in the conference proceedings of ICML-2010 [33]. In contrast to the conference paper, a substantial amount of new contents and extensions have been included in this journal article.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Our work is mainly related to two machine learning topics: online learning and transfer learning. Below reviews some important related work.
     </paragraph>
     <paragraph>
      Online learning (OL) has been extensively studied for years [28], [7], [9], [32], [34], [35], [36], [30], [19]. Unlike typical machine learning methods that assume training examples are available before the learning task, online learning is more appropriate for some real-world problems where training data arrives sequentially. Due to the merits of attractive efficiency and scalability, various online learning methods have been proposed. One well-known approach is the Perceptron algorithm [28], [14], which performs a simple update on the classification model when an incoming example is misclassified. Recently many online learning algorithms have been proposed based on the criterion of maximum margin [23], [9]. One example is the Passive–Aggressive (PA) method [9], which updates the model when a new example is misclassified or its classification confidence is smaller than some predefined threshold. Although the general online learning algorithms (e.g., Perceptron and PA) have solid theoretical guarantees and performs well on many applications, they usually keep the weights of the existing support vectors fixed during the whole learning process, which is clearly insufficient. To solve this issue, double updating online learning (DUOL) [34] is proposed to not only update the weight of the current support vector but also the weight of one existing support vector, which conflicts the most with the current one. Besides, traditional online learning tries to maximize the accuracy of the model while accuracy is unsuitable to many applications and scenarios. To tackle this problem, online AUC maximization (OAM) [35] is proposed to online maximize the AUC performance of the model. In addition, typical online learning usually stores all the misclassified examples as Support Vectors (SVs), which may result in high computational and memory costs. To deal with this problem, the researchers [36] have proposed a bounded online gradient descent algorithm (BOGD) to keep the number of stored SVs less than a pre-defined threshold. Moreover, most of online learning algorithms only exploit the first order information and assign all features the same learning rate, which may suffer from slow convergence rates. This can be solved by second order online learning [30], which not only use the first order but also the second order information of the examples. More extensive surveys for online learning can be found in [8], [19].
     </paragraph>
     <paragraph>
      Transfer learning (TL) has been actively studied recently [27]. The goal of TL is to extract knowledge from one or more source domains and then apply them to solve a learning task on a target domain. A variety of TL methods have been proposed in different learning settings. These methods can be roughly classified into three categories: inductive, transductive, and unsupervised learning approaches. Inductive TL [26] aims to induce the model in the target domain with the aid of knowledge transferred from the source domains; transductive TL [2], [12] aims to extract the knowledge from the source domains to improve the prediction tasks in the target domain without labeled data in the target domain; while unsupervised TL aims to resolve unsupervised learning tasks in the target domain [31], [11]. Moreover, according to different feature representation, TL can be classified as homogeneous TL or heterogeneous TL [1] where the feature spaces of source and target domains can be different. A comprehensive survey on batch transfer learning can be found in [27].
     </paragraph>
     <paragraph>
      Although both online learning and transfer learning have been actively studied in literature, to the best of our knowledge, we are the first to formulate transfer learning in an online learning framework [33]. In addition, it is also important to note that OTL is different from online multi-task learning[13], which aims to learn multiple tasks in parallel in an online learning setting. Finally, our work is also related to some existing studies on concept-drifting learning and mining in machine learning and data mining literature [17], [22], [6]. In data mining, most existing work usually adapt some batch learning algorithms to attack concept-drift learning/mining tasks using various instance selection/weighting strategies and heuristics. As our work is focused on online learning methodology, we exclude the detailed discussions on a large body of related work on batch learning studies in data mining. We refer readers to some comprehensive surveys in data mining [37], [15]. Below we review some representative work on online learning methods to handle concept drift in machine learning.
     </paragraph>
     <paragraph>
      In machine learning literature, various online learning methods have been proposed to handle concept drift learning [17], [3], [18], [16]. The well-known techniques include several variants of Perceptron-style algorithms [4], [6], [10]. For example, the Shifting Perceptron [6] attempts to tackle the concept drift challenge by diminishing the important of early updates by introducing some time-changing decaying factor. Most of the existing techniques usually assume some fixed or slowly changing input distribution, and typically cannot effectively handle sudden concept drift in a challenging real-world scenario. Unlike the existing approaches, we extend the idea of online transfer learning to tackle the problem of online learning with concept drift which can tackle sudden concept drift more effectively than the state-of-the-art approaches.
     </paragraph>
    </section>
    <section label="3">
     <section-title>
      Online Transfer Learning
     </section-title>
     <paragraph>
      In this section, we first present a framework of Online Transfer Learning (OTL) for classification, and then propose algorithms to solve the OTL tasks under two different settings. We note that although the following discussion is focused on classification tasks, the similar techniques and principles could be generalized to other data mining and machine learning tasks, such as regression or ranking.
     </paragraph>
     <section label="3.1">
      <section-title>
       Problem formulation
      </section-title>
      <paragraph>
       Let us denote by {a mathematical formula}Xs×Ys the source/old data space, where {a mathematical formula}Xs=Rm and {a mathematical formula}Ys={−1,+1}. Assume that a source classifier is a linear vector {a mathematical formula}v∈Rm. Typically the source classifier v can be obtained by applying existing learning techniques, such as online learning by the Perceptron algorithm [28], [14] or regular batch learning by support vector machines (SVM).
      </paragraph>
      <paragraph>
       The goal of an online transfer learning (OTL) task is to learn some prediction function {a mathematical formula}f(xt) on a target domain in an online fashion from a sequence of examples {a mathematical formula}{(xt,yt)|t=1,…,T} in some data space {a mathematical formula}X×Y. Without loss of generality, we assume a linear prediction model is used for the prediction function, i.e., {a mathematical formula}f(xt)=sign(wt⊤xt).
      </paragraph>
      <paragraph>
       Specifically, during the OTL task, at the t-th trial of online learning task, the learner receives an instance {a mathematical formula}xt, and the goal of online learning is to find a good prediction function such that the predicted class label {a mathematical formula}sign(wt⊤xt) can match its true class label {a mathematical formula}yt. The key challenge of OTL is how to effectively transfer the knowledge from the old/source domain to the new/target domain for improving the online learning performance. Next, we study OTL in two different settings: homogeneous OTL vs. heterogeneous OTL.
      </paragraph>
     </section>
     <section label="3.2">
      <section-title>
       Online Transfer Learning on homogeneous domains
      </section-title>
      <paragraph>
       We start by studying the homogeneous OTL, in which we assume the source and target domains share the same feature space, i.e., {a mathematical formula}X=Xs and {a mathematical formula}Y=Ys. One key challenge of this task is to address the covariate shift problem. This raises the challenge of transferring knowledge from source domain to target domain.
      </paragraph>
      <paragraph>
       The basic idea of our OTL solution is based on the ensemble learning strategy. In particular, we first construct an entirely new prediction function w only from the data in the target domain in an online fashion, and then learn an ensemble prediction function that is the mixture of both the old and the new prediction functions, i.e., v and w, which thus can transfer the knowledge from the source domain. The remaining issue is then how to effectively combine the two prediction functions for handling the covariate shift issue.
      </paragraph>
      <paragraph>
       In order to effectively combine the two prediction functions v and {a mathematical formula}wt at the t-trial of the online learning task, we introduce two combination weighting parameters, {a mathematical formula}α1,t and {a mathematical formula}α2,t, for the two prediction functions respectively. At the t-th step, given an instance {a mathematical formula}xt, we predict its class label by the following prediction function:{a mathematical formula} where {a mathematical formula}Π(z)∀z∈R is a projection function, i.e., {a mathematical formula}Π(z)=max⁡(0,min⁡(1,z+12)). At the beginning of the OTL task, we simply initialize {a mathematical formula}α1,1=α2,1=12. In order to perform effective transfer for the subsequent trials of the OTL task, in addition to updating the function {a mathematical formula}wt+1 by some online learning method, e.g. the PA algorithm [9], we expect the two weights of both prediction functions, i.e., {a mathematical formula}α1,t and {a mathematical formula}α2,t, should be adjusted dynamically. We thus suggest the following scheme for updating the weights:{a mathematical formula} where {a mathematical formula}st(u)=exp⁡{−ηℓ⁎(Π(u⊤xt),Π(yt))}, {a mathematical formula}∀u∈Rm and {a mathematical formula}ℓ⁎(z,y) is a loss function which is set to {a mathematical formula}ℓ⁎(z,y)=(z−y)2 in our approach. Finally, Algorithm 1 summarizes the proposed HomOTL-I algorithm. Before we analyze the mistake bound of the proposed algorithm, we first introduce a proposition as follows.
      </paragraph>
      <paragraph label="Proposition 1">
       When using the square loss{a mathematical formula}ℓ⁎(z,y)=(z−y)2for{a mathematical formula}z∈[0,1]and{a mathematical formula}y∈[0,1], the above exponentially weighting update method and setting{a mathematical formula}η=1/2, we have the bound of the ensemble algorithm as:{a mathematical formula}
      </paragraph>
      <paragraph>
       The proof of the above proposition is in Appendix A. By Proposition 1, we can derive the mistake bound of the HomOTL-I algorithm as follows.
      </paragraph>
      <paragraph label="Theorem 1">
       Let us denote by M the number of mistakes made by the HomOTL-I algorithm, we then have M bounded from above by:{a mathematical formula}where{a mathematical formula}Σv=∑t=1Tℓ⁎(Π(v⊤xt),Π(yt))and{a mathematical formula}Σw=∑t=1Tℓ⁎(Π(wt⊤xt),Π(yt)).
      </paragraph>
      <paragraph label="Proof">
       First notice that whenever there is a mistake at some t-th step, we should have {a mathematical formula}|α1,tΠ(v⊤xt)+α2,tΠ(wt⊤xt)−Π(yt)|≥12. Thus, we haves{a mathematical formula} Combining the above fact with Proposition 1, we have{a mathematical formula} where {a mathematical formula}Σv=∑t=1Tℓ⁎(Π(v⊤xt),Π(yt)) and {a mathematical formula}Σw=∑t=1Tℓ⁎(Π(wt⊤xt),Π(yt)). The theorem follows directly by multiplying 4 at both sides of the above.  □
      </paragraph>
      <paragraph label="Remark">
       To better understand the mistake bound, we denote by {a mathematical formula}Mv and {a mathematical formula}Mw the mistake bounds of model v and {a mathematical formula}wt, respectively. We first note that {a mathematical formula}ℓ⁎(Π(v⊤xt),Π(yt)) is the upper bound of {a mathematical formula}14Mv instead of {a mathematical formula}Mv (because {a mathematical formula}ℓ⁎ is a square loss and both {a mathematical formula}Π(v⊤xt) and {a mathematical formula}Π(yt) are normalized to {a mathematical formula}[0,1]); similarly, {a mathematical formula}ℓ⁎(Π(wt⊤xt),Π(yt)) is the upper bound of {a mathematical formula}14Mw. Further, if we assume {a mathematical formula}ℓ⁎(Π(v⊤xt),Π(yt))≈14Mv and {a mathematical formula}ℓ⁎(Π(wt⊤xt),Π(yt))≈14Mw, we have {a mathematical formula}M≤min⁡{Mv,Mw}+8ln⁡2. This gives a strong theoretical support for the HomOTL-I algorithm. However, please note that: while HomOTL-I will only make a constant number of mistakes more than the best base learner, the best base learner may still suffer some regret. Despite the nice result in theory, we note this bound may be further improved so that it can tell us exactly how much we can leverage the classifier from the source domain to improve over the target domain. However, this can be a very hard open challenge since an online transfer learning task is in general more challenging than a classical batch transfer learning task because in an OTL task only a linear classifier is stored for a source domain and the new instances for the target domain are received online sequentially, it is hard/almost impossible to directly compare the distributions of the source domain and the target domain.
      </paragraph>
      <paragraph>
       In addition to the above loss-based updating algorithm, we also provided the following mistake-driven Algorithm 2.
      </paragraph>
      <paragraph>
       In this framework, we use {a mathematical formula}θi,t to denote the combination weight for the two classifiers at round t, which is set to 1 at the initial round. For each learning round, we update the weight {a mathematical formula}θi,t by following the Hedge algorithm as follows:{a mathematical formula} where {a mathematical formula}β∈(0,1) is a discount weight parameter, which is employed to penalize the classifier that performs incorrect prediction at each learning step, and {a mathematical formula}zi,t indicates if the corresponding classifier makes a mistake on the prediction of the example {a mathematical formula}xt.
      </paragraph>
      <paragraph>
       Next we derive a theorem to show the mistake bound for Algorithm 2.
      </paragraph>
      <paragraph label="Theorem 2">
       After receiving a sequence of T training examples, denoted by{a mathematical formula}L={(xt,yt),t=1,…,T}, the number of mistakes M made by runningAlgorithm 2, denoted by{a mathematical formula}is bounded as follows{a mathematical formula}where{a mathematical formula}Mi=∑t=1Tzi,tfor{a mathematical formula}i=1,2. By choosing{a mathematical formula}β=TT+ln⁡2, we have{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       We bound {a mathematical formula}ln⁡(Θt+1/Θt) from both the above and the below. Firstly, to upper bound {a mathematical formula}ln⁡(Θt+1/Θt), we have{a mathematical formula} By adding the inequalities of all trials, we have{a mathematical formula} On the other hand, we have {a mathematical formula}ln⁡(ΘT+1/Θ1) lower bounded as follows{a mathematical formula} Since{a mathematical formula} we have the result in the theorem. Finally, to suggest the value for parameter β, by assuming {a mathematical formula}∑t=1Tzi,t≤T and {a mathematical formula}ln⁡(1/β)1−β≤1/β, we can derive the solution for parameter β as follows: {a mathematical formula}β=TT+ln⁡2, which leads to the final result as stated in the theorem.  □
      </paragraph>
     </section>
     <section label="3.3">
      <section-title>
       Online Transfer Learning across heterogeneous domains
      </section-title>
      <paragraph>
       In this section, we study the OTL problem across heterogeneous domains where the source and target domains have different feature spaces.
      </paragraph>
      <paragraph>
       Heterogeneous OTL is generally more challenging than homogeneous OTL. It is very hard, if not completely impossible, to perform knowledge transfer if the feature spaces of source and target domains are not overlapped at all. To simplify the difficulty a bit, we assume the feature space of the source domain is a subset of that of the target domain. As two feature spaces are not the same, we cannot directly apply the algorithm in the previous section. Below we propose a multi-view approach to solve the challenge.
      </paragraph>
      <paragraph>
       Formally, we denote the data on the target domain as: {a mathematical formula}{(xt,yt)|t=1,…,T}, where {a mathematical formula}xt∈X=Rn⊃Rm and {a mathematical formula}yt∈{−1,+1}. Without loss of generality, we assume the first m dimensions of {a mathematical formula}X represent the old feature space {a mathematical formula}Xs. In the multi-view setting, we split each data instance {a mathematical formula}xt into two instances {a mathematical formula}x1,t∈Xs and {a mathematical formula}x2,t∈X/Xs.
      </paragraph>
      <paragraph>
       The key idea of our heterogeneous OTL method is to adopt a co-regularization principle of online learning two classifiers {a mathematical formula}w1,t and {a mathematical formula}w2,t simultaneously from the two views, and predict an unseen example on the target domain by {a mathematical formula}yˆt=sign(12(w1,t⊤x1,t+w2,t⊤x2,t)).
      </paragraph>
      <paragraph>
       For the specific algorithm, we initialize the classifier for the first view by setting {a mathematical formula}w1,1=v, and setting {a mathematical formula}w2,1=0 for the second view. For a new example in the online learning task, we update the new functions {a mathematical formula}w1,t+1 and {a mathematical formula}w2,t+1 by the following co-regularization optimization:{a mathematical formula} where {a mathematical formula}γ1, {a mathematical formula}γ2 and C are positive parameters, and the loss is defined as:{a mathematical formula}
      </paragraph>
      <paragraph>
       Intuitively, the above updating method aims to make the updated ensemble classifier be able to classify the new observed example {a mathematical formula}(xt,yt) correctly, and to force the two-view classifiers without deviating too much from the previous classifiers {a mathematical formula}(w1,t,w2,t) via the first two regularization terms.
      </paragraph>
      <paragraph>
       The above optimization enjoys a closed-form solution as shown in Proposition 2. To simplify our discussion, we introduce notations {a mathematical formula}z1,t=‖x1,t‖2 and {a mathematical formula}z2,t=‖x2,t‖2.
      </paragraph>
      <paragraph label="Proposition 2">
       For the optimization problem(6), its solution can be expressed as follows:{a mathematical formula}where{a mathematical formula}τt=min⁡{C,4γ1γ2ℓtz1,tγ2+z2,tγ1}and{a mathematical formula}ℓt=ℓ(w1,t,w2,t;t).
      </paragraph>
      <paragraph>
       The proof of the proposition is given in Appendix A. By this proposition, we summarize the proposed “Heterogeneous Online Transfer Learning” (HetOTL) algorithm in Algorithm 3.
      </paragraph>
      <paragraph>
       Before we prove the mistake bound for the HetOTL algorithm, we first introduce a lemma.
      </paragraph>
      <paragraph label="Lemma 1">
       Let{a mathematical formula}(xt,yt),t=1,…,Tbe a sequence of examples, where{a mathematical formula}xt∈Rnand{a mathematical formula}yt∈{−1,+1}for all t. After we split the instance{a mathematical formula}xtinto two views{a mathematical formula}(x1,t,x2,t), for any{a mathematical formula}w1∈Rmand{a mathematical formula}w2∈Rn−m, we have the following bound:{a mathematical formula}where{a mathematical formula}ℓ(w1,w2;t)is given in Eqn.(7)and{a mathematical formula}ℓt=ℓ(w1,t,w2,t;t).
      </paragraph>
      <paragraph>
       The proof of the lemma is given in Appendix A. Using Lemma 1, we can show the following theorem for the mistake bound of the proposed HetOTL algorithm.
      </paragraph>
      <paragraph label="Theorem 3">
       Let{a mathematical formula}(xt,yt),t=1,…,Tbe a sequence of examples, where{a mathematical formula}xt∈Rnand{a mathematical formula}yt∈{−1,+1}for all t. If we split the instance{a mathematical formula}xtinto two views{a mathematical formula}(x1,t,x2,t), so that{a mathematical formula}z1,t≤R1and{a mathematical formula}z2,t≤R2{a mathematical formula}t=1,…,T. Then for any{a mathematical formula}w1∈Rmand{a mathematical formula}w2∈Rn−m, the number of mistakes M made by the proposed HetOTL algorithm is bounded from above as:{a mathematical formula}where{a mathematical formula}τ=min⁡{C,4γ1γ2R1γ2+R2γ1}.
      </paragraph>
      <paragraph label="Proof">
       Firstly, {a mathematical formula}τt=min⁡{C,4γ1γ2ℓtz1,tγ2+z2,tγ1}≤C implies {a mathematical formula}τtℓ(w1,w2;t)≤Cℓ(w1,w2;t). Combining with {a mathematical formula}τt=min⁡{C,4γ1γ2ℓtz1,tγ2+z2,tγ1}≤4γ1γ2ℓtz1,tγ2+z2,tγ1, we thus have{a mathematical formula} Combining the above inequality with the conclusion of Lemma 1, we have{a mathematical formula} Furthermore, when a mistake occurs, {a mathematical formula}ℓt≥1; thus, we have{a mathematical formula} Combining the above observation with the inequality in Eq. (12), we have{a mathematical formula} The theorem follows directly by multiplying {a mathematical formula}2/τ on both sides of the above inequality.  □
      </paragraph>
      <paragraph label="Corollary 4">
       Under the assumption inTheorem 3, if we further assume{a mathematical formula}R1=R2=1and{a mathematical formula}γ1=γ2, we have the following bound for the HetOTL algorithm{a mathematical formula}
      </paragraph>
      <paragraph label="Proof">
       It is easy to verify that to minimize the left hand side of the inequality (10) is equivalent to (set {a mathematical formula}R1=R2=1){a mathematical formula} which further is equivalent to{a mathematical formula} Plugging {a mathematical formula}γ1=γ2 into the above inequality will result in the conclusion.  □
      </paragraph>
     </section>
    </section>
    <section label="4">
     <section-title>
      Application of OTL for mining concept-drifting data streams
     </section-title>
     <paragraph>
      In this section, we apply the online transfer learning technique to attack the online learning task on concept-drifting data streams.
     </paragraph>
     <section label="4.1">
      <section-title>
       Concept-Drifting Online Learning algorithm
      </section-title>
      <paragraph>
       Consider a binary classification task in concept drift setting where a learner is presented with a sequence of data with time stamps. At time step t, the algorithm is provided with instance {a mathematical formula}xt∈Rd, and will predict its label as {a mathematical formula}yˆt=sign(wt⊤xt)∈{−1,+1}, where {a mathematical formula}wt is the current prediction function. After prediction, the environment will disclose the real label {a mathematical formula}yt, so that the learner will suffer a loss {a mathematical formula}ℓ((xt,yt);wt), which is the difference between its prediction and the true label. Specifically, we will still adopt hinge loss {a mathematical formula}ℓ((xt,yt);wt)=max⁡(0,1−ytwt⊤xt). After suffering from the loss, the leaner will update the prediction function using the current example with respect to some criterion. The overall objective of this learning process is to minimize the total mistake (or cumulative loss) over the entire sequence of examples. However, in the concept drifting setting, when the distribution changes frequently too much over time, traditional online algorithms will not work well.
      </paragraph>
      <paragraph>
       Our main idea is that during the online learning process, we will divide the whole learning process into several periods. In each period, we will transfer the well learnt knowledge from the old classifier to a new one using the previous studied OTL technique. Specifically, the old classifier is the best one selected from the two classifiers in last period, and the new classifier is initialized as zero vector. As a result, if concept drift occurs, the newly learnt classifier may be adapted better than the older one; if no concept drift occurs, the old classifier will still perform well.
      </paragraph>
      <paragraph>
       To formulate the above idea, we define a window size parameter {a mathematical formula}Pi as the number of instances received in the i-th period. We maintain two classifiers: a source classifier {a mathematical formula}vt and a target classifier {a mathematical formula}wt, which are weighted by {a mathematical formula}α1,t and {a mathematical formula}α2,t, respectively. As a result, at the tth step, given an instance {a mathematical formula}xt, we predict its class label by the following ensemble function:{a mathematical formula}
      </paragraph>
      <paragraph>
       The key problem is how to effectively tune the weights. It is obvious that at the first period, source classifier is constantly zero function, so the source function is weighted with 0; while target function is weighted with 1 throughout it. To dynamically adjust the weights for the remaining steps, we use the following performance-driven exponential weighted updating scheme: when {a mathematical formula}mod(t,Pi)≠0{a mathematical formula} where {a mathematical formula}st(u)=exp⁡{−ηℓ⁎(Π(u⊤xt),Π(yt))}, {a mathematical formula}∀u∈Rm and {a mathematical formula}ℓ⁎(z,y)=(z−y)2 in our approach. Finally, Algorithm 4 summarizes the proposed Concept Drift Online Learning (CDOL) algorithm.
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       Theoretical analysis
      </section-title>
      <paragraph>
       Next we analyze the mistake bound of the algorithm. By Proposition 1, we derive the mistake bound of the CDOL algorithm as follows.
      </paragraph>
      <paragraph label="Theorem 5">
       Assume the proposed CDOL algorithm is provided with a sequence of examples{a mathematical formula}{(xt,yt)|t=1,2,…,T}, where{a mathematical formula}‖xt‖≤R,{a mathematical formula}yt∈{−1,+1}and{a mathematical formula}T=∑i=1aPi(a is a positive integer). Let us denote by M the number of mistakes made by the CDOL algorithm, for any vectoru, we then have M bounded from above by:{a mathematical formula}where{a mathematical formula}Σv,iand{a mathematical formula}Σw,iare the cumulative{a mathematical formula}ℓ⁎loss suffered by the source classifier and the target classifier, respectively during the i-th period.
      </paragraph>
      <paragraph label="Proof">
       Let us denote by {a mathematical formula}Mi the number of mistakes made in period i, and M the total number of mistakes, which satisfies {a mathematical formula}M=∑i=1aMi. For the first period, the algorithm runs the same with the PA-I algorithm. Thus, the mistake bound for this period is the same as that of PA-I, i.e.,{a mathematical formula} After the first period, notice that whenever there is a mistake at some t-th step, we should have {a mathematical formula}(α1,tΠ(vt⊤xt)+α2,tΠ(wt⊤xt)−Π(yt))2≥14. Thus, for {a mathematical formula}i=2,…,a, we have{a mathematical formula} Combining the above facts with Proposition 1, we have{a mathematical formula} The final mistake bound can be proved by combining Eq. (16) and Eq. (17).  □
      </paragraph>
      <paragraph>
       To better understand the above theorem, we will show a corollary. To do so, we will need the following proposition.
      </paragraph>
      <paragraph label="Proposition 3">
       Denote{a mathematical formula}ℓt⁎=(Π(wt⊤xt)−Π(yt))2and{a mathematical formula}ℓt=max⁡{0,1−ytwt⊤xt}, then the two losses satisfy the following inequality:{a mathematical formula}
      </paragraph>
      <paragraph>
       The proof to the above proposition can be found in Appendix A. Combining this proposition with Theorem 5, we have the following corollary:
      </paragraph>
      <paragraph label="Corollary 6">
       Under the same assumption inTheorem 5, if further assume{a mathematical formula}R≤1and{a mathematical formula}C≥2, we have the following bound for the proposed CDOL algorithm inAlgorithm 4{a mathematical formula}where M is the number of mistakes, and{a mathematical formula}ui,i=1,2,…,aare any a vectors which may or may not be the same.
      </paragraph>
      <paragraph label="Proof">
       According to Lemma 1 in [9], we have the following inequalities:{a mathematical formula} where {a mathematical formula}ui,i=2,3,…,a are any vectors which may or may not be the same. Because {a mathematical formula}τt‖xt‖2=min⁡{C,ℓt/‖xt‖2}‖xt‖2≤ℓt and {a mathematical formula}τt≤C, the inequality (19) implies{a mathematical formula}Furthermore, because {a mathematical formula}‖xt‖≤1 and {a mathematical formula}C≥2, we have {a mathematical formula}{2ℓt,ℓt2}≤min⁡{Cℓt,ℓt2‖xt‖2}{a mathematical formula} where {a mathematical formula}i∈{2,3,…,a}. Combining the above inequalities (20) and (21), we have{a mathematical formula} Finally, combining the above inequality with Theorem 5 results in{a mathematical formula}  □
      </paragraph>
      <paragraph>
       Although the above theorem offers a nice theoretical guarantee of Algorithm 4, its empirical performance could be affected by the selection of the window size parameters {a mathematical formula}Pi at different periods. One simple way is to fix all {a mathematical formula}Pi values to a proper constant P, which ideally should match the concept drift cycle. Such an approach is practically infeasible because (i) finding a proper parameter P is hard since the optimal window size for concept drift can only be known in hindsight; and (ii) concept drift often occurs irregularly, which would make a single windows size parameter fail in practice. To overcome the challenge of parameter selection for {a mathematical formula}Pi, in this paper, we propose an automated parameter selection technique, an Online Window Adjustment (OWA) algorithm as shown in Algorithm 5, which can automatically determine a proper value for window size parameter {a mathematical formula}Pi during the online learning process. We note that this algorithm was inspired by the existing Window Adjustment algorithm [22] used for solving batch concept drift tasks.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Experimental results
     </section-title>
     <paragraph>
      In this section, we evaluate the empirical performance of the proposed OTL technique for three sets of experiments: (i) homogeneous OTL for classification tasks, (ii) heterogeneous OTL for classification tasks, and (III) application of OTL for concept-drifting online learning tasks. The whole experimental testbed including all the datasets and source code are available at http://www.stevenhoi.org/OTL/.
     </paragraph>
     <section label="5.1">
      <section-title>
       Experiment I: homogeneous OTL for classification tasks
      </section-title>
      <section label="5.1.1">
       <section-title>
        Experimental testbed and setup
       </section-title>
       <paragraph>
        Our first experiment is to evaluate the performance of HomOTL from homogeneous data. We compare our HomOTL technique against other popular online learning techniques, including the Passive–Aggressive algorithms (“PA”) [9] without exploiting any knowledge from the source domain, and a variant of it, which is the PA method Initialized with the Old classifier v, denoted as PAIO for short. For our HomOTL technique, in addition to Algorithm 1, Algorithm 2, we also implement another variant, which is implemented by fixing the ensemble weights of the HomOTL-I algorithm to 1/2, denoted “HomOTL(fixed)” for short. This helps examine the efficacy of the proposed weighting strategy. We evaluate the proposed algorithms on six benchmark datasets for transfer learning as listed in Table 1.
       </paragraph>
       <paragraph>
        These datasets were created based on the “sentiment” and “landmine” datasets downloaded from the website,{sup:1} which are popularly used to benchmark transfer learning algorithms. The first four datasets are named in the form of “name1–name2”, which means data “name1”, one domain from “sentiment”, is used as training data in the source domain, and data “name2”, another domain from “sentiment”, is treated as test data for online learning in the target domain. The last two datasets were created from “landmine”, which consists of 19 tasks, where 1–10 were collected at foliated regions and 11–19 were collected at regions that are bare earth or desert. Thus, “landmine1” uses 1–10 as the source data and the rest as target data; while “landmine2” uses “11–19” as source data and the rest as target data.
       </paragraph>
       <paragraph>
        Finally, we adopt the PA algorithm to run on the source dataset and adopt the average classifier as the source classifier, which generally enjoys better generalization ability [7]. Further, we draw 20 times of random permutation of the instances in the target domain in order to obtain stable results by averaging over the 20 trials. All the algorithms adopt the kernel-based implementation with the same Gaussian kernel function. For fair comparison and simplicity, we set the kernel parameter {a mathematical formula}σ1=4 for the source domain and {a mathematical formula}σ2=8 for the target domain for all the datasets and algorithms. In addition, we set the regularization parameter {a mathematical formula}C=5 for all algorithms, and parameter {a mathematical formula}β=T/(T+ln⁡2) for HomOTL-II. We will also conduct experiments to examine the parameter sensitivity in subsequent sections. For performance evaluation, we evaluate the predictive accuracy of online learning methods by measuring the standard mistake rate, the sparsity of the resulting classifiers by evaluating the number of support vectors, and time efficiency by calculating average time costs.
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Performance evaluation results
       </section-title>
       <paragraph>
        Table 2 summarizes the performance of the compared algorithms. Several observations can be drawn from the experimental results. First of all, for most of the datasets, we found that the PA algorithm performs the worst, which implies the necessity of studying online transfer learning. Secondly, PAIO achieves better performance than PA on the first four datasets, while has no much improvement on the final two datasets, which demonstrates the importance of developing more sophisticated algorithms. In addition, the proposed HomOTL-I and HomOTL-II algorithms achieve the best performance among all datasets, which implies that the exploiting learnt knowledge from source domain is able to boost the performance of traditional online learning algorithms, and the two kinds of weight updating methods are generally comparable. Furthermore, we found that HomOTL-I outperforms HomOTL(fixed) on all the datasets, which shows that the proposed weight updating strategy can effectively transfer the knowledge. Finally, for the time efficiency evaluation, the proposed two OTL strategies are generally comparable to PAIO, and PA is the most efficient because it does not exploit data in the target domain.
       </paragraph>
       <paragraph>
        Fig. 1 also shows the details of average mistake rates varying over the learning processes on the six data sets, respectively. Similar observations show that the two OTL algorithms achieve the best performance after receiving a small number of examples (e.g., less than 100 examples), which implies these two strategies can efficiently transfer the well-learnt knowledge from the source task to the target task. This again verifies the high learning efficacy of the proposed methodology.
       </paragraph>
      </section>
      <section label="5.1.3">
       Sensitivity evaluation of parameter C for homogeneous OTL
       <paragraph>
        Fig. 2 evaluates the online prediction performance of the compared algorithms with varied C values across all the homogeneous learning tasks. Several observations can be drawn from the results. First of all, it is clear that the proposed two online transfer learning algorithms are significantly more effective than the other algorithms for most cases. Second, among all the compared algorithms, we observe that the proposed HomOTL-I and HomOTL-II algorithms always achieve the best performance when C is sufficiently large (e.g. {a mathematical formula}C&gt;4), which indicates a large learning rate can efficiently improve the transfer learning efficiency. Third, we observe that HomOTL-I and HomOTL-II are significantly more accurate than the other two transfer learning strategies: HomOTL(fixed) and PAIO under varied C values, which indicates the proposed algorithms are more effective for online transfer learning. Fourth, while the insensitivity of HomOTL methods to the value of C on landmine datasets indicates that the dynamic weighting strategies are very effective for these datasets, HomOTL methods improve performance on these datasets only if a suboptimal value of C is chosen. Finally, the PA algorithm performs the worst on all the datasets for varied C values as it does not exploit the knowledge from the source domain.
       </paragraph>
      </section>
      <section label="5.1.4">
       Sensitivity evaluation of parameter β for the HomOTL-II algorithm
       <paragraph>
        In the previous experiments, we fix the value of parameter β to {a mathematical formula}T/(T+ln⁡2) for the proposed HomOTL-II algorithm. One concern is whether if this algorithm is sensitive to the value of parameter β. Table 3 evaluates the online prediction mistake rates of the HomOTL-II algorithm with varied values of β on six different homogeneous OTL tasks. From the results, we observe that the performance of the HomOTL-II algorithm is in general insensitive to the parameter β where HomOTL-II always outperforms PAIO consistently for all settings, validating the advantage of the proposed algorithm.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Experiment II: heterogeneous OTL for classification tasks
      </section-title>
      <section label="5.2.1">
       <section-title>
        Experimental testbed and setup
       </section-title>
       <paragraph>
        We now evaluate the empirical performance of the proposed HetOTL algorithm for heterogeneous OTL on classification tasks. We compare HetOTL with the PA algorithm, which does not exploit knowledge from the source domain. Similarly, we implement a variant of PA algorithm that uses only the first view of the data and is initialized with v from the source domain, denoted as “PAIO”. We also implement a variant of HetOTL, whose first-view classifier is initialized with a zero function, denoted as “HetOTL0”. This method enables us to examine the importance of engaging the v function learnt from the source domain. Finally, we implement another baseline algorithm that simply use HomOTL, where the source classifier only consider the first view, denoted as “Ensemble” for short. We evaluate all the algorithms extensively on several benchmark datasets, as shown in Table 4.
       </paragraph>
       <paragraph>
        These datasets are the same as those used in previous homogeneous classification tasks. However, to meet the assumption and setup of heterogeneous OTL tasks, the source-domain data associate with only half of the feature space while the target-domain data include the whole feature space.
       </paragraph>
       <paragraph>
        All the algorithms adopt the same Gaussian kernel. For fair comparison and simplicity, for all the datasets and algorithms, we set the regularization parameter {a mathematical formula}γ1=γ2=1 and kernel parameter {a mathematical formula}σ1=σ2=4 for the two views and {a mathematical formula}σ=8 for the whole feature. In addition, the regularization parameter C is set to 5 for all the algorithms on all the datasets. We conducted 20 runs of random permutations for each dataset and measured the average results of these 20 runs. In particular, we evaluate the performance of online learning methods by calculating the mistake rates, and evaluate the number of SVs and the time cost of the compared algorithms for efficiency evaluation.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Performance evaluation results
       </section-title>
       <paragraph>
        Table 5 summarizes the evaluation results of heterogeneous OTL tasks.
       </paragraph>
       <paragraph>
        Several observations can be drawn from the above results. First of all, we found that among all the algorithms, the PA algorithm without exploiting knowledge from source domain achieved very high mistake rate in most cases. This shows that it is important for studying knowledge transfer in an OTL task. Second, for all the datasets, we found that the HetOTL algorithm has the smallest mistake rate. This validates the proposed OTL technique is effective for knowledge transfer in the online learning tasks. By examining the running time cost, we found that the HetOTL techniques usually consumes comparable time with the other baselines except the PA algorithm, which is actually resulted in by the number of SVs stored by each algorithm. This clearly demonstrates the efficiency of the proposed HetOTL technique. Finally, Fig. 3 shows the details of the HetOTL processes. Firstly, the standard deviations are high for most of the algorithms, which reduces the significance of the improvement of the proposed algorithm. Secondly, similar observations on the average mistakes from the results, in a way, verify the proposed HetOTL method is effective for the challenging heterogeneous OTL tasks.
       </paragraph>
      </section>
      <section label="5.2.3">
       Sensitivity evaluation of parameter C for heterogeneous OTL
       <paragraph>
        Fig. 4 evaluates the online prediction performance of different algorithms with varied values of parameter C across all the heterogeneous learning tasks. Several observations can be drawn from the results. First of all, it is clear to observe that the proposed HetOTL algorithm is significantly more effective than the other algorithms for most cases. Second, among all the compared algorithms, we observe that the proposed HetOTL algorithm always achieves the best performance (or at least very close to the best performance, e.g., “landmine1” and “landmine2”) when C is sufficiently large (e.g., {a mathematical formula}C&gt;4). This shows that setting a large learning rate can improve the transfer learning efficacy. Third, we observe that HetOTL is significantly more accurate than the other transfer learning strategies under varied C values, which again validates the efficacy of the proposed OTL strategy. Fourth, HomOTL improves performance on the landmine datasets only if a suboptimal value of C is chosen. Finally, the PA algorithm performs the worst on all the datasets under varied C values.
       </paragraph>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Experiment III: OTL for learning with concept-drifting data streams
      </section-title>
      <section label="5.3.1">
       <section-title>
        Experimental testbed and setup
       </section-title>
       <paragraph>
        We now evaluate the empirical performance of the proposed technique for online learning tasks with concept-drifting data streams. We compare our CDOL algorithm with the standard Perceptron (denoted as “PE”) and PA algorithms. In addition, we also compare with two popular algorithms for concept-drifting online learning, i.e., the Modified Perceptron algorithm (denoted as “ModiPE” for short) [10], and the shifting Perceptron algorithm (denoted as “ShiftPE” for short) [6]. In addition, we also implement a variant of the CDOL which will set {a mathematical formula}Pi=P ∀i, and term it as CDOL(fixed).
       </paragraph>
       <paragraph>
        We evaluate the performance of all the algorithms on six benchmark datasets, as shown in Table 6, where the datasets “emaildata”, “usenet1” and “usenet2”, are downloaded from Concept Drift Datasets website,{sup:2} while the “MITface”, “newsgroup4” and “usps” are created by ourself by using the datasets downloaded from MIT website{sup:3} and the LIBSVM website, respectively. The details of “MITface”, “newsgroup4” and “usps” are shown in Table 7, Table 8, Table 9, respectively.
       </paragraph>
       <paragraph>
        All the algorithms employ the same Gaussian kernel, where the kernel width is set as {a mathematical formula}σ=8. Similarly, for fair comparison, we set the parameter C to 5 for all the algorithms on all the datasets. In addition, parameter λ is set to 1 for the Shift Perceptron algorithm, and parameter {a mathematical formula}P=30 is used for CDOL(fixed) and OWA, which is used to determine {a mathematical formula}Pi for CDOL automatically. We conducted 20 different runs of random permutations (the examples will be permutated within every period) to obtain the average results. We evaluate the accuracy of online learning algorithms by measuring the mistake rate, their model sparsity by measuring the number of SVs, and their efficiency by measuring time cost.
       </paragraph>
      </section>
      <section label="5.3.2">
       <section-title>
        Performance evaluation results
       </section-title>
       <paragraph>
        Table 10 summarizes the results for concept-drift online learning.
       </paragraph>
       <paragraph>
        Several observations can be drawn from the results. First of all, we found that for the first two algorithms without considering concept drift, the PA algorithm achieved better performance for most cases. This shows that PA can learn new knowledge more effectively than the passive PE algorithm. Second, among all the algorithms, the ModiPE and ShiftPE algorithms designed for learning with concept drift seldom outperform the simple PA algorithm, which indicates that concept drift learning is in general hard to solve and the existing techniques are still not effective enough. In addition, CDOL almost always outperforms CDOL(fixed), which implies that the proposed OWA algorithm could find proper {a mathematical formula}Pis effectively. Fourth, among all the evaluated algorithms, we found that the proposed CDOL algorithm achieved the smallest mistake rates for most of the datasets. This validates CDOL is effective for knowledge transfer in the concept-drift learning tasks. Of course, there is some cost for performing knowledge transfer for the gain achieved by the proposed CDOL method. By examining the running time cost, we found that CDOL usually took more time cost than the other algorithms, since it need take time to find the best {a mathematical formula}Pis. Finally, Fig. 5 shows the details of the concept-drift online learning processes. Similar observations can be found from the results, which again verify the proposed OTL technique is effective and promising for resolving the challenging tasks of online learning with concept drift.
       </paragraph>
      </section>
      <section label="5.3.3">
       Sensitivity evaluation of parameter C for concept-drifting learning
       <paragraph>
        Fig. 6 examines the online prediction performance of different algorithms with varied values of C for concept drifting online learning tasks. Several observations can be drawn from the results. First of all, it is clear to see that the proposed CDOL algorithm is considerably more effective than the other algorithms for most cases. Second, among all the compared algorithms, we observe that the proposed CDOL algorithm often achieves the best performance when C is sufficiently large (e.g. {a mathematical formula}C&gt;4) (except “usenet1”), which indicates a large learning rate can efficiently improve the transfer learning efficacy. Third, we observe that CDOL is significantly more accurate than the other two concept drift learning strategies: ModiPE and ShiftPE, under varied values of C, which again indicates the CDOL algorithm is more effective for concept drifting online learning tasks.
       </paragraph>
      </section>
     </section>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section label="A.1">
      Proof of Proposition 1
      <paragraph label="Proof">
       To facilitate the analysis, we denote {a mathematical formula}pt=α1,tΠ(v⊤xt)+α2,tΠ(wt⊤xt), {a mathematical formula}p1,t=Π(v⊤xt), and {a mathematical formula}p2,t=Π(wt⊤xt).It is straightforward to show that {a mathematical formula}F(z)=exp⁡(−12ℓ⁎(z,y)) is concave with respect to z for all y. Then according to Jensen's inequality{a mathematical formula} Denoting {a mathematical formula}ri,t=ℓ⁎(pt,Π(yt))−ℓ⁎(pi,t,Π(yt)) and rearranging the above inequality result in:{a mathematical formula} Combining the equality (2) with the above inequality, we have{a mathematical formula} Multiplying the two sides of the above inequality with {a mathematical formula}exp⁡(12∑j=1t−1ℓ⁎(pj,Π(yj))) results in{a mathematical formula} which further implies{a mathematical formula} Finally,{a mathematical formula} Plugging {a mathematical formula}pt=α1,tΠ(v⊤xt)+α2,tΠ(wt⊤xt), {a mathematical formula}p1,t=Π(v⊤xt), and {a mathematical formula}p2,t=Π(wt⊤xt) into the above inequality concludes the claim.  □
      </paragraph>
     </section>
     <section label="A.2">
      Proof of Proposition 2
      <paragraph label="Proof">
       It is not difficult to show the optimization in (6) is equivalent{a mathematical formula}{a mathematical formula}The Lagrangian of the above optimization problem is expressed as{a mathematical formula} where {a mathematical formula}τt≥0 and {a mathematical formula}λ≥0 are Lagrange multipliers. We now find the minimum of the Lagrangian w.r.t. {a mathematical formula}w1, {a mathematical formula}w2 and ξ by setting their partial derivatives to zeros. We get {a mathematical formula}wi=wi,t+τt2γiytxi,t for {a mathematical formula}i=1,2 and {a mathematical formula}C−τt−λ=0. And since {a mathematical formula}λ≥0, we conclude {a mathematical formula}C≥τt. We thus have {a mathematical formula}τt∈[0,C]. Plugging the three equations {a mathematical formula}wi=wi,t+τt2γiytxi,t (where {a mathematical formula}i=1,2) and {a mathematical formula}C−τt−λ=0 into Eq. (1), we have{a mathematical formula} Setting the derivative of the above to zero leads to:{a mathematical formula} Finally, combining the fact {a mathematical formula}τt∈[0,C], we thus have the final solution:{a mathematical formula}  □
      </paragraph>
     </section>
     <section label="A.3">
      Proof of Lemma 1
      <paragraph label="Proof">
       Let us introduce the following notation:{a mathematical formula} We then have{a mathematical formula} Second, when {a mathematical formula}ℓt=0, {a mathematical formula}wi,t+1=wi,t for {a mathematical formula}i=1,2, it is clear {a mathematical formula}Δt=0; when {a mathematical formula}ℓt&gt;0, {a mathematical formula}wi,t+1=wi,t+τt2γiytxi,t, we compute {a mathematical formula}Δt as:{a mathematical formula} We also have {a mathematical formula}ℓt=1−yt(12(w1,t⊤x1,t+w2,t⊤x2,t)) as {a mathematical formula}ℓt&gt;0, which is equivalent to:{a mathematical formula} In addition,{a mathematical formula} we thus have{a mathematical formula} Combining these two facts and inequality (2), we thus have the following:{a mathematical formula} Hence, we have the following conclusion:{a mathematical formula}  □
      </paragraph>
     </section>
     <section label="A.4">
      Proof of Proposition 3
      <paragraph label="Proof">
       First of all, we note that {a mathematical formula}Π(yt)=yt+12 since {a mathematical formula}yt∈{−1,+1}. Case 1.If {a mathematical formula}ytwt⊤xt∈(−∞,−1], then {a mathematical formula}ℓt≥2.
       <list>
        If {a mathematical formula}yt=−1, then {a mathematical formula}wt⊤xt≥+1 and {a mathematical formula}Π(wt⊤xt)=1 and {a mathematical formula}Π(yt)=0;If {a mathematical formula}yt=+1, then {a mathematical formula}wt⊤xt≤−1 and {a mathematical formula}Π(wt⊤xt)=0 and {a mathematical formula}Π(yt)=1;Case 2.If
       </list>
       <paragraph>
        {a mathematical formula}ytwt⊤xt∈(−1,+1), since {a mathematical formula}yt∈{−1,+1}, then {a mathematical formula}wt⊤xt∈(−1,+1), and {a mathematical formula}Π(wt⊤xt)=wt⊤xt+12∈(0,+1), as a result:{a mathematical formula}Case 3.If {a mathematical formula}ytwt⊤xt∈[+1,+∞), {a mathematical formula}ℓt=0.
       </paragraph>
       <list>
        <list-item label="3.1.">
         If {a mathematical formula}yt=−1, then {a mathematical formula}wt⊤xt≤−1 and {a mathematical formula}Π(wt⊤xt)=0=Π(yt);
        </list-item>
        <list-item label="3.2.">
         If {a mathematical formula}yt=+1, then {a mathematical formula}wt⊤xt≥+1 and {a mathematical formula}Π(wt⊤xt)=1=Π(yt);
        </list-item>
       </list>
       <paragraph>
        Accordingly, we have {a mathematical formula}ℓt⁎=(Π(wt⊤xt)−Π(yt))2=0=ℓt. In summary, we have {a mathematical formula}ℓt⁎≤min⁡{ℓt/2,ℓt2/4}.  □
       </paragraph>
      </paragraph>
     </section>
    </section>
   </appendices>
  </root>
 </body>
</html>