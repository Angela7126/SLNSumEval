<?xml version="1.0" encoding="utf-8"?>
<html>
 <body>
  <root>
   <title>
    How many diagnoses do we need?.
   </title>
   <abstract>
    A known limitation of many diagnosis algorithms is that the number of diagnoses they return can be very large. This is both time consuming and not very helpful from the perspective of a human operator: presenting hundreds of diagnoses to a human operator (charged with repairing the system) is meaningless. In various settings, including decision support for a human operator and automated troubleshooting processes, it is sufficient to be able to answer a basic diagnostic question: is a given component faulty? We propose a way to aggregate an arbitrarily large set of diagnoses to return an estimate of the likelihood of a given component to be faulty. The resulting mapping of components to their likelihood of being faulty is called the system's health state. We propose two metrics for evaluating the accuracy of a health state and show that an accurate health state can be found without finding all diagnoses. An empirical study explores the question of how many diagnoses are needed to obtain an accurate enough health state, and an online stopping criteria is proposed.
   </abstract>
   <content>
    <section label="1">
     <section-title>
      Introduction
     </section-title>
     <paragraph>
      A diagnosis problem arises when a system does not behave as expected. A solution to a diagnosis problem is a diagnosis, which is a set of components assumed to have caused the system's abnormal behavior. One of the fundamental approaches to automated diagnosis is Model-Based Diagnosis (MBD) [1], [2]. MBD has been studied in a vast spectrum of domains, including: automotive industry [3], [4], space [5], [6], robotics [7], [8] and computer software [9], [10].
     </paragraph>
     <paragraph>
      MBD requires an explicit model of the normal system behavior. Most MBD algorithms consider as a diagnosis every assumptions about which components are faulty that is logically consistent with the system model and the observed system behavior. This consistency-based approach to solve the diagnosis problem is principled and elegant, and many consistency-based diagnosis algorithms (DAs) have been proposed throughout the years (see examples referenced above).
     </paragraph>
     <paragraph>
      However, consistency-based DAs have a known limitations: the number of diagnoses that can be deduced from the system model and observations is often very large in non-trivial systems. This may be due to having an insufficient number of observations, an inaccurate model of the diagnosed system, and computational limitations.
     </paragraph>
     <paragraph>
      Some approaches apply minimality criteria to limit the number of diagnoses returned. One approach displays only diagnoses with the smallest number of components. Such diagnoses are known as minimal cardinality diagnoses. Considering only minimal cardinality diagnoses may miss potentially important diagnoses [11]. Another common approach is to return only diagnoses that are not a superset of another diagnosis. Such diagnoses are called minimal-subset diagnoses. Unfortunately, for systems with a large number of components, even the number of minimal cardinality diagnoses is so large that even enumerating them is time consuming [12]. For instance, in the known ISCAS-85 benchmark [13] the average number of diagnoses for the observations of Siddiqi [12] for system c880 with 383 components is 963,342 and for the system c1908 with 880 components is 1,894,733 [14].
     </paragraph>
     <paragraph>
      An alternative approach to reduce the number of diagnoses is to perform additional diagnostic actions, e.g., probing internal components and performing additional system testing [1], [15], [16]. Such actions can provide invaluable information for reducing the set of possible diagnosis. However, these actions often are costly that make it prohibitively expensive to reduce the set of diagnoses to a manageable size. Moreover, in some cases the set of possible diagnoses may stay too large even after performing any number of additional tests, due to inherent ambiguity of the system [17], [18].
     </paragraph>
     <paragraph>
      Some DAs assign a score to every returned diagnosis, which estimates the likelihood of each diagnosis to be correct. Given the likelihood of each diagnosis to be correct, one may consider displaying only the most probable diagnoses. Fig. 1, which is explained in greater detail later in this paper, shows an example where returning the most likely diagnosis is very misleading. The most likely diagnosis is that {a mathematical formula}C1 and {a mathematical formula}C2 are faulty, but it is actually more likely that {a mathematical formula}C3 is faulty since {a mathematical formula}C3 appears as faulty in most diagnoses. Thus, while showing a long list of diagnoses to a human operator is not helpful, focusing on a single diagnosis may miss important diagnostic information.
     </paragraph>
     <paragraph>
      The first contribution of this work is a method to aggregate the information stored in an arbitrarily large set of diagnoses in a useful and compact form. This aggregated form, which we call the health state of the diagnosed system, maps every component in the system to the likelihood of it being faulty. Having a system's health state allows answering a basic diagnostic question: is a given component faulty? This question is key in various diagnostic settings, including decision support for a human operator and automated troubleshooting processes.
     </paragraph>
     <paragraph>
      The second contribution of this work is an experimental investigation of the tradeoff between the quality of a health state and the number of diagnoses used to generate it. For this purpose, we propose three metrics for measuring the quality of a health state. The first metric is based on Euclidean distance from the optimal health state (where the true faults are known). The second metric views a health state as a classifier's model, and measures its quality according to the area under the curve (AUC) of a receiver operating characteristic (ROC) curve [19], which is a standard evaluation metric in the Machine Learning literature. The third metric is an adaptation of the wasted effort metric previously proposed for evaluating diagnoses [20], [21].
     </paragraph>
     <paragraph>
      The experimental investigation was performed over all these quality metrics. The first domain we experimented on is Boolean circuits, using the well established benchmarks ISCAS-85 [13] and 74XXX [22]. The second domain we used is software diagnosis, using the source files and reported bugs of Apache Ant, a popular open-source Java build tool [23]. For all quality metrics, we observed that the health state converges to a stable quality value without finding all diagnoses. This stable value is shown to be close to the best quality achievable, and in most cases such a value can be obtained by considering only minimal cardinality diagnoses (diagnoses with a minimal number of components). This supports the common MBD approach of focusing first on diagnoses with lower cardinality.
     </paragraph>
     <paragraph>
      Moreover, in most cases only a fraction of the set of minimal cardinality diagnoses is needed in order to reach a health state with a stable value. This result opens a great opportunity to develop DAs that determine online when to stop searching for more diagnoses [24]. A third contribution of this paper is by proposing such an online stopping condition for diagnosis algorithms. An empirical evaluation of this stopping condition shows that the quality of the system's health state is very close to the quality of the health state generated from all diagnoses.
     </paragraph>
     <paragraph>
      A shorter version of this work was published in the proceedings of AAAI 2015 [25]. Beyond providing more detailed explanations of the previously proposed health state quality metrics, we also consider another health state quality metric based on the wasted effort cost incurred when using this health state. An important contribution of this manuscript over the previous version is that we investigate how the quality of the health state is affected by different DAs. This investigation reveals interesting insights into the effectiveness of different DAs and the importance of finding minimal cardinality diagnoses. The final contribution of this paper, beyond the previous version, is by performing our experimental analysis over an additional domain of software diagnosis.
     </paragraph>
     <paragraph>
      The paper is structured as follows. Section 2 provides a formal definition of model-based diagnosis, and lists the basic assumptions we make about the output of a DA. Section 3 defines the notion of a health state, describes how we compute it, and proves the correctness of this computation under certain conditions. Section 4 presents several measures that one can use to evaluate the accuracy of a health state. Section 5 provides an empirical evaluation, where Section 5.2 evaluates the number of diagnoses required to achieve an accurate-enough health state and Section 5.3 studies the impact of different DAs on the number of diagnoses required to achieve an accurate health state. Section 6 shows how a simple online stopping condition, based on the health state values, can be used to decide online when to stop search for more diagnoses. Section 7 discusses how health states can be computed for DAs that consider a strong fault model. Finally, Section 8 lists related work and Section 9 concludes and lists possible directions for future work.
     </paragraph>
    </section>
    <section label="2">
     <section-title>
      Model based diagnosis
     </section-title>
     <paragraph>
      An MBD problem is specified as a triplet {a mathematical formula}〈SD,COMPS,OBS〉 where: {a mathematical formula}SD is a model of the diagnosed system, {a mathematical formula}COMPS is a set of components, and {a mathematical formula}OBS is an observation. SD takes into account that some components might be abnormal (faulty). This is specified by an unary predicate {a mathematical formula}h(⋅), such that {a mathematical formula}h(c) and {a mathematical formula}¬h(c) denote that component c is healthy or faulty, respectively. Denoting the correct behavior of c as a propositional formula, {a mathematical formula}φc, {a mathematical formula}SD is given formally as{a mathematical formula} Namely, a healthy component follows its correct behavior. A diagnosis problem (DP) arises when the assumption that all components are healthy is inconsistent with the system description and observation [1], [2]. System models can be classified into weak fault models (WFMs) and strong fault models (SFMs). In WFMs only the nominal behavior of every component is specified, while in SFMs additional information is available about how faulty components behave. For ease of presentation, we assume in this paper a WFM. In Section 7 we describe how the theoretical results in this paper generalize to SFM.
     </paragraph>
     <paragraph label="Definition 1">
      Fig. 2 shows an example of an MBD problem, where the normal behavior would give the output {a mathematical formula}E=1 but the observation had {a mathematical formula}E=0. See Appendix A for the formal system description and observations of this example. MBD algorithms try to find the actual faults – the faulty components that have caused the observed abnormal behavior of the diagnosed system. To this end, MBD algorithms often search for diagnoses, which are subsets of {a mathematical formula}COMPS that explain the observation if assumed faulty. DiagnosisA set of components {a mathematical formula}ω⊆COMPS is a diagnosis if the following term is consistent (i.e., it does not lead to a contradiction){a mathematical formula}
     </paragraph>
     <paragraph>
      Ideally, a DA will return a single diagnosis that contains exactly the actual faults. We refer to this diagnosis as the correct diagnosis. Clearly, the correct diagnosis is a diagnosis according to Definition 1, as long as the system model is correct and observations are accurate. Thus, a DA that returns all diagnoses is complete, in the sense that it will return the correct diagnosis.
     </paragraph>
     <paragraph>
      The key problem we address in this work is that for non-trivial systems, the number of diagnoses (as defined in Definition 1) is often much larger than one. Indeed, it is common that DAs return a set of diagnoses, denoted here as Ω, and in benchmark systems {a mathematical formula}|Ω| can be several hundreds of thousands [14], [12]. Note that such large number of diagnoses are not due to errors in the system description, but due to partial observability of the diagnosed system: if the input and output of every system component was observed, then finding the correct diagnosis would have been easy.
     </paragraph>
     <paragraph>
      Finding all of the diagnoses can be very time consuming and it is not clear how to reason about large sets of diagnoses in a meaningful and effective way. A common approach to limit the set of diagnoses to find and reason about is to only consider diagnoses that answer some minimality criteria.
     </paragraph>
     <paragraph label="Definition 2">
      Minimal DiagnosesWe say that a diagnosis ω is a minimal diagnosis if no proper subset {a mathematical formula}ω′⊂ω is a diagnosis, and that ω is a minimal cardinality diagnosis if no other diagnosis {a mathematical formula}ω′⊆COMPS exists such that {a mathematical formula}|ω′|&lt;|ω|.
     </paragraph>
     <paragraph>
      For the MBD of Fig. 2, {a mathematical formula}ω1={X1,X2}, {a mathematical formula}ω2={O1}, {a mathematical formula}ω3={A2} are all the minimal diagnoses, and {a mathematical formula}ω2, {a mathematical formula}ω3 are all the minimal cardinality diagnoses. Some MBD algorithms search for subset minimal diagnoses [26], [27], [28] and other MBD algorithms search only for minimal cardinality diagnoses [14], [29]. Finding a single minimal cardinality diagnosis is an NP-hard problem [30] and finding more than one minimal subset diagnosis is also NP-hard [31].
     </paragraph>
     <paragraph>
      Even if limiting the output of an MBD algorithm to only return minimal cardinality diagnoses, the number of returned diagnoses can still be exponential in the size of the diagnosis cardinality (the number of components assumed to be faulty). This occurs in practice in standard MBD benchmarks [12], [14]. The question of how to manage such a large set of output diagnoses still holds, even if limiting the set of diagnoses to only include minimal cardinality diagnoses.
     </paragraph>
     <section label="2.1">
      <section-title>
       Returning only the most probable diagnosis
      </section-title>
      <paragraph>
       Another principled way to limit the set of diagnoses returned is by only considering the diagnoses that are most likely to be the correct diagnosis. Indeed, some DAs return, in addition to a set of diagnoses Ω, a probability distribution p over Ω [32], [33], [34], [35], [21]. This {a mathematical formula}p(ω∈Ω) represents the probability that ω is the correct diagnosis given the observations (i.e., it is a posterior probability). Given such a probability function, one can focus the search for diagnoses towards more likely diagnosis [35], [28] or even return only the most probable diagnosis.
      </paragraph>
      <paragraph>
       While appealing, returning only the most probable diagnosis can be very misleading, as it ignores the information stored in all other diagnoses. Fig. 1 illustrates this. It depicts a hydraulic system in which components {a mathematical formula}C1,…,C8 are closed valves and component C9 is a tank. The observed system behavior is that oil flows into the system (depicted by the rectangle named “In”) and unexpectedly some oil leaks into the tank (C9), which is monitored by a sensor (depicted by the rectangle named “Out”). The set of subset minimal diagnoses{sup:1} is{a mathematical formula} Now, assume that the DA that we used returned also that the most probable diagnosis is {a mathematical formula}{C1,C2}, having a probability of 0.2, and all other diagnoses have a probability of 0.16. However, all diagnoses except the most probable diagnosis assume that {a mathematical formula}C3 is faulty. The probability mass of all these diagnoses is 0.8 – much more than the probability of most likely diagnosis (0.2). Thus the most likely explanation is actually that {a mathematical formula}C3 has failed, along with one of the components {a mathematical formula}C4, {a mathematical formula}C5, {a mathematical formula}C6, {a mathematical formula}C7 and {a mathematical formula}C8. More generally, considering only the most probable diagnosis ignores all the information that exists in the other diagnoses, and that information can lead to hypotheses about the system components' health that together are more likely than the most probable diagnoses being correct. The system health state defined next provides a principled way to consider the entire set of diagnoses and their probabilities.
      </paragraph>
     </section>
    </section>
    <section label="3">
     <section-title>
      The health state of a system
     </section-title>
     <paragraph>
      Given a large set of diagnoses, a reasonable question that a human operator might ask is “what is the probability that a component C is faulty?” This is helpful, for example, to highlight to an operator which component should be manually checked first. In addition, being able to estimate the likelihood of each component being faulty is helpful in troubleshooting algorithms [10], [36]. The health state defined below is exactly such a mapping of component to the probability that it is faulty.
     </paragraph>
     <paragraph label="Definition 3">
      Health StateA health state is a function {a mathematical formula}H:COMPS→[0,1] such that for every component {a mathematical formula}C∈COMPS:{a mathematical formula}
     </paragraph>
     <paragraph>
      Given a set of diagnoses Ω and a probability function over them p, we can derive a health state as follows{a mathematical formula} where {a mathematical formula}1C∈ω is the indicator function defined as:{a mathematical formula}
     </paragraph>
     <paragraph label="Theorem 1">
      Theorem 1 states exactly the assumptions required for Equation (1) to hold. Given a diagnosis problem{a mathematical formula}〈SD,COMPS,OBS〉a set of diagnoses Ω and a diagnosis likelihood function{a mathematical formula}p:Ω→[0,1], we can compute the corresponding health state using Equation(1)if all the following conditions hold:
     </paragraph>
     <list>
      <list-item label="1.">
       Ω is the set of all diagnoses.
      </list-item>
      <list-item label="2.">
       {a mathematical formula}p(ω)is the probability that ω is correct given the observations, i.e.,{a mathematical formula}
      </list-item>
     </list>
     <paragraph label="Proof">
      Let {a mathematical formula}Ω[C] be the set of diagnoses in Ω that contain C. Since we assume that Ω contains all the diagnoses, then if C is faulty it means that one of the diagnoses in Ω that assume it is faulty ({a mathematical formula}=Ω[C]) must be the correct diagnoses.{a mathematical formula} Every diagnosis is an assumption over all the components in COMP (see Definition 1). Therefore, there is exactly one correct diagnosis in Ω. Thus, two diagnoses cannot both be true, and more generally the probability that a given set of diagnoses contain the correct diagnosis is the sum of their probabilities. In our context:{a mathematical formula} as required. □
     </paragraph>
     <paragraph>
      Informally, Theorem 1 says that if Ω contains all diagnoses and the uncertainty over the true state of the world is accurately represented by p, then the health state generated by Equation (1) is accurate. Note that since only a single diagnosis is correct in a given state of the world, there is no notion of probability dependence between diagnoses. Generating a health state from a set of diagnoses Ω and p using Equation (1) is referred to in this paper as generating a health state from Ω and p.
     </paragraph>
     <paragraph>
      We argue that presenting a human operator with a health state is more meaningful and helpful than a long list of diagnoses, even if the diagnoses are prioritized by their probabilities. For example, consider Table 1, which shows the diagnoses found for the system depicted in Fig. 1. Every column represents a diagnosis and every row represents a components, where a value of “1” in column i and row j means that component j is part of diagnosis i. The values in the row labeled “p” show the probabilities of each diagnosis, and the values in the column labeled “{a mathematical formula}H(Ci)” show the value in the health state for the corresponding row. So, Table 1 shows that the DA returned five diagnoses {a mathematical formula}{C3,C4},{C3,C5},{C3,C6},{C3,C7},{C3,C8} with a probability of 0.16 each, and another diagnosis {a mathematical formula}{C1,C2} with a probability of 0.2. The most probable diagnosis is {a mathematical formula}{C1,C2}, having a probability of 0.2. The health state, however, would point at {a mathematical formula}C3 as the component that is most likely to be faulty, having the highest value in the health state: {a mathematical formula}H(C3)=0.8. This example demonstrates how a health state provides a more useful output than the most probable diagnosis.
     </paragraph>
     <paragraph>
      While a health state is an informative aggregation of a given set of diagnoses, some information contained in the set of diagnoses it was generated from, is lost. This lost information is the dependencies between the different components. For example, consider again the diagnoses in Table 1. The component {a mathematical formula}C1 is only a member of a single diagnosis {a mathematical formula}{C1,C2}. Thus, repairing only {a mathematical formula}C1 without repairing {a mathematical formula}C2 is not likely to fix the system. This relation between {a mathematical formula}C1 and {a mathematical formula}C2 is lost in the aggregated perspective of the health state. Note that this does not mean that the values in the health state are incorrect – component {a mathematical formula}C1 is still faulty with 20%. Automated troubleshooting algorithms [16], [1], [15] might make use of such additional relation information and might thus prefer as input a list of diagnoses over a health state.
     </paragraph>
     <paragraph>
      Finding a compact representation of a large set of diagnoses that does not lose some information is a hard problem that may not be solvable. The health state is proposed as a good compromise – it is compact ({a mathematical formula}O(|COMPS|)) and enables answering the basic diagnostic question – what is the probability of a given component to be faulty. Due to complexity reasons, DAs often do not return all consistent diagnoses. We expect that the quality of a health state depends on the diagnoses used to generate it. To study this relation, we require exact methods to evaluate the quality of a given health state. Next, we propose several such health state evaluation metrics.
     </paragraph>
    </section>
    <section label="4">
     <section-title>
      Evaluating a health state
     </section-title>
     <paragraph>
      An ideal health state indicates exactly which components are faulty and which components are healthy – setting {a mathematical formula}H(Ci)=1 for every {a mathematical formula}Ci that is faulty and setting {a mathematical formula}H(Cj)=0 for every {a mathematical formula}Cj that is not. We refer to such a health state as the offline optimal health state, denoted it by {a mathematical formula}H⁎. Formally:{a mathematical formula}
     </paragraph>
     <paragraph>
      Having such an ideal health state is not practical, since DAs commonly return more than a single diagnoses. In such cases, the resulting health state will be different from the offline optimal health state, reflecting the uncertainty over which diagnosis is correct. The question we raise is how accurate is a given health state. This question becomes even more important when considering that computational limitations often prevent MBD algorithms from returning all the diagnoses for a given diagnosis problem. In addition, the diagnosis probability function p is often a (usually rough) approximation. Thus, the actual question is how accurate is a health state generated from a given Ω and p. A complementing question is which and how many diagnoses should a DA return in order to generate a high quality health state.
     </paragraph>
     <paragraph>
      To answer these questions, a metric is needed to measure the quality of a generated health state. The term quality in general is often ambiguous. In our context, we use the term quality of a health state H to refer to how much different is H from the offline optimal health state {a mathematical formula}H⁎. This follows the reasoning that the offline optimal health state is perfect, and any deviation from it constitutes lower quality. Next, we present three such metrics for quantifying such a loss of quality, i.e., for quantifying the differences between H and {a mathematical formula}H⁎. Each metric has pros and cons, and we do not claim that any quality metric by itself is superior to the others.
     </paragraph>
     <section label="4.1">
      <section-title>
       The Euclidean distance metric
      </section-title>
      <paragraph>
       The first metric we propose for evaluating the quality of a health state is to consider every health state as a vector, and measure the accuracy of a health state H by its distance from {a mathematical formula}H⁎. There are several ways to compute distances between vectors, and in this work we use a simple Euclidean distance for this purpose, i.e.,{a mathematical formula}
      </paragraph>
      <paragraph>
       To demonstrate the Euclidean distance metric, consider our running example from Table 1 and assume that the faulty components (which are unknown to the diagnoser) are {a mathematical formula}{C3,C5}. The corresponding offline optimal health state is given in Table 1 in the column headed by {a mathematical formula}H⁎(Ci). The Euclidean metric for this case is {a mathematical formula}2⋅(0.2−0)2+(0.8−1)2+(0.16−1)2+4⋅(0.16−0)2 = 0.93. In general, a better health state according to this quality metric is one that has lower Euclidean distance, and zero Euclidean distance indicates that Ω contains a single diagnosis consisting of exactly the faulty components (i.e., the correct diagnosis).
      </paragraph>
     </section>
     <section label="4.2">
      <section-title>
       The area under the curve (AUC) metric
      </section-title>
      <paragraph>
       The second health state metric we propose is based on viewing the diagnosis problem as a classification problem and the health state as a parametric model of a classifier. Prior work have already formulated the diagnosis problem as a multi-label classification problem [37]. An optimal classifier labels correctly components as faulty or normal. They used a Machine Learning algorithm to learn a classifier and then model-based reasoning to refine the classifications suggested by that classifier (see Section 8 for a discussion on that work). We borrow from that prior work the idea of a diagnosis problem as a classification problem, and consider the health state as a parametric classifier, as follows. A component C is classified as faulty if {a mathematical formula}H(C)≥T, where T is a threshold parameter that can be tuned to control the sensitivity and specificity of the resulting classifier. Indeed, many classifiers accept as input a similar threshold parameter exactly for this reason. In our context, Setting {a mathematical formula}T=0 results in the classifier classifying all components as faulty, while {a mathematical formula}T=1 results in a classifier that only classifies components as faulty if they are faulty for certainty according to the health state (these are the components that are members of all the diagnoses in Ω). This classifier-oriented perspective of a health state corresponds to a natural repair policy: repair every component whose health state value is above the given threshold.
      </paragraph>
      <paragraph>
       A common metric for evaluating parametric classifiers is the AUC metric, and this is the second health state metric we propose. For completeness, we provide next a brief explanation of how the AUC metric is computed. For a given T, H, and {a mathematical formula}H⁎, it is possible to count the true/false positives/negatives as defined in Table 2. These definitions are used to compute the true positive rate (TPR) {a mathematical formula}TPR=TP/(TP+FN) and the false positive rate {a mathematical formula}FPR=FP/(FP+TN). Intuitively, TPR represents proportion of positives (in our case – faulty components) that are correctly identified as such, and FPR represents the probability that an instance is classified incorrectly as a positive (in our case – the probability that a component assumed faulty is actually healthy). TPR is also known as sensitivity or recall, and the complement of FPR – the true negative rate – is also known as specificity. By varying T the Receiver Operating Characteristic (ROC) curve can be drawn, which is the curve resulting from plotting the TPR against the FPR for a range of T values. A common measure for evaluating classifiers with such a threshold parameter is by measuring the area under the ROC curve. The AUC metric is exactly this area under the ROC curve. AUC values range from zero to one, where the best AUC value is one. An AUC value can be calculated by using a trapezoidal integration (approximation) or by an integral. We chose to use the trapezoidal integration: {a mathematical formula}AUC=∑i∈{0,0.1,...,0.9}((TPRi+TPRi+0.1)/2)⋅(FPRi+0.1−FPRi), where i represents the varied T (in our case it varies in interval of 0.1).
      </paragraph>
      <paragraph>
       Back to the running example, depicted in Table 1. Table (a) in Fig. 3 presents the TPR and the FPR for some thresholds, and Fig. 3b presents the appropriate ROC curve. The AUC in this case is 0.6675. In general, according to this quality metric higher AUC values represents a more accurate health state and the optimal health state will have an AUC of one.
      </paragraph>
     </section>
     <section label="4.3">
      <section-title>
       The wasted effort metric
      </section-title>
      <paragraph>
       Another possible health state quality metric is based on the wasted effort metric proposed by Abreu et al. [20], [21] for evaluating the output of a DA. The wasted effort metric estimates the effort wasted in repairing healthy components, given the diagnoses and probabilities returned by the DA. This metric is computed by assuming that components are repaired in the following order. First, the diagnoses returned by the DA are sorted according to their likelihoods. Then, we assume that components in the first diagnosis are repaired. Afterward, we assume that all the components in the second diagnosis are repaired. This continues until all faulty components are repaired. The wasted effort metric is the number of healthy components that are repaired in this process divided by the total number of healthy component. Thus, a wasted effort of zero is optimal, while a wasted effort of one is the worst outcome, meaning that all healthy components were repaired before repairing all the faulty ones.
      </paragraph>
      <paragraph>
       Consider our running example (from Fig. 2 and Table 1), where {a mathematical formula}C3 and {a mathematical formula}C5 are faulty. The first diagnoses is {a mathematical formula}{C1,C2}. Since both components are healthy and there are six healthy components, repairing {a mathematical formula}C1 and {a mathematical formula}C2 adds {a mathematical formula}26 to the wasted cost metric. The subsequent diagnoses all have equal probabilities, so assume that they are ordered lexicographically, i.e., the first diagnosis to be repaired is {a mathematical formula}{C3,C4}, then {a mathematical formula}{C3,C5} and so on. Repairing {a mathematical formula}{C3,C4} adds {a mathematical formula}16 to the wasted effort, as {a mathematical formula}C3 is indeed faulty. Finally, after {a mathematical formula}{C3,C5} is repaired all faulty components are repaired. Thus, the total wasted effort is {a mathematical formula}36.
      </paragraph>
      <paragraph>
       It is possible to adapt the wasted effort metric, which is used to evaluate diagnoses and probabilities, to evaluate health states. Instead of repairing the components in the diagnoses ordered by their probabilities, the health state wasted effort metric considers repairing components order by their probabilities in the health state. Thus, in our running example and assuming the same lexicographical tie-breaking, the first component repaired is {a mathematical formula}C3 (having {a mathematical formula}H(C3)=0.8), having the highest probability in the health state. Then {a mathematical formula}C1 and {a mathematical formula}C2 would be repaired (having {a mathematical formula}H(C1)=H(C2)=0.2). Finally, {a mathematical formula}C4 and {a mathematical formula}C5 will be repaired (having {a mathematical formula}H(C4)=H(C5)=0.16). The resulting total wasted effort is {a mathematical formula}36, since {a mathematical formula}C1, {a mathematical formula}C2, and {a mathematical formula}C4 are all healthy.
      </paragraph>
      <paragraph>
       Formally, we define the wasted effort metric as follows. Let F be the set of faulty components and assume that the components are sorted according to their health state values, i.e., {a mathematical formula}C1 has the highest {a mathematical formula}H(⋅) value, {a mathematical formula}C2 has the second highest {a mathematical formula}H(⋅) value, etc. Now, let {a mathematical formula}Ci be the set of components {a mathematical formula}{C1,…Ci}, i.e., the i components that have the highest {a mathematical formula}H(⋅) values. We define the wasted effort metric of a health state H as follows:{a mathematical formula}
      </paragraph>
      <paragraph>
       The wasted effort metric is presented since it is a natural adaptation of the existing wasted effort metric for a set of diagnoses and their probabilities. However, note that the wasted effort does not necessarily provide an accurate estimate of the actual effort wasted when repairing the system. First, troubleshooting algorithms for system repair often employ various costly diagnostic actions, such as setting probes and performing addition tests to get more observations. Second, intelligent system repair algorithms do not necessarily repair components in the order assumed by the wasted effort metric (in order of the probabilities in the health state). Other considerations also affect the choices made, such as cost of repair and uncertainty of repair outcomes [36], [38], [39]. For example, if two components have almost the same probability of being faulty according to the health state, but one is cheaper to repair than the other, then an intelligent system may choose to repair that component first, even if its probability is slightly smaller than the other component. Thus, the wasted effort metric is mostly given here for completeness and compatibility with previous work. As we show empirically in the next section, there is a strong correlation between this metric and the Euclidean and AUC metrics.
      </paragraph>
      <paragraph>
       All the proposed metrics can be used to evaluate health states. Using these metrics, we can study empirically the relation between the diagnoses returned by a DA and the quality of the resulting health state. As we show next, the resulting analysis provides key insights into how to design DAs to find high quality health states.
      </paragraph>
     </section>
    </section>
    <section label="5">
     <section-title>
      Empirical analysis
     </section-title>
     <paragraph>
      Next, we study experimentally the relation between the diagnoses returned by a DA and the quality of the health state generated from them. In particular, we (1) examine the amount of diagnoses required to produce a high-quality health state (Section 5.2), (2) compare the health states generated by using different DAs (Section 5.3), and (3) propose a stopping criterion that can be used online by a DA to halt the search for more diagnoses (Section 6).
     </paragraph>
     <section label="5.1">
      <section-title>
       Experimental settings
      </section-title>
      <paragraph>
       The experiments were performed on two domains: diagnosis of boolean circuits, and diagnosis of software bugs. Below we describe the details of our experiments in these domains, including the benchmark problems used, the DAs evaluated, and how diagnosis likelihood was computed.
      </paragraph>
      <section label="5.1.1">
       <section-title>
        Diagnosis of Boolean circuits
       </section-title>
       <paragraph>
        In this domain, the diagnosed system is a Boolean circuit, such as those used to design electrical circuits. The components in this domain are logic gates and the goal is to diagnose which gates are faulty. Evaluating DAs on Boolean circuits is standard in the literature, and in our evaluation we used two well-established standard Boolean circuit benchmarks: ISCAS-85 [13] and 74XXX [22]. Table 3 presents some basic information about these benchmarks: the systems' names (the column labeled “System”), number of components and number of inputs and outputs (columns labeled “{a mathematical formula}|COMPS|”, “In”, and “Out”). Due to computational complexity we did not run experiments on larger systems in ISCAS-85. The observations for the systems were drawn from Feldman's set of observations [40]. Note that observations for which the minimal cardinality diagnoses have a high cardinality correspond to scenarios that are more difficult computationally for most DAs, and, importantly, correspond to having a larger number of possible diagnoses. Since we study the question of how many diagnoses are needed, we experimented on a representative subset of Feldman's set of observations, choosing a random subset of observations per minimal cardinality. For each observation, we chose randomly one of the diagnoses to serve as the correct diagnosis. The rest of the columns in Table 3 include information about the observations we used: the number of observations (the column labeled “{a mathematical formula}|Observations|”), the average number of found diagnoses per observation (the column labeled “{a mathematical formula}|Ω|”), and the highest minimal cardinality value found among the different observations for each system (the column labeled “Max minc”).
       </paragraph>
       <paragraph>
        The DA we used was a forward search algorithm, first checking for single fault diagnoses, then all double faults, etc. Thus, diagnoses were returned in order of their cardinality, finding first all minimal cardinality diagnoses, then all subset-minimal diagnoses with cardinality higher than the minimal cardinality by one, and so on. To avoid memory limitations, we implemented this DA using an iterative deepening scheme. This DA was halted when all subset-minimal diagnoses were found or after 15 minutes runtime limit. While more sophisticated DAs exists, the focus of this work is not a new DA but to examine the outputted diagnoses. Moreover, what affects the number of diagnoses needed to produce a high quality health state is only the order in which the diagnoses are returned, not the runtime required to get it. Many DAs search diagnoses in an order similar to a forward search algorithm, starting by the smallest cardinality to largest. In Section 5.3 we discuss the impact of different diagnoses orderings on the number of diagnoses required.
       </paragraph>
       <paragraph>
        To compute the likelihood of a diagnosis ω, we followed a standard Bayesian approach:{a mathematical formula}
       </paragraph>
       <paragraph>
        Since all the diagnoses our DA returned are consistent and subset-minimal, we have that {a mathematical formula}Pr(Obs|ω)=1. The value {a mathematical formula}Pr(ω) represents the prior probability that the components in ω are faulty, without any observations. To compute {a mathematical formula}Pr(ω), we make two assumptions: (1) that we know for every component C the prior probability {a mathematical formula}Pr(C) that it will fail, and (2) that components fail independently of each other. Under these assumptions, {a mathematical formula}Pr(ω)=∏C∈ωPr(C).{sup:2} In reality, the component priors {a mathematical formula}Pr(C) can be given by the component manufacturer or approximated by applying Machine Learning methods [41]. In our experiments we set all {a mathematical formula}Pr(C) values to a constant 0.01. The assumption that faults occur independently, while not realistic in many cases, is a common assumption in MBD [1], [33], [28]. Finally, {a mathematical formula}Pr(Obs) is a normalizing factor, and thus, if Ω is the set of all diagnoses then we have{a mathematical formula}
       </paragraph>
       <paragraph>
        The focus of this work is not in proposing a novel way to compute the posterior probability that a diagnosis is correct. While commonly assumed in the academic literature, the assumptions we make in the computation of Equation (4) – known priors and independent failures – can be incorrect in practice, and there has been several prior work on taking into consideration more complex settings where these assumptions do not hold [34], [42]. Implementing and evaluating different methods for computing diagnosis probabilities is beyond the scope of this paper. Importantly, all the theoretical discussions in this paper are agnostic to how the diagnosis probabilities are obtained, and directly apply also to DAs that consider dependencies between component failures when computing {a mathematical formula}p(ω).
       </paragraph>
      </section>
      <section label="5.1.2">
       <section-title>
        Software diagnosis
       </section-title>
       <paragraph>
        The second domain we used is open-source software. In this domain, the software classes are the system components and the task is to find the classes that contain faults – software bugs – that caused some observed tests to fail.
       </paragraph>
       <paragraph>
        As a benchmark we used the open-source project Apache Ant [23], which is a popular build framework for Java. Apache Ant has 1,195 files and 10,830 methods. Over 1,176 bugs were found in Apache Ant and reported in the Bugzilla issue tracking system (www.bugzilla.org). Following prior work on software diagnosis [10], [41], we ran experiments on this dataset as follows. In every experiment we chose a subset of the reported bugs, created observations by running 40 tests selected randomly from the set of relevant JUnit tests. The passed and failed tests are given as input to a DA to find diagnoses (see detailed about the DA we used below). This type of experiment was performed 136 times.
       </paragraph>
       <paragraph>
        The DA we used is a data-augmented version of Barinel [41], referred to hereonafter as DA-Barinel. Barinel is a recent successful DA specifically designed for software diagnosis [20], [43]. It is significantly different from classical MBD algorithms in that it does not require a logical model of the correct functionality of every software component in the system. Instead, the traces of the observed tests are considered: Barinel treats every trace of a failed test as a conflict – a set of components that contain at least one faulty component, and returns hitting sets of theses conflicts as diagnoses. Barinel uses a fast but incomplete hitting set algorithm called STACATTO [44] that allows Barinel to scale well to large systems. An integral part of Barinel is how it computes diagnoses likelihoods. Briefly, they also use a Bayesian approach to compute diagnoses likelihoods, but since they handle multiple observations their computation also considers fault intermittency by incorporating a “goodness” function that estimates the probability that a faulty component will cause a test to fail. See [21] for details.
       </paragraph>
       <paragraph>
        DA-Barinel [41], which is the DA we used in our experiments, improves Barinel by using a data-driven approach to find more informed priors, which are then used by Barinel's Bayesian computation of diagnosis likelihood. In more details, these priors were generated using Machine Learning techniques on historical data of code versions and prior bugs. The learning process is done offline, before observing any failed test. In general, DA-Barinel is part of the LDP (Learn, Diagnose, and Plan) paradigm for software testing and debugging [41].
       </paragraph>
       <paragraph>
        As mentioned above, Barinel and DA-Barinel use a fast but incomplete hitting set algorithm called STACATTO [44] to scale to large systems. Thus it is possible that the correct diagnosis will not be included in the list of diagnoses they return. In practice, DA-Barinel found the correct diagnoses in 83 experiments out of the 136 experiments we performed. In the results below, we show experimental results averaged over all the 136 experiments (denoted as “All” in the tables below), including cases where the correct diagnoses was not found. To provide additional insights, we also show experimental results that are averaged only over the 83 experiments in which DA-Barinel found the correct diagnoses (denoted as “Complete” in the tables below).
       </paragraph>
       <paragraph>
        This experimental setting described above – software diagnosis using DA-Barinel – is significantly different from the standard Boolean circuits domain that was described in Section 5.1.1. Table 4 summarizes the differences between the experimental setups. First, the problem domains are different. Boolean circuits are the de-facto standard in evaluating MBD algorithms, and software diagnosis is an important application of automated diagnosis. Second, the DA used for Boolean circuit was a standard forward search DA while for the second setting we used a specialized DA for software diagnosis. Third, in the first setting the input to the DA is a system description (a model) and a single observation, while in the second setting the input are a set of observations – software tests with their traces and outcome (pass or fail). Forth, in the first setting the computation of diagnosis likelihoods relied on common simplifying assumption such as that all component have the same prior probability to fail. In contrast, the diagnosis likelihood computation in the second setting was evaluated in practice by prior work, and includes learning a fault prediction model to generate specific priors for every component. Lastly, the DA used for the first setting is complete, in the sense that the set of diagnoses it returns contains the correct diagnosis, while the DA used for the second setting is not.
       </paragraph>
      </section>
     </section>
     <section label="5.2">
      <section-title>
       Amount of diagnoses required
      </section-title>
      <paragraph>
       The main question we ask in this analysis is how many diagnoses are needed to produce a high quality health state. As a preliminary, we observed that after a certain number of diagnoses the quality of the health state converges to some stable value, after which adding more diagnoses results in negligible or non-existent change in health state quality. To demonstrate this, consider Fig. 4, Fig. 5 that show the health state quality for two observations of the 74182 system as a function of the number of diagnoses found. Quality (the y-axis) was measured here using the Euclidean distance metric, and thus lower values correspond to health state of a higher quality.
      </paragraph>
      <paragraph>
       Indeed, in both Figures after a certain number of diagnoses the quality of the health state converges to a stable value. For example, in Fig. 4 the health state quality converges to approximately 1.16 after 7 diagnoses returned by the DA. These two specific observations are representative examples, as we observed similar convergence in most of the problem instances we experimented with. This raises the question of how many diagnoses are needed for the health state to converge.
      </paragraph>
      <paragraph>
       A complementing question is what is the quality of the converged health state. As shown in Fig. 5, the health state after convergence can be worse than the health state generated from a smaller subset of all diagnoses. There (Fig. 5), the health state value starts at the optimal value (zero distance from {a mathematical formula}H⁎) and degrades to 0.07 where it remains stable. This is caused because the correct diagnosis happened to be the first diagnosis that was found by the DA.
      </paragraph>
      <section label="5.2.1">
       <section-title>
        Measuring convergence
       </section-title>
       <paragraph label="Definition 4">
        To answer the first question – how many diagnoses are needed for the health state to converge – we first define when a health state is considered to have converged. Let {a mathematical formula}Ωi be the set of the first i diagnoses returned by the DA, and let {a mathematical formula}Hi to be the health state generated from the diagnoses in {a mathematical formula}Ωi. For instance, {a mathematical formula}H2 is computed based on a set containing the first two diagnoses found by the DA. We say that the health state has converged after i diagnoses if {a mathematical formula}Hi is stable, where a stable health state is defined as follows. ϵ-Stable Health StateA health state {a mathematical formula}Hi is said to be ϵ-stable if for every {a mathematical formula}j&gt;i it holds that {a mathematical formula}|eval(Hj)−eval(Hi)|≤ϵ, where {a mathematical formula}ϵ≥0 is a parameter and {a mathematical formula}eval(Hi) is the quality of a health state {a mathematical formula}Hi according to the given quality metric.
       </paragraph>
       <paragraph>
        Note that for the AUC metric ϵ cannot be greater than one, while for the Euclidean distance it should not be larger than {a mathematical formula}|COMPS|.
       </paragraph>
       <paragraph>
        Now, we can ask the question of how many diagnoses are required to obtain an ϵ-stable health state. This is called the convergence rate of an observation. More formally, the convergence rate is the minimal {a mathematical formula}i∈[1,|Ω|] for which {a mathematical formula}Hi is ϵ-stable. In the results below we normalized the convergence rate by dividing them by {a mathematical formula}|Ω|. As an example, Table 5 lists the health state obtained for every {a mathematical formula}Ωi for our running example from Fig. 1 and Table 1. The right-most column shows the quality of every {a mathematical formula}Hi as measured by the Euclidean distance. For {a mathematical formula}ϵ=0.1 the convergence rate is {a mathematical formula}36, since {a mathematical formula}|eval(H3)−eval(Hi)|&lt;0.1 for every {a mathematical formula}i&gt;3, and there are 6 diagnoses. For {a mathematical formula}ϵ=0.2, two diagnoses sufficed to reach convergence, as {a mathematical formula}H2 is already 0.2-stable (as defined in Definition 4), and thus the convergence rate for {a mathematical formula}ϵ=0.2 is {a mathematical formula}26.
       </paragraph>
      </section>
      <section label="5.2.2">
       <section-title>
        Convergence rate results
       </section-title>
       <paragraph>
        We present first the result for the Boolean circuits experiments. Table 6, Table 7 show the average convergence rate and the wasted effort cost (in brackets) for AUC and Euclidean distance metrics, respectively, for a range of ϵ values. Each column represents the results for a set of observation of a single system (see Section 5.1 for details on each system). The row {a mathematical formula}ϵ=0 serves as a baseline, as convergence for {a mathematical formula}ϵ=0 is only reached once all diagnoses are found.
       </paragraph>
       <paragraph>
        The first clear trend we observe in these results is that it is possible to converge to a ϵ-stable health state without finding all diagnoses even for {a mathematical formula}ϵ=0.1. For example, consider the convergence rate results when using the AUC metric for system 74181. Only 17% of the diagnoses are needed to generate a health state that is at most 0.1 far from the health state generated from all diagnoses. This suggests that intelligent DAs can halt early without significant loss in health state quality.
       </paragraph>
       <paragraph>
        A second trivial trend is that increasing ϵ values decreases the convergence rate for both evaluation metrics. This flows directly from the definition of convergence rate. Comparing the convergence rate of the two quality metrics (AUC and Euclidean) suggests that the AUC metric provides more diverse results. For example, the convergence rate of the Euclidean distance metric quickly drops to 0.01 with virtually no effect of the ϵ value beyond {a mathematical formula}ϵ=0.3. By contrast, the convergence rate of the AUC metric ranges from 0.15 to 0.48, suggesting that AUC metric provides an evaluation metric that is easier to tune. This can be explained by the fact that AUC is normalized between 0 and 1, while Euclidean distance can range between 0 and {a mathematical formula}|COMPS|. Normalizing the Euclidean distance metric to the range {a mathematical formula}[0,1] is possible, but that would bias health states with more components to seem more accurate.
       </paragraph>
       <paragraph>
        The same trends observed in Table 6, Table 7 were also observed in the software diagnosis experimental results, which are shown in Table 8. The evaluation metric used is AUC. The columns are the ϵ values. The “All” row shows the results for all instances and the “Complete” row shows the results of only the instances where the DA found the correct diagnosis (the column marked “Complete”). The main trend – reaching convergence with a small fraction of all diagnoses – is clearly observed. For example, only 14% of the diagnoses were needed to reach a health state that is 0.1-stable. As could be expected, fewer diagnoses are needed to reach convergence in the cases where the DA actually returned the correct diagnoses. For example, only 6% of the diagnoses were needed to generate a 0.1-stable health state in the “Complete” experiment set (compared to 14% for the “All” experiment set). This provides a partial support that fewer diagnoses are needed to reach convergence for stronger DA. See more on this in Section 5.3.
       </paragraph>
      </section>
      <section label="5.2.3">
       The quality of ϵ-stable health states
       <paragraph>
        So far, we have examined the question of how many diagnoses are needed to reach a ϵ-stable health state. Here, we ask what is the quality of the converged health state, i.e., we inspect the actual quality of ϵ-stable health states. To this end, we considered the three quality metrics described in Section 4: wasted effort, Euclidean, and AUC.
       </paragraph>
       <paragraph>
        First, we analyzed the wasted effort metric. Fig. 6 shows the relation between the average wasted effort (y-axis) and the convergence rate (x-axis), for the Boolean circuits domain. The convergence rate was computed using the AUC metric for different values of ϵ. The relation is clear: the wasted effort decreases when the convergence rate increases. This was also verified by computing Pearson correlation coefficient, showing a strong negative correlation between the wasted effort and convergence rate, with {a mathematical formula}r=0.63, {a mathematical formula}n=42, and {a mathematical formula}p&lt;0.001. This correlation indicates that health states generated with more diagnoses tend to have a lower wasted effort value.
       </paragraph>
       <paragraph>
        Now, consider the wasted effort values of the converged health state for different values of ϵ. These results are given in brackets in Table 6, Table 7, Table 8. It is clear from the results in all the tables that the wasted effort cost grows with ϵ. This follows from the correlation of wasted effort and convergence rate (shown in Fig. 6): converging to an ϵ-stable health state for smaller ϵ requires a more diagnoses, and thus the health state is more reliable and, on average, the wasted effort cost decreases.
       </paragraph>
       <paragraph>
        Considering the wasted effort values provides an additional reason to prefer AUC over Euclidean distance. For most systems, the gap between the wasted effort cost of {a mathematical formula}ϵ=0 and {a mathematical formula}ϵ=0.1 is high. By contrast, the gap between similar ϵ values for AUC is more modest. For example, consider the 74283 system. The wasted effort cost for the health state generated from all diagnoses (the {a mathematical formula}ϵ=0 line) is 0.18. Now consider the health state for {a mathematical formula}ϵ=0.1. The health state generated from the diagnoses found until convergence according to the Euclidean distance has a wasted effort cost of 0.44 – much worse than the 0.18 for {a mathematical formula}ϵ=0. By contrast health state generated for the AUC metric has a wasted effort cost of 0.19 – almost the same as the wasted effort cost for {a mathematical formula}ϵ=0. This further supports AUC as a more flexible metric. Moreover, note that this health state (that resulted in 0.19 wasted effort cost) was generated from only 15% of the diagnoses. This result strengthens the conclusion that intelligent DAs can halt early and obtain a useful health state.
       </paragraph>
       <paragraph>
        This conclusion is also supported by the software diagnosis results (shown in Table 8). When considering the “All” results, the wasted effort having all diagnoses is 0.05, while it is only increased by 0.01 even for {a mathematical formula}ϵ=0.5. This is especially surprising, since the convergence rate for {a mathematical formula}ϵ=0.5 is 0.08, i.e., only 8% of the diagnoses are needed to create a health state that has only 0.01 more wasted effort cost than the health state generated by all diagnoses. Moreover, for the “Complete” version of the experiments, the wasted cost was 0 even for {a mathematical formula}ϵ=0.5.{sup:3} This means that even by finding only {a mathematical formula}5% of the diagnoses we do not loss any information related to the diagnosis, in this setting.
       </paragraph>
       <paragraph>
        In Section 4.3 we argued against the wasted effort cost metric (as adapted for evaluating health states) because its computation assumes a very rigid repair policy. Nonetheless, we provided the wasted efforts results above since this metric is based on a known metric for evaluating a set of diagnoses [20], [21]. Next, we analyzed health state quality using the other health state quality metrics we proposed: AUC and Euclidean distance.
       </paragraph>
       <paragraph>
        Table 9, Table 10 show the average AUC and Euclidean distance values, respectively, for a range of ϵ values. For example, the value 0.82 for system 74181 and {a mathematical formula}ϵ=0.1 in Table 9 is the AUC value of the health state obtained by halting the diagnosis process when reaching a ϵ-stable health state for {a mathematical formula}ϵ=0.1. Recall that higher quality health states corresponds to higher values of AUC and to lower values of Euclidean distance.
       </paragraph>
       <paragraph>
        The results show that increasing ϵ results in a lower quality health state. This demonstrates the expected tradeoff between the number of diagnoses used to generate a health state and its quality. Indeed, we already observed this tradeoff for the wasted effort metric in Fig. 6. This is basically the classical runtime vs. solution quality tradeoff, as finding more diagnoses requires more runtime.
       </paragraph>
       <paragraph>
        Nonetheless, we observe that the actual difference between the AUC/Euclidean values of obtained with all diagnoses ({a mathematical formula}ϵ=0) are often very close to those obtained for {a mathematical formula}ϵ=0.1. For example, the AUC obtained with all diagnoses for system c880 is 0.87 while for {a mathematical formula}ϵ=0.1 it was 0.84. This is especially remarkable because it means that one can obtain a 0.1-stable health state with only 29% of the diagnoses (see Table 6 for these results). Similar trends can be observed in most systems, including the software diagnosis domain.
       </paragraph>
       <paragraph>
        Note that while the results showed that the health state obtained using all the diagnoses is better than the one obtained with fewer diagnoses on average, there are individual observations where adding more diagnoses do not improve the health state quality. Such an example was shown in Table 5, where {a mathematical formula}H3 was better than health states generated with more diagnoses. Thus, to provide further context for the presented quality values, Table 9, Table 10 also contain a special row, marked “Oracle”. The Oracle values represent the quality of the health state generated by a DA that has an optimal stopping condition: it stops when adding more diagnoses will not improve the health state. More formally, for AUC the Oracle value is {a mathematical formula}maxi∈{1,...,|Ω|}⁡(eval(Hi)) and for the Euclidean distance the Oracle value is {a mathematical formula}mini∈{1,...,|Ω|}⁡(eval(Hi)). For example, in our running scenario the Oracle value is 1.23, which is obtained after finding the first three diagnoses (see Table 5 for the {a mathematical formula}eval(Hi) values). Note that the Oracle is computed for a specific order of the returned diagnoses, and for that order the quality of a ϵ-stable health state cannot be better than the Oracle value.
       </paragraph>
       <paragraph>
        Considering the results in Table 9, Table 10, we observe that in practice the difference in quality between Oracle value and the health state obtained using all the diagnoses ({a mathematical formula}ϵ=0) is relatively small. For the Boolean circuits experiments, the largest difference is 0.11 and 0.03 for the AUC and the Euclidean distance metric, respectively. The differences are even smaller for the software diagnosis experiments. Note that the AUC value of the “All” software diagnosis experiments is not as high as in the Boolean circuit experiments (0.71 compared to approximately 0.90) even for the Oracle. This is because there are 53 out of 136 observations in which the correct diagnosis (the one that consists the faulty components) does not exist in the list of diagnoses found by the DA (Ω) and thus the true positives are low.
       </paragraph>
       <paragraph>
        The fact that using all diagnoses is relatively close to the Oracle value is especially interesting because the results also show that with {a mathematical formula}ϵ=0.1 we get a health state that is almost the same as for {a mathematical formula}ϵ=0, and consequently to the Oracle value. This is important because as shown in Table 6, Table 7, Table 8, the ϵ-stable health state for {a mathematical formula}ϵ=0.1 is generated from a small portion of the entire set of diagnoses. This demonstrates the potential benefit of a smart DA that will halt early the search for diagnoses but still end up with a high quality health state. More generally, our conclusions from the analysis so far are:
       </paragraph>
       <list>
        <list-item label="•">
         For all quality metrics, only a small subset of all diagnoses are needed to reach a ϵ-stable health state.
        </list-item>
        <list-item label="•">
         Increasing ϵ results in fewer diagnoses required to find a ϵ-stable health state.
        </list-item>
        <list-item label="•">
         AUC is easier to tune effectively than Euclidean distance, since its values are normalized between 0 and 1.
        </list-item>
        <list-item label="•">
         The wasted effort cost is correlative with the convergence rate.
        </list-item>
        <list-item label="•">
         A small fraction of the diagnoses is needed to generate a health state that has almost the same quality as the health state generated by all diagnoses, for all the proposed quality metrics (wasted effort, AUC, and Euclidean distance).
        </list-item>
       </list>
      </section>
     </section>
     <section label="5.3">
      <section-title>
       Diagnoses from different DAs
      </section-title>
      <paragraph>
       In the above analysis we used a domain-specific solver for the software diagnosis domain, and a standard forward-search DA for the Boolean circuits domain that returns diagnoses in increasing order of their cardinality. Denote this order of increasing cardinality as a “Forward” order. Many DAs search for diagnoses in a forward order [14], [45], [27], but finding diagnoses in different orders may be faster [46]. In this section we investigate the impact of different ordering of diagnoses on the quality of the generated health state.
      </paragraph>
      <paragraph>
       “Backward” order stands for a decreasing order of the diagnoses, from biggest to smallest cardinality. In this order, the first health state is calculated based on a subset-minimal diagnosis that had the maximal number of faulty components. The last health state is calculated based on having all previous diagnoses and a new diagnosis that had the minimal number of faulty components. “Random” order stands for a random order of the subset-minimal diagnoses. To minimize variance, the results for Random order were obtained by repeatedly (20 times) calculating the health state of a randomly ordered set of subset-minimal diagnoses found by our DA. The last order we examined is the order of diagnoses as returned by the SAFARI algorithm [46], a stochastic state-of-the-art DA. We denote this order by “SAFARI”. SAFARI uses a SAT solver to initiate a candidate diagnosis and then employs an iterative elimination procedure in order to minimize its cardinality. SAFARI requires two parameters M and N as inputs. N represents the number of randomly independent searches for the first consistent candidate diagnosis and M represents the number of attempts the DA makes to improve the cardinality of the initial diagnoses (while preserving their consistency). It is important to state that this procedure does not guarantee minimal cardinality diagnoses. In our experiment we set {a mathematical formula}N=440 which is approximately the average number of overall diagnoses found per system and M was not set to a fixed number but rather to the cardinality of the initial candidate diagnosis (the number of faulty components in the initial consistent candidate diagnosis).
      </paragraph>
      <paragraph>
       Table 11, Table 12 present the convergence rate of the different orderings – Forward, Backward, Random and SAFARI. All results are for {a mathematical formula}ϵ=0.1, where Table 11 presents the results achieved using the AUC metric and Table 12 presents the results achieved using the Euclidean distance metric. For every system, the smallest convergence rate is marked in bold. It is clear that the order significantly affects the convergence rate, while the wasted effort cost is not significantly affected. In most cases the Forward order convergence rate is lower than the convergence rate in other orders. The difference is especially prominent when comparing it to the Backward order. Note that the quality of the health state obtained after convergence was very similar between the ordering. The wasted effort values shown in brackets show this, and similar trends were observed for the other quality metrics.
      </paragraph>
      <paragraph>
       Thus, a forward search, in general, is able to find health states of similar quality but with fewer diagnoses, which can translate to lower runtime. To illustrate the benefit of the Forward order, consider the convergence rate and wasted effort cost achieved using the AUC metric for 74181 system. Returning diagnoses in Forward order needs only 17% of the diagnoses in order to obtain a ϵ-stable health state, whereas the Backward order needs the computation of 84% of the diagnoses to obtain a ϵ-stable health state. Moreover, the wasted effort cost obtained by the Backward order is greater by 0.02 than that of the Forward order.
      </paragraph>
      <paragraph>
       The convergence rate of the Random order is somewhere between the Forward and Backward order. The convergence rate results for the different orders can be explained by the ratio of minimal cardinality diagnoses found (diagnoses that have minimal number of faulty components). The Forward order health state calculation is based on fewer diagnoses (lower convergence rate), however, these diagnoses include all minimal cardinality diagnoses. The Random order health state calculation is based on more diagnoses but fewer minimal cardinality diagnoses and the Backward order health state calculation is based on the least amount of minimal cardinality diagnoses. This indicates that finding minimal cardinality diagnoses, as commonly believed in MBD, is better.
      </paragraph>
      <paragraph>
       Let us observe the SAFARI results. SAFARI was shown to return diagnoses of good quality [46], however, theses diagnoses are not guaranteed to be of minimal cardinality. Surprisingly, SAFARI results in our experiments sometimes outperform even the Forwards order. This can be explained as follows: The Forward search order is generated by performing a breadth-first search over the space of possible diagnoses. Thus, diagnoses with common components are found together. As a result, subsequent diagnoses in Forward order are relatively similar to each other. This may affect the health state much by increasing the value of the common components. By contrast, SAFARI searches the space of diagnoses semi-randomly, and thus the diagnoses it returns are more diverse and build the health state more evenly.
      </paragraph>
      <section label="5.3.1">
       <section-title>
        Finding minimal cardinality diagnoses
       </section-title>
       <paragraph>
        Many previously proposed DAs focus on finding only minimal cardinality diagnoses, which are diagnoses that have minimal number of faulty components [14], [45]. The rational of this focus lies in the belief that malfunction containing smaller number of faulty components is more likely to occur. As a side note, we explored the relation between the number of diagnoses required until the health state converges to a stable value and the number of minimal cardinality diagnoses.
       </paragraph>
       <paragraph>
        Our results provide some support for this rational: in more than 70% of the observations in all the examined Boolean circuits systems, the health state has converged to a ϵ-stable value (using the AUC metric) without requiring any diagnosis that is not of minimal cardinality. Using the Euclidean distance metric, almost all the observations (more than 90%) needed only to compute minimal cardinality diagnoses to obtain a ϵ-stable health state. Thus, in most cases, limiting the DA to find only minimal cardinality diagnoses seems to be a reasonable choice.
       </paragraph>
       <paragraph>
        Moreover, a high-quality health state can be found with only a subset of all minimal cardinality diagnoses. Table 13, Table 14 show the ratio of minimal cardinality diagnoses (where 1 corresponds to all minimal cardinality diagnoses) required on average, to reach a ϵ-stable health state using AUC and Euclidean metrics respectively. As can be seen, even for {a mathematical formula}ϵ=0.1, only a fraction of the minimal cardinality diagnoses are needed to reach a ϵ-stable health state. For example, only 17% of the minimal cardinality diagnoses are needed to generate a health state that is ϵ-stable for {a mathematical formula}ϵ=0.1 for the 74181 system under the Euclidean distance metric (Table 14). Note that the values are normalized by the total number of the minimal cardinality diagnoses and therefore they are higher than the values presented in Table 6, Table 7 which are normalized by all diagnoses.
       </paragraph>
      </section>
     </section>
    </section>
    <section label="6">
     <section-title>
      Online stopping criteria
     </section-title>
     <paragraph>
      The results described above suggest that finding high quality health states is possible without finding all the diagnoses. This is a very important observation because it means that we can halt the DA earlier without losing the quality of the resulting health state. Now, we wish to propose a stopping condition that could be used online to determine when to stop the search for more diagnoses. Such a stopping criteria is especially needed in stochastic DAs such as SAFARI [46], which are known to work well in practice but require parameter tuning. We propose a simple stopping condition: halt when the Euclidean distance between two subsequent health states ({a mathematical formula}Hi and {a mathematical formula}Hi+1) is below a predefined threshold δ.{sup:4}
     </paragraph>
     <paragraph>
      The “{a mathematical formula}δ=X” rows in Table 15, Table 16 show the average AUC and Euclidean distances, respectively, obtained by using this online stopping criteria for a range of δ values. Since no subsequent diagnoses are exactly the same the Euclidean distance between {a mathematical formula}Hi and {a mathematical formula}Hi+1 is never zero. Thus, the {a mathematical formula}δ=0 row actually means the health state generated from all diagnoses. Marked in bold are the best values per system.
     </paragraph>
     <paragraph>
      Although the proposed online stopping condition is very simple, the results in Table 15, Table 16 show that the resulting values for {a mathematical formula}δ=0.1 are almost exactly the same as those obtained for health states generated from all diagnoses ({a mathematical formula}δ=0). In some cases, the health state obtained by the online stopping condition is even better than the health state of all diagnoses. The health state found when using the online stopping is also comparable to the quality obtained by the ϵ-stable health state for {a mathematical formula}ϵ=0.1 (presented in Table 9, Table 10).
     </paragraph>
     <paragraph>
      An online stopping condition such as the one proposed above can be only one part of a more holistic diagnosis system, in which one is also capable of performing diagnostic actions that provide additional information and prune possible diagnoses. Such a system poses interesting challenges such as when obtaining additional observations is better than searching for additional diagnoses for the current set of observations. To this end one needs to weigh the potential benefit to the obtained health state of finding more diagnoses compared to obtaining new observations. Proposing such a system is beyond the scope of this work.
     </paragraph>
    </section>
    <section label="7">
     <section-title>
      Discussion
     </section-title>
     <paragraph>
      Our experiments were performed on two domains: Boolean circuits and a software diagnosis. The Boolean circuit domain were chosen since they are a standard benchmark in the diagnosis literature, used in numerous prior works [47], [46], [48], [12], [26], [49] and even used as a standard for automatic benchmark generation [50]. The software diagnosis domain is a real world domain and have been recently used for software diagnosis experiments [41]. However, both domains have a weak-fault model, i.e., the abnormal behavior of components is not modeled.
     </paragraph>
     <paragraph>
      However, the theoretical results in this paper can be generalized to a model where the faulty behavior of the components is expressed (a strong fault-model). The key difference between a health state for a weak fault-model (WFM) and health state for a strong fault model (SFM). In a WFM, the health state maps a component to the probability that it is faulty. In a SFM, the health state maps a component and behavior mode to the probability that this behavior mode it is the correct behavior mode for that component. Note that since it is harder for DAs to produce diagnoses for SFM, and usually DAs outputs more diagnoses, then the expected benefit from considering the health state and ending the search before finding all diagnoses can be great. This is a topic for future work.
     </paragraph>
     <paragraph>
      Another interesting topic is how to obtain and evaluate health states in real hybrid systems, which deal with continuous values rather than Boolean values. For components that have discrete behavior modes, e.g., health or faulty, the health state can be defined exactly as in this paper. The problem becomes more complex for components that do not have such discrete behavior modes, but have a continuous “health” value that specifies its deviation from the nominal behavior. The challenge there is how to aggregate such values from a set of diagnoses in a meaningful way. One approach can be to average for every component the health value assumed to them in every diagnoses. This too is an exciting topic for future work.
     </paragraph>
    </section>
    <section label="8">
     <section-title>
      Related work
     </section-title>
     <paragraph>
      Many approaches and algorithms for MBD have been proposed. A classic approach to MBD, implemented in DAs like GDE [1], CDA* [28], SDE [26] and HS-DAG [51], find diagnoses in a two stage process. First, conflict sets are identified, each of which includes at least one fault. Then, a hitting set algorithm is used to extract diagnoses from these set of conflicts [2]. Others have proposed a compilation-based approach. For instance, Torasso and Torta [52] apply Binary Decision Diagrams (BDDs) and Darwiche [53] compiles an MBD problem into Decomposable Negation Normal Form (DNNF). Feldman et al. [54] propose MERIDIAN which compiles the MBD problem as a MAX-SAT problem. Recently, Metodi et al. [14] proposed a novel SAT-based approach to compute minimal cardinality diagnoses. A diagnosis algorithm based on a greedy stochastic approach was also proposed [24]. All these DAs may potentially return a large set of diagnoses. Thus, they are orthogonal to our work, as a health state can be generated from the set of diagnoses, regardless of the DA used.
     </paragraph>
     <paragraph>
      Keren et al. [37] present an alternative approach to diagnosis that combines MBD with multi-label classification. They propose to build a classifier that maps symptoms (observations) of the system to possible faults. The major advantage of this approach is in reducing significantly the online computational complexity. The learning process of the relations between observations and the diagnoses is performed in advance offline. Afterward (online), a diagnosis can be computed immediately by using the classifier that was learned offline. Unlike other DAs mentioned above, this machine learning approach to diagnosis returns a single diagnosis. Similar to the AUC metric we used to evaluate health states, the output of this machine learning DA is measured using standard classification metrics such as false positives and false negatives. A key difference is that we do not propose a new DA that returns a single diagnosis, but propose a general approach for aggregating a set of diagnoses that can be applied for a wide range of DAs.
     </paragraph>
     <paragraph>
      Maier et al. [55] remark that solutions to AI problems in engineering domains need to be compactly represented for the needs of engineers. However, we approach this challenge from opposite sides: we aim to compactly represent information generated from a low-level representation (a large number of diagnoses), while they assume a high-level representation is available and aim to auto-generate low-level representation such as Bayesian networks to serve as input to off-the-shelf diagnostic tools. Thus, the two approaches are complementary.
     </paragraph>
     <paragraph>
      Some methods try to deal with reducing the number of diagnoses after they are found. There are two known methods to discriminate diagnoses: testing and probing[1]. In testing, the diagnosis process is run through additional input vectors. Probing is similar, but instead of running the diagnosis on a new input vector, probes are observations of the output of internal components. Both methods can prune diagnoses, removing diagnoses that are not consistent with the new observations. Both methods can be run iteratively until hopefully focusing on a single diagnosis. Since assigning probes and performing tests are costly tasks, the main challenge in both methods is to reduce the number of probes or tests. A common greedy approach to address this challenge is to choose a probe or a test that maximizes the information gain [16]. Others analyze the model and diagnoses to find crucial literals, whose values can differentiate the possible diagnoses [56], or model testing as abductive reasoning [57]. The fundamental difference between any form of interactive diagnosis – probing and testing – and ours is that we do not consider how to obtain new information, but only how to aggregate the information already given by the DA. Moreover, in probing and testing the aim is to minimize the “physical” cost incurred by performing probes and tests, while we aim to avoid the computational cost of computing all diagnoses.
     </paragraph>
     <paragraph>
      A new approach to testing has been proposed by Feldman et al. [6] as part of the LYDIA-NG framework for Model-Based Diagnosis. This framework uses active testing on a real satellite Electrical Power System to decrease the diagnostic uncertainty in order to determine likely explanation faults. Similar to our work, they also use several known metrics in order to compute the residual difference, meaning the distance to the truly diagnosis (the faults that have actually occurred). The computation of metrics allows users to compare the performance of various diagnostic and simulation approaches. The LYDIA-NG framework presents a single diagnostic output containing the normalized probability of failure for each component. Our approach uses the residual difference to calculate the added value of finding more diagnoses, and presents as an output the health state – the likelihood of each component to be faulty.
     </paragraph>
    </section>
   </content>
   <appendices>
    <section label="Appendix A">
     <section-title>
      System description of a simple Boolean circuit
     </section-title>
     <paragraph>
      Here is a system description (SD) of the simple Boolean circuit given in Fig. 2.{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula}{a mathematical formula} The observations in Fig. 2 are represented as the following conjunction.{a mathematical formula}
     </paragraph>
    </section>
   </appendices>
  </root>
 </body>
</html>